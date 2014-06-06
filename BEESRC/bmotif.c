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

FILE * bstdout;

#include "motif.h"

#include "bmotif.h"

#include "appmch.motif.h"

#include "ctxmch.h"

#include "symmch.h"

#include "golmch.h"

#include "tacmch.h"


/* #ifndef BTOOLKIT_FLAG */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/utsname.h>

#include <Xm/XmAll.h>

/* #endif */


/***
Global data
***/

char err_str_buf [ 1000 ];

#ifndef BTOOLKIT_FLAG

#define alloc_init                 500000

#define init_alloc_topup          2000000
#define alloc_topup               2500000


#define compact_cut_off         100000000


int * mmts;
int max_mem = 0;

int max_fwd_ctr_auto_prf = 250;

int up_and_running = 0;

int is_debug = 0;

Dimension wm_width, wm_height;

Widget display_main_menu_dialog, display_a_theory_dialog,
       display_a_rule_dialog,    prove_rule_dialog;

int report_parse_errors = 1;

int display_unproved_btl_flag = 1;
int display_unproved_ipr_flag = 1;

char hyp_search_string [ 250 ];
int btl_rule;

int non_batch_non_compile_mode;

#endif

int ask_hyp_ret = 0;

int ask_eql_hyp_ret = 0;


int from_applicable_rr = 0;

int exit_flag = 0;

int popup_after_time_elapsed = 0;

XmFontList    	fontlist;

Position global_menu_x = -999;
Position global_menu_y = -999;

Position last_browse_x = -999;
Position last_browse_y = -999;

char cur_dir [ 250 ];

Widget curr_dialog_menu,
/* proof_tree_dialog, */
       proof_tree_dialog_form, proof_tree_scroll,
/*       proof_tree_scroll_h, proof_tree_scroll_v, */
       visible_scroll,
       proof_tree_scroll_form, 
       browse_theories_dialog, browse_a_theory_dialog,
       browse_theories_dialog_form, browse_a_theory_dialog_form,
       browse_theories_menu_scroll, browse_a_theory_menu_scroll;

int visible_browse_but_num;
int visible_thy_menu_rule_num = 1;

Pixmap h_pixmap, sv_pixmap, lv_pixmap;

Position global_proof_tree_x, global_proof_tree_y;

int last_node = -1;

Position global_browse_x = 1;
Position global_browse_y = 1;

Position global_query_box_x = -999;
Position global_query_box_y = -999;


Position global_applicable_x = -999;
Position global_applicable_y = -999;

#ifndef BTOOLKIT_FLAG
XmStringCharSet charset = ( XmStringCharSet ) XmSTRING_DEFAULT_CHARSET;
#endif

XtAppContext app;

Display *display;

Screen * proof_screen;

Pixel gray89, gray64, gray39, red, blue,
      Utilities_but_col, Utilities_lab_col,
      lib_but_col,       lib_lab_col,
      gen_but_col,       gen_lab_col,
      user_but_col,      user_lab_col,
      insens_but_col,
      main_text_col,
      option_set_col,    option_not_set_col,
#ifndef BTOOLKIT_FLAG
      Prompt_bck_col,  Prompt_top_col,  Prompt_bot_col,
      Browse_bck_col,  Browse_top_col,  Browse_bot_col,
      Prompt_text_bck_col, Browse_text_bck_col,
      Prompt_but_lab_col, Browse_but_lab_col,
#endif
      ProofTree_bck_col,  ProofTree_top_col,  ProofTree_bot_col;

Pixmap B_framed_pixmap_gray94;

Widget top_level, main_form, main_form_pane,
       top_frame_form, bottom_frame_form,
       constructs_form, constructs_frame,
       TopWin_scroll, TopWin_rc,
       bot_display_frame, main_text, curr_text;

#ifndef BTOOLKIT_FLAG
Widget TRBut [ 1000 + 1 ];
#endif

XmTextPosition main_text_posn, curr_text_posn;


int mc_interval;

int string_box_flag;


int file_sel_flag;


int curr_thy, curr_rule;

#ifndef BTOOLKIT_FLAG

int c_arr [ c_arr_MAX ];

const char *proved_label[] = { "(unproved)",
                         "(proved)",
                         "(proved at previous level)",
                         "(proved at this level)"
		       };

const char *proved_class[] = { "Highlight",
                         "Label",
                         "Label",
                         "Label"
		       };

#endif

void PopdownCurrMenu ();
void Popup_Info ();
void DisplayMainMenu ();
void DisplayMainTopWin ();
void DisplayATheoryMenu ();
void DisplayATheoryTopWin ();
void DisplayARuleMenu ();
void DisplayARuleTopWin ();
void ProveRuleMenu ();
void ClearTopWin ();
void CrePassiveButton ();
void QueryBox ();
void ApplyRuleBox ();
void ProveRuleMenu ();
XtCallbackProc SelRul_CB ();
void BrowseTheories ();
void BrowseATheory ();
void Popup_Error ();
void Popup_Info ();


