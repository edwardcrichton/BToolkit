MACHINE

  MaxOfSet

VARIABLES

  numset

CONSTANTS

  max_val

PROPERTIES

/*" This is the maximums value stored. "*/

  max_val = 1000000

INVARIANT

/*" This is the state invariant. "*/

  numset <: NAT1

INITIALISATION

  numset:={}

OPERATIONS

 enter(new) =    
   PRE 
     new: NAT1 & new <= max_val
   THEN
     numset :=  numset \/ {new}
   END;


 mx <-- maximum = 
    PRE 
       numset /= {}
    THEN
       mx  := max(numset) 
    END

END
