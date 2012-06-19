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
#include "Rename_UiSeq.h"

#define val_obj 1
#define next_uns_obj 2

#include "Rename_B_UiRcd.h"
#include "Rename_V_UiRcd.h"
#include "Rename_I_Uns.h"
#include "Rename_T_Uns.h"

#include "Bool_TYPE.h"
#include "Uns_TYPE.h"

INI_Rename_UiSeq()
{
  INI_Rename_B_UiRcd();
  INI_Rename_V_UiRcd();
  INI_Rename_I_Uns();
  INI_Rename_T_Uns();
  Rename_T_STO(0);
  Rename_I_STO(1);
}

/* ANSIC header */
Rename_UiSeq_FULL(int *bb)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_FULL(bb)
int *bb;
/* end non-ANSIC header */
{
  int len;
  Rename_T_VAL(&len);
  UEQ(bb,len,Rename_UiSeqP2);
}

/* ANSIC header */
Rename_UiSeq_IDX(int *bb, int idx)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_IDX(bb,idx)
int *bb,idx;
/* end non-ANSIC header */
{
  int len,tt;
  UGT(&tt,idx,MinUns);
  if( tt == TRUE ){
    Rename_T_VAL(&len);
    ULE(&tt,idx,len);
  };
  *bb = tt;
}

/* ANSIC header */
Rename_UiSeq_LEN(int *ll)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_LEN(ll)
int *ll;
/* end non-ANSIC header */
{

  Rename_T_VAL(ll);
}

/* ANSIC header */
Rename_UiSeq_FRST(int *vv)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_FRST(vv)
int *vv;
/* end non-ANSIC header */
{
  int ii;
  Rename_I_VAL(&ii);
  Rename_V_UiRcd_VAL(vv,ii,val_obj);
}

/* ANSIC header */
Rename_UiSeq_LAST(int *vv)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_LAST(vv)
int *vv;
/* end non-ANSIC header */
{
  int count,len,ii;
  count = 1;
  Rename_T_VAL(&len);
  Rename_I_VAL(&ii);
  while( count<len ){
    Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
    UINC(&count,count);
  };
  Rename_V_UiRcd_VAL(vv,ii,val_obj);
}

/* ANSIC header */
Rename_UiSeq_VAL(int *vv,int idx)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_VAL(vv,idx)
int *vv,idx;
/* end non-ANSIC header */
{
  int ii,count;
  count = 1;
  Rename_I_VAL(&ii);
  while( count<idx ){
    Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
    UINC(&count,count);
  };
  Rename_V_UiRcd_VAL(vv,ii,val_obj);
}

Rename_UiSeq_CLR()
{
  int count,len,ii,jj;
  count = 0;
  Rename_I_VAL(&ii);
  jj = ii;
  Rename_T_VAL(&len);
  while( count<len ){
    Rename_B_UiRcd_VAL(&jj,ii,val_obj);
    Rename_V_UiRcd_KILL(jj);
    jj = ii;
    Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
    Rename_B_UiRcd_KILL(jj);
    UINC(&count,count);
  };
  Rename_T_STO(0);
  Rename_I_STO(jj);
}

/* ANSIC header */
Rename_UiSeq_FILL(int len,int vv)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_FILL(len,vv)
int len,vv;
/* end non-ANSIC header */
{
  int count,ii,jj,kk;
  Rename_B_UiRcd_CRE(&ii);
  Rename_V_UiRcd_CRE(&jj);
  Rename_V_UiRcd_STO(jj,1,vv);
  Rename_B_UiRcd_STO(ii,val_obj,jj);
  Rename_I_STO(ii);
  count = 1;
  while( count<len ){
    Rename_B_UiRcd_CRE(&kk);
    Rename_V_UiRcd_CRE(&jj);
    Rename_V_UiRcd_STO(jj,1,vv);
    Rename_B_UiRcd_STO(ii,next_uns_obj,kk);
    Rename_B_UiRcd_STO(kk,val_obj,jj);
    ii = kk;
    UINC(&count,count);
  };
  Rename_T_STO(len);
}

/* ANSIC header */
Rename_UiSeq_STO(int idx,int vv)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_STO(idx,vv)
int idx,vv;
/* end non-ANSIC header */
{
  int count,ii;
  count = 1;
  Rename_I_VAL(&ii);
  while( count<idx ){
    Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
    UINC(&count,count);
  };
  Rename_V_UiRcd_STO(ii,val_obj,vv);
}

/* ANSIC header */
Rename_UiSeq_INS(int idx,int vv)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_INS(idx,vv)
int idx,vv;
/* end non-ANSIC header */
{
  int count,ii,jj,kk;
  count = 1;
  Rename_I_VAL(&ii);
  kk = ii;
  while( count<idx ){
    kk = ii;
    Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
    UINC(&count,count);
  };
  Rename_B_UiRcd_CRE(&jj);
  Rename_B_UiRcd_STO(kk,next_uns_obj,jj);
  Rename_B_UiRcd_STO(jj,next_uns_obj,ii);
  Rename_V_UiRcd_CRE(&ii);
  Rename_B_UiRcd_STO(jj,val_obj,ii);
  Rename_V_UiRcd_STO(ii,1,vv);
  Rename_T_INC();
}

