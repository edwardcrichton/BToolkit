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

#include "motif.h"

#include "bmotif.h"

#include "ctxmch.h"

#include "symmch.h"

#include "golmch.h"


/***

  proving t.n

  r  run_man_prf_r     val_rul(t,n)
  g  run_man_prf_g     info_nod ( run_man_prf_i )
  p  run_man_prf_p     cre_root_gol ( g )                  (the top node)
  i  run_man_prf_i     the current value of run_man_prf_p  (current node)
 ( i is sometimes n )
  f = frm_gol ( run_man_prf_g );

***/

/***

  proof are stored externally in the base:

    BASE
      btl_prf
    MANDATORY
      pob_thy_str   : STRING[25];
      pob_nn        : NAT;
      reason_depth  : NAT;
      prf_seq       : SEQ(prf_seq_stp)[25]
    END;

        pob_thy_str  = write_nam_the ( the_rul ( proved_rr [ i ] ) )
        pob_nn       = num_rul ( proved_rr [ i ] )
        reason_depth = val ( proved_seq_rr [ i ], 1 )        

    BASE
      prf_seq_stp
    MANDATORY
      stp_type     : NAT;
      stp_thy_str  : STRING[25];
      stp_rule_str : STRING[100];
      stp_posn     : NAT           posn of rewrite in goal
    END

        stp_type     = val ( proved_seq_rr [ i ], j )
            < 0          => Lemma, (proved_seq_rr contains the rule)
            <= max_rul   => Rule
            <= 2*max_rul => spe_gol
            else         => frm_gol
        stp_thy_str  = write_nam... ( the_rul ( val ( proved_seq_rr [ i ], j ) )  ) [Rule]
                       ""                                                           [else]
        stp_rule_str = write_ver... ( val ( proved_seq_rr [ i ], j ) )         [Rule]
                       write_frm... ( val ( proved_seq_hyp_rr [ i ], j ), 0 ); [HYP]
                       ""                                                      [else]
        stp_posn     = val ( proved_seq_sub_rr [ i ], j )



  internally:

    each proved_rr [ i ] contains the proved rule rr [pob_thy_str.pob_nn]

    each proved_seq_rr [ i ] contains the sequence (prf_seq):

    each proved_seq_breade_rr [ i ] contains the sequence gbreade

    each proved_fwd_btl_rr [ i ] contains the fwd_btl_users_thy rules used in
                                 the proof of proved_rr [ i ]


      reason_depth         [reason_depth]
    then (repeated):
      op:                  [stp_thy_str,stp_rule_str]
        rr (the proof rule, if rr<=max_rul, rr=op)
      or
        spe_gol (AND, etc, if spe_gol< 2*max_rul, spe_gol = op-max_rul )
      or
        frm_gol (otherwise, frm_gol = op-2*max_rul)
      op repeats


    each proved_seq_sub_rr [ i ] contains the sequence (prf_seq_sub):

      reason_depth         [reason_depth]
    then (repeated):
      rewrite_posn         [stp_posn]


    each proved_seq_hyp_rr [ i ] contains the sequence (prf_seq_hyp):

      reason_depth         [reason_depth]
    then (repeated):
      hyp_frm              [stp_rule_str]


    in the case when rr is a rewrite rule, or spe_gol is ARI or HYP
    the corresponding value of the sequence in the proved_seq_sub_rr entry
    (rewrite_posn) provides the leaf number of the current goal for the
    rewrite. In the case of HYP, hyp_frm provides the HYP frm; otherwse
    hyp_frm is 0.

    During proof, pssubrr [ i ]/hyp_mod_val corrresponds to the number
    of the hypothesis, and  pssubrr [ i ]%hyp_mod_val to rewrite_posn,
    when the step is HYP.

***/

/***

BToolLemmas source rules are stored in btl_lem_num [], btl_lem_rul []
 if btl_lem_num [ xx ] != 0
    btl_lem_num [ xx ] = rr &
    btl_lem_rul [ xx ] = 1796
   =>
    BToolLemmas.nn created in proof of rule 1796
      where rr = val_rul_the ( last_btl_thy_to_display, nn )

***/


/*****************************************************************************/

