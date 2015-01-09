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
#include <time.h>

#include "../MOTIF/BMotif_version.c"



#define max_name  55
#define max_ref   5000

FILE * Bcom;
FILE * Outfile;
FILE * Infile;

char word [ 5002 ];


char _dirname_  [ 400 ];
char filename [ max_name ];
char mchname  [ max_name ];
char impname  [ max_name ];

char own_arr_val        [ max_ref ] [ max_name ];
char own_arr_type       [ max_ref ];
int  tot_own_arr;

char ref_arr_mch_val    [ max_ref ] [ max_name ];
char ref_arr_name_val   [ max_ref ] [ max_name ];
char ref_arr_type       [ max_ref ];
int  tot_ref_arr;

int c, i, ll;

int in_annot = 0;

/***/
void
print_data ()
{
  printf ( "_dirname_: %s\nfilename: %s\nmchname: %s\nimpname: %s\n", _dirname_, filename, mchname, impname );
  printf ( " own:\n" );
  for ( i = 0 ; i < tot_own_arr ; i++ ) {
    printf ( "    `%c' `%s'\n", own_arr_type [ i ], own_arr_val [ i ] );
  }
  printf ( " ref:\n" );
  for ( i = 0 ; i < tot_ref_arr ; i++ ) {
    printf ( "    `%c' `%s' `%s'\n", ref_arr_type [ i ], ref_arr_mch_val [ i ], ref_arr_name_val [ i ] );
  }
}
/***/

void
err_exit ( n )
int n;
{
  printf ( "\n\n    CreHtmlc: error code %d\n", n );
  exit ( 1 );
}

