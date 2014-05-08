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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/utsname.h>
#include <time.h>

FILE * bstdout;

#define alloc_init                 500000

#define init_alloc_topup          2000000
#define alloc_topup               2500000

#define compact_cut_off         100000000

#define max_proved_rr_val        100
			     /* MUST be same as in bmotif.h */

int max_mem = 0;
int * mmts;

int max_fwd_ctr_auto_prf = 250;

/***
#ifdef suncomputer
***/

#define write_srv_res        putc(27, bstdout); fprintf ( bstdout, "[7m")
#define write_erv_res        putc(27, bstdout); fprintf ( bstdout, "[0m")
#define write_srv_err_res    putc(27,stderr); fprintf(stderr,"[7m")
#define write_erv_err_res    putc(27,stderr); fprintf(stderr,"[0m")

/***
#define write_top_clear_res  putc(27, bstdout); \
                             fprintf ( bstdout, "[1;1H"); \
                             putc(27, bstdout); \
                             fprintf ( bstdout, "[J")
***/

/***/
#define write_top_clear_res  ;
/***/


/*** 
#endif

#ifdef hpcomputer

#define write_srv_res        putc(27, bstdout); fprintf ( bstdout, "&dB")
#define write_erv_res        putc(27, bstdout); fprintf ( bstdout, "&d@")
#define write_srv_err_res    putc(27,stderr); fprintf(stderr,"&dB")
#define write_erv_err_res    putc(27,stderr); fprintf(stderr,"&d@")
#define write_top_clear_res  putc(27, bstdout); fprintf ( bstdout, "H");  putc(27, bstdout); fprintf ( bstdout, "J")

#endif
***/

#ifdef BTOOL_FLAG

char buf [ 250 ];
char BKIT_path [ 101 ];
int cs_nn, cs_rr;
char serv_addr [ 20 ];
int port;
FILE * Bfile;
int pid;
int Blm_registered = 0;

void ini_Blm ();

void
CreNumInBuf ( buf, n )
char * buf;
long n;
{
  sprintf( buf, "%ld", n);
}

#include "ClientSocket.c"
#endif /* BTOOL_FLAG */

#include "../MOTIF/BMotif_version.c"



#define WWW(x,y) fprintf ( bstdout, x, y )

#include "macros.c"

#include "trmmch.c"

#include "sysmch.c"

#include "winmch.c"

#include "natmch.c"


#include "max_vals.h"


#include "ctxmch.c"

#include "ysnmch.c"

#include "seqmch.c"

#include "strmch.c"

#include "symmch.c"

#include "setmch.c"

#include "fncmch.c"

#include "errmch.c"

#include "lexmch.c"

#include "nodmch.c"

#include "frmmch.c"

#include "codmch.c"

#include "resmch.c"

#include "ficmch.c"

#include "outmch.c"

#include "rulmch.c"

#include "themch.c"

#include "filmch.c"

#include "macmch.c"

#include "hypmch.c"

#include "golmch.c"

#include "tacmch.c"

#include "tolmch.c"

#include "shlmch.c"

#include "prfmch.c"

#include "inimch.c"

#include "itfmch.c"


bannerfunc()
#define banner bannerfunc()
{
  fprintf ( bstdout, "\n\n" );
/*
  fprintf ( bstdout, b_name );
*/
  fprintf ( bstdout, "                 b (malloc) for B-Core" );
  fprintf ( bstdout, "\n\n" );
  fprintf ( bstdout, toolkit_ver_with_sp );
  fprintf ( bstdout, "\n\n" );
  fprintf ( bstdout, orig_author );
  fprintf ( bstdout, "\n\n" );
  fprintf ( bstdout, toolkit_copyright );
  fprintf ( bstdout, "\n\n" );
}

/*  
   Possible cases for running b are the following:
      b
      b -m
      b -f FILE
      b -m -f FILE
      b -b FILE1 FILE2 ...
      b -m -b FILE1 FILE2 ...
      b -c FILE
      
   Options (-c exclusive with all other; -f,-b are exclusive):
   
      -m: with menu window
      -f: interactive with pre-loading
      -b: batch
      -c: compile (produces .bin file)
      
*/

exit___ ( nn )
int nn;
{
#ifdef BTOOL_FLAG
  if ( Blm_registered ) {
    ClientSocketNUM ( &cs_nn, &cs_rr, fini_request, pid, hi_l, hi_m, hi_h );
  }
#endif /* BTOOL_FLAG */

/***
printf ( "\nb (malloc) complete\n" );
***/
  exit ( nn );
}
      
#ifdef BTOOL_FLAG

