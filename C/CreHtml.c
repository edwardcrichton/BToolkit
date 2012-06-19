/* Copyright (c) 1996, B-Core (UK) Ltd
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
#include <time.h>

#include "../MOTIF/BMotif_version.c"

/*********************************************

format of TMP/.Bhtx:

2               tot no subsid constructs
Main ref        referencing construct name & ext
2 Sub1 Sub2     Subsid Constructs
3 op1 op2 op3   OPERATIONS

each referenced construct:
Sub1 mch        construct name & ext
2 SSS TTT       SETS
3 c1 c2 c3      CONSTANTS
1 v1            VARIABLES
1 op9           OPERATIONS
1 op_p          PROMOTES
1 def1          DEFINITIONS  (7 entries for each, including name)

empty entries appear as:
0
------------------
eg:
1test_concimp
1test_absmch
1test_op
test_absmch
0
0
0
1test_op
0
0
  (^[ == ESC)

************************************************/

/******************
global declarations
******************/
char arr_A [ 5000 ] [ 50 ];
char arr_B [ 5000 ] [ 1000 ];
int arr_tot;
int in_link = 0;
int in_annot = 0;

char referencing_mch_name [ 50 ];
char referencing_mch_ext [ 10 ];
char mch_name [ 50 ];
char mch_ext [ 10 ];
int is_mch, item_tot;
char abstraction [ 60 ];
char item_name [ 50 ];
char item_ext  [ 50 ];

int sub_mch_tot;

char in_file [ 100 ];
char out_file [ 100 ];

FILE * Bhtx;
FILE * in_fileid;
FILE * out_fileid;
int c, d, e, f, done;
char word [ 500 ];
char prev_word [ 500 ];

time_t time_now;

char * AMNReservedWords [] = {
  "BEGIN",
  "END",
  "PRE",
  "THEN",
  "IF",
  "VARIANT",
  "ELSE",
  "ELSIF",
  "<--",
  "skip",
  "::",
  "bool",
  "ANY",
  "WHERE",
  "LET",
  "BE",
  "IN",
  "SELECT",
  "WHEN",
  "THEN",
  "CHOICE",
  "OR",
  "CASE",
  "OF",
  "EITHER",
  "||",
  "VAR",
  "WHILE",
  "DO",
  ""
};

void
err_exit ( n )
int n;
{
  printf ( "\n\n    CreHtml: can't create %s (code %d)\n", out_file, n );
  exit ( 1 );
}

void
CheckForReference ()
{
  int i, found;
  i = 0;
  found = 0;
  while ( ! found  && i < arr_tot ) {
    if ( strcmp ( word, arr_A [ i ] ) == 0 ) {
      fprintf ( Bhtx, "%s", arr_B [ i ] );
      found = 1;
    }
    i++;
  }
  if ( ! found ) {
    fprintf ( Bhtx, "%s", word );
  }
}

