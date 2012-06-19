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
#ifdef BTOOLKIT_FLAG
#define  btl_lem_rul_MAX 100
int btl_lem_num [ btl_lem_rul_MAX + 2 ];
int btl_lem_rul [ btl_lem_rul_MAX + 2 ];
#endif

int max_sym              = max_sym_val;
int max_rul              = max_rul_val;
int max_the              = max_the_val;
int max_gol              = max_gol_val;
int max_tac              = max_tac_val;
int max_nod              = max_nod_val;
int max_hyp              = max_hyp_val;
int max_seq              = max_seq_val;

#ifdef BTOOLM_FLAG
int max_proved_rr        = max_proved_rr_val;
#endif

int hcod[max_sym_val+1];
int stri[max_sym_val+1];
int lexi[max_sym_val+1];
int edit[max_sym_val+1];
int prio[max_sym_val+1];
int righ[max_sym_val+1];
int clos[max_sym_val+1];
int arity[max_sym_val+1];
int ant[max_rul_val+1];
int cns[max_rul_val+1];
int rth[max_rul_val+1];
int num[max_rul_val+1];
int trl[max_rul_val+1];
int lsb[max_rul_val+1];
int pvd[max_rul_val+1];
int sts[max_rul_val+1];
int rtmb[max_rul_val+1];
int tru[max_the_val+1];
int tna[max_the_val+1];
int tnm[max_the_val+1];
int ttc[max_the_val+1];
int tft[max_the_val+1];
int ttmb[max_the_val+1];
int tdir[max_the_val+1];
int gfrm[max_gol_val+1];
int grul[max_gol_val+1];
int gniv[max_gol_val+1];
int ghso[max_gol_val+1];
int ghyp[max_gol_val+1];
int gbreade[max_gol_val+1];
int gspe[max_gol_val+1];
int isfrmg[max_gol_val+1];
int gtac[max_gol_val+1];
int gtpt[max_gol_val+1];
int gftac[max_gol_val+1];
int gftpt[max_gol_val+1];
int galt[max_gol_val+1];
int gtcl[max_gol_val+1];
int gfcl[max_gol_val+1];
int gtmb[max_gol_val+1];
int tathe[max_tac_val+1];
int tarul[max_tac_val+1];
int taspe[max_tac_val+1];
int tares[max_tac_val+1];
int tafrm[max_tac_val+1];
int tatmb[max_tac_val+1];
int info[max_nod_val+1];
int fath[max_nod_val+1];
int cptr[max_nod_val+1];
int sons[max_nod_val+1];
int snbr[max_nod_val+1];
int ntmb[max_nod_val+1];
int pssubrr[max_nod_val+1];
int hfrm[max_hyp_val+1];
int hrul[max_hyp_val+1];
int hniv[max_hyp_val+1];
int huti[max_hyp_val+1];
int hhso[max_hyp_val+1];
int hspe[max_hyp_val+1];
int htmb[max_hyp_val+1];
int adts[max_seq_val+3];
int tats[max_seq_val+3];
int tmbs[max_seq_val+3];
int coms[max_seq_val+3];

#ifdef BTOOLM_FLAG
int proved_rr [ max_proved_rr_val + 1 ];
int proved_seq_rr [ max_proved_rr_val +1 ];
int proved_seq_sub_rr [ max_proved_rr_val +1 ];
int proved_seq_hyp_rr [ max_proved_rr_val +1 ];
int proved_fwd_btl_rr [ max_proved_rr_val +1 ];
int proved_seq_breade_rr [ max_proved_rr_val +1 ];
#endif
