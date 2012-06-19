/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
v0.02
  VERSION:          B-Toolkit 5.0.14
  DATE:             27/01/01
***/

/*
Description: Renamable Library variable machine
             encapsulating an NVRAM array of Byte

History :
030698 v0.01 : Created as Rename_BiArr

270101 v0.01 : Renamed to Rename_BiArr_File for DecCo8
*/

MACHINE          Rename_BiArr_File(VALUE,lb,ub)

/*"
A parameterised renamable encapsulation of an NVRAM
{\em BYTE}-indexed array.

The values to be stored in the array stored appear as the {\em
VALUE\/} parameter which may be instantiated to any valid PASP type.

The array indices are set through the instantiation of the {\em lb\/}
and {\em ub\/} parameters, which may be instantiated to any natural
numbers in the range {\em 0\/} to {\em 255\/}.

Four operations are provided for this general purpose machine, {\em
IDX\/}, {\em VAL\/}, {\em STO\/} and {\em EQ\/}; it is thus
envisaged that all arithmetic operations on the values stored are
achieved by first copying those values into local variables (using
{\em VAL\/}) and subsequently updating the array (using {\em STO\/}).

The specification array variable has the name {\em Rename\/} and, as
with the single variable machines, the initialisation is
nondeterministic, in line with the current practice of the programmer
explicitly initialising all variables. Thus the invariant is
specified as a {\em partial\/} mapping into {\em VALUE\/} and the
initialisation allows {\em any\/} configuration consistent with that
requirement.

The variable array name will appear in the translated code as the
identifier given for the rename, and importing this machine results in
a global data declaration for the array. For example importing `{\em
control\_BiBArr(BYTE,10,20)\/}' will result in the global data
declaration:\\[1ex]
\hspace*{3em}{\tt VAR control : ARRAY [10..20] OF BYTE;}\\[1ex]
Thus the initialisation requires no translation
since the above declaration achieves the nondeterminism specified.
"*/

CONSTRAINTS      lb>=0 & ub<=255

SEES             Byt_TYPE, Bool_TYPE

VARIABLES        Rename

INVARIANT        Rename : lb..ub +-> VALUE

INITIALISATION   Rename :: lb..ub +-> VALUE

OPERATIONS

/*"
{\bf  Rename\_IDX}\\[.5ex]
The operation returns a boolean indicating whether or not the index
input parameter is within the bounds of the array, using the AMN {\sf
bool} operator (which returns the boolean value of its argument) - the
precondition ensures that the index input parameter has type {\em
BYTE\/}; translated as:\\
{\tt bb := (BGE(idx,lb) AND BLE(idx,ub))}
\newpage
"*/
  bb <-- Rename_IDX(idx : BYTE) =
    BEGIN bb := bool(b2n(idx): lb..ub) END;

/*"
{\bf  Rename\_VAL}\\[.5ex]
The operation to retrieve a value stored at a particular array index -
the precondition ensures that the index input parameter has type {\em
BYTE\/}, is within the bounds of the array and the array at that index
has been initialised; translated as:\\
{\tt vv := prefix [idx]}
"*/
  vv <-- Rename_VAL(idx : BYTE) =
    PRE b2n(idx) : dom(Rename) THEN
      vv := Rename(b2n(idx))
    END;

/*"
{\bf  Rename\_STO}\\[.5ex]
The operation to store a value at a particular array index -
the precondition ensures that the index input parameter has type {\em
BYTE\/} and is within the bounds of the array, and that the value
parameter is of the right type; translated as:\\
{\tt prefix [idx] := vv}
"*/
  Rename_STO(idx : BYTE & vv : VALUE) =
    PRE b2n(idx) : lb..ub THEN
      Rename(b2n(idx)) := vv
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

  bb <--  Rename_EQ (idx : BYTE & vv : VALUE) =
    PRE b2n(idx) : dom(Rename) THEN
      bb := bool(Rename(b2n(idx)) = vv)
    END



END