void
GetNextWord ()
{
  int i;
  c = getc ( in_fileid );
  while ( ( c < 'a' || c > 'z' ) &&
          ( c < 'A' || c > 'Z' ) &&
          ( c < '0' || c > '9' ) &&
          ( c != '<' )           &&
          ( c != '>' )           &&
          ( c != '/' )           &&
          ( c != '_' )           &&
          ( c != '/' )           &&
          ( c != '*' )           &&
          ( c != EOF )              ) {
    putc ( c, Bhtx );
    c = getc ( in_fileid );
  }
  if ( c != EOF ) {
    i = 0;
    while ( ( c >= 'a' && c <= 'z' ) ||
            ( c >= 'A' && c <= 'Z' ) ||
            ( c >= '0' && c <= '9' ) ||
            ( c == '<' ) ||
            ( c == '>' ) ||
            ( c == '/' ) ||
            ( c == '_' ) ||
            ( c == '*' )                ) {
      word [ i ] = ( char ) c;
      c = getc ( in_fileid );
      i++;
    }
    word [ i ] = '\0';
/***
    printf ( "  word: |%s|\n", word );
***/

    if ( ! in_link ) {
      if ( strcmp ( word, "<A" ) == 0 ) {
        in_link = 1;
/***
    printf ( "        in_link = 1\n" );
***/
      }
    }
    else {
      if ( strstr (  word, "</A>" ) !=NULL ) {
        in_link = 0;
/***
    printf ( "        in_link = 0\n" );
***/
      }
    }

    if ( ! in_annot ) {
      if ( strcmp ( word, "/*" ) == 0 ) {
        in_annot = 1;
/***
printf ( "in_annot = 1\n" );
***/
      }
    }
    else {
      if ( strcmp ( word, "*/" ) == 0 ) {
        in_annot = 0;
/***
printf ( "in_annot = 0\n" );
***/
      }
    }

    if ( ( ! in_link )                                     &&
         ( ! in_annot )                                    &&
         ( ( word [ 0 ] >= 'a' && word [ 0 ] <= 'z' ) ||
           ( word [ 0 ] >= 'A' && word [ 0 ] <= 'Z' )    )    ) {
      CheckForReference ();
    }
    else {
      fprintf ( Bhtx, "%s", word );
    }

    if ( c != EOF ) {
      putc ( c, Bhtx );
    }
  }
}

void
GetBhtxNum ( n )
int * n;
{
  * n = 0;
  while ( c != 27 &&  c != '\n' &&  c != EOF ) {
    * n = ( * n * 10 ) + c - '0';
    c = getc ( Bhtx );
  }
  if ( c == EOF ) {
    err_exit ( 1 );
  }
  else {
    c = getc ( Bhtx );
  }
/***
printf ( "GetBhtxNum: |%d|\n", * n );
***/
}

void
GetBhtxString ( buf )
char * buf;
{
  int i;
  i = 0;
  while ( c != 27 &&  c != '\n' &&  c != EOF ) {
    buf [ i ] = ( char ) c;
    if ( buf [ i ] == '<' ) {
      buf [ i++ ] = '&';
      buf [ i++ ] = 'l';
      buf [ i++ ] = 't';
      buf [ i ] = ';';
    }
    else if ( buf [ i ] == '>' ) {
      buf [ i++ ] = '&';
      buf [ i++ ] = 'g';
      buf [ i++ ] = 't';
      buf [ i ] = ';';
    }
    c = getc ( Bhtx );
    i++;
  }
  buf [ i ] = '\0';
/***
printf ( "GetBhtxString: |%s|\n", buf );
***/
  if ( c == EOF ) {
    err_exit ( 2 );
  }
  else {
    c = getc ( Bhtx );
  }
}

void
cre_AMNReservedWord ( res_word )
char * res_word;
{
  strcpy ( arr_A [ arr_tot ], res_word );
  strcpy ( arr_B [ arr_tot ], "<B>" );
  strcat ( arr_B [ arr_tot ], res_word );
  strcat ( arr_B [ arr_tot ], "</B>" );
  arr_tot++;
}

void
cre_Non_Op_NAME ( construct_name, construct_type, item_name )
char * construct_name;
char * construct_type;
char * item_name;
{
  strcpy ( arr_A [ arr_tot ], item_name );
  strcpy ( arr_B [ arr_tot ], "<A NAME=\"" );
  strcat ( arr_B [ arr_tot ], item_name );
  strcat ( arr_B [ arr_tot ], "\"><B>" );
  strcat ( arr_B [ arr_tot ], item_name );
  strcat ( arr_B [ arr_tot ], "</B></A>" );
  arr_tot++;
}

