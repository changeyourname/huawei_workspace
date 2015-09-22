/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                              Version 99999999
//                          Thu Aug  7 11:47:06 2014
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DMAC_IGEN_H
#define DMAC_IGEN_H

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

//////////////////////////////////// Externs ///////////////////////////////////

    extern Uns32 diagnosticLevel;

/////////////////////////// Register data declaration //////////////////////////

typedef struct DMACSP_ab8_dataS { 
    union { 
        Uns8 value;
    } intStatus;
    union { 
        Uns8 value;
    } intTCstatus;
    union { 
        Uns8 value;
    } intErrStatus;
    union { 
        Uns8 value;
    } rawTCstatus;
    union { 
        Uns8 value;
    } rawErrStatus;
    union { 
        Uns8 value;
    } enbldChns;
    union { 
        Uns8 value;
        struct {
            unsigned burstSize : 2;
        } bits;
    } config;
} DMACSP_ab8_dataT, *DMACSP_ab8_dataTP;

typedef struct DMACSP_ab32ch0_dataS { 
    union { 
        Uns32 value;
    } srcAddr;
    union { 
        Uns32 value;
    } dstAddr;
    union { 
        Uns32 value;
    } LLI;
    union { 
        Uns32 value;
        struct {
            unsigned transferSize : 12;
        } bits;
    } control;
    union { 
        Uns32 value;
        struct {
            unsigned enable : 1;
            unsigned __pad1 : 14;
            unsigned inten : 1;
            unsigned __pad16 : 2;
            unsigned halt : 1;
        } bits;
    } config;
} DMACSP_ab32ch0_dataT, *DMACSP_ab32ch0_dataTP;

typedef struct DMACSP_ab32ch1_dataS { 
    union { 
        Uns32 value;
    } srcAddr;
    union { 
        Uns32 value;
    } dstAddr;
    union { 
        Uns32 value;
    } LLI;
    union { 
        Uns32 value;
        struct {
            unsigned transferSize : 12;
        } bits;
    } control;
    union { 
        Uns32 value;
        struct {
            unsigned enable : 1;
            unsigned __pad1 : 17;
            unsigned halt : 1;
        } bits;
    } config;
} DMACSP_ab32ch1_dataT, *DMACSP_ab32ch1_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern DMACSP_ab8_dataT DMACSP_ab8_data;

extern DMACSP_ab32ch0_dataT DMACSP_ab32ch0_data;

extern DMACSP_ab32ch1_dataT DMACSP_ab32ch1_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle MREAD;
    ppmAddressSpaceHandle MWRITE;
    void                 *DMACSP;
    ppmNetHandle          INTTC;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(TCclearWr);
PPM_REG_WRITE_CB(configCh0Wr);
PPM_REG_WRITE_CB(configCh1Wr);
PPM_REG_WRITE_CB(configWr);
PPM_REG_WRITE_CB(errClearWr);
PPM_REG_READ_CB(regRd32);
PPM_REG_READ_CB(regRd8);
PPM_REG_WRITE_CB(regWr32);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);

#endif

#endif
