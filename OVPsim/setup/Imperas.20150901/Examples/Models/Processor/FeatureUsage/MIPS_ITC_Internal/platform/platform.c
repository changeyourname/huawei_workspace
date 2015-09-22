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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "icm/icmCpuManager.h"

// an arbitary limit to terminate infinite loops
#define INSTRUCTION_RUN_LIMIT  500

// Message prefix for this module
#define CPU_PREFIX "MIPS32_ITC"

// return processor name
#define GET_NAME(_P) icmGetProcessorName(_P, 0)


////////////////////////////////////////////////////////////////////////////////
// EXTERNALLY-IMPLEMENTED ITC
////////////////////////////////////////////////////////////////////////////////

//
// static root description
//
icmProcessorP root;

//
// implementation configuration limits
//
#define MIPS_ITC_MAX_FIFOS       16
#define MIPS_ITC_MAX_SEPAPHORES  16
#define MIPS_ITC_FIFO_DEPTH_LOG2 2
#define MIPS_ITC_FIFO_DEPTH      (1<<MIPS_ITC_FIFO_DEPTH_LOG2)
#define MIPS_ITC_SEMAPHORE_SAT   0xffff
#define MIPS_ITC_NUM_FIFO        8

//
// default views
//
typedef enum mipsITCViewE {
    ITCV_Bypass          = 0x0,
    ITCV_Control         = 0x1,
    ITCV_EF_Synchronized = 0x2,
    ITCV_EF_Try          = 0x3,
    ITCV_PV_Synchronized = 0x4,
    ITCV_PV_Try          = 0x5,
    ITCV_Last
} mipsITCView;

//
// default ITCAddressMap1 register definition
//
typedef struct mipsITCAddressMap1S {
    Uns32 EntryGrain :  3;
    Uns32 _u1        :  7;
    Uns32 AddrMask   :  7;
    Uns32 _u2        :  3;
    Uns32 NumEntries : 11;
    Uns32 M          :  1;
} mipsITCAddressMap1;

//
// default storage cell tag format
//
typedef struct mipsITCCellTagS {
    Uns32 E          :  1;
    Uns32 F          :  1;
    Uns32 _u1        : 14;
    Uns32 T          :  1;
    Uns32 FIFO       :  1;
    Uns32 FIFOPtr    :  3;
    Uns32 _u2        :  7;
    Uns32 FIFODepth  :  4;
} mipsITCCellTag;

//
// default storage cell
//
typedef struct mipsITCCellS {
    mipsITCCellTag tag;
    Bool           hasBlocked;
    Uns32          value[MIPS_ITC_FIFO_DEPTH];
} mipsITCCell, *mipsITCCellP;

//
// Type used to hold default ITC details
//
typedef struct mipsITCInfoS {
    mipsITCAddressMap1 addressMap1;
    mipsITCCell        cells[MIPS_ITC_MAX_FIFOS+MIPS_ITC_MAX_SEPAPHORES];
} mipsITCInfo, *mipsITCInfoP;

//
// static ITC block description
//
static mipsITCInfo ITCStatics;

//
// Emit current cell state
//
static void debugCell(mipsITCCellP cell) {

    // debug tag
    icmMessage(
        "I", CPU_PREFIX,
        "    TAG: {E:%u F:%u T:%u FIFO:%u FIFOPtr:%u FIFODepth:%u}",
        cell->tag.E,
        cell->tag.F,
        cell->tag.T,
        cell->tag.FIFO,
        cell->tag.FIFOPtr,
        cell->tag.FIFODepth
    );

    if(cell->tag.FIFO) {

        // FIFO cell
        Uns32 i;

        // print all values in the FIFO
        for(i=0; i<cell->tag.FIFOPtr; i++) {
            icmMessage(
                "I", CPU_PREFIX, "    VALUE[%u]: 0x%08x",
                i, cell->value[i]
            );
        }

    } else {

        // print the single semaphore value
        icmMessage("I", CPU_PREFIX, "    VALUE: 0x%08x", cell->value[0]);
    }
}

