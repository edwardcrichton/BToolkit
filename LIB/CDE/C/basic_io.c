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
#include "basic_io.h"

#ifndef _BT_Motif

#define mess_bool   while( c!='\n' ){ \
                      c = getchar(); \
                    } \
                    fprintf(_b, "    Not a boolean (TRUE/FALSE) - re-input: ")


#define mess_bits while( c!='\n' ){ \
                    c = getchar(); \
                  } \
                  fprintf(_b, "    Not a bit string (0/1's) - re-input: ")

#define init_bits n = 0; \
                  while( (c<'0') || (c>'1') ){ \
                    mess_bits; \
                    c = getchar(); \
                  }



#define mess_nbr  while( c!='\n' ){ \
                    c = getchar(); \
                  } \
                  fprintf(_b, "    Not a number (0..%d) - re-input: ",d)

#define init_nbr  n = 0; \
                  while( (c<'0') || (c>'9') ){ \
                    mess_nbr; \
                    c = getchar(); \
                  }

#define mess_int(l,u) \
                  while ( c != '\n' ) { c = getchar(); } \
                  fprintf ( _b, "    Not an integer in the range " ); \
                  if ( l >= 0 ) fprintf ( _b, "+%d", l ); else fprintf ( _b, "%d", l ); \
                  fprintf ( _b, " to " ); \
                  if ( u >= 0 ) fprintf ( _b, "+%d", u ); else fprintf ( _b, "%d", u ); \
                  fprintf ( _b, " \n    Re-input as +nnn/-nnn: " )


void
#ifdef _BT_ANSIC
_lib_GET_ACT_TOK( int * t, char * * T )
#else
_lib_GET_ACT_TOK( t, T )
int * t;
char * * T;
#endif
{
  int n;
  int i;
  int j;
  int done = 0;
  char u [ 50 ];
  if ( T [ 0 ] [ 0 ] != '\0' )  { 
    BLK ( 2 ); PUT_STR ( T [ 0 ] ); PUT_STR (  " value: " ); FLSH ();
    GET_NAT ( &n );
  }
  else {
    i = 1;
    while( T [ i ] [ 0 ] != '_' ) i++;
    j = 0;
    while ( T [ i ] [ j + 1 ] != '\0' && j < 50 ) {
      u [ j ] = T [ i ] [ j + 1 ];
     j++;
    }
    u [ j ] = '\0';
    while( ! done ) {
      i = 1;
      NWL ( 1 );
      while( T [ i ] [ 0 ] != '_' ){
        BLK ( 8 ); PUT_STR ( u ); PUT_STR ( "." );
        PUT_NAT_PAD ( i, 4 ); PUT_STR ( T [ i ] ); NWL ( 1 );
        i++;
      }
      BLK ( 4 ); PUT_STR ( u ); PUT_STR ( " value  (1.." );
      PUT_NAT ( i - 1 ); PUT_STR ( "): "); FLSH ();
      GET_NAT ( &n );
      if   ( n >= 1 && n <= i - 1 ) { done = 1; }
      else                          { BLK(15); PUT_STR (" Bad input!" ); }
    }
  }
  NWL ( 1 );
  *t = n; 
}

void
#ifdef _BT_ANSIC
_lib_GET_SET_ACT_TOK( int m, int * t, char * * T )
#else
_lib_GET_SET_ACT_TOK( m, t, T )
int m;
int * t;
char * * T;
#endif
{
  int n;
  int i;
  int j;
  int done;
  char u [ 50 ];
  if ( T [ 0 ] [ 0 ] != '\0' )  {
      for ( j = 0 ; j < m ; j++ ) {
        BLK ( 2 ); PUT_STR ( T [ 0 ] ); PUT_STR (  " value # ");
        PUT_NAT ( j + 1 ); PUT_STR ( ": "); FLSH ();
        GET_NAT ( &n );
        t [ j ] = n;
      }
  }
  else {
    i = 1;
    while( T [ i ] [ 0 ] != '_' ) i++;
    j = 0;
    while ( T [ i ] [ j + 1 ] != '\0' && j < 50 ) {
      u [ j ] = T [ i ] [ j + 1 ];
     j++;
    }
    u [ j ] = '\0';
    i = 1;
    while( T [ i ] [ 0 ] != '_' ){
      BLK ( 8 ); PUT_STR ( u ); PUT_STR ( "." );
      PUT_NAT_PAD ( i, 4 ); PUT_STR ( T [ i ] ); NWL ( 1 );
      i++;
    }
    for ( j = 0 ; j < m ; j++ ) {
      done = 0;
      while( ! done ) {
        BLK ( 4 ); PUT_STR ( u ); PUT_STR ( " value # " ); PUT_NAT ( j + 1 );
        PUT_STR(" (1.."); PUT_NAT ( i - 1 ); PUT_STR ( "): "); FLSH ();
        GET_NAT ( &n );
        if   ( n >= 1 && n <= i - 1 ) { t [ j ] = n; done = 1; }
        else                          { BLK(15); PUT_STR (" Bad input!\n" ); }
      }
    }
  } 
  NWL ( 1 );
}

