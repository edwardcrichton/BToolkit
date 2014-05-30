/* Copyright (c) 1992-98, B-Core (UK) Ltd
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

#include <inttypes.h>

#include "BMotif_globals.h"

struct Display * Display_0   = ( struct Display * ) NULL;
struct Display * Display_1   = ( struct Display * ) NULL;
struct Display * Display_2   = ( struct Display * ) NULL;
struct Display * Display_3   = ( struct Display * ) NULL;    /* Set*Sensitive */
struct Display * Display_visible;

/*int DisplayMallocTotal = 0;*/
/* may overflow */

intptr_t DisplayMallocTotal = 0;

int DisplayTotal = 0;
#define MALLOC_Display_INIT           25
#define MALLOC_Display_TOPUP          10

#define cmt_num     0
#define nme_num    99

struct MainDisplay * Main_0 = ( struct MainDisplay * ) NULL;
struct MainDisplay * Main_1 = ( struct MainDisplay * ) NULL;
struct MainDisplay * Main_2 = ( struct MainDisplay * ) NULL;
/*int MainMallocTotal = 0;*/
intptr_t MainMallocTotal = 0;

int MainTotal = 0;

#define MALLOC_MainDisplay_INIT       25
#define MALLOC_Main_TOPUP             10
#define anl_num     1
#define pog_num     2
#define anm_num     3
#define sts_num     4
#define rst_num     5

struct ProversDisplay * Provers_0 = ( struct ProversDisplay * ) NULL;
struct ProversDisplay * Provers_1 = ( struct ProversDisplay * ) NULL;
struct ProversDisplay * Provers_2 = ( struct ProversDisplay * ) NULL;

/*int ProversMallocTotal = 0;*/
intptr_t ProversMallocTotal = 0;

int ProversTotal = 0;

#define MALLOC_ProversDisplay_INIT    25
#define MALLOC_Provers_TOPUP          10
#define prv_num     6
#define pmd_num     7
#define ppf_num     8
#define rsl_num     9
#define lvl_num    10

struct GeneratorsDisplay * Generators_0 = ( struct GeneratorsDisplay * ) NULL;
struct GeneratorsDisplay * Generators_1 = ( struct GeneratorsDisplay * ) NULL;
struct GeneratorsDisplay * Generators_2 = ( struct GeneratorsDisplay * ) NULL;

/*int GeneratorsMallocTotal = 0;*/
intptr_t GeneratorsMallocTotal = 0;
int GeneratorsTotal = 0;

#define MALLOC_GeneratorsDisplay_INIT    5
#define MALLOC_Generators_TOPUP          5
#define gbo_num        11
#define gbm_num        12
#define Enm_num        13
#define Itf_num        14
#define gen_rst_num    15

struct TranslatorsDisplay * Translators_0 = ( struct TranslatorsDisplay * ) NULL;
struct TranslatorsDisplay * Translators_1 = ( struct TranslatorsDisplay * ) NULL;
struct TranslatorsDisplay * Translators_2 = ( struct TranslatorsDisplay * ) NULL;

/*int TranslatorsMallocTotal = 0;*/
intptr_t TranslatorsMallocTotal = 0;
int TranslatorsTotal = 0;

#define MALLOC_TranslatorsDisplay_INIT   5
#define MALLOC_Translators_TOPUP         5
#define trl_num        16
#define lnk_num        17
#define exe_num        18
#define trl_rst_num    19
#define fin_num        20

struct DocumentsDisplay * Documents_0 = ( struct DocumentsDisplay * ) NULL;
struct DocumentsDisplay * Documents_1 = ( struct DocumentsDisplay * ) NULL;
struct DocumentsDisplay * Documents_2 = ( struct DocumentsDisplay * ) NULL;

/*int DocumentsMallocTotal = 0;*/
intptr_t DocumentsMallocTotal = 0;
int DocumentsTotal = 0;

#define MALLOC_DocumentsDisplay_INIT    10
#define MALLOC_Documents_TOPUP           5
#define dmu_num        21
#define shw_num        22
#define prt_num        23
#define doc_rst_num    24


int MasterChanged = 1;

int MainSensitized = 1;
int ProversSensitized = 1;
int GeneratorsSensitized = 1;
int TranslatorsSensitized = 1;
int DocumentsSensitized = 1;

Boolean FrameSensitized = True;

int display_initialisation = 0;
/* - not needed */
/*
Widget * display_initialisation_malloc_arr;
int display_initialisation_malloc_idx = 0;
int display_initialisation_malloc_idx_0 = 0;
*/

/*
XmTextPosition display_text_pos;
*/
/*
#define applicable_unedited_chr ( char ) 164
*/
#define applicable_unedited_chr ( char ) 160 /* */
char applicable_unedited_str [ 5 ];

#define applicable_edited_chr   ( char ) '!'
char applicable_edited_str [ 5 ];

#define inapplicable_chr        ( char ) ' '
char inapplicable_str [ 5 ];


#define undecor_SRC_file_newer 0
#define decor_SRC_file_newer   1

#define cmt_off    0
#define cmt_on     1

void
PrintMallocRanges ()
{
  printf ( "Display:     %p->%p\n", Display_0, Display_0 + DisplayMallocTotal );
  printf ( "Main:        %p->%p\n", Main_0, Main_0 + MainMallocTotal );
  printf ( "Provers:     %p->%p\n", Provers_0, Provers_1 );
  printf ( "Generators:  %p->%p\n", Generators_0, Generators_1 );
  printf ( "Translators: %p->%p\n", Translators_0, Translators_1 );
  printf ( "Documents:   %p->%p\n", Documents_0, Documents_1 );
}

void
MainStatusStructure ( offset ) /* Display_1 is set */
int offset;
{
  if ( offset == -1 ) return;
  Main_1 = Main_0 + offset;
  printf ( "    row %p\n", Main_1->row );
  printf ( "    cmt %p\n", Main_1->cmt );
  printf ( "    anl %p\n", Main_1->anl );
  printf ( "    pog %p\n", Main_1->pog );
  printf ( "    anm %p\n", Main_1->anm );
  printf ( "    sts %p\n", Main_1->sts );
  printf ( "    rst %p\n", Main_1->rst );
  printf ( "    nme %p\n", Main_1->nme );
}

void
ProversStatusStructure ( offset ) /* Display_1 is set */
int offset;
{
  if ( offset == -1 ) return;
  Provers_1 = Provers_0 + offset;
  printf ( "    row %p\n", Provers_1->row );
  printf ( "    cmt %p\n", Provers_1->cmt );
  printf ( "    prv %p\n", Provers_1->prv );
  printf ( "    pmd %p\n", Provers_1->pmd );
  printf ( "    ppf %p\n", Provers_1->ppf );
  printf ( "    rsl %p\n", Provers_1->rsl );
  printf ( "    lvl %p\n", Provers_1->lvl );
  printf ( "    nme %p\n", Provers_1->nme );
}

void
GeneratorsStatusStructure ( offset ) /* Display_1 is set */
int offset;
{
  if ( offset == -1 ) return;
  Generators_1 = Generators_0 + offset;
  printf ( "    row %p\n", Generators_1->row );
  printf ( "    cmt %p\n", Generators_1->cmt );
  printf ( "    gbo %p\n", Generators_1->gbo );
  printf ( "    gbm %p\n", Generators_1->gbm );
  printf ( "    Enm %p\n", Generators_1->Enm );
  printf ( "    Itf %p\n", Generators_1->Itf );
  printf ( "    rst %p\n", Generators_1->rst );
  printf ( "    nme %p\n", Generators_1->nme );
}

void
TranslatorsStatusStructure ( offset ) /* Display_1 is set */
int offset;
{
  if ( offset == -1 ) return;
  Translators_1 = Translators_0 + offset;
  printf ( "    row %p\n", Translators_1->row );
  printf ( "    cmt %p\n", Translators_1->cmt );
  printf ( "    trl %p\n", Translators_1->trl );
  printf ( "    lnk %p\n", Translators_1->lnk );
  printf ( "    exe %p\n", Translators_1->exe );
  printf ( "    rst %p\n", Translators_1->rst );
  printf ( "    nme %p\n", Translators_1->nme );
}

void
DocumentsStatusStructure ( offset ) /* Display_1 is set */
int offset;
{
  if ( offset == -1 ) return;
  Documents_1 = Documents_0 + offset;
  printf ( "    row %p\n", Documents_1->row );
  printf ( "    cmt %p\n", Documents_1->cmt );
  printf ( "    dmu %p\n", Documents_1->dmu );
  printf ( "    shw %p\n", Documents_1->shw );
  printf ( "    prt %p\n", Documents_1->prt );
  printf ( "    rst %p\n", Documents_1->rst );
  printf ( "    nme %p\n", Documents_1->nme );
}

void
DisplayStatusStructure ( obj )
int obj;
{
  void SetDisplay_1_for_obj ();
  SetDisplay_1_for_obj ( obj );
  printf ( "--------------- %s --------------\n", Display_1->name );
  printf ( "  obj:                %2d\n",  Display_1->obj );
  printf ( "  type:               %2d\n",  Display_1->type );
  printf ( "  changed:            %2d\n",  Display_1->changed );
  printf ( "  decoration          %2d\n",  Display_1->decoration );
  printf ( "  cmt_on_off          %2d\n", Display_1->cmt_on_off );
  printf ( "  sc_state            %2d\n", Display_1->sc_state );
  printf ( "  ps:                 %2d\n",  Display_1->ps );
  printf ( "  Main_offset:        %2d\n",  Display_1->Main_offset );
  MainStatusStructure ( Display_1->Main_offset );
  printf ( "  Provers_offset:     %2d\n",  Display_1->Provers_offset );
  ProversStatusStructure ( Display_1->Provers_offset );
  printf ( "  Generators_offset:  %2d\n",  Display_1->Generators_offset );
  GeneratorsStatusStructure ( Display_1->Generators_offset);
  printf ( "  Translators_offset: %2d\n",  Display_1->Translators_offset );
  TranslatorsStatusStructure ( Display_1->Translators_offset);
  printf ( "  Documents_offset:   %2d\n",  Display_1->Documents_offset );
  DocumentsStatusStructure ( Display_1->Documents_offset);
  printf ( "----------------------------------------------\n" );
}

void
DisplayStatusStructureAll ()
{
  printf ( "  -------- DisplayStatusStructureAll --------\n\n" );
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    DisplayStatusStructure ( Display_1->obj );
  }
  printf ( "\n                 Total %3d\n\n", DisplayTotal );
  printf ( "  -------------------------------------------\n" );
}

void
DisplayAndCheckTotals ()
{
  int tot;

  printf ( "\nDisplay         %3d ", DisplayTotal );
  printf ( " (" PRIdPTR ")\n", DisplayMallocTotal );

  printf ( "Main            %3d ", MainTotal );
  tot = 0;
  for ( Main_1 = Main_0 ;
	 Main_1 < Main_0 + MainMallocTotal ; Main_1++ ) {
    if ( Main_1->row != /*( XtPointer )*/ NULL ) tot++;
  }
  if ( tot != MainTotal ) printf ( " ********** tot = %d ********** ", tot );
  printf ( " (" PRIdPTR ")\n", MainMallocTotal );

  printf ( "Provers         %3d ", ProversTotal );
  tot = 0;
  for ( Provers_1 = Provers_0 ;
	 Provers_1 < Provers_0 + ProversMallocTotal ; Provers_1++ ) {
    if ( Provers_1->row != /*( XtPointer )*/ NULL ) tot++;
  }
  if ( tot != ProversTotal ) printf ( " ********** tot = %d ********** ", tot );
  printf ( " (" PRIdPTR ")\n", ProversMallocTotal );

  printf ( "Generators      %3d ", GeneratorsTotal );
  tot = 0;
  for ( Generators_1 = Generators_0 ;
	 Generators_1 < Generators_0 + GeneratorsMallocTotal ; Generators_1++ ) {
    if ( Generators_1->row != /*( XtPointer )*/ NULL ) tot++;
  }
  if ( tot != GeneratorsTotal ) printf ( " ********** tot = %d ********** ", tot );
  printf ( " (" PRIdPTR ")\n", GeneratorsMallocTotal );

  printf ( "Translators     %3d ", TranslatorsTotal );
  tot = 0;
  for ( Translators_1 = Translators_0 ;
	 Translators_1 < Translators_0 + TranslatorsMallocTotal ; Translators_1++ ) {
    if ( Translators_1->row != /*( XtPointer )*/ NULL ) tot++;
  }
  if ( tot != TranslatorsTotal ) printf ( " ********** tot = %d ********** ", tot );
  printf ( " (" PRIdPTR ")\n", TranslatorsMallocTotal );

  printf ( "Documents       %3d ", DocumentsTotal );
  tot = 0;
  for ( Documents_1 = Documents_0 ;
         Documents_1 < Documents_0 + DocumentsMallocTotal ; Documents_1++ ) {
    if ( Documents_1->row != /*( XtPointer )*/ NULL ) tot++;
  }
  if ( tot != DocumentsTotal ) printf ( " ********** tot = %d ********** ", tot );
  printf ( " (" PRIdPTR ")\n", DocumentsMallocTotal );

}

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/


/*********************************************************************************/

void
Set_display_initialisation ()
{
  /*if ( DisplayTotal > 25 ) {*/
  
    XtUnmanageChild ( main_row_scroll );
    XtUnmanageChild ( provers_row_scroll );
    XtUnmanageChild ( generators_row_scroll );
    XtUnmanageChild ( translators_row_scroll );
    XtUnmanageChild ( documents_row_scroll );

  /*}*/

    display_initialisation = 1;
    /* - not needed */
    /*
    display_initialisation_malloc_arr = ( Widget * ) malloc ( ( 5 * DisplayTotal + 5 )  * sizeof ( Widget ) );
    */
/***
printf ( "\n ++++++++++++++++++++++++++++ malloc ( display_initialisation_malloc_arr )\n" ); fflush ( stdout );
***/

  initial_reattachment = 1;
}

/*********************************************************************************/

void
Reset_display_initialisation ()
{
  int tot;
  /*int dot_counter = 200;*/ /* not used ?*/
  /*void DisplayCurrentEnv ();*/ /* not used ? */
  void  DisplayNewEnv ();
  /* */
  WidgetList children=NULL;
  Cardinal num_children = 0;
  Widget forms[5];
  int num_forms=5;

  int formCounter=0;
  /* */

  nbr_Construct ( & tot );
  if ( display_initialisation ) {
    DisplayCurrWinText ( "\n  Initialising constructs " );
    if ( tot >= 250 ) DisplayCurrWinText ( "... please be patient " );
/*
       while ( display_initialisation_malloc_idx_0 != display_initialisation_malloc_idx )
       {
/???
printf ( "                                      %4d - %d\n",
   display_initialisation_malloc_idx_0, display_initialisation_malloc_arr [ display_initialisation_malloc_idx_0 ] );
???/
         XtManageChild ( display_initialisation_malloc_arr [ display_initialisation_malloc_idx_0++ ] );
      
         if ( ( display_initialisation_malloc_idx_0/dot_counter)*dot_counter == display_initialisation_malloc_idx_0 )
	 {
           DisplayCurrWinText ( ".");
           if ( dot_counter > 20 ) dot_counter -= 15;
/???
printf ( "dot_counter %d\n", dot_counter );
???/
         }
       }
       */
       
       /* - TRY IT THIS WAY */
	
	  forms[0]=main_row_form;
	  forms[1]=provers_row_form;
	  forms[2]=generators_row_form;
	  forms[3]=translators_row_form;
	  forms[4]=documents_row_form;

        for(formCounter=0;formCounter<num_forms;formCounter++)
	{	
		XtVaGetValues(forms[formCounter],
        	XmNchildren, &children,
		XmNnumChildren, &num_children,
        	NULL);
		XtManageChildren(children,num_children);
        }    	

   /* - not needed */
   /*
       free(display_initialisation_malloc_arr);
   */
       
/***
printf ( " ++++++++++++++++++++++++++++   free ( display_initialisation_malloc_arr )\n\n" ); fflush ( stdout );
***/
    XtManageChild ( main_row_scroll );
    XtManageChild ( provers_row_scroll );
    XtManageChild ( generators_row_scroll );
    XtManageChild ( translators_row_scroll );
    XtManageChild ( documents_row_scroll );
    DisplayCurrWinText ( " done\n");

    DisplayNewEnv ( provers_env );
    DisplayNewEnv ( generators_env );
    DisplayNewEnv ( documents_env );
    DisplayNewEnv ( translators_env );
    DisplayNewEnv ( main_env );

    display_initialisation = 0;

  } /* if ( display_initialisation ) */

  initial_reattachment = 0;
}

/***************************** ReallocPrimaryStringIfReq *********************/

void
ReallocPrimaryStringIfReq ()
{
  int factor = primary_string_len / DisplayTotal;
/***
 printf ( " >>> primary_string_len=%d DisplayTotal=%d factor=%d\n", primary_string_len, DisplayTotal, ( primary_string_len / DisplayTotal ) );
***/
  if ( factor < 50 ) {
    primary_string_len = 100 * DisplayTotal;

    primary_string    = ( char * ) realloc ( ( char * ) primary_string,
                  ( ( primary_string_len + 2 ) * sizeof ( char ) ) );
    if ( primary_string == NULL ) { BT_crash_err_exit ( 2271 ); return; }

    secondary_string  = ( char * ) realloc ( ( char * ) secondary_string,
                  ( ( primary_string_len + 2 ) * sizeof ( char ) ) );
    if ( secondary_string == NULL ) { BT_crash_err_exit ( 2271 ); return; }

    additional_string = ( char * ) realloc ( ( char * ) additional_string,
                  ( ( primary_string_len + 2 ) * sizeof ( char ) ) );
    if ( additional_string == NULL ) { BT_crash_err_exit ( 2271 ); return; }

/***
 printf ( "realloc done\n >>> primary_string_len=%d DisplayTotal=%d factor=%d\n", primary_string_len, DisplayTotal, ( primary_string_len / DisplayTotal ) );
***/
  }
}

/***************************** the Callback *********************/

void
Display_Button_CB ( button, client_data, call_data )
Widget button;
XtPointer client_data;
XtPointer call_data;
{
  XtPointer user_data;
  Pixel lab_col;
  int obj = * ( int * ) client_data;
  void SetDisplay_1_for_obj ();
  void OPN_CLO ();
  void CMT ();
  void ANL ();
  void POG ();
  void ANM ();
  void STS ();
  void RST ();
  void PRV ();
  void PMD ();
  void PPF ();
  void RSL ();
  void LVL ();
  void GBO ();
  void GBM ();
  void ENM ();
  void ITF ();
  void TRL ();
  void LNK ();
  void EXE ();
  void FIN ();
  void TRL_RST ();
  void DMU ();
  void SHW ();
  void PRT ();
  void DOC_RST ();

  int user_data_option;

  XtVaGetValues ( button,
    XmNuserData,   & user_data,
    XmNforeground, & lab_col,
    NULL );

  SetDisplay_1_for_obj ( obj );
  Display_visible = Display_1;
  curr_obj = obj;

  user_data_option = ( * ( int * ) user_data );

  if ( lab_col == inapplicable_lab_col )
  {
    /*if ( ( ( * ( int * ) user_data ) ) != nme_num )*/
    if ( user_data_option != nme_num ) { XBell ( display, -75 ); return; }
  }

  printf("user_data_option = %d\n", user_data_option);
  
  printf("nme_num: %d\n", nme_num);
  printf("cmt_num: %d\n", cmt_num);
  printf("anl_num: %d\n", anl_num);
  printf("pog_num: %d\n", pog_num);

  /*switch ( * ( int * ) user_data ) {*/
  switch ( user_data_option ) {

  case nme_num:
  printf("call OPN_CLO ( %d, %d ) Display_1 = %p\n",obj,Display_1->ps, Display_1);
    OPN_CLO ( obj, Display_1->ps );
    break;

  case cmt_num:
    CMT ( obj );
    break;

  case anl_num:
    ANL ( obj, Display_1->ps );
    break;

  case pog_num:
    POG ( obj, Display_1->ps );
    break;

  case anm_num:
    ANM ( obj );
    break;

  case sts_num:
    STS ( obj );
    break;

  case rst_num:
    RST ( obj );
    break;

  case prv_num:
    PRV ( obj );
    break;

  case pmd_num:
    PMD ( obj );
    break;

  case ppf_num:
    PPF ( obj );
    break;

  case rsl_num:
    RSL ( obj );
    break;

  case lvl_num:
    LVL ( obj );
    break;

  case gbo_num:
    GBO ( obj, Display_1->ps );
    break;

  case gbm_num:
    GBM ( obj, Display_1->ps );
    break;

  case Enm_num:
    ENM ( obj, Display_1->ps );
    break;

  case Itf_num:
    ITF ( obj, Display_1->ps );
    break;

  case gen_rst_num:
    RST ( obj );
    break;

  case trl_num:
    TRL ( obj, Display_1->ps );
    break;

  case lnk_num:
    LNK ( obj, Display_1->ps );
    break;

  case exe_num:
    EXE ( obj, Display_1->ps );
    break;

  case trl_rst_num:
    TRL_RST ( obj );
    break;

  case dmu_num:
    DMU ( obj, Display_1->ps );
    break;

  case shw_num:
    SHW ( obj );
    break;

  case prt_num:
    PRT ( obj );
    break;

  case doc_rst_num:
    DOC_RST ( obj );
    break;

  }
}


/************************ Set*Sensitive/DeSensitive ***********************/

#define SetMainSensitive(b) \
  XtUnmanageChild ( main_row_scroll ); \
  for ( Display_3 = Display_0 ; \
              Display_3 < Display_0 + DisplayTotal ; Display_3++ ) { \
    if ( Display_3->Main_offset != -1 ) { \
      Main_1 = Main_0 + Display_3->Main_offset; \
      XtVaSetValues ( Main_1->cmt, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Main_1->anl, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Main_1->anm, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Main_1->pog, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Main_1->sts, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Main_1->rst, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Main_1->nme, XmNsensitive, b, NULL ); \
    } \
  } \
  XtManageChild ( main_row_scroll )

#define SetProversSensitive(b) \
   XtUnmanageChild ( provers_row_scroll ); \
   for ( Display_3 = Display_0 ; \
              Display_3 < Display_0 + DisplayTotal ; Display_3++ ) { \
    if ( Display_3->Provers_offset != -1 ) { \
      Provers_1 = Provers_0 + Display_3->Provers_offset; \
      XtVaSetValues ( Provers_1->cmt, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Provers_1->prv, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Provers_1->pmd, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Provers_1->ppf, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Provers_1->rsl, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Provers_1->lvl, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Provers_1->nme, XmNsensitive, b, NULL ); \
    } \
  } \
  XtManageChild ( provers_row_scroll )

#define SetGeneratorsSensitive(b) \
   XtUnmanageChild ( generators_row_scroll ); \
   for ( Display_3 = Display_0 ; \
              Display_3 < Display_0 + DisplayTotal ; Display_3++ ) { \
    if ( Display_3->Generators_offset != -1 ) { \
      Generators_1 = Generators_0 + Display_3->Generators_offset; \
      XtVaSetValues ( Generators_1->cmt, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Generators_1->gbo, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Generators_1->gbm, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Generators_1->Enm, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Generators_1->Itf, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Generators_1->rst, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Generators_1->nme, XmNsensitive, b, NULL ); \
    } \
  } \
  XtManageChild ( generators_row_scroll )

#define SetTranslatorsSensitive(b) \
   XtUnmanageChild ( translators_row_scroll ); \
   for ( Display_3 = Display_0 ; \
              Display_3 < Display_0 + DisplayTotal ; Display_3++ ) { \
    if ( Display_3->Translators_offset != -1 ) { \
      Translators_1 = Translators_0 + Display_3->Translators_offset; \
      XtVaSetValues ( Translators_1->cmt, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Translators_1->trl, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Translators_1->lnk, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Translators_1->exe, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Translators_1->rst, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Translators_1->nme, XmNsensitive, b, NULL ); \
    } \
  } \
  XtManageChild ( translators_row_scroll )


#define SetDocumentsSensitive(b) \
   XtUnmanageChild ( documents_row_scroll ); \
   for ( Display_3 = Display_0 ; \
              Display_3 < Display_0 + DisplayTotal ; Display_3++ ) { \
    if ( Display_3->Documents_offset != -1 ) { \
      Documents_1 = Documents_0 + Display_3->Documents_offset; \
      XtVaSetValues ( Documents_1->cmt, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Documents_1->dmu, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Documents_1->shw, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Documents_1->prt, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Documents_1->rst, XmNsensitive, b, NULL ); \
      XtVaSetValues ( Documents_1->nme, XmNsensitive, b, NULL ); \
    } \
  } \
  XtManageChild ( documents_row_scroll )


void
DeSensitizeCurrentEnv ()
{
  switch ( curr_env ) {
  case main_env :
    if ( MainSensitized == 0 ) return;
    SetMainSensitive ( False );
    MainSensitized = 0;
    break;
  case provers_env :
    if ( ProversSensitized == 0 ) return;
    SetProversSensitive ( False );
    ProversSensitized = 0;
    break;
  case generators_env :
    if ( GeneratorsSensitized == 0 ) return;
    SetGeneratorsSensitive ( False );
    GeneratorsSensitized = 0;
    break;
  case translators_env :
    if ( TranslatorsSensitized == 0 ) return;
    SetTranslatorsSensitive ( False );
    TranslatorsSensitized = 0;
    break;
  case documents_env :
    if ( DocumentsSensitized == 0 ) return;
    SetDocumentsSensitive ( False );
    DocumentsSensitized = 0;
    break;
  }
}

void
SensitizeCurrentEnv ()
{
  XtSetSensitive ( InterruptPullDown, False ); 
  XmUpdateDisplay ( InterruptPullDown );
  XmUpdateDisplay ( top_bar );

  switch ( curr_env ) {
  case main_env :
    if ( MainSensitized ) return;
    SetMainSensitive ( True );
    MainSensitized = 1;
    break;
  case provers_env :
    if ( ProversSensitized ) return;
    SetProversSensitive ( True );
    ProversSensitized = 1;
    break;
  case generators_env :
    if ( GeneratorsSensitized ) return;
    SetGeneratorsSensitive ( True );
    GeneratorsSensitized = 1;
    break;
  case translators_env :
    if ( TranslatorsSensitized ) return;
    SetTranslatorsSensitive ( True );
    TranslatorsSensitized = 1;
    break;
  case documents_env :
    if ( DocumentsSensitized ) return;
    SetDocumentsSensitive ( True );
    DocumentsSensitized = 1;
    break;
  }
}

/************************** SensitizeFrame *************************/

