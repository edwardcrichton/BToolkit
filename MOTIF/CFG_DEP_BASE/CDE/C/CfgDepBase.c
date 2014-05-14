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
#include "CfgDepBase.h"

#define gset1_idx 1
#define gset2_idx 2
#define gset3_idx 3
#define gset4_idx 4
#define gset5_idx 5
#define gseq_idx 6
#define flags_idx 7
#define name_idx 1
#define ext_idx 2
#define type_idx 3
#define sees_uses_idx 4
#define inc_ipt_idx 5
#define abs2conc_idx 6
#define gen_by_idx 7
#define prf_level_idx 8
#define curMRIState_idx 9
#define cptMRIState_idx 10
#define curGENState_idx 11
#define cptGENState_idx 12
#define a2c_idx 1
#define anl_idx 1
#define dmu_idx 2
#define trl_idx 3
#define lnk_idx 4
#define pob_idx 5
#define ppf_idx 6
#define ppf_dmu_idx 7
#define gen1_idx 1
#define gen2_idx 2
#define gen_dmu_idx 3
#define seqstr_idx 1
#define string_idx 1

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

#include "CfgDepBaseCtx.h"
#include "Scalar_TYPE.h"
#include "Bool_TYPE.h"
#include "String_TYPE.h"
#include "basic_io.h"
#include "CfgDepBase_file_dump.h"
/*Ed:*/
#include <string.h>

void
INI_CfgDepBase()
{
  INI_CfgDepBase_Vffnc();
  INI_Construct_ffnc_ctx();
  INI_Construct_ffnc_obj();
  INI_Abs2Conc_ffnc_ctx();
  INI_Abs2Conc_ffnc_obj();
  INI_MRIState_ffnc_ctx();
  INI_MRIState_ffnc_obj();
  INI_GENState_ffnc_ctx();
  INI_GENState_ffnc_obj();
  INI_Seqstr_ffnc_ctx();
  INI_Seqstr_ffnc_obj();
  INI_String_ffnc_ctx();
  INI_String_ffnc_obj();
  INI_CfgDepBase_seq_ctx();
  INI_CfgDepBase_seq_obj();
  INI_CfgDepBase_str_ctx();
  INI_CfgDepBase_str_obj();
  INI_CfgDepBase_set_ctx();
  INI_CfgDepBase_set_obj();
  INI_CfgDepBase_token_io();
  {
    int bb,Set;
    CfgDepBase_CRE_SET_OBJ(&bb,&Set);
    CfgDepBase_STO_FNC(gset1_idx,Set);
  }
  {
    int bb,Set;
    CfgDepBase_CRE_SET_OBJ(&bb,&Set);
    CfgDepBase_STO_FNC(gset2_idx,Set);
  }
  {
    int bb,Set;
    CfgDepBase_CRE_SET_OBJ(&bb,&Set);
    CfgDepBase_STO_FNC(gset3_idx,Set);
  }
  {
    int bb,Set;
    CfgDepBase_CRE_SET_OBJ(&bb,&Set);
    CfgDepBase_STO_FNC(gset4_idx,Set);
  }
  {
    int bb,Set;
    CfgDepBase_CRE_SET_OBJ(&bb,&Set);
    CfgDepBase_STO_FNC(gset5_idx,Set);
  }
  {
    int bb,Seq;
    CfgDepBase_CRE_SEQ_OBJ(&bb,&Seq);
    CfgDepBase_STO_FNC(gseq_idx,Seq);
  }
  {
    int bb,Seq;
    CfgDepBase_CRE_SEQ_OBJ(&bb,&Seq);
    CfgDepBase_STO_FNC(flags_idx,Seq);
  }
}

void
save_CfgDepBase(_rep)
int *_rep;
{
  int bb;
  CfgDepBase_open_write_dump(&bb);
  if ( bb == TRUE ) {
    CfgDepBase_SAV_FNC();
    Construct_SAV_FNC_OBJ();
    Abs2Conc_SAV_FNC_OBJ();
    MRIState_SAV_FNC_OBJ();
    GENState_SAV_FNC_OBJ();
    Seqstr_SAV_FNC_OBJ();
    String_SAV_FNC_OBJ();
    CfgDepBase_SAV_STR_OBJ();
    CfgDepBase_SAV_SEQ_OBJ();
    CfgDepBase_SAV_SET_OBJ();
    CfgDepBase_close_dump(&bb);
  }
  *_rep = bb;
}

void
restore_CfgDepBase(_rep)
int *_rep;
{
  int bb;
  CfgDepBase_open_read_dump(&bb);
  if ( bb == TRUE ) {
    CfgDepBase_RST_FNC();
    Construct_RST_FNC_OBJ();
    Abs2Conc_RST_FNC_OBJ();
    MRIState_RST_FNC_OBJ();
    GENState_RST_FNC_OBJ();
    Seqstr_RST_FNC_OBJ();
    String_RST_FNC_OBJ();
    CfgDepBase_RST_STR_OBJ();
    CfgDepBase_RST_SEQ_OBJ();
    CfgDepBase_RST_SET_OBJ();
    CfgDepBase_close_dump(&bb);
  }
  *_rep = bb;
}

void
save_n_CfgDepBase(_rep)
int *_rep;
{
  int bb;
  CfgDepBase_open_write_dump(&bb);
  if ( bb == TRUE ) {
    CfgDepBase_SAVN_FNC();
    Construct_SAVN_FNC_OBJ();
    Abs2Conc_SAVN_FNC_OBJ();
    MRIState_SAVN_FNC_OBJ();
    GENState_SAVN_FNC_OBJ();
    Seqstr_SAVN_FNC_OBJ();
    String_SAVN_FNC_OBJ();
    CfgDepBase_SAVN_STR_OBJ();
    CfgDepBase_SAVN_SEQ_OBJ();
    CfgDepBase_SAVN_SET_OBJ();
    CfgDepBase_close_dump(&bb);
  }
  *_rep = bb;
}

void
restore_n_CfgDepBase(_rep)
int *_rep;
{
  int bb;
  CfgDepBase_open_read_dump(&bb);
  if ( bb == TRUE ) {
    CfgDepBase_RSTN_FNC();
    Construct_RSTN_FNC_OBJ();
    Abs2Conc_RSTN_FNC_OBJ();
    MRIState_RSTN_FNC_OBJ();
    GENState_RSTN_FNC_OBJ();
    Seqstr_RSTN_FNC_OBJ();
    String_RSTN_FNC_OBJ();
    CfgDepBase_RSTN_STR_OBJ();
    CfgDepBase_RSTN_SEQ_OBJ();
    CfgDepBase_RSTN_SET_OBJ();
    CfgDepBase_close_dump(&bb);
  }
  *_rep = bb;
}

