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
char bar[42]="________________________________________\0";
char tabs[42]="\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\0";
char h1bar[82]="********************************************************************************\0";
char h2bar[82]="================================================================================\0";
char h3bar[82]="--------------------------------------------------------------------------------\0";
int lhs, rhs;
int indent=0;
%}

S	[\ \n\t]

%e 4000
%p 10000
%a 10000
%o 10000
%n 1000

%%
\<\![^\>]*\>		{ ; }

\<PRE\>[^\<]*\<\/PRE\>	{ yytext[strlen(yytext)-6] = '\0';
			  printf("\n$$%s\n$$",yytext+5); }

\<pre\>[^\>]*\<\/pre\>	{ yytext[strlen(yytext)-6] = '\0';
			  printf("\n$$%s\n$$",yytext+5); }

[\ \n\t][\ \n\t]*	{ printf(" "); }

"\\\<"			{ printf("<"); }
"\\\>"			{ printf(">"); }

\<EM\>			{ printf("$em_st"); }
\<\/EM\>		{ printf("$em_end"); }

\<em\>			{ printf("$em_st"); }
\<\/em\>		{ printf("$em_end"); }

\<TITLE\>.*\<\/TITLE\>	{ lhs = strlen(yytext+13)/2;
			  rhs = lhs;
			  if ( 2*rhs != strlen(yytext+13) ) rhs = rhs+1;
			  yytext[strlen(yytext)-8] = '\0';
			  printf("\n%s %s %s\n",bar+lhs,yytext+7,bar+rhs); }		
\<title\>.*\<\/title\>	{ lhs = strlen(yytext+13)/2;
			  if ( (rhs = lhs) != strlen(yytext+13)/2 ) rhs = rhs+1;
			  yytext[strlen(yytext)-8] = '\0';
			  printf("\n%s %s %s\n",bar+lhs,yytext+7,bar+rhs); }

\<H1\>[^\<]*\<\/H1\>	{ yytext[strlen(yytext)-5] = '\0';
			  printf("\n\n%s\n%s\n\n",yytext+4,h1bar+80-strlen(yytext)+4); }		

\<h1\>[^\<]*\<\/h1\>	{ yytext[strlen(yytext)-5] = '\0';
			  printf("\n\n%s\n%s\n\n",yytext+4,h1bar+80-strlen(yytext)+4); }		

\<H2\>[^\<]*\<\/H2\>	{ yytext[strlen(yytext)-5] = '\0';
			  printf("\n\n%s\n%s\n\n",yytext+4,h2bar+80-strlen(yytext)+4); }		

\<h2\>[^\<]*\<\/h2\>	{ yytext[strlen(yytext)-5] = '\0';
			  printf("\n\n%s\n%s\n\n",yytext+4,h2bar+80-strlen(yytext)+4); }		

\<H3\>[^\<]*\<\/H3\>	{ yytext[strlen(yytext)-5] = '\0';
			  printf("\n\n%s\n%s\n\n",yytext+4,h3bar+80-strlen(yytext)+4); }		

\<h3\>[^\<]*\<\/h3\>	{ yytext[strlen(yytext)-5] = '\0';
			  printf("\n\n%s\n%s\n\n",yytext+4,h3bar+80-strlen(yytext)+4); }		

\<P\>			{ printf("\n\n"); }		
\<p\>			{ printf("\n\n"); }

\<HEAD\>		{ printf(""); }
\<\/HEAD\>		{ printf(""); }

\<head\>		{ printf(""); }
\<\/head\>		{ printf(""); }

\<BODY\>		{ ; }
\<\/BODY\>		{ ; }

\<body\>		{ ; }
\<\/body\>		{ ; }

\<HR\>			{ printf("\n%s%s\n",bar,bar); }
\<hr\>			{ printf("\n%s%s\n",bar,bar); }

\<UL\>			{ if ( indent < strlen(tabs) ) indent = indent+1; }
\<ul\>			{ if ( indent < strlen(tabs) ) indent = indent+1; }

\<OL\>			{ if ( indent < strlen(tabs) ) indent = indent+1; }
\<ol\>			{ if ( indent < strlen(tabs) ) indent = indent+1; }

\<\/UL\>		{ if ( indent > 0 ) indent = indent-1; }
\<\/ul\>		{ if ( indent > 0 ) indent = indent-1; }

\<\/OL\>		{ if ( indent > 0 ) indent = indent-1; }
\<\/ol\>		{ if ( indent > 0 ) indent = indent-1; }

\<LI\>			{ printf("\n%s-  ",tabs+strlen(tabs)-indent); }
\<li\>			{ printf("\n%s-  ",tabs+strlen(tabs)-indent); }

\<HTML\>		{ printf(""); }
\<\/HTML\>		{ printf("\n%s%s\n\n",bar,bar); }

\<html\>		{ printf(""); }
\<\/html\>		{ printf(""); }

\<[^\>]*\>		{ ; }
.			{ printf("%s",yytext); }
