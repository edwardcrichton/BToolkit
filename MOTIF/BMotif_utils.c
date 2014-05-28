/* Copyright (c) 1985-98, B-Core (UK) Ltd
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
#include <ctype.h>

#include "BMotif_globals.h"


/***
temp
***/
/***/
#define PUT_NATT(x) printf("%d",x)
void
show_gset (gsetnn)
     int gsetnn;
{
  int nn, cc, Str[250], ex;
  printf ( "    gset%d:\n", gsetnn );
  switch (gsetnn) {
  case 1:
      card_gset1 (&nn);
      break;
  case 2:
      card_gset2 (&nn);
      break;
  case 3:
      card_gset3 (&nn);
      break;
  case 4:
      card_gset4 (&nn);
      break;
  case 5:
      card_gset5 (&nn);
      break;
  }
  if ( ! nn ) printf ( "      empty\n" );
  while (nn > 0) {
    switch (gsetnn) {
    case 1:
	valOrd_gset1 (&cc, nn);
	break;
    case 2:
	valOrd_gset2 (&cc, nn);
	break;
    case 3:
	valOrd_gset3 (&cc, nn);
	break;
    case 4:
	valOrd_gset4 (&cc, nn);
	break;
    case 5:
	valOrd_gset5 (&cc, nn);
	break;
    }
    BLK (6);
    xtr_name (Str, cc);
    puts ((char *) Str);
    val_ext (&ex, cc);
    switch (ex) {
    case mch:
	printf (".mch");
	break;
    case ref:
	printf (".ref");
	break;
    case imp:
	printf (".imp");
	break;
    case bse:
	printf (".bse");
	break;
    case itf:
	printf (".itf");
	break;
    case enm:
	printf (".enm");
	break;
    case doc:
	printf (".doc");
	break;
    case ops:
	printf (".ops");
	break;
    case mch_prf:
      {
	int nn;
	printf (".mch");
	val_prf_level (&nn, cc);
        if ( nn ) {
          printf (".");
	  PUT_NATT (nn-1);
	}
	printf (".prf");
	break;
      }
    case ref_prf:
      {
	int nn;
	printf (".ref");
	val_prf_level (&nn, cc);
        if ( nn ) {
          printf (".");
	  PUT_NATT (nn-1);
	}
	printf (".prf");
	break;
      }
    case imp_prf:
      {
	int nn;
	printf (".imp");
	val_prf_level (&nn, cc);
        if ( nn ) {
          printf (".");
	  PUT_NATT (nn-1);
	}
	printf (".prf");
	break;
      }
    }
    NWL (1);
    nn = nn - 1;
  }
  fflush ( stdout );
}
/***/

correct_pob_for_btl ( nn )
int nn;
{
  if      ( nn == -999999 ) return 0;
  else if ( nn < 0 )        return (-nn);
  else                      return (nn);
}

/*"
   When a ({\em usr\/} or {\em lib\/} construct is introduced,
   appropriate {\em cur\_\/} and {\em cpt\_\/} states are created, with
   all entries being set to FALSE; none of the other optional fields are
   created.
"*/
void
intr_usr_lib (rep, cc, ex, nm, tt)
     int *rep, *cc, ex, *nm, tt;
{
  int rr, curMRI, cptMRI, curGEN, cptGEN;
  make_Construct (&rr, cc, ex, tt);
  if (rr == TRUE) {
    mod_name (&rr, *cc, nm);
    if (rr == TRUE) {
      switch (ex) {
      case mch:
      case ref:
      case imp:
      case doc:
      case map:
	  if (tt == lib) {
/*"
   if a {\em lib\/} set {\em anl\/} and {\em trl\/} to TRUE:
"*/
	    make_MRIState (&rr,
			   &curMRI, TRUE, FALSE, TRUE, FALSE);
	  }
	  else {
	    make_MRIState (&rr,
			   &curMRI, FALSE, FALSE, FALSE, FALSE);
	  }
	  if (rr == TRUE) {
	    if (tt == lib) {
/*"
   if a {\em lib\/} set {\em anl\/} and {\em trl\/} to TRUE:
"*/
	      make_MRIState (&rr, &cptMRI, TRUE, FALSE, TRUE, FALSE);
	    }
	    else {
	      make_MRIState (&rr, &cptMRI, FALSE, FALSE, FALSE, FALSE);
	    }
	    if (rr == TRUE) {
	      cre_curMRIState (*cc, curMRI);
	      cre_cptMRIState (*cc, cptMRI);
	    }
	  }
	  break;
      case bse:
      case enm:
      case itf:
	  make_GENState (&rr,
			 &curGEN, FALSE,
			 FALSE, FALSE);
	  if (rr == TRUE) {
	    make_GENState (&rr,
			   &cptGEN, FALSE, FALSE, FALSE);
	    if (rr == TRUE) {
	      cre_curGENState (*cc, curGEN);
	      cre_cptGENState (*cc, cptGEN);
	    }
	  }
	  break;
      }
    }
    if (rr == FALSE) {
      kill_Construct (*cc);
    }
  }
  *rep = rr;
}



/*" more kills needed for failure cases */
intr_gen (rep, cc, ex, nm, tt, cc1)
     int *rep, *cc, ex, *nm, tt, cc1;
{
  int rr, ac, curMRI, cptMRI, curGEN, cptGEN;
  make_Construct (&rr, cc, ex, tt);
  if (rr == TRUE) {
    mod_name (&rr, *cc, nm);
    if (rr == TRUE) {
      switch (tt) {
      case bse_gen:
	  if (ex == ops) {
	    cre_gen_by (*cc, cc1);
	  }
	  else {
	    make_MRIState (&rr, &curMRI, FALSE, FALSE, FALSE, FALSE);
	    if (rr == TRUE) {
	      make_MRIState (&rr, &cptMRI, FALSE, FALSE, FALSE, FALSE);
	      if (rr == TRUE) {
		cre_curMRIState (*cc, curMRI);
		cre_cptMRIState (*cc, cptMRI);
		cre_gen_by (*cc, cc1);
	      }
	    }
	  }
	  break;
      case enm_gen:
	  make_MRIState (&rr, &curMRI, TRUE, FALSE, TRUE, FALSE);
	  if (rr == TRUE) {
	    make_MRIState (&rr, &cptMRI, TRUE, FALSE, TRUE, FALSE);
	    if (rr == TRUE) {
	      cre_curMRIState (*cc, curMRI);
	      cre_cptMRIState (*cc, cptMRI);
	      cre_gen_by (*cc, cc1);
	    }
	  }
	  break;
      case itf_gen:
	  if (ex == enm) {
	    make_GENState (&rr, &curGEN, FALSE, FALSE, FALSE);
	    if (rr == TRUE) {
	      make_GENState (&rr, &cptGEN, FALSE, FALSE, FALSE);
	      if (rr == TRUE) {
		cre_curGENState (*cc, curGEN);
		cre_cptGENState (*cc, cptGEN);
		cre_gen_by (*cc, cc1);
	      }
	    }
	  }
	  else {
	    make_MRIState (&rr, &curMRI, FALSE, FALSE, FALSE, FALSE);
	    if (rr == TRUE) {
	      make_MRIState (&rr, &cptMRI, FALSE, FALSE, FALSE, FALSE);
	      if (rr == TRUE) {
		cre_curMRIState (*cc, curMRI);
		cre_cptMRIState (*cc, cptMRI);
		cre_gen_by (*cc, cc1);
	      }
	    }
	  }
	  break;
      }
    }
    if (rr == FALSE) {
      kill_Construct (*cc);
    }
  }
  *rep = rr;
}

