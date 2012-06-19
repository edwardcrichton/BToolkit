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
#include "btl_proof_seq_obj.h"
#include "btl_proof_seq_ctx.h"
#include "basic_io.h"


INI_btl_proof_seq_obj()
{
	btl_proof_ssiz_adr_seq_obj = 0;
	btl_proof_ssiz_len_seq_obj = 0;
	btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj+1] = 0;
	btl_proof_ssiz_adr_seq_obj = btl_proof_ssiz_adr_seq_obj+1;
	btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj+1] = btl_proof_seq_objP3;
	btl_proof_ssiz_adr_seq_obj = btl_proof_ssiz_adr_seq_obj+1;
	btl_proof_len_seq_obj[btl_proof_ssiz_len_seq_obj+1] = 0;
	btl_proof_ssiz_len_seq_obj = btl_proof_ssiz_len_seq_obj+1;
	btl_proof_tot_seq_obj = btl_proof_seq_objP3;
	btl_proof_ssiz_old_seq_obj = 0;
}


btl_proof_INI_SEQ_OBJ()
{
	btl_proof_ssiz_adr_seq_obj = 0;
	btl_proof_ssiz_len_seq_obj = 0;
	btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj+1] = 0;
	btl_proof_ssiz_adr_seq_obj = btl_proof_ssiz_adr_seq_obj+1;
	btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj+1] = btl_proof_seq_objP3;
	btl_proof_ssiz_adr_seq_obj = btl_proof_ssiz_adr_seq_obj+1;
	btl_proof_len_seq_obj[btl_proof_ssiz_len_seq_obj+1] = 0;
	btl_proof_ssiz_len_seq_obj = btl_proof_ssiz_len_seq_obj+1;
	btl_proof_tot_seq_obj = btl_proof_seq_objP3;
	btl_proof_ssiz_old_seq_obj = 0;
}