void
SensitizeFrame ( bb )
Boolean bb;
{
  int ii;

print_debug(5000001);
  if ( FrameSensitized == bb ) return;

print_debug(5000002);
  FrameSensitized = bb;

print_debug(5000003);
  XtSetSensitive ( UtilsPullDown,     bb );
print_debug(5000004);
  XtSetSensitive ( IntroducePullDown, bb );
print_debug(5000005);
  XtSetSensitive ( ConstructPullDown, bb );

#ifndef HOLLOWAY_FLAG
print_debug(5000006);
  XtSetSensitive ( RemakePullDown,    bb );
#endif

print_debug(5000007);
  XtSetSensitive ( BrowsePullDown,    bb );
print_debug(5000008);
  XtSetSensitive ( OptionsPullDown,   bb );
print_debug(5000009);
print_debug(5000010);

  for ( ii = 0 ; ii < EnvString_tot ; ii++ ) { XtSetSensitive ( env_lab [ ii ], bb ); print_debug(5000000+ii*10+11); }

  switch ( curr_env ) {
  case main_env:
print_debug(6000011);
    XtSetSensitive ( cmt_main_lab, bb );
print_debug(6000012);
    XtSetSensitive ( anl_lab,      bb );
print_debug(6000013);
    XtSetSensitive ( pog_lab,      bb );
print_debug(6000014);
    XtSetSensitive ( anm_lab,      bb );
print_debug(6000015);
    XtSetSensitive ( sts_lab,      bb );
print_debug(6000016);
    XtSetSensitive ( rst_lab,      bb );
print_debug(6000017);
    XtSetSensitive ( edt_main_lab, bb );
print_debug(6000018);
    break;
  case provers_env:
print_debug(6000019);
    XtSetSensitive ( cmt_provers_lab, bb );
print_debug(6000020);
    XtSetSensitive ( prv_lab,         bb );
print_debug(6000021);
    XtSetSensitive ( pmd_lab,         bb );
print_debug(6000022);
    XtSetSensitive ( rsl_lab,         bb );
print_debug(6000023);
    XtSetSensitive ( ppf_lab,         bb );
print_debug(6000024);
    XtSetSensitive ( lvl_lab,         bb );
print_debug(6000025);
    XtSetSensitive ( pob_lab,         bb );
print_debug(6000026);
    XtSetSensitive ( tot_lab,         bb );
print_debug(6000027);
    XtSetSensitive ( edt_provers_lab, bb );
print_debug(6000028);
    break;

  case translators_env:
print_debug(6000029);
    XtSetSensitive ( cmt_translators_lab, bb );
print_debug(6000030);
    XtSetSensitive ( trl_lab,             bb );
print_debug(6000031);
    XtSetSensitive ( lnk_lab,             bb );
print_debug(6000032);
    XtSetSensitive ( exe_lab,             bb );
print_debug(6000033);
    XtSetSensitive ( trl_rst_lab,         bb );
print_debug(6000034);
    XtSetSensitive ( edt_translators_lab, bb );
print_debug(6000035);
    break;
  case generators_env:
print_debug(6000036);
    XtSetSensitive ( cmt_generators_lab, bb );
print_debug(6000037);
    XtSetSensitive ( gbo_lab,            bb );
print_debug(6000038);
    XtSetSensitive ( gbm_lab,            bb );
print_debug(6000039);
    XtSetSensitive ( enm_lab,            bb );
print_debug(6000040);
    XtSetSensitive ( itf_lab,            bb );
print_debug(6000041);
    XtSetSensitive ( gen_rst_lab,        bb );
print_debug(6000042);
    XtSetSensitive ( edt_generators_lab, bb );
print_debug(6000043);
    break;
    case documents_env:
print_debug(6000044);
    XtSetSensitive ( cmt_documents_lab, bb );
print_debug(6000045);
    XtSetSensitive ( dmu_lab,           bb );
print_debug(6000046);
    XtSetSensitive ( shw_lab,           bb );
print_debug(6000047);
    XtSetSensitive ( prt_lab,           bb );
print_debug(6000048);
    XtSetSensitive ( doc_rst_lab,       bb );
print_debug(6000049);
    XtSetSensitive ( edt_documents_lab, bb );
print_debug(6000050);
    break;
  }
}

/***************************** DeSensitize ****************************/

void
DeSensitize ()
{
  SensitizeFrame ( False );
  DeSensitizeCurrentEnv ();
}

/****************************** Sensitize *****************************/

void
Sensitize ()
{
  SensitizeFrame ( True );
  SensitizeCurrentEnv ();
}

/************************** IsDeSensitized *****************************/

int
IsDeSensitized ()
{
  if   ( DeSensitized ) return 1;
  else                  return 0;
}

/*********************** RestoreAnmIprPaneSize **************************/

void
RestoreAnmIprPaneSize ()
{
  XtVaSetValues ( bottom_frame_form,
      XmNpaneMinimum,         bottom_frame_form_height,
      NULL );

  XtManageChild ( bottom_frame_form );

  XtVaSetValues ( bottom_frame_form,
      XmNpaneMinimum,         bottom_frame_form_min,
      NULL );

  XmUpdateDisplay ( bottom_frame_form );
  XmUpdateDisplay ( top_frame_form );
  XmUpdateDisplay ( main_form_pane );
}

void
SetAnmIprPaneSize ()
{
  XtVaGetValues ( bottom_frame_form,
      XmNheight,         & bottom_frame_form_height,
      NULL );

  XtUnmanageChild ( bottom_frame_form );

  XmUpdateDisplay ( bottom_frame_form );
  XmUpdateDisplay ( main_form_pane );
}

/********************** manage_all_env_labels *********************/

#define manage_all_env_labels \
{ \
  int ii; \
  for ( ii = 0 ; ii < EnvString_tot ; ii++ ) { XtManageChild ( env_lab [ ii ] ); } \
  XmUpdateDisplay (  top_frame_form );  \
}

/********************* unmanage_all_env_labels ********************/

#define unmanage_all_env_labels \
{ \
  int ii; \
  for ( ii = 0 ; ii < EnvString_tot ; ii++ ) { XtUnmanageChild ( env_lab [ ii ] ); } \
  XmUpdateDisplay (  top_frame_form );  \
}

/************************** DisplayNewEnv *************************/

void
DisplayNewEnv ( requested_env )
int requested_env;
{
  /***
  1. unmanages *_row_scroll & *_lab_form of curr_env
  2. sets curr_env label to passive
  3. sets new curr_env
  4. sets curr_env label to active
  5. calls DisplayCurrentEnv ()
  ***/

  void DisplayCurrentEnv ();

/***
printf ( "DisplayNewEnv curr_env=%d requested_env=%d\n", curr_env, requested_env );
printf ( "  MasterChanged=%d\n", MasterChanged );
printf ( "  Sensitized=%d\n", Sensitized );
***/

  if ( ( requested_env == curr_env ) && ( Sensitized ) ) return;

/***
printf ( "DisplayNewEnv continuing\n" );
***/

  

  switch ( curr_env ) {                   /* the one to be undisplayed */
    case main_env:
      XtUnmanageChild ( main_lab_form );
      XtUnmanageChild ( main_row_scroll );
      break;
    case provers_env:
      XtUnmanageChild ( provers_lab_form );
      XtUnmanageChild ( provers_row_scroll );
      break;
    case generators_env:
      XtUnmanageChild ( generators_lab_form );
      XtUnmanageChild ( generators_row_scroll );
      break;

    case translators_env:
      XtUnmanageChild ( translators_lab_form );
      XtUnmanageChild ( translators_row_scroll );
      break;

    case documents_env:
      XtUnmanageChild ( documents_lab_form );
      XtUnmanageChild ( documents_row_scroll );
      break;

  case anm_env:
    XtUnmanageChild ( env_lab [ env_str_anm_num ] );
    manage_all_env_labels
    XtUnmanageChild ( constructs_scroll );
    XtUnmanageChild ( constructs_rc );
    XtDestroyWidget ( constructs_rc );
    constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
        xmRowColumnWidgetClass,         constructs_scroll,
        XmNorientation,                 XmVERTICAL,
        XmNmarginWidth,                 18,
        XmNmarginHeight,                10,
        XmNspacing,                     0,
        XmNresizable,                   True,
        NULL );
    RestoreAnmIprPaneSize ();
    break;
  case ipr_pob_env:
  case ipr_lem_env:
    XtUnmanageChild ( env_lab [ env_str_ipr_num ] );
    manage_all_env_labels
    XtUnmanageChild ( constructs_scroll );
    XtUnmanageChild ( constructs_rc );
    XtDestroyWidget ( constructs_rc );
    constructs_rc = XtVaCreateManagedWidget ( "Canvas", 
        xmRowColumnWidgetClass,         constructs_scroll,
        XmNorientation,                 XmVERTICAL,
        XmNmarginWidth,                 18,
        XmNmarginHeight,                10,
        XmNspacing,                     0,
        XmNresizable,                   True,
        NULL );
    RestoreAnmIprPaneSize ();
    break;
  case btl_env:
    XtUnmanageChild ( env_lab [ env_str_btl_num ] );
    manage_all_env_labels
    break;

  } /* switch ( curr_env ) */

  XmUpdateDisplay ( top_frame_form );
  XmUpdateDisplay ( command_bar_rc );
  XmUpdateDisplay ( constructs_form );

  switch ( curr_env ) {                   /* the one to be undisplayed */

  case anm_env:
  case ipr_pob_env:
  case ipr_lem_env:
  case btl_env:
    break;
  default:
/* : set the foreground/background colours  */
      XtVaSetValues ( env_lab [ curr_env ],
    	XmNforeground,    Env_lab_passive,
	XmNbackgroundPixmap,            tabgrey_pixmap,
	NULL);
    break;
  }

  curr_env = requested_env;

  switch ( curr_env ) {                     /* the new env to be displayed */

  case anm_env:
    unmanage_all_env_labels
    XtManageChild ( env_lab [ env_str_anm_num ] );
    break;
  case ipr_pob_env:
  case ipr_lem_env:
    unmanage_all_env_labels
    XtManageChild ( env_lab [ env_str_ipr_num ] );
    break;
  case btl_env:
    unmanage_all_env_labels
    XtManageChild ( env_lab [ env_str_btl_num ] );
    break;
  default:

/* : set the foreground/background colours  */
    XtVaSetValues ( env_lab [ curr_env ],
    	XmNforeground,    Env_lab_active,
	XmNbackgroundPixmap,            tab_pixmap,
	NULL);

    break;

  }

  XmUpdateDisplay ( top_frame_form );

  DisplayCurrentEnv ();
}

/************************** DisplayCurrentEnv **************************/

void
DisplayCurrentEnv ()
{
  /***
  (*_row_scroll & *_lab_form may have been unmanaged)
  1. Calls Sensitize
  2. calls CreHtmlMasterFile if HtmlMasterFileChanged
  3. calls CheckUpdateChangedDisplay_Lnk 
      (checks MasterChanged - calling Allocate/DeAllocate
        as necessary - and then calls DisplayCurrentEnv_continue)
  ***/

  void CheckUpdateChangedDisplay_Lnk ();
  void CreHtmlMasterFile ();

/***
printf ( "DisplayCurrentEnv\n" );
***/

  Sensitize ();
  if ( HtmlMasterFileChanged ) CreHtmlMasterFile ();
  CheckUpdateChangedDisplay_Lnk ();
}

/********************** DisplayCurrentEnv_continue **********************/

void
DisplayCurrentEnv_continue ()  /*** so that .lnk may be correctly established ***/

{
  /***
  called from:
     CheckUpdateChangedDisplay_Lnk ( if ! MasterChanged || no trl imps)
  or
     BMotif_io (BT_QUERY_LNK_M)
  ***/

  void SRC_watch ();

/***
printf ( "DisplayCurrentEnv_continue\n" );
***/

/***
DisplayAndCheckTotals ();
***/

  switch ( curr_env ) {
    case main_env:
      XtManageChild ( main_lab_form );
      XtManageChild ( main_row_scroll );
      break;
    case provers_env:
      XtManageChild ( provers_lab_form );
      XtManageChild ( provers_row_scroll );
      break;
    case generators_env:
      XtManageChild ( generators_lab_form );
      XtManageChild ( generators_row_scroll );
      break;

    case translators_env:
      XtManageChild ( translators_lab_form );
      XtManageChild ( translators_row_scroll );
      break;
    case documents_env:
      XtManageChild ( documents_lab_form );
      XtManageChild ( documents_row_scroll );
      break;
    case anm_env:
      XtManageChild ( constructs_rc );
      XtManageChild ( constructs_scroll );
      SetAnmIprPaneSize ();
      DisplayCurrWinText ( "\nAnimator:\n" );
      break;
    case ipr_pob_env:
    case ipr_lem_env:
      XtManageChild ( constructs_rc );
      XtManageChild ( constructs_scroll );
      SetAnmIprPaneSize ();
      DisplayCurrWinText ( "\nInterProver:\n" );
      break;
    case btl_env:
      break;
  }
  XmUpdateDisplay ( constructs_form );

  FrameSensitized = 1;

/***
printf ( "Display_visible %d   Display_0 %d\n", Display_visible, Display_0 );
***/

  switch ( curr_env ) {
  case main_env:
    if ( ( Display_visible < Display_0 + DisplayTotal ) &&
         ( Display_visible->Main_offset != -1 )          ) {
      Main_1 = Main_0 + Display_visible->Main_offset;
      XmScrollVisible ( main_row_scroll, ( Widget ) Main_1->cmt, 2, 0 );
      XmProcessTraversal ( ( Widget ) Main_1->nme, XmTRAVERSE_CURRENT );
      XmUpdateDisplay ( main_row_scroll );
    }
    break;
  case provers_env:
    if ( ( Display_visible < Display_0 + DisplayTotal ) &&
         ( Display_visible->Provers_offset != -1 )       ) {
      Provers_1 = Provers_0 + Display_visible->Provers_offset;
      XmScrollVisible ( provers_row_scroll, ( Widget ) Provers_1->cmt, 2, 0 );
      XmProcessTraversal ( ( Widget ) Main_1->nme, XmTRAVERSE_CURRENT );
      XmUpdateDisplay ( provers_row_scroll );
   }
    break;
  case generators_env:
    if ( ( Display_visible < Display_0 + DisplayTotal ) &&
         ( Display_visible->Generators_offset != -1 )    ) {
      Generators_1 = Generators_0 + Display_visible->Generators_offset;
      XmScrollVisible ( generators_row_scroll, ( Widget ) Generators_1->cmt, 2, 0 );
      XmProcessTraversal ( ( Widget ) Generators_1->nme, XmTRAVERSE_CURRENT );
      XmUpdateDisplay ( generators_row_scroll );
    }
    break;
  case translators_env:
    if ( ( Display_visible < Display_0 + DisplayTotal ) &&
         ( Display_visible->Translators_offset != -1 )     ) {
      Translators_1 = Translators_0 + Display_visible->Translators_offset;
      XmScrollVisible ( translators_row_scroll, ( Widget ) Translators_1->cmt, 2, 0 );
      XmProcessTraversal ( ( Widget ) Translators_1->nme, XmTRAVERSE_CURRENT );
      XmUpdateDisplay ( translators_row_scroll );
    }
    break;

  case documents_env:
    if ( ( Display_visible < Display_0 + DisplayTotal ) &&
         ( Display_visible->Documents_offset != -1 )       ) {
      Documents_1 = Documents_0 + Display_visible->Documents_offset;
      XmScrollVisible ( documents_row_scroll, ( Widget ) Documents_1->cmt, 2, 0 );
      XmProcessTraversal ( ( Widget ) Documents_1->nme, XmTRAVERSE_CURRENT );
      XmUpdateDisplay ( documents_row_scroll );
    }
    break;

  case anm_env:
  case ipr_pob_env:
  case ipr_lem_env:
  case btl_env:
    break;

  } /* switch ( curr_env ) */

  XmUpdateDisplay ( constructs_form );

  SRC_watch ();
}

/***************************** chk_allocated_and_set *********************/

#define chk_allocated_and_set(o,p,n,m) \
  if ( Display_1->o == -1 ) { \
      p (); \
      Display_1->o = n - m; \
  } \
  n = Display_1->o + m

/**************************** chk_deallocated_and_reset *************************/

#define chk_deallocated_and_reset(o,p,n,m) \
  if ( Display_1->o != -1 ) { \
      n = Display_1->o + m; \
      p (); \
      Display_1->o = -1; \
  }
 
/********************* set_but_applicable/inapplicable *********************/

/* 
#define set_but_applicable(w,t) \
  { \
    if ( Display_1->decoration == decor_SRC_file_newer ) \
      xstr = XmStringCreateLtoR ( applicable_edited_str, charset ); \
    else \
      xstr = XmStringCreateLtoR ( applicable_unedited_str, charset ); \
    XtVaSetValues ( w, \
        XmNforeground,    lab_col_b [ t ], \
        XmNbackground,    lab_col_f [ t ], \
        XmNlabelString,   xstr, \
        NULL ); \
    XmStringFree ( xstr ); \
  }
*/

#define set_but_applicable(w,t) \
  { \
    if ( Display_1->decoration == decor_SRC_file_newer ) \
    { \
      xstr = XmStringCreateLtoR ( applicable_edited_str, charset ); \
    } \
    else \
    { \
      xstr = XmStringCreateLtoR ( applicable_unedited_str, charset ); \
    } \
    XtVaSetValues ( w, \
        XmNforeground,    lab_col_b [ t ], \
        XmNbackground,    lab_col_f [ t ], \
        XmNbackgroundPixmap,     lab_col_pixmap [ t ], \
        XmNlabelString,   xstr, \
        NULL ); \
    XmStringFree ( xstr ); \
  }

#define set_but_inapplicable(w) \
  { \
    xstr = XmStringCreateLtoR ( inapplicable_str, charset ); \
    XtVaSetValues ( w, \
        XmNforeground,    inapplicable_lab_col, \
        XmNbackground,    inapplicable_lab_col, \
        XmNbackgroundPixmap,     inapplicable_pixmap, \
        XmNlabelString,   xstr, \
        NULL ); \
    XmStringFree ( xstr ); \
  }

/************************** set_lvl_but_lab **************************/

void
SetLvlButLab ( ext, lenpob, lpob, fpob )  /* Provers_1 set */
int ext, lenpob, lpob, fpob;
{
  XmString xstr = NULL;

/***
printf ( "SetLvlButLab ( ext=%s lenpob=%d lpob=%d fpob=%d)\n", extens [ ext ], lenpob, lpob, fpob );
***/

  if ( ( ( ext != mch ) && ( ext != ref ) && ( ext != imp ) ) || ( lenpob == 0 ) )
  {
    strcpy ( buf, "          " );
  }
  else
  {
    snprintf ( buf, MAX_buf, "%2d%4d%4d", lenpob - 1, fpob, lpob );
  }
  xstr = XmStringCreateLtoR ( buf, charset );
  XtVaSetValues ( Provers_1->lvl, XmNlabelString, xstr, NULL );
  XmStringFree ( xstr );
}
   
/***************************** SetButtonsInapplicable *********************/

void
SetMainButtonsInapplicable () /* Display_1, Main_1 is set */
{
  XmString  xstr;
/***
printf ( " %s cmt_on_off is %d\n", Display_1->name, Display_1->cmt_on_off );
***/
  if ( Display_1->cmt_on_off == cmt_off ) set_but_inapplicable ( Main_1->cmt );
  set_but_inapplicable ( Main_1->anl );
  set_but_inapplicable ( Main_1->pog );
  set_but_inapplicable ( Main_1->anm );
  set_but_inapplicable ( Main_1->sts );
  set_but_inapplicable ( Main_1->rst );
}

void
SetProversButtonsInapplicable () /* Display_1, Provers_1 is set */
{
  XmString  xstr;
  if ( Display_1->cmt_on_off == cmt_off ) set_but_inapplicable ( Provers_1->cmt );
  set_but_inapplicable ( Provers_1->prv );
  set_but_inapplicable ( Provers_1->pmd );
  set_but_inapplicable ( Provers_1->ppf );
  set_but_inapplicable ( Provers_1->rsl );
}

void
SetGeneratorsButtonsInapplicable () /* Display_1, Generators_1 is set */
{
  XmString  xstr;
  if ( Display_1->cmt_on_off == cmt_off ) set_but_inapplicable ( Generators_1->cmt );
  set_but_inapplicable ( Generators_1->gbo );
  set_but_inapplicable ( Generators_1->gbm );
  set_but_inapplicable ( Generators_1->Enm );
  set_but_inapplicable ( Generators_1->Itf );
  set_but_inapplicable ( Generators_1->rst );
}

void
SetTranslatorsButtonsInapplicable () /* Display_1, Translators_1 is set */
{
  XmString  xstr;
  if ( Display_1->cmt_on_off == cmt_off ) set_but_inapplicable ( Translators_1->cmt );
  set_but_inapplicable ( Translators_1->trl );
  set_but_inapplicable ( Translators_1->lnk );
  set_but_inapplicable ( Translators_1->rst );
  set_but_inapplicable ( Translators_1->exe );
}

void
SetDocumentsButtonsInapplicable () /* Display_1, Documents_1 is set */
{
  XmString  xstr;
  if ( Display_1->cmt_on_off == cmt_off ) set_but_inapplicable ( Documents_1->cmt );
  set_but_inapplicable ( Documents_1->dmu );
  set_but_inapplicable ( Documents_1->shw );
  set_but_inapplicable ( Documents_1->prt );
  set_but_inapplicable ( Documents_1->rst );
}


/******************************* SetButtonState *******************************/

void
SetButtonState ( obj, lnk_flag ) /*** Display_1 is set ***/
int obj, lnk_flag;
{
  /***
  all _on are set except for lnk;
  if an imp (obj) if translated but not linked:
      if ( lnk_flag ):   (from CheckUpdateChangedDisplay_Lnk)
         added to igset1
      if ( ! lnk_flag ): (from CheckUpdateChangedDisplay_NoLnk)
         Display_1->changed is set (back) to 1;
         MasterChanged is set (back) to 1
  ***/

  int ext, type;
  /*int hidden = 0;*/ /* not used ? */
  int anl, dmu, trl, lnk, lenpob, fpob, cpt, fpobI, ppob, lpob;
  int gen1, gen2;
  int st, is_generated, is_gen_by, is_prf, prf_level, ppf_card;
  int rr;
  XmString  xstr;
  void AllocateMain ();
  void AllocateProvers ();
  void DeAllocateProvers ();
  void AllocateGenerators ();
  void AllocateTranslators ();
  void DeAllocateTranslators ();
  void AllocateDocuments ();
  void DeAllocateDocuments ();
  void Colour_name ();

/***
printf ( "  SetButtonState ( obj=%d(%s), lnk_flag=%d display_initialisation=%d)\n", ob
j, GetName(obj), lnk_flag, display_initialisation ); fflush ( stdout );
***/

  Display_1->changed = 0;

  val_ext ( &ext, obj );
  val_type ( &type, obj );
  val_opt ( &is_generated, &is_gen_by, &is_prf, &prf_level, obj );

  if ( hid_LIB_flag ) {
    if ( ( type == lib ) || ( type == lib_vhdl ) ) return;
  }
  if ( hid_gen_flag ) {
    if ( ( type == bse_gen ) || ( type == enm_gen ) ||
         ( type == itf_gen ) || ( type == prf_gen ) || ( type == gen_vhdl ) )  return;
  }

  switch ( ext ) {

  case mch:
  case ref:
  case imp:

    chk_allocated_and_set ( Main_offset, AllocateMain, Main_1, Main_0 );
    SetMainButtonsInapplicable ();
    val_curMRI ( &anl, &dmu, &trl, &lnk, &lenpob, &fpob, &ppob, &lpob, obj );
    lpob = correct_pob_for_btl ( lpob );
    fpob = correct_pob_for_btl ( fpob );
    val_cptMRIState ( &cpt, obj );
    valIth_pob ( &fpobI, cpt, lenpob );
    fpobI = correct_pob_for_btl ( fpobI );
    set_but_applicable ( Main_1->sts, Display_1->type );
    if ( anl == 0 ) {
      set_but_applicable ( Main_1->anl, Display_1->type );
      set_but_applicable ( Main_1->pog, Display_1->type );
      if ( display_initialisation == 0 ) {
        chk_deallocated_and_reset ( Provers_offset, DeAllocateProvers,
                                                      Provers_1, Provers_0 );
        chk_deallocated_and_reset ( Documents_offset, DeAllocateDocuments,
                                                      Documents_1, Documents_0 );
        if ( ext == imp ) {
          chk_deallocated_and_reset ( Translators_offset, DeAllocateTranslators,
                                                      Translators_1, Translators_0 );
	}
      }
    }
    else { /* anl */
      if ( ( ext == mch ) /* || ( ext == ref ) */ ) {
        set_but_applicable ( Main_1->anm, Display_1->type );
      }
      if ( ( Display_1->type == usr )      ||
           ( Display_1->type == usr_vhdl )    ) {
        set_but_applicable ( Main_1->rst, Display_1->type );
        if ( lenpob == 0 ) {
          set_but_applicable ( Main_1->pog, Display_1->type );
	}
        else {
          chk_allocated_and_set ( Provers_offset, AllocateProvers,
                                                            Provers_1, Provers_0 );
          SetProversButtonsInapplicable ();
          SetLvlButLab ( ext, lenpob, lpob, fpobI );
          val_curMRIState ( &st, obj );
          card_ppf ( &ppf_card, st );
          set_but_applicable ( Provers_1->pmd, Display_1->type );   /* moved    */
          if ( lpob ) {
            set_but_applicable ( Provers_1->prv, Display_1->type ); /* from here */
	  }
          if ( ( fpob !=0 ) && ( lenpob != ppf_card ) ) {
            set_but_applicable ( Provers_1->ppf, Display_1->type );
	  }
          if ( lenpob > 1 ) {
            set_but_applicable ( Provers_1->rsl, Display_1->type );
	  }
	}
      }

      chk_allocated_and_set ( Documents_offset, AllocateDocuments,
                                                        Documents_1, Documents_0 );
      SetDocumentsButtonsInapplicable ();
      if ( dmu ) {
        set_but_applicable ( Documents_1->shw, Display_1->type );
        set_but_applicable ( Documents_1->prt, Display_1->type );
        set_but_applicable ( Documents_1->rst, Display_1->type );
      }
      else {
        set_but_applicable ( Documents_1->dmu, Display_1->type );
      }
/***
printf ( "1 %s\n", GetName ( obj ) ); fflush ( stdout );
***/
      if ( ext == imp ) {
/***
printf ( "2 %s\n", GetName ( obj ) ); fflush ( stdout );
***/
        chk_allocated_and_set ( Translators_offset, AllocateTranslators,
                                                        Translators_1, Translators_0 );
        SetTranslatorsButtonsInapplicable ();
        if ( trl == 0 ) {
/***
printf ( "3 %s\n", GetName ( obj ) ); fflush ( stdout );
***/
          set_but_applicable ( Translators_1->trl, Display_1->type );
        }
        else { /* trl */
          set_but_applicable ( Translators_1->rst, Display_1->type );
/***
printf ( "4 %s\n", GetName ( obj ) ); fflush ( stdout );
***/
           if ( lnk == 0 ) {
            if ( lnk_flag ) {
/***
printf ( "5 %s\n", GetName ( obj ) ); fflush ( stdout );
***/
              add_gset1 ( &rr, obj );
/***
printf ( "  +>+>+>+>+>+>+>+> add_gset1 %s for BT_QUERY_LNK\n", GetName ( obj ) ); fflush ( stdout );
***/
              chk_rep ( rr, 236 );
            }
            else {
              Display_1->changed = 1;
              MasterChanged = 1;
	    }
          }  /* lnk */
          else {
            set_but_applicable ( Translators_1->exe, Display_1->type );
	  }
	}
      }
    } /* else ( so, anl ) */


    break;

  case mch_prf:
  case ref_prf:
  case imp_prf:

    chk_allocated_and_set ( Provers_offset, AllocateProvers
                                                        , Provers_1, Provers_0 );
    SetProversButtonsInapplicable ();
    SetLvlButLab ( ext, 0, 0, 0 );
    chk_allocated_and_set ( Documents_offset, AllocateDocuments,
                                                          Documents_1, Documents_0 );
    SetDocumentsButtonsInapplicable ();
    val_curMRIState ( &st, is_gen_by );
    member_ppf_dmu ( &dmu, st, prf_level );
    if ( dmu ) {
        set_but_applicable ( Documents_1->shw, Display_1->type );
        set_but_applicable ( Documents_1->prt, Display_1->type );
        set_but_applicable ( Documents_1->rst, Display_1->type );
    }
    else {
        set_but_applicable ( Documents_1->dmu, Display_1->type );
    }
    break;

  case bse:
  case enm:
  case itf:


    chk_allocated_and_set ( Generators_offset, AllocateGenerators,
                                                    Generators_1, Generators_0 );
    SetGeneratorsButtonsInapplicable ();

    val_curGEN ( &gen1, &gen2, &dmu, obj );
    if ( gen1 ) {


      set_but_applicable ( Generators_1->rst, Display_1->type );

      chk_allocated_and_set ( Documents_offset, AllocateDocuments,
                                                          Documents_1, Documents_0 );
      SetDocumentsButtonsInapplicable ();
      if ( dmu ) {
          set_but_applicable ( Documents_1->shw, Display_1->type );
          set_but_applicable ( Documents_1->prt, Display_1->type );
          set_but_applicable ( Documents_1->rst, Display_1->type );
      }
      else {
          set_but_applicable ( Documents_1->dmu, Display_1->type );
      }
      if ( ext == bse ) {
        if ( gen2 == 0 ) {
          set_but_applicable ( Generators_1->gbm, Display_1->type );
	}
      }
      else if ( ext == itf ) {
        if ( gen2 !=0 ) {
          chk_allocated_and_set ( Translators_offset, AllocateTranslators,
                                                    Translators_1, Translators_0 );
          SetTranslatorsButtonsInapplicable ();
          set_but_applicable ( Translators_1->exe, Display_1->type );
          set_but_applicable ( Translators_1->rst, Display_1->type );
	}
      }
    }
    else {  /* ! gen1 */
      if ( display_initialisation == 0 ) {
        chk_deallocated_and_reset ( Documents_offset, DeAllocateDocuments,
                                                      Documents_1, Documents_0 );
      }
      switch ( ext ) {
      case bse:
        set_but_applicable ( Generators_1->gbo, Display_1->type );
        break;
      case enm:

      set_but_applicable ( Generators_1->Enm, Display_1->type );

        break;

      case itf:
        set_but_applicable ( Generators_1->Itf, Display_1->type );
        if ( display_initialisation == 0 ) {
          chk_deallocated_and_reset ( Translators_offset, DeAllocateTranslators,
                                                    Translators_1, Translators_0 );
	}
        break;
      }
    }
    break;

  case ops:

    chk_allocated_and_set ( Generators_offset, AllocateGenerators,
                                                  Generators_1, Generators_0 );
    SetGeneratorsButtonsInapplicable ();
    break;

  case doc:

    chk_allocated_and_set ( Documents_offset, AllocateDocuments,
                                                          Documents_1, Documents_0 );
    SetDocumentsButtonsInapplicable ();
    val_curMRIState ( &st, obj );
    val_dmu ( &dmu, st );
    if ( dmu ) {
        set_but_applicable ( Documents_1->shw, Display_1->type );
        set_but_applicable ( Documents_1->prt, Display_1->type );
        set_but_applicable ( Documents_1->rst, Display_1->type );
    }
    else {
        set_but_applicable ( Documents_1->dmu, Display_1->type );
    }
    break;

  } /* switch ( ext ) */

  Colour_name ();

/***
printf ( "  SetButtonState done\n" ); fflush ( stdout );
***/
}

