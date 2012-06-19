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
extern int Rename_BiRcdP1;
extern int Rename_BiRcdP2;
extern int Rename_BiRcdP3;

extern int Rename_BiRcd_ARR_BiArrP1;
extern int Rename_BiRcd_ARR_BiArrP2;
extern int Rename_BiRcd_ARR_BiArrP3;

extern int Rename_BiRcd_ARR[];

extern int Rename_BiRcd_HEAP_ARR_BiArrP1;
extern int Rename_BiRcd_HEAP_ARR_BiArrP2;
extern int Rename_BiRcd_HEAP_ARR_BiArrP3;

extern int Rename_BiRcd_HEAP_ARR[];

extern int Rename_BiRcd_TOT;

void
INI_Rename_BiRcd()
{
  Rename_BiRcd_TOT = 0 ;
  {
    int ii;
    ii = 0;
    while( ii<Rename_BiRcdP3 ){
      Rename_BiRcd_HEAP_ARR[ ii ] =  ii  ;
      *( &ii ) = ( ii )+1 ;
    };
    Rename_BiRcd_TOT =  0  ;
  }
}

void
Rename_BiRcd_RST()
{
  int ii;
  ii = 0;
  while( ii<Rename_BiRcdP3 ){
    Rename_BiRcd_HEAP_ARR[ ii ] =  ii  ;
    *( &ii ) = ( ii )+1 ;
  };
  Rename_BiRcd_TOT =  0  ;
}

void
#ifdef _BT_ANSIC
Rename_BiRcd_IDX(int *bb, int idx)
#else
Rename_BiRcd_IDX(bb,idx)
int *bb,idx;
#endif
{
  if( idx<=Rename_BiRcdP2 ){
    *bb = 1 ;
  } else {
    *bb = 0 ;
  }
}

void
#ifdef _BT_ANSIC
Rename_BiRcd_FULL(int *bb)
#else
Rename_BiRcd_FULL(bb)
int *bb;
#endif
{
  int vv;
  *( &vv ) = Rename_BiRcd_TOT ;
  if( vv == Rename_BiRcdP3 ){
    *bb = 1 ;
  } else {
    *bb = 0 ;
  }
}

void
#ifdef _BT_ANSIC
Rename_BiRcd_CRE(int *rr)
#else
Rename_BiRcd_CRE(rr)
int *rr;
#endif
{
  int ii,ss;
  *( &ii ) = Rename_BiRcd_TOT ;
  *( &ss ) = Rename_BiRcd_HEAP_ARR[ ii ] ;
  *( rr ) = ( ss )+1 ;
  Rename_BiRcd_TOT = Rename_BiRcd_TOT+1 ;
}

void
#ifdef _BT_ANSIC
Rename_BiRcd_KILL(int rr)
#else
Rename_BiRcd_KILL(rr)
int rr;
#endif
{
  int ii,ss;
  Rename_BiRcd_TOT = Rename_BiRcd_TOT-1 ;
  *( &ss ) = ( rr )-1 ;
  *( &ii ) = Rename_BiRcd_TOT ;
  Rename_BiRcd_HEAP_ARR[ ii ] =  ss  ;
}

void
#ifdef _BT_ANSIC
Rename_BiRcd_VLD(int *bb, int rr)
#else
Rename_BiRcd_VLD(bb,rr)
int *bb,rr;
#endif
{
  int tt,ii,aa,ss;
  *( &tt ) = Rename_BiRcd_TOT ;
  if( rr >= 1 && rr <= Rename_BiRcdP3 ) {
    aa = 1 ;
  }
  else {
    aa = 0 ;
  }
  ii = Rename_BiRcdP3;
  while( aa == 1  && ii>tt ){
    *( &ii ) = ( ii )-1 ;
    *( &ss ) = Rename_BiRcd_HEAP_ARR[ ii ] ;
    *( &ss ) = ( ss )+1 ;
    if( rr == ss ){
      aa = 0 ;
    }
  };
  *bb = aa;
}

void
#ifdef _BT_ANSIC
Rename_BiRcd_STO(int rr, int idx, int vv)
#else
Rename_BiRcd_STO(rr,idx,vv)
int rr,idx,vv;
#endif
{
  int jj,kk;
  *( &jj ) = ( rr )-1 ;
  *( &kk ) = ( idx )-1 ;
  *( &jj ) = ( jj )*( Rename_BiRcdP2 ) ;
  *( &jj ) = ( jj )+( kk ) ;
  Rename_BiRcd_ARR[ jj ] =  vv  ;
}

void
#ifdef _BT_ANSIC
Rename_BiRcd_VAL(int *vv, int rr, int idx)
#else
Rename_BiRcd_VAL(vv,rr,idx)
int *vv,rr,idx;
#endif
{
  int jj,kk;
  *( &jj ) = ( rr )-1 ;
  *( &kk ) = ( idx )-1 ;
  *( &jj ) = ( jj )*( Rename_BiRcdP2 ) ;
  *( &jj ) = ( jj )+( kk ) ;
  *( vv ) = Rename_BiRcd_ARR[ jj ] ;
}
