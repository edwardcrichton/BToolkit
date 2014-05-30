MACHINE         Rename_Narr(maxint,maxidx)

CONSTRAINTS

   maxint > 0 &
   maxint <= 2147483646 &
   maxidx <= 2147483646

SEES            Bool_TYPE

VARIABLES       Rename_Narr

INVARIANT       Rename_Narr: 1..maxidx --> 0..maxint

INITIALISATION  Rename_Narr:: 1..maxidx --> 0..maxint

OPERATIONS

  bb <-- Rename_TST_IDX_NARR(ii) =
  PRE ii: NAT
  THEN
    bb := bool(ii:1..maxidx)
  END;

  vv <-- Rename_MAX_IDX_NARR(ii,jj) =
  PRE
    ii: 1..maxidx &
    jj: 1..maxidx &
    ran((ii..jj) <| Rename_Narr) /= {}
  THEN
    vv::Rename_Narr~[{max(ran((ii..jj) <| Rename_Narr))}]
  END;

  vv <-- Rename_MIN_IDX_NARR(ii,jj) =
  PRE
    ii: 1..maxidx &
    jj: 1..maxidx &
    ran((ii..jj) <| Rename_Narr) /= {}
  THEN
    vv::Rename_Narr~[{min(ran((ii..jj) <| Rename_Narr))}]
  END;

  vv <-- Rename_VAL_NARR(ii) =
  PRE ii:1..maxidx
  THEN 
    vv:=Rename_Narr(ii)
  END;

  Rename_STO_NARR(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..maxidx
  THEN 
    Rename_Narr(ii):=vv
  END;

  Rename_ADD_NARR(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..maxidx &
    Rename_Narr(ii)+vv <= maxint
  THEN 
    Rename_Narr(ii):=Rename_Narr(ii)+vv
  END;

  Rename_MUL_NARR(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..maxidx &
    Rename_Narr(ii)*vv <= maxint
  THEN 
    Rename_Narr(ii):=Rename_Narr(ii)*vv
  END;

  Rename_SUB_NARR(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..maxidx &
    Rename_Narr(ii) >= vv 
  THEN 
    Rename_Narr(ii):=Rename_Narr(ii)-vv
  END;

  Rename_DIV_NARR(ii,vv) =
  PRE
    vv:1..maxint &
    ii:1..maxidx
  THEN 
    Rename_Narr(ii):=Rename_Narr(ii)/vv
  END;

  Rename_MOD_NARR(ii,vv) =
  PRE
    vv:1..maxint &
    ii:1..maxidx
  THEN 
    Rename_Narr(ii):=Rename_Narr(ii)-vv*(Rename_Narr(ii)/vv)
  END;

  bb <-- Rename_EQL_NARR(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..maxidx
  THEN
    bb:=bool(Rename_Narr(ii)=vv)
  END;

  bb <-- Rename_NEQ_NARR(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..maxidx
  THEN
    bb:=bool(Rename_Narr(ii)/=vv)
  END;

  bb <-- Rename_GTR_NARR(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..maxidx
  THEN
    bb:=bool(Rename_Narr(ii)>vv)
  END;

  bb <-- Rename_GEQ_NARR(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..maxidx
  THEN
    bb:=bool(Rename_Narr(ii)>=vv)
  END;

  bb <-- Rename_SMR_NARR(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..maxidx
  THEN
    bb:=bool(Rename_Narr(ii)<vv)
  END;

  bb <-- Rename_LEQ_NARR(ii,vv) =
  PRE
    vv:0..maxint &
    ii:1..maxidx
  THEN
    bb:=bool(Rename_Narr(ii)<=vv)
  END;

  bb,ii <-- Rename_SCH_LO_EQL_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxidx})
    END
  END;

  bb,ii <-- Rename_SCH_LO_NEQ_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[(0..maxint)-{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxidx})
    END
  END;

  bb,ii <-- Rename_SCH_LO_GEQ_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[vv..maxint]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxidx})
    END
  END;

  bb,ii <-- Rename_SCH_LO_GTR_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[vv+1..maxint]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxidx})
    END
  END;

  bb,ii <-- Rename_SCH_LO_LEQ_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[0..vv]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxidx})
    END
  END;

  bb,ii <-- Rename_SCH_LO_SMR_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[ 0..vv-1]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxidx})
    END
  END;

  bb,ii <-- Rename_SCH_HI_EQL_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_NEQ_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[(0..maxint)-{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_GEQ_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[vv..maxint]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_GTR_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[vv+1..maxint]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_LEQ_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[0..vv]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_SMR_NARR(jj,kk,vv) =
  PRE
    vv:0..maxint &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Narr~[ 0..vv-1]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  Rename_SRT_ASC_NARR(ii,jj) =
  PRE
    ii:1..maxidx &
    jj:1..maxidx &
    ii <= jj
  THEN
    ANY ff,aa,bb,cc WHERE
      ff: (ii..jj) >->> (ii..jj) &
      bb: NAT +-> (0..maxint) &
      bb = (ff;Rename_Narr) &
      !kk.(kk:ii..jj-1 => bb(kk) <= bb(kk+1)) &
      aa = (1..ii-1) <| Rename_Narr &
      cc = (jj+1..maxidx) <| Rename_Narr
    THEN
      Rename_Narr := aa \/ bb \/ cc
    END
  END;

  Rename_SRT_DSC_NARR(ii,jj) =
  PRE
    ii:1..maxidx &
    jj:1..maxidx  &
    ii <= jj
  THEN
    ANY ff,aa,bb,cc WHERE
      ff: ii..jj >->> ii..jj &
      bb: NAT +-> (0..maxint) &
      bb = (ff;Rename_Narr) &
      !kk.(kk:ii..jj-1 => bb(kk) >= bb(kk+1)) &
      aa = (1..ii-1) <| Rename_Narr &
      cc = (jj+1..maxidx) <| Rename_Narr
    THEN
      Rename_Narr := aa \/ bb \/ cc
    END
  END;

  Rename_REV_NARR(ii,jj) =
  PRE
    ii:1..maxidx &
    jj:1..maxidx &
    ii <= jj
  THEN
    LET aa,bb,cc BE
      aa = (1..ii-1) <| Rename_Narr &
      bb = %kk.(kk:ii..jj | Rename_Narr(jj+ii-kk)) &
      cc = (jj+1..maxidx) <| Rename_Narr
    IN
      Rename_Narr := aa \/ bb \/ cc
    END
  END;

  Rename_RHT_NARR(ii,jj,nn) =
  PRE
    ii:1..maxidx &
    jj:1..maxidx &
    nn:1..maxidx &
    ii <= jj
  THEN
    LET aa,bb,cc BE
      aa = (1..ii+nn-1) <| Rename_Narr &
      bb = %kk.(
           kk:ii+nn..min({maxidx,jj+nn}) | Rename_Narr(kk-nn)
           ) &
      cc = (jj+nn+1..maxidx) <| Rename_Narr
    IN
      Rename_Narr := aa \/ bb \/ cc
    END
  END;

  Rename_LFT_NARR(ii,jj,nn) =
  PRE
    ii:1..maxidx &
    jj:1..maxidx &
    ii <= jj &
    nn:1..maxidx
  THEN
    LET aa,bb,cc BE
      aa = (1..ii-nn-1) <| Rename_Narr &
      bb = %kk.(
           kk:max({1,ii-nn})..jj-nn | Rename_Narr(kk+nn)
           ) &
      cc = (jj-nn+1..maxidx) <| Rename_Narr
    IN
      Rename_Narr := aa \/ bb \/ cc
    END
  END;


  Rename_SWP_NARR(ii,jj) =
  PRE
    ii: 1..maxidx &
    jj: 1..maxidx
  THEN
    Rename_Narr:= ( 
      Rename_Narr<+{ii |-> Rename_Narr(jj), jj |-> Rename_Narr(ii)}
      )
  END;


/**************  save/restore host byte order **************/

 Rename_SAV_NARR = BEGIN skip END;

 Rename_RST_NARR =
 BEGIN  Rename_Narr :: 1..maxidx --> 0..maxint END;


/**************  save/restore network byte order **************/

 Rename_SAVN_NARR = BEGIN skip END;
 
 Rename_RSTN_NARR =
 BEGIN  Rename_Narr :: 1..maxidx --> 0..maxint END


END

