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
#include "btl_proof_str_obj.h"
#include "basic_io.h"

INI_btl_proof_str_obj()
{
	btl_proof_ssiz_adr_str_obj = 0;
	btl_proof_ssiz_len_str_obj = 0;
	btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj+1] = 0;
	btl_proof_ssiz_adr_str_obj = btl_proof_ssiz_adr_str_obj+1;
	btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj+1] = btl_proof_str_objP2;
	btl_proof_ssiz_adr_str_obj = btl_proof_ssiz_adr_str_obj+1;
	btl_proof_len_str_obj[btl_proof_ssiz_len_str_obj+1] = 0;
	btl_proof_ssiz_len_str_obj = btl_proof_ssiz_len_str_obj+1;
	btl_proof_tot_str_obj = btl_proof_str_objP2;
	btl_proof_ssiz_old_str_obj = 0;
}


btl_proof_INI_STR_OBJ()
{
	btl_proof_ssiz_adr_str_obj = 0;
	btl_proof_ssiz_len_str_obj = 0;
	btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj+1] = 0;
	btl_proof_ssiz_adr_str_obj = btl_proof_ssiz_adr_str_obj+1;
	btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj+1] = btl_proof_str_objP2;
	btl_proof_ssiz_adr_str_obj = btl_proof_ssiz_adr_str_obj+1;
	btl_proof_len_str_obj[btl_proof_ssiz_len_str_obj+1] = 0;
	btl_proof_ssiz_len_str_obj = btl_proof_ssiz_len_str_obj+1;
	btl_proof_tot_str_obj = btl_proof_str_objP2;
	btl_proof_ssiz_old_str_obj = 0;
}


btl_proof_XST_STR_OBJ( bb, pp )
int *bb, pp;
{
	if ( pp > 0 && pp < btl_proof_ssiz_len_str_obj ) {
		int i;
		i = btl_proof_ssiz_old_str_obj;
		*bb = 1;
		while ( i != 0 ) {
			if ( pp != btl_proof_old_str_obj[i] ) {
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

btl_proof_SAV_STR_OBJ()
{
	int i;
	char c;
        btl_proof_tot_str_obj = btl_proof_str_objP2-btl_proof_tot_str_obj;
	write_fm(btl_proof_tot_str_obj,1);
	write_fm(btl_proof_ssiz_adr_str_obj,1);
	write_fm(btl_proof_adr_str_obj[1],btl_proof_ssiz_adr_str_obj);
	write_fm(btl_proof_ssiz_len_str_obj,1);
	write_fm(btl_proof_len_str_obj[1],btl_proof_ssiz_len_str_obj);
	write_fm(btl_proof_ssiz_old_str_obj,1);
	write_fm(btl_proof_old_str_obj[1],btl_proof_ssiz_old_str_obj);
	write_fmc(btl_proof_array_str_obj[1],btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj-1]);
	i = btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj-1] % 4;
	c = 'w';
	while( i!=0 ){
		write_fmc(c,1);
		i = i-1;
	}
        btl_proof_tot_str_obj = btl_proof_str_objP2-btl_proof_tot_str_obj;
}

btl_proof_SAVN_STR_OBJ()
{
	int i, j, k;
	char c;
        btl_proof_tot_str_obj = btl_proof_str_objP2-btl_proof_tot_str_obj;

	btl_proof_tot_str_obj = htonl ( btl_proof_tot_str_obj );
        write_fm(btl_proof_tot_str_obj,1);
	btl_proof_tot_str_obj = ntohl ( btl_proof_tot_str_obj );

	btl_proof_ssiz_adr_str_obj = htonl ( btl_proof_ssiz_adr_str_obj );
	write_fm(btl_proof_ssiz_adr_str_obj,1);
	btl_proof_ssiz_adr_str_obj = ntohl ( btl_proof_ssiz_adr_str_obj );

	convert_arr_htonl(btl_proof_adr_str_obj,1,btl_proof_ssiz_adr_str_obj);
	write_fm(btl_proof_adr_str_obj[1],btl_proof_ssiz_adr_str_obj);
	convert_arr_ntohl(btl_proof_adr_str_obj,1,btl_proof_ssiz_adr_str_obj);

	btl_proof_ssiz_len_str_obj = htonl ( btl_proof_ssiz_len_str_obj );
	write_fm(btl_proof_ssiz_len_str_obj,1);
	btl_proof_ssiz_len_str_obj = ntohl ( btl_proof_ssiz_len_str_obj );

	convert_arr_htonl(btl_proof_len_str_obj,1,btl_proof_ssiz_len_str_obj);
	write_fm(btl_proof_len_str_obj[1],btl_proof_ssiz_len_str_obj);
	convert_arr_ntohl(btl_proof_len_str_obj,1,btl_proof_ssiz_len_str_obj);

	btl_proof_ssiz_old_str_obj = htonl ( btl_proof_ssiz_old_str_obj );
	write_fm(btl_proof_ssiz_old_str_obj,1);
	btl_proof_ssiz_old_str_obj = ntohl ( btl_proof_ssiz_old_str_obj );

	convert_arr_htonl(btl_proof_old_str_obj,1,btl_proof_ssiz_old_str_obj);
	write_fm(btl_proof_old_str_obj[1],btl_proof_ssiz_old_str_obj);
	convert_arr_ntohl(btl_proof_old_str_obj,1,btl_proof_ssiz_old_str_obj);

	write_fmc(btl_proof_array_str_obj[1],btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj-1]);
	/* padding ? */
	i = btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj-1] % 4;
	c = 'w';
	while( i!=0 ){
		write_fmc(c,1);
		i = i-1;
	}

        btl_proof_tot_str_obj = btl_proof_str_objP2-btl_proof_tot_str_obj;
}


