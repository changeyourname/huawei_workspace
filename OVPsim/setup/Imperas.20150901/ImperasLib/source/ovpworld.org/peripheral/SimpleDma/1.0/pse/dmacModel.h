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

#ifndef _DMAC_H
#define _DMAC_H

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"

typedef struct controlS {

     Uns8 intStatus;
     Uns8 intTCstatus;
     Uns8 errStatus;
     Uns8 rawTCstatus;
     Uns8 rawErrorStatus;
     Uns8 enbldChns;
     union {
         Uns8 value;
         struct {
             unsigned burstSize : 2;
             unsigned __pad1    : 6;
         } bits;
     } config;

} controlRegs, *controlRegsP;

typedef struct channelS {
    Uns32 srcAddr;
    Uns32 dstAddr;
    Uns32 LLI;            // not used
    union {
        Uns32 value;
        struct {
            unsigned transferSize : 12;
        } bits;
    } control;
    union {
        Uns32 value;
        struct {
            unsigned enable : 1;
            unsigned __pad1 : 14;
            unsigned inten : 1;
            unsigned __pad16 : 2;
            unsigned halt : 1;
        } bits;
    } config;
} channelRegs, *channelRegsP;


// Net callbacks

void userInit(void);

void userMainLoop(void);
void userReset(Uns32 v);

// Bus and net port declarations
extern ppmNetHandle      INTR_handle;
extern ppmNetHandle      INTTC_handle;
extern ppmLocalBusHandle DMACSP_handle;

extern Uns32 diag;

extern channelRegs ch[2];

extern controlRegs control;

//
// prototypes
//
PPM_VIEW_CB(viewReg32);
PPM_REG_READ_CB(regRd32);
PPM_REG_WRITE_CB(regWr32);
PPM_VIEW_CB(viewReg8);
PPM_REG_READ_CB(regRd8);
PPM_REG_WRITE_CB(TCclearWr);
PPM_REG_WRITE_CB(errClearWr);
PPM_REG_WRITE_CB(configWr);
PPM_REG_WRITE_CB(configCh0Wr);
PPM_REG_WRITE_CB(configCh1Wr);

#endif
