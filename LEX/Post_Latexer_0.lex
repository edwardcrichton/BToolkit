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
%e  4000
%p 12000
%n  2000
%a  4500
%o  3000
%k  1000

	/***
	   Post_Latexer_0
	***/


  int flag=0;
	/*
		flag=0 => outside labels and annotations
		flag=1 => inside label
		flag=1 => inside annotation
	*/
 

STARTANNOT	"\"0QjKOo"
ENDANNOT	"oOKjQ0\""

ANNOTNL		" _?_oO00Oo_?_ "

ENDSTARTANNOT	"oOKjQ00QjKOo"

WS       [ \t\n]+
OPTWS    [ \t\n]*
NONNLWS  [ \t]*

%%

{STARTANNOT}	{ flag=2; }

{ENDANNOT}	{ flag=0; }


{ENDSTARTANNOT}	{ printf("\n"); }



{ANNOTNL}{OPTWS}{ENDSTARTANNOT}"\\\\\\rule"	{ printf("\\ \\\\\\rule"); }

{ANNOTNL}		{ printf("\n"); }






"\\end{tabbing}"{OPTWS}"\\vspace{-6.5ex}"{OPTWS}{STARTANNOT}{OPTWS}{ENDANNOT}"\\ \\\\"{OPTWS}"\\rule{\\textwidth}{.1ex}"	{ printf("\\end{tabbing}\n"); }






"\\end{tabbing}"{OPTWS}"\\vspace{-6.5ex}"{OPTWS}{STARTANNOT}{OPTWS}\\pagebreak{OPTWS}{ENDANNOT}"\\ \\\\"{OPTWS}"\\rule{\\textwidth}{.1ex}"	{ printf("\\end{tabbing}\n\\pagebreak\n"); }

"\\end{tabbing}"{OPTWS}"\\vspace{-6.5ex}"{OPTWS}{STARTANNOT}{OPTWS}\\newpage{OPTWS}{ENDANNOT}"\\ \\\\"{OPTWS}"\\rule{\\textwidth}{.1ex}"	{ printf("\\end{tabbing}\n\\newpage\n"); }





"\\+"{OPTWS}"\\-"{OPTWS}"\\bnl"{OPTWS}	{ ; }
"\\+"{OPTWS}"\\bnl"{OPTWS}"\\-"{OPTWS}	{ ; }
"\\-"{OPTWS}"\\+"{OPTWS}"\\bnl"{OPTWS}	{ ; }
"\\-"{OPTWS}"\\bnl"{OPTWS}"\\+"{OPTWS}	{ ; }

"\\+"{OPTWS}"\\-"{OPTWS}"\\bbnl"{OPTWS}	{ ; }
"\\+"{OPTWS}"\\bbnl"{OPTWS}"\\-"{OPTWS}	{ ; }
"\\-"{OPTWS}"\\+"{OPTWS}"\\bbnl"{OPTWS}	{ ; }
"\\-"{OPTWS}"\\bbnl"{OPTWS}"\\+"{OPTWS}	{ ; }





"\\end{tabbing}"{OPTWS}"\\begin{tabbing}"{OPTWS}"\\bSetTabs"{OPTWS}"\\+\\>"{OPTWS}"\\end{tabbing}"{OPTWS}"\\vspace{-1.5ex}"	{ printf("\\end{tabbing}\n\\vspace{-2ex} "); }


"\\bnl"{OPTWS}"\\+"{OPTWS}"\\end{tabbing}"	{ printf("\n\\end{tabbing}"); }
"\\+"{OPTWS}"\\bnl"{OPTWS}"\\end{tabbing}"	{ printf("\n\\end{tabbing}"); }
"\\bnl"{OPTWS}"\\end{tabbing}"			{ printf("\n\\end{tabbing}"); }

"\\bbnl"{OPTWS}"\\+"{OPTWS}"\\end{tabbing}"	{ printf("\\end{tabbing}"); }
"\\+"{OPTWS}"\\bbnl"{OPTWS}"\\end{tabbing}"	{ printf("\n\\end{tabbing}"); }
"\\bbnl"{OPTWS}"\\end{tabbing}"			{ printf("\n\\end{tabbing}"); }


"\\bhsp"{OPTWS}"\\bhsp"			{ printf("\\bhsp"); }
"\\bhsp"{OPTWS}"\\bnl"{OPTWS}"\\bhsp"	{ printf("\\bnl\n"); }
"\\bhsp"{OPTWS}"\\bnl"			{ printf("\\bnl"); }
"\\bnl"{OPTWS}"\\bhsp"			{ printf("\\bnl\n"); }

"\\bhsp"{OPTWS}"\\bbnl"{OPTWS}"\\bhsp"	{ printf("\\bbnl\n"); }
"\\bhsp"{OPTWS}"\\bbnl"			{ printf("\\bbnl"); }
"\\bbnl"{OPTWS}"\\bhsp"			{ printf("\\bbnl\n"); }


"\\bbnl"{OPTWS}"\\+"{OPTWS}"\\bnl"	{ printf("\\+ \\bbnl"); }

"\\bnl"{OPTWS}"\\+"{OPTWS}"\\bhsp"	{ printf("\\+ \\bnl\n"); }
"\\bnl"{OPTWS}"\\-"{OPTWS}"\\bhsp"	{ printf("\\- \\bnl\n"); }
"\\bnl"{OPTWS}"\\+"			{ printf("\\+ \\bnl\n"); }
"\\bnl"{OPTWS}"\\-"			{ printf("\\- \\bnl\n"); }

"\\bbnl"{OPTWS}"\\+"{OPTWS}"\\bhsp"	{ printf("\\+ \\bbnl\n"); }
"\\bbnl"{OPTWS}"\\-"{OPTWS}"\\bhsp"	{ printf("\\- \\bbnl\n"); }
"\\bbnl"{OPTWS}"\\+"			{ printf("\\+ \\bbnl\n"); }
"\\bbnl"{OPTWS}"\\-"			{ printf("\\- \\bbnl\n"); }


"\\bOpnWord{END}"{OPTWS}"\\-"{OPTWS}"\\bbnl"{OPTWS}"\\bOperationSemiColon"{OPTWS}	{ printf("\\bOpnWord{END} \\bOperationSemiColon \\- \n"); }


"\\bopname{"	{ ECHO; flag=32; } 

"\\label{"	{ ECHO; flag=3; } 

"\\index{"	{ ECHO; flag=3; } 

"\\bbpageref{"	{ if (flag==0) { ECHO; flag=40; } else { ECHO; flag=42; } }

"\\ref{"	{ ECHO; flag=5; } 

"}"		{ if (flag==3) { flag=0; ECHO; } else if (flag==40) { flag=0; ECHO; } else if (flag==42) { flag=2; ECHO; } else if (flag==32) { flag=0; ECHO; } else { ECHO; } } 


"_"	{ if (flag==0) { printf("\\_"); } else if (flag==32) { printf("\\_"); } else { ECHO; } }

{OPTWS}[\n]{OPTWS}	{ printf("\n"); }
