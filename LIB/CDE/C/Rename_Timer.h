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
#include <sys/types.h>
#include <time.h>

extern time_t Rename_sto;
extern time_t Rename_exp;


#define INI_Rename_Timer()      { Rename_exp = 0; Rename_sto = 0; }

#define Rename_GetCurTime(t)    { * t = time ( NULL ); }

#define Rename_StoTime(t)       { Rename_sto = t; }

#define Rename_GetStoTime(t)    { * t = Rename_sto; }

#define Rename_StartTimer(e,i)  { Rename_exp = time ( NULL ) + i; * e = Rename_exp; }

#define Rename_CheckTimer(e)    { * e = ( ( Rename_exp <= time ( NULL ) ) != 0 ); }

#define Rename_GetCurYearMonthDay(n) \
{ \
  struct tm* tm_struct; \
  time_t t = time ( NULL ); \
  tm_struct = localtime ( & t ); \
  * n = ( ( tm_struct -> tm_year + 1900 ) * 10000 ) + \
        ( ( tm_struct -> tm_mon  +    1 ) * 100   ) + \
        ( ( tm_struct -> tm_mday        )         ); \
}

void Rename_IncYearMonthDay();
