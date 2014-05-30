/* Copyright (c) 1985-98, B-Core (UK) Ltd
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
CantReadResourceFile ()
{
 ;
}

void
B_info_CB ( widget )
Widget widget;
{
  struct help_struct help_data;
  int i, j, k;

/***
PrintBase;
DisplayStatusStructureAll ();
return;
***/

/***
DisplayAndCheckTotals ();
return;
***/

  sprintf ( fifo_write_buf, "%s\n              --o--o--o--o--o--o--o--o--o--o--o--o                   \n\n%s\n", BCore_info_help_text, B_info_help_text );

  help_data.text = fifo_write_buf;
  help_data.type = DIALOG_HELP;
  help_data.width  = 375;
  help_data.height = 825;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}


void
B_dir_CB ()
{
  struct help_struct help_data;

  sprintf ( fifo_write_buf, "The current development directory is:\n %s", cur_dir );

  /*
  help_data.text = fifo_write_buf;
  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 125;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
  */
  
  /* */
  Popup_Info ( fifo_write_buf );
}


/*                  LEAVE FOR NOW
void
SetEnvLabelBut ( env )
int env;
{
  static char text [ 500 ];

  switch ( env ) {
    case main_env:
      strcpy ( text, "All constructs (except proofs, docs and ops) are displayed in this environment.\nDisplay may be filtered by changing the `Construct Display' settings\nthrough the Top Bar Options button.\n\nThe Environment may be changed through the Top Bar Environment button." );
      ChangeEnvButton ( "Main Environment", text );
      break;
    case provers_env:
      strcpy ( text, "Constructs which have been POGenerated, together with\nproof files, are displayed in this environment.\n\nThe Environment may be changed through the Top Bar Environment button." );
      ChangeEnvButton ( "Provers Environment", text );
      break;
    case generators_env:
      strcpy ( text, "Base Object, Enumeration, Operation and Interface constructs\nare displayed in this environment.\n\nThe Environment may be changed through the Top Bar Environment button." );
      ChangeEnvButton ( "Generators Environment", text );
      break;
    case translators_env:
      strcpy ( text, "Implementations that have been analysed, or Motif interfaces that have\nbeen generated are displayed in this environment.\n\nThe Environment may be changed through the Top Bar Environment button." );
      ChangeEnvButton ( "Translators Environment", text );
      break;
    case documents_env:
      strcpy ( text, "All constructs that are already marked up, or are ready for marking up\n(machines, refinements or implementations currently analysed; bases,\nenumerations or interfaces currently generated; proofs that have been\nconstructed) are displayed in this environment.\nDisplay may be filtered by changing the `Construct Display' settings\nthrough the Top Bar Options button.\n\nThe Environment may be changed through the Top Bar Environment button." );
      ChangeEnvButton ( "Documents Environment", text );
      break;
    case ipr_pob_env:
      strcpy ( text, "\nThe environment for investigating the interactive proof of constructs\nhaving outstanding proof obligations" );
      ChangeEnvButton ( "InterProver Environment", text );
      break;
    case ipr_lem_env:
      strcpy ( text, "\nThe environment for investigating the interactive proof of constructs\nhaving outstanding proof obligations" );
      ChangeEnvButton ( "InterProver Environment", text );
      break;
    case btl_env:
      strcpy ( text, "\nThe environment for fully-interactive proof of constructs\nhaving outstanding proof obligations using the B-Tool" );
      ChangeEnvButton ( "B-Tool Environment", text );
      break;
    case anm_env:
      strcpy ( text, "\nThe environment for validating specifications" );
      ChangeEnvButton ( "Animator Environment", text );
      break;
  }
}
*/

void
cmt_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Commit Edits:\n\
    This option is applicable to opened constructs. If the Top Bar Options `Editor'\n\
    option is set to `kill editor', the editor will be killed after committing\n\
    and the construct displayed as closed, but if the option is set to `preserve editor'\n\
    the editor will be preserved with the construct remaining open.\n\
See Top Bar Help -> ToolBar -> CommitEdits";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 180;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
help_main_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Command Bar help:\n\
\n\
The Command Bar displays the tools that are available in each of\n\
the five B-Toolkit Environments (Main, Provers, Generators,\n\
Translators and Documents). Each is denoted by a 3-letter acronym\n\
label - except for `opn/clo' - and brief information on\n\
each may be obtained by clicking on the label (for example,\n\
clicking on `anm' - after dismissing this Help! - will give\n\
information on the B-Toolkit Animator).\n\
\n\
The current Environment Label is displayed immediately above the\n\
Command Bar, and brief information on the current environment may\n\
be obtained by clicking on it. The environment may be changed through\n\
the Top Bar Environment button (when a different set of tools will be\n\
displayed in the Command Bar).\n\
\n\
The Constructs Area appears in the recessed area immediately below\n\
the Command Bar and (if constructs are configured for which the tools\n\
in the current environment are applicable) displays a matrix with\n\
the Command Bar tool labels along the top, and the construct names\n\
appearing down the right hand side. If a particular tool is currently\n\
applicable for a particular construct, it is shown as a sensitive push\n\
button (ie. it is coloured) in the appropriate matrix position, otherwise\n\
it is displayed as insensitive (coloured gray). The `opn/clo'\n\
option is always available for all constructs appearing in the environment.\n\
\n\
Thus to invoke a particular tool for a particular construct, the\n\
appropriate button in the Constructs Area matrix should be pushed (if\n\
the tool is not currently applicable - coloured gray - it will `beep').\n\
\n\
Comprehensive information for each tool is available in the Top Bar Help";

  help_data.type = DIALOG_HELP;
  help_data.width  = 485;
  help_data.height = 550;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
anl_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Analyser:\n\
    This option is applicable to all machines, refinements and implementations\n\
    that are committed but not currently analysed; analysis is a prerequisite for\n\
    pogeneration, animation, document mark-up and (in the case of\n\
    implementations) translation.\n\
See Top Bar Help -> Main -> Analyse Constructs";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 162;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
pog_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "POGenerator:\n\
    This option is applicable to all non-library, non-generated\n\
    machines, refinements and implementations that not currently\n\
    pogenerated; the Analyser is invoked first, where necessary.\n\
See Top Bar Help -> Main -> ProofObligations";

  help_data.type = DIALOG_HELP;
  help_data.width  = 424;
  help_data.height = 162;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
sts_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Status:\n\
    This option is applicable to all machines, refinements and\n\
    implementations.\n\
See Top Bar Help -> Main -> Status";

  help_data.type = DIALOG_HELP;
  help_data.width  = 424;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

/***
void
brw_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Browse Construct:\n\
    This option is applicable to all machines, refinements\n\
    and implementations which are currently anlaysed.\n\
See Top Bar Help `Browser'";

  help_data.type = DIALOG_HELP;
  help_data.width  = 424;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}
***/

void
rst_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Reset Construct:\n\
    This option is applicable to all non-library, non_generated\n\
    constructs on which some processing has been done.\n\
See Top Bar Help -> Main -> Reset Construct";

  help_data.type = DIALOG_HELP;
  help_data.width  = 424;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
anm_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Animator:\n\
    This option is applicable to all machines that are currently analysed.\n\
See Top Bar Help -> Main -> Animation";

  help_data.type = DIALOG_HELP;
  help_data.width  = 450;
  help_data.height = 125;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
dmu_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Document Mark-Up:\n\
    This option is applicable to all machines, refinements and implementations\n\
    that are analysed but not marked-up, all base objects, enumerations\n\
    and interfaces that are generated but not marked-up, and all documents\n\
    that are not currently marked-up.\n\
See Top Bar Help Documents -> Mark Up Documents";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 162;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
shw_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Show Document on screen:\n\
    This option is applicable to all constructs that are currently marked-up.\n\
See Top Bar Help Documents -> Show Documents";

  help_data.type = DIALOG_HELP;
  help_data.width  = 450;
  help_data.height = 125;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
prt_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Send Document to printer:\n\
    This option is applicable to all constructs that are currently marked-up.\n\
See Top Bar Help Documents -> Print Documents";

  help_data.type = DIALOG_HELP;
  help_data.width  = 450;
  help_data.height = 125;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
doc_rst_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Remove marked-up document :\n\
    This option is applicable to all constructs that are currently marked-up.\n\
See Top Bar Help Documents -> Mark Up Documents";

  help_data.type = DIALOG_HELP;
  help_data.width  = 450;
  help_data.height = 125;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
edt_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Opn/Clo:\n\
    Open Editor is applicable to all constructs that are not currently open,\n\
    Quit Editor being available for each opened construct; both are effected\n\
    by `clicking' on the construct name, with open constructs indicated by\n\
    the construct name being shown in inverse video. The editor to be invoked\n\
    may be designated through the BEDIT environment variable. Any changes\n\
    to the construct being edited MUST BE SAVED before quitting, if the\n\
    intention is to commit those changes to the system.\n\
See Top Bar Help -> ToolBar -> Close Edit Windows/Commit Edits'";

  help_data.type = DIALOG_HELP;
  help_data.width  = 485;
  help_data.height = 225;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}



/*
void
apr_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "AutoProver:\n\
    This option is applicable to all machines, refinements and implementations\n\
    which are pogenerated and currently have undischarged proof obligations.\n\
See Top Bar Help `AutoProver'";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
ipr_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "InterProver:\n\
    This option is applicable to all machines, refinements and implementations\n\
    which are pogenerated and currently have undischarged proof obligations.\n\
See Top Bar Help `InterProver'";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
btl_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "B-Tool:\n\
    This option is applicable to all machines, refinements and implementations\n\
    which are pogenerated and currently have undischarged proof obligations.\n\
See Top Bar Help `B-Tool'";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}
*/

void
prv_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Provers:\n\
    This option is applicable to all machines, refinements and implementations\n\
    which are pogenerated and currently have undischarged proof obligations.\n\
See Top Bar Help -> Provers";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
pmd_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Edit current level PROOFMETHOD file:\n\
    This option is applicable to all machines, refinements and implementations\n\
    which are pogenerated and currently have undischarged proof obligations.\n\
See Top Bar Help -> Provers";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
rsl_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

/*
  help_data.text = "Revert to Previous Proof Level:\n\
    This option is applicable to all machines, refinements and\n\
    implementations which currently have at least one level of autoproof.\n\
    WARNING: PROOFS (ESPECIALLY BTOOLPROVER PROOFS) ARE LOST!!!\n\
See Top Bar Help `AutoProver'";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 175;
*/

  help_data.text = "Revert to Previous Proof Level:\n\
    This option is applicable to all machines, refinements and\n\
    implementations which currently have at least one level of autoproof.\n\
See Top Bar Help -> Provers -> Remove Proofs";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 140;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
ppf_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Proof Printer:\n\
    This option is applicable to all machines, refinements and implementations\n\
    which are pogenerated/autoproved. A `prf' construct containing either\n\
    statements of proof obligations (in the case of Level 0 constructs produced\n\
    by the POGenarator), or proof listings (for Levels greater than 0 produced\n\
    by the AutoProver).\n\
See Top Bar Help -> Provers -> Print Proofs";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 175;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

/*
void
sup_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Show Undischarged Proof Obligations:\n\
    This option is applicable to all machines, refinements and implementations\n\
    which have undischarged proof obligations, and produces an on-screen listing\n\
    in the form \"proof obligation name\".\"number\".\n\
See Top Bar Help `AutoProver', `InterProver' and `BToolProver'";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 150;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}
*/

void
lvl_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Display of Current Proof Level:\n\
    This display (provided in the Provers Environment) indicates the\n\
    current proof level, 0 being the first (indicating no proofs yet).\n\
See Top Bar Help -> Provers";

  help_data.type = DIALOG_HELP;
  help_data.width  = 450;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
pob_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Display of Number of Undischarged Proof Obligations:\n\
    This display (provided in the Provers Environment) indicates the\n\
    current number of undischarged proof obligations.\n\
See Top Bar Help -> Provers";

  help_data.type = DIALOG_HELP;
  help_data.width  = 450;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
tot_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Display of Total Number of Proof Obligations:\n\
    This display (provided in the Provers Environment) indicates the\n\
    total number of proof obligations produced through the POGenerator.\n\
See Top Bar Help -> Main -> ProofObligations";

  help_data.type = DIALOG_HELP;
  help_data.width  = 450;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
gbo_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Generate Base Object Operations:\n\
    This option is applicable to all base object constructs which are not\n\
    currently generated, and generates a file of operations which may be edited\n\
    to the user's requirement.\n\
See Top Bar Help -> Generators -> Data Bases";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 150;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
gbm_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Generate Base Object Machines/Implementations:\n\
    This option is applicable to all base object constructs which currently\n\
    have the operations, but not machines/implementations generated.\n\
See Top Bar Help -> Generators -> Data Bases";

  help_data.type = DIALOG_HELP;
  help_data.width  = 450;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
enm_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Enumerator:\n\
    This option is applicable to all enumerations which are not currently\n\
    generated, and generates a machine/C-program files.\n\
See Top Bar Help -> Generators -> Enumerated Sets";

  help_data.type = DIALOG_HELP;
  help_data.width  = 450;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
itf_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Interface Generator:\n\
    This option is applicable to all interfaces which are not currently\n\
    generated, and generates machines/implementations.\n\
See Top Bar Help -> Generators -> Interactive Interfaces";

  help_data.type = DIALOG_HELP;
  help_data.width  = 430;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
gen_rst_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Reset Construct:\n\
    This option is applicable to all base, enumeration or\n\
    interface constructs which are currently generated\n\
See Top Bar Help -> Generators";

  help_data.type = DIALOG_HELP;
  help_data.width  = 500;
  help_data.height = 150;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
trl_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Translate Implementation:\n\
    This option is applicable to all implementations which are\n\
    currently analysed, but not translated.\n\
See Top Bar Help -> Translators -> Translate to Code";

  help_data.type = DIALOG_HELP;
  help_data.width  = 400;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
lnk_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Link Implementation:\n\
    This option is applicable to all implementations which are\n\
    currently translated, but not linked.\n\
See Top Bar Help -> Translators -> Link Code";

  help_data.type = DIALOG_HELP;
  help_data.width  = 400;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
exe_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Execute Program:\n\
    This option is applicable to all implementations which are currently linked,\n\
    or Motif interfaces that are currently generated.\n\
See Top Bar Help -> Translators -> Execute Programs";

  help_data.type = DIALOG_HELP;
  help_data.width  = 475;
  help_data.height = 137;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

void
trl_rst_lab_CB ( widget )
Widget widget;
{
  struct help_struct help_data;

  help_data.text = "Reset Code Module:\n\
    This option is applicable to all implementations which are currently\n\
     translated, or Motif interfaces that are currently generated.\n\
See Top Bar Help -> Translators";

  help_data.type = DIALOG_HELP;
  help_data.width  = 475;
  help_data.height = 200;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}

Widget
Cre_3_letter_lab_offset ( lab_str, lab_rc, left_widget, lab_CB, decorate, leftOffset)
char * lab_str;
Widget lab_rc, left_widget;
XtCallbackProc lab_CB;
int decorate;
int leftOffset;
{
 Widget lab;
  XmString xstr = XmStringCreateLtoR ( lab_str, charset );
  if ( left_widget == ( Widget ) NULL )
  {
    if(decorate)
    {
	    lab = XtVaCreateManagedWidget ( "CommandBar",
        	xmPushButtonWidgetClass,     lab_rc,
        	XmNtopAttachment,            XmATTACH_FORM,
        	XmNbottomAttachment,         XmATTACH_FORM,
        	XmNleftAttachment,           XmATTACH_FORM,
        	XmNleftOffset,               4+leftOffset+22,
		XmNlabelString,              xstr,
        	XmNshadowThickness,          0,
        	XmNmarginWidth,              2,
        	XmNmarginHeight,             5,
        	XmNtopOffset,                0,
		XmNbackgroundPixmap,       B_downarrow_pixmap,
        	NULL );
    }
    else
    {
    	lab = XtVaCreateManagedWidget ( "CommandBar",
        	xmPushButtonWidgetClass,     lab_rc,
        	XmNtopAttachment,            XmATTACH_FORM,
        	XmNbottomAttachment,         XmATTACH_FORM,
        	XmNleftAttachment,           XmATTACH_FORM,
        	XmNleftOffset,               4+leftOffset+22,
        	XmNlabelString,              xstr,
        	XmNshadowThickness,          0,
        	XmNmarginWidth,              2,
        	XmNmarginHeight,             5,
        	XmNtopOffset,                0,
        	NULL );
    }
  }
  else
  {
    if(decorate)
    {
	    lab = XtVaCreateManagedWidget ( "CommandBar",
        	xmPushButtonWidgetClass,     lab_rc,
        	XmNtopAttachment,            XmATTACH_FORM,
        	XmNbottomAttachment,         XmATTACH_FORM,
        	XmNleftAttachment,           XmATTACH_WIDGET,
        	XmNleftWidget,               left_widget,
        	XmNleftOffset,               4+leftOffset,
        	XmNlabelString,              xstr,
        	XmNshadowThickness,          0,
        	XmNmarginWidth,              2,
        	XmNmarginHeight,             5,
        	XmNtopOffset,                0,
		XmNbackgroundPixmap,       B_downarrow_pixmap,
        	NULL );
    }
    else
    {
    	    lab = XtVaCreateManagedWidget ( "CommandBar",
        	xmPushButtonWidgetClass,     lab_rc,
        	XmNtopAttachment,            XmATTACH_FORM,
        	XmNbottomAttachment,         XmATTACH_FORM,
        	XmNleftAttachment,           XmATTACH_WIDGET,
        	XmNleftWidget,               left_widget,
        	XmNleftOffset,               4+leftOffset,
        	XmNlabelString,              xstr,
        	XmNshadowThickness,          0,
        	XmNmarginWidth,              2,
        	XmNmarginHeight,             5,
        	XmNtopOffset,                0,
        	NULL );
    }
  }
  XmStringFree ( xstr );
  XtAddCallback ( lab, XmNactivateCallback, ( XtCallbackProc ) lab_CB, NULL );
  return ( lab );
}

Widget
Cre_3_letter_lab ( lab_str, lab_rc, left_widget, lab_CB, decorate)
char * lab_str;
Widget lab_rc, left_widget;
XtCallbackProc lab_CB;
int decorate;
{
	return Cre_3_letter_lab_offset ( lab_str, lab_rc, left_widget, lab_CB, decorate, 0 );
}

void
Cre_Env_Buttons_Label ()
{
  XmString xstr;

  /***
  main
  ***/
  main_lab_form = XtVaCreateWidget ( "CommandBar",
      xmFormWidgetClass,           command_bar_rc,
      XmNtraversalOn,              False,
      NULL );

  cmt_main_lab = Cre_3_letter_lab ( "cmt", main_lab_form, ( Widget ) NULL, cmt_lab_CB , 1);

  anl_lab = Cre_3_letter_lab ( "anl", main_lab_form, cmt_main_lab, anl_lab_CB , 1);

  pog_lab = Cre_3_letter_lab ( "pog", main_lab_form, anl_lab, pog_lab_CB , 1);

  anm_lab = Cre_3_letter_lab ( "anm", main_lab_form, pog_lab, anm_lab_CB , 1);

  sts_lab = Cre_3_letter_lab ( "sts", main_lab_form, anm_lab, sts_lab_CB , 1);

  rst_lab = Cre_3_letter_lab ( "rst", main_lab_form, sts_lab, rst_lab_CB , 1);

  edt_main_lab =
     Cre_3_letter_lab_offset ( "open/close", main_lab_form, rst_lab, edt_lab_CB, 0, 2);

  xstr = XmStringCreateLtoR ( "help", charset );
  help_main_lab =  XtVaCreateWidget ( "CommandBar",
      xmPushButtonWidgetClass,     main_lab_form,
      XmNtopAttachment,            XmATTACH_FORM,
      XmNbottomAttachment,         XmATTACH_FORM,
      XmNrightAttachment,          XmATTACH_FORM,
      XmNrightOffset,              25,
      XmNlabelString,              xstr,
      XmNshadowThickness,          0,
      XmNmarginWidth,              2,
      XmNmarginHeight,             5,
      XmNtopOffset,                0,
      NULL );
  XmStringFree ( xstr );
  XtAddCallback ( help_main_lab, XmNactivateCallback,
                            ( XtCallbackProc ) help_main_lab_CB, NULL );

  /***
  provers
  ***/
  provers_lab_form = XtVaCreateWidget ( "CommandBar", 
      xmFormWidgetClass,           command_bar_rc,
      XmNtraversalOn,              False,
      NULL );

  cmt_provers_lab =
         Cre_3_letter_lab ( "cmt", provers_lab_form, ( Widget ) NULL, cmt_lab_CB , 1);

  prv_lab = Cre_3_letter_lab ( "prv", provers_lab_form, cmt_provers_lab, prv_lab_CB, 1);

  pmd_lab = Cre_3_letter_lab ( "pmd", provers_lab_form, prv_lab, pmd_lab_CB, 1 );

  ppf_lab = Cre_3_letter_lab ( "ppf", provers_lab_form, pmd_lab, ppf_lab_CB, 1);

  rsl_lab = Cre_3_letter_lab ( "rpl", provers_lab_form, ppf_lab, rsl_lab_CB, 1 );

  lvl_lab = Cre_3_letter_lab_offset ( "lvl", provers_lab_form, rsl_lab, lvl_lab_CB, 1 , 4);

  tot_lab = Cre_3_letter_lab ( "tot", provers_lab_form, lvl_lab, tot_lab_CB, 1 );

  pob_lab = Cre_3_letter_lab ( "pob", provers_lab_form, tot_lab, pob_lab_CB, 1 );

  edt_provers_lab =
     Cre_3_letter_lab_offset ( "open/close", provers_lab_form, pob_lab, edt_lab_CB, 0 , 10);

  /***
  generators
  ***/
  generators_lab_form = XtVaCreateWidget ( "CommandBar", 
      xmFormWidgetClass,           command_bar_rc,
      XmNtraversalOn,              False,
      NULL );

  cmt_generators_lab =
         Cre_3_letter_lab ( "cmt", generators_lab_form, ( Widget ) NULL, cmt_lab_CB, 1 );

  gbo_lab =
         Cre_3_letter_lab ( "gbo", generators_lab_form, cmt_generators_lab, gbo_lab_CB, 1);

  gbm_lab = Cre_3_letter_lab ( "gbm", generators_lab_form, gbo_lab, gbm_lab_CB, 1 );

  enm_lab = Cre_3_letter_lab ( "enm", generators_lab_form, gbm_lab, enm_lab_CB, 1 );

  itf_lab = Cre_3_letter_lab ( "itf", generators_lab_form, enm_lab, itf_lab_CB, 1 );

  gen_rst_lab = Cre_3_letter_lab ( "rst", generators_lab_form, itf_lab, gen_rst_lab_CB, 1 );

  edt_generators_lab =
     Cre_3_letter_lab_offset ( "open/close", generators_lab_form, gen_rst_lab, edt_lab_CB, 0 , 2);

  /***
  translators
  ***/
  translators_lab_form = XtVaCreateWidget ( "CommandBar", 
      xmFormWidgetClass,           command_bar_rc,
      XmNtraversalOn,              False,
      NULL );

  cmt_translators_lab =
         Cre_3_letter_lab ( "cmt", translators_lab_form, ( Widget ) NULL, cmt_lab_CB, 1 );

  trl_lab =
     Cre_3_letter_lab ( "trl", translators_lab_form, cmt_translators_lab, trl_lab_CB, 1);

  lnk_lab = Cre_3_letter_lab ( "lnk", translators_lab_form, trl_lab, lnk_lab_CB, 1 );

  exe_lab = Cre_3_letter_lab ( "exe", translators_lab_form, lnk_lab, exe_lab_CB, 1 );

  trl_rst_lab = Cre_3_letter_lab ( "rst", translators_lab_form, exe_lab, trl_rst_lab_CB, 1 );

  edt_translators_lab =
      Cre_3_letter_lab_offset ( "open/close", translators_lab_form, trl_rst_lab, edt_lab_CB, 0, 2);


  /***
  documents
  ***/
  documents_lab_form = XtVaCreateWidget ( "CommandBar", 
      xmFormWidgetClass,           command_bar_rc,
      XmNtraversalOn,              False,
      NULL );

  cmt_documents_lab =
      Cre_3_letter_lab ( "cmt", documents_lab_form, ( Widget ) NULL, cmt_lab_CB, 1 );

  dmu_lab =
      Cre_3_letter_lab ( "dmu", documents_lab_form, cmt_documents_lab, dmu_lab_CB, 1);

  shw_lab = Cre_3_letter_lab ( "shw", documents_lab_form, dmu_lab, shw_lab_CB, 1 );

  prt_lab = Cre_3_letter_lab ( "prt", documents_lab_form, shw_lab, prt_lab_CB, 1 );

  doc_rst_lab = Cre_3_letter_lab ( "rst", documents_lab_form, prt_lab, doc_rst_lab_CB, 1);

  edt_documents_lab =
    Cre_3_letter_lab_offset ( "open/close", documents_lab_form, doc_rst_lab, edt_lab_CB, 0, 2);

}

/***************************
  Top Bar Pulldown Creation
**************************/

void
CreOptionUtilityLabelInStrBuf ( nn )
int nn;
{
  size_t i;
  char buf [ 150 ];  /* don't want the global buf */

  switch ( nn ) {
  case 1 :
    Retrieve_String ( optional_utility1_str_num, buf );
    strcpy ( str_buf, "Optional Utility 1 is not set" );
    break;
  case 2 :
    Retrieve_String ( optional_utility2_str_num, buf );
    strcpy ( str_buf, "Optional Utility 2 is not set" );
    break;
  case 3 :
    Retrieve_String ( optional_utility3_str_num, buf );
    strcpy ( str_buf, "Optional Utility 3 is not set" );
    break;
  case 4 :
    Retrieve_String ( optional_utility4_str_num, buf );
    strcpy ( str_buf, "Optional Utility 4 is not set" );
    break;
  case 5 :
    Retrieve_String ( optional_utility5_str_num, buf );
    strcpy ( str_buf, "Optional Utility 5 is not set" );
    break;
  }
  i = strlen ( buf );
  if ( i ) {
    while ( ( i ) && buf [ i ] != '/' ) { i--; }
    if ( buf [ i ] == '/' ) i++;
    strcpy( str_buf, & buf [ i ] );
  }
}

void
Cre_Top_Bar_Utils_Pulldown ()
{
  Widget pull_down, cascade, widget;
  size_t i;
  int j;
  XmString xstr;
  XtCallbackProc TopBar_Utils_CB ();

/***
printf("Cre_Top_Bar_Utils_Pulldown\n");
***/
  pull_down = XmCreatePulldownMenu ( top_bar, "PullDown", NULL, 0 );
  xstr = XmStringCreateLocalized ( "Utils" );
  UtilsPullDown = XtVaCreateManagedWidget ( "Utils",
      xmCascadeButtonGadgetClass,     top_bar,
      XmNsubMenuId,                   pull_down,
      XmNlabelString,                 xstr,
      NULL);
  XmStringFree ( xstr );

/***
printf("UtilsPullDown  - %d\n", UtilsPullDown );fflush(stdout);
***/

  for ( i = 0 ; Utilities_menu [ i ] . label != ( XtPointer ) NULL ; i++ ) {

    if ( strcmp ( Utilities_menu [ i ] . label, "Optional Utility" ) == 0 ) {
      Utils_Options_PullDown = XmCreatePulldownMenu ( pull_down, "PullDown", NULL, 0 );
      XtVaSetValues ( Utils_Options_PullDown, XmNtearOffModel, XmTEAR_OFF_ENABLED, NULL);
      xstr = XmStringCreateLocalized ( "Optional Utility" );
      cascade = XtVaCreateManagedWidget ( "Utils",
          xmCascadeButtonGadgetClass,     pull_down,
          XmNsubMenuId,                   Utils_Options_PullDown,
          XmNlabelString,                 xstr,
          NULL);
      XmStringFree ( xstr );

      for ( j = 1 ; j <= 5 ; j++ ) {
        CreOptionUtilityLabelInStrBuf ( j );
        Utils_Options_PullDown_PushButtons [ j ] = XtVaCreateManagedWidget ( str_buf,
             xmPushButtonGadgetClass,       Utils_Options_PullDown,
             XmNmarginWidth,               10, /* IHS */
            NULL );
        XtAddCallback( Utils_Options_PullDown_PushButtons [ j ],  XmNactivateCallback,
            ( XtCallbackProc ) TopBar_Utils_CB,
            ( XtPointer ) & c_arr [ 23 + j ] );
      }

    }

    else {

      if ( strcmp ( Utilities_menu [ i ] . label, "Help" ) == 0 ) {
        XtVaCreateManagedWidget ( "PullDown",
            xmSeparatorGadgetClass,      pull_down,
            XmNmarginWidth,              25,
            NULL );
      }

      widget = XtVaCreateManagedWidget ( Utilities_menu [ i ] . label,
           xmPushButtonGadgetClass,       pull_down,
           XmNmarginWidth,               10, /* IHS */
          NULL );
      XtAddCallback( widget,  XmNactivateCallback,
          ( XtCallbackProc ) TopBar_Utils_CB,
          ( XtPointer ) ( Utilities_menu [ i ] ) . client_data );

    }

  } /* for ( i = 0 ; ... */
}

Widget
Cre_Top_Bar_Pulldown ( parent, menu_title, items, call_back )
Widget parent;
char * menu_title;
TopBarMenuItem * items;
XtCallbackProc call_back;
{
  Widget pull_down, cascade, widget;
  size_t i;
  XmString xstr;

/* Pulldown menus are built from cascade buttons, so this function
 * also includes pullright menus.  Create the menu, the cascade button
 * that owns the menu, and then the submenu items.
*/

/***
  printf("Cre_Top_Bar_Pulldown - ");fflush(stdout);
***/
  pull_down = XmCreatePulldownMenu ( parent, "PullDown", NULL, 0 );
  if ( parent != top_bar ) {
    XtVaSetValues ( pull_down, XmNtearOffModel, XmTEAR_OFF_ENABLED, NULL);
  }
  xstr = XmStringCreateLocalized ( menu_title );
  cascade = XtVaCreateManagedWidget ( menu_title,
      xmCascadeButtonGadgetClass,     parent,
      XmNsubMenuId,                   pull_down,
      XmNlabelString,                 xstr,
      NULL);
  XmStringFree ( xstr );

  /* Now add the menu items */
  for ( i = 0 ; items  [ i ] . label != ( XtPointer ) NULL ; i++ ) {
    /* If subitems exist, create the pull-right menu by calling this
     * function recursively.  Since the function returns a cascade
     * button, the widget returned is used.
    */
    if ( items [ i ] . subitems != NULL ) {
      widget = Cre_Top_Bar_Pulldown ( pull_down, items [ i ] . label, 
                items [ i ] . subitems,  call_back );
    }
    else {
      if ( strcmp ( items [ i ] . label, "Dummy" ) == 0 ) {
        XtVaCreateManagedWidget ( "PullDown",
            xmSeparatorGadgetClass,      pull_down,
            XmNmarginWidth,              25,
            NULL );
      }
      else {
        if ( strcmp ( items [ i ] . label, "Help" ) == 0 ) {
          XtVaCreateManagedWidget ( "PullDown",
              xmSeparatorGadgetClass,      pull_down,
              XmNmarginWidth,              25,
              NULL );
        }
        widget = XtVaCreateManagedWidget ( items [ i ] . label,
             xmPushButtonGadgetClass,       pull_down,
             XmNmarginWidth,               10, /* IHS */
            NULL );
        XtAddCallback( widget,  XmNactivateCallback,
            ( XtCallbackProc ) call_back,
            ( XtPointer ) items [ i ] . client_data );
      }
    }
  }
/***
printf("%d\n",cascade);fflush(stdout);
***/
  XtRealizeWidget ( cascade );
  return ( cascade );
}


/**********************************************
        Top Bar Remake Callback
**********************************************/

XtCallbackProc
TopBar_Remake_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  if ( IsDeSensitized () ) {
    Popup_Info ( " Remake not available whilst processing ... " );    
    return;
  }

  LoadOpenEditedConstructsInto_sel_strs ();
  if ( sel_arr_tot ) {
    int i;
    Popup_Info ( "Can't Remake until edits are resolved" );
    DisplayCurrWinText ( "\n  The following open constructs have uncommited edits:\n\n" );
    for ( i = 0 ; i < sel_arr_tot ; i++ ) {
      sprintf ( buf, "    %s\n", sel_str_arr [ i ] );
      DisplayCurrWinText ( buf );
    }
    DisplayCurrWinText ( "\n  Resolve before Remake\n" );
    return;
  }

  switch ( * ( int * ) client_data ) {

  case 0:
      /* Pre_Remake ( remake_all_constructs ); */
      CommitAll_CB ( Commit_All_remake_all );
  break;

  case 1:
      /* Pre_Remake ( remake_construct ); */
      CommitAll_CB ( Commit_All_remake_construct );
  break;

  case 2:
  {
#define Remaketext "\
   Comprehensive help is available in Top Bar Help\n\
   for Remake.\n\n\
o `All constructs' produces a menu of jobs for all constructs\n\
  in the development which should be carried out for a full\n\
  remake (if required).\n\n\
o `Construct(s)' produces a menu of constructs from which\n\
  one or more may be selected, when a menu of jobs relating\n\
  to those constructs is subsequently produced (if required)\n\n\
  In both cases, the jobs presented depend on the current\n\
  setting of the Remake Options (see Top Bar Help for Options);\n\
  further, the list of jobs presented is pre-selected, and jobs may\n\
  be de-selected in the usual way to enable a partial remake\n\
  to be achieved."

    struct help_struct       help_data;
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) Remaketext;
    help_data.width  = 420;
    help_data.height = 325;
    Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
  }
  break;

  }
}


/**********************************************
        Top Bar Construct Callback
**********************************************/

XtCallbackProc
TopBar_Construct_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  char buf [ 150 ];  /* don't want the global buf */

  if ( IsDeSensitized () ) {
    Popup_Info ( " Constructs not available whilst processing ... " );    
    return;
  }

  switch ( * ( int * ) client_data ) {

  case 0:
    CloseAll_CB ();
  break;

  case 1: /* Commit All Currently-open-edited Constructs */
    CommitAll_CB ( Commit_All_not_remake );
  break;

  case 34: /* Analyse/Generate All Constructs */
    {
      void Pre_AnalyseGenerateAllConstructs ();
      Pre_AnalyseGenerateAllConstructs ( 1 );
    }
  break;

  case 36: /* Analyse/Generate & Translate All Constructs */
    {
      void Pre_AnalyseGenerateTranslateAllConstructs ();
      Pre_AnalyseGenerateTranslateAllConstructs ();
    }
  break;

  case 35: /* Remove All Code & Recompile SLIB Code */
    {
      void RecompileLibCodeFiles ();
      ResetAllCode ( /* desensitize_flag = */ 1 );
      RecompileLibCodeFiles ( /* interface_flag = */ 2 );
    }
  break;

  case 2: /* Reset All Constructs */
    {
      void ResetAllConstructs ();
      ResetAllConstructs ();
    }
  break;

  case 3: /* Remove All Marked-up Documents */
    {
       void RemoveAllMarkedUpDocuments ();
       RemoveAllMarkedUpDocuments ();
    }
  break;

  case 4: /* Remove All Code */
    ResetAllCode ( /* desensitize_flag = */ 1 );
  break;

  case 5: /* Rename Construct */
#ifdef WWW_VERSION
    WWW_Err;
#else /* ! WWW_VERSION */
    LoadRenamableInto_sel_strs ();
    if ( sel_arr_tot ) {
      Popup_Sel_flag = rename_selection;
      Popup_SelOne_Dialog ( top_level, "Rename construct" );
    }
    else {
      Popup_Info ( "No appropriate constructs to rename  " );
    }
#endif /* WWW_VERSION */
  break;

  case 6: /* Remove Construct(s) */
#ifdef WWW_VERSION
    WWW_Err;
#else /* ! WWW_VERSION */
    LoadRemovableInto_sel_strs ();
    if ( sel_arr_tot ) {
      Popup_Sel_flag = remove_selection;
      Popup_Sel_Dialog ( top_level, "Remove constructs" );
    }
    else {
      Popup_Info ( "No appropriate constructs to remove  " );
    }
#endif /* WWW_VERSION */
  break;

  case 7: /* Remove All Unused LIB Constructs */
    RemoveUnusedLibFiles ( 4 ); /* make 5 passes! */
  break;

  case 8: /* Create SLIB Construct */
#ifdef WWW_VERSION
    WWW_Err;
#else /* ! WWW_VERSION */
    if ( access ( BKIT_path, W_OK ) == -1  ) {
      sprintf ( buf, " No write permission in %s ", BKIT_path );
      Popup_Info ( buf );
      return;
    }
    LoadCreSLIBableInto_sel_strs ();
    if ( sel_arr_tot ) {
      Popup_Sel_flag = creSLIB_selection;
      Popup_SelOne_Dialog ( top_level, "Create SLIB construct" );
    }
    else {
      Popup_Info ( "  No appropriate constructs    " );
    }
#endif /* WWW_VERSION */
   break;

  case 13: /* Remove SLIB Construct */
#ifdef WWW_VERSION
    WWW_Err;
#else /* ! WWW_VERSION */
    if ( access ( BKIT_path, W_OK ) == -1  ) {
      sprintf ( buf, " No write permission in %s ", BKIT_path );
      Popup_Info ( buf );
      return;
    }
    sprintf ( buf, "%s/BLIB/LIB/CFG", BKIT_path );
    LoadLIBInto_sel_strs ( buf );
    if ( sel_arr_tot ) {
      Popup_Sel_flag = remSLIB_selection;
      Popup_SelOne_Dialog ( top_level, "Remove SLIB construct" );
    }
    else {
      Popup_Info ( "  No appropriate constructs    " );
    }
#endif /* WWW_VERSION */
   break;


/*
   case 9: /? Create TLIB Construct ?/
    {
      FILE ? Bcfg;
#ifdef WWW_VERSION
      WWW_Err;
#else /? ! WWW_VERSION ?/
      Retrieve_String ( teamlib_str_num, buf );
      if ( strcmp ( buf, "" ) == 0 ) {
        Popup_Err ( 0, "Teamlib directory not set - check TopBar Options" );
      }
      else if ( access ( buf, W_OK ) == -1 ) {
        sprintf ( fifo_write_buf, " No write permission in %s ", buf );
        Popup_Info ( fifo_write_buf );
        return;
      }
      else {
        strcat ( buf, "/CFG" );
        buf [ 249 ] = '\0';
        Bcfg = fopen ( buf, "r" );
        if ( Bcfg == NULL ) {
          char buf1 [ 300 ];
          strcpy ( buf1, "Directory " );
          Retrieve_String ( teamlib_str_num, buf );
          strcat ( buf1, buf );
          strcat ( buf1, "/CFG does not exist  " );
          buf [ 398 ] = '\0';
          Popup_Err ( 0, buf1 );
        }
        else {
          fclose ( Bcfg );
          LoadCreTLIBableInto_sel_strs ();
          if ( sel_arr_tot ) {
            Popup_Sel_flag = creTLIB_selection;
            Popup_SelOne_Dialog ( top_level, "Export TLIB construct" );
          }
          else {
            Popup_Info ( "  No appropriate constructs    " );
	  }
	}
      } 
#endif /? WWW_VERSION ?/
    }
  break;

  case 14: /? Remove TLIB Construct ?/
    {
      Popup_Info ( "       Not yet ...     " );
    }
  break;
*/

   case 15:
     {
       void UpdateFromSRC ();
       UpdateFromSRC ();
     }
  break;

    case 29:  /* Source Constrol setup */
     {
       void Popup_SourceControl_Setup ();
       Popup_SourceControl_Setup ();
     }
  break;

   case 30:  /* Source Control */
     {
       if ( SourceControl_Initialised ) {
         void Popup_SourceControl_Execute ();
         Popup_SourceControl_Execute ();
       }
       else {
         Popup_Minor_Err ( top_level, "Source Control has not been initialised" );
         DisplayCurrWinText ( "\n  TopBar Construct->Source Control Setup\n  to initialise Source Control" );
       }   
     }
  break;

   case 33:  /* Remove All Proofs */
    {
      int loc, obj, st, nn;
      void RemoveProofAtLevel ();

      first_Construct ( &loc, &obj );
      while ( loc ) {
        val_curMRIState( &st, obj );
        length_pob ( &nn, st );
        if ( nn ) { /* proofs have been generated */
          nn--;
          while ( nn ) {
            RemoveProofAtLevel ( obj, nn - 1 );
            nn--;
          }
          SetDisplayField_obj_Changed ( obj );
	}
        next_Construct ( &loc, &obj, loc, obj );
      } /* wile loc */
      DisplayCurrentEnv ();
    }
    break;

   case 10: /* Help */
    {
  

#define Constructtext "\
   Comprehensive help is available for all four items in the\n\
   Top Bar Help.\n\n\
o `Close All Currenlty-open Constructs' closes all constructs\n\
  currently open for editing; if the edited (SRC) file differs from\n\
  the configured (CFG) file, you are invited to commit the edits.\n\n\
o `Commit All Currenlty-open-edited Constructs' commits all edits to\n\
   open constructs currently made (and saved!) but not yet committed.\n\n\
o `Update from SRC' produces a (pre-selected) selection list of all\n\
   constructs having an edited (SRC) file that differs from the configured\n\
   (CFG) file. A further selection is then provided for each construct\n\
   enabling the differences between the SRC and CFG files to be viewed\n\
   before committing. Finally, any constructs in SRC which are not yet\n\
   configured are presented for possible introduction into the development\n\
   (as though TopBar Introduce -> From SRC had been pressed).\n\n\
o *`Reset All Constructs' results in the entire directory being\n\
  reset with all library/generated machines are removed; the\n\
  development may be automatically rebuilt through `Remake'.\n\n\
o `Remove Construct(s)' provides a menu of removable constructs\n\n\
o `Remove All Unused LIB Constructs' removes all library constructs\n\
  not currently employed.\n\n\
o *`Remove All Documents' results in all marked-up constructs\n\
  being removed - `Remake'will restore.\n\n\
o *`Remove All Code' results in all code being removed - `Remake'\n\
   will restore.\n\n\
o *`Remove All Proofs' results in all proofs being removed - `Remake'\n\
   will restore.\n\n\
o `Rename Construct' provides a menu of renamable constructs\n\n\
o *`Create SLIB Construct' facilitates the creation of a new library\n\
  construct in the system library directory.\n\n\
o *`Delete Library Construct from SLIB' facilitates the removal of an\n\
  existing library construct from SLIB - but the construct, together\n\
  with any code, will be lost!"

    struct help_struct       help_data;
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) Constructtext;
    help_data.width  = 475;
    help_data.height = 650;
    Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
    }
  break;

  }

}


/**********************************************
        Top Bar Introduce Callback
**********************************************/

XtCallbackProc
TopBar_Introduce_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  char buf [ 150 ];  /* don't want the global buf */

  if ( IsDeSensitized () ) {
    Popup_Info ( " Introduce not available whilst processing ... " );    
    return;
  }

  switch ( * ( int * ) client_data ) {

  case 0:
#ifdef WWW_VERSION
    WWW_Err;
#else /* ! WWW_VERSION */
    LoadIntroducableInto_sel_strs ( "SRC" );
    if ( sel_arr_tot ) {
      Popup_Sel_flag = introduce_SRC_selection;
      Popup_Sel_Dialog ( top_level, "SRC constructs" );
    }
    else {
      Popup_Info ( "No appropriate constructs in SRC  " );
    }
#endif /* WWW_VERSION */
  break;

  case 1:
    sprintf ( buf, "%s/BLIB/LIB/CFG", BKIT_path );
    LoadIntroducableInto_sel_strs ( buf );
    if ( sel_arr_tot ) {
      Popup_Sel_flag = introduce_SLIB_selection;
      Popup_SelOne_Dialog ( top_level, "SLIB constructs" );
    }
    else {
            Popup_Info ( "No appropriate constructs in SLIB  " );
    }
  break;

/*
  case 2:
    {
      FILE * Bcfg;
      Retrieve_String ( teamlib_str_num, buf );
      if ( strcmp ( buf, "" ) == 0 ) {
        Popup_Err ( 0, "Teamlib directory not set - check TopBar Options" );
      }
      else {
        strcat ( buf, "/CFG" );
        buf [ 249 ] = '\0';
        Bcfg = fopen ( buf, "r" );
        if ( Bcfg == NULL ) {
          char buf1 [ 300 ];
          strcpy ( buf1, "Directory " );
          Retrieve_String ( teamlib_str_num, buf );
          strcat ( buf1, buf );
          strcat ( buf1, "/CFG does not exist  " );
          buf [ 298 ] = '\0';
          Popup_Err ( 0, buf1 );
        }
        else {
          fclose ( Bcfg );
          LoadTLIBIntroducableInto_sel_strs ();
          if ( sel_arr_tot ) {
            Popup_Sel_flag = introduce_TLIB_selection;
            Popup_SelOne_Dialog ( top_level, "TLIB constructs" );
	  }
          else {
            Popup_Info ( "No appropriate constructs in TLIB  " );
          }
        }
      }
    }
  break;
*/

  case 3:
  {

#define Introducetext "\
   Comprehensive help is available for each of these items\n\
   in the Top Bar Help for Introduce.\n\n\
o `New' produces a menu of new constructs\n\
  that may be committed; selection of an item will cause a\n\
  template construct (containing as much relevant information\n\
  as possible) to be created and opened for editing.\n\n\
o `From SRC' produces a menu of\n\
  constructs currently in the user's SRC directory.\n\n\
o `From SLIB'\n\
  produces a menu of constructs (many of which are re-namable)\n\
  from the system library."

    struct help_struct       help_data;
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) Introducetext;
    help_data.width  = 410;
    help_data.height = 320;
    Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
  }
  break;

  case 10:
  case 11:
  case 13:
  case 15:
  case 16:
  case 18:
  case 20:
    Popup_IntroduceNewNamePromptDialog ( top_level,  * ( int * ) client_data - 10 );
  break;

  case 12:
    LoadRefImpAnlIntroducableInto_sel_strs ();
    if ( sel_arr_tot ) {
      Popup_Sel_flag = ref_anl_selection;
      Popup_SelOne_Dialog ( top_level, "Refine construct" );
    }
    else {
      Popup_Info ( "  No appropriate analysed constructs  " );
   }
   break;

  case 14:
    LoadRefImpAnlIntroducableInto_sel_strs ();
    if ( sel_arr_tot ) {
      Popup_Sel_flag = imp_anl_selection;
      Popup_SelOne_Dialog ( top_level, "Implement construct" );
    }
    else {
      Popup_Info ( "  No appropriate analysed constructs  " );
    }
  break;

  case 17:
    LoadAnlMchInto_sel_strs ();
    if ( sel_arr_tot ) {
      Popup_Sel_flag = enm_anl_selection;
      Popup_Sel_Dialog ( top_level, "Enumerate constructs" );
    }
    else {
      Popup_Info ( "  No appropriate analysed constructs  " );
    }
  break;

  case 19:
    LoadITFableMchInto_sel_strs ();
    if ( sel_arr_tot ) {
      Popup_Sel_flag = itf_anl_selection;
      Popup_SelOne_Dialog ( top_level, "Interface construct" );
    }
    else {
      Popup_Info ( "  No appropriate analysed constructs  " );
    }
  break;

  case 21:
    LoadNonOpsConstructsInto_sel_strs ();
    if ( sel_arr_tot ) {
      Popup_Sel_flag = doc_anl_selection;
      Popup_Sel_Dialog ( top_level, "Document constructs" );
    }
    else {
      Popup_Info ( "  No appropriate analysed constructs  " );
    }
  break;

  case 22:
  {

#define CmtNewtext "\
   This facility enables the introduction of a new\n\
   construct in template form (eg. with appropriate\n\
   keywords included in the construct) into the\n\
   development; the construct name is prompted for,\n\
   and the construct created in the user's SRC\n\
   directory and opened for editing:\n\n\
o `Machine'\n\
o `Refinement'\n\
o `Implementation'\n\
o `Base'\n\
o `Enumeration'\n\
o `Interface'\n\
o `Document'\n\n\
     each causes a file contaning appropriate keywords to be\n\
     created in SRC\n\n\
o `Refinement of analysed construct'\n\
o `Implementation of analysed construct'\n\
o `Enumeration of analysed machine(s)'\n\
o `Interface of implemented machine'\n\
o `Document of configured constructs'\n\n\
     each causes the toolkit to prompt for the anaysed construct (s)\n\
     required, after which a file contaning as much information as\n\
     possible (eg. all operation names with skeleton operations in\n\
     the first two cases) be created in SRC."

    struct help_struct       help_data;
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) CmtNewtext;
    help_data.width  = 450;
    help_data.height = 525;
    Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
  }
  break;

  case 30:
  case 31:
  case 32:
  case 33:
  case 35:
  case 37:
    Popup_IntroduceNewNamePromptDialog ( top_level, * ( int * ) client_data - 18 );
  break;

  }
}


/**********************************************
        Top Bar Utilities Callback
**********************************************/

XtCallbackProc
TopBar_Utils_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  char buf [ 150 ];  /* don't want the global buf */

  if ( IsDeSensitized () ) {
    Popup_Info ( " Utils not available whilst processing ... " );    
    return;
  }

  switch ( * ( int * ) client_data ) {

  case 7:
    B_info_CB ( top_level );
  break;

  case 5:
    B_dir_CB ();
  break;

  case 6:
     {
       LoadOpenEditedConstructsInto_sel_strs ();
       if ( ! sel_arr_tot ) {
         Pre_ChangeToNewDirectory ();
       }
       else {
         int i;
         Popup_Info ( "Can't change directory until edits are resolved" );
         DisplayCurrWinText ( "\n  The following open constructs have uncommited edits:\n\n" );
         for ( i = 0 ; i < sel_arr_tot ; i++ ) {
           sprintf ( buf, "    %s\n", sel_str_arr [ i ] );
           DisplayCurrWinText ( buf );
         }
         DisplayCurrWinText ( "\n  Resolve before changing to a new directory\n" );
       }
     }
  break;

  case 0:
    Retrieve_String ( shell_str_num, buf );
    if ( buf [ 0 ] != '\0' ) {
      strcat ( buf, " &" );
      execute ( buf );
      sprintf ( primary_string, "Executing %s", buf );
      Popup_Info ( primary_string );
    }
    else {
      execute ( "xterm &" );
      Popup_Info ( "Shell Options string not set - using xterm" );
    }
  break;

  case 1:
    DeSensitize ();
    Popup_FindPromptDialog ( top_level );
  break;

  case 2:
#ifdef WWW_VERSION
    WWW_Err;
#else /* ! WWW_VERSION */
    Popup_SavePromptDialog ( top_level );
#endif /* WWW_VERSION */
  break;

   case 3:
     {
/*
       LoadOpenEditedConstructsInto_sel_strs ();
       if ( ! sel_arr_tot ) {
          CloseAllOpenFilesAndQuit ();
       }
       else {
         int i;
         Popup_Info ( "Can't exit until edits are resolved" );
         DisplayCurrWinText ( "\n  The following open constructs have uncommited edits:\n\n" );
         for ( i = 0 ; i < sel_arr_tot ; i++ ) {
           sprintf ( buf, "    %s\n", sel_str_arr [ i ] );
           DisplayCurrWinText ( buf );
         }
         DisplayCurrWinText ( "\n  Resolve before exiting\n" );
       }
*/
       CloseAllOpenFilesAndQuit ();
     }
   break;

  case 24:
    Retrieve_String ( optional_utility1_str_num, buf );
    if ( buf [ 0 ] != '\0' ) {
      sprintf ( str_buf, "Executing %s", buf );
      Popup_Info ( str_buf );
      strcat ( buf, " &" );
      execute ( buf );
    }
    else {
      Popup_Minor_Err ( top_level, "Optional Utility 1 is not set!" );
    }
  break;

  case 25:
    Retrieve_String ( optional_utility2_str_num, buf );
    if ( buf [ 0 ] != '\0' ) {
      sprintf ( str_buf, "Executing %s", buf );
      Popup_Info ( str_buf );
      strcat ( buf, " &" );
      execute ( buf );
    }
    else {
      Popup_Minor_Err ( top_level, "Optional Utility 2 is not set!" );
    }
  break;

  case 26:
    Retrieve_String ( optional_utility3_str_num, buf );
    if ( buf [ 0 ] != '\0' ) {
      sprintf ( str_buf, "Executing %s", buf );
      Popup_Info ( str_buf );
      strcat ( buf, " &" );
      execute ( buf );
    }
    else {
      Popup_Minor_Err ( top_level, "Optional Utility 3 is not set!" );
    }
  break;

  case 27:
    Retrieve_String ( optional_utility4_str_num, buf );
    if ( buf [ 0 ] != '\0' ) {
      sprintf ( str_buf, "Executing %s", buf );
      Popup_Info ( str_buf );
      strcat ( buf, " &" );
      execute ( buf );
    }
    else {
      Popup_Minor_Err ( top_level, "Optional Utility 4 is not set!" );
    }
  break;

  case 28:
    Retrieve_String ( optional_utility5_str_num, buf );
    if ( buf [ 0 ] != '\0' ) {
      sprintf ( str_buf, "Executing %s", buf );
      Popup_Info ( str_buf );
      strcat ( buf, " &" );
      execute ( buf );
    }
    else {
      Popup_Minor_Err ( top_level, "Optional Utility 5 is not set!" );
    }
  break;

  case 4:
    {
/* */

#define Utilitiestext "\
   Comprehensive help is available for starred items in the\n\
   Top Bar Help.\n\n\
o `Release Information' displays information regarding this release\n\
   of the B-Toolkit.\n\n\
o `Current Development Directory' displays the full path of the current\n\
   development directory.\n\n\
o `Change / Create Development Directory' saves the current development and prompts\n\
   for a new directory.\n\n\
o *`Save in Remakable Form' writes the current state of the\n\
   development to a named directory; it may be automatically remade.\n\n\
o *`Find Identifier' locates the origin and type of a variable, set,\n\
   constant or operation name, together with a list of\n\
   referencing constructs.\n\n\
o `Shell' opens a shell (command prompt) in the current development directory;\n\
   If the Shell Option is set (Editor/Viewer/Shell Options), it is\n\
   used, otherwise an xterm is opened.\n\n\
o `Optional Utility' executes one of the five utilities set in\n\
   TopBar Options -> Optional Utilities.\n\n\
o `Exit' quits the B-Toolkit; any open files will be closed\n\
   (unsaved edits must first be resolved) - confirmation is required."

      struct help_struct       help_data;
      help_data.type   = DIALOG_HELP;
      help_data.text   = ( char * ) Utilitiestext;
      help_data.width  = 450;
      help_data.height = 500;
      Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
    }
  break;

  }
}

/**********************************************
        Top Bar Browse Callback
**********************************************/

XtCallbackProc
TopBar_Browse_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  char buf [ 150 ];  /* don't want the global buf */
  char* browserCommand;

  switch ( * ( int * ) client_data ) {

  case 10:
    {
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
        sprintf ( secondary_string, "Launching %s for ConstructsSummary", buf );
	/*
        strcpy ( primary_string, buf );
        strcat ( primary_string, " " );
        strcat ( primary_string, cur_dir );
        strcat ( primary_string, "/" );
        strcat ( primary_string, "HTX/ConstructsSummary.html &" );
	execute ( primary_string );
	*/
	/* - use more intelligent command line caller for browsers: */
	
	strcpy ( primary_string, cur_dir );
        strcat ( primary_string, "/" );
        strcat ( primary_string, "HTX/ConstructsSummary.html" );
	
	browserCommand=getBrowserCommandLine(buf,primary_string);
	strcpy ( primary_string, browserCommand );
	free(browserCommand);
	strcat ( primary_string, " &" );
	
	
	execute ( primary_string );
        
        Popup_Info ( secondary_string );
      }
    }
  break;

  case 21:
    {
      int nn;

      if ( IsDeSensitized () ) {
        Popup_Info ( " Overview not available whilst processing ... " );    
        return;
      }

      load_gset1_top_imp_nodes ();
      card_gset1( &nn );
      if ( ! nn ) {
        Popup_Info ( "No design to display   " );
      }
      else {
        DeSensitize ();
        init_htx_curr_obj ();
        GetTopImpNode ( nn );  /* BMotif_browser.c */
      }
    }
  break;

  case 22:
    {
      int nn;

      if ( IsDeSensitized () ) {
        Popup_Info ( " Overview not available whilst processing ... " );    
        return;
      }

      load_gset1_top_spec_nodes ();
      card_gset1( &nn );
      if ( ! nn ) {
        Popup_Info ( "No specifications to display   " );
      }
      else {
        DeSensitize ();
        init_htx_curr_obj ();
        GetTopSpecNode ( nn );  /* BMotif_browser.c */
      }
    }
  break;

  case 23:
    if ( IsDeSensitized () ) {
      Popup_Info ( " Overview not available whilst processing ... " );    
      return;
    }

    LoadBrowsableInto_sel_str ();
    if ( sel_arr_tot ) {
      Popup_Sel_flag = browse_selection;
      Popup_SelOne_Dialog ( top_level, "Browse construct" );
    }
    else {
      Popup_Info ( "No appropriate constructs to browse  " );
    }
  break;

  case 24:
  {
#define Overviewtext "\
   Comprehensive help is available in Top Bar Help\n\
   for Overview.\n\n\
o `Design' produces an overview of the top-level\n\
  design node; if more than one such node exists, a\n\
  selection of nodes is provided.\n\n\
o `Specification' produces an overview of the top-level\n\
  specification node; if more than one such node exists, a\n\
  selection of nodes is provided.\n\n\
o `Construct' produces a menu of constructs that\n\
  may currently be browsed; subsequent selection results in a\n\
  detailed overview of that construct."

    struct help_struct       help_data;
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) Overviewtext;
    help_data.width  = 400;
    help_data.height = 310;
    Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
  }
  break;

  default:  /* Palette */
    TopBar_Palette_CB ( * ( int * ) client_data );
  break;

  }
}

void
TopBar_Palette_CB ( nn )
int nn;
{
  FILE * Bpal;
  char pal_file [ 150 ];
  struct stat statBpal;
  struct help_struct help_data;
  char * text;

  /***
  create filename
  ***/
  strcpy ( pal_file, BKIT_path );
  strcat ( pal_file, "/BPALETTE/" );
  strcat ( pal_file, PaletteN_pal [ nn ] );

  /***
  get contents
  ***/
  if ( stat ( pal_file, &statBpal ) != 0 ) {
    perror( pal_file );
    return;
  }
  Bpal = fopen ( pal_file, "r" );
  if ( Bpal == NULL ) {
    perror( pal_file );
    return;
  }

  if ( ! ( text = XtMalloc ( ( unsigned ) statBpal.st_size + 1 ) ) ) {
    fprintf ( stderr, "\n Can't allocate enough space for %s\n",
        pal_file );
    return;
  }
  if ( ! fread ( text, sizeof ( char ), statBpal.st_size + 1, Bpal ) ) {
    fprintf ( stderr, "\n May not have read the entire file!\n" );
  }
  text [ statBpal.st_size ] = 0;
  fclose ( Bpal );

  /***
  set help data and call Popup_Help_CB 
  ***/
  help_data.type = PALETTE_HELP;
  help_data.text = ( char * ) text;
  help_data.width  = 250;
  help_data.height = 400;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );

  /***
  free allocated memory
  ***/
  XtFree ( text );
}


/**********************************************
        Top Bar Options
**********************************************/


/***
should agree with char * options [] in BMotif_globals.c
***/


#define OPTIONS_REMAKE                 0
#define OPTIONS_CONSTRUCT_DISPLAY      1
#define OPTIONS_EDITORS_VIEWERS        2
#define OPTIONS_DOCUMENTS              3
#define OPTIONS_TRANSLATORS_COMPILERS  4
#define OPTIONS_PROVERS                5
#define OPTIONS_INTERFACE              6
#define OPTIONS_BELL                   7
#define OPTIONS_SOURCE_CONTROL         8
#define OPTIONS_SAVE                   9
#define OPTIONS_RESTORE               10
#define OPTIONS_OPTIONAL_UTILITIES    11

#define tot_Options                   12


/*********
 Callback
**********/
XtCallbackProc
TopBar_Options_CB ( parent, client_data )
Widget parent;
XtPointer client_data;
{
  void Popup_NewRemake_Options_Dialog ();
  void Popup_NewConstructDisplay_Options_Dialog ();
  void Popup_NewEditorsViewers_Options_Dialog ();
  void Popup_NewDocuments_Options_Dialog ();
  void Popup_NewTranslatorsCompilers_Options_Dialog ();
  void Popup_NewProvers_Options_Dialog ();
  void Popup_NewInterface_Options_Dialog ();
  void Popup_NewBell_Options_Dialog ();
  void Popup_NewAnimateScripts_Options_Dialog ();
  void Popup_NewTeamlib_Options_Dialog ();
  void Popup_NewSourceControl_Options_Dialog ();

  if ( IsDeSensitized () ) {
    Popup_Info ( " Options not available whilst processing ... " );    
    return;
  }

  switch ( * ( int * ) client_data ) {
    case OPTIONS_REMAKE:
      Popup_NewRemake_Options_Dialog ( XtParent ( parent ) );
      break;
    case OPTIONS_CONSTRUCT_DISPLAY:
      Popup_NewConstructDisplay_Options_Dialog ( XtParent ( parent ) );
      break;
    case OPTIONS_EDITORS_VIEWERS:
      Popup_NewEditorsViewers_Options_Dialog ( XtParent ( parent ) );
      break;
    case OPTIONS_DOCUMENTS:
      Popup_NewDocuments_Options_Dialog ( XtParent ( parent ) );
      break;
    case OPTIONS_TRANSLATORS_COMPILERS:
      Popup_NewTranslatorsCompilers_Options_Dialog ( XtParent ( parent ) );
      break;
    case OPTIONS_PROVERS:
      Popup_NewProvers_Options_Dialog ( XtParent ( parent ) );
      break;
    case OPTIONS_INTERFACE:
      Popup_NewInterface_Options_Dialog ( XtParent ( parent ) );
      break;
    case OPTIONS_OPTIONAL_UTILITIES:
      Popup_NewAnimateScripts_Options_Dialog ( XtParent ( parent ) );
      break;
    case OPTIONS_BELL:
      Popup_NewBell_Options_Dialog ( XtParent ( parent ) );
      break;
/*
    case OPTIONS_TEAMLIB:
      Popup_NewTeamlib_Options_Dialog ( XtParent ( parent ) );
      break;
*/
    case OPTIONS_SOURCE_CONTROL:
      Popup_NewSourceControl_Options_Dialog ( XtParent ( parent ) );
      break;
    case OPTIONS_SAVE:
      SaveCurrentOptions ( XtParent ( parent ) );
      break;
    case OPTIONS_RESTORE:
      RestoreDefaultOptions ( XtParent ( parent ) );
      break;
  }
}

/***********
 Creation
**********/

void
Cre_Options_Pulldown ( parent )
Widget parent;
{
  Widget OptionsMenu;

  /***
  create options menu
  ***/
print_debug(1);
  OptionsMenu = XmCreatePulldownMenu ( parent, "PullDown", NULL, 0 );

/* */
  if ( parent != top_bar ) {
    XtVaSetValues ( OptionsMenu, XmNtearOffModel, XmTEAR_OFF_ENABLED, NULL);
  }
/** **/

  /***
  create options button
  ***/
  {
    XmString xstr = XmStringCreateLocalized ( "Options" );
print_debug(2);
print_debug(3);
    OptionsPullDown = XtVaCreateManagedWidget ( "Options",
        /* 
        xmCascadeButtonWidgetClass,   parent,
        */
        xmCascadeButtonGadgetClass,   parent,
        XmNlabelString,               xstr,
        XmNsubMenuId,                 OptionsMenu,
        NULL );
print_debug(4);
    XmStringFree ( xstr );

  }

/***
printf("OptionsPullDown  - %d\n", OptionsPullDown );fflush(stdout);
***/

  /***
  create menu items
  ***/
  {
    Widget but;
    int i;
    static struct help_struct NewOptions_help_data;

print_debug(5);
    NewOptions_help_data.type   = DIALOG_HELP;
    NewOptions_help_data.width  = 425;
    NewOptions_help_data.height = 275;  
    NewOptions_help_data.text   = "\
Options allow the user to customise various aspects of the B-Toolkit.\n\
The settings are automatically saved for each development directory,\n\
and restored when the toolkit is next invoked in that directory.\n\n\
The current Options settings may be saved/restored globally in/from\n\
the $HOME/.BToolkitrc file.\n\n\
Note, however, that Optional Utilities are not saved/restored globally,\n\
since such utilities are particular to a specific development directory.\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes      Options.";  

print_debug(6);
    for ( i = 0; i < tot_Options; i++ ) {

     if ( ( i == 9 ) || ( i == 11 ) ) {

print_debug(7);
        XtVaCreateManagedWidget ( options [ i ],
            xmSeparatorGadgetClass,      OptionsMenu,
            XmNmarginWidth,              25,
             NULL );
      }

print_debug(8);
      but = XtVaCreateManagedWidget ( options [ i ],
          xmPushButtonGadgetClass,     OptionsMenu,
          XmNmarginWidth,              10,
          NULL );
print_debug(9);
      XtAddCallback ( but, XmNactivateCallback,
          ( XtCallbackProc ) TopBar_Options_CB,
          ( XtPointer ) & c_arr [ i ] );
    }

print_debug(10);
    XtVaCreateManagedWidget ( "Options",
        xmSeparatorGadgetClass,      OptionsMenu,
        XmNmarginWidth,              25,
        NULL );
print_debug(11);
    but = XtVaCreateManagedWidget ( "Help",
        xmPushButtonGadgetClass,     OptionsMenu,
        XmNmarginWidth,              10,
        NULL );
print_debug(12);
    XtAddCallback ( but, XmNactivateCallback,
        ( XtCallbackProc ) Popup_Help_CB,
        ( XtPointer ) & NewOptions_help_data );
  }
print_debug(13);
}



/**********************************************
        Top Bar Interrupt Callback
**********************************************/

XtCallbackProc
TopBar_Interrupt_CB ()
{
  int pib;
  int c;
  FILE * Bpib;
  int read_ok = 0;
  int t = 0;

  while ( ( ! read_ok ) && t < 5 ) {
    Bpib = fopen ( ".Bpib", "r" );
    if ( Bpib != NULL ) {
      XtSetSensitive ( InterruptPullDown, False );
      sleep ( 1 );
      pib = 0;
      c = getc ( Bpib );
      while ( c != EOF && c != '\n' )  {
        pib = ( pib * 10 ) + c - '0';
        c = getc ( Bpib );
      }
      fclose ( Bpib );
      if ( c == '\n' ) read_ok = 1;   /* read the whole thing */
    }
    if ( ! read_ok ) { sleep ( 1 ); t++; }
  }
  if ( pib ) {
    if ( bell_option ) XBell ( display, 10 );
    interrupt_option = 1;
    kill ( pib, SIGUSR2 );
    XtSetSensitive ( InterruptPullDown, True );
  }
  else {
    XtSetSensitive ( InterruptPullDown, True );
    interrupt_option = 0;
    Popup_Info ( "Currently unable to interrupt - retry " ); 
  }
}

/**********************************************
        Top Bar Help
**********************************************/

/***********
 Callback
**********/
XtCallbackProc
TopBar_Help_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  char cmd [ 500 ];
  char p_string [ 1000 ];
  int Hypertext_Text_Option;
  char buf [ 150 ];  /* don't want the global buf */
  char* browserCommand;

#ifdef COUNT_WWW

  COUNT_25_flag = ( ! cs_nn );

#endif /* COUNT_WWW */


#ifdef WWW_VERSION

  WWWConstructsCycleCheck ( 1 );

#endif /* WWW_VERSION */


  valIth_flags ( &Hypertext_Text_Option, Hypertext_text_num );
  Retrieve_String ( htx_viewer_str_num, buf );

  if ( strcmp ( buf, "" ) == 0 ) {
    Popup_Err ( 0, "Hypertext Viewer not set - check TopBar Options" );
    return;
  }

  if ( Hypertext_Text_Option ) {
  
    /* : DisplayCurrWinText ( "\n  Displaying Help in ASCII format\n" );*/
    Popup_Info ( "Displaying Help in ASCII format" );
    
    strcpy ( cmd, "$BKIT/BLIB/Html1 < $BKIT/BHELP/" );
    strcat ( cmd, ( char * ) client_data );
    strcat ( cmd, ".html | $BKIT/BLIB/Html2 | $BKIT/BLIB/Html3 | $BKIT/BLIB/Html4 | $BKIT/BLIB/Html5 > .Bhlp" );
/***
printf("|%s|\n",cmd);
***/
    if ( system ( cmd ) != 0 ) {
      DisplayCurrWinText ( "\n  Can't execute:\n    \"" );
      DisplayCurrWinText ( cmd );
      DisplayCurrWinText ( "\"\n\n" );
      return;
    }
    
    /* - use more intelligent command line caller for browsers: */
    
    /*
    strcpy ( cmd, buf );
    strcat ( cmd, " .Bhlp& \n echo $! > .Bed" );
    */
    
    browserCommand=getBrowserCommandLine(buf,".Bhlp");
    strcpy ( cmd, browserCommand );
    free(browserCommand);
    strcat ( cmd, " & \n echo $! > .Bed" );
    
    system(cmd);
  }
  else {
    sprintf ( secondary_string, "Launching %s for Help", buf );
    Popup_Info ( secondary_string );
/*
    DisplayCurrWinText ( "\n  Launching " );    
    DisplayCurrWinText ( buf );    
    DisplayCurrWinText ( "\n" );
*/
    /* - use more intelligent command line caller for browsers: */
    /*
    strcpy ( p_string, buf );
    strcat ( p_string, " " );
    strcat ( p_string, BKIT_path );
    strcat ( p_string, "/BHELP/" );
    strcat ( p_string, ( char * ) client_data );
    strcat ( p_string, ".html & \n echo $! > .Bed" );
    system ( p_string );
    */
    
    strcpy ( p_string, BKIT_path );
    strcat ( p_string, "/BHELP/" );
    strcat ( p_string, ( char * ) client_data );
    strcat ( p_string, ".html" );
    
    browserCommand=getBrowserCommandLine(buf,p_string);
    strcpy ( p_string, browserCommand );
    free(browserCommand);
    strcat ( p_string, " & \n echo $! > .Bed" );
    
    system ( p_string );
  }
}

/***********
 Creation
**********/

Widget
Cre_Help_Pulldown ( parent, menu_title, items )
Widget parent;
char * menu_title;
MenuItem * items;
{
  Widget pull_down, cascade, widget;
  size_t i;
  XmString str;

/* Pulldown menus are built from cascade buttons, so this function
 * also includes pullright menus.  Create the menu, the cascade button
 * that owns the menu, and then the submenu items.
*/

  pull_down = XmCreatePulldownMenu ( parent, "PullDown", NULL, 0 );
  if ( parent != top_bar ) {
    XtVaSetValues ( pull_down, XmNtearOffModel, XmTEAR_OFF_ENABLED, NULL);
  }
  str = XmStringCreateLocalized ( menu_title );
  cascade = XtVaCreateManagedWidget ( menu_title,
      xmCascadeButtonGadgetClass,     parent,
      XmNsubMenuId,                   pull_down,
      XmNlabelString,                 str,
      NULL);
  XmStringFree ( str );

  /* Now add the menu items */
  for ( i = 0 ; items  [ i ] . label != ( XtPointer ) NULL ; i++ ) {
    /* If subitems exist, create the pull-right menu by calling this
     * function recursively.  Since the function returns a cascade
     * button, the widget returned is used.
    */
    if ( items [ i ] . subitems != NULL ) {
      widget = Cre_Help_Pulldown ( pull_down, items [ i ] . label, 
                items [ i ] . subitems );
    }
    else {
      widget = XtVaCreateManagedWidget ( items [ i ] . label,
          xmPushButtonGadgetClass,         pull_down,
          XmNmarginWidth,                  10, /* IHS */
          NULL );
      str = XmStringCreateLocalized ( items [ i ] . labelR );
      XtVaSetValues ( widget, XmNacceleratorText, str, NULL );
      XmStringFree ( str );
      XtAddCallback( widget,  XmNactivateCallback,
          ( XtCallbackProc ) TopBar_Help_CB,
          ( XtPointer ) items [ i ] . client_data );
    }
  }
  return cascade;
}

/**********************************************************************
                      SourceControl
***********************************************************************/

void
Cre_SourceControl_Dialog ( create_flag, num_but )
int create_flag, num_but;
{
  static Widget dialog_form,
                radio_box, radio_box_frame,
                B_logo,
                sep,
                och_o, och_c, och_h, och_form,
                label;
  static struct help_struct       help_data;
  static struct ok_cancel_but_struct ok_but_data;
  static struct ok_cancel_but_struct cancel_but_data;
  static Atom WM_DELETE_WINDOW;
  struct SourceControlStruct * SC_1;
  int i;
  char buf [ 150 ];  /* don't want the global buf */

  if ( create_flag ) {

    /***
    set labels
    ***/
    SC_1 = SC_0;
    for ( i = 0 ; i < num_but ; i++ ) {
      strcpy ( radio_labels [ i ], SC_1 -> but_name );
      SC_1++;
    }

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & top_level, & SC_dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          num_but,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
		          & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    XtVaSetValues ( och_c,
        XmNleftAttachment,       XmATTACH_NONE,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNrightOffset,          12,
        NULL );
    XtUnmanageChild ( och_h );

    DisplayCurrWinText ( "\n  Source Control installation succeeded\n" );

  }

  else { /* if ( create_flag ) */

    struct stat stat_buf;

    /***
    (re)create label
    ***/
    strcpy ( primary_string, "Source Control" );
    Retrieve_String ( source_control_str_num, buf );
    sprintf ( str_buf, "Directory: %s", buf );
    Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label, str_buf );

    second_visit = 0;
    global_file_diff_but = 999;
    radiobox_flag = source_control_radiobox;
    XtManageChild ( B_logo );
    XtManageChild ( label );
    XtManageChild ( radio_box );
    XtManageChild ( radio_box_frame );
    XtManageChild ( och_form );
    XtManageChild ( dialog_form );
    XtPopup ( SC_dialog, XtGrabNone );
    XmUpdateDisplay ( SC_dialog );

    if ( ! ( strlen ( buf ) ) ) {
      Popup_Minor_Err ( top_level, "Warning: TopBar Options->Source Control not set" );
    }
    else if ( stat ( buf, &stat_buf ) == -1 ) {
      sprintf ( str_buf, "Warning: %s does not exist", buf );
      Popup_Minor_Err ( top_level, str_buf );
    }
    else {
      if ( S_ISDIR ( stat_buf . st_mode ) == 0 ) {
        sprintf ( str_buf, "Warning: %s is not a directory", buf );
        Popup_Minor_Err ( top_level, str_buf );
      }
    }
  }

}

void
Popup_SourceControl_Execute ()
{
  if ( SC_dialog != ( Widget ) NULL )
    Cre_SourceControl_Dialog ( /* create_flag = */ 0, /* num_but = */ 0 );
}

void
Popup_SourceControl_Setup ()
{
#define sc_Setup_text "\
    Enables the user-defined use of source control within the B-Toolkit.\n\
    The file $HOME/.Bsc comprises a list of triples - the button-name,\n\
    the button-action and the effect of the action: CHECKED_IN,\n\
    CHECKED_OUT or UNCHANGED. Each entry should appear on\n\
    a separate line, empty lines are permitted\n\n\
    The B-Toolkit builds a dialog from the button-name/button action,\n\
    invoked via TopBar Construct->Source Control.\n\n\
    The button-actions may comprise an external program to execute or\n\
    commands in the form of a Bourne shell script. The variable Bscdir\n\
    may be used, and is taken from the development's Source Control\n\
    path setting in the Top Bar Options.\n\n\
    It is essential that the button-action returns the correct status of\n\
    the action in the variable Bstatus; if this is not correctly done\n\
    the status of the construct in the toolkit will not tally with that\n\
    of the construct in the Source Control directory.\n\n\
    The example script shows the default RCS settings:\n\n\
            Check Log\n\
            rlog $Bscdir/$1; Bstatus=$?\n\
            UNCHANGED\n\n\
            Check Out Into SRC For Edit\n\
            co -l $Bscdir/$1; Bstatus=$?; cp -f $Bscdir/$1 SRC\n\
            CHECKED_OUT\n\n\
            Check Out Into SRC Read Only\n\
            co $Bscdir/$1; Bstatus=$?; cp -f $Bscdir/$1 SRC\n\
            UNCHANGED\n\n\
            Check In From CFG\n\
            cp CFG/$1 $Bscdir; ci $Bscdir/$1; Bstatus=$?\n\
            CHECKED_IN\n\n\
o `Edit' opens an editor containing $HOME/.Bsc; if the file does\n\
  not exist, options for defaults for RCS, defaults for SCCS or\n\
  an empty file are offered.\n\n\
o `Check' ensures the file comprises a list of triples, with each entry\n\
  appearing on a separate line.\n\n\
o `Install' builds the Source Control dialog, invoked via\n\
   TopBar Construct->Source Control, provided that the syntax of\n\
   the file is correct; an existing Source Control dialog is replaced.\n\n\
o `Close' closes the editor (no checking is done, and the\n\
   script is not installed).\n\n\
See Top Bar Help `Source Control' for a fuller discusion (to follow)."

#define sc_Setup_width  450
#define sc_Setup_height 550

  static Widget dialog_form,
                radio_box, radio_box_frame,
                B_logo,
                sep,
                och_o, och_c, och_h, och_form,
                label;
  static struct help_struct       help_data;
  static struct ok_cancel_but_struct ok_but_data;
  static struct ok_cancel_but_struct cancel_but_data;
  static Atom WM_DELETE_WINDOW;

  if ( !SC_setup_dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Edit " );
    strcpy ( radio_labels [ 1 ], " Check " );
    strcpy ( radio_labels [ 2 ], " Install " );
    strcpy ( radio_labels [ 3 ], " Close " );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & top_level, & SC_setup_dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          4,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) sc_Setup_text;
    help_data.width  = sc_Setup_width;
    help_data.height = sc_Setup_height;

  }

  /***
  Static SC_setup_dialog now exists - (re)create label
  ***/
  strcpy ( primary_string, "Source Control" );
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label, "Setup $HOME/.Bsc" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  radiobox_flag = source_control_setup_radiobox;
  Manage_RadioBox_Dialog;
  XtPopup ( SC_setup_dialog, XtGrabNone );
  XmUpdateDisplay ( SC_setup_dialog );
}

void
Popup_SourceControl_DefaultEdit ()
{
#define sc_default_edit_text "\
    The file $HOME/.Bsc does not exist - it may be initialised\n\
    in one of the three ways indicated.\n\n\
    For a full explanation see Top Bar Help `Source Control'"
#define sc_default_edit_width  375
#define sc_default_edit_height 175

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Defaults for RCS " );
    strcpy ( radio_labels [ 1 ], " Defaults for SCCS " );
    strcpy ( radio_labels [ 2 ], " Empty File " );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & top_level, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          3,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) sc_default_edit_text;
    help_data.width  = sc_default_edit_width;
    help_data.height = sc_default_edit_height;

  }

  /***
  Static dialog now exists - (re)create label
  ***/
  strcpy ( primary_string, "Source Control" );
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label, "Initialise $HOME/.Bsc" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  radiobox_flag = source_control_edit_radiobox;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}



#define Anm_Multi_Input_label_MAX 1502

int Anm_Multi_Input_fld_ident [ MAX_ANM_MULTI_INPUT_FLD ];
Widget Anm_Multi_Input_text   [ MAX_ANM_MULTI_INPUT_FLD ];
char Anm_Multi_Input_label    [ MAX_ANM_MULTI_INPUT_FLD ] [  Anm_Multi_Input_label_MAX ];
int Anm_Multi_Input_enum_i    [ MAX_ANM_MULTI_INPUT_FLD ];
int Anm_Multi_Input_tot;

/***********************************************************************
************************************************************************
                       Animator
************************************************************************
***********************************************************************/

int
Anm_Multi_Input_unknwn_ok ( idx )
int idx;
{
  char * text;
  int ll;

  text = XmTextFieldGetString ( Anm_Multi_Input_text [ idx ] );
/***
printf ( "idx %d - str checking |%s|\n", idx, text );
***/
  ll = strlen ( text );
  if ( ! ll ) {
    XtFree ( text );
    sprintf ( buf, "Text for %s is empty", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  if ( ll > Anm_Multi_Input_label_MAX - 2 ) {
    XtFree ( text );
    sprintf ( buf, "String for %s too long (max &d)", Anm_Multi_Input_label [ idx ], Anm_Multi_Input_label_MAX - 2 );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  if ( ! FormulaParses ( text ) ) {
    XtFree ( text );
    sprintf ( buf, "%s: parse error", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  XtFree ( text );
  return 1;
}

int
Anm_Multi_Input_str_ok ( idx )
int idx;
{
  char * text;
  int ll;

  text = XmTextFieldGetString ( Anm_Multi_Input_text [ idx ] );
/***
printf ( "idx %d - str checking |%s|\n", idx, text );
***/
  ll = strlen ( text );
  XtFree ( text );
  if ( ! ll ) {
    sprintf ( buf, "Text for %s is empty", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  if ( ll > 248 ) {
    sprintf ( buf, "String for %s too long (max 150)", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  return 1;
}

int
Anm_Multi_Input_chr_ok ( idx )
int idx;
{
  char * text;
  int ll;

  text = XmTextFieldGetString ( Anm_Multi_Input_text [ idx ] );
/***
printf ( "idx %d - chr checking |%s|\n", idx, text );
***/
  if ( ( strcmp ( text, "B_SOH" ) == 0 ) ||
       ( strcmp ( text, "B_STX" ) == 0 ) ||
       ( strcmp ( text, "B_ETX" ) == 0 ) ||
       ( strcmp ( text, "B_EOT" ) == 0 ) ||
       ( strcmp ( text, "B_ENQ" ) == 0 ) ||
       ( strcmp ( text, "B_ACK" ) == 0 ) ||
       ( strcmp ( text, "B_BEL" ) == 0 ) ||
       ( strcmp ( text, "B_BS" ) == 0 ) ||
       ( strcmp ( text, "B_HT" ) == 0 ) ||
       ( strcmp ( text, "B_LF" ) == 0 ) ||
       ( strcmp ( text, "B_VT" ) == 0 ) ||
       ( strcmp ( text, "B_FF" ) == 0 ) ||
       ( strcmp ( text, "B_CR" ) == 0 ) ||
       ( strcmp ( text, "B_SO" ) == 0 ) ||
       ( strcmp ( text, "B_SI" ) == 0 ) ||
       ( strcmp ( text, "B_DLE" ) == 0 ) ||
       ( strcmp ( text, "B_DC1" ) == 0 ) ||
       ( strcmp ( text, "B_DC2" ) == 0 ) ||
       ( strcmp ( text, "B_DC3" ) == 0 ) ||
       ( strcmp ( text, "B_DC4" ) == 0 ) ||
       ( strcmp ( text, "B_NAK" ) == 0 ) ||
       ( strcmp ( text, "B_SYN" ) == 0 ) ||
       ( strcmp ( text, "B_ETB" ) == 0 ) ||
       ( strcmp ( text, "B_CAN" ) == 0 ) ||
       ( strcmp ( text, "B_EM" ) == 0 ) ||
       ( strcmp ( text, "B_SUB" ) == 0 ) ||
       ( strcmp ( text, "B_ESC" ) == 0 ) ||
       ( strcmp ( text, "B_EXCL" ) == 0 ) ||
       ( strcmp ( text, "B_QUOT" ) == 0 ) ||
       ( strcmp ( text, "B_HSH" ) == 0 ) ||
       ( strcmp ( text, "B_DOLL" ) == 0 ) ||
       ( strcmp ( text, "B_PCT" ) == 0 ) ||
       ( strcmp ( text, "B_AMP" ) == 0 ) ||
       ( strcmp ( text, "B_SQUOT" ) == 0 ) ||
       ( strcmp ( text, "B_OPAR" ) == 0 ) ||
       ( strcmp ( text, "B_CPAR" ) == 0 ) ||
       ( strcmp ( text, "B_MUL" ) == 0 ) ||
       ( strcmp ( text, "B_PLUS" ) == 0 ) ||
       ( strcmp ( text, "B_COM" ) == 0 ) ||
       ( strcmp ( text, "B_MINUS" ) == 0 ) ||
       ( strcmp ( text, "B_DOT" ) == 0 ) ||
       ( strcmp ( text, "B_DIV" ) == 0 ) ||
       ( strcmp ( text, "B_COL" ) == 0 ) ||
       ( strcmp ( text, "B_SCOL" ) == 0 ) ||
       ( strcmp ( text, "B_LESS" ) == 0 ) ||
       ( strcmp ( text, "B_EQL" ) == 0 ) ||
       ( strcmp ( text, "B_GTR" ) == 0 ) ||
       ( strcmp ( text, "B_QUERY" ) == 0 ) ||
       ( strcmp ( text, "B_CADD" ) == 0 ) ||
       ( strcmp ( text, "B_OBRK" ) == 0 ) ||
       ( strcmp ( text, "B_SLSH" ) == 0 ) ||
       ( strcmp ( text, "B_CBRK" ) == 0 ) ||
       ( strcmp ( text, "B_HAT" ) == 0 ) ||
       ( strcmp ( text, "B_UNL" ) == 0 ) ||
       ( strcmp ( text, "B_BSQ" ) == 0 ) ||
       ( strcmp ( text, "B_OBRC" ) == 0 ) ||
       ( strcmp ( text, "B_BAR" ) == 0 ) ||
       ( strcmp ( text, "B_CBRC" ) == 0 ) ||
       ( strcmp ( text, "B_TLD" ) == 0 ) ||
       ( strcmp ( text, "B_DEL" ) == 0 )    ) {
    XtFree ( text );
    return 1;
  }
  if ( strlen ( text ) != 1 ) {
    XtFree ( text );
    sprintf ( buf, " %s: not a single character", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  if ( ( text [ 0 ] < ( char ) 32 ) || ( text [ 0 ] > ( char ) 126 ) ) {
    XtFree ( text );
    sprintf ( buf, " %s: not a character", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  if ( ! FormulaParses ( text ) ) {
    XtFree ( text );
    sprintf ( buf, "%s: parse error", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  XtFree ( text );
  return 1;
}

int
Anm_Multi_Input_bts_ok ( idx )
int idx;
{
  char * text;
  int i, ll, is_bts_error;
  unsigned n;

  text = XmTextFieldGetString ( Anm_Multi_Input_text [ idx ] );
/***
printf ( "idx %d - bts checking |%s|\n", idx, text );
***/
  ll = strlen ( text );
  if ( ! ll ) {
    XtFree ( text );
    sprintf ( buf, "Text for %s is empty", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  if ( ll > 32 ) {
    XtFree ( text );
    sprintf ( buf, "%s: bitstring too long (max 32)", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  i = 0;
  n = 0;
  is_bts_error = 0;
  while ( i < ll ) {
    if ( text [ i ] != '0' && text [ i ] != '1' ) is_bts_error = 1;
    n = ( 10 * n ) + text [ i ] - '0';
    i++;
  }
  if ( is_bts_error ) {
    XtFree ( text );
    sprintf ( buf, "%s: bitstring not composed of 0/1's", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  if ( n > 2147483646 ) {
    XtFree ( text );
    sprintf ( buf, "%s: bitstring too long (max 32)", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  if ( ! FormulaParses ( text ) ) {
    XtFree ( text );
    sprintf ( buf, "%s: parse error", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  XtFree ( text );
  return 1;
}

int
Anm_Multi_Input_num_ok ( idx )
int idx;
{
  char * text;
  int i, is_num_error, ll;
  unsigned n;

  text = XmTextFieldGetString ( Anm_Multi_Input_text [ idx ] );
/***
printf ( "idx %d - checking |%s|\n", idx, text );
***/
  ll = strlen ( text );
  if ( ! ll ) {
    XtFree ( text );
    sprintf ( buf, "Text for %s is empty", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  if ( ll > 10 ) {
    XtFree ( text );
    sprintf ( buf, "%s: not a natural number", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  is_num_error = 0;
  n = 0;
  i = 0;
  while ( i < ll ) {
    if ( text [ i ] < '0' || text [ i ] > '9' ) is_num_error = 1;
    n = ( n * 10 ) + text [ i ] - '0';
    i++;
  }
  if ( is_num_error ) {
    XtFree ( text );
    sprintf ( buf, "%s: not a natural number", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  if ( n > 214748364 ) {
    XtFree ( text );
    sprintf ( buf, "%s: not a natural number", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  if ( ! FormulaParses ( text ) ) {
    XtFree ( text );
    sprintf ( buf, "%s: parse error", Anm_Multi_Input_label [ idx ] );
    Popup_Minor_Err ( top_level, buf );
    return 0;
  }
  XtFree ( text );
  return 1;
}


void
Anm_Multi_Input_Dialog_Abort_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  XtPopdown ( ( Widget )  client_data );
  XtDestroyWidget ( ( Widget )  client_data );
  strcpy ( fifo_write_buf, "0:" );
  Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
  InvokeB ( without_XTerm, 1 );
}

void
Anm_Multi_Input_Dialog_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  int i, ok;
  char * text;
  FILE * Bcom;

  i = 0;
  ok = 1;
  while ( ( ok ) && ( i < Anm_Multi_Input_tot ) ) {
/***
printf ( "checking idx %d - %d\n", i, Anm_Multi_Input_fld_ident [ i ] );
***/
    switch ( Anm_Multi_Input_fld_ident [ i ] ) {
    case Anm_Multi_Input_fld_is_num :
      ok = Anm_Multi_Input_num_ok ( i );
      break;
    case Anm_Multi_Input_fld_is_str :
      ok = Anm_Multi_Input_str_ok ( i );
      break;
    case Anm_Multi_Input_fld_is_chr :
      ok = Anm_Multi_Input_chr_ok ( i );
      break;
    case Anm_Multi_Input_fld_is_bts :
      ok = Anm_Multi_Input_bts_ok ( i );
      break;
    case Anm_Multi_Input_fld_unknwn :
      ok = Anm_Multi_Input_unknwn_ok ( i );
      break;
    case Anm_Multi_Input_fld_is_enm :
      break;
    }
    i++;
  }

  if ( ok ) {
    strcpy ( str_buf, "(?" );
    i = 0;
    while ( i < Anm_Multi_Input_tot ) {
      switch ( Anm_Multi_Input_fld_ident [ i ] ) {
      case Anm_Multi_Input_fld_is_num :
        text = XmTextFieldGetString ( Anm_Multi_Input_text [ i ] );
        strcat ( str_buf, ",(" );
        strcat ( str_buf,  Anm_Multi_Input_label [ i ] );
        strcat ( str_buf, "<--(" );
        strcat ( str_buf, text );
        strcat ( str_buf, "))" );
        XtFree ( text );
        break;
      case Anm_Multi_Input_fld_is_str :
        text = XmTextFieldGetString ( Anm_Multi_Input_text [ i ] );
        strcat ( str_buf, ",(\"" );
        strcat ( str_buf,  Anm_Multi_Input_label [ i ] );
        strcat ( str_buf, "<--(" );
        strcat ( str_buf, text );
        strcat ( str_buf, "\"))" );
        XtFree ( text );
        break;
    case Anm_Multi_Input_fld_is_chr :
        text = XmTextFieldGetString ( Anm_Multi_Input_text [ i ] );
        strcat ( str_buf, ",(" );
        strcat ( str_buf,  Anm_Multi_Input_label [ i ] );
        strcat ( str_buf, "<--(" );
        strcat ( str_buf, text );
        strcat ( str_buf, "))" );
        XtFree ( text );
        break;
      case Anm_Multi_Input_fld_is_bts :
        text = XmTextFieldGetString ( Anm_Multi_Input_text [ i ] );
        strcat ( str_buf, ",(" );
        strcat ( str_buf,  Anm_Multi_Input_label [ i ] );
        strcat ( str_buf, "<--(\"" );
        strcat ( str_buf, text );
        strcat ( str_buf, "\"))" );
        XtFree ( text );
        break;
      case Anm_Multi_Input_fld_is_enm :
        sprintf ( buf, "%d", Anm_Multi_Input_enum_i [ i ] + 1 );
        strcat ( str_buf, ",(" );
        strcat ( str_buf,  Anm_Multi_Input_label [ i ] );
        strcat ( str_buf, "<--(" );
        strcat ( str_buf, buf );
        strcat ( str_buf, "))" );
        break;
      case Anm_Multi_Input_fld_unknwn :
        text = XmTextFieldGetString ( Anm_Multi_Input_text [ i ] );
        strcat ( str_buf, ",(" );
        strcat ( str_buf,  Anm_Multi_Input_label [ i ] );
        strcat ( str_buf, "<--(" );
        strcat ( str_buf, text );
        strcat ( str_buf, "))" );
        XtFree ( text );
        break;
      }
      i++;
    }
    strcat ( str_buf, ")" );
/***
DisplayCurrWinText ( "\nAnm_Multi_Input_Dialog_CB str_buf `" );
DisplayCurrWinText ( str_buf );
DisplayCurrWinText ( "'\n" );
***/
    if ( FormulaParses ( str_buf ) ) {
      XtPopdown ( ( Widget )  client_data );
      XtDestroyWidget ( ( Widget )  client_data );
      sprintf ( fifo_write_buf, "%s:", str_buf );
      Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
      InvokeB ( without_XTerm, 1 );
    }
    else {
      Popup_Err ( "  Parse error  " );
    }
  }
}


XtCallbackProc
Anm_Multi_Input_Enum_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  int found = 0;
  i = 0;
  while ( ! found && i < MAX_ANM_MULTI_INPUT_FLD ) {
    if ( XtParent ( widget ) == Anm_Multi_Input_text [ i ] ) found = 1;
    if ( ! found ) i++;
  }
  Anm_Multi_Input_enum_i [ i ] = * ( int * ) client_data;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Anm_Multi_Input_Text_CB ( text_w, client_d )
Widget text_w;
XtPointer client_d;
{
  XmProcessTraversal ( text_w, XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_Anm_Multi_Input_Form_Format_Error ( nn )
int nn;
{
  sprintf ( buf, "\n  Anm_Multi_Input format error %d\n", nn );
  DisplayCurrWinText ( buf );
  Popup_Err ( 0, "  Unable to complete current job " );
}

void
Cre_Anm_Multi_Input_Form ( anm_Anm_Multi_Input_flag )
int anm_Anm_Multi_Input_flag;

/*** taken from Animator.src ***/
#define mch_param_input_type 1
#define mch_ctx_input_type   2
#define op_param_input_type  3
#define state_var_input_type 4
#define local_var_input_type 5

{
  Widget dialog, dialog_form, sep, B_logo, but,
         och_form, och_o, och_a,  och_h, label, form_scroll,
         form, left_rc, right_rc, pull_down;
  XmString xstr;
  static struct help_struct help_data;
  FILE * Bcom;
  Arg args [ 10 ];
  int idx, c, i, n;
  static struct coord coord_data;

  coord_data.x = 0; /* not used */
  if ( ( anm_Anm_Multi_Input_flag == op_param_input_type )  ||
       ( anm_Anm_Multi_Input_flag == local_var_input_type )    )
    coord_data.y = 1;
  else
    coord_data.y = 300;

  /***
  TMP/.Bcom contains -
  format: label|nn|Prompt string|xxx|nn|Prompt string|xxx|...|
    xxx is either default text (not is_enm)
           or enm1,enm2,enm3   (is_enm)
    nn = 1 => is_num
    nn = 2 => is_str
    nn = 3 => is_chr
    nn = 4 => is_bts
    nn = 5 => is_enm
  ***/

#define Anm_Multi_Input_help_text "\
o SETS may be left uninstantiated (but this may make the subsequent\n\
  animation unrealistic); if they are to be instantiated, they should\n\
  be entered in the form: {elem1,elem2,elem3}\n\n\
o CHARACTERS should be entered as single characters without quotes,\n\
  but the special charaters defined in String_TYPE (B_EXCL, etc.)\n\
  should be entered as their String_TYPE definition;\n\
  in the former case, they are automatically converted to B_EXCL, etc..\n\n\
o BITSTRINGS should be entered with quotes, for example \"0101\""

#define Anm_Multi_Input_help_width  475
#define Anm_Multi_Input_help_height 225

  help_data.type   = DIALOG_HELP;
  help_data.text   = ( char * ) Anm_Multi_Input_help_text;
  help_data.width  = Anm_Multi_Input_help_width;
  help_data.height = Anm_Multi_Input_help_height;

/***
printf ( "Cre_Anm_Multi_Input_Form ( %d )\n", anm_Anm_Multi_Input_flag );
***/


  XtDestroyWidget ( constructs_rc );  /* 11.98 */
  constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
      xmRowColumnWidgetClass,         constructs_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 18,
      XmNmarginHeight,                10,
      XmNspacing,                     0,
      XmNresizable,                   True,
      NULL );
  XmUpdateDisplay ( constructs_rc );
  XmUpdateDisplay ( constructs_scroll );
  XmUpdateDisplay ( constructs_form );

  /***
  create sub_frame1 in constructs_rc
  ***/
  sub_frame1 = XtVaCreateWidget ( "Canvas",
    xmFrameWidgetClass,          constructs_rc,
    XmNshadowType,               XmSHADOW_OUT,
    NULL );

  /***
  create sub_text1 in sub_frame1
  ***/
  /*
  WAS: @ 5.1.12
  sub_text1 = XtVaCreateWidget ( "Anm",
      xmTextWidgetClass,           sub_frame1,
      XmNcursorPositionVisible,    False,
      XmNeditable,                 False,
      XmNeditMode,                 XmMULTI_LINE_EDIT,
      XmNresizeHeight,             True,
      XmNresizeWidth,              True,
      XmNmarginWidth,              7,
      XmNmarginHeight,             7,
      XmNborderWidth,              0,
      XmNshadowThickness,          0,
      NULL );

  LoadFileIntoBuf ( ".Bsb1", buf, MAX_buf - 1 );
  XmTextSetString ( sub_text1, buf );
  */

LoadFileIntoBuf ( ".Bsb1", buf, MAX_buf - 1 );

sub_text1 = XtVaCreateWidget ( "Anm",
      xmTextWidgetClass,           sub_frame1,
      XmNcursorPositionVisible,    False,
      XmNeditable,                 False,
      XmNeditMode,                 XmMULTI_LINE_EDIT,
      XmNmarginWidth,              7,
      XmNmarginHeight,             7,
      XmNborderWidth,              0,
      XmNshadowThickness,          0,
      XmNwordWrap,                 False, /**/
      XmNscrollHorizontal,         False, /**/
      XmNscrollVertical,           False, /**/
      /*XmNvalue,			   buf,*/
      XmNresizeHeight,             True,
      XmNresizeWidth,              True,
      NULL );
      XmTextSetString ( sub_text1, buf );

  XtManageChild ( sub_text1 );
  XtManageChild ( sub_frame1 );

  if ( ( anm_Anm_Multi_Input_flag == op_param_input_type )  ||
       ( anm_Anm_Multi_Input_flag == local_var_input_type )    ) {

    /***
    create sub_frame2 in constructs_rc
    ***/
    sub_frame2 = XtVaCreateWidget ( "Canvas",
      xmFrameWidgetClass,          constructs_rc,
      XmNshadowType,               XmSHADOW_OUT,
      NULL );

    /***
    create sub_text2 in sub_frame2
    ***/
    sub_text2 = XtVaCreateWidget ( "Anm",
       xmTextWidgetClass,           sub_frame2,
        XmNcursorPositionVisible,    False,
        XmNeditable,                 False,
        XmNeditMode,                 XmMULTI_LINE_EDIT,
        XmNwordWrap,                 False, /**/
        XmNscrollHorizontal,         False, /**/
        XmNscrollVertical,           False, /**/
        XmNmarginWidth,              7,
        XmNmarginHeight,             7,
        XmNborderWidth,              0,
        XmNshadowThickness,          0,
	XmNresizeHeight,             True,
        XmNresizeWidth,              True,
        NULL );

    LoadFileIntoBuf ( ".Bsb2", buf, MAX_buf - 1 );
    XmTextSetString ( sub_text2, buf );

    XtManageChild ( sub_text2 );
    XtManageChild ( sub_frame2 );
  }

  /***
  create sub_dummy
  manage constructs_rc
  XmScrollVisible
  ***/
  sub_dummy = XtVaCreateWidget ( "Canvas",
      xmFormWidgetClass,          constructs_rc,
      NULL );
  XtManageChild ( sub_dummy );

  XtManageChild ( constructs_rc );
  XtManageChild ( constructs_scroll );
  XmScrollVisible ( constructs_scroll, sub_dummy, 0, 0 );
  XmUpdateDisplay ( constructs_scroll );

  dialog = XmCreateDialogShell ( top_frame_form, "SelDialog", NULL, 0 );

  XtAddCallback ( dialog, XmNpopupCallback,
      ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
      ( XtPointer ) & coord_data );

  dialog_form = XtVaCreateWidget ( "SelDialog",
      xmFormWidgetClass,         dialog,
      XmNdialogStyle,            XmDIALOG_MODELESS,
      XmNdefaultPosition,        True,  
      XmNtraversalOn,            True,
      XmNautoUnmanage,           False,
      NULL );

  B_logo = XtVaCreateManagedWidget ( "SelDialog", 
      xmPushButtonWidgetClass,    dialog_form,
      XmNtopAttachment,           XmATTACH_FORM,
      XmNtopOffset,               8,
      XmNleftAttachment,          XmATTACH_FORM,
      XmNleftOffset,              8,
      XmNlabelType,               XmPIXMAP,
      XmNlabelPixmap,             B_framed_pixmap_gray94,
      XmNshadowThickness,         0,
      XmNmarginWidth,             0,
      XmNmarginHeight,            0,
      XmNtraversalOn,             False,
      NULL );

  XtAddCallback ( B_logo, XmNactivateCallback,
                                    ( XtCallbackProc ) B_info_CB, NULL );

  sep = XtVaCreateManagedWidget ( "SelDialog",
      xmSeparatorGadgetClass,         dialog_form,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  0,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 0,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                48,
      NULL );

  form_scroll = XtVaCreateWidget ( "SelDialog",
      xmScrolledWindowWidgetClass,    dialog_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   40,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 5,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  5,
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                sep,
      XmNbottomOffset,                10,
      XmNwidth,                       450, /* 2500,  */
      XmNheight,                      500,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNspacing,                     0,
      NULL );

  form = XtVaCreateWidget ( "SelDialog",
      xmFormWidgetClass,              form_scroll,
      XmNfractionBase,                /* 10, */ 25,
      XmNwidth,                       3500,
      NULL );

  left_rc = XtVaCreateWidget ( "ButtonLabel",
      xmRowColumnWidgetClass,         form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   5,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_POSITION,
      XmNrightPosition,               1,
      XmNrightOffset,                 3,
      XmNisAligned,                   True,
      XmNentryAlignment,              XmALIGNMENT_END,
      XmNtraversalOn,                 False,
      XmNspacing,                     13,
      NULL );

  right_rc = XtVaCreateWidget ( "SelDialog",
      xmRowColumnWidgetClass,         form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_POSITION,
      XmNleftPosition,                1,
      XmNleftOffset,                  0,
      XmNnavigationType,              XmTAB_GROUP,
      XmNisHomogeneous,               False,
      XmNspacing,                     5,
      NULL );

  och_form = XtVaCreateWidget ( "ButtonLabel",
      xmFormWidgetClass,       dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         5,
      NULL );

  och_o = XtVaCreateManagedWidget ( "OK", 
      xmPushButtonGadgetClass, och_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           12,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( och_o, XmNactivateCallback,
      ( XtCallbackProc ) Anm_Multi_Input_Dialog_CB,
      ( XtPointer ) dialog );

  if ( ( anm_Anm_Multi_Input_flag == op_param_input_type )  ||
       ( anm_Anm_Multi_Input_flag == state_var_input_type ) ||
       ( anm_Anm_Multi_Input_flag == local_var_input_type )    ) {
     och_a = XtVaCreateManagedWidget ( "Abort Operation", 
        xmPushButtonGadgetClass, och_form,
        XmNleftAttachment,       XmATTACH_WIDGET,
        XmNleftWidget,           och_o,
        XmNleftOffset,           75,
        XmNtopAttachment,        XmATTACH_FORM,
        XmNtopOffset,            3,
        XmNheight,               27,
        XmNwidth,                125,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   1,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XtAddCallback ( och_a, XmNactivateCallback,
        ( XtCallbackProc ) Anm_Multi_Input_Dialog_Abort_CB,
        ( XtPointer ) dialog );
  }
  else if ( ( anm_Anm_Multi_Input_flag == mch_param_input_type ) ||
            ( anm_Anm_Multi_Input_flag == mch_ctx_input_type )      ) {
     och_a = XtVaCreateManagedWidget ( "Abort Animation", 
        xmPushButtonGadgetClass, och_form,
        XmNleftAttachment,       XmATTACH_WIDGET,
        XmNleftWidget,           och_o,
        XmNleftOffset,           75,
        XmNtopAttachment,        XmATTACH_FORM,
        XmNtopOffset,            3,
        XmNheight,               27,
        XmNwidth,                130,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   1,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XtAddCallback ( och_a, XmNactivateCallback,
        ( XtCallbackProc ) Anm_Multi_Input_Dialog_Abort_CB,
        ( XtPointer ) dialog );
  }

  och_h = XtVaCreateManagedWidget ( "Help", 
      xmPushButtonGadgetClass, och_form,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          12,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( och_h, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Help_CB,
      ( XtPointer ) & help_data );

  Bcom = fopen ( "TMP/.Bcom", "r" );

   if ( Bcom == NULL ) {
     DisplayCurrWinText ( "\n  Can't open TMP/.Bcom for reading\n" );
     Popup_Err ( 0, "  Unable to complete current job " );
     strcpy ( fifo_write_buf, "0:" );
     Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
     InvokeB ( without_XTerm, 1 );
     return;
   }

   c = getc ( Bcom );
   i = 0;
   while ( ( c != EOF ) && ( c != '\n' ) ) {
     buf [ i++ ] = c;
     c = getc ( Bcom );
   }
   buf [ i ] = '\0';
/***
printf ( "00 buf: %s\n", buf ); fflush ( stdout );
***/
   xstr = XmStringCreateLtoR ( buf, charset );
   label = XtVaCreateManagedWidget ( "Label", 
      xmLabelWidgetClass,        dialog_form,
      XmNtopAttachment,          XmATTACH_FORM,
      XmNtopOffset,              5,
      XmNleftAttachment,         XmATTACH_WIDGET,
      XmNleftWidget,             B_logo,
      XmNleftOffset,             15,
      XmNlabelString,            xstr,
      XmNmarginWidth,            10,
      XmNmarginHeight,           10,
      XmNtraversalOn,            False,
      NULL );
   XmStringFree ( xstr );

   if ( c == EOF ) {
     Cre_Anm_Multi_Input_Form_Format_Error ( idx*10 + 0 );
     strcpy ( fifo_write_buf, "0:" );
     Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
     InvokeB ( without_XTerm, 1 );
     return;
   }
   idx = 0;
   c = getc ( Bcom );
   while ( c != EOF ) {
     if ( c == '\n' ) {
       Cre_Anm_Multi_Input_Form_Format_Error ( idx*10 + 1 );
       strcpy ( fifo_write_buf, "0:" );
       Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
       InvokeB ( without_XTerm, 1 );
       return;
     }
     Anm_Multi_Input_fld_ident [ idx ] = c - '0';
/***
printf ( "0 Anm_Multi_Input_fld_ident [ %d ]: %d\n", idx, Anm_Multi_Input_fld_ident [ idx ] ); fflush ( stdout );
***/
     c = getc ( Bcom );
     if ( c != '\n' ) {
       Cre_Anm_Multi_Input_Form_Format_Error ( idx*10 + 2 );
       strcpy ( fifo_write_buf, "0:" );
       Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
       InvokeB ( without_XTerm, 1 );
       return;
     }
     i = 0;
     c = getc ( Bcom );
     while ( ( c != EOF ) && ( c != '\n' ) ) {
       Anm_Multi_Input_label [ idx ] [ i++ ] = c;
       c = getc ( Bcom );
     }
     Anm_Multi_Input_label [ idx ] [ i ] = '\0';
/***
printf ( "1 read Anm_Multi_Input_label [ %d ]: %s\n", idx, Anm_Multi_Input_label [ idx ] ); fflush ( stdout );
***/
     if ( c == EOF ) {
       Cre_Anm_Multi_Input_Form_Format_Error ( idx*10 + 3 );
       strcpy ( fifo_write_buf, "0:" );
       Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
       InvokeB ( without_XTerm, 1 );
       return;
     }
     buf [ 0 ] = '\0';
     for ( i = strlen ( Anm_Multi_Input_label [ idx ] ) ; i < 11 ; i++ ) {
       strcat ( buf, "  " );
     }
     strcat ( buf, Anm_Multi_Input_label [ idx ] );
/***
printf ( " --- %d |%s| |%s|\n", idx, Anm_Multi_Input_label [ idx ], buf );
***/
     XtVaCreateManagedWidget ( buf,
         xmLabelWidgetClass,             left_rc,
         XmNrightPosition,               1,
         XmNrightOffset,                 3,
         XmNalignment,                   XmALIGNMENT_END,
         NULL );

     if ( Anm_Multi_Input_fld_ident [ idx ] == Anm_Multi_Input_fld_is_enm ) {
       c = getc ( Bcom );
       if ( c == '\n' ) {
         Cre_Anm_Multi_Input_Form_Format_Error ( idx*10 + 4 );
         strcpy ( fifo_write_buf, "0:" );
         Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
         InvokeB ( without_XTerm, 1 );
         return;
       }
       Anm_Multi_Input_text [ idx ] =
                    XmCreatePulldownMenu ( right_rc, "SelDialog", NULL, 0);
       xstr = XmStringCreateLtoR ( "", charset );
       n = 0;
       XtSetArg ( args [ n ], XmNsubMenuId, Anm_Multi_Input_text [ idx ] ); n++;
       XtSetArg ( args [ n ], XmNlabelString, xstr ); n++;
       XtSetArg ( args [ n ], XmNtraversalOn, True ); n++;
       XtSetArg ( args [ n ], XmNdefaultButtonShadowThickness, 1 ); n++;
       XtSetArg ( args [ n ], XmNhighlightThickness, 1 ); n++;
       XtSetArg ( args [ n ], XmNnavigationType, XmTAB_GROUP ); n++;
       XtSetArg ( args [ n ], XmNmarginHeight, 0 ); n++;
       pull_down = XmCreateOptionMenu ( right_rc, "", args, n );
       XtVaSetValues ( pull_down,
           XmNrightAttachment,             XmATTACH_FORM,
           XmNleftAttachment,              XmATTACH_POSITION,
           XmNleftPosition,                1,
           XmNalignment,                   XmALIGNMENT_END,
           XmNtraversalOn,                 True,
           XmNdefaultButtonShadowThickness,        1,
           XmNhighlightThickness,          1,
           XmNnavigationType,              XmTAB_GROUP,
           NULL );
       XmStringFree ( xstr );
       j = 0;
       while ( ( c != EOF ) && ( c != '\n' ) ) {
         k = 0;
         while ( ( c != EOF ) && ( c != ',' ) && ( c != '\n' ) ) {
           buf [ k++ ] = c;
           c = getc ( Bcom );
	 }
         buf [ k ] = '\0';
/***
printf ( "2 idx %d j %d buf: %s\n", idx, j, buf ); fflush ( stdout );
***/
         but =
            XtVaCreateManagedWidget ( buf,
                xmPushButtonGadgetClass,  Anm_Multi_Input_text [ idx ],
                NULL );
         XtAddCallback ( but, XmNactivateCallback,
                  ( XtCallbackProc ) Anm_Multi_Input_Enum_CB,
                  ( XtPointer ) & c_arr [ j ] );
         XtManageChild ( pull_down );
         j++;
         if ( c == ',' ) c = getc ( Bcom );
       }
       if ( c == EOF ) {
         Cre_Anm_Multi_Input_Form_Format_Error ( idx*10 + 5 );
         strcpy ( fifo_write_buf, "0:" );
         Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
         InvokeB ( without_XTerm, 1 );
         return;
       }
     }

     else {     /* Anm_Multi_Input_fld_ident [ idx ] != Anm_Multi_Input_fld_is_enm */
       c = getc ( Bcom );
       if ( c == '\n' ) {
         Cre_Anm_Multi_Input_Form_Format_Error ( idx*10 + 5 );
         strcpy ( fifo_write_buf, "0:" );
         Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
         InvokeB ( without_XTerm, 1 );
         return;
       }
       i = 0;
       while ( ( c != EOF ) && ( c != '\n' ) ) {
         buf [ i++ ] = c;
         c = getc ( Bcom );
       }
       buf [ i ] = '\0';
       Anm_Multi_Input_text [ idx ] = XtVaCreateManagedWidget ( "InputText",
           xmTextFieldWidgetClass,         right_rc,
           XmNtraversalOn,                 True,
           XmNmarginWidth,                 3,
           XmNmarginHeight,                3,
           NULL );
       if ( strcmp ( buf, "?" ) == 0 ) buf [ 0 ] = '\0';
       XmTextFieldSetString ( Anm_Multi_Input_text [ idx ], buf ) ;
       XmTextFieldSetInsertionPosition ( Anm_Multi_Input_text [ idx ],
                                                             strlen ( buf ) );
      XtAddCallback ( Anm_Multi_Input_text [ idx ], XmNactivateCallback, 
               ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
                 NULL );

       if ( c == EOF ) {
         Cre_Anm_Multi_Input_Form_Format_Error ( idx*10 + 6 );
         strcpy ( fifo_write_buf, "0:" );
         Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
         InvokeB ( without_XTerm, 1 );
         return;
       }

     } /* else */

     c = getc ( Bcom );
     if ( c == '\n' ) {
       Cre_Anm_Multi_Input_Form_Format_Error ( idx*10 + 7 );
       strcpy ( fifo_write_buf, "0:" );
       Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
       InvokeB ( without_XTerm, 1 );
       return;
     }
/***
printf ( "3 loop done\n" ); fflush ( stdout );
***/

     idx++;

     /* while ( c == '\n' ) { c = getc ( Bcom ); } */

  } /* while ( c != EOF ) */

  fclose ( Bcom );

  Anm_Multi_Input_tot = idx;

  idx = ( 33 * idx ) + 15;
  if ( Anm_Multi_Input_tot < 3 ) idx = idx + 25;
  if ( idx > 600 ) idx = 600;
  XtVaSetValues ( form_scroll, XmNheight, idx, NULL );

/***
for ( idx = 0 ; idx < Anm_Multi_Input_tot ; idx++ ) {
  printf ( "%d - Anm_Multi_Input_fld_ident [ %d ] %d\n    Anm_Multi_Input_label [ %d ] %s\n", idx, idx, Anm_Multi_Input_fld_ident [ idx ], idx, Anm_Multi_Input_label [ idx ] ); fflush ( stdout );
}
***/

  XtManageChild ( och_form );
  XtManageChild ( form_scroll );
  XtManageChild ( left_rc );
  XtManageChild ( right_rc );
  XtManageChild ( form );
  XtManageChild ( dialog_form );

  XtPopup ( dialog, XtGrabNone );
  XmProcessTraversal ( Anm_Multi_Input_text [ 0 ], XmTRAVERSE_CURRENT );

  XmUpdateDisplay ( dialog );

  if ( multi_err_str [ 0 ] != '\0' ) {
    XBell ( display, 10 );
    strcpy ( primary_string, multi_err_str );
    multi_err_str [ 0 ] = '\0';
    Popup_Minor_Err ( top_level, primary_string );
  }

}

void
AnmInvariant_CB ( widget, but_num )
Widget widget;
int but_num;
{
  anm_invariant_flag = but_num;
}

void
Animate_Utilities ( parent )
Widget parent;
{
#define Animate_Utils_help_text "\
Select one operation from the list;\n`Cancel' to return Animator Operations"

#define Animate_Utils_help_width  275
#define Animate_Utils_help_height 125

         Widget dialog, dialog_form,
                radio_box_scroll, radio_box,
                B_logo,
                sep,
                och_form, och_o, och_c, och_h, och_a, och_n,
                label,
                invariant_but;

         Atom   WM_DELETE_WINDOW;

  XmString xstr;

  XtCallbackProc PositionAnmOpsRelMainWin_CB ();

  static struct help_struct help_data;
  static struct coord coord_data;

  /***
  check if BT_ANM_KEY_STEP_FINI_M
  ***/
  if ( strcmp ( additional_string, "No Utilities" ) == 0 ) {
    void DisplayNewEnv ();
    additional_string [ 0 ] = '\0';
    process_XTerm_IfReq ();
    DisplayNewEnv ( main_env );
    return;
  }

    /***
    Create the basic dialog
    ***/
    Cre_Sel_Dialog ( & parent, & dialog, & dialog_form,
                     & radio_box_scroll, & radio_box,
                     & B_logo,
                     & sep,
                     & och_form, & och_o, & och_c, & och_h, & och_a, & och_n,
                     & help_data, & label,
                     SelLarge_flag_NO,
		     & WM_DELETE_WINDOW,
                     0 );

    coord_data.x = 250;
    coord_data.y = 1;

    XtAddCallback ( dialog, XmNpopupCallback,
        ( XtCallbackProc ) PositionAnmOpsRelMainWin_CB,
        ( XtPointer ) & coord_data );

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) Animate_Utils_help_text;
    help_data.width  = Animate_Utils_help_width;
    help_data.height = Animate_Utils_help_height;

    /***
    not MODAL
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );

    /***
    unmanage och_a och_n
    ***/
    XtUnmanageChild ( och_a );
    XtUnmanageChild ( och_n );

    /***
    set width & button offsets
    ***/
    XtVaSetValues ( sep,
       XmNwidth,                150,
       NULL );

    XtVaSetValues ( och_o,
       XmNleftOffset,           8,
       NULL );

    XtVaSetValues ( och_c,
       XmNleftOffset,           4,
       NULL );

    XtVaSetValues ( och_h,
       XmNrightOffset,          8,
       NULL );

    /***
    destroy previous radio_box_scroll & label
    ***/
    XtDestroyWidget ( label );
    XtDestroyWidget ( radio_box_scroll );

    xstr = XmStringCreateLtoR ( "Animator Utilities", charset );
    label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,             dialog_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   10,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNlabelString,                 xstr,
        XmNmarginWidth,                 10,
        XmNmarginHeight,                10,
        XmNtraversalOn,                 False,
        NULL );
    XmStringFree ( xstr );

    sel_arr_tot = 0;
    strcpy ( sel_str_arr [ sel_arr_tot++ ], "Edit theory file" );
    strcpy ( sel_str_arr [ sel_arr_tot++ ], "Restore initial state" );
    strcpy ( sel_str_arr [ sel_arr_tot++ ], "Restart animation" );
    strcpy ( sel_str_arr [ sel_arr_tot++ ], "Set state variables" );
    strcpy ( sel_str_arr [ sel_arr_tot++ ], "Save output" );
    strcpy ( sel_str_arr [ sel_arr_tot++ ], "Save as ANIMATE Script Initialisation" );
    strcpy ( sel_str_arr [ sel_arr_tot++ ], "Save as ANIMATE Script Executable" );
    strcpy ( sel_str_arr [ sel_arr_tot++ ], "Clean animator files" );

    /***
    recreate radio_box_scroll
    ***/

    radio_box_scroll = XtVaCreateWidget ( "SelDialog",
        xmScrolledWindowWidgetClass,    dialog_form,
        XmNtopAttachment,               XmATTACH_WIDGET,
        XmNtopWidget,                   label,
        XmNtopOffset,                   5,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 10,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  15,
        XmNbottomAttachment,            XmATTACH_WIDGET,
        XmNbottomWidget,                sep,
        XmNbottomOffset,                10,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
        XmNwidth,                       210,
        XmNheight,                      200,
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNspacing,                     0,
        NULL );

    /***
    create radio_box
    ***/
    radio_box = XmCreateRadioBox ( radio_box_scroll, "SelDialog", NULL, 0 );
    XtVaSetValues ( radio_box,
        XmNisHomogeneous,          False,
        XmNspacing,                0,
        NULL );


    /***
    create buttons in radio_box
    ***/
    {
      Widget but;
      int i;

      /***
      first button
      ***/
      but = XtVaCreateManagedWidget ( sel_str_arr [ 0 ],
          xmToggleButtonGadgetClass,     radio_box,
          XmNspacing,                    2,
          XmNhighlightThickness,         1,
          XmNnavigationType,             XmTAB_GROUP,
          NULL );
      XtAddCallback ( but, XmNvalueChangedCallback,
          ( XtCallbackProc ) ToggleBox_CB, ( XtPointer ) & c_arr [ 0 ] );

      XmToggleButtonSetState ( but, True, False );
      sel_arr_tog [ 0 ] = 1;

      /***
      other buttons
      ***/
      for ( i = 1 ; i < sel_arr_tot ; i++ ) {
/*
        if ( ( i == 2 ) || ( i == 3 ) || ( i == 7 ) ) {
*/
        if ( ( i == 1 ) || ( i == 4 ) || ( i == 7 ) ) {
          XtVaCreateManagedWidget ( "Anm",
              xmSeparatorGadgetClass,    radio_box,
              XmNmarginHeight,            0,
              NULL );
	}
        but = XtVaCreateManagedWidget ( sel_str_arr [ i ],
            xmToggleButtonGadgetClass,     radio_box,
            XmNspacing,                    2,
            XmNhighlightThickness,         1,
            XmNnavigationType,             XmTAB_GROUP,
            NULL );
        XtAddCallback ( but, XmNvalueChangedCallback,
            ( XtCallbackProc ) ToggleBox_CB, ( XtPointer ) & c_arr [ i ] );
        sel_arr_tog [ i ] = 0;
      }
    }

    XtManageChild ( B_logo );
    XtManageChild ( label );
    XtManageChild ( radio_box );
    XtManageChild ( radio_box_scroll );
    XtManageChild ( och_o );
    XtManageChild ( och_c ); 
    XtManageChild ( och_h );
    XtManageChild ( och_form );
    XtManageChild ( sep );
    XtManageChild ( dialog_form );

    /***
    destroy anm_ops_dialog if it exists
    ***/
    if ( anm_ops_dialog ) {
      XtDestroyWidget ( anm_ops_dialog );
      anm_ops_dialog = ( Widget ) 0;
    }

    /***
    reset second_visit & SelOne_flagged
    ***/
    SelOne_flagged = 1;
    second_visit = 0;

    Popup_Sel_flag = animator_utilities_sel;
    anm_ops_option = 1;   /* normally set in BMotif_io */

    XtPopup ( dialog, XtGrabNone );
    XmProcessTraversal ( och_o, XmTRAVERSE_CURRENT );
    XmUpdateDisplay ( dialog );

}

void
Animate_ExecutableStep_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  int but;
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;

  if ( cbs->reason == XmCR_PROTOCOLS ) {
    XtPopdown ( widget );
    XtDestroyWidget ( widget );
    strcpy ( fifo_write_buf, "0:" );
  }
  else {
    but = * ( int * ) client_data;
    XtPopdown ( XtParent ( XtParent ( XtParent ( widget ) ) ) );
    XtDestroyWidget ( XtParent ( XtParent ( XtParent ( widget ) ) ) );
    if ( ( * ( int * ) client_data ) == OK_BUTTON )
      strcpy ( fifo_write_buf, "1:" );
    else
      strcpy ( fifo_write_buf, "0:" );
  }

  Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
  InvokeB ( without_XTerm, 1 );
}

void
Animate_ExecutableStep ( parent )
Widget parent;
{
  /***
  primary string contains the op
  ***/

  Widget dialog, dialog_form, B_logo, label, sep, och_form, och_o, och_c;
  Arg args [ 2 ];
  XmString xstr;
  Atom WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );
  static struct coord coord_data;
  int i, j, ll;

#define ExecutableStep_width 60

  coord_data.x = 0; /* not used */
  coord_data.y = -10;

  strcpy ( buf, "Next: " );
  ll = strlen ( primary_string );
  if ( primary_string [ 0 ] == '(' ) {
    for ( i = 1 ; i < ll - 1 ; i++ )
                               { primary_string [ i - 1 ] = primary_string [ i ]; }
    primary_string [ i - 1 ] = '\0';
  }
  if ( ll < ExecutableStep_width ) {
    ll = ( ( ExecutableStep_width - strlen ( primary_string ) ) / 2 );
    j = strlen ( buf );
    for ( i = 0 ; i < ll ; i++ ) { buf [ j++ ] = ' '; }
    buf [ j ] = '\0';
    strcat ( buf, primary_string );
    j = strlen ( buf );
    for ( i = 0 ; i < ll ; i++ ) { buf [ j++ ] = ' '; }
    buf [ j ] = '\0';
  }
  else {
    strcat ( buf, primary_string );
  }

  xstr = XmStringCreateLtoR ( buf, charset );
  XtSetArg ( args [ 0 ], XmNresizeWidth, True );
  dialog = XmCreateDialogShell ( top_frame_form, "SelDialog", args, 1 );
  XtAddCallback ( dialog, XmNpopupCallback,
      ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
      ( XtPointer ) & coord_data );

  dialog_form = XtVaCreateWidget ( "SelDialog",
      xmFormWidgetClass,         dialog,
      XmNdialogStyle,            XmDIALOG_MODELESS,
      XmNtraversalOn,            True,
      XmNautoUnmanage,           False,
      NULL );

  B_logo = XtVaCreateManagedWidget ( "SelDialog", 
      xmPushButtonWidgetClass,    dialog_form,
      XmNtopAttachment,           XmATTACH_FORM,
      XmNtopOffset,               14,
      XmNleftAttachment,          XmATTACH_FORM,
      XmNleftOffset,              10,
      XmNlabelType,               XmPIXMAP,
      XmNlabelPixmap,             B_framed_pixmap_gray94,
      XmNshadowThickness,         0,
      XmNmarginWidth,             0,
      XmNmarginHeight,            0,
      XmNtraversalOn,             False,
      NULL );

  XtAddCallback ( B_logo, XmNactivateCallback,
                                    ( XtCallbackProc ) B_info_CB, NULL );

  label = XtVaCreateManagedWidget ( "Label", 
      xmLabelWidgetClass,        dialog_form,
      XmNtopAttachment,          XmATTACH_FORM,
      XmNtopOffset,              12,
      XmNleftAttachment,         XmATTACH_WIDGET,
      XmNleftWidget,             B_logo,
      XmNleftOffset,             1,
      XmNrightAttachment,        XmATTACH_FORM,
      XmNrightOffset,            36,
      XmNlabelString,            xstr,
      XmNmarginWidth,            10,
      XmNmarginHeight,           10,
      XmNtraversalOn,            False,
      NULL );
  XmStringFree ( xstr );

  sep = XtVaCreateManagedWidget ( "SelDialog",
      xmSeparatorGadgetClass,  dialog_form,
      XmNtopAttachment,        XmATTACH_WIDGET,
      XmNtopWidget,            label,
      XmNtopOffset,            12,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           0,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          0,
				  /*
      XmNwidth,                300,
				  */
      NULL );

  och_form = XtVaCreateWidget ( "ButtonLabel",
      xmFormWidgetClass,       dialog_form,
      XmNtopAttachment,        XmATTACH_WIDGET,
      XmNtopWidget,            sep,
      XmNtopOffset,            5,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         5,
      NULL );

  och_o = XtVaCreateManagedWidget ( "Execute", 
      xmPushButtonGadgetClass, och_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           5,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                75,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( och_o, XmNactivateCallback,
      ( XtCallbackProc ) Animate_ExecutableStep_CB,
      ( XtPointer ) & c_arr [ OK_BUTTON ] );

  och_c = XtVaCreateManagedWidget ( "Abort Execution",
      xmPushButtonGadgetClass, och_form,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          5,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                130,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( och_c, XmNactivateCallback,
      ( XtCallbackProc ) Animate_ExecutableStep_CB,
      ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );

  XmAddWMProtocolCallback ( dialog, WM_DELETE_WINDOW,
      ( XtCallbackProc ) Animate_ExecutableStep_CB,
      ( XtPointer ) dialog_form );

  XtManageChild ( och_form );
  XtManageChild ( dialog_form );
  XtPopup ( dialog, XtGrabNone );
  XmProcessTraversal ( och_o, XmTRAVERSE_CURRENT );
  XmUpdateDisplay ( dialog );
}

void
Animate_Ops ( parent )
Widget parent;
{
#define Animate_Ops_help_text "\
Select one operation from the list;\n`Quit' to quit the Animator"

#define Animate_Ops_help_width  235
#define Animate_Ops_help_height 125

  static Widget dialog_form,
                radio_box_scroll, radio_box,
                B_logo,
                sep,
                och_form, och_o, och_c, och_h, och_a, och_n,
                label,
                invariant_but;
  static Atom   WM_DELETE_WINDOW;

  static struct help_struct help_data;
  static struct coord coord_data;

  int height;

  XmString xstr, xstr0, xstr1;

  XtCallbackProc PositionAnmOpsRelMainWin_CB ();

/***
printf ( "Animate_Ops\n" );
***/

  if ( anm_ops_dialog == ( Widget ) 0 ) {

/***
printf ( "  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> creating anm_ops_dialog\n" );
***/

    /***
    Create the basic dialog
    ***/
    Cre_Sel_Dialog ( & parent, & anm_ops_dialog, & dialog_form,
                     & radio_box_scroll, & radio_box,
                     & B_logo,
                     & sep,
                     & och_form, & och_o, & och_c, & och_h, & och_a, & och_n,
                     & help_data, & label,
                     SelLarge_flag_NO,
		     & WM_DELETE_WINDOW,
                     0 );

    coord_data.x = 250;
    coord_data.y = 1;

    XtAddCallback ( anm_ops_dialog, XmNpopupCallback,
        ( XtCallbackProc ) PositionAnmOpsRelMainWin_CB,
        ( XtPointer ) & coord_data );

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) Animate_Ops_help_text;
    help_data.width  = Animate_Ops_help_width;
    help_data.height = Animate_Ops_help_height;

    /***
    not MODAL
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );

    /***
    set width
    ***/
    XtVaSetValues ( sep,
       XmNwidth,                 250,
       NULL );

   /***
    unmanage och_a och_n
    ***/
    XtUnmanageChild ( och_a );
    XtUnmanageChild ( och_n );

    /***
    Cancel -> Quit & set position (15 -> 7)
    ***/
    XtDestroyWidget ( och_c );
    och_c = XtVaCreateManagedWidget ( "Quit", 
        xmPushButtonGadgetClass, och_form,
        XmNleftAttachment,       XmATTACH_WIDGET,
        XmNleftWidget,           och_o,
        XmNleftOffset,           7,
        XmNtopAttachment,        XmATTACH_FORM,
        XmNtopOffset,            3,
        XmNheight,               27,
        XmNwidth,                57,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   1,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XtAddCallback ( och_c, XmNactivateCallback,
        ( XtCallbackProc ) Popup_Sel_Dialog_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );

    /***
    destroy previous radio_box_scroll & label
    ***/
    XtDestroyWidget ( label );
    XtDestroyWidget ( radio_box_scroll );

    xstr = XmStringCreateLtoR ( "Animator Operation", charset );
    label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,             dialog_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   10,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNlabelString,                 xstr,
        XmNmarginWidth,                 10,
        XmNmarginHeight,                10,
        XmNtraversalOn,                  False,
        NULL );
    XmStringFree ( xstr );

    GetBsel ();

    /***
    set width of sep
    ***/
    XtVaSetValues ( sep, XmNwidth, 275, NULL );

    /***
    set height of radio_box_scroll & recreate
    ***/
    height = 21 * sel_arr_tot + /* 17 */ /* 35 */ /* 90 */ 75;
    if ( height > 600 ) height = 600;
    if ( height < 250 ) height = 250;

    radio_box_scroll = XtVaCreateWidget ( "SelDialog",
        xmScrolledWindowWidgetClass,    dialog_form,
        XmNtopAttachment,               XmATTACH_WIDGET,
        XmNtopWidget,                   label,
        XmNtopOffset,                   5,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 10,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  15,
        XmNbottomAttachment,            XmATTACH_WIDGET,
        XmNbottomWidget,                sep,
        XmNbottomOffset,                10,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
        XmNheight,                      height,
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNspacing,                     0,
        NULL );

    /***
    create radio_box
    ***/
    radio_box = XmCreateRadioBox ( radio_box_scroll, "SelDialog", NULL, 0 );
    XtVaSetValues ( radio_box,
        XmNisHomogeneous,          False,
        XmNspacing,                0,
        NULL );


    /***
    create buttons in radio_box
    ***/
    {
      Widget but;
      int i;

      /***
      first button
      ***/
      but = XtVaCreateManagedWidget ( sel_str_arr [ 0 ],
          xmToggleButtonGadgetClass,     radio_box,
          XmNspacing,                    2,
          XmNhighlightThickness,         1,
          XmNnavigationType,             XmTAB_GROUP,
          NULL );
      XtAddCallback ( but, XmNvalueChangedCallback,
          ( XtCallbackProc ) ToggleBox_CB, ( XtPointer ) & c_arr [ 0 ] );

      XmToggleButtonSetState ( but, True, False );
      sel_arr_tog [ 0 ] = 1;

      /***
      other buttons
      ***/
      for ( i = 1 ; i < sel_arr_tot ; i++ ) {
        if ( strcmp ( sel_str_arr [ i ], "Undo last operation" ) == 0 ) {
          XtVaCreateManagedWidget ( "Anm",
              xmSeparatorGadgetClass,    radio_box,
              XmNmarginHeight,            0,
              NULL );
	}
        but = XtVaCreateManagedWidget ( sel_str_arr [ i ],
            xmToggleButtonGadgetClass,     radio_box,
            XmNspacing,                    2,
            XmNhighlightThickness,         1,
            XmNnavigationType,             XmTAB_GROUP,
            NULL );
        XtAddCallback ( but, XmNvalueChangedCallback,
            ( XtCallbackProc ) ToggleBox_CB, ( XtPointer ) & c_arr [ i ] );
        sel_arr_tog [ i ] = 0;
      }
    }

    xstr =  XmStringCreateLtoR ( "", charset );
    xstr0 =  XmStringCreateLtoR ( "Don't display invariant", charset );
    xstr1 =  XmStringCreateLtoR ( "Display invariant", charset );

    if ( anm_invariant_flag ) 
      invariant_but = XmVaCreateSimpleOptionMenu ( radio_box, "Option",
          xstr, 0,
	  1, AnmInvariant_CB,
          XmVaPUSHBUTTON, xstr0, NULL, NULL, NULL,
          XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
          XmNshadowThickness,        0,
	  /* 
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
	  */
          XmNdefaultButtonShadowThickness,     1,
          XmNhighlightThickness,     1,
          XmNnavigationType,         XmTAB_GROUP,
          NULL);
    else
      invariant_but = XmVaCreateSimpleOptionMenu ( radio_box, "Option",
          xstr, 0,
	  0, AnmInvariant_CB,
          XmVaPUSHBUTTON, xstr0, NULL, NULL, NULL,
          XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
          XmNshadowThickness,        0,
          /* 
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          */
          XmNdefaultButtonShadowThickness,     1,
          XmNhighlightThickness,     1,
          XmNnavigationType,         XmTAB_GROUP,
          NULL);

    XmStringFree ( xstr );
    XmStringFree ( xstr0 );
    XmStringFree ( xstr1 );

    XtManageChild ( invariant_but );

    XtManageChild ( B_logo );
    XtManageChild ( label );
    XtManageChild ( radio_box );
    XtManageChild ( radio_box_scroll );
    XtManageChild ( och_o );
    XtManageChild ( och_c ); 
    XtManageChild ( och_h );
    XtManageChild ( och_form );
    XtManageChild ( sep );
    XtManageChild ( dialog_form );

  } /* end if ( ! anm_ops_dialog ) */

  /***
  reset second_visit & SelOne_flagged
  ***/
  SelOne_flagged = 1;
  second_visit = 0;

  XtPopup ( anm_ops_dialog, XtGrabNone );
  XmProcessTraversal ( och_o, XmTRAVERSE_CURRENT );
  XmUpdateDisplay ( anm_ops_dialog );

}

void
Animate ( option )
int option;
{
/***
  switch ( option ) {
  case BT_ANM_DSP_1_M:
    printf ( "Animate ( BT_ANM_DSP_1_M )\n" );
    break;
  case BT_ANM_DSP_2_M:
    printf ( "Animate ( BT_ANM_DSP_2_M )\n" );
    break;
  case BT_ANM_DSP_3_M:
    printf ( "Animate ( BT_ANM_DSP_3_M )\n" );
    break;
  case BT_ANM_PRCD_M:
    printf ( "Animate ( BT_ANM_PRCD_M )\n" );
    break;
  case BT_ANM_DISP_OP_M:
    printf ( "Animate ( BT_ANM_DISP_OP_M )\n" );
    break;
  case BT_ANM_GET_OP_M:
    printf ( "Animate ( BT_ANM_GET_OP_M )\n" );
    break;
  default :
    Popup_Minor_Err ( top_level, " Animate ( ?????????????????????????? ) " );
    break;
  }
***/

  if ( rewrite_prompt ) {
    DisplayCurrWinText ( "\nAnimator Environment:\n" );
    rewrite_prompt = 0;
  }

  /***
  all options
  destroy constructs_rc
  ***/
  XtDestroyWidget ( constructs_rc );
  constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
      xmRowColumnWidgetClass,         constructs_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 18,
      XmNmarginHeight,                10,
      XmNspacing,                     0,
      XmNresizable,                   True,
      NULL );
  XmUpdateDisplay ( constructs_rc );
  XmUpdateDisplay ( constructs_scroll );
  XmUpdateDisplay ( constructs_form );

  /***
  all options
  create sub_frame1 in constructs_rc
  ***/
  sub_frame1 = XtVaCreateWidget ( "Canvas",
      xmFrameWidgetClass,          constructs_rc,
      XmNshadowType,               XmSHADOW_OUT,
      NULL );

  /***
  create sub_text1 in sub_frame1
  ***/
  sub_text1 = XtVaCreateWidget ( "Anm",
      xmTextWidgetClass,           sub_frame1,
      XmNcursorPositionVisible,    False,
      XmNeditable,                 False,
      XmNeditMode,                 XmMULTI_LINE_EDIT,
      XmNwordWrap,                 False, /**/
      XmNscrollHorizontal,         False, /**/
      XmNscrollVertical,           False, /**/
      XmNmarginWidth,              7,
      XmNmarginHeight,             7,
      XmNborderWidth,              0,
      XmNshadowThickness,          0,
      XmNresizeHeight,             True,
      XmNresizeWidth,              True,
      NULL );

  LoadFileIntoBuf ( ".Bsb1", buf, MAX_buf - 1 );
  XmTextSetString ( sub_text1, buf );

  XtManageChild ( sub_text1 );
  XtManageChild ( sub_frame1 );

  switch ( option ) {

  case BT_ANM_DSP_2_M:
  case BT_ANM_DSP_3_M:

    /***
    create sub_frame2 in constructs_rc
    ***/
    sub_frame2 = XtVaCreateWidget ( "Canvas",
        xmFrameWidgetClass,          constructs_rc,
        XmNshadowType,               XmSHADOW_OUT,
        NULL );

    /***
    create sub_text2 in sub_frame2
    ***/
    sub_text2 = XtVaCreateWidget ( "Anm",
        xmTextWidgetClass,           sub_frame2,
        XmNcursorPositionVisible,    False,
        XmNeditable,                 False,
        XmNeditMode,                 XmMULTI_LINE_EDIT,
        XmNwordWrap,                 False, /**/
        XmNscrollHorizontal,         False, /**/
        XmNscrollVertical,           False, /**/
        XmNmarginWidth,              7,
        XmNmarginHeight,             7,
        XmNborderWidth,              0,
        XmNshadowThickness,          0,
	XmNresizeHeight,             True,
        XmNresizeWidth,              True,
        NULL );

    LoadFileIntoBuf ( ".Bsb2", buf, MAX_buf - 1 );
    XmTextSetString ( sub_text2, buf );

    XtManageChild ( sub_text2 );
    XtManageChild ( sub_frame2 );

    if ( option == BT_ANM_DSP_3_M ) {

      /***
      create sub_frame3 in constructs_rc
      ***/
      sub_frame3 = XtVaCreateWidget ( "Canvas",
          xmFrameWidgetClass,          constructs_rc,
          XmNshadowType,               XmSHADOW_OUT,
          NULL );

      /***
      create sub_text3 in sub_frame3
      ***/
      sub_text3 = XtVaCreateWidget ( "Anm",
          xmTextWidgetClass,           sub_frame3,
          XmNcursorPositionVisible,    False,
          XmNeditable,                 False,
          XmNeditMode,                 XmMULTI_LINE_EDIT,
          XmNwordWrap,                 False, /**/
          XmNscrollHorizontal,         False, /**/
          XmNscrollVertical,           False, /**/
          XmNmarginWidth,              7,
          XmNmarginHeight,             7,
          XmNborderWidth,              0,
          XmNshadowThickness,          0,
	  XmNresizeHeight,             True,
          XmNresizeWidth,              True,
          NULL );

      LoadFileIntoBuf ( ".Bsb3", buf, MAX_buf - 1 );
      XmTextSetString ( sub_text3, buf );

      XtManageChild ( sub_text3 );
      XtManageChild ( sub_frame3 );
    }

  } /* switch ( option ) */

  /***
  create sub_dummy
  manage constructs_rc
  XmScrollVisible
  ***/
  sub_dummy = XtVaCreateWidget ( "Canvas",
      xmFormWidgetClass,          constructs_rc,
      NULL );
  XtManageChild ( sub_dummy );

  XtManageChild ( constructs_rc );
  XtManageChild ( constructs_scroll );
  XmScrollVisible ( constructs_scroll, sub_dummy, 0, 0 );
  XmUpdateDisplay ( constructs_scroll );


  switch ( option ) {

    case BT_ANM_PRCD_M:

      /*      SetSensitiveEnvLabelBut ( True ); */
      Popup_InformationDialog ( top_level );
      break;

    case BT_ANM_PRCD_FALSE_M:

      /*      SetSensitiveEnvLabelBut ( True ); */
      Popup_InformationDialog ( top_level );
      Popup_Minor_Err ( top_level, secondary_string ); 
      break;

    case BT_ANM_DSP_1_M:
    case BT_ANM_DSP_2_M:
    case BT_ANM_DSP_3_M:

    if ( strcmp ( primary_string, "0" ) != 0 ) {
      XBell ( display, 10 );
      Popup_Minor_Err ( top_level, primary_string );
    }
    else if ( strcmp ( secondary_string, "0" ) != 0 ) {
      Popup_Info ( secondary_string );
    }
    /*      SetSensitiveEnvLabelBut ( False ); */
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
    InvokeB ( without_XTerm, 1 );
    break;

  case BT_ANM_DISP_OP_M:

      /*      SetSensitiveEnvLabelBut ( False ); */
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
      InvokeB ( without_XTerm, 1 );
      break;

  } /* switch ( option ) */
}



/***********************************************************************
************************************************************************
                       InterProver
************************************************************************
***********************************************************************/

void
IPRButton_CB ()
{
  /***
  fifo_write_buf already set
  de-activate pob label & current pob
  ***/

  if ( dont_destroy_display ) {          /* Reload PROOFMETHOD - don't change! */
    dont_destroy_display = 0;
  }
  else {
    XtVaSetValues ( ipr_label, XmNforeground, gray64, NULL );
    XtVaSetValues ( sub_text1, XmNforeground, gray64, NULL );
    if ( curr_env == ipr_pob_env ) {
      XtVaSetValues ( sub_text2, XmNforeground, gray64, NULL );
    }
  }

  InvokeB ( without_XTerm, 1 );
}

XtCallbackProc
DisplayIprHyp_Search_CB_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  int search_i = * ( int * ) client_data;
  XtPopdown ( ipr_hyp_sch_dialog [ search_i ] );
  XtDestroyWidget ( ipr_hyp_sch_dialog [ search_i ] );
  ipr_hyp_sch_dialog_up [ search_i ] = 0;
}

XtCallbackProc
DisplayIprHyp_Search_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  static Widget dialog_main_form, dialog_scroll,
                search_label,
                dialog_label_frame, dialog_label, dialog_text, but;
  int search_i, i, done;

  Dimension xx, yy;
  XmString xstr;
  XmTextPosition curr_posn;

  char * search_text;

  Atom   WM_DELETE_WINDOW;

  WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

  search_text = XmTextFieldGetString ( widget );
  if ( ! * search_text ) {
    Popup_Info ( "Search text empty" );
    XtFree ( search_text );
    return;
  }

  if ( strlen ( search_text ) > 248 ) {
    Popup_Info ( "Search text too long (max 250)" );
    XtFree ( search_text );
    return;
  }

  search_i = 0;
  done = 0;
  while ( ( ! done ) && ( search_i < 10 ) ) {
    if ( ipr_hyp_sch_dialog_up [ search_i ] == 0 ) done = 1;
    if ( ! done ) search_i++;
  }
  if ( ! done ) {
    Popup_Info ( "Too many hypotheses displayed" );
    XtFree ( search_text );
    return;
  }

  strcpy ( hyp_search_string, search_text );
  XtFree ( search_text );

  ipr_hyp_sch_dialog_up [ search_i ] = 1;
  ipr_hyp_sch_dialog [ search_i ] =
                     XmCreateDialogShell ( top_frame_form, "Hyp", NULL, 0 );
  XtAddCallback ( ipr_hyp_sch_dialog [ search_i ], XmNpopupCallback,
      ( XtCallbackProc ) IprPositionSearchedHyp_CB,
      ( XtPointer ) XtParent ( widget ) );
  XmAddWMProtocolCallback ( ipr_hyp_sch_dialog [ search_i ], WM_DELETE_WINDOW,
      ( XtCallbackProc ) IprPositionSearchedHyp_CB,
      ( XtPointer )  XtParent ( widget ) );

  dialog_main_form = XtVaCreateWidget ( "Hyp",
      xmFormWidgetClass,         ipr_hyp_sch_dialog [ search_i ],
      XmNdefaultPosition,        False,  
      NULL );
  dialog_label_frame = XtVaCreateWidget ( "Label",
        xmFrameWidgetClass,        dialog_main_form,
        XmNshadowType,             XmSHADOW_ETCHED_OUT,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_FORM,
        XmNleftOffset,             10,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNrightOffset,            10,
        XmNtraversalOn,            False,
        NULL );

  LoadFileIntoBuf ( "TMP/.Bgol", buf, MAX_buf );

#define truncated_goal_length 100
  /*** truncate goal (also used below) ***/

  buf [ truncated_goal_length - 5 ] = ' ';
  buf [ truncated_goal_length - 4 ] = '.';
  buf [ truncated_goal_length - 3 ] = '.';
  buf [ truncated_goal_length - 2 ] = '.';
  buf [ truncated_goal_length - 1 ] = ' ';
  buf [ truncated_goal_length ] = '\0';

  sprintf ( fifo_write_buf, "Goal:%s", buf );
  xstr = XmStringCreateLtoR ( fifo_write_buf, charset );
  dialog_label = XtVaCreateWidget ( "Label",
        xmLabelWidgetClass,        dialog_label_frame,
        XmNlabelString,            xstr,
        XmNmarginWidth,            5,
        XmNmarginHeight,           2,
        XmNtraversalOn,            False,
        NULL );
  XmStringFree ( xstr );
  strcpy ( buf, "Hypotheses containing \"" );
  strcat ( buf, hyp_search_string );
  strcat ( buf, "\"" );
  xstr = XmStringCreateLtoR ( buf, charset );
  search_label = XtVaCreateManagedWidget ( "Label",
      xmLabelWidgetClass,             dialog_main_form,
      XmNlabelString,                 xstr,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   dialog_label_frame,
      XmNtopOffset,                   10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNtraversalOn,                 False,
      NULL );
  XmStringFree ( xstr );
  dialog_scroll =  XtVaCreateWidget ( "Hyp",
      xmScrolledWindowWidgetClass,    dialog_main_form,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNwidth,                       450,
      XmNheight,                      255,
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNspacing,                     0,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   search_label,
      XmNtopOffset,                   10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                55,
      XmNtraversalOn,                 False,
      NULL );
  dialog_text = XtVaCreateWidget ( "Hyp", 
        xmTextWidgetClass,         dialog_scroll,
        XmNcursorPositionVisible,  False,
        XmNeditable,               False,
        XmNeditMode,               XmMULTI_LINE_EDIT,
        XmNwordWrap,                 False, /**/
        XmNscrollHorizontal,         False, /**/
        XmNscrollVertical,           False, /**/
        XmNmarginWidth,            5,
        XmNmarginHeight,           0,
        XmNborderWidth,            0,
        XmNshadowThickness,        0,
	XmNresizeHeight,           True,
        XmNresizeWidth,            True,
        NULL );
  XmTextSetString ( dialog_text, "" );
  curr_posn = 0;
  i = 0;
  while ( str_buf [ i ] != '\0' ) {
    j = 0;
    while ( ( str_buf [ i ] != '\n' ) &&
            ( str_buf [ i ] != '\0' )    ) {
      buf [ j++ ] = str_buf [ i++ ];
    }
    buf [ j ] = '\0';
    if ( sub_str_in_str ( hyp_search_string, buf ) ) {
      strcat ( buf, "\n" );
      XmTextInsert ( dialog_text, curr_posn, buf );
      curr_posn = curr_posn + strlen ( buf );
    }
    if ( str_buf [ i ] == '\n' ) i++;
  }
  if ( curr_posn == 0 ) XmTextSetString ( dialog_text, "No match" );
  XmTextShowPosition ( dialog_text, 0 );
  xstr = XmStringCreateLtoR ( "Dismiss filtered hypotheses", charset );
  but = XtVaCreateManagedWidget ( "Label",
        xmPushButtonGadgetClass,   dialog_main_form,
        XmNshadowThickness,        2,
        XmNlabelString,            xstr,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,     1,
        XmNmarginWidth,            7,
        XmNmarginHeight,           4,
        XmNleftAttachment,         XmATTACH_FORM,
        XmNleftOffset,             5,
        XmNbottomAttachment,       XmATTACH_FORM,
        XmNbottomOffset,           5,
        XmNnavigationType,         XmTAB_GROUP,
        NULL );
  XmStringFree ( xstr );
  XtAddCallback ( but, XmNactivateCallback,
      ( XtCallbackProc ) DisplayIprHyp_Search_CB_CB,
      ( XtPointer ) & c_arr [ search_i ] );

  XtManageChild ( dialog_label );
  XtManageChild ( dialog_label_frame );
  XtManageChild ( dialog_text );
  XtManageChild ( dialog_scroll );
  XtManageChild ( dialog_main_form );

  XtPopup ( ipr_hyp_sch_dialog [ search_i ], XtGrabNone );
  XmUpdateDisplay ( ipr_hyp_sch_dialog [ search_i ] );
}

XtCallbackProc
DisplayIprHyp_CB ()
{
  XtPopdown ( ipr_hyp_dialog );
  XtDestroyWidget ( ipr_hyp_dialog );
  ipr_hyp_dialog_up = 0;
}

void
DisplayIprHyp ()
{
  static Widget dialog_main_form, dialog_scroll,
                search_label, search_text,
                dialog_label_frame, dialog_label, but;
  static struct coord coord_data;
  XmString xstr;
  int num_hyp, i, ll;

  Atom   WM_DELETE_WINDOW;

  WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

  LoadFileIntoBuf ( "TMP/.Bhyp", str_buf, MAX_str_buf );

  LoadFileIntoBuf ( "TMP/.Bgol", buf, MAX_buf );

  coord_data.x = -240;
  coord_data.y = 282;

  ipr_hyp_dialog_up = 1;
  ipr_hyp_dialog = XmCreateDialogShell ( top_frame_form, "Hyp", NULL, 0 );
  XtAddCallback ( ipr_hyp_dialog, XmNpopupCallback,
      ( XtCallbackProc ) PositionWidgetRightMainWin_CB,
      ( XtPointer ) & coord_data );
  XmAddWMProtocolCallback ( ipr_hyp_dialog, WM_DELETE_WINDOW,
      ( XtCallbackProc ) DisplayIprHyp_CB,
      ( XtPointer ) NULL );

  dialog_main_form = XtVaCreateWidget ( "Hyp", 
      xmFormWidgetClass,         ipr_hyp_dialog,
      XmNdefaultPosition,        False,  
      NULL );
  dialog_label_frame = XtVaCreateWidget ( "Label",
        xmFrameWidgetClass,        dialog_main_form,
        XmNshadowType,              XmSHADOW_ETCHED_OUT,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_FORM,
        XmNleftOffset,             10,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNrightOffset,            10,
        XmNtraversalOn,            False,
        NULL );

  buf [ truncated_goal_length - 5 ] = ' ';
  buf [ truncated_goal_length - 4 ] = '.';
  buf [ truncated_goal_length - 3 ] = '.';
  buf [ truncated_goal_length - 2 ] = '.';
  buf [ truncated_goal_length - 1 ] = ' ';
  buf [ truncated_goal_length ] = '\0';

  sprintf ( fifo_write_buf, "Goal:%s", buf );
  xstr = XmStringCreateLtoR ( fifo_write_buf, charset );
  dialog_label = XtVaCreateWidget ( "Label",
        xmLabelWidgetClass,        dialog_label_frame,
        XmNlabelString,            xstr,
        XmNmarginWidth,            5,
        XmNmarginHeight,           2,
        XmNtraversalOn,            False,
        NULL );
  XmStringFree ( xstr );
  xstr = XmStringCreateLtoR ( "Search:", charset );
  search_label = XtVaCreateManagedWidget ( "Label",
      xmLabelWidgetClass,             dialog_main_form,
      XmNlabelString,                 xstr,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   dialog_label_frame,
      XmNtopOffset,                   13,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNtraversalOn,                 False,
      NULL );
  XmStringFree ( xstr );
  search_text = XtVaCreateManagedWidget ( "Label",
      xmTextFieldWidgetClass,         dialog_main_form,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   dialog_label_frame,
      XmNtopOffset,                   10,
      XmNleftAttachment,              XmATTACH_WIDGET,
      XmNleftWidget,                  search_label,
      XmNleftOffset,                  10,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 25,
      XmNmarginWidth,                 3,      
      XmNmarginHeight,                2,      
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,          1,
      NULL );
  XmTextFieldSetString ( search_text, hyp_search_string ) ;
  XmTextFieldSetInsertionPosition ( search_text, strlen ( hyp_search_string ) );
  XtAddCallback ( search_text, XmNactivateCallback,
     ( XtCallbackProc ) DisplayIprHyp_Search_CB,
     ( XtPointer ) search_text );
  
  dialog_scroll =  XtVaCreateWidget ( "Hyp",
      xmScrolledWindowWidgetClass,    dialog_main_form,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNwidth,                       450,
      XmNheight,                      350,
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNspacing,                     0,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   search_label,
      XmNtopOffset,                   10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                54,
      XmNtraversalOn,                 False,
      NULL );
  ipr_hyp_dialog_text = XtVaCreateWidget ( "Hyp", 
        xmTextWidgetClass,         dialog_scroll,
        XmNcursorPositionVisible,  False,
        XmNeditable,               False,
        XmNeditMode,               XmMULTI_LINE_EDIT,
        XmNwordWrap,                 False, /**/
        XmNscrollHorizontal,         False, /**/
        XmNscrollVertical,           False, /**/
        XmNmarginWidth,            5,
        XmNmarginHeight,           0,
        XmNborderWidth,            0,
        XmNshadowThickness,        0,
	XmNresizeHeight,           True,
        XmNresizeWidth,            True,
        NULL );
  num_hyp = 0;
  i = 0;
  while ( str_buf [ i ] != '\0' ) {
    if ( str_buf [ i ] == '&' ) {
      str_buf [ i ] = '\n';
      num_hyp++;
    }
    i++;
  }
  strcat ( str_buf, "\n" );
  if   ( num_hyp ) {
    XmTextSetString ( ipr_hyp_dialog_text, str_buf );
  }
  else {
    XmTextSetString ( ipr_hyp_dialog_text, "\n    No hypotheses\n" );
    XtVaSetValues ( dialog_scroll,
      XmNheight,                      150,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   50,
      NULL);
    XtUnmanageChild ( search_label );
    XtUnmanageChild ( search_text );
  }

  xstr = XmStringCreateLtoR ( "Dismiss hypotheses", charset );
  but = XtVaCreateManagedWidget ( "Label",
        xmPushButtonGadgetClass,   dialog_main_form,
        XmNshadowThickness,        2,
        XmNlabelString,            xstr,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,     1,
        XmNmarginWidth,            7,
        XmNmarginHeight,           4,
        XmNleftAttachment,         XmATTACH_FORM,
        XmNleftOffset,             5,
        XmNbottomAttachment,       XmATTACH_FORM,
        XmNbottomOffset,           5,
        XmNnavigationType,         XmTAB_GROUP,
        NULL );
  XmStringFree ( xstr );
  XtAddCallback ( but, XmNactivateCallback,
      ( XtCallbackProc ) DisplayIprHyp_CB,
      ( XtPointer ) NULL );

  XtRealizeWidget ( ipr_hyp_dialog );
  XtManageChild ( dialog_label );
  XtManageChild ( dialog_label_frame );
  XtManageChild ( ipr_hyp_dialog_text );
  XtManageChild ( dialog_scroll );
  XtManageChild ( dialog_main_form );

  XtPopup ( ipr_hyp_dialog, XtGrabNone );
  if   ( num_hyp ) {
    XmProcessTraversal ( search_text, XmTRAVERSE_CURRENT );
  }
  XmUpdateDisplay ( ipr_hyp_dialog );

}

XtCallbackProc
DisplayIprRuleMenu_1_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;
  void DisplayIprRuleMenu ();

  XtPopdown ( ( Widget ) client_data );
  XtDestroyWidget ( ipr_sel_rc );
  XmUpdateDisplay ( constructs_rc );
  XmUpdateDisplay ( top_level );
  if ( cbs->reason == XmCR_PROTOCOLS ) DisplayIprRuleMenu ( 1, 1 );
  sprintf ( fifo_write_buf, "(?,0):" );
  Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
  InvokeB ( without_XTerm, 1 );
}

XtCallbackProc
DisplayIprRuleMenu_2_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  XtPopdown ( ( Widget ) client_data );
  XtDestroyWidget ( ipr_sel_rc );
  /*  XmUpdateDisplay ( constructs_rc ); */
  /*  XmUpdateDisplay ( top_level ); */
  sprintf ( fifo_write_buf, "(?,1):" );
  Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
  InvokeB ( without_XTerm, 1 );
}

void
DisplayIprUnproved_CB ( widget, but_num )
Widget widget;
int but_num;
{
  void Ipr_Sel_Rule ();
/***
printf ( "prev display_unproved_ipr_flag: %d\n", display_unproved_ipr_flag );
***/
  if ( display_unproved_ipr_flag != but_num ) {
    display_unproved_ipr_flag = but_num;
    XtDestroyWidget ( ipr_sel_rc );
    Ipr_Sel_Rule ();
  }
/***
printf ( "display_unproved_ipr_flag: %d\n", display_unproved_ipr_flag );
***/
}

void
DisplayIprRuleMenu ( flag, WM_flag )
int flag;
int WM_flag;
{
  static Widget dialog, dialog_form, B_logo, Label,
                menu_rc, display_unproved_but;
  static struct coord coord_data;
  XmString xstr, xstr0, xstr1;

  static int first_time = 1;

  static Atom  WM_DELETE_WINDOW;

  if ( ! flag ) {
    XtPopdown ( dialog );
    XmUpdateDisplay ( top_level );
    return;
  }

  if ( WM_flag ) {    /* DisplayIprRuleMenu_1_CB - WM Close */
    XtDestroyWidget ( dialog );
    first_time = 1;
    return;
  }

  if ( first_time ) {

    first_time = 0;

    coord_data.x = -180;
    coord_data.y = 1;

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    dialog = XmCreateDialogShell ( top_frame_form, "SelDialog", NULL, 0 );
    XtAddCallback ( dialog, XmNpopupCallback,
        ( XtCallbackProc ) PositionWidgetRightMainWin_CB,
        ( XtPointer ) & coord_data );
    XmAddWMProtocolCallback ( dialog, WM_DELETE_WINDOW,
        ( XtCallbackProc ) DisplayIprRuleMenu_1_CB,
        ( XtPointer ) dialog );


    dialog_form = XtVaCreateWidget ( "SelDialog",
        xmFormWidgetClass,         dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        False,  
        XmNautoUnmanage,           False,
        NULL );

    B_logo =  XtVaCreateWidget ( "SelDialog",
        xmPushButtonWidgetClass,    dialog_form,
        XmNlabelType,               XmPIXMAP,
        XmNlabelPixmap,             B_framed_pixmap_gray94,
        XmNshadowThickness,         0,
        XmNmarginWidth,             0,
        XmNmarginHeight,            0,
        XmNtopAttachment,           XmATTACH_FORM,
        XmNtopOffset,               10,
        XmNleftAttachment,          XmATTACH_FORM,
        XmNleftOffset,              10,
        XmNtraversalOn,             False,
        NULL );

    XtAddCallback ( B_logo, XmNactivateCallback,
                                    ( XtCallbackProc ) B_info_CB, NULL );

    xstr = XmStringCreate ( "Theory Menu", charset );

    Label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNleftOffset,             13,
        XmNrightOffset,            23,
        XmNlabelString,            xstr,
        XmNmarginWidth,            10,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

    menu_rc = XtVaCreateWidget ( "Canvas", 
        xmRowColumnWidgetClass,         dialog_form,
        XmNorientation,                 XmVERTICAL,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   55,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 5,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  5,
        XmNbottomAttachment,            XmATTACH_FORM,
        XmNbottomOffset,                35,
        XmNmarginWidth,                 5,
        XmNmarginHeight,                5,
        XmNspacing,                     5,
        XmNisHomogeneous,               False,
        NULL );

    xstr =  XmStringCreateLtoR ( "", charset );
    xstr0 =  XmStringCreateLtoR ( "Display unproved only", charset );
    xstr1 =  XmStringCreateLtoR ( "Display all", charset );

    display_unproved_but = XmVaCreateSimpleOptionMenu ( menu_rc, "Canvas",
        xstr, 0,
	1, DisplayIprUnproved_CB,
        XmVaPUSHBUTTON, xstr0, NULL, NULL, NULL,
        XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
        XmNshadowThickness,        0,
        /* 
        XmNmarginWidth,            0,
        XmNmarginHeight,           0,
        */
        XmNdefaultButtonShadowThickness,     1,
        XmNhighlightThickness,     1,
        XmNnavigationType,         XmTAB_GROUP,
        NULL);

    XmStringFree ( xstr );
    XmStringFree ( xstr0 );
    XmStringFree ( xstr1 );

    display_unproved_ipr_flag = 1;

    XtManageChild ( display_unproved_but );

    CreHighlightedButton ( menu_rc, "  Quit to Theory Menu", 
              ( XtCallbackProc ) DisplayIprRuleMenu_2_CB,
              ( XtPointer ) dialog );

    CreHighlightedButton ( menu_rc, "  Exit InterProver", 
              ( XtCallbackProc ) DisplayIprRuleMenu_1_CB,
              ( XtPointer ) dialog );

    XtManageChild ( B_logo );
    XtManageChild ( Label );
    XtManageChild ( menu_rc );
    XtManageChild ( dialog_form );
  }

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
  XmUpdateDisplay ( top_level );

}

XtCallbackProc
Ipr_Sel_Rule_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  prev_rule = * ( int * ) client_data;
  if ( sel_obj_arr [ prev_rule ] ) {
    Popup_Info ( "    Already proved    " );
    return;
  }

  XtDestroyWidget ( ipr_sel_rc );
  DisplayIprRuleMenu ( 0, 0 );

  sprintf ( fifo_write_buf, "(?,%s.%d):",
                       sel_str_arr [ sel_arr_tot ], prev_rule + 1 );
  strcpy ( prev_thy, sel_str_arr [ sel_arr_tot ] );
  Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
  InvokeB ( without_XTerm, 1 );
}

void
Ipr_Sel_Rule ()
{
  XmString xstr;
  Widget but, label_form;
  int i, i_i, k, k_k, f, n, tt;
  int scroll_visible;
  Widget scroll_visible_widget;

  scroll_visible_widget = ( Widget ) 0;

  if ( strcmp ( prev_thy, sel_str_arr [ sel_arr_tot ] ) == 0 ) {
    scroll_visible = 1;
  }
  else {
    scroll_visible = 0;
  }

  ipr_sel_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         constructs_rc,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                0,
      XmNspacing,                     0,
      XmNisHomogeneous,               False,
      NULL );

  label_form = XtVaCreateWidget ( "Label", 
    xmFormWidgetClass,             ipr_sel_rc,
    NULL );

  xstr = XmStringCreateLtoR ( sel_str_arr [ sel_arr_tot ], charset );
  TRBut [ 0 ] = XtVaCreateManagedWidget ( "Label", 
    xmLabelWidgetClass,             label_form,
    XmNlabelString,                 xstr,
    XmNmarginWidth,                 20,
    XmNmarginHeight,                5,
    XmNleftAttachment,              XmATTACH_FORM,
    XmNtraversalOn,                 False,
    NULL );
  XmStringFree ( xstr );

  xstr = XmStringCreateLtoR ( "(Click a Rule to select)", charset );
  XtVaCreateManagedWidget ( "Highlight", 
    xmLabelWidgetClass,             label_form,
    XmNlabelString,                 xstr,
    XmNmarginWidth,                 0,
    XmNmarginHeight,                5,
    XmNleftAttachment,              XmATTACH_WIDGET,
    XmNleftWidget,                  TRBut [ 0 ],
    XmNleftOffset,                  0,
    XmNtraversalOn,                 False,
    NULL );
  XmStringFree ( xstr );

  XtManageChild ( label_form );

  for ( i = 0 ; i < sel_arr_tot ; i++ ) {

    str_buf [ 0 ] = '\0';

    label_form = XtVaCreateWidget ( "Label", 
      xmFormWidgetClass,             ipr_sel_rc,
      NULL );

    tt = strlen ( sel_str_arr [ i ] ) - 1;
    sel_obj_arr [ i ] = sel_str_arr [ i ] [ tt ] - '0';
    k = tt;
    while ( sel_str_arr [ i ] [ k ] != ':' ) { k--; }
    sel_str_arr [ i ] [ k ] = '\0';
    i_i = i;
    k_k = k;
    n = 0;
    k++;
    while ( k < tt ) {
      n = ( 10 * n ) + sel_str_arr [ i ] [ k ] - '0';
      k++;
    }

    if ( ( display_unproved_ipr_flag ) || ( ! sel_obj_arr [ i ] ) ) {

      sprintf ( buf, "%s.%d", sel_str_arr [ sel_arr_tot ], n );
      xstr = XmStringCreateLtoR ( buf, charset );
      but = XtVaCreateManagedWidget ( "Label", 
        xmLabelWidgetClass,             label_form,
        XmNlabelString,                 xstr,
        XmNmarginWidth,                 5,
        XmNmarginHeight,                5,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNtraversalOn,                 False,
        NULL );
      XmStringFree ( xstr );

      xstr = XmStringCreateLtoR ( proved_label [ sel_obj_arr [ i ] ], charset );
      XtVaCreateManagedWidget ( proved_class [ sel_obj_arr [ i ] ], 
        xmLabelWidgetClass,             label_form,
        XmNlabelString,                 xstr,
        XmNmarginWidth,                 5,
        XmNmarginHeight,                5,
        XmNleftAttachment,              XmATTACH_WIDGET,
        XmNleftWidget,                  but,
        XmNleftOffset,                  0,
        XmNtraversalOn,                 False,
          NULL );
      XmStringFree ( xstr );

      XtManageChild ( label_form );

      strcpy ( str_buf, sel_str_arr [ i ] );
      f = read_frmfunc_str_buf();
      if ( f != -999 ) {
        read_rul_the ( tmp_btool_ipr_thy, f );
        str_buf [ 0 ] = '\0';
        write_ver_rul_dave ( val_rul_the_from_btoolkit ( tmp_btool_ipr_thy, 1 ) );
        but = CreHighlightedButton ( ipr_sel_rc, str_buf,
                  ( XtCallbackProc ) Ipr_Sel_Rule_CB,
                  & c_arr [ i ] );

/*
        sprintf ( str_buf, "%s%d", sel_str_arr [ i ], sel_obj_arr [ i ] );
        strcpy ( sel_str_arr [ i ], str_buf );
*/

        if ( scroll_visible ) {
          if ( i == prev_rule ) {
            scroll_visible_widget = but;
	  }
        }

        rem_rul_the ( tmp_btool_ipr_thy, 1 );

      }
      else {
        Popup_Info ( buf, "Rule does not parse" );
        sprintf ( buf, "\n  Rule does not parse:\n\n    %s\n", str_buf );
        DisplayCurrWinText ( buf );
      }

    } /* if ( ( display_unproved_ipr_flag ) || ( ! i ) ) */

    sel_str_arr [ i_i ] [ k_k ] = ':';

  } /* for ( i = 0 ; i < sel_arr_tot ; i++ ) */

  XtManageChild ( ipr_sel_rc );

  if ( scroll_visible ) {
    if ( scroll_visible_widget != ( Widget ) 0 ) {
      XmScrollVisible ( constructs_scroll, scroll_visible_widget, 0, 10 );
    }
  }

  DisplayIprRuleMenu ( 1, 0 );

}

XtCallbackProc
DisplayIprThyMenu_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;
  void DisplayIprThyMenu ();

  XtPopdown ( ( Widget ) client_data );
  XtDestroyWidget ( ipr_sel_rc );
  XmUpdateDisplay ( constructs_rc );
  XmUpdateDisplay ( top_level );
  if ( cbs->reason == XmCR_PROTOCOLS ) DisplayIprThyMenu ( 1, 1 );
  sprintf ( fifo_write_buf, "(?,0):" );
  Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
  InvokeB ( without_XTerm, 1 );
}

void
DisplayIprThyMenu ( flag, WM_flag )
int flag;
int WM_flag;
{
  static Widget dialog, dialog_form, B_logo, Label, menu_rc;
  XmString xstr;

  static int first_time = 1;
  static struct coord coord_data;

  static Atom  WM_DELETE_WINDOW;

  if ( ! flag ) {
    XtPopdown ( dialog );
    XmUpdateDisplay ( top_level );
    return;
  }

  if ( WM_flag ) {    /* DisplayIprThyMenu_CB - WM Close */
    XtDestroyWidget ( dialog );
    first_time = 1;
    return;
  }

  if ( first_time ) {

    first_time = 0;

    coord_data.x = -185;
    coord_data.y = 1;

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    dialog = XmCreateDialogShell ( top_frame_form, "SelDialog", NULL, 0 );

    XtAddCallback ( dialog, XmNpopupCallback,
        ( XtCallbackProc ) PositionWidgetRightMainWin_CB,
        ( XtPointer ) & coord_data );
    XmAddWMProtocolCallback ( dialog, WM_DELETE_WINDOW,
        ( XtCallbackProc ) DisplayIprThyMenu_CB,
              ( XtPointer ) dialog );

    dialog_form = XtVaCreateWidget ( "SelDialog",
        xmFormWidgetClass,         dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        False,  
        XmNautoUnmanage,           False,
        NULL );

    B_logo =  XtVaCreateWidget ( "SelDialog",
        xmPushButtonWidgetClass,    dialog_form,
        XmNlabelType,               XmPIXMAP,
        XmNlabelPixmap,             B_framed_pixmap_gray94,
        XmNshadowThickness,         0,
        XmNmarginWidth,             0,
        XmNmarginHeight,            0,
        XmNtopAttachment,           XmATTACH_FORM,
        XmNtopOffset,               10,
        XmNleftAttachment,          XmATTACH_FORM,
        XmNleftOffset,              10,
        XmNtraversalOn,             False,
        NULL );

    XtAddCallback ( B_logo, XmNactivateCallback,
                                    ( XtCallbackProc ) B_info_CB, NULL );

    xstr = XmStringCreate ( "Theory Menu", charset );

    Label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNleftOffset,             13,
        XmNrightOffset,            23,
        XmNlabelString,            xstr,
        XmNmarginWidth,            10,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

    menu_rc = XtVaCreateWidget ( "Canvas", 
        xmRowColumnWidgetClass,         dialog_form,
        XmNorientation,                 XmVERTICAL,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   55,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 5,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  5,
        XmNbottomAttachment,            XmATTACH_FORM,
        XmNbottomOffset,                35,
        XmNmarginWidth,                 5,
        XmNmarginHeight,                5,
        XmNspacing,                     5,
        XmNisHomogeneous,               False,
        NULL );

    CreHighlightedButton ( menu_rc, "       Exit InterProver", 
              ( XtCallbackProc ) DisplayIprThyMenu_CB,
              ( XtPointer ) dialog );

    XtManageChild ( B_logo );
    XtManageChild ( Label );
    XtManageChild ( menu_rc );
    XtManageChild ( dialog_form );
  }

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
  XmUpdateDisplay ( top_level );
}

XtCallbackProc
Ipr_Sel_Thy_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  int i;
  int sel_str_num =  * ( int * ) client_data;

  XtDestroyWidget ( ipr_sel_rc );
  DisplayIprThyMenu ( 0, 0 );

  i = 3;
  while ( sel_str_arr [ sel_str_num ] [ i ] != ' ' ) { i++; }
  sel_str_arr [ sel_str_num ] [ i ] = '\0';

  if ( strcmp ( prev_thy, sel_str_arr [ sel_str_num ] ) != 0 ) {
    prev_thy [ 0 ] = '\0';
    prev_rule = 0;
  }

  sprintf ( fifo_write_buf, "(?,%s):", sel_str_arr [ sel_str_num ] );
  Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
  InvokeB ( without_XTerm, 1 );
}

void
Ipr_Sel_Thy ()
{
  XmString xstr;
  Widget but, label_form;
  int i, l;

  XtDestroyWidget ( constructs_rc );
  constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
      xmRowColumnWidgetClass,         constructs_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 18,
      XmNmarginHeight,                10,
      XmNspacing,                     0,
      XmNresizable,                   True,
      NULL );
  XmUpdateDisplay ( constructs_rc );
  XmUpdateDisplay ( constructs_scroll );
  XmUpdateDisplay ( constructs_form );

  ipr_sel_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         constructs_rc,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNspacing,                     5,
      XmNisHomogeneous,               False,
      NULL );

  label_form = XtVaCreateWidget ( "Label", 
    xmFormWidgetClass,             ipr_sel_rc,
    NULL );

  xstr = XmStringCreateLtoR ( "Theories", charset );
  TRBut [ 0 ] = XtVaCreateManagedWidget ( "Label",
    xmLabelWidgetClass,             label_form,
    XmNlabelString,                 xstr,
    XmNmarginWidth,                 20,
    XmNleftAttachment,              XmATTACH_FORM,
    XmNtraversalOn,                 False,
    NULL );
  XmStringFree ( xstr );

  xstr = XmStringCreateLtoR ( "(Click a Theory to select)", charset );
  XtVaCreateManagedWidget ( "Highlight", 
    xmLabelWidgetClass,             label_form,
    XmNlabelString,                 xstr,
    XmNmarginWidth,                 0,
    XmNleftAttachment,              XmATTACH_WIDGET,
    XmNleftWidget,                  TRBut [ 0 ],
    XmNleftOffset,                  0,
    XmNtraversalOn,                 False,
    NULL );
  XmStringFree ( xstr );

  XtManageChild ( label_form );

  strcpy ( buf, "     " );
  l = strlen ( sel_str_arr [ 0 ] ) - 15;
  for ( i = 1 ; i < l ; i++ ) {
    strcat ( buf, " " );
  }
  strcat ( buf, "  tot    pob");
  xstr = XmStringCreateLtoR ( buf, charset );
  XtVaCreateManagedWidget ( "Label", 
    xmLabelWidgetClass,             ipr_sel_rc,
    XmNlabelString,                 xstr,
    XmNmarginWidth,                 30,
    XmNmarginHeight,                5,
    XmNtraversalOn,                 False,
    NULL );
  XmStringFree ( xstr );

  for ( i = 0 ; i <  sel_arr_tot ; i++ ) {
    if ( i && ( sel_str_arr [ i ] [ 0 ] != ' ' ) ) {
        CreSmallPassiveButton ( ipr_sel_rc, "" );
    }
    but = CreHighlightedButton ( ipr_sel_rc, sel_str_arr [ i ],
              ( XtCallbackProc ) Ipr_Sel_Thy_CB,
              & c_arr [ i ] );
  }

  XtManageChild ( ipr_sel_rc );

  DisplayIprThyMenu ( 1, 0 );

}

void
Popup_SetMaxGenHyp_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
  char * text;

  XtUnmanageChild ( prompt_dialog );
  XmUpdateDisplay ( prompt_dialog );

  if ( * ( int * ) client_data == OK_BUTTON ) {
    void CheckAndSet_max_fwd_ctr_auto_prf ();
    XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text );
    CheckAndSet_max_fwd_ctr_auto_prf ( text );
    XtFree ( text );
    if ( curr_env == ipr_pob_env ) {
      strcpy ( fifo_write_buf, "(?,5):" );   /* InterProve_max_fwd_Option */
      Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
      InvokeB ( without_XTerm, 1 );
    }
    else if ( curr_env == ipr_lem_env ) {
      strcpy ( fifo_write_buf, "(?,4):" );   /* ProveLemma_max_fwd_Option */
      Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
      InvokeB ( without_XTerm, 1 );
    }
    else {  /* btl_env */
      /*** must agree with #define in motif.c ***/
      Proof_CB_continued ( /* run_Proof_CB */ TRUE , /* proof_step_flag_NO */ 0 );
    }
  }
  else { /* CANCEL_BUTTON */
    if ( curr_env == btl_env ) {
      /*** must agree with #define in motif.c ***/
      Proof_CB_continued ( /* run_Proof_CB */ TRUE , /* proof_step_flag_NO */ 0 );
    }
    else {
      Ipr_Sel_Ops ( top_level, Ipr_Prf_Option, 0 );
    }
  }
}

void
Popup_SetMaxGenHyp ()
{
  static Widget dialog = ( Widget ) 0;
  static struct coord coord_data;

  XmString xstr;

  coord_data.x = 0; /* not used */
  coord_data.y = 150;

  if ( ! dialog ) {

    /***
    create the dialog
    ***/
    dialog = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
    XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNautoUnmanage,           False,
        XmNwidth,                  250,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultButtonType,      XmNONE,
        NULL );

    /***
    add the callbacks
    ***/
    XtAddCallback ( dialog, XmNokCallback,
        ( XtCallbackProc ) Popup_SetMaxGenHyp_CB,
        ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( dialog, XmNcancelCallback,
        ( XtCallbackProc ) Popup_SetMaxGenHyp_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
    XtAddCallback ( dialog, XmNhelpCallback,
        ( XtCallbackProc ) Popup_PromptDialogHelp_CB, NULL );
   }

   /***
    static dialog exists - prompt
    ***/
  {
    char str [ 100 ];
    XmString xstr;

    strcpy ( str, "Set Max Generated Hypotheses:" );
    xstr = XmStringCreateLocalized ( str );
    XtVaSetValues ( dialog,
        XmNselectionLabelString,     xstr,
        NULL );
    XmStringFree ( xstr );
  }

  valIth_flags ( &max_fwd_ctr_auto_prf, Provers_max_fwd_Option_num );
  sprintf ( buf, "%d", max_fwd_ctr_auto_prf );
  xstr = XmStringCreateLocalized ( buf );
  XtVaSetValues ( dialog, XmNtextString, xstr, NULL );
  XmStringFree ( xstr );

  /***
  set secondary_string (for help )
  ***/
  secondary_string [ 0 ] = 'h';
  XtManageChild ( dialog );

  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Ipr_Sel_Ops ( parent, option, WM_flag )
Widget parent;
int option;
int WM_flag;
{
#define Ipr_Ops_help_pob_width  500
#define Ipr_Ops_help_pob_height 500

#define Ipr_Ops_help_text_pob "\
  o `Run InterProver' runs the prover on the Current Goal\n\n\
  o `Continue' either attempts to prove the Current Goal or,\n\
    if it can't be proved, backtracks up the `proof tree' selecting\n\
    the goal immediately prior to the Current Goal, and\n\
    attempts to prove that goal using a different tactic\n\n\
  o `Show Hypotheses' gives a listing of the hypotheses\n\
    corresponding to the Current Goal\n\n\
  o `Create Lemma' discharges the Current Goal\n\
    through the creation of a Lemma\n\n\
  o `Create & Prove Lemma' performs `Create Lemma', selects\n\
    selects that lemma and proves it\n\n\
  o `Edit Current PROOFMETHOD file'/`Edit Global PROOFMETHOD file'\n\
     opens the current PROOFMETHOD file/the Global file set in\n\
     Top Bar Options - Provers; if the Global file was set before\n\
     the creation of the current PROOFMETHOD file, it will\n\
     automatically appear in its INCLUSIONS clause.\n\n\
  o `Browse PROOFMETHOD file' provides a selection of \n\
    PROOFMETHOD files which may be opened for browsing.\n\n\
  o `InterProver Depth' can be set during the initial\n\
    proving phase to find an appropriate reasoning depth for the\n\
    creation of lemmas. Note that the PROOFMETHOD is not loaded\n\
    at this stage, and so neither the REASONING_DEPTH\n\
    nor any user-theory is consulted.\n\n\
      o `InterProver Depth 0' expands the hypothesis so that all CONSTRAINTS,\n\
        INVARIANT, PROPERTIES and PRECONDITION predicates appear, but\n\
        without the application of mathematical theory (except that necessary\n\
        to establish a contradiction - where applicable).\n\n\
      o `InterProver Depth 1' is as `Depth 0' but with the application of `Standard'\n\
      mathematical rules from the library.\n\n\
      o `InterProver Depth 2' is as `Depth 0' but with the application of all\n\
        mathematical rules from the library.\n\n\
            Once a lemma has been created and its proof attempted, however, the\n\
            PROOFMETHOD is loaded and the proof proceeds at the depth dictated by\n\
            its REASONING_DEPTH clause - i.e. the InterProver Reasoning Depth\n\
            plays no further part. However if the REASONING_DEPTH is lower that\n\
            the InterProver Reasoning Depth at which lemmas have been created,\n\
            a warning is issued (since this might affect the subsequent behavior\n\
            of the AutoProver which, of course, relies only on the PROOFMETHOD).\n\
            The tactic used in the proof attempt of the lemma is dictated by the\n\
            USETAC clause, and any user-theory provided is consulted (where\n\
            applicable) if its THEORY name forms part of the USETAC.\n\
        A fuller explanation is given in Top Bar Help for `InterProver'.\n\n\
  o `Cancel' returns to `Undischarged Theories' option\n\n\
Note that all options are not always available."

#define Ipr_Ops_help_lem_width  500
#define Ipr_Ops_help_lem_height 450
#define Ipr_Ops_help_text_lem "\
  o `Run InterProver' runs the prover on the Lemma\n\n\
  o `Show Hypotheses' gives a listing of the hypotheses\n\
    corresponding to the current goal\n\n\
  o `Reload PROOFMETHOD' reloads the users Proof Method\n\
    in readiness for another attempt at the lemma\n\n\
  o `Browse PROOFMETHOD file' provides a selection of\n\
    PROOFMETHOD files which may be opened for browsing.\n\n\
  o `Cancel' returns to `Undischarged Theories' option\n\n\
  o `Edit Current PROOFMETHOD file'/`Edit Global PROOFMETHOD file'\n\
     opens the current PROOFMETHOD file/the Global file set in\n\
     Top Bar Options - Provers; if the Global file was set before\n\
     the creation of the current PROOFMETHOD file, it will\n\
     automatically appear in its INCLUSIONS clause.\n\n\
  o `Browse PROOFMETHOD file' provides a selection of \n\
    PROOFMETHOD files which may be opened for browsing.\n\n\
Note that all options are not always available."

  static Widget dialog_form,
                radio_box_scroll, radio_box,
                radio_box_rc,
                B_logo,
                sep,
                reasoning_depth_but,
                och_form, och_o, och_c, och_h, och_a, och_n,
                label;

  static Atom   WM_DELETE_WINDOW;

  static struct help_struct help_data;
  static struct coord coord_data;

  static int first_time = 1;

  int nm [ 50 ], ex, cc, st, i, is_lemma;
  int pmd_level;
  XmString xstr;
  Widget but;

  is_lemma = 0;

  if ( WM_flag ) {
    XtPopdown ( ipr_ops_dialog );
    XmUpdateDisplay ( ipr_ops_dialog );
    XtDestroyWidget ( ipr_ops_dialog );
    first_time = 1;
    return;
  }

  if ( first_time ) {

    first_time = 0;

    /***
    Create the basic dialog
    ***/
    Cre_Sel_Dialog ( & parent, & ipr_ops_dialog, & dialog_form,
                     & radio_box_scroll, & radio_box,
                     & B_logo,
                     & sep,
                     & och_form, & och_o, & och_c, & och_h, & och_a, & och_n,
                     & help_data, & label,
                     SelLarge_flag_NO,
		     & WM_DELETE_WINDOW,
                     0 );

    coord_data.x = 285;
    coord_data.y = 1;

    XtAddCallback ( ipr_ops_dialog, XmNpopupCallback,
        ( XtCallbackProc ) PositionWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    if ( option <= BT_POB_R___M ) {
      help_data.text   = ( char * ) Ipr_Ops_help_text_pob;
      help_data.width  = Ipr_Ops_help_pob_width;
      help_data.height = Ipr_Ops_help_pob_height;
    }
    else {
      help_data.text   = ( char * ) Ipr_Ops_help_text_lem;
      help_data.width  = Ipr_Ops_help_lem_width;
      help_data.height = Ipr_Ops_help_lem_height;
    }

    /***
    unmanage och_a och_n
    ***/
    XtUnmanageChild ( och_a );
    XtUnmanageChild ( och_n );

    /***
    Adjust basic dialog
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );
    XtVaSetValues ( och_o,
        XmNleftOffset,                  9,
        NULL );
    XtVaSetValues ( och_c,
        XmNleftOffset,                  0,
        NULL );
    XtVaSetValues ( och_h,
        XmNrightOffset,                 9,
        NULL );
    XtVaSetValues ( radio_box_scroll,
	XmNheight,                      280,
        NULL );
    XtVaSetValues ( sep,
        XmNwidth,                       230,
        NULL );

/***
printf ( "post adjust: %x %x %x %x\n", dialog_form, sep, och_c, radio_box_scroll ); fflush ( stdout );
***/

/***
printf ( "1 radio_box %x\n", radio_box ); fflush ( stdout );
***/
    /***
    create RadioBox in Scroll
    ***/
    radio_box = XmCreateRadioBox ( radio_box_scroll, "SelDialog", NULL, 0 );
    XtVaSetValues ( radio_box,
        XmNisHomogeneous,          False,
        XmNspacing,                0,
        NULL );

/***
printf ( "2 radio_box %x\n", radio_box ); fflush ( stdout );
***/

/***
printf ( "1 label %x\n", label ); fflush ( stdout );
***/

    /***
    destroy previous label & recreate
    ***/
    XtDestroyWidget ( label );
    xstr = XmStringCreateLtoR ( "InterProver Operation", charset );
    label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,             dialog_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   10,
        XmNleftAttachment,              XmATTACH_WIDGET,
        XmNleftWidget,                  B_logo,
        XmNleftOffset,                  5,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNlabelString,                 xstr,
        XmNmarginWidth,                 10,
        XmNmarginHeight,                10,
        NULL );
    XmStringFree ( xstr );
  
/***
printf ( "2 label %x\n", label ); fflush ( stdout );
***/

    XtManageChild ( label );
    XtManageChild ( radio_box_scroll );
    XtManageChild ( radio_box );
    XtManageChild ( och_o );
    XtManageChild ( och_c ); 
    XtManageChild ( och_h );
    XtManageChild ( och_form );
    XtManageChild ( B_logo );
    XtManageChild ( sep );
    XtManageChild ( dialog_form );
    XtRealizeWidget ( ipr_ops_dialog );

  } /* first_time */


  /***
  reset Ipr_Prf_Level_dialog_isdplayed
  ***/
  Ipr_Prf_Level_dialog_isdplayed = 0;

  /***
  remember option
  ***/
  Ipr_Prf_Option = option;

  /***
  set pmd_level
  ***/
  GetExtNumFromString ( &ex, secondary_string );
  GetNameFromString ( nm, secondary_string );
  GetObjFromNameExt ( &cc, nm, ex );
  val_curMRIState( &st, cc );
  length_pob ( &pmd_level, st );

  /***
  Reset help data
  ***/
  if ( option <= BT_POB_R___M ) {
    help_data.text   = ( char * ) Ipr_Ops_help_text_pob;
    help_data.width  = Ipr_Ops_help_pob_width;
    help_data.height = Ipr_Ops_help_pob_height;
  }
  else {
    help_data.text   = ( char * ) Ipr_Ops_help_text_lem;
    help_data.width  = Ipr_Ops_help_lem_width;
    help_data.height = Ipr_Ops_help_lem_height;
  }


  /***
  set sel_str_arr
  ***/
  switch ( option ) {

    case BT_POB_RHL_M:
      strcpy ( sel_str_arr [ 0 ], "Continue" );
      strcpy ( sel_str_arr [ 1 ], "Show Hypotheses" );
      strcpy ( sel_str_arr [ 2 ], "Create Lemma" );
      sel_arr_tot = 3;
      break;

    case BT_POB_RH__M:
      strcpy ( sel_str_arr [ 0 ], "Run InterProver" );
      strcpy ( sel_str_arr [ 1 ], "Create Lemma" );
      strcpy ( sel_str_arr [ 2 ], "Create & Prove Lemma" );
      sel_arr_tot = 3;
      Ipr_Prf_Level_dialog_isdplayed = 1;
      break;

    case BT_POB_R_L_M:
      strcpy ( sel_str_arr [ 0 ], "Continue" );
      strcpy ( sel_str_arr [ 1 ], "Create Lemma" );
      sel_arr_tot = 2;
      break;

    case BT_POB_R___M:
      strcpy ( sel_str_arr [ 0 ], "Run InterProver" );
      sel_arr_tot = 1;
      Ipr_Prf_Level_dialog_isdplayed = 1;
      break;

    case BT_LEM_RHR_M:
      strcpy ( sel_str_arr [ 0 ], "Run InterProver" );
      strcpy ( sel_str_arr [ 1 ], "Show Hypotheses" );
      strcpy ( sel_str_arr [ 2 ], "Reload PROOFMETHOD" );
      sel_arr_tot = 3;
      is_lemma = 1;
      break;

    case BT_LEM_R_R_M:
    case BT_LEM__HR_M:
      strcpy ( sel_str_arr [ 0 ], "Run InterProver" );
      strcpy ( sel_str_arr [ 1 ], "Reload PROOFMETHOD" );
      sel_arr_tot = 2;
      is_lemma = 1;
      break;

    case BT_LEM___R_M:
      strcpy ( sel_str_arr [ 0 ], "Reload PROOFMETHOD" );
      sel_arr_tot = 1;
      is_lemma = 1;
      break;
  }

  /***
  destroy previous RadioBox and recreate
  ***/
/***
printf ( "destroy radio_box_scroll %x\n", radio_box ); fflush ( stdout );
***/

  XtDestroyWidget ( radio_box_scroll );
  radio_box_scroll = XtVaCreateWidget ( "SelDialog",
      xmScrolledWindowWidgetClass,    dialog_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   45,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 5,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  5,
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                sep,
      XmNbottomOffset,                5,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNwidth,                       170,
      XmNheight,                      175,
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNspacing,                     0,
      NULL );
  radio_box = XmCreateRadioBox ( radio_box_scroll, "SelDialog", NULL, 0 );
  XtVaSetValues ( radio_box,
      XmNorientation,            XmVERTICAL,
      XmNisHomogeneous,          False,
      XmNspacing,                0,
      NULL );
/***
printf ( "create  radio_box %x\n", radio_box ); fflush ( stdout );
***/

  /***
  create buttons in RadioBox
  ***/

  /***
  first button
  ***/
  but = XtVaCreateManagedWidget ( sel_str_arr [ 0 ],
      xmToggleButtonGadgetClass,     radio_box,
      XmNspacing,                    2,
      XmNhighlightThickness,         1,
      XmNnavigationType,             XmTAB_GROUP,
      NULL );
  XtAddCallback ( but, XmNvalueChangedCallback,
      ( XtCallbackProc ) ToggleBox_CB, ( XtPointer ) & c_arr [ 0 ] );

  XmToggleButtonSetState ( but, True, False );
  sel_arr_tog [ 0 ] = 1;

  /***
  rest
  ***/
  for ( i = 1; i < sel_arr_tot ; i++ ) {
    but = XtVaCreateManagedWidget ( sel_str_arr [ i ],
        xmToggleButtonGadgetClass,     radio_box,
        XmNspacing,                    2,
        XmNhighlightThickness,         1,
        XmNnavigationType,             XmTAB_GROUP,
        NULL );
    XtAddCallback ( but, XmNvalueChangedCallback,
        ( XtCallbackProc ) ToggleBox_CB, ( XtPointer ) & c_arr [ i ] );
    sel_arr_tog [ i ] = 0;
  }

  /***
  separator
  ***/
  XtVaCreateManagedWidget ( "SelDialog",
      xmSeparatorGadgetClass,        radio_box,
      XmNspacing,                    0,
      NULL );


  if ( ( Ipr_Prf_Level_dialog_isdplayed ) || ( is_lemma ) ) {
    strcpy ( sel_str_arr [ sel_arr_tot ], "Set Max Generated Hypotheses" );
    but = XtVaCreateManagedWidget ( sel_str_arr [ sel_arr_tot ],
        xmToggleButtonGadgetClass,     radio_box,
        XmNspacing,                    2,
        XmNhighlightThickness,         1,
        XmNnavigationType,             XmTAB_GROUP,
        NULL );
    XtAddCallback ( but, XmNvalueChangedCallback,
        ( XtCallbackProc ) ToggleBox_CB, ( XtPointer ) & c_arr [ sel_arr_tot ] );
    sel_arr_tog [ sel_arr_tot ] = 0;
    XtVaCreateManagedWidget ( "SelDialog",
        xmSeparatorGadgetClass,        radio_box,
        XmNspacing,                    0,
        NULL );
    sel_arr_tot++;
  }

  /***
  depth selection
  ***/
  if ( Ipr_Prf_Level_dialog_isdplayed ) {
    XmString xstr =  XmStringCreateLtoR ( "", charset );
    XmString xstr0 =  XmStringCreateLtoR ( "   InterProver Depth 0  ", charset );
    XmString xstr1 =  XmStringCreateLtoR ( "   InterProver Depth 1  ", charset );
    XmString xstr2 =  XmStringCreateLtoR ( "   InterProver Depth 2  ", charset );

    valIth_flags ( &pmd_level, Ipr_Prf_Level_num );
    reasoning_depth_but =
        XmVaCreateSimpleOptionMenu ( radio_box, "Option",
        xstr, 0,
	/* pmd_level, */ 2, IprReasoningDepth_CB,
        XmVaPUSHBUTTON, xstr0, NULL, NULL, NULL,
        XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
        XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
        /* 
        XmNmarginWidth,            0,
        XmNmarginHeight,           0,
        */
        XmNhighlightThickness,     1,
        XmNnavigationType,         XmTAB_GROUP,
        NULL);

    XmStringFree ( xstr );
    XmStringFree ( xstr0 );
    XmStringFree ( xstr1 );
    XmStringFree ( xstr2 );

   XtVaSetValues ( reasoning_depth_but,
        XmNshadowThickness,        0,
	/*
        XmNmarginWidth,            0,
        XmNmarginHeight,           0,
	*/
        XmNdefaultButtonShadowThickness,     1,
        XmNhighlightThickness,     1,
        XmNnavigationType,         XmTAB_GROUP,
        NULL);

    XtManageChild ( reasoning_depth_but );
  }

  /***
  last 3 button(s)
  ***/

  strcpy ( sel_str_arr [ sel_arr_tot++ ], "Edit Current PROOFMETHOD file" );
  strcpy ( sel_str_arr [ sel_arr_tot++ ], "Edit Global PROOFMETHOD file" );
  strcpy ( sel_str_arr [ sel_arr_tot++ ], "Browse PROOFMETHOD file" );
  
  for ( i = sel_arr_tot - 3; i < sel_arr_tot ; i++ ) {
    but = XtVaCreateManagedWidget ( sel_str_arr [ i ],
        xmToggleButtonGadgetClass,     radio_box,
        XmNspacing,                    2,
        XmNhighlightThickness,         1,
        XmNnavigationType,             XmTAB_GROUP,
        NULL );
    XtAddCallback ( but, XmNvalueChangedCallback,
        ( XtCallbackProc ) ToggleBox_CB, ( XtPointer ) & c_arr [ i ] );
    sel_arr_tog [ i ] = 0;
  }

  /***
  reset second_visit & SelOne_flagged
  ***/
  SelOne_flagged = 1;
  second_visit = 0;

  /***
  set sel option
  ***/
  Popup_Sel_flag = interprover_selection;

  XtManageChild ( radio_box_scroll );
  XtManageChild ( radio_box );

  XtPopup ( ipr_ops_dialog, XtGrabNone );
  XmUpdateDisplay ( ipr_ops_dialog );
}

void
Ipr ( option )
int option;
{
  XtUnmanageChild ( constructs_scroll );
  XmUpdateDisplay ( constructs_scroll );
  XmUpdateDisplay ( constructs_form );

  XtDestroyWidget ( constructs_rc );
  constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
      xmRowColumnWidgetClass,         constructs_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 18,
      XmNmarginHeight,                10,
      XmNspacing,                     0,
      XmNresizable,                   True,
      NULL );

  /***
  set ipr_pob_env/ipr_lem_env
  ***/
  if   ( option <= BT_POB_R___M ) curr_env = ipr_pob_env;
  else                            curr_env = ipr_lem_env;

  /***
  create ipr_label in constructs_rc
  ***/
  {
    char lab [ 100 ];
    XmString xstr;

    strcpy ( lab, secondary_string );
    strcat ( lab, ": " );
    strcat ( lab, primary_string );
    xstr = XmStringCreateLtoR ( lab, charset );
    ipr_label = XtVaCreateManagedWidget ( lab_types [ usr ], 
      xmLabelWidgetClass,          constructs_rc,
      XmNlabelString,              xstr,
      NULL );
    XmStringFree ( xstr );
  }

  /***
  create sub_frame1 in constructs_rc
  ***/
  sub_frame1 = XtVaCreateWidget ( "Canvas",
      xmFrameWidgetClass,          constructs_rc,
      XmNshadowType,               XmSHADOW_OUT,
      NULL );

  /***
  create sub_text1 in sub_frame1
  ***/
  sub_text1 = XtVaCreateWidget ( "Ipr",
      xmTextWidgetClass,           sub_frame1,
      XmNcursorPositionVisible,    False,
      XmNeditable,                 False,
      XmNeditMode,                 XmMULTI_LINE_EDIT,
      XmNmarginWidth,              7,
      XmNmarginHeight,             7,
      XmNborderWidth,              0,
      XmNshadowThickness,          0,
      XmNwordWrap,                 False, /**/
      XmNscrollHorizontal,         False, /**/
      XmNscrollVertical,           False, /**/
      XmNresizeHeight,             True,
      XmNresizeWidth,              True,
      NULL );

  LoadFileIntoBuf ( ".Bsel", buf, MAX_buf - 1 );
  XmTextSetString ( sub_text1, buf );

  if ( curr_env == ipr_pob_env ) {

    /***
    create sub_frame2 in constructs_rc
    ***/
    sub_frame2 = XtVaCreateWidget ( "Canvas",
        xmFrameWidgetClass,          constructs_rc,
        XmNshadowType,               XmSHADOW_OUT,
        NULL );

  /***
  create sub_text2 in sub_frame2
  ***/

  sub_text2 = XtVaCreateWidget ( "Ipr",
      xmTextWidgetClass,           sub_frame2,
      XmNcursorPositionVisible,    False,
      XmNeditable,                 False,
      XmNeditMode,                 XmMULTI_LINE_EDIT,
      XmNmarginWidth,              7,
      XmNmarginHeight,             7,
      XmNborderWidth,              0,
      XmNshadowThickness,          0,
      XmNwordWrap,                 False, /**/
      XmNscrollHorizontal,         False, /**/
      XmNscrollVertical,           False, /**/
      XmNresizeHeight,             True,
      XmNresizeWidth,              True,
      NULL );

  LoadFileIntoBuf ( ".Bcom", buf, MAX_buf - 1 );
  XmTextSetString ( sub_text2, buf );

  }

  /***
  manage
  ***/
  XtManageChild ( sub_text1 );
  XtManageChild ( sub_frame1 );
  if ( curr_env == ipr_pob_env ) {
    XtManageChild ( sub_text2 );
    XtManageChild ( sub_frame2 );
  }
  XtManageChild ( constructs_rc );
  XtManageChild ( constructs_scroll );
  if ( curr_env == ipr_pob_env ) {
    XmScrollVisible ( constructs_scroll, sub_frame2, 0, 0 );
  }
  else {
    XmScrollVisible ( constructs_scroll, sub_frame1, 0, 0 );
  }

  /***
  cre selection dialog
  ***/
  Ipr_Sel_Ops ( top_level, option, 0 );
}


/***********************************************************************
************************************************************************
                         Main Window
************************************************************************
***********************************************************************/


void
Re_Cre_Top_Bar_Utils_Pulldown ()
{
  XmString xstr;
  int      j;

  for ( j = 1 ; j <= 5 ; j++ ) {
    CreOptionUtilityLabelInStrBuf ( j );
    xstr = XmStringCreateLocalized ( str_buf );
    XtVaSetValues (  Utils_Options_PullDown_PushButtons [ j ],
		     XmNlabelString, xstr,
		     NULL );
  }
  XmStringFree ( xstr );
}

void
Re_Cre_Top_Bar_Utils_Pulldown_OLD ()
{
  XmString xstr;

/***
  printf("XtUnmanageChild ( top_bar ) %d %d\n",top_bar,XtIsManaged(top_bar));fflush(stdout);
***/
  XtUnmanageChild ( top_bar );

/***
printf("Re_Cre_Top_Bar_Utils_Pulldown\n");
***/
/***
  printf("XtUnmanageChild ( UtilsPullDown ) %d %d\n",UtilsPullDown,XtIsManaged(UtilsPullDown));fflush(stdout);
***/
  XtUnmanageChild ( UtilsPullDown );
print_debug(100001);
/***
printf("XtUnmanageChild ( IntroducePullDown ) %d %d\n",IntroducePullDown,XtIsManaged(IntroducePullDown));fflush(stdout);
***/
  XtUnmanageChild ( IntroducePullDown );
print_debug(100002);
/***
printf("XtUnmanageChild ( ConstructPullDown ) %d %d\n",ConstructPullDown,XtIsManaged(ConstructPullDown));fflush(stdout);
***/
  XtUnmanageChild ( ConstructPullDown );
print_debug(100003);

#ifndef HOLLOWAY_FLAG
/***
printf("XtUnmanageChild ( RemakePullDown ) %d %d\n",RemakePullDown,XtIsManaged(RemakePullDown));fflush(stdout);
***/
  XtUnmanageChild ( RemakePullDown );
#endif

print_debug(100004);
/***
printf("XtUnmanageChild ( BrowsePullDown ) %d %d\n",BrowsePullDown,XtIsManaged(BrowsePullDown));fflush(stdout);
***/
  XtUnmanageChild ( BrowsePullDown );
print_debug(100005);
/***
printf("XtUnmanageChild ( OptionsPullDown ); %d %d\n",OptionsPullDown,XtIsManaged(OptionsPullDown));fflush(stdout);
***/
  XtUnmanageChild ( OptionsPullDown );
print_debug(100006);
/***
printf("XtUnmanageChild ( InterruptPullDown ) %d %d\n",InterruptPullDown,XtIsManaged(InterruptPullDown));fflush(stdout);
***/
  XtUnmanageChild ( InterruptPullDown );
print_debug(100007);

  XtDestroyWidget ( UtilsPullDown );
print_debug(100008);
  XtDestroyWidget ( IntroducePullDown );
print_debug(100009);
  XtDestroyWidget ( ConstructPullDown );
#ifndef HOLLOWAY_FLAG
print_debug(100010);
  XtDestroyWidget ( RemakePullDown );
#endif
print_debug(100011);
  XtDestroyWidget ( BrowsePullDown );
print_debug(100012);
  XtDestroyWidget ( OptionsPullDown );
print_debug(100013);
  XtDestroyWidget ( InterruptPullDown );
print_debug(100014);


  Cre_Top_Bar_Utils_Pulldown ();
print_debug(100015);
  IntroducePullDown = Cre_Top_Bar_Pulldown ( top_bar, "Introduce",
                        Introduce_menu, TopBar_Introduce_CB );
/***
printf("IntroducePullDown 2 - %d\n", IntroducePullDown );fflush(stdout);
***/

print_debug(100016);
  ConstructPullDown = Cre_Top_Bar_Pulldown ( top_bar, "Construct",
                        Construct_menu, TopBar_Construct_CB );
/***
printf("ConstructPullDown 2 - %d\n", ConstructPullDown );fflush(stdout);
***/

#ifndef HOLLOWAY_FLAG
print_debug(100017);
  RemakePullDown = Cre_Top_Bar_Pulldown ( top_bar, "Remake",
                     Remake_menu, TopBar_Remake_CB );

/***
printf("RemakePullDown 2 - %d\n", RemakePullDown );fflush(stdout);
***/
#endif

print_debug(100018);
  BrowsePullDown = Cre_Top_Bar_Pulldown ( top_bar, "Browse",
                     Browse_menu, TopBar_Browse_CB );
/***
printf("BrowsePullDown 2 - %d\n",BrowsePullDown  );fflush(stdout);
***/

print_debug(100019);
  Cre_Options_Pulldown ( top_bar );

print_debug(100020);
  xstr = XmStringCreateLtoR ( "Interrupt", charset );
print_debug(100021);
  InterruptPullDown = XtVaCreateManagedWidget ( "Interrupt",
      xmCascadeButtonGadgetClass,     top_bar,
      XmNlabelString,                 xstr,
      NULL);

/***
printf("InterruptPullDown 2 - %d\n", InterruptPullDown );fflush(stdout);
***/

print_debug(100022);
  XmStringFree ( xstr );
print_debug(100023);
  XtAddCallback ( InterruptPullDown, XmNactivateCallback,
                    ( XtCallbackProc )TopBar_Interrupt_CB, NULL );
print_debug(100024);
  XtSetSensitive ( InterruptPullDown, False );
print_debug(100025);

  XtUnmanageChild ( HelpPullDown );
print_debug(100026);
  XtDestroyWidget ( HelpPullDown );
print_debug(100027);
  HelpPullDown = Cre_Help_Pulldown ( top_bar, "Help", Help_menus );
print_debug(100028);
  XtVaSetValues ( top_bar,
      XmNmenuHelpWidget,            HelpPullDown,
      NULL );
print_debug(100029);

/***
  printf("XtManageChild ( top_bar ) %d \n",top_bar);fflush(stdout);
***/
  XtManageChild ( top_bar );

}

void
Cre_MainWindow ( panel_shell )
Widget panel_shell;

{
  XmString xstr;
  int leftrightOffset=1;
  int scrollOffset=10; /* 15 */
  int commandOffset=10+scrollOffset+leftrightOffset;/* 26 */
  char notice[255];


  /***
  main form with User Data
  ***/
  main_form = XtVaCreateWidget ( "MainWin",
      xmFormWidgetClass,          panel_shell,
      XmNuserData,                ( XtPointer ) & c_arr [ 0 ],
      NULL );

  /***
  top bar in main form
  ***/
  top_bar = XmCreateMenuBar ( main_form, "TopBar", NULL, 0 );
  XtVaSetValues ( top_bar, 
      XmNtopAttachment,           XmATTACH_FORM,
      XmNleftAttachment,          XmATTACH_FORM,
      XmNrightAttachment,         XmATTACH_FORM,
      XmNspacing,                 /* 4, */ 0,
      XmNmarginHeight,            5,
      XmNmarginWidth,             /* 10, */ 5,
      XmNadjustLast,              False,
      /* - shaded background image */
      XmNbackgroundPixmap,       B_topbar_pixmap,
      NULL );

  /***
  create TopBar PullDowns
  ***/
  Cre_Top_Bar_Utils_Pulldown ();

  IntroducePullDown = Cre_Top_Bar_Pulldown ( top_bar, "Introduce",
                        Introduce_menu, TopBar_Introduce_CB );
/***
printf("IntroducePullDown 1 - %d\n", IntroducePullDown );fflush(stdout);
***/

  ConstructPullDown = Cre_Top_Bar_Pulldown ( top_bar, "Construct",
                        Construct_menu, TopBar_Construct_CB );

/***
printf("ConstructPullDown 1 - %d\n", ConstructPullDown );fflush(stdout);
***/

#ifndef HOLLOWAY_FLAG
  RemakePullDown = Cre_Top_Bar_Pulldown ( top_bar, "Remake",
                     Remake_menu, TopBar_Remake_CB );
/***
printf("RemakePullDown 1 - %d\n", RemakePullDown );fflush(stdout);
***/
#endif

  BrowsePullDown = Cre_Top_Bar_Pulldown ( top_bar, "Browse",
                     Browse_menu, TopBar_Browse_CB );
/***
printf("BrowsePullDown 1 - %d\n", BrowsePullDown );fflush(stdout);
***/

  Cre_Options_Pulldown ( top_bar );

  xstr = XmStringCreateLtoR ( "Interrupt", charset );
  InterruptPullDown = XtVaCreateManagedWidget ( "Interrupt",
      xmCascadeButtonGadgetClass,     top_bar,
      XmNlabelString,                 xstr,
      NULL);
  XmStringFree ( xstr );
  XtAddCallback ( InterruptPullDown, XmNactivateCallback,
                    ( XtCallbackProc )TopBar_Interrupt_CB, NULL );
  XtSetSensitive ( InterruptPullDown, False );

  HelpPullDown = Cre_Help_Pulldown ( top_bar, "Help", Help_menus );
  XtVaSetValues ( top_bar,
      XmNmenuHelpWidget,            HelpPullDown,
      NULL );

/***
printf("InterruptPullDown 1 - %d\n", InterruptPullDown );fflush(stdout);
***/

  /***
  toolkit pane in main form
  ***/
  main_form_pane = XtVaCreateWidget ( "MainWin", 
      xmPanedWindowWidgetClass,       main_form,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   top_bar,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNbottomAttachment,            XmATTACH_FORM,
      /* */
      XmNspacing,                     2,
      XmNmarginWidth,                 0,
      XmNmarginHeight,                0,
      XmNseparatorOn,                 False,
      XmNsashIndent,                  -1,
      XmNsashHeight,                  7,
      XmNsashWidth,                   64,
      XmNsashShadowThickness,         1,
      NULL );

  /***
  top_frame_form in toolkit pane
  ***/
  top_frame_form = XtVaCreateWidget ( "MainWin", 
      xmFormWidgetClass,              main_form_pane,
      XmNpaneMinimum,                 top_frame_form_min,
/*
      XmNpaneMaximum,                 top_frame_form_max,
*/

/*
      XmNwidth,                       522, - now in XBMotif
*/
      XmNheight,                      300,
      XmNmarginHeight,                10,
      NULL );

  /***
  bottom_frame_form in toolkit pane
  ***/
  bottom_frame_form = XtVaCreateWidget ( "MainWin", 
      xmFormWidgetClass,              main_form_pane,
      XmNpaneMinimum,                 bottom_frame_form_min,
      NULL );

  /***
  B_button in constructs form
  ***/
  B_button = XtVaCreateWidget ( "InformationPanel",
      xmPushButtonWidgetClass,        top_frame_form,
      XmNlabelType,                   XmPIXMAP,
      XmNlabelPixmap,                 B_framed_pixmap_gray94,
      XmNshadowThickness,             0,
      XmNmarginWidth,                 0,
      XmNmarginHeight,                0,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   /* 8, */ /* 3, */ /* ihs */ 0,/* */
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 /*  5,*/ 2,
      XmNtraversalOn,                 False,
      NULL );

  XtAddCallback ( B_button, XmNactivateCallback,
                                    ( XtCallbackProc ) B_info_CB, NULL );


  /***
  Environment Labels
  ***/
  for ( i = 0 ; i < EnvString_tot ; i++ ) {

    xstr = XmStringCreateLtoR ( EnvString [ i ], charset );
    env_lab [ i ] = XtVaCreateManagedWidget ( "EnvLabelPassive",
        xmPushButtonWidgetClass,        top_frame_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   /* 15, */ /* 9 ,*/ /* ihs */ 0,
        XmNlabelString,                 xstr,
        XmNshadowThickness,             0,
        XmNmarginWidth,                 /* 2,*/ 0,
        XmNmarginHeight,                /* 2,*/ 0,
        XmNnavigationType,              XmTAB_GROUP,
        XmNhighlightThickness,          /* 1,*/ 0,
        /* */
        XmNrecomputeSize,        False,
        XmNheight,               30,
        XmNbackgroundPixmap,            tabgrey_pixmap,
        NULL );
    XmStringFree ( xstr );

    XtAddCallback ( env_lab [ i ], XmNactivateCallback,
          ( XtCallbackProc ) env_lab_CB,
          ( XtPointer ) & c_arr [ i ] );

    if ( ! i ) {
      XtVaSetValues ( env_lab [ i ],
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  /* 65, */ /* 48, */ 2,
        NULL );
    }
    else {
      XtVaSetValues ( env_lab [ i ],
        XmNleftAttachment,              XmATTACH_WIDGET,
        XmNleftWidget,                  env_lab [ i - 1 ],
        XmNleftOffset,                  /* 8, */ /* 6, */ 0,
        NULL );
    }

    /* */
    if ( i==EnvString_tot-1)
    {
	XtVaSetValues ( env_lab [ i ],
                XmNwidth,                84,
        NULL );
    }
    else
    {
       XtVaSetValues ( env_lab [ i ],
                XmNwidth,                82,
        NULL );
    }


  } /* for ... */

  /***
  create unmanaged Animator/InterProver labels
  ***/

  xstr = XmStringCreateLtoR ( EnvString [ env_str_anm_num ], charset );
  env_lab [ env_str_anm_num ] = XtVaCreateWidget ( "EnvLabelActive",
      xmLabelWidgetClass,             top_frame_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   /* 15, */ 9, /* ihs */
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNlabelString,                 xstr,
      XmNshadowThickness,             0,
      XmNmarginWidth,                 2,
      XmNmarginHeight,                2,
      XmNtraversalOn,                 False,
      XmNhighlightThickness,          1,
      NULL );
   XmStringFree ( xstr );


  xstr = XmStringCreateLtoR ( EnvString [ env_str_ipr_num ], charset );
  env_lab [ env_str_ipr_num ] = XtVaCreateWidget ( "EnvLabelActive",
      xmLabelWidgetClass,             top_frame_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   /* 15, */ 9, /* ihs */
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNlabelString,                 xstr,
      XmNshadowThickness,             0,
      XmNmarginWidth,                 2,
      XmNmarginHeight,                2,
      XmNtraversalOn,                 False,
      XmNhighlightThickness,          1,
      NULL );
   XmStringFree ( xstr );

  xstr = XmStringCreateLtoR ( EnvString [ env_str_btl_num ], charset );
  env_lab [ env_str_btl_num ] = XtVaCreateWidget ( "EnvLabelActive",
      xmLabelWidgetClass,             top_frame_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   /* 15, */ 9, /* ihs */
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNlabelString,                 xstr,
      XmNshadowThickness,             0,
      XmNmarginWidth,                 2,
      XmNmarginHeight,                2,
      XmNtraversalOn,                 False,
      XmNhighlightThickness,          1,
      NULL );
   XmStringFree ( xstr );


  /***
  constructs_frame in constructs_form
  ***/
  constructs_frame = XtVaCreateWidget ( "Frame", 
      xmFrameWidgetClass,             top_frame_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   /* 50, */ /* 36, */ /* ihs */ 30, /* */
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  /* 5,*/ leftrightOffset,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 /* 5,*/ leftrightOffset,
      XmNbottomAttachment,            XmATTACH_FORM, /*XmATTACH_WIDGET,
      XmNbottomWidget,                information_label,*/
      /*XmNbottomOffset,*/                /* 5,*/ /*(scrollOffset+scrollOffset+20),*/
      XmNshadowType,                  XmSHADOW_ETCHED_IN,
      
      XmNshadowThickness,             0,
      XmNmarginHeight,                /*1,*/ 0,
      
      XmNmarginWidth,                 0,
      XmNhighlightThickness,          0,
      XmNborderWidth,                 0,
      NULL );

  /***
  constructs_form in construct_frame
  ***/
  constructs_form = XtVaCreateWidget ( "ConstructsArea", 
      xmFormWidgetClass,              constructs_frame,
      /* DOH! can't attach to child widget that is also the parent form!
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   constructs_frame,
      */
      XmNtopOffset,                   0,
      /*
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                constructs_frame,
      */
      XmNbottomOffset,                0,
      /*
      XmNleftAttachment,              XmATTACH_WIDGET,
      XmNleftWidget,                  constructs_frame,
      */
      XmNleftOffset,                  0,
      /*
      XmNrightAttachment,             XmATTACH_WIDGET,
      XmNrightWidget,                 constructs_frame,
      */
      XmNrightOffset,                 0,
      XmNshadowThickness,             0,
      XmNborderWidth,                 0,
      NULL );


  /***
  command_bar_rc in constructs_form
  ***/
  command_bar_rc = XtVaCreateWidget ( "CommandBar", 
      xmRowColumnWidgetClass,         constructs_form,
      /*
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   constructs_form,
      */
      XmNtopOffset,                   3,
      /*
      XmNleftAttachment,              XmATTACH_WIDGET,
      XmNleftWidget,                  constructs_form,
      */
      XmNleftOffset,                  /* 24, */ /* 26,*/ commandOffset,
      /*
      XmNrightAttachment,             XmATTACH_WIDGET,
      XmNrightWidget,                 constructs_form,
      */
      XmNrightOffset,                 0,
      XmNshadowThickness,             0,
      XmNborderWidth,                 0,
      XmNspacing,                     0,
      XmNorientation,                 XmHORIZONTAL,
      NULL);

  /***
  environment buttons label in constructs_form
  ***/
  Cre_Env_Buttons_Label ();


  /***
  control scroll in control form
  ***/
  constructs_scroll = XtVaCreateWidget ( "Canvas",
      xmScrolledWindowWidgetClass,    constructs_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   /* 35, */ 30,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                /* 15, */ scrollOffset,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  /* 15,*/ scrollOffset,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 /* 15,*/ scrollOffset,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNshadowThickness,             /* 3,*/ 1,
      NULL );

  /***
  constructs_rc rowcol in control scroll
  ***/
  constructs_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         constructs_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 /* 18, */ 0,
      XmNmarginHeight,                10,
      XmNspacing,                     0,
      NULL );

  /***
   *_row_scroll constructs_form
  ***/
  main_row_scroll = XtVaCreateWidget ( "Canvas",
      xmScrolledWindowWidgetClass,    constructs_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   35,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                /* 15,*/ scrollOffset,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  /* 15,*/ scrollOffset,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 /* 15,*/ scrollOffset,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNshadowThickness,             /* 3,*/ 1,
      NULL );
  provers_row_scroll = XtVaCreateWidget ( "Canvas",
      xmScrolledWindowWidgetClass,    constructs_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   35,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                /* 15,*/ scrollOffset,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  /* 15,*/ scrollOffset,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 /* 15,*/ scrollOffset,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNshadowThickness,             /* 3,*/ 1,
      NULL );
  generators_row_scroll = XtVaCreateWidget ( "Canvas",
      xmScrolledWindowWidgetClass,    constructs_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   35,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                /* 15,*/ scrollOffset,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  /* 15,*/ scrollOffset,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 /* 15,*/ scrollOffset,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNshadowThickness,             /* 3,*/ 1,
      NULL );
  translators_row_scroll = XtVaCreateWidget ( "Canvas",
      xmScrolledWindowWidgetClass,    constructs_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   35,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                /* 15,*/ scrollOffset,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  /* 15,*/ scrollOffset,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 /* 15,*/ scrollOffset,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNshadowThickness,             /* 3,*/ 1,
      NULL );
  documents_row_scroll = XtVaCreateWidget ( "Canvas",
      xmScrolledWindowWidgetClass,    constructs_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   35,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                /* 15,*/ scrollOffset,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  /* 15,*/ scrollOffset,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 /* 15,*/ scrollOffset,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNshadowThickness,             /* 3,*/ 1,
      NULL );


  /***
  *_row_form in *_row_scroll
  ***/
  main_row_form = XtVaCreateManagedWidget ( "Canvas", 
      xmFormWidgetClass,              main_row_scroll,
      NULL );
  provers_row_form = XtVaCreateManagedWidget ( "Canvas", 
      xmFormWidgetClass,              provers_row_scroll,
      NULL );
  generators_row_form = XtVaCreateManagedWidget ( "Canvas", 
      xmFormWidgetClass,              generators_row_scroll,
      NULL );
  translators_row_form = XtVaCreateManagedWidget ( "Canvas", 
      xmFormWidgetClass,              translators_row_scroll,
      NULL );
  documents_row_form = XtVaCreateManagedWidget ( "Canvas", 
      xmFormWidgetClass,              documents_row_scroll,
      NULL );

  /***
  Create the information label
  ***/

  xstr = XmStringCreateLtoR ( " \n \n ", charset );
  information_label = XtVaCreateWidget ( "InformationLabel",
      xmLabelWidgetClass,             bottom_frame_form,
      XmNlabelString,                 xstr,
      XmNheight,                      30,
      /*XmNtopAttachment,               XmATTACH_NONE,*/
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  leftrightOffset,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 leftrightOffset+1,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   scrollOffset,
      XmNshadowThickness,             0,
      XmNmarginWidth,                 /*1,*/ 0,
      XmNmarginHeight,                /*1,*/ 0,
      XmNtraversalOn,                 False,
      XmNhighlightThickness,          0,
      XmNborderWidth,                 /*1,*/ 0,
      XmNbackground,           WhitePixelOfScreen ( XtScreen ( top_level ) ),
      NULL );
   XmStringFree ( xstr );

  /***
  display frame in display form
  ***/
  bot_display_frame = XtVaCreateWidget ( "DisplayArea", 
      xmFrameWidgetClass,             bottom_frame_form,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   information_label,
      XmNtopOffset,                   /* 5,*/ scrollOffset,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  /* 5, */ leftrightOffset,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 /* 5, */ leftrightOffset,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                /* 5,*/ scrollOffset,
      XmNshadowType,                  XmSHADOW_ETCHED_IN,
      /* 
      XmNmarginWidth,                 10,
      XmNmarginHeight,                10, */
      NULL );

  /***
  main text in bot_display_frame
  ***/
  {
    Arg args [ 15 ];
    int n = 0;

    XtSetArg ( args [ n ], XmNrows,                  45                ); n++;
    XtSetArg ( args [ n ], XmNcolumns,               60                ); n++;
    XtSetArg ( args [ n ], XmNeditable,              False             ); n++;
    XtSetArg ( args [ n ], XmNeditMode,              XmMULTI_LINE_EDIT ); n++;
    XtSetArg ( args [ n ], XmNcursorPositionVisible, False             ); n++;
    XtSetArg ( args [ n ], XmNscrollHorizontal,      False             ); n++;
    XtSetArg ( args [ n ], XmNwordWrap,              True              ); n++;
    XtSetArg ( args [ n ], XmNmarginWidth,           5                 ); n++;
    XtSetArg ( args [ n ], XmNmarginHeight,          5                 ); n++;
    XtSetArg ( args [ n ], XmNshadowThickness,       1                 ); n++;
/*
    XtSetArg ( args [ n ], XmNtraversalOn,           False             ); n++;
*/

    main_text =
             XmCreateScrolledText ( bot_display_frame, "Canvas", args, n );
  }

  XtVaSetValues ( XtParent ( main_text ),
      XmNshadowThickness,       3,
      NULL );

  /***
  set text window
  ***/
  curr_text = main_text;
  main_text_posn = ( XmTextPosition ) 0;
  curr_text_posn =  main_text_posn;

  /***
  manage children
  ***/
  XtManageChild ( main_form_pane );
  XtManageChild ( constructs_frame );
  XtManageChild ( information_label );
  XtManageChild ( constructs_form );
  XtManageChild ( command_bar_rc );
  /*  XtManageChild ( constructs_rc ); */
  /*  XtManageChild ( constructs_scroll ); */
  XtManageChild ( B_button );
  XtManageChild ( top_bar );
  XtManageChild ( main_text );
  XtManageChild ( bot_display_frame );
  XtManageChild ( top_frame_form );
  XtManageChild ( bottom_frame_form );
  

  /***
  display version, copyright etc
  ***/
  #ifdef MAC_VERSION
  notice[0]='\0';
  strcat(notice,"/usr/bin/osascript -e \'tell app \"System Events\"\ndisplay dialog \"");
  strcat(notice,toolkit_name);
  strcat(notice, "\n" );
  strcat(notice, toolkit_ver_with_sp );
  strcat(notice, "\n" );
  strcat(notice, toolkit_copyright_year );
  strcat(notice, "\n" );
  strcat(notice, toolkit_company );
  
  strcat(notice,"\" with title \"");
  strcat(notice,toolkit_name);
  strcat(notice,"\" with icon note buttons {\"Ok\"} giving up after 10\nend tell\' > /dev/null &");
  system(notice);
  #else
  DisplayCurrWinText ( "\n" );
  DisplayCurrWinText ( toolkit_name );
  DisplayCurrWinText ( "\n\n" );
  DisplayCurrWinText ( toolkit_ver_with_sp );
  DisplayCurrWinText ( "\n\n" );
  DisplayCurrWinText ( toolkit_copyright );
  DisplayCurrWinText ( "\n\n" );
  #endif
}



/***********************************************************************
************************************************************************
                         Error & Error dialogs
************************************************************************
***********************************************************************/

/*
XtTimerCallbackProc
Dismiss_Info_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  Widget dialog = XtParent ( XtParent ( widget ) );

  XtRemoveTimeOut ( Popup_Info_id );
  XtPopdown ( dialog );
  XmUpdateDisplay ( dialog );
  XtDestroyWidget ( dialog );
}
*/

XtIntervalId Popup_Info_id;

void
Popup_Info_CB ( client_data, id )
XtPointer client_data;
XtIntervalId * id;
{
  static int first_time = 1;
  Widget * dialog = ( Widget * ) client_data;
/***
printf ( "Popup_Info_CB: * dialog = %d\n", * dialog );
***/
  if ( first_time ) {
    Position dialog_x, dialog_y;
    first_time = 0;
    XtVaGetValues ( * dialog, 
        XmNx,    & dialog_x,
        XmNy,    & dialog_y,
       NULL );
    /***
    wm_width & wm_height set in CentreWidgetRelMainWin_CB
    ***/
    wm_width = dialog_x - wm_width;
    wm_height = dialog_y - wm_height;
/***
printf ( "1 wm_width=%d wm_height=%d\n", wm_width, wm_height );
***/
    if ( ( wm_width < 2 ) || ( wm_width > 8 ) ) wm_width = 5;
    if ( ( wm_height < 2 ) || ( wm_height > 27 ) ) wm_height = 14;
  }

/***
printf ( "2 wm_width=%d wm_height=%d\n", wm_width, wm_height );
***/

  XtPopdown ( * dialog );
  XtDestroyWidget ( * dialog );
}

void
Popup_Info_WM_CB ( d_ialog, client_data, call_data )
Widget d_ialog;
XtPointer client_data;
XtPointer call_data;
{
  static int first_time = 1;
  Widget * dialog = ( Widget * ) client_data;
  XtRemoveTimeOut ( Popup_Info_id );
/***
printf ( "Popup_Info_WM_CB: d_ialog = %d * dialog = %d\n", d_ialog, * dialog );
***/
  if ( first_time ) {
    Position dialog_x, dialog_y;
    first_time = 0;
    XtVaGetValues ( * dialog, 
        XmNx,    & dialog_x,
        XmNy,    & dialog_y,
       NULL );
    /***
    wm_width & wm_height set in CentreWidgetRelMainWin_CB
    ***/
    wm_width = dialog_x - wm_width;
    wm_height = dialog_y - wm_height;
/***
printf ( "1 wm_width=%d wm_height=%d\n", wm_width, wm_height );
***/
    if ( ( wm_width < 2 ) || ( wm_width > 8 ) ) wm_width = 5;
    if ( ( wm_height < 2 ) || ( wm_height > 27 ) ) wm_height = 14;
  }

/***
printf ( "2 wm_width=%d wm_height=%d\n", wm_width, wm_height );
***/

  XtPopdown ( * dialog );
  XtDestroyWidget ( * dialog );
}

/* - timer call back for information_label */

void
Popup_Info_Label_CB ( client_data, id )
XtPointer client_data;
XtIntervalId * id;
{
  XmString xstr;
  char info_buf [ 1 ];
  Widget *label = ( Widget * ) client_data;
  
  info_buf[0]='\0';

  xstr = XmStringCreateLtoR ( info_buf, charset );
  XtVaSetValues( * label,
                 XmNlabelString,            xstr,
		 NULL );
  
  XmStringFree ( xstr );
  XmUpdateDisplay ( * label );
}


  /* updating the information_label */

  /* wrapping text */
  
char* wrap(char* toWrap, int width)
{
	int length;
	int maxsize;
	char* wrapped;
	int pos;
	int start;
	int destPos;
	
	length=strlen(toWrap);
	maxsize=(length/width)+length+1;
	
	wrapped=(char *) malloc((size_t) maxsize);
	wrapped[0]='\0';
	
	pos=0;
	start=0;
	destPos=0;
	
	for(;;)
	{
		pos=start+width;
		if(pos>=length)
		{
			while(toWrap[start]==' ' && start<length){start++;}
			memcpy((char*) (wrapped+destPos),(char*) (toWrap+start), (size_t) (length-start));
			destPos+=(length-start);
			break;
		}
		
		while(pos>start && toWrap[pos]!=' '){pos--;}
		
		if(pos-start == 0)
		{
			while(toWrap[start]==' ' && start<length){start++;}
			memcpy((char*) (wrapped+destPos),(char*) (toWrap+start), (size_t) width);
			destPos+=width;
			start+=width;
			wrapped[destPos++]='\n';
			continue;
		}
		else
		{
			while(toWrap[start]==' ' && start<length){start++;}
			memcpy((char*) (wrapped+destPos),(char*) (toWrap+start), (size_t) (pos-start));
			destPos+=(pos-start);
			start+=(pos-start);
			wrapped[destPos++]='\n';
			continue;
		}
	}
	
	wrapped[destPos]='\0';
	
	return wrapped;
}

  /* "popping up" the label */
void
Popup_Info ( text )
char * text;
{
  XmString xstr;
  char* info_buf;
  unsigned long timeout;
  int height;
  
  if ( ! up_and_running ) return;

  info_buf=wrap(text, 60);
  
  if(strstr(info_buf,"/")!=NULL)
  {
  	timeout=10000L;
	height=60;
  }
  else
  if(strlen(info_buf)<30){timeout=3000L;height=30;}
  else
  if(strlen(info_buf)<60){timeout=4000L;height=40;}
  else
  if(strlen(info_buf)<90){timeout=5000L;height=50;}
  else
  {
  	timeout=6000L;
	height=60;
  }

  xstr = XmStringCreateLtoR ( info_buf, charset );
  XtVaSetValues( information_label,
                 XmNlabelString,            xstr,
		 XmNheight,                 height,
		 NULL );
  
  XmStringFree ( xstr );
  
  XmUpdateDisplay ( information_label );

    XtAppAddTimeOut ( app, timeout,
        ( XtTimerCallbackProc ) Popup_Info_Label_CB,
        ( XtPointer ) information_label );
	
  free(info_buf);
}

void
Popup_Info_OLD ( text )
char * text;
{
  Widget dialog, dialog_form, B_logo, Label;
  XmString xstr;
  char info_buf [ 250 ];
  static struct coord coord_data;
  static Atom   WM_DELETE_WINDOW;
  static int first_time = 1;


  if ( ! up_and_running ) return;

  WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

  dialog = XmCreateDialogShell ( top_frame_form, "InfoDialog", NULL, 0 );

  coord_data.x = 0; /* not used */
  coord_data.y = -10;

  XtAddCallback ( dialog, XmNpopupCallback,
      ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
      ( XtPointer ) & coord_data );

  XmAddWMProtocolCallback ( dialog, WM_DELETE_WINDOW,
      ( XtCallbackProc ) Popup_Info_WM_CB,
      ( XtPointer ) dialog );

   dialog_form = XtVaCreateWidget ( "InfoDialog",
      xmFormWidgetClass,         dialog,
      XmNdialogStyle,            XmDIALOG_MODELESS,
      XmNdefaultPosition,        False,  
      XmNtraversalOn,            True,
      XmNdefaultButtonType,      XmNONE,
      XmNautoUnmanage,           False,
      NULL );

   B_logo =  XtVaCreateManagedWidget ( "WarningDialog",
      xmPushButtonWidgetClass,    dialog_form,
      XmNlabelType,               XmPIXMAP,
      XmNlabelPixmap,             B_framed_pixmap_gray94,
      XmNshadowThickness,         0,
      XmNmarginWidth,             0,
      XmNmarginHeight,            0,
      XmNtopAttachment,           XmATTACH_FORM,
      XmNtopOffset,               10,
      XmNleftAttachment,          XmATTACH_FORM,
      XmNleftOffset,              10,
      XmNtraversalOn,             False,
      NULL );

  XtAddCallback ( B_logo, XmNactivateCallback,
                                    ( XtCallbackProc ) B_info_CB, NULL );

  strcpy ( info_buf, text );
  xstr = XmStringCreateLtoR ( info_buf, charset );
  Label = XtVaCreateManagedWidget ( "WarningDialog", 
      xmLabelWidgetClass,        dialog_form,
      XmNlabelString,            xstr,
      XmNtopAttachment,          XmATTACH_FORM,
      XmNtopOffset,              10,
      XmNleftAttachment,         XmATTACH_WIDGET,
      XmNleftWidget,             B_logo,
      XmNleftOffset,             25,
      XmNrightAttachment,        XmATTACH_FORM,
      XmNrightOffset,            50,
      XmNbottomAttachment,       XmATTACH_FORM,
      XmNbottomOffset,           10,
      XmNmarginWidth,            10,
      XmNmarginHeight,           10,
      NULL );
  XmStringFree ( xstr );

  XtManageChild ( dialog_form );
  XmUpdateDisplay ( dialog_form );
  
  if ( first_time ) {
    first_time = 0;

  }

    Popup_Info_id = XtAppAddTimeOut ( app, ( long unsigned ) 2500L,
        ( XtTimerCallbackProc ) Popup_Info_CB,
        ( XtPointer ) dialog );


  XtPopup ( dialog, XtGrabNone );
  
  
/*
  XmUpdateDisplay ( Label );
  XmUpdateDisplay ( dialog_form );
  XmUpdateDisplay ( dialog );
*/
}


void
Popup_Err_CB ( err )
Widget err;
{
  Sensitize ();
  if ( errorbox_flag == BT_RECT_FAULT_M ) { /*** PFZ ***/
    if ( xterm_is_up ) {
      xterm_is_up = 0;
      DisplayXTermText ();
      KillXTerm ();
    }
    Save_n_CfgDepBase ();
    AbortedMsg ();
    
    unlink ( pid_id_file );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_NOOP );
    Write_FIFO ( fifo_write_buf );
    exit ( 1 );
  }
  else if ( errorbox_flag == 999999 ) {
    if ( xterm_is_up ) {
      xterm_is_up = 0;
      DisplayXTermText ();
      KillXTerm ();
    }
    Save_n_CfgDepBase ();
    AbortedMsg ();
    
    unlink ( pid_id_file );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_NOOP );
    Write_FIFO ( fifo_write_buf );
    exit ( 1 );
  }
  else if ( errorbox_flag == 999998 ) { /*** Can't read resource file ***/
    Save_n_CfgDepBase ();
    AbortedMsg ();
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
    InvokeB( without_XTerm, 1 );
  }
  else if ( errorbox_flag == BT_ERR_M ) { /*** Error_From_B ***/
    XtPopdown ( XtParent ( err ) );
    XmUpdateDisplay ( XtParent ( err ) );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_NOOP );
    InvokeB ( without_XTerm, 1 );
  }
  else if ( errorbox_flag == BT_MINOR_ERR_M ) { /*** Error_From_B ***/
    XtPopdown ( XtParent ( err ) );             /*** don't process XTerm ***/
    XmUpdateDisplay ( XtParent ( err ) );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
    InvokeB ( without_XTerm, 1 );
  }
  else {
    XtPopdown ( XtParent ( err ) );
    XmUpdateDisplay ( XtParent ( err ) );
  }
}

void
Popup_Err ( err_flag, text )
int  err_flag;
char * text;
{
  Widget err;
  XmString xstr;

  static struct coord coord_data;

  if ( ! up_and_running ) return;

  coord_data.x = 0; /* not used */
  coord_data.y = -15;

  err = XmCreateErrorDialog ( top_frame_form, "WarningDialog", NULL, 0 );
  xstr = XmStringCreateLtoR ( text, charset );
  XtVaSetValues ( err,
      XmNmessageString,          xstr,
      XmNsymbolPixmap,           B_framed_pixmap_gray94,
      XmNmarginWidth,            10,
      XmNmarginHeight,           5,
      XmNdialogStyle,            XmDIALOG_MODELESS,
      XmNdefaultButtonType,      XmNONE,
      NULL );
  XmStringFree ( xstr );

  XtAddCallback ( XtParent ( err ), XmNpopupCallback,
      ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
      ( XtPointer ) & coord_data );

  XtUnmanageChild ( XmMessageBoxGetChild ( err, XmDIALOG_CANCEL_BUTTON ) );
  XtUnmanageChild ( XmMessageBoxGetChild ( err, XmDIALOG_HELP_BUTTON ) );
  XtVaSetValues ( XmMessageBoxGetChild ( err, XmDIALOG_OK_BUTTON ),
      XmNdefaultButtonShadowThickness,  1,
      XmNnavigationType,       XmTAB_GROUP,
      XmNhighlightThickness,   1,
      NULL );

  XtAddCallback ( err, XmNokCallback, ( XtCallbackProc ) Popup_Err_CB, NULL );

  errorbox_flag = err_flag;

  if ( xterm_is_up                      &&
       errorbox_flag != BT_RECT_FAULT_M &&
       errorbox_flag != BT_MINOR_ERR_M  &&
       errorbox_flag != 999999             ) {
    process_XTerm_IfReq ();
  }

  if ( ( errorbox_flag == BT_MINOR_ERR_M )                     &&
       ( strcmp ( text, "Problem with Toolkit binary" ) == 0 )    ) {
    sprintf ( buf, "\n  %s\n", text );
    DisplayCurrWinText ( buf );
    if ( auto_reset_and_remake && ( ! upgrade3T04_flag ) ) {
      Save_n_CfgDepBase ();
      AutoRemakeFini ();
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
      InvokeB ( without_XTerm, 1 );
    }
  }

  if ( bell_option ) XBell ( display, 10 );

  XmProcessTraversal ( XmMessageBoxGetChild ( err, XmDIALOG_OK_BUTTON ),
                                                             XmTRAVERSE_CURRENT );
  DeSensitize ();

  XtManageChild ( err );
  XtPopup ( XtParent ( err ), XtGrabNone ); 
  XmUpdateDisplay ( XtParent ( err ) );

}

void
Popup_Minor_Err_CB ( err )
Widget err;
{
  if ( ( curr_env !=  ipr_pob_env ) &&
       ( curr_env !=  anm_env )     &&
       ( curr_env !=  ipr_lem_env )    ) {
   DisplayCurrentEnv ();
  }
  XtPopdown ( XtParent ( err ) );
  XmUpdateDisplay ( XtParent ( err ) );
}

void
Popup_Minor_Err ( parent, text )
Widget parent;
char * text;
{
  #ifdef MAC_VERSION
  
  char notice[2048];
  
  notice[0]='\0';
  strcat(notice,"/usr/bin/osascript -e \'tell app \"System Events\"\ndisplay dialog \"");
  strcat(notice,text);
  strcat(notice,"\" with title \"");
  strcat(notice,toolkit_name);
  strcat(notice,"\" buttons {\"Dismiss\"} giving up after 10\nend tell\' > /dev/null &");
  
  printf("%s\n",notice);
  
  system(notice);
  
  /* from  Popup_Minor_Err_CB */
  
  if ( ( curr_env !=  ipr_pob_env ) &&
       ( curr_env !=  anm_env )     &&
       ( curr_env !=  ipr_lem_env )    ) {
   DisplayCurrentEnv ();
  }
  
  #else
  Widget err;
  XmString xstr;

  static struct coord coord_data;

    if ( ! up_and_running ) return;

    coord_data.x = 0; /* not used */
    coord_data.y = -15;

    if ( parent )
      err = XmCreateErrorDialog ( top_frame_form, "WarningDialog", NULL, 0 );
    else
      err = XmCreateErrorDialog ( top_frame_form, "WarningDialog", NULL, 0 );
    XtVaSetValues ( err,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultButtonType,      XmNONE,
        NULL );
    XtUnmanageChild ( XmMessageBoxGetChild ( err, XmDIALOG_CANCEL_BUTTON ) );
    XtUnmanageChild ( XmMessageBoxGetChild ( err, XmDIALOG_HELP_BUTTON ) );
    XtVaSetValues ( XmMessageBoxGetChild ( err, XmDIALOG_OK_BUTTON ),
        XmNdefaultButtonShadowThickness,  1,
        XmNnavigationType,       XmTAB_GROUP,
        XmNhighlightThickness,   1,
        NULL );
    XtAddCallback ( err, XmNokCallback,
                                 ( XtCallbackProc ) Popup_Minor_Err_CB, NULL );

    XtAddCallback ( XtParent ( err ), XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );

    XtVaSetValues ( err,
        XmNsymbolPixmap,           B_framed_pixmap_gray94,
        NULL );
/* WHY?????????
    XtManageChild ( err );
    XtUnmanageChild ( err );
*/
    xstr = XmStringCreateLtoR ( ( char * ) text, charset );
    XtVaSetValues ( err,
        XmNmessageString,          xstr,
        NULL );
    XmStringFree ( xstr );

  XmProcessTraversal ( XmMessageBoxGetChild ( err, XmDIALOG_OK_BUTTON ),
                                                             XmTRAVERSE_CURRENT );
  if ( bell_option ) XBell ( display, 10 );
  XtManageChild ( err );

  /*  DeSensitize (); */

  XtPopup ( XtParent ( err ), XtGrabNone ); 
  XmUpdateDisplay ( XtParent ( err ) );
  #endif
}

void
Popup_Capacity_Err_CB ( err, client_data )
Widget err;
XtPointer client_data;
{
  int err_num = * ( int * ) client_data;
  XtPopdown ( XtParent ( err ) );
  XmUpdateDisplay ( XtParent ( err ) );
  Save_n_CfgDepBase ();
  AbortedMsg ();
  
  unlink ( pid_id_file );
  strcpy ( fifo_write_buf, "0:" );
  Cre_fifo_write_buf_cmd_0 ( BT_NOOP );
  Write_FIFO ( fifo_write_buf );
  exit ( 1 );
}

void
Popup_Capacity_Err ( err_flag, text, err_num )
int  err_flag;
char * text;
int err_num;
{
  static Widget err = ( Widget ) 0;
  Dimension top_level_w, err_w;

  if ( ! err ) {
    err = XmCreateErrorDialog ( top_level, "WarningDialog", NULL, 0 );
    XtVaSetValues ( err,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultButtonType,      XmNONE,
        NULL );
    XtUnmanageChild ( XmMessageBoxGetChild ( err, XmDIALOG_CANCEL_BUTTON ) );
    XtUnmanageChild ( XmMessageBoxGetChild ( err, XmDIALOG_HELP_BUTTON ) );
    XtAddCallback ( err, XmNokCallback,
                             ( XtCallbackProc ) Popup_Capacity_Err_CB,
                             ( XtPointer ) & c_arr [ err_num ] );
    XtManageChild ( err );
    XtUnmanageChild ( err );
  }

  /***
  static dialog exists - set message
  ***/
  {
    XmString xstr = XmStringCreateLtoR ( ( char * ) text, charset );
    XtVaSetValues ( err,
        XmNmessageString,          xstr,
        NULL );
    XmStringFree ( xstr );
  }

  errorbox_flag = err_flag;

  DeSensitize ();
  XtVaGetValues ( top_level, 
      XmNwidth,         &top_level_w,
      NULL );
  XtVaGetValues ( err, 
      XmNwidth,         &err_w,
      NULL );
  XtManageChild ( err );
  if ( bell_option ) XBell ( display, 10 );

  XtPopup ( XtParent ( err ) , XtGrabNone );
  XmUpdateDisplay ( XtParent ( err ) );
  XmUpdateDisplay ( err );
}

void
Error_From_B ()
{
  Popup_Err ( BT_ERR_M, primary_string );
}


/***********************************************************************
************************************************************************
                           Quit Editor Dialogs
************************************************************************
***********************************************************************/
void
QuitEditor_Popup_CB ( q_d, client_data )
Widget q_d;
XtPointer client_data;
{

  XtPopdown ( XtParent ( q_d ) );
  XmUpdateDisplay ( XtParent ( q_d ) );
  if ( * ( int * ) client_data == OK_BUTTON ) {
    Load_SRC_CFG_Names ( curr_obj );
    unlink( SRCName );
    /* MUST do this *after* the unlinking */
    KillProcess_Modify_ps ( curr_obj );
    DisplayCurrentEnv ();
  }
}

void
Check_QuitEditor_Popup ( obj )
int obj;
{
  static Widget q_d = ( Widget ) 0;
  static  XmString xstr;

  int file_diff = FileDiffIntoBcom ( obj );

  static struct coord coord_data;
  coord_data.x = 0; /* not used */
  coord_data.y = 150;

  curr_obj = obj;
  if ( file_diff ) {       /*** files are different ***/
    strcpy ( primary_string, GetName ( obj ) );
    radiobox_flag = close_radiobox;
    Popup_CloseEditedFile ( top_level );
  }
  else {                  /*** files are identical ***/
    /***
    create dialog if it does not esist
    ***/
    if ( ! q_d ) {
      xstr = XmStringCreateLtoR ("Quit Editor requested, but no changes saved!\n\n`Cancel' if you want to save any changes ...", charset );
      q_d = XmCreateQuestionDialog ( top_level, "QuestionDialog", NULL, 0 );
      XtVaSetValues ( q_d,
          XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
          XmNautoUnmanage,           False,
          XmNdefaultButtonType,      XmNONE,
          XmNmessageString,          xstr,
          XmNsymbolPixmap,           B_framed_pixmap_gray94,
          XmNmarginWidth,            10,
          XmNmarginHeight,           5,
          NULL );
      XmStringFree ( xstr );
      XtAddCallback ( XtParent ( q_d ), XmNpopupCallback,
          ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
          ( XtPointer ) & coord_data );
      XtUnmanageChild ( XmMessageBoxGetChild ( q_d, XmDIALOG_HELP_BUTTON ) );
      XtAddCallback ( q_d, XmNokCallback,
          ( XtCallbackProc ) QuitEditor_Popup_CB, ( XtPointer ) & c_arr [ OK_BUTTON ] );
      XtAddCallback ( q_d, XmNcancelCallback,
          ( XtCallbackProc ) QuitEditor_Popup_CB, ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );

      XtVaSetValues ( XmMessageBoxGetChild ( q_d, XmDIALOG_OK_BUTTON ),
          XmNnavigationType,              XmTAB_GROUP,
          XmNdefaultButtonShadowThickness,   1,
          XmNhighlightThickness,          1,
          NULL );

      XtVaSetValues ( XmMessageBoxGetChild ( q_d, XmDIALOG_CANCEL_BUTTON ),
          XmNnavigationType,              XmTAB_GROUP,
          XmNdefaultButtonShadowThickness,   1,
          XmNhighlightThickness,          1,
          NULL );
    }

    /***
    position, manage & ring bell
    ***/
    XtManageChild ( q_d );
    XtPopup ( XtParent ( q_d ) , XtGrabNone ); 
    XmUpdateDisplay ( XtParent ( q_d ) );
    if ( bell_option ) XBell ( display, 10 );
  }

}

/************************************
         Popup Help callbacks
************************************/

XtCallbackProc
Popup_Help_CB ( parent, help_data )
Widget parent;
XtPointer help_data;
{
  #ifdef MAC_VERSION
  char notice[2048];
  #endif
  Widget help_dialog, help_form,
         help_scroll, help_text,
         sep,
         o_form, o_o;
   char* textPtr;
   
   int help_height_;
   int help_width_;
   int help_type_;

   textPtr=( ( struct help_struct * ) help_data ) -> text;
   
   
  #ifdef MAC_VERSION
  /* can't cope with quotes just yet */
  
  if(strstr(textPtr,"`")==NULL && strstr(textPtr,"\"")==NULL && strstr(textPtr,"\'")==NULL)
  {
	  notice[0]='\0';
	  strcat(notice,"/usr/bin/osascript -e \'tell app \"System Events\"\ndisplay dialog \"");
	  strcat(notice, textPtr );
	  strcat(notice,"\" with title \"");
	  strcat(notice,toolkit_name);
	  strcat(notice,"\" buttons {\"Dismiss\"} giving up after 10\nend tell\' > /dev/null &");

	  printf("%s\n",notice);

	  system(notice);
	  return;
   }
  #endif

  help_height_ = ( ( struct help_struct * ) help_data ) -> height;
  help_width_  = ( ( struct help_struct * ) help_data ) -> width;
  help_type_   = ( ( struct help_struct * ) help_data ) -> type;

  /***
  create the dialog
  ***/
  help_dialog = XtVaCreatePopupShell ( "HelpDialog",
      xmDialogShellWidgetClass,  top_frame_form,
      NULL );

  /***
  create Form - APPLICATION_MODAL
  ***/
  switch ( help_type_ ) {

    case PALETTE_HELP:
      help_form = XtVaCreateWidget ( "PalDialog",
          xmFormWidgetClass,         help_dialog,
          XmNdefaultPosition,        True, 
          XmNwidth,                  help_width_,
          XmNheight,                 help_height_,
          NULL );
      break;
    case MAIN_HELP:
    case DIFF_HELP:
      help_form = XtVaCreateWidget ( "PalDialog",
          xmFormWidgetClass,         help_dialog,
          XmNdefaultPosition,        True,
          XmNwidth,                  help_width_,
          XmNheight,                 help_height_,
          NULL );
      break;
    default:
      help_form = XtVaCreateWidget ( "HelpDialog",
          xmFormWidgetClass,         help_dialog,
          XmNdefaultPosition,        True,
          XmNwidth,                  help_width_,
          XmNheight,                 help_height_,
          NULL );
      break;
    }

  /***
  create separator
  ***/
  sep = XtVaCreateManagedWidget ( "HelpDialog", 
      xmSeparatorGadgetClass,  help_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         48,
      NULL );

  /***
  create 1 PushButton in Form
  ***/
  o_form = XtVaCreateManagedWidget ( "ButtonLabel",
      xmFormWidgetClass,       help_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNtopAttachment,        XmATTACH_WIDGET,
      XmNtopWidget,            sep,
      XmNtopOffset,            5,
      NULL );

  o_o = XtVaCreateManagedWidget ( "Dismiss", 
      xmPushButtonGadgetClass, o_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           15,
      XmNheight,               25,
      XmNwidth,                /* 57 */ 65,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      NULL );
  XtAddCallback ( o_o, XmNactivateCallback,
           ( XtCallbackProc ) Popup_Help_OK_CB, NULL );

  /***
  create ScrolledWindow
  ***/
  help_scroll = XtVaCreateWidget ( "HelpDialog",
      xmScrolledWindowWidgetClass,    help_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                sep,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNmarginWidth,                 0,
      XmNmarginHeight,                0,
      XmNtraversalOn,                 False,
      NULL );

  /***
  create Text
  ***/
  help_text = XtVaCreateManagedWidget ( "HelpDialog",
      xmTextWidgetClass,         help_scroll,
      XmNcursorPositionVisible,  False,
      XmNeditable,               False,
      XmNeditMode,               XmMULTI_LINE_EDIT,
      XmNmarginWidth,            10,
      XmNmarginHeight,           10,
      XmNborderWidth,            0,
      XmNshadowThickness,        0,
      XmNtraversalOn,            False,
      NULL );
  XmTextSetString ( help_text,
                          ( ( struct help_struct * ) help_data ) -> text );

  /***
  manage children
  ***/
  XtManageChild ( o_o );
  XtManageChild ( o_form );
  XtManageChild ( sep );
  XtManageChild ( help_text );
  XtManageChild ( help_scroll );
  XtManageChild ( help_form );

  /***
  popup dialog
  ***/
  XtPopup ( help_dialog, XtGrabNone );
  XmUpdateDisplay ( help_dialog );

  XmProcessTraversal ( o_o, XmTRAVERSE_CURRENT );
}

void
Popup_Help_OK_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  XtPopdown ( XtParent ( XtParent ( XtParent ( widget ) ) ) );
  XmUpdateDisplay ( XtParent ( XtParent ( XtParent ( widget ) ) ) );
}


/***********************************************************************
************************************************************************
                         RadioBox dialogs
************************************************************************
***********************************************************************/

/**************************************************
     Creation of basic RadioBox dialog
***************************************************/

void
Popup_RadioBox_Dialog_WM_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
  switch ( radiobox_flag ) {
  case close_pmd_file :
      Popup_ClosePMDFile ( top_level, 1 );
    break;
  case close_anm_thy_file :
      Popup_CloseAnimThyFile ( top_level, 1 );
    break;
  }
  Popup_Info ( "  Ouch!  " );
}

void
Cre_RadioBox_Dialog ( parent, dialog, dialog_form,
                      radio_box, radio_box_frame,
                      radio_box_top_offset, radio_box_left_offset,
                      radio_labels_tot,
                      B_logo,
                      sep, och_form, och_o, och_c, och_h,
                      ok_but_data, cancel_but_data,
                      help_data, label,
                      label_text,
                      WM_DELETE_WINDOW,
                      no_cancel_flag )

                      Widget * parent;
                      Widget * dialog;
                      Widget * dialog_form;
                      Widget * radio_box;
                      Widget * radio_box_frame;
                      int radio_box_top_offset;
                      int radio_box_left_offset;
                      int radio_labels_tot;
                      Widget * B_logo;
                      Widget * sep;
                      Widget * och_form;
                      Widget * och_o;
                      Widget * och_c;
                      Widget * och_h;
                      struct ok_cancel_but_struct * ok_but_data;
                      struct ok_cancel_but_struct * cancel_but_data;
                      struct help_struct * help_data;
                      Widget * label;
                      char * label_text;
                      Atom * WM_DELETE_WINDOW;
                      int no_cancel_flag;
{
  int i, act_tot;
  Widget but;
  XmString xstr [ MAX_RADIO_BUT ];
  Arg args [ 2 ];

  * WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

  /***
  create the dialog
  ***/
  XtSetArg ( args [ 0 ], XmNautoUnmanage, False );
  * dialog = XmCreateDialogShell ( top_frame_form, "SelDialog", args, 1 );

  /***
  create Control Area Form
  ***/
  * dialog_form = XtVaCreateWidget ( "SelDialog",
      xmFormWidgetClass,         * dialog,
      XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
      XmNtraversalOn,            True,
      XmNautoUnmanage,           False,
      XmNuserData,               ( XtPointer ) & c_arr [ 0 ],
      NULL );

  /***
  create B logo
  ***/
  * B_logo = XtVaCreateWidget ( "SelDialog", 
      xmPushButtonWidgetClass,    * dialog_form,
      XmNlabelType,               XmPIXMAP,
      XmNlabelPixmap,             B_framed_pixmap_gray94,
      XmNshadowThickness,         0,
      XmNmarginWidth,             0,
      XmNmarginHeight,            0,
      XmNtopAttachment,           XmATTACH_FORM,
      XmNtopOffset,               7,
      XmNleftAttachment,          XmATTACH_FORM,
      XmNleftOffset,              7,
      XmNtraversalOn,             False,
      NULL );

  XtAddCallback ( * B_logo, XmNactivateCallback,
                                    ( XtCallbackProc ) B_info_CB, NULL );

  /***
  create the label
  ***/
  xstr [ 0 ] = XmStringCreateLtoR ( label_text, charset );
  * label = XtVaCreateWidget ( "Label", 
      xmLabelWidgetClass,        * dialog_form,
      XmNtopAttachment,          XmATTACH_FORM,
      XmNtopOffset,              10,
      XmNleftAttachment,         XmATTACH_WIDGET,
      XmNleftWidget,             * B_logo,
      XmNleftOffset,             1,
      XmNrightAttachment,        XmATTACH_FORM,
      XmNrightOffset,            40,
      XmNlabelString,            xstr [ 0 ],
      XmNmarginWidth,            10,
      XmNmarginHeight,           5,
      XmNtraversalOn,            False,
      NULL );
  XmStringFree ( xstr [ 0 ] );

  /***
  create radio_box_frame in dialog_form
  ***/
  * radio_box_frame = XtVaCreateManagedWidget ( "SelDialog", 
      xmFrameWidgetClass,       * dialog_form,
      XmNshadowType,            XmSHADOW_ETCHED_IN,
      XmNtopAttachment,         XmATTACH_WIDGET,
      XmNtopWidget,             * dialog_form,
      XmNtopOffset,             radio_box_top_offset,
      XmNbottomAttachment,      XmATTACH_FORM,
      XmNbottomOffset,          /* 75, */ 85,
      XmNleftAttachment,        XmATTACH_FORM,
      XmNleftOffset,            radio_box_left_offset,
      XmNrightAttachment,       XmATTACH_FORM,
      XmNrightOffset,           radio_box_left_offset,
      XmNmarginWidth,           10,
      XmNmarginHeight,          10,
      XmNtraversalOn,           True,
      NULL );

  * radio_box = XmCreateRadioBox ( * radio_box_frame, "SelDialog", NULL, 0 );

  if ( radio_labels_tot == 993 ) /* NEW_Dialog_RadioBox_EditedFileExists_CB */
    act_tot = 3;
  else
    act_tot = radio_labels_tot;

  for ( i = 0 ; i < act_tot ; i++ ) {
    xstr [ i ] = XmStringCreateLocalized ( radio_labels [ i ] );
  }

  for ( i = 0 ; i <  act_tot ; i++ ) {
    but = XtVaCreateManagedWidget ( radio_labels [ i ],
        xmToggleButtonGadgetClass, * radio_box,
        XmNdefaultButtonShadowThickness, 1,
        XmNhighlightThickness,           1,
        XmNnavigationType,               XmTAB_GROUP,
       NULL );
    if ( radio_labels_tot == 993 ) {
      XtAddCallback ( but, XmNvalueChangedCallback,
         ( XtCallbackProc ) NEW_Dialog_RadioBox_EditedFileExists_CB,
          ( XtPointer ) & c_arr [ i ] );
    }
    else {
      XtAddCallback ( but, XmNvalueChangedCallback,
          ( XtCallbackProc ) NEW_Dialog_RadioBox_CB,
          ( XtPointer ) & c_arr [ i ] );
    }
    if ( ! i ) {
      XmToggleButtonGadgetSetState ( but, True, True );
    }
  }

  for ( i = 0 ; i < act_tot ; i++ ) {
    XmStringFree ( xstr [ i ] );
  }

  /***
  create separator
  ***/
  * sep = XtVaCreateManagedWidget ( "SelDialog",
      xmSeparatorGadgetClass,  * dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           0,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          0,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         48,
      NULL );

  /***
  create Action Area Form
  ***/
  * och_form = XtVaCreateWidget ( "ButtonLabel",
      xmFormWidgetClass,       * dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         5,
      NULL );

  /***
  create OK button
  ***/
  * och_o = XtVaCreateManagedWidget ( "OK", 
      xmPushButtonGadgetClass, * och_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           12,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  ok_but_data -> but           = OK_BUTTON;
  ok_but_data -> file_diff_but = 999;

  XmProcessTraversal ( * och_o, XmTRAVERSE_CURRENT );

  if ( radio_labels_tot == 993 ) {
    XtAddCallback ( * och_o, XmNactivateCallback,
        ( XtCallbackProc ) Popup_EditedFileExists_Dialog_CB,
        ( XtPointer ) ok_but_data );
  }
  else {
    XtAddCallback ( * och_o, XmNactivateCallback,
        ( XtCallbackProc ) Popup_RadioBox_Dialog_CB,
        ( XtPointer ) ok_but_data );
  }

  /***
  create Cancel button
  ***/
  * och_c = XtVaCreateManagedWidget ( "Cancel", 
      xmPushButtonGadgetClass, * och_form,
      XmNleftAttachment,       XmATTACH_WIDGET,
      XmNleftWidget,           * och_o,
      XmNleftOffset,           15,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  cancel_but_data -> but           = CANCEL_BUTTON;
  cancel_but_data -> file_diff_but = 999;
  if ( radio_labels_tot == 993 ) {
    XtAddCallback ( * och_c, XmNactivateCallback,
        ( XtCallbackProc ) Popup_EditedFileExists_Dialog_CB,
        ( XtPointer ) cancel_but_data );
    if ( no_cancel_flag ) {
      XmAddWMProtocolCallback ( * dialog, * WM_DELETE_WINDOW,
          ( XtCallbackProc ) Popup_RadioBox_Dialog_WM_CB,
          ( XtPointer ) * dialog_form );
    }
    else {
      XmAddWMProtocolCallback ( * dialog, * WM_DELETE_WINDOW,
          ( XtCallbackProc ) Popup_EditedFileExists_Dialog_CB,
          ( XtPointer ) * dialog_form );
    }
  }
  else
  {
    XtAddCallback ( * och_c, XmNactivateCallback,
        ( XtCallbackProc ) Popup_RadioBox_Dialog_CB,
        ( XtPointer ) cancel_but_data );
    if ( no_cancel_flag ) {
      XmAddWMProtocolCallback ( * dialog, * WM_DELETE_WINDOW,
          ( XtCallbackProc ) Popup_RadioBox_Dialog_WM_CB,
          ( XtPointer ) * dialog_form );
    }
    else {
      XmAddWMProtocolCallback ( * dialog, * WM_DELETE_WINDOW,
          ( XtCallbackProc ) Popup_RadioBox_Dialog_CB,
          ( XtPointer ) * dialog_form );
    }
  }
  
  /***
  create Help button
  ***/
  * och_h = XtVaCreateManagedWidget ( "Help", 
      xmPushButtonGadgetClass, * och_form,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          12,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( * och_h, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Help_CB,
      ( XtPointer ) help_data );

/*
print_XmNtraversalOn_value("* dialog_form",* dialog_form);
print_XmNtraversalOn_value("* radio_box_frame",* radio_box_frame);
print_XmNtraversalOn_value("* radio_box",* radio_box);
print_XmNtraversalOn_value("* sep",* sep);
*/


}

/* Simple menu selection for configuration dialog boxes.
*/

XtCallbackProc
Do_Nothing_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
}

XtCallbackProc
Editor_Chosen_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
	struct textWidgetXeditor* chosen;
	
	chosen = ( struct textWidgetXeditor * ) client_data;
	
	XmTextFieldSetString ( (Widget) (chosen->widget), chosen->editor ) ;
        XmTextFieldSetInsertionPosition ( (Widget) (chosen->widget), strlen (chosen->editor ) );
}

XtCallbackProc
Browser_Chosen_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
	struct textWidgetXbrowser* chosen;
	
	chosen = ( struct textWidgetXbrowser * ) client_data;
	
	XmTextFieldSetString ( (Widget) (chosen->widget), chosen->browser ) ;
        XmTextFieldSetInsertionPosition ( (Widget) (chosen->widget), strlen (chosen->browser ) );
}

/**************************************************
     Re-creation of basic RadioBox dialog
***************************************************/

void
Re_Cre_RadioBox_Dialog ( dialog_form, B_logo, label, title )

                         Widget * dialog_form;
                         Widget * B_logo;
                         Widget * label;
                         char * title;
{
  XmString xstr;

  /***
  destroy old label, create new one
  ***/
  XtDestroyWidget ( * label );
  strcpy ( additional_string, primary_string );
  strcat ( additional_string, "\n          \n" );
  strcat ( additional_string, title );
  xstr = XmStringCreateLtoR ( additional_string, charset );
  * label = XtVaCreateWidget ( "Label", 
      xmLabelWidgetClass,        * dialog_form,
      XmNtopAttachment,          XmATTACH_FORM,
      XmNtopOffset,              10,
      XmNleftAttachment,         XmATTACH_WIDGET,
      XmNleftWidget,             * B_logo,
      XmNleftOffset,             1,
      XmNrightAttachment,        XmATTACH_FORM,
      XmNrightOffset,            40,
      XmNlabelString,            xstr,
      XmNmarginWidth,            10,
      XmNmarginHeight,           5,
      XmNtraversalOn,            False,
      NULL );
  XmStringFree ( xstr );
}


/*********************
  The RadioBox dialogs
*********************/


void
Popup_creSLIB_FINI ( parent )
Widget parent;
{
#define creSLIB_FINIhelp_text "\
o `Create SLIB construct' attempts to create\n\
  the construct, first checking that it compiles;\n\
  data should be declared in the .g file, and\n\
  declared as `extern' in the .h file.\n\n\
  Imported specification/code modules (if any)\n\
  have been opened as `read only' for reference.\n\n\
  Ensure all files have been edited and saved!\n\n\
o `Cancel' aborts the creation, but preserves\n\
   all files in the SRC directory."

#define creSLIB_FINIhelp_width  350
#define creSLIB_FINIhelp_height 275

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Create SLIB construct" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 45, 40,
                          1,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "Create SLIB construct",
			  & WM_DELETE_WINDOW,
                          0
                        );
    /***
    Set OK file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) creSLIB_FINIhelp_text;
    help_data.width  = creSLIB_FINIhelp_width;
    help_data.height = creSLIB_FINIhelp_height;

  }

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


void
Popup_creSLIB ( parent )
Widget parent;
{
#define creSLIB_help_text "\
   Two different types of SLIB construct may\n\
    be created:\n\n\
o `Create SLIB-Committable construct' enables\n\
  the created construct to be subsequently\n\
  introduced into other developments; it may\n\
  import lower-level SLIB constructs.\n\n\
o `Create lower-level SLIB construct' provides\n\
  a library construct on which other SLIB\n\
  constructs may be built; this one, however, is\n\
  not made available for direct introduction\n\
  into other developments."

#define creSLIB_help_width  325
#define creSLIB_help_height 300

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Create SLIB-Committable construct" );
    strcpy ( radio_labels [ 1 ], " Create lower-level SLIB construct" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 45, 40,
                          2,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "Create SLIB Construct",
			  & WM_DELETE_WINDOW,
                          0
                        );
    /***
    Set OK file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) creSLIB_help_text;
    help_data.width  = creSLIB_help_width;
    help_data.height = creSLIB_help_height;

  }

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


void
Popup_creSLIB_INI ( parent )
Widget parent;
{
#define creSLIB_INI_help_text "\
   The .ldf file should be edited to reflect\n\
    the importation of lower-level SLIB\n\
    modules, with parameters (if any):\n\n\
o `Create code template files in SRC' results\n\
   in the creation of template .c, .h and .g\n\
   files which should be edited to create the\n\
   SLIB code module (if those files already\n\
   exist, they are not ovwrwritten).\n\n\
o `Cancel' aborts the creation, but preserves\n\
   the .ldf file in the SRC directory."

#define creSLIB_INI_help_width  300
#define creSLIB_INI_help_height 280

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Create code template files in SRC" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 45, 40,
                          1,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "Create SLIB Construct",
			  & WM_DELETE_WINDOW,
                          0
                        );
    /***
    Set OK file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) creSLIB_INI_help_text;
    help_data.width  = creSLIB_INI_help_width;
    help_data.height = creSLIB_INI_help_height;

  }

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


void
Popup_CloseEditedFile ( parent )
Widget parent;
{
#define CloseEditedFile_help_text "\
   The file in the user's SRC directory differs\n\
   from that in the system CFG directory:\n\n\
o `Commit edits' updates the CFG directory, and in\n\
  so doing causes any processing of the construct\n\
  to be lost; further, processing of any dependent\n\
  constructs is also lost (but you will be warned in\n\
  this case before the commit is actually made).\n\
  If the difference is annotational, the processing\n\
  lost is restricted to marked-up documents.\n\n\
o `Discard edits' removes the edited SRC file\n\
  from the file system.\n\n\
o `Save in SRC' does not commit the edited file,\n\
  but leaves it in the SRC directory for later use.\n\n\
o `Show difference' displays the UNIX diff between\n\
  the SRC and CFG files."

#define CloseEditedFile_help_width  375
#define CloseEditedFile_help_height 400

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Commit edits" );
    strcpy ( radio_labels [ 1 ], " Discard edits" );
    strcpy ( radio_labels [ 2 ], " Save in SRC" );
    strcpy ( radio_labels [ 3 ], " Show difference" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          4,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );
    /***
    Set OK file_diff_but
    ***/
    ok_but_data.file_diff_but = 3;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) CloseEditedFile_help_text;
    help_data.width  = CloseEditedFile_help_width;
    help_data.height = CloseEditedFile_help_height;

  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                             "Edited file exists in SRC" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 3;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


void
Popup_UpdateFileFromSRC ( parent )
Widget parent;
{
#define UpdateFileFromSRC_help_text "\
   The file in the user's SRC directory differs\n\
   from that in the system CFG directory:\n\n\
o `Commit edits' updates the CFG directory, and in\n\
  so doing causes any processing of the construct\n\
  to be lost; further, processing of any dependent\n\
  constructs is also lost (but you will be warned in\n\
  this case before the commit is actually made).\n\
  If the difference is annotational, the processing\n\
  lost is restricted to marked-up documents.\n\n\
o `Show difference' displays the UNIX diff between\n\
  the SRC and CFG files.\n\n\
o `Cancel' leaves the file in SRC."

#define UpdateFileFromSRC_help_width  375
#define UpdateFileFromSRC_help_height 310

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Commit edits" );
    strcpy ( radio_labels [ 1 ], " Show difference" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          2,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );
    /***
    Set OK file_diff_but
    ***/
    ok_but_data.file_diff_but = 1;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) UpdateFileFromSRC_help_text;
    help_data.width  = UpdateFileFromSRC_help_width;
    help_data.height = UpdateFileFromSRC_help_height;

  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                             "Update from SRC" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 1;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


void
Popup_RemoveEditedFile ( parent )
Widget parent;
{
#define RemoveEditedFile_help_text "\
   The file in the user's SRC directory differs\n\
   from that in the system CFG directory:\n\n\
o `Preserve SRC file' causes the curently-committed\n\
  CFG file to be removed from the file system.\n\n\
o `Preserve CFG file' overwrites the modified SRC file\n\
  file with the curently-committed CFG file.\n\n\
o `Show difference' displays the UNIX diff between\n\
  the SRC and CFG files."

#define RemoveEditedFile_help_width  400
#define RemoveEditedFile_help_height 325

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Preserve SRC file" );
    strcpy ( radio_labels [ 1 ], " Preserve CFG file" );
    strcpy ( radio_labels [ 2 ], " Show difference" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          3,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 2;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) RemoveEditedFile_help_text;
    help_data.width  = RemoveEditedFile_help_width;
    help_data.height = RemoveEditedFile_help_height;

  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                             "Edited file exists in SRC" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 2;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_Edt_Proceed ( parent )
Widget parent;
{
#define Edt_Proceed_help_text "\
   The file in the user's SRC directory differs\n\
   from that in the system CFG directory:\n\n\
o `Proceed after committing' updates the CFG directory,\n\
  and in so doing causes any processing of the construct\n\
  to be lost; further, processing of any dependent\n\
  constructs is also lost (but you will be warned in\n\
  this case before the commit is actually made).\n\
  If the difference is annotational, the processing\n\
  lost is restricted to marked-up documents. If the\n\
  commit is successful, current processing of the\n\
  construct will resume.\n\n\
o `Proceed without committing' leaves the edited file in\n\
  the SRC directory for later use.\n\n\
o `Show difference' displays the UNIX diff between\n\
  the SRC and CFG files."

#define Edt_Proceed_help_width  375
#define Edt_Proceed_help_height 350

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Proceed after committing" );
    strcpy ( radio_labels [ 1 ], " Proceed without committing" );
    strcpy ( radio_labels [ 2 ], " Show difference" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          3,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 2;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) Edt_Proceed_help_text;
    help_data.width  = Edt_Proceed_help_width;
    help_data.height = Edt_Proceed_help_height;
  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                             "Edited file exists in SRC" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 2;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


void
Popup_CloseEditedProofFile ( parent )
Widget parent;
{
#define CloseEditedProofFile_help_text "\
   The file in the user's SRC directory differs\n\
   from that in the system POB directory:\n\n\
o `Commit edits' updates the POB directory, provided\n\
  that the change is annotational (mathematical\n\
  changes to proof files are not allowed) when\n\
  all marked-up processing of the construct (and\n\
  that of any dependent constructs) is lost.\n\n\
o `Discard edits' removes the edited SRC file\n\
  from the file system.\n\n\
o `Save in SRC' does not commit the edited file,\n\
  but leaves it in the SRC directory for later use.\n\n\
o `Show difference' displays the UNIX diff between\n\
  the SRC and POB files."

#define CloseEditedProofFile_help_width  350
#define CloseEditedProofFile_help_height 350

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Commit edits" );
    strcpy ( radio_labels [ 1 ], " Discard edits" );
    strcpy ( radio_labels [ 2 ], " Save in SRC" );
    strcpy ( radio_labels [ 3 ], " Show difference" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          4,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

      
    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 3;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) CloseEditedProofFile_help_text;
    help_data.width  = CloseEditedProofFile_help_width;
    help_data.height = CloseEditedProofFile_help_height;
  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                             "Edited file exists in SRC" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 3;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


/*
void
Popup_CloseEditedFileQuit ( parent, recreate_flag )
Widget parent;
int recreate_flag;
{
#define CloseEditedFileQuit_help_text "\
   The file in the user's SRC directory differs\n\
   from that in the system CFG directory:\n\n\
o `Preserve SRC file' does not commit the edited file,\n\
  but leaves it in the SRC directory for later use.\n\n\
o `Discard SRC file' removes the edited SRC file\n\
  from the file system.\n\n\
o `Show difference' displays the UNIX diff between\n\
  the SRC and CFG files."

#define CloseEditedFileQuit_help_width  350
#define CloseEditedFileQuit_help_height 250

  Make_RadioBox_Dialog_Declarations;

  if ( recreate_flag ) {
    XtDestroyWidget ( dialog );
    dialog = ( Widget ) 0;    
  }

  if ( ! dialog ) {

    /???
    set labels
    ???/
    strcpy ( radio_labels [ 0 ], " Preserve SRC file" );
    strcpy ( radio_labels [ 1 ], " Discard SRC file" );
    strcpy ( radio_labels [ 2 ], " Show difference" );

    /???
    create the basic radiobox dialog
    ???/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          3,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          1
                        );

    /???
    Set file_diff_but
    ???/
    ok_but_data.file_diff_but = 2;

    /???
    Set help data
    ???/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char ? ) CloseEditedFileQuit_help_text;
    help_data.width  = CloseEditedFileQuit_help_width;
    help_data.height = CloseEditedFileQuit_help_height;

    /???
    Make Cancel insensitive
      ???/
    XtSetSensitive ( och_c, False );
  }

  /???
  Static dialog now exists - (re)create label
  ???/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                             "Edited file exists in SRC" );

  /???
  Dialog ready
  ???/
  second_visit = 0;
  global_file_diff_but = 2;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}
*/


void
Popup_OpenEditedFile ( parent )
Widget parent;
{
#define OpenEditedFile_text "\
   The file in the user's SRC directory differs\n\
   from that in the system CFG directory:\n\n\
o `Open SRC file' opens the SRC file; edits may\n\
  subsequently be commited in the usual way.\n\n\
o `Open CFG file' opens the CGF file and in so-doing\n\
  overwrites the edited SRC file (which is thus lost).\n\n\
o `Show difference' displays the UNIX diff between\n\
  the SRC and CFG files."

#define OpenEditedFile_width  375
#define OpenEditedFile_height 250

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Open SRC File" );
    strcpy ( radio_labels [ 1 ], " Open CFG File" );
    strcpy ( radio_labels [ 2 ], " Show difference" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          993,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );
    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 2;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) OpenEditedFile_text;
    help_data.width  = OpenEditedFile_width;
    help_data.height = OpenEditedFile_height;

  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                             "Edited file exists in SRC" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 2;

  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


void
Popup_OpenEditedProofFile ( parent )
Widget parent;
{
#define OpenEditedProofFile_text "\
   The file in the user's SRC directory differs\n\
   from that in the system POB directory:\n\n\
o `Open SRC file' opens the SRC file; edits may\n\
  subsequently be commited in the usual way.\n\n\
o `Open POB file' opens the POB file and in so-doing\n\
  overwrites the edited SRC file (which is thus lost).\n\n\
o `Show difference' displays the UNIX diff between\n\
  the SRC and POB files."

#define OpenEditedProofFile_width  375
#define OpenEditedProofFile_height 250

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Open SRC File" );
    strcpy ( radio_labels [ 1 ], " Open POB File" );
    strcpy ( radio_labels [ 2 ], " Show difference" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          3,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 2;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) OpenEditedProofFile_text;
    help_data.width  = OpenEditedProofFile_width;
    help_data.height = OpenEditedProofFile_height;
  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                             "Edited file exists in SRC" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 2;
  radiobox_flag = open_radiobox;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_OpenProofFile ( parent )
Widget parent;
{
#define OpenProofFile_text "\
   A Marked-up proof file exists:\n\n\
o `Open Text File' opens the text file, which may\n\
  be edited and commited in the usual way.\n\n\
o `View Marked-up File' opens the maked-up file for\n\
  inspection in an appropriate viewer."

#define OpenProofFile_width  340
#define OpenProofFile_height 190

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Open Text File" );
    strcpy ( radio_labels [ 1 ], " View Marked-up File" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          2,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) OpenProofFile_text;
    help_data.width  = OpenProofFile_width;
    help_data.height = OpenProofFile_height;
  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                                "Marked-up file exists" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_MiniRemake ( parent )
Widget parent;
{
#define MiniRemake_text "\
   The current construct has been loaded into the\n\
   editor in anticipation of a mini-remake:\n\n\
o `Mini-remake' causes the toolkit to commit\n\
  your edited changes (save them first!) and\n\
  to attempt to `remake' back to the state\n\
  immediately prior to the error detection, and\n\
  then to re-process the current job; the cycle\n\
  is repeated until either no errors remain or\n\
  the `Cancel' option is selected"   
#define MiniRemake_width  300
#define MiniRemake_height 225

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Mini-remake" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          1,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) MiniRemake_text;
    help_data.width  = MiniRemake_width;
    help_data.height = MiniRemake_height;

    /***
    not MODAL
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );
  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label, "Mini-remake" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  radiobox_flag = mini_remake_radiobox;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_CommitBToolProofs ( parent )
Widget parent;
{
#define CommitBToolProofs_text "\
   Proofs have been constructed:\n\n\
o `Commit Proofs' commits the proofs and creates\n\
  a new proof level.\n\n\
o `Don't Commit Proofs' preserves the current\n\
  proof level."
#define CommitBToolProofs_width  340
#define CommitBToolProofs_height 190

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Commit Proofs" );
    strcpy ( radio_labels [ 1 ], " Don't Commit Proofs" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          2,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) CommitBToolProofs_text;
    help_data.width  = CommitBToolProofs_width;
    help_data.height = CommitBToolProofs_height;

    /***
    not MODAL
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
       NULL );
  }

  /***
  Static dialog now exists - (re)create label
  ***/
  strcpy ( primary_string, "BToolProver" );
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label, "Commit Proofs" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  radiobox_flag = commit_btool_radiobox;
  Manage_RadioBox_Dialog_NoCancel;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_CommitIprProofs ( parent )
Widget parent;
{
#define CommitIprProofs_text "\
   Proofs have been constructed:\n\n\
o `Commit Proofs' commits the proofs and creates\n\
  a new proof level.\n\n\
o `Don't Commit Proofs' preserves the current\n\
  proof level."
#define CommitIprProofs_width  340
#define CommitIprProofs_height 190

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Commit Proofs" );
    strcpy ( radio_labels [ 1 ], " Don't Commit Proofs" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          2,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) CommitIprProofs_text;
    help_data.width  = CommitIprProofs_width;
    help_data.height = CommitIprProofs_height;

    /***
    not MODAL
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );
  }

  /***
  Static dialog now exists - (re)create label
  ***/
  strcpy ( primary_string, "InterProver" );
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label, "Commit Proofs" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  radiobox_flag = commit_ipr_radiobox;
  Manage_RadioBox_Dialog_NoCancel;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_MainAnimatorMenu ( obj )
int obj;
{
#define MainAnimatorMenu_text "\
   Animation may be conducted in one of three ways:\n\n\
o `Interactive' runs the animator interactvely\n\n\
o `Execute Step' runs runs the animator step-by-step\n\
   from a previously-saved Executable.\n\n\
o `Execute Auto' runs runs the animator automatically\n\
   from a previously-saved Executable.\n\n\
o `Edit ANIMATE Script' enables an existing ANIMATE Script\n\
   to be edited, or a new one to be created.\n\n\
o `Browse Output File' enables a previously saved output\n\
   .out file to be viewed.\n\n\
o `Clean Animator Files' allows ANIMATE (.anm) and\n\
   Output (.out) files that are no longer required\n\
   to be removed.\n\n\
See Top Bar Help `Animator'.";
  
#define MainAnimatorMenu_width  400
#define MainAnimatorMenu_height 400

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Interactive" );
    strcpy ( radio_labels [ 1 ], " Execute Step" );
    strcpy ( radio_labels [ 2 ], " Execute Auto" );
    strcpy ( radio_labels [ 3 ], " Edit ANIMATE Script" );
    strcpy ( radio_labels [ 4 ], " Browse Output File" );
    strcpy ( radio_labels [ 5 ], " Clean Animator Files" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & top_level, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          6,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) MainAnimatorMenu_text;
    help_data.width  = MainAnimatorMenu_width;
    help_data.height = MainAnimatorMenu_height;

    /***
    not MODAL
    ***/
/*
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );
*/
  }

  /***
  Static dialog now exists - (re)create label
  ***/
  strcpy ( primary_string, GetName ( obj ) );
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label, "Animator" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  radiobox_flag = six_animators_radiobox;
  curr_obj = obj;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_ThreeProvers ( obj )
int obj;
{
#define ThreeProvers_text "\
   Proof may be attempted in one of three ways:\n\n\
o `AutoProver' runs completely automatically\n\n\
o `InterProver' runs automatically, but with tracing, \n\
  enabling user-theory to be developed.\n\n\
o `BToolProver' runs completely interactively, also\n\
  enabling user-theory to be developed.\n\n\
See Top Bar Help `AutoProver', `InterProver' and `BToolProver'.";
  
#define ThreeProvers_width  400
#define ThreeProvers_height 300

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " AutoProver" );
    strcpy ( radio_labels [ 1 ], " InterProver" );
    strcpy ( radio_labels [ 2 ], " BToolProver" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & top_level, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          3,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) ThreeProvers_text;
    help_data.width  = ThreeProvers_width;
    help_data.height = ThreeProvers_height;

    /***
    not MODAL
    ***/
/*
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );
*/
  }

  /***
  Static dialog now exists - (re)create label
  ***/
  strcpy ( primary_string, GetName ( obj ) );
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label, "Provers" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  radiobox_flag = three_provers_radiobox;
  curr_obj = obj;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_EditPmd ( obj )  /* Provers Env (ie. not InterProver!) */
int obj;
{
#define EditPmd_text "\
o `Edit Current PROOFMETHOD File' opens the currrent-level\n\
  PROOFMETHOD file for the selected construct for editing\n\n\
o `Edit Global PROOFMETHOD File' opens the currrent-level\n\
  PROOFMETHOD file for editing, if the Global file is set;\n\
  it may be set/changed through TopBar Options for Provers\n\n\
o `Browse PROOFMETHOD file' provides a selection of\n\
  PROOFMETHOD files which may be opened for browsing\n\n\
See Top Bar Help `AutoProver', `InterProver' and `BToolProver'.";
  
#define EditPmd_width  400
#define EditPmd_height 300

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Edit Current PROOFMETHOD File" );
    strcpy ( radio_labels [ 1 ], " Edit Global PROOFMETHOD File" );
    strcpy ( radio_labels [ 2 ], " Browse PROOFMETHOD file" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & top_level, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          3,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          0
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) EditPmd_text;
    help_data.width  = EditPmd_width;
    help_data.height = EditPmd_height;

    /***
    not MODAL
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );
  }

  /***
  Static dialog now exists - (re)create label
  ***/
  strcpy ( primary_string, GetName ( obj ) );
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label, "Edit/Browse PROOFMETHOD File" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  curr_obj = obj;
  radiobox_flag = edit_pmd_radiobox;
  Manage_RadioBox_Dialog;

  if ( curr_env == provers_env ) DeSensitize ();

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_ClosePMDFile ( parent, recreate_flag )
Widget parent;
int recreate_flag;
{
#define ClosePMDFile_text "\
   You may close the PROOFMETHOD file\n\
    in one of two ways:\n\n\
o `Check file parses' causes the toolkit to close the\n\
  editor only when the file parses\n\n\
o `Don't check file parses' causes the toolkit to close the\n\
  editor without checking whether the file parses or not; if\n\
  the file does not parse, the PROOFMETHOD cannot be\n\
  subsequently loaded during proof"

#define ClosePMDFile_width  400
#define ClosePMDFile_height 255

  Make_RadioBox_Dialog_Declarations;

  if ( recreate_flag ) {
    XtDestroyWidget ( dialog );
    dialog = ( Widget ) 0;
  }

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Check file parses" );
    strcpy ( radio_labels [ 1 ], " Don't check file parses" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          2,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          1
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) ClosePMDFile_text;
    help_data.width  = ClosePMDFile_width;
    help_data.height = ClosePMDFile_height;

    /***
    not MODAL
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );

  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                               "Close PROOFMETHOD file" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  radiobox_flag = close_pmd_file;
  Manage_RadioBox_Dialog;
  /*** set CANCEL unsensitive ***/
  XtSetSensitive ( och_c, False );
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_CloseAnmExeFile ( parent, recreate_flag )
Widget parent;
int recreate_flag;
{
#define CloseAnmExeFile_text "\
   You may close the ANIMATE Script\n\
    in one of two ways:\n\n\
o `Check file parses' causes the toolkit to close the\n\
  editor only when the file parses\n\n\
o `Don't check file parses' causes the toolkit to close the\n\
  editor without checking whether the file parses or not; if\n\
  the file does not parse, the file cannot be executed"

#define CloseAnmExeFile_width  400
#define CloseAnmExeFile_height 255

  Make_RadioBox_Dialog_Declarations;

  if ( recreate_flag ) {
    XtDestroyWidget ( dialog );
    dialog = ( Widget ) 0;
  }

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Check file parses" );
    strcpy ( radio_labels [ 1 ], " Don't check file parses" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          2,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          1
                        );

    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) CloseAnmExeFile_text;
    help_data.width  = CloseAnmExeFile_width;
    help_data.height = CloseAnmExeFile_height;

    /***
    not MODAL
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );

  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                               "Close ANIMATE Script" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  radiobox_flag = close_anm_exe_file;
  Manage_RadioBox_Dialog;
  /*** set CANCEL unsensitive ***/
  XtSetSensitive ( och_c, False );
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_CloseAnimThyFile ( parent, recreate_flag )
Widget parent;
int recreate_flag;
{
#define CloseAnimThyFile_text "\
   You may close the animator theory file,\n\
   before resuming animation, in one of two ways:\n\n\
o `Check file parses' causes the toolkit to commit\n\
  your edited changes only when the file parses; after\n\
  committing in this way, the file will automatically\n\
  be loaded when the animator resumes\n\n\
o `Don't check file parses' causes the toolkit to commit\n\
  your edited changes whether the file parses or not; if\n\
  the file does not parse, it cannot be loaded when\n\
  the animator resumes (and a warning will be issued)"

#define CloseAnimThyFile_width  350
#define CloseAnimThyFile_height 255

  Make_RadioBox_Dialog_Declarations;

  if ( recreate_flag ) {
    XtDestroyWidget ( dialog );
    dialog = ( Widget ) 0;    
  }

  if ( ! dialog ) {

    /***
    set labels
    ***/
    strcpy ( radio_labels [ 0 ], " Check file parses" );
    strcpy ( radio_labels [ 1 ], " Don't check file parses" );

    /***
    create the basic radiobox dialog
    ***/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          2,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          1
                        );

      
    /***
    Set file_diff_but
    ***/
    ok_but_data.file_diff_but = 999;

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) CloseAnimThyFile_text;
    help_data.width  = CloseAnimThyFile_width;
    help_data.height = CloseAnimThyFile_height;

    /***
    Make Cancel insensitive
    ***/
    XtSetSensitive ( och_c, False );

    /***
    not MODAL
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );
  }

  /***
  Static dialog now exists - (re)create label
  ***/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                          "Close Animator theory file" );

  /***
  Dialog ready
  ***/
  second_visit = 0;
  global_file_diff_but = 999;
  radiobox_flag = close_anm_thy_file;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


/*
void
Popup_IniAnim ( parent, recreate_flag )
Widget parent;
int recreate_flag;
{
#define IniAnim_text "\
   You may initialise the animator in one of two ways:\n\n\
o `Initialise from file' initialises from a previously-saved\n\
  state file, by-passing the initialisation operation; any\n\
  machine parameter data will also be initialised\n\n\
o `Initialise interactively' means that all necessary data\n\
  will be prompted for"

#define IniAnim_width  350
#define IniAnim_height 195

  Make_RadioBox_Dialog_Declarations;

  if ( recreate_flag ) {
    XtDestroyWidget ( dialog );
    dialog = ( Widget ) 0;    
  }

  if ( ! dialog ) {

    /???
    set labels
    ???/
    strcpy ( radio_labels [ 0 ], " Initialise from file" );
    strcpy ( radio_labels [ 1 ], " Initialise interactively" );

    /???
    create the basic radiobox dialog
    ???/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 80, 80,
                          2,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "dummy",
			  & WM_DELETE_WINDOW,
                          1
                        );
    /???
    Set OK file_diff_but
    ???/
    ok_but_data.file_diff_but = 999;

    /???
    Set help data
    ???/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char ? ) IniAnim_text;
    help_data.width  = IniAnim_width;
    help_data.height = IniAnim_height;

    /???
    Make Cancel insensitive
    ???/
    XtSetSensitive ( och_c, False );

    /???
    not MODAL
      ???/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );
  }

  /???
  Static dialog now exists - (re)create label
  ???/
  Re_Cre_RadioBox_Dialog ( & dialog_form, & B_logo, & label,
                                           "Animator initialisation" );

  /???
  Dialog ready
  ???/
  second_visit = 0;
  global_file_diff_but = 999;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}
*/


/*
void
Popup_CmtNotParse ( parent )
Widget parent;
{
#define CmtNotParse_text "\
   It is not possible to introduce a construct that\n\
   does not parse.\n\n\
o `Introduce' causes the toolkit to check that the\n\
  construct parses, before actually introducing it."

#define CmtNotParse_width  325
#define CmtNotParse_height 155

  Make_RadioBox_Dialog_Declarations;

  if ( ! dialog ) {

    /???
    set labels
    ???/
    strcpy ( radio_labels [ 0 ], " Introduce construct" );

    /???
    create the basic radiobox dialog
    ???/
    Cre_RadioBox_Dialog ( & parent, & dialog, & dialog_form,
                          & radio_box, & radio_box_frame, 45, 40,
                          1,
                          & B_logo,
                          & sep, & och_form, & och_o, & och_c, & och_h,
                          & ok_but_data, & cancel_but_data,
                          & help_data, & label,
                          "Introduce Construct",
			  & WM_DELETE_WINDOW,
                          0
                        );
    /???
    Set OK file_diff_but
    ???/
    ok_but_data.file_diff_but = 999;

    /???
    Set help data
    ???/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char ? ) CmtNotParse_text;
    help_data.width  = CmtNotParse_width;
    help_data.height = CmtNotParse_height;

  }

  /???
  Dialog ready
  ???/
  second_visit = 0;
  global_file_diff_but = 999;
  Manage_RadioBox_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}
*/


/***********************************************************************
************************************************************************
                         Prompt dialogs
************************************************************************
***********************************************************************/

/**************************************************
          Callback routines
***************************************************/

void
Popup_PromptDialog_WM_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
  Popup_NoCancel_PromptDialog ( top_level, 1 );
  Popup_Info ( "  Ouch!  " );
}

void
Popup_PromptDialog_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
  int ok_pressed;

  /***
  destroy parent dialog/get OK or CANCEL
  ***/
  if ( cbs->reason == XmCR_PROTOCOLS ) {    /*** WM Close ***/
    ok_pressed = 0;
/***
printf ( "prompt_dialog  = %d\n", ( Widget ) client_data );
***/
    XtUnmanageChild ( ( Widget ) client_data );
    XmUpdateDisplay ( ( Widget ) client_data );
  }
  else {
    if ( ( * ( int * ) client_data ) == OK_BUTTON )
      ok_pressed = 1;
    else
      ok_pressed = 0;
/***
printf ( "prompt_dialog  = %d\n", prompt_dialog );
***/
    XtUnmanageChild ( prompt_dialog );
    XmUpdateDisplay ( prompt_dialog );
  }

/***
printf ( "cbs->reason   = %d\n", cbs->reason );
printf ( "ok_pressed    = %d\n", ok_pressed );
***/

  /***
  check Animator
  ***/
/*
  if ( curr_env == anm_env ) {
    if ( sub_frame3 ) {
      XtVaSetValues ( sub_text3, XmNforeground, gray64, NULL );
      XmUpdateDisplay ( sub_frame3 );
    }
    else if ( sub_frame2 ) {
      XtVaSetValues ( sub_text2, XmNforeground, gray64, NULL );
      XmUpdateDisplay ( sub_frame2 );
    }
    else if ( sub_frame1 ) {
      XtVaSetValues ( sub_text1, XmNforeground, gray64, NULL );
      XmUpdateDisplay ( sub_frame1 );
    }
  }
*/

  if ( ok_pressed ) {

    /***
    write string to fifo_write_buf
    ***/
    {
       char * text;

       XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text );
       strcpy ( fifo_write_buf, text );
       XtFree ( text );

       if ( fifo_write_buf [ 0 ] == '\0' ) {
         XtManageChild ( prompt_dialog );
         XmUpdateDisplay ( prompt_dialog );
         Popup_Minor_Err ( top_level, "  Nothing entered!  " );
         return;
       }

       if ( ! FormulaParses ( fifo_write_buf ) ) {
         XtManageChild ( prompt_dialog );
         XmUpdateDisplay ( prompt_dialog );
         Popup_Minor_Err ( top_level, "  Parse Error!  " );
         return;
       }

       strcat ( fifo_write_buf, ":" );
     }
  }

  else {           /*** CANCEL_BUTTON ***/

    strcpy ( fifo_write_buf, "0:" );
  }

  Cre_fifo_write_buf_cmd_0 ( BT_BSEL );

  /***
  InvokeB
  ***/
  InvokeB ( without_XTerm, 1 );
}

void
Popup_DontWait_InformationDialog_CB ( prompt_dialog, client_data, call_data )
Widget prompt_dialog;
XtPointer client_data;
XtPointer call_data;
{
  /*
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;

  /???
  popdown dialog
  ???/
  if ( cbs->reason == XmCR_PROTOCOLS ) {    /??? WM Close ???/
    XtUnmanageChild ( ( Widget ) client_data );
    XmUpdateDisplay ( ( Widget ) client_data );
  }
  else {
    XtUnmanageChild ( prompt_dialog );
    XmUpdateDisplay ( prompt_dialog );
  }
*/
  ;
}

void
Popup_InformationDialog_CB ( prompt_dialog, client_data, call_data )
Widget prompt_dialog;
XtPointer client_data;
XtPointer call_data;
{
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;

  /***
  popdown dialog
  ***/
  if ( cbs->reason == XmCR_PROTOCOLS ) {    /*** WM Close ***/
    XtUnmanageChild ( ( Widget ) client_data );
    XmUpdateDisplay ( ( Widget ) client_data );
  }
  else {
    XtUnmanageChild ( prompt_dialog );
    XmUpdateDisplay ( prompt_dialog );
  }

/***
printf ( "cbs->reason   = %d\n", cbs->reason );
***/

/*
  /???
  check Animator
  ???/
  if ( curr_env == anm_env ) {
    if ( sub_frame3 ) {
      XtUnmanageChild ( sub_frame3 );
      XmUpdateDisplay ( sub_frame3 );
      XtDestroyWidget ( sub_frame3 );
      sub_frame3 = ( Widget ) NULL;
    }
    if ( sub_frame2 ) {
      XtUnmanageChild ( sub_frame2 );
      XmUpdateDisplay ( sub_frame2 );
      XtDestroyWidget ( sub_frame2 );
      sub_frame2 = ( Widget ) NULL;
    }
    if ( sub_frame1 ) {
      XtUnmanageChild ( sub_frame1 );
      XmUpdateDisplay ( sub_frame1 );
      XtDestroyWidget ( sub_frame1 );
      sub_frame1 = ( Widget ) NULL;
    }
    XmUpdateDisplay ( constructs_rc );
    XmUpdateDisplay ( constructs_scroll );
    XmUpdateDisplay ( constructs_form );
  }
*/

  strcpy ( fifo_write_buf, "CR:" );
  Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
  InvokeB ( without_XTerm, 1 );
}

void
Popup_SavePromptDialog_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
  void SaveInRemakableForm ();

  XtUnmanageChild ( prompt_dialog );
  XmUpdateDisplay ( prompt_dialog );

  if ( * ( int * ) client_data == OK_BUTTON ) {
    /***
    load primary_string
    ***/
    char * text;
    XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text);
    strcpy ( primary_string, text );
    XtFree ( text );

    if ( primary_string [ 0 ] == '\0' )  {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level,"  Directory string empty!  " );
      return;
    }

    if ( ! FormulaParses ( primary_string ) ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      DisplayCurrWinText ( "\n\n    Bad save directory:\n\n        " );
      DisplayCurrWinText ( primary_string );
      DisplayCurrWinText ( "\n\n    It does not conform to a B-formula!\n\n       One or more of the directory names is not an\n       `arity 1' symbol - see $BKIT/BHELP/BPlatform.html\n\n    Can't save to that directory\n\n\n" );
      Popup_Minor_Err ( top_level,"  Can't save to that directory  " );
      return;
    }

    DeSensitize ();
    SaveInRemakableForm ();

  }

  else {  /*** CANCEL ***/
    DisplayCurrWinText ( "\n  Save development aborted\n" );
  }

}

void
Popup_FindPromptDialog_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{

  XtUnmanageChild ( prompt_dialog );
  XmUpdateDisplay ( prompt_dialog );

  if ( * ( int * ) client_data == OK_BUTTON ) {
    /***
    write string to fifo_write_buf
    ***/
    char * text;
    XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text );
    strcpy ( fifo_write_buf, text );
    XtFree ( text );

    if ( fifo_write_buf [ 0 ] == '\0' ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Nothing entered!  " );
      return;
    }

    if ( ! FormulaParses ( fifo_write_buf ) ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Parse Error!  " );
      return;
    }

    /***
    reset radiobox & sel options!
    ***/
    strcat ( fifo_write_buf, ":" );
    CreNumInBuf ( fifo_write_buf, BT_FIND_WITH_ENV );
    Cre_tcp_env ();
    InvokeB ( without_XTerm, 1 );
  }

  else {  /*** CANCEL ***/
    /***
    reset radiobox & sel options!
    ***/
    radiobox_flag = 0;
    Popup_Sel_flag = 0;  
    DisplayCurrentEnv ();
  }

}

void
Popup_RenamePromptDialog_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
   char * text;
   int ok_pressed;


  /***
  get parent dialog/OK or CANCEL/file_diff_but/rad_but
  ***/
  if ( cbs->reason == XmCR_PROTOCOLS ) {    /*** WM Close ***/
    ok_pressed = 0;
    XtUnmanageChild ( ( Widget ) client_data );
    XmUpdateDisplay ( ( Widget ) client_data );
  }
  else {
    if ( * ( int * ) client_data == OK_BUTTON )
      ok_pressed = 1;
    else
      ok_pressed = 0;
      XtUnmanageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
  }

/***
printf ( "cbs->reason   = %d\n", cbs->reason );
printf ( "ok_pressed    = %d\n", ok_pressed );
***/

  if ( * ( int * ) client_data == OK_BUTTON ) {
    XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text );
    strcpy ( fifo_write_buf, text );
    XtFree ( text );

    if ( fifo_write_buf [ 0 ] == '\0' ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Rename string empty!  " );
      return;
    }

    if ( ! FormulaParses ( fifo_write_buf ) ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Parse Error!  " );
      return;
    }

    radiobox_flag = 0;
    Popup_Sel_flag = 0;  
    Rename ( fifo_write_buf );
  }

  else {  /*** CANCEL ***/
    radiobox_flag = 0;
    Popup_Sel_flag = 0;  
    DisplayCurrWinText ( "\n  Rename aborted\n" );
    DisplayCurrentEnv ();
  }

}

/*
void
Popup_SaveBrowseDialog_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct ?cbs;
{
  /???
  reset radiobox & sel options!
  ???/
  radiobox_flag = 0;
  Popup_Sel_flag = 0;  

  if ( ? ( int ? ) client_data == OK_BUTTON ) {
     FILE ? psfile;
     char buf [ 250 ];
     char ? text;
     XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text );
     if ( text != NULL ) {
       strcpy ( buf, "TEX/" );
       strcat ( buf, text );
       strcat ( buf, ".xwd" );
       buf [ 249 ] = '\0';
       strcpy ( additional_string, buf );
       psfile = fopen ( buf, "r" );
       if ( psfile != NULL ) {
         fclose ( psfile );
        strcpy ( primary_string, "\"" );
        strcat ( primary_string, buf );
        strcat ( primary_string, "\" already exists - overwrite?" );
        strcpy ( secondary_string, "Existing file will be lost" );
        radiobox_flag = save_browse_radiobox;
        strcpy ( additional_string, buf );
        confirm_flag = radiobox_flag;
        Popup_ConfirmDialog ( top_level );      
       }
       else {
         strcpy ( buf, "TEX/" );
         strcat ( buf, text );
         strcat ( buf, ".eps" );
         buf [ 249 ] = '\0';
         psfile = fopen ( buf, "r" );
         if ( psfile != NULL ) {
           fclose ( psfile );
          strcpy ( primary_string, "\"" );
          strcat ( primary_string, buf );
          strcat ( primary_string, "\" already exists - overwrite?" );
          strcpy ( secondary_string, "Existing file will be lost" );
          radiobox_flag = save_browse_radiobox;
          confirm_flag = radiobox_flag;
          Popup_ConfirmDialog ( top_level );      
	 }
         else {
           SaveBrowse ( buf );
	 }
       }
     }
     else {
       Popup_Info ( "  Filename string empty!  " );
    }
  }
  else {  /??? CANCEL ???/
    /???
    popdown dialog
    ???/
    XtUnmanageChild ( prompt_dialog );
    XmUpdateDisplay ( prompt_dialog );
  }
}
*/

void
Popup_LIBRenamePromptDialog_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
  char str [ 250 ];
  int i, j, ps_len;
  char sub_str [ 250 ];
  char * text;

  XtUnmanageChild ( prompt_dialog );
  XmUpdateDisplay ( prompt_dialog );

  if ( * ( int * ) client_data == OK_BUTTON ) {

    XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text );
    strcpy ( primary_string, text );
    XtFree ( text );

    if ( primary_string [ 0 ] == '\0' ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Rename string empty!  " );
      return;
    }

    if ( ! FormulaParses ( primary_string ) ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Parse Error!  " );
      return;
    }

    if ( ( primary_string [ 0 ] < 'a' || primary_string [ 0 ] > 'z' ) &&
         ( primary_string [ 0 ] < 'A' || primary_string [ 0 ] > 'Z' )   ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "The rename prefix must begin with a letter" );
      return;
    }

    ps_len = strlen ( primary_string );
    strcpy ( str, "(\"" );
    strcat ( str, primary_string );
    strcat ( str, "\"," );
    i = 7;
    j = 0;
    while ( secondary_string [ i ] != '.' ) {
      sub_str [ j ] = secondary_string [ i ];
      i++;
      j++;
    }
    sub_str [ j ] = '\0';
    strcat ( str, sub_str );
    strcat ( str, "):" );
    strcat ( primary_string, "_" );
    strcat ( primary_string, sub_str );
    strcat ( primary_string, ".mch" );
    j = IsAlreadyPresentFromCompositeString ( primary_string );
    if ( j ) {
      primary_string [ strlen ( primary_string ) - 4 ] = '\0';
      strcat ( primary_string, ": name is already used  " );
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, primary_string );
      return;
    }
    else {
      if ( ps_len <= 34 ) {
        strcpy ( fifo_write_buf, str );
        if ( Popup_Sel_flag == introduce_SLIB_selection ) {
          Popup_Sel_flag = 0;
          CreNumInBuf ( fifo_write_buf, BT_LIB_FRC_WITH_ENV );
          Cre_tcp_env ();
          InvokeB ( without_XTerm, 1 );
        }
        else if ( Popup_Sel_flag == introduce_VHDL_SLIB_selection ) {
          Popup_Sel_flag = 0;
          CreNumInBuf ( fifo_write_buf, BT_VHDL_LIB_FRC_WITH_ENV );
          Cre_tcp_env ();
          InvokeB ( without_XTerm, 1 );
        }
      }
      else {
        primary_string [ strlen ( primary_string ) - 4 ] = '\0';
        strcat ( primary_string, ": rename prefix too long  " );
        XtManageChild ( prompt_dialog );
        XmUpdateDisplay ( prompt_dialog );
        Popup_Minor_Err ( top_level, "Rename prefix too long!" );
        return;
      }
    }
  }

  else { /*** CANCEL ***/
    Popup_Sel_flag = 0;
  }
}

void
Popup_IntroduceNewNamePromptDialog_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
      char s [ 100 ];
      int slen;
      int not_ident = 0;
      int ext_option, ok;
      char * text;

      XtUnmanageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );

      if ( * ( int * ) client_data == CANCEL_BUTTON ) return;

      XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text );
      strcpy ( s, text );
      s [ 99 ] = '0';
      XtFree ( text );

      if ( s [ 0 ] == '\0' ) {
        XtManageChild ( prompt_dialog );
        XmUpdateDisplay ( prompt_dialog );
        Popup_Minor_Err ( top_level, "  Empty input!  " );
        return;
      }

      if ( ! FormulaParses ( s ) ) {
        XtManageChild ( prompt_dialog );
        XmUpdateDisplay ( prompt_dialog );
        Popup_Minor_Err ( top_level, "  Parse Error!  " );
        return;
      }

      if ( NameAlreadyUsed ( s, -1 ) ) {
        sprintf ( buf, "Name \"%s\" is already used  ", s );
        XtManageChild ( prompt_dialog );
        XmUpdateDisplay ( prompt_dialog );
        Popup_Minor_Err ( top_level, buf );
        return;
      }

       /***
        check identifier
        ***/ 
        if ( ! IsIdentifier ( s ) ) {
          sprintf ( buf, "  `%s' is not an identifier  ", s );
          XtManageChild ( prompt_dialog );
          XmUpdateDisplay ( prompt_dialog );
          Popup_Minor_Err ( top_level, buf );
          return;
	}


        /***
        write string to fifo_write_buf (in case it doesn't parse) ?????
        ***/
 
        strcat ( s, ":" );
        strcpy ( fifo_write_buf, s );
        switch ( option ) {
          case 0:
            if ( strlen ( s ) < 50 ) {
              Cre_fifo_write_buf_cmd_0 ( BT_CMT_NEW_MCH );          
              InvokeB ( without_XTerm, 1 );
	    }
            else {
              XtManageChild ( prompt_dialog );
              XmUpdateDisplay ( prompt_dialog );
              Popup_Minor_Err ( top_level, "Construct name too long (max length 50)" );
              return;
	    }
            break;
	case 1:
            if ( strlen ( s ) < 50 ) {
               Cre_fifo_write_buf_cmd_0 ( BT_CMT_NEW_REF );          
               InvokeB ( without_XTerm, 1 );
	     }
            else {
              XtManageChild ( prompt_dialog );
              XmUpdateDisplay ( prompt_dialog );
              Popup_Minor_Err ( top_level, "Construct name too long (max length 50)" );
              return;
	    }
            break;
          case 3:
            if ( strlen ( s ) < 50 ) {
              Cre_fifo_write_buf_cmd_0 ( BT_CMT_NEW_IMP );          
              InvokeB ( without_XTerm, 1 );
	    }
            else {
              XtManageChild ( prompt_dialog );
              XmUpdateDisplay ( prompt_dialog );
              Popup_Minor_Err ( top_level, "Construct name too long (max length 50)" );
              return;
	    }
            break;
          case 5:
            CheckBaseUnderscore ( &ok, s );
            if ( ok ) {
              if ( strlen ( s ) < 30 ) {
                Cre_fifo_write_buf_cmd_0 ( BT_CMT_NEW_BASE );          
                InvokeB ( without_XTerm, 1 );
	      }
              else {
                XtManageChild ( prompt_dialog );
                XmUpdateDisplay ( prompt_dialog );
                Popup_Minor_Err ( top_level, "Base name too long (max length 30)" );
                return;
	      }
	    }
            break;
          case 6:
            if ( strlen ( s ) < 30 ) {
              Cre_fifo_write_buf_cmd_0 ( BT_CMT_NEW_ENUM );          
              InvokeB ( without_XTerm, 1 );
	    }
            else {
              XtManageChild ( prompt_dialog );
              XmUpdateDisplay ( prompt_dialog );
              Popup_Minor_Err ( top_level, "Construct name too long (max length 30)" );
              return;
	    }
            break;
          case 8:
            if ( strlen ( s ) < 40 ) {
              Cre_fifo_write_buf_cmd_0 ( BT_CMT_NEW_ITF );          
              InvokeB ( without_XTerm, 1 );
	    }
            else {
              XtManageChild ( prompt_dialog );
              XmUpdateDisplay ( prompt_dialog );
              Popup_Minor_Err ( top_level, "Construct name too long (max length 40)" );
              return;
	    }
            break;
          case 10:
            if ( strlen ( s ) < 50 ) {
              Cre_fifo_write_buf_cmd_0 ( BT_CMT_NEW_DOC );          
              InvokeB ( without_XTerm, 1 );
	    }
            else {
              XtManageChild ( prompt_dialog );
              XmUpdateDisplay ( prompt_dialog );
              Popup_Minor_Err ( top_level, "Construct name too long (max length 50)" );
              return;
	    }
            break;

	} /* switch ( option ) */
}

void
SaveAnimOutput ( file, dont_allow_overwrite_flag )
int dont_allow_overwrite_flag;
char * file;
{
  int i, j, ps_len;
  FILE * fileptr;
  FILE * fileptr1;
  void Popup_SaveAnimOutput ();

/***
printf ( "SaveAnimOutput ( `%s' %d )\n", file, dont_allow_overwrite_flag );
***/
  if ( dont_allow_overwrite_flag ) {
    fileptr = fopen ( file, "r" );
    if ( fileptr != NULL ) {
      fclose ( fileptr );
      sprintf ( primary_string, "  File \"%s\" already exists!  ", file );
      Popup_SaveAnimOutput ();
      Popup_Minor_Err ( top_level, primary_string );
      return;
    }
  }

  fileptr = fopen ( file, "w" );
  if ( fileptr == NULL ) {
    sprintf ( primary_string, "  Can't open \"%s\" for writing!  ", file );
    Popup_SaveAnimOutput ();
    Popup_Minor_Err ( top_level, primary_string );
    return;
  }
  fileptr1 = fopen ( "TMP/anm.out", "r" );
  if ( fileptr1 == NULL ) {
    sprintf ( buf, "  Can't open \"%s\" for reading!  ", "TMP/anm.out" );
    fclose ( fileptr );
    Animate_Utilities ( top_level );
    Popup_Minor_Err ( top_level, buf );
    return;
  }
  c = getc ( fileptr1 );
  while ( c != EOF ) {
    putc ( c,  fileptr );
    c = getc ( fileptr1 );
  }
  fclose ( fileptr );
  fclose ( fileptr1 );

  Animate_Utilities ( top_level );
  sprintf ( primary_string, "Wrote %s", file );
  Popup_Info ( primary_string );
}

void
Popup_SaveAnimOutput_NewFile_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
  char * text;

  XtUnmanageChild ( prompt_dialog );
  XmUpdateDisplay ( prompt_dialog );

  if ( * ( int * ) client_data == OK_BUTTON ) {

    XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text );
    strcpy ( buf, text );
    XtFree ( text );

    if ( buf [ 0 ] == '\0' ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Filename empty!  " );
      return;
    }

    if ( strlen ( buf ) > 30 ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "Filname too long (max length 30)" );
      return;
    }

    if ( ! FormulaParses ( buf ) ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Parse Error!  " );
      return;
    }

    sprintf ( str_buf, "SRC/%s.%s.out", GetShortName ( curr_obj ), buf );
    SaveAnimOutput ( str_buf, 1 ); /* 1 => don't allow overwrite */
  }

  else { /*** CANCEL ***/
    Animate_Utilities ( top_level );
  }

}

void
SaveAnimateFile ( file, dont_allow_overwrite_flag )
char * file;
int dont_allow_overwrite_flag;
{
  int i;
  FILE * fileptr;
  FILE * fileptr1;
  void Popup_SaveAnimateFile ();

/***
printf ( "SaveAnimateFile ( %s %d )\n", file, dont_allow_overwrite_flag );
***/
  if ( dont_allow_overwrite_flag ) {
    fileptr = fopen ( file, "r" );
    if ( fileptr != NULL ) {
      fclose ( fileptr );
      sprintf ( primary_string, "  File \"%s\" already exists!  ", file );
      Popup_SaveAnimateFile ();
      Popup_Minor_Err ( top_level, primary_string );
      return;
    }
  }

  fileptr = fopen ( file, "w" );
  if ( fileptr == NULL ) {
    sprintf ( primary_string, "  Can't open \"%s\" for writing!  ", file );
    Popup_SaveAnimateFile ();
    Popup_Minor_Err ( top_level, primary_string );
    return;
  }
  fileptr1 = fopen ( "TMP/anm.anm", "r" );
  if ( fileptr1 == NULL ) {
    sprintf ( buf, "  Can't open \"%s\" for reading!  ", "TMP/anm.anm" );
    fclose ( fileptr );
    Animate_Utilities ( top_level );
    Popup_Minor_Err ( top_level, buf );
    return;
  }
  fprintf ( fileptr, "ANIMATE\n\n  ", file );
  i = 4;
  while ( file [ i ] != '\0' ) { putc ( file [ i++ ],  fileptr ); }
  c = getc ( fileptr1 );
  while ( c != EOF ) {
    putc ( c,  fileptr );
    c = getc ( fileptr1 );
  }
  fprintf ( fileptr, "\n\nEND\n" );
  fclose ( fileptr );
  fclose ( fileptr1 );

  Animate_Utilities ( top_level );
  sprintf ( primary_string, "Wrote %s", file );
  Popup_Info ( primary_string );
}

void
Popup_SaveAnimateFile_NewFile_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
  char * text;

  XtUnmanageChild ( prompt_dialog );
  XmUpdateDisplay ( prompt_dialog );

  if ( * ( int * ) client_data == OK_BUTTON ) {

    XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text );
    strcpy ( buf, text );
    XtFree ( text );

    if ( buf [ 0 ] == '\0' ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Filename empty!  " );
      return;
    }

    if ( strlen ( buf ) > 30 ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "Filname too long (max length 30)" );
      return;
    }

    if ( ! FormulaParses ( buf ) ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Parse Error!  " );
      return;
    }

    sprintf ( str_buf, "SRC/%s.%s.anm", GetShortName ( curr_obj ), buf );
    SaveAnimateFile ( str_buf, 1 ); /* 1 => don't allow overwrite */
  }

  else { /*** CANCEL ***/
    Animate_Utilities ( top_level );
  }

}

void
Popup_PromptDialogHelp_CB ()
{
  struct help_struct help_data;
  char text[500];

  /***
  set help data and call Popup_Help_CB 
  ***/
  switch ( secondary_string [ 0 ] ) {
    case '0' : /*** Non-zero actual value parameter ***/
      strcpy ( text, "The parameter should be non-zero." );
      help_data.width  = 270;
      help_data.height = 100;
      break;
    case '1' : /*** Rename construct ***/
      strcpy ( text, "The name must be an identifier,\nwith a maximum length of 50." );
      help_data.width  = 250;
      help_data.height = 120;
      break;
    case '2' : /*** LIB Rename ***/
      strcpy ( text, "The Rename must be an identifier\nand be such that the length of the renamed\nconstruct does not exceed 35." );
      help_data.width  = 350;
      help_data.height = 120;
      break;
    case '3' : /*** Find ***/
      strcpy ( text, "Enter one or more identifiers (no repetitions\nand separated by commas); they will be sought\nin constructs which are currently analysed." );
      help_data.width  = 310;
      help_data.height = 130;
      break;
    case '4' : /*** ntroduce New Contruct ***/
      strcpy ( text, "The name must be an identifier,\nwith a maximum length of 30, and\nshould not contain the underscore character." );
      help_data.width  = 300;
      help_data.height = 130;
      break;
    case '5' : /*** Save ***/
      strcpy ( text, "The directory may be given as absolute,\nor as relative to the current directory;\nthe directory must not already exist\n(and it must conform to a B-formula)." );
      help_data.width  = 310;
      help_data.height = 140;
      break;
    case '7' : /*** SaveBrowse ***/
      strcpy ( text, "The filname must be an identifier; the browse will be saved as the\nImage file TEX/filename.xwd (using `xwd') and processed\nas the PostScript file TEX/filename.eps (using `xpr')." );
      help_data.width  = 400;
      help_data.height = 150;
      break;

    case 'd' : /*** VHDL sub-module ***/
      strcpy ( text, "The name must be an identifier,\nwith a maximum length of 20\nand ending in `_CM'" );
      help_data.width  = 310;
      help_data.height = 140;
      break;
    case 'e' : /*** Popup_SaveAnimOutput_NewFile ***/
      strcpy ( text, "Click OK to save output from this Animator session.\n\nThe input must be an identifier\n\nThe output filename will be constructed as:\n    \"SRC/machinename.identifier.out\"\n\n This filename must not already exist." );
      help_data.width  = 350;
      help_data.height = 200;
      break;
    case 'f' : /*** Popup_SaveAnimateFile_NewFile ***/
      strcpy ( text, "Click OK to save ANIMATE Script from this Animator session.\n\nThe input must be an identifier\n\nThe output filename will be constructed as:\n    \"SRC/machinename.identifier.anm\"\n\n This filename must not already exist." );
      help_data.width  = 350;
      help_data.height = 200;
      break;
    case 'g' : /*** Popup_EditAnimateFile_NewFile ***/
      strcpy ( text, "Click OK create & edit new ANIMATE Script.\n\nThe input must be an identifier\n\nThe filename will be constructed as:\n    \"SRC/machinename.identifier.anm\"\n\n This filename must not already exist." );
      help_data.width  = 350;
      help_data.height = 200;
      break;
    case 'h' : /*** Popup_SetMaxGenHyp ***/
      strcpy ( text, "The number input will automatically be saved to\nOptions Provers->Max Generated Hypotheses." );
      help_data.width  = 350;
      help_data.height = 150;
      break;
    case 'i' : /*** Animator.thy ***/
      strcpy ( text, "Cannot quantify over carrier set\nLimit the set to continue :{e1,.,en}." );
      help_data.width  = 275;
      help_data.height = 110;
      break;
    case 'j' : /*** Animator.thy ***/
      strcpy ( text, "Cannot quantify over infinite sets\nLimit the set to continue :{0,1,2}." );
      help_data.width  = 275;
      help_data.height = 110;
      break;
    default : /*** text ***/
      strcpy ( text, secondary_string );
      help_data.width  = 250;
      help_data.height = 110;
      break;
  }

  help_data.type   = DIALOG_HELP;
  help_data.text = ( char * ) text;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}


/**************************************************
     Routines for creating prompt dialogs
***************************************************/

Widget
Cre_Information_Dialog ( parent )
Widget parent;
{
  Widget dialog;
  static struct coord coord_data;

  coord_data.x = 0; /* not used */
  coord_data.y = 20; /* 60; */

  /***
  create the dialog
  ***/
  dialog = XmCreateInformationDialog ( top_frame_form, "InfoDialog", NULL, 0 );
  XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
      ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
      ( XtPointer ) & coord_data );
  XtVaSetValues ( dialog,
      XmNsymbolPixmap,           B_framed_pixmap_gray94,
      XmNmarginWidth,            10,
      XmNmarginHeight,           5,
      XmNdialogStyle,            XmDIALOG_MODELESS,
      XmNdefaultButtonType,      XmNONE,
      NULL );

  /***
  unmanage cancel & help buttons & change label
  ***/
  XtUnmanageChild ( XmMessageBoxGetChild ( dialog, XmDIALOG_CANCEL_BUTTON ) );
  XtUnmanageChild ( XmMessageBoxGetChild ( dialog, XmDIALOG_HELP_BUTTON ) );

  XtVaSetValues ( XmMessageBoxGetChild ( dialog, XmDIALOG_OK_BUTTON ),
      XmNdefaultButton,        False,
      XmNdefaultButtonShadowThickness,  1,
      XmNnavigationType,       XmTAB_GROUP,
      XmNhighlightThickness,   1,
      NULL );

  /***
  add the callback
  ***/
  XtAddCallback ( dialog, XmNokCallback,
      ( XtCallbackProc ) Popup_InformationDialog_CB,
      ( XtPointer ) & c_arr [ OK_BUTTON ] );

  XmProcessTraversal ( XmMessageBoxGetChild ( dialog, XmDIALOG_OK_BUTTON ),
                                                          XmTRAVERSE_CURRENT );
  /***
  return dialog
  ***/
  return ( dialog );
}

Widget
Cre_Prompt_Dialog ( parent )
Widget parent;
{
  Widget dialog;
  static struct coord coord_data;
  Atom WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

  coord_data.x = 0; /* not used */
  coord_data.y = 150;

  /***
  create the dialog
  ***/
  dialog = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
  XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
      ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
      ( XtPointer ) & coord_data );
  XtVaSetValues ( dialog,
      XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
      XmNautoUnmanage,           False,
      XmNsymbolPixmap,           B_framed_pixmap_gray94,
      XmNmarginWidth,            10,
      XmNmarginHeight,           5,
      XmNdefaultButtonType,      XmNONE,
      NULL );

  /***
  add the callbacks
  ***/
  XtAddCallback ( dialog, XmNokCallback,
      ( XtCallbackProc ) Popup_PromptDialog_CB,
      ( XtPointer ) & c_arr [ OK_BUTTON ] );
  XtAddCallback ( dialog, XmNcancelCallback,
      ( XtCallbackProc ) Popup_PromptDialog_CB,
      ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
  XmAddWMProtocolCallback ( XtParent ( dialog ), WM_DELETE_WINDOW,
      ( XtCallbackProc ) Popup_PromptDialog_CB,
      ( XtPointer ) dialog );
  XtAddCallback ( dialog, XmNhelpCallback,
      ( XtCallbackProc ) Popup_PromptDialogHelp_CB,
      ( XtPointer ) NULL );

  /***
  return dialog
  ***/
  return ( dialog );
}

Widget
Cre_NoCancel_Prompt_Dialog ( parent )
Widget parent;
{
  Widget dialog;
  static struct coord coord_data;

  coord_data.x = 0; /* not used */
  coord_data.y = 20; /* 60; */

  /***
  create the dialog
  ***/
  dialog = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
  XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
      ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
      ( XtPointer ) & coord_data );
  XtVaSetValues ( dialog,
      XmNdialogStyle,            XmDIALOG_MODELESS,
      XmNautoUnmanage,           False,
      XmNsymbolPixmap,           B_framed_pixmap_gray94,
      XmNmarginWidth,            10,
      XmNmarginHeight,           5,
      XmNdefaultButtonType,      XmNONE,
      NULL );

  /***
  unmanage cancel button
  ***/
  XtUnmanageChild ( XmMessageBoxGetChild ( dialog, XmDIALOG_CANCEL_BUTTON ) );

  /***
  add the callbacks
  ***/
  XtAddCallback ( dialog, XmNokCallback,
      ( XtCallbackProc ) Popup_PromptDialog_CB,
      ( XtPointer ) & c_arr [ OK_BUTTON ] );
  XtAddCallback ( dialog, XmNhelpCallback,
      ( XtCallbackProc ) Popup_PromptDialogHelp_CB,
      ( XtPointer ) NULL );

  /***
  return dialog
  ***/
  return ( dialog );
}


/*********************
  The prompt dialogs
*********************/

void
Popup_DontWait_InformationDialog ( parent )
Widget parent;
{
  static Widget dialog = ( Widget ) 0;
  static Atom WM_DELETE_WINDOW;

  if ( ! dialog ) {
    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );
    dialog = Cre_Information_Dialog ( parent );
    XmAddWMProtocolCallback ( XtParent ( dialog ), WM_DELETE_WINDOW,
        ( XtCallbackProc ) Popup_DontWait_InformationDialog_CB,
        ( XtPointer ) dialog );
    /***
    remove the callback added by Cre_Information_Dialog
    ***/
    XtRemoveCallback ( dialog, XmNokCallback,
        ( XtCallbackProc ) Popup_InformationDialog_CB,
        ( XtPointer ) & c_arr [ OK_BUTTON ] );
  }

  /***
  Static dialog now exists - create message
  ***/
  {
    XmString xstr = XmStringCreateLtoR ( primary_string, charset );
    XtVaSetValues ( dialog,
        XmNmessageString,     xstr,
        NULL );
    XmStringFree ( xstr );
  }

  /***
  Prompt dialog ready
  ***/
  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );

  /***
  Don't Wait
  ***/
  strcpy ( fifo_write_buf, "0:" );
  Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
  InvokeB ( without_XTerm, 1 );
}

void
Popup_InformationDialog ( parent )
Widget parent;
{
  static Widget dialog = ( Widget ) 0;
  static Atom WM_DELETE_WINDOW;

  if ( ! dialog ) {
    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );
    dialog = Cre_Information_Dialog ( parent );
    XmAddWMProtocolCallback ( XtParent ( dialog ), WM_DELETE_WINDOW,
        ( XtCallbackProc ) Popup_InformationDialog_CB,
        ( XtPointer ) dialog );
  }

  /***
  Static dialog now exists - create message
  ***/
  {
    XmString xstr = XmStringCreateLtoR ( primary_string, charset );
    XtVaSetValues ( dialog,
        XmNmessageString,     xstr,
        NULL );
    XmStringFree ( xstr );
  }

  /***
  Prompt dialog ready
  ***/
  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Popup_PromptDialog ( parent )
Widget parent;
{
  static Widget dialog = ( Widget ) 0;

  if ( ! dialog ) {
    dialog = Cre_Prompt_Dialog ( parent );
  }

  /***
  Static dialog now exists - create prompt
  ***/
  {
    XmString xstr = XmStringCreateLtoR ( primary_string, charset );
    XtVaSetValues ( dialog,
        XmNselectionLabelString,     xstr,
        NULL );
    XmStringFree ( xstr );
  }

  /***
  set the default text
  ***/
  {
    XmString xstr;

    if ( additional_string [ 0 ] == '\0' ) {
      xstr = XmStringCreateLtoR ( (char * ) "", charset );
    }
    else {
      xstr = XmStringCreateLtoR ( (char * ) additional_string, charset );
    }
    XtVaSetValues ( dialog, XmNtextString, xstr, NULL );
    XmStringFree ( xstr );
  }

  /***
  Prompt dialog ready
  ***/
  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Popup_NoCancel_PromptDialog ( parent, recreate_flag )
Widget parent;
int recreate_flag;
{
  static Widget dialog = ( Widget ) 0;
  static Atom WM_DELETE_WINDOW;
  if ( recreate_flag ) {     /* from Popup_PromptDialog_WM_CB */
    XtDestroyWidget ( XtParent ( dialog ) );
    dialog = ( Widget ) 0;
  }
  if ( ! dialog ) {
    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );
    dialog = Cre_NoCancel_Prompt_Dialog ( parent );
    XmAddWMProtocolCallback ( XtParent ( dialog ), WM_DELETE_WINDOW,
        ( XtCallbackProc ) Popup_PromptDialog_WM_CB,
        ( XtPointer ) dialog );
  }

  /***
  Static dialog now exists - create prompt
  ***/
  {
    XmString xstr = XmStringCreateLtoR ( primary_string, charset );
    XtVaSetValues ( dialog,
        XmNselectionLabelString,     xstr,
        NULL );
    XmStringFree ( xstr );
  }

  /***
  set the default text
  ***/
  {
    XmString xstr;

    if ( additional_string [ 0 ] == '\0' ) {
      xstr = XmStringCreateLtoR ( ( char * ) "", charset );
    }
    else {
      xstr = XmStringCreateLtoR ( ( char * ) additional_string, charset );
    }
    XtVaSetValues ( dialog, XmNtextString, xstr, NULL );
    XmStringFree ( xstr );
  }

  /***
  Prompt dialog ready
  ***/
  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Popup_SavePromptDialog ( parent )
Widget parent;
{
  static Widget dialog = ( Widget ) 0;
  static struct coord coord_data;

  coord_data.x = 0; /* not used */
  coord_data.y = 150;

  if ( ! dialog ) {
    /***
    create the dialog
    ***/
    dialog = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
    XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNautoUnmanage,           False,
        XmNwidth,                  250,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultButtonType,      XmNONE,
        NULL );

    /***
    add the callbacks
    ***/
    XtAddCallback ( dialog, XmNokCallback,
        ( XtCallbackProc ) Popup_SavePromptDialog_CB,
        ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( dialog, XmNcancelCallback,
        ( XtCallbackProc ) Popup_SavePromptDialog_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
    XtAddCallback ( dialog, XmNhelpCallback,
        ( XtCallbackProc ) Popup_PromptDialogHelp_CB, NULL );

    /***
    prompt
    ***/
    {
      XmString xstr =
          XmStringCreateLocalized ( "Directory to save development to:" );
      XtVaSetValues ( dialog,
          XmNselectionLabelString,     xstr,
          NULL );
      XmStringFree ( xstr );
    }
  }

  /***
  static dialog exists - set secondary_string (for help )
  ***/
  secondary_string [ 0 ] = '5';

  /***
  Prompt dialog ready
  ***/
  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Popup_FindPromptDialog ( parent )
Widget parent;
{
  static Widget dialog = ( Widget ) 0;
  static struct coord coord_data;

  coord_data.x = 0; /* not used */
  coord_data.y = 150;

  if ( ! dialog ) {
    /***
    create the dialog
    ***/
    dialog = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
    XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );
    XtVaSetValues ( dialog,
/*        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL, */
        XmNautoUnmanage,           False,
        XmNwidth,                  250,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultButtonType,      XmNONE,
        NULL );

    /***
    add the callbacks
    ***/
    XtAddCallback ( dialog, XmNokCallback,
        ( XtCallbackProc ) Popup_FindPromptDialog_CB,
        ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( dialog, XmNcancelCallback,
        ( XtCallbackProc ) Popup_FindPromptDialog_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
    XtAddCallback ( dialog, XmNhelpCallback,
        ( XtCallbackProc ) Popup_PromptDialogHelp_CB, NULL );

    /***
    prompt
    ***/
    {
      XmString xstr = XmStringCreateLocalized ( "Identifier(s) to find:" );
      XtVaSetValues ( dialog,
          XmNselectionLabelString,     xstr,
          NULL );
      XmStringFree ( xstr );
    }
  }

  /***
  static dialog exists - set secondary_string (for help )
  ***/
  secondary_string [ 0 ] = '3';

  XtManageChild ( dialog );

  /***
  position the dialog
  ***/
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Popup_RenamePromptDialog ( name )
char * name;
{
  static Widget dialog = ( Widget ) 0;
  static struct coord coord_data;
  static Atom WM_DELETE_WINDOW;

  coord_data.x = 0; /* not used */
  coord_data.y = 150;

  if ( ! dialog ) {

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    /***
    create the dialog
    ***/
    dialog = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
    XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNautoUnmanage,           False,
        XmNwidth,                  250,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultButtonType,      XmNONE,
        NULL );

    /***
    add the callbacks
    ***/
    XtAddCallback ( dialog, XmNokCallback,
        ( XtCallbackProc ) Popup_RenamePromptDialog_CB,
        ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( dialog, XmNcancelCallback,
        ( XtCallbackProc ) Popup_RenamePromptDialog_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
    XmAddWMProtocolCallback ( XtParent ( dialog ), WM_DELETE_WINDOW,
        ( XtCallbackProc ) Popup_RenamePromptDialog_CB,
        ( XtPointer ) dialog );
    XtAddCallback ( dialog, XmNhelpCallback,
        ( XtCallbackProc ) Popup_PromptDialogHelp_CB, NULL );
  }

  /***
  prompt
  ***/
  {
    char buf [ 100 ];
    XmString xstr;
    strcpy ( buf, "Rename " );
    strcat ( buf, name );
    strcat ( buf, " to:" );
    xstr = XmStringCreateLocalized ( buf );
    XtVaSetValues ( dialog, XmNselectionLabelString, xstr, NULL );
    XmStringFree ( xstr );
    xstr = XmStringCreateLocalized ( name );
    XtVaSetValues ( dialog, XmNtextString, xstr, NULL );
    XmStringFree ( xstr );
  }

  /***
  static dialog exists - set secondary_string (for help )
  ***/
  secondary_string [ 0 ] = '1';

  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Popup_LIBRenamePromptDialog ( parent, i )
Widget parent;
int i;
{
  static Widget dialog = ( Widget ) 0;
  static struct coord coord_data;

  coord_data.x = 0; /* not used */
  coord_data.y = 150;


  if ( ! dialog ) {
    /***
    create the dialog
    ***/
    dialog = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
    XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNautoUnmanage,           False,
        XmNwidth,                  250,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultButtonType,      XmNONE,
        NULL );

    /***
    add the callbacks
    ***/
    XtAddCallback ( dialog, XmNokCallback,
        ( XtCallbackProc ) Popup_LIBRenamePromptDialog_CB,
        ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( dialog, XmNcancelCallback,
        ( XtCallbackProc ) Popup_LIBRenamePromptDialog_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
    XtAddCallback ( dialog, XmNhelpCallback,
        ( XtCallbackProc ) Popup_PromptDialogHelp_CB, NULL );

   }

   /***
    static dialog exists - prompt
    ***/
  {
    char str [ 100 ];
    XmString xstr;

    strcpy ( str, "Value for \"Rename\" in " );
    strcat ( str, sel_str_arr [ i ] );
    strcat ( str, ":" );
    xstr = XmStringCreateLocalized ( str );
    XtVaSetValues ( dialog,
        XmNselectionLabelString,     xstr,
        NULL );
    XmStringFree ( xstr );
  }

  /***
  set secondary_string (for help )
  ***/
  secondary_string [ 0 ] = '2';

  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Popup_SaveAnimOutput_NewFile ()
{
  static Widget dialog = ( Widget ) 0;
  static struct coord coord_data;

  coord_data.x = 0; /* not used */
  coord_data.y = 150;

  if ( ! dialog ) {

    /***
    create the dialog
    ***/
    dialog = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
    XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNautoUnmanage,           False,
        XmNwidth,                  250,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultButtonType,      XmNONE,
        NULL );

    /***
    add the callbacks
    ***/
    XtAddCallback ( dialog, XmNokCallback,
        ( XtCallbackProc ) Popup_SaveAnimOutput_NewFile_CB,
        ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( dialog, XmNcancelCallback,
        ( XtCallbackProc ) Popup_SaveAnimOutput_NewFile_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
    XtAddCallback ( dialog, XmNhelpCallback,
        ( XtCallbackProc ) Popup_PromptDialogHelp_CB, NULL );

   }

   /***
    static dialog exists - prompt
    ***/
  {
    char str [ 100 ];
    XmString xstr;

    strcpy ( str, "Save output to (SRC) file:" );
    xstr = XmStringCreateLocalized ( str );
    XtVaSetValues ( dialog,
        XmNselectionLabelString,     xstr,
        NULL );
    XmStringFree ( xstr );
  }

  /***
  set secondary_string (for help )
  ***/
  secondary_string [ 0 ] = 'e';
  XtManageChild ( dialog );

  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Popup_EditAnimateFile ()
{
  void LoadAnimateFilesInto_sel_strs ();
  LoadAnimateFilesInto_sel_strs ( curr_obj, 1 );
  Popup_Sel_flag = edit_anm_exe_sel;
  Popup_SelOne_Dialog ( top_level, "Select ANIMATE Script" );
}

void
EditAnimateFile ( file, dont_allow_overwrite_flag )
char * file;
int dont_allow_overwrite_flag;
{
  FILE * fileptr;
  void Popup_EditAnimateFile ();
  char buf [ 150 ];  /* don't want the global buf */
  char* editorCommand;

  if ( dont_allow_overwrite_flag ) {
    fileptr = fopen ( file, "r" );
    if ( fileptr != NULL ) {
      fclose ( fileptr );
      sprintf ( primary_string, "  File \"%s\" already exists!  ", file );
      Popup_EditAnimateFile ();
      Popup_Minor_Err ( top_level, primary_string );
      return;
    }
  }

  fileptr = fopen ( file, "a" );
  if ( fileptr == NULL ) {
    sprintf ( primary_string, "  Can't open \"%s\" for writing!  ", file );
    Popup_EditAnimateFile ();
    Popup_Minor_Err ( top_level, primary_string );
    return;
  }
  fclose ( fileptr );

  Retrieve_String ( editor_str_num, buf );
  /* - use more intelligent command line caller for editors: */
  /*
  strcat ( buf, " " );
  strcat ( buf, file );
  strcat ( buf, " & \n echo $! > .Bed" );
  execute ( buf );
  */
  
  editorCommand=getEditorCommandLine(buf,file);
  strcpy(buf, editorCommand);
  free(editorCommand);
  strcat ( buf, " & \n echo $! > .Bed" );
  execute ( buf );
  
  ModifyAnmExeOpenFromBed ();
  strcpy ( sel_str_arr [ sel_arr_MAX ], file );
  Popup_CloseAnmExeFile ( top_level, 0 );
}

void
Popup_EditAnimateFile_NewFile ()
{
  /***
  We know it's a new file (still to be prompted for);
  ***/

  void LoadAnimateFilesInto_sel_strs ();
  LoadAnimateFilesInto_sel_strs ( curr_obj, 2 );
  if ( sel_arr_tot == 1 ) {                             /* no existing files */
    void Popup_EditAnimateFile_NewFile_Contd ();
    additional_string [ 0 ] = '\0';
    Popup_EditAnimateFile_NewFile_Contd ();
  }
  else {
    void LoadAnimateFilesInto_sel_strs ();
    Popup_Sel_flag = edit_anm_exe_new_from_old_sel;
    Popup_SelOne_Dialog ( top_level, "Select New Executable Script Initialisation" );
  }
}

void
Popup_EditAnimateFile_NewFile_Contd_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
  /***
  additional string contains the initialisation
  ***/

  char * text;
  int i, c;
  struct stat stat_buf;
  FILE * filein;
  FILE * fileout;
  int nl_count = 0;

  XtUnmanageChild ( prompt_dialog );
  XmUpdateDisplay ( prompt_dialog );

  if ( * ( int * ) client_data == OK_BUTTON ) {

    XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text );
    strcpy ( buf, text );
    XtFree ( text );

    if ( buf [ 0 ] == '\0' ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Filename empty!  " );
      return;
    }

    if ( strlen ( buf ) > 30 ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "Filname too long (max length 30)" );
      return;
    }

    if ( ! FormulaParses ( buf ) ) {
      XtManageChild ( prompt_dialog );
      XmUpdateDisplay ( prompt_dialog );
      Popup_Minor_Err ( top_level, "  Parse Error!  " );
      return;
    }

    sprintf ( str_buf, "SRC/%s.%s.anm", GetShortName ( curr_obj ), buf );
    if ( stat ( str_buf, &stat_buf ) == -1 ) { /* str_buf not exist */
      /***
      if str_buf already exists don't overwrite it;
      ***/
      if ( additional_string [ 0 ] != '\0' ) {
        i = 19;                      /* remove initial `SRC/Template from: ' */
        while ( additional_string [ i ] != '\0' ) {
          additional_string [ i - 19 ] = additional_string [ i ];
          i++;
        }
        additional_string [ i - 19 ] = '\0';
        sprintf ( buf, "SRC/%s", additional_string );
        filein = fopen ( buf, "r" );
        if ( filein == NULL ) {
           sprintf ( primary_string, "Can't open %s for reading", buf );
           Popup_Minor_Err ( top_level, primary_string );
           return;
	}
        fileout = fopen ( str_buf, "w" );
        if ( filein == NULL ) {
           sprintf ( primary_string, "Can't open %s for writing", str_buf );
           Popup_Minor_Err ( top_level, primary_string );
           return;
	}
        /***
        it's a .anm.file
        ***/
        /***
        discard first three lines of filein
        ***/
        c = getc ( filein );
        while ( ( c != EOF ) && ( nl_count < 3 ) ) {
          if ( c == '\n' ) nl_count++;
          c = getc ( filein );
        }
        i = 4;
        /***
        remove `SRC/' from str_buf
        ***/
        while ( str_buf [ i ] != '\0' ) {
          str_buf [ i - 4 ] = str_buf [ i ];
          i++;
        }
        str_buf [ i - 4 ] = '\0';
        fprintf ( fileout, "ANIMATE\n\n  %s\n", str_buf );
        while ( c != EOF ) {
          putc ( c, fileout );
          c = getc ( filein );
        }
        fclose ( filein );
        fclose ( fileout );
        sprintf ( buf, "SRC/%s", str_buf );
        strcpy ( str_buf, buf );
        EditAnimateFile ( str_buf, 0 ); /* 0 => allow overwrite - just cre! */
      }
      else {  /* so additional_string [ 0 ] == '\0' - Empty ANIMATE Script */
        int cc, nn;
        sprintf ( fifo_write_buf, "(%s|?", GetName ( curr_obj ) );
        card_sees_uses ( &nn, curr_obj );
        while ( nn ) {
          valOrd_sees_uses ( &cc, curr_obj, nn );
          strcat ( fifo_write_buf, "," );
          strcat ( fifo_write_buf, GetName ( cc ) );
          nn--;
        }
        strcat ( fifo_write_buf, "|" );
        /***
        remove `SRC/' from str_buf
        ***/
        i = 4;
        while ( str_buf [ i ] != '\0' ) {
          str_buf [ i - 4 ] = str_buf [ i ];
          i++;
        }
        str_buf [ i - 4 ] = '\0';
        strcat( fifo_write_buf, str_buf );
        strcat ( fifo_write_buf, "):" );
        CreNumInBuf ( fifo_write_buf, BT_ANM_EMPTY_SCRIPT );
        strcat ( fifo_write_buf, ":0" );
        InvokeB ( without_XTerm, 1 );
      }
    }  /* if ( stat ( str_buf, &stat */
    else {
      void Popup_EditAnimateFile ();
      sprintf ( primary_string, "  File \"%s\" already exists!  ", str_buf );
      Popup_EditAnimateFile ();
      Popup_Minor_Err ( top_level, primary_string );
      return;
    }
  }
  else {  /* Cancel */
    Popup_MainAnimatorMenu ( curr_obj );
  }
}

void
Popup_EditAnimateFile_NewFile_Contd ()
{
  /***
  We know it's a new file prompt for it!
  (additional string contains the iniitialisation - if any)
  ***/

  static Widget dialog = ( Widget ) 0;
  static struct coord coord_data;

  coord_data.x = 0; /* not used */
  coord_data.y = 150;

  if ( ! dialog ) {

    /***
    create the dialog
    ***/
    dialog = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
    XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNautoUnmanage,           False,
        XmNwidth,                  250,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultButtonType,      XmNONE,
        NULL );

    /***
    add the callbacks
    ***/
    XtAddCallback ( dialog, XmNokCallback,
        ( XtCallbackProc ) Popup_EditAnimateFile_NewFile_Contd_CB,
        ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( dialog, XmNcancelCallback,
        ( XtCallbackProc ) Popup_EditAnimateFile_NewFile_Contd_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
    XtAddCallback ( dialog, XmNhelpCallback,
        ( XtCallbackProc ) Popup_PromptDialogHelp_CB, NULL );
   }

   /***
    static dialog exists - prompt
    ***/
  {
    char str [ 100 ];
    XmString xstr;

    strcpy ( str, "Name of new ANIMATE Script:" );
    xstr = XmStringCreateLocalized ( str );
    XtVaSetValues ( dialog,
        XmNselectionLabelString,     xstr,
        NULL );
    XmStringFree ( xstr );
  }

  /***
  set secondary_string (for help )
  ***/
  secondary_string [ 0 ] = 'g';
  XtManageChild ( dialog );

  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Popup_SaveAnimOutput ()
{
  void LoadAnimatorFilesInto_sel_strs ();
  LoadAnimatorFilesInto_sel_strs ( "New output file", "out" );
  Popup_Sel_flag = save_anm_output_sel;
  Popup_SelOne_Dialog ( top_level, "Select Output File" );
}

void
Popup_SaveAnimateFile_NewFile ()
{
  static Widget dialog = ( Widget ) 0;
  static struct coord coord_data;

  coord_data.x = 0; /* not used */
  coord_data.y = 150;

  if ( ! dialog ) {

    /***
    create the dialog
    ***/
    dialog = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
    XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNautoUnmanage,           False,
        XmNwidth,                  250,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultButtonType,      XmNONE,
        NULL );

    /***
    add the callbacks
    ***/
    XtAddCallback ( dialog, XmNokCallback,
        ( XtCallbackProc ) Popup_SaveAnimateFile_NewFile_CB,
        ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( dialog, XmNcancelCallback,
        ( XtCallbackProc ) Popup_SaveAnimateFile_NewFile_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
    XtAddCallback ( dialog, XmNhelpCallback,
        ( XtCallbackProc ) Popup_PromptDialogHelp_CB, NULL );

   }

   /***
    static dialog exists - prompt
    ***/
  {
    char str [ 100 ];
    XmString xstr;

    strcpy ( str, "Save ANIMATE Script to (SRC) file:" );
    xstr = XmStringCreateLocalized ( str );
    XtVaSetValues ( dialog,
        XmNselectionLabelString,     xstr,
        NULL );
    XmStringFree ( xstr );
  }

  /***
  set secondary_string (for help )
  ***/
  secondary_string [ 0 ] = 'f';
  XtManageChild ( dialog );

  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Popup_SaveAnimateFile ( parent, title )
Widget parent;
char * title;
{
  void LoadAnimatorFilesInto_sel_strs ();

  LoadAnimatorFilesInto_sel_strs ( "New ANIMATE Script", "anm" );
  Popup_Sel_flag = save_anm_animate_sel;
  Popup_SelOne_Dialog ( top_level, "Select ANIMATE Script" );
}

void
Popup_CleanAnimFiles ( parent, title )
Widget parent;
char * title;
{
  void LoadAnimatorFilesToCleanInto_sel_strs ();
  void Animate_Utilities ();
  void Popup_MainAnimatorMenu ();

  LoadAnimatorFilesToCleanInto_sel_strs ();
  if ( sel_arr_tot ) {
    Popup_Sel_flag = anm_clean_files_sel;
    Popup_Sel_Dialog ( top_level, "Select Animator Files to Remove" );
  }
  else {
    if   ( curr_env == anm_env ) Animate_Utilities ( top_level );
    else                         Popup_MainAnimatorMenu ( curr_obj );
    Popup_Info ( " No saved files to clean " );
  }
}

void
Popup_IntroduceNewNamePromptDialog ( parent, ext )
Widget parent;
int ext;
{
  static Widget dialog = ( Widget ) 0;
  XmString xstr1, xstr2;
  static struct coord coord_data;

  coord_data.x = 0; /* not used */
  coord_data.y = 150;

  if ( ! dialog ) {
    /***
    create the dialog
    ***/
    dialog = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
    XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNautoUnmanage,           False,
        XmNwidth,                  250,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultButtonType,      XmNONE,
        NULL );

    /***
    add the callbacks
    ***/
    XtAddCallback ( dialog, XmNokCallback,
        ( XtCallbackProc ) Popup_IntroduceNewNamePromptDialog_CB,
        ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( dialog, XmNcancelCallback,
        ( XtCallbackProc ) Popup_IntroduceNewNamePromptDialog_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
    XtAddCallback ( dialog, XmNhelpCallback,
        ( XtCallbackProc ) Popup_PromptDialogHelp_CB, NULL );

  }

  /***
  static dialog exists - set prompt (and secondary_string for help)
  ***/
  secondary_string [ 0 ] = '1';
  switch ( ext ) {
    case 0:
      xstr1 = XmStringCreateLocalized ( "Machine name:" );
      break;
    case 1:
      xstr1 = XmStringCreateLocalized ( "Refinement name:" );
      break;
    case 3:
      xstr1 = XmStringCreateLocalized ( "Implementation name:" );
      break;
    case 5:
      xstr1 = XmStringCreateLocalized ( "Base name:" );
      secondary_string [ 0 ] = '4';
      break;
    case 6:
      xstr1 = XmStringCreateLocalized ( "Enumeration name:" );
      break;
    case 8:
      xstr1 = XmStringCreateLocalized ( "Interface name:" );
      break;
    case 10:
      xstr1 = XmStringCreateLocalized ( "Document name:" );
      break;

   }

   XtVaSetValues ( dialog, XmNselectionLabelString, xstr1, NULL );
   XmStringFree ( xstr1 );

  /***
  set option
  ***/
  option = ext;

  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

/***********************************************************************
************************************************************************
                         Question dialogs
************************************************************************
***********************************************************************/

/**************************************************
          Callback routines
***************************************************/

/*
void
Quit_CB ( dialog, client_data  )
Widget dialog;
XtPointer client_data;
{
  XtPopdown ( XtParent ( dialog ) );
  XmUpdateDisplay ( XtParent ( dialog ) );
  void CloseAllOpenFilesAndQuit ();

  /???
  if OK - quit!
  ???/
  if ( * ( int * ) client_data == OK_BUTTON ) {
    close_all_quit_count = 1;
    CloseAllOpenFilesAndQuit ();
  }
}
*/


void
Popup_QuestionHelp_CB  ()
{
  struct help_struct help_data;

  help_data.type   = DIALOG_HELP;
  help_data.width  = 350;
  help_data.height = 130;
  help_data.text   = ( ( char * ) secondary_string );

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
}


/************************
  The question dialogs
************************/



/*
void
Popup_Quit ()
{
  static Widget dialog = ( Widget ) 0;

  if ( ! dialog ) {
    XmString xstr;
    dialog = XmCreateQuestionDialog( top_frame_form, "QuitDialog", NULL, 0 );
    xstr = XmStringCreateLocalized ( "      Exit B-Toolkit?      " );
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNautoUnmanage,           False,
        XmNdefaultButtonType,      XmNONE,
        XmNmessageString,          xstr,
        XmNsymbolPixmap,           B_framed_pixmap_gray94,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        NULL );
    XmStringFree ( xstr );
    XtUnmanageChild ( XmMessageBoxGetChild ( dialog, XmDIALOG_HELP_BUTTON ) );
    XtVaSetValues ( XmMessageBoxGetChild ( dialog, XmDIALOG_OK_BUTTON ),
        XmNdefaultButtonShadowThickness,  1,
        XmNnavigationType,       XmTAB_GROUP,
        XmNhighlightThickness,   1,
        NULL );
    XtVaSetValues ( XmMessageBoxGetChild ( dialog, XmDIALOG_CANCEL_BUTTON ),
        XmNdefaultButtonShadowThickness,  1,
        XmNnavigationType,       XmTAB_GROUP,
        XmNhighlightThickness,   1,
        NULL );
    XtAddCallback ( dialog, XmNokCallback,
              ( XtCallbackProc ) Quit_CB,
              ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( dialog, XmNcancelCallback,
              ( XtCallbackProc ) Quit_CB,
              ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
  }

  if ( bell_option ) XBell ( display, 10 );

  /???
  dialog now exists
  ???/
  XtManageChild ( dialog );

  XmProcessTraversal ( XmMessageBoxGetChild ( dialog, XmDIALOG_CANCEL_BUTTON ),
                                          XmTRAVERSE_CURRENT );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );

}
*/



void
Popup_ResetAll ()
{
  static Widget dialog = ( Widget ) 0;
  static struct coord coord_data;
  static Atom WM_DELETE_WINDOW;

  if ( ! dialog ) {
    XmString xstr;

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    dialog = XmCreateQuestionDialog ( top_level, "WarningDialog", NULL, 0 );

    coord_data.x = 0; /* not used */
    coord_data.y = /* 60; */ 150;

    XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );

    xstr = XmStringCreateLocalized ( "   Reset all constructs?          " );
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNautoUnmanage,           False,
        XmNdefaultButtonType,      XmDIALOG_OK_BUTTON,
        XmNdefaultPosition,        False,
        XmNmessageString,          xstr,
        XmNsymbolPixmap,           B_framed_pixmap_gray94,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        NULL );
    XmStringFree ( xstr );
    XtAddCallback ( dialog, XmNokCallback,
              ( XtCallbackProc ) ResetAll_CB,
              ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( dialog, XmNcancelCallback,
              ( XtCallbackProc ) ResetAll_CB,
              ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
    XmAddWMProtocolCallback ( XtParent ( dialog ), WM_DELETE_WINDOW,
              ( XtCallbackProc ) ResetAll_CB,
              ( XtPointer ) NULL );
    XtAddCallback ( dialog, XmNhelpCallback,
              ( XtCallbackProc ) ResetAll_CB,
              ( XtPointer ) & c_arr [ HELP_BUTTON ] );
  }

  if ( bell_option ) XBell ( display, 10 );

  /***
  dialog now exists
  ***/
  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
Popup_ConfirmDialog ( parent )
Widget parent;
{
  Widget dialog;
  XmString msg, yes, no;
  Atom WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );
  static struct coord coord_data;
  coord_data.x = 0; /* not used */
  coord_data.y = 150;

  dialog = XmCreateQuestionDialog( parent, "QuestionDialog", NULL, 0 );
  XtAddCallback ( XtParent ( dialog ), XmNpopupCallback,
      ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
      ( XtPointer ) & coord_data );
  yes = XmStringCreateLocalized ( "Yes" );
  no  = XmStringCreateLocalized ( "No" );
  XtVaSetValues ( dialog,
      XmNautoUnmanage,           False,
      XmNdefaultButtonType,      XmNONE,
      XmNokLabelString,          yes,
      XmNcancelLabelString,      no,
      XmNsymbolPixmap,           B_framed_pixmap_gray94,
      XmNmarginWidth,            10,
      XmNmarginHeight,           5,
      NULL );
  XmStringFree ( yes );
  XmStringFree ( no );
  XtAddCallback ( dialog, XmNokCallback,
      ( XtCallbackProc ) Popup_ConfirmDialog_CB, 
      ( XtPointer ) & c_arr [ OK_BUTTON ] );
  XtAddCallback ( dialog, XmNcancelCallback,
      ( XtCallbackProc ) Popup_ConfirmDialog_CB,
      ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
  XmAddWMProtocolCallback ( XtParent ( dialog ), WM_DELETE_WINDOW,
      ( XtCallbackProc ) Popup_ConfirmDialog_CB,
      ( XtPointer ) NULL );
  /***
  Check for help text
  ***/
  if ( secondary_string [ 0 ] == '0' ) {
    XtUnmanageChild ( XmMessageBoxGetChild ( dialog, XmDIALOG_HELP_BUTTON ) );
  }
  else {
    XtAddCallback ( dialog, XmNhelpCallback,
                     ( XtCallbackProc ) Popup_QuestionHelp_CB,
                     ( XtPointer ) NULL );
    XtVaSetValues ( XmMessageBoxGetChild ( dialog, XmDIALOG_HELP_BUTTON ),
       XmNdefaultButton,                 False,
       XmNdefaultButtonShadowThickness,  1,
       XmNhighlightThickness,            1,
       XmNnavigationType,                XmTAB_GROUP,
       NULL);
  }

  XtVaSetValues ( XmMessageBoxGetChild ( dialog, XmDIALOG_OK_BUTTON ),
     XmNdefaultButton,                 False,
     XmNdefaultButtonShadowThickness,  1,
     XmNhighlightThickness,            1,
     XmNnavigationType,                XmTAB_GROUP,
     NULL);

  XtVaSetValues ( XmMessageBoxGetChild ( dialog, XmDIALOG_CANCEL_BUTTON ),
     XmNdefaultButton,                 False,
     XmNdefaultButtonShadowThickness,  1,
     XmNhighlightThickness,            1,
     XmNnavigationType,                XmTAB_GROUP,
     NULL);

  /***
  change labels & set text
  ***/
  msg = XmStringCreateLtoR ( primary_string, charset );
  XtVaSetValues ( dialog,
      XmNmessageString,          msg,
      NULL );
  XmStringFree ( msg );

  /***
  MODELESS if anm or ipr
  ***/
  if ( ( curr_env == anm_env     ) ||
       ( curr_env == ipr_pob_env ) ||
       ( curr_env == ipr_lem_env )    ) {
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        NULL );
  }
  else {
    XtVaSetValues ( dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        NULL );
  }

  XmProcessTraversal ( XmMessageBoxGetChild ( dialog, XmDIALOG_OK_BUTTON ),
                                                          XmTRAVERSE_CURRENT );

  /***
  Question dialog ready
  ***/
  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}




/***********************************************************************
************************************************************************
                         Selection dialogs
************************************************************************
***********************************************************************/

/**************************************************
     Creation of basic Sel dialog
***************************************************/

void
Cre_Sel_Dialog ( parent, dialog, dialog_form,
                 radio_box_scroll, radio_box,
                 B_logo,
                 sep,
                 och_form, och_o, och_c, och_h, och_a, och_n,
                 help_data, label,
                 SelLarge_flag,
		 WM_DELETE_WINDOW,
                 no_cancel_flag )

                 Widget * parent;
                 Widget * dialog;
                 Widget * dialog_form;
                 Widget * radio_box_scroll;
                 Widget * radio_box;
                 Widget * B_logo;
                 Widget * sep;
                 Widget * och_form;
                 Widget * och_o;
                 Widget * och_c;
                 Widget * och_h;
                 Widget * och_a;
                 Widget * och_n;
                 struct help_struct * help_data;
                 Widget * label;
                 int SelLarge_flag;
                 Atom * WM_DELETE_WINDOW;
                 int no_cancel_flag;
{
  XmString xstr;
  Arg args [ 2 ];
  static struct coord coord_data;

  coord_data.x = 0; /* not used */
  coord_data.y = 75;

  * WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

  /***
  create the dialog
  ***/
  XtSetArg ( args [ 0 ], XmNresizeWidth, True );
  * dialog = XmCreateDialogShell ( top_frame_form, "SelDialog", args, 1 );

  XtAddCallback ( * dialog, XmNpopupCallback,
      ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
      ( XtPointer ) & coord_data );

  /***
  create Control Area Form
  ***/
  * dialog_form = XtVaCreateWidget ( "SelDialog",
      xmFormWidgetClass,         * dialog,
      XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
      XmNtraversalOn,            True,
      XmNautoUnmanage,           False,
      XmNuserData,               ( XtPointer ) & c_arr [ 0 ],
      NULL );

  /***
  create B logo
  ***/
  * B_logo = XtVaCreateWidget ( "SelDialog", 
      xmPushButtonWidgetClass,    * dialog_form,
      XmNtopAttachment,           XmATTACH_FORM,
      XmNtopOffset,               10,
      XmNleftAttachment,          XmATTACH_FORM,
      XmNleftOffset,              10,
      XmNlabelType,               XmPIXMAP,
      XmNlabelPixmap,             B_framed_pixmap_gray94,
      XmNshadowThickness,         0,
      XmNmarginWidth,             0,
      XmNmarginHeight,            0,
      XmNtraversalOn,             False,
      NULL );

  XtAddCallback ( * B_logo, XmNactivateCallback,
                                    ( XtCallbackProc ) B_info_CB, NULL );

  /***
  create the (initial dummy) label
  ***/
  xstr = XmStringCreateLtoR ( "dummy string", charset );
  * label = XtVaCreateWidget ( "Label", 
      xmLabelWidgetClass,        * dialog_form,
      XmNtopAttachment,          XmATTACH_FORM,
      XmNtopOffset,              12,
      XmNleftAttachment,         XmATTACH_WIDGET,
      XmNleftWidget,             * B_logo,
      XmNleftOffset,             1,
      XmNrightAttachment,        XmATTACH_FORM,
      XmNrightOffset,            36,
      XmNlabelString,            xstr,
      XmNmarginWidth,            10,
      XmNmarginHeight,           10,
      XmNtraversalOn,            False,
      NULL );
  XmStringFree ( xstr );

  /***
  create separator
  ***/
  if ( SelLarge_flag == SelLarge_flag_YES ) {
    * sep = XtVaCreateManagedWidget ( "SelDialog",
        xmSeparatorGadgetClass,  * dialog_form,
        XmNleftAttachment,       XmATTACH_FORM,
        XmNleftOffset,           0,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNrightOffset,          0,
        XmNbottomAttachment,     XmATTACH_FORM,
        XmNbottomOffset,         48,
        XmNwidth,                395,
        NULL );
  }
  else if ( SelLarge_flag == SelLarge_flag_EXTRA ) {
    * sep = XtVaCreateManagedWidget ( "SelDialog",
        xmSeparatorGadgetClass,  * dialog_form,
        XmNleftAttachment,       XmATTACH_FORM,
        XmNleftOffset,           0,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNrightOffset,          0,
        XmNbottomAttachment,     XmATTACH_FORM,
        XmNbottomOffset,         48,
        XmNtopAttachment,       XmATTACH_FORM,
        XmNtopOffset,            600,
        XmNwidth,                450,
        NULL );
  }
  else {
    * sep = XtVaCreateManagedWidget ( "SelDialog",
        xmSeparatorGadgetClass,  * dialog_form,
        XmNleftAttachment,       XmATTACH_FORM,
        XmNleftOffset,           0,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNrightOffset,          0,
        XmNbottomAttachment,     XmATTACH_FORM,
        XmNbottomOffset,         48,
        XmNwidth,                375,
        NULL );
  }

  /***
  create Scroll for RowCol in Form
  ***/
  * radio_box_scroll = XtVaCreateWidget ( "SelDialog",
      xmScrolledWindowWidgetClass,    * dialog_form,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   * label,
      XmNtopOffset,                   10,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  15,
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                * sep,
      XmNbottomOffset,                10,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNspacing,                     0,
      NULL );

  /***
  create Action Area Form
  ***/
  * och_form = XtVaCreateWidget ( "ButtonLabel",
      xmFormWidgetClass,       * dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         5,
      NULL );

  /***
  create OK button
  ***/
  * och_o = XtVaCreateManagedWidget ( "OK", 
      xmPushButtonGadgetClass, * och_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           5,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( * och_o, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Sel_Dialog_CB,
      ( XtPointer ) & c_arr [ OK_BUTTON ] );

  XmProcessTraversal ( * och_o, XmTRAVERSE_CURRENT );

  /***
  create Cancel button
  ***/
  * och_c = XtVaCreateManagedWidget ( "Cancel", 
      xmPushButtonGadgetClass, * och_form,
      XmNleftAttachment,       XmATTACH_WIDGET,
      XmNleftWidget,           * och_o,
      XmNleftOffset,           5,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( * och_c, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Sel_Dialog_CB,
      ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
  if ( no_cancel_flag ) {
    void Popup_Sel_Dialog_WM_CB ();
    XmAddWMProtocolCallback ( * dialog, * WM_DELETE_WINDOW,
        ( XtCallbackProc ) Popup_Sel_Dialog_WM_CB,
        ( XtPointer ) * dialog_form );
  }
  else {
    XmAddWMProtocolCallback ( * dialog, * WM_DELETE_WINDOW,
        ( XtCallbackProc ) Popup_Sel_Dialog_CB,
        ( XtPointer ) * dialog_form );
  }
  
  /***
  create All button
  ***/
  * och_a = XtVaCreateManagedWidget ( "All", 
      xmPushButtonGadgetClass, * och_form,
      XmNleftAttachment,       XmATTACH_WIDGET,
      XmNleftWidget,           * och_c,
      XmNleftOffset,           5,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( * och_a, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Sel_Dialog_CB,
      ( XtPointer ) & c_arr [ ALL_BUTTON ] );
  XtSetSensitive ( * och_a, False );

  /***
  create None button
  ***/
  * och_n = XtVaCreateManagedWidget ( "None", 
      xmPushButtonGadgetClass, * och_form,
      XmNleftAttachment,       XmATTACH_WIDGET,
      XmNleftWidget,           * och_a,
      XmNleftOffset,           1,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( * och_n, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Sel_Dialog_CB,
      ( XtPointer ) & c_arr [ NONE_BUTTON ] );
  XtSetSensitive ( * och_n, False );

  /***
  create Help button
  ***/
  * och_h = XtVaCreateManagedWidget ( "Help", 
      xmPushButtonGadgetClass, * och_form,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          8,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( * och_h, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Help_CB,
      ( XtPointer ) help_data );

}

void
Cre_Selection_Sel_Dialog ( parent, dialog, dialog_form,
                           radio_box_scroll, radio_box,
                           B_logo,
                           sep,
                           och_form, och_o, och_f, och_c, och_h,
                           help_data, label,
                           sel_label, sel_text,
		           WM_DELETE_WINDOW )

                           Widget * parent;
                           Widget * dialog;
                           Widget * dialog_form;
                           Widget * radio_box_scroll;
                           Widget * radio_box;
                           Widget * B_logo;
                           Widget * sep;
                           Widget * och_form;
                           Widget * och_o;
                           Widget * och_f;
                           Widget * och_c;
                           Widget * och_h;
                           struct help_struct * help_data;
                           Widget * label;
                           Widget * sel_label;
                           Widget * sel_text;
                           Atom * WM_DELETE_WINDOW;
{
  XmString xstr;

  * WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

  /***
  create the dialog
  ***/
  * dialog = XmCreateDialogShell ( top_frame_form, "SelDialog", NULL, 0 );

  /***
  create Control Area Form
  ***/
  * dialog_form = XtVaCreateWidget ( "SelDialog",
      xmFormWidgetClass,         * dialog,
      XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
      XmNtraversalOn,            True,
      XmNautoUnmanage,           False,
      XmNuserData,               ( XtPointer ) & c_arr [ 0 ],
      NULL );

  /***
  create B logo
  ***/
  * B_logo = XtVaCreateWidget ( "SelDialog", 
      xmPushButtonWidgetClass,    * dialog_form,
      XmNtopAttachment,           XmATTACH_FORM,
      XmNtopOffset,               10,
      XmNleftAttachment,          XmATTACH_FORM,
      XmNleftOffset,              10,
      XmNlabelType,               XmPIXMAP,
      XmNlabelPixmap,             B_framed_pixmap_gray94,
      XmNshadowThickness,         0,
      XmNmarginWidth,             0,
      XmNmarginHeight,            0,
      XmNtraversalOn,             False,
      NULL );

  XtAddCallback ( * B_logo, XmNactivateCallback,
                                    ( XtCallbackProc ) B_info_CB, NULL );

  /***
  create the (initial dummy) label
  ***/
  xstr = XmStringCreateLtoR ( "dummy string", charset );
  * label = XtVaCreateWidget ( "Label", 
      xmLabelWidgetClass,        * dialog_form,
      XmNtopAttachment,          XmATTACH_FORM,
      XmNtopOffset,              12,
      XmNleftAttachment,         XmATTACH_WIDGET,
      XmNleftWidget,             * B_logo,
      XmNleftOffset,             1,
      XmNrightAttachment,        XmATTACH_FORM,
      XmNrightOffset,            36,
      XmNlabelString,            xstr,
      XmNmarginWidth,            10,
      XmNmarginHeight,           10,
      XmNtraversalOn,            False,
      NULL );
  XmStringFree ( xstr );

  /***
  create separator
  ***/
  * sep = XtVaCreateManagedWidget ( "SelDialog",
      xmSeparatorGadgetClass,  * dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           0,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          0,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         48,
      XmNwidth,                475,
      NULL );

  /***
  create the Current Selection text
  ***/
  * sel_text = XtVaCreateWidget ( "SelDialog",
      xmTextFieldWidgetClass,    * dialog_form,
      XmNrightAttachment,        XmATTACH_FORM,
      XmNrightOffset,            10,
      XmNleftAttachment,         XmATTACH_FORM,
      XmNleftOffset,             10,
      XmNbottomAttachment,       XmATTACH_WIDGET,
      XmNbottomWidget,           * sep,
      XmNbottomOffset,           20,
      NULL );

  global_widget = * sel_text;

  XtAddCallback ( * sel_text, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Selection_Sel_Text_Dialog_CB,
      ( XtPointer ) sel_text );

  /***
  create the Current Selection label
  ***/
  xstr = XmStringCreateLtoR ( "Current Selection", charset );
  * sel_label = XtVaCreateWidget ( "Label", 
      xmLabelWidgetClass,        * dialog_form,
      XmNleftAttachment,         XmATTACH_FORM,
      XmNrightAttachment,        XmATTACH_FORM,
      XmNbottomAttachment,       XmATTACH_WIDGET,
      XmNbottomWidget,           * sel_text,
      XmNbottomOffset,           5,
      XmNlabelString,            xstr,
      XmNmarginWidth,            10,
      XmNmarginHeight,           10,
      NULL );
  XmStringFree ( xstr );

  /***
  create Scroll for RowCol in Form
  ***/
  * radio_box_scroll = XtVaCreateWidget ( "SelDialog",
      xmScrolledWindowWidgetClass,    * dialog_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   /* 35, */ 50,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  15,
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                * sel_label,
      XmNbottomOffset,                2,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
/*
      XmNwidth,                       175,
      XmNheight,                      300,
*/
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNspacing,                     0,
      NULL );

  /***
  create Action Area Form
  ***/
  * och_form = XtVaCreateWidget ( "ButtonLabel",
      xmFormWidgetClass,       * dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         5,
      NULL );

  /***
  create OK button
  ***/
  * och_o = XtVaCreateManagedWidget ( "OK", 
      xmPushButtonGadgetClass, * och_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           12,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( * och_o, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Selection_Sel_Dialog_CB,
      ( XtPointer ) & c_arr [ OK_BUTTON ] );

  XmProcessTraversal ( * och_o, XmTRAVERSE_CURRENT );

  /***
  create Filter button
  ***/
  * och_f = XtVaCreateManagedWidget ( "Filter", 
      xmPushButtonGadgetClass, * och_form,
      XmNleftAttachment,       XmATTACH_WIDGET,
      XmNleftWidget,           * och_o,
      XmNleftOffset,           15,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( * och_f, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Selection_Sel_Dialog_CB,
      ( XtPointer ) & c_arr [ FILTER_BUTTON ] );
  
  /***
  create Cancel button
  ***/
  * och_c = XtVaCreateManagedWidget ( "Cancel", 
      xmPushButtonGadgetClass, * och_form,
      XmNleftAttachment,       XmATTACH_WIDGET,
      XmNleftWidget,           * och_f,
      XmNleftOffset,           15,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( * och_c, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Selection_Sel_Dialog_CB,
      ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
  XmAddWMProtocolCallback ( * dialog, * WM_DELETE_WINDOW,
      ( XtCallbackProc ) Popup_Selection_Sel_Dialog_CB,
      ( XtPointer ) * dialog_form );
  
  /***
  create Help button
  ***/
  * och_h = XtVaCreateManagedWidget ( "Help", 
      xmPushButtonGadgetClass, * och_form,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          12,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( * och_h, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Help_CB,
      ( XtPointer ) help_data );
}

/**************************************************
     Re-creation of basic Sel dialog
***************************************************/

void
Re_Cre_Sel_Dialog ( dialog, dialog_form, label,
                   radio_box_scroll, radio_box,
                   B_logo, 
                   sep,
                   SelOne_flagged_flag, och_a, och_n,
                   title,
                   GetBsel_NLallowed_flag,
                   GetBsel_flag )

                   Widget *  dialog;
                   Widget *  dialog_form;
                   Widget *  label;
                   Widget *  radio_box_scroll;
                   Widget *  radio_box;
                   Widget *  B_logo;
                   Widget *  sep;
                   int SelOne_flagged_flag;
                   Widget *  och_a;
                   Widget *  och_n;
                   char * title;
                   int GetBsel_NLallowed_flag;
                   int GetBsel_flag;
{
  XmString xstr;
  int height, i;

  /***
  set SelOne_flagged (& second_visit)
  ***/
  SelOne_flagged = SelOne_flagged_flag;
  if ( SelOne_flagged ) {
    second_visit = 0;
  }
  else {
    second_visit = 1;        /* WHY ??????????? */
  }

  /***
  destroy previous radio_box_scroll & label
  ***/
  XtDestroyWidget ( * label );
  XtDestroyWidget ( * radio_box_scroll );

  /***
  recreate label
  ***/
  xstr = XmStringCreateLtoR ( title, charset );
  * label = XtVaCreateWidget ( "Label", 
      xmLabelWidgetClass,             * dialog_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   12,
      XmNleftAttachment,              XmATTACH_WIDGET,
      XmNleftWidget,                  * B_logo,
      XmNleftOffset,                  1,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 36,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 10,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );
  XmStringFree ( xstr );

  /***
  load sel_str_arr from Bsel if not commit_all_edit_selection etc.
  ***/
  if      ( GetBsel_NLallowed_flag )                  GetBsel_NLallowed ();
  else if ( GetBsel_flag )                            GetBsel ();
  else if ( Popup_Sel_flag == interprover_selection ) GetBsel ();
  else if ( ! Popup_Sel_flag )                        GetBsel ();

  /***
  calculate height
  ***/
  height = 20 * sel_arr_tot + 17;
  if ( height > 417 ) height = 417;

/***
printf ( "calculated height %d\n" , height );
***/
  height = 250;

  /***
  recreate Scroll for RowCol in Form
  ***/
  * radio_box_scroll = XtVaCreateWidget ( "SelDialog",
      xmScrolledWindowWidgetClass,    * dialog_form,
/*
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   /? 35, ?/ 50,
*/
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   * label,
      XmNtopOffset,                   5,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  15,
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                * sep,
      XmNbottomOffset,                10,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNwidth,                       /* 175, */ 170,
      XmNheight,                      height,
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNspacing,                     0,
      NULL );

  /***
  create RadioBox/RowCol in Scroll
  ***/
  if ( SelOne_flagged_flag ) {
    * radio_box = XmCreateRadioBox ( * radio_box_scroll,
          "SelDialog",
          NULL,
          0 );
    XtVaSetValues ( * radio_box,
          XmNorientation,            XmVERTICAL,
          XmNisHomogeneous,          False,
          XmNspacing,                0,
          NULL );
  }
  else {
    * radio_box = XtVaCreateWidget ( "SelDialog", 
          xmRowColumnWidgetClass,    * radio_box_scroll,
          XmNorientation,            XmVERTICAL,
          XmNspacing,                0,
          NULL );
    XtSetSensitive ( * och_a, True );
    XtSetSensitive ( * och_n, True );
  }

  /***
  recreate buttons in RadioBox/RowCol
  ***/
  for ( i = 0; i < sel_arr_tot; i++ ) {
    xstr = XmStringCreateLtoR ( sel_str_arr [ i ], charset );
    sel_arr_but [ i ] = XtVaCreateManagedWidget ( "SelDialog",
        xmToggleButtonGadgetClass,     * radio_box,
/*
        XmNspacing,                    2,
*/
        XmNlabelString,                xstr,
        XmNhighlightThickness,         1,
        XmNnavigationType,             XmTAB_GROUP,
        NULL );
    XmStringFree ( xstr );
    XtAddCallback ( sel_arr_but [ i ], XmNvalueChangedCallback,
        ( XtCallbackProc ) ToggleBox_CB,
        ( XtPointer ) & c_arr [ i ] );

    if ( ! SelOne_flagged ) {
      /***
      not SelOne: select all if commit_all_edit_selection etc, else deselect
      ***/
      if ( Popup_Sel_flag == commit_all_edit_selection        ||
           Popup_Sel_flag == close_all_edit_selection         ||
           Popup_Sel_flag == remake_jobs_selection            ||
           Popup_Sel_flag == analyse_generate_jobs_selection  ||
           Popup_Sel_flag == update_from_SRC_sel              ||
           Popup_Sel_flag == commit_all_remake_edit_selection /* ||
	   Popup_Sel_flag == introduce_SRC_selection */            ) { 
        XmToggleButtonSetState ( sel_arr_but [ i ], True, False );
        sel_arr_tog [ i ] = 1;
      }
      else {
        sel_arr_tog [ i ] = 0;
      }
    }
    else {
      /***
      SelOne: select last if rsl_selection else select first
      ***/
      if ( Popup_Sel_flag != rsl_selection ) {
        if ( i == 0 ) {
          XmToggleButtonSetState ( sel_arr_but [ i ], True, False );
          sel_arr_tog [ i ] = 1;
	}
        else {
          sel_arr_tog [ i ] = 0;
	}
      }
      else {
        if ( i == sel_arr_tot - 1 ) {
          XmToggleButtonSetState ( sel_arr_but [ i ], True, False );
          sel_arr_tog [ i ] = 1;
	}
        else {
          sel_arr_tog [ i ] = 0;
        }
      }
    }
  }

/***
  XtVaSetValues ( * dialog_form,
      XmNheight,                      height+50,
      NULL );
  XmUpdateDisplay ( * dialog_form );
***/

/***
  {
    Dimension x;
    XtVaGetValues ( * dialog_form,
      XmNheight,                      & x,
      NULL );
    printf ( " dialog_form height %d\n", x ); 
    XtVaGetValues ( * radio_box_scroll,
      XmNheight,                      & x,
      NULL );
    printf ( " radio_box_scroll height %d\n", x ); 
  }
***/

/*
print_XmNtraversalOn_value ( "radio_box_scroll", * radio_box_scroll );
print_XmNtraversalOn_value ( "B_logo", * B_logo );
print_XmNtraversalOn_value ( "sep", * sep );
print_XmNtraversalOn_value ( "label", * label );
print_XmNtraversalOn_value ( "radio_box", * radio_box );
*/

}


void
Re_Cre_Selection_Sel_Dialog ( dialog, dialog_form, label,
                              radio_box_scroll, radio_box,
                              B_logo,
                              sel_label, sel_text,
                              title )

                              Widget *  dialog;
                              Widget *  dialog_form;
                              Widget *  label;
                              Widget *  radio_box_scroll;
                              Widget *  radio_box;
                              Widget *  B_logo;
                              Widget *  sel_label;
                              Widget *  sel_text;
                              char * title;
{
  Widget but;
  XmString xstr;
  int height, i;

  second_visit = 0;

  /***
  destroy previous radio_box_scroll & label
  ***/
  XtDestroyWidget ( * label );
  XtDestroyWidget ( * radio_box_scroll );

  /***
  recreate label
  ***/
  sprintf ( buf, "Selection Directory: %s", title );
  xstr = XmStringCreateLtoR ( buf, charset );
  * label = XtVaCreateWidget ( "Label", 
      xmLabelWidgetClass,             * dialog_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   12,
      XmNleftAttachment,              XmATTACH_WIDGET,
      XmNleftWidget,                  * B_logo,
      XmNleftOffset,                  1,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 36,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 10,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );
  XmStringFree ( xstr );

  /***
  calculate height
  ***/
  height = 20 * sel_arr_tot + 17;
  if ( height > 417 ) height = 417;

/***
printf ( "calculated height %d\n" , height );
***/
  height = 250;

  /***
  recreate Scroll for RowCol in Form
  ***/
  * radio_box_scroll = XtVaCreateWidget ( "SelDialog",
      xmScrolledWindowWidgetClass,    * dialog_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   /* 35, */ 50,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  15,
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                * sel_label,
      XmNbottomOffset,                2,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNwidth,                       /* 175, */ 170,
      XmNheight,                      height,
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNspacing,                     0,
      NULL );

  /***
  create RadioBox/RowCol in Scroll
  ***/
  * radio_box = XmCreateRadioBox ( * radio_box_scroll,
        "SelDialog",
        NULL,
        0 );
  XtVaSetValues ( * radio_box,
        XmNorientation,            XmVERTICAL,
        XmNisHomogeneous,          False,
        XmNspacing,                0,
        NULL );

  /***
  recreate buttons in RadioBox/RowCol
  ***/
  for ( i = 0; i < sel_arr_tot; i++ ) {
    xstr = XmStringCreateLtoR ( sel_str_arr [ i ], charset );
    but = XtVaCreateManagedWidget ( "SelDialog",
        xmToggleButtonGadgetClass,     * radio_box,
        XmNspacing,                    2,
        XmNlabelString,                xstr,
        XmNhighlightThickness,         1,
        XmNnavigationType,             XmTAB_GROUP,
        NULL );
    XmStringFree ( xstr );
    XtAddCallback ( but, XmNvalueChangedCallback,
        ( XtCallbackProc ) SelectionToggleBox_CB,
        ( XtPointer ) & c_arr [ i ] );
    if ( i == 0 ) {
      XmToggleButtonSetState ( but, True, False );
      sel_arr_tog [ i ] = 1;
    }
    else {
      sel_arr_tog [ i ] = 0;
    }
  }

  /***
  Load text with dir ..
  ***/
  {
    int j = 0;
    int k = 0;
    while ( sel_str_arr [ sel_arr_MAX ] [ j ] != '\0' ) {
      fifo_write_buf [ k ] = sel_str_arr [ sel_arr_MAX ] [ j ];
      j++;
      k++;
    }
    fifo_write_buf [ k ] = '/';
    fifo_write_buf [ k + 1 ] = '\0';
    XmTextFieldSetString ( * sel_text, fifo_write_buf ) ;
  }
}



/************************
  The Sel dialogs
************************/
void
Popup_SelPMDRules_Dialog ( parent, title )
Widget parent;
char * title;
{
#define Sel_Dialog_help_text "\
Select one or more items from the list:\n(selection may be invoked by \"double-clicking\"\non the last item required)"

#define Sel_Dialog_help_width  275
#define Sel_Dialog_help_height 125

  Make_Sel_Dialog_Declarations;

  Widget but;
  XmString xstr;
  int height, i;
  char text [ 250 ];

  if ( ! dialog ) {
 
    /***
    Create the basic dialog
    ***/
    Cre_Sel_Dialog ( & parent, & dialog, & dialog_form,
                     & radio_box_scroll, & radio_box,
                     & B_logo,
                     & sep,
                     & och_form, & och_o, & och_c, & och_h, & och_a, & och_n,
                     & help_data, & label,
                     SelLarge_flag_EXTRA,
		     & WM_DELETE_WINDOW,
                     0 );

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) Sel_Dialog_help_text;
    help_data.width  = Sel_Dialog_help_width;
    help_data.height = Sel_Dialog_help_height;

  }

  Re_Cre_Sel_Dialog ( & dialog, & dialog_form, & label,
                      & radio_box_scroll, & radio_box,
                      & B_logo,
                      & sep,
                      SelOne_flagged_NO, & och_a, & och_n,
                      title,
                      GetBsel_NLallowed_flag_NO,
                      GetBsel_flag_NO );

  /***
  Dialog ready
  ***/
  Manage_Sel_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_Sel_Dialog ( parent, title )
Widget parent;
char * title;
{
#define Sel_Dialog_help_text "\
Select one or more items from the list:\n\n\
All items may be selected through \"All\"\n\n\
All items may be deselected through \"None\"\n\n\
(Selection may be invoked by \"double-clicking\"\non the last item required)"

#define Sel_Dialog_help_width  325
#define Sel_Dialog_help_height 225

  Make_Sel_Dialog_Declarations;

  Widget but;
  XmString xstr;
  int height, i;
  char text [ 250 ];

  if ( ! dialog ) {
 
    /***
    Create the basic dialog
    ***/
    Cre_Sel_Dialog ( & parent, & dialog, & dialog_form,
                     & radio_box_scroll, & radio_box,
                     & B_logo,
                     & sep,
                     & och_form, & och_o, & och_c, & och_h, & och_a, & och_n,
                     & help_data, & label,
                     SelLarge_flag_NO,
		     & WM_DELETE_WINDOW,
                     0 );

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) Sel_Dialog_help_text;
    help_data.width  = Sel_Dialog_help_width;
    help_data.height = Sel_Dialog_help_height;

  }

  Re_Cre_Sel_Dialog ( & dialog, & dialog_form, & label,
                      & radio_box_scroll, & radio_box,
                      & B_logo,
                      & sep,
                      SelOne_flagged_NO, & och_a, & och_n,
                      title,
                      GetBsel_NLallowed_flag_NO,
                      GetBsel_flag_NO );

  /***
  Dialog ready
  ***/
  Manage_Sel_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_SelLarge_Dialog ( parent, title )
Widget parent;
char * title;
{
#define SelLargeDialog_help_text "\
Select one or more items from the list:\n\n\
All items may be selected through \"All\"\n\n\
All items may be deselected through \"None\"\n\n\
(Selection may be invoked by \"double-clicking\"\non the last item required)"

#define SelLargeDialog_help_width  325
#define SelLargeDialog_help_height 225

  Make_Sel_Dialog_Declarations;

  if ( ! dialog ) {
 
    /***
    Create the basic dialog
    ***/
    Cre_Sel_Dialog ( & parent, & dialog, & dialog_form,
                     & radio_box_scroll, & radio_box,
                     & B_logo,
                     & sep,
                     & och_form, & och_o, & och_c, & och_h, & och_a, & och_n,
                     & help_data, & label,
                     SelLarge_flag_YES,
		     & WM_DELETE_WINDOW,
                     0 );

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) SelLargeDialog_help_text;
    help_data.width  = SelLargeDialog_help_width;
    help_data.height = SelLargeDialog_help_height;


  }

  Re_Cre_Sel_Dialog ( & dialog, & dialog_form, & label,
                      & radio_box_scroll, & radio_box,
                      & B_logo,
                      & sep,
                      SelOne_flagged_NO, & och_a, & och_n,
                      title,
                      GetBsel_NLallowed_flag_NO,
                      GetBsel_flag_NO );

  /***
  Dialog ready
  ***/
  Manage_Sel_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_SelOne_Dialog ( parent, title )
Widget parent;
char * title;
{
#define SelOneDialog_help_text "\
Select one item from the list:\n(selection may be invoked by \"double-clicking\"\non the required item)"

#define SelOneDialog_help_width  275
#define SelOneDialog_help_height 125

  Make_Sel_Dialog_Declarations;

/*
  if ( ( curr_env == ipr_pob_env || curr_env == ipr_lem_env ) &&
       ( Popup_Sel_flag != browse_pmd_selection )                ) {
    if ( sub_frame1 ) {
      XtUnmanageChild ( sub_frame1 );
      XmUpdateDisplay ( sub_frame1 );
      XtDestroyWidget ( sub_frame1 );
      sub_frame1 = ( Widget ) NULL;
    }
    if ( sub_frame2 ) {
      XtUnmanageChild ( sub_frame2 );
      XmUpdateDisplay ( sub_frame2 );
      XtDestroyWidget ( sub_frame2 );
      sub_frame2 = ( Widget ) NULL;
    }
  }
*/

  if ( ! dialog ) {

    /***
    Create the basic dialog
    ***/
    Cre_Sel_Dialog ( & parent, & dialog, & dialog_form,
                     & radio_box_scroll, & radio_box,
                     & B_logo,
                     & sep,
                     & och_form, & och_o, & och_c, & och_h, & och_a, & och_n,
                     & help_data, & label,
                     SelLarge_flag_NO,
		     & WM_DELETE_WINDOW,
                     0 );

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) SelOneDialog_help_text;
    help_data.width  = SelOneDialog_help_width;
    help_data.height = SelOneDialog_help_height;

  }

  Re_Cre_Sel_Dialog ( & dialog, & dialog_form, & label,
                      & radio_box_scroll, & radio_box,
                      & B_logo,
                      & sep,
                      SelOne_flagged_YES, & och_a, & och_n,
                      title,
                      GetBsel_NLallowed_flag_NO,
                      GetBsel_flag_NO );
  
  /***
  set MODAL if not ipr/anim
  ***/
  if ( curr_env == ipr_pob_env ||
       curr_env == ipr_lem_env ||
       curr_env == anm_env        ) {
    XtVaSetValues ( dialog_form,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        NULL );
  }
  else {
    XtVaSetValues ( dialog_form,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        NULL );
  }

  XtSetSensitive ( och_c, True );


  /***
  Dialog ready
  ***/
  Manage_Sel_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

void
Popup_Sel_Dialog_WM_CB ( prompt_dialog, client_data, cbs )
Widget prompt_dialog;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
  Popup_SelChoice_Dialog ( top_level, str_buf, 1 );
  Popup_Info ( "  Ouch!  " );
}

void
Popup_SelChoice_Dialog ( parent, title, recreate_flag )
Widget parent;
char * title;
int recreate_flag;
{
#define SelChoiceDialog_help_text "\
CHOICE encountered in specification;\nselect branch from the list"

#define SelChoiceDialog_help_width  275
#define SelChoiceDialog_help_height 150

  Make_Sel_Dialog_Declarations;

  strcpy ( str_buf, title );  /* for WM_Close */

  if ( recreate_flag ) {
    XtDestroyWidget ( dialog );
    dialog = ( Widget ) 0;
  }

  if ( ! dialog ) {

    /***
    Create the basic dialog
    ***/
    Cre_Sel_Dialog ( & parent, & dialog, & dialog_form,
                     & radio_box_scroll, & radio_box,
                     & B_logo,
                     & sep,
                     & och_form, & och_o, & och_c, & och_h, & och_a, & och_n,
                     & help_data, & label,
                     SelLarge_flag_YES,
		     & WM_DELETE_WINDOW,
                     1 );

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) SelChoiceDialog_help_text;
    help_data.width  = SelChoiceDialog_help_width;
    help_data.height = SelChoiceDialog_help_height;

    /***
    not MODAL
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,  /* sure ? */
       NULL );

    /***
    change CANCEL
    ***/
    XtDestroyWidget ( och_c );
    och_c = XtVaCreateManagedWidget ( "Abort Operation", 
        xmPushButtonGadgetClass, och_form,
        XmNleftAttachment,       XmATTACH_WIDGET,
        XmNleftWidget,           och_o,
        XmNleftOffset,           45,
        XmNtopAttachment,        XmATTACH_FORM,
        XmNtopOffset,            3,
        XmNheight,               27,
        XmNwidth,                125,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   1,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XtAddCallback ( och_c, XmNactivateCallback,
        ( XtCallbackProc ) Popup_Sel_Dialog_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
  }

  Re_Cre_Sel_Dialog ( & dialog, & dialog_form, & label,
                      & radio_box_scroll, & radio_box,
                      & B_logo,
                      & sep,
                      SelOne_flagged_YES, & och_a, & och_n,
                      title,
                      GetBsel_NLallowed_flag_YES,
                      GetBsel_flag_NO );

  /***
  unmanage och_a och_n
  ***/
  XtUnmanageChild ( och_a );
  XtUnmanageChild ( och_n );

  /***
  Dialog ready
  ***/
  Manage_Sel_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );

}

void
Popup_SelLargeOne_Dialog ( parent, title )
Widget parent;
char * title;
{
#define SelLargeOneDialog_help_text "\
Select one item from the list"

#define SelLargeOneDialog_help_width  225
#define SelLargeOneDialog_help_height 100

  Make_Sel_Dialog_Declarations;

  if ( ! dialog ) {
 
    /***
    Create the basic dialog
    ***/
    Cre_Sel_Dialog ( & parent, & dialog, & dialog_form,
                     & radio_box_scroll, & radio_box,
                     & B_logo,
                     & sep,
                     & och_form, & och_o, & och_c, & och_h, & och_a, & och_n,
                     & help_data, & label,
                     SelLarge_flag_EXTRA,
		     & WM_DELETE_WINDOW,
                     0 );

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) SelLargeOneDialog_help_text;
    help_data.width  = SelLargeOneDialog_help_width;
    help_data.height = SelLargeOneDialog_help_height;

    /***
    not MODAL
    ***/
    XtVaSetValues ( dialog_form,
       XmNdialogStyle,            XmDIALOG_MODELESS,
       NULL );

  }

  Re_Cre_Sel_Dialog ( & dialog, & dialog_form, & label,
                      & radio_box_scroll, & radio_box,
                      & B_logo,
                      & sep,
                      SelOne_flagged_YES, & och_a, & och_n,
                      title,
                      GetBsel_NLallowed_flag_NO,
                      GetBsel_flag_YES );
  
  /***
  Dialog ready
  ***/
  Manage_Sel_Dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


void
Popup_Selection_Sel_Dialog ( parent, title )
Widget parent;
char * title;
{

/* */
#define FileSelDialog_help_text "\
This dialog prompts for the directory to be used as the\n\
current development directory. If the directory given in as the\n\
\"Current Selection\" does not exist then you will be asked whether\n\
you would like it to be created. \n\n\
\"OK\" selects the \"Current Selection\", as does <CR> at the *end*\n\
of the Current Selection text.\n\n\
The selection may be changed by either clicking on one of the\n\
radio-buttons, or by typing the directory name (full path, or relative\n\
to the current development directory) directly into the Selection,\n\
and then selected by either \"OK\" or <CR>.\n\n\
\"Filter\" changes the directories displayed to those of the Current Selection.\n\n\
\"Double-clicking\" on a radio-button has same effect as clicking the\n\
radio-button and then clicking on \"Filter\".\n\n\
Note that directories without write permission are not displayed"

#define FileSelDialog_help_width  450
#define FileSelDialog_help_height 310

  Make_Selection_Sel_Dialog_Declarations;
  static struct coord coord_data;

   if ( ! dialog ) {

    /***
    Create the basic dialog
    ***/
    Cre_Selection_Sel_Dialog ( & parent, & dialog, & dialog_form,
                               & radio_box_scroll, & radio_box,
                               & B_logo,
                               & sep,
                               & och_form, & och_o, & och_f, & och_c, & och_h,
                               & help_data, & label,
                               & sel_label, & sel_text, & WM_DELETE_WINDOW );

    coord_data.x = 0; /* not used */
    coord_data.y = /* 60; */ 150;

    XtAddCallback ( dialog, XmNpopupCallback,
        ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
        ( XtPointer ) & coord_data );

    /***
    Set help data
    ***/
    help_data.type   = DIALOG_HELP;
    help_data.text   = ( char * ) FileSelDialog_help_text;
    help_data.width  = FileSelDialog_help_width;
    help_data.height = FileSelDialog_help_height;

  }

  Re_Cre_Selection_Sel_Dialog ( & dialog, & dialog_form, & label,
                           & radio_box_scroll, & radio_box,
                           & B_logo,
                           & sel_label, & sel_text,
                           title );
  
  XtVaSetValues ( dialog_form,
      XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
      NULL );

  /***
  Dialog ready
  ***/
  Manage_Selection_Sel_Dialog;
  cd_dialog = dialog;
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}



/**************************************************
     NewOptions
***************************************************/


/**************************** Global Save/Restore **************************/

void
SaveCurrentOptions_Proceed ()
{
  char *getenv(), *name;
  FILE * optfile;
  int i, n;
  char buf [ PATH_MAX ];  /* don't want the global buf */

  name = getenv ( "HOME" );
  if ( name == NULL ) {
    Popup_Info ( " Environment variable HOME not set " );
    DisplayCurrWinText ( "\n  Environment variable HOME not set\n" );
    return;
  }

  strcpy ( buf, name );
  strcat ( buf, "/.BToolkitrc" );
  optfile = fopen ( buf, "w" );
  if ( optfile == NULL ) {
    Popup_Info ( " BMotif: can't open .BToolkitrc " );
    DisplayCurrWinText ( "\n  BMotif: can't open " );
    DisplayCurrWinText ( buf );
    DisplayCurrWinText ( " for writing\n" );
    return;
  } 

  fprintf ( optfile, "%s%c", cur_hdr_string, '\0' );

  fprintf ( optfile, "%c", 27 );

  for ( i = 1 ; i <= 75 ; i++ ) { /* 75 flags */
    valIth_flags ( &n, i );
    fprintf ( optfile, "%c", n );
/***
printf ( "saved flag %2d: %d\n", i, n );
***/
  }

  for ( i = 1 ; i <= 50 ; i++ ) { /* 50 strings */
    Retrieve_String ( i, buf );
    fprintf ( optfile, "%s%c", buf, 27 );
/***
printf ( "saved string %2d: |%s|\n", i, buf );
***/
  }

  fclose ( optfile );
  DisplayCurrWinText ( "\n  Current Options saved as Globals\n" );
}

void
SaveCurrentOptions ()
{
  char *getenv(), *name;
  FILE * optfile;

  name = getenv ( "HOME" );
  if ( name == NULL ) {
    Popup_Info ( " Environment variable HOME not set " );
    DisplayCurrWinText ( "\n  Environment variable HOME not set\n" );
    return;
  }

  strcpy ( buf, name );
  strcat ( buf, "/.BToolkitrc" );
  optfile = fopen ( buf, "r" );
  if ( optfile != NULL ) {
    fclose ( optfile );
    strcpy ( primary_string, "Overwrite Global Options? " );
    strcpy ( secondary_string, "Current Global Options will be lost" );
    radiobox_flag = save_options_radiobox;
    confirm_flag = radiobox_flag;
    Popup_ConfirmDialog ( top_level );
  }
  else {
    SaveCurrentOptions_Proceed ();
  }  
}

void
RestoreDefaultOptions_Proceed ( message_flag )
int message_flag;
{
  /***
  message_flag not set if creating new directory
  ***/

  char buf [ 150 ];  /* don't want the global buf */
  char buf1 [ 150 ];
  char buf2 [ 150 ];
  char buf3 [ 150 ];
  char buf4 [ 150 ];
  char buf5 [ 150 ];

  char *getenv(), *name;
  FILE * optfile;
  int i, j, c, rr, old_val;

  name = getenv ( "HOME" );
  if ( name == NULL ) {
    Popup_Info ( " Environment variable HOME not set " );
    DisplayCurrWinText ( "\n  Environment variable HOME not set\n" );
    return;
  }

  strcpy ( buf, name );
  strcat ( buf, "/.BToolkitrc" );
  optfile = fopen ( buf, "r" );
  if ( optfile == NULL ) {
    DisplayCurrWinText ( "\n  BMotif: can't open " );
    DisplayCurrWinText ( buf );
    DisplayCurrWinText ( " for reading\n" );
    return;
  } 

  /***
  check header string from .Bpda
  ***/
  i = 0;
  c = 'x';
  while ( c != '\0' && c != EOF ) {
    c = getc ( optfile );
    buf [ i ] = ( char ) c;
    i++;
  }

  if ( c != EOF ) {
    if ( ( strcmp ( buf, old_hdr_string ) != 0 ) &&
         ( strcmp ( buf, cur_hdr_string ) != 0 )    ) {
      fclose ( optfile );
      Popup_Err ( 0, " Defaults file incompatability (1) " );
      strcpy ( buf, "\n  Defaults not saved from a " );
      strcat ( buf,  toolkit_short_ver );
      strcat ( buf,  " development (1)\n\n  Set Options and then `Save Current Options'\n" );
      DisplayCurrWinText ( buf );
      return;
    }
  }
  else {
    fclose ( optfile );
    Popup_Err ( 0, " Defaults file incompatability (2) " );
    strcpy ( buf, "\n  Defaults not saved from a " );
    strcat ( buf,  toolkit_short_ver );
    strcat ( buf,  " development (2)\n\n  Set Options and then `Save Current Options'\n" );
    DisplayCurrWinText ( buf );
    return;
  }

   /***
   save optional utilities
   ***/
   Retrieve_String ( optional_utility1_str_num, buf1 );
   Retrieve_String ( optional_utility2_str_num, buf2 );
   Retrieve_String ( optional_utility3_str_num, buf3 );
   Retrieve_String ( optional_utility4_str_num, buf4 );
   Retrieve_String ( optional_utility5_str_num, buf5 );

  c = getc ( optfile );

  if ( c == 27 ) {

    int old_Interface_Option, old_Prog_Language_Option;
    int new_Interface_Option, new_Prog_Language_Option;

    /*** new style ***/

/***
printf ( "new style restore\n" );
***/

     /***
     remember interface & prog language
     ***/
    valIth_flags ( &old_Interface_Option, Interface_Option_num );
    valIth_flags ( &old_Prog_Language_Option, Prog_Language_Option_num );

    i = 1;
    c = getc ( optfile );
    while ( ( c != EOF ) && ( i <= 75 ) ) {        /* 75 flags */
       modIth_flags ( i, c );
/***
printf ( "restored flag %2d: %d\n", i, c );
***/
       c = getc ( optfile );
       i++;
    }

    if ( c == EOF ) {
      fclose ( optfile );
      sprintf ( buf, " Error restoring defaults ( error code 1:%d ) ", i );
      Popup_Minor_Err ( top_level, buf );
      return;
    }

    i = 1;
    while ( ( c != EOF ) && ( i <= 50 ) ) {       /* 50 strings */
      j = 0;
      while ( c != EOF && c != 27 ) {
        buf [ j ] = ( char ) c;
        c = getc ( optfile );
        j++;
      }
      buf [ j ] = '\0';

      if ( c == EOF ) {
        fclose ( optfile );
        sprintf ( buf, " Error restoring defaults ( error code 2:%d ) ", i );
        Popup_Minor_Err ( top_level, buf );
        return;
      }
/***
printf ( "restored string %2d: `%s'\n", i, buf );
***/

      Store_String ( &rr, i, buf );
      chk_rep ( rr, 4000 + i );

      c = getc ( optfile );
      i++;
    }

    if ( i != 51 ) {
      fclose ( optfile );
      sprintf ( buf, " Error restoring defaults ( error code 3:%d ) ", i );
      Popup_Minor_Err ( top_level, buf );
      return;
    }

    fclose ( optfile );

    if ( message_flag ) {  /* ie. not from cre new dev dir  - DefaultSettings */

      valIth_flags ( &new_Interface_Option, Interface_Option_num );
      valIth_flags ( &new_Prog_Language_Option, Prog_Language_Option_num );

      if ( ( new_Interface_Option != old_Interface_Option )         || 
           ( new_Prog_Language_Option != old_Prog_Language_Option )    ) {

        void DisplayNewEnv ();

        RecompileLibCodeFiles ( 0 );
        ResetAllCode ( 0 );

        if ( new_Interface_Option != old_Interface_Option ) ResetAllInterfaces ();


        DisplayChanged = 1;
        DisplayCurrentEnv ();

      } /* if ( ( new_Interface_Option !=  ... */

    } /* if ( message_flag ) */

    if ( message_flag )
      DisplayCurrWinText ( "\n  Current options set from globals\n  (Optional Utilities preserved)\n" );

/*
    WriteBtlb ();  /? teamlib ?/
*/
    WriteBplf ();  /* prog lang option */
    WriteBdmf ();  /* dmu option       */

  } /* if ( c == 27 ) */

  else {

    DisplayCurrWinText ( "\n  Can't set current options from globals\n\n  Global file is too old - recreate current options and save\n" );
    Popup_Info ( "Can't set current options from globals" );

  }
  
  /***
  restore optional utilities
  ***/
  Store_String ( &rr, optional_utility1_str_num, buf1 );
  chk_rep ( rr, 243 );
  Store_String ( &rr, optional_utility2_str_num, buf2 );
  chk_rep ( rr, 244 );
  Store_String ( &rr, optional_utility3_str_num, buf3 );
  chk_rep ( rr, 245 );
  Store_String ( &rr, optional_utility4_str_num, buf4 );
  chk_rep ( rr, 246 );
  Store_String ( &rr, optional_utility5_str_num, buf5 );
  chk_rep ( rr, 247 );

  /***
  set max_fwd_ctr_auto_prf; print TMP/.Bmfh
  ***/
  valIth_flags ( &max_fwd_ctr_auto_prf, Provers_max_fwd_Option_num );
  if ( ! max_fwd_ctr_auto_prf ) max_fwd_ctr_auto_prf = 250;
  WriteBmfh ();

}

void
RestoreDefaultOptions ()
{
  char *getenv(), *name;
  FILE * optfile;

  name = getenv ( "HOME" );
  if ( name == NULL ) {
    Popup_Info ( " Environment variable HOME not set " );
    DisplayCurrWinText ( "\n  Environment variable HOME not set\n" );
    return;
  }
  
  strcpy ( buf, name );
  strcat ( buf, "/.BToolkitrc" );
  optfile  = fopen ( buf, "r" );
  if ( optfile != NULL ) {
    fclose ( optfile );
    strcpy ( primary_string, "Set Options from Globals? " );
    strcpy ( secondary_string, "Current settings will be lost" );
    radiobox_flag = restore_options_radiobox;
    confirm_flag = radiobox_flag;
    Popup_ConfirmDialog ( top_level );
  }
  else {
    Popup_Info ( " ~/.BToolkitrc does not exist! " );
    strcpy ( buf, "\n  " );
    strcat ( buf, name );
    strcat ( buf, "/.BToolkitrc" );
    strcat ( buf, " does not exist!\n" );
    DisplayCurrWinText ( buf ); 
  }
}

/*************************   Options   **********************************/

XtCallbackProc
Cre_NewOption_Dialog_OK_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  int * ud;

  void Cre_NewOption_Process_Remake ();
  void Cre_NewOption_Process_ConstructDisplay ();
  void Cre_NewOption_Process_EditorsViewers ();
  void Cre_NewOption_Process_Documents ();
  void Cre_NewOption_Process_TranslatorsCompilers ();
  void Cre_NewOption_Process_Provers ();
  void Cre_NewOption_Process_Interface ();
  void Cre_NewOption_Process_Bell ();
  void Cre_NewOption_Process_AnimateScripts ();
  void Cre_NewOption_Process_Teamlib ();
  void Cre_NewOption_Process_SourceControl ();

  XtPopdown ( ( Widget ) client_data );
  XmUpdateDisplay ( ( Widget ) client_data );

  XtVaGetValues ( widget, XmNuserData, & ud, NULL );
  switch ( * ud ) {
    case OPTIONS_REMAKE :
      Cre_NewOption_Process_Remake ();
      break;
    case OPTIONS_CONSTRUCT_DISPLAY :
      Cre_NewOption_Process_ConstructDisplay ();
      break;
    case OPTIONS_EDITORS_VIEWERS :
      Cre_NewOption_Process_EditorsViewers ();
      break;
    case OPTIONS_DOCUMENTS :
      Cre_NewOption_Process_Documents ();
      break;
    case OPTIONS_TRANSLATORS_COMPILERS :
      Cre_NewOption_Process_TranslatorsCompilers ();
      break;
    case OPTIONS_PROVERS :
      Cre_NewOption_Process_Provers ();
      break;
    case OPTIONS_INTERFACE :
      Cre_NewOption_Process_Interface ();
      break;
    case OPTIONS_BELL :
      Cre_NewOption_Process_Bell ();
      break;
    case OPTIONS_OPTIONAL_UTILITIES :
      Cre_NewOption_Process_AnimateScripts ();
      break;
/*
    case OPTIONS_TEAMLIB :
      Cre_NewOption_Process_Teamlib ();
      break;
*/
    case OPTIONS_SOURCE_CONTROL :
      Cre_NewOption_Process_SourceControl ();
      break;
  }

  XtDestroyWidget ( ( Widget ) client_data );
}

XtCallbackProc
Cre_NewOption_Dialog_CANCEL_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  XtPopdown ( ( Widget ) client_data );
  XmUpdateDisplay ( ( Widget ) client_data );
  XtDestroyWidget ( ( Widget ) client_data );
}

#define NewOptions_Dialog_help_text "\
All options setting are saved when the current\n\
developent is saved. They may be saved/restored\n\
from the .BToolkitrc file\n\n.\
For a description of options settings, see Top Bar Help:\n\
TopBar->Set Tool Attributes Options."

#define Make_NewOption_Dialog_Declarations \
 \
  Widget dialog, dialog_form, \
         label, B_logo, \
         sep, \
         form_scroll, form, left_rc, right_rc, \
         och_o, och_c, och_h, och_form; \
  static struct coord coord_data; \
  static struct help_struct help_data

#define Manage_NewOption_Dialog \
 \
  XtManageChild ( label ); \
  XtManageChild ( B_logo ); \
  XtManageChild ( left_rc ); \
  XtManageChild ( right_rc ); \
  XtManageChild ( form ); \
  XtManageChild ( form_scroll ); \
  XtManageChild ( och_o ); \
  XtManageChild ( och_c ); \
  XtManageChild ( och_h ); \
  XtManageChild ( och_form ); \
  XtManageChild ( sep ); \
  XtManageChild ( dialog_form )

void
Cre_NewOption_Dialog ( dialog, dialog_form, height,
                    label, B_logo,
                    sep,
                    form_scroll, form, left_rc, right_rc,
                    och_form, och_o, och_c, och_h,
                    label_string,
		    coord_data,
		    help_data,
                    option_id )

                    Widget * dialog;
                    Widget * dialog_form;
                    int height;
                    Widget * label;
                    Widget * B_logo;
                    Widget * sep;
                    Widget * form_scroll;
                    Widget * form;
                    Widget * left_rc;
                    Widget * right_rc;
                    Widget * och_form;
                    Widget * och_o;
                    Widget * och_c;
                    Widget * och_h;
                    char * label_string;
		    struct coord * coord_data;
                    struct help_struct * help_data;
		    int option_id;
{
  XmString xstr;
  Arg args [ 2 ];

  /***
  create the dialog
  ***/
  XtSetArg ( args [ 0 ], XmNresizeWidth, True );

  * dialog = XmCreateDialogShell ( top_frame_form, "SelDialog", args, 1 );

  coord_data->x = 0; /* not used */
  coord_data->y = 48;

  XtAddCallback ( * dialog, XmNpopupCallback,
      ( XtCallbackProc ) CentreWidgetRelMainWin_CB,
      ( XtPointer ) coord_data );

  * dialog_form = XtVaCreateWidget ( "Options",
      xmFormWidgetClass,         * dialog,
      XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
      XmNresizeWidth,            True,
      XmNdefaultPosition,        False,  
      XmNtraversalOn,            True,
      XmNautoUnmanage,           False,
      NULL );

  * B_logo = XtVaCreateWidget ( "Options", 
      xmPushButtonWidgetClass,    * dialog_form,
      XmNtopAttachment,           XmATTACH_FORM,
      XmNtopOffset,               10,
      XmNleftAttachment,          XmATTACH_FORM,
      XmNleftOffset,              10,
      XmNlabelType,               XmPIXMAP,
      XmNlabelPixmap,             B_framed_pixmap_gray94,
      XmNshadowThickness,         0,
      XmNmarginWidth,             0,
      XmNmarginHeight,            0,
      XmNtraversalOn,             False,
      NULL );

  XtAddCallback ( * B_logo, XmNactivateCallback,
                                    ( XtCallbackProc ) B_info_CB, NULL );

  xstr = XmStringCreateLocalized ( label_string );
  * label = XtVaCreateWidget ( "Label",
      xmLabelWidgetClass,        * dialog_form,
      XmNtopAttachment,          XmATTACH_FORM,
      XmNtopOffset,              12,
      XmNleftAttachment,         XmATTACH_WIDGET,
      XmNleftWidget,             * B_logo,
      XmNleftOffset,             1,
      XmNrightAttachment,        XmATTACH_FORM,
      XmNrightOffset,            36,
      XmNlabelString,            xstr,
      XmNmarginWidth,            10,
      XmNmarginHeight,           10,
      XmNtraversalOn,            False,
      NULL );
  XmStringFree ( xstr );

  * sep = XtVaCreateManagedWidget ( "Options",
      xmSeparatorGadgetClass,         * dialog_form,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  0,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 0,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                48,
      NULL );

  * form_scroll = XtVaCreateWidget ( "Options",
      xmScrolledWindowWidgetClass,    * dialog_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   55,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 5,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  5,
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                * sep,
      XmNbottomOffset,                10,
      XmNwidth,                       512,  /* 450,*/
      XmNheight,                      height,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNspacing,                     0,
      NULL );

  * form = XtVaCreateWidget ( "Options",
      xmFormWidgetClass,              * form_scroll,
      XmNwidth,                       480,  /* */
      XmNfractionBase,                10,
      NULL );

  /* */
  * left_rc = XtVaCreateWidget ( "ButtonLabel",
      xmRowColumnWidgetClass,         * form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   5,
      XmNbottomAttachment,            XmATTACH_FORM,

XmNleftAttachment, XmATTACH_POSITION,
XmNleftPosition, 0,
XmNwidth,                       240,

      XmNrightOffset,                 3,
      XmNleftOffset,                  3,
      XmNisAligned,                   True,
      XmNentryAlignment,              XmALIGNMENT_END,
      XmNtraversalOn,                 False,
      /* 
      XmNspacing,                     13,
      */
      XmNspacing,                     11,
      NULL );

	* right_rc = XtVaCreateWidget ( "Options",
      xmRowColumnWidgetClass,         * form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNleftAttachment,   XmATTACH_WIDGET,
      XmNleftWidget,       * left_rc,
      XmNleftOffset,                  0,
      XmNnavigationType,              XmTAB_GROUP,
      XmNisHomogeneous,               False,
      XmNspacing,                     5,
      NULL );
  

/* 
  * left_rc = XtVaCreateWidget ( "ButtonLabel",
      xmRowColumnWidgetClass,         * form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   5,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_POSITION,
      XmNrightPosition,               1,
      XmNrightOffset,                 3,
      XmNleftOffset,                  3,
      XmNisAligned,                   True,
      XmNentryAlignment,              XmALIGNMENT_END,
      XmNtraversalOn,                 False,
      XmNspacing,                     13,
      NULL );

  * right_rc = XtVaCreateWidget ( "Options",
      xmRowColumnWidgetClass,         * form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_POSITION,
      XmNleftPosition,                1,
      XmNleftOffset,                  0,
      XmNnavigationType,              XmTAB_GROUP,
      XmNisHomogeneous,               False,
      XmNspacing,                     5,
      NULL );
*/

  * och_form = XtVaCreateWidget ( "ButtonLabel",
      xmFormWidgetClass,       * dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         5,
      NULL );

  * och_o = XtVaCreateManagedWidget ( "OK", 
      xmPushButtonGadgetClass, * och_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           12,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      XmNuserData,             ( XtPointer ) & c_arr [ option_id ],
      NULL );
  XtAddCallback ( * och_o, XmNactivateCallback,
      ( XtCallbackProc ) Cre_NewOption_Dialog_OK_CB,
      ( XtPointer ) * dialog );

  * och_c = XtVaCreateManagedWidget ( "Cancel", 
      xmPushButtonGadgetClass, * och_form,
      XmNleftAttachment,       XmATTACH_WIDGET,
      XmNleftWidget,           * och_o,
      XmNleftOffset,           12,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      XmNuserData,             ( XtPointer ) & c_arr [ option_id ],
      NULL );
  XtAddCallback ( * och_c, XmNactivateCallback,
      ( XtCallbackProc ) Cre_NewOption_Dialog_CANCEL_CB,
      ( XtPointer ) * dialog );

  * och_h = XtVaCreateManagedWidget ( "Help", 
      xmPushButtonGadgetClass, * och_form,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          12,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            3,
      XmNheight,               27,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( * och_h, XmNactivateCallback,
      ( XtCallbackProc ) Popup_Help_CB,
      ( XtPointer ) help_data );

}

/*******************************   Remake Options   ****************************/

int    Remake_pog_NewOption_pd;
int    Remake_apr_NewOption_pd;
int    Remake_ppf_NewOption_pd;
int    Remake_dmu_NewOption_pd;
int    Remake_trl_NewOption_pd;
int    Remake_lnk_NewOption_pd;
int    Remake_itf_NewOption_pd;

void
Cre_NewOption_POG_Remake_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Remake_pog_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_APR_Remake_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Remake_apr_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_PPF_Remake_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Remake_ppf_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_DMU_Remake_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Remake_dmu_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_TRL_Remake_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Remake_trl_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_LNK_Remake_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Remake_lnk_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_ITF_Remake_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Remake_itf_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_Process_Remake ()
{
  modIth_flags ( Remake_pog_Option_num, Remake_pog_NewOption_pd );
  modIth_flags ( Remake_apr_Option_num, Remake_apr_NewOption_pd );
  modIth_flags ( Remake_ppf_Option_num, Remake_ppf_NewOption_pd );
  modIth_flags ( Remake_dmu_Option_num, Remake_dmu_NewOption_pd );
  modIth_flags ( Remake_trl_Option_num, Remake_trl_NewOption_pd );
  modIth_flags ( Remake_lnk_Option_num, Remake_lnk_NewOption_pd );
  modIth_flags ( Remake_itf_Option_num, Remake_itf_NewOption_pd );
}

void
Popup_NewRemake_Options_Dialog ()
{
  Make_NewOption_Dialog_Declarations;
  Widget w;
  XmString xstr, xstr1, xstr2;

  Cre_NewOption_Dialog ( & dialog, & dialog_form, 250,
                      & label, & B_logo,
                      & sep,
                      & form_scroll, & form, & left_rc, & right_rc,
                      & och_form, & och_o, & och_c, & och_h,
                      "Remake Options",
                      & coord_data,
                      & help_data,
                      OPTIONS_REMAKE
                    );

   help_data.type   = DIALOG_HELP;
   help_data.width  = 350;
   help_data.height = 150;  
   help_data.text   = "\
Each tool may be included or excluded from\n\
the Global Remake.\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes      Options.";  

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( "            excluded ", charset );
   xstr2 =  XmStringCreateLtoR ( " included ", charset );

   XtVaCreateManagedWidget ( "POGenerator:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   valIth_flags ( &Remake_pog_NewOption_pd, Remake_pog_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Remake_pog_NewOption_pd, Cre_NewOption_POG_Remake_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XtVaCreateManagedWidget ( "Auto/BToolProver:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   valIth_flags ( &Remake_apr_NewOption_pd, Remake_apr_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Remake_apr_NewOption_pd, Cre_NewOption_APR_Remake_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XtVaCreateManagedWidget ( "ProofPrinter:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   valIth_flags ( &Remake_ppf_NewOption_pd, Remake_ppf_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Remake_ppf_NewOption_pd, Cre_NewOption_PPF_Remake_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XtVaCreateManagedWidget ( "DocumentMarkUp:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   valIth_flags ( &Remake_dmu_NewOption_pd, Remake_dmu_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Remake_dmu_NewOption_pd, Cre_NewOption_DMU_Remake_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XtVaCreateManagedWidget ( "Translator:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   valIth_flags ( &Remake_trl_NewOption_pd, Remake_trl_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Remake_trl_NewOption_pd, Cre_NewOption_TRL_Remake_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /*
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XtVaCreateManagedWidget ( "Linker:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   valIth_flags ( &Remake_lnk_NewOption_pd, Remake_lnk_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Remake_lnk_NewOption_pd, Cre_NewOption_LNK_Remake_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XtVaCreateManagedWidget ( "ITFGenerator:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   valIth_flags ( &Remake_itf_NewOption_pd, Remake_itf_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Remake_itf_NewOption_pd, Cre_NewOption_ITF_Remake_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
  XtManageChild ( w );

/***
  {
    Dimension spc;
     XtVaGetValues ( w,
        XmNshadowThickness,         &spc,
        NULL );
     printf ( "spc=%d\n", spc );
  }

***/

  XmStringFree ( xstr );
  XmStringFree ( xstr1 );
  XmStringFree ( xstr2 );

  Manage_NewOption_Dialog;

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

/*************************   Construct Display   **************************/

int    hid_LIB_NewOption_pd;
int    hid_gen_NewOption_pd;

void
Cre_NewOption_hid_LIB_CB ( widget, but_num )
Widget widget;
int but_num;
{
  hid_LIB_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_hid_gen_CB ( widget, but_num )
Widget widget;
int but_num;
{
  hid_gen_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_Process_ConstructDisplay ()
{
  void EnvironmentDisplayDeAllocate_Allocate ();
  void DisplayNewEnv ();
  int hid_LIB_cur, hid_gen_cur, tot;
  
  valIth_flags ( &hid_LIB_cur, hid_LIB_Option_num );
  valIth_flags ( &hid_gen_cur, hid_gen_Option_num );
  modIth_flags ( hid_LIB_Option_num, hid_LIB_NewOption_pd );
  modIth_flags ( hid_gen_Option_num, hid_gen_NewOption_pd );
  hid_LIB_flag = hid_LIB_NewOption_pd;
  hid_gen_flag = hid_gen_NewOption_pd;
  if ( ( hid_LIB_cur != hid_LIB_NewOption_pd ) ||
       ( hid_gen_cur != hid_gen_NewOption_pd )    ) {
    nbr_Construct ( & tot );
    if ( tot >= 100 ) {
      DisplayCurrWinText ( "\n  Re-initialising construct display ... " );
      if ( tot >= 250 ) DisplayCurrWinText ( "please be patient ... " );
    }
    Save_CfgDepBase ();
    EnvironmentDisplayDeAllocate_Allocate ();
    if ( tot >= 100 ) DisplayCurrWinText ( "done\n" );
    LibGenConstructsHiddenDisplayMsg ( 1 );
  }
}

void
Popup_NewConstructDisplay_Options_Dialog ()
{
  Make_NewOption_Dialog_Declarations;
  Widget w;
  XmString xstr, xstr1, xstr2;

  Cre_NewOption_Dialog ( & dialog, & dialog_form, 100,
                      & label, & B_logo,
                      & sep,
                      & form_scroll, & form, & left_rc, & right_rc,
                      & och_form, & och_o, & och_c, & och_h,
                      "Construct Display",
                      & coord_data,
                      & help_data,
                      OPTIONS_CONSTRUCT_DISPLAY
                    );

   help_data.type   = DIALOG_HELP;
   help_data.width  = 375;
   help_data.height = 150;  
   help_data.text   = "\
Library and/or Generated Constructs may be `hidden'\n\
from the construct display (desirable in large developments).\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes      Options.";  

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( "displayed ", charset );
   xstr2 =  XmStringCreateLtoR ( "                    hidden ", charset );

   XtVaCreateManagedWidget ( "Library constructs:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   valIth_flags ( &hid_LIB_NewOption_pd, hid_LIB_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       hid_LIB_NewOption_pd, Cre_NewOption_hid_LIB_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XtVaCreateManagedWidget ( "Generated constructs:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   valIth_flags ( &hid_gen_NewOption_pd, hid_gen_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       hid_gen_NewOption_pd, Cre_NewOption_hid_gen_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

  XmStringFree ( xstr );
  XmStringFree ( xstr1 );
  XmStringFree ( xstr2 );

  Manage_NewOption_Dialog;

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

/*************************   Editors/Viewers Options   **************************/

int    Preserve_Editor_NewOption_pd;
int    Hypertext_Text_NewOption_pd;
Widget editor_str,
       pmd_editor_str,
       htx_viewer_str,
       shell_str;

void
Cre_NewOption_PreserveEditor_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Preserve_Editor_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_HypertextText_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Hypertext_Text_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}
void
Cre_NewOption_Process_EditorsViewers ()
{
  char * text;
  int rr;

  modIth_flags ( Preserve_Editor_Option_num, Preserve_Editor_NewOption_pd );

  text = XmTextFieldGetString ( editor_str );
/***
printf ( "storing editor_str as `%s' in `%d'\n", text, editor_str_num );
***/
  Store_String ( &rr, editor_str_num, text );
  chk_rep ( rr, 178 );
  XtFree ( text );

  text = XmTextFieldGetString ( pmd_editor_str );
  Store_String ( &rr, pmd_editor_str_num, text );
  chk_rep ( rr, 179 );
  XtFree ( text );

  text = XmTextFieldGetString ( htx_viewer_str );
  Store_String ( &rr, htx_viewer_str_num, text );
  chk_rep ( rr, 180 );
  XtFree ( text );

  modIth_flags ( Hypertext_text_num, Hypertext_Text_NewOption_pd );

  text = XmTextFieldGetString ( shell_str );
  Store_String ( &rr, shell_str_num, text );
  chk_rep ( rr, 185 );
  XtFree ( text );

}

void
Popup_NewEditorsViewers_Options_Dialog ()
{
  Make_NewOption_Dialog_Declarations;
  Widget w,constructEditor,pmdEditor,htmlBrowser,b,bb,bbb;
  size_t i;
  XmString xstr, xstr1, xstr2;
  char buf [ PATH_MAX ];  /* don't want the global buf */

  /*printf("Popup_NewEditorsViewers_Options_Dialog. buf size %d\n",PATH_MAX);*/

  Cre_NewOption_Dialog ( & dialog, & dialog_form, 200,
                      & label, & B_logo,
                      & sep,
                      & form_scroll, & form, & left_rc, & right_rc,
                      & och_form, & och_o, & och_c, & och_h,
                      "Editor,Browser,Shell Options",
                      & coord_data,
                      & help_data,
                      OPTIONS_EDITORS_VIEWERS
                    );

   help_data.type   = DIALOG_HELP;
   help_data.width  = 450;
   help_data.height = 350;  
   help_data.text   = "\
Whenever edits are committed, the editor may be either preserved or dismissed (the editor quits).\n\n\
Each setting should contain all the required arguments/parameters,\n\
and have a maximum length of 150\n\n\
eg. Construct Editor: xedit -geometry 550x564+550+300\n\n\
eg. PROOFMETHOD Editor: xedit -geometry 500x400-1-1\n\n\
eg. Hypertext Viewer: netscape -install -geometry =550x750+550-1\n\n\
eg. Shell: color_xterm -ls -sb -sl 5000 -fn 6x10 -geometry 75x35+100+250\n\n\
If no hypetrext viewer is available, the Hypertext Viewer string should be\n\
set to a text editor, and the `Display Hypertext As' set to text.\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes      Options.";  

   XtVaCreateManagedWidget ( "Commit Edits:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( "   dismiss editor  ", charset );
   xstr2 =  XmStringCreateLtoR ( "   preserve editor  ", charset );

   valIth_flags ( &Preserve_Editor_NewOption_pd, Preserve_Editor_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Preserve_Editor_NewOption_pd, Cre_NewOption_PreserveEditor_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       XmNtearOffModel, XmTEAR_OFF_DISABLED,
       NULL);
   XtManageChild ( w );

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );



  XtVaCreateManagedWidget ( "Construct Editor:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );


bb = XtVaCreateManagedWidget ( "form",
      xmFormWidgetClass,              right_rc,
      XmNfractionBase,     4,
      NULL );


   editor_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         bb,
       XmNtraversalOn,                 True,
       XmNtopAttachment,               XmATTACH_FORM,
       XmNleftAttachment,              XmATTACH_FORM,
       XmNrightAttachment,             XmATTACH_POSITION,
       XmNrightPosition,               3,
       
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
       
       
 xstr = XmStringCreateLtoR ( "Choose...", charset );
 constructEditor = XmVaCreateSimpleMenuBar(bb, "Choose",
        XmVaCASCADEBUTTON, xstr, 'C',
	XmNtopAttachment,               XmATTACH_FORM,
       XmNrightAttachment,             XmATTACH_FORM,
       XmNleftAttachment,              XmATTACH_WIDGET,
       XmNleftWidget,                  editor_str,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                2,
       XmNheight,                      24,
       XmNborderWidth,                 0,
       NULL );

  XtManageChild ( constructEditor );
  XmStringFree ( xstr );

  bbb=XmVaCreateSimplePulldownMenu(constructEditor, "editor_menu", 0,
  	( XtCallbackProc ) Do_Nothing_CB,
	XmNtearOffModel, XmTEAR_OFF_DISABLED,
	NULL
	);

  /*printf("Popup_NewEditorsViewers_Options_Dialog. call getEditorOptions\n");*/
  /* Load the global editors[] array */
  getEditorOptions();
  
  for(i=0;i<editorsCount;i=i+1)
  {
  	if(editors[i]==NULL){continue;}
	/*printf("Popup_NewEditorsViewers_Options_Dialog. item %s\n",editors[i]);*/
	xstr=XmStringCreateLtoR ( editors[i], charset );
  	b=XtVaCreateManagedWidget ( "item",
             xmPushButtonWidgetClass,       bbb,
	     XmNlabelString,              xstr,
            NULL );
	/* allocate a call back struct */
	    
	if(constructEditors[i]!=NULL)
	{
		/*printf("Popup_NewEditorsViewers_Options_Dialog. free(constructEditors[%d])\n",i);*/
		free(constructEditors[i]);
	}
	
	/*printf("Popup_NewEditorsViewers_Options_Dialog. constructEditors[%d] = malloc\n",i);*/
	constructEditors[i]=(struct textWidgetXeditor*) malloc((size_t) sizeof(textWidgetXeditor));
	(constructEditors[i]->widget)=(Widget) editor_str;
	(constructEditors[i]->editor)=editors[i];
	
	  XtAddCallback ( b, XmNactivateCallback,
      ( XtCallbackProc ) Editor_Chosen_CB,
      ( XtPointer ) constructEditors[i] );
      XmStringFree ( xstr );
  }
    
    XtManageChild ( bbb );

   buf[0]='\0';
   Retrieve_String ( editor_str_num, buf );
   XmTextFieldSetString ( editor_str, buf ) ;
   XmTextFieldSetInsertionPosition ( editor_str, strlen ( buf ) );
   XtAddCallback ( editor_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );
	   
	   

   XtVaCreateManagedWidget ( "PROOFMETHOD Editor:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );


bb = XtVaCreateManagedWidget ( "form",
      xmFormWidgetClass,              right_rc,
      XmNfractionBase,     4,
      NULL );


   pmd_editor_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         bb,
       XmNtraversalOn,                 True,
       XmNtopAttachment,               XmATTACH_FORM,
       XmNleftAttachment,              XmATTACH_FORM,
       XmNrightAttachment,             XmATTACH_POSITION,
       XmNrightPosition,               3,
       
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
       
       
 xstr = XmStringCreateLtoR ( "Choose...", charset );
 pmdEditor = XmVaCreateSimpleMenuBar(bb, "Choose",
        XmVaCASCADEBUTTON, xstr, 'C',
	XmNtopAttachment,               XmATTACH_FORM,
       XmNrightAttachment,             XmATTACH_FORM,
       XmNleftAttachment,              XmATTACH_WIDGET,
       XmNleftWidget,                  pmd_editor_str,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                2,
       XmNheight,                      24,
       XmNborderWidth,                 0,
       NULL );

  XtManageChild ( pmdEditor );
  XmStringFree ( xstr );

  bbb=XmVaCreateSimplePulldownMenu(pmdEditor, "pmd_editor_menu", 0,
  	( XtCallbackProc ) Do_Nothing_CB,
	XmNtearOffModel, XmTEAR_OFF_DISABLED,
	NULL
	);

  /*printf("Popup_NewEditorsViewers_Options_Dialog. proof method editors\n");*/
  for(i=0;i<editorsCount;i=i+1)
  {
  	if(editors[i]==NULL){continue;}
	/*printf("Popup_NewEditorsViewers_Options_Dialog. item %s\n",editors[i]);*/
	xstr=XmStringCreateLtoR ( editors[i], charset );
  	b=XtVaCreateManagedWidget ( "item",
             xmPushButtonWidgetClass,       bbb,
	     XmNlabelString,              xstr,
            NULL );
	/* allocate a call back struct */
	    
	if(proofMethodEditors[i]!=NULL)
	{
		/*printf("Popup_NewEditorsViewers_Options_Dialog. free(proofMethodEditors[%d])\n",i);*/
		free(proofMethodEditors[i]);
	}
	
	/*printf("Popup_NewEditorsViewers_Options_Dialog. proofMethodEditors[%d]=malloc\n",i);*/
	proofMethodEditors[i]=(struct textWidgetXeditor*) malloc((size_t) sizeof(textWidgetXeditor));
	(proofMethodEditors[i]->widget)=(Widget) pmd_editor_str;
	(proofMethodEditors[i]->editor)=editors[i];
	
	  XtAddCallback ( b, XmNactivateCallback,
      ( XtCallbackProc ) Editor_Chosen_CB,
      ( XtPointer ) proofMethodEditors[i] );
      XmStringFree ( xstr );
  }
    
    XtManageChild ( bbb );

   buf[0]='\0';
   Retrieve_String ( pmd_editor_str_num, buf );
   XmTextFieldSetString ( pmd_editor_str, buf ) ;
   XmTextFieldSetInsertionPosition ( pmd_editor_str, strlen ( buf ) );
   XtAddCallback ( pmd_editor_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

   XtVaCreateManagedWidget ( "Web browser:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

  /* choose for hypertext view aka browser */


bb = XtVaCreateManagedWidget ( "form",
      xmFormWidgetClass,              right_rc,
      XmNfractionBase,     4,
      NULL );

   htx_viewer_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         bb,
       XmNtraversalOn,                 True,
       XmNtopAttachment,               XmATTACH_FORM,
       XmNleftAttachment,              XmATTACH_FORM,
       XmNrightAttachment,             XmATTACH_POSITION,
       XmNrightPosition,               3,
       
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
       
       
 xstr = XmStringCreateLtoR ( "Choose...", charset );
 htmlBrowser = XmVaCreateSimpleMenuBar(bb, "Choose",
        XmVaCASCADEBUTTON, xstr, 'C',
	XmNtopAttachment,               XmATTACH_FORM,
       XmNrightAttachment,             XmATTACH_FORM,
       XmNleftAttachment,              XmATTACH_WIDGET,
       XmNleftWidget,                  htx_viewer_str,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                2,
       XmNheight,                      24,
       XmNborderWidth,                 0,
       NULL );

  XtManageChild ( htmlBrowser );
  XmStringFree ( xstr );

bbb=XmVaCreateSimplePulldownMenu(htmlBrowser, "browser_menu", 0,
  	( XtCallbackProc ) Do_Nothing_CB,
	XmNtearOffModel, XmTEAR_OFF_DISABLED,
	NULL
	);


  /*printf("Popup_NewEditorsViewers_Options_Dialog. call getBrowserOptions\n");*/
  /* Load the global editors[] array */
  getBrowserOptions();
  
  for(i=0;i<browsersCount;i=i+1)
  {
  	if(browsers[i]==NULL){continue;}
	/*printf("Popup_NewEditorsViewers_Options_Dialog. item %s\n",browsers[i]);*/
	xstr=XmStringCreateLtoR ( browsers[i], charset );
  	b=XtVaCreateManagedWidget ( "item",
             xmPushButtonWidgetClass,       bbb,
	     XmNlabelString,              xstr,
            NULL );
	/* allocate a call back struct */
	    
	if(htmlBrowsers[i]!=NULL)
	{
		/*printf("Popup_NewEditorsViewers_Options_Dialog. free(htmlBrowsers[%d])\n",i);*/
		free(htmlBrowsers[i]);
	}
	
	/*printf("Popup_NewEditorsViewers_Options_Dialog. htmlBrowsers[%d]=malloc\n",i);*/
	htmlBrowsers[i]=(struct textWidgetXbrowser*) malloc((size_t) sizeof(textWidgetXbrowser));
	(htmlBrowsers[i]->widget)=(Widget) htx_viewer_str;
	(htmlBrowsers[i]->browser)=browsers[i];
	
	  XtAddCallback ( b, XmNactivateCallback,
      ( XtCallbackProc ) Browser_Chosen_CB,
      ( XtPointer ) htmlBrowsers[i] );
      XmStringFree ( xstr );
  }
    
    XtManageChild ( bbb );

   buf[0]='\0';
   Retrieve_String ( htx_viewer_str_num, buf );
   XmTextFieldSetString ( htx_viewer_str, buf ) ;   XmTextFieldSetInsertionPosition ( htx_viewer_str, strlen ( buf ) );
   XtAddCallback ( htx_viewer_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );
	   
  /* */

   XtVaCreateManagedWidget ( "Display Hypertext As:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( " html ", charset );
   xstr2 =  XmStringCreateLtoR ( " text ", charset );

   valIth_flags ( &Hypertext_Text_NewOption_pd, Hypertext_text_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Hypertext_Text_NewOption_pd, Cre_NewOption_HypertextText_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       XmNtearOffModel, XmTEAR_OFF_DISABLED,
       NULL);
   XtManageChild ( w );

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );


   XtVaCreateManagedWidget ( "Shell:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   shell_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( shell_str_num, buf );
   XmTextFieldSetString ( shell_str, buf ) ;
   XmTextFieldSetInsertionPosition ( shell_str, strlen ( buf ) );
   XtAddCallback ( shell_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

  Manage_NewOption_Dialog;

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
  /*printf("Popup_NewEditorsViewers_Options_Dialog. done\n");*/
}

/*************************   Documents Options ********************************/

int    DMU_Labels_pd,
       DMU_ClIndex_pd,
       DMU_CoIndex_pd,
       DMU_GIndex_pd,
       Point_Size_pd;
/*
       DMU_eps_pd,
       DMU_Language_pd;
*/
Widget latex_declaration_str,
       latex_exec_name_str,
       dvi_screen_str,
       dvi_print_str;

void
Cre_NewOption_DMU_Labels_CB ( widget, but_num )
Widget widget;
int but_num;
{
  DMU_Labels_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_DMU_ClIndex_CB ( widget, but_num )
Widget widget;
int but_num;
{
  DMU_ClIndex_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_DMU_CoIndex_CB ( widget, but_num )
Widget widget;
int but_num;
{
  DMU_CoIndex_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_DMU_GIndex_CB ( widget, but_num )
Widget widget;
int but_num;
{
  DMU_GIndex_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_Point_Size_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Point_Size_pd = but_num + 10;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

/*
void
Cre_NewOption_DMU_eps_CB ( widget, but_num )
Widget widget;
int but_num;
{
  DMU_eps_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_DMU_Language_CB ( widget, but_num )
Widget widget;
int but_num;
{
  DMU_Language_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}
*/

void
Cre_NewOption_Process_Documents ()
{
  char * text;
  int rr;

  modIth_flags ( DMU_Labels_Option_num, DMU_Labels_pd );

  modIth_flags ( DMU_ClIndex_Option_num, DMU_ClIndex_pd );

  modIth_flags ( DMU_CoIndex_Option_num, DMU_CoIndex_pd );

  modIth_flags ( DMU_GIndex_Option_num, DMU_GIndex_pd );

  modIth_flags ( Point_Size_Option_num, Point_Size_pd );

/*
  modIth_flags ( DMU_eps_Option_num, DMU_eps_pd );

  modIth_flags ( DMU_Language_Option_num, DMU_Language_pd );
*/

  text = XmTextFieldGetString ( latex_declaration_str );
  Store_String ( &rr, latex_declaration_str_num, text );
  chk_rep ( rr, 341 );
  XtFree ( text );

  text = XmTextFieldGetString ( latex_exec_name_str );
  Store_String ( &rr, latex_exec_name_str_num, text );
  chk_rep ( rr, 242 );
  XtFree ( text );

  text = XmTextFieldGetString ( dvi_screen_str );
  Store_String ( &rr, dvi_screen_str_num, text );
  chk_rep ( rr, 181 );
  XtFree ( text );

  text = XmTextFieldGetString ( dvi_print_str );
  Store_String ( &rr, dvi_print_str_num, text );
  chk_rep ( rr, 182 );
  XtFree ( text );

  WriteBdmf ();  /* dmu option       */

}

void
Popup_NewDocuments_Options_Dialog ()
{
  Make_NewOption_Dialog_Declarations;
  Widget w;
  XmString xstr, xstr1, xstr2, xstr3;
  char buf [ 150 ];  /* don't want the global buf */

  Cre_NewOption_Dialog ( & dialog, & dialog_form, 300,
                      & label, & B_logo,
                      & sep,
                      & form_scroll, & form, & left_rc, & right_rc,
                      & och_form, & och_o, & och_c, & och_h,
                      "Documents Options",
                      & coord_data,
                      & help_data,
                      OPTIONS_DOCUMENTS
                    );

   help_data.type   = DIALOG_HELP;
   help_data.width  = 500;
   help_data.height = 725;  
   help_data.text   = "\
The first four Document Options may be set to `on' or `off'.\n\n\
The Point size may be set to `10', `11' or `12'.\n\n\
If the LaTex Declaration Option is empty, it defaults to:\n\n\
    \\documentclass[]{article} \\usepackage{Bkit}   or\n\
    \\documentclass[11pt]{article} \\usepackage{Bkit}   or\n\
    \\documentclass[12pt]{article} \\usepackage{Bkit}\n\n\
depending on the Point size setting.\n\n\
These default settings may be overidden by the LaTex Declaration Option,\n\
when the above Point size Option will be ignored; for example:\n\n\
    \\documentclass[article,11pt]{seminar} \\usepackage{Bkit} \\usepackage{epsf}\n\n\
However, if a particular package is required by only the DOCUMENT (and not\n\
its subordinate parts), it may be included in the document in the form of a\n\
prologue annotation: a special annotation appearing in a DOCUMENT between\n\
the document name and the CONTENTS keyword:\n\n\
    DOCUMENT    mydoc\n\
        /*\" LaTeX prologue annotation \"*/\n\
    CONTENTS    ...\n\
    END\n\n\
Such prologue text will appear immediately after the LaTex Declaration, but\n\
before the \\begin{document}. This prologue annotation is also useful when a\n\
particular document requires specific LaTeX commands.\n\n\
If the Latex Executable Option is empty, it defaults to `latex'; if your latex\n\
is called something else, or is not in your path, the appropriate path/name\n\
may be set here.\n\n\
The Screen Viewer and Print Script Options do not have defaults;\n\
example settings are, respectively:\n\n\
    xdvi -expert -s 4\n\n\
    $BKIT/BLIB/printdvi (a sample script is provided)\n\n\
Each string setting should contain all required arguments,\n\
and have a maximum length of 150\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes      Options.";  

   XtVaCreateManagedWidget ( "Labels:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( "         off ", charset );
   xstr2 =  XmStringCreateLtoR ( " on ", charset );

   valIth_flags ( &DMU_Labels_pd, DMU_Labels_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       DMU_Labels_pd, Cre_NewOption_DMU_Labels_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );

   XtVaCreateManagedWidget ( "Clause cross-references:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( "         off ", charset );
   xstr2 =  XmStringCreateLtoR ( " on ", charset );

   valIth_flags ( &DMU_ClIndex_pd, DMU_ClIndex_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       DMU_ClIndex_pd, Cre_NewOption_DMU_ClIndex_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );

   XtVaCreateManagedWidget ( "Construct cross-references:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( "         off ", charset );
   xstr2 =  XmStringCreateLtoR ( " on ", charset );

   valIth_flags ( &DMU_CoIndex_pd, DMU_CoIndex_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       DMU_CoIndex_pd, Cre_NewOption_DMU_CoIndex_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );

   XtVaCreateManagedWidget ( "Index:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( "         off ", charset );
   xstr2 =  XmStringCreateLtoR ( " on ", charset );

   valIth_flags ( &DMU_GIndex_pd, DMU_GIndex_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       DMU_GIndex_pd, Cre_NewOption_DMU_GIndex_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );

   XtVaCreateManagedWidget ( "Point size:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( " 10 ", charset );
   xstr2 =  XmStringCreateLtoR ( " 11 ", charset );
   xstr3 =  XmStringCreateLtoR ( " 12 ", charset );

   valIth_flags ( &Point_Size_pd, Point_Size_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Point_Size_pd - 10, Cre_NewOption_Point_Size_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr3, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );
   XmStringFree ( xstr3 );

/*
   XtVaCreateManagedWidget ( "Encapsulated PostScript:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( "         off ", charset );
   xstr2 =  XmStringCreateLtoR ( " on ", charset );

   valIth_flags ( &DMU_eps_pd, DMU_eps_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       DMU_eps_pd, Cre_NewOption_DMU_eps_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );

   XtVaCreateManagedWidget ( "Document mark-up language:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( " Latex2e ", charset );
   xstr2 =  XmStringCreateLtoR ( " Latex ", charset );

   valIth_flags ( &DMU_Language_pd, DMU_Language_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       DMU_Language_pd, Cre_NewOption_DMU_Language_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );
*/

   XtVaCreateManagedWidget ( "LaTeX Declaration:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   latex_declaration_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( latex_declaration_str_num, buf );
   XmTextFieldSetString ( latex_declaration_str, buf ) ;
   XmTextFieldSetInsertionPosition ( latex_declaration_str, strlen ( buf ) );
   XtAddCallback ( latex_declaration_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

   XtVaCreateManagedWidget ( "LaTeX Executable:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   latex_exec_name_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( latex_exec_name_str_num, buf );
   XmTextFieldSetString ( latex_exec_name_str, buf ) ;
   XmTextFieldSetInsertionPosition ( latex_exec_name_str, strlen ( buf ) );
   XtAddCallback ( latex_exec_name_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

   XtVaCreateManagedWidget ( "Dvi Screen Viewer:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   dvi_screen_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( dvi_screen_str_num, buf );
   XmTextFieldSetString ( dvi_screen_str, buf ) ;
   XmTextFieldSetInsertionPosition ( dvi_screen_str, strlen ( buf ) );
   XtAddCallback ( dvi_screen_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

   XtVaCreateManagedWidget ( "Dvi Print Script:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   dvi_print_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( dvi_print_str_num, buf );
   XmTextFieldSetString ( dvi_print_str, buf ) ;
   XmTextFieldSetInsertionPosition ( dvi_print_str, strlen ( buf ) );
   XtAddCallback ( dvi_print_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );


  Manage_NewOption_Dialog;

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );




}

/********************   Translators/Compilers Options   *************************/

int    prog_lang_pd;
Widget cc_compiler_str,
       cc_link_lib_str,
       cc_Xlink_lib_str;

void
Cre_NewOption_ProgLang_CB ( widget, but_num )
Widget widget;
int but_num;
{
  prog_lang_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_Process_TranslatorsCompilers ()
{
  char * text;
  int n, rr;
  void DisplayNewEnv ();

  text = XmTextFieldGetString ( cc_compiler_str );
  Store_String ( &rr, cc_compiler_str_num, text );
  chk_rep ( rr, 175 );
  XtFree ( text );

  text = XmTextFieldGetString ( cc_link_lib_str );
  Store_String ( &rr, cc_link_lib_str_num, text );
  chk_rep ( rr, 176 );
  XtFree ( text );

  text = XmTextFieldGetString ( cc_Xlink_lib_str );
  Store_String ( &rr, cc_Xlink_lib_str_num, text );
  chk_rep ( rr, 177 );
  XtFree ( text );

  HtmlMasterFileChanged = 1;

  valIth_flags ( &n, Prog_Language_Option_num );

/***
printf ( "\nCre_NewOption_Process_TranslatorsCompilers n=%d prog_lang_pd=%d\n",
                                                                  n, prog_lang_pd );
***/
  switch ( prog_lang_pd ) {

  case 0:    /* ANSIC */
    modIth_flags ( Prog_Language_Option_num, Prog_Language_Option_ANSI_C );
    WriteBplf ();                   /* prog lang options */
    if ( n != Prog_Language_Option_ANSI_C ) {
      void DisplayNewEnv ();
      DisplayChanged = 1;
      /*       ResetAllInterfaces (); */
      RecompileLibCodeFiles ( 0 );
      ResetAllCode ( 0 );
      ResetAllInterfaces ();

      DisplayChanged = 1;
      DisplayCurrentEnv ();

    }
    break;
  default:    /* C */
    modIth_flags ( Prog_Language_Option_num, Prog_Language_Option_C );
    WriteBplf ();                   /* prog lang options */
    if ( n != Prog_Language_Option_C ) {
      void DisplayNewEnv ();
      DisplayChanged = 1;
      /*       ResetAllInterfaces (); */
      RecompileLibCodeFiles ( 0 );
      ResetAllCode ( 0 );
      ResetAllInterfaces ();

      DisplayChanged = 1;
      DisplayCurrentEnv ();

    }
    break;
  }
}

void
Popup_NewTranslatorsCompilers_Options_Dialog ()
{
  Make_NewOption_Dialog_Declarations;
  Widget w;
  XmString xstr, xstr1, xstr2, xstr3;
  char buf [ 150 ];  /* don't want the global buf */

  Cre_NewOption_Dialog ( & dialog, & dialog_form, 150,
                      & label, & B_logo,
                      & sep,
                      & form_scroll, & form, & left_rc, & right_rc,
                      & och_form, & och_o, & och_c, & och_h,
                      "Translator/Compiler Options",
                      & coord_data,
                      & help_data,
                      OPTIONS_TRANSLATORS_COMPILERS
                    );

   help_data.type   = DIALOG_HELP;
   help_data.width  = 450;
   help_data.height = 275;

   help_data.text   = "\
The Programming Language may be set to `ANSI C' or `C'.\n\n\
The C Compiler/Flags string should contain all required arguments\neg. gcc -ansi -pipe -I/usr/X11R6/include -L/usr/X11R6/lib\nMaximum string length: 150\n\n\
The Non-X Link Libraries string should contain all required arguments\neg. -lm\nMaximum string length: 150\n\n\
The X Link Libraries string should contain all required arguments\neg. -lXm -lXt -lX11 -lXext -lXp\nMaximum string length: 150\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes      Options.";  

   XtVaCreateManagedWidget ( "Programming Language:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
        XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

  valIth_flags ( &prog_lang_pd, Prog_Language_Option_num );
  switch ( prog_lang_pd ) {
  case Prog_Language_Option_PASP:
    prog_lang_pd = 2;
    break;
  case Prog_Language_Option_ANSI_C:
    prog_lang_pd = 0;
    break;
  default:
    prog_lang_pd = 1;
    break;
  }

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( " ANSI C ", charset );
   xstr2 =  XmStringCreateLtoR ( " C ", charset );



   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       prog_lang_pd, Cre_NewOption_ProgLang_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );

   XtManageChild ( w );

   XtVaCreateManagedWidget ( "C Compiler/Flags:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );
    
   cc_compiler_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( cc_compiler_str_num, buf );
   XmTextFieldSetString ( cc_compiler_str, buf ) ;
   XmTextFieldSetInsertionPosition ( cc_compiler_str, strlen ( buf ) );
   XtAddCallback ( cc_compiler_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

   XtVaCreateManagedWidget ( "Non-X Link Libraries:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );
    

   cc_link_lib_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( cc_link_lib_str_num, buf );
   XmTextFieldSetString ( cc_link_lib_str, buf ) ;
   XmTextFieldSetInsertionPosition ( cc_link_lib_str, strlen ( buf ) );
   XtAddCallback ( cc_link_lib_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

   XtVaCreateManagedWidget ( "X Link Libraries:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );
    
   cc_Xlink_lib_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( cc_Xlink_lib_str_num, buf );
   XmTextFieldSetString ( cc_Xlink_lib_str, buf ) ;
   XmTextFieldSetInsertionPosition ( cc_Xlink_lib_str, strlen ( buf ) );
   XtAddCallback ( cc_Xlink_lib_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

  Manage_NewOption_Dialog;

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


/*******************************   Provers   ***********************************/

Widget provers_str;
Widget max_fwd_hyp_str;
int POG_NewOption_pd;

void
Cre_NewOption_POG_CB ( widget, but_num )
Widget widget;
int but_num;
{
  POG_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
CheckAndSet_max_fwd_ctr_auto_prf ( ss )
char * ss;
{
  int i, n;

  i = 0;
  /*** remove initial ws ***/
  while ( ( ss [ i ] == ' ' )  ||
          ( ss [ i ] == '\n' ) ||
          ( ss [ i ] == '\t' )    ) { i++; }
  if ( ( ss [ i ] < '0' ) || ( ss [ i ] > '9' ) ) {
    if ( ( curr_env !=  ipr_pob_env ) && ( curr_env !=  ipr_lem_env ) ) {
      sprintf ( buf, "\n  %s is not a number\n\n  Max generated Hypothesis settings not changed\n", ss );
      DisplayCurrWinText ( buf );
    }  
    Popup_Info ( "Not a number - max generated Hypothesis settings not changed" );
  }
  else {
    n = 0;
    while ( ( ss [ i ] >= '0' ) && ( ss [ i ] <= '9' ) ) {
      n = ( 10 * n ) + ss [ i ] - '0';
      i++;
    }
  /*** remove final ws ***/
    while ( ( ss [ i ] == ' ' )  ||
            ( ss [ i ] == '\n' ) ||
            ( ss [ i ] == '\t' )    ) { i++; }
    if ( ss [ i ] != '\0' ) {
      if ( ( curr_env !=  ipr_pob_env ) && ( curr_env !=  ipr_lem_env ) ) {
        sprintf ( buf, "\n  %s is not a number\n\n  Max generated Hypothesis settings not changed\n", ss );
        DisplayCurrWinText ( buf );    
      }
      Popup_Info ( "Not a number - max generated Hypothesis settings not changed" );
    }
    else {
      max_fwd_ctr_auto_prf = n;
/***
printf ( "  just set: max_fwd_ctr_auto_prf=%d\n",  max_fwd_ctr_auto_prf );
***/
      modIth_flags ( Provers_max_fwd_Option_num, max_fwd_ctr_auto_prf );
      WriteBmfh ();
    }
  }
}

void
Cre_NewOption_Process_Provers ()
{
  char * text;
  int i, rr;
  char buf [ 150 ];  /* don't want the global buf */

  modIth_flags ( POG_Option_num, POG_NewOption_pd );
  WriteBpog ();

  text = XmTextFieldGetString ( max_fwd_hyp_str );
  CheckAndSet_max_fwd_ctr_auto_prf ( text );
  XtFree ( text );

  text = XmTextFieldGetString ( provers_str );
  strcpy ( buf, text );
  XtFree ( text );
  i = strlen ( buf );
  if ( i ) i--;
  while ( i && ( buf [ i ] == ' ' ) ) {
    buf [ i ] = '\0';
    i--;
  }
  if ( strcmp ( buf, " " ) == 0 ) buf [ 0 ] = '\0';
  Store_String ( &rr, provers_str_num, buf );
  chk_rep ( rr, 183 );

  /*** check for existence ***/
  if ( buf [ 0 ] != '\0' ) {
    struct stat stat_buf;
    FILE * pmd;
    int i, j;
    if ( stat ( buf, &stat_buf ) == -1 ) { /* buf not exist */
      pmd = fopen ( buf, "w" );
      if ( pmd == NULL ) {
        sprintf ( str_buf, "Can't open \"%s\" for writing", buf );
        Popup_Minor_Err ( top_level, str_buf );
      }
      else {
        i = strlen ( buf );
        while ( i && ( buf [ i ] != '/' ) ) { i--; }
        j = 0;
        if ( i && ( buf [ i ] != '\0' ) ) {
          i++;
          while ( buf [ i ] != '\0' ) {
            buf [ j++ ] = buf [ i++ ];
          }
          buf [ j ] = '\0';
        }
        fprintf ( pmd, "PROOFMETHOD %s IS\n\n  THEORY UsersTheory IS\n\n    ?\n\n  END\n\n  &\n\n  THEORY FwdUsersTheory IS\n\n    ?\n\n  END\n\nEND\n\nDEFINITIONS\n\n  ?\n\nINCLUSIONS\n\n  ?\n", buf );
        fclose ( pmd );
        sprintf ( str_buf, "Template PROOFMETHOD %s created", buf );
        Popup_Info ( str_buf );
      }
    }
  }
}

void
Popup_NewProvers_Options_Dialog ()
{
  Make_NewOption_Dialog_Declarations;
  Widget w;
  XmString xstr, xstr1, xstr2;
  int i, n;
  char buf [ 150 ];  /* don't want the global buf */

  Cre_NewOption_Dialog ( & dialog, & dialog_form, 125,
                      & label, & B_logo,
                      & sep,
                      & form_scroll, & form, & left_rc, & right_rc,
                      & och_form, & och_o, & och_c, & och_h,
                      "Provers Options",
                      & coord_data,
                      & help_data,
                      OPTIONS_PROVERS
                    );

   help_data.type   = DIALOG_HELP;
   help_data.width  = 450;
   help_data.height = 300;  
   help_data.text   = "\
The maximum number of generated hypothses in one DED (forward\n\
proof step) may be set; large (>250) settings may compromise efficiency.\n\n\
Either all proof obligations, or just those which are non-trivial may be \n\
generated; see Top Bar Help: Main->ProofObligations.\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes  Options.\n\n\
A Global PROOFMETHOD file may be specified (as a string)\n\
for subsequent inclusion in other PROOFMETHODs\neg. \"/home/fred/BProof/Global.pmd\"\nMaximum string length: 150.";

   XtVaCreateManagedWidget ( "Max Generated Hypotheses:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   max_fwd_hyp_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   sprintf ( buf, "%d", max_fwd_ctr_auto_prf );
   XmTextFieldSetString ( max_fwd_hyp_str, buf );
   XmTextFieldSetInsertionPosition ( max_fwd_hyp_str, strlen ( buf ) );
   XtAddCallback ( max_fwd_hyp_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

   XtVaCreateManagedWidget ( "POGenerator Setting:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( " generate non-trivial obligations ", charset );
   xstr2 =  XmStringCreateLtoR ( " generate all obligations ", charset );

   valIth_flags ( & POG_NewOption_pd, POG_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
        POG_NewOption_pd, Cre_NewOption_POG_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );

   XtVaCreateManagedWidget ( "Global PROOFMETHOD file:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   provers_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( provers_str_num, buf );
   i = strlen ( buf );
   if ( i ) i--;
   while ( i && ( buf [ i ] == ' ' ) ) {
     buf [ i ] = '\0';
     i--;
   }
  if ( strcmp ( buf, " " ) == 0 ) buf [ 0 ] = '\0';
   XmTextFieldSetString ( provers_str, buf ) ;
   XmTextFieldSetInsertionPosition ( provers_str, strlen ( buf ) );
   XtAddCallback ( provers_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

  Manage_NewOption_Dialog;

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

/*******************************   Interface   ***********************************/

int Interface_NewOption_pd;

void
Cre_NewOption_Interface_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Interface_NewOption_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_Process_Interface ()
{
  int n;
  
  valIth_flags ( &n, Interface_Option_num );
  if ( n != Interface_NewOption_pd ) {
    modIth_flags ( Interface_Option_num, Interface_NewOption_pd );
    WriteBplf ();                   /* prog lang options */
    DisplayChanged = 1;
    ResetAllInterfaces ();
    RecompileLibCodeFiles ( 1 );
    ResetAllCode ( 0 );
    DisplayCurrentEnv ();
  }
}

void
Popup_NewInterface_Options_Dialog ()
{
  Make_NewOption_Dialog_Declarations;
  Widget w;
  XmString xstr, xstr1, xstr2;

  Cre_NewOption_Dialog ( & dialog, & dialog_form, 100,
                      & label, & B_logo,
                      & sep,
                      & form_scroll, & form, & left_rc, & right_rc,
                      & och_form, & och_o, & och_c, & och_h,
                      "Interface Option",
                      & coord_data,
                      & help_data,
                      OPTIONS_INTERFACE
                    );

   help_data.type   = DIALOG_HELP;
   help_data.width  = 475;
   help_data.height = 150;  
   help_data.text   = "\
The Interface may be set to `Motif' (requiring the Motif header files, eg.\n\
Xm/XmAll.h) or Non-Motif (when a teletype interface will be generated).\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes      Options.";  

   XtVaCreateManagedWidget ( "Interface type:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( " Motif ", charset );
   xstr2 =  XmStringCreateLtoR ( " Non-Motif ", charset );

   valIth_flags ( &Interface_NewOption_pd, Interface_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Interface_NewOption_pd, Cre_NewOption_Interface_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

   XmStringFree ( xstr );
   XmStringFree ( xstr1 );
   XmStringFree ( xstr2 );

  Manage_NewOption_Dialog;

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

/******************************   Bell Option   *******************************/

int Bell_pd;

void
Cre_NewOption_Bell_CB ( widget, but_num )
Widget widget;
int but_num;
{
  Bell_pd = but_num;
  XmProcessTraversal ( XtParent ( XtParent ( XtParent ( widget ) ) ),
                                                XmTRAVERSE_NEXT_TAB_GROUP );
}

void
Cre_NewOption_Process_Bell ()
{
  modIth_flags ( Bell_Option_num, Bell_pd );
  bell_option = Bell_pd;
}

void
Popup_NewBell_Options_Dialog ()
{
  Make_NewOption_Dialog_Declarations;
  Widget w;
  XmString xstr, xstr1, xstr2;

  Cre_NewOption_Dialog ( & dialog, & dialog_form, 100,
                      & label, & B_logo,
                      & sep,
                      & form_scroll, & form, & left_rc, & right_rc,
                      & och_form, & och_o, & och_c, & och_h,
                      "Bell Option",
                      & coord_data,
                      & help_data,
                      OPTIONS_BELL
                    );

   help_data.type   = DIALOG_HELP;
   help_data.width  = 350;
   help_data.height = 150;  
   help_data.text   = "\
The Bell may be set to ring on completion of jobs.\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes      Options.";  

   XtVaCreateManagedWidget ( "Ring bell on completion:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   xstr =  XmStringCreateLtoR ( "", charset );
   xstr1 =  XmStringCreateLtoR ( "         off ", charset );
   xstr2 =  XmStringCreateLtoR ( " on ", charset );

   valIth_flags ( &Bell_pd, Bell_Option_num );
   w = XmVaCreateSimpleOptionMenu ( right_rc, "PullDown",
       xstr, 0,
       Bell_pd, Cre_NewOption_Bell_CB,
       XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
       XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
       XmNshadowThickness,        0,
       /* 
       XmNmarginWidth,            0,
       XmNmarginHeight,           0,
       */
       XmNdefaultButtonShadowThickness,     1,
       XmNhighlightThickness,     1,
       XmNnavigationType,         XmTAB_GROUP,
       NULL);
   XtManageChild ( w );

  XmStringFree ( xstr );
  XmStringFree ( xstr1 );
  XmStringFree ( xstr2 );

  Manage_NewOption_Dialog;

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );

}

/**************************   AnimateScripts Option   **************************/

Widget optional_utility1_str,
       optional_utility2_str,
       optional_utility3_str,
       optional_utility4_str,
       optional_utility5_str;

void
Cre_NewOption_Process_AnimateScripts ()
{
  char * text;
  int rr;

  text = XmTextFieldGetString ( optional_utility1_str );
  Store_String ( &rr, optional_utility1_str_num, text );
  chk_rep ( rr, 191 );
  XtFree ( text );

  text = XmTextFieldGetString ( optional_utility2_str );
  Store_String ( &rr, optional_utility2_str_num, text );
  chk_rep ( rr, 192 );
  XtFree ( text );

  text = XmTextFieldGetString ( optional_utility3_str );
  Store_String ( &rr, optional_utility3_str_num, text );
  chk_rep ( rr, 193 );
  XtFree ( text );

  text = XmTextFieldGetString ( optional_utility4_str );
  Store_String ( &rr, optional_utility4_str_num, text );
  chk_rep ( rr, 194 );
  XtFree ( text );

  text = XmTextFieldGetString ( optional_utility5_str );
  Store_String ( &rr, optional_utility5_str_num, text );
  chk_rep ( rr, 195 );
  XtFree ( text );

  Re_Cre_Top_Bar_Utils_Pulldown ();
}

void
Popup_NewAnimateScripts_Options_Dialog ()
{
  Make_NewOption_Dialog_Declarations;
  Widget w;
  char buf [ 150 ];  /* don't want the global buf */

  Cre_NewOption_Dialog ( & dialog, & dialog_form, 175,
                      & label, & B_logo,
                      & sep,
                      & form_scroll, & form, & left_rc, & right_rc,
                      & och_form, & och_o, & och_c, & och_h,
                      "Optional Utilities",
                      & coord_data,
                      & help_data,
                      OPTIONS_OPTIONAL_UTILITIES
                    );

   help_data.type   = DIALOG_HELP;
   help_data.width  = 425;
   help_data.height = 200;  
   help_data.text   = "\
Each string may contain the location of a utility, which may\n\
then be executed through TopBar Utils -> Optional Utility\neg. $BKIT/BProcessInfo\nMaximum string length: 150.\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes      Options.";  

   XtVaCreateManagedWidget ( "Optional Utility 1:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   optional_utility1_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( optional_utility1_str_num, buf );
   XmTextFieldSetString ( optional_utility1_str, buf ) ;
   XmTextFieldSetInsertionPosition ( optional_utility1_str, strlen ( buf ) );
   XtAddCallback ( optional_utility1_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

   XtVaCreateManagedWidget ( "Optional Utility 2:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   optional_utility2_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( optional_utility2_str_num, buf );
   XmTextFieldSetString ( optional_utility2_str, buf ) ;
   XmTextFieldSetInsertionPosition ( optional_utility2_str, strlen ( buf ) );
   XtAddCallback ( optional_utility2_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

   XtVaCreateManagedWidget ( "Optional Utility 3:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   optional_utility3_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( optional_utility3_str_num, buf );
   XmTextFieldSetString ( optional_utility3_str, buf ) ;
   XmTextFieldSetInsertionPosition ( optional_utility3_str, strlen ( buf ) );
   XtAddCallback ( optional_utility3_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

   XtVaCreateManagedWidget ( "Optional Utility 4:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   optional_utility4_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( optional_utility4_str_num, buf );
   XmTextFieldSetString ( optional_utility4_str, buf ) ;
   XmTextFieldSetInsertionPosition ( optional_utility4_str, strlen ( buf ) );
   XtAddCallback ( optional_utility4_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

   XtVaCreateManagedWidget ( "Optional Utility 5:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   optional_utility5_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( optional_utility5_str_num, buf );
   XmTextFieldSetString ( optional_utility5_str, buf ) ;
   XmTextFieldSetInsertionPosition ( optional_utility5_str, strlen ( buf ) );
   XtAddCallback ( optional_utility5_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

  Manage_NewOption_Dialog;

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}


/******************************   Teamlib Option   *******************************/

Widget teamlib_str;

/*
void
Cre_NewOption_Process_Teamlib ()
{
  char * text;
  int rr;

  text = XmTextFieldGetString ( teamlib_str );
  Store_String ( &rr, teamlib_str_num, text );
  chk_rep ( rr, 184 );
  XtFree ( text );
}

void
Popup_NewTeamlib_Options_Dialog ()
{
  Make_NewOption_Dialog_Declarations;
  Widget w;

  Cre_NewOption_Dialog ( & dialog, & dialog_form, 100,
                      & label, & B_logo,
                      & sep,
                      & form_scroll, & form, & left_rc, & right_rc,
                      & och_form, & och_o, & och_c, & och_h,
                      "Teamlib Option",
                      & coord_data,
                      & help_data,
                      OPTIONS_TEAMLIB
                    );

   help_data.type   = DIALOG_HELP;
   help_data.width  = 375;
   help_data.height = 175;  
   help_data.text   = "\
The string should contain the location of the team library\neg. /home/fred/BTeamLib\nMaximum string length: 150.\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes      Options.";  

   XtVaCreateManagedWidget ( "Teamlib directory:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   teamlib_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( teamlib_str_num, buf );
   XmTextFieldSetString ( teamlib_str, buf ) ;
   XmTextFieldSetInsertionPosition ( teamlib_str, strlen ( buf ) );
   XtAddCallback ( teamlib_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

  Manage_NewOption_Dialog;

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}
*/

/*********************   SourceControl Option   ***************************/

Widget source_control_str;

void
Cre_NewOption_Process_SourceControl ()
{
  char * text;
  int rr;

  text = XmTextFieldGetString ( source_control_str );
  Store_String ( &rr, source_control_str_num, text );
  chk_rep ( rr, 184 );
  XtFree ( text );
}

void
Popup_NewSourceControl_Options_Dialog ()
{
  Make_NewOption_Dialog_Declarations;
  Widget w;
  char buf [ 150 ];  /* don't want the global buf */

  Cre_NewOption_Dialog ( & dialog, & dialog_form, 100,
                      & label, & B_logo,
                      & sep,
                      & form_scroll, & form, & left_rc, & right_rc,
                      & och_form, & och_o, & och_c, & och_h,
                      "Source Control Option",
                      & coord_data,
                      & help_data,
                      OPTIONS_SOURCE_CONTROL
                    );

   help_data.type   = DIALOG_HELP;
   help_data.width  = 375;
   help_data.height = 175;  
   help_data.text   = "\
The string should contain the location of the team library\neg. /home/fred/BSourceControl\nMaximum string length: 150.\n\n\
For a full description of Options, see Top Bar Help:\n\
TopBar->Set Tool Attributes      Options.";  

   XtVaCreateManagedWidget ( "Source Control directory:",
       xmLabelWidgetClass,             left_rc,
       XmNrightPosition,               1,
       XmNrightOffset,                 3,
       XmNalignment,                   XmALIGNMENT_END,
       NULL );

   source_control_str = XtVaCreateManagedWidget ( "InputText",
       xmTextFieldWidgetClass,         right_rc,
       XmNtraversalOn,                 True,
       XmNmarginWidth,                 3,
       XmNmarginHeight,                3,
       NULL );
   Retrieve_String ( source_control_str_num, buf );
   XmTextFieldSetString ( source_control_str, buf ) ;
   XmTextFieldSetInsertionPosition ( source_control_str, strlen ( buf ) );
   XtAddCallback ( source_control_str, XmNactivateCallback, 
           ( XtCallbackProc ) Anm_Multi_Input_Text_CB,
           NULL );

  Manage_NewOption_Dialog;

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );
}

/*****************************************************************************/



Cre_Arrow_Pixmaps ()
{
  sprintf ( str_buf, "%s/BHELP/r_arr.xpm", BKIT_path );
  htx_pixmap_right = XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( htx_pixmap_right == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create right arrow pixmap" );
    printf ( "\n  Can't create right arrow pixmap\n" );
  }

  sprintf ( str_buf, "%s/BHELP/l_arr.xpm", BKIT_path );
  htx_pixmap_left = XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( htx_pixmap_left == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create left arrow pixmap" );
    printf ( "\n  Can't create left arrow pixmap\n" );
  }

  sprintf ( str_buf, "%s/BHELP/lb_arr.xpm", BKIT_path );
  htx_pixmap_left_big = XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( htx_pixmap_left == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create left2 arrow pixmap" ); 
    printf("\n  Can't create left2 arrow pixmap\n" );
  }
}


void
UseBuiltInOptions ()
{
  int rr;
  char editor[250];
  char browser[250];

  getEditorOption(editor);
  getBrowserOption(browser);

  DisplayCurrWinText ( "\n    BMotif: can't open .BToolkitrc defaults Options\n" );
  DisplayCurrWinText ( "\n  Using built-in defaults (see TopBar Help for Options)\n\n" );
  modIth_flags ( Bell_Option_num, Bell_Option_off );
  bell_option = Bell_Option_off;
  /* CHANGED: */
  /*Store_String ( &rr, editor_str_num, "xedit -geometry 550x564-1-1" );*/

  Store_String ( &rr, editor_str_num, editor );
  /* */
  chk_rep ( rr, 111 );
  /* CHANGED: */
  /*Store_String ( &rr, pmd_editor_str_num, "xedit -geometry 500x400-1-1" );*/
  
  Store_String ( &rr, pmd_editor_str_num, editor );
  /* */
  chk_rep ( rr, 121 );
  /* CHANGED: */
  /*sprintf ( str_buf, "%s/BLIB/Bnetscape", BKIT_path ); */
  /* sprintf ( str_buf, "Bbrowser"); */  
  /* Store_String ( &rr, htx_viewer_str_num, str_buf ); */
  
  Store_String ( &rr, htx_viewer_str_num, browser ); 
  /* */
  chk_rep ( rr, 342 );
  Store_String ( &rr, dvi_screen_str_num, "xdvi -expert -paper a4 -s 9" );
  chk_rep ( rr, 349 );
  sprintf ( str_buf, "Bprintdvi");
  Store_String ( &rr, dvi_print_str_num, str_buf );
  chk_rep ( rr, 350 );
  Store_String ( &rr, cc_Xlink_lib_str_num, "-lXm -lXt -lX11 -lXext -lXp" );
  chk_rep ( rr, 343 );
  Store_String ( &rr, shell_str_num, "xterm" );
  chk_rep ( rr, 344 );
  Store_String ( &rr, cc_compiler_str_num, "gcc -pipe -I/usr/X11R6/include -L/usr/X11R6/lib" );
  chk_rep ( rr, 345 );
  if ( strcmp ( platform, "Solaris" ) == 0 ) {
    /* CHANGED: already catered for in getEditorOption */
    /*Store_String ( &rr, editor_str_num, "textedit -Wp 501 401 -Ws 632 500" );*/
    chk_rep ( rr, 141 );
    /* Store_String ( &rr, pmd_editor_str_num, "textedit" ); */
    chk_rep ( rr, 141 );
    /* */
    Store_String ( &rr, cc_compiler_str_num, "cc -I/usr/dt/include -I/usr/openwin/include -L/usr/openwin/lib -L/usr/dt/lib" );
    chk_rep ( rr, 346 );
    Store_String ( &rr, cc_Xlink_lib_str_num, "-lXm -lXt -lX11 -lgen" );
    chk_rep ( rr, 347 );
    Store_String ( &rr, shell_str_num, "dtterm" );
    chk_rep ( rr, 348 );
  }
  modIth_flags ( POG_Option_num, 0 );
  modIth_flags ( Prog_Language_Option_num, Prog_Language_Option_C );
}

void
DefaultSettings ()
{
  char *getenv(), *name;
  FILE * optfile;

  name = getenv ( "HOME" );
  
  if ( name == NULL ) {
    Popup_Info ( " Environment variable HOME not set " );
    DisplayCurrWinText ( "\n  Environment variable HOME not set\n" );
    UseBuiltInOptions ();
  }
  else {
    strcpy ( buf, name );
    strcat ( buf, "/.BToolkitrc" );
    optfile = fopen ( buf, "r" );
    if ( optfile == NULL ) {
      UseBuiltInOptions ();
    }
    else {
      fclose ( optfile );
      RestoreDefaultOptions_Proceed ( 0 );
    }
  }
}


InitialiseFlagsAndStrings ()
{
  int ii, jj, kk, rr, Base_Seqstr_tok;

  clear_flags ();
  
  push_flags ( &rr, False );  /* 1. hid_LIB_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, False );  /* 2. hid_gen_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, TRUE );  /* 3. Remake_pog_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, TRUE );  /* 4. Remake_apr_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, TRUE );  /* 5. Remake_ppf_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, TRUE );  /* 6. Remake_dmu_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, TRUE );  /* 7. Remake_trl_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, TRUE );  /* 8. Remake_lnk_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, TRUE );  /* 9. Remake_itf_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, False );  /* 10. Preserve_Editor_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, Interface_Option_Motif );  /* 11. Interface_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, 2 );  /* 12. Ipr_Prf_Level_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, TRUE );  /* 13. DMU_Labels_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, TRUE );  /* 14. DMU_ClIndex_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, TRUE );  /* 15. DMU_CoIndex_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, TRUE );  /* 16. DMU_GIndex_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, Prog_Language_Option_C );/* 17. Prog_Language_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, DMU_Language_Option_LaTeX2e );  /* 18. DMU_Language_Option_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, 10 );  /* 19. Point_Size_FOption_num */
  chk_rep ( rr, 62 );

  push_flags ( &rr, False );  /* 20. DMU_eps_Option_num - not used
                                     BUT LEAVE IN PLACE - 75 FLAGS MUST EXIST */
  chk_rep ( rr, 62 );

  ii = rand ();
  ii = ( ( ii % Option_2324_Max ) + Option_25_Max ); /* 21 */
  push_flags ( &rr, ii );
  chk_rep ( rr, 62 );
/***
printf ( "Initially %5d\n", ii );
***/
  ii = rand ();
  ii = ( ( ii % Option_2324_Max ) + Option_25_Max ); /* 22 */
  push_flags ( &rr, ii );
  chk_rep ( rr, 62 );
/***
printf ( "Initially %5d\n", ii );
***/
  ii = rand ();
  ii = ( ( ii % Option_2324_Max ) + Option_25_Max ); /* 23 */
  push_flags ( &rr, ii );
  chk_rep ( rr, 62 );
/***
printf ( "Initially %5d\n", ii );
***/
  ii = rand ();
  ii = ( ( ii % Option_2324_Max ) + Option_25_Max ); /* 24 */
  push_flags ( &rr, ii );
  chk_rep ( rr, 62 );
/***
printf ( "Initially %5d\n", ii );
***/
  ii = rand ();
  ii = ( ( ii % Option_2324_Max ) + Option_25_Max ); /* 25 */
  push_flags ( &rr, ii );
  chk_rep ( rr, 62 );
/***
printf ( "Initially %5d\n", ii );
***/

  /***
  initialise extra 50 flags to 0 (75 altogether)
  ***/
  for ( ii = 0; ii < 50 ; ii++ ) {
    push_flags ( &rr, 0 );
    chk_rep ( rr, 10001 + ii );
  }

  /***
  Set Provers_max_fwd_Option to 250
  ***/
  modIth_flags ( Provers_max_fwd_Option_num, 250 );

  /***
  create seq of 50 empty strings (50 altogether)
  ***/
  make_Seqstr ( &rr, &Base_Seqstr_tok );
  chk_rep ( rr, 123 );
  modIth_flags ( Base_Seqstr_tok_num, Base_Seqstr_tok );
  clear_seqstr ( Base_Seqstr_tok );
  for ( ii = 0; ii < 50 ; ii++ ) {
    make_String ( &rr, &jj );
    chk_rep ( rr, 20001 + ii );
    push_seqstr ( &rr, Base_Seqstr_tok, jj );
    chk_rep ( rr, 30001 + ii );
  }

  DefaultSettings ();

}



#ifdef WWW_VERSION

#define WWW_intro_flag   0
#define WWW_prelim_flag  1
#define WWW_READ_ME_flag 2

/**************************************************
          WWW init procedures
***************************************************/

void
Popup_WWW_init_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  FILE * ReadMe;
  struct stat statReadMe;
  void Popup_WWW_init ();
  char * text;
  int i = * ( int * ) client_data;

  XtPopdown ( XtParent ( XtParent ( XtParent ( widget ) ) ) );
  XmUpdateDisplay ( XtParent ( XtParent ( XtParent ( widget ) ) ) );
  XtDestroyWidget ( XtParent ( XtParent ( XtParent ( widget ) ) ) );

  if ( i == 0 ) { /* WWW_intro_flag */

    Popup_WWW_init ( WWW_prelim_flag, B_WWW_prelim_text );

  }

  else { /* WWW_prelim_flag */

    if ( stat ( "READ_ME", &statReadMe ) != 0 ) {
      DisplayCurrWinText ( "\n  BMotif: can't open READ_ME\n" );
      return;
    }
    ReadMe = fopen ( "READ_ME", "r" );
    if ( ReadMe == NULL ) {
      DisplayCurrWinText ( "\n  BMotif: can't open READ_ME\n" );
      return;
    }
    if ( ! ( text = XtMalloc ( ( unsigned ) statReadMe.st_size + 1 ) ) ) {
      DisplayCurrWinText ( "\n  Can't allocate enough space for READ_ME\n" );
      return;
    }
    if ( ! fread ( text, sizeof ( char ), statReadMe.st_size + 1, ReadMe ) ) {
      DisplayCurrWinText ( "\n  May not have read entire READ_ME\n" );
    }
    text [ statReadMe.st_size ] = 0;
    fclose ( ReadMe );
  
    Popup_WWW_init ( WWW_READ_ME_flag, text );

  }
}

void
Popup_WWW_init ( flag, text )
int flag;
char * text;
{
  Widget help_dialog, help_form,
         help_scroll, help_text,
         sep, o_o,
         o_form;

  /***
  create the dialog
  ***/
  help_dialog = XtVaCreatePopupShell ( "HelpDialog",
      xmDialogShellWidgetClass,  top_level,
      NULL );
  help_form = XtVaCreateWidget ( "HelpDialog",
      xmFormWidgetClass,         help_dialog,
      XmNdefaultPosition,        False,  
      NULL );

  if ( flag == WWW_intro_flag || flag == WWW_prelim_flag ) {

    XtVaSetValues ( help_form,
      XmNwidth,                  B_WWW_intro_text_width,
      XmNheight,                 B_WWW_intro_text_height,
      XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
      NULL );

    if ( flag == WWW_prelim_flag ) {
      XtVaSetValues ( help_form,
          XmNdialogStyle,            XmDIALOG_MODELESS,
          NULL );
    }

    /***
    create separator
    ***/
    sep = XtVaCreateManagedWidget ( "HelpDialog", 
        xmSeparatorGadgetClass,  help_form,
        XmNleftAttachment,       XmATTACH_FORM,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNbottomAttachment,     XmATTACH_FORM,
        XmNbottomOffset,         48,
        NULL );

    /***
    create Form for push button
    ***/
    o_form = XtVaCreateManagedWidget ( "ButtonLabel",
        xmFormWidgetClass,       help_form,
        XmNleftAttachment,       XmATTACH_FORM,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNtopAttachment,        XmATTACH_WIDGET,
        XmNtopWidget,            sep,
        XmNtopOffset,            5,
        XmNforeground,           red,
        NULL );

    /***
    create push button
    ***/
    o_o = XtVaCreateManagedWidget ( "Dismiss", 
        xmPushButtonGadgetClass, o_form,
        XmNleftAttachment,       XmATTACH_FORM,
        XmNleftOffset,           15,
        XmNheight,               25,
        XmNwidth,                57,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   0,
        NULL );

    if ( flag == WWW_intro_flag ) {
      XtAddCallback ( o_o, XmNactivateCallback,
               ( XtCallbackProc ) Popup_WWW_init_CB,
               ( XtPointer ) & c_arr [ 0 ] );
    }
    else {
    XtAddCallback ( o_o, XmNactivateCallback,
             ( XtCallbackProc ) Popup_WWW_init_CB,
             ( XtPointer ) & c_arr [ 1 ] );
    }

    /***
    create ScrolledWindow
    ***/
    help_scroll = XtVaCreateWidget ( "HelpDialog",
        xmScrolledWindowWidgetClass,    help_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNbottomAttachment,            XmATTACH_WIDGET,
        XmNbottomWidget,                sep,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNmarginWidth,                 0,
        XmNmarginHeight,                0,
        NULL );
  }
  else { /* flag == WWW_READ_ME_flag */

    XtVaSetValues ( help_form,
      XmNwidth,                  500,
      XmNheight,                 400,
      XmNdialogStyle,            XmDIALOG_MODELESS,
      NULL );

    /***
    create ScrolledWindow
    ***/
    help_scroll = XtVaCreateWidget ( "HelpDialog",
        xmScrolledWindowWidgetClass,    help_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNbottomAttachment,            XmATTACH_FORM,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNmarginWidth,                 0,
        XmNmarginHeight,                0,
        NULL );
  }

  /***
  create Text
  ***/
  help_text = XtVaCreateManagedWidget ( "HelpDialog",
      xmTextWidgetClass,         help_scroll,
      XmNcursorPositionVisible,  False,
      XmNeditable,               False,
      XmNeditMode,               XmMULTI_LINE_EDIT,
      XmNmarginWidth,            10,
      XmNmarginHeight,           10,
      XmNborderWidth,            0,
      XmNshadowThickness,        0,
      XmNforeground,             red,
      NULL );
  XmTextSetString ( help_text, text );

  /***
  manage children
  ***/
  if ( flag == WWW_intro_flag || flag == WWW_prelim_flag ) {
    XtManageChild ( o_o );
    XtManageChild ( o_form );
    XtManageChild ( sep );
  }
  XtManageChild ( help_text );
  XtManageChild ( help_scroll );
  XtManageChild ( help_form );

  /***
  set colour & position the Form
  ***/
  if ( flag == WWW_intro_flag || flag == WWW_prelim_flag ) {
    XtVaSetValues ( help_text,
      XmNforeground,             red,
      NULL );
/*
    PositionWidgetRelMainWin ( help_dialog,
            B_WWW_intro_text_left_offset, B_WWW_intro_text_top_offset );
*/
  }
  else {
    Dimension top_level_w;
    XtVaSetValues ( help_text,
      XmNforeground,             blue,
      NULL );
    XtVaGetValues ( top_level, 
        XmNwidth,         &top_level_w,
        NULL );
/*
    PositionWidgetRelMainWin ( help_dialog,
            ( int ) top_level_w + 10, 1 );  
*/  
  }

  /***
  popup dialog
  ***/
  XtPopup ( help_dialog, XtGrabNone );
  if ( flag == WWW_intro_flag || flag == WWW_prelim_flag ) {
    XmUpdateDisplay ( o_o );
    XmUpdateDisplay ( o_form );
    XmUpdateDisplay ( sep );
  }
  XmUpdateDisplay ( help_text );
  XmUpdateDisplay ( help_scroll );
  XmUpdateDisplay ( help_form );
  XmUpdateDisplay ( help_dialog );
}

#endif /* WWW_VERSION */

void
Bpda_file_error ( file, mode )
char * file;
char * mode;
{
  printf ( "\n  BMotif: can't open %s for %s\n\n", file, mode );
  Kill_bplatform_and_exit ( 1, 0 );
}

/* from  Upgrade4.xToWWW1.x.c */
int
check_Bpda_type ( file )
char * file;
{
  FILE * file_in;
  int c, i, t;

  file_in = fopen ( file, "r" );
  if ( file_in == NULL ) {
    Bpda_file_error ( file, "reading" );
  }

  /***
  header (checked in Restore_CfgDepBase/Restore_n_CfgDepBase)
  ***/
  for ( i = 0 ; i < ( int ) strlen ( cur_hdr_string ) ; i++ ) {
    c = getc ( file_in );
  }

/*
"header_string n1 n2 n3 n4 X X X X X 0 0 1 n5 n6 n7 n8 0 0 1 0 1 ......."
where length X X X X X = n1+(7*n2)+(49*n3)+(343*n4)+15
      length Y Y Y Y Y = n5+(7*n6)+(49*n7)+(343*n8)+23
*/

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
    fclose ( file_in );
    return ( 1 );
  }
  else if ( c != 0 ) {
    fclose ( file_in );
    return ( 2 );
  }

  c = getc ( file_in );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 3 );
  }
  else if ( c != 0 ) {
    fclose ( file_in );
    return ( 4 );
  }

  c = getc ( file_in );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 5 );
  }
  else if ( c != 1 ) {
    fclose ( file_in );
    return ( 6 );
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

  if ( c == EOF ) {
    fclose ( file_in );
    return ( 7 );
  }
  else if ( c != 0 ) {
    fclose ( file_in );
    return ( 8 );
  }

  c = getc ( file_in );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 9 );
  }
  else if ( c != 0 ) {
    fclose ( file_in );
    return ( 10 );
  }

  c = getc ( file_in );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 11 );
  }
  else if ( c != 1 ) {
    fclose ( file_in );
    return ( 12 );
  }

  c = getc ( file_in );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 13 );
  }
  else if ( c != 0 ) {
    fclose ( file_in );
    return ( 14 );
  }

  c = getc ( file_in );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 15 );
  }
  else if ( c != 1 ) {
    fclose ( file_in );
    return ( 16 );
  }

  fclose ( file_in );

  return ( 0 );
}


/* from  Upgrade4.xToWWW1.x.c */
int
check_Bpdan_type ( file )
char * file;
{
  FILE * file_in;
  int c, i, t;

  file_in = fopen ( file, "r" );
  if ( file_in == NULL ) {
    Bpda_file_error ( file, "reading" );
  }

  /***
  header (checked in Restore_CfgDepBase/Restore_n_CfgDepBase)
  ***/
  for ( i = 0 ; i < ( int ) strlen ( cur_hdr_string ) ; i++ ) {
    c = getc ( file_in );
  }

/*
"header_string n1 n2 n3 n4 X X X X X 0 0 1 n5 n6 n7 n8 0 0 1 0 1 ......."
where length X X X X X = n1+(7*n2)+(49*n3)+(343*n4)+15
      length Y Y Y Y Y = n5+(7*n6)+(49*n7)+(343*n8)+23
*/

  t = 0;
  c = getc ( file_in );
  c = ntohl ( c );
  t = t + ( int ) c; 
  c = getc ( file_in );
  c = ntohl ( c );
  t = t + ( 7 * ( int ) c ); 
  c = getc ( file_in );
  c = ntohl ( c );
  t = t + ( 49 * ( int ) c ); 
  c = getc ( file_in );
  c = ntohl ( c );
  t = t + ( 343 * ( int ) c ); 
  t = t + 15;

  i = 0;
  c = getc ( file_in );
  c = ntohl ( c );
  while ( i < ( int ) t && c != EOF ) {
    c = getc ( file_in );
    c = ntohl ( c );
    i++;
  }

  if ( c == EOF ) {
    fclose ( file_in );
    return ( 1 );
  }
  else if ( c != 0 ) {
    fclose ( file_in );
    return ( 2 );
  }

  c = getc ( file_in );
  c = ntohl ( c );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 3 );
  }
  else if ( c != 0 ) {
    fclose ( file_in );
    return ( 4 );
  }

  c = getc ( file_in );
  c = ntohl ( c );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 5 );
  }
  else if ( c != 1 ) {
    fclose ( file_in );
    return ( 6 );
  }

  t = 0;
  c = getc ( file_in );
  c = ntohl ( c );
  t = t + ( int ) c; 
  c = getc ( file_in );
  c = ntohl ( c );
  t = t + ( 7 * ( int ) c ); 
  c = getc ( file_in );
  c = ntohl ( c );
  t = t + ( 49 * ( int ) c ); 
  c = getc ( file_in );
  c = ntohl ( c );
  t = t + ( 343 * ( int ) c ); 
  t = t + 23;

  i = 0;
  c = getc ( file_in );
  c = ntohl ( c );
  while ( i < ( int ) t && c != EOF ) {
    c = getc ( file_in );
    c = ntohl ( c );
    i++;
  }

  if ( c == EOF ) {
    fclose ( file_in );
    return ( 7 );
  }
  else if ( c != 0 ) {
    fclose ( file_in );
    return ( 8 );
  }

  c = getc ( file_in );
  c = ntohl ( c );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 9 );
  }
  else if ( c != 0 ) {
    fclose ( file_in );
    return ( 10 );
  }

  c = getc ( file_in );
  c = ntohl ( c );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 11 );
  }
  else if ( c != 1 ) {
    fclose ( file_in );
    return ( 12 );
  }

  c = getc ( file_in );
  c = ntohl ( c );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 13 );
  }
  else if ( c != 0 ) {
    fclose ( file_in );
    return ( 14 );
  }

  c = getc ( file_in );
  c = ntohl ( c );
  if ( c == EOF ) {
    fclose ( file_in );
    return ( 15 );
  }
  else if ( c != 1 ) {
    fclose ( file_in );
    return ( 16 );
  }

  fclose ( file_in );

  return ( 0 );
}


/**************************************************
          WM_SAVE_YOURSELF
***************************************************/

/**************************************************
          main procedure
***************************************************/

void
SaveYourself ( dialog, client_data, call_data )
Widget dialog;
XtPointer client_data;
XtPointer call_data;
{
  FILE * Bpib;
  int c, pib;

  printf ( "\n  Panic Save (%d) !!!\n", ( * ( int * ) client_data ) ); fflush ( stdout );

  strcpy ( fifo_write_buf, "0:" );
  Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_PANIC_QUIT );
  Save_n_CfgDepBase ();
  DisplayCurrWinText ( "\n  B-Toolkit Terminated\n\n" );
  InvokeB ( without_XTerm, 1 );

  Bpib = fopen ( ".Bpib", "r" );
  if ( Bpib != NULL ) {
    c = getc ( Bpib );
    pib = 0;
    while ( c != EOF && c != '\n' )  {
      pib = ( pib * 10 ) + c - '0';
      c = getc ( Bpib );
    }
    fclose ( Bpib );
  }

  Bpib = fopen ( ".Bses", "w" );
  if ( Bpib != NULL ) {
     if ( ( * ( int * ) client_data ) == 1 )
       fprintf ( Bpib, "999999" );
     else
       fprintf ( Bpib, "0" );
    fclose ( Bpib );
  }

  

  kill ( pib, SIGKILL );  /* must be last */
  exit ( 1 );
}

int
main ( argc, argv )
int argc;
char *argv[];
{
  int i;
  Arg args [ 5 ];

  Atom WM_SAVE_YOURSELF;
  Atom WM_DELETE_WINDOW;

  struct stat stat_buf;
  int stat_buf_loaded;

  void SensitizeFrame ();

  brz = 0;

  started_from_cd = 0;

  initial_reattachment = 0;

  BOOSTER_link = 0;

  /***
  check whether an auto remake etc
  ***/
  auto_reset_and_remake = 0;
  auto_timer = 0;
  /* Manually set debug on or off */
  is_debug = 0;
 /*********************************/ 
  auto_reset = 0;
  if ( argc == 2 ) {
    if ( strcmp ( argv [ 1 ], ".r" ) == 0 ) {
      auto_reset_and_remake = 1;
      printf ( "\n                 Auto Reset&Remake Mode\n\n" );
    }
    else if ( strcmp ( argv [ 1 ], ".t" ) == 0 ) {
      auto_reset_and_remake = 1;
      auto_timer = 1;
      printf ( "\n                    Auto Timer Mode\n\n" );
    }
    else if ( strcmp ( argv [ 1 ], ".z" ) == 0 ) {
      auto_reset_and_remake = 1;
      auto_reset = 1;
      printf ( "\n                    Auto Reset Mode\n\n" );
    }
    else if ( strcmp ( argv [ 1 ], "debug" ) == 0 ) {
      struct stat statbuf;
      is_debug = 1;
      if ( stat ( "TMP", &statbuf ) != 0 ) {
        execute ( "mkdir TMP" );
      }
    }
  }
print_debug(1);

  CfgDepBase_is_Restored = 0;

print_debug(2);

  /***
  perform malloc for primary_string etc.
  ***/
  primary_string_len = 2500;
print_debug(3);
  primary_string    = ( char * ) malloc ( 2502 * sizeof ( char ) );
print_debug(4);
  secondary_string  = ( char * ) malloc ( 2502 * sizeof ( char ) );
print_debug(5);
  additional_string = ( char * ) malloc ( 2502 * sizeof ( char ) );
print_debug(6);

  /***
  initialise bstdout
  ***/
  bstdout = stdout;
print_debug(7);

  serv_addr [ 0 ] = '\0';
print_debug(8);

  Popup_Sel_flag = 0;
print_debug(9);
  up_and_running = 0;
print_debug(10);

  /***
  set up normal interrupts
  ***/
  act1.sa_handler = interrupt_SIGUSR1;
  sigemptyset ( & ( act1.sa_mask ) );
  act1.sa_flags = ( int ) 0;
/*
#ifdef SA_RESTART
printf ( "SA_RESTART\n" );
  act1.sa_flags |= SA_RESTART;
#endif
#ifdef SA_INTERRUPT
  act1.sa_flags &= ~SA_INTERRUPT;
printf ( "SA_INTERRUPT\n" );
#endif
*/
  sigaction ( SIGUSR1, & act1, NULL );
print_debug(11);

  act2.sa_handler = interrupt_SIGUSR2;
  sigemptyset ( & ( act2.sa_mask ) );
  act2.sa_flags = ( int ) 0;
#ifdef SA_RESTART
  act2.sa_flags |= SA_RESTART;
#endif
#ifdef SA_INTERRUPT
  act2.sa_flags &= ~SA_INTERRUPT;
#endif
  sigaction ( SIGUSR2,  & act2, NULL );
print_debug(12);


  /***
  set up crash interrupt
  ***/
  act3.sa_handler = interrupt_CRASH;
  sigemptyset ( & ( act3.sa_mask ) );
  act3.sa_flags = ( int ) 0;
print_debug(13);

  /***
  get platform
  ***/
  {
    struct utsname u_s;
    if ( uname ( & u_s ) == -1 ) {
      printf ( "\n\n             Problem with \"uname\"\n" );
      AbortedMsg ();
      Kill_bplatform_and_exit ( 0, 0 );
    }
    strcpy ( platform, u_s.sysname );
    strcpy ( nodename, u_s.nodename );
    platform [ 11 ] = '\0';
    if ( strcmp ( platform, "SunOS" ) == 0 ) {
      struct stat solaris_file;
      if ( stat ( "/etc/vfstab", &solaris_file ) == 0 ) {
        strcpy ( platform, "Solaris" );
      }
    }
  }
print_debug(14);

  if ( strcmp ( platform, "SunOS" ) == 0 )
     platform_ident = platform_ident_SunOS;
  else if ( strcmp ( platform, "Solaris" ) == 0 )
     platform_ident = platform_ident_Solaris;
  else if ( strcmp ( platform, "OSF1" ) == 0 )
     platform_ident = platform_ident_OSF1;
  else if ( strcmp ( platform, "Linux" ) == 0 )
     platform_ident = platform_ident_Linux;
  else if ( strcmp ( platform, "AIX" ) == 0 )
     platform_ident = platform_ident_AIX;
  else if ( strcmp ( platform, "HP-UX" ) == 0 )
     platform_ident = platform_ident_HP_UX;
print_debug(15);

  /***
  initialise
  ***/

  /***
  perform minimum malloc
  ***/
  max_mem = alloc_minimum;
  mmts = ( int * ) malloc ( ( max_mem + 5 ) * sizeof ( int ) );  

#ifdef MALLOC_VERBOSE

printf ( "\n    ---------------------------------------------------\n     mimimum malloc (BMotif): max_mem = %d\n    ---------------------------------------------------\n", max_mem );

#endif /* MALLOC_VERBOSE */

  ini_winfunc ();
print_debug(16);
  inifunc ();
print_debug(17);

  XtToolkitInitialize ();
print_debug(18);

  app = XtCreateApplicationContext ();
print_debug(19);

  XtSetLanguageProc ( NULL, NULL, NULL );
print_debug(20);

  display = XtOpenDisplay ( app, NULL, argv[0], "XBMotif",
                           NULL, 0, &argc, argv );
print_debug(21);
  if ( ! display ) {
    printf ( "\n\nBMotif: can't open display\n\n" );
    AbortedMsg ();
    Kill_bplatform_and_exit ( 0, 0 );
  }
print_debug(22);

  /***
  initialise c_arr
  ***/
  for ( i = 0 ; i < c_arr_MAX ; i++ ) { c_arr [ i ] = i; }
print_debug(23);

  /***
  get BKIT_path & cur_dir
  ***/
  {
    char *getenv(), *name;
    int ll;
    /* */
    int BLIB_in_path;
    char* PATH;
    char BLIB[250];
    char env[250];
    /* /*/

    name = getenv ( "BKIT" );
    if ( name == NULL ) {
      printf ( "\n              Environment variable BKIT not set\n" );
      AbortedMsg ();
      Kill_bplatform_and_exit ( 0, 0 );
    }
    ll=strlen(name);
    if (ll > 150) {
      printf ( "\n  Path \"%s\" too long\n\n  Max 150 characters\n\n",name);
      AbortedMsg ();
      Kill_bplatform_and_exit ( 0, 0 );
    }
    else {
      strcpy ( BKIT_path, name ); 
    }
    
    /* detect whether BLIB is in the PATH */
    
    BLIB[0]='\0';
    strcat(BLIB,BKIT_path);
    if(BLIB[strlen(BLIB)-1] !='/')
    {
        strcat(BLIB,"/");
    }
    strcat(BLIB,"BLIB");

    PATH=getenv("PATH");
    BLIB_in_path=0;
    
    if(PATH != NULL)
    {
	    if(strstr(PATH,BLIB) != NULL)
	    {
        	BLIB_in_path=1;
	    }
    }
    
    if(BLIB_in_path==0)
    {
    	/* add $BKIT/BLIB to path */
	
	env[0]='\0';
	strcat(env,"PATH=");
	strcat(env,BLIB);
	if(PATH!=NULL)
	{
		strcat(env,":");
		strcat(env,PATH);
	}
	putenv(env);
    }
    
    /* /*/
    
print_debug(24);

    {
      FILE * Bcom;
      int i, c;
      if ( system ( "pwd > TMP/.Bcom" ) != 0 ) {
        printf ( "\n\n             Error executing \"pwd > TMP/.Bcom\"\n" );
        AbortedMsg ();
        Kill_bplatform_and_exit ( 0, 0 );
      }
      Bcom = fopen ( "TMP/.Bcom", "r" );
      if ( Bcom == NULL ) {
        printf ( "\n\n             BMotif: can't open \"TMP/.Bcom\" for reading\n" );
        AbortedMsg ();
        Kill_bplatform_and_exit ( 0, 0 );
      }
      i = 0;
      c = getc ( Bcom );
      while ( c != EOF && c != '\n' ) {
        cur_dir [ i ] = c;
        i++;
        c = getc ( Bcom );
      }
      fclose ( Bcom );
      cur_dir [ i ] = '\0';
    }
    cur_dir [ 240 ] = '\0';
  
  }

print_debug(25);

  /***
  get colours
  ***/
  gray94 = GetPixel ( "gray94" );
  gray64 = GetPixel ( "gray64" );
  gray39 = GetPixel ( "gray39" );
  red    = GetPixel ( "firebrick3" );
  blue   = GetPixel ( "blue" );
  black  = GetPixel ( "black" );

print_debug(26);

  /***
  create top_level shell - SetTitle in bmotif.c (calls: XmeSetWMShellTitle)
  ***/
  sprintf ( buf, "%s@%s", toolkit_ver, nodename );
  XtSetArg ( args [ 0 ], XmNtitle, buf );
  XtSetArg ( args [ 1 ], XmNforeground, black );

  top_level = XtAppCreateShell ( argv[0], "XBMotif",
               applicationShellWidgetClass,
               display,
               args, 2 );

print_debug(27);

/*
  WM_SAVE_YOURSELF = XmInternAtom ( display, "WM_SAVE_YOURSELF", False );
  XmAddWMProtocols ( top_level, & WM_SAVE_YOURSELF, 1 );
  XmAddWMProtocolCallback ( top_level, WM_SAVE_YOURSELF,
      ( XtCallbackProc ) SaveYourself,
      ( XtPointer )  & c_arr [ 0 ] );
*/
  WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );
  XmAddWMProtocolCallback ( top_level, WM_DELETE_WINDOW,
      ( XtCallbackProc ) SaveYourself,
      ( XtPointer ) & c_arr [ 1 ] );

print_debug(28);

  /***
  enable tear-off menus
  ***/
  /* I hate tear off menus!
  XmRepTypeInstallTearOffModelConverter ();
  */

print_debug(29);

  /***
  create pixmaps
  ***/

print_debug(30);

  Cre_Arrow_Pixmaps ();

print_debug(31);

  sprintf ( str_buf, "%s/BHELP/B1.xpm", BKIT_path );
  B_framed_pixmap_gray94 =
      XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( B_framed_pixmap_gray94 == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create B1.xpm pixmap" );
    printf ( "\n  Can't create B1.xpm pixmap\n" );
  }

print_debug(32);

  sprintf ( str_buf, "%s/BHELP/B2.xpm", BKIT_path );
  B_framed_pixmap_inverse =
      XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( B_framed_pixmap_inverse == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create B2.xpm pixmap" );
    printf ( "\n  Can't create B2.xpm pixmap\n" );
  }
 
/* */
  sprintf ( str_buf, "%s/BHELP/topbar.xpm", BKIT_path );
  B_topbar_pixmap =
      XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( B_topbar_pixmap == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create topbar.xpm pixmap" );
    printf ( "\n  Can't create topbar.xpm pixmap\n" );
  }

  sprintf ( str_buf, "%s/BHELP/red.xpm", BKIT_path );
  red_pixmap =
      XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( red_pixmap == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create red.xpm pixmap" );
    printf ( "\n  Can't create red.xpm pixmap\n" );
  }

  sprintf ( str_buf, "%s/BHELP/green.xpm", BKIT_path );
  green_pixmap =
      XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( green_pixmap == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create green.xpm pixmap" );
    printf ( "\n  Can't create green.xpm pixmap\n" );
  }

  sprintf ( str_buf, "%s/BHELP/blue.xpm", BKIT_path );
  blue_pixmap =
      XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( blue_pixmap == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create blue.xpm pixmap" );
    printf ( "\n  Can't create blue.xpm pixmap\n" );
  }

  sprintf ( str_buf, "%s/BHELP/inapplicable.xpm", BKIT_path );
  inapplicable_pixmap =
      XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( inapplicable_pixmap == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create inapplicable.xpm pixmap" );
    printf ( "\n  Can't create inapplicable.xpm pixmap\n" );
  }

  sprintf ( str_buf, "%s/BHELP/tab.xpm", BKIT_path );
  tab_pixmap =
      XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( tab_pixmap == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create tab.xpm pixmap" );
    printf ( "\n  Can't create tab.xpm pixmap\n" );
  }
  
  sprintf ( str_buf, "%s/BHELP/tabgrey.xpm", BKIT_path );
  tabgrey_pixmap =
      XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( tabgrey_pixmap == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create tabgrey.xpm pixmap" );
    printf ( "\n  Can't create tabgrey.xpm pixmap\n" );
  }

  sprintf ( str_buf, "%s/BHELP/downarrow.xpm", BKIT_path );
  B_downarrow_pixmap =
      XmGetPixmap ( XtScreen ( top_level ), str_buf,
      BlackPixelOfScreen ( XtScreen ( top_level ) ),
      WhitePixelOfScreen ( XtScreen ( top_level ) ) );
  if ( B_downarrow_pixmap == XmUNSPECIFIED_PIXMAP ) {
    Popup_Minor_Err ( top_level, "Can't create downarrow.xpm pixmap" );
    printf ( "\n  Can't create downarrow.xpm pixmap\n" );
  }


print_debug(32000);

  /***
  create main window
  ***/
  curr_env = main_env;
print_debug(33);
  Cre_MainWindow ( top_level );
print_debug(34);

  /***
  create htx popup
  ***/
  Cre_HtxDialog ( top_level );
print_debug(35);

  /***
  get screen
  ***/
  proof_screen = XtScreen ( top_level );
print_debug(36);

  /***
  get colours
  ***/
  GetColours ();
print_debug(37);

  /***
  initialise lab_col
  so, for example : lab_col_b [ lib ] gives
  background colour for library buttons
  must appear after GetColours!
  ***/
  lab_col_f [ 1 ] = user_lab_col_f;
  lab_col_f [ 2 ] = lib_lab_col_f;
  lab_col_f [ 3 ] = gen_lab_col_f;
  lab_col_f [ 4 ] = gen_lab_col_f;
  lab_col_f [ 5 ] = gen_lab_col_f;
  lab_col_f [ 6 ] = gen_lab_col_f;
  lab_col_f [ 7 ] = user_vhdl_lab_col_f;
  lab_col_f [ 8 ] = gen_vhdl_lab_col_f;
  lab_col_f [ 9 ] = lib_vhdl_lab_col_f;
print_debug(38);

  lab_col_b [ 1 ] = user_lab_col_b;
  lab_col_b [ 2 ] = lib_lab_col_b;
  lab_col_b [ 3 ] = gen_lab_col_b;
  lab_col_b [ 4 ] = gen_lab_col_b;
  lab_col_b [ 5 ] = gen_lab_col_b;
  lab_col_b [ 6 ] = gen_lab_col_b;
  lab_col_b [ 7 ] = user_vhdl_lab_col_b;
  lab_col_b [ 8 ] = gen_vhdl_lab_col_b;
  lab_col_b [ 9 ] = lib_vhdl_lab_col_b;

  /* */

  lab_col_pixmap [1] = red_pixmap;
  lab_col_pixmap [2] = blue_pixmap;
  lab_col_pixmap [3] = green_pixmap;
  lab_col_pixmap [4] = green_pixmap;
  lab_col_pixmap [5] = green_pixmap;
  lab_col_pixmap [6] = green_pixmap;
  lab_col_pixmap [7] = red_pixmap;
  lab_col_pixmap [8] = blue_pixmap;
  lab_col_pixmap [9] = green_pixmap;

print_debug(39);

  /***
  Colour Main Environment Button
  ***/
  XtVaSetValues ( 
  	env_lab [ main_env ],
	XmNforeground,  Env_lab_active,
	XmNbackgroundPixmap,            tab_pixmap,
	NULL );
print_debug(40);

  /***
  get multi-click interval
  ***/
  mc_interval = XtGetMultiClickTime ( XtDisplay ( top_level ) );
/***
printf("mc_interval: %d\n",mc_interval);
***/
print_debug(41);

  /***
  initialise ipr_hyp_dialog
  ***/
  for ( i = 0 ; i < 10 ; i++ ) {
    ipr_hyp_sch_dialog_up [ i ] = 0;
  }
  ipr_hyp_dialog_up = 0;
print_debug(42);

  /***
  silently wait <= 2 mins for
  TMP/.BBcom (written by BToolkit)
  ***/
  {
    FILE * fileptr;
    int noBBcom = 1;
    int count = 0;
    int loop_count = 8;
    while ( noBBcom && ( count < 180 ) ) {
      fileptr = fopen ( "TMP/.BBcom", "r" );
      if ( fileptr != NULL ) {
        fclose ( fileptr );
        unlink ( "TMP/.BBcom" );
        unlink ( "TMP/.Bcom" );
        noBBcom = 0;
      }
      else {
        sleep ( 1 );
        if ( count && ( ( ( count / 15 ) * 15 ) == count ) ) {
	  loop_count--;
	  printf ( "\n          BMotif waiting to initialise ... (%d)", loop_count );
	  fflush ( stdout );
	}
        count++;
      }
    }
    if ( noBBcom  ) {
       printf ( "\n\n\n              BMotif giving up on BToolkit\n\n\n" );
       Kill_bplatform_and_exit ( 0, 0 );
    }
    else if ( loop_count != 8 ) {
      printf ( " ... ok\n" );
    }
  }

print_debug(43);

  /***
  get pid & write Bpim
  ***/
  {
    FILE * Bpim;
    Bpim = fopen ( ".Bpim", "w" );
    if ( Bpim == NULL ) {
      printf ( "\n  BMotif: can't open .Bpim for writing\n" );
      BT_err_exit ( 0 );
      return;
    }
    pid = getpid ();
    PrintNum ( Bpim, pid );
    fclose ( Bpim );
  }

print_debug(44);

  /***
  initialise fifo file names
  ***/
  sprintf ( fifo_file_2m, "/tmp/.B_%d_2m", pid );
  sprintf ( fifo_file_2b, "/tmp/.B_%d_2b", pid );
/***
printf ( "BMotif : fifo_file_2m=%s\n", fifo_file_2m );
printf ( "BMotif : fifo_file_2b=%s\n", fifo_file_2b );
***/

print_debug(45);

  /***
  empty .Bcjm
  ***/
  {
    FILE * Bcjm;
    Bcjm = fopen ( ".Bcjm", "w" );
    if ( Bcjm == NULL ) {
      printf( "\n  BMotif: can't open .Bcjm for writing\n" );
      BT_err_exit ( 0 );
      return;
    }
    fclose ( Bcjm );
  }

  /***
  write .Bmvr
  ***/
  {
    FILE * Bmvr;
    Bmvr = fopen ( ".Bmvr", "w" );
    if ( Bmvr == NULL ) {
      printf( "\n  BMotif: can't open .Bmvr for writing\n" );
      BT_err_exit ( 0 );
      return;
    }
    fprintf ( Bmvr, "%s\n", toolkit_ver ); 
    fclose ( Bmvr );
  }

#ifdef COUNT_WWW

  COUNT_25_flag = 0;
  COUNT_25_msg = 0;

#endif /* COUNT_WWW */

print_debug(46);

  /***
  initialise .Bini for BSession
  ***/
  go_flag = 0;

  {
    FILE * Bini;
    Bini = fopen ( ".Bini", "w" );
    if ( Bini == NULL ) {
      printf ( "\n          BMotif: can't open .Bini for writing\n" );
      Kill_bplatform_and_exit ( 0, 0 );
    }
    fprintf ( Bini, "%s|%d", cur_dir, pid );
    fclose ( Bini );
  }

print_debug(47);

  /***
  go! - first wait <= 2 mins for interrupt from bplatform
  ***/
  {
    int count = 0;
    int loop_count = 8;
    while ( ( ! go_flag ) && ( count < 120 ) ) {
      sleep ( 1 );
      if ( count && ( ( ( count / 15 ) * 15 ) == count ) ) {
        loop_count--;
        printf ( "\n                 BMotif waiting ... (%d)", loop_count );
        fflush ( stdout );
      }
      count++;
    }

print_debug(48);

    if ( ! go_flag  ) {
       printf ( "\n\n\n                   BMotif giving up\n\n\n" );
       Kill_bplatform_and_exit ( 0, 0 );
    }
    else if ( loop_count != 8 ) {
      printf ( " ... ok\n" );
    }
  }

print_debug(49);

  widget1_built = 0;

print_debug(50);

  XtManageChild ( main_form );
print_debug(51);

  XtRealizeWidget ( top_level );

print_debug(52);

/***
printf ( "%d  %d  %d  %d  %d  %d  %d\n",  user_lab_col_f, lib_lab_col_f, gen_lab_col_f, user_lab_col_b, lib_lab_col_b, gen_lab_col_b, inapplicable_lab_col );
***/

  if ( ( user_lab_col_f == lib_lab_col_f )        ||
       ( user_lab_col_f == gen_lab_col_f )        ||        
       ( lib_lab_col_f  == gen_lab_col_f )        ||        
       ( user_lab_col_b == inapplicable_lab_col ) ||
       ( lib_lab_col_b  == inapplicable_lab_col ) ||
       ( gen_lab_col_b  == inapplicable_lab_col )    ) {
    Popup_Err ( /* 999998  */ 0, "Can't allocate colours from  \"XBMotif\" " );
    sprintf ( buf, "%s", "\n  Can't allocate colours from \"XBMotif\" resource file.\n\n  This could be because of an already-running\n  colour-hungry application (eg. Netscape),\n  or because \"XBMotif\" is in the wrong place.\n\n  If it is the latter, please put \"XBMotif\"\n  where it can be read, for example in:\n\n        /usr/lib/X11/app-defaults           or\n        /usr/openwinlib/X11/app-defaults    or\n        /usr/X11R6/lib/app-defaults         or\n        $HOME\n\n  The location is dependent on the X file search path\n  of your local setup and you should consult\n  your System Administrator if you experience\n  difficulties.\n\n" );
    puts ( buf );
    DisplayCurrWinText ( buf );
    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );
  }

print_debug(53);

/***
  {
     Dimension d1, d2;
     XtVaGetValues ( top_frame_form,
        XmNpaneMinimum,      & d1, 
        XmNpaneMaximum,      & d2,
        NULL );
     printf ( "%d   %d\n", d1, d2 );
     XtVaGetValues ( bottom_frame_form,
        XmNpaneMinimum,      & d1, 
        XmNpaneMaximum,      & d2,
        NULL );
     printf ( "%d   %d\n", d1, d2 );
  }
***/

print_debug(54);

  srand ( time ( NULL ) );

print_debug(55);

  brz = 0;

/*  Make it a valid hardware licence */

brz=1;
Popup_Sel_flag=0;



/*************************************/

print_debug(56);

print_debug(63);

    inifunc (); /* to get OR_sym for InterProver */

print_debug(64);

    InstallSourceControlFromBsc ( /* init_flag = */ 1 );

print_debug(644);

    GetPixel ( "check colour_problem" );

print_debug(622);

    stat_buf_loaded = 1;
    if ( stat ( ".Bpdan", &stat_buf ) != 0 ) {   /* .Bpdan not exist */
      if ( stat ( ".Bpda", &stat_buf ) != 0 ) {     /* .Bpda not exist */
        if ( stat ( ".Bpda_0", &stat_buf ) != 0 ) {   /* .Bpda_0 not exist */
          stat_buf_loaded = 0;
        }
      }
    }

print_debug(623);

    up_and_running++;

    if ( Popup_Sel_flag == 0 ) { /* Popup_Sel_flag set => error has occurred */

      FILE * Bpda;

      Bpda = fopen ( ".Bpdan", "r" );
      if ( Bpda != NULL ) {                /* .Bpdan exists */
        fclose ( Bpda );
        main_continue ( 1, 0 );

      }
      else {
        Bpda = fopen ( ".Bpda", "r" );
        if ( Bpda != NULL ) {                /* .Bpda exists */
          fclose ( Bpda );
          main_continue ( 0, 0 );

        }
        else {
          Bpda = fopen ( ".Bpda_0", "r" );
          if ( Bpda != NULL ) {             /* .Bpda_0 exists */
             fclose ( Bpda );
             system ( "cp .Bpda_0 .Bpda" );
             main_continue ( 0, 0 );

           }

          else {                            /* .Bpdan, .Bpda & .Bpda_0 not exist */

            void SRC_watch_timer ();
            char *getenv(), *home_dir;
            char buf [ 250 ];  /* don't want the global buf */


/***
printf ( "about to call BMotif_init\n" );
***/
            rewrite_prompt = 0;
print_debug(6000);
            SensitizeFrame ( False );
print_debug(6001);
/*
            BMotifInit();
*/

            if ( auto_reset_and_remake || auto_timer) {
	    
	      printf ( "\n  Not a development directory\n\n" );
              strcpy ( fifo_write_buf, "0:" );
              Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
              InvokeB ( without_XTerm, 0 );
	      
            }
            else {
              home_dir = getenv ( "HOME" );
              if ( home_dir == NULL ) {
                buf [ 0 ] = '\0';
	      }
              else {
                strcpy ( buf, home_dir );
              }
              started_from_cd = 1;
/*
              if ( ( strcmp ( cur_dir, buf ) == 0 ) != 0 ) { 
                strcpy ( sel_str_arr [ sel_arr_MAX ], cur_dir );
	      }
              else {
                strcpy ( sel_str_arr [ sel_arr_MAX ], DropFinalDir ( cur_dir ) );
	      }
*/
              strcpy ( sel_str_arr [ sel_arr_MAX ], cur_dir );
              LoadWritableDirInto_sel_strs ( sel_str_arr [ sel_arr_MAX ] );

              Popup_Selection_Sel_flag = cd_Selection_sel;
              Popup_Selection_Sel_Dialog ( top_level, sel_str_arr [ sel_arr_MAX ] );
	    } 
print_debug(6002);
	  }
        }
      }
    }

  else {   /*  Popup_Sel_flag != 0 => error has occurred */
print_debug(6003);
    main_continue ( 0, 0 );               /* ... just peter out! */
print_debug(6004);

  }

print_debug(645);

print_debug(646);
#ifdef BOOSTER_VERSION
  {
    struct stat stat_buf;
/*
system ( "pwd" );
system ( "ls -al" );
printf ( ">>%d<<\n", lstat ( "menu",          &stat_buf ) );
printf ( ">>%d<<\n",  stat ( "SRC/UTIL/Menu", &stat_buf ) );
*/
    if ( ( lstat ( "menu",          &stat_buf ) == 0 ) != 0 ) system ( "rm -f menu" );
    if ( (  stat ( "SRC/UTIL/Menu", &stat_buf ) == 0 ) != 0 ) system ( "ln -s SRC/UTIL/Menu menu" );
  }
#endif /* BOOSTER_VERSION */
print_debug(647);

print_debug(648);
  XtAppMainLoop ( app );
print_debug(649);
  return ( 0 );
}

void
main_continue ( Bpdan_flag, cd_flag )
int Bpdan_flag;
int cd_flag;
{
  /***
  called from : Init_OK_CANCEL_CB (BMotif_init)
              : ChangeDirectoryExistingDir (BMotif)
              : ChangeDirectoryNewDir (BMotif)
              : ProcessB - BT_NEW_DIR_M (BMotif_io)
              : main (BMotif_widgets)
  
  Bpdan_flag = 1 => .Bpdan exists
  cd_flag    = 1 => changing directory
  ***/

  void SRC_watch_timer ();

print_debug(65);

  if ( ! Popup_Sel_flag ) {

#ifndef WWW_VERSION

    if ( Bpdan_flag ) {
      if ( ! check_Bpdan_type ( ".Bpdan" ) ) {
        XBell ( display, -75 );
        XBell ( display, -75 );
        XBell ( display, -75 );
        XBell ( display, -75 );
        
        printf ( "\n\n              B-Toolkit: Error code 14095\n" );
        unlink ( ".Bcjm" );
        unlink ( ".Bmvr" );
        unlink ( pid_id_file );
        Kill_bplatform_and_exit ( 1, 0 );
      }
    }
    else {
      if ( ! check_Bpda_type ( ".Bpda" ) ) {
        XBell ( display, -75 );
        XBell ( display, -75 );
        XBell ( display, -75 );
        XBell ( display, -75 );
        
        printf ( "\n\n              B-Toolkit: Error code 14095\n" );
        unlink ( ".Bcjm" );
        unlink ( ".Bmvr" );
        unlink ( pid_id_file );
        Kill_bplatform_and_exit ( 1, 0 );
      }
    }

#endif /* !  WWW_VERSION */
 
print_debug(66);

/*
    XtManageChild ( constructs_scroll );
*/

print_debug(67);

    Popup_Info ( "Initialising BToolkit" );

print_debug(68);

    CheckAllDIRSExist ();

print_debug(69);

    if   ( Bpdan_flag ) Restore_n_CfgDepBase ();
    else                Restore_CfgDepBase ();

print_debug(70);

    /***
    set max_fwd_ctr_auto_prf
    ***/
    valIth_flags ( &max_fwd_ctr_auto_prf, Provers_max_fwd_Option_num );
    if ( ! max_fwd_ctr_auto_prf ) max_fwd_ctr_auto_prf = 250;
    WriteBmfh ();

   /***
   set hid_LIB_flag & hid_gen_flag
   ***/
   valIth_flags ( &hid_LIB_flag, hid_LIB_Option_num );
   valIth_flags ( &hid_gen_flag, hid_gen_Option_num );

print_debug(700);

    Re_Cre_Top_Bar_Utils_Pulldown ();

print_debug(71);

    DisplayChanged = 0;

 print_debug(72);

   valIth_flags ( &bell_option, Bell_Option_num );
    if ( bell_option ) {
      XBell ( display, -75 );
      XBell ( display, -75 );
    }

#ifdef WWW_VERSION

    num_usr_constructs = GetNumUsrConstructs ();
    for ( i = 0 ; i < max_num_usr_constr ; i++ ) {
      strcpy ( constr_nme [ i ], "" );
      constr_anl_len [ i ] = 0;
      constr_pob_len [ i ] = 0;
    }

    WWWConstructsCycleCheck ( 999 );

    if ( COUNT_25_flag ) COUNTCheckIsBad ( COUNT_25_flag );

    Popup_WWW_init ( WWW_intro_flag, B_WWW_intro_text );

#endif /* WWW_VERSION */


print_debug(73);

    WriteBpog ();  /* picked up by BSession */

/*
    WriteBtlb ();  /? teamlib ?/
*/

print_debug(74);

    WriteBplf ();  /* prog lang option */

print_debug(75);

    WriteBdmf ();  /* dmu option       */


print_debug(76);


  } /* if ( ! Popup_Sel_flag ) */

print_debug(77);

/***
printf ( "started_from_cd %d cd_flag %d\n", started_from_cd, cd_flag ); fflush ( stdout );
***/

  if ( started_from_cd ) {
    InitialiseDisplay ();
  }

  if ( cd_flag ) { 
 
    /***
    change directory
    ***/
    void DisplayUnInsert_before_cd ();
    void DisplayInsert_after_cd ();
    void DisplayNewEnv ();

    sprintf ( buf, "\n  New Directory:\n\n    %s\n\n", cur_dir );
    DisplayCurrWinText ( buf );

    LibGenConstructsHiddenDisplayMsg ( 0 );

    SetTitle ( cur_dir, 1 );
    rewrite_prompt = 1;
    system ( "#! /bin/sh\nif [ -x /usr/bin/uname ]\nthen\n/usr/bin/uname > .Bpla\nfi" );
    system ( "#! /bin/sh\nif [ -x /usr/uname ]\nthen\n/usr/uname > .Bpla\nfi" );
    system ( "#! /bin/sh\nif [ -x /bin/uname ]\nthen\n/bin/uname > .Bpla\nfi" );
    DisplayUnInsert_before_cd ();
    DisplayInsert_after_cd ();
    Set_display_initialisation ();
/***
printf ( "oOoOoOoOoOoOoOoO 153 " ); fflush ( stdout );
***/
    DeSensitize ();
    DisplayNewEnv ( main_env );
    Reset_display_initialisation ();
  }
  else {

    if ( ! Popup_Sel_flag ) {

      /***
      not change directory
      ***/
      sprintf ( buf, "\n  Current Directory:\n\n    %s\n", cur_dir );
      DisplayCurrWinText ( buf );
    
      LibGenConstructsHiddenDisplayMsg ( 0 );
      SetTitle ( cur_dir, 1 );
      rewrite_prompt = 1;
      HtmlMasterFileChanged = 1;

      InitialiseDisplay ();
      DisplayCurrentEnv ();
    }

  }

print_debug(78);

  if ( ( started_from_cd ) || ( ! cd_flag ) ) { 
    /***
    start timer - SRC_watch_timer won't be performed
    but timer will start;
    DisplayCurrentEnv - above - will have made
    a call to SRC_watch (but not started timer)
    ***/
     SRC_watch_id = XtAppAddTimeOut ( app, SRC_watch_cycle,
                     ( XtTimerCallbackProc ) SRC_watch_timer, NULL );
     if ( started_from_cd ) {
       started_from_cd = 0;
     }
   }

print_debug(79);

  DesLSTBut ( Popup_Sel_flag );

print_debug(80);

  if ( auto_reset_and_remake || upgrade3T04_flag ) {

    void LoadAllConstructsInto_gset1 ();

print_debug(81);

    DeSensitize ();

print_debug(82);

    start_t = time ( NULL );

print_debug(83);

    if ( ! auto_timer ) {

      void auto_reset_and_remake_OR_upgrade_Reset ();

      if ( upgrade3T04_flag == upgrade3T04_reset ) {
        DisplayCurrWinText ( "\n  Auto Reset\n" );
      }
      else {
        if ( auto_reset_and_remake ) {
          if ( auto_reset ) DisplayCurrWinText ( "\n  Auto Reset (" );
          else              DisplayCurrWinText ( "\n  Auto Reset & Remake (" );
          system ( "date '+on %d/%m/%y at %H:%M:%S)' > TMP/.Bdat" );
          LoadFileIntoBuf ( "TMP/.Bdat", buf, MAX_buf - 1 );
          DisplayCurrWinText ( buf );
          unlink ( "TMP/.Bdat" );
        }
        else {
          DisplayCurrWinText ( "\n  Auto Reset & Remake (?)\n" );
        }
      }

      auto_reset_and_remake_OR_upgrade_Reset ();

      /***
      check for unused library machines
      ***/
      {
        int rr, nn;
        get_unused_lib ( &rr );
        chk_rep ( rr, 164 );
        card_gset1 ( &nn );
        if ( nn ) {
          DeSensitize ();
          DisplayCurrWinText ( "\n  Removing unused library constructs\n" );
          RemoveUnusedLibFiles ( 4 ); /* make 5 passes! */
        }
        else {
          DisplayCurrWinText ( "\n  No unused library constructs to remove\n" );
        }
      }

    }  /* if ( ! auto_timer ) ... */

print_debug(84);

    DisplayCurrentEnv ();

print_debug(85);

    LoadAllConstructsInto_gset1 ();

    if ( ( auto_reset_and_remake && ( ! upgrade3T04_flag ) ) ||
         ( upgrade3T04_flag == upgrade3T04_reset_remake )       ) {

      DeSensitize ();
      if ( auto_reset ) {
        Save_n_CfgDepBase ();
        AutoRemakeFini ();
        strcpy ( fifo_write_buf, "0:" );
        Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
        InvokeB ( without_XTerm, 1 );
      }
      else {
        Pre_Remake ( remake_all_constructs );
      }

    }

    else {

      auto_reset_and_remake = 0;
      upgrade3T04_flag = 0;

    }

  } /* if ( auto_reset_and_remake || upgrade3T04_flag ) */

/***
Info_40_Upgrade ( 9 );
***/

  /*  auto_reset_and_remake = 0; */
  upgrade3T04_flag = 0;

}

void
AutoRemakeFini ()
{
    FILE * logfile;
    static int already_visited = 0;

    if ( auto_reset ) return;

    if ( already_visited ) return;
    already_visited = 1;

    if   ( auto_timer ) {
      strcpy ( buf, "\n  " );
    }
    else {
      strcpy ( buf, "\n  Complete " );
      system ( "date '+at %H:%M:%S - ' > .Bdat" );
      LoadFileIntoBuf ( ".Bdat", str_buf, MAX_buf - 1 );
      unlink ( ".Bdat" );
      if ( str_buf [ strlen ( str_buf ) - 1 ] == '\n' )
        str_buf [ strlen ( str_buf ) - 1 ] = '\0';
      strcat ( buf, str_buf );
    }

    end_t = time ( NULL );
    end_t = end_t - start_t;
    if ( end_t > ( 60 * 60 ) ) {
      CreNumInBuf ( buf, ( end_t / ( 60 * 60 ) ) );
      if ( ( end_t / ( 60 * 60 ) ) != 1 ) {
        strcat ( buf, " hours " );
      }
      else {
        strcat ( buf, " hour " );
      }
    }
    end_t = end_t % ( 60 * 60 );
    if ( end_t > 60 ) {
      CreNumInBuf ( buf, ( end_t / 60 ) );
      if ( ( end_t / 60 ) != 1 ) {
        strcat ( buf, " minutes " );
      }
      else {
        strcat ( buf, " minute " );
      }
    }
    end_t = end_t % 60;
    CreNumInBuf ( buf, end_t );
    if ( end_t != 1 ) {
      strcat ( buf, " seconds processing\n\n" );
    }
    else {
      strcat ( buf, " second processing\n\n" );
    }
    DisplayCurrWinText ( buf );

    if ( auto_timer ) {

      logfile = fopen ( "_TimerLog", "a" );
      if ( logfile == NULL ) {
        printf ( "  BMotif: can't open \"_TimerLog\" for appending\n" );
      }
      else {
        FILE * fileid;
/***/
        char * string_ptr;
        string_ptr = XmTextGetString ( main_text );
        fprintf ( logfile, "  %s\n  ========================================================\n", string_ptr );
       XtFree ( string_ptr );
/***/
/***
        system ( "date '+on %d/%m/%y at %H:%M:%S' > .Bdat" );
        LoadFileIntoBuf ( ".Bdat", str_buf, MAX_buf - 1 );
        unlink ( ".Bdat" );
        fprintf ( logfile, "%s  %s\n  ========================================================\n", buf, str_buf );
***/
        fclose ( logfile );
        fileid = fopen ( ".Bpdan.timer", "r" );
        if ( fileid != NULL ) {
          fclose ( fileid );
          system ( "cp .Bpdan.timer .Bpdan" );
          unlink ( ".Bpdan.timer" );
        }
        fileid = fopen ( ".Bpda.timer", "r" );
        if ( fileid != NULL ) {
          fclose ( fileid );
          system ( "cp .Bpda.timer .Bpda" );
          unlink ( ".Bpda.timer" );
        }
        fileid = fopen ( ".Bpda_0.timer", "r" );
        if ( fileid != NULL ) {
          fclose ( fileid );
          system ( "cp .Bpda_0.timer .Bpda_0" );
          unlink ( ".Bpda_0.timer" );
        }
      }

      system ( "cat _TimerLog" );
      printf ( "\n  (Above is contained in _TimerLog)\n" );

    }

    else {

      logfile = fopen ( "_AutoRemakeLog.prev", "r" );
      if ( logfile != NULL ) {
        fclose ( logfile );
        system ( "cp _AutoRemakeLog.prev _AutoRemakeLog.prev.prev" );
        unlink ( "_AutoRemakeLog.prev" );
      }
      logfile = fopen ( "_AutoRemakeLog", "r" );
      if ( logfile != NULL ) {
        fclose ( logfile );
        system ( "cp _AutoRemakeLog _AutoRemakeLog.prev" );
        unlink ( "_AutoRemakeLog" );
      }
      logfile = fopen ( "_AutoRemakeLog", "w" );
      if ( logfile == NULL ) {
        printf ( "  BMotif: can't open \"_AutoRemakeLog\" for writing\n" );
      }
      else {
        char * string_ptr;
        string_ptr = XmTextGetString ( main_text );
        fprintf ( logfile, "%s", string_ptr );
        XtFree ( string_ptr );
        fclose ( logfile );
      }

/***
      printf ( "\n*****************************************************************\n" );
      printf ( "Contents of _AutoRemakeLog:\n" );
      printf ( "<    _AutoRemakeLog.prev\n" );
      printf ( "---\n" );
      printf ( ">    _AutoRemakeLog\n" );
      printf ( "**************************\n\n" );
      system ( "cat _AutoRemakeLog" );
***/

      logfile = fopen ( "_AutoRemakeLog.prev", "r" );
      if ( logfile != NULL ) {
        fclose ( logfile );
        system ( "diff _AutoRemakeLog.prev _AutoRemakeLog > _AutoRemakeLog_diff" );
        printf ( "\n*****************************************************************\n" );
        printf ( "\n%s\n", cur_dir );
        printf ( "\nContents of _AutoRemakeLog_diff:\n" );
        printf ( "*******************************\n\n" );
        system ( "cat _AutoRemakeLog_diff" );
      }
      printf ( "\n*****************************************************************\n" );

    }

/***
printf ( "AutoRemakeFini done\n" );
***/

}