#else

#define chk_slen(s) \
  if ( strlen ( s ) > 250 ) { \
    NWL ( 2 ); \
    PUT_STR_M ( s ); \
    PUT_STR_M ( " too long (max 250)" ); \
    NWL ( 2 ); \
    return; \
  }

#endif



void
#ifdef _BT_ANSIC
NWL( int n )
#else
NWL( n )
int n;
#endif
{
#ifndef _BT_Motif
	int i = 1;
	while ( i <= n ) {
		fprintf ( _b, "\n" );
		i++;
	}
#else
        NWL_M ( n );
#endif
}


void
#ifdef _BT_ANSIC
BLK( int n )
#else
BLK( n )
int n;
#endif
{
#ifndef _BT_Motif
	int i = 1;
	while( i <= n ) {
		fprintf ( _b, " " );
		i++;
	}
#else
        BLK_M ( n );
#endif
}


void
#ifdef _BT_ANSIC
GET_NBR( int *r, int d )
#else
GET_NBR( r, d )
int *r, d;
#endif
{
#ifndef _BT_Motif
	register int c,m,k,l,n ;
	{
                n = 0;
		k = d/10;
		l = d-10*(d/10);
		c = getchar();
		init_nbr;
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
					mess_nbr;
					c = getchar();
					init_nbr;
				}
			} else {
				mess_nbr;
				c = getchar();
				init_nbr;
			}
		}
		while( c!='\n' ){
			c = getchar();
		}
		*r = n;
	}
#else
        GET_PROMPT_NBR (r, "Input natural number:", d);
#endif
}




void
#ifdef _BT_ANSIC
GET_PROMPT_NBR( int *r, char *s, int d )
#else
GET_PROMPT_NBR( r, s, d )
int *r, d;
char *s;
#endif
{
#ifndef _BT_Motif
	PUT_STR ( s );
	GET_NBR ( r, d );
#else
        chk_slen( s );
        GET_PROMPT_NBR_M ( r, s, d );
#endif
}



void
#ifdef _BT_ANSIC
GET_ITGR( int *r, int l, int u )
#else
GET_ITGR( r, l, u )
int *r, l, u;
#endif
{
#ifndef _BT_Motif
  int buf [ 10 ];
  int i, c, is_neg, j, n, done;

  done = 0;
  while ( ! done ) {
    i = 0;
    c = getchar();
    while ( ( c == ' ' ) || ( c == '\t' ) ) { c = getchar(); }
    if ( ( c != '+' ) && ( c != '-' ) ) {
      mess_int ( l, u );
    }
    else {
      if   ( c == '+' )   is_neg = 0;
      else                is_neg = 1;
      c = getchar();
      while ( ( i < 10 ) && ( c>='0' ) && ( c<='9' ) ) {
        buf [ i++ ] = c - '0';
        c = getchar();
      }
      if ( ( c != '\n' ) || ( ! i ) || ( i > 10 ) ) {
        mess_int ( l, u );
      }
      else {
        if ( i < 10 ) {
          done = 1;
	}
        else {
          n = 0;
          for ( j = 0 ; j < 9 ; j++ ) { n = ( n * 10 ) + buf [ j ]; }
          if ( n < 214748364 ) {
            done = 1;
	  }
          else if ( n > 214748364 ) {
            mess_int ( l, u );
	  }
          else {
            if ( is_neg ) {
              if   ( buf [ 9 ] <= 7 ) { done = 1; }
              else                    { mess_int ( l, u ); }
	    }
            else {
              if   ( buf [ 9 ] <= 6 ) { done = 1; }
              else                    { mess_int ( l, u ); }
	    }
	  }
	}
      }
    }
    if ( done ) {
      n = 0;
      for ( j = 0 ; j < i ; j++ ) { n = ( n * 10 ) + buf [ j ]; }
      if ( is_neg ) n = -n;
      if ( ( n < l ) || ( n > u ) ) {
        done = 0;
        mess_int ( l, u );
      }
    }
  }
  *r = n;
#else
  GET_PROMPT_ITGR_M (r, "Input integer:", l, u );
#endif
}

void
#ifdef _BT_ANSIC
PUT_ITGR_PAD( int n, int p )
#else
PUT_ITGR_PAD( n, p )
int n;
int p;
#endif
{
  if ( n >= 0 ) PUT_STR ( "+" ); else PUT_STR ( "-" );
  if ( p > 0 ) PUT_NAT_PAD ( n, p-1 ); else PUT_NAT ( n );
}

