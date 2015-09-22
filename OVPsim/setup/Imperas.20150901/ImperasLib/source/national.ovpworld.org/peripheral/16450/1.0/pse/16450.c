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

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include "peripheral/impTypes.h"
#include "peripheral/ppm.h"
#include "peripheral/bhm.h"

#include "constants.h"

#define BUFFERLENGTH 16
#define DEBUG 0
#define PREFIX "16450"

//define no inline attribute for intercepted functions
#define NOINLINE  __attribute__((noinline))

#define DIAG_LOW             ((device.diag & 0xf) > 0)
#define DIAG_MED             ((device.diag & 0xf) > 1)
#define DIAG_HIGH            ((device.diag & 0xf) > 2)

#define REG_8BIT_BOUNDARY    1
#define REG_16BIT_BOUNDARY   2
#define REG_32BIT_BOUNDARY   4
#define REG_64BIT_BOUNDARY   8
#define MAX_BOUNDARY         REG_64BIT_BOUNDARY

#define WINDOW               8

#define CRYSTAL              18432000
#define PRESCALE             (8 * 2)

#define DEFAULT_BAUD         9

#define DEFAULT_RX_DELAY     20000

//
// All device statics are contained in this structure. Although there is no
// need to do this (file statics and program globals will work just as well in
// a PSE) this style makes it easy to locate the model's state and adds zero
// overhead to its execution.
//
typedef struct uart16450S {
    Uns32 registerAlign;         // default alignment on byte boundary

    // diagnostic level
    Int32    diag;

    // interrupt
    ppmNetHandle    intPortHandle;
    Bool            intState;

    // user events
    bhmEventHandle  gotChar;
    bhmEventHandle  sentChar;
    bhmEventHandle  txChar;
    bhmEventHandle  overrun;
    bhmEventHandle  interrupt;

    // duplex channel connection
    Int32    channel;

    // true means write to the simulator log
    Bool     log;

    // UART model state
    Uns16 divider;
    Uns8  rbr; /* receive register */
    Uns8  tbr; /* tx register */
    Uns8  ier;
    Uns8  iir; /* read only */
    Uns8  lcr;
    Uns8  mcr;
    Uns8  lsr; /* read only */
    Uns8  msr; /* read only */
    Uns8  scr;
    /* NOTE: this hidden state is necessary for tx irq generation as
       it can be reset while reading iir */
    Int32 thr_ipending;
    Int32 last_break_enable;

    Bool  uart16550;        // not used yet
    Bool  simulateBaud;     // delay tx characters, rather than sending immediately
    Bool  charMode;         // Ask client to run in character mode
    Bool  writeError;       // An error has occurred on most recent write
    Uns32 usec_delay;       // time between characters

} uart16450;

//
// Statics
//
static  uart16450 device;  // only one uart, but could support several

////////////////////////////////// RECORD / REPLAY ////////////////////////////////////

//
// extract register bits and calculate baud rate
//
static inline Uns32 data_bits   (void) { return (device.lcr & 0x03) + 5;     }
static inline Uns32 parity_bits (void) { return (device.lcr & 0x08) != 0;    }
static inline Uns32 parity_sense(void) { return (device.lcr & 0x10) != 0;    }
static inline Uns32 stop_bits   (void) { return (device.lcr & 0x04) ? 2 : 1; }
static inline Uns32 start_bits  (void) { return 1;                           }

static inline Uns32 baud_rate   (void) { return CRYSTAL / ((device.divider ?: 1)  * PRESCALE); }

static inline char  parity      (void) { return parity_bits() ? (parity_sense() ? 'E' : 'O') : 'N'; }

static inline Uns32 bits(void) {
    return start_bits() + data_bits() + parity_bits() + stop_bits();
}


static inline Uns32 microseconds_per_char(void) {
    return (bits() * 1000000) /  baud_rate();
}

static void serial_update_parameters(void)
{
    device.usec_delay = microseconds_per_char();
    if (DIAG_MED) {
        bhmMessage("I", PREFIX, "speed=%d  parity=%c  data bits=%d  total bits=%d\n",
           baud_rate(),
           parity(),
           data_bits(),
           bits()
        );
        bhmMessage("I", PREFIX, "character delay=%dusec\n", device.usec_delay);
    }
}

static NOINLINE void updateNet(Bool set){
    if(DIAG_MED)
        bhmMessage("I", PREFIX, "interrupt=%d", set);
    ppmWriteNet(device.intPortHandle, set);
}