#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

#define  read_fmc(a,b)   fread(&a,sizeof(char),b,dump_file)

btl_proof_RST_STR_OBJ()
{
	int i;
	char c;
	read_fm(btl_proof_tot_str_obj,1);
	read_fm(btl_proof_ssiz_adr_str_obj,1);
	read_fm(btl_proof_adr_str_obj[1],btl_proof_ssiz_adr_str_obj);
	read_fm(btl_proof_ssiz_len_str_obj,1);
	read_fm(btl_proof_len_str_obj[1],btl_proof_ssiz_len_str_obj);
	read_fm(btl_proof_ssiz_old_str_obj,1);
	read_fm(btl_proof_old_str_obj[1],btl_proof_ssiz_old_str_obj);
	read_fmc(btl_proof_array_str_obj[1],btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj-1]);
	i = btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj-1] % 4;
	while( i!=0 ){
		read_fmc(c,1);
		i = i-1;
	}
        btl_proof_tot_str_obj = btl_proof_str_objP2-btl_proof_tot_str_obj;
        btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj] = btl_proof_str_objP2;
}

btl_proof_RSTN_STR_OBJ()
{
	int i, j, k;
	char c;
	read_fm(btl_proof_tot_str_obj,1);
	btl_proof_tot_str_obj = ntohl ( btl_proof_tot_str_obj );

	read_fm(btl_proof_ssiz_adr_str_obj,1);
	btl_proof_ssiz_adr_str_obj = ntohl ( btl_proof_ssiz_adr_str_obj );

	read_fm(btl_proof_adr_str_obj[1],btl_proof_ssiz_adr_str_obj);
	convert_arr_ntohl(btl_proof_adr_str_obj,1,btl_proof_ssiz_adr_str_obj);

	read_fm(btl_proof_ssiz_len_str_obj,1);
	btl_proof_ssiz_len_str_obj = ntohl ( btl_proof_ssiz_len_str_obj );

	read_fm(btl_proof_len_str_obj[1],btl_proof_ssiz_len_str_obj);
	convert_arr_ntohl(btl_proof_len_str_obj,1,btl_proof_ssiz_len_str_obj);

	read_fm(btl_proof_ssiz_old_str_obj,1);
	btl_proof_ssiz_old_str_obj = ntohl ( btl_proof_ssiz_old_str_obj );

	read_fm(btl_proof_old_str_obj[1],btl_proof_ssiz_old_str_obj);
	convert_arr_ntohl(btl_proof_old_str_obj,1,btl_proof_ssiz_old_str_obj);

	read_fmc(btl_proof_array_str_obj[1],btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj-1]);
	/* padding ? */
	i = btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj-1] % 4;
	while( i!=0 ){
		read_fmc(c,1);
		i = i-1;
	}

        btl_proof_tot_str_obj = btl_proof_str_objP2-btl_proof_tot_str_obj;
        btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj] = btl_proof_str_objP2;
}


btl_proof_CRE_STR_OBJ( bb, pp )
int *bb, *pp;
{
	int b;
	btl_proof_OBJ_FUL_STR_OBJ(&b);
	if( b==0 ){
		if( btl_proof_ssiz_old_str_obj==0 ){
			btl_proof_adr_str_obj[btl_proof_ssiz_len_str_obj+1] = 
			    btl_proof_adr_str_obj[btl_proof_ssiz_len_str_obj];
			btl_proof_adr_str_obj[btl_proof_ssiz_adr_str_obj+1] =
                                                             btl_proof_str_objP2;
			btl_proof_ssiz_adr_str_obj = btl_proof_ssiz_adr_str_obj+1;
			btl_proof_len_str_obj[btl_proof_ssiz_len_str_obj+1] = 0;
			btl_proof_ssiz_len_str_obj = btl_proof_ssiz_len_str_obj+1;
			*pp = btl_proof_ssiz_len_str_obj-1;
		} else {
			*pp=btl_proof_old_str_obj[btl_proof_ssiz_old_str_obj];
			btl_proof_ssiz_old_str_obj=btl_proof_ssiz_old_str_obj-1;
		}
		*bb=1;
	} else {
		*pp=0;
		*bb=0;
	}
}