int loop_do_prf_r,loop_do_prf_p,loop_do_prf_i,loop_do_prf_g,loop_do_prf_j;

int do_prf_t,do_prf_n,do_prf_a,do_prf_p,do_prf_r,do_prf_i,do_prf_l,do_prf_b,do_prf_bbuf ;

int run_man_prf_f,run_man_prf_r,run_man_prf_p,run_man_prf_success,run_man_prf_ff,run_man_prf_fff,run_man_prf_j,run_man_prf_i,run_man_prf_gl,run_man_prf_g,run_man_prf_menu,run_man_prf_run_man_prf_res;

struct sigaction act3;

/*
int global_yes_no;
*/

char pid_buf [ 25 ];

/***
#ifdef suncomputer
***/







#ifdef BTOOL_FLAG

char BKIT_path [ 101 ];
int cs_nn, cs_rr;
char serv_addr [ 20 ];
FILE * Bfile;
int port;

#ifndef BTOOLKIT_FLAG
char buf [ 75000 ];
#endif

pid_t pid;
int Blm_registered = 0;

void ini_Blm ();

static char *numnum[] = { "0",
                       "1",
                       "2",
                       "3",
                       "4",
                       "5",
                       "6",
                       "7",
                       "8",
                       "9"
		     };

#ifndef BTOOLKIT_FLAG

void
CreNumInBuf ( buf, n )
char * buf;
long n;
{
  if ( n < 0 ) {
    n = n * (-1);
    strcat ( buf, "-" );
  }
  if ( n > 9 ) {
    CreNumInBuf ( buf, n/10 );
    strcat ( buf, numnum [ n % 10 ] );
  }
  else {
    strcat ( buf, numnum [ n ] );
  }
}

void
Popup_Minor_Err_CB ( err )
Widget err;
{
  XtPopdown ( XtParent ( err ) );
  XmUpdateDisplay ( XtParent ( err ) );
}

void
Popup_Minor_Err ( parent, text )
Widget parent;
char * text;
{
  Widget err;
  Dimension top_level_w, err_w;

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
    XtVaSetValues ( err,
        XmNsymbolPixmap,           B_framed_pixmap_gray94,
        NULL );
    XtManageChild ( err );
    XtUnmanageChild ( err );

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

  XtVaGetValues ( top_level, 
      XmNwidth,         &top_level_w,
      NULL );
  XtVaGetValues ( err, 
      XmNwidth,         &err_w,
      NULL );
  XtManageChild ( err );

/*
  if   ( parent ) PositionWidgetRelMainWin ( err,
                    ( ( ( int ) top_level_w - ( int ) err_w ) / 2 ), 50 );
  else            PositionWidgetRelMainWin ( err,
                    ( ( ( int ) top_level_w - ( int ) err_w ) / 2 ), 300 );
*/

  XtPopup ( XtParent ( err ), XtGrabNone ); 
  XmUpdateDisplay ( XtParent ( err ) );
}

#endif

void
PadNumInBuf ( buf, n, p )
char * buf;
long n;
int p;
{
  int m;
  if      ( n < 10 )          m = p - 1;
  else if ( n < 100 )         m = p - 2;
  else if ( n < 1000 )        m = p - 3;
  else if ( n < 10000 )       m = p - 4;
  else if ( n < 100000 )      m = p - 5;
  else if ( n < 1000000 )     m = p - 6;
  else if ( n < 10000000 )    m = p - 7;
  else if ( n < 100000000 )   m = p - 8;
  else if ( n < 1000000000 )  m = p - 9;
  if ( p < 0 ) p = 0;
  while ( p ) {
    strcat ( buf, " " );
    p--;
  }
  CreNumInBuf ( buf, n );
}

#ifndef BTOOLKIT_FLAG

#include "../C/ClientSocket.c"

char str_buf [ 75000 ];
int str_buf_i;

#include "../MOTIF/BMotif_version.c"

#endif

/*
char str_buf [ 75000 ];
int str_buf_i;
*/

void
SetTitle ( dir, toolkit_flag )
char * dir;
int toolkit_flag;
{
  XmString xstr;
  int i, j, k, ll;
  char truncated_nodename [ 75 ];

  i = 0;
  j = 0;
  while ( ( nodename [ i ] != '.' ) && ( nodename [ i ] != '\0' ) ) {
    truncated_nodename [ j++ ] =  nodename [ i++ ];
  }
  truncated_nodename [ j ] = '\0';

  ll = strlen ( dir );
  i = ll;
  while ( ( i ) && ( dir [ i ] != '/' ) ) { i--; }
  if ( i ) i++;
  if ( toolkit_flag ) {
    sprintf ( str_buf, "%s@%s:    ", toolkit_ver, truncated_nodename );
  }
  else {
    sprintf ( str_buf, "%s@%s:    ", tool_ver, truncated_nodename );
  }
  k = strlen ( str_buf );
  for ( j = i ; j <= ll ; j++ ) {
    str_buf [ k++ ] = dir [ j ];
  }
  str_buf [ k ] = '\0';
  xstr = XmStringCreateLtoR ( str_buf, charset );
#if ( defined ( SOLARIS_VERSION ) || defined ( SUNOS_VERSION ) || defined ( AIX_VERSION ) )
  XmStringFree ( xstr );
#else
  XmeSetWMShellTitle ( xstr, top_level );
  XmStringFree ( xstr );
#endif
}


