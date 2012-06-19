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
#include <time.h>
#define INI_Int_TYPE_Ops()  {srand((int)time((time_t*)0));}
#define MINI(u,v,w) {if( v<=w ){ *(u) = v ;}else{ *(u) = w ;};}
#define MAXI(u,v,w) {if( v>=w ){ *(u) = v ;}else{ *(u) = w ;};}
#define INCI(u,v)    {*(u) = (v)+1;}
#define DECI(u,v)    {*(u) = (v)-1;}
#define ADDI(u,v,w) {*(u) = (v)+(w);}
#define SUBI(u,v,w) {*(u) = (v)-(w);}
#define MULI(u,v,w) {*(u) = (v)*(w);}
#define DIVI(u,v,w) {*(u) = (v)/(w);}
#define MODI(u,v,w) {*(u) = (v)-( (w)*( (v)/(w) ));}
#define EQLI(b,v,w) {*(b) = ((v==w)!=0);}
#define NEQI(b,v,w) {*(b) = ((v!=w)!=0);}
#define GTRI(b,v,w) {*(b) = ((v> w)!=0);}
#define GEQI(b,v,w) {*(b) = ((v>=w)!=0);}
#define SMRI(b,v,w) {*(b) = ((v< w)!=0);}
#define LEQI(b,v,w) {*(b) = ((v<=w)!=0);}
#define EQZI(b,v) {*(b) = ((v==0)!=0);}
