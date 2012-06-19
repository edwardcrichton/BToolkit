MACHINE

  RMan(RES)

VARIABLES

  rfree

INVARIANT

  rfree <: RES

INITIALISATION

  rfree := {}

OPERATIONS

  alloc(rr) =
    PRE
      rr : rfree
    THEN
      rfree := rfree - {rr}
    END;

  free(rr) =
    PRE
      rr : RES & rr /: rfree
    THEN
      rfree := rfree \/ {rr}
    END;

  setfree(rrs) =
    PRE
      rrs <: RES
    THEN
      rfree := rrs
    END

END
