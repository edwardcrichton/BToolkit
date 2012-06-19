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
extern int Rename_setP2;
extern int Rename_setP1;
extern int Rename_sset[];
extern int Rename_scrd;
#define INI_Rename_set()          {Rename_scrd = 0;}
#define Rename_CLR_SET()          {Rename_scrd = 0;}
#define Rename_FUL_SET(bb)        {*(bb) = \
                                  ((Rename_scrd == Rename_setP2)!=0);}
#define Rename_XST_IDX_SET(bb,ii) {*(bb) = ((ii <= Rename_scrd)!=0);}
#define Rename_CRD_SET(nn)        {*(nn) = Rename_scrd;}
#define Rename_VAL_SET(vv,ii)     {*(vv) = Rename_sset[ii];}
#define Rename_ANY_SET(vv)     {*(vv) = Rename_sset[1];}
#define Rename_EMP_SET(bb) {*(bb) = ((Rename_scrd == 0)!=0);}

void Rename_SAV_SET();
void Rename_SAVN_SET();
void Rename_RST_SET();
void Rename_RSTN_SET();
void Rename_ENT_SET();
void Rename_RMV_SET();
void Rename_MBR_SET();