#define print_tac_info(s) \
printf ( "\n+++++++++++++++++++ %s ++++++++++++++++++++", s ); \
printf ( "\n node %d end_of_tac_prf %d new_tac_prf %d tac_ptr_prf %d\n from_applicable_rr %d\n", run_man_prf_i, end_of_tac_prf, new_tac_prf, tac_ptr_prf, from_applicable_rr ); \
printf ( "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );

# define print_recorded_proofs \
{ \
  int i, j, l; \
  printf ( "\n------------------------------------------------------------" ); \
  printf ( "\n---------------------- recorded proofs ----------------------\n" ); \
  for ( i = 1 ; i < max_proved_rr ; i++ ) { \
    if ( proved_rr [ i ] ) { \
      str_buf [ 0 ] = '\0'; \
      write_nam_the ( the_rul ( proved_rr [ i ] ) ); \
      printf ( "%s.%d (%d):\n", str_buf, num_rul ( proved_rr [ i ] ), proved_rr [ i ] ); \
      str_buf [ 0 ] = '\0'; \
      write_ver_rul_dave ( proved_rr [ i ] ); \
      printf ( "%s\n", str_buf ); \
      printf ( "   array index %d: %d", i, proved_rr [ i ] ); \
      l = len ( proved_seq_rr [ i ] ); \
      for ( j = 1 ; j <= l ; j++ ) { \
        printf ( " %d %d", val ( proved_seq_rr [ i ], j ), val ( proved_seq_sub_rr [ i ], j ) ); \
      } \
      printf ( "\n-------------------- end recorded proofs --------------------\n" ); \
      printf ( "------------------------------------------------------------\n\n" ); \
    } \
  } \
}

/***
print_hyp_len(ss,node) \
{ \
  int s; \
  if ( node != -999 ) { \
    s=cre(50); \
    strcpy ( buf, str_buf ); \
    str_buf [ 0 ] = '\0'; \
    lst_hyp_prf(run_man_prf_p,node,s); \
    printf ( " node %d(top %d):  hyp len: %d (%s)\n", node, run_man_prf_p, len ( s ), ss ); \
    kil(s); \
    strcpy ( str_buf, buf ); \
  } \
}
***/

/*****************************************************************************/

print_goal_into_str_buf ( goal ) 
{
  str_buf [ 0 ] = '\0';
  write_frm_first_prooftree_goal ( frm_gol ( goal ) );
}





cre_instant_rule ( rr )
{
  int i, a, c, s, f;

/***
print_live_seq ( "cre_instant_rule 1" );
***/
  str_buf [ 0 ] = '\0';
  a=ant_rul(rr);
  c=cns_rul(rr);
  if( len(a)!=0 ) {
    i = 1;
    while ( i <= len(a) ) {
      s = prd_tree(val(a,i));
      strcat ( str_buf, "(" );
      write_frm_res(s,0);
      strcat ( str_buf, ")" );
      kil(s);
      if ( i < len(a) ) strcat ( str_buf, "&" );
      i++;
    }
      strcat ( str_buf, "=>" );
  }
  s = prd_tree(c);
  strcat ( str_buf, "(" );
  write_frm_res(s,0);
  strcat ( str_buf, ")" );
  kil(s);
  s = read_frm_str_buf;
  if ( s!= -999 ) {
    str_buf [ 0 ] = '\0';
    reset_res ( 0 );
    write_frm_res_dave(s);
    kil(s);
  }
  else {
    Popup_Info ( "Problems showing instantiation of rule" );
  }
/***
printf ( "instantiated rule:\n|%s|\n", str_buf );
print_live_seq ( "cre_instant_rule 2" );
***/
}

cre_instant_hyp ( hf )
{
  int i, a, c, s, f;
/***
printf ( "cre_instant_hyp ( hf=%d )\n", hf ); fflush ( stdout );
***/
/***
print_live_seq ( "cre_instant_hyp 1" );
***/
  str_buf [ 0 ] = '\0';
  s = prd_tree(hf);
  strcat ( str_buf, "(" );
  write_frm_res(s,0);
  strcat ( str_buf, ")" );
/***
printf ( "str_buf=%s\n", str_buf ); fflush ( stdout );
***/
  kil(s);
  s = read_frm_str_buf;
  if ( s!= -999 ) {
    str_buf [ 0 ] = '\0';
    reset_res ( 0 );
    write_frm_res(s,0);
    kil(s);
  }
  else {
    Popup_Info ( "Problems showing instantiation of hypothesis" );
  }
/***
printf ( "instantiated rule:\n|%s|\n", str_buf );
print_live_seq ( "cre_instant_hyp 2" );
***/
}



/*****************************************************************************/

search_theory ( thy, str_ptr )
int thy;
char * str_ptr;
{
  int f1, f2, rr, nn, found, tot_rul;

/***
printf ( "\n*********************************** search_theory: thy=%d - ", thy );
str_buf [ 0 ] = '\0';
write_nam_the ( thy );
printf ( "%s\n", str_buf );
***/

  found = -999;
  strcpy ( str_buf, str_ptr );
  f1 = read_frm_str_buf;
  if ( f1 != -999 ) {
    tot_rul = nbr_rul_the ( thy );
/***
str_buf [ 0 ] = '\0';
write_frm_res ( f1, 0 );
printf ( "looking for (tot_rul %d):`%s'", tot_rul, str_buf );
***/
    nn = 1;
    while ( ( found == -999 ) && ( nn <= tot_rul ) ) {
      rr = val_rul_the ( thy, nn );
      f2 = cre_rec_rul ( rr );
/***
str_buf [ 0 ] = '\0';
write_frm_res ( f2, 0 );
printf ( "\n  Checking: \n  `%s'\n", str_buf );
***/
      if ( eql_frm ( f1, f2 ) ) found = rr;
      kil ( f2 );
      nn++;
    } /* while ... */
    kil ( f1 ); 
  }
  return ( found );
/***
printf ( "\n*********************************** search_theory returning found=%d\n\n", found );
***/
}


search_hypothesis ( ss ) /* str_buf contains the hyp */
int ss;
{
  int f1, ii, bb;

/***
printf ( "search_hypothesis ( ss=%d )\n", ss );
***/

  f1 = read_frm_str_buf;
  if ( f1 != -999 ) {
    bb = 0;
    ii = 1;
    while ( ( ! bb ) && (  ii <= len ( ss ) ) ) {
      bb = ( eql_frm ( f1, frm_hyp ( val ( ss, ii ) ) ) != 0 );
/***
str_buf [ 0 ] = '\0';
write_frm_res(frm_hyp(val ( ss, ii )),0);
printf ( " search_hypothesis %d: %s\n", ii, str_buf );
***/
      if ( ! bb ) ii++;
    }
    kil ( f1 );
    if   ( ! bb ) return -999;
    else          return ii;
  }
  else {
    return -999;
  }
}


/*****************************************************************************/


int tot_sons_above;

rec_add_tot_sons_above ( n )
int n;
{
  int i;
  for ( i = 1 ; i <= len ( sons_nod ( n ) ) ; i++ ) {
    rec_add_tot_sons_above ( val ( sons_nod ( n ), i ) );
  }
  tot_sons_above++;
}

get_tot_sons_above ( n )
int n;
{
  int f, i, j, k;
  tot_sons_above = 1;
  f = fath_nod ( n );
  i = 1;
  while ( n != val ( sons_nod ( f ), i ) ) {
    i++;
  }
  for ( j = 1 ; j < i ; j++ ) {
    rec_add_tot_sons_above ( val ( sons_nod ( f ), j ) );
  }
}


#ifndef BTOOLKIT_FLAG

GetLookUpNode ( node )
{
  return ( node );
}

#endif

  /***************************************************************************/

#ifdef BTOOLKIT_FLAG

int run_man_prf_p_copy, last_node_copy, run_man_prf_p_save, run_man_prf_i_save;


GetReverseLookUpNode ( node )
{
  int nn = 0;

  while ( ( nn < CopyProofTreeLookUpTot )              &&
          ( node != CopyProofTreeLookUp [ 0 ] [ nn ] )    ) {
    nn++;
  }
  if ( node != CopyProofTreeLookUp [ 0 ] [ nn ] ) {
/***
printf ( " ::::::::::::::::: ReverseCopyProofTreeLookUp FAILED for %d\n", node );
***/
    return ( node );
  }
  else {
/***
printf ( " ::::::::::::::::: ReverseCopyProofTreeLookUp %d -> %d\n",
                                    node, CopyProofTreeLookUp [ 1 ] [ nn ] );
***/
    return ( CopyProofTreeLookUp [ 1 ] [ nn ] );
  }
}


GetLookUpNode ( node )
{
  int nn = 0;

  while ( ( nn < CopyProofTreeLookUpTot )              &&
          ( node != CopyProofTreeLookUp [ 1 ] [ nn ] )    ) {
    nn++;
  }
  if ( node != CopyProofTreeLookUp [ 1 ] [ nn ] ) {
/***
printf ( " ::::::::::::::::: CopyProofTreeLookUp FAILED for %d\n", node );
***/
    return ( node );
  }
  else {
/***
printf ( " ::::::::::::::::: CopyProofTreeLookUp %d -> %d\n",
                                       node, CopyProofTreeLookUp [ 0 ] [ nn ] );
***/
    return ( CopyProofTreeLookUp [ 0 ] [ nn ] );
/***
printf ( "%d\n", node );
***/
  }
}


CreNextNodeCopyProofTree ( curr_node, curr_node_copy )
{
  int son_seq, len_son, nn, goal, tmp_son_node;

  CopyProofTreeLookUp [ 0 ] [ CopyProofTreeLookUpTot ] = curr_node;
  CopyProofTreeLookUp [ 1 ] [ CopyProofTreeLookUpTot ] = curr_node_copy;
/***
printf ( "  %3d -> %3d\n", CopyProofTreeLookUp [ 0 ] [ CopyProofTreeLookUpTot ],
                           CopyProofTreeLookUp [ 1 ] [ CopyProofTreeLookUpTot ] );
fflush ( stdout );
***/

/***
printf ( "      %3d -> %3d\n", pssubrr [ CopyProofTreeLookUp [ 0 ] [ CopyProofTreeLookUpTot ] ],
                               pssubrr [ CopyProofTreeLookUp [ 1 ] [ CopyProofTreeLookUpTot ] ] );
fflush ( stdout );
***/
  CopyProofTreeLookUpTot++;

  last_node_copy = curr_node_copy;

  son_seq = sons_nod ( curr_node );
  len_son = len ( son_seq );
  nn = 1;
  while ( nn <= len_son ) {
    tmp_son_node = cre_nod_return_node ( info_nod ( val ( son_seq, nn ) ), curr_node_copy );
/***
printf ( "tmp_son_node = %d curr_node = %d run_man_prf_i = %d last_node_copy = %d\n", tmp_son_node, curr_node, run_man_prf_i, last_node_copy );
***/
    CreNextNodeCopyProofTree ( val ( son_seq, nn ), tmp_son_node );
/***
printf ( "last_node_copy = %d\n", last_node_copy );
***/
    nn++;
  }
}

CreCopyProofTree ()
{
  int i, goal, prev_node, prev_goal, 
      next_node, next_goal, prev_prev_node, nn, found;

  run_man_prf_p_copy = cre_root_nod ( info_nod ( run_man_prf_p ) );
  CopyProofTreeLookUpTot = 0;
  CreNextNodeCopyProofTree ( run_man_prf_p, run_man_prf_p_copy );

/***
printf ( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\nCreCopyProofTree:\n  run_man_prf_p_copy=%d (run_man_prf_p=%d) last_node_copy=%d\n", run_man_prf_p_copy, run_man_prf_p, last_node_copy );
fflush ( stdout );
***/

/***
printf ( "\n+++++++++++++++++++++++ check AND_gol +++++++++++++++++++++++\n" );
fflush ( stdout );
***/
  i = run_man_prf_p_copy;
  while ( i != last_node_copy ) {
/***
printf ( " $$$$$$$$$$$$$$$$$ i=%d, run_man_prf_p_copy=%d last_node_copy=%d %d/%d\n", i, run_man_prf_p_copy, last_node_copy, fath_nod ( run_man_prf_p_copy ), next_nod ( run_man_prf_p_copy, last_node_copy ) );
fflush ( stdout );
***/
    if ( i != run_man_prf_p_copy ) {
      prev_node = fath_nod ( i );
      if ( prev_node != run_man_prf_p_copy ) {
        /*** check this node an AND & prev node a bcall ***/
        if ( ( def_spe_gol ( info_nod ( i ) ) )                &&
             ( spe_gol ( info_nod ( i ) ) == AND_gol )         &&
             ( def_spe_gol ( info_nod ( prev_node ) ) )        &&
             ( spe_gol ( info_nod ( prev_node ) ) == CAL_gol )    ) {
/***
printf ( " ************ FOUND AND_gol (i=%d) ************\n", i );
fflush ( stdout );
***/
          /***
          change upward links of each son node of i to prev prev node
          ***/
          prev_prev_node = fath_nod ( prev_node );
          nn = 1;
          while ( nn <= len ( sons_nod ( i ) ) ) {
/***
printf ( "  setting fath_node of %d (son #%d of i=%d) to prev_prev_node=%d\n",
                              val ( sons_nod ( i ), nn ), nn, i, prev_prev_node );
fflush ( stdout );
***/
            fath_nod ( val ( sons_nod ( i ), nn ) ) = prev_prev_node;
            nn++;
	  }
          /***
          change downward link -
            pop ( sons_nod (prev_prev_node) ) - remove the CALL
            loop pushing sons_nod (i,nn) - the nodes of the AND
          replace sons_nod seq from prev prev node with that of
          node sons_nod seq of i
          ***/
/***
printf ( "  pop sons_nod ( prev_prev_node=%d)\n", prev_prev_node );
fflush ( stdout );
***/
          pop ( sons_nod ( prev_prev_node ) );
          nn = 1;
          while ( nn <= len ( sons_nod ( i ) ) ) {
/***
printf ( "  psh %d (son #%d of i=%d) onto sons_nod ( prev_prev_node=%d )\n",
                               val ( sons_nod ( i ), nn ), nn, i, prev_prev_node );
fflush ( stdout );
***/
            psh ( sons_nod ( prev_prev_node ), val ( sons_nod ( i ), nn ) );
            snbr_nod ( val ( sons_nod ( i ), nn ) ) = len ( sons_nod ( prev_prev_node ) );
            nn++;
	  }
/***
printf ( "  kil seq sons_nod ( prev_node=%d )\n", prev_node );
printf ( "  returing node %d\n", prev_node );
fflush ( stdout );
***/
          kil ( sons_nod ( prev_node ) );
          sup_nod ( prev_node );
/***
printf ( "  kil seq sons_nod ( i=%d )\n", i );
printf ( "  returing node %d\n", i );
fflush ( stdout );
***/
          kil ( sons_nod ( i ) );
          sup_nod ( i );
          i = prev_prev_node;
/***
printf ( "        check:\n" );
nn = 1;
while ( nn <= len ( sons_nod ( i ) ) ) {
  printf ( "            son #%d (snbr_nod=%d) of %d is %d whose father is %d\n", nn, snbr_nod ( val ( sons_nod ( i ), nn ) ), i, val ( sons_nod ( i ), nn ), fath_nod ( val ( sons_nod ( i ), nn ) ) );
  if ( i != fath_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    fath_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  if ( nn != snbr_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    snbr_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  nn++;
}
fflush ( stdout );
***/
	}
        else { /* this node not an AND or prev not node a bcall ) */
          i = next_nod ( run_man_prf_p_copy, i );
        }
      }      
      else { /* prev_node run_man_prf_p_copy */
        i = next_nod ( run_man_prf_p_copy, i );
      }
    }
    else { /* this node run_man_prf_p_copy */
      i = next_nod ( run_man_prf_p_copy, i );
    }
  } /* while ( i ) */

  /***
  ... now remove bcalls ...
  ***/

/***
printf ( "\n+++++++++++++++++++++++ check CAL_gol +++++++++++++++++++++++\n" );
fflush ( stdout );
***/
  i = run_man_prf_p_copy;
  while ( i != last_node_copy ) {
/***
printf ( " $$$$$$$$$$$$$$$$$ i=%d, run_man_prf_p_copy=%d last_node_copy=%d %d/%d\n", i, run_man_prf_p_copy, last_node_copy, fath_nod ( run_man_prf_p_copy ), next_nod ( run_man_prf_p_copy, last_node_copy ) );
fflush ( stdout );
***/
    if ( i != run_man_prf_p_copy ) {
      if ( ( def_spe_gol ( info_nod ( i ) ) )        &&
           ( spe_gol ( info_nod ( i ) ) == CAL_gol )    ) {
        if ( len ( sons_nod ( i ) ) == 1 ) {
/***
printf ( " ************ FOUND CAL_gol (i=%d) ************\n", i );
fflush ( stdout );
***/
          prev_node = fath_nod ( i );
          next_node = fst ( sons_nod ( i ) );
/***
printf ( "  prev_node(%d) i(%d) next_node(%d)\n", prev_node, i, next_node );
fflush ( stdout );
***/
          /***
          change upward link
          ***/
/***
printf ( "  setting fath_node of %d  to %d\n", next_node, fath_nod ( i ) );
fflush ( stdout );
***/
          fath_nod ( next_node ) = fath_nod ( i );
          /***
          change downward link - find the son number first!
          ***/
          nn = 1;
          found = 0;
          while ( ! ( found ) ) {
            if ( val ( sons_nod ( prev_node ), nn ) == i ) found = 1;
            if ( ! found ) nn++;
	  } /* while */
/***
printf ( "  we are child #%d in prev_node(%d)\n", nn, prev_node );
printf ( "    storing next_node(%d) here instead of us\n", next_node );
  if ( nn != snbr_nod ( i ) ) {
    printf ( "\n\n\n\n\n    nn snbr_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
fflush ( stdout );
***/
          str ( sons_nod ( prev_node ), nn, next_node );
          snbr_nod ( next_node ) = nn;
/***
printf ( "  kil seq sons_nod ( i=%d )\n", i );
printf ( "  returing node %d\n", i );
fflush ( stdout );
***/
          kil ( sons_nod ( i ) );
          sup_nod ( i );
          i = prev_node;
/***
printf ( "        check:\n" );
nn = 1;
while ( nn <= len ( sons_nod ( i ) ) ) {
  printf ( "            son #%d (snbr_nod=%d) of %d is %d whose father is %d\n", nn, snbr_nod ( val ( sons_nod ( i ), nn ) ), i, val ( sons_nod ( i ), nn ), fath_nod ( val ( sons_nod ( i ), nn ) ) );
  if ( i != fath_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    fath_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  if ( nn != snbr_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    snbr_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  nn++;
}
fflush ( stdout );
***/
        }
        else { /* CAL_gol, but len ( sons_nod ( i ) ) != 1 */
          i = next_nod ( run_man_prf_p_copy, i );
	}
      }
      else { /* this node not CAL_gol */
        i = next_nod ( run_man_prf_p_copy, i );
      }      
    }    
    else { /* this node run_man_prf_p_copy */
      i = next_nod ( run_man_prf_p_copy, i );
    }
  } /* while ( i ) */

/***
printf ( "\n+++++++++++++++++++++++ check duplicate ++++++++++++++++++++++\n" );
fflush ( stdout );
***/
  i = run_man_prf_p_copy;
  while ( i != last_node_copy ) {
/***
printf ( " $$$$$$$$$$$$$$$$$ i=%d, run_man_prf_p_copy=%d last_node_copy=%d %d/%d\n", i, run_man_prf_p_copy, last_node_copy, fath_nod ( run_man_prf_p_copy ), next_nod ( run_man_prf_p_copy, last_node_copy ) );
fflush ( stdout );
***/
    if ( i != run_man_prf_p_copy ) {
      prev_node = fath_nod ( i );
      if ( prev_node != run_man_prf_p_copy ) {
        /*** check we are the last son ***/
        if ( lst ( sons_nod ( prev_node ) ) == i ) {
          goal = info_nod ( i );
          prev_goal = info_nod ( prev_node );
          if ( eql_frm ( frm_gol ( goal ), frm_gol ( prev_goal ) ) ) {
/***
printf ( " ************ FOUND eql_frm (i=%d) ************\n", i );
fflush ( stdout );
***/
            /***
            change upward link
            ***/
/***
printf ( "  setting fath_node of %d  to %d\n", i, fath_nod ( prev_node ) );
fflush ( stdout );
***/
            fath_nod ( i ) = fath_nod ( prev_node );
            /***
            change downward link - find the son number first!
            ***/
            prev_prev_node = fath_nod ( prev_node );
            nn = 1;
            found = 0;
            while ( ! ( found ) ) {
              if ( val ( sons_nod ( prev_prev_node ), nn ) == prev_node ) found = 1;
              if ( ! found ) nn++;
	    } /* while */
/***
  if ( nn != snbr_nod ( prev_node ) ) {
    printf ( "\n\n\n\n\n    nn snbr_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
fflush ( stdout );
printf ( "  prev_node(%d) is child #%d of prev_prev_node(%d)\n",  prev_node, nn, prev_prev_node );
printf ( "    stroring i(%d) in %d\n",
                                 i, val ( sons_nod ( prev_prev_node ), nn ) );
fflush ( stdout );
***/
           str ( sons_nod ( prev_prev_node ), nn, i );
           snbr_nod ( i ) = nn;
           /***
           remove all our brothers
	   ***/
/***
printf ( "  we are child #%d of prev_node\n", len ( sons_nod ( prev_node ) ) );
fflush ( stdout );
***/
           nn = 1;
           while ( nn < len ( sons_nod ( prev_node ) ) ) {
/***
printf ( "    killing our brother #%d - seq sons_nod ( %d ), returing node %d\n", nn, sons_nod ( val ( sons_nod ( prev_node ), nn ) ), val ( sons_nod ( prev_node ), nn ) );
fflush ( stdout );
***/
             kil ( sons_nod ( val ( sons_nod ( prev_node ), nn ) ) );
             sup_nod ( val ( sons_nod ( prev_node ), nn ) );
             nn++;
	   }
/***
printf ( "  kil seq sons_nod ( prev_node=%d )\n", prev_node );
printf ( "  returing node %d\n", prev_node );
fflush ( stdout );
***/
            kil ( sons_nod ( prev_node ) );
            sup_nod ( prev_node );
            i = prev_prev_node;
/***
printf ( "        check:\n" );
nn = 1;
while ( nn <= len ( sons_nod ( i ) ) ) {
  printf ( "            son #%d (snbr_nod=%d) of %d is %d whose father is %d\n", nn, snbr_nod ( val ( sons_nod ( i ), nn ) ), i, val ( sons_nod ( i ), nn ), fath_nod ( val ( sons_nod ( i ), nn ) ) );
  if ( i != fath_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    fath_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  if ( nn != snbr_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    snbr_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  nn++;
}
fflush ( stdout );
***/
	  }
          else { /* not eql frm */
            i = next_nod ( run_man_prf_p_copy, i );
          }
	}
        else { /* len ( sons_nod ( prev_node ) ) != 1 */
          i = next_nod ( run_man_prf_p_copy, i );
        }
      }      
      else { /* prev_node run_man_prf_p_copy */
        i = next_nod ( run_man_prf_p_copy, i );
      }
    }
    else { /* this node run_man_prf_p_copy */
      i = next_nod ( run_man_prf_p_copy, i );
    }
  } /* while ( i ) */

/***
printf ( "\n+++++++++++++++++ check last goal duplicate ++++++++++++++++++\n" );
fflush ( stdout );
***/
  if ( last_node_copy != run_man_prf_p_copy ) {
    prev_node = fath_nod ( last_node_copy );
    if ( prev_node != run_man_prf_p_copy ) {
      goal = info_nod ( last_node_copy );
      prev_goal = info_nod ( prev_node );
      if ( eql_frm ( frm_gol ( goal ), frm_gol ( prev_goal ) ) ) {
/***
printf ( " ************ FOUND eql_frm (i=%d) ************\n", last_node_copy );
fflush ( stdout );
***/
        /***
        change upward link
        ***/
/***
printf ( "  setting fath_node of %d  to %d\n",
                                       last_node_copy, fath_nod ( prev_node ) );
fflush ( stdout );
***/
        fath_nod ( last_node_copy ) = fath_nod ( prev_node );
        /***
        change downward link - find the son number first!
        ***/
        prev_prev_node = fath_nod ( prev_node );
        nn = 1;
        found = 0;
        while ( ! ( found ) ) {
          if ( val ( sons_nod ( prev_prev_node ), nn ) == prev_node ) found = 1;
          if ( ! found ) nn++;
	} /* while */
/***
printf ( "  child #%d in prev_prev_node(%d) - storing last_node_copy(%d) in %d\n",
     nn, prev_prev_node, last_node_copy, val ( sons_nod ( prev_prev_node ), nn ) );
fflush ( stdout );
***/
          str ( sons_nod ( prev_prev_node ), nn, last_node_copy );
          snbr_nod ( last_node_copy ) = nn;
/***
printf ( "  kil seq sons_nod ( prev_node=%d )\n", prev_node );
printf ( "  returing node %d\n", prev_node );
fflush ( stdout );
***/
        kil ( sons_nod ( prev_node ) );
        sup_nod ( prev_node );
/***
printf ( "        check:\n" );
i = last_node_copy;
nn = 1;
while ( nn <= len ( sons_nod ( i ) ) ) {
  printf ( "            son #%d (snbr_nod=%d) of %d is %d whose father is %d\n", nn, snbr_nod ( val ( sons_nod ( i ), nn ) ), i, val ( sons_nod ( i ), nn ), fath_nod ( val ( sons_nod ( i ), nn ) ) );
  if ( i != fath_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    fath_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  if ( nn != snbr_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    snbr_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  nn++;
}
fflush ( stdout );
***/
      }
    }
  }

/***
printf ( "\n+++++++++++++++++ check top goal duplicate +++++++++++++++++++\n" );
fflush ( stdout );
***/
  if ( len ( sons_nod ( run_man_prf_p_copy ) ) == 1 ) {
    next_node = fst ( sons_nod ( run_man_prf_p_copy ) );
    if ( len ( sons_nod ( next_node ) ) == 1 ) {
      goal = info_nod ( run_man_prf_p_copy );
      next_goal = info_nod ( next_node );
      if ( eql_frm ( frm_gol ( goal ), frm_gol ( next_goal ) ) ) {
/***
printf ( " ************ FOUND eql_frm (i=%d) ************\n", next_node );
fflush ( stdout );
***/
        /***
        ... remove upward link ...
        ***/
/***
printf ( "  setting (removing) fath_node of %d to %d\n", next_node, 0 );
fflush ( stdout );
***/
        fath_nod ( next_node ) = 0;
/***
printf ( "  kil seq sons_nod ( run_man_prf_p_copy=%d )\n", run_man_prf_p_copy );
printf ( "  returing node %d\n", run_man_prf_p_copy );
fflush ( stdout );
***/
        kil ( sons_nod ( run_man_prf_p_copy ) );
        sup_nod ( run_man_prf_p_copy );
        run_man_prf_p_copy = next_node;
/***
printf ( "        check:\n" );
i = run_man_prf_p_copy;
nn = 1;
while ( nn <= len ( sons_nod ( i ) ) ) {
  printf ( "            son #%d (snbr_nod=%d) of %d is %d whose father is %d\n", nn, snbr_nod ( val ( sons_nod ( i ), nn ) ), i, val ( sons_nod ( i ), nn ), fath_nod ( val ( sons_nod ( i ), nn ) ) );
  if ( i != fath_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    fath_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  if ( nn != snbr_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    snbr_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  nn++;
}
fflush ( stdout );
***/
      }
    }
  }

/***
printf ( "\n+++++++++++++++++ check top goal SwitchBTPX ++++++++++++++++++\n" );
fflush ( stdout );
***/
  if ( len ( sons_nod ( run_man_prf_p_copy ) ) == 1 ) {
    next_node = fst ( sons_nod ( run_man_prf_p_copy ) );
    goal = info_nod ( run_man_prf_p_copy );
    if ( ( def_rul_gol ( goal ) )                                &&
         ( ! ( def_spe_gol ( goal ) ) )                          &&
         ( ( the_rul ( rul_gol ( goal ) ) ==  nbr_the )     ||
           ( the_rul ( rul_gol ( goal ) ) ==  nbr_the - 1 )    )    ) {
/***
printf ( " ************ FOUND top goal SwitchBTPX (i=%d) *********\n", next_node );
fflush ( stdout );
***/
      /***
      ... remove upward link ...
      ***/
/***
printf ( "  setting (removing) fath_node of %d to %d\n", next_node, 0 );
fflush ( stdout );
***/
      fath_nod ( next_node ) = 0;
/***
printf ( "  kil seq sons_nod ( run_man_prf_p_copy=%d )\n", run_man_prf_p_copy );
printf ( "  returing node %d\n", run_man_prf_p_copy );
fflush ( stdout );
***/
      kil ( sons_nod ( run_man_prf_p_copy ) );
      sup_nod ( run_man_prf_p_copy );
      run_man_prf_p_copy = next_node;
/***
printf ( "        check:\n" );
i = run_man_prf_p_copy;
nn = 1;
while ( nn <= len ( sons_nod ( i ) ) ) {
  printf ( "            son #%d (snbr_nod=%d) of %d is %d whose father is %d\n", nn, snbr_nod ( val ( sons_nod ( i ), nn ) ), i, val ( sons_nod ( i ), nn ), fath_nod ( val ( sons_nod ( i ), nn ) ) );
  if ( i != fath_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    fath_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  if ( nn != snbr_nod ( val ( sons_nod ( i ), nn ) ) ) {
    printf ( "\n\n\n\n\n    snbr_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
    sleep ( 5 );
  }
  nn++;
}
fflush ( stdout );
***/
    }
  }

/***
printf ( "\n++++++++++++++++++++++++ modify rul_gol ++++++++++++++++++++++\n" );
fflush ( stdout );
***/
  i = run_man_prf_p_copy;
  while ( i != last_node_copy ) {
/***
printf ( " $$$$$$$$$$$$$$$$$ i=%d, run_man_prf_p_copy=%d last_node_copy=%d %d/%d\n", i, run_man_prf_p_copy, last_node_copy, fath_nod ( run_man_prf_p_copy ), next_nod ( run_man_prf_p_copy, last_node_copy ) );
fflush ( stdout );
***/
    goal = info_nod ( i );
    if ( ( def_rul_gol ( goal ) ) && ( ! ( def_spe_gol ( goal ) ) ) ) {
      int old_thy = the_rul ( rul_gol ( goal ) );
      if ( old_thy >= first_switchBTP_thy ) {
        int rule_num = num_rul ( rul_gol ( goal ) );
/***
str_buf [ 0 ] = '\0';
write_nam_the ( old_thy );
strcat ( str_buf, "." );
CreNumInBuf ( str_buf, rule_num );
printf ( "    %s -> ", str_buf );
fflush ( stdout );
***/
        mod_rul_gol ( goal, val_rul_the (
             old_thy + last_switch_thy - last_switchBTP_thy, rule_num ) );
/***
str_buf [ 0 ] = '\0';
write_nam_the ( the_rul ( rul_gol ( goal ) ) );
strcat ( str_buf, "." );
CreNumInBuf ( str_buf, num_rul ( rul_gol ( goal ) ) );
printf ( "%s\n", str_buf );
fflush ( stdout );
***/
      }
    } 
    i = next_nod ( run_man_prf_p_copy, i );
  }

/***
printf ( "\n++++++++++++++++ modify rul_gol last_node_copy +++++++++++++++\n" );
fflush ( stdout );
***/
  goal = info_nod ( last_node_copy );
  if ( ( def_rul_gol ( goal ) ) && ( ! ( def_spe_gol ( goal ) ) ) ) {
    int old_thy = the_rul ( rul_gol ( goal ) );
    if ( old_thy >= first_switchBTP_thy ) {
      int rule_num = num_rul ( rul_gol ( goal ) );
/***
str_buf [ 0 ] = '\0';
write_nam_the ( old_thy );
strcat ( str_buf, "." );
CreNumInBuf ( str_buf, rule_num );
printf ( "    %s -> ", str_buf );
fflush ( stdout );
***/
      mod_rul_gol ( goal, val_rul_the (
           old_thy + last_switch_thy - last_switchBTP_thy, rule_num ) );
/***
str_buf [ 0 ] = '\0';
write_nam_the ( the_rul ( rul_gol ( goal ) ) );
strcat ( str_buf, "." );
CreNumInBuf ( str_buf, num_rul ( rul_gol ( goal ) ) );
printf ( "%s\n", str_buf );
fflush ( stdout );
***/
    }
  } 

/***
printf ( "\n++++++++++++++++++ CreCopyProofTree complete +++++++++++++++++\n" );
printf ( "final run through tree:\n" );
i = run_man_prf_p_copy;
while ( i ) {
  printf ( "   run_man_prf_p_copy=%d last_node_copy=%d\n",
                                           run_man_prf_p_copy, last_node_copy );
  printf ( "       **** i=%d\n", i );
  printf ( "              len sons_nod = %d", len ( sons_nod ( i ) ) );
  fflush ( stdout );
  nn = 1;
  while ( nn <= len ( sons_nod ( i ) ) ) {
    printf ( "\n                  son #%d is %d (snbr_nod=%d)",
        nn, val ( sons_nod ( i ), nn ), snbr_nod ( val ( sons_nod ( i ), nn ) ) );
    if ( i != fath_nod ( val ( sons_nod ( i ), nn ) ) ) {
      printf ( "\n\n\n\n\n    fath_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
      sleep ( 5 );
    }
    if ( nn != snbr_nod ( val ( sons_nod ( i ), nn ) ) ) {
      printf ( "\n\n\n\n\n    snbr_nod YEUK\n\n\n\n\n" ); fflush ( stdout );
      sleep ( 5 );
    }
    nn++;
  }
  printf ( "\n" ); fflush ( stdout );
  i = next_nod ( run_man_prf_p_copy, i );
}
printf ( "++++++++++++++++++ CreCopyProofTree complete +++++++++++++++++\n" );
fflush ( stdout );
***/
}

#endif /* BTOOLKIT_FLAG */

  /***************************************************************************/



RedrawProofTree ( top_node, curr_node )
int top_node, curr_node;
/* itr_nod_proof_tree () */
{
  int nh = 0;
  int nv = 0;
  void DisplayProofNode ();

/***
printf ( "\n\n\n** RedrawProofTree(top_node=%d,curr_node=%d) last_node=%d\n",
                                                 top_node, curr_node, last_node );
***/
  /***
  curr_node == 0 => proof complete!
  ***/
  if ( NextProofStepWillBeAutoDischarged () && ( curr_node ) ) return;


#ifdef BTOOLKIT_FLAG

  node_to_be_displayed_as_last = curr_node;

#ifdef BTOOL_PROVER_NEW

  another_backtrack_required = 0;

  if ( backtrack_attempted ) {
/***/
printf ( "\n===================== backtrack_attempted =======================\n" );
printf ( "backtrack_succeeded = %d\n", backtrack_succeeded );
str_buf [ 0 ] = '\0';
write_frm_first_prooftree_goal ( last_goal_displayed_frm );
printf ( "prev_goal: %s\n", str_buf );
str_buf [ 0 ] = '\0';
print_goal_into_str_buf ( info_nod ( node_to_be_displayed_as_last ) );
printf ( "curr_goal: %s\n", str_buf );
/***/
    if ( eql_frm ( frm_gol ( info_nod ( node_to_be_displayed_as_last ) ),
	                                             last_goal_displayed_frm ) ) {
      another_backtrack_required = 1;
printf ( "another_backtrack_required = %d\n", another_backtrack_required );
printf ( "====================================================================\n" );
      return; /* from run_man_prf, to run_man_prf_A */
    }
printf ( "another_backtrack_required = %d\n", another_backtrack_required );
printf ( "====================================================================\n" );
  }

#endif /* BTOOL_PROVER_NEW */

#endif /* BTOOLKIT_FLAG */


  visible_scroll = ( Widget ) 0;

  XtUnmanageChild ( proof_tree_scroll_form );
  XtDestroyWidget ( proof_tree_scroll_form );

  proof_tree_scroll_form = XtVaCreateWidget ( "ProofTree",
      xmFormWidgetClass,         proof_tree_scroll,
      XmNdialogStyle,            XmDIALOG_MODELESS,
      XmNdefaultPosition,        False,  
      XmNtraversalOn,            True,
      NULL );



  /***************************************************************************/

#ifdef BTOOLKIT_FLAG

#ifdef BTOOL_PROVER_NEW

  /***
  copy proof tree
  ***/

  CreCopyProofTree ();

  run_man_prf_p_save = top_node;
/* FULL TREE JUNK */
/***/
  top_node = run_man_prf_p_copy;
/***/
  run_man_prf_i_save = curr_node;
  curr_node = GetReverseLookUpNode ( node_to_be_displayed_as_last );
  if ( fath_nod ( curr_node ) )
    node_to_undo_to = GetLookUpNode ( fath_nod ( curr_node ) );
  else
    node_to_undo_to = 0;

#endif /* BTOOL_PROVER_NEW */

#endif /* BTOOLKIT_FLAG */

  /***************************************************************************/


  i = top_node;
/***
printf ( "i = top_node = %d\n", i );
printf ( "curr_node = %d\n", curr_node );
#ifdef BTOOLKIT_FLAG
#ifdef BTOOL_PROVER_NEW
printf ( "node_to_be_displayed_as_last = %d\n", node_to_be_displayed_as_last );
#endif /? BTOOL_PROVER_NEW ?/
#endif /? BTOOLKIT_FLAG ?/
printf ( "fath_nod ( top_node ) = %d\n", fath_nod ( top_node ) );
***/
  while ( i != fath_nod ( top_node ) ) { /* fath_nod ( top_node ) == 0 !!! */
    if ( cptr_nod ( i ) == 0  ) {
      if   ( i == top_node ) tot_sons_above = 0;
      else                   get_tot_sons_above ( i );
#ifdef BTOOLKIT_FLAG
      if ( ! node_to_be_displayed_as_last ) { /* proof complete */
#else
      if ( ! curr_node ) {                    /* proof complete */
#endif
        /*** goals as labels - proof complete ***/
        DisplayProofNode ( i, curr_node, info_nod ( i ), nh, nv, tot_sons_above, 0 );
      }
      else {
        /*** goals as push buttons - proof NOT complete ***/
        DisplayProofNode ( i, curr_node, info_nod ( i ), nh, nv, tot_sons_above, 1 );
      }
      nv++;
      nh++;
    }

    if ( cptr_nod ( i ) == len ( sons_nod ( i ) ) ) { /* printed last son */
      cptr_nod ( i ) = 0;
      nh--;
      i = fath_nod ( i );
    }
    else if ( cptr_nod ( i ) == 0  ) {                /* get first son */
      cptr_nod ( i ) = 1;
      i = fst ( sons_nod ( i ) );
    } else {                                          /* get next son */
      cptr_nod ( i ) = cptr_nod ( i ) + 1;
      i = val ( sons_nod ( i ), cptr_nod ( i ) );
    }
  }

#ifdef BTOOLKIT_FLAG
  if   ( ! node_to_be_displayed_as_last )
#else
  if   ( ! curr_node )
#endif
    DisplayProofNode ( -999, 0, 0, 0, nv, 0, 0 ); /* goals_as_push_but=0 */
  else
    DisplayProofNode ( -999, 0, 0, 0, nv, 0, 1 ); /* proof not complete */




  /***************************************************************************/

#ifdef BTOOLKIT_FLAG

#ifdef BTOOL_PROVER_NEW

  top_node = run_man_prf_p_save;
  curr_node = run_man_prf_i_save;

  kil_nod ( run_man_prf_p_copy );
  
#endif /* BTOOL_PROVER_NEW */

#endif /* BTOOLKIT_FLAG */

  /***************************************************************************/



/***
print_hyp_len ( "RedrawProofTree 2", curr_node );
***/

  XtManageChild ( proof_tree_scroll_form );
  XtManageChild ( proof_tree_scroll );

  XmUpdateDisplay ( proof_tree_dialog_form );

  if ( visible_scroll )
    XmScrollVisible ( proof_tree_scroll, visible_scroll, 50, 50 );

  XmUpdateDisplay ( proof_tree_scroll );

/*
  XmUpdateDisplay ( proof_tree_scroll );
  XmUpdateDisplay ( proof_tree_scroll_form );
*/
}

#ifdef BTOOLKIT_FLAG

DumpRecordedProofsError ( n, file )
int n;
char * file;
{
  printf ( "\n\n    Can't save %s - error %d\n", file, n );
  AbortedMsg ();
  Kill_bplatform_and_exit ( 1, 0 );
}

DumpRecordedProofs ()
{
  int i, s, j, l, st, level;
  int rep, obj, stp;
  void SetDisplayField_obj_Changed ();

  val_curMRIState ( &st, curr_obj );
  length_pob ( &level, st );
  sprintf ( buf, "%s/POB/%s.%d.btl", cur_dir, GetName ( curr_obj ), level - 1 );

  for ( i = 1 ; i < max_proved_rr ; i++ ) {

    if ( proved_rr [ i ] ) {

/***
printf ( "make_btl_prf ( %d, %d )\n", num_rul ( proved_rr [ i ] ), val ( proved_seq_rr [ i ], 1 ) );
***/
      make_btl_prf ( &rep, &obj,
         num_rul ( proved_rr [ i ] ), val ( proved_seq_rr [ i ], 1 ) );
      if ( ! rep ) DumpRecordedProofsError ( 1, buf );
      str_buf [ 0 ] = '\0';
      write_nam_the ( the_rul ( proved_rr [ i ] ) );
/***
printf ( "mod_pob_thy_str ( %d, %s )\n", obj, str_buf );
***/
      mod_pob_thy_str ( &rep, obj, str_buf );
      if ( ! rep ) DumpRecordedProofsError ( 2, buf );

      l = len ( proved_seq_rr [ i ] );
      for ( j = 2 ; j <= l ; j++ ) {

        make_prf_seq_stp ( &rep, &stp, val ( proved_seq_rr [ i ], j ),
                             val ( proved_seq_sub_rr [ i ], j ) );
/***
printf ( "make_prf_seq_stp ( %d, %d )\n", val ( proved_seq_rr [ i ], j ), val ( proved_seq_sub_rr [ i ], j ) );
***/
        if ( ! rep ) DumpRecordedProofsError ( 3, buf );

        /******
        A Rule
        ******/
        if ( val ( proved_seq_rr [ i ], j ) <= max_rul ) {
/***
printf ( "A rule\n" );
***/
          str_buf [ 0 ] = '\0';
          write_nam_the ( the_rul ( val ( proved_seq_rr [ i ], j ) ) );
          mod_stp_thy_str ( &rep, stp, str_buf );
/***
printf ( "mod_stp_thy_str ( %d, %s )\n", stp, str_buf );
***/
          if ( ! rep ) DumpRecordedProofsError ( 4, buf );
          str_buf [ 0 ] = '\0';
          write_ver_rul_no_indent_no_nl ( val ( proved_seq_rr [ i ], j ) );
          mod_stp_rule_str ( &rep, stp, str_buf );
/***
printf ( "mod_stp_rule_str ( %d, %s )\n", stp, str_buf );
***/
          if ( ! rep ) DumpRecordedProofsError ( 5, buf );
	} /* <= max_rul - A rule */

        /******
        LEM_gol
        ******/
        else if ( val ( proved_seq_rr [ i ], j ) >= 3*max_rul ) {
/***
printf ( "A LEM_gol\n" );
***/
          str_buf [ 0 ] = '\0';
          write_ver_rul_no_indent_no_nl ( val ( proved_seq_rr [ i ], j ) - 3 * max_rul );
          mod_stp_rule_str ( &rep, stp, str_buf );
/***
printf ( "mod_stp_rule_str ( %d, %s )\n", stp, str_buf );
***/
          if ( ! rep ) DumpRecordedProofsError ( 17, buf );
	}

        /******
        A spe_gol
        ******/
        else if ( val ( proved_seq_rr [ i ], j ) <= 2*max_rul ) {
/***
printf ( "A spe_gol\n" );
***/
          if ( ( val ( proved_seq_rr [ i ], j ) - max_rul ) == HYP_gol ) {
/***
printf ( "A HYP_gol\n" );
***/
            str_buf [ 0 ] = '\0';
            write_frm_res ( val ( proved_seq_hyp_rr [ i ], j ), 0 );
            mod_stp_rule_str ( &rep, stp, str_buf );
/***
printf ( "mod_stp_rule_str ( %d, %s )\n", stp, str_buf );
***/
            if ( ! rep ) DumpRecordedProofsError ( 7, buf );
          }

        } /* <= 2*max_rul - A spe_gol */

        /******
        A frm_gol
        ******/
        else {
/***
printf ( "A frm_gol\n" );
***/
          ;
        } /* A frm_gol */

        push_prf_seq ( &rep ,obj, stp );
/***
printf ( "push_prf_seq ( %d, %d )\n", obj, stp );
***/
        if ( ! rep ) DumpRecordedProofsError ( 12, buf );

      } /* for ( j = 2 ... */


    } /* if ( proved_rr [ i ] ... */

  }/* for ( i = 1 ... */

  save_n_btl_proof ( &rep );
/***
printf ( "save_n_btl_proof\n" );
***/
  if ( ! rep ) DumpRecordedProofsError ( 13, buf );

  sprintf ( str_buf, "cp btl_proof.dump %s", buf );
  execute ( str_buf );
  unlink ( "btl_proof.dump" );

  SetDisplayField_obj_Changed ( curr_obj );
}

int
NotInSeq ( ss, rr )
int ss;
int rr;
{
  int i, ll, not_in_seq;

  ll = len ( ss );
/***
printf ( "-------------------------------\nseq values - looking for %d (seq length %d)\n", rr, ll );
for ( i = 1 ; i <= ll ; i++ ) printf ( " %d: %d ", i, val ( ss, i ) );
***/
  i = 1;
  not_in_seq = 1;
  while ( ( not_in_seq ) && ( i <= ll ) ) {
    if ( rr == val ( ss, i ) ) not_in_seq = 0;
    i++;
  }
/***
printf ( "\n -- i = %d  not_in_seq = %d\n-------------------------------\n", i, not_in_seq );
***/
  return ( not_in_seq );
}

void
PrintBToolProofMethod_Contd ()
{
  int i, j, n, ll, st, level, rul_prtd, is_prev;
  FILE * src;

/***
printf ( " -------- btool_proofs_committed      %d\n", btool_proofs_committed );
n = nbr_rul_the ( btl_users_thy );
printf ( " -------- btl_users_thy tot rules     %d\n", n );
n = nbr_rul_the ( fwd_btl_users_thy );
printf ( " -------- fwd_btl_users_thy tot rules %d\n", n );
***/
  sprintf ( str_buf, "%s/PMD/%s", cur_dir, GetName ( curr_obj ) );
  val_curMRIState ( &st, curr_obj );
  length_pob ( &level, st );
  /***
  btool_proofs_committed = 1 =>
  level has alread been incremented (Popup_CommitBToolProofs) - exit___contd ( 1, 0 )
  so we need to decrement by 2 (not 1 as previously)
  ***/
  if   ( btool_proofs_committed ) sprintf ( buf, "%s.%d.btl.pmd", str_buf, level - 2 );
  else                            sprintf ( buf, "%s.%d.btl.pmd", str_buf, level - 1 );
/***
printf ( " - %s\n", buf );
***/
  src = fopen ( buf, "w" );
  if ( src == NULL ) {
    strcpy ( primary_string, "\"" );
    strcat ( primary_string, buf );
    strcat ( primary_string, "\" for writing" );
    AbortedMsgFile ( primary_string );
    Kill_bplatform_and_exit ( 1, 0 );
  }
  fprintf ( src, "PROOFMETHOD %s.%d.btl IS\n\n", GetName ( curr_obj ), level - 1 );

  i = btl_users_thy;
  str_buf [ 0 ] = '\0';
  write_nam_the ( i );
  fprintf ( src, "  THEORY %s", str_buf );
  rul_prtd = 0;
  n = nbr_rul_the ( i );
  if ( n ) {
    for ( j = 1; j <= n ; j++ ) {
      is_prev = RulePrevPmdLevel ( val_rul_the ( i, j ) );
/***
printf ( " -- btl_users_thy rule %d - is_prev %d\n", j, is_prev );
***/
      if ( ( ! is_prev ) && ( NotInSeq ( unwanted_seq, val_rul_the ( i, j ) ) ) ) {
        if   ( ! rul_prtd ) { fprintf ( src, " IS\n" ); rul_prtd = 1; }
        else                { fprintf ( src, ";\n" ); }
        strcpy ( str_buf, "    " );
        write_ver_rul_no_indent_no_nl ( val_rul_the ( i, j ) );
/***
printf ( " {writing btl_users_thy rule}\n" );
***/
        fprintf ( src, "%s", str_buf );
      }
    }
  }

  i = fwd_btl_users_thy;
  str_buf [ 0 ] = '\0';
  write_nam_the ( i );
  fprintf ( src, "\n  END\n  &\n  THEORY %s", str_buf );
  rul_prtd = 0;
  n = nbr_rul_the ( i );
  if ( n ) {
    for ( j = 1; j <= n ; j++ ) {
      is_prev = RulePrevPmdLevel ( val_rul_the ( i, j ) );
/***
printf ( " -- fwd_btl_users_thy rule %d - is_prev %d\n", j, is_prev );
***/
      if ( ( ! is_prev ) && ( NotInSeq ( unwanted_seq, val_rul_the ( i, j ) ) ) ) {
        if   ( ! rul_prtd ) { fprintf ( src, " IS\n" ); rul_prtd = 1; }
        else                { fprintf ( src, ";\n" ); }
        strcpy ( str_buf, "    " );
        write_ver_rul_no_indent_no_nl ( val_rul_the ( i, j ) );
/***
printf ( " {writing fwd_btl_users_thy rule}\n" );
***/
        fprintf ( src, "%s", str_buf );
      }
    }
  }
  ll = len ( unwanted_seq );
/***
printf ( " >>>>>>> PrintBToolProofMethod_Contd -- unwanted_seq len %d <<<<<<<<<<\n", ll );
***/
  fprintf ( src, "\n  END\n\nEND\n" );
  fclose ( src );
  if ( ll ) {
    if   ( ll == 1 ) DisplayCurrWinText ( "\n  Discarded the following rule:" );
    else             DisplayCurrWinText ( "\n  Discarded the following rules:" );
    for ( i = 1 ; i <= ll ; i++ ) {
      strcpy ( str_buf, "\n\n  " );
      write_nam_the ( the_rul ( val ( unwanted_seq, i ) ) );
      strcat ( str_buf, "." );
      write_nat ( num_rul ( val ( unwanted_seq, i ) ) );
      strcat ( str_buf, "\n" );
      app_write_rul ( val ( unwanted_seq, i ) );
      DisplayCurrWinText ( str_buf );
    }
    DisplayCurrWinText ( "\n" );
  }
  kil ( unwanted_seq );
  exit___contd___finally ();
}

void
PrintBToolProofMethod ( print_all_rules_flag )
int print_all_rules_flag;
{
  int tmp_seq = cre ( 10 );
  int i, tt, rr;
  void LoadSeqAllBtlRulesUsedInProof ();

/***
printf ( " >>>>>>> PrintBToolProofMethod ( %d ) <<<<<<<<<<\n", print_all_rules_flag );
***/

  unwanted_seq = cre ( 10 );

  if ( print_all_rules_flag ) {

    PrintBToolProofMethod_Contd ();

  }

  else {

    LoadSeqAllBtlRulesUsedInProof ( & tmp_seq );

/***
printf ( " -- len ( tmp_seq ): %d\n", len ( tmp_seq ) );
***/

    sel_arr_tot = 0;
    tt = nbr_rul_the ( btl_users_thy );
    for ( i = 1 ; i <= tt ; i++ ) {
      rr = val_rul_the ( btl_users_thy, i );
      if ( ( NotInSeq ( tmp_seq, rr ) ) && ( ! ( RulePrevPmdLevel ( rr ) ) ) ) {
        str_buf [ 0 ] = '\0';
        write_nam_the ( the_rul ( rr ) );
        strcat ( str_buf, ".");
        write_nat ( num_rul ( rr ) );
        strcat ( str_buf, "\n" );
        app_write_rul ( rr );
        strcat ( str_buf, "\n  " );
        strcpy ( sel_str_arr [ sel_arr_tot ], str_buf );
        sel_obj_arr [ sel_arr_tot ] = rr;
        sel_arr_tot++;
      }
    }
    tt = nbr_rul_the ( fwd_btl_users_thy );
    for ( i = 1 ; i <= tt ; i++ ) {
      rr = val_rul_the ( fwd_btl_users_thy, i );
      if ( ( NotInSeq ( tmp_seq, rr ) ) && ( ! ( RulePrevPmdLevel ( rr ) ) ) ) {
        str_buf [ 0 ] = '\0';
        write_nam_the ( the_rul ( rr ) );
        strcat ( str_buf, ".");
        write_nat ( num_rul ( rr ) );
        strcat ( str_buf, "\n" );
        app_write_rul ( rr );
        strcat ( str_buf, "\n  " );
        strcpy ( sel_str_arr [ sel_arr_tot ], str_buf );
        sel_obj_arr [ sel_arr_tot ] = rr;
        sel_arr_tot++;
      }
    }
    kil ( tmp_seq );
    if ( sel_arr_tot ) {
      Popup_Sel_flag = btool_pmd_rule_selection;
      Popup_SelPMDRules_Dialog ( top_level, "Unused current-level user-theory rules\n  \nThe following rules have not been used; select each\nto preserve in the PROOFMETHOD, in which case they\nwill be available and editable at this proof level,\nand available (but not editable) at higher proof levels.\n  \n`Cancel' causes all rules to be preserved" );
    }
    else {
      PrintBToolProofMethod_Contd ();
    }

  } /* not print_all_rules_flag */

}

DumpNextPOFile ()
{
  int i, j, n, st, level;
  FILE * po;

  val_curMRIState ( &st, curr_obj );
  length_pob ( &level, st );
  sprintf ( buf, "%s/POB/%s.%d.po", cur_dir, GetName ( curr_obj ), level );
  po = fopen ( buf, "w" );
  if ( po == NULL ) {
    strcpy ( primary_string, "\"" );
    strcat ( primary_string, buf );
    strcat ( primary_string, "\" for writing" );
    AbortedMsgFile ( primary_string );
    Kill_bplatform_and_exit ( 1, 0 );
  }
  for ( i = first_btl_thy_to_display ; i <= last_btl_thy_to_display ; i++ ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    if ( i != first_btl_thy_to_display ) fprintf ( po, "&\n" );
    fprintf ( po, "THEORY %s", str_buf );
    n = nbr_rul_the ( i );
    if ( n ) {
      fprintf ( po, " IS " );
      for ( j = 1; j <= n ; j++ ) {
        if ( j != 1 ) fprintf ( po, ";" );
        if ( i == last_btl_thy_to_display ) { /* Lemmas */
          str_buf [ 0 ] = '\0';
          write_ver_rul_no_indent_no_nl ( val_rul_the ( i, j ) );
          if ( pvd_rul ( val_rul_the ( i, j ) ) == now_rul ) {
            fprintf ( po, "bproved(%s)", str_buf );
          }
          else {
            fprintf ( po, "(%s)", str_buf );
          }
	}
        else {
          if ( pvd_rul ( val_rul_the ( i, j ) ) == now_rul ) {
            fprintf ( po, "0" );
          }
          else {
            fprintf ( po, "1" );
	  }
	}
      }
    }
    fprintf ( po, " END" );
  }
  fprintf ( po, "\n" );
  fclose ( po );
}



/*
AutoProveStoreNewLemmaIn_proved_rr ( nn, rr )
int nn, rr;
{
/??? 
RestoreRecordedProofs couldn't initially store rr in proved_rr
because it didn't exist - it was created as a lemma during the
proof of a po; so nn was stored instead (BToolLemmas.nn).
Now, nn will be replaced by rr (if BToolLemmas.nn is proved
at this level).
???/
  int i = 1;
  while ( ( i < max_proved_rr ) && ( proved_rr [ i ] != nn ) ) {
/???/
if ( proved_rr [ i ] ) printf ( "AutoProveStoreNewLemmaIn_proved_rr - i %d:proved_rr [ %d ] = %d  \n", i, i, proved_rr [ i ] );
/???/
    i++;
  }
/???/
printf ( "===================================================== %d %d\n", nn, rr );
/???/
  if ( proved_rr [ i ] == nn ) {
     proved_rr [ i ] = rr;
/???/
printf ( "AutoProveStoreNewLemmaIn_proved_rr - replacing %d with %d\n", nn, rr );
{
char ccc [ 1000];
sprintf ( ccc, "AutoProveStoreNewLemmaIn_proved_rr - replacing %d with %d", nn, rr );
Popup_Info ( ccc );
}
/???/
  }
/???/
else {
printf ( "AutoProveStoreNewLemmaIn_proved_rr - BToolLemmas.%d not needed\n", nn );
{
char ccc [ 1000];
sprintf ( ccc, "AutoProveStoreNewLemmaIn_proved_rr - BToolLemmas.%d not needed", nn );
Popup_Info ( ccc );
}
}
/???/
}
*/

AutoProveStoreNewLemmaIn_proved_rr ( nn, rr )
int nn, rr;
{
/*** NOT QUITE !!! - nn the newly-created lemma ...
RestoreRecordedProofs couldn't initially store rr in proved_rr
because it didn't exist - it was created as a lemma during the
proof of a po; so nn was stored instead (BToolLemmas.nn).
Now, nn will be replaced by rr (if BToolLemmas.nn is proved
at this level).
***/
  int prf_seq, ll, k;
  int i = 1;
/***
printf ( "AutoProveStoreNewLemmaIn_proved_rr ( nn=%d rr=%d );\n", nn, rr );
***/
  while ( i < max_proved_rr ) {
    if (  proved_rr [ i ] ) {
/***
printf ( "%d: %d\n", i, proved_rr [ i ] );
***/
      prf_seq = proved_seq_rr [ i ];
      ll = len ( prf_seq );
      for ( k = 2 ; k <= ll ; k++ ) {  
/***
printf ( "    prf_seq.%d %d ", k, val ( prf_seq, k ) );
***/
        if (  val ( prf_seq, k ) == rr ) {
          val ( prf_seq, k ) = nn;
/***
printf ( "\nAutoProveStoreNewLemmaIn_proved_rr - proved_rr [ %d ]: %d -> %d\n", i, rr, val ( prf_seq, k ) );
***/
        }
      }
    }
    i++;
  }
/***
printf ( "\n" );
***/
}


int
RestoreRecordedProofs ( cc, level, autoprf_flag )
int cc, level, autoprf_flag;
{
  int tot, i, j, prf_seq, prf_seq_sub, prf_seq_hyp, prf_seq_breade;
  int rep, loc, obj, tt, nn, rr, stp_tot, stp, done, thy_name_matched;
  int goal; /* TO BE DONE */
  sprintf ( str_buf, "cp POB/%s.%d.btl btl_proof.dump", GetName ( cc ), level - 1 );
/***
printf ( "RestoreRecordedProofs ( cc=%d level=%d autoprf_flag=%d ) - `%s'\n", cc, level, autoprf_flag, buf );
***/
  execute ( str_buf );

  restore_n_btl_proof ( &rep );
  if ( ! rep ) {
    unlink ( "btl_proof.dump" );
    sprintf ( buf, "\n    Can't restore %s.%d.btl (Level %d) ... aborting\n", GetName ( cc ), level - 1, level );
    exit___contd ( 1, 1 ); /* to move to next level, etc. */
    return 0;
  }

  unlink ( "btl_proof.dump" );

  tot = 0;
  first_btl_prf ( &loc, &obj );
  while ( loc ) {
    tot++;
    xtr_pob_thy_str ( buf, obj );
/***
printf ( "RestoreRecordedProofs: theory name from btool proof file: %s\n", buf );
***/
    i = first_btl_thy_to_display;
    thy_name_matched = 0;
    while ( ( ! thy_name_matched ) && ( i <= last_btl_thy_to_display ) ) {
      str_buf [ 0 ] = '\0';
      write_nam_the ( i );
/***
printf ( "  current theory name from: %s - ", str_buf );
***/
      thy_name_matched = ( ( strcmp ( str_buf, ( char * ) buf ) == 0 ) != 0 );
/***
if ( thy_name_matched ) printf ( "matched\n" ); else printf ( "not matched\n" );
***/
      if ( ! thy_name_matched ) i++;
    }
    if ( ! thy_name_matched ) {
/***
printf ( "  *** BToolProof theory names do not match current theory names!\n" );
***/
      Popup_Info ( "BToolProof theory names do not match" );
      sprintf ( str_buf, "\n      Theory names of level %d BToolProofs\n      do not match those currently in use ... aborting\n", level );
      DisplayCurrWinText ( str_buf );
      exit___contd ( 1, 1 ); /* to move to next level, etc. */
      return 0;                 /* to  BMotif_io - ProcessB : case BT_BTL_AUP_M */
    }
/***
printf ( "pob_thy_str : %d\n", i );
***/
      val_pob_nn ( &nn, obj );
/***
printf ( "pob_nn : %d\n", nn );
***/
      tt = nbr_rul_the ( last_btl_thy_to_display );
      if ( ( i == last_btl_thy_to_display ) && ( nn > tt ) ) {
        rr = 0; /* BToolLemmas - not yet created! */
/***
printf ( "BToolLemmas - not yet created!\n", nn );
***/
      }
      else { 
        rr = val_rul_the ( i, nn );
      }
/***
printf ( "rr : %d\n", rr );
***/
      if    ( rr ) proved_rr [ tot ] = rr;
      else         proved_rr [ tot ] = nn; /* BToolLemma.nn will be created! */
      prf_seq = cre ( 25 );
      prf_seq_sub = cre ( 25 );
      prf_seq_hyp = cre ( 25 );
      prf_seq_breade = cre ( 25 );
      proved_seq_rr [ tot ] = prf_seq;
      proved_seq_sub_rr [ tot ] = prf_seq_sub;
      proved_seq_hyp_rr [ tot ] = prf_seq_hyp;
      proved_seq_breade_rr [ tot ] = prf_seq_breade;
      val_reason_depth ( &nn, obj );
/***
printf ( "reason_depth : %d\n", nn );
***/
      psh ( prf_seq, nn );
      psh ( prf_seq_sub, nn );
      psh ( prf_seq_hyp, nn );
      psh ( prf_seq_breade, nn );
/***
printf ( "+++++ pushed %d onto prf_seq\n", nn );
printf ( "+++++ pushed %d onto prf_seq_sub\n", nn );
printf ( "+++++ pushed %d - reason_depth - onto prf_seq_hyp (proved_seq_hyp_rr)\n", nn );
printf ( "+++++ pushed %d - reason_depth - onto prf_seq_breade (proved_seq_breade_rr)\n", nn );
***/

      length_prf_seq ( &stp_tot, obj );
/***
printf ( "length_prf_seq : %d\n", stp_tot );
***/
      for ( i = 1 ; i <= stp_tot ; i++ ) {
        valIth_prf_seq ( &stp, obj, i );
        val_stp_posn ( &nn, stp );
/***
printf ( "  %d stp_posn : %d\n", i, nn );
***/
        psh ( prf_seq_sub, nn );
        val_stp_type ( &nn, stp );
/***
printf ( "  %d stp_type : %d\n", i, nn );
***/


/***
printf ( "      j=%d nn=%d max_rul=%d 3*max_rul=%d\n", j, nn, max_rul, 3*max_rul );
***/

        if ( nn <= max_rul ) {
        /******
        A Rule
        ******/
          char old_thy [ 250 ];
/***
printf ( "  %d A Rule\n", i );
***/
          xtr_stp_thy_str ( buf, stp );
/***
printf ( "  %d stp_thy_str : |%s|\n", i, buf );
***/
          j = 2;
          done = 0;
          while ( ( ! done ) && ( j <= last_btl_thy_to_display ) ) {
            str_buf [ 0 ] = '\0';
            write_nam_the ( j );
            done = ( ( strcmp ( str_buf, ( char * ) buf ) == 0 ) != 0 );
            if ( ! done ) j++;
          }
          if ( ! done ) { /* theory doesn't exist */
            strcpy ( old_thy, ( char * ) buf );
            rr = -999;
	  }

          xtr_stp_rule_str ( buf, stp );
/***
printf ( "  %d stp_rule_str : |%s|\n", i, buf );
***/
          if ( rr != -999 ) {
            rr = search_theory ( j, ( char * ) buf );
            if ( rr == -999 ) { /* rule not in theory j */
              str_buf [ 0 ] = '\0';
              write_nam_the ( j );
              strcpy ( old_thy, str_buf );
	    }
	  }

          if ( rr == -999 ) { /* theory doesn't exist, or rule not in theory j */
             j = 2;
             while ( ( rr == -999 ) && ( j <= last_btl_thy_to_display ) ) {
/***
printf ( "old_thy=%s curr_thy=",old_thy );
str_buf [ 0 ] = '\0';
write_nam_the ( j );
printf ( "%s\n", str_buf );
***/
               rr = search_theory ( j, ( char * ) buf );
               if ( rr == -999 ) j++;
	     }
/***
printf ( "end of while: rr=%d\n", rr );
***/
             if ( rr != -999 ) {
               Popup_Info ( "Rule now in a different THEORY" );
               strcpy ( str_buf, "\n    Rule:\n\n      " );
               strcat ( str_buf, ( char * ) buf );
               strcat ( str_buf, "\n\n    is recorded as being in THEORY " );
               strcat ( str_buf, old_thy );
               strcat ( str_buf, "\n    but is now a rule of " );
               write_nam_the ( j );
               strcat ( str_buf, " ... continuing\n" );
               DisplayCurrWinText ( str_buf );
             }
             else {
               strcpy ( str_buf, "\n    Rule:\n\n      " );
               strcat ( str_buf, ( char * ) buf );
               strcat ( str_buf, "\n\n    is recorded as being in THEORY " );
               strcat ( str_buf, old_thy );
               strcat ( str_buf, "\n    but cannot be found in any THEORY ... aborting\n" );
               DisplayCurrWinText ( str_buf );
               exit___contd ( 1, 1 ); /* to move to next level, etc. */
               return 0;
	     }
          }
/***
printf ( "  %d rule : %d\n", i, rr );
***/
          psh ( prf_seq, rr );
          psh ( prf_seq_hyp, 0 );
          psh ( prf_seq_breade, gbreade [ goal ] );
/***
printf ( "+++++ pushed %d onto prf_seq\n", rr );
printf ( "+++++ pushed %d onto prf_seq_sub\n", nn );
printf ( "+++++ pushed 0 (rule - no hyp) onto prf_seq_hyp (proved_seq_hyp_rr)\n" );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/
	}



        else if ( nn >= ( 3 * max_rul ) ) {
/***
printf ( "  %d A lem_gol\n", i );
***/
          xtr_stp_rule_str ( buf, stp );
/***
printf ( "  %d stp_rule_str : |%s|\n", i, buf );
***/
          strcpy ( str_buf, ( char * ) buf );
/*
          if ( autoprf_flag || ppf_flag ) { /? added ppf_flag 150499 ?/
*/
          if ( autoprf_flag ) {

            psh ( prf_seq, nn );
            psh ( prf_seq_hyp, 0 );
            psh ( prf_seq_breade, gbreade [ goal ] );
/***
printf ( "+++++ pushed %d (%d) onto prf_seq\n", nn, nn - ( 3 * max_rul ) );
printf ( "+++++ pushed %d onto prf_seq_sub\n", nn );
printf ( "+++++ pushed 0 (lem_gol - no hyp) onto prf_seq_hyp (proved_seq_hyp_rr)\n" );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/

	  }



          else {
/***
printf ( "looking at BToolLemmas (%d)\n", nn );
***/
            rr = search_theory ( last_btl_thy_to_display, ( char * ) buf );
            if ( rr == -999 ) {
              strcpy ( str_buf, "\n  Can't locate " );
              write_nam_the ( last_btl_thy_to_display );
              strcat ( str_buf, " rule:\n\n    " );
              strcat ( str_buf, ( char * ) buf );
              strcat ( str_buf, " ... aborting\n" );
              DisplayCurrWinText ( str_buf );
              exit___contd ( 1, 1 ); /* to move to next level, etc. */
              return 0;
	    }
            else {
              psh ( prf_seq, rr + ( 3 * max_rul ) );
              psh ( prf_seq_hyp, 0 );
              psh ( prf_seq_breade, gbreade [ goal ] );
/***
printf ( "+++++ pushed %d (%d) onto prf_seq\n", rr + ( 3 * max_rul ), rr );
printf ( "+++++ pushed %d onto prf_seq_sub\n", nn );
printf ( "+++++ pushed 0 (lem_gol - no hyp) onto prf_seq_hyp (proved_seq_hyp_rr)\n" );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/
	    }
          }
	}

        else if ( nn <= ( 2 * max_rul ) ) {
          /******
          A spe_gol
          ******/
/***
printf ( "  %d A spe_gol\n", i );
***/
          if ( ( nn - max_rul ) == HYP_gol ) {
/***
printf ( "  %d A hyp_gol\n", i );
***/
            xtr_stp_rule_str ( buf, stp );
/***
printf ( "  %d stp_rule_str : |%s|\n", i, buf );
***/
            strcpy ( str_buf, ( char * ) buf );
            rr = read_frm_str_buf;
            psh ( prf_seq, nn );
            psh ( prf_seq_hyp, rr );
            psh ( prf_seq_breade, gbreade [ goal ] );
/***
printf ( "+++++ pushed %d (%d) onto prf_seq\n", nn, nn - max_rul );
printf ( "+++++ pushed %d onto prf_seq_sub\n", nn );
printf ( "+++++ pushed %d (spe_gol) onto prf_seq_hyp (proved_seq_hyp_rr)\n", rr );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/
	  }

          else {
/***
printf ( "  %d Not a hyp_gol/lem_gol\n", i );
***/
            psh ( prf_seq, nn );
            psh ( prf_seq_hyp, 0 );
            psh ( prf_seq_breade, gbreade [ goal ] );
/***
printf ( "+++++ pushed %d (%d) onto prf_seq\n", nn, nn - max_rul );
printf ( "+++++ pushed %d onto prf_seq_sub\n", nn );
printf ( "+++++ pushed 0 (not a hyp_gol/lem_gol) onto prf_seq_hyp (proved_seq_hyp_rr)\n" );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/
	  }
	}
        else {
          /******
          A frm_gol
          ******/
/***
printf ( "  %d A frm_gol\n", i );
***/
          psh ( prf_seq, nn );
          psh ( prf_seq_hyp, 0 );
          psh ( prf_seq_breade, gbreade [ goal ] );
/***
printf ( "+++++ pushed %d (%d) onto prf_seq\n", nn, nn - ( 2 * max_rul ) );
printf ( "+++++ pushed %d onto prf_seq_sub\n", nn );
printf ( "+++++ pushed 0 (frm_gol) onto prf_seq_hyp (proved_seq_hyp_rr)\n" );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/
	}

      } /* for i = 1 ... */

/***
printf ( "- - - - - - - - >>>  ONE PROOF RESTORED\n" );
***/

    next_btl_prf ( &loc, &obj, loc, obj );

  }
  return 1;
}

#endif

void
RemoveRecordedProof ( r )
int r;
{
  int k = 1;
  int i, l;
  int live_seq;
/***
printf ( "RemoveRecordedProof - %d.%d(%d)\n", the_rul ( r ), num_rul ( r ), r  );
***/
/***
print_live_seq ( "RemoveRecordedProof ini" );
***/
  while ( ( k < max_proved_rr ) && ( proved_rr [ k ] != r ) ) { k++; }
  if ( k == max_proved_rr ) {
/***
printf ( "No proof recorded\n" );
***/
    return;
  }

/***
printf ( "proved_rr [ %d ] : %d\n", k, proved_rr [ k ] );
***/

/***
printf ( "proved_seq_rr [ %d ]           = %4d (kil)\n", k, proved_seq_rr [ k ] );
printf ( "proved_seq_sub_rr [ %d ]       = %4d (kil)\n", k, proved_seq_sub_rr [ k ] );
***/
  kil ( proved_seq_rr [ k ] );
  kil ( proved_seq_sub_rr [ k ] );

  if ( proved_fwd_btl_rr [ k ] ) {
/***
printf ( "proved_fwd_btl_rr             = %4d (kil)\n", proved_fwd_btl_rr [ k ] );
***/
    kil ( proved_fwd_btl_rr [ k ] );
  }

  /***
  if proved_seq_hyp_rr [ k ] is non zero,
  iterate killing all its members;
  kill it (even if it was of length zero)
  ***/
  if ( proved_seq_hyp_rr [ k ] ) {
    l = len ( proved_seq_hyp_rr [ k ] );
/***
printf ( "len ( proved_seq_hyp_rr [ %d ] ) = %d (don't kill 1st, or zero members)\n", k, l );
***/
    for ( i = 2; i <= l ; i++ ) {
      if ( val ( proved_seq_hyp_rr [ k ], i ) ) {
/***
printf ( "proved_seq_hyp_rr [ %d ] [ %d ] = %4d (kil)\n", k, i, val ( proved_seq_hyp_rr [ k ], i ) );
***/
        kil ( val ( proved_seq_hyp_rr [ k ], i ) );
      }
    }
/***
printf ( "proved_seq_hyp_rr [ %d ]       = %4d (kil)\n", k, proved_seq_hyp_rr [ k ] );
***/
    kil ( proved_seq_hyp_rr [ k ] );
  }

  /***
  if proved_seq_breade_rr [ k ] is non zero,
  iterate killing all its members;
  kill it (even if it was of length zero)
  ***/
  if ( proved_seq_breade_rr [ k ] ) {
    l = len ( proved_seq_breade_rr [ k ] );
/***
printf ( "len ( proved_seq_breade_rr [ %d ] ) = %d (don't kill 1st, or zero members)\n", k, l );
***/
    for ( i = 2; i <= l ; i++ ) {
      if ( val ( proved_seq_breade_rr [ k ], i ) ) {
/***
printf ( "proved_seq_breade_rr [ %d ] [ %d ] = %4d (kil)\n", k, i, val ( proved_seq_breade_rr [ k ], i ) );
***/
        kil ( val ( proved_seq_breade_rr [ k ], i ) );
      }
    }
/***
printf ( "proved_seq_breade_rr [ %d ]       = %4d (kil)\n", k, proved_seq_breade_rr [ k ] );
***/
    kil ( proved_seq_breade_rr [ k ] );
  }

  proved_rr [ k ] = 0;
  proved_seq_rr [ k ] = 0;
  proved_seq_sub_rr [ k ] = 0;
  proved_fwd_btl_rr [ k ] = 0;
  proved_seq_hyp_rr [ k ] = 0;
  proved_seq_breade_rr [ k ] = 0;
/***
print_live_seq ( "RemoveRecordedProof fini" );
***/
}

RecordProof ()
{
  int i = 1;
  int prf_seq, prf_seq_sub, prf_seq_hyp, prf_seq_breade, goal;
  int ss;
/***
  printf ( "RecordProof - %d.%d(%d) top node=%d\n", the_rul ( run_man_prf_r ), num_rul ( run_man_prf_r ), run_man_prf_r, run_man_prf_p );
***/
/***
print_live_seq ( "RecordProof ini" );
***/
  while ( ( i < max_proved_rr ) && ( proved_rr [ i ] != 0 ) ) { i++; }
  if ( i == max_proved_rr ) {
/***
printf ( "Proof memory full\n" );
***/
    Popup_Error ( "  Proof memory full - create another Proof Level!  " );
    return;
  }


  proved_rr [ i ] = run_man_prf_r;
  prf_seq = cre ( 25 );
  prf_seq_sub = cre ( 25 );
  prf_seq_hyp = cre ( 25 );
  prf_seq_breade = cre ( 25 );
  proved_seq_rr [ i ] = prf_seq;
  proved_seq_sub_rr [ i ] = prf_seq_sub;
  proved_seq_hyp_rr [ i ] = prf_seq_hyp;
  proved_seq_breade_rr [ i ] = prf_seq_breade;

#ifdef BTOOLKIT_FLAG

/*** push the reasoning depth on three seqs ***/
  psh ( prf_seq, btl_fwd_tac_depth );
  psh ( prf_seq_sub, btl_fwd_tac_depth );
  psh ( prf_seq_hyp, btl_fwd_tac_depth );
  psh ( prf_seq_breade, btl_fwd_tac_depth );
/***
printf ( "+++++ pushed %d onto prf_seq\n", btl_fwd_tac_depth );
printf ( "+++++ pushed %d onto prf_seq_sub\n", btl_fwd_tac_depth );
printf ( "+++++ pushed %d (btl_fwd_tac_depth) onto prf_seq_hyp (proved_seq_hyp_rr)\n", btl_fwd_tac_depth );
printf ( "+++++ pushed %d (btl_fwd_tac_depth) onto prf_seq_breade (proved_seq_breade_rr)\n", btl_fwd_tac_depth );
***/

#else

  psh ( prf_seq, 0 );
  psh ( prf_seq_sub, 0 );
  psh ( prf_seq_hyp, 0 );
  psh ( prf_seq_breade, 0 );
/***
printf ( "+++++ pushed 0 onto prf_seq\n" );
printf ( "+++++ pushed 0 onto prf_seq_sub\n" );
printf ( "+++++ pushed 0 (btl_fwd_tac_depth) onto prf_seq_hyp (proved_seq_hyp_rr)\n" );
printf ( "+++++ pushed 0 (btl_fwd_tac_depth) onto prf_seq_breade (proved_seq_breade_rr)\n" );
***/

#endif

/***
printf ( "    proved_seq_rr [ %d ]     = %4d (cre)\n", i, prf_seq );
printf ( "    proved_seq_sub_rr [ %d ] = %4d (cre)\n", i, prf_seq_sub );
printf ( "    proved_seq_hyp_rr [ %d ] = %4d (cre)\n", i, prf_seq_hyp );
printf ( "    proved_seq_breade_rr [ %d ] = %4d (cre)\n", i, prf_seq_breade );
***/



  /***************************************************************************/

#ifdef BTOOLKIT_FLAG

#ifdef BTOOL_PROVER_NEW

  /***
  copy proof tree
  ***/
  CreCopyProofTree ();

  run_man_prf_p_save = run_man_prf_p;
  run_man_prf_p = run_man_prf_p_copy;
/***
printf ( "RecordProof\nrun_man_prf_p_save=%d run_man_prf_p=%d\n", run_man_prf_p_save, run_man_prf_p );
***/

#endif /* BTOOL_PROVER_NEW */

#endif /* BTOOLKIT_FLAG */

  /***************************************************************************/


  i = run_man_prf_p;
  while ( i != fath_nod ( run_man_prf_p ) ) {

    if ( cptr_nod ( i ) == 0  ) {
      goal = info_nod ( i );
/***
  str_buf [ 0 ] = '\0';
  write_gol_prf ( goal );
  str_buf [ strlen ( str_buf ) - 2 ] = '\0';
  printf ( "  -- RecordProof (node i=%d) (g=%d) %s\n", i, goal, str_buf );
***/
      if ( ( def_rul_gol ( goal ) ) && ( ! ( def_spe_gol ( goal ) ) ) ) {
        psh ( prf_seq, rul_gol ( goal ) );
        psh ( prf_seq_sub, pssubrr [ GetLookUpNode ( i ) ] );
        psh ( prf_seq_hyp, 0 );
        psh ( prf_seq_breade, gbreade [ goal ] );
/***
str_buf [ 0 ] = '\0';
write_nam_the ( the_rul ( rul_gol ( goal ) ) );
strcat ( str_buf, "." );
CreNumInBuf ( str_buf, num_rul ( rul_gol ( goal ) ) );
printf ( "+++++ pushed %d onto prf_seq\n", rul_gol ( goal ) );
printf ( "+++++ pushed %d onto prf_seq_sub\n", pssubrr [ GetLookUpNode ( i ) ] );
printf ( "+++++ pushed 0 (rul_gol %s) onto prf_seq_hyp (proved_seq_hyp_rr)\n", str_buf );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/
/***
  printf ( "\n         rule_gol %d prf_seq_sub %d prf_seq_hyp %d\n", rul_gol ( goal ), pssubrr [ GetLookUpNode ( i ) ], 0 );
***/
      }

      else if ( def_spe_gol ( goal ) ) {

        if ( ( spe_gol ( goal ) ) == HYP_gol ) {
          int hh;
          psh ( prf_seq, spe_gol ( goal ) + max_rul );
          ss = cre ( 100 );
/***
printf ( ">>>>> RecordProof spe_gol cre: ss=%d\n", ss );
***/
          lst_hyp_prf ( run_man_prf_p, i, ss );
          psh ( prf_seq_sub, pssubrr [ GetLookUpNode ( i ) ]%hyp_mod_val );
/***
printf ( "\n&&&&&&&&  pssubrr [ GetLookUpNode ( i ) ]/hyp_mod_val=%d\n", pssubrr [ GetLookUpNode ( i ) ]/hyp_mod_val );
***/
          str_buf [ 0 ] = '\0';
          write_frm_res( frm_hyp ( val ( ss, ( pssubrr [ GetLookUpNode ( i ) ]/hyp_mod_val ) ) ), 0 );
          hh = read_frm_str_buf;
          psh ( prf_seq_hyp, hh );
          psh ( prf_seq_breade, gbreade [ goal ] );
/***
printf ( "+++++ pushed %d (%d) onto prf_seq\n", spe_gol ( goal ) + max_rul, spe_gol ( goal ) );
printf ( "+++++ pushed %d onto prf_seq_sub\n", pssubrr [ GetLookUpNode ( i ) ]%hyp_mod_val );
printf ( "+++++ pushed %d (HYP_gol) onto prf_seq_hyp (proved_seq_hyp_rr)\n", hh );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/
          kil ( ss );
/***
printf ( "\n         HYP_gol %d prf_seq_sub %d prf_seq_hyp %d\n", spe_gol ( goal ) + max_rul, pssubrr [ GetLookUpNode ( i ) ]%hyp_mod_val, hh );
***/
	}

        else if ( ( spe_gol ( goal ) ) == LEM_gol ) {
          psh ( prf_seq, ( rul_gol ( goal ) + ( 3 * max_rul ) ) );
          psh ( prf_seq_sub, 0 );
          psh ( prf_seq_hyp, 0 );
          psh ( prf_seq_breade, gbreade [ goal ] );
/***
printf ( "+++++ pushed %d (%d) onto prf_seq\n", ( rul_gol ( goal ) + ( 3 * max_rul ) ), rul_gol ( goal ) );
printf ( "+++++ pushed %d onto prf_seq_sub\n", 0 );
printf ( "+++++ pushed 0 (LEM_gol) onto prf_seq_hyp (proved_seq_hyp_rr)\n" );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/
/***
  printf ( "\n         LEM_gol %d prf_seq_sub %d prf_seq_hyp %d\n", rul_gol ( goal ) + ( 3 * max_rul ), 0, 0 );
***/
	}

        else if ( ( spe_gol ( goal ) ) == ARI_gol ) {
          psh ( prf_seq, spe_gol ( goal ) + max_rul );
          psh ( prf_seq_sub, pssubrr [ GetLookUpNode ( i ) ] );
          psh ( prf_seq_hyp, 0 );
          psh ( prf_seq_breade, gbreade [ goal ] );
/***
printf ( "+++++ pushed %d (%d) onto prf_seq\n", spe_gol ( goal ) + max_rul, spe_gol ( goal ) );
printf ( "+++++ pushed %d onto prf_seq_sub\n", pssubrr [ GetLookUpNode ( i ) ] );
printf ( "+++++ pushed 0 (ARI_gol) onto prf_seq_hyp (proved_seq_hyp_rr)\n" );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/
/***
  printf ( "\n         ARI_gol %d prf_seq_sub %d prf_seq_hyp %d\n", spe_gol ( goal ) + max_rul, pssubrr [ GetLookUpNode ( i ) ], 0 );
***/
	}

        else {
          psh ( prf_seq, spe_gol ( goal ) + max_rul );
          psh ( prf_seq_sub, 0 );
          psh ( prf_seq_hyp, 0 );
          psh ( prf_seq_breade, gbreade [ goal ] );
/***
printf ( "+++++ pushed %d (%d) onto prf_seq\n",  spe_gol ( goal ) + max_rul, spe_gol ( goal ) );
printf ( "+++++ pushed %d onto prf_seq_sub\n", 0 );
printf ( "+++++ pushed 0 (other spe_gol) onto prf_seq_hyp (proved_seq_hyp_rr)\n" );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/
/***
  printf ( "\n         spe_gol %d prf_seq_sub %d prf_seq_hyp %d\n", spe_gol ( goal ) + max_rul, 0, 0 );
***/
	}
      }

      else {  /* oth_gol */
        psh ( prf_seq, val_root_frm ( frm_gol ( goal ) ) + ( 2 * max_rul ) );
        psh ( prf_seq_sub, pssubrr [ GetLookUpNode ( i ) ] );
        psh ( prf_seq_hyp, 0 );
        psh ( prf_seq_breade, gbreade [ goal ] );
/***
printf ( "+++++ pushed %d (%d) onto prf_seq\n",  val_root_frm ( frm_gol ( goal ) ) + ( 2 * max_rul ), val_root_frm ( frm_gol ( goal ) ) );
printf ( "+++++ pushed %d onto prf_seq_sub\n", pssubrr [ GetLookUpNode ( i ) ] );
printf ( "+++++ pushed 0 (oth_gol) onto prf_seq_hyp (proved_seq_hyp_rr)\n" );
printf ( "+++++ pushed %d onto prf_seq_breade (proved_seq_breade_rr)\n", gbreade [ goal ] );
***/
/***
  printf ( "\n         oth_gol %d prf_seq_sub %d prf_seq_hyp %d\n", val_root_frm ( frm_gol ( goal ) ) + ( 2 * max_rul ), pssubrr [ GetLookUpNode ( i ) ], 0 );
***/
      }
    }
    if ( cptr_nod ( i ) == len ( sons_nod ( i ) ) ) { /* printed last son */
      cptr_nod ( i ) = 0;
      i = fath_nod ( i );
    }
    else if ( cptr_nod ( i ) == 0  ) {                /* get first son */
      cptr_nod ( i ) = 1;
      i = fst ( sons_nod ( i ) );
    } else {                                          /* get next son */
      cptr_nod ( i )++;
      i = val ( sons_nod ( i ), cptr_nod ( i ) );
    }
/***
printf ( "            step complete\n" );
***/
  }

  /***************************************************************************/

#ifdef BTOOLKIT_FLAG

#ifdef BTOOL_PROVER_NEW

  run_man_prf_p = run_man_prf_p_save;

  kil_nod ( run_man_prf_p_copy );

#endif /* BTOOL_PROVER_NEW */

#endif /* BTOOLKIT_FLAG */

  /***************************************************************************/

/***
printf ( "RecordProof complete\n" );
***/
/***
print_live_seq ( "RecordProof fini" );
***/
}


#ifdef BTOOLKIT_FLAG

PrintProofError ( r, n, i )
int r, n, i;
{
  str_buf [ 0 ] = '\0';
  write_nam_the ( the_rul ( r ) );
  strcat ( str_buf, ".");
  write_nat ( num_rul ( r ) );
  printf ( "\n\n       %s - Print Proof Error %d (%d)\n", str_buf, n, i );
  AbortedMsg ();
  Kill_bplatform_and_exit ( 1, 0 );
}

#endif

/***
r is rule
flag = 1 => print proof tree
flag = 0 => print proof
             autoprf_flag => AutpProver
             ppf_flag     => ProofPrinter
***/
int
ReconstructProofAndPrint ( r, flag, hyp_analysis_flag, autoprf_flag, ppf_flag )
int r, flag, autoprf_flag, ppf_flag, hyp_analysis_flag;
{
  void CreProofTreeDialog ();
  int p, i, prev_i, g, f, nn;
  int k = 1;
  int prf_seq, prf_seq_sub, prf_seq_hyp, prf_seq_breade,
      ll, op, op_sub, op_hyp, op_breade, op_breade_copy;
  int b;
  char rul_buf [ 2500 ];
  int success = 0;
  int reason_depth;

/***
str_buf [ 0 ] = '\0';
write_nam_the ( the_rul(r) );
printf ( "\n------------------------------------------------\n" );
printf ( "    ReconstructProofAndPrint ( %d (%s.%d) %d %d %d %d )\n", r, str_buf, num_rul(r), flag, hyp_analysis_flag, autoprf_flag, ppf_flag );
str_buf [ 0 ] = '\0';
***/

  while ( ( k < max_proved_rr ) && ( proved_rr [ k ] != r ) ) { k++; }
  if ( k == max_proved_rr ) {
/*
    Popup_Info ( "  No proof recorded  " );
*/
    return;
  }

  exec_prf = FALSE;
  mod_rul_sys ( num_rul ( r ) );
  mod_theo_sys ( num_the ( the_rul ( r ) ) );

  prf_seq = proved_seq_rr [ k ];
  prf_seq_sub = proved_seq_sub_rr [ k ];
  prf_seq_hyp = proved_seq_hyp_rr [ k ];
  prf_seq_breade = proved_seq_breade_rr [ k ];


  ll = len ( prf_seq );

#ifdef BTOOLKIT_FLAG

  /*** save old fwd tac & get the reasoning depth ***/
  str_buf [ 0 ] = '\0';
  write_frm_res( fwd_tac_the ( val_theo_sys ), 0 );
  strcpy ( additional_string, str_buf );
  reason_depth = val ( prf_seq, 1 );
  {
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
    strcat ( str_buf, btl_fwd_tac [ reason_depth ] );
    strcat ( str_buf, ")~" );
/***
printf ( "tactic 2\n%s\n", str_buf );
***/
  }
  f = read_frm_str_buf;
  if ( f != -999 ) {
    mod_fwd_tac_the ( val_theo_sys, f );
  }
  else {
    sprintf ( buf, " Forward tactic %d does not parse ", reason_depth );
    Popup_Info ( buf );
  }

#endif

  prelude_prf ( the_rul ( r ), TRUE );
  p = cre_prf ( r );
  i = p;

/***
  str_buf [ 0 ] = '\0';
  write_nam_the ( the_rul ( r ) );
  strcat ( str_buf, "." );
  write_nat ( num_rul ( r ) );
  printf ( "-----------------------------------------------------------------\n" );
  printf ( "  RECORDED PROOF of %s (top node=%d):\n", str_buf, p );
  printf ( "    proof length %d\n", ll - 1 );
  printf ( "    fwd reasoning depth %d\n", val ( prf_seq, 1 ) );
  for ( k = 2 ; k <= ll ; k++ ) {
  op = val ( prf_seq, k );
  op_sub = val ( prf_seq_sub, k );
  op_hyp = val ( prf_seq_hyp, k );
  op_breade = val ( prf_seq_breade, k );
  if ( op <= max_rul ) {
    str_buf [ 0 ] = '\0';
    write_nam_the ( the_rul ( op ) );
    strcat ( str_buf, "." );
    write_nat ( num_rul ( op ) );
    printf ( "    step %2d (k=%2d): %d (rul_gol %s - sub %d - hyp %d - breade %d)\n", k - 1, k, op, str_buf, op_sub, op_hyp, op_breade );
  }
  else if ( op >= ( 3 * max_rul ) ) {
    printf ( "    step %2d (k=%2d): %d (LEM_gol - sub %d - hyp %d - breade %d)\n", k - 1, k, op - ( 3 * max_rul ), op_sub, op_hyp, op_breade );
  }
  else if ( op <= ( 2 * max_rul ) ) {
    str_buf [ 0 ] = '\0';
    write_spe_gol ( num_rul (op - max_rul ) );
    printf ( "    step %2d (k=%2d): %d (spe_gol %s - sub %d - hyp %d - breade %d)\n", k - 1, k, op - max_rul, str_buf, op_sub, op_hyp, op_breade );
  }
  else {
    printf ( "    step %2d (k=%2d): %d (oth_gol - sub %d - hyp %d - breade %d)\n", k - 1, k, op - ( 2 * max_rul ), op_sub, op_hyp, op_breade );
  }
}
printf ( "  END OF RECORDED PROOF\n" );
printf ( "-----------------------------------------------------------------\n" );
***/


  i = p;
  prev_i = i;
  k = 2;
  b = TRUE;
  while ( ( k <= ll ) && ( b == TRUE ) ) {
    g = info_nod ( i );
    f = frm_gol ( g );
    if ( def_tac_gol ( g ) == TRUE ) {
      tac_prf = tac_gol ( g );
      tac_ptr_prf = tpt_gol ( g );
      fwd_tac_prf = ftac_gol ( g );
      fwd_tac_ptr_prf = ftpt_gol ( g );
      end_of_tac_prf = FALSE;
    }

    op = val ( prf_seq, k );
    op_sub = val ( prf_seq_sub, k );
    op_hyp = val ( prf_seq_hyp, k );
    op_breade = val ( prf_seq_breade, k );

    if ( op_breade ) {
      op_breade_copy = cre ( 25 );
/***
printf ( " *** k = %d: op_breade %d - so copied into op_breade_copy %d\n", k, op_breade, op_breade_copy ); fflush ( stdout );
printf ( "  ----- op_breade:\n" ); prt_seq_dave ( op_breade ); fflush ( stdout );
***/
/*
      cop ( op_breade, op_breade_copy );
*/
      cpy_seq_and_contents_dave ( op_breade, op_breade_copy );
/***
printf ( " ----- op_breade_copy:\n" ); prt_seq_dave ( op_breade_copy ); fflush ( stdout );
***/
    }
    else {
/***
printf ( " *** k = %d: op_breade = 0 - so op_breade_copy = 0\n", k ); fflush ( stdout );
***/
      op_breade_copy = 0;
    }

/***
str_buf [ 0 ] = '\0';
write_gol_prf_no_nl ( g );
printf ( "\n-----\n    goal: %s\n    step %d/%d -- g=%d f=%d i=%d\n-----\n", str_buf, k - 1, ll, g, f, i ); fflush ( stdout );
printf ( "    op=%d op_sub=%d op_hyp=%d\n", op, op_sub, op_hyp ); fflush ( stdout );
***/

    if ( op <= max_rul ) {              /* rul_gol */
      str_buf [ 0 ] = '\0';
      write_nam_the ( the_rul ( op ) );
      sprintf ( rul_buf, "%s.%d", str_buf, num_rul ( op ) );
      {
        register int c,opp1;
        c=cns_rul(op);
        opp1=val_root_frm(c);
        clr_chk_frm;
        if( opp1==MAC_sym ){   /* rewrite rule */
          {
            register int c,lnod,opp2,li,la;
            c=cns_rul(op);
            lnod=left_node_frm(c);
            opp2=val_tree(c,lnod);
            if ( (is_in_frm(f,opp2)==TRUE) ||
                 (letter_sym(opp2)==TRUE)  ||
                 (opp2==JK2_sym)           ||
                 (opp2==JK1_sym)              ) {
              la=ant_rul(op);
              li=cre(len(la));
              b = test2_eql_rul_prf_func(op,p,i,la,f,op_sub,c,lnod,li);
              kil(li);
            }
            else {
              b = FALSE;
            }
          }
        }                     /* not rewrite rule */
        else if ( chk_frm(c,f)==TRUE ) {
/***
printf ( "not rewrite rule (op_breade_copy=%d)\n", op_breade_copy ); fflush ( stdout );
***/
 b = test_nrm_rul_prf_func(p,i,op, /* app_rule_flag = */ 2, /* prf_seq_breade_copy = */ op_breade_copy );
        } else {
          b = FALSE;
        }
        kil_content_input_prf;
      }
      if ( b ) { mod_rul_gol( g, op ); }
    }

    else if ( op >= ( 3 * max_rul ) ) {  /* LEM_gol */
      register int s, f, h, v, j;

      b=TRUE;

#ifndef BTOOLKIT_FLAG

      strcpy ( rul_buf, "LEM" );
      i = prev_i;
#else

      strcpy ( str_buf, "LEMMA (" );
      write_nam_the ( the_rul ( op - ( 3 * max_rul ) ) );
      strcat ( str_buf, "." );
      CreNumInBuf ( str_buf, num_rul ( op - ( 3 * max_rul ) ) );
      strcat ( str_buf, ")" );
      strcpy ( rul_buf, str_buf );

/*
      if ( b && ( autoprf_flag || ppf_flag ) ) {  /? ppf_flag added 150499 ?/
*/
      if ( b && autoprf_flag ) {
        str_buf [ 0 ] = '\0';
        s=cre(100);
        lst_hyp_prf(p,i,s);
        rev(s);
        save_MAX_COL_RES;
        mod_MAX_COL_RES(999999);
        b=TRUE;
        itr(s,j,h,{
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
        write_gol_prf_no_nl ( g );
        f = read_frm_str_buf;
        if ( f != -999 ) {
          read_rul_the ( last_btl_thy_to_display, f ); /* BToolLemmas */
        }
        else {
          b = FALSE;
	}
/***
{
char tmp_char [ 1000 ];
int nnn = nbr_rul_the ( last_btl_thy_to_display );
strcpy ( tmp_char, str_buf );
str_buf [ 0 ] = '\0';
write_nam_the ( last_btl_thy_to_display );
printf ( "|||------------------|||-------------------|||\nJust created %s.%d (recorded as %d)\n%s\n|||------------------|||-------------------|||\n", str_buf, nnn, op, tmp_char ); fflush ( stdout );
strcpy ( str_buf, tmp_char );
}
***/
        if ( b ) {
          nn = nbr_rul_the ( last_btl_thy_to_display );
          if ( val_rul_the ( last_btl_thy_to_display, nn ) + ( 3 * max_rul )
                                                                           != op )
            AutoProveStoreNewLemmaIn_proved_rr
             ( val_rul_the ( last_btl_thy_to_display, nn ) + ( 3 * max_rul ), op );
	}
      } /* ( b && autoprf_flag ) */

#endif

      if ( b ) { 
        mod_spe_gol ( g, LEM_gol );
        mod_rul_gol ( g, op - ( 3 * max_rul ) );
      }
    } /* ( op >= ( 3 * max_rul ) ) LEM_gol */

    else if ( op < ( 2 * max_rul ) ) {  /* spe_gol */
      switch ( op - max_rul ) {
      case AND_gol :
        strcpy ( rul_buf, "AND" );
        b = and_prf ( i, g, f );
        break;
      case DED_gol :
        strcpy ( rul_buf, "DED" );
        b = ded_prf ( r, p, i, g, f );
        break;
      case EQL_gol :
        strcpy ( rul_buf, "EQL" );
        b = eql_prf ( g, f );
        break;
      case ARI_gol :
        strcpy ( rul_buf, "ARI" );
	{
          register int w, s, ff, gl;
          int arith_prf_is_int;
/***
printf ( "reconstructing - test_ari_prf_func(%d,%d)\n",f,op_sub); fflush ( stdout );
***/
          if ( test_ari_prf_func(f,op_sub)==TRUE ) {
            w=comp_arith_prf(f,op_sub,&arith_prf_is_int);         
            if   ( arith_prf_is_int ) s=cre_int_frm(w);
            else                      s=cre_frm(w);
            ff=cre_mod_tree(f,op_sub,s);
            kil(s);
            gl=cre_gol(ff);
            cre_nod(gl,i);
            mod_spe_gol(g,ARI_gol);
            b = TRUE;
	  }
          else {
            b = FALSE;
	  }
	}
        break;
      case SUB_gol :
        strcpy ( rul_buf, "" );
        b = sub_prf_func ( p, i, g, f );
        break;
      case GEN_gol :
        strcpy ( rul_buf, "GEN" );
        b = gen_prf ( p, i, g, f );
        break;
      case HYP_gol :
        {
          register int s, op, hf, lnod, hyp_num;
          strcpy ( rul_buf, "HYP (" );
          s=cre(100);
          lst_hyp_prf(p,i,s);
          str_buf [ 0 ] = '\0';
          write_frm_res ( op_hyp, 0 );
          strcat ( rul_buf, str_buf );
          strcat ( rul_buf, ")" );
/***
printf ( "    1 HYP (%s) step %d/%d -- g=%d f=%d i=%d\n", rul_buf , k - 1, ll, g, f, i ); fflush ( stdout );
***/
          hyp_num = search_hypothesis ( s ); /* str_buf contains the hyp */
/***
printf ( "    hyp_num %d\n", hyp_num ); fflush ( stdout );
***/
          if ( hyp_num == -999 ) {
            sprintf ( buf, "\n\n    Step %d - can't locate:\n      %s\n\n    in current hypothesis\n", k - 1, str_buf );
            DisplayCurrWinText ( buf );
            b = FALSE;
	  }
          else {
            hf = frm_hyp(val(s,hyp_num));
/***
printf ( "    2 HYP -- g=%d f=%d i=%d op_sub %d\n", g, f, i, op_sub ); fflush ( stdout );
***/
            op=val_root_frm(hf);
/***
printf ( "    3 HYP -- g=%d f=%d i=%d op_sub %d\n", g, f, i, op_sub ); fflush ( stdout );
***/
            if( (op==EQL_sym) || (op==EQV_sym) ) {
/***
printf ( "        4 HYP (EQL_sym || op==EQV_sym) -- g=%d f=%d i=%d op_sub %d\n", g, f, i, op_sub ); fflush ( stdout );
***/
               lnod=left_node_frm(hf);
               op=val_tree(hf,lnod);
               if ( is_in_frm(f,op)==TRUE ) {
/***
printf ( "           5 HYP is_in_frm = TRUE -- g=%d f=%d i=%d op_sub %d\n", g, f, i, op_sub ); fflush ( stdout );
***/
                 b = test2_eql_hyp_prf_func(p,i,hf,lnod,f,op_sub);
	       }
               else {
                 b = FALSE;
	       }
	    }
            else {
/***
printf ( "        6 HYP ! (EQL_sym || op==EQV_sym) -- g=%d f=%d i=%d\n        test_hyp_prf_func(p=%d,i=%d,hf=%d,f=%d,op_sub=%d)\n", g, f, i,p,i,hf,f,op_sub  ); fflush ( stdout );
***/
               b = test_hyp_prf_func(p,i,hf,f,op_sub);
	    }
            if ( b == TRUE ) {
/***
printf ( "    HYP OK\n" ); fflush ( stdout );
***/
              mod_uti_hyp(val(s,/* op_sub */ hyp_num));
              mod_spe_gol(g,HYP_gol);
              mod_hyp_gol(g,val(s,/* op_sub */ hyp_num));    /* <<<<<<<<<<<<<<<< */
	    }
/***
            else {
printf ( "    HYP UNSUCCESSFUL\n" ); fflush ( stdout );
	    }
***/
	  }
          kil(s);
        }
        break;
      case MAP_gol :
        strcpy ( rul_buf, "MAP" );
        b = smap_prf ( i, g, f );
        if ( b == FALSE ) {
          b = nmap_prf ( i, g, f );
        }
        break;
      case LMAP_gol :
        strcpy ( rul_buf, "LMAP" );
        b = slmap_prf ( i, g, f );
        if ( b == FALSE ) {
          b = nlmap_prf ( i, g, f );
        }
        break;
      case CAL_gol :
        strcpy ( rul_buf, "CALL" );
        b = cal_prf ( p, i, g, f );
/***
printf ( " ZZZZZZZZZ b=%d = cal_prf ( p=%d, i=%d, g=%d, f=%d )\n", b,p,i,g,f ); fflush ( stdout );
***/
        break;
      case QUO_gol :
        strcpy ( rul_buf, "QUO" );
        b = bcatl_prf ( i, g, f );
        break;
      case NEW_gol :
        strcpy ( rul_buf, "NEWV" );
        b = bnewv_vrb_prf ( i, g, f );
        break;
      case REV_gol :
        strcpy ( rul_buf, "REV" );
        b = rev_prf ( i, g, f );
        break;
      case FLAT_gol :
        strcpy ( rul_buf, "FLAT" );
        b = flat_prf ( i, g, f );
        break;
      case HALT_gol :
        strcpy ( rul_buf, "HALT" );
        b = hlt_prf ( r, g, f );
        break;
      case INHYP_gol :
        strcpy ( rul_buf, "INHYP" );
        b = hyp_prf ( p, i, g, f );
        break;
      case CONTRA_gol :
        strcpy ( rul_buf, "CONTRA" );
        b = hyp_prf ( p, i, g, f );
        break;
      case REDO_gol :
        strcpy ( rul_buf, "REDO" );
        b = hlt_prf ( r, g, f );
        break;
      }
      if ( b ) {
        mod_spe_gol( g, op - max_rul );
      }
    }

    else {
      switch ( op - ( 2 * max_rul ) ) { /* frm_gol */
      case BCRER_sym :
        strcpy ( rul_buf, "RULE" );
        strcpy ( str_buf, "RULE" );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case BCREL_sym :
        strcpy ( rul_buf, "LEMMA" );
        strcpy ( str_buf, "LEMMA" );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case BPOP_sym :
        strcpy ( rul_buf, "RULE" );
        strcpy ( str_buf, "RULE" );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case BCLEAN_sym :
        strcpy ( rul_buf, "RULE" );
        strcpy ( str_buf, "RULE" );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case CLO_sym :
        strcpy ( rul_buf, "CLOSE" );
        b = clo_prf ( f );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case BCRELR_sym :
        strcpy ( rul_buf, "RULE" );
        strcpy ( str_buf, "RULE" );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case MODR_sym :
        strcpy ( rul_buf, "MODR" );
        b = bmodr_prf( f );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case MARK_sym :
        strcpy ( rul_buf, "MODR" );
        b = bmark_proved_prf ( f );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case SHL_sym :
        strcpy ( rul_buf, "SHELL" );
        b = bshell_prf ( f );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case WRIF_sym :
        strcpy ( rul_buf, "WRITE" );
        b = bwritef_prf ( f );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case WRIM_sym :
        strcpy ( rul_buf, "WRITE" );
        b = bwritef_prf ( f );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case PRIF_sym :
        strcpy ( rul_buf, "WRITE" );
        b = bwritef_prf ( f );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case BTAC_sym :
        strcpy ( rul_buf, "TACIC" );
        b = badd_tac_prf ( f );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case FTAC_sym :
        strcpy ( rul_buf, "TACIC" );
        b = badd_tac_prf ( f );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case BRECOMPACT_sym :
        strcpy ( rul_buf, "RECOMPACT" );
        b = recompact_prf ( f );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      case BSTATISTICS_sym :
        strcpy ( rul_buf, "STATISTICS" );
        b = stat_prf ( f );
        if ( b ) mod_is_frm_gol ( g, 1 );
        break;
      }

    }





    if ( op_breade_copy ) {
/***
printf ( " *** k = %d: op_breade_copy %d - so killing (len = %d)\n", k, op_breade_copy, len ( op_breade_copy ) ); fflush ( stdout );
***/
      kil ( op_breade_copy );
    }
/***
else printf ( " *** k = %d: op_breade_copy = 0 - nothing to do\n", k ); fflush ( stdout );
***/


    if ( b ) {  /* application successful */
/***
printf ( " >>>>>>>>>>>>>>> application successful - node %d -> ", i ); fflush ( stdout );
***/
      prev_i = i;
      i = nextp_nod ( p, i );
      k++;
/***
printf ( " node %d <<<<<<<<<<<<<<\n", i ); fflush ( stdout );
***/
    }

    /*****************************************************************
        This is ReconstructProofAndPrint - and all of this is to
            reconstruct a backtrack proof for the BTool only
    *****************************************************************/

    else {   /* application of rule did not succeed - try backtrack */
      int j = i;
      int bbb, success, kkk, ii, gg;
/***
printf ( " XXXXXXXXXXXXXX application unsuccessful - node %d\n", i ); fflush ( stdout );
***/
      kkk = k;
      success = FALSE;
      if ( p != i ) {
        bbb = test_for_backtrack ( p, j, r );
        if ( bbb == TRUE ) {
          xst_asc_nod(p,fath_nod(i),ii,gg,is_cal_gol(gg)==TRUE,bbb=TRUE,bbb=FALSE);
/***
printf ( " !!!!!!!!!!!!!! 1     bbb=%d success=%d\n", bbb, success ); fflush ( stdout );
***/
          while ( ( success == FALSE ) && ( bbb == TRUE ) ) {
/***
printf ( " !!!!!!!!!!!!!! calling backtrack_prf: 5 (p=%d j=%d r=%d)\n", p, j, r ); fflush ( stdout );
***/
            j=backtrack_prf(p,j,r);
            kkk--;
            while ( is_cal_gol(info_nod(j)) == FALSE ) {
              j=backtrack_prf(p,j,r);
              kkk--;
            }
            success = recal_prf ( j, info_nod ( j ) );
/***
printf ( " !!!!!!!!!!!!!! 2     bbb=%d success=%d\n", bbb, success ); fflush ( stdout );
***/
            if ( success == FALSE ) {
              xst_asc_nod(p,fath_nod(j),ii,gg,is_cal_gol(gg)==TRUE,bbb=TRUE,bbb=FALSE);
            }
            else {
              /* i = j; */
              b = TRUE;
              kkk++;
              k = 2;
              i = p;
              while ( k < kkk ) {
                i = nextp_nod ( p, i );
                k++;
              }
              g = info_nod ( i );
              f = frm_gol ( g );
              op = val ( prf_seq, k );
              op_sub = val ( prf_seq_sub, k );
              op_hyp = val ( prf_seq_hyp, k );
              op_breade = val ( prf_seq_breade, k );
              
/***
str_buf [ 0 ] = '\0';
write_gol_prf_no_nl ( g );
printf ( "\n---after backtrack ---\n    goal: %s\n    step %d/%d -- g=%d f=%d i=%d\n-----\n", str_buf, k - 1, ll, g, f, i ); fflush ( stdout );
printf ( "    op=%d op_sub=%d op_hyp=%d\n", op, op_sub, op_hyp ); fflush ( stdout );
***/
            }
/***
printf ( " !!!!!!!!!!!!!! 3     bbb=%d success=%d\n", bbb, success ); fflush ( stdout );
***/
          } /* while ( ( success == FALSE ) && ( bbb == TRUE ) ) */
        } /* if ( bbb == TRUE ) */
      } /* if ( p != j ) */
    } /* else - application of rule did not succeed ... */



  } /* while ( ( k <= ll ) && ( b == TRUE ) */

  auto_prf = FALSE;

  if ( ! b ) {        /* application of rule did not succeed */
    if ( ( ! autoprf_flag ) && ( ! ppf_flag ) ) CreProofTreeDialog ( 0 );
    str_buf [ 0 ] = '\0';
    write_nam_the ( the_rul ( r ) );
    sprintf ( buf, "Reconstruction of proof for %s.%d failed", str_buf, num_rul ( r ) );
    Popup_Info ( buf );
    sprintf ( buf, "\n  Can't reconstruct proof for %s.%d:\n\n    Step %d - application of:\n\n      %s", str_buf, num_rul ( r ), k - 1, rul_buf );
    DisplayCurrWinText ( buf );
    if ( op <= max_rul ) {
      str_buf [ 0 ] = '\0';
      write_ver_rul_no_indent_no_nl ( op );
      sprintf ( buf, " (%s)", str_buf );
      DisplayCurrWinText ( buf );
    }
    str_buf [ 0 ] = '\0';
    write_gol_prf_no_nl ( info_nod ( i ) );
    sprintf ( buf, "\n\n    to goal:\n\n      %s\n\n    failed\n", str_buf );
    DisplayCurrWinText ( buf );
    rem_sub_rul_the ( the_rul ( r ), num_rul ( r ) );
  }

  else if ( i ) {        /* goal left undischarged */
    if ( ( ! autoprf_flag ) && ( ! ppf_flag ) ) CreProofTreeDialog ( 0 );
    str_buf [ 0 ] = '\0';
    write_nam_the ( the_rul ( r ) );
    sprintf ( buf, "Reconstruction of proof for %s.%d failed", str_buf, num_rul ( r ) );
    Popup_Info ( buf );
    sprintf ( buf, "\n  Can't reconstruct proof for %s.%d:\n\n", str_buf, num_rul ( r ) );
    DisplayCurrWinText ( buf );
    str_buf [ 0 ] = '\0';
    write_gol_prf_no_nl ( info_nod ( i ) );
    sprintf ( buf, "    Step %d - goal:\n\n      %s\n\n    undischarged\n", k - 1, str_buf );
    DisplayCurrWinText ( buf );
    rem_sub_rul_the ( the_rul ( r ), num_rul ( r ) );
  }

  else {               /* proof ok */

    if ( autoprf_flag ) {

      success = 1;

    }

    else { /* ! autoprf_flag */

      if ( ! ppf_flag ) {

        if ( flag ) {
          CreProofTreeDialog ( 1 );
          last_node = -1;
/***
printf ( "  ))))))))))  RedrawProofTree(%d,0) motif.c ReconstructProofAndPrint\n", p );
***/
          RedrawProofTree ( p, 0 ); /* this is ReconstructProofAndPrint */
        }
        else {
          if ( val_print_ext_prf_the == TRUE ) {
            val_print_ext_prf_the = FALSE;
            reappend_trm ( name_prf_fil );
            str_buf [ 0 ] = '\0';
            write_prf ( p, 0 );
            fputs ( str_buf, bstdout );
	    reset_trm;
          }
          else {
            DisplayCurrWinText ( "\n" );
            str_buf [ 0 ] = '\0';
            write_prf ( p, 0 );
            DisplayCurrWinText ( str_buf );
	  }

        } /* else ( so, flag = 0 ) */

      }

#ifdef BTOOLKIT_FLAG

      else { /* ppf_flag */

        FILE * Bprf;
        int i, n, done;
        Bprf = fopen ( ".Bprf", "w" );
        if ( Bprf == NULL ) {
          strcpy ( primary_string, "\"" );
          strcat ( primary_string, ".Bprf" );
          strcat ( primary_string, "\" for writing" );
          AbortedMsgFile ( primary_string );
          Kill_bplatform_and_exit ( 1, 0 );
        }
        str_buf [ 0 ] = '\0';
        curr_thy = val_theo_sys;
        curr_rule = r;
        write_prf ( p, 1 );

/***
printf ( "--------------------PROOF-------------------\n" ); fflush ( stdout );
printf ( "%s\n", str_buf ); fflush ( stdout );
printf ( "--------------------PROOF-------------------\n\n\n" ); fflush ( stdout );
***/

        i = 6; /* start somewhere in "PROOF" */
        while ( ( str_buf [ i ] != '\n' ) && ( str_buf [ i ] != '\0' ) ) i++;
        if ( str_buf [ i ] == '\0' ) PrintProofError ( r, 1, i );
        i++;
        if ( str_buf [ i ] != '\n' ) PrintProofError ( r, 2, i );
        i++;
        done = 0;
        while ( ! done ) {
          fprintf ( Bprf, "(" );
          while ( str_buf [ i ] == ' ' ) {
            fprintf ( Bprf, " " );
            i++;
	  }
          while ( ( str_buf [ i ] >= '0' ) && ( str_buf [ i ] <= '9' ) ) {
            fprintf ( Bprf, "%c", str_buf [ i ] );
            i++;
	  }
          fprintf ( Bprf, "[" );
          n = 0;
          while ( str_buf [ i ] == ' ' ) {
            n++;
            i++;
          }
          fprintf ( Bprf, "%d]|(", ( n / 2 ) );
          n = n + 4;
/*
          while ( str_buf [ i ] != ' ' ) {
            fprintf ( Bprf, "%c", str_buf [ i ] );
            i++;
            n++;
	  }
*/
          while ( ( n < 50 ) && ( str_buf [ i ] != '\n' ) ) {
            fprintf ( Bprf, "%c", str_buf [ i ] );
            n++;
            i++;
            if ( str_buf [ i ] == '\n' ) {
/***
fprintf ( Bprf, "!NWL %d!", n );
***/
              fprintf ( Bprf, "\n" );
              n = 0;
              i++;
	    }
	  }
/***
fprintf ( Bprf, "!%d!", n );
***/
          fprintf ( Bprf, ")|(" );
          while ( str_buf [ i ] != '\n' ) {
            if ( str_buf [ i ] == ' ' ) {
              fprintf ( Bprf, "," );
              if ( str_buf [ i + 1 ] == '\n' ) {
                fprintf ( Bprf, "FEQL" );
              }
	    }
            else {
              fprintf ( Bprf, "%c", str_buf [ i ] );
	    }
            i++;
	  }
          fprintf ( Bprf, ")),\n" );
          while ( str_buf [ i ] != '\n' ) i++;
          if ( str_buf [ i ] == '\0' ) PrintProofError ( r, 3, i );
          i++;
          if ( str_buf [ i ] == '\n' ) {
            i++;
            if ( str_buf [ i ] == 'E' ) {
              fprintf ( Bprf, "?\n" );
              done = 1;
	    }
            else {
              PrintProofError ( r, 4, i );
	    }
	  }
	}
        fclose ( Bprf );
/***
printf ( "--------------------.Bprf-------------------\n" ); fflush ( stdout );
system ( "cat .Bprf" ); fflush ( stdout );
printf ( "--------------------.Bprf-------------------\n" ); fflush ( stdout );
***/

/***
printf ( "--------------------.Bnum-------------------\n" ); fflush ( stdout );
system ( "cat .Bnum" ); fflush ( stdout );
printf ( "\n--------------------.Bnum-------------------\n" ); fflush ( stdout );
***/
        Bprf = fopen ( ".Bnum", "r" );
        if ( Bprf == NULL ) {
          strcpy ( primary_string, "\"" );
          strcat ( primary_string, ".Bnum" );
          strcat ( primary_string, "\" for reading" );
          AbortedMsgFile ( primary_string );
          Kill_bplatform_and_exit ( 1, 0 );
        }
        n = getc ( Bprf );
        fclose ( Bprf );
        n++;
        if ( n == '5' ) n = '0';
        Bprf = fopen ( ".Bnum", "w" );
        if ( Bprf == NULL ) {
          strcpy ( primary_string, "\"" );
          strcat ( primary_string, ".Bnum" );
          strcat ( primary_string, "\" for writing" );
          AbortedMsgFile ( primary_string );
          Kill_bplatform_and_exit ( 1, 0 );
        }
        putc ( n, Bprf );
        fclose ( Bprf );
      }

/***
printf ( "--------------------.Bnum-------------------\n" ); fflush ( stdout );
system ( "cat .Bnum" ); fflush ( stdout );
printf ( "\n--------------------.Bnum-------------------\n" ); fflush ( stdout );
***/

#endif

    }

  }

  if ( flag && hyp_analysis_flag ) {
    int kk, ll;
/***
printf ( "***********************************  flag && hyp_analysis_flag\n" ); fflush ( stdout );
***/
str_buf [ 0 ] = '\0';
    kk = write_prf ( run_man_prf_p, 2 );
/***
printf ( "--------------------PROOF-------------------\n" ); fflush ( stdout );
printf ( "%s\n", str_buf ); fflush ( stdout );
printf ( "--------------------PROOF-------------------\n\n\n" ); fflush ( stdout );
***/
    ll = len ( proved_fwd_btl_rr [ kk ] );
/***
printf ( "length of proved_fwd_btl_rr [ %d ] is %d\n", kk, ll );
***/
  }

  write_res_prf;
  postlude_prf ( p );
/***
  print_live_nodes ( "In ReconstructProofAndPrint - post" );
***/

#ifdef BTOOLKIT_FLAG

  /*** restore old fwd tac ***/
  strcpy ( str_buf, additional_string );
  f = read_frm_str_buf;
  mod_fwd_tac_the ( val_theo_sys, f );

#endif

/***
  printf ( "\n  >>>>> Reconstruction of Recorded proof Complete <<<<<\n\n" );
***/

  return success;

}



#ifdef BTOOLKIT_FLAG

void
add_next_BToolLemmas ( nn, rr )
int nn, rr;
{
  int i = 1;
  while ( ( i < btl_lem_rul_MAX ) && ( btl_lem_num [ i ] != 0 ) ) { i++; }
  if ( i < btl_lem_rul_MAX ) {
    btl_lem_num [ i ] = nn;
    btl_lem_rul [ i ] = rr;
/***
printf ( "added: btl_lem_num [ %d ] = %d\n", i, nn );
printf ( "       btl_lem_rul [ %d ] = %d\n", i, rr );
***/
  }
}

void
rem_BToolLemma_from_backtrack ( nn, rr ) /* BToolLemma, curr_thy.curr_rul */
int nn;
{
  int i = 1;
  while ( ( ( btl_lem_num [ i ] != nn ) ||
            ( btl_lem_rul [ i ] != rr )    ) &&
          ( i < btl_lem_rul_MAX )               ) { i++; }
/***
printf ( "i=%d  btl_lem_num [ i ]=%d btl_lem_rul [ i ]=%d\n", i, btl_lem_num [ i ], btl_lem_rul [ i ] );
printf ( "last BToolLemmas=%d\n",  val_rul_the ( last_btl_thy_to_display,
                                   nbr_rul_the ( last_btl_thy_to_display ) ) );
***/
  if ( ( btl_lem_num [ i ] == nn ) && ( btl_lem_rul [ i ] == rr ) ) {
    rem_rul_the ( the_rul ( btl_lem_num [ i ] ), num_rul ( btl_lem_num [ i ] ) );
/***
printf ( "removed BToolLemma: %d\n", btl_lem_num [ i ] );
***/
    DisplayCurrWinText ( "\n  Removed BToolLemma\n" );
    Popup_Info ( "  Removed BToolLemma  " );
    btl_lem_num [ i ] = 0;
    btl_lem_rul [ i ] = 0;
  } 
}

int
BToolLemma_used_elsewhere ( ii, nn )
int ii, nn;
{
  int found = 0;
  int i;
/***
printf ( "BToolLemma_used_elsewhere ( ii=%d nn=%d )\n", ii, nn );
***/
  for ( i = 1 ; i < btl_lem_rul_MAX ; i++ ) {
    if ( ( btl_lem_num [ i ] == nn ) &&
         ( i != ii )                    ) {
      found = 1;
      i = btl_lem_rul_MAX + 1;
    }
  }
/***
if ( found )
  printf ( "YES: nn=%d used in ii=%d and i=%d\n", nn, ii, i );
***/
  return ( found );
}


void
check_rem_BToolLemmas ( rr ) /* rr is curr_thy.curr_rul */
int rr;
{
  int i;
/***
printf ( "check_rem_BToolLemmas ( rr=%d )\n", rr );
***/
  for ( i = 1 ; i < btl_lem_rul_MAX ; i++ ) {
    if ( ( btl_lem_num [ i ] != 0 ) &&
         ( btl_lem_rul [ i ] == rr )   ) {
      if ( ! ( BToolLemma_used_elsewhere ( i, btl_lem_num [ i ] ) ) ) {
        rem_rul_the ( the_rul ( btl_lem_num [ i ] ), num_rul ( btl_lem_num [ i ] ) );
/***
printf ( "removed BToolLemma: %d\n", btl_lem_num [ i ] );
***/
        DisplayCurrWinText ( "\n  Removed BToolLemma\n" );
        Popup_Info ( "  Removed BToolLemma  " );
      }
      btl_lem_num [ i ] = 0;
      btl_lem_rul [ i ] = 0;
    }
  }
}


int
is_in_proved_rr ( rr )
{
  int i, found;

  found = 0;
  i = 1;
  while ( ( ! found ) && ( i < max_proved_rr ) ) {
    found = ( ( proved_rr [ i ] == rr ) != 0 );
    i++;
  }
  return ( found );  
}


void
btl_autoprove ( obj )
{
  void SetFwdLibTac ();
  int st, ext, lenpob, tot, pob, i, n, j, count;
  char mchrefimp [ 25 ];

  curr_obj = obj;

  val_curMRIState( &st, obj );

  length_pob ( &lenpob, st );
  valIth_pob ( &tot, st, 1 );
  valIth_pob ( &pob, st, lenpob );
  pob = correct_pob_for_btl ( pob );
  val_ext ( &ext, obj );
  
  switch ( ext ) {
  case mch:
    sprintf ( buf, "\n  BToolProving MACHINE %s Level %d: %d/%d undischarged\n", GetShortName ( curr_obj ), lenpob - 1, pob, tot );
    break;
  case ref:
    sprintf ( buf, "\n  BToolProving REFINEMENT %s Level %d: %d/%d undischarged\n", GetShortName ( curr_obj ), lenpob - 1, pob, tot );
    break;
  case imp:
    sprintf ( buf, "\n  BToolProving IMPLEMENTATION %s Level %d: %d/%d undischarged\n", GetShortName ( curr_obj ), lenpob - 1, pob, tot );
    break;
  }
  DisplayCurrWinText ( buf );
  for ( i = first_btl_thy_to_display ; i <= last_btl_thy_to_display ; i++ ) {
    btl_fwd_tac_depth = 0;
    SetFwdLibTac ( i );
    str_buf [ 0 ] = '\0';
    write_nam_the ( i );
    sprintf ( buf, "\n    %s:\n      ", str_buf );
    DisplayCurrWinText ( buf );
    n = nbr_rul_the ( i );
    count = 0;
    for ( j = 1; j <= n ; j++ ) {
      if ( count ) {
        if ( ( ( count / 100 ) * 100 ) == count ) {
          DisplayCurrWinText ( "\n\n    " );
        }
        else if ( ( ( count / 25 ) * 25 ) == count ) {
          DisplayCurrWinText ( "\n    " );
        }
        else if ( ( ( count / 5 ) * 5 ) == count ) {
          DisplayCurrWinText ( " " );
        }
      }
/***
printf ( ">>> autoprove seeking val_rul_the ( %d, %d ): %d\n", i, j, val_rul_the ( i, j ) );
***/
      if ( pvd_rul ( val_rul_the ( i, j ) ) == now_rul ) {
        DisplayCurrWinText ( "p" );
      }
      else if ( is_in_proved_rr ( val_rul_the ( i, j ) ) ) {
        if ( ReconstructProofAndPrint ( val_rul_the ( i, j ), 1, 0, 1, 0 ) ) {
          mod_pvd_rul( val_rul_the ( i, j ), now_rul );
          DisplayCurrWinText ( "+" );
	}
        else {
          DisplayCurrWinText ( "\n      -" );
	}
      }
      else {
        DisplayCurrWinText ( "." );
      }
      XmUpdateDisplay ( top_level );
      count++;
    }
  }
  DisplayCurrWinText ( "\n" );
  curr_obj = obj;
  exit___contd ( 1, 1 );
  XmUpdateDisplay ( top_level );
}

void
btl_proofprint ( thy_name, num )
char * thy_name;
int num;
{
  int i, t;
  void SetFwdLibTac ();
/***
printf ( " --- btl_proofprint ( %s %d )\n", thy_name, num );
***/
  t = 0;
  for ( i = first_btl_thy_to_display ; i <= last_btl_thy_to_display ; i++ ) {
    btl_fwd_tac_depth = 0;
    SetFwdLibTac ( i );
    if ( ! t ) {
      str_buf [ 0 ] = '\0';
      write_nam_the ( i );
      if ( strcmp ( thy_name, str_buf ) == 0 ) t = i;
    }
  }
/***
str_buf [ 0 ] = '\0';
write_nam_the ( t );
sprintf ( buf, "btl_proofprint: %s.%d", str_buf, num );
Popup_Info ( buf );
***/
  ReconstructProofAndPrint ( val_rul_the ( t, num ), 1, 0, 0, 1 );
  ini;
  for ( i = 1; i < max_proved_rr ; i ++ ) {
    proved_rr [ i ] = 0;
    proved_seq_rr [ i ] = 0;
    proved_seq_sub_rr [ i ] = 0;
    proved_fwd_btl_rr [ i ] = 0;
  }
}


#endif


int app_rules [ 250 ];
int app_tot;

/* app_tot = no of applicable rules */
/* stored in app_tot as max_rul+rr */

/* theory 0 => builtin */
#define app_and            1
#define app_cal            2
#define app_eql            3
#define app_hlt            4
#define app_hyp            5
#define app_clo            6
#define app_stat           7
#define app_susp           8
#define app_recompact      9
#define app_ded           10
#define app_gen           11
#define app_mon_hyp       12
#define app_sub           13
#define app_mon2_hyp      14
#define app_ari           15
#define app_rev           16
#define app_flat          17
#define app_smap          18
#define app_nmap          19
#define app_bmodr         20
#define app_bmark_proved  21
#define app_bshell        22
#define app_bwritef       23
#define app_badd_rul      24
#define app_badd_lirul    25
#define app_bpopt         26
#define app_bcleant       27
#define app_badd_tac      28
#define app_bcatl         29
#define app_bnewv_vrb     30
#define app_low           31
#define app_slmap         32
#define app_nlmap         33

char *Builtin_TAC[] = {
  "", 
  "AND",
  "CALL",
  "EQL",
  "HALT",
  "INHYP",
  "CLOSE",
  "STATISTICS",
  "SUSPEND",
  "RECOMPACT",
  "DED",
  "GEN",
  "HYP",
  "SUB",
  "HYP",
  "ARI",
  "REV",
  "FLAT",
  "MAP",
  "MAP",
  "MODR",
  "MODR",
  "SHELL",
  "WRITE",
  "RULE",
  "RULE",
  "RULE",
  "RULE",
  "TACTIC",
  "CATL",
  "NEWV",
  "NEWV",
  "LMAP",
  "LMAP"
    };

/***************************************************************************/

app_info ()
{
  char info_buf [ 1000 ];
  sprintf ( info_buf, "gol %d(%d) nod %d(%d) seq %d(%d)\n", gol-gttm, gttm, nod-nttm, nttm, vnbs-ttms, ttms );
  DisplayCurrWinText ( info_buf );
}

/***************************************************************************/


app_write_rul_ful(r)
{
  register int f, n;
  n=num_rul(r);
  reset_res(0);
  str_buf [ 0 ] = '\0';
  if( sts_rul(r)==off_rul ){
    write_chr_res(ord('-'));
  } else if( pvd_rul(r)==now_rul ){
    write_blk_res(1);
  } else {
    write_chr_res(ord('*'));
  };
  switch( typ_rul(r) ){
    case nrm_rul :{
      write_chr_res(ord('N'));
    ;break;}case rul_rul :{
      write_chr_res(ord(' '));
    ;break;}case lem_rul :{
      write_chr_res(ord('L'))
    ;break;};
  };
  write_blk_res(1);
  if( is_inverted_rul(r)==TRUE ){
    write_srv_res;
  };
  write_num_res(num_rul(r));
  if( is_inverted_rul(r)==TRUE ){
    write_erv_res;
  };
  if( n<10 ){
    write_blk_res(1);
  };
  write_blk_res(1);
/*
  f=cre_rec_rul(r);
  write_frm_res(f,12);
  kil(f);
*/
  strcat ( str_buf, "\n" );
  write_ver_rul_dave(r);
}


app_write_rul(r)
{
/*
  register int f ;
  reset_res(0);
  f=cre_rec_rul(r);
  write_frm_res(f,12);
  kil(f);
*/
  save_MAX_COL_RES;
  mod_MAX_COL_RES(999999);
  write_ver_rul_dave ( r );
  restore_MAX_COL_RES;
}


/***************************************************************************/


app_test3_unv_eql_hyp_prf(p,n,hf,sgf,f,i,lv)
{
  register int gf,ln,rf,rq,rp,ff,sf,sq,gg,gl,ef,test3_unv_eql_hyp_prf_res,lvv,b ;
/***
print_hyp_len ( "app_test3_unv_eql_hyp_prf 1", run_man_prf_i );
***/
/***
printf ( "app_test3_unv_eql_hyp_prf(%d,%d,%d,%d,%d,%d,%d)\n", p,n,hf,sgf,f,i,lv);
***/
  gf=right_frm(sgf);
  ln=left_node_frm(gf);
  ef=cre_encode_tree(f,i);
  lvv = cre(5);
  get_asc_nod_vrb_frm(lvv,f,i);
  if( len(lvv)!=0 ){
    test3_unv_eql_hyp_prf_res=FALSE;
  }
  else if( is_qtf_frm(lvv,f,i)==TRUE ){ 
/*  added Fri Jun 12 1992  */
    test3_unv_eql_hyp_prf_res=FALSE;
  }
  else if( chk_set_tree(gf,ln,beg_tree(gf,ln),ef,root_tree(ef),1,lv)==TRUE ){
    if( ari_sym(val_tree(f,i))==0 ){
      b=father_is_idx_vrb_frm(f,i) 
/*  to avoid left of aaa$1 to match with aaa  */;
    } else {
      b=FALSE;
    }
    if( b==TRUE ){
      test3_unv_eql_hyp_prf_res=FALSE;
    }
    else {

      rf=right_frm(gf);
      rq=prd_tree(rf);
      rp=cre_decode_tree(rq,root_tree(rq));
      kil(rf);
      kil(rq);
      ff=cre_mod_tree(f,i,rp);
      kil(rp);
      if( already_frm_prf(p,n,ff)==TRUE ){
        kil(ff);
        test3_unv_eql_hyp_prf_res=FALSE;
      }
      else {
        sf=left_frm(sgf);
        sq=prd_tree(sf);
        gg=cre_decode_tree(sq,root_tree(sq));
        kil(sf);
        kil(sq);
        if( already_frm_prf(p,n,gg)==TRUE ){
          kil(ff);
          kil(gg);
          test3_unv_eql_hyp_prf_res=FALSE;
	}
        else {  /* ask_eql_hyp_prf(f,i,hf)==TRUE */
          kil(ff);
          kil(gg);
          test3_unv_eql_hyp_prf_res=TRUE;
/***
printf ( "test3_unv_eql_hyp_prf_res=TRUE\n" );
***/
	}
      }
    }
  } /*  else if( chk_set_tree(gf,ln,beg_tre ... */
  else {
    test3_unv_eql_hyp_prf_res=FALSE;
  }
  kil(lvv);
  kil(gf);
  kil(ef);
  clr_chk_frm;
/***
print_hyp_len ( "app_test3_unv_eql_hyp_prf 2", run_man_prf_i );
***/
  return test3_unv_eql_hyp_prf_res;
}

app_test2_unv_eql_hyp_prf(p,n,hhf,hf,f,i,lv)
{
  register int rf,rp,ff,gl,gf,rq,ln,ef,test2_unv_eql_hyp_prf_res,lvv,b ;
  gf=cre_encode_tree(hf,root_tree(hf));
  ln=left_node_frm(gf);
  ef=cre_encode_tree(f,i);
  lvv = cre(5);
  get_asc_nod_vrb_frm(lvv,f,i);
  if( len(lvv)!=0 ){
    test2_unv_eql_hyp_prf_res=FALSE;
  } else if( chk_set_tree(gf,ln,beg_tree(gf,ln),ef,root_tree(ef),1,lv)==TRUE ){
    if( ari_sym(val_tree(f,i))==0 ){
      b=father_is_idx_vrb_frm(f,i) 
/*  to avoid left of aaa$1 to match with aaa  */;
    } else {
      b=FALSE;
    }
    if( b==TRUE ){
      test2_unv_eql_hyp_prf_res=FALSE;
    } else {
      rf=right_frm(gf);
      rq=prd_tree(rf);
      rp=cre_decode_tree(rq,root_tree(rq));
      kil(rf);
      kil(rq);
      ff=cre_mod_tree(f,i,rp);
      kil(rp);
/*
      if( ask_eql_hyp_prf(f,i,hhf)==FALSE ){
        kil(ff);
        test2_unv_eql_hyp_prf_res=FALSE;
      } else if( already_frm_prf(p,n,ff)==TRUE ){
        kil(ff);
        test2_unv_eql_hyp_prf_res=FALSE;
      } else {
        gl=cre_gol(ff);
        cre_nod(gl,n);
        test2_unv_eql_hyp_prf_res=TRUE;
      }
*/
/***
printf ( "*** 2: test2_unv_eql_hyp_prf_res=TRUE\n" );
***/
      test2_unv_eql_hyp_prf_res=TRUE;

    }
  } else {
    test2_unv_eql_hyp_prf_res=FALSE;
  }
  kil(lvv);
  kil(gf);
  kil(ef);
  clr_chk_frm;
  return test2_unv_eql_hyp_prf_res;
}

app_test_imp_hyp_prf(p,n,hf,f)
{
  register int ff,gl,s,i,v,b,rn,op,lrn,rrn,op2,test_imp_hyp_prf_res ;
  if( eql_tree(hf,right_node_frm(hf),f,root_tree(f))==TRUE ){
    ff=left_frm(hf);
    if( val_root_frm(ff)==AND_sym ){
      s=dec_frm(ff,AND_sym);
      xst(s,i,v,already_frm_prf(p,n,v)==TRUE,b=FALSE,b=TRUE);

/*
      if( b==TRUE ){
        b=ask_hyp_prf(hf);
      }
      if( b==TRUE ){
        itr(s,i,v,gl=cre_gol(v);cre_nod(gl,n));
        test_imp_hyp_prf_res=TRUE;
      } else {
        test_imp_hyp_prf_res=FALSE;
        itr(s,i,v,kil(v));
      }
*/
      itr(s,i,v,kil(v));
      test_imp_hyp_prf_res=b;
/***
if ( b ) printf ( "*** 3: test_imp_hyp_prf_res=TRUE\n" );
***/

      kil(s);
      kil(ff);
    } else {
/*
       if( ask_hyp_prf(hf)==FALSE ){
        test_imp_hyp_prf_res=FALSE;
        kil(ff);
      } else if( already_frm_prf(p,n,ff)==TRUE ){
        test_imp_hyp_prf_res=FALSE;
        kil(ff);
      } else {
        test_imp_hyp_prf_res=TRUE;
        gl=cre_gol(ff);
        cre_nod(gl,n);
      }
*/
      kil(ff);
      test_imp_hyp_prf_res=TRUE;
/***
printf ( "*** 4: test_imp_hyp_prf_res=TRUE\n" );
***/

    }      ;
  } else {                    /* if( eql_tree(hf,..)==TRUE ) */
    rn=right_node_frm(hf);
    op=val_tree(hf,rn);
    if( (op==EQL_sym) || (op==EQV_sym) ){
    lrn=left_node_tree(hf,rn);
      rrn=right_node_tree(hf,rn);
      op2=val_tree(hf,lrn);
      if( is_in_frm(f,op2)==TRUE ){
          nxst_sub_frm(f,i,v,app_test3_eql_hyp_prf(p,n,hf,lrn,rrn,f,i)==TRUE,
                            test_imp_hyp_prf_res=TRUE,
                            test_imp_hyp_prf_res=FALSE);
      } else {
        test_imp_hyp_prf_res=FALSE;
      }
    } else { 
      test_imp_hyp_prf_res=FALSE;
    }
  }
  return test_imp_hyp_prf_res;
}

app_test3_eql_hyp_prf(p,n,hf,lnod,rnod,f,i)
{
  register int rp,ff,gl,gg,s,j,v,b,test3_eql_hyp_prf_res,lv ;
  if( eql_tree(hf,lnod,f,i)==TRUE ){
    if( ari_sym(val_tree(f,i))==0 ){
      b=father_is_idx_vrb_frm(f,i) 
/*  to avoid left of aaa$1 to match with aaa  */;
    } else {
      b=FALSE;
    }
    if( b==TRUE ){
      test3_eql_hyp_prf_res=FALSE;
    } else {
      rp=cre_cop_tree(hf,rnod);
      ff=cre_mod_tree(f,i,rp);
      kil(rp);
      lv=cre(5);
      get_asc_nod_vrb_frm(lv,f,i);
      if( rec_fre_prf(p,n,lv,hf,root_tree(hf)) ==TRUE ){
        kil(ff);
        test3_eql_hyp_prf_res=FALSE;
      } else if( already_frm_prf(p,n,ff)==TRUE ){
        kil(ff);
        test3_eql_hyp_prf_res=FALSE;
      } else {
        gg=left_frm(hf);
        if( val_root_frm(gg)==AND_sym ){
          s=dec_frm(gg,AND_sym);
          xst(s,j,v,already_frm_prf(p,n,v)==TRUE,b=FALSE,b=TRUE);
/*
          if( b==TRUE ){
            b=ask_eql_hyp_prf(f,i,hf);
          }
          if( b==TRUE ){
            itr(s,j,v,gl=cre_gol(v);cre_nod(gl,n));
            gl=cre_gol(ff);
            cre_nod(gl,n);
            test3_eql_hyp_prf_res=TRUE;
          } else {
            itr(s,j,v,kil(v));
            kil(ff);
            test3_eql_hyp_prf_res=FALSE;
          }
*/
          itr(s,j,v,kil(v));  
          kil(ff);
          test3_eql_hyp_prf_res=b;
/***
if ( b ) printf ( "*** 4: test3_eql_hyp_prf_res=TRUE\n" );
***/

          kil(s);
          kil(gg);
        } else {
          if( already_frm_prf(p,n,gg)==TRUE ){
            test3_eql_hyp_prf_res=FALSE;
            kil(ff);
            kil(gg);
/*
          } else if( ask_eql_hyp_prf(f,i,hf)==FALSE ){
            test3_eql_hyp_prf_res=FALSE;
            kil(ff);
            kil(gg);
          } else {
            test3_eql_hyp_prf_res=TRUE;
            gl=cre_gol(gg);
            cre_nod(gl,n);
            gl=cre_gol(ff);
            cre_nod(gl,n);
          }
*/
          } else {
            kil(ff);
            kil(gg);
            test3_eql_hyp_prf_res=TRUE;
/***
printf ( "*** 5: test3_eql_hyp_prf_res=TRUE\n" );
***/
          }
        }
      }
      kil(lv);
    }
  } else {
    test3_eql_hyp_prf_res=FALSE;
  }
  return test3_eql_hyp_prf_res;
}

app_test2_eql_hyp_prf(p,n,hf,lnod,f,i)
{
  register int rp,ff,gl,test2_eql_hyp_prf_res,lv,b ;
  if( eql_tree(hf,lnod,f,i)==TRUE ){
    if( ari_sym(val_tree(f,i))==0 ){
      b=father_is_idx_vrb_frm(f,i) 
/*  to avoid left of aaa$1 to match with aaa  */;
    } else {
      b=FALSE;
    }
    if( b==TRUE ){
      test2_eql_hyp_prf_res=FALSE;
    } else {
      rp=right_frm(hf);
      ff=cre_mod_tree(f,i,rp);
      kil(rp);
      lv=cre(5);
      get_asc_nod_vrb_frm(lv,f,i);
      if( rec_fre_prf(p,n,lv,hf,root_tree(hf)) ==TRUE ){
        kil(ff);
        test2_eql_hyp_prf_res=FALSE;
/*
      } else if( ask_eql_hyp_prf(f,i,hf)==FALSE ){
        kil(ff);
        test2_eql_hyp_prf_res=FALSE;
      } else if( already_frm_prf(p,n,ff)==TRUE ){
        kil(ff);
        test2_eql_hyp_prf_res=FALSE;
      } else {
        gl=cre_gol(ff);
        cre_nod(gl,n);
        test2_eql_hyp_prf_res=TRUE;
      }
*/
      } else {
        kil(ff);
        test2_eql_hyp_prf_res=TRUE;
/***
printf ( "*** 6: test2_eql_hyp_prf_res=TRUE\n" );
***/
      }
      kil(lv);
    }
  } else {
    test2_eql_hyp_prf_res=FALSE;
  }
  return test2_eql_hyp_prf_res;
}

app_test_eql_hyp_prf(p,n,hf,f)
{
  register int i,v,op,lnod,test_eql_hyp_prf_res ;
  lnod=left_node_frm(hf);
  op=val_tree(hf,lnod);
  if( is_in_frm(f,op)==TRUE ){
      nxst_sub_frm(f,i,v,app_test2_eql_hyp_prf(p,n,hf,lnod,f,i)==TRUE,
                        test_eql_hyp_prf_res=TRUE,
                        test_eql_hyp_prf_res=FALSE);
  } else {
    test_eql_hyp_prf_res=FALSE;
  }
  return test_eql_hyp_prf_res;
}

app_test_hyp_prf(p,n,hf,frm)
{
  register int op,lv,rhf,lhf,ff,gl,s,i,v,lnod,gf,fq,rn,lrn,op2,ef,test_hyp_prf_res ;
  op=val_root_frm(hf);
  if( (op==EQL_sym) || (op==EQV_sym) ){
    test_hyp_prf_res=app_test_eql_hyp_prf(p,n,hf,frm);
  } else if( op==IMP_sym ){
    test_hyp_prf_res=app_test_imp_hyp_prf(p,n,hf,frm);
  } else {
    lv=cre(4);
    if( is_unv_frm_prf(p,n,lv,hf,root_tree(hf))==TRUE ){
      clr_chk_frm;
      rhf=right_frm(hf);
      if( val_root_frm(rhf)==IMP_sym ){
        gf=cre_encode_tree(rhf,root_tree(rhf));
        rn=right_node_frm(gf);
        ef=cre_encode_tree(frm,root_tree(frm));
        if( chk_set_tree(gf,rn,beg_tree(gf,rn),
        ef,root_tree(ef),1,lv)==TRUE ){
/*
          if( ask_hyp_prf(hf)==FALSE ){
            test_hyp_prf_res=FALSE;
          } else {
            lhf=left_frm(gf);
            fq=prd_tree(lhf);
            ff=cre_decode_tree(fq,root_tree(fq));
            kil(lhf);
            kil(fq);
            if( val_root_frm(ff)==AND_sym ){
              s=dec_frm(ff,AND_sym);
              itr(s,i,v,gl=cre_gol(v);cre_nod(gl,n));
              kil(s);
              kil(ff);
            } else {
              gl=cre_gol(ff);
              cre_nod(gl,n);
            }
            test_hyp_prf_res=TRUE;
          }
*/
          test_hyp_prf_res=TRUE;
/***
printf ( "*** 7: test_hyp_prf_res=TRUE\n" );
***/

        } else {
          rn=right_node_frm(gf);
          op=val_tree(gf,rn);
          if( (op==EQL_sym) || (op==EQV_sym) ){
            lrn=left_node_tree(gf,rn);
            op2=val_tree(gf,lrn);
/***
print_hyp_len ( "app_test_hyp_prf 1", run_man_prf_i );
***/
            nxst_sub_frm(frm,i,v,
                        app_test3_unv_eql_hyp_prf(p,n,hf,gf,frm,i,lv)==TRUE,
                        test_hyp_prf_res=TRUE,
                        test_hyp_prf_res=FALSE)
              
/***
print_hyp_len ( "app_test_hyp_prf 2", run_man_prf_i );
***/

          } else {
            test_hyp_prf_res=FALSE;
          }
        }
        kil(gf);
        kil(ef);
      } else if( (val_root_frm(rhf)==EQL_sym) || (val_root_frm(rhf)==EQV_sym) ){
        lnod=left_node_frm(rhf);
        op=val_tree(rhf,lnod);
        nxst_sub_frm(frm,i,v,
                    app_test2_unv_eql_hyp_prf(p,n,hf,rhf,frm,i,lv)==TRUE,
                    test_hyp_prf_res=TRUE,
                    test_hyp_prf_res=FALSE)
      } else {
        if( chk_set_frm(rhf,frm,lv)==TRUE ){
/*
          if( ask_hyp_prf(hf)==FALSE ){
            test_hyp_prf_res=FALSE;
          } else {
            test_hyp_prf_res=TRUE;
          }
*/
          test_hyp_prf_res=TRUE;
/***
printf ( "*** 8: test_hyp_prf_res=TRUE\n" );
***/

        } else {
          test_hyp_prf_res=FALSE;
        }
      }
      kil(rhf);
    } else {
      test_hyp_prf_res=FALSE;
    }
    kil(lv);
  }
/***
print_hyp_len ( "app_test_hyp_prf 4", run_man_prf_i );
***/
  return test_hyp_prf_res;
}

/***************************************************************************/

app_test2_eql_rul_prf(rr,p,n,la,f,i,c,lnod,li)
{
  register int rp,s,ff,j,a,test2_eql_rul_prf_res   ,b,lv   ;
/***
printf ( "app_test2_eql_rul_prf\n" );
***/
  if( chk_tree(c,lnod,beg_tree(c,lnod),f,i,beg_tree(f,i))==TRUE ){
    if( ari_sym(val_tree(f,i))==0 ){
      b=father_is_idx_vrb_frm(f,i) 
/*  to avoid left of aaa$1 to match with aaa  */;
    } else {
      b=FALSE;
    }
    if( b==TRUE ){
      test2_eql_rul_prf_res=FALSE;
    } else if( len(la)!=0 ){
      nxst(la,j,a,guard_prf(p,n,a,li, /* app_rule_flag = */ 0, /* prf_seq_breade = */ 0 )==FALSE,
                    b=FALSE,
                    b=TRUE)
      if( b==TRUE ){
        lv=cre(5);
        get_asc_nod_vrb_frm(lv,f,i);
        if( len(lv)!=0 ){
          nxst(li,j,a,is_fre_in_ant_prf(p,n,lv,a)==TRUE,        
/* rec_fre_prf(p,n,lv,a,root_tree(a)) */
            clean_prf(li);
            test2_eql_rul_prf_res=FALSE,
            rp=right_frm(c);
            s=prd_tree(rp);
            ff=cre_mod_tree(f,i,s);
            psh(li,ff);
/*
            test2_eql_rul_prf_res=app_test3_eql_rul_prf(f,i,rr,li,p,n);
*/
            test2_eql_rul_prf_res=TRUE;
            clean_prf(li);
            kil(rp);
            kil(s)
            );
        } else {
          rp=right_frm(c);
          s=prd_tree(rp);
          ff=cre_mod_tree(f,i,s);
          psh(li,ff);
/*
          test2_eql_rul_prf_res=app_test3_eql_rul_prf(f,i,rr,li,p,n);
*/
          test2_eql_rul_prf_res=TRUE;
          clean_prf(li);
          kil(rp);
          kil(s);
        }
        kil(lv);
      } else {
        clean_prf(li);
        test2_eql_rul_prf_res=FALSE;
      }
    } else {
      rp=right_frm(c);
      s=prd_tree(rp);
      ff=cre_mod_tree(f,i,s);
      psh(li,ff);
/*
      test2_eql_rul_prf_res=app_test3_eql_rul_prf(f,i,rr,li,p,n);
*/
      test2_eql_rul_prf_res=TRUE;
      clean_prf(li);
      kil(rp);
      kil(s);
    }
  } else {
    test2_eql_rul_prf_res=FALSE;
  }
  clr_chk_frm;
  clean_prf(li);
  return test2_eql_rul_prf_res;
}

app_test_eql_rul_prf(p,n,r,f)
{
  register int c,lnod,op,li,la,i,v,test_eql_rul_prf_res ;
  c=cns_rul(r);
  lnod=left_node_frm(c);
  op=val_tree(c,lnod);
  if( (is_in_frm(f,op)==TRUE) || (letter_sym(op)==TRUE) || (op==JK2_sym) || (op==JK1_sym) ){
    la=ant_rul(r);
    li=cre(len(la));
    nxst_sub_frm(f,i,v,app_test2_eql_rul_prf(r,p,n,la,f,i,c,lnod,li)==TRUE,
                         test_eql_rul_prf_res=TRUE,
                         test_eql_rul_prf_res=FALSE);
    kil(li);
  } else {
    test_eql_rul_prf_res=FALSE;
  }
  return test_eql_rul_prf_res;
}

app_test_nrm_rul_prf(p,n,rr)
{
  register int la,li,j,a,b,i,pa ;
/***
printf ( "app_test_nrm_eql_rul_prf\n" );
***/
  la=ant_rul(rr);
  li=cre(len(la));
  nxst(la,j,a,guard_prf(p,n,a,li, /* app_rule_flag = */ 1, /* prf_seq_breade = */ 0 )==FALSE,
                b=FALSE,
                b=TRUE
               );
  itr(li,i,pa,kil(pa));
  kil(li);
  return b;
}

app_test_rul_prf(p,n,r,rr,frm)
{
  register int c,op,test_rul_prf_res ;
  auto_prf = TRUE;
  if( (r!=rr) && (val_sts_rul(rr)==on_rul) ){
    c=cns_rul(rr);
    op=val_root_frm(c);
    clr_chk_frm;
    if( op==MAC_sym ){   /* rewrite rule */
      test_rul_prf_res=app_test_eql_rul_prf(p,n,rr,frm);
    } else if( chk_frm(c,frm)==TRUE ){
      test_rul_prf_res=app_test_nrm_rul_prf(p,n,rr);
    } else {
      test_rul_prf_res=FALSE;
    }
    kil_content_input_prf;
  } else {
    test_rul_prf_res=FALSE;
  }
/*
#ifdef BTOOLKIT_FLAG
*/
  if ( test_rul_prf_res == TRUE ) {
    int ll;
    str_buf [ 0 ] = '\0';
    write_nam_the ( the_rul ( rr ) );
    ll = strlen ( str_buf );
    if ( ll > 3 ) {
      if ( ( str_buf [ 0 ] == 'F' ) &&
           ( str_buf [ 1 ] == 'w' ) &&
           ( str_buf [ 2 ] == 'd' )    ) {
        test_rul_prf_res = FALSE;
      }
/*
      else if ( strcmp ( str_buf, "SwitchX" ) == 0 ) {
        test_rul_prf_res = FALSE;
      }
      else if ( strcmp ( str_buf, "DupSwitchX" ) == 0 ) {
        test_rul_prf_res = FALSE;
      }
*/
    }
  }
/*
#endif
*/
  auto_prf = FALSE;
  return test_rul_prf_res;
}


/***************************************************************************/


app_and_prf(i,g,f)
{
  if( val_root_frm(f)!=AND_sym ) return FALSE;
  return TRUE;
}

app_call_prf(p,n,g,f) /* n == i */
{
  register int ss,j,v,b,cal_prf_res;
  if( val_root_frm(f)!=CAL_sym ) return FALSE;
  ss=dec_tree(f,right_node_frm(f),BAR_sym);
  xst(ss,j,v,val_root_frm(v)!=COL_sym,b=FALSE,b=TRUE);     
  if   ( (b==TRUE) && (val_alt_gol(g)==0) ) cal_prf_res = TRUE;
  else                                      cal_prf_res = FALSE;
  itr(ss,j,v,kil(v));
  kil(ss);
  return cal_prf_res;
}

app_eql_prf(g,f)
{
  if( val_root_frm(f)!=EQL_sym ) return FALSE;
  if( eql_tree(f,left_node_frm(f),f,right_node_frm(f))==FALSE ) return FALSE;
  return TRUE;
}

app_redo_prf(r,g,f)
{
  if (val_root_frm(f)!=REDO_sym) return FALSE;
  return TRUE;
}

app_hlt_prf(r,g,f)
{
  if (val_root_frm(f)!=HALT_sym) return FALSE;
  return TRUE;
}

app_hyp_prf(p,n,g,f) /* n == i */
{
  register int s,i,h,hyp_prf_res;
  s=cre(20);
  lst_hyp_prf(p,n,s);
  xst(s,i,h,(eql_frm(f,frm_hyp(h))==TRUE) || (val_root_frm(frm_hyp(h))==FAL_sym),
        hyp_prf_res=TRUE,
        hyp_prf_res=FALSE);
  kil(s);
  return hyp_prf_res;
}

app_clo_prf(f)
{
  if( val_root_frm(f)!=CLO_sym ) return FALSE;
  return TRUE;
}

app_stat_prf(f)
{
  if( val_root_frm(f)!=BSTATISTICS_sym ) return FALSE;
  return TRUE;
}

app_susp_prf(f)
{
  if( val_root_frm(f)!=BSUSPEND_sym ) return FALSE;
  return TRUE;
}

app_recompact_prf(f)
{
  if( val_root_frm(f)!=BRECOMPACT_sym ) return FALSE;
  return TRUE;
}

app_ded_prf(r,p,n,g,f) /* n == i */
{
  if( val_root_frm(f)!=IMP_sym ) return FALSE;
  return TRUE;
}

app_gen_prf(p,n,g,f) /* n == i */
{
  register int lv,gen_prf_res;
  lv=cre(4);
  if   ( is_unv_frm_prf(p,n,lv,f,root_tree(f))==TRUE ) gen_prf_res=TRUE;
  else                                                 gen_prf_res=FALSE;
  kil(lv);
  return gen_prf_res;
}

/* hyp implication and equality */
app_mon2_hyp_prf(p,n,g,f) /* n == i */ /* hyp implication and equality */
{
  register int s,i,h,mon2_hyp_prf_res ;
  s=cre(50);
  lst_hyp_prf(p,n,s);
  xst(s,i,h,app_test_hyp_prf(p,n,frm_hyp(h),f)==TRUE,
              mon2_hyp_prf_res=TRUE,
              mon2_hyp_prf_res=FALSE);
  kil(s);
  return mon2_hyp_prf_res;
}

app_sub_prf(p,i,g,f) /* n == i */
{
  register int n,v,lv,le,fff,ff,gl,j,sub_prf_res ;
  lv=cre(4);
  le=cre(4);
  nxst_sub_frm(f,n,v,is_dis_sub_frm_prf(p,i,lv,le,f,n)==TRUE,
                 fff=cre(4);
                 rec_sub_prf(p,i,lv,le,f,right_node_tree(f,n),fff,TRUE);
                 if( eql_tree(f,n,fff,root_tree(fff))==FALSE ) {
                   kil(fff);
                   sub_prf_res=TRUE;
		 } else {
                   kil(fff);
                   sub_prf_res=FALSE;
                 },
                 sub_prf_res=FALSE
               );
  kil(lv);
  itr(le,j,v,kil(v));
  kil(le);
  return sub_prf_res;
}

app_mon_hyp_prf(p,n,g,f) /* n == i */
{
  register int s,i,h,mon_hyp_prf_res;
/***
print_hyp_len ( "app_mon_hyp_prf 1", run_man_prf_i );
***/
  s=cre(50);
  lst_hyp_prf(p,n,s);
  nxst(s,i,h,app_test_hyp_prf(p,n,frm_hyp(h),f)==TRUE,
               mon_hyp_prf_res=TRUE,
               mon_hyp_prf_res=FALSE);
/***
print_hyp_len ( "app_mon_hyp_prf 2", run_man_prf_i );
***/
  kil(s);
  return mon_hyp_prf_res;
}

app_ari_prf(i,g,f)
{
  register int n,v,s,ff,gl,w,ari_prf_res ;
  xst_sub_frm(f,n,v,is_arith_frm(f,n)==TRUE,ari_prf_res=TRUE,
                                            ari_prf_res=FALSE);
  return ari_prf_res;
}

app_rev_prf(n,g,f) /* n == i */
{
  register int v,i,rev_prf_res ;
  nxst_sub_frm(f,i,v,v==REV_sym,rev_prf_res=TRUE,
                                rev_prf_res=FALSE);
  return rev_prf_res;
}

app_flat_prf(n,g,f) /* n == i */
{
  register int v,i,flat_prf_res ;
  nxst_sub_frm(f,i,v,v==FLAT_sym,flat_prf_res=TRUE,
                                 flat_prf_res=FALSE);
  return flat_prf_res;
}

app_smap_prf(n,g,f) /* n == i */
{
  if ( val_root_frm(f)!=SMAP_sym ) return FALSE;
  return TRUE;
}

app_nmap_prf(n,g,f) /* n == i */
{
  if ( val_root_frm(f)!=NMAP_sym ) return FALSE;
  return TRUE;
}

app_bmodr_prf(f)
{
  register int bmodr_res,r,lr,llrn,thn,t,b,rlrn,rc,n,rr ;
  bmodr_res=FALSE;
  if( val_root_frm(f)==MODR_sym ){
    r=right_frm(f);
    if( val_root_frm(r)==COM_sym ){
      lr=left_frm(r);
      if( val_root_frm(lr)==DOT_sym ){
        llrn=left_node_frm(lr);
        thn=val_tree(lr,llrn);
        if( ari_sym(thn)==0 ){
          xst_the(t,nam_the(t)==thn,b=TRUE,b=FALSE);
          if( b==TRUE ){
            rlrn=right_node_frm(lr);
            rc=val_tree(lr,rlrn);
            if( ari_sym(rc)==0 ){
              if( is_nbr_sym(rc)==TRUE ){
                n=arith_val_sym(rc);
                if( (n>0) && (n<=nbr_rul_the(t)) ){
                  bmodr_res=TRUE;
                }
              }
            }
          }
        }
      }
      kil(lr);
    }
    kil(r);
  }
  return bmodr_res;
}

app_bmark_proved_prf(f)
{
  register int bmark_proved_res,lr,llrn,thn,t,b,rlrn,rc,n,rr ;
  bmark_proved_res=FALSE;
  if( val_root_frm(f)==MARK_sym ){
    lr=right_frm(f);
    if( val_root_frm(lr)==DOT_sym ){
      llrn=left_node_frm(lr);
      thn=val_tree(lr,llrn);
      if( ari_sym(thn)==0 ){
        xst_the(t,nam_the(t)==thn,b=TRUE,b=FALSE);
        if( b==TRUE ){
          rlrn=right_node_frm(lr);
          rc=val_tree(lr,rlrn);
          if( ari_sym(rc)==0 ){
            if( is_nbr_sym(rc)==TRUE ){
              n=arith_val_sym(rc);
              if( (n>0) && (n<=nbr_rul_the(t)) ){
                bmark_proved_res=TRUE;
              }
            }
          }
        }
      }
    }
    kil(lr);
  }
  return bmark_proved_res;
}

app_bshell_prf(f)
{
  register int v,s,bshell_prf_res ;
  bshell_prf_res=FALSE;
  if( val_root_frm(f)==SHL_sym ){
    v=val_tree(f,right_node_frm(f));
    if( ari_sym(v)==0  ){
      if( nrml_stri_sym(v)==TRUE ){
        s=stri_sym(v);
        if( (fst_str(s)==SMPQUO_sym) && (lst_str(s)==SMPQUO_sym) ){
          bshell_prf_res=TRUE;
        }
      }
    }
  }
  return bshell_prf_res;
}

app_bwritef_prf(f)
{
  register int op,ff,i,fff,bwrite_prf_res,ss,vv ;
  op=val_root_frm(f);
  if( (op==WRIF_sym) || (op==PRIF_sym) || (op==WRIM_sym) ){
    ff=dec_tree(f,right_node_frm(f),COM_sym);
    ss=fst(ff);
    vv=val_root_frm(ss);
    if( is_string_sym(vv)==TRUE ){
      bwrite_prf_res=TRUE;
    } else {
      bwrite_prf_res=FALSE;
    };
    itr(ff,i,fff,kil(fff));
    kil(ff);
  } else {
    bwrite_prf_res=FALSE;
  }
  return bwrite_prf_res;
}

app_badd_rul_prf(p,n,rr,f) /* n == i */
{
  register int v,t,ff,r,s,fff,w,rp,add_rul_prf_res ;
  add_rul_prf_res=FALSE;
  w=val_root_frm(f);
  if( (w==BCRER_sym) || (w==BCREL_sym) ){
    rp=right_frm(f);
    if( val_root_frm(rp)==COM_sym ){
      v=val_tree(rp,left_node_frm(rp));
      if( (ari_sym(v)==0) && (is_nbr_sym(v)==FALSE) ){
        add_rul_prf_res=TRUE;
      }
    }
    kil(rp);
  }
  return add_rul_prf_res;
}

app_badd_lirul_prf(rr,f) /* rr == r */
{
  register int w,rp,v,t,ff,r,i,gg,fff,newfff,badd_lirul_prf_res ;
  badd_lirul_prf_res=FALSE;
  w=val_root_frm(f);
  if( w==BCRELR_sym ){
    rp=right_frm(f);
    if( val_root_frm(rp)==COM_sym ){
      v=val_tree(rp,left_node_frm(rp));
      if( ari_sym(v)==0 ){
        if( is_nbr_sym(v)==FALSE ){
          badd_lirul_prf_res=TRUE;
        }
      }
    }
    kil(rp);
  }
  return badd_lirul_prf_res;
}

app_bpopt_prf(rr,f) /* rr == r */
{
  register int bpopt_res,thn,t,r ;
  bpopt_res=FALSE;
  if( val_root_frm(f)==BPOP_sym ){
    thn=val_tree(f,right_node_frm(f));
    if( ari_sym(thn)==0 ){
      xst_the(t,nam_the(t)==thn,if( len(rul_the(t))!=0 ){
                                   r=lst(rul_the(t));
                                   if( typ_rul(r)!=nrm_rul ){
                                     if( test_lsb_rul(rr,r)==TRUE ){
                                       bpopt_res=TRUE
                                     ;}
                                   ;}
                                 ;},{});
    }
  }
  return bpopt_res;
}

app_bcleant_prf(rr,f) /* rr == r */
{
  register int bcleant_res,thn,t,b;
  bcleant_res=FALSE;
  if( val_root_frm(f)==BCLEAN_sym ){
    thn=val_tree(f,right_node_frm(f));
    if( ari_sym(thn)==0 ){
      xst_the(t,nam_the(t)==thn,b=TRUE,b=FALSE);
      if( b==TRUE ){
        bcleant_res=TRUE;
      }
    }
  }
  return bcleant_res;
}

app_badd_tac_prf(f)
{
  register int v,op,rp,add_tac_prf_res;
  op=val_root_frm(f);
  add_tac_prf_res=FALSE;
  if( (op==BTAC_sym) || (op==FTAC_sym) ){  
    rp=right_frm(f);
    if( val_root_frm(rp)==COM_sym ){   
      v=val_tree(rp,left_node_frm(rp));
      if( (ari_sym(v)==0) && (is_nbr_sym(v)==FALSE) ){
       add_tac_prf_res=TRUE;
      }
    }
    kil(rp);
  }
  return add_tac_prf_res;
}

app_bcatl_prf(i,g,f)
{
  register int n,v,quo_prf_res;
  xst_sub_frm(f,n,v,is_bcatl_frm(f,n)==TRUE,quo_prf_res=TRUE,
                                            quo_prf_res=FALSE);
  return quo_prf_res;
}

app_bnewv_vrb_prf(i,g,f)
{
  register int n,v,new_vrb_prf_res;
  xst_sub_frm(f,n,v,is_bnew_vrb_frm(f,n)==TRUE,new_vrb_prf_res=TRUE,
                                               new_vrb_prf_res=FALSE);
  return new_vrb_prf_res;
}

app_low_prf(i,g,f) /* n == i */
{
  register int n,v,low_prf_res ;
  xst_sub_frm(f,n,v,is_low_frm(f,n)==TRUE,low_prf_res=TRUE,
                                          low_prf_res=FALSE);
  return low_prf_res;
}

app_slmap_prf(n,g,f) /* n == i */
{
  register int v,i,slmap_prf_res;
  xst_sub_frm(f,i,v,v==SLMAP_sym,slmap_prf_res=TRUE,
                                 slmap_prf_res=FALSE);
  return slmap_prf_res;
}

app_nlmap_prf(n,g,f) /* n == i */
{
  register int v,i,slmap_prf_res;
  xst_sub_frm(f,i,v,v==NLMAP_sym,slmap_prf_res=TRUE,
                                 slmap_prf_res=FALSE);
  return slmap_prf_res;
}

app_rideol_test_prf(w,a)  /* breade */
{
  /*
  register int ff,i,fff,s,gg,ggg,b,rid_test_prf_res,ss,vv;
  ff=dec_tree(w,right_node_frm(w),COM_sym);
  gg=dec_tree(a,right_node_frm(a),COM_sym);
  pop(ff);
                    writing the prompt
  if ( len(ff) > 0 ) {
    ss=fst(ff);
    vv=val_root_frm(ss);
    if( is_string_sym(vv)==TRUE ){    
      save_fic;
      con_stderr_fic;
      reset_out(0);
      write_format_out(vv,ff);
      flush_fic;
      restore_fic;
    }
  }
                    reading the input and killing
  s=read_eol_frm;
  psh(lst_input_prf,s);
  rid_test_prf_res=chk_frm(lst(gg),s);
  itr(ff,i,fff,kil(fff));
  kil(ff);
  itr(gg,i,ggg,kil(ggg));
  kil(gg);
  return rid_test_prf_res;
  */
  return TRUE;
}
                            
run_app_prf(r,p,i,gl,flag)
{
  void ApplicableRuleMenu ();
  int f = frm_gol(gl);
  int the, nbr, tot_thy, cur_rul;

/***
char app_buf [ 250 ];
sprintf ( app_buf, "run_app_prf(%d,%d,%d,%d(frm_gol(%d):%d))\n", r,p,i,gl,gl,f);
DisplayCurrWinText ( app_buf );
***/

  app_tot = 1;

/***
app_info ();
***/

#ifndef BTOOLKIT_FLAG
  for ( the = 2 ; the <= nbr_the ; the++ ) {
#else
/*
  for ( the = last_btl_fwd_thy + 1 ; the <= nbr_the ; the++ ) {
*/
  for ( the = last_btl_fwd_thy + 1 ; the <= fwd_btl_users_thy ; the++ ) {
#endif
    tot_thy = nbr_rul_the ( the );
    for ( nbr = tot_thy ; nbr >= 1 ; nbr-- ) {
      cur_rul = val_rul_the ( the, nbr );
      if ( app_test_rul_prf(p,i,r,cur_rul,f) )
         app_rules [ app_tot++ ] = cur_rul;
    }
  }

#ifdef BTOOLKIT_FLAG
  the = last_btl_thy_to_display; /* BToolLemmas */
  tot_thy = nbr_rul_the ( the );
  for ( nbr = tot_thy ; nbr >= 1 ; nbr-- ) {
    cur_rul = val_rul_the ( the, nbr );
/***
str_buf [ 0 ] = '\0';
write_ver_rul_dave ( cur_rul );
printf ( "looking at `%s'\n", str_buf );
***/
    if ( app_test_rul_prf(p,i,r,cur_rul,f) ) {
       app_rules [ app_tot++ ] = cur_rul;
    }
  }
#endif

/***
app_info ();
***/


  /***
  {
    int i;
    char disp_buf [ 250 ];
    DisplayCurrWinText ( "\n---------------------------\n" );
    for ( i = 1 ; i < app_tot ; i++ ) {
      sprintf ( disp_buf, "                         %d %d %s\n", i, app_rules [ i ], Builtin_TAC [ app_rules [ i ] ] );
      DisplayCurrWinText ( disp_buf );
    }
    DisplayCurrWinText ( "---------------------------\n" );
  }
  ***/

  if ( flag ) {
    if   ( app_tot == 1 ) Popup_Info ( "  No applicable rules!  " );
    else                  ApplicableRuleMenu () ;
  }

}
