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
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>


FILE * bstdout;



#define alloc_init_val             500000
int alloc_init = alloc_init_val;

#define init_alloc_topup_val      2000000
int init_alloc_topup = init_alloc_topup_val;

#define alloc_topup_val           2500000
int alloc_topup = alloc_topup_val;

#define compact_cut_off         100000000



int max_mem = 0;
int * mmts;

int max_fwd_ctr_auto_prf = 250;




#ifndef INADDR_NONE
#define INADDR_NONE  0xffffffff
#endif /* INADDR_NONE */


int Bpim_ps_no = 0;



#ifdef bplatform

#define FILE_MODE ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )
int fifo_write_ptr, fifo_read_ptr;
char fifo_file_2m [ 300 ];
char fifo_file_2b [ 300 ];
char err_buf [ 250 ];

/*
#define bstdout stdout
*/

/*
#define exit___(x) exit(x)
*/

exit___(x)
{
  if ( x == 1 ) max0_toolfunc();
  exit ( x );
}

#endif



/***
#ifdef suncomputer
***/

#define write_srv_res        putc(27, bstdout); fprintf ( bstdout, "[7m")

#define write_erv_res        putc(27, bstdout); fprintf ( bstdout, "[0m")

#define write_srv_err_res    putc(27,stderr); fprintf(stderr,"[7m")

#define write_erv_err_res    putc(27,stderr); fprintf(stderr,"[0m")

#define write_top_clear_res  putc(27, bstdout); \
                             fprintf ( bstdout, "[1;1H"); \
                             putc(27, bstdout); \
                             fprintf ( bstdout, "[J")


/***
#endif

#ifdef hpcomputer
                        

#define write_srv_res        putc(27, bstdout); fprintf ( bstdout, "&dB")

#define write_erv_res        putc(27, bstdout); fprintf ( bstdout, "&d@")

#define write_srv_err_res    putc(27,stderr); fprintf(stderr,"&dB")

#define write_erv_err_res    putc(27,stderr); fprintf(stderr,"&d@")

#define write_top_clear_res  putc(27, bstdout); \
                             fprintf ( bstdout, "H"); \
                             putc(27, bstdout); \
                             fprintf ( bstdout, "J")

#endif
***/



/***
void
fifo_info ( ss, fd )
char * ss;
int fd;
{
  int accmode, val;

  if ( ( val = fcntl ( fd, F_GETFL, 0 ) ) < 0 )
    printf ( "\n\n -->> F_GETFL ERROR (1)\n\n" );

/?
  val &= ~O_NONBLOCK;
  if ( fcntl ( fd, F_SETFL, val ) < 0 )
    printf ( "\n\n -->> F_SETFL ERROR\n\n" );

  if ( ( val = fcntl ( fd, F_GETFL, 0 ) )  < 0 )
    printf ( "\n\n -->> F_GETFL ERROR (2)\n\n" );
?/

  accmode = val & O_ACCMODE;

  if      ( accmode == O_RDONLY ) printf ( "%s: read only", ss );
  else if ( accmode == O_WRONLY ) printf ( "%s: write only", ss );
  else if ( accmode == O_RDWR )   printf ( "%s: read write", ss );

  if ( val & O_NONBLOCK ) {
    printf ( ", nonblocking" );
  }
  else {
    fprintf (  bstdout, ", blocking" );
  }

  if ( val & O_NDELAY ) {
    printf ( ", nondelay" );
  }
  else {
    fprintf (  bstdout, ", delay" );
  }

  if ( val & O_APPEND ) {
    printf ( ", append" );
  }
  else {
    fprintf (  bstdout, ", non-append" );
  }

  if ( val & O_SYNC ) {
    printf ( ", synchronous writes" );
  }
  else {
    fprintf (  bstdout, ", asynchronous" );
  }

  printf ( " >>\n" ); fflush ( stdout );
}
***/








