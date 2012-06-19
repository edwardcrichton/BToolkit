MACHINE           Rename_RCD(VALUE,maxfld,maxrcd)

CONSTRAINTS       maxrcd>0

SEES              Bool_TYPE, Byt_TYPE

SETS              Rename_RCD

PROPERTIES        card(Rename_RCD) = maxrcd

VARIABLES         Rename_rcd, Rename_rcd_fnc

INVARIANT

  Rename_rcd <: Rename_RCD &
  Rename_rcd_fnc: Rename_rcd --> (1..maxfld +-> VALUE)     

INITIALISATION

  Rename_rcd := {} ||
  Rename_rcd_fnc := {}

OPERATIONS

  bb <-- Rename_RCD_IDX(idx : BYTE) =
    BEGIN bb := bool(b2n(idx) : 0..maxfld) END;

  bb <-- Rename_RCD_FULL =
    BEGIN bb:=bool(Rename_rcd = Rename_RCD) END;

  rr <-- Rename_RCD_CRE =
    PRE Rename_rcd /= Rename_RCD THEN
      ANY new_rcd WHERE new_rcd : Rename_RCD - Rename_rcd THEN
        Rename_rcd := Rename_rcd \/ {new_rcd} ||
        Rename_rcd_fnc(new_rcd) := {} ||
        rr := new_rcd
      END
    END;

  Rename_RCD_KILL(rr : Rename_RCD) =
    PRE rr : Rename_rcd THEN
      Rename_rcd := Rename_rcd - {rr} ||
      Rename_rcd_fnc := {rr} <<| Rename_rcd_fnc
    END;

  bb <-- Rename_RCD_DEF(rr : Rename_RCD) =
    BEGIN bb := bool(rr : Rename_rcd) END;

  Rename_RCD_STO(rr : Rename_RCD & idx : BYTE & vv : VALUE) =
    PRE rr : Rename_rcd & b2n(idx) : 1..maxfld THEN
      Rename_rcd_fnc(rr)(b2n(idx)) := vv
   END;

  vv <-- Rename_RCD_VAL(rr : Rename_RCD & idx : BYTE) =
    PRE rr : Rename_rcd & b2n(idx) : dom(Rename_rcd_fnc(rr)) THEN
      vv := Rename_rcd_fnc(rr)(b2n(idx))
    END

END
