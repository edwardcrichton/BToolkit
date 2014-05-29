MACHINE

  Rename_set(VALUE,maxcrd)

SEES

 Bool_TYPE

VARIABLES

  Rename_sset,Rename_ordn

INVARIANT

  Rename_sset: FIN(VALUE) &
  Rename_ordn: perm(Rename_sset) &
  card(Rename_sset)<=maxcrd

INITIALISATION

  Rename_sset,Rename_ordn:={},<>

OPERATIONS

  bb <-- Rename_FUL_SET =
  BEGIN
    bb:=bool(card(Rename_sset)=maxcrd)
  END;

  bb <-- Rename_XST_IDX_SET(ii) =
  PRE
    ii: 1..maxcrd
  THEN
    bb:=bool(ii:1..card(Rename_sset))
  END;

  nn <-- Rename_CRD_SET =
  BEGIN
    nn:=card(Rename_sset)
  END;

  vv <-- Rename_VAL_SET(ii) =
  PRE
    ii:1..card(Rename_sset)
  THEN 
    vv:=Rename_ordn(ii)
  END;

  vv <-- Rename_ANY_SET =
  PRE
    not(Rename_sset= {})
  THEN 
    vv:: Rename_sset
  END;

  Rename_CLR_SET =
  BEGIN
    Rename_sset := {} ||
    Rename_ordn := <>
  END;

  Rename_ENT_SET(vv) =
  PRE
    vv: VALUE &
    card(Rename_sset) < maxcrd
  THEN
    Rename_sset:=Rename_sset \/ {vv} ||
    Rename_ordn::perm(Rename_sset \/ {vv})
  END;

  Rename_RMV_SET(vv) =
  PRE
    vv: VALUE
  THEN
    Rename_sset:=Rename_sset - {vv} ||
    Rename_ordn::perm(Rename_sset - {vv})
  END;

  bb <-- Rename_MBR_SET(vv) =
  PRE
    vv: VALUE
  THEN
    bb:= bool(vv:Rename_sset)
  END;

  bb <-- Rename_EMP_SET =
  BEGIN
    bb:= bool(Rename_sset={})
  END;

  
/**************  save/restore host byte order **************/

  Rename_SAV_SET= skip;

  Rename_RST_SET =
  ANY rset,rseq WHERE
     rset: FIN(VALUE) &
     rseq : perm(rset) &
     card(rset) <= maxcrd
  THEN
    Rename_sset := rset ||
    Rename_ordn := rseq
  END;

/**************  save/restore network byte order **************/

  Rename_SAVN_SET= skip;

  Rename_RSTN_SET =
  ANY rset,rseq WHERE
     rset: FIN(VALUE) &
     rseq : perm(rset) &
     card(rset) <= maxcrd
  THEN
    Rename_sset := rset ||
    Rename_ordn := rseq
  END


END
