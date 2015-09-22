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

// VMI header files
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

// model header files
#include "or1kExceptions.h"
#include "or1kExceptionTypes.h"
#include "or1kFunctions.h"
#include "or1kStructure.h"
#include "or1kUtils.h"

//
// Read privilege exception handler callback function
//
VMI_RD_PRIV_EXCEPT_FN(or1kRdPrivExceptionCB) {
    if(MEM_AA_IS_TRUE_ACCESS(attrs)) {
        or1kP or1k = (or1kP)processor;
        or1k->EEAR = (Uns32)address;
        or1kTakeException(or1k, OR1K_EXCPT_DPF, 0);
    }
}

//
// Write privilege exception handler callback function
//
VMI_WR_PRIV_EXCEPT_FN(or1kWrPrivExceptionCB) {
    if(MEM_AA_IS_TRUE_ACCESS(attrs)) {
        or1kP or1k = (or1kP)processor;
        or1k->EEAR = (Uns32)address;
        or1kTakeException(or1k, OR1K_EXCPT_DPF, 0);
    }
}

//
// Read alignment exception handler callback function
//
VMI_RD_ALIGN_EXCEPT_FN(or1kRdAlignExceptionCB) {
    or1kP or1k = (or1kP)processor;
    or1k->EEAR = (Uns32)address;
    or1kTakeException(or1k, OR1K_EXCPT_BUS, 0);
    return 0;
}

//
// Write alignment exception handler callback function
//
VMI_WR_ALIGN_EXCEPT_FN(or1kWrAlignExceptionCB) {
    or1kP or1k = (or1kP)processor;
    or1k->EEAR = (Uns32)address;
    or1kTakeException(or1k, OR1K_EXCPT_BUS, 0);
    return 0;
}

//
// Arithmetic exception handler callback function
//
VMI_ARITH_EXCEPT_FN(or1kArithExceptionCB) {

    or1kP or1k = (or1kP)processor;

    switch(exceptionType) {

        // integer divide-by-zero and overflow should not generate exceptions
        // but instead set the carry flag
        case VMI_INTEGER_DIVIDE_BY_ZERO:
        case VMI_INTEGER_OVERFLOW:
            or1k->carryFlag = 1;
            return VMI_INTEGER_ABORT;

        // not expecting any other arithmetic exception types
        default:
            return VMI_INTEGER_UNHANDLED;
    }
}


////////////////////////////////////////////////////////////////////////////////
// HANDLING PENDING EXCEPTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Is there a pending external interrupt?
//
inline static Uns32 isIEEPending(or1kP or1k) {
    return (or1k->PICMR & or1k->PICSR);
}

//
// Are external interrupts enabled?
//
inline static Bool isIEEEnabled(or1kP or1k) {
    return (or1k->SR & SPR_SR_IEE);
}

//
// Should an external interrupt be taken?
//
inline static Uns32 takeIEE(or1kP or1k) {
    return isIEEPending(or1k) && isIEEEnabled(or1k);
}

//
// Is there a pending tick timer interrupt?
//
inline static Uns32 isTEEPending(or1kP or1k) {
    return (or1k->TTMR_IP && or1k->TTMR_IE);
}

//
// Are tick timer interrupts enabled?
//
inline static Bool isTEEEnabled(or1kP or1k) {
    return (or1k->SR & SPR_SR_TEE);
}

//
// Should a tick timer interrupt be taken?
//
inline static Uns32 takeTEE(or1kP or1k) {
    return isTEEPending(or1k) && isTEEEnabled(or1k);
}

//
// Ensure any pending interrupt is taken before the next instruction
//
void or1kInterruptNext(or1kP or1k) {

    if(or1k->reset || takeIEE(or1k) || takeTEE(or1k)) {
        vmirtDoSynchronousInterrupt((vmiProcessorP)or1k);
    }
}

//
// Take processor interrupt (may require processor restart)
//
static void doInterrupt(or1kP or1k) {
    vmirtRestartNext((vmiProcessorP)or1k);
    vmirtDoSynchronousInterrupt((vmiProcessorP)or1k);
}