void
CheckForReference ()
{
  int i, found;

  i = 0;
  found = 0;
  while ( ! found  && i < tot_own_arr ) {
    if ( strcmp ( word, own_arr_val [ i ] ) == 0 ) {
      fprintf ( Outfile, "<A NAME=\"" );
      if ( own_arr_type [ i ] == 'P' ) { /* slib ops */
        if ( ( strlen ( word ) > 5 ) &&
             ( word [ 0 ] == 'I' )   &&
             ( word [ 1 ] == 'N' )   &&
             ( word [ 2 ] == 'I' )   &&
             ( word [ 3 ] == '_' )      ) {
          fprintf ( Outfile, "%s!%s\"><A HREF=\"%s.mch.html\">%s</A></A>", "OPNAME", word, mchname, word );
	}
        else {
          fprintf ( Outfile, "%s!%s\"><A HREF=\"%s.mch.html#OPNAME!%s\">%s</A></A>", "OPNAME", word, mchname, word, word );
	}
      }
      else if ( own_arr_type [ i ] == 'O' ) {
        if ( ( strlen ( word ) > 5 ) &&
             ( word [ 0 ] == 'I' )   &&
             ( word [ 1 ] == 'N' )   &&
             ( word [ 2 ] == 'I' )   &&
             ( word [ 3 ] == '_' )      ) {
          fprintf ( Outfile, "%s!%s\"><A HREF=\"%s.html#IMPORTS\">%s</A></A>", "OPNAME", word, impname, word );
	}
        else {        
          fprintf ( Outfile, "%s!%s\"><A HREF=\"%s.html#OPNAME!%s\">%s</A></A>", "OPNAME", word, impname, word, word );
	}
      }
      else if ( own_arr_type [ i ] == 'C' ) { /* constants from the .imp */
        fprintf ( Outfile, "%s!%s\"><A HREF=\"%s.html#CONSTANTS\">%s</A></A>", "CONSTANTS", word, impname, word );
      }
      else if ( own_arr_type [ i ] == 'D' ) { /* constants from the .mch */
        fprintf ( Outfile, "%s!%s\"><A HREF=\"%s.mch.html#CONSTANTS\">%s</A></A>", "CONSTANTS", word, mchname, word );
      }
      else if ( own_arr_type [ i ] == 'S' ) { /* enum elements from the .imp */
        fprintf ( Outfile, "%s!%s\"><A HREF=\"%s.html#SETS\">%s</A></A>", "SETS", word, impname, word );
      }
      else if ( own_arr_type [ i ] == 'T' ) { /* enum elements from the .mch */
         fprintf ( Outfile, "%s!%s\"><A HREF=\"%s.mch.html#SETS\">%s</A></A>", "SETS", word, mchname, word );
      }
      else if ( own_arr_type [ i ] == 'M' ) {
        fprintf ( Outfile, "%s!%s\">%s</A>", "IMPLEMENTATION", word, word );
      }
      else if ( own_arr_type [ i ] == 'F' ) {
        fprintf ( Outfile, "%s\">%s</A>", "MODULENAME", word );
      }
      found = 1;
      strcpy ( own_arr_val [ i ], "" );       /* do it once only */
    }
    i++;
  }

  if ( ! found ) {
    i = 0;
    while ( ! found  && i < tot_ref_arr ) {
/***
printf ( "looking for word `%s'\n", ref_arr_name_val [ i ] );
***/
      if ( strcmp ( word, ref_arr_name_val [ i ] ) == 0 ) {
        if ( ref_arr_type [ i ] == 'b' ) {
          fprintf ( Outfile, "<B>%s</B>", word );
	}
        else {
          fprintf ( Outfile, "<A HREF=\"%s.html", ref_arr_mch_val [ i ] );
          if      ( ref_arr_type [ i ] == 'o' ) {
            fprintf ( Outfile, "#%s!%s\">%s</A>", "OPNAME", word, word );
	  }
          else if ( ref_arr_type [ i ] == 'c' ) {
            fprintf ( Outfile, "#%s!%s\">%s</A>", "CONST", word, word );
	  }
          else if ( ref_arr_type [ i ] == 'i' ) { /* imported module */
            fprintf ( Outfile, "#%s\">%s</A>", "MODULENAME", word );
	  }
          else if ( ref_arr_type [ i ] == 'm' ) {
            fprintf ( Outfile, "#%s!%s\">%s</A>", "MCHNAME", word, word );
	  }
          else if ( ref_arr_type [ i ] == 'v' ) { /* ref subsid SET (eg BYTE) */
            fprintf ( Outfile, "#%s\">%s</A>", "SETS", word );
	  }
          else if ( ref_arr_type [ i ] == 'w' ) { /* ref global (imported) var */
            fprintf ( Outfile, "#%s\">%s</A>", "MACHINE", word );
	  }
          else if ( ref_arr_type [ i ] == 'h' ) { /* VHDL var */
            fprintf ( Outfile, "#%s\">%s</A>", "INVARIANT", word );
	  }
          else if ( ref_arr_type [ i ] == 'x' ) { /* ref to subsidiary mch/imp */
            fprintf ( Outfile, "#%s\">%s</A>", word, word );
	  }
          else if ( ref_arr_type [ i ] == 's' ) { /* imp from which translated */
            fprintf ( Outfile, "#%s\">%s</A>", "MACHINE", word );
	  }
          else if ( ref_arr_type [ i ] == 't' ) { /* code module */
            fprintf ( Outfile, "\">%s</A>", word );
	  }
          else if ( ref_arr_type [ i ] == 'y' ) { /* SLIB mch for .param code */
            fprintf ( Outfile, "#%s\">%s</A>", "IMPLEMENTATION", word );
	  }
          else if ( ref_arr_type [ i ] == 'z' ) { /* op in imp */
            fprintf ( Outfile, "#%s\">%s</A>", word, word );
	  }
          else if ( ref_arr_type [ i ] == 'a' ) { /* ARCHITECTURE */
            char buf [ 250 ];
            strcpy ( buf, ref_arr_mch_val [ i ] );
            buf [ strlen ( buf ) - 7 ] = '\0';
            fprintf ( Outfile, "#%s!%s_architecture\"><B>%s</B></A>", "OPNAME", buf, word );
	  }
	  /*
          else if ( ref_arr_type [ i ] == 'p' ) { /? PORT ?/
            char buf [ 250 ];
            strcpy ( buf, ref_arr_mch_val [ i ] );
            buf [ strlen ( buf ) - 7 ] = '\0';
            fprintf ( Outfile, "#%s!%s_port\">%s</A>", "OPNAME", buf, word );
	  }
          */
	}
        found = 1;
      }
      i++;
    }

    if ( ! found ) {             /* not referenced */
      char buf [ 1000 ];
      int r;
      int k = 0;
      while ( word [ k ] != '\0' ) {
        r = 0;
        while ( ( word [ k ] != '\0' ) &&
                ( word [ k ] != '[' )  &&
                ( word [ k ] != ']' )     ) {
          buf [ r++ ] = word [ k++ ];
	}
        buf [ r ] = '\0';
        if ( strcmp ( buf, "ARRAY" ) == 0 ) {
          fprintf ( Outfile, "<B>ARRAY</B>" );
	}
        else if ( strcmp ( buf, "[" ) == 0 ) {
          fprintf ( Outfile, "<B>[</B>" );
	}
        else if ( strcmp ( buf, "]" ) == 0 ) {
          fprintf ( Outfile, "<B>]</B>" );
	}
        else {
          fputs ( buf, Outfile );
	}
        if ( word [ k ] == '[' ) {
          fprintf ( Outfile, "<B>[</B>" );
          k++;
	}
        else if ( word [ k ] == ']' ) {
          fprintf ( Outfile, "<B>]</B>" );
          k++;
	}
      }

    } /* if ( ! found ) */
  } /* if ( ! found ) */
}

