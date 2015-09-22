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


//  2x16 Alphanumeric Display

#include <ctype.h>
#include <string.h>

#include "pse.igen.h"
#include "userProgView.h"

#define PREFIX "ALPHA_2x16_DISPLAY"

#define MAX_CHARS 32
// Hold the data for the 2x16 display
Uns8 dataArray[MAX_CHARS+1];

//
// Size of stack for new threads
//
#define THREAD_STACK 8*1024

// These are Simulator delays used in bhmWaitDelay
// One second at a nominal 100MIPS rate
#define BHM_ONE_SECOND         1000000
// micro seconds delay
#define BHM_UPDATE_DELAY          1000


#define INCREMENT_ADDRESS(_add)   _add++;                    \
                                  if(_add >= MAX_CHARS) {    \
                                      _add = 0;             \
                                  }                         \


void clearDisplay(){
    int i;
    if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX,"Clear Display\n");
    for(i=0;i<32;i++){
        dataArray[i] = ' ';
    }
    dataArray[i] = 0;
}

static void setDisplay(){

    int i;
    if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX,"Set Display\n");
    for(i=0;i<32;i++){
        dataArray[i] = '#';
    }
}

static void showDisplay(char * from){

    Uns8 row1[20], row2[20];
    strncpy((char *)row1, (const char *)&dataArray[0], 16);
    strncpy((char *)row2, (const char *)&dataArray[16], 16);
    row1[16]=0;// terminate strings
    row2[16]=0;
    bhmMessage("I", PREFIX,"Alpha Numeric Display (%s)\n", from);
    bhmPrintf("Info ("PREFIX") Row1: '%s'\nInfo ("PREFIX") Row2: '%s'\n", row1, row2);
    bhmPrintf("Info ("PREFIX") Display : %s : %s\n",
            busPort_A_data.control.bits.enable ? "enabled" : "disabled",
            busPort_A_data.control.bits.invert ? "inverted" : "normal");
}


Uns8 secondTimerThreadStack[THREAD_STACK];

static void secondTimerThread(void *user)
{
    if (BHM_DIAG_MEDIUM)
        bhmMessage("I", PREFIX,"One Second Timer Thread Started\n");

    for(;;) {

        busPort_A_data.status.bits.busy = 1;

        bhmWaitDelay(BHM_UPDATE_DELAY);

        busPort_A_data.status.bits.busy = 0;

        bhmWaitDelay(BHM_ONE_SECOND-BHM_UPDATE_DELAY);

    }
}


//////////////////////////////// Callback stubs ////////////////////////////////

// Control register bits
#define CONTROL_ENABLE           0x01
#define CONTROL_CLEAR            0x02
#define CONTROL_SET              0x04
#define CONTROL_INVERT           0x08

PPM_REG_WRITE_CB(controlWrite) {
    if(data & CONTROL_SET){
        setDisplay();
        CONTROL_WRITE_SET_EVENT;
        if (BHM_DIAG_LOW){
            showDisplay("control set");
        }
    }
    if(data & CONTROL_CLEAR){
        clearDisplay();
        CONTROL_WRITE_CLEAR_EVENT;
        if (BHM_DIAG_LOW){
            showDisplay("control clear");
        }
    }

    if(busPort_A_data.control.bits.enable && !(data & CONTROL_ENABLE)){
        if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX,"Display Disabled");
        CONTROL_WRITE_DISABLE_EVENT;
    }
    if(!busPort_A_data.control.bits.enable && (data & CONTROL_ENABLE)){
        if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX,"Display Enabled");
        CONTROL_WRITE_ENABLE_EVENT;
    }

    busPort_A_data.control.value = data & ~(CONTROL_SET | CONTROL_CLEAR);

    busPort_A_data.status.bits.enable = busPort_A_data.control.bits.enable;
}

PPM_REG_READ_CB(dataRead) {
    busPort_A_data.data.value = dataArray[busPort_A_data.address.value];

    if (BHM_DIAG_MEDIUM) bhmMessage("I", PREFIX,"dataRead: Address %u", busPort_A_data.address.value);
    INCREMENT_ADDRESS(busPort_A_data.address.value);

    return busPort_A_data.data.value;
}

PPM_REG_WRITE_CB(dataWrite) {
    if(busPort_A_data.control.bits.enable){
        dataArray[busPort_A_data.address.value] = data;
        busPort_A_data.data.value = data;
        if (BHM_DIAG_MEDIUM) bhmMessage("I", PREFIX,"dataWrite: Address %u", busPort_A_data.address.value);

        INCREMENT_ADDRESS(busPort_A_data.address.value);
    }
    if (BHM_DIAG_LOW){
        showDisplay("data write");
    }
}

PPM_REG_WRITE_CB(statusWriteError) {
    // Do nothing on a write
    if (BHM_DIAG_LOW) bhmMessage("W", PREFIX,"Register 'status' is READ only");
}


PPM_CONSTRUCTOR_CB(userStart) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)

    initProgrammersView();
    clearDisplay();

    bhmThreadHandle secondTimer;
    secondTimer = bhmCreateThread(
                        secondTimerThread,
                        0,
                        "secondTimer",
                        &secondTimerThreadStack[THREAD_STACK]);


}

PPM_SAVE_STATE_FN(peripheralSaveState) {

    if (phase==PPM_POST_SAVE_RESTORE) {

        if (BHM_DIAG_LOW) {
            bhmMessage("I", PREFIX,"Save State");
        }
    }
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {

    if (phase==PPM_POST_SAVE_RESTORE) {

        if (BHM_DIAG_LOW) {
            bhmMessage("I", PREFIX,"Restore State");
        }

        if (BHM_DIAG_LOW) {
            showDisplay("restore");
        }
    }
}

