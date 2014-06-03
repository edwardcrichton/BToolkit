/* Copyright (c) 1988-96, B-Core (UK) Ltd
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
#define HERE(s) \
  printf ( s "\n");

#define storeStartClock \
  start_c = clock()

#define elapsedClock \
   clock() - start_c

#include "BMotif_globals.h"

#include "BMotif_version.c"

#include "BMotif_help.c"

#include "BMotif_detect.c"

#ifdef BTOOLKIT_FLAG

int brz = 0;

int started_from_cd = 0;

FILE * bstdout;

int * mmts;
int max_mem = 0;

int BOOSTER_link = 0;

/* from trmmch.c */

#define redirect_trm(fstr) \
    bstdout = fopen ( fstr, "w" ); \
    if ( bstdout == NULL ) { \
      fprintf ( stderr, "\n\n             Can't open %s for writing\n\n", fstr ); \
      exit___ ( 1 ); \
    }

#define reappend_trm(fstr) \
    bstdout = fopen ( fstr, "a" ); \
    if ( bstdout == NULL ) { \
      fprintf ( stderr, "\n\n             Can't open %s for appending\n\n", fstr ); \
      exit___ ( 1 ); \
    }

#define reset_trm \
    if ( fclose ( bstdout ) != 0 ) { \
      fprintf ( stderr, "\n\n             Can't close menu window\n\n" ); \
      exit___ ( 1 ); \
    } \
    bstdout = stdout;

#endif

/***
defined in CfgDepCtx.h:

ext:

#define mch         1
#define ref         2
#define imp         3
#define bse         4
#define itf         5
#define enm         6
#define doc         7
#define ops         8
#define mch_prf     9
#define ref_prf    10
#define imp_prf    11
#define map        12

type:

#define usr 1
#define lib 2
#define bse_gen 3
#define enm_gen 4
#define itf_gen 5
#define prf_gen 6
#define usr_vhdl 7
#define gen_vhdl 8
#define lib_vhdl 9
***/

Pixel lab_col_f [ lib_vhdl + 2 ];
Pixel lab_col_b [ lib_vhdl + 2 ];
Pixmap lab_col_pixmap [ lib_vhdl + 2 ]; /* */

/******************************* bit display stuff ******************************/

/*
struct cstr_bit_state * State [];
int StateTotal;
int MallocTotal;
*/

/********************************************************************************/

/*
#define print_tac_info(s) \
printf ( "\n+++++++++++++++++++ %s ++++++++++++++++++++", s ); \
printf ( "\n node %d end_of_tac_prf %d new_tac_prf %d tac_ptr_prf %d\n from_applicable_rr %d\n", run_man_prf_i, end_of_tac_prf, new_tac_prf, tac_ptr_prf, from_applicable_rr ); \
printf ( "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
*/


#ifdef WWW_VERSION

char strip_arr [ 3000 ];
int strip_arr_tot;

#define WWW_Err \
     WWWConstructsCycleCheck ( 1 ); \
     Popup_Err ( 0, "Option not available in WWW Demonstration Release" )

#endif /* WWW_VERSION */

/**************************************************
        "GlobalDefs.src"
***************************************************/

/**************************************************
        global 
***************************************************/

size_t editorsCount=10;
char* editors[10];

textWidgetXeditor* constructEditors[10];
textWidgetXeditor* proofMethodEditors[10];

size_t browsersCount=10;
char* browsers[10];

textWidgetXbrowser* htmlBrowsers[10];

/**************************************************
        global definitions
***************************************************/

char radio_labels [ MAX_RADIO_BUT ] [ MAX_RADIO_BUT_STR ];

int primary_string_len    = 2500;

/**************************************************
          global data
***************************************************/

int SourceControl_Initialised = 0;

struct SourceControlStruct * SC_0 = ( struct SourceControlStruct * ) NULL;

Widget SC_dialog = ( Widget ) NULL;
Widget SC_setup_dialog = ( Widget ) NULL;

int max_fwd_ctr_auto_prf;


