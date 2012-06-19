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

extern FILE *dump_file;

#define INI_Rename_file_dump()          { ; }


#define Rename_open_write_dump(rep) \
  { *rep = ( ( dump_file = fopen ( "Rename.dump", "w" ) ) != NULL ); }

#define Rename_open_append_dump(rep) \
  { *rep = ( ( dump_file = fopen ( "Rename.dump", "a" ) ) != NULL ); }

#define Rename_open_read_dump(rep) \
  { *rep = ( ( dump_file = fopen ( "Rename.dump", "r" ) ) != NULL ); }


#define Rename_open_write_dump_network(rep) \
  { *rep = ( ( dump_file = fopen ( "Rename.dump.network", "w" ) ) != NULL ); }

#define Rename_open_append_dump_network(rep) \
  { *rep = ( ( dump_file = fopen ( "Rename.dump.network", "a" ) ) != NULL ); }

#define Rename_open_read_dump_network(rep) \
  { *rep = ( ( dump_file = fopen ( "Rename.dump.network", "r" ) ) != NULL ); }


#define Rename_close_dump(rep) \
  { *rep = ( ( fclose ( dump_file ) ) == 0 ); }
