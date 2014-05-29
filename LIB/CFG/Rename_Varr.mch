MACHINE         Rename_Varr(VALUE,maxidx)

SEES            Bool_TYPE

CONSTRAINTS     maxidx>0

VARIABLES       Rename_Varr

INVARIANT       Rename_Varr: 1..maxidx --> VALUE

INITIALISATION  Rename_Varr:: 1..maxidx --> VALUE

OPERATIONS

  bb <-- Rename_TST_IDX_ARR(ii) =
  PRE
    ii: NAT
  THEN
    bb := bool(ii:1..maxidx)
  END;

  vv <-- Rename_VAL_ARR(ii) =
  PRE
    ii:1..maxidx
  THEN 
    vv:=Rename_Varr(ii)
  END;

  Rename_STO_ARR(ii,vv) =
  PRE
    vv:VALUE &
    ii:1..maxidx
  THEN 
    Rename_Varr(ii):=vv
  END;

  bb <-- Rename_EQL_ARR(ii,vv) =
  PRE
    vv:VALUE &
    ii:1..maxidx
  THEN
    bb:=bool(Rename_Varr(ii)=vv)
  END;

  bb <-- Rename_NEQ_ARR(ii,vv) =
  PRE
    vv:VALUE &
    ii:1..maxidx
  THEN
    bb:=bool(Rename_Varr(ii)/=vv)
  END;


  bb,ii <-- Rename_SCH_LO_EQL_ARR(jj,kk,vv) =
  PRE
    vv:VALUE &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Varr~[{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxidx})
    END
  END;

  bb,ii <-- Rename_SCH_LO_NEQ_ARR(jj,kk,vv) =
  PRE
    vv:VALUE &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Varr~[(VALUE)-{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= min(ss \/ {maxidx})
    END
  END;


  bb,ii <-- Rename_SCH_HI_EQL_ARR(jj,kk,vv) =
  PRE
    vv:VALUE &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Varr~[{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;

  bb,ii <-- Rename_SCH_HI_NEQ_ARR(jj,kk,vv) =
  PRE
    vv:VALUE &
    jj:1..maxidx &
    kk:1..maxidx
  THEN
    LET ss BE
      ss = (jj..kk) /\ Rename_Varr~[(VALUE)-{vv}]
    IN
      bb:=bool(ss/={}) ||
      ii:= max(ss \/ {1})
    END
  END;



  Rename_REV_ARR(ii,jj) =
  PRE
    ii:1..maxidx &
    jj:1..maxidx &
    ii < jj
  THEN
    LET Same,Rev BE
      Same = (1..ii-1\/jj+1..maxidx) <| Rename_Varr &
      Rev = %kk.(kk:ii..jj | Rename_Varr(jj+ii-kk)) 
    IN 
      Rename_Varr := Same \/ Rev
    END 
  END;

  Rename_RHT_ARR(ii,jj,nn) =
  PRE
    ii:1..maxidx &
    jj:1..maxidx &
    nn:1..maxidx &
    ii <= jj
  THEN
    LET Same, RShift BE
      Same = ((1..ii+nn-1)\/(jj+nn+1..maxidx)) <| Rename_Varr &
      RShift = %kk.(kk:ii+nn..min({maxidx,jj+nn}) | Rename_Varr(kk-nn)) 
    IN
      Rename_Varr := Same \/ RShift
    END
  END;

  Rename_LFT_ARR(ii,jj,nn) =
  PRE
    ii:1..maxidx &
    jj:1..maxidx &
    nn:1..maxidx &
    ii <= jj
  THEN
    LET Same, LShift BE
      Same = ((1..ii-nn-1)\/(jj-nn+1..maxidx)) <| Rename_Varr &
      LShift = %kk.(kk:max({1,ii-nn})..jj-nn | Rename_Varr(kk+nn))    IN
      Rename_Varr := Same \/ LShift
    END
  END;

  Rename_SWP_ARR(ii,jj) =
  PRE
    ii: 1..maxidx &
    jj: 1..maxidx
  THEN
    Rename_Varr:=
    Rename_Varr<+{ii |-> Rename_Varr(jj), jj |-> Rename_Varr(ii)}
  END;


/**************  save/restore host byte order **************/

 Rename_SAV_ARR = BEGIN skip END;

 Rename_RST_ARR =
 BEGIN  Rename_Varr :: 1..maxidx --> VALUE END;

/**************  save/restore network byte order **************/

 Rename_SAVN_ARR = BEGIN skip END;

 Rename_RSTN_ARR =
 BEGIN  Rename_Varr :: 1..maxidx --> VALUE END


END