//
// propagate the interrupt
//
static void setInt(Bool set)
{
    if(device.intPortHandle && set != device.intState){
        device.intState = set;
        updateNet(set);
        if (set) {
            if (DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Trigger device.interrupt");
            }
            bhmTriggerEvent(device.interrupt);
        }
    }
}

static void serial_update_irq(void)
{
    if ((device.lsr & UART_LSR_DR) && (device.ier & UART_IER_RDI)) {
        device.iir = UART_IIR_RDI;
    } else if (device.thr_ipending && (device.ier & UART_IER_THRI)) {
        device.iir = UART_IIR_THRI;
    } else {
        device.iir = UART_IIR_NO_INT;
    }
    if (DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Update interrupts (%s) IIR 0x%x (IER 0x%x) - Int State %s",
                (device.iir == UART_IIR_NO_INT) ? "-": "INT",
                device.iir,
                device.ier,
                ((device.intPortHandle) ? ((ppmReadNet(device.intPortHandle) != 0) ? "SET": "CLEAR") : "-"));
    }
    if (device.iir != UART_IIR_NO_INT) {
        setInt(1);
    } else {
        setInt(0);
    }
}

void overrun(void)
{
    device.lsr |= UART_LSR_OE;
    if (DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Trigger device.overrun");
    }
    bhmTriggerEvent(device.overrun);
}

void receiveByte(Int32 ch)
{
    if (DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Receive Data Byte '%c'", ch);
    }
    device.rbr = ch;
    if (device.lsr & UART_LSR_DR) {
        overrun();
    }
    device.lsr |= UART_LSR_DR;
    serial_update_irq();
}

static void uartReset (void)
{
    if (DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Reset");
    }
    device.lsr = UART_LSR_TEMT | UART_LSR_THRE;
    device.iir = UART_IIR_NO_INT;
    device.msr = UART_MSR_DCD | UART_MSR_DSR | UART_MSR_CTS;
}

static void openFiles(void)
{
    device.channel = bhmSerOpenAuto();
}

static Uns32 writeOutput(Uns8 *buffer, Uns32 length)
{
    Uns32 rc = 0;

    if (device.channel >= 0) {

        rc = bhmSerWriteN(device.channel, buffer, length);

        if (rc != length) {
            if (!device.writeError) {
                bhmMessage("W", PREFIX, "Serial channel write error. Channel closed?");
                device.writeError = True;
            }
        } else {
            device.writeError = False;
        }
    }

    return rc;
}

#define TOP (256 *1024)
Uns8 stack1[TOP];
Uns8 stack2[TOP];

//
// The polling process that gets characters at the specified baud-rate
//
#define MAXREAD 256
static void getChars(void *user)
{

    while(1) {
        Uns8  buffer[MAXREAD];
        Int32 bytes;

        double d = device.simulateBaud
            ? device.usec_delay
            : DEFAULT_RX_DELAY;

        //
        // Blocking read
        //
        bytes = bhmSerReadB(device.channel, buffer, MAXREAD);

        //
        // Do not allow overruns
        //
        if (device.charMode && (device.lsr & UART_LSR_DR)) {
            continue;
        }

        Uns32 i;
        for(i=0; i<bytes; i++) {
            bhmWaitDelay(d);
            Uns8 c = buffer[i];

            if (DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Get Character Input '%c'", c);
            }

            // If Character Mode strip Null characters
            // charMode c :: ignore
            //    0     0 :: False
            //    0     1 :: False
            //    1     0 :: True
            //    1     1 :: False
            if (device.charMode && (c==0)) {
            } else {
                bhmTriggerEvent(device.gotChar);
                receiveByte(c);
            }
        }
    }
}

//
// Used by either the register callback (if not simulating timing)
// Or by the putchars task if (simulating timing).
// Completes the transmit character operation.
//
static void transmitByte() {

    writeOutput(&(device.tbr), 1);

    device.thr_ipending = 1;
    device.lsr |= UART_LSR_THRE;
    device.lsr |= UART_LSR_TEMT;

    bhmTriggerEvent(device.sentChar);

    serial_update_irq();
}

//
// Process that delays the transmission of each character.
//
static void putChars(void *user)
{
    while(1) {
        bhmWaitEvent(device.txChar);
        if (device.usec_delay > 0) {
            bhmWaitDelay(device.usec_delay);
        }
        transmitByte();
    }
}

///////////////////////////////////////////////////////////////////////////////
// VIEW
///////////////////////////////////////////////////////////////////////////////

