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
extern int GENState_ffnc_objP2;
extern int GENState_ffnc_objP3;
extern int GENState_fnc_obj[];
extern int GENState_ssize_fnc_obj;
extern int GENState_old_fnc_obj[];
extern int GENState_sold_fnc_obj;

#define INI_GENState_ffnc_obj() \
{GENState_ssize_fnc_obj = 0; GENState_sold_fnc_obj=0;}

#define GENState_INI_FNC_OBJ() \
{GENState_ssize_fnc_obj = 0; GENState_sold_fnc_obj=0;}

#define GENState_ANY_FNC_OBJ(vv) \
{*(vv) = 1;}

#define GENState_TST_FLD_FNC_OBJ(bb,pp) \
{ *(bb) = ( ( (pp>0) && (pp<=GENState_ffnc_objP2) )!=0) ;}



#define GENState_FUL_FNC_OBJ(bb) \
{*(bb) = (((GENState_ssize_fnc_obj - GENState_sold_fnc_obj) == GENState_ffnc_objP3)!=0);}

#define GENState_DEF_FNC_OBJ(bb,ff,ii) \
{*(bb) = (GENState_fnc_obj[(ff-1)*GENState_ffnc_objP2+ii] != 2147483647)!=0;}

#define GENState_VAL_FNC_OBJ(vv,ff,ii) \
{*(vv) = GENState_fnc_obj[(ff-1)*GENState_ffnc_objP2+ii];}

#define GENState_STO_FNC_OBJ(ff,ii,vv) \
{GENState_fnc_obj[(ff-1)*GENState_ffnc_objP2+(ii)] = (vv);}

#define GENState_RMV_FNC_OBJ(ff,ii) \
{GENState_fnc_obj[(ff-1)*GENState_ffnc_objP2+ii] = 2147483647;}

#define GENState_KIL_FNC_OBJ(ff) \
{GENState_sold_fnc_obj=GENState_sold_fnc_obj+1; \
GENState_old_fnc_obj[GENState_sold_fnc_obj]=ff;}

void GENState_CRE_FNC_OBJ();
void GENState_XST_FNC_OBJ();
void GENState_SAV_FNC_OBJ();
void GENState_SAVN_FNC_OBJ();
void GENState_RST_FNC_OBJ();
void GENState_RSTN_FNC_OBJ();
void GENState_FIRST_FNC_OBJ();
void GENState_NEXT_FNC_OBJ();
void GENState_OVR_LIT_FFNC_OBJ();
void GENState_OVR_FFNC_OBJ();
void GENState_EQL_FFNC_OBJ();
void GENState_MOV_FFNC_OBJ();
void GENState_XTR_FFNC_OBJ();