//
// Handler for fetch exceptions - this should ensure any exceptions pending
// before an instruction is executed are taken.
//
VMI_IFETCH_FN(or1kIFetchExceptionCB) {

    or1kP or1k = (or1kP)processor;

    if(or1k->reset) {

        // reset pending - update registers to complete exception if required
        if(complete) {
            or1k->reset = False;
            or1kTakeException(or1k, OR1K_EXCPT_RST, 0);
            return VMI_FETCH_EXCEPTION_COMPLETE;
        } else {
            return VMI_FETCH_EXCEPTION_PENDING;
        }

    } else if(takeIEE(or1k)) {

        // external interrupt pending - update registers to complete exception
        // if required
        if(complete) {
            or1kTakeException(or1k, OR1K_EXCPT_EXI, 0);
            return VMI_FETCH_EXCEPTION_COMPLETE;
        } else {
            return VMI_FETCH_EXCEPTION_PENDING;
        }

    } else if(takeTEE(or1k)) {

        // tick timer interrupt pending - update registers to complete exception
        // if required
        if(complete) {
            or1kTakeException(or1k, OR1K_EXCPT_TTI, 0);
            return VMI_FETCH_EXCEPTION_COMPLETE;
        } else {
            return VMI_FETCH_EXCEPTION_PENDING;
        }

    } else if(address & 3) {

        // misaligned fetch exception pending - update registers to complete
        // exception if required
        if(complete) {
            or1k->EEAR = (Uns32)address;
            or1kTakeException(or1k, OR1K_EXCPT_BUS, 0);
            return VMI_FETCH_EXCEPTION_COMPLETE;
        } else {
            return VMI_FETCH_EXCEPTION_PENDING;
        }

    } else if(!vmirtIsExecutable(processor, address)) {

        // execute privilege exception pending - update registers to complete
        // exception if required
        if(complete) {
            or1k->EEAR = (Uns32)address;
            or1kTakeException(or1k, OR1K_EXCPT_IPF, 0);
            return VMI_FETCH_EXCEPTION_COMPLETE;
        } else {
            return VMI_FETCH_EXCEPTION_PENDING;
        }

    } else {

        // no exception
        return VMI_FETCH_NONE;
    }
}


////////////////////////////////////////////////////////////////////////////////
// TICK TIMER
////////////////////////////////////////////////////////////////////////////////

//
// values for TTMR_M mode bits
//
typedef enum TTMRmodeE {
    TTMR_DISABLED = 0,  //  TTCR does not run
    TTMR_RESTART  = 1,  //  TTCR counts up until TTMR_TP, then restarts at 0
    TTMR_ONCE     = 2,  //  TTCR counts up until TTMR_TP, then stops
    TTMR_FREE     = 3   //  TTCR counts up, overflowing at max
} TTMRmode;

//
// Return lower 32 bits of the OR1K instruction count
//
inline static Uns32 getThisICount(or1kP or1k) {
    return (Uns32)vmirtGetICount((vmiProcessorP)or1k);
}

//
// Return the TTCR register
//
inline static Uns32 getTTCR(or1kP or1k) {
    if(or1k->timerRunning) {
        return or1k->TTCR - or1k->TTCRSetCount + getThisICount(or1k);
    } else {
        return or1k->TTCR;
    }
}

//
// Set the TTCR register
//
static void setTTCR(or1kP or1k, Uns32 TTCR) {

    // update fields dependent on TTCR
    or1k->TTCR         = TTCR;
    or1k->TTCRSetCount = getThisICount(or1k);

    // if the timer is running, calculate the cycle delay to any interrupt
    // (28 bits maximum) and schedule timer interrupt
    if(or1k->timerRunning) {
        Uns32 iCount = (or1k->TTMR_TP-TTCR-1) & 0xfffffff;
        vmirtSetICountInterrupt((vmiProcessorP)or1k, iCount);
    } else {
        vmirtClearICountInterrupt((vmiProcessorP)or1k);
    }
}

//
// Return the TTCR register
//
Uns32 or1kGetTTCR(or1kP or1k) {
    return getTTCR(or1k);
}

//
// Set the TTCR register
//
void or1kSetTTCR(or1kP or1k, Uns32 TTCR) {

    // restart the timer if mode is TTMR_ONCE
    if(or1k->TTMR_M==TTMR_ONCE) {
        or1k->timerRunning = True;
    }

    setTTCR(or1k, TTCR);
}

