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
int btl_proofP1 = btl_proofPV1;
int btl_proofP2 = btl_proofPV2;


#include "btl_prf_ffnc_ctx.g"

#define btl_prf_ffnc_objPV1 { "btl_proof_STROBJ\\/0..2147483646\\/btl_proof_SEQOBJ" }
#define btl_prf_ffnc_objPV2 4
#define btl_prf_ffnc_objPV3 btl_proofPV1

#include "btl_prf_ffnc_obj.g"

#include "prf_seq_stp_ffnc_ctx.g"

#define prf_seq_stp_ffnc_objPV1 { "0..2147483646\\/btl_proof_STROBJ" }
#define prf_seq_stp_ffnc_objPV2 4
#define prf_seq_stp_ffnc_objPV3 btl_proofPV2

#include "prf_seq_stp_ffnc_obj.g"

#include "btl_proof_seq_ctx.g"

#define btl_proof_seq_objPV1 { "prf_seq_stp_FNCOBJ" }
#define btl_proof_seq_objPV2 (btl_proofPV1+5+5)
#define btl_proof_seq_objPV3 (25*(btl_proofPV1+5)+25)

#include "btl_proof_seq_obj.g"

#include "btl_proof_str_ctx.g"

#define btl_proof_str_objPV1 (btl_proofPV1+2*btl_proofPV2+5)
#define btl_proof_str_objPV2 (25*(btl_proofPV1+1)+125*(btl_proofPV2+2))

#include "btl_proof_str_obj.g"

