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
int is_win;
char name_win[101];
FILE *ff_win;
open_winfunc()
#define open_win open_winfunc()
{
  if( is_win==TRUE ){
    redirect_trm(name_win); 
/* freopen(name_win,"w",bstdout); */
    write_top_clear_res;
  } 
}

open_men_winfunc()
#define open_men_win open_men_winfunc()
{
  if( is_win==TRUE ){
    redirect_trm(name_win);
/* freopen(name_win,"w",bstdout); */
  } 
}

clos_winfunc()
#define clos_win clos_winfunc()
{
  if( is_win==TRUE ){
    reset_trm;
/* freopen(TERMINAL,"w",bstdout); */
  } 
}

sho_winfunc()
#define sho_win sho_winfunc()
{register int i ;
  fprintf ( bstdout, "                  Menu Window: ");   
  if( is_win==TRUE ){
    i=0;
    while( name_win[i]!='\0' ){
      putc(name_win[i], bstdout);
      i=i+1;
    } 
    fprintf ( bstdout, "\n");
  } else {
    fprintf ( bstdout, "\n");
  } 
}

ass_winfunc()
#define ass_win ass_winfunc()
{register int i,c ;  
  i=0;
  while( !(access("win",R_OK) >= 0) ){
    sleep ( 1 );
  } 
  while( is_win==FALSE ){
    ff_win=fopen("win","r");
    if ( ff_win == NULL ) {
      fprintf ( bstdout, "\n\n             Can't open \"win\" for reading\n\n" );
      exit___ ( 1 );
    } 
    i=0;
    c=getc(ff_win);
    while( c!=EOF ){
      i=i+1;
      name_win[i-1]=c;
      c=getc(ff_win);
    } 
    if( i>2 ){
      if( name_win[i-2]=='?' ){
        name_win[i-3]='\0';
        is_win=TRUE;
/*   commented out (at Dave's request) for B Toolkit */
        fprintf ( bstdout, "\n");
        sho_win;
      } 
    } 
    fclose(ff_win);
    system ( "rm -f win" );
  } 
}

ini_winfunc()
#define ini_win ini_winfunc()
{
  is_win=FALSE;
  if( val_men_sys==TRUE ){
    ass_win;
  } 
}