void
DisplayErrorBox ( ss, tt )
char * ss;
char * tt;
{
  char buf [ 500 ];

  strcpy ( buf, "$BKIT/BLIB/BPrompt \"bplatform: " );
  strcat ( buf, ss );
  strcat ( buf, " |" );
  strcat ( buf, tt );
  strcat ( buf, "|\"" );
  /*  system ( buf ); */
  printf ( "                                      %s %s\n", ss, tt );
}




void ReportSystemError ();

int interrupt_SIGUSR1_recd = 0;

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

void
ReportSystemError ( ss )
char * ss;
{
  FILE * Bsys;
  char cmd [ 250 ];

  strcpy ( cmd, "$BKIT/BLIB/BPrompt 'Error executing \"" );
  strcat ( cmd, ss );
  strcat ( cmd, "\"" );
  system ( cmd );
  Bsys = fopen ( ".Bsys", "w" );
  if ( Bsys != NULL ) {
    fprintf ( Bsys, "\n\n           Error executing \"%s\"\n\n", ss );
    fclose ( Bsys );
    system ( "echo .Bsys ; rm -f .Bsys" );
  }
}


bannerfunc()
#define banner bannerfunc()
{
  fprintf ( bstdout, "\n");
  fprintf ( bstdout, "\n");
  fprintf ( bstdout, "\n");
  fprintf ( bstdout, "\n\n");
  fprintf ( bstdout, "                      ____________________\n\n");
  fprintf ( bstdout, "              B-Platform for SPARC systems (Release 4.0)\n\n");
  fprintf ( bstdout, "            Copyright(c) 1985-98 B-Core(UK) Ltd\n\n\n");
  fprintf ( bstdout, "                      ____________________\n");
  fprintf ( bstdout, "\n");
  fprintf ( bstdout, "\n");
  fprintf ( bstdout, "\n");
}


void
interrupt_SIGUSR1 ()
{

/*****************************************************************/
#ifdef FIFO_TRACE_FLAG
fprintf ( bstdout, "                                  bplatform: received SIGUSR1\n" ); fflush ( bstdout );
#endif /* FIFO_TRACE_FLAG */
/*****************************************************************/

  interrupt_SIGUSR1_recd = 1;
}

