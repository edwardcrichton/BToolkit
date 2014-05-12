/* Copyright (c) 1985-96, B-Core (UK) Ltd
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
#define print_info(ss,cc) \
  DisplayCurrWinText ( ss ); \
  DisplayCurrWinText ( GetName ( cc ) ); \
  DisplayCurrWinText ( "\n" )

/***

DesLSTBut 

  > 100
          +7026 (6216 -> 6223 = 1 3 2 4 2 -> 1 3 2 4 9)
  else
   +7415 (Tk1) BT_LST_FLG
   +3426 (Tk9) BT_LST_FLG
   +   0 (Tk7) BT_MOTIF_QUIT written out here 2400 added
   +1837 (Tk1) BT_MOTIF_QUIT
   + 563 (_io) BT_QUIT_M     written out again

           +13241 (1 -> 8 = 1 3 2 4 2 -> 1 3 2 4 9)
***/

/*
#define MALLOC_CHECK_ 2
*/

#include "BMotif_globals.h"


#ifdef COUNT_VERSION

#define COUNT_WWW

#endif /* COUNT_VERSION */


#ifdef WWW_VERSION

#define COUNT_WWW

#endif /* WWW_VERSION */


#include <Xm/XmAll.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <dirent.h>


/***
recursive contents of CfgDep_C.g
***/
/***
CfgDepBase
  (
    max_Construct,
    max_Abs2Conc,
    max_MRIState,
    max_GENState,
    EXTENSION,
    TYPE
  )
***/

#include "BMotif_BaseParameters.h"

#include "CFG_DEP_BASE/CDE/C/CfgDepBase.g"

#include "CFG_DEP_BASE/CDE/C/file_dump.g"
#include "CFG_DEP_BASE/CDE/C/CfgDepCtx.g"
#include "CFG_DEP_BASE/CDE/C/CfgDepBaseCtx.g"
#include "CFG_DEP_BASE/CDE/C/Scalar_TYPE.g"
#include "CFG_DEP_BASE/CDE/C/Bool_TYPE.g"
#include "CFG_DEP_BASE/CDE/C/String_TYPE.g"
#include "CFG_DEP_BASE/CDE/C/basic_io.g"
#include "CFG_DEP_BASE/CDE/C/CfgDepBase_file_dump.g"

#include "CFG_DEP_BASE/CDE/C/Abs2Conc_ffnc_ctx.c"
#include "CFG_DEP_BASE/CDE/C/CfgDepBase_seq_ctx.c"
#include "CFG_DEP_BASE/CDE/C/CfgDepBase_set_ctx.c"
#include "CFG_DEP_BASE/CDE/C/CfgDepBase_str_ctx.c"
#include "CFG_DEP_BASE/CDE/C/Construct_ffnc_ctx.c"
#include "CFG_DEP_BASE/CDE/C/GENState_ffnc_ctx.c"
#include "CFG_DEP_BASE/CDE/C/MRIState_ffnc_ctx.c"
#include "CFG_DEP_BASE/CDE/C/Seqstr_ffnc_ctx.c"
#include "CFG_DEP_BASE/CDE/C/String_ffnc_ctx.c"

#include "CFG_DEP_BASE/CDE/C/CfgDepCtx.h"

/*
#define Licence_Daemon_ClientPV1 { "dummy" }
#define Licence_Daemon_ClientPV2 10000
#define Licence_Daemon_ClientPV3 10000

#include "CLIENT_SERVER/CDE/C/Licence_Daemon_Client.g"

#include "CLIENT_SERVER/CDE/C/Licence_Daemon_Client.c"
*/

void
DisplayCurrWinText_Delay ( client_data )
XtPointer client_data;
{
  DisplayCurrWinText ( ( char * ) client_data );
}

int
FormulaParses ( ss ) /* No Popup_Minor_Err if error ... */
char * ss;
{
  int f;
  if ( strcmp ( ss, str_buf ) != 0 ) strcpy ( str_buf, ss );
  f = read_frmfunc_str_buf();
  if ( f != -999 ) {
    kil_from_btoolkit(f);
    return 1;
  }
  return 0;
}

int
FileParses ( file ) /* Popup_Minor_Err if error ... */
char * file;
{
  int f;
  tmp_from_btoolkit = 2;
  mod_name_fil_from_btoolkit ( file );
  f = read_file_frmfunc();
  if ( f ) {
    kil_from_btoolkit(f);
    return 1;
  }
  return 0;
}

/**************************************************
          Cfg/Dep stuff
***************************************************/


void
Get_Next_Code_Dep ()
{
  int rr, nn, cc, cc1, cc2, cc3, st, ext, bb, type, nm [ 50 ];

  valOrd_gset4 ( &cc, 1 );
/***
printf ( "Get_Next_Code_Dep for %d\n", cc );
***/
  del_gset4 ( cc );
  get_topabs ( &cc1, cc );
  get_dep_cstr ( &rr, cc1 );
  chk_rep ( rr, 54 );
  card_gset1 ( &nn );
  while ( nn ) {
    valOrd_gset1 ( &cc2, nn );
    val_ext ( &ext, cc2 );
    if ( ext == imp ) {
      val_curMRIState ( &st, cc2 );
      val_trl ( &bb, st );
      if ( bb ) {
        member_gset5 ( &bb, cc2 );
        if ( ! bb ) {
          add_gset5 ( &rr, cc2 );
          chk_rep ( rr, 55 );
          member_gset4 ( &bb, cc2 );
          if ( ! bb ) {
            add_gset4 ( &rr, cc2 );
            chk_rep ( rr, 56 );
	  }
        }
      }
    }
    else if ( ext == itf ) {
      val_curGENState( &st, cc2 );
      val_gen2 ( &bb, st );
      if ( bb ) {
        xtr_name( nm, cc2 );
        GetObjFromNameExt ( &cc2, nm, mch );
        member_gset5 ( &bb, cc2 );
        if ( ! bb ) {
          add_gset5 ( &rr, cc2 );
          chk_rep ( rr, 71 );
	}
      }
    }

    nn--;
  }

}

/***
  .obj code dependencies stored as .imp in gset5
  executables stored as .mch
***/
void
Get_Code_Dep ( cc )
int cc;
{
  int cc1, rr, nn, bb, ext, st, type, nm [ 50 ];

/***
printf ( "Get_Code_Dep ( %d )\n", cc );
***/
  clear_gset1 ();
  clear_gset2 ();
  clear_gset3 ();
  clear_gset4 ();
  clear_gset5 ();

  top_level_dep_cstr = cc;
  get_dep_cstr ( &rr, cc );
  chk_rep ( rr, 74 );
  card_gset1( &nn );
  while ( nn ) {
    valOrd_gset1( &cc1, nn );
    val_ext ( &ext, cc1 );
    if ( ext == itf ) {
      val_curGENState( &st, cc1 );
      val_gen2 ( &bb, st );
      if ( bb ) {
        xtr_name( nm, cc1 );
        GetObjFromNameExt ( &cc1, nm, mch );
        member_gset5 ( &bb, cc1 );
        if ( ! bb ) {
          add_gset5 ( &rr, cc1 );
          chk_rep ( rr, 73 );
	}
      }
    }


    nn--;
  }  
  bb = Is_LibOrEnm ( cc );
  if ( bb ) {
    member_gset4 ( &bb, cc );
    if ( ! bb ) {
      add_gset4 ( &rr, cc );
      chk_rep ( rr, 57 );
    }
  }
  else {
    val_ext ( &ext, cc );
    if ( ext == itf ) {
      val_curGENState( &st, cc );
      val_gen2 ( &bb, st );
      if ( bb ) {
        xtr_name( nm, cc );
        GetObjFromNameExt ( &cc, nm, mch );
        member_gset5 ( &bb, cc );
        if ( ! bb ) {
          add_gset5 ( &rr, cc );
          chk_rep ( rr, 72 );
	}
      }
    }

    else {
      cc1 = HasImp ( cc );
      if ( cc1 ) {  
        member_gset4 ( &bb, cc1 );
        if ( ! bb ) {
          add_gset4 ( &rr, cc1 );
          chk_rep ( rr, 52 );
	}
      }
    }
  }


  card_gset4 ( &nn );
  while ( nn ) {
    Get_Next_Code_Dep ();
    card_gset4 ( &nn );
  }
}

void
Cp_gset_gset3 ( n )
int n;
{
  int rr, ss;

  clear_gset3 ();
  if ( n == 1 ) {
    val_gset1 ( &ss );
  }
  else {
    val_gset2 ( &ss );    
  }
  mod_gset3 ( &rr, ss );
  chk_rep ( rr, 37 );
}


gset1HasGenCstr ()
{
  int nn, cc, found, type;

  found = 0;
  card_gset1 ( &nn );
  while ( ! found && nn ) {
    valOrd_gset1 ( &cc, nn );
    val_type ( &type, cc );
    if ( type == bse_gen || type == enm_gen || type == gen_vhdl ||
         type == itf_gen || type == prf_gen                        ) {
      found = 1;
    }
    nn--;
  }
  if ( found ) {
    return ( cc );
  }
  else {
    return ( 0 );
  }
}


gset1HasIftGenCstr ()
{
  int nn, cc, found, type;

  found = 0;
  card_gset1 ( &nn );
  while ( ! found && nn ) {
    valOrd_gset1 ( &cc, nn );
    val_type ( &type, cc );
    if ( type == itf_gen ) {
      found = 1;
    }
    nn--;
  }
  if ( found ) {
    return ( cc );
  }
  else {
    return ( 0 );
  }
}

int
Is_Gen_Bse ( obj )
int obj;
{
  int st, bb, ext;

  val_ext ( &ext, obj );
  if ( ext == bse ) {
    def_curGENState ( &bb, obj );
    if ( bb ) {
      val_curGENState ( &st, obj );
      val_gen1 ( &bb, st );
      return ( bb );
    }
    else {
      return ( 0 );
    }
  }
  else {
    return ( 0 );
  }
}

int
IsGen1 ( obj )
int obj;
{
  int st, bb;

  val_curGENState ( &st, obj );
  val_gen1 ( &bb, st );
  return ( bb );
}

int
IsGen2 ( obj )
int obj;
{
  int st, bb;

  val_curGENState ( &st, obj );
  val_gen2 ( &bb, st );
  return ( bb );
}

int
IsDmu ( obj )
int obj;
{
  int st, bb;

  val_curMRIState ( &st, obj );
  val_dmu ( &bb, st );
  return ( bb );
}

int
IsAnl ( obj )
int obj;
{
  int st, bb;

  val_curMRIState ( &st, obj );
  val_anl ( &bb, st );
  return ( bb );
}

int
Is_Anl_MchRefImp ( obj )
int obj;
{
  int bb;

  def_curMRIState ( &bb, obj );
  if   ( bb ) return ( IsAnl ( obj ) );
  else        return ( 0 );
}


Is_Trl ( obj )
int obj;
{
  int st, bb;

  val_curMRIState ( &st, obj );
  val_trl ( &bb, st );
  return ( bb );
}


Is_LibOrEnm ( obj )
int obj;
{
  int name [ 50 ], ext, type;

  val_mand ( name, &ext, &type, obj );
  return ( type == lib      || type == enm_gen ||
           type == gen_vhdl || type == lib_vhdl   );
}


HasImp ( obj )
int obj;
{
  int cc, ext;

  get_botref ( &cc, obj );
  val_ext ( &ext, cc );
  if ( ext == imp ) {
    return ( cc );
  }
  else {
    return ( 0 );
  }
}

CheckDuplicateIpt ( cc )
int cc;
{
  /***
  duplicates are in gset3
  ***/

  int rr, nn, cc1, cc2, ex, bb;

  get_recipt_mchlist ( &rr, cc );
  chk_rep ( rr, 96 );
  clear_gset5 ();
  card_gset1( &nn );
  while ( nn ) {
    valOrd_gset1 ( &cc1, nn );
    get_botref ( &cc2, cc1 );
    val_ext ( &ex, cc2 );
    if ( ex == imp ) {
      add_gset5 ( &rr, cc2 );
      chk_rep ( rr, 87 );
    }
    nn--;
  }
/***
printf("recursive imports (gset1):\n");
show_gset(1);
printf("recursive imports (corresponding imp) (gset5):\n");
show_gset(5);
printf("duplicate imports: (gset3)\n");
show_gset(3);
***/
/*  chk_rep ( rr, 165 ); */
  card_gset3 ( &nn );
  if ( nn ) {
   clear_gseq ();
    while ( nn ) {
      valOrd_gset3 ( &cc1, nn );
      push_gseq ( &rr, cc1 );
      chk_rep ( rr, 40 );
      nn--;
    }
    length_gseq ( &nn );
  }
  return ( nn );  
}


/***
CheckDuplicateIpt should be called first (so gset3 loaded)
***/
GetIptWithNoImp ( cc )
int cc;
{
  int rr, nn, cc1, ext, bb;

  Cp_gset_gset3 ( 1 );
  card_gset1 ( &nn );
  while ( nn ) {
    valOrd_gset1 ( &cc1, nn );
    bb = Is_LibOrEnm ( cc1 );
    if ( bb ) {
      del_gset3 ( cc1 );
    }
    else {
      bb = HasImp ( cc1 );
      if ( bb ) {
        del_gset3 ( cc1 );
      }
    }
    nn--;
  }
  card_gset3 ( &nn );
  return ( nn );
}


GetSeenWithNoImp ( cc )
int cc;
{
  int rr, nn, cc1, bb;

  get_recseen_mchlist ( &rr, cc );
  chk_rep ( rr, 35 );
  Cp_gset_gset3 ( 1 );
  card_gset1 ( &nn );
  while ( nn ) {
    valOrd_gset1 ( &cc1, nn );
    bb = Is_LibOrEnm ( cc1 );
    if ( bb ) {
      del_gset3 ( cc1);
    }
    else {
      bb = HasImp ( cc1 );
      if ( bb ) {
        del_gset3 ( cc1 );
      }
    }
    nn--;
  }
  card_gset3 ( &nn );
  return ( nn );
}

void
GetIptThroughSees ( cc )
int cc;
{
  int rr, cc2, cc3, cc4, ext, nn, mm, bb;

  get_recseenipt_mchlist( &rr, cc );
/***
printf("\nget_recseenipt_mchlist\n");
show_gset ( 1 );
***/

  get_recseen_mchlist( &rr, cc );
  clear_gset4 ();
  card_gset1 ( &nn );
  while ( nn ) {
    valOrd_gset1 ( &cc2, nn );
    member_gset4 ( &bb, cc2 );
    if ( ! bb ) {
      add_gset4 ( &rr, cc2 );
      chk_rep ( rr, 79 );
    }
    nn--;
  }
/***
printf("\nget_recseen_mchlist\n");
show_gset ( 4 );
***/

  clear_gset5 ();
  card_gset4 ( &nn );
  while ( nn ) {
    valOrd_gset4 ( &cc2, nn );
    get_botref ( &cc3, cc2 );
    val_ext ( &ext, cc3 );
    if ( ext == imp ) {
      get_recipt_mchlist ( &rr, cc3 );
      chk_rep ( rr, 80 );
      card_gset1 ( &mm );
      while ( mm ) {
        valOrd_gset1 ( &cc4, mm );
        member_gset5 ( &bb, cc4 );
        if ( ! bb ) {
          add_gset5 ( &rr, cc4 );
          chk_rep ( rr, 81 );
	}
        mm--;
      }
    }
    nn--;
  }
/***
printf("\nipt through sees\n");
show_gset ( 5 );
***/
}

GetSeenNotIpt ( cc )
int cc;
{
  int rr, nn, cc1, bb;

  get_recipt_mchlist ( &rr, cc );
/***
printf("get_recipt_mchlist for %d in gset1\n",cc);
show_gset(1);
***/
  chk_rep ( rr, 43 );
/***
printf("copied to gset3\n");
show_gset(3);
***/
  Cp_gset_gset3 ( 1 );
  get_recseen_mchlist ( &rr, cc );
/***
printf("get_recseen_mchlist for %d in gset1\n",cc);
show_gset(1);
***/
  chk_rep ( rr, 166 );
  clear_gset2 ();
  card_gset1 ( &nn );
  while ( nn ) {
    valOrd_gset1 ( &cc1, nn );
    member_gset3 ( &bb, cc1 );
    if ( ! bb ) {
      member_gset2 ( &bb, cc1 );
      if ( ! bb ) {
        add_gset2 ( &rr, cc1 );
      }
      chk_rep ( rr, 45 );
    }    
    nn--;
  }
/***
printf("resulting gset2\n",cc);
show_gset(2);
***/
  card_gset2 ( &nn );
  return ( nn );  
}

GetLinkList ( cc )
int cc;
{
  int rr, nn, cc1, bb;

  get_recseenipt_mchlist ( &rr, cc );
  chk_rep ( rr, 44 );
  card_gset1 ( &nn );
  return ( nn );  
}

void
OpenGlobalPMD () /* primary_string set */
{
  FILE * gpmd;
  struct stat pmd;
  char* editorCommand;
  
  if ( stat ( primary_string, &pmd ) != 0 ) {
    strcpy ( buf, "\"" );
    strcat ( buf, primary_string );
    strcat ( buf, "\" does not exist" );
    if ( ( curr_env ==  ipr_pob_env ) || ( curr_env ==  ipr_lem_env ) )
      Ipr_Sel_Ops ( top_level, Ipr_Prf_Option, 0 );
    Popup_Minor_Err ( NULL, buf );
  }
  else {
    gpmd = fopen ( primary_string, "r" );
    if ( gpmd == NULL ) {
      strcpy ( buf, "Can't open \"" );
      strcat ( buf, primary_string );
      strcat ( buf, "\" for reading" );
      if ( ( curr_env ==  ipr_pob_env ) || ( curr_env ==  ipr_lem_env ) )
        Ipr_Sel_Ops ( top_level, Ipr_Prf_Option, 0 );
      Popup_Minor_Err ( NULL, buf );
    }
    else {
      int i, j;
      fclose ( gpmd );
      Retrieve_String ( pmd_editor_str_num, fifo_write_buf );
      
      /* - use more intelligent command line caller for editors: */
       /*
       strcat ( fifo_write_buf, " " );
       strcat ( fifo_write_buf, primary_string );
       strcat ( fifo_write_buf, " & \n echo $! > .Bed" );
       execute ( fifo_write_buf );
       */
  
      editorCommand=getEditorCommandLine(fifo_write_buf,primary_string);
      strcpy(fifo_write_buf, editorCommand);
      free(editorCommand);
      strcat ( fifo_write_buf, " & \n echo $! > .Bed" );
      execute ( fifo_write_buf );
     
      if ( curr_env != provers_env ) dont_destroy_display = 1; /* ipr */
      i = strlen ( primary_string );
      while ( i && ( primary_string [ i ] != '/' ) ) { i--; }
      j = 0;
      if ( i && ( primary_string [ i ] != '\0' ) ) {
        i++;
        while ( primary_string [ i ] != '\0' ) {
          primary_string [ j++ ] = primary_string [ i++ ];
        }
        primary_string [ j ] = '\0';
      }
      ModifyGlobalPMDOpenFromBed ();
      Popup_ClosePMDFile ( top_level, 0 );
    }
  }
}

void
OpenCurrentPMD ( cc ) /* from Popup_Sel_Dialog_CB &
                         Popup_RadioBox_Dialog_CB - edit_pmd_radiobox */
int cc;
{
  int st, level;  
  FILE * gpmd;
  struct stat pmd;
  char* editorCommand;
  char buf[250];

  val_curMRIState( &st, cc );
  length_pob( &level, st );
  sprintf ( primary_string, "%s.%d.pmd", GetName ( cc ), level - 1 ); 

  sprintf ( fifo_write_buf, "PMD/%s", primary_string );

  if ( stat ( fifo_write_buf, &pmd ) != 0 ) {
    sprintf ( buf, "\"%s\" does not exist", fifo_write_buf );
    if ( ( curr_env ==  ipr_pob_env ) || ( curr_env ==  ipr_lem_env ) ) {
      Ipr_Sel_Ops ( top_level, Ipr_Prf_Option, 0 );
    }
    else {
      DisplayChanged = 1;
    }
    Popup_Minor_Err ( NULL, buf );
  }
  else {
    gpmd = fopen ( fifo_write_buf, "r" );
    if ( gpmd == NULL ) {
      strcpy ( buf, "Can't open \"" );
      strcat ( buf, fifo_write_buf );
      strcat ( buf, "\" for reading" );
      if ( ( curr_env ==  ipr_pob_env ) || ( curr_env ==  ipr_lem_env ) ) {
        Ipr_Sel_Ops ( top_level, Ipr_Prf_Option, 0 );
      }
      else {
        DisplayChanged = 1;
      }
      Popup_Minor_Err ( NULL, buf );
    }
    else {
      fclose ( gpmd );
      Retrieve_String ( pmd_editor_str_num, fifo_write_buf );
      
      /* - use more intelligent command line caller for editors: */
      /*
      strcat ( fifo_write_buf, " PMD/" );
      strcat ( fifo_write_buf, primary_string );
      strcat ( fifo_write_buf, " & \n echo $! > .Bed" );
      execute ( fifo_write_buf );
      */
  
      strcpy(buf,"PMD/");
      strcat(buf,primary_string);
  
      editorCommand=getEditorCommandLine(fifo_write_buf,buf);
      strcpy(fifo_write_buf, editorCommand);
      free(editorCommand);
      strcat ( fifo_write_buf, " & \n echo $! > .Bed" );
      execute ( fifo_write_buf );
      

      if ( curr_env != provers_env ) dont_destroy_display = 1; /* ipr */
      ModifyCurrentPMDOpenFromBed ();
      Popup_ClosePMDFile ( top_level, 0 );
    }
  }
}

void
SourceControlBscSyntaxError ()
{
  DisplayCurrWinText ( "\n  $HOME/.Bhtx syntax error\n" );
  DisplayCurrWinText ( "\n  The file should comprise a list of triples,\n" );
  DisplayCurrWinText ( "  each item appearing on a separate line:\n\n" );
  DisplayCurrWinText ( "    the first of each triple is the button name\n" );
  DisplayCurrWinText ( "    the second is the button action\n" );
  DisplayCurrWinText ( "    the third is one of the attributes:\n" );
  DisplayCurrWinText ( "      CHECKED_OUT CHECKED_IN or UNCHANGED\n" );
  DisplayCurrWinText ( "\n  See TopBar Help for Source Control\n" );
  Popup_Minor_Err ( NULL, "$HOME/.Bhtx syntax error" );
}

int
CheckSourceControlFromBsc ( init_flag )
int init_flag;
{
  char *getenv(), *name;
  FILE * Bsc;
  FILE * Bcom;
  int i, c;
  int no_entries;

  name = getenv ( "HOME" );
  if ( name == NULL ) {
    if ( ! init_flag ) {
      Popup_Info ( " Environment variable HOME not set " );
      DisplayCurrWinText ( "\n  Environment variable HOME not set\n" );
    }
    return ( 0 );
  }

  sprintf ( buf, "%s/.Bsc", name );
  Bsc = fopen ( buf, "r" );
  if ( Bsc == NULL ) {
    if ( ! init_flag ) {
      sprintf ( str_buf, "BMotif: can't open %s", buf );
      Popup_Info ( str_buf );
      DisplayCurrWinText ( "\n  BMotif: can't open " );
      DisplayCurrWinText ( buf );
      DisplayCurrWinText ( " for reading\n" );
    }
    return ( 0 );
  }

  Bcom = fopen ( "TMP/.Bcom", "w" );
  if ( Bcom == NULL ) {
    fclose ( Bsc );
    if ( ! init_flag ) {
      Popup_Info ( "BMotif: can't open TMP/.Bcom" );
      DisplayCurrWinText ( "\n  BMotif: can't open " );
      DisplayCurrWinText ( "TMP/.Bcom" );
      DisplayCurrWinText ( " for writing\n" );
    }
    return ( 0 );
  }
  no_entries = 1;
  c = getc ( Bsc );
  while ( c != EOF ) {
    /* read to first non-ws */
    while ( ( c == ' ' ) || ( c == '\t' ) || ( c == '\n' ) ) {
      c = getc ( Bsc );
    }
    /* swallow empty lines */
    while ( c == '\n' ) {
      c = getc ( Bsc );
    }
    /* line into Bcom */
    i = 0;
    while ( ( c != EOF ) && ( c != '\n' ) ) {
      buf [ i++ ] = c;
      if ( c == '\"' ) putc ( '\\', Bcom );
      putc ( c, Bcom );
      c = getc ( Bsc );
    }
    buf [ i ] = '\0';
    if ( ( ( ( no_entries - 1 ) / 3 ) * 3 ) == ( no_entries - 1 ) ) {
      if ( ( int ) strlen ( buf ) > SC_BUT_NAME_MAX ) {
        fclose ( Bsc );
        fclose ( Bcom );
        if ( ! init_flag ) {
          sprintf ( buf, "\n  Maximum length for button name is %d\n",
                                                            SC_BUT_NAME_MAX );
          DisplayCurrWinText ( buf );
          DisplayCurrWinText ( "\n  See TopBar Help for Source Control\n" );
          Popup_Minor_Err ( NULL, "$HOME/.Bhtx syntax error" );
	}
        return ( 0 );
        break;
      }
    }
    if ( ( ( ( no_entries - 2 ) / 3 ) * 3 ) == ( no_entries - 2 ) ) {
      if ( ( int ) strlen ( buf ) > SC_BUT_ACT_MAX ) {
        fclose ( Bsc );
        fclose ( Bcom );
        if ( ! init_flag ) {
          sprintf ( buf, "\n  Maximum length for button action is %d\n",
                                                            SC_BUT_ACT_MAX );
          DisplayCurrWinText ( buf );
          DisplayCurrWinText ( "\n  (you may define a program to execute instead)\n" );
          DisplayCurrWinText ( "\n  See TopBar Help for Source Control\n" );
          Popup_Minor_Err ( NULL, "$HOME/.Bhtx syntax error" );
	}
        return ( 0 );
        break;
      }
    }
    if ( ( ( no_entries / 3 ) * 3 ) == no_entries ) {
      if ( ( strcmp ( buf, "CHECKED_OUT" ) != 0 ) &&
           ( strcmp ( buf, "CHECKED_IN" )  != 0 ) &&
           ( strcmp ( buf, "UNCHANGED" )   != 0 )    ) {
        fclose ( Bsc );
        fclose ( Bcom );
        if ( ! init_flag ) SourceControlBscSyntaxError ();
        return ( 0 );
        break;
      }
    }
    putc ( '\n', Bcom );
    no_entries++; 
    /* read to first non-ws */
    while ( ( c == ' ' ) || ( c == '\t' ) || ( c == '\n' ) ) {
      c = getc ( Bsc );
    }
   }

  fclose ( Bsc );
  fclose ( Bcom );

  no_entries--;
 
/***
printf ( "no_entries = %d\n-----------\n", no_entries );
system ( "cat TMP/.Bcom" );
printf ( "-----------\n" );
***/

  if ( ( ( no_entries / 3 ) * 3 ) != no_entries ) {
    if ( ! init_flag ) SourceControlBscSyntaxError ();
    return ( 0 );
  }

  return ( no_entries / 3 );

}

int
InstallSourceControlFromBsc ( init_flag )
int init_flag;
{
  FILE * Bcom;
  struct SourceControlStruct * SC_1;
  void Cre_SourceControl_Dialog ();

  int c, n, i;
  int num_but = CheckSourceControlFromBsc ( init_flag );

  if ( ! num_but ) return ( 0 );

  if ( SourceControl_Initialised ) {
    free ( SC_0 );
    XtDestroyWidget ( SC_dialog );
    SC_dialog = ( Widget ) NULL;
  }
  SC_0 = ( struct SourceControlStruct * ) malloc
                     ( num_but * sizeof ( struct SourceControlStruct) );

  Bcom = fopen ( "TMP/.Bcom", "r" );
  if ( Bcom == NULL ) {
    AbortedMsgFile ( "\"TMP/.Bcom\" for reading" );
    BT_err_exit ( 0 );
    return ( 0 );
  }

  SC_1 = SC_0;
  n = 0;
  c = getc ( Bcom );
  while ( ( c != EOF ) && ( n < num_but ) ) {
    i = 0;
    while ( ( c != EOF ) && ( c != '\n' ) ) {
      ( SC_1 -> but_name ) [ i++ ] = c;
      c = getc ( Bcom );
    }
    ( SC_1 -> but_name ) [ i ] = '\0';
/***
printf ( "  1: `%s'\n", SC_1 -> but_name );
***/
    i = 0;
    if ( c == '\n' ) c = getc ( Bcom );
    while ( ( c != EOF ) && ( c != '\n' ) ) {
      ( SC_1 -> but_act ) [ i++ ] = c;
      c = getc ( Bcom );
    }
    ( SC_1 -> but_act ) [ i ] = '\0';
/***
printf ( "  2: `%s'\n", SC_1 -> but_act );
***/
    i = 0;
    if ( c == '\n' ) c = getc ( Bcom );
    while ( ( c != EOF ) && ( c != '\n' ) ) {
      buf [ i++ ] = c;
      c = getc ( Bcom );
    }
    buf [ i ] = '\0';
    if ( ( strcmp ( buf, "CHECKED_OUT" ) == 0 ) )
      ( SC_1 -> type ) = SC_CHECKED_OUT;
    else if ( ( strcmp ( buf, "CHECKED_IN" ) == 0 ) )
      ( SC_1 -> type ) = SC_CHECKED_IN;
    else
      ( SC_1 -> type ) = SC_UNCHANGED;
    if ( c == '\n' ) c = getc ( Bcom );
/***
printf ( "  3:  %d\n", SC_1 -> type );
***/
    n++;
    SC_1++;
  }

  fclose ( Bcom );

/***
SC_1 = SC_0;
printf ( "----------------------\n" );
for ( i = 0 ; i < num_but ; i++ ) {
  printf ( "%d:\n  but_name `%s'\n  but_act  `%s'\n    type %d\n",
                              i, SC_1 -> but_name, SC_1 -> but_act, SC_1 -> type );
  SC_1++;
}
printf ( "\n----------------------\n" );
***/

 Cre_SourceControl_Dialog ( /* create_flag = */ 1, num_but );

  SourceControl_Initialised = 1;
  return ( 1 );
}

void
DisplayBrowsePMD ( pmd_file )
char * pmd_file;
{
  FILE * Bpmd;
  struct stat statBpmd;
  struct help_struct help_data;
  char * text;

  /***
  get contents
  ***/
  if ( ( stat ( pmd_file, &statBpmd ) ) != 0 ) {
    perror( pmd_file );
    sprintf ( buf, "%s does not exist", pmd_file );
    Popup_Info ( buf );
    return;
  }

  Bpmd = fopen ( pmd_file, "r" );
  if ( Bpmd == NULL ) {
    perror( pmd_file );
    sprintf ( buf, "Can't open %s for reading", pmd_file );
    Popup_Info ( buf );
    return;
  }

  if ( ! ( text = XtMalloc ( ( unsigned ) statBpmd.st_size + 1 ) ) ) {
    fprintf ( stderr, "\n Can't allocate enough space for %s\n",
        pmd_file );
    return;
  }
  if ( ! fread ( text, sizeof ( char ), statBpmd.st_size + 1, Bpmd ) ) {
    fprintf ( stderr, "\n May not have read the entire file!\n" );
  }
  text [ statBpmd.st_size ] = 0;
  fclose ( Bpmd );

  /***
  set help data and call Popup_Help_CB 
  ***/
  help_data.type = PALETTE_HELP;
  help_data.text = ( char * ) text;
  help_data.width  = 425 /* 310 */ ;
  help_data.height = 503;

  Popup_Help_CB ( top_level, ( XtPointer ) & help_data );

  /***
  free allocated memory
  ***/
  XtFree ( text );
}

void
GetAllLevelPMD ( cc )
int cc;
{
  int anl, dmu, trl, lnk, lenpob, fpob, ppob, lpob, level;

  val_curMRI ( &anl, &dmu, &trl, &lnk, &lenpob, &fpob, &ppob, &lpob, cc );
  lpob = correct_pob_for_btl ( lpob );
  if ( ! lpob ) lenpob--; /* if all pobs discharged, don't provide current level */

  sel_arr_tot = 0;
  level = 0;
  while ( level < lenpob ) {
    sprintf ( sel_str_arr [ sel_arr_tot++ ], "%s.%d.pmd",
                                                       GetName ( cc ), level );
    sprintf ( sel_str_arr [ sel_arr_tot++ ], "%s.%d.btl.pmd",
                                                       GetName ( cc ), level );
    level++;
  }
}

void
UpdateFromSRC ()
{
  void LoadSRCEditedNewInto_sel_strs ();
  LoadSRCEditedNewInto_sel_strs ( 1 ); /* 1 => edited */
  if ( sel_arr_tot ) {
    Popup_Sel_flag = update_from_SRC_sel;
    Popup_Sel_Dialog ( top_level, "Select Constructs to Update from SRC" );
  }
  else {
    Popup_Info ( "No updated constructs" );
  }
}

void
ProcessUpdateFromSRC_Next ()
{
  int nn;
  void LoadSRCEditedInto_sel_strs ();
  
  length_gseq ( &nn );
/***
printf ( "ProcessUpdateFromSRC_Next () - %d in length_gseq\n", nn );
***/
  if ( nn ) {
    valIth_gseq ( &curr_obj, 1 );
    strcpy ( primary_string, GetName ( curr_obj ) );
    radiobox_flag = update_from_src_radiobox;
    Popup_UpdateFileFromSRC ( top_level );
  }
  else {
    DisplayCurrentEnv ();
  }
}

void
OPN_CLO ( obj, ps )
int obj, ps;
{
  if   ( ps )
  {
  	printf("Check_QuitEditor_Popup( %d ) ps = %d\n",obj,ps);
  	Check_QuitEditor_Popup ( obj );
  }
  else
  {
  	printf("PreOpenConstruct( %d )\n",obj);
          PreOpenConstruct ( obj );
  }
}

void
CMT ( obj )
int obj;
{
  if (  FileDiffIntoBcom ( obj ) ) {
    radiobox_flag = commit_but_radiobox;
    CheckFileParses ( obj );
  }
  else {
    Popup_Info ( "  No edits saved!  " );  /* shouldn't be needed */
  }
}

void
ANL ( obj, ps )
int obj, ps;
{
  unlink ( ".Brec" );
  Cre_fifo_write_buf_cmd_env ( obj, BT_NML_WITH_ENV, 0 );
  if ( ps ) {
    int file_diff = FileDiffIntoBcom ( obj );
    if ( file_diff ) {
      int maths_change, no_comment_src, no_comment_cfg; 
      Load_SRC_CFG_Names ( obj );
      DeCommentFile ( SRCName, ".Bcom", &no_comment_src );
      DeCommentFile ( CFGName, ".BBcom", &no_comment_cfg );
      maths_change = FileDifference (  ".Bcom", ".BBcom" );
      if ( maths_change ) {
        DisplayCurrWinText ( "\n  Maths change in edited file\n" );
      }
      else {
        DisplayCurrWinText ( "\n  Annotation change in edited file\n" );
      }
      strcpy ( primary_string, GetName ( obj ) );
      radiobox_flag = file_ed_NML_radiobox;
      curr_obj = obj;
      Popup_Edt_Proceed ( top_level );
    }
    else { /* if ( file_diff ) */
     strcpy ( xterm_title, "B-Analyser" );
     InvokeB ( with_XTerm, 1 );
    }
  }
  else { /* if ( ps )  */
    strcpy ( xterm_title, "B-Analyser" );
    curr_obj = obj;
    InvokeB ( with_XTerm, 1 );
  }
}

void
POG ( obj, ps )
int obj, ps;
{
  Cre_fifo_write_buf_cmd_env ( obj, BT_POG_WITH_ENV, 0 );
  if (  ps ) {
    int file_diff = FileDiffIntoBcom ( obj );
    if ( file_diff ) {
      int maths_change, no_comment_src, no_comment_cfg; 
      Load_SRC_CFG_Names ( obj );
      DeCommentFile ( SRCName, ".Bcom", &no_comment_src );
      DeCommentFile ( CFGName, ".BBcom", &no_comment_cfg );
      maths_change = FileDifference (  ".Bcom", ".BBcom" );
      if ( maths_change ) {
        DisplayCurrWinText ( "\n  Maths change in edited file\n" );
      }
      else {
        DisplayCurrWinText ( "\n  Annotation change in edited file\n" );
      }
      strcpy ( primary_string, GetName ( obj ) );
      radiobox_flag = file_ed_POG_radiobox;
      curr_obj = obj;
      Popup_Edt_Proceed ( top_level );
    }
    else {
      strcpy ( xterm_title, "B-POGenerator" );
      curr_obj = obj;
      InvokeB ( with_XTerm, 1 );
    }
  }
  else {
    strcpy ( xterm_title, "B-POGenerator" );
    curr_obj = obj;
    InvokeB ( with_XTerm, 1 );
  }
}

void
ANM ( obj )
int obj;
{
  void Popup_MainAnimatorMenu ();
  Popup_MainAnimatorMenu ( obj );
}

void
Pre_Animate ( flag )
int flag;
{
  /***
  flag = 1 => Interactive
  flag = 2 => Replay - step        additional_string contains the ANIMATE file
  flag = 3 => Replay - automatic   additional_string contains the ANIMATE file
  ***/

  int nn, cc, i, j;
  struct stat stat_buf;
  void DisplayNewEnv ();

  if ( flag != 1 ) {
    if ( stat ( additional_string, &stat_buf ) == -1 ) {
      sprintf ( fifo_write_buf, "%s does not exist", additional_string );
      Popup_Minor_Err ( NULL, fifo_write_buf );
      return;
    }
    if ( ! ( FileParses ( additional_string ) ) ) {
      sprintf ( fifo_write_buf, "%s does not parse", additional_string );
      Popup_Minor_Err ( NULL, fifo_write_buf );
      return;
    }
  }

  sprintf ( fifo_write_buf, "(%s|?", GetName ( curr_obj ) );
  card_sees_uses ( &nn, curr_obj );
  while ( nn ) {
    valOrd_sees_uses ( &cc, curr_obj, nn );
    strcat ( fifo_write_buf, "," );
    strcat ( fifo_write_buf, GetName ( cc ) );
    nn--;
  }
  strcat ( fifo_write_buf, "|" );
  CreNumInBuf ( fifo_write_buf, anm_invariant_flag );

  if ( flag != 1 ) {
    /***
    additional_string of form SRC/aaa.ident.anm
    recover ident in buf
    ***/
    i = 0;
    while ( additional_string [ i ] != '.' ) { i++; }
    i++;
    j = 0;
    while ( additional_string [ i ] != '.' ) {
      buf [ j++ ] = additional_string [ i++ ];
    }
    buf [ j ] = '\0';
  }

  switch ( flag ) {
  case 1:
    strcat ( fifo_write_buf, "):" );
    CreNumInBuf ( fifo_write_buf, BT_ANM_WITH_ENV );
    strcpy ( xterm_title, "B-Animator-Interactive-State-Window" );
    DisplayNewEnv ( anm_env );
    break;
  case 2:
    strcat ( fifo_write_buf, "|\"" );
    strcat ( fifo_write_buf, additional_string );
    strcat ( fifo_write_buf, "\"|" );
    strcat ( fifo_write_buf, buf );
    strcat ( fifo_write_buf, "):" );
    CreNumInBuf ( fifo_write_buf, BT_ANM_EXE_STEP_WITH_ENV );
    DisplayNewEnv ( anm_env );
    strcpy ( xterm_title, "B-Animator-Execute-Step" );
    break;
  case 3:
    strcat ( fifo_write_buf, "|\"" );
    strcat ( fifo_write_buf, additional_string );
    strcat ( fifo_write_buf, "\"|" );
    strcat ( fifo_write_buf, buf );
    strcat ( fifo_write_buf, "):" );
    CreNumInBuf ( fifo_write_buf, BT_ANM_EXE_AUTO_WITH_ENV );
    strcpy ( xterm_title, "B-Animator-Execute-Auto" );
    break;
  } /* switch ( flag ) */
  Cre_tcp_env ();
  InvokeB ( with_XTerm, 1 );
}

void
STS ( obj )
int obj;
{
  MainWinDisp_status ( obj );
}

void
RST ( obj )
int obj;
{
  /***
  PreResetConstruct or equivalent is called
  first to load gsets with dependents
  ***/

  int rr, mm, nn, tt;

  DeSensitize ();
  Load_SRC_CFG_Names ( obj );
  top_level_dep_cstr = obj;
  Get_Code_Dep ( obj );
  card_gset5 ( &mm );
  top_level_dep_cstr = obj;
  get_dep_cstr ( &rr, obj );
  chk_rep ( rr, 67 );
  card_gset1 ( &nn );
  if ( nn == 0 && mm == 0 ) {
    ResetConstruct ( obj, 0 );
  }
  else {
    val_type ( &tt, obj );
    DisplayCurrWinText ( "\n\n    Dependent constructs:\n" );
    MainWinDisp_gset ( 1 );
    MainWinDispCode_gset ( 5 );
    if ( tt == lib || tt == enm_gen ) {
      sprintf ( buf, "      %s.o\n", GetShortName ( obj ) );
      DisplayCurrWinText ( buf );
    }
    sprintf ( primary_string, "Proceed with %s reset?", GetName ( obj ) );
    strcpy ( secondary_string,
                  "Dependent construct processing will be lost" );
    confirm_flag = rst_cst_but_radiobox;
    curr_obj = obj;
    Popup_ConfirmDialog ( top_level );
  }
}

void
PRV ( obj )
int obj;
{
  Popup_ThreeProvers ( obj );
}

void
PMD ( obj )
int obj;
{
  Popup_EditPmd ( obj );
}

void
PPF ( obj )
int obj;
{
  int st, su, pob_length, ppf_card, lvl, bb, nn,
      c_tot, p_tot, c_pob, p_pob;

  /*** see BMotif.c - look for ( a   b   c ) ***/

  sel_arr_tot = 0;
  val_curMRIState ( &st, obj );
  val_cptMRIState ( &su, obj );
  length_pob ( &pob_length, st );
/***
printf("pob_length: %d\n",pob_length);
***/
  if ( pob_length ) { 
    card_ppf ( &ppf_card, st );
/***
printf("ppf_card: %d\n",ppf_card);
***/
    if ( pob_length > ppf_card ) {
      lvl = 0;
      while ( lvl < pob_length ) {
        member_ppf ( &bb, st, lvl );
        if ( ! bb ) {
          sprintf ( sel_str_arr [ sel_arr_tot ], "%s -", GetName ( obj ) );
          if ( ! lvl ) {
            valIth_pob ( &nn, st, 1 );
            nn = correct_pob_for_btl ( nn );
            CreNumInBuf ( sel_str_arr [ sel_arr_tot ], nn );
            if ( nn == 1 ) {
              strcat ( sel_str_arr [ sel_arr_tot ], " proof obligation" );
	    }
            else {
              strcat ( sel_str_arr [ sel_arr_tot ], " proof obligations" );
	    }
            sel_obj_arr [ sel_arr_tot ] = ((1000000*lvl)+nn);
            sel_arr_tot++;
	  }
          else {
            strcat ( sel_str_arr [ sel_arr_tot ], " Level " );
            CreNumInBuf ( sel_str_arr [ sel_arr_tot ], lvl - 1 );
            strcat ( sel_str_arr [ sel_arr_tot ], ": " );

            valIth_pob( &c_tot, su, lvl + 1 );
            valIth_pob( &p_tot, su, lvl );
            valIth_pob( &c_pob, st, lvl + 1 );
            valIth_pob( &p_pob, st, lvl );
            c_tot = correct_pob_for_btl ( c_tot );
            p_tot = correct_pob_for_btl ( p_tot );
            c_pob = correct_pob_for_btl ( c_pob );
            p_pob = correct_pob_for_btl ( p_pob );
            if ( c_tot-p_tot+p_pob-c_pob != 0 ) {
              CreNumInBuf ( sel_str_arr [ sel_arr_tot ], c_tot-p_tot+p_pob-c_pob );
              if ( c_tot-p_tot+p_pob-c_pob == 1 ) {
                strcat ( sel_str_arr [ sel_arr_tot ], " proof" );
	      }
              else {
                strcat ( sel_str_arr [ sel_arr_tot ], " proofs" );
	      }
              sel_obj_arr [ sel_arr_tot ] = ((1000000*lvl)+c_tot-p_tot+p_pob-c_pob);
              sel_arr_tot++;
	    }
	  }
	}
        lvl++;
      }
    }
  }
  if ( sel_arr_tot ) {
    Popup_Sel_flag = ppf_selection;
    curr_obj = obj;
    Popup_SelOne_Dialog ( top_level, "Print proof construct" );
  }
  else {
    Popup_Info ( "No proofs to print!  " ); /* this shoudn't be needed */
  }
}

/*
void
RSL ( obj )
int obj;
{
  sprintf ( primary_string, "   \nProof levels are completely removed, and so ALL\nproofs will be lost (especially BToolProver proofs!)\n\nRemake will rebuild only to level selected\n\nAre you sure you want to revert to a previous  proof level?\n" );
  strcpy ( secondary_string,
                  "You may remove proofs by:\nTopBar->Construct->Remove All Proofs\nwhen Remake WILL rebuild to the current proof level" );
  confirm_flag = rsl_selection_confirm;
  curr_obj = obj;
  Popup_ConfirmDialog ( top_level );
}

RSL_confirmed ( obj )
{
  int lenpob, cur_lev, st, cur_pob, anl, dmu, trl, lnk, fpob, ppob, lpob;

  val_curMRI ( &anl, &dmu, &trl, &lnk, &lenpob, &fpob, &ppob, &lpob, obj );
  lpob = correct_pob_for_btl ( lpob );
  val_curMRIState( &st, obj );

  sel_arr_tot = 0;
  cur_lev = 1;
  while ( cur_lev < lenpob ) {
    valIth_pob( &cur_pob, st, cur_lev );
    cur_pob = correct_pob_for_btl ( cur_pob );
    if ( cur_lev == 1 )
      sprintf ( sel_str_arr [ sel_arr_tot ], "Level %d (%d proof obligations)",
                                                              cur_lev - 1, cur_pob );
    else
      sprintf ( sel_str_arr [ sel_arr_tot ], "Level %d (%d unproved)",
                                                              cur_lev - 1, cur_pob );
    cur_lev++;
    sel_arr_tot++;  
  }
  Popup_Sel_flag = rsl_selection;
  curr_obj = obj;
  Popup_SelOne_Dialog ( top_level, "Revert to Previous Proof Level" );
}
*/

RSL ( obj )
{
  int lenpob, cur_lev, st, cur_pob, anl, dmu, trl, lnk, fpob, ppob, lpob;

  val_curMRI ( &anl, &dmu, &trl, &lnk, &lenpob, &fpob, &ppob, &lpob, obj );
  lpob = correct_pob_for_btl ( lpob );
  val_curMRIState( &st, obj );

  sel_arr_tot = 0;
  cur_lev = 1;
  while ( cur_lev < lenpob ) {
    valIth_pob( &cur_pob, st, cur_lev );
    cur_pob = correct_pob_for_btl ( cur_pob );
    if ( cur_lev == 1 )
      sprintf ( sel_str_arr [ sel_arr_tot ], "Level %d (%d proof obligations)",
                                                              cur_lev - 1, cur_pob );
    else
      sprintf ( sel_str_arr [ sel_arr_tot ], "Level %d (%d unproved)",
                                                              cur_lev - 1, cur_pob );
    cur_lev++;
    sel_arr_tot++;  
  }
  Popup_Sel_flag = rsl_selection;
  curr_obj = obj;
  Popup_SelOne_Dialog ( top_level, "Revert to Previous Proof Level" );
}


void
LVL ( obj )
int obj;
{
  int i, st, su, c_tot, p_tot, c_pob, p_pob, btl_prf, lenpob;
  val_curMRIState( &st, obj );
  val_cptMRIState( &su, obj );
  length_pob ( &lenpob, st );
  sprintf ( buf, "\n  Summary of Proof Level(s) for %s:\n\n  lvl   tot   pob\n\n",
                                                                   GetName ( obj ) );
  DisplayCurrWinText ( buf );

  /***
  len cpt >= len cur

  cpt: 3   3  -4
  cur: 3
    3 pobs generated, but no proof yet (1st entries always positive)

  cpt: 3   3  -4  ( a   b   c )
  cur: 3   2      ( d   e     )
    b positive => AutoProof level 1:
        1 proved (= |b| - |a| + |d| - |e| = 3 - 3 + 3 - 2)

  cpt: 3   3  -6  ( a   b   c )
  cur: 3   2  -4  ( d   e   f )
    c negative => BToolProof level 2:
        1 proved (= |c| - |b| + |e| - |f| = 6 - 3 + 2 - 4)
        3 lemmas (= |c| - |b| = 6 - 3)
  ***/

  for ( i = 1 ; i <= lenpob - 1 ; i++ ) {
    valIth_pob( &c_tot, su, i + 1 );
    valIth_pob( &p_tot, su, i );
    valIth_pob( &c_pob, st, i + 1 );
    valIth_pob( &p_pob, st, i );

    btl_prf = ( ( c_tot < 0 ) != 0 );

    c_tot = correct_pob_for_btl ( c_tot );
    p_tot = correct_pob_for_btl ( p_tot );
    c_pob = correct_pob_for_btl ( c_pob );
    p_pob = correct_pob_for_btl ( p_pob );

    if ( btl_prf ) {
      if ( c_tot - p_tot == 1 ) {
        sprintf ( buf, "%5d%6d%6d (BToolProver:%3d) (created %2d lemma)\n", i - 1, c_tot, c_pob, c_tot-p_tot+p_pob-c_pob, c_tot-p_tot );
      }
      else if ( c_tot - p_tot ) {
        sprintf ( buf, "%5d%6d%6d (BToolProver:%3d) (create %2d lemmas)\n", i - 1, c_tot, c_pob, c_tot-p_tot+p_pob-c_pob, c_tot-p_tot );
      }
      else {
        sprintf ( buf, "%5d%6d%6d (BToolProver:%3d)\n", i - 1, c_tot, c_pob, c_tot-p_tot+p_pob-c_pob );
      }
    }
    else {
      sprintf ( buf, "%5d%6d%6d (AutoProver: %3d)\n", i - 1, c_tot, c_pob, c_tot-p_tot+p_pob-c_pob );
    }
    DisplayCurrWinText ( buf );
  }
  if ( lenpob ) {
    valIth_pob( &c_tot, su, lenpob );
    valIth_pob( &c_pob, st, lenpob );
    c_tot = correct_pob_for_btl ( c_tot );
    c_pob = correct_pob_for_btl ( c_pob );
    sprintf ( buf, "%5d%6d\n", lenpob - 1, c_tot );
    DisplayCurrWinText ( buf );
    if ( c_pob ) {
      sprintf ( buf, " \n  Current Level %d, %d/%d undischarged:\n", lenpob - 1, c_pob, c_tot );
      DisplayCurrWinText ( buf );
      sprintf ( fifo_write_buf, "%s.%d:0", GetName ( obj ), lenpob - 1 ); 
      Cre_fifo_write_buf_cmd_0 ( BT_PUP );
      InvokeB ( without_XTerm, 1 );
    }
    else {
      if ( lenpob == 1 ) 
        sprintf ( buf,
            "\n  Current Level %d: no proof obligations\n", lenpob - 1 );
      else
        sprintf ( buf,
            "\n  Current Level %d: all proof obligations discharged\n", lenpob - 1 );
      DisplayCurrWinText ( buf );
    } 
  }
}

void
GBO ( obj, ps )
int obj, ps;
{
  sprintf ( buf, "%sI", GetShortName ( obj ) );
  if ( ShortNameIsUsed ( buf ) ) {
    sprintf ( str_buf, "\n  Name clash: %s.imp will be generated\n", buf );
    DisplayCurrWinText ( str_buf ); 
    Popup_Err ( 0, "Generated construct name already used   " );
    return;
  }

  sprintf ( buf, "%sCtx", GetShortName ( obj ) );
  if ( ShortNameIsUsed ( buf ) ) {
    sprintf ( str_buf, "\n  Name clash: %s.mch may be generated\n", buf );
    DisplayCurrWinText ( str_buf ); 
    Popup_Err ( 0, "Generated construct name already used   " );
    return;
  }

  sprintf ( buf, "%sCtxI", GetShortName ( obj ) );
  if ( ShortNameIsUsed ( buf ) ) {
    sprintf ( str_buf, "\n  Name clash: %s.imp may be generated\n", buf );
    DisplayCurrWinText ( str_buf ); 
    Popup_Err ( 0, "Generated construct name already used   " );
    return;
  }

  Cre_fifo_write_buf_cmd_env ( obj, BT_GBO_WITH_ENV, 0 );
  if ( ps ) {
  int file_diff = FileDiffIntoBcom ( obj );
    if ( file_diff ) {
      int maths_change, no_comment_src, no_comment_cfg;
      Load_SRC_CFG_Names ( obj );
      DeCommentFile ( SRCName, ".Bcom", &no_comment_src );
      DeCommentFile ( CFGName, ".BBcom", &no_comment_cfg );
      maths_change = FileDifference (  ".Bcom", ".BBcom" );
      if ( maths_change ) {
        sprintf ( buf, "\n  Maths change in edited %s\n", GetName ( obj ) );
        DisplayCurrWinText ( buf );
        strcpy ( primary_string, GetName ( obj ) );
        curr_obj = obj;
        radiobox_flag = file_ed_GBO_radiobox;
        Popup_Edt_Proceed ( top_level );
      }
      else {
        sprintf ( buf, "\n  Annotation change in edited %s\n", GetName ( obj ) );
        DisplayCurrWinText ( buf );
        curr_obj = obj;
        strcpy ( xterm_title, "B_BaseObjectGenerator" );
        InvokeB ( with_XTerm, 1 );
     }
    } /* if ( file_diff */
    else {
      curr_obj = obj;
      strcpy ( xterm_title, "B_BaseObjectGenerator" );
      InvokeB ( with_XTerm, 1 );
    }
  } /* if ( ps ) */
  else {
    curr_obj = obj;
    strcpy ( xterm_title, "B_BaseObjectGenerator" );
    InvokeB ( with_XTerm, 1 );
  }
}

void
GBM ( obj, ps )
int obj, ps;
{
  sprintf ( buf, "%sI", GetShortName ( obj ) );
  if ( ShortNameIsUsed ( buf ) ) {
    sprintf ( str_buf, "\n  Name clash: %s.imp will be generated\n", buf );
    DisplayCurrWinText ( str_buf ); 
    Popup_Err ( 0, "Generated construct name already used   " );
    return;
  }

  sprintf ( buf, "%sCtx", GetShortName ( obj ) );
  if ( ShortNameIsUsed ( buf ) ) {
    sprintf ( str_buf, "\n  Name clash: %s.mch may be generated\n", buf );
    DisplayCurrWinText ( str_buf ); 
    Popup_Err ( 0, "Generated construct name already used   " );
    return;
  }

  sprintf ( buf, "%sCtxI", GetShortName ( obj ) );
  if ( ShortNameIsUsed ( buf ) ) {
    sprintf ( str_buf, "\n  Name clash: %s.imp may be generated\n", buf );
    DisplayCurrWinText ( str_buf ); 
    Popup_Err ( 0, "Generated construct name already used   " );
    return;
  }

  Cre_fifo_write_buf_cmd_env ( obj, BT_GBMI_WITH_ENV, 0 );
  if ( ps ) {
    int file_diff = FileDiffIntoBcom ( obj );
    if ( file_diff ) {
      int maths_change, no_comment_src, no_comment_cfg;
      Load_SRC_CFG_Names ( obj );
      DeCommentFile ( SRCName, ".Bcom", &no_comment_src );
      DeCommentFile ( CFGName, ".BBcom", &no_comment_cfg );
      maths_change = FileDifference (  ".Bcom", ".BBcom" );
      if ( maths_change ) {
        Popup_Info ( "  Maths change in edited Base  "  );
        sprintf ( buf, "\n  Maths change in edited %s\n\n  Resolve before generating machines\n", GetName ( obj ) );
        DisplayCurrWinText ( buf );
      }
      else {
        sprintf ( buf, "\n  Annotation change in edited %s\n", GetName ( obj ) );
        DisplayCurrWinText ( buf );
        curr_obj = obj;
        strcpy ( xterm_title, "B_BaseObjectGenerator" );
        InvokeB ( with_XTerm, 1 );
      }
    } /* if ( file_diff */
    else {
      curr_obj = obj;
      strcpy ( xterm_title, "B_BaseObjectGenerator" );
      InvokeB ( with_XTerm, 1 );
    }
  } /* if ( ps ) */
  else {
    curr_obj = obj;
    strcpy ( xterm_title, "B_BaseObjectGenerator" );
    InvokeB ( with_XTerm, 1 );
  }
}

void
ENM ( obj, ps )
int obj, ps;
{
  Cre_fifo_write_buf_cmd_env ( obj, BT_ENUM_WITH_ENV, 0 );
  if ( ps ) {
    int file_diff = FileDiffIntoBcom ( obj );
    if ( file_diff ) {
      int maths_change, no_comment_src, no_comment_cfg;
      Load_SRC_CFG_Names ( obj );
      DeCommentFile ( SRCName, ".Bcom", &no_comment_src );
      DeCommentFile ( CFGName, ".BBcom", &no_comment_cfg );
      maths_change = FileDifference (  ".Bcom", ".BBcom" );
      if ( maths_change ) {
        DisplayCurrWinText ( "\n  Maths change in edited file\n" );
        strcpy ( primary_string, GetName ( obj ) );
        curr_obj = obj;
        radiobox_flag = file_ed_ENM_radiobox;
        Popup_Edt_Proceed ( top_level );
      }
      else {
        sprintf ( buf, "\n  Annotation change in edited  %s\n", GetName ( obj )  );
        DisplayCurrWinText ( buf );
        curr_obj = obj;
        strcpy ( xterm_title, "B-Enumerator" );
        InvokeB ( with_XTerm, 1 );
      }
    } /* if ( file_diff */
    else {
      curr_obj = obj;
      strcpy ( xterm_title, "B-Enumerator" );
      InvokeB ( with_XTerm, 1 );
    }
  } /* if ( ps ) */
  else {
    curr_obj = obj;
    strcpy ( xterm_title, "B-Enumerator" );
    InvokeB ( with_XTerm, 1 );
  }
}

void
ITF ( obj, ps )
int obj, ps;
{
  int cc, Interface_Option;

  GetObjFromNameExt ( &cc, "basic_io", mch );
  if ( ! cc ) {
    /*
    strcpy ( str_buf, "\n  basic_io is not in scope!\n" );
    DisplayCurrWinText ( str_buf ); 
    Popup_Err ( 0, "basic_io is not in scope   " );
    */
    strcpy ( fifo_write_buf, "(?,basic_io):" );
    CreNumInBuf ( fifo_write_buf, BT_LIB_FRC_WITH_ENV );
    Cre_tcp_env ();
    ITF_Intro_basic_io_obj = obj;
    ITF_Intro_basic_io_ps = ps;
    ITF_Intro_basic_io = 1;
    InvokeB ( without_XTerm, 1 );
    return;
  }

  valIth_flags ( &Interface_Option, Interface_Option_num );

  if ( Interface_Option == Interface_Option_NonMotif ) {

    sprintf ( buf, "%sIo", GetShortName ( obj ) );
    if ( ShortNameIsUsed ( buf ) ) {
      sprintf ( str_buf, "\n  Name clash: %s.imp will be generated\n", buf );
      DisplayCurrWinText ( str_buf ); 
      Popup_Err ( 0, "Generated construct name already used   " );
      return;
    }

    sprintf ( buf, "%sIoI", GetShortName ( obj ) );
    if ( ShortNameIsUsed ( buf ) ) {
      sprintf ( str_buf, "\n  Name clash: %s.imp will be generated\n", buf );
      DisplayCurrWinText ( str_buf ); 
      Popup_Err ( 0, "Generated construct name already used   " );
      return;
    }

    sprintf ( buf, "%sItf", GetShortName ( obj ) );
    if ( ShortNameIsUsed ( buf ) ) {
      sprintf ( str_buf, "\n  Name clash: %s.imp will be generated\n", buf );
      DisplayCurrWinText ( str_buf ); 
      Popup_Err ( 0, "Generated construct name already used   " );
      return;
    }

    sprintf ( buf, "%sItfI", GetShortName ( obj ) );
    if ( ShortNameIsUsed ( buf ) ) {
      sprintf ( str_buf, "\n  Name clash: %s.imp will be generated\n", buf );
      DisplayCurrWinText ( str_buf ); 
      Popup_Err ( 0, "Generated construct name already used   " );
      return;
    }

    sprintf ( buf, "%sEOnumITF", GetShortName ( obj ) );
    if ( ShortNameIsUsed ( buf ) ) {
      sprintf ( str_buf, "\n  Name clash: %s.imp will be generated\n", buf );
      DisplayCurrWinText ( str_buf ); 
      Popup_Err ( 0, "Generated construct name already used   " );
      return;
    }

  } /* if ( Interface_Option == Interface_Option_NonMotif ) */


  if ( ps ) {
    int file_diff = FileDiffIntoBcom ( obj );
    if ( file_diff ) {
      int maths_change, no_comment_src, no_comment_cfg;
      Load_SRC_CFG_Names ( obj );
      DeCommentFile ( SRCName, ".Bcom", &no_comment_src );
      DeCommentFile ( CFGName, ".BBcom", &no_comment_cfg );
      maths_change = FileDifference (  ".Bcom", ".BBcom" );
      if ( maths_change ) {
        DisplayCurrWinText ( "\n  Maths change in edited file\n" );
        strcpy ( primary_string, GetName ( obj ) );
        curr_obj = obj;
        radiobox_flag = file_ed_ITF_radiobox;
        Popup_Edt_Proceed ( top_level );
      }
      else {
        sprintf ( buf, "\n  Annotation change in edited  %s\n", GetName ( obj )  );
        DisplayCurrWinText ( buf );
        Pre_Itf ( obj );
      }
    } /* if ( file_diff */
    else {
      Pre_Itf ( obj );
    }
  } /* if ( ps ) */
  else {
    Pre_Itf ( obj );
  }
}

void
TRL ( obj, ps )
int obj, ps;
{
  if ( ps ) {
    int file_diff = FileDiffIntoBcom ( obj );
    if ( file_diff ) {
      int maths_change, no_comment_src, no_comment_cfg; 
      Load_SRC_CFG_Names ( obj );
      DeCommentFile ( SRCName, ".Bcom", &no_comment_src );
      DeCommentFile ( CFGName, ".BBcom", &no_comment_cfg );
      maths_change = FileDifference (  ".Bcom", ".BBcom" );
      if ( maths_change ) {
        Popup_Info ( "Maths change in edited file  "  );
        DisplayCurrWinText ( "\n  Maths change in edited file - resolve before translation\n" );
      }
      else {
        DisplayCurrWinText ( "\n  Annotation change in edited file\n" );
        Pre_Trl ( obj );
      }
    }
    else {
      Pre_Trl ( obj );
    }
  }
  else {
    Pre_Trl ( obj );
  }
}

void
LNK ( obj, ps )
int obj, ps;
{
  if ( ps ) {
    int file_diff = FileDiffIntoBcom ( obj );
    if ( file_diff ) {
      int maths_change, no_comment_src, no_comment_cfg; 
      Load_SRC_CFG_Names ( obj );
      DeCommentFile ( SRCName, ".Bcom", &no_comment_src );
      DeCommentFile ( CFGName, ".BBcom", &no_comment_cfg );
      maths_change = FileDifference (  ".Bcom", ".BBcom" );
      if ( maths_change ) {
        Popup_Info ( "Maths change in edited file  "  );
        DisplayCurrWinText ( "\n  Maths change in edited file - resolve before linking\n" );
      }
      else {
        DisplayCurrWinText ( "\n  Annotation change in edited file\n" );
        Pre_Lnk ( obj );
      }
    }
    else {
      Pre_Lnk ( obj );
    }
  }
  else {
    Pre_Lnk ( obj );
  }
}

void
EXE ( obj, ps )
int obj, ps;
{
  char buf [ 100 ];
  int nm [ 50 ];
  int ext, cc1;
  int Prog_Language_Option;

  if ( ps ) {
    int file_diff = FileDiffIntoBcom ( obj );
    if ( file_diff ) {
      int maths_change, no_comment_src, no_comment_cfg; 
      Load_SRC_CFG_Names ( obj );
      DeCommentFile ( SRCName, ".Bcom", &no_comment_src );
      DeCommentFile ( CFGName, ".BBcom", &no_comment_cfg );
      maths_change = FileDifference (  ".Bcom", ".BBcom" );
      if ( maths_change ) {
        Popup_Info ( "Maths change in edited file  "  );
        DisplayCurrWinText ( "\n  Maths change in edited file - resolve before execution\n" );
        return;
      }
      else {
        DisplayCurrWinText ( "\n  Annotation change in edited file\n" );
      }
    }
  }
  valIth_flags ( &Prog_Language_Option, Prog_Language_Option_num );
                   
    val_ext ( &ext, obj );
    if ( ext == itf ) {
      sprintf ( primary_string, "cd CDE/C ; ./%s &", GetShortName ( obj ) );
      execute ( primary_string );
    }
    else {
      get_topabs ( &cc1, obj );
      Retrieve_String ( shell_str_num, fifo_write_buf );
      sprintf ( primary_string, "$BKIT/BLIB/ExeFile \"%s\" %s&", fifo_write_buf, GetShortName ( cc1 ) );
      execute ( primary_string );
    }
  
}

void
TRL_RST ( obj )
int obj;
{
  int ext, nn, bb, dep;
  void RST ();
  void ResetTranslatedConstruct ();

  val_ext ( & ext, obj );
  if ( ext == itf ) {
    RST ( obj );
  }
  else {
    top_level_dep_cstr = obj;
    Get_Code_Dep ( obj );
    card_gset5 ( &nn );
    if ( nn ) {
      if ( nn == 1 ) {
        member_gset5 ( &bb, obj );
        if ( bb ) {
          dep = 0;
        }
        else {
          dep = 1;
	}
      }
      else { /* nn && nn != 1 */
        dep = 1;
      }
    }
    else { /* ! nn */
      dep = 0;
    }

    del_gset5 ( obj );

    if ( dep ) {
      DisplayCurrWinText ( "\n\n    Code-dependent constructs:\n" );
      MainWinDispCode_gset ( 5 );
      sprintf ( primary_string, "Proceed with %s code module reset?", GetName ( obj ) );
      strcpy ( secondary_string,
        "Dependent code modules will be lost" );
      confirm_flag = rst_cde_but_confirm;
      curr_obj = obj;
      Popup_ConfirmDialog ( top_level );
    }
    else {
      DisplayCurrWinText ( "\n  No code-dependent constructs\n" );
      ResetTranslatedConstruct ( obj );
    }
  }
}

void
ResetTranslatedConstruct ( obj )
int obj;
{
  /***
  gset5 contains code-dependent constructs
  ***/

  int nn, cc, ext, st, bb, dep;

  card_gset5 ( &nn );
  dep = nn;
  while ( nn ) {
    valOrd_gset5 ( &cc, nn );
/***
printf ( "ResetTranslatedConstruct %s - dep %s\n", GetName ( obj ), GetName ( cc ) );
***/
    val_ext ( &ext, cc );
    if ( ext == imp ) {
      val_curMRIState ( &st, cc );
      mod_trl ( st, FALSE );
      mod_lnk ( st, FALSE );
      Load_SRC_CFG_Names ( cc );
      RemoveCodeFiles ( cc );
      SetDisplayField_obj_Changed ( cc );
    }
    else if ( ext == mch ) {  /* executables stored as mch */ 
      GetObjFromNameExt ( &cc, GetShortName ( cc ), itf );
      if ( cc ) {
        val_curGENState( &st, cc );
        val_gen2 ( &bb, st );
        if ( bb ) CheckUngen ( cc );
        SetDisplayField_obj_Changed ( cc );
      }
    }
    nn--;
  }
  val_ext ( &ext, obj );
  if ( ext == imp ) {
    val_curMRIState ( &st, obj );
    mod_trl ( st, FALSE );
    mod_lnk ( st, FALSE );
  }
  Load_SRC_CFG_Names ( obj );
  RemoveCodeFiles ( obj );
  SetDisplayField_obj_Changed ( obj );

  if ( dep ) 
    sprintf ( buf, "\n  Reset %s code modules\n  and code-dependents\n",
                                                                   GetName ( obj ) );
  else
    sprintf ( buf, "\n  Reset %s code modules\n", GetName ( obj ) );
  DisplayCurrWinText ( buf );
  DisplayCurrentEnv ();
}

void
DMU ( obj, ps )
int obj, ps;
{
  int ext, nn, rr;

  val_ext ( &ext, obj );
  if ( ext == doc ) {
    Cre_fifo_write_buf_cmd_env ( obj, BT_DOC_WITH_ENV, 0 );
  }
  else {
    Cre_fifo_write_buf_cmd_env ( obj, BT_DMU_WITH_ENV, 0 );
  }

  if ( ps ) {
    int file_diff = FileDiffIntoBcom ( obj );
    if ( file_diff ) {
      int maths_change, no_comment_src, no_comment_cfg; 
      Load_SRC_CFG_Names ( obj );
      DeCommentFile ( SRCName, ".Bcom", &no_comment_src );
      DeCommentFile ( CFGName, ".BBcom", &no_comment_cfg );
      maths_change = FileDifference (  ".Bcom", ".BBcom" );
      if ( ! maths_change ) {
        DisplayCurrWinText ( "\n  Annotation change in edited file " );
        top_level_dep_cstr = obj;
        get_dep_cstr ( &rr, obj );
        chk_rep ( rr, 4 );
        Remove_non_doc_gset1 ();
        card_gset1 ( &nn );
        if ( nn == 0 ) {
          DisplayCurrWinText ( "(no DOCUMENT dependencies)" );
        }
        else {
          /***
          This should never happen!
          ***/
          DisplayCurrWinText ( "\n\n    DOCUMENT-dependent constructs:\n" );
          MainWinDisp_gset ( 1 );
        }
        strcpy ( primary_string, GetName ( obj ) );
        if ( ext == doc ) {
          radiobox_flag = file_ed_DOC_radiobox;
	}
        else {
          radiobox_flag = file_ed_DMU_radiobox;
	}
        curr_obj = obj;
        Popup_Edt_Proceed ( top_level );
      }
      else {
        if ( ext == doc ) { 
          DisplayCurrWinText ( "\n  Maths change in edited file " );
          top_level_dep_cstr = obj;
          get_dep_cstr ( &rr, obj );
          chk_rep ( rr, 4 );
          Remove_non_doc_gset1 ();
          card_gset1 ( &nn );
          if ( nn == 0 ) {
            DisplayCurrWinText ( "(no DOCUMENT dependencies)" );
          }
          else {
            /***
            This should never happen!
            ***/
            DisplayCurrWinText ( "\n\n    DOCUMENT-dependent constructs:\n" );
            MainWinDisp_gset ( 1 );
          }
          strcpy ( primary_string, GetName ( obj ) );
          radiobox_flag = file_ed_DOC_radiobox;
          curr_obj = obj;
          Popup_Edt_Proceed ( top_level );
	}
        else {
          Popup_Info ( "Maths change in edited file  "  );
          DisplayCurrWinText (
                  "\n  Maths change in edited file - resolve before marking up\n" );
	}
      }
    }  /* if ( file_diff ) */
    else {
/***
printf ( "DMU: fifo_write_buf `%s'\n", fifo_write_buf );
***/
      strcpy ( xterm_title, "B-Documentor" );
      InvokeB ( with_XTerm, 1 );
    }
  }  
  else { /* if ( ps ) */
    strcpy ( xterm_title, "B-Documentor" );
/***
printf ( "DMU: fifo_write_buf `%s'\n", fifo_write_buf );
***/
    InvokeB ( with_XTerm, 1 );
  }
}

void
SHW ( obj )
int obj;
{
  Retrieve_String ( dvi_screen_str_num, buf );
  if ( strcmp ( buf, "" ) == 0 ) {
    Popup_Err ( 0, "Dvi Screen Viewer not set - check TopBar Options" );
    DisplayCurrentEnv ();
  }
  else {
    sprintf ( fifo_write_buf, " Executing %s TEX/%s.dvi", buf, GetName ( obj ) );
    Popup_Info ( fifo_write_buf );
    sprintf ( str_buf, "%s TEX/%s.dvi &", buf, GetName ( obj ) );
    execute ( str_buf );
  }
}

void
PRT ( obj )
int obj;
{
  Retrieve_String ( dvi_print_str_num, buf );
  if ( strcmp ( buf, "" ) == 0 ) {
    Popup_Err ( 0, "Dvi Print Script not set - check TopBar Options" );
    DisplayCurrentEnv ();
  }
  else {
    sprintf ( fifo_write_buf, " Executing %s TEX/%s.dvi", buf, GetName ( obj ) );
    Popup_Info ( fifo_write_buf );
    sprintf ( str_buf, "%s TEX/%s.dvi &", buf, GetName ( obj ) );
    execute ( str_buf );
  }
}

void
DOC_RST ( obj )
int obj;
{
  int rr, nn;
  void ResetDocument ();

  top_level_dep_cstr = obj;
  get_dep_cstr ( &rr, obj );
  chk_rep ( rr, 239 );
  Remove_non_doc_gset1 ();
  card_gset1 ( &nn );
  if ( nn == 0 ) {
    DisplayCurrWinText ( "\n    No DOCUMENT dependencies\n" );
    Load_SRC_CFG_Names ( obj );
    CommitAnnotationEdits ( obj, /* reset_dmu_flag = */ 1 );
  }
  else {
    DisplayCurrWinText ( "\n    DOCUMENT-dependent constructs:\n" );
    MainWinDisp_gset ( 1 );
    sprintf ( primary_string, "Proceed with %s document reset?", GetName ( obj ) );
    strcpy ( secondary_string,
      "Dependent document construct processing will be lost" );
    confirm_flag = commit_doc_rst_but_confirm;
    curr_obj = obj;
    Popup_ConfirmDialog ( top_level );
  }  
}

void
Pre_Itf ( obj )
int obj;
{
  int cc0, cc1, cc2, cc3, cc4, bb, nn, rr, mm, ss, ext;
  char buf [ 100 ];
  int tmp_arr [ 100 ];
  int Interface_Option;

  valIth_flags ( &Interface_Option, Interface_Option_num );

  GetObjFromNameExt ( &cc0, GetShortName ( obj ), mch );
  if ( ! cc0 ) {
    sprintf ( buf, "  %s.mch is not configured!  ", GetShortName ( obj ) );
    Popup_Err ( 0, buf );
    sprintf ( post_process_xterm_text, "\n  %s\n", buf );
    DisplayCurrWinText ( post_process_xterm_text );
    sprintf ( post_process_xterm_text, "\n  Can't generate interface for %s\n", GetShortName ( obj ) );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  sprintf ( fifo_write_buf, "(%s|", GetName ( cc0 ) );

  bb = Is_LibOrEnm ( cc0 );
/***
printf ( "bb=%d cc0=%d\n", bb, cc0 );
***/
  if ( bb ) {
    int type, nn, cc1, rr;
    strcat ( fifo_write_buf, GetName ( cc0 ) );
    val_type ( &type , cc0 );
    if ( type == lib      || type == enm_gen ||
         type == gen_vhdl || type == lib_vhdl   ) {
      strcat ( fifo_write_buf, "|?|" );
      clear_gset1 ();
      card_sees_uses ( &nn, cc0 );
      while ( nn ) {
        valOrd_sees_uses( &cc1, cc0, nn );
/***
printf ( "  cc1=%d\n", cc1 );
***/
        member_gset1 ( &bb, cc1 );
        if ( ! bb ) {
          add_gset1 ( &rr, cc1 );
          chk_rep ( rr, 93 );
	}
        nn--;
      }
      card_gset1 ( &nn );
      if ( nn ) {
        Cat_gset_tcp ( 1 );
        strcat ( fifo_write_buf, "|" );
        Cat_gset_tcp ( 1 );
      }
      else {
        strcat ( fifo_write_buf, "?|?" );
      }
      strcat ( fifo_write_buf, "):" );
    }
    else {
      strcat ( fifo_write_buf, "|?|?|?):" );
    }
    if ( Interface_Option == Interface_Option_Motif ) {
      CreNumInBuf ( fifo_write_buf, BT_CIOM_WITH_ENV );
    }
    else {
      CreNumInBuf ( fifo_write_buf, BT_CIO_WITH_ENV );
    }
    Cre_tcp_env ();
    strcpy ( xterm_title, "B-InterfaceGenerator" );
    translating_pre_MInterface = 0;
    InvokeB ( with_XTerm, 1 );  /* LibOrEnm - not necessary to do the checks below */
    return;
  }  /* Is_LibOrEnm */

  cc1 = HasImp ( cc0 );
  if ( ! cc1 ) {
    sprintf ( buf, "  %s has no (analysed) implementation!  ",
                                                            GetShortName ( cc0 ) );
    Popup_Err ( 0, buf );
    sprintf ( post_process_xterm_text, "\n  %s\n", buf );
    DisplayCurrWinText (  post_process_xterm_text );
    sprintf ( post_process_xterm_text, "\n  Can't generate interface for %s\n", GetShortName ( obj ) );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  strcat ( fifo_write_buf, GetName ( cc1 ) );
  strcat ( fifo_write_buf, "|" );

  nn = CheckDuplicateIpt ( cc1 );

  if ( nn ) {
    int ex;
    Popup_Err ( 0, "    Duplicate import!    " );
    post_process_xterm_text [ 0 ] = '\0';
    while ( nn ) {
      valIth_gseq ( &cc2, nn );
      strcat ( post_process_xterm_text, "\n    Duplicate import - " );
      strcat ( post_process_xterm_text, GetShortName ( cc1 ) );
      strcat ( post_process_xterm_text, " is already imported by:\n" );
      top_level_dep_cstr = cc2;
      get_dep_cstr ( &rr, cc2 );
      chk_rep ( rr, 41 );
      card_gset1 ( &mm );
      while ( mm ) {
        valOrd_gset1 ( &cc3, mm );
        val_ext ( &ex, cc3 );
        if ( ex == imp ) {
          member_inc_ipt ( &bb, cc3, cc2 );
          if ( bb ) {
            member_gset5 ( &bb, cc3 );
            if ( bb ) {
              strcat ( post_process_xterm_text, "      " );
              strcat ( post_process_xterm_text, GetShortName ( cc3 ) );
              strcat ( post_process_xterm_text, "\n" );
	    }
	  }
	}
        mm--;
      }
      nn--;
    }
    strcat ( post_process_xterm_text, "\n  Interface for " );
    strcat ( post_process_xterm_text, GetShortName ( cc0 ) );
    strcat ( post_process_xterm_text, " aborted\n" );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  Cat_gset_tcp ( 1 );
  strcat ( fifo_write_buf, "|" );
  
  nn = GetIptWithNoImp ( cc1 );
  if ( nn ) {
    Popup_Err ( 0, "All recursively imported machines should be implemented!" );
    if ( nn == 1 ) {
      valOrd_gset3 ( &cc1, 1 );
      strcpy ( post_process_xterm_text,"\n    (Recursively) Imported machine\n      " );
      strcat ( post_process_xterm_text, GetShortName ( cc1 ) );
      strcat ( post_process_xterm_text, "\n    has no (analysed) implementation\n" );
    }
    else {
      strcpy ( post_process_xterm_text,"\n    The following imported machines have\n    no (analysed) implementation:\n" );
      while ( nn ) {
        valOrd_gset3 ( &cc1, nn );
        strcat ( post_process_xterm_text, "      " );
        strcat ( post_process_xterm_text, GetShortName ( cc1 ) );
        strcat ( post_process_xterm_text,"\n" );
        
        nn--;
      }
    }
    strcat ( post_process_xterm_text, "\n  Interface for " );
    strcat ( post_process_xterm_text, GetShortName ( cc0 ) );
    strcat ( post_process_xterm_text, " aborted\n" );
    DisplayChanged = 1;
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  nn = GetSeenWithNoImp ( cc1 );
  if ( nn ) {
    Popup_Err ( 0, "All seen machines should be implemented!" );
    if ( nn == 1 ) {
      valOrd_gset3 ( &cc1, 1 );
      strcpy ( post_process_xterm_text,"\n    Seen machine\n      " );
      strcat ( post_process_xterm_text, GetShortName ( cc1 ) );
      strcat ( post_process_xterm_text, "\n    has no (analysed) implementation\n" );
    }
    else {
       strcpy ( post_process_xterm_text,"\n    The following seen machines have\n    no (analysed) implementation:\n" );
      while ( nn ) {
        valOrd_gset3 ( &cc1, nn );
        strcat ( post_process_xterm_text, "      " );
        strcat ( post_process_xterm_text, GetShortName ( cc1 ) );
        strcat ( post_process_xterm_text,"\n" );
        nn--;
      }
   }
    strcat ( post_process_xterm_text, "\n  Interface for " );
    strcat ( post_process_xterm_text, GetShortName ( cc0 ) );
    strcat ( post_process_xterm_text, " aborted\n" );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  GetIptThroughSees ( cc1 );

  nn = GetSeenNotIpt ( cc1 );
/***
printf("\nGetSeenNotIpt\n");
show_gset ( 2 );
***/

  clear_gset3 ();
  card_gset2 ( &nn );
  while ( nn ) {
    valOrd_gset2 ( &cc2, nn );
    member_gset5 ( &bb, cc2 );  /* presumeably, this *is* gset5 */
    if ( ! bb ) {
      member_gset3 ( &bb, cc2 );
      if ( ! bb ) {
        add_gset3 ( &rr, cc2 );
        chk_rep ( rr, 82 );
      }
    }
    nn--;
  }
/***
printf("\nFilteredSeenNotIpt\n");
show_gset ( 3 );
***/

  card_gset3 ( &nn );
  if ( nn ) {
    Cat_gset_tcp ( 3 );
  }
  else {
    strcat ( fifo_write_buf, "?" );
  }

  strcat ( fifo_write_buf, "|" );

  nn = GetLinkList ( cc1 );
/***
printf( "GetLinkList for %d:\n", cc1 );
show_gset(1);
***/
  if ( nn ) {
    Cat_gset_tcp ( 1 );
  }
  else {
    strcat ( fifo_write_buf, "?" );
  }

    strcat ( fifo_write_buf, "):" );
/***
printf( "seen but not imported:\n" );
show_gset(2);
***/
  if ( Interface_Option == Interface_Option_Motif ) {
    int is_trl;
    is_trl = Is_Trl ( cc1 );
    if ( is_trl ) {
/***
printf(" Interface_Option == Interface_Option_Motif && is_trl\n" );
***/
      CreNumInBuf ( fifo_write_buf, BT_CIOM_WITH_ENV );
      Cre_tcp_env ();
      strcpy ( xterm_title, "B-InterfaceGenerator" );
      translating_pre_MInterface = 0;
      InvokeB ( with_XTerm, 1 );
    }
    else {
/***
printf(" Interface_Option == Interface_Option_Motif && ! is_trl\n" );
***/
      if ( translating_pre_MInterface ) { /* been here before! */
        translating_pre_MInterface = 0;
        if ( bell_option ) {
          XBell ( display, -75 );
          XBell ( display, -75 );
        }
        process_XTerm_IfReq ();
        LoadBcjm ();
        XmUpdateDisplay ( top_level );
        DisplayCurrentEnv ();
        if ( auto_reset_and_remake && ( ! upgrade3T04_flag ) ){
          Save_n_CfgDepBase ();
          AutoRemakeFini ();
          strcpy ( fifo_write_buf, "0:" );
          Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
          InvokeB ( without_XTerm, 1 );
	}
      }
      else {
        translating_pre_MInterface = cc1;
        Load_SRC_CFG_Names ( cc1 );
        sprintf ( buf, "\n  Motif interface requires translation of %s ...\n",
                                                                   GetName ( cc1 ) );
        DisplayCurrWinText ( buf );
        Pre_Trl ( cc1 );
      }
    }
  }
  else {
/***
printf(" Interface_Option != Interface_Option_Motif\n" );
***/
    CreNumInBuf ( fifo_write_buf, BT_CIO_WITH_ENV );
    Cre_tcp_env ();
    strcpy ( xterm_title, "B-InterfaceGenerator" );
    InvokeB ( with_XTerm, 1 );
  }
}

void
Pre_Rename ( cc )
int cc;
{
  xtr_name ( buf, cc );
  curr_obj = cc;
  Popup_RenamePromptDialog ( ( char * ) buf );
}

void
Rename ( name )
char * name;
{
  int rr, cur_name [ 50 ];
  char cmd [ 250 ];
  char curr_cfg_file [ 75 ];
  int i, clash;
  void RenameDisplayName ();
  int NameAlreadyUsed ();

  if ( strlen ( name ) == 0 ) {
    Popup_Info ( "  Rename string empty!  " );
    DisplayCurrWinText ( "\n  Rename aborted\n" );
    DisplayCurrentEnv ();
    return;
  }
  if ( ( name [0] < 'a' || name [0] > 'z' ) &&
       ( name [0] < 'A' || name [0] > 'Z' )    ) {
    strcpy ( buf, "Name \"" );
    strcat ( buf, name );
    strcat ( buf, "\" should begin with a letter" );
    Popup_Err ( 0, buf );
    DisplayCurrWinText ( "\n  Rename aborted\n" );
    DisplayCurrentEnv ();
    return;
  }
  if ( strlen ( name ) > 50 ) {
    strcpy ( buf, "Name \"" );
    strcat ( buf, name );
    strcat ( buf, "\" too long (max length 50)" );
    Popup_Err ( 0, buf );
    DisplayCurrWinText ( "\n  Rename aborted\n" );
    DisplayCurrentEnv ();
    return;
  }

  clash = 0;
  xtr_name ( cur_name, curr_obj );
  if ( NameAlreadyUsed ( name, curr_obj ) ) {
    sprintf ( buf, "Name \"%s\" is already used", name );
    Popup_Err ( 0, buf );
    DisplayCurrWinText ( "\n  Rename aborted\n" );    
    DisplayCurrentEnv ();
    return;
  }

  sprintf ( curr_cfg_file, "CFG/%s", GetName ( curr_obj ) );
  sprintf ( buf, "\n  Renamed %s to ", GetName ( curr_obj ) );
  sprintf ( cmd, "sed -e s+\"%s\"+\"%s\"+g CFG/%s > .Btmp ",
                                  ( char * ) cur_name, name, GetName ( curr_obj ) );
  execute ( cmd ); 
  mod_name ( &rr, curr_obj, name );
  chk_rep ( rr, 151 );
  RenameDisplayName ( curr_obj, name );
  sprintf ( cmd, "mv .Btmp CFG/%s", GetName ( curr_obj ) );
/***
printf ( "%s\n", cmd );
***/
  execute ( cmd );
/***
printf ( "unlink \"%s\"\n", curr_cfg_file );
***/
  unlink ( curr_cfg_file );
  strcat ( buf, GetName ( curr_obj ) );
  strcat ( buf, "\n" );
  DisplayCurrWinText ( buf );
  DisplayCurrentEnv ();
}

void
Sub_Rec_Trl_In_gseq ( cc )
int cc;
{
  int nn, mm, bb, st, cc1, cc2, ext, rr;

/***
printf ( "IN Sub_Rec_Trl_In_gseq ( %d )\n", cc );
***/
  val_curMRIState ( &st, cc );
  val_trl ( &bb, st );
  if ( ! bb ) {
    within_gseq ( &bb, &mm, cc );
/***
printf ( "    Not in gseq\n" );
***/
    if ( ! bb ) {
      card_sees_uses ( &nn, cc );
      while ( nn ) {
        valOrd_sees_uses( &cc1, cc, nn );
        get_botref ( &cc2, cc1 );
        val_ext ( &ext, cc2 );
        if ( ext == imp ) {
          Sub_Rec_Trl_In_gseq ( cc2 );
	}
        nn--;
      }
      card_inc_ipt ( &nn, cc );
      while ( nn ) {
        valOrd_inc_ipt( &cc1, cc, nn );
        get_botref ( &cc2, cc1 );
        val_ext ( &ext, cc2 );
        if ( ext == imp ) {
          Sub_Rec_Trl_In_gseq ( cc2 );
	}
        nn--;
      }
      within_gseq ( &bb, &mm, cc );
      if ( ! bb ) {
        push_gseq ( &rr, cc );
        chk_rep ( rr, 47 );
      }
    }
  }
/***
printf ( "OUT Sub_Rec_Trl_In_gseq ( %d )\n", cc );
***/
}


void
Rec_Trl_In_gseq ( cc )
int cc;
{
  int nn, mm, cc1, cc2, st, ext, rr, bb;

  clear_gseq ();
  card_sees_uses ( &nn, cc );
  while ( nn ) {
    valOrd_sees_uses ( &cc1, cc, nn );
    get_botref ( &cc2, cc1 );
    val_ext ( &ext, cc2 );
    if ( ext == imp ) {
      Sub_Rec_Trl_In_gseq ( cc2 );
    }
    nn--;
  }
  card_inc_ipt ( &nn, cc );
  while ( nn ) {
    valOrd_inc_ipt( &cc1, cc, nn );
    get_botref ( &cc2, cc1 );
    val_ext ( &ext, cc2 );
    if ( ext == imp ) {
      Sub_Rec_Trl_In_gseq ( cc2 );
    }
    nn--;
  }
  val_curMRIState ( &st, cc );
  val_trl ( &bb, st );
  if ( ! bb ) {  
    within_gseq ( &bb, &mm, cc );
    if ( ! bb ) {
      push_gseq ( &rr, cc );
      chk_rep ( rr, 48 );
    }
  }
}


int
SeenImportedBelow ( cc0, cc )
int cc0, cc;
{
  /*** cc0 is the mch, cc is the imp ***/
  int nn, ss, rr, bb, cc1, cc2, cc3, loc, found;

/***
print_info ( "  -->> SeenImportedBelow for ", cc );
***/

  found = 0;

  /*** first load gset4 with seen by cc - if empty return 0 ***/

  clear_gset4 ();
  def_sees_uses ( &bb, cc );
  if ( bb ) {
    val_sees_uses ( &ss, cc );
    union_gset4 ( &rr, ss );
    chk_rep ( rr, 187 );
  }

  card_gset4 ( &nn );
  if ( ! nn ) return ( 0 );

  /*** first load gset3 with recseenipt for imported by cc ***/

  clear_gset3 ();
  def_inc_ipt ( &bb, cc );
  if ( bb ) {
    val_inc_ipt ( &ss, cc );
    union_gset3 ( &rr, ss );
    chk_rep ( rr, 188 );
    card_inc_ipt ( &nn, cc );
    while ( nn ) {
      valOrd_inc_ipt ( &cc1, cc, nn );
      get_botref ( &cc2, cc1 );
      get_recseenipt_mchlist ( &rr, cc2 );
      chk_rep ( rr, 189 );
      val_gset1 ( &ss );
      union_gset3 ( &rr, ss );
      chk_rep ( rr, 190 );
      nn--;
    }
  }

/***
card_gset3 ( &nn );
while ( nn ) {
  valOrd_gset3 ( &cc1, nn );
  print_info ( "  gset3:  ", cc1 );
  nn--;
}
DisplayCurrWinText ( "\n" );
***/

  /*** now gset3 /\ gset4 -> gset4  - if empty return 0 ***/

  val_gset3 ( &ss, cc );
  inter_gset4 ( ss );

/***
card_gset4 ( &nn );
while ( nn ) {
  valOrd_gset4 ( &cc1, nn );
  print_info ( "  concerned with gset4:  ", cc1 );
  nn--;
}
DisplayCurrWinText ( "\n" );
***/

  card_gset4 ( &nn );
  if ( ! nn ) return ( 0 );

  /*** find who imports each mch in gset4 - if in gset3 return it
       and set gset5 to be the singleton set with the importing imp ***/

  clear_gset5 ();
  while ( ( nn ) && ( ! found ) ) {
    valOrd_gset4 ( &cc1, nn );
    /*** looking to see who imports cc1 ***/
/***
  print_info ( "looking at:  ", cc1 );
***/
    first_Construct ( &loc, &cc2 );
    while ( ( loc ) && ( ! found ) ) {
      val_ext ( &tt, cc2 );
      if ( tt == imp ) {
/***
print_info ( "current imp:  ", cc2 );
***/
        def_inc_ipt ( &bb, cc2 );
        if ( bb ) {
          member_inc_ipt ( &bb, cc2, cc1 );
          /*** cc2 imports cc1 ***/
          if ( bb ) {
/***
print_info ( "imported by:  ", cc2 );
***/
            get_topabs ( &cc3, cc2 );
/***
print_info ( "abstraction:  ", cc3 );
***/
            member_gset3 ( &bb, cc3 );
            if ( bb ) {
/***
print_info ( "eureka: ", cc3 );
***/
              found = cc1;
              add_gset5 ( &rr, cc2 );
              chk_rep ( rr, 196 );
	    }
	  }
	}
      }
      next_Construct ( &loc, &cc2, loc, cc2 );
    }
    nn--;
  }

  return ( found );
}


void
Pre_Trl ( obj )
int obj;
{
  int cc, cc1, cc2, cc3, cc4, bb, nn, rr, mm, pp, ex, type;
  int Prog_Language_Option;
  char buf [ 100 ];

/***
printf ( "Pre_Trl %s\n", GetName ( obj ) );
***/

/***
printf ( "1 %s\n", GetName ( obj ) ); fflush ( stdout );
***/

  val_type ( &type, obj );
  get_topabs ( &cc, obj );
  nn = CheckDuplicateIpt ( obj );

/***
printf ( "2 %s %d\n", GetName ( cc ), nn ); fflush ( stdout );
***/

  if ( nn ) {
    Popup_Err ( 0, "    Duplicate import!    " );
    post_process_xterm_text [ 0 ] = '\0';
    while ( nn ) {
      valIth_gseq ( &cc2, nn );
      sprintf ( post_process_xterm_text,
            "\n    Duplicate import - %s is already imported by:\n",
                                                            GetShortName ( cc2 ) );
      top_level_dep_cstr = cc2;
      get_dep_cstr ( &rr, cc2 );
      chk_rep ( rr, 41 );
      card_gset1 ( &mm );
      while ( mm ) {
        valOrd_gset1 ( &cc3, mm );
        val_ext ( &ex, cc3 );
        if ( ex == imp ) {
          member_inc_ipt ( &bb, cc3, cc2 );
          if ( bb ) {
            member_gset5 ( &bb, cc3 );
            if ( bb ) {
              strcat ( post_process_xterm_text, "      " );
              strcat ( post_process_xterm_text, GetShortName ( cc3 ) );
	    }
	  }
	}
        mm--;
        strcat ( post_process_xterm_text, "\n\n" );
      }
      nn--;
    }
    strcat ( post_process_xterm_text, "\n  Translation of " );
    strcat ( post_process_xterm_text, GetShortName ( obj ) );
    strcat ( post_process_xterm_text, " aborted\n" );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  nn = GetIptWithNoImp ( obj );

/***
printf ( "3 %d\n", nn ); fflush ( stdout );
***/

  if ( nn && type != usr_vhdl && type != gen_vhdl ) {
    Popup_Err ( 0, "All recursively imported machines should be implemented!" );
    if ( nn == 1 ) {
      valOrd_gset3 ( &cc1, 1 );
      sprintf ( post_process_xterm_text,"\n    (Recursively) Imported machine\n      %s\n    has no (analysed) implementation\n", GetShortName ( cc1 ) );
    }
    else {
      strcpy ( post_process_xterm_text ,"\n    The following imported machines have\n    no (analysed) implementation:\n" );
      while ( nn ) {
        valOrd_gset3 ( &cc1, nn );
        strcat ( post_process_xterm_text, "      " );
        strcat ( post_process_xterm_text, GetShortName ( cc1 ) );
        strcat ( post_process_xterm_text,"\n" );
        
        nn--;
      }
    }
    strcat ( post_process_xterm_text, "\n  Translation of " );
    strcat ( post_process_xterm_text, GetShortName ( obj ) );
    strcat ( post_process_xterm_text, " aborted\n" );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  nn = GetSeenWithNoImp ( obj );

/***
printf ( "4 %d\n", nn ); fflush ( stdout );
***/

  if ( nn && type != usr_vhdl && type != gen_vhdl ) {
    Popup_Err ( 0, "All seen machines should be implemented!" );
    if ( nn == 1 ) {
      valOrd_gset3 ( &cc1, 1 );
      sprintf ( post_process_xterm_text,"\n    Seen machine\n      %s\n    has no (analysed) implementation\n", GetShortName ( cc1 ) );
    }
    else {
       strcpy ( post_process_xterm_text,"\n    The following seen machines have\n    no (analysed) implementation:\n" );
      while ( nn ) {
        valOrd_gset3 ( &cc1, nn );
        strcat ( post_process_xterm_text, "      " );
        strcat ( post_process_xterm_text, GetShortName ( cc1 ) );
        strcat ( post_process_xterm_text,"\n" );
        nn--;
      }
   }
    strcat ( post_process_xterm_text, "\n  Translation of " );
    strcat ( post_process_xterm_text, GetShortName ( obj ) );
    strcat ( post_process_xterm_text, " aborted\n" );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  cc2 = SeenImportedBelow ( cc, obj );

/***
printf ( "5 %d\n", cc2  ); fflush ( stdout );
***/

  if ( cc2 ) {
    Popup_Err ( 0, "    Bad design structure!    " );
    valOrd_gset5 ( &cc4, 1 );
    sprintf ( post_process_xterm_text, "\n  Seen machine\n    %s\n  is imported by lower-level\n    %s\n\n  Translation of %s aborted\n", GetShortName ( cc2 ), GetShortName ( cc4 ), GetShortName ( obj ), BT_RM_ALL_JOBS );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  Rec_Trl_In_gseq ( obj );

  length_gseq ( &mm );
  if ( ! mm ) {
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
  }
  else {
    strcpy ( fifo_write_buf, "(" );
    if ( type != usr_vhdl && type != gen_vhdl ) {
      pp = mm;
      while ( mm ) {
        if ( mm != pp ) {
          strcat ( fifo_write_buf, ";(" );
        }
        else {
          strcat ( fifo_write_buf, "(" );
        }
        valIth_gseq( &cc1, mm );
        strcat ( fifo_write_buf, GetName ( cc1 ) );
        strcat ( fifo_write_buf, "|" );
        get_topabs ( &cc2, cc1 );
        strcat ( fifo_write_buf, GetName ( cc2 ) );
        strcat ( fifo_write_buf, "|?" );
        card_inc_ipt ( &nn, cc1 );
        while ( nn ) {
          valOrd_inc_ipt ( &cc2, cc1, nn );
          strcat ( fifo_write_buf, "," );
          strcat ( fifo_write_buf, GetName ( cc2 ) );
          nn--;
        }
        strcat ( fifo_write_buf, "|?" );
        card_sees_uses ( &nn, cc1 );
        while ( nn ) {
          valOrd_sees_uses ( &cc2, cc1, nn );
          strcat ( fifo_write_buf, "," );
          strcat ( fifo_write_buf, GetName ( cc2 ) );
          nn--;
        }
        strcat ( fifo_write_buf, ")" );
        mm--;
      }
    }
    else { /* usr_vhdl || gen_vhdl */
      strcat ( fifo_write_buf, GetName ( obj ) );
      strcat ( fifo_write_buf, "|" );
      get_topabs ( &cc2, obj );
      strcat ( fifo_write_buf, GetName ( cc2 ) );
      strcat ( fifo_write_buf, "|?" );
      card_inc_ipt ( &nn, obj );
      while ( nn ) {
        valOrd_inc_ipt ( &cc2, obj, nn );
        strcat ( fifo_write_buf, "," );
        strcat ( fifo_write_buf, GetName ( cc2 ) );
        nn--;
      }
      strcat ( fifo_write_buf, "|?" );
      card_sees_uses ( &nn, obj );
      while ( nn ) {
        valOrd_sees_uses ( &cc2, obj, nn );
        strcat ( fifo_write_buf, "," );
        strcat ( fifo_write_buf, GetName ( cc2 ) );
        nn--;
      }
    }
    strcat ( fifo_write_buf, "):" );
    
      CreNumInBuf ( fifo_write_buf, BT_TRL_WITH_IPT_SEES );
      Cre_tcp_env ();
      valIth_flags ( &Prog_Language_Option, Prog_Language_Option_num );
      
        if ( translating_pre_MInterface ) {
          strcpy ( xterm_title, "B-InterfaceGenerator" );
        }
        else {
          strcpy ( xterm_title, "B-Translator" );
        }
      
    
  }
/***
  printf ( "\nMAX_NUM_CONSTRUCTS = %d %s %d\n", MAX_NUM_CONSTRUCTS, fifo_write_buf, strlen ( fifo_write_buf ) ); fflush ( stdout );
***/
  InvokeB ( with_XTerm, 1 );
}


void
Pre_Lnk ( obj )
int obj;
{
  int cc, cc1, cc2, cc3, bb, nn, rr, mm, pp, ex;
  char buf [ 100 ];

  get_topabs ( &cc, obj );
  nn = CheckDuplicateIpt ( obj );

  if ( nn ) {
    Popup_Err ( 0, "    Duplicate import!    " );
    post_process_xterm_text [ 0 ] = '\0';
    while ( nn ) {
      valIth_gseq ( &cc2, nn );
      sprintf ( post_process_xterm_text,
         "\n    Duplicate import - %s is already imported by:\n",
                                                          GetShortName ( cc2 ) );
      top_level_dep_cstr = cc2;
      get_dep_cstr ( &rr, cc2 );
      chk_rep ( rr, 41 );
      card_gset1 ( &mm );
      while ( mm ) {
        valOrd_gset1 ( &cc3, mm );
        val_ext ( &ex, cc3 );
        if ( ex == imp ) {
          member_inc_ipt ( &bb, cc3, cc2 );
          if ( bb ) {
            member_gset5 ( &bb, cc3 );
            if ( bb ) {
              strcat ( post_process_xterm_text, "      " );
              strcat ( post_process_xterm_text, GetShortName ( cc3 ) );
              strcat ( post_process_xterm_text, "\n" );
	    }
	  }
	}
        mm--;
      }
      nn--;
    }
    strcat ( post_process_xterm_text, "\n  Linking of " );
    strcat ( post_process_xterm_text, GetShortName ( obj ) );
    strcat ( post_process_xterm_text, " aborted\n" );
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  nn = GetIptWithNoImp ( obj );
  if ( nn ) {
    Popup_Err ( 0, "All recursively imported machines should be implemented!" );
    if ( nn == 1 ) {
      valOrd_gset3 ( &cc1, 1 );
      sprintf ( post_process_xterm_text,"\n    (Recursively) Imported machine\n     %s \n    has no (analysed) implementation\n", GetShortName ( cc1 ) );
    }
    else {
      strcpy ( post_process_xterm_text,"\n    The following imported machines have\n    no (analysed) implementation:\n" );
      while ( nn ) {
        valOrd_gset3 ( &cc1, nn );
        strcat ( post_process_xterm_text, "      " );
        strcat ( post_process_xterm_text, GetShortName ( cc1 ) );
        strcat ( post_process_xterm_text,"\n" );
        
        nn--;
      }
    }
    strcat ( post_process_xterm_text, "\n  Linking of " );
    strcat ( post_process_xterm_text, GetShortName ( obj ) );
    strcat ( post_process_xterm_text, " aborted\n" );
    DisplayChanged = 1;
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  nn = GetSeenWithNoImp ( obj );
  if ( nn ) {
    Popup_Err ( 0, "All seen machines should be implemented!" );
    if ( nn == 1 ) {
      sprintf ( post_process_xterm_text,"\n    Seen machine\n      %s\n    has no (analysed) implementation\n", GetShortName ( cc1 ) );
    }
    else {
       strcpy ( post_process_xterm_text,"\n    The following seen machines have\n    no (analysed) implementation:\n" );
      while ( nn ) {
        valOrd_gset3 ( &cc1, nn );
        strcat ( post_process_xterm_text, "      " );
        strcat ( post_process_xterm_text, GetShortName ( cc1 ) );
        strcat ( post_process_xterm_text,"\n" );
        nn--;
      }
   }
    strcat ( post_process_xterm_text, "\n  Linking of " );
    strcat ( post_process_xterm_text, GetShortName ( obj ) );
    strcat ( post_process_xterm_text, " aborted\n" );
    DisplayChanged = 1;
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  nn = GetSeenNotIpt ( obj );
  if ( nn ) {
    Popup_Err ( 0, "All seen machines should be imported!" );
    if ( nn == 1 ) {
      valOrd_gset2 ( &cc1, 1 );
      sprintf ( post_process_xterm_text,"\n    Seen machine\n      %s\n    is not imported\n", GetShortName ( cc1 ) );
    }
    else {
       strcpy ( post_process_xterm_text,"\n    The following seen machines are not imported:\n" );
      while ( nn ) {
        valOrd_gset2 ( &cc1, nn );
        strcat ( post_process_xterm_text, "      " );
        strcat ( post_process_xterm_text, GetShortName ( cc1 ) );
        strcat ( post_process_xterm_text,"\n" );
        nn--;
      }
   }
    strcat ( post_process_xterm_text, "\n  Linking of " );
    strcat ( post_process_xterm_text, GetShortName ( obj ) );
    strcat ( post_process_xterm_text, " aborted\n" );
    DisplayChanged = 1;
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
    InvokeB ( with_XTerm, 1 );
    return;
  }

  strcpy ( fifo_write_buf, "(" );
  strcat ( fifo_write_buf, GetName ( obj ) );
  strcat ( fifo_write_buf, "|" );
  get_topabs ( &cc2, obj );
  strcat ( fifo_write_buf, GetName ( cc2 ) );
  strcat ( fifo_write_buf, "|" );
  get_recipt_mchlist ( &rr, obj );
  chk_rep ( rr, 76 );
  Cat_gset_tcp ( 1 );
  strcat ( fifo_write_buf, "):" );
  CreNumInBuf ( fifo_write_buf, BT_LNK_WITH_IPT );
  Cre_tcp_env ();
  {
    int Prog_Language_Option;
    valIth_flags ( &Prog_Language_Option, Prog_Language_Option_num );
     strcpy ( xterm_title, "B-Linker" );
  }
  
#ifdef BOOSTER_VERSION
  Check_SSTL_Compile_Generic ( obj );
  BOOSTER_link = obj;
#endif /* BOOSTER_VERSION */
  InvokeB ( with_XTerm, 1 );
}

#ifdef BOOSTER_VERSION
Check_SSTL_Compile_Generic ( int obj )
{
  struct stat stat_buf;
  char sstl_buf [ 250 ];

  strcpy ( sstl_buf, "CDE/C/" );
  strcat ( sstl_buf, GetShortName ( obj ) );
  sstl_buf [ strlen ( sstl_buf ) - 7 ] = '\0';
  strcat ( sstl_buf, "DcrModify_Generic1.c" );
/***
printf ( "Check_SSTL_Compile_Generic - checking for %s\n", sstl_buf );
***/
  if ( stat ( sstl_buf, &stat_buf ) != -1 ) {
    strcpy ( sstl_buf, "\n  Compiling " );
    strcat ( sstl_buf, GetShortName ( obj ) );
    sstl_buf [ strlen ( sstl_buf ) - 7 ] = '\0';
    strcat ( sstl_buf, "DcrModify_Generic1 ... " );
    DisplayCurrWinText ( sstl_buf );
    strcpy ( sstl_buf, "cd CDE/C ; gcc -c -D_BT_ANSIC " );
    strcat ( sstl_buf, GetShortName ( obj ) );
    sstl_buf [ strlen ( sstl_buf ) - 7 ] = '\0';
    strcat ( sstl_buf, "DcrModify_Generic1.c" );
/***
printf ( "executing `%s'\n\n", sstl_buf );
***/
    execute ( sstl_buf );
    DisplayCurrWinText ( "done\n");
  }

  strcpy ( sstl_buf, "CDE/C/" );
  strcat ( sstl_buf, GetShortName ( obj ) );
  sstl_buf [ strlen ( sstl_buf ) - 7 ] = '\0';
  strcat ( sstl_buf, "OpcodesIo_Generic.c" );
/***
printf ( "Check_SSTL_Compile_Generic - checking for %s\n", sstl_buf );
***/
  if ( stat ( sstl_buf, &stat_buf ) != -1 ) {
    strcpy ( sstl_buf, "\n  Compiling " );
    strcat ( sstl_buf, GetShortName ( obj ) );
    sstl_buf [ strlen ( sstl_buf ) - 7 ] = '\0';
    strcat ( sstl_buf, "OpcodesIo_Generic ... " );
    DisplayCurrWinText ( sstl_buf );
    strcpy ( sstl_buf, "cd CDE/C ; gcc -c -D_BT_ANSIC " );
    strcat ( sstl_buf, GetShortName ( obj ) );
    sstl_buf [ strlen ( sstl_buf ) - 7 ] = '\0';
    strcat ( sstl_buf, "OpcodesIo_Generic.c" );
/***
printf ( "executing `%s'\n\n", sstl_buf );
***/
    execute ( sstl_buf );
    DisplayCurrWinText ( "done\n");
  }

  strcpy ( sstl_buf, "CDE/C/" );
  strcat ( sstl_buf, GetShortName ( obj ) );
  sstl_buf [ strlen ( sstl_buf ) - 7 ] = '\0';
  strcat ( sstl_buf, "_IntegrityCheck.c" );
/***
printf ( "Check_SSTL_Compile_Generic - checking for %s\n", sstl_buf );
***/
  if ( stat ( sstl_buf, &stat_buf ) != -1 ) {
    strcpy ( sstl_buf, "\n  Compiling " );
    strcat ( sstl_buf, GetShortName ( obj ) );
    sstl_buf [ strlen ( sstl_buf ) - 7 ] = '\0';
    strcat ( sstl_buf, "_IntegrityCheck.c ... " );
    DisplayCurrWinText ( sstl_buf );
    strcpy ( sstl_buf, "cd CDE/C ; gcc -c -D_BT_ANSIC " );
    strcat ( sstl_buf, GetShortName ( obj ) );
    sstl_buf [ strlen ( sstl_buf ) - 7 ] = '\0';
    strcat ( sstl_buf, "_IntegrityCheck.c" );
/***
printf ( "executing `%s'\n\n", sstl_buf );
***/
    execute ( sstl_buf );
    DisplayCurrWinText ( "done\n");
  }

}
#endif /* BOOSTER_VERSION */


/*
void
Pre_ExportTLIB ()
{
  int cc, cc1, cc2, cc3, bb, nn, rr, mm, pp, ex;
  char buf [ 100 ];

  cc = Mch_arr [ curr_Mch_arr ] . obj;
  get_botref ( &cc1, cc );
  nn = CheckDuplicateIpt ( cc1 );
  if ( nn ) {
    Popup_Err ( 0, "    Duplicate import!    " );
    while ( nn ) {
      valIth_gseq ( &cc2, nn );
      DisplayCurrWinText ( "\n  " );
      DisplayCurrWinText ( GetShortName ( cc2 ) );
      DisplayCurrWinText ( " is imported by:\n" );
      top_level_dep_cstr = cc2;
      get_dep_cstr ( &rr, cc2 );
      chk_rep ( rr, 41 );
      card_gset1 ( &mm );
      while ( mm ) {
        valOrd_gset1 ( &cc3, mm );
        val_ext ( &ex, cc3 );
        if ( ex == imp ) {
          member_inc_ipt ( &bb, cc3, cc2 );
          if ( bb ) {
            member_gset5 ( &bb, cc3 );
            if ( bb ) {
              DisplayCurrWinText ( "    " );
              DisplayCurrWinText ( GetShortName ( cc3 ) );
              DisplayCurrWinText ( "\n" );
	    }
	  }
	}
        mm--;
      }
      nn--;
    }
    DisplayCurrWinText ( "\n  Export aborted\n" );
    return;
  }

  nn = GetIptWithNoImp ( cc1 );
  if ( nn ) {
    Popup_Err ( 0, "All recursively imported machines should be implemented!" );
    if ( nn == 1 ) {
      valOrd_gset3 ( &cc1, 1 );
      DisplayCurrWinText ( "\n  Imported machine " );
      DisplayCurrWinText ( GetShortName ( cc1 ) );
      DisplayCurrWinText ( "\n  has no (analysed) implementation\n" );
    }
    else {
      DisplayCurrWinText ( "\n  The following imported machines have\n  no (analysed) implementation:\n" );
      MainWinDisp_gset ( 3 );
    }
    DisplayCurrWinText ( "\n  Export aborted\n" );
    return;
  }

  nn = GetSeenWithNoImp ( cc1 );
  if ( nn ) {
    Popup_Err ( 0, "All recursively seen machines should be implemented!" );
    if ( nn == 1 ) {
      valOrd_gset3 ( &cc1, 1 );
      DisplayCurrWinText ( "\n  Seen machine " );
      DisplayCurrWinText ( GetShortName ( cc1 ) );
      DisplayCurrWinText ( "\n  has no (analysed) implementation\n" );
    }
    else {
      DisplayCurrWinText ( "\n  The following seen machines have\n  no (analysed) implementation:\n" );
      MainWinDisp_gset ( 3 );
    }
    DisplayCurrWinText ( "\n  Export aborted\n" );
    return;
  }

  nn = GetSeenNotIpt ( cc1 );
  if ( nn ) {
    if ( nn == 1 ) {
      valOrd_gset2 ( &cc1, 1 );
      DisplayCurrWinText ( "\n  Warning - SEEN machine " );
      DisplayCurrWinText ( GetShortName ( cc1 ) );
      DisplayCurrWinText ( " is not IMPORTED\n" );
    }
    else {
      DisplayCurrWinText ( "\n  Warning - the following SEEN machines are not IMPORTED:\n\n" );
      MainWinDisp_gset ( 2 );
    }
  }

  clear_gset5 ();
  card_gset2 ( &nn );         /? seen not ipt copied into gset5 ?/
  while ( nn ) {
    valOrd_gset2 ( &cc2, nn );
    member_gset5 ( &bb, cc2 );
    if ( ! bb ) {
      add_gset5 ( &rr, cc2 );
/? rr=0; ?/
      chk_rep ( rr, 99 );
    }
    nn--;
  }

  strcpy ( fifo_write_buf, "(" );
  CatFullConstructName_fifo_write_buf ( cc );
  strcat ( fifo_write_buf, "|" );
  get_botref ( &cc1, cc );
  CatFullConstructName_fifo_write_buf ( cc1 );
  strcat ( fifo_write_buf, "|?" );
  card_sees_uses ( &nn, cc );         /? seen by mch ?/
  while ( nn ) {
    valOrd_sees_uses ( &cc2, cc, nn );
    strcat ( fifo_write_buf, "," );
    CatFullConstructName_fifo_write_buf ( cc2 );
    nn--;
  }
  strcat ( fifo_write_buf, "|?" );
  card_inc_ipt ( &nn, cc1 );         /? ipt by imp ?/
  while ( nn ) {
    valOrd_inc_ipt ( &cc2, cc1, nn );
    strcat ( fifo_write_buf, "," );
    CatFullConstructName_fifo_write_buf ( cc2 );
    nn--;
  }

  get_recipt_mchlist ( &rr, cc1 );
  chk_rep ( rr, 97 );
  strcat ( fifo_write_buf, "|" );
  Cat_gset_tcp ( 1 );

  strcat ( fifo_write_buf, "|" );
  Cat_gset_tcp ( 5 );         /? seen/not ipt list ?/

  /???
  check seen by mch is a superset of seen/not ipt list (gset5)
  ???/
  clear_gset4 ();
  card_gset5 ( &nn );
  while ( nn ) {
    valOrd_gset5 ( &cc2, nn );
    member_sees_uses( &bb, cc, cc2 );
    if ( ! bb ) {
      member_gset4 ( &bb, cc2 );
      if ( ! bb ) {
        add_gset4 ( &rr, cc2 );
        chk_rep ( rr, 98 );
      }
    }
    nn--;
  }
  card_gset4 ( &nn );
  if ( nn ) {
    DisplayCurrWinText ( "\n  Error - all design SEEN machines which are not IMPORTED\n          should be SEEN by the specification " );
    DisplayCurrWinText ( GetShortName ( cc ) );
    DisplayCurrWinText ( ":\n");
    while ( nn ) {
      valOrd_gset4 ( &cc2, nn );
      DisplayCurrWinText ( "\n              " );
      DisplayCurrWinText ( GetShortName ( cc2 ) );
      nn--;
    }
    DisplayCurrWinText ( "\n\n  Export aborted\n" );
    Popup_Err ( 0, "All non-imported design machines should be seen by the specification!" );
    return;
  }
  strcat ( fifo_write_buf, "):" );
  CreNumInBuf ( fifo_write_buf, BT_EXP );
  strcat ( fifo_write_buf, ":0" );
  InvokeB ( without_XTerm, 1 );
}
*/


void
Remove_non_doc_gset1 ()
{
  int nn, cc, bb, ext;

  card_gset1 ( &nn );
  while ( nn ) {
    valOrd_gset1 ( &cc, nn );
    val_ext ( &ext, cc );
    if ( ext != doc ) {
      del_gset1( cc );
/***
printf("removing %d\n",cc);
***/
    }
    nn--;
  }
}

void
ModifyGlobalPMDOpenFromBed ()
{
  FILE * Bed;

  int nn, c;
  Bed = fopen ( ".Bed", "r" );
  if ( Bed == NULL ) {
    AbortedMsgFile ( "\".Bed\" for reading" );
    BT_err_exit ( 0 );
    return;
  }
  nn = 0;
  c = getc ( Bed );
  while ( c != '\n' && c != EOF ) {
    nn = ( ( nn * 10 ) + c - '0' );
    c = getc ( Bed );
  }
  fclose ( Bed );
  global_pmd_ps = nn;
/***
printf("mch_num: %d, .Bed: %d\n",mch_num,nn);
system("cat .Bed");
***/
}


void
ModifyCurrentPMDOpenFromBed ()
{
  FILE * Bed;

  int nn, c;
  Bed = fopen ( ".Bed", "r" );
  if ( Bed == NULL ) {
    AbortedMsgFile ( "\".Bed\" for reading" );
    BT_err_exit ( 0 );
    return;
  }
  nn = 0;
  c = getc ( Bed );
  while ( c != '\n' && c != EOF ) {
    nn = ( ( nn * 10 ) + c - '0' );
    c = getc ( Bed );
  }
  fclose ( Bed );
  current_pmd_ps = nn;
/***
printf("mch_num: %d, .Bed: %d\n",mch_num,nn);
system("cat .Bed");
***/
}

void
ModifyAnmExeOpenFromBed ()
{
  FILE * Bed;

  int nn, c;
  Bed = fopen ( ".Bed", "r" );
  if ( Bed == NULL ) {
    AbortedMsgFile ( "\".Bed\" for reading" );
    BT_err_exit ( 0 );
    return;
  }
  nn = 0;
  c = getc ( Bed );
  while ( c != '\n' && c != EOF ) {
    nn = ( ( nn * 10 ) + c - '0' );
    c = getc ( Bed );
  }
  fclose ( Bed );
  anm_exe_ps = nn;
/***
printf("mch_num: %d, .Bed: %d\n",mch_num,nn);
system("cat .Bed");
***/
}

void
Modify_sc_psFromBed ()
{
  FILE * Bed;

  int nn, c;
  Bed = fopen ( ".Bed", "r" );
  if ( Bed == NULL ) {
    AbortedMsgFile ( "\".Bed\" for reading" );
    BT_err_exit ( 0 );
    return;
  }
  nn = 0;
  c = getc ( Bed );
  while ( c != '\n' && c != EOF ) {
    nn = ( ( nn * 10 ) + c - '0' );
    c = getc ( Bed );
  }
  fclose ( Bed );
  sc_ps = nn;
/***
printf("mch_num: %d, .Bed: %d\n",mch_num,nn);
system("cat .Bed");
***/
}



void
Pre_ChangeToNewDirectory ()
{
  void DisplayNewEnv ();

  CloseAllPriorCD ();
  DisplayNewEnv ( main_env );
  Save_n_CfgDepBase ();
  strcpy ( sel_str_arr [ sel_arr_MAX ], DropFinalDir ( cur_dir ) );
/*
  strcpy ( sel_str_arr [ sel_arr_MAX ], cur_dir );
*/
  LoadWritableDirInto_sel_strs ( sel_str_arr [ sel_arr_MAX ] );

  Popup_Selection_Sel_flag = cd_Selection_sel;
  Popup_Selection_Sel_Dialog ( top_level, sel_str_arr [ sel_arr_MAX ] );
}


KillConstruct ( obj )
int obj;
{
  int SRC_file_exists, tt, st, bb, ext;
  struct stat stat_buf;
  void DisplayUnInsert ();

/***
printf ( "KillConstruct ( obj=%d ) %s\n", obj, GetName ( obj ) );
***/

/***
if ( ! obj ) {
  Popup_Info ( "Attempting to kill obj 0" );
  return;
}
***/

  val_ext ( &ext, obj );
  val_type ( &tt, obj );


  unlink( CFGName );


  if ( tt == bse_gen || tt == enm_gen  || tt == gen_vhdl ||
       tt == itf_gen || tt == prf_gen                       ) {
    sprintf ( buf, "SRC/%s", GetName ( obj ) );
    if ( stat ( buf, &stat_buf ) != -1 ) unlink( buf );
  }

  if ( ext == mch || ext == ref || ext == imp ) {
    CheckUnanalyse ( obj, 1 );
  }
  else if ( ext == doc ) {
    CheckUndoc ( obj );
  }

  def_curMRIState ( &bb, obj );
  if ( bb ) {
    val_curMRIState ( &st, obj );
/***
printf("killing (cur) MRIState object %d\n",st);
***/
    kill_MRIState ( st );
  }
  def_cptMRIState ( &bb, obj );
  if ( bb ) {
    val_cptMRIState ( &st, obj );
/***
printf("killing (cpt) MRIState object %d\n",st);
***/
    kill_MRIState ( st );
  }

  def_curGENState ( &bb, obj );
  if ( bb ) {
    val_curGENState ( &st, obj );
/***
printf("killing (cur) GENState object %d\n",st);
***/
    kill_GENState ( st );
  }
  def_cptGENState ( &bb, obj );
  if ( bb ) {
    val_cptGENState ( &st, obj );
/***
printf("killing (cpt) GENState object %d\n",st);
***/
    kill_GENState ( st );
  }

  kill_Construct ( obj );

  /* MUST do this *after* the unlinking */
  if ( ! ( IsClosed ( obj ) ) ) KillProcess_Modify_ps ( obj );

  DisplayUnInsert ( obj );
}

void
RemoveUnusedLibFiles ( pass )
int pass;
{
  int rr, nn, obj;
  struct stat stat_buf;

  get_unused_lib ( &rr );
  chk_rep ( rr, 12 );
  card_gset1 ( &nn );
  if ( nn ) {
    if ( pass == 4 ) DeSensitize ();
    while ( nn ) {
      valOrd_gset1 ( &obj, nn );
      Load_SRC_CFG_Names ( obj );
      sprintf ( buf, "\n  Removed %s\n", GetName ( obj ) );
      DisplayCurrWinText ( buf );
      KillConstruct ( obj );
      if ( ( stat ( SRCName, &stat_buf ) != -1 ) != 0 ) unlink( SRCName );
      nn--;
    }
  }
  else { /* if ( nn ) */
    if ( pass == 4 ) Popup_Info ( "No unused library constructs to remove!  " );
  }
  if   ( pass ) {
    RemoveUnusedLibFiles ( pass - 1 );
  }
  else {
    DisplayCurrentEnv ();
  }
}

void
RemoveCodeFiles ( obj )
int obj;
{
  int cc, name [ 50 ], ext, bb;

/***
printf ( "RemoveCodeFiles (%s)\n", GetName ( obj ) );
***/

  val_ext ( &ext, obj );
  if ( ext == mch || ext == ref || ext == imp ) {
    get_topabs ( &cc, obj );
  }
  else {
    cc = obj;
  }
  vld_Construct ( &bb, cc );
  if ( bb ) {
    xtr_name( name, cc );
/***
printf("RemoveCodeFiles - name: `%s'\n", ( char * ) name );
***/
    sprintf ( buf, "CDE/C/%s", ( char * ) name );
    unlink ( buf );
/***
printf("`%s'\n",buf);
***/
    if ( ext != itf ) {
      sprintf ( buf, "CDE/C/%s.ldf", ( char * ) name );
      unlink ( buf );
/***
printf("`%s'\n",buf);
***/
      sprintf ( buf, "CDE/C/%s.o", ( char * ) name );
      unlink ( buf );
/***
printf("`%s'\n",buf);
***/
      sprintf ( buf, "CDE/C/%s.g", ( char * ) name );

      unlink ( buf );

/***
printf("`%s' ",buf);
***/
      sprintf ( buf, "HTX/%s.g.html", ( char * ) name );
      unlink ( buf );
/***
printf("`%s'\n",buf);
***/
      sprintf ( buf, "CDE/C/%s.h", ( char * ) name );

      unlink ( buf );

/***
printf("`%s' ",buf);
***/
      sprintf ( buf, "HTX/%s.h.html", ( char * ) name );
      unlink ( buf );
/***
printf("`%s'\n",buf);
***/
      sprintf ( buf, "CDE/C/%s.c", ( char * ) name );

      unlink ( buf );

/***
printf("`%s' ",buf);
***/
      sprintf ( buf, "HTX/%s.c.html", ( char * ) name );
      unlink ( buf );
/***
printf("`%s'\n",buf);
***/


    }
    SetDisplayField_obj_Changed ( obj );
  }

/***
else {printf("RemoveCodeFiles: %d NOT VALID\n",cc); }
***/

}

void
RemoveSinglePOBFiles ( obj, level )
int obj, level;
{
  sprintf ( buf, "POB/%s.%d.po", GetName ( obj ), level );
  unlink ( buf );
/***
printf("RemoveSinglePOBFiles: unlink `%s'\n",buf);
***/
  sprintf ( buf, "POB/%s.%d.prf", GetName ( obj ), level );
  unlink ( buf );
/***
printf("RemoveSinglePOBFiles: unlink `%s'\n",buf);
***/
  sprintf ( buf, "rm -f TEX/%s.%d.prf.*", GetName ( obj ), level );
  system ( buf );
/***
printf("RemoveSinglePOBFiles: `%s'\n",buf);
***/
}

void
RemoveTexFiles ( obj )
int obj;
{
  char buf1 [ MAX_SRCName + 15 ];
  int ext;

  val_ext ( &ext, obj );
  strcpy ( str_buf, GetName ( obj ) );

/***
printf("RemoveTexFiles - name: `%s'\n", str_buf );
***/

  sprintf ( buf, "TEX/_%s.tex", str_buf );
  unlink ( buf );
/***
printf("`%s'\n",buf);
***/
  sprintf ( buf, "TEX/%s.dvi", str_buf );
  unlink ( buf );
/***
printf("`%s'\n",buf);
***/
  sprintf ( buf, "TEX/%s.idx", str_buf );
  unlink ( buf );
/***
printf("`%s'\n",buf);
***/
  sprintf ( buf, "TEX/%s.idx", str_buf );
  unlink ( buf );
/***
printf("`%s'\n",buf);
***/

  if ( ext == doc ) {
    sprintf ( buf, "TEX/%s.aux", str_buf );
    unlink ( buf );
/***
printf("`%s'\n",buf);
***/
    sprintf ( buf, "TEX/%s.log", str_buf );
    unlink ( buf );
/***
printf("`%s'\n",buf);
***/
    sprintf ( buf, "TEX/%s.toc", str_buf );
    unlink ( buf );
/***
printf("`%s'\n",buf);
***/
  }
}

void
CopyCFGSRC ()
{
  sprintf ( buf, "cp %s %s", CFGName, SRCName );
  execute ( buf );
}

void
CopySRCCFG ()
{
  sprintf ( buf, "cp %s %s", SRCName, CFGName );
  execute ( buf );
}

void
CheckUnanalyse ( obj, nn )
int obj, nn;
{
  int name [ 50 ], ext, type;
  int bb, st, len_pob;

/***
printf( "CheckUnanalyse ( obj=%d nn=%d ) %s %s\n", obj, nn, GetShortName ( obj ), GetName ( obj ) );
***/
  val_mand ( name, &ext, &type, obj );
  val_curMRIState ( &st, obj );
/***
printf( "st %d\n", st );
***/
  val_anl ( &bb, st );
  if ( bb ) {

    /***
    remove .anl file
    ***/
    sprintf ( buf, "ANL/%s.anl", GetName ( obj ) );
    unlink ( buf );
/***
printf("`%s'\n",buf);
***/

    /***
    remove .typ file
    ***/
    sprintf ( buf, "TYP/%s.mri.typ", GetShortName ( obj ) );
    unlink ( buf );
/***
printf("`%s'\n",buf);
***/
    sprintf ( buf, "TYP/%s.imp.typ", GetShortName ( obj ) );
    unlink ( buf );
/***
printf("`%s'\n",buf);
***/

    /***
    remove all POB (TEX) files
    ***/
    length_pob ( &len_pob, st );
/***
printf( "length_pob %d\n", len_pob );
***/
    if ( len_pob ) {
      len_pob--;
      while ( len_pob ) {
        sprintf ( buf, "rm -f POB/%s.p*.%d", GetName ( obj ), len_pob );
        execute ( buf );
/***
printf("`%s'\n",buf);
***/
        sprintf ( buf, "rm -f TEX/%s.p*.%d", GetName ( obj ), len_pob );
        execute ( buf );
/***
printf("`%s'\n",buf);
***/
        len_pob--;
      }
      sprintf ( buf, "rm -f POB/%s.p*", GetName ( obj ), len_pob );
      execute ( buf );
/***
printf("`%s'\n",buf);
***/
      sprintf ( buf, "rm -f TEX/%s.p*", GetName ( obj ), len_pob );
      execute ( buf );
/***
printf("`%s'\n",buf);
***/
    }

    /***
    remove Tex files
    ***/
    RemoveTexFiles ( obj );

    /***
    remove Html file
    ***/
    sprintf ( buf, "HTX/%s.html", GetName ( obj ) );
    unlink ( buf );
/***
printf("`%s'\n",buf);
***/
    HtmlMasterFileChanged = 1;

    /***
    remove code files
    ***/

    if ( ext == imp || type == lib ) RemoveCodeFiles ( obj );

    unanalyse ( obj, nn );
/***
printf( "unanalyse ( %s %d )\n", name, nn );
***/

    SetDisplayField_obj_Changed ( obj );
  }
}


void
CheckUndoc ( obj )
int obj;
{
  int ext, bb, st;

  val_ext ( &ext, obj );
  val_curMRIState ( &st, obj );
  val_dmu ( &bb, st );
  if ( bb ) {
    RemoveTexFiles ( obj );
    mod_dmu ( st, FALSE );
    if ( ext == doc ) {
      def_sees_uses ( &bb, obj );
      if ( bb ) rem_sees_uses ( obj );
    }
/***
printf("undoc %s\n", GetName ( obj ) );
***/

    SetDisplayField_obj_Changed ( obj );
  }
}

void
CheckUngen ( obj )
int obj;
{
  int ext, cc1, bb, st;

  val_ext ( &ext, obj );
  val_curGENState ( &st, obj );
/***
PrintBase;
printf ( "CheckUngen %s\n", GetName ( obj ) );
***/
  switch ( ext ) {
  case bse:
    val_gen1 ( &bb, st );
/***
printf ( "val_gen1 %d ", bb );
***/
    if ( bb ) {
      mod_gen1 ( st, FALSE );
    }
    val_gen2 ( &bb, st );
/***
printf ( "val_gen2 %d\n", bb );
***/
    if ( bb ) {
      mod_gen2 ( st, FALSE );
    }
    /*    RemoveBaseOpsGeneratedConstructs ( obj ); */
    break;
  case ops:
    val_gen_by ( &cc1, obj );
    val_curGENState ( &st, cc1 );
    val_gen2 ( &bb, st );
    if ( bb ) {
      mod_gen2 ( st, FALSE );
      SetDisplayField_obj_Changed ( cc1 );
    }
    break;
  case enm:
    val_gen1 ( &bb, st );
    if ( bb ) {
      mod_gen1 ( st, FALSE );
      def_sees_uses ( &bb, obj );
      if ( bb ) {
        rem_sees_uses ( obj );
      }
      RemoveCodeFiles ( obj );
    }
    break;
  case itf:
    val_gen1 ( &bb, st );
    if ( bb ) {
      mod_gen1 ( st, FALSE );
      def_sees_uses ( &bb, obj );
      if ( bb ) {
        rem_sees_uses ( obj );
      }
    }
    val_gen2 ( &bb, st );
    if ( bb ) {
      mod_gen2 ( st, FALSE );
      val_cptGENState ( &st, obj );
      val_gen2 ( &bb, st );
      if ( bb ) {
        mod_gen2 ( st, FALSE );
      }
    }
    RemoveCodeFiles ( obj );
    break;
  }
/***
;printf("ungen %s\n",name);
***/

  SetDisplayField_obj_Changed ( obj );
}


void
RemoveConstruct ( obj, rm_flag )
int obj, rm_flag;
{
  FILE * Bsrc;
  int SRC_file_exists, file_diff, tt, ext;
  struct stat stat_buf;

/***
printf ( "RemoveConstruct ( obj=%d (%s), rm_flag=%d )\n",
                                              obj, GetName ( obj ), rm_flag );
***/

  Load_SRC_CFG_Names ( obj );

  val_type ( &tt, obj );
  val_ext ( &ext, obj );
  
  SRC_file_exists = ( ( stat ( SRCName, &stat_buf ) != -1 ) != 0 );

  if ( ( tt == usr || tt == usr_vhdl ) &&
         ext != itf                    &&
         SRC_file_exists                  ) {
    file_diff = FileDiffIntoBcom ( obj );
    if ( file_diff ) {
      strcpy ( primary_string, GetName ( obj ) );
      Popup_RemoveEditedFile ( top_level );
    }
    else {     /* no file_diff */
      sprintf ( buf, "\n  Removed %s - copied into SRC\n", GetName ( obj ) );
      DisplayCurrWinText ( buf );
      KillConstruct ( obj );
      RemoveNext ();
    }
  }
  else {      /* not usr or itf or SRC file doesn't exist */
    if ( SRC_file_exists ) {
      unlink( SRCName );
    }
    sprintf ( buf, "\n  Removed %s", GetName ( obj ) );
    DisplayCurrWinText ( buf );
    if ( ( tt == usr || tt == usr_vhdl )  &&
           ext != itf                        ) {
      CopyCFGSRC ();
    DisplayCurrWinText ( " - copied into SRC" );      
    }
    DisplayCurrWinText ( "\n" );
    if ( rm_flag ) DisplayCurrWinText ( "  and its dependent constructs\n" );
/***
else { printf("%s not usr type - not copied to SRC\n", GetName ( obj ) ); }
***/
    KillConstruct ( obj );
    RemoveNext ();
  }
}


void
RemoveNext ()
{
  int cc, ext, rr, nn, mm, bb;

  while ( ! sel_arr_tog [ remove_count ] &&
          remove_count < sel_arr_tot    ) {
    remove_count++;
  }
  if ( remove_count < sel_arr_tot ) {
    /***
    check it hasn't already been removed through dependency
    ***/
    vld_Construct ( &bb, sel_obj_arr [ remove_count ] );
    if ( bb ) {
/***
printf ( "RemoveNext: %s %s\n",
       sel_str_arr [ remove_count ], GetName ( sel_obj_arr [ remove_count ] ) );
***/
      Load_SRC_CFG_Names ( sel_obj_arr [ remove_count ] );
      top_level_dep_cstr = sel_obj_arr [ remove_count ];
      Get_Code_Dep ( sel_obj_arr [ remove_count ] );
      card_gset5 ( &mm );
      top_level_dep_cstr = sel_obj_arr [ remove_count ];
      get_dep_cstr ( &rr, sel_obj_arr [ remove_count ] );
      chk_rep ( rr, 4 );
      if ( IsPrfObj ( sel_obj_arr [ remove_count ] ) ) {
        /***
        leave only docs - the mch/ref/imp is shown as a dep! (& all the rest)
        ***/
        clear_gset2 ();
        card_gset1 ( &nn );
        while ( nn ) {
          valOrd_gset1 ( &cc, nn );
/***
printf ( ">>> %s\n", GetName ( cc ) );
***/
          val_ext ( &ext, cc );
          if ( ext == doc ) {
            add_gset2 ( &rr, cc );
            chk_rep ( rr, 239 );
	  } 
          nn--;
	}
        clear_gset1 ();
        card_gset2 ( &nn );
        while ( nn ) {
          valOrd_gset2 ( &cc, nn );
          add_gset1 ( &rr, cc );
          chk_rep ( rr, 240 );
          nn--;
	}
        /***
        clear code dependencies
        ***/
        clear_gset5 ();
        mm = 0;
      }
      card_gset1 ( &nn );
      if ( ( nn == 0 ) && ( mm == 0 ) ) {
        if ( IsPrfObj ( sel_obj_arr [ remove_count ] ) ) {
          void RemoveProofObj ();
          RemoveProofObj ( sel_obj_arr [ remove_count ], 0 );
	  remove_count++;
          RemoveNext ();
	}
        else {
          RemoveConstruct ( sel_obj_arr [ remove_count ], 0 );  /* no dep */
	  remove_count++;
	}
      }
      else {             /* dependencies */
        int tt;
        val_type ( &tt, sel_obj_arr [ remove_count ] );
        sprintf ( buf, "\n    %s - Dependent constructs:\n",
                                       GetName ( sel_obj_arr [ remove_count ] ) );
        DisplayCurrWinText ( buf );
        MainWinDisp_gset ( 1 );
        MainWinDispCode_gset ( 5 );
        if ( tt == lib || tt == enm_gen ) {
          sprintf ( buf, "      %s.o (object code)\n",
                                       GetName ( sel_obj_arr [ remove_count ] ) );
          DisplayCurrWinText ( buf );
	}
        sprintf ( primary_string, "Proceed with removal of %s?",
                                       GetName ( sel_obj_arr [ remove_count ] ) );
        strcpy ( secondary_string, "Dependent construct processing will be lost" );
        confirm_flag = radiobox_flag;
        curr_obj = sel_obj_arr [ remove_count ];
        remove_count++;
        Popup_ConfirmDialog ( top_level );
      }
    }
    else {         /* already been removed through dependency */
      remove_count++;
      RemoveNext ();
    }
  }
  else {  /* if ( remove_count < sel_arr_tot ) */
    radiobox_flag = 0;
    DisplayCurrentEnv ();
  }
}


void
RemoveLevel ( obj ) /* Revert to previous proof level */
int obj;
{
  int st, ext, nn, ppf_card, bb, prf_obj;

  val_curMRIState ( &st, obj );
  pop_pob( st );
  length_pob ( &nn, st );
  RemoveSinglePOBFiles ( obj, nn );
  member_ppf ( &bb, st, nn );
  if ( bb ) {
    del_ppf ( st, nn );
    del_ppf_dmu ( st, nn );
    val_ext ( &ext, obj );
    switch ( ext ) {
    case mch:
      GetPrfObjFromNameExtLvl ( &prf_obj, GetShortName ( obj ), mch_prf, nn - 1, 1 );
      break;
    case ref:
      GetPrfObjFromNameExtLvl ( &prf_obj, GetShortName ( obj ), ref_prf, nn - 1, 1 );
      break;
    case imp:
      GetPrfObjFromNameExtLvl ( &prf_obj, GetShortName ( obj ), imp_prf, nn - 1, 1 );
      break;
    }
    Load_SRC_CFG_Names ( prf_obj );
/***
printf ( "KillConstruct %s\n", GetName ( prf_obj ) );
***/
    KillConstruct ( prf_obj );
  }
}

void
RemoveProofAtLevel ( obj, level )
int obj, level;
{
  /***
  Remove All Proofs for a single object at level
  if level = 0 (i. first level of proof):
    rm ....1.po                   (will exist only if unproved left)
    rm ....prf.0 TEX/....prf.0.*
    if proof printed, ppf (and maybe ppf_dmu) will contain 1 (not 0)
      GetPrfObjFromNameExtLvl from level 0
  ***/

  int st, bb, ext, prf_obj;

/***
sprintf ( buf, "\n  RemoveProofAtLevel ( obj=%d, level=%d )\n", obj, level );
DisplayCurrWinText ( buf );
sprintf ( buf, "  RemoveProofAtLevel: %s at %d\n", GetName ( obj ), level );
DisplayCurrWinText ( buf );
sprintf ( buf, "  rm -f POB/%s.%d.po\n", GetName ( obj ), level + 1 );
DisplayCurrWinText ( buf );
sprintf ( buf, "  rm -f POB/%s.%d.prf\n", GetName ( obj ), level );
DisplayCurrWinText ( buf );
sprintf ( buf, "  rm -f TEX/%s.%d.prf.*\n", GetName ( obj ), level );
DisplayCurrWinText ( buf );
val_curMRIState ( &st, obj );
member_ppf ( &bb, st, level + 1 );
if ( bb ) {
  DisplayCurrWinText ( "  member_ppf\n" );
  val_ext ( &ext, obj );
  switch ( ext ) {
  case mch:
    GetPrfObjFromNameExtLvl ( &prf_obj, GetShortName ( obj ), mch_prf, level, 1 );
    break;
  case ref:
    GetPrfObjFromNameExtLvl ( &prf_obj, GetShortName ( obj ), ref_prf, level, 1 );
    break;
  case imp:
    GetPrfObjFromNameExtLvl ( &prf_obj, GetShortName ( obj ), imp_prf, level, 1 );
    break;
  }
  sprintf ( buf, "  about to kill proof object %s %d\n",
                                                   GetName ( prf_obj ), prf_obj );
  DisplayCurrWinText ( buf );
}
return;
***/

/***
printf ( "RemoveProofAtLevel ( obj=%d level=%d )\n", obj, level );
***/

  sprintf ( buf, "POB/%s.%d.po", GetName ( obj ), level + 1 );
  unlink ( buf );
  sprintf ( buf, "POB/%s.%d.prf", GetName ( obj ), level );
  unlink ( buf );
  sprintf ( buf, "rm -f TEX/%s.%d.prf.*", GetName ( obj ), level );
  system ( buf );

  val_curMRIState ( &st, obj );
  member_ppf ( &bb, st, level + 1 ); /* ppf is one more than level */
  if ( bb ) {
    del_ppf ( st, level + 1 );
    del_ppf_dmu ( st, level + 1 );
    val_ext ( &ext, obj );
    switch ( ext ) {
    case mch:
      GetPrfObjFromNameExtLvl ( &prf_obj, GetShortName ( obj ), mch_prf, level, 1 );
      break;
    case ref:
      GetPrfObjFromNameExtLvl ( &prf_obj, GetShortName ( obj ), ref_prf, level, 1 );
      break;
    case imp:
      GetPrfObjFromNameExtLvl ( &prf_obj, GetShortName ( obj ), imp_prf, level, 1 );
      break;
    }
    Load_SRC_CFG_Names ( prf_obj );
/***
printf ( "                                       - KillConstruct %d %s\n",
                                                    prf_obj, GetName ( prf_obj ) );
***/
    KillConstruct ( prf_obj );
  }
  pop_pob( st ); /* leave cpt! */
}

void
PreOpenConstruct ( obj )
int obj;
{
  int diff;
  struct stat stat_buf;
  void OpenConstruct ();

  Load_SRC_CFG_Names ( obj );
  if ( stat ( SRCName, &stat_buf ) == -1 ) {  /*** SRC file not exist ***/
    CopyCFGSRC ();
    OpenConstruct ( obj );
  }
  else {                                      /*** SRC file exists ...  ***/
    diff = FileDifference ( SRCName, CFGName );
    if ( ! diff ) {                           /*** ... but is identical ***/
      OpenConstruct ( obj );
    }
    else {                                    /*** ... and is different ***/
      strcpy ( primary_string, GetName ( obj ) );
      curr_obj = obj;
      Popup_OpenEditedFile ( top_level );
    }
  }
}

void
OpenConstruct ( obj )
int obj;
{
  FILE * Bed;
  int nn, c;
  void Modify_ps ();
  char* editorCommand;

  printf("OpenConstruct ( %d ) \n", obj);

  Retrieve_String ( editor_str_num, buf );
  
  printf("editor_str = %s SRCNAME = %s\n", buf,SRCName);
  
  /* - use more intelligent command line caller for editors: */
  /*
  sprintf ( primary_string, "%s %s  & \n echo $! > .Bed", buf, SRCName );
  execute ( primary_string );
  */
  
  editorCommand=getEditorCommandLine(buf,SRCName);
  
  printf("%s & \n echo $! > .Bed\n", editorCommand);
  
  sprintf ( primary_string, "%s & \n echo $! > .Bed", editorCommand);
  
  free(editorCommand);
  
  printf("freed editorCommand at %p",editorCommand);
  
  execute ( primary_string );
 
  printf("ran editor command\n");

  Bed = fopen ( ".Bed", "r" );
  if ( Bed == NULL ) {
    AbortedMsgFile ( "\".Bed\" for reading" );
    
     printf("couldnt open .Bed for reading. exiting.\n");
    
    BT_err_exit ( 0 );
    return;
  }
  nn = 0;
  c = getc ( Bed );
  while ( c != '\n' && c != EOF ) {
    nn = ( ( nn * 10 ) + c - '0' );
    c = getc ( Bed );
  }
  fclose ( Bed );
  unlink ( ".Bed" );
  Modify_ps ( obj, nn );
}

int
DetermineCommitType ( obj )
int obj;
{
  /***
  SRC file must parse!!!
  ***/

  int maths_change, no_comment_src, no_comment_cfg; 
  int rr, nn, type, src_f, cfg_f;

  Load_SRC_CFG_Names ( obj );

  val_type ( &type, obj );
  if ( type == prf_gen ) {
    sprintf ( buf, "$BKIT/BLIB/LatexProofFilter 0 < %s > .BBBcom", SRCName );
    execute ( buf );
    mod_name_fil_from_btoolkit ( ".BBBcom" );
  }
  else {
    mod_name_fil_from_btoolkit ( SRCName );
  }
/***
printf ( "src name_fil=`%s'\n", SRCName );
***/
  src_f = read_file_frmfunc();

  if ( type == prf_gen ) {
    sprintf ( buf, "$BKIT/BLIB/LatexProofFilter 0 < %s > .BBBcom", CFGName );
    execute ( buf );
    mod_name_fil_from_btoolkit ( ".BBBcom" );
  }
  else {
    mod_name_fil_from_btoolkit ( CFGName );
  }
/***
printf ( "cfg name_fil=`%s'\n", CFGName );
***/
  cfg_f = read_file_frmfunc();

  if ( ! cfg_f ) {
    sprintf ( buf, "\n  %s no longer parses!\n\n", CFGName );
    DisplayCurrWinText ( buf );
    printf ( buf );
    AbortedMsg ();
    BT_err_exit ( 0 );
  }
  if ( ! src_f ) {
    sprintf ( buf, "\n  %s no longer parses!\n\n", SRCName );
    DisplayCurrWinText ( buf );
    printf ( buf );
    AbortedMsg ();
    BT_err_exit ( 0 );
  }

  if ( ! ( eql_frm_from_btoolkit ( src_f, cfg_f ) ) ) {
    kil_from_btoolkit ( src_f );
    kil_from_btoolkit ( cfg_f );
    return ( commit_type_maths );
  }

  kil_from_btoolkit ( src_f );
  kil_from_btoolkit ( cfg_f );

  /*** so it's not a maths change ***/

  if ( type == prf_gen ) {
    strcpy ( buf, "$BKIT/BLIB/LatexProofFilter 0 < " );
    strcat ( buf, SRCName );
    strcat ( buf,  " > .BBBcom" );
    execute ( buf );
    PrintAnnotOnly ( ".BBBcom", ".Bcom" );
  }
  else {
    PrintAnnotOnly ( SRCName, ".Bcom" );
  }

  if ( type == prf_gen ) {
    strcpy ( buf, "$BKIT/BLIB/LatexProofFilter 0 < " );
    strcat ( buf, CFGName );
    strcat ( buf,  " > .BBBcom" );
    execute ( buf );
    PrintAnnotOnly ( ".BBBcom", ".BBcom" );
  }
  else {
    PrintAnnotOnly ( CFGName, ".BBcom" );
  }

/***
printf("--------- PrintAnnotOnly .Bcom --------\n");
system ( "cat .Bcom" );
printf("\n--------- PrintAnnotOnly .BBcom -------\n");
system ( "cat .BBcom" );
printf("\n------------------------\n");
***/

  if ( FileDifference ( ".Bcom", ".BBcom" ) ) {
    return ( commit_type_annot );
  }
  else {

  /*** it might be an annotational formatting change ***/

    if ( type == prf_gen ) {
      strcpy ( buf, "$BKIT/BLIB/LatexProofFilter 0 < " );
      strcat ( buf, SRCName );
      strcat ( buf,  " > .BBBcom" );
      execute ( buf );
      PrintCommentOnly ( ".BBBcom", ".Bcom" );
    }
    else {
      PrintCommentOnly ( SRCName, ".Bcom" );
    }

    if ( type == prf_gen ) {
      strcpy ( buf, "$BKIT/BLIB/LatexProofFilter 0 < " );
      strcat ( buf, CFGName );
      strcat ( buf,  " > .BBBcom" );
      execute ( buf );
      PrintCommentOnly ( ".BBBcom", ".BBcom" );
    }
    else {
      PrintCommentOnly ( CFGName, ".BBcom" );
    }

/***
printf("--------- PrintCommentOnly .Bcom --------\n");
system ( "cat .Bcom" );
printf("\n--------- PrintCommentOnly .BBcom -------\n");
system ( "cat .BBcom" );
printf("\n------------------------\n");
***/

    if ( FileDifference ( ".Bcom", ".BBcom" ) ) {
      return ( commit_type_ws );
    }
    else {
      return ( commit_type_assumed_annot );
    }
  }
}

void
CheckAnmThyFileParses ()
{
  sprintf ( fifo_write_buf, "SRC/%s.thy", GetName ( anm_thy_obj ) );
  if ( FileParses ( fifo_write_buf ) ) {
    Popup_Info ( "Theory file parses" );
    sprintf ( buf, "kill -9 %d", anm_thy_ps );
    system ( buf );
    anm_thy_ps = 0;
    sprintf ( fifo_write_buf, "0:%d", BT_SKIP );
    InvokeB ( without_XTerm, 1 );
  }
  else {
    radiobox_flag = close_anm_thy_file;
    Popup_Info ( "Animator theory file does not parse" );
    XtPopup ( temp_dialog, XtGrabNone );
    XmUpdateDisplay ( temp_dialog );
  }
}

void
CheckFileParses ( obj )
int obj;
{
  int type;

  curr_obj = obj;
  Load_SRC_CFG_Names ( obj );

/***
printf ( "CheckFileParses - for |%s| ", SRCName );
***/
  if ( FileParses ( SRCName ) ) {
    file_parses = 1;
/***
printf ( "ok - straight to CheckFileParses_contd\n" );
***/
    CheckFileParses_contd ();
  }
  else {
/***
printf ( "not ok - BT_CK_PARSE\n" );
***/
    unlink ( ".BBcom" );
    sprintf ( fifo_write_buf, "\"%s\":", SRCName );
    val_type ( &type, obj );
    if   ( type == prf_gen ) Cre_fifo_write_buf_cmd_num ( BT_CK_PARSE, 1 );
    else                     Cre_fifo_write_buf_cmd_num ( BT_CK_PARSE, 0 );
    ReturnFromB_option = from_CheckFileParses;
    InvokeB ( without_XTerm, 1 );
  }
}

void
CheckFileParses_contd ()
{
  /***
  curr_obj is set
  ***/

  int ext, type, commit_type_flag;

/***
printf ( "CheckFileParses_contd\n" );
***/

  Load_SRC_CFG_Names ( curr_obj );
  committed = 0;

  val_ext ( &ext, curr_obj );
  val_type ( &type, curr_obj );

  if   ( ! file_parses ) {

    /***
    file doesn't parse
    ***/
    sprintf ( buf, "SRC/%s", GetName ( curr_obj ) );
    display_non_parse_text ( buf );
    sprintf ( buf, "  %s does not parse - not committed\n", GetName ( curr_obj ) );
    DisplayCurrWinText ( buf ); 
    sprintf ( buf, "  %s does not parse - not committed\n", GetName ( curr_obj ) );
    Popup_Info ( buf );
    CheckFileParses_ContinueLoop ();

  }

  else {

    /***
    file parses
    ***/
    commit_type_flag = DetermineCommitType ( curr_obj );

/***
printf ( "commit_type_flag %d\n    (commit_type_maths %d commit_type_annot %d commit_type_assumed_annot %d commit_type_ws %d)\n", commit_type_flag, commit_type_maths, commit_type_annot, commit_type_assumed_annot,commit_type_ws  );
***/

    switch ( commit_type_flag ) {
    case commit_type_maths:
      PreCommitMathsEdits ( curr_obj, ext, type );
      break;
    case commit_type_annot:
    case commit_type_assumed_annot:
      PreCommitAnnotationEdits ( curr_obj, ext, type, commit_type_flag );
      break;
    case commit_type_ws:
      CommitWhitespaceEdits ( curr_obj, ext, type );
      break;
    }
  }
}

void
CheckFileParses_ContinueLoop ()
{
/***
printf ( "CheckFileParses_ContinueLoop\n" );
***/
    switch ( radiobox_flag ) {
    case close_all_radiobox:
      CloseAllOpenFilesNext ();
      break;
    case commit_all_radiobox:
     CommitAllOpenEditedFilesNext ();
      break;
    case commit_all_remake_radiobox:
      CommitAll_Remake_OpenEditedFilesNext ();
      break;
    case file_ed_NML_radiobox:
    case file_ed_POG_radiobox:
    case file_ed_DOC_radiobox:
    case file_ed_DMU_radiobox:
    case file_ed_GBO_radiobox:
    case file_ed_ENM_radiobox:
      file_ed_radiobox_contd ();
      break;
    case file_ed_ITF_radiobox:
      ITF_ed_radiobox_contd ();
      break;
    case mini_remake_radiobox:
      mini_remake_radiobox_contd ();
      break;
    case update_from_src_radiobox:
      ProcessUpdateFromSRC_Next ();
      break;
    default:
      DisplayCurrentEnv ();
      break;

    } /* switch ( radiobox_flag ) */
}

void
PreCommitMathsEdits ( obj, ext, type )
int obj;
int ext;
int type;
{
  int mm, nn, rr;

/***
printf ( "PreCommitMathsEdits - ( obj=%d, ext=%d, type=%d ) %s\n",  obj, ext, type, GetName ( obj ) );
***/

  if ( type == lib || type == lib_vhdl ) {
    Popup_Info ( "    Illegal maths change!  " );
    sprintf ( buf, "\n  %s is a library machine\n", GetName ( obj ) );
    DisplayCurrWinText ( buf );
    return;
  }

  if ( ( ext == mch )                            && 
       ( type == bse_gen || type == itf_gen ||
         type == enm_gen || type == gen_vhdl   )     ) {
    Popup_Info ( "    Illegal maths change!  " );
    sprintf ( buf, "\n  %s is a generated specification\n", GetName ( obj ) );
    DisplayCurrWinText ( buf );
    return;
  }

  if ( type == prf_gen ) {
    Popup_Info ( "    Illegal change in proof file!  " );
    sprintf ( buf, "\n  %s is a generated proof\n", GetName ( obj ) );
    DisplayCurrWinText ( buf );
    return;
  }

  top_level_dep_cstr = obj;
  Get_Code_Dep ( obj );
  card_gset5 ( &mm );
  top_level_dep_cstr = obj;
  get_dep_cstr ( &rr, obj );
  chk_rep ( rr, 4 );
  sprintf ( buf, "\n    Maths change in %s", GetName ( obj ) );
  DisplayCurrWinText ( buf );
  card_gset1 ( &nn );

  if ( nn == 0 && mm == 0 ) {

    /***
    no dependencies
    ***/
    DisplayCurrWinText ( " (no dependencies)" );
    if ( ext == imp && ( type == bse_gen || type == itf_gen ) ) {
    sprintf ( buf, "\n\n    %s is a generatedimplementation - \n    subsequent translation/linking may fail\n", GetName ( obj ) );
      DisplayCurrWinText ( buf );
      sprintf ( primary_string, "Proceed with %s commit?", GetName ( obj ) );
      strcpy ( secondary_string, "Dependent construct processing will be lost" );
      confirm_flag = radiobox_flag;
      curr_obj = obj;
      Popup_ConfirmDialog ( top_level );
    }
    else {
      CommitMathsEdits ( obj );
    }
  }

    else {

    /***
    dependencies
    ***/
    DisplayCurrWinText ( "\n\n    Dependent constructs:\n" );
    MainWinDisp_gset ( 1 );
    MainWinDispCode_gset ( 5 );
    if ( type == lib || type == enm_gen ) {
      DisplayCurrWinText ( "      " );
      DisplayCurrWinText ( GetShortName ( obj ) );
      DisplayCurrWinText ( ".o (object code)\n" );
    }
    if ( ext == imp && ( type == bse_gen || type == itf_gen ) ) {
    sprintf ( buf, "\n\n    %s is a generated implementation - \n    subsequent translation/linking may fail\n", GetName ( obj ) );
      DisplayCurrWinText ( buf );
    }
    sprintf ( primary_string, "Proceed with %s commit?", GetName ( obj ) );
    strcpy ( secondary_string, "Dependent construct processing will be lost" );
    confirm_flag = radiobox_flag;
    curr_obj = obj;
    Popup_ConfirmDialog ( top_level );

  }

}

int
ItfWarnMessage ()
{
  int nn, cc, found, ext, type;

  /***
  first see if .itf in gset1;
  if so return 0
  ***/
  found = 0;
  card_gset1 ( &nn );  /* dependencies */
  while ( ( ! found ) && ( nn ) ) {
    valOrd_gset1 ( &cc, nn );
    val_ext ( &ext, cc );
    if ( ext == itf ) found = 1;
    nn--;
  }
  if ( found ) return 0;

  /***
  no .itf in gset1;
  see if itf_gen in gset5
  ***/
  found = 0;
  card_gset5 ( &nn );  /* dependencies */
  while ( ( ! found ) && ( nn ) ) {
    valOrd_gset5 ( &cc, nn );
    val_type ( &type, cc );
    if ( type == itf_gen ) val_gen_by ( &found, cc );
    nn--;
  }
  return found;
}

void
CommitMathsEdits ( obj )
int obj;
{
  int ext, type;
  int Preserve_Editor_Option;
  int nn, mm, rr;
  int itf_warn_message_reqd = 0;

/***
printf ( "CommitMathsEdits - %s\n", GetName ( obj ) );
***/

  val_ext ( &ext, obj );
  val_type ( &type, obj );

  CopySRCCFG ();

  valIth_flags ( &Preserve_Editor_Option, Preserve_Editor_Option_num );
  if ( radiobox_flag == close_radiobox     ||
       radiobox_flag == close_all_radiobox    ) {
    unlink( SRCName );
    /* MUST do this *after* the unlinking */
    KillProcess_Modify_ps ( obj );
  }
  else if ( ! Preserve_Editor_Option ) {
    unlink( SRCName );
    /* MUST do this *after* the unlinking */
    KillProcess_Modify_ps ( obj );
  }

  card_gset5 ( &mm ); /* code dependencies */
  card_gset1 ( &nn );  /* dependencies */
  if ( nn || mm ) {  /* dependents */
    if ( ext == imp ) itf_warn_message_reqd = ItfWarnMessage ();
    ResetAllDependents ( obj );
    DisplayCurrWinText ( "\n    Reset dependent constructs" );
  }

  sprintf ( buf, "\n\n  Committed %s\n", GetName ( obj ) );
  DisplayCurrWinText ( buf );

  if ( ext == mch || ext == ref || ext == imp ) {
    CheckUnanalyse ( obj, 1 );
  }
  else if ( ext == doc ) {
    CheckUndoc ( obj );
  }
  else if ( ext == bse || ext == ops || ext == enm  || ext == itf ) {
    CheckUngen ( obj );
  }



  if ( itf_warn_message_reqd ) {
    sprintf ( buf, "\n  If the design has changed, you may need\n  to reset %s\n",
                                               GetName ( itf_warn_message_reqd ) );
    DisplayCurrWinText ( buf );
  }

  committed = 1;
  UnDecorate_SRC_file_newer ( obj );

  CheckFileParses_ContinueLoop ();
}

void
PreCommitAnnotationEdits ( obj, ext, type, commit_type_flag )
int obj;
int ext;
int type;
int commit_type_flag;
{

  int nn, rr;

/***
printf ( "PreCommitAnnotEdits %s\n", GetName ( obj ) );
***/

  if ( commit_type_flag == commit_type_annot )
    sprintf ( buf, "\n    Annotation change in %s", GetName ( obj ) );
  else
    sprintf ( buf, "\n    Assumed annotation change in %s", GetName ( obj ) );

  top_level_dep_cstr = obj;
  get_dep_cstr ( &rr, obj );
  chk_rep ( rr, 4 );
  Remove_non_doc_gset1 ();
  card_gset1 ( &nn );
  if ( nn == 0 ) {
    DisplayCurrWinText ( "\n    No DOCUMENT dependencies\n" );
    CommitAnnotationEdits ( obj, /* reset_dmu_flag = */ 0 );
  }
  else {
    DisplayCurrWinText ( "\n    DOCUMENT-dependent constructs:\n" );
    MainWinDisp_gset ( 1 );
    sprintf ( primary_string, "Proceed with %s commit?", GetName ( obj ) );
    strcpy ( secondary_string,
      "Dependent document construct processing will be lost" );
    confirm_flag = commitD_but_confirm;
    curr_obj = obj;
    Popup_ConfirmDialog ( top_level );
  }
}

void
CommitAnnotationEdits ( obj, reset_dmu_flag )
int obj, reset_dmu_flag;
{
  int cc, ext, type;
  int Preserve_Editor_Option;
  int is_mri, bb, nn, st, is_generated, is_gen_by, is_prf, prf_level;
  int marked_up_own_reset_flag = 0;

/***
printf ( "CommitAnnotEdits %s\n", GetName ( obj ) );
***/

  val_ext ( &ext, obj );
  val_type ( &type, obj );

  is_mri = 0;

  if ( ! reset_dmu_flag ) {

    CopySRCCFG ();

    valIth_flags ( &Preserve_Editor_Option, Preserve_Editor_Option_num );
    if ( ! Preserve_Editor_Option            || 
         radiobox_flag == close_radiobox     ||
         radiobox_flag == close_all_radiobox    ) {
        unlink( SRCName );
      /* MUST do this *after* the unlinking */
      KillProcess_Modify_ps ( obj );
    }
  }

  def_curMRIState ( &bb, obj );
  if ( bb ) {
    is_mri = 1;
    val_curMRIState ( &st, obj );
    val_dmu ( &bb, st );
  }
  else {
    def_curGENState ( &bb, obj );
    if ( bb ) {
      val_curGENState ( &st, obj );
      val_gen_dmu ( &bb, st );
    }
  }
  if ( bb ) { /* dmu */
    if ( is_mri ) {
      mod_dmu ( st, FALSE );
      if ( ext == doc ) {
        def_sees_uses ( &bb, obj );
        if ( bb ) rem_sees_uses ( obj );
      }
    }
    else {
      mod_gen_dmu ( st, FALSE );
    }
    def_sees_uses ( &bb, obj );
    if ( bb ) {
      rem_sees_uses ( obj );
    }
    RemoveTexFiles ( obj );
    SetDisplayField_obj_Changed ( obj );
    marked_up_own_reset_flag = 1;

  }
  else {
    if ( ext == mch_prf || ext == ref_prf || ext == imp_prf ) {
      val_opt ( &is_generated, &is_gen_by, &is_prf, &prf_level, obj );
      val_curMRIState ( &st, is_gen_by );
      member_ppf_dmu ( &bb, st, prf_level );
      if (  bb ) {
        del_ppf_dmu ( st, prf_level );
        RemoveTexFiles ( obj );
        SetDisplayField_obj_Changed ( obj );
        marked_up_own_reset_flag = 1;
      }
    }
  }

  card_gset1 ( &nn );
  if ( nn ) {
    while ( nn ) {  /* document-dependents */
      valOrd_gset1 ( &cc, nn );
      Load_SRC_CFG_Names ( cc );
      val_curMRIState ( &st, cc );
      mod_dmu ( st, FALSE );
      val_ext ( &ext, cc );
      if ( ext == doc ) {
        def_sees_uses ( &bb, cc );
        if ( bb ) {
          rem_sees_uses ( cc );
        }
      }
      RemoveTexFiles ( cc );
      SetDisplayField_obj_Changed ( cc );
      nn--;
    }
    DisplayCurrWinText ( "\n    Reset DOCUMENT-dependent constructs\n" );
  }

  if ( marked_up_own_reset_flag ) {
    sprintf ( buf, "    Marked-up %s document reset\n", GetName ( obj ) );
    DisplayCurrWinText ( buf ); 
  }

  if ( ! reset_dmu_flag ) {
    committed = 1;
  }

  UnDecorate_SRC_file_newer ( obj );

  if ( ! reset_dmu_flag ) {
    if ( ( Is_Anl_MchRefImp ( obj ) ) /* ||
         ( Is_Gen_Bse ( obj ) ) */       ) {
      sprintf ( buf, "    Re-creating %s html file ...", GetName ( obj ) );
      DisplayCurrWinText ( buf );
      curr_obj = obj;
      Cre_fifo_write_buf_cmd_env ( obj, BT_CRE_HTML_WITH_ENV, 0 );
      InvokeB ( without_XTerm, 1 );
    }
    else {
      sprintf ( buf, "\n  Committed %s \n", GetName ( obj ) );
      DisplayCurrWinText ( buf );
      CheckFileParses_ContinueLoop ();
    }
  }
  else {
    DisplayCurrentEnv ();
  }

}


void
CommitWhitespaceEdits ( obj, ext, type )
int obj, ext, type;
{
  int Preserve_Editor_Option;

/***
printf ( "CommitWhitespaceEdits - %s\n", GetName ( obj ) );
***/

  CopySRCCFG ();

  sprintf ( buf, "\n    No mathematical/annotation change in %s", GetName ( obj ) );
  DisplayCurrWinText ( buf );

  valIth_flags ( &Preserve_Editor_Option, Preserve_Editor_Option_num );

  if ( ! Preserve_Editor_Option         || 
      radiobox_flag == close_radiobox ||
      radiobox_flag == close_all_radiobox ) {
    Load_SRC_CFG_Names ( obj );
    unlink( SRCName );
    /* MUST do this *after* the unlinking */
    KillProcess_Modify_ps ( obj );
  }

  rewrite_prompt = 1;
  committed = 1;
  UnDecorate_SRC_file_newer ( obj );

  if ( ( Is_Anl_MchRefImp ( obj ) ) /* ||
       ( Is_Gen_Bse ( obj ) ) */      ) {
/*
    sprintf ( fifo_write_buf, "%s:0", GetName ( obj ) );
    curr_obj = obj;
    Cre_fifo_write_buf_cmd_0 ( BT_CRE_HTML_WITH_ENV );
*/
    sprintf ( buf, "\n    Re-creating %s html file ...", GetName ( obj ) );
    DisplayCurrWinText ( buf );
    curr_obj = obj;
    Cre_fifo_write_buf_cmd_env ( obj, BT_CRE_HTML_WITH_ENV, 0 );
    InvokeB ( without_XTerm, 1 );
  }
  else {
    sprintf ( buf,  "\n\n  Committed %s\n", GetName ( obj ) );
    DisplayCurrWinText ( buf ); 
    CheckFileParses_ContinueLoop ();
  }
}


void
RemoveProofObj ( obj, rm_flag )
int obj, rm_flag;
{
  int bb, gen_by, prf_level, st;
  void DisplayUnInsert ();

  def_gen_by ( &bb, obj );
  if ( bb ) {
    def_prf_level ( &bb, obj );
    if ( bb ) {
      val_gen_by ( &gen_by, obj );
      val_prf_level ( &prf_level, obj );
      val_curMRIState ( &st, gen_by );
      del_ppf ( st, prf_level );
      del_ppf_dmu ( st, prf_level );
      val_cptMRIState ( &st, gen_by );
      del_ppf ( st, prf_level );
      del_ppf_dmu ( st, prf_level );
      sprintf ( buf, "POB/%s", GetName ( obj ) );
      unlink ( buf );
      sprintf ( buf, "TEX/%s.tex", GetName ( obj ) );
      unlink ( buf );
      sprintf ( buf, "TEX/%s.dvi", GetName ( obj ) );
      unlink ( buf );
      sprintf ( buf, "\n  Removed proof object %s\n", GetName ( obj ) );
      if ( rm_flag ) strcat ( buf, "  and reset its dependent constructs\n" );
      kill_Construct ( obj );
      DisplayUnInsert ( obj );
      SetDisplayField_obj_Changed ( gen_by );
      DisplayCurrWinText ( buf );
    }
  }
}

ResetAllDependents ( obj )
int obj;
{
  /***
  gset1 contains all dependents
  gset5 contains all code dependents (mch => executable/.vhd, imp => .obj)
  ***/

  int nn, rr, anl, dmu, trl, lnk, lenpob, fpob, ppob, lpob, gen1, gen2;
  int cc, cc1, name [ 50 ], ext, type;
  int bb, ac, ac1, st;

  /***
  gset4 := gset5 - ( gset1 /\ gset5 )
  ***/

  clear_gset4();
  card_gset5 ( &nn );
  while ( nn ) {
    valOrd_gset5 ( &cc, nn );
    member_gset1 ( &bb, cc );
    if ( ! bb ) {
/***
printf ( "ResetAllDependents: %s of gset5 not in gset1\n", GetName ( cc ) );
***/
      add_gset4 (&rr, cc);
      chk_rep ( rr, 237 );
    }
/***
    else {
printf ( "ResetAllDependents: %s of gset5 in gset1 - removing\n", GetName ( cc ) );
    }
***/
    nn--;
  }


  val_mand ( name, &ext, &type, obj );
  def_curMRIState ( &bb, obj );
  if ( bb ) {
    val_curMRI ( &anl, &dmu, &trl, &lnk, &lenpob, &fpob, &ppob, &lpob, obj );
    lpob = correct_pob_for_btl ( lpob );
    def_abs2conc ( &bb, obj );
    if ( bb ) val_abs2conc ( &ac, obj );
  }

/***
PrintBase;
printf("ResetAllDependents %s ac=%d\n", GetName ( obj ), ac );
***/

  def_curGENState ( &bb, obj );
  if ( bb ) val_curGEN ( &gen1, &gen2, &dmu, obj );

  card_gset1 ( &nn );
  while ( nn ) {
    valOrd_gset1 ( &cc, nn );
/***
printf("gset1 DEPENDENT cc = %d\n", cc );
fflush ( stdout );
***/
    val_mand ( name, &ext, &type, cc );
/***
printf("gset1 DEPENDENT %s, type: %d\n", GetName ( cc ), type );
fflush ( stdout );
***/
    Load_SRC_CFG_Names ( cc );
    switch ( type ) {

    case usr:
    case usr_vhdl:
/***
printf( "type = usr\n" );
***/
      def_curGENState ( &bb, cc );
      if ( ( ext == mch ) || ( ext == ref ) || ( ext == imp ) ) {
        val_abs2conc ( &ac1, cc );
        if ( ac == ac1 ) {
/***
printf( "CheckUnanalyse 0\n" );
***/
          CheckUnanalyse ( cc, 0 );
        }
        else {
/***
printf( "CheckUnanalyse 1\n" );
***/
          CheckUnanalyse ( cc, 1 );
        }
      }
      else if ( ext == doc ) {
/***
printf( "CheckUndoc\n" );
***/
        CheckUndoc ( cc );
      }
      else if ( ( ext == bse ) || ( ext == enm ) || ( ext == itf ) ) {
/***
printf( "CheckUngen\n" );
***/
        CheckUngen ( cc );
      }

      break;

    case bse_gen:
    case enm_gen:
    case gen_vhdl:
    case itf_gen:
    case prf_gen:
    case lib:
/***
printf( "type = *_gen || type = lib\n" );
***/
      KillConstruct ( cc );
      break;


    }  /* switch ( type ) */

    nn = nn-1;
  }    /* while ( nn ) */

  clear_gset1 ();

  card_gset4 ( &nn );   /* gset4 is gset5 filtered ! */
  while ( nn ) {
    valOrd_gset4 ( &cc, nn );
/***
printf("gset5 DEPENDENT cc = %d\n", cc );
fflush ( stdout );
***/
    val_ext ( &ext, cc );

    if ( ext == mch ) {
      int cc3, st;
      GetObjFromNameExt ( &cc3, GetShortName ( cc ), itf );
      if ( cc3 ) {
        val_curGENState ( &st, cc3 );
        val_gen2 ( &bb, st );
        if ( bb ) {
          Load_SRC_CFG_Names ( cc3 );
          CheckUngen ( cc3 );
	}
      }
    }
    else {
      get_botref ( &cc1, cc );
/***
val_mand ( name, &ext, &type, cc );
***/
      Load_SRC_CFG_Names ( cc1 );
/***
printf("DEPENDENT CODE %s.%s, type: %d\n",  name, extens [ ext ], type );
***/
      val_curMRIState ( &st, cc1 );
/***
printf("modifying %d st - trl & lnk to FALSE\n",st);
***/
      mod_trl ( st, FALSE );
      mod_lnk ( st, FALSE );
      RemoveCodeFiles ( cc1 );
    }
    nn--;
  }
  clear_gset5 ();
}

void
ResetConstruct ( obj, dep_option )
int obj, dep_option;
{
  int ext;

/***
printf ( "ResetConstruct %s\n", GetName ( obj ) );
***/

  sprintf ( buf, "\n  Reset %s", GetName ( obj ) );
  DisplayCurrWinText ( buf ); 
  if ( dep_option ) {
    ResetAllDependents ( obj );
    DisplayCurrWinText ( " and its dependent constructs\n" );    
  }
  else {
    DisplayCurrWinText ( " (no dependent constructs)\n" );    
  }
  val_ext ( &ext, obj );
  if ( ext == mch || ext == ref || ext == imp ) {
    CheckUnanalyse ( obj, 1 );
  }
  else if ( ext == doc ) {
    CheckUndoc ( obj );
  }
  else if ( ext == bse || ext == ops || ext == enm  || ext == itf ) {
    CheckUngen ( obj );
  }
  DisplayCurrentEnv ();
}








/**************************************************
          Utilities from Steve
***************************************************/

Pixel
GetPixel ( colourname )
char *colourname;
{
  static colour_problem = 0;
  int scr = DefaultScreen ( display );
  Colormap cmap = DefaultColormap ( display, scr );
  XColor colour, ignore;

  if ( strcmp ( colourname, "check colour_problem" ) == 0 ) {
    if ( colour_problem ) {
      buf[0]='\0';
      strcat(buf,"\n  Can't allocate colours from \"XBMotif\" resource file.\n\n");
      strcat(buf,"  This could be because of an already-running\n  colour-hungry application (eg. Netscape),\n  or because \"XBMotif\" is in the wrong place.\n\n");
      strcat(buf,"  If it is the latter, please put \"XBMotif\"\n  where it can be read, for example in:\n\n");
      strcat(buf,"        /usr/lib/X11/app-defaults           or\n        /usr/openwinlib/X11/app-defaults    or\n        /usr/X11R6/lib/app-defaults         or\n        $HOME\n\n");
      strcat(buf,"  The location is dependent on the X file search path\n  of your local setup and you should consult\n  your System Administrator if you experience\n  difficulties.\n\n" );
      printf ( buf );
      DisplayCurrWinText ( buf );
      XBell ( display, -75 );
      XBell ( display, -75 );
      XBell ( display, -75 );
      XBell ( display, -75 );
    }
    return ( Pixel ) 0;
  }

  if ( XAllocNamedColor ( display, cmap, colourname, &colour, &ignore ) ) {
    return ( colour.pixel );
  }
  else
  {
/*
    printf ( "  BMotif: unable to get colour %s\n                   this has unpredictable consequences ...\n\n", colourname );
*/
    printf ( "  BMotif: not allocated colour %s\n", colourname );
    fflush ( stdout );
    colour_problem = 1;
    return ( WhitePixel (  display, scr ) );
/*
    return ( WhitePixelOfScreen ( XtScreen ( top_level ) ) );
*/
  }
}



/**************************************************
          Utilities
***************************************************/

void
ResetWaitingOption ()
{
  waiting_option = 0;
}

void
Bell_CB ()
{
  if ( bell_option ) XBell( display, 10 );
}

void
Kill_bplatform_and_exit ( BToolkitd_flag, COUNT_WWW_flag )
int BToolkitd_flag;
int COUNT_WWW_flag;
{
  int pib;
  int c;
  int t1, t2;
  FILE * Bpib;

  process_XTerm_IfReq ();

  system ( "echo 0 > .Bses" );

  unlink ( pid_id_file );

  t1 = 0;
  Bpib = NULL;
  while ( Bpib == NULL && t1 < 60 ) {
    Bpib = fopen ( ".Bpib", "r" );
    if   ( Bpib == NULL ) sleep ( 1 );
    else                  t1++;
  }
  if ( Bpib == NULL ) {
    AbortedMsgFile ( "\".Bpib\" for reading" );
/***
printf("t1 %d\n",t1);
***/
    exit ( 1 );
  }
  fclose ( Bpib );
  pib = 0;
  t2 = 0;
  Bpib = NULL;
  while ( t2 < 60 && ! pib ) {
    pib = 0;
    Bpib = fopen ( ".Bpib", "r" );
    if ( Bpib == NULL ) {
      AbortedMsgFile ( "\".Bpib\" for reading" );
      exit ( 1 );
    }
    sleep ( 1 );
    t2++;
    c = getc ( Bpib );
    while ( c != EOF && c != '\n' )  {
      pib = ( pib * 10 ) + c - '0';
      c = getc ( Bpib );
    }
    fclose ( Bpib );
  }
  if ( ! pib ) {
    AbortedMsgFile ( "\".Bpib\" for reading" );
/***
printf("t2 %d\n",t2);
***/
    exit ( 1 );
  }
  
/***
printf("BMotif: %d loop(s) waiting for .Bpib\n",t1);
printf("BMotif: %d loop(s) for non-zero read\n",t2);
printf("\n  kill (%d,SIGKILL)\n\n", pib );
***/

  kill ( pib, SIGKILL );
  exit ( 1 );
}

void
DesLSTBut ( nn )
int nn;
{
/***
printf ( "BMotif.c: DesLSTBut nn = %d\n", nn); fflush ( stdout );
***/
  if ( nn ) {
    DeSensitize ();
    XtSetSensitive ( InterruptPullDown, True );
    XtSetSensitive ( HelpPullDown,     False );
    XtSetSensitive ( help_main_lab,  False );
    XmUpdateDisplay ( InterruptPullDown );
    XmUpdateDisplay ( HelpPullDown );
    XmUpdateDisplay ( help_main_lab );
    XmUpdateDisplay ( top_bar );
    XmUpdateDisplay ( top_level );
    if ( ( nn > 100 ) && ( nn < 1000 ) ) {
      process_XTerm_IfReq ();
      sleep ( 1 );
      XBell ( display, -75 );
      XBell ( display, -75 );
      XBell ( display, -75 );
      XBell ( display, -75 );
      strcpy ( buf, "\n\n    B-Toolkit: Error code " );
      CreNumInBuf ( buf, nn + 7026 );
      strcat ( buf, "\n" );
      DisplayCurrWinText ( buf );
      AbortedMsgCode ( nn + 7026 );
      Kill_bplatform_and_exit ( 1, 0 );
    }
    else {
      strcpy ( xterm_title, "B-Analyser" );
      if   ( nn < 0 ) strcpy ( fifo_write_buf, "0" );
      else            fifo_write_buf [ 0 ] = '\0';
      CreNumInBuf ( fifo_write_buf, nn );
      strcat ( fifo_write_buf, ":" );
      Cre_fifo_write_buf_cmd_0 ( BT_LST_FLG );
      if   ( ! xterm_is_up ) CreateXTerm ();
      else                   Write_FIFO ( fifo_write_buf );
    }
  }
}

void
CloseAllOpenFilesNext ()
{
   while ( ( ! ( sel_arr_tog [ close_all_count ] ) ) &&
           ( close_all_count < sel_arr_tot )            ) {
    close_all_count++;
  }
  if ( close_all_count < sel_arr_tot ) {
    int file_diff;
    curr_obj = sel_obj_arr [ close_all_count ];
    Load_SRC_CFG_Names ( curr_obj );
    file_diff = FileDiffIntoBcom ( curr_obj );
    if ( file_diff ) {
      strcpy ( primary_string, GetName ( curr_obj ) );
      radiobox_flag = close_all_radiobox;
      close_all_count++;
      Popup_CloseEditedFile ( top_level );
    }
    else {
      unlink( SRCName );
      /* MUST do this *after* the unlinking */
      KillProcess_Modify_ps ( curr_obj );
      close_all_count++;
      CloseAllOpenFilesNext ();
    }
  }
  else {
    radiobox_flag = 0;
    DisplayCurrentEnv ();
  }
}

void
CommitAllOpenEditedFilesNext ()
{
  while ( ( ! ( sel_arr_tog [ commit_all_count ] ) ) &&
          ( commit_all_count < sel_arr_tot )            ) {
    commit_all_count++;
  }
  if ( commit_all_count < sel_arr_tot ) {
    curr_obj = sel_obj_arr [ commit_all_count ];
    Load_SRC_CFG_Names ( curr_obj );
    commit_all_count++;
    radiobox_flag = commit_all_radiobox;
    CheckFileParses ( curr_obj );
  }
  else {
    radiobox_flag = 0;
    DisplayCurrentEnv ();
  }
}

void
CommitAll_Remake_OpenEditedFilesNext ()
{
  void LoadAllConstructsInto_gset1 ();

  while ( ! sel_arr_tog [ commit_all_remake_count ] &&
          commit_all_remake_count < sel_arr_tot    ) {
    commit_all_remake_count++;
  }
  if ( commit_all_remake_count < sel_arr_tot ) {
    curr_obj = sel_obj_arr [ close_all_count ];
    Load_SRC_CFG_Names ( curr_obj );
    commit_all_remake_count++;
    radiobox_flag = commit_all_remake_radiobox;
/***
printf ( "1 commit_all_remake_radiobox %s\n", GetName ( curr_obj ) );
***/
    CheckFileParses ( curr_obj );
  }
  else {
    radiobox_flag = 0;
    if ( ( not_parse_option ) || ( commit_aborted ) ) {
      not_parse_option = 0;
      commit_aborted = 0;
      DisplayCurrWinText ( "\n  Remake aborted\n" );
      DisplayCurrentEnv ();
    }
    else {
      int i, rr;
      LoadAllConstructsInto_gset1 ();
      Remake ( dry_run );
      if ( ! sel_arr_tot ) {
        Popup_Info ( "    No remake required!    " );    
      }
      else {
        radiobox_flag = remake_all_or_construct_radiobox;
        if ( Commit_All_type == Commit_All_remake_all ) {
          Pre_Remake ( remake_all_constructs );
	}
        else {
/***
printf ( "13 commit_all_remake_radiobox %s\n", GetName ( curr_obj ) );
***/
          Pre_Remake ( remake_construct );
	}        
      }
    }
  }
}

void
ProcessAndDisplayCurrWinText ( text )
char * text;
{
  char i, j;

  i = 0;
  j = 0;
  while ( text [ j ] != '\0' ) {
    if ( text [ j ] == '\\' && text [ j + 1 ] == 'n' ) {
      buf [ i++ ] = '\n';
      j = j + 2;
    }
    else {
      buf [ i++ ] = text [ j ++ ];
    }
  }
  buf [ i ] = '\0';
  DisplayCurrWinText ( buf );
/***
printf ( "text |%s|\n", text );
printf ( "buf  |%s|\n", buf );
***/
}

void
ProcessAndDisplayCurrWinTextBcom ()
{
  FILE * Bcom;
  int c,i;
  i = 0;
  Bcom = fopen ( "TMP/.Bcom", "r" );
  if ( Bcom == NULL ) {
    AbortedMsgFile ( "\"TMP/.Bcom\" for reading" );
    BT_err_exit ( 0 );
    return;
  }
  c = getc ( Bcom );
  while ( c != EOF ) {
    fifo_write_buf [ i ] = ( char ) c;
    i++;
    c = getc ( Bcom );
  }
  fclose ( Bcom );
  fifo_write_buf [ i ] = '\0';
  ProcessAndDisplayCurrWinText ( fifo_write_buf );
}

void
RemoveTopCurrText ( add_length )
int add_length;
{
  XmTextPosition nl_pos;
  int nl_found;

#define text_trigger_tot   30000
#define text_rem_tot        2500

/***
printf ( "curr_text_posn start: %d\n", ( int ) curr_text_posn );
XBell( display, -75 );
***/
  nl_found = XmTextFindString ( curr_text,
                 ( XmTextPosition ) text_rem_tot,
                "\n",
                 XmTEXT_FORWARD,
                 & nl_pos );
  if ( nl_found ) {
    XmTextReplace ( curr_text,
         ( XmTextPosition ) 0,
         ( XmTextPosition ) nl_pos,
         "" );
    curr_text_posn = curr_text_posn - nl_pos;
  }
  else {
    XmTextReplace ( curr_text,
         ( XmTextPosition ) 0,
         ( XmTextPosition ) text_rem_tot,
         "" );
    curr_text_posn = curr_text_posn - text_rem_tot;
  }

  XmTextSetHighlight ( curr_text,
      ( XmTextPosition ) 0,
      ( XmTextPosition ) text_rem_tot + nl_pos,
      XmHIGHLIGHT_NORMAL );
/***
;XBell( display, -75 );
;printf ( "curr_text_posn end:   %d\n", ( int ) curr_text_posn );
;printf ( "  curr_text_posn diff:  %d\n", ( int ) nl_pos );
***/
}

void
DisplayCurrWinText ( text )
char *text;
{
  size_t text_length = strlen ( text );

  if (  ( text_length > 50 )                                        && 
        ( ( int ) curr_text_posn + text_length > text_trigger_tot )    ) {
    RemoveTopCurrText ( text_length );
  }
  XmTextInsert ( curr_text, curr_text_posn, text );
  curr_text_posn = curr_text_posn + text_length;
  XmTextShowPosition ( curr_text, curr_text_posn );
  XmUpdateDisplay ( curr_text );
}

void
DisplayCurrWinTextAt ( text_pos, text )
XmTextPosition text_pos;
char *text;
{
  XmTextReplace ( curr_text, text_pos, text_pos + strlen ( text ), text );
  XmTextShowPosition ( curr_text, text_pos );
  XmUpdateDisplay ( curr_text );
}

void
Remake_Proceed ()
{
  DisplayCurrWinText ( "\n  Remaking\n" );
  strcpy ( xterm_title, "B-Remake" );
  InvokeB ( with_XTerm, 1 );
}

void
RemakeSelections ( flag )
int flag;
{
  int reqd, i;

  reqd = 0;
  if   ( flag == remake_jobs_selection ) {
    DisplayCurrWinText ( "\n  Remaking\n" );
  }
  else {
    DisplayCurrWinText ( "\n  Analysing/Generating All Constructs\n" );
  }
  strcpy ( fifo_write_buf, "(" );
  for ( i = 0 ; i < sel_arr_tot ; i++ ) {
    if ( sel_arr_tog [ i ] ) {
      strcat ( fifo_write_buf, rmk_str_arr [ i ] );
      strcat ( fifo_write_buf, ";" );
      reqd = 1;
    }
  }
  strcat ( fifo_write_buf, "?)|_" );
/***
printf ( "Remake jobs:\n  %s\n", fifo_write_buf );
***/
  if ( reqd ) {
    if ( ! auto_reset_and_remake ) {
      if   ( flag == remake_jobs_selection ) {
        strcpy ( xterm_title, "B-Remake" ); }
      else {
        strcpy ( xterm_title, "Analyse/Generate" );
        Popup_Sel_flag = remake_jobs_selection;
      }
    }
    else {
      if      ( auto_timer ) strcpy ( xterm_title, "B-Auto-Timer" );
      else if ( auto_reset ) strcpy ( xterm_title, "B-Auto-Reset" );
      else                   strcpy ( xterm_title, "B-Auto-Reset-Remake" );
    }
    InvokeB ( with_XTerm, 1 );
  }
}

void
CommitAll_CB ( flag )
int flag; /* Commit_All_not_remake       || 
             Commit_All_remake_all       ||
             Commit_All_remake_construct    */
{
  /***
  reset radiobox & sel options!
  ***/
  radiobox_flag = 0;
  Popup_Sel_flag = 0;  
  Commit_All_type = flag;

#ifdef WWW_VERSION

    WWW_Err;

#else /* ! WWW_VERSION */

  LoadOpenEditedConstructsInto_sel_strs ();

  if ( ! sel_arr_tot ) {
    if ( Commit_All_type == Commit_All_remake_all ) {
      /* CommitAll_CB ( Commit_All_remake_all ); */
      Pre_Remake ( remake_all_constructs );
    }
    else if ( Commit_All_type == Commit_All_remake_construct ) {
      /* CommitAll_CB ( Commit_All_remake_construct ); */
      Pre_Remake ( remake_construct );
    }
    else {
      Popup_Info ( "No updated open constructs" );
    }
  }
  else {
    if ( Commit_All_type == Commit_All_not_remake ) {
      Popup_Sel_flag = commit_all_edit_selection;
      Popup_Sel_Dialog ( top_level, "Commit constructs" );
    }
    else {
      Popup_Sel_flag = commit_all_remake_edit_selection;
      Popup_Sel_Dialog ( top_level, "Commit before Remake" );
    }
  }

#endif /* WWW_VERSION */

}

void
CommitAll_Remake_CB ()
{
  /***
  reset radiobox & sel options!
  ***/
  radiobox_flag = 0;
  Popup_Sel_flag = 0;

#ifdef WWW_VERSION

  {
    void LoadAllConstructsInto_gset1 ();

    LoadAllConstructsInto_gset1 ();
    Remake ( dry_run );
    if ( ! sel_arr_tot ) {
      Popup_Info ( "    No remake required!    " );    
    }
    else {
      radiobox_flag = remake_all_or_construct_radiobox;
      /*
      Popup_Remake ( top_level );
      */
    }
  }

#else /* ! WWW_VERSION */

  LoadOpenEditedConstructsInto_sel_strs ();

  if ( sel_arr_tot ) {
    not_parse_option = 0;    
    commit_aborted = 0;
    Popup_Sel_flag = commit_all_remake_edit_selection;
    Popup_Sel_Dialog ( top_level, "Commit constructs" );
  }
  else {
    void LoadAllConstructsInto_gset1 ();

    LoadAllConstructsInto_gset1 ();
    Remake ( dry_run );
    if ( ! sel_arr_tot ) {
      Popup_Info ( "    No remake required!    " );    
    }
    else {
      radiobox_flag = remake_all_or_construct_radiobox;
      /*
      Popup_Remake ( top_level );
      */
    }
  }

#endif /* WWW_VERSION */

}

void
ChangeDirectoryExistingDir ( new_dir )
char * new_dir;
{
  struct stat stat_buf;
  FILE * Bpda; 
  FILE * Bpdan; 
  FILE * Bcom;
  int Bpdan_flag = 0; 
  int c, i;
  void ProcessUpgrade ();

  if ( chdir ( new_dir ) == -1 ) {
    sprintf ( fifo_write_buf, "\n  Can't change directory to %s\n", new_dir );
    DisplayCurrWinText ( fifo_write_buf );
    main_continue ( 0, 0 );
    return;
  }

  strcpy ( primary_string, cur_dir );
  strcpy ( cur_dir, new_dir ); 
  sprintf ( fifo_write_buf, "%s/.Bpdan", cur_dir );
  if ( stat ( fifo_write_buf, &stat_buf ) != -1 ) {
    Bpdan = fopen ( fifo_write_buf, "r" );
    if ( Bpdan == NULL ) {
      sprintf ( str_buf, "\n  Can't open %s for reading\n", fifo_write_buf );
      DisplayCurrWinText ( str_buf );
      strcpy ( cur_dir, primary_string );
      if ( chdir ( cur_dir ) == -1 ) {
        printf ("\n\n  Can't change directory to %s\n\n", cur_dir );
        perror ( "\n  chdir" );
        Kill_bplatform_and_exit ( 1, 0 );
      }
      main_continue ( 0, 0 );
      return;
    }
    /***
    get header string from .Bpdan
    ***/
    Bpdan_flag = 1;
    fread( &c, sizeof ( int ), 1, Bpdan );
    c = ntohl ( ( int ) c );
    i = 0;
    while ( i < ( int ) strlen ( cur_hdr_string ) && c != EOF ) {
      buf [ i ] = ( char ) c;
      i++;
      if ( i < ( int ) strlen ( cur_hdr_string ) ) {
        fread( &c, sizeof ( int ), 1, Bpdan );
        c = ntohl ( ( int ) c );
      }
    }
    buf [ i ] = '\0';
    /***
    read platform identifier ( but not needed here )
    ***/
    fread( &c, sizeof ( int ), 1, Bpdan ); /* platform_ident  */
    c = ntohl ( c );          /* no need to check here */
    fclose ( Bpdan );
  }
  else {   /* .Bpdan does not exist */
    sprintf ( fifo_write_buf, "%s/.Bpda", cur_dir );
    Bpda = fopen ( fifo_write_buf, "r" );
    if ( Bpda == NULL ) {
      sprintf ( str_buf, "\n  Can't open %s for reading\n", fifo_write_buf );
      DisplayCurrWinText ( str_buf );
      strcpy ( cur_dir, primary_string );
      if ( chdir ( cur_dir ) == -1 ) {
        printf ("\n\n  Can't change directory to %s\n\n", cur_dir );
        perror ( "\n  chdir" );
        Kill_bplatform_and_exit ( 1, 0 );
      }
      main_continue ( 0, 0 );
      return;
    }

    /***
    get header string from .Bpda
    ***/
    c = getc ( Bpda );
    i = 0;
    while ( i < ( int ) strlen ( cur_hdr_string ) && c != EOF ) {
      buf [ i ] = ( char ) c;
      i++;
      if ( i < ( int ) strlen ( cur_hdr_string ) ) c = getc ( Bpda );
      }
    buf [ i ] = '\0';
    /***
    read platform identifier
    ***/
    c = getc ( Bpda );   /* platform_ident */
    fclose ( Bpda );

/***
printf ( "%d %s   %d %s\n", c, platform_types [ c ], platform_ident, platform_types [ platform_ident ] );
***/
    if ( strcmp ( buf, cur_hdr_string ) == 0 ) {
      if ( ( c != platform_ident )                        &&
           ( ( c != platform_ident_SunOS   ||
               platform_ident != platform_ident_Solaris ) &&
             ( c != platform_ident_Solaris ||
               platform_ident != platform_ident_SunOS )       ) ) {

        sprintf ( buf, "\n %s:\n    Platform-independent data file does not exist\n\n    This development should be re-run on a %s platform\n", 
                                                  cur_dir, platform_types [ c ] );
        DisplayCurrWinText ( buf );
        strcpy ( cur_dir, primary_string );
        if ( chdir ( cur_dir ) == -1 ) {
          printf ("\n\n  Can't change directory to %s\n\n", cur_dir );
          perror ( "\n  chdir" );
          Kill_bplatform_and_exit ( 1, 0 );
        }
        main_continue ( 0, 0 );
        return;
      }
    }
    else { /* ( strcmp ( buf, cur_hdr_string ) != 0 */
/***
    printf ( "\n  No cur_hdr_string match |%s| |%s| %d\n", buf, cur_hdr_string, strlen ( cur_hdr_string ) );
***/
      sprintf ( buf, "\n  %s:\n\n    Not a %s development\n\n    You should run the toolkit in that\n    directory for an automatic upgrade\n      ",
                                                 cur_dir, toolkit_short_ver );
      DisplayCurrWinText ( buf );
      strcpy ( cur_dir, primary_string );
      if ( chdir ( cur_dir ) == -1 ) {
        printf ("\n\n  Can't change directory to %s\n\n", cur_dir );
        perror ( "\n  chdir" );
        Kill_bplatform_and_exit ( 1, 0 );
      }
      main_continue ( 0, 0 );
      return;

    }
  }

  sprintf ( fifo_write_buf, "%s/.Bcom", primary_string ); /* prev dir */
  Bcom = fopen ( fifo_write_buf, "w" );
  if ( Bcom == NULL ) {
    strcat ( fifo_write_buf, " for writing" );
    AbortedMsgFile ( fifo_write_buf );
    return;
  }
  fprintf ( Bcom, cur_dir );
  fclose ( Bcom );

  system ( "rm -fr TMP" );
  CheckAllDIRSExist ();     /* TMP ! */

  ReturnFromB_option = from_new_dir;
  strcpy ( fifo_write_buf, "0:" );
  Cre_fifo_write_buf_cmd_0 ( BT_NEW_DIR );
  InvokeB ( without_XTerm, 1 );
}

void
ChangeDirectoryNewDir ( new_dir )
char * new_dir;
{
  FILE * Bcom;

  if ( chdir ( new_dir ) == -1 ) {
    sprintf ( fifo_write_buf, "\n  Can't change directory to %s\n", new_dir );
    DisplayCurrWinText ( fifo_write_buf );
    main_continue ( 0, 0 );
    sprintf ( fifo_write_buf, " Can't change directory to %s", new_dir );
    check_started_from_cd ( fifo_write_buf );
    return;
  }
  strcpy ( primary_string, cur_dir );
  strcpy ( cur_dir, new_dir ); 
  INI_CfgDepBase ();
  InitialiseFlagsAndStrings ();
  system ( "touch .Bpda" );      /* so "cp .Bpda .Bpda_0" will work */
  Save_CfgDepBase ();
  system ( "cp .Bpda .Bpda_0" ); /* now they're the same */
  DisplayChanged = 0;
  DisplayCurrWinText ( "\n  Created new B-Toolkit development directory\n");

  sprintf ( fifo_write_buf, "%s/.Bcom", primary_string ); /* prev dir */
  
  Bcom = fopen ( fifo_write_buf, "w" );
  if ( Bcom == NULL ) {
    strcat ( fifo_write_buf, " for writing" );
    AbortedMsgFile ( fifo_write_buf );
    BT_err_exit ( 0 );
    return;
  }
  fprintf ( Bcom, cur_dir );
  fclose ( Bcom );
  system ( "rm -fr TMP" );
  CheckAllDIRSExist ();     /* TMP ! */
/*
  fifo_read_init ();
  make_fifo_in_cur_dir ();
*/

  ReturnFromB_option = from_new_dir;
  strcpy ( fifo_write_buf, "0:" );
  Cre_fifo_write_buf_cmd_0 ( BT_NEW_DIR );
  InvokeB( without_XTerm, 1 );
}

void
CloseAll_CB ()
{
  /***
  reset radiobox & sel options!
  ***/
  radiobox_flag = 0;
  Popup_Sel_flag = 0;  

  LoadOpenConstructsInto_sel_strs ();

  if ( ! sel_arr_tot ) {
    Popup_Info ( "No constructs currently open  " );
  }
  else {
    Popup_Sel_flag = close_all_edit_selection;
    Popup_Sel_Dialog ( top_level, "Close constructs" );
  }
}

/* not used
void
Hypertext_CB ()
{
  int Hypertext_Text_Option;

  /???
  reset radiobox & sel options!
  ???/
  radiobox_flag = 0;
  Popup_Sel_flag = 0;

  valIth_flags ( &Hypertext_Text_Option, Hypertext_text_num );
  Retrieve_String ( htx_viewer_str_num, buf );

  if ( Hypertext_Text_Option ) {
    Popup_Err ( 0, " Hypertext display set to text - check TopBar Options" );
  }
  else if ( strcmp ( buf, "" ) == 0 ) {
    Popup_Err ( 0, "Hypertext Viewer not set - check TopBar Options" );
    DisplayCurrentEnv ();
  }
  else {
    sprintf ( secondary_string, "Launching %s for ConstructsSummary", buf );
    Popup_Info ( secondary_string );
    strcpy ( primary_string, buf );
    strcat ( primary_string, " HTX/ConstructsSummary.html &" );
    execute ( primary_string );
  }
}
*/

XtCallbackProc
PositionAnmOpsRelMainWin_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  Position top_level_x;
  struct coord * coord_data;
  coord_data = ( struct coord * ) client_data;

/***
printf ( "PositionAnmOpsRelMainWin_CB anm_ops_x %d  anm_ops_y %d \n", anm_ops_x, anm_ops_y );
***/

  if ( anm_ops_x == -999 ) {

    XtVaGetValues ( top_level,
        XmNx,         &top_level_x,
        NULL );

    anm_ops_x =  top_level_x + ( Position ) coord_data->x;
    anm_ops_y = ( Position ) coord_data->y;

    XtVaSetValues ( widget,
        XmNx,         anm_ops_x,
        XmNy,         anm_ops_y,
        NULL );

  }

  else {
    XtVaSetValues ( widget,
		    XmNx,  ( Position ) anm_ops_x /* - wm_width */,
		    XmNy,  ( Position ) anm_ops_y /* - wm_height */,
        NULL );
  }

/***
printf ( "anm_ops_h == %d\n", anm_ops_h );
***/

  if ( anm_ops_h == 1 ) {

    XtVaGetValues ( widget,
        XmNheight,    &anm_ops_h,
        XmNwidth,     &anm_ops_w,
        NULL );

  }

  else {
    XtVaSetValues ( widget,
        XmNheight,    anm_ops_h,
        XmNwidth,     anm_ops_w,
        NULL );
  }

/***
printf ( "anm_ops_h == %d\n", anm_ops_h );
***/
}

XtCallbackProc
PositionWidgetRelMainWin_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  Position top_level_x;
  struct coord * coord_data;
  coord_data = ( struct coord * ) client_data;

  XtVaGetValues ( top_level,
      XmNx,         &top_level_x,
      NULL );
  XtVaSetValues ( widget,
      XmNx,         top_level_x + ( Position ) coord_data->x,
      XmNy,         ( Position ) coord_data->y,
      NULL );
}

XtCallbackProc
IprPositionSearchedHyp_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  Position parent_x, parent_y;

  XtVaGetValues ( ( Widget ) client_data,
      XmNx,       & parent_x,
      XmNy,       & parent_y,
      NULL);
  
  XtVaSetValues ( widget,
      XmNx,       parent_x + 5,
      XmNy,       parent_y + 73,
      NULL);
}

XtCallbackProc
PositionWidgetRightMainWin_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  Position top_level_x;
  Dimension top_level_w;
  struct coord * coord_data;
  coord_data = ( struct coord * ) client_data;
  
  XtVaGetValues ( top_level,
      XmNx,         &top_level_x,
      XmNwidth,     &top_level_w,
      NULL );
  XtVaSetValues ( widget,
      XmNx,         top_level_x + top_level_w + ( Position ) coord_data->x,
      XmNy,         ( Position ) coord_data->y,
      NULL );
}

XtCallbackProc
CentreWidgetRelMainWin_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  static int first_time = 1;
  Position top_level_x, top_level_y, widget_x, widget_y;
  Dimension top_level_w, widget_w, widget_h;
  struct coord * coord_data;
  coord_data = ( struct coord * ) client_data;

  XtVaGetValues ( top_level, 
      XmNx,         & top_level_x,
      XmNy,         & top_level_y,
      XmNwidth,     & top_level_w,
      NULL );

  XtVaGetValues (  widget, 
      XmNwidth,     & widget_w,
      XmNheight,    & widget_h,
      NULL );

  widget_x = top_level_x + ( ( top_level_w - widget_w ) / 2 ) - 5;
  if ( widget_x  < 1 ) widget_x = 1;
  if ( widget_x + widget_w >= WidthOfScreen ( proof_screen ) )
    widget_x = WidthOfScreen ( proof_screen ) - widget_w;

  widget_y = top_level_y + coord_data->y;
  if ( widget_y  < 1 ) widget_y = 1;
  if ( widget_y + widget_h >= HeightOfScreen ( proof_screen ) )
    widget_y = HeightOfScreen ( proof_screen ) - widget_h;

  XtVaSetValues ( widget, 
      XmNx,         widget_x,
      XmNy,         widget_y,
      NULL );

  if ( first_time ) {
    first_time = 0;
    wm_width = widget_x;
    wm_height = widget_y;
  }
}

/*** keep, for info ... ***
void
PositionWidgetRelCursor ( widget, x_offset, y_offset )
Widget widget;
int  x_offset;
int  y_offset;
{
  Window root, child;
  int win_x, win_y, ptr_x, ptr_y;
  Dimension widget_w, widget_h;
  int screen_w, screen_h;
  unsigned int kb;

  screen_w = WidthOfScreen  ( XtScreen ( widget ) );
  screen_h = HeightOfScreen ( XtScreen ( widget ) );

  XQueryPointer( display, DefaultRootWindow ( display ), &root, &child,
      &ptr_x, &ptr_y, &win_x, &win_y, &kb );

  XtVaGetValues ( widget, 
      XmNwidth,         &widget_w,
      XmNheight,        &widget_h,
      NULL );

  ptr_x = ptr_x + x_offset + 10;
  ptr_y = ptr_y + y_offset + 10;

/???
printf ( "screen_w: %d\n",screen_w);
printf ( "screen_h: %d\n",screen_h);
printf ( "widget_w: %d\n",(int)widget_w);
printf ( "widget_h: %d\n",(int)widget_h);
printf ( "ptr_x: %d\n",ptr_x);
printf ( "ptr_y: %d\n\n",ptr_y);
printf ( "x_offset: %d\n",x_offset);
printf ( "y_offset: %d\n\n",y_offset);
???/

  if ( ( int ) widget_w + ptr_x >= screen_w ) {
    ptr_x = screen_w - ( int ) widget_w - 7;
  }

  if ( ( int ) widget_h + ptr_y + 50 >= screen_h ) {
    ptr_y = screen_h - ( int ) widget_h - 27;
  }

  if ( ptr_x <= 0 ) {
    ptr_x = 2;
  }

  if ( ptr_y <= 0 ) {
    ptr_y = 2;
  }

  XtVaSetValues ( widget, 
      XmNx,         ptr_x,
      XmNy,         ptr_y,
      NULL );
}
*/

void
DestroyAllIprHypDialogs ()
{
  int i;
/***
printf ( "DestroyAllIprHypDialogs - start\n" ); fflush ( stdout );
***/
  for ( i = 0 ; i < 10 ; i++ ) {
    if ( ipr_hyp_sch_dialog_up [ i ] ) {
/***
printf ( "   --->>> DestroyAllIprHypDialogs %d %d\n", i, ipr_hyp_sch_dialog [ i ] ); fflush ( stdout );
***/
      XtPopdown ( ipr_hyp_sch_dialog [ i ] );
      XtDestroyWidget ( ipr_hyp_sch_dialog [ i ] );
      ipr_hyp_sch_dialog_up [ i ] = 0;
    }
  }
  if ( ipr_hyp_dialog_up ) {
/***
printf ( "   --->>> DestroyAllIprHypDialogs main %d\n", ipr_hyp_dialog ); fflush ( stdout );
***/
    XtPopdown ( ipr_hyp_dialog );
    XtDestroyWidget ( ipr_hyp_dialog );
    ipr_hyp_dialog_up = 0;
  }
/***
printf ( "DestroyAllIprHypDialogs - end\n" ); fflush ( stdout );
***/
}

/*
void
Popup_AnmTextDialog ()
{
  PositionWidgetRightMainWin ( anm_text_dialog, 10, 1 );
  XtPopup ( anm_text_dialog, XtGrabNone );
  XmUpdateDisplay ( anm_text_dialog );
}

void
ProcessAndDestroy_AnmTextDialog ()
{
  char * textptr;

  XtPopdown ( anm_text_dialog );
  textptr = XmTextGetString ( anm_text );
  anm_text_posn = curr_text_posn;
  curr_text = main_text;
  curr_text_posn = main_text_posn;
  if ( anm_text_posn > curr_text_posn ) {
    XmTextSetString ( curr_text, "" );
    curr_text_posn = ( XmTextPosition ) 0;
  }
  else if ( strlen ( textptr ) > curr_text_posn ) {
    RemoveTopCurrText ( strlen ( textptr ) );
  }
  XmTextInsert ( curr_text, curr_text_posn, textptr );
  curr_text_posn = curr_text_posn + strlen ( textptr );
  XmTextShowPosition ( curr_text, curr_text_posn );
  XmUpdateDisplay ( curr_text );
  XtDestroyWidget (  anm_text_dialog );
  RestoreAnmIprPaneSize ();
  XtFree ( textptr );
}

void
Popup_IprTextDialog ()
{
  PositionWidgetRightMainWin ( ipr_text_dialog, 10, 1 );
  XtPopup ( ipr_text_dialog, XtGrabNone );
  XmUpdateDisplay ( ipr_text_dialog );
}

void
ProcessAndDestroy_IprTextDialog ()
{
  char * textptr;

  XtPopdown ( ipr_text_dialog );
  textptr = XmTextGetString ( ipr_text );
  ipr_text_posn = curr_text_posn;
  curr_text = main_text;
  curr_text_posn = main_text_posn;
  if ( ipr_text_posn > curr_text_posn ) {
    XmTextSetString ( curr_text, "" );
    curr_text_posn = ( XmTextPosition ) 0;
  }
  else if ( strlen ( textptr ) > curr_text_posn ) {
    RemoveTopCurrText ( strlen ( textptr ) );
  }
  XmTextInsert ( curr_text, curr_text_posn, textptr );
  curr_text_posn = curr_text_posn + strlen ( textptr );
  XmTextShowPosition ( curr_text, curr_text_posn );
  XmUpdateDisplay ( curr_text );
  XtDestroyWidget (  ipr_text_dialog );
  RestoreAnmIprPaneSize ();
  XtFree ( textptr );
  kil_the ( tmp_btool_ipr_thy );
}
*/

void
ChangeLabel ( label, text, set )
Widget label;
char * text;
int set;
{
  XmString xstr = XmStringCreateLtoR ( text, charset );
  if ( set ) {
    XtVaSetValues ( label,
        XmNlabelString,         xstr,
        XmNforeground,          option_set_col,        
        NULL );
  }
  else {
    XtVaSetValues ( label,
        XmNlabelString,         xstr,
        XmNforeground,          option_not_set_col,        
        NULL );
  }
  XmUpdateDisplay ( label );  
  XmStringFree ( xstr );
}

void
env_lab_CB ( widget, client_data ) /* Env label pressed (to change env) */
Widget widget;
XtPointer client_data;
{
  int requested_env, prog_lang;
  void DisplayNewEnv ();

  if ( IsDeSensitized () ) {
    Popup_Info ( " Can't change Environment whilst processing ... " );    
    return;
  }

  requested_env = * ( int * ) client_data;


  DisplayNewEnv ( requested_env );
}


check_started_from_cd ( char * sss )
{
/***
printf ( "\nstarted_from_cd = %d\ncd_dialog = %d\n\n",  started_from_cd, ( int ) cd_dialog );
***/
  if ( started_from_cd  ) {
    if ( cd_dialog != ( Widget ) 0 ) {
      XtPopup ( cd_dialog, XtGrabNone );
      XmUpdateDisplay ( cd_dialog );
    }
    else {
      
      if ( sss [ 0 ] != '\0' )  printf ( "\n     %s\n", sss );
      printf("\n     B-Toolkit invocation aborted\n\n\n");
      DisplayCurrWinText ( "\n     B-Toolkit invocation aborted\n\n\n");
      unlink ( ".Bcjm" );
      unlink ( ".Bmvr" );
      unlink ( pid_id_file );
      unlink ( "HTX/ConstructsSummary.html" );
      unlink ( "HTX" );
      Kill_bplatform_and_exit ( 1, 0 );
    }
  }
  else {
    DisplayCurrentEnv ();
  }
}

/**************************************************
          ConfirmDialog callback
***************************************************/

void
Popup_ConfirmDialog_CB ( dialog, client_data, call_data )
Widget dialog;
XtPointer client_data;
XtPointer call_data;
{
  int ok_pressed;
  int conf_flag = confirm_flag;
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;

/***/
printf ( "Popup_ConfirmDialog_CB\n" );
printf ( "confirm_flag %d  curr_env %d ", confirm_flag, curr_env );
printf ( "client_data %d\n", * ( int * ) client_data );
/***/

  confirm_flag = 0;

  /***
  destroy parent dialog/get OK or CANCEL
  ***/
  if ( cbs->reason == XmCR_PROTOCOLS ) {    /*** WM Close ***/
    ok_pressed = 0;
/***
printf ( "dialog        = %d\n", dialog );
***/
    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );
    XtDestroyWidget ( dialog );
  }
  else {
    if ( ( * ( int * ) client_data ) == OK_BUTTON )
      ok_pressed = 1;
    else
      ok_pressed = 0;
/***
printf ( "dialog        = %d\n", XtParent ( dialog ) );
***/
    XtPopdown ( XtParent ( dialog ) );
    XmUpdateDisplay ( XtParent ( dialog ) );
    XtDestroyWidget ( XtParent ( dialog ) );
  }

/***
printf ( "cbs->reason   = %d\n", cbs->reason );
printf ( "ok_pressed    = %d\n", ok_pressed );
***/

  switch ( conf_flag ) {

  case commitD_but_confirm:           /*** commitD_but_confirm ***/

    if ( ok_pressed ) {
      CommitAnnotationEdits ( curr_obj, /* reset_dmu_flag = */ 0 );
    }
    else {
      DisplayCurrWinText ( "\n  Commit aborted\n" );
      commit_aborted = 1;
    }
    break;


  case commit_doc_rst_but_confirm:           /*** commit_doc_rst_but_confirm ***/

    if ( ok_pressed ) {
      Load_SRC_CFG_Names ( curr_obj );
      CommitAnnotationEdits ( curr_obj, /* reset_dmu_flag = */ 1 );
    }
    else {
      DisplayCurrWinText ( "\n  Reset document aborted\n" );
      commit_aborted = 1;
    }
    break;


  case rst_cde_but_confirm:           /*** rst_cde_but_confirm ***/

    if ( ok_pressed ) {
      ResetTranslatedConstruct ( curr_obj );
    }
    else {
      DisplayCurrWinText ( "\n  Code module reset aborted\n" );
      commit_aborted = 1;
    }
    break;

  case commit_but_confirm:           /*** commit_but_confirm ***/

    if ( ok_pressed ) {
      CommitMathsEdits ( curr_obj );
    }
    else {
      DisplayCurrWinText ( "\n  Commit aborted\n" );
      commit_aborted = 1;
    }
    break;


  case rst_cst_but_confirm:    /*** rst_cst_but_confirm ***/

    radiobox_flag = 0;
    if ( ok_pressed ) {
      ResetConstruct ( curr_obj, 1 );
    }
    else {
      DisplayCurrWinText ( "\n  Construct reset aborted\n" );
      DisplayCurrentEnv ();
    }
    break;


  case close_confirm:           /*** close_confirm ***/

    if ( ok_pressed ) {
      CommitMathsEdits ( curr_obj );
    }
    else {
      DisplayCurrWinText ( "\n  Commit aborted\n" );
      commit_aborted = 1;
    }
    break;


  case close_all_confirm:           /*** close_all_confirm ***/

    if ( ok_pressed ) {
      CommitMathsEdits ( curr_obj );
    }
    else {
      DisplayCurrWinText ( "\n  Commit aborted\n" );
      commit_aborted = 1;
      CloseAllOpenFilesNext ();
    }
    break;


  case commit_all_confirm:           /*** commit_all_confirm ***/

    if ( ok_pressed ) {
      CommitMathsEdits ( curr_obj );
    }
    else {
      DisplayCurrWinText ( "\n  Commit aborted\n" );
      commit_aborted = 1;
      CommitAllOpenEditedFilesNext ();
    }
    break;


  case update_from_src_confirm:           /*** update_from_src_confirm ***/

    if ( ok_pressed ) {
      CommitMathsEdits ( curr_obj );
    }
    else {
      DisplayCurrWinText ( "\n  Commit aborted\n" );
      commit_aborted = 1;
      ProcessUpdateFromSRC_Next ();
    }
    break;


  case commit_all_remake_confirm:   /*** commit_all_remake_confirm ***/

    if ( ok_pressed ) {
/***
printf ( "2 commit_all_remake_radiobox %s\n", GetName ( curr_obj ) );
***/
      CommitMathsEdits ( curr_obj );
    }
    else {
      DisplayCurrWinText ( "\n  Commit aborted\n" );
      commit_aborted = 1;
      CommitAll_Remake_OpenEditedFilesNext ();
    }
    break;


  case continue_remake_confirm:   /*** continue_remake_confirm ***/

    if ( ok_pressed ) {
      /***
      load all constructs into gset1
      ***/
      int i, rr;
      void LoadAllConstructsInto_gset1 ();
      LoadAllConstructsInto_gset1 ();
      Remake ( dry_run );
      if ( ! sel_arr_tot ) {
        Popup_Info ( "    No remake required!    " );    
      }
      else {
        /* radiobox_flag = remake_all_or_construct_radiobox; */
	/*
        Popup_Remake ( top_level );
	*/
        if ( Commit_All_type == Commit_All_remake_all ) {
          Pre_Remake ( remake_all_constructs );
	}
        else {
          Pre_Remake ( remake_construct );
	}
      }
    }
    else {
      DisplayCurrWinText ( "\n  Remake aborted\n" );
      DisplayCurrentEnv ();
    }
    break;


  case remove_confirm:              /*** remove_confirm ***/

    if ( ok_pressed ) {
      ResetAllDependents ( curr_obj );
      if ( IsPrfObj ( curr_obj ) )
        RemoveProofObj (curr_obj );
      else
        RemoveConstruct ( curr_obj, 1 );     /* dependencies */
    }
    else {
      sprintf ( buf, "\n  Removal of %s aborted\n", GetName ( curr_obj ) );
      DisplayCurrWinText ( buf );
    }
    RemoveNext ();
    break;


  case save_browse_confirm:              /*** save_browse_confirm ***/

    if ( ok_pressed ) {
      SaveBrowse ( additional_string );
    }
    break;

  case remake_confirm:              /*** remake_confirm ***/

    if ( ok_pressed ) {
      Remake_Proceed ();
    }
    else {
      DisplayCurrWinText ( "\n  Remake aborted\n" );
    }
    break;


  case save_options_confirm:         /*** save_options_confirm ***/

    if ( ok_pressed ) {
      SaveCurrentOptions_Proceed ();
    }
    else {
      DisplayCurrWinText ( "\n  Save Current Options as Globals aborted\n" );
    }
    break;


  case restore_options_confirm:        /*** restore_options_confirm ***/

    if ( ok_pressed ) {
      RestoreDefaultOptions_Proceed ( 1 );
    }
    else {
      DisplayCurrWinText ( "\n  Set Options from Globals aborted\n" );
    }
    break;

  case new_dev_dir_confirm:        /*** new_dev_dir_confirm ***/

   printf("case new_dev_dir_confirm\n");

    if ( ok_pressed ) {
      ChangeDirectoryNewDir ( buf );
    }
    else {
      if ( started_from_cd  ) {
        check_started_from_cd ( "" );
      }
      else {
/***
printf ( "\nstarted_from_cd = %d\ncd_dialog = %d\n\n",  started_from_cd, ( int ) cd_dialog );
***/
        if ( cd_dialog != ( Widget ) 0 ) {
          XtPopup ( cd_dialog, XtGrabNone );
          XmUpdateDisplay ( cd_dialog );
        }
        else {
          Popup_Info ( "   Change Directory aborted   " );
          DisplayCurrentEnv ();
	}
      }
    }
    break;


  case rem_SLIB_confirm:        /*** rem_SLIB_confirm ***/

    if ( ok_pressed ) {
      int j;
      sprintf ( buf, "rm %s/BLIB/LIB/CFG/%s", BKIT_path, fifo_write_buf );
      system ( buf );
      sprintf ( buf, "rm %s/BLIB/LIB/ANL/%s.anl", BKIT_path, fifo_write_buf );
      system ( buf );
      j = 0;
      while ( fifo_write_buf [ j ] != '.' ) j++;
      fifo_write_buf [ j ] = '\0';
      sprintf ( buf, "rm %s/BLIB/LIB/TYP/%s.mri.typ", BKIT_path, fifo_write_buf );
      system ( buf );
      sprintf ( buf, "rm %s/BLIB/LIB/CDE/C/%s.*", BKIT_path, fifo_write_buf );
      system ( buf );
      sprintf ( buf, "\n  Removed SLIB %s\n", fifo_write_buf );
      DisplayCurrWinText ( buf );
    }
    else {
      sprintf ( buf, "  SLIB %s remove aborted  ", fifo_write_buf );
      Popup_Info ( buf );
    }
    break;

  case cre_new_dir_dev_confirm:   /*** cre_new_dir_dev_confirm ***/

    {
      FILE * Bcom;

      if ( ok_pressed ) {

        radiobox_flag = 0;

/***
printf ( "case cre_new_dir_dev_confirm\n" );
printf ( "additional_string = `%s'\n", additional_string );
***/

        if ( mkdir ( additional_string, S_IRUSR | S_IWUSR | S_IXUSR |
                              S_IRGRP | S_IXGRP | 
		              S_IROTH | S_IXOTH ) != 0 ) {
          sprintf ( fifo_write_buf, "Can't create %s", additional_string );
          XtPopup ( global_widget1, XtGrabNone );
          XmUpdateDisplay ( global_widget );
          Popup_Info ( fifo_write_buf );
          return;
        }

        /***
        write new dir in .Bcom for BSession - prefix with aaa!
        ***/
        Bcom = fopen ( ".Bcom", "w" );
        if ( Bcom == NULL ) {
          AbortedMsgFile ( "\"%s\" for writing", ".Bcom" );
          BT_err_exit ( 0 );
          return;
        }
        fprintf ( Bcom, "aaa%s", additional_string );
        fclose ( Bcom );

        /***
        write new dir in .Bcom for BSession - no prefix!
        ***/
        Bcom = fopen ( ".BBBcom", "w" );
        if ( Bcom == NULL ) {
          AbortedMsgFile ( "\"%s\" for writing", ".BBBcom" );
          BT_err_exit ( 0 );
          return;
        }
        fprintf ( Bcom, "%s", additional_string );
        fclose ( Bcom );

        strcpy ( fifo_write_buf, "0:" );
        Cre_fifo_write_buf_cmd_num ( BT_CK_PARSE_BCOM, 0 );
        InvokeB( without_XTerm, 1 );

      }

      else {
          XtPopup ( global_widget1, XtGrabNone );
          XmUpdateDisplay ( global_widget1 );
      }

    }
    break;


/*
  case  rsl_selection_confirm:     /???  rsl_selection_confirm ???/
     if ( ok_pressed ) RSL_confirmed ( curr_obj );
     break;
*/

  case  reload_PMD_confirm:        /***  reload_PMD_confirm ***/

    if ( ok_pressed ) {
      strcpy ( fifo_write_buf, "(?,3):" );   /* ProveLemma_rld_Option */
      Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
      InvokeB ( without_XTerm, 1 );
    }
    else {
      strcpy ( fifo_write_buf, "(?,999):" ); /* ProveLemma_skip_Option */
      Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
      InvokeB ( without_XTerm, 1 );
    }
    break;

 default:

    if ( ok_pressed ) strcpy ( fifo_write_buf, "yes:" );
    else              strcpy ( fifo_write_buf, "no:" );
    Cre_fifo_write_buf_cmd_0 ( BT_BSEL );

    /***
    wait
    ***/
    InvokeB ( without_XTerm, 1 );
    break;

  }
  }

/**************************************************
          Radiobox callback
***************************************************/

void
NEW_Dialog_RadioBox_CB ( button, client_data, call_data )
Widget button;
int client_data;
/*long client_data;*/
XtPointer call_data;
{
  static int first_time = 1;
  static int double_click = 0;
  static XtIntervalId id = 0;
  int n = * ( int * ) client_data;
  /*long n = * ( long * ) client_data;*/
  XmPushButtonCallbackStruct * cbs =
              ( XmPushButtonCallbackStruct * ) call_data;

/***
if ( ! second_visit ) printf ( "\n" );
printf ( "NEW_Dialog_RadioBox_CB n=%d second_visit=%d waiting_option=%d\n", * ( int * ) client_data, second_visit, waiting_option );
***/

/***
if ( cbs->reason == XmCR_PROTOCOLS )
  printf ( "cbs->reason == XmCR_PROTOCOLS\n" );
else
  printf ( "cbs->reason != XmCR_PROTOCOLS\n" );
***/

/*
#ifdef LINUX_VERSION
  if ( ! second_visit ) {
#else
  if ( second_visit ) {
#endif /? LINUX_VERSION ?/
*/

  if ( second_visit ) {

/***
printf ( "setting XmNuserData of %d to address %d (value=%d)\n", XtParent ( XtParent ( XtParent ( button ) ) ), ( XtPointer ) & c_arr [ n ], c_arr [ n ] );
***/

    XtVaSetValues ( XtParent ( XtParent ( XtParent ( button ) ) ),
        XmNuserData,     ( XtPointer ) & c_arr [ n ],
        NULL);
  }

  else {  /* ! second_visit */

    if ( ! waiting_option )  {
      waiting_option = 1;
      id = XtAppAddTimeOut ( app, ( long unsigned ) mc_interval,
                   ( XtTimerCallbackProc ) ResetWaitingOption, NULL );
    }
    else {
      waiting_option = 0;
      double_click = 1;
    }
  }

  if ( double_click ) {
    double_click = 0;
    if ( first_time ) {
      first_time = 0;
    }
    else {
      struct ok_cancel_but_struct but_struct;
/*
      XmAnyCallbackStruct cbs1 = { XmCR_PROTOCOLS - 1, ( XtPointer ) NULL };
*/
      XmAnyCallbackStruct cbs1;
      cbs1.reason = XmCR_PROTOCOLS - 1;
      but_struct.but           = OK_BUTTON;
      but_struct.file_diff_but = global_file_diff_but;
/***
printf ( "calling Popup_RadioBox_Dialog_CB with %d\n", XtParent ( button ) );
***/
      Popup_RadioBox_Dialog_CB ( XtParent ( button ),
                                 ( XtPointer ) & but_struct,
                                 ( XtPointer ) & cbs1 );
    }
  }

  if   ( second_visit ) second_visit = 0;
  else                  second_visit = 1;
}

void
IprReasoningDepth_CB ( widget, but_num )
Widget widget;
int but_num;
{
  modIth_flags ( Ipr_Prf_Level_num, but_num );
}

void
NEW_Dialog_RadioBox_EditedFileExists_CB ( button, client_data, call_data )
Widget button;
int client_data;
/*long client_data;*/
XtPointer call_data;
{
  static int first_time = 1;
  static int double_click = 0;
  static XtIntervalId id = 0;
  int n = * ( int * ) client_data;
  /*long n = * ( long * ) client_data;*/
  XmPushButtonCallbackStruct * cbs =
              ( XmPushButtonCallbackStruct * ) call_data;

/***
if ( ! second_visit ) printf ( "\n" );
printf ( "NEW_Dialog_RadioBox_EditedFileExists_CB n=%d second_visit=%d waiting_option=%d\n", * ( int * ) client_data, second_visit, waiting_option );
***/

  if ( second_visit ) {
    XtVaSetValues ( XtParent ( XtParent ( XtParent ( button ) ) ),
        XmNuserData,     ( XtPointer ) & c_arr [ n ],
        NULL);
  }

  else {  /* ! second_visit */

     if ( ! waiting_option )  {
      waiting_option = 1;
      id = XtAppAddTimeOut ( app, ( long unsigned ) mc_interval,
                   ( XtTimerCallbackProc ) ResetWaitingOption, NULL );
    }
    else {
      waiting_option = 0;
      double_click = 1;
    }
  }

  if ( double_click ) {
    double_click = 0;
    if ( first_time ) {
      first_time = 0;
    }
    else {
      struct ok_cancel_but_struct but_struct;
/*
      XmAnyCallbackStruct cbs1 = { XmCR_PROTOCOLS - 1, ( XtPointer ) NULL };
*/
      XmAnyCallbackStruct cbs1;
      cbs1.reason = XmCR_PROTOCOLS - 1;

      but_struct.but           = OK_BUTTON;
      but_struct.file_diff_but = 2;
      Popup_EditedFileExists_Dialog_CB ( XtParent ( button ),
                                         ( XtPointer ) & but_struct,
                                         ( XtPointer ) & cbs1 );
    }
  }

  if   ( second_visit ) second_visit = 0;
  else                  second_visit = 1;
}
/**************************************************
          ToggleBox check
***************************************************/

int
ToggleBox_check_toggles_no_sel_str ()
{
  int i, set;

  i = 0;
  set = 0;
  while ( i < sel_arr_tot & ! set ) {
    set = sel_arr_tog [ i ];
    i++;
  }
  return ( set );
}

int
ToggleBox_check_toggles ()
{
  int i, j;
  int done;

  strcpy ( fifo_write_buf, "(?" );

  j = 0;
  for ( i = 0 ; i < sel_arr_tot ; i++ ) {
    if ( sel_arr_tog [ i ] ) {

      done = 0;
      strcat ( fifo_write_buf, "," );

      /***
      check for Save state
      ***/
      if ( strcmp ( sel_str_arr [ i ], "New Initialisation Script" ) == 0 ) {
        if ( anm_invariant_flag ) strcat ( fifo_write_buf, "101" );
        else                      strcat ( fifo_write_buf, "1" );
        done = 1;
      }
      /***
      check for Undo last operation
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Undo last operation" ) == 0 ) {
        if ( anm_invariant_flag ) strcat ( fifo_write_buf, "102" );
        else                      strcat ( fifo_write_buf, "2" );
        done = 1;
      }
      /***
      check for Save as ANIMATE Script Initialisation
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Save as ANIMATE Script Initialisation" ) == 0 ) {
        strcat ( fifo_write_buf, "1" );
        done = 1;
      }
      /***
      check for Restore initial state
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Restore initial state" ) == 0 ) {
        if ( anm_invariant_flag ) strcat ( fifo_write_buf, "103" );
        else                      strcat ( fifo_write_buf, "3" );
        done = 1;
      }
      /***
      check for Restart animation
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Restart animation" ) == 0 ) {
        if ( anm_invariant_flag ) strcat ( fifo_write_buf, "104" );
        else                      strcat ( fifo_write_buf, "4" );
        done = 1;
      }
      /***
      check for Edit theory file
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Edit theory file" ) == 0 ) {
        if ( anm_invariant_flag ) strcat ( fifo_write_buf, "105" );
        else                      strcat ( fifo_write_buf, "5" );
        done = 1;
      }
      /***
      check for Set state variables
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Set state variables" ) == 0 ) {
        if ( anm_invariant_flag ) strcat ( fifo_write_buf, "106" );
        else                      strcat ( fifo_write_buf, "6" );
        done = 1;
      }
      /***
      check for Run InterProver
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Run InterProver" ) == 0 ) {
        DestroyAllIprHypDialogs ();
        strcat ( fifo_write_buf, "1" );
        done = 1;
      }
      /***
      check for Continue
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Continue" ) == 0 ) {
        DestroyAllIprHypDialogs ();
        strcat ( fifo_write_buf, "1" );
        done = 1;
      }
      /***
      check for Backtrack
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Backtrack" ) == 0 ) {
        DestroyAllIprHypDialogs ();
        strcat ( fifo_write_buf, "1" );
        done = 1;
      }
      /***
      check for Show Hypotheses
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Show Hypotheses" ) == 0 ) {
        strcat ( fifo_write_buf, "2" );
        done = 1;
      }
      /***
      check for Create Lemma
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Create Lemma" ) == 0 ) {
        DestroyAllIprHypDialogs ();
        strcat ( fifo_write_buf, "3" );
        XtUnmanageChild ( constructs_rc );
        XmUpdateDisplay ( constructs_scroll );
        XtDestroyWidget ( constructs_rc );
        constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
            xmRowColumnWidgetClass,         constructs_scroll,
            XmNorientation,                 XmVERTICAL,
            XmNmarginWidth,                 18,
            XmNmarginHeight,                10,
            XmNspacing,                     0,
            XmNresizable,                   True,
            NULL );
        done = 1;
      }
      /***
      check for "Create & Prove Lemma
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Create & Prove Lemma" ) == 0 ) {
        DestroyAllIprHypDialogs ();
/*
        XtUnmanageChild ( ipr_label );
        XmUpdateDisplay ( ipr_label );
        XtUnmanageChild ( sub_frame1 );
        XmUpdateDisplay ( sub_frame1 );
        XtDestroyWidget ( sub_frame1 );
        sub_frame1 = ( Widget ) NULL;
        XtUnmanageChild ( sub_frame2 );
        XmUpdateDisplay ( sub_frame2 );
        XtDestroyWidget ( sub_frame2 );
        sub_frame2 = ( Widget ) NULL;
*/
        strcat ( fifo_write_buf, "4" );
        XtUnmanageChild ( constructs_rc );
        XmUpdateDisplay ( constructs_scroll );
        XtDestroyWidget ( constructs_rc );
        constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
            xmRowColumnWidgetClass,         constructs_scroll,
            XmNorientation,                 XmVERTICAL,
            XmNmarginWidth,                 18,
            XmNmarginHeight,                10,
            XmNspacing,                     0,
            XmNresizable,                   True,
            NULL );
        done = 1;
      }
      /***
      check for Reload PROOFMETHOD
      ***/
      else if ( strcmp ( sel_str_arr [ i ], "Reload PROOFMETHOD" ) == 0 ) {
        dont_destroy_display = 1;          /* Reload PROOFMETHOD - don't change! */
        strcat ( fifo_write_buf, "3" );
        done = 1;
      }

      if ( ! done ) { /*** not SaveState etc... ***/
        /***
        print only up to ':' (if present) - for SelFromList with string
        ***/
        int k = 0;
        int ll = strlen ( fifo_write_buf );

        while ( sel_str_arr [ i ] [ k ] != ':' &&
                sel_str_arr [ i ] [ k ] != '\0'   ) {
          fifo_write_buf [ ll ] = sel_str_arr [ i ] [ k ];
          ll++;
          k++;
        }
        fifo_write_buf [ ll ] = '\0';
        if ( ( curr_env == anm_env ) && ( anm_invariant_flag ) )
          strcat ( fifo_write_buf, ".1" );
     }
      j++;
    }
  }

  strcat ( fifo_write_buf, "):" );

/***
printf ( "ToggleBox_check_toggles - fifo_write_buf |%s|\n", fifo_write_buf );
***/
  return ( j ); /* to Popup_Sel_Dialog_CB */
}

/**************************************************
          Reset all box callback
***************************************************/

void
ResetAll_CB ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{

  /***
  loads all construct obj into gset1
  and the iterates through it
  ***/

  int rr, nn, obj, type, ext, reset_mesg_displayed;
  void LoadAllConstructsInto_gset1 ();

  /***
  if OK - reset all!
  ***/
  Widget dialog;
  int ok_pressed, cancel_pressed;
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;

  /***
  get parent dialog/OK or CANCEL
  ***/
  if ( cbs->reason == XmCR_PROTOCOLS ) {    /*** WM Close ***/
    dialog =  widget;
    ok_pressed = 0;
    cancel_pressed = 1;
  }
  else {
    dialog = XtParent ( widget );
    if ( ( * ( int * ) client_data ) == OK_BUTTON ) {
      ok_pressed = 1;
      cancel_pressed = 0;
    }
    else if ( ( * ( int * ) client_data ) == CANCEL_BUTTON ) {
      ok_pressed = 0;
      cancel_pressed = 1;
    }
    else {
      ok_pressed = 0;
      cancel_pressed = 0;
    }
  }

/***
printf ( "cbs->reason    = %d\n", cbs->reason );
printf ( "dialog         = %d\n", dialog );
printf ( "ok_pressed     = %d\n", ok_pressed );
printf ( "cancel_pressed = %d\n", cancel_pressed );
***/

  if ( ok_pressed ) {
 
    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );
    reset_mesg_displayed = 0;
    DeSensitize ();

    LoadAllConstructsInto_gset1 ();

    card_gset1 ( &nn );
    while ( nn ) {

      valOrd_gset1 ( &obj, nn );

      val_type ( &type, obj );
      val_ext ( &ext, obj );
      Load_SRC_CFG_Names ( obj );

      switch ( type ) {

      case usr:
      case usr_vhdl:

        val_ext ( &ext, obj );
        switch ( ext ) {

	case mch:
	case ref:
	case imp:

          CheckUnanalyse ( obj, 1 );
          if ( ! reset_mesg_displayed ) {
            DisplayCurrWinText ( "\n  Resetting all constructs ..." );
            reset_mesg_displayed = 1;
	  }
    	  break;

	case doc:

          CheckUndoc ( obj );
          if ( ! reset_mesg_displayed ) {
            DisplayCurrWinText ( "\n  Resetting all constructs ..." );
            reset_mesg_displayed = 1;
	  }
	  break;

	case bse:
	case ops:
	case enm:
	case itf:

          CheckUngen ( obj );
          if ( ! reset_mesg_displayed ) {
            DisplayCurrWinText ( "\n  Resetting all constructs ..." );
            reset_mesg_displayed = 1;
	  }
	  break;

	case map:

          rem_sees_uses ( obj );
          KillConstruct ( obj );
          if ( ! reset_mesg_displayed ) {
            DisplayCurrWinText ( "\n  Resetting all constructs ..." );
            reset_mesg_displayed = 1;
	  }
	  break;

	} /* switch ( ext ) */
        break;

      case bse_gen:
      case enm_gen:
      case itf_gen:
      case prf_gen:
      case gen_vhdl:
        KillConstruct ( obj );
        if ( ! reset_mesg_displayed ) {
          DisplayCurrWinText ( "\n  Resetting all constructs ..." );
          reset_mesg_displayed = 1;
        }
	break;

      case lib:
      case lib_vhdl:
          CheckUndoc ( obj );
          if ( ! reset_mesg_displayed ) {
            DisplayCurrWinText ( "\n  Resetting all constructs ..." );
            reset_mesg_displayed = 1;
	  }
	  break;

      } /* switch ( type ) */

      nn--;

    } /* while ( nn ) */

    DisplayCurrWinText ( " done\n" );
    DisplayCurrentEnv ();

  } /* if ( ok_pressed ) */

  else if ( ! cancel_pressed ) { /*** HELP_BUTTON ***/
    struct help_struct help_data;

    help_data.type   = DIALOG_HELP;
    help_data.width  = 290;
    help_data.height = 125;
    help_data.text   = ( char * ) "All processing will be lost\n(although a `Remake' will restore the\ndevelopment to the current state).";

    Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
  }

  else {                        /*** CANCEL_BUTTON ***/
    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );
  }
}


/**************************************************
          Selection box callback
***************************************************/

void
Popup_Sel_Dialog_CB ( button, client_data, call_data )
Widget button;
XtPointer client_data;
XtPointer call_data;
{
  int rad_but;
  Widget dialog;
  int selection_option;
  int ok_pressed;
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;
  char* editorCommand;

/***
printf ( "Popup_Sel_Dialog_CB - Popup_Sel_flag %d\n", Popup_Sel_flag );
printf ( "curr_env %d\n", curr_env );
***/

  /***
  get parent dialog/OK or CANCEL
  ***/
  if ( cbs->reason == XmCR_PROTOCOLS ) {    /*** WM Close ***/
    dialog =  button;
    ok_pressed = 0;
  }
  else {
    dialog = XtParent ( XtParent ( XtParent ( button ) ) );

    if ( ( * ( int * ) client_data ) == ALL_BUTTON ) {
      for ( i = 0; i < sel_arr_tot; i++ ) {
        XmToggleButtonSetState ( sel_arr_but [ i ], True, False );
        sel_arr_tog [ i ] = 1; 
      }
      return;
    }

    if ( ( * ( int * ) client_data ) == NONE_BUTTON ) {
      for ( i = 0; i < sel_arr_tot; i++ ) {
        XmToggleButtonSetState ( sel_arr_but [ i ], False, False );
        sel_arr_tog [ i ] = 0; 
      }
      return;
    }

    if ( ( * ( int * ) client_data ) == OK_BUTTON )
      ok_pressed = 1;
    else
      ok_pressed = 0;
  }

/***
printf ( "cbs->reason   = %d\n", cbs->reason );
printf ( "dialog        = %d\n", dialog );
printf ( "ok_pressed    = %d\n", ok_pressed );
***/

  switch ( Popup_Sel_flag ) {

  case interprover_selection:  /*** interprover_selection ***/

    if ( ( ok_pressed ) && ( Ipr_Prf_Level_dialog_isdplayed ) ) {
      FILE * Bipl;
      int level;
      Ipr_Prf_Level_dialog_isdplayed = 0;
      Bipl = fopen ( ".Bipl", "w" );
      if ( Bipl == NULL ) {
        AbortedMsgFile ( "\".Bipl\" for writing" );
        BT_err_exit ( 0 );
        return;
      }
      valIth_flags ( &level, Ipr_Prf_Level_num );
      PrintNum ( Bipl, level );
      fclose ( Bipl );
    }
  
    if ( ! ok_pressed ) {
      DestroyAllIprHypDialogs ();
      XtPopdown ( dialog );
      Popup_Sel_flag = 0;
      /***
      write Bsel, unmanage sub_frames
      destroy dialog & call IPRButton_CB
      ***/
/*
      XtUnmanageChild ( ipr_label );
      XmUpdateDisplay ( ipr_label );
      XtUnmanageChild ( sub_frame1 );
      XmUpdateDisplay ( sub_frame1 );
      XtDestroyWidget ( sub_frame2 );
      sub_frame2 = ( Widget ) NULL;
      if ( curr_env == ipr_pob_env ) {
        XtUnmanageChild ( sub_frame2 );
        XmUpdateDisplay ( sub_frame2 );
        XtDestroyWidget ( sub_frame2 );
        sub_frame2 = ( Widget ) NULL;
      }
*/
      XtUnmanageChild ( constructs_rc );
      XmUpdateDisplay ( constructs_scroll );
      XtDestroyWidget ( constructs_rc );
      constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
          xmRowColumnWidgetClass,         constructs_scroll,
          XmNorientation,                 XmVERTICAL,
          XmNmarginWidth,                 18,
          XmNmarginHeight,                10,
          XmNspacing,                     0,
          XmNresizable,                   True,
          NULL );
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
      InvokeB ( without_XTerm, 1 );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        XtPopdown ( dialog );
        /*        XmUpdateDisplay ( dialog ); */
	/*        XtDestroyWidget ( dialog ); */
        Popup_Sel_flag = 0;
        if ( strcmp ( sel_str_arr [ i ], 
                        "Browse PROOFMETHOD file" ) == 0 ) {
          int nm [ 50 ], ex, cc;
          GetExtNumFromString ( &ex, secondary_string );
          GetNameFromString ( nm, secondary_string );
          GetObjFromNameExt ( &cc, nm, ex );
          GetAllLevelPMD ( cc );
          Popup_Sel_flag = browse_pmd_selection;
          Popup_SelOne_Dialog ( top_level, "PROOFMETHOD to browse" );
	}
        else if ( strcmp ( sel_str_arr [ i ], 
                        "Edit Global PROOFMETHOD file" ) == 0 ) {
          int i = 0;
          int all_sp = 1;
          Retrieve_String ( provers_str_num, primary_string );
          while ( primary_string [ i ] != '\0' && all_sp ) {
            if ( primary_string [ i ] != ' ' ) all_sp = 0;
            i++;
	  }
          if ( all_sp ) {
            Ipr_Sel_Ops ( top_level, Ipr_Prf_Option, 0 );
            XmUpdateDisplay ( top_level );
            Popup_Minor_Err ( NULL, "Global PROOFMETHOD string not set\n  (Set in Top Bar Options - Provers)" );
	  }
          else {
            OpenGlobalPMD ();
	  }         
	}
        else if ( strcmp ( sel_str_arr [ i ], 
                        "Edit Current PROOFMETHOD file" ) == 0 ) {
          OpenCurrentPMD ( curr_obj );
	}
        else if ( strcmp ( sel_str_arr [ i ], 
                        "Set Max Generated Hypotheses" ) == 0 ) {
          Popup_SetMaxGenHyp ();
	}
        else {
          /***
          Bsel already written, sub_frames unmanaged (ToggleBox_check_toggles)
          destroy dialog & call IPRButton_CB
          ***/
          Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
          IPRButton_CB ();
	}
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;


  case commit_all_edit_selection:  /*** commit_all_edit_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();
      if ( i ) {
        DeSensitize ();
        Popup_Sel_flag = 0;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        commit_all_count = 0;
        CommitAllOpenEditedFilesNext ();
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;


  case commit_all_remake_edit_selection:
                                   /*** commit_all_remake_edit_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      strcpy ( primary_string, "Proceed with Remake? " );
      strcpy ( secondary_string, "Edited constructs will not be committed" );
      radiobox_flag = continue_remake_radiobox;
      confirm_flag = radiobox_flag;
      Popup_ConfirmDialog ( top_level );      
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();
      if ( i ) {
        Popup_Sel_flag = 0;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        commit_all_remake_count = 0;
        CommitAll_Remake_OpenEditedFilesNext ();
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;


  case close_all_edit_selection:  /*** close_all_edit_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();
      if ( i ) {
        DeSensitize ();
        Popup_Sel_flag = 0;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        close_all_count = 0;
        CloseAllOpenFilesNext ();
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;


  case introduce_SRC_selection:   /*** introduce_SRC_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        Popup_Sel_flag = 0;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        CreNumInBuf ( fifo_write_buf, BT_SRC );
/***
printf ( "fifo_write_buf=`%s'\n", fifo_write_buf );
***/
        Cre_tcp_env ();
        InvokeB ( without_XTerm, 1 );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case introduce_SLIB_selection:   /*** introduce_SLIB_selection ***/

    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );
    Popup_Sel_flag = 0;
    if ( ok_pressed ) {
      char str [ 100 ];
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        Popup_Sel_flag = 0;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        if ( strlen ( sel_str_arr [ i ] ) > 7 &&
             sel_str_arr [ i ] [ 0 ] == 'R' &&
             sel_str_arr [ i ] [ 1 ] == 'e' &&
             sel_str_arr [ i ] [ 2 ] == 'n' &&
             sel_str_arr [ i ] [ 3 ] == 'a' &&
             sel_str_arr [ i ] [ 4 ] == 'm' &&
             sel_str_arr [ i ] [ 5 ] == 'e' &&
             sel_str_arr [ i ] [ 6 ] == '_'    ) {
                  strcpy ( secondary_string, sel_str_arr [ i ] );
                  Popup_Sel_flag = introduce_SLIB_selection;
                  Popup_LIBRenamePromptDialog ( top_level, i );
	  }
          else {
            strcpy ( fifo_write_buf, "(?," );
            GetNameFromString ( str, sel_str_arr [ i ] );
            strcat ( fifo_write_buf, str );
            strcat ( fifo_write_buf, "):" );
            CreNumInBuf ( fifo_write_buf, BT_LIB_FRC_WITH_ENV );
            Cre_tcp_env ();
            InvokeB ( without_XTerm, 1 );
	  }
        }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;

  case introduce_TLIB_selection:   /*** introduce_TLIB_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      char str [ 100 ];
      int i = ToggleBox_check_toggles ();

      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        Popup_Sel_flag = 0;
        strcpy ( fifo_write_buf, sel_str_arr [ i ] );
        strcat ( fifo_write_buf, ":" );
        CreNumInBuf ( fifo_write_buf, BT_TLIB_WITH_ENV );
        Cre_tcp_env ();
        InvokeB ( without_XTerm, 1 );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case remove_selection:   /*** remove_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();

      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        DeSensitize ();
        Popup_Sel_flag = 0;
        remove_count = 0;
        radiobox_flag = remove_radiobox;
        RemoveNext ();
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;

  case remake_constructs_selection:   /*** remake_constructs_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      DisplayCurrWinText ( "\n  Remake aborted\n" );
    }
    else  { /*** OK_BUTTON ***/
      int i, rr;
      i = ToggleBox_check_toggles_no_sel_str ();
      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        Popup_Sel_flag = 0;
        /***
        load selected constructs into gset1
        ***/
        clear_gset1 ();
        for ( i = 0 ; i < sel_arr_tot ; i++ ) {
          if ( sel_arr_tog [ i ] ) {
            add_gset1 ( &rr, sel_obj_arr [ i ] );
            chk_rep ( rr, 89 );
	  }
	}
        Remake ( not_dry_run );
      }
      else {
        Popup_Info ( "Nothing selected!  " );
      }
    }
    break;



  case remake_jobs_selection:              /*** remake_jobs_selection ***/
  case analyse_generate_jobs_selection :   /*** analyse_generate_jobs_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      if ( Popup_Sel_flag  == remake_jobs_selection )
        DisplayCurrWinText ( "\n  Remake aborted\n" );
      else
        DisplayCurrWinText ( "\n  Analyse/generate aborted\n" );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();

      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        RemakeSelections ( Popup_Sel_flag );
        Popup_Sel_flag = 0;
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case rename_selection:   /*** rename_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();

      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        DeSensitize ();
        Popup_Sel_flag = 0;
        i = 0;
        while ( ! sel_arr_tog [ i ] ) { i++; }        
        Pre_Rename ( sel_obj_arr [ i ] );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case browse_selection:   /*** browse_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();

      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        Popup_Sel_flag = 0;
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }        
        curr_obj = sel_obj_arr [ i ];
        DeSensitize ();
        init_htx_curr_obj ();
        Popup_HtxDialog ();
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case browse_design_selection:   /*** browse_design_ & spec_selection ***/
  case browse_spec_selection:

    if ( ! ok_pressed ) {
      void dec_htx_curr_obj ();
      void BuildCurrBrowse ();
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      dec_htx_curr_obj ();
      BuildCurrBrowse ( htx_curr_obj [ htx_curr_obj_ptr ] );
      XtVaSetValues ( htx_done_but,   XmNsensitive, True, NULL );
      if ( htx_curr_obj_ptr == 0 ) {
        XtVaSetValues ( htx_prev_but, XmNsensitive, False, NULL );
      }
      else 
        XtVaSetValues ( htx_prev_but,   XmNsensitive, True, NULL );
       XtVaSetValues ( htx_spec_but,   XmNsensitive, True, NULL );
       XtVaSetValues ( htx_design_but, XmNsensitive, True, NULL );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();

      if ( i ) {
        int ext;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        Popup_Sel_flag = 0;
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }        
        val_ext ( & ext, sel_obj_arr [ i ] );
        if ( ext == imp ) {
          Load_DarrFromImpNode ( sel_obj_arr [ i ] );   /* BMotif_browser.c */
	}
        else {
          Load_DarrFromSpecNode ( sel_obj_arr [ i ] );   /* BMotif_browser.c */
	}
        DisplayTopNode ();
        XtVaSetValues ( htx_done_but,   XmNsensitive, True, NULL );
        if ( htx_curr_obj_ptr == 0 )
          XtVaSetValues ( htx_prev_but,   XmNsensitive, False, NULL );
        else 
          XtVaSetValues ( htx_prev_but,   XmNsensitive, True, NULL );
        XtVaSetValues ( htx_spec_but,   XmNsensitive, True, NULL );
        XtVaSetValues ( htx_design_but, XmNsensitive, True, NULL );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case browse_design_selection_top_win:   /*** browse_design_ & spec_selection ***/
  case browse_spec_selection_top_win:

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      ReDisplayCurrEnvFromBrowser ();
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();

      if ( i ) {
        int ext;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        Popup_Sel_flag = 0;
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }        
        XtVaSetValues ( htx_done_but,   XmNsensitive, True, NULL );
        if ( htx_curr_obj_ptr != 0 ) {
          XtVaSetValues ( htx_prev_but,   XmNsensitive, True, NULL );
	}
        XtVaSetValues ( htx_spec_but,   XmNsensitive, True, NULL );
        XtVaSetValues ( htx_design_but, XmNsensitive, True, NULL );
        val_ext ( & ext, sel_obj_arr [ i ] );
        if ( ext == imp ) {
          Load_DarrFromImpNode ( sel_obj_arr [ i ] );
	}
        else {
          Load_DarrFromSpecNode ( sel_obj_arr [ i ] );
	}
        DisplayTopNode ();
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case ref_anl_selection:       /*** ref_anl_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();

      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        Popup_Sel_flag = 0;
        sprintf ( fifo_write_buf, "%s:%d", sel_str_arr [ i ], BT_REF_ANL_WITH_ENV );
        Cre_tcp_env ();
        InvokeB ( without_XTerm, 1 );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case imp_anl_selection:       /*** imp_anl_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();

      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        Popup_Sel_flag = 0;
        strcpy ( fifo_write_buf, sel_str_arr [ i ] );
        strcat ( fifo_write_buf, ":" );
        CreNumInBuf ( fifo_write_buf, BT_IMP_ANL_WITH_ENV );
        Cre_tcp_env ();
        InvokeB ( without_XTerm, 1 );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case itf_anl_selection:       /*** itf_anl_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();

      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        Popup_Sel_flag = 0;
        strcpy ( fifo_write_buf, "(" );
        strcat ( fifo_write_buf, sel_str_arr [ i ] );
        strcat ( fifo_write_buf, "|" );
        {
          int cc, nn;
          cc = HasImp ( sel_obj_arr [ i ] );
          if ( cc ) {
            nn = GetSeenNotIpt ( cc );
/***
printf("seen but not imported:\n");
show_gset(2);
***/
            if ( nn ) {
              Cat_gset_tcp ( 2 );
            }
            else {
              strcat ( fifo_write_buf, "?" );
            }          
	  }
          else {
            strcat ( fifo_write_buf, "?" );
	  }
        }
        strcat ( fifo_write_buf, "):" );
        CreNumInBuf ( fifo_write_buf, BT_ITF_ANL_WITH_ENV );
        Cre_tcp_env ();
        InvokeB ( without_XTerm, 1 );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case enm_anl_selection:   /*** enm_anl_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/ 
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        Popup_Sel_flag = 0;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        CreNumInBuf ( fifo_write_buf, BT_ENUM_ANL_WITH_ENV );
        Cre_tcp_env ();
        InvokeB ( without_XTerm, 1 );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case introduce_cfg_CM_selection:   /*** enm_anl_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/ 
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        Popup_Sel_flag = 0;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        CreNumInBuf ( fifo_write_buf, BT_CMT_NEW_CM_CFG_VHDL );
        strcat ( fifo_write_buf, ":" );
        strcat ( fifo_write_buf, additional_string );
        InvokeB ( without_XTerm, 1 );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case doc_anl_selection:   /*** doc_anl_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/     
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        Popup_Sel_flag = 0;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        CreNumInBuf ( fifo_write_buf, BT_DOC_CFG_WITH_ENV );
        Cre_tcp_env ();
        InvokeB ( without_XTerm, 1 );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;


  case ppf_selection:   /*** ppf_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/ 
      int st, pob; 
      int i = ToggleBox_check_toggles_no_sel_str ();
      if ( i ) {
        Popup_Sel_flag = 0;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! sel_arr_tog [ i ] ) { i++; }
        sprintf ( fifo_write_buf, "(%s|%d|%d):", GetName ( curr_obj ),
                                             ( ( sel_obj_arr [ i ] ) / 1000000 ),
                                             ( ( sel_obj_arr [ i ] ) % 1000000 ) ); 
        val_curMRIState( &st, curr_obj );
        valIth_pob ( &pob, st, ( ( sel_obj_arr [ i ] ) / 1000000 + 1 ) );
        if ( pob < 0 ) {
          CreNumInBuf ( fifo_write_buf, BT_PFP_WITH_ENV_BTL );
	}
        else {
          CreNumInBuf ( fifo_write_buf, BT_PFP_WITH_ENV );
	}
        Cre_tcp_env ();
        strcpy ( xterm_title, "B-ProofPrinter" );
        InvokeB ( with_XTerm, 1 );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case rsl_selection:   /*** rsl_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();
      if ( i ) {
        int st, nn;
        Popup_Sel_flag = 0;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        val_curMRIState( &st, curr_obj );
	length_pob( &nn, st );
        nn = nn - i - 1;
/***
printf ( "%d levels to remove\n", nn );
***/
        while ( nn ) {
          RemoveLevel ( curr_obj );
          nn--;
	}
        sprintf ( buf, "\n  %s: Level %d restored\n", GetName ( curr_obj ), i );
        DisplayCurrWinText ( buf );
        SetDisplayField_obj_Changed ( curr_obj );
        DisplayCurrentEnv ();
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;



  case browse_pmd_selection:     /*** browse_pmd_selection ***/

    if ( ! ok_pressed ) {           /*** CANCEL_BUTTON ***/     
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      Popup_Sel_flag = 0;
      if ( ( curr_env ==  ipr_pob_env ) || ( curr_env ==  ipr_lem_env ) ) {
        Ipr_Sel_Ops ( top_level, Ipr_Prf_Option, 0 );
      }
      else {
        radiobox_flag = edit_pmd_radiobox;
        XtPopup ( temp_widget, XtGrabNone );
        XmUpdateDisplay ( temp_widget );
      }
    }
    else  {                         /*** OK_BUTTON ***/     
      int i = ToggleBox_check_toggles_no_sel_str ();
      if ( i ) {
        int st, nn;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        strcpy ( primary_string, "PMD/" );
        strcat ( primary_string, sel_str_arr [ i ] );
        if ( ( curr_env ==  ipr_pob_env ) || ( curr_env ==  ipr_lem_env ) ) {
          Ipr_Sel_Ops ( top_level, Ipr_Prf_Option, 0 );
	}
        else {
          radiobox_flag = edit_pmd_radiobox;
          XtPopup ( temp_widget, XtGrabNone );
          XmUpdateDisplay ( temp_widget );
	}
        DisplayBrowsePMD ( primary_string );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;

  case browse_out_selection:     /*** browse_out_selection ***/

    if ( ! ok_pressed ) {           /*** CANCEL_BUTTON ***/     
      void Popup_MainAnimatorMenu ();
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      Popup_Sel_flag = 0;
      Popup_MainAnimatorMenu ( curr_obj );
    }
    else  {                         /*** OK_BUTTON ***/     
      void Popup_MainAnimatorMenu ();
      struct stat stat_buf;
      FILE * Bout;
      struct help_struct help_data;
      char * text;
      int i = ToggleBox_check_toggles_no_sel_str ();
      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        Popup_Sel_flag = 0;
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        sprintf ( buf, "SRC/" );
        strcat ( buf, sel_str_arr [ i ] );
        if ( stat ( buf, &stat_buf ) != 0 ) {
          perror( buf );
          return;
        }

        Bout = fopen ( buf, "r" );
        if ( Bout == NULL ) {
          perror( buf );
          return;
        }

        if ( ! ( text = XtMalloc ( ( unsigned ) stat_buf.st_size + 1 ) ) ) {
          fprintf ( stderr, "\n Can't allocate enough space for %s\n", buf );
          return;
        }
        if ( ! fread ( text, sizeof ( char ), stat_buf.st_size + 1, Bout ) ) {
          fprintf ( stderr, "\n May not have read the entire file!\n" );
        }
        text [ stat_buf.st_size ] = 0;
        fclose ( Bout );

        /***
        set help data and call Popup_Help_CB 
        ***/
        help_data.type = PALETTE_HELP;
        help_data.text = ( char * ) text;
        help_data.width  = 455 /* 310 */ ;
        help_data.height = 503;

        Popup_Help_CB ( top_level, ( XtPointer ) & help_data );
        DisplayCurrentEnv ();

        /***
        free allocated memory
        ***/
        XtFree ( text );

      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;

  case edit_anm_thy_sel:     /*** edit_anm_thy_sel ***/

    if ( ! ok_pressed ) {           /*** CANCEL_BUTTON ***/     
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      Popup_Sel_flag = 0;
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
      InvokeB ( without_XTerm, 1 );
    }
    else  {                         /*** OK_BUTTON ***/     
      FILE * Bed;
      int j;
      int i = ToggleBox_check_toggles_no_sel_str ();
      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        Retrieve_String ( editor_str_num, str_buf );
	
	/* - use more intelligent command line caller for editors: */
	/*
        sprintf ( fifo_write_buf, "%s SRC/%s & \n echo $! > TMP/.Bed",
                                                    str_buf, sel_str_arr [ i ] );
	*/
	strcpy(fifo_write_buf,"SRC/");
	strcat(fifo_write_buf,sel_str_arr [ i ]);
	editorCommand=getEditorCommandLine(str_buf,fifo_write_buf);
	sprintf ( fifo_write_buf, "%s & \n echo $! > TMP/.Bed",
                                                    editorCommand );
        free(editorCommand);
	
	
        /***
        remove .thy fom sel_str_arr [ i ]
        ***/
        sel_str_arr [ i ] [ strlen ( sel_str_arr [ i ] ) - 4 ] = '\0';
/***
printf ( "edit_anm_thy_sel: %s\n", sel_str_arr [ i ] );
***/
        GetObjFromFullName ( & anm_thy_obj, sel_str_arr [ i ] );
/***
printf ( "edit_anm_thy_sel: %d %s\n", anm_thy_obj, GetName ( anm_thy_obj ) );
***/
        execute ( fifo_write_buf );
        Bed = fopen ( "TMP/.Bed", "r" );
        if ( Bed == NULL ) {
          AbortedMsgFile ( "\"TMP/.Bed\" for reading" );
          BT_err_exit ( 0 );
          return;
        }
        anm_thy_ps = 0;
        c = getc ( Bed );
        while ( ( c != '\n' ) && ( c != EOF ) ) {
          anm_thy_ps = ( ( anm_thy_ps * 10 ) + c - '0' );
          c = getc ( Bed );
        }
        fclose ( Bed );
        unlink ( "TMP/.Bed" );
        strcpy ( primary_string, GetName ( curr_obj ) );
        Popup_CloseAnimThyFile ( top_level, 0 );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;

  case creSLIB_selection:   /*** creSLIB_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      char str [ 100 ];
      int i = ToggleBox_check_toggles_no_sel_str ();
      int prog_lang;

      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        Popup_Sel_flag = 0;
        strcpy ( fifo_write_buf, sel_str_arr [ i ] );
        valIth_flags ( &prog_lang, Prog_Language_Option_num );
        if ( ( prog_lang == Prog_Language_Option_ANSI_C ) ||
             ( prog_lang == Prog_Language_Option_C )         ) {
          strcat ( fifo_write_buf, ":" );
          CreNumInBuf ( fifo_write_buf, BT_CRE_SLIB );
          Cre_tcp_env ();
          strcpy ( xterm_title, "B-CreSLIB" );
          InvokeB ( with_XTerm, 1 );
	}
        else {
          Popup_Info ( "Bad Programming Language Setting!" );
          DisplayCurrWinText ( "\n  Programming Language should be C or ANSI C\n" );          
	}
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;

  case remSLIB_selection:   /*** remSLIB_selection ***/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /*** OK_BUTTON ***/
      char str [ 100 ];
      int i = ToggleBox_check_toggles_no_sel_str ();
      int prog_lang;

      if ( i ) {
        int j;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        sprintf ( primary_string, "Proceed with removal of SLIB %s?", sel_str_arr [ i ] );
        strcpy ( secondary_string,
                    "The SLIB construct (and code) will be lost!" );
        strcpy ( fifo_write_buf, sel_str_arr [ i ] );
        radiobox_flag = rem_SLIB_radiobox;
        confirm_flag = radiobox_flag;
        Popup_ConfirmDialog ( top_level );
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;




/*
  case creTLIB_selection:   /??? creTLIB_selection ???/

    if ( ! ok_pressed ) {
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else  { /??? OK_BUTTON ???/
      char str [ 100 ];
      int i = ToggleBox_check_toggles_no_sel_str ();
      int prog_lang;

      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! sel_arr_tog [ i ] ) {
          i++;
        }
        Popup_Sel_flag = 0;
        curr_Mch_arr = 1;
        while ( Mch_arr [ curr_Mch_arr ] . obj != sel_Mch_arr [ i ] ) {
          curr_Mch_arr++;
         Load_SRC_CFG_Names ( curr_Mch_arr );
	}
        Pre_ExportTLIB ();
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    break;
*/


  case btool_pmd_rule_selection:   /*** btool_pmd_rule_selection ***/

    if ( ! ok_pressed ) {
      void PrintBToolProofMethod_Contd ();
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      PrintBToolProofMethod_Contd ();
    }
    else  { /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles_no_sel_str ();

      if ( i ) {
        void PrintBToolProofMethod_Contd ();
        int j;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        for ( i = 0 ; i < sel_arr_tot ; i++ ) {
          if ( ! ( sel_arr_tog [ i ] ) ) 
            psh_from_btoolkit ( unwanted_seq, sel_obj_arr [ i ] );
	}
        PrintBToolProofMethod_Contd ();
      }
      else {
        void PrintBToolProofMethod_Contd ();
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        for ( i = 0 ; i < sel_arr_tot ; i++ ) {
          psh_from_btoolkit ( unwanted_seq, sel_obj_arr [ i ] );
	}
        PrintBToolProofMethod_Contd ();
      }
    }
    break;

  case update_from_SRC_sel:   /*** update_from_SRC_sel ***/

    if ( ! ok_pressed ) {
      void ProcessUpdateFromSRC_Next ();
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      clear_gseq ();
      ProcessUpdateFromSRC_Next ();
    }
    else  { /*** OK_BUTTON ***/
      int i, rr;
      i = ToggleBox_check_toggles_no_sel_str ();
      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        Popup_Sel_flag = 0;
        /***
        load selected constructs into gset1
        ***/
        clear_gseq ();
        for ( i = 0 ; i < sel_arr_tot ; i++ ) {
          if ( sel_arr_tog [ i ] ) {
/***
printf ( "--%s--\n", GetName ( sel_arr_tog [ i ] ) );
***/
            push_gseq ( &rr, sel_obj_arr [ i ] );
            chk_rep ( rr, 197 );
	  }
	}
        ProcessUpdateFromSRC_Next ();
      }
      else {
        Popup_Info ( "Nothing selected!  " );
      }
    }
    break;


  case animator_utilities_sel:  /*** animator_utilities_sel ***/

    if ( ! ok_pressed ) {    /*** CANCEL_BUTTON ***/
      Position xx, yy;
      Dimension hh, ww;
      Popup_Sel_flag = 0;
      XtVaGetValues ( dialog,
          XmNx,         & xx,
          XmNy,         & yy,
          XmNwidth,     & ww,
          XmNheight,    & hh,
          NULL );
     if ( xx - wm_width  > anm_ops_x + allowable_dim_x ||
          xx - wm_width  < anm_ops_x - allowable_dim_x    )
       anm_ops_x = xx - wm_width;
     if ( yy - wm_height > anm_ops_y + allowable_dim_y ||
          yy - wm_height < anm_ops_y - allowable_dim_y    )
       anm_ops_y = yy - wm_height;
     if ( ww > anm_ops_w + allowable_dim_x ||
          ww < anm_ops_w - allowable_dim_x    ) anm_ops_w = ww;
     if ( hh > anm_ops_h + allowable_dim_y ||
          hh < anm_ops_h - allowable_dim_y    ) anm_ops_h = hh;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      XtDestroyWidget ( dialog );
      Animate_Ops ( top_level );
    }
    else { /*** OK_BUTTON ***/
      Position xx, yy;
      Dimension hh, ww;
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        i = 0;
        while ( ! ( sel_arr_tog [ i ] ) ) { i++; }
        Popup_Sel_flag = 0;
        XtVaGetValues ( dialog,
            XmNx,         & xx,
            XmNy,         & yy,
            XmNwidth,     & ww,
            XmNheight,    & hh,
            NULL );
       if ( xx - wm_width  > anm_ops_x + allowable_dim_x ||
            xx - wm_width  < anm_ops_x - allowable_dim_x    )
         anm_ops_x = xx - wm_width;
       if ( yy - wm_height > anm_ops_y + allowable_dim_y ||
            yy - wm_height < anm_ops_y - allowable_dim_y    )
         anm_ops_y = yy - wm_height;
       if ( ww > anm_ops_w + allowable_dim_x ||
            ww < anm_ops_w - allowable_dim_x    ) anm_ops_w = ww;
       if ( hh > anm_ops_h + allowable_dim_y ||
            hh < anm_ops_h - allowable_dim_y    ) anm_ops_h = hh;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        XtDestroyWidget ( dialog );

        if ( ( strcmp ( sel_str_arr [ i ], "Restore initial state" ) == 0 )       ||
             ( strcmp ( sel_str_arr [ i ], "Restart animation" ) == 0 )           ||
             ( strcmp ( sel_str_arr [ i ], "Set state variables" ) == 0 )         ||
             ( strcmp ( sel_str_arr [ i ], "Edit theory file" ) == 0 )            ||
             ( strcmp ( sel_str_arr [ i ], "Save as ANIMATE Script Initialisation" ) == 0 )   ) {
          XtUnmanageChild ( constructs_rc );
          XmUpdateDisplay ( constructs_scroll );
          XtDestroyWidget ( constructs_rc );
          constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
              xmRowColumnWidgetClass,         constructs_scroll,
              XmNorientation,                 XmVERTICAL,
              XmNmarginWidth,                 18,
              XmNmarginHeight,                10,
              XmNspacing,                     0,
              XmNresizable,                   True,
              NULL );
          Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
          InvokeB ( without_XTerm, 1 );
	}

        else {
          if ( strcmp ( sel_str_arr [ i ], "Save output" ) == 0 ) {
            Popup_SaveAnimOutput ();
	  }
          else if ( strcmp ( sel_str_arr [ i ], "Save as ANIMATE Script Executable" ) == 0 ) {
            Popup_SaveAnimateFile ();
	  }
          else if ( strcmp ( sel_str_arr [ i ], "Clean animator files" ) == 0 ) {
            void Popup_CleanAnimFiles ();
            Popup_CleanAnimFiles ();
	  }
          else {
            void Animate_Utilities ();
            Animate_Utilities ( top_level );
            Popup_Info ( "Selection not recognized" );
          }
	}

      }
      else {
        Popup_Info ( "Nothing selected!" );
      }
    }
    
    break;


  case save_anm_output_sel:  /*** save_anm_output_sel ***/

    if ( ! ok_pressed ) {    /*** CANCEL_BUTTON ***/
      void Animate_Utilities ();
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      Animate_Utilities ( top_level );
    }

    else {                   /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! ( sel_arr_tog [ i ] ) ) { i++; }
        Popup_Sel_flag = 0;
        if ( i == 0 ) {
          void Popup_SaveAnimOutput_NewFile ();
          Popup_SaveAnimOutput_NewFile ();
	}
	else {
          sprintf ( str_buf, "SRC/%s", sel_str_arr [ i ] );
          SaveAnimOutput ( str_buf, 0 ); /* 0 => allow overwrite */
	}
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }

    }

    break;


  case edit_anm_exe_sel:  /*** edit_anm_exe_sel ***/

    if ( ! ok_pressed ) {    /*** CANCEL_BUTTON ***/
      void Popup_MainAnimatorMenu ();
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      Popup_MainAnimatorMenu ( curr_obj );
    }

    else {                   /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! ( sel_arr_tog [ i ] ) ) { i++; }
        Popup_Sel_flag = 0;
        if ( i == 0 ) {
          void Popup_EditAnimateFile_NewFile ();
          Popup_EditAnimateFile_NewFile ();
	}
	else {
          sprintf ( str_buf, "SRC/%s", sel_str_arr [ i ] );
          EditAnimateFile ( str_buf, 0 ); /* 0 => allow overwrite */
	}
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }

    }

    break;


  case edit_anm_exe_new_from_old_sel:  /*** edit_anm_exe_new_from_old_sel ***/

    if ( ! ok_pressed ) {    /*** CANCEL_BUTTON ***/
      void Popup_MainAnimatorMenu ();
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      Popup_MainAnimatorMenu ( curr_obj );
    }

    else {                   /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        void Popup_EditAnimateFile_NewFile ();
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! ( sel_arr_tog [ i ] ) ) { i++; }
        Popup_Sel_flag = 0;
        if ( i == 0 ) {
          additional_string [ 0 ] = '\0';
	}
	else {
          sprintf ( additional_string, "SRC/%s", sel_str_arr [ i ] );
	}
        Popup_EditAnimateFile_NewFile_Contd ();
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }

    }

    break;


  case save_anm_animate_sel :  /*** save_anm_animate_sel ***/

    if ( ! ok_pressed ) {    /*** CANCEL_BUTTON ***/
      void Animate_Utilities ();
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      Animate_Utilities ( top_level );
    }

    else {                   /*** OK_BUTTON ***/
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        i = 0;
        while ( ! ( sel_arr_tog [ i ] ) ) { i++; }
        Popup_Sel_flag = 0;
        if ( i == 0 ) {
          void Popup_SaveAnimateFile_NewFile ();
          Popup_SaveAnimateFile_NewFile ();
	}
	else {
          sprintf ( str_buf, "SRC/%s", sel_str_arr [ i ] );
          SaveAnimateFile ( str_buf, 0 ); /* 0 => allow overwrite */
	}
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }

    }
    break;


  case anm_clean_files_sel:  /*** anm_clean_files_sel ***/

    if ( ! ok_pressed ) {    /*** CANCEL_BUTTON ***/
      void Animate_Utilities ();
      void Popup_MainAnimatorMenu ();
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      if   ( curr_env == anm_env ) Animate_Utilities ( top_level );
      else                         Popup_MainAnimatorMenu ( curr_obj );
    }

    else {                   /*** OK_BUTTON ***/
      void Animate_Utilities ();
      void Popup_MainAnimatorMenu ();
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        Popup_Sel_flag = 0;
        strcpy ( str_buf, "Removed:" );
        for ( i = 0 ; i < sel_arr_tot ; i++ ) {
          if ( sel_arr_tog [ i ] ) {
            sprintf ( buf, "SRC/%s",  sel_str_arr [ i ] );
            unlink ( buf );
            strcat ( str_buf, " " );
            strcat ( str_buf, buf );
	  }
	}
        if   ( curr_env == anm_env ) Animate_Utilities ( top_level );
        else                         Popup_MainAnimatorMenu ( curr_obj );
        Popup_Info ( str_buf );
      }
     else {
        Popup_Info ( "Nothing selected!" );
      }

    }
    break;


  case anm_exe_step:                           /*** anm_exe_step ***/

    if ( ! ok_pressed ) {    /*** CANCEL_BUTTON ***/
      void Popup_MainAnimatorMenu ();
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      Popup_MainAnimatorMenu ( curr_obj );
    }

    else {                   /*** OK_BUTTON ***/
      void Pre_Animate ();
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        Popup_Sel_flag = 0;
        i = 0;
        while ( ! ( sel_arr_tog [ i ] ) ) { i++; }
        sprintf ( additional_string, "SRC/%s",  sel_str_arr [ i ] );
        Pre_Animate ( 2 );  /* flag = 2 => Replay - step */
      }
     else {
        Popup_Info ( "Nothing selected!" );
      }

    }
    break;


  case anm_exe_auto:                           /*** anm_exe_auto ***/

    if ( ! ok_pressed ) {    /*** CANCEL_BUTTON ***/
      void Popup_MainAnimatorMenu ();
      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      Popup_MainAnimatorMenu ( curr_obj );
    }

    else {                   /*** OK_BUTTON ***/
      void Pre_Animate ();
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        Popup_Sel_flag = 0;
        i = 0;
        while ( ! ( sel_arr_tog [ i ] ) ) { i++; }
        sprintf ( additional_string, "SRC/%s",  sel_str_arr [ i ] );
        Pre_Animate ( 3 );  /* flag = 3 => Replay - auto */
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }

    }
    break;

  case source_control_sel:                           /*** source_control_sel ***/

    if ( ! ok_pressed ) {    /*** CANCEL_BUTTON ***/
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      Popup_Sel_flag = 0;
    }
    else {
      int n;
      int i = ToggleBox_check_toggles ();
      if ( i ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        Popup_Sel_flag = 0;
        i = 0;
        strcpy ( str_buf, "xterm -sb -geometry 65x30+1+1 -e .Bexe" ); 
        while ( i < sel_arr_tot ) {
          if ( sel_arr_tog [ i ] ) {
            strcat ( str_buf, " " );
            strcat ( str_buf, sel_str_arr [ i ] );
	  }
          i++;
	}
/***
system ( "cat .Bexe" );
printf ( "`%s'\n", str_buf );
***/
        system ( str_buf );
        LoadFileIntoBuf ( "TMP/.Bsta", buf, MAX_buf );
        n = 0;
        i = 0;
        while ( ( buf [ i ] >= '0' ) && ( buf [ i ] <= '9' )  ) {
          n = ( ( n * 10 ) + buf [ i ] - '0' );
          i++;
	}
        if ( n == 0 ) {
          Popup_Info ( "Source Control Command successful" );
	}
        else {
          Popup_Info ( "Bad return call" );
          sprintf ( buf, "\n  Bad return (%d) call from Source Control Command:\n", n );
          DisplayCurrWinText ( buf );
          LoadFileIntoBuf ( ".Bexe", buf, MAX_buf );
          DisplayCurrWinText ( "\n------------------------------------------------------\n" );
          DisplayCurrWinText ( buf );
          DisplayCurrWinText ( "------------------------------------------------------\n" );
	}
      }
      else {
        Popup_Info ( "Nothing selected!" );
      }

    }
    break;

  default:

/***
printf("\n    default\n" );
printf("curr_env: %d (anm_env %d)\n",curr_env,anm_env);
printf("anm_ops_dialog: %d\n",anm_ops_dialog);
printf("anm_ops_option: %d\n",anm_ops_option);
printf("sub_frame1: %d\n",sub_frame1);
printf("sub_frame2: %d\n",sub_frame2);
printf("sub_frame3: %d\n",sub_frame3);
printf("sub_dummy: %d\n",sub_dummy);
***/
    /***
    not commit edits/status/interprover ops
    ***/
    Popup_Sel_flag = 0;
    if ( ! ok_pressed ) {    /*** CANCEL_BUTTON ***/

/***
printf("default CANCEL_BUTTON\n");
***/

      /***
      popdown dialog
      ***/
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );

      /***
      check animator
      ***/
      if ( curr_env == anm_env ) {

          if ( anm_ops_dialog ) {
/***
printf ( " about to XtDestroyWidget ( anm_ops_dialog )\n" );
***/
            XtDestroyWidget ( anm_ops_dialog );
            anm_ops_dialog = ( Widget ) 0;
            anm_ops_x = -999;
            anm_ops_h = 1;
	  }

        /***
        destroy constructs_rc & reset anm_ops_dialog
        ***/
        if ( anm_ops_option ) {

/***
printf ( " anm_ops_option is set\n " );
***/

          XtUnmanageChild ( constructs_rc );
          XmUpdateDisplay ( constructs_scroll );
          XtDestroyWidget ( constructs_rc );
          constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
              xmRowColumnWidgetClass,         constructs_scroll,
              XmNorientation,                 XmVERTICAL,
              XmNmarginWidth,                 18,
              XmNmarginHeight,                10,
              XmNspacing,                     0,
              XmNresizable,                   True,
              NULL );
	}

        anm_ops_option = 0;

      }

      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
      InvokeB ( without_XTerm, 1 );

    }

    else  { /*** OK_BUTTON ***/

      int i = ToggleBox_check_toggles ();

/***
printf("default OK_BUTTON\n" );
***/

      if ( i ) {

        i = 0;
        while ( ! ( sel_arr_tog [ i ] ) ) { i++; }

/***
printf("                    |%s|\n", sel_str_arr [ i ] );
***/
/***
printf("                    |%s|\n", fifo_write_buf );
***/
        /***
        popdown dialog
        ***/
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );

       /***
        check animator (for ops - not choice)
        ***/
        if ( curr_env == anm_env ) {

          if ( anm_ops_option ) {

            if ( anm_ops_dialog ) { /* ops - not choice */
              Position xx, yy;
              Dimension hh, ww;
              XtVaGetValues ( anm_ops_dialog,
                  XmNx,         & xx,
                  XmNy,         & yy,
                  XmNwidth,     & ww,
                  XmNheight,    & hh,
                  NULL );
/***
printf ( "\n---------------------------------------\n" );
printf ( "xx=%d yy=%d ww=%d hh=%d\n", xx, yy, ww, hh );
printf ( "wm_width=%d wm_height=%d allowable_dim=%d\n", wm_width, wm_height, allowable_dim );
printf ( "0: anm_ops_x=%d anm_ops_y=%d anm_ops_w=%d anm_ops_h=%d\n", anm_ops_x, anm_ops_y, anm_ops_w, anm_ops_h );
***/
              if ( xx - wm_width  > anm_ops_x + allowable_dim_x ||
                   xx  - wm_width < anm_ops_x - allowable_dim_x    )
                anm_ops_x = xx - wm_width;
              if ( yy - wm_height > anm_ops_y + allowable_dim_y ||
                   yy - wm_height < anm_ops_y - allowable_dim_y    )
                anm_ops_y = yy - wm_height;
              if ( ww > anm_ops_w + allowable_dim_x ||
                   ww < anm_ops_w - allowable_dim_x    )
                 anm_ops_w = ww;
              if ( hh > anm_ops_h + allowable_dim_y ||
                   hh < anm_ops_h - allowable_dim_y    )
                 anm_ops_h = hh;
	    }
            anm_ops_option = 0;
/***
printf ( "1: anm_ops_x=%d anm_ops_y=%d anm_ops_w=%d anm_ops_h=%d\n", anm_ops_x, anm_ops_y, anm_ops_w, anm_ops_h );
***/

            if ( strcmp ( sel_str_arr [ i ], "Animator Utilities" ) == 0 ) {
              void Animate_Utilities ();
              Animate_Utilities ();
              return;
	    }
 /* not sure what this is? */
            if ( strcmp ( sel_str_arr [ i ], "Restart animation" ) != 0 ) {
              XtUnmanageChild ( constructs_rc );
              XmUpdateDisplay ( constructs_scroll );
              XtDestroyWidget ( constructs_rc );
              constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
                  xmRowColumnWidgetClass,         constructs_scroll,
                  XmNorientation,                 XmVERTICAL,
                  XmNmarginWidth,                 18,
                  XmNmarginHeight,                10,
                  XmNspacing,                     0,
                  XmNresizable,                   True,
                  NULL );
	    }

	  }

          else {                  /* choice not ops */

            if ( anm_ops_dialog ) {
/***
printf ( " about to XtDestroyWidget ( anm_ops_dialog )\n" );
***/
              XtDestroyWidget ( anm_ops_dialog );
              anm_ops_dialog = ( Widget ) 0;

	    }

	  }

        }  /* if ( curr_env == anm_env ) */

        else {
          if ( ( curr_env == ipr_pob_env ) ||
               ( curr_env == ipr_lem_env )    ) {
            int ll = strlen ( fifo_write_buf );
            if ( ll > 27 ) {
              if ( ( fifo_write_buf [ ll - 11 ] == 'u' ) &&
                   ( fifo_write_buf [ ll - 10 ] == 'n' ) &&
                   ( fifo_write_buf [ ll -  9 ] == 'p' ) &&
                   ( fifo_write_buf [ ll -  8 ] == 'r' ) &&
                   ( fifo_write_buf [ ll -  7 ] == 'o' ) &&
                   ( fifo_write_buf [ ll -  6 ] == 'v' ) &&
                   ( fifo_write_buf [ ll -  5 ] == 'e' ) &&
                   ( fifo_write_buf [ ll -  4 ] == 'd' ) &&
                   ( fifo_write_buf [ ll -  3 ] == ')' ) &&
                   ( fifo_write_buf [ ll -  2 ] == ')' ) &&
                   ( fifo_write_buf [ ll -  1 ] == ':' )    ) {
                ll = 2;
                while ( fifo_write_buf [ ll ] != '(' ) { ll++; }
                fifo_write_buf [ ll ] = ')';
                fifo_write_buf [ ll + 1 ] = ':';
                fifo_write_buf [ ll + 2 ] = '\0';
	      }
	    }
	  }
	}

        Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
        InvokeB ( without_XTerm, 1 );
      }
      else {

        /***
        complain
        ***/
        Popup_Info ( "Nothing selected!" );
      }
    }
  }
}

void
CreateDirAndNewDevelopment ()
{
  sprintf ( primary_string, "Create directory %s", additional_string );
  strcpy ( secondary_string, "The directory will be created with permission 755,\nmodified by the file mode creation mask" );
  radiobox_flag = cre_new_dir_dev_radiobox;
  confirm_flag = radiobox_flag;
  Popup_ConfirmDialog ( top_level );
}


void
Popup_Selection_Sel_Text_Dialog_CB ( text_widget, client_data )
XtPointer client_data;
Widget text_widget;
{
/***
  printf ( "%d %d %d\n", text_widget, XtParent ( text_widget ), XtParent ( XtParent ( text_widget ) ) );
***/

  switch ( Popup_Selection_Sel_flag ) {

  case cd_Selection_sel:   /*** cd_Selection_sel ***/
    {
      struct stat stat_buf;
      char * filename;
      FILE * Bcom;
      char * string_ptr;

      XtPopdown ( XtParent ( XtParent ( text_widget ) ) );
      XmUpdateDisplay ( XtParent ( XtParent ( text_widget ) ) );

      string_ptr = XmTextGetString ( text_widget );
      strcpy ( additional_string, string_ptr );
      XtFree ( string_ptr );

      if ( additional_string [ strlen ( additional_string ) - 1 ] == '/' )
        additional_string [ strlen ( additional_string ) - 1 ] = '\0';

      if ( strcmp ( additional_string, "" ) == 0 ) {
        Popup_Info ( "  Text sting empty! " );
        check_started_from_cd ( "  Text sting empty! ");
        return;
      }

      if ( ( strlen ( additional_string ) != 1 )                             &&
           ( additional_string [ strlen ( additional_string ) - 1 ] == '/' )    )
        additional_string [ strlen ( additional_string ) - 1 ] = '\0';

      if ( strcmp ( cur_dir, additional_string ) == 0 ) {
        if ( ! started_from_cd  ) {
          sprintf ( fifo_write_buf, " %s is the current directory! ", additional_string );
          XtPopup ( XtParent ( XtParent ( text_widget ) ), XtGrabNone );
          XmUpdateDisplay ( XtParent ( XtParent ( text_widget ) ) );
          Popup_Info ( fifo_write_buf );
          check_started_from_cd ( fifo_write_buf );
          return;
	}
      }
    
      if ( stat ( additional_string, &stat_buf ) == -1 ) {
        global_widget1 = XtParent ( XtParent ( text_widget ) );
        CreateDirAndNewDevelopment ();
        return;
      }
    
      else if ( ( stat_buf.st_mode & S_IFMT ) != S_IFDIR ) {
        sprintf ( fifo_write_buf, " %s is not a directory ", additional_string );
        XtPopup ( XtParent ( XtParent ( text_widget ) ), XtGrabNone );
        XmUpdateDisplay ( XtParent ( XtParent ( text_widget ) ) );
        Popup_Info ( fifo_write_buf );
        check_started_from_cd ( fifo_write_buf );
        return;
      }

      else if ( access ( additional_string, W_OK ) == -1 ) {
        sprintf ( fifo_write_buf, " You don't have write permission in %s ", additional_string );
        XtPopup ( XtParent ( XtParent ( text_widget ) ), XtGrabNone );
        XmUpdateDisplay ( XtParent ( XtParent ( text_widget ) ) );
        Popup_Info ( fifo_write_buf );
        check_started_from_cd ( fifo_write_buf );
        return;
      }

      else {
        sprintf ( fifo_write_buf, "%s/.BToolkitLock", additional_string );
        if ( stat ( fifo_write_buf, &stat_buf ) == 0 ) {
          if ( ! started_from_cd  ) {
            sprintf ( fifo_write_buf, " Directory %s is currently locked", additional_string );
            XtPopup ( XtParent ( XtParent ( text_widget ) ), XtGrabNone );
            XmUpdateDisplay ( XtParent ( XtParent ( text_widget ) ) );
            Popup_Info ( fifo_write_buf );
            check_started_from_cd ( fifo_write_buf );
            return;
	  }
        }
      }

      XtPopdown ( XtParent ( XtParent ( text_widget ) ) );
      XmUpdateDisplay ( XtParent ( XtParent ( text_widget ) ) );

      /***
      write new dir in .Bcom for BSession - prefix with aaa!
      ***/
      Bcom = fopen ( ".Bcom", "w" );
      if ( Bcom == NULL ) {
        AbortedMsgFile ( "\"%s\" for writing", ".Bcom" );
        BT_err_exit ( 0 );
        return;
      }
      fprintf ( Bcom, "aaa%s", additional_string );
      fclose ( Bcom );

      /***
      write new dir in .Bcom for BSession - no prefix!
      ***/
      Bcom = fopen ( ".BBBcom", "w" );
      if ( Bcom == NULL ) {
        AbortedMsgFile ( "\"%s\" for writing", ".BBBcom" );
        BT_err_exit ( 0 );
        return;
      }
      fprintf ( Bcom, "%s", additional_string );
      fclose ( Bcom );

      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_num ( BT_CK_PARSE_BCOM, 0 );
      InvokeB( without_XTerm, 1 );
      break;
    }
  }  /* switch ... */

}

void
Popup_Selection_Sel_Dialog_CB ( button, client_data, call_data )
Widget button;
XtPointer client_data;
XtPointer call_data;
{
  int rad_but;
  Widget dialog;
  int selection_option;
  int ok_pressed = 0;
  int filter_pressed = 0;
  char * string_ptr;
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;

/***
printf ( "Popup_Sel_Dialog_CB - Popup_Sel_flag %d\n", Popup_Sel_flag );
printf ( "curr_env %d\n", curr_env );
***/

  /***
  get parent dialog/OK or CANCEL
  ***/
  if ( cbs->reason == XmCR_PROTOCOLS ) {    /*** WM Close ***/
    dialog =  button;
    ok_pressed = 0;
    filter_pressed = 0;
  }
  else {
    dialog = XtParent ( XtParent ( XtParent ( button ) ) );
    if ( ( * ( int * ) client_data ) == OK_BUTTON ) {
      ok_pressed = 1;
      filter_pressed = 0;
    }
    else if ( ( * ( int * ) client_data ) == FILTER_BUTTON ) {
      ok_pressed = 0;
      filter_pressed = 1;
    }
    else {
      ok_pressed = 0;
      filter_pressed = 0;
    }
  }

/***
printf ( "cbs->reason   = %d\n", cbs->reason );
printf ( "dialog        = %d\n", dialog );
printf ( "ok_pressed    = %d\n", ok_pressed );
***/

  switch ( Popup_Selection_Sel_flag ) {

  case cd_Selection_sel:   /*** cd_Selection_sel ***/

    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );
 
    if ( ok_pressed ) { /*** OK_BUTTON ***/ 
      Popup_Selection_Sel_Text_Dialog_CB ( global_widget, client_data );
    }
    else if ( filter_pressed ) { /*** FILTER_BUTTON ***/
      string_ptr = XmTextGetString ( global_widget );
      strcpy ( sel_str_arr [ sel_arr_MAX ], string_ptr );
      XtFree ( string_ptr );
      if ( sel_str_arr [ sel_arr_MAX ] [ strlen ( sel_str_arr [ sel_arr_MAX ] ) - 1 ] == '/' )
        sel_str_arr [ sel_arr_MAX ] [ strlen ( sel_str_arr [ sel_arr_MAX ] ) - 1 ] = '\0';
      LoadWritableDirInto_sel_strs ( sel_str_arr [ sel_arr_MAX ] );
      Popup_Selection_Sel_Dialog ( top_level, sel_str_arr [ sel_arr_MAX ] );
    }
    else { /*** CANCEL_BUTTON ***/
      if ( started_from_cd ) {
         cd_dialog = ( Widget ) 0;
         check_started_from_cd ( "" );
      }
      else {
        DisplayCurrentEnv ();
      }
    }
    break;

  }  /* switch ... */

}

void
ToggleBox_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  static int double_click = 0;
  static XtIntervalId id = 0;
  int i = * ( int * ) client_data;

/***
if ( ! second_visit ) printf ( "\n" );
printf ( "ToggleBox_CB  i=%d client_data(i)=%d  second_visit=%d  waiting_option=%d\n", i, i, second_visit, waiting_option );
***/

  if   ( sel_arr_tog [ i ] ) sel_arr_tog [ i ] = 0;
  else                       sel_arr_tog [ i ] = 1;

/***
if ( sel_arr_tog [ i ] )
  printf ( "sel_arr_tog [ %d ]: 0 -> 1\n", i );
else 
  printf ( "sel_arr_tog [ %d ]: 1 -> 0\n", i );
***/

  if ( SelOne_flagged ) {  /* SelOne_flagged => two visits per button push! */

    if ( second_visit ) {
      if ( ! waiting_option )  {
        waiting_option = 1;
        id = XtAppAddTimeOut ( app, ( long unsigned ) mc_interval,
                     ( XtTimerCallbackProc ) ResetWaitingOption, NULL );
      }
      else {
        waiting_option = 0;
        double_click = 1;
      }
    }

    if ( double_click ) {
/*
      XmAnyCallbackStruct cbs1 = { XmCR_PROTOCOLS - 1, ( XtPointer ) NULL };
*/
      XmAnyCallbackStruct cbs1;
      cbs1.reason = XmCR_PROTOCOLS - 1;
      double_click = 0;
/***
DisplayCurrWinText ( "\n  DOUBLE CLICK\n" );
***/
      sel_arr_tog [ i ] = 1;
      Popup_Sel_Dialog_CB ( XtParent ( XtParent ( widget ) ),
              ( XtPointer )  & c_arr [ OK_BUTTON ],
              ( XtPointer ) & cbs1 );
    }

    if   ( second_visit ) second_visit = 0;
    else                  second_visit = 1;

  }

  else {                 /* not SelOne_flagged */

    if ( ! waiting_option )  {
      waiting_option = 1;
      id = XtAppAddTimeOut ( app, ( long unsigned ) mc_interval,
                   ( XtTimerCallbackProc ) ResetWaitingOption, NULL );
    }
    else {
      waiting_option = 0;
      double_click = 1;
    }

    if ( double_click ) {
/*
      XmAnyCallbackStruct cbs1 = { XmCR_PROTOCOLS - 1, ( XtPointer ) NULL };
*/
      XmAnyCallbackStruct cbs1;
      cbs1.reason = XmCR_PROTOCOLS - 1;
      double_click = 0;
/***
DisplayCurrWinText ( "\n  DOUBLE CLICK\n" );
***/
      sel_arr_tog [ i ] = 1;
      Popup_Sel_Dialog_CB ( XtParent ( XtParent ( widget ) ),
              ( XtPointer )  & c_arr [ OK_BUTTON ],
              ( XtPointer ) & cbs1 );
    }
  }
}

void
SelectionToggleBox_CB ( widget, client_data )
Widget widget;
XtPointer client_data;
{
  static int double_click = 0;

  static XtIntervalId id = 0;

  int i = * ( int * ) client_data;
  int j, k;

/***
printf ( "SelectionToggleBox_CB  client_data(i): %d  second_visit %d  waiting_option %d  double_click %d\n", i, second_visit, waiting_option, double_click );
***/

  if (  sel_arr_tog [ i ] ) {
    sel_arr_tog [ i ] = 0;
  }
  else {
    sel_arr_tog [ i ] = 1;
    if ( i == 0 ) {
      int j = 8;
      int k = 0;
      while ( sel_str_arr [ i ] [ j ] != '\0' ) {
        fifo_write_buf [ k ] = sel_str_arr [ i ] [ j ];
        j++;
        k++;
      }
      fifo_write_buf [ k ] = '\0';
    }
    else if ( i == 1 ) {
      int j = 6;
      int k = 0;
      while ( sel_str_arr [ i ] [ j ] != '\0' ) {
        fifo_write_buf [ k ] = sel_str_arr [ i ] [ j ];
        j++;
        k++;
      }
      fifo_write_buf [ k ] = '\0';
    }
    else {
      sprintf ( fifo_write_buf, "%s/%s", sel_str_arr [ sel_arr_MAX ], sel_str_arr [ i ] );
    }
    XmTextSetString ( global_widget, fifo_write_buf ) ;
  }

  /***
  two visits per button push!
  ***/
  if ( second_visit ) {
    if ( ! waiting_option )  {
      waiting_option = 1;
      id = XtAppAddTimeOut ( app, ( long unsigned ) mc_interval,
                   ( XtTimerCallbackProc ) ResetWaitingOption, NULL );
    }
    else {
      waiting_option = 0;
      double_click = 1;
    }
  }

  if   ( second_visit ) second_visit = 0;
  else                  second_visit = 1;

  if ( double_click ) {
/*
    XmAnyCallbackStruct cbs1 = { XmCR_PROTOCOLS - 1, ( XtPointer ) NULL };
*/
    XmAnyCallbackStruct cbs1;
    cbs1.reason = XmCR_PROTOCOLS - 1;
    double_click = 0;
/***
DisplayCurrWinText ( "\n  DOUBLE CLICK\n" );
***/
    sel_arr_tog [ i ] = 1;
    if ( i == 0 ) {
      int j = 8;
      int k = 0;
      while ( sel_str_arr [ i ] [ j ] != '\0' ) {
        fifo_write_buf [ k ] = sel_str_arr [ i ] [ j ];
        j++;
        k++;
      }
      fifo_write_buf [ k ] = '\0';
    }
    else if ( i == 1 ) {
      int j = 6;
      int k = 0;
      while ( sel_str_arr [ i ] [ j ] != '\0' ) {
        fifo_write_buf [ k ] = sel_str_arr [ i ] [ j ];
        j++;
        k++;
      }
      fifo_write_buf [ k ] = '\0';
    }
    else {
      sprintf ( fifo_write_buf, "%s/%s", sel_str_arr [ sel_arr_MAX ], sel_str_arr [ i ] );
    }
    XmTextSetString ( global_widget, fifo_write_buf ) ;
    Popup_Selection_Sel_Dialog_CB ( XtParent ( XtParent ( widget ) ),
            ( XtPointer )  & c_arr [ FILTER_BUTTON ],
            ( XtPointer ) & cbs1 );
  }
}

void
Popup_RadioBox_Dialog_CB ( button, client_data, call_data )
Widget button;
XtPointer client_data;
XtPointer call_data;
{
  /***
  curr_obj is set
  ***/

  int rad_but, * rad_but_address;
  int ok_pressed, file_diff_but;
  Widget dialog;
  int rad_option;
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;
  char* editorCommand;

/***
printf ( "\nPopup_RadioBox_Dialog_CB  radiobox_flag=%d ", radiobox_flag );
printf ( "curr_env %d\n", curr_env );
printf ( "  (Popup_Sel_flag %d)\n", Popup_Sel_flag );
fflush ( stdout );
***/

  /***
  get parent dialog/OK or CANCEL/file_diff_but/rad_but
  ***/
  if ( cbs->reason == XmCR_PROTOCOLS ) {    /*** WM Close ***/
    dialog =  button;
    ok_pressed = 0;
    file_diff_but = 999;
    XtVaGetValues (
        ( Widget ) ( ( ( struct ok_cancel_but_struct * ) client_data ) -> but ),
        XmNuserData,    & rad_but_address,
        NULL );
  }
  else {
    dialog = XtParent ( XtParent ( XtParent ( button ) ) );
    if ( ( ( ( struct ok_cancel_but_struct * ) client_data ) -> but ) == OK_BUTTON )
      ok_pressed = 1;
    else
      ok_pressed = 0;
    file_diff_but =
           ( ( struct ok_cancel_but_struct * ) client_data ) -> file_diff_but;
/***
printf ( "button                          =%d\n", button );
printf ( "XtParent ( XtParent ( button ) )=%d\n", XtParent ( XtParent ( button ) ) );
***/

/***
printf ( getting "XmNuserData of %d\n", XtParent ( XtParent ( button ) ) );
***/

    XtVaGetValues ( XtParent ( XtParent ( button ) ),
        XmNuserData,    & rad_but_address,
        NULL );
  }
  rad_but = * rad_but_address;

/***
printf ( "cbs->reason   = %d\n", cbs->reason );
printf ( "dialog        = %d\n", dialog );
printf ( "ok_pressed    = %d\n", ok_pressed );
printf ( "file_diff_but = %d\n", file_diff_but );
printf ( "rad_but addr  = %d\n\n", & rad_but_address );
printf ( "rad_but       = %d\n\n", rad_but );
***/

  rad_option = radiobox_flag;
  radiobox_flag = 0;

  switch ( rad_option ) {

  case open_radiobox:       /*** open_radiobox ***/

    if ( ! ok_pressed ) {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }

    else {
      if ( rad_but == file_diff_but ) {
        radiobox_flag = rad_option;
        ShowFileDiff ( curr_obj );
      }
      else  {
        char buf [ MAX_SRCName + MAX_CFGName + 10 ];  

        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        if ( rad_but == 1 ) {
          Load_SRC_CFG_Names ( curr_obj );
          CopyCFGSRC ();
	}
        else {
          sprintf ( buf, "\n  %s SRC file opened\n", GetName ( curr_obj ) );
          DisplayCurrWinText ( buf );
	}
        OpenConstruct ( curr_obj );
      }
    }
    break;

  case close_radiobox:   /*** close_radiobox ***/

    if ( ! ok_pressed ) {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
    }
    else {
      if ( rad_but == file_diff_but ) {
        radiobox_flag = close_radiobox;
        ShowFileDiff ( curr_obj );
      }
      else  {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        switch ( rad_but ) {
        case 0:                                       /*** Commit edits ***/
#ifdef WWW_VERSION
          WWW_Err;
#else /* ! WWW_VERSION */
          radiobox_flag = close_radiobox;
          CheckFileParses ( curr_obj );
#endif /* WWW_VERSION */
          break;
        case 1:                                       /*** Discard edits ***/
	  printf("Discard edits 1. curr_obj = %d \n",curr_obj);
          Load_SRC_CFG_Names ( curr_obj );
	  printf("Discard edits 2, SRCName = %s\n",SRCName);
          unlink( SRCName );
	  printf("Discard edits 3\n");
          /* MUST do this *after* the unlinking */
          KillProcess_Modify_ps ( curr_obj );
	  printf("Discard edits 4\n");
          sprintf ( buf, "\n  %s edits discarded\n", GetName ( curr_obj ) );
	  printf("Discard edits 5\n");
          DisplayCurrWinText ( buf );
	  printf("Discard edits 6\n");
          UnDecorate_SRC_file_newer ( curr_obj );
	  printf("Discard edits 7\n");
          DisplayCurrentEnv ();
	  printf("Discard edits 8\n");
          break;
        case 2:                                       /*** Save in SRC ***/
          KillProcess_Modify_ps ( curr_obj );
          sprintf ( buf, "\n  Saved %s in SRC\n", GetName ( curr_obj ) );
          DisplayCurrWinText ( buf );
          DisplayCurrentEnv ();
          break;
	}
      }
    }
    break;

  case update_from_src_radiobox:   /*** update_from_src_radiobox ***/

    if ( ! ok_pressed ) {
      int rr;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      sprintf ( buf, "Update of %s aborted\n", primary_string );
      Popup_Info ( buf );
      delIth_gseq ( &rr, 1 );
      chk_rep ( rr, 197 );
      ProcessUpdateFromSRC_Next ();
    }
    else {
      if ( rad_but == file_diff_but ) {
        radiobox_flag = update_from_src_radiobox;
        ShowFileDiff ( curr_obj );
      }
      else  { /*** Commit Edits ***/
        int rr;
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        delIth_gseq ( &rr, 1 );
        chk_rep ( rr, 198 );
        Load_SRC_CFG_Names ( curr_obj );
        radiobox_flag = update_from_src_radiobox;
        CheckFileParses ( curr_obj );
      }
    }
    break;

  case close_all_radiobox:   /*** close_all_radiobox ***/

    radiobox_flag = close_all_radiobox;

    if ( ! ok_pressed ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        CloseAllOpenFilesNext ();
      }
    else {
      if ( rad_but == file_diff_but ) {
        ShowFileDiff ( curr_obj );
      }
      else  {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        switch ( rad_but ) {
        case 0:     /*** Commit edits ***/
#ifdef WWW_VERSION
          WWW_Err;
          CloseAllOpenFilesNext ();
#else /* ! WWW_VERSION */
          CheckFileParses ( curr_obj );
#endif /* WWW_VERSION */
          break;
        case 1:     /*** Discard edits ***/
          {
            Load_SRC_CFG_Names ( curr_obj );
            unlink( SRCName );
            /* MUST do this *after* the unlinking */
            KillProcess_Modify_ps ( curr_obj );
            sprintf ( buf, "\n  %s edits discarded\n", GetName ( curr_obj ) );
            DisplayCurrWinText ( buf );
            UnDecorate_SRC_file_newer ( curr_obj );
            CloseAllOpenFilesNext ();
	  }
          break;
        case 2:     /*** Save in SRC ***/
          KillProcess_Modify_ps ( curr_obj );
          sprintf ( buf, "\n  Saved %s in SRC\n", GetName ( curr_obj ) );
          DisplayCurrWinText ( buf );
          CloseAllOpenFilesNext ();
          break;
        }
      }
    }
    break;

  case mini_remake_radiobox:    /*** mini_remake_radiobox ***/
/***
printf("Popup_RadioBox_Dialog_CB case mini_remake_radiobox: curr_env: %d\n",curr_env);
***/
    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );

    if ( ! ok_pressed ) {
      DisplayCurrWinText ( "\n  Mini-remake aborted\n" );
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
      InvokeB ( without_XTerm, 1 );
    }
    else {
      int file_diff;

      Load_SRC_CFG_Names ( curr_obj );

      file_diff = FileDiffIntoBcom ( curr_obj );
      if ( ! file_diff ) {
        Popup_Info ( "Mini-remake requested, but no edits saved!"  );
        radiobox_flag = mini_remake_radiobox;
        XtPopup ( dialog, XtGrabNone );
        XmUpdateDisplay ( dialog );
      }
      else {
        temp_dialog = dialog;
        radiobox_flag = mini_remake_radiobox;
        CheckFileParses ( curr_obj );
      }
    }
    break;

    case edit_pmd_radiobox:   /*** edit_pmd_radiobox - Popup_EditPmd (Provers Env -
                                                            ie. not InterProver) ***/
     {
       XtPopdown ( dialog );
       XmUpdateDisplay ( dialog );
       if ( ! ok_pressed ) {
         if ( curr_env == provers_env ) {
           DisplayCurrentEnv ();
	 }
       }
       else {
         switch ( rad_but ) {
         case  0 :
           OpenCurrentPMD ( curr_obj );
           break;
         case  1 :
	   {
             int i = 0;
             int all_sp = 1;
             Retrieve_String ( provers_str_num, primary_string );
             while ( primary_string [ i ] != '\0' && all_sp ) {
               if ( primary_string [ i ] != ' ' ) all_sp = 0;
               i++;
             }
             if ( all_sp ) {
               Popup_Minor_Err ( NULL, "Global PROOFMETHOD string not set\n  (Set in Top Bar Options - Provers)" );
	     }
             else {
               OpenGlobalPMD ();
	     }
	   }
           break;
         case 2 :
           {
             temp_widget = ( Widget ) dialog;
             GetAllLevelPMD ( curr_obj );
             Popup_Sel_flag = browse_pmd_selection;
             Popup_SelOne_Dialog ( top_level, "PROOFMETHOD to browse" );
	   }
           break;
	 }
       }
     }
     break;

  case six_animators_radiobox:        /*** six_animators_radiobox ***/

    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );

    if ( ! ok_pressed ) {
      DisplayCurrentEnv ();
    }
    else {
      switch ( rad_but ) {
      case  0 :                                   /* Interactive */
	{
          sprintf ( fifo_write_buf, "%s:%d:0", GetName ( curr_obj ), BT_CHK_FOR_OPS );
          InvokeB ( without_XTerm, 1 );
	}
        break;
      case 1:                                     /* Execute Step */
	{
          void LoadAnimateFilesInto_sel_strs ();
          void Popup_MainAnimatorMenu ();
          LoadAnimateFilesInto_sel_strs ( curr_obj, 0 );
          if ( sel_arr_tot ) {
            Popup_Sel_flag = anm_exe_step;
            Popup_SelOne_Dialog ( top_level, "Select ANIMATE Script" );
	  }
          else {
            sprintf ( buf,  "No appropriate ANIMATE Scripts %s",
                                                             GetName ( curr_obj ) );
            Popup_Info ( buf );
            Popup_MainAnimatorMenu ( curr_obj );
	  }
	}
        break;
      case 2:                                     /* Execute Auto */
	{
          void LoadAnimateFilesInto_sel_strs ();
          void Popup_MainAnimatorMenu ();
          LoadAnimateFilesInto_sel_strs ( curr_obj, 0 );
          if ( sel_arr_tot ) {
            Popup_Sel_flag = anm_exe_auto;
            Popup_SelOne_Dialog ( top_level, "Select ANIMATE Script" );
	  }
          else {
            sprintf ( buf,  "No appropriate ANIMATE Scripts for %s",
                                                             GetName ( curr_obj ) );
            Popup_MainAnimatorMenu ( curr_obj );
            Popup_Info ( buf );
	  }
	}
        break;
      case 3:                                     /* Edit ANIMATE Script */
	{
          void Popup_EditAnimateFile ();
          Popup_EditAnimateFile ();
	}
        break;
      case 4:                                     /* Browse Output File */
	{
          void LoadOutputFilesInto_sel_strs ();
          LoadOutputFilesInto_sel_strs ( curr_obj );
          if ( sel_arr_tot ) {
            Popup_Sel_flag = browse_out_selection;
            Popup_SelOne_Dialog ( top_level, "Output to browse" );
	  }
          else {
           void  Popup_MainAnimatorMenu ();
            sprintf ( buf,  "No appropriate Output for %s", GetName ( curr_obj ) );
            Popup_MainAnimatorMenu ( curr_obj );
            Popup_Info ( buf );
	  }
	}
        break;
      case 5:                                     /* Clean Animator Files */
	{
          void Popup_CleanAnimFiles ();
          Popup_CleanAnimFiles ();
	}
        break;
      }
    }
    break;
    

  case three_provers_radiobox:        /*** three_provers_radiobox ***/

    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );

    if ( ok_pressed ) {
      int st, lenpob;
      void DisplayNewEnv ();

      val_curMRIState( &st, curr_obj );
      length_pob ( &lenpob, st );

      switch ( rad_but ) {
      case  0 :
        Cre_fifo_write_buf_cmd_env ( curr_obj, BT_AUP_WITH_ENV, lenpob );
        strcpy ( xterm_title, "B-AutoProver" );
        InvokeB ( with_XTerm, 1 );
        break;
      case 1:
        DisplayNewEnv ( ipr_pob_env );
        inifunc();
        prev_thy [ 0 ] = '\0';
        prev_rule = 0;
        strcpy ( str_buf, "_____._____" );
        tmp_btool_ipr_thy = read_thefunc();
        {
          int i;
          for ( i = 0 ; i < 10 ; i++ ) {
            ipr_hyp_sch_dialog_up [ i ] = 0;
          }
        }
        ipr_hyp_dialog_up = 0;
        DisplayCurrWinText ( "\nInterProver:\n" );
        Retrieve_String ( editor_str_num, buf );
        Retrieve_String ( editor_str_num, str_buf );
        sprintf ( fifo_write_buf, "%s.%d:%d:(\"%s\";\"%s\")",
                        GetName ( curr_obj ), lenpob-1, BT_INP, buf, str_buf );
        strcpy ( xterm_title, "B-InterProver" );
        InvokeB ( with_XTerm, 1 );
        break;
      case 2:
        {
          void DisplayNewEnv ();
          struct stat stat_buf;

          DisplayNewEnv ( btl_env );
          sprintf ( fifo_write_buf, "POB/%s.0.po", GetName ( curr_obj ) );
          if ( stat ( fifo_write_buf, &stat_buf ) == 0 ) {
            if ( stat_buf.st_size > 1000000 ) {
              DisplayCurrWinText ( "\nBToolProver Environment:\n\n  Processing proof file\n  (this file is large - please be patient!) .." );
	    }
            else {
              DisplayCurrWinText ( "\nBToolProver Environment:\n\n  Processing proof file .." );
	    }
	  }
          sprintf ( fifo_write_buf, "%s.%d:%d:0", 
                                   GetName ( curr_obj ), lenpob-1, BT_BTL_INI );
          InvokeB ( without_XTerm, 1 );
        }
      }
    }  /* if ( ok_pressed ) */
    else {
      DisplayCurrentEnv ();
    }
    break;

  case source_control_setup_radiobox:     /*** source_control_setup_radiobox ***/

    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );

    if ( ok_pressed ) {

      switch ( rad_but ) {

      case  0 :         /* Edit $HOME/.Bsc */
#if ( defined ( UNKNOWN_VERSION ) )
        if ( ( sc_ps ) && ( getpgrp ( sc_ps ) != -1 ) ) {
#else
        if ( ( sc_ps ) && ( getpgid ( sc_ps ) != -1 ) ) {
#endif
          DisplayCurrWinText ( "\n  Already editing $HOME/.Bsc\n" );
          Popup_Info ( "Already editing $HOME/.Bsc" );
        }
        else {
          char *getenv(), *name;
          name = getenv ( "HOME" );
          if ( name == NULL ) {
            Popup_Info ( " Environment variable HOME not set " );
            DisplayCurrWinText ( "\n  Environment variable HOME not set\n" );
          }
          else {
            struct stat stat_buf;
            void Popup_SourceControl_DefaultEdit ();
            sprintf ( str_buf, "%s/.Bsc", name );
            if ( stat ( str_buf, &stat_buf ) == -1 ) {
              Popup_SourceControl_DefaultEdit ();
	    }
            else {
              Retrieve_String ( editor_str_num, buf );
	      /* - use more intelligent command line caller for editors: */
	      /*
              strcat ( buf, " " );
              strcat ( buf, str_buf );
              strcat ( buf, " & \n echo $! > .Bed" );
              execute ( buf );
	      */
	      editorCommand=getEditorCommandLine(buf,str_buf);
              strcpy(buf, editorCommand);
              free(editorCommand);
              strcat ( buf, " & \n echo $! > .Bed" );
	      execute ( buf );
	      
              Modify_sc_psFromBed ();
              XtPopup ( dialog, XtGrabNone );
              XmUpdateDisplay ( dialog );
              radiobox_flag = source_control_setup_radiobox;
	    }
	  }
	}
        break;

      case  1 :         /* Check $HOME/.Bsc */
        if ( CheckSourceControlFromBsc ( 0 ) )
          Popup_Info ( " $HOME/.Bsc checked " );
        XtPopup ( dialog, XtGrabNone );
        XmUpdateDisplay ( dialog );
        radiobox_flag = source_control_setup_radiobox;
        break;

      case  2 :         /* Install $HOME/.Bsc */
        if ( ! InstallSourceControlFromBsc ( 0 ) ) {
          XtPopup ( dialog, XtGrabNone );
          XmUpdateDisplay ( dialog );
          radiobox_flag = source_control_setup_radiobox;
	}
        else {
#if ( defined ( UNKNOWN_VERSION ) )
          if ( ( sc_ps ) && ( getpgrp ( sc_ps ) != -1 ) ) {
#else
          if ( ( sc_ps ) && ( getpgid ( sc_ps ) != -1 ) ) {
#endif
            sprintf ( buf, "kill -9 %d", sc_ps );
            system ( buf );
	  }
	}
        break;

      case  3 :         /* Close $HOME/.Bsc */
#if ( defined ( UNKNOWN_VERSION ) )
        if ( ( ! sc_ps ) || ( ( sc_ps ) && ( getpgrp ( sc_ps ) == -1 ) ) ) {
#else
        if ( ( ! sc_ps ) || ( ( sc_ps ) && ( getpgid ( sc_ps ) == -1 ) ) ) {
#endif
          DisplayCurrWinText ( "\n  Not editing $HOME/.Bsc\n" );
          Popup_Info ( "Not editing $HOME/.Bsc" );
        }
        else {
          sprintf ( buf, "kill -9 %d", sc_ps );
          system ( buf );
	}
        break;

	} /* switch ( rad_but ) */

    }  /* if ( ok_pressed ) */
    break;

   case source_control_edit_radiobox:     /*** source_control_edit_radiobox ***/

    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );

    if ( ok_pressed ) {

      FILE * Bsc;
      char *getenv(), *name;
      name = getenv ( "HOME" );
      if ( name == NULL ) {
        Popup_Info ( " Environment variable HOME not set " );
        DisplayCurrWinText ( "\n  Environment variable HOME not set\n" );
        return;
      }
      sprintf ( str_buf, "%s/.Bsc", name );

      switch ( rad_but ) {

      case  0 :         /* Defaults for RCS */
        Bsc = fopen ( str_buf, "w" );
        if ( Bsc == NULL ) {
          sprintf ( buf, "\"%s\" for writing", str_buf );
          AbortedMsgFile ( buf );
          BT_err_exit ( 0 );
	}
        fprintf ( Bsc, "Create (all commands are on SRC files)\n" );
        fprintf ( Bsc, "ci -i SRC/$1 $Bscdir/$1,v; Bstatus=$?; if [ $Bstatus = 0 ] then co SRC/$1 $Bscdir/$1,v; Bstatus=$? fi\n" );
        fprintf ( Bsc, "CHECKED_IN\n\n" );
        fprintf ( Bsc, "Check Out For Edit\n" );
        fprintf ( Bsc, "co -l SRC/$1 $Bscdir/$1,v; Bstatus=$?\n" );
        fprintf ( Bsc, "CHECKED_OUT\n\n" );
        fprintf ( Bsc, "Check Out Read Only\n" );
        fprintf ( Bsc, "co SRC/$1 $Bscdir/$1,v; Bstatus=$?\n" );
        fprintf ( Bsc, "UNCHANGED\n\n" );
        fprintf ( Bsc, "Check In & Check Out Read Only\n" );
        fprintf ( Bsc, "ci -u SRC/$1 $Bscdir/$1,v; Bstatus=$?\n" );
        fprintf ( Bsc, "CHECKED_IN\n\n" );
        fprintf ( Bsc, "Check In & Check Out For Edit\n" );
        fprintf ( Bsc, "ci -l SRC/$1 $Bscdir/$1,v; Bstatus=$?\n" );
        fprintf ( Bsc, "UNCHANGED\n\n" );
        fprintf ( Bsc, "Show Difference With Last Checked In\n" );
        fprintf ( Bsc, "rcsdiff SRC/$1 $Bscdir/$1,v; Bstatus=$?\n" );
        fprintf ( Bsc, "UNCHANGED\n\n" );
        fprintf ( Bsc, "Show History\n" );
        fprintf ( Bsc, "rlog SRC/$1 $Bscdir/$1,v; Bstatus=$?\n" );
        fprintf ( Bsc, "UNCHANGED\n\n" );
        fclose ( Bsc );
        break;
      case  1 :         /* Defaults for SCCS */
        Bsc = fopen ( str_buf, "w" );
        if ( Bsc == NULL ) {
          sprintf ( buf, "\"%s\" for writing", str_buf );
          AbortedMsgFile ( buf );
          BT_err_exit ( 0 );
	}
        fprintf ( Bsc, "Create (all commands are on SRC files)\n" );
        fprintf ( Bsc, "cd SRC; sccs -d$Bscdir create $1; Bstatus=$?\n" );
        fprintf ( Bsc, "CHECKED_IN\n\n" );
        fprintf ( Bsc, "Check Out For Edit\n" );
        fprintf ( Bsc, "cd SRC; sccs -d$Bscdir edit $1; Bstatus=$?\n" );
        fprintf ( Bsc, "CHECKED_OUT\n\n" );
        fprintf ( Bsc, "Check Out Read Only\n" );
        fprintf ( Bsc, "cd SRC; sccs -d$Bscdir get $1; Bstatus=$?\n" );
        fprintf ( Bsc, "UNCHANGED\n\n" );
        fprintf ( Bsc, "Check In & Check Out Read Only\n" );
        fprintf ( Bsc, "cd SRC; sccs -d$Bscdir delget $1; Bstatus=$?\n" );
        fprintf ( Bsc, "CHECKED_IN\n\n" );
        fprintf ( Bsc, "Check In & Check Out For Edit\n" );
        fprintf ( Bsc, "cd SRC; sccs -d$Bscdir deledit $1; Bstatus=$?\n" );
        fprintf ( Bsc, "UNCHANGED\n\n" );
        fprintf ( Bsc, "Show Difference With Last Checked In\n" );
        fprintf ( Bsc, "cd SRC; sccs -d$Bscdir diffs $1; Bstatus=$?\n" );
        fprintf ( Bsc, "UNCHANGED\n\n" );
        fprintf ( Bsc, "Show History\n" );
        fprintf ( Bsc, "cd SRC; sccs -d$Bscdir prt $1; Bstatus=$?\n" );
        fprintf ( Bsc, "UNCHANGED\n\n" );
        fclose ( Bsc );
        break;

	} /* switch ( rad_but ) */

      Retrieve_String ( editor_str_num, buf );
      /* - use more intelligent command line caller for editors: */
      /*
      strcat ( buf, " " );
      strcat ( buf, str_buf );
      strcat ( buf, " & \n echo $! > .Bed" );
      execute ( buf );
      */
      
      editorCommand=getEditorCommandLine(buf,str_buf);
      strcpy(buf, editorCommand);
      free(editorCommand);
      strcat ( buf, " & \n echo $! > .Bed" );
      execute ( buf );
      
      
      Modify_sc_psFromBed ();
     
      XtPopup ( SC_setup_dialog, XtGrabNone );
      XmUpdateDisplay ( SC_setup_dialog );
      radiobox_flag = source_control_setup_radiobox;

    }  /* if ( ok_pressed ) */
    break;

 case source_control_radiobox:     /*** source_control_radiobox ***/

    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );

    if ( ok_pressed ) {

      void LoadUsrConstructsInto_sel_strs ();
      FILE *  Bexe;
      struct SourceControlStruct * SC_1;

      Bexe = fopen ( "TMP/.Bsta", "w" );
      if ( Bexe == NULL ) {
        AbortedMsgFile ( "\".Bexe\" for writing" );
        BT_err_exit ( 0 );
        return;
      }
      fprintf ( Bexe, "999" );
      fclose ( Bexe );

      SC_1 = SC_0;
      SC_1 += rad_but;
      Bexe = fopen ( ".Bexe", "w" );
      if ( Bexe == NULL ) {
        AbortedMsgFile ( "\".Bexe\" for writing" );
        BT_err_exit ( 0 );
        return;
      }

      Retrieve_String ( source_control_str_num, buf );
      fprintf ( Bexe, "#! /bin/sh\ncurdir=`pwd`\nBscdir=%s\nBstatus=999\n\n%s\n\necho \"<CR> to continue\"\nread input\necho $Bstatus > $curdir/TMP/.Bsta\n", buf, SC_1 -> but_act );
      fclose ( Bexe );
      system ( "chmod +x .Bexe" );
      LoadUsrConstructsInto_sel_strs ();
      if ( sel_arr_tot ) {
        Popup_Sel_flag = source_control_sel;
        sprintf ( buf, "%s: select construct",SC_1 -> but_name );
        Popup_SelOne_Dialog ( top_level, buf );
      }
      else {
        Popup_Info ( "No user-constructs!" );
     }
    }  /* if ( ok_pressed ) */
    break;

  case file_ed_NML_radiobox:          /*** file_ed_NML_radiobox ***/

    if ( ! ok_pressed ) {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      DisplayCurrentEnv ();
    }
    else {
      switch ( rad_but ) {
      case 0:  /* proceed after commit */
	{
#ifdef WWW_VERSION
          WWW_Err;
          radiobox_flag = file_ed_NML_radiobox;
#else /* ! WWW_VERSION */
          DeSensitize ();
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          temp_dialog = dialog;
          Load_SRC_CFG_Names ( curr_obj );
          radiobox_flag = file_ed_NML_radiobox;
          CheckFileParses ( curr_obj );
#endif /* WWW_VERSION */
	}
        break;
      case 1:   /* proceed without commit */
        {
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          Cre_fifo_write_buf_cmd_env ( curr_obj, BT_NML_WITH_ENV, 0 );
          strcpy ( xterm_title, "B-Analyser" );
          InvokeB ( with_XTerm, 1 );
        }
        break;
      case 2:
        radiobox_flag = file_ed_NML_radiobox;
        ShowFileDiff ( curr_obj );
        break;
      }
    }
    break;


  case file_ed_GBO_radiobox:          /*** file_ed_GBO_radiobox ***/

    if ( ! ok_pressed ) {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      DisplayCurrentEnv ();
    }
    else {
      switch ( rad_but ) {
      case 0:  /* proceed after commit */
	{
#ifdef WWW_VERSION
          WWW_Err;
          radiobox_flag = file_ed_GBO_radiobox;
#else /* ! WWW_VERSION */
          DeSensitize ();
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          temp_dialog = dialog;
          Load_SRC_CFG_Names ( curr_obj );
          radiobox_flag = file_ed_GBO_radiobox;
          CheckFileParses ( curr_obj );
#endif /* WWW_VERSION */
	}
        break;
      case 1:   /* proceed without commit */
        {
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          Cre_fifo_write_buf_cmd_env ( curr_obj, BT_GBO_WITH_ENV, 0 );
          strcpy ( xterm_title, "B-Generator" );
          InvokeB ( with_XTerm, 1 );
        }
        break;
      case 2:
        radiobox_flag = file_ed_GBO_radiobox;
        ShowFileDiff ( curr_obj );
        break;
      }
    }
    break;


  case file_ed_ENM_radiobox:          /*** file_ed_ENM_radiobox ***/

    if ( ! ok_pressed ) {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      DisplayCurrentEnv ();
    }
    else {
      switch ( rad_but ) {
      case 0:  /* proceed after commit */
	{
#ifdef WWW_VERSION
          WWW_Err;
          radiobox_flag = file_ed_ENM_radiobox;
#else /* ! WWW_VERSION */
          DeSensitize ();
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          temp_dialog = dialog;
          Load_SRC_CFG_Names ( curr_obj );
          radiobox_flag = file_ed_ENM_radiobox;
          CheckFileParses ( curr_obj );
#endif /* WWW_VERSION */
	}
        break;
      case 1:   /* proceed without commit */
        {
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          Cre_fifo_write_buf_cmd_env ( curr_obj, BT_ENUM_WITH_ENV, 0 );
          strcpy ( xterm_title, "B-Enumerator" );
          InvokeB ( with_XTerm, 1 );
        }
        break;
      case 2:
        radiobox_flag = file_ed_ENM_radiobox;
        ShowFileDiff ( curr_obj );
        break;
      }
    }
    break;


  case file_ed_ITF_radiobox:          /*** file_ed_ITF_radiobox ***/

    if ( ! ok_pressed ) {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      DisplayCurrentEnv ();
    }
    else {
      switch ( rad_but ) {
      case 0:  /* proceed after commit */
	{
#ifdef WWW_VERSION
          WWW_Err;
          radiobox_flag = file_ed_ITF_radiobox;
#else /* ! WWW_VERSION */
          DeSensitize ();
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          temp_dialog = dialog;
          Load_SRC_CFG_Names ( curr_obj );
          radiobox_flag = file_ed_ITF_radiobox;
          CheckFileParses ( curr_obj );
#endif /* WWW_VERSION */
	}
        break;
      case 1:   /* proceed without commit */
        {
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          Pre_Itf ( curr_obj );
        }
        break;
      case 2:
        radiobox_flag = file_ed_ITF_radiobox;
        ShowFileDiff ( curr_obj );
        break;
      }
    }
    break;

  case close_anm_thy_file:            /*** close_anm_thy_file ***/
    XtPopdown ( dialog );             /* Cancel is insensitive */
    XmUpdateDisplay ( dialog );
    temp_dialog = dialog;
    switch ( rad_but ) {
    case 0:                           /* Check file parses */
      CheckAnmThyFileParses ();
      break;
    case 1:                           /* Don't check file parses */
      if ( anm_thy_ps ) {
        int nn, cc, cc1;
        strcpy ( buf, "kill -9 " );
        CreNumInBuf ( buf, anm_thy_ps );
        system ( buf );
      }
      Popup_Minor_Err ( NULL, "Animator theory file not checked for parsing" );
      anm_thy_ps = 0;
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
      InvokeB ( without_XTerm, 1 );
    }
    break;

  case close_pmd_file:  /***  close_pmd_file ***/
    {
      int st, level;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      temp_dialog = dialog;
      switch ( rad_but ) {
      case 0 :                        /* Check file parses */
        {
          int ss;
          if ( current_pmd_ps ) {
            val_curMRIState( &st, curr_obj );
            length_pob( &level, st );
            sprintf ( buf, "PMD/%s.%d.pmd", GetName ( curr_obj ), level - 1 ); 
	  }
          else {
            Retrieve_String ( provers_str_num, buf );
	  }
          tmp_from_btoolkit = 1;
          if ( FileParses ( buf ) ) {
            if ( current_pmd_ps ) {
              sprintf ( buf, "kill -9 %d", current_pmd_ps );
              current_pmd_ps = 0;
              system ( buf );
	    }
            if ( global_pmd_ps ) {
              sprintf ( buf, "kill -9 %d", global_pmd_ps );
              global_pmd_ps = 0;
              system ( buf );
	    }
            if ( ( curr_env ==  ipr_pob_env ) || ( curr_env ==  ipr_lem_env ) ) {
	      if ( curr_env ==  ipr_lem_env ) {
                strcpy ( primary_string, "Reload  PROOFMETHOD?" );
                strcpy ( secondary_string, "Lemmas should be proved with PROOFMETHOD\n loaded!" );
                confirm_flag = reload_PMD_confirm;
                Popup_ConfirmDialog ( top_level );
                Popup_Info ( "PROOFMETHOD parses" );
	      }
              else { /* curr_env ==  ipr_pob_env */
                Ipr_Sel_Ops ( top_level, Ipr_Prf_Option, 0 );
                Popup_Info ( "PROOFMETHOD parses" );
	      }
	    }
            else if ( curr_env ==  ipr_pob_env ) {
              Popup_Minor_Err ( NULL, "PROOFMETHOD parses\n\nHowever, it is loaded only at the `Prove Lemma' stage\nof the InterProver and will have no effect until then ..." );
              DisplayCurrentEnv ();
	    }
            else {
              Popup_Info ( "PROOFMETHOD parses" );
              DisplayCurrentEnv ();
	    }
	  }
          else {
            XtPopup ( temp_dialog, XtGrabNone );
            XmUpdateDisplay ( temp_dialog );
            XmUpdateDisplay ( top_level );
            radiobox_flag = close_pmd_file;
            Popup_Info ( "PROOFMETHOD doesn't parse" );
	  }
	}
      break;
      case 1 :                        /* Don't check file parses */
        if ( current_pmd_ps ) {
          sprintf ( buf, "kill -9 %d", current_pmd_ps );
          current_pmd_ps = 0;
          system ( buf );
	}
        if ( global_pmd_ps ) {
          sprintf ( buf, "kill -9 %d", global_pmd_ps );
          global_pmd_ps = 0;
          system ( buf );
	}
        Popup_Minor_Err ( NULL, "PROOFMETHOD not checked for parsing" );
	if ( ( curr_env ==  ipr_pob_env ) || ( curr_env ==  ipr_lem_env ) ) {
          Ipr_Sel_Ops ( top_level, Ipr_Prf_Option, 0 );
	}
        else {
          DisplayCurrentEnv ();
	}
        break;
      }
    }
    break;

  case close_anm_exe_file:  /***  close_anm_exe_file ***/
    {
      /***
      sel_str_arr [ sel_arr_MAX ] contains file name
      ***/

      int st, level;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      temp_dialog = dialog;
      switch ( rad_but ) {
      case 0 :                        /* Check file parses */
        if ( FileParses ( sel_str_arr [ sel_arr_MAX ] ) ) {
          void Popup_MainAnimatorMenu ();
          sprintf ( buf, "kill -9 %d", anm_exe_ps );
          system ( buf );
          anm_exe_ps = 0;
          Popup_MainAnimatorMenu ( curr_obj );
          sprintf ( buf, "%s parses", sel_str_arr [ sel_arr_MAX ] );
	}
        else {
          XtPopup ( temp_dialog, XtGrabNone );
          XmUpdateDisplay ( temp_dialog );
          XmUpdateDisplay ( top_level );
          radiobox_flag = close_anm_exe_file;
          sprintf ( buf, "%s doesn't parse", sel_str_arr [ sel_arr_MAX ] );
	}
        Popup_Info ( buf );
        break;
      case 1 :                        /* Don't check file parses */
        {
          void Popup_MainAnimatorMenu ();
          sprintf ( buf, "kill -9 %d", anm_exe_ps );
          system ( buf );
          anm_exe_ps = 0;
          sprintf ( buf, "%s not checked for parsing", sel_str_arr [ sel_arr_MAX ] );
          Popup_MainAnimatorMenu ( curr_obj );
          Popup_Minor_Err ( NULL, buf );
          break;
	}
      }
    }
    break;

  case file_ed_POG_radiobox:          /*** file_ed_POG_radiobox ***/

    if ( ! ok_pressed ) {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      DisplayCurrentEnv ();
    }
    else {
      switch ( rad_but ) {
      case 0:  /* proceed after commit */
	{
#ifdef WWW_VERSION
          WWW_Err;
          radiobox_flag = file_ed_POG_radiobox;
#else /* ! WWW_VERSION */
          DeSensitize ();
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          temp_dialog = dialog;
          Load_SRC_CFG_Names ( curr_obj );
          radiobox_flag = file_ed_POG_radiobox;
          CheckFileParses ( curr_obj );
#endif /* WWW_VERSION */
	}
        break;
      case 1:   /* proceed without commit */
        {
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          Cre_fifo_write_buf_cmd_env ( curr_obj, BT_POG_WITH_ENV, 0 );
          strcpy ( xterm_title, "B-POGenerator" );
          InvokeB ( with_XTerm, 1 );
        }
        break;
      case 2:
        radiobox_flag = file_ed_POG_radiobox;
        ShowFileDiff ( curr_obj );
        break;
      }
    }
    break;


  case file_ed_DOC_radiobox:          /*** file_ed_DOC_radiobox ***/

    if ( ! ok_pressed ) {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      DisplayCurrentEnv ();
    }
    else {
      switch ( rad_but ) {
      case 0:  /* proceed after commit */
	{
#ifdef WWW_VERSION
          WWW_Err;
          radiobox_flag = file_ed_DOC_radiobox;
#else /* ! WWW_VERSION */
          DeSensitize ();
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          temp_dialog = dialog;
          Load_SRC_CFG_Names ( curr_obj );
          radiobox_flag = file_ed_DOC_radiobox;
          CheckFileParses ( curr_obj );
#endif /* WWW_VERSION */
	}
        break;
      case 1:   /* proceed without commit */
        {
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          Cre_fifo_write_buf_cmd_env ( curr_obj, BT_DOC_WITH_ENV, 0 );
          strcpy ( xterm_title, "B-Documentor" );
          InvokeB ( with_XTerm, 1 );
        }
        break;
      case 2:
        radiobox_flag = file_ed_DOC_radiobox;
        ShowFileDiff ( curr_obj );
        break;
      }
    }
    break;


  case file_ed_DMU_radiobox:          /*** file_ed_DMU_radiobox ***/

    if ( ! ok_pressed ) {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      DisplayCurrentEnv ();
    }
    else {
      switch ( rad_but ) {
      case 0:  /* proceed after commit */
	{
#ifdef WWW_VERSION
          WWW_Err;
          radiobox_flag = file_ed_DMU_radiobox;
#else /* ! WWW_VERSION */
          DeSensitize ();
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          temp_dialog = dialog;
          Load_SRC_CFG_Names ( curr_obj );
          radiobox_flag = file_ed_DMU_radiobox;
          CheckFileParses ( curr_obj );
#endif /* WWW_VERSION */
	}
        break;
      case 1:   /* proceed without commit */
        {
          XtPopdown ( dialog );
          XmUpdateDisplay ( dialog );
          Cre_fifo_write_buf_cmd_env ( curr_obj, BT_DMU_WITH_ENV, 0 );
          strcpy ( xterm_title, "B-Documentor" );
          InvokeB ( with_XTerm, 1 );
        }
        break;
      case 2:
        radiobox_flag = file_ed_DMU_radiobox;
        ShowFileDiff ( curr_obj );
        break;
      }
    }
    break;


  case remove_radiobox:   /*** remove_radiobox ***/
    radiobox_flag = remove_radiobox;

    if ( ! ok_pressed ) {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        RemoveNext ();
      }
    else {
      if ( rad_but == file_diff_but ) {
        ShowFileDiff ( curr_obj );
      }
      else  {
        XtPopdown ( dialog );
        XmUpdateDisplay ( dialog );
        sprintf ( buf, "\n  Removed %s", GetName ( curr_obj ) );
        DisplayCurrWinText( buf );
        switch ( rad_but ) {
        case 0:     /*** Save SRC ***/
          DisplayCurrWinText ( " - SRC file preserved\n" );
          break;
        case 1:     /*** Save CFG ***/
          CopyCFGSRC ();
          DisplayCurrWinText ( " - copied into SRC\n" );
          break;
	}
        DisplayCurrWinText ( "\n" );
        KillConstruct ( curr_obj );
        RemoveNext ();
      }
    }
    break;


  case commit_btool_radiobox:   /*** commit_btool_radiobox ***/

    Popup_Sel_flag = 0;
    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );
    switch ( rad_but ) {
    case 0:                      /* commit */
      exit___contd ( 1, 0 );  /* commit, not autoproof */
      break;
    case 1:                      /* don't commit */
      exit___contd ( 0, 0 );  /* don't commit, not autoproof */
      break;
    }
    break;

  case commit_ipr_radiobox:   /*** commit_ipr_radiobox ***/

    {
      int st, lenpob;
      void DisplayNewEnv ();

      Popup_Sel_flag = 0;
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      val_curMRIState( &st, curr_obj );
      length_pob ( &lenpob, st );
      switch ( rad_but ) {
      case 0:  /* commit */
        Cre_fifo_write_buf_cmd_env ( curr_obj, BT_AUP_WITH_ENV, lenpob );
        strcpy ( xterm_title, "B-AutoProver" );
        DisplayNewEnv ( provers_env );
        InvokeB ( with_XTerm, 1 );
        break;
      case 1:  /* don't commit */
        sprintf ( buf, "\n  Proofs not committed\n\n  Current Proof Level %d maintained\n  for %s\n", lenpob - 1, GetName ( curr_obj ) );
        DisplayCurrWinText ( buf );
        DisplayNewEnv ( provers_env );
        break;
      }
    }
    break;


  default:              /*** default ***/
/***
printf("NOPE - radiobox_flag = %d (originally %d)\n",rad_option,radiobox_flag);
***/

    if ( ! ok_pressed ) {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      strcpy ( fifo_write_buf, "0:" );
    }
    else {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );

      switch ( rad_but ) {
      case  0: strcpy ( fifo_write_buf, "1:" ); break;
      case  1: strcpy ( fifo_write_buf, "2:" ); break;
      case  2: strcpy ( fifo_write_buf, "3:" ); break;
      case  3: strcpy ( fifo_write_buf, "4:" ); break;
      case  4: strcpy ( fifo_write_buf, "5:" ); break;
      case  5: strcpy ( fifo_write_buf, "6:" ); break;
      case  6: strcpy ( fifo_write_buf, "7:" ); break;
      case  7: strcpy ( fifo_write_buf, "8:" ); break;
      case  8: strcpy ( fifo_write_buf, "9:" ); break;
      case  9: strcpy ( fifo_write_buf, "10:" ); break;
      case 10: strcpy ( fifo_write_buf, "11:" ); break;
      case 11: strcpy ( fifo_write_buf, "12:" ); break;
      }
    }
    Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
    InvokeB ( without_XTerm, 1 );
    break;
  }
}

void
file_ed_radiobox_contd ()
{
  /***
  curr_obj is set
  ***/

/***
printf ( "file_ed_radiobox_contd %s", GetName ( curr_obj ) );
***/

  if ( committed ) {

    /***
    committed
    ***/
    switch ( radiobox_flag ) {
    case file_ed_NML_radiobox:
      Cre_fifo_write_buf_cmd_env ( curr_obj, BT_NML_WITH_ENV, 0 );
      strcpy ( xterm_title, "B-Analyser" );
      break;
    case file_ed_POG_radiobox:
      Cre_fifo_write_buf_cmd_env ( curr_obj, BT_POG_WITH_ENV, 0 );
      strcpy ( xterm_title, "B-POGenerator" );
      break;
    case file_ed_DOC_radiobox:
      Cre_fifo_write_buf_cmd_env ( curr_obj, BT_DOC_WITH_ENV, 0 );
      strcpy ( xterm_title, "B-Documentor" );
      break;
    case file_ed_DMU_radiobox:
      Cre_fifo_write_buf_cmd_env ( curr_obj,BT_DMU_WITH_ENV, 0 );
      strcpy ( xterm_title, "B-Documentor" );
      break;
    case file_ed_GBO_radiobox:
      Cre_fifo_write_buf_cmd_env ( curr_obj, BT_GBO_WITH_ENV, 0 );
      strcpy ( xterm_title, "B-Generator" );
      break;
    case file_ed_ENM_radiobox:
      Cre_fifo_write_buf_cmd_env ( curr_obj, BT_ENUM_WITH_ENV, 0 );
      strcpy ( xterm_title, "B-Enumerator" );
      break;
    }
    radiobox_flag = 0;
    InvokeB ( with_XTerm, 1 );  

  }

  else {

    /***
    not committed
    ***/
    strcpy ( primary_string, GetName ( curr_obj ) );
    XtPopup ( temp_dialog, XtGrabNone );
    XmUpdateDisplay ( temp_dialog );
  }
}

void
ITF_ed_radiobox_contd ()
{

  /***
  curr_obj is set
  ***/

/***
printf ( "ITF_ed_radiobox_contd %s", GetName ( curr_obj ) );
***/

  if ( committed ) {

    /***
    committed
    ***/
    radiobox_flag = 0;
    Pre_Itf ( curr_obj );

  }

  else {

    /***
    not committed
    ***/
    strcpy ( primary_string, GetName ( curr_obj ) );
    XtPopup ( temp_dialog, XtGrabNone );
    XmUpdateDisplay ( temp_dialog );
  }
}

void
mini_remake_radiobox_contd ()
{

/***
printf ( "mini_remake_radiobox_contd\n" );
***/

  if ( committed ) {

    /***
    committed
    ***/
    radiobox_flag = 0;

    if ( curr_env != anm_env ) {

      /***
      not animator
      ***/
      strcpy ( fifo_write_buf, "0:" );
      CreNumInBuf ( fifo_write_buf, BT_CNT_MINI_REMK );
      Cre_tcp_env ();
      strcpy ( xterm_title, "B-MiniRemake" );
      InvokeB ( with_XTerm, 1 );
    }

    else {

      /***
      animator
      ***/
      int bb, nn, cc, cc1;

      sprintf ( fifo_write_buf, "(%s|?", GetName ( curr_obj ) );
      def_sees_uses ( &bb, cc );
      if   ( bb )  card_sees_uses ( &nn, cc );
      else          nn = 0;
      while ( nn ) {
        valOrd_sees_uses ( &cc1, cc, nn );
        strcat ( fifo_write_buf, "," );
        strcat ( fifo_write_buf,GetName ( cc1 ) );
        nn--;
      }
      strcat ( fifo_write_buf, "):" );
      CreNumInBuf ( fifo_write_buf, BT_ANM_WITH_ENV );
      Cre_tcp_env ();
      strcpy ( xterm_title, "B-Animator" );
      InvokeB ( with_XTerm, 1 );
    }


  }

  else {

    /***
    not committed
    ***/
    XtPopup ( temp_dialog, XtGrabNone );
    XmUpdateDisplay ( temp_dialog );

  }

}

void
Popup_EditedFileExists_Dialog_CB ( button, client_data, call_data )
Widget button;
XtPointer client_data;
XtPointer call_data;
{
  /***
  curr_obj is set
  ***/

  int rad_but, * rad_but_address;
  int ok_pressed, file_diff_but;
  Widget dialog;
  XmAnyCallbackStruct * cbs = ( XmAnyCallbackStruct * ) call_data;

/***
printf ( "Popup_EditedFileExists_Dialog_CB  radiobox_flag %d ", radiobox_flag );
printf ( "curr_env %d\n", curr_env );
printf ( "  (Popup_Sel_flag %d)\n", Popup_Sel_flag );
fflush ( stdout );
***/

  /***
  get parent dialog/OK or CANCEL/file_diff_but/rad_but
  ***/
  if ( cbs->reason == XmCR_PROTOCOLS ) {    /*** WM Close ***/
    dialog =  button;
    ok_pressed = 0;
    file_diff_but = 999;
/***
printf ( "XmNuserData   = %d\n", ( ( struct ok_cancel_but_struct * ) client_data ) -> but );
***/
    XtVaGetValues (
        ( Widget ) ( ( ( struct ok_cancel_but_struct * ) client_data ) -> but ),
        XmNuserData,    & rad_but_address,
        NULL );
  }
  else {
    dialog = XtParent ( XtParent ( XtParent ( button ) ) );
    if ( ( ( ( struct ok_cancel_but_struct * ) client_data ) -> but ) == OK_BUTTON )
      ok_pressed = 1;
    else
      ok_pressed = 0;
    file_diff_but =
           ( ( struct ok_cancel_but_struct * ) client_data ) -> file_diff_but;
/***
printf ( "XmNuserData   = %d\n", XtParent ( XtParent ( button ) ) );
***/
    XtVaGetValues ( XtParent ( XtParent ( button ) ),
        XmNuserData,    & rad_but_address,
        NULL );
  }
  rad_but = * rad_but_address;

/***
printf ( "cbs->reason   = %d\n", cbs->reason );
printf ( "dialog        = %d\n", dialog );
printf ( "ok_pressed    = %d\n", ok_pressed );
printf ( "file_diff_but = %d\n", file_diff_but );
printf ( "rad_but       = %d\n\n", rad_but );
***/

  if ( ! ok_pressed ) {
    XtPopdown ( dialog );
    XmUpdateDisplay ( dialog );
  }

  else {
    if ( rad_but == file_diff_but ) {
      ShowFileDiff ( curr_obj );
    }
    else  {
      XtPopdown ( dialog );
      XmUpdateDisplay ( dialog );
      if ( rad_but == 1 ) {     /* open CFG file */
        CopyCFGSRC ( curr_obj );
      }
      else {                    /* open SRC file */
        sprintf ( buf, "\n  SRC file %s opened\n", GetName ( curr_obj ) );
        DisplayCurrWinText ( buf );
      }
      OpenConstruct ( curr_obj );
    }
  }
}
