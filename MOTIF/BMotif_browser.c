/* Copyright (c) 1992-96, B-Core (UK) Ltd
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
#include "BMotif_globals.h"


void
SaveBrowse_CB ( prompt_dialog, client_data )
Widget prompt_dialog;
XtPointer client_data;
{
  XtUnmanageChild ( prompt_dialog );
  XmUpdateDisplay ( prompt_dialog );
  if ( * ( int * ) client_data == OK_BUTTON ) {
    system ( primary_string );
  }
}

void
SaveBrowse ( filename )
char * filename;
{
  size_t len;
  Widget dialog;
  XmString xstr = XmStringCreateLtoR ( "Resize the browse window first (if required) and,\nafter clicking on `OK', position the crosshair\ncursor in the browse window and click the mouse.", charset );

  /***
  create the command - remove the .eps file first
  ***/
  strcpy ( primary_string, "rm -f " );
  strcat ( primary_string, filename );
  len = strlen ( primary_string );
  primary_string [ len - 3 ] = '\0';
  strcat ( primary_string, "eps" );
  system ( primary_string );

  strcpy ( primary_string, "xwd -nobdrs -out " );
  strcat ( primary_string, filename );

  /***
  create the info dialog
  ***/
  dialog = XmCreateInformationDialog ( top_level, "SelDialog", NULL, 0 );
  XtVaSetValues ( dialog,
      XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
      XmNautoUnmanage,           False,
      XmNmessageString,          xstr,
      XmNmarginWidth,            10,
      XmNmarginHeight,           5,
      NULL );
  XmStringFree ( xstr );

  /***
  unmanage cancel & help buttons & change label
  ***/
  XtUnmanageChild ( XmMessageBoxGetChild ( dialog, XmDIALOG_HELP_BUTTON ) );

  /***
  add the callback
  ***/
  XtAddCallback ( dialog, XmNokCallback,
      ( XtCallbackProc ) SaveBrowse_CB, ( XtPointer ) & c_arr [ OK_BUTTON ] );
  XtAddCallback ( dialog, XmNokCallback,
      ( XtCallbackProc ) SaveBrowse_CB, ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );

  /***
  Prompt dialog ready
  ***/
  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}


void
init_htx_curr_obj ()
{
  int i;
  for ( i = 0; i < MAX_htx_curr_obj ; i++ ) {
    htx_curr_obj [ i ] = 0;
  }
  htx_curr_obj_ptr = 0;
  XtVaSetValues ( htx_prev_but, XmNsensitive, False, NULL );
}

void
dec_htx_curr_obj ()
{
  int cc;
  if ( htx_curr_obj_ptr != 0 ) {
    htx_curr_obj_ptr--;
  }
  if ( htx_curr_obj_ptr == 0 ) {
    XtVaSetValues ( htx_prev_but, XmNsensitive, False, NULL );
  } 
}

void
inc_htx_curr_obj ()
{
  if ( htx_curr_obj_ptr < MAX_htx_curr_obj - 1 ) {
    htx_curr_obj_ptr++;
  } 
  if ( htx_curr_obj_ptr != 0 ) {
    XtVaSetValues ( htx_prev_but, XmNsensitive, True, NULL );   
  }
}

void
htx_help_but_CB ( dialog, client_data )
Widget dialog;
XtPointer client_data;
{
  struct help_struct help_data;

/***
  help_data.text = "\
The specification and design overviews are presented in\n\
a layered vertical manner, with the lowest level imported\n\
constructs (in the case of design overviews) or included\n\
constructs (in the case of specification overviews) to the\n\
right; construct extensions are not displayed for the\n\
overviews for space reasons.\n\n\
Selecting any construct in an overview will result in a detailed\n\
browse on that construct, when the diagram is also displayed in\n\
vertical form, with seen/used constructs (if any) to the left of\n\
the browsed construct and included constructs (when browsing\n\
a specification) or imported constructs (when browsing a\n\
design) on the right.\n\n\
Selecting the browsed (highlighted) construct will then popup a\n\
selection comprising the abstractions/refinements of that\n\
construct (if any); subsequent selection will result in a browse\n\
on that construct; the selection also provides the facility to open\n\
the main construct for (hypertext) viewing.\n\n\
Selecting any of the other constructs will result in a browse\n\
on that construct.\n\n\
`Save' enables the browse to be saved for subsequent inclusion\n\
in a DOCUMENT.\n\n\
`Previous' restores the previous browse (where applicable).\n\n\
`Specification' provides an overview of the specification\n\
construction.\n\n\
`Design' provides an overview of the design.\n\n\
For more information see Top Bar Help for Overview.";

  help_data.type = DIALOG_HELP;
  help_data.width  = 420;
  help_data.height = 600;
***/

  help_data.text = "\
The specification and design overviews are presented in\n\
a layered vertical manner, with the lowest level imported\n\
constructs (in the case of design overviews) or included\n\
constructs (in the case of specification overviews) to the\n\
right; construct extensions are not displayed for the\n\
overviews for space reasons.\n\n\
Selecting any construct in an overview will result in a detailed\n\
browse on that construct, when the diagram is also displayed in\n\
vertical form, with seen/used constructs (if any) to the left of\n\
the browsed construct and included constructs (when browsing\n\
a specification) or imported constructs (when browsing a\n\
design) on the right.\n\n\
Selecting the browsed (highlighted) construct will then popup a\n\
selection comprising the abstractions/refinements of that\n\
construct (if any); subsequent selection will result in a browse\n\
on that construct; the selection also provides the facility to open\n\
the main construct for editing.\n\n\
Selecting any of the other constructs will result in a browse\n\
on that construct.\n\n\
`Previous' restores the previous browse (where applicable).\n\n\
`Specification' provides an overview of the specification\n\
construction.\n\n\
`Design' provides an overview of the design.\n\n\
For more information see Top Bar Help for Overview.";

  help_data.type = DIALOG_HELP;
  help_data.width  = 420;
  help_data.height = 550;


  Popup_Help_CB ( top_level, &help_data );
}

void
htx_prev_but_CB ()
{
  if ( htx_curr_obj [ htx_curr_obj_ptr ] ) {
    DestroyDisplayedBrowse ();
    dec_htx_curr_obj ();
    BuildCurrBrowse ( htx_curr_obj [ htx_curr_obj_ptr ] );
  }
  else {        /* should not reach here */
    Popup_Info ( "No previous page to browse  " );
  }
}

void
htx_spec_but_CB ()
{
  int nn;

  load_gset1_top_spec_nodes ();
  card_gset1( &nn );
  if ( ! nn ) {
    Popup_Info ( "No specifications to display   " );
  }
  else {
    DestroyDisplayedBrowse ();
    inc_htx_curr_obj ();
    GetTopSpecNode ( nn );
  }
}

void
htx_design_but_CB ()
{
  int nn;

  load_gset1_top_imp_nodes ();
  card_gset1( &nn );
  if ( ! nn ) {
    Popup_Info ( "No design to display   " );
  }
  else {
    DestroyDisplayedBrowse ();
    inc_htx_curr_obj ();
    GetTopImpNode ( nn );
  }
}

void
htx_done_but_CB ( dialog, client_data, call_data )
Widget dialog;
XtPointer client_data;
XtPointer call_data;
{
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;
/***
printf ( "cbs->reason=%d\n", cbs->reason );
***/
  XtVaGetValues ( htx_curr_form, XmNwidth,  &HtxDialog_x, NULL );
  XtVaGetValues ( htx_curr_form, XmNheight, &HtxDialog_y, NULL );
  DestroyDisplayedBrowse ();
  XtPopdown ( htx_dialog );
  XmUpdateDisplay ( htx_dialog );
  htx_dialog_is_up = 0;
/*
  if ( cbs->reason == XmCR_PROTOCOLS ) {
    XtDestroyWidget ( htx_dialog );
    Cre_HtxDialog ( top_level );
  }
*/
  ReDisplayCurrEnvFromBrowser ();
/***
printf ( "cbs->reason=%d\n", cbs->reason );
***/
}

/*
void
htx_save_but_CB ( dialog )
Widget dialog;
{
  FILE ? Bcom;
  char buf [ 500 ];
  int c, i;

  system ( "which xwd xpr > .Bcom" );
  Bcom = fopen ( ".Bcom", "r" );
  if ( Bcom == NULL ) {
    Popup_Err ( 0, "  Problem executing \"which xwd xpr > .Bcom\"" );
    return;
  }

  /???
  xwd
  ???/
  i = 0;
  c = getc ( Bcom );
  while ( c == ' ' || c == '\n' ) {
    c = getc ( Bcom );
  }
  while ( c != ' ' && c != '\n' && c != EOF ) {
    buf [ i ] = c;
    i++;
    c = getc ( Bcom );
  }
  if ( i < 3 ) {
    Popup_Err ( 0, "  Problem finding \"xwd\"/\"xpr\"" );
    fclose ( Bcom );
    return;
  }
  else {
    if ( ( buf [ i - 1 ] != 'd' ) ||
         ( buf [ i - 2 ] != 'w' ) ||
         ( buf [ i - 3 ] != 'x' )    ) {
      Popup_Err ( 0, "  Problem finding \"xwd\"/\"xpr\"" );
      fclose ( Bcom );
      return;
    }
  }

  /???
  xpr
  ???/
  while ( c == ' ' || c == '\n' ) {
    c = getc ( Bcom );
  }
  i = 0;
  while ( c != ' ' && c != '\n' && c != EOF ) {
    buf [ i ] = c;
    i++;
    c = getc ( Bcom );
  }
  if ( i < 3 ) {
    Popup_Err ( 0, "  Problem finding \"xwd\"/\"xpr\"" );
    fclose ( Bcom );
    return;
  }
  else {
    if ( ( buf [ i - 1 ] != 'r' ) ||
         ( buf [ i - 2 ] != 'p' ) ||
         ( buf [ i - 3 ] != 'x' )    ) {
      Popup_Err ( 0, "  Problem finding \"xwd\"/\"xpr\"" );
      fclose ( Bcom );
      return;
    }
  }

  fclose ( Bcom );
  Popup_SaveBrowseDialog ();
}
*/

