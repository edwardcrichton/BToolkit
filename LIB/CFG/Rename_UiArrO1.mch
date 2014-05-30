/***
HISTORY:
 
V1.0
  VERSION:          B-Toolkit Beta 4.32
  DATE:             18/02/99
***/

/*
Description: Machine adapted from Rename_UiArrO1.
This is a single object machine.

History :
180299 v0.01 : Created.
*/

MACHINE             Rename_UiArrO1(ub,init_elem)	
/* ub - the lenght of the object */	

CONSTRAINTS         1<=ub & ub<=65535 & init_elem <= 255
  
SEES                Bool_TYPE, PASP_TYPE

VARIABLES

  Rename_UiAO1_arr,	/* the single array */
  Rename_UiAO1_nxt	/* array pointer */

INVARIANT

  Rename_UiAO1_arr : 1..ub --> BYTE &
  Rename_UiAO1_nxt : 1..ub

INITIALISATION

  BEGIN
    ANY array WHERE
      array : 1..ub --> BYTE &
      ran(array) = {n2b(init_elem)}
    THEN
      Rename_UiAO1_arr := array
    END ||
    Rename_UiAO1_nxt := 1		/* wraps around. */
  END

OPERATIONS

  /******************  Reset **************/

  /* Reset */
  Rename_UiAO1_RST =
    BEGIN Rename_UiAO1_arr :: 1..ub --> BYTE || Rename_UiAO1_nxt := 1 END;

  /******************  Query functions **********/

  /* View contents of location. */
  vv <-- Rename_UiAO1_VAL(ii : UNSIGNED) =
    PRE
      u2n(ii) : 1..ub
    THEN
      vv := Rename_UiAO1_arr(u2n(ii))
    END;

  /* Next available storage location */
  nn <-- Rename_UiAO1_NXT =
    BEGIN
      nn := n2u(Rename_UiAO1_nxt)
    END;

 /******************  Modify functions ***********************/

  /* Store vv at location ii and set next location to ii+1 */
  Rename_UiAO1_STO(ii : UNSIGNED & vv : BYTE) =
    PRE
     u2n(ii) : 1..ub
   THEN 
     Rename_UiAO1_arr(u2n(ii)) := vv ||
     IF u2n(ii) < ub THEN
       Rename_UiAO1_nxt := u2n(ii) + 1	/* Next available position recorded. */
     ELSE 
       Rename_UiAO1_nxt := 1		/* Wraps around. */
     END
   END;

  /* Store vv at `next' location and inc next location. */
  Rename_UiAO1_STO_NXT(vv :BYTE) =
    BEGIN
      Rename_UiAO1_arr(Rename_UiAO1_nxt) := vv ||
      IF Rename_UiAO1_nxt < ub THEN
        Rename_UiAO1_nxt := Rename_UiAO1_nxt + 1	/* Next available position recorded.*/
      ELSE 
        Rename_UiAO1_nxt := 1				/* Wraps around. */
      END
    END;

  /* fill store. */
  Rename_UiAO1_FILL(vv : BYTE) =
    BEGIN
      ANY array WHERE
        array : 1..ub --> BYTE &
        ran(array) = {vv}
      THEN
        Rename_UiAO1_arr := array
      END ||
      Rename_UiAO1_nxt := 1		/* wraps around. */
    END

END
