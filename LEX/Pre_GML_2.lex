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


%e  2000
%p 10000
%n   700
%a  2500
%k  1000
%o  2000
%S PROLOG INSCANT INADANT INCMANT SCRQD ADRQD CMRQD SCNOTRQD ADNOTRQD CMNOTRQD QSC QAD QCM

	/***
	   Pre_GML_1:
		replaces annotations by strings, ensuring parsing
	***/

	/*
	   where I've written / * or * / in the comments below
	  the space is there only to avoid confusion with cpp
	  and *this* file - the spaces don't appear in the
	  processed files

	  replaces annotations by strings:
		/ *" annot "* / --> "oO? annot oO?"
	  and inserts appropriate separator
	*/



  int flag=0;
	/*
		flag=0 => outside comments and annotations
		flag=1 => inside annotation
		flag=2 => inside comment
	*/



STARTANNOT	"/*\""
ENDANNOT	"\"*/"

WS		[ \t\n]+
OPTWS		[ \t\n]*

NONWS		[^ \t\n]*


%%


"#"             { printf("/* to prevent undefined control ... */  #"); }



<INSCANT>{ENDANNOT}	{ printf("?Oo\"");  flag=0; BEGIN QSC; }
<INSCANT>.		{ ECHO; }

<INADANT>{ENDANNOT}	{ printf("?Oo\"");  flag=0; BEGIN QAD; }
<INADANT>.		{ ECHO; }

<INCMANT>{ENDANNOT}	{ printf("?Oo\"");  flag=0; BEGIN QCM; }
<INCMANT>.		{ ECHO; }


<SCNOTRQD>{STARTANNOT}	{ printf("\"oO?");  flag=1; BEGIN INSCANT; }
<SCNOTRQD>{WS}=		{ ECHO; }
<SCNOTRQD>[ \t\n]	{ ECHO; }
<SCNOTRQD>[^;]		{ ECHO;                     BEGIN SCRQD; }

<ADNOTRQD>{STARTANNOT}	{ printf("\"oO?");  flag=1; BEGIN INADANT; }
<ADNOTRQD>{WS}=		{ ECHO; }
<ADNOTRQD>[ \t\n]	{ ECHO; }
<ADNOTRQD>[^&]		{ ECHO;                     BEGIN ADRQD; }

<CMNOTRQD>{STARTANNOT}	{ printf("\"oO?");  flag=1; BEGIN INCMANT; }
<CMNOTRQD>{WS}=		{ ECHO; }
<CMNOTRQD>[ \t\n]	{ ECHO; }
<CMNOTRQD>[^,]		{ ECHO;                     BEGIN CMRQD; }


<SCRQD>";"		{ ECHO;                               BEGIN SCNOTRQD; }
<SCRQD>"||"		{ ECHO;                               BEGIN SCNOTRQD; }
<SCRQD>{WS}:=		{ ECHO; }
<SCRQD>{WS}=		{ ECHO; }
<SCRQD>{STARTANNOT}	{ printf("70OoscoO07 \"oO?"); flag=1; BEGIN INSCANT; }

<ADRQD>"&"		{ ECHO;                                 BEGIN ADNOTRQD; }
<ADRQD>{WS}=		{ ECHO; }
<ADRQD>{STARTANNOT}	{ printf(" 70OoampoO07 \"oO?"); flag=1; BEGIN INADANT; }

<CMRQD>","		{ ECHO;                                 BEGIN CMNOTRQD; }
<CMRQD>{WS}=		{ ECHO; }
<CMRQD>{STARTANNOT}	{ printf(" 70OocomoO07 \"oO?"); flag=1; BEGIN INCMANT; }


<QSC>{WS}BEGIN{WS}	{ printf(" 70OoscoO07 "); 	ECHO; BEGIN SCNOTRQD; }
<QSC>{WS}IF{WS}		{ printf(" 70OoampoO07 "); 	ECHO; BEGIN ADNOTRQD; }
<QAD>{WS}IF{WS}		{ printf(" 70OoampoO07 "); 	ECHO; BEGIN ADNOTRQD; }

<QSC>{WS}PRE{WS}	{ printf(" 70OoampoO07 "); 	ECHO; BEGIN ADNOTRQD; }

<QSC>{WS}CHOICE{WS}	{ printf(" 70OoscoO07 "); 	ECHO; BEGIN SCNOTRQD; }
<QSC>{WS}SELECT{WS}	{ printf(" 70OoampoO07 "); 	ECHO; BEGIN ADNOTRQD; }
<QSC>{WS}CASE{WS}	{ printf(" 70OoscoO07 "); 	ECHO; BEGIN SCNOTRQD; }
<QSC>{WS}VAR{WS}	{ printf(" 70OoscoO07 "); 	ECHO; BEGIN SCNOTRQD; }
<QSC>{WS}ANY{WS}	{ printf(" 70OoscoO07 "); 	ECHO; BEGIN SCNOTRQD; }
<QSC>{WS}LET{WS}	{ printf(" 70OoscoO07 "); 	ECHO; BEGIN SCNOTRQD; }
<QSC>{WS}WHILE{WS}	{ printf(" 70OoampoO07 "); 	ECHO; BEGIN ADNOTRQD; }
<QSC>{WS}DO{WS}		{               ECHO; BEGIN SCNOTRQD; }
<QSC>{WS}EITHER{WS}	{ printf(" 70OoampoO07 "); 	ECHO; BEGIN ADNOTRQD; }
<QSC>{WS}BASE{WS}	{ printf(" 70OoscoO07 "); 	ECHO; BEGIN SCNOTRQD; }
<QSC>{WS}GLOBAL{WS}	{ printf(" 70OoscoO07 "); 	ECHO; BEGIN SCNOTRQD; }
<QSC>{WS}END{WS}	{               ECHO; BEGIN SCRQD;    }
<QAD>{WS}END{WS}	{               ECHO; BEGIN SCRQD;    }
<QCM>{WS}END{WS}	{               ECHO; BEGIN SCRQD;    }
<QSC>{WS}END[a-z0-9A-Z_]		{               ECHO;    }
<QAD>{WS}END[a-z0-9A-Z_]		{               ECHO;    }
<QCM>{WS}END[a-z0-9A-Z_]		{               ECHO;    }