void
Cre_HtxDialog ( parent )
Widget parent;

{
  Pixel bg;
  int i;
  static struct coord coord_data;

  static Atom WM_SAVE_YOURSELF;
  static Atom WM_DELETE_WINDOW;

  void SaveYourself ();

  htx_dialog = XtAppCreateShell ( toolkit_ver, "XBMotif",
               applicationShellWidgetClass,
               display,
               NULL, 0 );

  XtVaSetValues ( htx_dialog, XmNdefaultPosition, False, NULL );

  coord_data.x = 0;
  coord_data.y = 0;

  XtAddCallback ( htx_dialog, XmNpopupCallback,
      ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
      ( XtPointer ) & coord_data );

  WM_SAVE_YOURSELF = XmInternAtom ( display, "WM_SAVE_YOURSELF", False );
  XmAddWMProtocols ( htx_dialog, & WM_SAVE_YOURSELF, 1 );
  XmAddWMProtocolCallback ( htx_dialog, WM_SAVE_YOURSELF,
      ( XtCallbackProc ) SaveYourself,
      ( XtPointer )  & c_arr [ 0 ] );

  WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );
  XmAddWMProtocolCallback ( htx_dialog, WM_DELETE_WINDOW,
      ( XtCallbackProc ) SaveYourself,
      ( XtPointer ) & c_arr [ 1 ] );

  htx_curr_form = XtVaCreateWidget ( "Overview",
      xmFormWidgetClass,              htx_dialog,
      XmNdefaultPosition,             False,  
      XmNheight,                      500,
      XmNwidth,                       525,
      XmNautoUnmanage,                False,
      NULL );

  htx_label = XtVaCreateWidget ( "Label", 
      xmLabelGadgetClass,             htx_curr_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   14,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  75,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 75,
      XmNspacing,                     5,
      NULL );

  htx_B_logo = XtVaCreateWidget ( "SelDialog", 
      xmPushButtonWidgetClass,        htx_curr_form,
      XmNlabelType,                   XmPIXMAP,
      XmNlabelPixmap,                 B_framed_pixmap_gray94,
      XmNshadowThickness,             0,
      XmNmarginWidth,                 0,
      XmNmarginHeight,                0,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   7,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNtraversalOn,                 False,
      NULL );

  XtAddCallback ( htx_B_logo, XmNactivateCallback,
                                    ( XtCallbackProc ) B_info_CB, NULL );

  htx_frame = XtVaCreateWidget ( "Overview", 
      xmFrameWidgetClass,             htx_curr_form,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   htx_label,
      XmNtopOffset,                   17,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                65,
      XmNshadowType,                  XmSHADOW_ETCHED_IN,
      NULL );

  htx_form = XtVaCreateWidget ( "Frame", 
      xmFormWidgetClass,              htx_frame,
      XmNdefaultPosition,             False,  
      NULL );

  htx_scroll = XtVaCreateWidget ( "Canvas", 
      xmScrolledWindowWidgetClass,    htx_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   15,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                15,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  15,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 15,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNshadowThickness,             3,
      NULL );

  htx_scroll_form = XtVaCreateWidget ( "Canvas", 
      xmFormWidgetClass,              htx_scroll,
      XmNdefaultPosition,             False,
      NULL );

  XtVaGetValues ( htx_scroll_form, XmNbackground, &bg, NULL );

  htx_curr_form_lab = XtVaCreateManagedWidget ( "ButtonLabel",
      xmFormWidgetClass,              htx_curr_form,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   htx_frame,
      XmNtopOffset,                   10,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      NULL );

  htx_prev_but =  XtVaCreateManagedWidget ( "Previous",
      xmPushButtonGadgetClass,        htx_curr_form_lab,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                10,
      XmNleftAttachment,              XmATTACH_WIDGET,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  15,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNdefaultButtonShadowThickness,        1,
      NULL );
  XtAddCallback ( htx_prev_but, XmNactivateCallback,
      ( XtCallbackProc ) htx_prev_but_CB, NULL );

  htx_spec_but =  XtVaCreateManagedWidget ( "Specification",
      xmPushButtonGadgetClass,        htx_curr_form_lab,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                10,
      XmNleftAttachment,              XmATTACH_WIDGET,
      XmNleftWidget,                  htx_prev_but,
      XmNleftOffset,                  4,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNdefaultButtonShadowThickness,        1,
      NULL );
  XtAddCallback ( htx_spec_but, XmNactivateCallback,
      ( XtCallbackProc ) htx_spec_but_CB, ( XtPointer ) & c_arr [ 1 ] );

  htx_design_but =  XtVaCreateManagedWidget ( "Design",
      xmPushButtonGadgetClass,        htx_curr_form_lab,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                10,
      XmNleftAttachment,              XmATTACH_WIDGET,
      XmNleftWidget,                  htx_spec_but,
      XmNleftOffset,                  4,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNdefaultButtonShadowThickness,        1,
      NULL );
  XtAddCallback ( htx_design_but, XmNactivateCallback,
      ( XtCallbackProc ) htx_design_but_CB, ( XtPointer ) & c_arr [ 1 ] );

  htx_done_but =  XtVaCreateManagedWidget ( "Dismiss",
      xmPushButtonGadgetClass,        htx_curr_form_lab,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                10,
      XmNleftAttachment,              XmATTACH_WIDGET,
      XmNleftWidget,                  htx_design_but,
      XmNleftOffset,                  4,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNdefaultButtonShadowThickness,        1,
      NULL );
  XtAddCallback ( htx_done_but, XmNactivateCallback,
      ( XtCallbackProc ) htx_done_but_CB, ( XtPointer ) & c_arr [ 0 ] );

  htx_help_but =  XtVaCreateManagedWidget ( "Help",
      xmPushButtonGadgetClass,        htx_curr_form_lab,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                10,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 15,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNdefaultButtonShadowThickness,        1,
      NULL );
  XtAddCallback ( htx_help_but, XmNactivateCallback,
      ( XtCallbackProc ) htx_help_but_CB, ( XtPointer ) & c_arr [ 0 ] );

/***
  htx_pixmap_right =
    XCreatePixmapFromBitmapData ( XtDisplay ( htx_scroll_form ),
      RootWindowOfScreen ( XtScreen ( htx_scroll_form ) ),
      right_arr_bits, right_arr_width, right_arr_height,
      gray39, bg, DefaultDepthOfScreen ( XtScreen ( htx_scroll_form ) ) );

  htx_pixmap_left =
    XCreatePixmapFromBitmapData ( XtDisplay ( htx_scroll_form ),
      RootWindowOfScreen ( XtScreen ( htx_scroll_form ) ),
      left_arr_bits, left_arr_width, left_arr_height,
      gray39, bg, DefaultDepthOfScreen ( XtScreen ( htx_scroll_form ) ) );

  htx_pixmap_left_big =
    XCreatePixmapFromBitmapData ( XtDisplay ( htx_scroll_form ),
      RootWindowOfScreen ( XtScreen ( htx_scroll_form ) ),
      left_big_arr_bits, left_big_arr_width, left_big_arr_height,
      gray39, bg, DefaultDepthOfScreen ( XtScreen ( htx_scroll_form ) ) );
***/
}

void
DestroyDisplayedBrowse ()
{
  int i, j, r, c;

  XtUnmanageChild ( htx_scroll_form );

  if ( htx_curr_obj [ htx_curr_obj_ptr ] > 0 ) { /* not design/spec overview */

    XtDestroyWidget ( sees_htx_rc );
    XtDestroyWidget ( htx_down_arw );
    XtRemoveAllCallbacks ( curr_htx_but, XmNactivateCallback );
    XtDestroyWidget ( curr_htx );
    XtDestroyWidget ( htx_up_arw );
    XtDestroyWidget ( ipts_htx_rc );

    for ( j = 0; j <  sees_htx_a2c_Total ; j++ ) {
      for ( i = 0; i <  sees_htx_a2c_tot [ j ] ; i++ ) {
        XtRemoveAllCallbacks ( sees_htx_a2c [ j ] [ i ], XmNactivateCallback );
        XtDestroyWidget ( sees_htx_a2c [ j ] [ i ] );
        XtDestroyWidget ( sees_htx_a2c_frame [ j ] [ i ] );
        XtDestroyWidget ( sees_htx_rc_sub [ j ] );
      }
    }

    for ( j = 0; j <  ipts_htx_a2c_Total ; j++ ) {
      for ( i = 0; i <  ipts_htx_a2c_tot [ j ] ; i++ ) {
        XtRemoveAllCallbacks ( ipts_htx_a2c [ j ] [ i ], XmNactivateCallback );
        XtDestroyWidget ( ipts_htx_a2c [ j ] [ i ] );
        XtDestroyWidget ( ipts_htx_a2c_frame [ j ] [ i ] );
        XtDestroyWidget ( ipts_htx_rc_sub [ j ] );
      }
    }
  }

  else {                                /* design/spec overview */

    for ( i = tot_htx_blocks - 1 ; i >= 0 ; i-- ) {
      r = ( i / MAX_a2c_htx );
      c = ( i % MAX_a2c_htx );
      XtDestroyWidget ( ipts_htx_a2c [ r ] [ c ] );
      XtDestroyWidget ( ipts_htx_a2c_frame [ r ] [ c ] );
      if ( i != 0 ) {
        XtDestroyWidget ( left_big_arr_htx  [ r ] [ c ] );
      }
    }

    for ( i = 0 ; i < tot_htx_constructs ; i++ ) {
      r = ( i / MAX_a2c_htx );
      c = ( i % MAX_a2c_htx );
      XtRemoveAllCallbacks ( sees_htx_a2c [ r ] [ c ], XmNactivateCallback );
      XtDestroyWidget ( sees_htx_a2c [ r ] [ c ] );
      XtDestroyWidget ( sees_htx_a2c_frame [ r ] [ c ] );
    }
  }
}

