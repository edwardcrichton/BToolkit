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
#include "btl_proof.h"

#define pob_thy_str_idx 1
#define pob_nn_idx 2
#define reason_depth_idx 3
#define prf_seq_idx 4
#define stp_type_idx 1
#define stp_thy_str_idx 2
#define stp_rule_str_idx 3
#define stp_posn_idx 4

#include "btl_prf_ffnc_ctx.h"
#include "btl_prf_ffnc_obj.h"
#include "prf_seq_stp_ffnc_ctx.h"
#include "prf_seq_stp_ffnc_obj.h"
#include "btl_proof_seq_ctx.h"
#include "btl_proof_seq_obj.h"
#include "btl_proof_str_ctx.h"
#include "btl_proof_str_obj.h"

#include "btl_proofCtx.h"
#include "Scalar_TYPE.h"
#include "Bool_TYPE.h"
#include "String_TYPE.h"
#include "basic_io.h"
#include "btl_proof_file_dump.h"

INI_btl_proof()
{
  INI_btl_prf_ffnc_ctx();
  INI_btl_prf_ffnc_obj();
  INI_prf_seq_stp_ffnc_ctx();
  INI_prf_seq_stp_ffnc_obj();
  INI_btl_proof_seq_ctx();
  INI_btl_proof_seq_obj();
  INI_btl_proof_str_ctx();
  INI_btl_proof_str_obj();
}

save_n_btl_proof(rep)
int *rep;
{
  int bb;
  btl_proof_open_write_dump(&bb);
  if( bb == TRUE ){
    btl_prf_SAVN_FNC_OBJ();
    prf_seq_stp_SAVN_FNC_OBJ();
    btl_proof_SAVN_STR_OBJ();
    btl_proof_SAVN_SEQ_OBJ();
    btl_proof_close_dump(&bb);
  };
  *rep = bb;
}

restore_n_btl_proof(rep)
int *rep;
{
  int bb;
  btl_proof_open_read_dump(&bb);
  if( bb == TRUE ){
    btl_prf_RSTN_FNC_OBJ();
    prf_seq_stp_RSTN_FNC_OBJ();
    btl_proof_RSTN_STR_OBJ();
    btl_proof_RSTN_SEQ_OBJ();
    btl_proof_close_dump(&bb);
  };
  *rep = bb;
}

make_btl_prf(rep,Base_btl_prf,Val_pob_nn,Val_reason_depth)
int *rep,*Base_btl_prf,Val_pob_nn,Val_reason_depth;
{
  int Base_btl_prfx,bb,Str,Seq;
  btl_prf_CRE_FNC_OBJ(&bb,&Base_btl_prfx);
  if( bb == TRUE ){
    btl_proof_CRE_STR_OBJ(&bb,&Str);
    if( bb == TRUE ){
      btl_prf_STO_FNC_OBJ(Base_btl_prfx,pob_thy_str_idx,Str);
    }
  };
  if( bb == TRUE ){
    btl_proof_CRE_SEQ_OBJ(&bb,&Seq);
    if( bb == TRUE ){
      btl_prf_STO_FNC_OBJ(Base_btl_prfx,prf_seq_idx,Seq);
    }
  };
  if( bb == TRUE ){
    btl_prf_STO_FNC_OBJ(Base_btl_prfx,pob_nn_idx,Val_pob_nn);
    btl_prf_STO_FNC_OBJ(Base_btl_prfx,reason_depth_idx,Val_reason_depth);
  };
  *Base_btl_prf = Base_btl_prfx;
  *rep = bb;
}

first_btl_prf(loc,Base_btl_prf)
int *loc,*Base_btl_prf;
{
  btl_prf_FIRST_FNC_OBJ(loc,Base_btl_prf);
}

next_btl_prf(loc,Base_btl_prf,loc_0,Base_btl_prf_0)
int *loc,*Base_btl_prf,loc_0,Base_btl_prf_0;
{
  btl_prf_NEXT_FNC_OBJ(loc,Base_btl_prf,loc_0,Base_btl_prf_0);
}

xtr_pob_thy_str(Str,Base_btl_prf)
int *Str,Base_btl_prf;
{
  int Strx;
  btl_prf_VAL_FNC_OBJ(&Strx,Base_btl_prf,pob_thy_str_idx);
  btl_proof_XTR_STR_OBJ(Str,Strx);
}

mod_pob_thy_str(rep,Base_btl_prf,Str)
int *rep,Base_btl_prf,*Str;
{
  int Str_0,bb;
  btl_prf_VAL_FNC_OBJ(&Str_0,Base_btl_prf,pob_thy_str_idx);
  btl_proof_KIL_STR_OBJ(Str_0);
  btl_proof_NEW_STR_OBJ(&bb,&Str_0,Str);
  if( bb == TRUE ){
    btl_prf_STO_FNC_OBJ(Base_btl_prf,pob_thy_str_idx,Str_0);
  };
  *rep = bb;
}

val_pob_nn(nat,Base_btl_prf)
int *nat,Base_btl_prf;
{
  btl_prf_VAL_FNC_OBJ(nat,Base_btl_prf,pob_nn_idx);
}

