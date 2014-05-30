MACHINE      Bit_TYPE

SETS	     BITS

SEES         Bool_TYPE

CONSTANTS    tcp,tnd,tor,txr

PROPERTIES

  BITS = 1..32 --> BOOL &
 
  tcp = { TRUE |-> FALSE , FALSE |-> TRUE } &
 
  tnd = {(FALSE|->FALSE) |-> FALSE,
         (FALSE|->TRUE ) |-> FALSE, 
         (TRUE|->FALSE ) |-> FALSE,
         (TRUE |->TRUE ) |-> TRUE } &


  tor = {(FALSE|->FALSE) |-> FALSE,
         (FALSE|->TRUE ) |-> TRUE, 
         (TRUE|->FALSE ) |-> TRUE,
         (TRUE |->TRUE ) |-> TRUE } &

  txr = {(FALSE|->FALSE) |-> FALSE,
         (FALSE|->TRUE ) |-> TRUE,  
         (TRUE|->FALSE ) |-> TRUE,
         (TRUE |->TRUE ) |-> FALSE }
   

END
