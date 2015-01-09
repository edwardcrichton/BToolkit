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
char file_fic_buf [ 1000 ];

/*  ; return DONE  */
                
/*  FILE MACHINE DECLARATION  */
                
           
                
int fcol[5];
int fpre[5];
int file_fic,old_file_fic,file_exists_fic;
char fstr[1001];
FILE *ficxx;
FILE *ficxxtmp;
                    
/*  PROGRAMS FOR FILE MACHINE */
                    

#define col_fic(f)       fcol[f]

#define pre_fic(f)       fpre[f]
void trans_fic(s)
{register int l,x,i,v ;
  l=len_str(stri_sym(s));
  x=0;
  itr_str(stri_sym(s),i,v,
  if( (i!=1) && (i!=l) ){
    x=x+1;
    fstr[x-1]=chr(v)
 ;});
  fstr[x]='\0';
}

int rewrite_ficxxfunc()
#define rewrite_ficxx rewrite_ficxxfunc()
{register int rewrite_ficxx_res ;
  ficxxtmp=fopen(fstr,"w");
  if( ficxxtmp == NULL ){
    rewrite_ficxx_res=FALSE;
  } else {
    rewrite_ficxx_res=TRUE;
    ficxx=ficxxtmp;
  }
; return rewrite_ficxx_res;
}

int append_ficxxfunc()
#define append_ficxx append_ficxxfunc()
{register int p,append_ficxx_res ;
  ficxxtmp=fopen(fstr,"a");
  if( ficxxtmp == NULL ){
    append_ficxx_res=FALSE;
  } else {
    append_ficxx_res=TRUE;
    ficxx=ficxxtmp;
  }
; return append_ficxx_res;
}

void print_fic(s)
{
  if( file_fic==1 ){
    putc(s,stderr);
  } else if( (file_fic==2) || (file_fic==3) ){
    putc(s,bstdout);
#ifdef BTOOLM_FLAG
  } else if(file_fic==0){
    sprintf ( file_fic_buf, "%c", s );
    DisplayCurrWinText ( file_fic_buf );
  } else if(file_fic==-999){
    sprintf ( file_fic_buf, "%c", s );
    strcat ( str_buf, file_fic_buf );
#endif
  } else if( file_exists_fic == TRUE ){
    putc(s,ficxx);
  };
}

void write_srv_ficfunc()
#define write_srv_fic write_srv_ficfunc()
{
  if( file_fic==1 ){
    write_srv_err_res;
  } else if( (file_fic==2) || (file_fic==3) ){
    write_srv_res;
  };
}

void write_erv_ficfunc()
#define write_erv_fic write_erv_ficfunc()
{
  if( file_fic==1 ){
    write_erv_err_res;
  } else if( (file_fic==2) || (file_fic==3) ){
    write_erv_res;
  };
}

void write_nat_fic(n)
{
  if( file_fic==1 ){
    fprintf(stderr,"%d",n);
  } else if( (file_fic==2) || (file_fic==3) ){
    fprintf(bstdout,"%d",n);
#ifdef BTOOLM_FLAG
  } else if(file_fic==0){
    sprintf ( file_fic_buf, "%d", n );
    DisplayCurrWinText ( file_fic_buf );
  } else if(file_fic==-999){
    sprintf ( file_fic_buf, "%d", n );
    strcat ( str_buf, file_fic_buf );
#endif
  } else if( file_exists_fic == TRUE ){
    fprintf(ficxx,"%d",n);
  };
}

void flush_the_fic(f)
{
  if( f==1 ){
    fflush(stderr);
  } else if( (f==2) || (f==3) ){
    fflush(bstdout);
  } else if( file_exists_fic == TRUE ){
    fflush(ficxx);
  };
}

#define con_motif_fic file_fic=0

#define con_stderr_fic file_fic=1

#define con_stdout_fic file_fic=2

#define con_stdwin_fic file_fic=3

#define flush_fic           flush_the_fic(file_fic)
void close_ficxx_ficfunc()
#define close_ficxx_fic close_ficxx_ficfunc()
{
  if( file_exists_fic == TRUE ){
    fclose(ficxx);
  };
}

