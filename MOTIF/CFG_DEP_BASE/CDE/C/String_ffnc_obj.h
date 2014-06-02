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
extern int String_ffnc_objP2;
extern int String_ffnc_objP3;
extern int String_fnc_obj[];
extern int String_ssize_fnc_obj;
extern int String_old_fnc_obj[];
extern int String_sold_fnc_obj;

#define INI_String_ffnc_obj() \
{String_ssize_fnc_obj = 0; String_sold_fnc_obj=0;}

#define String_INI_FNC_OBJ() \
{String_ssize_fnc_obj = 0; String_sold_fnc_obj=0;}

#define String_ANY_FNC_OBJ(vv) \
{*(vv) = 1;}

#define String_TST_FLD_FNC_OBJ(bb,pp) \
{ *(bb) = ( ( (pp>0) && (pp<=String_ffnc_objP2) )!=0) ;}



#define String_FUL_FNC_OBJ(bb) \
{*(bb) = (((String_ssize_fnc_obj - String_sold_fnc_obj) == String_ffnc_objP3)!=0);}

#define String_DEF_FNC_OBJ(bb,ff,ii) \
{*(bb) = (String_fnc_obj[(ff-1)*String_ffnc_objP2+ii] != 2147483647)!=0;}

#define String_VAL_FNC_OBJ(vv,ff,ii) \
{*(vv) = String_fnc_obj[(ff-1)*String_ffnc_objP2+ii];}

#define String_STO_FNC_OBJ(ff,ii,vv) \
{String_fnc_obj[(ff-1)*String_ffnc_objP2+(ii)] = (vv);}

#define String_RMV_FNC_OBJ(ff,ii) \
{String_fnc_obj[(ff-1)*String_ffnc_objP2+ii] = 2147483647;}

#define String_KIL_FNC_OBJ(ff) \
{String_sold_fnc_obj=String_sold_fnc_obj+1; \
String_old_fnc_obj[String_sold_fnc_obj]=ff;}

void String_CRE_FNC_OBJ();
void String_XST_FNC_OBJ();
void String_SAV_FNC_OBJ();
void String_SAVN_FNC_OBJ();
void String_RST_FNC_OBJ();
void String_RSTN_FNC_OBJ();
void String_FIRST_FNC_OBJ();
void String_NEXT_FNC_OBJ();
void String_OVR_LIT_FFNC_OBJ();
void String_OVR_FFNC_OBJ();
void String_EQL_FFNC_OBJ();
void String_MOV_FFNC_OBJ();
void String_XTR_FFNC_OBJ();
