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
extern int MRIState_ffnc_objP2;
extern int MRIState_ffnc_objP3;
extern int MRIState_fnc_obj[];
extern int MRIState_ssize_fnc_obj;
extern int MRIState_old_fnc_obj[];
extern int MRIState_sold_fnc_obj;

char MRIState_buf_ffnc_obj[1000];

#define MRIState_CHARperWORD 4

#define INI_MRIState_ffnc_obj() \
{MRIState_ssize_fnc_obj = 0; MRIState_sold_fnc_obj=0;}

#define MRIState_INI_FNC_OBJ() \
{MRIState_ssize_fnc_obj = 0; MRIState_sold_fnc_obj=0;}

#define MRIState_ANY_FNC_OBJ(vv) \
{*(vv) = 1;}

#define MRIState_TST_FLD_FNC_OBJ(bb,pp) \
{ *(bb) = ( ( (pp>0) && (pp<=MRIState_ffnc_objP2) )!=0) ;}



#define MRIState_FUL_FNC_OBJ(bb) \
{*(bb) = (((MRIState_ssize_fnc_obj - MRIState_sold_fnc_obj) == MRIState_ffnc_objP3)!=0);}

#define MRIState_DEF_FNC_OBJ(bb,ff,ii) \
{*(bb) = (MRIState_fnc_obj[(ff-1)*MRIState_ffnc_objP2+ii] != 2147483647)!=0;}

#define MRIState_VAL_FNC_OBJ(vv,ff,ii) \
{*(vv) = MRIState_fnc_obj[(ff-1)*MRIState_ffnc_objP2+ii];}

#define MRIState_STO_FNC_OBJ(ff,ii,vv) \
{MRIState_fnc_obj[(ff-1)*MRIState_ffnc_objP2+(ii)] = (vv);}

#define MRIState_RMV_FNC_OBJ(ff,ii) \
{MRIState_fnc_obj[(ff-1)*MRIState_ffnc_objP2+ii] = 2147483647;}

#define MRIState_KIL_FNC_OBJ(ff) \
{MRIState_sold_fnc_obj=MRIState_sold_fnc_obj+1; \
MRIState_old_fnc_obj[MRIState_sold_fnc_obj]=ff;}

void MRIState_CRE_FNC_OBJ();
void MRIState_XST_FNC_OBJ();
void MRIState_SAV_FNC_OBJ();
void MRIState_SAVN_FNC_OBJ();
void MRIState_RST_FNC_OBJ();
void MRIState_RSTN_FNC_OBJ();
void MRIState_FIRST_FNC_OBJ();
void MRIState_NEXT_FNC_OBJ();
void MRIState_OVR_LIT_FFNC_OBJ();
void MRIState_OVR_FFNC_OBJ();
void MRIState_EQL_FFNC_OBJ();
void MRIState_MOV_FFNC_OBJ();
void MRIState_XTR_FFNC_OBJ();
