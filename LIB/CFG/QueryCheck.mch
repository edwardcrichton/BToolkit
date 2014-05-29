MACHINE           QueryCheck(STATUS)

SEES              String_TYPE

OPERATIONS

  status,comment <-- CHK_QUERY(query : STRING) =
  BEGIN status :: STATUS || comment :: STRING END

END
