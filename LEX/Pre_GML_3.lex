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
%p  6000
%e  2000
%n  1000

%S INCOMMENT INANT


	/***
	   Pre_GML_2:
             Replaces symbols with newline symbols
             (as defined in AMNSYMBOLD)

             Replaces "\"oO?" with "\"0QjKOo"
             Replaces "?Oo\"" with "oOKjQ0\""
	***/


  int flag=0;
	/*
		flag=0 => outside annotations 
		flag=2 => inside annotation
	*/
 

STARTANT	"\"oO?"
ENDANT		"?Oo\""

PRENL		[\n][ \t]*
POSTNL		[ \t]*[\n]
SPORTAB		[ \t]

NONNLWS		[ \t]
ALPHA		[a-zA-Z0-9 \t(){}\]]
NONALPHA        [^a-zA-Z0-9_]

%%

{STARTANT}		{ printf("\n\"0QjKOo"); flag=2; BEGIN INANT; }
<INANT>{ENDANT}		{ printf("oOKjQ0\"\n"); flag=0; BEGIN 0; }
<INANT>.		{ ECHO; }


{NONALPHA}IMPLEMENTATION{POSTNL}	{ if (flag==0) printf(" IMPLEMENTATIONoO0 "); else ECHO; }

{NONALPHA}REFINEMENT{POSTNL}	{ if (flag==0) printf(" REFINEMENToO0 "); else ECHO; }

{NONALPHA}SYSTEM{POSTNL}		{ if (flag==0) printf(" SYSTEMoO0 "); else ECHO; }

{NONALPHA}BASE{POSTNL}		{ if (flag==0) printf(" BASEoO0 "); else ECHO; }

{NONALPHA}MACHINE{POSTNL}		{ if (flag==0) printf(" MACHINEoO0 "); else ECHO; }

{NONALPHA}ENUMERATION{POSTNL}	{ if (flag==0) printf(" ENUMERATIONoO0 "); else ECHO; }

{NONALPHA}INTERFACE{POSTNL}	{ if (flag==0) printf(" INTERFACEoO0 "); else ECHO; }

{NONALPHA}REFINES{POSTNL}		{ if (flag==0) printf(" REFINESoO0 "); else ECHO; }

{NONALPHA}DEFINITIONS{POSTNL}	{ if (flag==0) printf(" DEFINITIONSoO0 "); else ECHO; }

{NONALPHA}SETS{POSTNL}		{ if (flag==0) printf(" SETSoO0 "); else ECHO; }

{NONALPHA}CONSTANTS{POSTNL}	{ if (flag==0) printf(" CONSTANTSoO0 "); else ECHO; }

{NONALPHA}PROPERTIES{POSTNL}	{ if (flag==0) printf(" PROPERTIESoO0 "); else ECHO; }

{NONALPHA}CONSTRAINTS{POSTNL}	{ if (flag==0) printf(" CONSTRAINTSoO0 "); else ECHO; }

{NONALPHA}USES{POSTNL}		{ if (flag==0) printf(" USESoO0 "); else ECHO; }

{NONALPHA}SEES{POSTNL}		{ if (flag==0) printf(" SEESoO0 "); else ECHO; }

{NONALPHA}EXTENDS{POSTNL}		{ if (flag==0) printf(" EXTENDSoO0 "); else ECHO; }

{NONALPHA}INCLUDES{POSTNL}	{ if (flag==0) printf(" INCLUDESoO0 "); else ECHO; }

{NONALPHA}IMPORTS{POSTNL}		{ if (flag==0) printf(" IMPORTSoO0 "); else ECHO; }

{NONALPHA}SUPPORTS{POSTNL}	{ if (flag==0) printf(" SUPPORTSoO0 "); else ECHO; }

{NONALPHA}PROMOTES{POSTNL}	{ if (flag==0) printf(" PROMOTESoO0 "); else ECHO; }

{NONALPHA}ASSERTIONS{POSTNL}	{ if (flag==0) printf(" ASSERTIONSoO0 "); else ECHO; }

{NONALPHA}VARIABLES{POSTNL}	{ if (flag==0) printf(" VARIABLESoO0 "); else ECHO; }

{NONALPHA}INITIALISATION{POSTNL}	{ if (flag==0) printf(" INITIALISATIONoO0 "); else ECHO; }