void
#ifdef _BT_ANSIC
GET_PROMPT_ITGR( int *r, char *s, int l, int u )
#else
GET_PROMPT_ITGR( r, s, l, u )
int *r, l, u;
char *s;
#endif
{
#ifndef _BT_Motif
	PUT_STR ( s );
	GET_ITGR ( r, l, u );
#else
	chk_slen( s );
	GET_PROMPT_ITGR_M ( r, s, l, u );
#endif
}


#ifdef _BT_Motif
void
#ifdef _BT_ANSIC
GET_PROMPT_STR( char *s, char *t )
#else
GET_PROMPT_STR( s, t )
char *s;
char *t;
#endif
{
        chk_slen( t );
        GET_PROMPT_STR_M ( s, t );
}
#endif

void
#ifdef _BT_ANSIC
GET_BOOL( int *r )
#else
GET_BOOL( r )
int *r;
#endif
{ 
#ifndef _BT_Motif
	int b,c;
	b = 1;
	while( b == 1 ){
		c = getchar();
		if( c == 'T' ){
			c = getchar();
			if( c == 'R' ){
				c = getchar();
				if( c == 'U' ){
					c = getchar();
					if( c == 'E' ){
						*r = 1;
						b = 0;
						while( c!='\n' ){
							c = getchar();
						}
					} else{
						mess_bool;
					}
				} else{
					mess_bool;
				}
			} else{
				mess_bool;
			}
		} else if( c == 'F' ){
			c = getchar();
			if( c == 'A' ){
				c = getchar();
				if( c == 'L' ){
					c = getchar();
					if( c == 'S' ){
						c = getchar();
						if( c == 'E' ){
							*r = 0;
							b = 0;
							while( c!='\n' ){
								c = getchar();
							}
						} else{
							mess_bool;
						}
					} else{
						mess_bool;
					}
				} else{
					mess_bool;
				}
			} else{
				mess_bool;
			}
		} else{
			mess_bool;
		}
	}
#else
        GET_PROMPT_BOOL ( r, "Input boolean:" );
#endif
}


void
#ifdef _BT_ANSIC
GET_PROMPT_BOOL( int *r, char *s )
#else
GET_PROMPT_BOOL( r, s )
int *r;
char *s;
#endif
{ 
#ifndef _BT_Motif
	PUT_STR ( s );
	GET_BOOL( r );
#else
        GET_PROMPT_BOOL_M ( r, s );
#endif
}


void
#ifdef _BT_ANSIC
GET_BTS( int *s )
#else
GET_BTS( s )
int *s;
#endif
{
#ifndef _BT_Motif
	register int c;
	unsigned int k,l,m,n ;
	{
                n = 0;
		k = 2147483647;
		l = 1;
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
				}
			} else{
				mess_bits;
				c = getchar();
				init_bits;
			}
		}
		while( c!='\n' ){
			c = getchar();
		}
		*s = n;
	}
#else
        GET_PROMPT_BTS ( s, "Input bit string:" );
#endif
}


void
#ifdef _BT_ANSIC
GET_PROMPT_BTS( int *s, char *t )
#else
GET_PROMPT_BTS( s, t )
int *s;
char *t;
#endif
{
#ifndef _BT_Motif
	PUT_STR ( t );
        GET_BTS( s );
#else
        chk_slen( t );
        GET_PROMPT_BTS_M ( s, t );
#endif
}


void
#ifdef _BT_ANSIC
PUT_BTS( int r )
#else
PUT_BTS( r )
int r;
#endif
{
#ifndef _BT_Motif
	int i;
	i = 32;
	while( i>0 ){
		PUT_NAT ( (((r>>(i-1))%2)+2)%2 );
		i--;
	}
#else
        PUT_BTS_M ( r );
#endif
}


void
#ifdef _BT_ANSIC
GET_CHR( int *c )
#else
GET_CHR( c )
int *c;
#endif
{ 
#ifndef _BT_Motif
	register int d;
	d = getchar();
	*c =  d;
	while( d!='\n' ){
		d = getchar();
	}
#else
        GET_PROMPT_CHR ( c, "Input character:" );
#endif
}


void
#ifdef _BT_ANSIC
GET_PROMPT_CHR( int *c, char *s )
#else
GET_PROMPT_CHR( c, s )
int *c;
char *s;
#endif
{ 
#ifndef _BT_Motif
        PUT_STR ( s );
	GET_CHR ( c );
#else
        chk_slen( s );
        GET_PROMPT_CHR_M ( c, s );
#endif
}

void
#ifdef _BT_ANSIC
PUT_NAT_PAD( int n, int p )
#else
PUT_NAT_PAD( n, p )
int n;
int p;
#endif
{
	int l = 0;
	int m = n;
        while ( m ) { l++; m = ( m / 10 ); }
        PUT_NAT ( n );
        if ( p > l ) BLK ( p - l );
}
