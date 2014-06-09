/* Copyright (c) 1988-968, B-Core (UK) Ltd
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static XmStringCharSet charset = ( XmStringCharSet ) XmSTRING_DEFAULT_CHARSET ;

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

#include "../MOTIF/BMotif_BaseParameters.h"

#include "../MOTIF/CFG_DEP_BASE/CDE/C/CfgDepBase.g"

#include "../MOTIF/CFG_DEP_BASE/CDE/C/file_dump.g"
#include "../MOTIF/CFG_DEP_BASE/CDE/C/CfgDepCtx.g"
#include "../MOTIF/CFG_DEP_BASE/CDE/C/CfgDepBaseCtx.g"
#include "../MOTIF/CFG_DEP_BASE/CDE/C/Scalar_TYPE.g"
#include "../MOTIF/CFG_DEP_BASE/CDE/C/Bool_TYPE.g"
#include "../MOTIF/CFG_DEP_BASE/CDE/C/String_TYPE.g"
#include "../MOTIF/CFG_DEP_BASE/CDE/C/basic_io.g"
#include "../MOTIF/CFG_DEP_BASE/CDE/C/CfgDepBase_file_dump.g"

#include "../MOTIF/CFG_DEP_BASE/CDE/C/CfgDepCtx.h"


/******************************************************************************/

#define  read_fm(a,b)    fread(&a,sizeof(int),b,dump_file)

#define  read_fmc(a,b)   fread(&a,sizeof(char),b,dump_file)

#define  write_fm(a,b)   fwrite(&a,sizeof(int),b,dump_file)

#define  write_fmc(a,b)  fwrite(&a,sizeof(char),b,dump_file)

FILE * dump_file;

void
Write ( ss )
char * ss;
{
  puts ( ss );  fflush ( stdout );
}

void
WriteDot ()
{
  Write ( "." );
}

/******************************************************************************/

void
Info_342 ()
{
  printf ( "\n" );
  printf ( "   %6d                Construct\n", Construct_ssize_fnc_obj - Construct_sold_fnc_obj );
  printf ( "   %6d                Abs2Conc\n", Abs2Conc_ssize_fnc_obj - Abs2Conc_sold_fnc_obj );
  printf ( "   %6d                MRIState\n", MRIState_ssize_fnc_obj - MRIState_sold_fnc_obj );
  printf ( "   %6d                GENState\n", GENState_ssize_fnc_obj - GENState_sold_fnc_obj );
  printf ( "   %6d                STR_OBJ\n", CfgDepBase_ssiz_len_str_obj-1-CfgDepBase_ssiz_old_str_obj );
  printf ( "   %6d                SEQ_OBJ\n", CfgDepBase_ssiz_len_seq_obj-1-CfgDepBase_ssiz_old_seq_obj );
  printf ( "   %6d                SET_OBJ\n", CfgDepBase_ssiz_len_set_obj-1-CfgDepBase_ssiz_old_set_obj );
}

/******************************************************************************/

int
CfgDepBase_open_read_file_342()
{
	dump_file = fopen(".Bpda","r");
        if ( dump_file == NULL ) {
          printf ( "\n  Can't open \".Bpda\" for reading\n\n" );
          return 0;
	}
        return 1;
}

void
CfgDepBase_RST_FNC_342()
{
	read_fm(CfgDepBase_Vfnc[1],CfgDepBase_VffncP2);
}

void
Construct_RST_FNC_OBJ_342()
{
	read_fm(Construct_ssize_fnc_obj,1);
	read_fm(Construct_fnc_obj[1],Construct_ssize_fnc_obj*Construct_ffnc_objP2);
	read_fm(Construct_sold_fnc_obj,1);
	read_fm(Construct_old_fnc_obj[1],Construct_ssize_fnc_obj);
}

void
Abs2Conc_RST_FNC_OBJ_342()
{
	read_fm(Abs2Conc_ssize_fnc_obj,1);
	read_fm(Abs2Conc_fnc_obj[1],Abs2Conc_ssize_fnc_obj*Abs2Conc_ffnc_objP2);
	read_fm(Abs2Conc_sold_fnc_obj,1);
	read_fm(Abs2Conc_old_fnc_obj[1],Abs2Conc_ssize_fnc_obj);
}

