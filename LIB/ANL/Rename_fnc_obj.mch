MACHINE

  Rename_fnc_obj(VALUE,maxfld,maxobj)


CONSTRAINTS

  maxobj>0

SEES

  file_dump,Bool_TYPE

SETS

  Rename_FNCOBJ

PROPERTIES

  card(Rename_FNCOBJ) = maxobj

VARIABLES

  Rename_fnctok, Rename_fncstruct,Rename_locate

INVARIANT

  Rename_fnctok <: Rename_FNCOBJ &
  Rename_fncstruct: Rename_fnctok --> (1..maxfld +-> VALUE) &
  Rename_locate : 1..card(Rename_fnctok) >->> Rename_fnctok

INITIALISATION

  Rename_fnctok, Rename_fncstruct, Rename_locate:= {},{},{}

OPERATIONS

/***************** General query functions ********************/

  bb <-- Rename_FUL_FNC_OBJ =
  BEGIN
    bb:=bool(Rename_fnctok = Rename_FNCOBJ)
  END;

  bb <-- Rename_TST_FLD_FNC_OBJ(ii) =
  PRE
    ii: NAT
  THEN
    bb:=bool(ii: 1..maxfld)
  END;

  vv <-- Rename_ANY_FNC_OBJ =
  BEGIN
    vv::Rename_FNCOBJ
  END;

/*********** Creating, killing and testing for existence ********/

  bb,pp <-- Rename_CRE_FNC_OBJ =
  IF Rename_fnctok /= Rename_FNCOBJ THEN 
    ANY qq,ll WHERE
      qq: Rename_FNCOBJ - Rename_fnctok &
      ll : 1..card(Rename_fnctok)+1 >->> (Rename_fnctok \/ {qq})
    THEN
      Rename_fncstruct(qq):={} ||
      Rename_fnctok := Rename_fnctok \/ {qq} ||
      Rename_locate := ll ||
      pp:=qq ||
      bb:= TRUE
    END
  ELSE
    bb:= FALSE || pp :: Rename_FNCOBJ
  END;

  Rename_KIL_FNC_OBJ(ff) =
  PRE
    ff: Rename_fnctok
  THEN
    Rename_fncstruct := {ff} <<| Rename_fncstruct ||
    Rename_fnctok := Rename_fnctok - {ff} ||
    Rename_locate :: (
     1..card(Rename_fnctok)-1 >->> (Rename_fnctok-{ff})
    )
  END;

  Rename_INI_FNC_OBJ =
  BEGIN
    Rename_fncstruct := {} ||
    Rename_fnctok := {} ||
    Rename_locate := {}
  END;

  bb <-- Rename_XST_FNC_OBJ(pp) =
  PRE
    pp: Rename_FNCOBJ
  THEN
    bb:=bool(pp:Rename_fnctok)
  END;

/********** Query functions for individual functions **************/

  
  bb <-- Rename_DEF_FNC_OBJ(ff,ii) =
  PRE
    ff: Rename_fnctok &
    ii: 1..maxfld
  THEN
    bb := bool(ii: dom(Rename_fncstruct(ff)))
  END;

  vv <-- Rename_VAL_FNC_OBJ(ff,ii) =
  PRE
    ff: Rename_fnctok &
    ii: dom(Rename_fncstruct(ff))
  THEN
    vv := Rename_fncstruct(ff)(ii)
  END;

/****** Operations for manipulating individual functions *********/

  Rename_STO_FNC_OBJ(ff,ii,vv) =
  PRE
    ff: Rename_fnctok &
    ii: 1..maxfld &
    vv: VALUE
  THEN
    Rename_fncstruct(ff)(ii) := vv
  END;

  Rename_RMV_FNC_OBJ(ff,ii) =
  PRE
    ff: Rename_fnctok &
    ii: 1..maxfld
  THEN
    Rename_fncstruct(ff) := {ii} <<| Rename_fncstruct(ff)
  END;

/************* Persistent data facilities ************************/  

/***********  save/restore host byte order ***********/

  Rename_SAV_FNC_OBJ =
  BEGIN
    skip
  END;

  Rename_RST_FNC_OBJ =
  ANY
    sfncn,sfnco,loc
  WHERE
    sfncn <: Rename_FNCOBJ &
    sfnco: sfncn --> (1..maxfld +-> VALUE) &
    loc : 1..card(sfncn) >->> sfncn
  THEN
    Rename_fncstruct := sfnco ||
    Rename_fnctok := sfncn ||
    Rename_locate := loc
  END;

/***********  save/restore network byte order ***********/

  Rename_SAVN_FNC_OBJ =
  BEGIN
    skip
  END;

  Rename_RSTN_FNC_OBJ =
  ANY
    sfncn,sfnco,loc
  WHERE
    sfncn <: Rename_FNCOBJ &
    sfnco: sfncn --> (1..maxfld +-> VALUE) &
    loc : 1..card(sfncn) >->> sfncn
  THEN
    Rename_fncstruct := sfnco ||
    Rename_fnctok := sfncn ||
    Rename_locate := loc
  END;

/********************* Browsing facilities ************************/


  nn,pp <-- Rename_FIRST_FNC_OBJ =   
  IF not(Rename_fnctok = {}) THEN
     pp := Rename_locate(card(Rename_fnctok)) || 
     nn := card(Rename_fnctok) 
  ELSE
     pp :: Rename_FNCOBJ ||
     nn := 0
  END;

  nn,qq <-- Rename_NEXT_FNC_OBJ(mm,pp) =  
  PRE
    pp : Rename_fnctok &
    mm : 1..card(Rename_fnctok)
  THEN
    nn:= mm-1 ||
    IF mm /=1 THEN
       qq := Rename_locate(mm-1) 
    ELSE
       qq :: Rename_fnctok
    END
  END
   
END


