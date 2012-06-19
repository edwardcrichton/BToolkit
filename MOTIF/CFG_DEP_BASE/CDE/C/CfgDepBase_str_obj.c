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
#include "CfgDepBase_str_obj.h"
#include "basic_io.h"

void
INI_CfgDepBase_str_obj()
{
	CfgDepBase_ssiz_adr_str_obj = 0;
	CfgDepBase_ssiz_len_str_obj = 0;
	CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj+1] = 0;
	CfgDepBase_ssiz_adr_str_obj = CfgDepBase_ssiz_adr_str_obj+1;
	CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj+1] = CfgDepBase_str_objP2;
	CfgDepBase_ssiz_adr_str_obj = CfgDepBase_ssiz_adr_str_obj+1;
	CfgDepBase_len_str_obj[CfgDepBase_ssiz_len_str_obj+1] = 0;
	CfgDepBase_ssiz_len_str_obj = CfgDepBase_ssiz_len_str_obj+1;
	CfgDepBase_tot_str_obj = CfgDepBase_str_objP2;
	CfgDepBase_ssiz_old_str_obj = 0;
}


void
CfgDepBase_INI_STR_OBJ()
{
	CfgDepBase_ssiz_adr_str_obj = 0;
	CfgDepBase_ssiz_len_str_obj = 0;
	CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj+1] = 0;
	CfgDepBase_ssiz_adr_str_obj = CfgDepBase_ssiz_adr_str_obj+1;
	CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj+1] = CfgDepBase_str_objP2;
	CfgDepBase_ssiz_adr_str_obj = CfgDepBase_ssiz_adr_str_obj+1;
	CfgDepBase_len_str_obj[CfgDepBase_ssiz_len_str_obj+1] = 0;
	CfgDepBase_ssiz_len_str_obj = CfgDepBase_ssiz_len_str_obj+1;
	CfgDepBase_tot_str_obj = CfgDepBase_str_objP2;
	CfgDepBase_ssiz_old_str_obj = 0;
}


void
#ifdef _BT_ANSIC
CfgDepBase_XST_STR_OBJ( int *bb, int pp )
#else
CfgDepBase_XST_STR_OBJ( bb, pp )
int *bb, pp;
#endif
{
	if ( pp > 0 && pp < CfgDepBase_ssiz_len_str_obj ) {
		int i;
		i = CfgDepBase_ssiz_old_str_obj;
		*bb = 1;
		while ( i != 0 ) {
			if ( pp != CfgDepBase_old_str_obj[i] ) {
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

#define  write_fmc(a,b)    fwrite(&a,sizeof(char),b,dump_file)

void
CfgDepBase_SAV_STR_OBJ()
{
	int i;
	char c;
        CfgDepBase_tot_str_obj = CfgDepBase_str_objP2-CfgDepBase_tot_str_obj;
	write_fm(CfgDepBase_tot_str_obj,1);
	write_fm(CfgDepBase_ssiz_adr_str_obj,1);
	write_fm(CfgDepBase_adr_str_obj[1],CfgDepBase_ssiz_adr_str_obj);
	write_fm(CfgDepBase_ssiz_len_str_obj,1);
	write_fm(CfgDepBase_len_str_obj[1],CfgDepBase_ssiz_len_str_obj);
	write_fm(CfgDepBase_ssiz_old_str_obj,1);
	write_fm(CfgDepBase_old_str_obj[1],CfgDepBase_ssiz_old_str_obj);
	write_fmc(CfgDepBase_array_str_obj[1],CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1]);
	i = CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1] % 4;
	c = 'w';
	while( i!=0 ){
		write_fmc(c,1);
		i = i-1;
	}
        CfgDepBase_tot_str_obj = CfgDepBase_str_objP2-CfgDepBase_tot_str_obj;
}

void
CfgDepBase_SAVN_STR_OBJ()
{
	int i, j, k;
	char c;
        CfgDepBase_tot_str_obj = CfgDepBase_str_objP2-CfgDepBase_tot_str_obj;

	CfgDepBase_tot_str_obj = htonl ( CfgDepBase_tot_str_obj );
        write_fm(CfgDepBase_tot_str_obj,1);
	CfgDepBase_tot_str_obj = ntohl ( CfgDepBase_tot_str_obj );

	CfgDepBase_ssiz_adr_str_obj = htonl ( CfgDepBase_ssiz_adr_str_obj );
	write_fm(CfgDepBase_ssiz_adr_str_obj,1);
	CfgDepBase_ssiz_adr_str_obj = ntohl ( CfgDepBase_ssiz_adr_str_obj );

	convert_arr_htonl(CfgDepBase_adr_str_obj,1,CfgDepBase_ssiz_adr_str_obj);
	write_fm(CfgDepBase_adr_str_obj[1],CfgDepBase_ssiz_adr_str_obj);
	convert_arr_ntohl(CfgDepBase_adr_str_obj,1,CfgDepBase_ssiz_adr_str_obj);

	CfgDepBase_ssiz_len_str_obj = htonl ( CfgDepBase_ssiz_len_str_obj );
	write_fm(CfgDepBase_ssiz_len_str_obj,1);
	CfgDepBase_ssiz_len_str_obj = ntohl ( CfgDepBase_ssiz_len_str_obj );

	convert_arr_htonl(CfgDepBase_len_str_obj,1,CfgDepBase_ssiz_len_str_obj);
	write_fm(CfgDepBase_len_str_obj[1],CfgDepBase_ssiz_len_str_obj);
	convert_arr_ntohl(CfgDepBase_len_str_obj,1,CfgDepBase_ssiz_len_str_obj);

	CfgDepBase_ssiz_old_str_obj = htonl ( CfgDepBase_ssiz_old_str_obj );
	write_fm(CfgDepBase_ssiz_old_str_obj,1);
	CfgDepBase_ssiz_old_str_obj = ntohl ( CfgDepBase_ssiz_old_str_obj );

	convert_arr_htonl(CfgDepBase_old_str_obj,1,CfgDepBase_ssiz_old_str_obj);
	write_fm(CfgDepBase_old_str_obj[1],CfgDepBase_ssiz_old_str_obj);
	convert_arr_ntohl(CfgDepBase_old_str_obj,1,CfgDepBase_ssiz_old_str_obj);

	write_fmc(CfgDepBase_array_str_obj[1],CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1]);
	/* padding ? */
	i = CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1] % 4;
	c = 'w';
	while( i!=0 ){
		write_fmc(c,1);
		i = i-1;
	}

        CfgDepBase_tot_str_obj = CfgDepBase_str_objP2-CfgDepBase_tot_str_obj;
}


