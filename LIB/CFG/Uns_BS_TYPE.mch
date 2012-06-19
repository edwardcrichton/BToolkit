/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
***/

/*
Description: Library Type machine extending Uns_TYPE to include BitString ops

History :
030698 v0.01 : Created.
*/

MACHINE       Uns_BS_TYPE

EXTENDS       Uns_TYPE

/*"
This specification is an extension of {\em Uns\_Type\/}, providing
the four bit manipulation functions {\em UAND, UOR, UXOR and UNOT\/}.
"*/

SEES          Byt_BS_TYPE

/*"
Since one of the parameters of the {\em UXTR\/} and {\em USET\/}
functions is a {\em BYTE\/}, we also have {\em Byt\_BS\_TYPE\/} in scope:
"*/

CONSTANTS

/*"
We now introduce the two conversion functions between {\em UNSIGNED\/}
and their `bit-sequence' representation:
"*/

  u2bs, bs2u

/*"
Since {\em Byt\_BS\_TYPE\/} is in scope, we have access to the bit
manipulation functions {\em bnd, bor, bxr\/} and {\em bcp\/}.
"*/


PROPERTIES

/*"
In order to provide the bit-manipulation operations we define {\em u2bs\/}
as the bijection between {\em UNSIGNED\/} and its bit-sequence value, and
{\em bs2u\/} as its inverse:
"*/

  u2bs : UNSIGNED >->> /* {ss | ss : seq {0,1} & size(ss) = 16} */ (1..16 --> {0,1}) &
/* !bb.(bb:UNSIGNED => (bb = n2b(SIGMA(ii).(ii:1..16 | 2^^(16-ii) * b2s(bb))))) & */
  bs2u = u2bs~ &

/*"
Finally we define the bit functions {\em bnd, bor, bxr\/} and {\em bcp\/}:
\newpage
"*/

  bnd = {(0|->0) |-> 0, (0|->1) |-> 0, (1|->0) |-> 0, (1|->1) |-> 1} &
  bor = {(0|->0) |-> 0, (0|->1) |-> 1, (1|->0) |-> 1, (1|->1) |-> 1} &
  bxr = {(0|->0) |-> 0, (0|->1) |-> 1, (1|->0) |-> 1, (1|->1) |-> 0} &
  bcp = {0 |-> 1, 1 |-> 0}

OPERATIONS

/*"
Each of the four bit manipulation operations has precondition that the
 input variables are of type {\em UNSIGNED\/}; in each case an {\em UNSIGNED\/}
value is returned.\\[1ex]

{\bf UAND}:\ \ \  translated as:\\{\tt rr := UAND(aa,bb)}\\
"*/
  rr <-- UAND(aa : UNSIGNED & bb : UNSIGNED) =
    BEGIN rr := bs2u((u2bs(aa) >< u2bs(bb)) ; bnd) END;

/*"
\newpage
{\bf UOR}:\ \ \  translated as:\\{\tt rr := UOR(aa,bb)}\\
"*/
  rr <-- UOR(aa : UNSIGNED & bb : UNSIGNED) =
    BEGIN rr := bs2u((u2bs(aa) >< u2bs(bb)) ; bor) END;

/*"
{\bf UXOR}:\ \ \  translated as:\\{\tt rr := UXOR(aa,bb)}\\
"*/
  rr <-- UXOR(aa : UNSIGNED & bb : UNSIGNED) =
    BEGIN rr := bs2u((u2bs(aa) >< u2bs(bb)) ; bxr) END;

/*"
{\bf UNOT}:\ \ \  translated as:\\{\tt rr := UNOT(aa)}\\
"*/
  rr <-- UNOT(aa : UNSIGNED) =
    BEGIN rr := bs2u(u2bs(aa) ; bcp) END

END
