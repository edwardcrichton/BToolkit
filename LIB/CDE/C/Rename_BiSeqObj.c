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
#include "Rename_BiSeqObj.h"

#define val_obj 1
#define next_byt_obj 2

#include "Rename_B_BiRcd.h"
#include "Rename_V_BiRcd.h"
#include "Rename_I_BiArr.h"
#include "Rename_S_BiArr.h"
#include "Rename_H_BiArr.h"
#include "Rename_TOT_Byt.h"

#include "Bool_TYPE.h"
#include "Byt_TYPE.h"

INI_Rename_BiSeqObj()
{
  INI_Rename_B_BiRcd();
  INI_Rename_V_BiRcd();
  INI_Rename_I_BiArr();
  INI_Rename_S_BiArr();
  INI_Rename_H_BiArr();
  INI_Rename_TOT_Byt();
  {
    int ii;
    ii = 0;
    while( ii<Rename_BiSeqObjP2 ){
      Rename_H_STO(ii,ii);
      Rename_S_STO(ii,0);
      Rename_I_STO(ii,0);
      BINC(&ii,ii);
    };
    Rename_TOT_STO(0);
  }
}

Rename_BiSeqObj_FULL_MEM(bb)
int *bb;
{
  int ii,tt,objtot,tot;
  Rename_TOT_VAL(&objtot);
  ii = 0;
  tot = 0;
  while( ii<objtot ){
    Rename_S_VAL(&tt,ii);
    BADD(&tot,tot,tt);
    BINC(&ii,ii);
  };
  BEQ(bb,tot,Rename_BiSeqObjP3);
}

Rename_BiSeqObj_FULL_OBJ(bb)
int *bb;
{
  int totobj;
  Rename_TOT_VAL(&totobj);
  BEQ(bb,totobj,Rename_BiSeqObjP2);
}

Rename_BiSeqObj_CRE(obj)
int *obj;
{
  int ii,ss;
  Rename_TOT_VAL(&ii);
  Rename_H_VAL(&ss,ii);
  Rename_S_STO(ss,0);
  Rename_TOT_INC();
  BINC(&ss,ss);
  *obj = ss;
}

Rename_BiSeqObj_KILL(obj)
int obj;
{
  int ii,jj,kk,len,count;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&len,ii);
  Rename_S_STO(ii,0);
  Rename_I_VAL(&ii,ii);
  kk = ii;
  count = 0;
  while( count<len ){
    Rename_B_BiRcd_VAL(&jj,ii,val_obj);
    Rename_V_BiRcd_KILL(jj);
    jj = ii;
    Rename_B_BiRcd_VAL(&ii,jj,next_byt_obj);
    Rename_B_BiRcd_KILL(jj);
    BINC(&count,count);
  };
  Rename_TOT_DEC();
}

Rename_BiSeqObj_VLD_OBJ(bb,obj)
int *bb,obj;
{
  int ii,objtot,aa,oo;
  Rename_TOT_VAL(&objtot);
  ii = Rename_BiSeqObjP2;
  if( obj>=1 && obj<=Rename_BiSeqObjP2 ){
    aa = TRUE;
  } else {
    aa = FALSE;
  };
  while( aa == TRUE && ii>objtot ){
    BDEC(&ii,ii);
    Rename_H_VAL(&oo,ii);
    BINC(&oo,oo);
    if( oo == obj ){
      aa = FALSE;
    }
  };
  *bb = aa;
}

Rename_BiSeqObj_VLD_IDX(bb,obj,idx)
int *bb,obj,idx;
{
  int ii,objtot,aa,oo,len;
  Rename_TOT_VAL(&objtot);
  ii = Rename_BiSeqObjP2;
  if( idx>=1 && obj>=1 && obj<=Rename_BiSeqObjP2 ){
    aa = TRUE;
  } else {
    aa = FALSE;
  };
  while( aa == TRUE && ii>objtot ){
    BDEC(&ii,ii);
    Rename_H_VAL(&oo,ii);
    BINC(&oo,oo);
    if( oo == obj ){
      aa = FALSE;
    }
  };
  if( aa == TRUE ){
    BDEC(&ii,obj);
    Rename_H_VAL(&ii,ii);
    Rename_S_VAL(&len,ii);
    BLE(&aa,idx,len);
  };
  *bb = aa;
}