/*
void
Process_code_files ()
{
  /???
  primary_string contains name (Bool_TYPE);
  ???/
  FILE ? codefile;
  FILE ? tempfile;
  int i;

  for ( i = 0 ; i < 3 ; i++ ) {
    switch ( i ) {
    case 0:
      sprintf ( str_buf, "CDE/C/%s.c", primary_string );
      break;
    case 1:
      sprintf ( str_buf, "CDE/C/%s.g", primary_string );
      break;
    case 2:
      sprintf ( str_buf, "CDE/C/%s.h", primary_string );
      break;
    }
  
/???/
printf ( "Process_code_files: about to fopen `%s'\n", str_buf );
/???/
    codefile = fopen ( str_buf, "r" );
    if ( codefile == NULL ) {
      sprintf ( str_buf, "\"%s\" for reading", str_buf );
      AbortedMsgFile ( str_buf );
      Kill_bplatform_and_exit ( 1, 0 );
    }

    tempfile = fopen ( "TMP/.Bcom", "w" );
    if ( tempfile == NULL ) {
      sprintf ( str_buf, "\"%s\" for writing", "TMP/.Bcom" );
      AbortedMsgFile ( str_buf );
      Kill_bplatform_and_exit ( 1, 0 );
    }

    c = getc ( codefile );
    while ( c != EOF ) {
      if ( c == '<' ) {
        c = getc ( codefile );
        if ( islower(c) ||
             isupper(c) ||
             isdigit(c) ) {
          putc ( ' ', tempfile );
          putc ( '<', tempfile );
          putc ( ' ', tempfile );
          putc ( c, tempfile );
        }
        else {
          putc ( '<', tempfile );
          putc ( c, tempfile );
        }
      }
      else {
        putc ( c, tempfile );
      }
      if ( c != EOF ) c = getc ( codefile );
    }

    fclose ( codefile );
    fclose ( tempfile );

/???/
sprintf ( buf, "diff %s %s", str_buf, "TMP/.Bcom" );
printf ( "\n\n------\ndiff: < %s   > %s\n", str_buf, "TMP/.Bcom" );
system ( buf );
printf ( "------\n" );
/???/
     codefile = fopen ( str_buf, "w" );
     if ( codefile == NULL ) {
       sprintf ( str_buf, "\"%s\" for writing", str_buf );
       AbortedMsgFile ( str_buf );
       Kill_bplatform_and_exit ( 1, 0 );
     }

     tempfile = fopen ( "TMP/.Bcom", "r" );
     if ( tempfile == NULL ) {
       sprintf ( str_buf, "\"%s\" for reading", "TMP/.Bcom" );
       AbortedMsgFile ( str_buf );
       Kill_bplatform_and_exit ( 1, 0 );
     }

    c = getc ( tempfile );
    while ( c != EOF ) {
      putc ( c, codefile );
      c = getc ( tempfile );
    }

     fclose ( codefile );
     fclose ( tempfile );
  }

}
*/

void
Print_extern_dot_h ()
{
  int i, j, k, c;
  FILE * hfile;
  char filename [ 250 ];

  sprintf ( filename, "CDE/C/%s.h", primary_string );

  strcpy ( secondary_string , "\"" );

  /***
  first #include 
  ***/
  hfile = fopen ( filename, "r" );
  if ( hfile == NULL ) {
    sprintf ( fifo_write_buf, "\"%s\" for reading", filename );
    AbortedMsgFile ( fifo_write_buf );
    Kill_bplatform_and_exit ( 1, 0 );
  }
  c = getc ( hfile );
  while ( c != EOF ) {
    /***
    get next word in buf
    ***/
    j = 0;
    while ( ( c != EOF ) && ( c != ' ' ) && ( c != '\n' ) && ( c != '\t' ) ) {
      buf [ j++ ] = c;
      c = getc ( hfile );
    }
    buf [ j ] = '\0';
    if ( strcmp ( buf, "#include" ) == 0 ) {
      strcat ( secondary_string, "#include" );
      i = strlen ( secondary_string );
      while ( ( c != '\n' ) && ( c != EOF ) ) {
        secondary_string [ i++ ] = c;
        c = getc ( hfile );
      }
      secondary_string [ i++ ] = '\n';
      secondary_string [ i++ ] = '\0';
    }
    if ( c != EOF ) c = getc ( hfile );
  }

  /***
  now extern
  ***/
  hfile = fopen ( filename, "r" );
  if ( hfile == NULL ) {
    sprintf ( fifo_write_buf, "\"%s\" for reading", filename );
    AbortedMsgFile ( fifo_write_buf );
    Kill_bplatform_and_exit ( 1, 0 );
  }
  c = getc ( hfile );
  while ( c != EOF ) {
    /***
    get next word in buf
    ***/
    j = 0;
    while ( ( c != EOF ) && ( c != ' ' ) && ( c != '\n' ) && ( c != '\t' ) ) {
      buf [ j++ ] = c;
      c = getc ( hfile );
    }
    buf [ j ] = '\0';
    if ( strcmp ( buf, "extern" ) == 0 ) {
      strcat ( secondary_string, "extern" );
      i = strlen ( secondary_string );
      while ( ( c != ';' ) && ( c != EOF ) ) {
        secondary_string [ i++ ] = c;
        c = getc ( hfile );
      }
      secondary_string [ i++ ] = ';';
      secondary_string [ i++ ] = '\n';
      secondary_string [ i++ ] = '\0';
    }
    if ( c != EOF ) c = getc ( hfile );
  }
  fclose ( hfile );

  strcat ( secondary_string, "\"" );
/***
printf ( "Print_extern_dot_h: secondary_string = `%s'\n", secondary_string );
***/
}


void
Print_inlined_op_dot_h ()
{
  int i, j, c, done;
  FILE * hfile;
  char filename [ 250 ];

  strcpy ( str_buf, primary_string );
  i = 0;
  j = strlen ( str_buf );
  while ( ( primary_string [ i ] != '!' ) && ( i < j ) ) { i++; }
  str_buf [ i ] = '\0';
  if ( i < j ) { i++; }
  strcpy ( filename, "CDE/C/" );
  j = 6;
  while ( ( primary_string [ i ] != '!' ) && ( primary_string [ i ] != '\0' ) ) {
    filename [ j++ ] = primary_string [ i++ ];
  }
  filename [ j ] = '\0';
  strcat ( filename, ".h" );
/***
printf ( "Print_inlined_op_dot_h: str_buf: `%s' filename: `%s' \n", str_buf, filename );
***/
  hfile = fopen ( filename, "r" );
  if ( hfile == NULL ) {
    sprintf ( fifo_write_buf, "\"%s\" for reading", filename );
    AbortedMsgFile ( fifo_write_buf );
    Kill_bplatform_and_exit ( 1, 0 );
  }
  done = 0;
  c = getc ( hfile );
  while ( ( ! done ) && ( c != EOF ) ) {
    /***
    get next word in buf
    ***/
    i = 0;
    while ( ( c != EOF ) && ( c != ' ' ) && ( c != '\n' ) && ( c != '\t' ) ) {
      buf [ i++ ] = c;
      c = getc ( hfile );
    }
    buf [ i ] = '\0';
    if ( strcmp ( buf, "#define" ) == 0 ) {
       while ( ( c == ' ' ) || ( c == '\n' ) || ( c == '\t' ) ) {
        c = getc ( hfile );
      }
      i = 0;
      while ( islower(c) ||
              isupper(c) ||
              isdigit(c) ||
              ( c == '_' )                    ) {
        buf [ i++ ] = c;
        c = getc ( hfile );
      }
      buf [ i ] = '\0';
      if ( strcmp ( buf, str_buf ) == 0 ) {
        sprintf ( secondary_string, "\"#define %s", buf );
        j = strlen ( secondary_string );
        while ( ( c == ' ' ) || ( c == '\n' ) || ( c == '\t' ) ) { c = getc ( hfile ); }
        while ( ( c != EOF ) && ( c != '\n' ) ) {
          if ( c == '\"' ) {
            secondary_string [ j++ ] = '\\';
            secondary_string [ j ] = c;
          }
          else {
            secondary_string [ j ] = c;
          }
          if ( c != EOF ) c = getc ( hfile );
          if ( c == '\n' ) {
	    if ( secondary_string [ j ] == '\\' ) { /* continuation character */
              j++;
              secondary_string [ j ] = c;
              c = getc ( hfile );
	    }
	  }
          j++;
	}       
        secondary_string [ j++ ] = '\"';
        secondary_string [ j ] = '\0';
        done = 1;
      }
    }
    if ( ( c != EOF ) && ( ! done ) ) c = getc ( hfile );
  }
  fclose ( hfile );
}

