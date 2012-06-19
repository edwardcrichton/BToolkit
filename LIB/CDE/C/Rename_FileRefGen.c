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
#include "Rename_FileRefGen.h"
#include "Bool_TYPE.h"

void
Rename_GEN_NEW_FILE_REF_pad_nbrStr( int _nn, char * _ss )
{
  if ( _nn < 10 ) {
    sprintf ( _ss, "0000%d", _nn );
  } 
  else if ( _nn < 100 ) {
    sprintf ( _ss, "000%d", _nn );
  } 
  else if ( _nn < 1000 ) {
    sprintf ( _ss, "00%d", _nn );
  } 
  else if ( _nn < 10000 ) {
    sprintf ( _ss, "0%d", _nn );
  } 
  else {
    sprintf ( _ss, "%d", _nn );
  } 
}

void
Rename_GEN_NEW_FILE_REF ( char * _filePathA, char * _filePathB, char * _filePathC, int * _updatedYear, int * _updatedRefNo, char * _refString, int _year, int _refNo )
{
  time_t       _tt;
  int          _mm;
  struct tm *  _tm_struct;
  char         _month_str [ 5 ];
  char         _nbr_str [ 10 ];

  _tt = time ( NULL );
  _tm_struct = localtime ( &_tt );

  _mm = _tm_struct->tm_mon + 1;
  if   ( _mm < 10 ) sprintf ( _month_str, "0%d", _mm );
  else              sprintf ( _month_str, "%d", _mm );

  * _updatedYear = _tm_struct->tm_year + 1900;

  * _updatedRefNo = _refNo;

  if   ( ( * _updatedRefNo < INT_MAX ) && ( * _updatedYear == _year ) ) * _updatedRefNo += 1;
  else                                                                  * _updatedRefNo = 1;
  Rename_GEN_NEW_FILE_REF_pad_nbrStr ( * _updatedRefNo, _nbr_str );
  sprintf ( _filePathA, "%s/%d_%s/%s",  _refString, * _updatedYear, _month_str, _nbr_str );

  if   ( * _updatedRefNo < INT_MAX ) * _updatedRefNo += 1;
  else                               * _updatedRefNo = 1;
  Rename_GEN_NEW_FILE_REF_pad_nbrStr ( * _updatedRefNo, _nbr_str );
  sprintf ( _filePathB, "%s/%d_%s/%s",  _refString, * _updatedYear, _month_str, _nbr_str );

  if   ( * _updatedRefNo < INT_MAX ) * _updatedRefNo += 1;
  else                               * _updatedRefNo = 1;
  Rename_GEN_NEW_FILE_REF_pad_nbrStr ( * _updatedRefNo, _nbr_str );
  sprintf ( _filePathC, "%s/%d_%s/%s",  _refString, * _updatedYear, _month_str, _nbr_str );
}

/*
void
Rename_GEN_BACKUP_FILE_REF ( char * _newFilePath, int * _updatedYear, int * _updatedRefNo, char * _filePath, int _year, int _refNo )
{
  #define _refStringMAX 100
  char _refString [ _refStringMAX + 1 ];
  int _ii = 0;
  
  while ( ( _ii < _refStringMAX ) && ( _filePath [ _ii ] != '/' ) && ( _filePath [ _ii ] != '\0' ) ) {
    _refString [ _ii ] = _filePath [ _ii ];
    _ii++;
  }
  _refString [ _ii ] = '\0';

  Rename_GEN_NEW_FILE_REF ( _newFilePath, _updatedYear, _updatedRefNo, _refString, _year, _refNo );
}
*/
