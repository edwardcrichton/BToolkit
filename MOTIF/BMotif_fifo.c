/* Copyright (c) 1985-96, B-Core (UK) Ltd
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
#include "BMotif_globals.h"

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
    printf (  ", blocking" );
  }

  if ( val & O_NDELAY ) {
    printf ( ", nondelay" );
  }
  else {
    printf (  ", delay" );
  }

  if ( val & O_APPEND ) {
    printf ( ", append" );
  }
  else {
    printf (  ", non-append" );
  }

  if ( val & O_SYNC ) {
    printf ( ", synchronous writes" );
  }
  else {
    printf (  ", asynchronous" );
  }

  printf ( " >>\n" ); fflush ( stdout );
}
***/


void
fifo_write ( fifo_write_buf )
char * fifo_write_buf;
{
  int i, c, read_ok = 0;
  FILE * Bpib;
  int len = strlen ( fifo_write_buf );

/*****************************************************************/
#ifdef FIFO_TRACE_FLAG
printf ( "BMotif: ready to write (%d)\n", len ); fflush(stdout );
/*
printf ( "(%s)\n", fifo_write_buf ); fflush(stdout );
*/
#endif /* FIFO_TRACE_FLAG */
/*****************************************************************/

  do
  {
  	#ifdef FIFO_TRACE_FLAG
  	fprintf ( stdout, " BMotif: write about to open\n"); fflush ( stdout );
	#endif /* FIFO_TRACE_FLAG */
	
  	fifo_write_ptr = open ( fifo_file_2b, O_WRONLY /* & ~O_NONBLOCK & ~O_NDELAY & ~O_APPEND */ );
	
	#ifdef FIFO_TRACE_FLAG
	fprintf ( stdout, " BMotif: write open\n"); fflush ( stdout );
	#endif /* FIFO_TRACE_FLAG */
	
	if(errno==EINTR)
	{
		#ifdef FIFO_TRACE_FLAG
		fprintf ( stdout, " BMotif: write open EINTR\n"); fflush ( stdout );
		#endif /* FIFO_TRACE_FLAG */
		
		usleep(1);
	}
  }
  while( fifo_write_ptr< 0 && errno == EINTR);


  if ( fifo_write_ptr < 0 ) {
    sprintf ( buf, "  BMotif: open %s", fifo_file_2b );
    perror ( buf );
    AbortedMsg ();
    Kill_bplatform_and_exit ( 1, 0 );
  }

/***
fifo_info ( "<< BMotif fifo_write_ptr", fifo_write_ptr );
***/

	#ifdef FIFO_TRACE_FLAG
	fprintf ( stdout, " BMotif: writing\n"); fflush ( stdout );
	#endif /* FIFO_TRACE_FLAG */
	
	
  if ( write ( fifo_write_ptr, fifo_write_buf, len ) != len ) {
    sprintf ( buf, "  BMotif: write %s", fifo_file_2b );
    perror ( buf );
    printf ( "\n        BMotif: attempting to write (len %d)\n", len ); fflush ( stdout );
    printf ( "\n        %s\n\n", fifo_write_buf ); fflush ( stdout );
    AbortedMsg ();
    Kill_bplatform_and_exit ( 1, 0 );
  }
  
  	#ifdef FIFO_TRACE_FLAG
  	fprintf ( stdout, " BMotif: written\n"); fflush ( stdout );
	#endif /* FIFO_TRACE_FLAG */
	
  /*  fflush ( NULL ); */


    if ( close ( fifo_write_ptr ) != 0 )
    {
    
      sprintf ( buf, "  BMotif: close %s", fifo_file_2b );
      perror ( buf );
      AbortedMsg ();
      Kill_bplatform_and_exit ( 1, 0 );
    }
    	#ifdef FIFO_TRACE_FLAG
  	fprintf ( stdout, " BMotif: write closed\n"); fflush ( stdout );  
	#endif /* FIFO_TRACE_FLAG */

/*****************************************************************/
#ifdef FIFO_TRACE_FLAG
printf ( "BMotif: wrote %d\n", len ); fflush(stdout );
printf ( "%s\nwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n", fifo_write_buf ); fflush(stdout );
#endif /* FIFO_TRACE_FLAG */
/*****************************************************************/

}