/******************* CheckUpdateChangedDisplay_NoLnk *********************/

void
CheckUpdateChangedDisplay_NoLnk ()
{
  /***
  if MasterChanged set:
    calls Save_CfgDepBase;
    iterates through Display;
    if changed field set to 1: calls SetButtonState ( lnk_flag = 0 )
    if changed field set to 2: removes Display
    (MasterChanged is set whenever a changed field of a Display is set)
    gset1 is ignored (see CheckUpdateChangedDisplay_Lnk)
    MasterChanged is reset
    ***** DisplayCurrentEnv_continue is NOT called *****
 ***/

  int remove_reqd;
  void DeAllocateMain ();
  void DeAllocateProvers ();
  void DeAllocateGenerators ();
  void DeAllocateTranslators ();
  void DeAllocateDocuments ();
  void DisplayRemove ();
  void SetDisplay_1_for_obj ();
  void DisplayCurrWinTextAt ();

  remove_reqd = 0;
  clear_gset1 ();

/***
printf ( " ++ CheckUpdateChangedDisplay_NoLnk: MasterChanged=%d\n", MasterChanged ); fflush ( stdout );
***/

  if ( MasterChanged == 0 ) return;

  Save_CfgDepBase ();

  MasterChanged = 0;

  for ( Display_3 = Display_0 ;
              Display_3 < Display_0 + DisplayTotal ; Display_3++ ) {
    if ( Display_3->changed == 1 ) {          /* construct changed */
/*
      if ( display_initialisation ) {
       DisplayCurrWinText ( ".");
      }
*/
/***
printf ( "        **** changing %s %d\n", Display_1->name, up_and_running );fflush ( stdout );
***/
      Display_1 = Display_3;
      SetButtonState ( Display_1->obj, /* lnk_flag = */ 0 );
    }
/***
else { printf ( "%s hasn't changed\n", Display_1->name ); } fflush ( stdout );
***/
  }
  Reset_display_initialisation ();
}

/******************* CheckUpdateChangedDisplay_Lnk *********************/

void
CheckUpdateChangedDisplay_Lnk ()
{
  /***
  if MasterChanged set:
    calls Save_CfgDepBase;
    iterates through Display;
    if changed field set to 1: calls SetButtonState ( lnk_flag = 1 )
    if changed field set to 2: removes Display
    MasterChanged is reset
    (MasterChanged is set whenever a changed field of a Display is set)
    gset1 will contains all .imps which may be linkable (BT_QUERY_LINK)
    which will have ben set in SetButtonState
    if gset1 non empty &&  ! auto_reset_and_remake && ! upgrade3T04_flag
      InvokeB BT_QUERY_LNK (->BT_QUERY_LNK_M->DisplayCurrentEnv_continue )
    else
      DisplayCurrentEnv_continue
  ***/

  int remove_reqd;
  int nn, obj;
  void DeAllocateMain ();
  void DeAllocateProvers ();
  void DeAllocateGenerators ();
  void DeAllocateTranslators ();
  void DeAllocateDocuments ();
  void DisplayRemove ();
  void SetDisplay_1_for_obj ();
  void DisplayCurrentEnv_continue ();
  void DisplayCurrWinTextAt ();

  remove_reqd = 0;
  clear_gset1 (); /* to be loaded in SetButtonState */

/***
printf ( " ++ CheckUpdateChangedDisplay_Lnk: MasterChanged=%d\n", MasterChanged );fflush ( stdout );
***/

  if ( MasterChanged == 0 ) {
    DisplayCurrentEnv_continue ();
    return;
  }

  Save_CfgDepBase ();

  MasterChanged = 0;

  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( Display_1->changed == 1 ) {          /* construct changed */
/*
      if ( display_initialisation ) {
        DisplayCurrWinText ( ".");
      }
*/
/***
printf ( "        **** changing %s\n", Display_1->name ); fflush ( stdout );
***/
      SetButtonState ( Display_1->obj, /* lnk_flag = */ 1 );
    }
/***
else { printf ( "%s hasn't changed\n", Display_1->name ); } fflush ( stdout );
***/
  }

  Reset_display_initialisation ();
  /***
   gset1 contains all .imps which may be linkable 
  (loaded in SetButtonState)
  ***/
  card_gset1 ( &nn );
  if ( ( auto_reset_and_remake == 0 ) && 
       ( upgrade3T04_flag == 0 )      &&
       ( nn != 0 )                         ) {
    strcpy ( fifo_write_buf, "(?" );
    while ( nn ) {
      valOrd_gset1 ( &obj, nn );
      SetDisplay_1_for_obj ( obj );
      strcat ( fifo_write_buf, "," );
      strcat ( fifo_write_buf, Display_1->name );
      nn--;
    }
    snprintf ( buf, MAX_buf, "):%d", BT_QUERY_LNK );
    strcat ( fifo_write_buf, buf );
    Cre_tcp_env ();
    InvokeB ( without_XTerm, 0 );
  }
  else { /* no suitable trl */
    DisplayCurrentEnv_continue ();
  }
}

/**************************** set_name_col *****************************/

#define set_name_col(o,n,m) \
  if ( Display_1->o != -1 ) { \
    n = m + Display_1->o; \
    XtVaSetValues ( ( Widget ) n->nme, XmNforeground, fg, XmNbackground, bg, NULL ); \
    XmUpdateDisplay ( ( Widget ) n->nme ); \
  }

/**************************** Colour_name *****************************/

void
Colour_name () /* Display_1 set */
{
  Pixel fg, bg;

  if ( Display_1->ps ) {
    fg = lab_col_b [ Display_1->type ];
    bg = lab_col_f [ Display_1->type ];
  }
  else {
    fg = lab_col_f [ Display_1->type ];
    bg = lab_col_b [ Display_1->type ];
  }

  set_name_col ( Main_offset, Main_1, Main_0 );
  set_name_col ( Provers_offset, Provers_1, Provers_0 );
  set_name_col ( Generators_offset, Generators_1, Generators_0 );
  set_name_col ( Translators_offset, Translators_1, Translators_0 );
  set_name_col ( Documents_offset, Documents_1, Documents_0 );

}

/**************************** set_name_col *****************************/

#define set_cmt_col(o,n,m) \
  if ( Display_1->o != -1 ) { \
    n = m + Display_1->o; \
    XtVaSetValues ( ( Widget ) n->cmt, XmNforeground, fg, XmNbackground, bg, NULL ); \
    XmUpdateDisplay ( ( Widget ) n->cmt ); \
  }

/* - reuse set_but_applicable(w,t) */
/* - reuse set_but_inapplicable(w) */

#define set_cmt_col_applicable(o,n,m) \
  if ( Display_1->o != -1 ) { \
    n = m + Display_1->o; \
    set_but_applicable(( Widget ) n->cmt,Display_1->type); \
    XmUpdateDisplay ( ( Widget ) n->cmt ); \
  }

#define set_cmt_col_inapplicable(o,n,m) \
  if ( Display_1->o != -1 ) { \
    n = m + Display_1->o; \
    set_but_inapplicable(( Widget ) n->cmt); \
    XmUpdateDisplay ( ( Widget ) n->cmt ); \
  }

/****************** Change*ButDecorationAndCmtApplicablity *******************/

void
ChangeMainButDecorationAndCmtApplicablity ( str )  /* Display_1/Main_1 is set */
char * str;
{
  Pixel fg, bg;
  XmString xstr = XmStringCreateLtoR ( str, charset );
  XtVaSetValues ( ( Widget ) Main_1->cmt, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Main_1->anl, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Main_1->pog, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Main_1->anm, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Main_1->sts, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Main_1->rst, XmNlabelString, xstr, NULL );
  XmUpdateDisplay ( ( Widget ) Main_1->row );
/*  if ( Display_1->ps ) { */
    if ( str [ 0 ] == applicable_edited_chr ) {
      /* - reuse existing defined macro
      fg = lab_col_b [ Display_1->type ];
      bg = lab_col_f [ Display_1->type ];
      */
      set_cmt_col_applicable ( Main_offset, Main_1, Main_0 );
    }
    else {
      fg = inapplicable_lab_col;
      bg = inapplicable_lab_col;
      set_cmt_col_inapplicable (Main_offset, Main_1, Main_0 );
    }
    /* set_cmt_col ( Main_offset, Main_1, Main_0 );*/
/*  } */
  XmStringFree ( xstr );
}

void
ChangeProversButDecorationAndCmtApplicablity ( str )  /* Provers_1 is set */
char * str;
{
  Pixel fg, bg;
  XmString  xstr = XmStringCreateLtoR ( str, charset );
  XtVaSetValues ( ( Widget ) Provers_1->cmt, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Provers_1->prv, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Provers_1->pmd, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Provers_1->ppf, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Provers_1->rsl, XmNlabelString, xstr, NULL );
  XmUpdateDisplay ( ( Widget ) Provers_1->row );
/*  if ( Display_1->ps ) { */
    if ( str [ 0 ] == applicable_edited_chr ) {
      /*
      fg = lab_col_b [ Display_1->type ];
      bg = lab_col_f [ Display_1->type ];
      */
      set_cmt_col_applicable ( Provers_offset, Provers_1, Provers_0 );
    }
    else {
     /*
      fg = inapplicable_lab_col;
      bg = inapplicable_lab_col;
      */
      set_cmt_col_inapplicable ( Provers_offset, Provers_1, Provers_0 );
    }
    /*set_cmt_col ( Provers_offset, Provers_1, Provers_0 );*/
/*  } */

  /**  gdb records a double free here? why? **/
  XmStringFree ( xstr );
}

void
ChangeGeneratorsButDecorationAndCmtApplicablity ( str )  /* Generators_1 is set */
char * str;
{
  Pixel fg, bg;
  XmString  xstr = XmStringCreateLtoR ( str, charset );
  XtVaSetValues ( ( Widget ) Generators_1->cmt, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Generators_1->gbo, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Generators_1->gbm, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Generators_1->Enm, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Generators_1->Itf, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Generators_1->rst, XmNlabelString, xstr, NULL );
  XmUpdateDisplay ( ( Widget ) Generators_1->row );
/*  if ( Display_1->ps ) { */
    if ( str [ 0 ] == applicable_edited_chr ) {
      /*
      fg = lab_col_b [ Display_1->type ];
      bg = lab_col_f [ Display_1->type ];
      */
      set_cmt_col_applicable ( Generators_offset, Generators_1, Generators_0 );
    }
    else {
      /*
      fg = inapplicable_lab_col;
      bg = inapplicable_lab_col;
      */
      set_cmt_col_inapplicable ( Generators_offset, Generators_1, Generators_0 );
    }
    /*
    set_cmt_col ( Generators_offset, Generators_1, Generators_0 );
    */
/*  } */
  XmStringFree ( xstr );
}

void
ChangeTranslatorsButDecorationAndCmtApplicablity ( str )  /* Translators_1 is set */
char * str;
{
  Pixel fg, bg;
  XmString  xstr = XmStringCreateLtoR ( str, charset );
  XtVaSetValues ( ( Widget ) Translators_1->cmt, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Translators_1->trl, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Translators_1->lnk, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Translators_1->exe, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Translators_1->rst, XmNlabelString, xstr, NULL );
  XmUpdateDisplay ( ( Widget ) Translators_1->row );
/*  if ( Display_1->ps ) { */
    if ( str [ 0 ] == applicable_edited_chr ) {
      /*
      fg = lab_col_b [ Display_1->type ];
      bg = lab_col_f [ Display_1->type ];
      */
      set_cmt_col_applicable ( Translators_offset, Translators_1, Translators_0 );
    }
    else {
      /*
      fg = inapplicable_lab_col;
      bg = inapplicable_lab_col;
      */
      set_cmt_col_inapplicable ( Translators_offset, Translators_1, Translators_0 );
    }
    /*
    set_cmt_col ( Translators_offset, Translators_1, Translators_0 );
    */
/*  } */
  XmStringFree ( xstr );
}

void
ChangeDocumentsButDecorationAndCmtApplicablity ( str )  /* Documents_1 is set */
char * str;
{
  Pixel fg, bg;
  XmString  xstr = XmStringCreateLtoR ( str, charset );
  XtVaSetValues ( ( Widget ) Documents_1->cmt, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Documents_1->dmu, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Documents_1->shw, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Documents_1->prt, XmNlabelString, xstr, NULL );
  XtVaSetValues ( ( Widget ) Documents_1->rst, XmNlabelString, xstr, NULL );
  XmUpdateDisplay ( ( Widget ) Documents_1->row );
/*  if ( Display_1->ps ) { */
    if ( str [ 0 ] == applicable_edited_chr ) {
      /*
      fg = lab_col_b [ Display_1->type ];
      bg = lab_col_f [ Display_1->type ];
      */
      set_cmt_col_applicable ( Documents_offset, Documents_1, Documents_0 );
    }
    else {
      /*
      fg = inapplicable_lab_col;
      bg = inapplicable_lab_col;
      */
      set_cmt_col_inapplicable ( Documents_offset, Documents_1, Documents_0 );
    }
    /*set_cmt_col ( Documents_offset, Documents_1, Documents_0 );*/
/*  } */
  XmStringFree ( xstr );
}

/***************** ChangeAllButDecorationAndCmtApplicablity ******************/

ChangeAllButDecorationAndCmtApplicablity ( str )  /* Display_1 is set */
char * str;
{
  /***
  called by (Un)Decorate_SRC_file_newer
  ***/

/***
printf ( "----------->>> ChangeAllButDecorationAndCmtApplicablity ( %s->%s )\n",
                                                                        Display_1->name, str );
***/

  if ( Display_1->Main_offset != -1 ) {
    Main_1 = Main_0 + Display_1->Main_offset;
    ChangeMainButDecorationAndCmtApplicablity ( str );
  }
  if ( Display_1->Provers_offset != -1 ) {
    Provers_1 = Provers_0 + Display_1->Provers_offset;
    ChangeProversButDecorationAndCmtApplicablity ( str );
  }
  if ( Display_1->Generators_offset != -1 ) {
    Generators_1 = Generators_0 + Display_1->Generators_offset;
    ChangeGeneratorsButDecorationAndCmtApplicablity ( str );
  }
  if ( Display_1->Translators_offset != -1 ) {
    Translators_1 = Translators_0 + Display_1->Translators_offset;
    ChangeTranslatorsButDecorationAndCmtApplicablity ( str );
  }
  if ( Display_1->Documents_offset != -1 ) {
    Documents_1 = Documents_0 + Display_1->Documents_offset;
    ChangeDocumentsButDecorationAndCmtApplicablity ( str );
  }

}

/************************* Decorate_SRC_file_newer **************************/
/*
void
Decorate_SRC_file_newer ( obj )
int obj;
{
  void SetDisplay_1_for_obj ();

  SetDisplay_1_for_obj ( obj );

/???
printf ( "Decorate_SRC_file_newer %s Display_1->cmt_on_off=%d\n",
                                         Display_1->name, Display_1->cmt_on_off );
???/
  if ( Display_1->decoration == undecor_SRC_file_newer ) {

    /???
    row currently wrongly decorated
    if open set cmt_on_off to cmt_on else set to cmt_off
    ???/
    Display_1->decoration = decor_SRC_file_newer;
    if ( Display_1->ps ) {
      Display_1->cmt_on_off = cmt_on;
/???
printf ( "        %s >>>just opened<<< Decorate_SRC_file_newe\n", Display_1->name );
???/
    }
    else {
/???
printf ( "        %s >>>just closed<<< Decorate_SRC_file_newer\n", Display_1->name );
???/
      Display_1->cmt_on_off = cmt_off;
    }
    ChangeAllButDecorationAndCmtApplicablity ( applicable_edited_str );
  }

  else {

    /???
    row currently correctly decorated 
    check cmt_on_off set to cmt_on if open, cmt_off if closed
    ???/
    if ( Display_1->ps ) {
      if ( Display_1->cmt_on_off == cmt_off ) {
        Display_1->cmt_on_off = cmt_on;
/???
printf ( "        %s >>>just opened<<< Decorate_SRC_file_newer\n", Display_1->name );
???/
        ChangeAllButDecorationAndCmtApplicablity ( applicable_edited_str );
      }
    }
    else { /? ! Display_1->ps ?/
      if ( Display_1->cmt_on_off == cmt_on ) {
        Display_1->cmt_on_off = cmt_off;
/???
printf ( "        %s >>>just closed<<< Decorate_SRC_file_newer\n", Display_1->name );
???/
        ChangeAllButDecorationAndCmtApplicablity ( applicable_edited_str );
      }
    }
  }
}
*/
void
Decorate_SRC_file_newer ( obj )
int obj;
{
  void SetDisplay_1_for_obj ();

  SetDisplay_1_for_obj ( obj );

/***
printf ( "Decorate_SRC_file_newer %s Display_1->cmt_on_off=%d\n",
                                         Display_1->name, Display_1->cmt_on_off );
***/
  if ( Display_1->decoration == undecor_SRC_file_newer ) {
    /***
    row currently wrongly decorated  - set cmt_on_off set to cmt_on
    ***/
/***
printf ( "Decorate_SRC_file_newer: row currently wrongly decorated\n" );
***/
    Display_1->decoration = decor_SRC_file_newer;
    Display_1->cmt_on_off = cmt_on;
    ChangeAllButDecorationAndCmtApplicablity ( applicable_edited_str );
  }

  else {
    /***
    row currently correctly decorated - check cmt_on_off set to cmt_on
    ***/
/***
printf ( "Decorate_SRC_file_newer: row currently correctly decorated\n" );
***/
    if ( Display_1->cmt_on_off == cmt_off ) {
      Display_1->cmt_on_off = cmt_on;
/***
printf ( "Decorate_SRC_file_newer: Display_1->cmt_on_off == cmt_off\n" );
***/
      ChangeAllButDecorationAndCmtApplicablity ( applicable_edited_str );
    }
  }
}

/********************** UnDecorate_SRC_file_newer ***********************/
/*
void
UnDecorate_SRC_file_newer ( obj )
int obj;
{
  void SetDisplay_1_for_obj ();

  SetDisplay_1_for_obj ( obj );

/???
printf ( "UnDecorate_SRC_file_newer %s Display_1->cmt_on_off=%d\n",
                                         Display_1->name, Display_1->cmt_on_off );
???/
  if ( Display_1->decoration == decor_SRC_file_newer ) {

    /???
    row currently wrongly decorated
    ???/
    Display_1->decoration = undecor_SRC_file_newer;
/???
printf ( "        %s >>>just de-edited<<< UnDecorate_SRC_file_newe\n", Display_1->name );
???/
    Display_1->cmt_on_off = cmt_off;
    ChangeAllButDecorationAndCmtApplicablity ( applicable_unedited_str );
  }

  else {

    /???
    row currently correctly decorated - check cmt_on_off set to cmt_off
    ???/
    if ( Display_1->cmt_on_off == cmt_on ) {
      if ( Display_1->cmt_on_off == cmt_on ) {
        Display_1->cmt_on_off = cmt_off;
/???
printf ( "        %s >>>???<<< UnDecorate_SRC_file_newer\n", Display_1->name );
???/
       ChangeAllButDecorationAndCmtApplicablity ( applicable_unedited_str );
      }
    }
  }
}
*/
void
UnDecorate_SRC_file_newer ( obj )
int obj;
{
  void SetDisplay_1_for_obj ();

  SetDisplay_1_for_obj ( obj );

/***
printf ( "UnDecorate_SRC_file_newer %s Display_1->cmt_on_off=%d\n",
                                         Display_1->name, Display_1->cmt_on_off );
***/
  if ( Display_1->decoration == decor_SRC_file_newer ) {
    /***
    row currently wrongly decorated - set cmt_on_off set to cmt_off
    ***/
    Display_1->decoration = undecor_SRC_file_newer;
    Display_1->cmt_on_off = cmt_off;
    ChangeAllButDecorationAndCmtApplicablity ( applicable_unedited_str );
  }
  else {
    /***
    row currently correctly decorated  - check cmt_on_off set to cmt_off
    ***/
    if ( Display_1->cmt_on_off == cmt_on ) {
      Display_1->cmt_on_off = cmt_off;
      ChangeAllButDecorationAndCmtApplicablity ( applicable_unedited_str );
    }
  }
}

/*************************** SetDisplay_visible ****************************/
void
SetDisplay_visible ( obj )
int obj;
{
  int type;
  void SetDisplay_1_for_obj ();

  if ( hid_LIB_flag ) {
    val_type ( &type, obj );
    if ( ( type == lib ) || ( type == lib_vhdl ) ) return;
  }
  if ( hid_gen_flag ) {
    val_type ( &type, obj );
    if ( ( type == bse_gen ) || ( type == enm_gen ) ||
         ( type == itf_gen ) || ( type == prf_gen ) || ( type == gen_vhdl ) )  return;
  }
  
  SetDisplay_1_for_obj ( obj );
  Display_visible = Display_1;
}

/**************************** create name button in row *************************/

Widget
CreNameButton ( row, but_num, type, bb ) /*** Display_1 is set ***/
Widget row;
int but_num, type;
Boolean bb;
{
  /***
  Display_1 is a pointer to a Display structure, row is the field of
  the _row structure to which Display_1->main/provers/... points.
  The button is created and stored in the _row structure,
  XmNuserData the (pointer) is set to the c_arr [ `but_no' ];
  the Callback is also set;
  XmNsensitive is set according to bb;
  the button is returned.
  ***/

  Widget but;
  void Display_Button_CB ();
  XmString xstr = XmStringCreateLtoR ( Display_1->name, charset );

/***
printf ( "CreNameButton ( row=%d but_num=%d type=%d)\n", row, but_num, type );
***/

  but = XtVaCreateManagedWidget ( lab_types [ type ],
      xmPushButtonWidgetClass, row,
      XmNlabelString,          xstr,
      XmNshadowThickness,      0,      
      XmNnavigationType,       XmTAB_GROUP,
      XmNhighlightThickness,   /* 1,*/ 0,
      XmNuserData,             ( XtPointer ) & c_arr [ nme_num ],
/*
      XmNforeground,           lab_col_b [ Display_1->type ],
      XmNbackground,           lab_col_f [ Display_1->type ], 
*/      
      XmNborderWidth,          0, /* */
      XmNsensitive,            bb,
      NULL );
  XmStringFree ( xstr );

  XtAddCallback ( but, XmNactivateCallback,
     ( XtCallbackProc ) Display_Button_CB,
     ( XtPointer ) & c_arr [ Display_1->obj ] );

  return ( but );
}

/**************************** create lvl button in row *************************/

Widget
CreLvlButton ( row, but_num, type, bb ) /*** Display_1 is set ***/
Widget row;
int but_num, type;
Boolean bb;
{
  /***
  Display_1 is a pointer to a Display structure, row is the field of
  the _row structure to which Display_1->main/provers/... points.
  The button is created and stored in the _row structure,
  XmNuserData the (pointer) is set to the c_arr [ `but_no' ];
  the Callback is also set;
  XmNsensitive is set according to bb;
  the button is returned.
  ***/

  Widget but;
  void Display_Button_CB ();
  XmString xstr = XmStringCreateLtoR ( "          ", charset );

/***
printf ( "CreNameButton ( but=%d row=%d but_num=%d type=%d)\n", but, row, but_num, type ); fflush ( stdout );
***/

  but = XtVaCreateManagedWidget ( lab_types [ type ], 
      xmPushButtonWidgetClass, row,
      XmNlabelString,          xstr,
      XmNrecomputeSize,        False,
      XmNheight,               10,
      XmNwidth,                /*92,*/ 88,
      XmNnavigationType,       XmTAB_GROUP,
      XmNborderWidth,          /* 1,*/ 0,
      XmNmarginWidth,          /* 2,*/ 0,
      XmNdefaultButtonShadowThickness,  0,
      XmNshadowThickness,      /* 2,*/ 1,
      XmNhighlightThickness,   /* 1,*/ 1,
      XmNuserData,             ( XtPointer ) & c_arr [ lvl_num ],
/*
      XmNforeground,           lab_col_b [ Display_1->type ], 
      XmNbackground,           lab_col_f [ Display_1->type ], 
*/
      XmNsensitive,            bb,
      NULL );
  XmStringFree ( xstr );

  XtAddCallback ( but, XmNactivateCallback,
     ( XtCallbackProc ) Display_Button_CB,
     ( XtPointer ) & c_arr [ Display_1->obj ] );

  return ( but );
}

