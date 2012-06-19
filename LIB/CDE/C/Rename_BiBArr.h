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
extern int Rename_BiBArrP1;
extern int Rename_BiBArrP2;
extern int Rename_BiBArrP3;

#include "Rename_B_BiArr.h"
#include "Rename_N_Byt.h"

void INI_Rename_BiBArr(void);
void Rename_BiBA_IDX(int *_bb,int _idx);
void Rename_BiBA_VAL(int *_vv,int _idx);
void Rename_BiBA_STO(int _idx,int _vv);
void Rename_BiBA_EQ(int *_bb,int _idx,int _vv);
void Rename_BiBA_IEQ(int *_bb,int _idx,int _idx2);
void Rename_BiBA_NE(int *_bb,int _idx,int _vv);
void Rename_BiBA_INE(int *_bb,int _idx,int _idx2);
void Rename_BiBA_GT(int *_bb,int _idx,int _vv);
void Rename_BiBA_IGT(int *_bb,int _idx,int _idx2);
void Rename_BiBA_GE(int *_bb,int _idx,int _vv);
void Rename_BiBA_IGE(int *_bb,int _idx,int _idx2);
void Rename_BiBA_LT(int *_bb,int _idx,int _vv);
void Rename_BiBA_ILT(int *_bb,int _idx,int _idx2);
void Rename_BiBA_LE(int *_bb,int _idx,int _vv);
void Rename_BiBA_ILE(int *_bb,int _idx,int _idx2);
void Rename_BiBA_ADD(int _idx,int _vv);
void Rename_BiBA_IADD(int _idx,int _idx2);
void Rename_BiBA_SUB(int _idx,int _vv);
void Rename_BiBA_ISUB(int _idx,int _idx2);
void Rename_BiBA_INC(int _idx);
void Rename_BiBA_DEC(int _idx);
void Rename_BiBA_MUL(int _idx,int _vv);
void Rename_BiBA_DIV(int _idx,int _vv);
void Rename_BiBA_REM(int _idx,int _vv);
void Rename_BiBA_STO_NXT(int _vv);
void Rename_BiBA_FILL(int _vv);
void Rename_BiBA_NXT(int *_nn);
