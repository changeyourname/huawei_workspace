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
    icmCLParserAdd(parser, "kernel"  , 0 , 0, "user platform config Linux", ICM_AT_STRINGVAL    , &options.kernel, "The Linux Kernel image e.g. vmlinux", 0x0, 0, 0);
    icmCLParserAdd(parser, "ramdisk" , 0 , 0, "user platform config Linux", ICM_AT_STRINGVAL    , &options.ramdisk, "Boot Linux Kernel from the specified ramdisk image e.g. initrd.gz", 0x0, 0, 0);
    icmCLParserAdd(parser, "disk"    , 0 , 0, "user platform config Linux", ICM_AT_STRINGVAL    , &options.disk, "Boot Linux Kernel from the root partition on the disk image e.g. mipsle_hda1", 0x0, 0, 0);
    icmCLParserAdd(parser, "root"    , 0 , 0, "user platform config Linux", ICM_AT_STRINGVAL    , &options.root, "Specify the root partition on the disk image e.g. /dev/sda1", 0x0, 0, 0);
    icmCLParserAdd(parser, "pagebits", 0 , 0, "user platform config Linux", ICM_AT_UNS64VAL     , &options.pagebits, "Specify the page bits used by a Linux Kernel", 0x0, 0, 0);
    icmCLParserAdd(parser, "console" , 0 , 0, "user platform config Linux", ICM_AT_STRINGVAL    , &options.console, "Specify the command line console entry of the Linux Kernel command line, for example tty0", 0x0, 0, 0);
    icmCLParserAdd(parser, "finishonhalt", 0 , 0, "user platform config", ICM_AT_BOOLVAL      , &options.finishonhalt, "Finish simulation when Malta Soft reset asserted", 0x0, 0, 0);
    icmCLParserAdd(parser, "redir"   , 0 , 0, "user platform config", ICM_AT_BOOLVAL      , &options.redir, "Enable re-direction of IP address", 0x0, 0, 0);
    icmCLParserAdd(parser, "nographics", 0 , 0, "user platform config", ICM_AT_BOOLVAL      , &options.nographics, "Disable the VGA graphics window.", 0x0, 0, 0);
    icmCLParserAdd(parser, "tftproot", 0 , 0, "user platform config", ICM_AT_STRINGVAL    , &options.tftproot, "Enable TFTP and specify the tftp root on the host machine.", 0x0, 0, 0);
    icmCLParserAdd(parser, "bootimage", 0 , 0, "user platform config", ICM_AT_STRINGVAL    , &options.bootimage, "Specify a boot image to use. This replaces the default image generated by the SmartLoader.", 0x0, 0, 0);
}
