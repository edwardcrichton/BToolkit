           /*** VHDL Variable Rename_number_SG ***/

MACHINE           Rename_number_SG(maxnum)

SEES              VHDL_PK

CONSTANTS         Rename_Ran 

/*" {\em 0 .. maxnum\/} also recognized as {\em Rename\_Ran} "*/

PROPERTIES        Rename_Ran = 0..maxnum 

VARIABLES         Rename_num

INVARIANT         Rename_num : Rename_Ran

INITIALISATION    Rename_num :: Rename_Ran

OPERATIONS

/* need all other ops from Scalar_type */

  Rename_EXP(num:0..maxnum & p1:0..maxnum) =
  PRE
    num ** p1 : 0..maxnum
  THEN
    Rename_num := num ** p1
  END

END
