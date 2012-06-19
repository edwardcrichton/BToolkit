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
extern int Rename_BiRcdP1;
extern int Rename_BiRcdP2;
extern int Rename_BiRcdP3;

extern int Rename_BiRcd_ARR_BiArrP1;
extern int Rename_BiRcd_ARR_BiArrP2;
extern int Rename_BiRcd_ARR_BiArrP3;

extern int Rename_BiRcd_ARR[];

extern int Rename_BiRcd_HEAP_ARR_BiArrP1;
extern int Rename_BiRcd_HEAP_ARR_BiArrP2;
extern int Rename_BiRcd_HEAP_ARR_BiArrP3;

extern int Rename_BiRcd_HEAP_ARR[];

extern int Rename_BiRcd_TOT;

void INI_Rename_BiRcd();
void Rename_BiRcd_RST();
void Rename_BiRcd_IDX();
void Rename_BiRcd_FULL();
void Rename_BiRcd_CRE();
void Rename_BiRcd_KILL();
void Rename_BiRcd_VLD();
void Rename_BiRcd_STO();
void Rename_BiRcd_VAL();
