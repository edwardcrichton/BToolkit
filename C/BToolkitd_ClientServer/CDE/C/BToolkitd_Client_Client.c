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
#include "String_TYPE.h"

#include "Bool_TYPE.h"

#include "BToolkitd_Client_Client.h"

#define Get4byteNum \
    ( ( ( unsigned char ) _in_buf [ _in_buf_ptr     ] * 16777216 ) + \
      ( ( unsigned char ) _in_buf [ _in_buf_ptr + 1 ] *    65536 ) + \
      ( ( unsigned char ) _in_buf [ _in_buf_ptr + 2 ] *      256 ) + \
      ( ( unsigned char ) _in_buf [ _in_buf_ptr + 3 ] ) )

#define Get3byteNum \
    ( ( ( unsigned char ) _in_buf [ _in_buf_ptr     ] *    65536 ) + \
      ( ( unsigned char ) _in_buf [ _in_buf_ptr + 1 ] *      256 ) + \
      ( ( unsigned char ) _in_buf [ _in_buf_ptr + 2 ] ) )

#define Get2byteNum \
    ( ( ( unsigned char ) _in_buf [ _in_buf_ptr     ] * 256 ) + \
      ( ( unsigned char ) _in_buf [ _in_buf_ptr + 1 ] ) )

#define Get1byteNum \
    ( ( unsigned char ) _in_buf [ _in_buf_ptr ] )



#define Put4byteNum(n) \
    _out_buf [ _out_buf_ptr     ] = ( unsigned char ) ( (n) / 16777216 ); \
    _out_buf [ _out_buf_ptr + 1 ] = ( unsigned char ) ( ((n) % 16777216) / 65536 ); \
    _out_buf [ _out_buf_ptr + 2 ] = ( unsigned char ) ( ((n) % 65536)    / 256 ); \
    _out_buf [ _out_buf_ptr + 3 ] = ( unsigned char ) ( (n) % 256 )

#define Put3byteNum(n) \
    _out_buf [ _out_buf_ptr     ] = ( unsigned char ) ( ((n) % 16777216) / 65536 ); \
    _out_buf [ _out_buf_ptr + 1 ] = ( unsigned char ) ( ((n) % 65536)    / 256 ); \
    _out_buf [ _out_buf_ptr + 2 ] = ( unsigned char ) ( (n) % 256 )

#define Put2byteNum(n) \
    _out_buf [ _out_buf_ptr     ] = ( unsigned char ) ( ((n) % 65536)    / 256 ); \
    _out_buf [ _out_buf_ptr + 1 ] = ( unsigned char ) ( (n) % 256 )

#define Put1byteNum(n) \
    _out_buf [ _out_buf_ptr     ] = ( unsigned char ) ( (n) % 256 )


#ifdef TEST_FLAG
#define Print_in_buf \
{ int n; printf ( "_in_buf (%d):\n    `", _in_buf_len ); \
         for ( n = 0 ; n < _in_buf_len ; n++ ) { printf ( "%3d ", ( unsigned char ) _in_buf [ n ] ); } printf ( "'\n    `" ); \
         for ( n = 0 ; n < _in_buf_len ; n++ ) { printf ( "%3c ", _in_buf [ n ] ); } printf ( "'\n" ); }
#endif



int slave_sock;
char serv_addr [ 20 ];
int serv_port;

void
BToolkitd_Client_INIT ( void * _ipaddress, int _port )
{
  int i = 0;
  while ( ( ( ( char * ) _ipaddress ) [ i ] != '\0' ) && ( i < 15 ) ) {
    serv_addr [ i ] = ( ( char * ) _ipaddress ) [ i ];
    i++;
  }
  serv_addr [ i ] = '\0';
  serv_port = _port;
  _out_buf_ptr = 2;
  _in_buf_ptr = 2;
}

