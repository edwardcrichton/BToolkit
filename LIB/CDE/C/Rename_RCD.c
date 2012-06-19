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
extern int Rename_RCDP1;
extern int Rename_RCDP2;
extern int Rename_RCDP3;

extern int Rename_RCD_ARR_BiArrP1;
extern int Rename_RCD_ARR_BiArrP2;
extern int Rename_RCD_ARR_BiArrP3;

extern int Rename_RCD_ARR[];

extern int Rename_RCD_HEAP_ARR_BiArrP1;
extern int Rename_RCD_HEAP_ARR_BiArrP2;
extern int Rename_RCD_HEAP_ARR_BiArrP3;

extern int Rename_RCD_HEAP_ARR[];

extern int Rename_RCD_TOT;

INI_Rename_RCD()
{
  INI_Rename_RCD_ARR_BiArr();
  INI_Rename_RCD_HEAP_ARR_BiArr();
  INI_Rename_RCD_TOT_Byt();
  {
    int ii;
    ii = 0;
    while( ii<Rename_RCDP3 ){
      Rename_RCD_HEAP_ARR[( ii )-(Rename_RCD_HEAP_ARR_BiArrP2)] =  ii  ;
      *( &ii ) = ( ii )+1 ;
    };
    Rename_RCD_TOT =  0  ;
  }
}

Rename_RCD_IDX(int *bb,int idx)
{
  if( idx<=Rename_RCDP2 ){
    *bb = 1 ;
  } else {
    *bb = 0 ;
  }
}

Rename_RCD_FULL(int *bb)
{
  int vv;
  *( &vv ) = Rename_RCD_TOT ;
  if( vv == Rename_RCDP3 ){
    *bb = 1 ;
  } else {
    *bb = 0 ;
  }
}

Rename_RCD_CRE(int *rr)
{
  int ii,ss;
  *( &ii ) = Rename_RCD_TOT ;
  *( &ss ) = Rename_RCD_HEAP_ARR[( ii )-(Rename_RCD_HEAP_ARR_BiArrP2)] ;
  *( rr ) = ( ss )+1 ;
  Rename_RCD_TOT = Rename_RCD_TOT+1 ;
}

Rename_RCD_KILL(int rr)
{
  int ii,ss;
  Rename_RCD_TOT = Rename_RCD_TOT-1 ;
  *( &ss ) = ( rr )-1 ;
  *( &ii ) = Rename_RCD_TOT ;
  Rename_RCD_HEAP_ARR[( ii )-(Rename_RCD_HEAP_ARR_BiArrP2)] =  ss  ;
}

Rename_RCD_DEF(int *bb,int rr)
{
  int tt,ii,aa,ss;
  *( &tt ) = Rename_RCD_TOT ;
  aa = 1 ;
  ii = Rename_RCDP3;
  while( aa == 1  && ii>tt ){
    *( &ii ) = ( ii )-1 ;
    *( &ss ) = Rename_RCD_HEAP_ARR[( ii )-(Rename_RCD_HEAP_ARR_BiArrP2)] ;
    *( &ss ) = ( ss )+1 ;
    if( rr == ss ){
      aa = 0 ;
    }
  };
  *bb = aa;
}

Rename_RCD_STO(int rr,int idx,int vv)
{
  int jj,kk;
  *( &jj ) = ( rr )-1 ;
  *( &kk ) = ( idx )-1 ;
  *( &jj ) = ( jj )*( Rename_RCDP2 ) ;
  *( &jj ) = ( jj )+( kk ) ;
  Rename_RCD_ARR[( jj )-(Rename_RCD_ARR_BiArrP2)] =  vv  ;
}

Rename_RCD_VAL(int *vv,int rr,int idx)
{
  int jj,kk;
  *( &jj ) = ( rr )-1 ;
  *( &kk ) = ( idx )-1 ;
  *( &jj ) = ( jj )*( Rename_RCDP2 ) ;
  *( &jj ) = ( jj )+( kk ) ;
  *( vv ) = Rename_RCD_ARR[( jj )-(Rename_RCD_ARR_BiArrP2)] ;
}