void
Check_inlined_ops_dot_h ()
{
  /***
  primary_string contains semi-colon construct name list (Bool_TYPE;my_mch);
  secondary_string loaded with #defines appearing after #define in .h files
  ***/

  int i, j, k, c, found;
  FILE * hfile;

  if ( primary_string [ strlen ( primary_string ) - 1 ] == ')' )
    primary_string [ strlen ( primary_string ) - 1 ] = '\0';
  if ( primary_string [ 0 ] == '(' ) k = 1; else k = 0;

  strcpy ( secondary_string, "?" );

  while ( primary_string [ k ] != '\0' ) {
    i = 0;
    while ( ( primary_string [ k ] != '\0' ) && ( primary_string [ k ] != ';' ) ) {
      str_buf [ i++ ] =  primary_string [ k++ ];
    }
    str_buf [ i ] = '\0';

    strcpy ( buf, "CDE/C/" );
    strcat ( buf, str_buf );
    strcat ( buf, ".h" );
/***
printf ( "Check_inlined_ops_dot_h: about to fopen `%s'\n", buf );
***/
    hfile = fopen ( buf, "r" );
    if ( hfile == NULL ) {
      sprintf ( str_buf, "\"%s\" for reading", buf );
      AbortedMsgFile ( str_buf );
      Kill_bplatform_and_exit ( 1, 0 );
    }

    c = getc ( hfile );
    while ( c != EOF ) {
      /***
      get next word in buf
      ***/
      i = 0;
      while ( ( c != EOF ) && ( c != ' ' ) && ( c != '\n' ) && ( c != '\t' ) ) {
        buf [ i++ ] = c;
        c = getc ( hfile );
      }
      buf [ i ] = '\0';
      if ( strcmp ( buf, "#define" ) == 0 ) {
        while ( ( c == ' ' ) || ( c == '\n' ) || ( c == '\t' ) ) {
          c = getc ( hfile );
        }
        i = 0;
        while ( islower(c) ||
                isupper(c) ||
                isdigit(c) ||
                ( c == '_' )                    ) {
          buf [ i++ ] = c;
          c = getc ( hfile );
        }
        buf [ i ] = '\0';
        if ( i + 2 + ( int ) strlen ( secondary_string ) < primary_string_len ) {
          strcat ( secondary_string, "," );
          strcat ( secondary_string, buf );
	}
      }
      if ( c != EOF ) c = getc ( hfile );
    }
    fclose ( hfile );
    if ( primary_string [ k ] == ';' ) k++;
  }
/***
printf ( "strlen ( secondary_string )=%d\n", strlen ( secondary_string ) );
***/
}



intr_prf (rep, pp, ex, cc, nn)
     int *rep, *pp, ex, cc, nn;
{
  int rr, st, mm, cc1, Str[250];
  switch (ex) {
  case mch:
    {
      make_Construct (&rr, &cc1, mch_prf,
		      prf_gen);
      break;
    }
  case ref:
    {
      make_Construct (&rr, &cc1, ref_prf,
		      prf_gen);
      break;
    }
  case imp:
    {
      make_Construct (&rr, &cc1, imp_prf,
		      prf_gen);
      break;
    }
  }
  if (rr == TRUE) {
    xtr_name (Str, cc);
    mod_name (&rr, cc1, Str);
    if (rr == TRUE) {
      cre_prf_level (cc1, nn);
      cre_gen_by (cc1, cc);
      val_curMRIState (&st, cc);
      add_ppf (&rr, st, nn);
      if (rr == TRUE) {
	val_cptMRIState (&st, cc);
	add_ppf (&rr, st, nn);
      }
    }
    if (rr == FALSE) {
      kill_Construct (cc1);
    }
  }
  *pp = cc1;
  *rep = rr;
}


/*"
   {\bf analyse}\\[.5ex]
   Modify {\em anl\/} to TRUE in both {\em curMRIState\/} and
   {\em cptMRIState\/}\\
   create {\em sees\_uses\/} and {\em inc\_ipt\/}, loading
   former from {\em gset1\/} and the latter from {\em gset2\/}\\
   if the first element of {\em gseq\/} is equal {\em cc\/},
   it is a {\em mch\/} and so {\em abs2conc\/} is created with
   {\em cc\/} its first element, otherwise this construct is
   the abstraction of {\em cc\/} and so {\em abs2conc\/} already
   exists, and {\em cc\/} is pushed on to the end:\\
"*/
void
analyse (rep, cc)
     int *rep, cc;
{
  int st, rr, ss, bb, cc1, ac;
  val_curMRIState (&st, cc);
  mod_anl (st, TRUE);
  val_cptMRIState (&st, cc);
  mod_anl (st, TRUE);
  cre_sees_uses (&rr, cc);
  if (rr == TRUE) {
    cre_inc_ipt (&rr, cc);
    if (rr == TRUE) {
      val_gset1 (&ss);
      mod_sees_uses (&rr, cc, ss);
      if (rr == TRUE) {
	val_gset2 (&ss);
	mod_inc_ipt (&rr, cc, ss);
	if (rr == TRUE) {
/*"
   check first element of {\em gseq\/} to see if {\em cc\/} is a
   {\em mch\/}:
"*/
	  valIth_gseq (&cc1,
		       1);
	  if (cc1 != cc) {
/*"
   {\em cc\/} therefore a {\em ref\/} or {\em imp\/}, {\em abs2cons\/}
   already exists for the abstraction {\em cc1\/}, create the reference
   here and so push {\em cc\/} onto the {\em abs2cons\/} sequence:
"*/
	    val_abs2conc (&ac,
			  cc1);
	    cre_abs2conc (cc, ac);
	    push_a2c (&rr, ac, cc);
	  }
	  else {
/*"
   {\em cc\/} a {\em mch\/}, and so create {\em abs2cons\/}
   as a singleton containing {\em cc\/}, and cretae the reference:
"*/
	    make_Abs2Conc (&rr,
			   &ac);
	    cre_abs2conc (cc, ac);
	    if (rr == TRUE) {
	      push_a2c (&rr, ac, cc);
	    }
	  }
	}
      }
    }
  }
  *rep = rr;
}


/*"
   {\bf unanalyse}\\[.5ex]
   {\em abs2conc\/} is first removed and, if {\em mm\/} is 1,
   {\em abs2conc\/} is updated (when, if {\em cc\/} is a
   {\em mch\/}, the {\em Abs2Conc\/} object is killed);\\
   the {\em anl\/}, {\em dmu\/}, {\em trl\/} and {\em lnk\/} are
   set to FALSE and {\em pob\/} and {\em prf\/} set to empty in
   the {\em curMRIState\/} of {\em cc\/}\\
   finally, {\em sees\_uses\/} and {\em inc\_ipt\/} are removed:\\
"*/
void
unanalyse (cc, mm)
     int cc, mm;
{
  int rr, st, bb, ac, ex, cc1, nn;
  val_abs2conc (&ac, cc);
  rem_abs2conc (cc);
  if (mm == 1) {
    val_ext (&ex, cc);
    if (ex == mch) {
      kill_Abs2Conc (ac);
    }
    else {
      vld_Abs2Conc (&bb, ac);
      if (bb == TRUE) {
	bb = FALSE;
	nn = 20;
	while (bb == FALSE) {
	  last_a2c (&cc1,
		    ac);
	  pop_a2c (ac);
	  nn = nn - 1;
	  if (cc1 == cc) {
	    bb = TRUE;
	  }
	}
      }
    }
  }
  val_curMRIState (&st, cc);
  mod_anl (st, FALSE);
  mod_dmu (st, FALSE);
  mod_trl (st, FALSE);
  mod_lnk (st, FALSE);
  clear_pob (st);
  clear_ppf (st);
  clear_ppf_dmu (st);
  def_sees_uses (&bb, cc);
  if (bb) {
    rem_sees_uses (cc);
  }
  def_inc_ipt (&bb, cc);
  if (bb) {
    rem_inc_ipt (cc);
  }
}



pogenerate (rep, cc, nn)
     int *rep, cc, nn;
{
  int st, rr, ll;
  val_curMRIState (&st, cc);
  push_pob (&rr, st, nn);
/*"
   Check recorded in {\em cpt\/} state:
"*/
  if (rr == TRUE) {
    val_cptMRIState (&st, cc);
    length_pob (&ll, st);
    if (ll == 0) {
      push_pob (&rr, st, nn);
    }
    val_cptMRIState (&st, cc);
    modIth_pob ( st, 1, nn );    
  }
  *rep = rr;
}



