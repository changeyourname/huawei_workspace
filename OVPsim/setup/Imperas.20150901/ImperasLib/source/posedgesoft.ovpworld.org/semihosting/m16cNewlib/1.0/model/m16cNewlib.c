/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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



// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"


//
// Message prefix
//
#define CPU_PREFIX "M16C/NEWLIB"

//
// Get native endianness
//
#ifdef HOST_IS_BIG_ENDIAN
    #define ENDIAN_NATIVE MEM_ENDIAN_BIG
#else
    #define ENDIAN_NATIVE MEM_ENDIAN_LITTLE
#endif

//
// M16C/NewLib file modes
//
#define M16C_NEWLIB_S_IFDIR  0x4000
#define M16C_NEWLIB_S_IFREG  0x8000

//
// M16C/NewLib offset of errno entry in struct _reent
//
#define M16C_ERRNO_OFFSET 0

////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

//
// This defines the number of file descriptors for this processor
//
#define FILE_DES_NUM 128
#define REG_ARG_NUM  3

typedef struct vmiosObjectS {

    // first few argument registers (standard ABI)
    vmiRegInfoCP args[REG_ARG_NUM];

    // return register (standard ABI)
    vmiRegInfoCP result;

    // stack pointer (standard ABI)
    vmiRegInfoCP sp;

    // __impure_ptr address and domain
    Addr       impurePtrAddr;
    memDomainP impurePtrDomain;

    // file descriptor table
    Int32 fileDescriptors[FILE_DES_NUM];

} vmiosObject;


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR & DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

#define ERRNO_REF "__impure_ptr"

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    Uns32 i;

    // first few argument registers (standard ABI)
    object->args[0] = vmiosGetRegDesc(processor, "R1");
    object->args[1] = vmiosGetRegDesc(processor, "R2");

    // return register (standard ABI)
    object->result = vmiosGetRegDesc(processor, "R0");

    // stack pointer (standard ABI)
    object->sp = vmiosGetRegDesc(processor, "ISP");

    // __impure_ptr address
    object->impurePtrDomain = vmirtAddressLookup(
        processor, ERRNO_REF, &object->impurePtrAddr
    );

    // initialise stdin, stderr and stdout
    object->fileDescriptors[0] = vmiosGetStdin(processor);
    object->fileDescriptors[1] = vmiosGetStdout(processor);
    object->fileDescriptors[2] = vmiosGetStderr(processor);

    // initialise remaining file descriptors
    for(i=3; i<FILE_DES_NUM; i++) {
        object->fileDescriptors[i] = -1;
    }
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
}


////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Map from model-specific file descriptor to simulated one
//
static Int32 mapFileDescriptor(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         i
) {
    if(i>=FILE_DES_NUM) {
        return -1;
    } else {
        return object->fileDescriptors[i];
    }
}

//
// Return the next available file descriptor
//
static Int32 newFileDescriptor(vmiosObjectP object, const char *context) {

    Int32 i;

    // find and return the first unused file descriptor
    for(i=0; i<FILE_DES_NUM; i++) {
        if(object->fileDescriptors[i]==-1) {
            return i;
        }
    }

    vmiMessage("P", "M16C_TMOF_NEWLIB",
        "Too many open files in %s - semihosting supports up to %u",
        context, FILE_DES_NUM
    );

    return -1;
}

//
// Byte swap the passed value
//
inline static Uns32 swap4(Uns32 value) {

    union {Uns32 v32; Uns8 v8[4];} u = {value};

    Uns8 tmp1 = u.v8[0];
    Uns8 tmp2 = u.v8[1];
    u.v8[0]   = u.v8[3];
    u.v8[1]   = u.v8[2];
    u.v8[2]   = tmp2;
    u.v8[3]   = tmp1;

    return u.v32;
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
    Uns16         sp_index;

    if(index>=2)//REG_ARG_NUM)
    {

        /*vmiMessage("P", "M16C_ANS_NEWLIB",
            "No more than %u function arguments supported",
            REG_ARG_NUM
        );

        vmirtFinish(-1);
        */
        memDomainP domain = vmirtGetProcessorDataDomain(processor);
        vmiosRegRead(processor, object->sp, &sp_index);
        vmirtReadNByteDomain( domain, sp_index + ((index - 2) + 3), result, 2, 0, False);

    } else {
        vmiosRegRead(processor, object->args[index], result);
    }
}

