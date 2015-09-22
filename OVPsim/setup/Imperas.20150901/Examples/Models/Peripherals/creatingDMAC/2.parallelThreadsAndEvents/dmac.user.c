/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                          Wed Aug 18 10:59:44 2010
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "dmac.igen.h"

#define THREAD_STACK      (8*1024)
#define NUM_CHANNELS      2
#define BYTES_PER_ACCESS  8

// Give a 'nice' name to the default generated
#define controlRegs DMACSP_ab8_dataT
#define channelRegs DMACSP_ab32ch0_dataT

controlRegs *control;
channelRegs *ch[2];

typedef struct {
    bhmThreadHandle       thread;
    bhmEventHandle        start;
    Bool                  busy;
    char                  stack[THREAD_STACK];
} channelState;

typedef struct {
    ppmAddressSpaceHandle readHandle;
    ppmAddressSpaceHandle writeHandle;
    ppmNetHandle          intTCHandle;
    Bool                  intTCAsserted;
    Bool                  inReset;
    channelState          ch[NUM_CHANNELS];
} dmaState;

static dmaState DMAState;

static inline Uns32 byteSwap(Uns32 data){
#ifdef ENDIANBIG
    return
        ((data & 0xff000000) >> 24) |
        ((data & 0x00ff0000) >>  8) |
        ((data & 0x0000ff00) <<  8) |
        ((data & 0x000000ff) << 24);
#else
    return data;
#endif
}


static void writeAndStart(Uns8 channel, Uns32 data)
{
    ch[channel]->config.value = byteSwap(data);
    if(!ch[channel]->config.bits.halt && ch[channel]->config.bits.enable && !DMAState.ch[channel].busy) {
        bhmTriggerEvent(DMAState.ch[channel].start);
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(TCclearWr) {
    // YOUR CODE HERE (TCclearWr)
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(configCh0Wr) {
    writeAndStart(0, data);
}

PPM_REG_WRITE_CB(configCh1Wr) {
    writeAndStart(1, data);
}

PPM_REG_WRITE_CB(configWr) {
    control->config.value = byteSwap(data);
}

PPM_REG_WRITE_CB(errClearWr) {
    control->intErrStatus.value = 0;
}

PPM_REG_READ_CB(regRd32) {
    return byteSwap(*(Uns32*)user);
}

PPM_REG_READ_CB(regRd8) {
    return *(Uns8*)user;
}

PPM_REG_WRITE_CB(regWr32) {
    *(Uns32*)user =  byteSwap(data);
}

static void dmaBurst(Uns32 channel)
{
    // this is where the dma will happen.
}

//
// Thread for each channel
// When it starts, it runs to the first 'wait' which is in this case bhmWaitEvent()
//
static void channelThread(void *user)
{
    Uns32 ch = (Uns32) user;
    for (;;) {
        if (diagnosticLevel >= 2) bhmMessage("I", "DMAC", "ch %u waiting\n", ch);
        DMAState.ch[ch].busy = False;

        bhmWaitEvent(DMAState.ch[ch].start);
        {
            DMAState.ch[ch].busy = True;
            if (diagnosticLevel >= 2) bhmMessage("I", "DMAC", "ch %u running\n", ch);

            // Perform DMA burst
            dmaBurst(ch);

            control->rawTCstatus.value |= (1 << ch);
            if (diagnosticLevel >= 2) {
                bhmMessage("I", "DMAC",
                    "ch %u status=0x%x\n",
                    ch,
                    control->rawTCstatus.value
                );
            }
        }
    }
}

void userInit(void)
{
    Uns32 i;
    char threadName[32];

    control = (controlRegs *)&DMACSP_ab8_data;
    ch[0] = (channelRegs *)&DMACSP_ab32ch0_data;
    ch[1] = (channelRegs *)((void *)&DMACSP_ab32ch1_data);

    DMAState.intTCAsserted = False;

    // Create threads for the channels
    for (i=0; i<NUM_CHANNELS; i++) {

        // Event to start the thread
        DMAState.ch[i].start = bhmCreateEvent();
        DMAState.ch[i].busy  = False;

        // create the thread
        sprintf(threadName, "ch%u", i);
        DMAState.ch[i].thread = bhmCreateThread(
            channelThread,
            (void*) i,
            threadName,
            &DMAState.ch[i].stack[THREAD_STACK] // top of downward growing stack
        );PPM_SAVE_STATE_FN(peripheralSaveState) {
            // YOUR CODE HERE (peripheralSaveState)
        }

        PPM_RESTORE_STATE_FN(peripheralRestoreState) {
            // YOUR CODE HERE (peripheralRestoreState)
        }
    }
}


PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)
    userInit();
}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}