autoprove (rep, cc, nn, tt)
     int *rep, cc, nn, tt;
{
  int st, rr, ll1, ll2, tot, mm;
/*
  Both nn(left) & tt(total) negative if btool-proved
*/
/***
printf ( " -->> BMotif_utils - autoprove cc=%d nn=%d(left) %d(tot pobs)\n", cc, nn, tt );
***/
  val_curMRIState (&st, cc);
  push_pob (&rr, st, nn);
  length_pob (&ll1, st);
/***
printf ( "curMRIState=%d length NOW=%d\n", st, ll1 );
***/
/*"
   Check {\em cpt\/} state has at least this level:
"*/
  if (rr == TRUE) {
    val_cptMRIState (&st, cc);
    length_pob (&ll2, st);
/***
printf ( "cptMRIState=%d length BFR=%d\n", st, ll2 );
***/
    if (ll2 < ll1) {
      push_pob (&rr, st, nn);
    }
  }
/*"
   Set {\em cpt\/} at {\em ll1\/} equal to {\em cur\/} 
"*/
  modIth_pob ( st, ll1, nn );
/*"
   Set {\em cpt\/} at {\ ll1\/} equal to {\em tt\/} - YES TOTAL POBS (- if btl)
"*/
  val_cptMRIState (&st, cc);
  modIth_pob ( st, ll1, tt );
/*"
   If no pobs left, equalise length of cpt to cur ...
"*/
  if ( (nn == 0) || (nn = -999999) ){
    val_curMRIState (&st, cc);
    length_pob (&ll1, st);
    val_cptMRIState (&st, cc);
    length_pob (&ll2, st);
    while (ll2 > ll1 && ll2 > 0) {
      pop_pob (st);
      length_pob (&ll2, st);
    }
/*"
   ... and check that entries in ppf & ppf_dmu for cpt do not exceed ll1
"*/
    card_ppf (&tot, st);
    while ( tot ) {
      valOrd_ppf ( &mm, st, tot );
      if ( mm >= ll1 ) del_ppf ( st, mm );
      tot--;
    }
    card_ppf_dmu (&tot, st);
    while ( tot ) {
      valOrd_ppf_dmu ( &mm, st, tot );
      if ( mm >= ll1 ) del_ppf_dmu ( st, mm );
      tot--;
    }
  }
/***
printf ( "curMRIState    length NOW=%d\n", ll1 );
printf ( "cptMRIState    length NOW=%d\n", ll2 );
***/

  *rep = rr;
}




/*"
   {\bf get\_sub\_cst}\\[.5ex]
   Subordinate constructs to {\em cc\/} loaded into {\em gset1\/}.\\
   Initially, {\em cc\/} put into {\em gset2\/} together with all
   constructs that appear in its {\em abs2conc\/} sequence up to {\em cc\/}\\
   the loop continues until {\em gset2\/} is empty, and at each cycle the
   first construct, {\em cc1\/} is removed from {\em gset2\/} and added
   to {\em gset1\/}, and:\\
   if {\em sees\_uses\/} is set for {\em cc1\/}, it is added (unioned) to
   {\em gset2\/}\\
   if {\em inc_ipt\/} is set for {\em cc1\/}, it is added (unioned) to
   {\em gset2\/}\\
   if {\em gen\_by\/} is set for {\em cc1\/}, it is added to {\em gset2\/}.
"*/
void
get_sub_cstr (rep, cc)
     int *rep, cc;
{
  int rr, card2, ss, cc1, cc2, bb, ac, nn, bbb;
/*"
   Clear both buffers, and load {\em gset2\/} with {\em cc\/}:
"*/
  clear_gset1 ();
  clear_gset2 ();
  add_gset2 (&rr, cc);
  if (rr == TRUE) {
    val_abs2conc (&ac, cc);
    bb = FALSE;
    nn = 1;
    while (bb == FALSE && rr == TRUE) {
      valIth_a2c (&cc1, ac, nn);
      if (cc1 != cc) {
	member_gset2 (&bbb, cc1);
	if (bbb == FALSE) {
	  add_gset2 (&rr, cc1);
	}
	nn = nn + 1;
      }
      else {
	bb = TRUE;
      }
    }
/*"
   Initialise {\em card2\/} to $1$, and start loop:
"*/
    if (rr == TRUE) {
      card2 = 1;
      while (card2 > 0 && rr == TRUE) {
/*"
   Remove first element {\em cc1\/} from {\em gset2\/} and add to {\em gset1\/}:
"*/
	valOrd_gset2 (&cc1, 1);
	del_gset2 (cc1);
	member_gset1 (&bbb, cc1);
	if (bbb == FALSE) {
	  add_gset1 (&rr, cc1);
	}
/*"
   Test for {\em sees\_uses\/}, and union to {\em gset1\/} (since sees/uses
   is not transitive) if it exists:
"*/
	if (rr == TRUE) {
	  def_sees_uses (&bb,cc1);
	  if (bb == TRUE) {
	    val_sees_uses (&ss,cc1);
	    union_gset1 (&rr, ss);
	  }
	}
/*"
   Test for {\em inc\_ipt\/}, and union to {\em gset2\/} (since inc/ipt
   is transitive) if it exists:
"*/
	if (rr == TRUE) {
	  def_inc_ipt (&bb,cc1);
	  if (bb == TRUE) {
	    val_inc_ipt (&ss,cc1);
	    union_gset2 (&rr, ss);
	  }
	}
/*"
   Test for {\em gen\_by\/}, and add to {\em gset2\/} (since generates
   is transitive) if it exists:
"*/
	if (rr == TRUE) {
	  def_gen_by (&bb,
		      cc1);
	  if (bb == TRUE) {
	    val_gen_by (&cc2,
			cc1);
	    member_gset2 (&bb, cc2);
	    if (bb == FALSE) {
	      add_gset2 (&rr, cc2);
	    }
	  }
	}
	card_gset2 (&card2);
      }
    }
/*"
   Finally, remove the original construct {\em cc\/} from {\em gset1\/}:
"*/
    if (rr == TRUE) {
      del_gset1 (cc);
    }
    *rep = rr;
  }
}



