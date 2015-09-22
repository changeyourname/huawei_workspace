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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiPSE.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiVersion.h"

#include "hostapi/impAlloc.h"

#define PREFIX "FlashNorP30"
#define CPU_PREFIX PREFIX

//
// Device access macros (model 2x16 data bit chips implementing 32 data bits)
// Note: cannot model with 16 data bit single chips because a peripheral
// model may not drive just the high/low 16 bits of bus.
//

// Each command is sent simultaneously to both chips,
// i.e. at the lower 16 bits AND at the higher 16 bits
#define CMD_MASK                0xffff
#define LOW_CMD(_V)             ((_V) & CMD_MASK)
#define HIGH_CMD(_V)            (LOW_CMD((_V >> 16)))
#define CMDS_MATCH(_V)          (LOW_CMD(_V) == HIGH_CMD(_V))
#define DUAL_VALUE(_V)          (((_V) << 16) | ((_V) & 0xffff))

// Blocks are organized as 256KB Main blocks (128KB per chip in the 2x16 configuration)
// with one main block implemented as 4x64KB parameter blocks
#define MAIN_BLOCK_SIZE         0x00040000
#define MAIN_BLOCK_MASK         (~(MAIN_BLOCK_SIZE-1))
#define PARAM_BLOCK_SIZE        0x00010000
#define PARAM_BLOCK_MASK        (~(PARAM_BLOCK_SIZE-1))

// Macros to calculate first/last main/param block offsets
// Only "Top Configuration" supported where last main block is used as parameter blocks
#define FIRST_MAIN_BLOCK(_S)    (0)
#define FIRST_PARAM_BLOCK(_S)   (((_S)-1) & MAIN_BLOCK_MASK)
#define LAST_MAIN_BLOCK(_S)     ((FIRST_PARAM_BLOCK(_S)-1) & MAIN_BLOCK_MASK)
#define LAST_PARAM_BLOCK(_S)    (((_S)-1) & PARAM_BLOCK_MASK)

// READ Commands
#define CMD_READ_DEVICE_ID                    0x0090
#define CMD_READ_STATUS_REGISTER              0x0070
#define CMD_CLEAR_STATUS_REGISTER             0x0050
#define CMD_READ_ARRAY                        0x00FF
#define CMD_READ_CFI_QUERY                    0x0098

// WRITE Commands
// Note buffered writes are simply written as they are received
#define CMD_WORD_PROGRAM_SETUP                0x0040
#define CMD_ALTERNATE_WORD_PROGRAM_SETUP      0x0010
#define CMD_BUFFERED_PROGRAM_SETUP            0x00E8
#define CMD_BUFFERED_PROGRAM_CONFIRM          0x00D0
#define CMD_BEFP_SETUP                        0x0080
#define CMD_BEFP_CONFIRM                      0x00D0

// ERASE Commands
#define CMD_BLOCK_ERASE_SETUP                 0x0020
#define CMD_BLOCK_ERASE_CONFIRM               0x00D0

// SUSPEND Commands
#define CMD_PROGRAM_OR_ERASE_SUSPEND          0x00B0
#define CMD_SUSPEND_RESUME                    0x00D0

// BLOCK LOCKING / UNLOCKING Commands
#define CMD_LOCK_BLOCK_SETUP                  0x0060
#define CMD_LOCK_BLOCK                        0x0001
#define CMD_UNLOCK_BLOCK                      0x00D0
#define CMD_LOCK_DOWN_BLOCK                   0x002F

// PROTECTION Commands
#define CMD_PROGRAM_PROTECTION_REGISTER_SETUP 0x00C0

// CONFIGURATION Commands
#define CMD_READ_CONFIGURATION_REGISTER_SETUP 0x0060
#define CMD_READ_CONFIGURATION_REGISTER       0x0003

// Read Device Identifier Data
// 0x0089 = Intel
#define READ_ID_MANUFACTURER                  0x0089
// 0x8919 = 256-MBit, Top Parameter
// TODO: Adjust this based on size of chips: 64/128/256 MBit
#define READ_ID_CODE                          0x8919
// Only default values for the Read Configuration Register are supported
#define READ_ID_RCR                           0xbfcf

