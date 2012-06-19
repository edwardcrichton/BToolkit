/* Copyright (c) 1992-96, B-Core (UK) Ltd
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
#include <string.h>

#define BToolkitd_ServerPV1 { "dummy" }
#define BToolkitd_ServerPV2 10000
#define BToolkitd_ServerPV3 10000

#include "BToolkitd_ClientServer/CDE/C/BToolkitd_Server.g"
#include "BToolkitd_ClientServer/CDE/C/BToolkitd_Server.c"

struct sigaction act1;

int ss_i, ss_j, read_len, ss_err;
int ss_p, ss_n, ss_r, ss_q, ss_t, ss_u, ss_v, ss_s;
FILE * Bfile;

pid_t BToolkitd_pid;

static char *num[] = { "0",
                       "1",
                       "2",
                       "3",
                       "4",
                       "5",
                       "6",
                       "7",
                       "8",
                       "9"
		     };

int n_loops;

#ifdef VERBOSE_FLAG

void
print_WHOLE_ARRAY ()
{
  printf ( "\n----------------------------\n" );
for ( i = ps_store ; i < ps_store + 6 ; i++ ) printf ( "%d ", ma [ i ] );
  printf ( "\n----------------------------\n" );
for ( i = ps_store + max_hiip ; i < ps_store + max_hiip + 12 ; i++ ) printf ( "%d ", ma [ i ] );
  printf ( "\n----------------------------\n" );
for ( i = ps_store + ( 3 * max_hiip ) ; i < ps_store + ( 3 * max_hiip ) + 15 ; i++ ) printf ( "%d ", ma [ i ] );
  printf ( "\n" );
for ( i = ps_store + ( 3 * max_hiip ) + 15 ; i < ps_store + ( 3 * max_hiip ) + 30 ; i++ ) printf ( "%d ", ma [ i ] );
  printf ( "\n" );
for ( i = ps_store + ( 3 * max_hiip ) + 30 ; i < ps_store + ( 3 * max_hiip ) + 45 ; i++ ) printf ( "%d ", ma [ i ] );
  printf ( "\n" );
for ( i = ps_store + ( 3 * max_hiip ) + 45 ; i < ps_store + ( 3 * max_hiip ) + 60 ; i++ ) printf ( "%d ", ma [ i ] );
  printf ( "\n" );
for ( i = ps_store + ( 3 * max_hiip ) + 60 ; i < ps_store + ( 3 * max_hiip ) + 75 ; i++ ) printf ( "%d ", ma [ i ] );
  printf ( "\n" );
for ( i = ps_store + ( 3 * max_hiip ) + 75 ; i < ps_store + ( 3 * max_hiip ) + 90 ; i++ ) printf ( "%d ", ma [ i ] );
  printf ( "\n----------------------------\n" );
}

#endif /* VERBOSE_FLAG */

#define ServerSocket_calc_ipa \
          a = ( ss_v / 256 ); \
          b = ( ( ss_v / 16 ) % 16 ); \
          c = ( ss_v % 16 ); \
          d = ( ss_u / 16 ); \
          e = ( ss_u % 16 ); \
          f = ( ss_t / 256 ); \
          g = ( ( ss_t / 16 ) % 16 ); \
          h = ( ss_t % 16 ); \
          ipa =  calc_ip ( a, b, c, d, e, f, g, h )

void
CreNumInBuf ( buf, n )
char * buf;
time_t n;
{
  if ( n > 9 ) {
    CreNumInBuf ( buf, n/10 );
    strcat ( buf, num [ n % 10 ] );
  }
  else {
    strcat ( buf, num [ n ] );
  }
}

void
child_reaper ( sig )
int sig;
{
  int status;

  while ( wait3 ( &status, WNOHANG, ( struct rusage * ) 0 ) >= 0 ) ;

#ifdef VERBOSE_FLAG
printf ( "-------->>>>>>>>> child_reaper sig %d status %d\n", sig, status );
#endif /* VERBOSE_FLAG */

}


int
ss_init ()
{
  char             buf [ 250 ];
  int              port;
  struct servent   * servent_ptr;
  int              rep;

  if ( ( servent_ptr = getservbyname ( "BToolkitd", "tcp" ) ) ) {
    port = ( ntohs ( servent_ptr -> s_port) );
  }
  else {
/*
    strcpy ( buf, licence_file );
    while ( buf [ strlen ( buf )  - 1 ]  != '/' ) {
      buf [ strlen ( buf )  - 1 ]  = '\0';
    }
    buf [ strlen ( buf )  - 1 ]  = '\0';
    strcat ( buf, port_file_name );
    Bfile = fopen ( buf, "r" );
    if ( Bfile != NULL ) {
      port = 0;
      c = getc ( Bfile );
      while ( ( c != EOF ) && ( c < '0' || c > '9' ) ) c = getc ( Bfile );
      while ( c >= '0' && c <= '9' ) {
        port = ( port * 10 ) + c - '0';
        c = getc ( Bfile );
      }
      fclose ( Bfile );
    }
    else {
      port = default_port;
    }
  }
*/
    port = argv2;
    if ( port != default_port ) {
      printf ( "\n  BToolkitd %s: ensure that $BKIT/B_port contains %d\n",
                                                    no_toolkit_short_ver, port );
    }
  } 

#ifdef VERBOSE_FLAG
printf ( "\n\n  attempting to listen at port %d\n", port );
printf ( "  licence_file: %s\n", licence_file );
printf ( "  lock_file   : %s\n", lock_file_name );
/*
printf ( "  data_file: %s\n", data_file );
printf ( "  data_file_backup: %s\n", data_file_backup );
*/
#endif /* VERBOSE_FLAG */

  printf ( "\n" );
  BToolkitd_INIT ( &rep, lock_file_name, port, "/tmp/.BT_backup" );

  if ( ! rep ) exit ( 1 );

  BToolkitd_pid = getpid ();

  return ( port );
}

