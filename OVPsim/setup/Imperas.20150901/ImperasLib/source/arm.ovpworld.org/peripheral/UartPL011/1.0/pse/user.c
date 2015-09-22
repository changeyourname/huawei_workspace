/*
 * QEMU Uart Emulator.
 *
 * Copyright (c) 2003 Fabrice Bellard
 * Copyright (c) 2006 Openedhand Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <string.h>

#include "pse.igen.h"

#define BPORT1 0
#include "pse.macros.igen.h"

//////////////////////////////// Callback stubs ////////////////////////////////

typedef enum uart_typeE {
    PL011_ARM,
    PL011_LUMINARY
} uart_type;

// Internal state
uart_type    uType;
static Uns32 read_fifo[16];
static Int32 read_pos;
static Int32 read_count;
static Int32 read_trigger;
static Int32 channel;        // serial socket/log channel
static bhmEventHandle charReceived, charSent;

#define DEFAULT_RX_DELAY 20000
// map generated names to shorthand
#define flags          bport1_ab_data.flags.value
#define int_level      bport1_ab_data.int_level.value
#define int_enabled    bport1_ab_data.int_enabled.value
#define dmacr          bport1_ab_data.dmacr.value
#define lcr            bport1_ab_data.lcr.value
#define cr             bport1_ab_data.cr.value
#define ifl            bport1_ab_data.ifl.value

#define RXFF           BPORT1_AB_FLAGS_RXFF
#define RXFE           BPORT1_AB_FLAGS_RXFE
#define TXFF           BPORT1_AB_FLAGS_TXFF
#define TXFE           BPORT1_AB_FLAGS_TXFE

#define FEN            BPORT1_AB_LCR_FEN

#define TX             BPORT1_AB_INT_LEVEL_TX
#define RX             BPORT1_AB_INT_LEVEL_RX

#define DIAG_LOW       (diagnosticLevel>= 1)
#define DIAG_MEDIUM    (diagnosticLevel>= 2)
#define DIAG_HIGH      (diagnosticLevel>= 3)

//
// ID
//
static const unsigned char id[2][8] = {
  { 0x11, 0x10, 0x14, 0x00, 0x0d, 0xf0, 0x05, 0xb1 }, /* PL011_ARM */
  { 0x11, 0x00, 0x18, 0x01, 0x0d, 0xf0, 0x05, 0xb1 }, /* PL011_LUMINARY */
};

void update(void)
{
    Bool f = (int_level & int_enabled) && 1;
    static Bool current = 0;
    if(DIAG_HIGH) {
        bhmMessage("I", "PL011_UPDATE", "Int %d->%d (level 0x%02x enabled 0x%02x)", current, f, int_level, int_enabled);
    }
    if (f != current) {
        current = f;
        if(DIAG_HIGH) {
            bhmMessage("I", "PL011_INT", "%d", current);
        }
        ppmWriteNet(handles.irq, current);
    }
}

Bool can_receive(void) {
    if (lcr & 0x10)
        return read_count < 16;
    else
        return read_count < 1;
}

void chr_write(Uns8 *data, Uns32 bytes){
    if(DIAG_HIGH) {
        if (bytes == 1) {
            bhmMessage("I", "PL011_TX", "Tx %c", (char)*data);
        } else {
            bhmMessage("W", "PL011_TX", "Sending multiple characters, first Tx %c", (char)*data);
        }
    }

    bhmSerWrite(channel, data, bytes);
    bhmTriggerEvent(charSent);
}

void receiveByte(Uns32 value)
{
    Int32 slot = read_pos + read_count;
    if (slot >= 16)
        slot -= 16;
    if(DIAG_HIGH) {
        bhmMessage("I", "PL011_RX", "Rx fifo[%d] = 0x%x (%c)", slot, (char)value, (char)value);
    }
    read_fifo[slot] = value;
    read_count++;
    flags &= ~RXFE;
    if ((cr & 0x10) || (read_count == 16) || (!(lcr & FEN) && read_count >= 1)) {
        flags |= RXFF;
    }
    if (read_count >= read_trigger) {
        int_level |= RX;
        update();
    }
}

