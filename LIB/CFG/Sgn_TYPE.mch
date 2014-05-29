MACHINE       Sgn_TYPE

/*" This specification models the built-in PASP {\em SIGNED\/} ({\em
INTEGER\/}) type using the four conversion {\em SIGNED-NAT\/}
functions {\em n2ps\/}, {\em n2ns\/}, {\em ns2n\/}, and {\em ps2n\/}.
{\em MinSgn\/} and {\em MaxSgn\/} are also defined.

The operations comprise the six comparison functions {\em SLE, SGE,
SLT, SGT, SEQ, SNE\/}, the seven arithmetic functions {\em SADD,
SSUB, SMUL, SDIV, SMOD, SINC\/} and {\em SDEC\/}.

Each of the operations is translated directly in terms of the binary
operators $<=$, $>=$, $<$, $>$, $=$, $<>$, $+$, $-$, $\times$,
{\tt DIV} and {\tt MOD}, as appropriate by the B-PASP Translator.  "*/

SEES

/*" Since some operations return a {\em BOOLEAN\/} we ensure that the
{\em Bool\_TYPE\/} machine is in scope: "*/

  Bool_TYPE

SETS

/*" We introduce the set {\em SIGNED\/}: "*/

  SIGNED

CONSTANTS

/*" We now introduce the two {\em SIGNED\/} constants: "*/

  MinSgn, MaxSgn,

/*" the four conversion functions between {\em SIGNED\/} - (positive
{\em SIGNED\/} ({\em ps}) and (negative {\em SIGNED\/} ({\em ns}) -
and {\em NAT\/}: "*/

  n2ps, n2ns, ps2n, ns2n

/*" \newpage "*/
PROPERTIES

/*"
We ensure that the the five basic arithmetic operations
are defined for {\em SIGNED\/}; we model each as a {\em partial\/}
function (for example, not all pairs of {\em SIGNED\/}
when added together will produce an {\em SIGNED\/}):
"*/

   ? + ?   : SIGNED * SIGNED +-> SIGNED &
   ? - ?   : SIGNED * SIGNED +-> SIGNED &
   ? * ?   : SIGNED * SIGNED +-> SIGNED &
   ? / ?   : SIGNED * SIGNED +-> SIGNED &
   ? mod ? : SIGNED * SIGNED +-> SIGNED &

/*" We define the {\em NAT\/} to positive {\em SIGNED\/} conversion
function ({\em n2ps\/}) as a total injections between natural numbers
in the range {\em 0\/} to {\em 32767\/} and {\em SIGNED\/} (i.e.\
there is a 1-to-1 correspondence between the two); we define the {\em
NAT\/} to negative {\em SIGNED\/} conversion function ({\em n2ns\/})
as a total injections between natural numbers in the range {\em 1\/}
to {\em 32768\/} and {\em SIGNED\/}; the {\em SIGNED\/} to {\em
NAT\/} functions may then be defined as their inverses:"*/

   n2ps : 0..32767 >-> SIGNED &
   n2ns : 1..32768 >-> SIGNED &
   ps2n = n2ps~ &
   ns2n = n2ns~ &
   
/*" The properties of the minimum and maximum {\em SIGNED\/} values
now follow: "*/

   MinSgn = n2ns(32768) &
   MaxSgn = n2ps(32767)

OPERATIONS

/*" Each of the following six operations returns a {\em BOOLEAN\/}
and is a specification of the appropriate built-in PASP
function. Each precondition ensures that both input parameters have
type {\em SIGNED\/}. We use the AMN {\sf bool} operator, returning
the boolean value of its~argument.\\[1ex]

{\bf SLE}:\ \ \  translated as:\\{\tt rr := (aa $<=$ bb)}\\
"*/
  rr <-- SLE(aa : SIGNED & bb : SIGNED) =
    BEGIN rr := bool (aa <= bb) END;

/*"
{\bf SGE}:\ \ \  translated as:\\{\tt rr := (aa $>=$ bb)}\\
"*/
  rr <-- SGE(aa : SIGNED & bb : SIGNED) =
    BEGIN rr := bool (aa >= bb) END;
 
/*"
{\bf SLT}:\ \ \  translated as:\\{\tt rr := (aa $<$ bb)}\\
"*/
  rr <-- SLT(aa : SIGNED & bb : SIGNED) =
    BEGIN rr := bool (aa < bb) END;

/*"
{\bf SGT}:\ \ \  translated as:\\{\tt rr := (aa $>$ bb)}\\
"*/
  rr <-- SGT(aa : SIGNED & bb : SIGNED) =
    BEGIN rr := bool (aa > bb) END;

/*"
{\bf SEQ}:\ \ \  translated as:\\{\tt rr := (aa $=$ bb)}\\
"*/
  rr <-- SEQ(aa : SIGNED & bb : SIGNED) =
    BEGIN rr := bool (aa = bb) END;

/*"
{\bf SNE}:\ \ \  translated as:\\{\tt rr := (aa $<>$ bb)}\\
"*/
  rr <-- SNE(aa : SIGNED & bb : SIGNED) =
    BEGIN rr := bool (aa /= bb) END;

/*"
\ \\

The precondition for each of the five arithmetic operations stipulates
that both input and output parameters are of type {\em SIGNED\/};
the former ensures that the operation is invoked safely, and
the latter that we do not have to deal with undefinedness.
Each is a specification of the appropriate built-in PASP
function\\[1ex]
{\bf SADD}:\ \ \  translated as:\\{\tt rr := (aa $+$ bb)}\\
"*/
  rr <-- SADD(aa : SIGNED & bb : SIGNED) =
    PRE aa + bb : SIGNED THEN
      rr := aa + bb
    END;

/*"
{\bf SSUB}:\ \ \  translated as:\\{\tt rr := (aa $-$ bb)}\\
"*/
  rr <-- SSUB(aa : SIGNED & bb : SIGNED) =
    PRE aa - bb : SIGNED THEN
      rr := aa - bb
    END;

/*"
{\bf SMUL}:\ \ \  translated as:\\{\tt rr := (aa $\times$ bb)}\\
"*/
  rr <-- SMUL(aa : SIGNED & bb : SIGNED) =
    PRE aa * bb : SIGNED THEN
      rr := aa * bb
    END;

/*"
{\bf SDIV}:\ \ \  translated as:\\{\tt rr := (aa DIV bb)}\\
"*/
  rr <-- SDIV(aa : SIGNED & bb : SIGNED) =
    PRE bb /= n2ps(0) & aa / bb : SIGNED THEN
      rr := aa / bb
    END;
  
/*"
\newpage
{\bf SMOD}:\ \ \  translated as:\\{\tt rr := (aa MOD bb)}\\
"*/
  rr <-- SMOD(aa : SIGNED & bb : SIGNED) =
    PRE bb > n2ps(0) & aa mod bb : SIGNED THEN
      rr := aa mod bb
    END;
  
/*"
The same comments apply to the next two operations except that they
are translated in terms of the built-in PASP functions $+$ and $-$.\\[1ex]

{\bf SINC}:\ \ \  translated as:\\{\tt rr := (aa $+$ +1)}\\
"*/
  rr <-- SINC(aa : SIGNED ) =
    PRE aa + n2ps(1) : SIGNED THEN
      rr := aa + n2ps(1)
    END;

/*"
{\bf SDEC}:\ \ \  translated as:\\{\tt rr := (aa $-$ +1)}\\
"*/
  rr <-- SDEC(aa : SIGNED ) =
    PRE aa - n2ps(1) : SIGNED THEN
      rr := aa - n2ps(1)
    END

END
