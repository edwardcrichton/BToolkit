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
extern int Rename_UiArrOP1;
extern int Rename_UiArrOP2;


extern char * _Rename_UiArrO_Rename_ARROBJ [];

#define Rename_ARROBJ _Rename_UiArrO_Rename_ARROBJ


#include "Rename_C_UiArr.h"
#include "Rename_M_Byt.h"
#include "Rename_O_BiArr.h"

void INI_Rename_UiArrO(void);
void Rename_UiAO_OBJ_FUL(int *_bb);
void Rename_UiAO_XST(int *_bb,int _pp);
void Rename_UiAO_INI(void);
void Rename_UiAO_CRE(int *_bb,int *_pp);
void Rename_UiAO_VAL(int *_vv,int _pp,int _ii);
void Rename_UiAO_NXT(int *_nn,int _pp);
void Rename_UiAO_EQL(int *_bb,int _ss,int _tt);
void Rename_UiAO_STO(int _pp,int _ii,int _vv);
void Rename_UiAO_STO_NXT(int _pp,int _vv);
void Rename_UiAO_CPY(int _pp,int _qq);
void Rename_UiAO_FILL(int _pp,int _vv);
