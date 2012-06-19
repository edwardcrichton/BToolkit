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
extern int btl_lem_num [];
extern int btl_lem_rul [];
#endif

extern char str_buf [];

#ifdef BTOOLM_FLAG
extern int max_proved_rr;
#endif


#ifdef BTOOLM_FLAG
extern int proved_rr [];
extern int proved_seq_rr [];
extern int proved_seq_sub_rr [];
extern int proved_seq_hyp_rr [];
extern int proved_seq_breade_rr [];
extern int proved_fwd_btl_rr [ max_proved_rr_val +1 ];
#endif

/*******************************************************************************/

#define clr_fnc       tfun=0
#define clr_chk_frm   clr_fnc
#define kil_content_input_prf kil_content_input_prffunc()
#define val_print_ext_prf_the     print_ext_prf
#define val_first_prf_the     first_prf
#define write_res_prf write_res_prffunc()
#define nev_rul 1
#define now_rul 2
#define bef_rul 3
#define nrm_rul 1
#define lem_rul 2
#define rul_rul 3
#define on_rul  1
#define off_rul 2
#define save_MAX_COL_RES        old_MAX_COL_RES=MAX_COL_RES
#define restore_MAX_COL_RES     MAX_COL_RES=old_MAX_COL_RES
#define mod_MAX_COL_RES(n)      MAX_COL_RES=n
#define cptr_nod(n)  cptr[n]
#define sons_nod(n)  sons[n]
#define nxst_sub_frm(t,n,op,P,S1,S2)  nxst(t,n,op,P,S1,S2)
#define nxst(t,i,v,p,s1,s2)  i=1;  while( i<=len(t) ){  v=val(t,i);  if( p ){  s1;  i=len(t)+2  ;} else {  i=i+1  ;};};  if( i==len(t)+1 ){ s2 ;}
#define xst_the(t,p,s1,s2)     stp=stp+2; stack[stp-1]=1; stack[stp-2]=ttdi+1; while( stack[stp-1]!=stack[stp-2] ){ t=tdir[stack[stp-1]]; if( p ){ s1; stack[stp-2]=stack[stp-1] ;} else { stack[stp-1]=stack[stp-1]+1 ;} ;}; if( stack[stp-1]==ttdi+1 ){ s2 ;}; stp=stp-2
#define val_theo_sys    theosys
#define itr(t,i,v,s)  itrn( i , 1 , len(t) , {  v=val(t,i); s  ;})
#define itrn(i,j,k,s)  for(i=j;i<=k;i++) s
#define ini inifunc()
#define ant_rul(r)  ant[r]
#define cns_rul(r)  cns[r]
#define len(s)     vtt(s)
#define vtt(i)     tats[i]
#define val(s,i)   vmm(vad(s)+i)
#define vmm(i)     mmts[i]
#define vad(i)     adts[i]
#define write_frm_res(f,n) write_tree_res(f,root_tree(f),n,FALSE)
#define root_tree(t)  len(t)


/*** copied from seqmch.c.motif ***/
#define kil(x) clr(x); ttms=ttms+1; tmbs[ttms]=x
/*
#ifdef BTOOLKIT_FLAG
#define kil(x) \
  if ( x == 0 ) { \
    printf ( "                                                 kil 0\n" ); \
    Popup_Error ( "  kil 0  " ) \
  } \
  clr(x); ttms=ttms+1; tmbs[ttms]=x
#else
#define kil(x) \
  clr(x); ttms=ttms+1; tmbs[ttms]=x
#endif
*/

/*
#ifdef BTOOLM_FLAG
#define kil(n) if ( n == 0 ) { printf ( "                                                 kil %d\n", n ); Popup_Error ( " kil 0 !!!" ); \
clr(n); } \
ttms=ttms+1; tmbs[ttms]=n
#else
#define kil(n) if ( n == 0 ) { printf ( "                                                 kil %d\n", n ); } \
clr(n); ttms=ttms+1; tmbs[ttms]=n
#endif

#define kil(n) clr(n); ttms=ttms+1; tmbs[ttms]=n
*/


