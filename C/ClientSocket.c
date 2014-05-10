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
#ifndef INADDR_NONE
#define INADDR_NONE  0xffffffff
#endif /* INADDR_NONE */


#define BToolkitd_Client_ClientPV1 { "dummy" }
#define BToolkitd_Client_ClientPV2 10000
#define BToolkitd_Client_ClientPV3 10000

#include "BToolkitd_ClientServer/CDE/C/BToolkitd_Client_Client.g"

#include "BToolkitd_ClientServer/CDE/C/BToolkitd_Client_Client.c"


#include "../MOTIF/BMotif_globals.h"


char pid_id_file [ sock_buf_len_MAX + 1 ];
char serv_addr_name [ 255 ];

int serv_name_found = 0;

#define null_offset 13245687

int hi_l;
int hi_m;
int hi_h;

/* enc - multiple definitions */
#ifndef H_DATA_FILE_PTR

#define H_DATA_FILE_PTR

FILE * data_file_ptr;

#endif


void
put_num( r_1, r_2, r_3 ) /* ipa - used by BMotif, bmotif.c, b.c */
int * r_1;
int * r_2;
int * r_3;
{
  int i;
  int g_j [ 16 ];
  char s [ 10 ];
  struct utsname u_s;
  struct hostent * h_s;

  s [ 0 ] = 'a' + 12;
  s [ 6 ] = s [ 0 ] + 8;
  s [ 7 ] = '\0';
  s [ 1 ] = s [ 0 ] + 3;
  s [ 5 ] = s [ 1 ] + 4;
  s [ 3 ] = s [ 0 ] - 4;
  s [ 4 ] = s [ 1 ];
  s [ 2 ] = s [ 3 ] - 1;
  i = 0;
  while ( s [ i ] != '\0' ) {
    s [ i ]--;
    i++;
  }
  for ( i = 0 ; i < 8 ; i++ ) {
    g_j [ i ] = 0;
  }
  if ( uname ( &u_s ) == -1 ) {
    fprintf ( bstdout, "B-Toolkit error code: 12224\n" );
    Kill_bplatform_and_exit ( 0, 0 );
  }
  if ( ( h_s = gethostbyname ( u_s.nodename ) ) == NULL ) {
    fprintf ( bstdout, "B-Toolkit error code: 12225\n" );
    Kill_bplatform_and_exit ( 0, 0 );
  }
  for ( i = 0 ; i < h_s -> h_length ; i++ ) {
    g_j [ i ] =  ( int ) h_s -> h_addr_list [ 0 ] [ i ];
    if ( g_j [ i ] < 0 ) {
      g_j [ i ] = g_j [ i ] + 256;
    }
  }

#ifdef VERBOSE_FLAG
  fprintf ( bstdout, "\nipaddress of this platform: %d.%d.%d.%d", g_j [ 0 ] , g_j [ 1 ] , g_j [ 2 ] , g_j [ 3 ] );
  {
    int a, b, c, d, e, f, g, h, x, y;
    a = g_j [ 0 ] / 16;
    b = g_j [ 0 ] % 16;
    c = g_j [ 1 ] / 16;
    d = g_j [ 1 ] % 16;
    e = g_j [ 2 ] / 16;
    f = g_j [ 2 ] % 16;
    g = g_j [ 3 ] / 16;
    h = g_j [ 3 ] % 16;
    fprintf ( bstdout, "\ndenary equilvalent: %d %d %d %d %d %d %d %d\n\n", a, b, c, d, e, f, g, h );
  }
#endif /* VERBOSE_FLAG */

  * r_1 = ( ( g_j [ 0 ] / 16 ) * 256 ) + ( ( g_j [ 0 ] % 16 ) * 16 ) + ( g_j [ 1 ] / 16 );
  * r_2 = ( ( g_j [ 1 ] % 16 ) * 16 ) + ( g_j [ 2 ] / 16 );
  * r_3 = ( ( g_j [ 2 ] % 16 ) * 256 ) + ( ( g_j [ 3 ] / 16 ) * 16 ) + ( g_j [ 3 ] % 16 );

} /* put_num() */