void
interrupt_SIGINT ()
{
  Popup_Info ( "   Ouch!   " );
  XmUpdateDisplay ( top_level );  
}

void
GetFonts ()
{
  XmFontListEntry	entry1, entry2, entry3;

  entry1 = XmFontListEntryLoad ( XtDisplay ( top_level ), 
        "-*-courier-*-r-*--*-120-*", XmFONT_IS_FONT, "TAG1" );
  entry2 = XmFontListEntryLoad ( XtDisplay  ( top_level ),
        "-*-courier-bold-o-*--*-140-*", XmFONT_IS_FONT, "TAG2" );
  entry3 = XmFontListEntryLoad ( XtDisplay  ( top_level ),
        "-*-new century schoolbook-medium-r-*--12-*", XmFONT_IS_FONT, "TAG3" );

  fontlist = XmFontListAppendEntry ( NULL, entry1 );
  fontlist = XmFontListAppendEntry ( fontlist, entry2 );
  fontlist = XmFontListAppendEntry ( fontlist, entry3 );

  XmFontListEntryFree ( &entry1 );
  XmFontListEntryFree ( &entry2 );
  XmFontListEntryFree ( &entry3 );
}

#endif /* BTOOL_FLAG */



int query_box_flag;
int query_box_rule;

int util_str_i;

int browse_theories_is_up = 0;
int browse_a_theory_is_up = 0;

int browse_btool_theory_rul;

int curr_menu = 0;

int auto_prf;

/* char buf [ 5000 ]; */

char util_str [ util_str_max + 2 ] [ util_str_max + 2 ];



#ifndef BTOOLKIT_FLAG

#include "macros.c"

#include "trmmch.c"

#include "sysmch.c"

#include "winmch.c"

#include "natmch.c"

#include "ctxmch.c"

#include "ysnmch.c"

#include "seqmch.c"

#include "strmch.c"

#include "symmch.c"

#include "setmch.c"

#include "fncmch.c"

#include "errmch.c"

#include "lexmch.c"

#include "nodmch.c"

#include "frmmch.c"

#include "codmch.c"

#include "resmch.c"

#include "ficmch.c"

#include "outmch.c"

#include "rulmch.c"

#include "themch.c"

#include "filmch.c"

#include "macmch.c"

#include "hypmch.c"

#include "golmch.c"

#include "tacmch.c"

#include "tolmch.c"

#include "shlmch.c"

#include "prfmch.c"

#include "inimch.c"

#include "appmch.motif.c"

#include "motif.c"

#else

#include "prfmch.c.motif"

#endif




bannerfunc()
#define banner bannerfunc()
{
  puts               ( "\n\n" );
  DisplayCurrWinText ( "\n\n" );
  puts               ( btool_name );
  DisplayCurrWinText ( btool_name );
  puts               ( "\n\n" );
  DisplayCurrWinText ( "\n\n" );
  puts               ( toolkit_ver_with_sp );
  DisplayCurrWinText ( toolkit_ver_with_sp );
  puts               ( "\n\n" );
  DisplayCurrWinText ( "\n\n" );
  puts               ( orig_author );
  DisplayCurrWinText ( orig_author );
  puts               ( "\n\n" );
  DisplayCurrWinText ( "\n\n" );
  puts               ( toolkit_copyright );
  DisplayCurrWinText ( toolkit_copyright );
  puts               ( "\n\n" );
  DisplayCurrWinText ( "\n\n" );
}

/*  
   Possible cases for running the BTool are the following:
      b
      b -m
      b -f FILE
      b -m -f FILE
      b -b FILE1 FILE2 ...
      b -m -b FILE1 FILE2 ...
      b -c FILE
      
   Options (-c exclusive with all other; -f,-b are exclusive):
   
      -m: with menu window
      -f: interactive with pre-loading
      -b: batch
      -c: compile (produces .bin file)
      
*/

#ifdef BTOOLKIT_FLAG

