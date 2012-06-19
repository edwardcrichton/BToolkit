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
#include "Char_TYPE.h"
#include "Char_TYPE_Ops.h"

void
#ifdef _BT_ANSIC
CPY_STR( int *tt, int *ff )
#else
CPY_STR( tt, ff )
int *ff, *tt;
#endif
{
	int i;
	char *f,*t;
	f = (char *)ff;
	t = (char *)tt;
	i=0;
	while ( f[i]!='\0' )  {
		t[i] = f[i];
		i = i+1;
	};
	t[i] = '\0';
}

void
#ifdef _BT_ANSIC
CNC_STR( int *tt, int *ff, int *gg )
#else
CNC_STR( tt, ff, gg )
int *ff, *tt, *gg;
#endif
{
	int i, j;
	char *f,*g,*t;
	f = (char *)ff;
	g = (char *)gg;
	t = (char *)tt;
	i=0;
	while ( f[i]!='\0' )  {
		t[i] = f[i];
		i++;
	};
        j = 0;
	while ( g[j]!='\0' )  {
		t[i] = g[j];
		j++;
		i++;
	};
	t[i] = '\0';
}
