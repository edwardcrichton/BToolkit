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
#include "CfgDepBase_seq_obj.h"
#include "CfgDepBase_seq_ctx.h"
#include "basic_io.h"


void
INI_CfgDepBase_seq_obj()
{
	CfgDepBase_ssiz_adr_seq_obj = 0;
	CfgDepBase_ssiz_len_seq_obj = 0;
	CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj+1] = 0;
	CfgDepBase_ssiz_adr_seq_obj = CfgDepBase_ssiz_adr_seq_obj+1;
	CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj+1] = CfgDepBase_seq_objP3;
	CfgDepBase_ssiz_adr_seq_obj = CfgDepBase_ssiz_adr_seq_obj+1;
	CfgDepBase_len_seq_obj[CfgDepBase_ssiz_len_seq_obj+1] = 0;
	CfgDepBase_ssiz_len_seq_obj = CfgDepBase_ssiz_len_seq_obj+1;
	CfgDepBase_tot_seq_obj = CfgDepBase_seq_objP3;
	CfgDepBase_ssiz_old_seq_obj = 0;
}


void
CfgDepBase_INI_SEQ_OBJ()
{
	CfgDepBase_ssiz_adr_seq_obj = 0;
	CfgDepBase_ssiz_len_seq_obj = 0;
	CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj+1] = 0;
	CfgDepBase_ssiz_adr_seq_obj = CfgDepBase_ssiz_adr_seq_obj+1;
	CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj+1] = CfgDepBase_seq_objP3;
	CfgDepBase_ssiz_adr_seq_obj = CfgDepBase_ssiz_adr_seq_obj+1;
	CfgDepBase_len_seq_obj[CfgDepBase_ssiz_len_seq_obj+1] = 0;
	CfgDepBase_ssiz_len_seq_obj = CfgDepBase_ssiz_len_seq_obj+1;
	CfgDepBase_tot_seq_obj = CfgDepBase_seq_objP3;
	CfgDepBase_ssiz_old_seq_obj = 0;
}


void
#ifdef _BT_ANSIC
CfgDepBase_XST_SEQ_OBJ( int *bb, int pp )
#else
CfgDepBase_XST_SEQ_OBJ( bb, pp )
int *bb, pp;
#endif
{
	if ( pp > 0 && pp < CfgDepBase_ssiz_len_seq_obj ) {
		int i;
		i = CfgDepBase_ssiz_old_seq_obj;
		*bb = 1;
		while ( i != 0 ) {
			if ( pp != CfgDepBase_old_seq_obj[i] ) {
				i = i - 1;
			} else {
				i = 0 ;
				*bb = 0;
			}
		}
	} else {
		*bb=0;
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
    a [ j ] = ntohl ( a [ j ] ); \
    j++; \
    k++; \
  }

#define  write_fm(a,b)    fwrite(&a,sizeof(int),b,dump_file)

void
CfgDepBase_SAV_SEQ_OBJ()
{
        CfgDepBase_tot_seq_obj = CfgDepBase_seq_objP3-CfgDepBase_tot_seq_obj;
	write_fm(CfgDepBase_tot_seq_obj,1);
	write_fm(CfgDepBase_ssiz_adr_seq_obj,1);
	write_fm(CfgDepBase_adr_seq_obj[1],CfgDepBase_ssiz_adr_seq_obj);
	write_fm(CfgDepBase_ssiz_len_seq_obj,1);
	write_fm(CfgDepBase_len_seq_obj[1],CfgDepBase_ssiz_len_seq_obj);
	write_fm(CfgDepBase_ssiz_old_seq_obj,1);
	write_fm(CfgDepBase_old_seq_obj[1],CfgDepBase_ssiz_old_seq_obj);
	write_fm(CfgDepBase_array_seq_obj[1],CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj-1]);
        CfgDepBase_tot_seq_obj = CfgDepBase_seq_objP3-CfgDepBase_tot_seq_obj;
}