void
MRIState_RST_FNC_OBJ_342()
{
	read_fm(MRIState_ssize_fnc_obj,1);
	read_fm(MRIState_fnc_obj[1],MRIState_ssize_fnc_obj*MRIState_ffnc_objP2);
	read_fm(MRIState_sold_fnc_obj,1);
	read_fm(MRIState_old_fnc_obj[1],MRIState_ssize_fnc_obj);
}

void
GENState_RST_FNC_OBJ_342()
{
	read_fm(GENState_ssize_fnc_obj,1);
	read_fm(GENState_fnc_obj[1],GENState_ssize_fnc_obj*GENState_ffnc_objP2);
	read_fm(GENState_sold_fnc_obj,1);
	read_fm(GENState_old_fnc_obj[1],GENState_ssize_fnc_obj);
}

void
CfgDepBase_RST_STR_OBJ_342()
{
	int i;
	char c;
	read_fm(CfgDepBase_tot_str_obj,1);
	read_fm(CfgDepBase_ssiz_adr_str_obj,1);
	read_fm(CfgDepBase_adr_str_obj[1],CfgDepBase_ssiz_adr_str_obj);
	read_fm(CfgDepBase_ssiz_len_str_obj,1);
	read_fm(CfgDepBase_len_str_obj[1],CfgDepBase_ssiz_len_str_obj);
	read_fm(CfgDepBase_ssiz_old_str_obj,1);
	read_fm(CfgDepBase_old_str_obj[1],CfgDepBase_ssiz_old_str_obj);
	read_fmc(CfgDepBase_array_str_obj[1],
                 CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1]
                );
	i = CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1] % 4;
	while( i!=0 ){
		read_fmc(c,1);
		i = i-1;
	}
}

void
CfgDepBase_RST_SEQ_OBJ_342()
{
	read_fm(CfgDepBase_tot_seq_obj,1);
	read_fm(CfgDepBase_ssiz_adr_seq_obj,1);
	read_fm(CfgDepBase_adr_seq_obj[1],CfgDepBase_ssiz_adr_seq_obj);
	read_fm(CfgDepBase_ssiz_len_seq_obj,1);
	read_fm(CfgDepBase_len_seq_obj[1],CfgDepBase_ssiz_len_seq_obj);
	read_fm(CfgDepBase_ssiz_old_seq_obj,1);
	read_fm(CfgDepBase_old_seq_obj[1],CfgDepBase_ssiz_old_seq_obj);
	read_fm(CfgDepBase_array_seq_obj[1],
                CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj-1]
               );
}

void
CfgDepBase_RST_SET_OBJ_342()
{
	read_fm(CfgDepBase_tot_set_obj,1);
	read_fm(CfgDepBase_ssiz_adr_set_obj,1);
	read_fm(CfgDepBase_adr_set_obj[1],CfgDepBase_ssiz_adr_set_obj);
	read_fm(CfgDepBase_ssiz_len_set_obj,1);
	read_fm(CfgDepBase_len_set_obj[1],CfgDepBase_ssiz_len_set_obj);
	read_fm(CfgDepBase_ssiz_old_set_obj,1);
	read_fm(CfgDepBase_old_set_obj[1],CfgDepBase_ssiz_old_set_obj);
	read_fm(CfgDepBase_array_set_obj[1],CfgDepBase_adr_set_obj[CfgDepBase_ssiz_adr_set_obj-1]);
}


void
CfgDepBase_close_file_342()
{
	fclose(dump_file);
}

/***************/

int
restore_CfgDepBase_342()
{
        if ( CfgDepBase_open_read_file_342() ) {
          Write ( "\n  Reading 3.4.2 data file ." );
	  CfgDepBase_RST_FNC_342();
          WriteDot ();
	  Construct_RST_FNC_OBJ_342();
          WriteDot ();
	  Abs2Conc_RST_FNC_OBJ_342();
          WriteDot ();
	  MRIState_RST_FNC_OBJ_342();
          WriteDot ();
	  GENState_RST_FNC_OBJ_342();
          WriteDot ();
	  CfgDepBase_RST_STR_OBJ_342();
          WriteDot ();
	  CfgDepBase_RST_SEQ_OBJ_342();
          WriteDot ();
	  CfgDepBase_RST_SET_OBJ_342();
          WriteDot ();
	  CfgDepBase_close_file_342();
          Write ( " done\n" );
/***
Info_342 ();
***/
          return 1;
	}
        return 0;
}

