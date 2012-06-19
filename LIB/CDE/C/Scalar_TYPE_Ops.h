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
#include <stdlib.h>
#include <time.h>
#define INI_Scalar_TYPE_Ops()  {srand((int)time((time_t*)0));}
#define SCL(u,v)    {*(u) = v;}
#define MIN(u,v,w) {if( v<=w ){ *(u) = v ;}else{ *(u) = w ;};}
#define MAX(u,v,w) {if( v>=w ){ *(u) = v ;}else{ *(u) = w ;};}
#define INC(u,v)    {*(u) = (v)+1;}
#define DEC(u,v)    {*(u) = (v)-1;}
#define ADD(u,v,w) {*(u) = (v)+(w);}
#define SUB(u,v,w) {*(u) = (v)-(w);}
#define MUL(u,v,w) {*(u) = (v)*(w);}
#define DIV(u,v,w) {*(u) = (v)/(w);}
#define MOD(u,v,w) {*(u) = (v)-( (w)*( (v)/(w) ));}
#define EQL(b,v,w) {*(b) = ((v==w)!=0);}
#define NEQ(b,v,w) {*(b) = ((v!=w)!=0);}
#define GTR(b,v,w) {*(b) = ((v> w)!=0);}
#define GEQ(b,v,w) {*(b) = ((v>=w)!=0);}
#define SMR(b,v,w) {*(b) = ((v< w)!=0);}
#define LEQ(b,v,w) {*(b) = ((v<=w)!=0);}
#define EQZ(b,v) {*(b) = ((v==0)!=0);}
#define RND(r,m) {*(r) = rand()%(m+1);}

void Scalar_TYPE_Ops_dummy___ ();