{NONALPHA}OPERATIONS{POSTNL}	{ if (flag==0) printf(" OPERATIONSoO0 "); else ECHO; }



{PRENL}BEGIN{POSTNL}	{ if (flag==0) printf(" 0OoBEGINoO0 "); else ECHO; }
{PRENL}BEGIN{SPORTAB}	{ if (flag==0) printf(" 0OoBEGIN ");    else ECHO; }
{SPORTAB}BEGIN{POSTNL}	{ if (flag==0) printf(" BEGINoO0 ");    else ECHO; }

{PRENL}PRE{POSTNL}	{ if (flag==0) printf(" 0OoPREoO0 "); else ECHO; }
{PRENL}PRE{SPORTAB}	{ if (flag==0) printf(" 0OoPRE ");    else ECHO; }
{SPORTAB}PRE{POSTNL}	{ if (flag==0) printf(" PREoO0 ");    else ECHO; }

{PRENL}IF{POSTNL}	{ if (flag==0) printf(" 0OoIFoO0 "); else ECHO; }
{PRENL}IF{SPORTAB}	{ if (flag==0) printf(" 0OoIF ");    else ECHO; }
{SPORTAB}IF{POSTNL}	{ if (flag==0) printf(" IFoO0 ");    else ECHO; }

{PRENL}CHOICE{POSTNL}	{ if (flag==0) printf(" 0OoCHOICEoO0 "); else ECHO; }
{PRENL}CHOICE{SPORTAB}	{ if (flag==0) printf(" 0OoCHOICE ");    else ECHO; }
{SPORTAB}CHOICE{POSTNL}	{ if (flag==0) printf(" CHOICEoO0 ");    else ECHO; }

{PRENL}SELECT{POSTNL}	{ if (flag==0) printf(" 0OoSELECToO0 "); else ECHO; }
{PRENL}SELECT{SPORTAB}	{ if (flag==0) printf(" 0OoSELECT ");    else ECHO; }
{SPORTAB}SELECT{POSTNL}	{ if (flag==0) printf(" SELECToO0 ");    else ECHO; }

{PRENL}CASE{POSTNL}	{ if (flag==0) printf(" 0OoCASEoO0 "); else ECHO; }
{PRENL}CASE{SPORTAB}	{ if (flag==0) printf(" 0OoCASE ");    else ECHO; }
{SPORTAB}CASE{POSTNL}	{ if (flag==0) printf(" CASEoO0 ");    else ECHO; }

{PRENL}EITHER{POSTNL}	{ if (flag==0) printf(" 0OoEITHERoO0 "); else ECHO; }
{PRENL}EITHER{SPORTAB}	{ if (flag==0) printf(" 0OoEITHER ");    else ECHO; }
{SPORTAB}EITHER{POSTNL}	{ if (flag==0) printf(" EITHERoO0 ");    else ECHO; }

{PRENL}ANY{POSTNL}	{ if (flag==0) printf(" 0OoANYoO0 "); else ECHO; }
{PRENL}ANY{SPORTAB}	{ if (flag==0) printf(" 0OoANY ");    else ECHO; }
{SPORTAB}ANY{POSTNL}	{ if (flag==0) printf(" ANYoO0 ");    else ECHO; }

{PRENL}VAR{POSTNL}	{ if (flag==0) printf(" 0OoVARoO0 "); else ECHO; }
{PRENL}VAR{SPORTAB}	{ if (flag==0) printf(" 0OoVAR ");    else ECHO; }
{SPORTAB}VAR{POSTNL}	{ if (flag==0) printf(" VARoO0 ");    else ECHO; }

{PRENL}LET{POSTNL}	{ if (flag==0) printf(" 0OoLEToO0 "); else ECHO; }
{PRENL}LET{SPORTAB}	{ if (flag==0) printf(" 0OoLET ");    else ECHO; }
{SPORTAB}LET{POSTNL}	{ if (flag==0) printf(" LEToO0 ");    else ECHO; }

{PRENL}WHILE{POSTNL}	{ if (flag==0) printf(" 0OoWHILEoO0 "); else ECHO; }
{PRENL}WHILE{SPORTAB}	{ if (flag==0) printf(" 0OoWHILE ");    else ECHO; }
{SPORTAB}WHILE{POSTNL}	{ if (flag==0) printf(" WHILEoO0 ");    else ECHO; }