//
// Emit debug for any cell access
//
static void debugAccess(
    icmProcessorP tc,
    Uns32         cellIndex,
    mipsITCView   view,
    Uns32         result,
    Bool          isRead
) {
    // list of view names
    static const char *viewNames[] = {
        [ITCV_Bypass]          = "Bypass",
        [ITCV_Control]         = "Control",
        [ITCV_EF_Synchronized] = "E/F Synchronized",
        [ITCV_EF_Try]          = "E/F Try",
        [ITCV_PV_Synchronized] = "P/V Synchronized",
        [ITCV_PV_Try]          = "P/V Try"
    };

    // describe the transaction
    icmMessage(
        "I", CPU_PREFIX,
        "%s %s cell %u %s view %s %08x",
        GET_NAME(tc),
        isRead ? "read" : "write",
        cellIndex,
        viewNames[view],
        isRead ? "<=" : "=>",
        result
    );
}

//
// Return spacing between ITC cells
//
inline static Uns32 getCellSpacing(void) {
    return 128*(1<<ITCStatics.addressMap1.EntryGrain);
}

//
// Return cell index implied by ITC address
//
inline static Uns32 getCellIndex(Uns32 address) {
    return address/getCellSpacing();
}

//
// Return view implied by ITC address
//
inline static mipsITCView getView(Uns32 address) {
    return (address>>3) & 0xf;
}

//
// Return the index of the oldest entry in the passed cell
//
inline static Uns32 getOldestIndex(mipsITCCellP cell) {
    return cell->tag.FIFOPtr ? cell->tag.FIFOPtr-1 : 0;
}

//
// Return the index of the newest entry in the passed cell
//
inline static Uns32 getNewestIndex(mipsITCCellP cell) {
    return 0;
}

//
// Is the value the minimum semaphore value?
//
inline static Bool isSemaphoreMin(Uns32 value) {
    return (value & MIPS_ITC_SEMAPHORE_SAT) == 0;
}

//
// Is the value the maximum semaphore value?
//
inline static Bool isSemaphoreMax(Uns32 value) {
    return (value & MIPS_ITC_SEMAPHORE_SAT) == MIPS_ITC_SEMAPHORE_SAT;
}

//
// Take gated exception trap when T bit is set
//
static void takeGatedExceptionTrap(icmProcessorP tc) {
    Uns32 dummy = 0;
    icmWriteReg(tc, "ITCGatedException", &dummy);
}

//
// If in an SC instruction, indicate failure
//
inline static void signalSCFail(icmProcessorP tc) {
    Uns32 dummy = 0;
    icmWriteReg(tc, "ITCSignalSCFail", &dummy);
}

//
// Perform actions when blocking on a gating storage access
//
static void blockTCGS(icmProcessorP tc) {
    Uns32 dummy = 0;
    icmWriteReg(tc, "ITCBlock", &dummy);
}

//
// Restart a TC if it is blocked reading or writing gating storage
//
static ICM_SMP_ITERATOR_FN(unblockTCGS) {
    Uns32 dummy = 0;
    icmWriteReg(processor, "ITCUnblock", &dummy);
}

//
// Perform actions when reading from an empty cell or writing to a full one
//
inline static void blockTCOnCell(icmProcessorP tc, mipsITCCellP cell) {

    // indicate that the cell has TCs blocked on it
    cell->hasBlocked = True;

    // either halt the TC or take an exception
    blockTCGS(tc);
}

//
// Restart any siblings of the passed TC that are blocked waiting on the cell
//
static void restartTCOnCell(mipsITCCellP cell) {

    if(cell->hasBlocked) {

        icmIterAllProcessors(root, unblockTCGS, 0);

        cell->hasBlocked = False;
    }
}

//
// Return bypass read for the passed cell
//
inline static Uns32 readCellBypass(mipsITCCellP cell) {

    return cell->value[getOldestIndex(cell)];
}

