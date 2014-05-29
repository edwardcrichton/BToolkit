           /*** VHDL Package Rename_numbers_VAR ***/

MACHINE           Rename_numbers_VAR(maxnum)

SEES             std_numbers_PK

CONSTANTS

   Rename_range 

/*" {\em 0 .. maxnum\/} also recognized as {\em Rename_range} "*/

PROPERTIES

   Rename_range = 0..maxnum 

VARIABLES

  Rename_num

INVARIANT

  Rename_num : Rename_range

OPERATIONS

/* need all other ops from Scalar_type */

  Rename_EXP(num : 0..maxnum & p1 : 0..maxnum) =
  PRE
    Rename_num ** p1 : 0..maxnum
  THEN
    Rename_num := num ** p1
  END

DEFINITIONS

  a ** b == exp(a,b) 

END