void
BToolkitd_Client_CONNECT ( int * _rep )
{
  int on = 1;
  struct sockaddr_in s_client;
  int connected, connect_count;

  if ( ( slave_sock = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP ) ) == -1 ) {
    printf ( "\n  BToolkitd_Client_CONNECT: socket failed - errno %d\n", errno );
    * _rep = FALSE;
    return;
  }

  if ( ( setsockopt ( slave_sock, SOL_SOCKET, SO_REUSEADDR,
		      ( char * ) &on, sizeof ( on ) ) ) == -1 ) {
    printf ( "\n  BToolkitd_Client_CONNECT: setsockopt failed - errno %d\n", errno );
    * _rep = FALSE;
    return;
  }

  memset ( ( char * ) &s_client, 0, sizeof ( s_client ) );
  s_client.sin_family = AF_INET;
  s_client.sin_port = htons ( serv_port );
  if ( ( s_client.sin_addr.s_addr = inet_addr ( serv_addr ) ) == INADDR_NONE ) {
    printf ( "\n  BToolkitd_Client_CONNECT: inet_addr failed - errno %d\n", errno );
    * _rep = FALSE;
    return;
  }

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

  if ( ! connected ) {
   printf ( "\n  BToolkitd_Client_CONNECT: connect failed - errno %d\n", errno );
   * _rep = FALSE;
    return;
  }
  * _rep =TRUE;
}

void
BToolkitd_Client_WRITE ( int * _rep )
{
  int write_len;
  int out_buf_ptr0 = _out_buf_ptr - 2;

  _out_buf_ptr = 0;
  Put2byteNum(out_buf_ptr0);
  write_len = write ( slave_sock, _out_buf, out_buf_ptr0 + 2 );
  if ( write_len != out_buf_ptr0 + 2 ) {
   printf ( "\n  BToolkitd_Client_WRITE: write error\n  `write' returned %d not %d\n",
                                                                    write_len, out_buf_ptr0 );
   * _rep = FALSE;
  }
  else {
   * _rep = TRUE;
  }
  _out_buf_ptr = 2;

#ifdef TEST_FLAG
{ int n; printf ( "BToolkitd_Client_WRITE (%d including 1st two length bytes):\n    `", write_len );
         for ( n = 0 ; n < write_len ; n++ ) { printf ( "%3d ", ( unsigned char ) _out_buf [ n ] ); } printf ( "'\n    `" );
         for ( n = 0 ; n < write_len ; n++ ) { printf ( "%3c ", _out_buf [ n ] ); } printf ( "'\n" ); }
#endif

}

void
BToolkitd_Client_READ ( int * _rep, int * _pp )
{
  int read_len, tot_read_len, in_buf_len_available;
  char * _in_buf_sock_ptr;

  read_len = read ( slave_sock, _in_buf, 2 );
  if ( read_len != 2 ) {
    printf ( "\n  BToolkitd_Client_READ: read error 1\n  `read' returned %d not 2\n", read_len);
    * _pp = 0;
    * _rep = FALSE;
    return;
  }
  _in_buf_ptr = 0;
  _in_buf_len = Get2byteNum;
  if ( _in_buf_len > BToolkitd_Client_ClientP2 ) {
    printf ( "\n  BToolkitd_Client_READ: read error 2\n  server requested %d read (>%d)\n",
                                                           read_len, BToolkitd_Client_ClientP2 );
    * _pp = 0;
    * _rep = FALSE;
    return;
  }

  /***
  read may come in many pieces
  ***/
  _in_buf_sock_ptr =_in_buf;
  in_buf_len_available = BToolkitd_Client_ClientP2;
  tot_read_len = 0;
  while ( ( tot_read_len < _in_buf_len ) && ( in_buf_len_available > 0 ) ) {
    read_len =  read ( slave_sock, _in_buf_sock_ptr, in_buf_len_available );
    if ( read_len == 0 ) break;
    if ( read_len < 0 ) {
      if ( errno != EINTR ) break;
    }
    tot_read_len += read_len;
    _in_buf_sock_ptr += read_len;
    in_buf_len_available -= read_len;
  }

  if ( tot_read_len != _in_buf_len ) {
     printf ( "\n  SSTLSocket_READ: read error 3\n  `read' returned %d not %d\n",
                                                       tot_read_len, _in_buf_len );
     * _pp = 0;
     * _rep = FALSE;
     return;
  }

  _in_buf_ptr = 0;
  * _pp = read_len;
  * _rep = TRUE;

#ifdef TEST_FLAG
  Print_in_buf
#endif

}

void
BToolkitd_Client_CLOSE ( int * _rep )
{
  if ( close ( slave_sock ) == -1 ) {
    printf ( "\n  BToolkitd_Client_CLOSE: close failed - errno %d\n", errno );
    * _rep = FALSE;
  }
  else {
    * _rep = TRUE;
  }
}

