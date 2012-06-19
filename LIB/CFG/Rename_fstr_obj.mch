MACHINE      Rename_fstr_obj(maxobj,maxmem)

CONSTRAINTS  maxobj>0

SEES         Bool_TYPE, Rename_fstr_ctx

VARIABLES    Rename_fstrtok, Rename_fstrstruct, Rename_fstrmem

INVARIANT

  Rename_fstrtok <: Rename_FSTROBJ &
  Rename_fstrstruct: Rename_fstrtok --> seq(0..255) &
  Rename_fstrmem:  NAT

INITIALISATION

  Rename_fstrtok, Rename_fstrstruct, Rename_fstrmem := {},{}, 0

OPERATIONS

/****************** General query functions *******************/

  bb <-- Rename_MEM_FUL_FSTR_OBJ =
  BEGIN
    bb:=bool(Rename_fstrmem=maxmem)
  END;

  bb <-- Rename_OBJ_FUL_FSTR_OBJ =
  BEGIN
    bb:=bool(card(Rename_fstrtok) = maxobj)
  END;

  bb <-- Rename_XST_FSTR_OBJ(pp) =
  PRE
    pp: Rename_FSTROBJ
  THEN
    bb:=bool(pp:Rename_fstrtok)
  END;

  pp <-- Rename_ANY_FSTR_OBJ =
  BEGIN
    pp :: Rename_FSTROBJ
  END;


/*************** Creating and deleting strings ******************/

  Rename_INI_FSTR_OBJ =
  BEGIN
    Rename_fstrtok, Rename_fstrstruct, Rename_fstrmem := {},{}, 0
  END;


  bb,pp <-- Rename_CRE_FSTR_OBJ =
  IF card(Rename_fstrtok) < maxobj THEN
      ANY qq WHERE
        qq: Rename_FSTROBJ - Rename_fstrtok
      THEN
        Rename_fstrstruct(qq):=<> ||
        Rename_fstrtok := Rename_fstrtok \/ {qq} ||
        pp:=qq ||
        bb:= TRUE
      END
  ELSE
      bb:=FALSE
  END;


  bb,pp <-- Rename_NEW_FSTR_OBJ(nn) =
  PRE
     card(Rename_fstrtok) < maxobj &
     nn : seq(0..255) 
     /* Rename_fstrmem + size(nn) <= maxmem */
  THEN 
     IF Rename_fstrmem + size(nn) <= maxmem THEN
       ANY qq WHERE
         qq: Rename_FSTROBJ - Rename_fstrtok
       THEN
         Rename_fstrstruct(qq):=nn ||
         Rename_fstrtok := Rename_fstrtok \/ {qq} ||
         Rename_fstrmem := Rename_fstrmem + size(nn) ||
         pp:=qq ||
         bb:=TRUE
       END
     ELSE
       bb := FALSE ||
       pp :: Rename_FSTROBJ
     END
 END;


  Rename_KIL_FSTR_OBJ(pp) =
  PRE
    pp: Rename_fstrtok
  THEN
    Rename_fstrstruct :=  {pp} <<| Rename_fstrstruct ||
    Rename_fstrtok := Rename_fstrtok - {pp} ||
    Rename_fstrmem := Rename_fstrmem - size(Rename_fstrstruct(pp))
  END;


