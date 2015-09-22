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

#ifndef PSE_IGEN_H
#define PSE_IGEN_H

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

//////////////////////////////////// Externs ///////////////////////////////////

extern Uns32 diagnosticLevel;


/////////////////////////// Dynamic Diagnostic Macros //////////////////////////

// Bottom two bits of word used for PSE diagnostics
#define PSE_DIAG_LOW      (BHM_DIAG_MASK_LOW(diagnosticLevel))
#define PSE_DIAG_MEDIUM   (BHM_DIAG_MASK_MEDIUM(diagnosticLevel))
#define PSE_DIAG_HIGH     (BHM_DIAG_MASK_HIGH(diagnosticLevel))
// Next two bits of word used for PSE semihost/intercept library diagnostics
#define PSE_DIAG_SEMIHOST (BHM_DIAG_MASK_SEMIHOST(diagnosticLevel))

/////////////////////////// Register data declaration //////////////////////////

typedef struct bport1_ab_dataS { 
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 12;
            unsigned RAMSIZE : 4;
            unsigned __pad16 : 3;
            unsigned OSC32KSEL : 1;
            unsigned __pad20 : 9;
            unsigned USBVSTBY : 1;
            unsigned USBSSTBY : 1;
            unsigned USBREGEN : 1;
        } bits;
    } SOPT1;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 24;
            unsigned URWE : 1;
            unsigned UVSWE : 1;
            unsigned USSWE : 1;
        } bits;
    } SOPT1CFG;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 2;
            unsigned USBHSRC : 2;
            unsigned RTCCLKOUTSEL : 1;
            unsigned CLKOUTSEL : 3;
            unsigned FBSL : 2;
            unsigned USBH_CLKSEL : 1;
            unsigned CMTUARTPAD : 1;
            unsigned TRACECLKSEL : 1;
            unsigned __pad13 : 2;
            unsigned NFC_CLKSEL : 1;
            unsigned PLLFLLSEL : 2;
            unsigned USBF_CLKSEL : 1;
            unsigned __pad19 : 1;
            unsigned TIMESRC : 2;
            unsigned USBFSRC : 2;
            unsigned __pad24 : 4;
            unsigned ESDHCSRC : 2;
            unsigned NFCSRC : 2;
        } bits;
    } SOPT2;
    union { 
        Uns32 value;
        struct {
            unsigned FTM0FLT0 : 1;
            unsigned FTM0FLT1 : 1;
            unsigned FTM0FLT2 : 1;
            unsigned FTM0FLT3 : 1;
            unsigned FTM1FLT0 : 1;
            unsigned __pad5 : 3;
            unsigned FTM2FLT0 : 1;
            unsigned __pad9 : 3;
            unsigned FTM3FLT0 : 1;
            unsigned __pad13 : 5;
            unsigned FTM1CH0SRC : 2;
            unsigned FTM2CH0SRC : 2;
            unsigned __pad22 : 2;
            unsigned FTM0CLKSEL : 1;
            unsigned FTM1CLKSEL : 1;
            unsigned FTM2CLKSEL : 1;
            unsigned FTM3CLKSEL : 1;
            unsigned FTM0TRG0SRC : 1;
            unsigned FTM0TRG1SRC : 1;
            unsigned FTM3TRG0SRC : 1;
            unsigned FTM3TRG1SRC : 1;
        } bits;
    } SOPT4;
    union { 
        Uns32 value;
        struct {
            unsigned UART0TXSRC : 2;
            unsigned UART0RXSRC : 2;
            unsigned UART1TXSRC : 2;
            unsigned UART1RXSRC : 2;
        } bits;
    } SOPT5;
    union { 
        Uns32 value;
        struct {
            unsigned MCC : 16;
            unsigned PCR : 4;
            unsigned __pad20 : 4;
            unsigned RSTFLTSEL : 5;
            unsigned RSTFLTEN : 3;
        } bits;
    } SOPT6;
    union { 
        Uns32 value;
        struct {
            unsigned ADC0TRGSEL : 4;
            unsigned ADC0PRETRGSEL : 1;
            unsigned __pad5 : 2;
            unsigned ADC0ALTTRGEN : 1;
            unsigned ADC1TRGSEL : 4;
            unsigned ADC1PRETRGSEL : 1;
            unsigned __pad13 : 2;
            unsigned ADC1ALTTRGEN : 1;
            unsigned ADC2TRGSEL : 4;
            unsigned ADC2PRETRGSEL : 1;
            unsigned __pad21 : 2;
            unsigned ADC2ALTTRGEN : 1;
            unsigned ADC3TRGSEL : 4;
            unsigned ADC3PRETRGSEL : 1;
            unsigned __pad29 : 2;
            unsigned ADC3ALTTRGEN : 1;
        } bits;
    } SOPT7;
    union { 
        Uns32 value;
        struct {
            unsigned PINID : 4;
            unsigned FAMID : 3;
            unsigned __pad7 : 5;
            unsigned REVID : 4;
        } bits;
    } SDID;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 5;
            unsigned OSC1 : 1;
            unsigned __pad6 : 4;
            unsigned UART4 : 1;
            unsigned UART5 : 1;
        } bits;
    } SCGC1;
    union { 
        Uns32 value;
        struct {
            unsigned ENET : 1;
            unsigned __pad1 : 11;
            unsigned DAC0 : 1;
            unsigned DAC1 : 1;
        } bits;
    } SCGC2;
    union { 
        Uns32 value;
        struct {
            unsigned RNGA : 1;
            unsigned __pad1 : 3;
            unsigned FLEXCAN1 : 1;
            unsigned __pad5 : 3;
            unsigned NFC : 1;
            unsigned __pad9 : 3;
            unsigned DSPI2 : 1;
            unsigned __pad13 : 1;
            unsigned DDR : 1;
            unsigned SAI1 : 1;
            unsigned __pad16 : 1;
            unsigned ESDHC : 1;
            unsigned __pad18 : 6;
            unsigned FTM2 : 1;
            unsigned FTM3 : 1;
            unsigned __pad26 : 1;
            unsigned ADC1 : 1;
            unsigned ADC3 : 1;
        } bits;
    } SCGC3;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 1;
            unsigned EWM : 1;
            unsigned CMT : 1;
            unsigned __pad3 : 1;
            unsigned MCG : 1;
            unsigned OSC : 1;
            unsigned IIC0 : 1;
            unsigned IIC1 : 1;
            unsigned __pad8 : 2;
            unsigned UART0 : 1;
            unsigned UART1 : 1;
            unsigned UART2 : 1;
            unsigned UART3 : 1;
            unsigned __pad14 : 4;
            unsigned USBFS : 1;
            unsigned CMP : 1;
            unsigned VREF : 1;
            unsigned __pad21 : 7;
            unsigned LLWU : 1;
            unsigned PMC : 1;
            unsigned SMC : 1;
            unsigned RCM : 1;
        } bits;
    } SCGC4;
    union { 
        Uns32 value;
        struct {
            unsigned LPTIMER : 1;
            unsigned REGFILE : 1;
            unsigned DRYICE : 1;
            unsigned DRYICESECREG : 1;
            unsigned __pad4 : 1;
            unsigned TSI : 1;
            unsigned ATX : 1;
            unsigned SIMDGO : 1;
            unsigned SIM : 1;
            unsigned PORTA : 1;
            unsigned PORTB : 1;
            unsigned PORTC : 1;
            unsigned PORTD : 1;
            unsigned PORTE : 1;
            unsigned PORTF : 1;
            unsigned __pad15 : 3;
            unsigned WDT : 1;
        } bits;
    } SCGC5;
    union { 
        Uns32 value;
        struct {
            unsigned FTF : 1;
            unsigned DMAMUX0 : 1;
            unsigned DMAMUX1 : 1;
            unsigned __pad3 : 1;
            unsigned FLEXCAN0 : 1;
            unsigned __pad5 : 7;
            unsigned DSPI0 : 1;
            unsigned DSPI1 : 1;
            unsigned __pad14 : 1;
            unsigned SAI0 : 1;
            unsigned __pad16 : 2;
            unsigned CRC : 1;
            unsigned __pad19 : 1;
            unsigned USBHS : 1;
            unsigned USBDCD : 1;
            unsigned PDB : 1;
            unsigned PIT : 1;
            unsigned FTM0 : 1;
            unsigned FTM1 : 1;
            unsigned __pad26 : 1;
            unsigned ADC0 : 1;
            unsigned ADC2 : 1;
            unsigned RTC : 1;
        } bits;
    } SCGC6;
    union { 
        Uns32 value;
        struct {
            unsigned FLEXBUS : 1;
            unsigned DMA : 1;
            unsigned MPU : 1;
        } bits;
    } SCGC7;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned OUTDIV4 : 4;
            unsigned OUTDIV3 : 4;
            unsigned OUTDIV2 : 4;
            unsigned OUTDIV1 : 4;
        } bits;
    } CLKDIV1;
    union { 
        Uns32 value;
        struct {
            unsigned USBFSFRAC : 1;
            unsigned USBFSDIV : 3;
            unsigned __pad4 : 4;
            unsigned USBHSFRAC : 1;
            unsigned USBHSDIV : 3;
        } bits;
    } CLKDIV2;
    union { 
        Uns32 value;
        struct {
            unsigned FTFDIS : 1;
            unsigned __pad1 : 7;
            unsigned DEPART : 4;
            unsigned __pad12 : 4;
            unsigned EESIZE : 4;
            unsigned __pad20 : 4;
            unsigned PFSIZE : 4;
            unsigned NVMSIZE : 4;
        } bits;
    } FCFG1;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned MAXADDR23 : 6;
            unsigned __pad22 : 2;
            unsigned MAXADDR01 : 6;
        } bits;
    } FCFG2;
    union { 
        Uns32 value;
        struct {
            unsigned UID : 32;
        } bits;
    } UIDH;
    union { 
        Uns32 value;
        struct {
            unsigned UID : 32;
        } bits;
    } UIDMH;
    union { 
        Uns32 value;
        struct {
            unsigned UID : 32;
        } bits;
    } UIDML;
    union { 
        Uns32 value;
        struct {
            unsigned UID : 32;
        } bits;
    } UIDL;
    union { 
        Uns32 value;
        struct {
            unsigned TRACEFRAC : 1;
            unsigned TRACEDIV : 3;
            unsigned __pad4 : 20;
            unsigned NFCFRAC : 3;
            unsigned NFCDIV : 5;
        } bits;
    } CLKDIV4;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 29;
            unsigned PDBLOOP : 1;
            unsigned ULPICLKOBE : 1;
            unsigned TRACECLKDIS : 1;
        } bits;
    } MCR;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
