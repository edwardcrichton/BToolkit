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
#define max_sym_val             22400
			     /* multiple of 128? */
 

/*  Maximum Number of THEORIES  */
#define max_the_val              1256

 
/*  Maximum Number of RULES  */
/* #define max_rul_val             8029 */
/* #define max_rul_val            10029 */
/* #define max_rul_val            15029 */
#define max_rul_val            30029


/*  Maximum Number of GOALS  */
/* #define max_gol_val             15013 */
#define max_gol_val             50075

 
/*  Maximum Number of NODES  */
/* #define max_nod_val             19019 */
/* #define max_nod_val             25019 */
#define max_nod_val             60109


/*  Maximum Number of TACTICS  */
#define max_tac_val            20123


/*  Maximum Number of HYPOTHESES  */
#define max_hyp_val             3037


/*  Maximum Number of SEQUENCES  */
/* #define max_seq_val            125013 */
#define max_seq_val            250011
