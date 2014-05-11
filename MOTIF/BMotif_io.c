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
#include "BMotif_globals.h"

#include "../C/BToolkitlm_globals.h"

extern char * no_toolkit_short_ver;

/*#include "../C/BToolkitd_common.c"*/


/**************************************************
             B communication/interrupts
***************************************************/

/* error messages now go to stderr. NOTE: In a gui environment should go in a window if no tty */

void
AbortedMsg ()
{
    fprintf ( stderr,  "\n                   B-Toolkit Aborted" );
    fprintf ( stderr,  "\n\n             All data has been preserved\n\n\n" );
}

void
AbortedBaseMsgCode ( exit_code )
int exit_code;
{
    fprintf ( stderr,  "\n\n                  B-Toolkit Terminated" );
    fprintf ( stderr,  "\n\n                    Exit code: %d", exit_code + 11800);
    fprintf ( stderr,  "\n\n             All data has been preserved\n\n\n" );
}

void
AbortedMsgCodeWithMsg ( exit_code, buf )
int exit_code;
char * buf;
{
    fprintf ( stderr,  "\n\n                  B-Toolkit Terminated" );
    fprintf ( stderr,  "\n\n                    Exit code: %d", exit_code );
    if( buf != NULL && buf[0] != '\0' )
    {
        fprintf ( stderr,  "\n\n                      (%s)", buf );
    }
    else if( buf == NULL || buf[0] == '\0' )
    {
        fprintf ( stderr,  "\n\n             See: %s/ErrorCodes", BKIT_path );
    }
    fprintf ( stderr,  "\n\n             All data has been preserved\n\n\n" );
}

void
AbortedMsgCode ( exit_code )
int exit_code;
{
    char temp[255] = "";

    switch ( exit_code ) {
    case 13242:
    case 13243:
    case 18011:
      AbortedMsgCodeWithMsg ( exit_code, "BToolkit licence has now expired" );
      break;
    case 13298:
      AbortedMsgCodeWithMsg ( exit_code, "$HOME/BHW.licence or $BKIT/BHW.licence has now expired" );
      break;
    case 13299:
      AbortedMsgCodeWithMsg ( exit_code, "$HOME/BHW.licence or $BKIT/BHW.licence does not authorise this platform" );
      break;
    case 13244:
      sprintf(temp,"Number of authorised users exceeds that allowed\n\n  Run: %s/BToolkitd_util\n\n", BKIT_path);
      AbortedMsgCodeWithMsg ( exit_code, temp );
      break;
    case 13246:
    case 13247:
      AbortedMsgCodeWithMsg ( exit_code, "The BToolkit licence does not include this platform" );
      break;
    case 13249:
      AbortedMsgCodeWithMsg ( exit_code, "This licence has been removed (maybe BToolkitd has been restarted?)\n\n                   Restart the BToolkit" );
      break;
    case 13270:
      sprintf(temp,"Cannot perform malloc: %s",strerror(errno));
      AbortedMsgCodeWithMsg ( exit_code, temp );
      break;
    case 13271:
      sprintf(temp,"Cannot perform realloc: %s",strerror(errno));
      AbortedMsgCodeWithMsg ( exit_code, temp );
      break;
    case 12224:
    case 12225:
    case 12226:
    case 13771:
    case 13772:
    case 13773:
    case 13812:
    case 13813:
    case 13814:
    case 13815:
    case 13816:
    case 13821:
    case 13822:
    case 13823:
    case 13824:
    case 13825:
    case 13933:
      AbortedMsgCodeWithMsg ( exit_code, "Bad return code from system call; contact B-Core" );
      break;
    case 13934:
      AbortedMsgCodeWithMsg ( exit_code, "Cant execute a BToolkit shell; contact B-Core" );
      break;
    case 15281:
    case 15282:
    case 15283:
    case 15284:
    case 15285:
    case 15286:
    case 15287:
    case 15288:
    case 15289:
      AbortedMsgCodeWithMsg ( exit_code, "Run `$BKIT/BProcessInfo'; contact B-Core" );
      break;
    default:
      AbortedMsgCodeWithMsg ( exit_code, NULL );
    }
}

void
AbortedMsgFile ( file_msg )
char * file_msg;
{
    fprintf ( stderr,  "\n\n             BMotif: can't open %s", file_msg );
    fprintf ( stderr,  "\n\n                  B-Toolkit Terminated" );
    fprintf ( stderr,  "\n\n             All data has been preserved\n\n\n" );
}

void
SRC_watch_timer_once_only ( client_data )
XtPointer client_data;
{
  void SRC_watch ();
/***
printf ( "SRC_watch_timer_once_only\n" );
***/
    SRC_watch ();
}

void
SRC_watch_timer ( client_data )
XtPointer client_data;
{
  void SRC_watch ();

  if  ( ! ( IsDeSensitized () ) ) {
    SRC_watch ();
  }
/***
else { printf ( "SRC_watch_timer - but desensitized\n" ); }
***/

  if   ( total_edits ) SRC_watch_cycle = short_SRC_watch_cycle;
  else                 SRC_watch_cycle = long_SRC_watch_cycle;

  SRC_watch_id = XtAppAddTimeOut ( app, SRC_watch_cycle,
                   ( XtTimerCallbackProc ) SRC_watch_timer, NULL );
}

void
Process_SetInvokeBLogoFlashTimer_ini ()
{
  InvokeBLogoFlashTimer_flag = 0;
  InvokeBLogoFlashTimer_id = XtAppAddTimeOut ( app, InvokeBLogoFlashTimer_delay_ini,
                   ( XtTimerCallbackProc ) Process_SetInvokeBLogoFlashTimer, NULL );
}

void
Process_SetInvokeBLogoFlashTimer_fini ()
{
  XtRemoveTimeOut ( InvokeBLogoFlashTimer_id );
  XtVaSetValues ( B_button, XmNlabelPixmap, B_framed_pixmap_gray94, NULL );
  InvokeBLogoFlashTimer_flag = -1;
  XmUpdateDisplay ( B_button );
  XmUpdateDisplay ( top_level );
}

XtTimerCallbackProc
Process_SetInvokeBLogoFlashTimer ( client_data )   /* from XtAppAddTimeOut() */
XtPointer client_data;
{
/***
  printf ( "Process_SetInvokeBLogoFlashTimer: %d\n", InvokeBLogoFlashTimer_flag );
***/
  switch ( InvokeBLogoFlashTimer_flag ) {
  case 0:
    InvokeBLogoFlashTimer_flag = 1;
    XtVaSetValues ( B_button, XmNlabelPixmap, B_framed_pixmap_inverse, NULL );
    XmUpdateDisplay ( B_button );
    XmUpdateDisplay ( top_level );
    InvokeBLogoFlashTimer_id = XtAppAddTimeOut ( app, InvokeBLogoFlashTimer_delay_on,
                            ( XtTimerCallbackProc ) Process_SetInvokeBLogoFlashTimer, NULL );
    break;
  case 1:
    InvokeBLogoFlashTimer_flag = 0;
    XtVaSetValues ( B_button, XmNlabelPixmap, B_framed_pixmap_gray94, NULL );
    XmUpdateDisplay ( B_button );
    InvokeBLogoFlashTimer_id = XtAppAddTimeOut ( app, InvokeBLogoFlashTimer_delay_off,
                            ( XtTimerCallbackProc ) Process_SetInvokeBLogoFlashTimer, NULL );
    break;
  }
}

void
interrupt_SIGUSR2 ()  /* bplatform out of memory, etc */
{
  XtIntervalId id = XtAppAddTimeOut ( app, ( long unsigned ) 1,
                   ( XtTimerCallbackProc ) Process_interrupt_SIGUSR2, NULL );
}

XtTimerCallbackProc
Process_interrupt_SIGUSR2 ( client_data )   /* client_data from XtAppAddTimeOut() */
XtPointer client_data;
{
  char buf [ 3002 ];

/***
  printf("\n  SIGUSR2 received (from bplatform)\n" );
printf( "    (Popup_Sel_flag %d  radiobox_flag %d)\n", Popup_Sel_flag, radiobox_flag );
***/

/*
  XtSetSensitive ( InterruptPullDown, False );
*/

  LoadFileIntoBuf ( ".Bcom", buf, 3001 );
  process_XTerm_IfReq ();
  if ( strcmp ( buf, "" ) == 0 ) {
    DisplayCurrWinText ( "\n\n\n  Problem running B-Toolkit\n\n" );
    Popup_Err ( 999999, " Problem running B-Toolkit " );
  }
  else {
    DisplayCurrWinText ( buf );
    DisplayCurrWinText ( "\n" );
    if ( strlen ( buf ) ) puts ( buf );
    Popup_Err ( 0, "  Can't complete current job " );
  }
}


void
interrupt_CRASH (sig, code, scp, addr)  /* yes - a real crash */
int sig, code;
struct sigcontext *scp;
char *addr;
{
  XtIntervalId id = XtAppAddTimeOut ( app, ( long unsigned ) 1,
                   ( XtTimerCallbackProc ) Process_interrupt_CRASH,
                   ( XtPointer ) & c_arr [ sig ] );
/***
  printf ( "\n\n  sig: %d  code: %d\n\n", sig, code );
***/
}

XtTimerCallbackProc
Process_interrupt_CRASH ( client_data )   /* client_data from XtAppAddTimeOut() */
XtPointer client_data;
{
  BT_crash_err_exit ( * ( int * ) client_data );
  
  unlink ( pid_id_file );
  exit ( 1 );
}

void
process_XTerm_IfReq ()
{
  if ( xterm_is_up ) {
    xterm_is_up = 0;
    DisplayXTermText ();
    KillXTerm ();
    if ( post_process_xterm_text [ 0 ] != '\0' ) {
      DisplayCurrWinText ( post_process_xterm_text );
      post_process_xterm_text [ 0 ] = '\0';
    }
  }
  if ( interrupt_option ) {
    interrupt_option = 0;
    XBell ( display, -75 );
    DisplayCurrWinText ( "\n\n  Interrupted!\n" );
    translating_pre_MInterface = 0;
    unlink ( ".Brec" );
  }
}

int from_option;

void
interrupt_SIGUSR1 ()  /* normal resume from SignalToM */
{
  static int initialised = 0;
  XtIntervalId id;
  void ProcessB ();

/***
printf ( "interrupt_SIGUSR1 %d\n", ReturnFromB_option );
***/

/*****************************************************************/
#ifdef FIFO_TRACE_FLAG
printf ( "BMotif: received SIGUSR1\n" );
#endif /* FIFO_TRACE_FLAG */
/*****************************************************************/

  if ( initialised ) {
    id = XtAppAddTimeOut ( app, ( long unsigned ) 1,
                   ( XtTimerCallbackProc ) Process_interrupt_SIGUSR1, NULL );
  }
  else {
    initialised = 1;
    ReturnFromB_option = from_InvokeB;
    ProcessB (); /* BT_INI_M,1,0/BT_INI_M,0,0 from Tk1 */    
  } 
}

XtTimerCallbackProc
Process_interrupt_SIGUSR1 ( client_data )   /* client_data from XtAppAddTimeOut() */
XtPointer client_data;
{

  void ProcessB ();

/***
printf ( "Process_interrupt_SIGUSR1 %d\n", ReturnFromB_option );
***/

  Process_SetInvokeBLogoFlashTimer_fini ();

  /***
  reset ReturnFromB_option 
  ***/
  from_option = ReturnFromB_option;
  ReturnFromB_option = from_InvokeB;

/***
  if (  from_option == from_EditedFileExists ) printf ( "from_EditedFileExists)\n" );
  if (  from_option == from_AnmEditThy ) printf ( "from_AnmEditThy)\n" );
***/

/***
  printf("\nSIGUSR1 received from bplatform (" );
  if (  from_option == from_CheckFileParses ) printf ( "from_CheckFileParses)\n" );
  if (  from_option == from_InvokeB )         printf ( "from_InvokeB)\n" );
  if (  from_option == from_Popup_Err_CB )    printf ( "from_Popup_Err_CB)\n" );
***/

  switch ( from_option ) {

  case from_new_dir:
/***
if (  from_option == from_new_dir )         printf ( "from_new_dir\n" );
***/
    ProcessB (); /* BT_INI_M,1,0/BT_INI_M,0,0 from Tk1 */
    break;

  case from_CheckFileParses:

    ProcessB ();
    file_parses = ( strcmp ( primary_string, "0" ) == 0 );
    if ( ! file_parses ) {
      LoadFileIntoBuf ( ".Bcom", buf, 3000 );
      DisplayCurrWinText ( "\n" );
      DisplayCurrWinText ( buf );
    }
    CheckFileParses_contd ();
    break;

  case from_InvokeB:

    ProcessB ();
    break;

  case from_Popup_Err_CB:

    AbortedMsg ();
    if ( xterm_is_up ) {
      xterm_is_up = 0;
      KillXTerm ();
    }
    
    unlink ( pid_id_file );
    exit ( 1 );
    break;


  }  /* switch ( from_option ) */
}

void
CreateXTerm ()
{
  Position tx, ty, y;
  Dimension w, h;

/***
printf ( "CreateXTerm ()\n" );
***/

  unlink ( ".Blog" );
  unlink ( ".Btty" );
  unlink ( ".Bpix" );
  XtVaGetValues ( top_level, XmNx, &tx, NULL );
  XtVaGetValues ( top_level, XmNy, &ty, NULL );
  XtVaGetValues ( bottom_frame_form, XmNy,      &y, NULL );
  XtVaGetValues ( bottom_frame_form, XmNwidth,  &w, NULL );
  XtVaGetValues ( bottom_frame_form, XmNheight, &h, NULL );
/***
printf("tx: %d   ty: %d         y: %d   w: %d   h: %d\n",tx,ty,y,w,h);
***/

  strcpy ( buf, "\"" );
  strcat ( buf, xterm_title );
  strcat ( buf, " -geometry " );

  /***
  76 - 6 = 70! (increase 6 for greater variation between smallest/largest)
  26 - 5 = 21! (increase 5 ...)
  ***/
  if   ( ( ( curr_env != anm_env )                                    &&
           ( curr_env != ipr_pob_env )                                   ) || 
         ( strcmp ( xterm_title, "B-Animator-Execute-Auto" ) == 0 )           ) {
    CreNumInBuf ( buf, ( ( 76 * ( int ) w ) / 522 ) - 7 );
    strcat ( buf, "x" );
    CreNumInBuf ( buf, ( ( ( 778 * ( int ) h ) / 10000 ) - 3 ) );
    strcat ( buf, "+" );
    CreNumInBuf ( buf, ( int ) tx + 5 );
    strcat ( buf, "+" );
    CreNumInBuf ( buf, ( int ) y + ( int ) ty + 39 );
  }
  else {
    strcat ( buf, "65x35+" );
    CreNumInBuf ( buf, ( int ) tx + ( int ) w + 7 );
    strcat ( buf, "+1" );
  }
  strcat ( buf, "\":156:0" );   /* BT_XTM_BGD - hard-wired */

/***
printf ( "   ================================================\n" );
fflush ( stdout );
printf ( "                InvokeB ( CreateXTerm )\n" );
fflush ( stdout );
printf ( "      %s\n", buf );
printf ( "      IsDeSensitized=%d  xterm_is_up=%d\n",
                                                  IsDeSensitized (), xterm_is_up );
fflush ( stdout );
printf ( "   ================================================\n" );
fflush ( stdout );
***/

  xterm_is_up = 1;

  Process_SetInvokeBLogoFlashTimer_ini ();

/***
printf ( "about to Write_FIFO (%s)\n", buf );
***/
  Write_FIFO ( buf );
}

void
KillXTerm ()
{
  FILE * fileid;
  int i, c, count, done;

  /***
  load Bpix
  ***/
  count = 0;
  done = 0;

  while ( ! done && count < 29 ) {
    fileid = fopen ( ".Bpix", "r" );
    if ( fileid != NULL ) {
      done = 1;
      i = 0;
      c = getc ( fileid );
      while ( c != EOF && c != '\n' ) {
        i = ( i * 10 ) + c - '0';
        c = getc ( fileid );
      }
      fclose ( fileid );
      unlink ( ".Bpix" );
      kill ( i, SIGKILL );
    }
    else {
      count ++;
      if ( ( ( count / 100 ) * 100 ) == count ) {
        DisplayCurrWinText ( "\n  Trying to kill xterm ...\n" );
      }
      sleep ( 1 );
    }
  }

  if ( ! done ) {
    printf( "\n  BMotif: can't open .Bpix (xterm) for reading\n" );
    BT_err_exit ( 0 );
    return;
  }

  unlink ( ".Btty" );
  unlink ( ".Bpix" );
  unlink ( ".Bxok" );
}

FILE * Blog;

void
DisplayXTermHighlightText ()
{
  char buf [ 3001 ];
  int i, c, done;
  XmTextPosition start_curr_text_posn;

  start_curr_text_posn = curr_text_posn;
  done = 0;
  c = getc ( Blog );
  while ( c != EOF /* && c != 27 &&  c != '[' */  && ! done ) {
    i = 0;
    while ( c != EOF && i < 2999 && /* c != 27 && */ c != '[' && ! done ) {
/***
printf("buf [ %d ] = ( char )   %c    (   %d   )\n",i,(char)c,(int)c);
printf("(   %d   )\n",(int)c);
***/
      buf [ i ] = ( char ) c;
      i++;
      c = getc ( Blog );
    }
    if ( c == '[' ) {
      buf [ i ] = '\0';
      if ( i > 0 && buf [ i - 1 ] == 27 ) {
        buf [ i - 1 ] = '\0';
      }
/***
printf("printing buf |||||%s|||||\n",buf);
***/
      DisplayCurrWinText ( buf );
      c = getc ( Blog );
      if ( c == '0' ) {
        c = getc ( Blog );
        if ( c == 'm' ) {
          XmTextSetHighlight ( curr_text, start_curr_text_posn,
                                    curr_text_posn, XmHIGHLIGHT_SELECTED );
          done = 1;
	}
        else {
          DisplayCurrWinText ( "[m" );
	}
      }
      else {
        DisplayCurrWinText ( "[" );
      }
    }
    else {
      buf [ i ] = '\0';
      DisplayCurrWinText ( buf );
    }
  }
}

void
DisplayXTermText ()
{
  char buf [ 3001 ];
  int i, c;
  Blog = fopen ( ".Blog", "r" );
  while ( Blog == NULL ) {
    sleep ( 1 );
    Blog = fopen ( ".Blog", "r" );
  }
  c = getc ( Blog );
  while ( c != EOF ) {
    i = 0;
    while ( c != EOF && i < 2999 && c != '[' ) {
      buf [ i ] = ( char ) c;
      i++;
      c = getc ( Blog );
    }
    if ( c == '[' ) {
      buf [ i ] = '\0';
      if ( i > 0 && buf [ i - 1 ] == 27 ) {
        buf [ i - 1 ] = '\0';
      }
/***
printf ( "DisplayCurrWinText |||||%s|||||\n", buf );
printf ( " buf [ i - 1 ]: %d %c\n",  ( int ) buf [ i - 1 ], ( char ) buf [ i - 1 ] );
printf ( " buf [ i - 2 ]: %d %c\n",  ( int ) buf [ i - 2 ], ( char ) buf [ i - 2 ]  );
***/
      DisplayCurrWinText ( buf );
      c = getc ( Blog );
      if ( c == '7' ) {
        c = getc ( Blog );
        if ( c == 'm' ) {
          DisplayXTermHighlightText ();
          c = getc ( Blog );
	}
        else {
          DisplayCurrWinText ( "[7" );
	}
      }
      else {
        DisplayCurrWinText ( "[" );
      }
    }
    else {
      buf [ i ] = '\0';
      DisplayCurrWinText ( buf );
    }
  }
  fclose ( Blog );
}


void
display_non_parse_text ( filename )
char * filename;
{
  FILE *BBcom;
  FILE *fileid;
  int err_line, i, c, cb, nl_count, start;
  char line_num_buf [ 10 ];
  char buf [ 1024 ];
  int done = 0;
  int display_range = 2;

  BBcom = fopen ( ".BBcom" , "r" );
  if ( BBcom == NULL ) {
    return;
  }

  cb = getc ( BBcom );
  while ( ! done ) {
  err_line = 0;
    while ( cb == ' ' ) {
      cb = getc ( BBcom );
    }
    while ( cb != EOF && cb != ' ' ) {
      err_line = ( ( err_line * 10 ) + cb - '0' );
      cb = getc ( BBcom );
    }
    while ( cb == ' ' ) {
      cb = getc ( BBcom );
    }
    if ( cb == EOF ) {
      done = 1;
    }

    fileid = fopen ( filename , "r" );
    if ( fileid == NULL ) {
      fclose ( BBcom );
      return;
    }
    nl_count = 0;
    c = getc ( fileid );
    start = err_line - display_range - 1;
    if ( start < 0 ) {
      start = 0;
    }
    while ( c != EOF && nl_count != start ) {
      if ( c == '\n' ) {
        nl_count++;
      }
      c = getc ( fileid );
    }
    if ( c != EOF ) {
      while ( c != EOF && nl_count != err_line + display_range ) {
        i = 0;
        while ( c != EOF && c != '\n' ) {
          buf [ i ] = ( char ) c;
          c = getc ( fileid );
          i++;
        }
        buf [ i ] = '\n';
        buf [ i + 1 ] = '\0';
        nl_count++;
        if ( nl_count == err_line ) {
          strcpy ( line_num_buf, ">" );
        }
        else {
          strcpy ( line_num_buf, " " );
        }
        if ( nl_count > 99 ) {
          strcat ( line_num_buf, " " );
        }
        else if ( nl_count > 9 ) {
          strcat ( line_num_buf, "  " );
        }
        else {
          strcat ( line_num_buf, "   " );
        }
        CreNumInBuf ( line_num_buf, nl_count );
        strcat ( line_num_buf, "  " );
        DisplayCurrWinText ( line_num_buf );
        DisplayCurrWinText ( buf );
        if ( c != EOF ) {
          c = getc ( fileid );
        }
      }
      DisplayCurrWinText ( "\n" );
    }
  }
  fclose ( BBcom );
  fclose ( fileid );
}

void
BaseCapacityReached ()
{
  terminal_option = 1;
  sprintf ( buf, "\n  Construct capacity reached (%d)\n", MAX_NUM_CONSTRUCTS );
  DisplayCurrWinText ( buf );
  Popup_Capacity_Err ( 0, "Construct capacity reached", 85 );
}

void
execute ( cmd )
char * cmd;
{
  int ret_cde = system ( cmd );

  if ( ret_cde != 0 ) {
    char execute_buf [ 1000 ];
    strcpy ( execute_buf, "\n  Didn't get 0 return from system call:\n    ");
    strcat ( execute_buf, cmd );
    strcat ( execute_buf, "\n  Code returned: " );
    CreNumInBuf ( execute_buf, ret_cde );
    strcat ( execute_buf, "\n" );
    DisplayCurrWinText ( execute_buf );
    Popup_Err ( 0, "Bad system call return code   " );
  }
/***
  if ( ret_cde != 0 ) {
    fprintf ( stderr, "\n  Code returned from %s: %d\n", cmd, ret_cde );
  }
***/
}

void
WarnBaseCapacityApproaching ()
{
  DisplayCurrWinText ( "\n  Construct total within 10 of maximum capacity!\n" );
  Popup_Err ( 0, "Constructs total within 10 of maximum capacity" );
}


void
LoadBSelRecLists ()
{
  int rr, nn, cc, cc1;
  int  ext, name [ 50 ];

  GetExtNumFromString ( &ext, primary_string );
  GetNameFromString ( name, primary_string );
  GetObjFromNameExt ( &cc,  name, ext );

  strcpy ( fifo_write_buf, "(" );

  get_recseenipt_mchlist ( &rr, cc );
  if ( ! rr ) {
    BT_err_exit ( 24 );    
    return;
  }
  strcat ( fifo_write_buf, "?" );
  card_gset1( &nn );
  while ( nn ) {
    valOrd_gset1 ( &cc1, nn );
    xtr_name ( name, cc1 );
    strcat ( fifo_write_buf, "," );
    strcat ( fifo_write_buf, ( char * ) name );
    strcat ( fifo_write_buf, ".mch" );
    nn = nn - 1;
  }

  strcat ( fifo_write_buf, "|" );

  get_recipt_mchlist ( &rr, cc );
  if ( ! rr ) {
    BT_err_exit ( 25 );    
    return;
  }
  strcat ( fifo_write_buf, "?" );
  while ( nn ) {
    valOrd_gset1 ( &cc1, nn );
    xtr_name ( name, cc1 );
    strcat ( fifo_write_buf, "," );
    strcat ( fifo_write_buf, ( char * ) name );
    strcat ( fifo_write_buf, ".mch" );
    nn = nn - 1;
  }

  strcat ( fifo_write_buf, "):" );
}

void
ReDisplayCurrEnvFromBrowser ()
{
  XtUnmanageChild ( constructs_scroll );
  DisplayCurrentEnv ();
}

/*
void
WriteBtlb ()
{
  FILE * Btlb;

  Btlb = fopen ( ".Btlb", "w" );
  if ( Btlb == NULL ) {
    perror( ".Btlb" );
    return;
  }
  
  Retrieve_String ( teamlib_str_num, buf );

  fprintf ( Btlb, "\"%s\"", buf );
  fclose ( Btlb );  
}
*/

void
WriteBpog ()
{
  FILE * Bpog;
  int n;

  Bpog = fopen ( "TMP/.Bpog", "w" );
  if ( Bpog == NULL ) {
    printf ( "\n  BMotif: can't open TMP/.Bpog for writing\n" );
    BT_err_exit ( 0 );
    return;
  }
  valIth_flags ( &n, POG_Option_num );
  PrintNum ( Bpog, n );
  fclose ( Bpog );
/***
printf ( "--> WriteBpog - %d\n", n );
***/
}

void
WriteBmfh ()
{
  FILE * Bmfh;

  Bmfh = fopen ( "TMP/.Bmfh", "w" );
  if ( Bmfh == NULL ) {
    perror( ".Bmfh" );
    return;
  }

  fprintf ( Bmfh, "%d", max_fwd_ctr_auto_prf );
  fclose ( Bmfh );  
/***
printf ( "Just wrote TMP/.Bmfh: max_fwd_ctr_auto_prf %d\n", max_fwd_ctr_auto_prf );
***/
}


void
WriteBplf ()
{
  FILE * Bplf;
  int Prog_Language_Option, Interface_Option;
  char buf1 [ 151 ];
  char buf2 [ 151 ];
  char buf3 [ 151 ];

  Bplf = fopen ( ".Bplf", "w" );
  if ( Bplf == NULL ) {
    perror( ".Bplf" );
    return;
  }
  
  valIth_flags ( &Prog_Language_Option, Prog_Language_Option_num );
  valIth_flags ( &Interface_Option, Interface_Option_num );
  Retrieve_String ( cc_compiler_str_num, buf1 );
  Retrieve_String ( cc_link_lib_str_num, buf2 );
  Retrieve_String ( cc_Xlink_lib_str_num, buf3 );
  
  fprintf ( Bplf, "%c;%c;\"'%s'\";\"'%s'\";\"'%s'\"",
      Interface_Option + '0', Prog_Language_Option + '0', buf1, buf2, buf3 );
/***
printf ( " Interface_Option %d\n", Interface_Option );
***/
  fclose ( Bplf );  
}

int
All_ws ( sss )
char * sss;
{
  int i = 0;

  while ( ( sss [ i ] == ' ' ) || ( sss [ i ] == '\t' ) || ( sss [ i ] == '\n' ) ) {
    i++;
  }
  return ( ( i == strlen ( sss ) ) != 0 );
}

void
WriteBdmf ()
{
  /***
  format:
    DMU_Labels_Option_num,
    DMU_ClIndex_Option_num,
    DMU_CoIndex_Option_num,
    DMU_GIndex_Option_num,
    "prologue",
    "latex executable"
  ***/

  FILE * Bdmf;
  int option, i;

  Bdmf = fopen ( ".Bdmf", "w" );
  if ( Bdmf == NULL ) {
    perror( ".Bdmf" );
    return;
  }
  
  valIth_flags ( &option, DMU_Labels_Option_num );
  putc ( option + '0', Bdmf );
  putc ( ',', Bdmf );

  valIth_flags ( &option, DMU_ClIndex_Option_num );
  putc ( option + '0', Bdmf );
  putc ( ',', Bdmf );

  valIth_flags ( &option, DMU_CoIndex_Option_num );
  putc ( option + '0', Bdmf );
  putc ( ',', Bdmf );

  valIth_flags ( &option, DMU_GIndex_Option_num );
  putc ( option + '0', Bdmf );
  putc ( ',', Bdmf );

  str_buf [ 0 ] = '\0';
  Retrieve_String ( latex_declaration_str_num, str_buf );
  if ( All_ws ( str_buf ) ) {
    fprintf ( Bdmf, "\"\\documentclass [" );
    valIth_flags ( &option, Point_Size_Option_num );
    switch ( option ) {
    case 11:
      fprintf ( Bdmf, "11pt" );
      break;
    case 12:
      fprintf ( Bdmf, "12pt" );
      break;
    }
    fprintf ( Bdmf, "]{article} \\usepackage{Bkit}\"," );
  }
  else {
    fprintf ( Bdmf, "\"%s\",", str_buf );
  }

  str_buf [ 0 ] = '\0';
  Retrieve_String ( latex_exec_name_str_num, str_buf );
  if ( All_ws ( str_buf ) ) {
    fprintf ( Bdmf, "\"latex\"" );
  }
  else {
    fprintf ( Bdmf, "\"%s\"", str_buf );
  }
  fclose ( Bdmf );
/***
printf("\nwrote .Bdmf\n");
***/
}

