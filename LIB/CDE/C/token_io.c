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
#ifndef _NO_PROTO

#include "token_io.h"

/* ANSIC header */
_GET_ACT_TOK( int * t, char * * T )
/* end ANSIC header */

/* non-ANSIC header */
_GET_ACT_TOK( t, T )
int * t;
char * * T;
/* end non-ANSIC header */
{
  int n;
  int i;
  int done = 0;
  if ( strcmp ( T [ 0 ], "" ) != 0 )  { 
      GET_NAT ( &n );
  }
  else {
    while( ! done ) {
      i = 1;
      printf( "\n" );
      while( T [ i ] [ 0 ] != '_' ){
        BLK ( 2 ); PUT_NAT_PAD ( i, 4 ); PUT_STR ( T [ i ] ); NWL ( 1 );
        i++;
      }
      BLK ( 4 ); PUT_STR ( "Enumerated element number (1.." ); PUT_NAT ( i - 1 );
      PUT_STR ( "): "); FLSH ();
      GET_NAT ( &n );
      if   ( n >= 1 && n <= i - 1 ) { done = 1; }
      else                          { BLK(15); PUT_STR (" Bad input!" ); }
    }
  }
  *t = n; 
}
#endif
