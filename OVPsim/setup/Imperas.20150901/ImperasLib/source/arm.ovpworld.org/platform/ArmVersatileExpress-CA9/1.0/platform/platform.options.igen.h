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

// This file declares variables that are set by command line arguments.
// This file should NOT need to be edited.

struct optionsS {
    const char*          zimage;
    Uns64                zimageaddr;
    const char*          initrd;
    Uns64                initrdaddr;
    const char*          linuxsym;
    const char*          linuxcmd;
    Int32                boardid;
    Uns64                linuxmem;
    const char*          boot;
    const char*          image0;
    Uns64                image0addr;
    const char*          image0sym;
    const char*          image1;
    Uns64                image1addr;
    const char*          image1sym;
    const char*          uart0port;
    const char*          uart1port;
    Bool                 nographics;
} options = {
};