void
interrupt_SIGUSR2 ()
{
  register int z,s,t,h,x ;  
  FILE * Bsta;
  FILE * Bses;
  FILE * Bpmd;
  Bsta = fopen( ".Bsta", "w" );
  if ( Bsta != NULL ) {
    fprintf ( Bsta, "\n      Max Number of Symbols:         " );
    fprintf ( Bsta, "%8d\n",max_sym);
    fprintf ( Bsta, "      Number of Used Symbols:        " );
    fprintf ( Bsta, "%8d\n\n",sym);
    fprintf ( Bsta, "      Max Number of Theories:        " );
    fprintf ( Bsta, "%8d\n",max_the);
    fprintf ( Bsta, "      Number of Used Theories:       " );
    fprintf ( Bsta, "%8d\n",the);
    fprintf ( Bsta, "      Number of Dead Theories:       " );
    fprintf ( Bsta, "%8d\n",tttm);
    fprintf ( Bsta, "      Number of Live Theories:       " );
    fprintf ( Bsta, "%8d\n\n",the-tttm);
    fprintf ( Bsta, "      Max Number of Goals:           " );
    fprintf ( Bsta, "%8d\n",max_gol);
    fprintf ( Bsta, "      Number of Used Goals:          " );
    fprintf ( Bsta, "%8d\n",gol);
    fprintf ( Bsta, "      Number of Dead Goals:          " );
    fprintf ( Bsta, "%8d\n",gttm);
    fprintf ( Bsta, "      Number of Live Goals:          " );
    fprintf ( Bsta, "%8d\n\n",gol-gttm);
    fprintf ( Bsta, "      Max Number of Nodes:           " );
    fprintf ( Bsta, "%8d\n",max_nod);
    fprintf ( Bsta, "      Number of Used Nodes:          " );
    fprintf ( Bsta, "%8d\n",nod);
    fprintf ( Bsta, "      Number of Dead Nodes:          " );
    fprintf ( Bsta, "%8d\n",nttm);
    fprintf ( Bsta, "      Number of Live Nodes:          " );
    fprintf ( Bsta, "%8d\n\n",nod-nttm);
    fprintf ( Bsta, "      Max Number of Tactics:         " );
    fprintf ( Bsta, "%8d\n",max_tac);
    fprintf ( Bsta, "      Number of Used Tactics:        " );
    fprintf ( Bsta, "%8d\n",tac);
    fprintf ( Bsta, "      Number of Dead Tactics:        " );
    fprintf ( Bsta, "%8d\n",tattm);
    fprintf ( Bsta, "      Number of Live Tactics:        " );
    fprintf ( Bsta, "%8d\n\n",tac-tattm);
    fprintf ( Bsta, "      Max Number of Hypos:           " );
    fprintf ( Bsta, "%8d\n",max_hyp);
    fprintf ( Bsta, "      Number of Used Hypos:          " );
    fprintf ( Bsta, "%8d\n",hyp);
    fprintf ( Bsta, "      Number of Dead Hypos:          " );
    fprintf ( Bsta, "%8d\n",httm);
    fprintf ( Bsta, "      Number of Live Hypos:          " );
    fprintf ( Bsta, "%8d\n\n",hyp-httm);
    fprintf ( Bsta, "      Max Number of Sequences:       " );
    fprintf ( Bsta, "%8d\n",max_seq);
    fprintf ( Bsta, "      Number of Used Sequences:      " );
    fprintf ( Bsta, "%8d\n",vnbs);
    fprintf ( Bsta, "      Number of Dead Sequences:      " );
    fprintf ( Bsta, "%8d\n",ttms);
    fprintf ( Bsta, "      Number of Live Sequences:      " );
    fprintf ( Bsta, "%8d\n",vnbs-ttms);
    fprintf ( Bsta, "\n" );
    fprintf ( Bsta, "      Memory Size:                   " );
    fprintf ( Bsta, "%8d words\n",max_mem);
    fprintf ( Bsta, "      Memory Used:                   " );
    fprintf ( Bsta, "%8d words\n",vad(vnbs+1));
    fprintf ( Bsta, "\n" );
    fprintf ( Bsta, "      SPARE MEMORY:                  " );
    fprintf ( Bsta, "%8d words\n",max_mem-vad(vnbs+1));
    fprintf ( Bsta, "\n");
    z=0;
    t=0;
    x=0;
    itrn( s , 1 , vnbs , {
    h=res_seq(s);
    z=z+h;
    t=t+len(s);
    if( h!=0 ){
      x=x+1;
    }; });
    fprintf ( Bsta, "      Sequences with no Free Space:  ");
    fprintf ( Bsta, "%8d\n",vnbs-x);
    fprintf ( Bsta, "      Sequences with Free Space:     ");
    fprintf ( Bsta, "%8d\n",x);
    fprintf ( Bsta, "      Average Sequence Size:         ");
    fprintf ( Bsta, "%8d words\n",(t / (vnbs)));
    if( x!=0 ){
      fprintf ( Bsta, "      Average Free Space Size:       ");
      fprintf ( Bsta, "%8d words\n",(z / x));
    }
    fprintf ( Bsta, "\n");
    fprintf ( Bsta, "      SIGMA OF FREE SPACES:          ");
    fprintf ( Bsta, "%8d words\n",z);
    fprintf ( Bsta, "\n");
    fprintf ( Bsta, "      SPARE MEMORY +                 ");
    fprintf ( Bsta, "\n");
    fprintf ( Bsta, "      SIGMA OF FREE SPACES:          ");
    fprintf ( Bsta, "%8d words\n\n",z+max_mem-vad(vnbs+1));
    fprintf ( Bsta, "\n");
    fclose ( Bsta );
  }

  Bpmd = fopen ( ".Bpmd", "r" );
  if ( Bpmd != NULL ) {
    char buf1 [ 100 ];
    char buf2 [ 25 ];
    strcpy ( buf1, "kill -9 " );
    x = 0;
    z = getc ( Bpmd );
    while ( z != EOF && z != '\n' ) {
      buf2 [ x ] = ( char ) z;
      x++;
      z = getc ( Bpmd );
    }
    fclose ( Bpmd );
    strcat (  buf1, buf2 );
    system ( buf1 );
  }
  Bses = fopen ( ".Bses", "w" );
  if ( Bses == NULL ) {
    fprintf ( bstdout,  "\n             Can't open \".Bses\" for writing\n\n" );
    exit ( 1 );
  }
  fprintf ( Bses, "999" );
  fclose ( Bses );
  exit ( 0 );
}


