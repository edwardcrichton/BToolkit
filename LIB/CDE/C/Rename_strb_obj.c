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
#include "Rename_str_obj.h"
#include "basic_io.h"

void
INI_Rename_str_obj()
{
	Rename_ssiz_adr_str_obj = 0;
	Rename_ssiz_len_str_obj = 0;
	Rename_adr_str_obj[Rename_ssiz_adr_str_obj+1] = 0;
	Rename_ssiz_adr_str_obj = Rename_ssiz_adr_str_obj+1;
	Rename_adr_str_obj[Rename_ssiz_adr_str_obj+1] = Rename_str_objP2;
	Rename_ssiz_adr_str_obj = Rename_ssiz_adr_str_obj+1;
	Rename_len_str_obj[Rename_ssiz_len_str_obj+1] = 0;
	Rename_ssiz_len_str_obj = Rename_ssiz_len_str_obj+1;
	Rename_tot_str_obj = Rename_str_objP2;
	Rename_ssiz_old_str_obj = 0;
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
Rename_SAV_STR_OBJ()
{
	int i;
	char c;
        Rename_tot_str_obj = Rename_str_objP2-Rename_tot_str_obj;
	write_fm(Rename_tot_str_obj,1);
	write_fm(Rename_ssiz_adr_str_obj,1);
	write_fm(Rename_adr_str_obj[1],Rename_ssiz_adr_str_obj);
	write_fm(Rename_ssiz_len_str_obj,1);
	write_fm(Rename_len_str_obj[1],Rename_ssiz_len_str_obj);
	write_fm(Rename_ssiz_old_str_obj,1);
	write_fm(Rename_old_str_obj[1],Rename_ssiz_old_str_obj);
	write_fmc(Rename_array_str_obj[1],Rename_adr_str_obj[Rename_ssiz_adr_str_obj-1]);
	i = Rename_adr_str_obj[Rename_ssiz_adr_str_obj-1] % 4;
	c = 'w';
	while( i!=0 ){
		write_fmc(c,1);
		i = i-1;
	}
        Rename_tot_str_obj = Rename_str_objP2-Rename_tot_str_obj;
}

void
Rename_SAVN_STR_OBJ()
{
	int i, j, k;
	char c;
        Rename_tot_str_obj = Rename_str_objP2-Rename_tot_str_obj;

	Rename_tot_str_obj = htonl ( Rename_tot_str_obj );
        write_fm(Rename_tot_str_obj,1);
	Rename_tot_str_obj = ntohl ( Rename_tot_str_obj );

	Rename_ssiz_adr_str_obj = htonl ( Rename_ssiz_adr_str_obj );
	write_fm(Rename_ssiz_adr_str_obj,1);
	Rename_ssiz_adr_str_obj = ntohl ( Rename_ssiz_adr_str_obj );

	convert_arr_htonl(Rename_adr_str_obj,1,Rename_ssiz_adr_str_obj);
	write_fm(Rename_adr_str_obj[1],Rename_ssiz_adr_str_obj);
	convert_arr_ntohl(Rename_adr_str_obj,1,Rename_ssiz_adr_str_obj);

	Rename_ssiz_len_str_obj = htonl ( Rename_ssiz_len_str_obj );
	write_fm(Rename_ssiz_len_str_obj,1);
	Rename_ssiz_len_str_obj = ntohl ( Rename_ssiz_len_str_obj );

	convert_arr_htonl(Rename_len_str_obj,1,Rename_ssiz_len_str_obj);
	write_fm(Rename_len_str_obj[1],Rename_ssiz_len_str_obj);
	convert_arr_ntohl(Rename_len_str_obj,1,Rename_ssiz_len_str_obj);

	Rename_ssiz_old_str_obj = htonl ( Rename_ssiz_old_str_obj );
	write_fm(Rename_ssiz_old_str_obj,1);
	Rename_ssiz_old_str_obj = ntohl ( Rename_ssiz_old_str_obj );

	convert_arr_htonl(Rename_old_str_obj,1,Rename_ssiz_old_str_obj);
	write_fm(Rename_old_str_obj[1],Rename_ssiz_old_str_obj);
	convert_arr_ntohl(Rename_old_str_obj,1,Rename_ssiz_old_str_obj);

	write_fmc(Rename_array_str_obj[1],Rename_adr_str_obj[Rename_ssiz_adr_str_obj-1]);
	/* padding ? */
	i = Rename_adr_str_obj[Rename_ssiz_adr_str_obj-1] % 4;
	c = 'w';
	while( i!=0 ){
		write_fmc(c,1);
		i = i-1;
	}

        Rename_tot_str_obj = Rename_str_objP2-Rename_tot_str_obj;
}


#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

#define  read_fmc(a,b)   fread(&a,sizeof(char),b,dump_file)

void
Rename_RST_STR_OBJ()
{
	int i;
	char c;
	read_fm(Rename_tot_str_obj,1);
	read_fm(Rename_ssiz_adr_str_obj,1);
	read_fm(Rename_adr_str_obj[1],Rename_ssiz_adr_str_obj);
	read_fm(Rename_ssiz_len_str_obj,1);
	read_fm(Rename_len_str_obj[1],Rename_ssiz_len_str_obj);
	read_fm(Rename_ssiz_old_str_obj,1);
	read_fm(Rename_old_str_obj[1],Rename_ssiz_old_str_obj);
	read_fmc(Rename_array_str_obj[1],Rename_adr_str_obj[Rename_ssiz_adr_str_obj-1]);
	i = Rename_adr_str_obj[Rename_ssiz_adr_str_obj-1] % 4;
	while( i!=0 ){
		read_fmc(c,1);
		i = i-1;
	}
        Rename_tot_str_obj = Rename_str_objP2-Rename_tot_str_obj;
        Rename_adr_str_obj[Rename_ssiz_adr_str_obj] = Rename_str_objP2;
}

void
Rename_RSTN_STR_OBJ()
{
	int i, j, k;
	char c;
	read_fm(Rename_tot_str_obj,1);
	Rename_tot_str_obj = ntohl ( Rename_tot_str_obj );

	read_fm(Rename_ssiz_adr_str_obj,1);
	Rename_ssiz_adr_str_obj = ntohl ( Rename_ssiz_adr_str_obj );

	read_fm(Rename_adr_str_obj[1],Rename_ssiz_adr_str_obj);
	convert_arr_ntohl(Rename_adr_str_obj,1,Rename_ssiz_adr_str_obj);

	read_fm(Rename_ssiz_len_str_obj,1);
	Rename_ssiz_len_str_obj = ntohl ( Rename_ssiz_len_str_obj );

	read_fm(Rename_len_str_obj[1],Rename_ssiz_len_str_obj);
	convert_arr_ntohl(Rename_len_str_obj,1,Rename_ssiz_len_str_obj);

	read_fm(Rename_ssiz_old_str_obj,1);
	Rename_ssiz_old_str_obj = ntohl ( Rename_ssiz_old_str_obj );

	read_fm(Rename_old_str_obj[1],Rename_ssiz_old_str_obj);
	convert_arr_ntohl(Rename_old_str_obj,1,Rename_ssiz_old_str_obj);

	read_fmc(Rename_array_str_obj[1],Rename_adr_str_obj[Rename_ssiz_adr_str_obj-1]);
	/* padding ? */
	i = Rename_adr_str_obj[Rename_ssiz_adr_str_obj-1] % 4;
	while( i!=0 ){
		read_fmc(c,1);
		i = i-1;
	}

        Rename_tot_str_obj = Rename_str_objP2-Rename_tot_str_obj;
        Rename_adr_str_obj[Rename_ssiz_adr_str_obj] = Rename_str_objP2;
}


void
#ifdef _BT_ANSIC
Rename_CRE_STR_OBJ( int *bb, int *pp )
#else
Rename_CRE_STR_OBJ( bb, pp )
int *bb, *pp;
#endif
{
	int b;
	Rename_OBJ_FUL_STR_OBJ(&b);
	if( b==0 ){
		if( Rename_ssiz_old_str_obj==0 ){
			Rename_adr_str_obj[Rename_ssiz_len_str_obj+1] = 
			    Rename_adr_str_obj[Rename_ssiz_len_str_obj];
			Rename_adr_str_obj[Rename_ssiz_adr_str_obj+1] =
                                                             Rename_str_objP2;
			Rename_ssiz_adr_str_obj = Rename_ssiz_adr_str_obj+1;
			Rename_len_str_obj[Rename_ssiz_len_str_obj+1] = 0;
			Rename_ssiz_len_str_obj = Rename_ssiz_len_str_obj+1;
			*pp = Rename_ssiz_len_str_obj-1;
		} else {
			*pp=Rename_old_str_obj[Rename_ssiz_old_str_obj];
			Rename_ssiz_old_str_obj=Rename_ssiz_old_str_obj-1;
		}
		*bb=1;
	} else {
		*pp=0;
		*bb=0;
	}
}


void
#ifdef _BT_ANSIC
Rename_PSH_STR_OBJ( int *bb, int ss, int vv )
#else
Rename_PSH_STR_OBJ( bb, ss, vv )
int *bb, ss, vv;
#endif
{
	int e;
	Rename_MEM_FUL_STR_OBJ(&e);
	if( e==0 ){
		int search_res,y,k,r;
		r = 1;
		y = Rename_ssiz_adr_str_obj+1;
		search_res = 0;
		while( y!=r ){
			if( Rename_ssiz_adr_str_obj>2*ss-1 ){
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
				if( r<=2*(Rename_ssiz_adr_str_obj-ss) ){
					if( (r-1)%2 == 0 ){
						k =ss - (r/2);
					} else {
						k = ss + (r/2);
					}
				} else {
					k = Rename_ssiz_adr_str_obj+1-r;
				}
			}
			if( Rename_adr_str_obj[k]+Rename_len_str_obj[k]<
                                                     Rename_adr_str_obj[k+1] ){
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
				a = Rename_adr_str_obj[j];
				b = Rename_len_str_obj[j];
				{
					int k;
					k=a+b;
					while( k>a ){
						Rename_array_str_obj[k+1]=
                                                        Rename_array_str_obj[k];
						k=k-1;
					}
				}
				Rename_adr_str_obj[j] = Rename_adr_str_obj[j]+1;
				j = j-1;
			}
		} else {
			int j,a,b;
			j = search_res+1;
			while( j<=ss ){
				a = Rename_adr_str_obj[j];
				b = Rename_len_str_obj[j];
				{
					int k;
					k=a+1;
					while( k<=a+b ){
						Rename_array_str_obj[k-1]=
                                                         Rename_array_str_obj[k];
						k=k+1;
					}
				}
				Rename_adr_str_obj[j] = Rename_adr_str_obj[j]-1;
				j = j+1;
			}
		}
		Rename_len_str_obj[ss] = Rename_len_str_obj[ss]+1;
		Rename_tot_str_obj = Rename_tot_str_obj-1;
		Rename_array_str_obj[Rename_len_str_obj[ss]+Rename_adr_str_obj[ss]] = vv;
	}
	*bb=!e;
}


void
#ifdef _BT_ANSIC
Rename_EQL_LIT_STR_OBJ( int *bb, int tt, int *nn )
#else
Rename_EQL_LIT_STR_OBJ( bb, tt, nn )
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
	n = Rename_len_str_obj[tt];
	if( m==n ){
		i = 1;
		*bb = 1;
		while( i<=m ){
			v = ss[i-1];
			w = Rename_array_str_obj[i+Rename_adr_str_obj[tt]];
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
Rename_NEW_STR_OBJ( int *bb, int *pp, int *nn )
#else
Rename_NEW_STR_OBJ( bb, pp, nn )
int *bb, *pp, *nn;
#endif
{
	int b,i,p;
	char *ss;
	ss = (char *)nn;
	Rename_CRE_STR_OBJ(&b,&p);
	if( b==1 ){
		i=0;
		while( (ss[i]!='\0') && (b==1) ){
			Rename_PSH_STR_OBJ(&b,p,ss[i]);
			i=i+1;
		}
		if( b==1 ){
			*pp = p;
			*bb = 1;
		} else {
			Rename_KIL_STR_OBJ(p);
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
Rename_XTR_STR_OBJ( int *ss, int pp )
#else
Rename_XTR_STR_OBJ( ss, pp )
int *ss, pp;
#endif
{
	int i,v,s;
	char *t;
	t = (char *)ss;
	i = 0;
	s = Rename_len_str_obj[pp];
	while( i<s ){
		Rename_VAL_STR_OBJ(&v,pp,i+1);
		t[i] = v;
		i = i+1;
	}
	t[i] = '\0';
}


void
#ifdef _BT_ANSIC
Rename_APP_STR_OBJ( int *bb, int ss, int tt )
#else
Rename_APP_STR_OBJ( bb, ss, tt )
int *bb, ss, tt;
#endif
{
	int k,v,s,b,n;
	b=1;
	k=1;
	s=Rename_len_str_obj[tt];
	Rename_FRE_MEM_STR_OBJ(&n);
	if( s<=n ){
		while( k<=s ){
			Rename_VAL_STR_OBJ(&v,tt,k);
			Rename_PSH_STR_OBJ(&b,ss,v);
			k = k+1;
		}
		*bb=1;
	} else {
		*bb=0;
	}
}