/**************************** create lvl button in row *************************/

Widget
CreLvlDummyLabel ( row, but_num, type, bb ) /*** Display_1 is set ***/
Widget row;
int but_num, type;
Boolean bb;
{
  /***
  Display_1 is a pointer to a Display structure, row is the field of
  the _row structure to which Display_1->main/provers/... points.
  The label is created and stored in the _row structure,
  XmNuserData the (pointer) is set to the c_arr [ `but_no' ];
  the Callback is also set;
  XmNsensitive is set according to bb;
  the button is returned.
  ***/

  Widget but;
  void Display_Button_CB ();
  XmString xstr = XmStringCreateLtoR ( "          ", charset );

/***
printf ( "CreNameButton ( but=%d row=%d but_num=%d type=%d)\n", but, row, but_num, type ); fflush ( stdout );
***/

  but = XtVaCreateManagedWidget ( lab_types [ type ], 
      xmLabelWidgetClass,      row,
      XmNlabelString,          xstr,
      XmNrecomputeSize,        False,
      XmNheight,               10,
      XmNwidth,                /*92,*/ 88,
      XmNborderWidth,          0,
      XmNmarginWidth,          /*2,*/ 0,
      XmNdefaultButtonShadowThickness,  0,
      XmNshadowThickness,      0,
      XmNhighlightThickness,   0,
      XmNuserData,             ( XtPointer ) & c_arr [ lvl_num ],
/*
      XmNforeground,           lab_col_b [ Display_1->type ], 
      XmNbackground,           lab_col_f [ Display_1->type ], 
*/
      XmNsensitive,            bb,
      NULL );
  XmStringFree ( xstr );

/*
Warning: Cannot find callback list in XtAddCallback
*/
/*
printf ( "%s %d\n", GetName ( Display_1->obj ), c_arr [ Display_1->obj ] );
  XtAddCallback ( but, XmNactivateCallback,
     ( XtCallbackProc ) Display_Button_CB,
     ( XtPointer ) & c_arr [ Display_1->obj ] );
*/

  return ( but );
}

/**************************** create push button in row *************************/

Widget
CrePushButton ( row, but_num, type, bb ) /*** Display_1 is set ***/
Widget row;
int but_num, type;
Boolean bb;
{
  /***
  Display_1 is a pointer to a Display structure, row is the field of
  the _row structure to which Display_1->main/provers/... points.
  The button is created and stored in the _row structure,
  XmNuserData the (pointer) is set to the c_arr [ `but_no' ];
  the Callback is also set;
  XmNsensitive is set according to bb;
  the button is returned.
  ***/

  Widget but;
  void Display_Button_CB ();

  XmString xstr = XmStringCreateLtoR ( " ", charset );

/***
printf ( "CrePushButton ( but=%d row=%d but_num=%d type=%d)\n", but, row, but_num, type ); fflush ( stdout );
***/

/***
storeStartClock;
***/

  but = XtVaCreateManagedWidget ( lab_types [ type ],
/*
  but = XtVaCreateWidget ( lab_types [ type ],
*/
      xmPushButtonWidgetClass, row,
      XmNalignment,            XmALIGNMENT_CENTER, /* */
      XmNforeground,           lab_col_b [ Display_1->type ], 
      XmNbackground,           lab_col_f [ Display_1->type ],
      XmNmarginTop,            1,
/*
      XmNmarginTop,            5,
*/
/*
      XmNlabelType,               XmPIXMAP,
      XmNlabelPixmap,             but_xpm,
*/
      XmNrecomputeSize,        False,
      XmNheight,               10,
      XmNwidth,                /* 14,*/ 16,
      XmNnavigationType,       XmTAB_GROUP,
      XmNborderWidth,          /* 1, */ 0,
      XmNdefaultButtonShadowThickness,  0,
      XmNshadowThickness,      /* 2,*/ 1,
      XmNhighlightThickness,   /* 1,*/ 1,
      XmNuserData,             ( XtPointer ) & c_arr [ but_num ],
      XmNsensitive,            bb,
      XmNlabelString,          xstr,
      NULL );
  XmStringFree ( xstr );
/***
printf ( " (%6d)", elapsedClock ); fflush ( stdout );
storeStartClock;
***/

  XtAddCallback ( but, XmNactivateCallback,
     ( XtCallbackProc ) Display_Button_CB,
     ( XtPointer ) & c_arr [ Display_1->obj ] );

/***
printf ( " (%6d)\n", elapsedClock ); fflush ( stdout );
***/
  return ( but );
}

/**************************** create row widget *************************/

Widget
CreRowWidget ( row_form )
Widget row_form;
{
  Widget row;
  /*
  row = XtVaCreateManagedWidget ( "Canvas", 
  */
  row = XtVaCreateWidget ( "Canvas", 
      xmRowColumnWidgetClass,  row_form,
      XmNleftAttachment,       XmATTACH_FORM, 
      XmNleftOffset,           17, 
      XmNorientation,          XmHORIZONTAL,
      XmNspacing,              13,
      NULL );
  if ( display_initialisation == 0 ) {
    XtManageChild ( row );
  }
  else {
  /* - not needed */
  /*
    if ( display_initialisation_malloc_idx < (5 * DisplayTotal) ) {
      display_initialisation_malloc_arr [ display_initialisation_malloc_idx++ ] = row;
/???
      printf ( "%4d - %d\n", display_initialisation_malloc_idx - 1, row );
???/
    }
    else { /??? array full ???/
/???
      printf ( "%4d - array full\n", row );
???/
      XtManageChild ( row );
    }
      */
  }
  return ( row );
}

/********************** ReattachMain_after_Allocate *************************/

void
ReattachMain_after_Allocate () /*** called after AllocateMain;
                                    Display_1 is set to the Display
                                    whose Main is to be allocated   ***/
{
  /***
  Main_1 =  Main_0 + Display_1->Main_offset
  1. go up from Display_1 until next Main
     is found, or Display_0 is reached;
     if Display_0 is reached, Main_1
     is the top widget, so set Main_1 attachment to FORM,
     else set Main_1's top attachment to that widget
  2. go down down from Display_1 until next Main
     is found, or DisplayTotal is reached;
     if DisplayTotal is reached, Main_1
     is the bottom widget, so there's nothing to do,
     else set the found widget's attachment to Main_1
  ***/

  Display_2 = Display_1;
  if ( Display_2 != Display_0 ) Display_2--;
  while ( ( Display_2 != Display_0 )         &&
          ( Display_2->Main_offset == -1 )    ) {
    Display_2--;
  }
  if ( Display_2->Main_offset == -1 ) {
    XtVaSetValues ( Main_1->row,
        XmNtopAttachment, XmATTACH_FORM,
        NULL );
  }
  else {
    Main_2 = Main_0 + Display_2->Main_offset;
    XtVaSetValues ( Main_1->row,
        XmNtopAttachment, XmATTACH_WIDGET,
        XmNtopWidget,     Main_2->row,
        NULL );
  }

  if ( initial_reattachment ) {
/***
printf ( "main - initial_reattachment for %s\n", Display_1->name );
***/
      return;
  }

  Display_2 = Display_1;
  if ( Display_2 < Display_0 + DisplayTotal ) Display_2++;
  while ( ( Display_2 < Display_0 + DisplayTotal ) &&
          ( Display_2->Main_offset == -1 )           ) {
    Display_2++;
  }
  if ( Display_2 < Display_0 + DisplayTotal ) {
    Main_2 = Main_0 + Display_2->Main_offset;
    XtVaSetValues ( Main_2->row,
        XmNtopAttachment, XmATTACH_WIDGET,
        XmNtopWidget,     Main_1->row,
        NULL );
  }
}

/********************** ReattachMain_before_DeAllocate *************************/

void
ReattachMain_before_DeAllocate () /*** called before DeAllocateMain;
                                        Display_1 is set to the Display
                                        whose Main is to be deallocated ***/
{
  /***
  1. go up from Display_1 until next Main
     is found, or Display_0 is reached;
     if Display_0 is reached, this
     was the top widget, so set top_attach to NULL,
     else set top_attach that widget
  2. go down from Display_1 until next Main
     is found, or DisplayTotal is reached;
     if DisplayTotal is reached, this Main
     is the bottom widget, so there's nothing to do,
     else set the found widget's attachment to top_attach
  ***/

  Widget top_attach;

/***
printf ( "ReattachMain_before_DeAllocate: %s\n", Display_1->name );
***/

  Display_2 = Display_1;
  if ( Display_2 != Display_0 ) Display_2--;
/***
printf ( "  Display_2 in initially %s\n", Display_2->name );
***/
  while ( ( Display_2 != Display_0 )         &&
          ( Display_2->Main_offset == -1 )    ) {
    Display_2--;
/***
printf ( "        Display_2 in now %s\n", Display_2->name );
***/
  }
  if ( ( Display_2 == Display_1 )              ||
       ( ( Display_2 == Display_0 )       &&
       ( Display_2->Main_offset == -1 )    )     ) {
    top_attach = ( Widget ) NULL;
/***
printf ( "   ---> top-attaching to TOP\n" );
***/
  }
  else {
    Main_2 = Main_0 + Display_2->Main_offset;
    top_attach = ( Widget ) Main_2->row;
/***
printf ( "   ---> top-attaching to %s\n", Display_2->name );
***/
  }

  Display_2 = Display_1;
  if ( Display_2 < Display_0 + DisplayTotal ) Display_2++;
  while ( ( Display_2 < Display_0 + DisplayTotal ) &&
          ( Display_2->Main_offset == -1 )           ) {
    Display_2++;
  }
  if ( Display_2 < Display_0 + DisplayTotal ) {
    Main_2 = Main_0 + Display_2->Main_offset;
    if ( top_attach == ( Widget ) NULL ) {
      XtVaSetValues ( Main_2->row,
          XmNtopAttachment, XmATTACH_FORM,
          NULL );
/***
printf ( "   ---> the widget %s\n", Display_2->name );
***/
    }
    else {
      XtVaSetValues ( Main_2->row,
          XmNtopAttachment, XmATTACH_WIDGET,
          XmNtopWidget,   top_attach,
          NULL );
/***
printf ( "   ---> the widget %s\n", Display_2->name );
***/
    }
  }
/***
else printf ( "   ---> however this was BOT\n" );
***/
}

/****************** ReattachProvers_after_Allocate *********************/

void
ReattachProvers_after_Allocate () /*** called after AllocateProvers;
                                    Display_1 is set to the Display
                                    whose Provers is to be allocated   ***/
{
  /***
  for comments see ReattachMain_after_Allocate
  ***/

  Display_2 = Display_1;
  if ( Display_2 != Display_0 ) Display_2--;
  while ( ( Display_2 != Display_0 )         &&
          ( Display_2->Provers_offset == -1 )    ) {
    Display_2--;
  }
  if ( Display_2->Provers_offset == -1 ) {
    XtVaSetValues ( Provers_1->row,
        XmNtopAttachment, XmATTACH_FORM,
        NULL );
  }
  else {
    Provers_2 = Provers_0 + Display_2->Provers_offset;
    XtVaSetValues ( Provers_1->row,
        XmNtopAttachment, XmATTACH_WIDGET,
        XmNtopWidget,     Provers_2->row,
        NULL );
  }

  if ( initial_reattachment ) {
/***
printf ( "provers - initial_reattachment for %s\n", Display_1->name );
***/
      return;
  }

  Display_2 = Display_1;
  if ( Display_2 < Display_0 + DisplayTotal ) Display_2++;
  while ( ( Display_2 < Display_0 + DisplayTotal ) &&
          ( Display_2->Provers_offset == -1 )           ) {
    Display_2++;
  }
  if ( Display_2 < Display_0 + DisplayTotal ) {
    Provers_2 = Provers_0 + Display_2->Provers_offset;
    XtVaSetValues ( Provers_2->row,
        XmNtopAttachment, XmATTACH_WIDGET,
        XmNtopWidget,     Provers_1->row,
        NULL );
  }
}

/***************** ReattachProvers_before_DeAllocate *********************/

void
ReattachProvers_before_DeAllocate () /*** called after DeAllocateProvers;
                                        Display_1 is set to the Display
                                        whose Provers is to be deallocated ***/
{
  /***
  for comments see ReattachMain_before_DeAllocate
  ***/

  Widget top_attach;

  Display_2 = Display_1;
  if ( Display_2 != Display_0 ) Display_2--;
  while ( ( Display_2 != Display_0 )         &&
          ( Display_2->Provers_offset == -1 )    ) {
    Display_2--;
  }
  if ( ( Display_2 == Display_1 )              ||
       ( ( Display_2 == Display_0 )         &&
       ( Display_2->Provers_offset == -1 )    )     ) {
    top_attach = ( Widget ) NULL;
  }
  else {
    Provers_2 = Provers_0 + Display_2->Provers_offset;
    top_attach = ( Widget ) Provers_2->row;
  }

  Display_2 = Display_1;
  if ( Display_2 < Display_0 + DisplayTotal ) Display_2++;
  while ( ( Display_2 < Display_0 + DisplayTotal ) &&
          ( Display_2->Provers_offset == -1 )           ) {
    Display_2++;
  }
  if ( Display_2 < Display_0 + DisplayTotal ) {
    Provers_2 = Provers_0 + Display_2->Provers_offset;
    if ( top_attach == ( Widget ) NULL )
      XtVaSetValues ( Provers_2->row,
          XmNtopAttachment, XmATTACH_FORM,
          NULL );
    else
      XtVaSetValues ( Provers_2->row,
          XmNtopAttachment, XmATTACH_WIDGET,
          XmNtopWidget,   top_attach,
          NULL );
  }
}

/******************* ReattachGenerators_after_Allocate ***********************/

void
ReattachGenerators_after_Allocate () /*** called after AllocateGenerators;
                                    Display_1 is set to the Display
                                    whose Generators is to be allocated   ***/
{
  /***
  for comments see ReattachMain_after_Allocate
  ***/

  Display_2 = Display_1;
  if ( Display_2 != Display_0 ) Display_2--;
  while ( ( Display_2 != Display_0 )         &&
          ( Display_2->Generators_offset == -1 )    ) {
    Display_2--;
  }
  if ( Display_2->Generators_offset == -1 ) {
    XtVaSetValues ( Generators_1->row,
        XmNtopAttachment, XmATTACH_FORM,
        NULL );
  }
  else {
    Generators_2 = Generators_0 + Display_2->Generators_offset;
    XtVaSetValues ( Generators_1->row,
        XmNtopAttachment, XmATTACH_WIDGET,
        XmNtopWidget,     Generators_2->row,
        NULL );
  }

  if ( initial_reattachment ) {
/***
printf ( "generators - initial_reattachment for %s\n", Display_1->name );
***/
      return;
  }

  Display_2 = Display_1;
  if ( Display_2 < Display_0 + DisplayTotal ) Display_2++;
  while ( ( Display_2 < Display_0 + DisplayTotal ) &&
          ( Display_2->Generators_offset == -1 )           ) {
    Display_2++;
  }
  if ( Display_2 < Display_0 + DisplayTotal ) {
    Generators_2 = Generators_0 + Display_2->Generators_offset;
    XtVaSetValues ( Generators_2->row,
        XmNtopAttachment, XmATTACH_WIDGET,
        XmNtopWidget,     Generators_1->row,
        NULL );
  }
}

/***************** ReattachGenerators_before_DeAllocate *********************/

void
ReattachGenerators_before_DeAllocate () /*** called after DeAllocateGenerators;
                                        Display_1 is set to the Display
                                        whose Generators is to be deallocated ***/
{
  /***
  for comments see ReattachMain_before_DeAllocate
  ***/

  Widget top_attach;

  Display_2 = Display_1;
  if ( Display_2 != Display_0 ) Display_2--;
  while ( ( Display_2 != Display_0 )         &&
          ( Display_2->Generators_offset == -1 )    ) {
    Display_2--;
  }
  if ( ( Display_2 == Display_1 )              ||
       ( ( Display_2 == Display_0 )       &&
       ( Display_2->Generators_offset == -1 )    )     ) {
    top_attach = ( Widget ) NULL;
  }
  else {
    Generators_2 = Generators_0 + Display_2->Generators_offset;
    top_attach = ( Widget ) Generators_2->row;
  }

  Display_2 = Display_1;
  if ( Display_2 < Display_0 + DisplayTotal ) Display_2++;
  while ( ( Display_2 < Display_0 + DisplayTotal ) &&
          ( Display_2->Generators_offset == -1 )           ) {
    Display_2++;
  }
  if ( Display_2 < Display_0 + DisplayTotal ) {
    Generators_2 = Generators_0 + Display_2->Generators_offset;
    if ( top_attach == ( Widget ) NULL )
      XtVaSetValues ( Generators_2->row,
          XmNtopAttachment, XmATTACH_FORM,
          NULL );
    else
      XtVaSetValues ( Generators_2->row,
          XmNtopAttachment, XmATTACH_WIDGET,
          XmNtopWidget,   top_attach,
          NULL );
  }
}

/******************* ReattachTranslators_after_Allocate **********************/

void
ReattachTranslators_after_Allocate () /*** called after AllocateTranslators;
                                    Display_1 is set to the Display
                                    whose Translators is to be allocated   ***/
{
  /***
  for comments see ReattachMain_after_Allocate
  ***/

  Display_2 = Display_1;
  if ( Display_2 != Display_0 ) Display_2--;
  while ( ( Display_2 != Display_0 )         &&
          ( Display_2->Translators_offset == -1 )    ) {
    Display_2--;
  }
  if ( Display_2->Translators_offset == -1 ) {
    XtVaSetValues ( Translators_1->row,
        XmNtopAttachment, XmATTACH_FORM,
        NULL );
  }
  else {
    Translators_2 = Translators_0 + Display_2->Translators_offset;
    XtVaSetValues ( Translators_1->row,
        XmNtopAttachment, XmATTACH_WIDGET,
        XmNtopWidget,     Translators_2->row,
        NULL );
  }

  if ( initial_reattachment ) {
/***
printf ( "translators - initial_reattachment for %s\n", Display_1->name );
***/
      return;
  }

  Display_2 = Display_1;
  if ( Display_2 < Display_0 + DisplayTotal ) Display_2++;
  while ( ( Display_2 < Display_0 + DisplayTotal ) &&
          ( Display_2->Translators_offset == -1 )           ) {
    Display_2++;
  }
  if ( Display_2 < Display_0 + DisplayTotal ) {
    Translators_2 = Translators_0 + Display_2->Translators_offset;
    XtVaSetValues ( Translators_2->row,
        XmNtopAttachment, XmATTACH_WIDGET,
        XmNtopWidget,     Translators_1->row,
        NULL );
  }
}

/***************** ReattachTranslators_before_DeAllocate ********************/

void
ReattachTranslators_before_DeAllocate () /*** called after DeAllocateTranslators;
                                        Display_1 is set to the Display
                                        whose Translators is to be deallocated ***/
{
  /***
  for comments see ReattachMain_before_DeAllocate
  ***/

  Widget top_attach;

  Display_2 = Display_1;
  if ( Display_2 != Display_0 ) Display_2--;
  while ( ( Display_2 != Display_0 )         &&
          ( Display_2->Translators_offset == -1 )    ) {
    Display_2--;
  }
  if ( ( Display_2 == Display_1 )              ||
       ( ( Display_2 == Display_0 )       &&
       ( Display_2->Translators_offset == -1 )    )     ) {
    top_attach = ( Widget ) NULL;
  }
  else {
    Translators_2 = Translators_0 + Display_2->Translators_offset;
    top_attach = ( Widget ) Translators_2->row;
  }

  Display_2 = Display_1;
  if ( Display_2 < Display_0 + DisplayTotal ) Display_2++;
  while ( ( Display_2 < Display_0 + DisplayTotal ) &&
          ( Display_2->Translators_offset == -1 )           ) {
    Display_2++;
  }
  if ( Display_2 < Display_0 + DisplayTotal ) {
    Translators_2 = Translators_0 + Display_2->Translators_offset;
    if ( top_attach == ( Widget ) NULL )
      XtVaSetValues ( Translators_2->row,
          XmNtopAttachment, XmATTACH_FORM,
          NULL );
    else
      XtVaSetValues ( Translators_2->row,
          XmNtopAttachment, XmATTACH_WIDGET,
          XmNtopWidget,   top_attach,
          NULL );
  }
}

/******************* ReattachDocuments_after_Allocate **********************/

void
ReattachDocuments_after_Allocate () /*** called after AllocateDocuments;
                                    Display_1 is set to the Display
                                    whose Documents is to be allocated   ***/
{
  /***
  for comments see ReattachMain_after_Allocate
  ***/

  Display_2 = Display_1;
  if ( Display_2 != Display_0 ) Display_2--;
  while ( ( Display_2 != Display_0 )         &&
          ( Display_2->Documents_offset == -1 )    ) {
    Display_2--;
  }
  if ( Display_2->Documents_offset == -1 ) {
    XtVaSetValues ( Documents_1->row,
        XmNtopAttachment, XmATTACH_FORM,
        NULL );
  }
  else {
    Documents_2 = Documents_0 + Display_2->Documents_offset;
    XtVaSetValues ( Documents_1->row,
        XmNtopAttachment, XmATTACH_WIDGET,
        XmNtopWidget,     Documents_2->row,
        NULL );
  }

  if ( initial_reattachment ) {
/***
printf ( "documents - initial_reattachment for %s\n", Display_1->name );
***/
      return;
  }

  Display_2 = Display_1;
  if ( Display_2 < Display_0 + DisplayTotal ) Display_2++;
  while ( ( Display_2 < Display_0 + DisplayTotal ) &&
          ( Display_2->Documents_offset == -1 )           ) {
    Display_2++;
  }
  if ( Display_2 < Display_0 + DisplayTotal ) {
    Documents_2 = Documents_0 + Display_2->Documents_offset;
    XtVaSetValues ( Documents_2->row,
        XmNtopAttachment, XmATTACH_WIDGET,
        XmNtopWidget,     Documents_1->row,
        NULL );
  }
}

/***************** ReattachDocuments_before_DeAllocate ********************/

void
ReattachDocuments_before_DeAllocate () /*** called after DeAllocateDocuments;
                                        Display_1 is set to the Display
                                        whose Documents is to be deallocated ***/
{
  /***
  for comments see ReattachMain_before_DeAllocate
  ***/

  Widget top_attach;

  Display_2 = Display_1;
  if ( Display_2 != Display_0 ) Display_2--;
  while ( ( Display_2 != Display_0 )         &&
          ( Display_2->Documents_offset == -1 )    ) {
    Display_2--;
  }
  if ( ( Display_2 == Display_1 )              ||
       ( ( Display_2 == Display_0 )       &&
       ( Display_2->Documents_offset == -1 )    )     ) {
    top_attach = ( Widget ) NULL;
  }
  else {
    Documents_2 = Documents_0 + Display_2->Documents_offset;
    top_attach = ( Widget ) Documents_2->row;
  }

  Display_2 = Display_1;
  if ( Display_2 < Display_0 + DisplayTotal ) Display_2++;
  while ( ( Display_2 < Display_0 + DisplayTotal ) &&
          ( Display_2->Documents_offset == -1 )           ) {
    Display_2++;
  }
  if ( Display_2 < Display_0 + DisplayTotal ) {
    Documents_2 = Documents_0 + Display_2->Documents_offset;
    if ( top_attach == ( Widget ) NULL )
      XtVaSetValues ( Documents_2->row,
          XmNtopAttachment, XmATTACH_FORM,
          NULL );
    else
      XtVaSetValues ( Documents_2->row,
          XmNtopAttachment, XmATTACH_WIDGET,
          XmNtopWidget,   top_attach,
          NULL );
  }
}

/******************************** realloc_check ********************************/

#define realloc_check(p,t,n) \
  p = ( struct t * ) realloc ( ( struct t * ) p, ( n * sizeof ( struct t ) ) ); \
  if ( p == NULL ) { BT_crash_err_exit ( 2271 ); return; }

/************************** initialise_row_to_null *****************************/

#define initialise_row_to_null(m,n,t,u) \
  for ( n = m + t ; n < m + u ; n++ ) { n->row = ( XtPointer ) NULL; }

/************************ initialise_name_to_empty ****************************/

#define initialise_name_to_empty(m,n,t,u) \
  for ( n = m + t ; n < m + u ; n++ ) { ( n->name ) [ 0 ] = '\0'; }

/*************************** DeAllocateMain *************************/

void
DeAllocateMain () /*** Main_1 is set ***/
{
  /***
  calls ReattachMain_before_DeAllocate;
  then deallocates the Main structure,
  XtDestroying the row & decrementing MainTotal
  ***/

  ReattachMain_before_DeAllocate ();

  XtDestroyWidget ( ( Widget ) Main_1->row );

  Main_1->row = ( XtPointer ) NULL;
  MainTotal--;

/***
printf ( "MainTotal = %d\n", MainTotal );
***/
}

/*************************** AllocateMain *************************/

void
AllocateMain () /*** Display_1 is set ***/
{
  /***
  allocates next available Main structure
  (calling realloc if reqd);
  creates all widgets;
  calls ReattachMain_after_Allocate;
  on exit Main_1 points to the new structure
  ***/

  Boolean bb;

/***
printf ( "AllocateMain - start ..." ); fflush ( stdout );
***/
  /***
  see if we need a(n initialised) realloc
  ***/
  if ( MainTotal == MainMallocTotal ) {
    int prev_MainMallocTotal = MainMallocTotal;
    MainMallocTotal += MALLOC_Main_TOPUP;
    realloc_check ( Main_0, MainDisplay, MainMallocTotal );
    initialise_row_to_null ( Main_0, Main_1,
                                   prev_MainMallocTotal, MainMallocTotal );
  }

  /***
  get next unused MainDisplay & create all widgets
  ***/
/***
printf ( "    AllocateMain - CrePushButton start ... " ); fflush ( stdout );
***/
  Main_1 = Main_0;
  while ( Main_1->row != ( XtPointer ) NULL ) { Main_1++; }

/***
printf ( " (%6d)", elapsedClock ); fflush ( stdout );
storeStartClock;
***/

  if   ( ( curr_env == main_env ) && ( DeSensitized ) ) bb = False;
  else                                                  bb = True;

/***
storeStartClock;
***/

  Main_1->row = ( XtPointer ) CreRowWidget  ( main_row_form );

  Main_1->cmt = ( XtPointer ) CrePushButton ( Main_1->row, cmt_num, Display_1->type, bb );
  Main_1->anl = ( XtPointer ) CrePushButton ( Main_1->row, anl_num, Display_1->type, bb );
  Main_1->pog = ( XtPointer ) CrePushButton ( Main_1->row, pog_num, Display_1->type, bb );
  Main_1->anm = ( XtPointer ) CrePushButton ( Main_1->row, anm_num, Display_1->type, bb );
  Main_1->sts = ( XtPointer ) CrePushButton ( Main_1->row, sts_num, Display_1->type, bb );
  Main_1->rst = ( XtPointer ) CrePushButton ( Main_1->row, rst_num, Display_1->type, bb );
  Main_1->nme = ( XtPointer ) CreNameButton ( Main_1->row, nme_num, Display_1->type, bb );
  MainTotal++;

/***
printf ( " (%6d)", elapsedClock ); fflush ( stdout );
storeStartClock;
***/
  ReattachMain_after_Allocate ();
/***
printf ( " end (%6d)\n", elapsedClock ); fflush ( stdout );
***/
}

/*************************** DeAllocateProvers *************************/

