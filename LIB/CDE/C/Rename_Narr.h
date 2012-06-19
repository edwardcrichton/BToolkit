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
extern int Rename_NarrP1;
extern int Rename_NarrP2;
extern int Rename_Narray[];
#define INI_Rename_Narr()      { ; }
#define Rename_TST_IDX_NARR(bb,ii) {*(bb) = \
                         (((ii>=1) && (ii<=Rename_NarrP2))!=0);}
#define Rename_VAL_NARR(vv,ii) {*(vv) = Rename_Narray[ii];}
#define Rename_STO_NARR(ii,vv) {Rename_Narray[ii] = (vv);}
#define Rename_ADD_NARR(ii,vv) {Rename_Narray[ii] = Rename_Narray[ii]+(vv);}
#define Rename_SUB_NARR(ii,vv) {Rename_Narray[ii] = Rename_Narray[ii]-(vv);}
#define Rename_MUL_NARR(ii,vv) {Rename_Narray[ii] = Rename_Narray[ii]*(vv);}
#define Rename_DIV_NARR(ii,vv) {Rename_Narray[ii] = Rename_Narray[ii]/(vv);}
#define Rename_MOD_NARR(ii,vv) \
{Rename_Narray[ii] = Rename_Narray[ii]-(vv)*(Rename_Narray[ii]/(vv));}

#define Rename_EQL_NARR(bb,ii,vv) {*(bb) = ((Rename_Narray[ii]==(vv))!=0);}
#define Rename_NEQ_NARR(bb,ii,vv) {*(bb) = ((Rename_Narray[ii]!=(vv))!=0);}
#define Rename_GTR_NARR(bb,ii,vv) {*(bb) = ((Rename_Narray[ii]> (vv))!=0);}
#define Rename_GEQ_NARR(bb,ii,vv) {*(bb) = ((Rename_Narray[ii]>=(vv))!=0);}
#define Rename_SMR_NARR(bb,ii,vv) {*(bb) = ((Rename_Narray[ii]< (vv))!=0);}
#define Rename_LEQ_NARR(bb,ii,vv) {*(bb) = ((Rename_Narray[ii]<=(vv))!=0);}

void Rename_SAV_NARR();
void Rename_SAVN_NARR();
void Rename_RST_NARR();
void Rename_RSTN_NARR();
void Rename_SWP_NARR();
void Rename_MAX_IDX_NARR();
void Rename_MIN_IDX_NARR();
void Rename_SCH_LO_EQL_NARR();
void Rename_SCH_LO_NEQ_NARR();
void Rename_SCH_LO_GEQ_NARR();
void Rename_SCH_LO_GTR_NARR();
void Rename_SCH_LO_LEQ_NARR();
void Rename_SCH_LO_SMR_NARR();
void Rename_SCH_HI_EQL_NARR();
void Rename_SCH_HI_NEQ_NARR();
void Rename_SCH_HI_GEQ_NARR();
void Rename_SCH_HI_GTR_NARR();
void Rename_SCH_HI_LEQ_NARR();
void Rename_SCH_HI_SMR_NARR();
void Rename_SRT_ASC_NARR();
void Rename_SRT_DSC_NARR();
void Rename_REV_NARR();
void Rename_RHT_NARR();
void Rename_LFT_NARR();
