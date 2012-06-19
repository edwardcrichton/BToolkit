/* Copyright (c) 1988-98, B-Core (UK) Ltd
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
extern char cur_hdr_string[];
extern char old_hdr_string[];
/*** must ALWAYS be length 5
       for UpgradeWWW, DetermineBpdaType & BToolkit to work ***/

/* must always be of length 8 */
extern char cur_BToolkitd_id[];
#define len_cur_BToolkitd_id 4


/***
used by BToolkit.c & BMotif_widgets.c
***/
extern char * b_name;
extern char * btool_name;
extern char * toolkit_name;
extern char * toolkit_ver_with_sp;
extern char * toolkit_copyright;
extern char * toolkit_copyright_year;
extern char * toolkit_company;
extern char * orig_author;

/***
used by BMotif_widgets.c & BMotif_browser.c
***/
extern char * toolkit_init_ver;
extern char * toolkit_ver;
extern char * tool_ver;
extern char * toolkit_short_ver;

extern char *cpyrt[];

/***
used by BMotif_widgets.c
***/
extern char * B_info_help_text;



#ifdef WWW_VERSION

extern char * BCore_info_help_text;

#else

extern char * BCore_info_help_text;

#endif

#ifdef WWW_VERSION

#define B_WWW_intro_text_width  400
#define B_WWW_intro_text_height 450
#define B_WWW_intro_text_top_offset 125
#define B_WWW_intro_text_left_offset 63
extern char * B_WWW_intro_text;

extern char * B_WWW_prelim_text;

#endif /* WWW_VERSION */
