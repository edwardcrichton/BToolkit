/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit 5.0.14
  DATE:             24/01/01
***/

/*
Description: Renamable Parameterised Library variable machine
             encapsulating a Unsigned-indexed READWRITE array

History :
240101 v0.01 : Created from Rename_BiArr_File
*/

MACHINE          Rename_UiArr(VALUE,lb,ub,init_val)

/*"
A parameterised renamable encapsulation of a READWRITE
{\em UNSIGNED}-indexed array.

The values to be stored in the array stored appear as
the {\em VALUE\/} parameter which may be instantiated to any valid PASP
type.

The array indices are set through the instantiation of the {\em lb\/}
and {\em ub\/} parameters, which may be instantiated to any natural
numbers in the range {\em 0\/} to {\em 65535\/}.

The specification array variable has the name {\em Rename\/} and the
initial value parameter provides the initial value for all indices
of the array.

So, for example, importing {\em prefix\_UiArr(BYTE,10,500,n2b(255))\/}
means that the array variable will appear in the translated code as\ \
{\tt prefix\_byt}\ \ and results in the global data
declaration:\\[1ex]
\hspace*{3em}{\tt VAR prefix : ARRAY [010..0500] OF BYTE = 255;}\\[1ex]
Thus the initialisation requires no translation since the
above declaration achieves the nondeterminism specified.

This, in turn, means that the mapping into VALUE is {\em total\/}
(rather the {\em partial\/} as is the case with the corresponding
{\em File\/} machine).

Four operations are provided for this general purpose machine, {\em
IDX\/}, {\em VAL\/}, {\em STO\/} and {\em EQ\/}; it is thus
envisaged that all arithmetic operations on the values stored are
achieved by first copying those values into local variables (using
{\em VAL\/}) and subsequently updating the array (using {\em STO\/}).
"*/

CONSTRAINTS      lb >= 0 & ub <= 65535 & init_val : VALUE

SEES             Uns_TYPE, Bool_TYPE

VARIABLES        Rename

INVARIANT        Rename : lb..ub --> VALUE

INITIALISATION

  ANY Rename_init WHERE
    Rename_init : lb..ub --> VALUE &
    ran(Rename_init) = {init_val}
  THEN
    Rename := Rename_init
  END

OPERATIONS

/*"
{\bf  Rename\_IDX}\\[.5ex]
The operation returns a boolean indicating whether or not the index
input parameter is within the bounds of the array, using the AMN {\sf
bool} operator (which returns the boolean value of its argument) - the
precondition ensures that the index input parameter has type {\em
UNSIGNED\/}; translated as:\\
{\tt bb := (UGE(idx,lb) AND ULE(idx,ub))}
\newpage
"*/
  bb <-- Rename_IDX(idx : UNSIGNED) =
    BEGIN bb := bool(u2n(idx): lb..ub) END;

/*"
{\bf  Rename\_VAL}\\[.5ex]
The operation to retrieve a value stored at a particular array index -
the precondition ensures that the index input parameter has type {\em
UNSIGNED\/}, is within the bounds of the array and the array at that index
has been initialised; translated as:\\
{\tt vv := prefix [idx]}
"*/
  vv <-- Rename_VAL(idx : UNSIGNED) =
    PRE u2n(idx) : dom(Rename) THEN
      vv := Rename(u2n(idx))
    END;

/*"
{\bf  Rename\_STO}\\[.5ex]
The operation to store a value at a particular array index - 
the precondition ensures that the index input parameter has type {\em
UNSIGNED\/} and is within the bounds of the array, and that the value
parameter is of the right type; translated as:\\
{\tt prefix [idx] := vv}
"*/
  Rename_STO(idx : UNSIGNED & vv : VALUE) =
    PRE u2n(idx) : lb..ub THEN
      Rename(u2n(idx)) := vv
    END;

/*"
{\bf  Rename\_EQ}\\[.5ex]
The operation returns a boolean indicating whether or not the value
input parameter is the same as that currently stored at the at the
array location at the index parameter, using the AMN {\sf bool}
operator (which returns the boolean value of its argument) - the
precondition ensures that the both input parameters have the right
type and that additionally the array at that index has been
initialised; if, for example, {\em VALUE\/} is instantiated to {\em
BYTE\/}, translated as:\\ {\tt bb := BEQ(prefix [idx], vv)} "*/

  bb <--  Rename_EQ(idx : UNSIGNED & vv : VALUE) =
    PRE u2n(idx) : dom(Rename) THEN
      bb := bool(Rename(u2n(idx)) = vv)
    END

END
