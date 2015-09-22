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
    } RX_DATA_FIFO;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_1;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_2;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_3;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_4;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_5;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_6;
    union { 
        Uns32 value;
    } RX_DATA_FIFO_7;
    union { 
        Uns32 value;
    } TX_DATA_FIFO;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_1;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_2;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_3;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_4;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_5;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_6;
    union { 
        Uns32 value;
    } TX_DATA_FIFO_7;
    union { 
        Uns32 value;
    } RX_STATUS_FIFO;
    union { 
        Uns32 value;
    } RX_STATUS_FIFO_PEEK;
    union { 
        Uns32 value;
    } TX_STATUS_FIFO;
    union { 
        Uns32 value;
    } TX_STATUS_FIFO_PEEK;
    union { 
        Uns32 value;
        struct {
            unsigned REV : 16;
            unsigned ID : 16;
        } bits;
    } ID_REV;
    union { 
        Uns32 value;
        struct {
            unsigned IRQ_TYPE : 1;
            unsigned __pad1 : 3;
            unsigned IRQ_POL : 1;
            unsigned __pad5 : 3;
            unsigned IRQ_EN : 1;
            unsigned __pad9 : 3;
            unsigned IRQ_INT : 1;
            unsigned INT_DEAS_STS : 1;
            unsigned INT_DEAS_CLR : 1;
            unsigned __pad15 : 9;
            unsigned INT_DEAS : 8;
        } bits;
    } IRQ_CFG;
    union { 
        Uns32 value;
        struct {
            unsigned GPIOx_INT : 3;
            unsigned RSFL : 1;
            unsigned RSFF : 1;
            unsigned __pad5 : 1;
            unsigned RXDF_INT : 1;
            unsigned TSFL : 1;
            unsigned TSFF : 1;
            unsigned TDFA : 1;
            unsigned TDFO : 1;
            unsigned __pad11 : 2;
            unsigned TXE : 1;
            unsigned RXE : 1;
            unsigned RWT : 1;
            unsigned TXSO : 1;
            unsigned PME_INT : 1;
            unsigned PHY_INT : 1;
            unsigned GPT_INT : 1;
            unsigned RXD_INT : 1;
            unsigned TX_IOC : 1;
            unsigned __pad22 : 1;
            unsigned RXDFH_INT : 1;
            unsigned RXSTOP_INT : 1;
            unsigned TXSTOP_INT : 1;
            unsigned __pad26 : 5;
            unsigned SW_INT : 1;
        } bits;
    } INT_STS;
    union { 
        Uns32 value;
        struct {
            unsigned GPIOx_INT_EN : 3;
            unsigned RSFL_INT_EN : 1;
            unsigned RSFF_INT_EN : 1;
            unsigned __pad5 : 1;
            unsigned RXDF_INT_EN : 1;
            unsigned TSFL_INT_EN : 1;
            unsigned TSFF_INT_EN : 1;
            unsigned TDFA_INT_EN : 1;
            unsigned TDFO_INT_EN : 1;
            unsigned __pad11 : 2;
            unsigned TXE_INT_EN : 1;
            unsigned RXE_INT_EN : 1;
            unsigned RWT_INT_EN : 1;
            unsigned TXSO_EN : 1;
            unsigned PME_INT_EN : 1;
            unsigned PHY_INT_EN : 1;
            unsigned GPT_INT_EN : 1;
            unsigned RXD_INT : 1;
            unsigned TIOC_INT_EN : 1;
            unsigned __pad22 : 1;
            unsigned RXDFH_INT_EN : 1;
            unsigned RXSTOP_INT_EN : 1;
            unsigned TXSTOP_INT_EN : 1;
            unsigned __pad26 : 5;
            unsigned SW_INT_EN : 1;
        } bits;
    } INT_EN;
    union { 
        Uns32 value;
    } BYTE_TEST;
    union { 
        Uns32 value;
        struct {
            unsigned RXStatusL : 8;
            unsigned __pad8 : 8;
            unsigned TXStatusL : 8;
            unsigned TXDataAvailL : 8;
        } bits;
    } FIFO_INT;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 8;
            unsigned RXDOFF : 5;
            unsigned __pad13 : 2;
            unsigned RX_DUMP : 1;
            unsigned RX_DMA_CNT : 12;
            unsigned __pad28 : 2;
            unsigned RXEndAlign : 2;
        } bits;
    } RX_CFG;
    union { 
        Uns32 value;
        struct {
            unsigned STOP_TX : 1;
            unsigned TX_ON : 1;
            unsigned TXSAO : 1;
            unsigned __pad3 : 11;
            unsigned TXD_DUMP : 1;
            unsigned TXS_DUMP : 1;
        } bits;
    } TX_CFG;
    union { 
        Uns32 value;
        struct {
            unsigned SRST : 1;
            unsigned SRST_TO : 1;
            unsigned MODE1632 : 1;
            unsigned __pad3 : 13;
            unsigned TX_FIF_SZ : 4;
            unsigned MBO : 1;
        } bits;
    } HW_CFG;
    union { 
        Uns32 value;
        struct {
            unsigned __pad0 : 31;
            unsigned RX_FFWD : 1;
        } bits;
    } RX_DP_CTRL;
    union { 
        Uns32 value;
        struct {
            unsigned RXDUSED : 16;
            unsigned RXSUSED : 8;
        } bits;
    } RX_FIFO_INF;
    union { 
        Uns32 value;
        struct {
            unsigned TXDFREE : 16;
            unsigned TXSUSED : 8;
        } bits;
    } TX_FIFO_INF;
    union { 
        Uns32 value;
        struct {
            unsigned READY : 1;
            unsigned PME_EN : 1;
            unsigned PME_POL : 1;
            unsigned PME_IND : 1;
            unsigned WUPS : 2;
            unsigned PME_TYPE : 1;
            unsigned __pad7 : 1;
            unsigned ED_EN : 1;
            unsigned WOL_EN : 1;
            unsigned PHY_RST : 1;
            unsigned __pad11 : 1;
            unsigned PM_MODE : 2;
        } bits;
    } PMT_CTRL;
    union { 
        Uns32 value;
        struct {
            unsigned GPIODn : 3;
            unsigned GPODn : 2;
            unsigned __pad5 : 3;
            unsigned GPDIRn : 3;
            unsigned __pad11 : 5;
            unsigned GPIOBUFn : 3;
            unsigned __pad19 : 1;
            unsigned EEPR_EN : 3;
            unsigned __pad23 : 1;
            unsigned GPIO_INT_POL : 3;
            unsigned __pad27 : 1;
            unsigned LEDx_EN : 3;
        } bits;
    } GPIO_CFG;
    union { 
        Uns32 value;
        struct {
            unsigned GPT_LOAD : 16;
            unsigned __pad16 : 13;
            unsigned TIMER_EN : 1;
        } bits;
    } GPT_CFG;
    union { 
        Uns32 value;
        struct {
            unsigned GPT_CNT : 16;
        } bits;
    } GPT_CNT;
    union { 
        Uns32 value;
    } WORD_SWAP;
    union { 
        Uns32 value;
        struct {
            unsigned FR_CNT : 32;
        } bits;
    } FREE_RUN;
    union { 
        Uns32 value;
        struct {
            unsigned RX_DFC : 32;
        } bits;
    } RX_DROP;
    union { 
        Uns32 value;
        struct {
            unsigned CSRAddress : 8;
            unsigned __pad8 : 22;
            unsigned RnW : 1;
            unsigned CSRBusy : 1;
        } bits;
    } MAC_CSR_CMD;
    union { 
        Uns32 value;
        struct {
            unsigned MACCSRData : 32;
        } bits;
    } MAC_CSR_DATA;
    union { 
        Uns32 value;
        struct {
            unsigned FCANY : 1;
            unsigned FCADD : 1;
            unsigned FCBRD : 1;
            unsigned FCMULT : 1;
            unsigned BACK_DUR : 4;
            unsigned AFC_LO : 8;
            unsigned AFC_HI : 8;
        } bits;
    } AFC_CFG;
    union { 
        Uns32 value;
        struct {
            unsigned EPCAddr : 8;
            unsigned MACAddrLoaded : 1;
            unsigned EPCTimeout : 1;
            unsigned __pad10 : 18;
            unsigned EPCcommand : 3;
            unsigned EPCBusy : 1;
        } bits;
    } E2P_CMD;
    union { 
        Uns32 value;
        struct {
            unsigned EEPROMData : 8;
        } bits;
    } E2P_DATA;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(byteTest);