<QSC>";"		{                           ECHO; BEGIN SCNOTRQD; }
<QSC>"="		{                           ECHO; BEGIN SCNOTRQD; }
<QSC>[ \t\n]		{                           ECHO;                 }
<QSC>.			{ printf(" 70OoscoO07 ");   ECHO; BEGIN SCNOTRQD; }

<QAD>"&"		{                           ECHO; BEGIN ADNOTRQD; }
<QAD>[ \t\n]		{                           ECHO;                 }
<QAD>.			{ printf(" 70OoampoO07 ");  ECHO; BEGIN ADNOTRQD; }

<QCM>","		{                           ECHO; BEGIN CMNOTRQD; }
<QCM>[ \t\n]		{                           ECHO;                 }
<QCM>.			{ printf(" 70OocomoO07 ");  ECHO; BEGIN CMNOTRQD; }


{WS}BEGIN{WS}		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}IF{WS} 		{ if (flag==0) { ECHO; BEGIN ADNOTRQD;} else { ECHO; } }
{WS}PRE{WS} 		{ if (flag==0) { ECHO; BEGIN ADNOTRQD;} else { ECHO; } }
{WS}CHOICE{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}SELECT{WS} 		{ if (flag==0) { ECHO; BEGIN ADNOTRQD;} else { ECHO; } }
{WS}CASE{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}EITHER{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}VAR{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}ANY{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}LET{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}WHILE{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}DO{WS}		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}GLOBAL{WS}		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}BASE{WS}		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}OF{WS}EITHER{WS} 	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}OF{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}THEN{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}IS{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}OR{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}WHEN{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}IN{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}BE{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}WHERE{WS} 		{ if (flag==0) { ECHO; BEGIN ADNOTRQD;} else { ECHO; } }
{WS}ELSE{WS} 		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}ELSIF{WS} 		{ if (flag==0) { ECHO; BEGIN ADNOTRQD;} else { ECHO; } }
{WS}VARIANT{WS} 	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{OPTWS}DOCUMENT{WS} 	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{OPTWS}MACHINE{WS} 	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{OPTWS}REFINEMENT{WS}	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{OPTWS}IMPLEMENTATION{WS} { if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{OPTWS}SYSTEM{WS}	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{OPTWS}ENUMERATION{WS}	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{OPTWS}INTERFACE{WS}	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}REFINES{WS}		{ if (flag==0) { ECHO; BEGIN CMNOTRQD;} else { ECHO; } }
{WS}DEFINITIONS{WS}	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}CONSTRAINTS{WS}	{ if (flag==0) { ECHO; BEGIN ADNOTRQD;} else { ECHO; } }
{WS}USES{WS}	 	{ if (flag==0) { ECHO; BEGIN CMNOTRQD;} else { ECHO; } }
{WS}SEES{WS}	 	{ if (flag==0) { ECHO; BEGIN CMNOTRQD;} else { ECHO; } }
{WS}INCLUDES{WS}	{ if (flag==0) { ECHO; BEGIN CMNOTRQD;} else { ECHO; } }
{WS}IMPORTS{WS}		{ if (flag==0) { ECHO; BEGIN CMNOTRQD;} else { ECHO; } }
{WS}SUPPORTS{WS}	{ if (flag==0) { ECHO; BEGIN CMNOTRQD;} else { ECHO; } }
{WS}PROMOTES{WS}	{ if (flag==0) { ECHO; BEGIN CMNOTRQD;} else { ECHO; } }
{WS}EXTENDS{WS}		{ if (flag==0) { ECHO; BEGIN CMNOTRQD;} else { ECHO; } }
{WS}SETS{WS}		{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}CONTENTS{WS}	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}CONSTANTS{WS}	{ if (flag==0) { ECHO; BEGIN CMNOTRQD;} else { ECHO; } }
{WS}PROPERTIES{WS}	{ if (flag==0) { ECHO; BEGIN ADNOTRQD;} else { ECHO; } }
{WS}VARIABLES{WS}	{ if (flag==0) { ECHO; BEGIN CMNOTRQD;} else { ECHO; } }
{WS}INVARIANT{WS}	{ if (flag==0) { ECHO; BEGIN ADNOTRQD;} else { ECHO; } }
{WS}ASSERTIONS{WS}	{ if (flag==0) { ECHO; BEGIN ADNOTRQD;} else { ECHO; } }
{WS}INITIALISATION{WS}	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}OPERATIONS{WS}	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}OPTIONAL{WS}	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}MANDATORY{WS}	{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}=			{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }
{WS}==			{ if (flag==0) { ECHO; BEGIN SCNOTRQD;} else { ECHO; } }


{WS}END		{ if (flag==0) { ECHO; BEGIN SCRQD; } else { ECHO; } }


{STARTANNOT}		{ printf(" \"oO?"); BEGIN PROLOG; }

<PROLOG>{ENDANNOT}	{ printf("?Oo\" 70OoscoO07 "); flag=0; }



.			{ ECHO; }


