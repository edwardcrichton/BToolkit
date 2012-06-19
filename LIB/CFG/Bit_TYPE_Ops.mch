MACHINE     Bit_TYPE_Ops

SEES        Bool_TYPE, Bit_TYPE

OPERATIONS

  ss <-- NO_BITS = BEGIN ss := (1..32)*{FALSE}  END;

  ss <-- LFT_BTS(tt,nn) =
  PRE
    tt: BITS &
    nn: 1..32
  THEN
    ss:= ( (tt\|/nn) ^ ((1..nn)*{FALSE}) )
  END;

  ss <-- RHT_BTS(tt,nn) =
  PRE
    tt :BITS &
    nn :1..32
  THEN
    ss:=( ( (1..nn)*{first(tt)} ) ^ (tt/|\(32-nn)) )
  END;

  ss <-- CPL_BTS(tt) =
  PRE
    tt: BITS
  THEN
    ss:= ( tt;tcp )
  END;

  ss <-- LND_BTS(tt,uu) =
  PRE
    tt: BITS &
    uu: BITS
  THEN
    ss:= ( (tt >< uu);tnd )
  END;

  ss <-- LOR_BTS(tt,uu) =
  PRE
    tt: BITS &
    uu: BITS
  THEN
    ss:= ( (tt >< uu);tor )
  END;

   ss <-- LXR_BTS(tt,uu) =
  PRE
    tt: BITS &
    uu: BITS
  THEN
    ss:= ( (tt >< uu);txr )
  END;

  ss <-- MSK_BTS(mm,nn) =
  PRE
    mm:0..32 &
    nn:0..32 &
    mm<=nn
  THEN
    ss:= ( ((1..32)*{FALSE}) <+ ((mm..nn)*{TRUE})  )
  END;

  ss <-- VMS_BTS(bb,mm,nn) =
  PRE
    bb:BITS &
    mm:1..32 &
    nn:1..32 &
    mm<=nn
  THEN
    ss:= ((1..32)*{FALSE}) <+ ( bb\|/(mm-1)/|\(nn-mm+1) ) 
  END;

   ss <-- MMS_BTS(bb,mm,nn,vv) =
  PRE
    bb: BITS &
    mm:1..32 &
    nn:1..32 &
    vv: BITS &
    mm<=nn
  THEN
    LET cc BE
      cc = vv \|/ (32-nn+mm-1)
    IN
      ss:= ( bb/|\(mm-1) ^ cc ^ (bb\|/nn) )
    END
  END;


  ss <-- VAL_BTS(bb,nn) =
  PRE
    bb : BITS &
    nn : 1..32 &
    bb(nn) : BOOL
  THEN
    ss := bb(nn)
  END;

  ss <-- STO_BTS(bb,nn,vv) =
  PRE
    bb : BITS  &
    nn : 1..32 &
    vv : BOOL
  THEN
    ss := bb <+ {nn |-> vv}
  END

END