void
get_tcpip ()
{   
  /*

    FILE * Btcp;
    strcpy ( buf, BKIT_path );
    strcat ( buf, tcpip_file_name );
    port = 0;
    i = 0;
    Btcp = fopen ( buf, "r" );
    if ( Btcp != NULL ) {
      c = getc ( Btcp );
      while ( ( c != EOF ) && ( c < '0' || c > '9' ) ) c = getc ( Btcp );
      if ( c == EOF ) {
        printf ( "\n  %s: syntax error 1\n", buf );
        exit ( 1 );
      }
      while ( ( c != EOF ) && ( c !=',' ) ) {
        serv_addr [ i ] = ( char ) c;
        i++;
        c = getc ( Btcp );
      }
      if ( c == EOF ) {
        printf ( "\n  %s: syntax error 2\n", buf );
        exit ( 1 );
      }
      else {
        c = getc ( Btcp );
      }
      while ( c >= '0' && c <= '9' ) {
        port = ( port * 10 ) + c - '0';
        c = getc ( Btcp );
      }
      fclose ( Btcp );
    }
    else {
      printf ( "\n  Can't open %s for reading\n\n", buf );
      printf ( "  Maybe BToolkitd isn't running?\n\n", buf );
      exit ( 1 );
    }
    */

  get_BToolkitd_tcpip ( BKIT_path );

}

void
ini_Blm_off ()
{
   int Popup_Sel_flag;

   Popup_Sel_flag = 0;

  get_tcpip ();

  pid = getpid ();
  strcpy ( pid_id_file, "/tmp/.B" );
  CreNumInBuf ( pid_id_file, pid );

  {
    FILE * Bpid_id;
    Bpid_id = fopen ( pid_id_file, "w" );
    if ( Bpid_id == NULL ) {
      printf ( "\n\n  Can't open %s\n\n", pid_id_file );
      exit ( 1 );
    }
    else {
      fclose ( Bpid_id );
    }
  }

  /***
  send hiip_request - hprot now redundant - always ipaddress protection!
  ***/
  ClientSocketNUM ( &cs_nn, &cs_rr, hiip_request, pid, 231, 87, 496 );
  if ( cs_rr < 0 ) {
    Popup_Sel_flag = 1; /* DesensitizeLSTButtons ( 1 ); */  /* 42 */
  }
  else {
    if ( cs_nn != ipaddress ) {
      Popup_Sel_flag = 4; /* DesensitizeLSTButtons ( 4 ); */  /* 45 */
    }
    else {
      int my_id;
      my_id = getuid ();
      put_num( &hi_l , &hi_m, &hi_h );
      /***
      send init_request
      ***/
      ClientSocketNUM ( &cs_nn, &cs_rr, init_request, pid, hi_l, hi_m, hi_h );
      if ( ! ( cs_nn + 4 ) ) {
        Popup_Sel_flag = 6; /* DesensitizeLSTButtons ( 7 ); */ /* 47 */
      }
      else if ( ! ( cs_nn + 3 ) ) {
        Popup_Sel_flag = 8; /* DesensitizeLSTButtons ( 8 ); */ /* 49 */
      }
      else if ( ! cs_nn ) {
        Popup_Sel_flag = 3; /* DesensitizeLSTButtons ( 3 ); */ /* 44 */
      }
      else {
        /***
        send non_count_request
        ***/
        ClientSocketNUM ( &cs_nn, &cs_rr, non_count_request, pid, hi_l, hi_m, hi_h );
        if ( ! ( cs_nn + 4 ) ) {
          Popup_Sel_flag = 7; /* DesensitizeLSTButtons ( 7 ); */ /* 48 */
        }
        else if ( ! ( cs_nn + 3 ) ) Popup_Sel_flag = 8; /* DesensitizeLSTButtons ( 8 ); */ /* 49 */
        else if ( ! cs_nn )         Popup_Sel_flag = 2; /* DesensitizeLSTButtons ( 2 ); */ /* 43 */
        else if ( cs_rr / 1000 )    Popup_Sel_flag = 1; /* DesensitizeLSTButtons ( 1 ); */ /* 42 */
      }
    }
  }
  DesensitizeLSTButtons ( Popup_Sel_flag + 40 );
  ini_Blm_done = 1;
}

void
ini_Blm ()
{
   int Popup_Sel_flag;

   Popup_Sel_flag = 0;

  DesensitizeLSTButtons ( Popup_Sel_flag + 40 );
  ini_Blm_done = 1;
}

Kill_bplatform_and_exit ( x, y )  /* for ClientSocket */
int x;
int y;
{
  exit ( 1 );
}

#endif /* BTOOL_FLAG */