void
PositionNonOverviewBrowse ()
{
  Dimension yys, yyd, yym, yyu, yyi;
  int offset, max_height;

  XtVaGetValues ( sees_htx_rc, XmNheight, &yys, NULL );
  XtVaGetValues ( htx_down_arw, XmNheight, &yyd, NULL );
  XtVaGetValues ( curr_htx, XmNheight, &yym, NULL );
  XtVaGetValues ( htx_up_arw, XmNheight, &yyu, NULL );
  XtVaGetValues ( ipts_htx_rc, XmNheight, &yyi, NULL );

  max_height = ( int ) yys;

  if ( ( int ) yyd > max_height ) {
    max_height = ( int ) yyd;
  }

  if ( ( int ) yym > max_height ) {
    max_height = ( int ) yym;
  }

  if ( ( int ) yyu > max_height ) {
    max_height = ( int ) yyu;
  }

  if ( ( int ) yyi > max_height ) {
    max_height = ( int ) yyi;
  }

  offset = ( ( max_height - yys ) / 2 ) + 10;
  if ( offset < 10 ) {
    offset = 10;
  }
  XtVaSetValues ( sees_htx_rc, XmNtopOffset, offset, NULL );

  offset = ( ( max_height - yyd ) / 2 ) + 10;
  if ( offset < 10 ) {
    offset = 10;
  }
  XtVaSetValues ( htx_down_arw, XmNtopOffset, offset, NULL );

  offset = ( ( max_height - yym ) / 2 ) + 10;
  if ( offset < 10 ) {
    offset = 10;
  }
  XtVaSetValues ( curr_htx, XmNtopOffset, offset, NULL );

  offset = ( ( max_height - yyu ) / 2 ) + 10;
  if ( offset < 10 ) {
    offset = 10;
  }
  XtVaSetValues ( htx_up_arw, XmNtopOffset, offset, NULL );

  offset = ( ( max_height - yyi ) / 2 ) + 10;
  if ( offset < 10 ) {
    offset = 10;
  }
  XtVaSetValues ( ipts_htx_rc, XmNtopOffset, offset, NULL );
}

void
Popup_HtxDialog ()
{
  /***
  curr_obj is set in Popup_Sel_Dialog_CB - case browse_selection (BMotif.c)
  ***/

  htx_curr_obj [ htx_curr_obj_ptr ] = curr_obj;
  cre_curr_sees_ipts_htx_rc ();
  cre_curr_sees_ipts_htx_a2c (  curr_obj );
  XtVaSetValues ( htx_done_but,   XmNsensitive, True, NULL );
  XtVaSetValues ( htx_prev_but,   XmNsensitive, False, NULL );
  XtVaSetValues ( htx_spec_but,   XmNsensitive, True, NULL );
  XtVaSetValues ( htx_design_but, XmNsensitive, True, NULL );
  XtManageChild ( sees_htx_rc );
  XtManageChild ( htx_down_arw );
  XtManageChild ( curr_htx );
  XtManageChild ( htx_up_arw );
  XtManageChild ( ipts_htx_rc );
  XtManageChild ( htx_scroll );
/***
  XtManageChild ( htx_scroll_form );
***/
  XtManageChild ( htx_label );
  XtManageChild ( htx_B_logo );
  XtManageChild ( htx_form );
  XtManageChild ( htx_frame );
  if ( HtxDialog_x ) {
    XtVaSetValues ( htx_curr_form, XmNwidth,  ( int ) HtxDialog_x, NULL );
    XtVaSetValues ( htx_curr_form, XmNheight, ( int ) HtxDialog_y, NULL );
  }
  XtManageChild ( htx_curr_form );
  XtPopup ( htx_dialog, XtGrabNone );
  XmUpdateDisplay ( htx_dialog );
  htx_dialog_is_up = 1;
  PositionNonOverviewBrowse ();
  XtManageChild ( htx_scroll_form );
}

/***
  builds from curr_obj_arr ( if < 0, an overview )
***/
void
BuildCurrBrowse ( cc )
int cc;
{
  int ext;
/***
printf ( "BuildCurrBrowse ( cc=%d )\n", cc );
***/
  if ( cc > 0 ) {          /* not overview */
    curr_obj = cc;
    cre_curr_sees_ipts_htx_rc ();
    cre_curr_sees_ipts_htx_a2c ( curr_obj );
    XtVaSetValues ( htx_done_but,   XmNsensitive, True, NULL );
    XtVaSetValues ( htx_spec_but,   XmNsensitive, True, NULL );
    XtVaSetValues ( htx_design_but, XmNsensitive, True, NULL );
    XtManageChild ( sees_htx_rc );
    XtManageChild ( htx_down_arw );
    XtManageChild ( curr_htx );
    XtManageChild ( htx_up_arw );
    XtManageChild ( ipts_htx_rc );
/***
    XtManageChild ( htx_scroll_form );
***/
    PositionNonOverviewBrowse ();
    XtManageChild ( htx_scroll_form );
  }
  else {                   /* overview */
    cc = ( -1 ) * cc;
    cc = curr_obj;
    val_ext ( & ext, cc );
    if ( ext == imp ) {
      Load_DarrFromImpNode ( cc );
    }
    else {
      Load_DarrFromSpecNode ( cc );
    }
    DisplayTopNode ();
  }
}

void
cre_curr_sees_ipts_htx_rc ()
{
  int nn, ext;

  sees_htx_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         htx_scroll_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   5,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNorientation,                 XmVERTICAL,
      XmNspacing,                     5,
      NULL );

  card_sees_uses ( &nn, curr_obj );
  if ( nn ) {
    htx_down_arw = XtVaCreateWidget ( "Canvas", 
        xmRowColumnWidgetClass,         htx_scroll_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNleftAttachment,              XmATTACH_WIDGET,
        XmNleftWidget,                  sees_htx_rc,
        XmNleftOffset,                  5,
        XmNorientation,                 XmVERTICAL,
        XmNspacing,                     0,
        NULL );

    XtVaCreateManagedWidget ( "Canvas",
        xmLabelGadgetClass,             htx_down_arw,
        XmNlabelType,                   XmPIXMAP,
        XmNlabelPixmap,                 htx_pixmap_right,
        NULL );

    XtVaCreateManagedWidget  ( " SEES/USES ",
        xmLabelGadgetClass,             htx_down_arw,
        XmNforeground,                  gray39,
        NULL );

    XtVaCreateManagedWidget ( "Canvas",
        xmLabelGadgetClass,             htx_down_arw,
        XmNlabelType,                   XmPIXMAP,
        XmNlabelPixmap,                 htx_pixmap_right,
        NULL );

  }
  else {
    htx_down_arw = XtVaCreateWidget ( "Canvas", 
        xmRowColumnWidgetClass,         htx_scroll_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  5,
        XmNorientation,                 XmVERTICAL,
        XmNspacing,                     0,
        NULL );

    XtVaCreateManagedWidget ( "     No",
        xmLabelGadgetClass,             htx_down_arw,
        NULL );

    XtVaCreateManagedWidget ( "Seen/Used",
        xmLabelGadgetClass,             htx_down_arw,
        NULL );

    XtVaCreateManagedWidget ( "Constructs",
        xmLabelGadgetClass,             htx_down_arw,
        NULL );

  }

  curr_htx = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         htx_scroll_form,
      XmNleftAttachment,              XmATTACH_WIDGET,
      XmNleftWidget,                  htx_down_arw,
      XmNleftOffset,                  5,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNorientation,                 XmVERTICAL,
      XmNspacing,                     1,
      NULL );


  val_ext ( &ext, curr_obj );

  card_inc_ipt ( &nn, curr_obj );

  if ( nn ) {

    htx_up_arw = XtVaCreateWidget ( "Canvas", 
        xmRowColumnWidgetClass,         htx_scroll_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNleftAttachment,              XmATTACH_WIDGET,
        XmNleftWidget,                  curr_htx,
        XmNleftOffset,                  5,
        XmNorientation,                 XmVERTICAL,
        XmNspacing,                     0,
        NULL );

    XtVaCreateManagedWidget ( "Canvas",
        xmLabelGadgetClass,             htx_up_arw,
        XmNlabelType,                   XmPIXMAP,
        XmNlabelPixmap,                 htx_pixmap_left,
        NULL );

    if ( ext == imp ) {
      XtVaCreateManagedWidget  ( " IMPORTS ",
          xmLabelGadgetClass,             htx_up_arw,
          XmNforeground,                  gray39,
          NULL );
    }
    else {
      XtVaCreateManagedWidget  ( " INCLUDES ",
          xmLabelGadgetClass,             htx_up_arw,
          XmNforeground,                  gray39,
          NULL );
    }

    XtVaCreateManagedWidget ( "Canvas",
        xmLabelGadgetClass,             htx_up_arw,
        XmNlabelType,                   XmPIXMAP,
        XmNlabelPixmap,                 htx_pixmap_left,
        NULL );
  }

  else {  /*** nn == 0 ***/
    if ( ext == imp ) {
     htx_up_arw = XtVaCreateWidget ( "Canvas", 
        xmRowColumnWidgetClass,         htx_scroll_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNleftAttachment,              XmATTACH_WIDGET,
        XmNleftWidget,                  curr_htx,
        XmNleftOffset,                  5,
        XmNorientation,                 XmVERTICAL,
        XmNspacing,                     0,
        NULL );

      XtVaCreateManagedWidget ( "     No",
          xmLabelGadgetClass,             htx_up_arw,
          NULL );

      XtVaCreateManagedWidget ( " Imported",
          xmLabelGadgetClass,             htx_up_arw,
          NULL );

      XtVaCreateManagedWidget ( "Constructs",
          xmLabelGadgetClass,             htx_up_arw,
          NULL );
    }
    else {
     htx_up_arw = XtVaCreateWidget ( "Canvas", 
        xmRowColumnWidgetClass,         htx_scroll_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNleftAttachment,              XmATTACH_WIDGET,
        XmNleftWidget,                  curr_htx,
        XmNleftOffset,                  5,
        XmNorientation,                 XmVERTICAL,
        XmNspacing,                     0,
        NULL );

      XtVaCreateManagedWidget ( "     No",
          xmLabelGadgetClass,             htx_up_arw,
          NULL );

      XtVaCreateManagedWidget ( " Included",
          xmLabelGadgetClass,             htx_up_arw,
          NULL );

      XtVaCreateManagedWidget ( "Constructs",
          xmLabelGadgetClass,             htx_up_arw,
          NULL );
    }

  }

  ipts_htx_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         htx_scroll_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_WIDGET,
      XmNleftWidget,                  htx_up_arw,
      XmNleftOffset,                  5,
      XmNorientation,                 XmVERTICAL,
      XmNspacing,                     5,
      NULL );
}

