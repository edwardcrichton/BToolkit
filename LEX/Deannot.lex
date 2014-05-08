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
%e 1500
%p 3750
%k  100
%a 1500
%o 1000

        /***
           Deannot
        ***/

%%

70OoampoO07     { printf("&"); }
0OoampoO0       { printf("&"); }
0Ooamp          { printf("&"); }
ampoO0          { printf("&"); }

70OocomoO07     { printf(","); }
0OocomoO0       { printf(","); }
0Oocom          { printf(","); }
comoO0          { printf(","); }

70OoparoO07     { printf("||"); }
0OoparoO0       { printf("||"); }
0Oopar          { printf("||"); }
paroO0          { printf("||"); }

0OoeqoO0     { printf("="); }
0Ooeq        { printf("="); }
eqoO0        { printf("="); }

0OoimploO0     { printf("=>"); }
0Ooimpl        { printf("=>"); }
imploO0        { printf("=>"); }

0OoiffoO0     { printf("<=>"); }
0Ooiff        { printf("<=>"); }
iffoO0        { printf("<=>"); }

0OooroO0     { printf("or"); }
0Ooor        { printf("or"); }
oroO0        { printf("or"); }

0OocoleqloO0     { printf(":="); }
0Oocoleql        { printf(":="); }
coleqloO0        { printf(":="); }

0OosnteroO0     { printf("<--"); }
0Oosnter        { printf("<--"); }
snteroO0        { printf("<--"); }

70OoscoO07        { printf(";"); }
[ ]0OoscoO0       { printf(";"); }
[ ]0Oosc          { printf(";"); }
[ ]scoO0          { printf(";"); }
0OoscoO0          { printf(";"); }
0Oosc             { printf(";"); }
scoO0             { printf(";"); }

0Oo              { ; }
oO0              { ; }

[ ]*"_?_oO00Oo_?_"[ ]*   { ; }

[ ]*\"0QjKOo[ ]*       { printf("\""); }
[ ]*oOKjQ0\"[ ]*       { printf("\""); }
