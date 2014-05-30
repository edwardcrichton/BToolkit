MACHINE      Rename_ffnc_obj(VALUE,rcdsiz,maxobj)

CONSTRAINTS  maxobj>0

SEES         file_dump, Bool_TYPE, String_TYPE, Rename_ffnc_ctx

CONSTANTS    Rename_UnPack, Rename_CHARperWORD

PROPERTIES

  Rename_UnPack : (NAT +-> VALUE) --> STRING &

  Rename_CHARperWORD = 4 

VARIABLES    Rename_fnctok, Rename_fncstruct,Rename_locate

INVARIANT

  Rename_fnctok <: Rename_FNCOBJ &
  Rename_fncstruct: Rename_fnctok --> (1..rcdsiz +-> VALUE) &
  Rename_locate : 1..card(Rename_fnctok) >->> Rename_fnctok

INITIALISATION

  Rename_fnctok, Rename_fncstruct, Rename_locate:= {},{},{} 

OPERATIONS

/***************** General query functions ********************/

  mm,nn <-- Rename_STS_FNC_OBJ =
  BEGIN
    mm,nn:=card(Rename_fnctok),maxobj
  END;

  bb <-- Rename_FUL_FNC_OBJ =
  BEGIN
    bb:=bool(card(Rename_fnctok) = maxobj)
  END;

  bb <-- Rename_TST_FLD_FNC_OBJ(ii) =
  PRE
    ii: NAT
  THEN
    bb:=bool(ii: 1..rcdsiz)
  END;

  vv <-- Rename_ANY_FNC_OBJ =
  BEGIN
    vv::Rename_FNCOBJ
  END;

/*********** Creating, killing and testing for existence ********/

  bb,pp <-- Rename_CRE_FNC_OBJ =
  IF card(Rename_fnctok) < maxobj THEN 
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
    ii: 1..rcdsiz
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
    ii: 1..rcdsiz &
    vv: VALUE
  THEN
    Rename_fncstruct(ff)(ii) := vv
  END;

  Rename_RMV_FNC_OBJ(ff,ii) =
  PRE
    ff: Rename_fnctok &
    ii: 1..rcdsiz 
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
    sfncn,sfnco,sfncl
  WHERE
    sfncn <: Rename_FNCOBJ &
    sfnco: sfncn --> (1..rcdsiz +-> VALUE)  &
    sfncl : 1..card(sfncn) >->> sfncn
  THEN
    Rename_fncstruct := sfnco ||
    Rename_fnctok := sfncn ||
    Rename_locate := sfncl
  END;

/***********  save/restore network byte order ***********/

  Rename_SAVN_FNC_OBJ =
  BEGIN
    skip
  END;

  Rename_RSTN_FNC_OBJ =
  ANY
    sfncn,sfnco,sfncl
  WHERE
    sfncn <: Rename_FNCOBJ &
    sfnco: sfncn --> (1..rcdsiz +-> VALUE)  &
    sfncl : 1..card(sfncn) >->> sfncn
  THEN
    Rename_fncstruct := sfnco ||
    Rename_fnctok := sfncn ||
    Rename_locate := sfncl
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
  END;
   

/********************* Additional FFNC facilities ************************/


 Rename_MOV_FFNC_OBJ(ff,gg,ii,jj,ll) =
    PRE
      ff: Rename_fnctok &
      gg: Rename_fnctok &
      ii: 1..rcdsiz &
      jj: 1..rcdsiz &
      ll: 1..rcdsiz &
      ii..(ii+ll-1) /\ jj..(jj+ll-1) = {} &
      ii..(ii+ll-1) <: dom(Rename_fncstruct(ff)) &
      jj..(jj+ll-1) <: 1..rcdsiz 
    THEN
       ANY newsegment WHERE
          newsegment : jj..(jj+ll-1) --> VALUE &
          newsegment = %xx.(xx:jj..(jj+ll-1)|Rename_fncstruct(ff)(ii+(xx-jj)))
       THEN
         Rename_fncstruct(gg) := Rename_fncstruct(gg) <+ newsegment
       END
    END;

  Rename_OVR_FFNC_OBJ(ff,ii,ll,aa) =
    PRE
      ff: Rename_fnctok &
      ii: 1..rcdsiz &
      ll: 1..rcdsiz &
      ii..(ii+ll-1) <: 1..rcdsiz &
      ll * Rename_CHARperWORD > size(aa) &
      aa: STRING 
    THEN
       ANY newsegment WHERE
          newsegment : (ii..(ii+ll-1)) --> VALUE &
          Rename_UnPack(newsegment) = aa
       THEN
         Rename_fncstruct(ff) := Rename_fncstruct(ff) <+ newsegment
       END
    END;

    Rename_OVR_LIT_FFNC_OBJ(ff,ii,ll,aa) =
    PRE
      ff: Rename_fnctok &
      ii: 1..rcdsiz &
      ll: 1..rcdsiz &
      ii..(ii+ll-1) <: 1..rcdsiz &
      ll * Rename_CHARperWORD > size(aa) &
      aa: STRING &
      size(aa) < 1000 
    THEN
       ANY newsegment WHERE
          newsegment : (ii..(ii+ll-1)) --> VALUE &
          Rename_UnPack(newsegment) = aa
       THEN
         Rename_fncstruct(ff) := Rename_fncstruct(ff) <+ newsegment
       END
    END;

  vv <-- Rename_XTR_FFNC_OBJ(ff,ii,ll) =
    PRE
      ff: Rename_fnctok &
      ii: 1..rcdsiz  &
      ll: 1..rcdsiz  &
      ii..(ii+ll-1) <: dom(Rename_fncstruct(ff)) 
    THEN
      ANY str WHERE
          str = Rename_UnPack( (ii..(ii+ll-1))<<|Rename_fncstruct(ff) ) 
      THEN
          vv := str 
      END
    END;

 
  bb <-- Rename_EQL_FFNC_OBJ(ff,ii,ll,vv) =
    PRE
      ff: Rename_fnctok &
      ii: 1..rcdsiz &
      ll: 1..rcdsiz &
      ii..(ii+ll-1) <: dom(Rename_fncstruct(ff)) &
      vv: STRING 
    THEN
         bb := bool(
        Rename_UnPack( (ii..(ii+ll-1))<<|Rename_fncstruct(ff) ) = vv
      )
    END


END
