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
#include "Rename_BiSSeq.h"

#include "Rename_V_BiArr.h"
#include "Rename_L_Byt.h"

#include "Bool_TYPE.h"
#include "Byt_TYPE.h"

void
INI_Rename_BiSSeq()
{
  INI_Rename_V_BiArr();
  INI_Rename_L_Byt();
  Rename_L_STO(0);
}

void
Rename_BiSSeq_LEN(ll)
int *ll;
{
  Rename_L_VAL(ll);
}

void
Rename_BiSSeq_VAL(vv,idx)
int *vv,idx;
{
  Rename_V_VAL(vv,idx);
}

void
Rename_BiSSeq_FILL(vv)
int vv;
{
  int idx;
  idx = 1;
  while( idx<=Rename_BiSSeqP2 ){
    Rename_V_STO(idx,vv);
    BINC(&idx,idx);
  };
  Rename_L_STO(Rename_BiSSeqP2);
}

void
Rename_BiSSeq_CHG(idx,vv)
int idx,vv;
{
  Rename_V_STO(idx,vv);
}

void
Rename_BiSSeq_APP(vv)
int vv;
{
  int ll;
  Rename_L_INC();
  Rename_L_VAL(&ll);
  Rename_V_STO(ll,vv);
}

void
Rename_BiSSeq_KEEP(idx)
int idx;
{
  Rename_L_STO(idx);
}

