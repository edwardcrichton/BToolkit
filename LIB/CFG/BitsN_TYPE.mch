MACHINE           BitsN_TYPE

SEES

   Bit_TYPE, Bool_TYPE

CONSTANTS

  BITSN,
  tsb

PROPERTIES

  BITSN : (1 .. 32) --> POW(1..32 +-> BOOL) &

  (!nn. (nn : 1..32 => BITSN(nn) = 1..nn --> BOOL)) &


  tsb =  {(FALSE|->FALSE) |-> FALSE,
         (FALSE|->TRUE ) |-> FALSE, 
         (TRUE|->FALSE ) |-> TRUE,
         (TRUE |->TRUE ) |-> FALSE }
  
END