void
print_Globals_CfgDepBase()
{
  PUT_STR("\n---------------- GLOBAL ----------------\n");
  {
    int setobj,elem,crd,ord;
    BLK(2);
    PUT_STR_PAD("gset1 ",13);
    PUT_STR("{ ");
    CfgDepBase_VAL_FNC(&setobj,gset1_idx);
    CfgDepBase_CRD_SET_OBJ(&crd,setobj);
    ord = 1;
    while ( ord <= crd ) {
      CfgDepBase_VAL_SET_OBJ(&elem,setobj,ord);
      {
        int strobj;
        Construct_VAL_FNC_OBJ(&strobj,elem,name_idx);
        {
          int ss[250];
          CfgDepBase_XTR_STR_OBJ(ss,strobj);
          PUT_STR(ss);
        }
        PUT_STR("(");
        CfgDepBase_PUT_TOK(elem);
        PUT_STR(")");
      }
      BLK(1);
      ord = ord+1;
    }
    PUT_STR("}");
    NWL(1);
  }
  {
    int setobj,elem,crd,ord;
    BLK(2);
    PUT_STR_PAD("gset2 ",13);
    PUT_STR("{ ");
    CfgDepBase_VAL_FNC(&setobj,gset2_idx);
    CfgDepBase_CRD_SET_OBJ(&crd,setobj);
    ord = 1;
    while ( ord <= crd ) {
      CfgDepBase_VAL_SET_OBJ(&elem,setobj,ord);
      {
        int strobj;
        Construct_VAL_FNC_OBJ(&strobj,elem,name_idx);
        {
          int ss[250];
          CfgDepBase_XTR_STR_OBJ(ss,strobj);
          PUT_STR(ss);
        }
        PUT_STR("(");
        CfgDepBase_PUT_TOK(elem);
        PUT_STR(")");
      }
      BLK(1);
      ord = ord+1;
    }
    PUT_STR("}");
    NWL(1);
  }
  {
    int setobj,elem,crd,ord;
    BLK(2);
    PUT_STR_PAD("gset3 ",13);
    PUT_STR("{ ");
    CfgDepBase_VAL_FNC(&setobj,gset3_idx);
    CfgDepBase_CRD_SET_OBJ(&crd,setobj);
    ord = 1;
    while ( ord <= crd ) {
      CfgDepBase_VAL_SET_OBJ(&elem,setobj,ord);
      {
        int strobj;
        Construct_VAL_FNC_OBJ(&strobj,elem,name_idx);
        {
          int ss[250];
          CfgDepBase_XTR_STR_OBJ(ss,strobj);
          PUT_STR(ss);
        }
        PUT_STR("(");
        CfgDepBase_PUT_TOK(elem);
        PUT_STR(")");
      }
      BLK(1);
      ord = ord+1;
    }
    PUT_STR("}");
    NWL(1);
  }
  {
    int setobj,elem,crd,ord;
    BLK(2);
    PUT_STR_PAD("gset4 ",13);
    PUT_STR("{ ");
    CfgDepBase_VAL_FNC(&setobj,gset4_idx);
    CfgDepBase_CRD_SET_OBJ(&crd,setobj);
    ord = 1;
    while ( ord <= crd ) {
      CfgDepBase_VAL_SET_OBJ(&elem,setobj,ord);
      {
        int strobj;
        Construct_VAL_FNC_OBJ(&strobj,elem,name_idx);
        {
          int ss[250];
          CfgDepBase_XTR_STR_OBJ(ss,strobj);
          PUT_STR(ss);
        }
        PUT_STR("(");
        CfgDepBase_PUT_TOK(elem);
        PUT_STR(")");
      }
      BLK(1);
      ord = ord+1;
    }
    PUT_STR("}");
    NWL(1);
  }
  {
    int setobj,elem,crd,ord;
    BLK(2);
    PUT_STR_PAD("gset5 ",13);
    PUT_STR("{ ");
    CfgDepBase_VAL_FNC(&setobj,gset5_idx);
    CfgDepBase_CRD_SET_OBJ(&crd,setobj);
    ord = 1;
    while ( ord <= crd ) {
      CfgDepBase_VAL_SET_OBJ(&elem,setobj,ord);
      {
        int strobj;
        Construct_VAL_FNC_OBJ(&strobj,elem,name_idx);
        {
          int ss[250];
          CfgDepBase_XTR_STR_OBJ(ss,strobj);
          PUT_STR(ss);
        }
        PUT_STR("(");
        CfgDepBase_PUT_TOK(elem);
        PUT_STR(")");
      }
      BLK(1);
      ord = ord+1;
    }
    PUT_STR("}");
    NWL(1);
  }
  {
    int seqobj,elem,len,ith;
    BLK(2);
    PUT_STR_PAD("gseq ",13);
    PUT_STR("[ ");
    CfgDepBase_VAL_FNC(&seqobj,gseq_idx);
    CfgDepBase_LEN_SEQ_OBJ(&len,seqobj);
    ith = 1;
    while ( ith <= len ) {
      CfgDepBase_VAL_SEQ_OBJ(&elem,seqobj,ith);
      {
        int strobj;
        Construct_VAL_FNC_OBJ(&strobj,elem,name_idx);
        {
          int ss[250];
          CfgDepBase_XTR_STR_OBJ(ss,strobj);
          PUT_STR(ss);
        }
        PUT_STR("(");
        CfgDepBase_PUT_TOK(elem);
        PUT_STR(")");
      }
      BLK(1);
      ith = ith+1;
    }
    PUT_STR("]");
    NWL(1);
  }
  {
    int seqobj,elem,len,ith;
    BLK(2);
    PUT_STR_PAD("flags ",13);
    PUT_STR("[ ");
    CfgDepBase_VAL_FNC(&seqobj,flags_idx);
    CfgDepBase_LEN_SEQ_OBJ(&len,seqobj);
    ith = 1;
    while ( ith <= len ) {
      CfgDepBase_VAL_SEQ_OBJ(&elem,seqobj,ith);
      CfgDepBase_PUT_ACT_TOK(SCALAR,elem);
      BLK(1);
      ith = ith+1;
    }
    PUT_STR("]");
    NWL(1);
  }
  PUT_STR("----------------------------------------\n");
}

void
val_gset1(_Set)
int *_Set;
{
  CfgDepBase_VAL_FNC(_Set,gset1_idx);
}

void
card_gset1(_nbr)
int *_nbr;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset1_idx);
  CfgDepBase_CRD_SET_OBJ(_nbr,Set);
}

void
clear_gset1()
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset1_idx);
  CfgDepBase_CLR_SET_OBJ(Set);
}

void
add_gset1(_rep,_Elem_Construct)
int *_rep,_Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset1_idx);
  CfgDepBase_ENT_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
del_gset1(_Elem_Construct)
int _Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset1_idx);
  CfgDepBase_RMV_SET_OBJ(Set,_Elem_Construct);
}

void
member_gset1(_rep,_Elem_Construct)
int *_rep,_Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset1_idx);
  CfgDepBase_MBR_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
union_gset1(_rep,_Set)
int *_rep,_Set;
{
  int Set_0;
  CfgDepBase_VAL_FNC(&Set_0,gset1_idx);
  CfgDepBase_UNION_SET_OBJ(_rep,Set_0,_Set);
}

void
mod_gset1(_rep,_Set)
int *_rep,_Set;
{
  int Set_0;
  CfgDepBase_VAL_FNC(&Set_0,gset1_idx);
  CfgDepBase_CPY_SET_OBJ(_rep,_Set,Set_0);
}

void
valOrd_gset1(_Elem_Construct,_ii)
int *_Elem_Construct,_ii;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset1_idx);
  CfgDepBase_VAL_SET_OBJ(_Elem_Construct,Set,_ii);
}

void
val_gset2(_Set)
int *_Set;
{
  CfgDepBase_VAL_FNC(_Set,gset2_idx);
}

void
card_gset2(_nbr)
int *_nbr;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset2_idx);
  CfgDepBase_CRD_SET_OBJ(_nbr,Set);
}

void
clear_gset2()
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset2_idx);
  CfgDepBase_CLR_SET_OBJ(Set);
}

void
add_gset2(_rep,_Elem_Construct)
int *_rep,_Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset2_idx);
  CfgDepBase_ENT_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
del_gset2(_Elem_Construct)
int _Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset2_idx);
  CfgDepBase_RMV_SET_OBJ(Set,_Elem_Construct);
}

void
member_gset2(_rep,_Elem_Construct)
int *_rep,_Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset2_idx);
  CfgDepBase_MBR_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
union_gset2(_rep,_Set)
int *_rep,_Set;
{
  int Set_0;
  CfgDepBase_VAL_FNC(&Set_0,gset2_idx);
  CfgDepBase_UNION_SET_OBJ(_rep,Set_0,_Set);
}

void
valOrd_gset2(_Elem_Construct,_ii)
int *_Elem_Construct,_ii;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset2_idx);
  CfgDepBase_VAL_SET_OBJ(_Elem_Construct,Set,_ii);
}

void
val_gset3(_Set)
int *_Set;
{
  CfgDepBase_VAL_FNC(_Set,gset3_idx);
}

void
card_gset3(_nbr)
int *_nbr;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset3_idx);
  CfgDepBase_CRD_SET_OBJ(_nbr,Set);
}

void
clear_gset3()
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset3_idx);
  CfgDepBase_CLR_SET_OBJ(Set);
}

void
add_gset3(_rep,_Elem_Construct)
int *_rep,_Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset3_idx);
  CfgDepBase_ENT_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
del_gset3(_Elem_Construct)
int _Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset3_idx);
  CfgDepBase_RMV_SET_OBJ(Set,_Elem_Construct);
}

void
member_gset3(_rep,_Elem_Construct)
int *_rep,_Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset3_idx);
  CfgDepBase_MBR_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
union_gset3(_rep,_Set)
int *_rep,_Set;
{
  int Set_0;
  CfgDepBase_VAL_FNC(&Set_0,gset3_idx);
  CfgDepBase_UNION_SET_OBJ(_rep,Set_0,_Set);
}

void
mod_gset3(_rep,_Set)
int *_rep,_Set;
{
  int Set_0;
  CfgDepBase_VAL_FNC(&Set_0,gset3_idx);
  CfgDepBase_CPY_SET_OBJ(_rep,_Set,Set_0);
}

void
valOrd_gset3(_Elem_Construct,_ii)
int *_Elem_Construct,_ii;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset3_idx);
  CfgDepBase_VAL_SET_OBJ(_Elem_Construct,Set,_ii);
}

void
card_gset4(_nbr)
int *_nbr;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset4_idx);
  CfgDepBase_CRD_SET_OBJ(_nbr,Set);
}

void
clear_gset4()
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset4_idx);
  CfgDepBase_CLR_SET_OBJ(Set);
}

void
add_gset4(_rep,_Elem_Construct)
int *_rep,_Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset4_idx);
  CfgDepBase_ENT_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
del_gset4(_Elem_Construct)
int _Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset4_idx);
  CfgDepBase_RMV_SET_OBJ(Set,_Elem_Construct);
}