void
cre_curr_sees_ipts_htx_a2c ( cc )
int cc;
{
  int nn, cc1;
  char buf [ 200 ];
  XmString xstr;
  card_sees_uses ( &nn, cc );
  sees_htx_a2c_Total = 0;
  while ( sees_htx_a2c_Total < nn && sees_htx_a2c_Total < MAX_sees_htx ) {
    valOrd_sees_uses ( &cc1, cc, sees_htx_a2c_Total + 1 );
    sees_htx_rc_sub [ sees_htx_a2c_Total ] =
        XtVaCreateManagedWidget ( "Canvas", 
            xmFormWidgetClass,              sees_htx_rc,
            XmNdefaultPosition,             False,  
            NULL );
    cre_sees_htx_a2c ( cc1, sees_htx_a2c_Total );
    sees_htx_a2c_Total++;
  }

  cre_curr_htx_a2c ( cc );

  card_inc_ipt ( &nn, cc );
  ipts_htx_a2c_Total = 0;
  while ( ipts_htx_a2c_Total < nn && ipts_htx_a2c_Total < MAX_ipts_htx ) {
    valOrd_inc_ipt ( &cc1, cc, ipts_htx_a2c_Total + 1 );
    ipts_htx_rc_sub [ ipts_htx_a2c_Total ] =
        XtVaCreateManagedWidget ( "Canvas", 
            xmFormWidgetClass,              ipts_htx_rc,
            XmNdefaultPosition,             False,  
            NULL );
    cre_ipts_htx_a2c ( cc1, ipts_htx_a2c_Total );
    ipts_htx_a2c_Total++;
  }

  sprintf ( buf, "      %s: Browse for %s            " ,
                                                       toolkit_ver, GetName ( cc ) );
  xstr = XmStringCreateLtoR ( buf, charset );
  XtVaSetValues ( htx_label, XmNlabelString, xstr, NULL );
  XmUpdateDisplay ( htx_label );
  XmStringFree ( xstr );
}

void
curr_htx_a2c_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  int i;
  int cc = * ( int * ) client_data;

  /***
  popdown curr_htx_dialog
  ***/
  XtPopdown ( curr_htx_dialog );
  XmUpdateDisplay ( curr_htx_dialog );

  if ( cc ) {
    /***
    Not Cancel
    ***/
    if ( curr_obj != cc ) {
      /***
      New Object - rm CallBacks & destroy curr_htx_dialog
      ***/
      for ( i = 0 ; i <  curr_htx_a2c_tot ; i++ ) {
        XtRemoveAllCallbacks ( curr_htx_a2c [ i ], XmNactivateCallback );
        XtDestroyWidget ( curr_htx_a2c [ i ] );
        XtDestroyWidget ( curr_htx_a2c_frame [ i ] );
      }
      /***
      destroy Cancel button of curr_htx_dialog
      ***/
      XtRemoveAllCallbacks ( curr_htx_a2c [ curr_htx_a2c_tot ],
                                               XmNactivateCallback );
      XtDestroyWidget ( curr_htx_a2c [ curr_htx_a2c_tot ] );
      XtDestroyWidget ( curr_htx_rc );
      XtDestroyWidget ( curr_htx_form );
      XtDestroyWidget ( curr_htx_dialog );

      DestroyDisplayedBrowse ();
      inc_htx_curr_obj ();
      htx_curr_obj [ htx_curr_obj_ptr ] = cc;
      BuildCurrBrowse ( cc );
    }
    else {
    /***
    Open
    ***/
      int Hypertext_Text_Option;

      valIth_flags ( &Hypertext_Text_Option, Hypertext_text_num );
      Retrieve_String ( htx_viewer_str_num, buf );

      if ( Hypertext_Text_Option ) {
        Popup_Err ( 0, " Hypertext display set to text - check TopBar Options" );
      }
      else if ( strcmp ( buf, "" ) == 0 ) {
        Popup_Err ( 0, "Hypertext Viewer not set - check TopBar Options" );
      }
      else {
        sprintf ( secondary_string, "Launching %s for %s", buf, GetShortName ( curr_obj ) );
        sprintf ( primary_string, "%s HTX/%s.html &", buf, GetName ( curr_obj ) );
        execute ( primary_string );
        Popup_Info ( secondary_string );
      }
    }
  }

  /***
  Set buttons
  ***/
  XtVaSetValues ( htx_done_but,   XmNsensitive, True, NULL );
  XtVaSetValues ( htx_spec_but,   XmNsensitive, True, NULL );
  XtVaSetValues ( htx_design_but, XmNsensitive, True, NULL );
  if ( htx_curr_obj_ptr != 0 ) {
    XtVaSetValues ( htx_prev_but, XmNsensitive, True, NULL );   
  }
}

void
curr_htx_CB ()
{
  XtVaSetValues ( htx_done_but,   XmNsensitive, False, NULL );
  XtVaSetValues ( htx_prev_but,   XmNsensitive, False, NULL );
  XtVaSetValues ( htx_spec_but,   XmNsensitive, False, NULL );
  XtVaSetValues ( htx_design_but, XmNsensitive, False, NULL );
  XtManageChild ( curr_htx_rc );
  XtManageChild ( curr_htx_form );
  XtPopup ( curr_htx_dialog, XtGrabNone );
}

void
cre_curr_htx_a2c ( cc )
int cc;
{
  XmString xstr;
  int bb, ac, ll, cc1, border_width;
  char buf [ 200 ];
  int name [ 50 ], ext, type;
  val_mand   ( name, &ext, &type, cc );

  /***
  Build curr_htx_but with callback to popop curr_htx_dialog
  ***/
  curr_htx_frame = XtVaCreateManagedWidget ( "Canvas",
      xmFrameWidgetClass,             curr_htx,
      XmNmarginWidth,                 2,
      XmNmarginHeight,                2,
      XmNshadowType,                  XmSHADOW_ETCHED_IN,
      NULL );

  curr_htx_inner_frame = XtVaCreateManagedWidget ( "MainBox",
      xmFrameWidgetClass,             curr_htx_frame,
      XmNshadowType,                  XmSHADOW_ETCHED_IN,
      NULL );

  strcpy ( buf, GetName ( cc ) );
  xstr = XmStringCreateLtoR ( buf, charset );
  curr_htx_but = XtVaCreateManagedWidget ( lab_types [ type ], 
      xmPushButtonWidgetClass, curr_htx_inner_frame,
      XmNlabelString,                 xstr,
      XmNshadowThickness,             0,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      NULL );
  XmStringFree ( xstr );
  
  XtAddCallback ( curr_htx_but, XmNactivateCallback,
      ( XtCallbackProc ) curr_htx_CB, ( XtPointer ) & c_arr [ 0 ] );

  /***
  Build popup
  ***/
  curr_htx_dialog =  XmCreateDialogShell ( curr_htx_but,
      toolkit_ver, NULL, 0 );
  XtVaSetValues ( curr_htx_dialog,
      XmNdefaultPosition,        False,  
      XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
      NULL );

  curr_htx_form = XtVaCreateWidget ( "Canvas", 
      xmFormWidgetClass,              curr_htx_dialog,
      NULL );
  
  curr_htx_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         curr_htx_form,
      XmNorientation,                 XmVERTICAL,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNmarginWidth,                 10,
      XmNmarginHeight,                15,
      XmNspacing,                     5,
      NULL );
  
  curr_htx_a2c_tot = 0;
  def_abs2conc( &bb, cc );
  if ( bb ) {
    val_abs2conc( &ac, cc );
    length_a2c( &ll, ac );
    while ( curr_htx_a2c_tot < MAX_a2c_htx && curr_htx_a2c_tot < ll ) {
      valIth_a2c( &cc1, ac, curr_htx_a2c_tot + 1 );
      if ( cc == cc1 ) {
        curr_htx_a2c_open_idx = curr_htx_a2c_tot;
        strcpy ( buf, "View " );
      }
      else {
        strcpy ( buf, "" );
      }
      strcat( buf, GetName ( cc1 ) );
      xstr = XmStringCreateLtoR ( buf, charset );
      curr_htx_a2c_frame [ curr_htx_a2c_tot ] =
          XtVaCreateManagedWidget ( "Canvas",
              xmFrameWidgetClass,              curr_htx_rc,
              XmNshadowType,                   XmSHADOW_ETCHED_IN,
              NULL );
      curr_htx_a2c [ curr_htx_a2c_tot ] =
          XtVaCreateWidget ( lab_types [ type ], 
              xmPushButtonWidgetClass,
                  curr_htx_a2c_frame [ curr_htx_a2c_tot ],
              XmNlabelString,                  xstr,
              XmNshadowThickness,              0,
              XmNmarginWidth,                  5,
              XmNmarginHeight,                 5,
              NULL );
      if ( cc == cc1 ) {

	/*
        if  ( ! ( IsClosed (curr_obj ) ) ) {
          XtVaSetValues ( curr_htx_a2c [ curr_htx_a2c_tot ],
              XmNsensitive,                   False,
              XmNforeground,                  gray39,
              NULL );
	}
        else {
          XtVaSetValues ( curr_htx_a2c [ curr_htx_a2c_tot ],
              XmNforeground,                  gray39,
              NULL );
	}
	*/
        XtVaSetValues ( curr_htx_a2c [ curr_htx_a2c_tot ],
            XmNforeground,                  gray39,
            NULL );

      }
      XmStringFree ( xstr );
      XtAddCallback ( curr_htx_a2c [ curr_htx_a2c_tot ],
            XmNactivateCallback, ( XtCallbackProc ) curr_htx_a2c_CB,
                                             ( XtPointer ) & c_arr [ cc1 ] );
      XtManageChild ( curr_htx_a2c [ curr_htx_a2c_tot ] );
      curr_htx_a2c_tot++;
    }
  }

  /***
  Cancel (no frame)
  ***/
  curr_htx_a2c [ curr_htx_a2c_tot ] = XtVaCreateManagedWidget ( "Cancel",
      xmPushButtonWidgetClass,        curr_htx_form,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   curr_htx_a2c [ curr_htx_a2c_tot - 1 ],
      XmNtopOffset,                   10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                10,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNforeground,                  gray39,
      XmNdefaultButtonShadowThickness,        0,
      NULL );
  XtAddCallback ( curr_htx_a2c [ curr_htx_a2c_tot ],
        XmNactivateCallback, ( XtCallbackProc ) curr_htx_a2c_CB,
                                             ( XtPointer ) & c_arr [ 0 ] );
}

