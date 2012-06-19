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
#include "BMotif_globals.h"


/*
String fallbacks[] = {
  "BMotifInit*fontList: -*-new century schoolbook-bold-r-*--12-*=TAG1",
  "BMotifInit*Dismiss.mnemonic: D",
  "BMotifInit*dialogTitle: B-Toolkit",
  "BMotifInit*traversalOn: true",
  "BMotifInit*highlightThickness: 0",
  "BMotifInit*borderWidth: 0",
  "BMotifInit*foreground: #a07040",
  "BMotifInit*background:  LightSkyBlue1",
  "BMotifInit*topShadowColor: gray98",
  "BMotifInit*bottomShadowColor: LightBlue4",
  "BMotifInit*Label*foreground: black",
  "BMotifInit*HelpDialog*dialogTitle: B-Toolkit Help",
  "BMotifInit*HelpDialog*background: LightCyan1",
  "BMotifInit*HelpDialog*topShadowColor: white",
  NULL
};
*/

void Init_OK_CANCEL_CB ( button, client_data )
Widget button;
XtPointer client_data;
{
  Widget dialog = XtParent ( XtParent ( XtParent ( button ) ) );

  XtPopdown ( dialog );
  XmUpdateDisplay ( dialog );
  XtDestroyWidget ( dialog );



 if ( ( * ( int * ) client_data ) == OK_BUTTON ) {

    CfgDepBase_is_Restored = 1;
    INI_CfgDepBase ();
    InitialiseFlagsAndStrings ();
    system ( "touch .Bpda" );      /* so "cp .Bpda .Bpda_0" will work */
    Save_CfgDepBase ();
    system ( "cp .Bpda .Bpda_0" ); /* now they're the same */
    DisplayCurrWinText ( "\n      Created new B-Toolkit development directory\n\n\n");
    main_continue ( 0, 0 );

  }
  else {                         /* CANCEL_BUTTON */
    
    printf("\n     Creation of new B-Toolkit directory aborted\n\n\n");
    DisplayCurrWinText ( "\n     Creation of new B-Toolkit directory aborted\n\n\n");
    unlink ( ".Bcjm" );
    unlink ( ".Bmvr" );
    unlink ( pid_id_file );
    unlink ( "HTX/ConstructsSummary.html" );
    unlink ( "HTX" );
    Kill_bplatform_and_exit ( 1, 0 );
  }
}

