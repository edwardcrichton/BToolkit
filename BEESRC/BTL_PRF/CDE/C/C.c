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
#include <Xm/XmAll.h>
#include <stdio.h>

#include "btl_proof_file_dump.g"
#include "basic_io.g"
#include "String_TYPE.g"
#include "Bool_TYPE.g"
#include "Scalar_TYPE.g"
#include "btl_proofCtx.g"
#include "Test.g"
#include "file_dump.g"

#include "btl_proof_file_dump.h"
#include "basic_io.h"
#include "String_TYPE.h"
#include "Bool_TYPE.h"
#include "Scalar_TYPE.h"
#include "btl_proofCtx.h"
#include "Test.h"
#include "file_dump.h"

Display *display___;
Widget top_level___, main_form___, prog_label___, B_prog_icon___, monolog_frame___, monolog_text___, done_but___;
XtAppContext app___;
XmString xstr___;
XmStringCharSet charset___ = (XmStringCharSet) XmSTRING_DEFAULT_CHARSET;
int mc_int___,wait_flag___,sec_visit___,sel_one___;
int nx___, ny___, pnx___, pny___;
FILE * Bcom___;
char buf___ [ 2000 ];
Pixmap B_framed_pixmap_gray95___;
int c_arr___ [ 1001 ];
void DisplayMWText___ ();
void AppNumToBuf___ ();


#define open_Bcom___ \
  Bcom___ = fopen ( ".Bcom", "r" ); \
  if ( Bcom___  == NULL ) { \
    printf ( "  \n\nMotif Interface:\n\n  Couldn't open .Bcom for reading\n\n" ); \
    exit ( 1 ); \
  }

#define close_Bcom___ fclose ( Bcom___ )

#define upd_pos___(x___,y___) \
  if ( x___ > nx___ + 15 || \
       x___ < nx___ - 15 || \
       y___ > ny___ + 15 || \
       y___ < ny___ - 15    ) { \
    pnx___ = nx___; \
    pny___ = ny___; \
    nx___ = x___; \
    ny___ = y___; \
  }

#define ini_prompt___(n1,n2) \
  strcpy ( buf___, "$BKIT/BLIB/BPrompt " ); \
  AppNumToBuf___ ( n1 ); \
  strcat ( buf___, " " ); \
  AppNumToBuf___ ( n2 )

#define cat_prompt___(s1,n1,n2) \
  strcat ( buf___, " \"" ); \
  strcat ( buf___, s1 ); \
  strcat ( buf___, "\" " ); \
  AppNumToBuf___ ( n1 ); \
  strcat ( buf___, " " ); \
  AppNumToBuf___ ( n2 )

#define cat_prompt_enm___(s1,n1,s2) \
  strcat ( buf___, " \"" ); \
  strcat ( buf___, s1 ); \
  strcat ( buf___, "\" " ); \
  AppNumToBuf___ ( n1 ); \
  strcat ( buf___, " " ); \
  strcat ( buf___, " \"" ); \
  strcat ( buf___, s2 ); \
  strcat ( buf___, "\" " );

#define nonws_Bcom___ \
  n___ = getc ( Bcom___ ); \
  while ( n___ == ' ' ) n___ = getc ( Bcom___ ) 

#define nat_Bcom___(n) \
  nonws_Bcom___; \
  n = 0; \
  while ( n___ != ( char ) 17 && n___ != EOF ) { \
    n = ( 10 * n ) + n___ - '0'; \
    n___ = getc ( Bcom___ ); \
  }

#define str_Bcom___(s) \
  nonws_Bcom___; \
  i___ = 0; \
  while ( n___ != ( char ) 17 && n___ != EOF ) { \
    s [ i___ ] = ( char ) n___; \
    i___++; \
    n___ = getc ( Bcom___ ); \
  } \
  s [ i___ ] = '\0'

#define chr_Bcom___(c) \
  c = ( char ) getc ( Bcom___ ) ; \
  n___ = getc ( Bcom___ )

#define bts_Bcom___(n) \
  nonws_Bcom___; \
  n = 0; \
  while ( n___ != ( char ) 17 && n___ != EOF ) { \
    n = ( 2 * n ) + n___ - '0'; \
    n___ = getc ( Bcom___ ); \
  }

void
NWL_M ( n___ )
int n___;
{
  int i___ = 1;
  while( i___ <= n___ ) {
    DisplayMWText___ ( "\n" );
    i___ = i___ + 1;
  }
}

void
BLK_M ( n___ )
int n___;
{
  int i___ = 1;
  while( i___ <= n___ ) {
    DisplayMWText___ ( " " );
    i___ = i___ + 1;
  }
}

void
PUT_NAT_M ( n___ )
int n___;
{
  buf___ [ 0 ] = '\0';
  AppNumToBuf___ ( n___ );
  DisplayMWText___ ( buf___ );
}

void
PUT_CHR_M ( c___ )
int c___;
{
  buf___ [ 0 ] = ( char ) c___ ;
  buf___ [ 1 ] = '\0';
  DisplayMWText___ ( buf___ );
}

void
PUT_STR_M ( s___ )
int * s___;
{
  DisplayMWText___ ( ( char * ) s___ );
}

void
PUT_BOOL_M ( b___ )
int b___;
{
  if   ( b___ )  DisplayMWText___ ( "TRUE" );
  else           DisplayMWText___ ( "FALSE" );
}

void
PUT_BTS_M ( b___ )
int b___;
{
  void AppBitsToBuf___ ();
  buf___ [ 0 ] = '\0';
  AppBitsToBuf___ ( b___ );
  DisplayMWText___ ( buf___ );
}

void
GET_PROMPT_NBR_M ( r___, s___, d___ )
int * r___;
char * s___;
int d___;
{
  int n___, x___, y___;
  ini_prompt___ ( nx___, ny___ );
  cat_prompt___ ( s___, 1, d___ );
  system ( buf___ );
  open_Bcom___;
  nat_Bcom___ ( * r___ );
  nat_Bcom___ ( x___ );
  nat_Bcom___ ( y___ );
  close_Bcom___;
  upd_pos___ ( x___, y___ );
}

void
GET_PROMPT_STR_M ( s___, t___ )
char * s___;
char * t___;
{
  int i___, n___, x___, y___;
  ini_prompt___ ( nx___, ny___ );
  cat_prompt___ ( t___, 2, 0 );
  system ( buf___ );
  open_Bcom___;
  str_Bcom___ ( s___ );
  nat_Bcom___ ( x___ );
  nat_Bcom___ ( y___ );
  close_Bcom___;
  upd_pos___ ( x___, y___ );
}

void
GET_PROMPT_BTS_M ( s___, t___ )
int * s___;
char * t___;
{
  int n___, x___, y___;
  ini_prompt___ ( nx___, ny___ );
  cat_prompt___ ( t___, 4, 0 );
  system ( buf___ );
  open_Bcom___;
  bts_Bcom___ ( * s___ );
  nat_Bcom___ ( x___ );
  nat_Bcom___ ( y___ );
  close_Bcom___;
  upd_pos___ ( x___, y___ );
}

void
GET_PROMPT_CHR_M ( c___, s___ )
int * c___;
char * s___;
{
  int n___, x___, y___;
  ini_prompt___ ( nx___, ny___ );
  cat_prompt___ ( s___, 3, 0 );
  system ( buf___ );
  open_Bcom___;
  chr_Bcom___ ( * c___ );
  nat_Bcom___ ( x___ );
  nat_Bcom___ ( y___ );
  close_Bcom___;
  upd_pos___ ( x___, y___ );
}