void
member_gset4(_rep,_Elem_Construct)
int *_rep,_Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset4_idx);
  CfgDepBase_MBR_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
union_gset4(_rep,_Set)
int *_rep,_Set;
{
  int Set_0;
  CfgDepBase_VAL_FNC(&Set_0,gset4_idx);
  CfgDepBase_UNION_SET_OBJ(_rep,Set_0,_Set);
}

void
inter_gset4(_Set)
int _Set;
{
  int Set_0;
  CfgDepBase_VAL_FNC(&Set_0,gset4_idx);
  CfgDepBase_INTER_SET_OBJ(Set_0,_Set);
}

void
valOrd_gset4(_Elem_Construct,_ii)
int *_Elem_Construct,_ii;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset4_idx);
  CfgDepBase_VAL_SET_OBJ(_Elem_Construct,Set,_ii);
}

void
card_gset5(_nbr)
int *_nbr;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset5_idx);
  CfgDepBase_CRD_SET_OBJ(_nbr,Set);
}

void
clear_gset5()
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset5_idx);
  CfgDepBase_CLR_SET_OBJ(Set);
}

void
add_gset5(_rep,_Elem_Construct)
int *_rep,_Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset5_idx);
  CfgDepBase_ENT_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
del_gset5(_Elem_Construct)
int _Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset5_idx);
  CfgDepBase_RMV_SET_OBJ(Set,_Elem_Construct);
}

void
member_gset5(_rep,_Elem_Construct)
int *_rep,_Elem_Construct;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset5_idx);
  CfgDepBase_MBR_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
valOrd_gset5(_Elem_Construct,_ii)
int *_Elem_Construct,_ii;
{
  int Set;
  CfgDepBase_VAL_FNC(&Set,gset5_idx);
  CfgDepBase_VAL_SET_OBJ(_Elem_Construct,Set,_ii);
}

void
length_gseq(_nbr)
int *_nbr;
{
  int Seq;
  CfgDepBase_VAL_FNC(&Seq,gseq_idx);
  CfgDepBase_LEN_SEQ_OBJ(_nbr,Seq);
}

void
clear_gseq()
{
  int Seq;
  CfgDepBase_VAL_FNC(&Seq,gseq_idx);
  CfgDepBase_CLR_SEQ_OBJ(Seq);
}

void
valIth_gseq(_Elem_Construct,_ii)
int *_Elem_Construct,_ii;
{
  int Seq;
  CfgDepBase_VAL_FNC(&Seq,gseq_idx);
  CfgDepBase_VAL_SEQ_OBJ(_Elem_Construct,Seq,_ii);
}

void
delIth_gseq(_rep,_ii)
int *_rep,_ii;
{
  int bb,Seq,Seq_0;
  CfgDepBase_VAL_FNC(&Seq,gseq_idx);
  CfgDepBase_CRE_SEQ_OBJ(&bb,&Seq_0);
  if ( bb == TRUE ) {
    CfgDepBase_CPY_SEQ_OBJ(&bb,Seq,Seq_0);
  }
  if ( bb == TRUE ) {
    CfgDepBase_CUT_SEQ_OBJ(Seq_0,_ii);
    CfgDepBase_KEP_SEQ_OBJ(Seq,_ii-1);
    CfgDepBase_APP_SEQ_OBJ(&bb,Seq,Seq_0);
  }
  CfgDepBase_KIL_SEQ_OBJ(Seq_0);
  *_rep = bb;
}

void
push_gseq(_rep,_Elem_Construct)
int *_rep,_Elem_Construct;
{
  int Seq;
  CfgDepBase_VAL_FNC(&Seq,gseq_idx);
  CfgDepBase_PSH_SEQ_OBJ(_rep,Seq,_Elem_Construct);
}

void
within_gseq(_rep , _ii,_Elem_Construct)
int *_rep,*_ii,_Elem_Construct;
{
  int Seq;
  CfgDepBase_VAL_FNC(&Seq,gseq_idx);
  CfgDepBase_MBR_SEQ_OBJ(_rep,_ii,Seq,_Elem_Construct);
}

void
clear_flags()
{
  int Seq;
  CfgDepBase_VAL_FNC(&Seq,flags_idx);
  CfgDepBase_CLR_SEQ_OBJ(Seq);
}

void
valIth_flags(_nat,_ii)
int *_nat,_ii;
{
  int Seq;
  CfgDepBase_VAL_FNC(&Seq,flags_idx);
  CfgDepBase_VAL_SEQ_OBJ(_nat,Seq,_ii);
}

void
modIth_flags(_ii , _nat)
int _ii,_nat;
{
  int Seq;
  CfgDepBase_VAL_FNC(&Seq,flags_idx);
  CfgDepBase_STO_SEQ_OBJ(Seq,_ii,_nat);
}

void
push_flags(_rep,_nat)
int *_rep,_nat;
{
  int Seq;
  CfgDepBase_VAL_FNC(&Seq,flags_idx);
  CfgDepBase_PSH_SEQ_OBJ(_rep,Seq,_nat);
}

void
make_Construct(_rep , _Base_Construct,_Val_ext , _Val_type)
int *_rep,*_Base_Construct,_Val_ext,_Val_type;
{
  int Base_Constructx,bb,Str;
  Construct_CRE_FNC_OBJ(&bb,&Base_Constructx);
  if ( bb == TRUE ) {
    CfgDepBase_CRE_STR_OBJ(&bb,&Str);
    if ( bb == TRUE ) {
      Construct_STO_FNC_OBJ(Base_Constructx,name_idx,Str);
    }
  }
  if ( bb == TRUE ) {
    Construct_STO_FNC_OBJ(Base_Constructx,ext_idx,_Val_ext);
    Construct_STO_FNC_OBJ(Base_Constructx,type_idx,_Val_type);
  }
  *_Base_Construct = Base_Constructx;
  *_rep = bb;
}

void
kill_Construct(_Base_Construct)
int _Base_Construct;
{
  {
    int Str;
    Construct_VAL_FNC_OBJ(&Str,_Base_Construct,name_idx);
    CfgDepBase_KIL_STR_OBJ(Str);
  }
  {
    int Set,bb;
    Construct_DEF_FNC_OBJ(&bb,_Base_Construct,sees_uses_idx);
    if ( bb == TRUE ) {
      Construct_VAL_FNC_OBJ(&Set,_Base_Construct,sees_uses_idx);
      CfgDepBase_KIL_SET_OBJ(Set);
    }
  }
  {
    int Set,bb;
    Construct_DEF_FNC_OBJ(&bb,_Base_Construct,inc_ipt_idx);
    if ( bb == TRUE ) {
      Construct_VAL_FNC_OBJ(&Set,_Base_Construct,inc_ipt_idx);
      CfgDepBase_KIL_SET_OBJ(Set);
    }
  }
  Construct_KIL_FNC_OBJ(_Base_Construct);
}

