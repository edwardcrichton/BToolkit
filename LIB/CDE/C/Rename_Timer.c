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
#include "Rename_Timer.h"
#include "Bool_TYPE.h"
#include "Scalar_TYPE.h"

#define __inc_month \
  { \
    _dd = 1; \
    _mm++; \
    if ( _mm == 13 ) { _mm = 1; _yy++; } \
  }

void
Rename_IncYearMonthDay( int * _inc_ymd, int _ymd, int _days )
{
  int _loop_n    = _days;
  int _dd        = _ymd-100*(_ymd/100);
  int _mm        = (_ymd/100)-100*(_ymd/10000);
  int _yy        = _ymd/10000;
  while ( _loop_n ) {
    switch ( _dd ) {
    case 31:
      __inc_month;
      break;
    case 30:
      switch ( _mm ) {
      case  9:
      case  4:
      case  6:
      case 11:
        __inc_month;
        break;
      default :
        _dd++;
        break;
      }
      break;
    case 29:
      switch ( _mm ) {
      case  2:
        __inc_month;
        break;
      default :
        _dd++;
        break;
      }
      break;
    case 28:
      switch ( _mm ) {
      case  2:
        if ( _yy == _yy-4*(_yy/4) ) _dd++;
        else  __inc_month;
        break;
      default :
        _dd++;
        break;
      }
      break;
    default:
      _dd++;
      break;
    }
    _loop_n--;
  }
  * _inc_ymd = (_yy*10000)+(_mm*100)+_dd;
}