void
DeAllocateProvers () /*** Provers_1 is set ***/
{
  /***
  for comments see DeAllocateMain
  ***/

  ReattachProvers_before_DeAllocate ();

  XtDestroyWidget ( ( Widget ) Provers_1->row );

  Provers_1->row = ( XtPointer ) NULL;
  ProversTotal--;

/***
printf ( "ProversTotal = %d\n", ProversTotal );
***/
}

/*************************** AllocateProvers *************************/

void
AllocateProvers ()
{
  /***
  for comments see AllocateMain
  ***/

  Boolean bb;

  if ( ProversTotal == ProversMallocTotal ) {
    int prev_ProversMallocTotal = ProversMallocTotal;
    ProversMallocTotal += MALLOC_Provers_TOPUP;
    realloc_check ( Provers_0, ProversDisplay, ProversMallocTotal );
    initialise_row_to_null ( Provers_0, Provers_1,
                                   prev_ProversMallocTotal, ProversMallocTotal );
  }

  Provers_1 = Provers_0;
  while ( Provers_1->row != ( XtPointer ) NULL ) { Provers_1++; }

  if   ( ( curr_env == provers_env ) && ( DeSensitized ) ) bb = False;
  else                                                     bb = True;

  Provers_1->row = ( XtPointer ) CreRowWidget  ( provers_row_form);
  Provers_1->cmt = ( XtPointer ) CrePushButton ( Provers_1->row, cmt_num, Display_1->type, bb );
  Provers_1->prv = ( XtPointer ) CrePushButton ( Provers_1->row, prv_num, Display_1->type, bb );
  Provers_1->pmd = ( XtPointer ) CrePushButton ( Provers_1->row, pmd_num, Display_1->type, bb );
  Provers_1->ppf = ( XtPointer ) CrePushButton ( Provers_1->row, ppf_num, Display_1->type, bb );
  Provers_1->rsl = ( XtPointer ) CrePushButton ( Provers_1->row, rsl_num, Display_1->type, bb );
  if ( Display_1->type == prf_gen ) {
    Provers_1->lvl = ( XtPointer ) CreLvlDummyLabel ( Provers_1->row, lvl_num, Display_1->type, bb );
  }
  else {
    Provers_1->lvl = ( XtPointer ) CreLvlButton  ( Provers_1->row, lvl_num, Display_1->type, bb );
  }
  Provers_1->nme = ( XtPointer ) CreNameButton ( Provers_1->row, nme_num, Display_1->type, bb );
  ProversTotal++;

  ReattachProvers_after_Allocate ();
}

/*************************** DeAllocateGenerators *************************/

void
DeAllocateGenerators () /*** Generators_1 is set ***/
{
  /***
  for comments see DeAllocateMain
  ***/

  ReattachGenerators_before_DeAllocate ();

  XtDestroyWidget ( ( Widget ) Generators_1->row );

  Generators_1->row = ( XtPointer ) NULL;
  GeneratorsTotal--;

/***
printf ( "GeneratorsTotal = %d\n", GeneratorsTotal );
***/
}

/*************************** AllocateGenerators *************************/

void
AllocateGenerators ()
{
  /***
  for comments see AllocateMain
  ***/

  Boolean bb;

  if ( GeneratorsTotal == GeneratorsMallocTotal ) {
    int prev_GeneratorsMallocTotal = GeneratorsMallocTotal;
    GeneratorsMallocTotal += MALLOC_Generators_TOPUP;
    realloc_check ( Generators_0, GeneratorsDisplay, GeneratorsMallocTotal );
    initialise_row_to_null ( Generators_0, Generators_1,
                                prev_GeneratorsMallocTotal, GeneratorsMallocTotal );
  }

  Generators_1 = Generators_0;
  while ( Generators_1->row != ( XtPointer ) NULL ) { Generators_1++; }

  if   ( ( curr_env == generators_env ) && ( DeSensitized ) ) bb = False;
  else                                                        bb = True;

  Generators_1->row = ( XtPointer ) CreRowWidget  ( generators_row_form);
  Generators_1->cmt = ( XtPointer ) CrePushButton ( Generators_1->row, cmt_num, Display_1->type, bb );
  Generators_1->gbo = ( XtPointer ) CrePushButton ( Generators_1->row, gbo_num, Display_1->type, bb );
  Generators_1->gbm = ( XtPointer ) CrePushButton ( Generators_1->row, gbm_num, Display_1->type, bb );
  Generators_1->Enm = ( XtPointer ) CrePushButton ( Generators_1->row, Enm_num, Display_1->type, bb );
  Generators_1->Itf = ( XtPointer ) CrePushButton ( Generators_1->row, Itf_num, Display_1->type, bb );
  Generators_1->rst = ( XtPointer ) CrePushButton ( Generators_1->row, gen_rst_num, Display_1->type, bb );
  Generators_1->nme = ( XtPointer ) CreNameButton ( Generators_1->row, nme_num, Display_1->type, bb );
  GeneratorsTotal++;

  ReattachGenerators_after_Allocate ();
}

/*************************** DeAllocateTranslators *************************/

void
DeAllocateTranslators () /*** Translators_1 is set ***/
{
  /***
  for comments see DeAllocateMain
  ***/

  ReattachTranslators_before_DeAllocate ();

  XtDestroyWidget ( ( Widget ) Translators_1->row );

  Translators_1->row = ( XtPointer ) NULL;
  TranslatorsTotal--;

/***
printf ( "TranslatorsTotal = %d\n", TranslatorsTotal );
***/
}

/*************************** AllocateTranslators *************************/

void
AllocateTranslators ()
{
  /***
  for comments see AllocateMain
  ***/

  int Prog_Language_Option;
  Boolean bb;

  if ( TranslatorsTotal == TranslatorsMallocTotal ) {
    int prev_TranslatorsMallocTotal = TranslatorsMallocTotal;
    TranslatorsMallocTotal += MALLOC_Translators_TOPUP;
    realloc_check ( Translators_0, TranslatorsDisplay, TranslatorsMallocTotal );
    initialise_row_to_null ( Translators_0, Translators_1,
                               prev_TranslatorsMallocTotal, TranslatorsMallocTotal );
  }

  Translators_1 = Translators_0;
  while ( Translators_1->row != ( XtPointer ) NULL ) { Translators_1++; }


  if   ( ( curr_env == translators_env ) && ( DeSensitized ) ) bb = False;
  else                                                         bb = True;

  Translators_1->row = ( XtPointer ) CreRowWidget  ( translators_row_form);
  Translators_1->cmt = ( XtPointer ) CrePushButton ( Translators_1->row, cmt_num, Display_1->type, bb );
  Translators_1->trl = ( XtPointer ) CrePushButton ( Translators_1->row, trl_num, Display_1->type, bb );
  Translators_1->lnk = ( XtPointer ) CrePushButton ( Translators_1->row, lnk_num, Display_1->type, bb );
  Translators_1->exe = ( XtPointer ) CrePushButton ( Translators_1->row, exe_num, Display_1->type, bb );
  Translators_1->rst = ( XtPointer ) CrePushButton ( Translators_1->row, trl_rst_num, Display_1->type, bb );
  Translators_1->nme = ( XtPointer ) CreNameButton ( Translators_1->row, nme_num, Display_1->type, bb );
  TranslatorsTotal++;

  ReattachTranslators_after_Allocate ();
}

/*************************** DeAllocateDocuments *************************/

void
DeAllocateDocuments () /*** Documents_1 is set ***/
{
  /***
  for comments see DeAllocateMain
  ***/

  ReattachDocuments_before_DeAllocate ();

  XtDestroyWidget ( ( Widget ) Documents_1->row );

  Documents_1->row = ( XtPointer ) NULL;
  DocumentsTotal--;

/***
printf ( "DocumentsTotal = %d\n", DocumentsTotal );
***/
}

/*************************** AllocateDocuments *************************/

void
AllocateDocuments ()
{
  /***
  for comments see AllocateMain
  ***/

  Boolean bb;

  if ( DocumentsTotal == DocumentsMallocTotal ) {
    int prev_DocumentsMallocTotal = DocumentsMallocTotal;
    DocumentsMallocTotal += MALLOC_Documents_TOPUP;
    realloc_check ( Documents_0, DocumentsDisplay, DocumentsMallocTotal );
    initialise_row_to_null ( Documents_0, Documents_1,
                                   prev_DocumentsMallocTotal, DocumentsMallocTotal );
  }

  Documents_1 = Documents_0;
  while ( Documents_1->row != ( XtPointer ) NULL ) { Documents_1++; }

  if   ( ( curr_env == documents_env ) && ( DeSensitized ) ) bb = False;
  else                                                       bb = True;

  Documents_1->row = ( XtPointer ) CreRowWidget  ( documents_row_form);
  Documents_1->cmt = ( XtPointer ) CrePushButton ( Documents_1->row, cmt_num, Display_1->type, bb );
  Documents_1->dmu = ( XtPointer ) CrePushButton ( Documents_1->row, dmu_num, Display_1->type, bb );
  Documents_1->shw = ( XtPointer ) CrePushButton ( Documents_1->row, shw_num, Display_1->type, bb );
  Documents_1->prt = ( XtPointer ) CrePushButton ( Documents_1->row, prt_num, Display_1->type, bb );
  Documents_1->rst = ( XtPointer ) CrePushButton ( Documents_1->row, doc_rst_num, Display_1->type, bb );
  Documents_1->nme = ( XtPointer ) CreNameButton ( Documents_1->row, nme_num, Display_1->type, bb );
  DocumentsTotal++;

  ReattachDocuments_after_Allocate ();
}


/************************* DisplayRemove *********************/

void
DisplayRemove ()  /*** Display_1 is set ***/
{
  /***
  shuffles Display up, overwriting Display_1,
  and then (re)initialises the last copied
  ***/

  for ( Display_2 = Display_1 ;
              Display_2 < Display_0 + DisplayTotal - 1 ; Display_2++ ) {
    DisplayCopy ( Display_2 + 1, Display_2 );
  }
  ( Display_2->name ) [ 0 ] = '\0';
  DisplayTotal--;
}

/************************* SetDisplay_1_for_obj *********************/

void
SetDisplay_1_for_obj ( obj )
int obj;
{
  
  /***
  sets Display_1 corresponding to Display_1->obj = obj
  ***/
  Display_1 = Display_0;
  while ( Display_1->obj != obj ) Display_1++;
}

/************************* SetDisplay_1_for_name *********************/

void
SetDisplay_1_for_name ( name )
char * name;
{
  
  /***
  sets Display_1 corresponding to Display_1->name = name
  if name is not matched, Display_1 is set to Display_0 - 1
  ***/
/***
printf ( "SetDisplay_1_for_name ( name = %s )\n", name );
***/
  Display_1 = Display_0;

  while ( ( Display_1 < Display_0 + DisplayTotal ) &&
          ( strcmp ( Display_1->name, name ) != 0 )   ) {
    Display_1++;
  }
  if ( Display_1 == Display_0 + DisplayTotal ) Display_1 = Display_0 - 1;
}

/************* SetDisplayField_obj_Changed ****************/

void
SetDisplayField_obj_Changed ( obj )
int obj;
{
  /***
  Sets the Display.changed flag
  MasterChanged set
  ***/

  SetDisplay_1_for_obj ( obj );
  Display_1->changed = 1;
  MasterChanged = 1;
  HtmlMasterFileChanged = 1;
/***
printf ( "***** flagging change %s (obj=%d)\n", Display_1->name, obj );
***/
}

/****************************** DisplayCopy **************************/

DisplayCopy ( d1, d2 )
struct Display * d1, * d2;
{
  /***
  copies contents of Display d1 into d2;
  called by DisplayInsert/DisplayUnInsert
  ***/

/***
printf ( "    DisplayCopy ( %d->%d )\n", d1, d2 ); fflush ( stdout );
***/

  d2->obj                = d1->obj;
  strcpy ( d2->name, d1->name );
  d2->type               = d1->type;
  d2->changed            = d1->changed;
  d2->decoration         = d1->decoration;
  d2->cmt_on_off         = d1->cmt_on_off;
  d2->sc_state           = d1->sc_state;
  d2->ps                 = d1->ps;
  d2->Main_offset        = d1->Main_offset;
  d2->Provers_offset     = d1->Provers_offset;
  d2->Generators_offset  = d1->Generators_offset;
  d2->Translators_offset = d1->Translators_offset;
  d2->Documents_offset   = d1->Documents_offset;
}

/************************* DisplayInsert *********************/

void
DisplayInsert ( obj )
int obj;
{
  /***
  first checks if a Display realloc is necessary;
  (if so calls initialise_name_to_empty);
  inserts obj into Display by shuffling (calling DisplayCopy);
  calls Save_CfgDepBase;

       sets:
         obj
         name          to full construct name
         type
         changed       to 1
         SRC_flagged   to 0
         ps            to 0
         *_offset      to -1 
  Finally calls ReallocPrimaryStringIfReq
  ***/

  int /*name [ 35 ],*/ ext, type; /* huh? int name ? char surely ... ? */
  char name [ 35 * sizeof(int) ];
  int is_generated, is_gen_by, is_prf, prf_level;
  char buf [ /*50*/ 297 ]; /* why is this so small? 35*4 + ext (4) = 144 + 1 for null = 145. Or at prf level: 35*4*2 +6 + 10 + 1 for null = 297 not 50*/
  void WarnBaseCapacityApproaching ();
  
  name[0]='\0';
  name[ sizeof(name) - 1 ]='\0';
  buf[0]='\0';

printf("DisplayInsert ( %d )\n",obj);

  /***
  see if we need a realloc - if so initialise the new structures
  ***/
  if ( DisplayTotal == DisplayMallocTotal ) {

    struct Display * Display_prev = Display_0;
    int prev_DisplayMallocTotal = DisplayMallocTotal;
    DisplayMallocTotal += MALLOC_Display_TOPUP;

/***
printf ( "                   DisplayMallocTotal: %d->%d Display_0=%d\n", prev_DisplayMallocTotal, DisplayMallocTotal, Display_0 ); fflush ( stdout );
***/
printf ( "                   DisplayMallocTotal: %d->%d Display_0=%p\n", prev_DisplayMallocTotal, DisplayMallocTotal, Display_0 ); fflush ( stdout );

    realloc_check ( Display_0, Display, DisplayMallocTotal );
/***
printf ( "                   DisplayMallocTotal: %d->%d\n", prev_DisplayMallocTotal, DisplayMallocTotal ); fflush ( stdout );
***/
printf ( "                   DisplayMallocTotal: %d->%d\n", prev_DisplayMallocTotal, DisplayMallocTotal ); fflush ( stdout );

    initialise_name_to_empty ( Display_0, Display_1,
                                   prev_DisplayMallocTotal, DisplayMallocTotal );

    if ( Display_prev != Display_0 ) {
/***
Popup_Info ( " malloc has changed Display_0 pointer\n\n       changing Display_visible        " );
***/
printf ( "malloc has changed Display_0 pointer\nchanging Display_visible        \n" );
      Display_visible = Display_visible + ( Display_0 - Display_prev );
    }
  }

printf("DisplayInsert ( %d ) before get values\n",obj, name);
  /***
  create full name;
  get other values
  ***/
  
  xtr_name ( name, obj );
  
 printf("DisplayInsert ( %d ) xtr_name ( %d ) = %s \n",obj, obj, name);
 
  val_ext ( &ext, obj );
  
printf("DisplayInsert ( %d ) val_ext ( %d ) = %d \n",obj, obj, ext);   
  
  val_type ( &type, obj );
  
printf("DisplayInsert ( %d ) val_type ( %d ) = %d \n",obj, obj, type);

  val_opt ( &is_generated, &is_gen_by, &is_prf, &prf_level, obj );
  
  if ( is_prf )
  {
    if ( prf_level )
    {
      snprintf ( buf, sizeof(buf), "%s.%s.prf.%d", ( char * ) name, extens [ ext ], prf_level - 1 );
      
      printf("1 buf=%s\n", buf);
     } 
    else
     {
      snprintf ( buf,sizeof(buf), "%s.%s.prf", ( char * ) name, extens [ ext ] );
      printf("2 buf=%s\n", buf);
     }
  }
  else
  {
    snprintf ( buf,sizeof(buf), "%s.%s", ( char * ) name, extens [ ext ] );
    printf("3 buf=%s\n", buf);
  } 
    
    printf("Display_0 is at %p\n sizeof(Display) is %llu",Display_0, (unsigned long long) sizeof(struct Display));
    
    
    
  /***
  insert into Display
  ***/
  Display_1 = Display_0;
  while ( ( strcmp ( buf, Display_1->name ) > 0 )  &&
          ( Display_1 < Display_0 + DisplayTotal )      ) {
/***
printf ( "   DisplayInsert:  %s > %s (%d)\n", buf, Display_1->name, Display_1 - Display_0 ); fflush ( stdout );
***/
printf ( "   DisplayInsert:  %s > %s (%llu)\n", buf, Display_1->name, (unsigned long long) (Display_1 - Display_0) ); fflush ( stdout );

    Display_1++;
  }
  
/***
printf ( "    %d is where the insertion will be made\n", Display_1 - Display_0 ); fflush ( stdout );
***/

  Display_2 = Display_0 + DisplayTotal;
  while ( Display_2 > Display_1 ) {
/***
printf ( "    copying %s (%d)->%s (%d) \n", ( Display_2-1 )->name, Display_2 - 1 - Display_0, Display_2->name, Display_2 - Display_0 ); fflush ( stdout );
***/
    DisplayCopy ( Display_2 - 1, Display_2 );
    Display_2--;
  }

  /***
  set fields of Display
  ***/
  Display_1->obj                = obj;
  strcpy ( Display_1->name, buf );
  Display_1->type               =  type;
  Display_1->changed            =  1;
  Display_1->decoration         =  undecor_SRC_file_newer;
  Display_1->cmt_on_off         =  cmt_off;
/***
printf ( "just set %s cmt_on_off to %d\n", Display_1->name, Display_1->cmt_on_off ); fflush ( stdout );
***/
  Display_1->sc_state           =  sc_state_w;
  Display_1->ps                 =  0;
  Display_1->Main_offset        = -1;
  Display_1->Provers_offset     = -1;
  Display_1->Generators_offset  = -1;
  Display_1->Translators_offset = -1;
  Display_1->Documents_offset   = -1;

  MasterChanged = 1;

  DisplayTotal++;

  if ( DisplayTotal + 25  > MAX_NUM_CONSTRUCTS ) { WarnBaseCapacityApproaching (); }

  Save_CfgDepBase ();

  ReallocPrimaryStringIfReq ();

/***
printf ( "        ******* DisplayInserted %s (%d) at Display posn %d\n", Display_1->name, obj, Display_1 - Display_0 ); fflush ( stdout );
***/
}

/***************************** DisplayUnInsert *************************/

void
DisplayUnInsert ( obj )
int obj;
{
  /***
  Called by KillConstruct - BMotif.c.
  First deallocate each *_offset structure
  (which will include reattaching if currently allocated)
  ***/

  void SetDisplay_1_for_obj ();
/*
  int hid_LIB_cur, hid_gen_cur, type;
*/

/***
printf ( "        ************ DisplayUnInsert %s\n", GetName ( obj ) );
***/

  SetDisplay_1_for_obj ( obj );
  chk_deallocated_and_reset ( Main_offset, DeAllocateMain,
                                                      Main_1, Main_0 );
  chk_deallocated_and_reset ( Provers_offset, DeAllocateProvers,
                                                      Provers_1, Provers_0 );
  chk_deallocated_and_reset ( Generators_offset, DeAllocateGenerators,
                                                      Generators_1, Generators_0 );
  chk_deallocated_and_reset ( Translators_offset, DeAllocateTranslators,
                                                      Translators_1, Translators_0 );
  chk_deallocated_and_reset ( Documents_offset, DeAllocateDocuments,
                                                      Documents_1, Documents_0 );

  /***
  Then remove from Display:
  shuffle Display up, overwriting Display_1,
  then (re)initialise the last copied (to make available);
  decrement DisplayTotal
  ***/

  SetDisplay_1_for_obj ( obj );
  for ( Display_2 = Display_1 ;
              Display_2 < Display_0 + DisplayTotal - 1 ; Display_2++ ) {
    DisplayCopy ( Display_2 + 1, Display_2 );
  }
  ( Display_2->name ) [ 0 ] = '\0';
  DisplayTotal--;
  
}

/**************************** malloc_check ***************************************/

#define malloc_check(p,t,n) \
  p = ( struct t * ) malloc ( n * sizeof ( struct t ) ); \
  if ( p == NULL ) { BT_crash_err_exit ( 2270 ); return; }

/*********************************************************************************/

void
InitialiseDisplay ()
{
 int loc, obj, tot;

  /***
  set applicable_str/inapplicable_str
  ***/

/***
printf ( "InitialiseDisplay ()\n" ); sleep ( 10 );
***/

  sprintf ( applicable_unedited_str, "%c", applicable_unedited_chr );
  sprintf ( applicable_edited_str,   "%c", applicable_edited_chr );
  sprintf ( inapplicable_str,        "%c", inapplicable_chr );

  /***
  perform the initial malloc
  ***/
  nbr_Construct ( & tot );
  tot += 5;
  DisplayMallocTotal     = tot;
  MainMallocTotal        = tot;
  ProversMallocTotal     = ( tot / 2 );
  GeneratorsMallocTotal  = 5;
  TranslatorsMallocTotal = ( tot / 2 );
  DocumentsMallocTotal   = tot;
/*
  DisplayMallocTotal     = MALLOC_Display_INIT;
  MainMallocTotal        = MALLOC_MainDisplay_INIT;
  ProversMallocTotal     = MALLOC_ProversDisplay_INIT;
  GeneratorsMallocTotal  = MALLOC_GeneratorsDisplay_INIT;
  TranslatorsMallocTotal = MALLOC_TranslatorsDisplay_INIT;
  DocumentsMallocTotal   = MALLOC_DocumentsDisplay_INIT;
*/


  malloc_check ( Display_0,     Display,            DisplayMallocTotal );
  malloc_check ( Main_0,        MainDisplay,        MainMallocTotal );
  malloc_check ( Provers_0,     ProversDisplay,     ProversMallocTotal );
  malloc_check ( Generators_0,  GeneratorsDisplay,  GeneratorsMallocTotal );
  malloc_check ( Translators_0, TranslatorsDisplay, TranslatorsMallocTotal );
  malloc_check ( Documents_0,   DocumentsDisplay,   DocumentsMallocTotal );

/***
printf ( "                   DisplayMallocTotal: %d->%d Display_0=%d\n", 0, DisplayMallocTotal, Display_0 ); fflush ( stdout );
printf ( "                   MainMallocTotal: %d->%d Main_0=%d\n", 0, MainMallocTotal, Main_0 ); fflush ( stdout );
printf ( "                   ProversMallocTotal: %d->%d Provers_0=%d\n", 0, ProversMallocTotal, Provers_0 ); fflush ( stdout );
printf ( "                   GeneratorsMallocTotal: %d->%d Generators_0=%d\n", 0, GeneratorsMallocTotal, Generators_0 ); fflush ( stdout );
printf ( "                   TranslatorsMallocTotal: %d->%d Translators_0=%d\n", 0, TranslatorsMallocTotal, Translators_0 ); fflush ( stdout );
printf ( "                   DocumentsMallocTotal: %d->%d Documents_0=%d\n", 0, DocumentsMallocTotal, Documents_0 ); fflush ( stdout );
***/

  /***
  initialise the malloced structures
  ***/
  initialise_name_to_empty ( Display_0,   Display_1,     0, DisplayMallocTotal );
  initialise_row_to_null ( Main_0,        Main_1,        0, MainMallocTotal );
  initialise_row_to_null ( Provers_0,     Provers_1,     0, ProversMallocTotal );
  initialise_row_to_null ( Generators_0,  Generators_1,  0, GeneratorsMallocTotal );
  initialise_row_to_null ( Translators_0, Translators_1, 0, TranslatorsMallocTotal );
  initialise_row_to_null ( Documents_0,   Documents_1,   0, DocumentsMallocTotal );

/***
  printf ( " *** starting to sore all constructs in sel_str_arr\n" ); fflush ( stdout );
***/
  /***
  sort all constructs in sel_str_arr
  ***/
  sel_arr_tot = 0;
  first_Construct ( &loc, &obj );
  while ( loc ) {
    xtr_name ( sel_str_arr [ sel_arr_tot ], obj );
    sel_obj_arr [ sel_arr_tot++ ] = obj;
    next_Construct ( &loc, &obj, loc, obj );
  }
  Sort_sel_strs ();
/***
  printf ( " *** done sorting - %d objects in total\n", sel_arr_tot ); fflush ( stdout );
***/

  /***
  insert all constructs into Display from sel_arr (sets changed field)
  ***/
  tot = sel_arr_tot;
  for ( sel_arr_tot = 0 ; sel_arr_tot < tot ; sel_arr_tot++ ) {
/***
printf ( "   %3d->%3d %s\n",
         sel_arr_tot, sel_obj_arr [ sel_arr_tot ], sel_str_arr [ sel_arr_tot ] ); fflush ( stdout );
***/
    DisplayInsert ( sel_obj_arr [ sel_arr_tot ] );
  }

/*
  /???
  insert all constructs into Display (sets changed field)
  ???/
  first_Construct ( &loc, &obj );
  while ( loc ) {
    DisplayInsert ( obj );
    next_Construct ( &loc, &obj, loc, obj );
  }
*/

  Display_visible = Display_0;

/***
  for ( i = 1 ; i < 10 ; i++ ) {
    printf ( "lab_col_f [ %d ] = %d  lab_col_b [ %d ] = %d\n", i, lab_col_f [ i ], i, lab_col_b [ i ] );  }
***/

  total_edits = 0;
  Set_display_initialisation ();

/***
DisplayAndCheckTotals ();
***/

}

/************************** DisplayUnInsert_before_cd ***************************/

void
DisplayUnInsert_before_cd ()
{
  int nn, obj;
  void LoadAllConstructsInto_gset1 ();
  LoadAllConstructsInto_gset1 ();
  card_gset1 ( &nn );
  while ( nn ) {
    valOrd_gset1 ( &obj, nn );
    DisplayUnInsert ( obj );
    nn--;
  }
}

/************************** EnvironmentDisplayUnInsert_Insert ***************************/

