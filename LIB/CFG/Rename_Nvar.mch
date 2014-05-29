MACHINE         Rename_Nvar(maxint)

CONSTRAINTS     maxint <= 2147483646

SEES            Bool_TYPE

VARIABLES       Rename_Nvar

INVARIANT       Rename_Nvar:0..maxint

INITIALISATION  Rename_Nvar:=0

OPERATIONS

  vv <-- Rename_VAL_NVAR =
  BEGIN 
    vv:=Rename_Nvar
  END;

  Rename_STO_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN 
    Rename_Nvar:=vv
  END;

  uu <-- Rename_MIN_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    uu:=min({Rename_Nvar,vv})
  END;

  uu <-- Rename_MAX_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    uu:=max({Rename_Nvar,vv})
  END;

  bb <-- Rename_PRE_INC_NVAR =
  BEGIN
    bb:=bool(Rename_Nvar<maxint)
  END;

  Rename_INC_NVAR =
  PRE
    Rename_Nvar+1:0..maxint
  THEN
    Rename_Nvar:=Rename_Nvar+1
  END;

  bb <-- Rename_PRE_DEC_NVAR =
  BEGIN
    bb:=bool(Rename_Nvar>0)
  END;

  Rename_DEC_NVAR =
  PRE
    Rename_Nvar:1..maxint
  THEN
    Rename_Nvar:=Rename_Nvar-1
  END;

  bb <-- Rename_PRE_ADD_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    bb:=bool(Rename_Nvar+vv <= maxint)
  END;

  Rename_ADD_NVAR(vv) =
  PRE
    vv:0..maxint &
    Rename_Nvar+vv <= maxint
  THEN 
    Rename_Nvar:=Rename_Nvar+vv
  END;

  bb <-- Rename_PRE_MUL_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    bb:=bool(Rename_Nvar*vv <= maxint)
  END;

  Rename_MUL_NVAR(vv) =
  PRE
    vv:0..maxint &
    Rename_Nvar*vv <= maxint
  THEN 
    Rename_Nvar:=Rename_Nvar*vv
  END;

  bb <-- Rename_PRE_SUB_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    bb:=bool(Rename_Nvar-vv >= 0)
  END;

  Rename_SUB_NVAR(vv) =
  PRE
    vv:0..maxint &
    Rename_Nvar-vv >= 0
  THEN 
    Rename_Nvar:=Rename_Nvar-vv
  END;

  bb <-- Rename_PRE_DIV_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    bb:=bool(vv > 0)
  END;

  Rename_DIV_NVAR(vv) =
  PRE
    vv:1..maxint
  THEN 
    Rename_Nvar:=Rename_Nvar/vv
  END;

  bb <-- Rename_PRE_MOD_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    bb:=bool(vv > 0)
  END;

  Rename_MOD_NVAR(vv) =
  PRE
    vv:1..maxint
  THEN 
    Rename_Nvar:=Rename_Nvar-vv*(Rename_Nvar/vv)
  END;

  bb <-- Rename_EQL_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    bb:=bool(Rename_Nvar=vv)
  END;

  bb <-- Rename_NEQ_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    bb:=bool(Rename_Nvar/=vv)
  END;

  bb <-- Rename_GTR_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    bb:=bool(Rename_Nvar>vv)
  END;

  bb <-- Rename_GEQ_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    bb:=bool(Rename_Nvar>=vv)
  END;

  bb <-- Rename_SMR_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    bb:=bool(Rename_Nvar<vv)
  END;

  bb <-- Rename_LEQ_NVAR(vv) =
  PRE
    vv:0..maxint
  THEN
    bb:=bool(Rename_Nvar<=vv)
  END;


/**************  save/restore host byte order **************/

  Rename_SAV_NVAR =
  BEGIN
     skip
  END;

  Rename_RST_NVAR =
  BEGIN
    Rename_Nvar :: 0..maxint
  END;

/**************  save/restore network byte order **************/

  Rename_SAVN_NVAR =
  BEGIN
     skip
  END;

  Rename_RSTN_NVAR =
  BEGIN
    Rename_Nvar :: 0..maxint
  END

END