void
GetNextWord ()
{
  int i;

  c = getc ( Infile );
  while ( ( c < 'a' || c > 'z' ) &&
          ( c < 'A' || c > 'Z' ) &&
          ( c < '0' || c > '9' ) &&
          ( c != '.' )           &&
          ( c != '#' )           &&
          ( c != '{' )           &&
          ( c != '}' )           &&
          ( c != '[' )           &&
          ( c != ']' )           &&
          ( c != '_' )           &&
          ( c != '.' )           &&
          ( c != '/' )           &&
          ( c != '*' )           &&
          ( c != EOF )              ) {
    putc ( c, Outfile );
    c = getc ( Infile );
  }
  if ( c != EOF ) {
    i = 0;
    while ( ( c >= 'a' && c <= 'z' ) ||
            ( c >= 'A' && c <= 'Z' ) ||
            ( c >= '0' && c <= '9' ) ||
            ( c == '.' )             ||
            ( c == '#' )             ||
            ( c == '{' )             ||
            ( c == '}' )             ||
            ( c == '[' )             ||
            ( c == ']' )             ||
            ( c == '_' )             ||
            ( c == '.' )             ||
/*            ( c == '/' )             || */
            ( c == '*' )                ) {
      word [ i ] = ( char ) c;
      c = getc ( Infile );
      i++;
    }
    word [ i ] = '\0';
/***
    printf ( "  word: |%s|\n", word );
***/

    if ( ! in_annot ) {
      if ( strcmp ( word, "/*" ) == 0 ) {
        in_annot = /* 1 */ 0;               /***** so, it's not used ! *****/
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

    if ( ( ! in_annot )                                   &&
         ( ( word [ 0 ] >= 'a' && word [ 0 ] <= 'z' ) ||
           ( word [ 0 ] >= 'A' && word [ 0 ] <= 'Z' ) ||
           ( word [ 0 ] == '#' )                      ||
           ( strcmp ( word, "}" ) == 0 )              ||
           ( strcmp ( word, "{" ) == 0 )                      )   ) {
        CheckForReference ();
    }
    else {
      fprintf ( Outfile, "%s", word );
    }

    if ( c != EOF ) {
      putc ( c, Outfile );
    }
  }
}

void
pre_process_file_into_Bhtx ()
{
  /***
  replaces < and > with &lt; and &gt;
  ***/

  strcpy ( word, _dirname_ );
  strcat ( word, filename );
  Infile =  fopen ( word, "r" );
  if ( Infile == NULL ) {
    printf ( "\n\n    CreHtmlc: can't open \"%s\" for reading\n", word );
    exit ( 1 );
  }

  Outfile = fopen ( "TMP/.Bhtx", "w" );
  if ( Outfile == NULL ) {
    printf ( "\n\n    CreHtml: can't open %s for writing\n", "TMP/.Bhtx" );
    exit ( 1 );
  }
   
  c = getc ( Infile );
  while ( c != EOF ) {
    /***
    load line into buf
    ***/
    i = 0;
    while ( ( c != EOF ) && ( c != '\n' ) && i < 5000 ) {
      word [ i++ ] = c;
      c = getc ( Infile );
    }
    word [ i ] = '\0';
    ll = i;
    i = 0;
    for ( i = 0 ; i < ll ; i++ ) {
      if ( word [ i ] == '<' ) {
        fputs ( "&lt;", Outfile );
      }
      else if ( word [ i ] == '>' ) {
        fputs ( "&gt;", Outfile );
      }
      else {
        putc ( word [ i ], Outfile );
      }
    }

    if ( c != EOF ) {
       putc ( c, Outfile );
       c = getc ( Infile );
    }
  }

  fclose ( Infile );
  fclose ( Outfile );

/***
sprintf ( word, "diff %s%s %s", _dirname_, filename, "TMP/.Bhtx" );
printf ( "\n\n------\ndiff: < %s%s   > %s\n", _dirname_, filename, "TMP/.Bhtx" );
system ( word );
printf ( "------\n" );
***/
}


/*void*/
/* should be int*/
int
main ( argc, argv )
int argc;
char *argv[];
{
  time_t time_now;
  char * name, bkit [ 250 ];

  printf ( "." ); fflush ( stdout );

  name = getenv ( "BKIT" );
  if ( name == NULL ) {
    printf ( "\n\n              Environment variable BKIT not set\n" );
    exit ( 1 );
  }
  strcpy ( bkit, name );

  tot_own_arr = 0;
  tot_ref_arr = 0;

/***
printf ( "contents of .Bcom:\n" );
system ( "cat .Bcom" );
***/

  Bcom = fopen ( ".Bcom", "r" );
  if ( Bcom == NULL ) {
    printf ( "\n\n    CreHtmlc: can't open \".Bcom\" for reading\n" );
    exit ( 1 );
  }

  c = getc ( Bcom );
  i = 0;
  while ( c != '|' && c != EOF ) {
    _dirname_ [ i ] = ( char ) c;
    i++;
    c = getc ( Bcom );
  }
  if ( c == EOF ) {
    err_exit ( 1 );
  }
  _dirname_ [ i ] = '\0';

  c = getc ( Bcom );
  i = 0;
  while ( c != '|' && c != EOF ) {
    filename [ i ] = ( char ) c;
    i++;
    c = getc ( Bcom );
  }
  if ( c == EOF ) {
    err_exit ( 2 );
  }
  filename [ i ] = '\0';

  c = getc ( Bcom );
  i = 0;
  while ( c != '|' && c != EOF ) {
    impname [ i ] = ( char ) c;
    i++;
    c = getc ( Bcom );
  }
  if ( c == EOF ) {
    err_exit ( 3 );
  }
  impname [ i ] = '\0';

  c = getc ( Bcom );
  i = 0;
  while ( c != '\n' && c != EOF ) {
    mchname [ i ] = ( char ) c;
    i++;
    c = getc ( Bcom );
  }
  if ( c == EOF ) {
    err_exit ( 4 );
  }
  mchname [ i ] = '\0';
  own_arr_type [ tot_own_arr ] = 'M';
  strcpy ( own_arr_val [ tot_own_arr ], mchname );
  tot_own_arr++;

/***
printf ( "tot_own_arr=%3d max_ref=%3d\n", tot_own_arr, max_ref );
***/

  printf ( "." ); fflush ( stdout );

  c = getc ( Bcom );

  while ( c != EOF ) {

    if ( c >= 'A' && c <= 'Z' ) {                   /* own_arr */

      if ( tot_own_arr < max_ref ) {
        own_arr_type [ tot_own_arr ] = ( char ) c;
      }
      c = getc ( Bcom );            /* read `|' */
      if ( c == EOF ) {
        err_exit ( 5 );
      }
      i = 0;
      c = getc ( Bcom );
      while ( c != '\n' &&  c != EOF ) {
        if ( tot_own_arr < max_ref ) {
          own_arr_val [ tot_own_arr ] [ i ] = ( char ) c;
          i++;
	}
        c = getc ( Bcom );
      }
      if ( tot_own_arr < max_ref ) {
        own_arr_val [ tot_own_arr ] [ i ] = '\0';
        tot_own_arr++;
      }

/***
printf ( "tot_own_arr=%3d max_ref=%3d\n", tot_own_arr, max_ref );
***/

    }

    else {  
                                                     /* ref_arr */
      if ( tot_ref_arr < max_ref ) {
        ref_arr_type [ tot_ref_arr ] = ( char ) c;
      }
      c = getc ( Bcom );
      if ( c == EOF ) {
        err_exit ( 6 );
      }
      i = 0;
      while ( c != '|' &&  c != EOF ) {
        if ( tot_ref_arr < max_ref ) {
          ref_arr_mch_val [ tot_ref_arr ] [ i ] = ( char ) c;
          i++;
	}
        c = getc ( Bcom );
      }
      ref_arr_mch_val [ tot_ref_arr ] [ i ] = '\0';
      if ( c == EOF ) {
        err_exit ( 7 );
      }
      c = getc ( Bcom );
      i = 0;
      while ( c != '\n' &&  c != EOF ) {
        ref_arr_name_val [ tot_ref_arr ] [ i ] = ( char ) c;
        i++;
        c = getc ( Bcom );
      }
      if ( tot_ref_arr < max_ref ) {
        ref_arr_name_val [ tot_ref_arr ] [ i ] = '\0';
        tot_ref_arr++;
      }

/***
printf ( "tot_ref_arr=%3d max_ref=%3d\n", tot_ref_arr, max_ref );
***/

    }

    if ( c != EOF ) {
        c = getc ( Bcom );
    }

  }

  fclose ( Bcom );

  /***
  if error - report only once (last - .g file)
   ***/
  if ( ( ( tot_own_arr == max_ref ) || ( tot_ref_arr == max_ref ) ) &&
       ( filename [ strlen ( filename ) - 1 ] == 'g' )                  ) {
    printf ( "    CreHtmlc: capacity reached\n\n    All references may not be present in the html modules\n\n" );
  }

/***
  printf ( "_dirname_: %s\nfilename: %s\nmchname: %s\nimpname: %s\n", _dirname_, filename, mchname, impname );
***/

/***
print_data ();
***/

  pre_process_file_into_Bhtx ();

  Infile =  fopen ( "TMP/.Bhtx", "r" );
  if ( Outfile == NULL ) {
    printf ( "\n\n    CreHtmlc: can't open \"%s\" for reading\n", "TMP/.Bhtx" );
    exit ( 1 );
  }

  strcpy ( word, "HTX/" );
  strcat ( word, filename );
  strcat ( word, ".html" );
  Outfile =  fopen ( word, "w" );
  if ( Outfile == NULL ) {
    printf ( "\n\n    CreHtmlc: can't open \"%s\" for writing\n", word );
    exit ( 1 );
  }

/***
  printf ( "  %s opened for reading\n",  word );
***/

/***
  printf ( "  %s opened for writing\n",  word );
***/

  fprintf ( Outfile, "<HTML>\n<HEAD>\n  <META NAME=\"Author\" CONTENT=\"%s\">\n  <META NAME=\"Description\" CONTENT=\"Hypertext version of %s Code Module\">\n  <TITLE>%s Code Module</TITLE>\n</HEAD>\n<BODY TEXT=\"#333333\" LINK=\"#2A6BF9\" VLINK=\"#EE4444\" ALINK=\"#EE0000\">\n<PRE>\n", toolkit_ver, filename, filename );

  printf ( "." ); fflush ( stdout );

  c = 'a';
  while ( c != EOF ) {
    GetNextWord ();
  }

  fprintf ( Outfile, "</PRE>\n<P></P><HR></HR>\n<P></P>\n<H3><FONT COLOR=\"#004EFF\">Analysed Constructs</FONT></H3>\n\n<MENU>\n<DD><A HREF=\"ConstructsSummary.html\">Hypertext Constructs Page</A></DD>\n</MENU>\n\n<H3><FONT COLOR=\"#004EFF\">On-line Help</FONT></H3>\n\n" );

  time_now = time ( NULL );

  fprintf ( Outfile, "<MENU>\n<DD><A HREF=\"%s/BHELP/Contents.html\">Help Contents Page</A>\n<DD><A HREF=\"%s/BHELP/Index.html\">Index</A></DD>\n</MENU>\n<CENTER>\n<HR  WIDTH=33%% SIZE=2 COLOR=\"#CF6500\" NOSHADE>\n<FONT FACE=\"sans-serif, Arial, Helvetica\"><FONT COLOR=\"#CF6500\"><FONT SIZE=-2>Document Last Updated: %s<BR>\n<IMG SRC=\"%s/BHELP/B.gif\" VSPACE=5><BR>%s</FONT></FONT></FONT>\n<CENTER>\n<HR  WIDTH=33%% SIZE=2 COLOR=\"#CF6500\" NOSHADE>\n</CENTER>\n</BODY>\n</HTML>\n", bkit, bkit, ctime ( & time_now ), bkit, toolkit_ver );

  fclose ( Infile );
  fclose ( Outfile );


  exit ( 0 );

}
