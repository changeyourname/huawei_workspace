/*
 * TimerSP804
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

#include "peripheral/bhm.h"
#include "pse.igen.h"

#define BPORT1 0
#include "pse.macros.igen.h"

#define DIAG_1  (diagnosticLevel >= 1)
#define DIAG_2  (diagnosticLevel >= 2)
#define DIAG_3  (diagnosticLevel >= 3)

#define  STACK (1024 *32)

typedef struct timerDataS {
    Uns8            stack[STACK];
    char            *name;

    // user registers
    Uns32           control;
    Uns32           load;


    // intermediates
    Uns32           frequency;
    Uns32           actualFrequency;
    Uns32           limit;
    Uns32           status;

    Uns64           triggerCount;

    bhmThreadHandle threadHandle;   // this timer's thread
    Flt64           threadDelay;    // time this this thread runs again
    Flt64           threadStarted;  // bhm time when timer was started.
    bhmEventHandle  expired;        // user-view event

    struct {
        ppmNetHandle net;
        Bool         current;
    } irq;

} timerData, *timerDataP;

static timerData timers[3];

static const double factor = 1000000;

//
// Bring the output net up to date
//
static void updateIRQ(Uns8 timer)
{
    Bool v = True && (timers[timer].status &&  (timers[timer].control & BPORT1_AB_T0CONTROL_IE));

    if (DIAG_3)
        bhmMessage("I", "SP804", "IRQ=%d", v);

    if (timers[timer].irq.current != v) {
        timers[timer].irq.current  = v;
       // if(timers[timer].irq.net) {
            ppmWriteNet(handles.irq, v);
       // }
    }
}

//
// Thread runs forever unless one-shot mode
//
static void timerThread(void *user) {
    Uns32 t = (Uns32) user;

    do {
        timers[t].threadStarted = bhmGetCurrentTime();
        if (DIAG_3)
            bhmMessage("I", "SP804", "timer %d started at %0.0fuS with delay %0.0fuS", t, timers[t].threadStarted, timers[t].threadDelay);
        bhmWaitDelay(timers[t].threadDelay);
        bhmTriggerEvent(timers[t].expired);
        timers[t].status = 1;
        timers[t].triggerCount++;
        if (DIAG_1)
            bhmMessage("I", "SP804", "timer %d expired at %0.0fuS", t, bhmGetCurrentTime());
        updateIRQ(t);
    } while ((timers[t].control & BPORT1_AB_T0CONTROL_ONESHOT) == 0);

    if (DIAG_3)
        bhmMessage("I", "SP804", "timer %d thread exit", t);
}

//
// If thread is already active, kill it, then start a new one.
//
static void startThread(Uns32 t) {
    if (timers[t].threadHandle) {
        bhmDeleteThread(timers[t].threadHandle);
        timers[t].threadHandle = 0;
        if (DIAG_1)
            bhmMessage("I", "SP804", "Deleting thread %d\n", t);
    }

    if (DIAG_1)
        bhmMessage("I", "SP804", "Creating thread:%s delay:%0.0fuS", timers[t].name, timers[t].threadDelay);

    timers[t].threadHandle = bhmCreateThread(
        timerThread,
        (void*)t,
        timers[t].name,
        &(timers[t].stack[STACK-1])
    );
}

//
// reset the timer because something has been re-programmed
//
static void recalibrate(Uns8 t, Bool reload) {
    Uns32 limit;

    if ((timers[t].control & BPORT1_AB_T0CONTROL_PERIODIC) == 0) {
        /* Free running.  */
        if (timers[t].control & BPORT1_AB_T0CONTROL_M32BIT)
            limit = 0xffffffff;
        else
            limit = 0xffff;
    } else {
        /* Periodic.  */
        limit = timers[t].load;
    }
    double delay = (double) limit * factor / (double) timers[t].actualFrequency;
    timers[t].threadDelay = delay;

    if (timers[t].control & BPORT1_AB_T0CONTROL_ENABLE) {
        startThread(t);
    }
}

//
// Callbacks
//



PPM_REG_READ_CB(readPCellID0) {
    return 0x0D;
}

PPM_REG_READ_CB(readPCellID1) {
    return 0xF0;
}

