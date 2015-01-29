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
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "../MOTIF/BMotif_version.c"

#include <limits.h>
#if !defined (PATH_MAX)
#    define PATH_MAX 2048
#endif

FILE *fileid;

char* name;
char* bkit;

char bpwd [ PATH_MAX ];
char bses [ PATH_MAX ];
char btkt [ PATH_MAX ];
char benv [ 101 ];

int i, c, n, is_solaris, is_linux, is_darwin, is_osf1, is_aix,
    is_debug, is_auto_remake, is_timed, is_debug_trace, is_reset;

#ifdef WWW_VERSION

void
file_error ( file, mode )
char * file;
char * mode;
{
  printf ( "\n  Can't open %s for %s\n\n", file, mode );
  exit ( 1 );
}

void
format_error ( file, err, cc )
char * file;
char * err;
char cc;
{
  printf ( "\n  Invalid %s directory\n\n", toolkit_init_ver );
  exit ( 1 );
}

/* from Upgrade4.xToWWW1.x.c */
void
check ( file )
char * file;
{
  FILE * file_in;
  int c, i, t;

  file_in = fopen ( file, "r" );
  if ( file_in == NULL ) file_error ( file, "reading" );

  /***
  cur_hdr_string
  ***/
  c = getc ( file_in );
  if ( c == 'B' ) {
    for ( i = 0 ; i < 4 ; i++ ) c = getc ( file_in );
  }
  else {
    t = c;
    for ( i = 0 ; i < t ; i++ ) c = getc ( file_in );
  }

  t = 0;
  c = getc ( file_in );
  t = t + ( int ) c; 
  c = getc ( file_in );
  t = t + ( 7 * ( int ) c ); 
  c = getc ( file_in );
  t = t + ( 49 * ( int ) c ); 
  c = getc ( file_in );
  t = t + ( 343 * ( int ) c ); 
  t = t + 15;

  i = 0;
  c = getc ( file_in );
  while ( i < ( int ) t && c != EOF ) {
    c = getc ( file_in );
    i++;
  }

  if ( c == EOF ) {
    format_error ( file, "1", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( file, "2", c );
  }

  c = getc ( file_in );
  if ( c == EOF ) {
    format_error ( file, "3", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( file, "4", c );
  }

  c = getc ( file_in );
  if ( c == EOF ) {
    format_error ( file, "5", ' ' );
  }
  else if ( c != 1 ) {
    format_error ( file, "6", c );
  }

  t = 0;
  c = getc ( file_in );
  t = t + ( int ) c; 
  c = getc ( file_in );
  t = t + ( 7 * ( int ) c ); 
  c = getc ( file_in );
  t = t + ( 49 * ( int ) c ); 
  c = getc ( file_in );
  t = t + ( 343 * ( int ) c ); 
  t = t + 23;

  i = 0;
  c = getc ( file_in );
  while ( i < ( int ) t && c != EOF ) {
    c = getc ( file_in );
    i++;
  }

  if      ( c == EOF )  format_error ( file, "7", ' ' );
  else if ( c != 0 )    format_error ( file, "8", c );

  c = getc ( file_in );
  if      ( c == EOF ) format_error ( file, "9", ' ' );
  else if ( c != 0 )   format_error ( file, "10", c );

  c = getc ( file_in );
  if      ( c == EOF ) format_error ( file, "11", ' ' );
  else if ( c != 1 )   format_error ( file, "12", c );

  c = getc ( file_in );
  if      ( c == EOF ) format_error ( file, "13", ' ' );
  else if ( c != 0 )   format_error ( file, "14", c );

  c = getc ( file_in );
  if      ( c == EOF ) format_error ( file, "15", ' ' );
  else if ( c != 1 )   format_error ( file, "16", c );

  fclose ( file_in );
}

#endif /* WWW_VERSION */




int
main ( argc, argv )
int argc;
char *argv[];
{
  void err_rep ();
  void rm_files ();

  struct stat stat_buf;
  
  char* HOME;

  is_debug = 0;
  is_auto_remake = 0;
  is_timed = 0;
  is_debug_trace = 0;
  is_reset = 0;

  if ( argc > 2 ) err_rep ( 32 );     /* no argument required */    

  if ( argc == 2 ) {
    if      ( strcmp ( argv [ 1 ], ".d." ) == 0 )    is_debug = 1;
    else if ( strcmp ( argv [ 1 ], ".r." ) == 0 )    is_auto_remake = 1;
    else if ( strcmp ( argv [ 1 ], ".t." ) == 0 )    is_timed = 1;
    else if ( strcmp ( argv [ 1 ], "debug" ) == 0 )  is_debug_trace = 1;
    else if ( strcmp ( argv [ 1 ], ".z." ) == 0 )    is_reset = 1;
    else                    err_rep ( 32 );    /* no argument required */    
   }

  if ( ! is_debug ) unlink ( ".Bini" );

  bkit = getenv ( "BKIT" );
  if ( bkit == NULL ) err_rep ( 9 );                 /* BKIT not set */

#ifdef WWW_VERSION
  check ( ".Bpda" );
  check ( ".Bpda_0" );
#endif /* WWW_VERSION */

  unlink ( ".Bxterm" );
  system ( "#!/bin/sh\nwhich xterm > .Bxterm" );
  fileid = fopen ( ".Bxterm", "r" );
  if ( fileid == NULL ) err_rep ( 41 );
  c = getc ( fileid );
  fclose ( fileid );
  unlink ( ".Bxterm" );
  if ( c != '/' ) err_rep ( 42 );

/*
fileid=popen("which xterm","r");
if ( fileid == NULL ) err_rep ( 41 );
c = getc ( fileid );
pclose(fileid);
if ( c != '/' ) err_rep ( 42 );
*/

  /* FIXME: use getcwd() */
  
  if ( system ( "pwd > .Bcom" ) != 0 ) {
    puts ( "\n\n             Error executing \"pwd > .Bcom\"\n\n" );
    exit ( 1 );
  }
  fileid = fopen ( ".Bcom", "r" );
  if ( fileid == NULL ) {
    puts ( "\n\n             Can't open \".Bcom\" for reading\n\n" );
    exit ( 1 );
  }
  i = 0;
  c = getc ( fileid );
  while ( c != EOF && c != '\n' ) {
    bpwd [ i ] = c;
    i++;
    c = getc ( fileid );
  }
  fclose ( fileid );
  unlink ( ".Bcom" );
  
  
  /*getcwd(bpwd, (size_t)PATH_MAX);*/
  
  fileid = fopen ( ".BToolkitLock", "r" );
  if ( fileid !=  NULL ) err_rep ( 1 );                 /* still locked */

  rm_files ();

  is_solaris = 0;
  is_linux = 0;
  is_darwin = 0;
  is_osf1 = 0;
  is_aix = 0;

  fileid = fopen ( ".BToolkitLock", "w" );
  if ( fileid == NULL ) err_rep ( 2 );       /* can't open .BToolkitLock */
  fclose ( fileid );

  unlink ( ".Benv" );
  fileid = fopen ( ".Benv", "w" );
  if ( fileid == NULL ) err_rep ( 3 );       /* can't open .Benv */
  fputs ( "0$toolkit$0$0\n", fileid );
  fclose ( fileid );

  unlink ( ".Bses" );
  fileid = fopen ( ".Bses", "w" );
  if ( fileid == NULL ) err_rep ( 4 );       /* can't open .Bses */
  fclose ( fileid );
  unlink ( ".Bses" );

  strcpy ( benv, "" );
  system ( "#!/bin/sh\nif [ -x /usr/bin/uname ]\nthen\n/usr/bin/uname > .Bpla\nfi" );
  system ( "#!/bin/sh\nif [ -x /usr/uname ]\nthen\n/usr/uname > .Bpla\nfi" );
  system ( "#!/bin/sh\nif [ -x /bin/uname ]\nthen\n/bin/uname > .Bpla\nfi" );

  fileid = fopen ( ".Bpla", "r" );
  if ( fileid  ==  NULL ) err_rep ( 6 );     /* uname problem */
  i = 0;
  c = getc ( fileid );
  while ( c != EOF && c != '\n' && i < 100 ) {
    benv [ i ] = c;
    c = getc ( fileid );
    i++;
  }
  fclose ( fileid );
  if   ( i < 100 ) benv [ i ] = '\0';
  else             err_rep ( 6 );

  if ( strcmp ( benv, "SunOS" ) == 0 ) {
    struct stat solaris_file;
    if ( stat ( "/etc/vfstab", &solaris_file ) == 0 ) {
      is_solaris = 1;
      strcpy ( benv, "Solaris" );
      fileid = fopen ( ".Bpla", "w" );
      if ( fileid  ==  NULL ) err_rep ( 25 );
      fputs ( benv, fileid );
      putc ( '\n', fileid );
      fclose ( fileid );
    }
  }
  else if ( strcmp ( benv, "OSF1" ) == 0 )  { is_osf1 = 1; }
  else if ( strcmp ( benv, "Linux" ) == 0 ) { is_linux = 1; }
  else if ( strcmp ( benv, "Darwin" ) == 0 ) { is_darwin = 1; }
  else if ( strcmp ( benv, "AIX" ) == 0 )   { is_aix = 1; }
  else {
    puts ( "\n\n              Alien environment:  " );
    puts ( benv );
    puts ( "\n\n              Known environments: SunOS" );
    puts ( "\n                                  Solaris" );
    puts ( "\n                                  Linux" );
    puts ( "\n                                  Darwin" );
    puts ( "\n                                  OSF1" );
    puts ( "\n                                  AIX\n" );
    puts ( "\n                Assuming Linux\n\n" );
    is_linux = 1;
  }

  strcpy ( bses, bkit );
  strcat ( bses, "/BLIB/BSession" );
  if ( stat ( bses, &stat_buf ) != 0 ) err_rep ( 7 );     /* BSession not exist */
  if ( ! ( stat_buf.st_mode & S_IXOTH ) ) err_rep ( 40 ); /* no execute permission */

  strcpy ( bses, bkit );
  strcat ( bses, "/BLIB/BMotif" );
  if ( stat ( bses, &stat_buf ) != 0 ) err_rep ( 31 );    /* BMotif not exist */
  if ( ! ( stat_buf.st_mode & S_IXOTH ) ) err_rep ( 38 ); /* no execute permission */

  strcpy ( bses, bkit );
  strcat ( bses, "/BPLAT/bplatform" );
  if ( stat ( bses, &stat_buf ) != 0 ) err_rep ( 30 );    /* bplatform not exist */
  if ( ! ( stat_buf.st_mode & S_IXOTH ) ) err_rep ( 39 ); /* no execute permission */

  puts ( "\n\n" );
  puts ( toolkit_name );
  puts ( "\n\n" );
  puts ( toolkit_ver_with_sp );
  puts ( "\n\n" );
  puts ( toolkit_copyright );
  puts ( "\n\n" );

  system ( "rm -fr TMP" );

  fileid = fopen ( "TMP", "r" );
  if ( fileid == NULL ) {
    if ( system ( "mkdir TMP" ) != 0 ) err_rep ( 36 );
  }
  else {
    fclose ( fileid );
  }

  /* unlink ( "TMP/.Bcom" );  part of BMotif initialisation - see BSession */

  if ( is_debug_trace ) {
      system ( "$BKIT/BLIB/BMotif debug &" );
  }
  else {
    if ( ! is_debug ) {
      if ( is_auto_remake ) {
        system ( "echo '' > .Btxt ; $BKIT/BLIB/BMotif .r < .Btxt&" );
      }
      else if ( is_reset ) {
        system ( "echo '' > .Btxt ; $BKIT/BLIB/BMotif .z < .Btxt&" );
      }
      else if ( is_timed ) {
        fileid = fopen ( ".Bpdan", "r" );
        if ( fileid != NULL ) {
          fclose ( fileid );
          system ( "cp .Bpdan .Bpdan.timer" );
        }
        fileid = fopen ( ".Bpda", "r" );
        if ( fileid != NULL ) {
          fclose ( fileid );
          system ( "cp .Bpda .Bpda.timer" );
        }
        fileid = fopen ( ".Bpda_0", "r" );
        if ( fileid != NULL ) {
          fclose ( fileid );
          system ( "cp .Bpda_0 .Bpda_0.timer" );
        }
        system ( "echo '' > .Btxt ; $BKIT/BLIB/BMotif .t < .Btxt&" );
      }
      else {
        system ( "$BKIT/BLIB/BMotif&" );
      }
    }
  }

  fileid = fopen ( ".Bver", "w" );
  if ( fileid == NULL ) {
    sleep ( 1 );
    err_rep ( 11 );
  }
  fputs (" 3.0\n", fileid );
  fclose ( fileid );


  /*printf("BSession 2 %s %s\n\n", bses, bpwd);*/
  strcpy ( bses, bkit );
  strcat ( bses, "/BLIB/BSession" );
  execl ( bses, bses, bpwd, ( char * ) 0 ); /* Benv (0$toolkit$0$0) Bses (1) */

  /***
  returns here only on failure
  ***/
   sleep ( 1 );
   err_rep ( 33 );
   
   return ( 0 );
}

void
err_rep ( err_no )
int err_no;
{
  void rm_files ();

  switch ( err_no ) {
  case 1:  if ( system ( "pwd > .Bcom" ) != 0 ) {
             puts ( "\n\n             Error executing \"pwd > .Bcom\"\n" );
             exit ( 1 );
           }
           fileid = fopen ( ".Bcom", "r" );
           if ( fileid == NULL ) {
             puts ( "\n\n             Can't open \".Bcom\" for reading\n" );
             exit ( 1 );
           }
           i = 0;
           c = getc ( fileid );
           while ( c != EOF && c != '\n' ) {
             bpwd [ i ] = c;
             i++;
             c = getc ( fileid );
           }
           bpwd [ i ] = '\0';
           fclose ( fileid );
           unlink ( ".Bcom" );
/*
           puts ( "\n\n  This B-Toolkit development directory:\n\n" );
           puts ( "    %s\n\n", bpwd );
           puts ( "  is currently locked; run\n\n" );
           puts ( "    $BKIT/BUnlock %s\n\n", bpwd );
           puts ( "  to unlock\n\n\n" );
*/
           puts ( "\n\n  Development not unlocked: run\n\n" );
           printf ( "    $BKIT/BUnlock %s\n\n", bpwd );
           puts ( "  to unlock" );
           break;
  case 2:  puts ( "\n\n              Can't write to file .BToolkitLock" );
           unlink ( ".BToolkitLock" );
           break;
  case 3:  puts ( "\n\n              Can't write to file .Benv" );
           unlink ( ".BToolkitLock" );
           break;
  case 4:  puts ( "\n\n              Can't write to file .Bses" );
           unlink ( ".BToolkitLock" );
           break;
  case 5:  puts ( "\n\n              Alien environment:  " );
           puts ( benv );
           puts ( "\n\n              Known environments: SunOS" );
           puts ( "\n                                  Solaris" );
           puts ( "\n                                  OSF1" );
           puts ( "\n                                  Linux" );
           puts ( "\n                                  Darwin" );
           puts ( "\n                                  AIX" );
           unlink ( ".BToolkitLock" );
           break;
  case 6:  puts ( "\n\n                Problem with `uname'" );
           unlink ( ".BToolkitLock" );
           break;
  case 7:  puts ( "\n\n                $BKIT/BLIB/BSession does not exist" );
           unlink ( ".BToolkitLock" );
           break;
  case 9:  puts ( "\n\n                Environment variable BKIT not set" );
           unlink ( ".BToolkitLock" );
           break;
  case 11: puts ( "\n\n               Can't write to file .Bver" );
           unlink ( ".BToolkitLock" );
           break;
  case 12: puts ( "\n\n               Environment variable BSITECODE not set" );
           unlink ( ".BToolkitLock" );
           break;
  case 16: puts ( "\n\n               B-Toolkit: Error code 13813" );
           unlink ( ".BToolkitLock" );
           break;
  case 17: puts ( "\n\n               B-Toolkit: Error code 13812" );
           unlink ( ".BToolkitLock" );
           break;
  case 18: puts ( "\n\n               Can't open .Bcom for reading" );
           unlink ( ".BToolkitLock" );
           break;
  case 22: puts ( "\n\n               B-Toolkit: Error code 13821" );
           unlink ( ".BToolkitLock" );
           break;
  case 23: puts ( "\n\n               B-Toolkit: Error code 13822" );
           unlink ( ".BToolkitLock" );
           break;
  case 24: puts ( "\n\n               B-Toolkit: Error code 13823" );
           unlink ( ".BToolkitLock" );
           break;
  case 25: puts ( "\n\n               Can't open .Bpla for writing" );
           unlink ( ".BToolkitLock" );
           break;
  case 26: puts ( "\n\n               B-Toolkit: Error code 13814" );
           unlink ( ".BToolkitLock" );
           break;
  case 27: puts ( "\n\n               B-Toolkit: Error code 13815" );
           unlink ( ".BToolkitLock" );
           break;
  case 28: puts ( "\n\n               B-Toolkit: Error code 13824" );
           unlink ( ".BToolkitLock" );
           break;
  case 30: puts ( "\n\n               $BKIT/BPLAT/bplatform does not exist" );
           unlink ( ".BToolkitLock" );
           break;
  case 31: puts ( "\n\n               $BKIT/BLIB/BMotif does not exist" );
           unlink ( ".BToolkitLock" );
           break;
  case 32: puts ( "\n\n               BToolkit: no argument required" );
           unlink ( ".BToolkitLock" );
           break;
  case 33: puts("\n                   Can't execute BSession");
           unlink ( ".BToolkitLock" );
           break;
  case 35: puts ( "\n\n               Can't open .Bjob for writing" );
           unlink ( ".BToolkitLock" );
           break;
  case 36: puts ( "\n\n               Can't create TMP" );
           unlink ( ".BToolkitLock" );
           break;
/*
  case 37: puts ( "\n\n                 Can't execute mkfifo\n\n      (%s)", bpwd );
          unlink ( ".BToolkitLock" );
          break;
*/
  case 38: puts ( "\n\n     $BKIT/BKIT/BMotif does not have execute permission" );
           unlink ( ".BToolkitLock" );
           break;
  case 39: puts ( "\n\n   $BKIT/BPLAT/bplatform does not have execute permission" );
           unlink ( ".BToolkitLock" );
           break;
  case 40: puts ( "\n\n    $BKIT/BLIB/BSession does not have execute permission" );
           unlink ( ".BToolkitLock" );
           break;
  case 41: puts ( "\n\n              Can't write to file .Bxterm" );
           unlink ( ".BToolkitLock" );
           break;
  case 42: puts ( "\n\n              Can't locate xterm from your PATH" );
           unlink ( ".BToolkitLock" );
           break;
  }
  puts("\n\n\n");
  if ( err_no != 1 ) {
    rm_files();
  }
  exit ( err_no );
}

void
rm_files ()
{
  system ( " rm -f .BBBcom .BBcom .Bver .Bmen .Benv .Berr .Bnum .Bprf btl_proof.dump" );
  system ( " rm -f .Bls .Bipr .Bses .Bopn .Bcom .Bed .Bbw .Brec .Bplx B.tmp .Bcjt" );
  system ( " rm -f  BB.tmp .Bhw .Bpw tmp.b tmp.c tmpb tmpc .Bprv .Bpob* .Bbbb .Btlb" );
  system ( " rm -f .Bpdu .Bsel .Bsb1 .Bsb2 .Bsb3 .Bpi* .Btad .Bhlp .Bxok" );
  system ( " rm -f .Bcjm .Bdmf .Bjob .Bplf .Bhyp .Bpla .Btty .Blog .Bpmd" );
  system ( " rm -f .Bini .Bcpp .Bler .Bter SRC/.BBcom SRC/.Bter .Bsta .Bfil .Bipl" );
  system ( " rm -f .B.bin .Blws .Bplt .Bpof .Bspo .Btac .Bthy .Btot .Bmvr" );
  system ( " rm -f TMP/.Bffi TMP/.Bffo" );
  system ( " rm -fr TMP" );
}