void
GET_PROMPT_BOOL_M ( r___, s___ )
int * r___;
char * s___;
{
  int i___, n___, x___, y___;
  ini_prompt___ ( nx___, ny___ );
  cat_prompt_enm___ ( s___, 5, "BOOL(FALSE,TRUE)" );
  system ( buf___ );
  open_Bcom___;
  nat_Bcom___ ( * r___ );
  nat_Bcom___ ( x___ );
  nat_Bcom___ ( y___ );
  close_Bcom___;
  upd_pos___ ( x___, y___ );
}


char *opnames___ [] = { "op" };
#define opnames_tot___ 1

char sel_tog___ [ opnames_tot___ + 1 ];


char *num__________ [] = {
  "0",
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9"
};

void
AppNumToBuf___ ( n___ )
int n___;
{
  if ( n___ < 0 ) {
    strcat ( buf___, "-" );
    n___ = n___ * (-1);
  }
  if ( n___ > 9 ) {
    AppNumToBuf___ ( n___ / 10 );
    strcat ( buf___, num__________ [ n___ % 10 ] );
  }
  else {
    strcat ( buf___, num__________ [ n___ ] );
  }
}

void
AppBitsToBuf___ ( n___ )
int n___;
{
  int i___ = 32;
  while( i___ > 0 ) {
    strcat ( buf___, num__________ [ ( ( ( n___ >> ( i___ - 1 ) ) % 2 ) + 2 ) % 2 ] );
      i___ = i___ - 1;
  }
}

AppCharToBuf___ ( c___ )
char c___;
{
  int l___ = strlen ( buf___ );
  buf___ [ l___++ ] = c___;
  buf___ [ l___ ] = '\0';
}

void
Popup_Err_CB ( err___ )
Widget err___;
{
  XtPopdown ( XtParent ( err___ ) );
  XmUpdateDisplay ( XtParent ( err___ ) );
}

void
Popup_Err ( text___ )
char * text___;
{
  static Widget err___;
  if ( ! err___ ) {
    err___ = XmCreateErrorDialog ( top_level___, "WarningDialog", NULL, 0 );
    XtVaSetValues ( err___,
        XmNmarginWidth,            10,
        XmNmarginHeight,           5,
        XmNdefaultPosition,        False,  
        XmNdialogStyle,            XmDIALOG_APPLICATION_MODAL,
        NULL );
    XtUnmanageChild ( XmMessageBoxGetChild ( err___, XmDIALOG_CANCEL_BUTTON ) );
    XtUnmanageChild ( XmMessageBoxGetChild ( err___, XmDIALOG_HELP_BUTTON ) );
    XtAddCallback ( err___, XmNokCallback, ( XtCallbackProc ) Popup_Err_CB, ( XtPointer ) NULL );
  }
  xstr___ = XmStringCreateLtoR ( ( char * ) text___, charset___ );
  XtVaSetValues ( err___, XmNmessageString, xstr___, NULL );
  XmStringFree ( xstr___ );
  XtVaSetValues ( err___, XmNx, 135, XmNy, 195, NULL );
  XtManageChild ( err___ );
  XtPopup ( XtParent ( err___ ) , XtGrabNone ); 
  XBell ( display___, 10 );
}

#define nat_type___     1
#define char_type___    2
#define string_type___  3
#define fstring_type___ 4
#define bool_type___    5
#define enum_type___    6
#define bit_type___     7
#define other_type___   8

int
check_nat___ ( str___ )
char * str___;
{
  int l___ = strlen ( str___ );
  int ok___ = 1;
  int  i___ = 0;
  if ( l___ == 0 ) {
    strcpy ( buf___, "Empty input field!" );
    Popup_Err ( buf___ );
    return ( 0 );
  }
  while ( i___ < l___ && ok___ ) {
    if ( str___ [ i___ ] < '0' || str___ [ i___ ] > '9' ) {
      ok___ = 0;
    }
    i___++;
  }
  if ( ok___ ) {
    if ( l___ > 10 ) {
      ok___ = 0;
    }
    else if ( l___ == 10 ) {
      unsigned j___ = 0;
      for ( i___ = 0 ; i___ < 10 ; i___++ ) {
        j___ = ( 10 * j___ ) + str___ [ i___ ] - '0';
      }
      if ( j___ > 2147483646 ) {
        ok___ = 0;
      }
    }
  }
  if ( ! ok___ ) {
    strcpy ( buf___, "\"" );
    strcat ( buf___, str___ );
    strcat ( buf___, "\" is not a number (0..2147483646)" );
    Popup_Err ( buf___ );
  }
  return ( ok___ );
}

int
check_bit___ ( str___ )
char * str___;
{
  int l___ = strlen ( str___ );
  int ok___ = 1;
  int  i___ = 0;
  if ( l___ == 0 ) {
    strcpy ( buf___, "Empty input field!" );
    Popup_Err ( buf___ );
    return ( 0 );
  }
  if ( l___ > 32 ) {
    strcpy ( buf___, "Bit string too long (max 32)!" );
    Popup_Err ( buf___ );
    return ( 0 );
  }
  while ( i___ < l___ && ok___ ) {
    if ( str___ [ i___ ] != '0' && str___ [ i___ ] != '1' ) {
      ok___ = 0;
    }
    i___++;
  }
  if ( ! ok___ ) {
    strcpy ( buf___, "\"" );
    strcat ( buf___, str___ );
    strcat ( buf___, "\" is not bit string" );
    Popup_Err ( buf___ );
  }
  return ( ok___ );
}

int
check_chr___ ( str___ )
char * str___;
{
  int l___ = strlen ( str___ );
  int ok___ = 1;
  if ( l___ != 1                   ||
       str___ [ 0 ] < ( char ) 32  || 
       str___ [ 0 ] > ( char ) 126    ) ok___ = 0;
  if ( ! ok___ ) {
    strcpy ( buf___, "\"" );
    strcat ( buf___, str___ );
    strcat ( buf___, "\" is not a (single) character" );
    Popup_Err ( buf___ );
  }
  return ( ok___ );
}

void
Ini_nx_ny___ ()
{
  Dimension tw___;
  XtVaGetValues ( top_level___, 
      XmNx,         &pnx___,
      XmNy,         &pny___,
      XmNwidth,     &tw___,
      NULL );
  pnx___ = pnx___ + tw___;
  nx___ = pnx___;
  ny___ = pny___;
}

char * BOOL___ [] = {"FALSE","TRUE"};

#define tot_BOOL___ 2

char * CHAR___ [] = {"B_SOH","B_STX","B_ETX","B_EOT","B_ENQ","B_ACK","B_BEL","B_BS","B_HT","B_LF","B_VT","B_FF","B_CR","B_SO","B_SI","B_DLE","B_DC1","B_DC2","B_DC3","B_DC4","B_NAK","B_SYN","B_ETB","B_CAN","B_EM","B_SUB","B_ESC","B_FS","B_GS","B_RS","B_US","B_SPACE","B_EXCL","B_QUOT","B_HSH","B_DOLL","B_PCT","B_AMP","B_SQUOT","B_OPAR","B_CPAR","B_MUL","B_PLUS","B_COM","B_MINUS","B_DOT","B_DIV","'0'","'1'","'2'","'3'","'4'","'5'","'6'","'7'","'8'","'9'","B_COL","B_SCOL","B_LESS","B_EQL","B_GTR","B_QUERY","B_CADD","'A'","'B'","'C'","'D'","'E'","'F'","'G'","'H'","'I'","'J'","'K'","'L'","'M'","'N'","'O'","'P'","'Q'","'R'","'S'","'T'","'U'","'V'","'W'","'X'","'Y'","'Z'","B_OBRK","B_SLSH","B_CBRK","B_HAT","B_UNL","B_BSQ","'a'","'b'","'c'","'d'","'e'","'f'","'g'","'h'","'i'","'j'","'k'","'l'","'m'","'n'","'o'","'p'","'q'","'r'","'s'","'u'","'v'","'w'","'x'","'y'","'z'","B_OBRC","B_BAR","B_CBRC","B_TLD","B_DEL"};

