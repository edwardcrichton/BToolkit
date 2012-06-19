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
extern int Rename_BiSeqP1;
extern int Rename_BiSeqP2;


#include "Rename_B_BiRcd.h"
#include "Rename_V_BiRcd.h"
#include "Rename_I_Byt.h"
#include "Rename_T_Byt.h"

void INI_Rename_BiSeq();
void Rename_BiSeq_FULL();
void Rename_BiSeq_IDX();
void Rename_BiSeq_LEN();
void Rename_BiSeq_FRST();
void Rename_BiSeq_LAST();
void Rename_BiSeq_VAL();
void Rename_BiSeq_CLR();
void Rename_BiSeq_FILL();
void Rename_BiSeq_STO();
void Rename_BiSeq_INS();
void Rename_BiSeq_SWP();
void Rename_BiSeq_PUSH();
void Rename_BiSeq_APP();
void Rename_BiSeq_POP();
void Rename_BiSeq_FRONT();
void Rename_BiSeq_DEL();
void Rename_BiSeq_RTN();
void Rename_BiSeq_RMV();