void
cre_Op_NAME ( construct_name, construct_type, item_name )
char * construct_name;
char * construct_type;
char * item_name;
{
  strcpy ( arr_A [ arr_tot ], item_name );
  strcpy ( arr_B [ arr_tot ], "<A NAME=\"" );
  strcat ( arr_B [ arr_tot ], "OPNAME!" );
  strcat ( arr_B [ arr_tot ], item_name );
  strcat ( arr_B [ arr_tot ], "\">" );
  if ( ! is_mch ) {
    strcat ( arr_B [ arr_tot ], "<A HREF=\"" );
    strcat ( arr_B [ arr_tot ], abstraction );
    strcat ( arr_B [ arr_tot ], ".html#OPNAME!" );
    strcat ( arr_B [ arr_tot ], item_name );
    strcat ( arr_B [ arr_tot ], "\">" );
  }
  strcat ( arr_B [ arr_tot ], item_name );
  strcat ( arr_B [ arr_tot ], "</A>" );
  arr_tot++;
}

void
cre_HREF ( construct_name, construct_type, ref_type, item_name )
char * construct_name;
char * construct_type;
char * ref_type;
char * item_name;
{
  strcpy ( arr_A [ arr_tot ], item_name );
  strcpy ( arr_B [ arr_tot ], "<A HREF=\"" );
  strcat ( arr_B [ arr_tot ], construct_name );
  strcat ( arr_B [ arr_tot ], "." );
  strcat ( arr_B [ arr_tot ], construct_type );
  strcat ( arr_B [ arr_tot ], ".html#" );
  if ( strcmp (  ref_type, item_name ) == 0 ) {   /* it's an op */
    strcat ( arr_B [ arr_tot ], "OPNAME!" );
    strcat ( arr_B [ arr_tot ], ref_type );
  }
  else {
    strcat ( arr_B [ arr_tot ], ref_type );
  }
  strcat ( arr_B [ arr_tot ], "\">" );
  strcat ( arr_B [ arr_tot ], item_name );
  strcat ( arr_B [ arr_tot ], "</A>" );
  arr_tot++;
}


