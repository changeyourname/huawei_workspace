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
//                          Wed Jan 12 17:58:14 2011
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

Uns32 availableLEDS = 4;    // Set default
Uns8 ledReg = 0;

//static inline void showLEDs() {
void showLEDs() {
    char buffer[64]; buffer[0]=0;
    Uns32 i;
    for (i=availableLEDS; i ; i--) {
        char buff[8]; buff[0]=0;
        sprintf(buff, "%s ", (ledReg & (1<<(i-1))) ? "ON" : "--");
        strcat(buffer, buff);
    }
    bhmMessage("I", "LED", "%s at %f", buffer, bhmGetCurrentTime()/1000000);
}

PPM_REG_READ_CB(readLed) {
    return ledReg;
}

PPM_REG_WRITE_CB(resetLed) {
    ledReg &= ~data;
    if(diagnosticLevel)
        showLEDs();
    *(Uns8*)user = ledReg;
}

PPM_REG_WRITE_CB(setLed) {
    ledReg |= data;
    if(diagnosticLevel)
        showLEDs();
    *(Uns8*)user = ledReg;
}

PPM_REG_WRITE_CB(writeLed) {
    ledReg = data;
    if(diagnosticLevel)
        showLEDs();
    *(Uns8*)user = ledReg;
}

PPM_CONSTRUCTOR_CB(config) {

    periphConstructor();

    if( bhmUns32Attribute("availableLEDS", &availableLEDS) && (availableLEDS > 8)) {
        bhmMessage("W", "LED", "Maximum LEDs to display is 8");
        availableLEDS=8;
    }

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));

}



PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

