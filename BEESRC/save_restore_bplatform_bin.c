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
#define read_fm(a,b)    fread(&a,sizeof(int),b,restore_fil)

void restore_bplatform_bin_file ()
{
  int rr;
/* 0 */
  read_fm( rr, 1 );
  read_fm(vnbs,1);
  read_fm(ttms,1);
  read_fm(vad(1),vnbs+1);
  restore_alloc ( vad(vnbs+1) );
  read_fm(mmts[1],vad(vnbs+1));
  read_fm(vtt(1),vnbs);
  read_fm(tmbs[1],ttms);
  mtt(vnbs+1,0);            /* !!! */
  mad(vnbs+2,max_mem);      /* !!! */
/* 1 */
  read_fm( rr, 1 );
  read_fm(sym,1);
  read_fm(stri[1],sym);
  read_fm(lexi[1],sym);
  read_fm(edit[1],sym);
  read_fm(prio[1],sym);
  read_fm(righ[1],sym);
  read_fm(clos[1],sym);
  read_fm(arity[1],sym);
/* 2 */
  read_fm( rr, 1 );
  read_fm(hcod[1],max_sym);
/* 3 */
  read_fm( rr, 1 );
  read_fm(rul,1);
  read_fm(ant[1],rul);
  read_fm(cns[1],rul);
  read_fm(rth[1],rul);
  read_fm(num[1],rul);
  read_fm(trl[1],rul);
  read_fm(lsb[1],rul);
  read_fm(pvd[1],rul);
  read_fm(sts[1],rul);
/* 4 */
  read_fm( rr, 1 );
  read_fm(rttm,1);
  read_fm(rtmb[1],rttm);
/* 7 */
  read_fm( rr, 1 );
  read_fm(the,1);
  read_fm(tru[1],the);
  read_fm(tna[1],the);
  read_fm(tnm[1],the);
  read_fm(ttc[1],the);
  read_fm(tft[1],the);
/* 8 */
  read_fm( rr, 1 );
  read_fm(tttm,1);
  read_fm(ttmb[1],tttm);
/* 9 */
  read_fm( rr, 1 );
  read_fm(ttdi,1);
  read_fm(tdir[1],ttdi);
}

#define write_fm(a,b)    fwrite(&a,sizeof(int),b,save_fil)

void save_bplatform_bin_file ()
{
  int rr;
  srand ( ( int ) ( ( time ( NULL ) % 65536 ) ) );
  rr = ( int ) rand ();
/* 0 */
  write_fm ( rr, 1 );
  write_fm(vnbs,1);
  write_fm(ttms,1);
  write_fm(vad(1),vnbs+1);
  write_fm(mmts[1],vad(vnbs+1));
  write_fm(vtt(1),vnbs);
  write_fm(tmbs[1],ttms);
/* 1 */
  rr = ( int ) rand ();
  write_fm ( rr, 1 );
  write_fm(sym,1);
  write_fm(stri[1],sym);
  write_fm(lexi[1],sym);
  write_fm(edit[1],sym);
  write_fm(prio[1],sym);
  write_fm(righ[1],sym);
  write_fm(clos[1],sym);
  write_fm(arity[1],sym);
/* 2 */
  rr = ( int ) rand ();
  write_fm ( rr, 1 );
  write_fm(hcod[1],max_sym);
/* 3 */
  rr = ( int ) rand ();
  write_fm ( rr, 1 );
  write_fm(rul,1);
  write_fm(ant[1],rul);
  write_fm(cns[1],rul);
  write_fm(rth[1],rul);
  write_fm(num[1],rul);
  write_fm(trl[1],rul);
  write_fm(lsb[1],rul);
  write_fm(pvd[1],rul);
  write_fm(sts[1],rul);
/* 4 */
  rr = ( int ) rand ();
  write_fm ( rr, 1 );
  write_fm(rttm,1);
  write_fm(rtmb[1],rttm);
/* 7 */
  rr = ( int ) rand ();
  write_fm ( rr, 1 );
  write_fm(the,1);
  write_fm(tru[1],the);
  write_fm(tna[1],the);
  write_fm(tnm[1],the);
  write_fm(ttc[1],the);
  write_fm(tft[1],the);
/* 8 */
  rr = ( int ) rand ();
  write_fm ( rr, 1 );
  write_fm(tttm,1);
  write_fm(ttmb[1],tttm);
/* 9 */
  rr = ( int ) rand ();
  write_fm ( rr, 1 );
  write_fm(ttdi,1);
  write_fm(tdir[1],ttdi);
}

