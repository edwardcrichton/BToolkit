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
extern int Seqstr_ffnc_objP2;
extern int Seqstr_ffnc_objP3;
extern int Seqstr_fnc_obj[];
extern int Seqstr_ssize_fnc_obj;
extern int Seqstr_old_fnc_obj[];
extern int Seqstr_sold_fnc_obj;

#define INI_Seqstr_ffnc_obj() \
{Seqstr_ssize_fnc_obj = 0; Seqstr_sold_fnc_obj=0;}

#define Seqstr_INI_FNC_OBJ() \
{Seqstr_ssize_fnc_obj = 0; Seqstr_sold_fnc_obj=0;}

#define Seqstr_ANY_FNC_OBJ(vv) \
{*(vv) = 1;}

#define Seqstr_TST_FLD_FNC_OBJ(bb,pp) \
{ *(bb) = ( ( (pp>0) && (pp<=Seqstr_ffnc_objP2) )!=0) ;}



#define Seqstr_FUL_FNC_OBJ(bb) \
{*(bb) = (((Seqstr_ssize_fnc_obj - Seqstr_sold_fnc_obj) == Seqstr_ffnc_objP3)!=0);}

#define Seqstr_DEF_FNC_OBJ(bb,ff,ii) \
{*(bb) = (Seqstr_fnc_obj[(ff-1)*Seqstr_ffnc_objP2+ii] != 2147483647)!=0;}

#define Seqstr_VAL_FNC_OBJ(vv,ff,ii) \
{*(vv) = Seqstr_fnc_obj[(ff-1)*Seqstr_ffnc_objP2+ii];}

#define Seqstr_STO_FNC_OBJ(ff,ii,vv) \
{Seqstr_fnc_obj[(ff-1)*Seqstr_ffnc_objP2+(ii)] = (vv);}

#define Seqstr_RMV_FNC_OBJ(ff,ii) \
{Seqstr_fnc_obj[(ff-1)*Seqstr_ffnc_objP2+ii] = 2147483647;}

#define Seqstr_KIL_FNC_OBJ(ff) \
{Seqstr_sold_fnc_obj=Seqstr_sold_fnc_obj+1; \
Seqstr_old_fnc_obj[Seqstr_sold_fnc_obj]=ff;}

void Seqstr_CRE_FNC_OBJ();
void Seqstr_XST_FNC_OBJ();
void Seqstr_SAV_FNC_OBJ();
void Seqstr_SAVN_FNC_OBJ();
void Seqstr_RST_FNC_OBJ();
void Seqstr_RSTN_FNC_OBJ();
void Seqstr_FIRST_FNC_OBJ();
void Seqstr_NEXT_FNC_OBJ();
void Seqstr_OVR_LIT_FFNC_OBJ();
void Seqstr_OVR_FFNC_OBJ();
void Seqstr_EQL_FFNC_OBJ();
void Seqstr_MOV_FFNC_OBJ();
void Seqstr_XTR_FFNC_OBJ();
