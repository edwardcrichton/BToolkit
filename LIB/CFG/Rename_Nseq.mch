MACHINE      Rename_Nseq(maxint,maxsize)

CONSTRAINTS

   maxint <= 2147483646 &
   maxsize <= 2147483646

SEES         Bool_TYPE

VARIABLES    Rename_Nseq

INVARIANT

  Rename_Nseq: seq(0..maxint) &
  size(Rename_Nseq)<=maxsize

INITIALISATION

  Rename_Nseq:=<>

OPERATIONS

  bb <-- Rename_FUL_NSEQ =
  BEGIN
    bb:=bool(size(Rename_Nseq)=maxsize)
  END;

  bb <-- Rename_XST_IDX_NSEQ(ii) =
  PRE
    ii: 1..maxsize
  THEN
    bb:=bool(ii:1..size(Rename_Nseq))
  END;

/**************** sequence operations ***************/


  Rename_STO_NSEQ(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..size(Rename_Nseq)
  THEN 
    Rename_Nseq(ii):=vv
  END;

  Rename_CLR_NSEQ =
  BEGIN
    Rename_Nseq:=<>
  END;

  Rename_PSH_NSEQ(vv) =
  PRE
    vv: 0..maxint &
    size(Rename_Nseq) < maxsize
  THEN
    Rename_Nseq:=Rename_Nseq <- vv
  END;

  Rename_POP_NSEQ =
  PRE
    size(Rename_Nseq)/=0
  THEN
    Rename_Nseq:= front(Rename_Nseq)
  END;

  vv <-- Rename_FST_NSEQ =
  PRE
    size(Rename_Nseq)/=0
  THEN
    vv := Rename_Nseq(1)
  END;

  vv <-- Rename_LST_NSEQ =
  PRE
    size(Rename_Nseq)/=0
  THEN
    vv := Rename_Nseq(size(Rename_Nseq))
  END;

  Rename_TAL_NSEQ =
  PRE
    size(Rename_Nseq)/=0
  THEN
    Rename_Nseq := tail(Rename_Nseq)
  END;

  Rename_KEP_NSEQ(ii) =
  PRE
    ii:0..size(Rename_Nseq)
  THEN
    Rename_Nseq:=Rename_Nseq /|\ ii
  END;

  Rename_CUT_NSEQ(ii) =
  PRE
    ii:0..size(Rename_Nseq)
  THEN
    Rename_Nseq:=Rename_Nseq \|/ ii
  END;

  Rename_SWP_NSEQ(ii,jj) =
  PRE
    ii: 1..size(Rename_Nseq) &
    jj: 1..size(Rename_Nseq)
  THEN
    Rename_Nseq:=Rename_Nseq<+(
    {ii |-> Rename_Nseq(jj), jj |-> Rename_Nseq(ii)}
     )
  END;

/*****************  Queries ************************/

  
  vv <-- Rename_VAL_NSEQ(ii) =
  PRE
    ii:1..size(Rename_Nseq)
  THEN 
    vv:=Rename_Nseq(ii)
  END;

  nn <-- Rename_LEN_NSEQ =
  BEGIN
    nn:=size(Rename_Nseq)
  END;

  bb <-- Rename_EMP_NSEQ =
  BEGIN
    bb:=bool(Rename_Nseq=<>)
  END;

  vv <-- Rename_MAX_IDX_NSEQ(ii,jj) =
  PRE
    ii: dom(Rename_Nseq) &
    jj: dom(Rename_Nseq) &
    ran((ii..jj) <| Rename_Nseq) /= {}
  THEN
    vv::Rename_Nseq~[{max(ran((ii..jj) <| Rename_Nseq))}]
  END;

  vv <-- Rename_MIN_IDX_NSEQ(ii,jj) =
  PRE
    ii: dom(Rename_Nseq) &
    jj: dom(Rename_Nseq) &
    ran((ii..jj) <| Rename_Nseq) /= {}
  THEN
    vv::Rename_Nseq~[{min(ran((ii..jj) <| Rename_Nseq))}]
  END;

/************** Arithmetic operations ***************/


  Rename_ADD_NSEQ(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..size(Rename_Nseq) &
    Rename_Nseq(ii)+vv <= maxint
  THEN 
    Rename_Nseq(ii):=Rename_Nseq(ii)+vv
  END;

  Rename_MUL_NSEQ(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..size(Rename_Nseq) &
    Rename_Nseq(ii)*vv <= maxint
  THEN 
    Rename_Nseq(ii):=Rename_Nseq(ii)*vv
  END;

  Rename_SUB_NSEQ(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..size(Rename_Nseq) &
    Rename_Nseq(ii)-vv >= 0
  THEN 
    Rename_Nseq(ii):=Rename_Nseq(ii)-vv
  END;

  Rename_DIV_NSEQ(ii,vv) =
  PRE
    vv:1..maxint &
    ii:1..size(Rename_Nseq)
  THEN 
    Rename_Nseq(ii):=Rename_Nseq(ii)/vv
  END;

  Rename_MOD_NSEQ(ii,vv) =
  PRE
    vv:1..maxint &
    ii:1..size(Rename_Nseq)
  THEN 
    Rename_Nseq(ii):=Rename_Nseq(ii)-vv*(Rename_Nseq(ii)/vv)
  END;


/**************  equality queries **************/


  bb <-- Rename_EQL_NSEQ(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..size(Rename_Nseq)
  THEN
    bb:=bool(Rename_Nseq(ii)=vv)
  END;

  bb <-- Rename_NEQ_NSEQ(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..size(Rename_Nseq)
  THEN
    bb:=bool(Rename_Nseq(ii)/=vv)
  END;

  bb <-- Rename_GTR_NSEQ(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..size(Rename_Nseq)
  THEN
    bb:=bool(Rename_Nseq(ii)>vv)
  END;

  bb <-- Rename_GEQ_NSEQ(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..size(Rename_Nseq)
  THEN
    bb:=bool(Rename_Nseq(ii)>=vv)
  END;

  bb <-- Rename_SMR_NSEQ(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..size(Rename_Nseq)
  THEN
    bb:=bool(Rename_Nseq(ii)<vv)
  END;

  bb <-- Rename_LEQ_NSEQ(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..size(Rename_Nseq)
  THEN
    bb:=bool(Rename_Nseq(ii)<=vv)
  END;


/***************** Searching *********************/

  bb,ii <-- Rename_SCH_LO_EQL_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:=min(ss \/ {maxsize})
    END
  END;

  bb,ii <-- Rename_SCH_LO_NEQ_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[(0..maxint)-{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxsize})
    END
  END;

  bb,ii <-- Rename_SCH_LO_GEQ_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[vv..maxint]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxsize})
    END
  END;

  bb,ii <-- Rename_SCH_LO_GTR_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[vv+1..maxint]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxsize})
    END
  END;

  bb,ii <-- Rename_SCH_LO_LEQ_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[0..vv]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxsize})
    END
  END;

  bb,ii <-- Rename_SCH_LO_SMR_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[ 0..vv-1]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxsize})
    END
  END;

  bb,ii <-- Rename_SCH_HI_EQL_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_NEQ_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[(0..maxint)-{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_GEQ_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[vv..maxint]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_GTR_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[vv+1..maxint]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_LEQ_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[0..vv]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_SMR_NSEQ(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:dom(Rename_Nseq) &
    kk:dom(Rename_Nseq)
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Nseq~[ 0..vv-1]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

/************** Re-ordering **********************/

  Rename_SRT_ASC_NSEQ(ii,jj) =
  PRE
    ii:1..size(Rename_Nseq) &
    jj:1..size(Rename_Nseq) &
    ii <= jj
  THEN
    ANY ff,aa,bb,cc WHERE
      ff: (ii..jj) >->> (ii..jj) &
      aa = (1..ii-1) <| Rename_Nseq &
      bb: NAT +-> (0..maxint) &
      bb = (ff;Rename_Nseq) &
      !kk.(kk:ii..jj-1 => bb(kk) <= bb(kk+1)) &
      cc = (jj+1..size(Rename_Nseq)) <| Rename_Nseq
    THEN
      Rename_Nseq := aa \/ bb \/ cc
    END
  END;

  Rename_SRT_DSC_NSEQ(ii,jj) =
  PRE
    ii:1..size(Rename_Nseq) &
    jj:1..size(Rename_Nseq) &
    ii <= jj
  THEN
    ANY ff,aa,bb,cc WHERE
      ff: ii..jj >->> ii..jj &
      aa = (1..ii-1) <| Rename_Nseq &
      bb: NAT +-> (0..maxint) &
      bb = (ff;Rename_Nseq) &
      !kk.(kk:ii..jj-1 => bb(kk) >= bb(kk+1)) &
      cc = (jj+1..size(Rename_Nseq)) <| Rename_Nseq
    THEN
      Rename_Nseq := aa \/ bb \/ cc
    END
  END;

  Rename_REV_NSEQ(ii,jj) =
  PRE
    ii:1..size(Rename_Nseq) &
    jj:1..size(Rename_Nseq) &
    ii <= jj
  THEN
    LET aa,bb,cc BE
      aa = (1..ii-1) <| Rename_Nseq &
      bb = %kk.(kk:ii..jj | Rename_Nseq(jj+ii-kk)) &
      cc = (jj+1..size(Rename_Nseq)) <| Rename_Nseq
    IN
      Rename_Nseq := aa \/ bb \/ cc
    END
  END;

  Rename_RHT_NSEQ(ii,jj,nn) =
  PRE
    ii:1..size(Rename_Nseq) &
    jj:1..size(Rename_Nseq) &
    nn:1..size(Rename_Nseq) &
    ii <= jj
  THEN
    LET aa,bb,cc BE
      aa = (1..ii+nn-1) <| Rename_Nseq &
      bb = 1..size(Rename_Nseq) <| (
          %kk.(kk:ii+nn..(jj+nn) | Rename_Nseq(kk-nn))
      ) &
      cc = (jj+nn+1..size(Rename_Nseq)) <| Rename_Nseq
    IN
      Rename_Nseq := aa \/ bb \/ cc
    END
  END;

  Rename_LFT_NSEQ(ii,jj,nn) =
  PRE
    ii:1..size(Rename_Nseq) &
    jj:1..size(Rename_Nseq) &
    nn:1..size(Rename_Nseq) &
    ii <= jj
  THEN
    LET aa,bb,cc BE
      aa = (1..ii-nn-1) <| Rename_Nseq &
      bb = 1..size(Rename_Nseq) <| (
        %kk.(kk:ii-nn..(jj-nn) | Rename_Nseq(kk+nn))
      ) &
      cc = (jj-nn+1..size(Rename_Nseq)) <| Rename_Nseq
    IN
      Rename_Nseq := aa \/ bb \/ cc
    END
  END;


 
/**************  save/restore host byte order **************/

  Rename_SAV_NSEQ = skip;

  Rename_RST_NSEQ =
  ANY nseq WHERE
    nseq: seq(0..maxint) &
    size(nseq) <= maxsize
  THEN
    Rename_Nseq := nseq
  END;

/**************  save/restore network byte order **************/

  Rename_SAVN_NSEQ = skip;

  Rename_RSTN_NSEQ =
  ANY nseq WHERE
    nseq: seq(0..maxint) &
    size(nseq) <= maxsize
  THEN
    Rename_Nseq := nseq
  END


END

