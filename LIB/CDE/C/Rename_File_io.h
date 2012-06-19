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

extern FILE *Rename_File_io_ptr;


#define INI_Rename_File_io()  { ; }

#define Rename_OPEN_READ(rep,filename) \
  { *rep = ( ( Rename_File_io_ptr = fopen ( ( char * ) filename, "r" ) ) != NULL ); }

#define Rename_OPEN_WRITE(rep,filename) \
  { *rep = ( ( Rename_File_io_ptr = fopen ( ( char * )filename, "w" ) ) != NULL ); }

#define Rename_OPEN_APPEND(rep,filename) \
  { *rep = ( ( Rename_File_io_ptr = fopen ( ( char * )filename, "a" ) ) != NULL ); }

#define Rename_CLOSE(rep) \
  { *rep = ( ( fclose ( Rename_File_io_ptr ) ) == 0 ); }

#define Rename_PUT_STR(rep,ss) \
  { *rep = ( ( fprintf ( Rename_File_io_ptr, "%s", ( char * ) ss ) ) == strlen ( ( char * ) ss ) ); }

#define Rename_PUT_CHAR(rep,cc) \
  { *rep = ( ( fprintf ( Rename_File_io_ptr, "%c", ( char ) cc ) ) != 0 ); }

#define Rename_PUT_NAT(rep,nn) \
  { *rep = ( ( fprintf ( Rename_File_io_ptr, "%d", ( int ) nn ) ) != 0 ); }

#define Rename_PUT_TOK(rep,tt) Rename_PUT_NAT(rep,tt)

#define Rename_GET_STR(rep,ss) \
  { *rep = ( ( fgets ( (char *) ss, 250, Rename_File_io_ptr ) != NULL ) ); }

#define Rename_GET_CHAR(rep,cc) \
  { *rep = ( ( *cc = getc ( Rename_File_io_ptr ) ) != EOF ); }

#define Rename_GET_NAT(rep,nn) \
  { *rep = ( ( *nn = getw ( Rename_File_io_ptr ) ) != EOF ); }

#define Rename_GET_TOK(rep,tt)  Rename_GET_NAT(rep,nn)

#define Rename_PUT_NWL(rep,nn) \
  { int i = nn; *rep = 1; while ( *rep && i ) \
   { Rename_PUT_CHAR ( rep, '\n' ); i--; } }

#define Rename_PUT_BLK(rep,nn) \
  { int i = nn; *rep = 1; while ( *rep && i ) \
   { Rename_PUT_CHAR (rep, ' ' ); i--; } }

#define Rename_FLUSH(rep) \
  { *rep = ( ( fflush ( Rename_File_io_ptr ) ) == 0 ); }