/*"
   {\bf getnext\_dep\_cst}\\[.5ex]
   Takes last element of {\em gset2\/}, {\em cc1\/}, and looks for upward
   dependents of {\em cc1\/} by looping through the {\em Construct\/} base;\\
   if found, they are added to {\em gset2\/}\\
   finally, {\em cc1\/} is moved from {\em gset2\/} to {\em gset1\/}\\
   if {\em cc1\/} is from {\em sees_uses\/} or {\em inc\_ipt\/} it\\
   is also added to {\em gset3\/}, so that the upward {\em abs2conc\/}\\
   of each can be added to {\em gset2\/} (done by {\em add\_a2cdep\/})\\
   (flag get_dep_cstr_num contains the construct for which dep sought):
"*/
void
getnext_dep_cst (rep)
     int *rep;
{
  int cc1, rr, found, loc, cc2, cc3, bb, cc4, ll, nn, ex, st, nm [ 50 ];
  void get_topabs ();

  card_gset2 (&ll);
  valOrd_gset2 (&cc1, ll);

/***
printf ("    getnext_dep_cst for %d %s\n", cc1, GetName (cc1));
***/

/***
print_Globals_CfgDepBase();
***/

  rr = TRUE;
  first_Construct (&loc, &cc2);
  while (loc != 0 && rr == TRUE) {
/*"
Check {\em cc2\/} not already in {\em gset1\/} or {\em gset2\/},
and is not {\em cc1 \/}:
"*/
    member_gset1 (&bb, cc2);
    if ( bb == FALSE ) {
      member_gset2 (&bb, cc2);
    }
    if (bb == FALSE && cc1 != cc2) {
      found = FALSE;

/*"
Check if {\em cc1\/} is seen/used by {\em cc2\/} if so, add
{\em cc2\/} to {\em gset2\/} if not already in {\em gset1\/}:
"*/
      if (found == FALSE && rr == TRUE) {
	def_sees_uses (&bb, cc2);
	if (bb == TRUE) {
	  member_sees_uses (&bb, cc2, cc1);
	  if (bb == TRUE) {
	    member_gset1 (&bb, cc2);
	    if (bb == FALSE) {
	      member_gset2 (&bb, cc2);
	      if (bb == FALSE) {
		add_gset2 (&rr, cc2);
		found = TRUE;
/***
printf ("            member_sees_uses %d %s\n", cc2, GetName (cc2));
***/
		if (rr == TRUE) {
		  member_gset3 (&bb, cc2);
		  if (bb == FALSE) {
		    add_gset3 (&rr, cc2);
		  }
		}
	      }
	    }
	  }
	}
      }

/*"
Check if {\em cc1\/} is included/imported by {\em cc2\/} if so, add
{\em cc2\/} to {\em gset2\/} if not already in {\em gset1\/}:
"*/
      if (found == FALSE && rr == TRUE) {
	def_inc_ipt (&bb, cc2);
	if (bb == TRUE) {
	  member_inc_ipt (&bb, cc2, cc1);
	  if (bb == TRUE) {
	    member_gset1 (&bb, cc2);
	    if (bb == FALSE) {
	      member_gset2 (&bb, cc2);
	      if (bb == FALSE) {
		add_gset2 (&rr, cc2);
		found = TRUE;
/***
printf ("            member_inc_ipt %d %s\n", cc2, GetName (cc2));
***/
		if (rr == TRUE) {
		  member_gset3 (&bb, cc2);
		  if (bb == FALSE) {
		    add_gset3 (&rr, cc2);
		  }
		}
	      }
	    }
	  }
	}
      }


/*
Check if {\em cc1\/} is generated by {\em cc2\/} if so, add
{\em cc2\/} to {\em gset2\/} if not already in {\em gset1\/};
do this only if top\_level\_dep\_cstr is not a bse\_gen/itf\_gen/enm\_gen:
*/
      val_type(&tt,top_level_dep_cstr);
      if ( ( tt != bse_gen ) && ( tt != itf_gen )  && ( tt != enm_gen ) ) {  
        if ( ( cc1 != cc2 )    && ( found == FALSE ) && ( rr == TRUE ) ) {
	  def_gen_by (&bb, cc1);
	  if (bb == TRUE) {
/***
printf ("%s(%d)       generated by       ", GetName (cc1),cc1);
printf ("%s(%d)?\n", GetName (cc2),cc2);
***/
	    eql_gen_by (&bb, cc1, cc2);
	    if (bb == TRUE) {
	      member_gset1 (&bb, cc2);
	      if (bb == FALSE) {
	        member_gset2 (&bb, cc2);
	        if (bb == FALSE) {
		  add_gset2 (&rr, cc2);
		  found = TRUE;
/***
printf ("     ------------>>>>>>>>> YES <<<<<<<<<<---------\n\n");
***/
                }
	      }
	    }
	  }
	}
/***
else printf ( "                  %s is gen ops/imp\n", GetName (cc2)); 
***/
      }


/*"
Check if {\em cc1\/} generates {\em cc2\/} if so, add
{\em cc2\/} to {\em gset2\/} if not already in {\em gset1\/}:
"*/
      if ((cc1 != cc2) && (found == FALSE) && (rr == TRUE)) {
	def_gen_by (&bb, cc2);
	if (bb == TRUE) {
/***
printf ("%s(%d)       generates       ", GetName (cc1),cc1);
printf ("%s(%d)*\n", GetName (cc2),cc2);
***/
	  eql_gen_by (&bb, cc2, cc1);
	  if (bb == TRUE) {
/***
printf ("     ------------>>>>>>>>> YES <<<<<<<<<<---------\n\n");
***/
	    member_gset1 (&bb, cc2);
	    if (bb == FALSE) {
	      member_gset2 (&bb, cc2);
	      if (bb == FALSE) {
		add_gset2 (&rr, cc2);
		found = TRUE;
/***
printf ("            generates %d %s\n", cc2, GetName (cc2));
***/
	      }
	    }
	  }
	}
      }

      if ( found == TRUE ) {
        val_ext ( &ex, cc2 );
        if ( ex == imp ) {
          get_topabs ( &cc3, cc2 );
          xtr_name( nm, cc3 );
          GetObjFromNameExt ( &cc3, nm, itf );
          if ( cc3 ) {
            val_curGENState( &st, cc3 );
            val_gen1 ( &bb, st );
            if ( bb ) {
              member_gset1 (&bb, cc3);
	      if ( ! bb ) {
	        member_gset2 (&bb, cc3);
	        if ( ! bb ) {
	          add_gset2 (&rr, cc3);
/***
printf ("            interface %d %s\n", cc3, GetName (cc3));
***/
	        }
	      }
	    }
            val_gen2 ( &bb, st );
            if ( bb ) {
              member_gset1 (&bb, cc3);
	      if ( ! bb ) {
	        member_gset2 (&bb, cc3);
	        if ( ! bb ) {
	          add_gset2 (&rr, cc3);
/***
printf ("            interface %d %s\n", cc3, GetName (cc3));
***/
	        }
	      }
	    }
	  }
	}
      }

    }

    next_Construct (&loc, &cc2, loc, cc2);

  }
/***
printf ("    removing %d %s from gset2 ", cc1, GetName (cc1));
***/
  if (rr == TRUE) {
    del_gset2 (cc1);
    member_gset1 (&bb, cc1);
    if (bb == FALSE) {
/***
printf ("and adding to gset1\n");
***/
      add_gset1 (&rr, cc1);
    }
/***
    else {
printf ("(already in gset1)\n");
    }
***/
  }
  *rep = rr;
}



/*"
   {\bf add\_a2cdep}\\[.5ex]
   adds upward {\em abs2conc\/} for {\em cc\/} to {\em gset1\/}\\
   first check it's defined (it might be a {\em doc\/}:
"*/
void
add_a2cdep (rep, cc)
     int *rep, cc;
{
  int rr, ac, ll, bb, cc1;
  rr = TRUE;
  def_abs2conc (&bb, cc);
  if (bb == TRUE) {
    val_abs2conc (&ac, cc);
    length_a2c (&ll, ac);
    bb = FALSE;
    rr = TRUE;
    while (bb == FALSE && rr == TRUE) {
      valIth_a2c (&cc1, ac, ll);
      if (cc != cc1) {
	member_gset1 (&bb, cc1);
	if (bb == FALSE) {
	  add_gset1 (&rr, cc1);
	}
	ll = ll - 1;
      }
      else {
	bb = TRUE;
      }
    }
  }
  *rep = rr;
}


/*"
   {\bf get\_topabs}\\[.5ex]
   Returns top level abstraction for {\em cc\/}:
"*/
void
get_topabs (cc1, cc)
     int *cc1, cc;
{
  int bb, ac;
  def_abs2conc (&bb, cc);
  if (bb == FALSE) {
    *cc1 = cc;
  }
  else {
    val_abs2conc (&ac, cc);
    valIth_a2c (cc1, ac, 1);
  }
}




/*"
   {\bf get\_botref}\\[.5ex]
   Returns lowest level refinement for {\em cc\/}:
"*/
void
get_botref (cc1, cc)
     int *cc1, cc;
{
  int bb, ac;
  def_abs2conc (&bb, cc);
  if (bb == FALSE) {
    *cc1 = cc;
  }
  else {
    val_abs2conc (&ac, cc);
    last_a2c (cc1, ac);
  }
}



/*"
   {\bf getnext\_recipt\_mchlist}\\[.5ex]
   Removes last element of {\em gset2\/}, {\em cc1\/}, and adds its
   {\em inc\_ipt\/} to {\em gset\/1} for each of these {\em mch\/},
   their {\em imp\/} (if it exists) is added to {\em gset2\/} if
   not already there; if it is, it is added to {\em gset3\/}
   (duplicate imports!):
"*/
void
getnext_recipt_mchlist (rep)
     int *rep;
{
  int ll, cc1, cc2, ac, ex, rr, bb;
  rr = TRUE;
  card_gset2 (&ll);
/***
printf ( "card_gset2 = %d\n", ll );
***/
  if (ll != 0) {
    valOrd_gset2 (&cc1, ll);
    del_gset2 (cc1);
    def_inc_ipt(&bb,cc1);
/***
def_inc_ipt(&bb,cc1);
printf ( "def_inc_ipt of %d %s = %d\n", cc1, GetName ( cc1 ), bb );
***/
    if ( bb == TRUE ) {
      card_inc_ipt (&ll, cc1);
/***
printf ( "card_inc_ipt of %d %s = %d\n", cc1, GetName ( cc1 ), ll );
***/
      while (ll > 0 && rr == TRUE) {
        valOrd_inc_ipt (&cc2, cc1, ll);
        member_gset1 (&bb, cc2);
        if (bb == TRUE) {
	  member_gset3 (&bb, cc2);
	  if (bb == FALSE) {
	    add_gset3 (&rr, cc2);
	  }
        }
        else {
	  add_gset1 (&rr, cc2);
        }
        if (rr == TRUE) {
	  val_abs2conc (&ac, cc2);
	  last_a2c (&cc2, ac);
	  val_ext (&ex, cc2);
	  if (ex == imp) {
	    member_gset2 (&bb, cc2);
	    if (bb == FALSE) {
	      add_gset2 (&rr, cc2);
	    }
	  }
	}
        ll = ll - 1;
/***
printf ( "ll %d -> %d\n", ll + 1, ll );
***/
      }
    }
  }
  *rep = rr;
}



