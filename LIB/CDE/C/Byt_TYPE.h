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
#define BYTE _Byt_TYPE_BYTE

extern char * _Byt_TYPE_BYTE [];


/*************** CONSTANTS *****************/ 

#define MinByt         0

#define MaxByt         255

#define n2b(n)         (n)

#define b2n(n)         (n)

#define b2bs(n)        (n)

#define bs2b(n)        (n)

#define b2bl(b)        (((b)==0)==0)

#define bl2b(n)        (n)

/*************** OPERATIONS *****************/

#define INI_Byt_TYPE() { }

#define BLE(r,a,b)     *(r) = ((a<=b)!=0)

#define BGE(r,a,b)     *(r) = ((a>=b)!=0)

#define BLT(r,a,b)     *(r) = ((a< b)!=0)

#define BGT(r,a,b)     *(r) = ((a> b)!=0)

#define BEQ(r,a,b)     *(r) = ((a==b)!=0)

#define BNE(r,a,b)     *(r) = ((a!=b)!=0)

#define BADD(r,a,b)    *(r) = (a)+(b)

#define BSUB(r,a,b)    *(r) = (a)-(b)

#define BMUL(r,a,b)    *(r) = (a)*(b)

#define BDIV(r,a,b)    *(r) = (a)/(b)

#define BMOD(r,a,b)    *(r) = (a)-( (b)*( (a)/(b) ))

#define BINC(r,a)      *(r) = (a)+1

#define BDEC(r,a)      *(r) = (a)-1

#define BLEFT(r,a)     *(r) = (a)*2

#define BRIGHT(r,a)    *(r) = (a)/2