static PPM_VIEW_CB(viewReg8) {
    *(Uns8*)data = *(Uns8*)user;
}

static PPM_VIEW_CB(viewReg16) {
    *(Uns16*)data = *(Uns16*)user;
}

///////////////////////////////////////////////////////////////////////////////
// READ
///////////////////////////////////////////////////////////////////////////////

static PPM_REG_READ_CB(readRbr) {
    Uns8 ret;
    if (device.lcr & UART_LCR_DLAB) {
        ret = device.divider & 0xff;
    } else {
        ret = device.rbr;
        device.lsr &= ~(UART_LSR_DR | UART_LSR_BI);
        serial_update_irq();
    }
    return ret;
}

static PPM_REG_READ_CB(readIer) {
    Uns8 ret;
    if (device.lcr & UART_LCR_DLAB) {
        ret = (device.divider >> 8) & 0xff;
    } else {
        ret = device.ier;
    }
    return ret;
}

static PPM_REG_READ_CB(readIir) {
    Uns8 ret = device.iir;
    /* reset THR pending bit */
    if ((ret & 0x7) == UART_IIR_THRI)
        device.thr_ipending = 0;
    serial_update_irq();
    return ret;
}

static PPM_REG_READ_CB(readMsr) {
    Uns8 ret;
    if (device.mcr & UART_MCR_LOOP) {
        /* in loopback, the modem output pins are connected to the inputs */
        ret = (device.mcr & 0x0c) << 4;
        ret |= (device.mcr & 0x02) << 3;
        ret |= (device.mcr & 0x01) << 5;
    } else {
        ret = device.msr;
    }
    return ret;
}

static PPM_REG_READ_CB(readReg) {
    return *(Uns8*)user;
}

///////////////////////////////////////////////////////////////////////////////
// WRITE
///////////////////////////////////////////////////////////////////////////////

static PPM_REG_WRITE_CB(writeTbr) {
    if (device.lcr & UART_LCR_DLAB) {
        device.divider = (device.divider & 0xff00) | data;
        serial_update_parameters();
    } else {
        if (!device.thr_ipending) {
            // detecting tx overrun is more complicated than this.
            // overrun();
        }
        device.thr_ipending = 0;
        device.lsr &= ~UART_LSR_THRE;
        serial_update_irq();

        device.tbr = data;
        if (device.simulateBaud) {
            bhmTriggerEvent(device.txChar);
        } else {
            transmitByte();
        }
    }
}

static PPM_REG_WRITE_CB(writeIer) {
    if (device.lcr & UART_LCR_DLAB) {
        device.divider = (device.divider & 0x00ff) | (data << 8);
        serial_update_parameters();
    } else {
        device.ier = data & 0x0f;
        if (device.lsr & UART_LSR_THRE) {
            device.thr_ipending = 1;
        }
        serial_update_irq();
    }
}

static PPM_REG_WRITE_CB(writeMcr) {
    device.mcr = data & 0x1f;
}

static PPM_REG_WRITE_CB(writeScr) {
    device.scr = data;
}

static PPM_REG_WRITE_CB(writeLcr) {
    Int32 break_enable;
    device.lcr = data;
    serial_update_parameters();
    break_enable = (data >> 6) & 1;
    if (break_enable != device.last_break_enable) {
        device.last_break_enable = break_enable;
    }
}

//
// UART has 2 addressing schemes: byte-wise and word-wise
//
static Uns32 winAddr(Uns8 base) {
    return base * device.registerAlign;
}

static void createRegisters(void) {
    Uns32 windowSize = WINDOW * device.registerAlign;

    void *w = ppmCreateSlaveBusPort("bport1", windowSize);
    //                name    description        base offset size read    write      view      user data
    ppmCreateRegister("rbr", "receive byte",     w, winAddr(0), 1, readRbr, NULL,     viewReg8, &device.rbr, True);
    ppmCreateRegister("tbr", "transmit byte",    w, winAddr(0), 1, NULL,    writeTbr, NULL,     NULL,        True);
    ppmCreateRegister("ier", "interrupt enable", w, winAddr(1), 1, readIer, writeIer, viewReg8, &device.ier, True);
    ppmCreateRegister("iir", "interrupt input",  w, winAddr(2), 1, readIir, NULL,     viewReg8, &device.iir, True);
    ppmCreateRegister("lcr", "line control",     w, winAddr(3), 1, readReg, writeLcr, viewReg8, &device.lcr, True);
    ppmCreateRegister("mcr", "modem control",    w, winAddr(4), 1, readReg, writeMcr, viewReg8, &device.mcr, True);
    ppmCreateRegister("lsr", "line status",      w, winAddr(5), 1, readReg, NULL,     viewReg8, &device.lsr, True);
    ppmCreateRegister("msr", "modem status",     w, winAddr(6), 1, readMsr, NULL,     viewReg8, &device.msr, True);
    ppmCreateRegister("scr", "status/control",   w, winAddr(7), 1, readReg, writeScr, viewReg8, &device.scr, True);
    ppmCreateInternalRegister("div", "baud rate divider", 2, viewReg16, &device.divider);
}

