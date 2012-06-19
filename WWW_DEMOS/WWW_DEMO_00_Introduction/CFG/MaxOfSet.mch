MACHINE  MaxOfSet(max_val)

/*"
The specification is parameterised by {\em max\_val\/}, which has the
implicit constraint that it is a natural number:
"*/
  
CONSTRAINTS

/*"
We further constrain {\em max\_val\/} by giving it an upper-bound:
"*/

  max_val <= 1000000

VARIABLES

/*"
In this (very) simple example we have only one variable:
"*/

  numset

INVARIANT

/*"
This is the state invariant - {\em numset\/} a set of numbers, each one
in the range from 0 upto {\em max\_val\/}:
"*/

  numset <: 0..max_val

INITIALISATION

/*"
Initially the set contains the single number 0:
"*/

  numset:={ 0 }


OPERATIONS

/*"
{\bf enter}\\[.5ex]
The first operation allows us to add a number to the set, and has the
input parameter {\em num\/}; the precondition ensures that {\em num\/} is
in the appropriate range (so that we do not break the invariant!); we use
set union to specify this operation:
"*/

 enter(num) =    
   PRE 
     num: NAT & num <= max_val
   THEN
     numset :=  numset \/ {num}
   END;

/*" {\bf maximum}\\[.5ex]
The second operation allows us to obtain the maximum number currently
stored in the set, the value being returned in the output parameter {\em
maximum\/}. We specify this operation using the mathematical {\em max\/}
function, which requires the set to be non-empty, and so we must have
this as our precondition
"*/

 mx <-- maximum = 
    PRE 
       numset /= {}
    THEN
       mx  := max(numset)
    END

END
