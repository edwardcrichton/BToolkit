MACHINE

  Rename_set_obj(VALUE,maxobj,maxmem)

CONSTRAINTS

  maxobj>0

SEES

  Bool_TYPE

SETS

  Rename_SETOBJ

PROPERTIES

  card(Rename_SETOBJ) = maxobj

VARIABLES

  Rename_settok, Rename_setstruct, Rename_setord

INVARIANT

  Rename_settok <: Rename_SETOBJ &
  Rename_setstruct: Rename_settok --> FIN(VALUE) &
  Rename_setord: Rename_settok --> seq(VALUE) &
  !rx.(
    rx:Rename_settok => Rename_setord(rx) : perm(Rename_setstruct(rx))
    )

INITIALISATION

  Rename_settok, Rename_setstruct, Rename_setord := {},{},{}

OPERATIONS

/**************** General Query functions ***********************/

  bb <-- Rename_MEM_FUL_SET_OBJ =
  BEGIN
    bb::BOOL
  END;

  

bb <-- Rename_OBJ_FUL_SET_OBJ =
  BEGIN
    bb:=bool(Rename_settok = Rename_SETOBJ)
  END;

  pp <-- Rename_ANY_SET_OBJ =
  BEGIN
    pp :: Rename_SETOBJ
  END;


  bb <-- Rename_XST_SET_OBJ(pp) =
  PRE
    pp: Rename_SETOBJ
  THEN
    bb:=bool(pp:Rename_settok)
  END;


/************ Operations for introducing and deleting sets **********/


  Rename_INI_SET_OBJ =
  BEGIN
    Rename_settok, Rename_setstruct, Rename_setord := {},{},{}
  END;

  bb,pp <-- Rename_CRE_SET_OBJ =
  IF Rename_settok /= Rename_SETOBJ THEN
      ANY qq WHERE
        qq: Rename_SETOBJ - Rename_settok
      THEN
        Rename_setstruct(qq):={} ||
        Rename_setord(qq):=<> ||
        Rename_settok := Rename_settok \/ {qq} ||
        pp:=qq ||
        bb := TRUE
      END
  ELSE
      bb:= FALSE || pp :: Rename_SETOBJ
  END;

  Rename_KIL_SET_OBJ(qq) =
  PRE
    qq: Rename_settok
  THEN
    Rename_setstruct := {qq} <<| Rename_setstruct ||
    Rename_setord := {qq} <<| Rename_setord ||
    Rename_settok := Rename_settok - {qq}
  END;



/************ Accessing a set using ordinal number *****************/


  bb <-- Rename_XST_ORD_SET_OBJ(pp,ii) =
  PRE
    pp: Rename_settok &
    ii: NAT
  THEN
    bb:=bool(ii:1.. card(Rename_setstruct(pp)))
  END;

  vv <-- Rename_VAL_SET_OBJ(pp,ii) =
  PRE
    pp: Rename_settok &
    ii: 1.. card(Rename_setstruct(pp))
  THEN
    vv:=Rename_setord(pp)(ii)
  END;