void
CfgDepBase_SAVN_SEQ_OBJ()
{
        int j, k;
        CfgDepBase_tot_seq_obj = CfgDepBase_seq_objP3-CfgDepBase_tot_seq_obj;

	CfgDepBase_tot_seq_obj = htonl ( CfgDepBase_tot_seq_obj );
        write_fm(CfgDepBase_tot_seq_obj,1);
	CfgDepBase_tot_seq_obj = ntohl ( CfgDepBase_tot_seq_obj );

	CfgDepBase_ssiz_adr_seq_obj = htonl ( CfgDepBase_ssiz_adr_seq_obj );
	write_fm(CfgDepBase_ssiz_adr_seq_obj,1);
	CfgDepBase_ssiz_adr_seq_obj = ntohl ( CfgDepBase_ssiz_adr_seq_obj );

	convert_arr_htonl(CfgDepBase_adr_seq_obj,1,CfgDepBase_ssiz_adr_seq_obj);
        write_fm(CfgDepBase_adr_seq_obj[1],CfgDepBase_ssiz_adr_seq_obj);
	convert_arr_ntohl(CfgDepBase_adr_seq_obj,1,CfgDepBase_ssiz_adr_seq_obj);

	CfgDepBase_ssiz_len_seq_obj = htonl ( CfgDepBase_ssiz_len_seq_obj );
	write_fm(CfgDepBase_ssiz_len_seq_obj,1);
	CfgDepBase_ssiz_len_seq_obj = ntohl ( CfgDepBase_ssiz_len_seq_obj );

	convert_arr_htonl(CfgDepBase_len_seq_obj,1,CfgDepBase_ssiz_len_seq_obj);
	write_fm(CfgDepBase_len_seq_obj[1],CfgDepBase_ssiz_len_seq_obj);
	convert_arr_ntohl(CfgDepBase_len_seq_obj,1,CfgDepBase_ssiz_len_seq_obj);

	CfgDepBase_ssiz_old_seq_obj = htonl ( CfgDepBase_ssiz_old_seq_obj );
	write_fm(CfgDepBase_ssiz_old_seq_obj,1);
	CfgDepBase_ssiz_old_seq_obj = ntohl ( CfgDepBase_ssiz_old_seq_obj );

	convert_arr_htonl(CfgDepBase_old_seq_obj,1,CfgDepBase_ssiz_old_seq_obj);
	write_fm(CfgDepBase_old_seq_obj[1],CfgDepBase_ssiz_old_seq_obj);
	convert_arr_ntohl(CfgDepBase_old_seq_obj,1,CfgDepBase_ssiz_old_seq_obj);

	convert_arr_htonl(CfgDepBase_array_seq_obj,1,CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj-1]);
	write_fm(CfgDepBase_array_seq_obj[1],CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj-1]);
	convert_arr_ntohl(CfgDepBase_array_seq_obj,1,CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj-1]);

        CfgDepBase_tot_seq_obj = CfgDepBase_seq_objP3-CfgDepBase_tot_seq_obj;
}


#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

void
CfgDepBase_RST_SEQ_OBJ()
{
	read_fm(CfgDepBase_tot_seq_obj,1);
	read_fm(CfgDepBase_ssiz_adr_seq_obj,1);
	read_fm(CfgDepBase_adr_seq_obj[1],CfgDepBase_ssiz_adr_seq_obj);
	read_fm(CfgDepBase_ssiz_len_seq_obj,1);
	read_fm(CfgDepBase_len_seq_obj[1],CfgDepBase_ssiz_len_seq_obj);
	read_fm(CfgDepBase_ssiz_old_seq_obj,1);
	read_fm(CfgDepBase_old_seq_obj[1],CfgDepBase_ssiz_old_seq_obj);
	read_fm(CfgDepBase_array_seq_obj[1],
                   CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj-1]);
        CfgDepBase_tot_seq_obj = CfgDepBase_seq_objP3-CfgDepBase_tot_seq_obj;
        CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj] = CfgDepBase_seq_objP3;
}

