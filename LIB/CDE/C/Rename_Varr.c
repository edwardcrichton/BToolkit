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
#include "Rename_Varr.h"

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
Rename_SAV_ARR()
{
	write_fm(Rename_Varray[1],Rename_VarrP2);
}

void
Rename_SAVN_ARR()
{
        int j, k;
	convert_arr_htonl(Rename_Varray,1,Rename_VarrP2);
	write_fm(Rename_Varray[1],Rename_VarrP2);
	convert_arr_ntohl(Rename_Varray,1,Rename_VarrP2);
}


#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

void
Rename_RST_ARR()
{
	read_fm(Rename_Varray[1],Rename_VarrP2);
}

void
Rename_RSTN_ARR()
{
        int j, k;
	read_fm(Rename_Varray[1],Rename_VarrP2);
	convert_arr_ntohl(Rename_Varray,1,Rename_VarrP2);
}


void
#ifdef _BT_ANSIC
Rename_SWP_ARR( int ii, int jj )
#else
Rename_SWP_ARR( ii, jj )
int ii, jj;
#endif
{
	int i;
	i=Rename_Varray[ii];
	Rename_Varray[ii]=Rename_Varray[jj];
	Rename_Varray[jj]=i;
}


void
#ifdef _BT_ANSIC
Rename_SCH_LO_EQL_ARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_LO_EQL_ARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=jj;
	y=kk+1;
	while( y!=r ){
		if( Rename_Varray[r] == vv ){
			y=r;
		} else{
			r=r+1;
		};
	}
	*(bb)=((r!=kk+1)!=0);
	*(ii)=r;
}


void
#ifdef _BT_ANSIC
Rename_SCH_LO_NEQ_ARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_LO_NEQ_ARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=jj;
	y=kk+1;
	while( y!=r ){
		if( Rename_Varray[r] != vv ){
			y=r;
		} else{
			r=r+1;
		};
	}
	*(bb)=((r!=kk+1)!=0);
	*(ii)=r;
}


void
#ifdef _BT_ANSIC
Rename_SCH_HI_EQL_ARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_HI_EQL_ARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=kk;
	y=jj-1;
	while( y!=r ){
		if( Rename_Varray[r] == vv ){
			y=r;
		} else{
			r=r-1;
		};
	}
	*(bb)=((r!=jj-1)!=0);
	*(ii)=r;
}


void
#ifdef _BT_ANSIC
Rename_SCH_HI_NEQ_ARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_HI_NEQ_ARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=kk;
	y=jj-1;
	while( y!=r ){
		if( Rename_Varray[r] != vv ){
			y=r;
		} else{
			r=r-1;
		};
	}
	*(bb)=((r!=jj-1)!=0);
	*(ii)=r;
}


void
#ifdef _BT_ANSIC
Rename_REV_ARR( int ii, int jj )
#else
Rename_REV_ARR( ii, jj )
int ii, jj;
#endif
{
	int i,j;
	i=ii;
	j=jj;
	while( i<j ){
		Rename_SWP_ARR(i,j);
		i=i+1;
		j=j-1;
	};
}


void
#ifdef _BT_ANSIC
Rename_RHT_ARR( int ii, int jj, int nn )
#else
Rename_RHT_ARR( ii, jj, nn )
int ii, jj, nn;
#endif
{
	int k,n;
	n=jj-ii+1;
	k=0;
	while( k<n ){
		if( jj+nn-k<=Rename_VarrP2 ){
			Rename_Varray[jj+nn-k]=Rename_Varray[jj-k];
		}
		k=k+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_LFT_ARR( int ii, int jj, int nn )
#else
Rename_LFT_ARR( ii, jj, nn )
int ii, jj, nn;
#endif
{
	int k,n;
	n=jj-ii+1;
	k=0;
	while( k<n ){
		if( ii-nn+k>=1 ){
			Rename_Varray[ii-nn+k]=Rename_Varray[ii+k];
		}
		k=k+1;
	};
}