int CfgDepBase_is_Restored = 0;

XtIntervalId SRC_watch_id;
long unsigned SRC_watch_cycle = long_SRC_watch_cycle;

int total_edits = 0;

int OR_sym;

char multi_err_str [ 250 ];

char post_process_xterm_text [ 1000 ];

time_t start_t, end_t, start_c, end_c;
Position anm_ops_x = -999;
Position anm_ops_y;
Dimension anm_ops_h = 1;
Dimension anm_ops_w;

int top_level_dep_cstr;

int report_parse_errors = 1;

#ifdef BTOOLKIT_FLAG

Dimension wm_width, wm_height;

Widget display_main_menu_dialog, display_a_theory_dialog,
       display_a_rule_dialog,    prove_rule_dialog;

int display_unproved_btl_flag = 1;
int display_unproved_ipr_flag = 1;

#endif

int upgrade3T04_flag = 0;

int anm_invariant_flag = 0;

int tmp_from_btoolkit = 0;

char fifo_write_buf [ MAX_FIFO_WRITE_BUF ];

Widget global_widget, global_widget1;

char nodename [ 75 ];
char platform [ 12 ];
int platform_ident = 0;

const char *platform_types[] = { "",
                                  "SunOS",
                                  "Solaris",
                                  "OSF1",
                                  "Linux",
                                  "AIX",
                                  "HP-UX"
			         };

int auto_reset_and_remake = 0;
int auto_timer = 0;
int is_debug = 0;
int auto_reset = 0;

int up_and_running = 0;
int interrupt_option = 0;
int file_parses = 0;
int xterm_is_up = 0;
int terminal_option = 0;
int obj_to_display = 0;
int row_to_display = 0;
int current_pmd_ps = 0;
int global_pmd_ps = 0;
int anm_exe_ps = 0;
int sc_ps = 0;
int btl_rule;
char xterm_title [ 250 ];

char buf [ MAX_buf ];

int half_proof_goal_height;
int proof_horiz_offset;
int proof_vert_offset;
int proof_extra_lines_offset;
int goal_rule_vert_diff;

char SwitchBTPXDED0 [ 1000 ];
char SwitchBTPXDED1 [ 1000 ];
char SwitchBTPXDED2 [ 1000 ];

int CopyProofTreeLookUp [ 2 ] [ MaxProofSteps ];
int CopyProofTreeLookUpTot;

int node_to_be_displayed_as_last;
int node_to_undo_to = 0;
int last_goal_displayed_frm = 0;
int run_button_pressed = 0;
int backtrack_attempted = 0;
int backtrack_succeeded = 0;
int another_backtrack_required = 0;

int first_switch_thy, last_switch_thy;
int first_switchBTP_thy, last_switchBTP_thy;
int first_btl_thy_to_display, last_btl_thy_to_display;
int btl_users_thy, fwd_btl_users_thy;
int users_thy, fwd_users_thy;
int last_btl_fwd_thy, last_rewrite_thy, last_lib_thy;
int max_btl_thy_len;
int orig_btl_proved;
int orig_btl_proved_arr [ orig_btl_proved_arr_MAX + 1 ];
int orig_btl_pmd_rule;
int orig_btl_pmd_rule_arr [ orig_btl_pmd_rule_arr_MAX + 1 ];
int btl_fwd_thy_depth [ btl_pob_thy_MAX + 1 ];
int forward_reasoning_depth;


int unwanted_seq;
int btool_proofs_committed;

int btl_fwd_tac_depth = 2;
int feql_val          = 0;

char *btl_fwd_tac[] = {
  REASONING_DEPTH_0_Tac,
  REASONING_DEPTH_1_Tac,
  REASONING_DEPTH_2_Tac,
  REASONING_DEPTH_0_FEQL_Tac,
  REASONING_DEPTH_1_FEQL_Tac,
  REASONING_DEPTH_2_FEQL_Tac  };

pid_t pid;