/*"
   {\bf getnext\_recseen\_mchlist}\\[.5ex]
   Removes last element of {\em gset2\/}, {\em cc1\/}, and adds its
   {\em seen\_uses\/} to {\em gset\/1} for each of these {\em mch\/},
   their {\em imp\/} (if it exists) is added to {\em gset2\/}:
"*/
void
getnext_recseen_mchlist (rep)
     int *rep;
{
  int ll, cc1, ss, rr, ac, cc2, ex, bb, b1;
  rr = TRUE;
  card_gset2 (&ll);
  if (ll != 0) {
    valOrd_gset2 (&cc1, ll);
    del_gset2 (cc1);
    def_sees_uses(&b1, cc1);
    if (b1 == TRUE) {
      card_sees_uses (&ll, cc1);
      if (ll != 0) {
        val_sees_uses (&ss, cc1);
        union_gset1 (&rr, ss);
      }
      while (ll > 0 && rr == TRUE) {
        valOrd_sees_uses (&cc2, cc1, ll);
        val_abs2conc (&ac, cc2);
        last_a2c (&cc2, ac);
        val_ext (&ex, cc2);
        if (ex == imp) {
	  member_gset2 (&bb, cc2);
	  if (bb == FALSE) {
	    add_gset2 (&bb, cc2);
	    chk_rep (bb, 167);
	  }
        }
        ll = ll - 1;
      }
    }
    if (rr == TRUE) {
      def_inc_ipt (&b1, cc1);
      if (b1 == TRUE) {
        card_inc_ipt (&ll, cc1);
        while (ll > 0 && rr == TRUE) {
          valOrd_inc_ipt (&cc2, cc1, ll);
	  val_abs2conc (&ac, cc2);
	  last_a2c (&cc2, ac);
	  val_ext (&ex, cc2);
	  if (ex == imp) {
	    member_gset2 (&bb, cc2);
	    if (bb == FALSE) {
	      add_gset2 (&bb, cc2);
	      chk_rep (bb, 168);
	    }
	  }
          ll = ll - 1;
        }
      }
    }
  }
  *rep = rr;
}




/*"
   {\bf getnext\_recseenipt\_mchlist}\\[.5ex]
   Removes last element of {\em gset2\/}, {\em cc1\/}, and adds its
   {\em inc\_ipt\/} and its {\em seen\_uses\/} to {\em gset\/1}
   for each of these {\em mch\/}, their {\em imp\/} (if it exists)
   is added to {\em gset2\/}:
"*/
void
getnext_recseenipt_mchlist (rep)
     int *rep;
{
  int ll, ss, nn, cc1, cc2, ac, ex, rr, bb, b1;
  rr = TRUE;
  card_gset2 (&ll);
  if (ll != 0) {
    valOrd_gset2 (&cc1, ll);
    del_gset2 (cc1);
    def_sees_uses(&b1, cc1);
    if (b1 == TRUE) {
      card_sees_uses (&ll, cc1);
      if (ll != 0) {
        val_sees_uses (&ss, cc1);
        union_gset1 (&rr, ss);
        if (rr == TRUE) {
	  nn = 1;
	  while (nn <= ll && rr == TRUE) {
	    valOrd_sees_uses (&cc2, cc1, nn);
	    val_abs2conc (&ac, cc2);
	    last_a2c (&cc2, ac);
	    val_ext (&ex, cc2);
	    if (ex == imp) {
	      member_gset2 (&bb, cc2);
	        if (bb == FALSE) {
	        add_gset2 (&bb, cc2);
	        chk_rep (bb, 169);
	      }
	    }
	    nn = nn + 1;
	  }
	}
      }
    }
    if (rr == TRUE) {
      def_inc_ipt (&rr, cc1);
      if (rr == TRUE) {
        card_inc_ipt (&ll, cc1);
        if (ll != 0) {
	  val_inc_ipt (&ss, cc1);
	  union_gset1 (&rr, ss);
	  if (rr == TRUE) {
	    nn = 1;
	    while (nn <= ll && rr == TRUE) {
	      valOrd_inc_ipt (&cc2, cc1, nn);
	      val_abs2conc (&ac, cc2);
	      last_a2c (&cc2, ac);
	      val_ext (&ex, cc2);
	      if (ex == imp) {
	        member_gset2 (&bb, cc2);
	        if (bb == FALSE) {
		  add_gset2 (&rr, cc2);
	        }
	      }
	      nn = nn + 1;
	    }
	  }
        }
      }
    }
  }
  *rep = rr;
}



/*"
   {\bf get_unused_lib}\\[.5ex]
   All unused library constructs loaded into {\em gset1\/}:
"*/
void
get_unused_lib (rep)
     int *rep;
{
  int rr, loc, cc1, bb, ss, tt;
/*"
   first load all sees\_uses/inc\_ipt machines into {\em gset2\/}
"*/
  clear_gset2 ();
  rr = TRUE;
  first_Construct (&loc, &cc1);
  while (loc != 0 && rr == TRUE) {
    def_sees_uses (&bb, cc1);
    if (bb == TRUE) {
      val_sees_uses (&ss, cc1);
      union_gset2 (&rr, ss);
    }
    if (rr == TRUE) {
      def_inc_ipt (&bb, cc1);
      if (bb == TRUE) {
	val_inc_ipt (&ss, cc1);
	union_gset2 (&rr, ss);
      }
    }
    next_Construct (&loc, &cc1, loc, cc1);
  }
/*"
   now loop through {\em lib\/} machines, and if not present in
   {\em gset2\/} add to {\em gset1\/}
"*/
  if (rr == TRUE) {
    clear_gset1 ();
    first_Construct (&loc, &cc1);
    while (loc != 0 && rr == TRUE) {
      val_type (&tt, cc1);
      if ( tt == lib || tt == lib_vhdl ) {
	member_gset2 (&bb, cc1);
	if (bb == FALSE) {
	  member_gset1 (&bb, cc1);
	  if (bb == FALSE) {
	    add_gset1 (&rr, cc1);
	  }
	}
      }
      next_Construct (&loc, &cc1, loc,
		      cc1);
    }
  }
  *rep = rr;
}



/*"
   {\bf val\_curMRI}\\[.5ex]
   In addition to return parameters, {\em gset1\/}
   is loaded with value of {\em ppf\/}
   {\em len_pob\/}: lenth of {\em pob\/}\\
   {\em fpob\/}: first element of {\em pob\/}\\
   {\em ppob\/}: penultimate element of {\em pob\/}\\
   {\em lpob\/}: last element of {\em pob\/}\\
   if any of the last three do not exists, 0 returned
"*/
void
val_curMRI (bb_anl, bb_dmu, bb_trl, bb_lnk,
	    lenpob, fpob, ppob, lpob, cc)
     int *bb_anl, *bb_dmu, *bb_trl, *bb_lnk, *lenpob, *fpob, *ppob, *lpob,
       cc;
{
  int st, nn;
  val_curMRIState (&st, cc);
  val_anl (bb_anl, st);
  val_dmu (bb_dmu, st);
  val_trl (bb_trl, st);
  val_lnk (bb_lnk, st);
  length_pob (&nn, st);
  if (nn >= 3) {
    valIth_pob (fpob, st, 1);
    valIth_pob (ppob, st, nn - 1);
    last_pob (lpob, st);
  }
  else {
    switch (nn) {
    case 2:
      {
	valIth_pob (fpob, st, 1);
	*ppob = 0;
	last_pob (lpob, st);
	break;
      }
    case 1:
      {
	valIth_pob (fpob, st, 1);
	*ppob = 0;
	last_pob (lpob, st);
	break;
      }
    default:
      {
	*fpob = 0;
	*ppob = 0;
	*lpob = 0;
	break;
      }
    }
  }
  *lenpob = nn;
}