#define tot_CHAR___ 126

void
PUT_ACT_TOK_M ( s___, o___ )
char * * s___;
int o___;
{
  if   ( ! strlen ( s___ [ 0 ] ) ) {
    DisplayMWText___ ( s___ [ o___ ] );
  }
  else {
    buf___ [ 0 ] = '\0';
    if ( ( strcmp ( s___ [ 0 ], "SCALAR" ) != 0 )        &&
         ( strcmp ( s___ [ 0 ], "0..2147483646" ) != 0 )    ) {
      strcat ( buf___, s___ [ 0 ] );
      strcat ( buf___, "." );
    }
    AppNumToBuf___ ( o___ );
    DisplayMWText___ ( buf___ );
  }
}

void
GET_ACT_TOK_M ( s___, o___, p___ )
char * * s___;
int * o___;
char * p___;
{
  char enm_buf___ [ 1000 ];
  int i___,j___,n___,x___,y___;
  i___ = 1;
  while ( s___ [ i___ ] [ 0 ] != '_' ) {
    i___++;
  }
  j___ = 0;
  while ( s___ [ i___ ] [ j___ ] != '\0' ) {
    enm_buf___ [ j___ ] = s___ [ i___ ] [ j___ ];
    j___++;
  }
  enm_buf___ [ j___ ] = '(';
  enm_buf___ [ j___ + 1 ] = '\0';
  i___ = 1;
  while ( s___ [ i___ ] [ 0 ] != '_' ) {
    if ( i___ != 1 ) strcat ( enm_buf___, "," );
    strcat ( enm_buf___, s___ [ i___ ] );
    i___++;
  }
  strcat ( enm_buf___, ")" );
  ini_prompt___ ( nx___, ny___ );
  cat_prompt_enm___ ( p___, 5, enm_buf___ );
  system ( buf___ );
  open_Bcom___;
  nat_Bcom___ ( * o___ );
  nat_Bcom___ ( x___ );
  nat_Bcom___ ( y___ );
  close_Bcom___;
  upd_pos___ ( x___, y___ );
}

void
GET_SET_ACT_TOK_M ( s___, m___, o___ )
char * * s___;
int m___;
int * o___;
{
  char enm_buf___ [ 1000 ];
  char t___ [ 250 ];
  char u___ [ 250 ];
  int i___,j___,n___,x___,y___;
  i___ = 1;
  while ( s___ [ i___ ] [ 0 ] != '_' ) {
    i___++;
  }
  j___ = 0;
  while ( s___ [ i___ ] [ j___ ] != '\0' ) {
    enm_buf___ [ j___ ] = s___ [ i___ ] [ j___ ];
    if ( j___ ) u___ [ j___ - 1 ] = s___ [ i___ ] [ j___ ];
    j___++;
  }
  u___ [ j___ ] = '\0';
  enm_buf___ [ j___ ] = '(';
  enm_buf___ [ j___ + 1 ] = '\0';
  i___ = 1;
  while ( s___ [ i___ ] [ 0 ] != '_' ) {
    if ( i___ != 1 ) strcat ( enm_buf___, "," );
    strcat ( enm_buf___, s___ [ i___ ] );
    i___++;
  }
  strcat ( enm_buf___, ")" );
  ini_prompt___ ( nx___, ny___ );
  for ( i___ = 0 ; i___ < m___ ; i___++ ) {
    sprintf ( t___, "  %s value # %d: ", u___, i___ + 1 );
    cat_prompt_enm___ ( t___, 5, enm_buf___ );
  }
  system ( buf___ );
  open_Bcom___;
  for ( i___ = 0 ; i___ < m___ ; i___++ ) {
    nat_Bcom___ ( j___ );
    o___ [ i___ ] = j___;
  }
  nat_Bcom___ ( x___ );
  nat_Bcom___ ( y___ );
  close_Bcom___;
  upd_pos___ ( x___, y___ );
}

void
GET_SET_TOK_M ( s___, m___, o___ )
char * * s___;
int m___;
int * o___;
{
  char t___ [ 250 ];
  int i___,j___,n___,x___,y___;
  ini_prompt___ ( nx___, ny___ );
  for ( i___ = 0 ; i___ < m___ ; i___++ ) {
    sprintf ( t___, "  %s value # %d: ", s___ [ 0 ], i___ + 1 );
    cat_prompt___ ( t___, 1, 2147483646 );
  }
  system ( buf___ );
  open_Bcom___;
  for ( i___ = 0 ; i___ < m___ ; i___++ ) {
    nat_Bcom___ ( j___ );
    o___ [ i___ ] = j___;
  }
  nat_Bcom___ ( x___ );
  nat_Bcom___ ( y___ );
  close_Bcom___;
  upd_pos___ ( x___, y___ );
}

Widget
cre_BOOL_PDown___ ( cb___, parent___ )
XtPointer cb___;
Widget parent___;
{
  XmString ppt___,FALSE___,TRUE___;
  Widget popup_BOOLM_rc___, popup_BOOLM___;
  ppt___ = XmStringCreateSimple ( "" );
  FALSE___ = XmStringCreateSimple ("FALSE");
  TRUE___ = XmStringCreateSimple ("TRUE");
  popup_BOOLM___ = XmVaCreateSimpleOptionMenu ( parent___, "ItfDialog",
      ppt___, 0,
      0, cb___,
      XmVaPUSHBUTTON, FALSE___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, TRUE___, NULL, NULL, NULL,
      NULL);
    XmStringFree ( ppt___ );
    XmStringFree ( FALSE___ );
    XmStringFree ( TRUE___ );
  return ( popup_BOOLM___ );
}

