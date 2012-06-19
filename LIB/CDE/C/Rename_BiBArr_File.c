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
#include "Rename_BiBArr_File.h"

#include "Rename_B_BiArr_File.h"
#include "Rename_N_Byt_File.h"

#include "Byt_TYPE.h"
#include "Bool_TYPE.h"

void
INI_Rename_BiBArr_File(void)
{
  INI_Rename_B_BiArr_File();
  INI_Rename_N_Byt_File();
  Rename_N_STO(Rename_BiBArr_FileP2);
}

void
Rename_BiBA_IDX(int *_bb,int _idx)
{
  if ( Rename_BiBArr_FileP1 <= _idx && _idx <= Rename_BiBArr_FileP2 ) {
    *_bb = TRUE;
  }
  else {
    *_bb = FALSE;
  }
}

void
Rename_BiBA_VAL(int *_vv,int _idx)
{
  Rename_B_VAL(_vv,_idx);
}

void
Rename_BiBA_STO(int _idx,int _vv)
{
  int nx;
  Rename_B_STO(_idx,_vv);
  BINC(&nx,_idx);
  if ( nx < Rename_BiBArr_FileP2 ) {
    Rename_N_INC();
  }
  else {
    Rename_N_STO(Rename_BiBArr_FileP1);
  }
}

void
Rename_BiBA_EQ(int *_bb,int _idx,int _vv)
{
  Rename_B_EQ(_bb,_idx,_vv);
}

void
Rename_BiBA_IEQ(int *_bb,int _idx,int _idx2)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  Rename_B_EQ(_bb,_idx2,yy);
}

void
Rename_BiBA_NE(int *_bb,int _idx,int _vv)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BNE(_bb,yy,_vv);
}

void
Rename_BiBA_INE(int *_bb,int _idx,int _idx2)
{
  int yy,vv;
  Rename_B_VAL(&yy,_idx);
  Rename_B_VAL(&vv,_idx2);
  BNE(_bb,yy,vv);
}

void
Rename_BiBA_GT(int *_bb,int _idx,int _vv)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BGT(_bb,yy,_vv);
}

void
Rename_BiBA_IGT(int *_bb,int _idx,int _idx2)
{
  int yy,vv;
  Rename_B_VAL(&yy,_idx);
  Rename_B_VAL(&vv,_idx2);
  BGT(_bb,yy,vv);
}

void
Rename_BiBA_GE(int *_bb,int _idx,int _vv)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BGE(_bb,yy,_vv);
}

void
Rename_BiBA_IGE(int *_bb,int _idx,int _idx2)
{
  int yy,vv;
  Rename_B_VAL(&yy,_idx);
  Rename_B_VAL(&vv,_idx2);
  BGE(_bb,yy,vv);
}

void
Rename_BiBA_LT(int *_bb,int _idx,int _vv)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BLT(_bb,yy,_vv);
}

void
Rename_BiBA_ILT(int *_bb,int _idx,int _idx2)
{
  int yy,vv;
  Rename_B_VAL(&yy,_idx);
  Rename_B_VAL(&vv,_idx2);
  BLT(_bb,yy,vv);
}

void
Rename_BiBA_LE(int *_bb,int _idx,int _vv)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BLE(_bb,yy,_vv);
}

void
Rename_BiBA_ILE(int *_bb,int _idx,int _idx2)
{
  int yy,vv;
  Rename_B_VAL(&yy,_idx);
  Rename_B_VAL(&vv,_idx2);
  BLE(_bb,yy,vv);
}

void
Rename_BiBA_ADD(int _idx,int _vv)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BADD(&yy,yy,_vv);
  Rename_B_STO(_idx,yy);
}

void
Rename_BiBA_IADD(int _idx,int _idx2)
{
  int yy,vv;
  Rename_B_VAL(&yy,_idx);
  Rename_B_VAL(&vv,_idx2);
  BADD(&yy,yy,vv);
  Rename_B_STO(_idx,yy);
}

void
Rename_BiBA_SUB(int _idx,int _vv)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BSUB(&yy,yy,_vv);
  Rename_B_STO(_idx,yy);
}

void
Rename_BiBA_ISUB(int _idx,int _idx2)
{
  int yy,vv;
  Rename_B_VAL(&yy,_idx);
  Rename_B_VAL(&vv,_idx2);
  BSUB(&yy,yy,vv);
  Rename_B_STO(_idx,yy);
}

void
Rename_BiBA_INC(int _idx)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BINC(&yy,yy);
  Rename_B_STO(_idx,yy);
}

void
Rename_BiBA_DEC(int _idx)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BDEC(&yy,yy);
  Rename_B_STO(_idx,yy);
}

void
Rename_BiBA_MUL(int _idx,int _vv)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BMUL(&yy,yy,_vv);
  Rename_B_STO(_idx,yy);
}

void
Rename_BiBA_DIV(int _idx,int _vv)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BDIV(&yy,yy,_vv);
  Rename_B_STO(_idx,yy);
}

void
Rename_BiBA_REM(int _idx,int _vv)
{
  int yy;
  Rename_B_VAL(&yy,_idx);
  BMOD(&yy,yy,_vv);
  Rename_B_STO(_idx,yy);
}

void
Rename_BiBA_STO_NXT(int _vv)
{
  int nx;
  Rename_N_VAL(&nx);
  Rename_B_STO(nx,_vv);
  if ( nx < Rename_BiBArr_FileP2 ) {
    Rename_N_INC();
  }
  else {
    Rename_N_STO(Rename_BiBArr_FileP1);
  }
}

void
Rename_BiBA_FILL(int _vv)
{
  int idx;
  idx = Rename_BiBArr_FileP1;
  while ( idx <= Rename_BiBArr_FileP2 ) {
    Rename_B_STO(idx,_vv);
    BINC(&idx,idx);
  };
  Rename_N_STO(Rename_BiBArr_FileP1);
}

void
Rename_BiBA_NXT(int *_nn)
{
  Rename_N_VAL(_nn);
}