void
EnvironmentDisplayDeAllocate_Allocate ()
{
  int i = 0;

/***
DisplayAndCheckTotals ();
***/

  switch ( curr_env ) {
    case main_env:
      XtUnmanageChild ( main_row_scroll );
      break;
    case provers_env:
      XtUnmanageChild ( provers_row_scroll );
      break;
    case generators_env:
      XtUnmanageChild ( generators_row_scroll );
      break;
    case translators_env:
      XtUnmanageChild ( translators_row_scroll );
      break;
    case documents_env:
      XtUnmanageChild ( documents_row_scroll );
      break;
  }

  XtDestroyWidget ( main_row_form );
  main_row_form = XtVaCreateManagedWidget ( "Canvas", 
      xmFormWidgetClass,              main_row_scroll,
      NULL );

  XtDestroyWidget ( provers_row_form );
  provers_row_form = XtVaCreateManagedWidget ( "Canvas", 
      xmFormWidgetClass,              provers_row_scroll,
      NULL );

  XtDestroyWidget ( generators_row_form );
  generators_row_form = XtVaCreateManagedWidget ( "Canvas", 
      xmFormWidgetClass,              generators_row_scroll,
      NULL );

  XtDestroyWidget ( translators_row_form );
  translators_row_form = XtVaCreateManagedWidget ( "Canvas", 
      xmFormWidgetClass,              translators_row_scroll,
      NULL );

  XtDestroyWidget ( documents_row_form );
  documents_row_form = XtVaCreateManagedWidget ( "Canvas", 
      xmFormWidgetClass,              documents_row_scroll,
      NULL );

  for ( Display_1 = Display_0 ;
             Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( Display_1->Main_offset != -1 ) {
      Main_1 = Main_0 + Display_1->Main_offset;
      Main_1->row = ( XtPointer ) NULL;
      Display_1->Main_offset = -1;
    }
    if ( Display_1->Provers_offset != -1 ) {
      Provers_1 = Provers_0 + Display_1->Provers_offset;
      Provers_1->row = ( XtPointer ) NULL;
      Display_1->Provers_offset = -1;
    }
    if ( Display_1->Generators_offset != -1 ) {
      Generators_1 = Generators_0 + Display_1->Generators_offset;
      Generators_1->row = ( XtPointer ) NULL;
      Display_1->Generators_offset = -1;
    }
    if ( Display_1->Translators_offset != -1 ) {
      Translators_1 = Translators_0 + Display_1->Translators_offset;
      Translators_1->row = ( XtPointer ) NULL;
      Display_1->Translators_offset = -1;
    }
    if ( Display_1->Documents_offset != -1 ) {
      Documents_1 = Documents_0 + Display_1->Documents_offset;
      Documents_1->row = ( XtPointer ) NULL;
      Display_1->Documents_offset = -1;
    }
   }

  MainTotal = 0;
  ProversTotal = 0;
  GeneratorsTotal = 0;
  TranslatorsTotal = 0;
  DocumentsTotal = 0;

  initial_reattachment = 1;
  for ( Display_3 = Display_0 ;
             Display_3 < Display_0 + DisplayTotal ; Display_3++ ) {
    Display_1 = Display_3;
    SetButtonState ( Display_1->obj, 0 );
  }
  initial_reattachment = 0;

  switch ( curr_env ) {
    case main_env:
      XtManageChild ( main_row_scroll );
      break;
    case provers_env:
      XtManageChild ( provers_row_scroll );
      break;
    case generators_env:
      XtManageChild ( generators_row_scroll );
      break;
    case translators_env:
      XtManageChild ( translators_row_scroll );
      break;
    case documents_env:
      XtManageChild ( documents_row_scroll );
      break;
  }

/***
DisplayAndCheckTotals ();
***/

  DisplayCurrentEnv ();

}

/**************************** DisplayInsert_after_cd *****************************/

void
DisplayInsert_after_cd ()
{
  int loc, obj;

  /***
  insert all constructs into Display (sets changed field)
  ***/
  first_Construct ( &loc, &obj );
  while ( loc ) {
    DisplayInsert ( obj );
    next_Construct ( &loc, &obj, loc, obj );
  }

  Display_visible = Display_0;

/***
DisplayAndCheckTotals ();
***/
}


/*************************************************************************/
/******************************    UTILITIES *****************************/
/*************************************************************************/

/************************** Load_SRC_CFG_Names ***************************/

void
Load_SRC_CFG_Names ( obj )
int obj;
{
  void SetDisplay_1_for_obj ();
  int ext;

  SetDisplay_1_for_obj ( obj );
  sprintf ( SRCName, "SRC/%s", Display_1->name );
  val_ext ( &ext, obj );
  switch ( ext ) {
  case mch_prf:
  case ref_prf:
  case imp_prf:
    sprintf ( CFGName, "POB/%s", Display_1->name );
    break;
  default:
    sprintf ( CFGName, "CFG/%s", Display_1->name );
    break;
  }
/***
printf("SRCName |%s| CFGName |%s|\n",SRCName,CFGName);
***/
}

/***************************** Set_lnk_on ******************************/

void
Set_lnk_on ( name ) /* called from BMotif_io.c */
char * name;
{
  XmString  xstr;
  void SetDisplay_1_for_name ();
  SetDisplay_1_for_name ( name );
  Translators_1 = Translators_0 + Display_1->Translators_offset;
  set_but_applicable ( Translators_1->lnk, Display_1->type );
}

/***************************** IsConfigured ******************************/

int
IsConfigured ( name )
char * name;
{
  void SetDisplay_1_for_name ();

  SetDisplay_1_for_name ( name );
  return ( ( Display_1 != Display_0 - 1 ) != 0 );
}

/**************************** Modify_ps *****************************/

void
Modify_ps ( obj, ps )
int obj, ps;
{
  void SetDisplay_1_for_obj ();
  void SRC_watch_timer_once_only ();
  Pixel fg, bg;
  int SRC_CFG_FilesDiffer ();
  void   SRC_watch ();

  SetDisplay_1_for_obj ( obj );
  Display_1->ps = ps;

/***
printf ( "Modify_ps %s %d\n", Display_1->name, Display_1->ps );
***/

  Colour_name ();

  /***
  editor opened
  ***/

  if ( ps ) {
    XtIntervalId once_only1, once_only2;

    if   ( SRC_CFG_FilesDiffer ( obj ) ) Decorate_SRC_file_newer ( obj );
    else                                 UnDecorate_SRC_file_newer ( obj );

    /***
    SRC_watch in 4 & 8 secs
    ***/
    once_only1 = XtAppAddTimeOut ( app, 4000,
                   ( XtTimerCallbackProc ) SRC_watch_timer_once_only, NULL );
    once_only2 = XtAppAddTimeOut ( app, 8000,
                   ( XtTimerCallbackProc ) SRC_watch_timer_once_only, NULL );
  }

  /***
  editor closed
  ***/

  if ( ! ps ) {
/*
    fg = inapplicable_lab_col;
    bg = inapplicable_lab_col;
    set_cmt_col ( Main_offset, Main_1, Main_0 );
    set_cmt_col ( Provers_offset, Provers_1, Provers_0 );
    set_cmt_col ( Generators_offset, Generators_1, Generators_0 );
    set_cmt_col ( Translators_offset, Translators_1, Translators_0 );
    set_cmt_col ( Documents_offset, Documents_1, Documents_0 );
*/
    total_edits--;    
  }
  else {
    total_edits++;    
  }
/***
printf ( "total_edits =%d\n", total_edits );
***/

  SRC_watch ();
}

/********************* KillProcess_Modify_ps **************************/

void
KillProcess_Modify_ps ( obj )
int obj;
{
  char cmd [ 50 ];
  void Modify_ps ();
  void SetDisplay_1_for_obj ();

  SetDisplay_1_for_obj ( obj );

  if ( ! Display_1->ps ) return;

#if ( defined ( UNKNOWN_VERSION ) )
  if ( getpgrp ( Display_1->ps ) != -1 ) {
#else
  if ( getpgid ( Display_1->ps ) != -1 ) {
#endif
    sprintf ( cmd, "kill -9 %d", Display_1->ps );
/***
printf("KillProcess_Modify_ps: %s %d `%s'\n",
                                            GetName ( obj ), Display_1->ps, cmd );
***/
    system ( cmd );
  }
/***
  else { printf ( "ps %d is already dead\n", Display_1->ps ); }
***/
  Modify_ps ( obj, 0 );
}

/*********************** CheckForUserClosedEdits **************************/

void
CheckForUserClosedEdits ()
{
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( Display_1->ps ) {
#if ( defined ( UNKNOWN_VERSION ) )
      if ( getpgrp ( Display_1->ps ) == -1 ) {
#else
      if ( getpgid ( Display_1->ps ) == -1 ) {
#endif /* ( defined ( AIX_VERSION ) || defined ( LINUX_VERSION ) || defined ( SOLARIS_VERSION ) ) */
        sprintf ( buf, "Edit process for %s closed", Display_1->name );
        Popup_Info ( buf );
        Modify_ps ( Display_1->obj, 0 );
      }
    }
  }
}

/****************************** CloseAllPriorCD ******************************/

void
CloseAllPriorCD ()
{
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( Display_1->ps ) {
      KillProcess_Modify_ps ( Display_1->obj );
      Load_SRC_CFG_Names ( Display_1->obj );
      unlink( SRCName );
    }
  }
}

/********************************* IsClosed **********************************/

int
IsClosed ( obj )
int obj;
{
  void SetDisplay_1_for_obj ();

  SetDisplay_1_for_obj ( obj );
  return ( ( Display_1->ps == 0 ) != 0 );
}

/********************* BaseCapacityAvailable *****************************/

int
BaseCapacity_ok ()
{
  return ( ( DisplayTotal < MAX_NUM_CONSTRUCTS ) != 0 );
}

/*************************** RenameDisplayName ******************************/

void
RenameDisplayName ( obj, name )
int obj;
char * name;
{
  int ext;
  void SetDisplay_1_for_obj ();
  XmString xstr;

  SetDisplay_1_for_obj ( obj );
  val_ext ( &ext, obj );
  sprintf ( Display_1->name, "%s.%s", name, extens [ ext ] );
  xstr = XmStringCreateLtoR ( Display_1->name, charset );
  if ( Display_1->Main_offset != -1 ) {
    Main_1 = Main_0 + Display_1->Main_offset;
    XtVaSetValues ( Main_1->nme, XmNlabelString, xstr, NULL );
  }
  if ( Display_1->Provers_offset != -1 ) {
    Provers_1 = Provers_0 + Display_1->Provers_offset;
    XtVaSetValues ( Provers_1->nme, XmNlabelString, xstr, NULL );
  }
  if ( Display_1->Generators_offset != -1 ) {
    Generators_1 = Generators_0 + Display_1->Generators_offset;
    XtVaSetValues ( Generators_1->nme, XmNlabelString, xstr, NULL );
  }
  if ( Display_1->Translators_offset != -1 ) {
    Translators_1 = Translators_0 + Display_1->Translators_offset;
    XtVaSetValues ( Translators_1->nme, XmNlabelString, xstr, NULL );
  }
  if ( Display_1->Documents_offset != -1 ) {
    Documents_1 = Documents_0 + Display_1->Documents_offset;
    XtVaSetValues ( Documents_1->nme, XmNlabelString, xstr, NULL );
  }
  XmStringFree ( xstr );
}

/********************************* IsOpen **********************************/

int
IsOpen ( obj )
int obj;
{
  void SetDisplay_1_for_obj ();
  SetDisplay_1_for_obj ( obj );
  return ( Display_1->ps );
}

/********************************* IsMapObj **********************************/

int
IsMapObj ( obj )
int obj;
{
  int slen;
  void SetDisplay_1_for_obj ();

  SetDisplay_1_for_obj ( obj );
  slen = strlen ( Display_1->name );
  if ( ( Display_1->name [ slen - 3 ] == 'm' ) &&
       ( Display_1->name [ slen - 2 ] == 'a' ) &&
       ( Display_1->name [ slen - 1 ] == 'p' )    )
    return ( 1 );
  else
    return ( 0 );
}

/********************************* IsPrfObj **********************************/

int
IsPrfObj ( obj )
int obj;
{
  void SetDisplay_1_for_obj ();

  SetDisplay_1_for_obj ( obj );
  return ( ( Display_1->type == prf_gen ) != 0 );
}

/********************************* GetName **********************************/

char *
GetName ( obj )
int obj;
{
  void SetDisplay_1_for_obj ();

  SetDisplay_1_for_obj ( obj );
  return ( Display_1->name );
}

/******************************* GetShortName *******************************/

char *
GetShortName ( obj )
int obj;
{
  int i = 0;
  static char short_buf [ 50 ];
  void SetDisplay_1_for_obj ();

  SetDisplay_1_for_obj ( obj );
  strcpy ( short_buf, Display_1->name );
  while ( ( short_buf [ i ] != '\0' ) && ( short_buf [ i ] != '.' ) ) { i++; }
  short_buf [ i ] = '\0';  
  return ( ( char *) short_buf );
}

/****************************** ShortNameIsUsed *****************************/

int
ShortNameIsUsed ( name )
char * name;
{
  int found =0;

  Display_1 = Display_0;
  while ( ( ! found )                              &&
          ( Display_1 < Display_0 + DisplayTotal )    ) {
    found = ( ( strcmp ( name, GetShortName ( Display_1->obj ) ) == 0 ) != 0 );
    Display_1++;
  }
  return ( found );
}

/***************** LoadUsrConstructsInto_sel_strs ********************/

void
LoadUsrConstructsInto_sel_strs ()
{
  int ext;

  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( ( Display_1->type == usr ) || ( Display_1->type == usr_vhdl ) ) {
      strcpy ( sel_str_arr [ sel_arr_tot ], Display_1->name );
      sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
    }
  }
}

/******************* LoadAnlMchInto_sel_strs **********************/

void
LoadAnlMchInto_sel_strs ()
{
  int ext;

  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ext == mch ) {
      if ( IsAnl ( Display_1->obj ) ) {
        strcpy ( sel_str_arr [ sel_arr_tot ], Display_1->name );
        sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
      }
    }
  }
}

/******************* LoadAnlConstructsInto_sel_strs **********************/

void
LoadAnlConstructsInto_sel_strs ()
{
  int ext;

  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ( ext == mch ) || ( ext == ref ) || ( ext == imp ) ) {
      if ( IsAnl ( Display_1->obj ) ) {
        strcpy ( sel_str_arr [ sel_arr_tot ], Display_1->name );
        sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
      }
    }
  }
}

/******************* LoadIntroducableInto_sel_strs **********************/

void
LoadIntroducableInto_sel_strs ( dir )
char * dir;
{
  struct stat stat_buf;
  struct dirent * dirent_ptr;
  DIR * dp;
  int is_config;

  sel_arr_tot = 0;
  if ( ( dp = opendir ( dir ) ) == NULL ) {
     sprintf ( fifo_write_buf, " Problem with \"opendir %s\" ", dir );
     Popup_Err ( 0, fifo_write_buf );
     return;
  }

  while ( ( ( dirent_ptr = readdir ( dp ) ) != NULL ) &&
          ( sel_arr_tot < sel_arr_MAX )       ) {
    if ( strlen ( dirent_ptr->d_name ) > 5 ) {
      sprintf ( str_buf, "%s/%s", dir, dirent_ptr->d_name );
      if ( stat ( str_buf, &stat_buf ) != -1 ) {
        if ( S_ISDIR ( stat_buf . st_mode ) == 0 ) {
          if ( ( valid_filename_ext ( dirent_ptr->d_name ) ) ) {
            is_config = 0;
            strcpy ( str_buf, dirent_ptr->d_name );
            if ( strlen ( str_buf ) > 4 ) str_buf [ strlen ( str_buf ) - 4 ] = '\0';
            Display_1 = Display_0;
            while ( ( ! is_config )                          &&
                    ( Display_1 < Display_0 + DisplayTotal )    ) {
              if ( strcmp ( str_buf, GetShortName ( Display_1->obj ) ) == 0 ) {
                is_config = 1;
              }
              else {
                Display_1++;
	      }
            }
            if ( ! is_config ) {
              strcpy ( sel_str_arr [ sel_arr_tot++ ], dirent_ptr->d_name );
	    }
            else { /* IsConfigured - but check for `Rename_' */
              if ( ( ( dirent_ptr->d_name ) [ 0 ] == 'R' ) &&
                   ( ( dirent_ptr->d_name ) [ 1 ] == 'e' ) &&
                   ( ( dirent_ptr->d_name ) [ 2 ] == 'n' ) &&
                   ( ( dirent_ptr->d_name ) [ 3 ] == 'a' ) &&
                   ( ( dirent_ptr->d_name ) [ 4 ] == 'm' ) &&
                   ( ( dirent_ptr->d_name ) [ 5 ] == 'e' ) &&
                   ( ( dirent_ptr->d_name ) [ 6 ] == '_' )    ) {
/* causes duplication
                strcpy ( sel_str_arr [ sel_arr_tot++ ], dirent_ptr->d_name );
*/
                ;
	      }
            }
	  }
	}
      }
    }
  }

  closedir ( dp );

  Sort_sel_strs ();

  if ( sel_arr_tot >= sel_arr_MAX ) {
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    sprintf ( buf, "Max number of selections exceeded (%d)", sel_arr_MAX );
    Popup_Err ( 0, buf );
  }
}

/******************* LoadAnimateFilesInto_sel_strs **********************/

void
LoadAnimateFilesInto_sel_strs ( obj, ini_flag )
int obj, ini_flag;
{
  struct stat stat_buf;
  struct dirent * dirent_ptr;
  DIR * dp;
  int len, ll;

  sel_arr_tot = 0;
  if ( ini_flag == 1 ) {          /* Popup_EditAnimateFile */
    strcpy ( sel_str_arr [ sel_arr_tot++ ], "New ANIMATE script" );
  }
  else if ( ini_flag == 2 ) {     /* Popup_EditAnimateFile_NewFile */
    strcpy ( sel_str_arr [ sel_arr_tot++ ], "Empty ANIMATE script" );
  }
  len = strlen ( GetShortName ( obj ) );
  sprintf ( buf, "%s/SRC", cur_dir );
  if ( ( dp = opendir ( buf ) ) == NULL ) {
     sprintf ( fifo_write_buf, " Problem with \"opendir %s\" ", buf );
     Popup_Err ( 0, fifo_write_buf );
     return;
  }

  while ( ( ( dirent_ptr = readdir ( dp ) ) != NULL ) &&
          ( sel_arr_tot < sel_arr_MAX )       ) {
    if ( ( int ) strlen ( dirent_ptr->d_name ) > len + 4 ) {
      strcpy ( buf, dirent_ptr->d_name );
      if ( buf [ len ] == '.' ) {
        buf [ len ] = '\0';
        if ( strcmp ( buf, GetShortName ( obj ) ) == 0 ) {
          ll = strlen ( dirent_ptr->d_name );
          if ( ( ( dirent_ptr->d_name ) [ ll - 4 ] == '.' ) &&
               ( ( dirent_ptr->d_name ) [ ll - 3 ] == 'a' ) &&
               ( ( dirent_ptr->d_name ) [ ll - 2 ] == 'n' ) &&
               ( ( dirent_ptr->d_name ) [ ll - 1 ] == 'm' )    ) {
            if ( ini_flag == 2 ) {
              strcpy ( sel_str_arr [ sel_arr_tot ], "Template from: " );
              strcat ( sel_str_arr [ sel_arr_tot++ ], dirent_ptr->d_name );
	    }
            else {
              strcpy ( sel_str_arr [ sel_arr_tot++ ], dirent_ptr->d_name );
	    }
	  }
	}
      }
    }
  }

  closedir ( dp );

  if ( ( ini_flag == 1 ) || ( ini_flag == 2 ) )
    Sort_sel_strs_from_second ();
  else
    Sort_sel_strs ();

  if ( sel_arr_tot >= sel_arr_MAX ) {
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    sprintf ( buf, "Max number of selections exceeded (%d)", sel_arr_MAX );
    Popup_Err ( 0, buf );
  }
}

/******************* LoadOutputFilesInto_sel_strs **********************/

void
LoadOutputFilesInto_sel_strs ( obj )
int obj;
{
  struct stat stat_buf;
  struct dirent * dirent_ptr;
  DIR * dp;
  int len, ll;

  sel_arr_tot = 0;
  len = strlen ( GetShortName ( obj ) );
  sprintf ( buf, "%s/SRC", cur_dir );
  if ( ( dp = opendir ( buf ) ) == NULL ) {
     sprintf ( fifo_write_buf, " Problem with \"opendir %s\" ", buf );
     Popup_Err ( 0, fifo_write_buf );
     return;
  }

  while ( ( ( dirent_ptr = readdir ( dp ) ) != NULL ) &&
          ( sel_arr_tot < sel_arr_MAX )       ) {
    if ( ( int ) strlen ( dirent_ptr->d_name ) > len + 4 ) {
      strcpy ( buf, dirent_ptr->d_name );
      if ( buf [ len ] == '.' ) {
        buf [ len ] = '\0';
        if ( strcmp ( buf, GetShortName ( obj ) ) == 0 ) {
          ll = strlen ( dirent_ptr->d_name );
          if ( ( ( dirent_ptr->d_name ) [ ll - 4 ] == '.' ) &&
               ( ( dirent_ptr->d_name ) [ ll - 3 ] == 'o' ) &&
               ( ( dirent_ptr->d_name ) [ ll - 2 ] == 'u' ) &&
               ( ( dirent_ptr->d_name ) [ ll - 1 ] == 't' )    ) {
            strcpy ( sel_str_arr [ sel_arr_tot++ ], dirent_ptr->d_name );
	  }
	}
      }
    }
  }

  closedir ( dp );

  Sort_sel_strs ();

  if ( sel_arr_tot >= sel_arr_MAX ) {
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    sprintf ( buf, "Max number of selections exceeded (%d)", sel_arr_MAX );
    Popup_Err ( 0, buf );
  }
}

/************** LoadRefImpAnlIntroducableInto_sel_strs ****************/

void
LoadRefImpAnlIntroducableInto_sel_strs ()
{
  int cc, ext, type, ll;

  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    val_type ( &type, Display_1->obj );
    if ( ( type == usr || type == usr_vhdl ) && ( ext == mch || ext == ref ) ) {
      if ( IsAnl ( Display_1->obj ) ) {
        get_botref ( &cc, Display_1->obj );
        if ( cc == Display_1->obj ) {
          sprintf ( sel_str_arr [ sel_arr_tot ], Display_1->name );
          sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
        }
      }
    }
  }
}


/******************* LoadRemovableInto_sel_strs **********************/

void
LoadRemovableInto_sel_strs ()
{
  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( ( Display_1->type == usr )      ||
         ( Display_1->type == lib )      ||
         ( Display_1->type == usr_vhdl ) ||
         ( Display_1->type == lib_vhdl ) ||
         ( Display_1->type == prf_gen )     ) {
      sprintf ( sel_str_arr [ sel_arr_tot ], Display_1->name );
      sel_obj_arr [ sel_arr_tot ++] = Display_1->obj;
    }
  }
}

/******************** LoadITFableMchInto_sel_strs ***********************/

void
LoadITFableMchInto_sel_strs ()
{
  int ext, is_lib_enum, has_imp;

  sel_arr_tot = 0;
  for ( Display_2 = Display_0 ;
              Display_2 < Display_0 + DisplayTotal ; Display_2++ ) {
    val_ext ( &ext, Display_2->obj );
    if ( ext == mch ) {
      if ( IsAnl ( Display_2->obj ) ) {
        is_lib_enum = Is_LibOrEnm ( Display_2->obj );
        if ( Display_2->type == lib_vhdl ) is_lib_enum = 0;
        has_imp = HasImp ( Display_2->obj );
        if ( is_lib_enum || has_imp ) {
          sprintf ( str_buf, "%s.itf", GetShortName ( Display_2->obj ) );
          if ( ! ( IsConfigured ( str_buf ) ) ) {
            strcpy ( sel_str_arr [ sel_arr_tot ], Display_2->name );
            sel_obj_arr [ sel_arr_tot++ ] = Display_2->obj;
	  }
	}
      }
    }
  }
}

/*************** LoadOpenConstructsInto_sel_strs ********************/

void
LoadOpenConstructsInto_sel_strs ()
{
  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( Display_1->ps ) {
      if ( sel_arr_tot < sel_arr_MAX ) {
        strcpy ( sel_str_arr [ sel_arr_tot ], Display_1->name );
        sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
      }
    }
  }
}

/*************** LoadOpenEditedConstructsInto_sel_strs ********************/

void
LoadOpenEditedConstructsInto_sel_strs ()
{
  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( Display_1->ps ) {
      int file_diff = FileDiffIntoBcom ( Display_1->obj );
      if ( file_diff ) {
        if ( sel_arr_tot < sel_arr_MAX ) {
          strcpy ( sel_str_arr [ sel_arr_tot ], Display_1->name );
          sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
        }
      }
    }
  }
  if ( sel_arr_tot == sel_arr_MAX ) {
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    sprintf ( buf, "Maximum number of selections exceeded (%d)", sel_arr_MAX - 1 );
    Popup_Err ( 0, buf );
  }
}

/*************** LoadCre_VHDSLIB_ableInto_sel_strs ********************/

void
LoadCre_VHDSLIB_ableInto_sel_strs ()
{
  struct stat stat_buf;
  int ext;
  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ( ext == mch ) && ( Display_1->type == usr_vhdl ) ) {
      if ( IsAnl ( Display_1->obj ) ) {
/*
        sprintf ( fifo_write_buf, "%s/BLIB/LIB_VHDL/CFG/%s.mch",
                               BKIT_path, GetShortName ( Display_1->obj ) );
        if ( stat ( fifo_write_buf, &stat_buf ) != 0 ) {
          strcpy ( sel_str_arr [ sel_arr_tot ], GetShortName ( Display_1->obj ) );
          sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
	}
*/
        strcpy ( sel_str_arr [ sel_arr_tot ], GetShortName ( Display_1->obj ) );
        sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
      }
    }
  }
}

/****************** LoadNonOpsConstructsInto_sel_strs **********************/

void
LoadNonOpsConstructsInto_sel_strs ()
{
  int ext;

  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ( ext != ops ) && ( ext != map ) ) {
      strcpy ( sel_str_arr [ sel_arr_tot ], Display_1->name );
      sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
    }
  }
}

/****************** LoadCreSLIBableInto_sel_strs **************************/

void
LoadCreSLIBableInto_sel_strs ()
{
  int ext;
  struct stat stat_buf;

  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ext == mch ) {
      if ( Display_1->type != lib ) {
        if ( IsAnl ( Display_1->obj ) ) {
          sprintf ( fifo_write_buf, "%s/BLIB/LIB/CFG/%s", BKIT_path, Display_1->name );
          if ( stat ( fifo_write_buf, &stat_buf ) == -1 ) {
            strcpy ( sel_str_arr [ sel_arr_tot ], Display_1->name );
            sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
	  }
	}
      }
    }
  }
}

/****************** LoadBrowsableInto_sel_str **************************/

void
LoadBrowsableInto_sel_str ()
{
  int ext;

  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ( ext == mch ) || ( ext == ref ) || ( ext == imp ) ) {
      if ( IsAnl ( Display_1->obj ) ) {
        sprintf ( sel_str_arr [ sel_arr_tot ], Display_1->name );
        sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
      }
    }
  }
}

/****************** LoadRenamableInto_sel_strs **************************/

void
LoadRenamableInto_sel_strs ()
{
  int rr, ext;

  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( ( Display_1->type == usr ) || ( Display_1->type == usr_vhdl ) ) {
      val_ext ( &ext, Display_1->obj );
      switch ( ext ) {
      case mch:
      case ref:
      case imp:
        if ( ! ( IsAnl ( Display_1->obj ) ) ) {
          if ( ! Display_1->ps ) {
            strcpy ( sel_str_arr [ sel_arr_tot ], Display_1->name );
            sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
	  }
	}
        break;
      case doc:
        if ( ! ( IsDmu ( Display_1->obj ) ) ) {
          if ( ! Display_1->ps ) {
            strcpy ( sel_str_arr [ sel_arr_tot ], Display_1->name );
            sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
	  }
	}
        break;
      case itf:
      case bse:
      case enm:
        if ( ! ( IsGen1 ( Display_1->obj ) ) ) {
          if ( ! Display_1->ps ) {
            strcpy ( sel_str_arr [ sel_arr_tot ], Display_1->name );
            sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
	  }
	}
        break;
      }
    }
  }
}

/*********************** GetObjFromFullName **************************/

void
GetObjFromFullName ( obj, name )
int * obj;
char * name;
{
  SetDisplay_1_for_name ( name );
  if   ( Display_1 == Display_0 - 1 ) * obj = 0;
  else                                * obj = Display_1->obj;
/***
printf ( "GetObjFromFullName name=%s * obj=%d\n", name, * obj );
***/
}


/*********************** GetObjFromNameExt **************************/