/*"
   {\bf val\_cptMRI}\\[.5ex]
   In addition to return parameters, {\em gset1\/}
   is loaded with value of {\em ppf\/}
   {\em len_pob\/}: lenth of {\em pob\/}\\
   {\em fpob\/}: first element of {\em pob\/}\\
   {\em ppob\/}: penultimate element of {\em pob\/}\\
   {\em lpob\/}: last element of {\em pob\/}\\
   if any of the last three do not exists, 0 returned
"*/
void
val_cptMRI (bb_anl, bb_dmu, bb_trl, bb_lnk,
	    lenpob, fpob, ppob, lpob, cc)
     int *bb_anl, *bb_dmu, *bb_trl, *bb_lnk, *lenpob, *fpob, *ppob, *lpob,
       cc;
{
  int st, nn;
  val_cptMRIState (&st, cc);
  val_anl (bb_anl, st);
  val_dmu (bb_dmu, st);
  val_trl (bb_trl, st);
  val_lnk (bb_lnk, st);
  length_pob (&nn, st);
  if (nn >= 3) {
    valIth_pob (fpob, st, 0);
    valIth_pob (ppob, st, nn - 1);
    last_pob (lpob, st);
  }
  else {
    switch (nn) {
    case 2:
      {
	valIth_pob (fpob, st, 1);
	*ppob = 0;
	last_pob (lpob, st);
	break;
      }
    case 1:
      {
	valIth_pob (fpob, st, 1);
	*ppob = 0;
	last_pob (lpob, st);
	break;
      }
    default:
      {
	*fpob = 0;
	*ppob = 0;
	*lpob = 0;
	break;
      }
    }
  }
  *lenpob = nn;
}



val_curGEN (bb_gen1, bb_gen2, bb_dmu, cc)
     int *bb_gen1, *bb_gen2, *bb_dmu, cc;
{
  int st;
  val_curGENState (&st, cc);
  val_gen1 (bb_gen1, st);
  val_gen2 (bb_gen2, st);
  val_gen_dmu (bb_dmu, st);
}


val_cptGEN (bb_gen1, bb_gen2, bb_dmu, cc)
     int *bb_gen1, *bb_gen2, *bb_dmu, cc;
{
  int st;
  val_cptGENState (&st, cc);
  val_gen1 (bb_gen1, st);
  val_gen2 (bb_gen2, st);
  val_gen_dmu (bb_dmu, st);
}


val_mand (nm, ex, tt, cc)
     int *nm, *ex, *tt, cc;
{
  xtr_name (nm, cc);
  val_ext (ex, cc);
  val_type (tt, cc);
}


val_opt (b1, c1, b2, nn, cc)
     int *b1, *c1, *b2, *nn, cc;
{
  int bb;
  def_gen_by (&bb, cc);
  *b1 = bb;
  if (bb == TRUE) {
    val_gen_by (c1, cc);
  }
  else {
    *c1 = cc;
  }
  def_prf_level (&bb, cc);
  *b2 = bb;
  if (bb == TRUE) {
    val_prf_level (nn, cc);
  }
  else {
    *nn = 0;
  }
}


/*"
   {\bf get\_dep\_cstr}\\[.5ex]
   Load dependent constructs into {\em gset1\/}
   start by loading {\em cc\/} and {\em abs2conc\/} (if defined)
   down to {\em cc\/} into {\em gset2\/}:
"*/
void
get_dep_cstr (rep, cc)
     int *rep, cc;
{
  int rr, bb, ll, ac, cc1, bbb;
/***
printf ( "\n        get_dep_cstr       %s(%d)",GetName(cc),cc);
printf ( "\n        top_level_dep_cstr %s(%d)\n\n",GetName(top_level_dep_cstr),top_level_dep_cstr );
***/
  clear_gset1 ();
  clear_gset2 ();
  clear_gset3 ();
  modIth_flags ( get_dep_cstr_num, cc );
  add_gset2 (&rr, cc);
  if (rr == TRUE) {
    def_abs2conc (&bb, cc);
    if (bb == TRUE) {
      val_abs2conc (&ac, cc);
      length_a2c (&ll, ac);
      bb = FALSE;
      while (bb == FALSE && rr == TRUE) {
	valIth_a2c (&cc1, ac, ll);
	if (cc != cc1) {
	  member_gset2 (&bbb, cc1);
	  if (bbb == FALSE) {
	    add_gset2 (&rr, cc1);
	  }
	  ll = ll - 1;
	}
	else {
	  bb = TRUE;
	}
      }
    }
    if (rr == TRUE) {
      ll = 1;
      while (ll > 0 && rr == TRUE) {
	getnext_dep_cst (&rr);
	card_gset2 (&ll);
      }
      del_gset1 (cc);
    }
  }
/*"
   finally, deal with {\em abs2conc\/} of {\em gset3\/}:
"*/
  card_gset3 (&ll);
  while (ll != 0 && rr == TRUE) {
    valOrd_gset3 (&cc1, ll);
    add_a2cdep (&rr, cc1);
    ll = ll - 1;
  }
  *rep = rr;
}

/*"
   {\bf intr\_usr\_cstr}\\[.5ex]
   Requires no other action:
"*/
void
intr_usr_cstr (rep, cc, nm, ex)
     int *rep, *cc, *nm, ex;
{
  intr_usr_lib (rep, cc, ex, nm, usr);
}


/*"
   {\bf intr\_lib\_machine}\\[.5ex]
   Requires no other action:
"*/
void
intr_lib_machine (rep, cc, nm)
     int *rep, *cc, *nm;
{
  int rr, cc1;
  intr_usr_lib (&rr, &cc1, mch, nm, lib);
  if (rr == TRUE) {
    clear_gset1 ();
    clear_gset2 ();
    clear_gseq ();
    push_gseq (&rr, cc1);
    if (rr == TRUE) {
      analyse (&rr, cc1);
    }
  }
  *rep = rr;
  *cc = cc1;
}


void
intr_vhdl_lib_machine (rep, cc, nm)
     int *rep, *cc, *nm;
{
  int rr, cc1;
  intr_usr_lib (&rr, &cc1, mch, nm, lib_vhdl);
  if (rr == TRUE) {
    clear_gset1 ();
    clear_gset2 ();
    clear_gseq ();
    push_gseq (&rr, cc1);
    if (rr == TRUE) {
      analyse (&rr, cc1);
    }
  }
  *rep = rr;
  *cc = cc1;
}


/*"
   {\bf get\_recipt\_mchlist}\\[.5ex]
   Recursive imported {\em mch\/} list for {\em cc.imp\/} stored
   in {\em gset1\/}, duplicates in {\em gset3\/}:
"*/
void
get_recipt_mchlist (rep, cc)
     int *rep, cc;
{
  int rr, ll;
  clear_gset1 ();
  clear_gset2 ();
  clear_gset3 ();
  add_gset2 (&rr, cc);
  ll = 1;
  while (ll > 0 && rr == TRUE) {
    getnext_recipt_mchlist (&rr);
    card_gset2 (&ll);
  }
  *rep = rr;
}


/*"
   {\bf get\_recseen\_mchlist}\\[.5ex]
   Recursive seen {\em mch\/} list for {\em imp\/} {\em cc\/} stored
   in {\em gset1\/}:
"*/
void
get_recseen_mchlist (rep, cc)
     int *rep, cc;
{
  int rr, ll;
  clear_gset1 ();
  clear_gset2 ();
  add_gset2 (&rr, cc);
  ll = 1;
  while (ll > 0 && rr == TRUE) {
    getnext_recseen_mchlist (&rr);
    card_gset2 (&ll);
  }
  *rep = rr;
}



/*"
   {\bf get\_recseenipt\_mchlist}\\[.5ex]
   Recursive seen {\em ipt\/} list for {\em imp\/} {\em cc\/} stored
   in {\em gset1\/}:
"*/
get_recseenipt_mchlist (rep, cc)
     int *rep, cc;
{
  int rr, ll;
  clear_gset1 ();
  clear_gset2 ();
  add_gset2 (&rr, cc);
  ll = 1;
  while (ll > 0 && rr == TRUE) {
    getnext_recseenipt_mchlist (&rr);
    card_gset2 (&ll);
  }
  *rep = rr;
}



