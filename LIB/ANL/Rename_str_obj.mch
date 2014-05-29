MACHINE

  Rename_str_obj(maxobj,maxmem)

CONSTRAINTS

  maxobj>0

SEES

  Bool_TYPE,String_TYPE

SETS

  Rename_STROBJ


PROPERTIES

  card(Rename_STROBJ) = maxobj
VARIABLES

  Rename_strtok, Rename_strstruct, Rename_strmem

INVARIANT

  Rename_strtok <: Rename_STROBJ &
  Rename_strstruct: Rename_strtok --> STRING &
  Rename_strmem : NAT
   

INITIALISATION

  Rename_strtok, Rename_strstruct, Rename_strmem := {},{}, 0 

OPERATIONS

/****************** General query functions *******************/

  bb <-- Rename_MEM_FUL_STR_OBJ =
  BEGIN
    bb:=bool(Rename_strmem=maxmem)
  END;

  bb <-- Rename_OBJ_FUL_STR_OBJ =
  BEGIN
    bb:=bool(Rename_strtok = Rename_STROBJ)
  END;

  bb <-- Rename_XST_STR_OBJ(pp) =
  PRE
    pp: Rename_STROBJ
  THEN
    bb:=bool(pp:Rename_strtok)
  END;

  pp <-- Rename_ANY_STR_OBJ =
  BEGIN
    pp :: Rename_STROBJ
  END;


/*************** Creating and deleting strings ******************/

  Rename_INI_STR_OBJ =
  BEGIN
    Rename_strtok, Rename_strstruct, Rename_strmem := {},{}, 0
  END;


  bb,pp <-- Rename_CRE_STR_OBJ =
  IF Rename_strtok /= Rename_STROBJ THEN
      ANY qq WHERE
        qq: Rename_STROBJ - Rename_strtok
      THEN
        Rename_strstruct(qq):=<> ||
        Rename_strtok := Rename_strtok \/ {qq} ||
        pp:=qq ||
        bb:= TRUE
      END
  ELSE
      bb:=FALSE || pp :: Rename_STROBJ
  END;


  bb,pp <-- Rename_NEW_STR_OBJ(nn) =
  PRE
     Rename_strtok /= Rename_STROBJ &
     nn : STRING 
     /* Rename_strmem + size(nn) <= maxmem */
  THEN 
     IF Rename_strmem + size(nn) <= maxmem THEN
       ANY qq WHERE
         qq: Rename_STROBJ - Rename_strtok
       THEN
         Rename_strstruct(qq):=nn ||
         Rename_strtok := Rename_strtok \/ {qq} ||
         Rename_strmem := Rename_strmem + size(nn) ||
         pp:=qq ||
         bb:=TRUE
       END
     ELSE
       bb := FALSE ||
       pp :: Rename_STROBJ
     END
 END;


  Rename_KIL_STR_OBJ(pp) =
  PRE
    pp: Rename_strtok &
    Rename_strmem >= size(Rename_strstruct(pp))
  THEN
    Rename_strstruct :=  {pp} <<| Rename_strstruct ||
    Rename_strtok := Rename_strtok - {pp} ||
    Rename_strmem := Rename_strmem - size(Rename_strstruct(pp))
  END;