Widget
cre_CHAR_PDown___ ( cb___, parent___ )
XtPointer cb___;
Widget parent___;
{
  XmString ppt___,B_SOH___,B_STX___,B_ETX___,B_EOT___,B_ENQ___,B_ACK___,B_BEL___,B_BS___,B_HT___,B_LF___,B_VT___,B_FF___,B_CR___,B_SO___,B_SI___,B_DLE___,B_DC1___,B_DC2___,B_DC3___,B_DC4___,B_NAK___,B_SYN___,B_ETB___,B_CAN___,B_EM___,B_SUB___,B_ESC___,B_FS___,B_GS___,B_RS___,B_US___,B_SPACE___,B_EXCL___,B_QUOT___,B_HSH___,B_DOLL___,B_PCT___,B_AMP___,B_SQUOT___,B_OPAR___,B_CPAR___,B_MUL___,B_PLUS___,B_COM___,B_MINUS___,B_DOT___,B_DIV___,Ch_0___,Ch_1___,Ch_2___,Ch_3___,Ch_4___,Ch_5___,Ch_6___,Ch_7___,Ch_8___,Ch_9___,B_COL___,B_SCOL___,B_LESS___,B_EQL___,B_GTR___,B_QUERY___,B_CADD___,Ch_A___,Ch_B___,Ch_C___,Ch_D___,Ch_E___,Ch_F___,Ch_G___,Ch_H___,Ch_I___,Ch_J___,Ch_K___,Ch_L___,Ch_M___,Ch_N___,Ch_O___,Ch_P___,Ch_Q___,Ch_R___,Ch_S___,Ch_T___,Ch_U___,Ch_V___,Ch_W___,Ch_X___,Ch_Y___,Ch_Z___,B_OBRK___,B_SLSH___,B_CBRK___,B_HAT___,B_UNL___,B_BSQ___,Ch_a___,Ch_b___,Ch_c___,Ch_d___,Ch_e___,Ch_f___,Ch_g___,Ch_h___,Ch_i___,Ch_j___,Ch_k___,Ch_l___,Ch_m___,Ch_n___,Ch_o___,Ch_p___,Ch_q___,Ch_r___,Ch_s___,Ch_u___,Ch_v___,Ch_w___,Ch_x___,Ch_y___,Ch_z___,B_OBRC___,B_BAR___,B_CBRC___,B_TLD___,B_DEL___;
  Widget popup_CHARM_rc___, popup_CHARM___;
  ppt___ = XmStringCreateSimple ( "" );
  B_SOH___ = XmStringCreateSimple ("B_SOH");
  B_STX___ = XmStringCreateSimple ("B_STX");
  B_ETX___ = XmStringCreateSimple ("B_ETX");
  B_EOT___ = XmStringCreateSimple ("B_EOT");
  B_ENQ___ = XmStringCreateSimple ("B_ENQ");
  B_ACK___ = XmStringCreateSimple ("B_ACK");
  B_BEL___ = XmStringCreateSimple ("B_BEL");
  B_BS___ = XmStringCreateSimple ("B_BS");
  B_HT___ = XmStringCreateSimple ("B_HT");
  B_LF___ = XmStringCreateSimple ("B_LF");
  B_VT___ = XmStringCreateSimple ("B_VT");
  B_FF___ = XmStringCreateSimple ("B_FF");
  B_CR___ = XmStringCreateSimple ("B_CR");
  B_SO___ = XmStringCreateSimple ("B_SO");
  B_SI___ = XmStringCreateSimple ("B_SI");
  B_DLE___ = XmStringCreateSimple ("B_DLE");
  B_DC1___ = XmStringCreateSimple ("B_DC1");
  B_DC2___ = XmStringCreateSimple ("B_DC2");
  B_DC3___ = XmStringCreateSimple ("B_DC3");
  B_DC4___ = XmStringCreateSimple ("B_DC4");
  B_NAK___ = XmStringCreateSimple ("B_NAK");
  B_SYN___ = XmStringCreateSimple ("B_SYN");
  B_ETB___ = XmStringCreateSimple ("B_ETB");
  B_CAN___ = XmStringCreateSimple ("B_CAN");
  B_EM___ = XmStringCreateSimple ("B_EM");
  B_SUB___ = XmStringCreateSimple ("B_SUB");
  B_ESC___ = XmStringCreateSimple ("B_ESC");
  B_FS___ = XmStringCreateSimple ("B_FS");
  B_GS___ = XmStringCreateSimple ("B_GS");
  B_RS___ = XmStringCreateSimple ("B_RS");
  B_US___ = XmStringCreateSimple ("B_US");
  B_SPACE___ = XmStringCreateSimple ("B_SPACE");
  B_EXCL___ = XmStringCreateSimple ("B_EXCL");
  B_QUOT___ = XmStringCreateSimple ("B_QUOT");
  B_HSH___ = XmStringCreateSimple ("B_HSH");
  B_DOLL___ = XmStringCreateSimple ("B_DOLL");
  B_PCT___ = XmStringCreateSimple ("B_PCT");
  B_AMP___ = XmStringCreateSimple ("B_AMP");
  B_SQUOT___ = XmStringCreateSimple ("B_SQUOT");
  B_OPAR___ = XmStringCreateSimple ("B_OPAR");
  B_CPAR___ = XmStringCreateSimple ("B_CPAR");
  B_MUL___ = XmStringCreateSimple ("B_MUL");
  B_PLUS___ = XmStringCreateSimple ("B_PLUS");
  B_COM___ = XmStringCreateSimple ("B_COM");
  B_MINUS___ = XmStringCreateSimple ("B_MINUS");
  B_DOT___ = XmStringCreateSimple ("B_DOT");
  B_DIV___ = XmStringCreateSimple ("B_DIV");
  Ch_0___ = XmStringCreateSimple ("0");
  Ch_1___ = XmStringCreateSimple ("1");
  Ch_2___ = XmStringCreateSimple ("2");
  Ch_3___ = XmStringCreateSimple ("3");
  Ch_4___ = XmStringCreateSimple ("4");
  Ch_5___ = XmStringCreateSimple ("5");
  Ch_6___ = XmStringCreateSimple ("6");
  Ch_7___ = XmStringCreateSimple ("7");
  Ch_8___ = XmStringCreateSimple ("8");
  Ch_9___ = XmStringCreateSimple ("9");
  B_COL___ = XmStringCreateSimple ("B_COL");
  B_SCOL___ = XmStringCreateSimple ("B_SCOL");
  B_LESS___ = XmStringCreateSimple ("B_LESS");
  B_EQL___ = XmStringCreateSimple ("B_EQL");
  B_GTR___ = XmStringCreateSimple ("B_GTR");
  B_QUERY___ = XmStringCreateSimple ("B_QUERY");
  B_CADD___ = XmStringCreateSimple ("B_CADD");
  Ch_A___ = XmStringCreateSimple ("A");
  Ch_B___ = XmStringCreateSimple ("B");
  Ch_C___ = XmStringCreateSimple ("C");
  Ch_D___ = XmStringCreateSimple ("D");
  Ch_E___ = XmStringCreateSimple ("E");
  Ch_F___ = XmStringCreateSimple ("F");
  Ch_G___ = XmStringCreateSimple ("G");
  Ch_H___ = XmStringCreateSimple ("H");
  Ch_I___ = XmStringCreateSimple ("I");
  Ch_J___ = XmStringCreateSimple ("J");
  Ch_K___ = XmStringCreateSimple ("K");
  Ch_L___ = XmStringCreateSimple ("L");
  Ch_M___ = XmStringCreateSimple ("M");
  Ch_N___ = XmStringCreateSimple ("N");
  Ch_O___ = XmStringCreateSimple ("O");
  Ch_P___ = XmStringCreateSimple ("P");
  Ch_Q___ = XmStringCreateSimple ("Q");
  Ch_R___ = XmStringCreateSimple ("R");
  Ch_S___ = XmStringCreateSimple ("S");
  Ch_T___ = XmStringCreateSimple ("T");
  Ch_U___ = XmStringCreateSimple ("U");
  Ch_V___ = XmStringCreateSimple ("V");
  Ch_W___ = XmStringCreateSimple ("W");
  Ch_X___ = XmStringCreateSimple ("X");
  Ch_Y___ = XmStringCreateSimple ("Y");
  Ch_Z___ = XmStringCreateSimple ("Z");
  B_OBRK___ = XmStringCreateSimple ("B_OBRK");
  B_SLSH___ = XmStringCreateSimple ("B_SLSH");
  B_CBRK___ = XmStringCreateSimple ("B_CBRK");
  B_HAT___ = XmStringCreateSimple ("B_HAT");
  B_UNL___ = XmStringCreateSimple ("B_UNL");
  B_BSQ___ = XmStringCreateSimple ("B_BSQ");
  Ch_a___ = XmStringCreateSimple ("a");
  Ch_b___ = XmStringCreateSimple ("b");
  Ch_c___ = XmStringCreateSimple ("c");
  Ch_d___ = XmStringCreateSimple ("d");
  Ch_e___ = XmStringCreateSimple ("e");
  Ch_f___ = XmStringCreateSimple ("f");
  Ch_g___ = XmStringCreateSimple ("g");
  Ch_h___ = XmStringCreateSimple ("h");
  Ch_i___ = XmStringCreateSimple ("i");
  Ch_j___ = XmStringCreateSimple ("j");
  Ch_k___ = XmStringCreateSimple ("k");
  Ch_l___ = XmStringCreateSimple ("l");
  Ch_m___ = XmStringCreateSimple ("m");
  Ch_n___ = XmStringCreateSimple ("n");
  Ch_o___ = XmStringCreateSimple ("o");
  Ch_p___ = XmStringCreateSimple ("p");
  Ch_q___ = XmStringCreateSimple ("q");
  Ch_r___ = XmStringCreateSimple ("r");
  Ch_s___ = XmStringCreateSimple ("s");
  Ch_u___ = XmStringCreateSimple ("u");
  Ch_v___ = XmStringCreateSimple ("v");
  Ch_w___ = XmStringCreateSimple ("w");
  Ch_x___ = XmStringCreateSimple ("x");
  Ch_y___ = XmStringCreateSimple ("y");
  Ch_z___ = XmStringCreateSimple ("z");
  B_OBRC___ = XmStringCreateSimple ("B_OBRC");
  B_BAR___ = XmStringCreateSimple ("B_BAR");
  B_CBRC___ = XmStringCreateSimple ("B_CBRC");
  B_TLD___ = XmStringCreateSimple ("B_TLD");
  B_DEL___ = XmStringCreateSimple ("B_DEL");
  popup_CHARM___ = XmVaCreateSimpleOptionMenu ( parent___, "ItfDialog",
      ppt___, 0,
      0, cb___,
      XmVaPUSHBUTTON, B_SOH___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_STX___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_ETX___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_EOT___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_ENQ___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_ACK___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_BEL___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_BS___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_HT___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_LF___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_VT___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_FF___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_CR___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_SO___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_SI___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_DLE___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_DC1___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_DC2___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_DC3___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_DC4___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_NAK___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_SYN___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_ETB___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_CAN___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_EM___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_SUB___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_ESC___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_FS___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_GS___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_RS___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_US___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_SPACE___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_EXCL___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_QUOT___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_HSH___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_DOLL___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_PCT___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_AMP___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_SQUOT___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_OPAR___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_CPAR___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_MUL___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_PLUS___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_COM___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_MINUS___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_DOT___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_DIV___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_0___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_1___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_2___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_3___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_4___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_5___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_6___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_7___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_8___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_9___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_COL___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_SCOL___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_LESS___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_EQL___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_GTR___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_QUERY___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_CADD___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_A___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_B___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_C___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_D___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_E___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_F___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_G___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_H___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_I___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_J___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_K___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_L___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_M___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_N___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_O___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_P___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_Q___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_R___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_S___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_T___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_U___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_V___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_W___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_X___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_Y___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_Z___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_OBRK___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_SLSH___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_CBRK___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_HAT___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_UNL___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_BSQ___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_a___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_b___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_c___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_d___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_e___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_f___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_g___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_h___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_i___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_j___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_k___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_l___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_m___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_n___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_o___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_p___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_q___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_r___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_s___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_u___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_v___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_w___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_x___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_y___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, Ch_z___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_OBRC___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_BAR___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_CBRC___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_TLD___, NULL, NULL, NULL,
      XmVaPUSHBUTTON, B_DEL___, NULL, NULL, NULL,
      NULL);
    XmStringFree ( ppt___ );
    XmStringFree ( B_SOH___ );
    XmStringFree ( B_STX___ );
    XmStringFree ( B_ETX___ );
    XmStringFree ( B_EOT___ );
    XmStringFree ( B_ENQ___ );
    XmStringFree ( B_ACK___ );
    XmStringFree ( B_BEL___ );
    XmStringFree ( B_BS___ );
    XmStringFree ( B_HT___ );
    XmStringFree ( B_LF___ );
    XmStringFree ( B_VT___ );
    XmStringFree ( B_FF___ );
    XmStringFree ( B_CR___ );
    XmStringFree ( B_SO___ );
    XmStringFree ( B_SI___ );
    XmStringFree ( B_DLE___ );
    XmStringFree ( B_DC1___ );
    XmStringFree ( B_DC2___ );
    XmStringFree ( B_DC3___ );
    XmStringFree ( B_DC4___ );
    XmStringFree ( B_NAK___ );
    XmStringFree ( B_SYN___ );
    XmStringFree ( B_ETB___ );
    XmStringFree ( B_CAN___ );
    XmStringFree ( B_EM___ );
    XmStringFree ( B_SUB___ );
    XmStringFree ( B_ESC___ );
    XmStringFree ( B_FS___ );
    XmStringFree ( B_GS___ );
    XmStringFree ( B_RS___ );
    XmStringFree ( B_US___ );
    XmStringFree ( B_SPACE___ );
    XmStringFree ( B_EXCL___ );
    XmStringFree ( B_QUOT___ );
    XmStringFree ( B_HSH___ );
    XmStringFree ( B_DOLL___ );
    XmStringFree ( B_PCT___ );
    XmStringFree ( B_AMP___ );
    XmStringFree ( B_SQUOT___ );
    XmStringFree ( B_OPAR___ );
    XmStringFree ( B_CPAR___ );
    XmStringFree ( B_MUL___ );
    XmStringFree ( B_PLUS___ );
    XmStringFree ( B_COM___ );
    XmStringFree ( B_MINUS___ );
    XmStringFree ( B_DOT___ );
    XmStringFree ( B_DIV___ );
    XmStringFree ( Ch_0___ );
    XmStringFree ( Ch_1___ );
    XmStringFree ( Ch_2___ );
    XmStringFree ( Ch_3___ );
    XmStringFree ( Ch_4___ );
    XmStringFree ( Ch_5___ );
    XmStringFree ( Ch_6___ );
    XmStringFree ( Ch_7___ );
    XmStringFree ( Ch_8___ );
    XmStringFree ( Ch_9___ );
    XmStringFree ( B_COL___ );
    XmStringFree ( B_SCOL___ );
    XmStringFree ( B_LESS___ );
    XmStringFree ( B_EQL___ );
    XmStringFree ( B_GTR___ );
    XmStringFree ( B_QUERY___ );
    XmStringFree ( B_CADD___ );
    XmStringFree ( Ch_A___ );
    XmStringFree ( Ch_B___ );
    XmStringFree ( Ch_C___ );
    XmStringFree ( Ch_D___ );
    XmStringFree ( Ch_E___ );
    XmStringFree ( Ch_F___ );
    XmStringFree ( Ch_G___ );
    XmStringFree ( Ch_H___ );
    XmStringFree ( Ch_I___ );
    XmStringFree ( Ch_J___ );
    XmStringFree ( Ch_K___ );
    XmStringFree ( Ch_L___ );
    XmStringFree ( Ch_M___ );
    XmStringFree ( Ch_N___ );
    XmStringFree ( Ch_O___ );
    XmStringFree ( Ch_P___ );
    XmStringFree ( Ch_Q___ );
    XmStringFree ( Ch_R___ );
    XmStringFree ( Ch_S___ );
    XmStringFree ( Ch_T___ );
    XmStringFree ( Ch_U___ );
    XmStringFree ( Ch_V___ );
    XmStringFree ( Ch_W___ );
    XmStringFree ( Ch_X___ );
    XmStringFree ( Ch_Y___ );
    XmStringFree ( Ch_Z___ );
    XmStringFree ( B_OBRK___ );
    XmStringFree ( B_SLSH___ );
    XmStringFree ( B_CBRK___ );
    XmStringFree ( B_HAT___ );
    XmStringFree ( B_UNL___ );
    XmStringFree ( B_BSQ___ );
    XmStringFree ( Ch_a___ );
    XmStringFree ( Ch_b___ );
    XmStringFree ( Ch_c___ );
    XmStringFree ( Ch_d___ );
    XmStringFree ( Ch_e___ );
    XmStringFree ( Ch_f___ );
    XmStringFree ( Ch_g___ );
    XmStringFree ( Ch_h___ );
    XmStringFree ( Ch_i___ );
    XmStringFree ( Ch_j___ );
    XmStringFree ( Ch_k___ );
    XmStringFree ( Ch_l___ );
    XmStringFree ( Ch_m___ );
    XmStringFree ( Ch_n___ );
    XmStringFree ( Ch_o___ );
    XmStringFree ( Ch_p___ );
    XmStringFree ( Ch_q___ );
    XmStringFree ( Ch_r___ );
    XmStringFree ( Ch_s___ );
    XmStringFree ( Ch_u___ );
    XmStringFree ( Ch_v___ );
    XmStringFree ( Ch_w___ );
    XmStringFree ( Ch_x___ );
    XmStringFree ( Ch_y___ );
    XmStringFree ( Ch_z___ );
    XmStringFree ( B_OBRC___ );
    XmStringFree ( B_BAR___ );
    XmStringFree ( B_CBRC___ );
    XmStringFree ( B_TLD___ );
    XmStringFree ( B_DEL___ );
  return ( popup_CHARM___ );
}

