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
#include "Rename_Segment_io.h"

void
#ifdef _BT_ANSIC
Rename_PUT_SEG( int vv )
#else
Rename_PUT_SEG( vv )
int vv;
#endif
{
	int i;
	int *p;
	p = (int *)vv;
	i = 0;
	while(i < Rename_Segment_ioP1){
		printf("\n%d: %d",i,p[i]); 
		i = i+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_GET_SEG( int *rr )
#else
Rename_GET_SEG( rr )
int *rr;
#endif
{
	int i;
	i = 0;
	printf("\n");
	while(i < Rename_Segment_ioP1){
		printf("%d: ",i);
		Rename_GET_RAW(&rr[i],214748364);
		i = i+1;
	};
}


void
#ifdef _BT_ANSIC
Rename_GET_PROMPT_SEG( int *rr, int *ss )
#else
Rename_GET_PROMPT_SEG( rr, ss )
int *rr, *ss;
#endif
{
	int i;
	printf(ss);
	i = 0;
	printf("\n");
	while(i < Rename_Segment_ioP1){
		printf("%d: ",i);
		Rename_GET_RAW(&rr[i],214748364);
		i = i+1;
	};
}



#define mess_tok  while( c!='\n' ){ \
                    c = getchar(); \
                  }; \
                  printf("    Not a token (0..%d) - Re-Input: ",d)

#define init_tok  n = 0; \
                  while( (c<'0') || (c>'9') ){ \
                    mess_tok; \
                    c = getchar(); \
                  }


void
#ifdef _BT_ANSIC
Rename_GET_RAW( int *r, int d )
#else
Rename_GET_RAW( r, d )
int *r, d;
#endif
{
	register int c,m,k,l,n ;
	{
		k = d/10;
		l = d-10*(d/10);
		c = getchar();
		init_tok;
		while( (c>='0') && (c<='9') ){
			m = c-'0';
			if( n<k ){
				n = 10*n+m;
				c = getchar();
			} else if( n == k ){
				if( m<=l ){
					n = 10*n+m;
					c = getchar();
				} else{
					mess_tok;
					c = getchar();
					init_tok;
				};
			} else{
				mess_tok;
				c = getchar();
				init_tok;
			};
		};
		while( c!='\n' ){
			c = getchar();
		};
		*r = n;
	};
}


void
#ifdef _BT_ANSIC
Rename_GET_PROMPT_RAW( int *r, char *s, int d )
#else
Rename_GET_PROMPT_RAW( r, s, d )
int *r, d;
char *s;
#endif
{
	register int c,m,k,l,n ;
	{
		k = d/10;
		l = d-10*(d/10);
		printf(s);
		c = getchar();
		init_tok;
		while( (c>='0') && (c<='9') ){
			m = c-'0';
			if( n<k ){
				n = 10*n+m;
				c = getchar();
			} else if( n == k ){
				if( m<=l ){
					n = 10*n+m;
					c = getchar();
				} else{
					mess_tok;
					c = getchar();
					init_tok;
				};
			} else{
				mess_tok;
				c = getchar();
				init_tok;
			};
		};
		while( c!='\n' ){
			c = getchar();
		};
		*r = n;
	};
}

