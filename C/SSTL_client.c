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
#define SAVE_n_STLBase 1
#define RESTORE_n_STLBase 2
#define MAKE_LocationInfo 3
#define PRINT_BaseObj_LocationInfo 4
#define MOD_Laddress 5
#define XTR_Laddress 6
#define MAKE_Person 7
#define PRINT_BaseObj_Person 8
#define XTR_Pname 9
#define MOD_Pname 10
#define KEY_SEARCH_Pname 11
#define VAL_Pdetails 12
#define MOD_Pdetails 13
#define VAL_Pcompany 14
#define CRE_Pcompany 15
#define MOD_Pcompany 16
#define DEF_Pcompany 17
#define MAKE_Company 18
#define PRINT_BaseObj_Company 19
#define MOD_Comname 20
#define XTR_Comname 21
#define MAKE_Awardee 22
#define PRINT_BaseObj_Awardee 23
#define FIRST_Awardee 24
#define NEXT_Awardee 25
#define KEY_SEARCH_Awardee_key 26
#define VAL_Astudent 28
#define KEY_SEARCH_Astudent 29
#define VAL_Atype 30
#define MOD_Atype 31
#define XTR_Amatric 32
#define MOD_Amatric 33
#define VAL_Aadvisor 34
#define MOD_Aadvisor 35
#define push_Amodules 36
#define VAL_Amodules 37
#define LENGTH_Amodules 38
#define VALITH_Amodules 39
#define WITHIN_Amodules 40
#define MAKE_Module 41
#define PRINT_BaseObj_Module 42
#define MOD_Mname 43
#define XTR_Mname 44
#define VAL_Mvenue 45
#define VAL_Mattendees 46
#define LENGTH_Mattendees 47
#define VALITH_Mattendees 48
#define VAL_Mlecturers 49
#define CRE_Mnext 50
#define DEF_Mnext 51
#define MOD_Mnext 52
#define VAL_Mnext 53
#define MAKE_Lecturer 54
#define PRINT_BaseObj_Lecturer 55
#define XTR_Lname 56
#define MOD_Lname 57


#define OPR 1
#define REC 2
#define MAP 3
#define ATT 4
#define TOK 5
#define STR 6
#define RES 7
#define ERR 8
#define OPC 9




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


char req_buf [ 1000 ];
int req_buf_ptr;

char rep_buf [ 1000 ];
int rep_buf_ptr;


#define Read4byteNum \
    ( ( ( unsigned char ) rep_buf [ rep_buf_ptr     ] * 16777216 ) + \
      ( ( unsigned char ) rep_buf [ rep_buf_ptr + 1 ] *    65536 ) + \
      ( ( unsigned char ) rep_buf [ rep_buf_ptr + 2 ] *      256 ) + \
      ( ( unsigned char ) rep_buf [ rep_buf_ptr + 3 ] ) )

#define Read2byteNum \
    ( ( ( unsigned char ) rep_buf [ rep_buf_ptr     ] * 256 ) + \
      ( ( unsigned char ) rep_buf [ rep_buf_ptr + 1 ] ) )

#define Read1byteNum \
    ( ( unsigned char ) rep_buf [ rep_buf_ptr ] )



#define Write4byteNum(n) \
    req_buf [ req_buf_ptr     ] = ( unsigned char ) ( n / 16777216 ); \
    req_buf [ req_buf_ptr + 1 ] = ( unsigned char ) ( ( ( n % 16777216 ) ) / 65536 ); \
    req_buf [ req_buf_ptr + 2 ] = ( unsigned char ) ( ( ( ( n % 16777216 ) ) / 65536 ) / 256 ); \
    req_buf [ req_buf_ptr + 3 ] = ( unsigned char ) ( n % 16777216 ); \
    req_buf_ptr += 4

#define Write2byteNum(n) \
    req_buf [ req_buf_ptr     ] = ( unsigned char ) ( n / 256 ); \
    req_buf [ req_buf_ptr + 1 ] = ( unsigned char ) ( n % 256 ); \
    req_buf_ptr += 2


#define Write1byteNum(n) \
    req_buf [ req_buf_ptr ] = ( unsigned char ) n; \
    req_buf_ptr ++



