MACHINE	 Int_TYPE_Ops 

SEES	Bool_TYPE,  Int_TYPE
 
OPERATIONS

  uu <-- MINI(vv:INT & ww:INT) = 
     SELECT vv <= ww THEN uu := vv 
     WHEN  ww <= vv THEN uu := ww END;

  uu <-- MAXI(vv:INT & ww:INT) = 
     SELECT vv >= ww THEN uu := vv 
     WHEN  ww >= vv THEN uu := ww END;

  uu <-- INCI(vv:INT) =
    PRE vv < MaxINT THEN uu:=vv+(+1) END;

  uu <-- DECI(vv:INT) =
    PRE vv > MinINT THEN uu:=vv-(+1) END;


  uu <-- ADDI(vv:INT & ww:INT) =
    PRE vv+ww : INT THEN uu:=vv+ww END;

  uu <-- MULI(vv:INT & ww:INT) =
    PRE vv*ww : INT THEN uu:=vv*ww END;

  uu <-- SUBI(vv:INT & ww:INT) =
    PRE vv-ww : INT THEN uu:=vv-ww END;

  uu <-- DIVI(vv:INT & ww:INT) =
    PRE ww /= +0 THEN uu:=vv/ww END;

  uu <-- MODI(vv:INT & ww:INT) =
    PRE ww /= +0 THEN uu:=vv-ww*(vv/ww) END;


  bb <-- EQLI(vv:INT & ww:INT) = BEGIN bb:=bool(vv=ww) END;

  bb <-- NEQI(vv:INT & ww:INT) = BEGIN bb:=bool(vv/=ww) END;

  bb <-- GTRI(vv:INT & ww:INT) = BEGIN bb:=bool(vv>ww) END;

  bb <-- GEQI(vv:INT & ww:INT) = BEGIN bb:=bool(vv>=ww) END;

  bb <-- SMRI(vv:INT & ww:INT) = BEGIN bb:=bool(vv<ww) END;

  bb <-- LEQI(vv:INT & ww:INT) = BEGIN bb:=bool(vv<=ww) END;

  bb <-- EQZI(vv:INT) = BEGIN bb:=bool(vv=(+0)) END

END