//
// Split function result into result (0/-1) and errno (-result)
//
static void setErrnoAndResult(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Int32         result,
    const char   *context
) {
    if(!object->impurePtrDomain) {

        vmiMessage("P", "M16C_ICF_NEWLIB",
            "Interception of '%s' failed - %s not found "
            "(application does not appear to be compiled with newlib "
            "or has no symbols)",
            context, ERRNO_REF
        );

        vmirtFinish(-1);

    } else if(result<0) {

        memDomainP domain     = object->impurePtrDomain;
        memEndian  endian     = vmirtGetProcessorDataEndian(processor);
        Int16      errnoValue = -result;
        Uns16      impurePtrAddr;

        result = -1;

        // swap errno endianness if required
        if(endian != ENDIAN_NATIVE) {
            errnoValue = swap4(errnoValue);
        }

        // read __impure_ptr value
        vmirtReadNByteDomain(
            domain, object->impurePtrAddr, &impurePtrAddr,
            sizeof(impurePtrAddr), 0, False
        );

        // swap errno address endianness if required
        if(endian != ENDIAN_NATIVE) {
            impurePtrAddr = swap4(impurePtrAddr);
        }

     //   vmiPrintf("impurePtrAddr[%04x] = %04x, errno=%04x\n",(Uns32) object->impurePtrAddr,impurePtrAddr,errnoValue);

        // write back errno
        vmirtWriteNByteDomain(
            domain, impurePtrAddr+M16C_ERRNO_OFFSET, &errnoValue,
            sizeof(errnoValue), 0, True
        );
    }

    vmiosRegWrite(processor, object->result, &result);
}

//
// Write data in the stat buffer 'buf' back to simulation space at address
// 'bufAddr'
//
static void transcribeStatData(
    vmiProcessorP processor,
    Uns32         bufAddr,
    vmiosStatBufP buf
) {
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    memEndian  endian = vmirtGetProcessorDataEndian(processor);

    // or1k/newlib stat structure
    struct {
        Uns32 _u1;      //  0:
        Uns32 mode;     //  4: mode
        Uns32 _u2;      //  8:
        Uns32 _u3;      // 12:
        Uns32 size;     // 16: size
        Uns32 atime;    // 20: atime
        Uns32 _u4;      // 24:
        Uns32 mtime;    // 28: mtime
        Uns32 _u5;      // 32:
        Uns32 ctime;    // 36: ctime
        Uns32 _u6;      // 40:
        Uns32 blksize;  // 44: blksize
        Uns32 blocks;   // 48: blocks
    } simStatStruct = {0};

    // convert from host mode to M16C mode
    // - host S_IFDIR converts to or1k M16C_NEWLIB_S_IFDIR
    // - host S_IFREG converts to or1k M16C_NEWLIB_S_IFREG
    simStatStruct.mode = (
        (buf->mode & 0x1ff) |
        ((buf->mode & VMIOS_S_IFDIR) ? M16C_NEWLIB_S_IFDIR : 0) |
        ((buf->mode & VMIOS_S_IFREG) ? M16C_NEWLIB_S_IFREG : 0)
    );

    // extract remaining basic fields
    simStatStruct.size    = (Uns32)buf->size;
    simStatStruct.atime   = buf->atime;
    simStatStruct.ctime   = buf->ctime;
    simStatStruct.mtime   = buf->mtime;
    simStatStruct.blocks  = buf->blocks;
    simStatStruct.blksize = buf->blksize;

    // swap endianness if required
    if(endian != ENDIAN_NATIVE) {
        simStatStruct.mode    = swap4(simStatStruct.mode);
        simStatStruct.size    = swap4(simStatStruct.size);
        simStatStruct.blocks  = swap4(simStatStruct.blocks);
        simStatStruct.blksize = swap4(simStatStruct.blksize);
        simStatStruct.atime   = swap4(simStatStruct.atime);
        simStatStruct.ctime   = swap4(simStatStruct.ctime);
        simStatStruct.mtime   = swap4(simStatStruct.mtime);
    }

    // write stat struct into M16C data domain
    vmirtWriteNByteDomain(
        domain, bufAddr, &simStatStruct, sizeof(simStatStruct), 0, True
    );
}