{PRENL}THEN{POSTNL}	{ if (flag==0) printf(" 0OoTHENoO0 "); else ECHO; }
{PRENL}THEN{SPORTAB}	{ if (flag==0) printf(" 0OoTHEN ");    else ECHO; }
{SPORTAB}THEN{POSTNL}	{ if (flag==0) printf(" THENoO0 ");    else ECHO; }

{PRENL}WHEN{POSTNL}	{ if (flag==0) printf(" 0OoWHENoO0 "); else ECHO; }
{PRENL}WHEN{SPORTAB}	{ if (flag==0) printf(" 0OoWHEN ");    else ECHO; }
{SPORTAB}WHEN{POSTNL}	{ if (flag==0) printf(" WHENoO0 ");    else ECHO; }

{PRENL}WHERE{POSTNL}	{ if (flag==0) printf(" 0OoWHEREoO0 "); else ECHO; }
{PRENL}WHERE{SPORTAB}	{ if (flag==0) printf(" 0OoWHERE ");    else ECHO; }
{SPORTAB}WHERE{POSTNL}	{ if (flag==0) printf(" WHEREoO0 ");    else ECHO; }

{PRENL}DO{POSTNL}	{ if (flag==0) printf(" 0OoDOoO0 "); else ECHO; }
{PRENL}DO{SPORTAB}	{ if (flag==0) printf(" 0OoDO ");    else ECHO; }
{SPORTAB}DO{POSTNL}		{ if (flag==0) printf(" DOoO0 ");    else ECHO; }

{PRENL}INVARIANT{POSTNL}	{ if (flag==0) printf(" 0OoINVARIANToO0 "); else ECHO; }
{PRENL}INVARIANT{SPORTAB}	{ if (flag==0) printf(" 0OoINVARIANT ");    else ECHO; }
{SPORTAB}INVARIANT{POSTNL}	{ if (flag==0) printf(" INVARIANToO0 ");    else ECHO; }

{PRENL}VARIANT{POSTNL}		{ if (flag==0) printf(" 0OoVARIANToO0 "); else ECHO; }
{PRENL}VARIANT{SPORTAB}		{ if (flag==0) printf(" 0OoVARIANT ");    else ECHO; }
{SPORTAB}VARIANT{POSTNL}	{ if (flag==0) printf(" VARIANToO0 ");    else ECHO; }

{PRENL}OF{POSTNL}	{ if (flag==0) printf(" 0OoOFoO0 "); else ECHO; }
{PRENL}OF{SPORTAB}	{ if (flag==0) printf(" 0OoOF ");    else ECHO; }
{SPORTAB}OF{POSTNL}	{ if (flag==0) printf(" OFoO0 ");    else ECHO; }

{PRENL}IN{POSTNL}	{ if (flag==0) printf(" 0OoINoO0 "); else ECHO; }
{PRENL}IN{SPORTAB}	{ if (flag==0) printf(" 0OoIN ");    else ECHO; }
{SPORTAB}IN{POSTNL}	{ if (flag==0) printf(" INoO0 ");    else ECHO; }

{PRENL}BE{POSTNL}	{ if (flag==0) printf(" 0OoBEoO0 "); else ECHO; }
{PRENL}BE{SPORTAB}	{ if (flag==0) printf(" 0OoBE ");    else ECHO; }
{SPORTAB}BE{POSTNL}	{ if (flag==0) printf(" BEoO0 ");    else ECHO; }

{PRENL}OR{POSTNL}	{ if (flag==0) printf(" 0OoORoO0 "); else ECHO; }
{PRENL}OR{SPORTAB}	{ if (flag==0) printf(" 0OoOR ");    else ECHO; }
{SPORTAB}OR{POSTNL}	{ if (flag==0) printf(" ORoO0 ");    else ECHO; }

{PRENL}ELSE{POSTNL}	{ if (flag==0) printf(" 0OoELSEoO0 "); else ECHO; }
{PRENL}ELSE{SPORTAB}	{ if (flag==0) printf(" 0OoELSE ");    else ECHO; }
{SPORTAB}ELSE{POSTNL}	{ if (flag==0) printf(" ELSEoO0 ");    else ECHO; }

