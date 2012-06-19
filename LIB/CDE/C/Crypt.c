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
#include <stdlib.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>

#include "Crypt.h"

char
_CRYPT_SALT ()
{
  char c;
  int rn = (int) (64.0 * rand() / (RAND_MAX+1.0) );
  if ( rn < 26 )       c = ( char ) 'a' + rn;
  else if ( rn < 52 )  c = ( char ) 'A' - 26 + rn;
  else if ( rn < 62 )  c = ( char ) '0' - 52 + rn;
  else if ( rn == 62 ) c = ( char ) '/';
  else                 c = ( char ) '.';
  return ( c );
}

void
CRYPT ( char * _ss, char * _key )
{
  char salt [ 3 ];
  salt [ 0 ] = _CRYPT_SALT ();
  salt [ 1 ] = _CRYPT_SALT ();
  salt [ 2 ] = '\0';
  strcpy ( _ss, crypt ( _key, salt ) );
}

void
CRYPT_CHECK ( int * _rr, char * _key, char * _encryption )
{
  char salt [ 3 ];
  salt [ 0 ] = _encryption [ 0 ];
  salt [ 1 ] = _encryption [ 1 ];
  salt [ 2 ] = '\0';
  * _rr = ( ( strcmp ( crypt ( _key, salt ), _encryption ) == 0 ) != 0 );
}