//
// Set bypass value for the passed cell
//
static void writeCellBypass(mipsITCCellP cell, Uns32 value) {

    cell->value[getNewestIndex(cell)] = value;

    // restart any TCs blocked waiting for this cell
    restartTCOnCell(cell);

    // emit debug if required
    debugCell(cell);
}

//
// Return tag for the passed cell
//
static Uns32 readCellTag(mipsITCCellP cell) {

    union {mipsITCCellTag tag; Uns32 u32;} u = {cell->tag};

    if(!u.tag.FIFO) {
        u.tag.FIFOPtr = 0;
    }

    return u.u32;
}

//
// Set tag for the passed cell
//
static void writeCellTag(mipsITCCellP cell, Uns32 value) {

    union {Uns32 u32; mipsITCCellTag tag;} u = {value};

    // update writable bits
    cell->tag.E = u.tag.E;
    cell->tag.F = u.tag.F;
    cell->tag.T = u.tag.T;

    // also clear FIFOPtr if E bit is set
    if(u.tag.E) {
        cell->tag.FIFOPtr = 0;
    }

    // restart any TCs blocked waiting for this cell
    restartTCOnCell(cell);

    // emit debug if required
    debugCell(cell);
}

//
// Read value from the passed cell using E/F view
//
static Uns32 readEFCellValue(mipsITCCellP cell) {

    Uns32 result;

    if(cell->tag.E) {

        result = 0;

    } else {

        // restart any TCs blocked waiting for this cell
        if(cell->tag.F) {
            restartTCOnCell(cell);
            cell->tag.F = 0;
        }

        // update cell state
        result = cell->value[--cell->tag.FIFOPtr];
        cell->tag.E = !cell->tag.FIFOPtr;

        // emit debug if required
        debugCell(cell);
    }

    return result;
}

//
// Write value to the passed cell using E/F view
//
static void writeEFCellValue(icmProcessorP tc, mipsITCCellP cell, Uns32 value) {

    Uns32 entries = (1<<cell->tag.FIFODepth);

    if(cell->tag.F) {

        // indicate failure if this is an SC instruction
        signalSCFail(tc);

    } else if(cell->tag.FIFOPtr<entries) {

        Int32 i;

        // restart any TCs blocked waiting for this cell
        if(cell->tag.E) {
            restartTCOnCell(cell);
            cell->tag.E = 0;
        }

        // shift up current entries
        for(i=cell->tag.FIFOPtr; i>0; i--) {
            cell->value[i] = cell->value[i-1];
        }

        // update cell state
        cell->value[0] = value;
        cell->tag.F = (++cell->tag.FIFOPtr==entries);

        // emit debug if required
        debugCell(cell);
    }
}

//
// Read value from the passed cell using P/V view
//
static Uns32 readPVCellValue(mipsITCCellP cell) {

    Uns32 result;

    if(isSemaphoreMin(cell->value[0])) {

        result = 0;

    } else {

        // restart any TCs blocked waiting for this cell
        if(isSemaphoreMax(cell->value[0])) {
            restartTCOnCell(cell);
        }

        // update cell state
        result = cell->value[0]--;

        // emit debug if required
        debugCell(cell);
    }

    return result;
}

//
// Write value to the passed cell using P/V view
//
static void writePVCellValue(icmProcessorP tc, mipsITCCellP cell, Uns32 value) {

    if(isSemaphoreMax(cell->value[0])) {

        // indicate failure if this is an SC instruction
        signalSCFail(tc);

    } else {

        // restart any TCs blocked waiting for this cell
        if(isSemaphoreMin(cell->value[0])) {
            restartTCOnCell(cell);
        }

        // update cell state
        cell->value[0]++;

        // emit debug if required
        debugCell(cell);
    }
}