Rename_BiSeqObj_OBJ_TOT(tt)
int *tt;
{
  Rename_TOT_VAL(tt);
}

Rename_BiSeqObj_LEN(ll,obj)
int *ll,obj;
{
  int ii;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(ll,ii);
}

Rename_BiSeqObj_FRST(vv,obj)
int *vv,obj;
{
  int ii;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_I_VAL(&ii,ii);
  Rename_B_BiRcd_VAL(&ii,ii,val_obj);
  Rename_V_BiRcd_VAL(vv,ii,1);
}

Rename_BiSeqObj_LAST(vv,obj)
int *vv,obj;
{
  int ii,len,count;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&len,ii);
  Rename_I_VAL(&ii,ii);
  count = 1;
  while( count<len ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_B_BiRcd_VAL(&ii,ii,val_obj);
  Rename_V_BiRcd_VAL(vv,ii,1);
}

Rename_BiSeqObj_VAL(vv,obj,idx)
int *vv,obj,idx;
{
  int ii,count;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_I_VAL(&ii,ii);
  count = 1;
  while( count<idx ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_B_BiRcd_VAL(&ii,ii,val_obj);
  Rename_V_BiRcd_VAL(vv,ii,1);
}

Rename_BiSeqObj_CLR(obj)
int obj;
{
  int ii,jj,kk,len,count;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&len,ii);
  Rename_S_STO(ii,0);
  kk = ii;
  Rename_I_VAL(&ii,ii);
  jj = ii;
  count = 0;
  while( count<len ){
    Rename_B_BiRcd_VAL(&jj,ii,val_obj);
    Rename_V_BiRcd_KILL(jj);
    jj = ii;
    Rename_B_BiRcd_VAL(&ii,jj,next_byt_obj);
    Rename_B_BiRcd_KILL(jj);
    BINC(&count,count);
  };
  Rename_I_STO(kk,jj);
}

