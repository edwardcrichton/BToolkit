/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit 5.0.14
  DATE:             31/01/01
***/

/*
Description: Library machine intruducing READONLY variable

History :
310101 v0.05 : Created for DecCo8.
*/

MACHINE           Rename_Byt_Read

/*"
A renamable encapsulation of a single READONLY byte variable.

The specification variable has the name {\em Rename\/} and the
single parameter provides its type.

A single operation {\em READ\/} is provided, with the initialisation
specified non-determinstically.
"*/

SEES             Byt_TYPE

VARIABLES        Rename_byt_ro

INVARIANT        Rename_byt_ro : BYTE

INITIALISATION   Rename_byt_ro :: BYTE

OPERATIONS

/*"
{\bf Rename\_READ}\\[1ex]
Returns the value of the variable without precondition; translated as:
\\\ \ \  {\tt vv := Rename\_byt\_ro}.
"*/
  vv <-- Rename_READ = BEGIN vv := Rename_byt_ro || Rename_byt_ro :: BYTE END

END
