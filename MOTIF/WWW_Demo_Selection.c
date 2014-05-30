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
#include <stdlib.h>
#include <unistd.h>

#include <Xm/XmAll.h>

#define MAX_WWW_DEMO_NAME 50
#define MAX_WWW_DEMO      50
char demo_directory [ MAX_WWW_DEMO + 1 ] [ MAX_WWW_DEMO_NAME + 1 ];

int c_arr [ MAX_WWW_DEMO ];

int tot_www_dirs;

char* bkit;

XtAppContext app;
Display *display;
static XmStringCharSet charset = (XmStringCharSet) XmSTRING_DEFAULT_CHARSET;


Pixel GetPixel ( colourname )
char *colourname;
{
  int scr = DefaultScreen ( display );
  Colormap cmap = DefaultColormap ( display, scr );
  XColor colour, ignore;

  if ( XAllocNamedColor( display, cmap, colourname, &colour, &ignore ) )
    return ( colour.pixel );
  else
  {
    printf ( "Warning unable to allocate colour %s\n", colourname );
    return (WhitePixel( display, scr ));
  }
}

void
pushed( widget, client_data )
Widget widget;
XtPointer client_data;
{
  char buf [ 1000 ];
  int i = * ( int * ) client_data;

  strcpy ( buf, "WWW_DEMOS/" );
  strcat ( buf, demo_directory [ i ] );
  chdir ( buf );
  strcpy ( buf, bkit );
  strcat ( buf, "/BToolkit" );
  execl( buf, "BToolkit", (char *) 0);
  printf ( "\n\n  Can't execute %s\n\n", buf );
  exit ( 1 );
}

void get_demo_directories ()
{
  int i, j, c;
  FILE * fileid;
  char bpda [ MAX_WWW_DEMO_NAME + 10 ];
  FILE * Bpda;

  unlink ( ".Bdir" );

  system ( "cd WWW_DEMOS ; ls > ../.Bdir" );

  fileid = fopen ( ".Bdir", "r" );
  if ( fileid == NULL ) {
    printf ( "\n\n  Can't open .Bdir for reading\n\n" );
    exit (1);
  }

  i = 0;
  c = getc ( fileid );
  while ( c != EOF && i < MAX_WWW_DEMO ) {
    j = 0;
    while ( c != EOF && c != '\n' && c != ' ' && j < MAX_WWW_DEMO_NAME ) {
      demo_directory [ i ] [ j ] = c;
      j++;
      c = getc ( fileid );
    }
    if ( j == MAX_WWW_DEMO_NAME ) {
      printf ( "\n  Direcrory name %s too long\n", demo_directory [ i ] );
      i--;
    }
    else {
      demo_directory [ i ] [ j ] = '\0';
      strcpy ( bpda, "WWW_DEMOS/" );
      strcat ( bpda, demo_directory [ i ] );
      strcat ( bpda, "/.Bpda" );
      Bpda = fopen ( bpda, "r" );
      if ( Bpda != NULL ) {
        fclose ( Bpda );
        strcpy ( bpda, "WWW_DEMOS/" );
        strcat ( bpda, demo_directory [ i ] );
        strcat ( bpda, "/.Bpda_0" );
        Bpda = fopen ( bpda, "r" );
        if ( Bpda != NULL ) {
          fclose ( Bpda );
        }
        else {
          i--;
        }
      }
      else {
        i--; 
      }
    }
    
    i++;
    while ( c == '\n' ||  c == ' ' ) {
      c = getc ( fileid );
    }
  }

  fclose ( fileid );

  if ( i == MAX_WWW_DEMO ) {
    printf ( "\n  Too many directories\n " );
  }

  tot_www_dirs = i;
}

