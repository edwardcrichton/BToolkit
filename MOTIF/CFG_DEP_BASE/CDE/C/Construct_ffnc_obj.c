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
#include "Construct_ffnc_obj.h"


void
#ifdef _BT_ANSIC
Construct_CRE_FNC_OBJ( int *bb, int *ff )
#else
Construct_CRE_FNC_OBJ( bb, ff )
int *bb, *ff;
#endif
{
	int b,i,f;
	Construct_FUL_FNC_OBJ(&b);
	if( b==0 ){
		if( Construct_sold_fnc_obj==0 ){
			Construct_ssize_fnc_obj = Construct_ssize_fnc_obj+1;
			f=Construct_ssize_fnc_obj;
		} else{
			f=Construct_old_fnc_obj[Construct_sold_fnc_obj];
			Construct_sold_fnc_obj=Construct_sold_fnc_obj-1;
		}
		i = 1;
		while( i<= Construct_ffnc_objP2 ){
			Construct_RMV_FNC_OBJ(f,i);
			i=i+1;
		}
		*ff = f;
		*bb = 1;
	} else{
		*ff = 0;
		*bb = 0;
	}
}


void
#ifdef _BT_ANSIC
Construct_XST_FNC_OBJ( int *bb, int pp )
#else
Construct_XST_FNC_OBJ( bb, pp )
int *bb, pp;
#endif
{
	int i;
	if ( (pp>0) && (pp<=Construct_ssize_fnc_obj) ) {
		i = Construct_sold_fnc_obj;
		*bb = 1;
		while ( i != 0 ) {
			if ( pp != Construct_old_fnc_obj[i] ) {
				i = i - 1;
			} else {
				i = 0 ;
				*bb = 0;
			}
		}
	}  else {
		*bb = 0;
	}
}

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
    a [ j ] = htonl ( a [ j ] ); \
    j++; \
    k++; \
  }

#define  write_fm(a,b)    fwrite(&a,sizeof(int),b,dump_file)


void
Construct_SAV_FNC_OBJ()
{
	write_fm(Construct_ssize_fnc_obj,1);
        write_fm(Construct_ffnc_objP2,1);
	write_fm(Construct_fnc_obj[1],Construct_ssize_fnc_obj*Construct_ffnc_objP2);
	write_fm(Construct_sold_fnc_obj,1);
	write_fm(Construct_old_fnc_obj[1],Construct_ssize_fnc_obj);
}

void
Construct_SAVN_FNC_OBJ()
{
        int j, k;

	Construct_ssize_fnc_obj = htonl ( Construct_ssize_fnc_obj );
        write_fm(Construct_ssize_fnc_obj,1);
	Construct_ssize_fnc_obj = ntohl ( Construct_ssize_fnc_obj );

        Construct_ffnc_objP2 = htonl ( Construct_ffnc_objP2 );
        write_fm(Construct_ffnc_objP2,1);
        Construct_ffnc_objP2 = ntohl ( Construct_ffnc_objP2 );

        convert_arr_htonl(Construct_fnc_obj,1,Construct_ssize_fnc_obj*Construct_ffnc_objP2);
	write_fm(Construct_fnc_obj[1],Construct_ssize_fnc_obj*Construct_ffnc_objP2);
        convert_arr_ntohl(Construct_fnc_obj,1,Construct_ssize_fnc_obj*Construct_ffnc_objP2);

	Construct_sold_fnc_obj = htonl ( Construct_sold_fnc_obj );
        write_fm(Construct_sold_fnc_obj,1);
	Construct_sold_fnc_obj = ntohl ( Construct_sold_fnc_obj );

        convert_arr_htonl(Construct_old_fnc_obj,1,Construct_ssize_fnc_obj);
	write_fm(Construct_old_fnc_obj[1],Construct_ssize_fnc_obj);
        convert_arr_ntohl(Construct_old_fnc_obj,1,Construct_ssize_fnc_obj);
}

#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

void
Construct_RST_FNC_OBJ()
{
	int old_size, i;
	read_fm(Construct_ssize_fnc_obj,1);
	read_fm(old_size,1);
        if ( old_size == Construct_ffnc_objP2 ) {
	  read_fm(Construct_fnc_obj[1],Construct_ssize_fnc_obj*Construct_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= Construct_ssize_fnc_obj*Construct_ffnc_objP2 ) {
	    Construct_fnc_obj[i] = 2147483647;
            i = i+1;
	  }
          i = 1;
          while ( i <= Construct_ssize_fnc_obj ) {
	    read_fm(Construct_fnc_obj[1+(i-1)*Construct_ffnc_objP2], old_size);
            i = i+1;
	  }
	}
	read_fm(Construct_sold_fnc_obj,1);
	read_fm(Construct_old_fnc_obj[1],Construct_ssize_fnc_obj);
}

