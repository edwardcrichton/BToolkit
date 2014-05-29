MACHINE

  Rename_Bit_String(strsize)

CONSTRAINTS

  strsize <= 32

SEES

  Bool_TYPE

SETS

  Rename_BITS

CONSTANTS

  bnd,bor,bxr

PROPERTIES

  Rename_BITS = 1..strsize --> BOOL &
 
 
  bnd = {(FALSE|->FALSE) |-> FALSE,
         (FALSE|->TRUE ) |-> FALSE, 
         (TRUE|->FALSE ) |-> FALSE,
         (TRUE |->TRUE ) |-> TRUE } &


  bor = {(FALSE|->FALSE) |-> FALSE,
         (FALSE|->TRUE ) |-> TRUE, 
         (TRUE|->FALSE ) |-> TRUE,
         (TRUE |->TRUE ) |-> TRUE } &

  bxr = {(FALSE|->FALSE) |-> FALSE,
         (FALSE|->TRUE ) |-> TRUE, 
         (TRUE|->FALSE ) |-> TRUE,
         (TRUE |->TRUE ) |-> FALSE }


OPERATIONS

  ss <--Rename_NO_BITS = BEGIN ss := (1..strsize)*{FALSE}  END;

  ss <-- Rename_LND_BTS(tt,uu) =
  PRE
    tt: Rename_BITS &
    uu: Rename_BITS
  THEN
    ss:= ( (tt >< uu);bnd )
  END;

  ss <-- Rename_LOR_BTS(tt,uu) =
  PRE
    tt: Rename_BITS &
    uu: Rename_BITS
  THEN
    ss:= ( (tt >< uu);bor )
  END;

  ss <-- Rename_LXR_BTS(tt,uu) =
  PRE
    tt: Rename_BITS &
    uu: Rename_BITS
  THEN
    ss:= ( (tt >< uu);bxr )
  END;


  ss <-- Rename_VAL_BTS(bb,nn) =
  PRE
    bb : Rename_BITS &
    nn : 1..strsize &
    bb(nn) : BOOL
  THEN
    ss := bb(nn)
  END;

  ss <-- Rename_STO_BTS(bb,nn,vv) =
  PRE
    bb : Rename_BITS  &
    nn : 1..strsize &
    vv : BOOL
  THEN
    ss := bb <+ {nn |-> vv}
  END

  

END
