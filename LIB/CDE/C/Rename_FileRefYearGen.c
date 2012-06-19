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
#include "Rename_FileRefYearGen.h"
#include "Bool_TYPE.h"

void
 Rename_GEN_FILE_REF_YEAR( char * _filePath, int * _updatedYear, int * _updatedRefNo, char * _refString, int _year, int _refNo )
{
  time_t       _tt;
  int          _mm;
  struct tm *  _tm_struct;

  _tm_struct = localtime ( &_tt );
  _mm = _tm_struct->tm_mon + 1;
  * _updatedYear = _tm_struct->tm_year + 1900;

  if   ( ( _refNo < INT_MAX ) && ( * _updatedYear == _year ) ) * _updatedRefNo = _refNo + 1;
  else                                                         * _updatedRefNo = 0;

  sprintf ( _filePath, "%s/%d_%d/%d", _refString, * _updatedYear, _mm, * _updatedRefNo );
}