void HELP_CB( button, client_data   )
Widget button;
XtPointer client_data;
{
  struct help_struct help_data;

  help_data.text = "Create new development directory:\n\n\
    System directories will be created, although existing\n\
    SRC or PMD directories will not be overwritten\n";

  help_data.type = DIALOG_HELP;
  help_data.width  = 375;
  help_data.height = 162;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

BMotifInit ()
{
  Widget            dialog, dialog_form,
                    B_logo,
                    label, sep, och_form,
                    och_o, och_c, och_h;
  XmString xstr;
  char buf [ 250 ];

  void B_info_CB ();

#ifdef WWW_VERSION

  system ( "echo \"0\" > .Bcom" );
  exit ( 0 );

#else /* ! WWW_VERSION */

print_debug(10001);
  dialog = XmCreateDialogShell ( top_frame_form, "Options", NULL, 0 );

print_debug(10002);
  dialog_form = XtVaCreateWidget ( "SelDialog",
        xmFormWidgetClass,            dialog,
        XmNtraversalOn,               True,
        XmNautoUnmanage,              False,
        NULL );

print_debug(10003);
  B_logo = XtVaCreateManagedWidget ( "SelDialog", 
        xmPushButtonWidgetClass,      dialog_form,
        XmNlabelType,                 XmPIXMAP,
        XmNlabelPixmap,               B_framed_pixmap_gray94,
        XmNshadowThickness,           0,
        XmNmarginWidth,               0,
        XmNmarginHeight,              0,
        XmNtopAttachment,             XmATTACH_FORM,
        XmNtopOffset,                 7,
        XmNleftAttachment,            XmATTACH_FORM,
        XmNleftOffset,                7,
        XmNtraversalOn,               False,
        NULL );

print_debug(10004);
  strcpy ( buf, "  Create new B-Toolkit development in:\n\n    " );
  strcat ( buf, cur_dir );   
  strcat ( buf, "\n" );
print_debug(10005);
  xstr = XmStringCreateLtoR ( buf, charset );
print_debug(10006);
  label = XtVaCreateManagedWidget ( "Label",
        xmLabelGadgetClass,          dialog_form,
        XmNtopAttachment,            XmATTACH_FORM,
        XmNtopOffset,                15,
        XmNleftAttachment,           XmATTACH_WIDGET,
        XmNleftWidget,               B_logo,
        XmNleftOffset,               5,
        XmNrightAttachment,          XmATTACH_FORM,
        XmNrightOffset,              30,
        xmPushButtonWidgetClass,     och_form,
        XmNlabelString,              xstr,
        XmNshadowThickness,          0,
        XmNmarginWidth,              5,
        XmNmarginHeight,             5,
        XmNtraversalOn,              False,
        NULL);
print_debug(10007);
  XmStringFree ( xstr );
print_debug(10008);

  sep = XtVaCreateManagedWidget ( "SelDialog", 
        xmSeparatorGadgetClass,      dialog_form,
        XmNtopAttachment,            XmATTACH_WIDGET,
        XmNtopWidget,                label,
        XmNtopOffset,                15,
        XmNleftAttachment,           XmATTACH_FORM,
        XmNrightAttachment,          XmATTACH_FORM,
        XmNbottomAttachment,         XmATTACH_FORM,
        XmNbottomOffset,             48,
        NULL );
print_debug(10009);

  och_form = XtVaCreateWidget ( "ButtonLabel",
        xmFormWidgetClass,          dialog_form,
        XmNleftAttachment,          XmATTACH_FORM,
        XmNrightAttachment,         XmATTACH_FORM,
        XmNbottomAttachment,        XmATTACH_FORM,
        XmNbottomOffset,            5,
        NULL );
print_debug(10010);

  och_o = XtVaCreateManagedWidget ( "Create", 
        xmPushButtonGadgetClass,     och_form,
        XmNtopAttachment,            XmATTACH_FORM,
        XmNtopOffset,                6,
        XmNleftAttachment,           XmATTACH_FORM,
        XmNleftOffset,               12,
        XmNheight,                   25,
        XmNwidth,                    57,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,       1,
        XmNnavigationType,           XmTAB_GROUP,
        NULL );
  XtAddCallback( och_o, XmNactivateCallback,
        ( XtCallbackProc ) Init_OK_CANCEL_CB,
        ( XtPointer ) & ( c_arr[ OK_BUTTON ] ) );
print_debug(10011);

  och_c = XtVaCreateManagedWidget ( "Abort", 
        xmPushButtonGadgetClass,     och_form,
        XmNleftAttachment,           XmATTACH_WIDGET,
        XmNleftWidget,               och_o,
        XmNleftOffset,               15,
        XmNtopAttachment,            XmATTACH_FORM,
        XmNtopOffset,                6,
        XmNheight,                   25,
        XmNwidth,                    57,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,       1,
        XmNnavigationType,           XmTAB_GROUP,
        NULL );
  XtAddCallback( och_c, XmNactivateCallback,
        ( XtCallbackProc ) Init_OK_CANCEL_CB,
        ( XtPointer ) & ( c_arr[ CANCEL_BUTTON ] ) );

print_debug(10012);
  och_h = XtVaCreateManagedWidget ( "Help", 
        xmPushButtonGadgetClass,     och_form,
        XmNrightAttachment,          XmATTACH_FORM,
        XmNrightOffset,              12,
        XmNtopAttachment,            XmATTACH_FORM,
        XmNtopOffset,                6,
        XmNheight,                   25,
        XmNwidth,                    57,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,       1,
        XmNnavigationType,           XmTAB_GROUP,
        NULL );
  XtAddCallback( och_h, XmNactivateCallback,
        ( XtCallbackProc ) HELP_CB, NULL );

print_debug(10013);
  XmProcessTraversal ( och_o, XmTRAVERSE_CURRENT );

print_debug(10014);
  XtManageChild ( och_form );
print_debug(10015);
  XtManageChild ( dialog_form );
print_debug(10016);
  XtRealizeWidget ( dialog );
print_debug(10017);
  XtPopup ( dialog, XtGrabNone );
print_debug(10018);
  XmUpdateDisplay ( dialog );

#endif /* WWW_VERSION */
}
