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
#define MinSgn -32768

#define MaxSgn 32767

#define n2ps(nn) nn

#define n2ns(nn) (-nn)

#define ps2n(nn) nn

#define ns2n(nn) (-nn)

/*************** OPERATIONS *****************/

#define INI_Sgn_TYPE() { }

#define SLE(rr,aa,bb) *(rr) = ((aa<=bb)!=0)

#define SGE(rr,aa,bb) *(rr) = ((aa>=bb)!=0)

#define SLT(rr,aa,bb) *(rr) = ((aa< bb)!=0)

#define SGT(rr,aa,bb) *(rr) = ((aa> bb)!=0)

#define SEQ(rr,aa,bb) *(rr) = ((aa==bb)!=0)

#define SNE(rr,aa,bb) *(rr) = ((aa!=bb)!=0)

#define SADD(rr,aa,bb) *(rr) = (aa)+(bb)

#define SSUB(rr,aa,bb) *(rr) = (aa)-(bb)

#define SMUL(rr,aa,bb) *(rr) = (aa)*(bb)

#define SDIV(rr,aa,bb) *(rr) = (aa)/(bb)

#define SMOD(rr,aa,bb) *(rr) = (aa)-( (bb)*( (aa)/(bb) ))

#define SINC(rr,aa) *(rr) = (aa)+1

#define SDEC(rr,aa) *(rr) = (aa)-1