// Read Device Identifier Data offsets
// NOTE: These are << 2 from the data sheet due to the 2x16 configuration
#define READ_ID_OFFSET_MANUFACTURER           0x00
#define READ_ID_OFFSET_CODE                   0x04
#define READ_ID_OFFSET_LOCK_CONFIG            0x08
#define READ_ID_OFFSET_RCR                    0x14

typedef enum flashStateE {
    state_READ_ARRAY = 0, // Initial state
    state_READ_ID,
    state_READ_CFI,
    state_READ_STATUS,
    state_PROGRAM,
    state_PROGRAM_BUFFERED_COUNT,
    state_PROGRAM_BUFFERED,
    state_PROGRAM_BUFFERED_DONE,
    state_ERASE,
    state_LOCK,
    state_PROTECT,
    state_CONFIG
} flashStateT;

#define STATE_ENUM_STRING(_N)  [state_##_N] = #_N
static const char *flashStateNames[] = {
    STATE_ENUM_STRING(READ_ARRAY),
    STATE_ENUM_STRING(READ_ID),
    STATE_ENUM_STRING(READ_CFI),
    STATE_ENUM_STRING(READ_STATUS),
    STATE_ENUM_STRING(PROGRAM),
    STATE_ENUM_STRING(ERASE),
    STATE_ENUM_STRING(LOCK),
    STATE_ENUM_STRING(PROTECT),
    STATE_ENUM_STRING(CONFIG)
};

typedef union flashStatusU {
    struct {
        Uns32   BWS: 1;   // BEFP Status (0=complete, 1=in progress)
        Uns32   BLS: 1;   // Bock-lock Status (0=not locked, 1=locked, op aborted)
        Uns32   PSS: 1;   // Suspend Status (0=not in effect, 1=in effect)
        Uns32   VPPS:1;   // VPP Status (0=in range, 1=out of range)
        Uns32   PS:  1;   // Program Status (0=successful, 1=fail or sequence error)
        Uns32   ES:  1;   // Erase Status (0=successful, 1=fail or sequence error)
        Uns32   ESS: 1;   // Erase suspend Status (0=not in effect, 1=in effect)
        Uns32   DWS: 1;   // Device Write Status (0=Busy, 1=Ready)
    } flags;
    Uns32 value;
} flashStatusT;
static const flashStatusT sequenceError = { .flags = {.ES=1, .PS=1} };
static const flashStatusT clearStatus   = { .flags = {.DWS=1} };

//
// CFI Query Data
// (See section C.4 in Intel StrataFlash Embedded Memory P30 Family Datasheet)
//
static Uns8 cfiQueryData[] = {
/*00h*/ 0x00, 0x00, 0x00, 0x00, // Filler to data start at 0x10
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
/*10h*/ 'Q', 'R', 'Y',          // ID string
        0x01, 0x00,             // Vendor command set ID
        0x0a, 0x01,             // Extended query table primary address
        0x00, 0x00,             // Alternate vendor command set (none)
        0x00, 0x00,             // Secondary Extended Query table primary address (none)
/*1Bh*/ 0x17, 0x20, 0x85, 0x95, // System Interface (from data sheet)
        0x08, 0x09, 0x0a, 0x00,
        0x01, 0x01, 0x02, 0x00,
/*27h*/ 0x01, 0x00, 0x06, 0x00, // Device Geometry (per chip), defaults for:
        0x19, 0x01, 0x00, 0x06, //  256MBit, top configuration
        0x00, 0x02, 0xfe, 0x00, //  255 Main blocks of 128KB
        0x00, 0x02, 0x03, 0x00, //  4   Parameter blocks of 32KB
        0x80, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
};

//
// CFI Extended Query Table Data
// (See section C.5 in Intel StrataFlash Embedded Memory P30 Family Datasheet)
// (p = offset = 0x10a)
//
static Uns8 cfiEQTData[] = {
/*p+00h*/ 'P', 'R', 'I', '1',     // ID string
          '4',  0x00, 0x00, 0x00, // Optional features (none supported)
/*p+08h*/ 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00,
/*p+10h*/ 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00,
/*p+18h*/ 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00
};

