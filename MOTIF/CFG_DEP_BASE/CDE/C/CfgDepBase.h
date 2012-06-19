/* Copyright (c) 1985-2012, B-Core (UK) Ltd
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
extern int CfgDepBaseP1;
extern int CfgDepBaseP2;
extern int CfgDepBaseP3;
extern int CfgDepBaseP4;
extern int CfgDepBaseP5;
extern int CfgDepBaseP6;
extern char * CfgDepBaseP7 [];
extern char * CfgDepBaseP8 [];


#include "CfgDepBase_Vffnc.h"
#include "Construct_ffnc_ctx.h"
#include "Construct_ffnc_obj.h"
#include "Abs2Conc_ffnc_ctx.h"
#include "Abs2Conc_ffnc_obj.h"
#include "MRIState_ffnc_ctx.h"
#include "MRIState_ffnc_obj.h"
#include "GENState_ffnc_ctx.h"
#include "GENState_ffnc_obj.h"
#include "Seqstr_ffnc_ctx.h"
#include "Seqstr_ffnc_obj.h"
#include "String_ffnc_ctx.h"
#include "String_ffnc_obj.h"
#include "CfgDepBase_seq_ctx.h"
#include "CfgDepBase_seq_obj.h"
#include "CfgDepBase_str_ctx.h"
#include "CfgDepBase_str_obj.h"
#include "CfgDepBase_set_ctx.h"
#include "CfgDepBase_set_obj.h"
#include "CfgDepBase_token_io.h"

void INI_CfgDepBase();
void save_CfgDepBase();
void restore_CfgDepBase();
void save_n_CfgDepBase();
void restore_n_CfgDepBase();
void print_Globals_CfgDepBase();
void val_gset1();
void card_gset1();
void clear_gset1();
void add_gset1();
void del_gset1();
void member_gset1();
void union_gset1();
void mod_gset1();
void valOrd_gset1();
void val_gset2();
void card_gset2();
void clear_gset2();
void add_gset2();
void del_gset2();
void member_gset2();
void union_gset2();
void valOrd_gset2();
void val_gset3();
void card_gset3();
void clear_gset3();
void add_gset3();
void del_gset3();
void member_gset3();
void union_gset3();
void mod_gset3();
void valOrd_gset3();
void card_gset4();
void clear_gset4();
void add_gset4();
void del_gset4();
void member_gset4();
void union_gset4();
void inter_gset4();
void valOrd_gset4();
void card_gset5();
void clear_gset5();
void add_gset5();
void del_gset5();
void member_gset5();
void valOrd_gset5();
void length_gseq();
void clear_gseq();
void valIth_gseq();
void delIth_gseq();
void push_gseq();
void within_gseq();
void clear_flags();
void valIth_flags();
void modIth_flags();
void push_flags();
void make_Construct();
void kill_Construct();
void print_BaseObj_Construct();
void first_Construct();
void next_Construct();
void vld_Construct();
void nbr_Construct();
void xtr_name();
void mod_name();
void val_ext();
void val_type();
void cre_sees_uses();
void rem_sees_uses();
void def_sees_uses();
void val_sees_uses();
void card_sees_uses();
void member_sees_uses();
void mod_sees_uses();
void valOrd_sees_uses();
void cre_inc_ipt();
void rem_inc_ipt();
void def_inc_ipt();
void val_inc_ipt();
void card_inc_ipt();
void member_inc_ipt();
void mod_inc_ipt();
void valOrd_inc_ipt();
void cre_abs2conc();
void rem_abs2conc();
void def_abs2conc();
void val_abs2conc();
void cre_gen_by();
void def_gen_by();
void val_gen_by();
void eql_gen_by();
void cre_prf_level();
void def_prf_level();
void val_prf_level();
void cre_curMRIState();
void def_curMRIState();
void val_curMRIState();
void cre_cptMRIState();
void def_cptMRIState();
void val_cptMRIState();
void cre_curGENState();
void def_curGENState();
void val_curGENState();
void cre_cptGENState();
void def_cptGENState();
void val_cptGENState();
void make_Abs2Conc();
void kill_Abs2Conc();
void print_BaseObj_Abs2Conc();
void first_Abs2Conc();
void next_Abs2Conc();
void vld_Abs2Conc();
void length_a2c();
void last_a2c();
void valIth_a2c();
void pop_a2c();
void push_a2c();
void make_MRIState();
void kill_MRIState();
void print_BaseObj_MRIState();
void first_MRIState();
void next_MRIState();
void val_anl();
void mod_anl();
void val_dmu();
void mod_dmu();
void val_trl();
void mod_trl();
void val_lnk();
void mod_lnk();
void length_pob();
void clear_pob();
void last_pob();
void valIth_pob();
void modIth_pob();
void pop_pob();
void push_pob();
void card_ppf();
void clear_ppf();
void add_ppf();
void del_ppf();
void member_ppf();
void valOrd_ppf();
void card_ppf_dmu();
void clear_ppf_dmu();
void add_ppf_dmu();
void del_ppf_dmu();
void member_ppf_dmu();
void valOrd_ppf_dmu();
void make_GENState();
void kill_GENState();
void print_BaseObj_GENState();
void first_GENState();
void next_GENState();
void val_gen1();
void mod_gen1();
void val_gen2();
void mod_gen2();
void val_gen_dmu();
void mod_gen_dmu();
void make_Seqstr();
void print_BaseObj_Seqstr();
void first_Seqstr();
void next_Seqstr();
void clear_seqstr();
void valIth_seqstr();
void push_seqstr();
void make_String();
void print_BaseObj_String();
void first_String();
void next_String();
void nbr_String();
void xtr_string();
void mod_string();
