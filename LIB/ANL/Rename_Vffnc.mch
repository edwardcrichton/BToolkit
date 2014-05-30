MACHINE

  Rename_Vffnc(VALUE,rcdsiz)

SEES

  Bool_TYPE, String_TYPE

CONSTANTS

  Rename_UnPack

PROPERTIES

  Rename_UnPack : (NAT +-> VALUE) --> STRING

VARIABLES

  Rename_Vfnc

INVARIANT

  Rename_Vfnc: 1..rcdsiz +-> VALUE 

INITIALISATION

  Rename_Vfnc := {} 

OPERATIONS

  bb <-- Rename_TST_FLD_FNC(ff) =
  PRE
    ff: NAT
  THEN
    bb:=bool(ff:1..rcdsiz)
  END;

  bb <-- Rename_DEF_FNC(ff) =
  PRE
    ff: 1..rcdsiz
  THEN
    bb:=bool(ff:dom(Rename_Vfnc))
  END;

  bb,dd <-- Rename_FREE_FNC =
  IF (1..rcdsiz )- dom(Rename_Vfnc) /= {}  THEN
    bb := TRUE ||
    dd :: (1..rcdsiz) - dom(Rename_Vfnc)
  ELSE
    bb := FALSE ||
    dd :: 1..rcdsiz 
  END;


  Rename_STO_FNC(ff,vv) =
  PRE
    ff:1..rcdsiz &
    vv:VALUE
  THEN 
    Rename_Vfnc(ff):=vv
  END;

  Rename_RMV_FNC(ff) =
  PRE
    ff:dom(Rename_Vfnc) 
  THEN 
    Rename_Vfnc:={ff} <<| Rename_Vfnc
  END;

  vv <-- Rename_VAL_FNC(ff) =
  PRE
    ff:dom(Rename_Vfnc)
  THEN 
    vv:=Rename_Vfnc(ff)
  END;


  bb <-- Rename_EQL_FNC(ff,vv) =
  PRE
    vv:VALUE &
    ff:dom(Rename_Vfnc)
  THEN
    bb:=bool(Rename_Vfnc(ff)=vv)
  END;

  bb <-- Rename_NEQ_FNC(ff,vv) =
  PRE
    vv:VALUE &
    ff:dom(Rename_Vfnc)
  THEN
    bb:=bool(Rename_Vfnc(ff)/=vv)
  END;



/********************* Additional FFNC facilities ************************/



 Rename_MOV_FFNC(ii,jj,ll) =
    PRE
      ii: 1..rcdsiz &
      jj: 1..rcdsiz &
      ll : 1..rcdsiz &
      ii..(ii+ll-1) /\ jj..(jj+ll-1) = {}  &
      jj..(jj+ll-1) <:  1..rcdsiz &
      ii..(ii+ll-1) <: dom(Rename_Vfnc) 
    THEN
       ANY newsegment WHERE
          newsegment : (jj..(jj+ll-1)) --> VALUE &
          newsegment = %xx.(xx:jj..(jj+ll-1)|Rename_Vfnc(ii+(jj-xx)))
       THEN
         Rename_Vfnc := Rename_Vfnc <+ newsegment
       END
    END;


  Rename_OVR_FFNC(ii,ll,aa) =
    PRE
      ii: 1..rcdsiz &
      ll: 1..rcdsiz &
      ii..(ii+ll-1) <: 1..rcdsiz &
      aa: STRING &
      ll * CHARperWORD > size(aa) 
    THEN
       ANY newsegment WHERE
          newsegment : (ii..(ii+ll-1)) --> VALUE &
          Rename_UnPack(newsegment) = aa
       THEN
         Rename_Vfnc := Rename_Vfnc <+ newsegment
       END
    END;

   Rename_OVR_LIT_FFNC(ii,ll,aa) =
    PRE
      ii: 1..rcdsiz &
      ll: 1..rcdsiz &
      ii..(ii+ll-1) <: 1..rcdsiz &
      aa: STRING &
      size(aa) < 1000 &
      ll * CHARperWORD > size(aa) 
    THEN
       ANY newsegment WHERE
          newsegment : (ii..(ii+ll-1)) --> VALUE &
          Rename_UnPack(newsegment) = aa
       THEN
         Rename_Vfnc := Rename_Vfnc <+ newsegment
       END
    END;

  vv <-- Rename_XTR_FFNC(ii,ll) =
    PRE
      ii: 1..rcdsiz  &
      ll: 1..rcdsiz  &
      ll <= 250 &
      ii..(ii+ll-1) <: dom(Rename_Vfnc) 
    THEN
      ANY str WHERE
         str : STRING &
         str = Rename_UnPack( (ii..(ii+ll-1))<<|Rename_Vfnc ) 
      THEN
         vv := str 
      END
    END;
   

  bb <-- Rename_EQL_FFNC(ii,ll,vv) =
    PRE
      ii: 1..rcdsiz &
      ll : 1..rcdsiz &
      ii..(ii+ll-1) <: dom(Rename_Vfnc) &
      vv: STRING
    THEN
       bb := bool( Rename_UnPack( (ii..(ii+ll-1))<<|Rename_Vfnc  ) = vv)
      
    END;


/**************  save/restore host byte order **************/

   Rename_SAV_FNC = BEGIN skip END;

 
   Rename_RST_FNC =
   BEGIN
      Rename_Vfnc  :: 1..rcdsiz +-> VALUE 
   END;

/**************  save/restore network byte order **************/

   Rename_SAVN_FNC = BEGIN skip END;

 
   Rename_RSTN_FNC =
   BEGIN
      Rename_Vfnc  :: 1..rcdsiz +-> VALUE 
   END



END