#define clr(s)     mtt(s,0)
#define mtt(i,v)   tats[i]=v
#define nbr_rul_the(t) len(rul_the(t))
#define rul_the(t)  tru[t]
#define val_rul_the(t,n)  val(rul_the(t),n)
#define eql_frm(f,g)  eql_tree(f,root_tree(f),g,root_tree(g))
#define val_tree(t,n) val(t,n)
#define right_node_frm(f)     right_node_tree(f,root_tree(f))
#define left_node_frm(f)      left_node_tree(f,root_tree(f))
#define right_node_tree(t,n)  n-1
#define left_node_tree(t,n)   beg_tree(t,n-1)-1
#define nam_the(t)  tna[t]
#define val_root_frm(f) val_tree(f,root_tree(f))
#define psh(s,v)   aug(s,1);adp(s,v)
#define adp(s,v)   mmm(vad(s)+vtt(s)+1,v);mtt(s,vtt(s)+1)
#define mmm(i,v)   mmts[i]=v
#define mtt(i,v)   tats[i]=v
#define frm_hyp(h)  hfrm[h]
#define fath_nod(n)  fath[n]
#define info_nod(n)  info[n]
#define fst(s)     val(s,1)
#define lst(s)     val(s,len(s))
#define num_rul(r)  num[r]
#define the_rul(r)  rth[r]
#define write_nam_the(t)  write_stri_sym(nam_the(t))
#define write_nat(n) CreNumInBuf ( str_buf, n );
#define mod_rul_sys(b) rulsys=b
#define mod_theo_sys(b) theosys=b
#define pvd_rul(r)  pvd[r]
#define num_the(t)  tnm[t]
#define fwd_tac_the(t) tft[t]
#define def_tac_gol(g) ((tac_gol(g)!=0)!=0)
#define tac_gol(g)  gtac[g]
#define ord(s)        (s)
#define chk_frm(f,g) chk_tree(f,root_tree(f),1,g,root_tree(g),1)
#define isa_der_hyp(h) (((def_rul_hyp(h)==TRUE) || (def_spe_hyp(h)==TRUE))!=0)
#define def_rul_hyp(h) ((rul_hyp(h)!=0)!=0)
#define rul_hyp(h)  hrul[h]
#define def_spe_hyp(h) ((spe_hyp(h)!=0)!=0)
#define spe_hyp(g)  hspe[h]
/*
#define reappend_trm(fstr) ;
#define redirect_trm(fstr) ;
#define reset_trm ;
*/
#define mod_first_prf_the(v)  first_prf=v
#define sts_rul(r)  sts[r]
#define typ_rul(r)  trl[r]
#define right_frm(f)    right_tree(f,root_tree(f))
#define right_tree(t,n) cre_cop_tree(t,right_node_tree(t,n))
#define chk_set_frm(f,g,s) chk_set_tree(f,root_tree(f),1,g,root_tree(g),1,s)
#define val_sts_rul(r)   sts_rul(r)
#define xst(t,i,v,p,s1,s2)  i=len(t);  while( i>0 ){  v=val(t,i);  if( p ){  s1;  i=(-i)  ;} else {  i=i-1  ;};};  if( i==0 ){ s2 ;}
#define xst_sub_frm(t,n,op,P,S1,S2)  xst(t,n,op,P,S1,S2)
#define left_frm(f)     left_tree(f,root_tree(f))
#define left_tree(t,n)  cre_cop_tree(t,left_node_tree(t,n))
#define left_node_tree(t,n)   beg_tree(t,n-1)-1
#define dec_frm(f,v) dec_tree(f,root_tree(f),v)
#define val_alt_gol(g)   alt_gol(g)
#define alt_gol(g)  galt[g]
#define xst_sub_frm(t,n,op,P,S1,S2)  xst(t,n,op,P,S1,S2)
#define fst_str(s)  val_str(s,1)
#define lst_str(s)  val_str(s,len_str(s))
#define nbr_the        ttdi
#define val_rec_sys    recsys
#define lst_all_the lst_all_thefunc()
#define val_batch_sys      batchsys
#define Forward_quota_prf Forward_quota_prffunc()
#define Normal_quota_prf Normal_quota_prffunc()
#define write_prf_name_fil write_prf_name_filfunc()
#define val_loaded_sys    loadedsys
#define lst_all_sym lst_all_symfunc()
#define lod_prf lod_prffunc()
#define save_tool save_BTool_toolfunc()
#define restore_tool restore_BTool_toolfunc()
#define relod_prf relod_prffunc()
#define re_ini re_inifunc()
#define val_reload_sys    reloadsys
#define val_ret_sys    retsys
#define read_the read_thefunc()
#define mod_print_ext_prf_the(v)  print_ext_prf=v
#define mod_reload_sys(b) reloadsys=b
#define has_fwd_tac_the(t) ((fwd_tac_the(t)!=0)!=0)
#define itr_asc_nod(p,n,m,g,S) m=n; while( m!=fath_nod(p) ){ g=info_nod(m); S; m=fath_nod(m) ;}
#define close_all_fic close_all_ficfunc()
#define read_load_file_frm read_load_file_frmfunc()
#define reset_fic reset_ficfunc()
#define cre_sym_fil cre_sym_filfunc()
#define read_file_frm read_file_frmfunc()
#define nitr(t,i,v,s)  nitrn( i , len(t) , 1 , {  v=val(t,i); s  ;})
#define nitrn(i,j,k,s) for(i=j;i>=k;i--) s
#define save_fic            old_file_fic=file_fic
#define restore_fic         file_fic=old_file_fic
#define con_motif_fic file_fic=0
#define open_men_win open_men_winfunc()
#define con_stdwin_fic file_fic=3
#define flush_fic           flush_the_fic(file_fic)
#define clos_win clos_winfunc()
#define itr_str(b,i,v,s)  itrn( i , 1 , len_str(b) , {  v=val_str(b,i); s  ;})
#define len_fnc          tfun
#define maxint        2147483647
#define real_maxint   (2147483647/2)
#define real_minint   -(2147483647/2)
#define close_fic close_ficfunc()
#define max0_tool max0_toolfunc()
#define itr_nod(n,i,v,s1,s2,s3) i=n; while( i!=fath_nod(n) ){ v=info_nod(i); if( cptr_nod(i)==0 ){ s1 ;}; if( cptr_nod(i)==len(sons_nod(i)) ){ cptr_nod(i)=0; s3; i=fath_nod(i) ;} else if( cptr_nod(i)==0 ){ cptr_nod(i)=1; i=fst(sons_nod(i)) ;} else { cptr_nod(i)=cptr_nod(i)+1; s2; i=val(sons_nod(i),cptr_nod(i)) ;}  ;}
#define cptr_nod(n)  cptr[n]
/*
#define spare_mem_percent_seq ((max_mem-vad(vnbs+1))*100)/max_mem
*/
#define con_stderr_fic file_fic=1
#define read_frm read_frmfunc()
#define read_eol_frm read_eol_frmfunc()
#define itr_next_nod(p,n,m,g,S) m=n; while( m!=0 ){ g=info_nod(m); S; m=next_nod(p,m) ;}
#define flush_all_fic flush_all_ficfunc()
#define is_vrb_spe_frm(f)   is_vrb_spe_tree(f,root_tree(f))
#define code_idx_vrb_frm(f,i)  code_vrb_idx_sym(val_tree(f,left_node_tree(f,i)),  val_tree(f,right_node_tree(f,i)))
#define str(s,i,v) mmm(vad(s)+i,v)
#define snbr_nod(n)  snbr[n]
#define reset_fnc(i)     tfun=i
#define mbr(s,v)  ((idx(s,v)!=0)!=0)
#define def_the_tac(t) ((the_tac(t)!=0)!=0)
#define def_spe_tac(t) ((spe_tac(t)!=0)!=0)
#define write_frm_out(f,n) write_tree_out(f,root_tree(f),n)
#define code_idx_vrb_frm(f,i)  code_vrb_idx_sym(val_tree(f,left_node_tree(f,i)),  val_tree(f,right_node_tree(f,i)))
#define chr(s)        (s)
#define add_set(a,v) if( mbr(a,v)==FALSE ){ psh(a,v) ;}
#define is_in_set(s,x) mbr(s,x)
#define exist_set(t,v,p,s1,s2)  stp=stp+1;  if( t<=0 ){ stack[stp-1]=(-t) ;} else { stack[stp-1]=len(t) ;};  while( stack[stp-1]>0 ){  if( t<=0 ){ v=stack[stp-1] ;} else { v=val(t,stack[stp-1]) ;};  if( p ){  s1; stack[stp-1]=(-stack[stp-1])  ;} else {  stack[stp-1]=stack[stp-1]-1  ;}  ;};  if( stack[stp-1]==0 ){ s2 ;};  stp=stp-1
#define  code_vrb_idx_sym(a,b) (10000*a+arith_val_sym(b))
#define pop(s)     mtt(s,vtt(s)-1)
#define eql_spe_frm(f,g)  eql_spe_tree(f,len(f),1,g,len(g),1)
#define xst_asc_nod(p,n,m,g,P,S1,S2) stp=stp+1; stack[stp-1]=FALSE; m=n; while( m!=fath_nod(p) ){ g=info_nod(m); if( P ){ S1; stack[stp-1]=TRUE; m=fath_nod(p) ;} else { m=fath_nod(m) ;}  ;}; if( stack[stp-1]==FALSE ){ S2  ;}; stp=stp-1
#define code_vrb_frm(f) code_vrb_tree(f,root_tree(f))
#define cnc_frm(g,f) cnc_tree(g,f,root_tree(f))
#define uti_hyp(h)  huti[h]
#define niv_hyp(h)  hniv[h]
#define def_lsb_rul(r)  ((lsb_rul(r)!=0)!=0)
#define lsb_rul(r)  lsb[r]
#define tac_the(t)  ttc[t]