#define DIAG_LOW(_O)  (((_O)->diagnosticLevel & 0x7) >= 1)
#define DIAG_MED(_O)  (((_O)->diagnosticLevel & 0x7) >= 2)
#define DIAG_HIGH(_O) (((_O)->diagnosticLevel & 0x7) >= 3)

typedef struct vmiosObjectS  {

    char         *name;
    vmiProcessorP processor;
    memDomainP    pseDomain;
    memEndian     pseEndian;

    // PSE ABI registers
    vmiRegInfoCP  result;
    vmiRegInfoCP  sp;

    // Command state
    flashStateT   state;
    flashStatusT  status;
    Uns32         bufferCount;      // buffered writes remaining until done

    // the Flash RAM mapped region
    memDomainP   portDomain;
    Uns8        *flashMem;
    Addr         flashSize;
    Addr         lowAddr;
    Addr         highAddr;

    // diagnostics (PSE's diagnosticLevel is remapped to use this variable)
    Uns32 diagnosticLevel;

} vmiosObject;

//
// Issue fatal message if address range is not in the flash memory range
//
static void checkAddress(vmiosObjectP object, Addr address, Uns32 bytes) {
    Addr high = bytes ? address+bytes-1 : address;
    if (address < object->lowAddr || object->highAddr < high) {
        vmiMessage(
            "F", PREFIX"_OOR",
            "%s: Flash Address 0x"FMT_Ax":0x"FMT_Ax" out of range 0x"FMT_Ax":0x"FMT_Ax,
            object->name,
            address,
            address+bytes,
            object->lowAddr,
            object->highAddr
        );
        // Not reached
    }
}

//
// Return the block base address and optionally the block size
// for a Flash memory address (Address may be in either
// a main block or a parameter block)
//
static Addr getBlockBase(vmiosObjectP object, Addr address, Uns32 *size) {

    checkAddress(object, address, 0);

    Addr offset     = address - object->lowAddr;
    Addr base       = offset & MAIN_BLOCK_MASK;
    Uns32 blockSize = MAIN_BLOCK_SIZE;

    if (base == FIRST_PARAM_BLOCK(object->flashSize)) {
        base = offset & PARAM_BLOCK_MASK;
        blockSize = PARAM_BLOCK_SIZE;
    }

    if (size) *size = blockSize;
    return object->lowAddr + base;

}

//
// Initialize the block of flash memory containing address to all 1's
//
static void eraseBlock(vmiosObjectP object, Addr address) {

    Uns32  blockSize;
    Addr   blockBase = getBlockBase(object, address, &blockSize);
    Uns8  *ptr       = object->flashMem+(blockBase-object->lowAddr);
    Uns8  *end       = ptr + blockSize;

    // Make sure we do not overflow the flash memory array
    if (end >= (object->flashMem + object->flashSize)) {
        end = object->flashMem + (object->flashSize);
    }

    while (ptr < end) {
        *(ptr++) = 0xff;
    }
}

static void printData(
    vmiosObjectP object,
    Addr         address,
    const void  *value,
    Uns32        bytes,
    const char  *type
) {
    if (bytes == 4) {
        vmiMessage(
            "I", PREFIX"_FRW",
            "%s: Flash %s: %d bytes at 0x"FMT_A08x" (block base=0x"FMT_A08x"): 0x%x",
            object->name,
            type,
            bytes,
            address,
            getBlockBase(object, address, NULL),
            *(Uns32 *)value
        );
    } else {
        vmiMessage(
            "I", PREFIX"_FRW",
            "%s: Flash %s: %d bytes at 0x"FMT_A08x" (block base=0x"FMT_A08x"): ",
            object->name,
            type,
            bytes,
            address,
            getBlockBase(object, address, NULL)
        );
        vmiPrintf("\t");
        Uns32 i = 0;
        while (i < bytes) {
            unsigned char byte = *((unsigned char *)(value + i));
            vmiPrintf(" %02x", byte);
            if (((++i % 8) == 0) && (i < bytes)) {
                vmiPrintf("\n\t");
            }
        }
        vmiPrintf("\n");
    }
}

