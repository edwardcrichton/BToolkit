/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
v0.02
  VERSION:          B-Toolkit Beta 4.32
  DATE:             15/02/99
v0.03
  VERSION:          B-Toolkit Beta 4.51
  DATE:             18/06/99
v0.04
  VERSION:          B-Toolkit Beta 4.52
  DATE:             12/07/99
v0.05
  VERSION:          B-Toolkit 5.0.14
  DATE:             15/01/00
***/

/*
Description: Library Type machine intruducing BYTE

History :
030698 v0.01 : Created.
150299 v0.02 : added: b2bl, bl2b
130699 v0.03 : change in PROPERTIES:
  !nat.(nat:NAT => b2n(n2b(nat)) = nat) ->
    !nat.(nat:NAT&nat<=255 => b2n(n2b(nat)) = nat)
120799 v0.04 : created Byt_SEMANTICS.mch & changed this TYPE machine
               so that mimimal semantic information is given here (to
               increase the efficiency of the provers - semantic information
               is mirrored in the PASP mathematical library)
150100 v0.05 : Changes for DecCo8.
               Properties reduced to minimal type information; full
               properies given in Byt_SEMANTICS.mch
               Introduced the two operations BOOL2B and B2BOOL
               Changed n2b/b2n from --> to >->> in line with Byt_SEMANTICS.mch.
*/

MACHINE           Byt_TYPE

/*"
This specification models the built-in PASP {\em BYTE\/}
type using the two conversion {\em BYTE-NAT\/} functions
{\em n2b\/} and {\em b2n\/}. {\em MinByte\/} and {\em MaxByte\/}
are also defined.

Each of the operations is translated directly to its PASP equivalent
by the B-PASP Translator; the exceptions are {\em BINC\/} and {\em
BDEC\/} which are translated in terms of {\em BADD\/} and {\em BSUB\/}.

The constants {\em n2b\/}, {\em  b2n\/}, {\em b2bl\/} and {\em  bl2b\/}
are also introduced, being defined in the {\em Byt_SEMANTICS\/} machine.
"*/

SEES              Bool_TYPE

/*"
Since some operations return a {\em BOOLEAN\/}
we ensure that the {\em Bool\_TYPE\/} machine is in scope:
"*/

SETS                BYTE

/*"
We introduce the set {\em BYTE\/}:
"*/

CONSTANTS

/*"
We now introduce the two conversion functions between {\em BYTE\/}
and {\em NAT\/}:
"*/

  n2b, b2n,

/*"
and the two conversion functions between {\em BYTE\/}
and {\em BOOL\/}:
"*/

  b2bl, bl2b

PROPERTIES

/*"
We give minimal properties here - full semantic information
is contained in {\em Byt\_SEMANTICS.mch\/}:
"*/

  n2b : 0..255 >->> BYTE &
  b2n : BYTE >->> 0..255 &

  b2bl : BYTE --> BOOL &
  bl2b : BOOL --> BYTE

DEFINITIONS

  MinByt == n2b(0);
  MaxByt == n2b(255)

OPERATIONS

/*"
Each of the following six operations returns a {\em BOOLEAN\/}
and is a specification of the identically-named built-in PASP
function. Each precondition ensures that both input parameters
have type {\em BYTE\/}. We use the AMN {\sf bool} operator which
returns the boolean value of its argument.\\[1ex]

{\bf BLE}\ \ \  translated as:\\{\tt rr := BLE(aa,bb)}\\
"*/
  rr <-- BLE(aa : BYTE & bb : BYTE) =
    BEGIN rr := bool (aa <= bb) END;

/*"
{\bf BGE}\ \ \  translated as:\\{\tt rr := BGE(aa,bb)}\\
"*/
  rr <-- BGE(aa : BYTE & bb : BYTE) =
    BEGIN rr := bool (aa >= bb) END;

/*"
{\bf BLT}:\ \ \  translated as:\\{\tt rr := BLT(aa,bb)}\\
"*/
  rr <-- BLT(aa : BYTE & bb : BYTE) =
    BEGIN rr := bool (aa < bb) END;

/*"
{\bf BGT}:\ \ \  translated as:\\{\tt rr := BGT(aa,bb)}\\
"*/
  rr <-- BGT(aa : BYTE & bb : BYTE) =
    BEGIN rr := bool (aa > bb) END;

