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
extern int Rename_NfncP1;
extern int Rename_NfncP2;

extern int Rename_Nfnc[];

#define Rename_TST_FLD_NFNC(bb,ii) {*(bb) = \
                         (((ii>=1) && (ii<=Rename_NfncP2))!=0);}
#define Rename_DEF_NFNC(bb,ff) {*(bb) = (Rename_Nfnc[ff] != 2147483647)!=0;}
#define Rename_VAL_NFNC(vv,ff) {*(vv) = Rename_Nfnc[ff];}
#define Rename_STO_NFNC(ff,vv) {Rename_Nfnc[ff] = vv;}
#define Rename_RMV_NFNC(ff)    {Rename_Nfnc[ff] = 2147483647;}
#define Rename_ADD_NFNC(ff,vv) {Rename_Nfnc[ff] = Rename_Nfnc[ff]+(vv);}
#define Rename_SUB_NFNC(ff,vv) {Rename_Nfnc[ff] = Rename_Nfnc[ff]-(vv);}
#define Rename_MUL_NFNC(ff,vv) {Rename_Nfnc[ff] = Rename_Nfnc[ff]*(vv);}
#define Rename_DIV_NFNC(ff,vv) {Rename_Nfnc[ff] = Rename_Nfnc[ff]/(vv);}

#define Rename_MOD_NFNC(ff,vv) \
{Rename_Nfnc[ff] = Rename_Nfnc[ff]-(vv)*(Rename_Nfnc[ff]/(vv));}

#define Rename_EQL_NFNC(bb,ff,vv) {*(bb) = ((Rename_Nfnc[ff]==vv)!=0);}
#define Rename_NEQ_NFNC(bb,ff,vv) {*(bb) = ((Rename_Nfnc[ff]!=vv)!=0);}
#define Rename_GTR_NFNC(bb,ff,vv) {*(bb) = ((Rename_Nfnc[ff]> vv)!=0);}
#define Rename_GEQ_NFNC(bb,ff,vv) {*(bb) = ((Rename_Nfnc[ff]>=vv)!=0);}
#define Rename_SMR_NFNC(bb,ff,vv) {*(bb) = ((Rename_Nfnc[ff]< vv)!=0);}
#define Rename_LEQ_NFNC(bb,ff,vv) {*(bb) = ((Rename_Nfnc[ff]<=vv)!=0);}

void Rename_SAV_NFNC();
void Rename_SAVN_NFNC();
void Rename_RST_NFNC();
void Rename_RSTN_NFNC();
void INI_Rename_Nfnc();
void Rename_FREE_NFNC();
