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
#include "Rename_Narr.h"

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
Rename_SAV_NARR()
{
	write_fm(Rename_Narray[1],Rename_NarrP2);
}

void
Rename_SAVN_NARR()
{
        int j, k;
	convert_arr_htonl(Rename_Narray,1,Rename_NarrP2);
	write_fm(Rename_Narray[1],Rename_NarrP2);
	convert_arr_ntohl(Rename_Narray,1,Rename_NarrP2);
}


#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

void
Rename_RST_NARR()
{
	read_fm(Rename_Narray[1],Rename_NarrP2);
}

void
Rename_RSTN_NARR()
{
        int j, k;
	read_fm(Rename_Narray[1],Rename_NarrP2);
	convert_arr_ntohl(Rename_Narray,1,Rename_NarrP2);
}


void
#ifdef _BT_ANSIC
Rename_SWP_NARR( int ii, int jj )
#else
Rename_SWP_NARR( ii, jj )
int ii, jj;
#endif
{
	int i;
	i=Rename_Narray[ii];
	Rename_Narray[ii]=Rename_Narray[jj];
	Rename_Narray[jj]=i;
}


void
#ifdef _BT_ANSIC
Rename_MAX_IDX_NARR( int *vv, int ii, int jj )
#else
Rename_MAX_IDX_NARR( vv, ii, jj )
int* vv;
int ii, jj;
#endif
{
	int x,t,k;
	x=ii;
	t=0;
	k=ii;
	while( x<=jj ){
		if( Rename_Narray[x]>=t ){
			t=Rename_Narray[x];
			k=x;
		};
		x=x+1;
	};
	*(vv)=k;
}


void
#ifdef _BT_ANSIC
Rename_MIN_IDX_NARR( int *vv, int ii, int jj )
#else
Rename_MIN_IDX_NARR( vv, ii, jj )
int* vv;
int ii, jj;
#endif
{
	int x,t,k;
	x=ii;
	k=ii;
	t=Rename_NarrP1;
	while( x<=jj ){
		if( Rename_Narray[x]<=t ){
			t=Rename_Narray[x];
			k=x;
		};
		x=x+1;
	};
	*(vv)=k;
}


void
#ifdef _BT_ANSIC
Rename_SCH_LO_EQL_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_LO_EQL_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=jj;
	y=kk+1;
	while( y!=r ){
		if( Rename_Narray[r] == vv ){
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
Rename_SCH_LO_NEQ_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_LO_NEQ_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=jj;
	y=kk+1;
	while( y!=r ){
		if( Rename_Narray[r] != vv ){
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
Rename_SCH_LO_GEQ_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_LO_GEQ_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=jj;
	y=kk+1;
	while( y!=r ){
		if( Rename_Narray[r] >= vv ){
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
Rename_SCH_LO_GTR_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_LO_GTR_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=jj;
	y=kk+1;
	while( y!=r ){
		if( Rename_Narray[r] > vv ){
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
Rename_SCH_LO_LEQ_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_LO_LEQ_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=jj;
	y=kk+1;
	while( y!=r ){
		if( Rename_Narray[r] <= vv ){
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
Rename_SCH_LO_SMR_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_LO_SMR_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=jj;
	y=kk+1;
	while( y!=r ){
		if( Rename_Narray[r] < vv ){
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
Rename_SCH_HI_EQL_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_HI_EQL_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=kk;
	y=jj-1;
	while( y!=r ){
		if( Rename_Narray[r] == vv ){
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
Rename_SCH_HI_NEQ_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_HI_NEQ_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=kk;
	y=jj-1;
	while( y!=r ){
		if( Rename_Narray[r] != vv ){
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
Rename_SCH_HI_GEQ_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_HI_GEQ_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=kk;
	y=jj-1;
	while( y!=r ){
		if( Rename_Narray[r] >= vv ){
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
Rename_SCH_HI_GTR_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_HI_GTR_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=kk;
	y=jj-1;
	while( y!=r ){
		if( Rename_Narray[r] > vv ){
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
Rename_SCH_HI_LEQ_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_HI_LEQ_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=kk;
	y=jj-1;
	while( y!=r ){
		if( Rename_Narray[r] <= vv ){
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
Rename_SCH_HI_SMR_NARR( int *bb, int *ii, int jj, int kk, int vv )
#else
Rename_SCH_HI_SMR_NARR( bb, ii, jj, kk, vv )
int *bb;
int *ii;
int jj, kk, vv;
#endif
{
	int r,y;
	r=kk;
	y=jj-1;
	while( y!=r ){
		if( Rename_Narray[r] < vv ){
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
Rename_SRT_ASC_NARR( int ii, int jj )
#else
Rename_SRT_ASC_NARR( ii, jj )
int ii, jj;
#endif
{
	int i,v,b,r;
	i=ii;
	while( i<jj ){
		Rename_VAL_NARR(&v,i+1);
		Rename_SCH_LO_GTR_NARR(&b,&r,ii,i,v);
		if( b==1 ){
			Rename_RHT_NARR(r,i,1);
			Rename_STO_NARR(r,v);
		};
		i=i+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_SRT_DSC_NARR( int ii, int jj )
#else
Rename_SRT_DSC_NARR( ii, jj )
int ii, jj;
#endif
{
	int i,v,b,r;
	i=ii;
	while( i<jj ){
		Rename_VAL_NARR(&v,i+1);
		Rename_SCH_LO_SMR_NARR(&b,&r,ii,i,v);
		if( b==1 ){
			Rename_RHT_NARR(r,i,1);
			Rename_STO_NARR(r,v);
		};
		i=i+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_REV_NARR( int ii, int jj )
#else
Rename_REV_NARR( ii, jj )
int ii, jj;
#endif
{
	int i,j;
	i=ii;
	j=jj;
	while( i<j ){
		Rename_SWP_NARR(i,j);
		i=i+1;
		j=j-1;
	};
}


void
#ifdef _BT_ANSIC
Rename_RHT_NARR( int ii, int jj, int nn )
#else
Rename_RHT_NARR( ii, jj, nn )
int ii, jj, nn;
#endif
{
	int k,n;
	n=jj-ii+1;
	k=0;
	while( k<n ){
		if( jj+nn-k<=Rename_NarrP2 ){
			Rename_Narray[jj+nn-k]=Rename_Narray[jj-k];
		}
		k=k+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_LFT_NARR( int ii, int jj, int nn )
#else
Rename_LFT_NARR( ii, jj, nn )
int ii, jj, nn;
#endif
{
	int k,n;
	n=jj-ii+1;
	k=0;
	while( k<n ){
		if( ii-nn+k>=1 ){
			Rename_Narray[ii-nn+k]=Rename_Narray[ii+k];
		}
		k=k+1;
	};
}

