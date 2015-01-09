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
int ini_Blm_done = 0;

void inifunc()
#define ini inifunc()
{
 ini_sys;
 ini_seq; 
 ini_sym; 
 ini_cod; 
 ini_lex;
 ini_res;
 ini_rul; 
 ini_the;
 ini_prf;
 ini_nod;
 ini_hyp;
 ini_gol;
 ini_tac;

#ifdef BTOOLKIT_FLAG
 {
   int i;
   for ( i = 0 ; i < btl_lem_rul_MAX ; i++ ) {
     btl_lem_num [ i ] = 0;
     btl_lem_rul [ i ] = 0;
   }
 }
#endif

#ifdef BTOOLM_FLAG
 {
   int i;
   for ( i = 0 ; i < max_proved_rr ; i++ ) {
     proved_rr [ i ] = 0;
     proved_seq_rr [ i ] = 0;
     proved_seq_sub_rr [ i ] = 0;
     proved_fwd_btl_rr [  i ] = 0;
   }
 }
#endif

#ifndef BTOOLKIT_FLAG

#ifdef BTOOL_FLAG

  if ( ! ini_Blm_done ) ini_Blm ();

#endif /* BTOOL_FLAG */

#endif /* BTOOLKIT_FLAG */

#if ( defined ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

  /***
  get OR_sym
  ***/
  {
    int f;
    strcpy ( str_buf, "aa or bb" );
    f = read_frmfunc_str_buf();
    if ( f != -999 ) {
      OR_sym = val_root_frm ( f );
      kil_from_btoolkit(f);
    }
  }

#endif /* ( defined ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) ) */

}

void re_inifunc()
#define re_ini re_inifunc()
{
 re_ini_sys;
 ini_seq; 
 ini_sym; 
 ini_cod; 
 ini_lex;
 ini_res;
 ini_rul; 
 ini_the;
 
/* ini_prf; */
 ini_nod;
 ini_hyp;
 ini_gol;
 ini_tac;

#ifdef BTOOLKIT_FLAG
 {
   int i;
   for ( i = 0 ; i < btl_lem_rul_MAX ; i++ ) {
     btl_lem_num [ i ] = 0;
     btl_lem_rul [ i ] = 0;
   }
 }
#endif

#ifdef BTOOLM_FLAG
 {
   int i;
   for ( i = 0 ; i < max_proved_rr ; i++ ) { proved_rr [ i ] = 0; }
 }
#endif

}