void
print_BaseObj_Construct(_Base_Construct)
int _Base_Construct;
{
  PUT_STR("\n-------- BASE Construct OBJECT ");
  CfgDepBase_PUT_TOK(_Base_Construct);
  PUT_STR(" --------\n");
  PUT_STR("MANDATORY\n");
  {
    int elem;
    Construct_VAL_FNC_OBJ(&elem,_Base_Construct,name_idx);
    BLK(2);
    PUT_STR_PAD("name ",13);
    {
      int ss[250];
      CfgDepBase_XTR_STR_OBJ(ss,elem);
      PUT_STR(ss);
    }
    NWL(1);
  }
  {
    int elem;
    Construct_VAL_FNC_OBJ(&elem,_Base_Construct,ext_idx);
    BLK(2);
    PUT_STR_PAD("ext ",13);
    CfgDepBase_PUT_ACT_TOK(CfgDepBaseP7,elem);
    NWL(1);
  }
  {
    int elem;
    Construct_VAL_FNC_OBJ(&elem,_Base_Construct,type_idx);
    BLK(2);
    PUT_STR_PAD("type ",13);
    CfgDepBase_PUT_ACT_TOK(CfgDepBaseP8,elem);
    NWL(1);
  }
  PUT_STR("OPTIONAL\n");
  {
    int bb;
    Construct_DEF_FNC_OBJ(&bb,_Base_Construct,sees_uses_idx);
    if ( bb == TRUE ) {
      int setobj,elem,crd,ord;
      BLK(2);
      PUT_STR_PAD("sees_uses ",13);
      PUT_STR("{ ");
      Construct_VAL_FNC_OBJ(&setobj,_Base_Construct,sees_uses_idx);
      CfgDepBase_CRD_SET_OBJ(&crd,setobj);
      ord = 1;
      while ( ord <= crd ) {
        CfgDepBase_VAL_SET_OBJ(&elem,setobj,ord);
        {
          int strobj;
          Construct_VAL_FNC_OBJ(&strobj,elem,name_idx);
          {
            int ss[250];
            CfgDepBase_XTR_STR_OBJ(ss,strobj);
            PUT_STR(ss);
          }
          PUT_STR("(");
          CfgDepBase_PUT_TOK(elem);
          PUT_STR(")");
        }
        BLK(1);
        ord = ord+1;
      }
      PUT_STR("}");
      NWL(1);
    }
  }
  {
    int bb;
    Construct_DEF_FNC_OBJ(&bb,_Base_Construct,inc_ipt_idx);
    if ( bb == TRUE ) {
      int setobj,elem,crd,ord;
      BLK(2);
      PUT_STR_PAD("inc_ipt ",13);
      PUT_STR("{ ");
      Construct_VAL_FNC_OBJ(&setobj,_Base_Construct,inc_ipt_idx);
      CfgDepBase_CRD_SET_OBJ(&crd,setobj);
      ord = 1;
      while ( ord <= crd ) {
        CfgDepBase_VAL_SET_OBJ(&elem,setobj,ord);
        {
          int strobj;
          Construct_VAL_FNC_OBJ(&strobj,elem,name_idx);
          {
            int ss[250];
            CfgDepBase_XTR_STR_OBJ(ss,strobj);
            PUT_STR(ss);
          }
          PUT_STR("(");
          CfgDepBase_PUT_TOK(elem);
          PUT_STR(")");
        }
        BLK(1);
        ord = ord+1;
      }
      PUT_STR("}");
      NWL(1);
    }
  }
  {
    int bb;
    Construct_DEF_FNC_OBJ(&bb,_Base_Construct,abs2conc_idx);
    if ( bb == TRUE ) {
      int elem;
      Construct_VAL_FNC_OBJ(&elem,_Base_Construct,abs2conc_idx);
      BLK(2);
      PUT_STR_PAD("abs2conc ",13);
      PUT_STR("Abs2Conc.");
      CfgDepBase_PUT_TOK(elem);
      NWL(1);
    }
  }
  {
    int bb;
    Construct_DEF_FNC_OBJ(&bb,_Base_Construct,gen_by_idx);
    if ( bb == TRUE ) {
      int elem;
      Construct_VAL_FNC_OBJ(&elem,_Base_Construct,gen_by_idx);
      BLK(2);
      PUT_STR_PAD("gen_by ",13);
      {
        int strobj;
        Construct_VAL_FNC_OBJ(&strobj,elem,name_idx);
        {
          int ss[250];
          CfgDepBase_XTR_STR_OBJ(ss,strobj);
          PUT_STR(ss);
        }
        PUT_STR("(");
        CfgDepBase_PUT_TOK(elem);
        PUT_STR(")");
      }
      NWL(1);
    }
  }
  {
    int bb;
    Construct_DEF_FNC_OBJ(&bb,_Base_Construct,prf_level_idx);
    if ( bb == TRUE ) {
      int elem;
      Construct_VAL_FNC_OBJ(&elem,_Base_Construct,prf_level_idx);
      BLK(2);
      PUT_STR_PAD("prf_level ",13);
      CfgDepBase_PUT_ACT_TOK(SCALAR,elem);
      NWL(1);
    }
  }
  {
    int bb;
    Construct_DEF_FNC_OBJ(&bb,_Base_Construct,curMRIState_idx);
    if ( bb == TRUE ) {
      int elem;
      Construct_VAL_FNC_OBJ(&elem,_Base_Construct,curMRIState_idx);
      BLK(2);
      PUT_STR_PAD("curMRIState ",13);
      PUT_STR("MRIState.");
      CfgDepBase_PUT_TOK(elem);
      NWL(1);
    }
  }
  {
    int bb;
    Construct_DEF_FNC_OBJ(&bb,_Base_Construct,cptMRIState_idx);
    if ( bb == TRUE ) {
      int elem;
      Construct_VAL_FNC_OBJ(&elem,_Base_Construct,cptMRIState_idx);
      BLK(2);
      PUT_STR_PAD("cptMRIState ",13);
      PUT_STR("MRIState.");
      CfgDepBase_PUT_TOK(elem);
      NWL(1);
    }
  }
  {
    int bb;
    Construct_DEF_FNC_OBJ(&bb,_Base_Construct,curGENState_idx);
    if ( bb == TRUE ) {
      int elem;
      Construct_VAL_FNC_OBJ(&elem,_Base_Construct,curGENState_idx);
      BLK(2);
      PUT_STR_PAD("curGENState ",13);
      PUT_STR("GENState.");
      CfgDepBase_PUT_TOK(elem);
      NWL(1);
    }
  }
  {
    int bb;
    Construct_DEF_FNC_OBJ(&bb,_Base_Construct,cptGENState_idx);
    if ( bb == TRUE ) {
      int elem;
      Construct_VAL_FNC_OBJ(&elem,_Base_Construct,cptGENState_idx);
      BLK(2);
      PUT_STR_PAD("cptGENState ",13);
      PUT_STR("GENState.");
      CfgDepBase_PUT_TOK(elem);
      NWL(1);
    }
  }
  PUT_STR("----------------------------------------\n");
}

void
first_Construct(_loc , _Base_Construct)
int *_loc,*_Base_Construct;
{
  Construct_FIRST_FNC_OBJ(_loc,_Base_Construct);
}

void
next_Construct(_loc , _Base_Construct,_loc_0 , _Base_Construct_0)
int *_loc,*_Base_Construct,_loc_0,_Base_Construct_0;
{
  Construct_NEXT_FNC_OBJ(_loc,_Base_Construct,_loc_0,_Base_Construct_0);
}

void
vld_Construct(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  Construct_XST_FNC_OBJ(_rep,_Base_Construct);
}

void
nbr_Construct(_tot)
int *_tot;
{
  int Base_Construct;
  Construct_FIRST_FNC_OBJ(_tot,&Base_Construct);
}

void
xtr_name(_Str,_Base_Construct)
int *_Str,_Base_Construct;
{
  int Strx;
  Construct_VAL_FNC_OBJ(&Strx,_Base_Construct,name_idx);
  CfgDepBase_XTR_STR_OBJ(_Str,Strx);
}

void
mod_name(_rep,_Base_Construct , _Str)
int *_rep,_Base_Construct,*_Str;
{
  int Str_0,bb;
  Construct_VAL_FNC_OBJ(&Str_0,_Base_Construct,name_idx);
  CfgDepBase_KIL_STR_OBJ(Str_0);
  CfgDepBase_NEW_STR_OBJ(&bb,&Str_0,_Str);
  if ( bb == TRUE ) {
    Construct_STO_FNC_OBJ(_Base_Construct,name_idx,Str_0);
  }
  *_rep = bb;
}

void
val_ext(_Elem_EXTENSION,_Base_Construct)
int *_Elem_EXTENSION,_Base_Construct;
{
  Construct_VAL_FNC_OBJ(_Elem_EXTENSION,_Base_Construct,ext_idx);
}

void
val_type(_Elem_TYPE,_Base_Construct)
int *_Elem_TYPE,_Base_Construct;
{
  Construct_VAL_FNC_OBJ(_Elem_TYPE,_Base_Construct,type_idx);
}

void
cre_sees_uses(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  int repx,Set;
  CfgDepBase_CRE_SET_OBJ(&repx,&Set);
  if ( repx == TRUE ) {
    Construct_STO_FNC_OBJ(_Base_Construct,sees_uses_idx,Set);
  }
  *_rep = repx;
}

void
rem_sees_uses(_Base_Construct)
int _Base_Construct;
{
  int Set;
  Construct_VAL_FNC_OBJ(&Set,_Base_Construct,sees_uses_idx);
  CfgDepBase_KIL_SET_OBJ(Set);
  Construct_RMV_FNC_OBJ(_Base_Construct,sees_uses_idx);
}

void
def_sees_uses(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  Construct_DEF_FNC_OBJ(_rep,_Base_Construct,sees_uses_idx);
}

void
val_sees_uses(_Set,_Base_Construct)
int *_Set,_Base_Construct;
{
  Construct_VAL_FNC_OBJ(_Set,_Base_Construct,sees_uses_idx);
}

void
card_sees_uses(_nbr,_Base_Construct)
int *_nbr,_Base_Construct;
{
  int Set;
  Construct_VAL_FNC_OBJ(&Set,_Base_Construct,sees_uses_idx);
  CfgDepBase_CRD_SET_OBJ(_nbr,Set);
}