void
sees_htx_a2c_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  int cc = * ( int * ) client_data;

  DestroyDisplayedBrowse ();
  inc_htx_curr_obj ();
  htx_curr_obj [ htx_curr_obj_ptr ] = cc;
  BuildCurrBrowse ( cc );
}

void
cre_sees_htx_a2c ( cc, nn )
int cc;
int nn;
{
  XmString xstr;
  int bb, ac, ll, cc1, border_width;
  char buf [ 200 ];
  int name [ 50 ], ext, type;

  sees_htx_a2c_tot [ nn ] = 0;
  def_abs2conc( &bb, cc );
  if ( bb ) {
    val_abs2conc( &ac, cc );
    length_a2c( &ll, ac );
    while ( sees_htx_a2c_tot [ nn ] < MAX_a2c_htx &&
            sees_htx_a2c_tot [ nn ] < ll             ) {
      valIth_a2c( &cc1, ac, sees_htx_a2c_tot [ nn ] + 1 );
      val_mand   ( name, &ext, &type, cc1 );
      strcpy ( buf, GetName ( cc1 ) );
      xstr = XmStringCreateLtoR ( buf, charset );
      sees_htx_a2c_frame [ nn ] [ sees_htx_a2c_tot [ nn ] ] =
          XtVaCreateManagedWidget ( "Box",
              xmFrameWidgetClass,             sees_htx_rc_sub [ nn ] ,
              XmNrightAttachment,             XmATTACH_FORM,
              XmNrightOffset,                 ( 0 * sees_htx_a2c_tot [ nn ] ),
              XmNshadowType,                  XmSHADOW_ETCHED_IN,
              NULL );
      if ( sees_htx_a2c_tot [ nn ] ) {
        XtVaSetValues ( sees_htx_a2c_frame [ nn ] [ sees_htx_a2c_tot [ nn ] ],
            XmNtopAttachment,               XmATTACH_WIDGET,
            XmNtopWidget,
                sees_htx_a2c_frame [ nn ] [ sees_htx_a2c_tot [ nn ] - 1 ],
            XmNtopOffset,                   -7,
         NULL );
      }
      else {
        XtVaSetValues ( sees_htx_a2c_frame [ nn ] [ sees_htx_a2c_tot [ nn ] ],
            XmNtopAttachment,               XmATTACH_FORM,
            XmNtopOffset,                   0,
            NULL );
      }
      sees_htx_a2c [ nn ] [ sees_htx_a2c_tot [ nn ] ] =
          XtVaCreateWidget ( lab_types [ type ], 
              xmPushButtonWidgetClass,
                  sees_htx_a2c_frame [ nn ] [ sees_htx_a2c_tot [ nn ] ],
              XmNlabelString,                xstr,
              XmNshadowThickness,            0,
              XmNmarginWidth,                5,
              XmNmarginHeight,               5,
              XmNborderWidth,                0,
              NULL );
      XtManageChild ( sees_htx_a2c [ nn ] [ sees_htx_a2c_tot [ nn ] ] );
      XtAddCallback ( sees_htx_a2c [ nn ] [ sees_htx_a2c_tot [ nn ] ],
            XmNactivateCallback, ( XtCallbackProc ) sees_htx_a2c_CB, ( XtPointer ) & c_arr [ cc1 ] );
      XmStringFree ( xstr );
      sees_htx_a2c_tot [ nn ]++;
    }
  }  
}

void
ipts_htx_a2c_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  int cc = * ( int * ) client_data;

  DestroyDisplayedBrowse ();
  inc_htx_curr_obj ();
  htx_curr_obj [ htx_curr_obj_ptr ] = cc;
  BuildCurrBrowse ( cc );
}

void
cre_ipts_htx_a2c ( cc, nn )
int cc;
int nn;
{
  XmString xstr;
  int bb, ac, ll, cc1, border_width;
  char buf [ 200 ];
  int name [ 50 ], ext, type;

  ipts_htx_a2c_tot [ nn ] = 0;
  def_abs2conc( &bb, cc );
  if ( bb ) {
    val_abs2conc( &ac, cc );
    length_a2c( &ll, ac );
    while ( ipts_htx_a2c_tot [ nn ] < MAX_a2c_htx &&
            ipts_htx_a2c_tot [ nn ] < ll             ) {
      valIth_a2c( &cc1, ac, ipts_htx_a2c_tot [ nn ] + 1 );
      val_mand   ( name, &ext, &type, cc1 );
      strcpy ( buf, GetName ( cc1 ) );
      xstr = XmStringCreateLtoR ( buf, charset );
      ipts_htx_a2c_frame [ nn ] [ ipts_htx_a2c_tot [ nn ] ] =
          XtVaCreateManagedWidget ( "Box",
              xmFrameWidgetClass,             ipts_htx_rc_sub [ nn ] ,
              XmNleftAttachment,              XmATTACH_FORM,
              XmNleftOffset,                  ( 0 * ipts_htx_a2c_tot [ nn ] ),
              XmNshadowType,                  XmSHADOW_ETCHED_IN,
              NULL );
      if ( ipts_htx_a2c_tot [ nn ] ) {
        XtVaSetValues ( ipts_htx_a2c_frame [ nn ] [ ipts_htx_a2c_tot [ nn ] ],
            XmNtopAttachment,               XmATTACH_WIDGET,
            XmNtopWidget,
                ipts_htx_a2c_frame [ nn ] [ ipts_htx_a2c_tot [ nn ] - 1 ],
            XmNtopOffset,                   -7,
         NULL );
      }
      else {
        XtVaSetValues ( ipts_htx_a2c_frame [ nn ] [ ipts_htx_a2c_tot [ nn ] ],
            XmNtopAttachment,               XmATTACH_FORM,
            XmNtopOffset,                   0,
            NULL );
      }
      ipts_htx_a2c [ nn ] [ ipts_htx_a2c_tot [ nn ] ] =
          XtVaCreateWidget ( lab_types [ type ], 
              xmPushButtonWidgetClass,
                  ipts_htx_a2c_frame [ nn ] [ ipts_htx_a2c_tot [ nn ] ],
              XmNlabelString,                xstr,
              XmNshadowThickness,            0,
              XmNmarginWidth,                5,
              XmNmarginHeight,               5,
              XmNborderWidth,                0,
              NULL );
      XtManageChild ( ipts_htx_a2c [ nn ] [ ipts_htx_a2c_tot [ nn ] ] );
      XtAddCallback ( ipts_htx_a2c [ nn ] [ ipts_htx_a2c_tot [ nn ] ],
            XmNactivateCallback, ( XtCallbackProc ) ipts_htx_a2c_CB, ( XtPointer ) & c_arr [ cc1 ] );
      XmStringFree ( xstr );
      ipts_htx_a2c_tot [ nn ]++;
    }
  }  
}


