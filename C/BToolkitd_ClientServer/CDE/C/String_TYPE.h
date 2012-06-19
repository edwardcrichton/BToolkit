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
extern char * _String_TYPE_CHAR [];
extern char * _String_TYPE_STRING [];

#define CHAR _String_TYPE_CHAR
#define STRING _String_TYPE_STRING

#define B_SOH 1
#define B_STX 2
#define B_ETX 3
#define B_EOT 4
#define B_ENQ 5
#define B_ACK 6
#define B_BEL 7
#define B_BS  8
#define B_HT  9
#define B_LF  10
#define B_VT  11
#define B_FF  12
#define B_CR  13
#define B_SO  14
#define B_SI  15
#define B_DLE 16
#define B_DC1 17
#define B_DC2 18
#define B_DC3 19
#define B_DC4 20
#define B_NAK 21
#define B_SYN 22
#define B_ETB 23
#define B_CAN 24
#define B_EM  25
#define B_SUB 26
#define B_ESC 27
#define B_FS  28
#define B_GS  29  
#define B_RS  30
#define B_US  31

#define B_SPACE 32
#define B_EXCL  33 /* ! */ 
#define B_QUOT  34 /* " */
#define B_HSH   35 /* # */
#define B_DOLL  36 /* $ */
#define B_PCT   37 /* % */
#define B_AMP   38 /* & */
#define B_SQUOT 39 /* ' */
#define B_OPAR  40 /* ( */
#define B_CPAR  41 /* ) */
#define B_MUL   42 /* * */
#define B_PLUS  43 /* + */
#define B_COM   44 /* , */
#define B_MINUS 45 /* - */
#define B_DOT   46 /* . */
#define B_DIV   47 /* / */

#define B_COL  58  /* : */
#define B_SCOL 59  /* ; */
#define B_LESS 60  /* < */
#define B_EQL  61  /* = */
#define B_GTR  62  /* > */
#define B_QUERY 63 /* ? */
#define B_CADD 64  /* @ */

#define B_OBRK 91  /* [ */
#define B_SLSH 92  /* \ */
#define B_CBRK 93  /* ] */
#define B_HAT  94  /* ^ */
#define B_UNL  95  /* _ */
#define B_BSQ  96  /* ` */

#define B_OBRC 123  /* { */
#define B_BAR  124  /* | */
#define B_CBRC 125  /* } */
#define B_TLD  126  /* ~ */
#define B_DEL  127

void INI_String_TYPE();
