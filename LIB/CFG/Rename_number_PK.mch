           /*** VHDL Package Rename_number_PK (stateless) ***/

MACHINE          Rename_number_PK(maxnum)

SEES             VHDL_PK

CONSTANTS

   Rename_Ran 

/*" {\em 0 .. maxnum\/} also recognized as {\em Rename\_range} "*/

PROPERTIES       Rename_Ran = 0..maxnum 

OPERATIONS

/* need all other ops from Scalar_type */

  nn <-- Rename_EXP(n1:0..maxnum & p1:0..maxnum) =
  PRE
    n1 ** p1 : 0..maxnum
  THEN
    nn := n1 ** p1
  END

END