exit___ ( nn )
int nn;
{
  int t, i, rr, tot, totp, n, st, lenpob;
  void RestoreBottomForm ();

/***
printf ( " >>>>>>> exit___ ( %d ) <<<<<<<<<<\n", nn );
***/

  tot = 0;
  totp = 0;
  for ( t = first_btl_thy_to_display ; t <= last_btl_thy_to_display ; t++ ) {
    n = nbr_rul_the ( t );
    for ( i = 1 ; i <= n ; i++ ) {
      if ( pvd_rul ( val_rul_the ( t, i ) ) == now_rul ) totp++;
      tot++;
    }
  }
  if ( orig_btl_proved != totp ) {
    Popup_CommitBToolProofs ( top_level );
  }
  else {
    ini;
    for ( i = 1; i < max_proved_rr ; i ++ ) {
      proved_rr [ i ] = 0;
      proved_seq_rr [ i ] = 0;
      proved_seq_sub_rr [ i ] = 0;
      proved_fwd_btl_rr [  i ] = 0;
    }

    PopdownCurrMenu ();
    if ( browse_theories_is_up ) BrowseTheories ( 0, 0 );
    if ( browse_a_theory_is_up ) BrowseATheory ( 0, 0 );

    /***    XtManageChild ( TopWin_scroll );  it's destroyed in the next line! ***/
    XtDestroyWidget ( TopWin_scroll );
    RestoreBottomForm ( 500 );
    val_curMRIState( &st, curr_obj );
    length_pob ( &lenpob, st );
    sprintf ( buf, "\n  BToolProver - nothing proved/committed\n\n  Current Proof Level %d maintained\n  for %s\n", lenpob - 1, GetName ( curr_obj ) );
    DisplayCurrWinText ( buf );
    DisplayNewEnv ( provers_env );
  }
}

exit_btool_prover ()
{
  int i, t, n, tot, totp, st, lenpob;

/***
printf ( " >>>>>>> exit_btool_prover <<<<<<<<<<\n" );
***/

  btool_proofs_committed = 0;

  tot = 0;
  totp = 0;
  for ( t = first_btl_thy_to_display ; t <= last_btl_thy_to_display ; t++ ) {
    n = nbr_rul_the ( t );
    for ( i = 1 ; i <= n ; i++ ) {
      if ( pvd_rul ( val_rul_the ( t, i ) ) == now_rul ) totp++;
      tot++;
    }
  }
  if ( orig_btl_proved != totp ) {
    Popup_CommitBToolProofs ( top_level );
  }
  else {
    val_curMRIState( &st, curr_obj );
    length_pob ( &lenpob, st );
    sprintf ( buf, "\n  BToolProver - nothing proved/committed\n\n  Current Proof Level %d maintained\n  for %s\n", lenpob - 1, GetName ( curr_obj ) );
    DisplayCurrWinText ( buf );
    PrintBToolProofMethod ( 1 ); /* print all pmd rules */
  }
}

exit___contd ( flag, autoproof_flag ) /* flag => proofs committed */
int flag;
{
  int t, i, rr, tot, totp, n;

/***
printf ( " >>>>>>> exit___contd ( %d, %d\n", flag, autoproof_flag );
 ***/

  if ( flag ) {

    DumpNextPOFile ();
    if ( ! autoproof_flag ) {
      DumpRecordedProofs ();
      btool_proofs_committed = 1;
    }

    tot = 0;
    totp = 0;
    for ( t = first_btl_thy_to_display ; t <= last_btl_thy_to_display ; t++ ) {
      n = nbr_rul_the ( t );
      for ( i = 1 ; i <= n ; i++ ) {
        if ( pvd_rul ( val_rul_the ( t, i ) ) == now_rul ) totp++;
        tot++;
      }
    }
    DisplayCurrWinText ( "\n  BToolProver:\n\n" );
    if ( ( totp == orig_btl_proved ) && ( ! autoproof_flag ) ) {
      int st, lenpob;
      val_curMRIState( &st, curr_obj );
      length_pob ( &lenpob, st );
      sprintf ( buf, "\n  BToolProver - nothing proved/committed\n\n  Current Proof Level %d maintained\n  for %s\n", lenpob - 1, GetName ( curr_obj ) );
      DisplayCurrWinText ( buf );
    }
    else {
      if ( totp - orig_btl_proved == 1 ) {
        sprintf ( buf, "%5d proof obligation discharged this Level\n", totp - orig_btl_proved );
      }
      else { /* totp == orig_btl_proved - ie. something proved */
        sprintf ( buf, "%5d proof obligations discharged this Level\n", totp - orig_btl_proved );
      }
      DisplayCurrWinText ( buf );
      if ( orig_btl_proved == 1 ) {
        sprintf ( buf, "%5d proof obligation discharged previously\n", orig_btl_proved );
      }
      else {
        sprintf ( buf, "%5d proof obligations discharged previously\n", orig_btl_proved );
      }
      DisplayCurrWinText ( buf );
      if ( tot - totp == 1 ) {
        sprintf ( buf, "\n%5d proof obligation remains\n", tot - totp );
      }
      else {
      sprintf ( buf, "\n%5d proof obligations remain\n", tot - totp );
      }
      DisplayCurrWinText ( buf );
      n = tot - totp;
      if   ( n == 0 ) n = -999999;
      else            n = (-n);
/***
printf ( "autoprove curr_obj=%d, n=%d (-tot)=%d\n", curr_obj, n, (-tot) );
 ***/
      autoprove ( &rr, curr_obj, n, (-tot) );
      chk_rep ( rr, 175 );
      SetDisplayField_obj_Changed ( curr_obj );
    }
  }

  else { /* not if ( flag ), so here proofs not committed ... */

      int st, lenpob;
      val_curMRIState( &st, curr_obj );
      length_pob ( &lenpob, st );
      sprintf ( buf, "\n  BToolProver - nothing proved/committed\n\n  Current Proof Level %d maintained\n  for %s\n", lenpob - 1, GetName ( curr_obj ) );
      DisplayCurrWinText ( buf );
  }

  if ( autoproof_flag ) {

    ini;
    for ( i = 1; i < max_proved_rr ; i ++ ) {
      proved_rr [ i ] = 0;
      proved_seq_rr [ i ] = 0;
      proved_seq_sub_rr [ i ] = 0;
    }

  }

  else {

    if   ( flag ) PrintBToolProofMethod ( 0 ); /* ask about unused pmd rules */
    else          PrintBToolProofMethod ( 1 ); /* print all pmd rules */

  }
}