{PRENL}ELSIF{POSTNL}	{ if (flag==0) printf(" 0OoELSIFoO0 "); else ECHO; }
{PRENL}ELSIF{SPORTAB}	{ if (flag==0) printf(" 0OoELSIF ");    else ECHO; }
{SPORTAB}ELSIF{POSTNL}	{ if (flag==0) printf(" ELSIFoO0 ");    else ECHO; }

{PRENL}or{POSTNL}	{ if (flag==0) printf(" 0OooroO0 "); else ECHO; }
{PRENL}or{SPORTAB}	{ if (flag==0) printf(" 0Ooor ");    else ECHO; }
{SPORTAB}or{POSTNL}	{ if (flag==0) printf(" oroO0 ");    else ECHO; }


{PRENL}"&"{POSTNL}	{ if (flag==0) printf(" 0OoampoO0 "); else ECHO; }
{PRENL}"&"{ALPHA}	{ if (flag==0) { printf(" 0Ooamp "); ECHO; }
                          else ECHO; }
{ALPHA}"&"{POSTNL}	{ if (flag==0) { ECHO; printf(" ampoO0 "); }
                          else ECHO; }

{PRENL}","{POSTNL}	{ if (flag==0) printf(" 0OocomoO0 "); else ECHO; }
{PRENL}","{ALPHA}	{ if (flag==0) { printf(" 0Oocom "); ECHO; }
                          else ECHO; }
{ALPHA}","{POSTNL}	{ if (flag==0) { ECHO; printf(" comoO0 "); }
                          else ECHO; }

{PRENL}";"{POSTNL}	{ if (flag==0) printf(" 0OoscoO0 "); else ECHO; }
{PRENL}";"{ALPHA}	{ if (flag==0) { printf(" 0Oosc "); ECHO; }
                          else ECHO; }
{ALPHA}";"{POSTNL}	{ if (flag==0) { ECHO; printf(" scoO0 "); }
                          else ECHO; }

{PRENL}"||"{POSTNL}	{ if (flag==0) printf(" 0OoparoO0 "); else ECHO; }
{PRENL}"||"{ALPHA}	{ if (flag==0) { printf(" 0Oopar "); ECHO; }
                          else ECHO; }
{ALPHA}"||"{POSTNL}	{ if (flag==0) { ECHO; printf(" paroO0 "); }
                          else ECHO; }

{PRENL}"="{POSTNL}	{ if (flag==0) printf(" 0OoeqoO0 "); else ECHO; }
{PRENL}"="{ALPHA}	{ if (flag==0) { printf(" 0Ooeq "); ECHO; }
                          else ECHO; }
{ALPHA}"="{POSTNL}	{ if (flag==0) { ECHO; printf(" eqoO0 "); }
                          else ECHO; }

{PRENL}"=>"{POSTNL}	{ if (flag==0) printf(" 0OoimploO0 "); else ECHO; }
{PRENL}"=>"{ALPHA}	{ if (flag==0) { printf(" 0Ooimpl "); ECHO; }
                          else ECHO; }
{ALPHA}"=>"{POSTNL}	{ if (flag==0) { ECHO; printf(" imploO0 "); }
                          else ECHO; }

{PRENL}"<=>"{POSTNL}	{ if (flag==0) printf(" 0OoiffoO0 "); else ECHO; }
{PRENL}"<=>"{ALPHA}	{ if (flag==0) { printf(" 0Ooiff "); ECHO; }
                          else ECHO; }
{ALPHA}"<=>"{POSTNL}	{ if (flag==0) { ECHO; printf(" iffoO0 "); }
                          else ECHO; }

{PRENL}":="{POSTNL}	{ if (flag==0) printf(" 0OocoleqloO0 "); else ECHO; }
{PRENL}":="{ALPHA}	{ if (flag==0) { printf(" 0Oocoleql "); ECHO; }
                          else ECHO; }
{ALPHA}":="{POSTNL}	{ if (flag==0) { ECHO; printf(" coleqloO0 "); }
                          else ECHO; }

{PRENL}"<--"{POSTNL}	{ if (flag==0) printf(" 0OosnteroO0 "); else ECHO; }
{PRENL}"<--"{ALPHA}	{ if (flag==0) { printf(" 0Oosnter "); ECHO; }
                          else ECHO; }
{ALPHA}"<--"{POSTNL}	{ if (flag==0) { ECHO; printf(" snteroO0 "); }
                          else ECHO; }

