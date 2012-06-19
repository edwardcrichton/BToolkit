MACHINE

  Rename_Vseq(VALUE,maxsize)

SEES

 Bool_TYPE

VARIABLES

  Rename_Vseq

INVARIANT

  Rename_Vseq: seq(VALUE) &
  size(Rename_Vseq)<=maxsize

INITIALISATION

  Rename_Vseq:=<>

OPERATIONS

  bb <-- Rename_FUL_SEQ =
  BEGIN
    bb:=bool(size(Rename_Vseq)=maxsize)
  END;

  bb <-- Rename_XST_IDX_SEQ(ii) =
  PRE
    ii: 1..maxsize
  THEN
    bb:=bool(ii:1..size(Rename_Vseq))
  END;


  Rename_STO_SEQ(ii,vv) =
  PRE
    vv:VALUE &
    ii:1..size(Rename_Vseq)
  THEN 
    Rename_Vseq(ii):=vv
  END;

  Rename_CLR_SEQ =
  BEGIN
    Rename_Vseq:=<>
  END;

  Rename_PSH_SEQ(vv) =
  PRE
    vv: VALUE &
    size(Rename_Vseq) < maxsize
  THEN
    Rename_Vseq:=Rename_Vseq <- vv
  END;

  Rename_POP_SEQ =
  PRE
    size(Rename_Vseq)/=0
  THEN
    Rename_Vseq:= front(Rename_Vseq)
  END;

  vv <-- Rename_FST_SEQ =
  PRE
    size(Rename_Vseq)/=0
  THEN
    vv := Rename_Vseq(1)
  END;

  vv <-- Rename_LST_SEQ =
  PRE
    size(Rename_Vseq)/=0
  THEN
    vv := Rename_Vseq(size(Rename_Vseq))
  END;

  Rename_TAL_SEQ =
  PRE
    size(Rename_Vseq)/=0
  THEN
    Rename_Vseq := tail(Rename_Vseq)
  END;

  Rename_KEP_SEQ(ii) =
  PRE
    ii:0..size(Rename_Vseq)
  THEN
    Rename_Vseq:=Rename_Vseq /|\ ii
  END;

  Rename_CUT_SEQ(ii) =
  PRE
    ii:0..size(Rename_Vseq)
  THEN
    Rename_Vseq:=Rename_Vseq \|/ ii
  END;

  Rename_SWP_SEQ(ii,jj) =
  PRE
    ii: 1..size(Rename_Vseq) &
    jj: 1..size(Rename_Vseq)
  THEN
    Rename_Vseq:= (
      Rename_Vseq<+{ii |-> Rename_Vseq(jj), jj |-> Rename_Vseq(ii)}
    )
  END;



  vv <-- Rename_VAL_SEQ(ii) =
  PRE
    ii:1..size(Rename_Vseq)
  THEN 
    vv:=Rename_Vseq(ii)
  END;

  nn <-- Rename_LEN_SEQ =
  BEGIN
    nn:=size(Rename_Vseq)
  END;

  bb <-- Rename_EMP_SEQ =
  BEGIN
    bb:=bool(Rename_Vseq=<>)
  END;

  bb <-- Rename_EQL_SEQ(ii,vv) =
  PRE
    vv:VALUE &
    ii:1..size(Rename_Vseq)
  THEN
    bb:=bool(Rename_Vseq(ii)=vv)
  END;

  bb <-- Rename_NEQ_SEQ(ii,vv) =
  PRE
    vv:VALUE &
    ii:1..size(Rename_Vseq)
  THEN
    bb:=bool(Rename_Vseq(ii)/=vv)
  END;

  bb,ii <-- Rename_SCH_LO_EQL_SEQ(jj,kk,vv) =
  PRE
    vv:VALUE &
    jj:dom(Rename_Vseq) &
    kk:dom(Rename_Vseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Vseq~[{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:=min(ss \/ {maxsize})
    END
  END;

  bb,ii <-- Rename_SCH_LO_NEQ_SEQ(jj,kk,vv) =
  PRE
    vv:VALUE &
    jj:dom(Rename_Vseq) &
    kk:dom(Rename_Vseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Vseq~[(VALUE)-{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxsize})
    END
  END;

  
  bb,ii <-- Rename_SCH_HI_EQL_SEQ(jj,kk,vv) =
  PRE
    vv:VALUE &
    jj:dom(Rename_Vseq) &
    kk:dom(Rename_Vseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Vseq~[{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_NEQ_SEQ(jj,kk,vv) =
  PRE
    vv:VALUE &
    jj:dom(Rename_Vseq) &
    kk:dom(Rename_Vseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Vseq~[(VALUE)-{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;


  Rename_REV_SEQ(ii,jj) =
  PRE
    ii:1..size(Rename_Vseq) &
    jj:1..size(Rename_Vseq) &
    ii <= jj
  THEN
    LET aa,bb,cc BE
      aa = (1..ii-1) <| Rename_Vseq &
      bb = %kk.(kk:ii..jj | Rename_Vseq(jj+ii-kk)) &
      cc = (jj+1..size(Rename_Vseq)) <| Rename_Vseq
    IN
      Rename_Vseq := aa \/ bb \/ cc
    END
  END;

  Rename_RHT_SEQ(ii,jj,nn) =
  PRE
    ii:1..size(Rename_Vseq) &
    jj:1..size(Rename_Vseq) &
    nn:1..size(Rename_Vseq) &
    ii <= jj
  THEN
    LET aa,bb,cc BE
      aa = (1..ii+nn-1) <| Rename_Vseq &
      bb = 1..size(Rename_Vseq) <| (
         %kk.(kk:ii+nn..(jj+nn) | Rename_Vseq(kk-nn)) 
       ) &
      cc = (jj+nn+1..size(Rename_Vseq)) <| Rename_Vseq
    IN
      Rename_Vseq := aa \/ bb \/ cc
    END
  END;

  Rename_LFT_SEQ(ii,jj,nn) =
  PRE
    ii:1..size(Rename_Vseq) &
    jj:1..size(Rename_Vseq) &
    nn:1..size(Rename_Vseq) &
    ii <= jj
  THEN
    LET aa,bb,cc BE
      aa = (1..ii-nn-1) <| Rename_Vseq &
      bb = 1..size(Rename_Vseq) <| ( 
            %kk.(kk:ii-nn..(jj-nn) | Rename_Vseq(kk+nn))
          ) &
      cc = (jj-nn+1..size(Rename_Vseq)) <| Rename_Vseq
    IN
      Rename_Vseq := aa \/ bb \/ cc
    END
  END;


/**************  save/restore host byte order **************/

  Rename_SAV_SEQ = skip;

  Rename_RST_SEQ =
  ANY vseq WHERE
     vseq: seq(VALUE) &
     size(vseq) <= maxsize
  THEN
    Rename_Vseq := vseq
  END;

/**************  save/restore network byte order **************/

  Rename_SAVN_SEQ = skip;

  Rename_RSTN_SEQ =
  ANY vseq WHERE
     vseq: seq(VALUE) &
     size(vseq) <= maxsize
  THEN
    Rename_Vseq := vseq
  END

END