void
member_sees_uses(_rep,_Base_Construct , _Elem_Construct)
int *_rep,_Base_Construct,_Elem_Construct;
{
  int Set;
  Construct_VAL_FNC_OBJ(&Set,_Base_Construct,sees_uses_idx);
  CfgDepBase_MBR_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
mod_sees_uses(_rep,_Base_Construct , _Set)
int *_rep,_Base_Construct,_Set;
{
  int Set_0;
  Construct_VAL_FNC_OBJ(&Set_0,_Base_Construct,sees_uses_idx);
  CfgDepBase_CPY_SET_OBJ(_rep,_Set,Set_0);
}

void
valOrd_sees_uses(_Elem_Construct,_Base_Construct , _ii)
int *_Elem_Construct,_Base_Construct,_ii;
{
  int Set;
  Construct_VAL_FNC_OBJ(&Set,_Base_Construct,sees_uses_idx);
  CfgDepBase_VAL_SET_OBJ(_Elem_Construct,Set,_ii);
}

void
cre_inc_ipt(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  int repx,Set;
  CfgDepBase_CRE_SET_OBJ(&repx,&Set);
  if ( repx == TRUE ) {
    Construct_STO_FNC_OBJ(_Base_Construct,inc_ipt_idx,Set);
  }
  *_rep = repx;
}

void
rem_inc_ipt(_Base_Construct)
int _Base_Construct;
{
  int Set;
  Construct_VAL_FNC_OBJ(&Set,_Base_Construct,inc_ipt_idx);
  CfgDepBase_KIL_SET_OBJ(Set);
  Construct_RMV_FNC_OBJ(_Base_Construct,inc_ipt_idx);
}

void
def_inc_ipt(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  Construct_DEF_FNC_OBJ(_rep,_Base_Construct,inc_ipt_idx);
}

void
val_inc_ipt(_Set,_Base_Construct)
int *_Set,_Base_Construct;
{
  Construct_VAL_FNC_OBJ(_Set,_Base_Construct,inc_ipt_idx);
}

void
card_inc_ipt(_nbr,_Base_Construct)
int *_nbr,_Base_Construct;
{
  int Set;
  Construct_VAL_FNC_OBJ(&Set,_Base_Construct,inc_ipt_idx);
  CfgDepBase_CRD_SET_OBJ(_nbr,Set);
}

void
member_inc_ipt(_rep,_Base_Construct , _Elem_Construct)
int *_rep,_Base_Construct,_Elem_Construct;
{
  int Set;
  Construct_VAL_FNC_OBJ(&Set,_Base_Construct,inc_ipt_idx);
  CfgDepBase_MBR_SET_OBJ(_rep,Set,_Elem_Construct);
}

void
mod_inc_ipt(_rep,_Base_Construct , _Set)
int *_rep,_Base_Construct,_Set;
{
  int Set_0;
  Construct_VAL_FNC_OBJ(&Set_0,_Base_Construct,inc_ipt_idx);
  CfgDepBase_CPY_SET_OBJ(_rep,_Set,Set_0);
}

void
valOrd_inc_ipt(_Elem_Construct,_Base_Construct , _ii)
int *_Elem_Construct,_Base_Construct,_ii;
{
  int Set;
  Construct_VAL_FNC_OBJ(&Set,_Base_Construct,inc_ipt_idx);
  CfgDepBase_VAL_SET_OBJ(_Elem_Construct,Set,_ii);
}

void
cre_abs2conc(_Base_Construct , _Base_Abs2Conc)
int _Base_Construct,_Base_Abs2Conc;
{
  Construct_STO_FNC_OBJ(_Base_Construct,abs2conc_idx,_Base_Abs2Conc);
}

void
rem_abs2conc(_Base_Construct)
int _Base_Construct;
{
  Construct_RMV_FNC_OBJ(_Base_Construct,abs2conc_idx);
}

void
def_abs2conc(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  Construct_DEF_FNC_OBJ(_rep,_Base_Construct,abs2conc_idx);
}

void
val_abs2conc(_Base_Abs2Conc,_Base_Construct)
int *_Base_Abs2Conc,_Base_Construct;
{
  Construct_VAL_FNC_OBJ(_Base_Abs2Conc,_Base_Construct,abs2conc_idx);
}

void
cre_gen_by(_Base_Construct , _Base_Constructx)
int _Base_Construct,_Base_Constructx;
{
  Construct_STO_FNC_OBJ(_Base_Construct,gen_by_idx,_Base_Constructx);
}

void
def_gen_by(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  Construct_DEF_FNC_OBJ(_rep,_Base_Construct,gen_by_idx);
}

void
val_gen_by(_Base_Construct,_Base_Constructx)
int *_Base_Construct,_Base_Constructx;
{
  Construct_VAL_FNC_OBJ(_Base_Construct,_Base_Constructx,gen_by_idx);
}

void
eql_gen_by(_rep,_Base_Construct , _Base_Constructx)
int *_rep,_Base_Construct,_Base_Constructx;
{
  int Base_Constructx_0;
  Construct_VAL_FNC_OBJ(&Base_Constructx_0,_Base_Construct,gen_by_idx);
  if ( Base_Constructx_0 == _Base_Constructx ) {
    *_rep = TRUE;
  }
  else {
    *_rep = FALSE;
  }
}

void
cre_prf_level(_Base_Construct , _nat)
int _Base_Construct,_nat;
{
  Construct_STO_FNC_OBJ(_Base_Construct,prf_level_idx,_nat);
}

void
def_prf_level(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  Construct_DEF_FNC_OBJ(_rep,_Base_Construct,prf_level_idx);
}

void
val_prf_level(_nat,_Base_Construct)
int *_nat,_Base_Construct;
{
  Construct_VAL_FNC_OBJ(_nat,_Base_Construct,prf_level_idx);
}

void
cre_curMRIState(_Base_Construct , _Base_MRIState)
int _Base_Construct,_Base_MRIState;
{
  Construct_STO_FNC_OBJ(_Base_Construct,curMRIState_idx,_Base_MRIState);
}

void
def_curMRIState(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  Construct_DEF_FNC_OBJ(_rep,_Base_Construct,curMRIState_idx);
}

void
val_curMRIState(_Base_MRIState,_Base_Construct)
int *_Base_MRIState,_Base_Construct;
{
  Construct_VAL_FNC_OBJ(_Base_MRIState,_Base_Construct,curMRIState_idx);
}

void
cre_cptMRIState(_Base_Construct , _Base_MRIState)
int _Base_Construct,_Base_MRIState;
{
  Construct_STO_FNC_OBJ(_Base_Construct,cptMRIState_idx,_Base_MRIState);
}

void
def_cptMRIState(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  Construct_DEF_FNC_OBJ(_rep,_Base_Construct,cptMRIState_idx);
}

void
val_cptMRIState(_Base_MRIState,_Base_Construct)
int *_Base_MRIState,_Base_Construct;
{
  Construct_VAL_FNC_OBJ(_Base_MRIState,_Base_Construct,cptMRIState_idx);
}

void
cre_curGENState(_Base_Construct , _Base_GENState)
int _Base_Construct,_Base_GENState;
{
  Construct_STO_FNC_OBJ(_Base_Construct,curGENState_idx,_Base_GENState);
}

void
def_curGENState(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  Construct_DEF_FNC_OBJ(_rep,_Base_Construct,curGENState_idx);
}

void
val_curGENState(_Base_GENState,_Base_Construct)
int *_Base_GENState,_Base_Construct;
{
  Construct_VAL_FNC_OBJ(_Base_GENState,_Base_Construct,curGENState_idx);
}

void
cre_cptGENState(_Base_Construct , _Base_GENState)
int _Base_Construct,_Base_GENState;
{
  Construct_STO_FNC_OBJ(_Base_Construct,cptGENState_idx,_Base_GENState);
}

void
def_cptGENState(_rep,_Base_Construct)
int *_rep,_Base_Construct;
{
  Construct_DEF_FNC_OBJ(_rep,_Base_Construct,cptGENState_idx);
}

void
val_cptGENState(_Base_GENState,_Base_Construct)
int *_Base_GENState,_Base_Construct;
{
  Construct_VAL_FNC_OBJ(_Base_GENState,_Base_Construct,cptGENState_idx);
}

void
make_Abs2Conc(_rep , _Base_Abs2Conc)
int *_rep,*_Base_Abs2Conc;
{
  int Base_Abs2Concx,bb,Seq;
  Abs2Conc_CRE_FNC_OBJ(&bb,&Base_Abs2Concx);
  if ( bb == TRUE ) {
    CfgDepBase_CRE_SEQ_OBJ(&bb,&Seq);
    if ( bb == TRUE ) {
      Abs2Conc_STO_FNC_OBJ(Base_Abs2Concx,a2c_idx,Seq);
    }
  }
  *_Base_Abs2Conc = Base_Abs2Concx;
  *_rep = bb;
}

void
kill_Abs2Conc(_Base_Abs2Conc)
int _Base_Abs2Conc;
{
  {
    int Seq;
    Abs2Conc_VAL_FNC_OBJ(&Seq,_Base_Abs2Conc,a2c_idx);
    CfgDepBase_KIL_SEQ_OBJ(Seq);
  }
  Abs2Conc_KIL_FNC_OBJ(_Base_Abs2Conc);
}

void
print_BaseObj_Abs2Conc(_Base_Abs2Conc)
int _Base_Abs2Conc;
{
  PUT_STR("\n-------- BASE Abs2Conc OBJECT ");
  CfgDepBase_PUT_TOK(_Base_Abs2Conc);
  PUT_STR(" --------\n");
  PUT_STR("MANDATORY\n");
  {
    int seqobj,elem,len,ith;
    BLK(2);
    PUT_STR_PAD("a2c ",13);
    PUT_STR("[ ");
    Abs2Conc_VAL_FNC_OBJ(&seqobj,_Base_Abs2Conc,a2c_idx);
    CfgDepBase_LEN_SEQ_OBJ(&len,seqobj);
    ith = 1;
    while ( ith <= len ) {
      CfgDepBase_VAL_SEQ_OBJ(&elem,seqobj,ith);
      {
        int strobj;
        Construct_VAL_FNC_OBJ(&strobj,elem,name_idx);
        {
          int ss[250];
          CfgDepBase_XTR_STR_OBJ(ss,strobj);
          PUT_STR(ss);
        }
        PUT_STR("(");
        CfgDepBase_PUT_TOK(elem);
        PUT_STR(")");
      }
      BLK(1);
      ith = ith+1;
    }
    PUT_STR("]");
    NWL(1);
  }
  PUT_STR("----------------------------------------\n");
}

void
first_Abs2Conc(_loc , _Base_Abs2Conc)
int *_loc,*_Base_Abs2Conc;
{
  Abs2Conc_FIRST_FNC_OBJ(_loc,_Base_Abs2Conc);
}

void
next_Abs2Conc(_loc , _Base_Abs2Conc,_loc_0 , _Base_Abs2Conc_0)
int *_loc,*_Base_Abs2Conc,_loc_0,_Base_Abs2Conc_0;
{
  Abs2Conc_NEXT_FNC_OBJ(_loc,_Base_Abs2Conc,_loc_0,_Base_Abs2Conc_0);
}

void
vld_Abs2Conc(_rep,_Base_Abs2Conc)
int *_rep,_Base_Abs2Conc;
{
  Abs2Conc_XST_FNC_OBJ(_rep,_Base_Abs2Conc);
}

void
length_a2c(_nbr,_Base_Abs2Conc)
int *_nbr,_Base_Abs2Conc;
{
  int Seq;
  Abs2Conc_VAL_FNC_OBJ(&Seq,_Base_Abs2Conc,a2c_idx);
  CfgDepBase_LEN_SEQ_OBJ(_nbr,Seq);
}

void
last_a2c(_Elem_Construct,_Base_Abs2Conc)
int *_Elem_Construct,_Base_Abs2Conc;
{
  int Seq,len;
  Abs2Conc_VAL_FNC_OBJ(&Seq,_Base_Abs2Conc,a2c_idx);
  CfgDepBase_LEN_SEQ_OBJ(&len,Seq);
  CfgDepBase_VAL_SEQ_OBJ(_Elem_Construct,Seq,len);
}

void
valIth_a2c(_Elem_Construct,_Base_Abs2Conc , _ii)
int *_Elem_Construct,_Base_Abs2Conc,_ii;
{
  int Seq;
  Abs2Conc_VAL_FNC_OBJ(&Seq,_Base_Abs2Conc,a2c_idx);
  CfgDepBase_VAL_SEQ_OBJ(_Elem_Construct,Seq,_ii);
}

void
pop_a2c(_Base_Abs2Conc)
int _Base_Abs2Conc;
{
  int Seq;
  Abs2Conc_VAL_FNC_OBJ(&Seq,_Base_Abs2Conc,a2c_idx);
  CfgDepBase_POP_SEQ_OBJ(Seq);
}

void
push_a2c(_rep,_Base_Abs2Conc , _Elem_Construct)
int *_rep,_Base_Abs2Conc,_Elem_Construct;
{
  int Seq;
  Abs2Conc_VAL_FNC_OBJ(&Seq,_Base_Abs2Conc,a2c_idx);
  CfgDepBase_PSH_SEQ_OBJ(_rep,Seq,_Elem_Construct);
}

void
make_MRIState(_rep , _Base_MRIState,_Val_anl , _Val_dmu , _Val_trl , _Val_lnk)
int *_rep,*_Base_MRIState,_Val_anl,_Val_dmu,_Val_trl,_Val_lnk;
{
  int Base_MRIStatex,bb,Seq,Set,Setx;
  MRIState_CRE_FNC_OBJ(&bb,&Base_MRIStatex);
  if ( bb == TRUE ) {
    CfgDepBase_CRE_SEQ_OBJ(&bb,&Seq);
    if ( bb == TRUE ) {
      MRIState_STO_FNC_OBJ(Base_MRIStatex,pob_idx,Seq);
    }
  }
  if ( bb == TRUE ) {
    CfgDepBase_CRE_SET_OBJ(&bb,&Set);
    if ( bb == TRUE ) {
      MRIState_STO_FNC_OBJ(Base_MRIStatex,ppf_idx,Set);
    }
  }
  if ( bb == TRUE ) {
    CfgDepBase_CRE_SET_OBJ(&bb,&Setx);
    if ( bb == TRUE ) {
      MRIState_STO_FNC_OBJ(Base_MRIStatex,ppf_dmu_idx,Setx);
    }
  }
  if ( bb == TRUE ) {
    MRIState_STO_FNC_OBJ(Base_MRIStatex,anl_idx,_Val_anl);
    MRIState_STO_FNC_OBJ(Base_MRIStatex,dmu_idx,_Val_dmu);
    MRIState_STO_FNC_OBJ(Base_MRIStatex,trl_idx,_Val_trl);
    MRIState_STO_FNC_OBJ(Base_MRIStatex,lnk_idx,_Val_lnk);
  }
  *_Base_MRIState = Base_MRIStatex;
  *_rep = bb;
}

void
kill_MRIState(_Base_MRIState)
int _Base_MRIState;
{
  {
    int Seq;
    MRIState_VAL_FNC_OBJ(&Seq,_Base_MRIState,pob_idx);
    CfgDepBase_KIL_SEQ_OBJ(Seq);
  }
  {
    int Set;
    MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_idx);
    CfgDepBase_KIL_SET_OBJ(Set);
  }
  {
    int Set;
    MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_dmu_idx);
    CfgDepBase_KIL_SET_OBJ(Set);
  }
  MRIState_KIL_FNC_OBJ(_Base_MRIState);
}

