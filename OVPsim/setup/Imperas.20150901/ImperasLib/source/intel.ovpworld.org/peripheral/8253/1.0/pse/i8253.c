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
//                          Tue Feb  8 12:12:21 2011
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

#define PREFIX "I8253"

typedef struct counterS {
    union {
       Uns16 value;
       struct {
           unsigned lo : 8;
           unsigned hi : 8;
       } bits;
    } COUNT;
    Uns8 mode;
    Uns8 bcd;
    Uns8 read, write;
} counterT, *counterP;

counterT counter[3];

PPM_REG_READ_CB(readCNTL) {
    // if(BHM_DIAG_HIGH)
    bhmMessage("F", PREFIX, "Read Control Unsupported\n");
    return *(Uns8*)user;
}

PPM_REG_WRITE_CB(writeCNTL) {
    *(Uns8*)user = data;

    if(BHM_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Write Control %f SC=%x RW=%x M=%x BCD=%x\n",
                bhmGetCurrentTime(),
                bport1_reg_data.CNTL.bits.SC, bport1_reg_data.CNTL.bits.RW,
                bport1_reg_data.CNTL.bits.M, bport1_reg_data.CNTL.bits.BCD);
    }

    Uns8 select = bport1_reg_data.CNTL.bits.SC;
    Uns8 mode   = bport1_reg_data.CNTL.bits.M;
    Uns8 bcd    = bport1_reg_data.CNTL.bits.BCD;
    Uns8 rw     = bport1_reg_data.CNTL.bits.RW;

    ppmNetHandle outP = NULL;

    switch (select) {
    case 0:
        outP = handles.out0;
        counter[select].mode = mode;
        counter[select].bcd  = bcd;
        break;
    case 1:
        outP = handles.out1;
        counter[select].mode = mode;
        counter[select].bcd  = bcd;
        break;
    case 2:
        outP = handles.out2;
        counter[select].mode = mode;
        counter[select].bcd  = bcd;
        break;
    case 3:
        bhmMessage("F", PREFIX, "Read BackCommand\n");
        break;
    }

    switch (mode) {
    case 0:
        // Output is initially low
        if (outP) ppmWriteNet(outP, 0);
        if(BHM_DIAG_HIGH) bhmMessage("I", PREFIX, "Mode 0\n");

    case 2:
        // Output is initially high
        if (outP) ppmWriteNet(outP, 1);
        if(BHM_DIAG_HIGH) bhmMessage("I", PREFIX, "Mode 2\n");
        break;

    default:
        bhmMessage("F", PREFIX, "Mode %d Unsupported\n", mode);
        break;
    }

    counter[select].read  = rw;
    counter[select].write = rw;

}

PPM_REG_READ_CB(readCTR0) {
    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Read Counter0 %f addr=%p bytes=%d user=%p\n", bhmGetCurrentTime(), addr, bytes, user);

    bhmMessage("F", PREFIX, "Unsupported Read from CTR0\n");
    return *(Uns8*)user;
}

void updateCounterWrite (counterP cP, Uns8 data) {
    switch (cP->write) {
    case 0:
        cP->write = -1;
        bhmMessage("F", PREFIX, "Unsupported Write latch\n");

    case 1: // lo
        cP->COUNT.bits.lo = data;
        cP->write = -1;

    case 2: // hi
        cP->COUNT.bits.hi = data;
        cP->write = -1;
        break;

    case 3: // lo, then hi
        cP->COUNT.bits.lo = data;
        cP->write = 2;
        break;

    default: // error
        bhmMessage("F", PREFIX, "Illegal Write Counter %f data=0x%02x\n", bhmGetCurrentTime(), data);
    }
}

PPM_REG_WRITE_CB(writeCTR0) {
    *(Uns8*)user = data;

    updateCounterWrite(&counter[0], data);

    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, "%f: Write Counter0 = 0x%04x\n", bhmGetCurrentTime(), counter[0].COUNT.value);

}

PPM_REG_READ_CB(readCTR1) {
    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Read Counter1 %f addr=%p bytes=%d user=%p\n", bhmGetCurrentTime(), addr, bytes, user);

    bhmMessage("F", PREFIX, "Unsupported Read from CTR1\n");
    return *(Uns8*)user;
}

PPM_REG_WRITE_CB(writeCTR1) {
    *(Uns8*)user = data;

    updateCounterWrite(&counter[1], data);

    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, "%f: Write Counter1 = 0x%04x\n", bhmGetCurrentTime(), counter[1].COUNT.value);
}

PPM_REG_READ_CB(readCTR2) {
    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Read Counter2 %f addr=%p bytes=%d user=%p\n", bhmGetCurrentTime(), addr, bytes, user);

    bhmMessage("F", PREFIX, "Unsupported Read from CTR2\n");
    return *(Uns8*)user;
}

PPM_REG_WRITE_CB(writeCTR2) {
    *(Uns8*)user = data;

    updateCounterWrite(&counter[2], data);

    if(BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, "%f: Write Counter2 = 0x%04x\n", bhmGetCurrentTime(), counter[2].COUNT.value);
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)

    // Set all outputs low
    if (handles.out0) ppmWriteNet(handles.out0, 0);
    if (handles.out1) ppmWriteNet(handles.out1, 0);
    if (handles.out2) ppmWriteNet(handles.out2, 0);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


