MACHINE

  factorial

INCLUDES

  FACTORIAL 

CONSTANTS

  my_maxint

PROPERTIES

  my_maxint: NAT


OPERATIONS

/*"{\bf comp\_fac}\\either computes factorial or returns {\em zero\/}. In this
specification we are not specific when factorial should be computed; however,
we expect the designer to do his/her best and try to achieve the 1st branch ... 
up to 12 should be possible on a 32 bit architecture 
"*/ 

  ret<--comp_fac(inp) =
    PRE inp: 0..(my_maxint)  THEN
      CHOICE
        ret := math_fac(inp) 
      OR
        ret := 0
      END
    END


END
