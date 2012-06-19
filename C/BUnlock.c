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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

FILE *fileid;

char *getenv();
char *bkit;

char bpwd [ 1000 ];
char block [ 1000 ];

int i, c;

int
main ( argc, argv )
int argc;
char *argv[];
{
  struct stat stat_buf;
  int unlock_reqd = 1;

  bkit = getenv ( "BKIT" );
  if ( bkit  ==  NULL ) {
    printf ( "\n  Environment variable BKIT not set\n\n" );
    exit ( 0 );
  };

  if ( argc == 3 ) {
    char buf [ 250 ];
    char msg [ 250 ];
    FILE * fileid;

    unlock_reqd = 0;
    strcpy ( bpwd, argv [ 1 ] );
    sprintf ( msg, "\n  This B-Toolkit development directory:\n\n    %s\n\n  is currently locked\n\n    Do you wish to unlock it [no]? ", bpwd );
    
    #ifdef MAC_VERSION
    /* use the dialog capabilities of mac os */
    sprintf ( buf, "%s/BLIB/BRead \"%s\"", bkit, msg );
    #else
    sprintf ( buf, "xterm -geometry 50x10 -e %s/BLIB/BRead \"%s\"", bkit, msg );
    #endif
    
    
    unlink ( ".Bcom" );
    system ( buf );
    fileid = fopen ( ".Bcom", "r" );
    if ( fileid == NULL ) {
      printf ( "\n\n             Can't open \".Bcom\" for reading\n\n" );
      exit ( 1 );
    }
    i = 0;
    c = getc ( fileid );
    while ( ( c != EOF ) && ( c != '\n' ) ) {
      buf [ i ] = c;
      i++;
      c = getc ( fileid );
    }
    buf [ i ] = '\0';
    fclose ( fileid );
    unlink ( ".Bcom" );
    if ( ( strcmp ( buf, "y" ) == 0 )   ||
         ( strcmp ( buf, "yes" ) == 0 )    ) {
      unlock_reqd = 1;
    }
  }
  else if ( argc == 2 ) {
    strcpy ( bpwd, argv [ 1 ] );
  }
  else {
    if ( system ( "pwd > .Bcom" ) != 0 ) {
      printf ( "\n\n             Error executing \"pwd > .Bcom\"\n\n" );
      exit ( 1 );
    }
    fileid = fopen ( ".Bcom", "r" );
    if ( fileid == NULL ) {
      printf ( "\n\n             Can't open \".Bcom\" for reading\n\n" );
      exit ( 1 );
    };
    i = 0;
    c = getc ( fileid );
    while ( c != EOF && c != '\n' ) {
      bpwd [ i ] = c;
      i++;
      c = getc ( fileid );
    };
    bpwd [ i ] = '\0';
    fclose ( fileid );
  }

  if ( unlock_reqd ) {

    strcpy ( block, bpwd );
    strcat ( block, "/.BToolkitLock" );

    if   ( stat ( block, &stat_buf ) == 0 ) {
      if ( unlink ( block ) != 0 ) {
        printf ( "\n  Can't remove:\n" );
        printf ( "\n    %s\n", bpwd );
        printf ( "\n  Error no. = %d\n\n", errno );
        exit ( errno );
      }
      else {
        printf ( "\n  Unlocked %s\n\n", bpwd );
      }
    }
    else {
      printf ( "\n  Directory:\n" );
      printf ( "\n    %s\n", bpwd );
      printf ( "\n  is not locked\n\n" );
    }
  }

  return ( 0 );
}
