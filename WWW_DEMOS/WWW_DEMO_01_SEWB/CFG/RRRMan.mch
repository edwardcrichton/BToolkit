MACHINE

  RRRMan

SETS

  MYRESOURCE;
  RESPONSE = { success, alreadyfree, nomorefree }

OPERATIONS

  rr, resp <-- allocate =
    BEGIN
      rr :: MYRESOURCE ||
      resp :: {success, nomorefree}
    END;

  resp <-- deallocate(rr) =
    PRE
      rr: MYRESOURCE
    THEN
      resp :: {success, alreadyfree}
    END;

  backup = skip;

  restore = skip

END