/************* Operations for individual sets *********************/



  Rename_CLR_SET_OBJ(pp) =
  PRE
    pp: Rename_settok
  THEN
    Rename_setstruct(pp):={}||
    Rename_setord(pp):=<>
  END;

  bb <-- Rename_UNION_SET_OBJ(ss,tt) =
  PRE
    ss: Rename_settok &
    tt: Rename_settok
  THEN
    CHOICE
      Rename_setstruct(ss) := Rename_setstruct(ss) \/ Rename_setstruct(tt) ||
      ANY xx WHERE
        xx : seq(VALUE) &
        xx:perm(Rename_setstruct(ss) \/ Rename_setstruct(tt))
      THEN      
        Rename_setord(ss) := xx
      END  ||
      bb:=TRUE
    OR
      bb:=FALSE
    END
  END;

  Rename_DIFF_SET_OBJ(ss,tt) =
  PRE
    ss: Rename_settok &
    tt: Rename_settok
  THEN
    Rename_setstruct(ss) := Rename_setstruct(ss) - Rename_setstruct(tt) ||
    ANY xx WHERE
        xx : seq(VALUE) &
      xx:perm(Rename_setstruct(ss) - Rename_setstruct(tt))
    THEN      
      Rename_setord(ss) := xx
    END
  END;

  Rename_INTER_SET_OBJ(ss,tt) =
  PRE
    ss: Rename_settok &
    tt: Rename_settok
  THEN
    Rename_setstruct(ss) := Rename_setstruct(ss) /\ Rename_setstruct(tt) ||
    ANY xx WHERE
        xx : seq(VALUE) &
      xx:perm(Rename_setstruct(ss) /\ Rename_setstruct(tt))
    THEN      
      Rename_setord(ss) := xx
    END
  END;

  bb <-- Rename_ENT_SET_OBJ(ss,vv) =
  PRE
    ss: Rename_settok &
    vv: VALUE
  THEN
    CHOICE
      Rename_setstruct(ss) := Rename_setstruct(ss) \/ {vv} ||
      ANY xx WHERE
        xx : seq(VALUE) &
        xx:perm(Rename_setstruct(ss) \/ {vv})
        THEN      
      Rename_setord(ss) := xx
      END ||
      bb:=TRUE
    OR
      bb:=FALSE
    END
  END;

  Rename_RMV_SET_OBJ(ss,vv) =
  PRE
    ss: Rename_settok &
    vv: VALUE
  THEN
    Rename_setstruct(ss) := Rename_setstruct(ss) - {vv} ||
    ANY xx WHERE
      xx : seq(VALUE) &
      xx:perm(Rename_setstruct(ss) -{vv})
    THEN      
      Rename_setord(ss) := xx
    END
  END;


  bb <-- Rename_CPY_SET_OBJ(pp,qq) =
  PRE
    pp:Rename_settok &
    qq:Rename_settok
  THEN
    CHOICE
      Rename_setstruct(qq):=Rename_setstruct(pp) ||
      Rename_setord(qq):=Rename_setord(pp) ||
      bb:=TRUE
    OR
      bb:=FALSE
    END
  END;



/**************** Query functions for individual sets **************/


  bb <-- Rename_EMP_SET_OBJ(pp) =
  PRE
    pp: Rename_settok
  THEN
    bb:=bool(Rename_setstruct(pp)={})
  END;


  nn <-- Rename_CRD_SET_OBJ(pp) =
  PRE
    pp: Rename_settok
  THEN
    nn:=card(Rename_setstruct(pp))
  END;

  bb <-- Rename_INCL_SET_OBJ(tt,ss) =
  PRE
    ss: Rename_settok &
    tt: Rename_settok
  THEN
    bb:=bool(Rename_setstruct(tt) <: Rename_setstruct(ss))
  END;

  bb <-- Rename_MBR_SET_OBJ(ss,vv) =
  PRE
    ss: Rename_settok &
    vv: VALUE
  THEN
    bb:=bool(vv: Rename_setstruct(ss))
  END;


/************** Persistent data facilities *************************/

/***********  save/restore host byte order ***********/

 Rename_SAV_SET_OBJ =
  BEGIN
    skip
  END;

  Rename_RST_SET_OBJ =
  ANY
    ssetn,sseto,ssetord
  WHERE
    ssetn <: Rename_SETOBJ &
    sseto: ssetn --> FIN(VALUE) &
    ssetord: ssetn --> seq(VALUE) &
    !pp.(pp:ssetn => ssetord(pp) : perm(sseto(pp)))
  THEN
    Rename_setstruct := sseto ||
    Rename_settok := ssetn ||
    Rename_setord := ssetord
  END;

/***********  save/restore network byte order ***********/

 Rename_SAVN_SET_OBJ =
  BEGIN
    skip
  END;

  Rename_RSTN_SET_OBJ =
  ANY
    ssetn,sseto,ssetord
  WHERE
    ssetn <: Rename_SETOBJ &
    sseto: ssetn --> FIN(VALUE) &
    ssetord: ssetn --> seq(VALUE) &
    !pp.(pp:ssetn => ssetord(pp) : perm(sseto(pp)))
  THEN
    Rename_setstruct := sseto ||
    Rename_settok := ssetn ||
    Rename_setord := ssetord
  END;

/********************** Browsing facilities ************************/


  nn,pp <-- Rename_FIRST_SET_OBJ =  
  IF not(Rename_settok = {}) THEN
     pp :: Rename_settok || 
     nn := card(Rename_settok) 
  ELSE
     pp :: Rename_SETOBJ ||
     nn := 0
  END;

  nn,qq <-- Rename_NEXT_SET_OBJ(mm,pp) = 
  PRE
    pp : Rename_settok &
    mm : NAT1
  THEN
    nn := mm-1 ||
    qq :: Rename_settok
  END


END

/*" \newpage "*/



