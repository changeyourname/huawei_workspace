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
            unsigned __pad0 : 2;
            unsigned DSADDR : 30;
        } bits;
    } DSADDR;
    union { 
        Uns32 value;
        struct {
            unsigned BLKSIZE : 13;
            unsigned __pad13 : 3;
            unsigned BLKCNT : 16;
        } bits;
    } BLKATTR;
    union { 
        Uns32 value;
        struct {
            unsigned CMDARG : 32;
        } bits;
    } CMDARG;
    union { 
        Uns32 value;
        struct {
            unsigned DMAEN : 1;
            unsigned BCEN : 1;
            unsigned AC12EN : 1;
            unsigned __pad3 : 1;
            unsigned DTDSEL : 1;
            unsigned MSBSEL : 1;
            unsigned __pad6 : 10;
            unsigned RSPTYP : 2;
            unsigned __pad18 : 1;
            unsigned CCCEN : 1;
            unsigned CICEN : 1;
            unsigned DPSEL : 1;
            unsigned CMDTYP : 2;
            unsigned CMDINX : 6;
        } bits;
    } XFERTYP;
    union { 
        Uns32 value;
        struct {
            unsigned CMDRSP0 : 32;
        } bits;
    } CMDRSP0;
    union { 
        Uns32 value;
        struct {
            unsigned CMDRSP1 : 32;
        } bits;
    } CMDRSP1;
    union { 
        Uns32 value;
        struct {
            unsigned CMDRSP2 : 32;
        } bits;
    } CMDRSP2;
    union { 
        Uns32 value;
        struct {
            unsigned CMDRSP3 : 32;
        } bits;
    } CMDRSP3;
    union { 
        Uns32 value;
        struct {
            unsigned DATCONT : 32;
        } bits;
    } DATPORT;
    union { 
        Uns32 value;
        struct {
            unsigned CIHB : 1;
            unsigned CDIHB : 1;
            unsigned DLA : 1;
            unsigned SDSTB : 1;
            unsigned IPGOFF : 1;
            unsigned HCKOFF : 1;
            unsigned PEROFF : 1;
            unsigned SDOFF : 1;
            unsigned WTA : 1;
            unsigned RTA : 1;
            unsigned BWEN : 1;
            unsigned BREN : 1;
            unsigned __pad12 : 4;
            unsigned CINS : 1;
            unsigned __pad17 : 6;
            unsigned CLSL : 1;
            unsigned DLSL : 8;
        } bits;
    } PRSSTAT;
    union { 
        Uns32 value;
        struct {
            unsigned LCTL : 1;
            unsigned DTW : 2;
            unsigned D3CD : 1;
            unsigned EMODE : 2;
            unsigned CDTL : 1;
            unsigned CDSS : 1;
            unsigned DMAS : 2;
            unsigned __pad10 : 6;
            unsigned SABGREQ : 1;
            unsigned CREQ : 1;
            unsigned RWCTL : 1;
            unsigned IABG : 1;
            unsigned __pad20 : 4;
            unsigned WECINT : 1;
            unsigned WECINS : 1;
            unsigned WECRM : 1;
        } bits;
    } PROCTL;
    union { 
        Uns32 value;
        struct {
            unsigned IPGEN : 1;
            unsigned HCKEN : 1;
            unsigned PEREN : 1;
            unsigned SDCLKEN : 1;
            unsigned DVS : 4;
            unsigned SDCLKFS : 8;
            unsigned DTOCV : 4;
            unsigned __pad20 : 4;
            unsigned RSTA : 1;
            unsigned RSTC : 1;
            unsigned RSTD : 1;
            unsigned INITA : 1;
        } bits;
    } SYSCTL;
    union { 
        Uns32 value;
        struct {
            unsigned CC : 1;
            unsigned TC : 1;
            unsigned BGE : 1;
            unsigned DINT : 1;
            unsigned BWR : 1;
            unsigned BRR : 1;
            unsigned CINS : 1;
            unsigned CRM : 1;
            unsigned CINT : 1;
            unsigned __pad9 : 7;
            unsigned CTOE : 1;
            unsigned CCE : 1;
            unsigned CEBE : 1;
            unsigned CIE : 1;
            unsigned DTOE : 1;
            unsigned DCE : 1;
            unsigned DEBE : 1;
            unsigned __pad23 : 1;
            unsigned AC12E : 1;
            unsigned __pad25 : 3;
            unsigned DMAE : 1;
        } bits;
    } IRQSTAT;
    union { 
        Uns32 value;
        struct {
            unsigned CCSEN : 1;
            unsigned TCSEN : 1;
            unsigned BGESEN : 1;
            unsigned DINTSEN : 1;
            unsigned BWRSEN : 1;
            unsigned BRRSEN : 1;
            unsigned CINSEN : 1;
            unsigned CRMSEN : 1;
            unsigned CINTSEN : 1;
            unsigned __pad9 : 7;
            unsigned CTOESEN : 1;
            unsigned CCESEN : 1;
            unsigned CEBESEN : 1;
            unsigned CIESEN : 1;
            unsigned DTOESEN : 1;
            unsigned DCESEN : 1;
            unsigned DEBESEN : 1;
            unsigned __pad23 : 1;
            unsigned AC12ESEN : 1;
            unsigned __pad25 : 3;
            unsigned DMAESEN : 1;
        } bits;
    } IRQSTATEN;
    union { 
        Uns32 value;
        struct {
            unsigned CCIEN : 1;
            unsigned TCIEN : 1;
            unsigned BGEIEN : 1;
            unsigned DINTIEN : 1;
            unsigned BWRIEN : 1;
            unsigned BRRIEN : 1;
            unsigned CINSIEN : 1;
            unsigned CRMIEN : 1;
            unsigned CINTIEN : 1;
            unsigned __pad9 : 7;
            unsigned CTOEIEN : 1;
            unsigned CCEIEN : 1;
            unsigned CEBEIEN : 1;
            unsigned CIEIEN : 1;
            unsigned DTOEIEN : 1;
            unsigned DCEIEN : 1;
            unsigned DEBEIEN : 1;
            unsigned __pad23 : 1;
            unsigned AC12EIEN : 1;
            unsigned __pad25 : 3;
            unsigned DMAEIEN : 1;
        } bits;
    } IRQSIGEN;
    union { 
        Uns32 value;
        struct {
            unsigned AC12NE : 1;
            unsigned AC12TOE : 1;
            unsigned AC12EBE : 1;
            unsigned AC12CE : 1;
            unsigned AC12IE : 1;
            unsigned __pad5 : 2;
            unsigned CNIBAC12E : 1;
        } bits;
    } AC12ERR;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 16;
            unsigned MBL : 3;
            unsigned __pad19 : 1;
            unsigned ADMAS : 1;
            unsigned HSS : 1;
            unsigned DMAS : 1;
            unsigned SRS : 1;
            unsigned VS33 : 1;
            unsigned VS30 : 1;
            unsigned VS18 : 1;
        } bits;
    } HTCAPBLT;
    union { 
        Uns32 value;
        struct {
            unsigned RDWML : 8;
            unsigned __pad8 : 8;
            unsigned WRWML : 8;
            unsigned WRBRSTLEN : 5;
        } bits;
    } WML;
    union { 
        Uns32 value;
        struct {
            unsigned AC12NE : 1;
            unsigned AC12TOE : 1;
            unsigned AC12CE : 1;
            unsigned AC12EBE : 1;
            unsigned AC12IE : 1;
            unsigned __pad5 : 2;
            unsigned CNIBAC12E : 1;
            unsigned __pad8 : 8;
            unsigned CTOE : 1;
            unsigned CCE : 1;
            unsigned CEBE : 1;
            unsigned CIE : 1;
            unsigned DTOE : 1;
            unsigned DCE : 1;
            unsigned DEBE : 1;
            unsigned __pad23 : 1;
            unsigned AC12E : 1;
            unsigned __pad25 : 3;
            unsigned DMAE : 1;
            unsigned __pad29 : 2;
            unsigned CINT : 1;
        } bits;
    } FEVT;
    union { 
        Uns32 value;
        struct {
            unsigned ADMAES : 2;
            unsigned ADMALME : 1;
            unsigned ADMADCE : 1;
        } bits;
    } ADMAES;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 2;
            unsigned ADSADDR : 30;
        } bits;
    } ADSADDR;
    union { 
        Uns32 value;
        struct {
            unsigned EXTDMAEN : 1;
            unsigned EXBLKNU : 1;
            unsigned __pad2 : 14;
            unsigned INTSTVAL : 8;
        } bits;
    } VENDOR;
    union { 
        Uns32 value;
        struct {
            unsigned DTOCVACK : 4;
            unsigned BOOTACK : 1;
            unsigned BOOTMODE : 1;
            unsigned BOOTEN : 1;
            unsigned AUTOSABGEN : 1;
            unsigned __pad8 : 8;
            unsigned BOOTBLKCNT : 16;
        } bits;
    } MMCBOOT;
    union { 
        Uns32 value;
        struct {
            unsigned SVN : 8;
            unsigned VVN : 8;
        } bits;
    } HOSTVER;
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
