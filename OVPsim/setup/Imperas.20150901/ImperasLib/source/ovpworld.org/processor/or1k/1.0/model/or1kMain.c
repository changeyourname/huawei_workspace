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


// Imperas header files
#include "hostapi/impAlloc.h"

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"

// model header files
#include "or1kDoc.h"
#include "or1kExceptions.h"
#include "or1kStructure.h"
#include "or1kFunctions.h"
#include "or1kParameters.h"

//
// Return number of members of an array
//
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))


////////////////////////////////////////////////////////////////////////////////
// BUS PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Template bus port list
//
const static vmiBusPort busPorts[] = {
    {"INSTRUCTION", vmi_BP_MASTER, vmi_DOM_CODE, {32,32}, 1, "Used to fetch code for execution"},
    {"DATA"       , vmi_BP_MASTER, vmi_DOM_DATA, {32,32}, 0, "Used to read & write data"       },
};

//
// Allocate bus port specifications
//
static void newBusPorts(or1kP or1k) {

    Uns32 i;

    or1k->busPorts = STYPE_CALLOC_N(vmiBusPort, NUM_MEMBERS(busPorts));

    for(i=0; i<NUM_MEMBERS(busPorts); i++) {
        or1k->busPorts[i] = busPorts[i];
    }
}

//
// Free bus port specifications
//
static void freeBusPorts(or1kP or1k) {

    if(or1k->busPorts) {
        STYPE_FREE(or1k->busPorts);
        or1k->busPorts = 0;
    }
}

//
// Get the next bus port
//
VMI_BUS_PORT_SPECS_FN(or1kGetBusPortSpec) {

    or1kP or1k = (or1kP)processor;

    if(!prev) {

        // first port
        return or1k->busPorts;

    } else {

        // port other than the first
        Uns32 prevIndex = (prev-or1k->busPorts);
        Uns32 thisIndex = prevIndex+1;

        return (thisIndex<NUM_MEMBERS(busPorts)) ? &or1k->busPorts[thisIndex] : 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
// FIFO PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Allocate FIFO port structure
//
static vmiFifoPortP newFifoPorts(or1kP or1k) {

    // declare temporary port structure (including terminator)
    vmiFifoPort template[] = {
        {"fifoIn" , vmi_FIFO_INPUT,  32, (void *)&or1k->inputConn },
        {"fifoOut", vmi_FIFO_OUTPUT, 32, (void *)&or1k->outputConn},
        VMI_END_FIFO_PORTS
    };

    // count members
    Uns32 numMembers = NUM_MEMBERS(template);
    Uns32 i;

    // allocate permanent port structure (including terminator)
    vmiFifoPortP result = STYPE_CALLOC_N(vmiFifoPort, numMembers);

    // fill permanent port structure
    for(i=0; i<numMembers; i++) {
        result[i] = template[i];
    }

    return result;
}

//
// Get the next fifo port, if enabled
//
VMI_FIFO_PORT_SPECS_FN(or1kGetFifoPortSpec) {

    or1kP or1k = (or1kP)processor;

    if(!prev) {
        return or1k->fifoPorts;
    }

    prev++;

    if(prev->name) {
        return prev;
    }

    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// OR1K processor constructor
//
VMI_CONSTRUCTOR_FN(or1kConstructor) {

    or1kP            or1k   = (or1kP)processor;
    or1kParamValuesP params = (or1kParamValuesP)parameterValues;
    Uns32 i;

    // initialise general purpose registers
    for(i=2; i<OR1K_REGS; i++) {
        or1k->regs[i] = 0xdeadbeef;
    }

    // initialise status registers SR, ESR, EPCR and EEAR
    or1k->SR   = SPR_SR_FO | SPR_SR_SM;
    or1k->ESR  = 0xdeadbeef;
    or1k->EPC  = 0xdeadbeef;
    or1k->EEAR = 0xdeadbeef;

    // create FIFO port descriptions if enabled
    if(OR1K_ENABLE_FIFOS(processor) || params->fifos) {
        or1k->fifoPorts = newFifoPorts(or1k);
    }

    // create bus port specifications
    newBusPorts(or1k);

    // construct the documentation  tree
    or1kDoc(processor, params);
}

//
// OR1K processor destructor
//
VMI_DESTRUCTOR_FN(or1kDestructor) {

    or1kP or1k = (or1kP)processor;

    if(or1k->fifoPorts) {
        STYPE_FREE(or1k->fifoPorts);
    }

    // free bus port specifications
    freeBusPorts(or1k);
}

//
// OR1K virtual memory initialisation
//
VMI_VMINIT_FN(or1kVMInit) {

	#if(OR1K_MRU_TEST)

        or1kP      or1k           = (or1kP)processor;
        memDomainP physicalDomain = codeDomains[0];
        memDomainP virtualDomain  = vmirtNewDomain("virtual", 32);

        or1k->mruSet.nextState    = &or1k->currentState;
        or1k->mruSet.currentState = &or1k->currentState;

        vmirtAliasMemory(
            physicalDomain,
            virtualDomain,
            0x00000000,
            0xffffffff,
            0x00000000,
            &or1k->mruSet
        );

        codeDomains[0] = virtualDomain;
        dataDomains[0] = virtualDomain;
        codeDomains[1] = virtualDomain;
        dataDomains[1] = virtualDomain;

    #endif
}