/* ANSIC header */
Rename_UiSeq_SWP(int idx1,int idx2)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_SWP(idx1,idx2)
int idx1,idx2;
/* end non-ANSIC header */
{
  int count,ii,jj,v1,v2;
  count = 1;
  Rename_I_VAL(&ii);
  while( count<idx1 ){
    Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
    UINC(&count,count);
  };
  Rename_B_UiRcd_VAL(&jj,ii,val_obj);
  Rename_V_UiRcd_VAL(&v1,jj,1);
  count = 1;
  Rename_I_VAL(&ii);
  while( count<idx2 ){
    Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
    UINC(&count,count);
  };
  Rename_B_UiRcd_VAL(&ii,ii,val_obj);
  Rename_V_UiRcd_VAL(&v2,ii,1);
  Rename_V_UiRcd_STO(ii,1,v1);
  Rename_V_UiRcd_STO(jj,1,v2);
}

/* ANSIC header */
Rename_UiSeq_PUSH(int vv)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_PUSH(vv)
int vv;
/* end non-ANSIC header */
{
  int ii,jj;
  Rename_I_VAL(&ii);
  Rename_B_UiRcd_CRE(&jj);
  Rename_I_STO(jj);
  Rename_B_UiRcd_STO(jj,next_uns_obj,ii);
  Rename_V_UiRcd_CRE(&ii);
  Rename_V_UiRcd_STO(ii,1,vv);
  Rename_B_UiRcd_STO(jj,val_obj,ii);
  Rename_T_INC();
}

/* ANSIC header */
Rename_UiSeq_APP(int vv)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_APP(vv)
int vv;
/* end non-ANSIC header */
{
  int count,len,ii,jj;
  count = 1;
  Rename_T_VAL(&len);
  if( len == 0 ){
    Rename_B_UiRcd_CRE(&ii);
    Rename_V_UiRcd_CRE(&jj);
    Rename_V_UiRcd_STO(jj,1,vv);
    Rename_B_UiRcd_STO(ii,val_obj,jj);
    Rename_I_STO(ii);
  }else{
    Rename_I_VAL(&ii);
    while( count<len ){
      Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
      UINC(&count,count);
    };
    Rename_B_UiRcd_CRE(&jj);
    Rename_B_UiRcd_STO(ii,next_uns_obj,jj);
    Rename_V_UiRcd_CRE(&ii);
    Rename_V_UiRcd_STO(ii,1,vv);
    Rename_B_UiRcd_STO(jj,val_obj,ii);
  };
  Rename_T_INC();
}

Rename_UiSeq_POP()
{
  int ii,jj;
  Rename_I_VAL(&ii);
  Rename_B_UiRcd_VAL(&jj,ii,next_uns_obj);
  Rename_I_STO(jj);
  Rename_B_UiRcd_VAL(&jj,ii,val_obj);
  Rename_V_UiRcd_KILL(jj);
  Rename_B_UiRcd_KILL(ii);
  Rename_T_DEC();
}

Rename_UiSeq_FRONT()
{
  int count,len,ii,jj;
  count = 1;
  Rename_T_VAL(&len);
  Rename_I_VAL(&ii);
  while( count<len ){
    Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
    UINC(&count,count);
  };
  Rename_B_UiRcd_VAL(&jj,ii,val_obj);
  Rename_V_UiRcd_KILL(jj);
  Rename_B_UiRcd_KILL(ii);
  Rename_T_DEC();
}

/* ANSIC header */
Rename_UiSeq_DEL(int idx)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_DEL(idx)
int idx;
/* end non-ANSIC header */
{
  int count,ii,jj,kk;
  Rename_I_VAL(&ii);
  if( idx == 1 ){
    Rename_B_UiRcd_VAL(&jj,ii,next_uns_obj);
    Rename_I_STO(jj);
    Rename_B_UiRcd_VAL(&jj,ii,val_obj);
    Rename_V_UiRcd_KILL(jj);
    Rename_B_UiRcd_KILL(ii);
  }else{
    count = 1;
    jj = ii;
    while( count<idx ){
      jj = ii;
      Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
      UINC(&count,count);
    };
    Rename_B_UiRcd_VAL(&kk,ii,next_uns_obj);
    Rename_B_UiRcd_STO(jj,next_uns_obj,kk);
    Rename_B_UiRcd_VAL(&jj,ii,val_obj);
    Rename_V_UiRcd_KILL(jj);
    Rename_B_UiRcd_KILL(ii);
  };
  Rename_T_DEC();
}

/* ANSIC header */
Rename_UiSeq_RTN(int idx)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_RTN(idx)
int idx;
/* end non-ANSIC header */
{
  int count,ii,jj,len;
  count = 0;
  Rename_I_VAL(&ii);
  while( count<idx ){
    Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
    UINC(&count,count);
  };
  Rename_T_VAL(&len);
  while( count<len ){
    Rename_B_UiRcd_VAL(&jj,ii,val_obj);
    Rename_V_UiRcd_KILL(jj);
    jj = ii;
    Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
    Rename_B_UiRcd_KILL(jj);
    UINC(&count,count);
  };
  Rename_T_STO(idx);
}

/* ANSIC header */
Rename_UiSeq_RMV(int idx)
/* end ANSIC header */

/* non-ANSIC header */
Rename_UiSeq_RMV(idx)
int idx;
/* end non-ANSIC header */
{
  int count,ii,jj;
  count = 0;
  Rename_I_VAL(&ii);
  while( count<idx ){
    Rename_B_UiRcd_VAL(&jj,ii,val_obj);
    Rename_V_UiRcd_KILL(jj);
    jj = ii;
    Rename_B_UiRcd_VAL(&ii,ii,next_uns_obj);
    Rename_B_UiRcd_KILL(jj);
    UINC(&count,count);
  };
  Rename_I_STO(ii);
  Rename_T_SUB(idx);
}

