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
#include "Rename_Vffnc.h"

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
	write_fm(Rename_Vfnc[1],Rename_VffncP2);
}

void
Rename_SAVN_FNC()
{
        int j, k;
	convert_arr_htonl(Rename_Vfnc,1,Rename_VffncP2);
	write_fm(Rename_Vfnc[1],Rename_VffncP2);
	convert_arr_ntohl(Rename_Vfnc,1,Rename_VffncP2);
}


#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

void
Rename_RST_FNC()
{
	read_fm(Rename_Vfnc[1],Rename_VffncP2);
}

void
Rename_RSTN_FNC()
{
        int j, k;
	read_fm(Rename_Vfnc[1],Rename_VffncP2);
	convert_arr_ntohl(Rename_Vfnc,1,Rename_VffncP2);
}

void
INI_Rename_Vffnc()
{
	int i;
	i = 1;
	while( i<= Rename_VffncP2 ){
		Rename_Vfnc[i] = 2147483647;
		i = i+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_FREE_FNC( int *bb, int *vv)
#else
Rename_FREE_FNC( bb, vv )
int *bb, *vv;
#endif
{
	int i;
	i = Rename_VffncP2;
	*bb = 0;
	*vv = 1;
	while( i>= 0 ){
		if (Rename_Vfnc[i] == 2147483647) {
			*bb = 1;
			*vv = i;
			i = 0;
		};
		i = i-1;
	};
}


void
#ifdef _BT_ANSIC
Rename_MOV_FFNC( int ii, int jj, int ll )
#else
Rename_MOV_FFNC( ii, jj, ll )
int ii, jj, ll;
#endif
{
	int i;
	i=0;
	while ( i < ll ){
		Rename_Vfnc[jj+i] = Rename_Vfnc[ii+i];
		i=i+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_OVR_LIT_FFNC( int ii, int ll, int *aa )
#else
Rename_OVR_LIT_FFNC( ii, ll, aa )
int ii, ll, *aa;
#endif
{
	int i;
	int *s;
	char *t;
	t = (char *)aa;
	i=0;
	while (t[i]!='\0') {
		Rename_ffnc_buf[i]=t[i];
		i=i+1;
	};
	Rename_ffnc_buf[i] = '\0';
	s = (int *)Rename_ffnc_buf;
	i=0;
	while ( i < ll ){ 
		Rename_Vfnc[ii+i] = s[i]; 
		i=i+1; 
	};
}


void
#ifdef _BT_ANSIC
Rename_OVR_FFNC( int ii, int ll, int *aa )
#else
Rename_OVR_FFNC( ii, ll, aa )
int ii, ll, *aa;
#endif
{
	int i;
	i=0;
	while ( i < ll ){ 
		Rename_Vfnc[ii+i] = aa[i]; 
		i=i+1; 
	};
}


void
#ifdef _BT_ANSIC
Rename_EQL_FFNC( int *bb, int ii, int ll, int *vv )
#else
Rename_EQL_FFNC( bb, ii, ll, vv )
int *bb, ii, ll, *vv;
#endif
{
	int i,b;
	char *s,*t,*e;
	s = (char *)vv;
	t = (char *)&(Rename_Vfnc[ii]);
	e = (char *)&(Rename_Vfnc[ii+ll]);
	i=0;
	b = 1;
	while ( s[i]!='\0' && b==1 ) {
		if ( t[i] == s[i] && &(t[i])!=e )
		{
			i = i+1
			    ;
		} else{
			b = 0
			    ;
		};
		
	};
        if ( s[i]=='\0' && t[i]!='\0') { *bb = 0; }else{ *bb = b; };
}


void
#ifdef _BT_ANSIC
Rename_XTR_FFNC( int *vv, int ii, int ll )
#else
Rename_XTR_FFNC( vv, ii, ll )
int ii ,ll, *vv;
#endif
{
	int i;
	char *s,*t,*e;
	s = (char *)vv;
	t = (char *)&(Rename_Vfnc[ii]);
	e = (char *)&(Rename_Vfnc[ii+ll]);
	i=0;
	while ( &(t[i])!=e ) {
		s[i] = t[i];
		i = i+1;
	};
}