//
// Write data in the time buffer 'buf' back to simulation space at address
// 'bufAddr'
//
static void transcribeTimeData(
    vmiProcessorP processor,
    Uns32         bufAddr,
    vmiosTimeBufP buf
) {
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    memEndian  endian = vmirtGetProcessorDataEndian(processor);

    // swap endianness if required
    if(endian != ENDIAN_NATIVE) {
        buf->sec  = swap4(buf->sec);
        buf->usec = swap4(buf->usec);
    }

    // write values into M16C data domain
    vmirtWriteNByteDomain(
        domain, bufAddr, buf, sizeof(*buf), 0, True
    );
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Intercept stat
//
static VMIOS_INTERCEPT_FN(statInt) {

    Uns16 file_nameAddr;
    Uns16 bufAddr;

    // obtain function arguments
    getArg(processor, object, 0, &file_nameAddr);
    getArg(processor, object, 1, &bufAddr);

  //  vmiPrintf("Semihost Intercept\n");
  //  vmirtFinish(0);

    // get file name from data domain
    memDomainP  domain    = vmirtGetProcessorDataDomain(processor);
    const char *file_name = vmirtGetString(domain, file_nameAddr);

    // implement stat
    vmiosStatBuf statBuf = {0};
    Uns32        result  = vmiosStat(processor, file_name, &statBuf);

    // write back results
    transcribeStatData(processor, bufAddr, &statBuf);
    setErrnoAndResult(processor, object, result, context);
}

//
// Intercept lstat
//
static VMIOS_INTERCEPT_FN(lstatInt) {

    Uns16 file_nameAddr;
    Uns16 bufAddr;

    // obtain function arguments
    getArg(processor, object, 0, &file_nameAddr);
    getArg(processor, object, 1, &bufAddr);

   //  vmiPrintf("Semihost Intercept\n");
  //  vmirtFinish(0);

    // get file name from data domain
    memDomainP  domain    = vmirtGetProcessorDataDomain(processor);
    const char *file_name = vmirtGetString(domain, file_nameAddr);

    // implement stat
    vmiosStatBuf statBuf = {0};
    Uns32        result  = vmiosLStat(processor, file_name, &statBuf);

    // write back results
    transcribeStatData(processor, bufAddr, &statBuf);
    setErrnoAndResult(processor, object, result, context);
}


//
// Intercept fstat
//
static VMIOS_INTERCEPT_FN(fstatInt) {

    Uns16 filedes;
    Uns16 bufAddr;

    // obtain function arguments
    getArg(processor, object, 0, &filedes);
    getArg(processor, object, 1, &bufAddr);

//    // 16-bit registers
//    filedes = filedes & 0x0000ffff;
//    bufAddr = bufAddr & 0x0000ffff;

    //vmiPrintf("Semihost Intercept, fd %d, buf %d\n", filedes, bufAddr);
    //vmirtFinish(0);

    // implement fstat
    vmiosStatBuf statBuf = {0};
    Int32        fdMap   = mapFileDescriptor(processor, object, filedes);
    Uns16        result  = vmiosFStat(processor, fdMap, &statBuf);


    // write back results
    transcribeStatData(processor, bufAddr, &statBuf);
    setErrnoAndResult(processor, object, result, context);

}

//
// Intercept read
//
static VMIOS_INTERCEPT_FN(readInt) {

    Uns16 fd;
    Uns16 buf;
    Uns16 count;

    // obtain function arguments
    getArg(processor, object, 0, &fd);
    getArg(processor, object, 1, &buf);
    getArg(processor, object, 2, &count);


  //   vmiPrintf("Semihost Intercept\n");
  //  vmirtFinish(0);

    // implement read
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    Int32      fdMap  = mapFileDescriptor(processor, object, fd);
    Int32      result = vmiosRead(processor, fdMap, domain, buf, count);

    // return result
    setErrnoAndResult(processor, object, result, context);
}

//
// Intercept write
//
static VMIOS_INTERCEPT_FN(writeInt) {

    Uns16 fd;
    Uns16 buf;
    Uns16 count;

    // obtain function arguments
    getArg(processor, object, 0, &fd);
    getArg(processor, object, 1, &buf);
    getArg(processor, object, 2, &count);


   //  vmiPrintf("_write Intercept fd=%0x, buf=%0x,count=%x\n",fd,buf,count);
  //  vmirtFinish(0);

    // implement read
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    Int32      fdMap  = mapFileDescriptor(processor, object, fd);
    Int32      result = vmiosWrite(processor, fdMap, domain, buf, (count));

    // return result
    setErrnoAndResult(processor, object, result, context);
}

//
// Intercept open - note that this appears NOT to use the standard ABI!
//
static VMIOS_INTERCEPT_FN(openInt) {

    Uns16 pathnameAddr;
    Int32 flags;
    Int32 mode;
    Uns32 sp;

    // obtain function arguments
    getArg(processor, object, 0, &pathnameAddr);
    vmiosRegRead(processor, object->sp,   &sp);

  //   vmiPrintf("Semihost Intercept\n");
  //  vmirtFinish(0);

    // get file name from data domain
    memDomainP  domain   = vmirtGetProcessorDataDomain(processor);
    memEndian   endian   = vmirtGetProcessorDataEndian(processor);
    const char *pathname = vmirtGetString(domain, pathnameAddr);

    // get flags & mode from data domain
    vmirtReadNByteDomain(domain, sp,   &flags, sizeof(flags), 0, True);
    vmirtReadNByteDomain(domain, sp+4, &mode,  sizeof(mode),  0, True);

    // swap endianness if required
    if(endian != ENDIAN_NATIVE) {
        flags = swap4(flags);
        mode  = swap4(mode);
    }

    // implement open
    Int32 result = vmiosOpen(processor, pathname, flags, mode);

    // save file descriptor in simulated descriptor table if successful
    if(result>=0) {
        Int32 fdMap = newFileDescriptor(object, context);
        object->fileDescriptors[fdMap] = result;
        result = fdMap;
    }

    // return result
    setErrnoAndResult(processor, object, result, context);
}

//
// Intercept close
//
static VMIOS_INTERCEPT_FN(closeInt) {

    Uns16 fd;

    // obtain function arguments
    getArg(processor, object, 0, &fd);

  //   vmiPrintf("Semihost Intercept\n");
  //  vmirtFinish(0);

    // implement close
    Int32 fdMap  = mapFileDescriptor(processor, object, fd);
    Int32 result = vmiosClose(processor, fdMap);

    // null out the semihosted file descriptor if success
    if(!result) {
        object->fileDescriptors[fd] = -1;
    }

    // return result
    setErrnoAndResult(processor, object, result, context);
}

//
// Intercept lseek
//
static VMIOS_INTERCEPT_FN(lseekInt) {

    Uns16 fildes;
    Uns16 offset;
    Uns16 whence;

    // obtain function arguments
    getArg(processor, object, 0, &fildes);
    getArg(processor, object, 1, &offset);
    getArg(processor, object, 2, &whence);


  //   vmiPrintf("Semihost Intercept\n");
  //  vmirtFinish(0);

    // implement lseek
    Int32 fdMap  = mapFileDescriptor(processor, object, fildes);
    Int32 result = vmiosLSeek(processor, fdMap, offset, whence);

    // return result
    setErrnoAndResult(processor, object, result, context);
}

//
// Intercept unlink
//
static VMIOS_INTERCEPT_FN(unlinkInt) {

    Uns16 pathnameAddr;

    // obtain function arguments
    getArg(processor, object, 0, &pathnameAddr);


  //   vmiPrintf("Semihost Intercept\n");
  //  vmirtFinish(0);

    // get file name from data domain
    memDomainP  domain   = vmirtGetProcessorDataDomain(processor);
    const char *pathname = vmirtGetString(domain, pathnameAddr);

    // implement unlink
    Int32 result = vmiosUnlink(processor, pathname);

    // return result
    setErrnoAndResult(processor, object, result, context);
}

//
// Intercept gettimeofday
//
static VMIOS_INTERCEPT_FN(gettimeofdayInt) {

    Uns16 tvAddr;

    // obtain function arguments
    getArg(processor, object, 0, &tvAddr);

 //    vmiPrintf("Semihost Intercept\n");
 //   vmirtFinish(0);

    // implement gettimeofday
    vmiosTimeBuf timeBuf = {0};
    Int32        result  = vmiosGetTimeOfDay(processor, &timeBuf);

    // write back results
    transcribeTimeData(processor, tvAddr, &timeBuf);
    setErrnoAndResult(processor, object, result, context);
}

//
// Intercept time
//
static VMIOS_INTERCEPT_FN(timeInt) {

    Uns16 tvAddr;

    // obtain function arguments
    getArg(processor, object, 0, &tvAddr);

 //    vmiPrintf("Semihost Intercept\n");
 //   vmirtFinish(0);

    // implement gettimeofday
    vmiosTimeBuf timeBuf = {0};
    vmiosGetTimeOfDay(processor, &timeBuf);

    // write back results
    vmiosRegWrite(processor, object->result, &timeBuf.sec);
}

//
// Intercept times
//
static VMIOS_INTERCEPT_FN(timesInt) {

    Uns16 bufAddr;
    Int32 result = 0;

    // obtain function arguments
    getArg(processor, object, 0, &bufAddr);

  //   vmiPrintf("Semihost Intercept\n");
  //  vmirtFinish(0);

    // ioctl isn't implemented
    vmiMessage("W", "M16C_UNS_NEWLIB1", "times(0x%x) unsupported\n", bufAddr);

    // write back results
    setErrnoAndResult(processor, object, result, context);
}

//
// Intercept ioctl
//
static VMIOS_INTERCEPT_FN(ioctlInt) {

    Uns16 d;
    Uns16 request;
    Int32 result = 0;

    // obtain function arguments
    getArg(processor, object, 0, &d);
    getArg(processor, object, 1, &request);

  //   vmiPrintf("Semihost Intercept\n");
  //  vmirtFinish(0);

    // ioctl isn't implemented
    vmiMessage("W", "M16C_UNS_NEWLIB2", "ioctl(%d, %d, ...) unsupported\n",
        d, request
    );

    // write back results
    setErrnoAndResult(processor, object, result, context);
}

//
// Intercept _exit
//
static VMIOS_INTERCEPT_FN(exitInt) {

    Uns16 status;
    Int32 result = 0;

    // obtain function arguments
    getArg(processor, object, 0, &status);

   //  vmiPrintf("Semihost Intercept\n");
   // vmirtFinish(0);

    // implement exit
    vmirtExit(processor);

    // write back results
    setErrnoAndResult(processor, object, result, context);
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,            // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,  // type
    .packageName    = "Newlib",               // description
    .objectSize     = sizeof(vmiosObject),    // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "posedgesoft.ovpworld.org",
        .library = "semihosting",
        .name    = "m16cNewlib",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,            // object constructor
    .destructorCB   = destructor,             // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = 0,                      // morph callback
    .nextPCCB       = 0,                      // get next instruction address
    .disCB          = 0,                      // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // ----------------- ------- ------ -----------------
        // Name              Address Opaque Callback
        // ----------------- ------- ------ -----------------
        {  "_close",         0,      True,   closeInt        },
        {  "__exit",         0,      True,   exitInt         },
        {  "_fstat",         0,      True,   fstatInt        },
        {  "_gettimeofday",  0,      True,   gettimeofdayInt },
        {  "_ioctl",         0,      True,   ioctlInt        },
        {  "_lseek",         0,      True,   lseekInt        },
        {  "_lstat",         0,      True,   lstatInt        },
        {  "_open",          0,      True,   openInt         },
        {  "_read",          0,      True,   readInt         },
        {  "_stat",          0,      True,   statInt         },
        {  "_time",          0,      True,   timeInt         },
        {  "_times",         0,      True,   timesInt        },
        {  "_unlink",        0,      True,   unlinkInt       },
        {  "_write",         0,      True,   writeInt        },
        {  0                                                 },
    }
};