void
CfgDepBase_RSTN_SEQ_OBJ()
{
        int j, k;
	read_fm(CfgDepBase_tot_seq_obj,1);
        CfgDepBase_tot_seq_obj = ntohl ( CfgDepBase_tot_seq_obj );

	read_fm(CfgDepBase_ssiz_adr_seq_obj,1);
        CfgDepBase_ssiz_adr_seq_obj = ntohl ( CfgDepBase_ssiz_adr_seq_obj );

	read_fm(CfgDepBase_adr_seq_obj[1],CfgDepBase_ssiz_adr_seq_obj);
	convert_arr_ntohl(CfgDepBase_adr_seq_obj,1,CfgDepBase_ssiz_adr_seq_obj);

	read_fm(CfgDepBase_ssiz_len_seq_obj,1);
        CfgDepBase_ssiz_len_seq_obj = ntohl ( CfgDepBase_ssiz_len_seq_obj );

	read_fm(CfgDepBase_len_seq_obj[1],CfgDepBase_ssiz_len_seq_obj);
	convert_arr_ntohl(CfgDepBase_len_seq_obj,1,CfgDepBase_ssiz_len_seq_obj);

	read_fm(CfgDepBase_ssiz_old_seq_obj,1);
        CfgDepBase_ssiz_old_seq_obj = ntohl ( CfgDepBase_ssiz_old_seq_obj );

	read_fm(CfgDepBase_old_seq_obj[1],CfgDepBase_ssiz_old_seq_obj);
	convert_arr_ntohl(CfgDepBase_old_seq_obj,1,CfgDepBase_ssiz_old_seq_obj);

	read_fm(CfgDepBase_array_seq_obj[1],CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj-1]);
	convert_arr_ntohl(CfgDepBase_array_seq_obj,1,CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj-1]);

        CfgDepBase_tot_seq_obj = CfgDepBase_seq_objP3-CfgDepBase_tot_seq_obj;
        CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj] = CfgDepBase_seq_objP3;
}