/*********************** Query operations ***********************/


  vv <-- Rename_VAL_STR_OBJ(pp,ii) =
  PRE
    pp:Rename_strtok &
    ii:dom(Rename_strstruct(pp))
  THEN 
    vv:=Rename_strstruct(pp)(ii)
  END;

  bb <-- Rename_EMP_STR_OBJ(pp) =
  PRE
    pp: Rename_strtok
  THEN
    bb:=bool(Rename_strstruct(pp)=<>)
  END;

  bb <-- Rename_XST_IDX_STR_OBJ(pp,ii) =
  PRE
    pp: Rename_strtok &
    ii: 1..maxmem
  THEN
    bb:=bool(ii:1..size(Rename_strstruct(pp)))
  END;

  nn <-- Rename_LEN_STR_OBJ(pp)=
  PRE
    pp: Rename_strtok
  THEN
    nn:=size(Rename_strstruct(pp))
  END;

  bb <-- Rename_SMR_STR_OBJ(ss,tt) =
  PRE
     tt : Rename_strtok &
     ss : Rename_strtok
  THEN
    bb :: BOOL 
  END;

  bb <-- Rename_EQL_STR_OBJ(ss,tt) =
  PRE
     tt : Rename_strtok &
     ss : Rename_strtok
  THEN
     bb := bool(Rename_strstruct(tt) = Rename_strstruct(ss))
  END;

  bb <-- Rename_SUB_STR_OBJ(ss,tt) =
  PRE
     tt : Rename_strtok &
     ss : Rename_strtok
  THEN
     bb := bool( Rename_strstruct(ss) <: Rename_strstruct(tt))
  END;

  bb <-- Rename_EQL_LIT_STR_OBJ(tt,nn) =
  PRE
     tt : Rename_strtok &
     nn : STRING
  THEN
     bb := bool(Rename_strstruct(tt) = nn)
  END;


  ss <-- Rename_XTR_STR_OBJ(pp) =
  PRE
    pp : Rename_strtok 
  THEN
    ss := Rename_strstruct(pp) 
  END;

/**************** String operations **************************/

  Rename_CLR_STR_OBJ(pp) =
  PRE
    pp: Rename_strtok &
    Rename_strmem >= size(Rename_strstruct(pp))
  THEN
    Rename_strstruct(pp) := <> ||
    Rename_strmem := (
     Rename_strmem - size(Rename_strstruct(pp))
    )
  END;


  bb <-- Rename_PSH_STR_OBJ(pp,vv) =
  PRE
    pp:Rename_strtok &
    vv: CHAR 
    /* Rename_strmem<maxmem */
  THEN
    IF Rename_strmem<maxmem THEN
      Rename_strstruct(pp):=Rename_strstruct(pp) <- vv ||
      Rename_strmem:=Rename_strmem+1 ||
      bb:=TRUE
    ELSE
      bb:=FALSE
    END
  END;

  Rename_KEP_STR_OBJ(pp,ii) =
  PRE
    pp:Rename_strtok &
    ii:0..size(Rename_strstruct(pp)) &
    Rename_strmem >= size(Rename_strstruct(pp))+ii
  THEN
    Rename_strstruct(pp):=Rename_strstruct(pp) /|\ ii ||
    Rename_strmem:= (
     Rename_strmem-size(Rename_strstruct(pp))+ii
    )
  END;

  Rename_CUT_STR_OBJ(pp,ii) =
  PRE
    pp:Rename_strtok &
    ii:0..size(Rename_strstruct(pp)) &
    ii <= Rename_strmem
  THEN
    Rename_strstruct(pp):=Rename_strstruct(pp) \|/ ii ||
    Rename_strmem:=Rename_strmem-ii
  END;

  Rename_REV_STR_OBJ(pp) =
  PRE
    pp:Rename_strtok
  THEN
    Rename_strstruct(pp):=rev(Rename_strstruct(pp))
  END;

  Rename_SWP_STR_OBJ(pp,ii,jj) =
  PRE
    pp:Rename_strtok &
    ii:dom(Rename_strstruct(pp)) &
    jj:dom(Rename_strstruct(pp))
  THEN
    Rename_strstruct(pp):= (
     Rename_strstruct(pp) <+ (
        {ii |-> Rename_strstruct(pp)(jj), jj |-> Rename_strstruct(pp)(ii)}
        )
     )

  END;

  Rename_POP_STR_OBJ(pp) =
  PRE
    pp:Rename_strtok &
    size(Rename_strstruct(pp))/=0
  THEN
    Rename_strstruct(pp):= front(Rename_strstruct(pp)) ||
    Rename_strmem:=Rename_strmem-1
  END;

  Rename_STO_STR_OBJ(pp,ii,vv) =
  PRE
    pp:Rename_strtok &
    vv:CHAR &
    ii:dom(Rename_strstruct(pp))
  THEN 
    Rename_strstruct(pp)(ii):=vv
  END;

  bb <-- Rename_APP_STR_OBJ(pp,qq) =
  PRE
    pp:Rename_strtok &
    qq:Rename_strtok 
    /* Rename_strmem+size(Rename_strstruct(qq))<=maxmem */
  THEN
    IF
      Rename_strmem+size(Rename_strstruct(qq))<=maxmem
   THEN
      Rename_strstruct(pp):= ( 
       Rename_strstruct(pp)^Rename_strstruct(qq) 
      ) ||
      Rename_strmem:= (
       Rename_strmem+size(Rename_strstruct(qq)) 
      )||
      bb:=TRUE
    ELSE
      bb:=FALSE
    END
  END;

  bb <-- Rename_CPY_STR_OBJ(pp,qq) =
  PRE
    pp:Rename_strtok &
    qq:Rename_strtok 
    /* Rename_strmem- (
     size(Rename_strstruct(qq))+size(Rename_strstruct(pp)) 
     ) <=  maxmem */
   
  THEN
    IF Rename_strmem- ( 
        size(Rename_strstruct(qq))+size(Rename_strstruct(pp))
         ) <=  maxmem 
   THEN
      Rename_strstruct(qq):=Rename_strstruct(pp) ||
      Rename_strmem:= ( 
        Rename_strmem- (
           size(Rename_strstruct(qq))+size(Rename_strstruct(pp))
        )
      ) ||
      bb:=TRUE
    ELSE
      bb:=FALSE
    END
  END;


  bb <-- Rename_OVR_STR_OBJ(pp,qq) =
  PRE
    pp:Rename_strtok &
    qq:Rename_strtok 
    /* Rename_strmem + (
    size(Rename_strstruct(qq))-size(Rename_strstruct(pp))
    ) <= maxmem */
  THEN
    IF
      Rename_strmem+ (
        size(Rename_strstruct(qq))-size(Rename_strstruct(pp))
      ) <=  maxmem 
    THEN
      Rename_strstruct(pp):= (
        Rename_strstruct(pp) <+ Rename_strstruct(qq)
      ) ||
      Rename_strmem:= (
         Rename_strmem+ (
            max({0,(size(Rename_strstruct(qq))-size(Rename_strstruct(pp)))}) 
         )
      )||
      bb:=TRUE
    ELSE
      bb:=FALSE
    END
  END;

