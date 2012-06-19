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
#include "Rename_BiSeq.h"

#define val_obj 1
#define next_byt_obj 2

#include "Rename_B_BiRcd.h"
#include "Rename_V_BiRcd.h"
#include "Rename_I_Byt.h"
#include "Rename_T_Byt.h"

#include "Bool_TYPE.h"
#include "Byt_TYPE.h"

void
INI_Rename_BiSeq()
{
  INI_Rename_B_BiRcd();
  INI_Rename_V_BiRcd();
  INI_Rename_I_Byt();
  INI_Rename_T_Byt();
  Rename_T_STO(0);
  Rename_I_STO(1);
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_FULL(int *bb)
#else
Rename_BiSeq_FULL(bb)
int *bb;
#endif
{
  int len;
  Rename_T_VAL(&len);
  BEQ(bb,len,Rename_BiSeqP2);
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_IDX(int *bb, int idx)
#else
Rename_BiSeq_IDX(bb,idx)
int *bb,idx;
#endif
{
  int len,tt;
  BGT(&tt,idx,MinByt);
  if( tt == TRUE ){
    Rename_T_VAL(&len);
    BLE(&tt,idx,len);
  };
  *bb = tt;
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_LEN(int *ll)
#else
Rename_BiSeq_LEN(ll)
int *ll;
#endif
{
  Rename_T_VAL(ll);
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_FRST(int *vv)
#else
Rename_BiSeq_FRST(vv)
int *vv;
#endif
{
  int ii;
  Rename_I_VAL(&ii);
  Rename_V_BiRcd_VAL(vv,ii,val_obj);
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_LAST(int *vv)
#else
Rename_BiSeq_LAST(vv)
int *vv;
#endif
{
  int count,len,ii;
  count = 1;
  Rename_T_VAL(&len);
  Rename_I_VAL(&ii);
  while( count<len ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_V_BiRcd_VAL(vv,ii,val_obj);
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_VAL(int *vv,int idx)
#else
Rename_BiSeq_VAL(vv,idx)
int *vv,idx;
#endif
{
  int ii,count;
  count = 1;
  Rename_I_VAL(&ii);
  while( count<idx ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_V_BiRcd_VAL(vv,ii,val_obj);
}

void
Rename_BiSeq_CLR()
{
  int count,len,ii,jj;
  count = 0;
  Rename_I_VAL(&ii);
  jj = ii;
  Rename_T_VAL(&len);
  while( count<len ){
    Rename_B_BiRcd_VAL(&jj,ii,val_obj);
    Rename_V_BiRcd_KILL(jj);
    jj = ii;
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    Rename_B_BiRcd_KILL(jj);
    BINC(&count,count);
  };
  Rename_T_STO(0);
  Rename_I_STO(jj);
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_FILL(int len,int vv)
#else
Rename_BiSeq_FILL(len,vv)
int len,vv;
#endif
{
  int count,ii,jj,kk;
  Rename_B_BiRcd_CRE(&ii);
  Rename_V_BiRcd_CRE(&jj);
  Rename_V_BiRcd_STO(jj,1,vv);
  Rename_B_BiRcd_STO(ii,val_obj,jj);
  Rename_I_STO(ii);
  count = 1;
  while( count<len ){
    Rename_B_BiRcd_CRE(&kk);
    Rename_V_BiRcd_CRE(&jj);
    Rename_V_BiRcd_STO(jj,1,vv);
    Rename_B_BiRcd_STO(ii,next_byt_obj,kk);
    Rename_B_BiRcd_STO(kk,val_obj,jj);
    ii = kk;
    BINC(&count,count);
  };
  Rename_T_STO(len);
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_STO(int idx,int vv)
#else
Rename_BiSeq_STO(idx,vv)
int idx,vv;
#endif
{
  int count,ii;
  count = 1;
  Rename_I_VAL(&ii);
  while( count<idx ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_V_BiRcd_STO(ii,val_obj,vv);
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_INS(int idx,int vv)
#else
Rename_BiSeq_INS(idx,vv)
int idx,vv;
#endif
{
  int count,ii,jj,kk;
  count = 1;
  Rename_I_VAL(&ii);
  kk = ii;
  while( count<idx ){
    kk = ii;
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_B_BiRcd_CRE(&jj);
  Rename_B_BiRcd_STO(kk,next_byt_obj,jj);
  Rename_B_BiRcd_STO(jj,next_byt_obj,ii);
  Rename_V_BiRcd_CRE(&ii);
  Rename_B_BiRcd_STO(jj,val_obj,ii);
  Rename_V_BiRcd_STO(ii,1,vv);
  Rename_T_INC();
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_SWP(int idx1,int idx2)
#else
Rename_BiSeq_SWP(idx1,idx2)
int idx1,idx2;
#endif
{
  int count,ii,jj,v1,v2;
  count = 1;
  Rename_I_VAL(&ii);
  while( count<idx1 ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_B_BiRcd_VAL(&jj,ii,val_obj);
  Rename_V_BiRcd_VAL(&v1,jj,1);
  count = 1;
  Rename_I_VAL(&ii);
  while( count<idx2 ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_B_BiRcd_VAL(&ii,ii,val_obj);
  Rename_V_BiRcd_VAL(&v2,ii,1);
  Rename_V_BiRcd_STO(ii,1,v1);
  Rename_V_BiRcd_STO(jj,1,v2);
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_PUSH(int vv)
#else
Rename_BiSeq_PUSH(vv)
int vv;
#endif
{
  int ii,jj;
  Rename_I_VAL(&ii);
  Rename_B_BiRcd_CRE(&jj);
  Rename_I_STO(jj);
  Rename_B_BiRcd_STO(jj,next_byt_obj,ii);
  Rename_V_BiRcd_CRE(&ii);
  Rename_V_BiRcd_STO(ii,1,vv);
  Rename_B_BiRcd_STO(jj,val_obj,ii);
  Rename_T_INC();
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_APP(int vv)
#else
Rename_BiSeq_APP(vv)
int vv;
#endif
{
  int count,len,ii,jj;
  count = 1;
  Rename_T_VAL(&len);
  if( len == 0 ){
    Rename_B_BiRcd_CRE(&ii);
    Rename_V_BiRcd_CRE(&jj);
    Rename_V_BiRcd_STO(jj,1,vv);
    Rename_B_BiRcd_STO(ii,val_obj,jj);
    Rename_I_STO(ii);
  }else{
    Rename_I_VAL(&ii);
    while( count<len ){
      Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
      BINC(&count,count);
    };
    Rename_B_BiRcd_CRE(&jj);
    Rename_B_BiRcd_STO(ii,next_byt_obj,jj);
    Rename_V_BiRcd_CRE(&ii);
    Rename_V_BiRcd_STO(ii,1,vv);
    Rename_B_BiRcd_STO(jj,val_obj,ii);
  };
  Rename_T_INC();
}

void
Rename_BiSeq_POP()
{
  int ii,jj;
  Rename_I_VAL(&ii);
  Rename_B_BiRcd_VAL(&jj,ii,next_byt_obj);
  Rename_I_STO(jj);
  Rename_B_BiRcd_VAL(&jj,ii,val_obj);
  Rename_V_BiRcd_KILL(jj);
  Rename_B_BiRcd_KILL(ii);
  Rename_T_DEC();
}

void
Rename_BiSeq_FRONT()
{
  int count,len,ii,jj;
  count = 1;
  Rename_T_VAL(&len);
  Rename_I_VAL(&ii);
  while( count<len ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_B_BiRcd_VAL(&jj,ii,val_obj);
  Rename_V_BiRcd_KILL(jj);
  Rename_B_BiRcd_KILL(ii);
  Rename_T_DEC();
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_DEL(int idx)
#else
Rename_BiSeq_DEL(idx)
int idx;
#endif
{
  int count,ii,jj,kk;
  Rename_I_VAL(&ii);
  if( idx == 1 ){
    Rename_B_BiRcd_VAL(&jj,ii,next_byt_obj);
    Rename_I_STO(jj);
    Rename_B_BiRcd_VAL(&jj,ii,val_obj);
    Rename_V_BiRcd_KILL(jj);
    Rename_B_BiRcd_KILL(ii);
  }else{
    count = 1;
    jj = ii;
    while( count<idx ){
      jj = ii;
      Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
      BINC(&count,count);
    };
    Rename_B_BiRcd_VAL(&kk,ii,next_byt_obj);
    Rename_B_BiRcd_STO(jj,next_byt_obj,kk);
    Rename_B_BiRcd_VAL(&jj,ii,val_obj);
    Rename_V_BiRcd_KILL(jj);
    Rename_B_BiRcd_KILL(ii);
  };
  Rename_T_DEC();
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_RTN(int idx)
#else
Rename_BiSeq_RTN(idx)
int idx;
#endif
{
  int count,ii,jj,len;
  count = 0;
  Rename_I_VAL(&ii);
  while( count<idx ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_T_VAL(&len);
  while( count<len ){
    Rename_B_BiRcd_VAL(&jj,ii,val_obj);
    Rename_V_BiRcd_KILL(jj);
    jj = ii;
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    Rename_B_BiRcd_KILL(jj);
    BINC(&count,count);
  };
  Rename_T_STO(idx);
}

void
#ifdef _BT_ANSIC
Rename_BiSeq_RMV(int idx)
#else
Rename_BiSeq_RMV(idx)
int idx;
#endif
{
  int count,ii,jj;
  count = 0;
  Rename_I_VAL(&ii);
  while( count<idx ){
    Rename_B_BiRcd_VAL(&jj,ii,val_obj);
    Rename_V_BiRcd_KILL(jj);
    jj = ii;
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    Rename_B_BiRcd_KILL(jj);
    BINC(&count,count);
  };
  Rename_I_STO(ii);
  Rename_T_SUB(idx);
}

