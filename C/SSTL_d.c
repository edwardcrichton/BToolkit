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
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <syslog.h>
#include <unistd.h>

#define default_port 2075
#define pid_file_name "/tmp/SSTL_d_pid"

/*
struct sigaction act1;
#define ret_code_0  47
#define ret_code_1  22
*/

void
ChildReaper ( sig )
int sig;
{
  int status;

printf ( "---------------------------------------------\n" );
system ( "ps auxww|grep SSTL_d" );
printf ( "---------------------------------------------\n" );

 while ( wait3 ( &status, WNOHANG, ( struct rusage * ) 0 ) >= 0 ) { ; }

printf ( "---------------------------------------------\n" );
system ( "ps auxww|grep SSTL_d" );
printf ( "---------------------------------------------\n" );

  printf ( "-------->>>>>>>>> child_reaper sig %d status %d\n", sig, status );
#ifdef VERBOSE_FLAG
  printf ( "-------->>>>>>>>> child_reaper sig %d status %d\n", sig, status );
#endif /* VERBOSE_FLAG */

}

void
SyslogMsgExit ( char * msg1, char * msg2 )
{
  openlog ( "SSTL_d", LOG_PID, LOG_DAEMON );
  setlogmask ( LOG_UPTO (  LOG_WARNING ) );
  syslog ( LOG_ERR, msg1, msg2 );
  closelog ();
  unlink ( pid_file_name );
  exit ( 1 );
}

void
SyslogErrExit ( char * msg, int err1, int err2 )
{
  openlog ( "SSTL_d", LOG_PID, LOG_DAEMON );
  setlogmask ( LOG_UPTO (  LOG_WARNING ) );
  if ( err2 != -1 ) {
    syslog ( LOG_ERR, msg, err1, err2 );
  }
  else if ( err1 != -1 ) {
    syslog ( LOG_ERR, msg, err1 );
  }
  else {
    syslog ( LOG_ERR, msg ); 
  }
  closelog ();
  unlink ( pid_file_name );
  exit ( 1 );
}


/*
void
ss_shutdown ()
{
  shutdown ( socksyslog_num, shutdown_all );
}
*/


void
SSTL_MasterSocketInit ( int * port, int * master_sock )
{
  struct servent      * servent_ptr;
  int                 on = 1;
  struct sockaddr_in  s_server;
  FILE                * pid_file;
  struct sigaction    act_CHLD;

  if ( ( servent_ptr = getservbyname ( "SSTL_d", "tcp" ) ) ) {
    * port = ( ntohs ( servent_ptr -> s_port) );
  }
  else {
    * port = default_port;
  }
  
#ifdef VERBOSE_FLAG
  printf ( "\n\n  attempting to listen at port %d\n", * port );
#endif /* VERBOSE_FLAG */

  if ( ( * master_sock = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP ) ) == -1 )
             SyslogErrExit ( "socket failed - errno %d\n", errno, -1 );

  if ( ( setsockopt ( * master_sock, SOL_SOCKET, SO_REUSEADDR,
                                     ( char * ) &on, sizeof ( on ) ) ) == -1 )
             SyslogErrExit ( "socketopt failed - errno %d\n", errno, -1 );

#ifdef VERBOSE_FLAG
  printf ( "  master_sock: %d\n\n", * master_sock );
#endif /* VERBOSE_FLAG */

  memset ( ( char * ) &s_server, 0, sizeof ( s_server ) );
  s_server.sin_family = AF_INET;
  s_server.sin_addr.s_addr = htonl ( INADDR_ANY );
  s_server.sin_port = htons ( * port );
  if ( bind ( * master_sock, ( struct sockaddr * ) &s_server,
                                           sizeof ( s_server ) ) == -1 ) {

    SyslogErrExit ( "can't bind to Blm_port %d - errno %d\n", * port, errno );  
  }

  if ( listen ( * master_sock, 5 ) == -1 )
    SyslogErrExit ( "listen failed - errno %d\n", errno, -1 );

  pid_file = fopen ( pid_file_name, "w" );
  if ( pid_file == NULL )
    SyslogMsgExit ( "can't write to file: %s\n", pid_file_name );
  fprintf ( pid_file, "%d\n", getpid () );
  fclose ( pid_file );

/*
  act_CHLD.sa_handler = ChildReaper;
  sigemptyset ( & ( act_CHLD.sa_mask ) );
  act_CHLD.sa_flags = ( int ) 0;
  sigaction ( SIGCHLD, & act_CHLD, NULL );
*/
/*
  ( void ) signal ( SIGCHLD, ChildReaper );
*/

  openlog ( "SSTL_d", LOG_PID, LOG_DAEMON );
  setlogmask ( LOG_UPTO (  LOG_WARNING ) );
  syslog ( LOG_ERR, "Listening at port %d\n", * port );
  closelog ();  

  printf ( "\n  SSLT_d started - listening at port %d\n\n", * port );
}

main ( int argc, char * * argv )
{
  int                 port;
  int                 master_sock;
  int                 slave_sock;
  int                 slave_sock_addr_len;
  struct sockaddr_in  acc_s_server;

  SSTL_MasterSocketInit ( &port, &master_sock );
  
  slave_sock_addr_len = sizeof ( struct sockaddr );

  while ( 1 ) {
    slave_sock = accept ( master_sock,
              ( struct sockaddr * ) &acc_s_server, &slave_sock_addr_len );
    if ( slave_sock < 0 ) {
      if ( errno == EINTR )
        continue;
      SyslogErrExit ( "accept failed - errno %d\n", errno, -1 );
    }

    switch ( fork () ) {
      case 0 :               /* slave */
        ( void ) close ( master_sock );
        exit ( ProcessRequest ( slave_sock ) );
        break;
      case -1 :             /* error */
        SyslogErrExit ( "fork failed - errno %d\n", errno, -1 );
        break;
      default :             /* master */
        ( void ) close ( slave_sock );
        break;
    }

  } /* end while ( 1 ) */

  
}

int
ProcessRequest ( int slave_sock )
{
#define sock_buf_len_MAX 1000
  char sock_buf [ sock_buf_len_MAX ];

#ifdef VERBOSE_FLAG
  printf ( "\n%d slave_sock: %d", getpid (), slave_sock );
#endif /* VERBOSE_FLAG */

    read ( slave_sock, sock_buf, sock_buf_len_MAX );
printf ( "%7d `%s'\n", getpid (), sock_buf );
    return 0;
}