//
// Called on writes to flash memory
//
static VMI_MEM_WRITE_FN(flashWriteCB) {

    vmiosObjectP object        = userData;
    Bool         writeData     = False;
    Bool         programData   = False;
    flashStateT  thisState     = object->state;
    flashStateT  nextState     = object->state;

    checkAddress(object, address, bytes);

    if (attrs == MEM_AA_FALSE) {

        // Allow artifact accesses to write to the flash memory
        writeData = True;

    } else if (bytes != 4) {

        vmiMessage(
            "W", PREFIX"_IWS",
            "%s: Invalid size %d for FLASH device write. Only 4 byte writes supported",
            object->name,
            bytes
        );

    } else if (thisState == state_PROGRAM) {

        // Program the data
        programData = True;
        nextState   = state_READ_STATUS;

    } else if (thisState == state_PROGRAM_BUFFERED) {

        // Program the data and decrement the count
        programData = True;
        if (object->bufferCount) {
            object->bufferCount--;
        } else {
            nextState = state_PROGRAM_BUFFERED_DONE;
        }

    } else {

        // Data is a command
        Uns32 data = *(Uns32 *)value;
        Uns16 cmd  = LOW_CMD(data);

        if (!CMDS_MATCH(data)) {

            // In 2x16 configuration all commands and data must match high and low
            vmiMessage(
                "W", PREFIX"_CDM",
                "%s: High and low flash commands do not match: 0x%x. Command ignored.",
                object->name,
                data
            );

        } else {

            switch (thisState) {
            case state_ERASE:
                if (cmd == CMD_BLOCK_ERASE_CONFIRM) {
                    eraseBlock(object, address);
                } else {
                    object->status.value |= sequenceError.value;
                }
                nextState = state_READ_STATUS;
                break;

            case state_LOCK:
                if ((cmd == CMD_LOCK_BLOCK) ||
                    (cmd == CMD_UNLOCK_BLOCK) ||
                    (cmd == CMD_LOCK_DOWN_BLOCK)) {
                    // Block locking not supported - ignore and move to Ready state
                    nextState = state_READ_STATUS;
                } else {
                    object->status.value |= sequenceError.value;
                }
                nextState = state_READ_STATUS;
                break;

            case state_PROGRAM_BUFFERED_COUNT:
                // write of the buffer count
                object->bufferCount = cmd;
                nextState           = state_PROGRAM_BUFFERED;
                break;

            case state_PROGRAM_BUFFERED_DONE:
                if (cmd != CMD_BUFFERED_PROGRAM_CONFIRM) {
                    object->status.value |= sequenceError.value;
                }
                nextState = state_READ_STATUS;
                break;

            case state_PROTECT:
                // Protection not supported - ignore
                // Spec does not indicate the state should change (?)
                break;

            case state_CONFIG:
                // Configuration register not supported - ignore and move to Ready state
                nextState = state_READ_STATUS;

                // Warn if attempting to place into burst mode
                // new config register data is the address (!)
                Uns32 newConfigVal = (address & 0xffff);
                if ((newConfigVal & 0x8000) == 0) {
                    vmiMessage(
                        "W", PREFIX"_BMU",
                        "%s: Attempt to place Flash into unsupported synchronous burst read mode ignored.",
                        object->name
                    );
                }
                break;

            default:
                switch (cmd) {
                case CMD_READ_ARRAY:
                    nextState = state_READ_ARRAY;
                    break;
                case CMD_READ_STATUS_REGISTER:
                    nextState = state_READ_STATUS;
                    break;
                case CMD_READ_DEVICE_ID:
                    nextState = state_READ_ID;
                    break;
                case CMD_READ_CFI_QUERY:
                    nextState = state_READ_CFI;
                    break;
                case CMD_CLEAR_STATUS_REGISTER:
                    object->status.value = clearStatus.value;
                    break;
                case CMD_WORD_PROGRAM_SETUP:
                case CMD_ALTERNATE_WORD_PROGRAM_SETUP:
                    nextState = state_PROGRAM;
                    break;
                case CMD_BUFFERED_PROGRAM_SETUP:
                    nextState = state_PROGRAM_BUFFERED_COUNT;
                    break;
                case CMD_BLOCK_ERASE_SETUP:
                    nextState = state_ERASE;
                    break;
                case CMD_LOCK_BLOCK_SETUP:
                    nextState = state_LOCK;
                    break;
                case 0xf0:
                case 0xaa:
                case 0x55:
                    // These are commands in other devices that this device
                    // does not recognize, but are issued by Linux - ignore
                    break;
                default:
                    vmiMessage(
                        "W", PREFIX"_UFC",
                        "%s: Unrecognized flash command 0x%x in state %s",
                        object->name,
                        cmd,
                        flashStateNames[thisState]
                    );
                }
                break;
            }
        }
    }

    if (DIAG_MED(object)) {
        if (thisState != nextState) {
            vmiMessage(
                "I", PREFIX"_FSC",
                "%s: Flash State changed: %s->%s",
                object->name,
                flashStateNames[thisState],
                flashStateNames[nextState]
            );
        }
    }

    if (writeData || programData) {

        // write data into flash memory
        Uns8 *start = object->flashMem + (address - object->lowAddr);
        Uns8 *d     = (Uns8 *)value;

        Uns8 *ptr;
        for (ptr = start; ptr < start+bytes; ptr++, d++) {
            if (programData) {
                // When programming can only change values from 1->0
                *ptr &= *d;
            } else {
                *ptr = *d;
            }
        }

        if (DIAG_MED(object)) {
            printData(object, address, start, bytes, "write");
        }

    }

    object->state = nextState;

}

