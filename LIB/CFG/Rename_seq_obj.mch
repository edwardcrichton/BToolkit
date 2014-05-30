MACHINE      Rename_seq_obj(VALUE,maxobj,maxmem)

CONSTRAINTS  maxobj>0

SEES         Rename_seq_ctx, Bool_TYPE

VARIABLES

  Rename_seqtok, Rename_seqstruct, Rename_seqmem

INVARIANT

  Rename_seqtok <: Rename_SEQOBJ &
  Rename_seqstruct: Rename_seqtok --> seq(VALUE) &
  Rename_seqmem = SIGMA tt.(tt : Rename_seqtok| size(Rename_seqstruct(tt))) &
  Rename_seqmem:  NAT &  
  Rename_seqmem <= maxmem

INITIALISATION

  Rename_seqtok, Rename_seqstruct, Rename_seqmem := {},{}, 0

OPERATIONS

/******************  General query functions *********************/

  mm,nn,pp,qq <-- Rename_STS_SEQ_OBJ =
  BEGIN
    mm,nn,pp,qq:=Rename_seqmem,maxmem,card(Rename_seqtok),maxobj
  END;

  bb <-- Rename_MEM_FUL_SEQ_OBJ =
  BEGIN
    bb:=bool(Rename_seqmem=maxmem)
  END;

  bb <-- Rename_OBJ_FUL_SEQ_OBJ =
  BEGIN
    bb:=bool(card(Rename_seqtok) =  maxobj)
  END;

  bb <-- Rename_XST_SEQ_OBJ(pp) =
  PRE
    pp: Rename_SEQOBJ
  THEN
    bb:=bool(pp:Rename_seqtok)
  END;


/******************  Creating and deleting sequences **************/


  Rename_INI_SEQ_OBJ =
  BEGIN
    Rename_seqtok, Rename_seqstruct, Rename_seqmem := {},{}, 0
  END;

  pp <-- Rename_ANY_SEQ_OBJ =
  BEGIN
    pp :: Rename_SEQOBJ
  END;


  bb,pp <-- Rename_CRE_SEQ_OBJ =
  IF card(Rename_seqtok) < maxobj THEN
      ANY qq WHERE
        qq: Rename_SEQOBJ - Rename_seqtok
      THEN
        Rename_seqstruct(qq):=<> ||
        Rename_seqtok := Rename_seqtok \/ {qq} ||
        pp:=qq ||
        bb := TRUE
      END
  ELSE
      bb:= FALSE || pp :: Rename_SEQOBJ
  END;

  Rename_KIL_SEQ_OBJ(pp) =
  PRE
    pp: Rename_seqtok &
    Rename_seqmem >= size(Rename_seqstruct(pp))
  THEN
    Rename_seqstruct :=  {pp} <<| Rename_seqstruct ||
    Rename_seqtok := Rename_seqtok - {pp} ||
    Rename_seqmem := Rename_seqmem - size(Rename_seqstruct(pp))
  END;


/******************  Query functions for individual sequences **********/


  vv <-- Rename_VAL_SEQ_OBJ(pp,ii) =
  PRE
    pp:Rename_seqtok &
    ii:dom(Rename_seqstruct(pp))
  THEN 
    vv:=Rename_seqstruct(pp)(ii)
  END;

  bb <-- Rename_XST_IDX_SEQ_OBJ(pp,ii) =
  PRE
    pp: Rename_seqtok &
    ii: 1..maxmem
  THEN
    bb:=bool(ii:1..size(Rename_seqstruct(pp)))
  END;

  nn <-- Rename_LEN_SEQ_OBJ(pp)=
  PRE
    pp: Rename_seqtok
  THEN
    nn:=size(Rename_seqstruct(pp))
  END;

  bb <-- Rename_EMP_SEQ_OBJ(pp) =
  PRE
    pp: Rename_seqtok
  THEN
    bb:=bool(Rename_seqstruct(pp)=<>)
  END;

  bb <-- Rename_EQL_SEQ_OBJ(ss,tt) =
  PRE
     tt : Rename_seqtok &
     ss : Rename_seqtok
  THEN
     bb := bool(Rename_seqstruct(tt) = Rename_seqstruct(ss))
  END;

  bb,ii <-- Rename_MBR_SEQ_OBJ(tt,vv) =
  PRE
     tt : Rename_seqtok &
     vv : VALUE
  THEN
     IF vv : ran(Rename_seqstruct(tt)) THEN
        ANY kk WHERE
           kk: NAT & (Rename_seqstruct(tt))(kk) = vv
        THEN
            bb := TRUE || ii := kk  
        END 
     ELSE
        bb := FALSE || ii :: NAT
     END 
  END;