/********************************************************************
                    Spec/design overviews
********************************************************************/
void
sort_D_arr ()
{
  int i, j, k, l, tt, temp [ MAX_D_block ];
  int row, block, cell, node, n1, n2;

  for ( i = 0 ; i < MAX_D_row ; i++ ) {
    for ( j = 0 ; j < MAX_D_block - 1 ; j++ ) {
      for ( k = j + 1 ; k < MAX_D_block ; k++ ) {
        if ( D_block_tot [ i ] [ j ] < D_block_tot [ i ] [ k ] ) {
          for ( l = 0 ; l < MAX_D_block ; l++ ) {
            temp [ l ] = D_arr [ i ] [ j ] [ l ];
	  }
          for ( l = 0 ; l < MAX_D_block ; l++ ) {
            D_arr [ i ] [ j ] [ l ] = D_arr [ i ] [ k ] [ l ];
	  }
          for ( l = 0 ; l < MAX_D_block ; l++ ) {
            D_arr [ i ] [ k ] [ l ] = temp [ l ];
	  }
          tt = D_block_tot [ i ] [ j ];
          D_block_tot [ i ] [ j ] = D_block_tot [ i ] [ k ];
          D_block_tot [ i ] [ k ] = tt;
          tt = D_node [ i ] [ j ];
          D_node [ i ] [ j ] = D_node [ i ] [ k ];
          D_node [ i ] [ k ] = tt;
	}
      }
    }
  }

  /***
  sort the blocks themselves according to above
  ***/
  for ( i = 0 ; i < MAX_D_row ; i++ ) {
    for ( j = 0 ; j < MAX_D_block ; j++ ) {
      for ( k = 0 ; k < MAX_D_cell - 1 ; k++ ) {
        for ( l = k + 1 ; l < MAX_D_cell ; l++ ) {
          n1 = 0;
          while ( D_node [ i + 1 ] [ n1 ] != D_arr [ i ] [ j ] [ k ] ) {
            n1++;
	  }
          n2 = 0;
          while ( D_node [ i + 1 ] [ n2 ] != D_arr [ i ] [ j ] [ l ] ) {
            n2++;
	  }
          if ( D_block_tot [ i ] [ n1 ] < D_block_tot [ i ] [ n2 ] ) {
            tt = D_arr [ i ] [ j ] [ k ];
            D_arr [ i ] [ j ] [ k ] = D_arr [ i ] [ j ] [ l ];
            D_arr [ i ] [ j ] [ l ] = tt;
	  }
	}
      }
    }
  }
}

D_arr_process_design_node ( cc, row )
int cc, row;
{
  int nn, cc1, i;
  int name [ 50 ], ext, type;

  if ( ! D_arr_load_err ) {
    D_cell = 0;

    val_ext ( &ext, cc );
    if ( ext == imp ) {  /* not a mch! (lib or enm_gen) */
      card_inc_ipt ( &nn, cc );
    }
    else {
      nn = 0;
    }

/*
    while ( nn && D_cell < MAX_D_cell ) {
      valOrd_inc_ipt ( &cc1, cc, nn );
      get_botref ( &cc1, cc1 );
      val_mand ( name, &ext, &type, cc1 );
      if ( ext == imp       || type == lib     ||
           type == lib_vhdl || type == enm_gen || type == gen_vhdl ) {
        D_arr [ row ] [ D_block [ row ] ] [ D_cell ]  = cc1;
        D_cell++;
      }
      nn--;
    }
*/
    for ( i = 1; i <= nn ; i++ ) {
     valOrd_inc_ipt ( &cc1, cc, i );
      get_botref ( &cc1, cc1 );
      val_mand ( name, &ext, &type, cc1 );
      if ( ext == imp       || type == lib     ||
           type == lib_vhdl || type == enm_gen || type == gen_vhdl ) {
        D_arr [ row ] [ D_block [ row ] ] [ D_cell ]  = cc1;
        D_cell++;
      }
    }

    if ( D_cell == MAX_D_cell ) {
      D_arr_load_err = 1;
    }

    if ( ! D_arr_load_err ) {
      D_node      [ row ] [ D_block [ row ] ] = cc;
      D_block_tot [ row ] [ D_block [ row ] ] = D_cell;
      D_block     [ row ] ++;

      if ( D_block [ row ] == MAX_D_cell ) {
        D_arr_load_err = 1;
      }

      if ( ! D_arr_load_err ) {
        val_ext ( &ext, cc );
        if ( ext == imp ) {  /* not a mch! (lib or enm_gen) */
          card_inc_ipt ( &nn, cc );
        }
        else {
          nn = 0;
        }
/*
        while ( nn ) {
          valOrd_inc_ipt ( &cc1, cc, nn );
          get_botref ( &cc1, cc1 );
          val_mand ( name, &ext, &type, cc1 );
          if ( ext == imp       || type == lib     ||
               type == lib_vhdl || type == enm_gen || type == gen_vhdl ) {
            if ( row + 1 == MAX_D_row ) {
              D_arr_load_err = 2;
	    }
            else {
              D_arr_process_design_node ( cc1, row + 1 );
	    }
	  }
          nn--;
	}
*/
        for ( i = 1; i <= nn ; i++ ) {
          valOrd_inc_ipt ( &cc1, cc, i );
          get_botref ( &cc1, cc1 );
          val_mand ( name, &ext, &type, cc1 );
          if ( ext == imp       || type == lib     ||
               type == lib_vhdl || type == enm_gen || type == gen_vhdl ) {
            if ( row + 1 == MAX_D_row ) {
              D_arr_load_err = 2;
	    }
            else {
              D_arr_process_design_node ( cc1, row + 1 );
	    }
	  }
	}

      }
    }
  }
}

D_arr_process_spec_node ( cc, row )
int cc, row;
{
  int nn, cc1, i;
  int name [ 50 ], ext, type;

  if ( ! D_arr_load_err ) {
    D_cell = 0;

    val_ext ( &ext, cc );
    if ( ext == mch ) {  /* not an imp! (lib or enm_gen) */
      card_inc_ipt ( &nn, cc );
    }
    else {
      nn = 0;
    }

/*
    while ( nn && D_cell < MAX_D_cell ) {
      valOrd_inc_ipt ( &cc1, cc, nn );
      val_mand ( name, &ext, &type, cc1 );
      if ( ext == mch || type == lib || type == enm_gen ) {
        D_arr [ row ] [ D_block [ row ] ] [ D_cell ]  = cc1;
        D_cell++;
      }
      nn--;
    }
*/
    for ( i = 1; i <= nn ; i++ ) {
      valOrd_inc_ipt ( &cc1, cc, i );
      val_mand ( name, &ext, &type, cc1 );
      if ( ext == mch || type == lib || type == enm_gen ) {
        D_arr [ row ] [ D_block [ row ] ] [ D_cell ]  = cc1;
        D_cell++;
      }
    }

    if ( D_cell == MAX_D_cell ) {
      D_arr_load_err = 1;
    }

    if ( ! D_arr_load_err ) {
      D_node      [ row ] [ D_block [ row ] ] = cc;
      D_block_tot [ row ] [ D_block [ row ] ] = D_cell;
      D_block     [ row ] ++;

      if ( D_block [ row ] == MAX_D_cell ) {
        D_arr_load_err = 1;
      }

      if ( ! D_arr_load_err ) {
        val_ext ( &ext, cc );
        if ( ext == mch ) {  /* not an imp! (lib or enm_gen) */
          card_inc_ipt ( &nn, cc );
        }
        else {
          nn = 0;
        }

/*
        while ( nn ) {
          valOrd_inc_ipt ( &cc1, cc, nn );
          val_mand ( name, &ext, &type, cc1 );
          if ( ext == mch       || type == lib     ||
               type == lib_vhdl || type == enm_gen || type == gen_vhdl ) {
            if ( row + 1 == MAX_D_row ) {
              D_arr_load_err = 2;
	    }
            else {
              D_arr_process_spec_node ( cc1, row + 1 );
	    }
	  }
          nn--;
	}
*/
        for ( i = 1; i <= nn ; i++ ) {
          valOrd_inc_ipt ( &cc1, cc, i );
          val_mand ( name, &ext, &type, cc1 );
          if ( ext == mch       || type == lib     ||
               type == lib_vhdl || type == enm_gen || type == gen_vhdl ) {
            if ( row + 1 == MAX_D_row ) {
              D_arr_load_err = 2;
	    }
            else {
              D_arr_process_spec_node ( cc1, row + 1 );
	    }
	  }
	}

      }
    }
  }
}

void
init_D_arr ()
{
  int i,j,k;

  for ( i = 0 ; i < MAX_D_row ; i++ ) {
    for ( j = 0 ; j < MAX_D_block ; j++ ) {
      for ( k = 0 ; k < MAX_D_cell ; k++ ) {
        D_arr [ i ] [ j ] [ k ] = 0;
      }
      D_block_tot [ i ] [ j ] = 0;
      D_node      [ i ] [ j ] = 0;
      D_frame     [ i ] [ j ] = 0;
      D_sticky    [ i ] [ j ] = 0;
    }
    D_block [ i ] = 0;
  }
}

void
Load_DarrFromImpNode ( cc )
int cc;
{
  curr_obj = cc;
  init_D_arr ();
  D_arr_load_err = 0;
  D_arr_process_design_node ( cc, 0 );
  if ( ! D_arr_load_err ) {
    sort_D_arr ();
  }
}

void
Load_DarrFromSpecNode ( cc )
int cc;
{
  curr_obj = cc;
  init_D_arr ();
  D_arr_load_err = 0;
  D_arr_process_spec_node ( cc, 0 );
  if ( ! D_arr_load_err ) {
    sort_D_arr ();
/***
  {
    int i, j, k;
     printf ( "------------------------------------------------\n" );
     for ( i = 0 ; i < MAX_D_row ; i++ ) {
       for ( j = 0 ; j < MAX_D_block ; j++ ) {
         for ( k = 0 ; k < MAX_D_cell ; k++ ) {
           printf("%d   ", D_arr [ i ] [ j ] [ k ]);
         }
         printf ( "    %d  %d  %d  %d\n",D_block_tot [ i ] [ j ], D_node [ i ] [ j ], D_frame [ i ] [ j ], D_sticky [ i ] [ j ] );
       }
       printf("\n");
     }
  }
***/
  }
}

void
find_cc_in_D_node ( cc, i, j )
int cc, i, *j;
{
  *j = 0;
  while ( D_node [ i ] [ *j ] != cc ) {
    (*j)++;
  }
}