/******************************************************************************/

void
Info_40 ()
{
  printf ( "\n" );
  printf ( "   %6d %6d         Construct\n", (Construct_ssize_fnc_obj - Construct_sold_fnc_obj), Construct_ffnc_objP3 );
  printf ( "   %6d %6d         Abs2Conc\n", (Abs2Conc_ssize_fnc_obj - Abs2Conc_sold_fnc_obj), Abs2Conc_ffnc_objP3 );
  printf ( "   %6d %6d         MRIState\n", (MRIState_ssize_fnc_obj - MRIState_sold_fnc_obj), MRIState_ffnc_objP3 );
  printf ( "   %6d %6d         GENState\n", (GENState_ssize_fnc_obj - GENState_sold_fnc_obj), GENState_ffnc_objP3 );
  printf ( "   %6d %6d %6d  STR_OBJ\n", CfgDepBase_ssiz_len_str_obj-1-CfgDepBase_ssiz_old_str_obj, CfgDepBase_str_objP1, CfgDepBase_tot_str_obj );
  printf ( "   %6d %6d %6d  SEQ_OBJ\n", CfgDepBase_ssiz_len_seq_obj-1-CfgDepBase_ssiz_old_seq_obj, CfgDepBase_seq_objP2, CfgDepBase_tot_seq_obj );
  printf ( "   %6d %6d %6d  SET_OBJ\n", CfgDepBase_ssiz_len_set_obj-1-CfgDepBase_ssiz_old_set_obj, CfgDepBase_set_objP2, CfgDepBase_tot_set_obj );
  printf ( "   %6d %6d         Seqstr\n", (Seqstr_ssize_fnc_obj - Seqstr_sold_fnc_obj), Seqstr_ffnc_objP3 );
  printf ( "   %6d %6d         String\n", (String_ssize_fnc_obj - String_sold_fnc_obj), String_ffnc_objP3 );
}

/******************************************************************************/

#define CfgDepBase_open_write_dump_40(rep) \
  { *rep = ( ( dump_file = fopen ( "CfgDepBase.dump", "w" ) ) != NULL ); }

void
CfgDepBase_SAV_FNC_40()
{
	write_fm(CfgDepBase_Vfnc[1],CfgDepBase_VffncP2);
}

void
Construct_SAV_FNC_OBJ_40()
{
	write_fm(Construct_ssize_fnc_obj,1);
        write_fm(Construct_ffnc_objP2,1);
	write_fm(Construct_fnc_obj[1],Construct_ssize_fnc_obj*Construct_ffnc_objP2);
	write_fm(Construct_sold_fnc_obj,1);
	write_fm(Construct_old_fnc_obj[1],Construct_ssize_fnc_obj);
}

void
Abs2Conc_SAV_FNC_OBJ_40()
{
	write_fm(Abs2Conc_ssize_fnc_obj,1);
        write_fm(Abs2Conc_ffnc_objP2,1);
	write_fm(Abs2Conc_fnc_obj[1],Abs2Conc_ssize_fnc_obj*Abs2Conc_ffnc_objP2);
	write_fm(Abs2Conc_sold_fnc_obj,1);
	write_fm(Abs2Conc_old_fnc_obj[1],Abs2Conc_ssize_fnc_obj);
}

void
MRIState_SAV_FNC_OBJ_40()
{
	write_fm(MRIState_ssize_fnc_obj,1);
        write_fm(MRIState_ffnc_objP2,1);
	write_fm(MRIState_fnc_obj[1],MRIState_ssize_fnc_obj*MRIState_ffnc_objP2);
	write_fm(MRIState_sold_fnc_obj,1);
	write_fm(MRIState_old_fnc_obj[1],MRIState_ssize_fnc_obj);
}

void
GENState_SAV_FNC_OBJ_40()
{
	write_fm(GENState_ssize_fnc_obj,1);
        write_fm(GENState_ffnc_objP2,1);
	write_fm(GENState_fnc_obj[1],GENState_ssize_fnc_obj*GENState_ffnc_objP2);
	write_fm(GENState_sold_fnc_obj,1);
	write_fm(GENState_old_fnc_obj[1],GENState_ssize_fnc_obj);
}

