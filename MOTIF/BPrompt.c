/* Copyright (c) 1985-97, B-Core (UK) Ltd
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
#include <Xm/XmAll.h>

#include <stdio.h>
#include <stdlib.h>

String fallbacks[] = {
  "ErrorBox*fontList: -*-new century schoolbook-bold-r-*--12-*=TAG1",
  "ErrorBox*Dismiss.mnemonic: D",
  "ErrorBox*dialogTitle: B-Toolkit",
  "ErrorBox*traversalOn: true",
  "ErrorBox*highlightThickness: 0",
  "ErrorBox*borderWidth: 0",
  "ErrorBox*foreground: red",
  "ErrorBox*background: gray75",
  "ErrorBox*geometry: +400+150",
  NULL
};
Display *       display;
XtAppContext  app;
Position nx, ny;


#define max_num_fld 250
#define max_num_enm 100


int dd [ max_num_fld ];
int is_error_box;
int is_num [ max_num_fld ], is_str [ max_num_fld ], is_chr [ max_num_fld ], is_bts [ max_num_fld ], is_enm [ max_num_fld ];
Pixmap B_framed_pixmap_gray94, B_topbar_pixmap, applicable_edited_pixmap, applicable_unedited_pixmap, inapplicable_pixmap;
Widget        top_level, dialog, dialog_form, sep,
              ok_form, ok, label, scroll,
              row_col, form, left_rc, right_rc;
Widget        text [ max_num_fld ];
int           height;
XmString      xstr;
XmStringCharSet charset = (XmStringCharSet) XmSTRING_DEFAULT_CHARSET;
char          cur_buf [ 500 ];
char          buf [ 500 + ( max_num_fld * 250 ) ];
int i, j, k;
int c_arr [ 101 ];
char Enum_Name  [ max_num_fld ] [ 100 ];
char Enum_Elem  [ max_num_fld ] [ max_num_enm ] [ 100 ];
int enum_i  [ max_num_fld ];
Widget menu [ max_num_fld ];

int tot_fld, cur_fld;

int is_error;

void
AppNumToBuf ( buf, n )
char * buf;
int n;
{
  sprintf(buf, "%d", n);
}

void
Cre_Framed_B_logo_Pixmap ()
{
  FILE * Bxpm;

  B_framed_pixmap_gray94 = XmGetPixmap ( XtScreen ( top_level ), "../../B.xpm",
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( B_framed_pixmap_gray94 != XmUNSPECIFIED_PIXMAP ) return;

  B_framed_pixmap_gray94 = XmGetPixmap ( XtScreen ( top_level ), "B.xpm",
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( B_framed_pixmap_gray94 != XmUNSPECIFIED_PIXMAP ) return;

  Bxpm = fopen ( "B.xpm", "w" );
  if ( Bxpm == NULL ) {
    printf ( "\n  BPrompt: can't open B.xpm for writing\n" );
    exit ( 1 );
    return;
  }
  fprintf ( Bxpm, "/" );
  fprintf ( Bxpm, "* XPM *" );
  fprintf ( Bxpm, "/\n" );
  fprintf ( Bxpm, "static char * B_pxm[] = {\n" );
  fprintf ( Bxpm, "\"32 28 5 1\",\n" );
  fprintf ( Bxpm, "\"   c black\",\n" );
  fprintf ( Bxpm, "\".	c gray94\",\n" );
  fprintf ( Bxpm, "\"X	c white\",\n" );
  fprintf ( Bxpm, "\"o	c #d1b499\",\n" );
  fprintf ( Bxpm, "\"O	c #6dacff\",\n" );
  fprintf ( Bxpm, "\"                                \",\n" );
  fprintf ( Bxpm, "\" .XXXXXXXXXXXXXXXXXXXXXXXXXXXXX \",\n" );
  fprintf ( Bxpm, "\" .X                 ........... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOO .......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOO ......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOO ......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOO .......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo            ........... \",\n" );
  fprintf ( Bxpm, "\" .X oooo ...................... \",\n" );
  fprintf ( Bxpm, "\" .X oooo ...................... \",\n" );
  fprintf ( Bxpm, "\" .X oooo            ........... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOO .......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOO ......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOO ......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOO .......... \",\n" );
  fprintf ( Bxpm, "\" .X                 ........... \",\n" );
  fprintf ( Bxpm, "\" .XXXXXXXXXXXXXXXXXXXXXXXXXXXXX \",\n" );
  fprintf ( Bxpm, "\"                                \"};\n" );
  fclose ( Bxpm );
  B_framed_pixmap_gray94 = XmGetPixmap ( XtScreen ( top_level ), "B.xpm",
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( B_framed_pixmap_gray94 == XmUNSPECIFIED_PIXMAP ) {
    printf("\n  Warning - can't create %s pixmap\n\n", "B.xpm" );
  }
}

void
cre_B_logo ( parent, t_off, r_off )
Widget parent;
int t_off;
int r_off;
{
  Widget B_logo;
  Cre_Framed_B_logo_Pixmap ();
  B_logo =  XtVaCreateManagedWidget ( "ItfDialog",
      xmLabelGadgetClass,             parent,
      XmNlabelType,                   XmPIXMAP,
      XmNlabelPixmap,                 B_framed_pixmap_gray94,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   t_off,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 r_off,
      XmNshadowType,                  XmSHADOW_ETCHED_IN,
      XmNshadowThickness,             0,
      XmNmarginWidth,                 0,
      XmNmarginHeight,                0,
      NULL );
}

Widget
cre_dialog_form ( class, parent )
char * class;
Widget parent;
{
  Widget dialog_form = XtVaCreateWidget ( class,
      xmFormWidgetClass,         parent,
      XmNdefaultPosition,        False,  
      XmNtraversalOn,            True,
      NULL);
  return ( dialog_form );
}

Widget
cre_sep  ( class, parent )
char * class;
Widget parent;
{
  Widget sep = XtVaCreateManagedWidget ( class,
      xmSeparatorGadgetClass,  parent,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         48,
      NULL);
  return ( sep );
}

Widget
cre_ok_form ( class, parent, top_w )
char * class;
Widget parent;
Widget top_w;
{
  Widget ok_form = XtVaCreateWidget ( class,
      xmFormWidgetClass,       parent,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNtopAttachment,        XmATTACH_WIDGET,
      XmNtopWidget,            top_w,
      XmNtopOffset,            5,
      NULL );
  return ( ok_form );
}

Widget
cre_ok ( parent )
Widget parent;
{
  Widget ok = XtVaCreateManagedWidget ( "OK", 
      xmPushButtonGadgetClass, parent,
      XmNtraversalOn,          True,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           12,
      XmNheight,               25,
      XmNwidth,                57,
      XmNshowAsDefault,        True,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   0,
      NULL );
  return ( ok );
}

Widget
cre_label ( class, parent, buffer, l_off )
char * class;
Widget parent;
char * buffer;
int l_off;
{
  Widget label;
  xstr = XmStringCreateLtoR ( buffer , charset );
  label = XtVaCreateWidget ( class, 
      xmLabelGadgetClass,        parent,
      XmNlabelString,            xstr,
      XmNtopAttachment,          XmATTACH_FORM,
      XmNtopOffset,              10,
      XmNleftAttachment,         XmATTACH_FORM,
      XmNleftOffset,             l_off,
      NULL);
  XmStringFree ( xstr );
  return ( label );
}

Widget
cre_left_rc ( class, parent )
char * class;
Widget parent;
{
  Widget rc = XtVaCreateManagedWidget ( class,
      xmRowColumnWidgetClass,         parent,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   7,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_POSITION,
      XmNrightPosition,               1,
      XmNrightOffset,                 3,
      XmNisAligned,                   True,
      XmNentryAlignment,              XmALIGNMENT_END,
      XmNspacing,                     10,
      NULL );
  return ( rc );
}

Widget
cre_right_rc ( class, parent )
char * class;
Widget parent;
{
  Widget rc = XtVaCreateManagedWidget ( class,
      xmRowColumnWidgetClass,         parent,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_POSITION,
      XmNleftPosition,                1,
      XmNnavigationType,              XmTAB_GROUP,
      XmNisHomogeneous,               False,
      XmNspacing,                     0,
      NULL );
  return ( rc );
}

Widget
cre_form ( class, parent, bottom_w )
char * class;
Widget parent;
Widget bottom_w;
{
  Widget form = XtVaCreateWidget ( class,
      xmFormWidgetClass,              parent,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   40,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                bottom_w,
      XmNbottomOffset,                10,
      XmNfractionBase,                2,
      NULL );
  return ( form );
}

Widget
cre_inplab ( class, parent )
char * class;
Widget parent;
{
  Widget ptlab = XtVaCreateManagedWidget ( class,
      xmLabelGadgetClass,             parent,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_POSITION,
      XmNrightPosition,               1,
      XmNrightOffset,                 3,
      XmNalignment,                   XmALIGNMENT_END,
      NULL );
  return ( ptlab );
}

void
cre_enumCB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  int found = 0;
  i = 0;
  while ( ! found && i < max_num_fld ) {
    if ( XtParent ( widget ) == menu [ i ] ) found = 1;
    if ( ! found ) i++;
  }
  enum_i [ i ] = * ( int * ) client_data;
}

Widget
cre_enum ( field_num, class, parent, enum_set, enum_list, tot )
int field_num;
char * class;
Widget parent;
char * enum_set;
char * enum_list [];
int tot;
{
  Widget pull_down, widget;
  Arg args [ 5 ];
  int n = 0;
  menu [ field_num ] = XmCreatePulldownMenu ( parent, "InputText", NULL, 0);
  xstr = XmStringCreateLtoR ( "", charset );
  XtSetArg ( args [ n ], XmNsubMenuId, menu [ field_num ] ); n++;
  XtSetArg ( args [ n ], XmNlabelString, xstr ); n++;
  pull_down = XmCreateOptionMenu ( parent, "", args, n );
  XtVaSetValues ( pull_down,
      XmNtraversalOn,                 True,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_POSITION,
      XmNleftPosition,                1,
      XmNalignment,                   XmALIGNMENT_END,
      NULL );
  XmStringFree ( xstr );
  for ( i = 0 ; i < tot ; i++ ) {
    widget =
       XtVaCreateManagedWidget ( Enum_Elem [ field_num ] [ i ], 
           xmPushButtonGadgetClass,  menu [ field_num ],
           NULL );
    XtAddCallback ( widget, XmNactivateCallback,
             ( XtCallbackProc ) cre_enumCB,
             ( XtPointer ) & c_arr [ i ] );
  }

  return ( pull_down );
}

void
Popup_Dialog_Text_CB ( text_w, client_d )
Widget text_w;
XtPointer client_d;
{
  XmProcessTraversal ( text_w, XmTRAVERSE_NEXT_TAB_GROUP );
}

Widget
cre_text ( class1, class2, parent )
char * class1;
char * class2;
Widget parent;
{
  Widget text_form = XtVaCreateManagedWidget ( class1,
      xmFormWidgetClass,              parent,
      XmNtraversalOn,                 True,
      NULL );
  Widget text = XtVaCreateManagedWidget ( class2,
      xmTextFieldWidgetClass,         text_form,
      XmNtraversalOn,                 True,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNtopOffset,                   5,
      NULL );
  XtAddCallback ( text, XmNactivateCallback, 
          ( XtCallbackProc ) Popup_Dialog_Text_CB,
          NULL );
  return ( text );
}

void
write_Bcom_and_exit ()
{
  FILE * Bcom;
  XtVaGetValues ( dialog, XmNx, &nx,  XmNy, &ny, NULL );
  XtUnmanageChild ( dialog );
  XmUpdateDisplay ( dialog );
  Bcom = fopen ( ".Bcom", "w" );
  if ( Bcom == NULL ) {
    printf ( "\n\n     BPrompt: Can't open .bcom for writing\n\n" );
    exit ( 1 );
  }
  fprintf ( Bcom, "%s%c%d%c%d%c", buf, ( char ) 17, nx, ( char ) 17, ny, ( char ) 17 );
  fclose ( Bcom );
  exit ( 0 );
}

void
inform_error ( msg1, msg2 )
char * msg1;
char * msg2;
{
  strcpy ( buf, "$BKIT/BLIB/ErrorBox \"        " );
  strcat ( buf, msg1 );
  strcat ( buf, msg2 );
  strcat ( buf, "        \"" );
  system ( buf );
  is_error = 1;
}

void
Popup_CB ( dialog, client_data )
Widget dialog;
XtPointer client_data;
{
  char * text_string;
  unsigned j;

  is_error = 0;
  buf [ 0 ] = '\0';
  cur_fld = 0;

  while ( cur_fld < tot_fld && ! is_error ) {

    if ( is_enm [ cur_fld ] ) {
      if ( strcmp ( Enum_Name [ cur_fld ], "_BOOL" ) == 0 ) {
        if  ( enum_i [ cur_fld ] ) strcat ( buf, "1" );
        else                          strcat ( buf, "0" );
      }
      else {
        AppNumToBuf ( buf, enum_i [ cur_fld ] + 1 );
      }
    }

    else {   /* ! is_enm [ cur_fld ] */

      cur_buf [ 0 ] = '\0';

      text_string = XmTextFieldGetString ( text [ cur_fld ] );
      if ( ! strlen ( text_string ) ) {
        XtFree ( text_string );
        inform_error ( "", "Empty input!" );
      }
      else if ( strlen ( text_string ) > 248 ) {
        XtFree ( text_string );
        inform_error ( "", "Input too long (max 250)!" );
      }
      else {    /* text ok */
        strcpy ( cur_buf, text_string );
        XtFree ( text_string );

        if ( is_num [ cur_fld ] ) {
          int is_num_error = 0;
          int slen = strlen ( cur_buf );
          if ( slen > 10 ) {
            is_num_error = 1;
          }
          else {
            i = 0;
            j = 0;
            while ( ! is_num_error && i < slen ) {
              if ( cur_buf [ i ] < '0' || cur_buf [ i ] > '9' )
                is_num_error = 1;
              else
                j = ( 10 * j ) + cur_buf [ i ] - '0';
              i++;
            }
          }
          if ( is_num_error ) {
            if ( ! is_error )
              inform_error ( cur_buf, " - not a natural number!" );
          }
          else if ( j > dd [ cur_fld ] ) {
            char ss [ 250 ];
            strcpy ( ss, " - not in range 0.." );
            AppNumToBuf ( ss, dd [ cur_fld ] );
            if ( ! is_error )
              inform_error ( cur_buf, ss );
          }
          else {
            strcat ( buf, cur_buf );
	  }
        }

        else if ( is_chr [ cur_fld ] ) {
          int slen = strlen ( cur_buf );
          if ( slen != 1                       ||
               cur_buf [ 0 ] < ( char ) 32  ||
               cur_buf [ 0 ] > ( char ) 126    ) {
            if ( ! is_error )
              inform_error ( cur_buf, " - not a (single) character!" );
	  }
          else {
            strcat ( buf, cur_buf );
	  }
        }

        else if ( is_bts [ cur_fld ] ) {
          int is_bts_error = 0;
          int slen = strlen ( cur_buf );
          if ( slen > 32 ) {
            is_bts_error = 1;
          }
          else {
            i = 0;
            j = 0;
            while ( ! is_bts_error && i < slen ) {
              if ( cur_buf [ i ] != '0' && cur_buf [ i ] != '1' )
                is_bts_error = 2;
              else
                j = ( 10 * j ) + cur_buf [ i ] - '0';
              i++;
            }
          }
          if ( is_bts_error ) {
            if ( ! is_error ) {
              if ( is_bts_error == 2 )
                inform_error ( cur_buf, " - not a bit string (0/1's)!" );
              else
                inform_error ( cur_buf, " - Bit string too large (max 32)!" );
	    }
	  }
          else if ( j > 2147483646 ) {
            if ( ! is_error )
              inform_error ( cur_buf, " - Bit string too large (max 32)!" );
	  }
          else {
            strcat ( buf, cur_buf );
	  }
        }
        else if ( is_str [ cur_fld ] ) {
          strcat ( buf, cur_buf );
        }
      }

    }

    if ( ! is_error ) {
      cur_fld++;
      if ( cur_fld != tot_fld ) {
        int slen = strlen ( buf );
        buf [ slen ] = ( char ) 17;
        buf [ slen + 1 ] = '\0';
      }
    }
  }          /* while ( cur_fld < tot_fld && ! is_error ) */
  
  if ( ! is_error ) write_Bcom_and_exit ();
}

