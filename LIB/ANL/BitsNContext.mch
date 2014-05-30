MACHINE

  BitsNContext

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
  

OPERATIONS


  rr <-- NO_BTSN(len) = 
  PRE
    len : 1..32
  THEN
    rr := (1..len) * {FALSE}
  END;

  rr <-- STO_BTSN(len,reg,nn,bb) =
  PRE
    len : 1 .. 32 &
    reg : BITSN (len) &
    nn : 1 .. len &
    bb : BOOL
  THEN
    rr := reg <+ {nn |-> bb}
  END;

  bb <-- VAL_BTSN(len,reg,nn) =
  PRE
    len : 1 .. 32 &
    reg : BITSN (len) &
    nn : 1 .. len
  THEN
    bb := reg (nn)
  END;

  rr <-- CPL_BTSN(len,reg) =
  PRE
    len : 1 .. 32 &
    reg : BITSN (len) 
  THEN
    rr := (reg ; tcp)
  END;

  rr <-- SUB_BTSN(len,reg1,reg2) =
  PRE
    len : 1 .. 32 &
    reg1 : BITSN (len) &
    reg2 : BITSN (len) 
  THEN
    rr := ((reg1 >< reg2) ; tsb)
  END



END
