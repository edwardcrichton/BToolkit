MACHINE

  RRMan(RESOURCE, max_res)

CONSTRAINTS

  card(RESOURCE) >= max_res

SEES

  Bool_TYPE

INCLUDES

  RMan(RESOURCE),
  bkup.RMan(RESOURCE)

INVARIANT

  card(rfree) <= max_res &
  card(bkup.rfree) <= max_res

OPERATIONS

  res <-- rec_alloc =
    PRE
      rfree /= {}
    THEN
      ANY rr
      WHERE
        rr : rfree
      THEN
        res := rr ||
        alloc(rr)
      END
    END;

  ans <-- is_any_free =
    BEGIN
      ans := bool(rfree /= {})
    END;

  rec_free(rr) =
    PRE
      rr : RESOURCE - rfree &
      card(rfree) < max_res
    THEN
      free(rr)
    END;

  ans <-- is_free(rr) =
    PRE
      rr : RESOURCE
    THEN
      ans := bool(rr : rfree)
    END;

  rec_backup =
    BEGIN
      bkup.setfree(rfree)
    END;

  rec_restore =
    BEGIN
      setfree(bkup.rfree)
    END

END
