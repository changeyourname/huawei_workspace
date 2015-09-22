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
//                          Wed Aug 11 15:27:05 2010
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "icm/icmCpuManager.h"

static    Bool  noGraphics            = False;
static    Bool  wallClock             = False;
static    Bool  programLoad           = False;
static    Uns32 uartPort              = 0;
static    Bool  connectARMUartPort    = False;
static    Bool  connectXilinxUartPort = False;
static    float stopafter             = 0.0;
static    char variantArm[32]         = {"ARM926EJ-S"};   // default ARM CPU model is ARM926EJ-S
static    char variantXilinx[32]      = {""};             // default Xilinx CPU model ISA
static    Bool xilinxVariantSet       = False;
static    char xilinxApp[64]          = {""};
static    Bool  enableDebug           = False;          // set True when debugging selected
static    Bool  autoGDBConsole        = False;         // set True when auto start of GDB console selected
static    Uns32 portNum               = 0;              // set to a port number for a debug connection
static    Bool  selectCore            = False;          // set True when a specific core is selected
static    char  coreName[32]          = "arm1";         // set to core name to debug
          char  *coreNameP            = coreName;

static const char* arguments = "[variant <arm|xilinx> <cpu model variant>] [wallclock]\n"
                               "[nographics] [nolinux] [attach <arm|xilinx> <port number>]\n"
                               "[stopafter <seconds to stop after>]\n"
                               "[xilinxapp <application>]"
                               "[debug <port number>] [core <core name for debug>]";

static void parseArgs(int firstarg, int argc, char **argv);

void createPlatform(Uns32 icmInitAttrs) {

    icmPrintf("createPlatform\n"
              "Init: icmInitAttrs 0x%x\n", icmInitAttrs);
    icmPrintf("Options: wallclock %u nographics %u nolinux %u attach %d\n",
                            wallClock, noGraphics, programLoad, uartPort);
    icmPrintf("Debug: %sabled%s port %d\n",
                            enableDebug ? "en" : "dis",
                            autoGDBConsole ? "-autostart" : "",
                            portNum);
    if (selectCore)
        icmPrintf("     : Selected core %s\n", coreName );

////////////////////////////////////////////////////////////////////////////////

    if(autoGDBConsole) {
        icmInitAttrs |= ICM_GDB_CONSOLE;
    }

    icmInitPlatform(ICM_VERSION, icmInitAttrs, enableDebug ? "rsp" : 0, portNum, "Hetero_ArmIntegratorCP_Xilinx");

    if(wallClock) {
        icmSetWallClockFactor(3.0);     // Allow up to 3x wallclock
    }
}

