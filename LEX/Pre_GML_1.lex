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


STARTANT	"/*\""
ENDANT		"\"*/"

NL		[ \t]*"\n"[ \t]*
OPTNL		[ \t\n]*
NONNLWS		[ \t]+


%%


{ENDANT}{NL}{NL}{NL}{NL}{NL}{OPTNL}{STARTANT}	{ printf(" _?_oO00Oo_?_\n _?_oO00Oo_?_\n _?_oO00Oo_?_\n _?_oO00Oo_?_\n _?_oO00Oo_?_\n"); }
{ENDANT}{NL}{NL}{NL}{NL}{STARTANT}		{ printf(" _?_oO00Oo_?_\n _?_oO00Oo_?_\n _?_oO00Oo_?_\n _?_oO00Oo_?_\n"); }
{ENDANT}{NL}{NL}{NL}{STARTANT}			{ printf(" _?_oO00Oo_?_\n _?_oO00Oo_?_\n _?_oO00Oo_?_\n"); }
{ENDANT}{NL}{NL}{STARTANT}			{ printf(" _?_oO00Oo_?_\n _?_oO00Oo_?_\n"); }
{ENDANT}{NL}{STARTANT}				{ printf("_?_oO00Oo_?_\n"); }
{ENDANT}{NONNLWS}{STARTANT}			{ printf(" "); }

"\nPRE"		{ printf("\n PRE"); }
"\nBEGIN"	{ printf("\n BEGIN"); }
"\nIF"		{ printf("\n IF"); }
"\nCHOICE"	{ printf("\n CHOICE"); }
"\nSELECT"	{ printf("\n SELECT"); }
"\nCASE"	{ printf("\n CASE"); }
"\nEITHER"	{ printf("\n EITHER"); }
"\nANY"		{ printf("\n ANY"); }
"\nVAR"		{ printf("\n VAR"); }
"\nLET"		{ printf("\n LET"); }
"\nWHILE"	{ printf("\n WHILE"); }
"\nTHEN"	{ printf("\n THEN"); }
"\nWHERE"	{ printf("\n WHERE"); }
"\nDO"		{ printf("\n DO"); }
"\nINVARIANT"	{ printf("\n INVARIANT"); }
"\nVARIANT"	{ printf("\n VARIANT"); }
"\nOF"		{ printf("\n OF"); }
"\nIN"		{ printf("\n IN"); }
"\nBE"		{ printf("\n BE"); }
"\nOR"		{ printf("\n OR"); }
"\nELSE"	{ printf("\n ELSE"); }
"\nor "		{ printf("\n or "); }
"\nor\t"	{ printf("\n or\t"); }

[ \t]*"("[ \t]*\n	{ printf("(tnednItS & "); }
\n[ \t]*")"[ \t]*	{ printf(" & tnednIdE)"); }
