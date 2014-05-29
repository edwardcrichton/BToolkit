/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
v0.02
  VERSION:          B-Toolkit Beta 4.51
  DATE:             18/06/99
v0.03
  VERSION:          B-Toolkit Beta 4.52
  DATE:             12/07/99
v0.04
  VERSION:          B-Toolkit 5.0.14
  DATE:             15/01/01
***/

/*
Description: Library Type machine intruducing UNSIGNED

History :
180299 v0.01 : Created.
130699 v0.02 : change in PROPERTIES:
  !nat.(nat:NAT => u2n(n2u(nat)) = nat) ->
    !nat.(nat:NAT&nat<=65535 => u2n(n2u(nat)) = nat)
120799 v0.03 : created Uns_SEMANTICS.mch & changed this TYPE machine
               so that mimimal semantic information is given here (to
               increase the efficiency of the provers - semantic information
               is mirrored in the PASP mathematical library)
150101 v0.04 : Changes for DecCo8.
               Properties reduced to minimal type information; full
               properies given in Uns_SEMANTICS.mch
               Changed n2u/u2n from --> to >->> in line with Uns_SEMANTICS.mch.
               Added operations ULEFT and URIGHT
*/

MACHINE       Uns_TYPE

/*"
This specification models the built-in PASP {\em UNSIGNED\/}
type using the two conversion {\em UNSIGNED-NAT\/} functions
{\em n2u\/} and {\em u2n\/}. {\em MinUnsigned\/} and {\em MaxUnsigned\/}
are also defined, as are the {\em UNSIGNED\/}-`bit-sequence' functions
{\em u2bs\/} and {\em bs2u\/} together with four bit manipulation
functions {\em bnd, bor, bxr\/} and {\em bcp\/}.

Each of the operations is translated directly to its PASP equivalent
by the B-PASP Translator; the exceptions are {\em UINC\/} and {\em
UDEC\/} which are translated in terms of {\em BADD\/} and {\em BSUB\/}.

The constants {\em n2u\/} and {\em  u2n\/}
are also introduced, being defined in the {\em Uns_SEMANTICS\/} machine.
"*/

SEES          Bool_TYPE

/*"
Since some operations return a {\em BOOLEAN\/}
we ensure that the {\em Bool\_TYPE\/} machine is in scope, and since
one of the parameters of the {\em UXTR\/} and {\em USET\/} functions
is a {\em BYTE\/}, we also have {\em Byt\_TYPE\/} in scope:
"*/

SETS          UNSIGNED

/*"
We introduce the set {\em UNSIGNED\/}:
"*/

CONSTANTS

/*"
We now introduce the two conversion functions between {\em UNSIGNED\/}
and {\em NAT\/}:
"*/

  n2u, u2n

PROPERTIES

/*"
We give minimal properties here - full semantic information
is contained in {\em Uns\_SEMANTICS.mch\/}:
"*/

   n2u : 0..65535 >->> UNSIGNED &

   u2n : UNSIGNED >->> 0..65535

DEFINITIONS

   MinUns == n2u(0);
   MaxUns == n2u(65535)

OPERATIONS

/*"
Each of the following six operations returns a {\em BOOLEAN\/}
and is a specification of the identically-named built-in PASP
function. Each precondition ensures that both input parameters
have type {\em UNSIGNED\/}. We use the AMN {\sf bool} operator which
returns the boolean value of its argument.\\[1ex]

{\bf ULE}:\ \ \  translated as:\\{\tt rr := ULE(aa,bb)}\\
"*/
  rr <-- ULE(aa : UNSIGNED & bb : UNSIGNED) =
    BEGIN rr := bool (aa <= bb) END;

/*"
{\bf UGE}:\ \ \  translated as:\\{\tt rr := UGE(aa,bb)}\\
"*/
  rr <-- UGE(aa : UNSIGNED & bb : UNSIGNED) =
    BEGIN rr := bool (aa >= bb) END;
 
/*"
{\bf ULT}:\ \ \  translated as:\\{\tt rr := ULT(aa,bb)}\\
"*/
  rr <-- ULT(aa : UNSIGNED & bb : UNSIGNED) =
    BEGIN rr := bool (aa < bb) END;