#define Write_OPR(n)     Write1byteNum(OPR); Write2byteNum(n)
#define Write_REC(n)     Write1byteNum(REC); Write2byteNum(n)
#define Write_MAP(p)     Write1byteNum(MAP); Write2byteNum(p)
#define Write_ATT(n,p)   Write1byteNum(ATT); Write2byteNum(n); Write2byteNum(p)
#define Write_OPC(p)     Write1byteNum(OPC); Write2byteNum(p)
#define Write_TOK(n)     Write1byteNum(TOK); Write4byteNum(n)
#define Write_ERR        Write1byteNum(ERR)


void
err_exit ( int n )
{
  printf ( "SSTL_client error %d\n", n );
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
  int sock_buf_len;                        /* buffer length    */
  int read_len;

  if ( ( servent_ptr = ( getservbyname ( "SSTL_Top", "tcp" ) ) ) ) {
    port = ( ntohs ( servent_ptr -> s_port ) );
  }
  else {
    /* err_exit ( 1 ); */ port = 2075;
  }

  if ( uname ( &u_s ) == -1 ) err_exit ( 2 );

  if ( ( h_s = gethostbyname ( u_s.nodename ) ) == NULL ) err_exit ( 3 );

/*
  if ( ( h_s = gethostbyname ( "merlot" ) ) == NULL ) err_exit ( 3 );
*/

  serv_addr [ 0 ] =  '\0';
  for ( i = 0 ; i < h_s -> h_length ; i++ ) {
    c [ i ] = ( int ) ( h_s -> h_addr_list [ 0 ] [ i ] );
    if ( c [ i ] < 0 ) c [ i ]  = c [ i ] + 256;
  }
  sprintf ( serv_addr, "%d.%d.%d.%d", c [ 0 ], c [ 1 ], c [ 2 ], c [ 3 ] );

/***/
printf ( "%s,%d\n", serv_addr, port );
/***/

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
  while ( ( connect_count < 10 ) && ( ! connected ) ) {
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


  /***
  request 1
  ***/

  req_buf_ptr = 2;

  Write_REC(1);
  Write_TOK(1);
  Write_ATT(1,XTR_Pname);
  printf ( "<CR> to send request: REC 1 TOK 1 ATT 1 XTR_Pname " ); fflush ( stdout );

/*
  Write_REC(1);
  Write_TOK(1);
  Write_ATT(2,VAL_Pdetails);
  Write_OPC(XTR_Laddress);
  printf ( "<CR> to send request: REC 1 TOK 1 ATT 2 VAL_Pdetails OPC XTR_Laddress " ); fflush ( stdout );
*/

/*
  Write_REC(1);
  Write_TOK(1);
  Write_MAP(VAL_Amodules);
  Write_ATT(1,XTR_Mname);
  printf ( "<CR> to send request: REC 1 TOK 1 MAP VAL_Amodules ATT 1 XTR_Mname " ); fflush ( stdout );
*/

  d = getchar ();
  while ( d != '\n' ) { d = getchar (); }
  printf ( "\n" );

printf ( "req_buf_ptr=%d\n", req_buf_ptr );
  n = req_buf_ptr - 2;
printf ( "sending 2 + %d\n", n );
  req_buf_ptr = 0;
  Write2byteNum(n);
  
  write ( slave_sock, req_buf, n + 2 );
printf ( "wrote\n" );



  /***
  read first 2 chars & process to get remainder buffer length
  ***/
  read ( slave_sock, rep_buf, 2 );
printf ( "read 1\n" );
  rep_buf_ptr = 0;
  sock_buf_len = Read2byteNum;

  /***
  read rest of buffer & close socket
  ***/
  read_len =  read ( slave_sock, rep_buf, 1000 );
  close ( slave_sock );

  printf ( "sock_buf_len=%d read_len=%d\n", sock_buf_len, read_len );

  /***  message is now in sock_buf  ***/

  printf ( "Received from SSTL server:\n`" );

{ int n; for ( n = 0 ; n < read_len ; n++ ) { printf ( "%d ", rep_buf [ n ] ); } printf ( "'\n`" );
         for ( n = 0 ; n < read_len ; n++ ) { printf ( "%c ", rep_buf [ n ] ); } printf ( "'\n" ); }



  return ( 0 );

}