int cs_nn, cs_rr;
char serv_addr [ 20 ];
FILE * Bfile;
int port;

#ifdef COUNT_VERSION

int cs_nn, cs_rr;
char serv_addr [ 20 ];
int port;
int COUNT_25_flag = 0;
int COUNT_25_msg = 0;

#endif /* COUNT_VERSION */

#ifdef WWW_VERSION

int cs_nn, cs_rr;
char serv_addr [ 20 ];
int port;
int COUNT_25_flag = 0;
int COUNT_25_msg = 0;

int num_usr_constructs       = 0;
int constr_anl_len [ max_num_usr_constr ];
int constr_pob_len [ max_num_usr_constr ];
char constr_nme [ max_num_usr_constr ] [ 50 ];

#endif /* WWW_VERSION */

Widget temp_widget, temp_dialog;
int temp_level;


/***********
current object curr_obj
***********/
int curr_obj;
int anm_thy_obj;

/***********
multi-click interval
***********/
int mc_interval;


/***********
!!!!!!!!!!
***********/
int option;
int not_parse_option = 0;
int commit_aborted = 0;

int translating_pre_MInterface = 0;

Widget cd_dialog = ( Widget ) 0;

int ITF_Intro_basic_io = 0;
int ITF_Intro_basic_io_obj;
int ITF_Intro_basic_io_ps;

int close_all_count;
int close_all_quit_count;
int commit_all_count;
int commit_all_remake_count;
int remove_count;

int dont_destroy_display = 0;

int init_option = 1;

int bell_option = 1;


int widget1_built = 0;

int Popup_Sel_flag = 0;

int Popup_Selection_Sel_flag = 0;

int Commit_All_type;

const char *EnvString[] = {
                       "Main",
                       "Provers",
                       "Generators",
                       "Translators",
                       "Documents",
                       "Animator",
                       "InterProver",
                       "BToolProver"
		     };

Widget env_lab [ EnvString_tot + 3 ];

int curr_env = 999;

/***********
client data
***********/

int c_arr [ c_arr_MAX ];

int global_file_diff_but;


const char *lab_types[] = { "",
                             "UserLab",
                             "LibraryLab",
                             "GeneratedLab",
                             "GeneratedLab",
                             "GeneratedLab",
                             "GeneratedLab",
                             "UserVHDLLab",
                             "GenVHDLLab",
                             "LibVHDLLab"
			   };

const char *extens[] = { "",
                          "mch",
                          "ref",
                          "imp",
                          "bse",
                          "itf",
                          "enm",
                          "doc",
                          "ops",
                          "mch",
                          "ref",
                          "imp",
                          "map"
			};

const char *DIRS[] = { "ANL",
                 "CFG",
                 "HTX",
                 "PMD",
                 "POB",
                 "SRC",
                 "TEX",
                 "TMP",
                 "TYP",
                 "CDE",
                 "CDE/C"
	       };
#define dir_len         11

TopBarMenuItem Overview_menu [] = {
  { "Design",        ( XtPointer ) & c_arr [ 21 ], ( TopBarMenuItem * ) NULL },
  { "Specification", ( XtPointer ) & c_arr [ 22 ], ( TopBarMenuItem * ) NULL },
  { "Construct",     ( XtPointer ) & c_arr [ 23 ], ( TopBarMenuItem * ) NULL },
  { "Help",          ( XtPointer ) & c_arr [ 24 ], ( TopBarMenuItem * ) NULL },
  ( XtPointer ) NULL,
};

const char *PaletteN_pal[] = {
 "Machines.pal",
 "OpsMch.pal",
 "Refinements.pal",
 "OpsRef.pal",
 "Implementations.pal",
 "OpsImp.pal",
 "Bases.pal",
 "Documents.pal",
 "Enumerations.pal",
 "Interfaces.pal"
};

