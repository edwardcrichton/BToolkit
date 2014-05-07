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
#define itr_set(t,v,p,s)  stp=stp+1;  if( t<=0 ){ stack[stp-1]=(-t) ;} else { stack[stp-1]=len(t) ;};  while( stack[stp-1]>0 ){  if( t<=0 ){ v=stack[stp-1] ;} else { v=val(t,stack[stp-1]) ;};  if( p ){ s ;};  stack[stp-1]=stack[stp-1]-1  ;};  stp=stp-1
  

#define exist_set(t,v,p,s1,s2)  stp=stp+1;  if( t<=0 ){ stack[stp-1]=(-t) ;} else { stack[stp-1]=len(t) ;};  while( stack[stp-1]>0 ){  if( t<=0 ){ v=stack[stp-1] ;} else { v=val(t,stack[stp-1]) ;};  if( p ){  s1; stack[stp-1]=(-stack[stp-1])  ;} else {  stack[stp-1]=stack[stp-1]-1  ;}  ;};  if( stack[stp-1]==0 ){ s2 ;};  stp=stp-1

#define add_set(a,v) if( mbr(a,v)==FALSE ){ psh(a,v) ;}

#define is_in_set(s,x) mbr(s,x)
del_set(a,v)
{register int jj ;
  jj = idx(a,v); 
  if( !(jj==0) ){ 
    str(a,jj,val(a,len(a)));
    pop(a) ;
  }
}

union_set(s,t)
{register int i,v ;
  itr(t,i,v,add_set(s,v));
}

inter_set(s,t)
{register int i ;
  i=1;
  while( i!=len(s)+1 ){
    if( idx(t,val(s,i))==0 ){
      str(s,i,val(s,len(s)));
      pop(s);
    } else {
      i=i+1;
    }
  }
}

diff_set(s,t)
{register int i,v ;
  itr(t,i,v,del_set(s,v));
}

