MACHINE   Rename_Sgn

/*" A renamable encapsulation of a single {\em SIGNED\/} ({\em
INTEGER\/}) variable, providing the nine operations {\em VAL, STO,
INC, DEC, ADD, SUB, MUL, DIV\/} and {\em MOD\/}. The operations are,
where necessary, specified in terms of the operations of the
corresponding type machine {\em Sgn\_TYPE\/}, and so that machine is
brought into scope; {\em Bool\_TYPE\/} is also needed.

The specification variable has the name {\em Rename\_sgn\/} and has a
nondeterministic initialisation (`$:\in$ {\em SIGNED\/}' means `takes
{\em any SIGNED\/} value') in line with the current practice of the
programmer explicitly initialising all variables.

So, for example, importing {\em prefix\_Sgn\/} means that the signed variable
will appear in the translated code as\ \ {\tt prefix\_sgn}\ \ and results
in the global data declaration:\\[1ex]\hspace*{3em}{\tt VAR prefix\_sgn
:  INTEGER;}\\[1ex]
Thus the initialisation requires no translation since the above
declaration achieves the nondeterminism specified. "*/

SEES             Bool_TYPE, Sgn_TYPE

VARIABLES        Rename_sgn

INVARIANT        Rename_sgn : SIGNED

INITIALISATION   Rename_sgn :: SIGNED

OPERATIONS

/*"
{\bf Rename\_VAL}\\[1ex]
Returns the value of the variable without precondition; translated as:\\\ \ \  {\tt vv := prefix\_sgn}.
"*/
  vv <-- Rename_VAL = BEGIN vv := Rename_sgn END;


/*"
{\bf Rename\_STO}\\[1ex]
Stores a new value in the variable with precondition that the
parameter should be a {\em SIGNED\/}; translated as:\\\ \ \  {\tt prefix\_sgn := vv}.
"*/
  Rename_STO(vv : SIGNED) = BEGIN Rename_sgn:=vv END;

/*"
{\bf Rename\_INC}\\[1ex]
Increments the variable with precondition that the
incremented variable should be a {\em SIGNED\/} (thus avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_sgn := prefix\_sgn $+$ +1}.
"*/
  Rename_INC = 
    PRE Rename_sgn + n2ps(1): SIGNED THEN
      Rename_sgn <-- SADD(Rename_sgn,n2ps(1))
    END;

/*"
{\bf Rename\_DEC}\\[1ex]
Decrements the variable with precondition that the
decremented variable should be a {\em SIGNED\/} (thus avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_sgn := prefix\_sgn $-$ +1}.
"*/
  Rename_DEC =
    PRE Rename_sgn - n2ps(1): SIGNED THEN
      Rename_sgn <-- SSUB(Rename_sgn,n2ps(1))
    END;

/*"
{\bf Rename\_ADD}\\[1ex]
Increases the variable by the value of the input parameter,
with precondition that both the parameter and the 
increased variable should be a {\em SIGNED\/} (the former ensuring that
the precondition of {\em SADD\/} is met and the latter avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_sgn := prefix\_sgn $+$ vv}.
"*/
  Rename_ADD(vv : SIGNED) =
    PRE Rename_sgn + vv: SIGNED THEN 
      Rename_sgn <-- SADD(Rename_sgn,vv)
    END;

/*"
{\bf Rename\_SUB}\\[1ex]
Decreases the variable by the value of the input parameter,
with precondition that both the parameter and the 
decreased variable should be a {\em SIGNED\/} (the former ensuring that
the precondition of {\em SSUB\/} is met and the latter avoiding
nondefinedness); translated as:\\\ \ \  {\tt prefix\_sgn := prefix\_sgn $-$ vv}.
"*/
  Rename_SUB(vv : SIGNED) =
    PRE Rename_sgn - vv: SIGNED THEN 
      Rename_sgn <-- SSUB(Rename_sgn,vv)
    END;

/*"
{\bf Rename\_MUL}\\[1ex]
Changes the variable to be the product of its current value and that
of the input parameter, with precondition that both the parameter and
the increased variable should be a {\em SIGNED\/} (the former ensuring
that the precondition of {\em SMUL\/} is met and the latter avoiding
nondefinedness); translated as:\\\ \ \ {\tt prefix\_sgn :=
prefix\_sgn $\times$ vv}.
"*/
  Rename_MUL(vv : SIGNED) =
    PRE Rename_sgn * vv : SIGNED THEN 
      Rename_sgn <-- SMUL(Rename_sgn,vv)
    END;

/*"
{\bf Rename\_DIV}\\[1ex]
Changes the variable to be its current value divided by that of the
input parameter, with precondition that both the parameter and the
decreased variable should be a {\em SIGNED\/} and the parameter be
non-zero (ensuring that the precondition of {\em SDIV\/} is met and
avoiding nondefinedness); translated as:\\\ \ \ {\tt prefix\_sgn :=
prefix\_sgn DIV vv}.
"*/
  Rename_DIV(vv : SIGNED) =
    PRE vv /= n2ps(0) & Rename_sgn / vv : SIGNED THEN 
      Rename_sgn <-- SDIV(Rename_sgn,vv)
    END;

/*"
{\bf Rename\_MOD}\\[1ex]
Changes the variable to be its current value modulus that of the input
parameter, with precondition that both the parameter and the decreased
variable should be a {\em SIGNED\/} and the parameter be greater than
(ensuring that the precondition of {\em SMOD\/} is met and avoiding
nondefinedness); translated as:\\\ \ \ {\tt prefix\_sgn :=
prefix\_sgn MOD vv}.
"*/
  Rename_MOD(vv : SIGNED) =
    PRE vv > n2ps(0) & Rename_sgn mod vv : SIGNED THEN 
      Rename_sgn <-- SMOD(Rename_sgn,vv)
    END

END
/*"
\newpage
"*/
