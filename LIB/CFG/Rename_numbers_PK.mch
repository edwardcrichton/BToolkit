           /*** VHDL Package Rename_numbers_PK (stateless) ***/

MACHINE           Rename_numbers_PK(maxnum)

SEES             std_numbers_PK

CONSTANTS

   Rename_range 

/*" {\em 0 .. maxnum\/} also recognized as {\em Rename_range} "*/

PROPERTIES

   Rename_range = 0..maxnum 

OPERATIONS

/* need all other ops from Scalar_type */

  nn <-- Rename_EXP(n1 : 0..maxnum & p1 : 0..maxnum) =
  PRE
    n1 ** p1 : 0..maxnum
  THEN
    nn := n1 ** p1
  END

DEFINITIONS

  a ** b == exp(a,b) 

END