void
print_BaseObj_MRIState(_Base_MRIState)
int _Base_MRIState;
{
  PUT_STR("\n-------- BASE MRIState OBJECT ");
  CfgDepBase_PUT_TOK(_Base_MRIState);
  PUT_STR(" --------\n");
  PUT_STR("MANDATORY\n");
  {
    int elem;
    MRIState_VAL_FNC_OBJ(&elem,_Base_MRIState,anl_idx);
    BLK(2);
    PUT_STR_PAD("anl ",13);
    PUT_BOOL(elem);
    NWL(1);
  }
  {
    int elem;
    MRIState_VAL_FNC_OBJ(&elem,_Base_MRIState,dmu_idx);
    BLK(2);
    PUT_STR_PAD("dmu ",13);
    PUT_BOOL(elem);
    NWL(1);
  }
  {
    int elem;
    MRIState_VAL_FNC_OBJ(&elem,_Base_MRIState,trl_idx);
    BLK(2);
    PUT_STR_PAD("trl ",13);
    PUT_BOOL(elem);
    NWL(1);
  }
  {
    int elem;
    MRIState_VAL_FNC_OBJ(&elem,_Base_MRIState,lnk_idx);
    BLK(2);
    PUT_STR_PAD("lnk ",13);
    PUT_BOOL(elem);
    NWL(1);
  }
  {
    int seqobj,elem,len,ith;
    BLK(2);
    PUT_STR_PAD("pob ",13);
    PUT_STR("[ ");
    MRIState_VAL_FNC_OBJ(&seqobj,_Base_MRIState,pob_idx);
    CfgDepBase_LEN_SEQ_OBJ(&len,seqobj);
    ith = 1;
    while ( ith <= len ) {
      CfgDepBase_VAL_SEQ_OBJ(&elem,seqobj,ith);
      CfgDepBase_PUT_ACT_TOK(SCALAR,elem);
      BLK(1);
      ith = ith+1;
    }
    PUT_STR("]");
    NWL(1);
  }
  {
    int setobj,elem,crd,ord;
    BLK(2);
    PUT_STR_PAD("ppf ",13);
    PUT_STR("{ ");
    MRIState_VAL_FNC_OBJ(&setobj,_Base_MRIState,ppf_idx);
    CfgDepBase_CRD_SET_OBJ(&crd,setobj);
    ord = 1;
    while ( ord <= crd ) {
      CfgDepBase_VAL_SET_OBJ(&elem,setobj,ord);
      CfgDepBase_PUT_ACT_TOK(SCALAR,elem);
      BLK(1);
      ord = ord+1;
    }
    PUT_STR("}");
    NWL(1);
  }
  {
    int setobj,elem,crd,ord;
    BLK(2);
    PUT_STR_PAD("ppf_dmu ",13);
    PUT_STR("{ ");
    MRIState_VAL_FNC_OBJ(&setobj,_Base_MRIState,ppf_dmu_idx);
    CfgDepBase_CRD_SET_OBJ(&crd,setobj);
    ord = 1;
    while ( ord <= crd ) {
      CfgDepBase_VAL_SET_OBJ(&elem,setobj,ord);
      CfgDepBase_PUT_ACT_TOK(SCALAR,elem);
      BLK(1);
      ord = ord+1;
    }
    PUT_STR("}");
    NWL(1);
  }
  PUT_STR("----------------------------------------\n");
}

