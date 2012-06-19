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
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <dirent.h>

#include <linux/major.h>
#include <linux/hdreg.h>

#include "BToolkitlm_globals.c"

FILE * Bfile;
char buf [ 250 ];
char Student_buf [ 250 ];
int c;
#define student_data_file_SIZE 256



void
sn_last8padX ()
{
  int t, i;

  /***
  buf contains ser no: 
  take last 8 characters from buf,
  front-padding with 'X' if reqd
  ***/

  t = strlen ( buf );
  if ( t < 8 ) {
    for ( i = 0 ; i < t ; i++ ) {
      buf [ i + 8 - t ] = buf [ i ];
    }
    for ( i = 0 ; i < 8 - t ; i++ ) {
      buf [ i ] = 'X';
    }
  }
  else if ( t > 8 ) {
    for ( i = 0 ; i < 8 ; i++ ) {
      buf [ i ] = buf [ i + t - 8 ];
    }
  }

#ifdef VERBOSE_FLAG
printf ( "  sn_last8padX: " );
for ( i = 0 ; i < 8 ; i++ ) { printf ( "%c", buf [ i ] ); }
printf ( "\n" );
printf ( "  sn_last8padX as numbers:" );
for ( i = 0 ; i < 8 ; i++ ) { printf ( "%3d", buf [ i ] ); }
printf ( "\n" );
#endif

}


void
sn_inrange ()
{
  int t, i;

  /***
  buf contains ser no in 1st 8 chars: 
  ensure each in range 48 .. 99
  ***/

  for ( i = 0 ; i < 8 ; i++ ) {
    if ( buf [ i ] > 99 ) buf [ i ] = buf [ i ] - 99;
    if ( buf [ i ] < 0 ) {
      buf [ i ] = ( - ( buf [ i ] ) );
      if ( buf [ i ] > 99 ) buf [ i ] = buf [ i ] - 99;
    }
  }

#ifdef VERBOSE_FLAG
printf ( "  sn_inrange   as numbers:" );
for ( i = 0 ; i < 8 ; i++ ) { printf ( "%3d", buf [ i ] ); }
printf ( "\n" );
printf ( "  equivalent ip address:       %d.%d.%d.%d\n",
  buf [ 0 ] +  buf [ 1 ],
  buf [ 2 ] +  buf [ 3 ],
  buf [ 4 ] +  buf [ 5 ],
  buf [ 6 ] +  buf [ 7 ] );
#endif

}


rr ( int nn )
{
  int i;
  for ( i = 0 ; i < nn ; i++ ) { c = getc ( Bfile ); }
}


int
rcc ()
{
  c =  getc ( Bfile );
  return ( cv2 [ cv1 [ c - '0' ] ] );
}


void
main ( argc, argv )
int argc;
char *argv[];
{

  int fd, i;
  struct hd_driveid id;

  if ( argc != 2 ) {
    printf ( "\n  Useage: Student student_data_file\n\n" );
    exit ( 1 );
  }

  strcpy ( student_data_file, argv [ 1 ] );

  if ( stat ( student_data_file, &stat_buf ) == -1 ) {
    printf ( "\n  %s does not exist\n\n", student_data_file );
    exit ( 1 );
  }

  if ( stat_buf . st_size != student_data_file_SIZE ) {
    printf ( "\n  %s has wrong size %d (should be %d)\n\n", student_data_file, stat_buf . st_size, student_data_file_SIZE );
    exit ( 1 );
  }

  Bfile = fopen ( student_data_file, "r" );
  if ( Bfile == NULL ) {
    printf ( "\n  Unable to open ./%s for reading\n\n", student_data_file );
    exit ( 1 );
  }

  fd = open ( "/dev/hda", O_RDONLY );

  if ( fd < 0 ) {
    perror ( "\n\n  Bad read protection - rerun as root\n\n" );
    exit ( 1 );
  }

  if ( ioctl ( fd, HDIO_GET_IDENTITY, &id ) != 0 ) {
    perror ( "\n\n  Could not get required info\n\n" );
    exit ( 1 );
  }

#ifdef VERBOSE_FLAG
printf("\n\n  ------------------------------------------------\n  SERIAL_NO:   \"%s\"\n",
                                                               id . serial_no );
#endif

  strcpy ( buf, id . serial_no );

  /***
  make buf 8 chars
  ***/
  sn_last8padX ();

  /***
  ensure each buf [ i ] : 0 .. 99
  ***/
  sn_inrange ();

  /***
  load Student_buf from Student file
  ***/
  i = 0;
  rr ( 17 );
  Student_buf [ i ] = rcc ();
  rr ( 12 );
  Student_buf [ i ] = ( 10 * Student_buf [ i ] ) + rcc ();
  i++;
  rr ( 11 );
  Student_buf [ i ] = rcc ();
  rr ( 7 );
  Student_buf [ i ] = ( 10 * Student_buf [ i ] ) + rcc ();
  i++;
  rr ( 28 );
  Student_buf [ i ] = rcc ();
  rr ( 36 );
  Student_buf [ i ] = ( 10 * Student_buf [ i ] ) + rcc ();
  i++;
  rr ( 19 );
  Student_buf [ i ] = rcc ();
  rr ( 10 );
  Student_buf [ i ] = ( 10 * Student_buf [ i ] ) + rcc ();
  i++;
  rr ( 9 );
  Student_buf [ i ] = rcc ();
  rr ( 8 );
  Student_buf [ i ] = ( 10 * Student_buf [ i ] ) + rcc ();
  i++;
  rr ( 24 );
  Student_buf [ i ] = rcc ();
  rr ( 13 );
  Student_buf [ i ] = ( 10 * Student_buf [ i ] ) + rcc ();
  i++;
  rr ( 4 );
  Student_buf [ i ] = rcc ();
  rr ( 15 );
  Student_buf [ i ] = ( 10 * Student_buf [ i ] ) + rcc ();
  i++;
  rr ( 11 );
  Student_buf [ i ] = rcc ();
  rr ( 9 );
  Student_buf [ i ] = ( 10 * Student_buf [ i ] ) + rcc ();
  rr ( 7 );

#ifdef VERBOSE_FLAG
printf ( "                 -------------------\n  read from Student file: " );
for ( i = 0 ; i < 8 ; i++ ) { printf ( "%3d", Student_buf [ i ] ); }
printf ( "\n" );
printf ( "  equivalent ip address:       %d.%d.%d.%d\n  ------------------------------------------------\n\n",
  Student_buf [ 0 ] +  Student_buf [ 1 ],
  Student_buf [ 2 ] +  Student_buf [ 3 ],
  Student_buf [ 4 ] +  Student_buf [ 5 ],
  Student_buf [ 6 ] +  Student_buf [ 7 ] );
#endif

/***
c = getc ( Bfile );
if ( c != EOF ) { printf ( "\n\n\n  %d %c != EOF\n\n\n", c, c ); }
else { printf ( "\n\n\n  EOF is correct!!!\n\n\n" ); }
***/

  fclose ( Bfile );

  for ( i = 0 ; i < 8 ; i++ ) {
    if ( buf [ i ] != Student_buf [ i ] ) {
      printf ( "\n\n  Bad match at buf [ %d ]: %d != %d\n\n",
                                              i, buf [ i ], Student_buf [ i ] );
      exit ( 1 );
    }
  }

  printf ( "\n  check is ok\n\n" );

}
