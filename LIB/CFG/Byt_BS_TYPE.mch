/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
v0.02
  VERSION:          B-Toolkit Beta 4.32
  DATE:             09/01/99
v0.03
  VERSION:          B-Toolkit Beta 4.32
  DATE:             15/02/99
***/

/*
Description: Library Type machine extending Byt_TYPE to include BitString ops

History :
030698 v0.01 : Created.
090199 v0.02 : added: exp, SETBIT, RESETBIT
150299 v0.03 : added: SEES Bool_TYPE
*/

MACHINE           Byt_BS_TYPE

EXTENDS           Byt_TYPE

/*"
This specification is an extension of {\em Byt\_Type\/}, providing
the four bit manipulation functions {\em BAND, BOR, BXOR and BNOT\/},
using the {\em BYTE\/}-`bit-sequence' constants
{\em b2bs\/} and {\em bs2b\/} together with four bit manipulation
functions {\em bnd, bor, bxr\/} and {\em bcp\/}.

The additional operations provide the four bit
manipulation functions {\em BAND, BOR, BXOR and BNOT\/}.
"*/

SEES              Bool_TYPE

/*"
Required because of {\em b2bl\/} and {\em  bl2b\/} in {\em Byt\_TYPE\/}
"*/

CONSTANTS

/*"
We introduce the two conversion functions between {\em BYTE\/}
and their `bit-sequence' representation:
"*/

  b2bs, bs2b,

/*"
and the bit manipulation functions for `and', `or', `xor' and `complement':
"*/

  bnd, bor, bxr, bcp

/*
/?"
We finally introduce the exponential function:
"?/

  exp
*/

PROPERTIES

/*"
In order to provide the bit-manipulation operations we define {\em b2bs\/}
as the bijection between {\em BYTE\/} and its bit-sequence value, and
{\em bs2b\/} as its inverse:
"*/

  b2bs : BYTE >->> /* {ss | ss : seq {0,1} & size(ss) = 8} */ (1..8 --> {0,1}) &
/* !bb.(bb:BYTE => (bb = n2b(SIGMA(ii).(ii:1..8 | 2^^(8-ii) * b2bs(bb))))) & */
  bs2b = b2bs~ &

/*"
We define the bit functions {\em bnd, bor, bxr\/} and {\em bcp\/}:
\newpage
"*/

  bnd = {(0|->0) |-> 0, (0|->1) |-> 0, (1|->0) |-> 0, (1|->1) |-> 1} &
  bor = {(0|->0) |-> 0, (0|->1) |-> 1, (1|->0) |-> 1, (1|->1) |-> 1} &
  bxr = {(0|->0) |-> 0, (0|->1) |-> 1, (1|->0) |-> 1, (1|->1) |-> 0} &
  bcp = {0 |-> 1, 1 |-> 0}

/*
/?"
We now axiomatize the {\em exp\/} function:
"?/
   exp : NAT * NAT --> NAT &
   !(xx,nn). ( xx : NAT & nn : NAT => ( 
               exp(xx,0) = 1 &
               exp(xx,nn+1) = exp(xx,nn) * nn )
             )
*/
   
OPERATIONS

/*"
Each of the first four bit manipulation operations has precondition
that the input variables are of type {\em BYTE\/}; in
each case a {\em BYTE\/} value is returned.\\[1ex]

{\bf BAND}:\ \ \  translated as:\\{\tt rr := BAND(aa,bb)}\\
"*/
  rr <-- BAND(aa : BYTE & bb : BYTE) =
    BEGIN rr := bs2b((b2bs(aa) >< b2bs(bb)) ; bnd) END;

/*"
{\bf BOR}:\ \ \  translated as:\\{\tt rr := BOR(aa,bb)}\\
"*/
  rr <-- BOR(aa : BYTE & bb : BYTE) =
    BEGIN rr := bs2b((b2bs(aa) >< b2bs(bb)) ; bor) END;

/*"
{\bf BXOR}:\ \ \  translated as:\\{\tt rr := BXOR(aa,bb)}\\
"*/
  rr <-- BXOR(aa : BYTE & bb : BYTE) =
    BEGIN rr := bs2b((b2bs(aa) >< b2bs(bb)) ; bxr) END;

/*"
\newpage
{\bf BNOT}:\ \ \  translated as:\\{\tt rr := BNOT(aa)}\\
"*/
  rr <-- BNOT(aa : BYTE) =
    BEGIN rr := bs2b(b2bs(aa) ; bcp)  END;

/*"
The last two bit manipulation operations take a bit position and a
{\em BYTE\/}, with precondition that the {\em bit\/} is no bigger than
$7$; in each case a {\em BYTE\/} value is returned. HOWEVER, in order
that the operations may be translated in-line, the bit position parameter
must be a {\em number\/} and not an {\em identifier\/}; the latter
will be rejected by the translator\\[1ex]

{\bf ISBITSET}:\ \ \  translated (effectively) as:\\{\tt bb := b2bl(BAND(aa,bb))}\\
where {\em bb\/} is a {\em BYTE\/} whose bits are all $0$ except
that at position {\em bit\/} which is $1$\\
"*/
  bb <-- ISBITSET(bit : BYTE & aa : BYTE) =
    PRE b2n(bit) : 0..7 THEN
      bb := bool ( b2bs(aa) (b2n(bit)+1) = 1 )
    END;

/*"
{\bf SETBIT}:\ \ \  translated as:\\{\tt rr := BOR(aa,bb)}\\
where {\em bb\/} is a {\em BYTE\/} whose bits are all $0$ except
that at position {\em bit\/} which is $1$\\
"*/
  rr <-- SETBIT(bit : BYTE & aa : BYTE) =
    PRE b2n(bit) : 0..7 THEN
      rr := bs2b(b2bs(aa) <+ {b2n(bit)+1 |-> 1})
    END;

/*"
{\bf RESETBIT}:\ \ \  translated as:\\{\tt rr := BAND(aa,bb)}\\
where {\em bb\/} is a {\em BYTE\/} whose bits are all $1$ except
that at position {\em bit\/} which is $0$\\
"*/
  rr <-- RESETBIT(bit : BYTE & aa : BYTE) =
    PRE b2n(bit) : 0..7 THEN
      rr :=bs2b(b2bs(aa) <+ {b2n(bit)+1 |-> 0})
    END

END