int
get_BToolkitd_tcpip_exit ( bkit_dir, toExit )
char * bkit_dir;
int toExit;
{
  struct servent * servent_ptr;
  struct utsname u_s;
  struct hostent * h_s;
  int i, m;
  unsigned long addr;

  if ( ( servent_ptr = ( getservbyname ( "BToolkitd", "tcp" ) ) ) ) {
    port = ( ntohs ( servent_ptr -> s_port ) );
  }
  else {
    strcpy ( buf, bkit_dir );
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

  strcpy ( buf, bkit_dir );
  strcat ( buf, Btkd_server_file_name );
  Bfile = fopen ( buf, "r" );
  if ( Bfile != NULL ) {
#ifdef VERBOSE_FLAG
  printf ( "\ntaking ipaddress from %s\n", buf );
#endif /* VERBOSE_FLAG */
    i = 0;
    c = getc ( Bfile );
    while ( c == ' ' || c == '\t' || c == '\n' ) c = getc ( Bfile );
/*
    while ( ( ( c >= '0' && c <= '9' ) || c == '.' ) && i < 20 ) {
*/
    while ( c != ' ' && c != '\t' && c != '\n' && c != EOF ) {
      serv_addr [ i ] = ( char ) c;
      i++;
      c = getc ( Bfile );
    }
    serv_addr [ i ] = '\0';
    fclose ( Bfile );

    /***
    see if gethostbyname works if not a dotted quad!
    ***/
    i = 0;
    c = 0;
    while ( serv_addr [ i ] != '\0' ) {
      if ( serv_addr [ i ] == '.' ) c++;
      i++;
    }
    if ( c != 3 ) {
      if ( ( h_s = gethostbyname ( serv_addr ) ) != 0 ) {
        int g_j [ 16 ];
#ifdef VERBOSE_FLAG
        printf ( "gethostbyname %s -> ", serv_addr );
        fflush ( bstdout );
#endif /* VERBOSE_FLAG */
        for ( i = 0 ; i < 8 ; i++ ) g_j [ i ] = 0;
        for ( i = 0 ; i < h_s -> h_length ; i++ ) {
          g_j [ i ] =  ( int ) h_s -> h_addr_list [ 0 ] [ i ]; /* + 256 */
          if ( g_j [ i ] < 0 ) g_j [ i ] = g_j [ i ] + 256;
        }
        sprintf ( serv_addr, "%d.%d.%d.%d", g_j [ 0 ], g_j [ 1 ], g_j [ 2 ], g_j [ 3 ] );
#ifdef VERBOSE_FLAG
        printf ( "%s\n", serv_addr );
#endif /* VERBOSE_FLAG */
      }
      else {
      printf ( "\n\n            The contents of %s:\n\n                %s\n\n            does not constitute an ipaddress,\n            but \"gethostbyname\" failed\n\n\n", buf, serv_addr );
      if(toExit==1) {Kill_bplatform_and_exit ( 0, 0 );} else {return 0;}
      }
    }
  }

  else {
#ifdef VERBOSE_FLAG
    printf ( "%s%s does not exist - taking host ipaddress\n", bkit_dir, Btkd_server_file_name );
#endif /* VERBOSE_FLAG */
    if ( uname ( &u_s ) == -1 ) {
      fprintf ( bstdout, "B-Toolkit error code: 12224\n" );
      if(toExit==1) {Kill_bplatform_and_exit ( 0, 0 );} else {return 0;}
    }
    if ( ( h_s = gethostbyname ( u_s.nodename ) ) == NULL ) {
      fprintf ( bstdout, "B-Toolkit error code: 12225\n" );
      if(toExit==1) {Kill_bplatform_and_exit ( 0, 0 );} else {return 0;}
    }
    serv_addr [ 0 ] =  '\0';
    for ( i = 0 ; i < h_s -> h_length ; i++ ) {
      c = ( int ) ( h_s -> h_addr_list [ 0 ] [ i ] ); /* + 256 !!! */
      if ( c < 0 ) {
        c = c + 256;
      }
      CreNumInBuf ( serv_addr, c );
      if ( i < 3 ) strcat ( serv_addr, "." );
    }
  }

  /***
  see if we can find name (serv_name_found)
  ***/
  i = 0;
  for ( j = 0 ; j < 4 ; j++ ) {
    m = 0;
    while ( serv_addr [ i ] != '.' && serv_addr [ i ] != '\0' ) {
     m = ( 10 * m ) + serv_addr [ i ] - '0';
     i++;
    }
    i++;
    serv_addr_name [ j ] = ( char ) m;
  }
  if (  ( int ) ( addr = inet_addr ( serv_addr ) ) != -1 ) {
    if ( ( h_s = gethostbyaddr ( (char *) &addr, sizeof ( addr ), AF_INET)) != 0 ) {
      strcpy ( serv_addr_name, h_s -> h_name );
      i = 0;
      while ( serv_addr_name [ i ] != '.' && serv_addr_name [ i ] != '\0' ) i++;
      if (  serv_addr_name [ i ] == '.' ) serv_addr_name [ i ] = '\0';
      serv_name_found = 1;

#ifdef VERBOSE_FLAG
    printf ( "\nserv_addr_name |%s| found from |%s|\n", serv_addr_name, serv_addr );
#endif /* VERBOSE_FLAG */

    }

#ifdef VERBOSE_FLAG
    else
      printf ( "\nserv_addr_name not found from |%s|\n", serv_addr );
#endif /* VERBOSE_FLAG */

  }

#ifdef VERBOSE_FLAG
  else
    printf ( "\nserv_addr_name not found from |%s|\n", serv_addr );
#endif /* VERBOSE_FLAG */

#ifdef VERBOSE_FLAG
  if ( serv_name_found ) 
    printf ( "\nattempting to connect to BToolkitd at tcp/ip %s,%d\n", serv_addr_name, port );
  else
    printf ( "\nattempting to connect to BToolkitd at tcp/ip %s,%d\n", serv_addr, port );
#endif /* VERBOSE_FLAG */

  if ( serv_name_found ) 
/*
    printf ( "\n  Waiting for response from BToolkitd (%s,%d)\n", serv_addr_name, port );
  else
    printf ( "\n  Waiting for response from BToolkitd (%s,%d)\n", serv_addr, port );
*/
    printf ( "\n  Attempting to contact BToolkitd @ (%s,%d)\n", serv_addr_name, port );
  else
    printf ( "\n  Attempting to contact BToolkitd @ (%s,%d)\n", serv_addr, port );
  fflush ( stdout );

  BToolkitd_Client_INIT ( serv_addr, port );
  
  return 1;
/*
  printf ( "ok\n" );
*/
}

void
get_BToolkitd_tcpip ( bkit_dir )
char * bkit_dir;
{
   get_BToolkitd_tcpip_exit (bkit_dir, 1 );
}

void
remove_my_zombie_pid ( pid, my_id )
pid_t pid;
uid_t my_id;
{
  int ClientSocketNUM ();
  FILE * Bcom;
  char buf [ 250 ];
  int c, i, is_num, p, my_proc;
  struct stat stat_buf;

  system ( "ls /tmp/.B_* > .Bcom" );

  Bcom = fopen ( ".Bcom", "r" );
  if ( Bcom != NULL ) {
    c = getc ( Bcom );
    while ( c != EOF ) {
      i = 0;
      while ( c != EOF && c != '\n' ) {
        buf [ i ] = ( char ) c;
        i++;
        c = getc ( Bcom );
      }
      buf [ i ] = '\0';
      p = 0;
      i = 8;
      is_num = 1;
      while ( ( buf [ i ] != '_' ) && ( buf [ i ] != '\0' ) ) {
        if   (  buf [ i ] < '0' || buf [ i ] > '9' ) is_num = 0;
        else                                         p = ( 10 * p ) + buf [ i ] - '0';
        i++;
      }

/***
printf ( "remove_my_zombie_pid - found `%s' %d\n", buf, p );
***/
      if ( is_num && ( p != pid ) ) {

/***
printf ( "    not my own pid\n" );
***/

#if ( defined ( UNKNOWN_VERSION )  )
        if ( getpgrp ( p ) == -1 ) {
#else
        if ( getpgid ( p ) == -1 ) {
#endif /* ( defined ( AIX_VERSION ) || defined ( LINUX_VERSION ) || defined ( SOLARIS_VERSION ) ) */
          lstat ( buf, &stat_buf );
          my_proc = ( ( ( int ) stat_buf.st_uid == my_id ) != 0 );
          if ( my_proc ) {

/***
printf ( "    my process and not active - killing\n" );
***/

#ifdef VERBOSE_FLAG
            printf ( "\n\n%s not active (my process)\nsending rem_zombie_request ", buf);
#endif /* VERBOSE_FLAG */
            unlink ( buf );
          }
          else {
#ifdef VERBOSE_FLAG

/***
printf ( "    not my process and not active - killing\n" );
***/

            printf ( "\n\n%s not active (not my process)\nsending rem_zombie_request ", buf);
#endif /* VERBOSE_FLAG */
              ;
	  }
          ClientSocketNUM ( &cs_nn, &cs_rr, rem_zombie_request, p, pid + 1, pid + 2, pid + 3 );
        }
#ifdef VERBOSE_FLAG
        else {
          printf ( "%s currently active\n", buf );
        }
#endif /* VERBOSE_FLAG */
      }
        if ( c != EOF ) c = getc ( Bcom );
    }
    fclose ( Bcom );
    unlink ( ".Bcom" );
  }
}

void
remove_all_zombie_pid ( p, my_id )
int p;
uid_t my_id;
{
  int ClientSocketNUM ();
  char buf [ 250 ];

  sprintf ( buf, "%d", p );
#ifdef VERBOSE_FLAG
    printf ( "\n\n    remove_all_zombie_pid: %s ", buf );
#endif /* VERBOSE_FLAG */
#if ( defined ( UNKNOWN_VERSION ) )
  if ( getpgrp ( p ) == -1 ) {
#else
  if ( getpgid ( p ) == -1 ) {
#endif /* ( defined ( AIX_VERSION ) || defined ( LINUX_VERSION ) || defined ( SOLARIS_VERSION ) ) */
#ifdef VERBOSE_FLAG
    printf ( "not active\nsending rem_zombie_request ", buf );
#endif /* VERBOSE_FLAG */
    ClientSocketNUM ( &cs_nn, &cs_rr, rem_zombie_request, p, p + 1, p + 2, p + 3 );
  }
#ifdef VERBOSE_FLAG
  else {
    printf ( "currently active\n" );
  }
#endif /* VERBOSE_FLAG */
}




#define UnsChars2Int(s,n) \
  ( ( unsigned char ) s [ n ] * 256 ) + ( unsigned char ) s [ n + 1 ]

/*all the Kill_bplatform_and_exit to be switched off */

int
ClientSocketNUM (nn, rr, req, pid, hi_l, hi_m, hi_h )
int * nn;
int * rr;
int req;
pid_t pid;
int hi_l;
int hi_m;
int hi_h;
{
	/* call this function with the kill bplatform flag on (last parameter) */
	return DoClientSocketNUM(nn,rr,req,pid,hi_l,hi_m,hi_h,1);
}


int
DoClientSocketNUM ( nn, rr, req, pid, hi_l, hi_m, hi_h , killPlatform)
int * nn;
int * rr;
int req;
pid_t pid;
int hi_l;
int hi_m;
int hi_h;
int killPlatform;
{
  int rep, tot_tok, tok, pp;
  int cs_nn, cs_pp, cs_qq, cs_tt;

/***
printf ( "\n\n\t\t  ClientSocketNUM\n" );
***/

  cs_tt = ( time ( NULL ) % 1000 );
  cs_tt = count_request + cs_tt + init_request;
  if ( req == user_uid_request ) cs_tt = getpid ();

  BToolkitd_Client_PUT_TOK ( 6, 4 );    /* 6 args to be sent */
  
  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( cs_tt + pid + cs_tt + req, 4 );

  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( cs_tt + pid + cs_tt, 4 );

  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( cs_tt, 4 );

  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( hi_l + cs_tt + hi_m + hi_h, 4 );

  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( hi_l + hi_h + cs_tt + hi_m + hi_h, 4 );

  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( hi_l + cs_tt + hi_m + hi_l + hi_h, 4 );

    /**************************
      2time+pid+req
      2time+pid
      time
      hi_l+hi_m+hi_h+time
      hi_l+hi_m+2hi_h+time
      2hi_l+hi_m+hi_h+time
    **************************/ 

  BToolkitd_Client_CONNECT ( &rep );
  if ( ! rep ) {
    printf ( "\n  No response from BToolkitd\n\n" );
    if(killPlatform==0){return 0;}
    Kill_bplatform_and_exit ( 0, 0 );
  }


#ifdef VERBOSE_FLAG
  switch ( req ) {
  case hiip_request                : fprintf ( bstdout, "\nClient Socket sending hiip_request " ); break;
  case pre_init_request            : fprintf ( bstdout, "\nClient Socket sending pre_init_request " ); break;
  case init_request                : fprintf ( bstdout, "\nClient Socket sending init_request " ); break;
  case user_uid_request            : fprintf ( bstdout, "\nClient Socket sending user_uid_request " ); break;
  case BTd_id_BT_id_check          : fprintf ( bstdout, "\nClient Socket sending BTd_id_BT_id_check " ); break;
  case BPInfo_remove               : fprintf ( bstdout, "\nClient Socket sending BPInfo_remove " ); break;
  case count_request               : fprintf ( bstdout, "\nClient Socket sending count_request " ); break;
  case non_count_request           : fprintf ( bstdout, "\nClient Socket sending non_count_request " ); break;
  case fini_request                : fprintf ( bstdout, "\nClient Socket sending fini_request " ); break;
  case am_anonymous_server_request : fprintf ( bstdout, "\nClient Socket sending am_anonymous_server_request " ); break;
  case BToolkitd_util_status       : fprintf ( bstdout, "\nClient Socket sending BToolkitd_util_status " ); break;
  case BToolkitd_util_down         : fprintf ( bstdout, "\nClient Socket sending BToolkitd_util_down " ); break;
  case BToolkitd_util_remove       : fprintf ( bstdout, "\nClient Socket sending BToolkitd_util_remove " ); break;
  case BToolkitd_util_reread       : fprintf ( bstdout, "\nClient Socket sending BToolkitd_util_reread " ); break;
  case BToolkitd_util_generate     : fprintf ( bstdout, "\nClient Socket sending BToolkitd_util_generate " ); break;
  default : fprintf ( bstdout, "\nClient Socket sending %d ", req ); break;
  }
  fprintf ( bstdout, "(req=%d)\n", req );
#endif


  BToolkitd_Client_WRITE ( &rep );
  if ( ! rep ) Kill_bplatform_and_exit ( 0, 0 );

  if ( req == BToolkitd_util_generate ) {

    char ss [ 1001 ];
    int tot_arg;

    BToolkitd_Client_READ ( &rep, &pp );
    if ( ! rep ) { if(killPlatform==0){return 0;} Kill_bplatform_and_exit ( 0, 0 ); }

    BToolkitd_Client_CLOSE ( &rep );
    if ( ! rep ) { if(killPlatform==0){return 0;} Kill_bplatform_and_exit ( 0, 0 ); }

    BToolkitd_Client_GET_TOK ( &tot_arg, 4 );

    if ( tot_arg == 1 ) { /* error message string - just print */

      BToolkitd_Client_GET_TOK ( &tok, 1 );
      if ( tok != STR ) {
        printf ( "    BToolkitd client read error 11.tot_str.: %d read\n", tok );
        if(killPlatform==0){return 0;}
        Kill_bplatform_and_exit ( 0, 0 );
      }
      BToolkitd_Client_GET_STR (  ( int * ) ss );
      puts ( ss );

      * nn = 0;
      * rr = 0;

    }

    else { /* 2 NUM arg */

      BToolkitd_Client_GET_TOK ( &tok, 1 );
      if ( tok != NUM ) {
        printf ( "    BToolkitd client read error 11.tot_str.: %d read\n", tok );
        if(killPlatform==0){return 0;}
        Kill_bplatform_and_exit ( 0, 0 );
      }
      BToolkitd_Client_GET_TOK ( nn, 4 );

      BToolkitd_Client_GET_TOK ( &tok, 1 );
      if ( tok != NUM ) {
        printf ( "    BToolkitd client read error 12.tot_str.: %d read\n", tok );
        if(killPlatform==0){return 0;}
        Kill_bplatform_and_exit ( 0, 0 );
      }
      BToolkitd_Client_GET_TOK ( rr, 4 );

    }
 
    return 1;
  }

  if ( ( req == am_anonymous_server_request ) ||
       ( req == BToolkitd_util_status )       ||
       ( req == BToolkitd_util_down )         ||
       ( req == BToolkitd_util_remove )       ||
       ( req == BToolkitd_util_reread )          ) {

    char ss [ 1001 ];
    int tot_str;

    BToolkitd_Client_READ ( &rep, &pp );
    if ( ! rep ) {if(killPlatform==0){return 0;} Kill_bplatform_and_exit ( 0, 0 ); }

    BToolkitd_Client_CLOSE ( &rep );
    if ( ! rep ) {if(killPlatform==0){return 0;}Kill_bplatform_and_exit ( 0, 0 );}

    BToolkitd_Client_GET_TOK ( &tot_str, 4 );

    while ( tot_str ) {

      BToolkitd_Client_GET_TOK ( &tok, 1 );
      if ( tok != STR ) {
        printf ( "    BToolkitd client read error 5.tot_str.: %d read\n", tok );
        if(killPlatform==0){return 0;}
        Kill_bplatform_and_exit ( 0, 0 );
      }

      BToolkitd_Client_GET_STR (  ( int * ) ss );
      puts ( ss );

      tot_str--;
    }

    return 1;
  }

  BToolkitd_Client_READ ( &rep, &pp );
  if ( ! rep ) {if(killPlatform==0){return 0;}Kill_bplatform_and_exit ( 0, 0 );}

  BToolkitd_Client_CLOSE ( &rep );
  if ( ! rep ) Kill_bplatform_and_exit ( 0, 0 );



  BToolkitd_Client_GET_TOK ( &tot_tok, 4 );    /* 1/3/4/5 args to be received */
  if ( ( tot_tok != 1 ) && ( tot_tok != 3 ) && ( tot_tok != 4 ) && ( tot_tok != 5 ) ) {
    printf ( "    BToolkitd client read error 1: %d read\n", tot_tok );
    if(killPlatform==0){return 0;}
    Kill_bplatform_and_exit ( 0, 0 );
  }

  if ( tot_tok != 1 ) {
    BToolkitd_Client_GET_TOK ( &tok, 1 );
    if ( tok != NUM ) {
      printf ( "    BToolkitd client read error 2: %d read\n", tok );
      if(killPlatform==0){return 0;}
      Kill_bplatform_and_exit ( 0, 0 );
    }
    BToolkitd_Client_GET_TOK ( &cs_nn, 4 );

    BToolkitd_Client_GET_TOK ( &tok, 1 );
    if ( tok != NUM ) {
      printf ( "    BToolkitd client read error 3: %d read\n", tok );
      if(killPlatform==0){return 0;}
      Kill_bplatform_and_exit ( 0, 0 );
    }
    BToolkitd_Client_GET_TOK ( &cs_pp, 4 );

    BToolkitd_Client_GET_TOK ( &tok, 1 );
    if ( tok != NUM ) {
      printf ( "    BToolkitd client read error 4: %d read\n", tok );
      if(killPlatform==0){return 0;}
      Kill_bplatform_and_exit ( 0, 0 );
    }
    BToolkitd_Client_GET_TOK ( &cs_qq, 4 );
  }

  if ( tot_tok != 3 ) {
    BToolkitd_Client_GET_TOK ( &tok, 1 );
    if ( tok != STR ) {
      printf ( "    BToolkitd client read error 9: %d read\n", tok );
      if(killPlatform==0){return 0;}
      Kill_bplatform_and_exit ( 0, 0 );
    }
    BToolkitd_Client_GET_STR (  ( int * ) buf );
    if ( buf [ 0 ] != '\0' ) {
      if ( strlen ( buf ) > 2 ) {
        if ( ( buf [ 0 ] != 'Z' ) && ( buf [ 0 ] != 'Z' ) )
          puts ( buf );
      }
    }
  }

  if ( tot_tok == 5 ) {
    BToolkitd_Client_GET_TOK ( &tok, 1 );
    if ( tok != STR ) {
      printf ( "    BToolkitd client read error 14: %d read\n", tok );
      if(killPlatform==0){return 0;}
      Kill_bplatform_and_exit ( 0, 0 );
    }
    BToolkitd_Client_GET_STR (  ( int * ) buf );
    if ( buf [ 0 ] != '\0' ) {
      if ( strlen ( buf ) > 2 ) {
        if ( ( buf [ 0 ] != 'Z' ) && ( buf [ 0 ] != 'Z' ) )
          puts ( buf );
      }
    }
  }

  /************************************************************************

    cs_nn=N+rnd+pid+req | cs_pp=2N+rnd+pid+2req | cs_qq=3N+2rnd+pid+3req

    cs_nn + cs_pp - cs_qq = pid

    cs_pp - cs_nn - req = N

    cs_nn + cs_qq - ( 2 * cs_pp ) = rnd

  ************************************************************************/

  * rr = ( cs_nn + cs_qq - ( 2 * cs_pp ) );

#ifdef VERBOSE_FLAG
fprintf ( bstdout, "\n  raw return: [ %d %d %d ]\n  ", cs_nn, cs_pp, cs_qq );
#endif /* VERBOSE_FLAG */

  if ( ( ! cs_nn ) && ( ! cs_pp ) &&  ( ! cs_qq ) ) {
    * nn = -4;

#ifdef VERBOSE_FLAG
    fprintf ( bstdout, " wrong ipaddress: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

    return 1;
  }

  else if ( ( ! cs_nn ) && ( ! cs_pp - 1 ) &&  ( ! cs_qq ) ) {
    * nn = -3;

#ifdef VERBOSE_FLAG
    fprintf ( bstdout, " previously stored pid no longer matches: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

    return 1;
  }

  else {

  switch ( req ) {

    case non_count_request :
      * nn = ( cs_pp - cs_nn - non_count_request - null_offset );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - non_count_request: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

      break;

    case count_request :
      * nn = ( cs_pp - cs_nn - count_request - null_offset );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - count_request: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

      break;

    case pre_init_request :
      * nn = ( cs_pp - cs_nn == pre_init_request + 1 );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - pre_init_request: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

      break;

    case init_request :
      * nn = ( cs_pp - cs_nn == init_request + 1 );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - init_request: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

      break;

    case am_anonymous_server_request :
      * nn = ( cs_pp - cs_nn == init_request + 1 );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - am_anonymous_server_request: returned %d %d (ignored)\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

      break;

  case hiip_request :
    *nn = ( cs_pp - cs_nn - ( 2 * hiip_request ) );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - hiip_request: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

      break;

  case fini_request :
    * nn = ( cs_pp - cs_nn == fini_request + 1 );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - fini_request: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

      break;

  case BTd_id_BT_id_check :
    * nn = ( cs_pp - cs_nn - 2 );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - BTd_id_BT_id_check: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

      break;

  case user_uid_request :
    * nn = ( cs_pp - cs_nn - 5 );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - user_uid_request: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

      break;

  case BPInfo_remove :
    * nn = ( cs_pp - cs_nn - 8 );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - BPInfo_remove: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

      break;

    } /* switch ( req ) */

  } /* else */

  return 1;
}

void
ClientSocketSTR ( nn, rr, req, sss, hi_l, hi_m, hi_h )
int * nn;
int * rr;
int req;
int * sss;
int hi_l;
int hi_m;
int hi_h;
{
  int rep, tot_tok, tok, pp;
  int pid, cs_nn, cs_pp, cs_qq, cs_tt;

/***
printf ( "\n\n\t\t  ClientSocketSTR\n" );
***/

  cs_tt = ( time ( NULL ) % 1000 );
  cs_tt = count_request + cs_tt + init_request;
  if ( req == user_name_request ) {
    cs_tt = getpid ();
    pid = getuid ();
  }
  else {
    pid = getpid ();
  }

  BToolkitd_Client_PUT_TOK ( 7, 4 );    /* 7 args to be sent */
  
  BToolkitd_Client_PUT_TOK ( STR, 1 );
  BToolkitd_Client_PUT_STR ( ( int * ) sss );

  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( cs_tt + pid + cs_tt + req, 4 );

  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( cs_tt + pid + cs_tt, 4 );

  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( cs_tt, 4 );

  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( hi_l + cs_tt + hi_m + hi_h, 4 );

  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( hi_l + hi_h + cs_tt + hi_m + hi_h, 4 );

  BToolkitd_Client_PUT_TOK ( NUM, 1 );
  BToolkitd_Client_PUT_TOK ( hi_l + cs_tt + hi_m + hi_l + hi_h, 4 );

    /**************************
      sss
      2time+pid+req
      2time+pid
      time
      hi_l+hi_m+hi_h+time
      hi_l+hi_m+2hi_h+time
      2hi_l+hi_m+hi_h+time
    **************************/ 

  BToolkitd_Client_CONNECT ( &rep );
  if ( ! rep ) {
    printf ( "\n  No response from BToolkitd\n\n" );
    Kill_bplatform_and_exit ( 0, 0 );
  }


#ifdef VERBOSE_FLAG
switch ( req ) {
case user_name_request       : fprintf ( bstdout, "\nClient Socket sending user_name_request " ); break;
  case chk_vers_request      : fprintf ( bstdout, "\nClient Socket sending chk_vers_request " ); break;
  case Bpda_time_request     : fprintf ( bstdout, "\nClient Socket sending Bpda_time_request " ); break;
}
fprintf ( bstdout, " (req=%d)\n", req );
#endif


  BToolkitd_Client_WRITE ( &rep );
  if ( ! rep ) Kill_bplatform_and_exit ( 0, 0 );

  BToolkitd_Client_READ ( &rep, &pp );
  if ( ! rep ) Kill_bplatform_and_exit ( 0, 0 );

  BToolkitd_Client_CLOSE ( &rep );
  if ( ! rep ) Kill_bplatform_and_exit ( 0, 0 );



  BToolkitd_Client_GET_TOK ( &tot_tok, 4 );    /* 3/4 args to be received */
  if ( ( tot_tok != 3 ) && ( tot_tok != 4 ) ) {
    printf ( "    BToolkitd client read error 5: %d read\n", tok );
    Kill_bplatform_and_exit ( 0, 0 );
  }

  BToolkitd_Client_GET_TOK ( &tok, 1 );
  if ( tok != NUM ) {
    printf ( "    BToolkitd client read error 6: %d read\n", tok );
    Kill_bplatform_and_exit ( 0, 0 );
  }
  BToolkitd_Client_GET_TOK ( &cs_nn, 4 );

  BToolkitd_Client_GET_TOK ( &tok, 1 );
  if ( tok != NUM ) {
    printf ( "    BToolkitd client read error 7: %d read\n", tok );
    Kill_bplatform_and_exit ( 0, 0 );
  }
  BToolkitd_Client_GET_TOK ( &cs_pp, 4 );

  BToolkitd_Client_GET_TOK ( &tok, 1 );
  if ( tok != NUM ) {
    printf ( "    BToolkitd client read error 8: %d read\n", tok );
    Kill_bplatform_and_exit ( 0, 0 );
  }
  BToolkitd_Client_GET_TOK ( &cs_qq, 4 );

  if ( tot_tok != 3 ) {
    BToolkitd_Client_GET_TOK ( &tok, 1 );
    if ( tok != STR ) {
      printf ( "    BToolkitd client read error 10: %d read\n", tok );
      Kill_bplatform_and_exit ( 0, 0 );
    }
    BToolkitd_Client_GET_STR (  ( int * ) buf );
    if ( buf [ 0 ] != '0' ) puts ( buf );
  }

  /************************************************************************

    cs_nn=N+rnd+pid+req | cs_pp=2N+rnd+pid+2req | cs_qq=3N+2rnd+pid+3req

    cs_nn + cs_pp - cs_qq = pid

    cs_pp - cs_nn - req = N

    cs_nn + cs_qq - ( 2 * cs_pp ) = rnd

  ************************************************************************/

  * rr = ( cs_nn + cs_qq - ( 2 * cs_pp ) );

#ifdef VERBOSE_FLAG
fprintf ( bstdout, "\n  raw return: [ %d %d %d ]\n  ", cs_nn, cs_pp, cs_qq );
#endif /* VERBOSE_FLAG */

  if ( ( ! cs_nn ) && ( ! cs_pp ) &&  ( ! cs_qq ) ) {
    * nn = -4;

#ifdef VERBOSE_FLAG
    fprintf ( bstdout, " wrong ipaddress: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

    return;
  }

  else if ( ( ! cs_nn ) && ( ! cs_pp - 1 ) &&  ( ! cs_qq ) ) {
    * nn = -3;

#ifdef VERBOSE_FLAG
    fprintf ( bstdout, " previously stored pid no longer matches: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

    return;
  }

  else {

    switch ( req ) {

    case user_name_request :
      * nn = ( cs_pp - cs_nn - 5 );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - user_name_request: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

        break;

    case chk_vers_request :

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - chk_vers_request: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

        break;

    case Bpda_time_request :
      * nn = ( cs_pp - cs_nn );

#ifdef VERBOSE_FLAG
      fprintf ( bstdout, "ClientSocket - Bpda_time_request: returned %d %d\n", * nn, * rr );
#endif /* VERBOSE_FLAG */

        break;
    }
  }
}