struct sigaction act1;
struct sigaction act_USR1;
struct sigaction act_USR2;

void
check_system_calls_ok()
{
  FILE * Bbbb;
  int c;

  Bbbb = fopen ( ".Bbbb", "w" );
  if ( Bbbb == NULL ) {
    fprintf ( stdout,  "\n             Can't open \".Bbbb\" for writing\n\n" );
    exit ( 1 );
  }
  putc ( '1', Bbbb );
  fclose ( Bbbb );
  Bbbb = fopen ( ".Bbbb", "r" );
  if ( Bbbb == NULL ) {
    fprintf ( stdout,  "\n             Can't open \".Bbbb\" for reading\n\n" );
    exit ( 1 );
  }
  c = getc ( Bbbb );
  if ( ( char ) c  != '1' ) {
    fprintf ( stdout,  "\n             Can't write to \".Bbbb\"\n\n" );
    fclose ( Bbbb );
    exit ( 1 );
  }
  fclose ( Bbbb );
  system ( "echo 2 > .Bbbb" );
  fopen ( ".Bbbb", "r" );
  if ( Bbbb == NULL ) {
    fprintf ( stdout,  "\n             Can't open \".Bbbb\" for reading\n\n" );
    exit ( 1 );
  }
  c = getc ( Bbbb );
  if ( ( char ) c  != '2' ) {
    fprintf ( stdout,  "\n             bplatform: not enough memory (bplatform_size: %d)\n\n", max_mem );
    fprintf ( stdout,  "\n             Run:\n               $BKIT/BProcessInfo\n             to kill B Processes\n\n" );
    fclose ( Bbbb );
    exit ( 1 );
  }
  fclose ( Bbbb );
  unlink ( ".Bbbb" );
}

void
int_trap ()
{
  FILE * Bses;
  Bses = fopen ( ".Bses", "w" );
  if ( Bses == NULL ) {
    fprintf ( bstdout,  "\n             Can't open \".Bses\" for writing\n\n" );
    exit ( 1 );
  }
  fprintf ( Bses, "997" );
  fclose ( Bses );
  exit ( 0 );  
}

