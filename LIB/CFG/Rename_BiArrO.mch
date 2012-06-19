/*
Description: Machine adapted from the object sequence.  This array sequences has many
simplifications.  Each array has a fixed length.  There is a seperation of concerns.
Array object are for storage primarily.  It is assumed that those wishing to 
undertake arithmetic manipulation of index contents or comparsons of index values
will use the individual array machines.
 Operations FULL, XST, INI, CRE, VAL, NXT, EQL, STO, NXT_STO, CPY, FILL


History :
080597 v0.01 : Created.
130597 v0.02 : Member operation removed - possibility of reading unwritten
 	       locations.
*/
MACHINE             Rename_BiArrO(maxobj,ub)	
/* `maxobj - max no. objects,  no. of storage locations. */	

SEES                Bool_TYPE, Byt_TYPE, Uns_TYPE

CONSTRAINTS         maxobj: 1..255 & ub>0 & maxobj*ub<=32768
  
SETS                Rename_ARROBJ

CONSTANTS           Rename_lb

PROPERTIES          card(Rename_ARROBJ) = maxobj & Rename_lb = n2u(1)

VARIABLES

  Rename_BiAO_arr,
  Rename_BiAO_arrtok,		/* array identifiers (tokens). */
  Rename_BiAO_arrstruct,	/* structure consisting of each array and its token. */
  Rename_BiAO_nxt		/* array pointer structure. */

INVARIANT

  Rename_BiAO_arr : u2n(Rename_lb)..ub +-> BYTE &
  Rename_BiAO_arrtok <: Rename_ARROBJ &
  Rename_BiAO_arrstruct: Rename_BiAO_arrtok --> (u2n(Rename_lb)..ub +-> BYTE) &
  Rename_BiAO_nxt :  Rename_BiAO_arrtok --> /* NAT */ u2n(Rename_lb)..ub

INITIALISATION

  Rename_BiAO_arr, Rename_BiAO_arrtok, Rename_BiAO_arrstruct, Rename_BiAO_nxt :=
       {},{},{},{}

OPERATIONS

/******************  General query functions *********************/


  /* Are all the tokens used up. */
  bb <-- Rename_BiAO_OBJ_FUL =
  BEGIN
    bb:=bool(Rename_ARROBJ =  Rename_BiAO_arrtok)
  END;

  /* Does the array `pp' exist? */
  bb <-- Rename_BiAO_XST(pp) =
  PRE
    pp: Rename_ARROBJ
  THEN
    bb:=bool(pp:Rename_BiAO_arrtok)
  END;


/******************  Creating and deleting sequences **************/


  /* Reset all pointers. */
  Rename_BiAO_INI =
  BEGIN
    Rename_BiAO_arrtok, Rename_BiAO_arrstruct,  Rename_BiAO_nxt := {},{}, {}
  END;

  /* Create an array structure. */
  bb,pp <-- Rename_BiAO_CRE =
  IF Rename_BiAO_arrtok /= Rename_ARROBJ THEN
      ANY qq WHERE
        qq: Rename_ARROBJ - Rename_BiAO_arrtok
      THEN
        Rename_BiAO_arrstruct(qq):= {} ||	/* EMPTY MAP */
        Rename_BiAO_nxt(qq) := u2n(Rename_lb) ||
        Rename_BiAO_arrtok := Rename_BiAO_arrtok \/ {qq} ||
        pp:=qq ||
        bb := TRUE
      END
  ELSE
      bb:= FALSE || pp :: Rename_ARROBJ
  END;

/* No need to kill one array kill all with INI. */

/******************  Query functions for individual sequences **********/

  /* View contents of location. */
  vv <-- Rename_BiAO_VAL(pp,ii) =
  PRE
    ii : UNSIGNED &
    pp:Rename_BiAO_arrtok &
    u2n(ii):dom(Rename_BiAO_arrstruct(pp))
  THEN 
    vv:=Rename_BiAO_arrstruct(pp)(u2n(ii))
  END;


  /* Next available storage location in `pp'. */
  nn <-- Rename_Rename_BiAO_nxt(pp) =
  PRE
    pp : Rename_BiAO_arrtok
  THEN
    nn := n2u(Rename_BiAO_nxt(pp))
  END;


  /* Are two array contents equal (notincluding next points). */
  bb <-- Rename_BiAO_EQL(ss,tt) =
  PRE
     tt : Rename_BiAO_arrtok &
     ss : Rename_BiAO_arrtok
  THEN
     bb := bool(Rename_BiAO_arrstruct(tt) = Rename_BiAO_arrstruct(ss))
  END;

/******************   Sequence Operations ***********************/

 /* Store vv in array pp at location ii and set next location to ii+1 */
 Rename_BiAO_STO(pp,ii,vv) =
  PRE
    pp : Rename_BiAO_arrtok &
    vv : BYTE &
    ii : UNSIGNED &
    u2n(ii) : u2n(Rename_lb)..ub
  THEN 
    Rename_BiAO_arrstruct(pp)(u2n(ii)) := vv ||

    IF u2n(ii) < ub THEN
      Rename_BiAO_nxt(pp) := u2n(ii) + 1 /* Next available position recorded. */
    ELSE 
      Rename_BiAO_nxt(pp) := u2n(Rename_lb)	 /* Wraps around. */
    END
  END;


 /* Store vv in array pp at `next' location and inc next location. */
  Rename_BiAO_STO_NXT(pp,vv) =
  PRE
    pp: Rename_BiAO_arrtok &
    vv: BYTE
  THEN
    Rename_BiAO_arrstruct(pp)(Rename_BiAO_nxt(pp)) := vv ||

    IF Rename_BiAO_nxt(pp) < ub THEN
      Rename_BiAO_nxt(pp) := Rename_BiAO_nxt(pp) + 1 /* Next available position recorded.*/
    ELSE 
      Rename_BiAO_nxt(pp) := u2n(Rename_lb)		    /* Wraps around. */
    END
  END;


  /* Copy array pp to array qq. */
  Rename_BiAO_CPY(pp,qq) =
  PRE
    pp:Rename_BiAO_arrtok &
    qq:Rename_BiAO_arrtok 
  THEN
    Rename_BiAO_arrstruct(qq):=Rename_BiAO_arrstruct(pp)
  END;


/* fill store. */
  Rename_BiAO_FILL(pp: Rename_ARROBJ & vv : BYTE) =
  PRE
    pp:Rename_BiAO_arrtok
  THEN
    ANY array WHERE
      array : u2n(Rename_lb)..ub +-> BYTE &
      card(array) = ub &
      ran(array) = {vv}
    THEN
      Rename_BiAO_arrstruct(pp) := array
    END
         ||
    Rename_BiAO_nxt(pp):= u2n(Rename_lb)		/* wraps around. */
  END

END