//
// Validate parameters for access to an ITC cell
//
static Bool validateITC(
    Uns32       cellIndex,
    Uns32       view,
    Uns32       bytes,
    const char *access
) {
    Uns32 numCells = ITCStatics.addressMap1.NumEntries;

    if(bytes!=4) {

        // illegal access size
        icmMessage(
            "W", CPU_PREFIX"_BSZ",
            "ITC %u-byte %s access ignored",
            bytes,
            access
        );
        return False;

    } else if(cellIndex>=numCells) {

        // illegal cell index
        icmMessage(
            "W", CPU_PREFIX"_BCI",
            "ITC cell index %u exceeds maximum %u - %s ignored",
            cellIndex,
            numCells-1,
            access
        );
        return False;

    } else if(view>=ITCV_Last) {

        // illegal cell index
        icmMessage(
            "W", CPU_PREFIX"_BCI",
            "ITC view %u exceeds maximum %u - %s ignored",
            view,
            ITCV_Last-1,
            access
        );
        return False;

    } else {

        return True;
    }
}

//
// ITC read callback
//
static ICM_MEM_READ_FN(readITC) {

    // refresh ITCAddressMap1
    icmReadReg(processor, "ITCAddressMap1", &ITCStatics.addressMap1);

    icmProcessorP tc        = processor;
    Uns32         cellIndex = getCellIndex(address);
    mipsITCView   view      = getView(address);

    if(validateITC(cellIndex, view, bytes, "read")) {

        mipsITCCellP cell   = &ITCStatics.cells[cellIndex];
        Uns32        result = 0;

        // take action based on view
        switch(view) {

            case ITCV_Bypass:
                result = readCellBypass(cell);
                break;

            case ITCV_Control:
                result = readCellTag(cell);
                break;

            case ITCV_EF_Synchronized:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else if(!cell->tag.E) {
                    result = readEFCellValue(cell);
                } else {
                    blockTCOnCell(tc, cell);
                }
                break;

            case ITCV_EF_Try:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else {
                    result = readEFCellValue(cell);
                }
                break;

            case ITCV_PV_Synchronized:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else if(!isSemaphoreMin(cell->value[0])) {
                    result = readPVCellValue(cell);
                } else {
                    blockTCOnCell(tc, cell);
                }
                break;

            case ITCV_PV_Try:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else {
                    result = readPVCellValue(cell);
                }
                break;

            default:
                break;
        }

        // emit debug if required
        debugAccess(tc, cellIndex, view, result, True);

        // return result
        *(Uns32*)value = result;

    } else {

        // return zero result
        memset(value, 0, bytes);
    }
}