void
GetObjFromNameExt ( obj, name, ext )
int * obj;
char * name;
int ext;
{
  sprintf ( buf, "%s.%s", name, extens [ ext ] );

  SetDisplay_1_for_name ( buf );
  if   ( Display_1 == Display_0 - 1 ) * obj = 0;
  else                                * obj = Display_1->obj;
}


/********************* GetPrfObjFromNameExtLvl ************************/

void
GetPrfObjFromNameExtLvl ( obj, name, prf_ext, nn, kill_if_not_found )
int * obj;
char * name;
int prf_ext, nn;
{
  int found = 0;
  if ( nn == -1 ) {            /* proof obligations */
    switch ( prf_ext ) {
    case mch_prf:
      sprintf ( buf, "%s.mch.prf", name );
      break;
    case ref_prf:
      sprintf ( buf, "%s.ref.prf", name );
      break;
    case imp_prf:
      sprintf ( buf, "%s.imp.prf", name );
      break;
    }
  }
  else {                      /* proofs level nn */
    switch ( prf_ext ) {
    case mch_prf:
      sprintf ( buf, "%s.mch.prf.%d", name, nn );
      break;
    case ref_prf:
      sprintf ( buf, "%s.ref.prf.%d", name, nn );
      break;
    case imp_prf:
      sprintf ( buf, "%s.imp.prf.%d", name, nn );
      break;
    }
  }

  SetDisplay_1_for_name ( buf );
  if ( Display_1 == Display_0 - 1 ) {
    if ( kill_if_not_found ) {
    printf ( "\n\n     Unable to locate Display object for %s", buf );
    BT_err_exit ( 13001 );
    }
    else {
      * obj = 0;
    }
  }
  else {
    * obj = Display_1->obj;
  }
}

/******************** GetMchRefImpObjFromNameExt ***********************/

void
GetMchRefImpObjFromNameExt ( mch_num, name )
int * mch_num;
char * name;
{
/***
printf("GetMchRefImpObjFromNameExt ( mch_num, %s )\n",name);
***/
  GetObjFromNameExt ( mch_num, name, mch );
  if ( * mch_num ) return;
  GetObjFromNameExt ( mch_num, name, ref );
  if ( * mch_num ) return;
  GetObjFromNameExt ( mch_num, name, imp );
  if ( * mch_num ) return;
  printf ( "\n\n     Unable to locate Display object for %s", name );
  BT_err_exit ( 13002 );
}

/************************** Cre_tcp_env *****************************/

void
Cre_tcp_env ()
{
/*
  :(Cfg|Anl|Usr|Dmu|Lvl|Ref|Prv|Gen|Trl|Lnk|EditorString|UsrVHDL|IsPASP|IsVHDL)
  appended to fifo_write_buf
*/
  int i, ext, st, su, cc, bb, prf_level, gen_by, ll, nn, ac,
      anl, dmu, trl, lnk, lenpob, fpob, ppob, lpob;
  strcat ( fifo_write_buf, ":(?" );

  /*** 
  Cfg
  ***/
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    strcat ( fifo_write_buf, "," );
    strcat ( fifo_write_buf, Display_1->name );
  }
  strcat ( fifo_write_buf, "|?" );

  /*** 
  Anl
  ***/
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ext == mch || ext == ref || ext == imp ) {
      val_curMRIState( &st, Display_1->obj );
      val_anl( &bb, st );
      if ( bb ) {
        strcat ( fifo_write_buf, "," );
        strcat ( fifo_write_buf, Display_1->name );
      }
    }
  }
  strcat ( fifo_write_buf, "|?" );

  /*** 
  Usr
  ***/
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( Display_1->type == usr ) {
      strcat ( fifo_write_buf, "," );
      strcat ( fifo_write_buf, Display_1->name );
    }
  }
  strcat ( fifo_write_buf, "|?" );

  /*** 
  Dmu
  ***/
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    def_curMRIState ( &bb, Display_1->obj );
    if ( bb ) {
      val_curMRIState ( &st, Display_1->obj );
      val_dmu ( &bb, st );
      if ( bb ) {
        strcat ( fifo_write_buf, "," );
        strcat ( fifo_write_buf, Display_1->name );
      }
    }
    else {
      def_prf_level ( &bb, Display_1->obj );
      if ( bb ) {
        val_prf_level ( &prf_level, Display_1->obj );
        val_gen_by ( &gen_by, Display_1->obj );
        val_curMRIState ( &st, gen_by );
        member_ppf_dmu ( &bb, st, prf_level );
        if ( bb ) {
          strcat ( fifo_write_buf, "," );
          strcat ( fifo_write_buf, Display_1->name );
	}
      }
      else {
        def_curGENState ( &bb, Display_1->obj );
        if ( bb ) {
          val_curGENState ( &st, Display_1->obj );
          val_gen_dmu ( &bb, st );
          if ( bb ) {
            strcat ( fifo_write_buf, "," );
            strcat ( fifo_write_buf, Display_1->name );
          }
        }
      }
    }
  }
  strcat ( fifo_write_buf, "|?" );
  /*** 
  Lvl
  ***/
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    def_curMRIState ( &bb, Display_1->obj );
    if ( bb ) {
      val_curMRIState ( &st, Display_1->obj );
      length_pob ( &bb, st );
      if ( bb ) {
        strcat ( fifo_write_buf, "," );
        strcat ( fifo_write_buf, Display_1->name );
        strcat ( fifo_write_buf, "(" );
        CreNumInBuf ( fifo_write_buf, bb-1 );
        strcat ( fifo_write_buf, ")" );
      }
    }
  }
  strcat ( fifo_write_buf, "|?" );

  /*** 
  Ref
  ***/
  first_Abs2Conc ( &ll, &ac );
  while ( ll != 0 ) {
    valIth_a2c ( &cc, ac, 1 );
    strcat ( fifo_write_buf, ";" );
    SetDisplay_1_for_obj ( cc );
    strcat ( fifo_write_buf, Display_1->name );
    i = 2;
    length_a2c ( &nn, ac );
    while ( i <= nn ) {
      valIth_a2c ( &cc, ac, i );
      if ( i != 1 ) {
        strcat ( fifo_write_buf, "," );
      }
      SetDisplay_1_for_obj ( cc );
      strcat ( fifo_write_buf, Display_1->name );
      i++;
    }
    next_Abs2Conc ( &ll, &ac, ll, ac );
  }
  strcat ( fifo_write_buf, "|?" );

  /*** 
  Prv
  ***/
  /*** see BMotif.c - look for ( a   b   c ) ***/
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    def_curMRIState ( &bb, Display_1->obj );
    if ( bb ) {
      val_curMRIState ( &st, Display_1->obj );
      length_pob ( &bb, st );
      if ( bb ) {
        val_curMRI ( &anl, &dmu, &trl, &lnk,
                       &lenpob, &fpob, &ppob, &lpob, Display_1->obj );
        lpob = correct_pob_for_btl ( lpob );
        strcat ( fifo_write_buf, "," );
        strcat ( fifo_write_buf, Display_1->name );
        strcat ( fifo_write_buf, "(" );
        CreNumInBuf ( fifo_write_buf, lpob );
        strcat ( fifo_write_buf, ":" );
        val_cptMRIState( &su, Display_1->obj );
        valIth_pob( &lpob, su, lenpob );
        lpob = correct_pob_for_btl ( lpob );
        CreNumInBuf ( fifo_write_buf, lpob );
        strcat ( fifo_write_buf, ")" );
      }
    }
  }
  strcat ( fifo_write_buf, "|?" );

  /*** 
  Gen
  ***/
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ext == bse || ext == enm || ext == itf ) {
      val_curGENState( &st, Display_1->obj );
      val_gen1( &bb, st );
      if ( bb ) {
        strcat ( fifo_write_buf, "," );
        strcat ( fifo_write_buf, Display_1->name );
      }
    }
  }
  strcat ( fifo_write_buf, "|?" );

  /*** 
  Trl
  ***/
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ext == imp ) {
      val_curMRIState( &st, Display_1->obj );
      val_trl( &bb, st );
      if ( bb ) {
        strcat ( fifo_write_buf, "," );
        strcat ( fifo_write_buf, Display_1->name );
      }
    }
  }
  strcat ( fifo_write_buf, "|?" );

  /*** 
  Lnk
  ***/
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ext == imp ) {
      val_curMRIState( &st, Display_1->obj );
      val_lnk( &bb, st );
      if ( bb ) {
        strcat ( fifo_write_buf, "," );
        strcat ( fifo_write_buf, Display_1->name );
      }
    }
  }
  strcat ( fifo_write_buf, "|\"" );

  /*** 
  EditorString
  ***/
  Retrieve_String ( editor_str_num, buf );
  strcat ( fifo_write_buf, buf );
  strcat ( fifo_write_buf, "\"|?" );

  /*** 
  UsrVHDL/GenVHDL
  ***/
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( Display_1->type == usr_vhdl || tt == gen_vhdl ) {
      strcat ( fifo_write_buf, "," );
      strcat ( fifo_write_buf, Display_1->name );
    }
  }

  strcat ( fifo_write_buf, "|?" );
  strcat ( fifo_write_buf, "|?)" );

/***
printf ( "BMotif - Cre_tcp_env:\n|%s|\n", fifo_write_buf );
***/

}

/************************** CreHtmlMasterFile **************************/

void
CreHtmlMasterFile ()
{
  int i, ext, st, anl;
  int cc, bb;
  FILE * html_file;
  struct stat stat_buf;
  int Prog_Language_Option;
  time_t time_now;

/***
printf ( "creating HTX/ConstructsSummary.html\n" );
***/

  html_file = fopen ( "HTX/ConstructsSummary.html", "w" );
  if ( html_file == NULL ) {
    printf( "\n  BMotif: can't open \"HTX/ConstructsSummary.html\" for writing\n" );
    BT_err_exit ( 0 );
    return;
  }

  fprintf (  html_file, "<HTML>\n<HEAD>\n <META NAME=\"Author\" CONTENT=\"%s\">\n  <META NAME=\"Description\" CONTENT=\"Summary of Hypertext Constructs for %s\">\n  <TITLE>Hypertext Constructs</TITLE>\n</HEAD>\n<BODY TEXT=\"#004EFF\" BGCOLOR=\"#CEDDCE\" LINK=\"#2A9BFF\" VLINK=\"#FF6565\" ALINK=\"#FF0000\">\n\n", toolkit_ver, cur_dir );

  fprintf (  html_file, "<CENTER>\n<IMG SRC=\"%s/BHELP/B.gif\" >\n<H2>Summary of Hypertext Constructs</H2>\n</CENTER>\n", BKIT_path );

  fprintf (  html_file, "\n<P><HR WIDTH=80%%><P>\n<H3>Analysed Constructs</H3>\n<MENU>\n" );

  for ( Display_2 = Display_0 ;
              Display_2 < Display_0 + DisplayTotal ; Display_2++ ) {
    val_ext ( &ext, Display_2->obj );
    if ( ( ext == mch ) || ( ext == ref ) || ( ext == imp ) ) {
      val_curMRIState ( &st, Display_2->obj );
      val_anl ( &anl, st );
      if ( anl ) {
        fprintf (  html_file, "  <LI><A HREF=\"%s.html\">%s</A>\n",
                                             Display_2->name, Display_2->name  );
      }
    }
  }


  fprintf (  html_file, "</MENU>\n\n<P><HR WIDTH=60%%><P>\n<H3>C Code Modules</H3>\n<MENU>\n" );

  for ( Display_2 = Display_0 ;
              Display_2 < Display_0 + DisplayTotal ; Display_2++ ) {
    val_ext ( &ext, Display_2->obj );
    if ( ( ext == mch ) || ( ext == ref ) || ( ext == imp ) ) {
      if ( Is_Trl ( Display_2->obj ) ) {
        get_topabs ( &cc, Display_2->obj );
        sprintf ( buf, "CDE/C/%s.c", GetShortName ( cc ) );
        if ( stat ( buf, &stat_buf ) != -1 ) {
          fprintf (  html_file, "  <LI><A HREF=\"%s.c.html\">%s.c</A>\n",
                                          GetShortName ( cc ), GetShortName ( cc ) );
          fprintf (  html_file, "  <LI><A HREF=\"%s.g.html\">%s.g</A>\n",
                                          GetShortName ( cc ), GetShortName ( cc ) );
          fprintf (  html_file, "  <LI><A HREF=\"%s.h.html\">%s.h</A>\n",
                                          GetShortName ( cc ), GetShortName ( cc ) );
	}
      }
    }    
  }


  time_now = time ( NULL );

  fprintf (  html_file, "</MENU>\n<P><HR WIDTH=80%%><P>\n<H3>On-line Help</H3>\n<MENU>\n<DD><A HREF=\"%s/BHELP/Contents.html\">Help Contents Page</A>\n<DD><A HREF=\"%s/BHELP/Index.html\">Index</A></DD>\n</MENU>\n<CENTER>\n<HR  WIDTH=33%% SIZE=2 COLOR=\"#CF6500\" NOSHADE>\n<FONT FACE=\"sans-serif, Arial, Helvetica\"><FONT COLOR=\"#CF6500\"><FONT SIZE=-2>Document Last Updated: %s<BR>\n<IMG SRC=\"%s/BHELP/B.gif\" VSPACE=5><BR>%s</FONT></FONT></FONT>\n<CENTER>\n<HR  WIDTH=33%% SIZE=2 COLOR=\"#CF6500\" NOSHADE>\n</CENTER>\n</BODY>\n</HTML>\n", BKIT_path, BKIT_path, ctime ( & time_now ), BKIT_path, toolkit_ver );
  fclose ( html_file );
  HtmlMasterFileChanged = 0;
}

/************************* NameAlreadyUsed ***********************/

int
NameAlreadyUsed ( name, obj )
char * name;
int obj;
{
  int present = 0;

  Display_1 = Display_0;
  while ( ( ! present )                              &&
          ( Display_1 < Display_0 + DisplayTotal ) )    {
    if ( ( Display_1->obj != obj )                                 &&
         ( strcmp ( GetShortName ( Display_1->obj ), name ) == 0 )    ) {
      present = 1;
    }
    Display_1++;
  }
  return ( present );
}

/******************** IsAlreadyPresentFromCompositeString *************/

int
IsAlreadyPresentFromCompositeString ( str )
char * str;
{
  int ext, ex;
  char name [ 50 ];
  int present = 0;

  GetNameFromString ( name, str );
  GetExtNumFromString ( &ext, str );

  Display_1 = Display_0;
  while ( ( ! present )                              &&
          ( Display_1 < Display_0 + DisplayTotal ) )    {
    if ( strcmp ( GetShortName ( Display_1->obj ), name ) == 0 ) {
      if ( ext == mch ) {
        val_ext ( &ex, Display_1->obj );
        if ( ex != itf ) present = 1;
      }
      else if ( ext != itf ) {
         present = 1;
      }
      else {
        val_ext ( &ex, Display_1->obj );
        if ( ex != mch ) present = 1;
      }
    }
    Display_1++;
  }
  return ( present );
}

/*********************** SaveInRemakableForm *************************/

void
SaveInRemakableForm ()
{

  FILE * Save;
  FILE * Bpda;
  FILE * Bpdan;
  FILE * CfgDepBase;
  int ac, ext, reset, bb, st;
  struct stat stat_buf;

  if ( stat ( primary_string, &stat_buf ) != -1 ) {
    sprintf ( buf, "  Directory \"%s\" already exists!  ", primary_string );
    Popup_Err ( 0, buf );
    return;
  }

  sprintf ( buf, "mkdir %s", primary_string );
  if ( system ( buf ) != 0 ) {
    sprintf ( buf, "  Cant create directory \"%s\" ", primary_string );
    Popup_Err ( 0, buf );
    return;
  }

  sprintf ( buf, "  \n  Saving to directory \"%s\" ...", primary_string );
  DisplayCurrWinText ( buf );

  Save_CfgDepBase ();  /* upper-case `S' - creates .Bpda */

  sprintf ( buf,
        "cd %s ; mkdir ANL CFG HTX PMD POB SRC TEX TYP CDE CDE/C", primary_string );
  execute ( buf );

  sprintf ( buf, "cp -r SRC/* %s/SRC 2> /dev/null", primary_string );
  system ( buf );

  sprintf ( buf, "cp -r PMD/* %s/PMD 2> /dev/null", primary_string );
  system ( buf );

  sprintf ( buf, "cp -r POB/*.btl %s/POB 2> /dev/null", primary_string );
  system ( buf );

  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
      val_ext ( &ext, Display_1->obj );
      if ( ( Display_1->type == usr ) || ( Display_1->type == usr_vhdl ) ) {
        if ( ( ext == mch ) || ( ext == ref ) || ( ext == imp ) || ( ext == doc ) ) {
        val_curMRIState ( &st, Display_1->obj );
        val_anl ( &bb, st );
        if ( bb ) {
          val_abs2conc ( &ac, Display_1->obj );
          vld_Abs2Conc ( &bb, ac );
          if ( bb ) {
            kill_Abs2Conc ( ac );
	  }
          rem_abs2conc ( Display_1->obj );
          def_sees_uses ( &bb, Display_1->obj );
          if ( bb ) rem_sees_uses ( Display_1->obj );
          def_inc_ipt ( &bb, Display_1->obj );
          if ( bb ) rem_inc_ipt ( Display_1->obj );
	}
        mod_anl ( st, FALSE );
        mod_dmu ( st, FALSE );
        if ( ext == doc ) {
          def_sees_uses ( &bb, Display_1->obj );
          if ( bb ) rem_sees_uses ( Display_1->obj );
        }
        mod_trl ( st, FALSE );
        mod_lnk ( st, FALSE );
        clear_pob ( st );
        clear_ppf ( st );
        clear_ppf_dmu ( st );
      }
      else if ( ext == itf || ext == bse || ext == enm ) {
        val_curGENState ( &st, Display_1->obj );
        mod_gen1 ( st, FALSE );
        mod_gen2 ( st, FALSE );
        mod_gen_dmu ( st, FALSE );
        def_sees_uses ( &bb, Display_1->obj );
        if ( bb ) rem_sees_uses ( Display_1->obj );
      }
      if   ( ext == map ) strcpy ( buf, "cp -r CDE/PASP/" );
      else                strcpy ( buf, "cp -r CFG/" );
      strcat ( buf, Display_1->name );
      strcat ( buf , " " );
      strcat ( buf, primary_string );
      if   ( ext == map ) strcat ( buf, "/CDE/PASP" );
      else                strcat ( buf, "/CFG" );
      execute ( buf );
/***
;printf("Save|%s|\n",buf);
***/
      }
    else {
      def_sees_uses ( &bb, Display_1->obj );
      if ( bb ) {
        rem_sees_uses ( Display_1->obj );
      }
      def_inc_ipt ( &bb, Display_1->obj );
      if ( bb ) {
        rem_inc_ipt ( Display_1->obj );
      }
      def_abs2conc ( &bb, Display_1->obj );
      if ( bb ) {
        val_abs2conc ( &ac, Display_1->obj );
        vld_Abs2Conc ( &bb, ac );
        if ( bb ) {
          kill_Abs2Conc ( ac );
	}
        rem_abs2conc ( Display_1->obj );
      }

      def_cptMRIState ( &bb, Display_1->obj );
      if ( bb ) {
        val_curMRIState ( &st, Display_1->obj );
/***
printf("killing (cur) MRIState object %d\n",st);
***/
        kill_MRIState ( st );
      }
      def_cptMRIState ( &bb, Display_1->obj );
      if ( bb ) {
        val_cptMRIState ( &st, Display_1->obj );
/***
printf("killing (cpt) MRIState object %d\n",st);
***/
        kill_MRIState ( st );
      }

      def_curGENState ( &bb, Display_1->obj );
      if ( bb ) {
        val_curGENState ( &st, Display_1->obj );
/***
printf("killing (cur) GENState object %d\n",st);
***/
        kill_GENState ( st );
      }
      def_cptGENState ( &bb, Display_1->obj );
      if ( bb ) {
        val_cptGENState ( &st, Display_1->obj );
/***
printf("killing (cpt) GENState object %d\n",st);
***/
        kill_GENState ( st );
      }
      kill_Construct ( Display_1->obj );
/***
printf("killing construct %d\n",Display_1->obj);
***/
    }
  }

  save_CfgDepBase ( &bb );  /* lower-case `S' - the underlying CFG_DEP_BSE ! */
  if ( ! bb ) {
    Popup_Err ( 0, "  BMotif: write CfgDepBase.dump error " );
    DisplayCurrWinText ( "\n  BMotif: write CfgDepBase.dump error\n" );
    return;    
  }

  /***
  open "save_dir"/.Bpda for writing & initialise
  ***/
  sprintf ( buf, "%s/.Bpda", primary_string );
  Bpda = fopen ( buf, "w" );
  if ( Bpda == NULL ) {
    sprintf ( primary_string, "\"%s\" for writing", buf );
    AbortedMsgFile ( primary_string );
    Kill_bplatform_and_exit ( 1, 0 );
  }

  /***
  write header
  ***/
  for ( j = 0 ; j < ( int ) strlen ( cur_hdr_string ) ; j++ ) {
    putc ( cur_hdr_string [ j ], Bpda );
  }
  
  /***
  write platform identifier
  ***/
  putc ( platform_ident, Bpda );

  /***
  open "save"/CfgDepBase.dump for reading
  ***/
  strcpy ( buf, "CfgDepBase.dump" );
  CfgDepBase = fopen ( buf, "r" );
  if ( CfgDepBase == NULL ) {
    sprintf ( primary_string, "\"%s\" for reading", buf );
    AbortedMsgFile ( primary_string );
    Kill_bplatform_and_exit ( 1, 0 );
  }

  /***
  append "save"/CfgDepBase.dump to "save"/.Bpda
  ***/
  c = getc ( CfgDepBase );
  while ( c != EOF ) {
    putc ( c, Bpda );
    c = getc ( CfgDepBase );
  }

  /***
  close "save"/CfgDepBase.dump & "save"/.Bpda
  ***/
  fclose ( CfgDepBase );
  fclose ( Bpda );

  /***
  remove CfgDepBase.dump
  ***/
  unlink ( "CfgDepBase.dump" );

  /***
  copy "save_dir"/.Bpda save_dir"/.Bpda_0
  ***/

  sprintf ( buf, "cp %s/.Bpda %s/.Bpda_0 ", primary_string, primary_string );
  execute ( buf );

  save_n_CfgDepBase ( &bb );
  if ( ! bb ) {
    Popup_Err ( 0, "  BMotif: write CfgDepBase.dump error " );
    DisplayCurrWinText ( "\n  BMotif: write CfgDepBase.dump error\n" );
    return;    
  }

  /***
  open "save"/.Bpdan for writing & initialise
  ***/
  strcpy ( buf, primary_string );
  strcat ( buf, "/.Bpdan" );
  Bpdan = fopen ( buf, "w" );
  if ( Bpdan == NULL ) {
    strcpy ( primary_string, "\"" );
    strcat ( primary_string, buf );
    strcat ( primary_string, "\" for writing" );
    AbortedMsgFile ( primary_string );
    Kill_bplatform_and_exit ( 1, 0 );
  }

  /***
  write header
  ***/
  for ( j = 0 ; j < ( int ) strlen ( cur_hdr_string ) ; j++ ) {
    c = htonl ( ( int ) cur_hdr_string [ j ] );
    fwrite( &c, sizeof ( int ), 1, Bpdan );
  }

  /***
  write platform identifier - this won't be used!
  ***/
  c = htonl ( platform_ident );
  fwrite( &c, sizeof ( int ), 1, Bpdan );

  /***
  open "save"/CfgDepBase.dump for reading
  ***/
  strcpy ( buf, "CfgDepBase.dump" );
  CfgDepBase = fopen ( buf, "r" );
  if ( CfgDepBase == NULL ) {
    sprintf ( primary_string, "\"%s\" for reading", buf );
    AbortedMsgFile ( primary_string );
    Kill_bplatform_and_exit ( 1, 0 );
  }

  /***
  append "save_dir"/CfgDepBase.dump to "save_dir"/.Bpdan
  ***/
  c = getc ( CfgDepBase );
  while ( c != EOF ) {
    putc ( c, Bpdan );
    c = getc ( CfgDepBase );
  }

  /***
  close "save_dir"/CfgDepBase.dump & "save_dir"/.Bpdan
  ***/
  fclose ( CfgDepBase );
  fclose ( Bpdan );

  /***
  remove CfgDepBase.dump
  ***/
  unlink ( "CfgDepBase.dump" );

  /***
  restore
  ***/

  Restore_CfgDepBase ();
  DisplayCurrWinText ( " done\n" );
  Sensitize ();
}

/*********************** ResetAllConstructs *************************/

void
ResetAllConstructs ()
{
  int ext;
  int reset_reqd = 0;

  Display_1 = Display_0;
  while ( ( ! reset_reqd )                         &&
          ( Display_1 < Display_0 + DisplayTotal )    ) {

    switch ( Display_1->type ) {

    case usr:
    case usr_vhdl:

      val_ext ( &ext, Display_1->obj );
      switch ( ext ) {
      case mch:
      case ref:
      case imp:
        reset_reqd = IsAnl ( Display_1->obj );
        break;
      case doc:
        reset_reqd = IsDmu ( Display_1->obj );
        break;
      case bse:
      case itf:
      case enm:
        reset_reqd = IsGen1 ( Display_1->obj );
        break;
      }  /* switch ( ext ) */
      break;

    case lib:
    case lib_vhdl:
        reset_reqd = IsDmu ( Display_1->obj );
        break;

    } /* switch ( Display_1->type ) */

    Display_1++;

  } /* while ... */

  if ( reset_reqd ) {
    Popup_ResetAll ();
  }
  else {
    Popup_Info ( "    Nothing to reset!      " );
    DisplayCurrentEnv ();
  }
}

/*********************** CloseAllOpenFilesAndQuit *************************/

void
CloseAllOpenFilesAndQuit ()
{
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    if ( Display_1->ps ) { KillProcess_Modify_ps ( Display_1->obj ); }
  }

  strcpy ( fifo_write_buf, "0:" );
  Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
  Save_n_CfgDepBase ();
  DisplayCurrWinText ( "\n  B-Toolkit Terminated\n\n" );
  InvokeB ( without_XTerm, 1 );
}

/********************** LoadAllConstructsInto_gset1 **********************/

void
LoadAllConstructsInto_gset1 ()
{
  int rr;

  clear_gset1 ();
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    add_gset1 ( &rr, Display_1->obj );
    chk_rep ( rr, 238 );
  }
}

/*********************** Pre_AnalyseGenerateAllConstructs *************************/

void
Pre_AnalyseGenerateAllConstructs ( int flag )
{
  int ext, rr;

  /***
  load sel_str_arr
  ***/

  sel_arr_tot = 0;

  for ( Display_1 = Display_0 ;
               Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {

    val_ext ( &ext, Display_1->obj );
    switch ( ext ) {

      case mch:
      case ref:
      case imp:
        if ( ! IsAnl ( Display_1->obj ) ) {
          if ( sel_arr_tot < sel_arr_MAX - 1 ) {
            sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   Analyse", 
                                                        Display_1->name );
            sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_NML );
	  }
	}
        break;

      case bse:
        if ( ! ( IsGen1 ( Display_1->obj ) ) ) {
          if ( sel_arr_tot < sel_arr_MAX - 1 ) {
            sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   GenBaseOperations", 
                                                        Display_1->name );
            sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_GBO );
	  }
	}
        if ( ! ( IsGen2 ( Display_1->obj ) ) ) {
          if ( sel_arr_tot < sel_arr_MAX - 1 ) {
            sel_arr_tog [ sel_arr_tot ] = 1;
            sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   GenBaseMachines", 
                                                        Display_1->name );
            sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_GBMI );
	  }
	}
        break;

      case enm:
        if ( ! ( IsGen1 ( Display_1->obj ) ) ) {
          if ( sel_arr_tot < sel_arr_MAX - 1 ) {
            
              sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   Enumerate", 
                                                        Display_1->name );
              sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                        Display_1->name, BT_ENUM );
	    
	  }
	}
        break;

    } /* switch ( ext ) */

  } /* for ( Display_1 = ... */

  if ( flag ) {
    if ( sel_arr_tot ) {
      Popup_Sel_flag = analyse_generate_jobs_selection;
      Popup_SelLarge_Dialog ( top_level, "Analyse/Generate jobs" );
    }
   else {
      Popup_Info ( "    No appropriate constructs   " );
    }
  }
}