PPM_REG_READ_CB(defaultRdCB);
PPM_REG_WRITE_CB(defaultWrCB);
PPM_REG_READ_CB(hwCfgRd);
PPM_REG_WRITE_CB(hwCfgWr);
PPM_REG_READ_CB(idRev);
PPM_REG_READ_CB(intEnRd);
PPM_REG_WRITE_CB(intEnWr);
PPM_REG_READ_CB(intStsRd);
PPM_REG_WRITE_CB(intStsWr);
PPM_REG_READ_CB(irqCfgRd);
PPM_REG_WRITE_CB(irqCfgWr);
PPM_REG_READ_CB(macCsrCmdRd);
PPM_REG_WRITE_CB(macCsrCmdWr);
PPM_REG_READ_CB(macCsrDataRd);
PPM_REG_WRITE_CB(macCsrDataWr);
PPM_REG_READ_CB(rxCfgRd);
PPM_REG_WRITE_CB(rxCfgWr);
PPM_REG_READ_CB(rxDropRd);
PPM_REG_READ_CB(rxFifoInfRd);
PPM_REG_READ_CB(rxFifoRd);
PPM_REG_READ_CB(rxStatusFifoPeek);
PPM_REG_READ_CB(rxStatusFifoRd);
PPM_REG_READ_CB(txCfgRd);
PPM_REG_WRITE_CB(txCfgWr);
PPM_REG_READ_CB(txFifoInfRd);
PPM_REG_WRITE_CB(txFifoWr);
PPM_REG_READ_CB(txStatusFifoPeek);
PPM_REG_READ_CB(txStatusFifoRd);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
