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
extern int Rename_fnc_objP2;
extern int Rename_fnc_objP3;
extern int Rename_fnc_obj[];
extern int Rename_ssize_fnc_obj;
extern int Rename_old_fnc_obj[];
extern int Rename_sold_fnc_obj;

#define INI_Rename_fnc_obj() \
{Rename_ssize_fnc_obj = 0; Rename_sold_fnc_obj=0;}

#define Rename_INI_FNC_OBJ() \
{Rename_ssize_fnc_obj = 0; Rename_sold_fnc_obj=0;}

#define Rename_ANY_FNC_OBJ(vv) \
{*(vv) = 1;}

#define Rename_TST_FLD_FNC_OBJ(bb,pp) \
{ *(bb) = ( ( (pp>0) && (pp<=Rename_fnc_objP2) )!=0) ;}



#define Rename_FUL_FNC_OBJ(bb) \
{*(bb) = (((Rename_ssize_fnc_obj - Rename_sold_fnc_obj) == Rename_fnc_objP3)!=0);}

#define Rename_DEF_FNC_OBJ(bb,ff,ii) \
{*(bb) = (Rename_fnc_obj[(ff-1)*Rename_fnc_objP2+ii] != 2147483647)!=0;}

#define Rename_VAL_FNC_OBJ(vv,ff,ii) \
{*(vv) = Rename_fnc_obj[(ff-1)*Rename_fnc_objP2+ii];}

#define Rename_STO_FNC_OBJ(ff,ii,vv) \
{Rename_fnc_obj[(ff-1)*Rename_fnc_objP2+ii] = vv;}

#define Rename_RMV_FNC_OBJ(ff,ii) \
{Rename_fnc_obj[(ff-1)*Rename_fnc_objP2+ii] = 2147483647;}

#define Rename_KIL_FNC_OBJ(ff) \
{Rename_sold_fnc_obj=Rename_sold_fnc_obj+1; \
Rename_old_fnc_obj[Rename_sold_fnc_obj]=ff;}

void Rename_CRE_FNC_OBJ();
void Rename_XST_FNC_OBJ();
void Rename_SAV_FNC_OBJ();
void Rename_SAVN_FNC_OBJ();
void Rename_RST_FNC_OBJ();
void Rename_RSTN_FNC_OBJ();
void Rename_FIRST_FNC_OBJ();
void Rename_NEXT_FNC_OBJ();