static VMI_MEM_READ_FN(flashReadCB) {

    vmiosObjectP object = userData;

    checkAddress(object, address, bytes);

    if (attrs == MEM_AA_FALSE || object->state == state_READ_ARRAY) {

        // do a normal read from the flash memory
        Uns8  *ptr = object->flashMem + (address - object->lowAddr);
        Uns8  *end = ptr + bytes;
        Uns8  *d   = (Uns8 *)value;

        while (ptr < end) {
            *(d++) = *(ptr++);
        }

    } else if (bytes != 4) {

        vmiMessage(
            "W", PREFIX"_IWS",
            "%s: Invalid size %d for FLASH device non-array read. Only 4 byte reads supported",
            object->name,
            bytes
        );

    } else {

        Uns32 result = 0;
        const char *readType = "read";

        if ((object->state == state_READ_STATUS) ||
            (object->state == state_PROGRAM_BUFFERED_COUNT)
        ) {

            result = DUAL_VALUE((Uns32)object->status.value);
            readType = "read status";

        } else if (object->state == state_READ_ID) {

            // Return Device Identifier Info based on address
            Uns16 deviceIdInfo   = 0;
            Addr  deviceIdOffset = address - getBlockBase(object, address, NULL);

            if (deviceIdOffset == READ_ID_OFFSET_MANUFACTURER) {
                deviceIdInfo = READ_ID_MANUFACTURER;
            } else if (deviceIdOffset == READ_ID_OFFSET_CODE) {
                deviceIdInfo = READ_ID_CODE;
            } else if (deviceIdOffset == READ_ID_OFFSET_LOCK_CONFIG) {
                // All blocks are always unlocked so just use constant value
                deviceIdInfo = 0;
            } else if (deviceIdOffset == READ_ID_OFFSET_RCR) {
                deviceIdInfo = READ_ID_RCR;
            } else {
                vmiMessage(
                    "W", PREFIX"_URI",
                    "%s: Unsupported Read Device ID offset address 0x"FMT_Ax,
                    object->name,
                    deviceIdOffset
                );
            }

            result = DUAL_VALUE(deviceIdInfo);
            readType = "read id";

        } else if (object->state == state_READ_CFI) {

            // Return CFI Query Structure Info based on address
            // Note: must adjust offset for 2x16 bit chips
            Addr offset     = (address - object->lowAddr) >> 2;
            Uns8 cfiQryInfo = 0;

            if ((offset >= 0x10) && (offset < sizeof(cfiQueryData))) {
                cfiQryInfo = cfiQueryData[offset];
            } else if ((offset >= 0x10a) && (offset < 0x10a + sizeof(cfiEQTData))) {
                // CFI Extended Query Table data starts at 0x10a
                cfiQryInfo = cfiEQTData[offset-0x10a];
            }

            result = DUAL_VALUE(cfiQryInfo);
            readType = "read cfi";

        } else {

            vmiMessage(
                "W", PREFIX"_UFS",
                "%s: Unexpected state %s in Flash read callback",
                object->name,
                flashStateNames[object->state]
            );

        }

        *((Uns32 *)value) = result;

        if (DIAG_MED(object)) {
            printData(object, address, value, bytes, readType);
        }
    }
}

