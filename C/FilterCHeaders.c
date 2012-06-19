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


FILE *Btmp;
FILE *dotcfile;


int eof_flag;

int c;

char argv3;

char opfile [ 100 ];
char cmd [ 150 ];

#define maxline 10000
char line_arr [ maxline + 1 ];

#define ansiC_header "/* ANSIC header */\n"
#define ansiC_footer "/* end ANSIC header */\n"

#define non_ansiC_header "/* non-ANSIC header */\n"
#define non_ansiC_footer "/* end non-ANSIC header */\n"



void
print_ansiC_op ()
{
  int found;

  /***
  print to ansiC_header
  ***/
  found = 0;
  while ( ! found && ! eof_flag ) {
    if ( fgets ( line_arr, maxline, dotcfile ) == NULL ) {
      eof_flag = 1;
    };
    if ( ! eof_flag ) {
      if ( strcmp ( line_arr, ansiC_header ) == 0 ) {
        found = 1;
        if ( argv3 == '1' ) {
          fputs ( "\n", Btmp );
	}
      }
      else {
        fputs ( line_arr, Btmp );
      }
    }
  };

  /***
  print to ansiC_footer
  ***/
  if ( ! eof_flag ) {
    found = 0;
    while ( ! found ) {
      fgets ( line_arr, maxline, dotcfile );
      if ( strcmp ( line_arr, ansiC_footer ) == 0 ) {
        found = 1;
        if ( argv3 == '1' ) {
          fputs ( "\n", Btmp );
	}
      }
      else {
        fputs ( line_arr, Btmp );
      }
    }
  };

  /***
  remove non-ansiC signature
  ***/
  if ( ! eof_flag ) {
    found = 0;
    while ( ! found ) {
      fgets ( line_arr, maxline, dotcfile );
      if ( strcmp ( line_arr, non_ansiC_header ) == 0 ) {
        found = 1;
        if ( argv3 == '1' ) {
          fputs ( "\n", Btmp );
	}
      }
      else if ( argv3 == '1' ) {
        fputs ( "\n", Btmp );
      }
    };
    found = 0;
    while ( ! found ) {
      fgets ( line_arr, maxline, dotcfile );
      if ( strcmp ( line_arr, non_ansiC_footer ) == 0 ) {
        found = 1;
        if ( argv3 == '1' ) {
          fputs ( "\n", Btmp );
	}
      }
      else if ( argv3 == '1' ) {
        if ( argv3 == '1' ) {
          fputs ( "\n", Btmp );
	}
      }
    };
    c = getc ( dotcfile );
    if ( c != '\n' ) {
      ungetc ( c, dotcfile );
    }
  }
}



void
print_non_ansiC_op ()
{
  int found;

  /***
  print to ansiC_header
  ***/
  found = 0;
  while ( ! found && ! eof_flag ) {
    if ( fgets ( line_arr, maxline, dotcfile ) == NULL ) {
      eof_flag = 1;
    };
    if ( ! eof_flag ) {
      if ( strcmp ( line_arr, ansiC_header ) == 0 ) {
        found = 1;
        if ( argv3 == '1' ) {
          fputs ( "\n", Btmp );
	}
      }
      else {
        fputs ( line_arr, Btmp );
      }
    }
  };

  /***
  remove to non-ansiC_header
  ***/
  if ( ! eof_flag ) {
    found = 0;
    while ( ! found ) {
      fgets ( line_arr, maxline, dotcfile );
      if ( strcmp ( line_arr, non_ansiC_header ) == 0 ) {
        found = 1;
        if ( argv3 == '1' ) {
          fputs ( "\n", Btmp );
	}
      }
      else if ( argv3 == '1' ) {
        fputs ( "\n", Btmp );
      }
    };
  }

  /***
  print to non_ansiC_footer
  ***/
  if ( ! eof_flag ) {
    found = 0;
    while ( ! found ) {
      fgets ( line_arr, maxline, dotcfile );
      if ( strcmp ( line_arr, non_ansiC_footer ) == 0 ) {
        found = 1;
        if ( argv3 == '1' ) {
          fputs ( "\n", Btmp );
	}
      }
      else {
        fputs ( line_arr, Btmp );
      }
    };
    c = getc ( dotcfile );
    if ( c != '\n' ) {
      ungetc ( c, dotcfile );
    }
  }
}


void
main(argc,argv)
int argc;
char *argv[];
{
  strcpy ( opfile, argv [ 1 ] );
  strcat ( opfile, ".c" );

  argv3 = argv [ 3 ] [ 0 ];

  if ( ( Btmp = fopen ( ".Btmp", "w" ) ) == NULL ) {
    printf( "\n      Can't open .Btmp for writing " );
    exit ( 1 );
  };

  if ( ( dotcfile = fopen ( opfile, "r" ) ) == NULL ) {
    printf( "\n      Can't open %s for reading\n\n", opfile );
    exit ( 1 );
  };

  eof_flag = 0;

  if ( argv [ 2 ] [ 0 ] == '1' ) {
    while ( ! eof_flag ) {
      print_non_ansiC_op ();
    }
  }
  else {
    while ( ! eof_flag ) {
      print_ansiC_op ();
    }
  };

  fclose ( Btmp );
  fclose ( dotcfile );

  strcat ( cmd, "cp .Btmp " );
  strcat ( cmd, opfile );
  strcat ( cmd, " ; rm -f .Btmp" );
  system ( cmd );

  exit ( 0 );

}