/*"
{\bf UGT}:\ \ \  translated as:\\{\tt rr := UGT(aa,bb)}\\
"*/
  rr <-- UGT(aa : UNSIGNED & bb : UNSIGNED) =
    BEGIN rr := bool (aa > bb) END;

/*"
{\bf UEQ}:\ \ \  translated as:\\{\tt rr := UEQ(aa,bb)}\\
"*/
  rr <-- UEQ(aa : UNSIGNED & bb : UNSIGNED) =
    BEGIN rr := bool (aa = bb) END;

/*"
{\bf UNE}:\ \ \  translated as:\\{\tt rr := UNE(aa,bb)}\\
"*/
  rr <-- UNE(aa : UNSIGNED & bb : UNSIGNED) =
    BEGIN rr := bool (aa /= bb) END;

/*"
\ \\

The precondition for each of the five arithmetic operations stipulates
that both input and output parameters are of type {\em UNSIGNED\/};
the former ensures that the operation is invoked safely, and
the latter that we do not have to deal with undefinedness.
Each is a specification of the identically-named built-in PASP
function\\[1ex]
{\bf UADD}:\ \ \  translated as:\\{\tt rr := UADD(aa,bb)}\\
"*/
  rr <-- UADD(aa : UNSIGNED & bb : UNSIGNED) =
    PRE aa + bb : UNSIGNED THEN
      rr := aa + bb
    END;

/*"
\newpage
{\bf USUB}:\ \ \  translated as:\\{\tt rr := USUB(aa,bb)}\\
"*/
  rr <-- USUB(aa : UNSIGNED & bb : UNSIGNED) =
    PRE aa - bb : UNSIGNED THEN
      rr := aa - bb
    END;

/*"
{\bf UMUL}:\ \ \  translated as:\\{\tt rr := UMUL(aa,bb)}\\
"*/
  rr <-- UMUL(aa : UNSIGNED & bb : UNSIGNED) =
    PRE aa * bb : UNSIGNED THEN
      rr := aa * bb
    END;

/*"
{\bf UDIV}:\ \ \  translated as:\\{\tt rr := UDIV(aa,bb)}\\
"*/
  rr <-- UDIV(aa : UNSIGNED & bb : UNSIGNED) =
    PRE bb /= MinUns & aa /bb : UNSIGNED THEN
      rr := aa / bb
    END;
  
/*"
{\bf UMOD}:\ \ \  translated as:\\{\tt rr := UMOD(aa,bb)}\\
"*/
  rr <-- UMOD(aa : UNSIGNED & bb : UNSIGNED) =
    PRE bb /= MinUns & aa mod bb : UNSIGNED THEN
      rr := aa mod bb
    END;
  
/*"
\newpage
The same comments apply to the next four operations except that the
first two are translated in terms of the built-in PASP functions {\em UADD\/}
and {\em USUB\/}, and the latter {\em ULEFT\/} and {\em URIGHT\/}.\\[1ex]

{\bf UINC}:\ \ \  translated as:\\{\tt rr := UADD(aa,01)}\\
"*/
  rr <-- UINC(aa : UNSIGNED) =
    PRE aa + n2u(1) : UNSIGNED THEN
      rr := aa + n2u(1)
    END;

/*"
{\bf UDEC}:\ \ \  translated as:\\{\tt rr := USUB(aa,01)}\\
"*/
  rr <-- UDEC(aa : UNSIGNED) =
    PRE aa - n2u(1) : UNSIGNED THEN
      rr := aa - n2u(1)
    END;

/*"
{\bf ULEFT}:\ \ \  translated as:\\{\tt rr := ULEFT(aa)}\\
"*/
  rr <-- ULEFT(aa : UNSIGNED) =
    PRE aa * n2u(2) : UNSIGNED THEN
      rr := aa * n2u(2)
    END;

/*"
{\bf URIGHT}:\ \ \  translated as:\\{\tt rr := URIGHT(aa)}\\
"*/
  rr <-- URIGHT(aa : UNSIGNED) =
    PRE aa / n2u(2) : UNSIGNED THEN
      rr := aa / n2u(2)
    END

END