val_reason_depth(nat,Base_btl_prf)
int *nat,Base_btl_prf;
{
  btl_prf_VAL_FNC_OBJ(nat,Base_btl_prf,reason_depth_idx);
}

length_prf_seq(nbr,Base_btl_prf)
int *nbr,Base_btl_prf;
{
  int Seq;
  btl_prf_VAL_FNC_OBJ(&Seq,Base_btl_prf,prf_seq_idx);
  btl_proof_LEN_SEQ_OBJ(nbr,Seq);
}

valIth_prf_seq(Elem_prf_seq_stp,Base_btl_prf,ii)
int *Elem_prf_seq_stp,Base_btl_prf,ii;
{
  int Seq;
  btl_prf_VAL_FNC_OBJ(&Seq,Base_btl_prf,prf_seq_idx);
  btl_proof_VAL_SEQ_OBJ(Elem_prf_seq_stp,Seq,ii);
}

push_prf_seq(rep,Base_btl_prf,Elem_prf_seq_stp)
int *rep,Base_btl_prf,Elem_prf_seq_stp;
{
  int Seq;
  btl_prf_VAL_FNC_OBJ(&Seq,Base_btl_prf,prf_seq_idx);
  btl_proof_PSH_SEQ_OBJ(rep,Seq,Elem_prf_seq_stp);
}

make_prf_seq_stp(rep,Base_prf_seq_stp,Val_stp_type,Val_stp_posn)
int *rep,*Base_prf_seq_stp,Val_stp_type,Val_stp_posn;
{
  int Base_prf_seq_stpx,bb,Str,Strx;
  prf_seq_stp_CRE_FNC_OBJ(&bb,&Base_prf_seq_stpx);
  if( bb == TRUE ){
    btl_proof_CRE_STR_OBJ(&bb,&Str);
    if( bb == TRUE ){
      prf_seq_stp_STO_FNC_OBJ(Base_prf_seq_stpx,stp_thy_str_idx,Str);
    }
  };
  if( bb == TRUE ){
    btl_proof_CRE_STR_OBJ(&bb,&Strx);
    if( bb == TRUE ){
      prf_seq_stp_STO_FNC_OBJ(Base_prf_seq_stpx,stp_rule_str_idx,Strx);
    }
  };
  if( bb == TRUE ){
    prf_seq_stp_STO_FNC_OBJ(Base_prf_seq_stpx,stp_type_idx,Val_stp_type);
    prf_seq_stp_STO_FNC_OBJ(Base_prf_seq_stpx,stp_posn_idx,Val_stp_posn);
  };
  *Base_prf_seq_stp = Base_prf_seq_stpx;
  *rep = bb;
}

val_stp_type(nat,Base_prf_seq_stp)
int *nat,Base_prf_seq_stp;
{
  prf_seq_stp_VAL_FNC_OBJ(nat,Base_prf_seq_stp,stp_type_idx);
}

xtr_stp_thy_str(Str,Base_prf_seq_stp)
int *Str,Base_prf_seq_stp;
{
  int Strx;
  prf_seq_stp_VAL_FNC_OBJ(&Strx,Base_prf_seq_stp,stp_thy_str_idx);
  btl_proof_XTR_STR_OBJ(Str,Strx);
}

mod_stp_thy_str(rep,Base_prf_seq_stp,Str)
int *rep,Base_prf_seq_stp,*Str;
{
  int Str_0,bb;
  prf_seq_stp_VAL_FNC_OBJ(&Str_0,Base_prf_seq_stp,stp_thy_str_idx);
  btl_proof_KIL_STR_OBJ(Str_0);
  btl_proof_NEW_STR_OBJ(&bb,&Str_0,Str);
  if( bb == TRUE ){
    prf_seq_stp_STO_FNC_OBJ(Base_prf_seq_stp,stp_thy_str_idx,Str_0);
  };
  *rep = bb;
}

xtr_stp_rule_str(Str,Base_prf_seq_stp)
int *Str,Base_prf_seq_stp;
{
  int Strx;
  prf_seq_stp_VAL_FNC_OBJ(&Strx,Base_prf_seq_stp,stp_rule_str_idx);
  btl_proof_XTR_STR_OBJ(Str,Strx);
}

mod_stp_rule_str(rep,Base_prf_seq_stp,Str)
int *rep,Base_prf_seq_stp,*Str;
{
  int Str_0,bb;
  prf_seq_stp_VAL_FNC_OBJ(&Str_0,Base_prf_seq_stp,stp_rule_str_idx);
  btl_proof_KIL_STR_OBJ(Str_0);
  btl_proof_NEW_STR_OBJ(&bb,&Str_0,Str);
  if( bb == TRUE ){
    prf_seq_stp_STO_FNC_OBJ(Base_prf_seq_stp,stp_rule_str_idx,Str_0);
  };
  *rep = bb;
}

val_stp_posn(nat,Base_prf_seq_stp)
int *nat,Base_prf_seq_stp;
{
  prf_seq_stp_VAL_FNC_OBJ(nat,Base_prf_seq_stp,stp_posn_idx);
}