main ( argc, argv )
int argc;
char *argv[];
{register int n ;

/***
{
  int i;
  printf ( "\nb (malloc) argc: %d\n", argc );
  for ( i = 0 ; i < argc ; i++ ) {
    printf ( "  %d: %s\n", i, argv [ i ] ); fflush ( stdout );
  }
  printf ( "\n" );
}
***/

  /***
  initialise bstdout
  ***/
  bstdout = stdout;

  /***
  perform malloc
  ***/
  max_mem = alloc_init;
  mmts = ( int * ) malloc ( ( max_mem + 5 ) * sizeof ( int ) );

#ifdef MALLOC_VERBOSE

printf ( "\n    ---------------------------------------------------\n     initial malloc: max_mem = %d\n    ---------------------------------------------------\n", max_mem );

#endif /* MALLOC_VERBOSE */

  if ( mmts == NULL ) {
     printf ( "\n  malloc failure\n" );
     exit ( 1 );
  }



  if( argc>1 ){

    if( (argv[1][0]=='-') && (argv[1][1]=='c') ){
      if( argc==3 ){
        mod_men_sys(FALSE);
        ini_win;
        ini;
        strcpy(name_load_fil,argv[2]);
        relod_prf;
        strcpy(name_save_fil,argv[2]);
        strcat(name_save_fil,".bin");
        cmp_seq(-999);
        save_comp_tool;
      }
    }

    else if( (argv[1][0]=='-') && (argv[1][1]=='s') ){
      if( argc==3 ){
        int t;
        mod_men_sys(FALSE);
        ini_win;
        ini;
        strcpy(name_load_fil,argv[2]);
        relod_prf;
        strcpy(name_save_fil,argv[2]);
        strcat(name_save_fil,"_");
        if ( open_save_comp_fil==TRUE ) {
          bstdout = save_fil;
          fprintf ( save_fil, "THEORY bootX END" );
          for ( t = 2 ; t <= nbr_the ; t++ ) {
            fprintf ( save_fil, "\n&\n" );
            lst_rul_the(t);
	  }
          fprintf ( save_fil, "\n" );
          close_save_fil;
	}
      }
    }
    else {
    if( (argv[1][0]=='-') && (argv[1][1]=='m') ){
      mod_men_sys(TRUE);
      n=2;
    } else {
      mod_men_sys(FALSE);
      n=1;
    }
    if( argc>n ){
      if( (argv[n][0]=='-') && (argv[n][1]=='f') ){
        if( argc==n+2 ){
          banner;
          ini_win;
          ini;
          strcpy(name_load_fil,argv[n+1]);
          relod_prf;
          fprintf ( bstdout, "\n" );
          sys_all_the;
        } else {         
/*  error (no file) --> interactive without file  */
          banner;
          ini_win;
          ini;
          fprintf ( bstdout, "\n" );
          sys_all_the;
        }
      } else if( (argv[n][0]=='-') && (argv[n][1]=='b') ){
        mod_batch_sys(TRUE);
        n=n+1;
        ini_win;
        while( n+1<argc ){
          ini;
          strcpy(name_restore_fil,argv[n]);
          restore_tool;
          strcpy(name_fil,argv[n+1]);
          {register int t ;
            xst_the(t,num_the(t)==2,exec_file_prf(t),{});
          }
          n=n+2;
        }
      } else if( (argv[n][0]=='-') && (argv[n][1]=='s') ){
        {register int
          more;
          FILE *pipein, *pipeout;
          char first[1001], second[1001];
          mod_batch_sys(TRUE);
          n = n+1;
          pipein = fopen(argv[n], "r");
          pipeout = fopen(argv[n+1], "w");
          if( pipein == NULL || pipeout == NULL ){
            fprintf(pipeout, "1\n");  
/*  is this correct ??  */
            fflush(pipeout);
          } else {
            fprintf(pipeout, "0\n");
            fflush(pipeout);
            ini_win;
            more = fscanf(pipein, "%s %s", first, second);
            while( more == 2 ){
              if( strcmp(name_restore_fil, first) != 0 ){
                ini;
                strcpy(name_restore_fil, first);
                restore_tool;
              }
              strcpy(name_fil, second);
              {register int t ;
                xst_the(t,num_the(t)==2,exec_file_prf(t),{});
                rem_rul_the(t,len(rul_the(t)));
              }
              fprintf(pipeout, "0\n");
              fflush(pipeout);
              more = fscanf(pipein, "%s %s", first, second);
            }
          }
        }
      } else { 
/*  error (unknown || missing option) --> interactive without file  */
        banner;
        ini_win;
        ini;
        fprintf ( bstdout, "\n" );
        sys_all_the;
      }
    } else {  
/*  b -m  */
      banner;
      ini_win;
      ini;
      fprintf ( bstdout, "\n" );
      sys_all_the;
    }
    }
  } else {  
/*  b  */
    banner;
    ini_win;
    ini;
    fprintf ( bstdout, "\n" );
    sys_all_the;
  }
  fprintf ( bstdout, "\n" );
  exit___ ( 0 );
}
