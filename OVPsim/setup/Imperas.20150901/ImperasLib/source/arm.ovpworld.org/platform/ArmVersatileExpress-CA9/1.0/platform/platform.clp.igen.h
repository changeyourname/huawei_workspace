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
//                             Version 20150901.0
//
////////////////////////////////////////////////////////////////////////////////

static void cmdParserAddUserArgs(icmCLPP parser) {
    icmCLParserAdd(parser, "zimage"  , 0 , 0, "userPlatformConfig", ICM_AT_STRINGVAL    , &options.zimage, "Linux zImage file to load using smartLoader", 0x0, 0, 0);
    icmCLParserAdd(parser, "zimageaddr", 0 , 0, "userPlatformConfig", ICM_AT_UNS64VAL     , &options.zimageaddr, "Physical address to load zImage file (default:physicalbase + 0x00010000)", 0x0, 0, 0);
    icmCLParserAdd(parser, "initrd"  , 0 , 0, "userPlatformConfig", ICM_AT_STRINGVAL    , &options.initrd, "Linux initrd file to load using smartLoader", 0x0, 0, 0);
    icmCLParserAdd(parser, "initrdaddr", 0 , 0, "userPlatformConfig", ICM_AT_UNS64VAL     , &options.initrdaddr, "Physical address to load initrd file (default:physicalbase + 0x00d00000)", 0x0, 0, 0);
    icmCLParserAdd(parser, "linuxsym", 0 , 0, "userPlatformConfig", ICM_AT_STRINGVAL    , &options.linuxsym, "Linux ELF file with symbolic debug info (CpuManger only)", 0x0, 0, 0);
    icmCLParserAdd(parser, "linuxcmd", 0 , 0, "userPlatformConfig", ICM_AT_STRINGVAL    , &options.linuxcmd, "Linux command line (default: 'mem=1024M raid=noautodetect console=ttyAMA0,38400n8 vmalloc=256MB devtmpfs.mount=0'", 0x0, 0, 0);
    icmCLParserAdd(parser, "boardid" , 0 , 0, "userPlatformConfig", ICM_AT_INT32VAL     , &options.boardid, "Value to pass to Linux as the boardid (default (0x8e0)", 0x0, 0, 0);
    icmCLParserAdd(parser, "linuxmem", 0 , 0, "userPlatformConfig", ICM_AT_UNS64VAL     , &options.linuxmem, "Amount of memory allocated to Linux (required in AMP mode)", 0x0, 0, 0);
    icmCLParserAdd(parser, "boot"    , 0 , 0, "userPlatformConfig", ICM_AT_STRINGVAL    , &options.boot, "Boot code object file (If specified, smartLoader will jump to this rather than zImage)", 0x0, 0, 0);
    icmCLParserAdd(parser, "image0"  , 0 , 0, "userPlatformConfig", ICM_AT_STRINGVAL    , &options.image0, "Image file to load on cpu0", 0x0, 0, 0);
    icmCLParserAdd(parser, "image0addr", 0 , 0, "userPlatformConfig", ICM_AT_UNS64VAL     , &options.image0addr, "load address for image on cpu0 (IMAGE0 must be specified)", 0x0, 0, 0);
    icmCLParserAdd(parser, "image0sym", 0 , 0, "userPlatformConfig", ICM_AT_STRINGVAL    , &options.image0sym, "Elf file with symbolic debug info for image on cpu0 (IMAGE0 must be specified, CpuManger only)", 0x0, 0, 0);
    icmCLParserAdd(parser, "image1"  , 0 , 0, "userPlatformConfig", ICM_AT_STRINGVAL    , &options.image1, "Image file to load on cpu1 to n", 0x0, 0, 0);
    icmCLParserAdd(parser, "image1addr", 0 , 0, "userPlatformConfig", ICM_AT_UNS64VAL     , &options.image1addr, "Load address for image on cpu1 to n (IMAGE1 must be specified)", 0x0, 0, 0);
    icmCLParserAdd(parser, "image1sym", 0 , 0, "userPlatformConfig", ICM_AT_STRINGVAL    , &options.image1sym, "Elf file with symbolic debug info for image on cpu1 to n (IMAGE1 must be specified, CpuManger only)", 0x0, 0, 0);
    icmCLParserAdd(parser, "uart0port", 0 , 0, "userPlatformConfig", ICM_AT_STRINGVAL    , &options.uart0port, "Uart0 port: 'auto' for automatic console, 0 for simulator chosen port #, or number of specific port", 0x0, 0, 0);
    icmCLParserAdd(parser, "uart1port", 0 , 0, "userPlatformConfig", ICM_AT_STRINGVAL    , &options.uart1port, "Uart1 port: 'auto' for automatic console, 0 for simulator chosen port #, or number of specific port", 0x0, 0, 0);
    icmCLParserAdd(parser, "nographics", 0 , 0, "userPlatformConfig", ICM_AT_BOOLVAL      , &options.nographics, "Inhibit opening of the lcd graphics window", 0x0, 0, 0);
}