void
DisplayMWText___ ( mtext___ )
char * mtext___;
{
  static XmTextPosition monolog_text_posn___;
  XmTextInsert ( monolog_text___, monolog_text_posn___, mtext___ );
  monolog_text_posn___ = monolog_text_posn___ + strlen ( mtext___ );
  XmTextShowPosition ( monolog_text___, monolog_text_posn___ );
  XmUpdateDisplay ( monolog_text___);
}

void
ResetWaitFlag___ ()
{
  wait_flag___ = 0;
}

void
cre_pixmap___ ()
{
  FILE * Bxpm;
  B_framed_pixmap_gray95___ = XmGetPixmap ( XtScreen ( top_level___ ), "../../B.xpm",
      BlackPixelOfScreen ( XtScreen ( top_level___ ) ),
      WhitePixelOfScreen ( XtScreen ( top_level___ ) ) );
  if ( B_framed_pixmap_gray95___ != XmUNSPECIFIED_PIXMAP ) return;
  B_framed_pixmap_gray95___ = XmGetPixmap ( XtScreen ( top_level___ ), "./B.xpm",
      BlackPixelOfScreen ( XtScreen ( top_level___ ) ),
      WhitePixelOfScreen ( XtScreen ( top_level___ ) ) );
  if ( B_framed_pixmap_gray95___ != XmUNSPECIFIED_PIXMAP ) return;
  Bxpm = fopen ( "B.xpm", "w" );
  if ( Bxpm == NULL ) {
    printf ( "\n  Can't open \"B.xpm\" for writing\n\n" );
      exit ( 1 );
  }
  fprintf ( Bxpm, "/" );
  fprintf ( Bxpm, "* XPM *" );
  fprintf ( Bxpm, "/\n" );
  fprintf ( Bxpm, "static char * B_pxm[] = {\n" );
  fprintf ( Bxpm, "\"32 28 5 1\",\n" );
  fprintf ( Bxpm, "\"   c black\",\n" );
  fprintf ( Bxpm, "\".  c gray95\",\n" );
  fprintf ( Bxpm, "\"X  c white\",\n" );
  fprintf ( Bxpm, "\"o  c #d1b499\",\n" );
  fprintf ( Bxpm, "\"O  c #6dacff\",\n" );
  fprintf ( Bxpm, "\"                                \",\n" );
  fprintf ( Bxpm, "\" .XXXXXXXXXXXXXXXXXXXXXXXXXXXXX \",\n" );
  fprintf ( Bxpm, "\" .X                 ........... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOO .......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOO ......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOO ......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOO .......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo            ........... \",\n" );
  fprintf ( Bxpm, "\" .X oooo ...................... \",\n" );
  fprintf ( Bxpm, "\" .X oooo ...................... \",\n" );
  fprintf ( Bxpm, "\" .X oooo            ........... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOO .......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOO ......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOOO ........ \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOOO ......... \",\n" );
  fprintf ( Bxpm, "\" .X oooo OOOOOOOOOOO .......... \",\n" );
  fprintf ( Bxpm, "\" .X                 ........... \",\n" );
  fprintf ( Bxpm, "\" .XXXXXXXXXXXXXXXXXXXXXXXXXXXXX \",\n" );
  fprintf ( Bxpm, "\"                                \"};\n" );
  fclose ( Bxpm );
  B_framed_pixmap_gray95___ = XmGetPixmap ( XtScreen ( top_level___ ), "./B.xpm",
      BlackPixelOfScreen ( XtScreen ( top_level___ ) ),
      WhitePixelOfScreen ( XtScreen ( top_level___ ) ) );
  if ( B_framed_pixmap_gray95___ == XmUNSPECIFIED_PIXMAP ) {
    printf("\n  Warning - can't create (B.xpm) pixmap\n" );
  }
}

