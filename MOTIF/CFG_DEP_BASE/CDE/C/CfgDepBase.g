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
int CfgDepBaseP1 = CfgDepBasePV1;
int CfgDepBaseP2 = CfgDepBasePV2;
int CfgDepBaseP3 = CfgDepBasePV3;
int CfgDepBaseP4 = CfgDepBasePV4;
int CfgDepBaseP5 = CfgDepBasePV5;
int CfgDepBaseP6 = CfgDepBasePV6;
char * CfgDepBaseP7 [] = CfgDepBasePV7;
char * CfgDepBaseP8 [] = CfgDepBasePV8;


#define CfgDepBase_VffncPV1 { "CfgDepBase_SETOBJ\\/CfgDepBase_SEQOBJ" }
#define CfgDepBase_VffncPV2 7

#include "CfgDepBase_Vffnc.g"

#include "Construct_ffnc_ctx.g"

#define Construct_ffnc_objPV1 { "CfgDepBase_STROBJ\\/CfgDepBasePV7\\/CfgDepBasePV8\\/CfgDepBase_SETOBJ\\/Abs2Conc_FNCOBJ\\/Construct_FNCOBJ\\/0..2147483646\\/MRIState_FNCOBJ\\/GENState_FNCOBJ" }
#define Construct_ffnc_objPV2 12
#define Construct_ffnc_objPV3 CfgDepBasePV1

#include "Construct_ffnc_obj.g"

#include "Abs2Conc_ffnc_ctx.g"

#define Abs2Conc_ffnc_objPV1 { "CfgDepBase_SEQOBJ" }
#define Abs2Conc_ffnc_objPV2 1
#define Abs2Conc_ffnc_objPV3 CfgDepBasePV2

#include "Abs2Conc_ffnc_obj.g"

#include "MRIState_ffnc_ctx.g"

#define MRIState_ffnc_objPV1 { "BOOL\\/CfgDepBase_SEQOBJ\\/CfgDepBase_SETOBJ" }
#define MRIState_ffnc_objPV2 7
#define MRIState_ffnc_objPV3 CfgDepBasePV3

#include "MRIState_ffnc_obj.g"

#include "GENState_ffnc_ctx.g"

#define GENState_ffnc_objPV1 { "BOOL" }
#define GENState_ffnc_objPV2 3
#define GENState_ffnc_objPV3 CfgDepBasePV4

#include "GENState_ffnc_obj.g"

#include "Seqstr_ffnc_ctx.g"

#define Seqstr_ffnc_objPV1 { "CfgDepBase_SEQOBJ" }
#define Seqstr_ffnc_objPV2 1
#define Seqstr_ffnc_objPV3 CfgDepBasePV5

#include "Seqstr_ffnc_obj.g"

#include "String_ffnc_ctx.g"

#define String_ffnc_objPV1 { "CfgDepBase_STROBJ" }
#define String_ffnc_objPV2 1
#define String_ffnc_objPV3 CfgDepBasePV6

#include "String_ffnc_obj.g"

#include "CfgDepBase_seq_ctx.g"

#define CfgDepBase_seq_objPV1 { "Construct_FNCOBJ\\/0..2147483646\\/String_FNCOBJ" }
#define CfgDepBase_seq_objPV2 (8+CfgDepBasePV2+5+CfgDepBasePV3+5+CfgDepBasePV5+5+5)
#define CfgDepBase_seq_objPV3 (175+10*(CfgDepBasePV2+5)+25*(CfgDepBasePV3+5)+50*(CfgDepBasePV5+5)+260)

#include "CfgDepBase_seq_obj.g"

#include "CfgDepBase_str_ctx.g"

#define CfgDepBase_str_objPV1 (CfgDepBasePV1+CfgDepBasePV6+5)
#define CfgDepBase_str_objPV2 (30*(CfgDepBasePV1+1)+75*(CfgDepBasePV6+1))

#include "CfgDepBase_str_obj.g"

#include "CfgDepBase_set_ctx.g"

#define CfgDepBase_set_objPV1 { "Construct_FNCOBJ\\/0..2147483646" }
#define CfgDepBase_set_objPV2 (5+2*CfgDepBasePV1+2*CfgDepBasePV3)
#define CfgDepBase_set_objPV3 (500+40*CfgDepBasePV1+50*CfgDepBasePV3)

#include "CfgDepBase_set_obj.g"

#define CfgDepBase_token_ioPV1 { "String_FNCOBJ\\/CfgDepBase_STROBJ\\/Seqstr_FNCOBJ\\/CfgDepBase_SEQOBJ\\/GENState_FNCOBJ\\/MRIState_FNCOBJ\\/CfgDepBase_SETOBJ\\/Abs2Conc_FNCOBJ\\/Construct\\/Construct_FNCOBJ\\/CfgDepBase_STROBJ\\/CfgDepBasePV7\\/CfgDepBasePV8\\/Abs2Conc_FNCOBJ\\/Construct_FNCOBJ\\/MRIState_FNCOBJ\\/GENState_FNCOBJ\\/0..2147483646" }

#include "CfgDepBase_token_io.g"