//
// ITC write callback
//
static ICM_MEM_WRITE_FN(writeITC) {

    // refresh ITCAddressMap1
    icmReadReg(processor, "ITCAddressMap1", &ITCStatics.addressMap1);

    icmProcessorP tc        = processor;
    Uns32         cellIndex = getCellIndex(address);
    mipsITCView   view      = getView(address);

    if(validateITC(cellIndex, view, bytes, "write")) {

        mipsITCCellP cell   = &ITCStatics.cells[cellIndex];
        Uns32        result = *(Uns32*)value;

        // emit debug if required
        debugAccess(tc, cellIndex, view, result, False);

        // take action based on view
        switch(view) {

            case ITCV_Bypass:
                writeCellBypass(cell, result);
                break;

            case ITCV_Control:
                writeCellTag(cell, result);
                break;

            case ITCV_EF_Synchronized:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else if(!cell->tag.F) {
                    writeEFCellValue(tc, cell, result);
                } else {
                    blockTCOnCell(tc, cell);
                }
                break;

            case ITCV_EF_Try:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else {
                    writeEFCellValue(tc, cell, result);
                }
                break;

            case ITCV_PV_Synchronized:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else if(!isSemaphoreMax(cell->value[0])) {
                    writePVCellValue(tc, cell, result);
                } else {
                    blockTCOnCell(tc, cell);
                }
                break;

            case ITCV_PV_Try:
                if(cell->tag.T) {
                    takeGatedExceptionTrap(tc);
                } else {
                    writePVCellValue(tc, cell, result);
                }
                break;

            default:
                break;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
// COMMON CODE
////////////////////////////////////////////////////////////////////////////////

//
// Scheduler loop
//
static Bool simulate(icmProcessorP processor, Uns64 instructions) {

    switch(icmSimulate(processor, instructions)) {

        case ICM_SR_SCHED:
        case ICM_SR_HALT:
            return True;

        default:
            // end simulation
            return False;
    }
}

const char *vendors[] = {"mips.com", "mips.ovpworld.org", 0};
#define NUMBER_VENDORS 2

//
// Select vendor to use for models
//
static const char *selectVendor() {
    Uns32 i, index = 0;

    // Select default model vendor to be used to load model
    char *runtime = getenv("IMPERAS_RUNTIME");
    if(!runtime || !strcmp(runtime, "OVPsim") || !strcmp(runtime, "CpuManager")) {
        index++; // start from next vendor
    } else {
        ;        // leave default index
    }
    for(i=0;i<NUMBER_VENDORS;i++){
        const char *mipsModel    = icmTryVlnvString(NULL, vendors[index], "processor", "mips32", "1.0", "model");
        const char *mipsSemihost = icmTryVlnvString(NULL, vendors[index], "semihosting", "mips32Newlib", "1.0", "model");
        if(mipsModel && mipsSemihost) {
            return vendors[index];
        }
        // Select next in list, if zero back to first
        if (!vendors[++index]) index = 0;
    }

    icmMessage("F", "MODEL", "No Model Available");
    // Will never reach here
    return NULL;
}

#define MIN_ARGS    6
#define MAX_ARGS    8
#define PROC_ARG    3
#define ENDIAN_ARG  4
#define MODE_ARG    5
#define TRACE_ARG   6

//
// Main simulation routine
//
int main(int argc, char ** argv) {

    Bool trace     = False;
    Bool traceRegs = False;
    Bool bigEndian = False;
    Bool external  = False;

    const char *cpuType = NULL;

    if ((argc < MIN_ARGS) || (argc > MAX_ARGS)) {
        icmPrintf("Wrong number of args (%d)\n", argc);
        icmPrintf("usage: %s <application file> <exception file> <processor> <endian> <mode> [<dbglevel>]\n", argv[0]);
        icmPrintf("where: <application file>   : application file loaded\n"
                  "       <exception file>     : application file loaded containing exception vector code\n"
                  "       <processor variant>  : variant to configure the model e.g. 34Kc\n"
                  "       <endian>             : L or B set Little or Big Endian\n"
                  "       <mode>               : I (internal implement) or X (external implement)\n"
                  "       <dbglevel>           : set bit 1/2 to enable instruction/register trace\n");
        return -1;
    }

    if (argc > PROC_ARG) {
        cpuType = argv[PROC_ARG];
        icmPrintf("\nProcessor %s\n", cpuType);
    }
    if (argc > ENDIAN_ARG) {
        bigEndian = (argv[ENDIAN_ARG][0] == 'B');
    }
    if (argc > MODE_ARG) {
        external = (argv[MODE_ARG][0] == 'X');
    }

    if (argc > TRACE_ARG) {
        trace     = atoi(argv[TRACE_ARG]) & 1;
        traceRegs = atoi(argv[TRACE_ARG]) & 2;
        icmPrintf("Tracing Instructions %s Registers %s\n",
            trace     ? "ON" : "-",
            traceRegs ? "ON" : "-"
        );
    }

    //////////////////////////////////////////////////////////////////////////////
    // Platform Creation Starts here

    //
    // initialize CpuManager
    //
    icmInitPlatform(ICM_VERSION, 0, 0, 0, "platform");

    //
    // Setup the configuration attributes for the simulator
    //
    Uns32 icmAttrs = ICM_ATTR_SIMEX  // the processor model handles simulated exceptions
                     | ICM_ATTR_TRACE_ICOUNT
                     | (trace ? ICM_ATTR_TRACE : 0)
                     | (traceRegs ? ICM_ATTR_TRACE_REGS : 0);

    //
    // Setup the configuration attributes for the MIPS model
    //
    icmAttrListP userAttrs = icmNewAttrList();

    icmAddStringAttr(userAttrs, "endian", bigEndian ? "big" : "little");    // setup endianess

    // Select the processor configuration
    icmAddStringAttr(userAttrs, "variant", cpuType);

    // Enable vectored interrupts
    icmAddStringAttr(userAttrs, "vectoredinterrupt", "enable");

    // Enable MIPS-format trace
    icmAddStringAttr(userAttrs, "MIPS_TRACE", "enable");

    // Enable ITC with 8 FIFO entries and 4 semaphore entries
    icmAddUns64Attr(userAttrs, "ITCNumEntries", 12);
    icmAddUns64Attr(userAttrs, "ITCNumFIFO",    8);

    // Select processor model from library
    const char *vendor    = selectVendor();
    const char *modelFile = icmGetVlnvString(NULL, vendor, "processor", "mips32", "1.0", "model");

    // select semihost file from library
    const char *semihostFile = icmGetVlnvString(NULL, vendor, "semihosting", "mips32Newlib", "1.0", "model");

    //
    // create a processor
    //
    icmProcessorP processor = icmNewProcessor(
        "mips32",       // processor name
        "mips32",       // processor type
        0,              // processor cpuId
        0x20000000,     // enable ITC debug
        32,             // address bits
        modelFile,      // model file
        "modelAttrs",   // morpher attributes
        icmAttrs,       // processor attributes
        userAttrs,      // user attribute list
        semihostFile,   // semihosting file name
        "modelAttrs"    // semihosting attribute symbol
    );

    if(!external) {

        icmPrintf("****************************\n");
        icmPrintf("*       INTERNAL ITC       *\n");
        icmPrintf("****************************\n");

    } else {

        icmPrintf("****************************\n");
        icmPrintf("*       EXTERNAL ITC       *\n");
        icmPrintf("****************************\n");

        // create ITC bus
        icmBusP ITCBus = icmNewBus("ITCBus", 32);

        // map ITC memory using callbacks
        icmMapExternalMemory (
            ITCBus,
            "ITC_Memory",
            ICM_PRIV_RWX,
            0,
            (Uns32)-1,
            readITC,
            writeITC,
            0
        );

        // connect ITC bus
        icmConnectProcessorBusByName(processor, "ITC", ITCBus);

        Uns32 i;

        // save root processor
        root = processor;

        // initialize FIFO cells
        for(i=0; i<MIPS_ITC_NUM_FIFO; i++) {
            ITCStatics.cells[i].tag.E         = 1;
            ITCStatics.cells[i].tag.FIFODepth = MIPS_ITC_FIFO_DEPTH_LOG2;
            ITCStatics.cells[i].tag.FIFO      = 1;
        }
    }

    Uns32 ITCAddressMap0;
    Uns32 ITCAddressMap1;
    Uns32 index;

    // load the processor object files
    if (icmLoadProcessorMemory(processor, argv[1], ICM_LOAD_DEFAULT, False, True) &&
        icmLoadProcessorMemory(processor, argv[2], ICM_LOAD_DEFAULT, False, False)) {
    } else {
        icmPrintf("Fault loading Programs\n");
        return -1;
    }

    ////////////////////////////////////////////////////////////////////////////
    // DO A SIMULATION RUN
    ////////////////////////////////////////////////////////////////////////////

    for(index=0; index<INSTRUCTION_RUN_LIMIT; index++) {
        simulate(processor, 1);
    }

    // show final configuration of ITC
    icmReadReg(processor, "ITCAddressMap0", &ITCAddressMap0);
    icmReadReg(processor, "ITCAddressMap1", &ITCAddressMap1);

    icmPrintf(
        "ITCAddressMap0=0x%08x ITCAddressMap1=0x%08x\n",
        ITCAddressMap0, ITCAddressMap1
    );

    icmTerminate();

    return 0;
}
