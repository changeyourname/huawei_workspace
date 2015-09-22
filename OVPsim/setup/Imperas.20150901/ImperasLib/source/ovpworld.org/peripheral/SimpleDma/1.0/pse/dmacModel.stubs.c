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

//  Peripheral DMAC

#include <stdio.h>
#include <string.h>

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"
#include "dmacModel.h"


#define THREAD_STACK	  (8*1024)
#define NUM_CHANNELS	  2
#define BYTES_PER_ACCESS  8

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

static void updateInterrupts(void);

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


//
// View any 32-bit register
//
PPM_VIEW_CB(viewReg32) {
    *(Uns32*)data = byteSwap(*(Uns32*)user);
}

//
// Read any 32-bit register
//
PPM_REG_READ_CB(regRd32) {
    return byteSwap(*(Uns32*)user);
}

//
// Update any 32-bit register (with no side effects)
//
PPM_REG_WRITE_CB(regWr32) {
    *(Uns32*)user =  byteSwap(data);
}

//
// View any 8-bit register
//
PPM_VIEW_CB(viewReg8) {
    *(Uns8*)data = *(Uns8*)user;
}

//
// Read any 8-bit register
//
PPM_REG_READ_CB(regRd8) {
    return *(Uns8*)user;
}

//
// any write will clear the TC register
//
PPM_REG_WRITE_CB(TCclearWr) {
    control.intTCstatus = 0;
}

//
// any write will clear the error register
//
PPM_REG_WRITE_CB(errClearWr) {
    control.errStatus = 0;
}

static void writeAndStart(Uns8 channel, Uns32 data)
{
    ch[channel].config.value = byteSwap(data);
    if(!ch[channel].config.bits.halt && ch[channel].config.bits.enable && !DMAState.ch[channel].busy) {
        bhmTriggerEvent(DMAState.ch[channel].start);
    }
    updateInterrupts();
}

PPM_REG_WRITE_CB(configWr) {
    control.config.value = data;
}
//
// write config reg channel 0
//
PPM_REG_WRITE_CB(configCh0Wr) {
    writeAndStart(0, data);
}

//
// write config reg channel 1
//
PPM_REG_WRITE_CB(configCh1Wr) {
    writeAndStart(1, data);
}

#define CH0_INT (1<<0)
#define CH1_INT (1<<1)

static void updateInterrupts(void)
{
	// Update intTCStatus from rawIntTCStatus
	Uns32 rawIntTCStatus = control.rawTCstatus;
	Uns32 intTCStatus = 0;

    if ((ch[0].config.bits.inten) && (rawIntTCStatus & CH0_INT)) {
        intTCStatus |= CH0_INT;
    }

    if ((ch[1].config.bits.inten) && (rawIntTCStatus & CH1_INT)) {
        intTCStatus |= CH1_INT;
    }
	control.intTCstatus = intTCStatus;

    // Update TC interrupt line
    if (DMAState.intTCHandle) {
		if (intTCStatus && !DMAState.intTCAsserted) {
			ppmWriteNet(DMAState.intTCHandle, 1);
			DMAState.intTCAsserted = True;
		} else if (!intTCStatus && DMAState.intTCAsserted) {
		    ppmWriteNet(DMAState.intTCHandle, 0);
		    DMAState.intTCAsserted = False;
		}
	}
}

static void dmaBurst(Uns32 channel)
{
	Uns32 bytes;
    Uns32 src;
    Uns32 dest;
    char buff[BYTES_PER_ACCESS];

	bytes = ch[channel].control.bits.transferSize;
    src   = ch[channel].srcAddr;
    dest  = ch[channel].dstAddr;
    Uns32 burst = 1 << control.config.bits.burstSize;

    if (diag >= 2) {
        bhmMessage("I", "DMAC",
            "ch %u burst %u %u bytes from %08x to %08x\n",
            channel, burst, bytes, src, dest
        );
    }
    while (bytes) {
        Uns32 thisAccess = (bytes > burst) ? burst : bytes;
        ppmReadAddressSpace (DMAState.readHandle,  src,  thisAccess, buff);
        ppmWriteAddressSpace(DMAState.writeHandle, dest, thisAccess, buff);
        src   += thisAccess;
        dest  += thisAccess;
        bytes -= thisAccess;
        if (diag >= 3) {
            bhmMessage("I", "DMAC",
                "ch %u access %u bytes from %08x to %08x\n",
                channel, thisAccess, src, dest
            );
        }
        ch[channel].srcAddr = src;
        ch[channel].dstAddr = dest;
        bhmWaitDelay(1);
    }
}

// Thread for each channel
static void channelThread(void *user)
{
    Uns32 ch = (Uns32) user;
    for (;;) {
		if (diag >= 2) bhmMessage("I", "DMAC", "ch %u waiting\n", ch);
		DMAState.ch[ch].busy = False;

		bhmWaitEvent(DMAState.ch[ch].start);
		//bhmWaitDelay(100);
        if (DMAState.inReset) {
            if (diag >= 2) bhmMessage("I", "DMAC", "In reset\n");
        } else {
    		DMAState.ch[ch].busy = True;
    		if (diag >= 2) bhmMessage("I", "DMAC", "ch %u running\n", ch);

    		// Perform DMA burst
    		dmaBurst(ch);

    		control.rawTCstatus |= (1 << ch);
            if (diag >= 2)
                bhmMessage("I", "DMAC",
                    "ch %u status=0x%x\n",
                    ch,
                    control.rawTCstatus
                );
    		updateInterrupts();
        }
    }
}

void userReset(Uns32 v) {
    memset(ch,       0, sizeof(ch));
    memset(&DMAState, 0, sizeof(DMAState));
    memset(&control,  0, sizeof(control));
    DMAState.inReset = v;
}

void userInit(void)
{
	Uns32 i;
	char threadName[32];

    if (diag >= 3)
        bhmMessage("I", "PP_STUBS","User initialization\n");

    // USER INITIALIZATION
    DMAState.readHandle = ppmOpenAddressSpace("MREAD");
    if(!DMAState.readHandle) {
        bhmMessage("F", "DMAC", "Failed to open read port\n");
        bhmFinish();
    }
    DMAState.writeHandle = ppmOpenAddressSpace("MWRITE");
    if(!DMAState.writeHandle) {
        bhmMessage("E", "DMAC", "Failed to open write port\n");
        bhmFinish();
    }

    DMAState.intTCHandle = ppmOpenNetPort("INTTC");
    DMAState.intTCAsserted = False;

    // Create threads for the channels
    for (i=0; i<NUM_CHANNELS; i++) {

    	// Event to start the thread
    	DMAState.ch[i].start = bhmCreateEvent();
    	DMAState.ch[i].busy = False;

    	sprintf(threadName, "ch%u", i);
    	DMAState.ch[i].thread = bhmCreateThread(
			channelThread,
			(void*) i,
			threadName,
			&DMAState.ch[i].stack[THREAD_STACK]	// top of downward growing stack
		);
    }

}


