MACHINE         Rename_Vfnc(VALUE,maxfld)

SEES            Bool_TYPE

VARIABLES       Rename_Vfnc

INVARIANT       Rename_Vfnc: 1..maxfld +-> VALUE

INITIALISATION  Rename_Vfnc := {}

OPERATIONS

  bb <-- Rename_TST_FLD_FNC(ff) =
  PRE
    ff: NAT
  THEN
    bb:=bool(ff:1..maxfld)
  END;

  bb <-- Rename_DEF_FNC(ff) =
  PRE
    ff: 1..maxfld
  THEN
    bb:=bool(ff:dom(Rename_Vfnc))
  END;

  bb,dd <-- Rename_FREE_FNC =
  IF (1..maxfld )- dom(Rename_Vfnc) /= {}  THEN
    bb := TRUE ||
    dd :: (1..maxfld) - dom(Rename_Vfnc)
  ELSE
    bb := FALSE ||
    dd :: 1..maxfld 
  END;


  Rename_STO_FNC(ff,vv) =
  PRE
    ff:1..maxfld &
    vv:VALUE
  THEN 
    Rename_Vfnc(ff):=vv
  END;

  Rename_RMV_FNC(ff) =
  PRE
    ff:dom(Rename_Vfnc)
  THEN 
    Rename_Vfnc:={ff} <<| Rename_Vfnc
  END;

  vv <-- Rename_VAL_FNC(ff) =
  PRE
    ff:dom(Rename_Vfnc)
  THEN 
    vv:=Rename_Vfnc(ff)
  END;


  bb <-- Rename_EQL_FNC(ff,vv) =
  PRE
    vv:VALUE &
    ff:dom(Rename_Vfnc)
  THEN
    bb:=bool(Rename_Vfnc(ff)=vv)
  END;

  bb <-- Rename_NEQ_FNC(ff,vv) =
  PRE
    vv:VALUE &
    ff:dom(Rename_Vfnc)
  THEN
    bb:=bool(Rename_Vfnc(ff)/=vv)
  END;


/**************  save/restore host byte order **************/

   Rename_SAV_FNC = BEGIN skip END;

   Rename_RST_FNC =
   BEGIN  Rename_Vfnc :: 1..maxfld +-> VALUE END;


/**************  save/restore network byte order **************/

   Rename_SAVN_FNC = BEGIN skip END;
 
   Rename_RSTN_FNC =
   BEGIN  Rename_Vfnc :: 1..maxfld +-> VALUE END




END

