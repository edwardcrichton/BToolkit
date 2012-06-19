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
#include <strings.h>
#include "String_TYPE.h"

#define INI_String_TYPE_Ops() {} 

#define ASSIGN_ANY_STR(r) { r[0] = (char)'\0' ;}

#define LEN_STR(n,s) { *(n) = strlen((char *)s) ;}

#define VAL_ITH_CHAR(c,s,i) { *(c) = ((char *)s)[i-1] ;}

#define CHAR_TO_NAT(i,c) { *(i) = (long)c ;}

#define NAT_TO_STR(s,n) { sprintf((char *)s,"%d",n); }

#define CMP_STR(b,r,s) { *(b) = ( strcasecmp((char *)r,(char *)s) == 0 ) ;}

#define SMR_STR(b,r,s) { *(b) = ( strcasecmp((char *)r,(char *)s) < 0 ) ;}

void CPY_STR ();
void CNC_STR ();
void PFX_STR ();
void PSX_STR ();
void SUB_STR ();
