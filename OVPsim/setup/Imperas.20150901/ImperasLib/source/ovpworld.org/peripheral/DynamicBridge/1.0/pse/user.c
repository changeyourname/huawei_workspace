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
//                          Mon Jul  1 22:01:35 2013
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#define PREFIX "DynamicBridge"

#define DIAG_1  (diagnosticLevel >= 1)
#define DIAG_2  (diagnosticLevel >= 2)
#define DIAG_3  (diagnosticLevel >= 3)

SimAddr mpLoAddress;
SimAddr spLoAddress;
Uns64   portSize;
Bool    bridgeEnabled = False;

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NET_CB(updateEnable) {

    Bool enable  =  value && !bridgeEnabled;
    Bool disable = !value &&  bridgeEnabled;

    if (disable) {

        // Disable dynamic bridge
        ppmDeleteDynamicBridge("sp", spLoAddress, portSize);
        bridgeEnabled = False;

    }

    if (enable) {

        // Enable dynamic bridge
        ppmCreateDynamicBridge("sp", spLoAddress, portSize, "mp", mpLoAddress);
        bridgeEnabled = True;

    }

    if (DIAG_1) {
        if (enable || disable) {
            bhmMessage(
                "I", PREFIX,
                "%s dynamic mapping for port of size %d at 0x%08llx",
                enable ? "Enable" : "Disable",
                (Uns32) portSize, mpLoAddress
            );
        }
    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    Bool enable = False;

    // Note this peripheral is a nop if no net connected to enable unless enabled
    if (handles.enable || (enable = bhmBoolAttribute("enableBridge"))) {

        if (!bhmUns64Attribute("mpLoAddress", &mpLoAddress) ||
            !bhmUns64Attribute("spLoAddress", &spLoAddress) ||
            !bhmUns64Attribute("portSize"   , &portSize)) {
            bhmMessage("E", PREFIX, "mpLoAddress, spLoAddress and portSize parameters must all be defined");
        }
        if(enable)
        	updateEnable(1, 0);
    }
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

