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
#include <Xm/XmAll.h>

#define print_XmNtraversalOn_value(ss,ww) \
{ \
  Boolean bb; \
  XmNavigationType nt; \
  XtVaGetValues ( ww, XmNtraversalOn, &bb, NULL ); \
  if   ( bb == True ) printf ( "%s XmNtraversalOn is True ", ss ); \
  else                printf ( "%s XmNtraversalOn is False ", ss ); \
  XtVaGetValues ( ww, XmNnavigationType, &nt, NULL ); \
  if      ( nt == XmTAB_GROUP ) printf ( " XmTAB_GROUP\n" ); \
  else if ( nt == XmNONE )      printf ( " XmNONE\n" ); \
  else                          printf ( " Xm???\n" ); \
}

#define DAVE_print_frm_nkd(f)     str_buf [ 0 ] = '\0'; \
                                  reset_res(0); \
                                  write_frm_res(f, 0); \
                                  printf ( "|%s|", str_buf )

#define DAVE_print_frm(f)     str_buf [ 0 ] = '\0'; \
                              reset_res(0); \
                              write_frm_res(f, 0); \
                              printf ( "frm %d: |%s|\n", f, str_buf )

#define DAVE_print_frm_sgl(s,f) \
  printf ( "-- DAVE_print_frm_sgl -- %s\n     - ", s ); \
  DAVE_print_frm(f)

#define DAVE_print_frm_lst(s,f) \
{ \
  int k; \
  k = 1; \
  printf ( "-- DAVE_print_frm_lst -- %s -- (len %d)\n", s, len(f) ); \
  while ( k <= len(f) ) { \
    printf ( "    %d - " , k ); \
    DAVE_print_frm(val(f,k)); \
    k++; \
  } \
}




#define DAVE_print_rule(r)     str_buf [ 0 ] = '\0'; \
                               write_hor_short_rul ( r ); \
                               printf ( "rule #%d:\n  %s", r, str_buf )

#define DAVE_print_rule_nl(r)     str_buf [ 0 ] = '\0'; \
                                  write_hor_short_rul ( r ); \
                                  printf ( "rule #%d:\n  %s\n", r, str_buf )

#define DAVE_print_goal(r)     str_buf [ 0 ] = '\0'; \
                               write_gol_prf ( r ); \
                               printf ( "goal #%d:\n  %s", r, str_buf )


/* for Proof_CB_continued */
#define proof_step_flag_NO  0
#define proof_step_flag_YES 1

#define DAVE_print_info_nod(r) \
     { \
       int i, j; \
       strcpy ( str_buf, "---------------------------------\n" ); \
       write_gol_prf ( info_nod ( r ) ); \
       DisplayCurrWinText ( str_buf ); \
       for ( i = 10 ; i <= r ; i++ ) { \
         sprintf ( buf, "node: %d  fath %d  len ( sons ) %d\n", i, fath_nod ( i ), len ( sons_nod ( i ) ) ); \
         DisplayCurrWinText ( buf ); \
         for ( j = 1 ; j <= len ( sons_nod ( i ) ) ; j++ ) { \
           sprintf ( buf, "    son %d\n", val ( sons_nod ( i ), j ) ); \
           DisplayCurrWinText ( buf ); \
	 }  \
       } \
       sprintf ( buf, "---------------------------------\n" ); \
       DisplayCurrWinText ( buf ); \
     }


#define DAVE_print_hyp(r)     str_buf [ 0 ] = '\0'; \
                              write_frm_res(frm_hyp(r),0); \
                              printf ( "hyp #%d (seq #%d):\n  %s\n", r, frm_hyp(r), str_buf )

#define DAVE_print_seq(r)     { int L = vnbs; \
                              str_buf [ 0 ] = '\0'; \
                              write_frm_res(r,0); \
                              if ( L != vnbs ) \
{ printf ( " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ %d -> %d \n", L, vnbs ); } \
                              printf ( "seq #%d (len = %d):\n  %s\n", r, len(r), str_buf ); \
											                     } \

