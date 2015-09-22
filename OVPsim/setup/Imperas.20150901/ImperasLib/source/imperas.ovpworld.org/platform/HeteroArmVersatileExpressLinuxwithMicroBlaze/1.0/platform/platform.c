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
//                              Version 99999999
//                          Wed Oct 26 15:41:19 2011
//
////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "icm/icmCpuManager.h"

// Arguments definition
static void parseArgs(int firstarg, int argc, char **argv);
Uns32   uartPort = 0;
Bool    connectARMUartPort      = False;
Bool    connectXilinxUartPort   = False;
Bool    autoConsole             = False;
Bool    noGraphics              = False;
char    bootCode[256]           = "";
Bool    loadBootCode            = False;
char    variantArm[32]          = "Cortex-A9MPx1";
char    sdCardImage[256]        = "";
Bool    loadSDCard              = False;
char    modelVendor[64]         = "arm.ovpworld.org";
char    modelVersion[8]         = "1.0";
char    variantXilinx[32]       = {""};             // default Xilinx CPU model ISA
Bool    xilinxVariantSet        = False;
char    xilinxApp[64]           = {"hello.MICROBLAZE.elf"};
Bool    wallClock               = False;
float   stopafter               = 0.0;


const char *arguments = "[variant <arm|xilinx> <cpu model variant>]\n"
                        "[B <boot code>] [SD <Card Image to load> ]"
                        "[attach <arm|xilinx> <port number>]\n"
                        "[stopafter <seconds to stop after>] [nographics]\n"
                        "[xilinxapp <application>]";

ICM_SMP_ITERATOR_FN(setStartAddress);


void createPlatform(Uns32 icmInitAttrs) {

    icmPrintf("createPlatform\n"
              "Init: icmInitAttrs 0x%x\n", icmInitAttrs);
    icmPrintf("Options: wallclock %u nographics %u attach %d\n",
                            wallClock, noGraphics, uartPort);

////////////////////////////////////////////////////////////////////////////////

    icmInitPlatform(ICM_VERSION, icmInitAttrs, 0, 0, "Hetero_ArmVersatileExpress_Xilinx");

    if(wallClock) {
        icmSetWallClockFactor(3.0);     // Allow up to 3x wallclock
    }
}

