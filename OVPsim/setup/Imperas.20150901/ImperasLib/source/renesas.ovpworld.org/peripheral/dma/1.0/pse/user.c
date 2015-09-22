/*
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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                              Version 99999999
//                          Tue Sep 23 14:04:23 2014
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#define DIAG_HIGH (diagnosticLevel >= 3)
#define DIAG_MED  (diagnosticLevel >= 2)
#define DIAG_LOW  (diagnosticLevel >= 1)

#define PREFIX "DMA"

#define THREAD_STACK         (8*1024)
#define NUM_CHANNELS          8
#define NUM_ADC_CHANNELS      2
#define MAX_BYTES_PER_ACCESS  8

#define ADCMA0_ADDRESS    0x0ffff22e
#define ADCMA1_ADDRESS    0x0ffff26e
#define MARBASE_ADDRESS   0x0fff0000

// Give a 'nice' name to the default generated
#define waitControlRegs DMAP0_abc_data
#define dmaByteRegs     DMAP1_abb_data
#define dmaWordRegs     DMAP1_abw_data

typedef struct {
    bhmThreadHandle       thread;
    bhmEventHandle        enable;
    bhmEventHandle        trigger;
    bhmEventHandle        transfer;
    Bool                  busy;
    Uns32                 srcAddr;
    Uns32                 tgtAddr;
    Uns32                 count;
    Bool                  incTgtAddr;
    Bool                  incSrcAddr;
    Bool                  incSize;
    char                  stack[THREAD_STACK];
} channelState;

typedef struct {
    ppmAddressSpaceHandle portHandle;
    ppmNetHandle          intHandle[NUM_CHANNELS];
    Uns32                 intAsserted[NUM_CHANNELS];
    channelState          ch[NUM_CHANNELS];
} dmaStateT, *dmaStateTP;

dmaStateT DMAState;

static void updateStatus(Uns32 ch)
{
    if (DIAG_MED) bhmMessage("I", PREFIX"_US", "Update status ch %d", ch);
    // set bit in status register to indicate transfer complete
    dmaByteRegs.DMASL.value |= (1 << ch);

    // Update interrupt line
    // Does writing/reading DMASL clear interrupt or pulse ok?
    if (DMAState.intHandle[ch]) {
            ppmWriteNet(DMAState.intHandle[ch], 1);
            if (DIAG_MED) bhmMessage("I", PREFIX"_INT", "Interrupt line ch %d asserted (pulse)",ch);
            ppmWriteNet(DMAState.intHandle[ch], 0);
            DMAState.intAsserted[ch] = False;
    } else {
        bhmMessage("W", PREFIX"_IF", "Interrupt line ch %d not connected",ch);
    }
}


static void resetCounts(Uns32 ch) {
    switch (ch) {
        case 0:
            // Channel 0
            // channel destination register
            DMAState.ch[ch].tgtAddr = dmaWordRegs.MAR0.value + MARBASE_ADDRESS;
            // channel count register
            DMAState.ch[ch].count   = dmaByteRegs.DTCR0.value;
            DMAState.ch[ch].srcAddr = ADCMA0_ADDRESS;
            break;
        case 1:
            // Channel 1
            // channel destination register
            DMAState.ch[ch].tgtAddr = dmaWordRegs.MAR1.value + MARBASE_ADDRESS;
            // channel count register
            DMAState.ch[ch].count   = dmaByteRegs.DTCR1.value;
            DMAState.ch[ch].srcAddr = ADCMA1_ADDRESS;
            break;
        default:
            bhmMessage("E", PREFIX"_CH", "Configured with unsupported ADC channel %u", ch);
            break;
        }
}
// Thread for each channel
static void channelADCThread(void *user)
{
    Uns32 ch = (Uns32) user;
    unsigned char buff[MAX_BYTES_PER_ACCESS];

    if (DIAG_LOW) bhmMessage("I", PREFIX"_CH", "Configure ch %u ADC%u", ch, ch);

    resetCounts(ch);

    // 0,1 : ADC to RAM MARn (16-bit)
    // 2,3 : RAM MARn to Timer S start address SARn (16-bit)
    // 4,5 : CSIB, CSIE, UARTC to RAM MARn (8-bit/16-bit)
    // 6,7 : RAM MARn to CSIB, CSIE, UARTC (8-bit/16-bit)
    for (;;) {
        // Check still enabled
        DMAState.ch[ch].busy = False;
        if (!(dmaByteRegs.DMAMCL.value & (1<<ch))) {
            if (DIAG_MED) bhmMessage("I", PREFIX, "ch %u waiting for enable", ch);

            bhmWaitEvent(DMAState.ch[ch].enable);

            resetCounts(ch); // reset counters

            DMAState.ch[ch].busy = True;
            if (DIAG_HIGH) bhmMessage("I", PREFIX, "ch %u enabled", ch);
        } else if (DMAState.ch[ch].count == 0) {
            if (DIAG_MED) bhmMessage("I", PREFIX, "ch %u waiting for transfer count", ch);
            bhmWaitEvent(DMAState.ch[ch].transfer);

            resetCounts(ch); // reset counters

        }
        // Perform DMA burst (access size set by register 8/16 bit)
        // burst bytes DMAState.ch[ch].DTCR
        // from I/O device (need address map in system)
        // to address in DMAState.ch[ch].MAR

        Uns32 src = DMAState.ch[ch].srcAddr;
        Uns32 thisAccess = 2;   // always 2 bytes transferred

        while (DMAState.ch[ch].count > 0) {
            if (DIAG_HIGH) bhmMessage("I", PREFIX, "ch %u wait trigger", ch);
            bhmWaitEvent(DMAState.ch[ch].trigger);
            if (DIAG_HIGH) {
                bhmMessage("I", PREFIX"_XFR",
                    "ch %u access %u bytes from 0x%08x to 0x%08x (count remaining %d)",
                    ch, thisAccess, src, DMAState.ch[ch].tgtAddr, DMAState.ch[ch].count
                );
            }
            // Transfer the data
            ppmReadAddressSpace (DMAState.portHandle,   src, thisAccess, buff);
            if(DIAG_HIGH) {
                Uns32 it;
                for (it=0;it<thisAccess;it++){
                    bhmMessage("I", PREFIX"_XFRD", "  buff[%d]=0x%02x", it, buff[it]);
                }
            }
            Bool bret = ppmWriteAddressSpace(DMAState.portHandle, DMAState.ch[ch].tgtAddr, thisAccess, buff);
            if(DIAG_LOW)
                bhmMessage("I", PREFIX"_XFRD2", "  buff[0-1]=%d 0x%02x   DMAState.ch[ch].tgtAddr=%d 0x%02x tgtaddr:0x%x ret:%d",
                                *(unsigned short*)buff, *(unsigned short*)buff,
                                *(unsigned char*)(DMAState.ch[ch].tgtAddr), *(unsigned char*)(DMAState.ch[ch].tgtAddr),
		       (DMAState.ch[ch].tgtAddr), bret);
            DMAState.ch[ch].tgtAddr  += thisAccess;
            DMAState.ch[ch].count -= 1;

            bhmWaitDelay(1);

            if (!(dmaByteRegs.DMAMCL.value & (1<<ch))) {
                // stop if the DMA channel is no longer enabled
                break;
            }
        }
        if (DIAG_MED) bhmMessage("I", PREFIX, "ch %u complete", ch);
        updateStatus(ch);
    }
}

void userInit(void)
{
    Uns32 i;
    char threadName[32];

    if (DIAG_HIGH)
        bhmMessage("I", PREFIX,"User initialization");

    DMAState.portHandle = handles.DMAPM;

    DMAState.intHandle[0] = handles.INTDMA0;
    DMAState.intHandle[1] = handles.INTDMA1;

    // Create threads for the ADC channels
    for (i=0; i<NUM_ADC_CHANNELS; i++) {

        // Event to start the thread
        DMAState.ch[i].enable = bhmCreateEvent();
        DMAState.ch[i].trigger = bhmCreateEvent();
        DMAState.ch[i].transfer = bhmCreateEvent();
        DMAState.ch[i].busy = False;

        sprintf(threadName, "adc-ch%u", i);
        DMAState.ch[i].thread = bhmCreateThread(
            channelADCThread,
            (void*) i,
            threadName,
            &DMAState.ch[i].stack[THREAD_STACK] // top of downward growing stack
        );
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(readDMADSCL) {
    // YOUR CODE HERE (readDMADSCL)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDMAMCL) {
    // YOUR CODE HERE (readDMAMCL)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDMASL) {
    // YOUR CODE HERE (readDMASL)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDMAWC0) {
    // YOUR CODE HERE (readDMAWC0)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readDMAWC1) {
    // YOUR CODE HERE (readDMAWC1)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readDTCR0) {
    // YOUR CODE HERE (readDTCR0)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTCR1) {
    // YOUR CODE HERE (readDTCR1)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTCR2) {
    // YOUR CODE HERE (readDTCR2)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTCR3) {
    // YOUR CODE HERE (readDTCR3)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTCR4) {
    // YOUR CODE HERE (readDTCR4)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTCR5) {
    // YOUR CODE HERE (readDTCR5)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTCR6) {
    // YOUR CODE HERE (readDTCR6)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTCR7) {
    // YOUR CODE HERE (readDTCR7)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTCR8) {
    // YOUR CODE HERE (readDTCR8)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTCR9) {
    // YOUR CODE HERE (readDTCR9)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTFR4) {
    // YOUR CODE HERE (readDTFR4)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTFR5) {
    // YOUR CODE HERE (readDTFR5)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTFR6) {
    // YOUR CODE HERE (readDTFR6)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDTFR7) {
    // YOUR CODE HERE (readDTFR7)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readMAR0) {
    // YOUR CODE HERE (readMAR0)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readMAR1) {
    // YOUR CODE HERE (readMAR1)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readMAR2) {
    // YOUR CODE HERE (readMAR2)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readMAR3) {
    // YOUR CODE HERE (readMAR3)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readMAR4) {
    // YOUR CODE HERE (readMAR4)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readMAR5) {
    // YOUR CODE HERE (readMAR5)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readMAR6) {
    // YOUR CODE HERE (readMAR6)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readMAR7) {
    // YOUR CODE HERE (readMAR7)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readMAR8) {
    // YOUR CODE HERE (readMAR8)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readMAR9) {
    // YOUR CODE HERE (readMAR9)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readSAR2) {
    // YOUR CODE HERE (readSAR2)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readSAR3) {
    // YOUR CODE HERE (readSAR3)
    return *(Uns8*)user;
}

PPM_NET_CB(triggerADDMARQ0) {
    if(value) {
        if (DIAG_HIGH) bhmMessage("I", PREFIX"_ADDMARQ0", "Trigger ADC0 (%d)", value);
        bhmTriggerEvent(DMAState.ch[0].trigger);
    }
}

PPM_NET_CB(triggerADDMARQ1) {
    if(value) {
        if (DIAG_HIGH) bhmMessage("I", PREFIX"_ADDMARQ1", "Trigger ADC1 (%d)", value);
        bhmTriggerEvent(DMAState.ch[1].trigger);
    }
}

PPM_NET_CB(triggerINTBE0R) {
    if (DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTBE0R Not Implemented (%d)", value);
}

PPM_NET_CB(triggerINTBE1R) {
    if (DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTBE1R Not Implemented (%d)", value);
}

PPM_NET_CB(triggerINTCE0C) {
    if (DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTCE0C Not Implemented (%d)", value);
}

PPM_NET_CB(triggerINTCE1C) {
    if (DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTCE1C Not Implemented (%d)", value);
}

PPM_NET_CB(triggerINTTS0CD) {
    if (DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTTS0CD Not Implemented (%d)", value);
}

PPM_NET_CB(triggerINTTS1CD) {
    if (DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTTS1CD Not Implemented (%d)", value);
}

PPM_NET_CB(triggerINTUC0R) {
    if (DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTUC0R Not Implemented (%d)", value);
}

PPM_NET_CB(triggerINTUC1R) {
    if (DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTUC1R Not Implemented (%d)", value);
}

PPM_NET_CB(triggerINTUC2R) {
    if (DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTUC2R Not Implemented (%d)", value);
}

PPM_REG_WRITE_CB(writeDMADSCL) {
    // YOUR CODE HERE (writeDMADSCL)
    if (DIAG_LOW)
        bhmMessage("W", PREFIX"_DMADSCLW", "No Behaviour Implemented");

    *(Uns8*)user = (*(Uns8*)user & 0xf) | (data & 0xf0);
}

//
// Only write when a value change occurs
//
static void setADCDMAEnable(Uns32 ch, Uns32 value) {
    if ((ch==0)||(ch==1)) {
        ppmNetHandle denNet = (ch == 0) ? handles.DMA0EN : handles.DMA1EN;

        Uns32 current = ppmReadNet(denNet);
        if (DIAG_MED)
            bhmMessage("I", PREFIX"_DMAEN", "Channel %d (%d) : Set DMAEN %d", ch, current, value);
        if (value != current) {
            ppmWriteNet(denNet, value);
        }
    }
}

PPM_REG_WRITE_CB(writeDMAMCL) {
    // YOUR CODE HERE (writeDMAMCL)
    // Can only change inactive channels
    Uns8 i;
    Uns16 mask = 0;
    Uns8 current = *(Uns8*)user;

    // Only inactive channels can be changed
    for (i=0;i<NUM_CHANNELS;i++) {
        if (!DMAState.ch[i].busy) {
            mask |= 1<<i;
        }
    }
    Uns8 new = data & mask;
    if (DIAG_LOW)
        bhmMessage("I", PREFIX"_DMAMCL", "Channel Mode Control update 0x%02x mask 0x%02x dmamcl 0x%02x->0x%02x", data, mask, current,new);

    *(Uns8*)user = new;
    // If the channel has gone from disabled to enabled we need to start the DMA
    // TODO: channels started in priority order?
    for (i=0;i<NUM_CHANNELS;i++) {
        if (!(current & (1<<i)) && (new & (1<<i))) {
            if (DIAG_HIGH)
                bhmMessage("I", PREFIX"_DMAEN", "Channel %d Enabled", i);
            setADCDMAEnable(i, 1);
            bhmTriggerEvent(DMAState.ch[i].enable);
        } else if (!(new & (1<<i))) {
           setADCDMAEnable(i, 0);
        }
    }
}

PPM_REG_WRITE_CB(writeDMASL) {
    // YOUR CODE HERE (writeDMASL)
    Uns8 current = *(Uns8*)user;
    // Can only clear (not set)
    current ^= data & 0xff;
    if (DIAG_HIGH)
        bhmMessage("I", PREFIX"_DMASLW", "DMASL write 0x%02x, value 0x%02x->0x%02x", data, *(Uns8*)user, current);
    *(Uns8*)user = current;
}

PPM_REG_WRITE_CB(writeDMAWC0) {
    // YOUR CODE HERE (writeDMAWC0)
    if (DIAG_HIGH)
        bhmMessage("W", PREFIX"_DMAWC0W", "No Behaviour Implemented");
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDMAWC1) {
    // YOUR CODE HERE (writeDMAWC1)
    if (DIAG_HIGH)
        bhmMessage("W", PREFIX"_DMAWC1W", "No Behaviour Implemented");
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTCR0) {
    *(Uns8*)user = data;
    if (data) {
        if (DIAG_HIGH)
            bhmMessage("I", PREFIX"_DTCR0", "Set Count %d", data);
        bhmTriggerEvent(DMAState.ch[0].transfer);
    }
}

PPM_REG_WRITE_CB(writeDTCR1) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTCR2) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTCR3) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTCR4) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTCR5) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTCR6) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTCR7) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTCR8) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTCR9) {
    // YOUR CODE HERE (writeDTCR9)
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTFR4) {
    // YOUR CODE HERE (writeDTFR4)
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTFR5) {
    // YOUR CODE HERE (writeDTFR5)
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTFR6) {
    // YOUR CODE HERE (writeDTFR6)
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTFR7) {
    // YOUR CODE HERE (writeDTFR7)
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeMAR0) {
    if(data) {
        if (DIAG_HIGH) bhmMessage("I", PREFIX"_MAR0", "Target address written (0x%04x)", data);
    }
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeMAR1) {
    // YOUR CODE HERE (writeMAR1)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeMAR2) {
    // YOUR CODE HERE (writeMAR2)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeMAR3) {
    // YOUR CODE HERE (writeMAR3)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeMAR4) {
    // YOUR CODE HERE (writeMAR4)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeMAR5) {
    // YOUR CODE HERE (writeMAR5)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeMAR6) {
    // YOUR CODE HERE (writeMAR6)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeMAR7) {
    // YOUR CODE HERE (writeMAR7)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeMAR8) {
    // YOUR CODE HERE (writeMAR8)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeMAR9) {
    // YOUR CODE HERE (writeMAR9)
    *(Uns16*)user = data;
}

PPM_REG_WRITE_CB(writeSAR2) {
    // YOUR CODE HERE (writeSAR2)
    if (DIAG_HIGH)
        bhmMessage("W", PREFIX"_SAR2W", "No Behaviour Implemented");
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);
}

PPM_REG_WRITE_CB(writeSAR3) {
    // YOUR CODE HERE (writeSAR3)
    if (DIAG_HIGH)
        bhmMessage("W", PREFIX"_SAR3W", "No Behaviour Implemented");
    *(Uns8*)user = (*(Uns8*)user & 0xf0) | (data & 0xf);
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    userInit();

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

