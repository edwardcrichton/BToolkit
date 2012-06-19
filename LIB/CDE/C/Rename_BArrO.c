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
#include "Rename_BArrO.h"

#include "Rename_C_UiArr.h"
#include "Rename_M_Byt.h"
#include "Rename_O_BiArr.h"

#include "Bool_TYPE.h"
#include "PASP_TYPE.h"

INI_Rename_BArrO()
{
  INI_Rename_C_UiArr();
  INI_Rename_M_Byt();
  INI_Rename_O_BiArr();
}

Rename_BAO_OBJ_FUL(bb)
int *bb;
{
  int obj;
  Rename_M_VAL(&obj);
  if( obj == Rename_BArrOP1 ){
    *bb = TRUE;
  } else {
    *bb = FALSE;
  }
}

Rename_BAO_XST(bb,pp)
int *bb,pp;
{
  int tok,xx,yy;
  Rename_M_VAL(&tok);
  BNE(&xx,0,tok);
  BLE(&yy,pp,tok);
  if( xx == TRUE && yy == TRUE ){
    *bb = TRUE;
  } else {
    *bb = FALSE;
  }
}

Rename_BAO_INI()
{
  Rename_M_STO(0);
}

Rename_BAO_CRE(bb,pp)
int *bb,*pp;
{
  int tt,tok;
  Rename_M_VAL(&tt);
  if( tt!=Rename_BArrOP1 ){
    BINC(&tok,tt);
    Rename_M_STO(tok);
    Rename_O_STO(tok,lb);
    *pp = tok;
    *bb = TRUE;
  } else {
    *bb = FALSE;
    *pp = 0;
  }
}

Rename_BAO_VAL(vv,pp,ii)
int *vv,pp,ii;
{
  int seg,idx;
  BDEC(&seg,pp);
  UMUL(&idx,seg,Rename_BArrOP2);
  UADD(&idx,idx,ii);
  Rename_C_VAL(vv,idx);
}

Rename_BAO_NXT(nn,pp)
int *nn,pp;
{
  Rename_O_VAL(nn,pp);
}

Rename_BAO_EQL(bb,ss,tt)
int *bb,ss,tt;
{
  int idx,offset,seg,top,xidx,xoffset,xseg,v1,v2,pp,qq;
  BDEC(&seg,ss);
  UMUL(&offset,Rename_BArrOP2,seg);
  UINC(&idx,offset);
  UADD(&top,offset,Rename_BArrOP2);
  BDEC(&xseg,tt);
  UMUL(&xoffset,Rename_BArrOP2,xseg);
  UINC(&xidx,xoffset);
  pp = TRUE;
  while( pp == TRUE ){
    Rename_C_VAL(&v1,idx);
    Rename_C_VAL(&v2,xidx);
    UINC(&idx,idx);
    UINC(&xidx,xidx);
    ULE(&pp,idx,top);
    BEQ(&qq,v1,v2);
    if( pp == TRUE && qq == TRUE ){
      pp = TRUE;
    } else {
      pp = FALSE;
    }
  };
  Rename_O_STO(ss,lb);
  Rename_O_STO(tt,lb);
  *bb = qq;
}

Rename_BAO_STO(pp,ii,vv)
int pp,ii,vv;
{
  int nx,offset,seg,index;
  BDEC(&seg,pp);
  UMUL(&offset,Rename_BArrOP2,seg);
  UADD(&index,offset,ii);
  Rename_C_STO(index,vv);
  UINC(&nx,ii);
  if( nx<Rename_BArrOP2 ){
    Rename_O_STO(pp,nx);
  }else{
    Rename_O_STO(pp,lb);
  }
}

Rename_BAO_STO_NXT(pp,vv)
int pp,vv;
{
  int nx,offset,seg,index,ii;
  BDEC(&seg,pp);
  UMUL(&offset,Rename_BArrOP2,seg);
  Rename_O_VAL(&ii,pp);
  UADD(&index,offset,ii);
  Rename_C_STO(index,vv);
  UINC(&nx,ii);
  if( nx<Rename_BArrOP2 ){
    Rename_O_STO(pp,nx);
  }else{
    Rename_O_STO(pp,lb);
  }
}

Rename_BAO_CPY(pp,qq)
int pp,qq;
{
  int idx,offset,seg,top,xidx,xoffset,xseg,vv;
  BDEC(&seg,pp);
  UMUL(&offset,Rename_BArrOP2,seg);
  UINC(&idx,offset);
  UADD(&top,offset,Rename_BArrOP2);
  BDEC(&xseg,qq);
  UMUL(&xoffset,Rename_BArrOP2,xseg);
  UINC(&xidx,xoffset);
  while( idx<=top ){
    Rename_C_VAL(&vv,idx);
    Rename_C_STO(xidx,vv);
    UINC(&idx,idx);
    UINC(&xidx,xidx);
  };
  Rename_O_STO(pp,lb);
  Rename_O_STO(qq,lb);
}

Rename_BAO_FILL(pp,vv)
int pp,vv;
{
  int idx,offset,seg,top;
  BDEC(&seg,pp);
  UMUL(&offset,Rename_BArrOP2,seg);
  UINC(&idx,offset);
  UADD(&top,offset,Rename_BArrOP2);
  while( idx<=top ){
    Rename_C_STO(idx,vv);
    UINC(&idx,idx);
  };
  Rename_O_STO(pp,lb);
}