#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

#define  read_fmc(a,b)   fread(&a,sizeof(char),b,dump_file)

void
CfgDepBase_RST_STR_OBJ()
{
	int i;
	char c;
	read_fm(CfgDepBase_tot_str_obj,1);
	read_fm(CfgDepBase_ssiz_adr_str_obj,1);
	read_fm(CfgDepBase_adr_str_obj[1],CfgDepBase_ssiz_adr_str_obj);
	read_fm(CfgDepBase_ssiz_len_str_obj,1);
	read_fm(CfgDepBase_len_str_obj[1],CfgDepBase_ssiz_len_str_obj);
	read_fm(CfgDepBase_ssiz_old_str_obj,1);
	read_fm(CfgDepBase_old_str_obj[1],CfgDepBase_ssiz_old_str_obj);
	read_fmc(CfgDepBase_array_str_obj[1],CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1]);
	i = CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1] % 4;
	while( i!=0 ){
		read_fmc(c,1);
		i = i-1;
	}
        CfgDepBase_tot_str_obj = CfgDepBase_str_objP2-CfgDepBase_tot_str_obj;
        CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj] = CfgDepBase_str_objP2;
}

void
CfgDepBase_RSTN_STR_OBJ()
{
	int i, j, k;
	char c;
	read_fm(CfgDepBase_tot_str_obj,1);
	CfgDepBase_tot_str_obj = ntohl ( CfgDepBase_tot_str_obj );

	read_fm(CfgDepBase_ssiz_adr_str_obj,1);
	CfgDepBase_ssiz_adr_str_obj = ntohl ( CfgDepBase_ssiz_adr_str_obj );

	read_fm(CfgDepBase_adr_str_obj[1],CfgDepBase_ssiz_adr_str_obj);
	convert_arr_ntohl(CfgDepBase_adr_str_obj,1,CfgDepBase_ssiz_adr_str_obj);

	read_fm(CfgDepBase_ssiz_len_str_obj,1);
	CfgDepBase_ssiz_len_str_obj = ntohl ( CfgDepBase_ssiz_len_str_obj );

	read_fm(CfgDepBase_len_str_obj[1],CfgDepBase_ssiz_len_str_obj);
	convert_arr_ntohl(CfgDepBase_len_str_obj,1,CfgDepBase_ssiz_len_str_obj);

	read_fm(CfgDepBase_ssiz_old_str_obj,1);
	CfgDepBase_ssiz_old_str_obj = ntohl ( CfgDepBase_ssiz_old_str_obj );

	read_fm(CfgDepBase_old_str_obj[1],CfgDepBase_ssiz_old_str_obj);
	convert_arr_ntohl(CfgDepBase_old_str_obj,1,CfgDepBase_ssiz_old_str_obj);

	read_fmc(CfgDepBase_array_str_obj[1],CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1]);
	/* padding ? */
	i = CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1] % 4;
	while( i!=0 ){
		read_fmc(c,1);
		i = i-1;
	}

        CfgDepBase_tot_str_obj = CfgDepBase_str_objP2-CfgDepBase_tot_str_obj;
        CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj] = CfgDepBase_str_objP2;
}


