/* Copyright (c) 1988-2009, B-Core (UK) Ltd
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
#define BT_VERSION "6.0.3"
#define BT_COPYRIGHT_YEAR "2012"
#define BT_COMPANY "B-Core(UK) Ltd."

char cur_hdr_string[] = "BT401";
char old_hdr_string[] = "BT400";
/*** must ALWAYS be length 5
       for UpgradeWWW, DetermineBpdaType & BToolkit to work ***/

/* must always be of length 8 */
char cur_BToolkitd_id[] = "0401";
#define len_cur_BToolkitd_id 4


char * lock_file_name         = "/tmp/.Btkd"BT_VERSION"pid";

char * b_name                 = "                b Release "BT_VERSION" for B-Core";
char * btool_name             = "                         B-Tool";
char * toolkit_name           = "                       B-Toolkit";

char * toolkit_ver_with_sp    = "                    Release "BT_VERSION"";

char * toolkit_copyright      = "          Copyright(c) 1985-"BT_COPYRIGHT_YEAR" "BT_COMPANY"";

/**/
char * toolkit_copyright_year = "          Copyright(c) 1985-"BT_COPYRIGHT_YEAR"";
char * toolkit_company        = "                    "BT_COMPANY"";

char * orig_author            = "               Original Author J-R Abrial";

char * toolkit_ver            = "B-Toolkit Release "BT_VERSION"";
char * tool_ver               = "B-Tool Release "BT_VERSION"";
char * toolkit_short_ver      = "B-Toolkit "BT_VERSION"";
char * no_toolkit_short_ver   = BT_VERSION;

char *cpyrt[] = { "B-Toolkit (c) Copyright "BT_COMPANY" 1985-"BT_COPYRIGHT_YEAR"" };

/***
used by BMotif_widgets.c
***/

char *B_info_help_text =
     "  `B' is the generic term comprising the following:\n\n\
  o  B-Method\n\
       the collection of mathematically based techniques\n\
       for the specification, design and implementation\n\
        of software components.\n\n\
  o  Abstract Machine Notation\n\
       the notation used to specify and design software\n\
       systems using the B-Method; often abbreviated\n\
       to AMN, it is, in turn, based on the mathematical\n\
       theory of Generalised Substitutions.\n\n\
  o  B-Toolkit\n\
       the set of integrated software tools designed to\n\
       provide complete support for all aspects of\n\
       software developments using the B-Method\n\n\
  o  B-Platform\n\
       the inference engine providing the software\n\
       platform on which many of the tools of the B-Toolkit\n\
       are built also known as the B-Tool and the B-Kernel,\n\
       it has been sold as the former since 1991.\n\n\
      B was developed by BP International Ltd. from 1985-92;\n\
       B-Core(UK) Ltd. purchased the full rights to B in 1993,\n\
              and is continuing to develop all aspects of B.";


char * BCore_info_help_text = "\n\
                           B-Toolkit Release "BT_VERSION"\n\n\
                               B-Core(UK) Ltd.\n\
           The B-Tool, B-Toolkit, B-Platform and AMN are\n\
                Copyright (c) 1985-"BT_COPYRIGHT_YEAR" B-Core(UK) Ltd.\n";
