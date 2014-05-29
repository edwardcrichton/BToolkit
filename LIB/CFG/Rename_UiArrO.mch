/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
v0.03
  VERSION:          B-Toolkit Beta 4.51
  DATE:             06/07/99
***/

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
040898 v0.02 : Changed SEES from `Bool_TYPE, Byt_TYPE, Uns_TYPE' to
               `Bool_TYPE, PASP_TYPE' (the same as the .imp)
060799 v0.03 : Changes to facilitate proof of Rename_UiArrOI.imp
               Removed VARIABLE Rename_UiAO_arr (redundant)
               Removed card(Rename_ARROBJ) = maxobj
               Added card(Rename_UiAO_arrtok) < maxobj to INVARIANT
               Changed all Rename_UiAO_arrtok = Rename_ARROBJ ->
                                         card(Rename_UiAO_arrtok) = maxobj, etc.
               Changed Rename_UiAO_FIL to be deterministic (using *)
               Changed constraints to : maxobj*ub<=65535 (was 32768)
               Removed constant Rename_lb so that all occurrences
                                         of u2n(Rename_lb) simplify to 1
               Added PROPERTY that Rename_ARROBJ is BYTE (since this fact
               could not be inferred from this spec)
*/

MACHINE             Rename_UiArrO(maxobj,ub)	
/* `maxobj' - max no. objects,  no. of storage locations. */	

SEES                Bool_TYPE, PASP_TYPE

CONSTRAINTS         maxobj: 1..255 & ub>0 & maxobj*ub<=65535

SETS                Rename_ARROBJ

PROPERTIES          Rename_ARROBJ = BYTE

VARIABLES

  Rename_UiAO_arrtok,	 /* array identifiers (tokens). */
  Rename_UiAO_arrstruct, /* structure consisting of each array and its token. */
  Rename_UiAO_nxt	 /* array pointer structure. */

INVARIANT

  Rename_UiAO_arrtok <: Rename_ARROBJ &
  card(Rename_UiAO_arrtok) <= maxobj &
  Rename_UiAO_arrstruct: Rename_UiAO_arrtok --> (1..ub +-> BYTE) &
  Rename_UiAO_nxt :  Rename_UiAO_arrtok --> /* NAT */ 1..ub

INITIALISATION

  Rename_UiAO_arrtok, Rename_UiAO_arrstruct, Rename_UiAO_nxt := {},{},{}

OPERATIONS

/******************  General query functions *********************/


  /* Are all the tokens used up. */
  bb <-- Rename_UiAO_OBJ_FUL =
  BEGIN
    bb:=bool(card(Rename_UiAO_arrtok) = maxobj)
  END;

  /* Does the array `pp' exist? */
  bb <-- Rename_UiAO_XST(pp : Rename_ARROBJ) =
  BEGIN
    bb:=bool(pp:Rename_UiAO_arrtok)
  END;


/******************  Creating and deleting sequences **************/


  /* Reset all pointers. */
  Rename_UiAO_INI =
  BEGIN
    Rename_UiAO_arrtok, Rename_UiAO_arrstruct,  Rename_UiAO_nxt := {},{},{}
  END;

  /* Create an array structure. */
  bb,pp <-- Rename_UiAO_CRE =
    IF card(Rename_UiAO_arrtok) < maxobj THEN
        ANY qq WHERE
          qq: Rename_ARROBJ - Rename_UiAO_arrtok
        THEN
          Rename_UiAO_arrstruct(qq):= {} ||	/* EMPTY MAP */
          Rename_UiAO_nxt(qq) := 1 ||
          Rename_UiAO_arrtok := Rename_UiAO_arrtok \/ {qq} ||
          pp:=qq ||
          bb := TRUE
        END
    ELSE
        bb:= FALSE || pp :: Rename_ARROBJ
    END;

/* No need to kill one array kill all with INI. */

/******************  Query functions for individual sequences **********/

  /* View contents of location. */
  vv <-- Rename_UiAO_VAL(pp : Rename_ARROBJ & ii : UNSIGNED) =
    PRE
      pp:Rename_UiAO_arrtok &
      u2n(ii):dom(Rename_UiAO_arrstruct(pp))
    THEN 
      vv:=Rename_UiAO_arrstruct(pp)(u2n(ii))
    END;


  /* Next available storage location in `pp'. */
  nn <-- Rename_UiAO_NXT(pp : Rename_ARROBJ) =
    PRE pp : Rename_UiAO_arrtok THEN
      nn := n2u(Rename_UiAO_nxt(pp))
    END;


  /* Are two array contents equal (ignoring next points). */
  bb <-- Rename_UiAO_EQL(ss : Rename_ARROBJ & tt : Rename_ARROBJ) =
    PRE
       tt : Rename_UiAO_arrtok &
       ss : Rename_UiAO_arrtok
    THEN
       bb := bool(Rename_UiAO_arrstruct(tt) = Rename_UiAO_arrstruct(ss))
    END;

/******************   Sequence Operations ***********************/

 /* Store vv in array pp at location ii and set next location to ii+1 */
 Rename_UiAO_STO(pp : Rename_ARROBJ & ii : UNSIGNED & vv : BYTE) =
   PRE
     pp : Rename_UiAO_arrtok &
     u2n(ii) : 1..ub
   THEN 
     Rename_UiAO_arrstruct(pp)(u2n(ii)) := vv ||

     IF u2n(ii) < ub THEN
       Rename_UiAO_nxt(pp) := u2n(ii) + 1 /* Next available position recorded. */
     ELSE 
       Rename_UiAO_nxt(pp) := 1	 /* Wraps around. */
     END
   END;


 /* Store vv in array pp at `next' location and inc next location. */
  Rename_UiAO_STO_NXT(pp : Rename_ARROBJ & vv :BYTE) =
    PRE pp: Rename_UiAO_arrtok THEN
      Rename_UiAO_arrstruct(pp)(Rename_UiAO_nxt(pp)) := vv ||
      IF Rename_UiAO_nxt(pp) < ub THEN
        Rename_UiAO_nxt(pp) := Rename_UiAO_nxt(pp) + 1 /* Next available position recorded.*/
      ELSE 
        Rename_UiAO_nxt(pp) := 1		    /* Wraps around. */
      END
    END;


  /* Copy array pp to array qq. */
  Rename_UiAO_CPY(pp : Rename_ARROBJ & qq : Rename_ARROBJ) =
    PRE
      pp:Rename_UiAO_arrtok &
      qq:Rename_UiAO_arrtok 
    THEN
      Rename_UiAO_arrstruct(qq):=Rename_UiAO_arrstruct(pp)
    END;


/* fill store. */
  Rename_UiAO_FILL(pp : Rename_ARROBJ & vv : BYTE) =
    PRE pp:Rename_UiAO_arrtok THEN
      Rename_UiAO_arrstruct(pp) := (1..ub) * {vv}  ||
      Rename_UiAO_nxt(pp):= 1		/* wraps around. */
    END

END