Widget
cre_B_logo___ ( parent___, t_off___, r_off___ )
Widget parent___;
int t_off___;
int r_off___;
{
  Widget B_logo___;
  B_logo___ =  XtVaCreateManagedWidget ( "ItfDialog",
      xmLabelWidgetClass,             parent___,
      XmNlabelType,                   XmPIXMAP,
      XmNlabelPixmap,                 B_framed_pixmap_gray95___,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   t_off___,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 r_off___,
      XmNshadowType,                  XmSHADOW_ETCHED_IN,
      XmNshadowThickness,             0,
      XmNmarginWidth,                 0,
      XmNmarginHeight,                0,
      XmNtraversalOn,                 False,
      NULL );
  return ( B_logo___ );
}

Widget
cre_dialog_form___ ( class___, parent___ )
char * class___;
Widget parent___;
{
  Widget dialog_form___ = XtVaCreateWidget ( class___,
      xmFormWidgetClass,         parent___,
      XmNdefaultPosition,        False,  
      NULL);
  return ( dialog_form___ );
}

Widget
cre_sep___  ( class___, parent___ )
char * class___;
Widget parent___;
{
  Widget sep___ = XtVaCreateManagedWidget ( class___,
      xmSeparatorGadgetClass,  parent___,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNbottomAttachment,     XmATTACH_FORM,
      XmNbottomOffset,         48,
      NULL);
  return ( sep___ );
}

Widget
cre_ok_form___ ( class___, parent___, top_w___ )
char * class___;
Widget parent___;
Widget top_w___;
{
  Widget ok_form___ = XtVaCreateWidget ( class___,
      xmFormWidgetClass,       parent___,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNtopAttachment,        XmATTACH_WIDGET,
      XmNtopWidget,            top_w___,
      XmNtopOffset,            5,
      NULL );
  return ( ok_form___ );
}

Widget
cre_ok___ ( parent___ )
Widget parent___;
{
  Widget ok___ = XtVaCreateManagedWidget ( "OK", 
      xmPushButtonGadgetClass, parent___,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNleftAttachment,       XmATTACH_FORM,
      XmNleftOffset,           12,
      XmNheight,               25,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      NULL );
  return ( ok___ );
}

Widget
cre_cancel___ ( parent___ )
Widget parent___;
{
  Widget cancel___ = XtVaCreateManagedWidget ( "Cancel", 
      xmPushButtonGadgetClass, parent___,
      XmNtopAttachment,        XmATTACH_FORM,
      XmNtopOffset,            5,
      XmNrightAttachment,      XmATTACH_FORM,
      XmNrightOffset,          12,
      XmNheight,               25,
      XmNwidth,                57,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,   1,
      NULL );
  return ( cancel___ );
}

Widget
cre_label___ ( class___, parent___, buffer___, l_off___ )
char * class___;
Widget parent___;
char * buffer___;
int l_off___;
{
  Widget label___;
  xstr___ = XmStringCreateLtoR ( buffer___ , charset___ );
  label___ = XtVaCreateWidget ( class___, 
      xmLabelWidgetClass,        parent___,
      XmNlabelString,            xstr___,
      XmNtopAttachment,          XmATTACH_FORM,
      XmNtopOffset,              10,
      XmNleftAttachment,         XmATTACH_FORM,
      XmNleftOffset,             l_off___,
      XmNtraversalOn,            False,
      NULL);
  XmStringFree ( xstr___ );
  return ( label___ );
}

