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
extern int Rename_NseqP2;
extern int Rename_NseqP1;
extern int Rename_Nseq[];
extern int Rename_Nsize;

#define INI_Rename_Nseq()         {Rename_Nsize = 0;}

#define Rename_FUL_NSEQ(bb)        \
{*(bb) = ((Rename_Nsize == Rename_NseqP2)!=0);}

#define Rename_XST_IDX_NSEQ(bb,ii) {*(bb) = (((ii>0) && (ii <= Rename_Nsize))!=0);}
#define Rename_LEN_NSEQ(nn)        {*(nn) = Rename_Nsize;}

#define Rename_CLR_NSEQ()          {Rename_Nsize = 0;}

#define Rename_EMP_NSEQ(bb)        {*(bb) = ((Rename_Nsize == 0)!=0);}

#define Rename_PSH_NSEQ(vv)        \
{Rename_Nseq[Rename_Nsize+1] = vv; Rename_Nsize = Rename_Nsize+1;}

#define Rename_POP_NSEQ()          {Rename_Nsize = Rename_Nsize-1;}
#define Rename_FST_NSEQ(vv)        {*(vv) = Rename_Nseq[1];}
#define Rename_LST_NSEQ(vv)        {*(vv) = Rename_Nseq[Rename_Nsize];}
#define Rename_KEP_NSEQ(ii)        {Rename_Nsize = ii;}
#define Rename_VAL_NSEQ(vv,ii)     {*(vv) = Rename_Nseq[ii];}
#define Rename_STO_NSEQ(ii,vv)     {Rename_Nseq[ii] = vv;}
#define Rename_ADD_NSEQ(ii,vv)     {Rename_Nseq[ii] = Rename_Nseq[ii]+(vv);}
#define Rename_SUB_NSEQ(ii,vv)     {Rename_Nseq[ii] = Rename_Nseq[ii]-(vv);}
#define Rename_MUL_NSEQ(ii,vv)     {Rename_Nseq[ii] = Rename_Nseq[ii]*(vv);}
#define Rename_DIV_NSEQ(ii,vv)     {Rename_Nseq[ii] = Rename_Nseq[ii]/(vv);}

#define Rename_MOD_NSEQ(ii,vv) \
{Rename_Nseq[ii] = Rename_Nseq[ii]-(vv)*(Rename_Nseq[ii]/(vv));}

#define Rename_EQL_NSEQ(bb,ii,vv)  {*(bb) = ((Rename_Nseq[ii]==(vv))!=0);}
#define Rename_NEQ_NSEQ(bb,ii,vv)  {*(bb) = ((Rename_Nseq[ii]!=(vv))!=0);}
#define Rename_GTR_NSEQ(bb,ii,vv)  {*(bb) = ((Rename_Nseq[ii]> (vv))!=0);}
#define Rename_GEQ_NSEQ(bb,ii,vv)  {*(bb) = ((Rename_Nseq[ii]>=(vv))!=0);}
#define Rename_SMR_NSEQ(bb,ii,vv)  {*(bb) = ((Rename_Nseq[ii]< (vv))!=0);}
#define Rename_LEQ_NSEQ(bb,ii,vv)  {*(bb) = ((Rename_Nseq[ii]<=(vv))!=0);}

void Rename_SAV_NSEQ();
void Rename_SAVN_NSEQ();
void Rename_RST_NSEQ();
void Rename_RSTN_NSEQ();
void Rename_TAL_NSEQ();
void Rename_CUT_NSEQ();
void Rename_SWP_NSEQ();
void Rename_MAX_IDX_NSEQ();
void Rename_MIN_IDX_NSEQ();
void Rename_SCH_LO_EQL_NSEQ();
void Rename_SCH_LO_NEQ_NSEQ();
void Rename_SCH_LO_GEQ_NSEQ();
void Rename_SCH_LO_GTR_NSEQ();
void Rename_SCH_LO_LEQ_NSEQ();
void Rename_SCH_LO_SMR_NSEQ();
void Rename_SCH_HI_EQL_NSEQ();
void Rename_SCH_HI_NEQ_NSEQ();
void Rename_SCH_HI_GEQ_NSEQ();
void Rename_SCH_HI_GTR_NSEQ();
void Rename_SCH_HI_LEQ_NSEQ();
void Rename_SCH_HI_SMR_NSEQ();
void Rename_SRT_ASC_NSEQ();
void Rename_SRT_DSC_NSEQ();
void Rename_REV_NSEQ();
void Rename_RHT_NSEQ();
void Rename_LFT_NSEQ();