void
Cre_fifo_write_buf_cmd_env ( obj, BT_VAL, cc_lenpob )
int obj;
int BT_VAL;
int cc_lenpob;
{
  /***
  cc_obj_name:BT_VAL
  then Cre_tcp_env called
  ***/

  /*** 
  empty fifo_write_buf
  ***/

  fifo_write_buf [ 0 ] = '\0';

  /*** 
  cc_obj_name
  ***/

  if ( BT_VAL == BT_SRC ) {
    strcat ( fifo_write_buf, "0" );  
  }
  else {
    strcat ( fifo_write_buf, GetName ( obj ) );
  }
  if ( BT_VAL == BT_AUP_WITH_ENV ) {
    strcat ( fifo_write_buf, "." );
    CreNumInBuf ( fifo_write_buf, cc_lenpob-1 );
  }

  /*** 
  BT_VAL
  ***/

  strcat ( fifo_write_buf, ":" );
  CreNumInBuf ( fifo_write_buf, BT_VAL );

  Cre_tcp_env ();
}

void
Cre_fifo_write_buf_cmd_num ( BT_VAL, num )
int BT_VAL;
int num;
{
  /***
  pre-loaded fifo_write_buf (ending in :)
  BT_VAL : num
  ***/

  int ll = strlen ( fifo_write_buf );
  if ( BT_VAL < 10 ) {
    fifo_write_buf [ ll + 0 ] = BT_VAL + '0';
    fifo_write_buf [ ll + 1 ] = ':';
    fifo_write_buf [ ll + 2 ] = '\0';
  }
  else if ( BT_VAL < 100 ) {
    fifo_write_buf [ ll + 0 ] = ( BT_VAL / 10 ) + '0';
    fifo_write_buf [ ll + 1 ] = ( BT_VAL % 10 ) + '0';
    fifo_write_buf [ ll + 2 ] = ':';
    fifo_write_buf [ ll + 3 ] = '\0';
  }
  else {
    fifo_write_buf [ ll + 0 ] = ( BT_VAL / 100 ) + '0';
    BT_VAL = BT_VAL % 100;
    fifo_write_buf [ ll + 1 ] = ( BT_VAL / 10 ) + '0';
    fifo_write_buf [ ll + 2 ] = ( BT_VAL % 10 ) + '0';
    fifo_write_buf [ ll + 3 ] = ':';
    fifo_write_buf [ ll + 4 ] = '\0';
  }

  ll = strlen ( fifo_write_buf );
  if ( num < 10 ) {
    fifo_write_buf [ ll + 0 ] = num + '0';
    fifo_write_buf [ ll + 1 ] = '\0';
  }
  else if ( num < 100 ) {
    fifo_write_buf [ ll + 0 ] = ( num / 10 ) + '0';
    fifo_write_buf [ ll + 1 ] = ( num % 10 ) + '0';
    fifo_write_buf [ ll + 2 ] = '\0';
  }
  else {
    fifo_write_buf [ ll + 0 ] = ( num / 100 ) + '0';
    num = num % 100;
    fifo_write_buf [ ll + 1 ] = ( num / 10 ) + '0';
    fifo_write_buf [ ll + 2 ] = ( num % 10 ) + '0';
    fifo_write_buf [ ll + 3 ] = '\0';
  }
}

IsIdentifier ( str )
char * str;
{
  int slen = strlen ( str );
  int not_ident = 0;
  int i;

  if ( slen < 2 ) not_ident = 1;
  if ( ! ( str [ 0 ] >= 'a' && str [ 0 ] <= 'z' ) &&
       ! ( str [ 0 ] >= 'A' && str [ 0 ] <= 'Z' )    ) not_ident = 1;
  for ( i = 1 ; i < slen ; i++ ) {
    if ( ! ( str [ i ] >= 'a' && str [ i ] <= 'z' ) &&
         ! ( str [ i ] >= 'A' && str [ i ] <= 'Z' ) &&
         ! ( str [ i ] >= '0' && str [ i ] <= '9' ) &&
         ! ( str [ i ] == '_' )                        ) not_ident = 1;
  }
  return ( ! not_ident );
}

char *
DropFinalDir ( dir )
char * dir;
{
  int i, j, k;
  i = 0;
  j = 0;
  strcpy ( buf, dir );
  while ( buf [ i ] != '\0' ) {
    if ( buf [ i ] == '/' ) j++;
    i++;
  }
  if ( j > 1 ) {
    i = 0;
    k = 0;
    while ( buf [ i ] != '\0' ) {
      if ( buf [ i ] == '/' ) k++;
      if ( k == j ) buf [ i ] = '\0';
      i++;
    }
  }
  return buf;
}


int 
valid_filename_ext ( file )
char * file;
{

  /***
  called from SRC_watch ()
  we know strlen ( file ) > 5
  ***/

  char extbuf [ 5 ];
  int res = 0;
  int slen =  strlen ( file );
  int j;
  int i;

  if ( slen < 6 ) return ( 0 );

/***
printf ( "  valid_filename_ext checking %s\n", file );
***/
  if ( file [ slen - 4 ] == '.' ) {
    j = 0;
    for ( i = slen - 3 ; i < slen ; i++ ) { extbuf [ j++ ] = file [ i ]; }
    extbuf [ j ] = '\0';
    if ( ( strcmp ( extbuf, "mch" ) == 0 ) ||
         ( strcmp ( extbuf, "ref" ) == 0 ) ||
         ( strcmp ( extbuf, "imp" ) == 0 ) ||
         ( strcmp ( extbuf, "prf" ) == 0 ) ||
         ( strcmp ( extbuf, "bse" ) == 0 ) ||
         ( strcmp ( extbuf, "enm" ) == 0 ) ||
         ( strcmp ( extbuf, "itf" ) == 0 ) ||
         ( strcmp ( extbuf, "ops" ) == 0 ) ||
         ( strcmp ( extbuf, "map" ) == 0 ) ||
         ( strcmp ( extbuf, "doc" ) == 0 )    ) res = 1;
  }

  if ( ! res ) {  /* may be a.b.prf.n */
    if ( slen > 11 ) {
      i = slen - 1;
      while ( ( file [ i ] >= '0' ) && ( file [ i ] <= '9' ) ) { i--; }
      if ( ( i > 9 )                 &&
           ( file [ i     ] == '.' ) &&
           ( file [ i - 1 ] == 'f' ) &&
           ( file [ i - 2 ] == 'r' ) &&
           ( file [ i - 3 ] == 'p' ) &&
           ( file [ i - 4 ] == '.' )    ) {
        j = 0;
        extbuf [ j++ ] =  file [ i - 7 ];
        extbuf [ j++ ] =  file [ i - 6 ];
        extbuf [ j++ ] =  file [ i - 5 ];
        extbuf [ j ] = '\0';
        if ( ( strcmp ( extbuf, "mch" ) == 0 ) ||
             ( strcmp ( extbuf, "ref" ) == 0 ) ||
             ( strcmp ( extbuf, "imp" ) == 0 )    ) res = 1;
      }
    }
  }

  return ( res );
}

void
SRC_watch ()
{

  /***
  any file in SRC which has a valid extension and has been modified
  since the last SRC_watch ( > last_time ) is checked for being configured;
  if so, a check is made to see id the SRC file is newer than the CFG file;
  if so a call is made to `SRC_file_newer_from_name' if either lengths are different,
  or the lengths are the same and the content is different;
  if last_time_flag is set, the last_time is first reset to 0;
  if time (NULL) - last_time < 10 return (SRC_watch will also be called
  asynchronously by `DisplayCurrentEnv_continue') provided total_edits = 0
  ***/

  struct stat SRC_stat_buf, CFG_stat_buf;
  struct dirent * dirent_ptr;
  DIR * dp;
  int i, obj;
  static time_t last_time = ( time_t ) 0;
  void Decorate_SRC_file_newer ();
  void UnDecorate_SRC_file_newer ();
  void CheckForUserClosedEdits ();
  int  IsPrfObj ();
  int  IsMapObj ();
  int IsOpen ();

/***
printf ( "   ---------------- SRC_watch %d -----------------------\n", last_time );
***/

  if ( ( time ( NULL ) - last_time < 2 ) &&
       ( ! total_edits )                     ) {
/***
printf ( "  >>> >>> >>> NO SRC_watch <<< <<< <<< accessed < 2 secs ago & no edits\n" );
***/
    return;
  }

  last_time = time ( NULL );

  switch ( curr_env ) {
  case anm_env:
  case ipr_pob_env:
  case ipr_lem_env:
  case btl_env:
/***
printf ( "  >>> >>> >>> NO SRC_watch <<< <<< <<< inappropriate environment %d\n", curr_env );
***/
    return;
    break;
  }

  sprintf ( buf, "%s/SRC", cur_dir );

  if ( ( dp = opendir ( buf ) ) == NULL ) {
     sprintf ( fifo_write_buf, " Problem with \"opendir %s\" ", buf );
     Popup_Err ( 0, fifo_write_buf );
     return;
  }

  while ( ( dirent_ptr = readdir ( dp ) ) != NULL ) {
    if ( IsConfigured ( dirent_ptr -> d_name ) ) {
      GetObjFromFullName ( &obj, dirent_ptr -> d_name );
/***
printf ( "   configured: %s\n",  dirent_ptr -> d_name );
***/
      sprintf ( buf, "%s/SRC/%s", cur_dir, dirent_ptr -> d_name );
      if ( stat ( buf, &SRC_stat_buf ) != -1 ) {
        if ( IsPrfObj ( obj ) ) {
          sprintf ( buf, "%s/POB/%s", cur_dir, dirent_ptr -> d_name );
        }
        else {
          if ( IsMapObj ( obj ) ) 
            sprintf ( buf, "%s/CDE/PASP/%s", cur_dir, dirent_ptr -> d_name );
          else
            sprintf ( buf, "%s/CFG/%s", cur_dir, dirent_ptr -> d_name );
        }
        if ( stat ( buf, &CFG_stat_buf ) != -1 ) {
          if ( SRC_stat_buf . st_size != CFG_stat_buf . st_size ) {
/***
printf ( "     SRC/CFG length unequal -> Decorate_SRC_file_newer\n" );
***/
            Decorate_SRC_file_newer ( obj );
          }
          else {
/***
printf ( "     SRC/CFG length equal - " );
***/
            sprintf ( str_buf, "%s/SRC/%s", cur_dir, dirent_ptr -> d_name );
            if ( ( FileDifference ( buf, str_buf ) ) ) {
/***
printf ( "file diff -> Decorate_SRC_file_newer\n" );
***/
              Decorate_SRC_file_newer ( obj );
	    }
            else {
/***
printf ( "no file diff -> UnDecorate_SRC_file_newer\n" );
***/
              UnDecorate_SRC_file_newer ( obj );
              if ( ! ( IsOpen ( obj ) ) )  {
/***
printf ( "  %s not open for edit ... unlinking\n", str_buf );
***/
                unlink ( str_buf );
	      }
	    }
	  }
	}
      }
    }
  } /* while ... */
  closedir ( dp );
  CheckForUserClosedEdits ();
}

int
VHDLULIBIsADirectory ( int flag )
{
  struct stat stat_buf;
  int i, j;

  Retrieve_String ( vhdl_ulib_str_num, fifo_write_buf );
  i = 0;
  while ( ( fifo_write_buf [ i ] == ' ' ) || ( fifo_write_buf [ i ] == '\t' ) ) { i++; }
  j = 0;
  while ( fifo_write_buf [ i ] != '\0' ) {
    buf [ j++ ] = fifo_write_buf [ i++ ];
  }
  buf [ j ]= '\0';

  i = 0;
  while ( ( buf [ i ] == ' ' ) || ( buf [ i ] == '\t' ) ) { i++; }
  if ( flag && ( buf [ i ] == '\0' ) ) {
    Popup_Err ( 0, "VHDL ULIB Directory is not set - check TopBar Options" );
    return ( 0 );
  }

  if ( strcmp ( buf, "" ) == 0 ) {
    Popup_Err ( 0, "Teamlib directory not set - check TopBar Options" );
    return ( 0 );
  }

  if ( flag && ( stat ( buf, &stat_buf ) == -1 ) ) {
    sprintf ( fifo_write_buf, "VHDL ULIB Directory: `%s' does not exist - check TopBar Options", buf );
    Popup_Err ( 0, fifo_write_buf );
    return ( 0 );
  }

  if ( flag && ( S_ISDIR ( stat_buf . st_mode ) == 0 ) ) {
    sprintf ( fifo_write_buf, "VHDL ULIB Directory: `%s' is not a directory - check TopBar Options", buf );
    Popup_Err ( 0, fifo_write_buf );
    return ( 0 );
  }

  return ( 1 );
}

void
LoadWritableDirInto_sel_strs ( dir )
char * dir;
{
  struct stat stat_buf;
  struct dirent * dirent_ptr;
  DIR * dp;
  int i;
  int full = 0;
  void Sort_sel_strs_from_third ();

  if ( ( dp = opendir ( dir ) ) == NULL ) {
     sprintf ( fifo_write_buf, " Problem with \"opendir %s\" ", dir );
     Popup_Err ( 0, fifo_write_buf );
     return;
  }

  sprintf ( fifo_write_buf, "Current %s", /* DropFinalDir ( cur_dir ) */ dir );
  strcpy ( sel_str_arr [ 0 ], fifo_write_buf );

  sprintf ( fifo_write_buf, "Up to %s", DropFinalDir ( dir ) );
  strcpy ( sel_str_arr [ 1 ], fifo_write_buf );

  sel_arr_tot = 2;

  while ( ( ! full ) && ( ( dirent_ptr = readdir ( dp ) ) != NULL ) ) {

    sprintf ( buf, "%s/%s", dir, dirent_ptr -> d_name );
    if ( strcmp ( dirent_ptr -> d_name, "." ) == 0 ) {
      continue;
    }

    else if ( strcmp ( dirent_ptr -> d_name, ".." ) == 0 ) {
      continue;
   }

    else {
      if ( stat ( buf, &stat_buf ) == -1 ) {
         sprintf ( fifo_write_buf, " Problem with \"stat %s\" ", buf );
         Popup_Err ( 0, fifo_write_buf );
         return;
      }
      if ( S_ISDIR ( stat_buf . st_mode ) != 0 ) {
        full = ( ( sel_arr_tot < sel_arr_MAX - 1 ) == 0 );
        if ( ! full )
          strcpy ( sel_str_arr [ sel_arr_tot++ ], dirent_ptr -> d_name );
      }
    }

  } /* while ... */

  closedir ( dp );

  strcpy ( sel_str_arr [ sel_arr_MAX ], dir );

  Sort_sel_strs_from_third ();

  i = strlen ( sel_str_arr [ sel_arr_MAX ] );
  if (  sel_str_arr [ sel_arr_MAX ] [ i - 1 ] == '/' )
    sel_str_arr [ sel_arr_MAX ] [ i - 1 ] = '\0';

  if ( full ) {
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    sprintf ( buf, "Maximum number of selections exceeded (%d)", sel_arr_MAX - 1 );
    Popup_Err ( 0, buf );
  }
}

void
LoadSRCEditedNewInto_sel_strs ( edited_flag )
int edited_flag;        /* 1 => edited, 0 => New */
{
  struct dirent * dirent_ptr;
  DIR * dp;
  int i, ll, cc;
  int full = 0;
  void Sort_sel_strs ();

  if ( ( dp = opendir ( "SRC" ) ) == NULL ) {
     sprintf ( fifo_write_buf, " Problem with \"opendir %s\" ", "SRC" );
     Popup_Err ( 0, fifo_write_buf );
     return;
  }

  sel_arr_tot = 0;

  while ( ( ! full ) && ( ( dirent_ptr = readdir ( dp ) ) != NULL ) ) {

/***
printf ( "LoadSRCEditedNewInto_sel_strs: dirent_ptr -> d_name |%s|\n", dirent_ptr -> d_name );
***/
    ll = strlen ( dirent_ptr -> d_name );
    if ( ll > 4 ) {
      if ( ( valid_filename_ext ( dirent_ptr -> d_name ) ) ) {
        GetObjFromFullName ( &cc, dirent_ptr -> d_name );
/***
printf ( "cc=%d\n", cc ); fflush ( stdout );
***/
        if ( edited_flag ) {
          if ( cc ) {
            int IsPrfObj ();
            int IsMapObj ();
            sprintf ( primary_string, "SRC/%s", dirent_ptr -> d_name );
            if ( IsPrfObj ( cc ) ) {
              sprintf ( secondary_string, "POB/%s", dirent_ptr -> d_name );
	    }
            else {
              if ( IsMapObj ( cc ) ) 
                sprintf ( secondary_string, "CDE/PASP/%s", dirent_ptr -> d_name );
              else
                sprintf ( secondary_string, "CFG/%s", dirent_ptr -> d_name );
	    }
/***
printf ( "primary_string %s\n", primary_string );
printf ( "secondary_string %s\n", secondary_string );
***/
            if ( FileDifference ( primary_string, secondary_string ) ) {
              full = ( ( sel_arr_tot < sel_arr_MAX - 1 ) == 0 );
              if ( ! full )
                sel_obj_arr [ sel_arr_tot ] = cc;
                strcpy ( sel_str_arr [ sel_arr_tot ], dirent_ptr -> d_name );
                sel_arr_tot++;
/***
printf ( "yup\n" );
***/
	    }
	  }
        }
        else {
          if ( ! cc ) {
            full = ( ( sel_arr_tot < sel_arr_MAX - 1 ) == 0 );
            if ( ! full )
              sel_obj_arr [ sel_arr_tot ] = cc;
              strcpy ( sel_str_arr [ sel_arr_tot ], dirent_ptr -> d_name );
              sel_arr_tot++;
/***
printf ( "yup\n" );
***/
	  }
        }
      }
    }
  }

/***
printf ( ":::::::::::::::::::::::\n" );
for ( i = 0 ; i < sel_arr_tot ; i++ ) {
  printf ( "sel_str_arr [ %d ] %s\n", i, sel_str_arr [ i ] );
}
printf ( ":::::::::::::::::::::::\n" );
***/

  closedir ( dp );

  Sort_sel_strs ();

/***
printf ( ":::::::::::::::::::::::\n" );
for ( i = 0 ; i < sel_arr_tot ; i++ ) {
  printf ( "sel_str_arr [ %d ] %s\n", i, sel_str_arr [ i ] );
}
printf ( ":::::::::::::::::::::::\n" );
***/


  if ( full ) {
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    sprintf ( buf, "Maximum number of selections exceeded (%d)", sel_arr_MAX - 1 );
    Popup_Err ( 0, buf );
  }
}

void
LoadAnimatorFilesInto_sel_strs ( prompt, str )
char * prompt;
char * str;
{
  struct dirent * dirent_ptr;
  DIR * dp;
  int ll;

  strcpy ( sel_str_arr [ 0 ], prompt );
  sel_arr_tot = 1;

  if ( ( dp = opendir ( "SRC" ) ) == NULL ) {
     sprintf ( fifo_write_buf, " Problem with \"opendir %s\" ", "SRC" );
     Popup_Err ( 0, fifo_write_buf );
     return;
  }

  while ( ( dirent_ptr = readdir ( dp ) ) != NULL ) {
/***
printf ( "dirent_ptr -> d_name |%s|\n", dirent_ptr -> d_name );
***/
    ll = strlen ( dirent_ptr -> d_name );
    if ( ( ll > 5 ) && ( ( dirent_ptr -> d_name ) [ ll - 4 ] == '.' ) ) {
      buf [ 0 ] = ( dirent_ptr -> d_name ) [ ll - 3 ];
      buf [ 1 ] = ( dirent_ptr -> d_name ) [ ll - 2 ];
      buf [ 2 ] = ( dirent_ptr -> d_name ) [ ll - 1 ];
      buf [ 3 ] = '\0';
/***
printf ( "  buf |%s|\n", buf );
***/
      if   ( strcmp ( buf, str ) == 0 ) {
        strcpy ( str_buf, dirent_ptr -> d_name );
/***
printf ( "    str_buf |%s|\n", str_buf );
***/
        ll = strlen ( GetShortName ( curr_obj ) );
        if ( ( int ) strlen ( str_buf ) > ll + 3 ) {
          str_buf [ ll ] = '\0';
/***
printf ( "      str_buf |%s|\n", str_buf );
***/
	}
        if ( strcmp ( str_buf, GetShortName ( curr_obj ) ) == 0 ) {
/***
printf ( "        yup\n" );
***/
          if ( sel_arr_tot < sel_arr_MAX - 1 ) {
            strcpy ( sel_str_arr [ sel_arr_tot++ ], dirent_ptr -> d_name );
	  }
	}
      }
    }
  }

  closedir ( dp );

  Sort_sel_strs_from_second ();

}

void
LoadAnimatorFilesToCleanInto_sel_strs ()
{
  struct dirent * dirent_ptr;
  DIR * dp;
  int ll;
  void Sort_sel_strs ();

  sel_arr_tot = 0;

  if ( ( dp = opendir ( "SRC" ) ) == NULL ) {
     sprintf ( fifo_write_buf, " Problem with \"opendir %s\" ", "SRC" );
     Popup_Err ( 0, fifo_write_buf );
     return;
  }

  while ( ( dirent_ptr = readdir ( dp ) ) != NULL ) {
/***
printf ( "dirent_ptr -> d_name |%s|\n", dirent_ptr -> d_name );
***/
    ll = strlen ( dirent_ptr -> d_name );
    if ( ( ll > 5 ) && ( ( dirent_ptr -> d_name ) [ ll - 4 ] == '.' ) ) {
      buf [ 0 ] = ( dirent_ptr -> d_name ) [ ll - 3 ];
      buf [ 1 ] = ( dirent_ptr -> d_name ) [ ll - 2 ];
      buf [ 2 ] = ( dirent_ptr -> d_name ) [ ll - 1 ];
      buf [ 3 ] = '\0';
/***
printf ( "  buf |%s|\n", buf );
***/
      if ( ( strcmp ( buf, "out" ) == 0 ) ||
           ( strcmp ( buf, "anm" ) == 0 )    ) {
        strcpy ( str_buf, dirent_ptr -> d_name );
/***
printf ( "    str_buf |%s|\n", str_buf );
***/
        ll = strlen ( GetShortName ( curr_obj ) );
        if ( ( int ) strlen ( str_buf ) > ll + 3 ) {
          str_buf [ ll ] = '\0';
/***
printf ( "      str_buf |%s|\n", str_buf );
***/
	}
        if ( strcmp ( str_buf, GetShortName ( curr_obj ) ) == 0 ) {
/***
printf ( "        yup\n" );
***/
          if ( sel_arr_tot < sel_arr_MAX - 1 ) {
            strcpy ( sel_str_arr [ sel_arr_tot++ ], dirent_ptr -> d_name );
	  }
	}
      }
    }
  }

  closedir ( dp );

  Sort_sel_strs ();

}

