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
#include "Rename_Vfnc.h"

#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>

extern FILE *dump_file;

#define convert_arr_htonl(a,i,n) \
  j = i; \
  k = 0; \
  while ( k < n ) { \
    a [ j ] = htonl ( a [ j ] ); \
    j++; \
    k++; \
  }

#define convert_arr_ntohl(a,i,n) \
  j = i; \
  k = 0; \
  while ( k < n ) { \
    a [ j ] = ntohl ( a [ j ] ); \
    j++; \
    k++; \
  }

#define  write_fm(a,b)    fwrite(&a,sizeof(int),b,dump_file)

void
Rename_SAV_FNC()
{
	write_fm(Rename_Vfnc[1],Rename_VfncP2);
}

void
Rename_SAVN_FNC()
{
        int j, k;
	convert_arr_htonl(Rename_Vfnc,1,Rename_VfncP2);
	write_fm(Rename_Vfnc[1],Rename_VfncP2);
	convert_arr_ntohl(Rename_Vfnc,1,Rename_VfncP2);
}


#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)


void
Rename_RST_FNC()
{
	read_fm(Rename_Vfnc[1],Rename_VfncP2);
}

void
Rename_RSTN_FNC()
{
        int j, k;
	read_fm(Rename_Vfnc[1],Rename_VfncP2);
	convert_arr_ntohl(Rename_Vfnc,1,Rename_VfncP2);
}


void
INI_Rename_Vfnc()
{
	int i;
	i = 1;
	while( i<= Rename_VfncP2 ){
		Rename_Vfnc[i] = 2147483647;
		i = i+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_FREE_FNC( int *b, int *v )
#else
Rename_FREE_FNC( b, v )
int *b, *v;
#endif
{
	int i;
	i = Rename_VfncP2;
	*b = 0;
	*v = 1;
	while( i>= 0 ){
		if (Rename_Vfnc[i] == 2147483647) {
			*b = 1;
			*v = i;
			i = 0;

			;
		};
		i = i-1;
	};
}
