/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit 5.0.14
  DATE:             31/01/01
***/

/*
Description: Library machine intruducing WRITEONLY variable

History :
310101 v0.05 : Created for DecCo8.
*/

MACHINE           Rename_Byt_Write

/*"
A renamable encapsulation of a single WRITEONLY byte variable.

The specification variable has the name {\em Rename\/} and the
single parameter provides its type.

A single operation {\em WRITE\/} is provided, with the initialisation
specified non-determinstically.
"*/

SEES             Byt_TYPE

VARIABLES        Rename_byt_wo

INVARIANT        Rename_byt_wo : BYTE

INITIALISATION   Rename_byt_wo :: BYTE

OPERATIONS

/*"
{\bf Rename\_WRITE}\\[1ex]
Sets the value of the variable to int input parameter; translated as:
\\\ \ \  {\tt vv := Rename\_byt\_wo := vv}.
"*/
  Rename_WRITE(vv : BYTE) = BEGIN Rename_byt_wo := vv END

END