/******************   Sequence Operations ***********************/


  bb <-- Rename_PSH_SEQ_OBJ(pp,vv) =
  PRE
    pp:Rename_seqtok &
    vv: VALUE
    /* Rename_seqmem < maxmem */
  THEN
    IF Rename_seqmem<maxmem THEN
      Rename_seqstruct(pp):=Rename_seqstruct(pp) <- vv ||
      Rename_seqmem:=Rename_seqmem+1 ||
      bb := TRUE
    ELSE
      bb := FALSE
    END
  END;


  Rename_CLR_SEQ_OBJ(pp) =
  PRE
    pp: Rename_seqtok  /* &
    Rename_seqmem >= size(Rename_seqstruct(pp)) */
  THEN
    Rename_seqstruct(pp) := <> ||
    Rename_seqmem := Rename_seqmem - size(Rename_seqstruct(pp))
  END;


  Rename_KEP_SEQ_OBJ(pp,ii) =
  PRE
    pp:Rename_seqtok &
    ii:0..size(Rename_seqstruct(pp)) &
    Rename_seqmem >= size(Rename_seqstruct(pp))+ii
  THEN
    Rename_seqstruct(pp):=Rename_seqstruct(pp) /|\ ii ||
    Rename_seqmem:=Rename_seqmem-size(Rename_seqstruct(pp))+ii
  END;

  Rename_CUT_SEQ_OBJ(pp,ii) =
  PRE
    pp:Rename_seqtok &
    ii:0..size(Rename_seqstruct(pp)) &
    Rename_seqmem >= ii
  THEN
    Rename_seqstruct(pp):=Rename_seqstruct(pp) \|/ ii ||
    Rename_seqmem:=Rename_seqmem-ii
  END;


  Rename_REV_SEQ_OBJ(pp) =
  PRE
    pp:Rename_seqtok
  THEN
    Rename_seqstruct(pp):=rev(Rename_seqstruct(pp))
  END;


  Rename_SWP_SEQ_OBJ(pp,ii,jj) =
  PRE
    pp:Rename_seqtok &
    ii:dom(Rename_seqstruct(pp)) &
    jj:dom(Rename_seqstruct(pp))
  THEN
    Rename_seqstruct(pp):= (
     Rename_seqstruct(pp) <+  (
       {ii |-> Rename_seqstruct(pp)(jj), jj |-> Rename_seqstruct(pp)(ii) }
       )
     )
  END;

  Rename_POP_SEQ_OBJ(pp) =
  PRE
    pp:Rename_seqtok &
    Rename_seqstruct(pp)/=<> &
    Rename_seqmem > 0
  THEN
    Rename_seqstruct(pp):= front(Rename_seqstruct(pp)) ||
    Rename_seqmem:=Rename_seqmem-1
  END;

  Rename_STO_SEQ_OBJ(pp,ii,vv) =
  PRE
    pp:Rename_seqtok &
    vv:VALUE &
    ii:1..size(Rename_seqstruct(pp))
  THEN 
    Rename_seqstruct(pp)(ii):=vv
  END;

  bb <-- Rename_APP_SEQ_OBJ(pp,qq) =
  PRE
    pp:Rename_seqtok &
    qq:Rename_seqtok 
    /* Rename_seqmem+size(Rename_seqstruct(qq))<=maxmem */
  THEN
    IF
     Rename_seqmem+size(Rename_seqstruct(qq))<=maxmem
    THEN
      Rename_seqstruct(pp):= (
        Rename_seqstruct(pp)^Rename_seqstruct(qq) 
      ) ||
      Rename_seqmem:= (
       Rename_seqmem+size(Rename_seqstruct(qq)) 
      ) ||
      bb:=TRUE
    ELSE
      bb:=FALSE
    END
  END;

  bb <-- Rename_CPY_SEQ_OBJ(pp,qq) =
  PRE
    pp:Rename_seqtok &
    qq:Rename_seqtok 
    /* Rename_seqmem -  ( 
     size(Rename_seqstruct(qq)) + size(Rename_seqstruct(pp))
     ) <= maxmem  */
  THEN
    IF
     Rename_seqmem - (
       size(Rename_seqstruct(qq))+ (
         size(Rename_seqstruct(pp))
       )
     ) <= maxmem
    THEN
      Rename_seqstruct(qq):=Rename_seqstruct(pp) ||
      Rename_seqmem:= (
       Rename_seqmem-size(Rename_seqstruct(qq))+ ( 
         size(Rename_seqstruct(pp)) 
         )
      )||
      bb:=TRUE
    ELSE
      bb:=FALSE
    END
  END;


  bb <-- Rename_OVR_SEQ_OBJ(pp,qq) =
  PRE
    pp:Rename_seqtok &
    qq:Rename_seqtok 
    /* Rename_seqmem + (
     size(Rename_seqstruct(qq))-size(Rename_seqstruct(pp))
    ) <= maxmem */
  THEN
    IF
      Rename_seqmem+ (
        size(Rename_seqstruct(qq))-(
          size(Rename_seqstruct(pp))
        )
      ) <= maxmem
    THEN
      Rename_seqstruct(qq):= (
        Rename_seqstruct(qq) <+ Rename_seqstruct(pp) 
      ) ||
      Rename_seqmem:= (
       Rename_seqmem + (
         max({0,(size(Rename_seqstruct(qq))-(
          size(Rename_seqstruct(pp))
         ))}) 
       )
      ) ||
      bb:=TRUE
    ELSE
      bb:=FALSE
    END
  END;