void
LoadAllAnmThyFilesInto_sel_strs ()
{
  struct stat stat_buf;
  struct dirent * dirent_ptr;
  DIR * dp;
  int ll;
  void Sort_sel_strs ();

  sel_arr_tot = 0;
  sprintf ( buf, "%s/SRC", cur_dir );
  if ( ( dp = opendir ( buf ) ) == NULL ) {
     sprintf ( fifo_write_buf, " Problem with \"opendir %s\" ", buf );
     Popup_Err ( 0, fifo_write_buf );
     return;
  }

  while ( ( ( dirent_ptr = readdir ( dp ) ) != NULL ) &&
          ( sel_arr_tot < sel_arr_MAX )       ) {
    ll = strlen ( dirent_ptr -> d_name );
    if ( ll > 8 ) {
      if ( ( ( dirent_ptr -> d_name ) [ ll - 4 ] == '.' ) &&
           ( ( dirent_ptr -> d_name ) [ ll - 3 ] == 't' ) &&
           ( ( dirent_ptr -> d_name ) [ ll - 2 ] == 'h' ) &&
           ( ( dirent_ptr -> d_name ) [ ll - 1 ] == 'y' )    ) {
        strcpy ( buf, dirent_ptr -> d_name );
        buf [ ll - 4 ] = '\0';
        if ( IsConfigured ( buf ) ) {
          strcpy ( sel_str_arr [ sel_arr_tot++ ], dirent_ptr -> d_name );
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




/*
void
Load_Mch_arr_TEMP ()
{
  int l, c, i, j, e, o, nm [ 50 ] ;
  i = 1;
  first_Construct ( &l, &c );
  while ( l != 0 && i <= MAX_NUM_CONSTRUCTS ) {
    xtr_name ( nm, c );
    strcpy ( Mch_arr [ i ] . name, ( char * ) nm );
    val_ext ( &e, c );
    Mch_arr [ i ] . obj = c;
    Mch_arr [ i ] . ext = e;
    Mch_arr [ i ] . ps =  0;
    next_Construct ( &l, &c, l, c );
    i++;
  }
  Mch_arr_tot = i-1;
  Sort_Mch_arr ();
}

void
LoadCreTLIBableInto_sel_strs ()
{
  int i, j, not_present, tot_tlib, cc;
  int tt, st, anl, ac, cc1, bb;
  FILE * Bcfg;
  char buf [ 250 ];

  sel_arr_tot = 0;

  Retrieve_String ( teamlib_str_num, buf );
  if ( strcmp ( buf, "" ) == 0 ) {
    Popup_Err ( 0, "Teamlib directory not set - check TopBar Options" );
    return;
  }

  Save_CfgDepBase ();
  strcpy ( primary_string, "cp " );
  strcat ( primary_string, buf );
  strcat ( primary_string, "/.Bpda CfgDepBase.dump" );
  execute ( primary_string );
  restore_CfgDepBase ( &bb );
  if ( ! bb ) {
    Popup_Err ( 0, "  BMotif: read CfgDepBase.dump error " );
    DisplayCurrWinText ( "\n  BMotif: read CfgDepBase.dump error\n" );
    return;    
  }
  Load_Mch_arr_TEMP ();
  tot_tlib = Mch_arr_tot;
  for ( i = 1 ; i <= tot_tlib; i++ ) {
    strcpy ( rmk_str_arr [ i ], Mch_arr [ i ] . name );
  }
  if ( tot_tlib == 0 ) {
    DisplayCurrWinText ( "\n  No constructs currently configured in " );
    DisplayCurrWinText ( buf ) ;
    DisplayCurrWinText ( "\n" );
  }
  else {
    DisplayCurrWinText ( "\n  Constructs currently configured in " );
    DisplayCurrWinText ( buf ) ;
    DisplayCurrWinText ( "\n" );
    for ( i = 1 ; i <= tot_tlib ; i++ ) {
      strcpy ( buf, "    " );
      strcat ( buf, rmk_str_arr [ i ] );
      strcat ( buf, "\n" );
      DisplayCurrWinText ( buf );
    }
    DisplayCurrWinText ( "\n" );
  }
  Restore_CfgDepBase ();

  for ( i = 1 ; i <= Mch_arr_tot ; i++ ) {
    if ( Mch_arr [ i ] . ext == mch ) {
      val_type ( &tt, Mch_arr [ i ] . obj );
      if ( tt != lib ) {
        val_curMRIState ( &st, Mch_arr [ i ] . obj );
        val_anl ( &anl, st );
        if ( anl ) {
          cc1 = HasImp ( Mch_arr [ i ] . obj );
          if ( cc1 ) {
            val_curMRIState ( &st, cc1 );
            val_trl ( &bb, st );
            if ( bb ) {
              not_present = 1;
              for ( j = 1 ; j <= tot_tlib ; j++ ) {
                if ( not_present ) {
                  not_present =
                   ( strcmp ( rmk_str_arr [ j ], Mch_arr [ i ] . name ) != 0 );
		}
	      }
              if ( not_present ) {
                strcpy ( sel_str_arr [ sel_arr_tot ], Mch_arr [ i ] . name );
                strcat ( sel_str_arr [ sel_arr_tot ], ".mch" );
                sel_Mch_arr [ sel_arr_tot ] = Mch_arr [ i ] . obj;
                sel_arr_tot++;
	      }
	    }
	  }
	}
      }
    }
  }
}

void
LoadTLIBIntroducableInto_sel_strs ()
{
  int bb, i, j, not_present, tot_tlib;

  sel_arr_tot = 0;

  Retrieve_String ( teamlib_str_num, buf );
  if ( strcmp ( buf, "" ) == 0 ) {
    Popup_Err ( 0, "Teamlib directory not set - check TopBar Options" );
    return;
  }

  Save_CfgDepBase ();

  strcpy ( primary_string, "cp " );
  strcat ( primary_string, buf );
  strcat ( primary_string, "/.Bpda CfgDepBase.dump" );
  execute ( primary_string );
  restore_CfgDepBase ( &bb );
  if ( ! bb ) {
    Popup_Err ( 0, "  BMotif: read CfgDepBase.dump error " );
    DisplayCurrWinText ( "\n  BMotif: read CfgDepBase.dump error\n" );
    return;    
  }
  Load_Mch_arr_TEMP ();

  tot_tlib = Mch_arr_tot;
  for ( i = 1 ; i <= tot_tlib; i++ ) {
    strcpy ( rmk_str_arr [ i ], Mch_arr [ i ] . name );
  }
  if ( tot_tlib == 0 ) {
    DisplayCurrWinText ( "\n  No constructs currently configured in " );
    DisplayCurrWinText ( buf ) ;
    DisplayCurrWinText ( "\n" );
    Restore_CfgDepBase ();
    return;
  }
  else {
    DisplayCurrWinText ( "\n  Constructs currently configured in " );
    DisplayCurrWinText ( buf ) ;
    DisplayCurrWinText ( "\n" );
    for ( i = 1 ; i <= tot_tlib ; i++ ) {
      strcpy ( buf, "    " );
      strcat ( buf, rmk_str_arr [ i ] );
      strcat ( buf, "\n" );
      DisplayCurrWinText ( buf );
    }
    DisplayCurrWinText ( "\n" );
  }

  Restore_CfgDepBase ();

  for ( j = 1 ; j <= tot_tlib ; j++ ) {
    not_present = 1;
    for ( i = 1 ; i <= Mch_arr_tot ; i++ ) {
      if ( not_present ) {
        not_present =
                   ( strcmp ( rmk_str_arr [ j ], Mch_arr [ i ] . name ) != 0 );
      }
    }
    if ( not_present && sel_arr_tot < sel_arr_MAX ) {
      strcpy ( sel_str_arr [ sel_arr_tot ], rmk_str_arr [ j ] );
      strcat ( sel_str_arr [ sel_arr_tot ], ".mch" );
      sel_arr_tot++;
    }
  }
  if ( sel_arr_tot >= sel_arr_MAX ) {
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    strcpy ( buf, "Maximum number of selections exceeded (" );
    CreNumInBuf ( buf, sel_arr_MAX );
    strcat ( buf, ")" );
    Popup_Err ( 0, buf );
  }
  Restore_CfgDepBase ();
}
*/




void
LoadLIBInto_sel_strs ( dir )
char * dir;
{
  FILE * Bcom;
  int i, c;
  sprintf ( fifo_write_buf, "curdir=`pwd` ; cd %s ; ls *.mch 2> /dev/null  > $curdir/TMP/.Bcom", dir );
  system ( fifo_write_buf );
  Bcom = fopen ( "TMP/.Bcom", "r" );
  if ( Bcom == NULL ) {
    printf( "\n  BMotif: can't open TMP/.Bcom for reading\n" );
    BT_err_exit ( 0 );
    return;
  }
  sel_arr_tot = 0;
  i = 0;
  c = getc ( Bcom );
  while ( c != EOF && sel_arr_tot < sel_arr_MAX ) {
    while ( sel_arr_tot < sel_arr_MAX &&
            i < 35 && c != '\n' && c != EOF         ) {
      sel_str_arr [ sel_arr_tot ] [ i ] = c;
      c = getc ( Bcom );
      i++;
    }
    if ( i != 35 && sel_arr_tot < sel_arr_MAX ) {
      sel_str_arr [ sel_arr_tot ] [ i ] = '\0';
      if ( c != EOF ) {
        sel_arr_tot++;
        i = 0;
        c = getc ( Bcom );
      }
    }
    else if ( sel_arr_tot < sel_arr_MAX ) {
      while ( c != '\n' && c != EOF ) {
         c = getc ( Bcom );
       }
       if ( c != EOF ) {
        i = 0;
        c = getc ( Bcom );
      }
    }
  }
  if ( sel_arr_tot >= sel_arr_MAX ) {
    char buf [ 100 ];
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    strcpy ( buf, "Maximum number of selections exceeded (" );
    CreNumInBuf ( buf, sel_arr_MAX );
    strcat ( buf, ")" );
    Popup_Err ( 0, buf );
  }
  fclose ( Bcom );
}

void
LoadVHDLSLIBInto_sel_strs ()
{
  FILE * Bcom;
  int i, c;
  sprintf ( fifo_write_buf, "curdir=`pwd` ; cd %s/BLIB/LIB_VHDL/CFG ; ls *.mch 2> /dev/null  > $curdir/TMP/.Bcom", BKIT_path );
  system ( fifo_write_buf );
  Bcom = fopen ( "TMP/.Bcom", "r" );
  if ( Bcom == NULL ) {
    printf( "\n  BMotif: can't open TMP/.Bcom for reading\n" );
    BT_err_exit ( 0 );
    return;
  }
  sel_arr_tot = 0;
  i = 0;
  c = getc ( Bcom );
  while ( c != EOF && sel_arr_tot < sel_arr_MAX ) {
    while ( sel_arr_tot < sel_arr_MAX &&
            i < 35 && c != '\n' && c != EOF         ) {
      sel_str_arr [ sel_arr_tot ] [ i ] = c;
      c = getc ( Bcom );
      i++;
    }
    if ( i != 35 && sel_arr_tot < sel_arr_MAX ) {
      sel_str_arr [ sel_arr_tot ] [ i ] = '\0';
      if ( c != EOF ) {
        sel_arr_tot++;
        i = 0;
        c = getc ( Bcom );
      }
    }
    else if ( sel_arr_tot < sel_arr_MAX ) {
      while ( c != '\n' && c != EOF ) {
         c = getc ( Bcom );
       }
       if ( c != EOF ) {
        i = 0;
        c = getc ( Bcom );
      }
    }
  }
  if ( sel_arr_tot >= sel_arr_MAX ) {
    char buf [ 100 ];
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    strcpy ( buf, "Maximum number of selections exceeded (" );
    CreNumInBuf ( buf, sel_arr_MAX );
    strcat ( buf, ")" );
    Popup_Err ( 0, buf );
  }
  fclose ( Bcom );
}


void
BT_crash_err_exit ( n )
int n;
{
    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );
    AbortedMsgCode ( 11000 + n );
    Save_n_CfgDepBase ();
    if ( ! up_and_running ) {
      Kill_bplatform_and_exit ( 1, 0 );
    }
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
    InvokeB ( without_XTerm, 1 );
}

void
BT_err_exit ( n )
int n;
{
    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );
    if ( ( n != 0 ) && ( n != 999999 ) ) {
      AbortedMsgCode ( n );
    }
    if ( n!=999999 ) {
      Save_n_CfgDepBase ();
    }
    /*
    if ( ! up_and_running ) {
      Kill_bplatform_and_exit ( 1, 0 );
    }
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
    InvokeB ( without_XTerm, 1 );
    */
    Kill_bplatform_and_exit ( 1, 0 );        /* DON'T CHANGE */
}

void
BT_base_err_exit ( n )
int n;
{
    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );
    AbortedBaseMsgCode ( n );
    Kill_bplatform_and_exit ( 1, 0 );        /* DON'T CHANGE */
}

void
BT_system_exit ( buf )
char * buf;
{
    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );
    if ( ! up_and_running ) {
      Kill_bplatform_and_exit ( 1, 0 );
    }
    printf ( "\n\n  Can't execute \"%s\"\n\n", buf );
    Save_n_CfgDepBase ();
    if ( ! up_and_running ) {
      Kill_bplatform_and_exit ( 1, 0 );
    }
    strcpy ( fifo_write_buf, "0:" );
    Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
    InvokeB ( without_XTerm, 1 );
}

void
file_error ( file, mode )
char * file;
char * mode;
{
  printf ( "\n  BMotif: can't open %s for %s\n\n", file, mode );
  Kill_bplatform_and_exit ( 1, 0 );
}


#ifdef WWW_VERSION

void
format_error ( file, err, cc )
char * file;
char * err;
char cc;
{
/***
  printf ( "\n  Format error in %s: %s\n\n    char: %c\n\n    int: %d\n\n", file, err, cc, ( int ) cc );
***/
  printf ( "\n\n                  B-Toolkit Terminated" );
  if ( strlen ( err ) == 1 ) {
    printf ( "\n\n                    Exit code: 1410%s", err);
  }
  else {
    printf ( "\n\n                    Exit code: 141%s", err);
  }
  printf ( "\n\n             All data has been preserved\n\n\n" );
  Kill_bplatform_and_exit ( 1, 0 );
}

#endif /* WWW_VERSION */

/*
"header_string n1 n2 n3 n4 X X X X X 0 0 1 n5 n6 n7 n8 0 0 1 0 1 ......."
where length X X X X X = n1+(7*n2)+(49*n3)+(343*n4)+15
      length Y Y Y Y Y = n5+(7*n6)+(49*n7)+(343*n8)+23
*/

void
Save_CfgDepBase_sub ()
{
  FILE * CfgDepBase;
  FILE * Bpda;
  FILE * Bpda_0;
  int bb, j, c;

  /***
  copy .Bpda .Bpda_0
  ***/
  execute ( "cp .Bpda .Bpda_0" );

  /***
  open .Bpda for writing & initialise
  ***/
  Bpda = fopen ( ".Bpda", "w" );
  if ( Bpda == NULL ) {
    AbortedMsgFile ( "\".Bpda\" for writing" );
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

#ifdef WWW_VERSION

  /***
  write WWW strip
  ***/
  for ( j = 0 ; j < strip_arr_tot ; j++ ) {
    putc ( strip_arr [ j ], Bpda );    
  }

#endif /* WWW_VERSION */

  /***
  open CfgDepBase.dump for reading
  ***/
  CfgDepBase = fopen ( "CfgDepBase.dump", "r" );
  if ( CfgDepBase == NULL ) {
    AbortedMsgFile ( "\"CfgDepBase.dump\" for reading" );
    Kill_bplatform_and_exit ( 1, 0 );
  }

  /***
  append CfgDepBase.dump to .Bpda
  ***/
  c = getc ( CfgDepBase );
  while ( c != EOF ) {
    putc ( c, Bpda );
    c = getc ( CfgDepBase );
  }

  /***
  close  CfgDepBase.dump & .Bpda
  ***/
  fclose ( CfgDepBase );
  fclose ( Bpda );

  /***
  remove CfgDep
  ***/
  unlink ( "CfgDepBase.dump" );
}

void
Save_CfgDepBase ()
{
  static int saving;
  int bb;

  if ( ( ! CfgDepBase_is_Restored ) && ( ! started_from_cd ) ) {
/***
printf ( "Save_CfgDepBase but ! CfgDepBase_is_Restored\n" );
***/
    return;
  }

  /***
  call Base save
  ***/
  save_CfgDepBase ( &bb );
  if ( ! bb ) {
    Popup_Err ( 0, "  BMotif: write CfgDepBase.dump error " );
    DisplayCurrWinText ( "\n  BMotif: write CfgDepBase.dump error\n" );
    return;    
  }

  if ( saving ) {
    Popup_Err ( 0, "Attempt to save whilst already saving!" );  
  }

  saving = 1;

  Save_CfgDepBase_sub ();

  saving = 0;
}

void
ProcessUpgrade ()
{
  FILE * Bcom;
  FILE * Bpda;
  FILE * CfgDepBase;
  int bb, j, c;

  printf ( "\n\n  Not a %s development.\n", toolkit_short_ver );

  sprintf ( primary_string, "%s/BLIB/Upgrade3To4 %s %d", BKIT_path, cur_dir, 5 );
  system ( primary_string );

  Bcom = fopen ( "TMP/.Bcom", "r" );
  if ( Bcom == NULL ) {
    AbortedMsgFile ( "\"TMP/.Bcom\" for reading" );
    BT_err_exit ( 0 );
    return;
  }
  c = getc ( Bcom );
  fclose ( Bcom );
  if   ( c == 0 ) {
    Kill_bplatform_and_exit ( 1, 0 );
  }
  else if ( c == 1 ) {
    upgrade3T04_flag = upgrade3T04_reset;
  }
  else {
    upgrade3T04_flag = upgrade3T04_reset_remake;
  }

/***
system ( "echo '----------------'" );
system ( "ls -alrt *.dump .B*" );
system ( "echo '----------------'" );
***/

  restore_CfgDepBase ( &bb );
  if ( ! bb ) {
    Popup_Err ( 0, "  BMotif: read CfgDepBase.dump error " );
    DisplayCurrWinText ( "\n  BMotif: read CfgDepBase.dump error\n" );
    Kill_bplatform_and_exit ( 1, 0 );
  }

/***
Info_40_Upgrade ( 0 );
***/

/***
system ( "ls -alrt *.dump .B*" );
system ( "echo '----------------'" );
***/

  auto_reset_and_remake = 1;

/***
Info_40_Upgrade ( 1 );
***/

  InitialiseFlagsAndStrings ();

  Save_CfgDepBase_sub ();

/***
Info_40_Upgrade ( 2 );
***/

}

void
Restore_CfgDepBase ()
{
  FILE * CfgDepBase;
  FILE * Bpda;
  int i, j, t, c, bb;

  /***
  if .Bpda can't be opened copy .Bpda_0 to .Bpda
  ***/
  Bpda = fopen ( ".Bpda", "r" );
  if ( Bpda != NULL ) {
    fclose ( Bpda );
  }
  else {
    printf( "\n  BMotif: can't open .Bpda for reading - trying .Bpda_0 - " );
    Bpda = fopen ( ".Bpda_0", "r" );
    if ( Bpda != NULL ) {
      fclose ( Bpda );
      execute ( "cp .Bpda_0 .Bpda" );
      printf ( "ok\n" );
    }
    else {
      printf( "failed\n\n  BMotif: can't open .Bpda/.Bpda_0 for reading\n" );
      BT_err_exit ( 999999 );
      return;
    }
  }

  /***
  open .Bpda for reading
  ***/
  Bpda = fopen ( ".Bpda", "r" );
  if ( Bpda == NULL ) {
    printf( "\n\n  BMotif: can't open .Bpda for reading\n" );
    BT_err_exit ( 999999 );
    return;
  }

  /***
  check header string from .Bpda
  ***/
  c = getc ( Bpda );
  i = 0;
  while ( i < ( int ) strlen ( cur_hdr_string ) && c != EOF ) {
    buf [ i ] = ( char ) c;
    i++;
    if ( i < ( int ) strlen ( cur_hdr_string ) ) c = getc ( Bpda );
  }
  buf [ i ] = '\0';

  if ( strcmp ( buf, cur_hdr_string ) == 0 ) {
    /***
    read platform identifier
    ***/
    c = getc ( Bpda );   /* platform_ident */

/***
printf ( "%d %s   %d %s\n", c, platform_types [ c ], platform_ident, platform_types [ platform_ident ] );
***/

    if ( c != platform_ident ) {
      if ( ( c != platform_ident_SunOS   ||
             platform_ident != platform_ident_Solaris ) &&
           ( c != platform_ident_Solaris ||
             platform_ident != platform_ident_SunOS )       ) {
        printf ( "\n        Platform-independent data file does not exist\n" );
        printf ( "\n      This development should be re-run on a %s platform\n\n\n", platform_types [ c ] );
        Kill_bplatform_and_exit ( 1, 0 );
      }
    }
  }
  else /* if ( strcmp ( buf, old_hdr_string ) != 0 ) */ {
/***
    printf ( "\n  No cur_hdr_string match |%s| |%s| %d\n", buf, cur_hdr_string, strlen ( cur_hdr_string ) );
***/

    ProcessUpgrade ();
    return;

  }

#ifdef WWW_VERSION

  /***
  get WWW strip
  ***/
  t = 0;
  j = 0;
  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  t = t + ( int ) c; 
  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  t = t + ( 7 * ( int ) c ); 
  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  t = t + ( 49 * ( int ) c ); 
  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  t = t + ( 343 * ( int ) c ); 
  t = t + 15;

  i = 0;
  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  while ( i < ( int ) t && c != EOF ) {
    c = getc ( Bpda );
    strip_arr [ j++ ] = c;
    i++;
  }

  if ( c == EOF ) {
    format_error ( ".Bpda", "1", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( ".Bpda", "2", c );
  }

  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  if ( c == EOF ) {
    format_error ( ".Bpda", "3", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( ".Bpda", "4", c );
  }

  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  if ( c == EOF ) {
    format_error ( ".Bpda", "5", ' ' );
  }
  else if ( c != 1 ) {
    format_error ( ".Bpda", "6", c );
  }

  t = 0;
  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  t = t + ( int ) c; 
  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  t = t + ( 7 * ( int ) c ); 
  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  t = t + ( 49 * ( int ) c ); 
  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  t = t + ( 343 * ( int ) c ); 
  t = t + 23;

  i = 0;
  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  while ( i < ( int ) t && c != EOF ) {
    c = getc ( Bpda );
    strip_arr [ j++ ] = c;
    i++;
  }

  if ( c == EOF ) {
    format_error ( ".Bpda", "7", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( ".Bpda", "8", c );
  }

  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  if ( c == EOF ) {
    format_error ( ".Bpda", "9", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( ".Bpda", "10", c );
  }

  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  if ( c == EOF ) {
    format_error ( ".Bpda", "11", ' ' );
  }
  else if ( c != 1 ) {
    format_error ( ".Bpda", "12", c );
  }

  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  if ( c == EOF ) {
    format_error ( ".Bpda", "13", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( ".Bpda", "14", c );
  }

  c = getc ( Bpda );
  strip_arr [ j++ ] = c;
  strip_arr_tot = j;
  if ( c == EOF ) {
    format_error ( ".Bpda", "15", ' ' );
  }
  else if ( c != 1 ) {
    format_error ( ".Bpda", "16", c );
  }

#endif /* WWW_VERSION */

  /***
  open CfgDepBase.dump for writing
  ***/
  CfgDepBase = fopen ( "CfgDepBase.dump", "w" );
  if ( CfgDepBase == NULL ) {
    printf( "failed\n\n  BMotif: can't open CfgDepBase.dump for writing\n" );
    BT_err_exit ( 999999 );
    return;
  }

  /***
  copy remainder of .Bpda to CfgDepBase.dump
  ***/
  c = getc ( Bpda );
  while ( c != EOF ) {
    putc ( c, CfgDepBase );
    c = getc ( Bpda );
  }

  fclose ( Bpda );
  fclose ( CfgDepBase );
  
  /***
  call Base restore
  ***/
  restore_CfgDepBase ( &bb );
  if ( ! bb ) {
    printf( "\n  BMotif: read CfgDepBase.dump error\n" );
    BT_err_exit ( 999999 );
    return;
  }

  /***
  remove CfgDep
  ***/
  unlink ( "CfgDepBase.dump" );

  CfgDepBase_is_Restored = 1;
}


void
Save_n_CfgDepBase ()
{
  FILE * CfgDepBase;
  FILE * Bpda;
  FILE * Bpda_0;
  FILE * Bpdan;
  int bb, j, c;
  static int saving;

  if ( saving ) {
    Popup_Err ( 0, "Attempt to save whilst already saving!" );  
  }

  saving = 1;

  /***
  call Base save_n
  ***/
  save_n_CfgDepBase ( &bb );
  if ( ! bb ) {
    Popup_Err ( 0, "  BMotif: write CfgDepBase.dump error " );
    DisplayCurrWinText ( "\n  BMotif: write CfgDepBase.dump error\n" );
    return;    
  }

  /***
  copy .Bpda .Bpda_0
  ***/
  execute ( "cp .Bpda .Bpda_0" );

  /***
  open .Bpdan for writing & initialise
  ***/
  Bpdan = fopen ( ".Bpdan", "w" );
  if ( Bpdan == NULL ) {
    AbortedMsgFile ( "\".Bpdan\" for writing" );
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

#ifdef WWW_VERSION

  /***
  write WWW strip
  ***/
  for ( j = 0 ; j < strip_arr_tot ; j++ ) {
    c = htonl ( strip_arr [ j ] );
    putc ( c, Bpdan );    
  }

#endif /* WWW_VERSION */

  /***
  open CfgDepBase.dump for reading
  ***/
  CfgDepBase = fopen ( "CfgDepBase.dump", "r" );
  if ( CfgDepBase == NULL ) {
    AbortedMsgFile ( "\"CfgDepBase.dump\" for reading" );
    Kill_bplatform_and_exit ( 1, 0 );
  }

  /***
  append CfgDepBase.dump to .Bpdan
  ***/
  c = getc ( CfgDepBase );
  while ( c != EOF ) {
    putc ( c, Bpdan );
    c = getc ( CfgDepBase );
  }

  /***
  close  CfgDepBase.dump & .Bpda
  ***/
  fclose ( CfgDepBase );
  fclose ( Bpdan );

  /***
  remove CfgDep
  ***/
  unlink ( "CfgDepBase.dump" );

  saving = 0;
}

void
/*
"header_string n1 n2 n3 n4 X X X X X 0 0 1 n5 n6 n7 n8 0 0 1 0 1 ......."
where length X X X X X = n1+(7*n2)+(49*n3)+(343*n4)+15
      length Y Y Y Y Y = n5+(7*n6)+(49*n7)+(343*n8)+23
*/

Restore_n_CfgDepBase ()
{
  FILE * CfgDepBase;
  FILE * Bpdan;
  int i, j, t, c, bb;

  /***
  open .Bpdan for reading
  ***/
  Bpdan = fopen ( ".Bpdan", "r" );
  if ( Bpdan == NULL ) {
    printf( "\n\n  BMotif: can't open .Bpdan for reading\n" );
    BT_err_exit ( 999999 );
    return;
  }

  /***
  check header string from .Bpdan
  ***/
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
  read platform identifier
  ***/
  fread( &c, sizeof ( int ), 1, Bpdan ); /* platform_ident  */
  c = ntohl ( c );          /* no need to check here */

/***
printf ( "c %d %s   platform_ident %d %s\n", c, platform_types [ c ], platform_ident, platform_types [ platform_ident ] );
***/

  if ( strcmp ( buf, cur_hdr_string ) != 0 ) {

/***
    printf ( "\n  No cur_hdr_string match |%s| |%s| %d\n", buf, cur_hdr_string, strlen ( cur_hdr_string ) );
***/

    ProcessUpgrade ();
    return;

  }

#ifdef WWW_VERSION

  /***
  get WWW strip
  ***/
  t = 0;
  j = 0;
  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  t = t + ( int ) c; 
  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  t = t + ( 7 * ( int ) c ); 
  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  t = t + ( 49 * ( int ) c ); 
  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  t = t + ( 343 * ( int ) c ); 
  t = t + 15;

  i = 0;
  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  while ( i < ( int ) t && c != EOF ) {
    c = getc ( Bpdan );
    c = ntohl ( c );
    strip_arr [ j++ ] = c;
    i++;
  }

  if ( c == EOF ) {
    format_error ( ".Bpdan", "1", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( ".Bpdan", "2", c );
  }

  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  if ( c == EOF ) {
    format_error ( ".Bpdan", "3", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( ".Bpdan", "4", c );
  }

  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  if ( c == EOF ) {
    format_error ( ".Bpdan", "5", ' ' );
  }
  else if ( c != 1 ) {
    format_error ( ".Bpdan", "6", c );
  }

  t = 0;
  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  t = t + ( int ) c; 
  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  t = t + ( 7 * ( int ) c ); 
  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  t = t + ( 49 * ( int ) c ); 
  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  t = t + ( 343 * ( int ) c ); 
  t = t + 23;

  i = 0;
  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  while ( i < ( int ) t && c != EOF ) {
    c = getc ( Bpdan );
    c = ntohl ( c );
    strip_arr [ j++ ] = c;
    i++;
  }

  if ( c == EOF ) {
    format_error ( ".Bpdan", "7", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( ".Bpdan", "8", c );
  }

  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  if ( c == EOF ) {
    format_error ( ".Bpdan", "9", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( ".Bpdan", "10", c );
  }

  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  if ( c == EOF ) {
    format_error ( ".Bpdan", "11", ' ' );
  }
  else if ( c != 1 ) {
    format_error ( ".Bpdan", "12", c );
  }

  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  if ( c == EOF ) {
    format_error ( ".Bpdan", "13", ' ' );
  }
  else if ( c != 0 ) {
    format_error ( ".Bpdan", "14", c );
  }

  c = getc ( Bpdan );
  c = ntohl ( c );
  strip_arr [ j++ ] = c;
  strip_arr_tot = j;
  if ( c == EOF ) {
    format_error ( ".Bpdan", "15", ' ' );
  }
  else if ( c != 1 ) {
    format_error ( ".Bpdan", "16", c );
  }

#endif /* WWW_VERSION */

  /***
  open CfgDepBase.dump for writing
  ***/
  CfgDepBase = fopen ( "CfgDepBase.dump", "w" );
  if ( CfgDepBase == NULL ) {
    printf( "failed\n\n  BMotif: can't open CfgDepBase.dump for writing\n" );
    BT_err_exit ( 999999 );
    return;
  }

  /***
  copy remainder of .Bpdan to CfgDepBase.dump
  ***/
  c = getc ( Bpdan );
  while ( c != EOF ) {
    putc ( c, CfgDepBase );
    c = getc ( Bpdan );
  }

  fclose ( Bpdan );
  fclose ( CfgDepBase );
  
  /***
  call Base restore
  ***/
  restore_n_CfgDepBase ( &bb );
  if ( ! bb ) {
    printf( "\n  BMotif: read CfgDepBase.dump error\n" );
    BT_err_exit ( 999999 );
    return;
  }

  /***
  remove .Bpdan & CfgDep
  ***/
  unlink ( ".Bpdan" );
  unlink ( "CfgDepBase.dump" );

  CfgDepBase_is_Restored = 1;
}

void
GetExtNumFromString ( ext, name )
int * ext;
char * name;
{
  int i = 0;
  int j = 0;
  char ext_str [ 10 ];

  while ( name [ i ] != '.' ) {
    i++;
  }
  i++;
  while ( name [ i ] != '\0' ) {
    ext_str [ j ] = name [ i ];
    i++;
    j++;
  }
  ext_str [ j ] = '\0';
  i = 0;
  * ext = 0;
  while ( ! ( * ext ) ) {
    i++;
    if ( strcmp ( extens [ i ], ext_str ) == 0 ) {
      * ext = i;
    }
  }
}


void
GetNameFromString ( name, str )
char * name;
char * str;
{
  int i = 0;

  while ( str [ i ] != '.' && str [ i ] != '\0' ) {
    name [ i ] = str [ i ];
    i++;
  }
  name [ i ] = '\0';
}


void
CreNumInBuf ( buf_, n )
char * buf_;
int n;
{
  if ( n < 0 ) {
    n = n * (-1);
    strcat ( buf_, "-" );
  }
  if ( n > 9 ) {
    CreNumInBuf ( buf_, n/10 );
    strcat ( buf_, num_strings [ n % 10 ] );
  }
  else {
    strcat ( buf_, num_strings [ n ] );
  }
}


void
PrintNum ( file, n )
FILE * file;
int n;
{
  if ( n > 9 ) {
    PrintNum ( file, n/10 );
    fprintf ( file, num_strings [ n % 10 ] );
  }
  else {
    fprintf ( file, num_strings [ n ] );
  }
}


void
CreNumFromBuf ( n, buf )
int * n;
char * buf;
{
  int i;

  * n = 0;
  i = 0;
  while ( buf [ i ] != '\0' ) {
    * n = ( ( ( * n ) * 10 ) + buf [ i ] - '0' );
    i++;
  }
}


void
DeCommentFile ( filenamein, filenameout, no_annot )
char * filenamein;
char * filenameout;
int * no_annot;
{
  FILE * filein;
  FILE * fileout;

  int c, in_comment;

  filein = fopen ( filenamein, "r" );
  if ( filein == NULL ) {
    printf("\n  BMotif: can't open %s for reading\n", filenamein );
    BT_err_exit ( 0 );
    return;
  }
  fileout = fopen ( filenameout, "w" );
  if ( fileout == NULL ) {
    fclose ( filein );
    printf("\n  BMotif: can't open %s for writing\n",filenameout );
    BT_err_exit ( 0 );
    return;
  }

  * no_annot = 1;
  c = getc ( filein );
  while ( c != EOF ) {
    if ( c == ' ' || c == '\t' || c == '\n' ) {
      while ( c == ' ' || c == '\t' || c == '\n' ) {
        c = getc ( filein );
      }
    }
    if ( c == '/' ) {
      c = getc ( filein );
      if ( c == '*' ) {
        in_comment = 1;
        * no_annot = 0;
        c = getc ( filein );
        while ( in_comment && c != EOF ) {
          if ( c == '*' ) {
            c = getc ( filein );
            if ( c == '/' ) {
              in_comment = 0;
              c = getc ( filein );
              while ( c == ' ' || c == '\t' || c == '\n' ) {
                c = getc ( filein );
              }
            }
            else if ( c == '*' ) {
              ungetc( c, filein );
              c = getc ( filein );
            }
            else {
              if ( c != EOF ) {
                c = getc ( filein );
              }
            }
          }
          else {
            if ( c != EOF ) {
              c = getc ( filein );
            }
          }
        }
      }
      else {
        putc ( '/', fileout );
        if ( c != '/' && c != EOF ) {
          putc ( c, fileout );
          c = getc ( filein );
        }
      }
    }
    else {
      if ( c != EOF ) {
        putc ( c, fileout );
        c = getc ( filein );
      }
    }
  }

  fclose ( filein );
  fclose ( fileout );
}


void
PrintAnnotOnly ( filenamein, filenameout )
char * filenamein;
char * filenameout;
{
  FILE * filein;
  FILE * fileout;

  int c, in_annot = 0;

  filein = fopen ( filenamein, "r" );
  if ( filein == NULL ) {
    printf("\n  BMotif: can't open %s for reading\n", filenamein );
    BT_err_exit ( 0 );
    return;
  }
  fileout = fopen ( filenameout, "w" );
  if ( fileout == NULL ) {
    fclose ( filein );
    printf("\n  BMotif: can't open %s for writing\n",filenameout );
    BT_err_exit ( 0 );
    return;
  }

  c = getc ( filein );

  while ( c != EOF ) {

    while ( ( c != '/' ) && ( c != '"' ) && ( c != EOF ) ) {
      if ( in_annot ) putc ( c, fileout );
      c = getc ( filein );
    }

    if ( ! in_annot ) {

      if ( c == '/' ) {
        c = getc ( filein );
        if ( c == '*' ) {
          c = getc ( filein );
          if ( c == '"' ) {
            in_annot = 1;
	  }
        }
      }
    }

    else { /* in_annot */

      if ( c == '"' ) {
        c = getc ( filein );
        if ( c == '*' ) {
          c = getc ( filein );
          if ( c == '/' ) {
            in_annot = 0;
	  }
          else {
            putc ( '"', fileout );
            putc ( '*', fileout );
            putc ( c, fileout );
	  }
	}
        else {
          putc ( '"', fileout );
          putc ( c, fileout );
	}
      }
      else {
        putc ( c, fileout );
      }
    }

    if ( c != EOF ) c = getc ( filein );

  }

  fclose ( filein );
  fclose ( fileout );
}


void
PrintCommentOnly ( filenamein, filenameout )
char * filenamein;
char * filenameout;
{
  FILE * filein;
  FILE * fileout;

  int c, in_comment = 0;

  filein = fopen ( filenamein, "r" );
  if ( filein == NULL ) {
    printf("\n  BMotif: can't open %s for reading\n", filenamein );
    BT_err_exit ( 0 );
    return;
  }
  fileout = fopen ( filenameout, "w" );
  if ( fileout == NULL ) {
    fclose ( filein );
    printf("\n  BMotif: can't open %s for writing\n",filenameout );
    BT_err_exit ( 0 );
    return;
  }

  c = getc ( filein );

  while ( c != EOF ) {

    while ( ( c != '/' ) && ( c != '*' ) && ( c != EOF ) ) {
      if ( in_comment ) putc ( c, fileout );
      c = getc ( filein );
    }

    if ( ! in_comment ) {

      if ( c == '/' ) {
        c = getc ( filein );
        if ( c == '*' ) {
          c = getc ( filein );
          if ( c != '"' ) {
            in_comment = 1;
	  }
        }
      }
    }

    else { /* in_comment */

      if ( c == '*' ) {
        c = getc ( filein );
        if ( c == '/' ) {
          in_comment = 0;
	}
        else {
          putc ( '*', fileout );
          putc ( c, fileout );
	}
      }
      else {
        putc ( c, fileout );
      }
    }

    if ( c != EOF ) c = getc ( filein );

  }

  fclose ( filein );
  fclose ( fileout );
}

int
FileDifference ( filename1, filename2 )
char * filename1;
char * filename2;
{
  FILE * file1;
  FILE * file2;
  int c,d;

  file1 = fopen ( filename1, "r" );
  if ( file1 == NULL ) {
    printf("\n  BMotif: can't open %s for reading\n", filename1 );
    BT_err_exit ( 0 );
    return ( 1 );
  }
  file2 = fopen ( filename2, "r" );
  if ( file2 == NULL ) {
    fclose ( file1 );
    printf("\n  BMotif: can't open %s for reading\n",filename2 );
    BT_err_exit ( 0 );
    return ( 1 );
  }

  c = getc ( file1 );
  d = getc ( file2 );
  while ( ( c == d ) && ( c != EOF ) && ( d != EOF ) ) {
    c = getc ( file1 );
    d = getc ( file2 );
  }
  fclose ( file1 );
  fclose ( file2 );
  return ( c != d );
}

int
SRC_CFG_FilesDiffer ( obj )
int obj;
{
  Load_SRC_CFG_Names ( obj );
  return ( FileDifference ( SRCName, CFGName ) );
}

void
ShowFileDiff ( obj )
int obj;
{
  /***
  primary string contains full name
  (it will be the top label of the dialog)
  ***/

  FILE * Berr;
  char s [ 10000 ];
  char dir [ 50 ];
  struct stat statBerr;
  struct help_struct help_data;
  char *text;
  int ext;

  val_ext ( &ext, obj );

  /***
  set directory
  ***/
  if ( ext ==  mch_prf || ext == ref_prf || ext == imp_prf ) {
    strcpy ( dir, "POB/" );
  }
  else {
    strcpy ( dir, "CFG/" );
  }
 
  /***
  put diff data into .Berr
  ***/
  Berr = fopen ( ".Berr", "w" );
  if ( Berr == NULL ) {
    perror( " .Berr" );
    return;
  }
  fputs ( "< SRC/", Berr );
  fputs ( primary_string, Berr );
  fputs ( "\n---\n> ", Berr );
  fputs ( dir , Berr );
  fputs ( primary_string, Berr );
  fputs ( "\n\n", Berr );
  fclose ( Berr );
  strcpy ( s, "diff SRC/" );
  strcat ( s, primary_string );
  strcat ( s, " " );
  strcat ( s, dir );
  strcat ( s, primary_string );
  strcat ( s, ">>.Berr" );
  system ( s );

  /***
  load diff data from .Berr
  ***/
  if ( stat ( ".Berr", &statBerr ) != 0 ) {
    perror( " stat: .Berr" );
    return;
  }
  Berr = fopen ( ".Berr", "r" );
  if ( Berr == NULL ) {
    perror( " .Berr" );
    return;
  }
  if ( ! ( text = XtMalloc ( ( unsigned ) statBerr.st_size + 1 ) ) ) {
    DisplayCurrWinText ( "\n Can't allocate enough space for .Berr\n" );
    return;
  }
  if ( ! fread ( text, sizeof ( char ), statBerr.st_size + 1, Berr ) ) {
    sprintf ( buf, "\n May not have read the entire file %s\n", ".Berr" );
    DisplayCurrWinText ( buf );
  }
  text [ statBerr.st_size ] = 0;
  fclose ( Berr );
    
  /***
  set help data and call Popup_Help_CB 
  ***/
  help_data.type = DIFF_HELP;
  help_data.text = ( char * ) text;
  help_data.width  = 500;
  help_data.height = 250;

  Popup_Help_CB ( top_level, &help_data );

  /***
  free allocated memory
  ***/
  XtFree ( text );
}

void
MainWinDisp_type(tt)
int     tt;
{
        if ( tt == lib ) {
                DisplayCurrWinText ( "LIBRARY " );
        }
        if ( tt == lib_vhdl ) {
                DisplayCurrWinText ( "VHDL LIBRARY " );
        }
        else if ( tt == usr_vhdl ) {
                DisplayCurrWinText ( "VHDL " );
        }
        else if ( tt == gen_vhdl ) {
                DisplayCurrWinText ( "VHDL GENERATED PACKAGE " );
        }
        else if ( tt != usr && tt != usr_vhdl && tt != gen_vhdl ) {
                DisplayCurrWinText ( "GENERATED " );
        }
}


void
MainWinDisp_mri(ex)
int     ex;
{
        if ( ex == mch ) {
                DisplayCurrWinText ( "MACHINE " );
        } else if ( ex == ref ) {
                DisplayCurrWinText ( "REFINEMENT " );
        } else {
                DisplayCurrWinText ( "IMPLEMENTATION " );
        }
}


void
MainWinDisp_spec_ref_imp_by(ex)
int     ex;
{
        if ( ex == mch ) {
                DisplayCurrWinText ( "SPECIFICATION " );
        } else if ( ex == ref ) {
                DisplayCurrWinText ( "REFINED by " );
        } else {
                DisplayCurrWinText ( "IMPLEMENTED by " );
        }
}


void
MainWinDisp_nat ( nn )
int nn;
{
  char buf [ 50 ];

  strcpy ( buf, "" );
  CreNumInBuf ( buf, nn );
  DisplayCurrWinText ( buf );
}


void
MainWinDispCode_gset ( n )
int n;
{
  int nm [ 50 ];
  char buf [ 100 ];
  int nn, st, ext, type, cc, cc1, bb;
/***
sprintf ( str_buf, "MainWinDispCode_gset ( %d )\n", n );
DisplayCurrWinText ( str_buf );
***/
  switch ( n ) {
  case 1:
    card_gset1( &nn );
    break;
  case 2:
    card_gset2( &nn );
    break;
  case 3:
    card_gset3( &nn );
    break;
  case 4:
    card_gset4( &nn );
    break;
  case 5:
    card_gset5( &nn );
    break;
  }
  while ( nn ) {
    switch ( n ) {
    case 1:
      valOrd_gset1 ( &cc, nn );
      break;
    case 2:
      valOrd_gset2 ( &cc, nn );
      break;
    case 3:
      valOrd_gset3 ( &cc, nn );
      break;
    case 4:
      valOrd_gset4 ( &cc, nn );
      break;
    case 5:
      valOrd_gset5 ( &cc, nn );
      break;
    }
    strcpy ( buf, "      " );
    get_topabs ( &cc1, cc );
    xtr_name ( nm, cc1 );
    strcat ( buf, ( char * ) nm );
    val_ext ( &ext, cc );
    if ( ext == imp ) {
      strcat ( buf, ".o (object code)\n" );
    }
    else {  /* ext = itf mch??? */
      strcat ( buf, " (executable code)\n" );
    }

    DisplayCurrWinText ( buf );
    if ( ext == imp ) {

      /*
      val_type ( &type, cc );
      if ( type == itf_gen ) {
        val_gen_by ( &cc, cc );
        val_curMRIState( &st, cc );
        val_lnk( &bb, st );
        if ( bb ) {
          strcpy ( buf, "      " );
          strcat ( buf, ( char * ) nm );
          strcat ( buf, " (executable code)\n" );
          DisplayCurrWinText ( buf );
        }
      }
      */

      val_curMRIState( &st, cc );
      val_lnk( &bb, st );
      if ( bb ) {
        strcpy ( buf, "      " );
        strcat ( buf, ( char * ) nm );
        strcat ( buf, " (executable code)\n" );
        DisplayCurrWinText ( buf );
      }
    }
    nn--;
  }
}

void
MainWinDisp_gset ( n )
int n;
{
  char buf [ 50 ];
  int nn, cc;

  switch ( n ) {
  case 1:
    card_gset1( &nn );
    break;
  case 2:
    card_gset2( &nn );
    break;
  case 3:
    card_gset3( &nn );
    break;
  case 4:
    card_gset4( &nn );
    break;
  case 5:
    card_gset5( &nn );
    break;
  }
  while ( nn ) {
    switch ( n ) {
    case 1:
      valOrd_gset1 ( &cc, nn );
      break;
    case 2:
      valOrd_gset2 ( &cc, nn );
      break;
    case 3:
      valOrd_gset3 ( &cc, nn );
      break;
    case 4:
      valOrd_gset4 ( &cc, nn );
      break;
    case 5:
      valOrd_gset5 ( &cc, nn );
      break;
    }
    DisplayCurrWinText ( "      " );
    DisplayCurrWinText ( GetName ( cc ) );
    DisplayCurrWinText ( "\n" );
    nn = nn-1;
  }
}


void
Cat_gset_tcp ( n )
int n;
{
  int nn, cc;

  strcat ( fifo_write_buf, "?" );
  switch ( n ) {
  case 1:
    card_gset1 ( &nn );
    break;
  case 2:
    card_gset2 ( &nn );
    break;
  case 3:
    card_gset3 ( &nn );
    break;
  case 4:
    card_gset4 ( &nn );
    break;
  case 5:
    card_gset5 ( &nn );
    break;
  }
  while ( nn ) {
    switch ( n ) {
    case 1:
      valOrd_gset1 ( &cc, nn );
      break;
    case 2:
      valOrd_gset2 ( &cc, nn );
      break;
    case 3:
      valOrd_gset3 ( &cc, nn );
      break;
    case 4:
      valOrd_gset4 ( &cc, nn );
      break;
    case 5:
      valOrd_gset5 ( &cc, nn );
      break;
    }
    strcat ( fifo_write_buf, "," );
    strcat ( fifo_write_buf, GetName ( cc ) );
    nn = nn-1;
  }
  if ( nn ) {
    BT_err_exit ( 5 );    
    return;
  }
}


void
MainWinDisp_status ( cc )
int	cc;
{
	int	ex, rr, ll, cc1, tt, bb, cc2, stt, nn, mm, st, suc, ac;

	DisplayCurrWinText ( "\n  Status information:\n\n" );
	val_ext(&ex, cc);
	if ( ex == doc ) {
		{ ; }
	}  else {
		val_curMRIState(&st, cc);
		val_anl(&bb, st);
		if ( bb == FALSE ) {
			val_type(&tt, cc);
			val_ext(&ex, cc);
			DisplayCurrWinText ( "  " );
			MainWinDisp_type(tt);
			MainWinDisp_mri(ex);
			DisplayCurrWinText ( GetShortName ( cc ) );
			DisplayCurrWinText ( " is not analysed\n" );
		} else {
			val_abs2conc(&ac, cc);
		        nn = 1;
		        bb = FALSE;
			while ( bb == FALSE ) {
			        valIth_a2c(&cc1, ac, nn);
			        val_ext(&ex, cc1);
			        val_type(&tt, cc1);
			        if ( ex == mch ) {
				        DisplayCurrWinText ( "  " );
				        MainWinDisp_type(tt);
				        MainWinDisp_spec_ref_imp_by(ex);
			        } else {
				        DisplayCurrWinText ( "  " );
				        MainWinDisp_spec_ref_imp_by(ex);
				        MainWinDisp_type(tt);
			        }
			        DisplayCurrWinText ( GetShortName ( cc1 ) );
			        DisplayCurrWinText ( "\n\n" );
			        nn = nn + 1;
			        if ( cc == cc1 ) {
				        bb = TRUE;
			        }
			}
			val_type(&tt, cc);
			if ( ( tt == usr ) || ( tt == usr_vhdl ) ) {
				DisplayCurrWinText ( "    " );
				val_curMRIState(&st, cc);
				length_pob(&nn, st);
				if ( nn == 0 ) {
					DisplayCurrWinText ( "Proof obligations not generated\n" );
				} else {
					DisplayCurrWinText ( "Proof obligations:\n" );
					valIth_pob(&mm,
					     st, 1);
                                        mm = correct_pob_for_btl ( mm );
					DisplayCurrWinText ( "      Level 0  (" );
					MainWinDisp_nat(mm);
                                        if ( mm == 1 ) {
					  DisplayCurrWinText ( " proof obligation)\n" );
					}
                                        else {
					  DisplayCurrWinText ( " proof obligations)\n" );
					}
					ll = 1;
					while ( ll < nn ) {
/* code folded from here */
	valIth_pob(&mm,
	     st, ll + 1);
        mm = correct_pob_for_btl ( mm );
	DisplayCurrWinText ( "      Level " );
	MainWinDisp_nat(ll);
	DisplayCurrWinText ( "  (" );
	if ( mm == 0 ) {
		DisplayCurrWinText ( "all discharged)\n" );
	} else {
		MainWinDisp_nat(mm);
		DisplayCurrWinText ( " undischarged)\n" );
	}
	ll = ll + 1;
/* unfolding */
					}
				}
				DisplayCurrWinText ( "\n" );
			}
			val_dmu(&bb, st);
			if ( bb == FALSE ) {
				DisplayCurrWinText ( "    Not Marked Up" );
			} else {
				DisplayCurrWinText ( "    Marked Up" );
			}
			val_ext(&ex, cc);
			if ( ex == imp ) {
				DisplayCurrWinText ( "\n    " );
				val_trl(&bb, st);
				if ( bb == TRUE ) {
					val_lnk(&bb, st);
					if ( bb == TRUE ) {
/* code folded from here */
	DisplayCurrWinText ( "Translated and Linked" );
/* unfolding */
					} else {
/* code folded from here */
	DisplayCurrWinText ( "Translated" );
/* unfolding */
					}
				} else {
					DisplayCurrWinText ( "Not Translated" );
				}
			}
			DisplayCurrWinText ( "\n\n    " );
			clear_gset1();
			clear_gset2();
			clear_gset3();
                        modIth_flags ( get_dep_cstr_num, cc );
			add_gset2(&rr, cc);
			length_a2c(&nn, ac);
			bb = FALSE;
			while ( bb == FALSE & rr == TRUE ) {
				valIth_a2c(&cc1, ac, nn);
				if ( cc != cc1 ) {
					add_gset2(&rr, cc1);
					nn = nn - 1;
				} else {
					bb = TRUE;
				}
			}
			card_gset2(&ll);
			while ( ll > 0 & rr == TRUE ) {
                                top_level_dep_cstr = cc;
				getnext_dep_cst(&rr);
				card_gset2(&ll);
			}
			card_gset3(&ll);
			while ( ll != 0 & rr == TRUE ) {
				valOrd_gset3(&cc1, ll);
				add_a2cdep(&rr, cc1);
				ll = ll - 1;
			}
			if ( rr == TRUE ) {
				del_gset1(cc);
				card_gset1(&ll);
				if ( ll == 0 ) {
					val_trl(&bb, st);
					if ( bb == TRUE ) {
/* code folded from here */
        if ( tt == lib || tt == enm_gen ) {
	  DisplayCurrWinText ( "Dependent constructs:\n" );
	  DisplayCurrWinText ( "      " );
          DisplayCurrWinText ( GetShortName ( cc ) );
	  DisplayCurrWinText ( ".o (object code)\n" );
          top_level_dep_cstr = cc;
          Get_Code_Dep ( cc );
/*
DisplayCurrWinText ( "*****\n" );
*/
          MainWinDispCode_gset ( 5 );
/*
DisplayCurrWinText ( "*****\n" );
*/
	}
        else {
          top_level_dep_cstr = cc;
          Get_Code_Dep ( cc );
          card_gset5 ( &nn );
          if ( nn ) {
	    DisplayCurrWinText ( "Dependent constructs:\n" );
/*
DisplayCurrWinText ( "@@@@@\n" );
*/
            MainWinDispCode_gset ( 5 );
/*
DisplayCurrWinText ( "@@@@@\n" );
*/
	  }
          else {
	    DisplayCurrWinText ( "No dependent constructs\n" );
	  }
	}
          
					} /*** if ( bb == TRUE ) ***/
                                        else {
/* code folded from here */
      int mm, nn;
      Get_Code_Dep ( cc );
      card_gset5 ( &mm );
      top_level_dep_cstr = cc;
      get_dep_cstr ( &rr, cc );
      chk_rep ( rr, 4 );
      card_gset1 ( &nn );
      if ( nn == 0 && mm == 0 ) {
	  DisplayCurrWinText ( "No dependent constructs\n" );
	}
      else {
        DisplayCurrWinText ( "\n\n    Dependent constructs:\n" );
        MainWinDisp_gset ( 1 );
        MainWinDispCode_gset ( 5 );
      }
					}
/* unfolding */
				      } /*** if ( ll == 0 ) (card_gset1) ***/
                                else {
					DisplayCurrWinText ( "Dependent constructs:\n" );
/*
DisplayCurrWinText ( "=====\n" );
*/
					MainWinDisp_gset ( 1 );
/*
DisplayCurrWinText ( "=====\n" );
*/
                                        if ( tt == lib || tt == enm_gen ) {
	                                  DisplayCurrWinText ( "      " );
                                          DisplayCurrWinText ( GetShortName ( cc ) );
	                                  DisplayCurrWinText ( ".o (object code)\n" );
					}
                                        top_level_dep_cstr = cc;
                                        Get_Code_Dep ( cc );
                                        MainWinDispCode_gset ( 5 );
/*
DisplayCurrWinText ( "=====\n" );
*/
				}
				DisplayCurrWinText ( "\n" );
				if ( tt != /* lib */ 99999 ) {
					get_sub_cstr(&rr,
					     cc);
					card_gset1(&ll);
					if ( ll == 0 ) {
/* code folded from here */
	DisplayCurrWinText ( "    " );
	DisplayCurrWinText ( "No subordinate constructs\n" );
/* unfolding */
					} else {
/* code folded from here */
	DisplayCurrWinText ( "    " );
	DisplayCurrWinText ( "Subordinate constructs:\n" );
	MainWinDisp_gset ( 1 );
/* unfolding */
					}
				}
				if ( tt != lib && tt != lib_vhdl && tt != enm_gen && tt != gen_vhdl ) {
					DisplayCurrWinText ( "\n" );
					if ( ex != imp ) {
/* code folded from here */
	nn = 1;
	suc = FALSE;
	while ( suc == FALSE ) {
		valIth_a2c(&cc1, ac, nn);
		nn = nn + 1;
		if ( cc == cc1 ) {
			suc = TRUE;
		}
	}
	length_a2c(&ll, ac);
	if ( ll < nn ) {
		if ( ex == mch ) {
			DisplayCurrWinText ( "    " );
			DisplayCurrWinText ( "No refinement\n" );
		} else {
			DisplayCurrWinText ( "    " );
			DisplayCurrWinText ( "No further refinement\n" );
		}
	} else {
		while ( nn <= ll ) {
			valIth_a2c(&cc1, ac, nn);
			nn = nn + 1;
			val_ext(&ex, cc1);
			val_type(&tt, cc1);
			DisplayCurrWinText ( "  " );
			MainWinDisp_spec_ref_imp_by(ex);
			MainWinDisp_type(tt);
			DisplayCurrWinText ( GetShortName ( cc1 ) );
			DisplayCurrWinText ( "\n" );
		}
	}
/* unfolding */
					}
				}
			}
		}
        }

/***
    DisplayStatusStructure ( cc );
***/

}

int
ProcessLibSeesIncludes ( str, name, ext_num )
char * str;
char * name;
int ext_num;
{
  char sub_str [ 50 ];
  int i = 0;
  int j, obj, rr;
/***
printf("ProcessLibSeesIncludes: %s %s %d\n",str,name,ext_num);
***/
  clear_gset1 ();
  j = 0;
  while ( str [ i ] != ';' ) {
    while ( str [ i ] != ',' && str [ i ] != ';' ) {
      sub_str [ j ] = str [ i ];
      i++;
      j++;
    }
    if ( str [ i ] != ';' ) {
      i++;
    }
    if ( sub_str [ j-1 ] != '?' ) {
      sub_str [ j ] = '\0';
      GetObjFromNameExt ( &obj, sub_str, mch );
/***
printf ( "Sees: GetObjFromNameExt: %d (%s, %d)\n", obj, sub_str, mch );
***/
      add_gset1( &rr, obj );
      chk_rep ( rr, 90 );
      j = 0;
    }
  }
  i++;
  clear_gset2 ();
  j = 0;
  while ( str [ i ] != ';' ) {
    while ( str [ i ] != ',' && str [ i ] != ';' ) {
      sub_str [ j ] = str [ i ];
      i++;
      j++;
    }
    if ( str [ i ] != ';' ) {
      i++;
    }
    if ( sub_str [ j-1 ] != '?' ) {
      sub_str [ j ] = '\0';
      GetObjFromNameExt ( &obj, sub_str, mch );
/***
printf ( "Includes: GetObjFromNameExt: %d (%s, %d)\n", j, sub_str, mch );
***/
      add_gset2( &rr, obj );
      chk_rep ( rr, 90 );
      j = 0;
    }    
  }
  card_gset1 ( &i );
  return ( i );
}

void
Load_Seen_gset1_Ipt_gset2 ( cc, cc0 )
int * cc, * cc0;
{
  int i = 1;
  char sub_str [ 50 ];
  int obj, rr;

/***
printf ( "---------------------------\nLoad_Seen_gset1_Ipt_gset2:%s\n", primary_string );
***/

  /***
  sets: cc to the imp
        cc0 to the spec
        gset1 contains the seen/used list
        gset2 contains the imported list
  ***/ 

  clear_gset1 ();
  clear_gset2 ();
  clear_gset3 ();
  clear_gset4 ();

  while ( primary_string [ i ] != ';' ) {
    j = 0;
    while ( primary_string [ i ] != ',' && primary_string [ i ] != ';' ) {
      if ( primary_string [ i ] != ' ' ) {
        sub_str [ j ] = primary_string [ i ];
        j++;
      }
      i++;
    }
    if ( primary_string [ i ] != ';' ) {
      i++;
    }
    if ( sub_str [ j-1 ] != '?' ) {
      sub_str [ j ] = '\0';
      GetObjFromNameExt ( &obj, sub_str, imp );
      * cc =  obj;    /* the imp being checked */
/***
printf("  the imp is %s\n", GetName ( obj ) );
***/
    }
  }
  i++;
  while ( primary_string [ i ] != ';' ) {
    j = 0;
    while ( primary_string [ i ] != ',' && primary_string [ i ] != ';' ) {
      if ( primary_string [ i ] != ' ' ) {
        sub_str [ j ] = primary_string [ i ];
        j++;
      }
      i++;
    }
    if ( primary_string [ i ] != ';' ) {
      i++;
    }
    if ( sub_str [ j-1 ] != '?' ) {
      sub_str [ j ] = '\0';
      GetObjFromNameExt ( &obj, sub_str, mch );
      * cc0 =  obj;    /* the top level mch */
/***
printf("  the mch is %s\n", GetName ( obj ) );
***/
    }
  }
  i++;
  while ( primary_string [ i ] != ';' ) {
    j = 0;
    while ( primary_string [ i ] != ',' && primary_string [ i ] != ';' ) {
      if ( primary_string [ i ] != ' ' ) {
        sub_str [ j ] = primary_string [ i ];
        j++;
      }
      i++;
    }
    if ( primary_string [ i ] != ';' ) {
      i++;
    }
    if ( sub_str [ j-1 ] != '?' ) {
      sub_str [ j ] = '\0';
      GetObjFromNameExt ( &obj, sub_str, mch );
      add_gset1 ( &rr, obj );
      chk_rep ( rr, 214 );
/***
printf("    added %s to gset1 (sees/uses)\n", GetName ( obj ) );
***/
    }
/***
else { printf("1st arg ?\n"); }
***/
  }
  i++;
  while ( primary_string [ i ] != ')' ) {
    j = 0;
    while ( primary_string [ i ] != ',' && primary_string [ i ] != ')' ) {
      if ( primary_string [ i ] != ' ' ) {
        sub_str [ j ] = primary_string [ i ];
        j++;
      }
      i++;
    }
    if ( primary_string [ i ] != ')' ) {
      i++;
    }
    if ( sub_str [ j-1 ] != '?' ) {
      sub_str [ j ] = '\0';
      GetObjFromNameExt ( &obj, sub_str, mch );
      add_gset2 ( &rr, obj );
      chk_rep ( rr, 207 );
/***
printf("        added %s.%s to gset2 (inc/ipt)\n", GetName ( obj ) );
***/
    }
/***
else { printf("2nd arg ?\n"); }
***/
  }
/***
printf ( "  cc=%s", GetName ( * cc ), GetName ( * cc0 ) );
printf ( " cc0=%s\n", GetName ( * cc0 ) );
printf ( "  the seen/used machines:\n" );
show_gset ( 1 );
printf ( "  the imported machines:\n" );
show_gset ( 2 );
printf ( "-----------------------\n" );
***/
}

void
IptDesignCheckOK ()
{
  int cc, cc0, cc1, cc2, cc3, loc_itr, cc_itr, ext;
  int ss, rr, mm, nn, bb;
  int design_ok = 1;

/***
printf ( "---------------------------------------------------------\nIptDesignCheckOK\n" );
***/

  Load_Seen_gset1_Ipt_gset2 ( &cc, &cc0 );

  /***
  stage 1: build expanded sees list set in gset3
           use gset4 as working imp set

  1. gset3 = gset1 (seen list for cc) ; gset4={cc}
     (note that this is ok since cc not analysed &
      its sees/imp lists won't be found in stage 2)
  2. loop while gset4/={}
       a. get 1st elem cc1 of gset4 & remove from gset4
       b. get sees list for cc1 and union into gset3
       c. get_topabs cc2 of cc1
       d. get set of all imps who either import or see cc2 and add to gset4
  ***/

/***
printf ( "-------------------\n" );
printf ( "  %s SEES\n", GetName ( cc ) );
show_gset ( 1 );
printf ( "  %s IMPORTS\n", GetName ( cc ) );
show_gset ( 2 );
printf ( "-------------------\n" );
***/


  clear_gset3 ();
  val_gset1 ( &ss );
  mod_gset3 ( &rr, ss );
  chk_rep ( rr, 218 );
  
  clear_gset4 ();
  add_gset4 ( &rr, cc );
  chk_rep ( rr, 221 );

  card_gset4 ( &nn );
  while ( nn ) {
/***
show_gset ( 3 );
show_gset ( 4 );
***/
    valOrd_gset4 ( &cc1, 1 );                             /* cc1 is imp */
    del_gset4 ( cc1 );
/***
printf ( "  processing %s\n", GetName ( cc1 ) );
***/
    def_sees_uses ( &bb, cc1 );
    if ( bb ) {
      val_sees_uses ( &ss, cc1 );
      union_gset3 ( &rr, ss );
      chk_rep ( rr, 219 );
    }
/***
show_gset ( 3 );
***/
    if   ( cc1 == cc ) cc2 = cc0;                    /* THE imp - use cc0 */
    else               get_topabs ( &cc2, cc1 );
/***
printf ( "    machine is %s\n", GetName ( cc2 ) );
***/
    first_Construct ( &loc_itr, &cc_itr );
    while ( loc_itr ) {
      val_ext ( &ext, cc_itr );
      if ( ext == imp ) {
        def_sees_uses ( &bb, cc_itr );
        if ( bb ) {
          member_sees_uses ( &bb, cc_itr, cc2 );
          if ( bb ) {
/***
printf ( "      seen by %s\n", GetName ( cc_itr ) );
***/
            add_gset4 ( &rr, cc_itr );
            chk_rep ( rr, 220 );
	  }
	}
        def_inc_ipt ( &bb, cc_itr );
        if ( bb ) {
          member_inc_ipt ( &bb, cc_itr, cc2 );
          if ( bb ) {
            add_gset4 ( &rr, cc_itr );
/***
printf ( "      imported by %s\n", GetName ( cc_itr ) );
***/
            chk_rep ( rr, 220 );
	  }
	} /* if ( bb ) */
      } /* if ( ext == imp ) */
      next_Construct ( &loc_itr, &cc_itr, loc_itr, cc_itr );
    }  /* while ( loc_itr ) */
    card_gset4 ( &nn );
  } /* while ( nn ) */

/***
printf ( "----\nstage 1 complete - expanded sees list for %s:\n", GetName ( cc ) );
show_gset ( 3 );
printf ( "----\n" );
***/

  /***
  stage 2: check for import of any menber of gset3
           use gset4 as working imp set

  1. gset4={cc}
  2. loop while gset4/={}
       a. get 1st elem cc1 of gset4 & remove from gset4
       b. get imports list for cc1 & check for membership
          of each (cc2) in gset3
            if found - ERROR, so break
       d. get_botref of cc2, cc3, if it exists and add to gset4
       e. get sees list for cc1 and for each (cc2) get_botref (cc3)
          if it exists and add to gset4
  ***/

  clear_gset4 ();
  add_gset4 ( &rr, cc );
  chk_rep ( rr, 227 );

  card_gset4 ( &nn );
  while ( nn ) {
    valOrd_gset4 ( &cc1, 1 );                             /* cc1 is imp */
    del_gset4 ( cc1 );
/***
printf ( "  processing %s\n", GetName ( cc1 ) );
show_gset ( 4 );
***/
    if ( cc == cc1 ) {            /* THE imp - use the import list from gset2 */
      card_gset2 ( &mm );
      while ( mm ) {
        valOrd_gset2 ( &cc2, mm );
/***
printf ( "    imports %s\n", GetName ( cc2 ) );
***/
        member_gset3 ( &bb, cc2 );
        if ( bb ) { design_ok = 0; break; }
        if ( HasImp ( cc2 ) ) {
          get_botref ( &cc3, cc2 );    
          add_gset4 ( &rr, cc3 );
          chk_rep ( rr, 222 );
	}
        mm--;
      } /* while ( mm ) */
    }
    else {
      def_inc_ipt ( &bb, cc1 );
      if ( bb ) {
        card_inc_ipt ( &mm, cc1 );
        while ( mm ) {
          valOrd_inc_ipt ( &cc2, cc1, mm );
/***
printf ( "    imports %s\n", GetName ( cc2 ) );
***/
          member_gset3 ( &bb, cc2 );
          if ( bb ) { design_ok = 0; break; }
          if ( HasImp ( cc2 ) ) {
            get_botref ( &cc3, cc2 );    
            add_gset4 ( &rr, cc3 );
            chk_rep ( rr, 226 );
	  }
          mm--;
        } /* while ( mm ) */
      }
    }
    if ( ! design_ok ) break;
    if ( cc == cc1 ) {            /* THE imp - use the sees list from gset1 */
      card_gset1 ( &mm );
      while ( mm ) {
        valOrd_gset1 ( &cc2, mm );
/***
printf ( "    sees %d %s\n", cc2, GetName ( cc2 ) );
***/
        if ( HasImp ( cc2 ) ) {
          get_botref ( &cc3, cc2 );    
          add_gset4 ( &rr, cc3 );
          chk_rep ( rr, 223 );
        }
        mm--;
      } /* while ( mm ) */
    }
    else {
      def_sees_uses ( &bb, cc1 );
      if ( bb ) {
        card_sees_uses ( &mm, cc1 );
        while ( mm ) {
          valOrd_sees_uses ( &cc2, cc1, mm );
/***
printf ( "    sees %s\n", GetName ( cc2 ) );
***/
          if ( HasImp ( cc2 ) ) {
            get_botref ( &cc3, cc2 );    
            add_gset4 ( &rr, cc3 );
            chk_rep ( rr, 225 );
          }
          mm--;
        } /* while ( mm ) */
      }
    }
    card_gset4 ( &nn );
  } /* while ( nn ) */

  if ( design_ok ) {
    sprintf ( fifo_write_buf, "(?,1):%d:0", BT_BSEL );
  }
  else {
    sprintf ( buf, "%s", GetName ( cc1 ) );      /* comma separator! */
    sprintf ( fifo_write_buf, "(?,(%s,%s)):%d:0", buf, GetName ( cc2 ), BT_BSEL );
  }
  InvokeB ( without_XTerm, 1 );
}

void
IptClosureOK ()
{
  int cc0, cc, cc1, cc3, j, rr, nn, bb, ss;
  int card2;
  int closure_ok = 1;

/***
printf ( "---------------------------------------------------------\nIptClosureOK()\n" );
***/

  Load_Seen_gset1_Ipt_gset2 ( & cc, & cc0 );

  /* change both gsets 1 & 2 to include both sees & ipts */
  val_gset1 ( &ss );
  union_gset2 ( &rr, ss );
  chk_rep ( rr, 215 );
  val_gset2 ( &ss );
  mod_gset1 ( &rr, ss );
  chk_rep ( rr, 216 );

/***
show_gset ( 1 );
show_gset ( 2 );
***/

  /***
  the ipt mch (cc) (of the imp being analysed) are in gset2
     1. add the abstraction (cc0) (of the imp being analysed) to gset3
     2. get 1st member of gset2 (cc)
     3. get imp (if any) (cc1) and get ipt list of each
     4, iterate through ipt list - each is cc3
     5. check cc3 is in gset3
          if so error
          if not add to gset3 and gset2
        continue iteration of imported lists
     6, iterate through sees list - each is cc3
     7. check cc3 is in gset3
          if so error
          if not add to gset3 and gset2
        continue iteration of seen lists
     8. if not error, delete cc from gset2
     9. if gset2 not empty, goto 2.

   THEN do the same, but also with SEES (not checking for duplicate imports)

  ***/

  clear_gset3 ();
  add_gset3 ( &rr, cc0 );
  chk_rep ( rr, 210 );
  card_gset2 ( &card2 );
/***
printf ("                                      init: card2=%d\n", card2 );
show_gset ( 3 );
show_gset ( 2 );
show_gset ( 1 );
***/
  while ( ( card2 ) && ( closure_ok ) ) {
    valOrd_gset2 ( &cc, 1 );                             /* cc is mch */
/***
printf ("  processing cc %s from gset2\n", GetName ( cc ) );
***/
    if ( HasImp ( cc ) ) {
      get_botref ( &cc1, cc );                           /* cc1 is imp */
/***
printf ("    has imp cc1 %s\n", GetName ( cc1 ) );
***/
      def_inc_ipt ( &bb, cc1 );
      if ( bb ) {
        card_inc_ipt ( &nn, cc1 );
        while ( nn ) {
          valOrd_inc_ipt( &cc3, cc1, nn );                 /* cc3 is mch */
/***
printf ("      imports cc3 %s \n", GetName ( cc3 ) );
***/
          member_gset3 ( &bb, cc3 );
          if ( bb ) { closure_ok = 0; break; }
          add_gset2 ( &rr, cc3 );
          chk_rep ( rr, 211 );
          nn--;
	} /* while ( nn ) - card_inc_ipt */
      } /* if ( bb ) - def_inc_ipt */
      def_sees_uses ( &bb, cc1 );
      if ( bb ) {
        card_sees_uses ( &nn, cc1 );
        while ( nn ) {
          valOrd_sees_uses( &cc3, cc1, nn );                 /* cc3 is mch */
/***
printf ("      sees cc3 %s \n", GetName ( cc3 ) );
***/
          member_gset3 ( &bb, cc3 );
          if ( bb ) { closure_ok = 0; break; }
          add_gset2 ( &rr, cc3 );
          chk_rep ( rr, 229 );
          nn--;
	} /* while ( nn ) - card_sees_uses */
      } /* if ( bb ) - def_sees_uses */
    } /* ( HasImp ( cc ) */
    if ( ! closure_ok ) break;
    del_gset2 ( cc );
    card_gset2 ( &card2 );
/***
printf ("                                      now: card2=%d\n", card2 );
show_gset ( 3 );
show_gset ( 2 );
show_gset ( 1 );
***/
  } /* while ( ( card_gset2 ) && ( closure_ok ) ) */

/***
printf ("closure_ok=%d\n", closure_ok );
***/

  if ( closure_ok ) {
    sprintf ( fifo_write_buf, "(?,1):%d:0", BT_BSEL );
  }
  else {
    sprintf ( fifo_write_buf, "(?,2):%d:0", BT_BSEL );
  }
  InvokeB ( without_XTerm, 1 );
}

int
TopLevelImp ( cc, cc_0 )
int cc, cc_0;
{
  int cc_top, cc_top_0, loc_itr, cc_itr, another_level_found, ext, bb;

  /***
  cc is an imp, cc_0 the spec
  the top-level (wrt import) is returned (possibly cc itself)
  during the iteration:
    cc_top is the current top-level imp
    cc2 is its abstraction
    if the loop finds a new top-level imp, cc_found is set
    the loop continues as long as cc1 != cc_found
  ***/

/***
printf ( "-----------\nTopLevelImp ( cc=%s )\n", GetName ( cc ) );
***/

  cc_top = cc;          /* initialise the current top-level imp to the parameter */
  another_level_found = 1;                /* to start the loop */
  while ( another_level_found ) {
    another_level_found = 0;
    if   ( cc_top == cc ) cc_top_0 = cc_0;
    else                  get_topabs ( &cc_top_0, cc_top );
    first_Construct ( &loc_itr, &cc_itr );
    while ( loc_itr ) {
      val_ext ( &ext, cc_itr );
      if ( ext == imp ) {
        def_inc_ipt ( &bb, cc_itr );
        if ( bb ) {
          member_inc_ipt ( &bb, cc_itr, cc_top_0 );
          if ( bb ) {
/***
printf ( "  new top-level imp found - %s\n", GetName ( cc_itr ) );
***/
            cc_top = cc_itr;
            another_level_found = 1;
            break;               /* new level found, so break out of iteration */
	  }
	}
      } /* if ( ext == imp ) */
      next_Construct ( &loc_itr, &cc_itr, loc_itr, cc_itr );
    } /* while ( loc_itr ) */
  } /* while ( another_level_found ) */
/***
printf ( "returning %s\n-----------\n", GetName ( cc_top ) );
***/
  return ( cc_top );
}


void
DupIptCheckOK ()
{
  int ss, cc, cc0, cc1, cc2, cc3, cc4, bb, rr, nn, mm, loc_itr, cc_itr, ext;
  int dup_ipt_ok = 1;

/***
printf ( "---------------------------------------------------------\nDupIptCheckOK()\n" );
***/

  Load_Seen_gset1_Ipt_gset2 ( & cc, & cc0 );

  /***
  save imports in gset3
   ***/
  val_gset2 ( &ss );
  mod_gset3 ( &rr, ss );
  chk_rep ( rr, 235 );

  /***
  stage 1: find top level node
  ***/

  cc1 = TopLevelImp ( cc, cc0 );

/***
printf ( "  %s IMPORTS\n", GetName ( cc ) );
show_gset ( 2 );
printf ( "  top-level imp is %s\n", GetName ( cc1 ) );
***/

  /***
  stage 2: move down through import structure from the top level imp cc1
    gset2 is the (expanding) list of recursively imported machines
      this is initialised to the set of machines imported by cc
    gset1 is the working set containing imps
      this set is initialised to the top level imp cc1
      and the imps of the machines imported by cc
      since they won't otherwise be found!
    loop while gset1 != {}
        1. take 1st member of gset2, cc2 (imp)
        2. get ipt list, each is cc3
        3. check if cc3 in gset2
           if so, error - break
           if not, get imp for cc3 if ir exists and add to gset1 (cc4)
  ***/

  clear_gset1 ();
  add_gset1 ( &rr, cc1 );
  chk_rep ( rr, 230 );

  /***
  add the imps of the machines imported by cc to gset1
  ***/
  card_gset2 ( &mm );              /* the machines imported by cc */
  while ( mm ) {
    valOrd_gset2 ( &cc2, mm );            /* cc2 is mch */
    if ( HasImp ( cc2 ) ) {
      get_botref ( &cc3, cc2 );        /* cc3 is imp */   
      add_gset1 ( &rr, cc3 );
      chk_rep ( rr, 233 );
    }
    mm--;
  } /* while ( mm ) - card_gset2 */

/***
printf ( "  Initially:\n" );
show_gset ( 1 );
show_gset ( 2 );
***/

  card_gset1 ( &nn );
  while ( nn ) {
    valOrd_gset1 ( &cc2, 1 );                             /* cc2 is imp */
/***
printf ( "\n" );
show_gset ( 1 );
show_gset ( 2 );
printf ( "  processing imp %s\n", GetName ( cc2 ) );
***/
    del_gset1 ( cc2 );
    def_inc_ipt ( &bb, cc2 ); 
    if ( bb ) {
      card_inc_ipt ( &mm, cc2 );
      while ( mm ) {
        valOrd_inc_ipt ( &cc3, cc2, mm );                 /* cc3 is mch */
/***
printf ( "    imports %s\n", GetName ( cc3 ) );
***/
        member_gset2 ( &bb, cc3 );
        if ( bb ) { dup_ipt_ok = 0; break; }       /* break out of inner loop */
/***
printf ( "      adding %s to gset2\n", GetName ( cc3 ) );
***/
        add_gset2 ( &rr, cc3 );
        chk_rep ( rr, 231 );
        if ( HasImp ( cc3 ) ) {
          get_botref ( &cc4, cc3 );                      /* cc4 is imp */   
/***
printf ( "      adding %s to gset1\n", GetName ( cc4 ) );
***/
          add_gset1 ( &rr, cc4 );
          chk_rep ( rr, 232 );
	}
        else if ( cc3 == cc0 ) {
/***
printf ( "      adding %s to gset1\n", GetName ( cc ) );
***/
          add_gset1 ( &rr, cc );
          chk_rep ( rr, 234 );
	}
        mm--;
      } /* while ( mm ) - card_inc_ipt */
    }
    if ( ! dup_ipt_ok ) break;                     /* break out of outer loop */
    card_gset1 ( &nn );
  } /* while ( nn ) - card_gset1 */
  
  if ( dup_ipt_ok ) {
    sprintf ( fifo_write_buf, "(?,1):%d:0", BT_BSEL );
  }
  else {
    /***
    find who else (other than cc2) imports cc3
    ***/
    member_gset3 ( &bb, cc3 );
    if ( ( bb ) && ( cc2 != cc ) ) {
      cc_itr = cc;
    }
    else {
      first_Construct ( &loc_itr, &cc_itr );
      while ( loc_itr ) {
        val_ext ( &ext, cc_itr );
        if ( (ext == imp ) && ( cc_itr != cc2 ) ) {
          def_inc_ipt ( &bb, cc_itr );
          if ( bb ) {
            member_inc_ipt ( &bb, cc_itr, cc3 );
            if ( bb ) {
/***
printf ( "  other importing imp found - %s\n", GetName ( cc_itr ) );
***/
              break;
	    }
	  }
        } /* if ( ext == imp ) */
      next_Construct ( &loc_itr, &cc_itr, loc_itr, cc_itr );
      } /* while ( loc_itr ) */
    } /* else */
    sprintf ( buf, "%s", GetName ( cc2 ) );
    sprintf ( str_buf, "%s", GetName ( cc_itr ) );
    sprintf ( fifo_write_buf, "(?,(%s;%s;%s):%d:0)", str_buf, buf, GetName ( cc3 ), BT_BSEL );
  }
  InvokeB ( without_XTerm, 1 ); 
}

void
ProcessAnalyse ( str, name, ext_num )
char * str;
char * name;
int ext_num;
{
  char sub_str [ 50 ];
  int i = 0;
  int cc, j, obj, rr;

  clear_gset1 ();
  clear_gset2 ();
  clear_gseq ();
  GetObjFromNameExt ( &cc, name, ext_num );
  Load_SRC_CFG_Names ( cc );
/***
printf("analysing %s\n", GetName ( cc ) );
***/
  j = 0;
  while ( str [ i ] != ';' ) {
    while ( str [ i ] != ',' && str [ i ] != ';' ) {
      sub_str [ j ] = str [ i ];
      i++;
      j++;
    }
    if ( str [ i ] != ';' ) {
      i++;
    }
    if ( sub_str [ j-1 ] != '?' ) {
      sub_str [ j ] = '\0';
      GetObjFromNameExt ( &obj, sub_str, mch );
      add_gset1( &rr, obj );
      chk_rep ( rr, 6 );
/***
printf("added %s to sees_uses\n", GetName ( obj ) );
***/
    }
/***
else { printf("1st arg ?\n"); }
***/
    j = 0;
  }
  i++;
  j = 0;
  while ( str [ i ] != ';' ) {
    while ( str [ i ] != ',' && str [ i ] != ';' ) {
      sub_str [ j ] = str [ i ];
      i++;
      j++;
    }
    if ( str [ i ] != ';' ) {
      i++;
    }
    if ( sub_str [ j-1 ] != '?' ) {
      sub_str [ j ] = '\0';
      GetObjFromNameExt ( &obj, sub_str, mch );
      add_gset2 ( &rr, obj );
      if ( ! rr ) {
        BT_err_exit ( 7 );
        return;
      }
/***
printf("added %s to inc_ipt\n", GetName ( obj ) );
***/
    }
/***
else { printf("2nd arg ?\n"); }
***/
    j = 0;
  }
  i++;
  while ( str [ i ] != '\0' ) {
    sub_str [ j ] = str [ i ];
    i++;
    j++;
  }
  if ( sub_str [ j-1 ] != '?' ) {
    sub_str [ j ] = '\0';
/***
printf("3rd arg %s\n",sub_str );
***/
    GetMchRefImpObjFromNameExt ( &obj, sub_str );
  }
  else {
/***
printf("3rd arg ?\n");
***/
    GetObjFromNameExt ( &obj, name, mch );
  }
  push_gseq( &rr, obj );
  chk_rep ( rr, 8 );
/***
printf("abstraction %s\n", GetName ( obj ) );
***/

  analyse ( &rr, cc );
  chk_rep ( rr, 9 );
  if ( ext_num == imp ) {
    int pp, i, ee, nn, mm, cc2, cc3, cc4, cc5, bb, tmparr [ 100 ];
    get_topabs ( &cc2, cc );
    top_level_dep_cstr = cc2;
    get_dep_cstr ( &rr, cc2 );
    chk_rep ( rr, 46 );
    card_gset1 ( &pp );
    i = 0;
    while ( pp && i < 100 ) {
      valOrd_gset1 ( &cc3, pp );        /* recipt_mchlist in tmparr */
      val_ext ( &ee, cc3 );
      if ( ee == imp ) {
        tmparr [ i ] = cc3;
        i++;
      }
      pp--;
    }
/***
printf("---\n");
for ( pp = 0 ; pp < i ; pp++ ) {
printf("tmparr [ %d ]: %d\n",pp,tmparr [ pp ]); }
printf("---\n");
***/
    for ( pp = 0 ; pp < i ; pp++ ) {
      nn = CheckDuplicateIpt ( tmparr [ pp ] );
      if ( nn ) {
        int found;
        char buf [ 100 ];
        int recipt_mch_arr [ 100 ], qq, j;
        card_gset1 ( &qq );
        j = 0;
        while ( qq && j < 100 ) {
          valOrd_gset1 ( &cc3, qq );  /* recipt_mchlist in recipt_mch_arr */
          recipt_mch_arr [ j ] = cc3;
          j++;
          qq--;
        }
        get_topabs ( &cc4, tmparr [ pp ] );  /* add abs of tmparr [ pp ]! */
        recipt_mch_arr [ j ] = cc4;
        j++;
        strcpy ( buf, "\n  Warning - duplicate import in design structure\n  for " );
        GetShortName ( tmparr [ pp ] );
        strcat ( buf, ":\n" );
        DisplayCurrWinText ( buf );
/***
printf("---\n");
show_gset(1);
printf("---\n");
for ( qq = 0 ; qq < j ; qq++ ) {
printf("recipt_mch_arr [ %d ]: %d\n",qq,recipt_mch_arr [ qq ]); }
printf("---\n");
***/
        while ( nn ) {
          found = 0;
          valIth_gseq ( &cc2, nn );            /* dup ipt mch */
          top_level_dep_cstr = cc2;
          get_dep_cstr ( &rr, cc2 );
          chk_rep ( rr, 42 );
          card_gset1 ( &mm );
          while ( mm ) {
            valOrd_gset1 ( &cc3, mm );        /* dep_cstr for cc2 */
            member_inc_ipt ( &bb, cc3, cc2 );
            if ( bb ) {
              get_topabs ( &cc4, cc3 );
              /***
              check in scope of tmparr [ pp ] ( recipt_mch_arr )
              ***/
              bb = 0;
              qq = 0;
              while ( ! bb && qq < j ) {
                if ( cc4 == recipt_mch_arr [ qq ] ) {
                  bb = 1;
		}
                qq++;
	      }
              if ( bb ) {
                switch ( found ) {
		case 0:
                  cc5 = cc3;
                  break;
                case 1:
                  strcpy ( buf, "\n      " );
                  strcat ( buf, GetShortName ( cc2 ) );
                  strcat ( buf, " is imported by:\n        " );
                  strcat ( buf, GetShortName ( cc5 ) );
                  strcat ( buf, "\n        " );
                  strcat ( buf, GetShortName ( cc3 ) );
                  strcat ( buf, "\n" );
                  DisplayCurrWinText ( buf );
                  break;
                default:
                  strcpy ( buf, "        " );
                  strcat ( buf, GetShortName (cc3 ) );
                  strcat ( buf, "\n" );
                  DisplayCurrWinText ( buf );
                  break;
		}
                found++;
	      }
	    }
            mm--;
          }
        nn--;
	}
      }
    }
  }


  SetDisplayField_obj_Changed ( cc );
}


void
ProcessDocument ( str, name, ext_num )
char * str;
char * name;
int ext_num;
{
  char sub_str [ 50 ];
  char ext [ 10 ];
  int i = 0;
  int j, k, obj, cc, rr, st, nn;

  clear_gset1 ();
  GetObjFromNameExt ( &obj, name, ext_num );
  Load_SRC_CFG_Names ( obj );
/***
printf("documenting %s\n", GetName ( obj ) );
printf("str: |%s|\n",str);
***/
  if ( str [ 0 ] != '?' ) {
    j = 0;
    while ( str [ i ] != '\0' ) {
      while ( str [ i ] != '.' ) {
        sub_str [ j ] = str [ i ];
        i++;
        j++;
      }
      sub_str [ j ] = '\0';
/***
printf("sub_str %s\n",sub_str);
***/
      i++;
      j = 0;
      while ( str [ i ] != '.'  && str [ i ] != ','  && str [ i ] != '\0' ) {
        ext [ j ] = str [ i ];
        i++;
        j++;
      }
      ext [ j ] = '\0';
/***
printf("ext %s\n",ext);
***/
      j = 1;
      while ( strcmp ( ext, extens [ j ] ) != 0 ) {
        j++;
      }
/***
printf("ext %d\n",j);
***/

      if ( str [ i ] == '.' ) {    /* a.b.n.prf */
        switch ( j ) {
        case mch:
          j = mch_prf;
          break;
        case ref:
          j = ref_prf;
          break;
        case imp:
          j = imp_prf;
          break;
        }
        i += 4;  /* skip prf  - now points to . if proof level > 0
                    or EOF or , if proof level 0                      */
/***
printf ( "1: `%c'\n", str [ i ] );fflush ( stdout );
***/
        if ( ( str [ i ] == '\0' ) || ( str [ i ] == ',' ) ) {
          nn = (-1);
	  /*  i--; */
	}
        else {
          i++;
          nn = 0;
          while ( ( str [ i ] != '\0' ) && ( str [ i ] != ',' ) ) { 
            nn = ( nn * 10 ) + str [ i ] - '0';
            i++;
	  }
        }
        nn++;
/***
printf ( "2: `%c'\n", str [ i ] );fflush ( stdout );
***/
/***
printf("however a prf - ext %d, (incremented) level %d\n",j,nn);
***/
        { int mm;
          GetPrfObjFromNameExtLvl ( &k, sub_str, j, nn - 1, 0 );
	}
        if ( k ) add_gset1( &rr, k );
/***
printf("added prf object %s to sees_uses\n", GetName ( k ) );
***/
      }
      else {                       /* not a.b.n.prf */
        if ( ( strcmp ( ext, "eps" ) != 0 )  &&
             ( strcmp ( ext, "tex" ) != 0 )    ) {
          GetObjFromNameExt ( &k, sub_str, j );
          add_gset1( &rr, k );
/***
printf("added %s to sees_uses\n", GetName ( k ) );
***/
	}
      }
      chk_rep ( rr, 19 );
      j = 0;
      if ( str [ i ] != '\0' ) i++;
    }
  }
  cre_sees_uses ( &rr, obj );
  chk_rep ( rr, 20 );
  val_gset1 ( &j );
  mod_sees_uses ( &rr, obj, j );
  chk_rep ( rr, 21 );
  val_curMRIState ( &st, obj );
  mod_dmu ( st, TRUE );
  val_cptMRIState ( &st, obj );
  mod_dmu ( st, TRUE );
  SetDisplayField_obj_Changed ( obj );
}



void
ProcessEnumItf ( str, name, ext_num, motif_option )
char * str;
char * name;
int ext_num;
int motif_option;
{
  char sub_str [ 50 ];
  char ext [ 10 ];
  int i = 0;
  int j, k, obj, cc, rr, st;

  clear_gset1 ();
  GetObjFromNameExt ( &obj, name, ext_num );
  Load_SRC_CFG_Names ( obj );
/***
printf("enumerating/interfacing %s\n", GetName ( obj ) );
printf("str: |%s|\n",str);
***/
  if ( str [ 0 ] != '?' ) {
    j = 0;
    while ( str [ i ] != '\0' ) {
      while ( str [ i ] != ','  && str [ i ] != '\0' ) {
        sub_str [ j ] = str [ i ];
        i++;
        j++;
      }
      sub_str [ j ] = '\0';
/***
printf("sub_str: |%s|\n",sub_str);
***/
      GetObjFromNameExt ( &cc, sub_str, mch );
      add_gset1( &rr, cc );
      chk_rep ( rr, 190 );
      j = 0;
      if ( str [ i ] != '\0' ) {
        i++;
      }
/***
printf("added %s.%s to sees_uses\n", GetName ( cc ) );
***/
    }
  }
  cre_sees_uses ( &rr, obj );
  chk_rep ( rr, 20 );
  val_gset1 ( &j );
  mod_sees_uses ( &rr, obj, j );
  chk_rep ( rr, 21 );
  val_curGENState ( &st, obj );
  mod_gen1 ( st, TRUE );
  if ( motif_option ) {
    mod_gen2 ( st, TRUE );
  }
  val_cptGENState ( &st, obj );
  mod_gen1 ( st, TRUE );
  if ( motif_option ) {
    mod_gen2 ( st, TRUE );
  }
  SetDisplayField_obj_Changed ( obj );
}



void
CheckBaseUnderscore ( ok, name )
int * ok;
char * name;
{
  int i = 0;

  * ok = 1;
  while ( * ok  && name [ i ] != '\0' ) {
    if ( name [ i ] == '_' ) {
      * ok = 0;
    }
    i++;
  }
  if ( ! * ok ) {
    Popup_Err ( 0, "Base names may not contain the underscore character!" );     }
}


void
ProcessCompletedJobs ( BT_num, str, name, ext_num )
int BT_num;
char * str;
char * name;
int ext_num;
{
  int ok, obj, arr_num, cc1;
  int st;

/***
printf ( "    +++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
printf ( "    ProcessCompletedJobs ( %d `%s' `%s' %d )\n",BT_num,str,name,ext_num );
printf ( "        (Popup_Sel_flag %d radiobox_flag %d)\n", Popup_Sel_flag, radiobox_flag );
printf ( "    +++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
***/

  XmUpdateDisplay ( curr_text );

  
#ifdef WWW_VERSION

  WWWConstructsCycleCheck ( 0 );

#endif /* WWW_VERSION */



  if ( terminal_option ) {
    return;
  }

  switch ( BT_num ) {

  case BT_CMT_CSTR:
    if ( BaseCapacity_ok () ) {
      intr_usr_cstr ( &ok, &obj, name, ext_num );
      chk_rep ( ok, 2 );
      DisplayInsert ( obj );
    }
    else {
      BaseCapacityReached ();
    }
    break;


  case BT_CMT_OPEN_CSTR:
    if ( BaseCapacity_ok () ) {
      void SetDisplay_visible ();

      intr_usr_cstr( &ok, &obj, name, ext_num );
      chk_rep ( ok, 2 );
      DisplayInsert ( obj );

      SetDisplay_visible ( obj );
      Load_SRC_CFG_Names ( obj );

      if ( IsClosed ( obj ) ) PreOpenConstruct ( obj );

    }
    else {
      BaseCapacityReached ();
    }
    break;

  case BT_CMT_GEN_CSTR:
    {
      int nm [ 50 ], ex;
      if ( BaseCapacity_ok () ) {
        GetExtNumFromString ( &ex, str );
        GetNameFromString ( nm, str );
        GetObjFromNameExt ( &cc1,  nm, ex );
        if ( ex == ops ) {
          if ( ext_num == mch || ext_num == imp ) {
            intr_gen ( &ok, &obj, ext_num, name, bse_gen, cc1 );
            chk_rep ( ok, 25 );
            DisplayInsert ( obj );
            val_gen_by ( &cc1, cc1 );
            val_curGENState ( &st, cc1 );
            mod_gen2 ( st, TRUE );
            val_cptGENState ( &st, cc1 );
            mod_gen2 ( st, TRUE );
	  }
        }
        else if ( ex == bse ) {
          if ( ext_num == ops ) {
            intr_gen ( &ok, &obj, ext_num, name, bse_gen, cc1 );
            chk_rep ( ok, 26 );
            DisplayInsert ( obj );
            val_curGENState ( &st, cc1 );
            mod_gen1 ( st, TRUE );
            val_cptGENState ( &st, cc1 );
            mod_gen1 ( st, TRUE );
          }
        }
        else if ( ex == enm ) {
          int cc2, cc3, nn, type;

          intr_gen ( &ok, &obj, ext_num, name, enm_gen, cc1 );

          chk_rep ( ok, 30 );
          DisplayInsert ( obj );
          clear_gset1 ();             /* sees/uses */
          /***
          copy sees/uses from nm.enm to nm.mch
	  ***/
          GetObjFromNameExt ( &cc2,  nm, 6 ); /* nm.enm */
          card_sees_uses ( &nn, cc2 );
          while ( nn ) {
            valOrd_sees_uses( &cc3, cc2, nn );
            add_gset1 ( &ok, cc3 );
            chk_rep ( ok, 93 );
            nn--;
          }

          clear_gset2 ();
          clear_gseq ();
          push_gseq ( &ok, obj );
          chk_rep ( ok, 31 );
          analyse( &ok, obj );
          chk_rep ( ok, 32 );
        }

        else if ( ex == itf ) {
          intr_gen ( &ok, &obj, ext_num, name, itf_gen, cc1 );
          chk_rep ( ok, 30 );
          DisplayInsert ( obj );
          val_curGENState ( &st, cc1 );
          mod_gen1 ( st, TRUE );
          val_cptGENState ( &st, cc1 );
          mod_gen1 ( st, TRUE );
        }
        SetDisplayField_obj_Changed ( cc1 );
      }
      else {
        BaseCapacityReached ();
      }
    }
    break;

  case BT_CMT_OPEN_GEN_CSTR:
    {
      int nm [ 50 ], obj, ex;
      if ( BaseCapacity_ok () ) {
        GetExtNumFromString ( &ex, str );
        GetNameFromString ( nm, str );
        GetObjFromNameExt ( &cc1,  nm, ex );
        if ( ex == bse ) {
          if ( ext_num == ops ) {
            intr_gen ( &ok, &obj, ext_num, name, bse_gen, cc1 );
            chk_rep ( ok, 26 );
            DisplayInsert ( obj );
            val_curGENState ( &st, cc1 );
            mod_gen1 ( st, TRUE );
            val_cptGENState ( &st, cc1 );
            mod_gen1 ( st, TRUE );
          }
          Load_SRC_CFG_Names ( obj );
          if ( IsClosed ( obj ) ) PreOpenConstruct ( obj );
        }
      }
      else {
        BaseCapacityReached ();
      }
    }
    break;

  case BT_CMT_LIB_CSTR:
    if ( BaseCapacity_ok () ) {
      int su, ss;
      intr_lib_machine( &ok, &obj, name );
      chk_rep ( ok, 2 );
      DisplayInsert ( obj );
      su = ProcessLibSeesIncludes ( str, name, mch );
      if ( su ) {
        val_gset1( &ss );
        mod_sees_uses ( &ok, obj, ss );
        chk_rep ( ok, 91 );
      }
      card_gset2 ( &su );
      if ( su )  {
        val_gset2( &ss );
        mod_inc_ipt ( &ok, obj, ss );
        chk_rep ( ok, 213 );
      }
      HtmlMasterFileChanged = 1;
    }
    else {
      BaseCapacityReached ();
    }
    break;

  case BT_NML:
    ProcessAnalyse ( str, name, ext_num );  /* SetDisplayField_obj_Changed */
    HtmlMasterFileChanged = 1;
    break;

  case BT_POG:
    {
      int nn, rr, obj;
      if ( BaseCapacity_ok () ) {
        GetObjFromNameExt ( &obj, name, ext_num );
        Load_SRC_CFG_Names ( obj );
        CreNumFromBuf ( &nn, str );
        pogenerate ( &rr, obj, nn );
        chk_rep ( rr, 22 );
        SetDisplayField_obj_Changed ( obj );
      }
      else {
        BaseCapacityReached ();
      }
    }
    break;

  case BT_AUP:
    {
      int nn, tt, rr, i, obj;
      if ( BaseCapacity_ok () ) {
        GetObjFromNameExt ( &obj, name, ext_num );
        Load_SRC_CFG_Names ( obj );
        i = 0;
        nn = 0;          /* pobs left */
        while ( ( str [ i ] != ',' ) && ( str [ i ] != '\0' ) ) {
          nn = ( nn * 10 ) + str [ i ] - '0';
          i++;
	}
        i++;
        tt = 0;          /* total pobs */
        while ( ( str [ i ] != ',' ) && ( str [ i ] != '\0' ) ) {
          tt = ( tt * 10 ) + str [ i ] - '0';
          i++;
	}
        autoprove ( &rr, obj, nn, tt );
        chk_rep ( rr, 86 );
        SetDisplayField_obj_Changed ( obj );
      }
      else {
        BaseCapacityReached ();
      }
    }
    break;

  case BT_PFP:
    {
      int nn, cc, rr, obj;
      if ( BaseCapacity_ok () ) {
        GetObjFromNameExt ( &obj, name, ext_num );     /*** the mch/ref/imp ***/
        Load_SRC_CFG_Names ( obj );
        SetDisplayField_obj_Changed ( obj );           /*** so ppf is updated ***/
        CreNumFromBuf ( &nn, str );
        intr_prf ( &rr, &cc, ext_num, obj, nn );       /*** cc the .prf ***/
        chk_rep ( rr, 63 );
        DisplayInsert ( cc );
      }
      else {
        BaseCapacityReached ();
      }
    }
    break;

  case BT_DMU:
    {
      int obj, st, cc1, rr, nn;
      if ( BaseCapacity_ok () ) {
        switch ( ext_num ) {
        case mch:
        case ref:
        case imp:
          GetObjFromNameExt ( &obj, name, ext_num );
          val_curMRIState ( &st, obj );
          mod_dmu ( st, TRUE );
          val_cptMRIState ( &st, obj );
          mod_dmu ( st, TRUE );
          SetDisplayField_obj_Changed ( obj );
          break;
        case bse:
        case enm:
        case itf:
          GetObjFromNameExt ( &obj, name, ext_num );
          val_curGENState ( &st, obj );
          mod_gen_dmu ( st, TRUE );
          val_cptGENState ( &st, obj );
          mod_gen_dmu ( st, TRUE );
          SetDisplayField_obj_Changed ( obj );
          break;
        case mch_prf:
        case ref_prf:
        case imp_prf:
          CreNumFromBuf ( &nn, str );
          if ( nn == 999999 ) nn = (-1);
          GetPrfObjFromNameExtLvl ( &obj, name, ext_num, nn, 1 );
          val_gen_by ( &cc1, obj );
          val_curMRIState ( &st, cc1 );
          add_ppf_dmu ( &rr, st, nn + 1 );
          val_cptMRIState ( &st, cc1 );
          add_ppf_dmu ( &rr, st, nn + 1 );
          chk_rep ( rr, 65 );
          SetDisplayField_obj_Changed ( obj );
          break;
        }
      }
      else {
        BaseCapacityReached ();
      }
    }
    break;

  case BT_DOC:
    if ( BaseCapacity_ok () ) {
      ProcessDocument ( str, name, ext_num );  /* SetDisplayField_obj_Changed */
    }
    else {
      BaseCapacityReached ();
    }
    break;

  case BT_ENUM:
    if ( BaseCapacity_ok () ) {
      ProcessEnumItf ( str, name, ext_num, 0 );  /* SetDisplayField_obj_Changed */
      HtmlMasterFileChanged = 1;
    }
    else {
      BaseCapacityReached ();
    }
    break;

  case BT_CIO:
    if ( BaseCapacity_ok () ) {
      ProcessEnumItf ( str, name, ext_num, 0 );  /* SetDisplayField_obj_Changed */
    }
    else {
     BaseCapacityReached ();
   }
   break;

  case BT_CIOM:
    if ( BaseCapacity_ok () ) {
      ProcessEnumItf ( str, name, ext_num, 1 );  /* SetDisplayField_obj_Changed */
    }
    else {
     BaseCapacityReached ();
   }
   break;

  case BT_TRL:
    {
      int cc, st;
      if ( BaseCapacity_ok () ) {
        GetObjFromNameExt ( &cc, name, ext_num );
        val_curMRIState ( &st, cc );
        mod_trl ( st, TRUE );
        val_cptMRIState ( &st, cc );
        mod_trl ( st, TRUE );
	clear_gset1();            /* see BT_LNK, BT_RUN - get_recipt_mchlist */
        HtmlMasterFileChanged = 1;
        SetDisplayField_obj_Changed ( cc );
      }
      else {
        BaseCapacityReached ();
      }
    }
    break;

  case BT_LNK:
    {
      int cc, st, rr;
      if ( BaseCapacity_ok () ) {
        GetObjFromNameExt ( &cc, name, ext_num );
        val_curMRIState ( &st, cc );
        mod_lnk ( st, TRUE );
        val_cptMRIState ( &st, cc );
        mod_lnk ( st, TRUE );
        get_recipt_mchlist ( &rr, cc );
        chk_rep ( rr, 152 );
        HtmlMasterFileChanged = 1;
        SetDisplayField_obj_Changed ( cc );
      }
      else {
        BaseCapacityReached ();
      }
    }
    break;

  case BT_RUN:
    {
      int cc, rr;
      GetObjFromNameExt ( &cc, name, ext_num );
      get_recipt_mchlist ( &rr, cc );
      chk_rep ( rr, 153 );
      HtmlMasterFileChanged = 1;
      SetDisplayField_obj_Changed ( cc );
    }
    break;

  case BT_CK_PARSE:
    return;
    break; 

  case BT_DMU_PRASE_ERROR_M:
    strcpy ( buf, "\n  See: " );
    strcat ( buf, str );
    strcat ( buf, "\n  (Parse errors appear at the end of the file)\n" );
    DisplayCurrWinText ( buf );
    break; 

  case BT_CRE_HTML_RETURN_M:
    sprintf ( buf, " done\n\n  Committed %s\n", GetName ( curr_obj ) );
    DisplayCurrWinText ( buf );
    CheckFileParses_ContinueLoop ();
    break;

  default:

/***
printf("Couldn't \"ProcessCompletedJobs\"!\n");
printf ( "++++++++++++ .Bcjm ++++++++++++\n" );
system ( "cat .Bcjm" );
printf ( "+++++++++++++++++++++++++++++++\n" );
***/
    DisplayCurrWinText ( "\n\n  Couldn't \"ProcessCompletedJobs\"\n " );
    system ( "cat .Bcjm" );
    DisplayCurrentEnv ();
    break;
  }

  CheckUpdateChangedDisplay_NoLnk ();
}

void
LoadBcjm ()
{
  /***
  list of jobs completed loaded into job_arr:
  eg. `BT_PUP\E4\Eaaa\E1\nBT_PUP:1:bbb\E3\n' in .Bcjm
  1  =>mch, 3=>imp etc
  ***/

  FILE * Bcjm;
#define LoadBcjm_nameMAX 2500
  char name [ LoadBcjm_nameMAX + 10 ];
  int c, i, BT_num, ext_num, objnum, found;
#define LoadBcjm_strMAX 7500
  char str [ LoadBcjm_strMAX + 10 ];
  char ext [ 10 ];

/***
printf ( "++++++++++++ .Bcjm ++++++++++++\n" );
system ( "cat .Bcjm" );
printf ( "+++++++++++++++++++++++++++++++\n" );
***/

  Bcjm = fopen ( ".Bcjm", "r" );
  if ( Bcjm == NULL ) {
    printf( "\n  BMotif: can't open .Bcjm for reading\n" );
    BT_err_exit ( 0 );
    return;
  }
  c = getc ( Bcjm );
  while ( c != EOF ) {
    while ( c != '\n' && c != EOF ) {
      /***
      get BT_job number
      ***/
      BT_num = 0;
      while ( c != 27 && c != '\n' && c != EOF ) {
        if ( c != ' ' ) BT_num = ( ( BT_num * 10 ) + c - '0' );
        c = getc ( Bcjm );
      }
      if ( c != 27 ) {
        printf( "\n  .Bcjm format error 1.%d\n", i );
        BT_err_exit ( 0 );
        return;
      }
      /***
      get str
      ***/
      c = getc ( Bcjm );
      i = 0;
      while ( c != 27 && c != '\n' && c != EOF && i < LoadBcjm_strMAX ) {
        if ( c != ' ' ) str [ i++ ] = c;
        c = getc ( Bcjm );
      }
      if  ( i == LoadBcjm_strMAX ) {
        printf( "\n  .Bcjm format error 2.%d\n", i ); /* string too long */
        BT_err_exit ( 0 );
        return;
      }
      else if ( c != 27 ) {
        printf( "\n  .Bcjm format error 3.%d\n", i );
        BT_err_exit ( 0 );
        return;
      }
      str [ i ] = '\0';
      /***
      get name
      ***/
      c = getc ( Bcjm );
      i = 0;
      while ( c != 27 && c != '\n' && c != EOF && i < LoadBcjm_nameMAX ) {
        if ( c != ' ' ) name [ i++ ] = c;
        c = getc ( Bcjm );
      }
      if ( c != 27 ) {
        name [ i ] ='\0';
        printf( "\n  .Bcjm format error 4.%d %s\n", i, name );
        BT_err_exit ( 0 );
        return;
      }
      name [ i ] ='\0';
      /***
      get ext_num
      ***/
      c = getc ( Bcjm );
      ext_num = 0;
      while ( c != 27 && c != '\n' && c != EOF ) {
        if ( c != ' ' ) ext_num = ( ( ext_num * 10 ) + c - '0' );
        c = getc ( Bcjm );
      }
      if ( c != '\n' ) {
        printf( "\n  .Bcjm format error 5.%d\n", i );
        BT_err_exit ( 0 );
        return;
     }
      ProcessCompletedJobs ( BT_num, str, name, ext_num );
      if ( c != EOF ) c = getc ( Bcjm );
    }
  }
  fclose ( Bcjm );

  /***
  empty .Bcjm
  ***/
  {
    FILE * Bcjm;
    Bcjm = fopen ( ".Bcjm", "w" );
    if ( Bcjm == NULL ) {
      printf( "\n  BMotif: can't open .Bcjm for writing\n" );
      BT_err_exit ( 0 );
      return;
    }
    fclose ( Bcjm );
  }
}


/****************************************************************************/

int
FileDiffIntoBcom ( obj )
int obj;
{
  FILE * Bcom;
  int c;
  int i = 0;
  int ext;

  Load_SRC_CFG_Names ( obj );
  sprintf ( buf, "diff %s %s > .Bcom", SRCName, CFGName );

  system ( buf );

  Bcom = fopen ( ".Bcom", "r" );
  if ( Bcom == NULL ) {
    perror( " .Bcom" );
    AbortedMsgFile ( "\".Bcom\" for reading" );
    Kill_bplatform_and_exit ( 1, 0 );
  }
  c = getc ( Bcom );
  while ( c != EOF && c != '\n' && i < 10 ) {
    buf [ i++ ] = c;
    c = getc ( Bcom );
  }
  buf [ i ] = '\0';
  fclose ( Bcom );
  return ( strcmp ( buf, "" ) != 0 );
}

void
LoadFileIntoBuf ( file, str_buf, max_str_buf )
char * file;
char * str_buf;
int max_str_buf;
{
  FILE * file_ptr;
  int i = 0;
  int count, c;

  count = 1;
  file_ptr = NULL;
  while ( file_ptr == NULL && count < 51 ) {
    file_ptr = fopen ( file, "r" );
    if ( file_ptr == NULL ) {
/***
printf( "LoadFileIntoBuf trying to open %s (attempt %d)\n", file, count );
***/
      sleep ( 1 );
    }
    if ( count == 50 ) {
      {
        char buf1 [ 100 ];
        strcpy ( buf1, "\"" );
        strcat ( buf1, file );
        strcat ( buf1, "\" for reading" );
        AbortedMsgFile ( buf1 );
      }
      Kill_bplatform_and_exit ( 1, 0 );
    }
    else {
      count++;
    }
  }

  c = getc ( file_ptr );
  while ( c != EOF && i < max_str_buf - 1 ) {
    if ( c >= 10 ) {
      str_buf [ i++ ] = c;
    }
    c = getc ( file_ptr );
  }
  str_buf [ i ] = '\0';

  fclose ( file_ptr );

  if ( i == max_str_buf - 1 ) {
    DisplayCurrWinText ( "\n  Entire file (" );
    DisplayCurrWinText ( file );
    DisplayCurrWinText ( ") may not have been read\n" );
  }
}

void
Sort_sel_strs ()
{
  int i,j,tmp;
  char tmp_sel [ 1501 ];

  for ( i = 0 ; i < sel_arr_tot; i++ ) {
    for ( j = i + 1; j < sel_arr_tot; j++ ) {
      if ( strcmp ( sel_str_arr [ i ],  sel_str_arr [ j ] ) > 0 ) {
        strcpy ( tmp_sel, sel_str_arr [ i ] );
        strcpy ( sel_str_arr [ i ], sel_str_arr [ j ] );
        strcpy ( sel_str_arr [ j ], tmp_sel );
        tmp = sel_obj_arr [ i ];
        sel_obj_arr [ i ] = sel_obj_arr [ j ];
        sel_obj_arr [ j ] = tmp;
      }
    }
  }
}

void
Sort_sel_strs_from_second ()
{
  int i,j;
  char tmp_sel [ 1501 ];

  for ( i = 1 ; i < sel_arr_tot; i++ ) {
    for ( j = i + 1; j < sel_arr_tot; j++ ) {
      if ( strcmp ( sel_str_arr [ i ],  sel_str_arr [ j ] ) > 0 ) {
        strcpy ( tmp_sel, sel_str_arr [ i ] );
        strcpy ( sel_str_arr [ i ], sel_str_arr [ j ] );
        strcpy ( sel_str_arr [ j ], tmp_sel );
      }
    }
  }
}

void
Sort_sel_strs_from_third ()
{
  int i,j;
  char tmp_sel [ 1501 ];

  for ( i = 2 ; i < sel_arr_tot; i++ ) {
    for ( j = i + 1; j < sel_arr_tot; j++ ) {
      if ( strcmp ( sel_str_arr [ i ],  sel_str_arr [ j ] ) > 0 ) {
        strcpy ( tmp_sel, sel_str_arr [ i ] );
        strcpy ( sel_str_arr [ i ], sel_str_arr [ j ] );
        strcpy ( sel_str_arr [ j ], tmp_sel );
      }
    }
  }
}

void
GetBsel ( widget )
Widget widget;
{
/***
ESC separates items
` gives newline
***/

  FILE * Bsel;
  int i;
  int c;
  int err_msg_displayed;
/***
system ( "cat .Bsel" );
***/
  err_msg_displayed = 0;
  if ( (Bsel = fopen ( ".Bsel", "r" ) ) == NULL ) {
    perror ( " .Bsel" );
    AbortedMsgFile ( "\".Bsel\" for reading" );
    Kill_bplatform_and_exit ( 1, 0 );
  }
 
  i = 0;
  sel_arr_tot = 0;
  c = getc( Bsel );
  while ( c != '\n'                            &&
          c!= EOF                              &&
          sel_arr_tot < sel_arr_MAX    ) {
    if ( c == 27 ) { /*** ESC ***/
      sel_str_arr [ sel_arr_tot ] [ i ] = '\0';
      sel_arr_tot++;
      i = 0;
    }
    else if ( c == '`' ) {
      sel_str_arr [ sel_arr_tot ] [ i ] = '\n';
      i++;
    }
    else {
      sel_str_arr [ sel_arr_tot ] [ i ] = c;
      i++;
    }
    if ( i >= sel_str_len_MAX ) {
      if ( ! err_msg_displayed ) {
        err_msg_displayed = 1;
        DisplayCurrWinText ( "\n  String length exceeded:\n\n    " );
        DisplayCurrWinText ( sel_str_arr [ sel_arr_tot ] );
        DisplayCurrWinText ( "\n" );
        sprintf ( buf, "  Maximum selection string length exceeded (%d) ",
                                                              sel_str_len_MAX - 1 );
        Popup_Info ( buf );
      }
      while ( c!= '\n' && c!= 27 && c!= EOF ) {
        c = getc( Bsel );
      }
      ungetc ( c, Bsel );
      i = sel_str_len_MAX - 1;
    }
    c = getc( Bsel );
  }
  sel_str_arr [ sel_arr_tot ] [ i ] = '\0';
  sel_arr_tot++;
  fclose ( Bsel );
  if ( sel_arr_tot >= sel_arr_MAX ) {
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    sprintf ( buf, "  Maximum selections exceeded (%d) ", sel_arr_MAX - 1 );
    Popup_Info ( buf );
  }
/***
  {
    int i;
    for ( i = 0 ; i < sel_arr_tot ; i++ ) printf ( "  %d: |%s|\n", i, sel_str_arr [ i ] );
  }
***/
}

void
ProcessInterProverRuleRange ()
{
  int i, j, m, n, c;
  FILE * Unp;
  short unp [ 250 ];

  sprintf ( buf, "TMP/.%s_unp",  primary_string );
  Unp = fopen ( buf, "r" );
  if ( Unp != NULL ) {
    j = 0;
    c = getc ( Unp );
    while ( c != EOF ) {
      n = 0;
      while ( ( c != ';' ) && ( c != EOF ) ) {
        n = ( n * 10 ) + c - '0';
        c = getc ( Unp );
      }
      unp [ j++ ] = n;
      if ( c == ';' ) c = getc ( Unp );
    }
    fclose ( Unp );
  }
  
/***
  for ( j = 0 ; j < 250 ; j++ ) { printf ( "%3d %2d  ", j, unp [ j ] ); }
***/

  j = 0;
  sel_arr_tot = 0;
  i = 0;
  n = 0;
  while ( secondary_string [ i ] != '\0' ) {
    n = ( 10 * n ) + secondary_string [ i ] - '0';
    i++;
  }

  for ( i = 1 ; i < n ; i = i + 50 ) {
    if ( n < i + 49 )   m = n;
    else                m = i + 49;
/*
    if ( n < 10 ) {
      sprintf ( sel_str_arr [ sel_arr_tot ], "%4d.. %d", i, m );
    }
    else if ( n < 100 ) {
      sprintf ( sel_str_arr [ sel_arr_tot ], "%4d.. %2d", i, m );
    }
    else {
      sprintf ( sel_str_arr [ sel_arr_tot ], "%4d..%4d", i, m );
    }
*/
    sprintf ( sel_str_arr [ sel_arr_tot ], "%4d .. %4d  (%2d unproved)", i, m,unp [ j++ ]  );
    sel_arr_tot++;
  }
  sprintf ( sel_str_arr [ sel_arr_MAX ], "Select %s range to display", primary_string );
  Popup_Sel_flag = ipr_thy_range_selection;
  Popup_SelOne_Dialog ( top_level, sel_str_arr [ sel_arr_MAX ] );
}

void
ProcessInterProverRuleSelectionError ( nn )
int nn;
{
    printf ( "       InterProver format error %d\n", nn );
    AbortedMsg ();
    Kill_bplatform_and_exit ( 1, 0 );
}

void
ProcessInterProverRuleSelection ()
{
  FILE * Bcom;
  int i, c, n, string_overflow;

  string_overflow = 0;
  sel_arr_tot = 0;
  if ( ( Bcom = fopen ( "TMP/.Bcom", "r" ) ) == NULL )
  {
    perror ( " TMP/.Bcom" );
    AbortedMsgFile ( "\"TMP/.Bcom\" for reading" );
    Kill_bplatform_and_exit ( 1, 0 );
  }
  c = getc ( Bcom );
  if ( c == EOF ) ProcessInterProverRuleSelectionError ( 1 );
  while ( c != EOF ) {
    i = 0;
    while ( ( c != '\n' )                                &&
            ( c != EOF )                                 &&
            ( sel_arr_tot < sel_arr_MAX - 2 )    ) {
      if ( i < sel_str_len_MAX - 2 ) 
        sel_str_arr [ sel_arr_tot ] [ i++ ] = c;
      else
        string_overflow = 1;
      c = getc ( Bcom );
    }
    sel_str_arr [ sel_arr_tot ] [ i ] = '\0';
/***
printf ( "%d: %s\n", sel_arr_tot, sel_str_arr [ sel_arr_tot ] );
***/
    sel_arr_tot++;
    if ( c != EOF ) c = getc ( Bcom );
  }

  fclose ( Bcom );

  if ( string_overflow ) {
    Popup_Err ( 0, "At least one of the selections is truncated\n" );    
  }

  if ( sel_arr_tot == sel_str_len_MAX - 2 ) {
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    sprintf ( buf, "Maximum number of selections exceeded (%d)", sel_arr_MAX - 1 );
    Popup_Err ( 0, buf );
  }

  strcpy ( sel_str_arr [ sel_arr_tot ], primary_string );
/***
printf ( "\n%d: %s\n", sel_arr_tot, sel_str_arr [ sel_arr_tot ] );
***/
  Ipr_Sel_Rule ();
}

void
GetBsel_NLallowed ( widget )
Widget widget;
{
/***
ESC separates
***/

  FILE * Bsel;
  int i;
  int c;
  int err_msg_displayed;

  err_msg_displayed = 0;
  if ( (Bsel = fopen ( ".Bsel", "r" ) ) == NULL )
  {
    perror ( " .Bsel" );
    AbortedMsgFile ( "\".Bsel\" for reading" );
    Kill_bplatform_and_exit ( 1, 0 );
  }
 
  i = 0;
  sel_arr_tot = 0;
  c = getc( Bsel );
  while ( c!= EOF                              &&
          sel_arr_tot < sel_arr_MAX    ) {
    if ( c == 27 ) { /*** ESC ***/
      sel_str_arr [ sel_arr_tot ] [ i ] = '\0';
      sel_arr_tot++;
      i = 0;
    }
    else {
      sel_str_arr [ sel_arr_tot ] [ i ] = c;
      i++;
    }
    if ( i >= sel_str_len_MAX ) {
      if ( ! err_msg_displayed ) {
        char buf [ 100 ];
        err_msg_displayed = 1;
        DisplayCurrWinText ( "\n  String length exceeded: " );
        DisplayCurrWinText ( sel_str_arr [ sel_arr_tot ] );
        DisplayCurrWinText ( " ...\n" );
        strcpy ( buf, "Maximum selection string length exceeded (" );
        CreNumInBuf ( buf, sel_str_len_MAX - 1 );
        strcat ( buf, ")" );
        Popup_Err ( 0, buf );
      }
      while ( c != 27  && c!= EOF ) {
        c = getc( Bsel );
      }
      ungetc ( c, Bsel );
      i = sel_str_len_MAX - 1;
    }
    c = getc( Bsel );
  }
  sel_str_arr [ sel_arr_tot ] [ i ] = '\0';
  sel_arr_tot++;
  fclose ( Bsel );
  if ( sel_arr_tot >= sel_arr_MAX ) {
    char buf [ 100 ];
    DisplayCurrWinText ( "\n  Can't provide all selections found!\n" );
    strcpy ( buf, "Maximum number of selections exceeded (" );
    CreNumInBuf ( buf, sel_arr_MAX );
    strcat ( buf, ")" );
    Popup_Err ( 0, buf );
  }
}

#ifdef WWW_VERSION

Reset_WWW() {}
/*
{
  int name [ 50 ], ext, type;
  DeSensitize ();
  for ( curr_Mch_arr = 1; curr_Mch_arr <= Mch_arr_tot ; curr_Mch_arr++ ) {
    Load_SRC_CFG_Names ( curr_Mch_arr );
    val_mand ( name, &ext, &type, Mch_arr [ curr_Mch_arr ] . obj );
    if ( type == usr ) {
      if ( ext == mch || ext == ref || ext == imp ) {
        CheckUnanalyse ( 1 );
      }
      else if ( ext == doc ) {
        CheckUndoc ();
      }
      else if ( ext == bse || ext == ops || ext == enm || ext == itf ) {
        CheckUngen ();
      }
      else if ( type == bse_gen || type == enm_gen ||
                type == itf_gen || type == prf_gen || type == gen_vhdl ) {
        KillConstruct ();
      }
    }
  }
}
*/
#endif /* WWW_VERSION */

#ifdef COUNT_WWW

void
COUNTCheckIsBad ( nn )
int nn;
{

/***
printf ( "In COUNTCheckIsBad: nn %d: COUNT_25_msg %d\n", nn, COUNT_25_msg );
***/
  if ( COUNT_25_msg ) {

#ifdef WWW_VERSION

    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );
    XBell ( display, -75 );

    Reset_WWW();
    printf ( "\n\n   This B-Toolkit demonstration licence has now expired\n\n\n" );

#endif /* WWW_VERSION */

    Kill_bplatform_and_exit ( 1, 1 );
  }
  COUNT_25_msg = 1;

#ifdef COUNT_VERSION

  printf ( "\n\n   This B-Toolkit restricted licence has now expired\n\n\n" );
  DisplayCurrWinText ( "\nThis B-Toolkit restricted licence has now expired\n");

#endif /* COUNT_VERSION */

#ifdef WWW_VERSION

  strcpy ( buf, "\n  B-Toolkit error code: 1801" );
  CreNumInBuf ( buf, nn );
  strcat ( buf, "\n" );
  DisplayCurrWinText ( buf );
  printf ( "\n\n              B-Toolkit: Error code 1801%d\n", nn );

#endif /* WWW_VERSION */

  DeSensitize ();
  strcpy ( xterm_title, "B-ErrorMessage" );
  strcpy ( fifo_write_buf, "0:" );
  Cre_fifo_write_buf_cmd_0 ( BT_LST_FLG );
  if   ( ! xterm_is_up ) CreateXTerm ();
  else                   Write_FIFO ( fifo_write_buf );
}

#endif /* COUNT_WWW */

#ifdef WWW_VERSION

void
WWWConstructsCycleCheck ( nn ) {}
int nn;
/*
{
  int ii, jj, kk;
  int name [ 50 ], ext, type;
  int cc, bb, st;
  int c, i, j;
  int anl_len, pob_num, pob_len, name_found, constr_found, next_loc_found;
  FILE ? anl_file;
  FILE ? pob_file;

  if ( COUNT_25_flag ) {
    return;
  }

  valIth_flags ( &ii, Option_23 );
  valIth_flags ( &jj, Option_24 );
  valIth_flags ( &kk, Option_25 );
  ii = ( ii / 2 );
  jj = ( jj / 2 );
  kk = ( kk - ii - jj );
  kk = ( kk - 26 );


/?
  if ( ( ! nn ) && kk != ( ( kk / check_iterations ) ? check_iterations ) ) {
    return;
  }
?/

  if ( num_usr_constructs != GetNumUsrConstructs () ) {
    COUNT_25_flag = 2;
  }

  for ( i = 1; i <= Mch_arr_tot; i++ ) {
    if ( ! COUNT_25_flag ) {
      val_mand ( name, &ext, &type, Mch_arr [ i ] . obj );
      if ( type == usr ) {
        val_curMRIState ( &st, Mch_arr [ i ] . obj );
        val_anl ( &bb, st );
        if ( bb ) {                        /? analysed ?/
          strcpy ( buf, "ANL/" );
          LoadBufFullConstructName ( buf, Mch_arr [ i ] . obj );
          strcat ( buf, ".anl" );
          anl_file = fopen ( buf, "r" );
          if ( anl_file == NULL ) {
            printf ( "\n\n           BMotif: can't open %s for reading", buf );
            printf ( "\n\n                  B-Toolkit Terminated" );
            printf ( "\n\n             All data has been preserved\n\n\n" );
            Kill_bplatform_and_exit ( 1, 0 );
          }
          anl_len = 0;
          c = getc ( anl_file );
          while ( c != EOF ) {
            anl_len++;
            c = getc ( anl_file );
	  }
          fclose ( anl_file );
          pob_len = 0;
          length_pob ( &pob_num, st );
          if ( pob_num ) {                 /? pogenerated ?/
            strcpy ( buf, "POB/" );
            LoadBufFullConstructName ( buf, Mch_arr [ i ] . obj );
            strcat ( buf, ".0.po" );
            pob_file = fopen ( buf, "r" );
            pob_len = 0;
            if ( pob_file != NULL ) { /? make sure pog produces obligations! ?/
              c = getc ( pob_file );
              while ( c != EOF ) {
                pob_len++;
                c = getc ( pob_file );
	      }
              fclose ( pob_file );
	    }
	  }
/???
printf ( "loading/comparing %s anl_len %d pob_num %d pob_len %d\n", ( char ? ) name, anl_len, pob_num, pob_len );
???/
          j = 0;
          name_found = 0;
          constr_found = 0;
          while ( ! constr_found && j < max_num_usr_constr ) {
            if ( strcmp ( constr_nme [ j ], ( char ? ) name ) == 0 ) {
              name_found = 1;
              if ( constr_anl_len [ j ] == anl_len ) {
                if ( ! constr_pob_len [ j ] ) {   /? hasn't been stored yet ?/
	          constr_found = 1;
                  if ( pob_len ) {                  /? but now pog ... ?/
                    constr_pob_len [ j ] = pob_len; /? ... so store it ?/
/???
printf ( "storing pob_length %d\n", pob_len );
???/
		  }
		}
                else if ( pob_len == 0 ) {        /? not currently pog ?/
	          constr_found = 1;
		}
                else if ( constr_pob_len [ j ] == pob_len ) { /? lengths ok ?/
	          constr_found = 1;
	        }
	      }
	    }
            if ( ! constr_found ) {
              j++;
	    }
	  }
          if ( name_found ) {
/???
printf ( "name found ... " );
???/
            if ( ! constr_found ) {
/???
printf ( "and construct not found\n" );
???/
              COUNT_25_flag = 3;
	    }
/???
else { printf ( "and construct found\n" ); }
???/
	  }
          else {
/???
printf ( "name not found ... " );
???/
            j = 0;
            next_loc_found = 0;
            while ( ! next_loc_found && j < max_num_usr_constr ) {
              if ( strcmp ( constr_nme [ j ], "" ) == 0 ) {
                next_loc_found = 1;
	      }
              if ( ! next_loc_found ) {
                j++;
	      }
	    }
            if ( next_loc_found ) {
/???
printf ( "so loading in array position %d\n", j );
???/
              strcpy ( constr_nme [ j ], ( char ? ) name );
              constr_anl_len [ j ] = anl_len;
              constr_pob_len [ j ] = pob_len;
            }
/???
else { printf ( "but array full\n" ); }
???/
          }
	}
      }
    }
  }

/???
printf ( "+++++++++++++\n" );
for ( i = 0 ; i < max_num_usr_constr ; i++ ) {
  if ( constr_nme [ i ] [ 0 ] != '\0' ) {
    printf ( "|%s| %d %d\n", constr_nme [ i ], constr_anl_len [ i ], constr_pob_len [ i ] );
  }
}
printf ( "+++++++++++++\n" );
???/

  if ( COUNT_25_flag ) {
    int ii, jj, kk;
    valIth_flags ( &ii, Option_23 );
    ii = ii / 2;
    valIth_flags ( &jj, Option_24 );
    jj = ( jj / 2 );
    valIth_flags ( &kk, Option_25 );
    kk = ( Option_25_Max + ii + jj + 26 );
/???
printf ( "kk inc to max %d\n", kk );
???/
    modIth_flags ( Option_25, kk );
  }
  if ( nn != 999 ) {  /? not from main ?/
    Save_CfgDepBase ();
  }
}

int
GetNumUsrConstructs ()
{
  int i, tt, nn;
/???
printf ( "GetNumUsrConstructs: " );
???/
  nn = 0;
  for ( i = 1; i <= Mch_arr_tot; i++ ) {
    val_type ( &tt, Mch_arr [ i ] . obj );
    if ( tt == usr ) {
      nn++;
    }
  }
/???
printf ( "%d\n", nn );
???/
  return ( nn );
}
*/

#endif /* WWW_VERSION */





void
InvokeB ( XTerm_option, desensitize_flag )
int XTerm_option;
int desensitize_flag;
{
  int cmd, i, j;

  XtSetSensitive ( InterruptPullDown, True ); 
  XmUpdateDisplay ( InterruptPullDown );
  XmUpdateDisplay ( top_bar );

  if ( terminal_option ) return;

  if ( desensitize_flag ) DeSensitize ();

  
#ifdef WWW_VERSION

  WWWConstructsCycleCheck ( 0 );

#endif /* WWW_VERSION */

#ifdef COUNT_WWW

  if ( COUNT_25_flag ) {
    COUNTCheckIsBad ( COUNT_25_flag );
    return;
  }

  if ( COUNT_25_flag ) {
    COUNTCheckIsBad ( COUNT_25_flag );
    return;
  }

#endif /* COUNT_WWW */

/***
printf( "---------------------- InvokeB -----------------------\n    --->>>" );
printf ( fifo_write_buf );
printf( "<<<---\n    %d\n    Popup_Sel_flag %d  radiobox_flag %d\n---------------------------------------------------\n", strlen ( fifo_write_buf ), Popup_Sel_flag, radiobox_flag );
***/

/***
printf ( "   ================================================\n" );
fflush ( stdout );
printf ( "    InvokeB ( XTerm_option=%d desensitize_flag=%d )\n",
                                                  XTerm_option, desensitize_flag );
printf ( "      %s\n", fifo_write_buf );
fflush ( stdout );
printf ( "      IsDeSensitized=%d  xterm_is_up=%d\n",
                                                  IsDeSensitized (), xterm_is_up );
fflush ( stdout );
printf ( "   ================================================\n" );
fflush ( stdout );
***/

  if   ( XTerm_option && ( ! xterm_is_up ) ) {
    CreateXTerm ();
  }
  else {
    Process_SetInvokeBLogoFlashTimer_ini ();

    Write_FIFO ( fifo_write_buf );
  }
}  /* InvokeB */


void
ProcessB ()
{

/***
  cmd : primary_string : secondary_string : [ : additional_string ]
***/

  int cmd, i, j;

  Read_FIFO ();   /* into buf */

/***
printf ( "ProcessB - buf `%s'\n", buf );
***/

  i = 0;
  cmd = 0;
  while ( ( buf [ i ] != '@' ) && ( buf [ i ] != ' ' ) ) {
    cmd = ( 10 * cmd ) + buf [ i ] - '0';
    i++;
  }

  while ( buf [ i ] == ' ' ) { i++; }

  /***
  primary string
  ***/
  i++;
  j = 0;
  while ( ( j < primary_string_len - 1 ) &&
          ( buf [ i ] != '@' )              ) {
   if ( buf [ i ] != '|' ) {
      primary_string [ j ] = buf [ i ];
    }
    else {
      primary_string [ j ] = '\n';
    }
    i++;
    j++;
  }
  i++;
  primary_string [ j ] = '\0';

  /***
  secondary string
  ***/
  j = 0;
  while ( j < primary_string_len - 1 &&
          buf [ i ] != '@'        &&
          buf [ i ] != '\n'       &&
          buf [ i ] != '\0'           ) {
    if ( buf [ i ] != '|' ) {
      secondary_string [ j ] = buf [ i ];
    }
    else {
      secondary_string [ j ] = '\n';
    }
    i++;
    j++;
  }
  secondary_string [ j ] = '\0';

  /***
  check for additional string
  ***/
  j = 0;
  if ( buf [ i ] == '@' ) {
    i++;
    while ( j < primary_string_len - 1 &&
            buf [ i ] != '\0'           ) {
      additional_string [ j ] = buf [ i ];
      i++;
      j++;
    }
  }
  additional_string [ j ] = '\0';

/***
printf( "                    +---------------+-------------+-------------+\n" );
printf( "                    ProcessB %d\n",cmd);
printf( "                        primary_string `" );
printf(primary_string); fflush ( stdout );
printf( "'\n                        secondary_string `" );
printf(secondary_string); fflush ( stdout );
printf( "'\n                        additional_string `" );
printf(additional_string);
printf( "'\n                    +---------------+-------------+-------------+\n" );
fflush ( stdout );
***/

  if ( ( cmd == BT_INI_M )             &&
       ( from_option == from_new_dir )    ) {
    cmd = BT_NEW_DIR_M;
  }

  switch ( cmd ) {
    case BT_TEXT_M:
      rewrite_prompt = 1;
      ProcessAndDisplayCurrWinText ( primary_string );
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_NOOP );
      InvokeB ( without_XTerm, 0 );
      break;

    case BT_TEXT_FROM_BCOM_M:
      rewrite_prompt = 1;
      ProcessAndDisplayCurrWinTextBcom ();
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_NOOP );
      InvokeB ( without_XTerm, 0 );
      break;

    case BT_PARSE_M:
      break;

    case BT_ENV_M:
      strcpy ( fifo_write_buf, "0:" );
      CreNumInBuf ( fifo_write_buf, BT_ENV );
      Cre_tcp_env ();
      InvokeB ( without_XTerm, 0 );
      break;

    case BT_CIO_RMK_M:
      {
        char name [ 50 ];
        int ext, obj;

        GetNameFromString ( name, primary_string );
        GetExtNumFromString ( &ext, primary_string );
        GetObjFromNameExt ( &obj, name, ext );
        Load_SRC_CFG_Names ( obj );
        LoadBcjm ();
        Pre_Itf ( obj );
      }
      break;

    case BT_TRL_M:
      {
        char name [ 50 ];
        int ext, obj;

        GetNameFromString ( name, primary_string );
        GetExtNumFromString ( &ext, primary_string );
        GetObjFromNameExt ( &obj, name, ext );
        Load_SRC_CFG_Names ( obj );
        LoadBcjm ();
        Pre_Trl ( obj );
      }
      break;

    case BT_LNK_M:
      {
        char name [ 50 ];
        int st, bb, ext, obj;

        GetNameFromString ( name, primary_string );
        GetExtNumFromString ( &ext, primary_string );
        GetObjFromNameExt ( &obj, name, ext );
        LoadBcjm ();
        val_curMRIState ( &st, obj );
        val_trl ( &bb, st );
        if ( bb ) {
          Load_SRC_CFG_Names ( obj );
          Pre_Lnk ( obj );
	}
        else {
          strcpy ( fifo_write_buf, "0:" );
          Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
          sprintf ( buf, "\n  Linker: %s is not translated\n", GetName ( obj ) );
          DisplayCurrWinText ( buf );
          InvokeB ( without_XTerm, 0 );
	}
      }
      break;

    case BT_PFP_M:
      {
        char name [ 50 ];
        int ext, obj;
        int st, su, len_pob, nn, pp, qq, btl_prf, c_tot, p_tot, p_pob, c_pob;
/***
printf ( "BT_PFP_M\n" );
printf ( "  primary_string %s\n", primary_string );
printf ( "  secondary_string %s\n", secondary_string );
printf ( "  additional_string %s\n", additional_string );
***/
        GetNameFromString ( name, primary_string );
        GetExtNumFromString ( &ext, primary_string );
        GetObjFromNameExt ( &obj, name, ext );
        Load_SRC_CFG_Names ( obj );
        CreNumFromBuf ( &nn, secondary_string );
        val_curMRIState ( &st, obj );
        val_cptMRIState ( &su, obj );
        length_pob ( &len_pob, st );
/***
printf ( "  nn=%d len_pob=%d (if nn<len_pob autoproof exists)\n", nn, len_pob );
***/
        if ( nn < len_pob ) {  /* autoproof exists */
/***
printf ( "    so autoproof exists\n" );
***/
          sprintf ( fifo_write_buf, "(%s|%s|", GetName ( obj ), secondary_string );
          CreNumFromBuf ( &nn, secondary_string );
/***
printf ( "    now nn=%d\n", nn );
***/
          LoadBcjm ();
          btl_prf = 0;
          if ( ! nn ) {
            valIth_pob ( &pp, st, 1 );
            pp = correct_pob_for_btl ( pp );
            CreNumInBuf ( fifo_write_buf, pp );
	  }
          else {
            valIth_pob( &c_tot, su, nn + 1 );
            valIth_pob( &p_tot, su, nn );
            valIth_pob( &c_pob, st, nn + 1 );
            valIth_pob( &p_pob, st, nn );
            btl_prf = ( ( c_tot < 0 ) != 0 );
            c_tot = correct_pob_for_btl ( c_tot );
            p_tot = correct_pob_for_btl ( p_tot );
            c_pob = correct_pob_for_btl ( c_pob );
            p_pob = correct_pob_for_btl ( p_pob );
            CreNumInBuf ( fifo_write_buf,  c_tot-p_tot+p_pob-c_pob );
	  }
          strcat ( fifo_write_buf, "):" );
          if   ( btl_prf ) CreNumInBuf ( fifo_write_buf, BT_PFP_WITH_ENV_BTL );
          else             CreNumInBuf ( fifo_write_buf, BT_PFP_WITH_ENV );
          Cre_tcp_env ();
/***
printf ( "    fifo_write_buf=%s\n", fifo_write_buf );
***/
	}
        else {              /* autoproof not exist */
/***
printf ( "    so autoproof not exist\n" );
***/
          sprintf ( fifo_write_buf, "(%s|%s|",
                                        GetName ( obj ), secondary_string );
          CreNumFromBuf ( &nn, secondary_string );
/***
printf ( "    now nn=%d\n", nn );
***/
          LoadBcjm ();
          CreNumInBuf ( fifo_write_buf, 999999 );
          strcat ( fifo_write_buf, "):" );
          CreNumInBuf ( fifo_write_buf, BT_PFP_WITH_ENV );
/***
printf ( "    fifo_write_buf=%s\n", fifo_write_buf );
***/
          Cre_tcp_env ();
	}  
/***
printf("%s\n",fifo_write_buf);
***/
        InvokeB ( without_XTerm, 0 );
      }
      break;

    case BT_PNP_BTL_M:
      {
        char name [ 50 ];
        int i, n, cur_mch, ext, level, obj;
/***
printf ( "BT_PNP_BTL_M\n" );
printf ( "  primary_string %s\n", primary_string );
printf ( "  secondary_string %s\n", secondary_string );
printf ( "  additional_string %s\n", additional_string );
***/
        i = 0;
        while ( primary_string [ i ] != '.' ) {
          name [ i ] = primary_string [ i ];
          i++;
	}
        name [ i ] = '\0';
        i++;
        ext = primary_string [ i ] - '0';
        i++;
        i++;
        level = 0;
        while ( primary_string [ i ] != '\0' ) {
          level = ( ( 10 * level ) + primary_string [ i ] - '0' );
          i++;
	}
        i = 0;
        while ( secondary_string [ i ] != '.' ) {
          primary_string [ i ] = secondary_string [ i ];
          i++;
	}
        primary_string [ i ] = '\0';
        strcpy ( additional_string, primary_string );
        i++;
        n = 0;
        while ( secondary_string [ i ] != '\0' ) {
          n = ( ( 10 * n ) + secondary_string [ i ] - '0' );
          i++;
        }
        GetObjFromNameExt ( &obj, name, ext );
        load_toolkit15_po_dot_src ( 0 ); /* BT_PNP_BTL_M - no dots! */
        if ( RestoreRecordedProofs ( obj, level, 0 ) ) {
          btl_proofprint ( additional_string, n );
          strcpy ( fifo_write_buf, "0:" );
          Cre_fifo_write_buf_cmd_0 ( BT_NOOP );
          InvokeB ( without_XTerm, 0 );
	}
        else {
          Popup_Err ( 0, "  Unable to complete current job " );
          TopBar_Interrupt_CB ();
/*
          strcpy ( fifo_write_buf, "0:" );
          Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
          InvokeB ( with_XTerm, 0 );
*/
	}
      }
      break;

    case BT_BTL_RLD_M:
      {
        void ReturnFromReloadPMD ();
        ReturnFromReloadPMD ( primary_string [ 0 ] - '0' );
      }
      break;

    case BT_DMU_M:
      {
        char name [ 50 ];
        int ext, nn, obj, st, bb;

        GetNameFromString ( name, primary_string );
        GetExtNumFromString ( &ext, primary_string );
        GetObjFromNameExt ( &obj, name, ext );
        CreNumFromBuf ( &nn, secondary_string );
        Load_SRC_CFG_Names ( obj );
        LoadBcjm ();
/***
printf("looking at %s, level %d\n", GetName ( obj ), nn );
***/
        val_curMRIState ( &st, obj );
/***
printf("looking at current state %d\n",st);
***/
        switch ( ext ) {
        case mch:
          GetPrfObjFromNameExtLvl ( &obj, name, mch_prf, nn - 1, 0 );
          break;
        case ref:
          GetPrfObjFromNameExtLvl ( &obj, name, ref_prf, nn - 1, 0 );
          break;
        case imp:
          GetPrfObjFromNameExtLvl ( &obj, name, imp_prf, nn - 1, 0 );
          break;
        }
        if ( obj ) {
          Cre_fifo_write_buf_cmd_env ( obj, BT_DMU_WITH_ENV, 0 );
/***
printf ( "BT_DMU_M:\n  %s\n", fifo_write_buf );
***/
	}
        else {
          strcpy ( fifo_write_buf, "0:" );
          Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
/***
printf ( "Should have been BT_DMU_M:\n  %s\n", fifo_write_buf );
***/
	}
        InvokeB ( without_XTerm, 0 );
      }
      break;

    case BT_INTERIM_COMP_JOBS_M:
/***
printf ( "\n\n\t\t\tBT_INTERIM_COMP_JOBS_M\n" );
***/
      LoadBcjm ();
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
      InvokeB ( without_XTerm, 0 );
      break;

    case BT_REC_LISTS_M:
      LoadBSelRecLists ();
      Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
      InvokeB ( without_XTerm, 0 );
      break;

    case BT_XTM_BGD_M:
      Process_SetInvokeBLogoFlashTimer_ini ();
/***
printf ( "about to Write_FIFO (%s)\n", fifo_write_buf );
***/
      Write_FIFO ( fifo_write_buf );
      break;

    case BT_DSP_FILE_M:
      LoadFileIntoBuf ( primary_string, secondary_string, primary_string_len );
      if ( secondary_string [ 0 ] != '\0' ) {
        DisplayCurrWinText ( "\n" );
        DisplayCurrWinText ( "\n" );
        DisplayCurrWinText ( secondary_string );
        DisplayCurrWinText ( "\n" );
      }
      unlink ( primary_string );
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
      InvokeB ( without_XTerm, 0 );
      break;

    case BT_IPR_HYP_M:
      DisplayIprHyp ();
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
      InvokeB ( without_XTerm, 0 );
      break;

    case BT_IPR_THY_M:
      {
        int i, j, l;
        l = strlen ( primary_string );
        if ( ( primary_string [ 0 ] == '(' ) &&
             ( primary_string [ l - 1 ] == ')' )    ) {
          for ( i = 1 ; i < l - 1 ; i++ ) {
            primary_string [ i - 1 ] = primary_string [ i ];
	  }
          primary_string [ l - 2 ] = '\0';
	}
        sel_arr_tot = 0;
        i = 0;
        while ( primary_string [ i ] != '\0' ) {
          j = 0;
          while ( ( primary_string [ i ] != '\0' ) &&
                  ( primary_string [ i ] != ';' )    ) {
            sel_str_arr [ sel_arr_tot ] [ j ] = primary_string [ i ];
            i++;
            j++;
	  }
          sel_str_arr [ sel_arr_tot ] [ j ] = '\0';
          sel_arr_tot++;
          if ( primary_string [ i ] == ';' ) i++;
	}
        Ipr_Sel_Thy ();
      }
      break;

    case BT_IPR_RUL_M:
      {
        int i, l;
        l = strlen ( primary_string );
        if ( ( primary_string [ 0 ] == '(' ) &&
             ( primary_string [ l - 1 ] == ')' )    ) {
          for ( i = 1 ; i < l - 1 ; i++ ) {
            primary_string [ i - 1 ] = primary_string [ i ];
	  }
          primary_string [ l - 2 ] = '\0';
	}
        ProcessInterProverRuleSelection ();
      }
      break;


    case BT_IPR_RUL_RANGE_M:
      ProcessInterProverRuleRange ();
      break;

  case BT_INP_ASK_FINI_M:                   /* ask commit proofs */
      {
        if ( bell_option ) {
         XBell ( display, -75 );
         XBell ( display, -75 );
        }
        Popup_CommitIprProofs ( top_level );
      }
      break;

    case BT_PROB_BINARY_M:
      XBell ( display, -75 );
      XBell ( display, -75 );
      Popup_Err ( BT_MINOR_ERR_M, "Problem with Toolkit Binary" );
      process_XTerm_IfReq ();
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
      InvokeB ( with_XTerm, 0 );
      break;

    case BT_CURR_ENV_M:                     /* Toolkit1 - no more jobs */
      { 
        int obj, nm [ 50 ];
/***
printf ( "BT_CURR_ENV_M\n" );
***/
        if ( translating_pre_MInterface ) {
/***
printf ( "translating_pre_MInterface\n" );
***/
          LoadBcjm ();
          get_topabs ( &obj, translating_pre_MInterface );
          xtr_name( nm, obj );
          GetObjFromNameExt ( &obj, nm, itf );
          Load_SRC_CFG_Names ( obj );
          Pre_Itf ( obj );
	}
        else if ( ITF_Intro_basic_io ) {
/***
printf ( "ITF_Intro_basic_io\n" );
***/
          ITF_Intro_basic_io = 0;
          ITF ( ITF_Intro_basic_io_obj, ITF_Intro_basic_io_ps );
	}
        else {
/***
printf ( "! translating_pre_MInterface\n" );
***/
          if ( bell_option ) {
           XBell ( display, -75 );
           XBell ( display, -75 );
          }

          switch ( curr_env ) {
          case anm_env:
            DisplayNewEnv ( main_env );
            break;
          case ipr_pob_env:
          case ipr_lem_env:
          case btl_env:
            DisplayNewEnv ( provers_env );
            break;
          default:
            LoadBcjm ();
            DisplayCurrentEnv ();
            break;
	  }  /* switch ( curr_env ) */

          process_XTerm_IfReq ();

          if ( auto_reset_and_remake && ( ! upgrade3T04_flag ) ){
            Save_n_CfgDepBase ();
            AutoRemakeFini ();
            strcpy ( fifo_write_buf, "0:" );
            Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
            InvokeB ( without_XTerm, 0 );
	  }

#ifdef BOOSTER_VERSION
	  if ( BOOSTER_link ) {
            int st, bb;
	    val_curMRIState( &st, BOOSTER_link );
            val_lnk( &bb, st );
            if ( ! bb ) { /* not linked */
	      val_cptMRIState( &st, BOOSTER_link );
              val_lnk( &bb, st );
              if ( ! bb ) { /* never been linked */
                DisplayCurrWinText ( "\n  If linking a BOOSTER Minimal Administrator System for the\n  first time, you need to re-run Generate and re-link\n" );
	      }
              else {
                DisplayCurrWinText ( "\n  If linking a BOOSTER System, try\n  re-running Generate and re-linking\n" );
	      }
	    }
            BOOSTER_link = 0;
 	  }
#endif /* BOOSTER_VERSION */

	}
      }
      break;

   case BT_MINI_RMK_M:
      {
        int ext, cc, obj;
        int name [ 50 ];

        GetExtNumFromString ( &ext, primary_string );
        GetNameFromString ( name, primary_string );
        GetObjFromNameExt ( &obj, name, ext );
        curr_obj = obj;
        Load_SRC_CFG_Names ( obj );
        LoadBcjm ();
        process_XTerm_IfReq ();
        if ( auto_reset_and_remake && ( ! upgrade3T04_flag ) ) {
          Save_n_CfgDepBase ();
          AutoRemakeFini ();
          strcpy ( fifo_write_buf, "0:" );
          Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
          InvokeB ( without_XTerm, 0 );
          return;
        }
        Popup_MiniRemake ( top_level );
        if ( auto_reset_and_remake && ( ! upgrade3T04_flag ) ) {
          Save_n_CfgDepBase ();
          AutoRemakeFini ();
          strcpy ( fifo_write_buf, "0:" );
          Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
          InvokeB ( without_XTerm, 0 );
	}
        else {
          if ( IsClosed ( obj ) ) {
            PreOpenConstruct ( obj );
	  }
	}
      }
      break;

    case BT_XTERM_REQD_M:
      dont_destroy_display = 1;
      strcpy ( xterm_title, primary_string );
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
      InvokeB ( with_XTerm, 0 );
      break;

    case BT_CRE_SLIB_M:
      Popup_creSLIB ( top_level );
      break;

    case BT_CRE_SLIB_FINI_M:
      Popup_creSLIB_FINI ( top_level );
      break;

    case BT_CRE_SLIB_INI_M:
      Popup_creSLIB_INI ( top_level );
      break;

    case BT_POB_RHL_M:
      Ipr ( BT_POB_RHL_M );
      break;

    case BT_POB_RH__M:
      Ipr ( BT_POB_RH__M );
      break;

    case BT_POB_R_L_M:
      Ipr ( BT_POB_R_L_M );
      break;

    case BT_POB_R___M:
      Ipr ( BT_POB_R___M );
      break;

    case BT_LEM_RHR_M:
      Ipr ( BT_LEM_RHR_M );
      break;

    case BT_LEM_R_R_M:
      Ipr ( BT_LEM_R_R_M );
      break;

    case BT_LEM_RHR_NOT_PARSE_M:
      {
        int bb;
        sprintf ( buf, "PMD/%s.pmd", GetName ( curr_obj ) );
        bb = ( FileParses ( buf ) );
        Ipr ( BT_LEM_R_R_M );
      }
      break;

    case BT_LEM__HR_M:
      Ipr ( BT_LEM__HR_M );
      break;

    case BT_LEM___R_M:
      Ipr ( BT_LEM___R_M );
      break;

  case BT_LEM____RLD_FAIL_M:
      if ( curr_env == ipr_pob_env ) {             /* initially, pmd does not load */
        strcpy ( fifo_write_buf, "(?,999):" );      /* ProveLemma_skip_Option */
        Cre_fifo_write_buf_cmd_0 ( BT_BSEL );
        InvokeB ( without_XTerm, 0 );
      }
      else {                                                /* mid-lemma proof */
        OpenCurrentPMD ( curr_obj );
      }
      break;

    case BT_ANM_MULTI_INP_M:
      Cre_Anm_Multi_Input_Form ( primary_string [ 0 ] - '0' );
      break;

    case BT_ANM_OK_CONT_M:
      /*      SetSensitiveEnvLabelBut ( True ); */
      strcpy ( primary_string, "  Continue  " );
      Popup_InformationDialog ( top_level );
      break;

    case BT_INFO_DONT_WAIT_M:
      /*      SetSensitiveEnvLabelBut ( True ); */
      Popup_DontWait_InformationDialog ( top_level );
      break;

    case BT_ANM_PRCD_M:
      Animate ( BT_ANM_PRCD_M );
      break;

    case BT_ANM_PRCD_FALSE_M:
      Animate ( BT_ANM_PRCD_FALSE_M );
      break;

    case BT_ANM_DISP_OP_M:
      Animate ( BT_ANM_DISP_OP_M );
      break;

    case BT_ANM_DSP_1_M:
      Animate ( BT_ANM_DSP_1_M );
      break;

    case BT_ANM_DSP_2_M:
      Animate ( BT_ANM_DSP_2_M );
      break;

    case BT_ANM_DSP_3_M:
      Animate ( BT_ANM_DSP_3_M );
      break;

    case BT_MULTI_ERR_STR_M:
      primary_string [ 248  ] = '\0';
      strcpy ( multi_err_str, primary_string );
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
      InvokeB ( without_XTerm, 0 );
      break;

    case BT_ANM_GET_EXE_STEP_M:
      Animate_ExecutableStep ( top_level );
      break;

    case BT_ANM_GET_OP_M:
      anm_ops_option = 1;
      Animate_Ops ( top_level );
      break;

    case BT_ANM_UTILS_M:
      {
        void Animate_Utilities ();
        anm_ops_option = 1;
        Animate_Utilities ( top_level );
      }
      break;

/*
    case BT_EDT_ANM_THY_M:
      {
        FILE * Bed;
        int c;

        Retrieve_String ( editor_str_num, str_buf );
        sprintf ( fifo_write_buf, "%s SRC/%s.thy & \n echo $! > TMP/.Bed",
                                                    str_buf, GetName ( curr_obj ) );
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
      break;
*/

    case BT_EDT_ANM_THY_M:
      LoadAllAnmThyFilesInto_sel_strs ();
      if ( sel_arr_tot ) {
        Popup_Sel_flag = edit_anm_thy_sel;
        Popup_SelOne_Dialog ( top_level, "Theory file to edit" );
      }
      else {
        void Animate_Utilities ();
        Animate_Utilities ( top_level );
        Popup_Minor_Err ( top_level, "  No Theory files to edit  " );
      }
      break;


    case BT_CMT_NOT_PARSE_M:
/*
      Popup_CmtNotParse ( top_level );
*/
      Popup_Minor_Err ( top_level, "Can't introduce a construct that does not parse!" );


          strcpy ( fifo_write_buf, "0:" );
          Cre_fifo_write_buf_cmd_0 ( BT_SKIP );
          InvokeB ( without_XTerm, 0 );


      break;

    case BT_PROMPT_CFM_M:
      confirm_flag = 0;
      Popup_ConfirmDialog ( top_level );
      break;

    case BT_GET_STRING_M:
      Popup_PromptDialog ( top_level );
      break;

    case BT_GET_LIST_M:
      Popup_Sel_Dialog ( top_level, primary_string );
      break;

    case BT_GET_ONE_M:
      Popup_SelOne_Dialog ( top_level, primary_string );
      break;

    case BT_GET_L_ONE_M:
      Popup_SelLargeOne_Dialog ( top_level, primary_string );
      break;

    case BT_GET_CHOICE_M:
      Popup_SelChoice_Dialog ( top_level, "Choose Branch", 0 );
      break;

    case BT_EDT_PROCD_M:
      Popup_Edt_Proceed ( top_level );
      break;

    case BT_ERR_M:
      Error_From_B ( top_level );
      break;

    case BT_MINOR_ERR_M:
      Popup_Err ( BT_MINOR_ERR_M, primary_string );
      break;

    case BT_RMV_EDT_M:
      Popup_RemoveEditedFile ( top_level );
      break;

    case BT_BCOM_PARSE_M:
      {
        int i, c;
        FILE * Bcom;
        /***
        load new_dir from .BBBcom into buf
        ***/
        Bcom = fopen ( ".BBBcom", "r" );
        if ( Bcom == NULL ) {
          AbortedMsgFile ( "\"%s\" for reading", ".BBBcom" );
          BT_err_exit ( 0 );
          return;
        }
        i = 0;
        c = getc ( Bcom );
        while ( ( c != EOF ) && ( c != '\n' ) ) {
          buf [ i ] = ( char ) c;
          i++;
          c = getc ( Bcom );
        }
        fclose ( Bcom );
        buf [ i ] = '\0';

        if ( strcmp ( primary_string, "0" ) == 0 ) {
          int ok  = 0;
          sprintf ( additional_string, "%s/.Bpdan", buf );
          if ( stat ( additional_string, &stat_buf ) != -1 ) ok = 1;
          if ( ! ok ) {
            sprintf ( additional_string, "%s/.Bpda", buf );
            if ( stat ( additional_string, &stat_buf ) != -1 ) ok = 1;
          }
          if ( ok ) {
            ChangeDirectoryExistingDir ( buf );
	  }
          else {
            strcpy ( secondary_string, "The current development has been saved" );
            sprintf ( primary_string, " Create new development in %s? ", buf );
            radiobox_flag = new_dev_dir_radiobox;
            confirm_flag = radiobox_flag;
            Popup_ConfirmDialog ( top_level );
	  }
        }
        else {
          Popup_Info ( " Can't create new development directory " );
          DisplayCurrWinText ( "\n\n    Bad directory:\n\n        " );
          printf ( "\n\n    Bad directory:\n\n        " );
          DisplayCurrWinText ( buf );
          puts ( buf );
          strcat ( buf, "\n\n    It does not conform to a B-formula!\n\n       One or more of the directory names is not an\n       `arity 1' symbol - see $BKIT/BHELP/BPlatform.html\n\n    Can't create BToolkit development directory\n\n\n" );
          DisplayCurrWinText(buf);
          puts ( buf );
          check_started_from_cd ( "" );
          DisplayCurrentEnv ();
	}
      }
      break;

    case BT_NEW_DIR_M:
      {
        struct stat stat_buf;
        FILE * Bcjm;
        FILE * Bpim;
        FILE * Bmvr;
/***
printf ( "Motif : BT_NEW_DIR_M\n" );
***/
        /***
        write Bpim
        ***/
        Bpim = fopen ( ".Bpim", "w" );
        if ( Bpim == NULL ) {
          printf ( "\n  BMotif: can't open .Bpim for writing\n" );
          BT_err_exit ( 0 );
          return;
        }
        PrintNum ( Bpim, pid );
        fclose ( Bpim );

        /***
        empty .Bcjm
        ***/
        Bcjm = fopen ( ".Bcjm", "w" );
        if ( Bcjm == NULL ) {
          printf( "\n  BMotif: can't open .Bcjm for writing\n" );
          BT_err_exit ( 0 );
          return;
        }
        fclose ( Bcjm );

        /***
        write .Bmvr
        ***/
        Bmvr = fopen ( ".Bmvr", "w" );
        if ( Bmvr == NULL ) {
          printf( "\n  BMotif: can't open .Bmvr for writing\n" );
          BT_err_exit ( 0 );
          return;
        }
        fprintf ( Bmvr, "%s\n", toolkit_ver ); 
        fclose ( Bmvr );

        sprintf ( fifo_write_buf, "%s/.Bpdan", cur_dir );
        if ( stat ( fifo_write_buf, &stat_buf ) != -1 )
          main_continue ( 1, 1 );
        else
          main_continue ( 0, 1 );
      }
      break;

    case BT_QUIT_M:
      process_XTerm_IfReq ();
      {
        int i;
        int nn;
        i = 0;
        nn = 0;
        while ( secondary_string [ i ] != '\0' ) {
          nn = ( ( nn * 10 ) + secondary_string [ i ] - '0' );
          i++;
	}
/***
printf ( "nn: %d nn+563: %d\n", nn, nn + 563 ); fflush ( stdout );
***/
        if ( nn < 1838 ) {
          printf ( "\n                 B-Toolkit Terminated\n\n\n" );
	}
        else {
          XBell ( display, -75 );
          XBell ( display, -75 );
          XBell ( display, -75 );
          XBell ( display, -75 );

/*
          Save_n_CfgDepBase ();
*/
          AbortedMsgCode ( nn + 563 );

          if ( auto_reset_and_remake && ( ! upgrade3T04_flag ) ) AutoRemakeFini ();
          unlink ( pid_id_file );
          exit ( 1 );
	}  /* else ( if ( nn < 1838 ) ) */
      }
      
      unlink ( pid_id_file );
      unlink ( ".Bpim" );

      if ( auto_reset_and_remake  && ( ! upgrade3T04_flag )) AutoRemakeFini ();
      exit ( 0 );
      break;

    case BT_RECT_FAULT_M:
      process_XTerm_IfReq ();
      if ( auto_reset_and_remake && ( ! upgrade3T04_flag ) ) {
        Save_n_CfgDepBase ();
        AutoRemakeFini ();
        strcpy ( fifo_write_buf, "0:" );
        Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
        InvokeB ( without_XTerm, 0 );
      }
      else {
        Popup_Err ( BT_RECT_FAULT_M, "Restart - data has been preserved" );
      }
      break;

    case BT_INTERRUPT_M:
      break;

    case BT_INI_M:
      if ( strcmp ( primary_string, "1" ) != 0 ) { /* pwd doesn't parse */
        strcpy ( buf, "\n\n    Bad directory:\n\n        " );
        strcat ( buf, cur_dir );
        strcat ( buf, "\n\n    It does not conform to a B-formula!\n\n       One or more of the directory names is not an\n       `arity 1' symbol - see $BKIT/BHELP/BPlatform.html\n\n    Can't create BToolkit development directory\n\n\n" );
        DisplayCurrWinText(buf);
        puts ( buf );

        unlink ( pid_id_file );
        exit ( 1 );
      }
      else {
        go_flag = 1;
      }
      break;

    case BT_PMD_INCL_M:
      {
        int i = 0;
        int empty = 1;
        Retrieve_String ( provers_str_num, buf );
        while ( i < ( int ) strlen ( buf ) && empty ) {
          if ( buf [ i ] != ' ' ) empty = 0;
          i++;
	}
        if ( empty ) buf [ 0 ] = '\0';
        sprintf ( fifo_write_buf, "\"%s\":%d:0", buf, BT_BSEL );
        InvokeB ( without_XTerm, 0 );
      }
      break;

  case BT_BITSTR2SET_M:
    /***
      "01110100" -> {7|->1,6|->1,5|->1,4|->1,3|->0,2|->1,1|->0,0|->0}
    ***/
      {
        int i = 0;
        int j = strlen ( primary_string );
        char mini_buf [ 50 ];
        strcpy ( buf, "{" );
        while ( primary_string [ i ] != '\0' ) {
          j--;
          if ( i ) 
            sprintf ( mini_buf, ",%d|->'%d'", j, primary_string [ i ] - '0' );
          else
            sprintf ( mini_buf, "%d|->'%d'", j, primary_string [ i ] - '0' );
          strcat( buf, mini_buf );
          i++;
        }
        strcat ( buf, "}" );
/***
printf ( "BT_BITSTR2SET_M - |%s| |%s|\n", primary_string, buf );
***/
        sprintf ( fifo_write_buf, "%s:%d:0", buf, BT_BSEL );
        InvokeB ( without_XTerm, 0 );
      }
      break;

    /***
      returns 1 if BITSTRING, else 0
    ***/
  case BT_POSTFIX_M:
    /***
    returns: AAA_BBB_KKK as ("AAA_BBB","_KKK")
             AAABBBKKK_  as ("AAABBB","_")
             AAABBBKKK   as ("AAABBBKKK","")
    ***/
      {
        int i = 0;
        int j = 0;
        int k;
        while ( primary_string [ i ] != '\0' ) {
          if ( primary_string [ i ] == '_' ) j = i;
          i++;
	}
        if ( j ) {
          strcpy ( buf, "(\"" );
          k = 2;
          i = 0;
          while ( i != j ) {
            buf [ k ] = primary_string [ i ];
            i++;
            k++;
	  }
          buf [ k++ ] = '\"';
          buf [ k++ ] = ',';
          buf [ k++ ] = '\"';
          while ( primary_string [ i ] != '\0' ) {
            buf [ k ] = primary_string [ i ];
            i++;
            k++;
	  }
          buf [ k ] = '\"';
          buf [ k + 1 ] = ')';
          buf [ k + 2 ] = '\0';
	}
        else {
          sprintf ( buf, "(\"%s\",\"\")", primary_string );
	}
        sprintf ( fifo_write_buf, "%s:%d:0", buf, BT_BSEL );
/***
printf ( "BT_POSTFIX_M - |%s| |%s|\n", primary_string, buf );
***/
        InvokeB ( without_XTerm, 0 );
      }
      break;

  case BT_ADD_UND_M:
    /***
    AAA  --> AAA_
    ***/
      sprintf ( fifo_write_buf, "%s_:%d:0", primary_string, BT_BSEL );
      InvokeB ( without_XTerm, 0 );
      break;

  case BT_SPLIT_AT_FIRST_UND_M:
    /***
    xxxx_AAA_BBB_CCC  --> XXXX|AAA_BBB_CCC
    xxxx              --> xxxx
    ***/
      {
        int i = 0;
        int j = 0;
        while ( ( primary_string [ i ] != '_' )  &&
	        ( primary_string [ i ] != '\0' )    ) { i++; }
        if ( primary_string [ i ] == '_' ) {
          primary_string [ i ] = '\0';
          i++;
	}
        while ( primary_string [ i ] != '\0' ) {
          buf [ j ] =  primary_string [ i ];
          j++;
          i++;
	}
        buf [ j ] ='\0';
        if ( buf [ 0 ] == '\0' ) {
          sprintf ( fifo_write_buf, "\"%s\":%d:0", primary_string, BT_BSEL );
	}
        else {
          sprintf ( fifo_write_buf, "(\"%s\"|\"%s\"):%d:0", primary_string, buf, BT_BSEL );
	}
        InvokeB ( without_XTerm, 0 );
      }
      break;

  case BT_SPLIT_AT_SECOND_UND_M:
    /***
    xxxx_AAA_BBB_CCC  --> XXXX_AAA|BBB_CCC
    xxxx_AAA          --> xxxx_AAA
    ***/
/***
printf ( "BT_SPLIT_AT_SECOND_UND_M - |%s|", primary_string );
***/
      {
        int i = 0;
        int j = 0;
        while ( ( primary_string [ i ] != '_' )  &&
	        ( primary_string [ i ] != '\0' )    ) { i++; }
        if ( primary_string [ i ] == '_' ) {
          i++;
          while ( ( primary_string [ i ] != '_' )  &&
	          ( primary_string [ i ] != '\0' )    ) { i++; }
          if ( primary_string [ i ] == '_' ) {
            primary_string [ i ] = '\0';
            i++;
	  }
          while ( primary_string [ i ] != '\0' ) {
            buf [ j ] =  primary_string [ i ];
            j++;
            i++;
	  }
	}
        buf [ j ] ='\0';
        if ( buf [ 0 ] == '\0' )
          sprintf ( fifo_write_buf, "\"%s\":%d:0", primary_string, BT_BSEL );
        else
          sprintf ( fifo_write_buf, "(\"%s\"|\"%s\"):%d:0", primary_string, buf, BT_BSEL );
/***
printf ( "|%s|\n", fifo_write_buf );
***/
        InvokeB ( without_XTerm, 0 );
      }
      break;

  case BT_BCATL_M:
    /***
    removes , and " and returns as string
    ***/
      {
        int i = 1;
        int c;
        FILE * Bcom;
        Bcom = fopen ( ".Bcom", "r" );
        if ( Bcom == NULL ) {
          strcpy ( primary_string, "\"" );
          strcat ( primary_string, ".Bcom" );
          strcat ( primary_string, "\" for reading" );
          AbortedMsgFile ( primary_string );
          Kill_bplatform_and_exit ( 1, 0 );
        }
        buf [ 0 ] = '\"';
        c = getc ( Bcom );
        while ( c != EOF ) {
          if ( c != '\"' && c != ' ') {
            buf [ i ] =  ( char ) c;
            i++;
	  }

	  /*
          else if ( c == '.' ) {
            c = getc ( Bcom );
            if ( c != '|' ) {
              buf [ i ] =  '.';
              i++;
              if ( c != EOF ) {
                if ( c != '\"' ) {
                  buf [ i ] =  ( char ) c;
                  i++;
                }
	      }
	    }
	  }
	  */

          else if ( c == ' ' ) {
            c = getc ( Bcom );
            if ( c == '.' ) {
              c = getc ( Bcom );
              if ( c == '|' ) {
                c = getc ( Bcom );
                if ( c != ' ' ) {
                  buf [ i++ ] =  ' ';
                  buf [ i++ ] =  '.';
                  buf [ i++ ] =  '|';
                  if ( c != EOF ) {
                    if ( c != '\"' ) {
                      buf [ i++ ] =  ( char ) c;
		    }
		  }
		}
	      }
              else { /* c != '|' */
                buf [ i++ ] =  ' ';
                buf [ i++ ] =  '.';
                if ( c != EOF ) {
                  if ( c != '\"' ) {
                    buf [ i++ ] =  ( char ) c;
		  }
		}
	      }
	    }
            else {  /* c != '.' */
              buf [ i++ ] =  ' ';
              if ( c != EOF ) {
                if ( c != '\"' ) {
                  buf [ i++ ] =  ( char ) c;
		}
	      }
	    }
	  }
          if ( c != EOF ) c = getc ( Bcom );
	}
        fclose ( Bcom );
        buf [ i ] =  '\"';
        buf [ i + 1 ] =  '\0';
        sprintf ( fifo_write_buf, "(%s):%d:0", buf, BT_BSEL );
/***
printf ( "BT_BCATL_M - start\n-----\n" );
system ( "cat .Bcom" );
printf ( "\n-----\n|%s|\n-----\nBT_BCATL_M - end\n", buf );
***/
        InvokeB ( without_XTerm, 0 );
      }
      break;

    case BT_CANT_DISCH_GOAL_M:
      if ( curr_env == anm_env ) {
        curr_env = main_env;         /* temp ... */
        process_XTerm_IfReq ();      /* to process xterm */
        curr_env = anm_env;          /* ... restored */
      }
      else {
        process_XTerm_IfReq ();
      }
      LoadBcjm ();
      DisplayCurrWinText ( "\n\n\n  Unable to discharge goal:\n\n    " );
      LoadFileIntoBuf ( "TMP/.Bcom", primary_string, 3001 );
      DisplayCurrWinText ( primary_string );
      DisplayCurrWinText ( "\n\n\n" );
      if ( auto_reset_and_remake && ( ! upgrade3T04_flag ) ) {
        Save_n_CfgDepBase ();
        AutoRemakeFini ();
        strcpy ( fifo_write_buf, "0:" );
        Cre_fifo_write_buf_cmd_0 ( BT_MOTIF_QUIT );
        InvokeB ( without_XTerm, 0 );
        return;
      }
      Popup_Err ( 0, "  Unable to complete current job " );
      strcpy ( fifo_write_buf, "0:" );
      Cre_fifo_write_buf_cmd_0 ( BT_RM_ALL_JOBS );
      InvokeB ( without_XTerm, 0 );
      break;      

    case BT_BTL_M:
      motif_init ( 0, "" );
      DisplayCurrWinText ( "...." );
      load_toolkit15_po_dot_src ( 1 ); /* dots! */
      DisplayCurrWinText ( "\n" );
      DisplayMainMenu ( 1, 0 );
      DisplayMainTopWin ();
      break;

    case BT_BTL_AUP_M:
      {
        int i, j, ext, st, level, obj;
        void load_toolkit15_po_dot_src ();
        int RestoreRecordedProofs ();
        void btl_autoprove ();
/***
printf ( "1BT_BTL_AUP_M: primary_string %s secondary_string %s\n", primary_string, secondary_string ); fflush ( stdout );
***/
        i = 0;
        j = 0;
        while ( ( primary_string [ i ] != '.' )  && 
                ( primary_string [ i ] != '\0' )    ) {
          buf [ j ] = primary_string [ i ];
          i++;
          j++;
	}
        buf [ j ] = '\0';
        if ( primary_string [ i ] != '\0' ) i++;
        j = 0;
        while ( primary_string [ i ] != '\0' ) {
          additional_string [ j ] = primary_string [ i ];
          i++;
          j++;
	}
        additional_string [ j ] = '\0';
        strcpy ( primary_string, buf );

        i = 0;
        j = 0;
        while ( ( secondary_string [ i ] != '.' )  && 
                ( secondary_string [ i ] != '\0' )    ) {
          buf [ j ] = secondary_string [ i ];
          i++;
          j++;
	}
        buf [ j ] = '\0';
        if ( secondary_string [ i ] != '\0' ) i++;


        ext = secondary_string [ i ] - '0';
        strcpy ( secondary_string, additional_string );

/***
printf ( "2BT_BTL_AUP_M: primary_string %s secondary_string %s buf %s ext %d\n", primary_string, secondary_string, buf, ext ); fflush ( stdout );
***/
        GetObjFromNameExt ( &obj, buf, ext );
        val_curMRIState ( &st, obj );
        length_pob ( &level, st );
        process_XTerm_IfReq ();
        LoadBcjm ();
        XmUpdateDisplay ( top_level );
        DisplayCurrWinText ( "\n  Processing proof file .." );
        load_toolkit15_po_dot_src ( 1 ); /* dots! */
        DisplayCurrWinText ( " done\n" );
        if ( RestoreRecordedProofs ( obj, level, 1 ) ) {
          btl_autoprove ( obj );
          strcpy ( fifo_write_buf, "0:" );
          CreNumInBuf ( fifo_write_buf, BT_ENV );
          Cre_tcp_env ();
          InvokeB ( with_XTerm, 0 );
	}
        else {
	  /***
          Popup_Err ( 0, "  Unable to complete current job " );
          TopBar_Interrupt_CB ();
          DisplayCurrentEnv ();
	  ***/
          strcpy ( fifo_write_buf, "0:" );
          CreNumInBuf ( fifo_write_buf, BT_ENV );
          Cre_tcp_env ();
          InvokeB ( with_XTerm, 0 );
	}
      }
      break;

    case BT_FILE_PARSE_NEW_M:
      if ( FileParses ( primary_string ) )
        sprintf ( fifo_write_buf, "1", BT_BSEL );
      else
        sprintf ( fifo_write_buf, "0", BT_BSEL );
      InvokeB ( without_XTerm, 0 );
      break;

    case BT_CHK_MCH_NAME_PARSES_M:
     {
       int i, f;
       int read_frmfunc_str_buf();
       i = 0;
       while ( primary_string [ i ] != '\0' ) {
         if   ( primary_string [ i ] == '_' ) str_buf [ i ] = ';';
         else                                 str_buf [ i ] = primary_string [ i ];
         i++;
       }
       str_buf [ i ] = '\0';
       report_parse_errors = 0;
       f = read_frmfunc_str_buf();
       report_parse_errors = 1;
       if ( f != -999 ) {
         kil_from_btoolkit(f);
         sprintf ( fifo_write_buf, "1", BT_BSEL );
       }
       else {
         sprintf ( fifo_write_buf, "0", BT_BSEL );
       }
       InvokeB ( without_XTerm, 0 );
     }
     break;

    case BT_IN_LINED_OPS_M:
      {
        void Check_inlined_ops_dot_h ();
        Check_inlined_ops_dot_h ();
        sprintf ( fifo_write_buf, "(%s):%d:0", secondary_string, BT_IN_LINED_OPS );
        InvokeB ( without_XTerm, 0 );
      }
      break;

    case BT_PRINT_EXTERN_M:
      {
        void Print_extern_dot_h ();
        Print_extern_dot_h ();
        sprintf ( fifo_write_buf, "(%s):%d:0", secondary_string, BT_PRINT_EXTERN );
        InvokeB ( without_XTerm, 0 );
      }
      break;

    case BT_PRINT_IN_LINED_OP_M:
      {
        void Print_inlined_op_dot_h ();
        Print_inlined_op_dot_h ();
        sprintf ( fifo_write_buf, "(%s):%d:0", secondary_string, BT_PRINT_IN_LINED_OP );
        InvokeB ( without_XTerm, 0 );
      }
      break;

    case BT_CHK_FOR_OPS_M:
      if ( primary_string [ 0 ] == '1' ) {
        void Pre_Animate ();
        Pre_Animate ( 1 );  /* flag = 1 => Interactive */
      }
      else {
        sprintf ( buf, "%s has no operations", secondary_string );
        Popup_Minor_Err ( NULL, buf );
      }
      break;

    case BT_IPT_CLOSURE_M:
      IptClosureOK ();
      break;

    case BT_IPT_DSGN_CHK_M:
      IptDesignCheckOK ();
      break;

    case BT_DUP_IPT_CHK_M:
      DupIptCheckOK ();
      break;

    case BT_QUERY_LNK_M:
    {

      /***
      primary string of form:
        (imp1 : 1)
      or
        (imp1 : 1;imp2 : 0)
      indicating that imp1 is linkable (imp2 is not)
      ***/

      void DisplayCurrentEnv_continue ();
      void Set_lnk_on ();
      i = 0;  /* i points to ( */
      while ( primary_string [ i ] != ')' ) {
        i++;
        j = 0;
        while ( primary_string [ i ] != ' ' ) {
          buf [ j++ ] = primary_string [ i++ ];
	}
        i = i + 3;  /* read sp colon sp */
        if ( primary_string [ i ] == '1' ) {
          buf [ j++ ] = '.';
          buf [ j++ ] = 'i';
          buf [ j++ ] = 'm';
          buf [ j++ ] = 'p';
          buf [ j++ ] = '\0';
          Set_lnk_on ( buf );
	}
        i++;       /* i now points to either ; or ) */
      }
      DisplayCurrentEnv_continue ();
    }
    break;

    case BT_ANM_EXE_STEP_FINI_M:
      {
        void LoadAnimatorFilesInto_sel_strs ();
        strcpy ( additional_string, "No Utilities" );
        LoadAnimatorFilesInto_sel_strs ( "New output file", "out" );
        Popup_Sel_flag = save_anm_output_sel;
        Popup_SelOne_Dialog ( top_level, "Select Output File" );
      }
    break;

    case BT_ANM_EXE_AUTO_FINI_M:
      {
        void LoadAnimatorFilesInto_sel_strs ();
        strcpy ( additional_string, "No Utilities" );
        LoadAnimatorFilesInto_sel_strs ( "New output file", "out" );
        Popup_Sel_flag = save_anm_output_sel;
        Popup_SelOne_Dialog ( top_level, "Select Output File" );
        if ( primary_string [ 0 ] == '0' )
          Popup_Minor_Err ( NULL, "All assertions evaluated to true" );
        else  if ( primary_string [ 0 ] == '1' )
          Popup_Minor_Err ( NULL, "At least one assertion did not evaluate to true" );
        else
          Popup_Minor_Err ( NULL, "No assertions in ANIMATE Script" );
      }
    break;

    case BT_ANM_EMPTY_SCRIPT_M:
      {
        void EditAnimateFile ();
        sprintf ( str_buf, "SRC/%s", primary_string );
        EditAnimateFile ( str_buf, 0 ); /* 0 => allow overwrite - just cre! */
      }
    break;

  case BT_PASP_APP_UNDERSC_M:
    /***
      rename prefix removed up to last underscore
      and replaced with Rename:
      aaa_bbb_sss_Name -> Rename_Name
    ***/
      {
        size_t j;
        size_t i = strlen ( primary_string );

        while ( ( i ) && primary_string [ i ] != '_' ) { i--; }
        if ( primary_string [ i ] = '_' ) {
          primary_string [ i ] = '\0';
          sprintf ( buf, "(%s_;Rename_", primary_string );
          primary_string [ i ] = '_';
          j = strlen ( buf );
          i++;
          while ( primary_string [ i ] != '\0' ) {
            buf [ j++ ] = primary_string [ i++ ];
	  }
         buf [ j ] = ')';
         buf [ j + 1 ] = '\0';
	}
        else {
          strcpy ( buf, "(0;0)" );
	}
/***
printf ( "BT_PASP_APP_UNDERSC_M: `%s' -> `%s'\n", primary_string, buf );
***/
        sprintf ( fifo_write_buf, "%s:%d:0", buf, BT_BSEL );
        InvokeB ( without_XTerm, 0 );
      }
      break;

    default:
      if ( bell_option ) {
        XBell ( display, -75 );
        XBell ( display, -75 );
      }
      process_XTerm_IfReq ();
      DisplayCurrentEnv ();
      break;

    } /* switch ( cmd ) */

}  /* ProcessB */