#define DAVE_dead_seq         { int II; \
                                for ( II = ttms ; II > 0 ; II-- ) \
                                  { DAVE_print_seq ( tmbs [ II ] ); } \
                                printf ( "%d in total\n", ttms );\
			      }


#define string_box_new_thy                  1
#define string_box_recompact                2
#define string_box_new_rule                 3
#define string_box_exec_direct              4
#define string_box_exec_file                5
#define string_box_prf_to_file              6
#define string_box_nml_tac_a_theory         7
#define string_box_fwd_tac_a_theory         8
#define string_box_nml_tac_a_rule           9
#define string_box_fwd_tac_a_rule          10
#define string_box_nml_quota               11
#define string_box_fwd_quota               12
#define string_box_move_rule               13
#define string_box_change_rule             14
#define string_box_new_rule_from_browse    15
#define string_box_change_rule_from_browse 16
#define string_box_nml_quota_from_proof    17
#define string_box_fwd_quota_from_proof    18

#define file_sel_flag_load_bin    1
#define file_sel_flag_load_src    2
#define file_sel_flag_save_bin    3

#define  bmotif_top_frame_form_min                50
#define  bmotif_bottom_frame_form_min             50
#define  bmotif_bottom_form_main_length          250
#define  bmotif_bottom_form_proof_length         400
#define  bmotif_bottom_form_proof_tree_length    650

#define ask_hyp_test_hyp1      1
#define ask_hyp_test_hyp2      2
#define ask_hyp_test_imp_hyp1  3
#define ask_hyp_test_imp_hyp2  4

#define ask_eql_hyp_test2_eql   1
#define ask_eql_hyp_test3_eql1  2
#define ask_eql_hyp_test3_eql2  3
#define ask_eql_hyp_test3_unv   4
#define ask_eql_hyp_test2_unv   5

#define allowable_dim_x 12
#define allowable_dim_y 25

#define menu_position_changed_x \
         last_menu_x - wm_width  > global_menu_x + allowable_dim_x || \
         last_menu_x - wm_width  < global_menu_x - allowable_dim_x

#define menu_position_changed_y \
         last_menu_y - wm_height > global_menu_y + allowable_dim_y || \
         last_menu_y - wm_height < global_menu_y - allowable_dim_y \


#ifndef BTOOLKIT_FLAG

int OR_sym;

#define proof_ini_horiz       5
#define proof_ini_vert        5
#define proof_header_height  35
int half_proof_goal_height;
int proof_horiz_offset;
int proof_vert_offset;
int proof_extra_lines_offset;
int goal_rule_vert_diff;

#endif

#define browse_position_changed_x \
         last_browse_x - wm_width  > global_browse_x + allowable_dim_x || \
         last_browse_x - wm_width  < global_browse_x - allowable_dim_x

#define browse_position_changed_y \
         last_browse_y - wm_height > global_browse_y + allowable_dim_y || \
         last_browse_y - wm_height < global_browse_y - allowable_dim_y

#define applicable_position_changed_x \
         last_applicable_x - wm_width  > global_applicable_x + allowable_dim_x || \
         last_applicable_x - wm_width  < global_applicable_x - allowable_dim_x

#define applicable_position_changed_y \
         last_applicable_y - wm_height > global_applicable_y + allowable_dim_y || \
         last_applicable_y - wm_height < global_applicable_y - allowable_dim_y \


#define text_trigger_tot   30000
#define text_rem_tot        2500

#define MAX_num_sel_string    1001

/*
#define write_srv_res        putc(27, bstdout); fprintf ( bstdout, "[7m")

#define write_erv_res        putc(27, bstdout); fprintf ( bstdout, "[0m")

#define write_srv_err_res    putc(27,stderr); fprintf(stderr,"[7m")

#define write_erv_err_res    putc(27,stderr); fprintf(stderr,"[0m")
*/

#define rv_char ( char )     17
#define dollar_char ( char ) 18