//
// Load a binary image file into flash memory
//
static int loadImageFile(vmiosObjectP object, const char *fileName, Uns32 offset) {

    FILE *fp = fopen(fileName, "rb");

    if (!fp) {
        vmiMessage(
            "E", PREFIX "_IFE",
            "%s: Unable to open Flash image file '%s'\n",
            object->name,
            fileName
        );
        return 0;
    }

    Addr       totalBytes;
    Uns32      bytesRead;
    char       buf[1024];
    memRegionP cachedRegion = NULL;

    for (totalBytes = 0; (totalBytes < object->flashSize); totalBytes += bytesRead) {

        Uns32 numRead = sizeof(buf);

        if (totalBytes + numRead > object->flashSize) {
            numRead = object->flashSize - totalBytes;
        }

        // Read data from Image file
        bytesRead = fread(buf, 1, numRead, fp);
        if (bytesRead <= 0) {
            // EOF or error
            break;
        }

        // Copy data read from image file to flash memory
        Addr thisBase = object->lowAddr + offset + totalBytes;
        memMapped rc = vmirtWriteNByteDomain(
            object->portDomain,
            thisBase,
            buf,
            bytesRead,
            &cachedRegion,
            MEM_AA_FALSE
        );
        if (rc != MEM_MAP_FULL) {
            vmiMessage(
                "F" , PREFIX"_IWE",
                "%s: Error writing %u bytes from image file to Flash memory at 0x"FMT_Ax": rc=%d",
                object->name,
                bytesRead,
                thisBase,
                rc
            );
            // not reached
        }
    }

    if (ferror(fp)) {

        vmiMessage(
            "I", PREFIX "_IFE",
            "%s: Error reading Flash image file '%s': %s",
            object->name,
            fileName,
            strerror(errno)
        );

    } else {


        vmiMessage(
            "I", PREFIX "_IFR",
            "%s: "FMT_Au" bytes loaded from Flash image file '%s' to location 0x"FMT_A08x,
            object->name,
            totalBytes,
            fileName,
            object->lowAddr+offset
        );

        // Are any bytes left in the image file?
        if (fread(buf, 1, 1, fp)==1) {
            vmiMessage(
                "W", PREFIX"_ILF",
                "%s: Image file '%s' is larger than Flash memory size of "FMT_Au" bytes",
                object->name,
                fileName,
                object->flashSize
            );
        }
    }

    if (fclose(fp)!=0) {
        vmiMessage(
            "E", PREFIX "_ICE",
            "%s: Failed to close Flash image file '%s'",
            object->name,
            fileName
        );
    }
    return 0;
}

//
// Parse fileName string of filename[@offset][,filename[@offset]]...
//
static void loadImageFiles(vmiosObjectP object, const char *fileNamesIn) {

    char *next;
    char *fileName = strdup(fileNamesIn);

    while (fileName && *fileName) {

        // look for multiple file names separated by ','
        next = strchr(fileName, ',');
        if (next) {
            // separate file names by replacing ',' delimiter with \0
            *(next++) = '\0';
        }

        // Look for an offset separated by '@'
        Uns32 offset    = 0;
        char *offsetStr = strchr(fileName, '@');
        if (offsetStr) {
            // separate file name and offset by replacing '@' delimiter with \0
            char *end;
            *(offsetStr++) = '\0';
            offset = strtoul(offsetStr, &end, 0);
            if (!end || *end != '\0') {
                vmiMessage(
                    "F", PREFIX"_IFS",
                    "%s: Invalid offset '%s' in image file specification: '%s'",
                    object->name,
                    offsetStr,
                    fileNamesIn
                );
            }
        }

        // Load this file
        loadImageFile(object, fileName, offset);

        // chect next name, if specified
        fileName = next;
    }
}