/*void*/
/* should be int*/
int
main ()
{
  int i, j;
  char * getenv(), * name, bkit [ 250 ];

  in_link = 0;

  name = getenv ( "BKIT" );
  if ( name == NULL ) {
    printf ( "\n\n              Environment variable BKIT not set\n" );
    exit (1);
  }
  strcpy ( bkit, name );

/***
printf ( "\n------- CreHtml: TMP/.Bhtx --------\n\n" ); fflush ( stdout );
system ( "cat TMP/.Bhtx" ); fflush ( stdout );
printf ( "-----------------------------------\n" ); fflush ( stdout );
***/

  Bhtx = fopen ( "TMP/.Bhtx", "r" );
  if ( Bhtx == NULL ) {
    printf ( "\n\n    CreHtml: can't open \"TMP/.Bhtx\" for reading\n" );
    exit ( 1 );
  }
  c = getc ( Bhtx );

  arr_tot = 0;

  GetBhtxNum ( & sub_mch_tot );

  /***
  main construct
  ***/
  GetBhtxString ( mch_name );
  GetBhtxString ( mch_ext );

  strcpy ( in_file, "CFG/" );
  strcat ( in_file, mch_name );
  strcat ( in_file, "." );
  strcat ( in_file, mch_ext );
  if   ( strcmp ( mch_ext, "mch" ) == 0 ) is_mch = 1;
  else                                    is_mch = 0;

/***
printf ( "is_mch=%d\n", is_mch ); fflush ( stdout );
***/

  strcpy ( out_file, "HTX/" );
  strcat ( out_file, mch_name );
  strcat ( out_file, "." );
  strcat ( out_file, mch_ext );
  strcat ( out_file, ".html" );

  strcpy ( referencing_mch_name, mch_name );
  strcpy ( referencing_mch_ext, mch_ext );

/***
printf ( "\nin_file:  %s\nout_file: %s\n\n", in_file, out_file );
***/

  /***
  main construct
  ***/

  /***
  create NAME tag for MACHINE, IMPLEMENTATION or REFINEMENT
  ***/
  if ( strcmp ( mch_ext, "mch" ) == 0 ) {
    cre_Non_Op_NAME ( mch_name, mch_ext, "MACHINE" );
  }
  else if ( strcmp ( mch_ext, "imp" ) == 0 ) {
    cre_Non_Op_NAME ( mch_name, mch_ext, "IMPLEMENTATION" );
  }
  else {
    cre_Non_Op_NAME ( mch_name, mch_ext, "REFINEMENT" );
  }

  /***
  create NAME tags for SETS, CONSTANTS, INVARIANT and PROMOTES
  ***/
  cre_Non_Op_NAME ( mch_name, mch_ext, "CONSTRAINTS" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "REFINES" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "SEES" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "USES" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "INCLUDES" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "IMPORTS" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "VARIABLES" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "INITIALISATION" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "SETS" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "CONSTANTS" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "PROPERTIES" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "OPERATIONS" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "INVARIANT" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "PROMOTES" );
  cre_Non_Op_NAME ( mch_name, mch_ext, "DEFINITIONS" );

  j = 0;
  while ( AMNReservedWords [ j ] [ 0 ] != '\0' ) {
    cre_AMNReservedWord ( AMNReservedWords [ j++ ] );
  }

  /***
  create HREF to MACHINE of subordinate
  ***/
  GetBhtxNum ( & item_tot );  /* REFINES SEES USES INCLUDES IMPORTS */
/***
printf ( " no. of subordinates=%d\n", item_tot );
***/
  for ( j = 0 ; j < item_tot ; j++ ) {
    GetBhtxString ( item_name );
    GetBhtxString ( item_ext );
    if ( ( ! is_mch ) && ( j == 0 ) ) { /* this is the abstraction */
      sprintf ( abstraction, "%s.%s", item_name, item_ext );
/***
printf ( "abstraction=`%s'\n", abstraction ); fflush ( stdout );
***/
    }
    if ( strcmp ( item_ext, "mch" ) == 0 ) {
      cre_HREF ( item_name, "mch", "MACHINE", item_name );
    }
    else if ( strcmp ( item_ext, "imp" ) == 0 ) {
      cre_HREF ( item_name, "imp", "IMPLEMENTATION", item_name );
    }
    else {
      cre_HREF ( item_name, "ref", "REFINEMENT", item_name );
    }
  }

  /***
  create NAME tag for op_name
  ***/
  GetBhtxNum ( & item_tot ); /* OPERATIONS */
/***
printf ( "   no. of operations=%d\n", item_tot );
***/
  for ( j = 0 ; j < item_tot ; j++ ) {
    GetBhtxString ( item_name );
    cre_Op_NAME ( mch_name, mch_ext, item_name );
  }

  /***
  subordinate constructs
  ***/
  for ( i = 0 ; i < sub_mch_tot ; i++ ) {

    GetBhtxString ( mch_name );
    GetBhtxString ( mch_ext );

    /***
    create HREF to SETS of subordinate
    ***/
    GetBhtxNum ( & item_tot );
/***
printf ( " no. of sets=%d\n", item_tot );
***/
    for ( j = 0 ; j < item_tot ; j++ ) {
      GetBhtxString ( item_name );
      cre_HREF ( mch_name, mch_ext, "SETS", item_name );
    }

    /***
    create HREF to CONSTANTS of subordinate
    ***/
    GetBhtxNum ( & item_tot );
/***
printf ( " no. of constants=%d\n", item_tot );
***/
    for ( j = 0 ; j < item_tot ; j++ ) {
      GetBhtxString ( item_name );
      cre_HREF ( mch_name, mch_ext, "CONSTANTS", item_name );
    }

    /***
    create HREF to INVARIANT of subordinate
    ***/
    GetBhtxNum ( & item_tot );
/***
printf ( " no. of invariants=%d\n", item_tot );
***/
    for ( j = 0 ; j < item_tot ; j++ ) {
      GetBhtxString ( item_name );
      cre_HREF ( mch_name, mch_ext, "INVARIANT", item_name );
    }

    /***
    create HREF to op_name of subordinate
    ***/
    GetBhtxNum ( & item_tot );
/***
printf ( " no. of op_name=%d\n", item_tot );
***/
    for ( j = 0 ; j < item_tot ; j++ ) {
      GetBhtxString ( item_name );
      cre_HREF ( mch_name, mch_ext, item_name, item_name );
    }

    /***
    create HREF to PROMOTES of subordinate
    ***/
    GetBhtxNum ( & item_tot );
/***
printf ( " no. of promotes=%d\n", item_tot );
***/
    for ( j = 0 ; j < item_tot ; j++ ) {
      GetBhtxString ( item_name );
      cre_HREF ( mch_name, mch_ext, "PROMOTES", item_name );
    }

    /***
    create HREF to DEFINITIONS of subordinate
    ***/
    GetBhtxNum ( & item_tot );
/***
printf ( " no. of definitions=%d\n", item_tot );
***/
    for ( j = 0 ; j < item_tot ; j++ ) {
      GetBhtxString ( item_name );
      cre_HREF ( mch_name, mch_ext, "DEFINITIONS", item_name );
    }

  }

  fclose ( Bhtx );

/***
  printf ( "\n" );
  for ( i = 0 ; i < arr_tot ; i++ ) {
    printf ( "%s\t%s\n", arr_A [ i ], arr_B [ i ] );
  }
***/

  in_fileid = fopen ( in_file, "r" );
  if ( in_fileid == NULL ) {
    printf ( "\n\n    CreHtml: can't open %s for reading\n", in_file );
    exit ( 1 );
  }

  Bhtx = fopen ( "TMP/.Bhtx", "w" );
  if ( Bhtx == NULL ) {
    printf ( "\n\n    CreHtml: can't open %s for writing\n", "TMP/.Bhtx" );
    exit ( 1 );
  }

  fprintf ( Bhtx, "<HTML>\n<HEAD>\n  <META NAME=\"Author\" CONTENT=\"%s\">\n  <META NAME=\"Description\" CONTENT=\"Hypertext version of %s\">\n  <TITLE>The %s ", toolkit_ver, referencing_mch_name , referencing_mch_name );
  if ( strcmp ( referencing_mch_ext, "mch" ) == 0 ) {
    fprintf ( Bhtx, "machine" );
  }
  else if ( strcmp ( referencing_mch_ext, "imp" ) == 0 ) {
    fprintf ( Bhtx, "implementation" );
  }
  else {
    fprintf ( Bhtx, "refinement" );
  }
  fprintf ( Bhtx, "</TITLE>\n</HEAD>\n<BODY TEXT=\"#000000\" BGCOLOR=\"#FFFFE0\" LINK=\"#2A9BFF\" VLINK=\"#FF6565\" ALINK=\"#FF0000\">\n\n<PRE>" );

  while ( c != EOF ) {
    GetNextWord ();
  }

  fprintf ( Bhtx, "</PRE>\n<P><HR WIDTH=80%%>\n<P>\n<H3><FONT COLOR=\"#004EFF\">Analysed Constructs</FONT></H3>\n\n<MENU>\n<DD><A HREF=\"ConstructsSummary.html\">Hypertext Constructs Page</A></DD>\n</MENU>\n\n<H3><FONT COLOR=\"#004EFF\">On-line Help</FONT></H3>\n" );

  time_now = time ( NULL );

  fprintf ( Bhtx, "<MENU>\n<DD><A HREF=\"%s/BHELP/Contents.html\">Help Contents Page</A>\n<DD><A HREF=\"%s/BHELP/Index.html\">Index</A></DD>\n</MENU>\n<CENTER>\n<HR  WIDTH=33%% SIZE=2 COLOR=\"#CF6500\" NOSHADE>\n<FONT FACE=\"sans-serif, Arial, Helvetica\"><FONT COLOR=\"#CF6500\"><FONT SIZE=-2>Document Last Updat %s<BR>\n<IMG SRC=\"%s/BHELP/B.gif\" VSPACE=5><BR>%s</FONT></FONT></FONT>\n<CENTER>\n<HR  WIDTH=33%% SIZE=2 COLOR=\"#CF6500\" NOSHADE>\n</CENTER>\n</BODY>\n</HTML>\n", bkit, bkit, ctime ( & time_now ), bkit, toolkit_ver );

  fclose ( in_fileid );
  fclose ( Bhtx );

/***
system("cat TMP/.Bhtx");
***/

  Bhtx = fopen ( "TMP/.Bhtx", "r" );
  if ( Bhtx == NULL ) {
    printf ( "\n\n    CreHtml: can't open %s for reading\n", "TMP/.Bhtx" );
    exit ( 1 );
  }
   
  out_fileid = fopen ( out_file, "w" );
  if ( out_fileid == NULL ) {
    printf ( "\n\n    CreHtml: can't open %s for writing\n", out_file );
    exit ( 1 );
  }

  c = getc ( Bhtx );
  while ( c != EOF ) {
    while ( c != EOF && c != '<' && c != '>' ) {
      putc ( c, out_fileid );
      c = getc ( Bhtx );
    }
    if ( c == '<' ) {
      i = 0;
      while ( c != EOF &&
              c != '>' &&
              c != 27 && c != '\t' && c != '\n' ) {
        word [ i ] = ( char ) c;
        i++;
        c = getc ( Bhtx );
      }
      word [ i ] = '\0';
      if  ( strcmp ( word, "<BODY" ) == 0 ) {
        fputs ( word, out_fileid );
        while ( c != EOF && c != '>' ) {
          putc ( c, out_fileid );
          c = getc ( Bhtx );
	}
        if ( c == '>' ) {
          putc ( c, out_fileid );
          c = getc ( Bhtx );
	}
      }
      else if ( c == '>' ) {
        fputs ( word, out_fileid );
        putc ( c, out_fileid );
        c = getc ( Bhtx );
      }
      else if ( c != EOF && i == 2 && 
                ( ( word [ 1 ] >= 'a' && word [ 1 ] <= 'z' ) ||
                  ( word [ 1 ] >= 'A' && word [ 1 ] <= 'Z' )    ) ) {
        fputs ( word, out_fileid );
        while ( c != EOF && c != '>' ) {
          putc ( c, out_fileid );
          c = getc ( Bhtx );
	}
        if ( c == '>' ) {
          putc ( c, out_fileid );
          c = getc ( Bhtx );
	}
      }
      else {
        fputs ( "&lt;", out_fileid );
        i = 1;
/***
printf("|%s|\n",word);
***/
        while ( word [ i ] != '\0' ) {
          putc ( word [ i ], out_fileid );
          i++;
	}
        if ( c != EOF ) {
          putc ( c, out_fileid );
          c = getc ( Bhtx );
	}
        if ( ( i >= 2 ) &&
             ( word [ i - 2 ] == '<' ) &&
             ( ( word [ i - 1 ] >= 'a' && word [ i - 1 ] <= 'z' ) ||
               ( word [ i - 1 ] >= 'A' && word [ i - 1 ] <= 'Z' )    ) ) {
          while ( c != EOF && c != '>'  && c != '<' ) {
            putc ( c, out_fileid );
            c = getc ( Bhtx );
	  }
	}
        if ( c != EOF && c != '<' ) {
          putc ( c, out_fileid );
          c = getc ( Bhtx );
	}
      }
    }
    else if ( c == '>' ) {
      fputs ( "&gt;", out_fileid );
      c = getc ( Bhtx );
    }
  }

  fclose ( Bhtx );
  fclose ( out_fileid );

  exit ( 0 );   
}
