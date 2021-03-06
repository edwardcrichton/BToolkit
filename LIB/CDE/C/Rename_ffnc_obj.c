/*Copyright (c) 1985-2012, B-Core (UK) Ltd

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "Rename_ffnc_obj.h"


void
#ifdef _BT_ANSIC
Rename_CRE_FNC_OBJ( int *bb, int *ff )
#else
Rename_CRE_FNC_OBJ( bb, ff )
int *bb, *ff;
#endif
{
	int b,i,f;
	Rename_FUL_FNC_OBJ(&b);
	if( b==0 ){
		if( Rename_sold_fnc_obj==0 ){
			Rename_ssize_fnc_obj = Rename_ssize_fnc_obj+1;
			f=Rename_ssize_fnc_obj
			    ;
		} else{
			f=Rename_old_fnc_obj[Rename_sold_fnc_obj];
			Rename_sold_fnc_obj=Rename_sold_fnc_obj-1
			    ;
		};
		i = 1;
		while( i<= Rename_ffnc_objP2 ){
			Rename_RMV_FNC_OBJ(f,i);
			i=i+1
			    ;
		};
		*ff = f;
		*bb = 1;
	} else{
		*ff = 0;
		*bb = 0;
	};
}


void
#ifdef _BT_ANSIC
Rename_XST_FNC_OBJ( int *bb, int pp )
#else
Rename_XST_FNC_OBJ( bb, pp )
int *bb, pp;
#endif
{
	int i;
	if ( (pp>0) && (pp<=Rename_ssize_fnc_obj) ) {
		i = Rename_sold_fnc_obj;
		*bb = 1;
		while ( i != 0 ) {
			if ( pp != Rename_old_fnc_obj[i] ) {
				i = i - 1;
			} else {
				i = 0 ;
				*bb = 0;
			};
		};
	}  else {
		*bb = 0
		    ;
	};
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
Rename_SAV_FNC_OBJ()
{
	write_fm(Rename_ssize_fnc_obj,1);
        write_fm(Rename_ffnc_objP2,1);
	write_fm(Rename_fnc_obj[1],Rename_ssize_fnc_obj*Rename_ffnc_objP2);
	write_fm(Rename_sold_fnc_obj,1);
	write_fm(Rename_old_fnc_obj[1],Rename_ssize_fnc_obj);
}

void
Rename_SAVN_FNC_OBJ()
{
        int j, k;

	Rename_ssize_fnc_obj = htonl ( Rename_ssize_fnc_obj );
        write_fm(Rename_ssize_fnc_obj,1);
	Rename_ssize_fnc_obj = ntohl ( Rename_ssize_fnc_obj );

        Rename_ffnc_objP2 = htonl ( Rename_ffnc_objP2 );
        write_fm(Rename_ffnc_objP2,1);
        Rename_ffnc_objP2 = ntohl ( Rename_ffnc_objP2 );

        convert_arr_htonl(Rename_fnc_obj,1,Rename_ssize_fnc_obj*Rename_ffnc_objP2);
	write_fm(Rename_fnc_obj[1],Rename_ssize_fnc_obj*Rename_ffnc_objP2);
        convert_arr_ntohl(Rename_fnc_obj,1,Rename_ssize_fnc_obj*Rename_ffnc_objP2);

	Rename_sold_fnc_obj = htonl ( Rename_sold_fnc_obj );
        write_fm(Rename_sold_fnc_obj,1);
	Rename_sold_fnc_obj = ntohl ( Rename_sold_fnc_obj );

        convert_arr_htonl(Rename_old_fnc_obj,1,Rename_ssize_fnc_obj);
	write_fm(Rename_old_fnc_obj[1],Rename_ssize_fnc_obj);
        convert_arr_ntohl(Rename_old_fnc_obj,1,Rename_ssize_fnc_obj);
}

#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

void
Rename_RST_FNC_OBJ()
{
	int old_size, i;
	read_fm(Rename_ssize_fnc_obj,1);
	read_fm(old_size,1);
        if ( old_size == Rename_ffnc_objP2 ) {
	  read_fm(Rename_fnc_obj[1],Rename_ssize_fnc_obj*Rename_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= Rename_ssize_fnc_obj*Rename_ffnc_objP2 ) {
	    Rename_fnc_obj[i] = 2147483647;
            i = i+1;
	  };
          i = 1;
          while ( i <= Rename_ssize_fnc_obj ) {
	    read_fm(Rename_fnc_obj[1+(i-1)*Rename_ffnc_objP2], old_size);
            i = i+1;
	  }
	}
	read_fm(Rename_sold_fnc_obj,1);
	read_fm(Rename_old_fnc_obj[1],Rename_ssize_fnc_obj);
}

void
Rename_RSTN_FNC_OBJ()
{
	int old_size, i, j, k;
	read_fm(Rename_ssize_fnc_obj,1);
        Rename_ssize_fnc_obj = ntohl ( Rename_ssize_fnc_obj );

	read_fm(old_size,1);
        old_size = ntohl ( old_size );

        if ( old_size == Rename_ffnc_objP2 ) {
	  read_fm(Rename_fnc_obj[1],Rename_ssize_fnc_obj*Rename_ffnc_objP2);
          convert_arr_ntohl(Rename_fnc_obj,1,Rename_ssize_fnc_obj*Rename_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= Rename_ssize_fnc_obj*Rename_ffnc_objP2 ) {
	    Rename_fnc_obj[i] = 2147483647;
            i = i+1;
	  };
          i = 1;
          while ( i <= Rename_ssize_fnc_obj ) {
	    read_fm(Rename_fnc_obj[1+(i-1)*Rename_ffnc_objP2], old_size);
            convert_arr_ntohl(Rename_fnc_obj,1+(i-1)*Rename_ffnc_objP2,old_size);
            i = i+1;
	  }
	}
	read_fm(Rename_sold_fnc_obj,1);
        Rename_sold_fnc_obj = ntohl ( Rename_sold_fnc_obj );

	read_fm(Rename_old_fnc_obj[1],Rename_ssize_fnc_obj);
        convert_arr_ntohl(Rename_old_fnc_obj,1,Rename_ssize_fnc_obj);
}


void
#ifdef _BT_ANSIC
Rename_FIRST_FNC_OBJ( int *cc, int *ss )
#else
Rename_FIRST_FNC_OBJ( cc, ss )
int *cc, *ss;
#endif
{
	int c,i,b;
	c = ( Rename_ssize_fnc_obj - Rename_sold_fnc_obj );
	if ( c != 0 ) {
		i = Rename_ssize_fnc_obj;
		Rename_XST_FNC_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			Rename_XST_FNC_OBJ(&b,i);
		};
		*ss = i;
		*cc = c;
	} else {
		*ss = 0;
		*cc = 0;
	};
}


void
#ifdef _BT_ANSIC
Rename_NEXT_FNC_OBJ( int *cc, int *ss, int oc, int os )
#else
Rename_NEXT_FNC_OBJ( cc, ss, oc, os )
int *cc, *ss, oc, os;
#endif
{
	int c,i,b;
	c = oc - 1;
	if ( c != 0 ) {
		i = os - 1;
		Rename_XST_FNC_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			Rename_XST_FNC_OBJ(&b,i);
		};
		*ss = i;
		*cc = c;
	} else {
		*ss = 0;
		*cc = 0;
	};

}


void
#ifdef _BT_ANSIC
Rename_OVR_LIT_FFNC_OBJ( int ff, int ii, int ll, int *aa )
#else
Rename_OVR_LIT_FFNC_OBJ( ff, ii, ll, aa )
int ff, ii, ll, *aa;
#endif
{
	int i;
	int *s;
	char *t;
	t = (char *)aa;
	i=0;
	while (t[i]!='\0') {
		Rename_buf_ffnc_obj[i]=t[i];
		i=i+1;
	};
	Rename_buf_ffnc_obj[i] = '\0';
	s = (int *)Rename_buf_ffnc_obj;
	i=0;
	while ( i < ll ){
		Rename_STO_FNC_OBJ(ff,(ii+i),s[i]);
		i=i+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_OVR_FFNC_OBJ( int ff, int ii, int ll, int *aa )
#else
Rename_OVR_FFNC_OBJ( ff, ii, ll, aa )
int ff, ii, ll, *aa;
#endif
{
	int i;
	i=0;
	while ( i < ll ){
		Rename_STO_FNC_OBJ(ff,(ii+i),aa[i]);
		i=i+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_EQL_FFNC_OBJ( int *bb, int ff, int ii, int ll, int *vv )
#else
Rename_EQL_FFNC_OBJ( bb, ff, ii, ll, vv )
int *bb, ff, ii, ll, *vv;
#endif
{
	int i,b;
	char *s,*t,*e;
	s = (char *)vv;
	t = (char *)&(Rename_fnc_obj[(ff-1)*Rename_ffnc_objP2+ii]);
	e = (char *)&(Rename_fnc_obj[(ff-1)*Rename_ffnc_objP2+ii+ll]);
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
Rename_MOV_FFNC_OBJ( int ff, int gg, int ii, int jj, int ll )
#else
Rename_MOV_FFNC_OBJ( ff, gg, ii, jj, ll )
int ff, gg, ii, jj, ll;
#endif
{
	int i;
	i=0;
	while ( i < ll ){
		Rename_STO_FNC_OBJ(gg,
                                  (jj+i),
                                  Rename_fnc_obj[(ff-1)*Rename_ffnc_objP2+ii+i]
                                  );
		i=i+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_XTR_FFNC_OBJ( int *vv, int ff, int ii, int ll )
#else
Rename_XTR_FFNC_OBJ( vv, ff, ii, ll )
int ff, ii, ll, *vv;
#endif
{
	int i;
	char *s,*t,*e;
	s = (char *)vv;
	t = (char *)&(Rename_fnc_obj[(ff-1)*Rename_ffnc_objP2+ii]);
	e = (char *)&(Rename_fnc_obj[(ff-1)*Rename_ffnc_objP2+ii+ll]);
	i=0;
	while ( &(t[i])!=e) {
		s[i] = t[i];
		i = i + 1;
	};
}