/************************ Persistent storage facilities *****************/

/***********  save/restore host byte order ***********/

  Rename_SAV_SEQ_OBJ =
  BEGIN
    skip
  END;

  Rename_RST_SEQ_OBJ =
  ANY
    sseqn,sseqo,stotseq
  WHERE
    sseqn <: Rename_SEQOBJ &
    sseqo: sseqn --> seq(VALUE) &
    stotseq:  NAT 
  THEN
    Rename_seqstruct := sseqo ||
    Rename_seqtok := sseqn ||
    Rename_seqmem := stotseq
  END;

/***********  save/restore network byte order ***********/

  Rename_SAVN_SEQ_OBJ =
  BEGIN
    skip
  END;

  Rename_RSTN_SEQ_OBJ =
  ANY
    sseqn,sseqo,stotseq
  WHERE
    sseqn <: Rename_SEQOBJ &
    sseqo: sseqn --> seq(VALUE) &
    stotseq:  NAT 
  THEN
    Rename_seqstruct := sseqo ||
    Rename_seqtok := sseqn ||
    Rename_seqmem := stotseq
  END;

/************************** Browsing ************************************/

  nn,pp <-- Rename_FIRST_SEQ_OBJ =  
  IF not(Rename_seqtok = {}) THEN
     pp :: Rename_seqtok || 
     nn := card(Rename_seqtok) 
  ELSE
     pp :: Rename_SEQOBJ ||
     nn := 0
  END;

  nn,qq <-- Rename_NEXT_SEQ_OBJ(mm,pp) = 
  PRE
    pp : Rename_seqtok &
    mm : NAT1
  THEN
    nn := mm-1 ||
    qq :: Rename_seqtok
  END;


/********************** Input Output facilities ************************/

  Rename_OUTPUT_SEQ_OBJ(SS,pp) =  
  PRE
    SS<: VALUE &
    pp: Rename_seqtok
  THEN
    skip
  END;

  bb <-- Rename_INPUT_SEQ_OBJ(SS,pp,ll) = 
  PRE
    SS<: VALUE &
    pp: Rename_seqtok &
    ll: 1..250
  THEN
     IF Rename_seqmem + ll <= maxmem THEN
       ANY ss WHERE
         ss : seq(VALUE) &
         size(ss) = ll
       THEN
         Rename_seqstruct(pp) := Rename_seqstruct(pp) ^ ss ||
         Rename_seqmem := Rename_seqmem + ll ||
         bb := TRUE
       END
     ELSE
     bb := FALSE
   END
  END

END