TopBarMenuItem PaletteN_menu [] = {
  { "Machines",           ( XtPointer ) & c_arr [ 0 ], ( TopBarMenuItem * ) NULL },
  { "Machine Ops",        ( XtPointer ) & c_arr [ 1 ], ( TopBarMenuItem * ) NULL },
  { "Refinements",        ( XtPointer ) & c_arr [ 2 ], ( TopBarMenuItem * ) NULL },
  { "Refinement Ops",     ( XtPointer ) & c_arr [ 3 ], ( TopBarMenuItem * ) NULL },
  { "Implementations",    ( XtPointer ) & c_arr [ 4 ], ( TopBarMenuItem * ) NULL },
  { "Implementation Ops", ( XtPointer ) & c_arr [ 5 ], ( TopBarMenuItem * ) NULL },
  { "Bases",              ( XtPointer ) & c_arr [ 6 ], ( TopBarMenuItem * ) NULL },
  { "Documents",          ( XtPointer ) & c_arr [ 7 ], ( TopBarMenuItem * ) NULL },
  { "Enumerations",       ( XtPointer ) & c_arr [ 8 ], ( TopBarMenuItem * ) NULL },
  { "Interfaces",         ( XtPointer ) & c_arr [ 9 ], ( TopBarMenuItem * ) NULL },
  ( XtPointer ) NULL,
};

TopBarMenuItem Browse_menu [] = {
  { "Hypertext", ( XtPointer ) & c_arr [ 10 ], ( TopBarMenuItem * ) NULL },
  { "Overview",  ( XtPointer ) NULL,           Overview_menu },
  { "Palette",   ( XtPointer ) NULL,           PaletteN_menu },
  ( XtPointer ) NULL,
};

TopBarMenuItem Remake_menu [] = {
  { "All Constructs", ( XtPointer ) & c_arr [ 0 ], ( TopBarMenuItem * ) NULL },
  { "Construct(s)",   ( XtPointer ) & c_arr [ 1 ], ( TopBarMenuItem * ) NULL },
  { "Help",           ( XtPointer ) & c_arr [ 2 ], ( TopBarMenuItem * ) NULL },
  ( XtPointer ) NULL,
};

TopBarMenuItem IntroduceNew_menu [] = {
  { "Machine",                              ( XtPointer ) & c_arr [ 10 ], ( TopBarMenuItem * ) NULL },
  { "Refinement",                           ( XtPointer ) & c_arr [ 11 ], ( TopBarMenuItem * ) NULL },
  { "Refinement of analysed construct",     ( XtPointer ) & c_arr [ 12 ], ( TopBarMenuItem * ) NULL },
  { "Implementation",                       ( XtPointer ) & c_arr [ 13 ], ( TopBarMenuItem * ) NULL },
  { "Implementation of analysed construct", ( XtPointer ) & c_arr [ 14 ], ( TopBarMenuItem * ) NULL },
  { "Base",                                 ( XtPointer ) & c_arr [ 15 ], ( TopBarMenuItem * ) NULL },
  { "Enumeration",                          ( XtPointer ) & c_arr [ 16 ], ( TopBarMenuItem * ) NULL },
  { "Enumeration of analysed machine(s)",   ( XtPointer ) & c_arr [ 17 ], ( TopBarMenuItem * ) NULL },
  { "Interface",                            ( XtPointer ) & c_arr [ 18 ], ( TopBarMenuItem * ) NULL },
  { "Interface of implemented machine",     ( XtPointer ) & c_arr [ 19 ], ( TopBarMenuItem * ) NULL },
  { "Document",                             ( XtPointer ) & c_arr [ 20 ], ( TopBarMenuItem * ) NULL },
  { "Document of configured constructs",    ( XtPointer ) & c_arr [ 21 ], ( TopBarMenuItem * ) NULL },
  { "Help",                                 ( XtPointer ) & c_arr [ 22 ], ( TopBarMenuItem * ) NULL },
  ( XtPointer ) NULL,
};

