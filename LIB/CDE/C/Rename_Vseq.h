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
extern int Rename_VseqP2;
extern int Rename_Vseq[];
extern int Rename_Vsize;

#define INI_Rename_Vseq()         {Rename_Vsize = 0;}

#define Rename_FUL_SEQ(bb)        \
{*(bb) = ((Rename_Vsize == Rename_VseqP2)!=0);}

#define Rename_XST_IDX_SEQ(bb,ii) {*(bb) = (((ii>0) && (ii <= Rename_Vsize))!=0);}
#define Rename_LEN_SEQ(nn)        {*(nn) = Rename_Vsize;}

#define Rename_CLR_SEQ()          {Rename_Vsize = 0;}

#define Rename_EMP_SEQ(bb)        {*(bb) = ((Rename_Vsize == 0)!=0);}

#define Rename_PSH_SEQ(vv)        \
{Rename_Vseq[Rename_Vsize+1] = vv; Rename_Vsize = Rename_Vsize+1;}

#define Rename_POP_SEQ()          {Rename_Vsize = Rename_Vsize-1;}
#define Rename_FST_SEQ(vv)        {*(vv) = Rename_Vseq[1];}
#define Rename_LST_SEQ(vv)        {*(vv) = Rename_Vseq[Rename_Vsize];}
#define Rename_KEP_SEQ(ii)        {Rename_Vsize = ii;}
#define Rename_VAL_SEQ(vv,ii)     {*(vv) = Rename_Vseq[ii];}
#define Rename_STO_SEQ(ii,vv)     {Rename_Vseq[ii] = vv;}

#define Rename_EQL_SEQ(bb,ii,vv)  {*(bb) = ((Rename_Vseq[ii]==vv)!=0);}
#define Rename_NEQ_SEQ(bb,ii,vv)  {*(bb) = ((Rename_Vseq[ii]!=vv)!=0);}

void Rename_SAV_SEQ();
void Rename_SAVN_SEQ();
void Rename_RST_SEQ();
void Rename_RSTN_SEQ();
void Rename_TAL_SEQ();
void Rename_CUT_SEQ();
void Rename_SWP_SEQ();
void Rename_SCH_LO_EQL_SEQ();
void Rename_SCH_LO_NEQ_SEQ();
void Rename_SCH_HI_EQL_SEQ();
void Rename_SCH_HI_NEQ_SEQ();
void Rename_REV_SEQ();
void Rename_RHT_SEQ();
void Rename_LFT_SEQ();