/******************** Persistent Data facilities ***********************/

/***********  save/restore host byte order ***********/
 
  Rename_SAV_STR_OBJ =
  BEGIN
    skip
  END;

  Rename_RST_STR_OBJ =
  ANY
    sstrn,sstro,stotstr
  WHERE
    sstrn <: Rename_STROBJ &
    sstro: sstrn --> STRING &
    stotstr:  NAT 
  THEN
    Rename_strstruct := sstro ||
    Rename_strtok := sstrn ||
    Rename_strmem := stotstr
  END;

/***********  save/restore network byte order ***********/

  Rename_SAVN_STR_OBJ =
  BEGIN
    skip
  END;

  Rename_RSTN_STR_OBJ =
  ANY
    sstrn,sstro,stotstr
  WHERE
    sstrn <: Rename_STROBJ &
    sstro: sstrn --> STRING &
    stotstr:  NAT 
  THEN
    Rename_strstruct := sstro ||
    Rename_strtok := sstrn ||
    Rename_strmem := stotstr
  END;


/**************************** Browsing ********************************/

  nn,pp <-- Rename_FIRST_STR_OBJ =  
  IF not(Rename_strtok = {}) THEN
     pp :: Rename_strtok || 
     nn := card(Rename_strtok) 
  ELSE
     pp :: Rename_STROBJ ||
     nn := 0
  END;

  nn,qq <-- Rename_NEXT_STR_OBJ(mm,pp) = 
  PRE
    pp : Rename_strtok &
    mm : NAT1
  THEN
    nn := mm-1 ||
    qq :: Rename_strtok
  END



END

