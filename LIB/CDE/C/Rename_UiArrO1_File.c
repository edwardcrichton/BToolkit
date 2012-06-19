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
#include "Rename_UiArrO1.h"

#include "Rename_O1_UiArr.h"
#include "Rename_N1_Uns.h"

#include "Bool_TYPE.h"
#include "PASP_TYPE.h"

void
INI_Rename_UiArrO1(void)
{
  INI_Rename_O1_UiArr();
  INI_Rename_N1_Uns();
  {
    int ii;
    ii = 0;
    while ( ii < Rename_UiArrO1P1 ) {
      UINC(&ii,ii);
      Rename_O1_STO(ii,Rename_UiArrO1P2);
    };
    Rename_N1_STO(1);
  }
}

void
Rename_UiAO1_RST(void)
{
  Rename_N1_STO(1);
}

void
Rename_UiAO1_VAL(int *_vv,int _ii)
{
  Rename_O1_VAL(_vv,_ii);
}

void
Rename_UiAO1_NXT(int *_nn)
{
  Rename_N1_VAL(_nn);
}

void
Rename_UiAO1_STO(int _ii,int _vv)
{
  int jj;
  Rename_O1_STO(_ii,_vv);
  if ( _ii < Rename_UiArrO1P1 ) {
    UINC(&jj,_ii);
    Rename_N1_STO(jj);
  }
  else {
    Rename_N1_STO(1);
  }
}

void
Rename_UiAO1_STO_NXT(int _vv)
{
  int ii;
  Rename_N1_VAL(&ii);
  Rename_O1_STO(ii,_vv);
  if ( ii < Rename_UiArrO1P1 ) {
    Rename_N1_INC();
  }
  else {
    Rename_N1_STO(1);
  }
}

void
Rename_UiAO1_FILL(int _vv)
{
  int ii;
  ii = 0;
  while ( ii < Rename_UiArrO1P1 ) {
    UINC(&ii,ii);
    Rename_O1_STO(ii,_vv);
  };
  Rename_N1_STO(1);
}

