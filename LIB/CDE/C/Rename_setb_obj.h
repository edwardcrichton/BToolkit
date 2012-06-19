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
extern char * Rename_set_objP1 [];
extern int Rename_set_objP2;
extern int Rename_set_objP3;
extern int Rename_tot_set_obj;

extern int Rename_adr_set_obj[];
extern int Rename_ssiz_adr_set_obj;

extern int Rename_len_set_obj[];
extern int Rename_ssiz_len_set_obj;

extern int Rename_old_set_obj[];
extern int Rename_ssiz_old_set_obj;

extern int Rename_array_set_obj[];

#define Rename_STS_SET_OBJ(mm,nn,pp,qq) \
{ \
  *(mm) = (Rename_set_objP3) - Rename_tot_set_obj; \
  *(nn) = (Rename_set_objP3); \
  *(pp) = (Rename_ssiz_len_set_obj-1-Rename_ssiz_old_set_obj); \
  *(qq) = (Rename_set_objP2); \
}

#define Rename_MEM_FUL_SET_OBJ(bb) \
{*(bb) = ((Rename_tot_set_obj == 0)!=0);}

#define Rename_OBJ_FUL_SET_OBJ(bb)     \
{*(bb) = ((Rename_ssiz_len_set_obj-1-Rename_ssiz_old_set_obj == Rename_set_objP2)!=0);}

#define Rename_ANY_SET_OBJ(pp) \
{*(pp) = 1; }

#define Rename_FRE_MEM_SET_OBJ(nn) \
{*(nn) =  Rename_tot_set_obj;}

#define Rename_FRE_OBJ_SET_OBJ(nn)     \
{*(nn) = (Rename_set_objP2-Rename_ssiz_len_set_obj+1+Rename_ssiz_old_set_obj);}

#define Rename_XST_ORD_SET_OBJ(bb,pp,ii)   \
{*(bb) = ((ii>0) && (ii <= Rename_len_set_obj[pp]))!=0;}

#define Rename_EMP_SET_OBJ(bb,pp)  \
{*(bb) = ((Rename_len_set_obj[pp] == 0)!=0);}

#define Rename_CLR_SET_OBJ(ss) \
{Rename_tot_set_obj = Rename_tot_set_obj+Rename_len_set_obj[ss];Rename_len_set_obj[ss] = 0;}

#define Rename_KIL_SET_OBJ(pp) \
{Rename_CLR_SET_OBJ(pp); \
 Rename_ssiz_old_set_obj=Rename_ssiz_old_set_obj+1; \
 Rename_old_set_obj[Rename_ssiz_old_set_obj]=pp;}

#define Rename_STO_SET_OBJ(ss,ii,vv)  \
{Rename_array_set_obj[ii+Rename_adr_set_obj[ss]] = vv;}

#define Rename_VAL_SET_OBJ(vv,ss,ii)  \
{*(vv) = Rename_array_set_obj[ii+Rename_adr_set_obj[ss]];}

#define Rename_POP_SET_OBJ(pp)        \
{Rename_len_set_obj[pp] = Rename_len_set_obj[pp]-1; Rename_tot_set_obj = Rename_tot_set_obj+1;}

#define Rename_LEN_SET_OBJ(nn,pp)     \
{*(nn) = Rename_len_set_obj[pp];}

#define Rename_CRD_SET_OBJ(nn,pp)     \
{Rename_LEN_SET_OBJ(nn,pp);}

void INI_Rename_set_obj();
void Rename_XST_SET_OBJ();
void Rename_SAV_SET_OBJ();
void Rename_SAVN_SET_OBJ();
void Rename_RST_SET_OBJ();
void Rename_RSTN_SET_OBJ();
void Rename_CRE_SET_OBJ();
void Rename_MBR_SET_OBJ();
void Rename_ENT_SET_OBJ();
void Rename_RMV_SET_OBJ();