void
first_MRIState(_loc , _Base_MRIState)
int *_loc,*_Base_MRIState;
{
  MRIState_FIRST_FNC_OBJ(_loc,_Base_MRIState);
}

void
next_MRIState(_loc , _Base_MRIState,_loc_0 , _Base_MRIState_0)
int *_loc,*_Base_MRIState,_loc_0,_Base_MRIState_0;
{
  MRIState_NEXT_FNC_OBJ(_loc,_Base_MRIState,_loc_0,_Base_MRIState_0);
}

void
val_anl(_Elem_BOOL,_Base_MRIState)
int *_Elem_BOOL,_Base_MRIState;
{
  MRIState_VAL_FNC_OBJ(_Elem_BOOL,_Base_MRIState,anl_idx);
}

void
mod_anl(_Base_MRIState , _Elem_BOOL)
int _Base_MRIState,_Elem_BOOL;
{
  MRIState_STO_FNC_OBJ(_Base_MRIState,anl_idx,_Elem_BOOL);
}

void
val_dmu(_Elem_BOOL,_Base_MRIState)
int *_Elem_BOOL,_Base_MRIState;
{
  MRIState_VAL_FNC_OBJ(_Elem_BOOL,_Base_MRIState,dmu_idx);
}

void
mod_dmu(_Base_MRIState , _Elem_BOOL)
int _Base_MRIState,_Elem_BOOL;
{
  MRIState_STO_FNC_OBJ(_Base_MRIState,dmu_idx,_Elem_BOOL);
}

void
val_trl(_Elem_BOOL,_Base_MRIState)
int *_Elem_BOOL,_Base_MRIState;
{
  MRIState_VAL_FNC_OBJ(_Elem_BOOL,_Base_MRIState,trl_idx);
}

void
mod_trl(_Base_MRIState , _Elem_BOOL)
int _Base_MRIState,_Elem_BOOL;
{
  MRIState_STO_FNC_OBJ(_Base_MRIState,trl_idx,_Elem_BOOL);
}

void
val_lnk(_Elem_BOOL,_Base_MRIState)
int *_Elem_BOOL,_Base_MRIState;
{
  MRIState_VAL_FNC_OBJ(_Elem_BOOL,_Base_MRIState,lnk_idx);
}

void
mod_lnk(_Base_MRIState , _Elem_BOOL)
int _Base_MRIState,_Elem_BOOL;
{
  MRIState_STO_FNC_OBJ(_Base_MRIState,lnk_idx,_Elem_BOOL);
}

void
length_pob(_nbr,_Base_MRIState)
int *_nbr,_Base_MRIState;
{
  int Seq;
  MRIState_VAL_FNC_OBJ(&Seq,_Base_MRIState,pob_idx);
  CfgDepBase_LEN_SEQ_OBJ(_nbr,Seq);
}

void
clear_pob(_Base_MRIState)
int _Base_MRIState;
{
  int Seq;
  MRIState_VAL_FNC_OBJ(&Seq,_Base_MRIState,pob_idx);
  CfgDepBase_CLR_SEQ_OBJ(Seq);
}

void
last_pob(_nat,_Base_MRIState)
int *_nat,_Base_MRIState;
{
  int Seq,len;
  MRIState_VAL_FNC_OBJ(&Seq,_Base_MRIState,pob_idx);
  CfgDepBase_LEN_SEQ_OBJ(&len,Seq);
  CfgDepBase_VAL_SEQ_OBJ(_nat,Seq,len);
}

void
valIth_pob(_nat,_Base_MRIState , _ii)
int *_nat,_Base_MRIState,_ii;
{
  int Seq;
  MRIState_VAL_FNC_OBJ(&Seq,_Base_MRIState,pob_idx);
  CfgDepBase_VAL_SEQ_OBJ(_nat,Seq,_ii);
}

void
modIth_pob(_Base_MRIState , _ii , _nat)
int _Base_MRIState,_ii,_nat;
{
  int Seq;
  MRIState_VAL_FNC_OBJ(&Seq,_Base_MRIState,pob_idx);
  CfgDepBase_STO_SEQ_OBJ(Seq,_ii,_nat);
}

void
pop_pob(_Base_MRIState)
int _Base_MRIState;
{
  int Seq;
  MRIState_VAL_FNC_OBJ(&Seq,_Base_MRIState,pob_idx);
  CfgDepBase_POP_SEQ_OBJ(Seq);
}

void
push_pob(_rep,_Base_MRIState , _nat)
int *_rep,_Base_MRIState,_nat;
{
  int Seq;
  MRIState_VAL_FNC_OBJ(&Seq,_Base_MRIState,pob_idx);
  CfgDepBase_PSH_SEQ_OBJ(_rep,Seq,_nat);
}

void
card_ppf(_nbr,_Base_MRIState)
int *_nbr,_Base_MRIState;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_idx);
  CfgDepBase_CRD_SET_OBJ(_nbr,Set);
}

void
clear_ppf(_Base_MRIState)
int _Base_MRIState;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_idx);
  CfgDepBase_CLR_SET_OBJ(Set);
}

void
add_ppf(_rep,_Base_MRIState , _nat)
int *_rep,_Base_MRIState,_nat;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_idx);
  CfgDepBase_ENT_SET_OBJ(_rep,Set,_nat);
}

void
del_ppf(_Base_MRIState , _nat)
int _Base_MRIState,_nat;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_idx);
  CfgDepBase_RMV_SET_OBJ(Set,_nat);
}

void
member_ppf(_rep,_Base_MRIState , _nat)
int *_rep,_Base_MRIState,_nat;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_idx);
  CfgDepBase_MBR_SET_OBJ(_rep,Set,_nat);
}

void
valOrd_ppf(_nat,_Base_MRIState , _ii)
int *_nat,_Base_MRIState,_ii;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_idx);
  CfgDepBase_VAL_SET_OBJ(_nat,Set,_ii);
}

void
card_ppf_dmu(_nbr,_Base_MRIState)
int *_nbr,_Base_MRIState;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_dmu_idx);
  CfgDepBase_CRD_SET_OBJ(_nbr,Set);
}

void
clear_ppf_dmu(_Base_MRIState)
int _Base_MRIState;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_dmu_idx);
  CfgDepBase_CLR_SET_OBJ(Set);
}

void
add_ppf_dmu(_rep,_Base_MRIState , _nat)
int *_rep,_Base_MRIState,_nat;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_dmu_idx);
  CfgDepBase_ENT_SET_OBJ(_rep,Set,_nat);
}

void
del_ppf_dmu(_Base_MRIState , _nat)
int _Base_MRIState,_nat;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_dmu_idx);
  CfgDepBase_RMV_SET_OBJ(Set,_nat);
}

void
member_ppf_dmu(_rep,_Base_MRIState , _nat)
int *_rep,_Base_MRIState,_nat;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_dmu_idx);
  CfgDepBase_MBR_SET_OBJ(_rep,Set,_nat);
}

void
valOrd_ppf_dmu(_nat,_Base_MRIState , _ii)
int *_nat,_Base_MRIState,_ii;
{
  int Set;
  MRIState_VAL_FNC_OBJ(&Set,_Base_MRIState,ppf_dmu_idx);
  CfgDepBase_VAL_SET_OBJ(_nat,Set,_ii);
}

void
make_GENState(_rep , _Base_GENState,_Val_gen1 , _Val_gen2 , _Val_gen_dmu)
int *_rep,*_Base_GENState,_Val_gen1,_Val_gen2,_Val_gen_dmu;
{
  int Base_GENStatex,bb;
  GENState_CRE_FNC_OBJ(&bb,&Base_GENStatex);
  if ( bb == TRUE ) {
    GENState_STO_FNC_OBJ(Base_GENStatex,gen1_idx,_Val_gen1);
    GENState_STO_FNC_OBJ(Base_GENStatex,gen2_idx,_Val_gen2);
    GENState_STO_FNC_OBJ(Base_GENStatex,gen_dmu_idx,_Val_gen_dmu);
  }
  *_Base_GENState = Base_GENStatex;
  *_rep = bb;
}

void
kill_GENState(_Base_GENState)
int _Base_GENState;
{
  GENState_KIL_FNC_OBJ(_Base_GENState);
}