main ( argc, argv )
int argc;
char *argv[];
{

  int i, ll;
  FILE * Bpib;

/***
  the arguments

  0: /apps/btoolkit/TOOLKIT/MASTER_RELEASE/4.1/BKIT/BPLAT/bplatform
  1: /apps/btoolkit/TOOLKIT/MASTER_RELEASE/4.1/BKIT/BLIB/Toolkit11.bin
  2: 16526 (BMotif process num .Bpim)
  3: full dev path
  4: 040
  5: pog_flag value
  6: /tmp/.B_16526 (BMotif process num .Bpim - the pipe)
  7: /tmp/.B_16526 (BMotif process num .Bpim - the pipe)
***/


/***
{
  char buf [ 250 ];
  strcpy ( buf, "$BKIT/BLIB/BPrompt \"" );
  for ( i = 0 ; i < argc ; i++ ) {
    strcat ( buf, argv [ i ] );
    strcat ( buf, " " );
  }
  strcat ( buf, "\"" );
  system ( buf );
}
***/

/***
  printf ( "bplatform argc: %d\n", argc );
  for ( i = 0 ; i < argc ; i++ ) {
    printf ( "  %d: %s\n", i, argv [ i ] );
  }
  printf ( "\n" );
***/

/***
AutoProver   => exec_prf==TRUE   val_batch_sys==TRUE
ProofPrinter => exec_prf==FALSE  val_batch_sys==FALSE
***/

  if ( ( argc != 2 ) && ( argc != 8 ) ) exit ( argc + 1 );

  /***
  set up interrupts
  ***/

  /***
  for bsuspend (not currently used)
  ***/
  act_USR1.sa_handler = interrupt_SIGUSR1;
  sigemptyset ( & ( act_USR1.sa_mask ) );
  act_USR1.sa_flags = ( int ) 0;
  sigaction ( SIGUSR1, & act_USR1, NULL );

  /***
  for genuine interrupt from BMotif
  ***/
  act_USR2.sa_handler = interrupt_SIGUSR2;
  sigemptyset ( & ( act_USR2.sa_mask ) );
  act_USR2.sa_flags = ( int ) 0;
  sigaction ( SIGUSR2, & act_USR2, NULL );

  /***
  set up interrupt for ^C
  ***/
  act1.sa_handler = int_trap;
  sigemptyset ( & ( act1.sa_mask ) );
  sigaddset ( & ( act1.sa_mask ), SIGINT );
  act1.sa_flags = ( int ) 0;
  sigaction ( SIGINT,  & act1, NULL );


  /***
  check system calls
  ***/
  check_system_calls_ok();


  /***
  write getpid to .Bpib
  ***/
  Bpib = fopen ( ".Bpib", "w" );
  if ( Bpib == NULL ) {
    fprintf ( stdout,  "\n             Can't open \".Bpib\" for writing\n\n" );
    exit ( 1 );
  }
  fprintf ( Bpib, "%d\n", getpid() );    /* the \n is necessary! */
  fclose ( Bpib );

  /***
  set max_fwd_ctr_auto_prf
  ***/
  Bpib = fopen ( "TMP/.Bmfh", "r" );
  if ( Bpib != NULL ) {
    int c;
    max_fwd_ctr_auto_prf = 0;
    c = getc ( Bpib );
    while ( ( c != EOF ) && ( c != '\n') ) {
      max_fwd_ctr_auto_prf = ( 10 * max_fwd_ctr_auto_prf ) + c - '0';
      c = getc ( Bpib );
    }
/***
printf ( "max_fwd_ctr_auto_prf = %d\n", max_fwd_ctr_auto_prf );
***/
    fclose ( Bpib );
  }



  bstdout = stdout;


  /******************************************************************
  to print a trace of all goals (sho_big_gol_prf = TRUE if required)
  ******************************************************************/

#ifdef BPLATFORM_TRACE_FLAG

  goal_trace_ptr = fopen ( "bplatform_trace", "a" );

  printf ( "\n\n      >>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<" );
  printf ( "\n      >>>>> GOAL TRACE in file \"bplatform_trace\" <<<<<\n" );
  printf ( "      >>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<\n\n" );

  /***/
  sho_big_gol_prf = TRUE;
  /***/

#else

  goal_trace_ptr = NULL;

#endif

  pog_flag = 0;                      /*** don't edit this line ***/


  /***
  check for malloc file
  ***/
  {
    FILE * malloc_ptr;
    int c, n;
    malloc_ptr = fopen ( "malloc", "r" );
    if ( malloc_ptr != NULL ) {
      c = getc ( malloc_ptr );
      while ( ( c != EOF )                   &&
              ( ( c < '0' ) || ( c > '9' ) )     ) {
        c = getc ( malloc_ptr );
      }
      if ( c != EOF ) {
        n = 0;
        while ( ( c >= '0' ) && ( c <= '9' ) ) {
          n = ( 10 * n ) + c - '0';
          c = getc ( malloc_ptr );
        }
        alloc_init = n;
      }
      while ( ( c != EOF ) && ( c != ',' ) ) {
        c = getc ( malloc_ptr );
      }
      if ( c == ',' )  c = getc ( malloc_ptr );
      while ( ( c != EOF )                   &&
              ( ( c < '0' ) || ( c > '9' ) )     ) {
        c = getc ( malloc_ptr );
      }
      if ( c != EOF ) {
        n = 0;
        while ( ( c >= '0' ) && ( c <= '9' ) ) {
          n = ( 10 * n ) + c - '0';
          c = getc ( malloc_ptr );
	}
        alloc_topup = n;
      }
      fprintf ( bstdout, "\n  malloc file read as: %d,%d\n",
                                                      alloc_init, alloc_topup );
    }
  }


  /***
  perform malloc
  ***/
  max_mem = alloc_init;
  mmts = ( int * ) malloc ( ( max_mem + 5 ) * sizeof ( int ) );

#ifdef MALLOC_VERBOSE

printf ( "\n    ---------------------------------------------------\n     initial malloc : max_mem = %d\n    ---------------------------------------------------\n", max_mem );

#endif /* MALLOC_VERBOSE */

  if ( mmts == NULL ) {
     printf ( "\n  malloc failure\n" );
     exit ( 1 );
  }

  if ( argc == 8 ) {

    /***
    get Bpim_ps_no
    ***/
    Bpim_ps_no = 0;
    i = 0;
    while ( argv [ 2 ] [ i ] != '\0' ) {
      Bpim_ps_no = ( Bpim_ps_no * 10 ) + argv[2 ]  [ i ] - '0';
      i++;
    }

    /***
    initialise fifo file names
    ***/

/***
printf ( "bplatform cur_dir : |%s|\n", argv [ 3 ] );
***/

    strcpy ( fifo_file_2m, argv [ 6 ] );
    strcpy ( fifo_file_2b, argv [ 7 ] );

/***
printf ( "blpatform : fifo_file_2b=%s\n            fifo_file_2m=%s\n\n", fifo_file_2b, fifo_file_2m );
***/

    ll = strlen ( argv [ 1 ] );

    if( ( argv [ 1 ] [ ll - 4 ] == '.' ) &&
        ( argv [ 1 ] [ ll - 3 ] == 'b' ) &&
        ( argv [ 1 ] [ ll - 2 ] == 'i' ) &&
        ( argv [ 1 ] [ ll - 1 ] == 'n' )    ) {

      /***
      Toolkit N ...
      ***/

      if ( ( argv[ 1 ] [ ll - 6 ] == 't' &&
             argv[ 1 ] [ ll - 5 ] == '5'    ) ||
           ( argv[ 1 ] [ ll - 7 ] == 't' &&
             argv[ 1 ] [ ll - 6 ] == '2' &&
             argv[ 1 ] [ ll - 5 ] == '0'    ) ||
           ( argv[ 1 ] [ ll - 7 ] == 't' &&
             argv[ 1 ] [ ll - 6 ] == '2' &&
             argv[ 1 ] [ ll - 5 ] == '1'    )    ) {

        /***
        Toolkit 5 20 or 21
        ***/

        /*** 1 for ALL pobs, else 0 ***/
        pog_flag = argv [ 5 ] [ 0 ] - '0';
/***
printf ( "bplatform: pog_flag %d\n", pog_flag );
***/

      }
      mod_men_sys ( FALSE );
      mod_batch_sys ( TRUE );
      ini_win;     
      ini;
      strcpy ( name_restore_fil, argv [ 1 ] );
      restore_tool;
      strcpy ( name_fil, ".Benv" );
/***
max0_toolfunc();
***/
      aborted_goal=cre(4);
      aborted_goal_copied = 0;
      {register int t;
        xst_the ( t, num_the ( t ) == 2, exec_file_prf ( t ), {} );
      }
      return 0;

    }

  }

  else if ( ( argc == 2 )          &&
             (argv[1][0]=='r') &&
             (argv[1][1]=='R') &&
             (argv[1][2]=='1') &&
             (argv[1][3]=='H') &&
             (argv[1][4]=='1') &&
             (argv[1][5]=='p') &&
             (argv[1][6]=='p')    ){        /* ppf */

    ini_win;
    ini;
    fprintf ( bstdout, "\n");
    sys_all_the;
    return 0;

  }

}