void createPlatformArm(Uns32 icmAttrs) {


////////////////////////////////////////////////////////////////////////////////
//                                 Bus smbus_b
////////////////////////////////////////////////////////////////////////////////

    icmBusP smbus_b = icmNewBus( "smbus_b", 32);


////////////////////////////////////////////////////////////////////////////////
//                                Bus ddr2bus_b
////////////////////////////////////////////////////////////////////////////////

    icmBusP ddr2bus_b = icmNewBus( "ddr2bus_b", 32);


////////////////////////////////////////////////////////////////////////////////
//                               Processor cpu0
////////////////////////////////////////////////////////////////////////////////

    const char *cpu_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        modelVendor,    // vendor
        0,    // library
        "arm",    // name
        modelVersion,    // version
        "model"     // model
    );

    icmAttrListP cpu_attr = icmNewAttrList();

    icmAddStringAttr(cpu_attr, "variant", variantArm);
    icmAddStringAttr(cpu_attr, "compatibility", "ISA");
    icmAddStringAttr(cpu_attr, "showHiddenRegs", "0");
    icmAddStringAttr(cpu_attr, "UAL", "1");
    icmAddUns64Attr(cpu_attr, "override_CBAR", 503316480);
    icmAddDoubleAttr(cpu_attr, "mips", 448.000000);
    icmAddStringAttr(cpu_attr, "endian", "little");

    icmProcessorP cpu_c = icmNewProcessor(
        "cpu",   // name
        "arm",   // type
        0,   // cpuId
        0x0, // flags
         32,   // address bits
        cpu_path,   // model
        "modelAttrs",   // symbol
        0x20,   // procAttrs
        cpu_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectProcessorBusses( cpu_c, smbus_b, smbus_b );


////////////////////////////////////////////////////////////////////////////////
//                                 PSE sysRegs
////////////////////////////////////////////////////////////////////////////////

    const char *sysRegs_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "VexpressSysRegs",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP sysRegs_attr = icmNewAttrList();


    icmPseP sysRegs_p = icmNewPSE(
        "sysRegs",   // name
        sysRegs_path,   // model
        sysRegs_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( sysRegs_p, smbus_b, "bport1", 0, 0x10000000, 0x10000fff);


////////////////////////////////////////////////////////////////////////////////
//                                 PSE sysCtrl
////////////////////////////////////////////////////////////////////////////////

    const char *sysCtrl_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "SysCtrlSP810",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP sysCtrl_attr = icmNewAttrList();


    icmPseP sysCtrl_p = icmNewPSE(
        "sysCtrl",   // name
        sysCtrl_path,   // model
        sysCtrl_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( sysCtrl_p, smbus_b, "bport1", 0, 0x10001000, 0x10001fff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE aac1
////////////////////////////////////////////////////////////////////////////////

    const char *aac1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "AaciPL041",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP aac1_attr = icmNewAttrList();


    icmPseP aac1_p = icmNewPSE(
        "aac1",   // name
        aac1_path,   // model
        aac1_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( aac1_p, smbus_b, "bport1", 0, 0x10004000, 0x10004fff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE mmc1
////////////////////////////////////////////////////////////////////////////////

    const char *mmc1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "MmciPL181",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP mmc1_attr = icmNewAttrList();

    if (loadSDCard) {
        icmAddStringAttr(mmc1_attr, "SD_DRIVE", sdCardImage);
    }


    icmPseP mmc1_p = icmNewPSE(
        "mmc1",   // name
        mmc1_path,   // model
        mmc1_attr,   // attrlist
        0,   // semihost file
        "modelAttrs"    // semihost symbol
    );


    icmConnectPSEBus( mmc1_p, smbus_b, "bport1", 0, 0x10005000, 0x10005fff);


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

    icmAddUns64Attr(kb1_attr, "isKeyboard", 1);
    icmAddUns64Attr(kb1_attr, "grabDisable", 1);

    icmPseP kb1_p = icmNewPSE(
        "kb1",   // name
        kb1_path,   // model
        kb1_attr,   // attrlist
        0,   // semihost file
        "modelAttrs"    // semihost symbol
    );

    icmConnectPSEBus( kb1_p, smbus_b, "bport1", 0, 0x10006000, 0x10006fff);


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

    icmConnectPSEBus( ms1_p, smbus_b, "bport1", 0, 0x10007000, 0x10007fff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart0
////////////////////////////////////////////////////////////////////////////////

    const char *uart0_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "UartPL011",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP uart0_attr = icmNewAttrList();
    icmAddStringAttr(uart0_attr, "variant", "ARM");
    icmAddStringAttr(uart0_attr, "outfile", "arm-uart0.log");
    if(connectARMUartPort) {
        if(autoConsole) {
            icmAddUns64Attr(uart0_attr, "console", 1);
        } else {
            icmAddUns64Attr(uart0_attr, "portnum", uartPort);
        }
        icmAddUns64Attr(uart0_attr, "finishOnDisconnect", 1);
    }
    icmPseP uart0_p = icmNewPSE(
        "arm-uart0",   // name
        uart0_path,   // model
        uart0_attr,   // attrlist
        NULL,   // semihost file
        NULL    // semihost symbol
    );

    icmConnectPSEBus( uart0_p, smbus_b, "bport1", 0, 0x10009000, 0x10009fff);
    if(connectARMUartPort) {
        icmSetPSEdiagnosticLevel(uart0_p, 1);
    }


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

    icmPseP uart1_p = icmNewPSE(
        "arm-uart1",   // name
        uart1_path,   // model
        uart1_attr,   // attrlist
        NULL,   // semihost file
        NULL    // semihost symbol
    );

    icmConnectPSEBus( uart1_p, smbus_b, "bport1", 0, 0x1000a000, 0x1000afff);


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

    icmPseP uart2_p = icmNewPSE(
        "arm-uart2",   // name
        uart2_path,   // model
        uart2_attr,   // attrlist
        NULL,   // semihost file
        NULL    // semihost symbol
    );

    icmConnectPSEBus( uart2_p, smbus_b, "bport1", 0, 0x1000b000, 0x1000bfff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE uart3
////////////////////////////////////////////////////////////////////////////////

    const char *uart3_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "UartPL011",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP uart3_attr = icmNewAttrList();

    icmAddStringAttr(uart3_attr, "variant", "ARM");

    icmPseP uart3_p = icmNewPSE(
        "arm-uart3",   // name
        uart3_path,   // model
        uart3_attr,   // attrlist
        NULL,   // semihost file
        NULL    // symbol
    );
    icmConnectPSEBus( uart3_p, smbus_b, "bport1", 0, 0x1000c000, 0x1000cfff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE wdt1
////////////////////////////////////////////////////////////////////////////////

    const char *wdt1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "WdtSP805",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP wdt1_attr = icmNewAttrList();


    icmPseP wdt1_p = icmNewPSE(
        "wdt1",   // name
        wdt1_path,   // model
        wdt1_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( wdt1_p, smbus_b, "bport1", 0, 0x1000f000, 0x1000ffff);


////////////////////////////////////////////////////////////////////////////////
//                                 PSE timer01
////////////////////////////////////////////////////////////////////////////////

    const char *timer01_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "TimerSP804",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP timer01_attr = icmNewAttrList();


    icmPseP timer01_p = icmNewPSE(
        "timer01",   // name
        timer01_path,   // model
        timer01_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( timer01_p, smbus_b, "bport1", 0, 0x10011000, 0x10011fff);


////////////////////////////////////////////////////////////////////////////////
//                                 PSE timer23
////////////////////////////////////////////////////////////////////////////////

    const char *timer23_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "TimerSP804",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP timer23_attr = icmNewAttrList();


    icmPseP timer23_p = icmNewPSE(
        "timer23",   // name
        timer23_path,   // model
        timer23_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( timer23_p, smbus_b, "bport1", 0, 0x10012000, 0x10012fff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE dvi1
////////////////////////////////////////////////////////////////////////////////

    const char *dvi1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "SerBusDviRegs",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP dvi1_attr = icmNewAttrList();


    icmPseP dvi1_p = icmNewPSE(
        "dvi1",   // name
        dvi1_path,   // model
        dvi1_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( dvi1_p, smbus_b, "bport1", 0, 0x10016000, 0x10016fff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE rtc1
////////////////////////////////////////////////////////////////////////////////

    const char *rtc1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "RtcPL031",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP rtc1_attr = icmNewAttrList();


    icmPseP rtc1_p = icmNewPSE(
        "rtc1",   // name
        rtc1_path,   // model
        rtc1_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( rtc1_p, smbus_b, "bport1", 0, 0x10017000, 0x10017fff);


////////////////////////////////////////////////////////////////////////////////
//                                   PSE cf1
////////////////////////////////////////////////////////////////////////////////

    const char *cf1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "CompactFlashRegs",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP cf1_attr = icmNewAttrList();


    icmPseP cf1_p = icmNewPSE(
        "cf1",   // name
        cf1_path,   // model
        cf1_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( cf1_p, smbus_b, "bport1", 0, 0x1001a000, 0x1001afff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE lcd1
////////////////////////////////////////////////////////////////////////////////

    const char *lcd1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "LcdPL110",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP lcd1_attr = icmNewAttrList();

//    icmAddUns64Attr(lcd1_attr, "scanDelay", 50000);
    icmAddUns64Attr(lcd1_attr, "noGraphics", noGraphics);
    icmAddStringAttr(lcd1_attr, "resolution", "xga");

    icmPseP lcd1_p = icmNewPSE(
        "lcd1",   // name
        lcd1_path,   // model
        lcd1_attr,   // attrlist
        0,   // semihost file
        "modelAttrs"    // semihost symbol
    );

    icmConnectPSEBus( lcd1_p, smbus_b, "bport1", 0, 0x10020000, 0x10020fff);

    icmConnectPSEBusDynamic( lcd1_p, smbus_b, "memory", 0);


////////////////////////////////////////////////////////////////////////////////
//                                    lcd2
////////////////////////////////////////////////////////////////////////////////


    // Versatile Express contains CLCD controller on both the motherboard and
    // daughterboard.  Rather than 2 instances, map motherboard controller as RAM
    icmMemoryP lcd2_m = icmNewMemory("lcd2_m", 0x7, 0xfff);
    icmConnectMemoryToBus( smbus_b, "sp1", lcd2_m, 0x1001f000);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE dmc1
////////////////////////////////////////////////////////////////////////////////

    const char *dmc1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "DMemCtrlPL341",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP dmc1_attr = icmNewAttrList();


    icmPseP dmc1_p = icmNewPSE(
        "dmc1",   // name
        dmc1_path,   // model
        dmc1_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( dmc1_p, smbus_b, "bport1", 0, 0x100e0000, 0x100e0fff);


////////////////////////////////////////////////////////////////////////////////
//                                  PSE smc1
////////////////////////////////////////////////////////////////////////////////

    const char *smc1_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "SMemCtrlPL354",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP smc1_attr = icmNewAttrList();


    icmPseP smc1_p = icmNewPSE(
        "smc1",   // name
        smc1_path,   // model
        smc1_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( smc1_p, smbus_b, "bport1", 0, 0x100e1000, 0x100e1fff);


////////////////////////////////////////////////////////////////////////////////
//                                 PSE timer45
////////////////////////////////////////////////////////////////////////////////

    const char *timer45_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        0,    // vendor
        0,    // library
        "TimerSP804",    // name
        0,    // version
        "pse"     // model
    );

    icmAttrListP timer45_attr = icmNewAttrList();


    icmPseP timer45_p = icmNewPSE(
        "timer45",   // name
        timer45_path,   // model
        timer45_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( timer45_p, smbus_b, "bport1", 0, 0x100e4000, 0x100e4fff);


////////////////////////////////////////////////////////////////////////////////
//                                PSE eth0
////////////////////////////////////////////////////////////////////////////////

    const char *eth0_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        "smsc.ovpworld.org",    // vendor
        "peripheral",           // library
        "LAN9118",              // name
        "1.0",                  // version
        "pse"                   // model
    );

    icmAttrListP eth0_attr = icmNewAttrList();

    icmPseP eth0_p = icmNewPSE(
        "eth0",   // name
        eth0_path,   // model
        eth0_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( eth0_p, smbus_b, "bport1", 0, 0x4e000000, 0x4e000fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE usb0
////////////////////////////////////////////////////////////////////////////////

    const char *usb0_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        "philips.ovpworld.org",    // vendor
        "peripheral",           // library
        "ISP1761",    // name
        0,    // version
        "pse"     // model
    );
    icmAttrListP usb0_attr = icmNewAttrList();

    icmPseP usb0_p = icmNewPSE(
        "usb0",   // name
        usb0_path,   // model
        usb0_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( usb0_p, smbus_b, "bport1", 0, 0x4f000000, 0x4f00ffff);

   // icmMemoryP m4_m = icmNewMemory("m4_m", 0x7, 0xfff);
   // icmConnectMemoryToBus( smbus_b, "sp1", m4_m, 0x4e000000);

   // icmMemoryP m5_m = icmNewMemory("m5_m", 0x7, 0xfff);
   // icmConnectMemoryToBus( smbus_b, "sp1", m5_m, 0x4f000000);

////////////////////////////////////////////////////////////////////////////////
//                                Memory nor0
////////////////////////////////////////////////////////////////////////////////

    // NOR Flash 0
    icmMemoryP nor0_m = icmNewMemory("nor0_m", ICM_PRIV_RW, 0x03ffffff);
    icmConnectMemoryToBus( smbus_b, "sp1", nor0_m, 0x40000000);

////////////////////////////////////////////////////////////////////////////////
//                                Memory nor1
////////////////////////////////////////////////////////////////////////////////

    // NOR Flash 1
    icmMemoryP nor1_m = icmNewMemory("nor1_m", ICM_PRIV_RW, 0x03ffffff);
    icmConnectMemoryToBus( smbus_b, "sp1", nor1_m, 0x44000000);


////////////////////////////////////////////////////////////////////////////////
//                                Memory sram1
////////////////////////////////////////////////////////////////////////////////

    icmMemoryP sram1_m = icmNewMemory("sram1_m", 0x7, 0x1ffffff);

    icmConnectMemoryToBus( smbus_b, "sp1", sram1_m, 0x48000000);


////////////////////////////////////////////////////////////////////////////////
//                                Memory vram1
////////////////////////////////////////////////////////////////////////////////

    icmMemoryP vram1_m = icmNewMemory("vram1_m", 0x7, 0x7fffff);

    icmConnectMemoryToBus( smbus_b, "sp1", vram1_m, 0x4c000000);


////////////////////////////////////////////////////////////////////////////////
//                               Memory ddr2ram
////////////////////////////////////////////////////////////////////////////////

    icmMemoryP ddr2ram_m = icmNewMemory("ddr2ram_m", 0x7, 0x3fffffff);

    icmConnectMemoryToBus( ddr2bus_b, "sp1", ddr2ram_m, 0x0);


////////////////////////////////////////////////////////////////////////////////
//                            Bridge ddr2RamBridge
////////////////////////////////////////////////////////////////////////////////

    icmNewBusBridge(smbus_b, ddr2bus_b, "ddr2RamBridge", "sp", "mp", 0x0, 0x3fffffff, 0x60000000);


////////////////////////////////////////////////////////////////////////////////
//                           Bridge ddr2RemapBridge
////////////////////////////////////////////////////////////////////////////////

    icmNewBusBridge(smbus_b, ddr2bus_b, "ddr2RemapBridge", "sp1", "mp", 0x20000000, 0x23ffffff, 0x0);


    ////////////////////////////////////////////////////////////////////////////////
    //                                 PSE l2regs
    ////////////////////////////////////////////////////////////////////////////////

        const char *l2regs_path = icmGetVlnvString(
            0,    // path (0 if from the product directory)
            0,    // vendor
            0,    // library
            "L2CachePL310",    // name
            0,    // version
            "pse"     // model
        );

        icmAttrListP l2regs_attr = icmNewAttrList();


        icmPseP l2regs_p = icmNewPSE(
            "l2regs",   // name
            l2regs_path,   // model
            l2regs_attr,   // attrlist
            0,   // semihost file
            0    // semihost symbol
        );

        icmConnectPSEBus( l2regs_p, smbus_b, "bport1", 0, 0x1e00a000, 0x1e00afff);


////////////////////////////////////////////////////////////////////////////////
//                               PSE smartLoader
////////////////////////////////////////////////////////////////////////////////

    const char *smartLoader_path = icmGetVlnvString(
        0,    // path (0 if from the product directory)
        "arm.ovpworld.org",    // vendor
        0,    // library
        "SmartLoaderArmLinux",    // name
        "1.0",    // version
        "pse"     // model
    );

    icmAttrListP smartLoader_attr = icmNewAttrList();

    icmAddStringAttr(smartLoader_attr, "kernel", "zImage");
    icmAddStringAttr(smartLoader_attr, "initrd", "fs.img");

    char command[256] = "mem=1024M raid=noautodetect console=ttyAMA0,38400n8 vmalloc=256MB devtmpfs.mount=0";
    icmAddStringAttr(smartLoader_attr, "command", command);
    icmAddUns64Attr(smartLoader_attr, "memsize", (256*1024*1024));
    icmAddUns64Attr(smartLoader_attr, "physicalbase", 0x60000000);
    icmAddUns64Attr(smartLoader_attr, "boardid", 0x8e0); // Versatile Express
    if(loadBootCode ) {
        icmImagefileP image = icmLoadBus(smbus_b,bootCode,ICM_LOAD_VERBOSE,True);
        if (image) {
            icmAddUns64Attr (smartLoader_attr, "bootaddr", icmGetImagefileEntry(image));
        }
    }


    icmPseP smartLoader_p = icmNewPSE(
        "smartLoader",   // name
        smartLoader_path,   // model
        smartLoader_attr,   // attrlist
        0,   // semihost file
        0    // semihost symbol
    );

    icmConnectPSEBus( smartLoader_p, smbus_b, "mport", 1, 0x0, 0xffffffff);

    // Listed as "Reserved" in data sheet, is used for gpio
    icmMemoryP gpio_m = icmNewMemory("gpio_m", 0x7, 0xfff);
    icmConnectMemoryToBus( smbus_b, "sp1", gpio_m, 0x100e8000);

////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////


    icmNetP cardin_n = icmNewNet("cardin_n" );

    icmConnectPSENet( sysRegs_p, cardin_n, "cardin", ICM_INPUT);

    icmConnectPSENet( mmc1_p, cardin_n, "cardin", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////

    icmNetP wprot_n = icmNewNet("wprot_n" );

    icmConnectPSENet( sysRegs_p, wprot_n, "wprot", ICM_INPUT);

    icmConnectPSENet( mmc1_p, wprot_n, "wprot", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////

    icmNetP ir2_n = icmNewNet("ir2_n" );

    icmConnectProcessorNet( cpu_c, ir2_n, "SPI34", ICM_INPUT);

    icmConnectPSENet( timer01_p, ir2_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir3_n = icmNewNet("ir3_n" );

    icmConnectProcessorNet( cpu_c, ir3_n, "SPI35", ICM_INPUT);

    icmConnectPSENet( timer23_p, ir3_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir4_n = icmNewNet("ir4_n" );

    icmConnectProcessorNet( cpu_c, ir4_n, "SPI36", ICM_INPUT);

    icmConnectPSENet( rtc1_p, ir4_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir5_n = icmNewNet("ir5_n" );

    icmConnectProcessorNet( cpu_c, ir5_n, "SPI37", ICM_INPUT);

    icmConnectPSENet( uart0_p, ir5_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir6_n = icmNewNet("ir6_n" );

    icmConnectProcessorNet( cpu_c, ir6_n, "SPI38", ICM_INPUT);

    icmConnectPSENet( uart1_p, ir6_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir7_n = icmNewNet("ir7_n" );

    icmConnectProcessorNet( cpu_c, ir7_n, "SPI39", ICM_INPUT);

    icmConnectPSENet( uart2_p, ir7_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir8_n = icmNewNet("ir8_n" );

    icmConnectProcessorNet( cpu_c, ir8_n, "SPI40", ICM_INPUT);

    icmConnectPSENet( uart3_p, ir8_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir9_n = icmNewNet("ir9_n" );

    icmConnectProcessorNet( cpu_c, ir9_n, "SPI41", ICM_INPUT);

    icmConnectPSENet( mmc1_p, ir9_n, "irq0", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir10_n = icmNewNet("ir10_n" );

    icmConnectProcessorNet( cpu_c, ir10_n, "SPI42", ICM_INPUT);

    icmConnectPSENet( mmc1_p, ir10_n, "irq1", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir12_n = icmNewNet("ir12_n" );

    icmConnectProcessorNet( cpu_c, ir12_n, "SPI44", ICM_INPUT);

    icmConnectPSENet( kb1_p, ir12_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir13_n = icmNewNet("ir13_n" );

    icmConnectProcessorNet( cpu_c, ir13_n, "SPI45", ICM_INPUT);

    icmConnectPSENet( ms1_p, ir13_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir15_n = icmNewNet("ir15_n" );

    icmConnectProcessorNet( cpu_c, ir15_n, "SPI47", ICM_INPUT);

    icmConnectPSENet( eth0_p, ir15_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
   icmNetP ir16_n = icmNewNet("ir16_n" );

   icmConnectProcessorNet( cpu_c, ir16_n, "SPI48", ICM_INPUT);

   icmConnectPSENet( usb0_p, ir16_n, "hc_irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir44_n = icmNewNet("ir44_n" );

    icmConnectProcessorNet( cpu_c, ir44_n, "SPI76", ICM_INPUT);

    icmConnectPSENet( lcd1_p, ir44_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////
    icmNetP ir48_n = icmNewNet("ir48_n" );

    icmConnectProcessorNet( cpu_c, ir48_n, "SPI80", ICM_INPUT);

    icmConnectPSENet( timer45_p, ir48_n, "irq", ICM_OUTPUT);

////////////////////////////////////////////////////////////////////////////////

    icmIterAllChildren(cpu_c, setStartAddress, 0);

}


void createPlatformXilinx(Uns32 icmAttrs) {

    icmPrintf("createPlatform Xilinx icmAttrs 0x%x\n"
              "  Variant Xilinx %s\n"
              "  Xilinx App %s\n", icmAttrs, xilinxVariantSet ? variantXilinx : "Default", xilinxApp);

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
        if(autoConsole) {
            icmAddUns64Attr(uartX_attr, "console", 1);
        } else {
            icmAddUns64Attr(uartX_attr, "portnum", uartPort);
        }
        icmAddUns64Attr(uartX_attr, "finishOnDisconnect", 1);
    }

    icmPseP uartX_p = icmNewPSE(
        "xilinx-uart",   // name
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


////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[]) {

    // check for the application program name argument
    if((argc<1)) {
        icmPrintf(
           "usage: %s %s\n",
            argv[0], arguments
        );
        return -1;
    }

    parseArgs(1, argc, argv);

    Uns32 icmAttrsArm    = ICM_ATTR_SIMEX;      // simulate exceptions
    Uns32 icmAttrsXilinx = ICM_ATTR_DEFAULT;

    Uns32 icmInitAttrs =   ICM_STOP_ON_CTRLC                 // Ctr-C stops simulation
                         | ICM_VERBOSE                       // Print out statistics on simulation finish
                         | (wallClock ? ICM_WALLCLOCK : 0);  // Do not move time forward when blocked

    // the constructor
    createPlatform(icmInitAttrs);
    createPlatformArm(icmAttrsArm);
    createPlatformXilinx(icmAttrsXilinx);

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
            if (strcmp(argv[++i], "auto") == 0) {
                autoConsole=True;
            } else {
                sscanf(argv[i], "%d", &uartPort);
            }
        } else if (strcmp(argv[i], "stopafter") == 0) {
            sscanf(argv[++i], "%f", &stopafter);
        } else if (strcmp(argv[i], "xilinxapp") == 0) {
            sscanf(argv[++i], "%s", xilinxApp);
        } else if (strcmp(argv[i], "nographics") == 0) {
            noGraphics = True;
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
        } else if (strcmp(argv[i], "B") == 0) {
            sscanf(argv[++i], "%s", bootCode);
            loadBootCode = True;
        } else if (strcmp(argv[i], "SD") == 0) {
             sscanf(argv[++i], "%s", sdCardImage);
             loadSDCard=True;
        } else {
            fprintf(stderr, "unrecognised argument %s\n", argv[i]);
            exit(1);
        }
    }
}




ICM_SMP_ITERATOR_FN(setStartAddress) {

    Uns32 start = 0x60000000;
    icmMessage("I", "STARTUP", "Set start address for %s to 0x%08x", icmGetProcessorName(processor, ""), start);
    icmSetPC(processor, start);
}
