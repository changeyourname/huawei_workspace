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

// This file constructs the command line parser.
// This file constructs and runs the command line parser.
// This file should NOT need to be edited.

static Bool cmdParser(int argc, const char *argv[]) {
    icmCLPObject parser("AlteraCycloneV_HPS_TLM2", ICM_AC_ALL);
    parser.addArg("ZIMAGE"  , 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.ZIMAGE, "Linux zImage file to load using smartLoader", 0x0, 0, 0);
    parser.addArg("ZIMAGEADDR", 0 , 0, 0                   , ICM_AT_UNS64VAL     , &options.ZIMAGEADDR, "Physical address to load zImage file (default 0x04000000)", 0x0, 0, 0);
    parser.addArg("INITRD"  , 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.INITRD, "Linux initrd file to load using smartLoader", 0x0, 0, 0);
    parser.addArg("INITRDADDR", 0 , 0, 0                   , ICM_AT_UNS64VAL     , &options.INITRDADDR, "Physical address to load initrd file (default 0x06000000)", 0x0, 0, 0);
    parser.addArg("LINUXSYM", 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.LINUXSYM, "Linux ELF file with symbolic debug info (CpuManger only)", 0x0, 0, 0);
    parser.addArg("BOARDID" , 0 , 0, 0                   , ICM_AT_INT32VAL     , &options.BOARDID, "Value to pass to Linux as the boardid (default (0xffffffff)", 0x0, 0, 0);
    parser.addArg("LINUXMEM", 0 , 0, 0                   , ICM_AT_UNS64VAL     , &options.LINUXMEM, "Amount of memory allocated to Linux (required in AMP mode)", 0x0, 0, 0);
    parser.addArg("LINUXCMD", 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.LINUXCMD, "Linux command line (default: 'mem=128M console=ttyS0', with mem value adjusted if LINUXMEM or MEMSIZE specified)", 0x0, 0, 0);
    parser.addArg("APP0"    , 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.APP0, "ELF file to load on CPU0 instead of Linux (Precludes use of Linux options)", 0x0, 0, 0);
    parser.addArg("APP1"    , 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.APP1, "ELF file to load on CPU1 for AMP", 0x0, 0, 0);
    parser.addArg("BOOT"    , 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.BOOT, "ELF file with boot code (both processors will start at its entry)", 0x0, 0, 0);
    parser.addArg("IMAGE0"  , 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.IMAGE0, "Image file to load on cpu0", 0x0, 0, 0);
    parser.addArg("IMAGE0ADDR", 0 , 0, 0                   , ICM_AT_UNS64VAL     , &options.IMAGE0ADDR, "Load address for image on cpu0 (IMAGE0 must be specified)", 0x0, 0, 0);
    parser.addArg("IMAGE0SYM", 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.IMAGE0SYM, "Elf file with symbolic debug info for image on cpu0 (IMAGE0 must be specified, CpuManger only)", 0x0, 0, 0);
    parser.addArg("IMAGE1"  , 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.IMAGE1, "Image file to load on cpu1", 0x0, 0, 0);
    parser.addArg("IMAGE1ADDR", 0 , 0, 0                   , ICM_AT_UNS64VAL     , &options.IMAGE1ADDR, "Load address for image on cpu1 (IMAGE1 must be specified)", 0x0, 0, 0);
    parser.addArg("IMAGE1SYM", 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.IMAGE1SYM, "Elf file with symbolic debug info for image on cpu1 (IMAGE1 must be specified, CpuManger only)", 0x0, 0, 0);
    parser.addArg("UART0PORT", 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.UART0PORT, "Uart0 port: 'auto' for automatic console, 0 for simulator-chosen port, or number for specific port", 0x0, 0, 0);
    parser.addArg("UART1PORT", 0 , 0, 0                   , ICM_AT_STRINGVAL    , &options.UART1PORT, "Uart1 port: 'auto' for automatic console, 0 for simulator-chosen port, or number for specific port", 0x0, 0, 0);
    return parser.parse(argc, argv);
}