TopBarMenuItem Introduce_menu [] = {
  { "New",            ( XtPointer ) NULL,          IntroduceNew_menu },
  { "From SRC",       ( XtPointer ) & c_arr [ 0 ], ( TopBarMenuItem * ) NULL },
  { "From SLIB",      ( XtPointer ) & c_arr [ 1 ], ( TopBarMenuItem * ) NULL },

/*
  { "From TLIB",      ( XtPointer ) & c_arr [ 2 ], ( TopBarMenuItem * ) NULL },
*/

  { "Help",           ( XtPointer ) & c_arr [ 3 ], ( TopBarMenuItem * ) NULL },
  ( XtPointer ) NULL,
};

/* not actually used, but callback numbers valid */
TopBarMenuItem Optional_Utilities_menu [] = {
  { "Optional Utility 1"   , ( XtPointer ) & c_arr [ 24 ],  ( TopBarMenuItem * ) NULL },
  { "Optional Utility 2"   , ( XtPointer ) & c_arr [ 25 ],  ( TopBarMenuItem * ) NULL },
  { "Optional Utility 3"   , ( XtPointer ) & c_arr [ 26 ],  ( TopBarMenuItem * ) NULL },
  { "Optional Utility 4"   , ( XtPointer ) & c_arr [ 27 ],  ( TopBarMenuItem * ) NULL },
  { "Optional Utility 5"   , ( XtPointer ) & c_arr [ 28 ],  ( TopBarMenuItem * ) NULL },
  ( XtPointer ) NULL,
};

TopBarMenuItem Utilities_menu [] = {
  { "Release Information"   ,                ( XtPointer ) & c_arr [ 7 ],  ( TopBarMenuItem * ) NULL },
  { "Current Development Directory",         ( XtPointer ) & c_arr [ 5 ],  ( TopBarMenuItem * ) NULL }, /* */
  { "Create / Change Development Directory", ( XtPointer ) & c_arr [ 6 ],  ( TopBarMenuItem * ) NULL }, /* */
  { "Save in Remakable Form",                ( XtPointer ) & c_arr [ 2 ],  ( TopBarMenuItem * ) NULL },
  { "Find Identifier",                       ( XtPointer ) & c_arr [ 1 ],  ( TopBarMenuItem * ) NULL },
  { "Shell",                                 ( XtPointer ) & c_arr [ 0 ],  ( TopBarMenuItem * ) NULL },
  { "Optional Utility",                      ( XtPointer ) NULL,            Optional_Utilities_menu },
  { "Exit",                                  ( XtPointer ) & c_arr [ 3 ],  ( TopBarMenuItem * ) NULL },
  { "Help",                                  ( XtPointer ) & c_arr [ 4 ],  ( TopBarMenuItem * ) NULL },
  ( XtPointer ) NULL,
};