/*
   cc a mch - returns first imp found in which
   cc is imported (-1 if not found)
 */
void
get_higher_imp_node (cc1, cc)
     int *cc1, cc;
{
  int loc, cc2, ext, st, anl;
  int found = 0;

  first_Construct (&loc, &cc2);
  while (loc && !found) {
    val_ext (&ext, cc2);
    if (ext == imp) {
      val_curMRIState (&st, cc2);
      val_anl (&anl, st);
      if (anl) {
        member_inc_ipt (&found, cc2, cc);
        if (found) *cc1 = cc2;
      }
    }
    if (!found) {
      next_Construct (&loc, &cc2, loc, cc2);
    }
  }
  if (!found) *cc1 = -1;
}

/*
   cc a mch - returns first mch found in which
   cc is included (-1 if not found)
 */
void
get_higher_spec_node (cc1, cc)
     int *cc1, cc;
{
  int loc, cc2, ext, st, anl;
  int found = 0;

  first_Construct (&loc, &cc2);
  while (loc && !found) {
    val_ext (&ext, cc2);
    if (ext == mch) {
      val_curMRIState (&st, cc2);
      val_anl (&anl, st);
      if (anl) {
        member_inc_ipt (&found, cc2, cc);
        if (found) *cc1 = cc2;
      }
    }
    if (!found) {
      next_Construct (&loc, &cc2, loc, cc2);
    }
  }
  if (!found) *cc1 = -1;
}

/*
   loads gset1 with top imp node(s)
*/
void
load_gset1_top_imp_nodes ()
{
  int loc, cc, cc2, cc1, bb;
  int ext, st, anl, tt;

  clear_gset1 ();
  /***
  process all anl imps
  ***/
  first_Construct (&loc, &cc);
  while (loc) {
    val_ext (&ext, cc);
    if (ext == imp) {
      val_type (&tt, cc);
      if ( /* tt == usr || tt == usr_vhdl */ 1 ) {
	val_curMRIState (&st, cc);
	val_anl (&anl, st);
	if (anl) {
	  get_topabs (&cc1, cc);
	  cc2 = 0;
	  while (cc2 != -1) {
	    get_higher_imp_node (&cc2, cc1);
	    if (cc2 != -1) {
	      get_topabs (&cc1, cc2);
	    }
	  }
	  get_botref (&cc2, cc1);
	  member_gset1 (&bb, cc2);
	  if (bb == FALSE) {
	    add_gset1 (&bb, cc2);
	    chk_rep (bb, 170);
	  }
	}
      }
    }
    next_Construct (&loc, &cc, loc, cc);
  }
}

/*
   loads gset1 with top mch node(s)
*/
void
load_gset1_top_spec_nodes ()
{
  int loc, cc, cc1, cc2, bb;
  int ext, st, anl, tt;

  clear_gset1 ();
  /***
  process all anl mch
  ***/
  first_Construct (&loc, &cc);
  while (loc) {
    val_ext (&ext, cc);
    if (ext == mch) {
      val_type (&tt, cc);
      if ( /* tt == usr || tt == usr_vhdl */ 1 ) {
	val_curMRIState (&st, cc);
	val_anl (&anl, st);
	if (anl) {
	  cc1 = cc;
	  cc2 = 0;
	  while (cc2 != -1) {
	    get_higher_spec_node (&cc2, cc1);
	    if (cc2 != -1) {
	      cc1 = cc2;
	    }
	  }
	  member_gset1 (&bb, cc1);
	  if (bb == FALSE) {
	    add_gset1 (&bb, cc1);
	    chk_rep (bb, 171);
	  }
	}
      }
    }
    next_Construct (&loc, &cc, loc, cc);
  }
}

/***
void
PrintStringObj ( nn )
int nn;
{
  int i, ss, Base_Seqstr_tok;

  printf( "\n+++++++++++++++++++++++++++++++++++++++\nPrintStringObj %d:  ", nn );
  for ( i = 1 ; i <= 50 ; i++ ) {
    valIth_flags ( &Base_Seqstr_tok, Base_Seqstr_tok_num );
    valIth_seqstr ( &ss, Base_Seqstr_tok, i );
    if ( i != ss ) printf ( "i=%2d != obj=%2d ",i, ss );
  }
  printf( "\n+++++++++++++++++++++++++++++++++++++++\n" );
}
***/

void
Store_String (rep, pos, str)
     int *rep;
     int pos;
     int *str;
{
  int ss, Base_Seqstr_tok;

  valIth_flags (&Base_Seqstr_tok, Base_Seqstr_tok_num);
  valIth_seqstr (&ss, Base_Seqstr_tok, pos);
/***
{
char bbb [ 250 ];
sprintf ( bbb, "Store_String: `%s' in `%d' obj %d length %d", ( char * ) str, pos, ss, strlen ( ( char * ) str ) );
printf ( "%s\n", bbb );
}
***/
  mod_string (rep, ss, (int *) str);

/***
{
char bbb [ 250 ];
valIth_seqstr (&ss, Base_Seqstr_tok, 1);
xtr_string (bbb, ss);
printf ( "                ----->>>>> obj1 is %s\n", bbb );
}
***/
}

void
Retrieve_String (pos, str)
     int pos;
     int *str;
{
  int ss, Base_Seqstr_tok;

  valIth_flags (&Base_Seqstr_tok, Base_Seqstr_tok_num);
  valIth_seqstr (&ss, Base_Seqstr_tok, pos);
  xtr_string (str, ss);
/***
{
char bbb [ 250 ];
sprintf ( bbb, "Retrieve_String: `%s' in `%d' obj %d length %d", ( char * ) str, pos, ss, strlen ( ( char * ) str ) );
printf ( "%s\n", bbb );
}
***/
}

void
CheckAllDIRSExist ()
{
  int i;
  struct stat stat_buf;
  DIR * dp;

  for ( i = 0; i < dir_len; i++ ) {
    if ( stat ( DIRS [ i ], &stat_buf ) == -1 ) {
      sprintf ( buf, "mkdir %s", DIRS [ i ] );
      execute ( buf );
      if ( stat ( DIRS [ i ], &stat_buf ) == -1 ) {
        printf ( "\n    \"%s\" failed\n\n", buf );
        AbortedMsg ();
        Kill_bplatform_and_exit ( 0, 0 );
      }
    }
  }
  /* check all readable */
  for ( i = 0; i < dir_len; i++ ) {
    if ( ( dp = opendir ( DIRS [ i ] ) ) == NULL ) {
      printf ( "\n    \"opendir %s\" failed\n\n", DIRS [ i ] );
      AbortedMsg ();
      Kill_bplatform_and_exit ( 0, 0 );
    }
  }
}

void
LibGenConstructsHiddenDisplayMsg ( not_init_flag )
{
  void DisplayCurrWinText ();
  if ( ! not_init_flag ) {
    int tot;
    nbr_Construct ( & tot );
    if   ( tot == 1 ) sprintf ( str_buf, "\n  %d construct is configured (maximum %d)\n", tot, MAX_NUM_CONSTRUCTS);
    else              sprintf ( str_buf, "\n  %d constructs are configured (maximum %d)\n", tot, MAX_NUM_CONSTRUCTS );
    DisplayCurrWinText ( str_buf );
  }
  DisplayCurrWinText ( "\n  Library constructs are " );
  if   ( not_init_flag ) DisplayCurrWinText ( "now " );
  if   ( hid_LIB_flag ) DisplayCurrWinText ( "hidden\n" );
  else                  DisplayCurrWinText ( "displayed\n" );
  DisplayCurrWinText ( "\n  Generated constructs are " );
  if   ( not_init_flag ) DisplayCurrWinText ( "now " );
  if   ( hid_gen_flag ) DisplayCurrWinText ( "hidden\n" );
  else                  DisplayCurrWinText ( "displayed\n" );
}


/* : check whether a file exists and can be read from. I.e. can data be
   read from this file? */
int file_exists_for_read (fileName)
char * fileName;
{
   struct stat buf;
   int i = stat ( fileName, &buf );
   if ( i == 0 )
   {
     if(buf.st_mode & S_IRUSR)
     {
        if (S_ISDIR(buf.st_mode) < 1)
	{
           return 1;
	}
     }
   }
   return 0;
}
