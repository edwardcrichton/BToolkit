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
             encapsulating a single NVRAM Unsigned
             together with Bitwise operations

History :
030698 v0.01 : Created.
170101 v0.02 : Changes for DecCo8.
               Added operations Rename_LEFT, Rename_RIGHT
               Renamed to Rename_Uns_BS_File for DecCo8
*/

MACHINE   Rename_Uns_BS_File

/*"
A renamable encapsulation of a single NVRAM {\em UNSIGNED\/} variable,
providing the fifteen operations {\em VAL, STO, INC, DEC, ADD, SUB,
MUL, DIV, MOD, LEFT, RIGHT, AND, OR, XOR\/} and {\em NOT\/}. The
operations are, where necessary, specified in terms of the operations
of the corresponding type machine {\em Uns\_BS\_TYPE\/}, and so that
machine is brought into scope; {\em Bool\_TYPE\/} is also needed.

The specification variable has the name {\em Rename\_uns\/} and has a
nondeterministic initialisation (`$:\in$ {\em UNSIGNED\/}' means `takes
{\em any UNSIGNED\/} value') in line with the current practice of the
programmer explicitly initialising all variables.

So, for example, importing {\em prefix\_Uns\/} means that the unsigned variable
will appear in the translated code as\ \ {\tt prefix\_uns}\ \ and results
in the global data declaration:\\[1ex]
\hspace*{3em}{\tt VAR prefix\_uns :  UNSIGNED;}\\[1ex]
Thus the initialisation requires no translation since the above
declaration achieves the nondeterminism specified.
"*/

SEES             Uns_BS_TYPE, Byt_BS_TYPE

VARIABLES        Rename_uns

INVARIANT        Rename_uns : UNSIGNED

INITIALISATION   Rename_uns :: UNSIGNED

OPERATIONS

/*"
{\bf Rename\_VAL}\\[1ex]
Returns the value of the variable without precondition; translated as:\\\ \ \  {\tt vv := prefix\_uns}.
"*/
  vv <-- Rename_VAL = BEGIN vv := Rename_uns END;


/*"
{\bf Rename\_STO}\\[1ex]
Stores a new value in the variable with precondition that the
parameter should be a {\em UNSIGNED\/}; translated as:\\\ \ \  {\tt prefix\_uns := vv}.
"*/
  Rename_STO(vv : UNSIGNED) = BEGIN Rename_uns:=vv END;

/*"
{\bf Rename\_INC}\\[1ex]
Increments the variable with precondition that the
incremented variable should be a {\em UNSIGNED\/} (thus avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_uns := UADD(prefix\_uns,1)}.
"*/
  Rename_INC = 
    PRE Rename_uns + n2u(1): UNSIGNED THEN
      Rename_uns <-- UADD(Rename_uns,n2u(1))
    END;

/*"
{\bf Rename\_DEC}\\[1ex]
Decrements the variable with precondition that the
decremented variable should be a {\em UNSIGNED\/} (thus avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_uns := USUB(prefix\_uns,1)}.
"*/
  Rename_DEC =
    PRE Rename_uns - n2u(1): UNSIGNED THEN
      Rename_uns <-- USUB(Rename_uns,n2u(1))
    END;

/*"
{\bf Rename\_ADD}\\[1ex]
Increases the variable by the value of the input parameter,
with precondition that both the parameter and the 
increased variable should be a {\em UNSIGNED\/} (the former ensuring that
the precondition of {\em UADD\/} is met and the latter avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_uns := UADD(prefix\_uns,vv)}.
"*/
  Rename_ADD(vv : UNSIGNED) =
    PRE Rename_uns + vv: UNSIGNED THEN 
      Rename_uns <-- UADD(Rename_uns,vv)
    END;

/*"
{\bf Rename\_SUB}\\[1ex]
Decreases the variable by the value of the input parameter,
with precondition that both the parameter and the 
decreased variable should be a {\em UNSIGNED\/} (the former ensuring that
the precondition of {\em USUB\/} is met and the latter avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_uns := USUB(prefix\_uns,vv)}.
"*/
  Rename_SUB(vv : UNSIGNED) =
    PRE Rename_uns - vv: UNSIGNED THEN 
      Rename_uns <-- USUB(Rename_uns,vv)
    END;

