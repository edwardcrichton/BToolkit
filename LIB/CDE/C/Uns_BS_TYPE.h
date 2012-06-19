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
#define UNSIGNED _Uns_TYPE_UNSIGNED

extern char * _Uns_TYPE_UNSIGNED [];


/*************** CONSTANTS *****************/ 

#define MinUns  0

#define MaxUns  65535

#define n2u(n)  (n)

#define u2n(n)  (n)

#define u2bs(n) (n)

#define bs2u(n) (n)

/*************** OPERATIONS *****************/

#define INI_Uns_BS_TYPE() { }

#define ULE(r,a,b)        *(r) = ((a<=b)!=0)

#define UGE(r,a,b)        *(r) = ((a>=b)!=0)

#define ULT(r,a,b)        *(r) = ((a< b)!=0)

#define UGT(r,a,b)        *(r) = ((a> b)!=0)

#define UEQ(r,a,b)        *(r) = ((a==b)!=0)

#define UNE(r,a,b)        *(r) = ((a!=b)!=0)

#define UADD(r,a,b)       *(r) = (a)+(b)

#define USUB(r,a,b)       *(r) = (a)-(b)

#define UMUL(r,a,b)       *(r) = (a)*(b)

#define UDIV(r,a,b)       *(r) = (a)/(b)

#define UMOD(r,a,b)       *(r) = (a)-( (b)*( (a)/(b) ))

#define UINC(r,a)         *(r) = (a)+1

#define UDEC(r,a)         *(r) = (a)-1

#define UAND(r,a,b)       *(r) = (a)&(b)

#define UOR(r,a,b)        *(r) = (a)|(b)

#define UXOR(r,a,b)       *(r) = (a)^(b)

#define UNOT(r,a)         *(r) = ~(a)
