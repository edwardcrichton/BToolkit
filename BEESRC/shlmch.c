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
char cstr_shl[1001];
void sys_shlfunc()
#define sys_shl sys_shlfunc()
{register int st,i,v ;
  st=cre(1);
  fprintf ( bstdout, "Shell (0 to quit): ");
  read_str(st);
  while( len_str(st)==0 ){
    fprintf ( bstdout, "\n");
    fprintf ( bstdout, "Shell (0 to quit): ");
    read_str(st);
  }
  while( fst_str(st)!=ord('0') ){
    itr_str(st,i,v,cstr_shl[i-1]=chr(v));
    cstr_shl[len_str(st)]='\0';
    fprintf ( bstdout, "\n");
    system(cstr_shl);
    fprintf ( bstdout, "\n");
    fprintf ( bstdout, "Shell (0 to quit): ");
    read_str(st);
    while( len_str(st)==0 ){
      fprintf ( bstdout, "\n");
      fprintf ( bstdout, "Shell (0 to quit): ");
      read_str(st);
    }
  }
}