//
// Set the local diag level
//
static void setDiagLevel(Uns32 d)
{
    device.diag = d;
}

int main(int argc, char **argv)
{
    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Model of 16550/16450 UART.");
        ppmDocAddText(doc_12_node, "Connects to a bus by a slave port and optionally to a processor by an interrupt signal.");
		ppmDocAddText(doc_12_node, "The serial input/output ports are modelled by socket connection which must be attached to a"
				                   "process outside the simulation environment. Note that on start:up, the UART model will block"
				                   "the simulator, pending a connection to the socket.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Simplified baud:rate.");
		ppmDocAddText(doc_22_node, "No modem support (DTR etc).");
		ppmDocAddText(doc_22_node, "No support for parity.");
		ppmDocAddText(doc_22_node, "No means to simulate errors.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Based upon 16450 features of http://www.ti.com/lit/ds/symlink/pc16550d.pdf");
    }

	bhmInstallDiagCB(setDiagLevel);
    device.txChar        = bhmCreateNamedEvent("txChar",    "About to transmit");
    device.sentChar      = bhmCreateNamedEvent("charOut",   "Uart character output event");
    device.overrun       = bhmCreateNamedEvent("overrun",   "Transmit or Receive overrun");
    device.interrupt     = bhmCreateNamedEvent("interrupt", "Interrupt generated");
    device.gotChar       = bhmCreateNamedEvent("charIn",    "Uart character input event");
    Uns32 defaultBaud    = DEFAULT_BAUD;
    if (bhmIntegerAttribute("defaultbaud", &defaultBaud)) {
        if (DIAG_LOW) {
            bhmMessage("I", PREFIX, "Default Baud, changed from %d to %d.",
                                               DEFAULT_BAUD, defaultBaud);
        }
    }
    device.divider       = defaultBaud;
    serial_update_parameters();

    openFiles();
    uartReset();

    device.registerAlign = REG_8BIT_BOUNDARY; // Set default to byte boundary;

    if ((device.simulateBaud = bhmBoolAttribute("simulatebaud"))) {
        if (DIAG_LOW) {
            bhmMessage("I", PREFIX, "Simulating transmission delays.");
        }
    }

    if ((device.uart16550 = bhmBoolAttribute("uart16550"))) {
        if (DIAG_LOW) {
            bhmMessage("I", PREFIX, "Simulating 16550A Fifos.");
        }
    }

    Bool charMode  = bhmBoolAttribute("charmode");
    if (charMode) {
        if (DIAG_LOW) {
            bhmMessage("I", PREFIX, "Asking client to run in Char Mode");
        }
        device.charMode = 1;

        // IAC WILL ECHO IAC WILL SUPPRESS_GO_AHEAD IAC WONT LINEMODE
        // 255  251    1 255  251                 3 255  252       34
        Uns8 buffer[] = {255, 251, 1, 255, 251, 3, 255, 252, 34};
        Uns32 rc = bhmSerWriteN(device.channel, buffer, 9);
        bhmMessage("I", PREFIX, "Sent %d initialisation chars to socket", rc);
    }

    device.intPortHandle = ppmOpenNetPort("intOut");
    if(!device.intPortHandle && DIAG_MED) {
        bhmMessage("W", PREFIX, "Net Port intOut not Opened\n");
    }
    createRegisters();

    // create the thread which causes characters to come in.
    bhmCreateThread(getChars, NULL, "getchars", &stack1[TOP]);
    if (device.simulateBaud) {
        bhmCreateThread(putChars, NULL, "putchars", &stack2[TOP]);
    }

    // now sit and wait for things to happen
    if(DIAG_LOW) bhmMessage("I", PREFIX, "main done\n");
    bhmEventHandle endSimulation = bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION);
    bhmWaitEvent(endSimulation);

    if(device.channel >= 0) {
        bhmSerClose(device.channel);
    }

    return 0;
}