//
// Initialize flash memory to all 1's
//
static void initFlashMemory(vmiosObjectP object) {

    Addr blockOffset;
    Addr firstMainBlock  = FIRST_MAIN_BLOCK (object->flashSize);
    Addr lastMainBlock   = LAST_MAIN_BLOCK  (object->flashSize);
    Addr firstParamBlock = FIRST_PARAM_BLOCK(object->flashSize);
    Addr lastParamBlock  = LAST_PARAM_BLOCK (object->flashSize);

    // Erase Main Blocks
    for (
         blockOffset =  firstMainBlock;
         blockOffset <= lastMainBlock;
         blockOffset += MAIN_BLOCK_SIZE
    ) {
        eraseBlock(object, object->lowAddr+blockOffset);
    }

    // Erase Parameter Blocks
    for (
         blockOffset =  firstParamBlock;
         blockOffset <= lastParamBlock;
         blockOffset += PARAM_BLOCK_SIZE
    ) {
        eraseBlock(object, object->lowAddr+blockOffset);
    }
}

//
// Return n such that value = 2^^n
// Value must be a power of 2
//
static Uns32 log2Int(Addr value) {
    Uns32 n = 0;
    if (value) {
        VMI_ASSERT(!(value & (value-1)), "Argument not a power of 2");
        while (!(value & 0x1ULL)) {
            n++;
            value >>= 1;
        }
    }
    return n;
}

//
// Set the CFI Device geometry info according to the size of the memory defined
//
static void setCFIGeometry(vmiosObjectP object) {

    Addr  size           = object->flashSize;
    Uns32 numBlocks      = size / MAIN_BLOCK_SIZE;
    Uns32 numMainBlocks  = numBlocks - 1;
    Uns32 numParamBlocks = 4;

    // Check for legal flash memory size: power of 2 and at least 2 main blocks
    if (numBlocks < 2 || (size & (size-1))) {
        vmiMessage(
            "E", PREFIX "_IS",
            "%s: Invalid Flash memory size 0x"FMT_Ax" - must be power of 2 >= 0x%x",
            object->name,
            object->flashSize,
            (2*MAIN_BLOCK_SIZE)
        );
        // Set the default size, though simulation cannot continue
        object->flashSize = (1025 * 512);
        object->highAddr = object->lowAddr + object->flashSize - 1;
        return;
    }

    // 0x27: n such that device size = 2n in number of bytes
    // Note: adjust size for single chip
    cfiQueryData[0x27] = log2Int(size/2);

    // 0x2c: number of regions with different sizes
    cfiQueryData[0x2c] = 2;

    // 0x2e:0x2d: Number of same size blocks in region 1 minus 1
    cfiQueryData[0x2d] =  (numMainBlocks - 1)       & 0xff;
    cfiQueryData[0x2e] = ((numMainBlocks - 1) >> 8) & 0xff;

    // 0x30:0x2f: Size of blocks in region 1 divided by 256
    // Note: adjust BLOCK_SIZE for single chip
    cfiQueryData[0x2f] = ((MAIN_BLOCK_SIZE/2)>>8)  & 0xff;
    cfiQueryData[0x30] = ((MAIN_BLOCK_SIZE/2)>>16) & 0xff;

    // 0x32:0x31: Number of same size blocks in region 2 minus 1
    // Region 2 is last main block implemented as 4 parameter blocks
    cfiQueryData[0x31] =  (numParamBlocks - 1)       & 0xff;
    cfiQueryData[0x32] = ((numParamBlocks - 1) >> 8) & 0xff;

    // 0x34:0x33: Size of blocks in region 2 divided by 256
    // Note: adjust BLOCK_SIZE for single chip
    cfiQueryData[0x33] = ((PARAM_BLOCK_SIZE/2)>>8)  & 0xff;
    cfiQueryData[0x34] = ((PARAM_BLOCK_SIZE/2)>>16) & 0xff;

}

//
// Read a function argument using the standard ABI
//
static void getArg(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         index,
    void         *result
) {
    Uns32      argSize   = 4;
    Uns32      argOffset = (index+1)*argSize;
    Uns32      spAddr;

    // get the stack
    vmiosRegRead(processor, object->sp, &spAddr);

    // read argument value
    vmirtReadNByteDomain(object->pseDomain, spAddr+argOffset, result, argSize, 0, True);
}