//
// Set the TTMR register
//
void or1kSetTTMR(or1kP or1k, Uns32 TTMR) {

    Uns32 TTCR = getTTCR(or1k);

    // update TTMR, recording old and new values of TTMR_IP
    Bool oldIP = or1k->TTMR_IP;
    or1k->TTMR = TTMR;
    Bool newIP = or1k->TTMR_IP;

    // TTMR_IP must not be set by l.mtspr!
    if(!oldIP && newIP) {
        or1k->TTMR_IP = 0;
    }

    // start the timer if mode is TTMR_RESTART or TTMR_FREE
    // (for TTMR_ONCE, timer is restarted by write to TTCR)
    if((or1k->TTMR_M==TTMR_RESTART) || (or1k->TTMR_M==TTMR_FREE)) {
        or1k->timerRunning = True;
    }

    setTTCR(or1k, TTCR);
}

//
// This is called when the tick timer has expired. It should set the interrupt
// pending bit for this exception and return a boolean indicating whether the
// exception is enabled. The exception is subsequently handled in the
// instruction fetch handler, or1kIFetchExceptionCB.
//
VMI_ICOUNT_FN(or1kICountPendingCB) {

    or1kP or1k = (or1kP)processor;

    switch(or1k->TTMR_M) {

        case TTMR_RESTART:
            // restart the timer from 0 on the NEXT instruction
            setTTCR(or1k, -1);
            break;

        case TTMR_FREE:
            // schedule the next interrupt event
            setTTCR(or1k, getTTCR(or1k));
            break;

        case TTMR_ONCE:
            // stop the timer on the NEXT instruction count
            or1k->TTCR         = (getTTCR(or1k)+1) & 0xfffffff;
            or1k->timerRunning = False;
            break;

        case TTMR_DISABLED:
            // how did we get here?
            VMI_ABORT("timer interrupt, but timer was disabled");
            break;
    }

    // if interrupt generation is enabled, set TTMR_IP
    if(or1k->TTMR_IE) {
        or1k->TTMR_IP = 1;
    }

    // handle exception if required
    if(takeTEE(or1k)) {
        doInterrupt(or1k);
    }
}


////////////////////////////////////////////////////////////////////////////////
// PROGRAMMABLE INTERRUPT CONTROLLER
////////////////////////////////////////////////////////////////////////////////

//
// Set the PICMR register
//
void or1kSetPICMR(or1kP or1k, Uns32 PICMR) {

    or1k->PICMR = PICMR;

    // take any pending external interrupt before the next instruction
    if(takeIEE(or1k)) {
        vmirtDoSynchronousInterrupt((vmiProcessorP)or1k);
    }
}

//
// Raise an interrupt request to the Programmable Interrupt Controller
// 'deviceId' should have one bit set to identify the interrupting device
// 'newValue' indicates if the interrupt is to be raised (if zero) or lowered
// (if non-zero)
//
static VMI_NET_CHANGE_FN(externalInterrupt) {

    or1kP or1k     = (or1kP)processor;
    UnsPS deviceId = (UnsPS)userData;

    if(newValue) {
        or1k->PICSR |= deviceId;
    } else {
        or1k->PICSR &= ~deviceId;
    }

    if(takeIEE(or1k)) {
        doInterrupt(or1k);
    }
}

//
// Raise a result interrupt request
//
static VMI_NET_CHANGE_FN(externalReset) {

    or1kP or1k = (or1kP)processor;

    // 'reset' is written with non-zero, raise interrupt
    Bool raise = (newValue != 0) ? True : False;

    if (raise) {
        // if not already halted, halt processor execution
        if(!or1k->halted) {
            or1k->halted = True;
            vmirtHalt((vmiProcessorP)or1k);
        }

    } else {
        // if processor was halted restart
        if(or1k->halted) {
            or1k->halted = False;
            vmirtRestartNext((vmiProcessorP)or1k);
        }

        // indicate that processor reset is required
        or1k->reset = True;

        // exception should be handled now
        doInterrupt(or1k);
    }
}

////////////////////////////////////////////////////////////////////////////////
// NET PORTS
////////////////////////////////////////////////////////////////////////////////

static vmiNetPort netPorts[] = {
    {"intr0", vmi_NP_INPUT, (void*)1, externalInterrupt },
    {"intr1", vmi_NP_INPUT, (void*)2, externalInterrupt },
    {"intr2", vmi_NP_INPUT, (void*)4, externalInterrupt },
    {"intr3", vmi_NP_INPUT, (void*)8, externalInterrupt },
    {"reset", vmi_NP_INPUT, (void*)0, externalReset     },
    VMI_END_NET_PORTS
};

//
// Get the next net port
//
VMI_NET_PORT_SPECS_FN(or1kGetNetPortSpec) {
    if (!prev) {
        return netPorts;
    }
    prev++;
    if (prev->name) {
        return prev;
    }
    return 0;
}



