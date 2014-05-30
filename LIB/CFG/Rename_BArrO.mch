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
MACHINE

  Rename_BArrO(maxobj,ub)	
/* `maxobj - max no. objects,  no. of storage locations. */	

SEES

 Bool_TYPE, Byt_TYPE, Uns_TYPE

CONSTRAINTS

  maxobj>0 & maxobj<256 & ub>0 & maxobj*ub<=32768
  
SETS

  ARROBJ

CONSTANTS
  lb

PROPERTIES

  card(ARROBJ) = maxobj &
  lb = n2u(1)

VARIABLES

  BAO_arr,
  BAO_arrtok,		/* array identifiers (tokens). */
  BAO_arrstruct,	/* structure consisting of each array and its token. */
  BAO_nxt		/* array pointer structure. */

INVARIANT

  BAO_arr : u2n(lb)..ub +-> BYTE &
  BAO_arrtok <: ARROBJ &
  BAO_arrstruct: BAO_arrtok --> (u2n(lb)..ub +-> BYTE) &
  BAO_nxt :  BAO_arrtok --> NAT

INITIALISATION

  BAO_arr, BAO_arrtok, BAO_arrstruct, BAO_nxt := {},{},{},{}

OPERATIONS

/******************  General query functions *********************/


  /* Are all the tokens used up. */
  bb <-- Rename_BAO_OBJ_FUL =
  BEGIN
    bb:=bool(ARROBJ =  BAO_arrtok)
  END;

  /* Does the array `pp' exist? */
  bb <-- Rename_BAO_XST(pp) =
  PRE
    pp: ARROBJ
  THEN
    bb:=bool(pp:BAO_arrtok)
  END;


/******************  Creating and deleting sequences **************/


  /* Reset all pointers. */
  Rename_BAO_INI =
  BEGIN
    BAO_arrtok, BAO_arrstruct,  BAO_nxt := {},{}, {}
  END;

  /* Create an array structure. */
  bb,pp <-- Rename_BAO_CRE =
  IF BAO_arrtok /= ARROBJ THEN
      ANY qq WHERE
        qq: ARROBJ - BAO_arrtok
      THEN
        BAO_arrstruct(qq):= {} ||	/* EMPTY MAP */
        BAO_nxt(qq) := u2n(lb) ||
        BAO_arrtok := BAO_arrtok \/ {qq} ||
        pp:=qq ||
        bb := TRUE
      END
  ELSE
      bb:= FALSE || pp :: ARROBJ
  END;

/* No need to kill one array kill all with INI. */

/******************  Query functions for individual sequences **********/

  /* View contents of location. */
  vv <-- Rename_BAO_VAL(pp,ii) =
  PRE
    ii : UNSIGNED &
    pp:BAO_arrtok &
    u2n(ii):dom(BAO_arrstruct(pp))
  THEN 
    vv:=BAO_arrstruct(pp)(u2n(ii))
  END;


  /* Next available storage location in `pp'. */
  nn <-- Rename_BAO_NXT(pp) =
  PRE
    pp : BAO_arrtok
  THEN
    nn := n2u(BAO_nxt(pp))
  END;


  /* Are two array contents equal (notincluding next points). */
  bb <-- Rename_BAO_EQL(ss,tt) =
  PRE
     tt : BAO_arrtok &
     ss : BAO_arrtok
  THEN
     bb := bool(BAO_arrstruct(tt) = BAO_arrstruct(ss))
  END;

/******************   Sequence Operations ***********************/

 /* Store vv in array pp at location ii and set next location to ii+1 */
 Rename_BAO_STO(pp,ii,vv) =
  PRE
    pp : BAO_arrtok &
    vv : BYTE &
    ii : UNSIGNED &
    u2n(ii) : u2n(lb)..ub
  THEN 
    BAO_arrstruct(pp)(u2n(ii)) := vv ||

    IF u2n(ii) < ub THEN
      BAO_nxt(pp) := u2n(ii) + 1 /* Next available position recorded. */
    ELSE 
      BAO_nxt(pp) := u2n(lb)	 /* Wraps around. */
    END
  END;


 /* Store vv in array pp at `next' location and inc next location. */
  Rename_BAO_STO_NXT(pp,vv) =
  PRE
    pp: BAO_arrtok &
    vv: BYTE
  THEN
    BAO_arrstruct(pp)(BAO_nxt(pp)) := vv ||

    IF BAO_nxt(pp) < ub THEN
      BAO_nxt(pp) := BAO_nxt(pp) + 1 /* Next available position recorded.*/
    ELSE 
      BAO_nxt(pp) := u2n(lb)		    /* Wraps around. */
    END
  END;


  /* Copy array pp to array qq. */
  Rename_BAO_CPY(pp,qq) =
  PRE
    pp:BAO_arrtok &
    qq:BAO_arrtok 
  THEN
    BAO_arrstruct(qq):=BAO_arrstruct(pp)
  END;


/* fill store. */
  Rename_BAO_FILL(pp: ARROBJ & vv : BYTE) =
  BEGIN
    ANY array WHERE
      array : u2n(lb)..ub +-> BYTE &
      card(array) = ub &
      ran(array) = {vv}
    THEN
      BAO_arrstruct(pp) := array
    END
         ||
    BAO_nxt(pp):= u2n(lb)		/* wraps around. */
  END

END