/*********************** Pre_AnalyseGenerateTranslateAllConstructs *************************/

void
Pre_AnalyseGenerateTranslateAllConstructs ()
{
  int ext, rr;

  Pre_AnalyseGenerateAllConstructs ( 0 );

  /***
  append sel_str_arr
  ***/

  for ( Display_1 = Display_0 ;
               Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ext == imp ) {
      if ( ! Is_Trl ( Display_1->obj ) ) {
        if ( sel_arr_tot < sel_arr_MAX - 1 ) {
          sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   Translate",
                                                                Display_1->name );
          sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_TRL );
        }
      }
    }
  }

  if ( sel_arr_tot ) {
    Popup_Sel_flag = analyse_generate_jobs_selection;
    Popup_SelLarge_Dialog ( top_level, "Analyse/Generate/Translate jobs" );
  }
  else {
    Popup_Info ( "    No appropriate constructs   " );
  }
}



/******************************* Pre_Remake ******************************/

void
Pre_Remake ( option )
int option;
{
  int ext, rr;

  clear_gset1 ();
  if ( option == remake_all_constructs ) {
    if ( DisplayTotal ) {
      LoadAllConstructsInto_gset1 ();
      Remake ( not_dry_run );
    }
    else {
      Popup_Info ( "    No constructs configured   " );    
    }
  }
  else { /* option == remake_construct */
    /***
    load sel_str_arr
    ***/
    int reqd, cur, cpt, cur_val, cpt_val, rr;
    sel_arr_tot = 0;

    for ( Display_1 = Display_0 ;
               Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
      reqd = 0;
      val_ext ( &ext, Display_1->obj );
      switch ( ext ) {
      case mch:
      case ref:
      case imp:
      case doc:
        val_curMRIState ( &cur, Display_1->obj );
        val_cptMRIState ( &cpt, Display_1->obj );
        val_anl ( &cur_val, cur );
        val_anl ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          reqd = 1;
    	}
        length_pob ( &cur_val, cur );
        length_pob ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          reqd = 1;
    	}
        card_ppf ( &cur_val, cur );
        card_ppf ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          reqd = 1;
    	}
        card_ppf_dmu ( &cur_val, cur );
        card_ppf_dmu ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          reqd = 1;
        }
        val_trl ( &cur_val, cur );
        val_trl ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          reqd = 1;
        }
        val_lnk ( &cur_val, cur );
        val_lnk ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          reqd = 1;
        }
        val_dmu ( &cur_val, cur );
        val_dmu ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          reqd = 1;
        }
        card_ppf ( &cur_val, cur );
        card_ppf ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          reqd = 1;
    	}
        break;
      case bse:
      case enm:
      case itf:
        val_curGENState ( &cur, Display_1->obj );
        val_cptGENState ( &cpt, Display_1->obj );
        val_gen1 ( &cur_val, cur );
        val_gen1 ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          reqd = 1;
    	}
        val_gen2 ( &cur_val, cur );
        val_gen2 ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          reqd = 1;
    	}
        val_gen_dmu ( &cur_val, cur );
        val_gen_dmu ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          reqd = 1;
    	}
        break;
      } /* switch ( ext ) */

      if ( reqd ) {
        strcpy ( sel_str_arr [ sel_arr_tot ], Display_1->name );
        sel_obj_arr [ sel_arr_tot++ ] = Display_1->obj;
      }
    }
    if ( sel_arr_tot ) {
      Popup_Sel_flag = remake_constructs_selection;
      Popup_Sel_Dialog ( top_level, "Remake constructs" );
    }
    else {
      Popup_Info ( "    No appropriate constructs   " );
    }
  }
}

/******************************* Remake ******************************/

void
Remake ( option )
int option;
{
  int Remake_pog_Option, Remake_apr_Option, Remake_dmu_Option;
  int Remake_trl_Option, Remake_lnk_Option, Remake_itf_Option;
  int Remake_ppf_Option, Interface_Option, Prog_Language_Option;
  int ext, reset;
  int cur_pob;
  int cur, cpt;
  int cur_val, cpt_val;
  int rr, bb;

  valIth_flags ( &Prog_Language_Option, Prog_Language_Option_num );

  if ( ! auto_reset_and_remake ) {
    valIth_flags ( &Remake_pog_Option, Remake_pog_Option_num );
    valIth_flags ( &Remake_apr_Option, Remake_apr_Option_num );
    valIth_flags ( &Remake_ppf_Option, Remake_ppf_Option_num );
    valIth_flags ( &Remake_dmu_Option, Remake_dmu_Option_num );
    valIth_flags ( &Remake_trl_Option, Remake_trl_Option_num );
    valIth_flags ( &Remake_lnk_Option, Remake_lnk_Option_num );
    valIth_flags ( &Remake_itf_Option, Remake_itf_Option_num );
    valIth_flags ( &Interface_Option,  Interface_Option_num  );
  }
  else {
    if ( auto_timer ) {
      valIth_flags ( &Remake_pog_Option, Remake_pog_Option_num );
      valIth_flags ( &Remake_apr_Option, Remake_apr_Option_num );
      valIth_flags ( &Remake_ppf_Option, Remake_ppf_Option_num );
      valIth_flags ( &Remake_dmu_Option, Remake_dmu_Option_num );
      valIth_flags ( &Remake_trl_Option, Remake_trl_Option_num );
      valIth_flags ( &Remake_lnk_Option, Remake_lnk_Option_num );
      valIth_flags ( &Remake_itf_Option, Remake_itf_Option_num );
      valIth_flags ( &Interface_Option,  Interface_Option_num  );
    }
    else {
      Remake_pog_Option = 1;
      Remake_apr_Option = 1;
      Remake_ppf_Option = 1;
      Remake_dmu_Option = 1;
      Remake_trl_Option = 1;
      Remake_lnk_Option = 1;
      Remake_itf_Option = 1;
      Interface_Option  = 1;
    }
  }

  sel_arr_tot = 0;
  for ( Display_1 = Display_0 ;
              Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    curr_obj = Display_1->obj;
    member_gset1 ( &bb, Display_1->obj );
    if ( bb ) {

      val_ext ( &ext, Display_1->obj );

      switch ( ext ) {

      case mch:
      case ref:
      case imp:
      case doc:

        val_curMRIState ( &cur, Display_1->obj );
        val_cptMRIState ( &cpt, Display_1->obj );

        val_anl ( &cur_val, cur );
        val_anl ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          if ( ! cpt_val ) {
            BT_err_exit ( 14 );
            return;
          }
          if ( sel_arr_tot < sel_arr_MAX - 1 ) {
            sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   Analyse", 
                                                        Display_1->name );
            sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_NML );
	  }
	}

        if ( Remake_pog_Option ) {
          length_pob ( &cur_val, cur );
          length_pob ( &cpt_val, cpt );
          if ( cur_val != cpt_val ) {
            if ( cur_val > cpt_val ) {
              BT_err_exit ( 18 );
              return;
            }
            if ( cur_val == 0 ) {
              if ( sel_arr_tot < sel_arr_MAX - 1 ) {
                sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   POGenerate", 
                                                        Display_1->name );
                sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_POG );
	      }
	    }
	  }
	}

        if ( Remake_apr_Option ) {
          length_pob ( &cur_val, cur );
          length_pob ( &cpt_val, cpt );
          if ( cur_val != cpt_val ) {
            if ( cur_val > cpt_val ) {
              BT_err_exit ( 18 );
              return;
            }
            if ( cur_val == 0 ) {
              cur_val = 1;
	    }
            while ( cpt_val > cur_val ) {
              int btl_prf;
              valIth_pob( &cur_pob, cpt, cur_val + 1 );
              btl_prf = ( ( cur_pob < 0 ) != 0 );
              if ( sel_arr_tot < sel_arr_MAX - 1 ) {
                if ( btl_prf ) {
                  sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   BToolProve Level %d",
                                    Display_1->name, cur_val - 1 );
                  sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s.%d:%d:0",
                                    Display_1->name, cur_val - 1, BT_BTL_AUP_INI );
		}
                else {
                  sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   AutoProve Level %d",
                                    Display_1->name, cur_val - 1 );
                  sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s.%d:%d:0",
                                    Display_1->name, cur_val - 1, BT_AUP );
		}
	      }
              cur_val++;
	    }
	  }
	}

        if ( Remake_ppf_Option ) {
          int i, bb, nn;
          card_ppf ( &cur_val, cur );
          card_ppf ( &cpt_val, cpt );
          if ( cur_val != cpt_val ) {
            if ( cur_val > cpt_val ) {
              BT_err_exit ( 64 );
              return;
	    }
            i = 1;
            while ( i <= cpt_val ) {
              valOrd_ppf ( &nn, cpt, i );
              member_ppf ( &bb, cur, nn );
              if ( ! bb ) {
                if ( sel_arr_tot < sel_arr_MAX - 1 ) {
                  if ( nn ) {
                    sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   PrintProof Level %d",
                                                 Display_1->name, nn - 1 );
                    sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:%d",
                                                 Display_1->name, BT_PFP_RMK, nn );
		  }
                  else {
                    sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   PrintProof Obligations",
                                                 Display_1->name, nn - 1 );
                    sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:%d",
                                                 Display_1->name, BT_PFP_RMK, nn );
		  }
		}
	      }
              i++;
	    }
	  }
	}

        if ( Remake_trl_Option ) {
          val_trl ( &cur_val, cur );
          val_trl ( &cpt_val, cpt );
          if ( cur_val != cpt_val ) {
            if ( ! cpt_val ) {
              BT_err_exit ( 16 );
              return;
            }
            if ( sel_arr_tot < sel_arr_MAX - 1 ) {
              
                
              sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   Translate",
                                                                Display_1->name );
	        
	      
              sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_TRL );
	    }
	  }
	}

        if ( Remake_lnk_Option ) {
          val_lnk ( &cur_val, cur );
          val_lnk ( &cpt_val, cpt );
          if ( cur_val != cpt_val ) {
            if ( ! cpt_val ) {
              BT_err_exit ( 17 );
              return;
            }
            if ( sel_arr_tot < sel_arr_MAX - 1 ) {
              
              sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   Link",
                                                                Display_1->name );
	      
              sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_LNK );
	    }
	  }
	}

        if ( Remake_dmu_Option ) {
          val_dmu ( &cur_val, cur );
          val_dmu ( &cpt_val, cpt );
          if ( cur_val != cpt_val ) {
            if ( ! cpt_val ) {
              BT_err_exit ( 15 );
              return;
            }
            if ( sel_arr_tot < sel_arr_MAX - 1 ) {
              sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   DocumentMarkUp",
                                                                Display_1->name );
              if ( ext == doc ) {
                sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_DOC );
	      }
              else {
                sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_DMU );
	      }
	    }
	  }
	}

        if ( Remake_dmu_Option ) {
          int i, bb, nn;
          card_ppf_dmu ( &cur_val, cur );
          card_ppf_dmu ( &cpt_val, cpt );
          if ( cur_val != cpt_val ) {
            if ( cur_val > cpt_val ) {
              BT_err_exit ( 64 );
              return;
	    }
            i = 1;
            while ( i <= cpt_val ) {
              valOrd_ppf_dmu ( &nn, cpt, i );
              member_ppf_dmu ( &bb, cur, nn );
              if ( ! bb ) {
                if ( sel_arr_tot < sel_arr_MAX - 1 ) {
                  if ( nn ) {
                    sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   DocumentMarkUp Proof Level %d",
                                                             Display_1->name, nn );
		  }
                  else {
                    sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   DocumentMarkUp Proof Obligations",
                                                             Display_1->name );
		  }
                  sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:%d",
                                                 Display_1->name, BT_DMU_RMK, nn );
		}
	      }
              i++;
	    }
	  }
	}

        break;

      case bse:

        val_curGENState ( &cur, Display_1->obj );
        val_cptGENState ( &cpt, Display_1->obj );

        val_gen1 ( &cur_val, cur );
        val_gen1 ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          if ( cur_val && ! cpt_val ) {
            BT_err_exit ( 27 );
            return;
          }
          if ( sel_arr_tot < sel_arr_MAX - 1 ) {
            sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   GenBaseOperations", 
                                                        Display_1->name );
            sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_GBO );
	  }
	}

        val_gen2 ( &cur_val, cur );
        val_gen2 ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          if ( cur_val && ! cpt_val ) {
            BT_err_exit ( 27 );
            return;
          }
          if ( sel_arr_tot < sel_arr_MAX - 1 ) {
            sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   GenBaseMachines", 
                                                        Display_1->name );
            sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_GBMI );
	  }
	}

        if ( Remake_dmu_Option ) {
          val_gen_dmu ( &cur_val, cur );
          val_gen_dmu ( &cpt_val, cpt );
          if ( cur_val != cpt_val ) {
            if ( ! cpt_val ) {
              BT_err_exit ( 15 );
              return;
            }
            if ( sel_arr_tot < sel_arr_MAX - 1 ) {
              sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   DocumentMarkUp", 
                                                        Display_1->name );
              sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_DMU );
	    }
	  }
	}
      
        break;

      case enm:

        val_curGENState ( &cur, Display_1->obj );
        val_cptGENState ( &cpt, Display_1->obj );

        val_gen1 ( &cur_val, cur );
        val_gen1 ( &cpt_val, cpt );
        if ( cur_val != cpt_val ) {
          if ( cur_val && ! cpt_val ) {
            BT_err_exit ( 29 );
            return;
          }

          if ( sel_arr_tot < sel_arr_MAX - 1 ) {
            
              sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   Enumerate", 
                                                        Display_1->name );
              sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                        Display_1->name, BT_ENUM );
	    
	  }
	}

        if ( Remake_dmu_Option ) {
          val_gen_dmu ( &cur_val, cur );
          val_gen_dmu ( &cpt_val, cpt );
          if ( cur_val != cpt_val ) {
            if ( ! cpt_val ) {
              BT_err_exit ( 15 );
              return;
            }
            if ( sel_arr_tot < sel_arr_MAX - 1 ) {
              sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   DocumentMarkUp", 
                                                        Display_1->name );
              sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_DMU );
	    }
	  }
	}
      
        break;

      case itf:

        val_curGENState ( &cur, Display_1->obj );
        val_cptGENState ( &cpt, Display_1->obj );
        if ( ( Remake_itf_Option )                                 &&
             ( Prog_Language_Option != Prog_Language_Option_PASP )    ) {
          val_gen1 ( &cur_val, cur );
          val_gen1 ( &cpt_val, cpt );
          if ( cur_val != cpt_val ) {
            if ( cur_val && ! cpt_val ) {
              BT_err_exit ( 60 );
              return;
            }
            if ( sel_arr_tot < sel_arr_MAX - 1 ) {
              if ( Interface_Option == Interface_Option_Motif ) {
                sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   Generate Motif Interface", 
                                                        Display_1->name );
                sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                    Display_1->name, BT_CIO_CIOM );
	      }
              else {
                sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   Generate Non-Motif Interface", 
                                                        Display_1->name );
                sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                    Display_1->name, BT_CIO_CIOM );
	      }
	    }
	  }
	}

        if ( Remake_dmu_Option ) {
          val_gen_dmu ( &cur_val, cur );
          val_gen_dmu ( &cpt_val, cpt );
          if ( cur_val != cpt_val ) {
            if ( ! cpt_val ) {
              BT_err_exit ( 15 );
              return;
            }
            if ( sel_arr_tot < sel_arr_MAX - 1 ) {
              sprintf ( sel_str_arr [ sel_arr_tot ], "%s:   DocumentMarkUp", 
                                                        Display_1->name );
              sprintf ( rmk_str_arr [ sel_arr_tot++ ], "%s:%d:0",
                                                        Display_1->name, BT_DMU );
	    }
	  }
	}

      }        /* switch ( ext ) */

    }        /* if member_gset1 */

  }      /* for ... */

  if ( ! auto_reset_and_remake ) {
    if ( option == not_dry_run ) {
      if ( sel_arr_tot ) {
        Popup_Sel_flag = remake_jobs_selection;
        Popup_SelLarge_Dialog ( top_level, "Remake jobs" );
      }
      else if (  ! Remake_dmu_Option ||
                 ! Remake_trl_Option ||
                 ! Remake_lnk_Option ||
                 ! Remake_pog_Option ||
                 ! Remake_ppf_Option ||
                 ! Remake_apr_Option ||
                 ! Remake_itf_Option    ) {
        Popup_Info ( "    No remake required (check Remake Options)   " );
      }
      else {
        Popup_Info ( "    No remake required!    " );
      }
    }
  }
  else if ( ! auto_reset ) { /* auto_reset_and_remake */
    if ( sel_arr_tot ) {
      for ( i = 0 ; i < sel_arr_tot ; i++ ) sel_arr_tog [ i ] = 1;
      RemakeSelections ( remake_jobs_selection );
    }
    else if ( ! upgrade3T04_flag ) {
      DisplayCurrWinText ( "\n  No remake required!\n" );
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
      InvokeB ( without_XTerm, 1 );
    }
  }
}

/*************************** RecompileLibCodeFiles **************************/

void
RecompileLibCodeFiles ( interface_flag )
int interface_flag;
{
  int ext, Prog_Language_Option, Interface_Option;
  int msg_not_printed = 1;

/***
printf ( "RecompileLibCodeFiles ( interface_flag=%d )\n", interface_flag );
***/
    for ( Display_1 = Display_0 ;
                Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {

    val_ext ( &ext, Display_1->obj );
    if ( ( ext == mch )                                                       &&
         ( ( Display_1->type == lib ) || ( Display_1->type == enm_gen ) )    ) {
/***
printf( "Recompiling |%s|\n", name );
***/
      if ( msg_not_printed ) {
        msg_not_printed = 0;
        Popup_Info ( "  Recompiling library modules " );
        XmUpdateDisplay ( top_level );
        DeSensitize ();
        XmUpdateDisplay ( top_level );
        if ( interface_flag == 2 ) {
          DisplayCurrWinText ( "\n  Recompiling library code ... " );
	}
        else if ( interface_flag == 1 ) {
          DisplayCurrWinText ( "\n  Programming language changed;\n  recompiling library code ... " );
	}
        else {
          DisplayCurrWinText ( "\n  Programming language changed;\n  recompiling library code ... " );
	}
      }

      sprintf ( buf, "CDE/C/%s.o", GetShortName ( Display_1->obj ) );
      unlink ( buf );
/***
printf ( " unlink %s\n", buf );
***/
      Retrieve_String ( cc_compiler_str_num, str_buf );
      valIth_flags ( &Interface_Option, Interface_Option_num );
      valIth_flags ( &Prog_Language_Option, Prog_Language_Option_num );
      if ( Prog_Language_Option == Prog_Language_Option_ANSI_C ) {
        if ( Interface_Option == Interface_Option_Motif ) {
          sprintf ( buf, "cd CDE/C ; %s -D_BT_ANSIC -D_BT_Motif -c %s.c", 
                                      str_buf, GetShortName ( Display_1->obj ) );
	}
        else {
          sprintf ( buf, "cd CDE/C ; %s -D_BT_ANSIC -c %s.c", 
                                      str_buf, GetShortName ( Display_1->obj ) );
	}
      }
      else {
        if ( Interface_Option == Interface_Option_Motif ) {
          sprintf ( buf, "cd CDE/C ; %s -D_BT_Motif -c %s.c", 
                                      str_buf, GetShortName ( Display_1->obj ) );
	}
        else {
          sprintf ( buf, "cd CDE/C ; %s -c %s.c", 
                                      str_buf, GetShortName ( Display_1->obj ) );
	}
      }
      execute ( buf );
/***
printf("  |%s|\n",buf);
***/
    }
  }
  if ( ! msg_not_printed ) {
    DisplayCurrWinText ( "done\n" );
    Sensitize ();
  }
}

/******************************* ResetAllCode ******************************/

void
ResetAllCode ( desensitize_flag )
int desensitize_flag;
{
  int ext, st, bb;

  if ( desensitize_flag ) { DeSensitize (); }
  for ( Display_1 = Display_0 ;
                Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );
    if ( ext == imp ) {
      def_curMRIState ( &bb, Display_1->obj );
      if ( bb ) {
        val_curMRIState ( &st, Display_1->obj );
        val_trl ( &bb, st );
        if ( bb ) {
          mod_trl ( st, FALSE );
          mod_lnk ( st, FALSE );
          RemoveCodeFiles ( Display_1->obj );
          Display_1->changed = 1;
          MasterChanged = 1;
	}
      }
    }
    else if ( ext == itf ) {
      def_curGENState ( &bb, Display_1->obj );
      if ( bb ) {
        val_curGENState ( &st, Display_1->obj );
        val_gen2 ( &bb, st );            /* motif itf */
        if ( bb ) {
          mod_gen1 ( st, FALSE );
          mod_gen2 ( st, FALSE );
          RemoveCodeFiles ( Display_1->obj );
          sprintf ( buf, "\n  Reset %s and its dependent constructs",
                                                               Display_1->name );
          DisplayCurrWinText ( buf ); 
          Display_1->changed = 1;
          MasterChanged = 1;
	}
      }
    }


  } /* for Display_1 ... */

  if ( MasterChanged ) {
    DisplayCurrWinText ( "\n  All non-library code reset\n" );
    HtmlMasterFileChanged = 1;
  }
  else {
    if ( desensitize_flag ) {
      Popup_Info ( "    No code to remove!    " );
    }
  }
  if ( desensitize_flag ) DisplayCurrentEnv ();
}

/**************************** ResetAllInterfaces ****************************/

void
ResetAllInterfaces ()
{
  int rr, mm, nn, ext, st, bb;

  for ( Display_3 = Display_0 ;
                Display_3 < Display_0 + DisplayTotal ; Display_3++ ) {
    val_ext ( &ext, Display_3->obj );
    if ( ext == itf ) {
      def_curGENState ( &bb, Display_3->obj );
      if ( bb ) {
        val_curGENState ( &st, Display_3->obj );
        val_gen1 ( &bb, st );
        if ( bb ) {
          Load_SRC_CFG_Names ( Display_3->obj );
          top_level_dep_cstr = Display_3->obj;
          Get_Code_Dep ( Display_3->obj );
          card_gset5 ( &mm );
          top_level_dep_cstr = Display_3->obj;
          get_dep_cstr ( &rr, Display_3->obj );
          chk_rep ( rr, 67 );
          card_gset1 ( &nn );
          if   ( ( nn == 0 ) && ( mm == 0 ) ) ResetConstruct ( Display_3->obj, 0 );
          else                                ResetConstruct ( Display_3->obj, 1 );
	}
      }
    }
  }
}

/************************* RemoveAllMarkedUpDocuments **********************/

void
RemoveAllMarkedUpDocuments ()
{
  int ext, gen_by, prf_level, st, bb, buf, reset;

  DeSensitize ();
  for ( Display_1 = Display_0 ;
                Display_1 < Display_0 + DisplayTotal ; Display_1++ ) {
    val_ext ( &ext, Display_1->obj );

    switch ( ext ) {

    case mch:
    case ref:
    case imp:
    case doc:
      val_curMRIState ( &st, Display_1->obj );
      val_dmu ( &bb, st );
      if ( bb ) {
        mod_dmu ( st, False );
        if ( ext == doc ) {
          def_sees_uses ( &bb, Display_1->obj );
          if ( bb ) rem_sees_uses ( Display_1->obj );
        }
        RemoveTexFiles ( Display_1->obj );
        Display_1->changed = 1;
        MasterChanged = 1;
      }
      break;

    case bse:
    case enm:
    case itf:
      val_curGENState ( &st, Display_1->obj );
      val_gen_dmu ( &bb, st );
      if ( bb ) {
        mod_gen_dmu ( st, False );
        RemoveTexFiles ( Display_1->obj);
        Display_1->changed = 1;
        MasterChanged = 1;
      }
      break;

    case mch_prf:
    case ref_prf:
    case imp_prf:
      val_gen_by ( &gen_by, Display_1->obj );
      val_prf_level ( &prf_level, Display_1->obj );
      val_curMRIState ( &st, gen_by );
      member_ppf_dmu ( &bb, st, prf_level );
      if ( bb ) {
        del_ppf_dmu ( st, prf_level );
        RemoveTexFiles ( Display_1->obj );
        Display_1->changed = 1;
        MasterChanged = 1;
      }
      break;

    } /* switch ( Display_1->ext ) */

  } /* for ( Display_1 ... */

  if   ( MasterChanged ) Popup_Info ( "All Marked-up Documents reset" );
  else                   Popup_Info ( "    No Marked-up Documents to reset!    " );

  DisplayCurrentEnv ();
}

/**************** auto_reset_and_remake_OR_upgrade_Reset ***************/

void
auto_reset_and_remake_OR_upgrade_Reset ()
{
  int nn, obj, type, ext;
  int reset_msg_displayed = 0;

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

      switch ( ext ) {

      case mch:
      case ref:
      case imp:

        CheckUnanalyse ( obj, 1 );
        if ( ( MasterChanged ) && ( ! reset_msg_displayed ) ) {
          DisplayCurrWinText ( "\n  Resetting all constructs ..." );
          reset_msg_displayed = 1;
	}
        break;

      case doc:

        CheckUndoc ( obj );
        if ( ( MasterChanged ) && ( ! reset_msg_displayed ) ) {
          DisplayCurrWinText ( "\n  Resetting all constructs ..." );
          reset_msg_displayed = 1;
	}
        break;

      case bse:
      case ops:
      case enm:
      case itf:

        CheckUngen ( obj );
        if ( ( MasterChanged ) && ( ! reset_msg_displayed ) ) {
          DisplayCurrWinText ( "\n  Resetting all constructs ..." );
          reset_msg_displayed = 1;
	}
        break;

      case map:

        rem_sees_uses ( obj );
        KillConstruct ( obj );
        if ( ( MasterChanged ) && ( ! reset_msg_displayed ) ) {
          DisplayCurrWinText ( "\n  Resetting all constructs ..." );
          reset_msg_displayed = 1;
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
      if ( ( MasterChanged ) && ( ! reset_msg_displayed ) ) {
        DisplayCurrWinText ( "\n  Resetting all constructs ..." );
        reset_msg_displayed = 1;
      }
      break;

    case lib:
    case lib_vhdl:
        CheckUndoc ( obj );
        if ( ! reset_msg_displayed ) {
          DisplayCurrWinText ( "\n  Resetting all constructs ..." );
          reset_msg_displayed = 1;
        }
        break;

    } /* switch ( type ) ) */

    nn--;

  } /* while ( nn ) */

  if ( reset_msg_displayed ) {
    DisplayCurrWinText ( " done\n" );
    DisplayCurrentEnv ();
  }
  else {
    DisplayCurrWinText ( "\n  Nothing to reset!\n" );
  }
}
