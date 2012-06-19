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
extern char * CfgDepBase_set_objP1 [];
extern int CfgDepBase_set_objP2;
extern int CfgDepBase_set_objP3;
extern int CfgDepBase_tot_set_obj;

extern int CfgDepBase_adr_set_obj[];
extern int CfgDepBase_ssiz_adr_set_obj;

extern int CfgDepBase_len_set_obj[];
extern int CfgDepBase_ssiz_len_set_obj;

extern int CfgDepBase_old_set_obj[];
extern int CfgDepBase_ssiz_old_set_obj;

extern int CfgDepBase_array_set_obj[];

#define CfgDepBase_MEM_FUL_SET_OBJ(bb) \
{*(bb) = ((CfgDepBase_tot_set_obj == 0)!=0);}

#define CfgDepBase_OBJ_FUL_SET_OBJ(bb)     \
{*(bb) = ((CfgDepBase_ssiz_len_set_obj-1-CfgDepBase_ssiz_old_set_obj == CfgDepBase_set_objP2)!=0);}

#define CfgDepBase_ANY_SET_OBJ(pp) \
{*(pp) = 1; }

#define CfgDepBase_FRE_MEM_SET_OBJ(nn) \
{*(nn) =  CfgDepBase_tot_set_obj;}

#define CfgDepBase_FRE_OBJ_SET_OBJ(nn)     \
{*(nn) = (CfgDepBase_set_objP2-CfgDepBase_ssiz_len_set_obj+1+CfgDepBase_ssiz_old_set_obj);}

#define CfgDepBase_XST_ORD_SET_OBJ(bb,pp,ii)   \
{*(bb) = ((ii>0) && (ii <= CfgDepBase_len_set_obj[pp]))!=0;}

#define CfgDepBase_EMP_SET_OBJ(bb,pp)  \
{*(bb) = ((CfgDepBase_len_set_obj[pp] == 0)!=0);}

#define CfgDepBase_CLR_SET_OBJ(ss) \
{CfgDepBase_tot_set_obj = CfgDepBase_tot_set_obj+CfgDepBase_len_set_obj[ss];CfgDepBase_len_set_obj[ss] = 0;}

#define CfgDepBase_KIL_SET_OBJ(pp) \
{CfgDepBase_CLR_SET_OBJ(pp); \
 CfgDepBase_ssiz_old_set_obj=CfgDepBase_ssiz_old_set_obj+1; \
 CfgDepBase_old_set_obj[CfgDepBase_ssiz_old_set_obj]=pp;}

#define CfgDepBase_STO_SET_OBJ(ss,ii,vv)  \
{CfgDepBase_array_set_obj[ii+CfgDepBase_adr_set_obj[ss]] = vv;}

#define CfgDepBase_VAL_SET_OBJ(vv,ss,ii)  \
{*(vv) = CfgDepBase_array_set_obj[ii+CfgDepBase_adr_set_obj[ss]];}

#define CfgDepBase_POP_SET_OBJ(pp)        \
{CfgDepBase_len_set_obj[pp] = CfgDepBase_len_set_obj[pp]-1; CfgDepBase_tot_set_obj = CfgDepBase_tot_set_obj+1;}

#define CfgDepBase_LEN_SET_OBJ(nn,pp)     \
{*(nn) = CfgDepBase_len_set_obj[pp];}

#define CfgDepBase_CRD_SET_OBJ(nn,pp)     \
{CfgDepBase_LEN_SET_OBJ(nn,pp);}

void INI_CfgDepBase_set_obj();
void CfgDepBase_INI_SET_OBJ();
void CfgDepBase_XST_SET_OBJ();
void CfgDepBase_SAV_SET_OBJ();
void CfgDepBase_SAVN_SET_OBJ();
void CfgDepBase_RST_SET_OBJ();
void CfgDepBase_RSTN_SET_OBJ();
void CfgDepBase_CRE_SET_OBJ();
void CfgDepBase_UNION_SET_OBJ();
void CfgDepBase_DIFF_SET_OBJ();
void CfgDepBase_INTER_SET_OBJ();
void CfgDepBase_INCL_SET_OBJ();
void CfgDepBase_MBR_SET_OBJ();
void CfgDepBase_ENT_SET_OBJ();
void CfgDepBase_RMV_SET_OBJ();
void CfgDepBase_CPY_SET_OBJ();
void CfgDepBase_FIRST_SET_OBJ();
void CfgDepBase_NEXT_SET_OBJ();
void CfgDepBase_OUTPUT_SET_OBJ();
void CfgDepBase_INPUT_SET_OBJ();