void
ss_shutdown ()
{
  shutdown ( sock_num, shutdown_all );
}

void
check_BToolkitd_pid_still_ok ()
{
  /***
  prevents abuse of the licence system, by stopping two daemons
  running on two different ports on the same machine.

  DO NOT REMOVE

  ***/

  int c;
  pid_t d;
  Bfile = fopen ( lock_file_name, "r" );

  if ( Bfile == NULL ) {
    int lf;                /* file descriptor for pid/lock file */
    char pid_buf [ 10 ];   /* buffer for pid                    */

#ifdef VERBOSE_FLAG
printf ( "Recreating lock file %s\n", lock_file_name );
#endif /* VERBOSE_FLAG */
    /***
    acquire exclusive lock
    ***/
    lf = open ( ( char * ) lock_file_name, O_RDWR | O_CREAT, 0640 );
    if ( lf < 0 ) syslog_msg_exit ( "Can't create file: %s\n", lock_file_name );

/*
    if ( flock ( lf, LOCK_EX | LOCK_NB ) )
      syslog_msg_exit ( "Unable to obtain lock on %s\n", lock_file_name );
*/

    /***
    write pid to file & close
    ***/
    sprintf ( pid_buf, "%d", getpid () );
    write ( lf, pid_buf, strlen ( pid_buf ) );
    close ( lf );
  }

  else { /* Bfile != NULL */
    d = 0;
    c = getc ( Bfile );
    while ( ( c != EOF ) && ( c < '0' || c > '9' ) ) c = getc ( Bfile );
    while ( ( c >= '0' ) && ( c <= '9' ) ) {
      d = ( d * 10 ) + c - '0';
      c = getc ( Bfile );
    }
    fclose ( Bfile );
    if ( d != BToolkitd_pid )
      syslog_msg_exit ( "Can't validate file: %s\n", lock_file_name );
  }
}

void
WriteSocket ()
{
  int rep;

  BToolkitd_WRITE ( &rep );
  if ( ! rep )
  {
     /* can't do much about it if it has failed to write, but we should close the socket. */
  	/*return;*/
  }

  BToolkitd_CLOSE ( &rep );
}

#define UnsChars2Int(s,n) \
            ( ( unsigned char ) s [ n ] * 256 ) + ( unsigned char ) s [ n + 1 ]

