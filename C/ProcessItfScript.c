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
#include <string.h>
#include <stdlib.h>

FILE *scriptfile_in;
FILE *scriptfile_out;

int c;
int n;

void
rem_ws ()
{
  /***
  remove spaces
  ***/
  if ( ( c == ' ' || c == '\t' ) && c != EOF ) {
    c = getc ( scriptfile_in );
    while ( ( c == ' ' || c == '\t' ) && c != EOF ) {
      c = getc ( scriptfile_in );
    }
  }
}


void
find_start_opname ()
{
  /***
  read up to first char of op name
  ***/
  if ( ( c < 'a' || c > 'z' ) && ( c < 'A' || c > 'Z' ) && c != EOF ) {
    c = getc ( scriptfile_in );
    while ( ( c < 'a' || c > 'z' ) && ( c < 'A' || c > 'Z' ) && c != EOF ) {
      c = getc ( scriptfile_in );
    }
  }
}


void
print_op_and_params ()
{
  /***
  prints until  '(', ';', ' ' or '\n' encountered
  then prints `_OP'
  ***/
  while ( c != '(' && c != ';' && c != ' ' && c != '\n' && c != EOF ) {
    putc( c,  scriptfile_out );
    c = getc ( scriptfile_in );
  }
  fputs ( "_OP\n",  scriptfile_out );

  rem_ws ();
 
  if ( c == '(' ) {
    /***
    params present
    ***/
    c = getc ( scriptfile_in );
    while ( c != ')' ) {
      /***
      print until ',', ' ', '\t' or ')' 
      ***/
      while ( c != ',' && c != ' ' && c != '\t' && c != ')' && c != EOF ) {
        putc( c,  scriptfile_out );
        c = getc ( scriptfile_in );
      }
      if ( c == ',' ) {
        putc( '\n',  scriptfile_out );
      }
      if ( c != ')' && c != EOF ) {
        c = getc ( scriptfile_in );
      }
    }
  }
  putc( '\n',  scriptfile_out );
  rem_ws ();
}

void
print_num ( m )
int m;
{
  fprintf(scriptfile_out, "%d", m);
}

void
clean_files ()
{
  system ( "rm -f C.c C.i" );
}

int
main(argc,argv)
int argc;
char *argv[];
{

char dot_h_file  [ 100 ];
char script_file [ 100 ];

  /***
  construct itf.h and user's script file names
  ***/
  strcpy ( dot_h_file, ( char * ) argv [ 1 ] );
  strcat ( dot_h_file, "IO.h" );
  strcpy ( script_file, ( char * ) argv [ 2 ] );

  /***
  pre-process itf script
  ***/
  {
    char s [ 200 ];
    strcpy ( s, "cp " );
    strcat ( s, script_file );
    strcat ( s, "  C.c ; cc -P C.c" );
    if ( system ( s ) != 0 ) {
      printf( "\n  Can't execute \"" );
      printf( "%s", s );
      printf( "\"\n\n" );
      clean_files ();
      exit ( 1 );
    }
  }

  /***
  decrement op numbers in itf.h file!
  ***/
  scriptfile_out = fopen( "C.c", "w" );
  if ( scriptfile_out == NULL ) {
    printf( "\n  Can't open C.c for writing\n\n" );
    clean_files ();
    exit ( 1 );
  }
  scriptfile_in = fopen( dot_h_file, "r" );
  if ( scriptfile_in == NULL ) {
    printf( "\n  Can't open %s for reading\n\n", dot_h_file );
    clean_files ();
    exit ( 1 );
  }

  c = getc ( scriptfile_in );
  while ( c != EOF ) {
    /***
    read up to start of num: first space
    ***/
    while ( c != ' ' && c != EOF ) {
      putc( c,  scriptfile_out );
      c = getc ( scriptfile_in );
    }
    if ( c != EOF ) {
      putc( c,  scriptfile_out );
      c = getc ( scriptfile_in );
    }
    /***
    read up to second space
    ***/
    while ( c != ' ' && c != EOF ) {
      putc( c,  scriptfile_out );
      c = getc ( scriptfile_in );
    }
    while ( c != EOF && ( c < '0' || c > '9' ) ) {
      putc( c,  scriptfile_out );
      c = getc ( scriptfile_in );
    }
    if ( c != EOF ) {
      /***
      read value into n
      ***/
      n = 0;
      while ( c >= '0' && c <= '9' ) {
        n = ( ( 10 * n ) + c - '0' );
        c = getc ( scriptfile_in );
      };
      /***
      subtract one and print
      ***/
      n--;
      print_num ( n );
    }
  }

  fclose ( scriptfile_in );
  fclose ( scriptfile_out );

  scriptfile_out = fopen( "C.c", "a" );
  if ( scriptfile_out == NULL ) {
    printf( "\n  Can't open C.c for writing\n\n" );
    clean_files ();
    exit ( 1 );
  }
  scriptfile_in = fopen( "C.i", "r" );
  if ( scriptfile_in == NULL ) {
    printf( "\n  Can't open C.i for reading\n\n" );
    clean_files ();
    exit ( 1 );
  }

  c = getc ( scriptfile_in );
  while ( c != EOF ) {
    find_start_opname ();
    if ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) ) {
      print_op_and_params ();
    }
  }

  /***
  add Quit_OP
  ***/
  fputs ( "\nQuit_OP\n", scriptfile_out );

  fclose ( scriptfile_in );
  fclose ( scriptfile_out );

  if ( system ( "cc -P C.c" ) != 0 ) {
    printf( "\n  Can't execute \"cc -P C.c\"\n\n" );
    clean_files ();
    exit ( 1 );
  }

  /***
  and finally, remove newlines
  ***/
  /***
  construct output script file name
  ***/
  strcpy ( script_file, ( char * ) argv [ 2 ] );
  strcat ( script_file, ".itf" );

  scriptfile_out = fopen( script_file, "w" );
  if ( scriptfile_out == NULL ) {
    printf( "\n  Can't open %s for writing\n\n", script_file );
    clean_files ();
    exit ( 1 );
  }

  scriptfile_in = fopen( "C.i", "r" );
  if ( scriptfile_in == NULL ) {
    printf( "\n  Can't open C.i for reading\n\n" );
    clean_files ();
    exit ( 1 );
  }

  /***
  remove initial whitespace
  ***/
  c = getc ( scriptfile_in );
  while ( ( c == ' ' || c == '\t' || c == '\n' ) && c != EOF ) {
    c = getc ( scriptfile_in );
  }
  if ( c != EOF ) {
    putc( c,  scriptfile_out );
    c = getc ( scriptfile_in );
  }

  /***
  remove subsequent multiple newlines
  ***/
  while ( c != EOF ) {
    putc( c, scriptfile_out );
    if ( c == '\n' ) {
      while ( c == '\n' ) {
        c = getc ( scriptfile_in );
      }
    }
    else {
      c = getc ( scriptfile_in );
    }
  }

  fclose ( scriptfile_in );
  fclose ( scriptfile_out );

  clean_files ();

  /***
  execute
  ***/
  {
    char s [ 250 ];

    strcpy ( s, ( char * ) argv [ 1 ] );
    strcat ( s, "ITF < " );
    strcat ( s, script_file );
/*
    strcat ( s, " > /dev/null" );
*/
    system ( s );
  }

  exit ( 0 );

  return 0;

}