#define INI_Seqstr_ffnc_obj_40() \
{Seqstr_ssize_fnc_obj = 0; Seqstr_sold_fnc_obj=0;}

void
Seqstr_SAV_FNC_OBJ_40()
{
	write_fm(Seqstr_ssize_fnc_obj,1);
        write_fm(Seqstr_ffnc_objP2,1);
	write_fm(Seqstr_fnc_obj[1],Seqstr_ssize_fnc_obj*Seqstr_ffnc_objP2);
	write_fm(Seqstr_sold_fnc_obj,1);
	write_fm(Seqstr_old_fnc_obj[1],Seqstr_ssize_fnc_obj);
}

void
String_SAV_FNC_OBJ_40()
{
	write_fm(String_ssize_fnc_obj,1);
        write_fm(String_ffnc_objP2,1);
	write_fm(String_fnc_obj[1],String_ssize_fnc_obj*String_ffnc_objP2);
	write_fm(String_sold_fnc_obj,1);
	write_fm(String_old_fnc_obj[1],String_ssize_fnc_obj);
}

void
CfgDepBase_SAV_STR_OBJ_40()
{
	int i;
	char c;
        CfgDepBase_tot_str_obj = CfgDepBase_str_objP2-CfgDepBase_tot_str_obj;
	write_fm(CfgDepBase_tot_str_obj,1);
	write_fm(CfgDepBase_ssiz_adr_str_obj,1);
	write_fm(CfgDepBase_adr_str_obj[1],CfgDepBase_ssiz_adr_str_obj);
	write_fm(CfgDepBase_ssiz_len_str_obj,1);
	write_fm(CfgDepBase_len_str_obj[1],CfgDepBase_ssiz_len_str_obj);
	write_fm(CfgDepBase_ssiz_old_str_obj,1);
	write_fm(CfgDepBase_old_str_obj[1],CfgDepBase_ssiz_old_str_obj);
	write_fmc(CfgDepBase_array_str_obj[1],CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1]);
	i = CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1] % 4;
	c = 'w';
	while( i!=0 ){
		write_fmc(c,1);
		i = i-1;
	}
        CfgDepBase_tot_str_obj = CfgDepBase_str_objP2-CfgDepBase_tot_str_obj;
}

void
CfgDepBase_SAV_SEQ_OBJ_40()
{
        CfgDepBase_tot_seq_obj = CfgDepBase_seq_objP3-CfgDepBase_tot_seq_obj;
	write_fm(CfgDepBase_tot_seq_obj,1);
	write_fm(CfgDepBase_ssiz_adr_seq_obj,1);
	write_fm(CfgDepBase_adr_seq_obj[1],CfgDepBase_ssiz_adr_seq_obj);
	write_fm(CfgDepBase_ssiz_len_seq_obj,1);
	write_fm(CfgDepBase_len_seq_obj[1],CfgDepBase_ssiz_len_seq_obj);
	write_fm(CfgDepBase_ssiz_old_seq_obj,1);
	write_fm(CfgDepBase_old_seq_obj[1],CfgDepBase_ssiz_old_seq_obj);
	write_fm(CfgDepBase_array_seq_obj[1],CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj-1]);
        CfgDepBase_tot_seq_obj = CfgDepBase_seq_objP3-CfgDepBase_tot_seq_obj;
}

void
CfgDepBase_SAV_SET_OBJ_40()
{
        CfgDepBase_tot_set_obj = CfgDepBase_set_objP3-CfgDepBase_tot_set_obj;
	write_fm(CfgDepBase_tot_set_obj,1);
	write_fm(CfgDepBase_ssiz_adr_set_obj,1);
	write_fm(CfgDepBase_adr_set_obj[1],CfgDepBase_ssiz_adr_set_obj);
	write_fm(CfgDepBase_ssiz_len_set_obj,1);
	write_fm(CfgDepBase_len_set_obj[1],CfgDepBase_ssiz_len_set_obj);
	write_fm(CfgDepBase_ssiz_old_set_obj,1);
	write_fm(CfgDepBase_old_set_obj[1],CfgDepBase_ssiz_old_set_obj);
	write_fm(CfgDepBase_array_set_obj[1],CfgDepBase_adr_set_obj[CfgDepBase_ssiz_adr_set_obj-1]);
        CfgDepBase_tot_set_obj = CfgDepBase_set_objP3-CfgDepBase_tot_set_obj;
}

