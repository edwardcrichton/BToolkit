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
#include "BitSeq_TYPE.h"

#include "Byt_TYPE.h"

#include "basic_io.h"

#define mess_bits while( c!='\n' ){ \
                    c = getchar(); \
                  }; \
                  printf("    Not a Bit String - Re-input: ")

#define init_bits n = 0; \
                  while( (c<'0') || (c>'1') ){ \
                    mess_bits; \
                    c = getchar(); \
                  }

void
#ifdef _BT_ANSIC
BSGET( int *r, char *s )
#else
BSGET( r, s )
int *r;
char *s;
#endif
{
        register int c;
        unsigned int k,l,m,n ;
        {
                k = 2147483647;
                l = 1;
                printf(s);
                c = getchar();
                init_bits;
                while( (c>='0') && (c<='1') ){
                        m = c-'0';
                        if( n<k ){
                                n = 2*n+m;
                                c = getchar();
                        } else if( n == k ){
                                if( m<=l ){
                                        n = 2*n+m;
                                        c = getchar();
                                } else{
                                        mess_bits;
                                        c = getchar();
                                        init_bits;
                                };
                        } else{
                                mess_bits;
                                c = getchar();
                                init_bits;
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
BSPUT( int s )
#else
BSPUT( s )
int s;
#endif
{
        int i;
        i = 32;
        while( i>0 ){
                printf("%d",(((s>>(i-1))%2)+2)%2);
                i = i-1;
        };
}

