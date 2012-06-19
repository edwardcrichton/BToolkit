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
#include "Rename_set_obj.h"
#include "Rename_set_ctx.h"
#include "basic_io.h"

void
INI_Rename_set_obj()
{
	Rename_ssiz_adr_set_obj = 0;
	Rename_ssiz_len_set_obj = 0;
	Rename_adr_set_obj[Rename_ssiz_adr_set_obj+1] = 0;
	Rename_ssiz_adr_set_obj = Rename_ssiz_adr_set_obj+1;
	Rename_adr_set_obj[Rename_ssiz_adr_set_obj+1] = Rename_set_objP3;
	Rename_ssiz_adr_set_obj = Rename_ssiz_adr_set_obj+1;
	Rename_len_set_obj[Rename_ssiz_len_set_obj+1] = 0;
	Rename_ssiz_len_set_obj = Rename_ssiz_len_set_obj+1;
	Rename_tot_set_obj = Rename_set_objP3;
	Rename_ssiz_old_set_obj = 0;
}


void
Rename_INI_SET_OBJ()
{
	Rename_ssiz_adr_set_obj = 0;
	Rename_ssiz_len_set_obj = 0;
	Rename_adr_set_obj[Rename_ssiz_adr_set_obj+1] = 0;
	Rename_ssiz_adr_set_obj = Rename_ssiz_adr_set_obj+1;
	Rename_adr_set_obj[Rename_ssiz_adr_set_obj+1] = Rename_set_objP3;
	Rename_ssiz_adr_set_obj = Rename_ssiz_adr_set_obj+1;
	Rename_len_set_obj[Rename_ssiz_len_set_obj+1] = 0;
	Rename_ssiz_len_set_obj = Rename_ssiz_len_set_obj+1;
	Rename_tot_set_obj = Rename_set_objP3;
	Rename_ssiz_old_set_obj = 0;
}