#define CfgDepBase_close_dump_40(rep) \
  { *rep = ( ( fclose ( dump_file ) ) == 0 ); }

/***************/

void
save_CfgDepBase(rep)
int *rep;
{
  int bb;
  CfgDepBase_open_write_dump_40(&bb);
  if( bb ){
    Write ( "\n  Writing 4.0 data file ." );
    CfgDepBase_SAV_FNC_40();
    WriteDot ();
    Construct_SAV_FNC_OBJ_40();
    WriteDot ();
    Abs2Conc_SAV_FNC_OBJ_40();
    WriteDot ();
    MRIState_SAV_FNC_OBJ_40();
    WriteDot ();
    GENState_SAV_FNC_OBJ_40();
    WriteDot ();
    INI_Seqstr_ffnc_obj_40 ();
    Seqstr_SAV_FNC_OBJ_40();
    WriteDot ();
    String_SAV_FNC_OBJ_40();
    WriteDot ();
    CfgDepBase_SAV_STR_OBJ_40();
    WriteDot ();
    CfgDepBase_SAV_SEQ_OBJ_40();
    WriteDot ();
    CfgDepBase_SAV_SET_OBJ_40();
    WriteDot ();
    Write ( " done\n" );
/***
Info_40 ();
***/
    CfgDepBase_close_dump_40(&bb);
  }
  *rep = bb;
}

/******************************************************************************/

#define CfgDepBase_open_read_dump_40(rep) \
  { *rep = ( ( dump_file = fopen ( "CfgDepBase.dump", "r" ) ) != NULL ); }

void
CfgDepBase_RST_FNC_40()
{
	read_fm(CfgDepBase_Vfnc[1],CfgDepBase_VffncP2);
}

void
Construct_RST_FNC_OBJ_40()
{
	int old_size, i;
	read_fm(Construct_ssize_fnc_obj,1);
	read_fm(old_size,1);
        if ( old_size == Construct_ffnc_objP2 ) {
	  read_fm(Construct_fnc_obj[1],Construct_ssize_fnc_obj*Construct_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= Construct_ssize_fnc_obj*Construct_ffnc_objP2 ) {
	    Construct_fnc_obj[i] = 2147483647;
            i = i+1;
	  }
          i = 1;
          while ( i <= Construct_ssize_fnc_obj ) {
	    read_fm(Construct_fnc_obj[1+(i-1)*Construct_ffnc_objP2], old_size);
            i = i+1;
	  }
	}
	read_fm(Construct_sold_fnc_obj,1);
	read_fm(Construct_old_fnc_obj[1],Construct_ssize_fnc_obj);
}

void
Abs2Conc_RST_FNC_OBJ_40()
{
	int old_size, i;
	read_fm(Abs2Conc_ssize_fnc_obj,1);
	read_fm(old_size,1);
        if ( old_size == Abs2Conc_ffnc_objP2 ) {
	  read_fm(Abs2Conc_fnc_obj[1],Abs2Conc_ssize_fnc_obj*Abs2Conc_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= Abs2Conc_ssize_fnc_obj*Abs2Conc_ffnc_objP2 ) {
	    Abs2Conc_fnc_obj[i] = 2147483647;
            i = i+1;
	  }
          i = 1;
          while ( i <= Abs2Conc_ssize_fnc_obj ) {
	    read_fm(Abs2Conc_fnc_obj[1+(i-1)*Abs2Conc_ffnc_objP2], old_size);
            i = i+1;
	  }
	}
	read_fm(Abs2Conc_sold_fnc_obj,1);
	read_fm(Abs2Conc_old_fnc_obj[1],Abs2Conc_ssize_fnc_obj);
}

