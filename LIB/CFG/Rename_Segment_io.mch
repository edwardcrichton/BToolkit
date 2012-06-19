MACHINE     Rename_Segment_io(SEGMENT)

SEES       String_TYPE

OPERATIONS

   rr <-- Rename_GET_SEG = 
  BEGIN 
     rr:: SEGMENT      /* multiple words */
  END;
  
  rr <-- Rename_GET_PROMPT_SEG(ss) = 
  PRE 
     ss : STRING
  THEN
     rr:: SEGMENT     /* multiple words */
  END;

  Rename_PUT_SEG(dd) = 
  PRE 
     dd:SEGMENT
  THEN 
     skip
  END


END
