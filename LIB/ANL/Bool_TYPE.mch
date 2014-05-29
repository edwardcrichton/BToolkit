MACHINE

  Bool_TYPE

SETS

  BOOL = {FALSE,TRUE}

OPERATIONS

  bb <-- CNJ_BOOL(cc,dd) =
  PRE
    cc:BOOL &
    dd:BOOL
  THEN 
    bb:=bool((cc=TRUE) & (dd=TRUE))
  END;

  bb <-- DIS_BOOL(cc,dd) =
  PRE
    cc:BOOL &
    dd:BOOL
  THEN 
    bb:=bool((cc=TRUE) or (dd=TRUE))
  END;

  bb <-- NEG_BOOL(cc) =
  PRE
    cc:BOOL
  THEN
    bb:=bool(cc=FALSE)
  END;

  vv <-- BTS_BOOL(bb) =
  PRE
    bb:BOOL
  THEN
    IF bb=TRUE THEN
      vv:=1
    ELSE
      vv:=0
    END
  END

END
