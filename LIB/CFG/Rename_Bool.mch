/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit 5.0.14
  DATE:             24/01/01
***/

/*
Description: Renamable Parameterised Library variable machine
             encapsulating a single READWRITE Boolean

History :
250101 v0.01 : Created from Rename_Bool
*/

MACHINE           Rename_Bool(init_val)

/*"
A renamable parameterised encapsulation of a single READWRITE {\em
BOOLEAN\/} variable, providing the seven operations {\em VAL, STO,
EQL, NOT, AND, OR\/} and {\em XOR\/}.  The operations are, where
necessary, specified in terms of the {\em Bool\_TYPE\/} operations.

The specification variable has the name {\em Rename\_bool\/} and
the single parameter provides its initial value via its declaration.

Because of the restriction in {\em AMN\/} that all machine parameters
are natural numbers, the number is converted into a boolean value
through the {\tt n2b} and {\tt n2b} operators of {\em Byt\_TYPE}.
Typically, the parameter would be provided as {\tt b2n(bl2b(TRUE))}
or {\tt b2n(bl2b(FALSE))}.

So, for example, importing {\em prefix\_Bool(b2n(bl2b(TRUE)))\/}
means that the bool variable will appear in the translated code as
\ \ {\tt prefix\_bool}\ \ and results in the global data declaration:\\[1ex]
\hspace*{3em}{\tt VAR prefix\_bool : BOOLEAN = TRUE;}\\[1ex]
Thus the initialisation requires no translation since the above
declaration achieves the initialisation.
"*/

CONSTRAINTS       init_val : {0,1}

SEES              Bool_TYPE, Byt_TYPE

VARIABLES         Rename_bool

INVARIANT         Rename_bool : BOOL

INITIALISATION    Rename_bool := b2bl(n2b(init_val))

OPERATIONS

/*"
{\bf Rename\_VAL}\\[1ex]
Returns the value of the variable without precondition; translated as:\\\ \ \  {\tt vv := prefix\_bool}.
"*/
  vv <-- Rename_VAL = BEGIN vv := Rename_bool END;

/*"
{\bf Rename\_STO}\\[1ex]
Stores a new value in the variable with precondition that the
parameter should be a {\em BOOL\/}; translated as:\\\ \ \  {\tt prefix\_bool := vv}.
"*/
  Rename_STO(vv : BOOL) = BEGIN Rename_bool:=vv END;

/*"
{\bf Rename\_SET}\\[1ex]
Stores {\em TRUE\/} in the variable; translated as:\\\ \ \  {\tt prefix\_bool := TRUE}.
"*/
  Rename_SET = BEGIN Rename_bool:=TRUE END;

/*"
{\bf Rename\_RESET}\\[1ex]
Stores {\em FALSE\/} in the variable; translated as:\\\ \ \  {\tt prefix\_bool := FALSE}.
"*/
  Rename_RESET = BEGIN Rename_bool:=FALSE END;

/*"
{\bf Rename\_EQL}\\[1ex]
Returns a boolean indicating whether or not the value stored has the same
value as the input parameter, with precondition that the
parameter should be a {\em BOOL\/};
translated as:\\\ \ \  {\tt vv := prefix\_bool}.
"*/
  bb <-- Rename_EQL(vv : BOOL) =
    BEGIN
      bb := bool( (vv=TRUE & Rename_bool=TRUE ) or (vv=FALSE & Rename_bool=FALSE ) )
    END;

/*"
{\bf Rename\_NOT}\\[1ex]
Performs a logical {\tt NOT} of the variable, storing the result;
translated as:\\\ \ \  {\tt prefix\_bool := NOT(prefix\_bool)}.
"*/
  Rename_NOT = BEGIN Rename_bool := bool(Rename_bool=FALSE) END;

/*"
{\bf Rename\_AND}\\[1ex]
Changes the variable to be the `logical and' of itself and its input
parameter, with precondition that the parameter has type {\em BOOL\/};
translated as:\\\ \ \  {\tt prefix\_bool := (prefix\_bool AND vv)}.
"*/
  Rename_AND(vv : BOOL) = 
    BEGIN Rename_bool := bool((Rename_bool=TRUE) & (vv=TRUE)) END;

/*"
{\bf Rename\_OR}\\[1ex]
Changes the variable to be the `logical or' of itself and its input
parameter, with precondition that the parameter has type {\em BOOL\/};
translated as:\\\ \ \  {\tt prefix\_bool := (prefix\_bool OR vv)}.
"*/
  Rename_OR(vv : BOOL) =
    BEGIN Rename_bool := bool((Rename_bool=TRUE) or (vv=TRUE)) END;

/*"
{\bf Rename\_XOR}\\[1ex]
Changes the variable to be the `logical xor' of itself and its input
parameter, with precondition that the parameter has type {\em BOOL\/};
translated as:\\\ \ \  {\tt prefix\_bool := (prefix\_bool XOR vv)}.
"*/
  Rename_XOR(vv : BOOL) =
    BEGIN
      Rename_bool := bool ( (
                      ((Rename_bool=TRUE) & (vv=FALSE)) or
                      ((Rename_bool=FALSE) & (vv=TRUE))
                             )
                    )
     END

END