void
BToolkitd_Client_GET_TOK ( int * _tok, int _toksize )
{
  if ( ( _in_buf_ptr + _toksize ) <=  BToolkitd_Client_ClientP3 ) {
    switch ( _toksize ) {
    case 1:
      * _tok = Get1byteNum;
      break;
    case 2:
      * _tok = Get2byteNum;
      break;
    case 3:
      * _tok = Get3byteNum;
      break;
    case 4:
      * _tok = Get4byteNum;
      break;
    }
    _in_buf_ptr += _toksize;
  }
  else {
    * _tok = 1;
  }
}


void
BToolkitd_Client_GET_STR ( int * _ss )
{
  int i = 0;
  char *s = ( char * ) _ss;
  int ss_len = Get2byteNum;

  if ( ( _in_buf_ptr + 3 ) <=  BToolkitd_Client_ClientP3 ) {
    _in_buf_ptr += 2;
    while ( ss_len ) {
      if ( i < 1000 )  { s [ i++ ] = _in_buf [ _in_buf_ptr ]; }
      if ( i == 1000 ) { s [ i++ ] = '\0'; }
      ss_len--;
      _in_buf_ptr++;
    }
  }
  else {
    s [ 0 ] = '\0';
  }
}


void
BToolkitd_Client_GET_FIL ( int * _rep, int * _filename )
{
  FILE * fileptr;
  int ss_len = Get2byteNum;

  _in_buf_ptr += 2;

  fileptr = fopen ( ( char * ) _filename, "w" );
  if ( fileptr == NULL ) { 
    printf ( "\n  BToolkitd_Client_GET_FIL(%s): failed - errno %d\n",
                                                    ( char * ) _filename, errno );
    *_rep = FALSE;
    return;
  }

  while ( ( ss_len ) && ( _in_buf_ptr <= BToolkitd_Client_ClientP3 ) ) {
    putc ( _in_buf [ _in_buf_ptr ], fileptr );
    ss_len--;
    _in_buf_ptr++;
  }
  if ( fclose ( fileptr ) ) {
    printf ( "\n  BToolkitd_Client_GET_FIL(%s): failed - errno %d\n",
                                                    ( char * ) _filename, errno );
    *_rep = FALSE;
    return;
  }
  if ( ss_len ) {
    printf ( "\n  BToolkitd_Client_GET_FIL(%s): failed - file exceeds input buffer\n",
                                                            ( char * ) _filename );
    *_rep = FALSE;
  }
}


/*  for more effecient code 
void
BToolkitd_Client_GET_PTR_STR ( int * _ss )
{
  int ss_len = Get2byteNum;

  _in_buf_ptr += 2 ;
  _ss  = (int *) &(_in_buf [ _in_buf_ptr ]) ;
  _in_buf_ptr += ss_len;
}
*/

void
BToolkitd_Client_PUT_TOK ( int _tok, int _toksize )
{
  if ( ( _out_buf_ptr + _toksize ) <=  BToolkitd_Client_ClientP3 ) {
    switch ( _toksize ) {
    case 1:
      Put1byteNum ( _tok );
      break;
    case 2:
      Put2byteNum ( _tok );
      break;
    case 3:
      Put3byteNum ( _tok );
      break;
    case 4:
      Put4byteNum ( _tok );
      break;
    }
    _out_buf_ptr += _toksize;
  }
}

void
BToolkitd_Client_PUT_STR ( int * _ss )
{
  char *s = (char *)_ss;
  int ss_len;
  int i = 0;
  ss_len = strlen ( s );

  if ( (_out_buf_ptr + ss_len + 3 ) < BToolkitd_Client_ClientP3  ) {
    Put2byteNum ( ss_len + 1 );
    _out_buf_ptr += 2;
    while ( ss_len ) {
      _out_buf [ _out_buf_ptr++ ] = s [ i++ ];
      ss_len--;
    }
    _out_buf [ _out_buf_ptr++ ] = '\0';
  }
}

void
BToolkitd_Client_GET_IN_PTR ( int * _ptr )
{
  * _ptr = _in_buf_ptr;
}

void
BToolkitd_Client_SET_IN_PTR ( int _ptr )
{
  _in_buf_ptr = _ptr;
}

void
BToolkitd_Client_GET_OUT_PTR ( int * _ptr )
{
  * _ptr = _out_buf_ptr - 2;
}

void
BToolkitd_Client_SET_OUT_PTR ( int _ptr )
{
  _out_buf_ptr = _ptr + 2;
}