int
main(argc, argv)
int argc;
char *argv[];
{
  Widget top_level, label, but, form, row_col;
  XmString xstr;
  int i;
  Pixel Ivory, gray90, LightSkyBlue1, LightSkyBlue4, firebrick3;


  bkit = getenv ( "BKIT" );
  if ( bkit  ==  NULL ) {
    printf ( "\n\n  Environment variable BKIT not set\n\n" );
    exit ( 1 );
  }

  XtSetLanguageProc ( NULL, NULL, NULL );

  XtToolkitInitialize ();

  app = XtCreateApplicationContext ();

  display = XtOpenDisplay ( app, NULL, argv[0], "WWWDialog",
                           NULL, 0, &argc, argv );

  top_level = XtAppCreateShell ( argv[0], "WWWDialog",
               applicationShellWidgetClass,
               display,
               NULL, 0 );

  XtVaSetValues ( top_level,
      XmNx,                              250,
      XmNx,                              250,
      NULL );

  gray90 = GetPixel ( "gray90" );
  Ivory = GetPixel ( "Ivory" );
  firebrick3 = GetPixel ( "firebrick3" );
  LightSkyBlue1 = GetPixel ( "LightSkyBlue1" );
  LightSkyBlue4 = GetPixel ( "LightSkyBlue4" );

  form = XtVaCreateManagedWidget ( "WWWDialog",
      xmFormWidgetClass,                 top_level,
      XmNx,                              250,
      XmNy,                              250,
      XmNbackground,                     Ivory,
      XmNborderWidth,                    0,
      NULL );

  xstr = XmStringCreateLtoR ( "Select B-Toolkit WWW Demonstration", charset );
  label = XtVaCreateManagedWidget ( "WWWDialog",
      xmLabelGadgetClass,                form,
      XmNtopAttachment,                  XmATTACH_FORM,
      XmNtopOffset,                      10,
      XmNleftAttachment,                 XmATTACH_FORM,
      XmNleftOffset,                     15,
      XmNrightAttachment,                XmATTACH_FORM,
      XmNrightOffset,                    15,
      XmNlabelString,                    xstr,
      XmNborderWidth,                    0,
      XmNmarginHeight,                   5,
      XmNmarginWidth,                    5,
      XmNforeground,                     firebrick3,
      XmNbackground,                     Ivory,
      NULL);
  XmStringFree ( xstr );

  row_col = XtVaCreateManagedWidget ( "WWWDialog",
      xmRowColumnWidgetClass,            form,
      XmNtopAttachment,                  XmATTACH_WIDGET,
      XmNtopWidget,                      label,
      XmNtopOffset,                      15,
      XmNbottomAttachment,               XmATTACH_FORM,
      XmNbottomOffset,                   25,
      XmNleftAttachment,                 XmATTACH_FORM,
      XmNleftOffset,                     50,
      XmNrightAttachment,                XmATTACH_FORM,
      XmNrightOffset,                    50,
      XmNspacing,                        10,
      XmNbackground,                     Ivory,
      XmNborderWidth,                    0,
      NULL );

  get_demo_directories ();

  for ( i = 0 ; i < tot_www_dirs ; i++ ) {
    char buf [ 250 ];
    int j, k;
    c_arr [ i ] = i;
    strcpy ( buf, "Demonstration " );
    j = 0;
    while ( demo_directory [ i ] [ j ] != '_' ) {
      j++;
    }
    j++;
    while ( demo_directory [ i ] [ j ] != '_' ) {
      j++;
    }
    j++;
    while ( demo_directory [ i ] [ j ] != '_' ) {
      j++;
    }
    j++;
    if ( demo_directory [ i ] [ j - 3 ] != '0' ) {
      buf [ 14 ] = demo_directory [ i ] [ j - 3 ];
      buf [ 15 ] = demo_directory [ i ] [ j - 2 ];
      buf [ 16 ] = ':';
      buf [ 17 ] = ' ';
      k = 18;
    }
    else {
      buf [ 14 ] = demo_directory [ i ] [ j - 2 ];
      buf [ 15 ] = ':';
      buf [ 16 ] = ' ';
      k = 17;
    }
    while ( demo_directory [ i ] [ j - 3 ] != '\0' ) {
      buf [ k ] = demo_directory [ i ] [ j ];
      j++;
      k++;
    }
    buf [ k ] = '\0';
    xstr = XmStringCreateLtoR ( buf, charset );
    but = XtVaCreateManagedWidget ( "WWWDialog",
        xmPushButtonWidgetClass,           row_col,
        XmNlabelString,                    xstr,
        XmNhighlightThickness,             0,
        XmNborderWidth,                    0,
        XmNmarginHeight,                   5,
        XmNmarginWidth,                    10,
        XmNbackground,                     LightSkyBlue1,
        XmNtopShadowColor,                 gray90,
        XmNbottomShadowColor,              LightSkyBlue4,
        XmNbackground,                     LightSkyBlue1,
        NULL);
    XtAddCallback ( but, XmNactivateCallback,
                           ( XtCallbackProc ) pushed,
                           ( XtPointer ) & c_arr [ i ] );
    XmStringFree ( xstr );
  }

  XtManageChild ( row_col );
  XtRealizeWidget ( top_level );
  XtAppMainLoop ( app );

  return 0;
}