exit___contd___finally ()
{
    int i, st, lenpob;
    void RestoreBottomForm ();

/***
printf ( " >>>>>>> exit___contd___finally\n\n" );
***/

    ini;
    for ( i = 1; i < max_proved_rr ; i ++ ) {
      proved_rr [ i ] = 0;
      proved_seq_rr [ i ] = 0;
      proved_seq_sub_rr [ i ] = 0;
    }

    btool_proofs_committed = 0;

    PopdownCurrMenu ();
    XtManageChild ( TopWin_scroll );
    XtUnmanageChild ( bottom_frame_form );
    XtVaSetValues ( bottom_frame_form,
        XmNpaneMinimum,         bottom_frame_form_height,
        NULL );
    XtManageChild ( bottom_frame_form );
    XtVaSetValues ( bottom_frame_form,
        XmNpaneMinimum,         bottom_frame_form_min,
        NULL );
    RestoreBottomForm ( 500 );
    XmUpdateDisplay ( bottom_frame_form );
    XmUpdateDisplay ( top_frame_form );
    XmUpdateDisplay ( main_form_pane );
    XtDestroyWidget ( TopWin_scroll );
    if ( browse_theories_is_up ) BrowseTheories ( 0, 0 );
    if ( browse_a_theory_is_up ) BrowseATheory ( 0, 0 );

    /***
    free mmts
    ***/

#ifdef MALLOC_VERBOSE

printf ( "\n    ---------------------------------------------------\n     free mmts (BMotif): max_mem = %d -> 0\n    ---------------------------------------------------\n", max_mem );

#endif /* MALLOC_VERBOSE */

    max_mem = 0;
    free ( mmts );

    /***
    perform minimum malloc
    ***/
    max_mem = alloc_minimum;
    mmts = ( int * ) malloc ( ( max_mem + 5 ) * sizeof ( int ) );  

#ifdef MALLOC_VERBOSE

printf ( "\n    ---------------------------------------------------\n     mimimum malloc (BMotif): max_mem = %d\n    ---------------------------------------------------\n", max_mem );

#endif /* MALLOC_VERBOSE */

    ini_winfunc ();
    inifunc ();

    val_curMRIState( &st, curr_obj );
    length_pob ( &lenpob, st );
    sprintf ( fifo_write_buf, "%s.%d:%d:0",
                                 GetName ( curr_obj ), lenpob-1, BT_BTL_FINI );
    InvokeB ( without_XTerm, 0 );
}

#else

exit___ ( nn )
int nn;
{
#ifdef BTOOL_FLAG
  if ( Blm_registered ) {
    ClientSocketNUM ( &cs_nn, &cs_rr, fini_request, pid, hi_l, hi_m, hi_h );
    printf ( "\n" );
  }
#endif /* BTOOL_FLAG */

  exit ( nn );

}

#endif /* BTOOLKIT_FLAG */





#ifndef BTOOLKIT_FLAG

void
get_tcpip ()
{   
  get_BToolkitd_tcpip ( BKIT_path );
}

