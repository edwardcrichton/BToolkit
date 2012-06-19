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
extern int CfgDepBase_VffncP2;
extern int CfgDepBase_Vfnc[];

char CfgDepBase_ffnc_buf[1000];

#define CfgDepBase_CHARperWORD 4

#define CfgDepBase_TST_FLD_FNC(bb,ii) {*(bb) = \
                         (((ii>=1) && (ii<=CfgDepBase_VffncP2))!=0);}
#define CfgDepBase_VAL_ARR(vv,ii) {*(vv) = CfgDepBase_array[ii];}
#define CfgDepBase_DEF_FNC(bb,ff) {*(bb) = (CfgDepBase_Vfnc[ff] != 2147483647)!=0;}
#define CfgDepBase_VAL_FNC(vv,ff) {*(vv) = CfgDepBase_Vfnc[ff];}
#define CfgDepBase_STO_FNC(ff,vv) {CfgDepBase_Vfnc[ff] = vv;}
#define CfgDepBase_RMV_FNC(ff)    {CfgDepBase_Vfnc[ff] = 2147483647;}

#define CfgDepBase_EQL_FNC(bb,ff,vv) {*(bb) = ((CfgDepBase_Vfnc[ff]==vv)!=0);}
#define CfgDepBase_NEQ_FNC(bb,ff,vv) {*(bb) = ((CfgDepBase_Vfnc[ff]!=vv)!=0);}

void CfgDepBase_SAV_FNC();
void CfgDepBase_SAVN_FNC();
void CfgDepBase_RST_FNC();
void CfgDepBase_RSTN_FNC();
void INI_CfgDepBase_Vffnc();
void CfgDepBase_FREE_FNC();
void CfgDepBase_MOV_FFNC();
void CfgDepBase_OVR_LIT_FFNC();
void CfgDepBase_OVR_FFNC();
void CfgDepBase_EQL_FFNC();
void CfgDepBase_XTR_FFNC();