void
exit_invocation ( n )
int n;
{
  printf ( "\n\n      BPrompt invocation error (%d)\n\n", n );
  exit ( n );
}

void
OK_CB( w )
Widget w;
{
  exit ( 0 );
}

int
main(argc,argv)
int argc;
char *argv[];
/*
                   1  2         3          4     5
                                6          7     8  ... 
  invoke: BPrompt sss (replaces ErrorBox)
    is_error_box

 or

  invoke: BPrompt xx yy [ "Prompt string" nn enum_str/0 ] ~
    nn = 1 => is_num
    nn = 2 => is_str
    nn = 3 => is_chr
    nn = 4 => is_bts
    nn = 5 => is_enm
*/
{
  int i;

/***
  {
    printf ( "BPrompt\n" );
    for ( i = 1 ; i < argc ; i++ ) {
    printf ( "  arg %d: %s\n", i, argv [ i ] );
  }
}
***/

  if ( argc == 2 ) {

    is_error_box = 1;

  }

  else {

    is_error_box = 0;

    if ( argc < 6 || argc > ( max_num_fld * 3 ) + 2 ) exit_invocation ( argc );

    if ( argc != ( ( argc / 3 ) * 3 ) )  exit_invocation ( argc );

    tot_fld = ( argc - 3 ) / 3;

    for ( i = 0 ; i < tot_fld ; i++ ) {
      is_num [ i ] = 0;
      is_str [ i ] = 0;
      is_chr [ i ] = 0;
      is_bts [ i ] = 0;
      is_enm [ i ] = 0;
     enum_i [ i ] = 0;
    }

    nx = 0;
    i = 0;
    while ( argv [ 1 ] [ i ] != '\0' ) {
      nx = ( nx * 10 ) + argv [ 1 ] [ i ] - '0';
      i++;
    }

    ny = 0;
    i = 0;
    while ( argv [ 2 ] [ i ] != '\0' ) {
      ny = ( ny * 10 ) + argv [ 2 ] [ i ] - '0';
      i++;
    }

    cur_fld = 0;
    while ( cur_fld < tot_fld ) {

      if      ( strcmp ( argv [ 4 + ( 3 * cur_fld ) ], "1" ) == 0 ) is_num [ cur_fld ] = 1;
      else if ( strcmp ( argv [ 4 + ( 3 * cur_fld ) ], "2" ) == 0 ) is_str [ cur_fld ] = 1;
      else if ( strcmp ( argv [ 4 + ( 3 * cur_fld ) ], "3" ) == 0 ) is_chr [ cur_fld ] = 1;
      else if ( strcmp ( argv [ 4 + ( 3 * cur_fld ) ], "4" ) == 0 ) is_bts [ cur_fld ] = 1;
      else if ( strcmp ( argv [ 4 + ( 3 * cur_fld ) ], "5" ) == 0 ) is_enm [ cur_fld ] = 1;
      else                                                          exit_invocation ( 666 );

      if ( is_num [ cur_fld ] ) {
        for ( i = 0 ; i < 101 ; i++ ) c_arr [ i ] = i;
        dd [ cur_fld ] = 0;
        i = 0;
        while ( argv [ 5 + ( 3 * cur_fld ) ] [ i ] != '\0' ) {
          dd [ cur_fld ] = ( dd [ cur_fld ] * 10 ) + argv [ 5 + ( 3 * cur_fld ) ] [ i ] - '0';
          i++;
        }
      }

      else if ( is_enm [ cur_fld ] ) {
        for ( i = 0 ; i < 101 ; i++ ) c_arr [ i ] = i;
        i = 0;
        while ( argv [ 5 + ( 3 * cur_fld ) ] [ i ] != '(' ) {
          Enum_Name [ cur_fld ] [ i ] = argv [ 5 + ( 3 * cur_fld ) ] [ i ];
          i++;
        }
        Enum_Name [ cur_fld ] [ i ] = '\0';
        i++;
        j = 0;
        while ( argv [ 5 + ( 3 * cur_fld ) ] [ i ] != ')' ) {
          k = 0;
          while ( argv [ 5 + ( 3 * cur_fld ) ] [ i ] != ',' && argv [ 5 + ( 3 * cur_fld ) ] [ i ] != ')' ) {
            Enum_Elem [ cur_fld ] [ j ] [ k ] = argv [ 5 + ( 3 * cur_fld ) ] [ i ];
            i++;
            k++;
          }
          Enum_Elem [ cur_fld ] [ j ] [ k ] = '\0';
          j++;
          if ( argv [ 5 + ( 3 * cur_fld ) ] [ i ] != ')' ) i++;
        }
      }

      cur_fld++;
    }

  }

  XtSetLanguageProc ( NULL, NULL, NULL );

  top_level = XtVaAppInitialize ( &app, "XBMotif", NULL, 0,
                   &argc, argv, fallbacks, NULL );

  display = XtDisplay ( top_level );

  dialog =  XmCreateDialogShell ( top_level, "ItfDialog", NULL, 0 );

  dialog_form = cre_dialog_form ( "ItfDialog", dialog ); 

  if ( is_error_box ) {

    XtVaSetValues ( dialog_form, XmNx, 400,  XmNy, 150, NULL );

    strcpy ( cur_buf, argv [ 1 ] );
    xstr = XmStringCreate ( cur_buf, "TAG1" );
    label = XtVaCreateManagedWidget ( "QuestionDialog",
          xmLabelGadgetClass,          dialog_form,
          XmNtopAttachment,            XmATTACH_FORM,
          XmNtopOffset,                10,
          XmNleftAttachment,           XmATTACH_FORM,
          XmNleftOffset,               30,
          XmNrightAttachment,          XmATTACH_FORM,
          XmNrightOffset,              30,
          XmNlabelString,              xstr,
          XmNmarginWidth,              5,
          XmNmarginHeight,             5,
          NULL);
    XmStringFree ( xstr );

    sep = XtVaCreateManagedWidget ( "ItfDialog", 
          xmSeparatorGadgetClass,      dialog_form,
          XmNtopAttachment,            XmATTACH_WIDGET,
          XmNtopWidget,                label,
          XmNtopOffset,                10,
          XmNleftAttachment,           XmATTACH_FORM,
          XmNrightAttachment,          XmATTACH_FORM,
          NULL );

    ok_form = cre_ok_form ( "ButtonLabel", dialog_form, sep );
    ok = cre_ok ( ok_form );
/*
    xstr = XmStringCreate ( "Dismiss", "TAG1" );
    button = XtVaCreateManagedWidget ( "Dismiss",
          xmPushButtonWidgetClass,     dialog_form,
          XmNtopAttachment,            XmATTACH_WIDGET,
          XmNtopWidget,                sep,
          XmNtopOffset,                5,
          XmNleftAttachment,           XmATTACH_FORM,
          XmNleftOffset,               10,
          XmNbottomAttachment,         XmATTACH_FORM,
          XmNbottomOffset,             5,
          XmNlabelString,              xstr,
          XmNheight,                   25,
          XmNwidth,                    60,
          XmNshowAsDefault,            True,
          XmNdefaultButtonShadowThickness,        1,
          NULL);
    XmStringFree ( xstr );
*/

    XtAddCallback( ok,
        XmNactivateCallback, ( XtCallbackProc ) OK_CB, NULL );

    XBell ( display, 10 );
    XBell ( display, 10 );
    XBell ( display, 10 );
    XBell ( display, 10 );

  }

  else {

    XtVaSetValues ( dialog_form, XmNx, nx,  XmNy, ny, NULL );
    sep = cre_sep ( "ItfDialog", dialog_form );
    ok_form = cre_ok_form ( "ButtonLabel", dialog_form, sep );
    ok = cre_ok ( ok_form );
    XtAddCallback ( ok, XmNactivateCallback,
            ( XtCallbackProc )  Popup_CB,
          ( XtPointer ) NULL );
    label = cre_label ( "OpName", dialog_form, "BPrompt", 10 );
    cre_B_logo ( dialog_form, 5, 10 );
    form = cre_form ( "ItfDialog", dialog_form, sep );
    left_rc = cre_left_rc ( "ItfDialog", form );
    right_rc = cre_right_rc ( "ItfDialog", form );

    cur_fld = 0;
    while ( cur_fld < tot_fld ) {

      cre_inplab ( argv [ 3 + ( 3 * cur_fld ) ], left_rc );
      if ( is_enm [ cur_fld ] ) {
        text [ cur_fld ] =
           cre_enum ( cur_fld, "InputText", right_rc, Enum_Name [ cur_fld ], Enum_Elem [ cur_fld ], j );
      }
      else {
        text [ cur_fld ] = cre_text ( "ItfDialog", "InputText", right_rc );
      }
      XtManageChild ( text [ cur_fld ] );
      cur_fld++;

    }

    XtManageChild ( right_rc );
    XtManageChild ( left_rc );
    XtManageChild ( form );
    XtManageChild ( label );

  }

  XtManageChild ( ok_form );
  XtManageChild ( dialog_form );
  XtRealizeWidget ( top_level );

  if ( is_error_box ) {
    XtPopup ( dialog, XtGrabNone );
/*
    XtPopup ( dialog, XtGrabExclusive );
    XtGrabPointer ( ok, True, 0, GrabModeAsync, GrabModeAsync,
                    None, None, CurrentTime );
*/
  } 
  else {
    XtPopup ( dialog, XtGrabNone );
  }

  XtAppMainLoop ( app );
}
