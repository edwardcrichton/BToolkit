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
#include "Motif_io.h"

#include "String_TYPE.h"

/*
  Do not edit above this comment or the operation headers
  (except to remove entire operations)

  Operations in this file should not appear in "Motif_io.h"
  Remove all comments that should not appear in SLIB modules
*/

INI_Motif_io()
{
	;
}


/* ANSIC header */
Motif_PUT_NAT( int nn )
/* end ANSIC header */

/* non-ANSIC header */
Motif_PUT_NAT( nn )
int	nn;
/* end non-ANSIC header */
{
        if ( nn < 0 ) {
          nn = ( -1 * nn );
	  strcpy (  buf___, "-" );
	}
        else {
	  strcpy (  buf___, "" );
	};
	AppNumToBuf___ ( nn );
	DisplayMWText___ ( buf___ );
}


/* ANSIC header */
Motif_NWL( int nn )
/* end ANSIC header */

/* non-ANSIC header */
Motif_NWL( nn )
int	nn;
/* end non-ANSIC header */
{
	while ( nn ) {
		DisplayMWText___ ( "\n" );
		nn--;
	}
}


/* ANSIC header */
Motif_BLK( int nn )
/* end ANSIC header */

/* non-ANSIC header */
Motif_BLK( nn )
int	nn;
/* end non-ANSIC header */
{
	while ( nn ) {
		DisplayMWText___ ( " " );
		nn--;
	}
}