/*"
{\bf Rename\_MUL}\\[1ex]
Changes the variable to be the product of its current value and that
of the input parameter, with precondition that both the parameter and
the increased variable should be a {\em UNSIGNED\/} (the former ensuring
that the precondition of {\em UMUL\/} is met and the latter avoiding
nondefinedness); translated as:\\\ \ \ {\tt prefix\_uns :=
UMUL(prefix\_uns,vv)}.
"*/
  Rename_MUL(vv : UNSIGNED) =
    PRE Rename_uns * vv : UNSIGNED THEN 
      Rename_uns <-- UMUL(Rename_uns,vv)
    END;

/*"
{\bf Rename\_DIV}\\[1ex]
Changes the variable to be its current value divided by that of the
input parameter, with precondition that both the parameter and the
decreased variable should be a {\em UNSIGNED\/} and the parameter be
non-zero (ensuring that the precondition of {\em UDIV\/} is met and
avoiding nondefinedness); translated as:\\\ \ \ {\tt prefix\_uns :=
UDIV(prefix\_uns,vv)}.
"*/
  Rename_DIV(vv : UNSIGNED) =
    PRE vv /= MinUns & Rename_uns / vv : UNSIGNED THEN 
      Rename_uns <-- UDIV(Rename_uns,vv)
    END;

/*"
{\bf Rename\_MOD}\\[1ex]
Changes the variable to be its current value modulus that of the input
parameter, with precondition that both the parameter and the decreased
variable should be a {\em UNSIGNED\/} and the parameter be non-zero
(ensuring that the precondition of {\em UMOD\/} is met and avoiding
nondefinedness); translated as:\\\ \ \ {\tt prefix\_uns :=
UMOD(prefix\_uns,vv)}.
"*/
  Rename_MOD(vv : UNSIGNED) =
    PRE vv /= MinUns & Rename_uns mod vv : UNSIGNED THEN 
      Rename_uns <-- UMOD(Rename_uns,vv)
    END;

/*"
{\bf Rename\_LEFT}\\[1ex]
Changes the variable to be its current value unsigned-shifted left,
with precondition that resulting value is a {\em UNSIGNED\/}
(ensuring that the precondition of {\em BLEFT\/} is met and avoiding
nondefinedness); translated as:\\\ \ \ {\tt prefix\_byt :=
ULEFT(prefix\_byt)}.
"*/
  Rename_LEFT =
    PRE (Rename_uns * n2u(2)) :  UNSIGNED THEN 
      Rename_uns <-- ULEFT(Rename_uns)
    END;

/*"
{\bf Rename\_RIGHT}\\[1ex]
Changes the variable to be its current value unsigned-shifted right,
with precondition that resulting value is a {\em UNSIGNED\/}
(ensuring that the precondition of {\em BRIGHT\/} is met and avoiding
nondefinedness); translated as:\\\ \ \ {\tt prefix\_byt :=
URIGHT(prefix\_byt)}.
"*/
  Rename_RIGHT =
    PRE (Rename_uns / n2u(2)) :  UNSIGNED THEN 
      Rename_uns <-- URIGHT(Rename_uns)
    END;

/*"
\newpage
{\bf Rename\_AND}\\[1ex]
Changes the variable to be the `bitwise and' of itself and its input
parameter, with precondition that the parameter has type {\em UNSIGNED\/};
translated as:\\\ \ \ {\tt prefix\_uns := UAND(prefix\_uns,vv)}.
"*/
  Rename_AND(vv : UNSIGNED) =
    BEGIN Rename_uns <-- UAND(Rename_uns,vv) END;

/*"
{\bf Rename\_OR}\\[1ex]
Changes the variable to be the `bitwise or' of itself and its input
parameter, with precondition that the parameter has type {\em UNSIGNED\/};
translated as:\\\ \ \ {\tt prefix\_uns := UOR(prefix\_uns,vv)}.
"*/
  Rename_OR(vv : UNSIGNED) =
    BEGIN Rename_uns <-- UOR(Rename_uns,vv) END;

/*"
{\bf Rename\_XOR}\\[1ex]
Changes the variable to be the `bitwise xor' of itself and its input
parameter, with precondition that the parameter has type {\em UNSIGNED\/};
translated as:\\\ \ \ {\tt prefix\_uns := UXOR(prefix\_uns,vv)}.
"*/
  Rename_XOR(vv : UNSIGNED) =
    BEGIN Rename_uns <-- UXOR(Rename_uns,vv) END;

/*"
\newpage
{\bf Rename\_NOT}\\[1ex]
Changes the variable to be the `bitwise complement' of itself;
translated as:\\\ \ \ {\tt prefix\_uns := UNOT(prefix\_uns)}.
"*/
  Rename_NOT = BEGIN Rename_uns <-- UNOT(Rename_uns) END

END