void
print_BaseObj_GENState(_Base_GENState)
int _Base_GENState;
{
  PUT_STR("\n-------- BASE GENState OBJECT ");
  CfgDepBase_PUT_TOK(_Base_GENState);
  PUT_STR(" --------\n");
  PUT_STR("MANDATORY\n");
  {
    int elem;
    GENState_VAL_FNC_OBJ(&elem,_Base_GENState,gen1_idx);
    BLK(2);
    PUT_STR_PAD("gen1 ",13);
    PUT_BOOL(elem);
    NWL(1);
  }
  {
    int elem;
    GENState_VAL_FNC_OBJ(&elem,_Base_GENState,gen2_idx);
    BLK(2);
    PUT_STR_PAD("gen2 ",13);
    PUT_BOOL(elem);
    NWL(1);
  }
  {
    int elem;
    GENState_VAL_FNC_OBJ(&elem,_Base_GENState,gen_dmu_idx);
    BLK(2);
    PUT_STR_PAD("gen_dmu ",13);
    PUT_BOOL(elem);
    NWL(1);
  }
  PUT_STR("----------------------------------------\n");
}

void
first_GENState(_loc , _Base_GENState)
int *_loc,*_Base_GENState;
{
  GENState_FIRST_FNC_OBJ(_loc,_Base_GENState);
}

void
next_GENState(_loc , _Base_GENState,_loc_0 , _Base_GENState_0)
int *_loc,*_Base_GENState,_loc_0,_Base_GENState_0;
{
  GENState_NEXT_FNC_OBJ(_loc,_Base_GENState,_loc_0,_Base_GENState_0);
}

void
val_gen1(_Elem_BOOL,_Base_GENState)
int *_Elem_BOOL,_Base_GENState;
{
  GENState_VAL_FNC_OBJ(_Elem_BOOL,_Base_GENState,gen1_idx);
}

void
mod_gen1(_Base_GENState , _Elem_BOOL)
int _Base_GENState,_Elem_BOOL;
{
  GENState_STO_FNC_OBJ(_Base_GENState,gen1_idx,_Elem_BOOL);
}

void
val_gen2(_Elem_BOOL,_Base_GENState)
int *_Elem_BOOL,_Base_GENState;
{
  GENState_VAL_FNC_OBJ(_Elem_BOOL,_Base_GENState,gen2_idx);
}

void
mod_gen2(_Base_GENState , _Elem_BOOL)
int _Base_GENState,_Elem_BOOL;
{
  GENState_STO_FNC_OBJ(_Base_GENState,gen2_idx,_Elem_BOOL);
}

void
val_gen_dmu(_Elem_BOOL,_Base_GENState)
int *_Elem_BOOL,_Base_GENState;
{
  GENState_VAL_FNC_OBJ(_Elem_BOOL,_Base_GENState,gen_dmu_idx);
}

void
mod_gen_dmu(_Base_GENState , _Elem_BOOL)
int _Base_GENState,_Elem_BOOL;
{
  GENState_STO_FNC_OBJ(_Base_GENState,gen_dmu_idx,_Elem_BOOL);
}

void
make_Seqstr(_rep , _Base_Seqstr)
int *_rep,*_Base_Seqstr;
{
  int Base_Seqstrx,bb,Seq;
  Seqstr_CRE_FNC_OBJ(&bb,&Base_Seqstrx);
  if ( bb == TRUE ) {
    CfgDepBase_CRE_SEQ_OBJ(&bb,&Seq);
    if ( bb == TRUE ) {
      Seqstr_STO_FNC_OBJ(Base_Seqstrx,seqstr_idx,Seq);
    }
  }
  *_Base_Seqstr = Base_Seqstrx;
  *_rep = bb;
}

void
print_BaseObj_Seqstr(_Base_Seqstr)
int _Base_Seqstr;
{
  PUT_STR("\n-------- BASE Seqstr OBJECT ");
  CfgDepBase_PUT_TOK(_Base_Seqstr);
  PUT_STR(" --------\n");
  PUT_STR("MANDATORY\n");
  {
    int seqobj,elem,len,ith;
    BLK(2);
    PUT_STR_PAD("seqstr ",13);
    PUT_STR("[ ");
    Seqstr_VAL_FNC_OBJ(&seqobj,_Base_Seqstr,seqstr_idx);
    CfgDepBase_LEN_SEQ_OBJ(&len,seqobj);
    ith = 1;
    while ( ith <= len ) {
      CfgDepBase_VAL_SEQ_OBJ(&elem,seqobj,ith);
      {
        int strobj;
        String_VAL_FNC_OBJ(&strobj,elem,string_idx);
        {
          int ss[250];
          CfgDepBase_XTR_STR_OBJ(ss,strobj);
          PUT_STR(ss);
        }
        PUT_STR("(");
        CfgDepBase_PUT_TOK(elem);
        PUT_STR(")");
      }
      BLK(1);
      ith = ith+1;
    }
    PUT_STR("]");
    NWL(1);
  }
  PUT_STR("----------------------------------------\n");
}

void
first_Seqstr(_loc , _Base_Seqstr)
int *_loc,*_Base_Seqstr;
{
  Seqstr_FIRST_FNC_OBJ(_loc,_Base_Seqstr);
}

void
next_Seqstr(_loc , _Base_Seqstr,_loc_0 , _Base_Seqstr_0)
int *_loc,*_Base_Seqstr,_loc_0,_Base_Seqstr_0;
{
  Seqstr_NEXT_FNC_OBJ(_loc,_Base_Seqstr,_loc_0,_Base_Seqstr_0);
}

void
clear_seqstr(_Base_Seqstr)
int _Base_Seqstr;
{
  int Seq;
  Seqstr_VAL_FNC_OBJ(&Seq,_Base_Seqstr,seqstr_idx);
  CfgDepBase_CLR_SEQ_OBJ(Seq);
}

void
valIth_seqstr(_Elem_String,_Base_Seqstr , _ii)
int *_Elem_String,_Base_Seqstr,_ii;
{
  int Seq;
  Seqstr_VAL_FNC_OBJ(&Seq,_Base_Seqstr,seqstr_idx);
  CfgDepBase_VAL_SEQ_OBJ(_Elem_String,Seq,_ii);
}

void
push_seqstr(_rep,_Base_Seqstr , _Elem_String)
int *_rep,_Base_Seqstr,_Elem_String;
{
  int Seq;
  Seqstr_VAL_FNC_OBJ(&Seq,_Base_Seqstr,seqstr_idx);
  CfgDepBase_PSH_SEQ_OBJ(_rep,Seq,_Elem_String);
}

void
make_String(_rep , _Base_String)
int *_rep,*_Base_String;
{
  int Base_Stringx,bb,Str;
  String_CRE_FNC_OBJ(&bb,&Base_Stringx);
  if ( bb == TRUE ) {
    CfgDepBase_CRE_STR_OBJ(&bb,&Str);
    if ( bb == TRUE ) {
      String_STO_FNC_OBJ(Base_Stringx,string_idx,Str);
    }
  }
  *_Base_String = Base_Stringx;
  *_rep = bb;
}

void
print_BaseObj_String(_Base_String)
int _Base_String;
{
  PUT_STR("\n-------- BASE String OBJECT ");
  CfgDepBase_PUT_TOK(_Base_String);
  PUT_STR(" --------\n");
  PUT_STR("MANDATORY\n");
  {
    int elem;
    String_VAL_FNC_OBJ(&elem,_Base_String,string_idx);
    BLK(2);
    PUT_STR_PAD("string ",13);
    {
      int ss[250];
      CfgDepBase_XTR_STR_OBJ(ss,elem);
      PUT_STR(ss);
    }
    NWL(1);
  }
  PUT_STR("----------------------------------------\n");
}

void
first_String(_loc , _Base_String)
int *_loc,*_Base_String;
{
  String_FIRST_FNC_OBJ(_loc,_Base_String);
}

void
next_String(_loc , _Base_String,_loc_0 , _Base_String_0)
int *_loc,*_Base_String,_loc_0,_Base_String_0;
{
  String_NEXT_FNC_OBJ(_loc,_Base_String,_loc_0,_Base_String_0);
}

void
nbr_String(_tot)
int *_tot;
{
  int Base_String;
  String_FIRST_FNC_OBJ(_tot,&Base_String);
}

void
xtr_string(_Str,_Base_String)
int *_Str,_Base_String;
{
  int Strx;
  String_VAL_FNC_OBJ(&Strx,_Base_String,string_idx);
  CfgDepBase_XTR_STR_OBJ(_Str,Strx);
}

void
mod_string(_rep,_Base_String , _Str)
int *_rep,_Base_String,*_Str;
{
  int Str_0,bb;
  String_VAL_FNC_OBJ(&Str_0,_Base_String,string_idx);
  CfgDepBase_KIL_STR_OBJ(Str_0);
  CfgDepBase_NEW_STR_OBJ(&bb,&Str_0,_Str);
  if ( bb == TRUE ) {
    String_STO_FNC_OBJ(_Base_String,string_idx,Str_0);
  }
  *_rep = bb;
}

