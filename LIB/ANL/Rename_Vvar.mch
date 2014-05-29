MACHINE

  Rename_Vvar(VALUE)

SEES

 Bool_TYPE

VARIABLES

  Rename_Vvar

INVARIANT

  Rename_Vvar:VALUE

INITIALISATION

  Rename_Vvar::VALUE

OPERATIONS

  vv <-- Rename_VAL_VAR =
  BEGIN 
    vv:=Rename_Vvar
  END;

  Rename_STO_VAR(vv) =
  PRE
    vv:VALUE
  THEN 
    Rename_Vvar:=vv
  END;

  bb <-- Rename_EQL_VAR(vv) =
  PRE
    vv:VALUE
  THEN
    bb:=bool(Rename_Vvar=vv)
  END;

  bb <-- Rename_NEQ_VAR(vv) =
  PRE
    vv:VALUE
  THEN
    bb:=bool(Rename_Vvar/=vv)
  END;


/**************  save/restore host byte order **************/

  Rename_SAV_VAR =
  BEGIN skip END;

  Rename_RST_VAR =
  BEGIN
     Rename_Vvar :: VALUE
  END;

/**************  save/restore network byte order **************/

  Rename_SAVN_VAR =
  BEGIN skip END;

  Rename_RSTN_VAR =
  BEGIN
     Rename_Vvar :: VALUE
  END

END




