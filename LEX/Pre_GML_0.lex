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

	/***
	   Pre_GML_0:
             removes comments
	***/


EMPTYCOMMENT    "/*"[ \t\n]*"*/"

STARTANNOT      "/*\""
ENDANNOT	"\"*/"

STARTANNOTNL	"/*\""[ \t]*[\n][ \t]*

STARTANNOTSP	"/*\""[ \t]

STARTCOMMENT  "/*"[^"]
ENDCOMMENT    [^"]"*/"

  int flag=0;
	/*
		flag=0 => outside comments and annotations 
		flag=1 => inside annotation
		flag=2 => inside comment
	*/
 
%%

{EMPTYCOMMENT}  { flag=0; }

{STARTANNOTNL}	{ printf("/*\""); flag=1; }

{STARTANNOTSP}	{ printf("/*\""); flag=1; }

{STARTANNOT}	{ ECHO; flag=1; }
{ENDANNOT}	{ ECHO; flag=0; }

{STARTCOMMENT}	{ flag=2; }
{ENDCOMMENT}	{ flag=0; }

"\\newpage"[ \t\n]*	{ printf("\\newpage "); }
"\\pagebreak"[ \t\n]*	{ printf("\\pagebreak "); }

[\n]		{ if (flag==1) { printf(" _?_oO00Oo_?_\n"); } else { ECHO; } }

.		{ if (flag==2) { ; }  else { ECHO; } }