btl_proof_PSH_STR_OBJ( bb, ss, vv )
int *bb, ss, vv;
{
	int e;
	btl_proof_MEM_FUL_STR_OBJ(&e);
	if( e==0 ){
		int search_res,y,k,r;
		r = 1;
		y = btl_proof_ssiz_adr_str_obj+1;
		search_res = 0;
		while( y!=r ){
			if( btl_proof_ssiz_adr_str_obj>2*ss-1 ){
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
				if( r<=2*(btl_proof_ssiz_adr_str_obj-ss) ){
					if( (r-1)%2 == 0 ){
						k =ss - (r/2);
					} else {
						k = ss + (r/2);
					}
				} else {
					k = btl_proof_ssiz_adr_str_obj+1-r;
				}
			}
			if( btl_proof_adr_str_obj[k]+btl_proof_len_str_obj[k]<
                                                     btl_proof_adr_str_obj[k+1] ){
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
				a = btl_proof_adr_str_obj[j];
				b = btl_proof_len_str_obj[j];
				{
					int k;
					k=a+b;
					while( k>a ){
						btl_proof_array_str_obj[k+1]=
                                                        btl_proof_array_str_obj[k];
						k=k-1;
					}
				}
				btl_proof_adr_str_obj[j] = btl_proof_adr_str_obj[j]+1;
				j = j-1;
			}
		} else {
			int j,a,b;
			j = search_res+1;
			while( j<=ss ){
				a = btl_proof_adr_str_obj[j];
				b = btl_proof_len_str_obj[j];
				{
					int k;
					k=a+1;
					while( k<=a+b ){
						btl_proof_array_str_obj[k-1]=
                                                         btl_proof_array_str_obj[k];
						k=k+1;
					}
				}
				btl_proof_adr_str_obj[j] = btl_proof_adr_str_obj[j]-1;
				j = j+1;
			}
		}
		btl_proof_len_str_obj[ss] = btl_proof_len_str_obj[ss]+1;
		btl_proof_tot_str_obj = btl_proof_tot_str_obj-1;
		btl_proof_array_str_obj[btl_proof_len_str_obj[ss]+btl_proof_adr_str_obj[ss]] = vv;
	}
	*bb=!e;
}


