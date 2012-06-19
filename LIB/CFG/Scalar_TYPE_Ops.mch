MACHINE	 Scalar_TYPE_Ops 

SEES	Bool_TYPE,  Scalar_TYPE
 
OPERATIONS

  uu <-- SCL(vv:SCALAR) = BEGIN uu:=vv END;

  uu <-- MIN(vv:SCALAR & ww:SCALAR) = BEGIN uu:=min({vv,ww}) END;

  uu <-- MAX(vv:SCALAR & ww:SCALAR) = BEGIN uu:=max({vv,ww}) END;

  uu <-- INC(vv:SCALAR) =
    PRE vv < MaxScalar THEN uu:=vv+1 END;

  uu <-- DEC(vv:SCALAR) =
    PRE 0<vv THEN uu:=vv-1 END;

  uu <-- ADD(vv:SCALAR & ww:SCALAR) =
    PRE vv+ww <= MaxScalar THEN uu:=vv+ww END;

  uu <-- MUL(vv:SCALAR & ww:SCALAR) =
    PRE vv*ww <= MaxScalar THEN uu:=vv*ww END;

  uu <-- SUB(vv:SCALAR & ww:SCALAR) =
    PRE ww<=vv THEN uu:=vv-ww END;

  uu <-- DIV(vv:SCALAR & ww:SCALAR) =
    PRE 0<ww THEN uu:=vv/ww END;

  uu <-- MOD(vv:SCALAR & ww:SCALAR) =
    PRE 0<ww THEN uu:=vv-ww*(vv/ww) END;

  bb <-- EQL(vv:SCALAR & ww:SCALAR) = BEGIN bb:=bool(vv=ww) END;

  bb <-- NEQ(vv:SCALAR & ww:SCALAR) = BEGIN bb:=bool(vv/=ww) END;

  bb <-- GTR(vv:SCALAR & ww:SCALAR) = BEGIN bb:=bool(vv>ww) END;

  bb <-- GEQ(vv:SCALAR & ww:SCALAR) = BEGIN bb:=bool(vv>=ww) END;

  bb <-- SMR(vv:SCALAR & ww:SCALAR) = BEGIN bb:=bool(vv<ww) END;

  bb <-- LEQ(vv:SCALAR & ww:SCALAR) = BEGIN bb:=bool(vv<=ww) END;

  bb <-- EQZ(vv:SCALAR) = BEGIN bb:=bool(vv=0) END;

  nn <-- RND(mm:SCALAR) = BEGIN nn :: 0..mm END


END