int con_fic(s)
{register int i,v,con_fic_res ;
  close_ficxx_fic;
  trans_fic(s);
  if( rewrite_ficxx == TRUE ){
    file_fic=4;
    file_exists_fic=TRUE;
    con_fic_res=TRUE;
  } else {
    con_fic_res=FALSE;
  }
  
/* 
  xst_str(stri_sym(s),i,v,v==ord('/'),
            if( (i!=len_str(stri_sym(s))-1) && (i!=2) ){
              fstr[i-2]='\0';
              if( access(fstr,W_OK)==0 ){
                fstr[i-2]='/';
                if( rewrite_ficxx == TRUE ){
                  file_fic=4;
                  file_exists_fic=TRUE;
                  con_fic_res=TRUE;
                } else {
                  con_fic_res=FALSE;
                };
              } else {
                con_fic_res=FALSE;
              };
            } else {
              con_fic_res=FALSE;
            },
            if( rewrite_ficxx == TRUE ){
              file_fic=4;
              file_exists_fic=TRUE;
              con_fic_res=TRUE;
            } else {
              con_fic_res=FALSE
           ;})
   */
; return con_fic_res;
}

void close_ficfunc()
#define close_fic close_ficfunc()
{
  close_ficxx_fic;
  file_exists_fic=FALSE;
#ifdef BTOOLM_FLAG
  file_fic=0;
#else
  file_fic=2;
#endif
}

int app_fic(s)
{register int i,v,con_fic_res ;
  close_ficxx_fic;
  trans_fic(s);
  if( append_ficxx == TRUE ){
    file_fic=4;
    file_exists_fic=TRUE;
    con_fic_res=TRUE;
  } else {
    con_fic_res=FALSE;
  }
  
/* 
  xst_str(stri_sym(s),i,v,v==ord('/'),
            if( (i!=len_str(stri_sym(s))-1) && (i!=2) ){
              fstr[i-2]='\0';
              if( access(fstr,W_OK)==0 ){
                fstr[i-2]='/';
                if( append_ficxx == TRUE ){
                  file_fic=4;
                  file_exists_fic=TRUE;
                  con_fic_res=TRUE;
                } else {
                  con_fic_res=FALSE;
                };
              } else {
                con_fic_res=FALSE;
              };
            } else {
              con_fic_res=FALSE;
            },
            if( append_ficxx == TRUE ){
              file_fic=4;
              file_exists_fic=TRUE;
              con_fic_res=TRUE;
            } else {
              con_fic_res=FALSE
           ;})
   */
; return con_fic_res;
}

void flush_all_ficfunc()
#define flush_all_fic flush_all_ficfunc()
{register int f ;
  flush_the_fic(1);
  flush_the_fic(2);
  flush_the_fic(3);
  flush_the_fic(4);
}

void close_all_ficfunc()
#define close_all_fic close_all_ficfunc()
{
  close_ficxx_fic;
}

#define val_col_ctr_fic     col_fic(file_fic)
  

#define mod_col_ctr_fic(n)  col_fic(file_fic)=n

#define val_pre_fic         pre_fic(file_fic)

#define mod_pre_fic(n)      pre_fic(file_fic)=n
void reset_ficfunc()
#define reset_fic reset_ficfunc()
{
  file_exists_fic=FALSE;
  col_fic(0)=1;
  pre_fic(0)=1;
  col_fic(1)=1;
  pre_fic(1)=1;
  col_fic(1)=1;
  pre_fic(1)=1;
  col_fic(2)=1;
  pre_fic(2)=1;
  col_fic(3)=1;
  pre_fic(3)=1;
  col_fic(4)=1;
  pre_fic(4)=1;
#ifdef BTOOLM_FLAG
  file_fic=0;
#else
  file_fic=2;
#endif
}

#define save_fic            old_file_fic=file_fic

#define restore_fic         file_fic=old_file_fic
  

#define print_newl_fic      print_fic(10)
    
      
  
