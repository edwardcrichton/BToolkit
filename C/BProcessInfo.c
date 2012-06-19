/* Copyright (c) 1988-96, B-Core (UK) Ltd
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
#include <unistd.h>
#include <errno.h>
#include <signal.h>

char serv_addr [ 20 ];
int cs_nn, cs_rr, port;
FILE * Bfile;

FILE *fileid;

char benv [ 101 ];
char buf [ 25000 ];
char buf1 [ 100 ];
char buf2 [ 100 ];
char buf3 [ 100 ];
char proc [ 1000 ] [ 100 ];
char bmotif_proc [ 1000 ] [ 100 ];

int c, i, j, k;
int done, user_header, other_header, proc_total, bmotif_proc_total, reqd;
int bm_num;

static char *num[] = { "0","1","2","3","4","5","6","7","8","9" };

void
CreNumInBuf ( buf, n )
char * buf;
long n;
{
  if ( n < 0 ) {
    n = n * (-1);
    strcat ( buf, "-" );
  }
  if ( n > 9 ) {
    CreNumInBuf ( buf, n/10 );
    strcat ( buf, num [ n % 10 ] );
  }
  else {
    strcat ( buf, num [ n ] );
  }
}

void
Kill_bplatform_and_exit ( flag1, flag2 )
int flag1;
int flag2;
{
  exit ( 1 );
}

#include "ClientSocket.c"

#include "BToolkitlm_globals.c"

int platform;
#define is_sunos   1
#define is_solaris 2
#define is_aix     3
#define is_osf1    4
#define is_irix    5
#define is_linux   6
#define is_darwin  7



void
print_user_header_if_nec ()
{
  if ( ! user_header ) {
    user_header = 1;
    printf ( "\n\n   Your B Processes:       process         pid         started\n\n" );
  }
}


void
print_other_header_if_nec ()
{
  if ( ! other_header ) {
    other_header = 1;
    printf ( "\n\n  Other B Processes:       process         pid         started\n\n" );
  }
}


void
read_fwd_to_start_ws ()
{
  while ( buf [ i ] != ' ' && buf [ i ] != '\t' ) {
    i++;
  }
}

void
read_fwd_to_start_non_ws ()
{
  while ( buf [ i ] == ' ' || buf [ i ] == '\t' ) {
    i++;
  }
}

void
read_bwd_to_end_ws ()
{
  while ( buf [ i ] != ' ' && buf [ i ] != '\t' ) {
    i--;
  }
}

void
read_bwd_to_end_non_ws ()
{
  while ( buf [ i ] == ' ' || buf [ i ] == '\t' ) {
    i--;
  }
}

void
get_proc_no ()
{
  j = 0;
  i = 0;
  read_fwd_to_start_ws ();
  read_fwd_to_start_non_ws ();
  if ( platform == is_irix ) {
    read_fwd_to_start_ws ();
    read_fwd_to_start_non_ws ();
    read_fwd_to_start_ws ();
    read_fwd_to_start_non_ws ();
  }
  buf2 [ j ] = buf [ i ];
  j++;
  i++;
  while ( buf [ i ] != ' ' && buf [ i ] != '\t' ) {
    buf2 [ j ] = buf [ i ];
    j++;
    i++;
  }
  while ( j < 10 ) {
    buf2 [ j ] = ' ';
    j++;
  }
  buf2 [ j ] = '\0';
}

void
get_start_time ()
{
  j = 0;
  i = 0;
  read_fwd_to_start_ws ();
  read_fwd_to_start_non_ws ();
  read_fwd_to_start_ws ();
  read_fwd_to_start_non_ws ();
  read_fwd_to_start_ws ();
  read_fwd_to_start_non_ws ();
  read_fwd_to_start_ws ();
  read_fwd_to_start_non_ws ();
  read_fwd_to_start_ws ();
  read_fwd_to_start_non_ws ();
  read_fwd_to_start_ws ();
  read_fwd_to_start_non_ws ();
  read_fwd_to_start_ws ();
  read_fwd_to_start_non_ws ();
  read_fwd_to_start_ws ();
  read_fwd_to_start_non_ws ();
  if ( ( platform == is_osf1 ) || ( platform == is_irix ) ) {
    read_fwd_to_start_ws ();
    read_fwd_to_start_non_ws ();
  }
  if ( platform == is_irix ) {
    read_fwd_to_start_ws ();
    read_fwd_to_start_non_ws ();
  }
  buf3 [ j ] = buf [ i ];
  j++;
  i++;
  while ( buf [ i ] != ' ' && buf [ i ] != '\t' ) {
    buf3 [ j ] = buf [ i ];
    j++;
    i++;
  }
  buf3 [ j ] = '\0';
}

int
main (  argc, argv )
int argc;
char *argv[];
{
  char * bkit;

  proc_total = 0;
  bmotif_proc_total = 0;
  user_header = 0;
  other_header = 0;

  printf ( "\n\n                     B Process Information\n                     ---------------------\n\n" );

  system ( "#! /bin/sh\nif [ -x /usr/bin/uname ]\nthen\n/usr/bin/uname -s > .Bpla\nfi" );
  system ( "#! /bin/sh\nif [ -x /usr/uname ]\nthen\n/usr/uname -s > .Bpla\nfi" );
  system ( "#! /bin/sh\nif [ -x /bin/uname ]\nthen\n/bin/uname > .Bpla\nfi" );

  fileid = fopen ( ".Bpla", "r" );
  if ( fileid  ==  NULL ) {
    printf ( "\n\n  Problem with \"uname\"\n\n" );
    exit ( 1 );
  }

  i = 0;
  c = getc ( fileid );
  while ( c != EOF && c != '\n' && i < 100 ) {
    benv [ i ] = c;
    c = getc ( fileid );
    i++;
  }
  fclose ( fileid );
  if ( i < 100 ) {
    benv [ i ] = '\0';
  }
  else {
    printf ( "\n\n  Problem with \"uname\"\n\n" );
    exit ( 1 );
  }

  unlink ( ".Bpla ");
  
  if      ( strcmp ( benv, "SunOS" ) == 0 ) {
     platform = is_sunos;
  }
  else if ( strcmp ( benv, "AIX" ) == 0 ) {
    platform = is_aix;
  }
  else  if ( strcmp ( benv, "OSF1" ) == 0 ) {
    platform = is_osf1;
  }
  else  if ( strcmp ( benv, "IRIX" ) == 0 ) {
    platform = is_irix;
  }
  else  if ( strcmp ( benv, "Linux" ) == 0 ) {
    platform = is_linux;
  }
    else  if ( strcmp ( benv, "Darwin" ) == 0 ) {
    platform = is_darwin;
  }
  else {
    printf ( "\n\n              Alien environment:  " );
    printf ( benv );
    printf ( "\n\n              Known environments: SunOS" );
    printf ( "\n                                  Solaris" );
    printf ( "\n                                  OSF1" );
    printf ( "\n                                  IRIX" );
    printf ( "\n                                  Linux" );
    printf ( "\n                                  Darwin" );
    printf ( "\n                                  AIX\n" );
    printf ( "\n                Assuming Linux\n\n" );
    platform = is_linux;
  }

  if ( platform == is_sunos ) {
    system ( "#! /bin/sh\nif [ -x /usr/bin/uname ]\nthen\n/usr/bin/uname -r > .Bpla\nfi" );
    system ( "#! /bin/sh\nif [ -x /usr/uname ]\nthen\n/usr/uname -r > .Bpla\nfi" );
    fileid = fopen ( ".Bpla", "r" );
    if ( fileid  ==  NULL ) {
      printf ( "\n\n  Problem with \"uname\"\n\n" );
      exit ( 1 );
    }

    i = 0;
    c = getc ( fileid );
    fclose ( fileid );
    if ( c == '5' ) {
      platform = is_solaris;
    }
    else if ( c != '4' ) {
      printf ( "\n\n  Unknown SunOS: " );
      system ( "cat .Bpla" );
      printf ( "\n\n" );
      exit ( 1 );
    }
    unlink ( ".Bpla" );
  }

  switch ( platform ) {
  case is_solaris:
    system ( "/usr/ucb/ps -guxww | grep BKIT | grep -v grep > .Bcom" );
    break;
  case is_aix:
    system ( "/bin/ps uxww | grep BKIT | grep -v grep > .Bcom" );
    break;
  case is_osf1:
    system ( "/usr/ucb/ps uxww | grep BKIT | grep -v grep > .Bcom" );
    break;
  case is_irix:
    system ( "/bin/ps -lf -u `whoami` | grep BKIT | grep -v grep > .Bcom" );
    break;
  case is_linux:
    system ( "/bin/ps uwwx | grep BKIT | grep -v grep > .Bcom" );
    break;
  case is_darwin:
    system ( "/bin/ps uwwx | grep BKIT | grep -v grep > .Bcom" );
    break;
  default:     /* is_sunos */
    system ( "/bin/ps -uwwx | grep BKIT | grep -v grep > .Bcom" );
    break;
  }

  fileid = fopen ( ".Bcom", "r" );
  if ( fileid == NULL ) {
    printf ( "\n\n  Can't open \".Bcom\" for reading\n\n" );
    exit ( 1 );
  }

  done = 0;
  while ( ! done ) {
    buf [ 0 ] = '\0';
    fgets ( buf, 9999, fileid );
    if ( buf [ 0 ] == '\0' ) {
      done = 1;
    }
    else {
      if      ( strstr ( buf, "bplatform" ) != NULL ) {
        get_proc_no ();
        strcpy ( proc [ proc_total ], buf2 );
        proc_total++;
        get_start_time ();
        print_user_header_if_nec ();
        printf ( "                           bplatform       %s  %s\n", buf2, buf3 );  
      }
      else if ( strstr ( buf, "BSession" ) != NULL ) {
        get_proc_no ();
        strcpy ( proc [ proc_total ], buf2 );
        proc_total++;
        get_start_time ();
        print_user_header_if_nec ();
        printf ( "                           BSession        %s  %s\n", buf2, buf3 ); 
      }
      else if ( strstr ( buf, "BMotif" ) != NULL ) {
        get_proc_no ();
        strcpy ( proc [ proc_total ], buf2 );
        proc_total++;
        strcpy ( bmotif_proc [ bmotif_proc_total ], buf2 );
        bmotif_proc_total++;
        get_start_time ();
        print_user_header_if_nec ();
        printf ( "                           BMotif          %s  %s\n", buf2, buf3 );  

      }
      else if ( strstr ( buf, "BTool" ) != NULL ) {
        if ( ( strstr ( buf, "BToolkitd" )      == NULL ) &&
             ( strstr ( buf, "BPocessInfo" )    == NULL )    ) {
          get_proc_no ();
          strcpy ( proc [ proc_total ], buf2 );
          proc_total++;
          strcpy ( bmotif_proc [ bmotif_proc_total ], buf2 );
          bmotif_proc_total++;
          get_start_time ();
          print_user_header_if_nec ();
/***
printf ( "%s\n", buf );
***/
          printf ( "                           BTool           %s  %s\n", buf2, buf3 );
	}
      }
    }
  }

  if ( ! user_header ) {
    printf ( "\n\n   Your B Processes:       none\n\n" );
  }

  fclose ( fileid );

  switch ( platform ) {
  case is_solaris:
    system ( "/usr/ucb/ps -auxww | grep BKIT | grep -v grep > .Bcom" );
    break;
  case is_aix:
    system ( "/bin/ps auxww | grep BKIT | grep -v grep > .Bcom" );
    break;
  case is_osf1:
    system ( "/usr/ucb/ps auxww | grep BKIT | grep -v grep > .Bcom" );
    break;
  case is_irix:
    system ( "/bin/ps -elf | grep BKIT | grep -v grep > .Bcom" );
    break;
  case is_linux:
    system ( "/bin/ps auxww | grep BKIT | grep -v grep > .Bcom" );
    break;
  case is_darwin:
    system ( "/bin/ps auwwx | grep BKIT | grep -v grep > .Bcom" );
    break;
  default:     /* is_sunos */
    system ( "/bin/ps -auxww | grep BKIT | grep -v grep > .Bcom" );
    break;
  }

  fileid = fopen ( ".Bcom", "r" );
  if ( fileid == NULL ) {
    printf ( "\n\n  Can't open \".Bcom\" for reading\n\n" );
    exit ( 1 );
  }

  done = 0;
  while ( ! done ) {
    buf [ 0 ] = '\0';
    fgets ( buf, 999, fileid );
    if ( buf [ 0 ] == '\0' ) {
      done = 1;
    }
    else {
      if ( strstr ( buf, "bplatform" ) != NULL ) {
        get_proc_no ();
        reqd = 1;
        k = 0;
        while ( k < proc_total ) {
          if ( strcmp ( proc [ k ], buf2 ) == 0 ) {
            reqd = 0;
	  }
          k++;
	}
        if ( reqd ) {
          get_start_time ();
          print_other_header_if_nec ();
          printf ( "                           bplatform       %s  %s\n", buf2, buf3 );
	}
      }
      else if ( strstr ( buf, "BSession" ) != NULL ) {
        get_proc_no ();
        reqd = 1;
        k = 0;
        while ( k < proc_total ) {
          if ( strcmp ( proc [ k ], buf2 ) == 0 ) {
            reqd = 0;
	  }
          k++;
	}
        if ( reqd ) {
          get_start_time ();
          print_other_header_if_nec ();
          printf ( "                           BSession        %s  %s\n", buf2, buf3 );
	}
      }
      else if ( strstr ( buf, "BMotif" ) != NULL ) {
        get_proc_no ();
        reqd = 1;
        k = 0;
        while ( k < proc_total ) {
          if ( strcmp ( proc [ k ], buf2 ) == 0 ) {
            reqd = 0;
	  }
          k++;
	}
        if ( reqd ) {
          get_start_time ();
          print_other_header_if_nec ();
          printf ( "                           BMotif          %s  %s\n", buf2, buf3 );
	}
      }
      else if ( strstr ( buf, "BTool" ) != NULL ) {
        if ( ( strstr ( buf, "BToolkitd" )      == NULL ) &&
             ( strstr ( buf, "BPocessInfo" )    == NULL )    ) {
          get_proc_no ();
          reqd = 1;
          k = 0;
          while ( k < proc_total ) {
            if ( strcmp ( proc [ k ], buf2 ) == 0 ) {
              reqd = 0;
	    }
            k++;
	  }
          if ( reqd ) {
            get_start_time ();
            print_other_header_if_nec ();
/***
printf ( "%s\n", buf );
***/
            printf ( "                           BTool           %s  %s\n", buf2, buf3 );
	  }
	}
      }
    }
  }

  fclose ( fileid );
  unlink ( ".Bcom" );

  if ( ! other_header ) {
    printf ( "\n\n  Other B Processes:       none\n" );
  }
  printf ( "\n" );

  bkit = getenv ( "BKIT" );
  get_BToolkitd_tcpip ( bkit );

  if ( proc_total ) {
    printf ( "\n  Kill your own B Processes (no data will be lost) - (y/n)? " );
    c = getchar ();
    if ( c != 'y' ) {
      printf ( "\n  No processes killed\n" );
    }
    else {
      printf ( "\n" );
      for ( i = 0 ; i < proc_total ; i++ ) {
        strcpy ( buf, "kill -9 " );
        strcat ( buf, proc [ i ] );
        if ( system ( buf ) == 0 ) printf ( "  Killed process %s\n", proc [ i ] );
      }
      if ( bmotif_proc_total ) {
        struct utsname u_s;
        put_num ( &hi_l , &hi_m, &hi_h );
        if ( uname ( &u_s ) == -1 ) {
          fprintf ( bstdout, "Error code: 12224\n" );
          Kill_bplatform_and_exit ( 0, 0 );
        }
        strcpy ( buf, u_s.nodename );
        i = 0;
        while ( ( buf [ i ] != '.' ) && ( buf [ i ] != '\0' ) ) { i++; }
        buf [ i ] = '\0';
        for ( i = 0 ; i < bmotif_proc_total ; i++ ) {
          bm_num = 0;
          j = 0;
          while ( ( bmotif_proc [ i ] [ j ] != ' ' )  &&
                  ( bmotif_proc [ i ] [ j ] != '\0' )    ) {
            bm_num = ( 10 * bm_num ) + bmotif_proc [ i ] [ j ] - '0';
            j++;
          }
          printf ( "\n    Attempting to remove Licence for process %d on %s - ", bm_num, buf );
          ClientSocketNUM ( &cs_nn, &cs_rr, BPInfo_remove, bm_num, hi_l, hi_m, hi_h );
          if   ( cs_nn ) printf ( "ok\n" );
          else           printf ( "failed\n" );
        } /* for ( i = 0 ; ... */
      } /* if bmotif_proc_total ) */
    } /* else - if ( c != 'y' ) */
  } /* if ( proc_total */

  ClientSocketNUM ( &cs_nn, &cs_rr, BToolkitd_util_status, 724, 20, 754, 6 );

  return ( 0 );

/***
  for ( i = 0 ; i < bmotif_proc_total ; i++ ) {
    bm_num = 0;
    j = 0;
    while ( ( bmotif_proc [ i ] [ j ] != ' ' )  &&
            ( bmotif_proc [ i ] [ j ] != '\0' )    ) {
      bm_num = ( 10 * bm_num ) + bmotif_proc [ i ] [ j ] - '0';
      j++;
    }
    printf ( "  -- bmotif: %d\n", bm_num );
  }
***/
}
