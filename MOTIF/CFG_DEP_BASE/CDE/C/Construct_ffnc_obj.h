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
extern int Construct_ffnc_objP2;
extern int Construct_ffnc_objP3;
extern int Construct_fnc_obj[];
extern int Construct_ssize_fnc_obj;
extern int Construct_old_fnc_obj[];
extern int Construct_sold_fnc_obj;

#define INI_Construct_ffnc_obj() \
{Construct_ssize_fnc_obj = 0; Construct_sold_fnc_obj=0;}

#define Construct_INI_FNC_OBJ() \
{Construct_ssize_fnc_obj = 0; Construct_sold_fnc_obj=0;}

#define Construct_ANY_FNC_OBJ(vv) \
{*(vv) = 1;}

#define Construct_TST_FLD_FNC_OBJ(bb,pp) \
{ *(bb) = ( ( (pp>0) && (pp<=Construct_ffnc_objP2) )!=0) ;}



#define Construct_FUL_FNC_OBJ(bb) \
{*(bb) = (((Construct_ssize_fnc_obj - Construct_sold_fnc_obj) == Construct_ffnc_objP3)!=0);}

#define Construct_DEF_FNC_OBJ(bb,ff,ii) \
{*(bb) = (Construct_fnc_obj[(ff-1)*Construct_ffnc_objP2+ii] != 2147483647)!=0;}

#define Construct_VAL_FNC_OBJ(vv,ff,ii) \
{*(vv) = Construct_fnc_obj[(ff-1)*Construct_ffnc_objP2+ii];}

#define Construct_STO_FNC_OBJ(ff,ii,vv) \
{Construct_fnc_obj[(ff-1)*Construct_ffnc_objP2+(ii)] = (vv);}

#define Construct_RMV_FNC_OBJ(ff,ii) \
{Construct_fnc_obj[(ff-1)*Construct_ffnc_objP2+ii] = 2147483647;}

#define Construct_KIL_FNC_OBJ(ff) \
{Construct_sold_fnc_obj=Construct_sold_fnc_obj+1; \
Construct_old_fnc_obj[Construct_sold_fnc_obj]=ff;}

void Construct_CRE_FNC_OBJ();
void Construct_XST_FNC_OBJ();
void Construct_SAV_FNC_OBJ();
void Construct_SAVN_FNC_OBJ();
void Construct_RST_FNC_OBJ();
void Construct_RSTN_FNC_OBJ();
void Construct_FIRST_FNC_OBJ();
void Construct_NEXT_FNC_OBJ();
void Construct_OVR_LIT_FFNC_OBJ();
void Construct_OVR_FFNC_OBJ();
void Construct_EQL_FFNC_OBJ();
void Construct_MOV_FFNC_OBJ();
void Construct_XTR_FFNC_OBJ();
