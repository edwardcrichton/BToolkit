MACHINE      Rename_Segment_Ops(WORD)

OPERATIONS

   rr <-- Rename_ASSIGN_ANY_SEG = 
  BEGIN
    rr :: WORD
  END;

  rr <-- Rename_CPY_SEG(ss) =  
  PRE
    ss : WORD 
  THEN
    rr:=ss 
  END



END

