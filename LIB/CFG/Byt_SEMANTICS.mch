/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit Beta 4.52
  DATE:             12/07/99
***/

/*
Description: Library Type semantics machine

History :
120799 v0.01 : Created.
               semantic descriptions of the four operators n2b, b2n, b2bl, bl2b
               moved here from Byt_TYPE to aid efficiency pf proof.
*/

MACHINE           Byt_SEMANTICS

SEES              Byt_TYPE, Bool_TYPE

PROPERTIES

/*"
We define the {\em NAT\/} to {\em BYTE\/} conversion function
as a bijection between natural numbers in the range {\em 0\/}
to {\em 255\/} and {\em BYTE\/} (i.e.\  there is
a 1-to-1 correspondence between the two);
the {\em BYTE\/} to {\em NAT\/} function
may then be defined as the inverse:
"*/

  !byt.(byt:BYTE => n2b(b2n(byt)) = byt) &
  !nat.(nat:NAT&nat<=255 => b2n(n2b(nat)) = nat) &

  b2bl(n2b(0)) = FALSE &
  !byt.(byt:BYTE & not(byt=n2b(0)) => b2bl(byt) = TRUE) &
  bl2b(FALSE) = n2b(0) &
  bl2b(TRUE) = n2b(1)

END