/*********************** Query operations ***********************/


  vv <-- Rename_VAL_FSTR_OBJ(pp,ii) =
  PRE
    pp:Rename_fstrtok &
    ii:1..size(Rename_fstrstruct(pp))
  THEN 
    vv:=Rename_fstrstruct(pp)(ii)
  END;

  bb <-- Rename_EMP_FSTR_OBJ(pp) =
  PRE
    pp: Rename_fstrtok
  THEN
    bb:=bool(Rename_fstrstruct(pp)=<>)
  END;

  bb <-- Rename_XST_IDX_FSTR_OBJ(pp,ii) =
  PRE
    pp: Rename_fstrtok &
    ii: 1..maxmem
  THEN
    bb:=bool(ii:1..size(Rename_fstrstruct(pp)))
  END;

  nn <-- Rename_LEN_FSTR_OBJ(pp)=
  PRE
    pp: Rename_fstrtok
  THEN
    nn:=size(Rename_fstrstruct(pp))
  END;

  bb <-- Rename_SMR_FSTR_OBJ(ss,tt) =
  PRE
     tt : Rename_fstrtok &
     ss : Rename_fstrtok
  THEN
    bb :: BOOL 
  END;

  bb <-- Rename_EQL_FSTR_OBJ(ss,tt) =
  PRE
     tt : Rename_fstrtok &
     ss : Rename_fstrtok
  THEN
     bb := bool(Rename_fstrstruct(tt) = Rename_fstrstruct(ss))
  END;

  bb <-- Rename_EQL_LIT_FSTR_OBJ(tt,nn) =
  PRE
     tt : Rename_fstrtok &
     nn : seq(0..255)
  THEN
     bb := bool(Rename_fstrstruct(tt) = nn)
  END;


  ss <-- Rename_XTR_FSTR_OBJ(pp) =
  PRE
    pp : Rename_fstrtok
  THEN
    ss := Rename_fstrstruct(pp)
  END;

/**************** String operations **************************/

  Rename_CLR_FSTR_OBJ(pp) =
  PRE
    pp: Rename_fstrtok
  THEN
    Rename_fstrstruct(pp) := <> ||
    Rename_fstrmem := (
     Rename_fstrmem - size(Rename_fstrstruct(pp))
    )
  END;


  bb <-- Rename_PSH_FSTR_OBJ(pp,vv) =
  PRE
    pp:Rename_fstrtok &
    vv: 0..255 
    /* Rename_fstrmem<maxmem */
  THEN
    IF Rename_fstrmem<maxmem THEN
      Rename_fstrstruct(pp):=Rename_fstrstruct(pp) <- vv ||
      Rename_fstrmem:=Rename_fstrmem+1 ||
      bb:=TRUE
    ELSE
      bb:=FALSE
    END
  END;

  Rename_KEP_FSTR_OBJ(pp,ii) =
  PRE
    pp:Rename_fstrtok &
    ii:0..size(Rename_fstrstruct(pp))
  THEN
    Rename_fstrstruct(pp):=Rename_fstrstruct(pp) /|\ ii ||
    Rename_fstrmem:= (
     Rename_fstrmem-size(Rename_fstrstruct(pp))+ii
    )
  END;

  Rename_CUT_FSTR_OBJ(pp,ii) =
  PRE
    pp:Rename_fstrtok &
    ii:0..size(Rename_fstrstruct(pp))
  THEN
    Rename_fstrstruct(pp):=Rename_fstrstruct(pp) \|/ ii ||
    Rename_fstrmem:=Rename_fstrmem-ii
  END;

  Rename_REV_FSTR_OBJ(pp) =
  PRE
    pp:Rename_fstrtok
  THEN
    Rename_fstrstruct(pp):=rev(Rename_fstrstruct(pp))
  END;

  Rename_SWP_FSTR_OBJ(pp,ii,jj) =
  PRE
    pp:Rename_fstrtok &
    ii:0..size(Rename_fstrstruct(pp)) &
    jj:0..size(Rename_fstrstruct(pp))
  THEN
    Rename_fstrstruct(pp):= (
     Rename_fstrstruct(pp) <+ (
        {ii |-> Rename_fstrstruct(pp)(jj), jj |-> Rename_fstrstruct(pp)(ii)}
        )
     )

  END;

  Rename_POP_FSTR_OBJ(pp) =
  PRE
    pp:Rename_fstrtok &
    size(Rename_fstrstruct(pp))/=0
  THEN
    Rename_fstrstruct(pp):= front(Rename_fstrstruct(pp)) ||
    Rename_fstrmem:=Rename_fstrmem-1
  END;

  Rename_STO_FSTR_OBJ(pp,ii,vv) =
  PRE
    pp:Rename_fstrtok &
    vv:0..255 &
    ii:1..size(Rename_fstrstruct(pp))
  THEN 
    Rename_fstrstruct(pp)(ii):=vv
  END;

  bb <-- Rename_APP_FSTR_OBJ(pp,qq) =
  PRE
    pp:Rename_fstrtok &
    qq:Rename_fstrtok 
    /* Rename_fstrmem+size(Rename_fstrstruct(qq))<=maxmem */
  THEN
    IF
      Rename_fstrmem+size(Rename_fstrstruct(qq))<=maxmem
   THEN
      Rename_fstrstruct(pp):= ( 
       Rename_fstrstruct(pp)^Rename_fstrstruct(qq) 
      ) ||
      Rename_fstrmem:= (
       Rename_fstrmem+size(Rename_fstrstruct(qq)) 
      )||
      bb:=TRUE
    ELSE
      bb:=FALSE
    END
  END;

  bb <-- Rename_CPY_FSTR_OBJ(pp,qq) =
  PRE
    pp:Rename_fstrtok &
    qq:Rename_fstrtok 
    /* Rename_fstrmem- (
     size(Rename_fstrstruct(qq))+size(Rename_fstrstruct(pp)) 
     ) <=  maxmem */
   
  THEN
    IF Rename_fstrmem- ( 
        size(Rename_fstrstruct(qq))+size(Rename_fstrstruct(pp))
         ) <=  maxmem 
   THEN
      Rename_fstrstruct(qq):=Rename_fstrstruct(pp) ||
      Rename_fstrmem:= ( 
        Rename_fstrmem- (
           size(Rename_fstrstruct(qq))+size(Rename_fstrstruct(pp))
        )
      ) ||
      bb:=TRUE
    ELSE
      bb:=FALSE
    END
  END;


  bb <-- Rename_OVR_FSTR_OBJ(pp,qq) =
  PRE
    pp:Rename_fstrtok &
    qq:Rename_fstrtok 
    /* Rename_fstrmem + (
    size(Rename_fstrstruct(qq))-size(Rename_fstrstruct(pp))
    ) <= maxmem */
  THEN
    IF
      Rename_fstrmem+ (
        size(Rename_fstrstruct(qq))-size(Rename_fstrstruct(pp))
      ) <=  maxmem 
    THEN
      Rename_fstrstruct(pp):= (
        Rename_fstrstruct(pp) <+ Rename_fstrstruct(qq)
      ) ||
      Rename_fstrmem:= (
         Rename_fstrmem+ (
            max({0,(size(Rename_fstrstruct(qq))-size(Rename_fstrstruct(pp)))}) 
         )
      )||
      bb:=TRUE
    ELSE
      bb:=FALSE
    END
  END;

 /******************** Persistent Data facilities ***********************/

