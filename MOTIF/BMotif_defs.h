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
#ifndef ___BMOTIF_DEFS
#define ___BMOTIF_DEFS

#if ( defined ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

#include <Xm/XmAll.h>

typedef struct textWidgetXeditor
{
	Widget* widget;
	char* editor;
} textWidgetXeditor;

typedef struct textWidgetXbrowser
{
	Widget* widget;
	char* browser;
} textWidgetXbrowser;

typedef struct TopBarMenuItem {
    char                   * label;     /* the label */
    XtPointer              client_data; /* client*data for callback/NULL */
    struct TopBarMenuItem  * subitems;  /* cascade pullright menu/NULL */
} TopBarMenuItem;

typedef struct HelpMenuItem {
    char                * label;     /* the label for the item */
    char                * labelR;    /* the (dummy) accel label for the item */
    XtPointer           client_data; /* client*data for callback/NULL */
    struct HelpMenuItem * subitems;  /* cascade pullright menu/NULL */
} MenuItem;

#endif /* ( defined ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) ) */


struct ok_cancel_but_struct {
  int      but;
  int      file_diff_but;
};

struct help_struct {
  char *     text;
  int        width;
  int        height;
  int        type;
};

struct coord {
  int      x;
  int      y;
};

#if ( defined ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) )

struct MainDisplay {
  XtPointer row;
  XtPointer cmt;
  XtPointer anl;
  XtPointer pog;
  XtPointer anm;
  XtPointer sts;
  XtPointer rst;
  XtPointer nme;
};
  
struct ProversDisplay {
  XtPointer row;
  XtPointer cmt;
  XtPointer prv;
  XtPointer pmd;
  XtPointer ppf;
  XtPointer rsl;
  XtPointer lvl;
  XtPointer nme;
};
  
struct GeneratorsDisplay {
  XtPointer row;
  XtPointer cmt;
  XtPointer gbo;
  XtPointer gbm;
  XtPointer Enm;
  XtPointer Itf;
  XtPointer rst;
  XtPointer nme;
};
  
struct TranslatorsDisplay {
  XtPointer row;
  XtPointer cmt;
  XtPointer trl;
  XtPointer lnk;
  XtPointer exe;
  XtPointer rst;
  XtPointer nme;
};

struct DocumentsDisplay {
  XtPointer row;
  XtPointer cmt;
  XtPointer dmu;
  XtPointer shw;
  XtPointer prt;
  XtPointer rst;
  XtPointer nme;
};

struct Display {  /* remember to edit DisplayCopy */
  int      obj;
  char     name [ MAX_SRCName ];
  short    type;
  short    changed;
  short    decoration;
  short    cmt_on_off;
  short    sc_state;
  int      ps;
  int      Main_offset;
  int      Provers_offset;
  int      Generators_offset;
  int      Translators_offset;
  int      Documents_offset;
};

struct SourceControlStruct {
  char but_name [ SC_BUT_NAME_MAX + 10 ];
  char but_act  [ SC_BUT_ACT_MAX  + 50 ];
  short type;
};


#endif /* ( defined ( BTOOLKIT_FLAG ) || defined ( BTOOLM_FLAG ) ) */

#endif /* #ifndef ___BMOTIF_DEFS */
