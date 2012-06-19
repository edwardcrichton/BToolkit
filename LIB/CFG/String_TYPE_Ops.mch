MACHINE     String_TYPE_Ops

SEES        Bool_TYPE, String_TYPE

OPERATIONS

  rr <-- ASSIGN_ANY_STR = BEGIN rr :: STRING  END;

  bb <-- CMP_STR(rr : STRING & ss : STRING ) =  
 	 PRE size(rr) <= 1000 & size(ss) <= 1000 THEN bb:= bool(rr = ss) END;

 /* bb is TRUE when rr < ss, FALSE otherwise */
  bb <-- SMR_STR(rr : STRING & ss : STRING ) =  
 	 PRE size(rr) <= 1000 & size(ss) <= 1000 THEN bb :: BOOL END;

 /* bb is TRUE when rr a prefix (case insensitive) of ss, FALSE otherwise */
  bb <-- PFX_STR(rr : STRING & ss : STRING ) =  
 	 PRE size(rr) <= 1000 & size(ss) <= 1000 THEN bb :: BOOL END;

 /* bb is TRUE when rr a postfix (case insensitive) of ss, FALSE otherwise */
  bb <-- PSX_STR(rr : STRING & ss : STRING ) =  
 	 PRE size(rr) <= 1000 & size(ss) <= 1000 THEN bb :: BOOL END;

 /* bb is TRUE when rr a sub-string (case insensitive) of ss, FALSE otherwise */
  bb <-- SUB_STR(rr : STRING & ss : STRING ) =  
 	 PRE size(rr) <= 1000 & size(ss) <= 1000 THEN bb :: BOOL END;

  rr <-- CPY_STR(ss : STRING) =  
  	 PRE size(ss) <= 1000 THEN rr:=ss END;

  rr <-- CNC_STR(ss : STRING & tt : STRING) =  
  	 PRE size(ss) + size(tt) <= 1000 THEN rr:=(ss^tt) END;

  nn <-- LEN_STR(ss : STRING) = BEGIN nn := size(ss) END;

  cc <-- VAL_ITH_CHAR(ss : STRING & ii : 1..size(ss)) =
 	 PRE size(ss) <= 1000 THEN cc := ss(ii) END;

  nn <-- CHAR_TO_NAT(cc: CHAR) = BEGIN nn :: NAT END;
  
  ss <-- NAT_TO_STR(nn : NAT) = BEGIN ss :: STRING END
  
END