void
proc_socket ()
{
  int      yy, zz, tok;
  time_t   dl ();

  void     int_status ();
  void     int_down ();
  void     int_remove ();
  void     int_reread ();
  int      chk_hiip ();
  int      chk_pid ();

  check_BToolkitd_pid_still_ok ();

  ss_err = 0;

  BToolkitd_GET_TOK ( &tok, 4 );    /* 6(NUM) or 7(STR) args to be received */
  if ( tok == 7 ) {
    BToolkitd_GET_TOK ( &tok, 1 );
    if ( tok != STR ) ss_err = 1;
    else              BToolkitd_GET_STR ( ( int * ) buf );    
  }
  else if ( tok != 6 ) ss_err = 1;

  if ( ! ss_err ) {
    BToolkitd_GET_TOK ( &tok, 1 );
    if ( tok != NUM ) ss_err = 1;
    else              BToolkitd_GET_TOK ( &ss_p, 4 );
  }

  if ( ! ss_err ) {
    BToolkitd_GET_TOK ( &tok, 1 );
    if ( tok != NUM ) ss_err = 1;
    else              BToolkitd_GET_TOK ( &ss_n, 4 );
  }

  if ( ! ss_err ) {
    BToolkitd_GET_TOK ( &tok, 1 );
    if ( tok != NUM ) ss_err = 1;
    else              BToolkitd_GET_TOK ( &ss_q, 4 );
  }

  if ( ! ss_err ) {
    BToolkitd_GET_TOK ( &tok, 1 );
    if ( tok != NUM ) ss_err = 1;
    else              BToolkitd_GET_TOK ( &ss_t, 4 );
  }

  if ( ! ss_err ) {
    BToolkitd_GET_TOK ( &tok, 1 );
    if ( tok != NUM ) ss_err = 1;
    else              BToolkitd_GET_TOK ( &ss_u, 4 );
  }

  if ( ! ss_err ) {
    BToolkitd_GET_TOK ( &tok, 1 );
    if ( tok != NUM ) ss_err = 1;
    else              BToolkitd_GET_TOK ( &ss_v, 4 );
  }

/***
printf ( " - - - - - %d %d %d %d %d %d\n", ss_p, ss_n, ss_q, ss_t, ss_u, ss_v );
***/

/* ss_p=2rnd+pid+req | dir | ss_n=2rnd+pid | ss_q=rnd |
      ss_t=l+m+h+rnd | ss_u=l+m+2h+rnd | ss_v=2l+m+h+rnd */

    if ( ! ss_err ) {
      ss_p = ss_p - ss_q; /* = rnd+pid+req */
      ss_n = ss_n - ss_q; /* = rnd+pid */
      ss_p = ss_p - ss_q; /* = pid+req */
      ss_n = ss_n - ss_q; /* pid */

      /********* ss_p=pid+req | dir | ss_n=pid | ss_q=rnd **********/

      ss_t = ss_u - ss_t;                       /* = h */
      ss_v = ss_v + ss_t - ss_u;                /* = l */
      ss_u = ss_u - ss_t - ss_v - ss_t - ss_q ; /* = m */
      ss_s = ss_q;           /* random/pid (in case of user_uid/name_request) */

/***
printf ( " - - - - - - - - - - - - - %d %d %d %d\n", ss_t, ss_v, ss_u, ss_s );
***/

      ss_q = ss_p - ss_n; /* = req */

/***
printf ( " - - - - - - - - - - - - - %d\n", ss_q );
***/
      if ( ( ss_q != hiip_request )                &&
           ( ss_q != user_uid_request )            &&
           ( ss_q != user_name_request )           &&
           ( ss_q != chk_vers_request )            &&
           ( ss_q != Bpda_time_request )           &&
           ( ss_q != fini_request )                &&
           ( ss_q != am_anonymous_server_request ) &&
           ( ss_q != BTd_id_BT_id_check )          &&
           ( ss_q != rem_zombie_request )          &&
           ( ss_q != BPInfo_remove )               &&
           ( ss_q != BToolkitd_util_status )       &&
           ( ss_q != BToolkitd_util_down )         &&
           ( ss_q != BToolkitd_util_remove )       &&
           ( ss_q != BToolkitd_util_generate )     &&
           ( ss_q != BToolkitd_util_reread )      ) {

        /***
        check hostid still ok
        ***/
        yy = chk_hiip  (
                ( ss_v / 256 ) ,
                ( ( ss_v / 16 ) % 16 ),
                ( ss_v % 16 ),
                ( ss_u / 16 ),
                ( ss_u % 16 ),
                ( ss_t / 256 ) ,
                ( ( ss_t / 16 ) % 16 ),
                ( ss_t % 16 ) );

        if ( yy == -1 ) {

#ifdef VERBOSE_FLAG
printf ( "\n    no ipadress match!!!\n" );
#endif /* VERBOSE_FLAG */
        
          BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( 0, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( 0, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( 0, 4 );
          WriteSocket ();
          ss_p = ss_n;  /* so it won't `switch' */
	} /* if ( yy == -1 ) */

#ifdef VERBOSE_FLAG
else {
  printf ( "    ipaddress match at ipaddress position" );
  printf ( " #%2d\n", yy );
}
#endif /* VERBOSE_FLAG */

      }  /* end check hostid still ok */

      if ( ( ss_q != hiip_request )                && 
           ( ss_q != pre_init_request )            &&
           ( ss_q != init_request )                &&
           ( ss_q != user_uid_request )            &&
           ( ss_q != user_name_request )           &&
           ( ss_q != chk_vers_request )            &&
           ( ss_q != Bpda_time_request )           &&
           ( ss_q != fini_request )                &&
           ( ss_q != am_anonymous_server_request ) &&
           ( ss_q != BTd_id_BT_id_check )          &&
           ( ss_q != rem_zombie_request )          &&
           ( ss_q != BPInfo_remove )               &&
           ( ss_q != BToolkitd_util_status )       &&
           ( ss_q != BToolkitd_util_down )         &&
           ( ss_q != BToolkitd_util_remove )       &&
           ( ss_q != BToolkitd_util_generate )     &&
           ( ss_q != BToolkitd_util_reread )      ) {

        /***
        check pid still ok
        ***/

        zz = chk_pid  ( ss_n );
        if ( zz == -1 ) {

#ifdef VERBOSE_FLAG
printf ( "\n    no longer a pid match!!! (req = %d)\n", ss_q );
#endif /* VERBOSE_FLAG */

          BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( 0, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( 1, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( 0, 4 );
          WriteSocket ();
          ss_p = ss_n;  /* so it won't `switch' */
	}
        else {
          upd_ps ( zz );

#ifdef VERBOSE_FLAG
printf ( "    pid match at pid position #%2d\n", zz );
#endif /* VERBOSE_FLAG */

	}

      }   /* end check  pid still ok */

/* ss_p=pid+req | dir | ss_n=pid | ss_q=req */

      ss_r = ( ( t4 % 1000 ) + ( 1000 * tt ) );

/***
printf ( "\n\n\n\n       ss_p - ss_n = %d\n\n\n\n", ss_p - ss_n );
***/

      switch ( ss_p - ss_n ) { /* req */

      case count_request :

#ifdef VERBOSE_FLAG
printf ( "count_request - pid %d", ss_n );
printf ( " -> left: %d", t5 - t6 );
printf ( " (%d,%d)", t5, t6 );
printf ( " %d\n", ss_r );
#endif /* VERBOSE_FLAG */

        bd ( count_request, ss_n );
        BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( ss_r + t5 + ss_p, 4 );
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( t5 + ss_r + ss_p + ss_p + t5 - ss_n, 4 );
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( t5 + ss_r + ss_p + ss_p + t5 - ss_n + ss_r + ss_p + t5 - ss_n, 4 );
        WriteSocket ();
      break; /* t5+rnd+pid+req | 2t5+rnd+pid+2req | 3t5+2rnd+pid+3req */

      case non_count_request :

#ifdef VERBOSE_FLAG
printf ( "non_count_request - pid %d", ss_n );
printf ( " -> sent: %d", t5 - t6 );
printf ( " (%d,%d)", t5, t6 );
printf ( " %d\n", ss_r );
#endif /* VERBOSE_FLAG */

        bd ( non_count_request, ss_n );
        BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( ss_r + t5 + ss_p, 4 );
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( t5 + ss_r + ss_p + ss_p + t5 - ss_n, 4 );
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( t5 + ss_r + ss_p + ss_p + t5 - ss_n + ss_r + ss_p + t5 - ss_n, 4 );
        WriteSocket ();
      break; /* t5+rnd+pid+req | 2t5+rnd+pid+2req | 3t5+2rnd+pid+3req */

      case init_request :
        {
          int nn, mm, p;

          nn = 0;
          for ( k = 0 ; k < max_hiip ; k++ ) {
            if ( ma [ ps_store + k ] ) {
              if ( yy == ( ma [ ps_store + max_hiip + ( 2 * k ) ] +
                      ( 10 * ma [ ps_store + max_hiip + ( 2 * k ) + 1 ] ) ) ) {
#ifdef VERBOSE_FLAG
g_pid ( k, &p );
printf ( "        k=#%d matches this ipaddress - pid %d\n", k, p );
#endif /* VERBOSE_FLAG */

                 nn++;
	      }
	    }
	  }

#ifdef VERBOSE_FLAG
printf ( "    init_request - %d process(es) currently stored of %dth ", nn, yy );
print_ipa ( yy );
printf ( "\n" );
#endif /* VERBOSE_FLAG */

          mm = ( ma [ hi_store + ( 2 * yy ) ] +
               ( 10 *  ma [ hi_store + ( 2 * yy ) + 1 ] ) );

#ifdef VERBOSE_FLAG
printf ( "    max authorised for this ipaddress: %d\n", mm );
#endif /* VERBOSE_FLAG */

          if ( nn < mm ) {
            k = sto_ps ( yy, ss_n,
                ( ss_v / 256 ) ,
                ( ( ss_v / 16 ) % 16 ),
                ( ss_v % 16 ),
                ( ss_u / 16 ),
                ( ss_u % 16 ),
                ( ss_t / 256 ) ,
                ( ( ss_t / 16 ) % 16 ),
                ( ss_t % 16 ) );
            upd_ps ( k );

#ifdef VERBOSE_FLAG
/*
print_WHOLE_ARRAY ();
*/
print_ps ();
printf ( "init_request" );
printf ( " -> sent: %d (ok) %d\n", init_request + 1, ss_r );
#endif /* VERBOSE_FLAG */

            BToolkitd_PUT_TOK ( 4, 4 );        /* 4 args to be sent */
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( ss_r + ss_n + init_request + 1, 4 );
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( init_request + 1 + ss_r + ss_n + init_request + 1, 4 );
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( init_request + 1 + ss_r + init_request + ss_r + 1 + ss_n + init_request + 1, 4 );
            sprintf ( buf, "\n  BToolkitd %s: authorising with licence #%d\n\n", no_toolkit_short_ver, k + 1 );
            BToolkitd_PUT_TOK ( STR, 1 );
            BToolkitd_PUT_STR ( ( int * ) buf );
            WriteSocket ();
	  }
          else {

#ifdef VERBOSE_FLAG
printf ( "    so already at maximum" );
print_ps ();
printf ( "init_request" );
printf ( " -> sent: %d (full) %d\n", init_request, ss_r );
#endif /* VERBOSE_FLAG */

            BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( ss_r + ss_n + init_request - 2, 4 );
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( init_request - 2 + ss_r + ss_n + init_request - 2, 4 );
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( init_request - 2 + ss_r + init_request - 2 + ss_r + ss_n + init_request - 2, 4 );
            WriteSocket ();
	  }
	}
      break;

      case pre_init_request :
        {
          int mm, nn, p;
          char pre_init_str [ 1000 ];

#ifdef VERBOSE_FLAG
printf ( "\n" );
#endif /* VERBOSE_FLAG */

          nn = 0;
          strcpy ( pre_init_str, "ZZ" );
          for ( k = 0 ; k < max_hiip ; k++ ) {
            if ( /* ma [ ps_store + k ] */ 0 ) { /* TEMPORARILY SUPPRESS */
              if ( yy == ( ma [ ps_store + max_hiip + ( 2 * k ) ] +
                      ( 10 * ma [ ps_store + max_hiip + ( 2 * k ) + 1 ] ) ) ) {
                g_pid ( k, &p );
                sprintf ( buf, "%d ", p );
                if ( ( strlen ( pre_init_str ) + strlen ( buf ) ) < 1000 ) {

#ifdef VERBOSE_FLAG
printf ( "  pid(k)=#%d matches this ipaddress - pid %d\n", k, p );
#endif /* VERBOSE_FLAG */

                  strcat ( pre_init_str, buf );             
                  nn++;
		}
	      }
	    }
	  }          

#ifdef VERBOSE_FLAG
printf ( "    sending STR `%s' (tot %d)\n", pre_init_str, nn );
print_ps ();
printf ( "pre_init_request" );
printf ( " -> sent: %d (ok) %d\n", pre_init_request + 1, ss_r );
#endif /* VERBOSE_FLAG */

          BToolkitd_PUT_TOK ( 4, 4 );        /* 4 args to be sent */
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( ss_r + ss_n + pre_init_request + 1, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( pre_init_request + 1 + ss_r + ss_n + pre_init_request + 1, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( pre_init_request + 1 + ss_r + pre_init_request + ss_r + 1 + ss_n + pre_init_request + 1, 4 );
          BToolkitd_PUT_TOK ( STR, 1 );
          BToolkitd_PUT_STR ( ( int * ) pre_init_str );
          WriteSocket ();
	}
      break;

      case hiip_request :

        ss_r = ( dl () - t4 );
        read_ ( &t_, tda );
        ss_r = ( ss_r / t_ );
        if ( tt ) ss_r--;


  /***
  hiip_request - hprot now redundant - always ipaddress protection!
  ***/
#ifdef VERBOSE_FLAG
printf ( "hiip_request" );
printf ( " -> sent: %d %d\n", hiip_request + /* ipaddress */ 1, ss_r );
#endif /* VERBOSE_FLAG */

        BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( ss_r + hiip_request + /* ipaddress */ 1 + ss_p, 4 );
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( hiip_request + /* ipaddress */ 1 + ss_r + ss_p + ss_p + hiip_request + /* ipaddress */ 1 - ss_n, 4 );
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( hiip_request + /* ipaddress */ 1 + ss_r + ss_p + ss_p + hiip_request + /* ipaddress */ 1 - ss_n + ss_r + ss_p + hiip_request + /* ipaddress */ 1 - ss_n, 4 );
        WriteSocket ();

        ck_old_ps ();

      break;

      case fini_request :
	  {

#ifdef VERBOSE_FLAG
printf ( "fini_request" );
printf ( " -> sent: %d %d\n", fini_request + 1, ss_r );
#endif /* VERBOSE_FLAG */

          zz = chk_pid  ( ss_n );
          if ( zz == -1 ) {

#ifdef VERBOSE_FLAG
printf ( "\nCOULDN'T REMOVE pid %d\n", ss_n );
#endif /* VERBOSE_FLAG */

            ;
	  }
          else {

#ifdef VERBOSE_FLAG
void print_actual_ip_arr ();
void print_user_id_arr ();
void print_user_name_arr ();
void print_user_time_arr ();
#endif /* VERBOSE_FLAG */

            ma [ ps_store + zz ] = 0;

#ifdef VERBOSE_FLAG
printf ( "removed pid %d stored at pid position #%2d\n", ss_n, zz );
#endif /* VERBOSE_FLAG */

          }
          actual_ip_arr [ zz ] = 0;
          user_id_arr [ zz ] = 0;
          user_name_arr [ zz * user_name_len ] = 0;
          user_time_arr [ zz ] = 0;

#ifdef VERBOSE_FLAG
print_ps ();
print_actual_ip_arr ();
print_user_id_arr ();
print_user_name_arr ();
print_user_time_arr ();
#endif /* VERBOSE_FLAG */

        BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( ss_r + ss_n + fini_request + 1, 4 );
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( fini_request + 1 + ss_r + ss_n + fini_request + 1, 4 );
        BToolkitd_PUT_TOK ( NUM, 1 );
        BToolkitd_PUT_TOK ( fini_request + 1 + ss_r + fini_request + ss_r + 1 + ss_n + fini_request + 1, 4 );
        WriteSocket ();
	}
      break;

      case rem_zombie_request :
        {
          zz = chk_pid ( ss_n );
          if ( zz != -1 ) {

            BToolkitd_PUT_TOK ( 5, 4 );        /* 5 args to be sent */
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( ss_r + ss_n + rem_zombie_request + 1, 4 );
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( rem_zombie_request + 1 + ss_r + ss_n + rem_zombie_request + 1, 4 );
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( rem_zombie_request + 1 + ss_r + rem_zombie_request + ss_r + 1 + ss_n + rem_zombie_request + 1, 4 );
            status_for_zombie ( zz );
            WriteSocket ();
            ma [ ps_store + zz ] = 0;

#ifdef VERBOSE_FLAG
printf ( "\nzombie pid %d removed\n", ss_n );
#endif /* VERBOSE_FLAG */

          }
          else {

            BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( ss_r + ss_n + rem_zombie_request + 2, 4 );
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( rem_zombie_request + 2 + ss_r + ss_n + rem_zombie_request + 2, 4 );
            BToolkitd_PUT_TOK ( NUM, 1 );
            BToolkitd_PUT_TOK ( rem_zombie_request + 2 + ss_r + rem_zombie_request + ss_r + 2 + ss_n + rem_zombie_request + 2, 4 );
            WriteSocket ();

#ifdef VERBOSE_FLAG
printf ( "\nzombie pid %d not removed\n", ss_n );
#endif /* VERBOSE_FLAG */

	    }
	  }
        break;

      case BTd_id_BT_id_check :
        {

#ifdef VERBOSE_FLAG
printf ( "BTd_id_BT_id_check" );
printf ( " -> sent: %d %d\n", btd_id + 2, ss_r );
#endif /* VERBOSE_FLAG */

          BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( ss_r + ss_n + btd_id + 2, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( btd_id + 2 + ss_r + ss_n + btd_id + 2, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( btd_id + 2 + ss_r + btd_id + ss_r + 2 + ss_n + btd_id + 2, 4 );
          WriteSocket ();
	}
        break;

      case user_uid_request :
        {
          int a, b, c, d, e, f, g, h, m;
          long unsigned ipa;
          long unsigned calc_ip ();
          void print_actual_ip_arr ();
          void print_user_id_arr ();
          void print_user_name_arr ();
          void print_user_time_arr ();

          ServerSocket_calc_ipa;

/***
printf ( "\n\n\n\n                   +++++user_uid_request: chk_pid(%d)=%d\n\n\n\n", ss_s, chk_pid ( ss_s ) );
***/

          if ( chk_pid ( ss_s ) != -1 ) { /* protect it! */
            user_id_arr [ chk_pid ( ss_s ) ] = ss_n;
            m = match_actual_ip_arr_and_user_id ( ipa, ss_n );
            m--;  /* don't include this one! */
	  }
          else {

#ifdef VERBOSE_FLAG
printf ( "\n\n\n\n                   ->->->->->->user_uid_request: chk_pid -1 - not storing\n\n\n\n" );
#endif /* VERBOSE_FLAG */

            m = 0;
	  }

#ifdef VERBOSE_FLAG
printf ( "user_uid_request ipa=%d (%d.%d.%d.%d)\n             uid=%d pid=%d this pos=%d", ipa, 16*a+b, 16*c+d, 16*e+f, 16*g+h, ss_n, ss_s, chk_pid ( ss_s ) + 1 );
printf ( " other matches=%d\n", m );
printf ( " -> sent: %d %d\n", m + 5, ss_r );
print_actual_ip_arr ();
print_user_id_arr ();
print_user_name_arr ();
print_user_time_arr ();
#endif /* VERBOSE_FLAG */

          BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( ss_r + ss_n + m + 5, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( m + 5 + ss_r + ss_n + m + 5, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( m + 5 + ss_r + m + ss_r + 5 + ss_n + m + 5, 4 );
          WriteSocket ();
	}
        break;

      case user_name_request :
        {
          int a, b, c, d, e, f, g, h, m, i, k;
          long unsigned ipa;
          long unsigned calc_ip ();
          void print_actual_ip_arr ();
          void print_user_id_arr ();
          void print_user_name_arr ();
          void print_user_time_arr ();

          ServerSocket_calc_ipa;

/***
printf ( "\n\n\n\n                   +++++user_name_arr: chk_pid(%d)=%d\n\n\n\n", ss_s, chk_pid ( ss_s ) );
***/

          if ( chk_pid ( ss_s ) != -1 ) { /* protect it! */

            k = chk_pid ( ss_s ) * user_name_len;

#ifdef VERBOSE_FLAG
printf ( "storing %s at user_name_arr [ %d .. ", buf, k );
#endif /* VERBOSE_FLAG */

            i = 0;
              while ( ( buf [ i ] != '\0' ) && ( i < user_name_len - 1 ) ) {
            user_name_arr [ k++ ] = buf [ i++ ];
            }
            user_name_arr [ k ] = '\0';
            user_time_arr [ chk_pid ( ss_s ) ] = time ( NULL );
          
#ifdef VERBOSE_FLAG
printf ( "%d ]\n", k );
#endif /* VERBOSE_FLAG */

            m = match_actual_ip_arr_and_user_id ( ipa, ss_n );
            m--;  /* don't include this one! */
	  }
          else {

#ifdef VERBOSE_FLAG
printf ( "\n\n\n\n                   ->->->->->->user_name_request: chk_pid -1 - not storing\n\n\n\n" );
#endif /* VERBOSE_FLAG */

            m = 0;
	  }

#ifdef VERBOSE_FLAG
printf ( "user_name_request ipa=%d (%d.%d.%d.%d)\n             name=%s uid=%d pid=%d this pos=%d", ipa, 16*a+b, 16*c+d, 16*e+f, 16*g+h, buf, ss_n, ss_s, chk_pid ( ss_s ) + 1 );
printf ( " other matches=%d\n", m );
printf ( " -> sent: %d %d\n", m + 5, ss_r );
print_actual_ip_arr ();
print_user_id_arr ();
print_user_name_arr ();
print_user_time_arr ();
#endif /* VERBOSE_FLAG */

          BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( ss_r + ss_n + m + 5, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( m + 5 + ss_r + ss_n + m + 5, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( m + 5 + ss_r + m + ss_r + 5 + ss_n + m + 5, 4 );
          WriteSocket ();
	}
        break;

      case chk_vers_request :
        {
          int a, b, c, d, e, f, g, h, m, i, k;
          long unsigned ipa;
          long unsigned calc_ip ();
          void print_actual_ip_arr ();
          void print_user_id_arr ();
          void print_user_name_arr ();
          void print_user_time_arr ();
          char out_buf [ 250 ];

#ifdef VERBOSE_FLAG
printf ( "chk_vers_request bt ver=%s btd ver=%s\n  uid=%d pid=%d this pos=%d", buf, no_toolkit_short_ver, ss_n, ss_s, chk_pid ( ss_s ) + 1 );
printf ( " other matches=%d\n", m );
printf ( " -> sent: %d %d\n", m + 5, ss_r );
print_actual_ip_arr ();
print_user_id_arr ();
print_user_name_arr ();
print_user_time_arr ();
#endif /* VERBOSE_FLAG */

          BToolkitd_PUT_TOK ( 4, 4 );        /* 4 args to be sent */
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( ss_r + ss_n + init_request + 1, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( init_request + 1 + ss_r + ss_n + init_request + 1, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( init_request + 1 + ss_r + init_request + ss_r + 1 + ss_n + init_request + 1, 4 );
          BToolkitd_PUT_TOK ( STR, 1 );
          if ( strcmp ( buf, no_toolkit_short_ver ) != 0 ) {
            sprintf ( out_buf, "  WARNING: BToolkit/BToolkitd versions differ: %s/%s\n\n", buf, no_toolkit_short_ver );
	  }
          else {
            out_buf [ 0 ] = '\0';
	  }
          BToolkitd_PUT_STR ( ( int * ) out_buf );
          WriteSocket ();

	}
        break;

      case Bpda_time_request :
        {

          int i;
          time_t t1, t2;

          i = 0;
          t1 = 0;
          while ( buf [ i ] != '\0' ) { t1 = ( 10 * t1 ) + buf [ i++ ] - '0'; }

          t2 = time ( NULL );
          if   ( t1 > t2 ) i = 7651;
          else             i = 7652;

#ifdef VERBOSE_FLAG
printf ( "Bpda_time_request (%s)...\n", buf );
printf ( "Bpda time received: %s", ctime ( &t1 ) );
t1 += 3600;
printf ( "Bpda actual time:   %s", ctime ( &t1 ) );
printf ( "time now:           %s", ctime ( &t2 ) );
printf ( " -> sent: %d %d\n", i, ss_r );
print_actual_ip_arr ();
print_user_id_arr ();
print_user_name_arr ();
print_user_time_arr ();
#endif /* VERBOSE_FLAG */

          BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( ss_r + ss_n + i, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( i + ss_r + ss_n + i, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( i + ss_r + i + ss_r + ss_n + i, 4 );
          WriteSocket ();

	}
        break;

      case am_anonymous_server_request :
        {
          int yy;

          yy = chk_hiip_is_anonymous_server  (
                  ( ss_v / 256 ) ,
                  ( ( ss_v / 16 ) % 16 ),
                  ( ss_v % 16 ),
                  ( ss_u / 16 ),
                  ( ss_u % 16 ),
                  ( ss_t / 256 ) ,
                  ( ( ss_t / 16 ) % 16 ),
                  ( ss_t % 16 ) );

#ifdef VERBOSE_FLAG
printf ( "am_anonymous_server_request:\n    chk_hiip_is_anonymous_server returned %d\n", yy );
print_actual_ip_arr ();
print_user_id_arr ();
print_user_name_arr ();
print_user_time_arr ();
#endif /* VERBOSE_FLAG */

          BToolkitd_PUT_TOK ( 1, 4 );   /* 1 string to be sent */
          BToolkitd_PUT_TOK ( STR, 1 );
          if ( yy == 0 ) {
            strcpy ( buf, "\n\n  You cannot run the BToolkit on the BToolkitd licence\n  server platform with an anonymous-client licence\n\n  To do this you need either a named-client or a hardware licence\n" );
	  }
          else {
            strcpy ( buf, " " );
	  }
          BToolkitd_PUT_STR ( ( int * ) buf );
          WriteSocket ();
	}
        break;

      case BPInfo_remove :
        {
          int a, b, c, d, e, f, g, h, m;
          long unsigned ipa;
          long unsigned calc_ip ();
          void print_actual_ip_arr ();
          void print_user_id_arr ();
          void print_user_name_arr ();
          void print_user_time_arr ();

          ServerSocket_calc_ipa;

#ifdef VERBOSE_FLAG
          printf ( "BPInfo_remove ipa=%d (%d.%d.%d.%d)\n             pid=%d\n", ipa, 16*a+b, 16*c+d, 16*e+f, 16*g+h, ss_n );
#endif /* VERBOSE_FLAG */

          m = remove_actual_ip_arr_and_pid ( ipa, ss_n );

          BToolkitd_PUT_TOK ( 3, 4 );        /* 3 args to be sent */
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( ss_r + ss_n + m + 8, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( m + 8 + ss_r + ss_n + m + 8, 4 );
          BToolkitd_PUT_TOK ( NUM, 1 );
          BToolkitd_PUT_TOK ( m + 8 + ss_r + m + ss_r + 8 + ss_n + m + 8, 4 );
          WriteSocket ();
	}
        break;

      case BToolkitd_util_status :
        int_status ();
        WriteSocket ();
        break;

      case BToolkitd_util_down :
        {
           struct passwd * passw_buf;
           int ok_to_down;

#ifdef VERBOSE_FLAG
printf ( "BToolkitd_util_down uid=%d getuid ()=%d\n", ss_n, getuid () );
#endif /* VERBOSE_FLAG */

          passw_buf = getpwuid ( ss_n );
          if ( passw_buf == NULL ) {
            perror ( "\n\n  getpwuid () failed\n\n" );
            exit ( 1 );
	  }

#ifdef VERBOSE_FLAG
printf ( "BToolkitd_util_down passw_buf -> pw_name = %s\n", passw_buf -> pw_name );
#endif /* VERBOSE_FLAG */

          if ( strcmp ( ( passw_buf -> pw_name ), "root" ) == 0 ) {
            ok_to_down = 1;
          }
          else {
            ok_to_down = ( ( ss_n == getuid () ) != 0 );
	  }
          if ( ok_to_down ) {
            rm_pid_file ();  /* this also puts out a syslog halted message */
            int_down ();
            WriteSocket ();
            exit ( 0 );
	  }
          else {
            BToolkitd_PUT_TOK ( 1, 4 );   /* 1 string to be sent */
            BToolkitd_PUT_TOK ( STR, 1 );
            passw_buf = getpwuid ( geteuid ( ) );
            if ( passw_buf == NULL ) {
              perror ( "\n\n  getpwuid ( geteuid () ) failed\n\n" );
              exit ( 1 );
	    }
            if ( strcmp ( ( passw_buf -> pw_name ), "root" ) == 0 ) {
              sprintf ( buf, "\n  Only %s can take BToolkitd %s down\n\n",
                                  ( passw_buf -> pw_name ), no_toolkit_short_ver );
	    }
            else {
              sprintf ( buf, "\n  Only %s or root can take BToolkitd %s down\n\n",
                                  ( passw_buf -> pw_name ), no_toolkit_short_ver );
	    }
            BToolkitd_PUT_STR ( ( int * ) buf );
            WriteSocket ();
	  }
	}
        break;

      case BToolkitd_util_remove :
        int_remove ( ss_n, /* status_flag = */ 1 );
        WriteSocket ();
        break;

      case BToolkitd_util_generate :
        {
          struct passwd * passw_buf;
          int ok_to_generate;

#ifdef VERBOSE_FLAG
printf ( "BToolkitd_util_generate uid=%d getuid ()=%d\n", ss_n, getuid () );
#endif /* VERBOSE_FLAG */

          if ( is_alex ) {
            BToolkitd_PUT_TOK ( 1, 4 );   /* 1 string to be sent */
            BToolkitd_PUT_TOK ( STR, 1 );
              sprintf ( buf, "\n  BToolkitd %s: inappropriate hardware licence\n\n",
                                                         no_toolkit_short_ver );
            BToolkitd_PUT_STR ( ( int * ) buf );
            WriteSocket ();
            return;
	  }

          passw_buf = getpwuid ( ss_n );
          if ( passw_buf == NULL ) {
            perror ( "\n\n  getpwuid () failed\n\n" );
            exit ( 1 );
	  }

#ifdef VERBOSE_FLAG
printf ( "BToolkitd_util_generate passw_buf -> pw_name = %s\n", passw_buf -> pw_name );
#endif /* VERBOSE_FLAG */

          if ( strcmp ( ( passw_buf -> pw_name ), "root" ) == 0 ) {
            ok_to_generate = 1;
          }
          else {
            ok_to_generate = ( ( ss_n == getuid () ) != 0 );
	  }
          if ( ok_to_generate ) {
            void int_generate ();
            int_generate ();
            WriteSocket ();
	  }
          else {
            BToolkitd_PUT_TOK ( 1, 4 );   /* 1 string to be sent */
            BToolkitd_PUT_TOK ( STR, 1 );
            passw_buf = getpwuid ( geteuid ( ) );
            if ( passw_buf == NULL ) {
              perror ( "\n\n  getpwuid ( geteuid () ) failed\n\n" );
              exit ( 1 );
	    }
            if ( strcmp ( ( passw_buf -> pw_name ), "root" ) == 0 ) {
              sprintf ( buf, "\n  BToolkitd %s: only %s can do this\n\n",
                                  no_toolkit_short_ver, ( passw_buf -> pw_name ) );
	    }
            else {
              sprintf ( buf, "\n  BToolkitd %s: only %s or root can do this\n\n",
                                  no_toolkit_short_ver, ( passw_buf -> pw_name ) );
	    }
            BToolkitd_PUT_STR ( ( int * ) buf );
            WriteSocket ();
	  }
        }
        break;

      case BToolkitd_util_reread :
        {
           struct passwd * passw_buf;
           int ok_to_reread;

#ifdef VERBOSE_FLAG
printf ( "BToolkitd_util_down uid=%d getuid ()=%d\n", ss_n, getuid () );
#endif /* VERBOSE_FLAG */

          passw_buf = getpwuid ( ss_n );
          if ( passw_buf == NULL ) {
            perror ( "\n\n  getpwuid () failed\n\n" );
            exit ( 1 );
	  }

#ifdef VERBOSE_FLAG
printf ( "BToolkitd_util_down passw_buf -> pw_name = %s\n", passw_buf -> pw_name );
#endif /* VERBOSE_FLAG */

          if ( strcmp ( ( passw_buf -> pw_name ), "root" ) == 0 ) {
            ok_to_reread = 1;
          }
          else {
            ok_to_reread = ( ( ss_n == getuid () ) != 0 );
	  }
          if ( ok_to_reread ) {
            int_reread ();
            WriteSocket ();
	  }
          else {
            BToolkitd_PUT_TOK ( 1, 4 );   /* 1 string to be sent */
            BToolkitd_PUT_TOK ( STR, 1 );
            passw_buf = getpwuid ( geteuid ( ) );
            if ( passw_buf == NULL ) {
              perror ( "\n\n  getpwuid ( geteuid () ) failed\n\n" );
              exit ( 1 );
	    }
            if ( strcmp ( ( passw_buf -> pw_name ), "root" ) == 0 ) {
              sprintf ( buf, "\n  Only %s can effect a BToolkitd %s reread\n\n",
                                  ( passw_buf -> pw_name ), no_toolkit_short_ver );
	    }
            else {
              sprintf ( buf, "\n  Only %s or root can effect a BToolkitd %s reread\n\n",
                                  ( passw_buf -> pw_name ), no_toolkit_short_ver );
	    }
            BToolkitd_PUT_STR ( ( int * ) buf );
            WriteSocket ();
	  }
	}
        break;


      }  /* end switch */

    } /* if ( ! ss_err ) */

#ifdef VERBOSE_FLAG
    else {
      printf ( "discarding %d\n", ( ss_p - ss_n ) /* req */);
    }
#endif /* VERBOSE_FLAG */

} /* proc_socket () */

void
ss_loop ()
{
  int rep, insize;

  while ( 1 ) {

    BToolkitd_ACCEPT ( & rep );
    if ( ! rep ) exit ( 1 );

    BToolkitd_READ( &rep, &insize );
    if ( ! rep )
    {
        /* why stop the service if a socket fails? Clean up and keep going.*/
	BToolkitd_CLOSE ( &rep );
    	/*exit ( 1 );*/
	continue;
    }

    proc_socket ();

  }

}
