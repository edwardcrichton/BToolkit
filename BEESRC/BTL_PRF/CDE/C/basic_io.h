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
#include <stdio.h>

#define INI_basic_io()       {}

#define GET_NAT(r)           GET_NBR ( r, 2147483646 )

#define GET_PROMPT_NAT(r,s)  GET_PROMPT_NBR ( r, s, 2147483646 )

#define PUT_NBR_PAD(n,p)     PUT_NAT_PAD ( n, p )

#define _lib_GET_TOK(t)           GET_NAT ( t )

#define _lib_GET_PROMPT_TOK(t,s)  GET_PROMPT_NAT ( t, s )

#define _lib_PUT_TOK(t)           PUT_NAT ( t )

#define PUT_STR_PAD(s,p)     PUT_STR ( s ); \
                             BLK ( p - strlen ( ( char * ) s ) )

#define PUT_BOOL_PAD(b,p)    PUT_BOOL(b); \
                             if   ( b ) BLK ( p - 4 ); \
                             else       BLK ( p - 5 )


#ifndef _NO_PROTO


#define PUT_NAT(n)           printf ( "%d", n )

#define PUT_NBR(n)           PUT_NAT ( n )

#define PUT_CHR(c)           putchar ( c )

#define PUT_STR(s)           puts ( ( char * ) s )

#define PUT_BOOL(b)          if   ( b )  PUT_STR ( "TRUE" ); \
                             else        PUT_STR ( "FALSE" )

#define FLSH()               fflush( stdout)

#define GET_STR(s)           gets ( ( char * ) s )

#define GET_PROMPT_STR(s,t)  PUT_STR ( ( char * ) t ); gets ( ( char * ) s )

#define _lib_PUT_ACT_TOK(T,t) \
  if ( T [ 0 ] [ 0 ] == '\0' ) { \
    PUT_STR ( T [ t ] ); \
  } \
  else { \
    if ( ( strcmp ( T [ 0 ], "SCALAR" ) != 0 )        && \
         ( strcmp ( T [ 0 ], "0..2147483646" ) != 0 )    ) { \
      PUT_STR( T [ 0 ] ); PUT_CHR ('.'); \
    } \
    PUT_NAT ( t ); \
  }

#define _lib_GET_PROMPT_ACT_TOK(t,T,s) \
  PUT_STR ( s ); \
  _lib_GET_ACT_TOK (t, T )

#else

extern void PUT_NAT_M ();
extern void PUT_STR_M ();
extern void PUT_CHR_M ();
extern void PUT_BTS_M ();
extern void PUT_BOOL_M ();
extern void GET_PROMPT_NBR_M ();
extern void GET_PROMPT_STR_M ();
extern void GET_PROMPT_CHR_M ();
extern void GET_PROMPT_BTS_M ();
extern void GET_PROMPT_BOOL_M ();
extern void PUT_ACT_TOK_M ();
extern void GET_ACT_TOK_M ();
extern void GET_SET_ACT_TOK_M ();
extern void GET_SET_TOK_M ();

#define PUT_STR(s)           PUT_STR_M ( s )

#define PUT_CHR(c)           PUT_CHR_M ( c )

#define PUT_NAT(n)           PUT_NAT_M ( n )

#define PUT_NBR(n)           PUT_NAT ( n )

#define PUT_BOOL(b)          PUT_BOOL_M ( b )

#define FLSH()               ;

#define GET_STR(s)           GET_PROMPT_STR ( s, "        Input string:     " )


#define _lib_PUT_ACT_TOK(T,t) \
  if ( T [ 0 ][ 0 ] == '\0' ) \
    PUT_ACT_TOK_M ( T, t ); \
  else \
    _lib_PUT_TOK ( t )

#define _lib_GET_ACT_TOK(t,T) \
  if ( T [ 0 ][ 0 ] == '\0' ) \
    GET_ACT_TOK_M ( T, t, "      Select token:     " ); \
  else \
    _lib_GET_TOK ( t )

#define _lib_GET_PROMPT_ACT_TOK(t,T,s) \
  if ( T [ 0 ][ 0 ] == '\0' ) \
    GET_ACT_TOK_M ( T, t, s ); \
  else \
    _lib_GET_PROMPT_TOK ( t, s )

#define _lib_GET_SET_ACT_TOK(m,t,T) \
  if ( T [ 0 ][ 0 ] == '\0' ) \
    GET_SET_ACT_TOK_M ( T, m, t ); \
  else \
    GET_SET_TOK_M ( T, m, t )

#endif

