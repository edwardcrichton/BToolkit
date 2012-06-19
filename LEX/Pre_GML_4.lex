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


WS	[ \t\n]*

%%

","{WS}"comoO0"		{ printf(" comoO0 "); }
"&"{WS}"ampoO0"		{ printf(" ampoO0 "); }
";"{WS}"scoO0"		{ printf(" scoO0 "); }
"||"{WS}"paroO0"	{ printf(" paroO0 "); }
"="{WS}"eqoO0"		{ printf(" eqoO0 "); }
"=>"{WS}"imploO0"	{ printf(" imploO0 "); }
"<=>"{WS}"iffoO0"	{ printf(" iffoO0 "); }
"or"{WS}"oroO0"		{ printf(" oroO0 "); }
":="{WS}"coleqloO0"	{ printf(" coleqloO0 "); }
"<--"{WS}"snteroO0"	{ printf(" snteroO0 "); }

"0Oocom"{WS}","		{ printf(" 0Oocom "); }
"0Ooamp"{WS}"&"		{ printf(" 0Ooamp "); }
"0Oosc"{WS}";"		{ printf(" 0Oosc "); }
"0Oopar"{WS}"||"	{ printf(" 0Oopar "); }
"0Ooeq"{WS}"="		{ printf(" 0Ooeq "); }
"0Ooimpl"{WS}"=>"	{ printf(" 0Ooimpl "); }
"0Ooiff"{WS}"<=>"	{ printf(" 0Ooiff "); }
"0Ooor"{WS}"or"		{ printf(" 0Ooor "); }
"0Oocoleql"{WS}":="	{ printf(" 0Oocoleql "); }
"0Oosnter"{WS}"<--"	{ printf(" 0Oosnter "); }