Rename_BiSeqObj_STO(obj,idx,vv)
int obj,idx,vv;
{
  int ii,count;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_I_VAL(&ii,ii);
  count = 1;
  while( count<idx ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_B_BiRcd_VAL(&ii,ii,val_obj);
  Rename_V_BiRcd_STO(ii,1,vv);
}

Rename_BiSeqObj_INS(obj,idx,vv)
int obj,idx,vv;
{
  int ii,jj,kk,count;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&jj,ii);
  BINC(&jj,jj);
  Rename_S_STO(ii,jj);
  Rename_I_VAL(&ii,ii);
  count = 2;
  while( count<idx ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_B_BiRcd_VAL(&jj,ii,next_byt_obj);
  Rename_B_BiRcd_CRE(&kk);
  Rename_B_BiRcd_STO(ii,next_byt_obj,kk);
  Rename_B_BiRcd_STO(kk,next_byt_obj,jj);
  Rename_V_BiRcd_CRE(&jj);
  Rename_B_BiRcd_STO(kk,val_obj,jj);
  Rename_V_BiRcd_STO(jj,1,vv);
}

Rename_BiSeqObj_SWP(obj,idx1,idx2)
int obj,idx1,idx2;
{
  int ii,kk,count,j1,j2,k1,k2;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_I_VAL(&ii,ii);
  kk = ii;
  count = 1;
  while( count<idx1 ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  j1 = ii;
  Rename_B_BiRcd_VAL(&k1,j1,val_obj);
  ii = kk;
  count = 1;
  while( count<idx2 ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  j2 = ii;
  Rename_B_BiRcd_VAL(&k2,j2,val_obj);
  Rename_B_BiRcd_STO(j2,val_obj,k1);
  Rename_B_BiRcd_STO(j1,val_obj,k2);
}

Rename_BiSeqObj_PUSH(obj,vv)
int obj,vv;
{
  int ii,jj,kk;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&jj,ii);
  BINC(&jj,jj);
  Rename_S_STO(ii,jj);
  Rename_I_VAL(&jj,ii);
  Rename_B_BiRcd_CRE(&kk);
  Rename_I_STO(ii,kk);
  Rename_B_BiRcd_STO(kk,next_byt_obj,jj);
  Rename_V_BiRcd_CRE(&ii);
  Rename_V_BiRcd_STO(ii,1,vv);
  Rename_B_BiRcd_STO(kk,val_obj,ii);
}

Rename_BiSeqObj_APP(obj,vv)
int obj,vv;
{
  int ii,jj,kk,len,count;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&len,ii);
  BINC(&jj,len);
  Rename_S_STO(ii,jj);
  if( len == 0 ){
    Rename_B_BiRcd_CRE(&kk);
    Rename_V_BiRcd_CRE(&jj);
    Rename_V_BiRcd_STO(jj,1,vv);
    Rename_B_BiRcd_STO(kk,val_obj,jj);
    Rename_I_STO(ii,kk);
  }else{
    Rename_I_VAL(&ii,ii);
    count = 1;
    while( count<len ){
      Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
      BINC(&count,count);
    };
    Rename_B_BiRcd_CRE(&jj);
    Rename_B_BiRcd_STO(ii,next_byt_obj,jj);
    Rename_V_BiRcd_CRE(&ii);
    Rename_V_BiRcd_STO(ii,1,vv);
    Rename_B_BiRcd_STO(jj,val_obj,ii);
  }
}

Rename_BiSeqObj_POP(obj)
int obj;
{
  int ii,jj,kk;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&jj,ii);
  BDEC(&jj,jj);
  Rename_S_STO(ii,jj);
  Rename_I_VAL(&jj,ii);
  Rename_B_BiRcd_VAL(&kk,jj,val_obj);
  Rename_V_BiRcd_KILL(kk);
  Rename_B_BiRcd_VAL(&kk,jj,next_byt_obj);
  Rename_I_STO(ii,kk);
  Rename_B_BiRcd_KILL(jj);
}

Rename_BiSeqObj_FRONT(obj)
int obj;
{
  int ii,jj,len,count;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&len,ii);
  BDEC(&len,len);
  Rename_S_STO(ii,len);
  Rename_I_VAL(&ii,ii);
  count = 0;
  while( count<len ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  Rename_B_BiRcd_VAL(&jj,ii,val_obj);
  Rename_V_BiRcd_KILL(jj);
  Rename_B_BiRcd_KILL(ii);
}

Rename_BiSeqObj_DEL(obj,idx)
int obj,idx;
{
  int ii,jj,kk,count;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&jj,ii);
  BDEC(&jj,jj);
  Rename_S_STO(ii,jj);
  Rename_I_VAL(&jj,ii);
  if( idx == 1 ){
    Rename_B_BiRcd_VAL(&kk,jj,val_obj);
    Rename_V_BiRcd_KILL(kk);
    Rename_B_BiRcd_VAL(&kk,jj,next_byt_obj);
    Rename_I_STO(ii,kk);
    Rename_B_BiRcd_KILL(jj);
  }else{
    ii = jj;
    count = 1;
    while( count<idx ){
      ii = jj;
      Rename_B_BiRcd_VAL(&jj,jj,next_byt_obj);
      BINC(&count,count);
    };
    Rename_B_BiRcd_VAL(&kk,jj,next_byt_obj);
    Rename_B_BiRcd_STO(ii,next_byt_obj,kk);
    Rename_B_BiRcd_VAL(&kk,jj,val_obj);
    Rename_V_BiRcd_KILL(kk);
    Rename_B_BiRcd_KILL(jj);
  }
}