#define write_srv_res        str_buf_i = strlen ( str_buf ); \
                             str_buf [ str_buf_i++ ] = rv_char; \
                             str_buf [ str_buf_i ] = '\0'

#define write_erv_res        write_srv_res

#define write_srv_err_res    ;

#define write_erv_err_res    ;

/*
#define write_top_clear_res  putc(27, bstdout); \
                             fprintf ( bstdout, "[1;1H"); \
                             putc(27, bstdout); \
                             fprintf ( bstdout, "[J")
*/
#define write_top_clear_res  ;


/*** 
#endif
  

#ifdef hpcomputer
                        

#define write_srv_res        putc(27, bstdout); fprintf ( bstdout, "&dB")

#define write_erv_res        putc(27, bstdout); fprintf ( bstdout, "&d@")

#define write_srv_err_res    putc(27,stderr); fprintf(stderr,"&dB")

#define write_erv_err_res    putc(27,stderr); fprintf(stderr,"&d@")

#define write_top_clear_res  putc(27, bstdout); fprintf ( bstdout, "H");  putc(27, bstdout); fprintf ( bstdout, "J")

#endif
***/


#define WWW(x,y) fprintf ( bstdout, x, y )

#define OK_BUTTON          1
#define CANCEL_BUTTON      2
#define HELP_BUTTON        3

#define query_box_flag_clear              1
#define query_box_flag_quit               2
#define query_box_flag_rld_src_main       3
#define query_box_flag_rem_thy            4
#define query_box_flag_rem_last_rule      5
/* #define query_box_prf_to_screen           6 */
#define query_box_rem_proof               7
#define query_box_flag_rld_src_a_theory   8
#define query_box_flag_rld_src_a_rule     9
#define query_box_flag_rem_rule          10
#define query_box_ask_ari_prf            11
#define query_box_quit_proof             12
#define query_box_ask_rul_prf            13
#define query_box_ask_eql_rul_prf        14
#define query_box_ask_hyp_prf            15
#define query_box_ask_eql_hyp_prf        16

#define main_menu          1
#define a_theory_menu      2
#define a_rule_menu        3
#define prove_rule_menu    4

#define util_str_max 1000

/*  Maximum Number of SYMBOLS  */
/*  
#define max_sym_val             7500  */

/* #define max_sym_val             12544 */
#define max_sym_val             22528
			     /* multiple of 128? */
 
/*  Maximum Number of THEORIES  */

#define max_the_val              1250
 
/*  Maximum Number of RULES  */

#define max_rul_val             25000
/*  Maximum Number of GOALS  */

#define max_gol_val             45000
 
/*  Maximum Number of NODES  */

/* #define max_nod_val             19000 */
/* #define max_nod_val             25000 */
#define max_nod_val             60000

/*  Maximum Number of TACTICS  */

#define max_tac_val            20000
/*  Maximum Number of HYPOTHESES  */

#define max_hyp_val             3000
/*  Maximum Number of SEQUENCES  */
#define hyp_mod_val             /* max_hyp_val+10 */  10000

#define max_seq_val            225000

/*  Maximum Number of stored proofs  */

#define max_proved_rr_val        100
			     /* MUST be same as in b.c.malloc */

#define btl_proofPV1 max_proved_rr_val
#define btl_proofPV2 (25*max_proved_rr_val)

#ifdef ipaddresses

#define iphid_val 1

#endif


#ifdef hostids

#define iphid_val 0

#endif


/**************************************************************************/

extern char err_str_buf [];

#ifndef BTOOLKIT_FLAG
extern char hyp_search_string [];
extern int btl_rule;
#endif

extern int ask_hyp_ret;

extern int ask_eql_hyp_ret;


extern int from_applicable_rr;

extern int exit_flag;

extern int popup_after_time_elapsed ;

extern XmFontList fontlist;

extern Position global_menu_x, global_menu_y;

extern char cur_dir [];

extern Widget curr_dialog_menu,
/* proof_tree_dialog, */
       proof_tree_dialog_form, proof_tree_scroll,
