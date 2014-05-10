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
#include "../MOTIF/BMotif_globals.h"

#include "appmch.motif.h"

#include "bmotif.h"

#include "ctxmch.h"

#include "symmch.h"

#include "golmch.h"

int applicable_rules_up=0;

#ifdef BTOOLKIT_FLAG

#include "BTL_PRF/CDE/C/btl_proofCtx.h"
#include "BTL_PRF/CDE/C/btl_proof.h"
#include "BTL_PRF/CDE/C/btl_proof_file_dump.h"

#include "BTL_PRF/CDE/C/btl_proofCtx.g"
#include "BTL_PRF/CDE/C/btl_proof.g"
#include "BTL_PRF/CDE/C/btl_proof_file_dump.g"

#include "BTL_PRF/CDE/C/btl_proofCtx.h"
#include "BTL_PRF/CDE/C/btl_proof.h"
#include "BTL_PRF/CDE/C/btl_proof_file_dump.h"

#endif

#define thy_first_rule_max 250
int thy_first_rule [ thy_first_rule_max ] [ 2 ];

Widget main_browse_widget_but,
       theory_browse_widget_but,
       rule_browse_widget_but,
       prove_browse_widget_but;

Widget run_but_library;

void Popup_Error ();
void CreProofTreeDialog ();
void Proof_CB_continued ();

/* Main Menu */
#define load_source_but                1
#define reload_source_main_but         2
#define load_binary_but                3
#define save_binary_but                4
#define new_theory_but                 5
#define clear_but                      6
#define statistics_but                 7
#define recompact_but                  8
#define list_symbols_but               9
#define browse_theories_but           10
#define quit_but                      11

/* Theory menu */
#define new_rule_but                  21
#define list_rules_on_file_but        22
#define exec_direct_input_but         23
#define exec_file_input_but           24
#define remove_last_rule_but          25
#define shell_but                     26
#define reload_source_theory_but      27
#define remove_theory_but             28
/* #define statistics_but                 7 */
/* #define proof_on_file_on_off_but      30 */
#define change_normal_tac_theory_but  31
#define change_fwd_tac_theory_but     32
#define prove_lemmas_but              33
/* #define browse_theories_but           10 */
#define main_menu_theory_but          35

/* Rule menu */
#define prove_rule_but                50
#define change_rule_but               51
#define move_rule_but                 52
#define remove_rule_but               53
#define rule_on_off_but               54
/* #define shell_but                     26 */
#define reload_source_rule_but        56
#define remove_proof_but              57
#define reconstruct_proof_tree_but    58
#define build_and_print_proof_but     59
#define change_normal_tac_rule_but    60
#define change_fwd_tac_rule_but       61
#define change_normal_quota_rule_but  62
#define change_fwd_quota_rule_but     63
/* #define browse_theories_but           10 */
#define theory_menu_but               65
#define main_menu_rule_but            66

/* Proof Menu */
#define loop_until_quota_but          70
#define single_step_but               71
#define show_applicable_rules_but     72
#define and_but                       73
#define call_but                      74
#define eql_but                       75
#define inhyp_but                     76
#define ded_but                       77
#define gen_but                       78
#define hyp_but                       79
#define ari_but                       80
#define sub_but                       81
#define flat_but                      82
#define rev_but                       83
#define map_but                       84
#define lmap_but                      85
#define modr_but                      86
#define rule_but                      87
#define write_but                     88
#define catl_but                      89
#define reasoning_depth_but           90
/* #define recompact_but                  8 */
#define newv_but                      91
#define tactic_but                    92
#define close_but                     93
/* #define statistics_but                 7 */
#define redo_but                   95
#define halt_but                      96
#define undo_but                      97
int undo_was_last_button;
#define create_lemma_but              98
#define tactic_browse_but             99
#define dump_hypotheses_but           100
/* #define statistics_but                 7 */
/* #define toggle_show_goals_but         102 */
/* #define toggle_show_hyp_but           103 */
#define change_normal_quota_proof_but 104
#define change_fwd_quota_proof_but    105
#define quit_proof_but               106

#define lemma_but                    107

#define build_and_dsply_proof_but    108

#define max_fwd_hyp_but              109

#define edit_cur_PMD_but             110
#define edit_glob_PMD_but            111
#define reload_PMD_but               112

Widget app_rule_dialog = 0;

#ifdef BTOOLKIT_FLAG

void
Store_thy_first_rule ( thy, first )
int thy;
int first;
{
  int i = 0;
  int found = 0;
  while ( ( ! found ) && ( i < thy_first_rule_max ) ) {
    if   ( ( thy_first_rule [ i ] [ 0 ] == 0 )   ||
           ( thy_first_rule [ i ] [ 0 ] == thy )    ) {
      found = 1;
    }
    else {
      i++;
    }
  }
  if ( found ) {
    thy_first_rule [ i ] [ 0 ] = thy;
    thy_first_rule [ i ] [ 1 ] = first;
  }
/***
printf ( "Store_thy_first_rule: found %d    i %d    thy %d    first %d\n", found, i, thy, first );
***/
}

int
Get_thy_first_rule ( thy )
int thy;
{
  int i = 0;
  int found = 0;
  while ( ( ! found ) && ( i < thy_first_rule_max ) ) {
    if   ( ( thy_first_rule [ i ] [ 0 ] == thy )    ) {
      found = 1;
    }
    else {
      i++;
    }
  }
  if ( found ) {
/***
printf ( "Get_thy_first_rule: found %d  returned %d\n", found, thy_first_rule [ i ] [ 1 ] );
***/
    return ( thy_first_rule [ i ] [ 1 ] );
  }
  else {
/***
printf ( "Get_thy_first_rule: found %d  returned %d\n", found, 1 );
***/
    return ( 1 );
  }
}

#endif

rem_surrounding_ws_str_buf ()
{
  int slen = strlen ( str_buf );
  int i = 0;
  int j;
  while ( str_buf [ i ] == ' ' || str_buf [ i ] == '\t' ) i++;
  slen = slen - i;
  for ( j = 0 ; j < slen ; j++ )  str_buf  [ j ] = str_buf [ j + i ];
  while (   slen && 
          ( str_buf [ slen - 1 ] == ' ' || str_buf [ slen - 1 ] == '\t' ) )
              slen--;
  str_buf [ slen ] = '\0';
}

repl_nl_sp_str_buf ()
{
  int i = 0;
  while ( str_buf [ i ] != '\0' ) {
    if ( str_buf [ i ] == '\n' ) str_buf [ i ] = ' ';
    i++;
  }
}

#define is_alpha(x) ( ( x >= 'a' && x <= 'z' ) || \
                      ( x >= 'A' && x <= 'Z' )    )

#define is_num(x) ( x >= '0' && x <= '9' )

#define is_und(x) ( x == '_' )

#define is_dot(x) ( x == '.' )

str_buf_is_num ()
{
  int i = 0;
  int slen = strlen ( str_buf );
  int is_num_res = 1;
  while ( i < slen && is_num_res ) {
   is_num_res = is_num( str_buf [ i ] );
   i++;
  }
  return ( is_num_res );  
}

str_buf_is_ident ()
{
  int i = 1;
  int slen = strlen ( str_buf );
  int is_ident_res = is_alpha ( str_buf [ 0 ] );

  if ( ! slen ) return ( 0 );

  while ( i < slen && is_ident_res ) {
   is_ident_res =
      ( is_alpha ( str_buf [ i ] ) || 
        is_und   ( str_buf [ i ] ) ||
        is_num   ( str_buf [ i ] )    );
   i++;
  }
  return ( is_ident_res );  
}

sub_str_in_str ( sub_str, main_str )
char * sub_str;
char * main_str;
{
  char * str_ptr;
  int sub_len, str_len, count, found;
  sub_len = strlen ( sub_str );
  str_len = strlen ( main_str );
  str_ptr = main_str;

/***
printf ( "looking for |%s| in |%s| - ", sub_str, str_ptr );
***/
  found = 0;
  count = 0;
  while ( ( ! found ) && ( count < str_len - sub_len + 1 ) ) {
    if ( ! strncmp ( str_ptr, sub_str, sub_len ) ) found = 1;
    str_ptr++;
    count++;
  }
/***
printf ( "%d\n", found );
***/
  return ( found );
}

void
Popup_Parse_Err ()
{
  Widget err;
  XmString xstr;

  err = XmCreateErrorDialog ( top_frame_form, "WarningDialog", NULL, 0 );

  XtVaSetValues ( XtParent ( err ),
      XmNdialogStyle,            XmDIALOG_MODELESS,
      NULL );
  xstr = XmStringCreateLtoR ( err_str_buf, charset );
  XtVaSetValues ( err,
      XmNmessageString,          xstr,
      XmNsymbolPixmap,           B_framed_pixmap_gray94,
      XmNmarginWidth,            10,
      XmNmarginHeight,           5,
      XmNdialogStyle,            XmDIALOG_MODELESS,
      XmNdefaultButtonType,      XmNONE,
      NULL );
  XmStringFree ( xstr );

  XtUnmanageChild ( XmMessageBoxGetChild ( err, XmDIALOG_CANCEL_BUTTON ) );
  XtUnmanageChild ( XmMessageBoxGetChild ( err, XmDIALOG_HELP_BUTTON ) );

  XtVaSetValues ( XmMessageBoxGetChild ( err, XmDIALOG_OK_BUTTON ),
      XmNdefaultButtonShadowThickness,  1,
      XmNnavigationType,       XmTAB_GROUP,
      XmNhighlightThickness,   1,
      NULL );

  XmProcessTraversal ( XmMessageBoxGetChild ( err, XmDIALOG_OK_BUTTON ),
                                                             XmTRAVERSE_CURRENT );
  XBell ( display, 100 );
  XtManageChild ( err );
  XtPopup ( XtParent ( err ), XtGrabNone ); 
  XmUpdateDisplay ( XtParent ( err ) );

}

void
GetColours ()
{
  XtVaGetValues ( main_text, XmNforeground, &main_text_col, NULL );
  {
    Widget row, rc, but, d1;
    Dimension proof_h;
    XmString xstr;

print_debug(1000);

#ifdef BTOOLKIT_FLAG

    row = XtVaCreateWidget ( "Canvas", 
        xmRowColumnWidgetClass,         constructs_rc,
        NULL );

print_debug(1001);
    but = XtVaCreateWidget ( "UserLab", 
        xmPushButtonWidgetClass,        row,
        NULL );
print_debug(1002);
    XtVaGetValues ( but,
        XmNbackground, &user_lab_col_b,
        XmNforeground, &user_lab_col_f,
        NULL );
print_debug(1003);
    XtDestroyWidget ( but );

print_debug(1004);
   but = XtVaCreateWidget ( "LibraryLab", 
        xmPushButtonWidgetClass,        row,
        NULL );
print_debug(1005);
    XtVaGetValues ( but,
        XmNbackground, &lib_lab_col_b,
        XmNforeground, &lib_lab_col_f,
        NULL );
print_debug(1006);
    XtDestroyWidget ( but );

print_debug(1007);
    but = XtVaCreateWidget ( "GeneratedLab", 
        xmPushButtonWidgetClass,        row,
        NULL );
print_debug(1008);
    XtVaGetValues ( but,
        XmNbackground, &gen_lab_col_b,
        XmNforeground, &gen_lab_col_f,
        NULL );
print_debug(1009);
    XtDestroyWidget ( but );

print_debug(1019);
    but = XtVaCreateWidget ( "InapplicableLab", 
        xmPushButtonWidgetClass,        row,
        NULL );
print_debug(1020);
    XtVaGetValues ( but, XmNforeground, &inapplicable_lab_col, NULL );
print_debug(1021);
    XtDestroyWidget ( but );

print_debug(1022);
    XtDestroyWidget ( row );

#endif /* BTOOLKIT_FLAG */

print_debug(1031);
    but = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
print_debug(1032);
    d1 = XtVaCreateWidget ( "ButtonLabel", xmFormWidgetClass, but, NULL );
print_debug(1033);
    XtVaGetValues ( d1, XmNforeground, &Prompt_but_lab_col, NULL );
print_debug(1034);
    Browse_but_lab_col = Prompt_but_lab_col;
print_debug(10342);
    XtVaGetValues ( XmSelectionBoxGetChild ( but, XmDIALOG_TEXT ),
        XmNbackground, &Prompt_text_bck_col, NULL );
print_debug(1035);
    Browse_text_bck_col =Prompt_text_bck_col;
print_debug(10351);
    XtVaGetValues ( but, XmNbackground, &Prompt_bck_col, NULL );
print_debug(1036);
    Browse_bck_col = Prompt_bck_col;
print_debug(10361);
    XtVaGetValues ( but, XmNtopShadowColor, &Prompt_top_col, NULL );
print_debug(1037);
    Browse_top_col = Prompt_top_col;
print_debug(10371);
    XtVaGetValues ( but, XmNbottomShadowColor, &Prompt_bot_col, NULL );
print_debug(1038);
    Browse_bot_col = Prompt_bot_col;
print_debug(10381);
    XtDestroyWidget ( d1 );
print_debug(1039);
/********************************************************************
    XtDestroyWidget ( but ); AIX PROBLEM - LEAVE COMMENTED OUT !!!!!
********************************************************************/

print_debug(1052);
    d1 = XtVaCreateWidget ( "TopBar", 
        xmFormWidgetClass,              main_form,
        NULL );

#ifdef BTOOLKIT_FLAG
print_debug(1053);
    but = XtVaCreateWidget ( "EnvLabelActive",
        xmPushButtonWidgetClass,        main_form,
        NULL );
print_debug(1054);
    XtVaGetValues ( but, XmNforeground, &Env_lab_active, NULL );
print_debug(1055);
    XtDestroyWidget ( but );

print_debug(1056);
    but = XtVaCreateWidget ( "EnvLabelPassive",
        xmPushButtonWidgetClass,        main_form,
        NULL );
print_debug(1057);
    XtVaGetValues ( but, XmNforeground, &Env_lab_passive, NULL );
print_debug(1058);
    XtDestroyWidget ( but );
#endif /* BTOOLKIT_FLAG */

print_debug(1059);
    row = XtVaCreateWidget ( "PullDown", 
        xmFormWidgetClass,              d1,
        NULL );

print_debug(1062);
    xstr = XmStringCreateLtoR ( "aaa=>bbb", charset );
print_debug(1063);
    rc = XtVaCreateWidget ( "Goal",
        xmRowColumnWidgetClass,    row,
        XmNorientation,            XmVERTICAL,
        XmNmarginWidth,            0,
        XmNmarginHeight,           0,
        XmNspacing,                0,
        XmNisHomogeneous,          False,
        NULL );
print_debug(1064);
    but = XtVaCreateWidget ( "Goal", 
        xmPushButtonGadgetClass,   rc,
        XmNshadowThickness,        0,
        XmNlabelString,            xstr,
        XmNmarginWidth,            0,
        XmNmarginHeight,           0,
        XmNdefaultButtonShadowThickness,        0,
        XmNhighlightThickness,     0,
        XmNx,                      0,  
        XmNy,                      0,  
        NULL );
print_debug(1065);
    XmStringFree ( xstr );
print_debug(1066);
    XtVaGetValues ( rc, XmNheight, & proof_h, NULL );

print_debug(1067);
    if ( proof_h != ( ( proof_h / 2 ) * 2 ) )
      proof_h = ( ( proof_h / 2 ) * 2 ) + 2;

print_debug(1068);
    half_proof_goal_height = proof_h / 2;
    goal_rule_vert_diff = ( ( 3 * proof_h ) / 2) - 8;
    proof_horiz_offset = ( 3 * proof_h ) - 7;
    proof_vert_offset = ( 3 * proof_h ) - 7;
    proof_extra_lines_offset = goal_rule_vert_diff - 3;
/***
printf ( ">>>>>>>>>>>>>>>>>>>>>>>>> %d %d %d %d %d\n", half_proof_goal_height, proof_horiz_offset, proof_vert_offset, proof_h, proof_extra_lines_offset );
***/

print_debug(1069);
    XtDestroyWidget ( but );
print_debug(1070);
    XtDestroyWidget ( rc );
print_debug(10700);
    XtDestroyWidget ( row );
print_debug(1071);
    XtDestroyWidget ( d1 );
print_debug(1072);
  }

  {
    Widget d0, d1, d2, w;
print_debug(1073);
    d0 =  XtVaCreateWidget ( "TopBar",
        xmFormWidgetClass,           main_form,
        NULL );
print_debug(1074);
    d1 = XtVaCreateWidget ( "PullDown",
        xmFormWidgetClass,           d0,
        NULL );
print_debug(1075);
    d2 = XtVaCreateWidget ( "Options",
        xmFormWidgetClass,           d1,
        NULL );
print_debug(1076);
    w = XtVaCreateWidget ( "OptionSet",
        xmPushButtonWidgetClass,     d2,
        NULL );
print_debug(1077);
    XtVaGetValues ( w, XmNforeground, &option_set_col, NULL );
print_debug(10770);
    XtDestroyWidget ( w );
print_debug(1078);
    w = XtVaCreateWidget ( "OptionNotSet",
        xmPushButtonWidgetClass,     d2,
        NULL );
print_debug(1079);
    XtVaGetValues ( w, XmNforeground, &option_not_set_col, NULL );
    XtDestroyWidget ( w );
print_debug(1080);
    XtDestroyWidget ( d2 );
print_debug(1081);
    XtDestroyWidget ( d1 );
print_debug(1082);
    XtDestroyWidget ( d0 );
  }
}

void
ClearTopWin ()
{
  if ( XtIsManaged ( TopWin_rc ) ) {
    XtDestroyWidget ( TopWin_rc );
  }

  TopWin_rc = XtVaCreateManagedWidget ( "Canvas", 
      xmRowColumnWidgetClass,         TopWin_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 0,
      XmNmarginHeight,                5,
      XmNspacing,                     2,
      XmNisHomogeneous,               False,
      XmNtraversalOn,                 False,
      NULL );
  XmUpdateDisplay ( TopWin_rc );
  XmUpdateDisplay ( top_frame_form );
  XmUpdateDisplay ( bottom_frame_form );
  XmUpdateDisplay ( main_form_pane );
}

#ifdef BTOOLKIT_FLAG

void
HideTopWin ()
{
  if ( ! ( XtIsManaged ( top_frame_form ) ) ) return;
  XtUnmanageChild ( top_frame_form );
  XmUpdateDisplay ( top_frame_form );
  XmUpdateDisplay ( bottom_frame_form );
  XmUpdateDisplay ( main_form_pane );
}

void
UnHideTopWin ()
{
  if ( XtIsManaged ( top_frame_form ) ) return;
  XtManageChild ( top_frame_form );
  XmUpdateDisplay ( top_frame_form );
  XmUpdateDisplay ( bottom_frame_form );
  XmUpdateDisplay ( main_form_pane );
}

#endif /* BTOOLKIT_FLAG */

void
RemoveBottomForm ()
{
  if ( XtIsManaged ( bottom_frame_form ) ) {
    XtUnmanageChild ( bottom_frame_form );
  }
  XtUnmanageChild ( bot_display_frame );
  XmUpdateDisplay ( bot_display_frame );
  XmUpdateDisplay ( bottom_frame_form );
  XmUpdateDisplay ( top_frame_form );
  XmUpdateDisplay ( main_form_pane );
}

void
RestoreBottomForm ( nn )
int nn;
{
  RemoveBottomForm ();
  XtVaSetValues ( bottom_frame_form,
       XmNpaneMinimum,          nn,
       NULL );
  XtManageChild ( bottom_frame_form );
  XtManageChild ( bot_display_frame );
  XtVaSetValues ( bottom_frame_form,
      XmNpaneMinimum,           bmotif_bottom_frame_form_min,
      NULL );
  XmUpdateDisplay ( bot_display_frame );
  XmUpdateDisplay ( bottom_frame_form );
  XmUpdateDisplay ( top_frame_form );
  XmUpdateDisplay ( main_form_pane );
  XmUpdateDisplay ( top_level );
  XmUpdateDisplay ( curr_text );
  XmUpdateDisplay ( XtParent ( curr_text ) );
}

int
GetProvedStatus ( r )
int r;
{

#ifdef BTOOLKIT_FLAG

  if ( ProvedPrevLevel ( r ) ) {
    return 2;
  }
  else if ( pvd_rul ( r ) == now_rul ) {
    return 3;
  }
  else {
    return 0;
  }

#else

  if ( pvd_rul ( r ) == now_rul ) {
    return 1;
  }
  else {
    return 0;
  }

#endif

}


str_buf_is_filename ()
{
  int i = 0;
  int slen = strlen ( str_buf );
  int is_ident_res =  1;

  if ( ! slen ) return ( 0 );

  while ( i < slen && is_ident_res ) {
   is_ident_res =
      ( is_alpha ( str_buf [ i ] ) || 
        is_und   ( str_buf [ i ] ) ||
        is_dot   ( str_buf [ i ] ) ||
        is_num   ( str_buf [ i ] )    );
   i++;
  }
  return ( is_ident_res );  
}

void
GetCurDir ()
{
  FILE * Bcom;
  int i, c;
  if ( system ( "pwd > .Bcom" ) != 0 ) {
    printf ( "\n\n             Error executing \"pwd > .Bcom\"\n\n" );
    exit___ ( 1 );
  }
  Bcom = fopen ( ".Bcom", "r" );
  if ( Bcom == NULL ) {
    printf ( "\n\n             BMotif: can't open \".Bcom\" for reading\n" );
    exit___ ( 1 );
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
  cur_dir [ 240 ] = '\0';
  unlink ( ".Bcom" );
}

XtCallbackProc
PositionInfoRelMainWin_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  static int first_time = 1;
  Position  top_level_x, top_level_y;
  Dimension top_level_w, widget_w;

  XtVaGetValues ( top_level,
      XmNx,         & top_level_x,
      XmNy,         & top_level_y,
      XmNwidth,     & top_level_w,
      NULL );

  XtVaGetValues ( widget,
      XmNwidth,     & widget_w,
      NULL );

  XtVaSetValues ( widget, 
      XmNx,         top_level_x + ( ( top_level_w - widget_w ) / 2 ),
      XmNy,         1,
      NULL );

  if ( first_time ) {
    first_time = 0;
    wm_width = top_level_x + ( ( top_level_w - widget_w ) / 2 );
    wm_height = 1;
  }
}

XtCallbackProc
PositionWidgetRelCurrMenu_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  Dimension  w_w, g_x, g_w;
  Position   b_x, b_y;

  XtVaGetValues ( widget,
      XmNwidth,     & w_w,
      NULL );

  if ( ( string_box_flag == string_box_new_rule_from_browse ) ||
       ( string_box_flag == string_box_change_rule_from_browse ) ) {

    XtVaGetValues ( browse_a_theory_dialog_form,
        XmNx,         & b_x,
        XmNy,         & b_y,
        XmNwidth,     & g_w,
        NULL );

    XtVaSetValues ( widget, 
        XmNx,         b_x + ( ( g_w - w_w ) / 2 ),
        XmNy,         b_y + 50,
        NULL );
  }

  else {

    XtVaGetValues ( curr_dialog_menu,
        XmNx,         & g_x,
        XmNwidth,     & g_w,
        NULL );

    XtVaSetValues ( widget, 
        XmNx,         g_x + ( ( g_w - w_w ) / 2 ),
        NULL );
  }

/***
printf ( "global_menu_x %d  global_menu_y %d   global_menu_w %d  widget_w %d   (%d,%d)\n", global_menu_x, global_menu_y, global_menu_w, widget_w, global_menu_x + ( ( global_menu_w - widget_w ) / 2 ), global_menu_y );
***/
}

XtCallbackProc
RepositionMenu_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  Position dialog_x;
  Position dialog_y;
  Widget dialog;

/***
printf ( "applicable_rules_up=%d\n", applicable_rules_up );
***/

  switch ( curr_menu ) {
  case main_menu :
    dialog = display_main_menu_dialog;
/***
printf ( "main_menu - " );
***/
    break;
  case a_theory_menu :
    dialog = display_a_theory_dialog;
/***
printf ( "thy_menu  - " );
***/
    break;
  case a_rule_menu :
    dialog = display_a_rule_dialog;
/***
printf ( "rule_menu - " );
***/
    break;
  case prove_rule_menu :
    dialog = prove_rule_dialog;
/***
printf ( "prov_menu - " );
***/
    break;
  }

  XtVaGetValues ( curr_dialog_menu,
      XmNx,       & dialog_x,
      XmNy,       & dialog_y,
      NULL );

/***
printf ( "RepositionMenu_CB curr_dialog_menu=%d\n  dialog_x=     %3d dialog_y=     %3d\n  global_menu_x=%3d global_menu_y=%3d\n",  curr_dialog_menu, dialog_x,  dialog_y, global_menu_x, global_menu_y );
***/

  XtVaGetValues ( dialog,
      XmNx,       & dialog_x,
      XmNy,       & dialog_y,
      NULL );

/***
printf ( "RepositionMenu_CB dialog=%d\n  dialog_x=     %3d dialog_y=     %3d\n  global_menu_x=%3d global_menu_y=%3d\n",  dialog, dialog_x,  dialog_y, global_menu_x, global_menu_y );
***/

  if ( applicable_rules_up ) {
    applicable_rules_up = 0;
    return;
  }

  if ( ( dialog_x - wm_width  > global_menu_x + allowable_dim_x ) ||
       ( dialog_x - wm_width  < global_menu_x - allowable_dim_x ) ) {

/***
printf ( "  wm_height=%d    allowable_dim_x=%d      --- repositioning_y\n",
                                                     wm_height, allowable_dim_x );
***/
    XtVaSetValues ( dialog,
        XmNx,       global_menu_x,
        NULL );
  }

  if ( ( dialog_y - wm_height > global_menu_y + allowable_dim_y ) ||
       ( dialog_y - wm_height < global_menu_y - allowable_dim_y )    ) {

/***
printf ( "  wm_height=%d    allowable_dim_y=%d      --- repositioning_y\n",
                                                     wm_height, allowable_dim_y );
***/
    XtVaSetValues ( dialog,
        XmNy,       global_menu_y,
        NULL );
  }
/***
printf ( "\n" );
***/ 
}

/***
for display_main_menu_dialog only
***/
XtCallbackProc
InitWidgetRelMainWin_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  Position  top_level_x;
  Dimension top_level_w, widget_w;

  XtVaGetValues ( top_level,
      XmNx,         &top_level_x,
      XmNwidth,     &top_level_w,
      NULL );
  XtVaGetValues ( widget,
      XmNwidth,     &widget_w,
      NULL );

  global_menu_x = top_level_w + 150 + top_level_x - widget_w;
  global_menu_y = 1;

/***
printf ( "InitWidgetRelMainWin_CB widget=%d\n  top_level_x=%d top_level_w=%d global_menu_x=%3d global_menu_y=%3d widget_w=%3d\n\n", widget, top_level_x, top_level_w, global_menu_x, global_menu_y, widget_w );
***/
  XtVaSetValues ( widget,
      XmNx,         global_menu_x,
      XmNy,         global_menu_y,
      NULL );

  XtRemoveCallback ( widget, XmNpopupCallback,
      ( XtCallbackProc ) InitWidgetRelMainWin_CB,
      NULL );

  XtAddCallback ( widget, XmNpopupCallback,
      ( XtCallbackProc ) RepositionMenu_CB,
      NULL );
}

XtCallbackProc
RepositionBrowse_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  Position widget_x;
  Position widget_y;

  XtVaGetValues ( widget,
      XmNx,       & widget_x,
      XmNy,       & widget_y,
      NULL );

  if ( ( widget_x - wm_width  > global_browse_x + allowable_dim_x ) ||
       ( widget_x - wm_width  < global_browse_x - allowable_dim_x )    ) {

    XtVaSetValues ( widget,
        XmNx,       global_browse_x,
        NULL );
  }

  if ( ( widget_y - wm_height > global_browse_y + allowable_dim_y ) ||
       ( widget_y - wm_height < global_browse_y - allowable_dim_y )    ) {

    XtVaSetValues ( widget,
        XmNy,       global_browse_y,
        NULL );
  }
/***
printf ( "RepositionBrowse_CB:\n  last_browse_x   %3d   last_browse_y   %3d\n  global_browse_x %3d   global_browse_y %3d   (%d,%d)\n", last_browse_x, last_browse_y, global_browse_x, global_browse_x, global_browse_x, global_browse_y );
***/
}

void
WM_KillCurrMenu ()
{
/***
printf ( "WM_KillCurrMenu\n" );
***/
  switch ( curr_menu ) {
  case main_menu :
    DisplayMainMenu ( 1, 1 );
    break;
  case a_theory_menu :
    DisplayATheoryMenu ( 1, 1 );
    break;
  case a_rule_menu :
    DisplayARuleMenu ( 0, 0 );
    break;
  case prove_rule_menu :
    ProveRuleMenu ( 0, 1 );
    break;
  }
  XmUpdateDisplay ( top_level );
}
      
void
PopdownCurrMenu ()
{
/*
printf ( "PopdownCurrMenu - " );
*/
  switch ( curr_menu ) {
  case main_menu :
    DisplayMainMenu ( 0, 0 );
    break;
  case a_theory_menu :
    DisplayATheoryMenu ( 0, 0 );
    break;
  case a_rule_menu :
    DisplayARuleMenu ( 0, 0 );
    break;
  case prove_rule_menu :
    if ( ! app_rule_dialog ) ProveRuleMenu ( 0, 0 );
    break;
  }
  XmUpdateDisplay ( top_level );
}
      
#ifndef BTOOLKIT_FLAG

Pixmap
Cre_Framed_B_logo_Pixmap ( file, col_str )
char * file;
char * col_str;
{
  FILE * Bxpm;
  Pixmap pixmap;

  Bxpm = fopen ( file, "w" );
  if ( Bxpm == NULL ) {
    printf ( "\n  BMotif: can't open B.xpm for writing\n" );
    exit___ ( 1 );
  }
  fprintf ( Bxpm, "/" );
  fprintf ( Bxpm, "* XPM *" );
  fprintf ( Bxpm, "/\n" );
  fprintf ( Bxpm, "static char * B_frame_pixmap_pxm[] = {\n" );
  fprintf ( Bxpm, "\"32 28 5 1\",\n" );
  fprintf ( Bxpm, "\" 	c black\",\n" );
  fprintf ( Bxpm, "\".	c %s\",\n", col_str );
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
/***
strcpy ( buf, "cat " );
strcat ( buf, file );
system ( buf );
***/
  pixmap = XmGetPixmap ( proof_screen, file,
      BlackPixelOfScreen ( proof_screen ),
      WhitePixelOfScreen ( proof_screen ) );
  unlink ( file );
  if ( pixmap == XmUNSPECIFIED_PIXMAP ) {
    printf("\n  Warning - can't create %s pixmap\n", file );
    sprintf ( buf, "  Can't create %s pixmap  ", file );
    Popup_Info ( buf );
  }
  return ( pixmap );
}

Pixel
GetPixel ( colourname )
char *colourname;
{
  int scr = DefaultScreen ( display );
  Colormap cmap = DefaultColormap ( display, scr );
  XColor colour, ignore;

  if ( XAllocNamedColor( display, cmap, colourname, &colour, &ignore ) )
    return ( colour.pixel );
  else
  {
    printf ( "Warning: unable to allocate colour %s\n", colourname );
    return (WhitePixel( display, scr ));
  }
}

void
RemoveTopCurrText ( add_length )
int add_length;
{
  XmTextPosition nl_pos;
  int nl_found;

/***
printf ( "curr_text_posn start: %d\n", ( int ) curr_text_posn );
XBell( display, -75 );
***/
  nl_found = XmTextFindString ( curr_text,
                 ( XmTextPosition ) text_rem_tot,
                 "\n",
                 XmTEXT_FORWARD,
                 & nl_pos );
  if ( nl_found ) {
    XmTextReplace ( curr_text,
         ( XmTextPosition ) 0,
         ( XmTextPosition ) nl_pos,
         "" );
    curr_text_posn = curr_text_posn - nl_pos;
  }
  else {
    XmTextReplace ( curr_text,
         ( XmTextPosition ) 0,
         ( XmTextPosition ) text_rem_tot,
         "" );
    curr_text_posn = curr_text_posn - text_rem_tot;
  }

  XmTextSetHighlight ( curr_text,
      ( XmTextPosition ) 0,
      ( XmTextPosition ) text_rem_tot + nl_pos,
      XmHIGHLIGHT_NORMAL );
/***
;XBell( display, -75 );
;printf ( "curr_text_posn end:   %d\n", ( int ) curr_text_posn );
;printf ( "  curr_text_posn diff:  %d\n", ( int ) nl_pos );
***/
}

void
DisplayCurrWinText ( text )
char *text;
{
  int text_length = strlen ( text );

  if ( val_batch_sys==FALSE ) {
    if (  ( text_length > 50 )                                           && 
          ( ( int ) curr_text_posn + text_length > text_trigger_tot )    ) {
      RemoveTopCurrText ( text_length );
    }
    XmTextInsert ( curr_text, curr_text_posn, text );
    curr_text_posn = curr_text_posn + text_length;
    XmTextShowPosition ( curr_text, curr_text_posn );
    XmUpdateDisplay ( curr_text );
  }
}

#endif

#ifdef BTOOLKIT_FLAG

UsersBToolThy ( t )
int t;
{
  return ( ( ( t == btl_users_thy ) || ( t == fwd_btl_users_thy ) ) != 0 );
}

ThySeparatorReqd ( t )
int t;
{
  return ( ( ( t == last_btl_fwd_thy )  ||
             ( t == last_rewrite_thy )  ||
             ( t == last_lib_thy )      ||
             ( t == btl_users_thy - 1 )    ) != 0 );
}

ProvedPrevLevel ( rr )
int rr;
{
  int i = 1;
  int found = 0;
  while ( i <= orig_btl_proved & ( ! found ) ) {
    found = ( ( orig_btl_proved_arr [ i ] == rr ) != 0 );
    i++;
  }
  return found;
}

RulePrevPmdLevel ( rr )
int rr;
{
  int i = 1;
  int found = 0;
/***
printf ( "orig_btl_pmd_rule %d\n", orig_btl_pmd_rule );
***/
  while ( i <= orig_btl_pmd_rule & ( ! found ) ) {
    found = ( ( orig_btl_pmd_rule_arr [ i ] == rr ) != 0 );
    i++;
  }
/***
printf ( "RulePrevPmdLevel ( %d )  found %d\n", rr, found );
***/
  return found;
}

int
is_a_guard ( g ) {
  register int w, op, rr;
  w=prd_tree(g);
  op=val_root_frm(w);
  switch ( op ) {
    case BTST_sym : 
      rr = 1;
      break;
    case BNUM_sym : 
      rr = 1;
      break;
    case BINT_sym : 
      rr = 1;
      break;
    case STR_sym : 
      rr = 1;
      break;
    case BBITSTR_sym : 
      rr = 1;
      break;
    case BLITERAL_sym : 
      rr = 1;
      break;
    case BSINGLETON_sym : 
      rr = 1;
      break;
    case IDENT_sym : 
      rr = 1;
      break;
    case UIDENT_sym : 
      rr = 1;
      break;
    case LIDENT_sym : 
      rr = 1;
      break;
    case ANTI_SLASH_sym : 
      rr = 1;
      break;
    case BVRB_sym : 
      rr = 1;
      break;
    case CON_sym : 
      rr = 1;
      break;
    case APP_sym : 
      rr = 1;
      break;
    case BINH_sym : 
      rr = 1;
      break;
    case RUL_sym : 
      rr = 1;
      break;
    case BLENT_sym : 
      rr = 1;
      break;
    case LEM_sym : 
      rr = 1;
      break;
    case RIDF_sym : 
      rr = 1;
      break;
    case RIDE_sym : 
      rr = 1;
      break;
    case GET_sym : 
      rr = 1;
      break;
    case BGETHYP_sym : 
      rr = 1;
      break;
    case BGETALLHYP_sym : 
      rr = 1;
      break;
    case BSEARCH_sym : 
      rr = 1;
      break;
    case BSPAREMEM_sym : 
      rr = 1;
      break;
    case BSETFWDPRF_sym : 
      rr = 1;
      break;
    default : 
      rr = 0;
      break;
  }
  kil ( w );
  return ( rr );
}

void
load_toolkit15_po_dot_src ( dots_flag )
int dots_flag;
{
  int i, t, n, found;
  struct stat stat_buf;

  sho_big_gol_prf=TRUE;
  sho_gol_prf=TRUE;
  sho_der_hyp_prf=TRUE;


  /***
  An initial alloc (of 1000) is made when the toolkit is first started so that
  OR_sym for the InterProver may be obtained (BMotif_widgets.c); this is then
  freed here.
  However on quitting the BTool Prover, mmts is also freed (and max_mem set
  to 0 - exit___contd___finally of bmotif.c); thus it does not need freeing again!
  ***/

/***
printf ( "load_toolkit15_po_dot_src top:\n  primary_string = %s, secondary_string = %s\n",  primary_string, secondary_string );
***/

  if ( max_mem ) {
    /***
    free mmts
    ***/

#ifdef MALLOC_VERBOSE

printf ( "\n    ---------------------------------------------------\n     free mmts (BMotif): max_mem = %d -> 0\n    ---------------------------------------------------\n", max_mem );

#endif /* MALLOC_VERBOSE */

    max_mem = 0;
    free ( mmts );

  }

  /***
  perform malloc
  ***/
  max_mem = alloc_init;
  mmts = ( int * ) malloc ( ( max_mem + 5 ) * sizeof ( int ) );  

#ifdef MALLOC_VERBOSE

printf ( "\n    ---------------------------------------------------\n     initial malloc (BMotif): max_mem = %d\n    ---------------------------------------------------\n", max_mem );

#endif /* MALLOC_VERBOSE */

  ini_winfunc ();
  inifunc ();

  /***
  create formulae for SwitchBTPX forward HYP rule
  ***/
  {
    register int f;
    FILE * BTPftac;
    int c, i;
    strcpy ( str_buf, "bcall((DED~;SwitchBTPX~),(ExpandHypX;PropertiesX;" );
    BTPftac = fopen ( "TMP/.BTPftac", "r" );
    if ( BTPftac != NULL ) {
      i = strlen ( str_buf );
      c = getc ( BTPftac );
      while ( ( c != EOF ) && ( c != '\n' ) ) {
        str_buf [ i++ ] = c;
        c = getc ( BTPftac );
      }
      fclose ( BTPftac );
      str_buf [ i ] = '\0';
     }
    strcat ( str_buf, ";FwdBToolUsersTheory;" );
    i = strlen ( str_buf );

    str_buf [ i ] = '\0';
    strcat ( str_buf, btl_fwd_tac [ 0 ] );
    strcat ( str_buf, ")~:(h=>g))=>(h=>g)" );
    strcpy ( SwitchBTPXDED0, str_buf );
/***
printf ( "\nSwitchBTPXDED0 %s (len=%d)\n",
                                      SwitchBTPXDED0, strlen ( SwitchBTPXDED0 ) );
***/

    str_buf [ i ] = '\0';
    strcat ( str_buf, btl_fwd_tac [ 1 ] );
    strcat ( str_buf, ")~:(h=>g))=>(h=>g)" );
    strcpy ( SwitchBTPXDED1, str_buf );
/***
printf ( "\nSwitchBTPXDED1 %s (len=%d)\n",
                                      SwitchBTPXDED1, strlen ( SwitchBTPXDED1 ) );
***/

    str_buf [ i ] = '\0';
    strcat ( str_buf, btl_fwd_tac [ 2 ] );
    strcat ( str_buf, ")~:(h=>g))=>(h=>g)" );
    strcpy ( SwitchBTPXDED2, str_buf );
/***
printf ( "\nSwitchBTPXDED2 %s (len=%d)\n\n",
                                      SwitchBTPXDED2, strlen ( SwitchBTPXDED2 ) );
***/
  }

  /***
  load Toolkit15.bin
  ***/
  sprintf ( name_restore_fil, "%s/BLIB/Toolkit15.bin", BKIT_path );
  restore_fil = fopen ( name_restore_fil, "r" );
  if ( restore_fil == NULL ) {
    DisplayCurrWinText ( "\n  Can't read \"" );
    DisplayCurrWinText ( name_restore_fil );
    DisplayCurrWinText ( "\"\n" );
    Popup_Info ( "    Can't read file!        " );
  }
  else {
    restore_BTool_toolfunc();  /* tolmch.c.motif */
  }
  /***
  load po.src
  ***/
/***
printf ( "\n------------------------ po.src ------------------\n" );
system ( "cat TMP/po.src" );
printf ( "\n--------------------------------------------------\n\n" );
***/
  sprintf ( name_load_fil, "%s/TMP/po.src", cur_dir );
  if ( stat ( name_load_fil, &stat_buf ) == -1 ) {
    DisplayCurrWinText ( "\n\n  Can't read \"" );
    DisplayCurrWinText ( name_load_fil );
    DisplayCurrWinText ( "\"\n" );
    Popup_Info ( "    Can't read file!        " );
  }
  else {
    lod_prf;  /* prfmch.c.motif */
    sprintf ( str_buf, "%s/TMP/po.src", cur_dir );
    unlink ( str_buf );
    if ( dots_flag ) DisplayCurrWinText ( "...." );
  }

/***
printf ( "load_toolkit15_po_dot_src mid:\n  primary_string = %s, secondary_string = %s\n",  primary_string, secondary_string );
***/

  max_btl_thy_len = 0;
  first_btl_thy_to_display = 2;
  last_btl_thy_to_display = nbr_the;

  /*

  not necessary - for interactive BToolProof and Remake,
  secondary_string = BToolLemmas, but for ProofPrinter
  secondary_string = thyToBePrinted.n

  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    if ( ( int ) strlen ( str_buf ) > max_btl_thy_len )
      max_btl_thy_len = strlen ( str_buf );
    found = ( ( strcmp ( str_buf, secondary_string ) == 0 ) != 0 );
    i--;
  }
  i++;
  if ( found ) last_btl_thy_to_display = i;

  this is one less than FwdBToolUsersTheory

  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    if ( ( int ) strlen ( str_buf ) > max_btl_thy_len )
      max_btl_thy_len = strlen ( str_buf );
    found = ( ( strcmp ( str_buf, primary_string ) == 0 ) != 0 );
    i--;
  }
  if ( found ) first_btl_thy_to_display = i + 1;

  */

  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    found = ( ( strcmp ( str_buf, "UsersTheory" ) == 0 ) != 0 );
    i--;
  }
  if   ( found ) users_thy = i + 1;
  else           users_thy = 0;

  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    found = ( ( strcmp ( str_buf, "FwdUsersTheory" ) == 0 ) != 0 );
    i--;
  }
  if   ( found ) fwd_users_thy = i + 1;
  else           fwd_users_thy = 0;

  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    found = ( ( strcmp ( str_buf, "BToolUsersTheory" ) == 0 ) != 0 );
    i--;
  }
  if   ( found ) btl_users_thy = i + 1;
  else           btl_users_thy = 0;

  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    found = ( ( strcmp ( str_buf, "FwdBToolUsersTheory" ) == 0 ) != 0 );
    i--;
  }
  if   ( found ) { first_btl_thy_to_display = i + 2; fwd_btl_users_thy = i + 1; }
  else           { fwd_btl_users_thy = 0; }

  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    found = ( ( strcmp ( str_buf, "FwdPOGTheoryX" ) == 0 ) != 0 );
    i--;
  }
  if   ( found ) last_btl_fwd_thy = i + 1;
  else           last_btl_fwd_thy = 0;

  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    found = ( ( strcmp ( str_buf, "StandardizeX" ) == 0 ) != 0 );
    i--;
  }
  if   ( found ) last_rewrite_thy = i;
  else           last_rewrite_thy = 0;

  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    found = ( ( strcmp ( str_buf, "OrX" ) == 0 ) != 0 );
    i--;
  }
  if   ( found ) last_lib_thy = i + 1;
  else           last_lib_thy = 0;

  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    found = ( ( strcmp ( str_buf, "StandardizeX" ) == 0 ) != 0 );
    i--;
  }
  if   ( found ) first_switch_thy = i + 2;
  else           first_switch_thy = 0;

  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    found = ( ( strcmp ( str_buf, "OrX" ) == 0 ) != 0 );
    i--;
  }
  if   ( found ) last_switch_thy = i + 1;
  else           last_switch_thy = 0;

  /*** 
  set max_btl_thy_len
  ***/
  for ( i = first_btl_thy_to_display ; i <= last_btl_thy_to_display ; i++ ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    if ( ( int ) strlen ( str_buf ) > max_btl_thy_len )
                                          max_btl_thy_len = strlen ( str_buf );
  }

  /***
  load btl.src
  ***/
/***
printf ( "----------------------- btl.src ------------------\n" );
system ( "cat TMP/btl.src" );
printf ( "\n--------------------------------------------------\n\n" );
***/
  sprintf ( name_load_fil, "%s/TMP/btl.src", cur_dir );
  if ( name_load_fil == NULL ) {
    DisplayCurrWinText ( "\n  Can't read \"" );
    DisplayCurrWinText ( name_load_fil );
    DisplayCurrWinText ( "\"\n" );
    Popup_Info ( "    Can't read file!        " );
  }
  else {
    lod_prf;  /* prfmch.c.motif */
    sprintf ( str_buf, "%s/TMP/btl.src", cur_dir );
    unlink ( str_buf );
  }

  /***
  store previous pmd rules
  ***/
  orig_btl_pmd_rule = 0;
  t = btl_users_thy;
/***
str_buf [ 0 ] = '\0';
write_nam_the ( t );
printf ( "looking at theory %s:\n", str_buf );
***/
  if ( t ) {
    n = nbr_rul_the ( t );
    i = 1;
    found = 0;
    while ( ( ! found ) && ( i <= n ) ) {
      str_buf [ 0 ] = '\0';
      write_ver_rul_dave ( val_rul_the ( t, i ) );
/***
printf ( "found rule `%s'\n", str_buf );
***/
      found = ( ( strcmp ( str_buf, "_________.__" ) == 0 ) != 0 );
      if ( ! found ) {
        orig_btl_pmd_rule++;
        if ( orig_btl_pmd_rule < orig_btl_pmd_rule_arr_MAX ) {
          orig_btl_pmd_rule_arr [ orig_btl_pmd_rule ] = val_rul_the ( t, i );
        }
        i++;
      }
    }  /* i points to rule _________.__ */
    if ( found ) {
/***
str_buf [ 0 ] = '\0';
write_nam_the ( t );
printf ( "removing separator rule %d of %s:\n", i, str_buf );
str_buf [ 0 ] = '\0';
write_ver_rul_dave ( val_rul_the ( t, i ) );
printf ( "    %s\n", str_buf );
***/
      rem_rul_the ( t, i );
    }
  }

  t = fwd_btl_users_thy;
/***
str_buf [ 0 ] = '\0';
write_nam_the ( t );
printf ( "looking at theory %s:\n", str_buf );
***/
  if ( t ) {
    n = nbr_rul_the ( t );
    i = 1;
    found = 0;
    while ( ( ! found ) && ( i <= n ) ) {
      str_buf [ 0 ] = '\0';
      write_ver_rul_dave (  val_rul_the ( t, i ) );
/***
printf ( "found rule `%s'\n", str_buf );
***/
      found = ( ( strcmp ( str_buf, "_________.__" ) == 0 ) != 0 );
      if ( ! found ) {
        orig_btl_pmd_rule++;
        if ( orig_btl_pmd_rule < orig_btl_pmd_rule_arr_MAX ) {
          orig_btl_pmd_rule_arr [ orig_btl_pmd_rule ] = val_rul_the ( t, i );
        }
        i++;
      }
    }  /* i points to rule _________.__ */
    if ( found ) {
/***
str_buf [ 0 ] = '\0';
write_nam_the ( t );
printf ( "removing separator rule %d of %s:\n", i, str_buf );
str_buf [ 0 ] = '\0';
write_ver_rul_dave ( val_rul_the ( t, i ) );
printf ( "    %s\n", str_buf );
***/
      rem_rul_the ( t, i );
    }
  }

  /***
  store previously proved
  ***/
  orig_btl_proved = 0;
  for ( t = first_btl_thy_to_display ; t <= last_btl_thy_to_display ; t++ ) {
    n = nbr_rul_the ( t );
    for ( i = 1 ; i <= n ; i++ ) {
      if ( pvd_rul ( val_rul_the ( t, i ) ) == now_rul ) {
        orig_btl_proved++;
        if ( orig_btl_proved < orig_btl_proved_arr_MAX )
          orig_btl_proved_arr [ orig_btl_proved ] = val_rul_the ( t, i );
      }
    }
  }


  /***
  load swbtp.src
  ***/
/***
printf ( "----------------------- swbtp.src ------------------\n" );
system ( "cat TMP/swbtp.src" );
printf ( "\n--------------------------------------------------\n\n" );
***/
  sprintf ( name_load_fil, "%s/TMP/swbtp.src", cur_dir );
  if ( stat ( name_load_fil, &stat_buf ) == -1 ) {
    DisplayCurrWinText ( "\n\n  Can't read \"" );
    DisplayCurrWinText ( name_load_fil );
    DisplayCurrWinText ( "\"\n" );
    Popup_Info ( "    Can't read file!        " );
  }
  else {
    lod_prf;  /* prfmch.c.motif */
    sprintf ( str_buf, "%s/TMP/swbtp.src", cur_dir );
    unlink ( str_buf );
    if ( dots_flag ) DisplayCurrWinText ( "...." );
  }

  str_buf [ 0 ] = '\0';
  write_nam_the ( first_switch_thy );
  strcat ( str_buf, "___SwitchBTPX" );
  strcpy ( primary_string, str_buf );
  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    found = ( ( strcmp ( str_buf, primary_string ) == 0 ) != 0 );
    i--;
  }
  if   ( found ) first_switchBTP_thy = i + 1;
  else           first_switchBTP_thy = 0;

  str_buf [ 0 ] = '\0';
  write_nam_the ( last_switch_thy );
  strcat ( str_buf, "___SwitchBTPX" );
  strcpy ( primary_string, str_buf );
  found = 0;
  i = nbr_the;
  while ( i && ( ! found ) ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    found = ( ( strcmp ( str_buf, primary_string ) == 0 ) != 0 );
    i--;
  }
  if   ( found ) last_switchBTP_thy = i + 1;
  else           last_switchBTP_thy = 0;

  /***
  Set TAC to SwitchBTPX
  ***/
  str_buf [ 0 ] = '\0'; write_nam_the ( nbr_the ); /* SwitchBTPX */
  k = read_frm_str_buf;
  if ( k != -999 ) {
    for ( t = first_btl_thy_to_display ; t <= last_btl_thy_to_display ; t++ ) {
      mod_tac_the ( t, k );
    }
  }

/***
str_buf [ 0 ] = '\0'; write_nam_the ( users_thy );
printf ( "A: users_thy                =%4d (%s)\n", users_thy, str_buf );
str_buf [ 0 ] = '\0'; write_nam_the ( fwd_users_thy );
printf ( "A: fwd_users_thy            =%4d (%s)\n", fwd_users_thy, str_buf );
str_buf [ 0 ] = '\0'; write_nam_the ( btl_users_thy );
printf ( "A: btl_users_thy            =%4d (%s)\n", btl_users_thy, str_buf );
str_buf [ 0 ] = '\0'; write_nam_the ( fwd_btl_users_thy );
printf ( "A: fwd_btl_users_thy        =%4d (%s)\n", fwd_btl_users_thy, str_buf );
str_buf [ 0 ] = '\0'; write_nam_the ( last_btl_fwd_thy );
printf ( "A: last_btl_fwd_thy         =%4d (%s)\n", last_btl_fwd_thy, str_buf );
str_buf [ 0 ] = '\0'; write_nam_the ( last_rewrite_thy );
printf ( "A: last_rewrite_thy         =%4d (%s)\n", last_rewrite_thy, str_buf );
str_buf [ 0 ] = '\0'; write_nam_the ( last_lib_thy );
printf ( "A: last_lib_thy             =%4d (%s)\n", last_lib_thy, str_buf );
str_buf [ 0 ] = '\0'; write_nam_the ( first_btl_thy_to_display );
printf ( "A: first_btl_thy_to_display =%4d (%s)\n", first_btl_thy_to_display, str_buf );
str_buf [ 0 ] = '\0'; write_nam_the ( last_btl_thy_to_display );
printf ( "A: last_btl_thy_to_display  =%4d (%s)\n", last_btl_thy_to_display, str_buf );
str_buf [ 0 ] = '\0'; write_nam_the ( first_switch_thy );
printf ( "A: first_switch_thy         =%4d (%s)\n", first_switch_thy, str_buf );
str_buf [ 0 ] = '\0'; write_nam_the ( last_switch_thy );
printf ( "A: last_switch_thy          =%4d (%s)\n", last_switch_thy, str_buf );
str_buf [ 0 ] = '\0'; write_nam_the ( first_switchBTP_thy );
printf ( "A: first_switchBTP_thy      =%4d (%s) (%d)\n", first_switchBTP_thy, str_buf, nbr_rul_the ( first_switchBTP_thy ) );
str_buf [ 0 ] = '\0'; write_nam_the ( last_switchBTP_thy );
printf ( "A: last_switchBTP_thy       =%4d (%s) (%d)\n", last_switchBTP_thy, str_buf, nbr_rul_the ( last_switchBTP_thy ) );
n = nbr_the - 1;
str_buf [ 0 ] = '\0'; write_nam_the ( n );
printf ( "A: penultimate              =%4d (%s) (%d)\n", n, str_buf, nbr_rul_the ( n ) );
n++;
str_buf [ 0 ] = '\0'; write_nam_the ( n );
printf ( "A: last                     =%4d (%s) (%d)\n", n, str_buf, nbr_rul_the ( n ) );
printf ( "\n" );
***/

/*
A: users_thy                =  96 (UsersTheory)
A: fwd_users_thy            =  97 (FwdUsersTheory)
A: btl_users_thy            =  98 (BToolUsersTheory)
A: fwd_btl_users_thy        =  99 (FwdBToolUsersTheory)
A: last_btl_fwd_thy         =  41 (FwdPOGTheoryX)
A: last_rewrite_thy         =  65 (RewriteNonHypLogic2X)
A: last_lib_thy             =  91 (OrX)
A: first_btl_thy_to_display = 100 (Initialisation)
A: last_btl_thy_to_display  = 103 (BToolLemmas)
A: first_switch_thy         =  67 (CardinalityX)
A: last_switch_thy          =  91 (OrX)
A: first_switchBTP_thy      = 104 (CardinalityX___SwitchBTPX) (14)
A: last_switchBTP_thy       = 128 (OrX___SwitchBTPX) (2)
A: penultimate              = 129 (SwitchNotBTPX) (14)
A: last                     = 130 (SwitchBTPX) (18)
*/

}

#endif

SaveYourself_BTool ( dialog, client_data, call_data )
Widget dialog;
XtPointer client_data;
XtPointer call_data;
{
  printf ( "\n  Panic Save (%d) !!!\n", ( * ( int * ) client_data ) ); fflush ( stdout );
  if ( ( * ( int * ) client_data ) == 1 ) {
    printf ( "\n\n         THIS IS *NOT* THE WAY TO TERMINATE THE B-TOOL;\n          DATA MAY BE LOST, OR THE SYSTEM LEFT HANGING\n\n             PLEASE USE THE `QUIT BTOOL' BUTTON\n\n\n\n" );
  }
  XmFontListFree ( fontlist );
  exit___ ( 0 );
}

void
motif_init ( argc, argv )  /* from bmotif.c & BMotif_io */
int argc;
char *argv[];
{
  int i;
  Arg args [ 5 ];

#ifndef BTOOLKIT_FLAG

  Atom WM_SAVE_YOURSELF;
  Atom WM_DELETE_WINDOW;

  /***
  initialise
  ***/
  XtToolkitInitialize ();

  app = XtCreateApplicationContext ();

  XtSetLanguageProc ( NULL, NULL, NULL );

  display = XtOpenDisplay ( app, NULL, argv[0], "XBMotif",
                           NULL, 0, &argc, argv );
  if ( ! display ) {
    XtWarning ( " BMotif: can't open display\n" );
    exit___ ( 1 );
  }

  /***
  get current directory
  ***/
  GetCurDir ();

  /***
  create top_level shell
  ***/
  XtSetArg ( args [ 0 ], XmNtitle, tool_ver );

  top_level = XtAppCreateShell ( argv[0], "XBMotif",
               applicationShellWidgetClass,
               display,
               args, 1 );

  WM_SAVE_YOURSELF = XmInternAtom ( display, "WM_SAVE_YOURSELF", False );
  XmAddWMProtocols ( top_level, & WM_SAVE_YOURSELF, 1 );
  XmAddWMProtocolCallback ( top_level, WM_SAVE_YOURSELF,
      ( XtCallbackProc ) SaveYourself_BTool,
      ( XtPointer )  & c_arr [ 0 ] );

  WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );
  XmAddWMProtocolCallback ( top_level, WM_DELETE_WINDOW,
      ( XtCallbackProc ) SaveYourself_BTool,
      ( XtPointer ) & c_arr [ 1 ] );

  /***
  get screen
  ***/
  proof_screen = XtScreen ( top_level );

  /***
  enable tear-off menus
  ***/
  XmRepTypeInstallTearOffModelConverter ();

  /***
  get colours
  ***/
  gray89 = GetPixel ( "gray89" );
  gray64 = GetPixel ( "gray64" );
  gray39 = GetPixel ( "gray39" );
  red    = GetPixel ( "firebrick3" );
  blue   = GetPixel ( "blue" );

  /***
  create pixmaps
  ***/
  B_framed_pixmap_gray94 = Cre_Framed_B_logo_Pixmap ( "B.xpm", "gray94" );

  /***
  main form with User Data
  ***/
  main_form = XtVaCreateWidget ( "MainWin",
      xmFormWidgetClass,          top_level,
      XmNuserData,                ( XtPointer ) & c_arr [ 0 ],
      NULL );

  /***
  toolkit pane in main form
  ***/
  main_form_pane = XtVaCreateWidget ( "MainWin", 
      xmPanedWindowWidgetClass,       main_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNspacing,                     5,
      XmNallowResize,                 True,
      NULL );

  /***
  top_frame_form in toolkit pane
  ***/
  top_frame_form = XtVaCreateWidget ( "MainWin", 
      xmFormWidgetClass,              main_form_pane,
      XmNpaneMinimum,                 bmotif_top_frame_form_min,
      XmNwidth,                       522,
      XmNheight,                      600, /* height of top win */
      NULL );

  /***
  constructs_frame in top_frame_form
  ***/
  constructs_frame = XtVaCreateWidget ( "Frame", 
      xmFrameWidgetClass,             top_frame_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   5,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  5,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 5,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                5,
      XmNshadowType,                  XmSHADOW_ETCHED_IN,
      NULL );

  /***
  constructs_form in constructs_frame_form
  ***/
  constructs_form = XtVaCreateWidget ( "ConstructsArea", 
      xmFormWidgetClass,             constructs_frame,
      NULL );

  

#else

  XtUnmanageChild ( constructs_scroll );

  INI_btl_proofCtx ();
  INI_btl_proof();
  INI_btl_proof_file_dump ();

#endif

  /***
  TopWin_scroll in constructs_form
  **/
  TopWin_scroll = XtVaCreateWidget ( "Canvas", 
      xmScrolledWindowWidgetClass,    constructs_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   10,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNshadowThickness,             3,
      XmNwidth,                       300, /* width of TL win */
      NULL );

  /***
  TopWin_rc rowcol in TopWin_scroll
  ***/
  TopWin_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         TopWin_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 0,
      XmNmarginHeight,                5,
      XmNspacing,                     2,
      XmNisHomogeneous,               False,
      XmNtraversalOn,                 False,
      NULL );

#ifndef BTOOLKIT_FLAG

  /***
  bottom_frame_form in toolkit pane
  ***/
  bottom_frame_form = XtVaCreateWidget ( "MainWin", 
      xmFormWidgetClass,              main_form_pane,
      XmNpaneMinimum,                 bmotif_bottom_frame_form_min,
      NULL );

  /***
  display frame in display form
  ***/
  bot_display_frame = XtVaCreateWidget ( "DisplayArea", 
      xmFrameWidgetClass,             bottom_frame_form,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   5,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  5,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 5,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                5,
      XmNshadowType,                  XmSHADOW_ETCHED_IN,
      XmNmarginWidth,                 10,
      XmNmarginHeight,                10,
      NULL );

  /***
  display text in bot_display_frame
  ***/
  {
    Arg args [ 15 ];
    int n = 0;

    /*
    XtSetArg ( args [ n ], XmNrows,                  45                ); n++;
    XtSetArg ( args [ n ], XmNcolumns,               60                ); n++;
    */
    XtSetArg ( args [ n ], XmNeditable,              False             ); n++;
    XtSetArg ( args [ n ], XmNeditMode,              XmMULTI_LINE_EDIT ); n++;
    XtSetArg ( args [ n ], XmNcursorPositionVisible, False             ); n++;
    XtSetArg ( args [ n ], XmNscrollHorizontal,      False             ); n++;
    XtSetArg ( args [ n ], XmNwordWrap,              True              ); n++;
    XtSetArg ( args [ n ], XmNmarginWidth,           5                 ); n++;
    XtSetArg ( args [ n ], XmNmarginHeight,          5                 ); n++;
    XtSetArg ( args [ n ], XmNshadowThickness,       3                 ); n++;
    XtSetArg ( args [ n ], XmNshadowThickness,       3                 ); n++;
    XtSetArg ( args [ n ], XmNtraversalOn,           False             ); n++;
    main_text =
             XmCreateScrolledText ( bot_display_frame, "Canvas", args, n );
  }

  /***
  set text window
  ***/
  curr_text = main_text;
  curr_text_posn = main_text_posn;

#endif

  /***
  get fonts
  ***/
  GetFonts ();

  /***
  manage children (motif_init)
  ***/
  XtManageChild ( TopWin_rc );
  XtManageChild ( TopWin_scroll );
#ifndef BTOOLKIT_FLAG
  XtManageChild ( constructs_form );
  XtManageChild ( constructs_frame );
  XtManageChild ( main_text );
  XtManageChild ( bot_display_frame );
  XtManageChild ( top_frame_form );
  XtManageChild ( bottom_frame_form );
  XtManageChild ( main_form_pane );
#else
  XtVaGetValues ( bottom_frame_form,
      XmNheight,         & bottom_frame_form_height,
      NULL );
#endif

  XmUpdateDisplay ( constructs_form );
  XmUpdateDisplay ( top_level );

#ifndef BTOOLKIT_FLAG

  /***
  get colours
  ***/
  GetColours ();
    
  /***
  get multi-click interval
  ***/
  mc_interval = XtGetMultiClickTime ( XtDisplay ( top_level ) );

  /***
  initialise c_arr
  ***/
  for ( i = 0 ; i < c_arr_MAX ; i++ ) {
    c_arr [ i ] = i;
  }

  XtManageChild ( main_form );
  XtRealizeWidget ( top_level );

#endif

  hyp_search_string [ 0 ] = '\0';

#ifdef BTOOLKIT_FLAG

  /***
  initialise thy_first_rule
  ***/
  for ( i = 0; i < thy_first_rule_max ; i++ ) {
    thy_first_rule [ i ] [ 0 ] = 0;
  }

#endif

}

Widget
CreHighlightedButton ( parent, label, call_back, value )
  Widget parent;
  char * label;
  XtCallbackProc call_back;
  XtPointer value;
{
  XmString xstr;
  Widget button;

  xstr = XmStringCreateLtoR ( label, charset );
  button = XtVaCreateManagedWidget ( "Canvas", 
       xmPushButtonGadgetClass,        parent,
       XmNshadowThickness,             0,
       XmNlabelString,                 xstr,
       XmNmarginWidth,                 2,
       XmNmarginHeight,                2,
       XmNdefaultButtonShadowThickness,        0,
       XmNhighlightThickness,          1,
       XmNnavigationType,              XmTAB_GROUP,
       NULL );
  XmStringFree ( xstr );

  XtAddCallback ( button, XmNactivateCallback,
      ( XtCallbackProc ) call_back,
      ( XtPointer ) value );

  return button;
}

Widget
CreHighlightedButtonUserData ( parent, label, call_back, value, nn )
  Widget parent;
  char * label;
  XtCallbackProc call_back;
  XtPointer value;
  int nn;
{
  XmString xstr;
  Widget button;

/***
printf ( "CreHighlightedButtonUserData - %d\n", nn );
***/

  xstr = XmStringCreateLtoR ( label, charset );
  button = XtVaCreateManagedWidget ( "Canvas", 
       xmPushButtonGadgetClass,        parent,
       XmNshadowThickness,             0,
       XmNlabelString,                 xstr,
       XmNmarginWidth,                 2,
       XmNmarginHeight,                1,
       XmNdefaultButtonShadowThickness,        0,
       XmNhighlightThickness,          1,
       XmNnavigationType,              XmTAB_GROUP,
       XmNuserData,( XtPointer )       & c_arr [ nn ],
       NULL );
  XmStringFree ( xstr );

  XtAddCallback ( button, XmNactivateCallback,
      ( XtCallbackProc ) call_back,
      ( XtPointer ) value );

  return button;
}

Widget
CreHighlightedProofButton ( parent, label, top_off, left_off, call_back, value )
  Widget parent;
  char * label;
  int top_off, left_off;
  XtCallbackProc call_back;
  XtPointer value;
{
  XmString xstr;
  Widget button;

  xstr = XmStringCreateLtoR ( label, charset );

#define proof_h_tab 46
#define proof_v_tab 15

  button = XtVaCreateManagedWidget ( "Canvas", 
       xmPushButtonGadgetClass,        parent,
       XmNtopAttachment,               XmATTACH_FORM,
       XmNtopOffset,                   top_off * proof_v_tab,
       XmNleftAttachment,              XmATTACH_WIDGET,
       XmNleftOffset,                  left_off * proof_h_tab,
       XmNshadowThickness,             0,
       XmNlabelString,                 xstr,
       XmNfontList,                    fontlist,
       XmNdefaultButtonShadowThickness,        0,
       XmNhighlightThickness,          1,
       XmNnavigationType,              XmTAB_GROUP,
       NULL );

  XmStringFree ( xstr );

  XtAddCallback ( button, XmNactivateCallback,
      ( XtCallbackProc ) call_back,
      ( XtPointer ) value );

  return button;
}

void
CrePassiveButton ( parent, label )
  Widget parent;
  char * label;
{
  XmString xstr;

  xstr = XmStringCreateLtoR ( label, charset );

  XtVaCreateManagedWidget ( "SelDialog", 
       xmLabelWidgetClass,         parent,
       XmNlabelString,             xstr,
       XmNshadowThickness,         0,
       XmNtraversalOn,             False,
       XmNmarginWidth,             0,
       XmNmarginHeight,            0,
       NULL );
  XmStringFree ( xstr );

}

void
CreSmallPassiveButton ( parent, label )
  Widget parent;
  char * label;
{
  XmString xstr;

  xstr = XmStringCreateLtoR ( label, charset );

  XtVaCreateManagedWidget ( "SelDialog", 
       xmLabelWidgetClass,         parent,
       XmNlabelString,             xstr,
       XmNshadowThickness,         0,
       XmNmarginHeight,            1,
       XmNtraversalOn,             False,
       NULL );
  XmStringFree ( xstr );

}

#ifndef BTOOLKIT_FLAG

XtIntervalId Popup_Info_id;

XtTimerCallbackProc
Popup_Info_CB ( client_data, id )
XtPointer client_data;
XtIntervalId * id;
{
  static int first_time = 1;
  Widget * dialog = ( Widget * ) client_data;
/*
printf ( "       >>>>>>>>>>>> timer done %d \n", ( * dialog ) );
*/

  XtRemoveTimeOut ( Popup_Info_id );
  if ( first_time ) {
    Position dialog_x, dialog_y;
    first_time = 0;
    XtVaGetValues ( * dialog, 
        XmNx,    & dialog_x,
        XmNy,    & dialog_y,
       NULL );
    /***
    wm_width & wm_height set in PositionInfoRelMainWin_CB
    ***/
    wm_width = dialog_x - wm_width;
    wm_height = dialog_y - wm_height;
/***
printf ( "wm_width=%d wm_height=%d\n", wm_width, wm_height );
***/
    if ( ( wm_width < 2 ) || ( wm_width > 8 ) ) wm_width = 5;
    if ( ( wm_height < 2 ) || ( wm_height > 27 ) ) wm_height = 14;

  }

  XtPopdown ( * dialog );
  XtDestroyWidget ( * dialog );

  if ( exit_flag ) {
    XmFontListFree ( fontlist );
    exit___ ( 1 );
  }
  else if ( popup_after_time_elapsed ) {

    popup_after_time_elapsed = 0;
    switch ( string_box_flag ) {

    case string_box_new_rule:
    case string_box_new_rule_from_browse:
    case string_box_change_rule:
    case string_box_change_rule_from_browse:
      LargeStringBox ( " New Rule:                                                                                                     ", buf );
      break;

    case string_box_new_thy:
      StringBox ( " Theory name:              ", str_buf );
      break;

    case string_box_recompact:
      StringBox ( "Max Size of Free space after each sequence?", str_buf );
      break;

    case string_box_prf_to_file:
      StringBox ( " File for proofs:          ", str_buf );
      break;

    case string_box_nml_tac_a_theory:
    case string_box_nml_tac_a_rule:
      StringBox ( " New Normal tactic:                                       ", buf );
      break;

    case string_box_fwd_tac_a_theory:
    case string_box_fwd_tac_a_rule:
      StringBox ( " New Forward tactic:                                       ", buf );
      break;

    case string_box_nml_quota:
      StringBox ( " New Normal proof quota: ", str_buf );
      break;

    case string_box_fwd_quota:
      StringBox ( " New Forward proof quota: ", str_buf );
      break;

    case string_box_move_rule:
      StringBox ( " New position:   ", str_buf );
      break;

    case string_box_nml_quota_from_proof:
      StringBox ( " New Normal proof quota: ", str_buf );
      break;

    case string_box_fwd_quota_from_proof:
      StringBox ( " New Forward proof quota: ", str_buf );
      break;

    case string_box_exec_direct:
      StringBox ( " Rule to Exec:                                        ", buf );
      break;

    }

  }

}

void
Popup_Info ( text )
char * text;
{
    static int first_time = 1;
    Widget dialog, dialog_form, B_logo;
    Widget Label;
    XmString xstr;
    Atom   WM_DELETE_WINDOW;

    if ( ! up_and_running ) return;

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    dialog = XmCreateDialogShell ( top_frame_form, "InfoDialog", NULL, 0 );

    dialog_form = XtVaCreateWidget ( "InfoDialog",
        xmFormWidgetClass,         dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        False,  
        NULL );

    XtAddCallback ( dialog, XmNpopupCallback,
        ( XtCallbackProc ) PositionInfoRelMainWin_CB,
        NULL );

    B_logo =  XtVaCreateWidget ( "InfoDialog",
        xmLabelWidgetClass,         dialog_form,
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


  xstr = XmStringCreateLtoR ( text, charset );
  Label = XtVaCreateWidget ( "InfoDialog", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNleftOffset,             25,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNrightOffset,            50,
        XmNbottomAttachment,       XmATTACH_FORM,
        XmNbottomOffset,           10,
        XmNlabelString,            xstr,
        XmNmarginWidth,            10,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
  XmStringFree ( xstr );

  
  XtManageChild ( Label );
  XtManageChild ( B_logo );
  XtManageChild ( dialog_form );
  XtRealizeWidget ( dialog );

  if ( first_time ) {
    first_time = 0;
    Popup_Info_id = XtAppAddTimeOut ( app, 2500UL,
      ( XtTimerCallbackProc ) Popup_Info_CB,
      ( XtPointer ) dialog );
    XmAddWMProtocolCallback ( dialog, WM_DELETE_WINDOW,
        ( XtCallbackProc ) Popup_Info_CB,
        ( XtPointer ) dialog );
  }
  else {
     Popup_Info_id = XtAppAddTimeOut ( app, 3500UL,
      ( XtTimerCallbackProc ) Popup_Info_CB,
      ( XtPointer ) dialog );
  }

  if ( exit_flag ) printf ( "\n                   %s\n\n\n", text );

  XtPopup ( dialog, XtGrabNone );

  XmUpdateDisplay ( dialog );
  XmUpdateDisplay ( top_level );
}

#endif

void
Popup_Error_CB ( err )
Widget err;
{
  XtPopdown ( XtParent ( err ) );
  XmUpdateDisplay ( XtParent ( err ) );
}

void
Popup_Error ( text )
char * text;
{
    Widget err;
    XmString xstr;

    if ( ! up_and_running ) return;

    err = XmCreateErrorDialog ( top_level, "WarningDialog", NULL, 0 );

    XtAddCallback ( err, XmNmapCallback,
        ( XtCallbackProc ) PositionInfoRelMainWin_CB,
        NULL );

    XtVaSetValues ( err,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultPosition,        False,  
        XmNdialogStyle,            XmDIALOG_MODELESS,
        NULL );
    XtUnmanageChild ( XmMessageBoxGetChild ( err, XmDIALOG_CANCEL_BUTTON ) );
    XtUnmanageChild ( XmMessageBoxGetChild ( err, XmDIALOG_HELP_BUTTON ) );
    XtVaSetValues ( err,
        XmNsymbolPixmap,           B_framed_pixmap_gray94,
        NULL );
    XtAddCallback ( err, XmNokCallback,
                                 ( XtCallbackProc ) Popup_Error_CB, NULL );

    xstr = XmStringCreateLtoR ( text, charset );
    XtVaSetValues ( err,
        XmNmessageString,          xstr,
        NULL );
    XmStringFree ( xstr );

    XtManageChild ( err );
    XtPopup ( XtParent ( err ), XtGrabNone ); 

    XmUpdateDisplay ( err );
}

XtCallbackProc
StringBox_CB ( widget, client_data, cbs )
Widget widget;
XtPointer client_data;
XmSelectionBoxCallbackStruct *cbs;
{
  char * text;
  int but_num =  * ( int * ) client_data;

  if ( but_num == OK_BUTTON ) {

   XmStringGetLtoR ( cbs->value, XmSTRING_DEFAULT_CHARSET, &text );
   if   ( text != NULL ) strcpy ( str_buf, text );
   else                  strcpy ( str_buf, "" );
   XtFree ( text );

   rem_surrounding_ws_str_buf ();

   switch ( string_box_flag ) {

     case string_box_new_thy :
       {
         int slen = strlen ( str_buf );
         if ( slen ) {
           if ( ! str_buf_is_ident () ) {
             popup_after_time_elapsed = 1;
             Popup_Info ( "  Theory name should be an identifier!  " );
	   }
           else {
             if ( browse_theories_is_up ) {
               BrowseTheories ( 0, 0 );
               BrowseTheories ( 1, 0 );
	     }
             curr_thy = read_the;
             PopdownCurrMenu ();
             DisplayATheoryMenu ( 1, 0 );
             util_str_i = 1;
             DisplayATheoryTopWin ( curr_thy );
	   }
	 }
         else {
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Empty input!     " );
         }
       }
       break;

     case string_box_recompact :
       {
         int i;
         long int nn;
         int slen = strlen ( str_buf );
         nn = 0;
         i = 0;
         if ( slen ) {
           if ( ! str_buf_is_num () ) {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Not a natural number!  " );
	   }
           else if ( slen < 11 ) {
             while ( i < slen ) nn = ( nn * 10 ) + str_buf [ i++ ] - '0';
             if ( nn >= 0 ) {
               cmp_seq ( nn );
               sta_seq_hdr ();
	     }
             else {
               popup_after_time_elapsed = 1;
               Popup_Info ( "   Number greater than 2147483647  " );
	     }
	   }
           else {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Number greater than 2147483647  " );
	   }
	 }
         else {
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Empty input!     " );
         }
       }
       break;

     case string_box_exec_direct :
       {
         register int f = read_frm_str_buf;
         if ( f != -999 ) {
           exec_dir_prf ( curr_thy, f );
	 }
         else {
	   /*           kil(f);  done in macmch! */
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Input does not parse!     " );
	 }
       }
       break;

     case string_box_exec_file :
       exec_file_prf ( curr_thy );
       if ( val_ret_sys == TRUE ) DisplayCurrWinText ( "\n  Done\n" );
       DisplayATheoryTopWin ( curr_thy );
       break;

#ifndef BTOOLKIT_FLAG

     case string_box_prf_to_file :
       if ( str_buf_is_filename () ) {
         void BuildAndPrintProof2 ();
         strcpy ( name_prf_fil, str_buf );
         mod_print_ext_prf_the (TRUE);
/*         mod_first_prf_the (TRUE); not used */
         BuildAndPrintProof2 ();
/*
         mod_print_ext_prf_the (TRUE);
         mod_first_prf_the (TRUE);
         strcpy ( str_buf, "\n  Proofs printed on file " );
         write_prf_name_fil;
         strcat ( str_buf, "\n" );
         DisplayCurrWinText ( str_buf );
*/
       }
       else {
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Not a valid filename!     " );
       }
       break;

#endif

     case string_box_nml_tac_a_theory :
       {
         register int f = read_frm_str_buf;
         if ( f != -999 ) {
           mod_tac_the ( curr_thy, f );
           DisplayATheoryTopWin ( curr_thy );
	 }
         else {
	   /*           kil(f);  done in macmch! */
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Input does not parse!     " );
	 }
       }
       break;

     case string_box_fwd_tac_a_theory :
       {
         register int f = read_frm_str_buf;
         if ( f != -999 ) {
           mod_fwd_tac_the ( curr_thy, f );
           DisplayATheoryTopWin ( curr_thy );
	 }
         else {
	   /*           kil(f);  done in macmch! */
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Input does not parse!     " );
	 }
       }
       break;

     case string_box_nml_tac_a_rule :
       {
         register int f = read_frm_str_buf;
         if ( f != -999 ) {
           mod_tac_the ( curr_thy, f );
           DisplayARuleTopWin ( curr_rule );
	 }
         else {
	   /*           kil(f);  done in macmch! */
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Input does not parse!     " );
	 }
       }
       break;

     case string_box_fwd_tac_a_rule :
       {
         register int f = read_frm_str_buf;
         if ( f != -999 ) {
           mod_fwd_tac_the ( curr_thy, f );
           DisplayARuleTopWin ( curr_rule );
	 }
         else {
	   /*           kil(f);  done in macmch! */
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Input does not parse!     " );
	 }
       }
       break;

     case string_box_nml_quota :
       {
         int i;
         long int nn;
         int slen = strlen ( str_buf );
         nn = 0;
         i = 0;
         if ( slen ) {
           if ( ! str_buf_is_num () ) {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Not a natural number!  " );
	   }
           else if ( slen < 11 ) {
             while ( i < slen ) nn = ( nn * 10 ) + str_buf [ i++ ] - '0';
             if ( nn >= 0 ) {
               max_ctr_prf = nn;
               DisplayARuleTopWin ( curr_rule );
               strcpy ( str_buf, "      New Normal proof quota: " );
               CreNumInBuf ( str_buf, max_ctr_prf );
               strcat ( str_buf, "      " );
               Popup_Info ( str_buf );
	     }
             else {
               popup_after_time_elapsed = 1;
               Popup_Info ( "   Number greater than 2147483647  " );
	     }
	   }
           else {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Number greater than 2147483647  " );
	   }
	 }
         else {
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Empty input!     " );
         }
       }
       break;

     case string_box_nml_quota_from_proof :
       {
         int i;
         long int nn;
         int slen = strlen ( str_buf );
         nn = 0;
         i = 0;
         if ( slen ) {
           if ( ! str_buf_is_num () ) {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Not a natural number!  " );
	   }
           else if ( slen < 11 ) {
             while ( i < slen ) nn = ( nn * 10 ) + str_buf [ i++ ] - '0';
             if ( nn >= 0 ) {
               Normal_quota_prffunc_contd ( nn );
	     }
             else {
               popup_after_time_elapsed = 1;
               Popup_Info ( "   Number greater than 2147483647  " );
	     }
	   }
           else {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Number greater than 2147483647  " );
	   }
	 }
         else {
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Empty input!     " );
         }
       }
       break;

     case string_box_fwd_quota_from_proof :
       {
         int i;
         long int nn;
         int slen = strlen ( str_buf );
         nn = 0;
         i = 0;
         if ( slen ) {
           if ( ! str_buf_is_num () ) {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Not a natural number!  " );
	   }
           else if ( slen < 11 ) {
             while ( i < slen ) nn = ( nn * 10 ) + str_buf [ i++ ] - '0';
             if ( nn >= 0 ) {
               Forward_quota_prffunc_contd ( nn );
	     }
             else {
               popup_after_time_elapsed = 1;
               Popup_Info ( "   Number greater than 2147483647  " );
	     }
	   }
           else {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Number greater than 2147483647  " );
	   }
	 }
         else {
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Empty input!     " );
         }
       }
       break;

     case string_box_fwd_quota :
       {
         int i;
         long int nn;
         int slen = strlen ( str_buf );
         nn = 0;
         i = 0;
         if ( slen ) {
           if ( ! str_buf_is_num () ) {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Not a natural number!  " );
	   }
           else if ( slen < 11 ) {
             while ( i < slen ) nn = ( nn * 10 ) + str_buf [ i++ ] - '0';
             if ( nn >= 0 ) {
               max_fwd_ctr_prf = nn;
               DisplayARuleTopWin ( curr_rule );
               strcpy ( str_buf, "      New Normal proof quota: " );
               CreNumInBuf ( str_buf, max_fwd_ctr_prf );
               strcat ( str_buf, "      " );
               Popup_Info ( str_buf );
	     }
             else {
               popup_after_time_elapsed = 1;
               Popup_Info ( "   Number greater than 2147483647  " );
	     }
	   }
           else {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Number greater than 2147483647  " );
	   }
	 }
         else {
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Empty input!     " );
         }
       }
       break;

     case string_box_move_rule :
       {
         int i;
         long int nn;
         int slen = strlen ( str_buf );
         CreProofTreeDialog ( 0 );
         nn = 0;
         i = 0;
         if ( slen ) {
           if ( ! str_buf_is_num () ) {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Not a natural number!  " );
	   }
           else if ( slen < 11 ) {
             while ( i < slen ) { nn = ( nn * 10 ) + str_buf [ i++ ] - '0'; }
             if ( nn >= 0 ) {
               if ( ( nn >= 1 ) && ( nn <= nbr_rul_the ( curr_thy ) ) ) {  
                 mod_num_rul_the ( curr_thy, curr_rule, nn );
                 curr_rule = nn;
                 DisplayARuleTopWin ( curr_rule );
                 if ( curr_thy == browse_a_theory_is_up ) {
                   int browse_a_theory_is_up_save;
                   browse_a_theory_is_up_save = browse_a_theory_is_up;
                   BrowseATheory ( 0, 0 );
                   browse_a_theory_is_up = browse_a_theory_is_up_save;
                   BrowseATheory ( browse_a_theory_is_up, 0 );
                 }
	       }
               else {
                popup_after_time_elapsed = 1;
                 Popup_Info ( "      Bad position!    " );
               }
	     }
             else {
               popup_after_time_elapsed = 1;
               Popup_Info ( "   Number greater than 2147483647  " );
	     }
	   }
           else {
             popup_after_time_elapsed = 1;
             Popup_Info ( "   Number greater than 2147483647  " );
	   }
	 }
         else {
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Empty input!     " );
         }
       }
       break;

     }
  }

  else { /* CANCEL */
    if ( ( string_box_flag == string_box_nml_quota_from_proof ) ||
         ( string_box_flag == string_box_fwd_quota_from_proof )    ) {
      Proof_CB_continued ( TRUE, proof_step_flag_NO );
    }
  }
}

void
StringBox ( prompt, label )
char * prompt;
char * label;
{
  static Widget s_d;
  XmString xstr;

  if ( ! s_d ) {
    /***
    create the s_d
    ***/
    s_d = XmCreatePromptDialog ( top_level, "PromptDialog", NULL, 0 );
    XtVaSetValues ( s_d,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNautoUnmanage,           False,
        XmNdefaultPosition,        False,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        NULL );
    XtUnmanageChild ( XmSelectionBoxGetChild ( s_d, XmDIALOG_HELP_BUTTON ) );

    /***
    add the callbacks
    ***/
    XtAddCallback ( s_d, XmNmapCallback,
        ( XtCallbackProc ) PositionWidgetRelCurrMenu_CB,
        NULL );
    XtAddCallback ( s_d, XmNokCallback,
        ( XtCallbackProc ) StringBox_CB,
        ( XtPointer ) & c_arr [ OK_BUTTON ] );
    XtAddCallback ( s_d, XmNcancelCallback,
        ( XtCallbackProc ) StringBox_CB,
        ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );

  }

  xstr = XmStringCreateLocalized ( prompt );
  XtVaSetValues ( s_d, XmNselectionLabelString, xstr, NULL );
  XmStringFree ( xstr );

  xstr = XmStringCreateLocalized ( label );
  XtVaSetValues ( s_d, XmNtextString, xstr, NULL );
  XmStringFree ( xstr );

  XtRealizeWidget ( s_d );

  if ( ( string_box_flag == string_box_new_rule_from_browse ) ||
       ( string_box_flag == string_box_change_rule_from_browse ) ) {
    XtVaSetValues ( s_d,
        XmNbackground,            Browse_bck_col,
        XmNtopShadowColor,        Browse_top_col,
        XmNbottomShadowColor,     Browse_bot_col,
        NULL );
    XtVaSetValues ( XmSelectionBoxGetChild ( s_d, XmDIALOG_TEXT ),
        XmNbackground,            Browse_text_bck_col,
        NULL );
  }
  else {
    XtVaSetValues ( s_d,
        XmNbackground,            Prompt_bck_col,
        XmNtopShadowColor,        Prompt_top_col,
        XmNbottomShadowColor,     Prompt_bot_col,
        NULL );
    XtVaSetValues ( XmSelectionBoxGetChild ( s_d, XmDIALOG_TEXT ),
        XmNbackground,            Prompt_text_bck_col,
        NULL );
  }

  XtManageChild ( s_d );
}

XtCallbackProc
LargeStringBox_ok_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  register int f ;
  char * string_ptr;
  Widget prompt_dialog = XtParent ( XtParent ( XtParent ( widget ) ) );
  XtPopdown ( prompt_dialog );
  string_ptr = XmTextGetString ( ( Widget ) client_data );
  strcpy ( str_buf, string_ptr );
  strcpy ( buf, str_buf );
  XtFree ( string_ptr );
/*
  repl_nl_sp_str_buf ();
  rem_surrounding_ws_str_buf ();
*/
  if ( str_buf [ 0 ] == '\0' ) {
    popup_after_time_elapsed = 1;
    Popup_Info ( "    Empty input!   " );
  }
  else {  
   switch ( string_box_flag ) {
     case string_box_new_rule :
       {
         register int f ;
         f = read_frm_str_buf;
         if ( f != -999 ) {
           read_rul_the ( curr_thy, f );
           visible_thy_menu_rule_num = nbr_rul_the ( curr_thy );
           DisplayATheoryTopWin ( curr_thy );
           if ( browse_theories_is_up ) {
             BrowseTheories ( 0, 0 );
             BrowseTheories ( 1, 0 );
           }
           else if ( curr_thy == browse_a_theory_is_up ) {
             int browse_a_theory_is_up_save;
             browse_a_theory_is_up_save = browse_a_theory_is_up;
             BrowseATheory ( 0, 0 );
             browse_a_theory_is_up = browse_a_theory_is_up_save;
             BrowseATheory ( browse_a_theory_is_up, 0 );
	   }
	 }
         else {
	   /*           kil(f);  done in macmch! */
           XtPopup ( prompt_dialog, XtGrabNone );
           XmUpdateDisplay ( prompt_dialog );
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Input does not parse!     " );
	 }
       }
       break;
     case string_box_new_rule_from_browse :
       {
         register int f, browse_a_theory_is_up_save ;
         f = read_frm_str_buf;
         if ( f != -999 ) {
           read_rul_the ( browse_a_theory_is_up, f );
           browse_a_theory_is_up_save = browse_a_theory_is_up;
           BrowseATheory ( 0, 0 );
           switch ( curr_menu ) {
	     case main_menu :
               DisplayMainTopWin ( 0 );
               DisplayMainTopWin ( 1 );
               break;
	     case a_theory_menu :
               if ( curr_thy == browse_a_theory_is_up_save ) {
                 DisplayATheoryTopWin ( 0 );
                 DisplayATheoryTopWin ( curr_thy );
	       }
               break;
	     case prove_rule_menu :
               ProveRuleMenu ( 0, 0 );
               ProveRuleMenu ( 1, 0 );
               break;
	   }
           string_box_flag = 0;
           browse_a_theory_is_up = browse_a_theory_is_up_save;
           BrowseATheory ( browse_a_theory_is_up, 0 );
	 }
         else {
	   /*           kil(f);  done in macmch! */
           XtPopup ( prompt_dialog, XtGrabNone );
           XmUpdateDisplay ( prompt_dialog );
           popup_after_time_elapsed = 1;
           Popup_Minor_Err ( top_level, "     New rule does not parse!     " );
	 }
       }
       break;
     case string_box_change_rule :
       {
         register int f ;
         CreProofTreeDialog ( 0 );
         f = read_frm_str_buf;
         if ( f != -999 ) {
           read_mod_rul_the ( curr_thy, curr_rule, f );
           DisplayARuleTopWin ( curr_rule );
           if ( curr_thy == browse_a_theory_is_up ) {
             int browse_a_theory_is_up_save;
             browse_a_theory_is_up_save = browse_a_theory_is_up;
             BrowseATheory ( 0, 0 );
             browse_a_theory_is_up = browse_a_theory_is_up_save;
             BrowseATheory ( browse_a_theory_is_up, 0 );
           }
	 }
         else {
	   /*           kil(f);  done in macmch! */
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Input does not parse!     " );
	 }
       }
       break;
     case string_box_change_rule_from_browse :
       {
         register int f, browse_a_theory_is_up_save ;
         f = read_frm_str_buf;
         if ( f != -999 ) {
           int t, n;
           t = the_rul ( browse_btool_theory_rul );
           n = num_rul ( browse_btool_theory_rul );
           read_mod_rul_the ( t, n, f );
           browse_a_theory_is_up_save = browse_a_theory_is_up;
           BrowseATheory ( 0, 0 );
           switch ( curr_menu ) {
	     case main_menu :
               DisplayMainTopWin ( 0 );
               DisplayMainTopWin ( 1 );
               break;
	     case a_theory_menu :
               if ( curr_thy == browse_a_theory_is_up_save ) {
                 DisplayATheoryTopWin ( 0 );
                 DisplayATheoryTopWin ( curr_thy );
	       }
               break;
	     case prove_rule_menu :
               ProveRuleMenu ( 0, 0 );
               ProveRuleMenu ( 1, 0 );
               break;
	   }
           string_box_flag = 0;
           browse_a_theory_is_up = browse_a_theory_is_up_save;
           BrowseATheory ( browse_a_theory_is_up, 0 );
	 }
         else {
	   /*           kil(f);  done in macmch! */
           popup_after_time_elapsed = 1;
           Popup_Info ( "     Input does not parse!     " );
	 }
       }
       break;
    }
  }
}

XtCallbackProc
LargeStringBox_cancel_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  XtPopdown ( XtParent ( XtParent ( XtParent ( widget ) ) ) );
}

LargeStringBox ( prompt, label )
char * prompt;
char * label;
{
  static Widget dialog, dialog_form,
                B_logo, Label, sep,
                text, bot_form,
                ok, cancel;
  Arg args [ 30 ];
  XmString xstr;
  int n;
  static int first_time = 1;

  if ( first_time ) {

    first_time = 0;

    dialog =
          XmCreateDialogShell ( top_frame_form, "BrowseDialog", NULL, 0 );

    XtAddCallback ( dialog, XmNpopupCallback,
        ( XtCallbackProc ) PositionWidgetRelCurrMenu_CB,
        NULL );

    dialog_form = XtVaCreateWidget ( "BrowseDialog",
        xmFormWidgetClass,         dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNdefaultPosition,        False,  
        NULL );

    B_logo =  XtVaCreateWidget ( "BrowseDialog",
        xmLabelWidgetClass,         dialog_form,
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

    xstr = XmStringCreateLtoR ( "  New Rule:  ", charset );
    Label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              5,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNleftOffset,             45,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNrightOffset,            70,
        XmNlabelString,            xstr,
        XmNmarginWidth,            10,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

    sep = XtVaCreateManagedWidget ( "BrowseDialog", 
      xmSeparatorGadgetClass,  dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         48,
      NULL );

    n = 0;
    XtSetArg ( args [ n ], XmNrows,                  5                 ); n++;
    XtSetArg ( args [ n ], XmNcolumns,               50                ); n++;
    XtSetArg ( args [ n ], XmNeditable,              True              ); n++;
    XtSetArg ( args [ n ], XmNeditMode,              XmMULTI_LINE_EDIT ); n++;
    XtSetArg ( args [ n ], XmNcursorPositionVisible, True              ); n++;
    XtSetArg ( args [ n ], XmNscrollHorizontal,      False             ); n++;
    XtSetArg ( args [ n ], XmNwordWrap,              True              ); n++;
    XtSetArg ( args [ n ], XmNmarginWidth,           5                 ); n++;
    XtSetArg ( args [ n ], XmNmarginHeight,          5                 ); n++;
    XtSetArg ( args [ n ], XmNshadowThickness,       3                 ); n++;
    XtSetArg ( args [ n ], XmNtopAttachment,         XmATTACH_FORM     ); n++;
    XtSetArg ( args [ n ], XmNtopOffset,             50                ); n++;
    XtSetArg ( args [ n ], XmNrightAttachment,       XmATTACH_FORM     ); n++;
    XtSetArg ( args [ n ], XmNrightOffset,           5                 ); n++;
    XtSetArg ( args [ n ], XmNleftAttachment,        XmATTACH_FORM     ); n++;
    XtSetArg ( args [ n ], XmNleftOffset,            5                 ); n++;
    XtSetArg ( args [ n ], XmNbottomAttachment,      XmATTACH_WIDGET   ); n++;
    XtSetArg ( args [ n ], XmNbottomWidget,          sep               ); n++;
    XtSetArg ( args [ n ], XmNbottomOffset,          10                ); n++;
    XtSetArg ( args [ n ], XmNfontList,              fontlist          ); n++;
    /*
    XtSetArg ( args [ n ], XmNscrollBarDisplayPolicy,  XmAS_NEEDED     ); n++;
    XtSetArg ( args [ n ], XmNscrollingPolicy,       XmAUTOMATIC       ); n++;
    XtSetArg ( args [ n ], XmNshadowThickness,       0                 ); n++;
    */
    XtSetArg ( args [ n ], XmNborderWidth,           0                 ); n++;

    text =
        XmCreateScrolledText ( dialog_form, "Canvas", args, n );
  
    bot_form = XtVaCreateWidget ( "ButtonLabel",
        xmFormWidgetClass,       dialog_form,
        XmNleftAttachment,       XmATTACH_FORM,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNtopAttachment,        XmATTACH_WIDGET,
        XmNtopWidget,            sep,
        XmNtopOffset,            3,
        NULL );

    ok = XtVaCreateManagedWidget ( "OK", 
        xmPushButtonGadgetClass, bot_form,
        XmNleftAttachment,       XmATTACH_FORM,
        XmNleftOffset,           15,
        XmNtopAttachment,        XmATTACH_FORM,
        XmNtopOffset,            6,
        XmNheight,               25,
        XmNwidth,                57,
        XmNdefaultButtonShadowThickness,        0,
        XmNhighlightThickness,   0,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XtAddCallback ( ok, XmNactivateCallback,
        ( XtCallbackProc ) LargeStringBox_ok_CB,
        ( XtPointer ) text );

    cancel = XtVaCreateManagedWidget ( "Cancel", 
        xmPushButtonGadgetClass, bot_form,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNrightOffset,          15,
        XmNtopAttachment,        XmATTACH_FORM,
        XmNtopOffset,            6,
        XmNheight,               25,
        XmNwidth,                57,
        XmNdefaultButtonShadowThickness,        0,
        XmNhighlightThickness,   0,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XtAddCallback ( cancel, XmNactivateCallback,
        ( XtCallbackProc ) LargeStringBox_cancel_CB,
        ( XtPointer ) text );

  } /* first_time */

  XmTextSetString ( text, label );
  XmTextShowPosition ( text, ( XmTextPosition ) strlen ( label ) );
  XmTextSetInsertionPosition ( text, ( XmTextPosition ) strlen ( label ) );
  XmUpdateDisplay ( text );

  XtManageChild ( B_logo );
  XtManageChild ( Label );
  XtManageChild ( text );
  XtManageChild ( bot_form );
  XtManageChild ( dialog_form );
  XtRealizeWidget ( dialog );

  if ( ( string_box_flag == string_box_new_rule_from_browse ) ||
       ( string_box_flag == string_box_change_rule_from_browse ) ) {
    XtVaSetValues ( dialog_form,
        XmNbackground,            Browse_bck_col,
        XmNtopShadowColor,        Browse_top_col,
        NULL );
    XtVaSetValues ( text,
        XmNbackground,            Browse_text_bck_col,
        NULL );
    XtVaSetValues ( Label,
        XmNbackground,            Browse_bck_col,
        NULL );
    XtVaSetValues ( bot_form,
        XmNbackground,            Browse_bck_col,
        XmNforeground,            Browse_but_lab_col,
        NULL );
  }
  else {
    XtVaSetValues ( dialog_form,
        XmNbackground,            Prompt_bck_col,
        XmNtopShadowColor,        Prompt_top_col,
        XmNbottomShadowColor,     Prompt_bot_col,
        NULL );
    XtVaSetValues ( text,
        XmNbackground,            Prompt_text_bck_col,
        NULL );
    XtVaSetValues ( Label,
        XmNbackground,            Prompt_bck_col,
        NULL );
    XtVaSetValues ( bot_form,
        XmNbackground,            Prompt_bck_col,
        XmNforeground,            Prompt_but_lab_col,
        NULL );
  }

  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay ( dialog );

}


QueryBox_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;
  Dimension top_level_w, s_d_w;
  int but_num;

  static Position last_query_box_x, last_query_box_y;

/***
printf ( "QueryBox_CB widget=%d query_box_flag=%d cbs->reason=%d\n", widget, query_box_flag, cbs->reason );
printf ( "XtParent ( widget )                          =%d\n", XtParent ( widget ) );
printf ( "XtParent ( XtParent ( widget ) )             =%d\n", XtParent ( XtParent ( widget ) ) );
printf ( "XtParent ( XtParent ( XtParent ( widget ) ) )=%d\n", XtParent ( XtParent ( XtParent ( widget ) ) ) );
***/

  if ( cbs->reason == XmCR_PROTOCOLS ) {

/***
printf ( "( Widget ) client_data=%d\n", ( Widget ) client_data );
***/
        XtPopdown ( ( Widget ) client_data );
        XtDestroyWidget ( ( Widget ) client_data );
    but_num = CANCEL_BUTTON;
  }

  else if ( widget != ( Widget ) 0 ) {

    but_num =  * ( int * ) client_data;

    switch ( query_box_flag ) {
    case query_box_ask_ari_prf:
    case query_box_ask_rul_prf:
    case query_box_ask_eql_rul_prf:
    case query_box_ask_hyp_prf:
    case query_box_ask_eql_hyp_prf:
      if ( but_num == CANCEL_BUTTON ) {
        XtPopdown ( XtParent ( XtParent ( widget ) ) );
        XtDestroyWidget ( XtParent ( XtParent ( widget ) ) );
      }
      else {
        XtPopdown ( XtParent ( XtParent ( XtParent ( widget ) ) ) );
        XtDestroyWidget ( XtParent ( XtParent ( XtParent ( widget ) ) ) );
      }
      break;
    default:
      XtPopdown ( XtParent ( XtParent ( XtParent ( widget ) ) ) );
      XtDestroyWidget ( XtParent ( XtParent ( XtParent ( widget ) ) ) );
      break;
    }
  }

  if ( but_num == OK_BUTTON ) {

    switch ( query_box_flag ) {

    case query_box_flag_clear :
      ini;
      DisplayCurrWinText ( "\n  All theory cleared\n" );
      DisplayMainTopWin ();
      if ( browse_a_theory_is_up ) {
        BrowseATheory ( 0, 0 );
        BrowseTheories ( 1, 0 );
      }
      else if ( browse_theories_is_up ) {
        BrowseTheories ( 0, 0 );
        BrowseTheories ( 1, 0 );
      }
      break;

    case query_box_flag_quit :
#ifndef BTOOLKIT_FLAG
      unlink ( "B.xpm" );
#endif
      XmFontListFree ( fontlist );
      exit___ ( 0 );
      break;

    case query_box_flag_rld_src_main :
      CreProofTreeDialog ( 0 );
      mod_reload_sys ( TRUE );
      DisplayCurrWinText ( "\n  Reloading \"" );
      DisplayCurrWinText ( name_load_fil );
      DisplayCurrWinText ( "\"\n" );
      while ( val_reload_sys==TRUE ) {
        mod_reload_sys(FALSE);
        re_ini;
        relod_prf;
      }
      DisplayMainTopWin ();
      if ( browse_a_theory_is_up ) {
        BrowseATheory ( 0, 0 );
        BrowseTheories ( 1, 0 );
      }
      else if ( browse_theories_is_up ) {
        BrowseTheories ( 0, 0 );
        BrowseTheories ( 1, 0 );
      }
      break;

    case query_box_flag_rld_src_a_theory :
      mod_reload_sys ( TRUE );
      DisplayCurrWinText ( "\n  Reloading \"" );
      DisplayCurrWinText ( name_load_fil );
      DisplayCurrWinText ( "\"\n" );
      while ( val_reload_sys==TRUE ) {
        mod_reload_sys(FALSE);
        re_ini;
        relod_prf;
      }
      if ( browse_a_theory_is_up ) {
        BrowseATheory ( 0, 0 );
        BrowseTheories ( 1, 0 );
      }
      else if ( browse_theories_is_up ) {
        BrowseTheories ( 0, 0 );
        BrowseTheories ( 1, 0 );
      }
      PopdownCurrMenu ();
      DisplayMainMenu ( 1, 0 );
      DisplayMainTopWin ();
      break;

    case query_box_flag_rld_src_a_rule :
      mod_reload_sys ( TRUE );
      DisplayCurrWinText ( "\n  Reloading \"" );
      DisplayCurrWinText ( name_load_fil );
      DisplayCurrWinText ( "\"\n" );
      while ( val_reload_sys==TRUE ) {
        mod_reload_sys(FALSE);
        re_ini;
        relod_prf;
      }
      if ( browse_a_theory_is_up ) {
        BrowseATheory ( 0, 0 );
        BrowseTheories ( 1, 0 );
      }
      else if ( browse_theories_is_up ) {
        BrowseTheories ( 0, 0 );
        BrowseTheories ( 1, 0 );
      }
      PopdownCurrMenu ();
      DisplayMainMenu ( 1, 0 );
      DisplayMainTopWin ();
      break;

    case query_box_flag_rem_thy :
      {
        int curr_thy_save;
        curr_thy_save = curr_thy;
        if ( browse_theories_is_up ) {
          BrowseTheories ( 0, 0 );
          BrowseTheories ( 1, 0 );
        }
        else if ( curr_thy_save == browse_a_theory_is_up ) {
          BrowseATheory ( 0, 0 );
          BrowseTheories ( 1, 0 );
        }
        PopdownCurrMenu ();
        DisplayMainMenu ( 1, 0 );
        kil_the ( curr_thy );
        DisplayMainTopWin ();
        strcpy ( str_buf, "\n  Removed " );
        write_nam_the ( curr_thy );
        strcat ( str_buf, "\n" );
        DisplayCurrWinText ( str_buf );
     }
      break;

    case query_box_flag_rem_last_rule :
      CreProofTreeDialog ( 0 );
      rem_rul_the ( curr_thy, len( rul_the ( curr_thy )));
      DisplayATheoryTopWin ( curr_thy );
      if ( browse_theories_is_up ) {
        BrowseTheories ( 0, 0 );
        BrowseTheories ( 1, 0 );
      }
      else if ( curr_thy == browse_a_theory_is_up ) {
        int browse_a_theory_is_up_save;
        browse_a_theory_is_up_save = browse_a_theory_is_up;
        BrowseATheory ( 0, 0 );
        browse_a_theory_is_up = browse_a_theory_is_up_save;
        BrowseATheory ( browse_a_theory_is_up, 0 );
      }
      break;

    case query_box_rem_proof :
      strcpy ( str_buf, "\n  Proof for " );
      write_nam_the ( curr_thy );
      strcat ( str_buf, "." );
      write_nat ( curr_rule );
      strcat ( str_buf, " removed\n" );
      DisplayCurrWinText ( str_buf );
      rem_prv_rul_the ( curr_thy, curr_rule );
#ifdef BTOOLKIT_FLAG
      check_rem_BToolLemmas ( val_rul_the ( curr_thy, curr_rule ) );
#endif
      DisplayARuleTopWin ( 0 );
      DisplayARuleTopWin ( curr_rule );
      CreProofTreeDialog ( 0 );
      DisplayARuleMenu ( 0, 0 );
      DisplayARuleMenu ( 1, 0 );
      if ( browse_theories_is_up ) {
        BrowseTheories ( 0, 0 );
        BrowseTheories ( 1, 0 );
      }
      else if ( curr_thy == browse_a_theory_is_up ) {
        int browse_a_theory_is_up_save;
        browse_a_theory_is_up_save = browse_a_theory_is_up;
        BrowseATheory ( 0, 0 );
        browse_a_theory_is_up = browse_a_theory_is_up_save;
        BrowseATheory ( browse_a_theory_is_up, 0 );
      }
      break;

    case query_box_flag_rem_rule :
      if ( browse_theories_is_up ) {
        BrowseTheories ( 0, 0 );
        BrowseTheories ( 1, 0 );
      }
      else if ( curr_thy == browse_a_theory_is_up ) {
        int browse_a_theory_is_up_save;
        browse_a_theory_is_up_save = browse_a_theory_is_up;
        BrowseATheory ( 0, 0 );
        browse_a_theory_is_up = browse_a_theory_is_up_save;
        BrowseATheory ( browse_a_theory_is_up, 0 );
      }
      PopdownCurrMenu ();
      DisplayATheoryMenu ( 1, 0 );
      rem_rul_the ( curr_thy, curr_rule );
      DisplayATheoryTopWin ( curr_thy );
      break;

    case query_box_quit_proof :
      abt_prf=TRUE;
      run_man_prf_success=TRUE;
      /*      DisplayCurrWinText ( " - aborted\n" ); */
      run_man_prf_run_man_prf_res=run_man_prf_i;
      /*      CreProofTreeDialog ( 0 ); */
#ifdef BTOOLKIT_FLAG
      check_rem_BToolLemmas ( val_rul_the ( curr_thy, curr_rule ) );
#endif
      Proof_CB_continued ( TRUE, proof_step_flag_NO );
      break;

    case query_box_ask_ari_prf :
      ari_prf_2 ( TRUE );
      break;

    case query_box_ask_rul_prf :
/***
printf ( "QueryBox_CB  - test_nrm_rul_prf1\n" );
***/
      test_nrm_rul_prf1 ( TRUE );
      break;

    case query_box_ask_eql_rul_prf :
/***
printf ( "QueryBox_CB  - test3_eql_rul_prf1\n" );
***/
      test3_eql_rul_prf1 ( TRUE );
      break;

    case query_box_ask_hyp_prf :
      switch ( ask_hyp_ret ) {
      case ask_hyp_test_hyp1 :
/***
printf ( "QueryBox_CB  - test_hyp_prf2\n" );
***/
        test_hyp_prf2 ( TRUE );
        break;
      case ask_hyp_test_hyp2 :
/***
printf ( "QueryBox_CB  - test_hyp_prf1\n" );
***/
        test_hyp_prf1 ( TRUE );
        break;
      case ask_hyp_test_imp_hyp1 :
/***
printf ( "QueryBox_CB  - test_imp_hyp_prf1\n" );
***/
        test_imp_hyp_prf1 ( TRUE );
        break;
      case ask_hyp_test_imp_hyp2 :
/***
printf ( "QueryBox_CB  - test_imp_hyp_prf2\n" );
***/
        test_imp_hyp_prf2 ( TRUE );
        break;
      }
      break;

    case query_box_ask_eql_hyp_prf :
      switch ( ask_eql_hyp_ret ) {
      case ask_eql_hyp_test2_eql :
/***
printf ( "QueryBox_CB  - test2_eql_hyp_prf1\n" );
***/
        test2_eql_hyp_prf1 ( TRUE );
        break;
      case ask_eql_hyp_test3_eql1 :
/***
printf ( "QueryBox_CB  - test3_eql_hyp_prf2\n" );
***/
        test3_eql_hyp_prf2 ( TRUE );
        break;
      case ask_eql_hyp_test3_eql2 :
/***
printf ( "QueryBox_CB  - test3_eql_hyp_prf3\n" );
***/
        test3_eql_hyp_prf3 ( TRUE );
        break;
      case ask_eql_hyp_test3_unv :
/***
printf ( "QueryBox_CB  - test3_unv_eql_hyp_prf2\n" );
***/
        test3_unv_eql_hyp_prf2 ( TRUE );
        break;
      case ask_eql_hyp_test2_unv :
/***
printf ( "QueryBox_CB  - test2_unv_eql_hyp_prf2\n" );
***/
        test2_unv_eql_hyp_prf2 ( TRUE );
        break;
      }
      break;

    }

  }

  else {   /* No pressed */

    switch ( query_box_flag ) {

    case query_box_quit_proof :
      run_man_prf_success=FALSE;
      Proof_CB_continued ( TRUE, proof_step_flag_NO );
      break;

    case query_box_ask_ari_prf :
      ari_prf_2 ( FALSE );
      break;

    case query_box_ask_rul_prf :
      test_nrm_rul_prf1 ( FALSE );
      break;

    case query_box_ask_eql_rul_prf :
      test3_eql_rul_prf1 ( FALSE );
      break;

    case query_box_ask_hyp_prf :
      switch ( ask_hyp_ret ) {
      case ask_hyp_test_hyp1 :
        test_hyp_prf2 ( FALSE );
        break;
      case ask_hyp_test_hyp2 :
        test_hyp_prf1 ( FALSE );
        break;
      case ask_hyp_test_imp_hyp1 :
        test_imp_hyp_prf1 ( FALSE );
        break;
      case ask_hyp_test_imp_hyp2 :
        test_imp_hyp_prf2 ( FALSE );
        break;
      }
      break;

    case query_box_ask_eql_hyp_prf :
      switch ( ask_eql_hyp_ret ) {
      case ask_eql_hyp_test2_eql :
        test2_eql_hyp_prf1 ( FALSE );
        break;
      case ask_eql_hyp_test3_eql1 :
        test3_eql_hyp_prf2 ( FALSE );
        break;
      case ask_eql_hyp_test3_eql2 :
        test3_eql_hyp_prf3 ( FALSE );
        break;
      case ask_eql_hyp_test3_unv :
        test3_unv_eql_hyp_prf2 ( FALSE );
        break;
      case ask_eql_hyp_test2_unv :
        test2_unv_eql_hyp_prf2 ( FALSE );
        break;
      }
      break;

#ifndef BTOOLKIT_FLAG

    case query_box_flag_quit :
      DisplayMainMenu ( 1, 0 );
      break;

#endif

    }

  }

}

void
ApplyRuleBox ( rr, highlight_flag )
int rr;
int highlight_flag;
/***
  rr =  0 => ARI          buf is "ARI"
  rr = -1 => HYPOTHESIS   buf is "rule"
  else       rr is rule   buf is "rule"

  str_buf contains the (possibly highlighted) goal
  however, if rr is NOT a rewrite rule, str_buf will be empty!
***/
{
  Widget dialog, dialog_form, B_logo,
         rule_rc, rule_pb, rule_lab, apply_lab,
         goal_lab, goal_scroll, goal_rc, Goal1, Goal2, Goal3,
         instant, format_goal, dismiss;
  XmString xstr;
  Dimension dialog_w;
  int i, j, done, found, width, height;
  char c;
  Atom   WM_DELETE_WINDOW;
  char * tmp_str;
  int malloced;
  int Goal2_formed = 0;

#ifndef BTOOLKIT_FLAG
#define primary_string_len    2500
char primary_string [ primary_string_len ];
#endif

void InstantiateRuleBox_CB ();
void FormattedGoal_CB ();

/***
printf ( "\n\nstr_buf: |" );
i = 0;
while ( str_buf [ i ] != '\0' ) {
  if   ( str_buf [ i ] == rv_char ) printf ( "?" );
  else                              printf ( "%c", str_buf [ i ] );
  i++;
}
printf ( "|\n\n" );
***/

  WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

  width = 0;
  i = 0;
  j = 0;
  while ( str_buf [ i ] != '\0' ) {
    if ( str_buf [ i ] == '\n' ) {
      if ( j > width ) width = j;
      j = 0;
    }
    else {
      j++;
    }
    i++;
  }
  if ( j > width ) width = j;

  width = width * 10;
  if ( width > 750 ) width = 750;
  if ( width < 500 ) width = 500;

  j = 0;
  if ( rr ) {  /* buf contains the rule */
    i = 0;
    while ( buf [ i ] != '\0' ) {
      if ( buf [ i ] == '\n' ) j++;
      i++;
    }
  }
  height = 250 + ( j * 10 );


  done = 0;
  while ( ! done ) {
    found = 0;
    i = 0;
    while ( ( ! found ) && ( str_buf [ i ] != '\0' ) ) {
      if ( ( int ) strlen ( str_buf ) >= i + 3 ) {
        if ( ( str_buf [ i ] == rv_char )     &&
             ( str_buf [ i + 1 ] == rv_char )    ) {
          i = i + 2;
          while ( str_buf [ i ] != '\0' ) {
            str_buf [ i - 2 ] = str_buf [ i ];
            i++;
	  }
          str_buf [ i - 2 ] = '\0';
          found = 1;
	}
        else if ( ( str_buf [ i ] == rv_char )     &&
                  ( str_buf [ i + 1 ] == '\n' )    &&
                  ( str_buf [ i + 2 ] == rv_char )     ) {
          i = i + 3;
          while ( str_buf [ i ] != '\0' ) {
            str_buf [ i - 3 ] = str_buf [ i ];
            i++;
	  }
          str_buf [ i - 3 ] = '\0';
          found = 1;
	}
      }
      if ( ! found ) i++;
    }
    if ( ! found ) done = 1;
  }

/***
printf ( "\n\nstr_buf: |" );
i = 0;
while ( str_buf [ i ] != '\0' ) {
  if   ( str_buf [ i ] == rv_char ) printf ( "?" );
  else                              printf ( "%c", str_buf [ i ] );
  i++;
}
printf ( "|\n\n" );
***/

  done = 0;
  while ( ! done ) {
    i = 0;
    j = 0;
    while ( ( str_buf [ i ] != '\0' ) && ( str_buf [ i ] != '\n' ) ) {
      i++;
      j++;
    }
    if ( str_buf [ i ] != '\0' ) {
      str_buf [ j++ ] = ' ';
      i++;
      while ( str_buf [ i ] == ' ' ) i++;
      while ( str_buf [ i ] != '\0' ) {
        str_buf [ j++ ] = str_buf [ i++ ];
      }
      str_buf [ j ] = '\0';
    }
    else {
      done = 1;
    }
  }

  dialog =
     XmCreateDialogShell ( curr_dialog_menu, "ApplyRuleDialog", NULL, 0 );

  XmAddWMProtocolCallback ( dialog, WM_DELETE_WINDOW,
      ( XtCallbackProc ) QueryBox_CB,
      ( XtPointer ) dialog );

  dialog_form = XtVaCreateWidget ( "ApplyRuleDialog",
        xmFormWidgetClass,         dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        True,  
        XmNmarginWidth,            5,
        XmNautoUnmanage,           False,
/*
        XmNwidth,                  width,
	XmNheight,                 height,
*/
        NULL );

  B_logo =  XtVaCreateManagedWidget ( "ApplyRuleDialog",
        xmLabelWidgetClass,         dialog_form,
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

  if ( ( int ) strlen ( str_buf ) < primary_string_len - 5 ) {
    tmp_str = primary_string;
    malloced = 0;
  }
  else {
/***
printf ( "malloc\n" );
***/
    tmp_str = ( char * ) malloc ( ( strlen ( str_buf ) + 5 ) * sizeof ( char ) );
#ifdef BTOOLKIT_FLAG
    if ( tmp_str == NULL ) { BT_crash_err_exit ( 2270 ); return; }
#else
    if ( tmp_str == NULL ) { printf ( "\n\n  Cannot perform malloc\n\n" ); exit; }
#endif
    malloced = 1;
  }
  strcpy ( tmp_str, str_buf );

  if ( rr == 0 ) {
    strcpy ( str_buf, "ARI" );
  }
  else if ( rr == -1 ) {
    strcpy ( str_buf, "HYPOTHESIS" );
  }
  else {
    str_buf [ 0 ] = '\0';
    write_nam_the(the_rul(rr));
    strcat ( str_buf, ".");
    write_nat(num_rul(rr));
  }

  xstr = XmStringCreateLtoR ( str_buf, charset );
  rule_lab = XtVaCreateManagedWidget ( "Label", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNleftOffset,             20,
        XmNlabelString,            xstr,
        XmNfontList,               fontlist,
        XmNshadowThickness,        0,
        XmNmarginWidth,            0,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
  XmStringFree ( xstr );

  strcpy ( str_buf, tmp_str );         /* free (if reqd) done down below */

  if ( rr == 0 ) {
    xstr = XmStringCreateLtoR ( "(Click to apply ARI)", charset );
  }
  else {
    if ( str_buf [ 0 ] != '\0' ) 
      xstr = XmStringCreateLtoR ( "(Click to apply re-write rule)", charset );
    else
      xstr = XmStringCreateLtoR ( "(Click to apply rule)         ", charset );
  }

  apply_lab = XtVaCreateManagedWidget ( "Highlight", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             rule_lab,
        XmNleftOffset,             5,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNrightOffset,            50,
        XmNlabelString,            xstr,
        XmNshadowThickness,        0,
        XmNmarginWidth,            10,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
  XmStringFree ( xstr );

  if ( str_buf [ 0 ] != '\0' ) {            /* there will be a goal_scroll */
    rule_rc = XtVaCreateManagedWidget ( "ApplyRuleDialog",
        xmRowColumnWidgetClass,    dialog_form,
        XmNtopAttachment,          XmATTACH_WIDGET,
        XmNtopWidget,              rule_lab,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_FORM,
        XmNleftOffset,             0,
        XmNlabelString,            xstr,
        XmNorientation,            XmVERTICAL,
        XmNmarginWidth,            25,
        XmNmarginHeight,           5,
        XmNspacing,                10,
        XmNisHomogeneous,          False,
        XmNtraversalOn,            True,
        NULL );
  }
  else {                              /* no goal_scroll, so attach to bottom */
    rule_rc = XtVaCreateManagedWidget ( "ApplyRuleDialog",
        xmRowColumnWidgetClass,    dialog_form,
        XmNtopAttachment,          XmATTACH_WIDGET,
        XmNtopWidget,              rule_lab,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_FORM,
        XmNleftOffset,             0,
        XmNbottomAttachment,       XmATTACH_FORM,
        XmNbottomOffset,           65,
        XmNlabelString,            xstr,
        XmNorientation,            XmVERTICAL,
        XmNmarginWidth,            25,
        XmNmarginHeight,           5,
        XmNspacing,                10,
        XmNisHomogeneous,          False,
        XmNtraversalOn,            True,
        NULL );
  }

  xstr = XmStringCreateLtoR ( buf, charset );
  rule_pb = XtVaCreateManagedWidget ( "Rule", 
        xmPushButtonGadgetClass,   rule_rc,
        XmNlabelString,            xstr,
        XmNfontList,               fontlist,
        XmNshadowThickness,        0,
        XmNdefaultButtonShadowThickness,   1,
        XmNhighlightThickness,     1,
        XmNnavigationType,         XmTAB_GROUP,
        NULL );
  XmStringFree ( xstr );

  XtAddCallback ( rule_pb, XmNactivateCallback,
      ( XtCallbackProc ) QueryBox_CB, 
      ( XtPointer ) & c_arr [ OK_BUTTON ] );

  if ( str_buf [ 0 ] != '\0' ) {

    xstr = XmStringCreateLtoR ( "GOAL:", charset );
    goal_lab = XtVaCreateManagedWidget ( "Label", 
          xmLabelWidgetClass,        dialog_form,
          XmNtopAttachment,          XmATTACH_WIDGET,
          XmNtopWidget,              rule_rc,
          XmNtopOffset,              10,
	  XmNleftAttachment,         XmATTACH_FORM,
          XmNleftOffset,             15,
          XmNlabelString,            xstr,
          XmNfontList,               fontlist,
          XmNshadowThickness,        0,
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          XmNtraversalOn,            False,
          NULL );
    XmStringFree ( xstr );

    goal_scroll = XtVaCreateWidget ( "ApplyRuleDialog",
          xmScrolledWindowWidgetClass,    dialog_form,
          XmNtopAttachment,               XmATTACH_WIDGET,
          XmNtopWidget,                   goal_lab,
          XmNtopOffset,                   5,
	  XmNleftAttachment,              XmATTACH_FORM,
          XmNleftOffset,                  15,
	  XmNrightAttachment,             XmATTACH_FORM,
          XmNrightOffset,                 15,
          XmNbottomAttachment,            XmATTACH_FORM,
          XmNbottomOffset,                55,
          XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
          XmNscrollingPolicy,             XmAUTOMATIC,
          XmNborderWidth,                 0,
          XmNshadowThickness,             0,
          NULL );

    goal_rc = XtVaCreateWidget ( "Goal", 
          xmRowColumnWidgetClass,    goal_scroll,
          XmNorientation,            XmHORIZONTAL,
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          XmNspacing,                0,
/*
	  XmNisHomogeneous,          False,
*/
          NULL );

    i = 0;
    while ( ( str_buf [ i ] != rv_char ) && ( str_buf [ i ] != '\0' ) ) { i++; }
    c = str_buf [ i ];
    str_buf [ i ] = '\0';

/***
printf ( "Goal1: |%s|%d %d\n", str_buf, strlen ( str_buf ), MAX_str_buf );
***/

    xstr = XmStringCreateLtoR ( str_buf, charset );
    Goal1 = XtVaCreateManagedWidget ( "Goal", 
          xmLabelWidgetClass,        goal_rc,
          XmNlabelString,            xstr,
          XmNfontList,               fontlist,
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          XmNtraversalOn,            False,
          NULL );
    XmStringFree ( xstr );

    str_buf [ i ] = c;
    if ( str_buf [ i ] != '\0' ) i++;

    j = 0;
    while ( str_buf [ i ] != '\0' ) {
      str_buf [ j++ ] = str_buf [ i++ ];
    }
    str_buf [ j ] = '\0';
    i = 0;
    while ( ( str_buf [ i ] != rv_char ) && ( str_buf [ i ] != '\0' ) ) {
      i++;
    }
    c = str_buf [ i ];
    str_buf [ i ] = '\0';

/***
printf ( "Goal2: |%s|%d %d\n", str_buf, strlen ( str_buf ), MAX_str_buf );
***/

    xstr = XmStringCreateLtoR ( str_buf, charset );
    Goal2 = XtVaCreateManagedWidget ( "Highlight", 
          xmLabelWidgetClass,        goal_rc,
          XmNlabelString,            xstr,
          XmNfontList,               fontlist,
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          XmNtraversalOn,            False,
          NULL );
    XmStringFree ( xstr );
    str_buf [ i ] = c;
    if ( str_buf [ i ] != '\0' ) i++;

    j = 0;
    while ( str_buf [ i ] != '\0' ) {
      str_buf [ j++ ] = str_buf [ i++ ];
    }
    str_buf [ j ] = '\0';
    Goal2_formed = 1;

/***
printf ( "Goal3: |%s|%d %d\n", str_buf, strlen ( str_buf ), MAX_str_buf );
***/

    xstr = XmStringCreateLtoR ( str_buf, charset );
    Goal3 = XtVaCreateManagedWidget ( "Goal", 
          xmLabelWidgetClass,        goal_rc,
          XmNlabelString,            xstr,
          XmNfontList,               fontlist,
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          XmNtraversalOn,            False,
          NULL );
    XmStringFree ( xstr );

    XtManageChild ( goal_rc );
    XtManageChild ( goal_scroll );

    if ( rr != 0 ) {    /* ie. not ARI */
      xstr = XmStringCreateLtoR ( "Instantiate", charset );
      instant = XtVaCreateManagedWidget ( "ButtonLabel", 
          xmPushButtonGadgetClass, dialog_form,
          XmNlabelString,          xstr,
          XmNleftAttachment,       XmATTACH_FORM,
          XmNleftOffset,           5,
          XmNbottomAttachment,     XmATTACH_FORM,
          XmNbottomOffset,         10,
          XmNheight,               28,
          XmNwidth,                90,
          XmNdefaultButtonShadowThickness,        1,
          XmNhighlightThickness,   1,
          XmNnavigationType,       XmTAB_GROUP,
          NULL );
     XmStringFree ( xstr );
    }

    xstr = XmStringCreateLtoR ( "Don't Apply", charset );
    dismiss = XtVaCreateManagedWidget ( "ButtonLabel", 
        xmPushButtonGadgetClass, dialog_form,
        XmNlabelString,          xstr,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNrightOffset,          5,
        XmNbottomAttachment,     XmATTACH_FORM,
        XmNbottomOffset,         10,
        XmNheight,               28,
        XmNwidth,                90,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   1,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XmStringFree ( xstr );

    xstr = XmStringCreateLtoR ( "Show formatted goal", charset );
    format_goal = XtVaCreateManagedWidget ( "ButtonLabel", 
        xmPushButtonGadgetClass, dialog_form,
        XmNlabelString,          xstr,
        XmNleftAttachment,       XmATTACH_FORM,
        XmNleftOffset,           125,
        XmNbottomAttachment,     XmATTACH_FORM,
        XmNbottomOffset,         10,
        XmNheight,               28,
        XmNwidth,                155,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   1,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XmStringFree ( xstr );

    XtAddCallback ( format_goal, XmNactivateCallback,
        ( XtCallbackProc ) FormattedGoal_CB,
        ( XtPointer ) dialog );

  } 

  else { /* str_buf [ 0 ] == '\0', so no goal scroll & no formatted goal! */

    if ( rr != 0 ) {
      xstr = XmStringCreateLtoR ( "Instantiate", charset );
      instant = XtVaCreateManagedWidget ( "ButtonLabel", 
          xmPushButtonGadgetClass, dialog_form,
          XmNlabelString,          xstr,
          XmNleftAttachment,       XmATTACH_FORM,
          XmNleftOffset,           5,
          XmNbottomAttachment,     XmATTACH_FORM,
          XmNbottomOffset,         10,
          XmNheight,               28,
          XmNwidth,                90,
          XmNdefaultButtonShadowThickness,        1,
          XmNhighlightThickness,   1,
          XmNnavigationType,       XmTAB_GROUP,
          NULL );
      XmStringFree ( xstr );
    }

    xstr = XmStringCreateLtoR ( "Don't Apply", charset );
    dismiss = XtVaCreateManagedWidget ( "ButtonLabel", 
        xmPushButtonGadgetClass, dialog_form,
        XmNlabelString,          xstr,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNrightOffset,          5,
        XmNbottomAttachment,     XmATTACH_FORM,
        XmNbottomOffset,         10,
        XmNheight,               28,
        XmNwidth,                90,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   1,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XmStringFree ( xstr );

  }

  if ( rr != 0 ) {
    XtAddCallback ( instant, XmNactivateCallback,
        ( XtCallbackProc ) InstantiateRuleBox_CB,
        NULL );
  }
  
  strcpy ( str_buf, tmp_str );
  if ( malloced ) {
/***
printf ( "free\n" );
***/
    free ( tmp_str );
    malloced = 0;
  }

  XtAddCallback ( dismiss, XmNactivateCallback,
      ( XtCallbackProc ) QueryBox_CB, 
      ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );

  XtManageChild ( dialog_form );

  XtRealizeWidget ( dialog );

  if ( Goal2_formed ) {
    XmScrollVisible ( goal_scroll, Goal2, 150, 0 );
    XmUpdateDisplay ( goal_scroll );
  }

  XtManageChild ( dialog );
  XmProcessTraversal ( rule_pb, XmTRAVERSE_CURRENT );  

}

void
InstantiateRuleBox_CB_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  XtUnmanageChild ( ( Widget ) client_data );
  XtDestroyWidget ( ( Widget ) client_data );
}

void
InstantiateRuleBox_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  Widget dialog, dialog_form, B_logo, rule_lab, rule_rc, rule, dismiss;
  XmString xstr;
  char * tmp_str;
  int malloced;
#ifndef BTOOLKIT_FLAG
#define primary_string_len    2500
char primary_string    [ primary_string_len ];
#endif

  if ( ( int ) strlen ( str_buf ) < primary_string_len - 5 ) {
    tmp_str = primary_string;
    malloced = 0;
  }
  else {
/***
printf ( "malloc\n" );
***/
    tmp_str = ( char * ) malloc ( ( strlen ( str_buf ) + 5 ) * sizeof ( char ) );
#ifdef BTOOLKIT_FLAG
    if ( tmp_str == NULL ) { BT_crash_err_exit ( 2270 ); return; }
#else
    if ( tmp_str == NULL ) { printf ( "\n\n  Cannot perform malloc\n\n" ); exit; }
#endif
    malloced = 1;
  }
  strcpy ( tmp_str, str_buf );

  dialog =
     XmCreateDialogShell ( XtParent ( widget ),
                                     "InstantiateRuleDialog", NULL, 0 );

  dialog_form = XtVaCreateWidget ( "InstantiateRuleDialog",
        xmFormWidgetClass,         dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        True,  
        XmNmarginWidth,            5,
        NULL );

  B_logo =  XtVaCreateManagedWidget ( "InstantiateRuleDialog",
        xmLabelWidgetClass,         dialog_form,
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

  if ( query_box_rule < 0 ) {
    strcpy ( str_buf, "Instantiation of HYPOTHESIS" );
  }
  else {
    strcpy ( str_buf, "Instantiation of " );
    write_nam_the(the_rul(query_box_rule));
    strcat ( str_buf, ".");
    write_nat(num_rul(query_box_rule));
  }

  xstr = XmStringCreateLtoR ( str_buf, charset );
  rule_lab = XtVaCreateManagedWidget ( "Label", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNleftOffset,             8,
        XmNlabelString,            xstr,
        XmNfontList,               fontlist,
        XmNshadowThickness,        0,
        XmNmarginWidth,            0,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
  XmStringFree ( xstr );

  rule_rc = XtVaCreateManagedWidget ( "InstantiatedRule", 
        xmRowColumnWidgetClass,    dialog_form,
        XmNtopAttachment,          XmATTACH_WIDGET,
        XmNtopWidget,              rule_lab,
        XmNtopOffset,              20,
        XmNleftAttachment,         XmATTACH_FORM,
        XmNleftOffset,             20,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNrightOffset,            20,
        XmNisHomogeneous,          False,
        XmNtraversalOn,            False,
        NULL );

  if ( query_box_rule < 0 ) {
    cre_instant_hyp ( (-query_box_rule) );
  }
  else {
    cre_instant_rule ( query_box_rule );
  }
  xstr = XmStringCreateLtoR ( str_buf, charset );
  rule = XtVaCreateManagedWidget ( "InstantiatedRule", 
        xmLabelWidgetClass,        rule_rc,
        XmNlabelString,            xstr,
        XmNfontList,               fontlist,
        XmNtraversalOn,            False,
        NULL );
  XmStringFree ( xstr );

  xstr = XmStringCreateLtoR ( "Dismiss", charset );
  dismiss = XtVaCreateManagedWidget ( "ButtonLabel", 
      xmPushButtonGadgetClass, dialog_form,
      XmNlabelString,          xstr,
      XmNtopAttachment,        XmATTACH_WIDGET,
      XmNtopWidget,            rule,
      XmNtopOffset,            15,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          10,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         10,
      XmNheight,               28,
      XmNwidth,                90,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XmStringFree ( xstr );

  XtAddCallback ( dismiss, XmNactivateCallback,
      ( XtCallbackProc ) InstantiateRuleBox_CB_CB,
      ( XtPointer ) dialog );

  strcpy ( str_buf, tmp_str );
  if ( malloced ) {
/***
printf ( "free\n" );
***/
    free ( tmp_str );
    malloced = 0;
  }

  XtManageChild ( dialog_form );
  XtRealizeWidget ( dialog );

  XtManageChild ( dialog );
  XmProcessTraversal ( dismiss, XmTRAVERSE_CURRENT );

}

void
FormattedGoal_CB_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  XtUnmanageChild ( ( Widget ) client_data );
  XtDestroyWidget ( ( Widget ) client_data );
}

void
Pre_FormattedGoal_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  void FormattedGoal_CB ();
  int goal =  * ( int * ) client_data;
  strcpy ( str_buf, " " );
  write_frm_first_prooftree_goal ( frm_gol ( goal ) );

  FormattedGoal_CB ( ( Widget ) NULL, ( XtPointer ) NULL, ( XtPointer ) NULL );
}

void
FormattedGoal_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{

  /***
  str_buf contains the goal
  ***/

  Widget dialog, dialog_form, B_logo, rule_lab, rule_scroll, rule_rc, rule, dismiss;
  XmString xstr;
  int f, malloced, i, j, height, width, tot;
  char * tmp_str;

#ifndef BTOOLKIT_FLAG
#define primary_string_len    2500
char primary_string    [ primary_string_len ];
#endif

/***
printf ( "FormattedGoal_CB (str_buf):\n-----\n%s\n-----\n", str_buf );
***/

  f = read_frmfunc_str_buf();
  if ( f == -999 ) {
    Popup_Info ( "  Problem formatting goal"  );
    return;
  }
 
  if ( ( int ) strlen ( str_buf ) < primary_string_len - 5 ) {
    tmp_str = primary_string;
    malloced = 0;
  }
  else {
/***
printf ( "malloc\n" );
***/
    tmp_str = ( char * ) malloc ( ( strlen ( str_buf ) + 5 ) * sizeof ( char ) );
#ifdef BTOOLKIT_FLAG
    if ( tmp_str == NULL ) { BT_crash_err_exit ( 2270 ); return; }
#else
    if ( tmp_str == NULL ) { printf ( "\n\n  Cannot perform malloc\n\n" ); exit; }
#endif
    malloced = 1;
  }
  strcpy ( tmp_str, str_buf );

  read_rul_the ( 2, f );
  tot = nbr_rul_the ( 2 );
  str_buf [ 0 ] = '\0';
  write_ver_rul_dave ( val_rul_the ( 2, tot ) );
  rem_rul_the ( 2, tot );         /* this also does the kil for f */

  height = 1;
  width = 0;
  i = 0;
  j = 0;
  while ( str_buf [ i ] != '\0' ) {
    if ( str_buf [ i ] == '\n' ) {
      height++;
      if ( j > width ) width = j;
      j = 0;
    }
    else {
      j++;
    }
    i++;
  }
  if ( j > width ) width = j;

  if ( height > 14 ) height = 14;
  height = ( height - 1 ) * 30 + 150;

  width = width * 10;
  if ( width > 750 ) width = 750;
  if ( width < 500 ) width = 500;

  dialog = XmCreateDialogShell ( bot_display_frame,
                                     "FormattedGoalDialog", NULL, 0 );

  dialog_form = XtVaCreateWidget ( "FormattedGoalDialog",
        xmFormWidgetClass,         dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        True,  
        XmNmarginWidth,            5,
        XmNheight,                 height,
        XmNwidth,                  width,
        NULL );

  B_logo =  XtVaCreateManagedWidget ( "FormattedGoalDialog",
        xmLabelWidgetClass,         dialog_form,
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

  xstr = XmStringCreateLtoR ( "Formatted Goal:", charset );
  rule_lab = XtVaCreateManagedWidget ( "ButtonLabel", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNleftOffset,             8,
        XmNlabelString,            xstr,
        XmNfontList,               fontlist,
        XmNshadowThickness,        0,
        XmNmarginWidth,            0,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
  XmStringFree ( xstr );

  rule_scroll = XtVaCreateWidget ( "Goal",
        xmScrolledWindowWidgetClass,    dialog_form,
        XmNtopAttachment,               XmATTACH_WIDGET,
        XmNtopWidget,                   rule_lab,
        XmNtopOffset,                   10,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  10,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 10,
        XmNbottomAttachment,            XmATTACH_FORM,
        XmNbottomOffset,                55,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        NULL );

  rule_rc = XtVaCreateManagedWidget ( "Goal", 
        xmRowColumnWidgetClass,    rule_scroll,
        XmNisHomogeneous,          False,
        XmNtraversalOn,            False,
        XmNmarginWidth,            0,
        XmNmarginHeight,           0,
        XmNspacing,                0,
        NULL );

  xstr = XmStringCreateLtoR ( str_buf, charset );
  rule = XtVaCreateManagedWidget ( "Goal", 
        xmLabelWidgetClass,        rule_rc,
        XmNlabelString,            xstr,
        XmNfontList,               fontlist,
        XmNtraversalOn,            False,
        NULL );
  XmStringFree ( xstr );

  strcpy ( str_buf, tmp_str );
  if ( malloced ) {
/***
printf ( "free\n" );
***/
    free ( tmp_str );
    malloced = 0;
  }

  xstr = XmStringCreateLtoR ( "Dismiss", charset );
  dismiss = XtVaCreateManagedWidget ( "ButtonLabel", 
      xmPushButtonGadgetClass, dialog_form,
      XmNlabelString,          xstr,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          10,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         10,
      XmNheight,               28,
      XmNwidth,                90,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XmStringFree ( xstr );

  XtAddCallback ( dismiss, XmNactivateCallback,
      ( XtCallbackProc ) FormattedGoal_CB_CB,
      ( XtPointer ) dialog );

  XtManageChild ( dialog_form );
  XtManageChild ( rule_scroll );
  XtRealizeWidget ( dialog );

  XtManageChild ( dialog );
  XmProcessTraversal ( dismiss, XmTRAVERSE_CURRENT );

}



void
QueryBox ( text )
char * text;
{
  Widget dialog, dialog_form, B_logo, Label, sep, bot_form, yes, no;
  XmString xstr;
  Dimension dialog_w;
  Atom   WM_DELETE_WINDOW;

  WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

  dialog =  XmCreateDialogShell ( curr_dialog_menu, "SelDialog", NULL, 0 );

  XmAddWMProtocolCallback ( dialog, WM_DELETE_WINDOW,
      ( XtCallbackProc ) QueryBox_CB,
      ( XtPointer ) dialog );

  dialog_form = XtVaCreateWidget ( "SelDialog",
        xmFormWidgetClass,         dialog,
        XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
        XmNdefaultPosition,        True,
        NULL );

  B_logo =  XtVaCreateWidget ( "SelDialog",
        xmLabelWidgetClass,         dialog_form,
        XmNlabelType,               XmPIXMAP,
        XmNlabelPixmap,             B_framed_pixmap_gray94,
        XmNshadowThickness,         0,
        XmNmarginWidth,             0,
        XmNmarginHeight,            0,
        XmNtopAttachment,           XmATTACH_FORM,
        XmNtopOffset,               15,
        XmNleftAttachment,          XmATTACH_FORM,
        XmNleftOffset,              15,
        XmNtraversalOn,             False,
        NULL );

  xstr = XmStringCreateLtoR ( text, charset );
  Label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              17,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNleftOffset,             25,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNrightOffset,            50,
        XmNlabelString,            xstr,
        XmNfontList,               fontlist,
        XmNmarginWidth,            5,
        XmNmarginHeight,           5,
        XmNtraversalOn,            False,
        NULL );
  XmStringFree ( xstr );

  sep = XtVaCreateManagedWidget ( "SelDialog", 
      xmSeparatorGadgetClass,  dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         /* 58, */ 52,
      XmNtopAttachment,        XmATTACH_WIDGET,
      XmNtopWidget,            Label,
      XmNtopOffset,            15,
      NULL );

  bot_form = XtVaCreateWidget ( "ButtonLabel",
      xmFormWidgetClass,       dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNtopAttachment,        XmATTACH_WIDGET,
      XmNtopWidget,            sep,
      XmNtopOffset,            3,
      NULL );

  yes = XtVaCreateManagedWidget ( "Yes", 
      xmPushButtonGadgetClass, bot_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           15,
      XmNtopAttachment,        XmATTACH_FORM,
				  /*      XmNtopOffset,            6, */
      XmNheight,               28,
      XmNwidth,                50,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( yes, XmNactivateCallback,
      ( XtCallbackProc ) QueryBox_CB, 
      ( XtPointer ) & c_arr [ OK_BUTTON ] );
  
  no = XtVaCreateManagedWidget ( "No", 
      xmPushButtonGadgetClass, bot_form,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          15,
      XmNtopAttachment,        XmATTACH_FORM,
				 /*       XmNtopOffset,            6, */
      XmNheight,               28,
      XmNwidth,                40,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( no, XmNactivateCallback,
      ( XtCallbackProc ) QueryBox_CB, 
      ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
  
  XtManageChild ( B_logo );
  XtManageChild ( Label );
  XtManageChild ( bot_form );
  XtManageChild ( dialog_form );

  XtRealizeWidget ( dialog );

/***
print_XmNtraversalOn_value ( "B_logo", B_logo );
print_XmNtraversalOn_value ( "Label", Label );
print_XmNtraversalOn_value ( "sep", sep );
print_XmNtraversalOn_value ( "bot_form", bot_form );
print_XmNtraversalOn_value ( "yes", yes );
print_XmNtraversalOn_value ( "no", no );
***/

  XtManageChild ( dialog );
  XmProcessTraversal ( yes, XmTRAVERSE_CURRENT );

}

#ifndef BTOOLKIT_FLAG

XtCallbackProc
FileSel_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  char * filename;
  int ll;
  XmFileSelectionBoxCallbackStruct * cbs =
    ( XmFileSelectionBoxCallbackStruct * ) call_data;
  int but_num =  * ( int * ) client_data;

  XtUnmanageChild ( widget );

  switch ( file_sel_flag ) {

    case file_sel_flag_load_bin : 

      switch ( but_num ) {
        case CANCEL_BUTTON :
          break;
        case OK_BUTTON :
          if ( XmStringGetLtoR 
	       ( cbs->value, XmSTRING_DEFAULT_CHARSET, &filename ) ) {
            if ( ! * filename ) {
              Popup_Info ( "     No file selected!         " );
              XtFree ( filename );
              return;
            }
            ll = strlen ( filename );
            if ( ll < 5 ) {
              DisplayCurrWinText ( "\n  \"" );
              DisplayCurrWinText ( filename );
              DisplayCurrWinText ( "\" does not end in \".bin\"\n" );
              Popup_Info ( "       Bad filename!         " );
	    }
            else if ( ( filename [ ll - 1 ] != 'n' ) ||
                      ( filename [ ll - 2 ] != 'i' ) ||
                      ( filename [ ll - 3 ] != 'b' ) ||
                      ( filename [ ll - 4 ] != '.' )    ) {
              DisplayCurrWinText ( "\n  \"" );
              DisplayCurrWinText ( filename );
              DisplayCurrWinText ( "\" does not end in \".bin\"\n" );
              XtFree ( filename );
              Popup_Info ( "       Bad filename!         " );
	    }
            else {
              strcpy ( name_restore_fil, filename );
              restore_fil = fopen ( name_restore_fil, "r" );
              if ( restore_fil == NULL ) {
                DisplayCurrWinText ( "\n  Can't read \"" );
                DisplayCurrWinText ( filename );
                DisplayCurrWinText ( "\"\n" );
                XtFree ( filename );
                Popup_Info ( "    Can't read file!        " );
	      }
              else {
                DisplayCurrWinText ( "\n  Read \"" );
                DisplayCurrWinText ( filename );
                DisplayCurrWinText ( "\"\n" );
                strcpy ( name_restore_fil, filename );
                XtFree ( filename );
	        restore_tool;  /* tolmch.c.motif */
                DisplayMainTopWin ();
                if ( browse_a_theory_is_up ) {
                  BrowseATheory ( 0, 0 );
                  BrowseTheories ( 1, 0 );
                }
                else if ( browse_theories_is_up ) {
                  BrowseTheories ( 0, 0 );
                  BrowseTheories ( 1, 0 );
                }
	      }
            }
            break;
          }
          break;
      }
      break;
 
    case file_sel_flag_save_bin : 

      switch ( but_num ) {
        case CANCEL_BUTTON :
          break;
        case OK_BUTTON :
          if ( XmStringGetLtoR 
	       ( cbs->value, XmSTRING_DEFAULT_CHARSET, &filename ) ) {
            if ( ! * filename ) {
              Popup_Info ( "     No file selected!         " );
              XtFree ( filename );
              return;
            }
            ll = strlen ( filename );
            if ( ll < 5 ) {
              DisplayCurrWinText ( "\n  \"" );
              DisplayCurrWinText ( filename );
              DisplayCurrWinText ( "\" does not end in \".bin\"\n" );
              XtFree ( filename );
              Popup_Info ( "       Bad filename!         " );
	    }
            else if ( ( filename [ ll - 1 ] != 'n' ) ||
                      ( filename [ ll - 2 ] != 'i' ) ||
                      ( filename [ ll - 3 ] != 'b' ) ||
                      ( filename [ ll - 4 ] != '.' )    ) {
              DisplayCurrWinText ( "\n  \"" );
              DisplayCurrWinText ( filename );
              DisplayCurrWinText ( "\" does not end in \".bin\"\n" );
              XtFree ( filename );
              Popup_Info ( "       Bad filename!         " );
	    }
            else {
              strcpy ( name_save_fil, filename );
              XtFree ( filename );
              save_fil = fopen ( name_save_fil, "w" );
              if ( save_fil == NULL ) {
                DisplayCurrWinText ( "\n  Can't write \"" );
                DisplayCurrWinText ( filename );
                DisplayCurrWinText ( "\"\n" );
                Popup_Info ( "   Can't write to file!       " );
	      }
              else {
                DisplayCurrWinText ( "\n  Wrote \"" );
                DisplayCurrWinText ( name_save_fil );
                DisplayCurrWinText ( "\"\n" );
	        save_tool;
	      }
	    }
            break;
          }
          break;
      }
      break;
 
    case file_sel_flag_load_src : 

      switch ( but_num ) {
        case CANCEL_BUTTON :
          break;
        case OK_BUTTON :
          if ( XmStringGetLtoR 
	       ( cbs->value, XmSTRING_DEFAULT_CHARSET, &filename ) ) {
            if ( ! * filename ) {
              Popup_Info ( "     No file selected!         " );
              XtFree ( filename );
              return;
            }
            ll = strlen ( filename );
            if ( ll < 5 ) {
              DisplayCurrWinText ( "\n  \"" );
              DisplayCurrWinText ( filename );
              DisplayCurrWinText ( "\" does not end in \".src\"\n" );
              XtFree ( filename );
              Popup_Info ( "       Bad filename!         " );
	    }
            else if ( ( filename [ ll - 1 ] != 'c' ) ||
                      ( filename [ ll - 2 ] != 'r' ) ||
                      ( filename [ ll - 3 ] != 's' ) ||
                      ( filename [ ll - 4 ] != '.' )    ) {
              DisplayCurrWinText ( "\n  \"" );
              DisplayCurrWinText ( filename );
              DisplayCurrWinText ( "\" does not end in \".src\"\n" );
              XtFree ( filename );
              Popup_Info ( "       Bad filename!         " );
	    }
            else {
              FILE * fileptr = fopen ( filename, "r" );
              if ( fileptr == NULL ) {
                DisplayCurrWinText ( "\n  Can't read \"" );
                DisplayCurrWinText ( filename );
                DisplayCurrWinText ( "\"\n" );
                Popup_Info ( "    Can't read file!        " );
                XtFree ( filename );
	      }
              else {
                fclose ( fileptr );
                DisplayCurrWinText ( "\n  Read \"" );
                DisplayCurrWinText ( filename );
                DisplayCurrWinText ( "\"\n" );
                strcpy ( name_load_fil, filename );
                lod_prf;  /* prfmch.c.motif */
                XtFree ( filename );
                DisplayMainTopWin ();
                if ( browse_a_theory_is_up ) {
                  BrowseATheory ( 0, 0 );
                  BrowseTheories ( 1, 0 );
                }
                else if ( browse_theories_is_up ) {
                  BrowseTheories ( 0, 0 );
                  BrowseTheories ( 1, 0 );
                }
	      }
	    }
            break;
          }
          break;

      }
      break;

  }
}

#endif


#ifndef BTOOLKIT_FLAG

void
BuildAndPrintProof1 ()
{
  string_box_flag = string_box_prf_to_file;
  str_buf [ 0 ] = '\0';
  write_nam_the ( curr_thy );
  strcat ( str_buf, "." );
  write_nat ( curr_rule );
  StringBox ( " File for proofs:           ", str_buf );
}

void
BuildAndPrintProof2 ()  /* now we have filename in name_prf_fil */
{
  int file_exists = 0;
  struct stat stat_buf;
  if ( stat ( name_prf_fil, &stat_buf ) == 0 ) file_exists = 1;
  CreProofTreeDialog ( 0 );
/***
print_live_nodes ( "BuildAndPrintProof2 pre ReconstructProofAndPrint" );
***/
  DisplayARuleMenu ( 0, 0 );
  Popup_Info ( "  Building proof  " );
  ReconstructProofAndPrint ( val_rul_the ( curr_thy, curr_rule ), 0, 0, 0, 0 );
  strcpy ( str_buf, "\n  Proof of " );
  write_nam_the ( curr_thy );
  strcat ( str_buf, "." );
  write_nat ( curr_rule );
  if ( file_exists ) 
    strcat ( str_buf, " appended to " );
  else
    strcat ( str_buf, " written to " );
  write_prf_name_fil;
  strcat ( str_buf, "\n" );
  DisplayCurrWinText ( str_buf );
  DisplayARuleMenu ( 1, 0 );
/***
print_live_nodes ( "BuildAndPrintProof2 post ReconstructProofAndPrint" );
***/
  RestoreBottomForm ( bmotif_bottom_form_proof_length );
}

#endif /* BTOOLKIT_FLAG */

XtCallbackProc
SelThy_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{

#ifdef BTOOLKIT_FLAG

  int but_num =  * ( int * ) client_data + first_btl_thy_to_display;
  int * first_address;

#else

  int but_num =  * ( int * ) client_data;

#endif

  int first;
  int i;

#ifdef BTOOLKIT_FLAG

  XtVaGetValues ( widget,
      XmNuserData,    & first_address,
      NULL );
  first = ( 50 * ( * first_address ) ) + 1;
  Store_thy_first_rule (  but_num, first );

#endif

/***
  printf ( "first %d\n", first );
***/

  util_str_i = 1;

  curr_thy = but_num;
  PopdownCurrMenu ();
  DisplayATheoryMenu ( 1, 0 );
  lst_short_rul_the ( curr_thy );  /* themch.c.motif */
  DisplayATheoryTopWin ( curr_thy );
}

XtCallbackProc
SelRul_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  int but_num =  * ( int * ) client_data;
  int i,r;

  curr_rule =  but_num;
  visible_thy_menu_rule_num = but_num;
  PopdownCurrMenu ();
  DisplayARuleMenu ( 1, 0 );
  DisplayARuleTopWin ( curr_rule );
 }

XtCallbackProc
TLMenu_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;
  int but_num =  * ( int * ) client_data;
  int i;

  switch ( but_num ) {

#ifndef BTOOLKIT_FLAG

  case save_binary_but:
    {
       Widget dialog;
       XmString xstr;
       dialog =
            XmCreateFileSelectionDialog ( top_level, "SelDialog", NULL, 0 );
       XtUnmanageChild ( XmFileSelectionBoxGetChild (
            dialog, XmDIALOG_HELP_BUTTON ) );
       XtAddCallback ( dialog, XmNmapCallback,
           ( XtCallbackProc ) PositionWidgetRelCurrMenu_CB,
           NULL );
       XtAddCallback ( dialog, XmNcancelCallback, 
           ( XtCallbackProc ) FileSel_CB,
           & c_arr [ CANCEL_BUTTON ] );
       XtAddCallback ( dialog, XmNokCallback, 
           ( XtCallbackProc ) FileSel_CB,
           & c_arr [ OK_BUTTON ] );
       XtVaSetValues ( dialog, 
           XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
           XmNdefaultPosition,        False,
           NULL );
       file_sel_flag = file_sel_flag_save_bin;
       xstr = XmStringCreateLtoR ( "*.bin", charset );
       XmFileSelectionDoSearch ( dialog, xstr );
       XmStringFree ( xstr );
       /*
       XtRealizeWidget ( dialog );
       PositionWidgetRelCurrMenu ( & dialog );
       */
       XtManageChild ( dialog );
    }
    break;

  case load_binary_but:
    {
       Widget dialog;
       XmString xstr;
       dialog =
            XmCreateFileSelectionDialog ( top_level, "SelDialog", NULL, 0 );
       XtUnmanageChild ( XmFileSelectionBoxGetChild (
            dialog, XmDIALOG_HELP_BUTTON ) );
       XtAddCallback ( dialog, XmNmapCallback,
           ( XtCallbackProc ) PositionWidgetRelCurrMenu_CB,
           NULL );
       XtAddCallback ( dialog, XmNcancelCallback, 
           ( XtCallbackProc ) FileSel_CB,
           & c_arr [ CANCEL_BUTTON ] );
       XtAddCallback ( dialog, XmNokCallback, 
           ( XtCallbackProc ) FileSel_CB,
           & c_arr [ OK_BUTTON ] );
       XtVaSetValues ( dialog, 
           XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
           XmNdefaultPosition,        False,
           NULL );
       file_sel_flag = file_sel_flag_load_bin;
       xstr = XmStringCreateLtoR ( "*.bin", charset );
       XmFileSelectionDoSearch ( dialog, xstr );
       XmStringFree ( xstr );
       /*
       XtRealizeWidget ( dialog );
       PositionWidgetRelCurrMenu ( & dialog );
       */
       XtManageChild ( dialog );
    }
    break;

  case load_source_but:
    {
       Widget dialog;
       XmString xstr;
       dialog =
            XmCreateFileSelectionDialog ( top_level, "SelDialog", NULL, 0 );
       XtUnmanageChild ( XmFileSelectionBoxGetChild (
            dialog, XmDIALOG_HELP_BUTTON ) );
       XtAddCallback ( dialog, XmNmapCallback,
           ( XtCallbackProc ) PositionWidgetRelCurrMenu_CB,
           NULL );
       XtAddCallback ( dialog, XmNcancelCallback, 
           ( XtCallbackProc ) FileSel_CB,
           & c_arr [ 0 ] );
       XtAddCallback ( dialog, XmNokCallback, 
           ( XtCallbackProc ) FileSel_CB,
           & c_arr [ 1 ] );
       file_sel_flag = file_sel_flag_load_src;
       XtVaSetValues ( dialog, 
           XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
           XmNdefaultPosition,        False,
           NULL );
       xstr = XmStringCreateLtoR ( "*.src", charset );
       XmFileSelectionDoSearch ( dialog, xstr );
       XmStringFree ( xstr );
       /*
       XtRealizeWidget ( dialog );
       PositionWidgetRelCurrMenu ( & dialog );
       */
       XtManageChild ( dialog );
    }
    break;

  case clear_but:
    if( val_rec_sys == FALSE ) {
      query_box_flag = query_box_flag_clear;
      QueryBox ( " Clear all theories? " );
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case statistics_but :
    max_toolfunc();
    break;

  case recompact_but:
    sta_seq_hdr ();
    string_box_flag = string_box_recompact;
    StringBox ( "Max Size of Free space after each sequence?", ""  );
    break;

  case  list_symbols_but:
    redirect_trm ( "b.sym" );
    lst_all_sym;
    reset_trm 
    Popup_Info ( "     Symbols written to file  \"b.sym\"          " );
    break;

  case  reload_source_main_but:
    if( (val_rec_sys==FALSE) && (val_loaded_sys==TRUE) ) {
      query_box_flag = query_box_flag_rld_src_main;
      QueryBox ( " Reload Source? " );
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case reload_source_theory_but:
    if( (val_rec_sys==FALSE) && (val_loaded_sys==TRUE) ) {
      query_box_flag = query_box_flag_rld_src_a_theory;
      QueryBox ( " Reload Source? " );
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case reload_source_rule_but:
    if ( ( val_rec_sys == FALSE ) && ( val_loaded_sys == TRUE ) ) {
      query_box_flag = query_box_flag_rld_src_a_rule;
      QueryBox ( " Reload Source? " );
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case new_theory_but : /* "New Theory" from Main */
    string_box_flag = string_box_new_thy;
    StringBox ( " Theory name:                ", "" );
    break;

#endif

  case quit_but:
    query_box_flag = query_box_flag_quit;
#ifdef BTOOLKIT_FLAG
    {  int t,n,tot,totp;
       tot = 0;
       totp = 0;
       for ( t = first_btl_thy_to_display ; t <= last_btl_thy_to_display ; t++ ) {
         n = nbr_rul_the ( t );
         for ( i = 1 ; i <= n ; i++ ) {
           if ( pvd_rul ( val_rul_the ( t, i ) ) == now_rul ) totp++;
           tot++;
         }
       }
       PopdownCurrMenu ();
       if ( cbs->reason == XmCR_PROTOCOLS ) WM_KillCurrMenu ();
       XmFontListFree ( fontlist );
       if ( ( last_goal_displayed_frm != -999 ) && ( last_goal_displayed_frm ) ) {
#ifdef BTOOL_PROVER_NEW
/***/
printf ( "\n\n________________ motif.c: kil ( last_goal_displayed_frm ) ___________________\n\n" );
sleep ( 5 );
/***/
#endif /* BTOOL_PROVER_NEW */
         kil ( last_goal_displayed_frm );
         last_goal_displayed_frm = 0;
       }
       exit_btool_prover ();
    }
#else
    PopdownCurrMenu ();
    if ( cbs->reason == XmCR_PROTOCOLS ) {
      XmFontListFree ( fontlist );
      exit___ ( 0 );
    }
    else {
      QueryBox ( " Quit BTool? " );
    }
#endif
    break;

  case main_menu_theory_but:
    PopdownCurrMenu ();
    if ( cbs->reason == XmCR_PROTOCOLS ) WM_KillCurrMenu ();
    DisplayMainMenu ( 1, 0 );
    DisplayMainTopWin ();
    break;

#ifndef BTOOLKIT_FLAG

  case new_rule_but:
    if ( curr_thy != 1 ) {
      string_box_flag = string_box_new_rule;
      LargeStringBox ( " New Rule:                                                                                                       ", "" );
    }
    else {
      Popup_Info ( "    Can't add new rule to this theory!   " );
    }
    break;

  case list_rules_on_file_but:
    redirect_trm("b.src" ); 
    lst_rul_the ( curr_thy );
    reset_trm;
    Popup_Info ( "     Rules in file b.src         " );
    break;

  case exec_direct_input_but:
    if ( val_rec_sys == FALSE ) {
      string_box_flag = string_box_exec_direct;
      StringBox ( " Rule to Exec:                                        ", "" );
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case exec_file_input_but:
    if ( val_rec_sys == FALSE ) {
      string_box_flag = string_box_exec_file;
      StringBox ( " File to Exec:              ", "" );
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case remove_last_rule_but:
    {
      int r;
      if ( val_rec_sys == FALSE ) {
        if( len ( rul_the ( curr_thy ) ) != 0 ) {
          r = lst ( rul_the ( curr_thy ) );
          if ( curr_thy == 1 || typ_rul ( r ) != nrm_rul ) {
            Popup_Info ( "    Can't remove a lemma/auto-rule!   " );
          }
          else {
            write_ver_rul_dave ( r );
            query_box_flag = query_box_flag_rem_last_rule;
            QueryBox ( " Remove Last Rule? " );
          }
	}
        else {
          DisplayCurrWinText ( "      No rule to remove\n" );
        }
      }
      else {
        Popup_Info ( "      Impossible now!    " );
      }
    }
    break;

  case shell_but:
   system ( "xterm&" );
   break;

  case remove_theory_but:
    {
      register int i,r,b ;
      if( val_rec_sys == FALSE ) {
        xst(rul_the ( curr_thy ),i,r,typ_rul(r)!=nrm_rul,b=TRUE,b=FALSE);
          if ( b == TRUE  || curr_thy == 1 ) {
            Popup_Info ( "     Can't remove theory!         " );
            strcpy ( str_buf, "\n  " );
            write_nam_the ( curr_thy );
            strcat ( str_buf, " contains lemmas/auto-rules\n" );
            DisplayCurrWinText ( str_buf );
          }
          else {
            query_box_flag = query_box_flag_rem_thy;
            strcpy ( str_buf, "          Remove " );
            write_nam_the ( curr_thy );
            strcat ( str_buf, "?      " );
            QueryBox ( str_buf );
          }
      }
      else {
        Popup_Info ( "      Impossible now!    " );
      }
    }
    break;

/*
  case proof_on_file_on_off_but:
    if( val_print_ext_prf_the==FALSE ) {
      string_box_flag = string_box_prf_to_file;
      StringBox ( " File for proofs:           ", "" );
    }
    else {
      strcpy ( str_buf, "\n  Proofs now available on file " );
      write_prf_name_fil;
      strcat ( str_buf, "\n" );
      DisplayCurrWinText ( str_buf );
      query_box_flag = query_box_prf_to_screen;
      QueryBox ( " Proofs back to screen? " );
    }
    break;
*/

  case change_normal_tac_theory_but:
    if( val_rec_sys==FALSE ) {
      str_buf [ 0 ] = '\0';
      write_frm_res(tac_the ( curr_thy ),0);
      string_box_flag = string_box_nml_tac_a_theory;
      StringBox ( " New Normal tactic:                                       ", str_buf );
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case change_fwd_tac_theory_but:
    if( val_rec_sys==FALSE ) {
      str_buf [ 0 ] = '\0';
      if( has_fwd_tac_the ( curr_thy )==TRUE ) {
        write_frm_res( fwd_tac_the ( curr_thy ),0 );
      }
      string_box_flag = string_box_fwd_tac_a_theory;
      StringBox ( " New Forward tactic:                                       ", str_buf );
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case change_normal_tac_rule_but:
    CreProofTreeDialog ( 0 );
    if( val_rec_sys==FALSE ) {
      str_buf [ 0 ] = '\0';
      write_frm_res(tac_the ( curr_thy ),0);
      string_box_flag = string_box_nml_tac_a_rule;
      StringBox ( " New Normal tactic:                                       " , str_buf );
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case change_fwd_tac_rule_but:
    CreProofTreeDialog ( 0 );
    if( val_rec_sys==FALSE ) {
      str_buf [ 0 ] = '\0';
      if( has_fwd_tac_the ( curr_thy )==TRUE ) {
        write_frm_res(fwd_tac_the ( curr_thy ),0);
      }
      string_box_flag = string_box_fwd_tac_a_rule;
      StringBox ( " New Forward tactic:                                       ", str_buf );
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case prove_lemmas_but:
        if( val_rec_sys==FALSE ) {
	  /*
          itr_lem_the_prf( curr_thy );
	  */
          DAVE_prove_lemmas ( curr_thy );
        }
        else {
          Popup_Info ( "      Impossible now!    " );
        }
    break;

  case change_normal_quota_rule_but:
    str_buf [ 0 ] = '\0';
    write_nat(max_ctr_prf);
    string_box_flag = string_box_nml_quota;
    StringBox ( " New Normal proof quota: ", str_buf );
    break;

  case change_fwd_quota_rule_but:
    str_buf [ 0 ] = '\0';
    write_nat(max_fwd_ctr_prf);
    string_box_flag = string_box_fwd_quota;
    StringBox ( " New Forward proof quota: ", str_buf );
    break;

  case rule_on_off_but:
    {
      int rr = val_rul_the ( curr_thy, curr_rule );
      CreProofTreeDialog ( 0 );
      if ( curr_thy != 1 ) {
        strcpy ( str_buf, "\n  " );
        write_nam_the ( curr_thy );
        strcat ( str_buf, "." );
        write_nat ( curr_rule );
        if( val_sts_rul( rr )==on_rul ) {
          mod_sts_rul ( rr, off_rul );
          strcat ( str_buf, " is now off\n" );
          Popup_Info ( "       Rule is now off       " );
        }
        else {
          mod_sts_rul ( rr, on_rul );
          strcat ( str_buf, " is now on\n" );
          Popup_Info ( "       Rule is now on       " );
        }
        DisplayCurrWinText ( str_buf );
        if ( curr_thy == browse_a_theory_is_up ) {
          int browse_a_theory_is_up_save;
          browse_a_theory_is_up_save = browse_a_theory_is_up;
          BrowseATheory ( 0, 0 );
          browse_a_theory_is_up = browse_a_theory_is_up_save;
          BrowseATheory ( browse_a_theory_is_up, 0 );
        }
      }
      else {
        Popup_Info ( "    Can't change an auto-rule    " );
      }
    }
    break;

  case change_rule_but:
    if ( val_rec_sys == FALSE ) {
      if ( ( typ_rul( val_rul_the ( curr_thy, curr_rule ) ) != lem_rul ) &&
             curr_thy != 1                                                  ) {
        string_box_flag = string_box_change_rule;
        str_buf [ 0 ] = '\0';
        write_ver_rul_dave ( val_rul_the ( curr_thy , curr_rule ) );
        LargeStringBox ( " New rule:                                                                                                        ", str_buf );
      }
      else {
        Popup_Info ( "  Can't modify a lemma/auto-rule   " );
      }
    }
    else {
        Popup_Info ( "      Impossible now!    " );
    }
    break;

  case move_rule_but:
    if ( val_rec_sys == FALSE ) {
      if ( curr_thy != 1 ) {
        string_box_flag = string_box_move_rule;
        StringBox ( " New position:   ", "" );
      }
      else {
        Popup_Info ( "    Can't move an auto-rule    " );
      }
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case remove_rule_but:
    if ( val_rec_sys == FALSE ) {
      if ( curr_thy == 1                                              || 
           typ_rul ( val_rul_the ( curr_thy , curr_rule ) )!= nrm_rul    ) {
        Popup_Info ( "    Can't remove a lemma/auto-rule!    " );
      }
      else {
        query_box_flag = query_box_flag_rem_rule;
        QueryBox ( " Remove rule? " );
      }
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

#endif

  case prove_rule_but:
    if ( val_rec_sys==FALSE ) {
      if ( pvd_rul ( val_rul_the ( curr_thy, curr_rule ) ) == now_rul ) {
	Popup_Info ( "      Already proved!!           " );
      }
      else {
        void CreProofTreeDialog ();
        void ClearTopWin ();
        Dimension top_level_w;
        ClearTopWin ();
        XtVaGetValues ( top_level, XmNwidth, &top_level_w, NULL );
        PopdownCurrMenu ();
        str_buf [ 0 ] = '\0';
        write_nam_the ( curr_thy );
        strcat ( str_buf, "." );
        write_nat ( curr_rule );
        DisplayCurrWinText ( "\n  Proving " );
        if ( typ_rul (  val_rul_the ( curr_thy , curr_rule ) ) == lem_rul ) {
          DisplayCurrWinText ( "lemma " );
	}
        DisplayCurrWinText ( str_buf );
        
        CreProofTreeDialog ( 1 );
        do_prf ( curr_thy, curr_rule, TRUE );
      }
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

  case reconstruct_proof_tree_but:
    if ( val_rec_sys == FALSE ) {
      if ( pvd_rul ( val_rul_the ( curr_thy, curr_rule ) ) != now_rul ) {
        Popup_Info ( "      No proof to replay!    " );
      }
      else {
        void RestoreBottomForm ();
/***
print_live_nodes ( "TLMenu_CB 1 pre ReconstructProofAndPrint" );
***/
        DisplayARuleMenu ( 0, 0 );
        Popup_Info ( "  Reconstructing proof tree " );
        ReconstructProofAndPrint ( val_rul_the ( curr_thy, curr_rule ), 1, 0, 0, 0 );
        DisplayARuleMenu ( 1, 0 );
        RestoreBottomForm ( bmotif_bottom_form_proof_tree_length );
/***
print_live_nodes ( "TLMenu_CB 1 post ReconstructProofAndPrint" );
***/
      }
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
    break;

#ifndef BTOOLKIT_FLAG

  case build_and_print_proof_but:
    if ( val_rec_sys == FALSE ) {
      if ( pvd_rul ( val_rul_the ( curr_thy, curr_rule ) ) != now_rul ) {
        Popup_Info ( "      No proof to replay!    " );
      }
      else {
        BuildAndPrintProof1 ();
      }
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }   
    break;

#endif /* BTOOLKIT_FLAG */

  case build_and_dsply_proof_but:
    if ( val_rec_sys == FALSE ) {
      if ( pvd_rul ( val_rul_the ( curr_thy, curr_rule ) ) != now_rul ) {
        Popup_Info ( "      No proof to replay!    " );
      }
      else {
        CreProofTreeDialog ( 0 );
/***
print_live_nodes ( "TLMenu_CB 2 pre ReconstructProofAndPrint" );
***/
        DisplayARuleMenu ( 0, 0 );
        Popup_Info ( "  Building proof  " );
        ReconstructProofAndPrint ( val_rul_the ( curr_thy, curr_rule ), 0, 0, 0, 0 );
        DisplayARuleMenu ( 1, 0 );
        RestoreBottomForm ( bmotif_bottom_form_proof_tree_length );
/***
print_live_nodes ( "TLMenu_CB 2 post ReconstructProofAndPrint" );
***/
      }
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }   
    break;

  case remove_proof_but:
    if ( val_rec_sys == FALSE ) {
      if ( pvd_rul ( val_rul_the ( curr_thy, curr_rule ) ) != now_rul ) {
        Popup_Info ( "      No proof to remove!    " );
      }
      else {
        query_box_flag = query_box_rem_proof;
        QueryBox ( " Remove proof? " );
      }
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }   
    break;

  case theory_menu_but:
    CreProofTreeDialog ( 0 );
    PopdownCurrMenu ();
    DisplayATheoryMenu ( 1, 0 );
    DisplayATheoryTopWin ( curr_thy );
    break;

  case main_menu_rule_but:
    CreProofTreeDialog ( 0 );
    PopdownCurrMenu ();
    DisplayMainMenu ( 1, 0 );
    DisplayMainTopWin ();
    break;

  case browse_theories_but:
    BrowseTheories ( 1, 0 );
    break;

#ifdef BTOOLKIT_FLAG

  case  reload_PMD_but:
    {
      int st, lenpob;
      val_curMRIState( &st, curr_obj );
      length_pob ( &lenpob, st );
      sprintf ( fifo_write_buf, "%s.%d:0", GetName ( curr_obj ), lenpob - 1 ); 
      Cre_fifo_write_buf_cmd_0 ( BT_BTL_RLD_REQ );
/***
printf ( "`%s'\n", fifo_write_buf );
***/
      InvokeB ( without_XTerm, 1 );
    }
    break;

  case  edit_cur_PMD_but:
    {
      void EditPMDFile ();
      EditPMDFile ( 0 );
    }
    break;

  case  edit_glob_PMD_but:
    {
      void EditPMDFile ();
      EditPMDFile ( 1 );
    }
    break;

#endif /* BTOOLKIT_FLAG */

  } /* switch ( but_num ) */
}

#ifdef BTOOLKIT_FLAG

void
RedisplayAfter_reload_PMD_but ()
{
  switch ( curr_menu ) {
  case a_theory_menu:
    DisplayATheoryTopWin ( 0 );
    DisplayATheoryTopWin ( curr_thy );
    break;
  case a_rule_menu:
    DisplayARuleTopWin ( 0 );
    DisplayARuleTopWin ( curr_rule );
    break;
  }
}

void
EditPMDFile ( flag )
{
  /***
  flag = 0 => current PMD
  flag = 1 => global PMD
  ***/

  Retrieve_String ( pmd_editor_str_num, fifo_write_buf );

  if ( ! flag ) { /* current pmd */
    int st, level, lenpob; 
    val_curMRIState( &st, curr_obj );
    length_pob ( &lenpob, st );
    sprintf ( primary_string, " PMD/%s.%d.pmd",
                                            GetName ( curr_obj ), lenpob - 1 ); 
    strcat ( fifo_write_buf, primary_string );
    strcat ( fifo_write_buf, " &" );
    execute ( fifo_write_buf );
    sprintf ( buf, "Opened %s.%d.pmd for editing",
                                              GetName ( curr_obj ), lenpob - 1);
    Popup_Info ( buf );
  }
  else { /* global pmd */
    int i = 0;
    int all_sp = 1;
    Retrieve_String ( provers_str_num, primary_string );
    while ( primary_string [ i ] != '\0' && all_sp ) {
      if ( primary_string [ i ] != ' ' ) all_sp = 0;
      i++;
    }
    if ( all_sp ) {
      Popup_Minor_Err ( NULL, "Global PROOFMETHOD string not set\n  (Set in Top Bar Options - Provers)" );
    }
    else {
      strcat ( fifo_write_buf, " " );
      strcat ( fifo_write_buf, primary_string );
      strcat ( fifo_write_buf, " &" );
      execute ( fifo_write_buf );
      sprintf ( buf, "Opened %s for editing", primary_string );
      Popup_Info ( buf );
    }
  }
}

void
ReturnFromReloadPMD ( flag )

     /***
     flag = 1 => PMD parses
     flag = 0 => parse errors in .BBcom
     ***/

{
  int st, lenpob;

  val_curMRIState( &st, curr_obj );
  length_pob ( &lenpob, st );
  sprintf ( fifo_write_buf, "%s.%d:0", GetName ( curr_obj ), lenpob - 1 ); 

/***
printf ( "flag=%d - rld.src:\n", flag );
system ( "cat TMP/rld.src" );
***/

  if ( ! flag ) {  /* PMD not parse */
    LoadFileIntoBuf ( ".BBcom", buf, 3001 );
    sprintf ( str_buf, "%s.%d.pmd does not parse:\n\n%s",
                                          GetName ( curr_obj ), lenpob - 1, buf );
    Popup_Minor_Err ( top_level, str_buf );
    return;
  }

  if ( FileParses ( "TMP/rld.src" ) ) {
    int t;

/***
printf ( "B: btl_users_thy    =%d\n", btl_users_thy );
printf ( "B: fwd_btl_users_thy=%d\n", fwd_btl_users_thy );
printf ( "B: users_thy    =%d\n", users_thy );
printf ( "B: fwd_users_thy=%d\n", fwd_users_thy );
printf ( "B: browse_theories_is_up=%d\n", browse_theories_is_up );
printf ( "B: browse_a_theory_is_up=%d\n", browse_a_theory_is_up );
***/

    if ( users_thy ) {
      for ( t = users_thy ; t < btl_users_thy ; t++ ) {
        remove_all_rules_thy ( t );
/***
strcpy ( str_buf, "  -->> removed all rules in " );
write_nam_the ( t );
printf ( "(%d) %s\n", t, str_buf );
***/
      }
    }
/*
    if ( users_thy )     remove_all_rules_thy  ( users_thy );
    if ( fwd_users_thy ) remove_all_rules_thy  ( fwd_users_thy );
*/

/***
printf ( "\n----------------------- rld.src ------------------\n" );
system ( "cat TMP/rld.src" );
printf ( "\n--------------------------------------------------\n\n" );
***/

    sprintf ( name_load_fil, "%s/TMP/rld.src", cur_dir );
    lod_prf;  /* prfmch.c.motif */

    if ( browse_theories_is_up ) {
      BrowseTheories ( 0, 0 );
      BrowseTheories ( 1, 0 );
    }
    else if ( browse_a_theory_is_up ) {
      if ( ( browse_a_theory_is_up >= users_thy )    ||
	   ( browse_a_theory_is_up < fwd_users_thy )    ) {
        int browse_a_theory_is_up_save = browse_a_theory_is_up;
        BrowseATheory ( 0, 0 );
        BrowseATheory ( browse_a_theory_is_up_save, 0 );
      }
    }

    sprintf ( str_buf, "%s.%d.pmd reloaded", GetName ( curr_obj ), lenpob - 1 );
    Popup_Info ( str_buf );
    RedisplayAfter_reload_PMD_but ();
  }
  else { /* ! FileParses ( "TMP/rld.src" ) */
    sprintf ( str_buf, "Problem processing %s.%d.pmd",
                                          GetName ( curr_obj ), lenpob - 1, buf );
    Popup_Minor_Err ( top_level, str_buf );
  }
}

#endif /* BTOOLKIT_FLAG */

void
DisplayMainMenu ( flag, WM_flag )
int flag;
int WM_flag;
{
  static Widget dialog_form, B_logo,
                Label, menu_scroll, menu_rc;

  static Atom  WM_DELETE_WINDOW;

  Widget but;

  XmString xstr;
  static int first_time = 1;

  static Position last_menu_x, last_menu_y;

/***
printf ( "DisplayMainMenu (flag=%d WM_flag=%d)\n", flag, WM_flag );
***/

  if ( WM_flag ) {
      XtDestroyWidget ( display_main_menu_dialog );
      first_time = 1;
      return;
  }

  if ( ! flag ) {

    XtVaGetValues ( display_main_menu_dialog, 
        XmNx,       & last_menu_x,
        XmNy,       & last_menu_y,
        NULL );

    if (  menu_position_changed_x ) {
      global_menu_x = last_menu_x - wm_width;
    }

    if (  menu_position_changed_y ) {
      global_menu_y = last_menu_y - wm_height;
    }

    XtPopdown ( display_main_menu_dialog );
    XmUpdateDisplay ( top_level );
    return;

  }

  if ( first_time ) {

    first_time = 0;

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    display_main_menu_dialog =
       XmCreateDialogShell ( top_frame_form, "SelDialog", NULL, 0 );

    XmAddWMProtocolCallback ( display_main_menu_dialog, WM_DELETE_WINDOW,
        ( XtCallbackProc ) TLMenu_CB,
        ( XtPointer ) & c_arr [ quit_but ] );

    dialog_form = XtVaCreateWidget ( "SelDialog",
        xmFormWidgetClass,         display_main_menu_dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        False,  
        NULL );

    B_logo =  XtVaCreateWidget ( "SelDialog",
        xmLabelWidgetClass,         dialog_form,
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

    xstr = XmStringCreate ( "Main Menu", charset );

    Label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNrightAttachment,        XmATTACH_FORM,
#ifndef BTOOLKIT_FLAG
        XmNleftOffset,             1,
        XmNrightOffset,            3,
#else
/*
        XmNleftOffset,             33,
        XmNrightOffset,            43,
*/
        XmNleftOffset,             53,
        XmNrightOffset,            63,
#endif
        XmNlabelString,            xstr,
        XmNmarginWidth,            10,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

    menu_scroll = XtVaCreateWidget ( "SelDialog",
        xmScrolledWindowWidgetClass,    dialog_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   50,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 5,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  5,
        XmNbottomAttachment,            XmATTACH_FORM,
        XmNbottomOffset,                10,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
#ifndef BTOOLKIT_FLAG
        XmNheight,                      310,
#else
        XmNheight,                      /* 100, */ 140,
#endif
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNspacing,                     0,
        NULL );

    menu_rc = XtVaCreateWidget ( "Canvas", 
        xmRowColumnWidgetClass,         menu_scroll,
        XmNorientation,                 XmVERTICAL,
        XmNmarginWidth,                 5,
        XmNmarginHeight,                5,
        XmNspacing,                     5,
        XmNisHomogeneous,               False,
        NULL );

#ifndef BTOOLKIT_FLAG

    but = CreHighlightedButton ( menu_rc, "New Theory", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ new_theory_but ] );

    but = CreHighlightedButton ( menu_rc, "Load Source", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ load_source_but ] );

    but = CreHighlightedButton ( menu_rc, "Reload Source", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ reload_source_main_but ] );

    but = CreHighlightedButton ( menu_rc, "Load Binary", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ load_binary_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Save Binary", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ save_binary_but ] );

    but = CreHighlightedButton ( menu_rc, "Clear Theories", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ clear_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Statistics", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ statistics_but ] );

    but = CreHighlightedButton ( menu_rc, "Recompact", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ recompact_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "List Symbols", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ list_symbols_but ] );

    but = CreHighlightedButton ( menu_rc, "Shell", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ shell_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

#endif

#ifdef BTOOLKIT_FLAG

    main_browse_widget_but =
         CreHighlightedButton ( menu_rc, "Browse Library/Edit BTool Theory", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ browse_theories_but ] );

    but = CreHighlightedButton ( menu_rc, "Edit Current PROOFMETHOD", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ edit_cur_PMD_but ] );

    but = CreHighlightedButton ( menu_rc, "Edit Global PROOFMETHOD", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ edit_glob_PMD_but ] );

    but = CreHighlightedButton ( menu_rc, "Reload Current PROOFMETHOD", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ reload_PMD_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Exit BToolProver", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ quit_but ] );
#else
    but = CreHighlightedButton ( menu_rc, "Quit BTool", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ quit_but ] );
#endif

    XtAddCallback ( display_main_menu_dialog, XmNpopupCallback,
        ( XtCallbackProc ) InitWidgetRelMainWin_CB,
        NULL );

    XtManageChild ( B_logo );
    XtManageChild ( Label );
    XtManageChild ( menu_scroll );
    XtManageChild ( menu_rc );
    XtManageChild ( dialog_form );

  }

  visible_thy_menu_rule_num = 1;

  curr_dialog_menu = dialog_form;
  curr_menu = main_menu;

#ifdef BTOOLKIT_FLAG

  if ( browse_theories_is_up || browse_a_theory_is_up ) {
    XtVaSetValues ( main_browse_widget_but, XmNsensitive, False, NULL );
  }
  else {
    XtVaSetValues ( main_browse_widget_but, XmNsensitive, True, NULL );
  }
  XmUpdateDisplay ( main_browse_widget_but );

#endif

                /*** DisplayMainMenu ***/
  RestoreBottomForm ( bmotif_bottom_form_main_length );
#ifdef BTOOLKIT_FLAG
  UnHideTopWin ();
#endif

  XtPopup ( display_main_menu_dialog, XtGrabNone );
  XmUpdateDisplay ( display_main_menu_dialog );
  XmUpdateDisplay ( top_level );

/***
print_live_nodes ( "MainMenu" );
***/
}

#ifdef BTOOLKIT_FLAG

void
DisplayBtlUnproved_CB ( widget, but_num )
Widget widget;
int but_num;
{
/***
printf ( "prev display_unproved_btl_flag: %d\n", display_unproved_btl_flag );
***/
  if ( display_unproved_btl_flag != but_num ) {
    display_unproved_btl_flag = but_num;
    DisplayATheoryTopWin ( 0 );
    DisplayATheoryTopWin ( curr_thy );   
  }
/***
printf ( "display_unproved_btl_flag: %d\n", display_unproved_btl_flag );
***/
}

#endif

void
DisplayATheoryMenu ( flag, WM_flag )
int flag;
int WM_flag;
{
  static Widget dialog_form, B_logo, Label,
                display_unproved_but, menu_scroll, menu_rc;

  static Atom  WM_DELETE_WINDOW;

  Widget but;

  XmString xstr, xstr0, xstr1;

  static int first_time = 1;

  static Position last_menu_x, last_menu_y;

/***
printf ( "DisplayATheoryMenu (flag=%d WM_flag=%d)\n", flag, WM_flag );
***/

  if ( WM_flag ) {
      XtDestroyWidget ( display_a_theory_dialog );
      first_time = 1;
      return;
  }

  if ( ! flag ) {

    XtVaGetValues ( display_a_theory_dialog, 
        XmNx,       & last_menu_x,
        XmNy,       & last_menu_y,
        NULL );

    if (  menu_position_changed_x ) {
      global_menu_x = last_menu_x - wm_width;
    }

    if (  menu_position_changed_y ) {
     global_menu_y = last_menu_y - wm_height;
    }

    XtPopdown ( display_a_theory_dialog );
    XmUpdateDisplay ( top_level );
    return;

  }

  if ( first_time ) {

    first_time = 0;

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    display_a_theory_dialog =
        XmCreateDialogShell ( top_frame_form, "SelDialog", NULL, 0 );

    XmAddWMProtocolCallback ( display_a_theory_dialog, WM_DELETE_WINDOW,
        ( XtCallbackProc ) TLMenu_CB,
              ( XtPointer ) & c_arr [  main_menu_theory_but ] );

    dialog_form = XtVaCreateWidget ( "SelDialog",
        xmFormWidgetClass,         display_a_theory_dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        False,  
        NULL );

    B_logo =  XtVaCreateWidget ( "SelDialog",
        xmLabelWidgetClass,         dialog_form,
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

    xstr = XmStringCreateLtoR ( "Theory Menu", charset );
    Label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNrightAttachment,        XmATTACH_FORM,
#ifndef BTOOLKIT_FLAG
        XmNleftOffset,             12,
        XmNrightOffset,            25,
#else
/*
        XmNleftOffset,             30,
        XmNrightOffset,            40,
*/
        XmNleftOffset,             50,
        XmNrightOffset,            60,
#endif
        XmNlabelString,            xstr,
        XmNmarginWidth,            10,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

    menu_scroll = XtVaCreateWidget ( "SelDialog",
        xmScrolledWindowWidgetClass,    dialog_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   50,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 5,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  5,
        XmNbottomAttachment,            XmATTACH_FORM,
        XmNbottomOffset,                10,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
/*
        XmNwidth,                       5,
*/
#ifndef BTOOLKIT_FLAG
	XmNheight,                      /* 405, */ 380,
#else
        XmNheight,                      /* 120, */ 185,
#endif
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNspacing,                     0,
        NULL );

  menu_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         menu_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNspacing,                     5,
      XmNisHomogeneous,               False,
      NULL );

#ifndef BTOOLKIT_FLAG

    but = CreHighlightedButton ( menu_rc, "New Rule", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ new_rule_but ] );

    but = CreHighlightedButton ( menu_rc, "Reload (Source)", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ reload_source_theory_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Change Normal Tactic", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ change_normal_tac_theory_but ] );

    but = CreHighlightedButton ( menu_rc, "Change Forward Tactic", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ change_fwd_tac_theory_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Exec - Direct Input", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ exec_direct_input_but ] );

    but = CreHighlightedButton ( menu_rc, "Exec - File Input", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ exec_file_input_but ] );

    but = CreHighlightedButton ( menu_rc, "Prove Lemmas", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ prove_lemmas_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Remove Last Rule", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ remove_last_rule_but ] );

    but = CreHighlightedButton ( menu_rc, "Remove Theory", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ remove_theory_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Statistics", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ statistics_but ] );

/*
    but = CreHighlightedButton ( menu_rc, "Proof on File (on/off)", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ proof_on_file_on_off_but ] );
*/

    but = CreHighlightedButton ( menu_rc, "List Rules on File", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ list_rules_on_file_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    theory_browse_widget_but = CreHighlightedButton ( menu_rc, "Browse Theories", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ browse_theories_but ] );

#else

    xstr =  XmStringCreateLtoR ( "", charset );
    xstr0 =  XmStringCreateLtoR ( "Display unproved only", charset );
    xstr1 =  XmStringCreateLtoR ( "Display all", charset );

    display_unproved_but = XmVaCreateSimpleOptionMenu ( menu_rc, "Canvas",
        xstr, 0,
	1, DisplayBtlUnproved_CB,
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

    display_unproved_btl_flag = 1;

    XtManageChild ( display_unproved_but );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    theory_browse_widget_but = CreHighlightedButton ( menu_rc, "Browse Library/Edit BTool Theory", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ browse_theories_but ] );

    but = CreHighlightedButton ( menu_rc, "Edit Current PROOFMETHOD", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ edit_cur_PMD_but ] );

    but = CreHighlightedButton ( menu_rc, "Edit Global PROOFMETHOD", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ edit_glob_PMD_but ] );

    but = CreHighlightedButton ( menu_rc, "Reload Current PROOFMETHOD", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ reload_PMD_but ] );

#endif

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Quit to Main Menu", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ main_menu_theory_but ] );

    XtManageChild ( B_logo );
    XtManageChild ( Label );
    XtManageChild ( menu_scroll );
    XtManageChild ( menu_rc );

    XtAddCallback ( display_a_theory_dialog, XmNpopupCallback,
        ( XtCallbackProc ) RepositionMenu_CB,
        NULL );

  }

  curr_dialog_menu = dialog_form;
  curr_menu = a_theory_menu;

  XtManageChild ( dialog_form );

  if ( browse_theories_is_up || browse_a_theory_is_up ) {
    XtVaSetValues ( theory_browse_widget_but, XmNsensitive, False, NULL );
  }
  else {
    XtVaSetValues ( theory_browse_widget_but, XmNsensitive, True, NULL );
  }
  XmUpdateDisplay ( theory_browse_widget_but );

                    /*** DisplayATheoryMenu ***/
  RemoveBottomForm ();
#ifdef BTOOLKIT_FLAG
  UnHideTopWin ();
#endif

  XtPopup ( display_a_theory_dialog, XtGrabNone );
  XmUpdateDisplay ( display_a_theory_dialog );
  XmUpdateDisplay ( top_level );

/***
print_live_nodes ( "TheoryMenu" );
***/
}



#ifdef BTOOLKIT_FLAG

void
ReasoningDepth_CB ( widget, but_num )
Widget widget;
int but_num;
{
  void SetFwdLibTac ();
  btl_fwd_tac_depth = but_num + feql_val;
  SetFwdLibTac ( curr_thy );
/***
printf ( "ReasoningDepth_CB: btl_fwd_tac_depth=%d\n", btl_fwd_tac_depth );
***/
  DisplayARuleTopWin ( 0 );
  DisplayARuleTopWin ( curr_rule );
}

void
FEQL_CB ( widget, but_num )
Widget widget;
int but_num;
{
  void SetFwdLibTac ();
  btl_fwd_tac_depth = btl_fwd_tac_depth - feql_val;
  if   ( but_num ) feql_val = 3;
  else             feql_val = 0;
  btl_fwd_tac_depth = btl_fwd_tac_depth + feql_val;
  SetFwdLibTac ( curr_thy );
  DisplayARuleTopWin ( 0 );
  DisplayARuleTopWin ( curr_rule );
}

#endif

void
DisplayARuleMenu ( flag, WM_flag )
int flag;
int WM_flag;
{
  static Widget dialog_form, B_logo, Label,
         menu_scroll, menu_rc;

  static Atom  WM_DELETE_WINDOW;

  Widget but;

  static Widget prv_but, remprf_but, prt_prf_tree_but,
                prt_prf_but, dsply_prf_but, reasoning_depth_widget_but,
                feql_widget_but;

  XmString xstr;

  static int first_time = 1;

  static Position last_menu_x, last_menu_y;

  void SetFwdLibTac ();

/***
printf ( "DisplayARuleMenu (flag=%d WM_flag=%d)\n", flag, WM_flag );
***/

  if ( WM_flag ) {
      XtDestroyWidget ( display_a_rule_dialog );
      first_time = 1;
      return;
  }

  if ( ! flag ) {

    XtVaGetValues ( display_a_rule_dialog, 
        XmNx,       & last_menu_x,
        XmNy,       & last_menu_y,
        NULL );

    if (  menu_position_changed_x ) {
      global_menu_x = last_menu_x - wm_width;
    }

    if (  menu_position_changed_y ) {
      global_menu_y = last_menu_y - wm_height;
    }

    XtPopdown ( display_a_rule_dialog );
    XmUpdateDisplay ( top_level );
    return;

  }

  if ( first_time ) {

    first_time = 0;

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    display_a_rule_dialog =
        XmCreateDialogShell ( top_frame_form, "SelDialog", NULL, 0 );

    XmAddWMProtocolCallback ( display_a_rule_dialog, WM_DELETE_WINDOW,
        ( XtCallbackProc ) TLMenu_CB,
              ( XtPointer ) & c_arr [  main_menu_theory_but ] );

    dialog_form = XtVaCreateWidget ( "SelDialog",
        xmFormWidgetClass,         display_a_rule_dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        False,  
        NULL );

    B_logo =  XtVaCreateWidget ( "SelDialog",
        xmLabelWidgetClass,         dialog_form,
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

    xstr = XmStringCreateLtoR ( "Rule Menu", charset );
    Label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNrightAttachment,        XmATTACH_FORM,
#ifndef BTOOLKIT_FLAG
        XmNleftOffset,             30,
        XmNrightOffset,            40,
#else
/*
        XmNleftOffset,             40,
        XmNrightOffset,            50,
*/
        XmNleftOffset,             60,
        XmNrightOffset,            70,
#endif
        XmNlabelString,            xstr,
        XmNmarginWidth,            10,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

    menu_scroll = XtVaCreateWidget ( "SelDialog",
        xmScrolledWindowWidgetClass,    dialog_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   50,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 5,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  5,
        XmNbottomAttachment,            XmATTACH_FORM,
        XmNbottomOffset,                10,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
/*
        XmNwidth,                       5,
*/
#ifndef BTOOLKIT_FLAG
        XmNheight,                      475,
#else
        XmNheight,                      /* 290, */ 345,
#endif
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNspacing,                     0,
        NULL );

  menu_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         menu_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNspacing,                     5,
      XmNisHomogeneous,               False,
      NULL );

    prv_but = CreHighlightedButton ( menu_rc, "Prove Rule", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ prove_rule_but ] );

    prt_prf_tree_but = CreHighlightedButton ( menu_rc, "Reconstruct Proof Tree", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ reconstruct_proof_tree_but ] );

    dsply_prf_but = CreHighlightedButton ( menu_rc, "Build & Display Proof", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ build_and_dsply_proof_but ] );

#ifndef BTOOLKIT_FLAG

    prt_prf_but = CreHighlightedButton ( menu_rc, "Build & Print Proof", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ build_and_print_proof_but ] );

#endif

    remprf_but = CreHighlightedButton ( menu_rc, "Remove Proof", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ remove_proof_but ] );

#ifdef BTOOLKIT_FLAG

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    {
      XmString xstr =  XmStringCreateLtoR ( "", charset );
      XmString xstr0 =  XmStringCreateLtoR ( "Fwd Reasoning Depth 0", charset );
      XmString xstr1 =  XmStringCreateLtoR ( "Fwd Reasoning Depth 1", charset );
      XmString xstr2 =  XmStringCreateLtoR ( "Fwd Reasoning Depth 2", charset );

      reasoning_depth_widget_but =
          XmVaCreateSimpleOptionMenu ( menu_rc, "Canvas",
          xstr, 0,
          2, ReasoningDepth_CB,
          XmVaPUSHBUTTON, xstr0, NULL, NULL, NULL,
          XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
          XmVaPUSHBUTTON, xstr2, NULL, NULL, NULL,
          NULL);

      btl_fwd_tac_depth = 2 + feql_val;
      SetFwdLibTac ( curr_thy );

      XmStringFree ( xstr );
      XmStringFree ( xstr0 );
      XmStringFree ( xstr1 );
      XmStringFree ( xstr2 );

     XtVaSetValues ( reasoning_depth_widget_but,
          XmNshadowThickness,        0,
          /* 
          XmNmarginWidth,            2,
          XmNmarginHeight,           2,
          */
          XmNdefaultButtonShadowThickness,     1,
          XmNhighlightThickness,     1,
          XmNnavigationType,         XmTAB_GROUP,
          NULL);

      XtManageChild ( reasoning_depth_widget_but );


      xstr =  XmStringCreateLtoR ( "", charset );
      xstr0 =  XmStringCreateLtoR ( "FEQL off", charset );
      xstr1 =  XmStringCreateLtoR ( "FEQL on", charset );

      feql_widget_but =
          XmVaCreateSimpleOptionMenu ( menu_rc, "Canvas",
          xstr, 0,
          0, FEQL_CB,
          XmVaPUSHBUTTON, xstr0, NULL, NULL, NULL,
          XmVaPUSHBUTTON, xstr1, NULL, NULL, NULL,
          NULL);

      XmStringFree ( xstr );
      XmStringFree ( xstr0 );
      XmStringFree ( xstr1 );

     XtVaSetValues ( feql_widget_but,
          XmNshadowThickness,        0,
          /* 
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          */
          XmNdefaultButtonShadowThickness,     0,
          XmNhighlightThickness,     1,
          XmNnavigationType,         XmTAB_GROUP,
          NULL);

      XtManageChild ( feql_widget_but );

    }

#endif

#ifndef BTOOLKIT_FLAG

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Change Rule", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ change_rule_but ] );

    but = CreHighlightedButton ( menu_rc, "Move Rule", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ move_rule_but ] );

    but = CreHighlightedButton ( menu_rc, "Remove Rule", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ remove_rule_but ] );

    but = CreHighlightedButton ( menu_rc, "Rule on/off", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ rule_on_off_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
          NULL );

    but = CreHighlightedButton ( menu_rc, "Reload (Source)", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ reload_source_rule_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Change Normal Tactic", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ change_normal_tac_rule_but ] );

    but = CreHighlightedButton ( menu_rc, "Change Forward Tactic", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ change_fwd_tac_rule_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
          NULL );

    but = CreHighlightedButton ( menu_rc, "Change Normal Quota", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ change_normal_quota_rule_but ] );

    but = CreHighlightedButton ( menu_rc, "Change Forward Quota", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ change_fwd_quota_rule_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    rule_browse_widget_but = CreHighlightedButton
        ( menu_rc, "Browse Theories", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ browse_theories_but ] );

#else

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    rule_browse_widget_but = CreHighlightedButton
         ( menu_rc, "Browse Library/Edit BTool Theory", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ browse_theories_but ] );

    but = CreHighlightedButton ( menu_rc, "Edit Current PROOFMETHOD", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ edit_cur_PMD_but ] );

    but = CreHighlightedButton ( menu_rc, "Edit Global PROOFMETHOD", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ edit_glob_PMD_but ] );

    but = CreHighlightedButton ( menu_rc, "Reload Current PROOFMETHOD", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ reload_PMD_but ] );

#endif

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Quit to Theory Menu", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ theory_menu_but ] );

    but = CreHighlightedButton ( menu_rc, "Quit to Main Menu", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ main_menu_rule_but ] );

    XtManageChild ( B_logo );
    XtManageChild ( Label );
    XtManageChild ( menu_scroll );
    XtManageChild ( menu_rc );

    XtAddCallback ( display_a_rule_dialog, XmNpopupCallback,
        ( XtCallbackProc ) RepositionMenu_CB,
        NULL );

  }

#ifdef BTOOLKIT_FLAG
  if ( ProvedPrevLevel ( val_rul_the ( curr_thy, curr_rule ) ) ) {
    XtVaSetValues ( prv_but, XmNsensitive, False, NULL );
    XtVaSetValues ( prt_prf_tree_but, XmNsensitive, False, NULL );
    XtVaSetValues ( dsply_prf_but, XmNsensitive, False, NULL );
    XtVaSetValues ( remprf_but, XmNsensitive, False, NULL );
  }
  else {
    if ( pvd_rul ( val_rul_the ( curr_thy, curr_rule ) ) != now_rul ) {
      XtVaSetValues ( prv_but, XmNsensitive, True, NULL );
      XtVaSetValues ( prt_prf_tree_but, XmNsensitive, False, NULL );
      XtVaSetValues ( dsply_prf_but, XmNsensitive, False, NULL );
      XtVaSetValues ( remprf_but, XmNsensitive, False, NULL );
    }
    else {
      XtVaSetValues ( prv_but, XmNsensitive, False, NULL );
      XtVaSetValues ( prt_prf_tree_but, XmNsensitive, True, NULL );
      XtVaSetValues ( dsply_prf_but, XmNsensitive, True, NULL );
      XtVaSetValues ( remprf_but, XmNsensitive, True, NULL );
    }
  }

#else

  if ( pvd_rul ( val_rul_the ( curr_thy, curr_rule ) ) != now_rul ) {
    XtVaSetValues ( prv_but, XmNsensitive, True, NULL );
    XtVaSetValues ( prt_prf_tree_but, XmNsensitive, False, NULL );
    XtVaSetValues ( prt_prf_but, XmNsensitive, False, NULL );
    XtVaSetValues ( dsply_prf_but, XmNsensitive, False, NULL );
    XtVaSetValues ( remprf_but, XmNsensitive, False, NULL );
  }
  else {
    XtVaSetValues ( prv_but, XmNsensitive, False, NULL );
    XtVaSetValues ( prt_prf_tree_but, XmNsensitive, True, NULL );
    XtVaSetValues ( prt_prf_but, XmNsensitive, True, NULL );
    XtVaSetValues ( dsply_prf_but, XmNsensitive, True, NULL );
    XtVaSetValues ( remprf_but, XmNsensitive, True, NULL );
  }

#endif

                 /*** DisplayARuleMenu ***/
  RemoveBottomForm ();
#ifdef BTOOLKIT_FLAG
  UnHideTopWin ();
#endif

/***
printf ( "query_box_flag %d\n", query_box_flag );
***/
  curr_dialog_menu = dialog_form;
  curr_menu = a_rule_menu;

  XtManageChild ( dialog_form );

  if ( browse_theories_is_up || browse_a_theory_is_up ) {
    XtVaSetValues ( rule_browse_widget_but, XmNsensitive, False, NULL );
  }
  else {
    XtVaSetValues ( rule_browse_widget_but, XmNsensitive, True, NULL );
  }
  XmUpdateDisplay ( rule_browse_widget_but );

  XtPopup ( display_a_rule_dialog, XtGrabNone );
  XmUpdateDisplay ( display_a_rule_dialog );
  XmUpdateDisplay ( top_level );

/***
print_live_nodes ( "RuleMenu" );
***/
}

/***
void
list_all_theories_loaded()
{
  int i;

  for ( i = 1 ; i <= last_btl_thy_to_display + 10 ; i++ ) {
    sprintf ( str_buf, "%2d: ", i );
    write_nam_the ( i );
    printf ( "%s (%d)\n", str_buf, nbr_rul_the ( i ) );
  }

  sprintf ( str_buf, "%2d: ", last_btl_thy_to_display );
  write_nam_the ( last_btl_thy_to_display );
  printf ( "last_btl_thy_to_display: %s (%d)\n", str_buf );

  sprintf ( str_buf, "%2d: ", last_btl_fwd_thy );
  write_nam_the ( last_btl_fwd_thy );
  printf ( "last_btl_fwd_thy: %s (%d)\n", str_buf );

  sprintf ( str_buf, "%2d: ", first_btl_thy_to_display );
  write_nam_the ( first_btl_thy_to_display );
  printf ( "first_btl_thy_to_display: %s (%d)\n", str_buf );

  sprintf ( str_buf, "%2d: ", btl_users_thy );
  write_nam_the ( btl_users_thy );
  printf ( "btl_users_thy: %s (%d)\n", str_buf );

  sprintf ( str_buf, "%2d: ", fwd_btl_users_thy );
  write_nam_the ( fwd_btl_users_thy );
  printf ( "fwd_btl_users_thy: %s (%d)\n", str_buf );

  sprintf ( str_buf, "%2d: ", last_rewrite_thy );
  write_nam_the ( last_rewrite_thy );
  printf ( "last_rewrite_thy: %s (%d)\n", str_buf );

  sprintf ( str_buf, "%2d: ", last_lib_thy );
  write_nam_the ( last_lib_thy );
  printf ( "last_lib_thy: %s (%d)\n", str_buf );

  sprintf ( str_buf, "%2d: ", nbr_the );
  write_nam_the ( nbr_the );
  printf ( "nbr_the: %s (%d)\n", str_buf );
}
***/

XtCallbackProc
Proof_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;
  int but_num =  * ( int * ) client_data;
  int i;

  int run_Proof_CB = FALSE;

  void CreProofTreeDialog ();

/***
printf ( "Proof_CB ()\n" );
***/

  from_applicable_rr = 0;

  PopdownCurrMenu ();

  run_man_prf_f = frm_gol(run_man_prf_g);

  run_man_prf_success = FALSE;

  switch ( but_num ) {

  case show_applicable_rules_but:
/***
list_all_theories_loaded();
***/
    run_app_prf(run_man_prf_r,run_man_prf_p,run_man_prf_i,run_man_prf_g,1);
    run_Proof_CB = TRUE;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case loop_until_quota_but:

#ifdef BTOOLKIT_FLAG
  run_button_pressed = 1;
#endif
    auto_prf=TRUE;
    ctr_prf=max_ctr_prf;
    one_step_of_prf ();
  break;

 case single_step_but:
    one_step_of_prf ();
  break;

 case undo_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    end_of_tac_prf=FALSE;
    run_man_prf_run_man_prf_res=(-run_man_prf_i);
    auto_prf=FALSE;
    run_man_prf_success=TRUE;
    undo_was_last_button = 1;
/***
printf ( "undo_was_last_button=%d (1)\n", undo_was_last_button );
***/
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break; 

#ifdef BTOOLKIT_FLAG

 case max_fwd_hyp_but:
  Popup_SetMaxGenHyp ();
  break;

#endif /* BTOOLKIT_FLAG */

  case and_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    if( and_prf(run_man_prf_i,run_man_prf_g,run_man_prf_f)==TRUE ) {
      run_man_prf_success=TRUE;
    }
    run_man_prf_run_man_prf_res=run_man_prf_i;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case call_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    if( cal_prf(run_man_prf_p,run_man_prf_i,run_man_prf_g,run_man_prf_f)==TRUE ) {
      run_man_prf_success=TRUE;
    }
    run_man_prf_run_man_prf_res=run_man_prf_i;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case eql_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    if( eql_prf(run_man_prf_g,run_man_prf_f)==TRUE ) {
      run_man_prf_success=TRUE;
    }
    run_man_prf_run_man_prf_res=run_man_prf_i;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case inhyp_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    if( hyp_prf(run_man_prf_p,run_man_prf_i,run_man_prf_g,run_man_prf_f)==TRUE ) {
      run_man_prf_success=TRUE;
    }
    run_man_prf_run_man_prf_res=run_man_prf_i;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case ded_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    if( ded_prf(run_man_prf_r,run_man_prf_p,run_man_prf_i,run_man_prf_g,run_man_prf_f)==TRUE ) {
      run_man_prf_success=TRUE;
    }
    run_man_prf_run_man_prf_res=run_man_prf_i;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case gen_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=gen_prf(run_man_prf_p,run_man_prf_i,run_man_prf_g,run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case hyp_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    {
      register int t;
      t=info_nod(tac_ptr_prf);
      mon2_hyp_prf(t,run_man_prf_p,run_man_prf_i,run_man_prf_g,run_man_prf_f);
    }
  break;

  case ari_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    {
      register int t;
      t=info_nod(tac_ptr_prf);
      ari_prf( t );
    }
  break;

  case create_lemma_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
/***
printf ( "(Not BToolkit) Proof_CB: switch ( but_num ) - case create_lemma_but\n" );
***/
    run_man_prf_ff=cre_frm(nam_the (the_rul(run_man_prf_r)));
    run_man_prf_fff=cons_frm(run_man_prf_ff,MUL_sym,run_man_prf_f);
    run_man_prf_gl=cre_gol(run_man_prf_fff);
    cre_nod(run_man_prf_gl,run_man_prf_i);
    mod_spe_gol(run_man_prf_g,LEM_gol);
    mod_rul_gol(run_man_prf_g,0);
    kil(run_man_prf_ff);
    run_man_prf_i=next_nod(run_man_prf_p,run_man_prf_i);
    run_man_prf_success=add_rul_prf(run_man_prf_p,run_man_prf_i,run_man_prf_r,run_man_prf_fff);
    run_man_prf_run_man_prf_res=run_man_prf_i;
    if ( browse_theories_is_up ) {
      BrowseTheories ( 0, 0 );
      BrowseTheories ( 1, 0 );
    }
    else if ( curr_thy == browse_a_theory_is_up ) {
      int browse_a_theory_is_up_save;
      browse_a_theory_is_up_save = browse_a_theory_is_up;
      BrowseATheory ( 0, 0 );
      browse_a_theory_is_up = browse_a_theory_is_up_save;
      BrowseATheory ( browse_a_theory_is_up, 0 );
    }
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;     

  case sub_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
   run_man_prf_success=sub_prf_func(run_man_prf_p,run_man_prf_i,run_man_prf_g,run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case rev_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=rev_prf(run_man_prf_i,run_man_prf_g,run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case flat_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=flat_prf(run_man_prf_i,run_man_prf_g,run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case map_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=smap_prf(run_man_prf_i,run_man_prf_g,run_man_prf_f);
    if ( ! run_man_prf_success )
      run_man_prf_success=nmap_prf(run_man_prf_i,run_man_prf_g,run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case lmap_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success= slmap_prf(run_man_prf_i,run_man_prf_g,run_man_prf_f);
    if ( ! run_man_prf_success )
      run_man_prf_success=nlmap_prf(run_man_prf_i,run_man_prf_g,run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;    
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case modr_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=bmodr_prf(run_man_prf_f);
    if ( ! run_man_prf_success )
      run_man_prf_success=bmark_proved_prf(run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    if ( run_man_prf_success ) mod_is_frm_gol ( run_man_prf_g, 1 );
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case rule_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=badd_rul_prf(run_man_prf_p,run_man_prf_i,run_man_prf_r,run_man_prf_f);
    if ( ! run_man_prf_success )
      run_man_prf_success=badd_lirul_prf(run_man_prf_r,run_man_prf_f);
    if ( ! run_man_prf_success )
      run_man_prf_success=bpopt_prf(run_man_prf_r,run_man_prf_f);
    if ( ! run_man_prf_success )
      run_man_prf_success=bcleant_prf(run_man_prf_r,run_man_prf_f);
    if ( run_man_prf_success ) mod_is_frm_gol ( run_man_prf_g, 1 );
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case write_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=bwritef_prf(run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    if ( run_man_prf_success ) mod_is_frm_gol ( run_man_prf_g, 1 );
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case catl_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=bcatl_prf(run_man_prf_i,run_man_prf_g,run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    Proof_CB_continued ( run_Proof_CB , proof_step_flag_NO);
  break;

  case shell_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=bshell_prf(run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    if ( run_man_prf_success ) mod_is_frm_gol ( run_man_prf_g, 1 );
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case recompact_but:
    run_man_prf_success=recompact_prf(run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    if ( run_man_prf_success ) mod_is_frm_gol ( run_man_prf_g, 1 );
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

#ifdef BTOOLKIT_FLAG

  case lemma_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    {
      int b, h, i, f, s, v;
/***
strcpy ( str_buf, "`Created from " );
write_nam_the ( curr_thy );
strcat ( str_buf, "." );
write_nat ( curr_rule );
strcat ( str_buf, " (" );
write_nat ( val_rul_the ( curr_thy, curr_rule ) );
strcat ( str_buf, ")" );
strcat ( str_buf, "'\n" );
printf ( str_buf );
***/
      str_buf [ 0 ] = '\0';
      s=cre(100);
      lst_hyp_prf(run_man_prf_p,run_man_prf_i,s);
      rev(s);
      save_MAX_COL_RES;
      mod_MAX_COL_RES(999999);
      b=TRUE;
      itr(s,i,h,{
            v=val_root_frm(frm_hyp(h));
            if( (v==ANTI_SLASH_sym) || (v==BVRB_sym) ){
              {};
            } else if( isa_der_hyp(h)==TRUE ){
              {};
            } else {
              b=TRUE;
              reset_res(0);
              write_frm_res(frm_hyp(h),0);
              strcat ( str_buf, "&\n" );
            }
         ;});
      restore_MAX_COL_RES;
      kil(s);
      if ( strlen ( str_buf ) > 1 ) {
        str_buf [ strlen ( str_buf ) - 2 ] = '\0';
        strcat ( str_buf, "\n=>\n" );
      }
      write_gol_prf_no_nl (  run_man_prf_g );
      f = read_frm_str_buf;
      if ( f != -999 ) {
        if ( nbr_rul_the ( last_btl_thy_to_display ) + 1 <  btl_lem_rul_MAX ) {
          read_rul_the ( last_btl_thy_to_display, f ); /* BToolLemmas */
          from_applicable_rr = - ( val_rul_the ( last_btl_thy_to_display,
                                   nbr_rul_the ( last_btl_thy_to_display ) ) );
          add_next_BToolLemmas ( -from_applicable_rr,
                                              val_rul_the ( curr_thy, curr_rule ) );
          run_man_prf_success = TRUE;
	}
        else {
          sprintf ( buf, "Maximum BToolLemmas capacity reached (%d)", btl_lem_rul_MAX );
          Popup_Info ( buf );
          kil ( f );
          run_man_prf_success = FALSE;
	}
      }
      else {
        run_man_prf_success = FALSE;
      }

      if ( run_man_prf_success ) {
        mod_spe_gol(run_man_prf_g,LEM_gol);
        mod_rul_gol ( run_man_prf_g, ( - from_applicable_rr ) );
      }
      run_man_prf_run_man_prf_res=run_man_prf_i;

    }
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
    break;

#endif

  case newv_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=bnewv_vrb_prf(run_man_prf_i,run_man_prf_g,run_man_prf_f);
    if ( ! run_man_prf_success )
      run_man_prf_success=low_prf(run_man_prf_i,run_man_prf_g,run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case tactic_but:
    run_man_prf_success=badd_tac_prf(run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    if ( run_man_prf_success ) mod_is_frm_gol ( run_man_prf_g, 1 );
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case close_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=clo_prf(run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    if ( run_man_prf_success ) mod_is_frm_gol ( run_man_prf_g, 1 );
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case statistics_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=stat_prf(run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    if ( run_man_prf_success ) mod_is_frm_gol ( run_man_prf_g, 1 );
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case redo_but:
  case halt_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
#endif
    run_man_prf_success=hlt_prf(run_man_prf_r,run_man_prf_g,run_man_prf_f);
    run_man_prf_run_man_prf_res=run_man_prf_i;      
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case tactic_browse_but:
    tac_ptr_prf=nxt_tac_prf(tac_prf,tac_ptr_prf);
    new_tac_prf=FALSE;
    run_Proof_CB=TRUE;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case dump_hypotheses_but:
    str_buf [ 0 ] = '\0';
    redirect_trm("b.hyp"); 
/* freopen("b.s","w", bstdout); */
    if( sho_der_hyp_prf==FALSE ) {
      sho_der_hyp_prf=TRUE;
/*
        writeln_lst_hyp_prf(run_man_prf_p,run_man_prf_i);
*/
      ;
      sho_der_hyp_prf=FALSE;
    }
    else {
/*
      writeln_lst_hyp_prf(run_man_prf_p,run_man_prf_i);
*/
      ;
    }
    if ( strlen ( str_buf ) > 0 ) {
      fprintf ( bstdout, "HYPOTHESES:\n\n" );
      fprintf ( bstdout, str_buf );
    }
    else {
      fprintf ( bstdout, "No hypotheses\n" );
    }
      reset_trm; 
/* freopen(TERMINAL,"w", bstdout); */
    Popup_Info ( " Hypotheses written to file b.hyp " );
    run_Proof_CB=TRUE;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

/*
  case toggle_show_goals_but:
    sho_gol_prf=((sho_gol_prf==FALSE)!=0);
    run_Proof_CB=TRUE;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  case toggle_show_hyp_but:
    sho_der_hyp_prf=((sho_der_hyp_prf==FALSE)!=0);
    run_Proof_CB=TRUE;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;
*/

  case change_normal_quota_proof_but:
    Normal_quota_prf;
  break;

  case change_fwd_quota_proof_but:
    Forward_quota_prf;
  break;

  case quit_proof_but:
#ifdef BTOOLKIT_FLAG
  run_button_pressed = 0;
  backtrack_attempted = 0;
  backtrack_succeeded = 0;
  another_backtrack_required = 0;
#endif
    if ( cbs->reason == XmCR_PROTOCOLS ) {
      WM_KillCurrMenu ();
      abt_prf=TRUE;
      run_man_prf_success=TRUE;
      /*      DisplayCurrWinText ( " - aborted\n" ); */
      run_man_prf_run_man_prf_res=run_man_prf_i;
      /*      CreProofTreeDialog ( 0 ); */
#ifdef BTOOLKIT_FLAG
      check_rem_BToolLemmas ( val_rul_the ( curr_thy, curr_rule ) );
#endif
      Proof_CB_continued ( TRUE, proof_step_flag_NO );
    }
    else {
      strcpy ( str_buf, "    Quit Proof?   ");
      query_box_flag = query_box_quit_proof;
      QueryBox ( " Quit Proof? " );
    }
  break;

  default :
    Popup_Info ( "     Not yet implemented!         " );
    run_Proof_CB=TRUE;
    Proof_CB_continued ( run_Proof_CB, proof_step_flag_NO );
  break;

  }   /* switch ( but_num ) */

}

void
Proof_CB_continued ( run_Proof_CB, proof_step_flag )
int run_Proof_CB, proof_step_flag;
{
/***
printf ( "Proof_CB_continued: success %d run_Proof_CB %d proof_step_flag %d \n  from_applicable_rr %d tac_the(%d) %d run_man_prf_i %d\n", run_man_prf_success, run_Proof_CB, proof_step_flag, from_applicable_rr, curr_thy, tac_the(curr_thy), run_man_prf_i );
***/

  /***
  move tactic pointer if ! run_man_prf_success
  ***/

  if ( ( ! run_man_prf_success )  &&
       ( proof_step_flag )        &&
       ( from_applicable_rr == 0 )   ) {

    if( new_tac_prf==FALSE ){
      tac_ptr_prf=nxt_tac_prf(tac_prf,tac_ptr_prf);
    }
    else {
      new_tac_prf=FALSE;
    }

  }

  /************ print unsuccessful messages if required **********/

  /***
  print application of rule unsuccessful if from_applicable_rr
  ***/

  if      ( ( ! val_batch_sys )        && 
            ( proof_step_flag )        &&
            ( ! run_man_prf_success )  &&
            ( from_applicable_rr > 0 )    ) { /* applicable rules attempted */

    str_buf [ 0 ] = '\0';
    write_nam_the ( the_rul ( from_applicable_rr ) );
    sprintf ( buf, "  Application of %s.%d did not succeed ...  ",
                                        str_buf, num_rul ( from_applicable_rr ) );
    Popup_Info ( buf );

  }

  /***
  print no appropriate rule applies if end_of_tac_prf
  ***/

  else if ( ( ! val_batch_sys )           && 
            ( proof_step_flag )           &&
            ( ! run_man_prf_success )     &&
            ( from_applicable_rr != -1 )  && /* ! applicable rules dismissed */
            ( end_of_tac_prf )               ) {

    Popup_Info ( "   No appropriate rule applies  " );

  }

  /********************* NOT run_man_prf_success  *******************/

  if ( ! run_man_prf_success ) {

    /***
    run_man_prf_A if from_applicable_rr/! proof_step_flag/end_of_tac_prf
    this throws up the Proof Menu window
    ***/

    if ( ( from_applicable_rr )  ||
         ( ! proof_step_flag )   ||
         ( end_of_tac_prf )          ) {

      run_man_prf_A ();

    }

    /***
    else one_step_of_prf (single step(curr tac not apply)/loop)
    this continues the proof
    ***/

    else {

     one_step_of_prf ();

    }

  }

  /********************* run_man_prf_success ... *******************/

  else {
    /***
    run_man_prf_success - loop_do_prf_B ();
    ***/

    loop_do_prf_j = run_man_prf_run_man_prf_res;
    if ( ! val_batch_sys ) {
/***
printf ( "  ))))))))))  RedrawProofTree(%d,%d) - motif.c - Proof_CB_continued\n", 
                                                 run_man_prf_p, run_man_prf_i );
printf ( "  ))))))))))  but not redrawing ...\n" );
***/
/*
      RedrawProofTree ( run_man_prf_p, run_man_prf_i );
*/
    }
    loop_do_prf_B ();

  }

}

void
ProveRuleMenu ( flag, WM_flag )
int flag;
int WM_flag;
{
  static Widget  dialog_form, B_logo,
                 Label, HighlightLabel, menu_scroll, menu_rc;

  static Widget show_app_but,
                and_widget_but, call_widget_but, eql_widget_but,
                inhyp_widget_but, ded_widget_but, gen_widget_but,
                hyp_widget_but, ari_widget_but, sub_widget_but, form,
                flat_widget_but, map_widget_but, lmap_widget_but,
                modr_widget_but, rule_widget_but, write_widget_but,
                catl_widget_but, shell_widget_but, recompact_widget_but,
                lemma_widget_but,
                newv_widget_but, tactic_widget_but, close_widget_but,
                halt_widget_but, rev_widget_but, max_fwd_hyp_widget_but,
                statistics_widget_but, redo_widget_but, undo_widget_but;

  static Atom  WM_DELETE_WINDOW;

  Widget but;

  XmString xstr;

  static int first_time = 1;

  static Position last_menu_x, last_menu_y;

  int f;

  int binhyp_is_applicable, eql_is_applicable, and_is_applicable;

/***
printf ( "ProveRuleMenu (flag=%d WM_flag=%d) app_rule_dialog=%d\n", flag, WM_flag, app_rule_dialog );
***/

  if ( WM_flag ) {
      XtDestroyWidget ( prove_rule_dialog );
      first_time = 1;
      return;
  }

/***
printf ( "----- ProveRuleMenu:tac_the(%d) %d flag=%d app_rule_dialog=%d\n",
                          curr_thy, tac_the(curr_thy), flag, app_rule_dialog );
***/
  if ( app_rule_dialog ) return;

  if ( ! flag ) {

/***
printf ( "! flag and CHANGING applicable_rules_up=%d\n", applicable_rules_up );
***/

    if ( ! applicable_rules_up ) {

      XtVaGetValues ( prove_rule_dialog, 
          XmNx,       & last_menu_x,
          XmNy,       & last_menu_y,
          NULL );

      if (  menu_position_changed_x ) {
        global_menu_x = last_menu_x - wm_width;
      }

      if (  menu_position_changed_y ) {
        global_menu_y = last_menu_y - wm_height;
      }

    }

    XtPopdown ( prove_rule_dialog );
    XmUpdateDisplay ( top_level );
    return;

  }

  if ( first_time ) {

    first_time = 0;

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    prove_rule_dialog =
       XmCreateDialogShell ( top_frame_form, "SelDialog", NULL, 0 );

    XmAddWMProtocolCallback ( prove_rule_dialog, WM_DELETE_WINDOW,
        ( XtCallbackProc ) Proof_CB,
              ( XtPointer ) & c_arr [  quit_proof_but ] );

    dialog_form = XtVaCreateWidget ( "SelDialog",
        xmFormWidgetClass,         prove_rule_dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        False,  
        NULL );

    B_logo =  XtVaCreateWidget ( "SelDialog",
        xmLabelWidgetClass,         dialog_form,
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

    xstr = XmStringCreateLtoR ( "Proof Menu", charset );
    Label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
#ifndef BTOOLKIT_FLAG
        XmNleftOffset,             10,
#else
        XmNleftOffset,             15,
#endif
        XmNlabelString,            xstr,
        XmNmarginWidth,            0,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

    xstr = XmStringCreateLtoR ( "(Click to apply)", charset );
    HighlightLabel = XtVaCreateWidget ( "Highlight", 
        xmLabelWidgetClass,        dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             Label,
        XmNleftOffset,             15,
        XmNrightAttachment,        XmATTACH_FORM,
#ifndef BTOOLKIT_FLAG
        XmNrightOffset,            15,
#else
        XmNrightOffset,            15,
#endif
        XmNlabelString,            xstr,
        XmNmarginWidth,            0,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

    menu_scroll = XtVaCreateWidget ( "SelDialog",
        xmScrolledWindowWidgetClass,    dialog_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   50,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 5,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  5,
        XmNbottomAttachment,            XmATTACH_FORM,
        XmNbottomOffset,                10,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
/*
        XmNwidth,                       5,
*/
#ifndef BTOOLKIT_FLAG

        XmNheight,                      460,
#else

#ifdef BTOOL_PROVER_NEW
	XmNheight,                      295, /* 325, */
#else
        XmNheight,                      265,
#endif /* BTOOL_PROVER_NEW */

#endif /* BTOOLKIT_FLAG */

        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNspacing,                     0,
        NULL );

  menu_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         menu_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNspacing,                     5,
      XmNisHomogeneous,               False,
      NULL );

#ifndef BTOOLKIT_FLAG

    but = CreHighlightedButton ( menu_rc, "Single Step (Tactic)", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ single_step_but ] );

    but = CreHighlightedButton ( menu_rc, "Loop Until Quota (Tactic)", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ loop_until_quota_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

#else

#ifdef BTOOL_PROVER_NEW

/*
    but = CreHighlightedButton ( menu_rc, "Single Step (Library Tactic)", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ single_step_but ] );
*/

    run_but_library = CreHighlightedButton ( menu_rc, "Run/Backtrack (Library Tactic)", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ loop_until_quota_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

#endif /* BTOOL_PROVER_NEW */

#endif /* BTOOLKIT_FLAG */

    form = XtVaCreateManagedWidget ( "SelDialog",
        xmFormWidgetClass,       menu_rc,
        NULL );

    and_widget_but = CreHighlightedProofButton ( form, "AND", 0, 0,
        ( XtCallbackProc ) Proof_CB, & c_arr [ and_but ] );

    call_widget_but = CreHighlightedProofButton ( form, "CALL", 0, 1,
        ( XtCallbackProc ) Proof_CB, & c_arr [ call_but ] );

    eql_widget_but = CreHighlightedProofButton ( form, "EQL", 0, 2,
        ( XtCallbackProc ) Proof_CB, & c_arr [ eql_but ] );

    ded_widget_but = CreHighlightedProofButton ( form, "DED",  0, 3,
        ( XtCallbackProc ) Proof_CB, & c_arr [ ded_but ] );

    inhyp_widget_but = CreHighlightedProofButton ( form, "INHYP", 0, 4,
        ( XtCallbackProc ) Proof_CB, & c_arr [ inhyp_but ] );

    gen_widget_but = CreHighlightedProofButton ( form, "GEN", 1, 0,
        ( XtCallbackProc ) Proof_CB, & c_arr [ gen_but ] );

    hyp_widget_but = CreHighlightedProofButton ( form, "HYP", 1, 1,
        ( XtCallbackProc ) Proof_CB, & c_arr [ hyp_but ] );

    ari_widget_but = CreHighlightedProofButton ( form, "ARI", 1, 2,
        ( XtCallbackProc ) Proof_CB, & c_arr [ ari_but ] );

    sub_widget_but = CreHighlightedProofButton ( form, "SUB", 1, 3,
        ( XtCallbackProc ) Proof_CB, & c_arr [ sub_but ] );

    flat_widget_but = CreHighlightedProofButton ( form, "FLAT", 1, 4,
        ( XtCallbackProc ) Proof_CB, & c_arr [ flat_but ] );

    rev_widget_but = CreHighlightedProofButton ( form, "REV", 2, 0,
        ( XtCallbackProc ) Proof_CB, & c_arr [ rev_but ] );

    map_widget_but = CreHighlightedProofButton ( form, "MAP", 2, 1,
        ( XtCallbackProc ) Proof_CB, & c_arr [ map_but ] );

    lmap_widget_but = CreHighlightedProofButton ( form, "LMAP", 2, 2,
        ( XtCallbackProc ) Proof_CB, & c_arr [ lmap_but ] );

    modr_widget_but = CreHighlightedProofButton ( form, "MODR", 2, 3,
        ( XtCallbackProc ) Proof_CB, & c_arr [ modr_but ] );

    rule_widget_but = CreHighlightedProofButton ( form, "RULE", 2, 4,
        ( XtCallbackProc ) Proof_CB, & c_arr [ rule_but ] );

    write_widget_but = CreHighlightedProofButton ( form, "WRITE", 3, 0,
        ( XtCallbackProc ) Proof_CB, & c_arr [ write_but ] );

    catl_widget_but = CreHighlightedProofButton ( form, "CATL", 3, 1,
        ( XtCallbackProc ) Proof_CB, & c_arr [ catl_but ] );

    shell_widget_but = CreHighlightedProofButton ( form, "SHELL", 3, 2,
        ( XtCallbackProc ) Proof_CB, & c_arr [ shell_but ] );

    newv_widget_but = CreHighlightedProofButton ( form, "NEWV", 3, 3,
        ( XtCallbackProc ) Proof_CB, & c_arr [ newv_but ] );

    tactic_widget_but = CreHighlightedProofButton ( form, "TACTIC", 3, 4,
        ( XtCallbackProc ) Proof_CB, & c_arr [ tactic_but ] );

    close_widget_but = CreHighlightedProofButton ( form, "CLOSE", 4, 0,
        ( XtCallbackProc ) Proof_CB, & c_arr [ close_but ] );

    halt_widget_but = CreHighlightedProofButton ( form, "HALT", 4, 1,
        ( XtCallbackProc ) Proof_CB, & c_arr [ halt_but ] );

    redo_widget_but = CreHighlightedProofButton ( form, "REDO", 4, 2,
        ( XtCallbackProc ) Proof_CB, & c_arr [ redo_but ] );

    statistics_widget_but = CreHighlightedProofButton ( form, "STATISTICS", 4, 3,
        ( XtCallbackProc ) Proof_CB, & c_arr [ statistics_but ] );

#ifdef BTOOLKIT_FLAG

    lemma_widget_but = CreHighlightedProofButton ( form, "LEMMA", 5, 0,
        ( XtCallbackProc ) Proof_CB, & c_arr [ lemma_but ] );

    recompact_widget_but = CreHighlightedProofButton ( form, "RECOMPACT", 5, 1,
        ( XtCallbackProc ) Proof_CB, & c_arr [ recompact_but ] );

#else

    recompact_widget_but = CreHighlightedProofButton ( form, "RECOMPACT", 5, 0,
        ( XtCallbackProc ) Proof_CB, & c_arr [ recompact_but ] );

#endif

    show_app_but = CreHighlightedButton ( menu_rc, "Show all applicable rules", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ show_applicable_rules_but ] );

#ifdef BTOOLKIT_FLAG

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    max_fwd_hyp_widget_but = CreHighlightedButton ( menu_rc, "Set Max Generated Hypotheses", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ max_fwd_hyp_but ] );

#endif /* BTOOLKIT_FLAG */

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    undo_widget_but = CreHighlightedButton ( menu_rc, "Undo", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ undo_but ] );

#ifndef BTOOLKIT_FLAG

    but = CreHighlightedButton ( menu_rc, "Create Lemma", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ create_lemma_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Tactic Browse", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ tactic_browse_but  ] );

    but = CreHighlightedButton ( menu_rc, "Dump Hypotheses", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ dump_hypotheses_but ] );

    but = CreHighlightedButton ( menu_rc, "Statistics", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ statistics_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Change Normal Quota", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ change_normal_quota_proof_but ] );

    but = CreHighlightedButton ( menu_rc, "Change Forward Quota", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ change_fwd_quota_proof_but ] );

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    prove_browse_widget_but = CreHighlightedButton ( menu_rc, "Browse Theories", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ browse_theories_but ] );

#else

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    prove_browse_widget_but = CreHighlightedButton ( menu_rc, "Browse Library/Edit BTool Theory", 
              ( XtCallbackProc ) TLMenu_CB,
              & c_arr [ browse_theories_but ] );

#endif

    XtVaCreateManagedWidget ( "SelDialog",
          xmSeparatorGadgetClass,  menu_rc,
      NULL );

    but = CreHighlightedButton ( menu_rc, "Quit Proof", 
              ( XtCallbackProc ) Proof_CB,
              & c_arr [ quit_proof_but ] );

    XtManageChild ( B_logo );
    XtManageChild ( Label );
    XtManageChild ( HighlightLabel );
    XtManageChild ( menu_scroll );
    XtManageChild ( menu_rc );

    XtAddCallback ( prove_rule_dialog, XmNpopupCallback,
        ( XtCallbackProc ) RepositionMenu_CB,
        NULL );

  }

  f = frm_gol( run_man_prf_g );

  if ( app_eql_prf( run_man_prf_g, f ) ) {
    eql_is_applicable = 1;
    XtVaSetValues ( eql_widget_but, XmNsensitive, True, NULL );
  }
  else {
    eql_is_applicable = 0;
    XtVaSetValues ( eql_widget_but, XmNsensitive, False, NULL );
  }

  if ( app_hyp_prf( run_man_prf_p,run_man_prf_i,run_man_prf_g, f ) ) {
    binhyp_is_applicable = 1;
    XtVaSetValues ( inhyp_widget_but, XmNsensitive, True, NULL );
  }
  else {
    binhyp_is_applicable = 0;
    XtVaSetValues ( inhyp_widget_but, XmNsensitive, False, NULL );
  }

  if ( ( ! eql_is_applicable )                           &&
       ( ! binhyp_is_applicable )                        &&
       ( app_and_prf( run_man_prf_i,run_man_prf_g, f ) )    ) {
    and_is_applicable = 1;
    XtVaSetValues ( and_widget_but, XmNsensitive, True, NULL );
  }
  else {
    and_is_applicable = 0;
    XtVaSetValues ( and_widget_but, XmNsensitive, False, NULL );
  }

  XtVaSetValues ( call_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( ded_widget_but, XmNsensitive, False, NULL );
#ifdef BTOOLKIT_FLAG
  XtVaSetValues ( max_fwd_hyp_widget_but, XmNsensitive, False, NULL );
#endif /* BTOOLKIT_FLAG */
  XtVaSetValues ( gen_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( hyp_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( ari_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( sub_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( flat_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( rev_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( map_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( lmap_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( modr_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( rule_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( write_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( catl_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( shell_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( newv_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( tactic_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( close_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( halt_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( redo_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( statistics_widget_but, XmNsensitive, False, NULL );
#ifdef BTOOLKIT_FLAG
  XtVaSetValues ( lemma_widget_but, XmNsensitive, False, NULL );
#endif
  XtVaSetValues ( recompact_widget_but, XmNsensitive, False, NULL );
  XtVaSetValues ( show_app_but, XmNsensitive, False, NULL );
  XtVaSetValues ( undo_widget_but, XmNsensitive, False, NULL );


  if ( ( ! eql_is_applicable )    &&
       ( ! binhyp_is_applicable ) &&
       ( ! and_is_applicable )       ) {

    run_app_prf(run_man_prf_r,run_man_prf_p,run_man_prf_i,run_man_prf_g,0);
    if   ( app_tot != 1 ) 
      XtVaSetValues ( show_app_but, XmNsensitive, True, NULL );

    if ( app_call_prf( run_man_prf_p,run_man_prf_i,run_man_prf_g, f ) )
      XtVaSetValues ( call_widget_but, XmNsensitive, True, NULL );

    if ( app_ded_prf( run_man_prf_r,run_man_prf_p,run_man_prf_i,run_man_prf_g, f ) ) {
      XtVaSetValues ( ded_widget_but, XmNsensitive, True, NULL );
#ifdef BTOOLKIT_FLAG
      XtVaSetValues ( max_fwd_hyp_widget_but, XmNsensitive, True, NULL );
#endif /* BTOOLKIT_FLAG */
    }

    if ( app_gen_prf( run_man_prf_p,run_man_prf_i,run_man_prf_g, f ) )
      XtVaSetValues ( gen_widget_but, XmNsensitive, True, NULL );

    if ( app_mon_hyp_prf( run_man_prf_p,run_man_prf_i,run_man_prf_g, f ) ) {
      XtVaSetValues ( hyp_widget_but, XmNsensitive, True, NULL );
    }
    else if ( app_mon2_hyp_prf( run_man_prf_p,run_man_prf_i,run_man_prf_g, f ) ) {
      XtVaSetValues ( hyp_widget_but, XmNsensitive, True, NULL );
    }

    if ( app_ari_prf( run_man_prf_i,run_man_prf_g, f ) )
      XtVaSetValues ( ari_widget_but, XmNsensitive, True, NULL );

    if ( app_sub_prf( run_man_prf_p,run_man_prf_i,run_man_prf_g, f ) )
      XtVaSetValues ( sub_widget_but, XmNsensitive, True, NULL );

    if ( app_clo_prf( f ) )
      XtVaSetValues ( close_widget_but, XmNsensitive, True, NULL );

    if ( app_stat_prf( f ) )
      XtVaSetValues ( statistics_widget_but, XmNsensitive, True, NULL );

    if ( app_redo_prf( run_man_prf_r, run_man_prf_g, f ) )
      XtVaSetValues ( redo_widget_but, XmNsensitive, True, NULL );

    if ( app_recompact_prf( f ) )
      XtVaSetValues ( recompact_widget_but, XmNsensitive, True, NULL );

#ifdef BTOOLKIT_FLAG

  XtVaSetValues ( lemma_widget_but, XmNsensitive, True, NULL );

#endif

    if ( app_hlt_prf( run_man_prf_r, run_man_prf_g, f ) )
      XtVaSetValues ( halt_widget_but, XmNsensitive, True, NULL );

    if ( app_rev_prf( run_man_prf_i, run_man_prf_g, f ) )
      XtVaSetValues ( rev_widget_but, XmNsensitive, True, NULL );

    if ( app_flat_prf( run_man_prf_i, run_man_prf_g, f ) )
      XtVaSetValues ( flat_widget_but, XmNsensitive, True, NULL );

    if ( app_smap_prf( run_man_prf_i, run_man_prf_g, f ) ) {
      XtVaSetValues ( map_widget_but, XmNsensitive, True, NULL );
    }
    else if ( app_nmap_prf( run_man_prf_i, run_man_prf_g, f ) ) {
      XtVaSetValues ( map_widget_but, XmNsensitive, True, NULL );
    }

    if ( app_bmodr_prf( f ) ) {
      XtVaSetValues ( modr_widget_but, XmNsensitive, True, NULL );
    }
    else if ( app_bmark_proved_prf ( f ) ) {
      XtVaSetValues ( modr_widget_but, XmNsensitive, True, NULL );
    }

    if ( app_bshell_prf( f ) )
      XtVaSetValues ( shell_widget_but, XmNsensitive, True, NULL );

    if ( app_bwritef_prf( f ) )
      XtVaSetValues ( write_widget_but, XmNsensitive, True, NULL );

    if ( app_badd_rul_prf( run_man_prf_p, run_man_prf_i, run_man_prf_r, f ) ) {
      XtVaSetValues ( rule_widget_but, XmNsensitive, True, NULL );
    }
    else if ( app_badd_lirul_prf( run_man_prf_r, f ) ) {
      XtVaSetValues ( rule_widget_but, XmNsensitive, True, NULL );
    }
    else if ( app_bpopt_prf( run_man_prf_r, f ) ) {
      XtVaSetValues ( rule_widget_but, XmNsensitive, True, NULL );
    }
    else if ( app_bcleant_prf( run_man_prf_r, f ) ) {
      XtVaSetValues ( rule_widget_but, XmNsensitive, True, NULL );
    }

    if ( app_badd_tac_prf( f ) )
      XtVaSetValues ( tactic_widget_but, XmNsensitive, True, NULL );

    if ( app_bcatl_prf( run_man_prf_i, run_man_prf_g, f ) )
      XtVaSetValues ( catl_widget_but, XmNsensitive, True, NULL );

    if ( app_bnewv_vrb_prf( run_man_prf_i, run_man_prf_g, f ) ) {
      XtVaSetValues ( newv_widget_but, XmNsensitive, True, NULL );
    }
    else if ( app_low_prf( run_man_prf_i, run_man_prf_g, f ) ) {
      XtVaSetValues ( newv_widget_but, XmNsensitive, True, NULL );
    }

    if ( app_slmap_prf(run_man_prf_i, run_man_prf_g, f ) ) {
      XtVaSetValues ( lmap_widget_but, XmNsensitive, True, NULL );
    }
    else if ( app_nlmap_prf( run_man_prf_i, run_man_prf_g, f ) ) {
      XtVaSetValues ( lmap_widget_but, XmNsensitive, True, NULL );
    }

  } /* if ( ( ! eql_is_applicable )    && ... */


#ifdef BTOOLKIT_FLAG
/***
printf ( "UNDO node_to_undo_to = %d\n", node_to_undo_to );
***/
#ifdef BTOOL_PROVER_NEW
  if ( node_to_undo_to )
#else
  if ( run_man_prf_p != run_man_prf_i )
#endif /* BTOOL_PROVER_NEW */
#else
  if ( run_man_prf_p != run_man_prf_i )
#endif /* BTOOLKIT_FLAG */

    XtVaSetValues ( undo_widget_but, XmNsensitive, True, NULL );

  if ( browse_theories_is_up || browse_a_theory_is_up ) {
    XtVaSetValues ( prove_browse_widget_but, XmNsensitive, False, NULL );
  }
  else {
    XtVaSetValues ( prove_browse_widget_but, XmNsensitive, True, NULL );
  }
  XmUpdateDisplay ( prove_browse_widget_but );

#ifdef BTOOLKIT_FLAG

#ifdef BTOOL_PROVER_NEW

/***/
printf ( "\n :::: motif.c - ProveRuleMenu:\n  run_button_pressed = %d\n  backtrack_attempted = %d backtrack_succeeded = %d\n  another_backtrack_required = %d\n", run_button_pressed, backtrack_attempted, backtrack_succeeded, another_backtrack_required );
/***/

  if ( ( ! run_button_pressed )                                 ||
       ( run_man_prf_p == run_man_prf_i )                       ||
       ( ( backtrack_attempted ) && ( ! backtrack_succeeded ) )    )
    xstr = XmStringCreateLtoR ( "Run (Library Tactic)", charset );
  else
    xstr = XmStringCreateLtoR ( "Backtrack (Library Tactic)", charset );
    
  XtVaSetValues ( run_but_library, XmNlabelString, xstr, NULL );
  XmStringFree ( xstr );
  XmUpdateDisplay ( run_but_library );

/*
  run_button_pressed = 0;
  backtrack_attempted = 0;
  backtrack_succeeded = 0;
*/

#endif /* BTOOL_PROVER_NEW */

#endif /* BTOOLKIT_FLAG */

                     /*** ProveRuleMenu ***/
  RestoreBottomForm ( bmotif_bottom_form_proof_tree_length );
#ifdef BTOOLKIT_FLAG
  HideTopWin ();
#endif

  curr_dialog_menu = dialog_form;
  curr_menu = prove_rule_menu;

  XtManageChild ( dialog_form );

  XtPopup ( prove_rule_dialog, XtGrabNone );
  XmUpdateDisplay ( prove_rule_dialog );
  XmUpdateDisplay ( top_level );

/*
printf ( " --->>> r %d  p %d  i %d  g %d  f %d\n", run_man_prf_r, run_man_prf_p, run_man_prf_i, run_man_prf_g, f );
DAVE_print_info_nod ( run_man_prf_i );
*/


/*
DAVE_dead_seq;
*/

/***
print_live_nodes ( "ProofMenu" );
***/

/***
print_tac_info("ProofMenu");
***/

}

int
NextProofStepWillBeAutoDischarged ()
{

  /***
  MUST AGREE with prfmch.c.motif "Automatically execute BINHYP EQL AND"
  ***/

  int rr;
  int f = frm_gol( run_man_prf_g );

  return ( 0 );

  rr = app_and_prf( run_man_prf_i,run_man_prf_g, f );
/***
if ( rr ) printf ( "\n  not redrawing proof tree - next step AND!\n" );
***/
  if ( ! rr ) {
     rr = app_hyp_prf( run_man_prf_p,run_man_prf_i,run_man_prf_g, f );
/***
if ( rr ) printf ( "\n  not redrawing proof tree - next step BINHYP!\n" );
***/
  }
  if ( ! rr ) {
    rr = app_eql_prf(run_man_prf_g,f);
/***
if ( rr ) printf ( "\n  not redrawing proof tree - next step EQL!\n" );
***/
  }
/***
if ( ! rr ) printf ( "\n  redrawing proof tree - next step not auto discharged\n" );
***/
  return ( rr );
}

void
DisplayMainTopWin ()
{
  int i, maxtot, tot;

  XmString xstr;

  Widget but, label_form;

  ClearTopWin ();

  lst_all_the;

  label_form = XtVaCreateWidget ( "Label", 
    xmFormWidgetClass,             TopWin_rc,
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

#ifndef BTOOLKIT_FLAG

  but = CreHighlightedButton ( TopWin_rc, "  1: bootX (9)",
              ( XtCallbackProc ) SelThy_CB,
              & c_arr [ 1 ] );

#endif

#ifdef BTOOLKIT_FLAG

  maxtot = 0;
  for ( util_str_i = first_btl_thy_to_display ; util_str_i <= last_btl_thy_to_display ; util_str_i++ ) {
    if ( nbr_rul_the ( util_str_i ) > maxtot ) maxtot = nbr_rul_the ( util_str_i );
  }

  strcpy ( buf, "  " );
  for ( util_str_i = 1 ; util_str_i <= max_btl_thy_len ; util_str_i++ )
    strcat ( buf, " " );
  if ( maxtot > 99 ) {
    strcat ( buf, "                tot   pob");
  }
  else if ( maxtot > 9 ) {
    strcat ( buf, "                tot   pob");
  }
  else {
    strcat ( buf, "               tot   pob");
  }

  xstr = XmStringCreateLtoR ( buf, charset );
  XtVaCreateManagedWidget ( "Label", 
    xmLabelWidgetClass,             TopWin_rc,
    XmNlabelString,                 xstr,
    XmNmarginWidth,                 30,
    XmNmarginHeight,                5,
    XmNtraversalOn,                 False,
    NULL );
  XmStringFree ( xstr );

  /*
  for ( util_str_i = first_btl_thy_to_display ; util_str_i <= last_btl_thy_to_display ; util_str_i++ ) {
    if ( nbr_rul_the ( util_str_i ) ) {
      write_pob_the ( util_str_i );
      but = CreHighlightedButton ( TopWin_rc, str_buf,
                ( XtCallbackProc ) SelThy_CB,
                & c_arr [ util_str_i ] );
    }
  }
  */

  for ( util_str_i = first_btl_thy_to_display ; util_str_i <= last_btl_thy_to_display ; util_str_i++ ) {
    tot = nbr_rul_the ( util_str_i );
    if ( tot != 0 ) {
      for ( i = 1 ; i <= tot; i = i + 50 ) {
        write_pob_the_range ( util_str_i, i, maxtot );
        but = CreHighlightedButtonUserData ( TopWin_rc, str_buf,
                ( XtCallbackProc ) SelThy_CB,
                  & c_arr [ util_str_i - first_btl_thy_to_display ],
                  ( i / 50 ) );
      }
      CreSmallPassiveButton ( TopWin_rc, "" );
    }
  }

#else

  for ( util_str_i = 2 ; util_str_i <= nbr_the ; util_str_i++ ) {
    write_the ( util_str_i );
    but = CreHighlightedButton ( TopWin_rc, str_buf,
              ( XtCallbackProc ) SelThy_CB,
              & c_arr [ util_str_i ] );
  }

#endif


}


#ifdef BTOOLKIT_FLAG

void
ModifySwitchBTPXDEDrule ()
{
  int f;

/***
strcpy ( str_buf, "\nModifySwitchBTPXDEDrule - " );
write_nam_the ( nbr_the );
printf ( "%s.%d\n", str_buf, nbr_rul_the ( nbr_the ) ); fflush ( stdout );
***/

  if ( nbr_rul_the ( nbr_the ) ) {
    switch ( btl_fwd_tac_depth ) {
    case 0:
        strcpy ( str_buf, SwitchBTPXDED0 );
      break;
    case 1:
        strcpy ( str_buf, SwitchBTPXDED1 );
      break;
    case 2:
        strcpy ( str_buf, SwitchBTPXDED2 );
      break;
    }

      f = read_frm_str_buf;
    if ( f != -999 ) {
      read_mod_rul_the ( nbr_the, nbr_rul_the ( nbr_the ), f );
    }
/***
sprintf ( str_buf, "btl_fwd_tac_depth=%d:\n    ", btl_fwd_tac_depth );
write_ver_rul_dave ( val_rul_the ( nbr_the, nbr_rul_the ( nbr_the ) ) );
printf ( "%s\n\n", str_buf ); fflush ( stdout );
***/      
  }
}


void
SetFwdLibTac ( t )
int t;
{
  register int f;
  FILE * BTPftac;
  int c, i;
  strcpy ( str_buf, "(ExpandHypX;PropertiesX;" );
  BTPftac = fopen ( "TMP/.BTPftac", "r" );
  if ( BTPftac != NULL ) {
    i = strlen ( str_buf );
    c = getc ( BTPftac );
    while ( ( c != EOF ) && ( c != '\n' ) ) {
      str_buf [ i++ ] = c;
      c = getc ( BTPftac );
    }
    fclose ( BTPftac );
    str_buf [ i ] = '\0';
   }
  strcat ( str_buf, ";FwdBToolUsersTheory;" );
  strcat ( str_buf, btl_fwd_tac [ btl_fwd_tac_depth ] );
  strcat ( str_buf, ")~" );
/***
printf ( "tactic 1\n%s\n", str_buf );
***/
  f = read_frm_str_buf;
  if ( f != -999 ) {
    mod_fwd_tac_the ( t, f );
  }
  else {
    sprintf ( buf, " Forward tactic %d does not parse ", btl_fwd_tac_depth );
    Popup_Info ( buf );
  }
  ModifySwitchBTPXDEDrule ();
}

#endif


void
DisplayATheoryTopWin ( t )
int t;
{
  XmString xstr;
  int tot_rul, i;
  char cur_thy_name [ 250 ];
  int first, last;

  Widget but, label_form, visible_thy_menu_rule_but = 0;

  ClearTopWin ();

  if ( ! t ) return;

  label_form = XtVaCreateWidget ( "Label", 
    xmFormWidgetClass,             TopWin_rc,
    NULL );

  str_buf [ 0 ] = '\0';
  write_nam_the ( t );
  strcpy ( cur_thy_name, str_buf );

  xstr = XmStringCreateLtoR ( str_buf, charset );
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

  tot_rul = nbr_rul_the ( t );

#ifdef BTOOLKIT_FLAG
  first = Get_thy_first_rule ( t );
  if   ( tot_rul > first + 49 ) last = first + 49;
  else                          last = tot_rul;
#else
  first = 1;
  last = tot_rul;
#endif

  for ( util_str_i = first ; util_str_i <= last ; util_str_i++ ) {
    str_buf [ 0 ] = '\0';

    i = GetProvedStatus ( val_rul_the ( t, util_str_i ) );

    if ( ( display_unproved_btl_flag ) || ( ! i ) ) {

      label_form = XtVaCreateWidget ( "Label", 
        xmFormWidgetClass,             TopWin_rc,
        NULL );

      sprintf ( buf, "%s.%d", cur_thy_name, util_str_i );
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

      xstr = XmStringCreateLtoR ( proved_label [ i ], charset );
      XtVaCreateManagedWidget ( proved_class [ i ], 
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

      write_ver_rul_dave ( val_rul_the ( t, util_str_i ) );
/*
strcat ( str_buf, "\n" );
*/
      but = CreHighlightedButton ( TopWin_rc, str_buf,
                ( XtCallbackProc ) SelRul_CB,
                & c_arr [ util_str_i ] );

      if ( visible_thy_menu_rule_num == util_str_i )
          visible_thy_menu_rule_but = but;

    } /* if ( ( display_unproved_btl_flag ) || ( ! i ) ) */

  }

  CrePassiveButton ( TopWin_rc, " " );

  if ( tot_rul == 0 ) {
    CrePassiveButton ( TopWin_rc, "   No rules\n" );
  }

#ifdef BTOOLKIT_FLAG

  SetFwdLibTac ( curr_thy );

#endif

  if( has_fwd_tac_the ( curr_thy )==TRUE ) {
    xstr = XmStringCreateLtoR ( "\nFORWARD TACTIC", charset );
    XtVaCreateManagedWidget ( "Label", 
      xmLabelWidgetClass,             TopWin_rc,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 20,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );
    XmStringFree ( xstr );

    str_buf [ 0 ] = '\0';
    reset_res(3);
    write_frm_res(fwd_tac_the ( curr_thy ),3);
    strcat ( str_buf, "\n" );
    xstr = XmStringCreateLtoR ( str_buf, charset );
    XtVaCreateManagedWidget ( "SelDialog", 
      xmLabelWidgetClass,             TopWin_rc,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 20,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );
    XmStringFree ( xstr );
/*
      writeln_fwd_tac_prf(fwd_tac_prf);
*/
    }

#ifndef BTOOLKIT_FLAG

    xstr = XmStringCreateLtoR ( "\nNORMAL TACTIC", charset );
    XtVaCreateManagedWidget ( "Label", 
      xmLabelWidgetClass,             TopWin_rc,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 20,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );
    XmStringFree ( xstr );

    str_buf [ 0 ] = '\0';
    reset_res(3);
    write_frm_res(tac_the ( curr_thy ),3);
    strcat ( str_buf, "\n" );
    xstr = XmStringCreateLtoR ( str_buf, charset );
    XtVaCreateManagedWidget ( "SelDialog", 
      xmLabelWidgetClass,             TopWin_rc,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 20,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );
    XmStringFree ( xstr );

#endif

    if ( visible_thy_menu_rule_but ) 
      XmScrollVisible ( TopWin_scroll, visible_thy_menu_rule_but, 0, 20 );
    XmUpdateDisplay ( TopWin_rc );
    XmUpdateDisplay ( TopWin_scroll );

}

XtCallbackProc
DisplayARuleTopWin_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
    if ( val_rec_sys==FALSE ) {
      if ( pvd_rul ( val_rul_the ( curr_thy, curr_rule ) ) == now_rul ) {
	Popup_Info ( "      Already proved!!           " );
      }
      else {
        void CreProofTreeDialog ();
        Dimension top_level_w;
        ClearTopWin ();
        XtVaGetValues ( top_level, XmNwidth, &top_level_w, NULL );
        PopdownCurrMenu ();
        str_buf [ 0 ] = '\0';
        write_nam_the ( curr_thy );
        strcat ( str_buf, "." );
        write_nat ( curr_rule );
        DisplayCurrWinText ( "\n  Proving " );
        if ( typ_rul (  val_rul_the ( curr_thy , curr_rule ) ) == lem_rul ) {
          DisplayCurrWinText ( "lemma " );
	}
        DisplayCurrWinText ( str_buf );
        
        CreProofTreeDialog ( 1 );
        do_prf ( curr_thy, curr_rule, TRUE );
      }
    }
    else {
      Popup_Info ( "      Impossible now!    " );
    }
}

void
DisplayARuleTopWin ( r )
int r;
{
  Widget but, label_form;
  XmString xstr;
  int tot_rul,i,t;

  ClearTopWin ();

  if ( ! r ) return;

  label_form = XtVaCreateWidget ( "Label", 
    xmFormWidgetClass,             TopWin_rc,
    NULL );

  str_buf [ 0 ] = '\0';
  write_nam_the ( curr_thy );
  strcat ( str_buf, "." );
  write_nat ( r );

  xstr = XmStringCreateLtoR ( str_buf, charset );
  but = XtVaCreateManagedWidget ( "Label", 
    xmLabelWidgetClass,             label_form,
    XmNlabelString,                 xstr,
    XmNmarginWidth,                 5,
    XmNmarginHeight,                5,
    XmNleftAttachment,              XmATTACH_FORM,
    XmNtraversalOn,                 False,
    NULL );
  XmStringFree ( xstr );

  i = GetProvedStatus ( val_rul_the ( curr_thy , r ) );

  xstr = XmStringCreateLtoR ( proved_label [ i ], charset );
  XtVaCreateManagedWidget ( proved_class [ i ], 
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

  str_buf [ 0 ] = '\0';
  write_ver_rul_dave ( val_rul_the ( curr_thy , r ) );
  strcat ( str_buf, "\n" );

  xstr = XmStringCreateLtoR ( str_buf, charset );
  but = XtVaCreateManagedWidget ( "SelDialog", 
      xmPushButtonGadgetClass,        TopWin_rc,
      XmNshadowThickness,             0,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 20,
      XmNmarginHeight,                5,
      XmNnavigationType,              XmTAB_GROUP,
      NULL );

  XtAddCallback ( but, XmNactivateCallback,
      ( XtCallbackProc ) DisplayARuleTopWin_CB,
      ( XtPointer ) NULL );
    
  XmStringFree ( xstr );

  if( has_fwd_tac_the ( curr_thy )==TRUE ) {
    xstr = XmStringCreateLtoR ( "\nFORWARD TACTIC", charset );
    XtVaCreateManagedWidget ( "Label", 
      xmLabelWidgetClass,             TopWin_rc,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 20,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );
    XmStringFree ( xstr );

    str_buf [ 0 ] = '\0';
    reset_res(6);
    write_frm_res(fwd_tac_the ( curr_thy ),6);
    strcat ( str_buf, "\n" );
    xstr = XmStringCreateLtoR ( str_buf, charset );
    XtVaCreateManagedWidget ( "SelDialog", 
      xmLabelWidgetClass,             TopWin_rc,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 20,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );

    XmStringFree ( xstr );
/*
      writeln_fwd_tac_prf(fwd_tac_prf);
*/
    }

#ifndef BTOOLKIT_FLAG

    xstr = XmStringCreateLtoR ( "\nNORMAL TACTIC", charset );
    XtVaCreateManagedWidget ( "Label", 
      xmLabelWidgetClass,             TopWin_rc,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 20,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );
    XmStringFree ( xstr );

    str_buf [ 0 ] = '\0';
    reset_res(6);
    write_frm_res(tac_the ( curr_thy ),6);
    strcat ( str_buf, "\n" );
    xstr = XmStringCreateLtoR ( str_buf, charset );
    XtVaCreateManagedWidget ( "SelDialog", 
      xmLabelWidgetClass,             TopWin_rc,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 20,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );
    XmStringFree ( xstr );

/*
    if( has_fwd_tac_the ( curr_thy ) == TRUE ) {
*/
      xstr = XmStringCreateLtoR ( "\nFORWARD PROOF QUOTA", charset );
      XtVaCreateManagedWidget ( "Label", 
        xmLabelWidgetClass,             TopWin_rc,
        XmNlabelString,                 xstr,
        XmNmarginWidth,                 20,
        XmNmarginHeight,                5,
        XmNtraversalOn,                 False,
        NULL );
      XmStringFree ( xstr );

      strcpy ( str_buf, "      " );
      write_nat(max_fwd_ctr_prf);
      strcat ( str_buf, "\n" );
      xstr = XmStringCreateLtoR ( str_buf, charset );
      XtVaCreateManagedWidget ( "SelDialog", 
        xmLabelWidgetClass,             TopWin_rc,
        XmNlabelString,                 xstr,
        XmNmarginWidth,                 20,
        XmNmarginHeight,                5,
        XmNtraversalOn,                 False,
        NULL );
      XmStringFree ( xstr );
/*
    }
*/

    xstr = XmStringCreateLtoR ( "\nNORMAL PROOF QUOTA", charset );
    XtVaCreateManagedWidget ( "Label", 
      xmLabelWidgetClass,             TopWin_rc,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 20,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );
    XmStringFree ( xstr );

    strcpy ( str_buf, "      " );
    write_nat(max_ctr_prf);
    strcat ( str_buf, "\n" );
    xstr = XmStringCreateLtoR ( str_buf, charset );
    XtVaCreateManagedWidget ( "SelDialog", 
      xmLabelWidgetClass,             TopWin_rc,
      XmNlabelString,                 xstr,
      XmNmarginWidth,                 20,
      XmNmarginHeight,                5,
      XmNtraversalOn,                 False,
      NULL );
    XmStringFree ( xstr );

#endif

}

void
CreProofTreeDialog ( flag )
int flag;
{
  static int proof_tree_is_up = 0;

  static int first_time = 1;

  char * textptr;
  Arg args [ 12 ];
  int n;

  GC gc;
  XGCValues gcv;

  if ( ! flag ) {
    if ( proof_tree_is_up ) {
      XtUnmanageChild ( proof_tree_dialog_form );
      XtDestroyWidget ( proof_tree_dialog_form );
      textptr = XmTextGetString ( main_text );
      XtDestroyWidget ( main_text );
      XtUnmanageChild ( bot_display_frame );
      XtDestroyWidget ( bot_display_frame );
      bot_display_frame = XtVaCreateWidget ( "DisplayArea", 
          xmFrameWidgetClass,             bottom_frame_form,
          XmNtopAttachment,               XmATTACH_FORM,
          XmNtopOffset,                   5,
          XmNleftAttachment,              XmATTACH_FORM,
          XmNleftOffset,                  5,
          XmNrightAttachment,             XmATTACH_FORM,
          XmNrightOffset,                 5,
          XmNbottomAttachment,            XmATTACH_FORM,
          XmNbottomOffset,                5,
          XmNshadowType,                  XmSHADOW_ETCHED_IN,
          XmNmarginWidth,                 10,
          XmNmarginHeight,                10,
          NULL );
      n = 0;
      XtSetArg ( args [ n ], XmNeditable,              False             );
      n++;
      XtSetArg ( args [ n ], XmNeditMode,              XmMULTI_LINE_EDIT );
      n++;
      XtSetArg ( args [ n ], XmNcursorPositionVisible, False             );
      n++;
      XtSetArg ( args [ n ], XmNscrollHorizontal,      False             );
      n++;
      XtSetArg ( args [ n ], XmNwordWrap,              True              );
      n++;
      XtSetArg ( args [ n ], XmNmarginWidth,           5                 );
      n++;
      XtSetArg ( args [ n ], XmNmarginHeight,          5                 );
      n++;
      XtSetArg ( args [ n ], XmNshadowThickness,       3                 );
      n++;
      main_text =
             XmCreateScrolledText ( bot_display_frame, "Canvas", args, n );
      XmTextSetString ( main_text, textptr );
      main_text_posn = strlen ( textptr );
      XmTextShowPosition ( main_text, main_text_posn );

      curr_text = main_text;
      curr_text_posn = main_text_posn;

      XtManageChild ( main_text );
      XtManageChild ( bot_display_frame );
      XmUpdateDisplay ( main_text );
      XmUpdateDisplay ( bot_display_frame );
      XtFree ( textptr );
    }
    last_node = -1;
    proof_tree_is_up = 0;
    return;
  }

  XtUnmanageChild ( main_text );

  proof_tree_is_up = 1;

    proof_tree_dialog_form = XtVaCreateWidget ( "ProofTree",
        xmFormWidgetClass,         bot_display_frame,
        XmNmarginWidth,            5,
        XmNmarginHeight,           5,
        XmNshadowThickness,        3,
        XmNresizeHeight,           True,
        XmNresizeWidth,            True,
        NULL );

    proof_tree_scroll = XtVaCreateWidget ( "ProofTree",
        xmScrolledWindowWidgetClass,    proof_tree_dialog_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   5,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 5,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  5,
        XmNbottomAttachment,            XmATTACH_FORM,
        XmNbottomOffset,                5,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNspacing,                     0,
        NULL );

    proof_tree_scroll_form = XtVaCreateWidget ( "ProofTree",
        xmFormWidgetClass,         proof_tree_scroll,
        XmNdefaultPosition,        False,  
        NULL );

  XtManageChild ( proof_tree_scroll_form );
  XtManageChild ( proof_tree_dialog_form );
  XtManageChild ( proof_tree_scroll );

  XmUpdateDisplay ( proof_tree_scroll_form );
  XmUpdateDisplay ( proof_tree_dialog_form );
  XmUpdateDisplay ( proof_tree_scroll );

/*
  if ( first_time ) {

    first_time = 0;
*/

  /*
      gc = XCreateGC ( display,
	         ( Drawable ) RootWindowOfScreen ( proof_screen ),
	         ( unsigned long ) GCForeground,
                 &gcv );
      if ( ( gc == BadAlloc  ) ||
           ( gc == BadFont   ) ||
           ( gc == BadGC     ) ||
           ( gc == BadMatch  ) ||
           ( gc == BadPixmap ) ||
           ( gc == BadValue  )    ) {
      sprintf ( buf, "\n  Bad return (%d) from XCreateGC\n", ( int ) gc );
      DisplayCurrWinText ( buf );
  */

      if ( ! ( gc = XCreateGC ( display,
	         ( Drawable ) RootWindowOfScreen ( proof_screen ),
	         ( unsigned long ) GCForeground,
				&gcv ) ) ) {
        DisplayCurrWinText ( "\n  Bad return from XCreateGC\n" );
        Popup_Info ( "  Can't create gc  " );
        return;
      }

    /*    XSetForeground ( display, gc, ( unsigned long ) 0 ); */

    XSetForeground ( display, gc, BlackPixelOfScreen ( proof_screen ) );

/*
    h_pixmap = XCreatePixmap ( display,
                 RootWindowOfScreen ( proof_screen ),
                 ( unsigned int ) ( proof_horiz_offset / 2 ) + 1,
                 ( unsigned int ) 1,
	         ( unsigned int ) DefaultDepthOfScreen ( proof_screen ) );
    if ( ( h_pixmap == BadAlloc    ) ||
         ( h_pixmap == BadDrawable ) ||
         ( h_pixmap == BadValue    )    ) {
      sprintf ( buf, "\n  Bad return (%d) from XCreatePixmap\n",
                                                            ( int ) h_pixmap );
      DisplayCurrWinText ( buf );
*/

    if ( ! ( h_pixmap = XCreatePixmap ( display,
                 RootWindowOfScreen ( proof_screen ),
                 ( unsigned int ) ( proof_horiz_offset / 2 ) + 1,
                 ( unsigned int ) 1,
					( unsigned int ) DefaultDepthOfScreen ( proof_screen ) ) ) ) {
      DisplayCurrWinText ( "\n  Bad return from XCreatePixmap ( 1 )\n" );
      Popup_Info ( "  Can't create h_pixmap  " );
      return;
    }

/*
    sv_pixmap = XCreatePixmap ( display,
                 RootWindowOfScreen ( proof_screen ),
                 ( unsigned int ) 1,
                 ( unsigned int ) proof_vert_offset - half_proof_goal_height - goal_rule_vert_diff + 1,
	         ( unsigned int ) DefaultDepthOfScreen ( proof_screen ) );
    if ( ( sv_pixmap == BadAlloc    ) ||
         ( sv_pixmap == BadDrawable ) ||
         ( sv_pixmap == BadValue    )    ) {
      sprintf ( buf, "\n  Bad return (%d) from XCreatePixmap\n",
                                                            ( int ) sv_pixmap );
      DisplayCurrWinText ( buf );
*/

    if ( ! ( sv_pixmap = XCreatePixmap ( display,
                 RootWindowOfScreen ( proof_screen ),
                 ( unsigned int ) 1,
                 ( unsigned int ) proof_vert_offset - half_proof_goal_height - goal_rule_vert_diff + 1,
		 ( unsigned int ) DefaultDepthOfScreen ( proof_screen ) ) ) ) {
      DisplayCurrWinText ( "\n  Bad return from XCreatePixmap ( 2 )\n" );
      Popup_Info ( "  Can't create sv_pixmap  " );
      return;
    }

/*
    lv_pixmap = XCreatePixmap ( display,
                 RootWindowOfScreen ( proof_screen ),
                 ( unsigned int ) 1,
                 ( unsigned int ) proof_vert_offset + 1,
	         ( unsigned int ) DefaultDepthOfScreen ( proof_screen ) );
    if ( ( lv_pixmap == BadAlloc    ) ||
         ( lv_pixmap == BadDrawable ) ||
         ( lv_pixmap == BadValue    )    ) {
      sprintf ( buf, "\n  Bad return (%d) from XCreatePixmap\n",
                                                            ( int ) lv_pixmap );
      DisplayCurrWinText ( buf );
*/

    if ( ! ( lv_pixmap = XCreatePixmap ( display,
                 RootWindowOfScreen ( proof_screen ),
                 ( unsigned int ) 1,
                 ( unsigned int ) proof_vert_offset + 1,
		 ( unsigned int ) DefaultDepthOfScreen ( proof_screen ) ) ) ) {
      DisplayCurrWinText ( "\n  Bad return from XCreatePixmap ( 3 )\n" );
      Popup_Info ( "  Can't create lv_pixmap  " );
      return;
    }

    XDrawLine ( display, h_pixmap, gc,
                ( int ) 0, ( int ) 0,
                ( int ) ( proof_horiz_offset / 2 ), ( int ) 0 );

    XDrawLine ( display, sv_pixmap, gc,
                ( int ) 0, ( int ) 0,
                ( int ) 0, ( int ) proof_vert_offset - half_proof_goal_height );

    XDrawLine ( display, lv_pixmap, gc,
                ( int ) 0, ( int ) 0,
                ( int ) 0, ( int ) proof_vert_offset );
/*
  }
*/

}

void
Append_rul_hyp ( h )
int h;
{
/* #define Append_rul_hyp_tab 48 */
#define Append_rul_hyp_tab 80

  int r, t;
  if ( def_rul_hyp ( h ) ) {
    t = strlen ( str_buf );
    r = t;
    while ( r && ( str_buf [ r ] != '\n' ) ) { r--; }
    r = t - r;
    while ( r < Append_rul_hyp_tab ) {
      strcat ( str_buf, " " );
      r++;
    }
    strcat ( str_buf, "  " );
    r = rul_hyp( h );
    if ( r == 1 ) {                /* ARI ! */
      strcat ( str_buf, "(ARI)" );
    }
    else if ( r == 2 ) {           /* SUB ! */
      strcat ( str_buf, "(SUB)" );
    }
    else {
      strcat ( str_buf, "(");
      write_nam_the(the_rul(r));
      strcat ( str_buf, ".");
      write_nat(num_rul(r));
      strcat ( str_buf, ")");
    }
  }
}


XtCallbackProc
DisplayProofNode_CB ()
{
  CreProofTreeDialog ( 0 );
}

XtCallbackProc
ProofNode_Goal_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  Widget w;
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;
  if ( cbs->reason == XmCR_PROTOCOLS )
    w = ( Widget ) client_data;
  else
    w = XtParent ( XtParent ( widget ) );
  XtPopdown ( w );
  XtDestroyWidget ( w );
}

XtCallbackProc
PositionSearchedHyp_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  Position parent_x, parent_y;
  Dimension parent_h, widget_h;

  XtVaGetValues ( ( Widget ) client_data,
      XmNx,       & parent_x,
      XmNy,       & parent_y,
      XmNheight,  & parent_h,
      NULL);

  XtVaGetValues ( widget,
      XmNheight,  & widget_h,
      NULL);

  XtVaSetValues ( widget,
      XmNx,       parent_x + 5,
      XmNy,       parent_y + parent_h - widget_h - 15,
      NULL);
}

XtCallbackProc
Hyp_Search_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  Widget dialog, dialog_main_form, dialog_scroll,
         search_label,
         dialog_label_frame, dialog_label, dialog_text, but;
  register int s,i,j,h,dec,b,v,nsc;
  char * search_text;
  int node =  * ( int * ) client_data;
  XmString xstr;
  XmTextPosition curr_posn;

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

  strcpy ( hyp_search_string, search_text );
  XtFree ( search_text );

  strcpy ( str_buf, "Goal: " );
  write_gol_prf_no_nl ( info_nod ( node ) );

#define truncated_goal_length 100
  /*** truncate goal (also used below) ***/

  str_buf [ truncated_goal_length - 5 ] = ' ';
  str_buf [ truncated_goal_length - 4 ] = '.';
  str_buf [ truncated_goal_length - 3 ] = '.';
  str_buf [ truncated_goal_length - 2 ] = '.';
  str_buf [ truncated_goal_length - 1 ] = ' ';
  str_buf [ truncated_goal_length ] = '\0';

  dialog = XmCreateDialogShell ( top_frame_form, "Hyp", NULL, 0 );
  XtAddCallback ( dialog, XmNpopupCallback,
      ( XtCallbackProc ) PositionSearchedHyp_CB,
      ( XtPointer ) XtParent ( widget ) );
  XmAddWMProtocolCallback ( dialog, WM_DELETE_WINDOW,
      ( XtCallbackProc ) ProofNode_Goal_CB,
      ( XtPointer ) dialog );
  dialog_main_form = XtVaCreateWidget ( "Hyp",
      xmFormWidgetClass,         dialog,
      XmNdefaultPosition,        False,  
      NULL );
  dialog_label_frame = XtVaCreateWidget ( "Label",
        xmFrameWidgetClass,        dialog_main_form,
        XmNshadowType,             XmSHADOW_ETCHED_OUT,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_FORM,
        XmNleftOffset,             10,
        XmNrightOffset,            5,
        XmNtraversalOn,            False,
        NULL );
  xstr = XmStringCreateLtoR ( str_buf, charset );
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
      XmNwidth,                       /* 550, */ 750,
      XmNheight,                      255,
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNspacing,                     0,
      XmNtopAttachment,               XmATTACH_WIDGET,
      XmNtopWidget,                   search_label,
      XmNtopOffset,                   1,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNbottomOffset,                54,
      XmNtraversalOn,                 False,
      NULL );
  dialog_text = XtVaCreateWidget ( "Hyp", 
        xmTextWidgetClass,         dialog_scroll,
        XmNcursorPositionVisible,  False,
        XmNeditable,               False,
        XmNeditMode,               XmMULTI_LINE_EDIT,
        XmNresizeHeight,           True,
        XmNresizeWidth,            True,
        XmNmarginWidth,            5,
        XmNmarginHeight,           0,
        XmNborderWidth,            0,
        XmNshadowThickness,        0,
        NULL );
  s=cre(100);
  lst_hyp_prf(run_man_prf_p,node,s);
  rev(s);
  nsc=0;
  str_buf [ 0 ] = '\0';
  save_MAX_COL_RES;
  mod_MAX_COL_RES(999999);
  xst(s,i,h,(
        (val_root_frm(frm_hyp(h))==BVRB_sym) || (val_root_frm(frm_hyp(h))==ANTI_SLASH_sym)),b=TRUE,b=FALSE);
  if( b==TRUE ){
    itr(s,i,h,{
          v=val_root_frm(frm_hyp(h));
          if( (v==ANTI_SLASH_sym) || (v==BVRB_sym) ){
            reset_res(0);
            write_frm_res(frm_hyp(h),0);
            strcat ( str_buf, "\n" );
            nsc=nsc+1;
          }
       ;});
  }
  if( len(s)>nsc ){
    b=TRUE;
    itr(s,i,h,{
          v=val_root_frm(frm_hyp(h));
          if( (v==ANTI_SLASH_sym) || (v==BVRB_sym) ){
            {};
          } else if( (isa_der_hyp(h)==TRUE) && (sho_der_hyp_prf==TRUE) ){
            reset_res(4);
            write_frm_res(frm_hyp(h),4);
            strcat ( str_buf, "\n" );
          } else {
            b=TRUE;
            reset_res(0);
            write_frm_res(frm_hyp(h),0);
            strcat ( str_buf, "\n" );
          }
       ;});
  }
  kil(s);
  restore_MAX_COL_RES;
  XmTextSetString ( dialog_text, "" );
  XmTextInsert ( dialog_text, curr_posn, "\n" );
  curr_posn = 1;
  i = 0;
  while ( str_buf [ i ] != '\0' ) {
    j = 0;
    while ( str_buf [ i ] == ' ' ) i++;
    while ( ( str_buf [ i ] != '\n' ) &&  ( str_buf [ i ] != '\0' ) ) {
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
  if ( curr_posn == 1 ) XmTextSetString ( dialog_text, "No match" );
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
      ( XtCallbackProc ) ProofNode_Goal_CB,
      ( XtPointer ) NULL );

  XtRealizeWidget ( dialog );
  XtManageChild (  dialog_label );
  XtManageChild (  dialog_label_frame );
  XtManageChild (  dialog_text );
  XtManageChild (  dialog_scroll );
  XtManageChild (  dialog_main_form );
  XtPopup ( dialog, XtGrabNone );
  XmUpdateDisplay (  dialog );
}

XtCallbackProc
PositionHyp_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  Position top_level_x, top_level_y;
  Position widget_x, widget_y, parent_x, parent_y;
  Dimension top_level_w, top_frame_form_h, parent_w, parent_h, widget_w, widget_h;

  XtVaGetValues ( top_level,
      XmNx,       & top_level_x,
      XmNy,       & top_level_y,
      NULL );

  XtVaGetValues ( top_frame_form,
      XmNheight,  & top_frame_form_h,
      NULL );

  XtVaGetValues ( XtParent ( ( Widget ) client_data ),
      XmNx,       & parent_x,
      XmNy,       & parent_y,
      XmNwidth,   & parent_w,
      XmNheight,  & parent_h,
      NULL);

  XtVaGetValues ( widget,
      XmNwidth,   & widget_w,
      XmNheight,  & widget_h,
      NULL );

/***
printf ( "top_level_x %d top_level_y %d\ntop_frame_form_h %d\nparent_x %d parent_y %d parent_w %d parent_h %d\nwidget_w %d widget_h %d\n",top_level_x, top_level_y, top_frame_form_h, parent_x, parent_y, parent_w, parent_h, widget_w, widget_h );
***/

  widget_x = top_level_x + parent_x + parent_w + 25;
  if ( widget_x < 1 ) widget_x = 10;
  if ( widget_x + widget_w >= WidthOfScreen ( proof_screen ) )
    widget_x = WidthOfScreen ( proof_screen ) - widget_w;

  widget_y = top_level_y + parent_y + top_frame_form_h -10 + 
                                             ( parent_h / 2 ) - ( widget_h / 2 );
  if ( widget_y < 1 ) widget_y = 10;
  if ( widget_y + widget_h >= HeightOfScreen ( proof_screen ) )
    widget_y = HeightOfScreen ( proof_screen ) - widget_h;

  XtVaSetValues ( widget,
      XmNx,       widget_x,
      XmNy,       widget_y,
      NULL);
}

XtCallbackProc
ProofNode_Goal ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  Widget dialog, dialog_main_form, dialog_scroll,
         search_label, search_text,
         dialog_label_frame, dialog_label, dialog_text, but;
  register int s,i,j,h,b,v,nsc,num_hyp, r;
  int node =  * ( int * ) client_data;
  int nn;
  XmString xstr;

  Atom   WM_DELETE_WINDOW;

  WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

  strcpy ( str_buf, "Goal: " );

  node = GetLookUpNode ( node );

  write_gol_prf_no_nl ( info_nod ( node ) );
  /*** truncate goal ***/
  str_buf [ truncated_goal_length - 5 ] = ' ';
  str_buf [ truncated_goal_length - 4 ] = '.';
  str_buf [ truncated_goal_length - 3 ] = '.';
  str_buf [ truncated_goal_length - 2 ] = '.';
  str_buf [ truncated_goal_length - 1 ] = ' ';
  str_buf [ truncated_goal_length ] = '\0';

  dialog = XmCreateDialogShell ( top_frame_form, "Hyp", NULL, 0 );
  XtAddCallback ( dialog, XmNpopupCallback,
      ( XtCallbackProc ) PositionHyp_CB,
      ( XtPointer ) XtParent ( widget ) );
  XmAddWMProtocolCallback ( dialog, WM_DELETE_WINDOW,
      ( XtCallbackProc ) ProofNode_Goal_CB,
      ( XtPointer ) dialog );
  dialog_main_form = XtVaCreateWidget ( "Hyp", 
      xmFormWidgetClass,         dialog,
      XmNdefaultPosition,        False,  
      NULL );
  dialog_label_frame = XtVaCreateWidget ( "Label",
        xmFrameWidgetClass,        dialog_main_form,
        XmNshadowType,             XmSHADOW_ETCHED_OUT,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_FORM,
        XmNleftOffset,             10,
        XmNrightOffset,            5,
        XmNtraversalOn,            False,
        NULL );
  xstr = XmStringCreateLtoR ( str_buf, charset );
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
     ( XtCallbackProc ) Hyp_Search_CB,
     ( XtPointer ) & c_arr [ node ] );
  
  dialog_scroll =  XtVaCreateWidget ( "Hyp",
      xmScrolledWindowWidgetClass,    dialog_main_form,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNwidth,                       /* 550, */ 750,
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
  dialog_text = XtVaCreateWidget ( "Hyp", 
        xmTextWidgetClass,         dialog_scroll,
        XmNcursorPositionVisible,  False,
        XmNeditable,               False,
        XmNeditMode,               XmMULTI_LINE_EDIT,
        XmNresizeHeight,           True,
        XmNresizeWidth,            True,
        XmNmarginWidth,            5,
        XmNmarginHeight,           0,
        XmNborderWidth,            0,
        XmNshadowThickness,        0,
        NULL );
  s=cre(100);
/***
printf ( "lst_hyp_prf - run_man_prf_p %d   node %d\n", run_man_prf_p,node );
***/
  lst_hyp_prf(run_man_prf_p,node,s);
  num_hyp = len ( s );
/***
printf ( "len ( %d ): %d\n", s, num_hyp );
***/
  rev(s);
/***
printf ( "len ( %d ): %d\n", s, num_hyp );
***/
  nsc=0;
  str_buf [ 0 ] = '\0';
  save_MAX_COL_RES;
  mod_MAX_COL_RES(999999);
  xst(s,i,h,(
        (val_root_frm(frm_hyp(h))==BVRB_sym) || (val_root_frm(frm_hyp(h))==ANTI_SLASH_sym)),b=TRUE,b=FALSE);
  if( b==TRUE ){
    itr(s,i,h,{
          v=val_root_frm(frm_hyp(h));
          if( (v==ANTI_SLASH_sym) || (v==BVRB_sym) ){
            reset_res(0);
            write_frm_res(frm_hyp(h),0);
            Append_rul_hyp ( h );
            strcat ( str_buf, "\n" );
            nsc=nsc+1;
          }
       ;});
  }
  if( len(s)>nsc ){
    b=TRUE;
    itr(s,i,h,{
          v=val_root_frm(frm_hyp(h));
          if( (v==ANTI_SLASH_sym) || (v==BVRB_sym) ){
            {};
          } else if( (isa_der_hyp(h)==TRUE) && (sho_der_hyp_prf==TRUE) ){
            reset_res(4);
            write_frm_res(frm_hyp(h),4);
            Append_rul_hyp ( h );
            strcat ( str_buf, "\n" );
          } else {
            b=TRUE;
            reset_res(0);
            write_frm_res(frm_hyp(h),0);
            Append_rul_hyp ( h );
            strcat ( str_buf, "\n" );
          }
       ;});
  }
  if   ( num_hyp ) {
    XmTextSetString ( dialog_text, str_buf );
  }
  else {
    XmTextSetString ( dialog_text, "\n    No hypotheses\n" );
    XtVaSetValues ( dialog_scroll,
      XmNheight,                      150,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   50,
      NULL);
    XtUnmanageChild ( search_label );
    XtUnmanageChild ( search_text );
  }
  kil(s);
  restore_MAX_COL_RES;
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
      ( XtCallbackProc ) ProofNode_Goal_CB,
      ( XtPointer ) NULL );

  XtRealizeWidget ( dialog );
  XtManageChild (  dialog_label );
  XtManageChild (  dialog_label_frame );
  XtManageChild (  dialog_text );
  XtManageChild (  dialog_scroll );
  XtManageChild (  dialog_main_form );
  XtPopup ( dialog, XtGrabNone );
  if   ( num_hyp ) {
    XmProcessTraversal ( search_text, XmTRAVERSE_CURRENT );
  }
  XmUpdateDisplay (  dialog );

}

int
nl_in_str_buf ()
{
  int i, n;
  i = 0;
  n = 0;
  while ( str_buf [ i ] != '\0' ) {
    if ( str_buf [ i ] == '\n' ) n++;
    i++;
  }
  return ( n );
}

void
DisplayProofNode ( node, curr_node, goal, nx, ny, son_num, goals_as_push_but )
int node, curr_node, goal, nx, ny, son_num, goals_as_push_but;
{

  /***
  node = -999 => this is the final node to be displayed
  nx = 0      => this is the original goal
  ***/

  static int extra_lines;
  int num_imp;
  XmString xstr, xstr1;
  Dimension x_pos = proof_ini_horiz + ( nx * proof_horiz_offset );
  Dimension y_pos = proof_ini_vert + ( ny * proof_vert_offset ) + proof_header_height;
  Widget header_frame, frame, rc, H, but;
  int i, j, k;
  char goal_str [ 15 ];

#ifndef BTOOLKIT_FLAG
char additional_string [ 2500 ];
#endif

  if ( ( nx == 0 ) && ( ny == 0 ) ) {

/***
printf ( "  setting extra_lines to 0\n" );
***/

    extra_lines = 0;
    XtVaCreateManagedWidget ( "ProofTree",
        xmLabelWidgetClass,         proof_tree_scroll_form,
        XmNlabelType,               XmPIXMAP,
        XmNlabelPixmap,             B_framed_pixmap_gray94,
        XmNshadowThickness,         0,
        XmNmarginWidth,             0,
        XmNmarginHeight,            0,
        XmNx,                       proof_ini_horiz + 2,  
        XmNy,                       proof_ini_vert,  
        XmNtraversalOn,             False,
        NULL );
    header_frame = XtVaCreateManagedWidget ( "ProofTree",
        xmFrameWidgetClass,         proof_tree_scroll_form,
        XmNx,                       50,  
        XmNy,                       proof_ini_vert + 1,  
        XmNshadowType,              XmSHADOW_ETCHED_OUT,
        NULL );
    strcpy ( str_buf , "Proof Tree for " );
    write_nam_the ( curr_thy );
    strcat ( str_buf, "." );
    write_nat ( curr_rule );
    xstr = XmStringCreateLtoR ( str_buf, charset );
    XtVaCreateManagedWidget ( "Label", 
        xmLabelWidgetClass,        header_frame,
        XmNshadowThickness,        0,
        XmNlabelString,            xstr,
        XmNdefaultButtonShadowThickness,        0,
        XmNhighlightThickness,     0,
        XmNmarginWidth,            5,
        XmNmarginHeight,           2,
        XmNtraversalOn,            False,
       NULL );
    XmStringFree ( xstr );
  }

  y_pos = y_pos + ( extra_lines * proof_extra_lines_offset );

  str_buf [ 0 ] = '\0';

  if ( ( def_rul_gol ( goal ) ) && ( ! ( def_spe_gol ( goal ) ) ) ) {
    write_nam_the ( the_rul ( rul_gol ( goal ) ) );
    strcat ( str_buf, "." );
    CreNumInBuf ( str_buf, num_rul ( rul_gol ( goal ) ) );
  }
  else if ( def_spe_gol ( goal ) ) {
    if ( spe_gol ( goal ) == HYP_gol ) {
      strcpy ( str_buf, "HYP: " );
      write_frm_res(frm_hyp(hyp_gol(goal)),0);
      repl_nl_sp_str_buf ();
    }
    else {
      write_spe_gol ( spe_gol ( goal ) );

#ifdef BTOOLKIT_FLAG

      if ( spe_gol ( goal ) == LEM_gol ) {
        strcat ( str_buf, "MA" );
        strcat ( str_buf, " (" );
        write_nam_the ( the_rul ( rul_gol ( goal ) ) );
        strcat ( str_buf, "." );
        CreNumInBuf ( str_buf, num_rul ( rul_gol ( goal ) ) );
        strcat ( str_buf, ")" );
      }

#endif

    }
  }
  else if ( def_hyp_gol( goal ) ) {
    if ( val_root_frm ( frm_hyp ( hyp_gol ( goal ) ) ) == FAL_sym ) {
      strcpy ( str_buf, "CONTRA" );
    } else {
      strcpy ( str_buf, "INHYP" );
    }
  }
  else if ( is_frm_gol ( goal ) ) {
    int op = val_root_frm ( frm_gol ( goal ) );
    if( ( op == BCRER_sym ) ) {
      strcpy ( str_buf, "RULE" );
    } else if ( (op == BCREL_sym) ) {
      strcpy ( str_buf, "LEMMA" );
    } else if ( op == BPOP_sym ) {
      strcpy ( str_buf, "RULE" );
    } else if ( op == BCLEAN_sym ) {
      strcpy ( str_buf, "RULE" );
    } else if ( op == CLO_sym ) {
      strcpy ( str_buf, "CLOSE" );
    } else if ( op == BCRELR_sym ) {
      strcpy ( str_buf, "RULE" );
    } else if ( op == MODR_sym ) {
      strcpy ( str_buf, "MODR" );
    } else if ( op == MARK_sym ) {
      strcpy ( str_buf, "RULE" );
    } else if ( op == SHL_sym ) {
      strcpy ( str_buf, "SHELL" );
    } else if ( op == WRIF_sym ) {
      strcpy ( str_buf, "WRITE" );
    } else if ( op == WRIM_sym ) {
      strcpy ( str_buf, "WRITE" );
    } else if ( op == PRIF_sym ) {
      strcpy ( str_buf, "WRITE" );
    } else if ( op == BTAC_sym ) {
      strcpy ( str_buf, "TACTIC" );
    } else if ( op == FTAC_sym ) {
      strcpy ( str_buf, "TACTIC" );
    } else if ( op == BRECOMPACT_sym ) {
      strcpy ( str_buf, "RECOMPACT" );
    } else if ( op == BSTATISTICS_sym ) {
      strcpy ( str_buf, "STATISTICS" );
    }
  }

  strcpy ( buf, str_buf );  /* buf = "" => no justification to be printed */

  strcpy ( str_buf, " " );
  /* str_buf [ 0 ] = '\0'; */
  /* write_gol_prf_no_nl ( goal ); */

  if ( nx == 0 ) /* the original goal */
    num_imp = write_frm_first_prooftree_goal ( frm_gol ( goal ) ); /* resmch */
  else
    num_imp = write_frm_non_first_prooftree_goal ( frm_gol ( goal ) ); /* resmch */

  num_imp = nl_in_str_buf ();

#ifdef BTOOLKIT_FLAG

/***
printf ( "\n*** DisplayProofNode this node=%d end node=%d goal=%d nx=%d ny=%d son_num=%d\n    extra_lines=%d num_imp=%d    loop_do_prf_i=%d info_nod(loop_do_prf_i)=%d\n    goals_as_push_but=%d\n   %s\n", node, curr_node, goal, nx, ny, son_num ,extra_lines, num_imp, loop_do_prf_i, info_nod(loop_do_prf_i), goals_as_push_but, str_buf  );
***/

#endif

#ifdef BTOOLKIT_FLAG

  if ( node == curr_node ) {
    if ( ( last_goal_displayed_frm != -999 ) && ( last_goal_displayed_frm ) ) {
/***
printf ( "motif.c: kil ( last_goal_displayed_frm )\n" );
***/
      kil ( last_goal_displayed_frm );
    }
    last_goal_displayed_frm = read_frm_str_buf;
/***
printf ( "motif.c: setting last_goal_displayed_frm\n" );
***/
  }
#endif /* BTOOLKIT_FLAG */


  xstr = XmStringCreateLtoR ( str_buf, charset );

  if ( buf [ 0 ] == '\0' ) {    /* no justification */
    if ( node == curr_node ) {
      strcpy ( goal_str, "CurrentGoal" );
      frame = XtVaCreateManagedWidget ( goal_str, 
          xmFrameWidgetClass,        proof_tree_scroll_form,
          XmNx,                      x_pos + 2,  
          XmNy,                      y_pos,  
          XmNshadowType,             XmSHADOW_ETCHED_IN,
          NULL );
      rc = XtVaCreateManagedWidget ( goal_str,
          xmRowColumnWidgetClass,    frame,
          XmNorientation,            XmHORIZONTAL,
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          XmNspacing,                0,
          XmNisHomogeneous,          False,
          NULL );
      if ( ( nx ) && ( node != 999 ) ) {    /* not the original goal, or `Click' */
        sprintf ( additional_string, " H%d ", nx );
        xstr1 = XmStringCreateLtoR ( " H ", charset );
        H = XtVaCreateManagedWidget ( goal_str,
            xmPushButtonWidgetClass,   rc,
            XmNshadowThickness,        0,
            XmNlabelString,            xstr1,
            XmNmarginWidth,            2,
            XmNmarginHeight,           2,
            XmNdefaultButtonShadowThickness,        0,
            XmNhighlightThickness,     0,
            NULL );
        XmStringFree ( xstr1 );
        XtAddCallback ( H, XmNactivateCallback,
            ( XtCallbackProc ) ProofNode_Goal,
            ( XtPointer ) & c_arr [ node ] );
        xstr1 = XmStringCreateLtoR ( "|-", charset );
        XtVaCreateManagedWidget ( goal_str,
            xmLabelWidgetClass,        rc,
            XmNshadowThickness,        0,
            XmNlabelString,            xstr1,
            XmNmarginWidth,            2,
            XmNmarginHeight,           2,
            XmNdefaultButtonShadowThickness,        0,
            XmNhighlightThickness,     0,
            NULL );
        XmStringFree ( xstr1 );
      }
      but = XtVaCreateManagedWidget ( goal_str, 
          xmPushButtonWidgetClass,   rc,
          XmNshadowThickness,        0,
          XmNlabelString,            xstr,
          XmNmarginWidth,            2,
          XmNmarginHeight,           2,
          XmNdefaultButtonShadowThickness,        0,
          XmNhighlightThickness,     0,
          NULL );
      XtAddCallback ( but, XmNactivateCallback,
          ( XtCallbackProc ) Pre_FormattedGoal_CB,
          ( XtPointer ) & c_arr [ goal ] );
      visible_scroll = frame;
    }
    else {        /* if ( node == curr_node ) */
      strcpy ( goal_str, "UndischGoal" );
      rc = XtVaCreateManagedWidget ( goal_str,
          xmRowColumnWidgetClass,    proof_tree_scroll_form,
          XmNorientation,            XmHORIZONTAL,
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          XmNspacing,                0,
          XmNisHomogeneous,          False,
          XmNx,                      x_pos + 2,  
          XmNy,                      y_pos,  
          NULL );
      if ( ( nx ) && ( node != 999 ) ) {   /* not the original goal, or `Click' */
        sprintf ( additional_string, " H%d ", nx );
        xstr1 = XmStringCreateLtoR ( " H ", charset );
        H = XtVaCreateManagedWidget ( goal_str,
            xmPushButtonWidgetClass,   rc,
            XmNshadowThickness,        0,
            XmNlabelString,            xstr1,
            XmNmarginWidth,            2,
            XmNmarginHeight,           2,
            XmNdefaultButtonShadowThickness,        0,
            XmNhighlightThickness,     0,
            NULL );
        XmStringFree ( xstr1 );
        XtAddCallback ( H, XmNactivateCallback,
            ( XtCallbackProc ) ProofNode_Goal,
            ( XtPointer ) & c_arr [ node ] );
        xstr1 = XmStringCreateLtoR ( "|-", charset );
        XtVaCreateManagedWidget ( goal_str,
            xmLabelWidgetClass,        rc,
            XmNshadowThickness,        0,
            XmNlabelString,            xstr1,
            XmNmarginWidth,            2,
            XmNmarginHeight,           2,
            XmNdefaultButtonShadowThickness,        0,
            XmNhighlightThickness,     0,
            NULL );
        XmStringFree ( xstr1 );
      }
      but = XtVaCreateManagedWidget ( goal_str, 
          xmPushButtonWidgetClass,   rc,
          XmNshadowThickness,        0,
          XmNlabelString,            xstr,
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          XmNdefaultButtonShadowThickness,        0,
          XmNhighlightThickness,     0,
         NULL );
      XtAddCallback ( but, XmNactivateCallback,
          ( XtCallbackProc ) Pre_FormattedGoal_CB,
          ( XtPointer ) & c_arr [ goal ] );
    }
  }
  else {    /* if ( buf [ 0 ] == '\0' ) {  so justification to be printed */
    strcpy ( goal_str, "DischGoal" );
    rc = XtVaCreateManagedWidget ( goal_str,
        xmRowColumnWidgetClass,    proof_tree_scroll_form,
        XmNorientation,            XmHORIZONTAL,
        XmNmarginWidth,            0,
        XmNmarginHeight,           0,
        XmNspacing,                0,
        XmNisHomogeneous,          False,
        XmNx,                      x_pos + 2,  
        XmNy,                      y_pos,  
        NULL );
    if ( goals_as_push_but ) {
      if ( ( nx ) && ( node != 999 ) ) {   /* not the original goal, or `Click' */
        sprintf ( additional_string, " H%d ", nx );
        xstr1 = XmStringCreateLtoR ( " H ", charset );
        H = XtVaCreateManagedWidget ( goal_str,
            xmPushButtonWidgetClass,   rc,
            XmNshadowThickness,        0,
            XmNlabelString,            xstr1,
            XmNmarginWidth,            2,
            XmNmarginHeight,           2,
            XmNdefaultButtonShadowThickness,        0,
            XmNhighlightThickness,     0,
            NULL );
        XmStringFree ( xstr1 );
        XtAddCallback ( H, XmNactivateCallback,
            ( XtCallbackProc ) ProofNode_Goal,
            ( XtPointer ) & c_arr [ node ] );
        xstr1 = XmStringCreateLtoR ( "|-", charset );
        XtVaCreateManagedWidget ( goal_str,
            xmLabelWidgetClass,        rc,
            XmNshadowThickness,        0,
            XmNlabelString,            xstr1,
            XmNmarginWidth,            2,
            XmNmarginHeight,           2,
            XmNdefaultButtonShadowThickness,        0,
            XmNhighlightThickness,     0,
            NULL );
        XmStringFree ( xstr1 );
      }
      but = XtVaCreateManagedWidget ( goal_str, 
          xmPushButtonWidgetClass,   rc,
          XmNshadowThickness,        0,
          XmNlabelString,            xstr,
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          XmNdefaultButtonShadowThickness,        0,
          XmNhighlightThickness,     0, 
          NULL );
      XtAddCallback ( but, XmNactivateCallback,
          ( XtCallbackProc ) Pre_FormattedGoal_CB,
          ( XtPointer ) & c_arr [ goal ] );
    }
    else {  /* ! goals_as_push_but */
      but = XtVaCreateManagedWidget ( goal_str, 
          xmLabelWidgetClass,        rc,
          XmNshadowThickness,        0,
          XmNlabelString,            xstr,
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          XmNdefaultButtonShadowThickness,        0,
          XmNhighlightThickness,     0,
          XmNtraversalOn,            False,
          NULL );
    }
  }

  XmStringFree ( xstr );

/***
  printf ( "    goal @ %d %d (extra_lines %d)\n", x_pos + 2, y_pos, extra_lines );
***/

  extra_lines = extra_lines + num_imp;
  y_pos = y_pos + ( num_imp * proof_extra_lines_offset );

/***
printf ( "  incrementing extra_lines by %d, y_pos by %d\n", num_imp, num_imp * proof_extra_lines_offset );
***/

  if ( son_num ) {

    extra_lines = extra_lines - num_imp;
    y_pos = y_pos - ( num_imp * proof_extra_lines_offset );

    XtVaCreateManagedWidget ( "ProofTree", 
        xmLabelWidgetClass,         proof_tree_scroll_form,
        XmNlabelType,               XmPIXMAP,
        XmNlabelPixmap,             h_pixmap,
        XmNshadowThickness,         0,
        XmNmarginWidth,             0,
        XmNmarginHeight,            0,
        XmNx,                       x_pos - ( proof_horiz_offset / 2 ),
        XmNy,                       y_pos + half_proof_goal_height,
        XmNtraversalOn,             False,
        NULL );

/***
  printf ( "    line @ %d %d (extra_lines %d)\n", x_pos - ( proof_horiz_offset / 2 ), y_pos + half_proof_goal_height, extra_lines );
***/

    XtVaCreateManagedWidget ( "ProofTree", 
        xmLabelWidgetClass,         proof_tree_scroll_form,
        XmNlabelType,               XmPIXMAP,
        XmNlabelPixmap,             sv_pixmap,
        XmNshadowThickness,         0,
        XmNmarginWidth,             0,
        XmNmarginHeight,            0,
        XmNx,                       x_pos - ( proof_horiz_offset / 2 ),
        XmNy,                       y_pos - proof_vert_offset + ( 2 * half_proof_goal_height ) + goal_rule_vert_diff,
        XmNtraversalOn,             False,
        NULL );

    for ( i = 1 ; i < son_num ; i++ ) {

      XtVaCreateManagedWidget ( "ProofTree", 
          xmLabelWidgetClass,         proof_tree_scroll_form,
          XmNlabelType,               XmPIXMAP,
          XmNlabelPixmap,             lv_pixmap,
          XmNshadowThickness,         0,
          XmNmarginWidth,             0,
          XmNmarginHeight,            0,
          XmNx,                       x_pos - ( proof_horiz_offset / 2 ),
          XmNy,                       y_pos - proof_vert_offset + ( 2 * half_proof_goal_height ) + goal_rule_vert_diff - ( i * proof_vert_offset ),
          XmNtraversalOn,             False,
          NULL );

    }

    extra_lines = extra_lines + num_imp;
    y_pos = y_pos + ( num_imp * proof_extra_lines_offset );

  }

  y_pos = y_pos + goal_rule_vert_diff;

  if ( buf [ 0 ] != '\0' ) {
    xstr = XmStringCreateLtoR ( buf, charset );
    but = XtVaCreateManagedWidget ( "Rule",
        xmLabelWidgetClass,        proof_tree_scroll_form,
        XmNshadowThickness,        0,
        XmNlabelString,            xstr,
        XmNmarginWidth,            0,
        XmNmarginHeight,           0,
        XmNdefaultButtonShadowThickness,        0,
        XmNhighlightThickness,     0,
        XmNx,                      x_pos + 7,  
        XmNy,                      y_pos,  
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

/*
    if ( strcmp ( buf, "DED" ) == 0 ) {
      XtVaSetValues ( but,
          XmNx,                      x_pos + 12,  
          NULL );
    }
*/

/***
  printf ( "%s\n", buf );
  printf ( "    just @ %d %d (extra_lines %d)\n", x_pos + 7, y_pos, extra_lines );
***/

  }

  if ( ( node == -999 ) && ( ny != 1 ) ) {        /**** ??? nx != 0 ??? ***/

    extra_lines = extra_lines - num_imp;
    y_pos = y_pos - ( num_imp * proof_extra_lines_offset );

    if ( goals_as_push_but ) {
      xstr = XmStringCreateLtoR ( "(Click H for hypotheses, goal for its formatted version)", charset );
      but = XtVaCreateManagedWidget ( "Highlight",
          xmLabelWidgetClass,        proof_tree_scroll_form,
          XmNlabelString,            xstr,
          XmNmarginWidth,            0,
          XmNmarginHeight,           0,
          XmNx,                      x_pos,
          XmNy,                      y_pos,
          XmNtraversalOn,            False,
          NULL );
      XmStringFree ( xstr );
    }
    else {
      header_frame = XtVaCreateManagedWidget ( "CurrentGoal", 
          xmFrameWidgetClass,        proof_tree_scroll_form,
          XmNx,                      x_pos + 25,
          XmNy,                      y_pos - 15,
          XmNshadowType,             XmSHADOW_ETCHED_OUT,
          NULL );
      xstr = XmStringCreateLtoR ( "Complete", charset );

      but = XtVaCreateManagedWidget ( "Label",
          xmLabelWidgetClass,        header_frame,
          XmNshadowThickness,        0,
          XmNlabelString,            xstr,
          XmNdefaultButtonShadowThickness,        0,
          XmNhighlightThickness,     0,
          XmNmarginWidth,            5,
          XmNmarginHeight,           2,
          XmNtraversalOn,            False,
          NULL );
      XmStringFree ( xstr );

      visible_scroll = but;
    }
  }

/***
{
  Dimension xx, yy;
  int zz;
    XtVaGetValues ( proof_tree_scroll_h,
        XmNx,       & xx,
        XmNy,       & yy,
        NULL );
  printf ( "    proof_tree_scroll_h %d %d\n", xx, yy );
    XtVaGetValues ( proof_tree_scroll_v,
        XmNx,       & xx,
        XmNy,       & yy,
        NULL );
  printf ( "    proof_tree_scroll_v %d %d\n", xx, yy );
    XtVaGetValues ( proof_tree_scroll_h,
        XmNvalue,       & zz,
        NULL );
  printf ( "    proof_tree_scroll_h %d %d\n", zz );
    XtVaGetValues ( proof_tree_scroll_v,
        XmNvalue,       & zz,
        NULL );
  printf ( "    proof_tree_scroll_v %d %d\n", zz );
}
***/

/***
printf ( "----DisplayProofNode done\n\n" );
***/
/*
  XmUpdateDisplay ( proof_tree_scroll_form );
*/
}


XtCallbackProc
Dismiss_BrowseTheories_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;
  BrowseTheories ( 0, 0 );
  if ( cbs->reason == XmCR_PROTOCOLS ) BrowseTheories ( 0, 1 );
}

XtCallbackProc
BrowseTheories_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  int but_num =  * ( int * ) client_data;
  visible_browse_but_num = but_num;
  BrowseTheories ( 0, 0 );
  BrowseATheory ( but_num, 0 );
}

void
BrowseTheories ( flag, WM_flag )
int flag;
int WM_flag;
{
  static Widget B_logo, Label, sep, menu_rc, visible_browse_but;

  Widget but, bot_form, dismiss;

  XmString xstr;
  int i;
  static int first_time = 1;
  static Atom   WM_DELETE_WINDOW;

  if ( ! flag ) {

    XtVaGetValues ( browse_theories_dialog,
        XmNx,       & last_browse_x,
        XmNy,       & last_browse_y,
        NULL );

    if ( browse_position_changed_x ) {
      global_browse_x = last_browse_x - wm_width;
    }

    if ( browse_position_changed_y ) {
      global_browse_y = last_browse_y - wm_height;
    }

    XtPopdown ( browse_theories_dialog );
    XtDestroyWidget ( menu_rc );
    browse_theories_is_up = 0;

    switch ( curr_menu ) {
    case main_menu :
      XtVaSetValues ( main_browse_widget_but, XmNsensitive, True, NULL );
      XmUpdateDisplay ( main_browse_widget_but );
      break;
    case a_theory_menu :
      XtVaSetValues ( theory_browse_widget_but, XmNsensitive, True, NULL );
      XmUpdateDisplay ( theory_browse_widget_but );
      break;
    case a_rule_menu :
      XtVaSetValues ( rule_browse_widget_but, XmNsensitive, True, NULL );
      XmUpdateDisplay ( rule_browse_widget_but );
      break;
    case prove_rule_menu :
      XtVaSetValues ( prove_browse_widget_but, XmNsensitive, True, NULL );
      XmUpdateDisplay ( prove_browse_widget_but );
      break;
    }

    XmUpdateDisplay ( top_level );
    return;
  }

  if ( WM_flag ) {
      XtDestroyWidget ( browse_theories_dialog );
      first_time = 1;
      return;
  }

  if ( browse_theories_is_up || browse_a_theory_is_up ) {
    Popup_Info ( "   Theory browse already displayed!   " );
    return;
  }

  if ( first_time ) {

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    browse_theories_dialog =
          XmCreateDialogShell ( top_frame_form, "BrowseDialog", NULL, 0 );

    XmAddWMProtocolCallback ( browse_theories_dialog, WM_DELETE_WINDOW,
        ( XtCallbackProc ) Dismiss_BrowseTheories_CB,
        ( XtPointer ) NULL );

    browse_theories_dialog_form = XtVaCreateWidget ( "BrowseDialog",
        xmFormWidgetClass,         browse_theories_dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        False,  
        NULL );

    XtAddCallback ( browse_theories_dialog, XmNpopupCallback,
        ( XtCallbackProc ) RepositionBrowse_CB,
        NULL );

    B_logo =  XtVaCreateWidget ( "BrowseDialog",
        xmLabelWidgetClass,         browse_theories_dialog_form,
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

    xstr = XmStringCreateLtoR ( "  Browse Theories  ", charset );
    Label = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,        browse_theories_dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNleftOffset,             50,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNrightOffset,            75,
        XmNlabelString,            xstr,
        XmNmarginWidth,            10,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

    sep = XtVaCreateManagedWidget ( "BrowseDialog", 
      xmSeparatorGadgetClass,  browse_theories_dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         48,
      NULL );

    browse_theories_menu_scroll = XtVaCreateWidget ( "BrowseDialog",
        xmScrolledWindowWidgetClass,    browse_theories_dialog_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   50,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 5,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  5,
        XmNbottomAttachment,            XmATTACH_WIDGET,
        XmNbottomWidget,                sep,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNspacing,                     0,
        NULL );

#ifndef BTOOLKIT_FLAG
    visible_browse_but_num = 1;
#else
    visible_browse_but_num = first_btl_thy_to_display - 1;
#endif

  }

  menu_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         browse_theories_menu_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNspacing,                     5,
      XmNisHomogeneous,               False,
      NULL );


#ifndef BTOOLKIT_FLAG
  but = CreHighlightedButton ( menu_rc, "  1: bootX (9)",
              ( XtCallbackProc ) BrowseTheories_CB,
              & c_arr [ 1 ] );
  if ( visible_browse_but_num == 1 ) visible_browse_but = but;
#endif

#ifndef BTOOLKIT_FLAG
  for ( i = 2 ; i <= nbr_the ; i++ ) {
#else

#ifdef BTOOL_PROVER_NEW
  for ( i = 2 ; i <= nbr_the ; i++ ) {
#else
  for ( i = 2 ; i < first_btl_thy_to_display ; i++ ) {
#endif /* BTOOL_PROVER_NEW */

#endif /* BTOOLKIT_FLAG */

    write_the ( i );
    but = CreHighlightedButton ( menu_rc, str_buf,
              ( XtCallbackProc ) BrowseTheories_CB,
              & c_arr [ i ] );

#ifdef BTOOLKIT_FLAG
    if ( ThySeparatorReqd ( i ) )
      XtVaCreateManagedWidget ( "Canvas",
          xmSeparatorGadgetClass,  menu_rc,
          NULL );
#endif

    if ( i == visible_browse_but_num ) visible_browse_but = but;

  }


  bot_form = XtVaCreateWidget ( "ButtonLabel",
      xmFormWidgetClass,       browse_theories_dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNtopAttachment,        XmATTACH_WIDGET,
      XmNtopWidget,            sep,
      XmNtopOffset,            3,
      NULL );

  dismiss = XtVaCreateManagedWidget ( "Dismiss", 
      xmPushButtonGadgetClass, bot_form,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          15,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNheight,               28,
      XmNwidth,                70,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      XmNnavigationType,       XmTAB_GROUP,
      NULL );
  XtAddCallback ( dismiss, XmNactivateCallback,
      ( XtCallbackProc ) Dismiss_BrowseTheories_CB,
      ( XtPointer ) Dismiss_BrowseTheories_CB );
  

  XtManageChild ( B_logo );
  XtManageChild ( Label );
  XtManageChild ( browse_theories_menu_scroll );
  XtManageChild ( menu_rc );
  XtManageChild ( bot_form );

  if ( first_time ) {

    first_time = 0;

    if ( nbr_the <= 10 ) {
      XtVaSetValues ( browse_theories_menu_scroll, XmNheight, ( 10 * /* 21 */ 19 ) + 10, NULL );
    }
    else if ( nbr_the <= 30 ) {
      XtVaSetValues ( browse_theories_menu_scroll, XmNheight, ( nbr_the * /* 21 */ 19 ) + 10, NULL );
    }
    else {
      XtVaSetValues ( browse_theories_menu_scroll, XmNheight, ( 30 * /* 21 */ 19 ) + 10, NULL );
    }

  }

  browse_theories_is_up = 1;

  XtManageChild ( browse_theories_dialog_form );

  XmScrollVisible ( browse_theories_menu_scroll, visible_browse_but, 0, 20 );
  XmUpdateDisplay ( menu_rc );
  XmUpdateDisplay ( browse_theories_menu_scroll );

  switch ( curr_menu ) {
  case main_menu :
    XtVaSetValues ( main_browse_widget_but, XmNsensitive, False, NULL );
    XmUpdateDisplay ( main_browse_widget_but );
    break;
  case a_theory_menu :
    XtVaSetValues ( theory_browse_widget_but, XmNsensitive, False, NULL );
    XmUpdateDisplay ( theory_browse_widget_but );
    break;
  case a_rule_menu :
    XtVaSetValues ( rule_browse_widget_but, XmNsensitive, False, NULL );
    XmUpdateDisplay ( rule_browse_widget_but );
    break;
  case prove_rule_menu :
    XtVaSetValues ( prove_browse_widget_but, XmNsensitive, False, NULL );
    XmUpdateDisplay ( prove_browse_widget_but );
    break;
  }

  XtPopup ( browse_theories_dialog, XtGrabNone );
  XmUpdateDisplay (  browse_theories_dialog );

}

/*
void
DisplayDependentProofs ( tmp_seq )
int tmp_seq;
{
  int i;
  int ll = len ( tmp_seq );
  if ( ll ) {
    if ( ll == 1 )
      strcpy ( str_buf, "\n  \nThe following proof is dependent on\n" );
    else
      strcpy ( str_buf, "\nThe following proofs are dependent on\n" );
    write_nam_the ( the_rul ( btl_rule ) );
    strcat ( str_buf, "." );
    write_nat ( num_rul ( btl_rule ) );
    strcat ( str_buf, " and must\nfirst be removed:\n" );
    for ( i = 1 ; i <= ll ; i++ ) {
      strcat ( str_buf, "\n                    " );
      write_nam_the ( the_rul ( val ( tmp_seq, i ) ) );
      strcat ( str_buf, "." );
      write_nat ( num_rul ( val ( tmp_seq, i ) ) );    
    }
    sprintf ( primary_string, "%s\n\n              Remove rule ?\n  ", str_buf );
    strcpy ( secondary_string, "All dependent proofs will be lost!" );
    radiobox_flag = rem_rul_dep_proof_radiobox;
    Popup_ConfirmDialog ( top_level );
  }
  else {
    DisplayDependentProofs_YES ();
  }
}
*/


void
LoadSeqProofsUsing_btl_rule ( tmp_seq )
int * tmp_seq;
{
  int i, l, j;
  for ( i = 1 ; i < max_proved_rr ; i++ ) {

    if ( proved_rr [ i ] ) {
/***
printf ( "  ** LoadSeqProofsUsing_btl_rule: proved_rr [ %d ]\n", i );
***/
      l = len ( proved_seq_rr [ i ] );
      for ( j = 1 ; j <= l ; j++ ) {
        if ( val ( proved_seq_rr [ i ], j ) == btl_rule ) {
/***
printf ( "     ** val ( proved_seq_rr [ i ], j ) == btl_rule: %d\n", btl_rule );
***/
          psh ( * tmp_seq, proved_rr [ i ] );
/***
printf ( "         pushing proved_rr [ i ] (%d) onto tmp_seq\n", proved_rr [ i ] );
***/
	}
      }
    }

    if ( proved_fwd_btl_rr [ i ] ) {
/***
printf ( "  ** LoadSeqProofsUsing_btl_rule: proved_fwd_btl_rr [ %d ]\n", i );
***/
      l = len ( proved_fwd_btl_rr [ i ] );
      for ( j = 1 ; j <= l ; j++ ) {
        if ( val ( proved_fwd_btl_rr [ i ], j ) == btl_rule ) {
/***
printf ( "     ** val ( proved_fwd_btl_rr [ i ], j ) == btl_rule: %d\n", btl_rule );
***/
          psh ( * tmp_seq, proved_rr [ i ] );
/***
printf ( "         pushing proved_rr [ i ] (%d) onto tmp_seq\n", proved_rr [ i ] );
***/
	}
      }
    }

  }
}

#ifdef BTOOLKIT_FLAG

void
LoadSeqAllBtlRulesUsedInProof ( tmp_seq )
int * tmp_seq;
{
  int i, l, j, rr;

  for ( i = 1 ; i < max_proved_rr ; i++ ) {

    if ( proved_rr [ i ] ) {
/***
printf ( "  ** LoadSeqAllBtlRulesUsedInProof: proved_rr [ %d ]\n", i );
***/
      l = len ( proved_seq_rr [ i ] );
/***
printf ( "  len ( proved_seq_rr [ %d ] ) = %d\n", i, l );
***/
      for ( j = 1 ; j <= l ; j++ ) {
        rr = val ( proved_seq_rr [ i ], j );
        if ( rr <= max_rul ) {
/***
printf ( "     ** rr -> %d  the_rul ( %d ) -> %d\n", rr, rr, the_rul ( rr ) );
***/
          if ( ( the_rul ( rr ) == btl_users_thy )    ||
               ( the_rul ( rr ) == fwd_btl_users_thy )   ) {
            psh ( * tmp_seq, rr );
/***
printf ( "         pushing rr (%d) onto tmp_seq\n", rr );
***/
	  }
	}
      }
    }

    if ( proved_fwd_btl_rr [ i ] ) {
/***
printf ( "  ** LoadSeqAllBtlRulesUsedInProof: proved_fwd_btl_rr [ %d ]\n", i );
***/
      l = len ( proved_fwd_btl_rr [ i ] );
/***
printf ( "  len ( proved_fwd_btl_rr [ %d ] ) = %d\n", i, l );
***/
      for ( j = 1 ; j <= l ; j++ ) {
        rr = val ( proved_fwd_btl_rr [ i ], j );
        if ( rr <= max_rul ) {
/***
printf ( "     ** rr -> %d  the_rul ( %d ) -> %d\n", rr, rr, the_rul ( rr ) );
***/
          if ( ( the_rul ( rr ) == btl_users_thy )    ||
               ( the_rul ( rr ) == fwd_btl_users_thy )   ) {
            psh ( * tmp_seq, rr );
/***
printf ( "         pushing rr (%d) onto tmp_seq\n", rr );
***/
	  }
	}
      }
    }

  }
}

#endif /* BTOOLKIT_FLAG */


XtCallbackProc
AddRule_BrowseATheory_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  if ( browse_a_theory_is_up != 1 ) {
    string_box_flag = string_box_new_rule_from_browse;
    LargeStringBox ( " New Rule:                                                                                                      ", "" );
  }
  else {
    Popup_Info ( "    Can't add new rule to this theory!   " );
  }
}

XtCallbackProc
BrowseTheories_BrowseATheory_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  BrowseATheory ( 0, 0 );
  BrowseTheories ( 1, 0 );
}

XtCallbackProc
Dismiss_BrowseATheory_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;
  BrowseATheory ( 0, 0 );
  if ( cbs->reason == XmCR_PROTOCOLS ) BrowseATheory ( 0, 1 );
}

void
ChangeBToolUserRule ()
{ 
  string_box_flag = string_box_change_rule_from_browse;
  str_buf [ 0 ] = '\0';
  browse_btool_theory_rul = btl_rule;
  write_ver_rul_dave ( browse_btool_theory_rul );
  LargeStringBox ( " New Rule:                                                                                                      ", str_buf );
}

XtCallbackProc
BrowseUserRule_CB_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  int browse_a_theory_is_up_save;

  XtPopdown ( XtParent ( widget ) );
  XmUpdateDisplay ( XtParent ( widget ) );
  XtDestroyWidget ( XtParent ( widget ) );

  if   ( ( * ( int * ) client_data ) == HELP_BUTTON ) return;

  if   ( ( * ( int * ) client_data ) == OK_BUTTON ) {
    ChangeBToolUserRule ();
  }
  else {
    rem_rul_the ( the_rul ( btl_rule ), num_rul ( btl_rule ) );
      browse_a_theory_is_up_save = browse_a_theory_is_up;
      BrowseATheory ( 0, 0 );
      browse_a_theory_is_up = browse_a_theory_is_up_save;
      BrowseATheory ( browse_a_theory_is_up, 0 );
  }
}

XtCallbackProc
BrowseUserRule_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  Widget dialog;
  XmString msg, change, remove, cancel;
  int tmp_seq = cre ( 10 );
  int dependent_proofs = 0;
  int j, ll;

  btl_rule = val_rul_the ( browse_a_theory_is_up, ( * ( int * ) client_data ) );

  dialog = XmCreateQuestionDialog( browse_a_theory_dialog, "UserRule", NULL, 0 );
  change = XmStringCreateLocalized ( "Change Rule" );
  remove = XmStringCreateLocalized ( "Remove Rule" );
  cancel = XmStringCreateLocalized ( "Dismiss" );
  XtVaSetValues ( dialog,
      XmNautoUnmanage,           False,
      XmNdefaultButtonType,      XmNONE,
      XmNokLabelString,          change,
      XmNcancelLabelString,      remove,
      XmNhelpLabelString,        cancel,
      XmNsymbolPixmap,           B_framed_pixmap_gray94,
      XmNmarginWidth,            10,
      XmNmarginHeight,           5,
      NULL );
  XmStringFree ( change );
  XmStringFree ( remove );
  XmStringFree ( cancel );

  XtAddCallback ( dialog, XmNokCallback,
                     ( XtCallbackProc ) BrowseUserRule_CB_CB, 
                     ( XtPointer ) & c_arr [ OK_BUTTON ] );
  XtAddCallback ( dialog, XmNcancelCallback,
                     ( XtCallbackProc ) BrowseUserRule_CB_CB,
                     ( XtPointer ) & c_arr [ CANCEL_BUTTON ] );
  XtAddCallback ( dialog, XmNhelpCallback,
                     ( XtCallbackProc ) BrowseUserRule_CB_CB,
                     ( XtPointer ) & c_arr [ HELP_BUTTON ] );

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

  XtVaSetValues ( XmMessageBoxGetChild ( dialog, XmDIALOG_HELP_BUTTON ),
     XmNdefaultButton,                 False,
     XmNdefaultButtonShadowThickness,  1,
     XmNhighlightThickness,            1,
     XmNnavigationType,                XmTAB_GROUP,
     NULL);

  strcpy ( str_buf, "    \n" );
  write_nam_the ( browse_a_theory_is_up );
  strcat ( str_buf, "." );
  write_nat ( num_rul ( btl_rule ) );
  strcat ( str_buf, "\n  \n" );
  app_write_rul ( btl_rule );
  strcat ( str_buf, "  \n    \n" );
  LoadSeqProofsUsing_btl_rule ( & tmp_seq );
  ll = len ( tmp_seq );
  if ( ! ll ) {
    strcat ( str_buf, "No dependent proofs\n  " );
  }
  else {
    dependent_proofs = 1;
    strcat ( str_buf, "Proofs:\n " );
    for ( j = 1 ; j <= ll ; j++ ) {
      strcat ( str_buf, "\n    " );
      write_nam_the ( the_rul ( val ( tmp_seq, j ) ) );
      strcat ( str_buf, "." );
      write_nat ( num_rul ( val ( tmp_seq, j ) ) );    
    }
    strcat ( str_buf, "\n    \n    " );
  }
  kil ( tmp_seq );

  msg = XmStringCreateLtoR ( str_buf, charset );
  XtVaSetValues ( dialog,
      XmNmessageString,          msg,
      NULL );
  XmStringFree ( msg );

  if ( dependent_proofs ) {
    XtSetSensitive( XmMessageBoxGetChild ( dialog, XmDIALOG_OK_BUTTON ), False );
    XtSetSensitive( XmMessageBoxGetChild ( dialog, XmDIALOG_CANCEL_BUTTON ), False );
  }

  XtVaSetValues ( dialog,
      XmNdialogStyle,            XmDIALOG_PRIMARY_APPLICATION_MODAL,
      NULL );

  XmProcessTraversal ( XmMessageBoxGetChild ( dialog, XmDIALOG_OK_BUTTON ),
                                                          XmTRAVERSE_CURRENT );

  XtManageChild ( dialog );
  XtPopup ( XtParent ( dialog ), XtGrabNone );
  XmUpdateDisplay ( XtParent ( dialog ) );
}

void
BrowseATheory ( t, WM_flag )
int t;
int WM_flag;
{
  static Widget B_logo, Label1, Label2, sep, menu_rc,
         bot_form, add_rule, browse_theories, dismiss;

  Widget but, first_but;

  XmString xstr;
  int i, j, tot_rul, cur_level_rules, ll, tmp_seq;

  static int first_time = 1;
  static Atom   WM_DELETE_WINDOW;

  cur_level_rules = 0;

  first_but = 0;

  if ( ! t ) {

    XtVaGetValues ( browse_a_theory_dialog,
        XmNx,       & last_browse_x,
        XmNy,       & last_browse_y,
        NULL );

    if ( browse_position_changed_x ) {
      global_browse_x = last_browse_x - wm_width;
    }

    if ( browse_position_changed_y ) {
      global_browse_y = last_browse_y - wm_height;
    }

    XtPopdown ( browse_a_theory_dialog );
    XtDestroyWidget ( menu_rc );
    browse_a_theory_is_up = 0;

    switch ( curr_menu ) {
    case main_menu :
      XtVaSetValues ( main_browse_widget_but, XmNsensitive, True, NULL );
      XmUpdateDisplay ( main_browse_widget_but );
      break;
    case a_theory_menu :
      XtVaSetValues ( theory_browse_widget_but, XmNsensitive, True, NULL );
      XmUpdateDisplay ( theory_browse_widget_but );
      break;
    case a_rule_menu :
      XtVaSetValues ( rule_browse_widget_but, XmNsensitive, True, NULL );
      XmUpdateDisplay ( rule_browse_widget_but );
      break;
    case prove_rule_menu :
      XtVaSetValues ( prove_browse_widget_but, XmNsensitive, True, NULL );
      XmUpdateDisplay ( prove_browse_widget_but );
      break;
    }

    XmUpdateDisplay ( top_level );
    return;
  }

  if ( WM_flag ) {
      XtDestroyWidget ( browse_a_theory_dialog );
      first_time = 1;
      return;
  }

  if ( first_time ) {

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    browse_a_theory_dialog =
        XmCreateDialogShell ( top_frame_form, "BrowseDialog", NULL, 0 );

    XmAddWMProtocolCallback ( browse_a_theory_dialog, WM_DELETE_WINDOW,
        ( XtCallbackProc ) Dismiss_BrowseATheory_CB,
        ( XtPointer ) NULL );

    browse_a_theory_dialog_form = XtVaCreateWidget ( "BrowseDialog",
        xmFormWidgetClass,         browse_a_theory_dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        False,  
        NULL );

    XtAddCallback ( browse_a_theory_dialog, XmNpopupCallback,
        ( XtCallbackProc ) RepositionBrowse_CB,
        NULL );

    B_logo =  XtVaCreateWidget ( "BrowseDialog",
        xmLabelWidgetClass,         browse_a_theory_dialog_form,
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

    strcpy ( str_buf, "        Browse:   " );
    write_nam_the ( t );
    strcat ( str_buf, "                  " );
    xstr = XmStringCreateLtoR ( str_buf, charset );
    Label1 = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,        browse_a_theory_dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              7,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNleftOffset,             5,
        XmNlabelString,            xstr,
        XmNmarginWidth,            10,
        XmNmarginHeight,           10,
        XmNtraversalOn,            False,
        NULL );

#ifdef BTOOLKIT_FLAG

    XmStringFree ( xstr );
    xstr =
      XmStringCreateLtoR ( "(Click to select a current-level Rule)", charset );
    Label2 = XtVaCreateWidget ( "Highlight", 
        xmLabelWidgetClass,        browse_a_theory_dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              35,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNleftOffset,             5,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNlabelString,            xstr,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNtraversalOn,            False,
        NULL );
#endif

    XmStringFree ( xstr );

    sep = XtVaCreateManagedWidget ( "HelpDialog", 
      xmSeparatorGadgetClass,  browse_a_theory_dialog_form,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         48,
      NULL );

    browse_a_theory_menu_scroll = XtVaCreateWidget ( "BrowseDialog",
        xmScrolledWindowWidgetClass,    browse_a_theory_dialog_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   50,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 5,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  5,
        XmNbottomAttachment,            XmATTACH_WIDGET,
        XmNbottomWidget,                sep,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNspacing,                     0,
        NULL );

    bot_form = XtVaCreateWidget ( "ButtonLabel",
        xmFormWidgetClass,       browse_a_theory_dialog_form,
        XmNleftAttachment,       XmATTACH_FORM,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNtopAttachment,        XmATTACH_WIDGET,
        XmNtopWidget,            sep,
        XmNtopOffset,            3,
        NULL );

    dismiss = XtVaCreateManagedWidget ( "Quit", 
        xmPushButtonGadgetClass, bot_form,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNrightOffset,          7,
        XmNtopAttachment,        XmATTACH_FORM,
        XmNheight,               28,
        XmNwidth,                85,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   1,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XtAddCallback ( dismiss, XmNactivateCallback,
        ( XtCallbackProc ) Dismiss_BrowseATheory_CB,
        ( XtPointer ) Dismiss_BrowseATheory_CB );
  
    browse_theories = XtVaCreateManagedWidget ( "Theories", 
        xmPushButtonGadgetClass, bot_form,
        XmNleftAttachment,       XmATTACH_FORM,
        XmNleftOffset,           7,
        XmNtopAttachment,        XmATTACH_FORM,
        XmNheight,               28,
        XmNwidth,                110,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   1,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XtAddCallback ( browse_theories, XmNactivateCallback,
        ( XtCallbackProc ) BrowseTheories_BrowseATheory_CB,
        ( XtPointer ) NULL );
  
    add_rule = XtVaCreateWidget ( "Add New Rule", 
        xmPushButtonGadgetClass, bot_form,
        XmNleftAttachment,       XmATTACH_WIDGET,
        XmNleftWidget,           browse_theories,
        XmNleftOffset,           0,
        XmNtopAttachment,        XmATTACH_FORM,
        XmNheight,               28,
        XmNwidth,                112,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   1,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XtAddCallback ( add_rule, XmNactivateCallback,
        ( XtCallbackProc ) AddRule_BrowseATheory_CB,
        ( XtPointer ) NULL );
  
  }  /* if ( first_time ) */

  XtDestroyWidget ( Label1 );

  strcpy ( str_buf, "                         " ); 
  write_nam_the ( t );
  strcat ( str_buf, "                         " ); 

  xstr = XmStringCreateLtoR ( str_buf, charset );
  Label1 = XtVaCreateWidget ( "Label", 
      xmLabelWidgetClass,        browse_a_theory_dialog_form,
      XmNtopAttachment,          XmATTACH_FORM,
      XmNtopOffset,              7,
      XmNleftAttachment,         XmATTACH_WIDGET,
      XmNleftWidget,             B_logo,
      XmNleftOffset,             5,
      XmNrightAttachment,        XmATTACH_FORM,
      XmNlabelString,            xstr,
      XmNmarginWidth,            10,
      XmNmarginHeight,           10,
      XmNtraversalOn,            False,
      NULL );
  XmStringFree ( xstr );

#ifdef BTOOLKIT_FLAG

  if ( UsersBToolThy ( t ) ) {
    XtVaSetValues ( browse_a_theory_menu_scroll,
        XmNtopOffset,              55,
        NULL );
  }
  else {
    XtVaSetValues ( browse_a_theory_menu_scroll,
        XmNtopOffset,              40,
        NULL );
  }

#endif

  menu_rc = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,         browse_a_theory_menu_scroll,
      XmNorientation,                 XmVERTICAL,
      XmNmarginWidth,                 5,
      XmNmarginHeight,                5,
      XmNspacing,                     5,
      XmNisHomogeneous,               False,
      XmNnavigationType,              XmTAB_GROUP,
      NULL );

  tot_rul = nbr_rul_the ( t );

  for ( i = 1 ; i <= tot_rul ; i++ ) {
    str_buf [ 0 ] = '\0';
    app_write_rul_ful ( val_rul_the ( t, i ) );

#ifdef BTOOLKIT_FLAG
    
    if ( UsersBToolThy ( t ) ) {
      if ( RulePrevPmdLevel ( val_rul_the ( t, i ) ) ) {
        CrePassiveButton ( menu_rc, str_buf );
        xstr = XmStringCreateLtoR ( "    Previous level rule\n  ", charset );
        XtVaCreateManagedWidget ( "Label",
            xmLabelWidgetClass,        menu_rc,
            XmNlabelString,            xstr,
            XmNmarginWidth,            5,
            XmNmarginHeight,           0,
            XmNtraversalOn,            False,
            NULL );
        XmStringFree ( xstr );
      }
      else {
        cur_level_rules = 1;
        xstr = XmStringCreateLtoR ( str_buf, charset );
        but = XtVaCreateManagedWidget ( "SelDialog",
            xmPushButtonGadgetClass,   menu_rc,
            XmNshadowThickness,        0,
            XmNlabelString,            xstr,
            XmNmarginWidth,            0,
            XmNmarginHeight,           0,
            XmNdefaultButtonShadowThickness,        0,
            XmNhighlightThickness,     1,
            XmNnavigationType,         XmTAB_GROUP,
            NULL );
        XmStringFree ( xstr );

        if ( ! first_but ) first_but = but;

        btl_rule = val_rul_the ( t, i );
        tmp_seq = cre ( 10 );
        LoadSeqProofsUsing_btl_rule ( & tmp_seq );
        ll = len ( tmp_seq );
	if ( ! ll ) {
          strcpy ( str_buf, "    No dependent proofs\n  " );
	}
        else {
          strcpy ( str_buf, "    Proofs:" );
          for ( j = 1 ; j <= ll ; j++ ) {
            strcat ( str_buf, " " );
            write_nam_the ( the_rul ( val ( tmp_seq, j ) ) );
            strcat ( str_buf, "." );
            write_nat ( num_rul ( val ( tmp_seq, j ) ) );    
          }
          strcat ( str_buf, "\n  " );
	}
        kil ( tmp_seq );

        xstr = XmStringCreateLtoR ( str_buf, charset );
        XtVaCreateManagedWidget ( "Highlight", 
            xmLabelWidgetClass,        menu_rc,
            XmNlabelString,            xstr,
            XmNmarginWidth,            5,
            XmNmarginHeight,           0,
            XmNtraversalOn,            False,
            NULL );
        XmStringFree ( xstr );

        if ( t == btl_users_thy ) {
          XtAddCallback ( but, XmNactivateCallback,
              ( XtCallbackProc ) BrowseUserRule_CB,
              & c_arr [ i ] );
        }
        else {
          XtAddCallback ( but, XmNactivateCallback,
              ( XtCallbackProc ) BrowseUserRule_CB,
              & c_arr [ i ] );
	}
      }
    }
    else {
      CrePassiveButton ( menu_rc, str_buf );
    }

#else

    CrePassiveButton ( menu_rc, str_buf );

#endif

  }

  XtManageChild ( B_logo );
  XtManageChild ( browse_a_theory_menu_scroll );
  XtManageChild ( menu_rc );
  XtManageChild ( Label1 );
#ifdef BTOOLKIT_FLAG
  if   ( UsersBToolThy ( t ) ) XtManageChild ( Label2 );
  else                         XtUnmanageChild ( Label2 );
#endif
  XtManageChild ( bot_form );

  if ( first_time ) {

    first_time = 0;

/*
    if ( tot_rul <= 10 ) {
      XtVaSetValues ( browse_a_theory_menu_scroll, XmNheight, ( 10 * 24 ) + 10, NULL );
    }
    else if ( tot_rul <= 30 ) {
      XtVaSetValues ( browse_a_theory_menu_scroll, XmNheight, ( tot_rul * 24 ) + 10, NULL );
    }
    else {
      XtVaSetValues ( browse_a_theory_menu_scroll, XmNheight, ( 30 * 24 ) + 10, NULL );
    }
*/
    if ( nbr_the <= 10 ) {
      XtVaSetValues (  browse_a_theory_menu_scroll, XmNheight, ( 10 * /* 21 */ 19 ) + 10, NULL );
    }
    else if ( nbr_the <= 30 ) {
      XtVaSetValues (  browse_a_theory_menu_scroll, XmNheight, ( nbr_the * /* 21 */ 19 ) + 10, NULL );
    }
    else {
      XtVaSetValues (  browse_a_theory_menu_scroll, XmNheight, ( 30 * /* 21 */ 19 ) + 10, NULL );
    }
  }

  browse_a_theory_is_up = t;

  XtManageChild ( browse_a_theory_dialog_form );

#ifdef BTOOLKIT_FLAG

  if   ( UsersBToolThy ( t ) ) {
    XtManageChild ( add_rule );
  }
  else {
    XtUnmanageChild ( add_rule );
  }

#else

  if   ( t == 1 ) {
    XtUnmanageChild ( add_rule );
  }
  else {
    XtManageChild ( add_rule );
  }

#endif

  switch ( curr_menu ) {
  case main_menu :
    XtVaSetValues ( main_browse_widget_but, XmNsensitive, False, NULL );
    XmUpdateDisplay ( main_browse_widget_but );
    break;
  case a_theory_menu :
    XtVaSetValues ( theory_browse_widget_but, XmNsensitive, False, NULL );
    XmUpdateDisplay ( theory_browse_widget_but );
    break;
  case a_rule_menu :
    XtVaSetValues ( rule_browse_widget_but, XmNsensitive, False, NULL );
    XmUpdateDisplay ( rule_browse_widget_but );
    break;
  case prove_rule_menu :
    XtVaSetValues ( prove_browse_widget_but, XmNsensitive, False, NULL );
    XmUpdateDisplay ( prove_browse_widget_but );
    break;
  }

  XtPopup ( browse_a_theory_dialog, XtGrabNone );
  XmUpdateDisplay (  browse_a_theory_dialog );

  if   ( ! first_but ) XmProcessTraversal ( browse_theories, XmTRAVERSE_CURRENT );
  else                 XmProcessTraversal ( first_but, XmTRAVERSE_CURRENT );
}

XtCallbackProc
ApplicableRuleMenu_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  int the, nbr, t, th;
  int but_num =  * ( int * ) client_data;

  int run_ApplicableRuleMenu_CB = FALSE;

  static Position last_applicable_x, last_applicable_y;

/***
char tmp_buf [ 250 ];
sprintf ( tmp_buf, "Button %d pressed (contents %d)\n", but_num, app_rules [ but_num ] );
DisplayCurrWinText ( tmp_buf );
***/
/***
print_tac_info("ApplicableRuleMenu_CB 1");
***/
  run_man_prf_f = frm_gol(run_man_prf_g);

  XtVaGetValues ( app_rule_dialog,
      XmNx,       & last_applicable_x,
      XmNy,       & last_applicable_y,
      NULL );

  if (  applicable_position_changed_x ) {
    global_applicable_x = last_applicable_x - wm_width;
  }

  if (  applicable_position_changed_y ) {
    global_applicable_y = last_applicable_y - wm_height;
  }

  XtUnmanageChild ( app_rule_dialog );
  XtDestroyWidget ( app_rule_dialog );
  app_rule_dialog = 0;

  if ( app_rules [ but_num ] == 0 ) {
    from_applicable_rr = -1;
    run_man_prf_success = FALSE;
    Proof_CB_continued ( TRUE, proof_step_flag_NO );
  }
  else {                                        /* Theory rule */
    from_applicable_rr = app_rules [ but_num ];
/***
printf ( " 2 ====== from_applicable_rr %d\n", from_applicable_rr );
***/
    one_step_of_prf ();
  }
}

void
ApplicableRuleMenu ()
{
    Widget dialog_form, B_logo, Label1, Label2,
           menu_scroll, menu_rc, but, label_form;
    int i;
    XmString xstr;

    Atom   WM_DELETE_WINDOW;

    app_rule_dialog = XmCreateDialogShell ( top_frame_form, "SelDialog", NULL, 0 );

    WM_DELETE_WINDOW = XmInternAtom ( display, "WM_DELETE_WINDOW", False );

    XtAddCallback ( app_rule_dialog, XmNpopupCallback,
        ( XtCallbackProc ) PositionWidgetRelCurrMenu_CB,
        NULL );

    XmAddWMProtocolCallback ( app_rule_dialog, WM_DELETE_WINDOW,
        ( XtCallbackProc ) ApplicableRuleMenu_CB,
        ( XtPointer ) & c_arr [ 0 ] );

    dialog_form = XtVaCreateWidget ( "SelDialog",
        xmFormWidgetClass,         app_rule_dialog,
        XmNdialogStyle,            XmDIALOG_MODELESS,
        XmNdefaultPosition,        False,  
        NULL );

    B_logo =  XtVaCreateWidget ( "SelDialog",
        xmLabelWidgetClass,         dialog_form,
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

    label_form = XtVaCreateWidget ( "Label", 
        xmFormWidgetClass,         dialog_form,
        XmNtopAttachment,          XmATTACH_FORM,
        XmNtopOffset,              10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             B_logo,
        XmNleftOffset,             15,
        XmNrightAttachment,        XmATTACH_FORM,
        XmNrightOffset,            40,
      NULL );

    xstr = XmStringCreateLtoR ( "Applicable Rules", charset );
    Label1 = XtVaCreateWidget ( "Label", 
        xmLabelWidgetClass,        label_form,
        XmNlabelString,            xstr,
        XmNmarginWidth,            5,
        XmNmarginHeight,           10,
        XmNleftAttachment,         XmATTACH_FORM,
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

    xstr = XmStringCreateLtoR ( "(Click to apply)", charset );
    Label2 = XtVaCreateWidget ( "Highlight", 
        xmLabelWidgetClass,        label_form,
        XmNlabelString,            xstr,
        XmNmarginWidth,            5,
        XmNmarginHeight,           10,
        XmNleftAttachment,         XmATTACH_WIDGET,
        XmNleftWidget,             Label1,
        XmNleftOffset,             0,
        XmNtraversalOn,            False,
        NULL );
    XmStringFree ( xstr );

    menu_scroll = XtVaCreateWidget ( "SelDialog",
        xmScrolledWindowWidgetClass,    dialog_form,
        XmNtopAttachment,               XmATTACH_FORM,
        XmNtopOffset,                   50,
        XmNrightAttachment,             XmATTACH_FORM,
        XmNrightOffset,                 5,
        XmNleftAttachment,              XmATTACH_FORM,
        XmNleftOffset,                  5,
        XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
        XmNscrollingPolicy,             XmAUTOMATIC,
        XmNborderWidth,                 0,
        XmNshadowThickness,             0,
        XmNspacing,                     0,
        NULL );

    if   ( app_tot <= 4 ) i = ( app_tot * 90 );
    else                  i = 500;

    XtVaSetValues ( menu_scroll,
        XmNwidth,                       475,
        XmNheight,                      i,
        NULL );

    menu_rc = XtVaCreateWidget ( "Canvas",
        xmRowColumnWidgetClass,         menu_scroll,
        XmNorientation,                 XmVERTICAL,
        XmNmarginWidth,                 5,
        XmNmarginHeight,                5,
        XmNspacing,                     10,
        XmNisHomogeneous,               False,
        NULL );

    for ( i = 1 ; i < app_tot ; i++ ) {
      if ( app_rules [ i ] > max_rul ) {   /* Builtin rule (WON'T APPLY!!!) */
        but = CreHighlightedButton ( menu_rc, Builtin_TAC [ app_rules [ i ] - max_rul ],
              ( XtCallbackProc ) ApplicableRuleMenu_CB,
              & c_arr [ i ] );
      }
      else {                                        /* Theory rule */
        int rr = app_rules [ i ];
        int the = the_rul ( rr );
        int nbr = num_rul ( rr );
        str_buf [ 0 ] = '\0';
        write_nam_the ( the );
        strcat ( str_buf, "." );
        CreNumInBuf ( str_buf, nbr );
        strcat ( str_buf, "\n\n" );
        app_write_rul ( rr );
        but = CreHighlightedButton ( menu_rc, str_buf,
              ( XtCallbackProc ) ApplicableRuleMenu_CB,
              & c_arr [ i ] );
      }
    }

    xstr = XmStringCreateLtoR ( "Return to Proof Menu", charset );
    but = XtVaCreateManagedWidget ( "ButtonLabel", 
        xmPushButtonGadgetClass, dialog_form,
        XmNlabelString,          xstr,
        XmNtopAttachment,        XmATTACH_WIDGET,
        XmNtopWidget,            menu_scroll,
        XmNtopOffset,            20,
        XmNrightAttachment,      XmATTACH_FORM,
        XmNrightOffset,          15,
        XmNbottomAttachment,     XmATTACH_FORM,
        XmNbottomOffset,         15,
        XmNheight,               28,
        XmNwidth,                175,
        XmNdefaultButtonShadowThickness,        1,
        XmNhighlightThickness,   1,
        XmNnavigationType,       XmTAB_GROUP,
        NULL );
    XmStringFree ( xstr );

    XtAddCallback ( but, XmNactivateCallback,
        ( XtCallbackProc ) ApplicableRuleMenu_CB,
        ( XtPointer ) & c_arr [ 0 ] );

    applicable_rules_up = 1;

    XtManageChild ( B_logo );
    XtManageChild ( Label1 );
    XtManageChild ( Label2 );
    XtManageChild ( label_form );
    XtManageChild ( menu_scroll );
    XtManageChild ( menu_rc );

    XtManageChild ( dialog_form );

    XtPopup ( app_rule_dialog, XtGrabNone );
    XmUpdateDisplay ( app_rule_dialog );
    XmUpdateDisplay ( top_level );
/***
print_tac_info("AppRules");
***/
}

void
CheckBrowseAfterModrRule ( t )
int t;
{
  if ( t == browse_a_theory_is_up ) {
    BrowseATheory ( 0, 0 );
    BrowseATheory ( t, 0 );
  }
  else if ( browse_theories_is_up ) {
    BrowseTheories ( 0, 0 );
    BrowseTheories ( 1, 0 );
  }
}