void
#ifdef _BT_ANSIC
Rename_XST_SET_OBJ( int *bb, int pp )
#else
Rename_XST_SET_OBJ( bb, pp )
int *bb, pp;
#endif
{
	if ( pp > 0 && pp < Rename_ssiz_len_set_obj ) {
		int i;
		i = Rename_ssiz_old_set_obj;
		*bb = 1;
		while ( i != 0 ) {
			if ( pp != Rename_old_set_obj[i] ) {
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
Rename_SAV_SET_OBJ()
{
        Rename_tot_set_obj = Rename_set_objP3-Rename_tot_set_obj;
	write_fm(Rename_tot_set_obj,1);
	write_fm(Rename_ssiz_adr_set_obj,1);
	write_fm(Rename_adr_set_obj[1],Rename_ssiz_adr_set_obj);
	write_fm(Rename_ssiz_len_set_obj,1);
	write_fm(Rename_len_set_obj[1],Rename_ssiz_len_set_obj);
	write_fm(Rename_ssiz_old_set_obj,1);
	write_fm(Rename_old_set_obj[1],Rename_ssiz_old_set_obj);
	write_fm(Rename_array_set_obj[1],Rename_adr_set_obj[Rename_ssiz_adr_set_obj-1]);
        Rename_tot_set_obj = Rename_set_objP3-Rename_tot_set_obj;
}

void
Rename_SAVN_SET_OBJ()
{
        int j, k;
        Rename_tot_set_obj = Rename_set_objP3-Rename_tot_set_obj;

	Rename_tot_set_obj = htonl ( Rename_tot_set_obj );
        write_fm(Rename_tot_set_obj,1);
	Rename_tot_set_obj = ntohl ( Rename_tot_set_obj );

	Rename_ssiz_adr_set_obj = htonl ( Rename_ssiz_adr_set_obj );
	write_fm(Rename_ssiz_adr_set_obj,1);
	Rename_ssiz_adr_set_obj = ntohl ( Rename_ssiz_adr_set_obj );

	convert_arr_htonl(Rename_adr_set_obj,1,Rename_ssiz_adr_set_obj);
	write_fm(Rename_adr_set_obj[1],Rename_ssiz_adr_set_obj);
	convert_arr_ntohl(Rename_adr_set_obj,1,Rename_ssiz_adr_set_obj);

	Rename_ssiz_len_set_obj = htonl ( Rename_ssiz_len_set_obj );
	write_fm(Rename_ssiz_len_set_obj,1);
	Rename_ssiz_len_set_obj = ntohl ( Rename_ssiz_len_set_obj );

	convert_arr_htonl(Rename_len_set_obj,1,Rename_ssiz_len_set_obj);
	write_fm(Rename_len_set_obj[1],Rename_ssiz_len_set_obj);
	convert_arr_ntohl(Rename_len_set_obj,1,Rename_ssiz_len_set_obj);

	Rename_ssiz_old_set_obj = htonl ( Rename_ssiz_old_set_obj );
	write_fm(Rename_ssiz_old_set_obj,1);
	Rename_ssiz_old_set_obj = ntohl ( Rename_ssiz_old_set_obj );

	convert_arr_htonl(Rename_old_set_obj,1,Rename_ssiz_old_set_obj);
	write_fm(Rename_old_set_obj[1],Rename_ssiz_old_set_obj);
	convert_arr_ntohl(Rename_old_set_obj,1,Rename_ssiz_old_set_obj);

	convert_arr_htonl(Rename_array_set_obj,1,Rename_adr_set_obj[Rename_ssiz_adr_set_obj-1]);
	write_fm(Rename_array_set_obj[1],Rename_adr_set_obj[Rename_ssiz_adr_set_obj-1]);
	convert_arr_ntohl(Rename_array_set_obj,1,Rename_adr_set_obj[Rename_ssiz_adr_set_obj-1]);

        Rename_tot_set_obj = Rename_set_objP3-Rename_tot_set_obj;
}


#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

void
Rename_RST_SET_OBJ()
{
	read_fm(Rename_tot_set_obj,1);
	read_fm(Rename_ssiz_adr_set_obj,1);
	read_fm(Rename_adr_set_obj[1],Rename_ssiz_adr_set_obj);
	read_fm(Rename_ssiz_len_set_obj,1);
	read_fm(Rename_len_set_obj[1],Rename_ssiz_len_set_obj);
	read_fm(Rename_ssiz_old_set_obj,1);
	read_fm(Rename_old_set_obj[1],Rename_ssiz_old_set_obj);
	read_fm(Rename_array_set_obj[1],Rename_adr_set_obj[Rename_ssiz_adr_set_obj-1]);
        Rename_tot_set_obj = Rename_set_objP3-Rename_tot_set_obj;
        Rename_adr_set_obj[Rename_ssiz_adr_set_obj] = Rename_set_objP3;
}

void
Rename_RSTN_SET_OBJ()
{
        int j, k;
	read_fm(Rename_tot_set_obj,1);
        Rename_tot_set_obj = ntohl ( Rename_tot_set_obj );

	read_fm(Rename_ssiz_adr_set_obj,1);
        Rename_ssiz_adr_set_obj = ntohl ( Rename_ssiz_adr_set_obj );

	read_fm(Rename_adr_set_obj[1],Rename_ssiz_adr_set_obj);
	convert_arr_ntohl(Rename_adr_set_obj,1,Rename_ssiz_adr_set_obj);

	read_fm(Rename_ssiz_len_set_obj,1);
        Rename_ssiz_len_set_obj = ntohl ( Rename_ssiz_len_set_obj );

	read_fm(Rename_len_set_obj[1],Rename_ssiz_len_set_obj);
	convert_arr_ntohl(Rename_len_set_obj,1,Rename_ssiz_len_set_obj);

	read_fm(Rename_ssiz_old_set_obj,1);
        Rename_ssiz_old_set_obj = ntohl ( Rename_ssiz_old_set_obj );

	read_fm(Rename_old_set_obj[1],Rename_ssiz_old_set_obj);
	convert_arr_ntohl(Rename_old_set_obj,1,Rename_ssiz_old_set_obj);

	read_fm(Rename_array_set_obj[1],Rename_adr_set_obj[Rename_ssiz_adr_set_obj-1]);
	convert_arr_ntohl(Rename_array_set_obj,1,Rename_adr_set_obj[Rename_ssiz_adr_set_obj-1]);

        Rename_tot_set_obj = Rename_set_objP3-Rename_tot_set_obj;
        Rename_adr_set_obj[Rename_ssiz_adr_set_obj] = Rename_set_objP3;
}


void
#ifdef _BT_ANSIC
Rename_CRE_SET_OBJ( int *bb, int *pp )
#else
Rename_CRE_SET_OBJ( bb, pp )
int *bb, *pp;
#endif
{
	int b;
	Rename_OBJ_FUL_SET_OBJ(&b);
	if( b==0 ){
		if( Rename_ssiz_old_set_obj==0 ){
			Rename_adr_set_obj[Rename_ssiz_len_set_obj+1] = 
			    Rename_adr_set_obj[Rename_ssiz_len_set_obj];
			Rename_adr_set_obj[Rename_ssiz_adr_set_obj+1]=
                                                             Rename_set_objP3;
			Rename_ssiz_adr_set_obj = Rename_ssiz_adr_set_obj+1;
			Rename_len_set_obj[Rename_ssiz_len_set_obj+1] = 0;
			Rename_ssiz_len_set_obj = Rename_ssiz_len_set_obj+1;
			*pp = Rename_ssiz_len_set_obj-1;
		} else {
			*pp=Rename_old_set_obj[Rename_ssiz_old_set_obj];
			Rename_ssiz_old_set_obj=Rename_ssiz_old_set_obj-1;
		}
		*bb=1;
	} else {
		*pp=0;
		*bb=0;
	}
}


static void
#ifdef _BT_ANSIC
Rename_PSH_SET_OBJ( int *bb, int ss, int vv )
#else
Rename_PSH_SET_OBJ( bb, ss, vv )
int *bb, ss, vv;
#endif
{
	int e;
	Rename_MEM_FUL_SET_OBJ(&e);
	if( e==0 ){
		int search_res,y,k,r;
		r = 1;
		y = Rename_ssiz_adr_set_obj+1;
		search_res = 0;
		while( y!=r ){
			if( Rename_ssiz_adr_set_obj>2*ss-1 ){
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
				if( r<=2*(Rename_ssiz_adr_set_obj-ss) ){
					if( (r-1)%2 == 0 ){
						k =ss - (r/2);
					} else {
						k = ss + (r/2);
					}
				} else {
					k = Rename_ssiz_adr_set_obj+1-r;
				}
			}
			if( Rename_adr_set_obj[k]+Rename_len_set_obj[k]<
                                                     Rename_adr_set_obj[k+1] ){
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
				a = Rename_adr_set_obj[j];
				b = Rename_len_set_obj[j];
				{
					int k;
					k=a+b;
					while( k>a ){
						Rename_array_set_obj[k+1]=
                                                        Rename_array_set_obj[k];
						k=k-1;
					}
				}
				Rename_adr_set_obj[j] = Rename_adr_set_obj[j]+1;
				j = j-1;
			}
		} else {
			int j,a,b;
			j = search_res+1;
			while( j<=ss ){
				a = Rename_adr_set_obj[j];
				b = Rename_len_set_obj[j];
				{
					int k;
					k=a+1;
					while( k<=a+b ){
						Rename_array_set_obj[k-1]=
                                                        Rename_array_set_obj[k];
						k=k+1;
					}
				}
				Rename_adr_set_obj[j] = Rename_adr_set_obj[j]-1;
				j = j+1;
			}
		}
		Rename_len_set_obj[ss] = Rename_len_set_obj[ss]+1;
		Rename_tot_set_obj = Rename_tot_set_obj-1;
		Rename_array_set_obj[Rename_len_set_obj[ss]+Rename_adr_set_obj[ss]] = vv;
	}
	*bb=!e;
}


static void
#ifdef _BT_ANSIC
Rename_SRC_HIH_EQL_SET_OBJ( int *bb, int *ii, int ss, int vv )
#else
Rename_SRC_HIH_EQL_SET_OBJ( bb, ii, ss, vv )
int *bb, *ii, ss, vv;
#endif
{
	int r,y,w;
	Rename_LEN_SET_OBJ(&r,ss);
	y=0;
	while( y!=r ){
		Rename_VAL_SET_OBJ(&w,ss,r)
		    if( w == vv ){
			y=r;
		} else {
			r=r-1;
		}
	}
	*(bb)=((r!=0)!=0);
	*(ii)=r;
}


static void
#ifdef _BT_ANSIC
Rename_DEL_SET_OBJ( int tt, int ii )
#else
Rename_DEL_SET_OBJ( tt, ii )
int tt, ii;
#endif
{
	int l,v;
	Rename_LEN_SET_OBJ(&l,tt);
	if( ii!=l ){
		Rename_VAL_SET_OBJ(&v,tt,l);
		Rename_STO_SET_OBJ(tt,ii,v);
	}
	Rename_POP_SET_OBJ(tt);
}


void
#ifdef _BT_ANSIC
Rename_UNION_SET_OBJ( int *bb, int tt, int ss )
#else
Rename_UNION_SET_OBJ( bb, tt, ss )
int *bb, tt, ss;
#endif
{
	int b,j,v,r,c,n;
	Rename_LEN_SET_OBJ(&j,ss);
	n = 0;
	c = 1;
	while( (j!=0) && (c==1) ){
		Rename_VAL_SET_OBJ(&v,ss,j);
		Rename_SRC_HIH_EQL_SET_OBJ(&b,&r,tt,v);
		if( b==0 ){
			Rename_PSH_SET_OBJ(&c,tt,v);
			if( c==1 ){
				n = n+1;
			}
		}
		j=j-1;
	}
	if( c==0 ){
		while( n>0 ){
			Rename_POP_SET_OBJ(tt);
			n = n-1;
		}
	}
	*bb = c;
}


void
#ifdef _BT_ANSIC
Rename_DIFF_SET_OBJ( int tt, int ss )
#else
Rename_DIFF_SET_OBJ( tt, ss )
int tt, ss;
#endif
{
	int b,j,v,r;
	Rename_LEN_SET_OBJ(&j,ss);
	while( j!=0 ){
		Rename_VAL_SET_OBJ(&v,ss,j);
		Rename_SRC_HIH_EQL_SET_OBJ(&b,&r,tt,v);
		if( b==1 ){
			Rename_DEL_SET_OBJ(tt,r);
		}
		j=j-1;
	}
}


void
#ifdef _BT_ANSIC
Rename_INTER_SET_OBJ( int tt, int ss )
#else
Rename_INTER_SET_OBJ( tt, ss )
int tt, ss;
#endif
{
	int j,l,v,r,b;
	j=1;
	Rename_LEN_SET_OBJ(&l,tt);
	while( j!=l+1 ){
		Rename_VAL_SET_OBJ(&v,tt,j);
		Rename_SRC_HIH_EQL_SET_OBJ(&b,&r,ss,v);
		if( b==0 ){
			Rename_DEL_SET_OBJ(tt,j);
		} else {
			j=j+1;
		}
		Rename_LEN_SET_OBJ(&l,tt);
	}
}


void
#ifdef _BT_ANSIC
Rename_INCL_SET_OBJ( int *bb, int tt, int ss )
#else
Rename_INCL_SET_OBJ( bb, tt, ss )
int *bb, tt, ss;
#endif
{
	int j,r,v,c;
	*bb=1;
	Rename_LEN_SET_OBJ(&j,tt);
	while( j!=0 ){
		Rename_VAL_SET_OBJ(&v,tt,j);
		Rename_SRC_HIH_EQL_SET_OBJ(&c,&r,ss,v);
		if( c==1 ){
			j=j-1;
		} else {
			*bb=0;
			j=0;
		}
	}
}


void
#ifdef _BT_ANSIC
Rename_MBR_SET_OBJ( int *bb, int ss, int vv )
#else
Rename_MBR_SET_OBJ( bb, ss, vv )
int *bb, ss, vv;
#endif
{
	int r,b;
	Rename_SRC_HIH_EQL_SET_OBJ(&b,&r,ss,vv);
	*bb=b;
}


void
#ifdef _BT_ANSIC
Rename_ENT_SET_OBJ( int *bb, int ss, int vv )
#else
Rename_ENT_SET_OBJ( bb, ss, vv )
int *bb, ss, vv;
#endif
{
	int r,b;
	Rename_SRC_HIH_EQL_SET_OBJ(&b,&r,ss,vv);
	if( b==0 ){
		Rename_PSH_SET_OBJ(bb,ss,vv);
	} else {
          *bb=1;
	}
}


void
#ifdef _BT_ANSIC
Rename_RMV_SET_OBJ( int ss, int vv )
#else
Rename_RMV_SET_OBJ( ss, vv )
int ss, vv;
#endif
{
	int r,b;
	Rename_SRC_HIH_EQL_SET_OBJ(&b,&r,ss,vv);
	if( b==1 ){
		Rename_DEL_SET_OBJ(ss,r);
	}
}


static void
#ifdef _BT_ANSIC
Rename_APP_SET_OBJ( int *bb, int ss, int tt )
#else
Rename_APP_SET_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int k,v,s,b,n;
	k=1;
	s = Rename_len_set_obj[tt];
	Rename_FRE_MEM_SET_OBJ(&n);
	if( s<=n ){
		while( k<=s ){
			Rename_VAL_SET_OBJ(&v,tt,k);
			Rename_PSH_SET_OBJ(&b,ss,v);
			k = k+1;
		}
		*bb=1;
	} else {
		*bb=0;
	}
}


void
#ifdef _BT_ANSIC
Rename_CPY_SET_OBJ( int *bb, int ss, int tt )
#else
Rename_CPY_SET_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int s,t,n;
	if( ss!=tt ){
		s = Rename_len_set_obj[ss];
		t = Rename_len_set_obj[tt];
		Rename_FRE_MEM_SET_OBJ(&n);
		if( s<=n+t ){
			Rename_CLR_SET_OBJ(tt);
			Rename_APP_SET_OBJ(&(*bb),tt,ss);
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
Rename_FIRST_SET_OBJ( int *cc, int *ss )
#else
Rename_FIRST_SET_OBJ( cc, ss )
int *cc, *ss;
#endif
{
	int c,i,b;
	c = ( Rename_ssiz_len_set_obj - 1 - Rename_ssiz_old_set_obj );
	if ( c != 0 ) {
		i = Rename_ssiz_len_set_obj - 1;
		Rename_XST_SET_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			Rename_XST_SET_OBJ(&b,i);
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
Rename_NEXT_SET_OBJ( int *cc, int *ss, int oc, int os )
#else
Rename_NEXT_SET_OBJ( cc, ss, oc, os )
int *cc, *ss;
#endif
{
	int c,i,b;
	c = oc - 1;
	if ( c != 0 ) {
		i = os - 1;
		Rename_XST_SET_OBJ(&b,i);
		while ( b != 1 && i != 0 ) {
			i = i - 1;
			Rename_XST_SET_OBJ(&b,i);
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
Rename_OUTPUT_SET_OBJ( char * * SS, int pp )
#else
Rename_OUTPUT_SET_OBJ( SS, pp )
int pp;
char * * SS;
#endif
{
	int e,c,o;
	BLK(2); PUT_STR("{ ");
	Rename_LEN_SET_OBJ(&c,pp);
	o = 1;
	while( o<=c ){
		Rename_VAL_SET_OBJ(&e,pp,o);
		_lib_PUT_ACT_TOK(SS,e);
		BLK(1);
		o++;
	}
	PUT_STR("}");
	NWL(1);
}

void
#ifdef _BT_ANSIC
Rename_INPUT_SET_OBJ( int *bb, char * * SS, int pp, int ll )
#else
Rename_INPUT_SET_OBJ( bb, SS, pp, ll )
int *bb, pp, ll;
char * * SS;
#endif
{
	int m;
	Rename_FRE_MEM_SET_OBJ(&m);
        if ( ll <= m ) {
	        int n[250],b,i;
                _lib_GET_SET_ACT_TOK(ll,n,SS);
                i = 0;
                b = 1;
                while (i<ll && b) {
                        Rename_ENT_SET_OBJ(&b,pp,n[i]);
                        i++;
	        }
                *bb = b;
	}
        else {
                *bb = 0;
	}
}
