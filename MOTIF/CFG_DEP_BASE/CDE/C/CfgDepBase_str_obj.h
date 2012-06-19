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
extern int CfgDepBase_str_objP1;
extern int CfgDepBase_str_objP2;
extern int CfgDepBase_tot_str_obj;

extern int CfgDepBase_adr_str_obj[];
extern int CfgDepBase_ssiz_adr_str_obj;

extern int CfgDepBase_len_str_obj[];
extern int CfgDepBase_ssiz_len_str_obj;

extern int CfgDepBase_old_str_obj[];
extern int CfgDepBase_ssiz_old_str_obj;

extern char CfgDepBase_array_str_obj[];


#define CfgDepBase_MEM_FUL_STR_OBJ(bb) \
{*(bb) = ((CfgDepBase_tot_str_obj == 0)!=0);}

#define CfgDepBase_OBJ_FUL_STR_OBJ(bb)     \
{*(bb) = ((CfgDepBase_ssiz_len_str_obj-1-CfgDepBase_ssiz_old_str_obj == CfgDepBase_str_objP1)!=0);}

#define CfgDepBase_FRE_MEM_STR_OBJ(nn) \
{*(nn) =  CfgDepBase_tot_str_obj;}

#define CfgDepBase_FRE_OBJ_STR_OBJ(nn)     \
{*(nn) = (CfgDepBase_str_objP1-CfgDepBase_ssiz_len_str_obj+1+CfgDepBase_ssiz_old_str_obj);}

#define CfgDepBase_ANY_STR_OBJ(nn)  \
{*(nn) = 1;}

#define CfgDepBase_XST_IDX_STR_OBJ(bb,pp,ii)   \
{*(bb) = ((ii>0) && (ii <= CfgDepBase_len_str_obj[pp]))!=0;}

#define CfgDepBase_CLR_STR_OBJ(ss) \
{CfgDepBase_tot_str_obj = CfgDepBase_tot_str_obj+CfgDepBase_len_str_obj[ss]; \
 CfgDepBase_len_str_obj[ss] = 0;}

#define CfgDepBase_KIL_STR_OBJ(pp) \
{CfgDepBase_CLR_STR_OBJ(pp); \
 CfgDepBase_ssiz_old_str_obj=CfgDepBase_ssiz_old_str_obj+1; \
 CfgDepBase_old_str_obj[CfgDepBase_ssiz_old_str_obj]=pp;}

#define CfgDepBase_STO_STR_OBJ(ss,ii,vv)  \
{CfgDepBase_array_str_obj[ii+CfgDepBase_adr_str_obj[ss]] = vv;}

#define CfgDepBase_VAL_STR_OBJ(vv,ss,ii)  \
{*(vv) = CfgDepBase_array_str_obj[ii+CfgDepBase_adr_str_obj[ss]];}

#define CfgDepBase_POP_STR_OBJ(pp)        \
{CfgDepBase_len_str_obj[pp] = CfgDepBase_len_str_obj[pp]-1; \
 CfgDepBase_tot_str_obj = CfgDepBase_tot_str_obj+1;}

#define CfgDepBase_KEP_STR_OBJ(pp,ii)      \
{CfgDepBase_tot_str_obj = CfgDepBase_tot_str_obj+CfgDepBase_len_str_obj[pp]-(ii); \
 CfgDepBase_len_str_obj[pp] = ii;}

#define CfgDepBase_LEN_STR_OBJ(nn,pp)     \
{*(nn) = CfgDepBase_len_str_obj[pp];}

#define CfgDepBase_EMP_STR_OBJ(bb,pp)   \
{*(bb) = (CfgDepBase_len_str_obj[pp]==0)!=0;}

#define CfgDepBase_REL_BUF_STR_OBJ() {}

void INI_CfgDepBase_str_obj();
void CfgDepBase_INI_STR_OBJ();
void CfgDepBase_XST_STR_OBJ();
void CfgDepBase_SAV_STR_OBJ();
void CfgDepBase_SAVN_STR_OBJ();
void CfgDepBase_RST_STR_OBJ();
void CfgDepBase_RSTN_STR_OBJ();
void CfgDepBase_CRE_STR_OBJ();
void CfgDepBase_PSH_STR_OBJ();
void CfgDepBase_SMR_STR_OBJ();
void CfgDepBase_EQL_STR_OBJ();
void CfgDepBase_SUB_STR_OBJ();
void CfgDepBase_EQL_LIT_STR_OBJ();
void CfgDepBase_NEW_STR_OBJ();
void CfgDepBase_XTR_STR_OBJ();
void CfgDepBase_APP_STR_OBJ();
void CfgDepBase_CPY_STR_OBJ();
void CfgDepBase_OVR_STR_OBJ();
void CfgDepBase_CUT_STR_OBJ();
void CfgDepBase_SWP_STR_OBJ();
void CfgDepBase_REV_STR_OBJ();
void CfgDepBase_FIRST_STR_OBJ();
void CfgDepBase_NEXT_STR_OBJ();