void
MRIState_RST_FNC_OBJ_40()
{
	int old_size, i;
	read_fm(MRIState_ssize_fnc_obj,1);
	read_fm(old_size,1);
        if ( old_size == MRIState_ffnc_objP2 ) {
	  read_fm(MRIState_fnc_obj[1],MRIState_ssize_fnc_obj*MRIState_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= MRIState_ssize_fnc_obj*MRIState_ffnc_objP2 ) {
	    MRIState_fnc_obj[i] = 2147483647;
            i = i+1;
	  }
          i = 1;
          while ( i <= MRIState_ssize_fnc_obj ) {
	    read_fm(MRIState_fnc_obj[1+(i-1)*MRIState_ffnc_objP2], old_size);
            i = i+1;
	  }
	}
	read_fm(MRIState_sold_fnc_obj,1);
	read_fm(MRIState_old_fnc_obj[1],MRIState_ssize_fnc_obj);
}

void
GENState_RST_FNC_OBJ_40()
{
	int old_size, i;
	read_fm(GENState_ssize_fnc_obj,1);
	read_fm(old_size,1);
        if ( old_size == GENState_ffnc_objP2 ) {
	  read_fm(GENState_fnc_obj[1],GENState_ssize_fnc_obj*GENState_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= GENState_ssize_fnc_obj*GENState_ffnc_objP2 ) {
	    GENState_fnc_obj[i] = 2147483647;
            i = i+1;
	  }
          i = 1;
          while ( i <= GENState_ssize_fnc_obj ) {
	    read_fm(GENState_fnc_obj[1+(i-1)*GENState_ffnc_objP2], old_size);
            i = i+1;
	  }
	}
	read_fm(GENState_sold_fnc_obj,1);
	read_fm(GENState_old_fnc_obj[1],GENState_ssize_fnc_obj);
}

void
Seqstr_RST_FNC_OBJ_40()
{
	int old_size, i;
	read_fm(Seqstr_ssize_fnc_obj,1);
	read_fm(old_size,1);
        if ( old_size == Seqstr_ffnc_objP2 ) {
	  read_fm(Seqstr_fnc_obj[1],Seqstr_ssize_fnc_obj*Seqstr_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= Seqstr_ssize_fnc_obj*Seqstr_ffnc_objP2 ) {
	    Seqstr_fnc_obj[i] = 2147483647;
            i = i+1;
	  }
          i = 1;
          while ( i <= Seqstr_ssize_fnc_obj ) {
	    read_fm(Seqstr_fnc_obj[1+(i-1)*Seqstr_ffnc_objP2], old_size);
            i = i+1;
	  }
	}
	read_fm(Seqstr_sold_fnc_obj,1);
	read_fm(Seqstr_old_fnc_obj[1],Seqstr_ssize_fnc_obj);
}

void
String_RST_FNC_OBJ_40()
{
	int old_size, i;
	read_fm(String_ssize_fnc_obj,1);
	read_fm(old_size,1);
        if ( old_size == String_ffnc_objP2 ) {
	  read_fm(String_fnc_obj[1],String_ssize_fnc_obj*String_ffnc_objP2);
	}
        else {
          i = 1;
          while ( i <= String_ssize_fnc_obj*String_ffnc_objP2 ) {
	    String_fnc_obj[i] = 2147483647;
            i = i+1;
	  }
          i = 1;
          while ( i <= String_ssize_fnc_obj ) {
	    read_fm(String_fnc_obj[1+(i-1)*String_ffnc_objP2], old_size);
            i = i+1;
	  }
	}
	read_fm(String_sold_fnc_obj,1);
	read_fm(String_old_fnc_obj[1],String_ssize_fnc_obj);
}

void
CfgDepBase_RST_STR_OBJ_40()
{
	int i;
	char c;
	read_fm(CfgDepBase_tot_str_obj,1);
	read_fm(CfgDepBase_ssiz_adr_str_obj,1);
	read_fm(CfgDepBase_adr_str_obj[1],CfgDepBase_ssiz_adr_str_obj);
	read_fm(CfgDepBase_ssiz_len_str_obj,1);
	read_fm(CfgDepBase_len_str_obj[1],CfgDepBase_ssiz_len_str_obj);
	read_fm(CfgDepBase_ssiz_old_str_obj,1);
	read_fm(CfgDepBase_old_str_obj[1],CfgDepBase_ssiz_old_str_obj);
	read_fmc(CfgDepBase_array_str_obj[1],CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1]);
	i = CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj-1] % 4;
	while( i!=0 ){
		read_fmc(c,1);
		i = i-1;
	}
        CfgDepBase_tot_str_obj = CfgDepBase_str_objP2-CfgDepBase_tot_str_obj;
        CfgDepBase_adr_str_obj[CfgDepBase_ssiz_adr_str_obj] = CfgDepBase_str_objP2;
}

