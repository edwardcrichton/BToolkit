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
#define n2bs(n) (n)

#define bs2n(n) (n)

#define _BS_WORD_MASK(L,H)  (((~0)<<(L)) & ~((~0)<<((H)+1)))

/*************** OPERATIONS *****************/

#define INI_BitSeq_TYPE()    {}

#define BSAND(r,a,b)         { *r = (a) & (b); }

#define BSOR(r,a,b)          { *r = (a) | (b); }

#define BSXOR(r,a,b)         { *r = (a) ^ (b); }

#define BSNOT(r,a)           { *r = ~(a); }

#define BSXTR(r,a,i)         { *r = ((a) & (1<<(i))) >> (i); }

#define BSSET(r,a,i,v)  \
  { *r = ( (v) ? ((a) | (1<<(i))) : (((a) | (1<<(i))) ^ (1<<(i))) ); }
   
#define BFBS( r, a, i, j ) \
  { *r = ((a)>>(i)) & _BS_WORD_MASK(0,(j)-(i)); }

#define BIBS( r, a, b, i, j ) \
  { *r = ((a)&~(_BS_WORD_MASK((i),(j))) | ((b)<<(i)&_BS_WORD_MASK((i),(j)))); }

void BSGET();
void BSPUT();
