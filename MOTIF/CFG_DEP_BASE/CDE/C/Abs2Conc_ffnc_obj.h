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
extern int Abs2Conc_ffnc_objP2;
extern int Abs2Conc_ffnc_objP3;
extern int Abs2Conc_fnc_obj[];
extern int Abs2Conc_ssize_fnc_obj;
extern int Abs2Conc_old_fnc_obj[];
extern int Abs2Conc_sold_fnc_obj;

char Abs2Conc_buf_ffnc_obj[1000];

#define Abs2Conc_CHARperWORD 4

#define INI_Abs2Conc_ffnc_obj() \
{Abs2Conc_ssize_fnc_obj = 0; Abs2Conc_sold_fnc_obj=0;}

#define Abs2Conc_INI_FNC_OBJ() \
{Abs2Conc_ssize_fnc_obj = 0; Abs2Conc_sold_fnc_obj=0;}

#define Abs2Conc_ANY_FNC_OBJ(vv) \
{*(vv) = 1;}

#define Abs2Conc_TST_FLD_FNC_OBJ(bb,pp) \
{ *(bb) = ( ( (pp>0) && (pp<=Abs2Conc_ffnc_objP2) )!=0) ;}



#define Abs2Conc_FUL_FNC_OBJ(bb) \
{*(bb) = (((Abs2Conc_ssize_fnc_obj - Abs2Conc_sold_fnc_obj) == Abs2Conc_ffnc_objP3)!=0);}

#define Abs2Conc_DEF_FNC_OBJ(bb,ff,ii) \
{*(bb) = (Abs2Conc_fnc_obj[(ff-1)*Abs2Conc_ffnc_objP2+ii] != 2147483647)!=0;}

#define Abs2Conc_VAL_FNC_OBJ(vv,ff,ii) \
{*(vv) = Abs2Conc_fnc_obj[(ff-1)*Abs2Conc_ffnc_objP2+ii];}

#define Abs2Conc_STO_FNC_OBJ(ff,ii,vv) \
{Abs2Conc_fnc_obj[(ff-1)*Abs2Conc_ffnc_objP2+(ii)] = (vv);}

#define Abs2Conc_RMV_FNC_OBJ(ff,ii) \
{Abs2Conc_fnc_obj[(ff-1)*Abs2Conc_ffnc_objP2+ii] = 2147483647;}

#define Abs2Conc_KIL_FNC_OBJ(ff) \
{Abs2Conc_sold_fnc_obj=Abs2Conc_sold_fnc_obj+1; \
Abs2Conc_old_fnc_obj[Abs2Conc_sold_fnc_obj]=ff;}

void Abs2Conc_CRE_FNC_OBJ();
void Abs2Conc_XST_FNC_OBJ();
void Abs2Conc_SAV_FNC_OBJ();
void Abs2Conc_SAVN_FNC_OBJ();
void Abs2Conc_RST_FNC_OBJ();
void Abs2Conc_RSTN_FNC_OBJ();
void Abs2Conc_FIRST_FNC_OBJ();
void Abs2Conc_NEXT_FNC_OBJ();
void Abs2Conc_OVR_LIT_FFNC_OBJ();
void Abs2Conc_OVR_FFNC_OBJ();
void Abs2Conc_EQL_FFNC_OBJ();
void Abs2Conc_MOV_FFNC_OBJ();
void Abs2Conc_XTR_FFNC_OBJ();