void
find_cc_in_D_arr ( cc, i, j, k )
int cc, i, *j, *k;
{
  *j = 0;
  *k = 0;
  while ( D_arr [ i ] [ *j ] [ *k ] != cc ) {
    if ( *j + 1 < MAX_D_block ) {
      (*j)++;
    }
    else {
      (*k)++;
      *j = 0;
    }
  }
}

int
abs_y_coord_for_construct ( c_row, c_col )
int c_row, c_col;
{
  Dimension d1, d2, d3;
  

  XtVaGetValues (
      XtParent ( XtParent ( sees_htx_a2c_frame [ c_row ] [ c_col ] ) ),
      XmNy,                &d3,
      NULL );


  XtVaGetValues (
      sees_htx_a2c_frame [ c_row ] [ c_col ],
      XmNy,                &d1,
      XmNheight,           &d2,
      NULL );
  return ( ( int ) d1 + ( int ) d2 + ( int ) d3 );
}

int
abs_y_coord_for_frame ( c_row, c_col )
int c_row, c_col;
{
  Dimension d1, d2, d3;
  

  XtVaGetValues (
      XtParent ( XtParent ( sees_htx_a2c_frame [ c_row ] [ c_col ] ) ),
      XmNy,                &d3,
      NULL );


  XtVaGetValues (
      sees_htx_a2c_frame [ c_row ] [ c_col ],
      XmNy,                &d1,
      XmNheight,           &d2,
      NULL );
  return ( ( int ) d1 + ( ( int ) d2 / 2  ) + ( int ) d3 );
}

void
PositionDisplay ()
{
  int i, j, k, cc, jj, kk, done, found;
  int block_row, block_col, construct_row, construct_col;
  int top_offset;

  /***
  set all offsets
  ***/
  tot_htx_constructs = 1;
  tot_htx_blocks = 1;
  i = 0;
  j = 0;
  k = 0;
  construct_row = 0;
  construct_col = 0;

  done = 0;

  cc = D_arr [ i ] [ j ] [ k ];


  if ( cc == 0 ) {
    done = 1;
  }

  while ( ! done ) {
    if ( i + 1 < MAX_D_row ) {

      if ( k == 0 ) {

        /***
        set offset for frame
        ***/
        block_row = ( tot_htx_blocks / MAX_a2c_htx );
        block_col = ( tot_htx_blocks % MAX_a2c_htx );

        if ( i == 0 ) {
          top_offset = abs_y_coord_for_frame ( 0, 0 );
	}
        else {
          top_offset = abs_y_coord_for_frame (
             ( D_sticky [ i ] [ j ] / MAX_a2c_htx ),
             ( D_sticky [ i ] [ j ] % MAX_a2c_htx )  );
	}

        XtVaSetValues ( left_big_arr_htx [ block_row ] [ block_col ],
            XmNtopOffset,         top_offset + 3,
             NULL );
        tot_htx_blocks++;
      }

      /***
      set offset for construct
      ***/
      construct_row = ( tot_htx_constructs / MAX_a2c_htx );
      construct_col = ( tot_htx_constructs % MAX_a2c_htx );

      if ( k == 0 ) {
        /***
        first in block
        ***/
        top_offset = -5;
      }
      else {
        /***
        not first in block
        ***/
        Dimension dd;
        top_offset = abs_y_coord_for_construct (
                 ( tot_htx_constructs - 1 ) / MAX_a2c_htx,
                 ( tot_htx_constructs - 1 ) % MAX_a2c_htx  );
        XtVaGetValues (
            XtParent ( XtParent ( sees_htx_a2c_frame
                                       [ construct_row ] [ construct_col ] ) ),
            XmNy,                &dd,
            NULL );
        top_offset = top_offset - ( int ) dd;
      }

      XtVaSetValues (
          sees_htx_a2c_frame [ construct_row ] [ construct_col ],
          XmNtopOffset,           top_offset + 5,
          NULL );    
      
      tot_htx_constructs++;

      find_cc_in_D_node ( cc, i + 1, &jj );
      if ( D_block_tot [ i + 1 ] [ jj ] ) {
        /***
        something imported below
        ***/
        j = jj;
        i++;
        k = 0;
        cc = D_arr [ i ] [ j ] [ k ];
      }
      else {
        /***
        nothing imported below
        ***/
        if ( ( k + 1 < MAX_D_block )         &&
             ( D_arr [ i ] [ j ] [ k + 1 ] )    ) {
          /***
          more imported in same frame
          ***/
          k++;
          cc = D_arr [ i ] [ j ] [ k ];
        }
        else {
          /***
          no more imported in current frame - backtrack!
          ***/
          found = 0;
          while ( ! found && i != 0 ) {
            i--;
            find_cc_in_D_arr ( D_node [ i + 1 ] [ j ], i, &j, &k );
            if ( ( k + 1 < MAX_D_cell )          &&
                 ( D_arr [ i ] [ j ] [ k + 1 ] )   ) {
              /***
              a previous frame incomplete
              ***/
              found = 1;
              k = k + 1;
              cc = D_arr [ i ] [ j ] [ k ];
	    }
	  }
          if ( ! found ) {
            done = 1;
	  }
	}
      }
    }
    else { /*** ! ( i + 1 < MAX_D_row ) ***/
      done = 1;
    }
  }
/*
  XMapRaised ( display, ( Window ) left_big_arr_htx [ 0 ] [ 1 ] );
  XtUnmanageChild ( left_big_arr_htx [ 0 ] [ 1 ] );
  XtManageChild ( left_big_arr_htx [ 0 ] [ 1 ] );
*/
}

