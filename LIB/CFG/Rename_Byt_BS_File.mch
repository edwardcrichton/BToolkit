/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
v0.02
  VERSION:          B-Toolkit 5.0.14
  DATE:             17/01/01
***/

/*
Description: Renamable Library variable machine
             encapsulating a single NVRAM Byte
             together with Bitwise operations

History :
030698 v0.01 : Created.
170101 v0.02 : Changes for DecCo8.
               Added operations Rename_LEFT, Rename_RIGHT
               Renamed to Rename_Byt_BS_File for DecCo8
*/

MACHINE          Rename_Byt_BS_File

/*"
A renamable encapsulation of a single NVRAM {\em BYTE\/} variable,
providing the fifteen operations {\em VAL, STO, INC, DEC, ADD, SUB,
MUL, DIV, LEFT, RIGHT, MOD, AND, OR, XOR and NOT\/}. The operations
are, where necessary, specified in terms of the operations of the
corresponding type machine {\em Byt\_\_BSTYPE\/}, and so that machine
is brought into scope; {\em Bool\_TYPE\/} is also needed.

The specification variable has the name {\em Rename\_byt\/} and has a
nondeterministic initialisation (`$:\in$ {\em BYTE\/}' means `takes
{\em any BYTE\/} value') in line with the current practice of the
programmer explicitly initialising all variables.

So, for example, importing {\em prefix\_Byt\/} means that the byte variable
will appear in the translated code as\ \ {\tt prefix\_byt}\ \ and results
in the global data declaration:\\[1ex] \hspace*{3em}{\tt VAR prefix\_byt
: BYTE;}\\[1ex]
Thus the initialisation requires no translation since the above
declaration achieves the nondeterminism specified.
"*/

SEES             Bool_TYPE, Byt_BS_TYPE

VARIABLES        Rename_byt

INVARIANT        Rename_byt : BYTE

INITIALISATION   Rename_byt :: BYTE

OPERATIONS

/*"
{\bf Rename\_VAL}\\[1ex]
Returns the value of the variable without precondition; translated as:\\\ \ \  {\tt vv := prefix\_byt}.
"*/
  vv <-- Rename_VAL = BEGIN vv := Rename_byt END;

/*"
{\bf Rename\_STO}\\[1ex]
Stores a new value in the variable with precondition that the
parameter should be a {\em BYTE\/}; translated as:\\\ \ \  {\tt prefix\_byt := vv}.
"*/
  Rename_STO(vv : BYTE) = BEGIN Rename_byt:=vv END;

/*"
{\bf Rename\_INC}\\[1ex]
Increments the variable with precondition that the
incremented variable should be a {\em BYTE\/} (thus avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_byt := BADD(prefix\_byt,1)}.
"*/
  Rename_INC = 
    PRE Rename_byt + n2b(1) : BYTE THEN
      Rename_byt <-- BADD(Rename_byt,n2b(1))
    END;

/*"
{\bf Rename\_DEC}\\[1ex]
Decrements the variable with precondition that the
decremented variable should be a {\em BYTE\/} (thus avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_byt := BSUB(prefix\_byt,1)}.
"*/
  Rename_DEC = 
    PRE  Rename_byt - n2b(1) : BYTE THEN
      Rename_byt <-- BSUB(Rename_byt,n2b(1))
    END;

/*"
{\bf Rename\_ADD}\\[1ex]
Increases the variable by the value of the input parameter,
with precondition that both the parameter and the 
increased variable should be a {\em BYTE\/} (the former ensuring that
the precondition of {\em BADD\/} is met and the latter avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_byt :=
BADD(prefix\_byt,vv)}.
"*/
  Rename_ADD(vv : BYTE) =
    PRE Rename_byt + vv : BYTE THEN 
      Rename_byt <-- BADD(Rename_byt,vv)
    END;

/*"
{\bf Rename\_SUB}\\[1ex]
Decreases the variable by the value of the input parameter,
with precondition that both the parameter and the 
decreased variable should be a {\em BYTE\/} (the former ensuring that
the precondition of {\em BSUB\/} is met and the latter avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_byt := BSUB(prefix\_byt,vv)}.
"*/
  Rename_SUB(vv : BYTE) =
    PRE Rename_byt - vv : BYTE THEN 
      Rename_byt <-- BSUB(Rename_byt,vv)
    END;