/***********  save/restore host byte order ***********/

  Rename_SAV_FSTR_OBJ =
  BEGIN
    skip
  END;

  Rename_RST_FSTR_OBJ =
  ANY
    sstrn,sstro,stotstr
  WHERE
    sstrn <: Rename_FSTROBJ &
    sstro: sstrn --> seq(0..255) &
    stotstr:  NAT 
  THEN
    Rename_fstrstruct := sstro ||
    Rename_fstrtok := sstrn ||
    Rename_fstrmem := stotstr
  END;

  Rename_SAVN_FSTR_OBJ =
  BEGIN
    skip
  END;

/***********  save/restore network byte order ***********/

  Rename_RSTN_FSTR_OBJ =
  ANY
    sstrn,sstro,stotstr
  WHERE
    sstrn <: Rename_FSTROBJ &
    sstro: sstrn --> seq(0..255) &
    stotstr:  NAT 
  THEN
    Rename_fstrstruct := sstro ||
    Rename_fstrtok := sstrn ||
    Rename_fstrmem := stotstr
  END;


/**************************** Browsing ********************************/

  nn,pp <-- Rename_FIRST_FSTR_OBJ =  
  IF not(Rename_fstrtok = {}) THEN
     pp :: Rename_fstrtok || 
     nn := card(Rename_fstrtok) 
  ELSE
     pp :: Rename_FSTROBJ ||
     nn := 0
  END;

  nn,qq <-- Rename_NEXT_FSTR_OBJ(mm,pp) = 
  PRE
    pp : Rename_fstrtok &
    mm : NAT1
  THEN
    nn := mm-1 ||
    qq :: Rename_fstrtok
  END



END