void
CfgDepBase_RST_SEQ_OBJ_40()
{
	read_fm(CfgDepBase_tot_seq_obj,1);
	read_fm(CfgDepBase_ssiz_adr_seq_obj,1);
	read_fm(CfgDepBase_adr_seq_obj[1],CfgDepBase_ssiz_adr_seq_obj);
	read_fm(CfgDepBase_ssiz_len_seq_obj,1);
	read_fm(CfgDepBase_len_seq_obj[1],CfgDepBase_ssiz_len_seq_obj);
	read_fm(CfgDepBase_ssiz_old_seq_obj,1);
	read_fm(CfgDepBase_old_seq_obj[1],CfgDepBase_ssiz_old_seq_obj);
	read_fm(CfgDepBase_array_seq_obj[1],
                   CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj-1]);
        CfgDepBase_tot_seq_obj = CfgDepBase_seq_objP3-CfgDepBase_tot_seq_obj;
        CfgDepBase_adr_seq_obj[CfgDepBase_ssiz_adr_seq_obj] = CfgDepBase_seq_objP3;
}

void
CfgDepBase_RST_SET_OBJ_40()
{
	read_fm(CfgDepBase_tot_set_obj,1);
	read_fm(CfgDepBase_ssiz_adr_set_obj,1);
	read_fm(CfgDepBase_adr_set_obj[1],CfgDepBase_ssiz_adr_set_obj);
	read_fm(CfgDepBase_ssiz_len_set_obj,1);
	read_fm(CfgDepBase_len_set_obj[1],CfgDepBase_ssiz_len_set_obj);
	read_fm(CfgDepBase_ssiz_old_set_obj,1);
	read_fm(CfgDepBase_old_set_obj[1],CfgDepBase_ssiz_old_set_obj);
	read_fm(CfgDepBase_array_set_obj[1],CfgDepBase_adr_set_obj[CfgDepBase_ssiz_adr_set_obj-1]);
        CfgDepBase_tot_set_obj = CfgDepBase_set_objP3-CfgDepBase_tot_set_obj;
        CfgDepBase_adr_set_obj[CfgDepBase_ssiz_adr_set_obj] = CfgDepBase_set_objP3;
}

/***************/

void
restore_CfgDepBase_40(rep)
int *rep;
{
  int bb;
  CfgDepBase_open_read_dump_40(&bb);
  if( bb ){
    Write ( "\n  Reading 4.0 data file ." );
    CfgDepBase_RST_FNC_40();
    WriteDot ();
    Construct_RST_FNC_OBJ_40();
    WriteDot ();
    Abs2Conc_RST_FNC_OBJ_40();
    WriteDot ();
    MRIState_RST_FNC_OBJ_40();
    WriteDot ();
    GENState_RST_FNC_OBJ_40();
    WriteDot ();
    Seqstr_RST_FNC_OBJ_40();
    WriteDot ();
    String_RST_FNC_OBJ_40();
    WriteDot ();
    CfgDepBase_RST_STR_OBJ_40();
    WriteDot ();
    CfgDepBase_RST_SEQ_OBJ_40();
    WriteDot ();
    CfgDepBase_RST_SET_OBJ_40();
    WriteDot ();
    Write ( " done\n" );
/***
Info_40 ();
***/
    CfgDepBase_close_dump_40(&bb);
  }
  *rep = bb;
}

/******************************************************************************/

