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
#define print_string_pairs \
  printf ( "tot_pairs %d:\n", tot_pairs ); \
  for ( i = 0 ; i < tot_pairs ; i++ ) { \
    printf ( "  |%s| |%s|\n", orig_string [ i ], repl_string [ i ] ); \
  }

#define print_word \
  if ( ( strcmp ( "", word ) != 0 ) ) printf ( "word: |%s|\n", word )






#include <stdio.h>
/**/
#include <string.h>
/**/
#include <stdlib.h>

#define max_pairs  1000
#define max_string  255


char in_file_name  [ 255 ];
char out_file_name [ 255 ];

FILE * file_in;
FILE * file_out;

char word [ max_string + 1 ];

int i, c, found;

char orig_string [ max_pairs + 1 ] [ max_string + 1 ];
char repl_string [ max_pairs + 1 ] [ max_string + 1 ];
int tot_pairs;

int space_equate;

int code_rewrite;
int array_rewrite;

void
format_error ( err )
int err;
{
  printf ( "\n  Greplace: format error %d\n\n", err );
  exit ( 1 );
}

void
check_replace_word ()
{
  i = 0;
  found = 0;
  while ( ! found && i < tot_pairs ) {
    found = ( strcmp ( word, orig_string [ i ] ) == 0 );
    if ( ! found ) {
      i++;
    }
  };
  if ( found ) {
    fputs ( repl_string [ i ], file_out );
  }
  else {
    fputs ( word, file_out );
  }
}

void
process_next_word ()
{
  i = 0;
  while ( ( ( c >= 'a' && c <= 'z' ) ||
            ( c >= 'A' && c <= 'Z' ) ||
            ( c >= '0' && c <= '9' ) ||
/*             ( c == '.' )             || leave this out, else 0ub! */
            ( c == '_' )                ) &&
          i < max_string                     ) {
    word [ i ] = c;
    c = getc ( file_in );
    i++;
  };
  if ( i == max_string ) {
    format_error ( 5 );
  };
  word [ i ] = '\0';
/***
  print_word;
***/
  check_replace_word ();
  if ( c != EOF ) {
    putc ( c, file_out );
    c = getc ( file_in );
  }
}

void
process_next_html_word ()
{
  i = 0;
  while ( ( ( c >= 'a' && c <= 'z' ) ||
            ( c >= 'A' && c <= 'Z' ) ||
            ( c >= '0' && c <= '9' ) ||
            ( c == '.' )             ||
            ( c == '_' )                ) &&
          i < max_string                     ) {
    word [ i ] = c;
    c = getc ( file_in );
    i++;
  };
  if ( i == max_string ) {
    format_error ( 5 );
  };
  word [ i ] = '\0';
/***
  print_word;
***/
  check_replace_word ();
  if ( c != EOF ) {
    putc ( c, file_out );
    c = getc ( file_in );
  }
}

void
process_next_num_word ()
{
  i = 0;
  while ( ( ( c >= '0' && c <= '9' ) ||
            ( c == '+' )             ||
            ( c == '-' )             ||
            ( c == '*' )             ||
            ( c == '/' )                ) &&
          i < max_string                     ) {
    word [ i ] = c;
    c = getc ( file_in );
    i++;
  };
  if ( i == max_string ) {
    format_error ( 5 );
  };
  word [ i ] = '\0';
/***
  print_word;
***/
  check_replace_word ();
  if ( c != EOF ) {
    putc ( c, file_out );
    c = getc ( file_in );
  }
}