TopBarMenuItem Construct_menu [] = {
  { "Close All Open Constructs",       ( XtPointer ) & c_arr [ 0 ],  ( TopBarMenuItem * ) NULL },
  { "Dummy",                           ( XtPointer ) NULL,  ( TopBarMenuItem * ) NULL },
  { "Commit All Updated Constructs",   ( XtPointer ) & c_arr [ 15 ],  ( TopBarMenuItem * ) NULL },
  { "Commit All Updated Open Constructs", ( XtPointer ) & c_arr [ 1 ],  ( TopBarMenuItem * ) NULL },
  { "Dummy",                           ( XtPointer ) NULL,  ( TopBarMenuItem * ) NULL },
  { "Analyse/Generate All Constructs", ( XtPointer ) & c_arr [ 34 ],  ( TopBarMenuItem * ) NULL },
  { "Analyse/Generate & Translate All Constructs", ( XtPointer ) & c_arr [ 36 ],  ( TopBarMenuItem * ) NULL },
  { "Dummy",                           ( XtPointer ) NULL,  ( TopBarMenuItem * ) NULL },
  { "Reset All Constructs",            ( XtPointer ) & c_arr [ 2 ],  ( TopBarMenuItem * ) NULL },
  { "Dummy",                           ( XtPointer ) NULL,  ( TopBarMenuItem * ) NULL },
  { "Remove Construct(s)",             ( XtPointer ) & c_arr [ 6 ],  ( TopBarMenuItem * ) NULL },
  { "Remove All Unused LIB Constructs", ( XtPointer ) & c_arr [ 7 ],  ( TopBarMenuItem * ) NULL },
  { "Remove All Marked-up Documents",   ( XtPointer ) & c_arr [ 3 ],  ( TopBarMenuItem * ) NULL },
  { "Remove All Code",                  ( XtPointer ) & c_arr [ 4 ],  ( TopBarMenuItem * ) NULL },
  { "Remove All Code & Recompile SLIB Code", ( XtPointer ) & c_arr [ 35 ],  ( TopBarMenuItem * ) NULL },
  { "Remove All Proofs",                  ( XtPointer ) & c_arr [ 33 ],  ( TopBarMenuItem * ) NULL },
  { "Dummy",                           ( XtPointer ) NULL,  ( TopBarMenuItem * ) NULL },
  { "Rename Construct",                ( XtPointer ) & c_arr [ 5 ],  ( TopBarMenuItem * ) NULL },
  { "Dummy",                           ( XtPointer ) NULL,  ( TopBarMenuItem * ) NULL },
  { "Create SLIB Construct",           ( XtPointer ) & c_arr [ 8 ],  ( TopBarMenuItem * ) NULL },
  { "Delete Library Construct from SLIB",           ( XtPointer ) & c_arr [ 13 ],  ( TopBarMenuItem * ) NULL },
  { "Dummy",                           ( XtPointer ) NULL,  ( TopBarMenuItem * ) NULL },

  /*
  { "Create TLIB Construct",        ( XtPointer ) & c_arr [ 9 ],  ( TopBarMenuItem * ) NULL },
  { "Remove TLIB Construct",        ( XtPointer ) & c_arr [ 14 ],  ( TopBarMenuItem * ) NULL },
  */

  { "Source Control Setup",            ( XtPointer ) & c_arr [ 29 ],  ( TopBarMenuItem * ) NULL },
  { "Source Control",                  ( XtPointer ) & c_arr [ 30 ],  ( TopBarMenuItem * ) NULL },
  { "Help",                            ( XtPointer ) & c_arr [ 10 ], ( TopBarMenuItem * ) NULL },
  ( XtPointer ) NULL,
};

TopBarMenuItem Interrupt_menu [] = {
  ( XtPointer ) NULL,
};

/***
interrupts
***/
struct sigaction act1, act2, act3;

int anm_thy_ps = 0;

XmStringCharSet charset = ( XmStringCharSet ) XmSTRING_DEFAULT_CHARSET ;

XtAppContext app;

Widget top_level,          main_form,            top_bar;

Widget main_form_pane;

Dimension bottom_frame_form_height;

Widget top_frame_form,    bottom_frame_form,
       B_button,          B_label,
       bot_display_frame,
       ipr_text_dialog,   anm_text_dialog,
       ipr_text_form,     anm_text_form,
       main_text,         ipr_text,             anm_text,        curr_text,
       ipr_hyp_dialog,    ipr_hyp_dialog_text,  ipr_hyp_sch_dialog [ 10 ],
       constructs_frame,  constructs_form,
       main_row_scroll,     provers_row_scroll,  generators_row_scroll,
       translators_row_scroll, documents_row_scroll,
       main_row_form,     provers_row_form,  generators_row_form,
       translators_row_form, documents_row_form,
       /* */ information_label,
       constructs_scroll, constructs_rc,  ipr_label,
       ipr_sel_rc,
                          sub_text1,
                          sub_text2,
                          sub_text3,
       InterruptPullDown,
       OptionsPullDown,   InterruptPullDown,    BrowsePullDown,
       UtilsPullDown,     RemakePullDown,       ConstructPullDown,
       IntroducePullDown, HelpPullDown,
       Utils_Options_PullDown, Utils_Options_PullDown_PushButtons [ 6 ];

