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


%S INBRACES
	/***
	   Doc_Latexer
	***/

  int flag=0;


DOCCLASSBEGA    "\\documentclass{"
DOCCLASSBEGB    "\\documentclass["
DOCSTYLEBEGA    "\\documentstyle{"
DOCSTYLEBEGB    "\\documentstyle["
USEPACKBEG      "\\usepackage{"

BEGINDOC        "\\begin{document}\n"
ENDDOC		"\\end{document}\n"
MKINDEX		"\\makeindex\n"
TOK             "\\tableofcontents\n"
STARTANNOT	"\"0QjKOo"
ENDANNOT	"oOKjQ0\""

   int bracket_flag = 0;

%%

{BEGINDOC}	{ ; }
{ENDDOC}	{ ; }
{MKINDEX}	{ ; }
{TOK}           { ; }
{STARTANNOT}	{ ; }
{ENDANNOT}	{ ; }

{DOCCLASSBEGA}           { BEGIN INBRACES; }
{DOCCLASSBEGB}           { BEGIN INBRACES; }
{DOCSTYLEBEGA}           { BEGIN INBRACES; }
{DOCSTYLEBEGB}           { BEGIN INBRACES; }
{USEPACKBEG}             { BEGIN INBRACES; }

<INBRACES>"}[ \t]*\n"    { BEGIN 0; }
<INBRACES>"}\n"          { BEGIN 0; }
<INBRACES>"_".           { ; }
<INBRACES>"\\_".         { ; }
<INBRACES>.              { ; }

"\\bbpageref"		{ printf("\\pageref"); }

" _?_oO00Oo_?_ "	{ printf("\n"); }

"\\section{"		{ ECHO; flag=1; } 

"\\_"			{ ECHO; }

"_"			{ if (flag==1) { printf("\\_"); } else { ECHO; } }

"}"			{ flag=0; ECHO; } 
