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
               semantic descriptions of the two operators n2u, n2n
               moved here from Uns_TYPE to aid efficiency pf proof.
*/

MACHINE           Uns_SEMANTICS

SEES              Uns_TYPE

PROPERTIES

/*"
We define the {\em NAT\/} to {\em UNSIGNED\/} conversion function
as a bijection between natural numbers in the range {\em 0\/}
to {\em 65535\/} and {\em UNSIGNED\/} (i.e.\  there is
a 1-to-1 correspondence between the two);
the {\em UNSIGNED\/} to {\em NAT\/} function
may then be defined as the inverse:
"*/

  !uns.(uns:UNSIGNED => n2u(u2n(uns)) = uns) &
  !nat.(nat:NAT&nat<=65535 => u2n(n2u(nat)) = nat)

END