void
Construct_RSTN_FNC_OBJ()
{
	int old_size, i, j, k;
	read_fm(Construct_ssize_fnc_obj,1);
        Construct_ssize_fnc_obj = ntohl ( Construct_ssize_fnc_obj );

	read_fm(old_size,1);
        old_size = ntohl ( old_size );

        if ( old_size == Construct_ffnc_objP2 ) {
	  read_fm(Construct_fnc_obj[1],Construct_ssize_fnc_obj*Construct_ffnc_objP2);
          convert_arr_ntohl(Construct_fnc_obj,1,Construct_ssize_fnc_obj*Construct_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= Construct_ssize_fnc_obj*Construct_ffnc_objP2 ) {
	    Construct_fnc_obj[i] = 2147483647;
            i = i+1;
	  }
          i = 1;
          while ( i <= Construct_ssize_fnc_obj ) {
	    read_fm(Construct_fnc_obj[1+(i-1)*Construct_ffnc_objP2], old_size);
            convert_arr_ntohl(Construct_fnc_obj,1+(i-1)*Construct_ffnc_objP2,old_size);
            i = i+1;
	  }
	}
	read_fm(Construct_sold_fnc_obj,1);
        Construct_sold_fnc_obj = ntohl ( Construct_sold_fnc_obj );

	read_fm(Construct_old_fnc_obj[1],Construct_ssize_fnc_obj);
        convert_arr_ntohl(Construct_old_fnc_obj,1,Construct_ssize_fnc_obj);
}


void
#ifdef _BT_ANSIC
Construct_FIRST_FNC_OBJ( int *cc, int *ss )
#else
Construct_FIRST_FNC_OBJ( cc, ss )
int *cc, *ss;
#endif
{
	int c,i,b;
	c = ( Construct_ssize_fnc_obj - Construct_sold_fnc_obj );
	if ( c != 0 ) {
		i = Construct_ssize_fnc_obj;
		Construct_XST_FNC_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			Construct_XST_FNC_OBJ(&b,i);
		}
		*ss = i;
		*cc = c;
	} else {
		*ss = 0;
		*cc = 0;
	}
}


void
#ifdef _BT_ANSIC
Construct_NEXT_FNC_OBJ( int *cc, int *ss, int oc, int os )
#else
Construct_NEXT_FNC_OBJ( cc, ss, oc, os )
int *cc, *ss, oc, os;
#endif
{
	int c,i,b;
	c = oc - 1;
	if ( c != 0 ) {
		i = os - 1;
		Construct_XST_FNC_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			Construct_XST_FNC_OBJ(&b,i);
		}
		*ss = i;
		*cc = c;
	} else {
		*ss = 0;
		*cc = 0;
	}

}


void
#ifdef _BT_ANSIC
Construct_OVR_LIT_FFNC_OBJ( int ff, int ii, int ll, int *aa )
#else
Construct_OVR_LIT_FFNC_OBJ( ff, ii, ll, aa )
int ff, ii, ll, *aa;
#endif
{
	size_t i;
	int *s;
	char *t;
	t = (char *)aa;
	i=0;
	while (t[i]!='\0') {
		Construct_buf_ffnc_obj[i]=t[i];
		i=i+1;
	}
	Construct_buf_ffnc_obj[i] = '\0';
	s = (int *)Construct_buf_ffnc_obj;
	i=0;
	while ( i < ll ){
		Construct_STO_FNC_OBJ(ff,(ii+i),s[i]);
		i=i+1;
	}
}


void
#ifdef _BT_ANSIC
Construct_OVR_FFNC_OBJ( int ff, int ii, int ll, int *aa )
#else
Construct_OVR_FFNC_OBJ( ff, ii, ll, aa )
int ff, ii, ll, *aa;
#endif
{
	size_t i;
	i=0;
	while ( i < ll ){
		Construct_STO_FNC_OBJ(ff,(ii+i),aa[i]);
		i=i+1;
	}
}


void
#ifdef _BT_ANSIC
Construct_EQL_FFNC_OBJ( int *bb, int ff, int ii, int ll, int *vv )
#else
Construct_EQL_FFNC_OBJ( bb, ff, ii, ll, vv )
int *bb, ff, ii, ll, *vv;
#endif
{
	size_t i;
	int b;
	char *s,*t,*e;
	s = (char *)vv;
	t = (char *)&(Construct_fnc_obj[(ff-1)*Construct_ffnc_objP2+ii]);
	e = (char *)&(Construct_fnc_obj[(ff-1)*Construct_ffnc_objP2+ii+ll]);
	i=0;
	b = 1;
	while ( s[i]!='\0' && b==1 ) {
		if ( t[i] == s[i] && &(t[i])!=e )
		{
			i = i+1;
		} else{
			b = 0;
		}
	}
        if ( s[i]=='\0' && t[i]!='\0') { *bb = 0; } else{ *bb = b; }
}


void
#ifdef _BT_ANSIC
Construct_MOV_FFNC_OBJ( int ff, int gg, int ii, int jj, int ll )
#else
Construct_MOV_FFNC_OBJ( ff, gg, ii, jj, ll )
int ff, gg, ii, jj, ll;
#endif
{
	int i;
	i=0;
	while ( i < ll ){
		Construct_STO_FNC_OBJ(gg,
                                  (jj+i),
                                  Construct_fnc_obj[(ff-1)*Construct_ffnc_objP2+ii+i]
                                  );
		i=i+1;
	}
}


void
#ifdef _BT_ANSIC
Construct_XTR_FFNC_OBJ( int *vv, int ff, int ii, int ll )
#else
Construct_XTR_FFNC_OBJ( vv, ff, ii, ll )
int ff, ii, ll, *vv;
#endif
{
	size_t i;
	char *s,*t,*e;
	s = (char *)vv;
	t = (char *)&(Construct_fnc_obj[(ff-1)*Construct_ffnc_objP2+ii]);
	e = (char *)&(Construct_fnc_obj[(ff-1)*Construct_ffnc_objP2+ii+ll]);
	i=0;
	while ( &(t[i])!=e) {
		s[i] = t[i];
		i = i + 1;
	}
}