//
// Called to create the Flash model state.
//
static VMIOS_INTERCEPT_FN(flashNorCFIInit) {

    Uns32 portNameP;
    Uns32 imageFileNameP;
    Uns32 diagP;

    // Get arguments
    getArg(processor, object, 0, &portNameP);
    getArg(processor, object, 1, &imageFileNameP);
    getArg(processor, object, 2, &diagP);

    // Read the current value of the PSE diagnosticLevel
    object->diagnosticLevel = vmirtRead4ByteDomain(object->pseDomain, diagP, object->pseEndian, MEM_AA_FALSE);

    // Remap the PSE diagnosticLevel to native memory so
    // changes to it are visible here as well
    vmirtMapNativeMemory(object->pseDomain, diagP, diagP+sizeof(Uns32)-1, &object->diagnosticLevel);

    // Get info from port connection
    Bool isMaster;
    Bool isDynamic;
    const char *portName  = vmirtGetString(object->pseDomain, portNameP);
    object->portDomain = vmipsePlatformPortAttributes(
        processor,
        portName,
        &object->lowAddr,
        &object->highAddr,
        &isMaster,
        &isDynamic
    );
    if (!object->portDomain || isMaster) {
        vmiMessage(
            "F", PREFIX "_NP",
            "%s: Unable to find slave port '%s'",
            object->name,
            portName
        );
    }

    // Calculate size and set the CFI configuration accordingly
    object->flashSize = object->highAddr - object->lowAddr + 1;
    setCFIGeometry(object);

    // Allocate memory for the Flash array and initialize to all 1's
    object->flashMem = STYPE_ALLOC_N(Uns8, object->flashSize);
    VMI_ASSERT(object->flashMem, "Unable to allocate "FMT_Au" bytes for flash memory", object->flashSize);
    initFlashMemory(object);

    // Add read/write callbacks for the Flash port
    vmirtMapCallbacks(object->portDomain, object->lowAddr, object->highAddr, flashReadCB, flashWriteCB, object);

    if (DIAG_LOW(object)) {
        vmiMessage(
            "I", PREFIX "_FMA",
            "%s: NOR FLASH memory added at 0x"FMT_A08x":0x"FMT_A08x" ("FMT_Au" bytes)",
            object->name,
            object->lowAddr,
            object->highAddr,
            object->flashSize
        );
    }


    // Load image file(s), if specified
    const char *fileNames = vmirtGetString(object->pseDomain, imageFileNameP);
    if (fileNames) {
        loadImageFiles(object, fileNames);
    } else {
        if (DIAG_LOW(object)) {
            vmiMessage(
                "W", PREFIX "_NFI",
                "%s: No image file(s) specified for initializing flash memory",
                object->name
            );
        }
    }

    // Set Device Write Status bit
    object->status.flags.DWS = 1;

}


// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    object->name      = strdup(vmirtProcessorName(processor));
    object->processor = processor;
    object->pseDomain = vmirtGetProcessorDataDomain(processor);
    object->pseEndian = vmirtGetProcessorDataEndian(processor);

    // get PSE ABI registers
    object->result = vmiosGetRegDesc(processor, "eax");
    object->sp     = vmiosGetRegDesc(processor, "esp");

    if (!object->result || !object->sp) {
        vmiMessage(
            "F", PREFIX"_IP",
            "%s: Intercept library attached to non-PSE processor model.",
            object->name
        );
    }
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
    if (object->name) {
        free(object->name);
        object->name = NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,                // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,      // type
    .packageName    = PREFIX,                     // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "intel.ovpworld.org",
        .library = "peripheral",
        .name    = "NorFlashP30",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,                // object constructor
    .destructorCB   = destructor,                 // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = 0,                          // morph callback
    .nextPCCB       = 0,                          // get next instruction address
    .disCB          = 0,                          // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////
    // -------------------   ----------- ------ -----------------
    // Name                  Address     Opaque Callback
    // -------------------   ----------- ------ -----------------
    .intercepts = {
        {"flashNorCFIInit",  0,       True,   flashNorCFIInit},
        {0}
    }
};
