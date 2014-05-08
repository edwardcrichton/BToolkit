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
	   Pre_GML_5:
             tidies up after Pre_GML_4
	***/

WS	[ \t\n]*

%%

"70OoscoO07"{WS}":="{WS}"70OoscoO07"		{ printf("70OoscoO07 777770Oo77_7_77oO077777 := 777770Oo77_7_77oO077777 70OoscoO07 "); }
"70OoscoO07"{WS}"0OocoleqloO0"{WS}"70OoscoO07"	{ printf("70OoscoO07 777770Oo77_7_77oO077777 0Oocoleql 777770Oo77_7_77oO077777 70OoscoO07 "); }
"70OoscoO07"{WS}"coleqloO0"{WS}"70OoscoO07"	{ printf("70OoscoO07 777770Oo77_7_77oO077777 := 777770Oo77_7_77oO077777 70OoscoO07 "); }
"70OoscoO07"{WS}"0Oocoleql"{WS}"70OoscoO07"	{ printf("70OoscoO07 777770Oo77_7_77oO077777 0Oocoleql 777770Oo77_7_77oO077777 70OoscoO07 "); }

":="{WS}"70OoscoO07"		{ printf(":= 777770Oo77_7_77oO077777 70OoscoO07 "); }
"0OocoleqloO0"{WS}"70OoscoO07"	{ printf("0Oocoleql 777770Oo77_7_77oO077777 70OoscoO07 "); }
"coleqloO0"{WS}"70OoscoO07"	{ printf(":= 777770Oo77_7_77oO077777 70OoscoO07 "); }
"0Oocoleql"{WS}"70OoscoO07"	{ printf("0Oocoleql 777770Oo77_7_77oO077777 70OoscoO07 "); }

"70OoscoO07"{WS}":="		{ printf("70OoscoO07 777770Oo77_7_77oO077777 := "); }
"70OoscoO07"{WS}"0OocoleqloO0"	{ printf("70OoscoO07 777770Oo77_7_77oO077777 0Oocoleql "); }
"70OoscoO07"{WS}"coleqloO0"	{ printf("70OoscoO07 777770Oo77_7_77oO077777 := "); }
"70OoscoO07"{WS}"0Oocoleql"	{ printf("70OoscoO07 777770Oo77_7_77oO077777 0Oocoleql "); }