int
main  ( argc, argv )
int argc;
char *argv[];
{
  if ( argc != 6 ) {
    format_error ( 0 );
  };

/***
{
int i;
printf ( "Greplace (%s -> %s) argc: %d\n", argv [ 1 ],  argv [ 2 ], argc );
for ( i = 0 ; i < argc ; i++ ) {
  printf ( "  %d: %s\n", i, argv [ i ] );
}
}
***/

  array_rewrite = 0;
  if      ( strcmp ( argv [ 4 ], "1" ) == 0 ) code_rewrite = 0;
  else if ( strcmp ( argv [ 4 ], "0" ) == 0 ) code_rewrite = 1;
  else if ( strcmp ( argv [ 4 ], "2" ) == 0 ) array_rewrite = 1;
  else                                        format_error ( 7 );

  strcpy ( in_file_name,  argv [ 1 ] );
  strcpy ( out_file_name, argv [ 2 ] );
  if      ( strcmp ( argv [ 3 ], "0" ) == 0 ) {
    space_equate = 0;
  }
  else if ( strcmp ( argv [ 3 ], "0" ) == 1 ) {
    space_equate = 1;
  }
  else {
    format_error ( 6 );
  };

  file_in = fopen ( ".Bcom", "r" );
  if ( file_in == NULL ) {
    printf ( "\n  Greplace: can't open \"%s\" for reading\n\n", ".Bcom" );
    exit ( 1 );
  }
  tot_pairs = 0;
  c = getc ( file_in );
  while ( c != EOF              &&
          tot_pairs < max_pairs    ) {
    i = 0;
    while ( c != ',' && c != EOF ) {
      orig_string [ tot_pairs ] [ i ] = c;
      c = getc ( file_in );
      i++;
    };
    if ( i == max_string ) {
      format_error ( 1 );
    };
    if ( c != ',' ) {
      format_error ( 2 );
    };
    orig_string [ tot_pairs ] [ i ] = '\0';
    c = getc ( file_in );
    i = 0;
    while ( c != '\n' && c != EOF ) {
      repl_string [ tot_pairs ] [ i ] = c;
      c = getc ( file_in );
      i++;
    };
    if ( i == max_string ) {
      format_error ( 3 );
    };
    if ( c != '\n' ) {
      format_error ( 4 );
    };
    repl_string [ tot_pairs ] [ i ] = '\0';
    c = getc ( file_in );
    tot_pairs++;
  };
  if ( c != EOF ) {
    format_error ( 3 );
  };
  fclose ( file_in );

/***
print_string_pairs;
***/

  file_in = fopen ( in_file_name, "r" );
  if ( file_in == NULL ) {
    printf ( "\n  Greplace: can't open \"%s\" for reading\n\n", in_file_name );
   exit ( 1 );
  }

  file_out = fopen ( out_file_name, "w" );
  if ( file_out == NULL ) {
    printf ( "\n  Greplace: can't open \"%s\" for writing\n\n", out_file_name );
    exit ( 1 );
  };

  /***
  if PASP skip to MODULE or MAIN if present
  ***/

  if ( strcmp ( argv [ 5 ], "1" ) == 0 ) {
    char buf [ 1000 ];
    int MODULE_OR_MAIN_found = 0;
    int i;
/***
printf ( "argv [ 5 ] is 1\n" );  fflush ( stdout );
***/
    c = getc ( file_in );
    putc ( c, file_out );
    while ( ( c != EOF ) && ( ! MODULE_OR_MAIN_found ) ) {
      i = 0;
      while ( ( c != EOF ) && ( c != 'M' ) ) {
        c = getc ( file_in );
        putc ( c, file_out );
      }
      if ( c == 'M' ) {
        while ( ( c >= 'A' ) && ( c <= 'U' ) ) {
          buf [ i++ ] = c;
          c = getc ( file_in );
          putc ( c, file_out );
	}
        buf [ i ] = '\0';
        if ( ( strcmp ( buf, "MODULE" ) == 0 ) ||
             ( strcmp ( buf, "MAIN" )   == 0 )    ) MODULE_OR_MAIN_found = 1;
      }
      if ( ( c != EOF ) && ( ! MODULE_OR_MAIN_found ) ) {
        c = getc ( file_in );
        putc ( c, file_out );
      }
    }
    if ( ! MODULE_OR_MAIN_found ) {

      fclose ( file_in );
      file_in = fopen ( in_file_name, "r" );
      if ( file_in == NULL ) {
        printf ( "\n  Greplace: can't open \"%s\" for reading\n\n", in_file_name );
       exit ( 1 );
      }

      fclose ( file_out );
      file_out = fopen ( out_file_name, "w" );
      if ( file_out == NULL ) {
        printf ( "\n  Greplace: can't open \"%s\" for writing\n\n", out_file_name );
        exit ( 1 );
      }

    }
/***
printf ( "\nMODULE_OR_MAIN_found %d\n", MODULE_OR_MAIN_found );
if ( ! MODULE_OR_MAIN_found ) {
  char buf [ 250 ];
  printf ( "\n---------------------------------------------------\n" ); fflush ( stdout );
  sprintf ( buf, "cat %s", argv [ 1 ] );
  system ( buf ); fflush ( stdout );
  printf ( "\n---------------------------------------------------\n" ); fflush ( stdout );
}
***/
  } /* argv [ 5 ] is  "1" */

  c = getc ( file_in );

  while ( c != EOF ) {
    if ( ! array_rewrite ) {
      if   ( code_rewrite ) process_next_word ();
      else                  process_next_html_word ();
    }
    else {
      process_next_num_word ();
    }
  };

  fclose ( file_in );
  fclose ( file_out );

  exit ( 0 );
}

   