void
#ifdef _BT_ANSIC
CfgDepBase_CRE_SEQ_OBJ( int *bb, int *pp )
#else
CfgDepBase_CRE_SEQ_OBJ( bb, pp )
int *bb, *pp;
#endif
{
	int b;
	CfgDepBase_OBJ_FUL_SEQ_OBJ(&b);
	if( b==0 ){
		if( CfgDepBase_ssiz_old_seq_obj==0 ){
			CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_len_seq_obj+1] = 
			    CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_len_seq_obj];
			CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj+1] =
                                                             CfgDepBase_seq_objP3;
			CfgDepBase_ssiz_adr_seq_obj = CfgDepBase_ssiz_adr_seq_obj+1;
			CfgDepBase_len_seq_obj[CfgDepBase_ssiz_len_seq_obj+1] = 0;
			CfgDepBase_ssiz_len_seq_obj = CfgDepBase_ssiz_len_seq_obj+1;
			*pp = CfgDepBase_ssiz_len_seq_obj-1;
		} else {
			*pp=CfgDepBase_old_seq_obj[CfgDepBase_ssiz_old_seq_obj];
			CfgDepBase_ssiz_old_seq_obj=CfgDepBase_ssiz_old_seq_obj-1;
		}
		*bb=1;
	} else {
		*pp=0;
		*bb=0;
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_PSH_SEQ_OBJ( int *bb, int ss, int vv )
#else
CfgDepBase_PSH_SEQ_OBJ( bb, ss, vv )
int *bb, ss, vv;
#endif
{
	int e;
	CfgDepBase_MEM_FUL_SEQ_OBJ(&e);
	if( e==0 ){
		int search_res,y,k,r;
		r = 1;
		y = CfgDepBase_ssiz_adr_seq_obj+1;
		search_res = 0;
		while( y!=r ){
			if( CfgDepBase_ssiz_adr_seq_obj>2*ss-1 ){
				if( r<=2*ss-1 ){
					if( (r-1)%2 == 0 ){
						k = ss - (r/2);
					} else {
						k = ss + (r/2);
					}
				} else {
					k = r;
				}
			} else {
				if( r<=2*(CfgDepBase_ssiz_adr_seq_obj-ss) ){
					if( (r-1)%2 == 0 ){
						k =ss - (r/2);
					} else {
						k = ss + (r/2);
					}
				} else {
					k = CfgDepBase_ssiz_adr_seq_obj+1-r;
				}
			}
			if( CfgDepBase_adr_seq_obj[k]+CfgDepBase_len_seq_obj[k]<
                                                     CfgDepBase_adr_seq_obj[k+1] ){
				y = r;
				search_res = k;
			} else {
				r = r+1;
			}
		}
		if( ss<search_res ){
			int j,a,b;
			j = search_res;
			while( j>ss ){
				a = CfgDepBase_adr_seq_obj[j];
				b = CfgDepBase_len_seq_obj[j];
				{
					int k;
					k=a+b;
					while( k>a ){
						CfgDepBase_array_seq_obj[k+1]=
                                                        CfgDepBase_array_seq_obj[k];
						k=k-1;
					}
				}
				CfgDepBase_adr_seq_obj[j] = CfgDepBase_adr_seq_obj[j]+1;
				j = j-1;
			}
		} else {
			int j,a,b;
			j = search_res+1;
			while( j<=ss ){
				a = CfgDepBase_adr_seq_obj[j];
				b = CfgDepBase_len_seq_obj[j];
				{
					int k;
					k=a+1;
					while( k<=a+b ){
						CfgDepBase_array_seq_obj[k-1]=
                                                        CfgDepBase_array_seq_obj[k];
						k=k+1;
					}
				}
				CfgDepBase_adr_seq_obj[j] = CfgDepBase_adr_seq_obj[j]-1;
				j = j+1;
			}
		}
		CfgDepBase_len_seq_obj[ss] = CfgDepBase_len_seq_obj[ss]+1;
		CfgDepBase_tot_seq_obj = CfgDepBase_tot_seq_obj-1;
		CfgDepBase_array_seq_obj[CfgDepBase_len_seq_obj[ss]+CfgDepBase_adr_seq_obj[ss]] = vv;
	}
	*bb=!e;
}

void
#ifdef _BT_ANSIC
CfgDepBase_EQL_SEQ_OBJ( int *bb, int ss, int tt )
#else
CfgDepBase_EQL_SEQ_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int m,n,i,v,w;
	m = CfgDepBase_len_seq_obj[ss];
	n = CfgDepBase_len_seq_obj[tt];
	if( m==n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = CfgDepBase_array_seq_obj[i+CfgDepBase_adr_seq_obj[ss]];
			w = CfgDepBase_array_seq_obj[i+CfgDepBase_adr_seq_obj[tt]];
			if( v!=w ){
				i = m+1;
				*bb = 0;
			} else {
				i = i+1;
			}
		}
	} else {
		*bb = 0;
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_MBR_SEQ_OBJ( int *bb, int *ii, int tt, int vv )
#else
CfgDepBase_MBR_SEQ_OBJ( bb, ii, tt, vv )
int *bb, *ii, tt, vv;
#endif
{
	int n,i,v;
	n = CfgDepBase_len_seq_obj[tt];
	if( n!=0 ){
		i = 1;
		*bb = 0;
		while( i<=n ){
			v = CfgDepBase_array_seq_obj[i+CfgDepBase_adr_seq_obj[tt]];
			if( v==vv ){
				*ii = i;
				i = n+1;
				*bb = 1;
			} else {
				i = i+1;
			}
		}
	} else {
		*bb = 0 ; 
		*ii = 0;
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_APP_SEQ_OBJ( int *bb, int ss, int tt )
#else
CfgDepBase_APP_SEQ_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int k,v,s,b,n;
	b=1;
	k=1;
	s=CfgDepBase_len_seq_obj[tt];
	CfgDepBase_FRE_MEM_SEQ_OBJ(&n);
	if( s<=n ){
		while( k<=s ){
			CfgDepBase_VAL_SEQ_OBJ(&v,tt,k);
			CfgDepBase_PSH_SEQ_OBJ(&b,ss,v);
			k = k+1;
		}
		*bb=1;
	} else {
		*bb=0;
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_CPY_SEQ_OBJ( int *bb, int ss, int tt )
#else
CfgDepBase_CPY_SEQ_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int s,t,n;
	if( ss!=tt ){
		s = CfgDepBase_len_seq_obj[ss];
		t = CfgDepBase_len_seq_obj[tt];
		CfgDepBase_FRE_MEM_SEQ_OBJ(&n);
		if( s<=n+t ){
			CfgDepBase_CLR_SEQ_OBJ(tt);
			CfgDepBase_APP_SEQ_OBJ(&(*bb),tt,ss);
			*bb = 1;
		} else {
			*bb = 0;
		}
	} else {
		*bb = 0;
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_OVR_SEQ_OBJ( int *bb, int ss, int tt )
#else
CfgDepBase_OVR_SEQ_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int s,t,n,i,v,b;
	if( ss!=tt ){
		s = CfgDepBase_len_seq_obj[ss];
		t = CfgDepBase_len_seq_obj[tt];
		CfgDepBase_FRE_MEM_SEQ_OBJ(&n);
		if( t<=n+s ){
			i = 1;
			while( i<=t ){
				CfgDepBase_VAL_SEQ_OBJ(&v,tt,i);
				if( i<=s ){
					CfgDepBase_STO_SEQ_OBJ(ss,i,v);
				} else {
					CfgDepBase_PSH_SEQ_OBJ(&b,ss,v);
				}
				i = i+1;
			}
			*bb = 1;
		} else {
			*bb = 0;
		}
	} else {
		*bb = 1;
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_CUT_SEQ_OBJ( int pp, int ii )
#else
CfgDepBase_CUT_SEQ_OBJ( pp, ii )
int pp, ii;
#endif
{
	int i,l,v;
	i = ii+1;
	CfgDepBase_LEN_SEQ_OBJ(&l,pp);
	while( i<=l ){
		CfgDepBase_VAL_SEQ_OBJ(&v,pp,i);
		CfgDepBase_STO_SEQ_OBJ(pp,i-ii,v);
		i = i+1
		    ;
	}
	CfgDepBase_len_seq_obj[pp] = CfgDepBase_len_seq_obj[pp]-ii;
	CfgDepBase_tot_seq_obj = CfgDepBase_tot_seq_obj+ii;
}


void
#ifdef _BT_ANSIC
CfgDepBase_SWP_SEQ_OBJ( int ss, int ii, int jj )
#else
CfgDepBase_SWP_SEQ_OBJ( ss, ii, jj )
int ss, ii, jj;
#endif
{
	int v,w;
	CfgDepBase_VAL_SEQ_OBJ(&v,ss,ii);
	CfgDepBase_VAL_SEQ_OBJ(&w,ss,jj);
	CfgDepBase_STO_SEQ_OBJ(ss,jj,v);
	CfgDepBase_STO_SEQ_OBJ(ss,ii,w);
}


void
#ifdef _BT_ANSIC
CfgDepBase_REV_SEQ_OBJ( int ss )
#else
CfgDepBase_REV_SEQ_OBJ( ss )
int ss;
#endif
{
	int i,j;
	i=1;
	CfgDepBase_LEN_SEQ_OBJ(&j,ss);
	while( i<j ){
		CfgDepBase_SWP_SEQ_OBJ(ss,i,j);
		i=i+1;
		j=j-1;
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_FIRST_SEQ_OBJ( int *cc, int *ss )
#else
CfgDepBase_FIRST_SEQ_OBJ( cc, ss )
int *cc, *ss;
#endif
{
	int c,i,b;
	c = ( CfgDepBase_ssiz_len_seq_obj - 1 - CfgDepBase_ssiz_old_seq_obj );
	if ( c != 0 ) {
		i = CfgDepBase_ssiz_len_seq_obj - 1;
		CfgDepBase_XST_SEQ_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			CfgDepBase_XST_SEQ_OBJ(&b,i);
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
CfgDepBase_NEXT_SEQ_OBJ( int *cc, int *ss, int oc, int os )
#else
CfgDepBase_NEXT_SEQ_OBJ( cc, ss, oc, os )
int *cc, *ss, oc, os;
#endif
{
	int c,i,b;
	c = oc - 1;
	if ( c != 0 ) {
		i = os - 1;
		CfgDepBase_XST_SEQ_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			CfgDepBase_XST_SEQ_OBJ(&b,i);
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
CfgDepBase_OUTPUT_SEQ_OBJ( char * * SS, int pp )
#else
CfgDepBase_OUTPUT_SEQ_OBJ( SS, pp )
int pp;
char * * SS;
#endif
{
	int e,c,o;
	BLK(2); PUT_STR("[ ");
	CfgDepBase_LEN_SEQ_OBJ(&c,pp);
	o = 1;
	while( o<=c ){
		CfgDepBase_VAL_SEQ_OBJ(&e,pp,o);
		_lib_PUT_ACT_TOK(SS,e);
		BLK(1);
		o++;
	}
	PUT_STR("]");
	NWL(1);
}

void
#ifdef _BT_ANSIC
CfgDepBase_INPUT_SEQ_OBJ( int *bb, char * * SS, int pp, int ll )
#else
CfgDepBase_INPUT_SEQ_OBJ( bb, SS, pp, ll )
int *bb, pp, ll;
char * * SS;
#endif
{
	int m;
	CfgDepBase_FRE_MEM_SEQ_OBJ(&m);
        if ( ll <= m ) {
	        int n[250],b,i;
                _lib_GET_SET_ACT_TOK(ll,n,SS);
                i = 0;
                b = 1;
                while (i<ll && b) {
                        CfgDepBase_PSH_SEQ_OBJ(&b,pp,n[i]);
                        i++;
	        }
                *bb = b;
	}
        else {
                *bb = 0;
	}
}