Widget sub_frame1 = ( Widget ) NULL;
Widget sub_frame2 = ( Widget ) NULL;
Widget sub_frame3 = ( Widget ) NULL;
Widget sub_dummy  = ( Widget ) NULL;

Widget TRBut [ 1000 + 1 ];
char str_buf [ MAX_str_buf + 5 ];
int str_buf_i;
int tmp_btool_ipr_thy;

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

char prev_thy [ sel_str_len_MAX ];
int  prev_rule = 0;

int ipr_hyp_dialog_up, ipr_hyp_sch_dialog_up [ 10 ];

int Ipr_Prf_Level_dialog_isdplayed = 0;
int Ipr_Prf_Option = 0;
char hyp_search_string [ 250 ];

Widget command_bar_rc,
       help_main_lab,
       main_lab_form,  provers_lab_form, 
       generators_lab_form, translators_lab_form,
       documents_lab_form, cmt_documents_lab, dmu_lab, shw_lab,
       prt_lab, doc_rst_lab,
       sts_lab, rst_lab, edt_documents_lab,
       cmt_main_lab, cmt_provers_lab, cmt_generators_lab, cmt_translators_lab,
       edt_main_lab, edt_provers_lab, edt_generators_lab, edt_translators_lab,
       anl_lab,  pog_lab,  anm_lab, pmd_lab,
       prv_lab,
       rsl_lab,
       ppf_lab, sup_lab,  lvl_lab, pob_lab, tot_lab,
       gbo_lab,  gbm_lab,  enm_lab, itf_lab, gen_rst_lab,
       trl_lab,  lnk_lab, exe_lab, trl_rst_lab;

Widget ipr_ops_dialog = ( Widget ) 0;

Widget anm_ops_dialog = ( Widget ) 0;

int anm_ops_option;

Widget htx_curr_form, htx_curr_form_lab,
       htx_B_logo,
       htx_label, htx_prev_but, htx_done_but, htx_help_but,
       htx_spec_but, htx_design_but, htx_save_but, 
       htx_dialog, htx_frame, htx_form, htx_scroll, htx_scroll_form,
       htx_down_arw, htx_up_arw,
       curr_htx, curr_htx_frame, curr_htx_inner_frame, curr_htx_but,
       curr_htx_rc, curr_htx_form, curr_htx_dialog,
       ipts_htx_rc, sees_htx_rc;

int htx_dialog_is_up;

Pixmap B_framed_pixmap_gray94, B_framed_pixmap_inverse, B_topbar_pixmap, red_pixmap, green_pixmap, blue_pixmap,
       inapplicable_pixmap, tab_pixmap, tabgrey_pixmap, B_downarrow_pixmap,
       htx_pixmap_right, htx_pixmap_left, htx_pixmap_left_big;

Dimension HtxDialog_x = 0;
Dimension HtxDialog_y = 0;

Widget curr_htx_a2c_frame [ MAX_a2c_htx ], curr_htx_a2c [ MAX_a2c_htx ];
int  curr_htx_a2c_tot;
int  curr_htx_a2c_open_idx;

Widget sees_htx_rc_sub [ MAX_sees_htx + 1 ],
       sees_htx_a2c_frame [ MAX_sees_htx + 1 ] [ MAX_a2c_htx ],
       sees_htx_a2c [ MAX_sees_htx + 1 ] [ MAX_a2c_htx ];

int    sees_htx_a2c_Total, sees_htx_a2c_tot [ MAX_sees_htx ];

Widget ipts_htx_rc_sub [ MAX_ipts_htx + 1 ],
       ipts_htx_a2c_frame [ MAX_ipts_htx + 1 ] [ MAX_a2c_htx ],
       ipts_htx_a2c [ MAX_ipts_htx + 1 ] [ MAX_a2c_htx ];

Widget left_big_arr_htx [ MAX_ipts_htx + 1 ] [ MAX_a2c_htx ];

int    ipts_htx_a2c_Total, ipts_htx_a2c_tot [ MAX_ipts_htx ];