void fifo_read ()
{
  ssize_t n;
  char * buf_ptr;
  int buf_len;

/*****************************************************************/
#ifdef FIFO_TRACE_FLAG
printf ( "BMotif: about to open for read\n" );
#endif /* FIFO_TRACE_FLAG */
/*****************************************************************/

  do
  {
  	#ifdef FIFO_TRACE_FLAG
	fprintf ( stdout, " BMotif: read about open\n"); fflush ( stdout );
	#endif /* FIFO_TRACE_FLAG */
	
  	fifo_read_ptr = open ( fifo_file_2m, O_RDONLY /* & ~O_NONBLOCK & ~O_NDELAY & ~O_APPEND */ );
	
	#ifdef FIFO_TRACE_FLAG
	fprintf ( stdout, " BMotif: read open\n"); fflush ( stdout );
	#endif /* FIFO_TRACE_FLAG */
	
	if(errno==EINTR)
	{
	
		#ifdef FIFO_TRACE_FLAG
		fprintf ( stdout, " BMotif: read open EINTR\n"); fflush ( stdout );
		#endif /* FIFO_TRACE_FLAG */
		
		usleep(1);
	}
  }
  while( fifo_read_ptr < 0 && errno == EINTR);


  
  if ( fifo_read_ptr < 0 ) {
/***
printf ( "1 %d %d\n", fifo_read_ptr, errno ); fflush ( stdout );
***/
		fprintf ( stdout, " BMotif: read open error\n"); fflush ( stdout );

    sprintf ( buf, "  BMotif: open %s", fifo_file_2m );
    perror ( buf );
    AbortedMsg ();
    Kill_bplatform_and_exit ( 1, 0 );
  }
/***
printf ( "2 %d %d\n", fifo_read_ptr, errno ); fflush ( stdout );
***/

/***
fifo_info ( "<< BMotif fifo_read_ptr", fifo_read_ptr );
***/

  /***
  read may come in many pieces
  ***/
  	#ifdef FIFO_TRACE_FLAG
  	fprintf ( stdout, " BMotif: reading\n"); fflush ( stdout );
	#endif /* FIFO_TRACE_FLAG */
	
  buf_len = MAX_buf;
  buf_ptr = buf;
  while ( buf_len > 0 ) {
  
    #ifdef FIFO_TRACE_FLAG
    fprintf ( stdout, " BMotif: before call to read\n"); fflush ( stdout );
    #endif /* FIFO_TRACE_FLAG */
    
    errno=0;
    
    n = read ( fifo_read_ptr, buf_ptr, buf_len );
    
    #ifdef FIFO_TRACE_FLAG
    fprintf ( stdout, " BMotif: after call to read\n"); fflush ( stdout );
    #endif /* FIFO_TRACE_FLAG */
    
    if(errno == EINTR)
    {
    	#ifdef FIFO_TRACE_FLAG
  	fprintf ( stdout, " BMotif: read ignored EINTR\n"); fflush ( stdout );
	#endif /* FIFO_TRACE_FLAG */
	
	usleep(1);
    	continue;
    }
    if(n==0 && buf_len == MAX_buf)
    {
    	#ifdef FIFO_TRACE_FLAG
      	fprintf ( stdout, " BMotif: read n==0 and nothing read\n"); fflush ( stdout );
	#endif /* FIFO_TRACE_FLAG */
	
	usleep(1);
    	continue;    
    }
    if ( n <= 0 ) break;
    buf_ptr += n;
    buf_len -= n;
  }
  
  	#ifdef FIFO_TRACE_FLAG
  	fprintf ( stdout, " BMotif: read\n"); fflush ( stdout );
	#endif /* FIFO_TRACE_FLAG */

/*
  while ( ( n = read ( fifo_read_ptr, buf_ptr, buf_len ) ) > 0 ) {
    buf_ptr += n;
    buf_len -= n;
  }
*/

  buf [ MAX_buf - buf_len ] = '\0';

/*****************************************************************/
#ifdef FIFO_TRACE_FLAG
printf ( "BMotif: read %d\n", MAX_buf - buf_len );
printf ( "%s\nrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n", buf );
#endif /* FIFO_TRACE_FLAG */
/*****************************************************************/

  if ( n < 0 ) {
/***
printf ( "n: %d\n", n ); fflush ( stdout );
***/
    sprintf ( buf, "  BMotif: read %s", fifo_file_2m );
    perror ( buf );
    fprintf ( stdout, "\n        BMotif: read error \n"); fflush ( stdout );
    fprintf ( stdout, "\n        BMotif: read %d\n", MAX_buf - buf_len ); fflush ( stdout );
    fprintf ( stdout,"\n        %s\n\n", buf ); fflush ( stdout );
    AbortedMsg ();
    Kill_bplatform_and_exit ( 1, 0 );
  }


	if ( close ( fifo_read_ptr ) != 0 )
	{
/***
printf ( "2\n" ); fflush ( stdout );
***/
	    fprintf ( stdout, "\n        BMotif: close error %s", fifo_file_2m); fflush ( stdout );
    	    sprintf ( buf, "  BMotif: close %s", fifo_file_2m );
	    perror ( buf );
	    AbortedMsg ();
	    Kill_bplatform_and_exit ( 1, 0 );
        }
	
	#ifdef FIFO_TRACE_FLAG
	fprintf ( stdout, " BMotif: read closed\n"); fflush ( stdout );
	#endif /* FIFO_TRACE_FLAG */	
}


