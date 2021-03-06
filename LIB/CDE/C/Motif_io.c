/*Copyright (c) 1985-2012, B-Core (UK) Ltd

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
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


