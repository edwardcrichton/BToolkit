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
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <syslog.h>
#include <unistd.h>

#define sock_buf_len_MAX 1000

#define UnsChars2Int(s,n) \
            ( ( unsigned char ) s [ n ] * 256 ) + ( unsigned char ) s [ n + 1 ]

void
err_exit ( int n )
{
  printf ( "SSTL_c error %d\n", n );
  exit ( n ); 
}

int
main  ( int argc, char * * argv )
{
  int port;
  struct utsname u_s;
  int i, c [ 4 ], d, n;
  char serv_addr [ 15 ];
  struct servent * servent_ptr;
  struct hostent * h_s;
  struct sockaddr_in s_client;
  int slave_sock;
  int on = 1;
  int connected, connect_count;
  char stdin_buf [ 100 ];
  char sock_buf [ sock_buf_len_MAX ];      /* buffer for read  */
  int sock_buf_len;                        /* buffer length    */

  if ( ( servent_ptr = ( getservbyname ( "SSTL_d", "tcp" ) ) ) ) {
    port = ( ntohs ( servent_ptr -> s_port ) );
  }
  else {
    err_exit ( 1 );
  }

  if ( uname ( &u_s ) == -1 ) err_exit ( 2 );

  if ( ( h_s = gethostbyname ( u_s.nodename ) ) == NULL ) err_exit ( 3 );

  serv_addr [ 0 ] =  '\0';
  for ( i = 0 ; i < h_s -> h_length ; i++ ) {
    c [ i ] = ( int ) ( h_s -> h_addr_list [ 0 ] [ i ] );
    if ( c [ i ] < 0 ) c [ i ]  = c [ i ] + 256;
  }
  sprintf ( serv_addr, "%d.%d.%d.%d", c [ 0 ], c [ 1 ], c [ 2 ], c [ 3 ] );

/***
printf ( "%s\n", serv_addr );
***/

 if ( ( slave_sock = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP ) ) == -1 ) {
    err_exit ( 4 );
 }

  if ( ( setsockopt ( slave_sock, SOL_SOCKET, SO_REUSEADDR,
                                   ( char * ) &on, sizeof ( on ) ) ) == -1 )
    err_exit ( 5 );

  memset ( ( char * ) &s_client, 0, sizeof ( s_client ) );
  s_client.sin_family = AF_INET;
  s_client.sin_port = htons ( port );
  if ( ( s_client.sin_addr.s_addr = inet_addr ( serv_addr ) ) == INADDR_NONE )
        err_exit ( 6 );

  connected = 0;
  connect_count = 0;
  while ( ( connect_count < 30 ) && ( ! connected ) ) {
    if ( connect ( slave_sock, ( struct sockaddr * ) &s_client,
                                            sizeof ( s_client ) ) == 0 ) {
      connected = 1;
    }
    else {
      connect_count++;
      sleep ( 1 );
    }
  }

  if ( ! connected ) err_exit ( 7 );

  printf ( "000=query 001=add\nstring args separated by ,\neg.\n  John Williams000\n  John Williams,27,male001\n" );
  i = 2;
  d = getchar ();
  while ( d != '\n' ) {
    stdin_buf [ i++ ] = ( char ) d;
    d = getchar ();
  }
  /***
  convert last 3 chars into 2-byte unsigned
  ***/
  n = ( 100 * ( stdin_buf [ i - 3 ] - '0' ) ) +
      (  10 * ( stdin_buf [ i - 2 ] - '0' ) ) +
      (       ( stdin_buf [ i - 1 ] - '0' ) );
  stdin_buf [ i - 3 ] = ( unsigned char ) n / 256;
  stdin_buf [ i - 2 ] = ( unsigned char ) n % 256;

  /***
  write length of stdin_buf in first two chars
  ***/
  stdin_buf [ 0 ] = ( unsigned char ) ( i - 3 ) / 256;
  stdin_buf [ 1 ] = ( unsigned char ) ( i - 3 ) % 256;
  write ( slave_sock, stdin_buf, i - 1 );

/************
{
  int j;
  for ( j = 0 ; j < i - 1 ; j++ ) { printf ( "`%c'", stdin_buf [ j ] ); }
  printf ( "\n" );
  printf ( "%d\n", UnsChars2Int ( stdin_buf, 0 ) );
  printf ( "%d\n", UnsChars2Int ( stdin_buf, i - 3 ) );
}
************/

  /***
  read first 2 chars & process to get remainder buffer length
  ***/
  read ( slave_sock, sock_buf, 2 );
  sock_buf_len = UnsChars2Int ( sock_buf, 0 );

  /***
  read rest of buffer & close socket
  ***/
  read ( slave_sock, sock_buf, sock_buf_len );
  close ( slave_sock );

  /***  message is now in sock_buf  ***/

  sock_buf [ sock_buf_len + 1 ] = '\0';

  printf ( "Received from SSTL server:\n%s\n", sock_buf );

  return ( 0 );

}

