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
/* added*/
#include <string.h>

#define MAX_BUF 1000

/*void*/
/* should be int*/
int
main  ( argc, argv )
int argc;
char *argv[];
{

  int i, c, done;
  char buf [ MAX_BUF + 1 ];
  char cpy_buf [ MAX_BUF + 1 ];

  i = 0;
  c = getc ( stdin );
  while ( c != EOF && i < MAX_BUF ) {
    buf [ i ] = ( char ) c;
    i++;
    c = getc ( stdin );
  }
  buf [ i ] = '\0';

  strcpy ( cpy_buf, buf );

  done = 0;
  while ( ! done && i > 0 ) {
    i--;
    if ( buf [ i ] == '_' ) {
      buf [ i ] = ';';
      done = 1;
    }
  }

  /********************************************************************/

  putc ( '(', stdout );
  putc ( '(', stdout );
  putc ( '?', stdout );
  putc ( ')', stdout );
  putc ( '|', stdout );
  putc ( '(', stdout );

  /********************************************************************/

  i = 0;
  while ( buf [ i ] != '\0' ) {
    putc ( buf [ i ], stdout );
    i++;
  }

  /********************************************************************/
  putc ( ')', stdout );
  putc ( '|', stdout );
  putc ( '(', stdout );

  /********************************************************************/

  strcpy ( buf, cpy_buf );

  done = 0;
  while ( ! done && i > 0 ) {
    i--;
    if ( buf [ i ] == '_' ) {
      done = 1;
    }
  }

  done = 0;
  while ( ! done && i > 0 ) {
    i--;
    if ( buf [ i ] == '_' ) {
      buf [ i ] = ';';
      done = 1;
    }
  }

  i = 0;
  while ( buf [ i ] != '\0' ) {
    putc ( buf [ i ], stdout );
    i++;
  }

  /********************************************************************/

  putc ( ')', stdout );
  putc ( '|', stdout );
  putc ( '(', stdout );

  /********************************************************************/

  strcpy ( buf, cpy_buf );

  done = 0;
  while ( ! done && i > 0 ) {
    i--;
    if ( buf [ i ] == '_' ) {
      done = 1;
    }
  }

  done = 0;
  while ( ! done && i > 0 ) {
    i--;
    if ( buf [ i ] == '_' ) {
      done = 1;
    }
  }

  done = 0;
  while ( ! done && i > 0 ) {
    i--;
    if ( buf [ i ] == '_' ) {
      buf [ i ] = ';';
      done = 1;
    }
  }

  i = 0;
  while ( buf [ i ] != '\0' ) {
    putc ( buf [ i ], stdout );
    i++;
  }

  /********************************************************************/

  putc ( ')', stdout );
  putc ( ')', stdout );

  /********************************************************************/


  return 0;
}
