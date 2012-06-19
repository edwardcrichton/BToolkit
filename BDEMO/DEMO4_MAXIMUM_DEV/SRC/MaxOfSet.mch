MACHINE

  MaxOfSet(maxint)

VARIABLES

  numset 

INVARIANT

/*"The state is a set of  positive numbers"*/

 numset  <: 1..maxint  


INITIALISATION

  numset:={}

OPERATIONS

/*"{\bf enter}

 This operation adds a new positive number to the set of numbers "*/

 enter(new) =    
   PRE 
     new: NAT1 & new <= maxint
   THEN
     numset :=  numset \/ {new}
   END;

/*"{\bf maximum}

This operation returns the maximum number currntly held in the set "*/

 mx <-- maximum = 
    PRE 
       numset /= {}
    THEN
       mx  := max(numset) 
    END

END