PPM_REG_READ_CB(readDR) {
//TODO: is this right??
//    flags &= ~TXFE;
    Uns32 c = read_fifo[read_pos];
    if (read_count > 0) {
        read_count--;
        if (++read_pos == 16)
            read_pos = 0;
    }
    if (read_count == 0) {
        flags |= RXFE;          // signal Rx Empty
        if (!(lcr & FEN) ) {
            flags &= ~RXFF;     // if Fifo not enabled clear Rx full
        }
    }
    if (read_count == read_trigger - 1)
        int_level &= ~RX;
    update();
    return c;
}

PPM_REG_READ_CB(readECR) {
    // const 0
    return 0;
}

PPM_REG_READ_CB(readID) {
    Uns32 offset = ((Uns32)user - (Uns32)&bport1_ab_data.id0.value)/sizeof(bport1_ab_data.id0.value);
    offset &= 7;
    return id[uType][offset];
}

PPM_REG_READ_CB(readMIS) {
    return int_level & int_enabled;
}

PPM_REG_WRITE_CB(writeDMA) {
    *(Uns32*)user = data;
    if (dmacr & 3)
        bhmMessage("E", "PL011_DNS", "DMA mode not supported");
}

PPM_REG_WRITE_CB(writeDR) {
    /* ??? Check if transmitter is enabled.  */
     Uns8 ch = data;
     chr_write(&ch, 1);

     int_level |= BPORT1_AB_INT_LEVEL_TX;
     update();
}

PPM_REG_WRITE_CB(writeICR) {
    int_level &= (~data) & 0xFF;
    update();
}

PPM_REG_WRITE_CB(writeIMSC) {
    int_enabled = data;
    update();
}

PPM_REG_WRITE_CB(writeIFL) {
    ifl = data;
    read_trigger = 1;
}

PPM_REG_WRITE_CB(writeLCR) {
    lcr = data;
    read_trigger = 1;
}

#define TOP (256 *1024)
Uns8 stack1[TOP];

//
// The polling process that gets characters
//
void getChars(void *user)
{
    while(1) {
        double d = DEFAULT_RX_DELAY;

        bhmWaitDelay(d);
        if (can_receive()) {
            Uns8 c;
            if (bhmSerRead(channel, &c, 1)) {
                bhmTriggerEvent(charReceived);
                receiveByte(c);
            }
        }
    }
}

void openFiles(void)
{
    channel = bhmSerOpenAuto();
}

void initialState() {
    // Set the initial state of registers
    if(DIAG_HIGH) {
        bhmMessage("I", "PL011_INIT", "Initialize registers");
    }

    // Set Transmit Fifo empty
    flags |= TXFE;
}

PPM_CONSTRUCTOR_CB(constructor) {
    uType = PL011_ARM;
    if(DIAG_HIGH) {
        bhmMessage("I", "PL011_CONSTRUCT", "Start Constructor");
    }

    char variant[128];

    if (bhmStringAttribute("variant", variant, sizeof(variant))) {
        if (strcmp(variant, "ARM") == 0) {
            uType = PL011_ARM;
        } else if (strcmp(variant, "LUMINARY") == 0) {
            uType = PL011_LUMINARY;
        } else {
            bhmMessage("F", "PL011_INV", "Invalid variant '%s'. Expected ARM or LUMINARY", variant);
        }
    }
    periphConstructor();
    openFiles();

    Bool charMode = bhmBoolAttribute("charmode");
    if (charMode) {
        if (DIAG_LOW) {
            bhmMessage("I", "PL011", "Asking client to run in Char Mode");
        }

        // IAC WILL ECHO IAC WILL SUPPRESS_GO_AHEAD IAC WONT LINEMODE
        // 255  251    1 255  251                 3 255  252       34
        Uns8 buffer[] = {255, 251, 1, 255, 251, 3, 255, 252, 34};
        Uns32 rc = bhmSerWrite(channel, buffer, 9);

        if (DIAG_LOW) {
            bhmMessage("I", "PL011", "Sent %d initialisation chars to socket", rc);
        }
    }

    read_trigger = 1;
    bhmCreateThread(getChars, NULL, "getchars", &stack1[TOP]);
    charReceived = bhmCreateNamedEvent("Rx", "Character received");
    charSent     = bhmCreateNamedEvent("Tx", "Character sent");

    // Set initial state of registers
    initialState();
}

PPM_DESTRUCTOR_CB(closeDown) {
    if(channel >= 0) {
        bhmSerClose(channel);
    }
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