void
ini_Blm_off ()
{
  int Popup_Sel_flag;

  Popup_Sel_flag = 0;

  get_tcpip ();

  pid = getpid ();
  strcpy ( pid_id_file, "/tmp/.B_" );
  CreNumInBuf ( pid_id_file, pid );

  {
    FILE * Bpid_id;
    Bpid_id = fopen ( pid_id_file, "w" );
    if ( Bpid_id == NULL ) {
      printf ( "\n\n  Can't open %s\n\n", pid_id_file );
      exit ( 1 );
    }
    else {
      fclose ( Bpid_id );
    }
  }

  /***
  send hiip_request - hprot now redundant - always ipaddress protection!
  ***/
  ClientSocketNUM ( &cs_nn, &cs_rr, hiip_request, pid, 231, 87, 496 );
  if ( cs_rr < 0 ) {
    Popup_Sel_flag = 1; /* DesensitizeLSTButtons ( 1 ); */  /* 42 */
  }
  else {
    {
      uid_t my_id;
      my_id = getuid ();
      remove_my_zombie_pid ( pid, my_id );
      put_num( &hi_l , &hi_m, &hi_h );


      ClientSocketNUM ( &cs_nn, &cs_rr, pre_init_request, pid, hi_l, hi_m, hi_h );

#ifdef VERBOSE_FLAG
printf ( "\n  pre_init_request: buf = `%s'\n", buf );
#endif /* VERBOSE_FLAG */

      {
	int i = 2; /* ignore initial "ZZ" */
        int p;
        while ( buf [ i ] != '\0' ) {
          p = 0;
          while ( ( buf [ i ] != ' ' ) && ( buf [ i ] != '\0' ) ) {
            p = ( 10 * p ) + buf [ i++ ] - '0';
	  }
          if ( buf [ i ] == ' ' ) i++;

          remove_all_zombie_pid ( p );
          
	}
      }

      /***
      send init_request
      ***/
      ClientSocketNUM ( &cs_nn, &cs_rr, init_request, pid, hi_l, hi_m, hi_h );
      if ( ! ( cs_nn + 4 ) ) {
        Popup_Sel_flag = 6; /* DesensitizeLSTButtons ( 7 ); */ /* 47 */
      }
      else if ( ! ( cs_nn + 3 ) ) {
        Popup_Sel_flag = 8; /* DesensitizeLSTButtons ( 8 ); */ /* 49 */
      }
      else if ( ! cs_nn ) {
        Popup_Sel_flag = 3; /* DesensitizeLSTButtons ( 3 ); */ /* 44 */
      }
      else {
        /***
        send non_count_request
        ***/
        ClientSocketSTR ( &cs_nn, &cs_rr, chk_vers_request, no_toolkit_short_ver, hi_l, hi_m, hi_h );
        ClientSocketNUM ( &cs_nn, &cs_rr, non_count_request, pid, hi_l, hi_m, hi_h );
        if ( ! ( cs_nn + 4 ) ) {
          Popup_Sel_flag = 7; /* DesensitizeLSTButtons ( 7 ); */ /* 48 */
        }
        else if ( ! ( cs_nn + 3 ) ) Popup_Sel_flag = 8; /* DesensitizeLSTButtons ( 8 ); */ /* 49 */
        else if ( ! cs_nn )         Popup_Sel_flag = 2; /* DesensitizeLSTButtons ( 2 ); */ /* 43 */
        else if ( cs_rr / 1000 )    Popup_Sel_flag = 1; /* DesensitizeLSTButtons ( 1 ); */ /* 42 */
        
        ClientSocketNUM ( &cs_nn, &cs_rr, BTd_id_BT_id_check, pid, hi_l, hi_m, hi_h );

        cs_rr = 0;
        j = strlen(cur_BToolkitd_id);
        i = 0;
        while ( i != j ) {
          cs_rr = ( 10 * cs_rr ) + cv2 [ cv1 [ cur_BToolkitd_id [ j - i - 1 ] - '0' ] ];
          i++;
        }

#ifdef VERBOSE_FLAG
    printf ( "\nBTd_id_BT_id_check  cs_nn: %d  cs_rr: %d\n", cs_nn, cs_rr );
#endif /* VERBOSE_FLAG */

        if ( cs_nn != cs_rr )    Popup_Sel_flag = 9; /* DesLSTBut ( 9 ); */ /* 50 */

#ifdef VERBOSE_FLAG
    printf ( "\nuser_uid_request  cs_nn: %d  cs_rr: %d\n", cs_nn, cs_rr );
#endif /* VERBOSE_FLAG */

        ClientSocketNUM ( &cs_nn, &cs_rr, user_uid_request, getuid (), hi_l, hi_m, hi_h );

#ifdef VERBOSE_FLAG
    printf ( "\nuser_name_request  %s  cs_nn: %d  cs_rr: %d\n", cuserid ( NULL ), cs_nn, cs_rr );
#endif /* VERBOSE_FLAG */

    ClientSocketSTR ( &cs_nn, &cs_rr, user_name_request, cuserid ( NULL ), hi_l, hi_m, hi_h );

#ifndef BTOOLKIT_FLAG
/***
printf ( "non_batch_non_compile_mode=%d\n", non_batch_non_compile_mode );
***/
        if ( ( cs_nn ) && ( non_batch_non_compile_mode ) ) {
#else
        if ( cs_nn ) {
#endif
          sprintf ( buf, "\n  You are already running %d B process", cs_nn );
          if ( cs_nn > 1 ) strcat ( buf, "es" );
          strcat ( buf, " on this platform\n" );
          DisplayCurrWinText ( buf );
          sprintf ( buf,
         "\n  To remove *all* your B processes, you may run:\n\n    %s/BProcessInfo\n\n  (but Quit this session first)\n\n", BKIT_path );
          DisplayCurrWinText ( buf );
        }
      }
    }
  }
  DesensitizeLSTButtons ( Popup_Sel_flag + 40 );
  ini_Blm_done = 1;
}

void
ini_Blm ()
{
  int Popup_Sel_flag;

  Popup_Sel_flag = 0;

  DesensitizeLSTButtons ( Popup_Sel_flag + 40 );
  ini_Blm_done = 1;
}

#ifndef BTOOLKIT_FLAG

void
Kill_bplatform_and_exit ( x, y )  /* for ClientSocket */
int x;
int y;
{
  exit ( 1 );
}

#endif

#endif /* BTOOL_FLAG */


BadInitialFile ( filename )
char * filename;
{
  DisplayCurrWinText ( "\n  \"" );
  DisplayCurrWinText ( filename );
  DisplayCurrWinText ( "\" does not end in \".src\" or \".bin\"\n" );
  Popup_Info ( "       Bad initial filename!         " );
}

#ifndef BTOOLKIT_FLAG

char nodename [ 75 ];

#endif


int
nbr_rul_the_from_btoolkit ( n )
{
  return ( nbr_rul_the ( n ) );
}

int
val_rul_the_from_btoolkit ( t, i )
{
  return ( val_rul_the ( t, i ) );
}

void
psh_from_btoolkit ( s, e )
{
  psh ( s, e );
}


#ifndef BTOOLKIT_FLAG

FILE * bstdout;

main ( argc, argv )
int argc;
char *argv[];
{register int i, n, ll;

  /***
  initialise bstdout
  ***/
  bstdout = stdout;

  up_and_running = 0;

  non_batch_non_compile_mode = 1;

  /***
  set is_debug;
  ***/
  is_debug = 0;
  if ( argc == 2 ) {
    if ( strcmp ( argv [ 1 ], "debug" ) == 0 ) is_debug = 1;
  }

  /***
  set up iterrupt handler
  ***/
  act3.sa_handler = interrupt_SIGINT;
  sigemptyset ( & ( act3.sa_mask ) );
  act3.sa_flags = ( int ) 0;
  sigaction ( SIGINT, & act3, NULL );

  mod_men_sys(FALSE);

  if( argc >= 3 ) {

    /***
    -c
    ***/
    if ( ( argc == 3 ) && (argv[1][0]=='-') && (argv[1][1]=='c') ) {
      non_batch_non_compile_mode = 0;

      /***
      perform malloc
      ***/
      max_mem = alloc_init;
      mmts = ( int * ) malloc ( ( max_mem + 5 ) * sizeof ( int ) );  

#ifdef MALLOC_VERBOSE

printf ( "\n    ---------------------------------------------------\n     initial malloc (BMotif): max_mem = %d\n    ---------------------------------------------------\n", max_mem );

#endif /* MALLOC_VERBOSE */

      ini_win;
      ini;
      strcpy(name_load_fil,argv[2]);
      if ( ( strcmp ( name_load_fil, "MakeSetOfRules_BTool.src" ) == 0 ) ||
           ( strcmp ( name_load_fil, "Toolkit15.tmp.src" ) == 0 )           )
        Toolkit15_flag = 1;
      relod_prf;
      strcpy(name_save_fil,argv[2]);
      strcat(name_save_fil,".bin");
      cmp_seq(-999);
      save_comp_tool;
      exit___ ( 0 );
    }

    /***
    -b
    ***/
    if ( ( argc >= 4 ) && (argv[1][0]=='-') && (argv[1][1]=='b') ) {
      non_batch_non_compile_mode = 0;
      mod_batch_sys(TRUE);
      n=2;
      ini_win;

      /***
      perform malloc
      ***/
      max_mem = alloc_init;
      mmts = ( int * ) malloc ( ( max_mem + 5 ) * sizeof ( int ) );  

#ifdef MALLOC_VERBOSE

printf ( "\n    ---------------------------------------------------\n     initial malloc (BMotif): max_mem = %d\n    ---------------------------------------------------\n", max_mem );

#endif /* MALLOC_VERBOSE */

      while( n+1<argc ){
        ini;
        strcpy(name_restore_fil,argv[n]);
        if ( open_restore_batch_fil == FALSE )  exit___ ( 0 );
        restore_tool;
        strcpy(name_fil,argv[n+1]);
        {register int t ;
          xst_the(t,num_the(t)==2,exec_file_prf(t),{});
        }
        n=n+2;
      }
      exit___ ( 0 );
    }
  }

  /***
  get platform
  ***/
  {
    struct utsname u_s;
    if ( uname ( & u_s ) == -1 ) {
      printf ( "\n\n             Problem with \"uname\"\n\n\n" );
      exit ( 1 );
    }
    strcpy ( nodename, u_s.nodename );
  }

  /***
  initialise motif
  ***/
  motif_init( argc, argv );
  pid = getpid ();
  pid_buf [ 0 ] = '\0';
  CreNumInBuf ( pid_buf, pid );

  banner;

  sho_big_gol_prf=TRUE;
  sho_gol_prf=TRUE;
  sho_der_hyp_prf=TRUE;

  /***
  perform malloc
  ***/
  max_mem = alloc_init;
  mmts = ( int * ) malloc ( ( max_mem + 5 ) * sizeof ( int ) );  

#ifdef MALLOC_VERBOSE

printf ( "\n    ---------------------------------------------------\n     initial malloc (BMotif): max_mem = %d\n    ---------------------------------------------------\n", max_mem );

#endif /* MALLOC_VERBOSE */

  ini_win;
  ini;

  if ( ( argc == 3 ) && (argv[1][0]=='-') && (argv[1][1]=='f') ) {
    ll = strlen ( argv [ 2 ] );
    if ( ll >= 5 ) {

      if    ( ( argv [ 2 ] [ ll - 1 ] == 'c' ) &&
              ( argv [ 2 ] [ ll - 2 ] == 'r' ) &&
              ( argv [ 2 ] [ ll - 3 ] == 's' ) &&
              ( argv [ 2 ] [ ll - 4 ] == '.' )    ) {
        FILE * fileptr = fopen ( argv [ 2 ], "r" );
        if ( fileptr == NULL ) {
          DisplayCurrWinText ( "\n  Can't read \"" );
          DisplayCurrWinText ( argv [ 2 ] );
          DisplayCurrWinText ( "\"\n" );
          Popup_Info ( "    Can't read file!        " );
        }
        else {
          fclose ( fileptr );
          DisplayCurrWinText ( "\n  Read \"" );
          DisplayCurrWinText ( argv [ 2 ] );
          DisplayCurrWinText ( "\"\n" );
          strcpy ( name_load_fil, argv [ 2 ] );
          lod_prf;  /* prfmch.c.motif */
        }
      }

      else if ( ( argv [ 2 ] [ ll - 1 ] == 'n' ) &&
                ( argv [ 2 ] [ ll - 2 ] == 'i' ) &&
                ( argv [ 2 ] [ ll - 3 ] == 'b' ) &&
                ( argv [ 2 ] [ ll - 4 ] == '.' )    ) {
        restore_fil = fopen ( argv [ 2 ], "r" );
        if ( restore_fil == NULL ) {
          DisplayCurrWinText ( "\n  Can't read \"" );
          DisplayCurrWinText ( argv [ 2 ] );
          DisplayCurrWinText ( "\"\n" );
          Popup_Info ( "    Can't read file!        " );
        }
        else {
          DisplayCurrWinText ( "\n  Read \"" );
          DisplayCurrWinText ( argv [ 2 ] );
          DisplayCurrWinText ( "\"\n" );
          strcpy ( name_restore_fil, argv [ 2 ] );
          restore_tool;  /* tolmch.c.motif */
        }
      }
      else {
        BadInitialFile ( argv [ 2 ] );
      }
    }
    else {
      BadInitialFile ( argv [ 2 ] );
    }
  }

  DisplayMainMenu ( 1, 0 );
  DisplayMainTopWin ();

/***
{
  int the, tot_thy, nbr;
  for ( the = 2 ; the <= nbr_the ; the++ ) {
    tot_thy = nbr_rul_the ( the );
    for ( nbr = tot_thy ; nbr >= 1 ; nbr-- ) {
      cur_rul = val_rul_the ( the, nbr );
      str_buf [ 0 ] = '\0';
      write_nam_the ( the );
      strcat ( str_buf, "(thy no. ");
      write_nat ( the );
      strcat ( str_buf, ").");
      write_nat ( nbr );
      strcat ( str_buf, ": (");
      write_nat ( cur_rul );
      strcat ( str_buf, ")");
      DisplayCurrWinText ( str_buf );
      app_write_rul ( cur_rul );
      strcat ( str_buf, "\n");
      DisplayCurrWinText ( str_buf );
    }
  }
}
***/

  SetTitle ( cur_dir, 0 );

  up_and_running = 1;
  Popup_Info ( "Initialising BTool" );

  XtAppMainLoop ( app );

}

#endif