int
main ( argc, argv )
int argc;
char *argv[];
{
  Widget        toplevel, frame, rc, rc2, but1, but2, but3;
  XtAppContext  app;
  void          proceed_remake ();
  void          proceed_no_remake ();
  void          no_proceed ();
  XmString 	xstr;
  void upgrade_end ();
  
  if ( argc != 3 ) upgrade_end ( 1 );
  if ( strcmp ( argv [ 2 ], "5" ) != 0 ) upgrade_end ( 1 );

  XtSetLanguageProc ( NULL, NULL, NULL );

  toplevel = XtVaAppInitialize ( &app, "XBMotif", NULL, 0,
        &argc, argv, NULL, NULL );

  XtVaSetValues ( toplevel,
      XmNheight, 225,
      XmNwidth,  250,
      XmNx,      250,
      XmNy,      250,
      NULL );

  rc = XtVaCreateManagedWidget ( "MainWin",
      xmRowColumnWidgetClass,  toplevel,
      XmNmarginWidth,          10,
      XmNmarginHeight,         10,
      XmNspacing,              10,
      NULL );

  frame = XtVaCreateManagedWidget ( "SelDialog",
      xmFrameWidgetClass,        rc,
      XmNshadowType,             XmSHADOW_ETCHED_IN,
      NULL );

  xstr = XmStringCreateLtoR ( "\nA B-Toolkit 3 development!\n\nTo run B-Toolkit 4\nit must be upgraded,\nnecessitating resetting\nand, optionally, remaking.", charset ); 
  but1 = XtVaCreateManagedWidget ( "SelDialog",
      xmLabelWidgetClass,      frame,
      XmNlabelString,          xstr,
      XmNmarginWidth,          5,
      XmNmarginHeight,         5,
      NULL );
  XmStringFree ( xstr );
  
  rc2 = XtVaCreateManagedWidget ( "SelDialog",
      xmFormWidgetClass,       rc,
      XmNmarginWidth,          0,
      XmNmarginHeight,         0,
      NULL );

  xstr = XmStringCreateLtoR ( "Upgrade, Reset & Remake", charset ); 
  but1 = XtVaCreateManagedWidget ( "SelDialog",
      xmPushButtonWidgetClass, rc2,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           0,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          0,
      XmNlabelString,          xstr,
      XmNmarginWidth,          5,
      XmNmarginHeight,         5,
      NULL );
  XmStringFree ( xstr );
  XtAddCallback ( but1, XmNactivateCallback, proceed_remake, NULL );

  xstr = XmStringCreateLtoR ( "Upgrade & Reset", charset ); 
  but2 = XtVaCreateManagedWidget ( "SelDialog",
      xmPushButtonWidgetClass, rc2,
      XmNtopAttachment,        XmATTACH_WIDGET,
      XmNtopWidget,            but1,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           0,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          0,
      XmNlabelString,          xstr,
      XmNmarginWidth,          5,
      XmNmarginHeight,         5,
      NULL );
  XmStringFree ( xstr );
  XtAddCallback ( but2, XmNactivateCallback, proceed_no_remake, NULL );

  xstr = XmStringCreateLtoR ( "Abort Upgrade", charset ); 
  but3 = XtVaCreateManagedWidget ( "SelDialog",
      xmPushButtonWidgetClass, rc2,
      XmNtopAttachment,        XmATTACH_WIDGET,
      XmNtopWidget,            but2,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           0,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          0,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNlabelString,          xstr,
      XmNmarginWidth,          5,
      XmNmarginHeight,         5,
      NULL );
  XmStringFree ( xstr );
  XtAddCallback ( but3, XmNactivateCallback, no_proceed, NULL );

  XtRealizeWidget ( toplevel );
  XtAppMainLoop ( app );

}

/******************************************************************************/

void
no_proceed ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  void upgrade_end ();
  printf ( "\n\n  Upgrade aborted\n\n\n" );
  upgrade_end ( 0 );
}

int
upgrade ()
{
  int rep;

  if ( restore_CfgDepBase_342() ) save_CfgDepBase ( &rep );
  if ( rep ) restore_CfgDepBase_40( &rep );
  if   ( rep ) Write ( "\n  Upgrade 3.4.2 -> 4.0 complete\n\n" );
  else         Write ( "\n  Upgrade 3.4.2 -> 4.0 failed\n\n" );
  return ( rep );
}

void
proceed_remake ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  void upgrade_end ();
  int rep = upgrade ();

  if ( rep ) rep++;
  upgrade_end ( rep );
}

void
proceed_no_remake ( widget, client_data, call_data )
Widget widget;
XtPointer client_data;
XtPointer call_data;
{
  void upgrade_end ();
  int rep = upgrade ();

  upgrade_end ( rep );
}

void
upgrade_end ( rep )
int rep;
{
  FILE * Bcom;
  Bcom = fopen ( "TMP/.Bcom", "w" );
  if ( Bcom != NULL ) {
    putc ( rep, Bcom );
    fclose ( Bcom );
  }
  exit ( rep );
}
