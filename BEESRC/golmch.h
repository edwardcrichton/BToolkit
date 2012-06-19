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
extern int gfrm[];
extern int grul[];
extern int gniv[];
extern int ghso[];
extern int ghyp[];
extern int gspe[];
extern int isfrmg[];
extern int gtac[];
extern int gtpt[];
extern int gftac[];
extern int gftpt[];
extern int galt[];
extern int gtcl[];
extern int gfcl[];
extern int gtmb[];
extern int max_gol;
int gol;
int gttm;

#define AND_gol 1

#define DED_gol 2

#define EQL_gol 3

#define RUL_gol 4

#define TAC_gol 5

#define ARI_gol 6

#define SUB_gol 7

#define GEN_gol 8

#define HYP_gol 9

#define MAP_gol 10

#define CAL_gol 11

#define LEM_gol 12

#define QUO_gol 13

#define NEW_gol 14

#define REV_gol 15

#define FLAT_gol 16

#define HALT_gol 17

#define INHYP_gol 18

#define CONTRA_gol 19

#define REDO_gol 20
                  
#define LMAP_gol 21

/*  PROGRAMS FOR GOAL MACHINE  */
                
                  

#define ini_gol gol=0; gttm=0

#define frm_gol(g)  gfrm[g]

#define rul_gol(g)  grul[g]

#define niv_gol(g)  gniv[g]

#define hso_gol(g)  ghso[g]

#define hyp_gol(g)  ghyp[g]

#define spe_gol(g)  gspe[g]


#define is_frm_gol(g)  isfrmg[g]


#define tac_gol(g)  gtac[g]

#define tpt_gol(g)  gtpt[g]

#define ftac_gol(g) gftac[g]

#define ftpt_gol(g) gftpt[g]

#define alt_gol(g)  galt[g]

#define tcl_gol(g)  gtcl[g]

#define fcl_gol(g)  gfcl[g]
/*   
   frm_g:  formula of goal
   rul_g:  rule of goal (if any)
   niv_g:  level of goal (for proof presentation)
   hso_g:  son hypotheses of goal (if any)
   hyp_g:  goal is exactly that hypothesis (if any:HYP_gol)
   spe_g:  special goal (list on top)
   tac_g:  tactic of goal (for backtracking)
   tpt_g:  tactic pointer of goal (for backtracking)
   ftac_g: forward tactic of goal (for backtracking)
   ftpt_g: forward tactic pointer of goal (for backtracking)
   alt_g:  current alternative number (if any:CAL_gol)
   tcl_g:  tactic called (if any:CAL_gol)
   fcl_g:  fwd tactic called (if any:CAL_gol)
 */
   

#define mod_tcl_gol(g,v) gtcl[g]=v

#define mod_fcl_gol(g,v) gfcl[g]=v

#define def_tcl_gol(g) ((tcl_gol(g)!=0)!=0)

#define def_fcl_gol(g) ((fcl_gol(g)!=0)!=0)

#define rem_tcl_gol(g) gtcl[g]=0

#define rem_fcl_gol(g) gfcl[g]=0

#define def_rul_gol(g) ((rul_gol(g)!=0)!=0)

#define def_hso_gol(g) ((hso_gol(g)!=0)!=0)

#define def_spe_gol(g) ((spe_gol(g)!=0)!=0)


#define def_is_frm_gol(g) ((is_frm_gol(g)!=0)!=0)

