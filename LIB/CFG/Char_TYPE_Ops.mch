MACHINE     Char_TYPE_Ops

SEES        Bool_TYPE, Char_TYPE

OPERATIONS

  rr <-- ASSIGN_ANY_STR = BEGIN rr :: STRING  END;

  bb <-- CMP_STR(rr:STRING & ss: STRING ) =  
 	 PRE size(rr) <= 1000 & size(ss) <= 1000 THEN bb:= bool(rr = ss) END;

 /* bb is TRUE when rr < ss, FALSE otherwise */
  bb <-- SMR_STR(rr:STRING & ss: STRING ) =  
 	 PRE size(rr) <= 1000 & size(ss) <= 1000 THEN bb :: BOOL END;

  rr <-- CPY_STR(ss  : STRING) =  
  	 PRE size(ss) <= 1000 THEN rr:=ss END;

  rr <-- CNC_STR(ss  : STRING & tt : STRING) =  
  	 PRE size(ss) + size(tt) <= 1000 THEN rr:=(ss^tt) END;

  nn <-- LEN_STR(ss : STRING) = BEGIN nn := size(ss) END;

  cc <-- VAL_ITH_CHAR(ss: STRING & ii: 1..size(ss)) =
 	 PRE size(ss) <= 1000 THEN cc := ss(ii) END;

  nn <-- CHAR_TO_NAT(cc: CHAR) = BEGIN nn :: NAT END
  
END

