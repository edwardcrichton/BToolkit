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
#include "QueryCheck.h"

void
#ifdef _BT_ANSIC
CHK_QUERY( int *_status, int *_comment, int *_query )
#else
CHK_QUERY( _status, _comment, _query )
int *_status, *_comment *_query;
#endif
{
  FILE *file_in, *file_out;
  int  c, i, j;
  char __query   [ 2000 ];
  char __comment [ 2000 ];
  struct stat stat_buf;

  *_status = _unknownQueryStatus;
  __comment [ 0 ] = '\0';

  i = 0;
  j = 0;
  while ( ( ( char * ) _query ) [ i ] != '\0' ) {
    if  ( ( ( char * ) _query ) [ i ] == '\r' ) {  /* deal with windows crap */
      i++;
    }
    else {
      if   ( ( ( char * ) _query ) [ i ] == '\n' ) {
         __query [ j++ ] = ' ';
         __query [ j++ ] = ( ( char * ) _query ) [ i++ ];
         __query [ j++ ] = ' ';
      }
      else {
        __query [ j++ ] = ( ( char * ) _query ) [ i++ ];
      }
    }
  }
  __query [ j ] = '\0';

  file_out = fopen ( ".BBcom", "w" );
  if ( file_out == NULL ) {
    printf ( "\n  %s: can't open \"%s\" for writing\n\n", "QueryCheck", ".BBcom" );
    *_status = _unknownQueryStatus;
    __comment [ 0 ] = '\0';
    strcpy ( ( char * ) _comment, __comment );
    return;
  }
  fprintf ( file_out, "%s\n", __query );
  fclose ( file_out );

  if ( stat ( "EXEC/queryCheck.src.bin", &stat_buf ) == -1 ) {
    printf ( "\n  %s: does not exist\n\n", "EXEC/queryCheck.src.bin" );
    *_status = _unknownQueryStatus;
    __comment [ 0 ] = '\0';
    strcpy ( ( char * ) _comment, __comment );
    return;
  }
  if ( stat ( "EXEC/b", &stat_buf ) == -1 ) {
    printf ( "\n  %s: does not exist\n\n", "EXEC/b" );
    *_status = _unknownQueryStatus;
    __comment [ 0 ] = '\0';
    strcpy ( ( char * ) _comment, __comment );
    return;
  }
  if ( stat ( "EXEC/.Bexe", &stat_buf ) == -1 ) {
    printf ( "\n  %s: does not exist\n\n", "EXEC/.Bexe" );
    *_status = _unknownQueryStatus;
    __comment [ 0 ] = '\0';
    strcpy ( ( char * ) _comment, __comment );
    return;
  }

  unlink ( ".BBlog" );
  unlink ( ".Blog" );
  unlink ( ".Bcom" );

  system ( "EXEC/b -b EXEC/queryCheck.src.bin EXEC/.Bexe 2> .Blog" );
  /*
  system ( "EXEC/b -b EXEC/queryCheck.src.bin EXEC/.Bexe 2> .Blog > /dev/null" );
  */

  file_in = fopen ( ".Bcom", "r" );
  if ( file_in == NULL ) {
   printf ( "\n  %s: can't open \"%s\" for reading\n\n", "QueryCheck", ".Bcom" );
    *_status = _unknownQueryStatus;
    __comment [ 0 ] = '\0';
    strcpy ( ( char * ) _comment, __comment );
   return;
  }
  c = getc ( file_in ) - '0';
  fclose ( file_in );
  unlink ( ".Bcom" );

  switch ( c ) {
  case 2:
    *_status = _isValidQueryStatus;
    break;
  case 3:
    *_status = _doesNotParseQueryStatus;
    break;
  case 4:
    *_status = _isInvalidQueryStatus;
    break;
  default:
    printf ( "\n  %s: error reading %s\n\n", "QueryCheck", ".Bcom" );
    *_status = _unknownQueryStatus;
    __comment [ 0 ] = '\0';
    strcpy ( ( char * ) _comment, __comment );
    return;
    break;
  }

  if ( c == 4 ) {
    system ( "cp .BBlog .Blog" );
    unlink ( ".BBlog" );
  }

  if ( c != 2 ) {

/***
printf ( "\n***** QueryCheck.c (INITIALLY) *****\n" ); system ( "cat .Blog" ); printf ( "\n***** QueryCheck.c (INITIALLY) *****\n" ); fflush ( stdout );
***/

    system ( "#!/bin/sh\nsed s/[\\ ]*[\\(]*.BBcom[\\)]*[\\ ]*[:]*//g                         < .Blog   > .BBBcom" );
    system ( "#!/bin/sh\nsed s/[0-9][0-9]*[:]/Line\\ \\&/g                                   < .BBBcom > .Blog"   );
    system ( "#!/bin/sh\nsed s/[\\ ]*Line\\ /Line\\ \\/g                                     < .Blog   > .BBBcom" );
    system ( "#!/bin/sh\nsed s/SSEELLEECCTT/SELECT/g                                         < .BBBcom > .Blog"   );
    system ( "#!/bin/sh\nsed s/xxxorxxx/OR/g                                                 < .Blog   > .BBBcom" );
    system ( "#!/bin/sh\nsed s/xxxandxxx/AND/g                                               < .BBBcom > .Blog"   );
    system ( "#!/bin/sh\nsed s/AAAINAAA/IN/g                                                 < .Blog   > .BBBcom" );
    system ( "#!/bin/sh\nsed s/AAAEQAAA/==/g                                                 < .BBBcom > .Blog"   );
    system ( "#!/bin/sh\nsed s/BBBEQBBB/IS/g                                                 < .Blog   > .BBBcom" );
    system ( "#!/bin/sh\nsed s/AAANEAAA/!=/g                                                 < .BBBcom > .Blog"   );
    system ( "#!/bin/sh\nsed s/BBBEQBBB/IS/g                                                 < .Blog   > .BBBcom" );
    system ( "#!/bin/sh\nsed s/[\\[]\\\"/\\[/g                                               < .BBBcom > .Blog"   );
    system ( "#!/bin/sh\nsed s/\\\"[\\]]/\\]/g                                               < .Blog   > .BBBcom" );
    system ( "#!/bin/sh\nsed s/possible\\ real\\ start\\ of\\ unterminated\\ constant/start\\ of\\ unterminated\\ string?/g  < .BBBcom > .Blog"   );
    system ( "#!/bin/sh\nsed s/\\ or\\ character\\ constant//g                               < .Blog   > .BBBcom" );
    system ( "#!/bin/sh\nsed s/Formula\\ required\\ at\\ start\\ of\\ line/Emtpty\\ query/g  < .BBBcom > .Blog"   );
    system ( "#!/bin/sh\nsed s/Formula/Text/g                                                < .Blog   > .BBBcom" );
    system ( "#!/bin/sh\nsed s/formula/text/g                                                < .BBBcom > .Blog"   );
    system ( "#!/bin/sh\nsed s/required/missing/g                                            < .Blog   > .BBBcom" );
    system ( "#!/bin/sh\nsed s/\\ yyyoryyy\\ /\\ \\|\\ /g                                    < .BBBcom > .Blog"   );
    unlink ( ".BBBcom" );

/***
printf ( "\n***** QueryCheck.c (FINALLY) *****\n" ); system ( "cat .Blog" ); printf ( "\n***** QueryCheck.c (FINALLY) *****\n" ); fflush ( stdout );
***/

    file_in = fopen ( ".Blog", "r" );
    if ( file_in == NULL ) {
     printf ( "\n  %s: can't open \"%s\" for reading\n\n", "QueryCheck", ".Blog" );
       *_status = _unknownQueryStatus;
       __comment [ 0 ] = '\0';
       strcpy ( ( char * ) _comment, __comment );
       return;
    }
    c = getc ( file_in );
    i = 0;
    while ( ( c == ' ' ) || ( c == '\n' ) ) { c = getc ( file_in ); };
    while ( ( i < 990 ) && ( c != EOF ) ) {
      __comment [ i++ ] = c;
      if ( c == '\n' ) {
        c = getc ( file_in );
        while ( /* ( c == ' ' ) || */ ( c == '\n' ) ) { c = getc ( file_in ); };
      }
      else {
         c = getc ( file_in );
      }
    }
    fclose ( file_in );
    unlink ( ".Blog" );

    __comment [ i ] = '\0';
    while ( ( __comment [ i - 1 ] == '\n' ) || ( __comment [ i - 1 ] == ' ' ) ) {
      __comment [ i - 1 ] = '\0';
      i--;
    }
    i = strlen ( __comment );
    if ( i == 990 ) {
      __comment [ 970 ] = '\0';
      strcat ( __comment, " ... etc etc!" );
    }
  }

  strcpy ( ( char * ) _comment, __comment );

/***
printf ( "\n***** QueryCheck.c returning status as %d\n", *_status ); fflush ( stdout );
***/

}