Rename_BiSeqObj_RTN(obj,idx)
int obj,idx;
{
  int ii,jj,len,count;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&len,ii);
  Rename_S_STO(ii,idx);
  Rename_I_VAL(&ii,ii);
  count = 0;
  while( count<idx ){
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    BINC(&count,count);
  };
  while( count<len ){
    Rename_B_BiRcd_VAL(&jj,ii,val_obj);
    Rename_V_BiRcd_KILL(jj);
    jj = ii;
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    Rename_B_BiRcd_KILL(jj);
    BINC(&count,count);
  }
}

Rename_BiSeqObj_RMV(obj,idx)
int obj,idx;
{
  int ii,jj,kk,len,count;
  BDEC(&ii,obj);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&len,ii);
  BSUB(&len,len,idx);
  Rename_S_STO(ii,len);
  kk = ii;
  Rename_I_VAL(&ii,ii);
  count = 0;
  while( count<idx ){
    Rename_B_BiRcd_VAL(&jj,ii,val_obj);
    Rename_V_BiRcd_KILL(jj);
    jj = ii;
    Rename_B_BiRcd_VAL(&ii,jj,next_byt_obj);
    Rename_B_BiRcd_KILL(jj);
    BINC(&count,count);
  };
  Rename_I_STO(kk,ii);
}

Rename_BiSeqObj_CPY(obj1,obj2)
int obj1,obj2;
{
  int ii,jj,kk,ll,mm,len,count,vv;
  BDEC(&ii,obj1);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&len,ii);
  Rename_I_VAL(&ii,ii);
  BDEC(&kk,obj2);
  Rename_H_VAL(&kk,kk);
  Rename_S_STO(kk,len);
  mm = kk;
  Rename_I_VAL(&kk,kk);
  count = 0;
  while( count<len ){
    Rename_B_BiRcd_VAL(&jj,ii,val_obj);
    Rename_V_BiRcd_VAL(&vv,jj,1);
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    Rename_V_BiRcd_CRE(&ll);
    Rename_V_BiRcd_STO(ll,1,vv);
    Rename_B_BiRcd_CRE(&jj);
    Rename_B_BiRcd_STO(jj,val_obj,ll);
    if( count == 0 ){
      Rename_I_STO(mm,jj);
    }else{
      Rename_B_BiRcd_STO(kk,next_byt_obj,jj);
    };
    kk = ll;
    BINC(&count,count);
  }
}

Rename_BiSeqObj_CAT(obj1,obj2)
int obj1,obj2;
{
  int ii,jj,kk,ll,mm,len1,len2,count,vv;
  BDEC(&ii,obj1);
  Rename_H_VAL(&ii,ii);
  Rename_S_VAL(&len1,ii);
  Rename_I_VAL(&ii,ii);
  BDEC(&kk,obj2);
  Rename_H_VAL(&kk,kk);
  Rename_S_VAL(&len2,kk);
  mm = kk;
  Rename_I_VAL(&kk,kk);
  count = 1;
  while( count<len2 ){
    Rename_B_BiRcd_VAL(&kk,kk,next_byt_obj);
    BINC(&count,count);
  };
  count = 0;
  while( count<len1 ){
    Rename_B_BiRcd_VAL(&jj,ii,val_obj);
    Rename_V_BiRcd_VAL(&vv,jj,1);
    Rename_B_BiRcd_VAL(&ii,ii,next_byt_obj);
    Rename_V_BiRcd_CRE(&ll);
    Rename_V_BiRcd_STO(ll,1,vv);
    Rename_B_BiRcd_CRE(&jj);
    Rename_B_BiRcd_STO(jj,val_obj,ll);
    if( len2 == 0 && count == 0 ){
      Rename_I_STO(mm,jj);
    }else{
      Rename_B_BiRcd_STO(kk,next_byt_obj,jj);
    };
    kk = jj;
    BINC(&count,count);
  };
  BADD(&len2,len2,len1);
  Rename_S_STO(mm,len2);
}

