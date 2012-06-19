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
#include "Rename_Utilities.h"

#define _chk_exist(a,b) \
  if ( stat ( a, &stat_buf ) == -1 ) { \
    if ( b ) printf ( "\n\n  %s: does not exist\n\n", a ); \
    else     printf ( "\n\n  %s: could not create\n\n", a ); \
    *_rep = 0; \
    return; \
  }

void
Rename_RestorePreviousData ( int * _rep, char * _sysname, int _op )
{
  char iedir   [ 100 ];
  char buf    [ 1000 ];
  struct stat stat_buf;
  time_t _t = time ( NULL );
  FILE * infofile;

  _chk_exist ( "IntegrityCheck.txt", 1 );
  sprintf ( iedir, "%d_IntegrityError", ( int ) _t );
  sprintf ( buf, "rm -fr %s", iedir );
  system ( buf );
  sprintf ( buf, "mkdir %s", iedir );
  system ( buf );
  sprintf ( buf, "cp IntegrityCheck.txt %s", iedir );
  system ( buf );
  sprintf ( buf, "cp TXT/*.txt %s", iedir );
  system ( buf );
  sprintf ( buf, "%d_IntegrityError_READ_ME", ( int ) _t );
  infofile = fopen ( buf, "w" );
  if ( fopen != NULL ) {
    fprintf ( infofile, "\n  Integrity error occurred on " );
    fclose ( infofile );
  }
  sprintf ( buf, "date >> %d_IntegrityError_READ_ME", ( int ) _t );
  system ( buf );
  fflush ( stdout );
  sprintf ( buf, "%d_IntegrityError_READ_ME", ( int ) _t );
  infofile = fopen ( buf, "a" );
  if ( fopen != NULL ) {
    fprintf ( infofile, "\n  The relevant IntegrityCheck.txt and object .txt files are\n  in the directory %s\n\n", iedir );
    fprintf ( infofile, "  The error seems to have been caused by op %d,\n  appearing in FILE_C/%sOpcodes.h as:\n\n    ", _op, _sysname );
    fclose ( infofile );
  }
  sprintf ( buf, "grep %d FILE_C/%sOpcodes.h >> %d_IntegrityError_READ_ME", _op, _sysname, ( int ) _t );
  system ( buf );
  sprintf ( buf, "%d_IntegrityError_READ_ME", ( int ) _t );
  infofile = fopen ( buf, "a" );
  if ( fopen != NULL ) {
    fprintf ( infofile, "\n  For the op history list, see `modOpHistory' in `Global.txt'\n\n" );
    fclose ( infofile );
  }

  *_rep = 1;
}