extern int max_sym;
extern int max_rul;
extern int max_the;
extern int max_gol;
extern int max_tac;
extern int max_nod;
extern int max_hyp;
extern int max_seq;


extern int exec_prf;
extern int tac_prf;
extern int tac_ptr;
extern int tac_ptr_prf;
extern int fwd_tac_prf;
extern int fwd_tac_ptr_prf;
extern int end_of_tac_prf;
extern int auto_prf;
extern int print_ext_prf;
extern int first_prf;
extern int tfun;
extern int nod;
extern int nttm;
extern int vnbs;
extern int ttms;
extern int MAX_COL_RES;
extern int old_MAX_COL_RES;
extern int stp;
extern int ttdi;
extern int theosys;
extern int rulsys;
extern int sho_der_hyp_prf;
extern int max_ctr_prf;
extern int recsys;
extern int batchsys;
extern int max_fwd_ctr_prf;
extern int new_tac_prf;
extern int ctr_prf;
extern int loadedsys;
extern int abt_prf;
extern int reloadsys;
extern int retsys;
extern int sho_big_gol_prf;
extern int sho_gol_prf;
extern int ini_Blm_done;
extern int file_fic,old_file_fic,file_exists_fic;
extern int max_mem;

extern int stri[];
extern int lexi[];
extern int edit[];
extern int prio[];
extern int righ[];
extern int clos[];
extern int arity[];
extern int ant[];
extern int cns[];
extern int rth[];
extern int num[];
extern int trl[];
extern int lsb[];
extern int pvd[];
extern int sts[];
extern int rtmb[];
extern int tru[];
extern int tna[];
extern int tnm[];
extern int ttc[];
extern int tft[];
extern int ttmb[];
extern int tdir[];
extern int gfrm[];
extern int grul[];
extern int gniv[];
extern int ghso[];
extern int ghyp[];
extern int gbreade[];
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
extern int tathe[];
extern int tarul[];
extern int taspe[];
extern int tares[];
extern int tafrm[];
extern int tatmb[];
extern int info[];
extern int fath[];
extern int cptr[];
extern int sons[];
extern int snbr[];
extern int ntmb[];
extern int pssubrr[];
extern int hfrm[];
extern int hrul[];
extern int hniv[];
extern int huti[];
extern int hhso[];
extern int hspe[];
extern int htmb[];
extern int adts[];
extern int tats[];
extern int tmbs[];
extern int coms[];
extern char name_prf_fil[];
extern int cptr[];
extern int sons[];
extern int stack[];
extern int ant[];
extern int cns[];
/* extern int vtt[]; */
extern int * mmts;
extern int adts[];
extern int tats[];
extern int tmbs[];
extern int tru[];
extern int tna[];
extern int hfrm[];
extern int fath[];
extern int info[];
extern char name_load_fil[];
extern char name_save_fil[];
extern char name_restore_fil[];
extern FILE *save_fil;
extern FILE *restore_fil;
extern char name_fil[];
