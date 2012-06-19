MACHINE       Factorial

/*"
A stateless specification having a single operation which, if
possible, returns the Factorial of its input parameter.
"*/

INCLUDES      FACTORIAL

SEES          Scalar_TYPE

OPERATIONS

/*"{\bf comp\_fac}\\[.5ex]
Either computes Factorial or returns 0. In this specification
we are not specific when Factorial should be computed; however,
we expect the designer to do his/her best to try to achieve the
computation ...
"*/

  fac_or_0 <-- comp_fac(inp) =
    PRE inp: SCALAR THEN
      CHOICE
        fac_or_0 := math_fac(inp) 
      OR
        fac_or_0 := 0
      END
    END

END
