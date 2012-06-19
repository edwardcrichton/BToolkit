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
extern int Rename_NvarP1;
extern int Rename_Nscv;

#define INI_Rename_Nvar()   {Rename_Nscv = 0;}
#define Rename_VAL_NVAR(uu) {*(uu) = Rename_Nscv;}
#define Rename_STO_NVAR(vv) {Rename_Nscv = vv;}
#define Rename_MIN_NVAR(uu,vv) {if( Rename_Nscv<=vv ){ *(uu) = Rename_Nscv ;}else{ *(uu) = vv ;};}
#define Rename_MAX_NVAR(uu,vv) {if( Rename_Nscv>=vv ){ *(uu) = Rename_Nscv ;}else{ *(uu) = vv ;};}
#define Rename_PRE_INC_NVAR(bb)   {*(bb) = \
                    ((Rename_Nscv < Rename_NvarP1)!=0);}
#define Rename_INC_NVAR()   {Rename_Nscv = Rename_Nscv+1;}

#define Rename_PRE_DEC_NVAR(bb)  {*(bb) = ((Rename_Nscv > 0)!=0);}
#define Rename_DEC_NVAR()  {Rename_Nscv = Rename_Nscv-1;}

#define Rename_PRE_ADD_NVAR(bb,vv) {*(bb) = \
                   ((vv<=Rename_NvarP1-Rename_Nscv)!=0);}
#define Rename_ADD_NVAR(vv) {Rename_Nscv = Rename_Nscv+(vv);}

#define Rename_PRE_SUB_NVAR(bb,vv) {*(bb) = ((vv<=Rename_Nscv)!=0);}
#define Rename_SUB_NVAR(vv) {Rename_Nscv = Rename_Nscv-(vv);}

#define Rename_PRE_MUL_NVAR(bb,vv) {*(bb) = \
                    ( (Rename_Nscv!=0) ? ((vv<=Rename_NvarP1/Rename_Nscv)!=0) : 1) ;} 
#define Rename_MUL_NVAR(vv) {Rename_Nscv = Rename_Nscv*(vv);}

#define Rename_PRE_DIV_NVAR(bb,vv) {*(bb) = ((vv>0)!=0);}
#define Rename_DIV_NVAR(vv) {Rename_Nscv = Rename_Nscv/(vv);}

#define Rename_PRE_MOD_NVAR(bb,vv) {*(bb) = ((vv>0)!=0);}
#define Rename_MOD_NVAR(vv) {Rename_Nscv = Rename_Nscv-(vv)*(Rename_Nscv/(vv));}

#define Rename_EQL_NVAR(bb,vv) {*(bb) = ((Rename_Nscv==vv)!=0);}
#define Rename_NEQ_NVAR(bb,vv) {*(bb) = ((Rename_Nscv!=vv)!=0);}
#define Rename_GTR_NVAR(bb,vv) {*(bb) = ((Rename_Nscv> vv)!=0);}
#define Rename_GEQ_NVAR(bb,vv) {*(bb) = ((Rename_Nscv>=vv)!=0);}
#define Rename_SMR_NVAR(bb,vv) {*(bb) = ((Rename_Nscv< vv)!=0);}
#define Rename_LEQ_NVAR(bb,vv) {*(bb) = ((Rename_Nscv<=vv)!=0);}

void Rename_SAV_NVAR();
void Rename_SAVN_NVAR();
void Rename_RST_NVAR();
void Rename_RSTN_NVAR();
