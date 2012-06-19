MACHINE

  Rename_Nfnc(maxint,maxfld)

CONSTRAINTS

   maxint <= 2147483646 &
   maxfld <= 2147483646
   
SEES

 Bool_TYPE

VARIABLES

  Rename_Nfnc

INVARIANT

  Rename_Nfnc: 1..maxfld +-> 0..maxint

INITIALISATION

  Rename_Nfnc := {}

OPERATIONS

  bb <-- Rename_TST_FLD_NFNC(ff) =
  PRE
    ff: NAT
  THEN
    bb:=bool(ff:1..maxfld)
  END;

 bb <-- Rename_DEF_NFNC(ff) =
  PRE
    ff: 1..maxfld
  THEN
    bb:=bool(ff:dom(Rename_Nfnc))
  END;

  bb,dd <-- Rename_FREE_NFNC =
  IF (1..maxfld )- dom(Rename_Nfnc) /= {}  THEN
    bb := TRUE ||
    dd :: (1..maxfld) - dom(Rename_Nfnc)
  ELSE
    bb := FALSE ||
    dd :: 1..maxfld 
  END;


  Rename_STO_NFNC(ff,vv) =
  PRE
    ff:1..maxfld &
    vv:0..maxint
  THEN 
    Rename_Nfnc(ff):=vv
  END;

  Rename_RMV_NFNC(ff) =
  PRE
    ff:dom(Rename_Nfnc)
  THEN 
    Rename_Nfnc:={ff} <<| Rename_Nfnc
  END;

  Rename_ADD_NFNC(ff,vv) =
  PRE
    vv:0..maxint &
    ff:dom(Rename_Nfnc) &
    Rename_Nfnc(ff)+vv <= maxint
  THEN 
    Rename_Nfnc(ff):=Rename_Nfnc(ff)+vv
  END;

  Rename_MUL_NFNC(ff,vv) =
  PRE
    vv:0..maxint &
    ff:dom(Rename_Nfnc) &
    Rename_Nfnc(ff)*vv <= maxint
  THEN 
    Rename_Nfnc(ff):=Rename_Nfnc(ff)*vv
  END;

  Rename_SUB_NFNC(ff,vv) =
  PRE
    vv:0..maxint &
    ff:dom(Rename_Nfnc) &
    Rename_Nfnc(ff) >= vv
  THEN 
    Rename_Nfnc(ff):=Rename_Nfnc(ff)-vv
  END;

  Rename_DIV_NFNC(ff,vv) =
  PRE
    vv:1..maxint &
    ff:dom(Rename_Nfnc)
  THEN 
    Rename_Nfnc(ff):=Rename_Nfnc(ff)/vv
  END;

  Rename_MOD_NFNC(ff,vv) =
  PRE
    vv:1..maxint &
    ff:dom(Rename_Nfnc)
  THEN 
    Rename_Nfnc(ff):=Rename_Nfnc(ff)-vv*(Rename_Nfnc(ff)/vv)
  END;

  vv <-- Rename_VAL_NFNC(ff) =
  PRE
    ff:dom(Rename_Nfnc)
  THEN 
    vv:=Rename_Nfnc(ff)
  END;


  bb <-- Rename_EQL_NFNC(ff,vv) =
  PRE
    vv:0..maxint &
    ff:dom(Rename_Nfnc)
  THEN
    bb:=bool(Rename_Nfnc(ff)=vv)
  END;

  bb <-- Rename_NEQ_NFNC(ff,vv) =
  PRE
    vv:0..maxint &
    ff:dom(Rename_Nfnc)
  THEN
    bb:=bool(Rename_Nfnc(ff)/=vv)
  END;

  bb <-- Rename_GTR_NFNC(ff,vv) =
  PRE
    vv:0..maxint &
    ff:dom(Rename_Nfnc)
  THEN
    bb:=bool(Rename_Nfnc(ff)>vv)
  END;

  bb <-- Rename_GEQ_NFNC(ff,vv) =
  PRE
    vv:0..maxint &
    ff:dom(Rename_Nfnc)
  THEN
    bb:=bool(Rename_Nfnc(ff)>=vv)
  END;

  bb <-- Rename_SMR_NFNC(ff,vv) =
  PRE
    vv:0..maxint &
    ff:dom(Rename_Nfnc)
  THEN
    bb:=bool(Rename_Nfnc(ff)<vv)
  END;

  bb <-- Rename_LEQ_NFNC(ff,vv) =
  PRE
    vv:0..maxint &
    ff:dom(Rename_Nfnc)
  THEN
    bb:=bool(Rename_Nfnc(ff)<=vv)
  END;


/**************  save/restore host byte order **************/

  Rename_SAV_FNC = BEGIN skip END;

 
  Rename_RST_FNC =
  BEGIN  Rename_Nfnc  :: 1..maxfld +-> 0..maxint END;



/**************  save/restore network byte order **************/

  Rename_SAVN_FNC = BEGIN skip END;

 
  Rename_RSTN_FNC =
  BEGIN  Rename_Nfnc  :: 1..maxfld +-> 0..maxint END



END

