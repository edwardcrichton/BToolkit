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
extern int Rename_VfncP2;
extern int Rename_Vfnc[];

#define Rename_TST_FLD_FNC(bb,ii) {*(bb) = \
                         (((ii>=1) && (ii<=Rename_VfncP2))!=0);}
#define Rename_DEF_FNC(bb,ff) {*(bb) = (Rename_Vfnc[ff] != 2147483647)!=0;}
#define Rename_VAL_FNC(vv,ff) {*(vv) = Rename_Vfnc[ff];}
#define Rename_STO_FNC(ff,vv) {Rename_Vfnc[ff] = vv;}
#define Rename_RMV_FNC(ff)    {Rename_Vfnc[ff] = 2147483647;}

#define Rename_EQL_FNC(bb,ff,vv) {*(bb) = ((Rename_Vfnc[ff]==vv)!=0);}
#define Rename_NEQ_FNC(bb,ff,vv) {*(bb) = ((Rename_Vfnc[ff]!=vv)!=0);}

void Rename_SAV_FNC();
void Rename_SAVN_FNC();
void Rename_RST_FNC();
void Rename_RSTN_FNC();
void INI_Rename_Vfnc();
void Rename_FREE_FNC();
