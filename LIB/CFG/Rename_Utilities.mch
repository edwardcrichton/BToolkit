MACHINE           Rename_Utilities(OBJ)

SEES              String_TYPE, Bool_TYPE

OPERATIONS

  rep <-- Rename_RestorePreviousData (sysname : STRING & op : NAT ) =
  BEGIN rep :: BOOL END;

  nn <-- OBJ_TO_NAT(obj : OBJ) =
  BEGIN nn :: NAT END;

  ss <-- OBJ_TO_STR(obj : OBJ) =
  BEGIN ss :: STRING END

END