/*"
{\bf Rename\_MUL}\\[1ex]
Changes the variable to be the product of its current value and that
of the input parameter, with precondition that both the parameter and
the increased variable should be a {\em BYTE\/} (the former ensuring
that the precondition of {\em BMUL\/} is met and the latter avoiding
nondefinedness); translated as:\\\ \ \ {\tt prefix\_byt :=
BMUL(prefix\_byt,vv)}.
"*/
  Rename_MUL(vv : BYTE) =
    PRE Rename_byt * vv : BYTE THEN 
      Rename_byt <-- BMUL(Rename_byt,vv)
    END;

/*"
{\bf Rename\_DIV}\\[1ex]
Changes the variable to be its current value divided by that of the
input parameter, with precondition that both the parameter and the
decreased variable should be a {\em BYTE\/} and the parameter be
non-zero (ensuring that the precondition of {\em BDIV\/} is met and
avoiding nondefinedness); translated as:\\\ \ \ {\tt prefix\_byt :=
BDIV(prefix\_byt,vv)}.
"*/
  Rename_DIV(vv : BYTE) =
    PRE vv /= MinByt & Rename_byt / vv : BYTE THEN 
      Rename_byt <-- BDIV(Rename_byt,vv)
    END;

/*"
{\bf Rename\_MOD}\\[1ex]
Changes the variable to be its current value modulus that of the input
parameter, with precondition that both the parameter and the decreased
variable should be a {\em BYTE\/} and the parameter be non-zero
(ensuring that the precondition of {\em BMOD\/} is met and avoiding
nondefinedness); translated as:\\\ \ \ {\tt prefix\_byt :=
BMOD(prefix\_byt,vv)}.
"*/
  Rename_MOD(vv : BYTE) =
    PRE vv /= MinByt & Rename_byt mod vv : BYTE THEN 
      Rename_byt <-- BMOD(Rename_byt,vv)
    END;

/*"
{\bf Rename\_LEFT}\\[1ex]
Changes the variable to be its current value byte-shifted left,
with precondition that resulting value is a {\em BYTE\/}
(ensuring that the precondition of {\em BLEFT\/} is met and avoiding
nondefinedness); translated as:\\\ \ \ {\tt prefix\_byt := BLEFT(prefix\_byt)}.
"*/
  Rename_LEFT =
    PRE (Rename_byt * n2b(2)) :  BYTE THEN 
      Rename_byt <-- BLEFT(Rename_byt)
    END;

/*"
{\bf Rename\_RIGHT}\\[1ex]
Changes the variable to be its current value byte-shifted right,
with precondition that resulting value is a {\em BYTE\/}
(ensuring that the precondition of {\em BRIGHT\/} is met and avoiding
nondefinedness); translated as:\\\ \ \ {\tt prefix\_byt := BRIGHT(prefix\_byt)}.
"*/
  Rename_RIGHT =
    PRE (Rename_byt / n2b(2)) :  BYTE THEN 
      Rename_byt <-- BRIGHT(Rename_byt)
    END;

/*"
\newpage
{\bf Rename\_AND}\\[1ex]
Changes the variable to be the `bitwise and' of itself and its input
parameter, with precondition that the parameter has type {\em BYTE\/};
translated as:\\\ \ \ {\tt prefix\_byt := BAND(prefix\_byt,vv)}.
"*/
  Rename_AND(vv : BYTE) =
    BEGIN Rename_byt <-- BAND(Rename_byt,vv) END;

/*"
{\bf Rename\_OR}\\[1ex]
Changes the variable to be the `bitwise or' of itself and its input
parameter, with precondition that the parameter has type {\em BYTE\/};
translated as:\\\ \ \ {\tt prefix\_byt := BOR(prefix\_byt,vv)}.
"*/
  Rename_OR(vv : BYTE) =
    BEGIN Rename_byt <-- BOR(Rename_byt,vv) END;

/*"
{\bf Rename\_XOR}\\[1ex]
Changes the variable to be the `bitwise xor' of itself and its input
parameter, with precondition that the parameter has type {\em BYTE\/};
translated as:\\\ \ \ {\tt prefix\_byt := BXOR(prefix\_byt,vv)}.
"*/
  Rename_XOR(vv : BYTE) =
    BEGIN Rename_byt <-- BXOR(Rename_byt,vv) END;

/*"
\newpage
{\bf Rename\_NOT}\\[1ex]
Changes the variable to be the `bitwise complement' of itself;
translated as:\\\ \ \ {\tt prefix\_byt := BNOT(prefix\_byt)}.
"*/
  Rename_NOT = BEGIN Rename_byt <-- BNOT(Rename_byt) END

END