int htx_curr_obj [ MAX_htx_curr_obj ];
int htx_curr_obj_ptr;

int htx_offset;
int tot_htx_constructs, tot_htx_blocks, tot_htx_rows;

int D_arr        [ MAX_D_row ] [ MAX_D_block ] [ MAX_D_cell ];
int D_block_tot  [ MAX_D_row ] [ MAX_D_block ];
int D_node       [ MAX_D_row ] [ MAX_D_block ];
int D_frame      [ MAX_D_row ] [ MAX_D_block ];
int D_sticky     [ MAX_D_row ] [ MAX_D_block ];

int D_cell;
int D_block [ MAX_D_row ];

int D_arr_load_err;

int initial_reattachment;

/***
used in display
***/
int HtmlMasterFileChanged = 0;
int DisplayChanged = 0;

Display *display;

Screen * proof_screen;

char * primary_string;
char * secondary_string;
char * additional_string;

char SRCName    [ MAX_SRCName ];
char CFGName    [ MAX_CFGName ];

char   sel_str_arr [ sel_arr_MAX + 5 ] [ sel_str_len_MAX ];
char   rmk_str_arr [ sel_arr_MAX + 5 ] [ sel_str_len_MAX ];
int    sel_obj_arr [ sel_arr_MAX + 5 ];
short  sel_arr_tog [ sel_arr_MAX + 5 ];
Widget sel_arr_but [ sel_arr_MAX + 5 ];
int    sel_arr_tot;

int hid_LIB_flag;
int hid_gen_flag;

/***
 should agree with #define OPTIONS_REMAKE etc in BMotif_widgets.c
***/

const char *options[] = { "Remake",
                    "Construct Display",
                    "Editors/Viewers/Shell",
                    "Documents",
                    "Translators/Compilers",
                    "Provers",
                    "Interface",
                    "Bell",
                    "Source Control",
                    "Save Current Options As Global",
                    "Set Current Options From Global",
                    "Optional Utilities"
                    };

char BKIT_path [ 101 ];
char cur_dir [ 250 ];

Pixel gray94, gray64, gray39, red, blue, black,
      user_lab_col_f,      user_lab_col_b,
      lib_lab_col_f,       lib_lab_col_b,
      gen_lab_col_f,       gen_lab_col_b,
      user_vhdl_lab_col_f, user_vhdl_lab_col_b,
      gen_vhdl_lab_col_f,  gen_vhdl_lab_col_b,
      lib_vhdl_lab_col_f,  lib_vhdl_lab_col_b,
      inapplicable_lab_col,      main_text_col,
      option_set_col,      option_not_set_col,
      Prompt_bck_col,      Prompt_top_col,  Prompt_bot_col,
      Browse_bck_col,      Browse_top_col,  Browse_bot_col,  
      Prompt_text_bck_col, Browse_text_bck_col,
      Prompt_but_lab_col,  Browse_but_lab_col,
      Prompt_bck_col,
      Env_lab_active,      Env_lab_passive;

/* Pixel but_xpm; */

int rewrite_prompt = 0;


/**************************************************
               interrupts etc
***************************************************/

int go_flag = 0;
int ReturnFromB_option;

XtIntervalId InvokeBLogoFlashTimer_id;
int          InvokeBLogoFlashTimer_flag = -1;

/**************************************************
     internal procedures
***************************************************/

int committed;

/**************************************************
     socket procedures & data
***************************************************/

int fifo_write_ptr, fifo_read_ptr;
char fifo_file_2m [ 50 ];
char fifo_file_2b [ 50 ];

/**************************************************
     Utilities
***************************************************/

int waiting_option;
int second_visit;
int SelOne_flagged;

XmTextPosition main_text_posn, ipr_text_posn, anm_text_posn, curr_text_posn;

/*****************************************************
******************************************************
                  radiobox dialogs
******************************************************
*****************************************************/

/*******************************
 radiobox dialog callbacks
*******************************/

int errorbox_flag = 0;

int radiobox_flag = 0;

int confirm_flag = 0;
