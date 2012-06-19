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
extern char * _CfgDepCtx_CONSTRUCT [];
extern char * _CfgDepCtx_MRISTATE [];
extern char * _CfgDepCtx_GENSTATE [];
extern char * _CfgDepCtx_EXTENSION [];
extern char * _CfgDepCtx_TYPE [];

#define CONSTRUCT _CfgDepCtx_CONSTRUCT
#define MRISTATE _CfgDepCtx_MRISTATE
#define GENSTATE _CfgDepCtx_GENSTATE
#define EXTENSION _CfgDepCtx_EXTENSION
#define TYPE _CfgDepCtx_TYPE

#define mch 1
#define ref 2
#define imp 3
#define bse 4
#define itf 5
#define enm 6
#define doc 7
#define ops 8
#define mch_prf 9
#define ref_prf 10
#define imp_prf 11
#define map 12
#define usr 1
#define lib 2
#define bse_gen 3
#define enm_gen 4
#define itf_gen 5
#define prf_gen 6
#define usr_vhdl 7
#define gen_vhdl 8
#define lib_vhdl 9

void INI_CfgDepCtx();
