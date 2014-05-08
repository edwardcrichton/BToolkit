/*" \begin{center} {\bf DEMO1\_MAXIMUM} \end{center} "*/

MACHINE               MaxOfSet

VARIABLES             numset

CONSTANTS             max_val

PROPERTIES            max_val = 1000000

/*" This is the maximum value stored. "*/

INVARIANT             numset <: NAT1

/*" This is the state invariant. "*/

INITIALISATION        numset:={}

OPERATIONS

 enter(new) =    
   PRE 
     new : NAT1 & new <= max_val
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