PPM_REG_READ_CB(readPCellID2) {
    return 0x05;
}

PPM_REG_READ_CB(readPCellID3) {
    return 0xB1;
}

PPM_REG_READ_CB(readPeriphID0) {
    return 0x04;
}

PPM_REG_READ_CB(readPeriphID1) {
    return 0x18;
}

PPM_REG_READ_CB(readPeriphID2) {
    return 0x14;
}

PPM_REG_READ_CB(readPeriphID3) {
    return 0x0;
}


PPM_REG_READ_CB(readControl) {
    Uns8 timer = (Uns32)user;
    return timers[timer].control;
}

PPM_REG_READ_CB(readLoad) {
    Uns8 timer = (Uns32)user;
    return timers[timer].load;
}

PPM_REG_READ_CB(readMIS) {
    Uns8 timer = (Uns32)user;
    if (timers[timer].control & BPORT1_AB_T0CONTROL_IE)
        return timers[timer].status;
    else
        return 0;
}

PPM_REG_READ_CB(readRIS) {
    Uns8 timer = (Uns32)user;
    return timers[timer].status;
}

PPM_REG_READ_CB(readValue) {
    Uns8  t     = (Uns32)user;
    Flt64 now   = bhmGetCurrentTime();
    // TODO: Assume the simulation does not run long enough for bhmGetCurrentTime to wrap back to zero
    Flt64 diff  = now - timers[t].threadStarted;
    Uns32 res   = (timers[t].threadDelay - diff) * timers[t].actualFrequency / factor;
    if (DIAG_3)
        bhmMessage("I", "SP804", "readValue : timer %d: start %0.0fuS now %0.0fuS diff %0.0fuS : delay %0.0fuS : res 0x%08x",
                t, timers[t].threadStarted, now, diff, timers[t].threadDelay, res);

    return (Uns32)res;
}

PPM_REG_WRITE_CB(writeBGLoad) {
    Uns8 t = (Uns32)user;
    timers[t].load = data;

}

PPM_REG_WRITE_CB(writeControl) {
     Uns8 t = (Uns32)user;
    timers[t].control = data;
    Uns32 freq = timers[t].frequency;

    if (DIAG_3)
        bhmMessage("I", "SP804", "WriteControl %d: value = %d", t, data);

    switch ((data >> 2) & 3) {
        case 1: freq >>= 4; break;
        case 2: freq >>= 8; break;
    }
    timers[t].actualFrequency = freq;
    if (DIAG_1)
        bhmMessage("I", "SP804", "WriteControl %d: Actual freq = %d", t, freq);
    recalibrate(t, 0);

    updateIRQ(t); // TODO: is this needed?
}

PPM_REG_WRITE_CB(writeIntClr) {
    Uns8 timer = (Uns32)user;
    if (DIAG_3)
        bhmMessage("I", "SP804", "writeIntClr %d",timer);
    timers[timer].status = 0;
    updateIRQ(timer);
}

PPM_REG_WRITE_CB(writeLoad) {
     Uns8 t = (Uns32)user;
    timers[t].load = data;

    recalibrate(t, 1);
    updateIRQ(t);

    //timers[t].control = timers[t].control | BPORT1_AB_T0CONTROL_IE;
}



PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();



    timers[0].frequency  = 1000000;  // 1.0MHz
    timers[1].frequency  = 1000000;   // 1.0MHz


    timers[0].expired = bhmCreateNamedEvent("T0", "Timer0 has expired");
    timers[1].expired = bhmCreateNamedEvent("T1", "Timer1 has expired");


    timers[0].name = "t0";
    timers[1].name = "t1";

    timers[0].status = 0;
    timers[1].status = 0;


    int t;
    for(t = 0; t < 2; t++) {
        timers[t].control      = BPORT1_AB_T0CONTROL_IE;
        timers[t].triggerCount = 0;
    }
}

PPM_DESTRUCTOR_CB(destructor) {
    if (DIAG_1) {
        int t;
        for(t = 0; t < 2; t++) {
            bhmMessage("I", "SP804", "Timer %d  events:%lld", t, timers[t].triggerCount);
        }
    }
}



PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

