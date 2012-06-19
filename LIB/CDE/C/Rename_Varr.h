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
extern int Rename_VarrP2; 
extern int Rename_Varray[];
#define INI_Rename_Varr()      {}
#define Rename_TST_IDX_ARR(bb,ii) {*(bb) = \
                         (((ii>=1) && (ii<=Rename_VarrP2))!=0);}
#define Rename_VAL_ARR(vv,ii) {*(vv) = Rename_Varray[ii];}
#define Rename_STO_ARR(ii,vv) {Rename_Varray[ii] = vv;}
#define Rename_ADD_ARR(ii,vv) {Rename_Varray[ii] = Rename_Varray[ii]+(vv);}
#define Rename_SUB_ARR(ii,vv) {Rename_Varray[ii] = Rename_Varray[ii]-(vv);}
#define Rename_MUL_ARR(ii,vv) {Rename_Varray[ii] = Rename_Varray[ii]*(vv);}
#define Rename_DIV_ARR(ii,vv) {Rename_Varray[ii] = Rename_Varray[ii]/(vv);}
#define Rename_MOD_ARR(ii,vv) \
{Rename_Varray[ii] = Rename_Varray[ii]-(vv)*(Rename_Varray[ii]/(vv));}

#define Rename_EQL_ARR(bb,ii,vv) {*(bb) = ((Rename_Varray[ii]==(vv))!=0);}
#define Rename_NEQ_ARR(bb,ii,vv) {*(bb) = ((Rename_Varray[ii]!=(vv))!=0);}
#define Rename_GTR_ARR(bb,ii,vv) {*(bb) = ((Rename_Varray[ii]> (vv))!=0);}
#define Rename_GEQ_ARR(bb,ii,vv) {*(bb) = ((Rename_Varray[ii]>=(vv))!=0);}
#define Rename_SMR_ARR(bb,ii,vv) {*(bb) = ((Rename_Varray[ii]< (vv))!=0);}
#define Rename_LEQ_ARR(bb,ii,vv) {*(bb) = ((Rename_Varray[ii]<=(vv))!=0);}

void Rename_SAV_ARR();
void Rename_SAVN_ARR();
void Rename_RST_ARR();
void Rename_RSTN_ARR();
void Rename_SWP_ARR();
void Rename_SCH_LO_EQL_ARR();
void Rename_SCH_LO_NEQ_ARR();
void Rename_SCH_HI_EQL_ARR();
void Rename_SCH_HI_NEQ_ARR();
void Rename_REV_ARR();
void Rename_RHT_ARR();
void Rename_LFT_ARR();