btl_proof_SMR_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
{
	int m,n,i,v,w;
	m = btl_proof_len_str_obj[ss];
	n = btl_proof_len_str_obj[tt];
	if( m<=n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = btl_proof_array_str_obj[i+btl_proof_adr_str_obj[ss]];
			w = btl_proof_array_str_obj[i+btl_proof_adr_str_obj[tt]];
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
			v = btl_proof_array_str_obj[i+btl_proof_adr_str_obj[ss]];
			w = btl_proof_array_str_obj[i+btl_proof_adr_str_obj[tt]];
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


btl_proof_EQL_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
{
	int m,n,i,v,w;
	m = btl_proof_len_str_obj[ss];
	n = btl_proof_len_str_obj[tt];
	if( m==n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = btl_proof_array_str_obj[i+btl_proof_adr_str_obj[ss]];
			w = btl_proof_array_str_obj[i+btl_proof_adr_str_obj[tt]];
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


btl_proof_SUB_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
{
	int m,n,i,v,w;
	m = btl_proof_len_str_obj[ss];
	n = btl_proof_len_str_obj[tt];
	if( m<=n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = btl_proof_array_str_obj[i+btl_proof_adr_str_obj[ss]];
			w = btl_proof_array_str_obj[i+btl_proof_adr_str_obj[tt]];
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


btl_proof_EQL_LIT_STR_OBJ( bb, tt, nn )
int *bb, tt, *nn;
{
	int m,n,i,v,w;
	char *ss;
	ss = (char *)nn;
	m = 0;
	while( ss[m]!='\0' ){
		m = m+1;
	}
	n = btl_proof_len_str_obj[tt];
	if( m==n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = ss[i-1];
			w = btl_proof_array_str_obj[i+btl_proof_adr_str_obj[tt]];
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


btl_proof_NEW_STR_OBJ( bb, pp, nn )
int *bb, *pp, *nn;
{
	int b,i,p;
	char *ss;
	ss = (char *)nn;
	btl_proof_CRE_STR_OBJ(&b,&p);
	if( b==1 ){
		i=0;
		while( (ss[i]!='\0') && (b==1) ){
			btl_proof_PSH_STR_OBJ(&b,p,ss[i]);
			i=i+1;
		}
		if( b==1 ){
			*pp = p;
			*bb = 1;
		} else {
			btl_proof_KIL_STR_OBJ(p);
			*pp = 0;
			*bb = 0;
		}
	} else {
		*pp = 0;
		*bb = b;
	}
}


btl_proof_XTR_STR_OBJ( ss, pp )
int *ss, pp;
{
	int i,v,s;
	char *t;
	t = (char *)ss;
	i = 0;
	s = btl_proof_len_str_obj[pp];
	while( i<s ){
		btl_proof_VAL_STR_OBJ(&v,pp,i+1);
		t[i] = v;
		i = i+1;
	}
	t[i] = '\0';
}


btl_proof_APP_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
{
	int k,v,s,b,n;
	b=1;
	k=1;
	s=btl_proof_len_str_obj[tt];
	btl_proof_FRE_MEM_STR_OBJ(&n);
	if( s<=n ){
		while( k<=s ){
			btl_proof_VAL_STR_OBJ(&v,tt,k);
			btl_proof_PSH_STR_OBJ(&b,ss,v);
			k = k+1;
		}
		*bb=1;
	} else {
		*bb=0;
	}
}


btl_proof_CPY_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
{
	int s,t,n;
	if( ss!=tt ){
		s = btl_proof_len_str_obj[ss];
		t = btl_proof_len_str_obj[tt];
		btl_proof_FRE_MEM_STR_OBJ(&n);
		if( s<=n+t ){
			btl_proof_CLR_STR_OBJ(tt);
			btl_proof_APP_STR_OBJ(&(*bb),tt,ss);
			*bb = 1;
		} else {
			*bb = 0;
		}
	} else {
		*bb = 1;
	}
}


/* ss over-written by tt */

btl_proof_OVR_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
{
	int s,t,n,i,v,b;
	if( ss!=tt ){
		s = btl_proof_len_str_obj[ss];
		t = btl_proof_len_str_obj[tt];
		btl_proof_FRE_MEM_STR_OBJ(&n);
		if( t<=n+s ){
			i = 1;
			while( i<=t ){
				btl_proof_VAL_STR_OBJ(&v,tt,i);
				if( i<=s ){
					btl_proof_STO_STR_OBJ(ss,i,v);
				} else {
					btl_proof_PSH_STR_OBJ(&b,ss,v);
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


btl_proof_CUT_STR_OBJ( pp, ii )
int pp, ii;
{
	int i,l,v;
	i = ii+1;
	btl_proof_LEN_STR_OBJ(&l,pp);
	while( i<=l ){
		btl_proof_VAL_STR_OBJ(&v,pp,i);
		btl_proof_STO_STR_OBJ(pp,i-ii,v);
		i = i+1
		    ;
	}
	btl_proof_len_str_obj[pp] = btl_proof_len_str_obj[pp]-ii;
	btl_proof_tot_str_obj = btl_proof_tot_str_obj+ii;
}


btl_proof_SWP_STR_OBJ( ss, ii, jj )
int ss, ii, jj;
{
	int v,w;
	btl_proof_VAL_STR_OBJ(&v,ss,ii);
	btl_proof_VAL_STR_OBJ(&w,ss,jj);
	btl_proof_STO_STR_OBJ(ss,jj,v);
	btl_proof_STO_STR_OBJ(ss,ii,w);
}


btl_proof_REV_STR_OBJ( ss )
int ss;
{
	int i,j;
	i=1;
	btl_proof_LEN_STR_OBJ(&j,ss);
	while( i<j ){
		btl_proof_SWP_STR_OBJ(ss,i,j);
		i=i+1;
		j=j-1;
	}
}


btl_proof_FIRST_STR_OBJ( cc, ss )
int *cc, *ss;
{
	int c,i,b;
	c = ( btl_proof_ssiz_len_str_obj - 1 - btl_proof_ssiz_old_str_obj );
	if ( c != 0 ) {
		i = btl_proof_ssiz_len_str_obj - 1;
		btl_proof_XST_STR_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			btl_proof_XST_STR_OBJ(&b,i);
		}
		*ss = i;
		*cc = c;
	} else {
		*ss = 0;
		*cc = 0;
	}
}


btl_proof_NEXT_STR_OBJ( cc, ss, oc, os )
int *cc, *ss, oc, os;
{
	int c,i,b;
	c = oc - 1;
	if ( c != 0 ) {
		i = os - 1;
		btl_proof_XST_STR_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			btl_proof_XST_STR_OBJ(&b,i);
		}
		*ss = i;
		*cc = c;
	} else {
		*ss = 0;
		*cc = 0;
	}

}