void
BuildDisplayFromD_arr ()
{
  int i, j, k, cc, jj, kk, done, found;
  int block_row, block_col, construct_row, construct_col;
  int name [ 50 ], ext, type;
  XmString xstr;
  char buf [ 200 ];
  int top_offset;

  /***
  top node
  ***/
  cc = D_node [ 0 ] [ 0 ];
  val_mand ( name, &ext, &type, cc );

  ipts_htx_a2c_frame [ 0 ] [ 0 ] = XtVaCreateManagedWidget ( "Canvas",
      xmFrameWidgetClass,             htx_scroll_form,
      XmNmarginWidth,                 10,
      XmNmarginHeight,                10,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   5,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  5,
      XmNshadowType,                  XmSHADOW_ETCHED_IN,
      NULL );

  ipts_htx_a2c [ 0 ] [ 0 ] = XtVaCreateManagedWidget ( "Canvas", 
      xmFormWidgetClass,              ipts_htx_a2c_frame [ 0 ] [ 0 ],
      NULL );

  sees_htx_a2c_frame [ 0 ] [ 0 ] = XtVaCreateManagedWidget ( "MainBox",
      xmFrameWidgetClass,             ipts_htx_a2c [ 0 ] [ 0 ],
      XmNtopAttachment,               XmATTACH_FORM,
      XmNshadowType,                  XmSHADOW_ETCHED_IN,
      NULL );

/***
printf ( "Managing box %s\n", ( char * ) name );
***/

  xstr = XmStringCreateLtoR ( ( char * ) name, charset );
  sees_htx_a2c [ 0 ] [ 0 ] = XtVaCreateManagedWidget ( lab_types [ type ], 
      xmPushButtonWidgetClass,        sees_htx_a2c_frame [ 0 ] [ 0 ],
      XmNlabelString,                 xstr,
      XmNshadowThickness,             0,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      NULL );
  XmStringFree ( xstr );

  XtAddCallback ( sees_htx_a2c [ 0 ] [ 0 ],
      XmNactivateCallback,
      ( XtCallbackProc ) ipts_htx_a2c_CB,
      ( XtPointer ) & c_arr [ cc ] );

  /***
  the rest
  ***/
  tot_htx_constructs = 1;
  tot_htx_blocks = 1;
  i = 0;
  j = 0;
  k = 0;
  construct_row = 0;
  construct_col = 0;

  done = 0;

  cc = D_arr [ i ] [ j ] [ k ];

  if ( cc == 0 ) {
    done = 1;
  }

  while ( ! done ) {
    if ( i + 1 < MAX_D_row ) {

      val_mand ( name, &ext, &type, D_arr [ i ] [ j ] [ k ] );

      if ( k == 0 ) {

        /***
        create new arrow & frame
        ***/
        D_frame  [ i ] [ j ] = tot_htx_blocks;
        D_sticky [ i ] [ j ] = tot_htx_constructs - 1;
        block_row = ( tot_htx_blocks / MAX_a2c_htx );
        block_col = ( tot_htx_blocks % MAX_a2c_htx );

        if ( i == 0 ) {
          left_big_arr_htx [ block_row ] [ block_col ] =
                 XtVaCreateWidget ( "Canvas",
             xmLabelWidgetClass,             htx_scroll_form,
             XmNlabelType,                   XmPIXMAP,
             XmNlabelPixmap,                 htx_pixmap_left_big,
             XmNtopAttachment,               XmATTACH_FORM,
             XmNleftAttachment,              XmATTACH_WIDGET,
             XmNleftWidget,                  ipts_htx_a2c_frame [ 0 ] [ 0 ],
             XmNleftOffset,                  -13,
             NULL );
	}
        else {

          find_cc_in_D_arr ( D_node [ i ] [ j ], i - 1, &jj, &kk );

          left_big_arr_htx [ block_row ] [ block_col ] =
                 XtVaCreateWidget ( "Canvas",
             xmLabelWidgetClass,             htx_scroll_form,
             XmNlabelType,                   XmPIXMAP,
             XmNlabelPixmap,                 htx_pixmap_left_big,
             XmNtopAttachment,               XmATTACH_FORM,
             XmNleftAttachment,              XmATTACH_WIDGET,
             XmNleftWidget,                  ipts_htx_a2c_frame
                                  [ D_frame [ i - 1 ] [ jj ] / MAX_a2c_htx ]
                                  [ D_frame [ i - 1 ] [ jj ] % MAX_a2c_htx ],
             XmNleftOffset,                  -13,
             NULL );
	}

        XtManageChild ( left_big_arr_htx [ block_row ] [ block_col ] );

/***
printf ( "Managing arrow %d %d\n", block_row, block_col );
***/

        ipts_htx_a2c_frame [ block_row ] [ block_col ] =
               XtVaCreateManagedWidget ( "Canvas",
           xmFrameWidgetClass,             htx_scroll_form,
           XmNmarginWidth,                 10,
           XmNmarginHeight,                10,
           XmNtopAttachment,               XmATTACH_WIDGET,
           XmNtopWidget,                   left_big_arr_htx
                                              [ block_row ] [ block_col ],
           XmNtopOffset,                   -11,
           XmNleftAttachment,              XmATTACH_WIDGET,
           XmNleftWidget,                  left_big_arr_htx
                                              [ block_row ] [ block_col ],
           XmNleftOffset,                  -1,
           XmNshadowType,                  XmSHADOW_ETCHED_IN,
           NULL );

        ipts_htx_a2c [ block_row ] [ block_col ] =
            XtVaCreateManagedWidget ( "Canvas", 
            xmFormWidgetClass,             ipts_htx_a2c_frame
                                              [ block_row ] [ block_col ],
            NULL );

        tot_htx_blocks++;
      }

      /***
      create construct
      ***/
      construct_row = ( tot_htx_constructs / MAX_a2c_htx );
      construct_col = ( tot_htx_constructs % MAX_a2c_htx );

      sees_htx_a2c_frame [ construct_row ] [ construct_col ] =
              XtVaCreateManagedWidget ( "Box",
         xmFrameWidgetClass,             ipts_htx_a2c
                                          [ D_frame [ i ][ j ] / MAX_a2c_htx ]
                                          [ D_frame [ i ][ j ] % MAX_a2c_htx ],
         XmNtopAttachment,               XmATTACH_FORM,
         XmNrightAttachment,             XmATTACH_FORM,
         XmNshadowType,                  XmSHADOW_ETCHED_IN,
         NULL );

/***
printf ( "Managing box %s\n", ( char * ) name );
***/
      xstr = XmStringCreateLtoR ( ( char * ) name, charset );
      sees_htx_a2c [ construct_row ] [ construct_col ] =
                 XtVaCreateManagedWidget ( lab_types [ type ], 
          xmPushButtonWidgetClass,        sees_htx_a2c_frame
                                                [ construct_row ]
                                                [ construct_col ],
          XmNlabelString,                 xstr,
          XmNshadowThickness,             0,
          XmNmarginWidth,                 5,
          XmNmarginHeight,                5,
          NULL );
      XmStringFree ( xstr );

      XtAddCallback ( sees_htx_a2c [ construct_row ] [ construct_col ],
          XmNactivateCallback, ( XtCallbackProc ) ipts_htx_a2c_CB,
             ( XtPointer ) & c_arr [ D_arr [ i ] [ j ] [ k ] ] );

      tot_htx_constructs++;
      find_cc_in_D_node ( cc, i + 1, &jj );
      if ( D_block_tot [ i + 1 ] [ jj ] ) {
        /***
        something imported below
        ***/
        j = jj;
        i++;
        k = 0;
        cc = D_arr [ i ] [ j ] [ k ];
      }
      else {
        /***
        nothing imported below
        ***/
        if ( ( k + 1 < MAX_D_block )         &&
             ( D_arr [ i ] [ j ] [ k + 1 ] )    ) {
          /***
          more imported in same frame
          ***/
          k++;
          cc = D_arr [ i ] [ j ] [ k ];
        }
        else {
          /***
          no more imported in current frame - backtrack!
          ***/
          found = 0;
          while ( ! found && i != 0 ) {
            i--;
            find_cc_in_D_arr ( D_node [ i + 1 ] [ j ], i, &j, &k );
            if ( ( k + 1 < MAX_D_cell )          &&
                 ( D_arr [ i ] [ j ] [ k + 1 ] )   ) {
              /***
              a previous frame incomplete
              ***/
              found = 1;
              k = k + 1;
              cc = D_arr [ i ] [ j ] [ k ];
	    }
	  }
          if ( ! found ) {
            done = 1;
	  }
	}
      }
    }
    else { /*** ! ( i + 1 < MAX_D_row ) ***/
      done = 1;
    }

  }

  sprintf ( buf, "    %s: Overview for %s       ",
                        toolkit_ver, GetName ( D_node [ 0 ] [ 0 ] ) );
  xstr = XmStringCreateLtoR ( buf, charset );
  XtVaSetValues ( htx_label, XmNlabelString, xstr, NULL );
  XmUpdateDisplay ( htx_label );
  XmStringFree ( xstr );
}

/***
  dialog already up
***/
void
ManageOverviewAndPosition ()
{
  BuildDisplayFromD_arr ();
  PositionDisplay ();
  XtManageChild ( htx_scroll_form );
}

/***
  dialog not yet up
***/
void
PopupOverviewAndPosition ()
{
  XtManageChild ( htx_scroll_form );
  XtManageChild ( htx_label );
  XtManageChild ( htx_B_logo );
  XtManageChild ( htx_form );
  XtManageChild ( htx_frame );
  XtManageChild ( htx_curr_form_lab );
  XtManageChild ( htx_curr_form );
  XtManageChild ( htx_scroll );
  htx_dialog_is_up = 1;
  XtPopup ( htx_dialog, XtGrabNone );
  XtUnmanageChild ( htx_scroll_form );
  ManageOverviewAndPosition ();
}

void
DisplayTopNode ()
{
  int rr, cc, nn;

  if ( ! D_arr_load_err ) {
    htx_curr_obj [ htx_curr_obj_ptr ] = ( -1 * D_node [ 0 ] [ 0 ] );
    if ( htx_dialog_is_up ) {
      ManageOverviewAndPosition ();
    }
    else {
      PopupOverviewAndPosition ();
    }
  }
  else {
    if ( D_arr_load_err == 1 ) {
      Popup_Err ( 0, "Insufficient Capacity for display:\n  recompile BMotif increasing `MAX_Browser'" );
    }
    else { /* D_arr_load_err == 2 */
      Popup_Err ( 0, "Insufficient Capacity for display:\n  recompile BMotif increasing `MAX_Design_Spec'" );
    }
  }
}

void
GetTopImpNode ( nn )
int nn;
{
  int cc;

  if ( nn == 1 ) {
    valOrd_gset1 ( &cc, 1 );
    curr_obj = cc;
    Load_DarrFromImpNode ( cc );
    XtVaSetValues ( htx_done_but,   XmNsensitive, True, NULL );
    XtVaSetValues ( htx_spec_but,   XmNsensitive, True, NULL );
    XtVaSetValues ( htx_design_but, XmNsensitive, True, NULL );
    if ( htx_curr_obj_ptr != 0 ) {
      XtVaSetValues ( htx_prev_but, XmNsensitive, True, NULL );   
    }
    DisplayTopNode ();
  }
  else {
    XtVaSetValues ( htx_done_but,   XmNsensitive, False, NULL );
    XtVaSetValues ( htx_prev_but,   XmNsensitive, False, NULL );
    XtVaSetValues ( htx_spec_but,   XmNsensitive, False, NULL );
    XtVaSetValues ( htx_design_but, XmNsensitive, False, NULL );
    sel_arr_tot = 0;
    while ( nn  && sel_arr_tot  < sel_str_len_MAX ) {
      valOrd_gset1 ( &cc, nn );
      strcpy ( sel_str_arr [ sel_arr_tot ], GetName ( cc ) );
      sel_obj_arr [ sel_arr_tot++ ] = cc;
      nn--;
    }
    if ( htx_dialog_is_up ) {
      Popup_Sel_flag = browse_design_selection;
    }
    else {
      Popup_Sel_flag = browse_design_selection_top_win;
    }
    Popup_SelOne_Dialog ( top_level, "Select design node" );
  }
}

void
GetTopSpecNode ( nn )
int nn;
{
  int cc;

  if ( nn == 1 ) {
    valOrd_gset1 ( &cc, 1 );
    curr_obj = cc;
    Load_DarrFromSpecNode ( cc );
    XtVaSetValues ( htx_done_but,   XmNsensitive, True, NULL );
    XtVaSetValues ( htx_spec_but,   XmNsensitive, True, NULL );
    XtVaSetValues ( htx_design_but, XmNsensitive, True, NULL );
    if ( htx_curr_obj_ptr != 0 ) {
      XtVaSetValues ( htx_prev_but, XmNsensitive, True, NULL );   
    }
    DisplayTopNode ();
  }
  else {
    XtVaSetValues ( htx_done_but,   XmNsensitive, False, NULL );
    XtVaSetValues ( htx_prev_but,   XmNsensitive, False, NULL );
    XtVaSetValues ( htx_spec_but,   XmNsensitive, False, NULL );
    XtVaSetValues ( htx_design_but, XmNsensitive, False, NULL );
    sel_arr_tot = 0;
    while ( nn  && ( sel_arr_tot  < sel_str_len_MAX ) ) {
      valOrd_gset1 ( &cc, nn );
      strcpy ( sel_str_arr [ sel_arr_tot ], GetName ( cc ) );
      sel_obj_arr [ sel_arr_tot++ ] = cc;
      nn--;
    }
    if ( htx_dialog_is_up ) {
      Popup_Sel_flag = browse_spec_selection;
    }
    else {
      Popup_Sel_flag = browse_spec_selection_top_win;
    }
    Popup_SelOne_Dialog ( top_level, "Select specification node" );
  }
}