/*
void
fifo_write_non_fifo ( fifo_write_buf )
char ? fifo_write_buf;
{
  FILE ? fileptr;
  FILE ? Bpib;
  int len = strlen ( fifo_write_buf );
  int read_ok = 0;

/?????????????????????????????????????????????????????????????????/
#ifdef FIFO_TRACE_FLAG
printf ( "BMotif: ready to write non_fifo (%d)\n", len ); fflush(stdout );
/? printf ( "(%s)\n", fifo_write_buf ); fflush(stdout ); ?/
#endif /? FIFO_TRACE_FLAG ?/
/?????????????????????????????????????????????????????????????????/

/?
  XtSetSensitive ( InterruptPullDown, True );
  XmUpdateDisplay ( InterruptPullDown );
  XmUpdateDisplay ( top_bar );
?/

  if ( ( fileptr = fopen ( "TMP/.Bfif", "w" ) ) == NULL ) {
    AbortedMsgFile ( "\"%s\" for writing", "TMP/.Bfif" );
    Kill_bplatform_and_exit ( 1, 0 );
  }

  fprintf ( fileptr, fifo_write_buf );
  fprintf ( fileptr, "%c", ( char ) 27 );
  fclose ( fileptr );

/?????????????????????????????????????????????????????????????????/
#ifdef FIFO_TRACE_FLAG
printf ( "BMotif: wrote %d\n", len ); fflush(stdout );
printf ( "%s\nwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n", fifo_write_buf ); fflush(stdout );
#endif /? FIFO_TRACE_FLAG ?/
/?????????????????????????????????????????????????????????????????/

  while ( ! read_ok ) {
    Bpib = fopen ( ".Bpib", "r" );
    if ( Bpib != NULL ) {
      i = 0;
      c = getc ( Bpib );
      while ( c != EOF && c != '\n' ) {
        i = ( i ? 10 ) + c - '0';
        c = getc ( Bpib );
      }
      fclose ( Bpib );
      if   ( c == '\n' ) read_ok = 1;   /? read the whole thing ?/
      else               sleep ( 1 );
    }
    kill ( i, SIGUSR1 );
  }
}

void fifo_read_non_fifo ()
{
  FILE ? fileptr;
  int c, i;
  int whole_file_read = 0;

/?????????????????????????????????????????????????????????????????/
#ifdef FIFO_TRACE_FLAG
printf ( "BMotif: about to open for read non_fifo\n" );
#endif /? FIFO_TRACE_FLAG ?/
/?????????????????????????????????????????????????????????????????/

/?
  XtSetSensitive ( InterruptPullDown, False );
  XmUpdateDisplay ( InterruptPullDown );
  XmUpdateDisplay ( top_bar );
?/

  while ( ! whole_file_read ) {
    if ( ( fileptr = fopen ( "TMP/.Bfif", "r" ) ) == NULL ) {
      AbortedMsgFile ( "\"%s\" for reading", "TMP/.Bfif" );
      Kill_bplatform_and_exit ( 1, 0 );
    }
    i = 0;
    c = getc ( fileptr );
    while ( c != EOF ) {
      buf [ i++ ] = c;
      c = getc ( fileptr );
    }
    fclose ( fileptr );
    if ( buf [ i - 1 ] == 27 ) whole_file_read = 1;
#ifdef FIFO_TRACE_FLAG
    else                       { printf ( "sleeping (i=%d %c %d)\n", i - 1, buf [ i - 1 ], buf [ i - 1 ] ); sleep ( 1 ); }
#else
    else                       sleep ( 1 );
#endif
  }
  unlink ( "TMP/.Bfif" );
  buf [ i - 1 ] = '\0';

/?????????????????????????????????????????????????????????????????/
#ifdef FIFO_TRACE_FLAG
printf ( "BMotif: read %d\n", strlen ( buf ) );
printf ( "%s\nrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n", buf );
#endif /? FIFO_TRACE_FLAG ?/
/?????????????????????????????????????????????????????????????????/

}
*/
