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
int fdom[151];
int fval1[151];
int fval2[151];
int fval3[151];
int tfun;
                    
/*  PARTIAL FUNCTION MACHINE  */

#define clr_fnc           tfun=0
  
idx_fnc(v)
{register int i,r ;
  i=tfun;
  r=0;
  while( i!=r ){
    if( fdom[i]==v ){
      r=i;
    } else {
      i=i-1;
    }
  }
  return r;
}

#define in_dom_fnc(v)    ((idx_fnc(v)!=0)!=0)

#define val1_fnc(i)      fval1[i]

#define val2_fnc(i)      fval2[i]

#define val3_fnc(i)      fval3[i]

#define add_fnc(i,v,w,t) tfun=tfun+1; fdom[tfun]=i; fval1[tfun]=v; fval2[tfun]=w; fval3[tfun]=t

#define len_fnc          tfun

#define reset_fnc(i)     tfun=i
anti_restr_fnc(lv,le,lq,newlv,newle)
{register int i,v ;
  itr(lv,i,v,if( mbr(lq,v)==FALSE ){
               psh(newlv,v);
               psh(newle,val(le,i));
            });
}
