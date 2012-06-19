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
#include "Rename_set.h"

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
Rename_SAV_SET()
{
	write_fm(Rename_scrd,1);
	write_fm(Rename_sset[1],Rename_scrd);
}

void
Rename_SAVN_SET()
{
        int j, k;
	Rename_scrd = htonl ( Rename_scrd );
	write_fm(Rename_scrd,1);
	Rename_scrd = ntohl ( Rename_scrd );

	convert_arr_htonl(Rename_sset,1,Rename_scrd);
	write_fm(Rename_sset[1],Rename_scrd);
	convert_arr_ntohl(Rename_sset,1,Rename_scrd);
}


#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

void
Rename_RST_SET()
{
	read_fm(Rename_scrd,1);
	read_fm(Rename_sset[1],Rename_scrd);
}

void
Rename_RSTN_SET()
{
        int j, k;
	read_fm(Rename_scrd,1);
	Rename_scrd = ntohl ( Rename_scrd );

	read_fm(Rename_sset[1],Rename_scrd);
	convert_arr_ntohl(Rename_sset,1,Rename_scrd);
}


void
#ifdef _BT_ANSIC
Rename_ENT_SET( int vv )
#else
Rename_ENT_SET( vv )
int vv;
#endif
{
	int i,j;
	i = 0;
	j = Rename_scrd;
	while( j!=i ){
		if( Rename_sset[j] == vv ){
			i = j;
		} else{
			j = j-1;
		};
	};
	if( j==0 ){
		Rename_sset[Rename_scrd+1] = vv;
		Rename_scrd = Rename_scrd+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_RMV_SET( int vv )
#else
Rename_RMV_SET( vv )
int vv;
#endif
{
	int i,j;
	i = 0;
	j = Rename_scrd;
	while( j!=i ){
		if( Rename_sset[j] == vv ){
			i = j;
		} else{
			j = j-1;
		};
	};
	if( j!=0 ){
		Rename_sset[j] = Rename_sset[Rename_scrd];
		Rename_scrd = Rename_scrd-1;
	};
}


void
#ifdef _BT_ANSIC
Rename_MBR_SET( int *bb, int vv )
#else
Rename_MBR_SET( bb, vv )
int *bb;
int vv;
#endif
{
	int i,j;
	i = 0;
	j = Rename_scrd;
	while( j!=i ){
		if( Rename_sset[j] == vv ){
			i = j;
		} else{
			j = j-1;
		};
	};
	*bb = ((j != 0)!=0 );
}