void
#ifdef _BT_ANSIC
CfgDepBase_CRE_STR_OBJ( int *bb, int *pp )
#else
CfgDepBase_CRE_STR_OBJ( bb, pp )
int *bb, *pp;
#endif
{
	int b;
	CfgDepBase_OBJ_FUL_STR_OBJ(&b);
	if( b==0 ){
		if( CfgDepBase_ssiz_old_str_obj==0 ){
			CfgDepBase_adr_str_obj[CfgDepBase_ssiz_len_str_obj+1] = 
			    CfgDepBase_adr_str_obj[CfgDepBase_ssiz_len_str_obj];
			CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj+1] =
                                                             CfgDepBase_str_objP2;
			CfgDepBase_ssiz_adr_str_obj = CfgDepBase_ssiz_adr_str_obj+1;
			CfgDepBase_len_str_obj[CfgDepBase_ssiz_len_str_obj+1] = 0;
			CfgDepBase_ssiz_len_str_obj = CfgDepBase_ssiz_len_str_obj+1;
			*pp = CfgDepBase_ssiz_len_str_obj-1;
		} else {
			*pp=CfgDepBase_old_str_obj[CfgDepBase_ssiz_old_str_obj];
			CfgDepBase_ssiz_old_str_obj=CfgDepBase_ssiz_old_str_obj-1;
		}
		*bb=1;
	} else {
		*pp=0;
		*bb=0;
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_PSH_STR_OBJ( int *bb, int ss, int vv )
#else
CfgDepBase_PSH_STR_OBJ( bb, ss, vv )
int *bb, ss, vv;
#endif
{
	int e;
	CfgDepBase_MEM_FUL_STR_OBJ(&e);
	if( e==0 ){
		int search_res,y,k,r;
		r = 1;
		y = CfgDepBase_ssiz_adr_str_obj+1;
		search_res = 0;
		while( y!=r ){
			if( CfgDepBase_ssiz_adr_str_obj>2*ss-1 ){
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
				if( r<=2*(CfgDepBase_ssiz_adr_str_obj-ss) ){
					if( (r-1)%2 == 0 ){
						k =ss - (r/2);
					} else {
						k = ss + (r/2);
					}
				} else {
					k = CfgDepBase_ssiz_adr_str_obj+1-r;
				}
			}
			if( CfgDepBase_adr_str_obj[k]+CfgDepBase_len_str_obj[k]<
                                                     CfgDepBase_adr_str_obj[k+1] ){
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
				a = CfgDepBase_adr_str_obj[j];
				b = CfgDepBase_len_str_obj[j];
				{
					int k;
					k=a+b;
					while( k>a ){
						CfgDepBase_array_str_obj[k+1]=
                                                        CfgDepBase_array_str_obj[k];
						k=k-1;
					}
				}
				CfgDepBase_adr_str_obj[j] = CfgDepBase_adr_str_obj[j]+1;
				j = j-1;
			}
		} else {
			int j,a,b;
			j = search_res+1;
			while( j<=ss ){
				a = CfgDepBase_adr_str_obj[j];
				b = CfgDepBase_len_str_obj[j];
				{
					int k;
					k=a+1;
					while( k<=a+b ){
						CfgDepBase_array_str_obj[k-1]=
                                                         CfgDepBase_array_str_obj[k];
						k=k+1;
					}
				}
				CfgDepBase_adr_str_obj[j] = CfgDepBase_adr_str_obj[j]-1;
				j = j+1;
			}
		}
		CfgDepBase_len_str_obj[ss] = CfgDepBase_len_str_obj[ss]+1;
		CfgDepBase_tot_str_obj = CfgDepBase_tot_str_obj-1;
		CfgDepBase_array_str_obj[CfgDepBase_len_str_obj[ss]+CfgDepBase_adr_str_obj[ss]] = vv;
	}
	*bb=!e;
}


void
#ifdef _BT_ANSIC
CfgDepBase_SMR_STR_OBJ( int *bb, int ss, int tt )
#else
CfgDepBase_SMR_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int m,n,i,v,w;
	m = CfgDepBase_len_str_obj[ss];
	n = CfgDepBase_len_str_obj[tt];
	if( m<=n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = CfgDepBase_array_str_obj[i+CfgDepBase_adr_str_obj[ss]];
			w = CfgDepBase_array_str_obj[i+CfgDepBase_adr_str_obj[tt]];
			if( v<w ){
				i = m+1;
				*bb = 1;
			} else if( w<v ){
				i = m+1;
				*bb = 0;
			} else {
				i = i+1;
			}
		}
	} else {
		i = 1;
		*bb = 0;
		while( i<=n ){
			v = CfgDepBase_array_str_obj[i+CfgDepBase_adr_str_obj[ss]];
			w = CfgDepBase_array_str_obj[i+CfgDepBase_adr_str_obj[tt]];
			if( v<w ){
				i = n+1;
				*bb = 1;
			} else if( w<v ){
				i = n+1;
				*bb = 0;
			} else {
				i = i+1;
			}
		}
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_EQL_STR_OBJ( int *bb, int ss, int tt )
#else
CfgDepBase_EQL_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int m,n,i,v,w;
	m = CfgDepBase_len_str_obj[ss];
	n = CfgDepBase_len_str_obj[tt];
	if( m==n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = CfgDepBase_array_str_obj[i+CfgDepBase_adr_str_obj[ss]];
			w = CfgDepBase_array_str_obj[i+CfgDepBase_adr_str_obj[tt]];
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
CfgDepBase_SUB_STR_OBJ( int *bb, int ss, int tt )
#else
CfgDepBase_SUB_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int m,n,i,v,w;
	m = CfgDepBase_len_str_obj[ss];
	n = CfgDepBase_len_str_obj[tt];
	if( m<=n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = CfgDepBase_array_str_obj[i+CfgDepBase_adr_str_obj[ss]];
			w = CfgDepBase_array_str_obj[i+CfgDepBase_adr_str_obj[tt]];
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
CfgDepBase_EQL_LIT_STR_OBJ( int *bb, int tt, int *nn )
#else
CfgDepBase_EQL_LIT_STR_OBJ( bb, tt, nn )
int *bb, tt, *nn;
#endif
{
	int m,n,i,v,w;
	char *ss;
	ss = (char *)nn;
	m = 0;
	while( ss[m]!='\0' ){
		m = m+1;
	}
	n = CfgDepBase_len_str_obj[tt];
	if( m==n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = ss[i-1];
			w = CfgDepBase_array_str_obj[i+CfgDepBase_adr_str_obj[tt]];
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
CfgDepBase_NEW_STR_OBJ( int *bb, int *pp, int *nn )
#else
CfgDepBase_NEW_STR_OBJ( bb, pp, nn )
int *bb, *pp, *nn;
#endif
{
	int b,i,p;
	char *ss;
	ss = (char *)nn;
	CfgDepBase_CRE_STR_OBJ(&b,&p);
	if( b==1 ){
		i=0;
		while( (ss[i]!='\0') && (b==1) ){
			CfgDepBase_PSH_STR_OBJ(&b,p,ss[i]);
			i=i+1;
		}
		if( b==1 ){
			*pp = p;
			*bb = 1;
		} else {
			CfgDepBase_KIL_STR_OBJ(p);
			*pp = 0;
			*bb = 0;
		}
	} else {
		*pp = 0;
		*bb = b;
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_XTR_STR_OBJ( int *ss, int pp )
#else
CfgDepBase_XTR_STR_OBJ( ss, pp )
int *ss, pp;
#endif
{
	int i,v,s;
	char *t;
	t = (char *)ss;
	i = 0;
	s = CfgDepBase_len_str_obj[pp];
	while( i<s ){
		CfgDepBase_VAL_STR_OBJ(&v,pp,i+1);
		t[i] = v;
		i = i+1;
	}
	t[i] = '\0';
}


void
#ifdef _BT_ANSIC
CfgDepBase_APP_STR_OBJ( int *bb, int ss, int tt )
#else
CfgDepBase_APP_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int k,v,s,b,n;
	b=1;
	k=1;
	s=CfgDepBase_len_str_obj[tt];
	CfgDepBase_FRE_MEM_STR_OBJ(&n);
	if( s<=n ){
		while( k<=s ){
			CfgDepBase_VAL_STR_OBJ(&v,tt,k);
			CfgDepBase_PSH_STR_OBJ(&b,ss,v);
			k = k+1;
		}
		*bb=1;
	} else {
		*bb=0;
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_CPY_STR_OBJ(int * bb,int  ss, int tt )
#else
CfgDepBase_CPY_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int s,t,n;
	if( ss!=tt ){
		s = CfgDepBase_len_str_obj[ss];
		t = CfgDepBase_len_str_obj[tt];
		CfgDepBase_FRE_MEM_STR_OBJ(&n);
		if( s<=n+t ){
			CfgDepBase_CLR_STR_OBJ(tt);
			CfgDepBase_APP_STR_OBJ(&(*bb),tt,ss);
			*bb = 1;
		} else {
			*bb = 0;
		}
	} else {
		*bb = 1;
	}
}


/* ss over-written by tt */

void
#ifdef _BT_ANSIC
CfgDepBase_OVR_STR_OBJ( int *bb, int ss, int tt )
#else
CfgDepBase_OVR_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int s,t,n,i,v,b;
	if( ss!=tt ){
		s = CfgDepBase_len_str_obj[ss];
		t = CfgDepBase_len_str_obj[tt];
		CfgDepBase_FRE_MEM_STR_OBJ(&n);
		if( t<=n+s ){
			i = 1;
			while( i<=t ){
				CfgDepBase_VAL_STR_OBJ(&v,tt,i);
				if( i<=s ){
					CfgDepBase_STO_STR_OBJ(ss,i,v);
				} else {
					CfgDepBase_PSH_STR_OBJ(&b,ss,v);
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
CfgDepBase_CUT_STR_OBJ( int pp, int ii )
#else
CfgDepBase_CUT_STR_OBJ( pp, ii )
int pp, ii;
#endif
{
	int i,l,v;
	i = ii+1;
	CfgDepBase_LEN_STR_OBJ(&l,pp);
	while( i<=l ){
		CfgDepBase_VAL_STR_OBJ(&v,pp,i);
		CfgDepBase_STO_STR_OBJ(pp,i-ii,v);
		i = i+1
		    ;
	}
	CfgDepBase_len_str_obj[pp] = CfgDepBase_len_str_obj[pp]-ii;
	CfgDepBase_tot_str_obj = CfgDepBase_tot_str_obj+ii;
}


void
#ifdef _BT_ANSIC
CfgDepBase_SWP_STR_OBJ( int ss, int ii, int jj )
#else
CfgDepBase_SWP_STR_OBJ( ss, ii, jj )
int ss, ii, jj;
#endif
{
	int v,w;
	CfgDepBase_VAL_STR_OBJ(&v,ss,ii);
	CfgDepBase_VAL_STR_OBJ(&w,ss,jj);
	CfgDepBase_STO_STR_OBJ(ss,jj,v);
	CfgDepBase_STO_STR_OBJ(ss,ii,w);
}


void
#ifdef _BT_ANSIC
CfgDepBase_REV_STR_OBJ( int ss )
#else
CfgDepBase_REV_STR_OBJ( ss )
int ss;
#endif
{
	int i,j;
	i=1;
	CfgDepBase_LEN_STR_OBJ(&j,ss);
	while( i<j ){
		CfgDepBase_SWP_STR_OBJ(ss,i,j);
		i=i+1;
		j=j-1;
	}
}


void
#ifdef _BT_ANSIC
CfgDepBase_FIRST_STR_OBJ( int *cc, int *ss )
#else
CfgDepBase_FIRST_STR_OBJ( cc, ss )
int *cc, *ss;
#endif
{
	int c,i,b;
	c = ( CfgDepBase_ssiz_len_str_obj - 1 - CfgDepBase_ssiz_old_str_obj );
	if ( c != 0 ) {
		i = CfgDepBase_ssiz_len_str_obj - 1;
		CfgDepBase_XST_STR_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			CfgDepBase_XST_STR_OBJ(&b,i);
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
CfgDepBase_NEXT_STR_OBJ( int *cc, int *ss, int oc, int os )
#else
CfgDepBase_NEXT_STR_OBJ( cc, ss, oc, os )
int *cc, *ss, oc, os;
#endif
{
	int c,i,b;
	c = oc - 1;
	if ( c != 0 ) {
		i = os - 1;
		CfgDepBase_XST_STR_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			CfgDepBase_XST_STR_OBJ(&b,i);
		}
		*ss = i;
		*cc = c;
	} else {
		*ss = 0;
		*cc = 0;
	}

}
