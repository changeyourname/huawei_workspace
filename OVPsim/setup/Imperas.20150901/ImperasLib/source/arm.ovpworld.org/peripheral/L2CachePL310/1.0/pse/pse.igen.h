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
    } reg0_cache_id;
    union { 
        Uns32 value;
    } reg0_cache_type;
    union { 
        Uns32 value;
    } reg1_control;
    union { 
        Uns32 value;
    } reg1_aux_control;
    union { 
        Uns32 value;
    } reg1_tag_ram_control;
    union { 
        Uns32 value;
    } reg1_data_ram_control;
    union { 
        Uns32 value;
    } reg2_ev_counter_ctrl;
    union { 
        Uns32 value;
    } reg2_ev_counter1_cfg;
    union { 
        Uns32 value;
    } reg2_ev_counter0_cfg;
    union { 
        Uns32 value;
    } reg2_ev_counter1;
    union { 
        Uns32 value;
    } reg2_ev_counter0;
    union { 
        Uns32 value;
    } reg2_int_maske;
    union { 
        Uns32 value;
    } reg2_int_mask_statuse;
    union { 
        Uns32 value;
    } reg2_int_raw_statuse;
    union { 
        Uns32 value;
    } reg2_int_cleare;
    union { 
        Uns32 value;
    } reg7_cache_sync;
    union { 
        Uns32 value;
    } reg7_inv_pa;
    union { 
        Uns32 value;
    } reg7_inv_way;
    union { 
        Uns32 value;
    } reg7_clean_pa;
    union { 
        Uns32 value;
    } reg7_clean_index;
    union { 
        Uns32 value;
    } reg7_clean_way;
    union { 
        Uns32 value;
    } reg7_clean_inv_pa;
    union { 
        Uns32 value;
    } reg7_clean_inv_index;
    union { 
        Uns32 value;
    } reg7_clean_inv_way;
    union { 
        Uns32 value;
    } reg9_d_lockdown0;
    union { 
        Uns32 value;
    } reg9_i_lockdown0;
    union { 
        Uns32 value;
    } reg9_d_lockdown1f;
    union { 
        Uns32 value;
    } reg9_i_lockdown1f;
    union { 
        Uns32 value;
    } reg9_d_lockdown2f;
    union { 
        Uns32 value;
    } reg9_i_lockdown2f;
    union { 
        Uns32 value;
    } reg9_d_lockdown3f;
    union { 
        Uns32 value;
    } reg9_i_lockdown3f;
    union { 
        Uns32 value;
    } reg9_d_lockdown4f;
    union { 
        Uns32 value;
    } reg9_i_lockdown4f;
    union { 
        Uns32 value;
    } reg9_d_lockdown5f;
    union { 
        Uns32 value;
    } reg9_i_lockdown5f;
    union { 
        Uns32 value;
    } reg9_d_lockdown6f;
    union { 
        Uns32 value;
    } reg9_i_lockdown6f;
    union { 
        Uns32 value;
    } reg9_d_lockdown7f;
    union { 
        Uns32 value;
    } reg9_i_lockdown7f;
    union { 
        Uns32 value;
    } reg9_lock_line_eng;
    union { 
        Uns32 value;
    } reg9_unlock_wayg;
    union { 
        Uns32 value;
    } reg12_addr_filt_start;
    union { 
        Uns32 value;
    } reg12_addr_filt_end;
    union { 
        Uns32 value;
    } reg15_debug_ctrl;
    union { 
        Uns32 value;
    } reg15_prefetch_ctrl;
    union { 
        Uns32 value;
    } reg15_power_ctrl;
} bport1_ab_dataT, *bport1_ab_dataTP;

/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

#ifdef _PSE_
///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readAux);
PPM_REG_READ_CB(readCleanInvWay);
PPM_REG_READ_CB(readCleanWay);
PPM_REG_READ_CB(readCtrl);
PPM_REG_READ_CB(readId);
PPM_REG_READ_CB(readInvWay);
PPM_REG_READ_CB(readType);
PPM_REG_WRITE_CB(writeAux);
PPM_REG_WRITE_CB(writeCtrl);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);

#endif

#endif
