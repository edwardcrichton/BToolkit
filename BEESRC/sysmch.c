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
int recsys,retsys,reloadsys,batchsys,loadedsys,theosys,rulsys,mensys;

#define val_rec_sys    recsys

#define mod_rec_sys(b) recsys=b

#define val_ret_sys    retsys

#define mod_ret_sys(b) retsys=b

#define val_reload_sys    reloadsys

#define mod_reload_sys(b) reloadsys=b

#define val_loaded_sys    loadedsys

#define mod_loaded_sys(b) loadedsys=b

#define val_theo_sys    theosys

#define mod_theo_sys(b) theosys=b

#define val_rul_sys    rulsys

#define mod_rul_sys(b) rulsys=b

#define ini_sys        recsys=FALSE;retsys=FALSE;reloadsys=FALSE;loadedsys=FALSE;theosys=0;rulsys=0

#define re_ini_sys        recsys=FALSE;retsys=FALSE;reloadsys=FALSE;loadedsys=FALSE

#define val_batch_sys      batchsys

#define mod_batch_sys(b)   batchsys=b

#define val_men_sys      mensys

#define mod_men_sys(b)   mensys=b
