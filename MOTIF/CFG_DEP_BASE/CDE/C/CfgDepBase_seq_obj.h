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
extern char * CfgDepBase_seq_objP1 [];
extern int CfgDepBase_seq_objP2;
extern int CfgDepBase_seq_objP3;
extern int CfgDepBase_tot_seq_obj;

extern int CfgDepBase_adr_seq_obj[];
extern int CfgDepBase_ssiz_adr_seq_obj;

extern int CfgDepBase_len_seq_obj[];
extern int CfgDepBase_ssiz_len_seq_obj;

extern int CfgDepBase_old_seq_obj[];
extern int CfgDepBase_ssiz_old_seq_obj;

extern int CfgDepBase_array_seq_obj[];

#define CfgDepBase_MEM_FUL_SEQ_OBJ(bb) \
{*(bb) = ((CfgDepBase_tot_seq_obj == 0)!=0);}

#define CfgDepBase_OBJ_FUL_SEQ_OBJ(bb)     \
{*(bb) = ((CfgDepBase_ssiz_len_seq_obj-1-CfgDepBase_ssiz_old_seq_obj == CfgDepBase_seq_objP2)!=0);}

#define CfgDepBase_FRE_MEM_SEQ_OBJ(nn) \
{*(nn) =  CfgDepBase_tot_seq_obj;}

#define CfgDepBase_FRE_OBJ_SEQ_OBJ(nn)     \
{*(nn) = (CfgDepBase_seq_objP2-CfgDepBase_ssiz_len_seq_obj+1+CfgDepBase_ssiz_old_seq_obj);}

#define CfgDepBase_ANY_SEQ_OBJ(nn)  \
{*(nn) = 1;}

#define CfgDepBase_XST_IDX_SEQ_OBJ(bb,pp,ii)   \
{*(bb) = ((ii>0) && (ii <= CfgDepBase_len_seq_obj[pp]))!=0;}

#define CfgDepBase_CLR_SEQ_OBJ(ss) \
{CfgDepBase_tot_seq_obj = CfgDepBase_tot_seq_obj+CfgDepBase_len_seq_obj[ss]; \
 CfgDepBase_len_seq_obj[ss] = 0;}

#define CfgDepBase_KIL_SEQ_OBJ(pp) \
{CfgDepBase_CLR_SEQ_OBJ(pp); \
 CfgDepBase_ssiz_old_seq_obj=CfgDepBase_ssiz_old_seq_obj+1; \
 CfgDepBase_old_seq_obj[CfgDepBase_ssiz_old_seq_obj]=pp;}

#define CfgDepBase_STO_SEQ_OBJ(ss,ii,vv)  \
{CfgDepBase_array_seq_obj[ii+CfgDepBase_adr_seq_obj[ss]] = vv;}

#define CfgDepBase_VAL_SEQ_OBJ(vv,ss,ii)  \
{*(vv) = CfgDepBase_array_seq_obj[ii+CfgDepBase_adr_seq_obj[ss]];}

#define CfgDepBase_POP_SEQ_OBJ(pp)        \
{CfgDepBase_len_seq_obj[pp] = CfgDepBase_len_seq_obj[pp]-1; \
 CfgDepBase_tot_seq_obj = CfgDepBase_tot_seq_obj+1;}

#define CfgDepBase_KEP_SEQ_OBJ(pp,ii)      \
       {CfgDepBase_tot_seq_obj = CfgDepBase_tot_seq_obj+CfgDepBase_len_seq_obj[pp]-(ii); \
        CfgDepBase_len_seq_obj[pp] = ii;}

#define CfgDepBase_LEN_SEQ_OBJ(nn,pp)     \
{*(nn) = CfgDepBase_len_seq_obj[pp];}

#define CfgDepBase_EMP_SEQ_OBJ(bb,pp)   \
{*(bb) = (CfgDepBase_len_seq_obj[pp]==0)!=0;}

void INI_CfgDepBase_seq_obj();
void CfgDepBase_INI_SEQ_OBJ();
void CfgDepBase_XST_SEQ_OBJ();
void CfgDepBase_SAV_SEQ_OBJ();
void CfgDepBase_SAVN_SEQ_OBJ();
void CfgDepBase_RST_SEQ_OBJ();
void CfgDepBase_RSTN_SEQ_OBJ();
void CfgDepBase_CRE_SEQ_OBJ();
void CfgDepBase_PSH_SEQ_OBJ();
void CfgDepBase_EQL_SEQ_OBJ();
void CfgDepBase_MBR_SEQ_OBJ();
void CfgDepBase_APP_SEQ_OBJ();
void CfgDepBase_CPY_SEQ_OBJ();
void CfgDepBase_OVR_SEQ_OBJ();
void CfgDepBase_CUT_SEQ_OBJ();
void CfgDepBase_SWP_SEQ_OBJ();
void CfgDepBase_REV_SEQ_OBJ();
void CfgDepBase_FIRST_SEQ_OBJ();
void CfgDepBase_NEXT_SEQ_OBJ();
void CfgDepBase_OUTPUT_SEQ_OBJ();
void CfgDepBase_INPUT_SEQ_OBJ();