Widget
cre_scroll___ ( class___, parent___, bottom_w___, height___ )
char * class___;
Widget parent___;
Widget bottom_w___;
int height___;
{
  Widget scroll___ = XtVaCreateWidget ( class___,
      xmScrolledWindowWidgetClass,    parent___,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   40,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                bottom_w___,
      XmNbottomOffset,                10,
      XmNscrollBarDisplayPolicy,      XmAS_NEEDED,
      XmNscrollingPolicy,             XmAUTOMATIC,
      XmNheight,                      height___,
      XmNborderWidth,                 0,
      XmNshadowThickness,             0,
      XmNspacing,                     0,
      NULL );
  return ( scroll___ );
}

Widget
cre_rb___ ( class___, parent___ )
char * class___;
Widget parent___;
{
  Widget rb___ = XmCreateRadioBox( parent___, class___, NULL, 0);
  XtVaSetValues ( rb___, XmNspacing, 0, NULL );
  return ( rb___ );
}

Widget
cre_left_rc___ ( class___, parent___ )
char * class___;
Widget parent___;
{
  Widget rc___ = XtVaCreateManagedWidget ( class___,
      xmRowColumnWidgetClass,         parent___,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   7,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_POSITION,
      XmNrightPosition,               1,
      XmNrightOffset,                 3,
      XmNisAligned,                   True,
      XmNentryAlignment,              XmALIGNMENT_END,
      XmNspacing,                     10,
      XmNtraversalOn,                 False,
      NULL );
  return ( rc___ );
}

Widget
cre_right_rc___ ( class___, parent___ )
char * class___;
Widget parent___;
{
  Widget rc___ = XtVaCreateManagedWidget ( class___,
      xmRowColumnWidgetClass,         parent___,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_POSITION,
      XmNleftPosition,                1,
      XmNisHomogeneous,               False,
      XmNspacing,                     0,
      NULL );
  return ( rc___ );
}

Widget
cre_form___ ( class___, parent___, bottom_w___ )
char * class___;
Widget parent___;
Widget bottom_w___;
{
  Widget form = XtVaCreateWidget ( class___,
      xmFormWidgetClass,           parent___,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNtopOffset,                   40,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNrightOffset,                 10,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNleftOffset,                  10,
      XmNbottomAttachment,            XmATTACH_WIDGET,
      XmNbottomWidget,                bottom_w___,
      XmNbottomOffset,                10,
      XmNfractionBase,                2,
      NULL );
  return ( form );
}

Widget
cre_inp___lab ( buffer___, parent___ )
char * buffer___;
Widget parent___;
{
  Widget pt____lab = XtVaCreateManagedWidget ( buffer___,
      xmLabelGadgetClass,             parent___,
      NULL );
  return ( pt____lab );
}

void
Popup_Dialog_Text_CB___  ( text_w___, client_d___ )
Widget text_w___;
XtPointer client_d___;
{
  XmProcessTraversal ( text_w___, XmTRAVERSE_NEXT_TAB_GROUP );
}

Widget
cre_text___ ( class1___, class2___, parent___ )
char * class1___;
char * class2___;
Widget parent___;
{
  Widget text_form___ = XtVaCreateManagedWidget ( class1___,
      xmFormWidgetClass,              parent___,
      NULL );
  Widget text___ = XtVaCreateManagedWidget ( class2___,
      xmTextFieldWidgetClass,         text_form___,
      XmNtopAttachment,               XmATTACH_FORM,
      XmNbottomAttachment,            XmATTACH_FORM,
      XmNrightAttachment,             XmATTACH_FORM,
      XmNleftAttachment,              XmATTACH_FORM,
      XmNtopOffset,                   5,
      NULL );
  XtAddCallback ( text___, XmNactivateCallback, ( XtCallbackProc ) Popup_Dialog_Text_CB___, ( XtPointer ) NULL );
  return ( text___ );
}

void
Popup_Dialog_CB___ ( button___ )
Widget button___;
{
  void OpsSwitch___ ();
  Widget dialog___ = XtParent ( XtParent ( XtParent ( button___ ) ) );
  int i___ = 0;
  XtPopdown ( dialog___ );
  XmUpdateDisplay ( dialog___ );
  while ( ! sel_tog___ [ i___ ] ) {
    i___++;
  }
  OpsSwitch___ ( i___ );
}

void
Cancel_CB___ ( button___ )
Widget button___;
{
  void Ops_Popup___ ();
  Dimension x___, y___;
  Widget dialog___ = XtParent ( XtParent ( XtParent ( button___ ) ) );
  XtVaGetValues ( dialog___, XmNx, &x___,  XmNy, &y___, NULL );
  upd_pos___ ( x___, y___ );
  XtPopdown ( dialog___ );
  XmUpdateDisplay ( dialog___ );
  Ops_Popup___ ();
}

void
ToggleBox_CB___ ( widget___, client_d___ )
Widget widget___;
XtPointer client_d___;
{
  static int dbl_clck___ = 0;
  static XtIntervalId id___;
  int i___ = * ( int * ) client_d___;
  if ( sel_tog___ [ i___ ] ) {
    sel_tog___ [ i___ ] = 0;
  }
  else {
    sel_tog___ [ i___ ] = 1;
  }
  if ( sel_one___ ) {
    if ( sec_visit___ ) {
      sec_visit___ = 0;
    }
    else {
      sec_visit___ = 1;
    }
    if ( sec_visit___ ) {
      if ( ! wait_flag___ )  {
        wait_flag___ = 1;
        id___ = XtAppAddTimeOut ( app___, mc_int___, ResetWaitFlag___, ( XtPointer ) NULL );
      }
      else {
        XtRemoveTimeOut ( id___ );
        wait_flag___ = 0;
        dbl_clck___ = 1;
      }
    }
    if ( dbl_clck___ ) {
      dbl_clck___ = 0;
      sel_tog___ [ i___ ] = 1;
      Popup_Dialog_CB___ ( XtParent ( XtParent ( widget___ ) ) );
    }
  }
  else {
    if ( ! wait_flag___ )  {
      wait_flag___ = 1;
      id___ = XtAppAddTimeOut ( app___, mc_int___, ResetWaitFlag___, ( XtPointer ) NULL );
    }
    else {
      XtRemoveTimeOut ( id___ );
      wait_flag___ = 0;
      dbl_clck___ = 1;
    }
    if ( dbl_clck___ ) {
      dbl_clck___ = 0;
      sel_tog___ [ i___ ] = 1;
      Popup_Dialog_CB___ ( XtParent ( XtParent ( widget___ ) ) );
    }
  }
}