void createPlatformArm(char *kernelFile, char *ramDisk, Uns32 icmAttrs) {

    icmPrintf("createPlatform ARM icmAttrs 0x%x\n"
              "  Files: kernelFile %s\n"
              "         ramDisk %s\n"
              "  Variant ARM %s \n", icmAttrs, kernelFile, ramDisk, variantArm);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus bus1_b
////////////////////////////////////////////////////////////////////////////////

    icmBusP bus1_b = icmNewBus( "bus1_b", 32);


////////////////////////////////////////////////////////////////////////////////
//                                Bus membus_b
////////////////////////////////////////////////////////////////////////////////

    icmBusP membus_b = icmNewBus( "membus_b", 32);


////////////////////////////////////////////////////////////////////////////////
//                               Processor arm1
////////////////////////////////////////////////////////////////////////////////

    const char *arm1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        "arm.ovpworld.org",    // vendor
        0,    // library
        "arm",    // name
        0,    // version
        "model"     // model
    );

    icmAttrListP arm1_attr = icmNewAttrList();

    icmAddStringAttr(arm1_attr, "variant", variantArm);
    icmAddStringAttr(arm1_attr, "compatibility", "ISA");
    icmAddStringAttr(arm1_attr, "showHiddenRegs", "0");
    icmAddDoubleAttr(arm1_attr, "mips", 200.000000);
    icmAddStringAttr(arm1_attr, "endian", "little");

    icmProcessorP arm1_c = icmNewProcessor(
        "arm1",   // name
        "arm",   // type
        0,   // cpuId
        0x0, // flags
         32,   // address bits
        arm1_path,   // model
        "modelAttrs",   // symbol
        0x20,   // procAttrs
        arm1_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectProcessorBusses( arm1_c, bus1_b, bus1_b );

////////////////////////////////////////////////////////////////////////////////
//                                   PSE cm
////////////////////////////////////////////////////////////////////////////////

    const char *cm_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "CoreModule9x6",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP cm_attr = icmNewAttrList();


    icmPseP cm_p = icmNewPSE(
        "cm",   // name
        cm_path,   // model
        cm_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( cm_p, bus1_b, "bport1", 0, 0x10000000, 0x10000fff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE pic1
////////////////////////////////////////////////////////////////////////////////

    const char *pic1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "IntICP",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP pic1_attr = icmNewAttrList();


    icmPseP pic1_p = icmNewPSE(
        "pic1",   // name
        pic1_path,   // model
        pic1_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( pic1_p, bus1_b, "bport1", 0, 0x14000000, 0x14000fff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE pic2
////////////////////////////////////////////////////////////////////////////////

    const char *pic2_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "IntICP",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP pic2_attr = icmNewAttrList();


    icmPseP pic2_p = icmNewPSE(
        "pic2",   // name
        pic2_path,   // model
        pic2_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( pic2_p, bus1_b, "bport1", 0, 0xca000000, 0xca000fff);


////////////////////////////////////////////////////////////////////////////////
//                                   PSE pit
////////////////////////////////////////////////////////////////////////////////

    const char *pit_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "IcpCounterTimer",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP pit_attr = icmNewAttrList();


    icmPseP pit_p = icmNewPSE(
        "pit",   // name
        pit_path,   // model
        pit_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( pit_p, bus1_b, "bport1", 0, 0x13000000, 0x13000fff);


////////////////////////////////////////////////////////////////////////////////
//                                   PSE icp
////////////////////////////////////////////////////////////////////////////////

    const char *icp_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "IcpControl",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP icp_attr = icmNewAttrList();


    icmPseP icp_p = icmNewPSE(
        "icp",   // name
        icp_path,   // model
        icp_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( icp_p, bus1_b, "bport1", 0, 0xcb000000, 0xcb00000f);


////////////////////////////////////////////////////////////////////////////////
//                                   PSE ld1
////////////////////////////////////////////////////////////////////////////////

    const char *ld1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "DebugLedAndDipSwitch",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP ld1_attr = icmNewAttrList();


    icmPseP ld1_p = icmNewPSE(
        "ld1",   // name
        ld1_path,   // model
        ld1_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( ld1_p, bus1_b, "bport1", 0, 0x1a000000, 0x1a000fff);


////////////////////////////////////////////////////////////////////////////////
//                                   PSE kb1
////////////////////////////////////////////////////////////////////////////////

    const char *kb1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "KbPL050",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP kb1_attr = icmNewAttrList();

    icmAddUns64Attr(kb1_attr, "isMouse", 0);
    icmAddUns64Attr(kb1_attr, "grabDisable", 0);

    icmPseP kb1_p = icmNewPSE(
        "kb1",   // name
        kb1_path,   // model
        kb1_attr,   // attrlist
        0,   // semihost file
        "modelAttrs"    // semihost symbol
    );

    icmConnectPSEBus( kb1_p, bus1_b, "bport1", 0, 0x18000000, 0x18000fff);


////////////////////////////////////////////////////////////////////////////////
//                                   PSE ms1
////////////////////////////////////////////////////////////////////////////////

    const char *ms1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "KbPL050",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP ms1_attr = icmNewAttrList();

    icmAddUns64Attr(ms1_attr, "isMouse", 1);
    icmAddUns64Attr(ms1_attr, "grabDisable", 1);

    icmPseP ms1_p = icmNewPSE(
        "ms1",   // name
        ms1_path,   // model
        ms1_attr,   // attrlist
        0,   // semihost file
        "modelAttrs"    // semihost symbol
    );

    icmConnectPSEBus( ms1_p, bus1_b, "bport1", 0, 0x19000000, 0x19000fff);


////////////////////////////////////////////////////////////////////////////////
//                                   PSE rtc
////////////////////////////////////////////////////////////////////////////////

    const char *rtc_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "RtcPL031",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP rtc_attr = icmNewAttrList();


    icmPseP rtc_p = icmNewPSE(
        "rtc",   // name
        rtc_path,   // model
        rtc_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( rtc_p, bus1_b, "bport1", 0, 0x15000000, 0x15000fff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart1
////////////////////////////////////////////////////////////////////////////////

    const char *uart1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "UartPL011",    // name
        0,    // version
        "pse"     // model
    );


    icmAttrListP uart1_attr = icmNewAttrList();
    icmAddStringAttr(uart1_attr, "variant", "ARM");
    icmAddStringAttr(uart1_attr, "outfile", "arm-uart1.log");
    if(connectARMUartPort) {
        if(!uartPort) {
            icmAddUns64Attr(uart1_attr, "console", 1);
        } else {
            icmAddUns64Attr(uart1_attr, "portnum", uartPort);
        }
        icmAddUns64Attr(uart1_attr, "finishOnDisconnect", 1);
    }

    icmPseP uart1_p = icmNewPSE(
        "uart1",       // name
        uart1_path,   // model
        uart1_attr,   // attrlist
        NULL,         // semihost file
        NULL          // semihost symbol
    );

    icmConnectPSEBus( uart1_p, bus1_b, "bport1", 0, 0x16000000, 0x16000fff);
    if(connectARMUartPort) {
        icmSetPSEdiagnosticLevel(uart1_p, 1);
    }

////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart2
////////////////////////////////////////////////////////////////////////////////

    const char *uart2_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "UartPL011",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP uart2_attr = icmNewAttrList();
    icmAddStringAttr(uart2_attr, "variant", "ARM");
    icmAddStringAttr(uart2_attr, "outfile", "arm-uart2.log");

    icmPseP uart2_p = icmNewPSE(
        "uart2",   // name
        uart2_path,   // model
        uart2_attr,   // attrlist
        NULL,   // semihost file
        NULL    // semihost symbol
    );

    icmConnectPSEBus( uart2_p, bus1_b, "bport1", 0, 0x17000000, 0x17000fff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE mmci
////////////////////////////////////////////////////////////////////////////////

    const char *mmci_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "MmciPL181",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP mmci_attr = icmNewAttrList();


    icmPseP mmci_p = icmNewPSE(
        "mmci",   // name
        mmci_path,   // model
        mmci_attr,   // attrlist
        0,   // semihost file
        "modelAttrs"    // semihost symbol
    );

    icmConnectPSEBus( mmci_p, bus1_b, "bport1", 0, 0x1c000000, 0x1c000fff);


////////////////////////////////////////////////////////////////////////////////
//                                   PSE lcd
////////////////////////////////////////////////////////////////////////////////

    const char *lcd_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "LcdPL110",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP lcd_attr = icmNewAttrList();

    icmAddUns64Attr(lcd_attr, "scanDelay", 50000);
	icmAddDoubleAttr(lcd_attr, "noGraphics", noGraphics);
	icmAddDoubleAttr(lcd_attr, "busOffset",  0x80000000);

    icmPseP lcd_p = icmNewPSE(
        "lcd",   // name
        lcd_path,   // model
        lcd_attr,   // attrlist
        0,   // semihost file
        "modelAttrs"    // semihost symbol
    );

    icmConnectPSEBus( lcd_p, bus1_b, "bport1", 0, 0xc0000000, 0xc0000fff);

    icmConnectPSEBusDynamic( lcd_p, membus_b, "memory", 0);


////////////////////////////////////////////////////////////////////////////////
//                               PSE smartLoader
////////////////////////////////////////////////////////////////////////////////

    const char *smartLoader_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        "arm.ovpworld.org",    // vendor
        0,    // library
        "SmartLoaderArmLinux",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP smartLoader_attr = icmNewAttrList();
    if(programLoad) {
        icmAddStringAttr(smartLoader_attr, "disable", "1");
    } else {
        icmAddStringAttr(smartLoader_attr, "initrd", ramDisk);
        icmAddStringAttr(smartLoader_attr, "kernel", kernelFile);
    }


    icmPseP smartLoader_p = icmNewPSE(
        "smartLoader",   // name
        smartLoader_path,   // model
        smartLoader_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( smartLoader_p, bus1_b, "mport", 1, 0x0, 0xffffffff);


////////////////////////////////////////////////////////////////////////////////
//                                 Memory ram1
////////////////////////////////////////////////////////////////////////////////

    icmMemoryP ram1_m = icmNewMemory("ram1_m", 0x7, 0x7ffffff);

    icmConnectMemoryToBus( membus_b, "sp1", ram1_m, 0x0);


////////////////////////////////////////////////////////////////////////////////
//                              Memory ambaDummy
////////////////////////////////////////////////////////////////////////////////

    icmMemoryP ambaDummy_m = icmNewMemory("ambaDummy_m", 0x7, 0xfff);

    icmConnectMemoryToBus( bus1_b, "sp1", ambaDummy_m, 0x1d000000);


////////////////////////////////////////////////////////////////////////////////
//                              Bridge ram1Bridge
////////////////////////////////////////////////////////////////////////////////

    icmNewBusBridge(bus1_b, membus_b, "ram1Bridge", "sp", "mp", 0x0, 0x7ffffff, 0x0);


////////////////////////////////////////////////////////////////////////////////
//                              Bridge ram2Bridge
////////////////////////////////////////////////////////////////////////////////

    icmNewBusBridge(bus1_b, membus_b, "ram2Bridge", "sp1", "mp", 0x0, 0x7ffffff, 0x80000000);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    icmNetP irq_n = icmNewNet("irq_n" );

    icmConnectProcessorNet( arm1_c, irq_n, "irq", ICM_INPUT);

    icmConnectPSENet( pic1_p, irq_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP fiq_n = icmNewNet("fiq_n" );

    icmConnectProcessorNet( arm1_c, fiq_n, "fiq", ICM_INPUT);

    icmConnectPSENet( pic1_p, fiq_n, "fiq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir1_n = icmNewNet("ir1_n" );

    icmConnectPSENet( pic1_p, ir1_n, "ir1", ICM_INPUT);

    icmConnectPSENet( uart1_p, ir1_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir2_n = icmNewNet("ir2_n" );

    icmConnectPSENet( pic1_p, ir2_n, "ir2", ICM_INPUT);

    icmConnectPSENet( uart2_p, ir2_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir3_n = icmNewNet("ir3_n" );

    icmConnectPSENet( pic1_p, ir3_n, "ir3", ICM_INPUT);

    icmConnectPSENet( kb1_p, ir3_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir4_n = icmNewNet("ir4_n" );

    icmConnectPSENet( pic1_p, ir4_n, "ir4", ICM_INPUT);

    icmConnectPSENet( ms1_p, ir4_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir5_n = icmNewNet("ir5_n" );

    icmConnectPSENet( pic1_p, ir5_n, "ir5", ICM_INPUT);

    icmConnectPSENet( pit_p, ir5_n, "irq0", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir6_n = icmNewNet("ir6_n" );

    icmConnectPSENet( pic1_p, ir6_n, "ir6", ICM_INPUT);

    icmConnectPSENet( pit_p, ir6_n, "irq1", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir7_n = icmNewNet("ir7_n" );

    icmConnectPSENet( pic1_p, ir7_n, "ir7", ICM_INPUT);

    icmConnectPSENet( pit_p, ir7_n, "irq2", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir8_n = icmNewNet("ir8_n" );

    icmConnectPSENet( pic1_p, ir8_n, "ir8", ICM_INPUT);

    icmConnectPSENet( rtc_p, ir8_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir23_n = icmNewNet("ir23_n" );

    icmConnectPSENet( pic1_p, ir23_n, "ir23", ICM_INPUT);

    icmConnectPSENet( mmci_p, ir23_n, "irq0", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir24_n = icmNewNet("ir24_n" );

    icmConnectPSENet( pic1_p, ir24_n, "ir24", ICM_INPUT);

    icmConnectPSENet( mmci_p, ir24_n, "irq1", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////

    if(programLoad) {
        if(icmLoadProcessorMemory(arm1_c, kernelFile, ICM_LOAD_DEFAULT, True, True)) {
            // All files loaded correctly
        } else {
            icmPrintf("Failed to load %s\n", kernelFile);
            exit(1);
        }
    }

}

void createPlatformXilinx(Uns32 icmAttrs) {

    icmPrintf("createPlatform Xilinx icmAttrs 0x%x\n"
              "  Variant Xilinx %s\n"
              "  Xilinx App %s\n", icmAttrs, xilinxVariantSet ? variantXilinx : "Not Specified", xilinxApp);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus bus1_b
////////////////////////////////////////////////////////////////////////////////

    icmBusP busX1_b = icmNewBus( "busX1_b", 32);


////////////////////////////////////////////////////////////////////////////////
//                               Processor xilinx1
////////////////////////////////////////////////////////////////////////////////

    const char *xilinx1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        "xilinx.ovpworld.org",    // vendor
        "processor",    // library
        "microblaze",    // name
        0,    // version
        "model"     // model
    );

#if 0
    const char *xilinx_semihost = icmGetVlnvString(
            NULL,
            "xilinx.ovpworld.org",
            "semihosting",
            "microblazeNewlib",
            "1.0",
            "model");
#else
    const char *xilinx_semihost = 0;
#endif

    icmAttrListP xilinx1_attr = icmNewAttrList();

    if(xilinxVariantSet) {
        icmAddStringAttr(xilinx1_attr, "variant", variantXilinx);
    }
//    icmAddStringAttr(xilinx1_attr, "endian", "little");

    icmProcessorP xilinx1_c = icmNewProcessor(
        "xilinx1",         // name
        "microblaze",      // type
        1,                 // cpuId
        icmAttrs,          // flags
         32,               // address bits
        xilinx1_path,      // model
        "modelAttrs",      // symbol
        icmAttrs,          // procAttrs
        xilinx1_attr,      // attrlist
        xilinx_semihost,   // semihost file
        0       // semihost symbol
    );

    icmConnectProcessorBusses( xilinx1_c, busX1_b, busX1_b );

////////////////////////////////////////////////////////////////////////////////
//                                 Memory ram1
////////////////////////////////////////////////////////////////////////////////

    icmMemoryP ramX1_m = icmNewMemory("ramX1_m", 0x7, 0x2fffffff);

    icmConnectMemoryToBus( busX1_b, "sp1", ramX1_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 Peripheral uart
////////////////////////////////////////////////////////////////////////////////

    const char *uartX_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "16550",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP uartX_attr = icmNewAttrList();
    icmAddStringAttr(uartX_attr, "outfile", "xilinx-uart.log");
    if(connectXilinxUartPort) {
        if(!uartPort) {
            icmAddUns64Attr(uartX_attr, "console", 1);
        } else {
            icmAddUns64Attr(uartX_attr, "portnum", uartPort);
        }
        icmAddUns64Attr(uartX_attr, "finishOnDisconnect", 1);
    }

    icmPseP uartX_p = icmNewPSE(
        "uartX",   // name
        uartX_path,   // model
        uartX_attr,   // attrlist
        0,
        0
    );

    icmConnectPSEBus( uartX_p, busX1_b, "bport1", 0, 0x40000000, 0x40000007);
    if(connectXilinxUartPort) {
        icmSetPSEdiagnosticLevel(uartX_p, 0x1);
    }


////////////////////////////////////////////////////////////////////////////////

        if(icmLoadProcessorMemory(xilinx1_c, xilinxApp, ICM_LOAD_DEFAULT, True, True)) {
            // All files loaded correctly
        } else {
            icmPrintf("Failed to load %s\n", xilinxApp);
            exit(1);
        }
}

int main(int argc, char *argv[]) {

    // check for the application program name argument
    if((argc<3)) {
        icmPrintf(
           "usage: %s <kernelFile> <ramdisk>\n"
           "%s\n",
            argv[0], arguments
        );
        return -1;
    }
    char *kernelFile = argv[1];
    char *ramDisk = argv[2];

    parseArgs(3, argc, argv);

    Uns32 icmAttrsArm    = ICM_ATTR_SIMEX;      // simulate exceptions
    Uns32 icmAttrsXilinx = ICM_ATTR_DEFAULT;

    Uns32 icmInitAttrs =   ICM_STOP_ON_CTRLC                 // Ctr-C stops simulation
                         | ICM_VERBOSE                       // Print out statistics on simulation finish
                         | (wallClock ? ICM_WALLCLOCK : 0);  // Do not move time forward when blocked

    // the constructor
    createPlatform(icmInitAttrs);
    createPlatformArm(kernelFile, ramDisk, icmAttrsArm);
    createPlatformXilinx(icmAttrsXilinx);

    if(enableDebug && selectCore) {
        icmProcessorP proc = icmFindProcessorByName(coreName);
        if(proc) {
            // If there's a processor of this name, set this for debug
            // This is required for debug using a standard GDB via RSP.
            // It's not required for Imperas MPD
            icmDebugThisProcessor(proc);
        } else {
            icmMessage("F", "DEBUG", "Core %s could not be found for debugging", coreName);
        }
    }

    if (stopafter) {
        // test mode, run for limited number of instructions
        if(!icmSetSimulationStopTime(stopafter)){
            icmPrintf("Failed to Set Stop Time %f\n", stopafter);
            return -1;
        }
    }

    // run till the end
    icmSimulatePlatform();

    // finish and clean up
    icmTerminate();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////


static void parseArgs(int firstarg, int argc, char **argv) {

    int i;
    for(i=firstarg; i < argc; i++) {
        if (strcmp(argv[i], "wallclock") == 0) {
            wallClock = True;
        } else if (strcmp(argv[i], "nographics") == 0) {
            noGraphics = True;
        } else if (strcmp(argv[i], "nolinux") == 0) {
            programLoad     = True;
        } else if (strcmp(argv[i], "attach") == 0) {
            i++;
            if (strcmp(argv[i], "arm") == 0) {
                connectARMUartPort = True;
            } else if (strcmp(argv[i], "xilinx") == 0) {
                connectXilinxUartPort = True;
            } else {
                fprintf(stderr, "unknown %s: usage attach <arm|xilinx> <variant>\n", argv[i]);
                exit(1);
            }
            sscanf(argv[++i], "%d", &uartPort);
        } else if (strcmp(argv[i], "debug") == 0) {
            if (!strcmp(argv[++i], "autoGDB"))
                autoGDBConsole = True;
            else
                sscanf(argv[i], "%d", &portNum);
            enableDebug = True;
        } else if (strcmp(argv[i], "core") == 0) {
            sscanf(argv[++i], "%s", coreNameP);
            selectCore = True;
        } else if (strcmp(argv[i], "stopafter") == 0) {
            sscanf(argv[++i], "%f", &stopafter);
        } else if (strcmp(argv[i], "xilinxapp") == 0) {
            sscanf(argv[++i], "%s", xilinxApp);
        } else if (strcmp(argv[i], "variant") == 0) {
            i++;
            if (strcmp(argv[i], "arm") == 0) {
                sscanf(argv[++i], "%s", variantArm);
            } else if (strcmp(argv[i], "xilinx") == 0) {
                sscanf(argv[++i], "%s", variantXilinx);
                xilinxVariantSet = True;
            } else {
                fprintf(stderr, "unknown %s: usage variant <arm|xilinx> <variant>\n", argv[i]);
                exit(1);
            }
        } else {
            fprintf(stderr, "unrecognised argument %s\n", argv[i]);
            exit(1);
        }
    }
}
