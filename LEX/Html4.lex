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

%{
#define LEXDEBUG
#define allprint(x) printf("%d",x);
#define sprint(x) sprintf("%s",x);
int linelen=0;
char startem[8]="";
char endem[6]="";
%}

%e 4000
%p 10000
%a 10000
%o 10000
%n 1000

%%

"\$em\_end"	{ printf("%s",startem); }
"\$em\_st"	{ printf("%s",endem); }

\$\$[^\$]*\$\$	{ printf("%s",yytext); }

\n		{ linelen = 0; printf("\n"); }

[^\$^\ ^\t^\n]*	{ linelen = linelen+strlen(yytext);
		  if ( linelen > 80 ) { printf("\n"); linelen = strlen(yytext); }
		  printf("%s",yytext); }

\ 		{ linelen = linelen+1; printf(" "); }

\t 		{ linelen = linelen+4; printf("\t"); }

.       	{ linelen = linelen+1; printf("%s",yytext); }