btl_proof_XST_SEQ_OBJ( bb, pp )
int *bb, pp;
{
	if ( pp > 0 && pp < btl_proof_ssiz_len_seq_obj ) {
		int i;
		i = btl_proof_ssiz_old_seq_obj;
		*bb = 1;
		while ( i != 0 ) {
			if ( pp != btl_proof_old_seq_obj[i] ) {
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

btl_proof_SAV_SEQ_OBJ()
{
        btl_proof_tot_seq_obj = btl_proof_seq_objP3-btl_proof_tot_seq_obj;
	write_fm(btl_proof_tot_seq_obj,1);
	write_fm(btl_proof_ssiz_adr_seq_obj,1);
	write_fm(btl_proof_adr_seq_obj[1],btl_proof_ssiz_adr_seq_obj);
	write_fm(btl_proof_ssiz_len_seq_obj,1);
	write_fm(btl_proof_len_seq_obj[1],btl_proof_ssiz_len_seq_obj);
	write_fm(btl_proof_ssiz_old_seq_obj,1);
	write_fm(btl_proof_old_seq_obj[1],btl_proof_ssiz_old_seq_obj);
	write_fm(btl_proof_array_seq_obj[1],btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj-1]);
        btl_proof_tot_seq_obj = btl_proof_seq_objP3-btl_proof_tot_seq_obj;
}

btl_proof_SAVN_SEQ_OBJ()
{
        int j, k;
        btl_proof_tot_seq_obj = btl_proof_seq_objP3-btl_proof_tot_seq_obj;

	btl_proof_tot_seq_obj = htonl ( btl_proof_tot_seq_obj );
        write_fm(btl_proof_tot_seq_obj,1);
	btl_proof_tot_seq_obj = ntohl ( btl_proof_tot_seq_obj );

	btl_proof_ssiz_adr_seq_obj = htonl ( btl_proof_ssiz_adr_seq_obj );
	write_fm(btl_proof_ssiz_adr_seq_obj,1);
	btl_proof_ssiz_adr_seq_obj = ntohl ( btl_proof_ssiz_adr_seq_obj );

	convert_arr_htonl(btl_proof_adr_seq_obj,1,btl_proof_ssiz_adr_seq_obj);
        write_fm(btl_proof_adr_seq_obj[1],btl_proof_ssiz_adr_seq_obj);
	convert_arr_ntohl(btl_proof_adr_seq_obj,1,btl_proof_ssiz_adr_seq_obj);

	btl_proof_ssiz_len_seq_obj = htonl ( btl_proof_ssiz_len_seq_obj );
	write_fm(btl_proof_ssiz_len_seq_obj,1);
	btl_proof_ssiz_len_seq_obj = ntohl ( btl_proof_ssiz_len_seq_obj );

	convert_arr_htonl(btl_proof_len_seq_obj,1,btl_proof_ssiz_len_seq_obj);
	write_fm(btl_proof_len_seq_obj[1],btl_proof_ssiz_len_seq_obj);
	convert_arr_ntohl(btl_proof_len_seq_obj,1,btl_proof_ssiz_len_seq_obj);

	btl_proof_ssiz_old_seq_obj = htonl ( btl_proof_ssiz_old_seq_obj );
	write_fm(btl_proof_ssiz_old_seq_obj,1);
	btl_proof_ssiz_old_seq_obj = ntohl ( btl_proof_ssiz_old_seq_obj );

	convert_arr_htonl(btl_proof_old_seq_obj,1,btl_proof_ssiz_old_seq_obj);
	write_fm(btl_proof_old_seq_obj[1],btl_proof_ssiz_old_seq_obj);
	convert_arr_ntohl(btl_proof_old_seq_obj,1,btl_proof_ssiz_old_seq_obj);

	convert_arr_htonl(btl_proof_array_seq_obj,1,btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj-1]);
	write_fm(btl_proof_array_seq_obj[1],btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj-1]);
	convert_arr_ntohl(btl_proof_array_seq_obj,1,btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj-1]);

        btl_proof_tot_seq_obj = btl_proof_seq_objP3-btl_proof_tot_seq_obj;
}


#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

btl_proof_RST_SEQ_OBJ()
{
	read_fm(btl_proof_tot_seq_obj,1);
	read_fm(btl_proof_ssiz_adr_seq_obj,1);
	read_fm(btl_proof_adr_seq_obj[1],btl_proof_ssiz_adr_seq_obj);
	read_fm(btl_proof_ssiz_len_seq_obj,1);
	read_fm(btl_proof_len_seq_obj[1],btl_proof_ssiz_len_seq_obj);
	read_fm(btl_proof_ssiz_old_seq_obj,1);
	read_fm(btl_proof_old_seq_obj[1],btl_proof_ssiz_old_seq_obj);
	read_fm(btl_proof_array_seq_obj[1],
                   btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj-1]);
        btl_proof_tot_seq_obj = btl_proof_seq_objP3-btl_proof_tot_seq_obj;
        btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj] = btl_proof_seq_objP3;
}