void
Ops_Popup___ ()
{
  static Widget dialog___, dialog_form___, sep___, ok_form___, ok___, label___, rb_scroll___, rb___;
  static int height___;
  int i___;
  if ( ! dialog___ ) {
    dialog___ =  XmCreateDialogShell ( top_level___, "ItfDialog", NULL, 0 );
    dialog_form___ = cre_dialog_form___ ( "ItfDialog", dialog___ );
    sep___ = cre_sep___ ( "ItfDialog", dialog_form___ );
    ok_form___ = cre_ok_form___ ( "ButtonLabel", dialog_form___, sep___ );
    ok___ = cre_ok___ ( ok_form___ );
    XtAddCallback ( ok___, XmNactivateCallback,
                          ( XtCallbackProc ) Popup_Dialog_CB___, ( XtPointer ) NULL );
    label___ = cre_label___ ( "OpName", dialog_form___, "Test Operations", 20 );
    B_prog_icon___ = cre_B_logo___ ( dialog_form___, 5, 10 );
    height___ = 25 * opnames_tot___;
    if ( height___ > 600 ) {
      height___ = 600;
    }
    rb_scroll___ = cre_scroll___ ( "ItfDialog", dialog_form___, sep___, height___ );
    XtVaSetValues ( rb_scroll___,  XmNwidth, 250, NULL );
    rb___ = cre_rb___ ( "ItfDialog", rb_scroll___ );
    {
      Widget but;
      but = XtVaCreateManagedWidget (opnames___ [ 0 ],
          xmToggleButtonGadgetClass,     rb___,
          XmNspacing,                    2,
          NULL );
      XtAddCallback ( but, XmNvalueChangedCallback,
          ( XtCallbackProc ) ToggleBox_CB___, ( XtPointer ) & c_arr___ [ 0 ] );
      XmToggleButtonSetState ( but, TRUE, FALSE );
      sel_tog___ [ 0 ] = 1;
      for ( i___ = 1; i___ < opnames_tot___; i___++ ) {
        but = XtVaCreateManagedWidget (opnames___ [ i___ ],
            xmToggleButtonGadgetClass,     rb___,
            XmNspacing,                    2,
            NULL );
        XtAddCallback ( but, XmNvalueChangedCallback,
            ( XtCallbackProc ) ToggleBox_CB___, ( XtPointer ) & c_arr___ [ i___ ] );
        sel_tog___ [ i___ ] = 0;
      }
      Ini_nx_ny___ ();
      XtVaSetValues ( dialog_form___, 
          XmNx,         nx___,
          XmNy,         ny___,
          NULL );
    }
    sel_one___ = 1;
    sec_visit___ = 1;
    XtManageChild ( label___ );
    XtManageChild ( rb_scroll___ );
    XtManageChild ( rb___ );
    XtManageChild ( ok_form___ );
    XtManageChild ( dialog_form___ );
  }
  XtPopup ( dialog___, XtGrabNone );
}

void
op___ ()
{
  op ();
  DisplayMWText___ ( "No values returned\n" );
  Ops_Popup___ ();
}

void
op_D___ ()
{
  strcpy ( buf___, "\nop:\n");
  DisplayMWText___ ( buf___ );
  op___ ();
}

void
OpsSwitch___ ( op_num___ )
int op_num___;
{
  switch ( op_num___ ) {
  case 0:
    op_D___  ();
    break;
  }
}

void
done_but_CB___ ()
{
  exit ( 0 );
}

main ( argc, argv )
int argc;
char * * argv;
{
  XtToolkitInitialize ();
  app___ = XtCreateApplicationContext ();
  XtSetLanguageProc ( NULL, NULL, NULL );
  display___ = XtOpenDisplay ( app___, NULL, argv[0], "XBMotif",NULL, 0, &argc, argv );
  if ( ! display___ ) { XtWarning ( "          Can't open display, exiting  " ); exit ( 1 ); }
  XtDisplayInitialize ( app___, display___, argv[0], "XBMotif", NULL, 0, &argc, argv );
  top_level___ = XtAppCreateShell ( argv[0], "XBMotif", applicationShellWidgetClass, display___, NULL, 0 );
  XmRepTypeInstallTearOffModelConverter ();
  cre_pixmap___ ();
  {
    int i___;
    for ( i___ = 0 ; i___ < 1000 ; i___++ ) {
      c_arr___ [ i___ ] = i___;
    }
  }
  main_form___ = XtVaCreateWidget ( "Interface",
      xmFormWidgetClass,          top_level___,
      NULL );
  xstr___ =  XmStringCreateLtoR ( " B-Toolkit 4.1n Beta ", charset___ );
  B_prog_icon___ = cre_B_logo___ ( main_form___, 10, 10 );
  prog_label___ = XtVaCreateWidget ( "Label", 
      xmLabelWidgetClass,          main_form___,
      XmNtopAttachment,            XmATTACH_FORM,
      XmNtopOffset,                15,
      XmNleftAttachment,           XmATTACH_FORM,
      XmNrightAttachment,          XmATTACH_WIDGET,
      XmNrightWidget,              B_prog_icon___,
      XmNlabelString,              xstr___,
      XmNtraversalOn,              False,
      NULL );
  XmStringFree ( xstr___ );
  xstr___ = XmStringCreateLtoR ( "Done", charset___ );
  done_but___ =  XtVaCreateWidget ( "ButtonLabel",
      xmPushButtonWidgetClass,      main_form___,
      XmNbottomAttachment,          XmATTACH_FORM,
      XmNbottomOffset,              10,
      XmNleftAttachment,            XmATTACH_FORM,
      XmNleftOffset,                15,
      XmNlabelString,               xstr___,
      XmNmarginWidth,               5,
      XmNmarginHeight,              5,
      XmNdefaultButtonShadowThickness,        1,
      XmNhighlightThickness,        1,
      NULL );
  XmStringFree ( xstr___ );
  XtAddCallback ( done_but___, XmNactivateCallback, ( XtCallbackProc ) done_but_CB___, ( XtPointer ) NULL );
  monolog_frame___ = XtVaCreateWidget ( "Frame", 
      xmFrameWidgetClass,           main_form___,
      XmNtopAttachment,             XmATTACH_WIDGET,
      XmNtopWidget,                 prog_label___,
      XmNtopOffset,                 15,
      XmNleftAttachment,            XmATTACH_FORM,
      XmNleftOffset,                10,
      XmNrightAttachment,           XmATTACH_FORM,
      XmNrightOffset,               10,
      XmNbottomAttachment,          XmATTACH_WIDGET,
      XmNbottomWidget,              done_but___,
      XmNbottomOffset,              10,
      XmNshadowType,                XmSHADOW_ETCHED_IN,
      XmNmarginWidth,               15,
      XmNmarginHeight,              15,
      XmNtraversalOn,               False,
      NULL );
  {
    Arg args [ 15 ];
    int n = 0;
    XtSetArg ( args [ n ], XmNrows,                  45                ); n++;
    XtSetArg ( args [ n ], XmNcolumns,               60                ); n++;
    XtSetArg ( args [ n ], XmNeditable,              False             ); n++;
    XtSetArg ( args [ n ], XmNeditMode,              XmMULTI_LINE_EDIT ); n++;
    XtSetArg ( args [ n ], XmNcursorPositionVisible, False             ); n++;
    XtSetArg ( args [ n ], XmNscrollHorizontal,      False             ); n++;
    XtSetArg ( args [ n ], XmNwordWrap,              True              ); n++;
    XtSetArg ( args [ n ], XmNmarginWidth,           5                 ); n++;
    XtSetArg ( args [ n ], XmNmarginHeight,          5                 ); n++;
    XtSetArg ( args [ n ], XmNtraversalOn,           False            ); n++;
    monolog_text___ = XmCreateScrolledText ( monolog_frame___, "Canvas", args, n );
  }
  mc_int___ = XtGetMultiClickTime ( XtDisplay ( top_level___ ) );
  XtManageChild ( prog_label___ );
  XtManageChild ( done_but___ );
  XtManageChild ( monolog_text___ );
  XtManageChild ( monolog_frame___ );
  XtManageChild ( main_form___ );
  XtRealizeWidget ( top_level___ );
  INI_Test ();
  INI_file_dump ();
  INI_btl_proof_file_dump ();
  INI_basic_io ();
  INI_String_TYPE ();
  INI_Bool_TYPE ();
  INI_Scalar_TYPE ();
  INI_btl_proofCtx ();
  Ops_Popup___ ();
  DisplayMWText___ ( "Program output:\n");
  XtAppMainLoop ( app___ );
}