/*       proof_tree_scroll_h, proof_tree_scroll_v, */
       visible_scroll,
       proof_tree_scroll_form, 
       browse_theories_dialog, browse_a_theory_dialog,
       browse_theories_dialog_form, browse_a_theory_dialog_form,
       browse_theories_menu_scroll, browse_a_theory_menu_scroll;

extern int visible_browse_but_num;
extern int visible_thy_menu_rule_num;

extern Pixmap h_pixmap, sv_pixmap, lv_pixmap;

extern Position global_proof_tree_x, global_proof_tree_y;

extern int last_node;

extern Position global_browse_x, global_browse_y;

extern Position global_query_box_x;
extern Position global_query_box_y;


extern Position global_applicable_x;
extern Position global_applicable_y;

#ifndef BTOOLKIT_FLAG
extern XmStringCharSet charset;
#endif

extern XtAppContext app;

extern Display *display;

extern Screen * proof_screen;

extern Pixel gray89, gray64, gray39, red, blue,
      main_text_col,
      option_set_col,    option_not_set_col,
#ifndef BTOOLKIT_FLAG
      Prompt_bck_col,  Prompt_top_col,  Prompt_bot_col,
      Browse_bck_col,  Browse_top_col,  Browse_bot_col,
      Prompt_text_bck_col, Browse_text_bck_col,
      Prompt_but_lab_col, Browse_but_lab_col,
#endif
      ProofTree_bck_col,  ProofTree_top_col,  ProofTree_bot_col;

extern Pixmap B_framed_pixmap_gray94;

extern Widget top_level, main_form, main_form_pane,
       top_frame_form, bottom_frame_form,
       constructs_form, constructs_frame,
       TopWin_scroll, TopWin_rc,
       bot_display_frame, main_text, curr_text;

#ifndef BTOOLKIT_FLAG
extern Widget TRBut [];
#endif

extern XmTextPosition main_text_posn, curr_text_posn;


extern int mc_interval;

extern int string_box_flag;


extern int file_sel_flag;


extern int curr_thy, curr_rule;
extern int c_arr [];

#ifndef BTOOLKIT_FLAG

extern char *proved_label[];

extern char *proved_class[];

#endif

extern void PopdownCurrMenu ();
extern void Popup_Info ();
extern void DisplayMainMenu ();
extern void DisplayMainTopWin ();
extern void DisplayATheoryMenu ();
extern void DisplayATheoryTopWin ();
extern void DisplayARuleMenu ();
extern void DisplayARuleTopWin ();
extern void ProveRuleMenu ();
extern void ResetTopWin ();
extern void CrePassiveButton ();
extern void QueryBox ();
extern void ApplyRuleBox ();
extern void ProveRuleMenu ();
extern XtCallbackProc SelRul_CB ();
extern void BrowseTheories ();
extern void BrowseATheory ();
extern void Popup_Error ();
extern void Popup_Info ();


int loop_do_prf_r,loop_do_prf_p,loop_do_prf_i,loop_do_prf_g,loop_do_prf_j;

int do_prf_t,do_prf_n,do_prf_a,do_prf_p,do_prf_r,do_prf_i,do_prf_l,do_prf_b,do_prf_bbuf ;

int run_man_prf_f,run_man_prf_r,run_man_prf_p,run_man_prf_success,run_man_prf_ff,run_man_prf_fff,run_man_prf_j,run_man_prf_i,run_man_prf_gl,run_man_prf_g,run_man_prf_menu,run_man_prf_run_man_prf_res;

/**************************************************************************/

#define read_frm_str_buf read_frmfunc_str_buf()
#define ini_prf ini_prffunc()

/**************************************************************************/

extern int browse_theories_is_up;
extern int browse_a_theory_is_up;
extern int browse_btool_theory_rul;
extern int curr_menu;
extern int util_str_i;
extern int query_box_flag;
extern int query_box_rule;
extern int Blm_registered;
extern char util_str [] [ util_str_max + 2 ];
extern int auto_prf;