btl_proof_RSTN_SEQ_OBJ()
{
        int j, k;
	read_fm(btl_proof_tot_seq_obj,1);
        btl_proof_tot_seq_obj = ntohl ( btl_proof_tot_seq_obj );

	read_fm(btl_proof_ssiz_adr_seq_obj,1);
        btl_proof_ssiz_adr_seq_obj = ntohl ( btl_proof_ssiz_adr_seq_obj );

	read_fm(btl_proof_adr_seq_obj[1],btl_proof_ssiz_adr_seq_obj);
	convert_arr_ntohl(btl_proof_adr_seq_obj,1,btl_proof_ssiz_adr_seq_obj);

	read_fm(btl_proof_ssiz_len_seq_obj,1);
        btl_proof_ssiz_len_seq_obj = ntohl ( btl_proof_ssiz_len_seq_obj );

	read_fm(btl_proof_len_seq_obj[1],btl_proof_ssiz_len_seq_obj);
	convert_arr_ntohl(btl_proof_len_seq_obj,1,btl_proof_ssiz_len_seq_obj);

	read_fm(btl_proof_ssiz_old_seq_obj,1);
        btl_proof_ssiz_old_seq_obj = ntohl ( btl_proof_ssiz_old_seq_obj );

	read_fm(btl_proof_old_seq_obj[1],btl_proof_ssiz_old_seq_obj);
	convert_arr_ntohl(btl_proof_old_seq_obj,1,btl_proof_ssiz_old_seq_obj);

	read_fm(btl_proof_array_seq_obj[1],btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj-1]);
	convert_arr_ntohl(btl_proof_array_seq_obj,1,btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj-1]);

        btl_proof_tot_seq_obj = btl_proof_seq_objP3-btl_proof_tot_seq_obj;
        btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj] = btl_proof_seq_objP3;
}


btl_proof_CRE_SEQ_OBJ( bb, pp )
int *bb, *pp;
{
	int b;
	btl_proof_OBJ_FUL_SEQ_OBJ(&b);
	if( b==0 ){
		if( btl_proof_ssiz_old_seq_obj==0 ){
			btl_proof_adr_seq_obj[btl_proof_ssiz_len_seq_obj+1] = 
			    btl_proof_adr_seq_obj[btl_proof_ssiz_len_seq_obj];
			btl_proof_adr_seq_obj[btl_proof_ssiz_adr_seq_obj+1] =
                                                             btl_proof_seq_objP3;
			btl_proof_ssiz_adr_seq_obj = btl_proof_ssiz_adr_seq_obj+1;
			btl_proof_len_seq_obj[btl_proof_ssiz_len_seq_obj+1] = 0;
			btl_proof_ssiz_len_seq_obj = btl_proof_ssiz_len_seq_obj+1;
			*pp = btl_proof_ssiz_len_seq_obj-1;
		} else {
			*pp=btl_proof_old_seq_obj[btl_proof_ssiz_old_seq_obj];
			btl_proof_ssiz_old_seq_obj=btl_proof_ssiz_old_seq_obj-1;
		}
		*bb=1;
	} else {
		*pp=0;
		*bb=0;
	}
}


btl_proof_PSH_SEQ_OBJ( bb, ss, vv )
int *bb, ss, vv;
{
	int e;
	btl_proof_MEM_FUL_SEQ_OBJ(&e);
	if( e==0 ){
		int search_res,y,k,r;
		r = 1;
		y = btl_proof_ssiz_adr_seq_obj+1;
		search_res = 0;
		while( y!=r ){
			if( btl_proof_ssiz_adr_seq_obj>2*ss-1 ){
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
				if( r<=2*(btl_proof_ssiz_adr_seq_obj-ss) ){
					if( (r-1)%2 == 0 ){
						k =ss - (r/2);
					} else {
						k = ss + (r/2);
					}
				} else {
					k = btl_proof_ssiz_adr_seq_obj+1-r;
				}
			}
			if( btl_proof_adr_seq_obj[k]+btl_proof_len_seq_obj[k]<
                                                     btl_proof_adr_seq_obj[k+1] ){
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
				a = btl_proof_adr_seq_obj[j];
				b = btl_proof_len_seq_obj[j];
				{
					int k;
					k=a+b;
					while( k>a ){
						btl_proof_array_seq_obj[k+1]=
                                                        btl_proof_array_seq_obj[k];
						k=k-1;
					}
				}
				btl_proof_adr_seq_obj[j] = btl_proof_adr_seq_obj[j]+1;
				j = j-1;
			}
		} else {
			int j,a,b;
			j = search_res+1;
			while( j<=ss ){
				a = btl_proof_adr_seq_obj[j];
				b = btl_proof_len_seq_obj[j];
				{
					int k;
					k=a+1;
					while( k<=a+b ){
						btl_proof_array_seq_obj[k-1]=
                                                        btl_proof_array_seq_obj[k];
						k=k+1;
					}
				}
				btl_proof_adr_seq_obj[j] = btl_proof_adr_seq_obj[j]-1;
				j = j+1;
			}
		}
		btl_proof_len_seq_obj[ss] = btl_proof_len_seq_obj[ss]+1;
		btl_proof_tot_seq_obj = btl_proof_tot_seq_obj-1;
		btl_proof_array_seq_obj[btl_proof_len_seq_obj[ss]+btl_proof_adr_seq_obj[ss]] = vv;
	}
	*bb=!e;
}


