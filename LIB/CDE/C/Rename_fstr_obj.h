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
extern int Rename_fstr_objP1;
extern int Rename_fstr_objP2;
extern int Rename_tot_fstr_obj;

extern int Rename_adr_fstr_obj[];
extern int Rename_ssiz_adr_fstr_obj;

extern int Rename_len_fstr_obj[];
extern int Rename_ssiz_len_fstr_obj;

extern int Rename_old_fstr_obj[];
extern int Rename_ssiz_old_fstr_obj;

extern char Rename_array_fstr_obj[];

char Rename_buf_fstr_obj[1000];


#define Rename_MEM_FUL_FSTR_OBJ(bb) \
{*(bb) = ((Rename_tot_fstr_obj == 0)!=0);}

#define Rename_OBJ_FUL_FSTR_OBJ(bb)     \
{*(bb) = ((Rename_ssiz_len_fstr_obj-1-Rename_ssiz_old_fstr_obj == Rename_fstr_objP1)!=0);}

#define Rename_FRE_MEM_FSTR_OBJ(nn) \
{*(nn) =  Rename_tot_fstr_obj;}

#define Rename_FRE_OBJ_FSTR_OBJ(nn)     \
{*(nn) = (Rename_fstr_objP1-Rename_ssiz_len_fstr_obj+1+Rename_ssiz_old_fstr_obj);}

#define Rename_ANY_FSTR_OBJ(nn)  \
{*(nn) = 1;}

#define Rename_XST_IDX_FSTR_OBJ(bb,pp,ii)   \
{*(bb) = ((ii>0) && (ii <= Rename_len_fstr_obj[pp]))!=0;}

#define Rename_CLR_FSTR_OBJ(ss) \
{Rename_tot_fstr_obj = Rename_tot_fstr_obj+Rename_len_fstr_obj[ss]; \
 Rename_len_fstr_obj[ss] = 0;}

#define Rename_KIL_FSTR_OBJ(pp) \
{Rename_CLR_FSTR_OBJ(pp); \
 Rename_ssiz_old_fstr_obj=Rename_ssiz_old_fstr_obj+1; \
 Rename_old_fstr_obj[Rename_ssiz_old_fstr_obj]=pp;}

#define Rename_STO_FSTR_OBJ(ss,ii,vv)  \
{Rename_array_fstr_obj[ii+Rename_adr_fstr_obj[ss]] = vv;}

#define Rename_VAL_FSTR_OBJ(vv,ss,ii)  \
{*(vv) = Rename_array_fstr_obj[ii+Rename_adr_fstr_obj[ss]];}

#define Rename_POP_FSTR_OBJ(pp)        \
{Rename_len_fstr_obj[pp] = Rename_len_fstr_obj[pp]-1; \
 Rename_tot_fstr_obj = Rename_tot_fstr_obj+1;}

#define Rename_KEP_FSTR_OBJ(pp,ii)      \
{Rename_tot_fstr_obj = Rename_tot_fstr_obj+Rename_len_fstr_obj[pp]-(ii); \
 Rename_len_fstr_obj[pp] = ii;}

#define Rename_LEN_FSTR_OBJ(nn,pp)     \
{*(nn) = Rename_len_fstr_obj[pp];}

#define Rename_EMP_FSTR_OBJ(bb,pp)   \
{*(bb) = (Rename_len_fstr_obj[pp]==0)!=0;}

void INI_Rename_fstr_obj();
void Rename_INI_FSTR_OBJ();
void Rename_XST_FSTR_OBJ();
void Rename_SAV_FSTR_OBJ();
void Rename_SAVN_FSTR_OBJ();
void Rename_RST_FSTR_OBJ();
void Rename_RSTN_FSTR_OBJ();
void Rename_CRE_FSTR_OBJ();
void Rename_PSH_FSTR_OBJ();
void Rename_SMR_FSTR_OBJ();
void Rename_EQL_FSTR_OBJ();
void Rename_EQL_LIT_FSTR_OBJ();
void Rename_NEW_FSTR_OBJ();
void Rename_XTR_FSTR_OBJ();
void Rename_APP_FSTR_OBJ();
void Rename_CPY_FSTR_OBJ();
void Rename_OVR_FSTR_OBJ();
void Rename_CUT_FSTR_OBJ();
void Rename_SWP_FSTR_OBJ();
void Rename_REV_FSTR_OBJ();
void Rename_FIRST_FSTR_OBJ();
void Rename_NEXT_FSTR_OBJ();