/*"
\newpage
{\bf BEQ}:\ \ \  translated as:\\{\tt rr := BEQ(aa,bb)}\\
"*/
  rr <-- BEQ(aa : BYTE & bb : BYTE) =
    BEGIN rr := bool (aa = bb) END;

/*"
{\bf BNE}:\ \ \  translated as:\\{\tt rr := BNE(aa,bb)}\\
"*/
  rr <-- BNE(aa : BYTE & bb : BYTE) =
    BEGIN rr := bool (aa /= bb) END;



/*"
\ \\

The precondition for each of the following five arithmetic operations
stipulates that both input and output parameters are of type {\em
BYTE\/}; the former ensures that the operation is invoked safely, and
the latter that we do not have to deal with undefinedness.  Each is a
specification of the identically-named built-in PASP function\\[1ex]
{\bf BADD}:\ \ \  translated as:\\{\tt rr := BADD(aa,bb)}\\
"*/
  rr <-- BADD(aa : BYTE & bb : BYTE) =
    PRE aa + bb : BYTE THEN
      rr := aa + bb
    END;

/*"
{\bf BSUB}:\ \ \  translated as:\\{\tt rr := BSUB(aa,bb)}\\
"*/
  rr <-- BSUB(aa : BYTE & bb : BYTE) =
    PRE aa - bb : BYTE THEN
      rr := aa - bb
    END;

/*"
\newpage
{\bf BMUL}:\ \ \  translated as:\\{\tt rr := BMUL(aa,bb)}\\
"*/
  rr <-- BMUL(aa : BYTE & bb : BYTE) =
    PRE aa * bb : BYTE THEN
      rr := aa * bb
    END;

/*"
{\bf BDIV}:\ \ \  translated as:\\{\tt rr := BDIV(aa,bb)}\\
"*/
  rr <-- BDIV(aa : BYTE & bb : BYTE) =
    PRE bb /= MinByt & aa / bb : BYTE THEN
      rr := aa / bb
    END;
  
/*"
{\bf BMOD}:\ \ \  translated as:\\{\tt rr := BMOD(aa,bb)}\\
"*/
  rr <-- BMOD(aa : BYTE & bb : BYTE) =
    PRE bb /= MinByt & aa mod bb : BYTE THEN
      rr := aa mod bb
    END;
  
/*"
\ \\

The same comments apply to the next two operations except that they
are translated in terms of the built-in PASP functions {\em BADD\/}
and {\em BSUB\/}.\\[1ex]

{\bf BINC}:\ \ \  translated as:\\{\tt rr := BADD(aa,1)}\\
"*/
  rr <-- BINC(aa : BYTE) =
    PRE aa + n2b(1) : BYTE THEN
      rr := aa + n2b(1)
    END;

/*"
{\bf BDEC}:\ \ \  translated as:\\{\tt rr := BSUB(aa,1)}\\
"*/
  rr <-- BDEC(aa : BYTE) =
    PRE aa - n2b(1) : BYTE THEN
      rr := aa - n2b(1)
    END;

/*"
The next two  operations are specifications of the
identically-named built-in PASP {\em BYTE\/}-{\em BOOL\/}
commands, and are defined in terms of the operators {\em b2bl\/}
and {\em bl2b\/}.\\[1ex]
{\bf B2BOOL}\ \ \  translated as:\\{\tt rr := B2BOOL(aa)}\\
"*/
  rr <-- B2BOOL(aa : BYTE) =
    BEGIN rr := b2bl(aa) END;

/*"
{\bf BOOL2B}\ \ \  translated as:\\{\tt rr := BOOL2B(aa)}\\
"*/
  rr <-- BOOL2B(aa : BOOL) =
    BEGIN rr := bl2b(aa) END;

/*"
The final operations are specifications of the shift commands;
both input and output parameters are of type {\em BYTE\/};
the former ensures that the operation is invoked safely, and
the latter that we do not have to deal with undefinedness.\\[1ex]
{\bf BLEFT}\ \ \  translated as:\\{\tt rr := BLEFT(aa) }\\
"*/
  rr <-- BLEFT(aa : BYTE) =
    PRE aa * n2b(2) : BYTE THEN
      rr := aa * n2b(2)
    END;

/*"
{\bf BRIGHT}\ \ \  translated as:\\{\tt rr := BRIGHT(aa) }\\
"*/
  rr <-- BRIGHT(aa : BYTE) =
    PRE aa / n2b(2) : BYTE THEN
      rr := aa / n2b(2)
    END

END