/* 

 ANSIC header 
btl_proof_SMR_SEQ_OBJ( int *bb, int ss, int tt )
 end ANSIC header 

 non-ANSIC header 
btl_proof_SMR_SEQ_OBJ( bb, ss, tt )
int *bb, ss, tt;
 end non-ANSIC header 

{
	int m,n,i,v,w;
	m = btl_proof_len_seq_obj[ss];
	n = btl_proof_len_seq_obj[tt];
	if( m<=n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = btl_proof_array_seq_obj[i+btl_proof_adr_seq_obj[ss]];
			w = btl_proof_array_seq_obj[i+btl_proof_adr_seq_obj[tt]];
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
			v = btl_proof_array_seq_obj[i+btl_proof_adr_seq_obj[ss]];
			w = btl_proof_array_seq_obj[i+btl_proof_adr_seq_obj[tt]];
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
*/

btl_proof_EQL_SEQ_OBJ( bb, ss, tt )
int *bb, ss, tt;
{
	int m,n,i,v,w;
	m = btl_proof_len_seq_obj[ss];
	n = btl_proof_len_seq_obj[tt];
	if( m==n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = btl_proof_array_seq_obj[i+btl_proof_adr_seq_obj[ss]];
			w = btl_proof_array_seq_obj[i+btl_proof_adr_seq_obj[tt]];
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


btl_proof_MBR_SEQ_OBJ( bb, ii, tt, vv )
int *bb, *ii, tt, vv;
{
	int n,i,v;
	n = btl_proof_len_seq_obj[tt];
	if( n!=0 ){
		i = 1;
		*bb = 0;
		while( i<=n ){
			v = btl_proof_array_seq_obj[i+btl_proof_adr_seq_obj[tt]];
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


btl_proof_APP_SEQ_OBJ( bb, ss, tt )
int *bb, ss, tt;
{
	int k,v,s,b,n;
	b=1;
	k=1;
	s=btl_proof_len_seq_obj[tt];
	btl_proof_FRE_MEM_SEQ_OBJ(&n);
	if( s<=n ){
		while( k<=s ){
			btl_proof_VAL_SEQ_OBJ(&v,tt,k);
			btl_proof_PSH_SEQ_OBJ(&b,ss,v);
			k = k+1;
		}
		*bb=1;
	} else {
		*bb=0;
	}
}


btl_proof_CPY_SEQ_OBJ( bb, ss, tt )
int *bb, ss, tt;
{
	int s,t,n;
	if( ss!=tt ){
		s = btl_proof_len_seq_obj[ss];
		t = btl_proof_len_seq_obj[tt];
		btl_proof_FRE_MEM_SEQ_OBJ(&n);
		if( s<=n+t ){
			btl_proof_CLR_SEQ_OBJ(tt);
			btl_proof_APP_SEQ_OBJ(&(*bb),tt,ss);
			*bb = 1;
		} else {
			*bb = 0;
		}
	} else {
		*bb = 0;
	}
}


btl_proof_OVR_SEQ_OBJ( bb, ss, tt )
int *bb, ss, tt;
{
	int s,t,n,i,v,b;
	if( ss!=tt ){
		s = btl_proof_len_seq_obj[ss];
		t = btl_proof_len_seq_obj[tt];
		btl_proof_FRE_MEM_SEQ_OBJ(&n);
		if( t<=n+s ){
			i = 1;
			while( i<=t ){
				btl_proof_VAL_SEQ_OBJ(&v,tt,i);
				if( i<=s ){
					btl_proof_STO_SEQ_OBJ(ss,i,v);
				} else {
					btl_proof_PSH_SEQ_OBJ(&b,ss,v);
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


btl_proof_CUT_SEQ_OBJ( pp, ii )
int pp, ii;
{
	int i,l,v;
	i = ii+1;
	btl_proof_LEN_SEQ_OBJ(&l,pp);
	while( i<=l ){
		btl_proof_VAL_SEQ_OBJ(&v,pp,i);
		btl_proof_STO_SEQ_OBJ(pp,i-ii,v);
		i = i+1
		    ;
	}
	btl_proof_len_seq_obj[pp] = btl_proof_len_seq_obj[pp]-ii;
	btl_proof_tot_seq_obj = btl_proof_tot_seq_obj+ii;
}


btl_proof_SWP_SEQ_OBJ( ss, ii, jj )
int ss, ii, jj;
{
	int v,w;
	btl_proof_VAL_SEQ_OBJ(&v,ss,ii);
	btl_proof_VAL_SEQ_OBJ(&w,ss,jj);
	btl_proof_STO_SEQ_OBJ(ss,jj,v);
	btl_proof_STO_SEQ_OBJ(ss,ii,w);
}


btl_proof_REV_SEQ_OBJ( ss )
int ss;
{
	int i,j;
	i=1;
	btl_proof_LEN_SEQ_OBJ(&j,ss);
	while( i<j ){
		btl_proof_SWP_SEQ_OBJ(ss,i,j);
		i=i+1;
		j=j-1;
	}
}


btl_proof_FIRST_SEQ_OBJ( cc, ss )
int *cc, *ss;
{
	int c,i,b;
	c = ( btl_proof_ssiz_len_seq_obj - 1 - btl_proof_ssiz_old_seq_obj );
	if ( c != 0 ) {
		i = btl_proof_ssiz_len_seq_obj - 1;
		btl_proof_XST_SEQ_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			btl_proof_XST_SEQ_OBJ(&b,i);
		}
		*ss = i;
		*cc = c;
	} else {
		*ss = 0;
		*cc = 0;
	}
}


btl_proof_NEXT_SEQ_OBJ( cc, ss, oc, os )
int *cc, *ss, oc, os;
{
	int c,i,b;
	c = oc - 1;
	if ( c != 0 ) {
		i = os - 1;
		btl_proof_XST_SEQ_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			btl_proof_XST_SEQ_OBJ(&b,i);
		}
		*ss = i;
		*cc = c;
	} else {
		*ss = 0;
		*cc = 0;
	}

}

btl_proof_OUTPUT_SEQ_OBJ( SS, pp )
int pp;
char * * SS;
{
	int e,c,o;
	BLK(2); PUT_STR("[ ");
	btl_proof_LEN_SEQ_OBJ(&c,pp);
	o = 1;
	while( o<=c ){
		btl_proof_VAL_SEQ_OBJ(&e,pp,o);
		_lib_PUT_ACT_TOK(SS,e);
		BLK(1);
		o++;
	}
	PUT_STR("]");
	NWL(1);
}

btl_proof_INPUT_SEQ_OBJ( bb, SS, pp, ll )
int *bb, pp, ll;
char * * SS;
{
	int m;
	btl_proof_FRE_MEM_SEQ_OBJ(&m);
        if ( ll <= m ) {
	        int n[250],b,i;
                _lib_GET_SET_ACT_TOK(ll,n,SS);
                i = 0;
                b = 1;
                while (i<ll && b) {
                        btl_proof_PSH_SEQ_OBJ(&b,pp,n[i]);
                        i++;
	        }
                *bb = b;
	}
        else {
                *bb = 0;
	}
}
