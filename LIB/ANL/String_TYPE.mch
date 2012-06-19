MACHINE

  String_TYPE

SETS

  CHAR; STRING

CONSTANTS
 
  EmptyString,
  CHARperWORD
  
PROPERTIES


  STRING = {ss | ss : seq(CHAR) & size(ss) <= 1000 } &

  EmptyString : STRING &

  size(EmptyString) = 0 &

  EmptyString = "" &
  
  CHARperWORD = 4 

OPERATIONS

  rr <-- ASSIGN_ANY_STR = 
  BEGIN
    rr :: STRING
  END;

  rr <-- CPY_STR(ss) =  
  PRE
    ss : STRING &
    size(ss) <= 1000
  THEN
    rr:=ss 
  END

END
