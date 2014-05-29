/***
HISTORY:
 
v0.01
  VERSION:          B-Toolkit 5.0.14
  DATE:             27/01/01
***/

/*
Description: Renamable Parameterised Library variable machine
             encapsulating a READWRITE Byte-indexed array of Byte.

History :
270101 v0.01 : Created from Rename_BiBArr_File
*/

MACHINE          Rename_BiBArr(lb,ub,init_val)

/*"
The array indices are set through the instantiation of the {\em lb\/}
and {\em ub\/} parameters, which may be instantiated to any natural
numbers in the range {\em 0\/} to {\em 255\/}.

The specification array variable has the name {\em Rename\_B\/} and
pointer {\em Rename\_N_byt\/} and the initial value parameter provides
the initial value for all indices of the array.

For example importing `{\em control\_BiArr(10,20,255)\/}'
will result in the global data declaration (in the .pas module):\\[1ex]
\hspace*{3em}{\tt VAR control\_B : ARRAY [10..20] OF BYTE = 255;}\\[1ex]
\hspace*{3em}{\tt VAR control\_N_byt : BYTE = 20;}\\[1ex]
Thus the initialisation requires no translation.

This, in turn, means that the mapping into BYTE is {\em total\/}
(rather the {\em partial\/} as is the case with the corresponding
{\em File\/} machine).
"*/

CONSTRAINTS      lb>=0 & ub<=255 & lb<=ub & init_val : 0..255

SEES             Byt_TYPE, Bool_TYPE

VARIABLES        Rename_bba,  /* Map used to respresent the array storage. */
		 Rename_nxt   /* Pointer that records the next available index. */

INVARIANT        Rename_bba : lb..ub --> BYTE &  
		 Rename_nxt : lb..ub

INITIALISATION   /* Rename_bba :: lb..ub +-> BYTE ||
		 Rename_nxt := ub */

  ANY Rename_bba_init WHERE
    Rename_bba_init : lb..ub --> BYTE &
    ran(Rename_bba_init) = { n2b(init_val) }
  THEN
    Rename_bba := Rename_bba_init
  END ||
  Rename_nxt := ub

OPERATIONS

/*"
{\bf  Rename\_BiBA\_IDX}\\[.5ex]
The operation returns a boolean indicating whether or not the index
input parameter is within the bounds of the array, using the AMN {\sf
bool} operator (which returns the boolean value of its argument) - the
precondition ensures that the index input parameter has type {\em
BYTE\/}; translated as:\\
{\tt bb := (BGE(idx,lb) AND BLE(idx,ub))}
\newpage
"*/
  bb <-- Rename_BiBA_IDX(idx : BYTE) =
    BEGIN bb := bool(b2n(idx): lb..ub) END;

/*"
{\bf  Rename\_BiBA\_VAL}\\[.5ex]
The operation to retrieve a value stored at a particular array index -
the precondition ensures that the index input parameter has type {\em
BYTE\/}, is within the bounds of the array and the array at that index
has been initialised; translated as:\\
{\tt vv := prefix [idx]}
"*/
  vv <-- Rename_BiBA_VAL(idx : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) THEN
      vv := Rename_bba(b2n(idx))
    END;

/*"
{\bf  Rename\_BiBA\_STO}\\[.5ex]
The operation to store a value at a particular array index -
the precondition ensures that the index input parameter has type {\em
BYTE\/} and is within the bounds of the array, and that the value
parameter is of the right type; translated as:\\
{\tt prefix [idx] := vv}
"*/
  Rename_BiBA_STO(idx : BYTE & vv : BYTE) =
    PRE b2n(idx) : lb..ub THEN
      Rename_bba(b2n(idx)) := vv ||
      IF b2n(idx) < ub 
      THEN
        Rename_nxt := b2n(idx) + 1	/* next available position recorded. */
      ELSE 
        Rename_nxt := lb		/* wraps around. */
      END
    END;

/*"
{\bf  Rename\_BiBA\_EQ}\\[.5ex]
The operation returns a boolean indicating whether or not the value
input parameter is the same as that currently stored at the at the
array location at the index parameter, using the AMN {\sf bool}
operator (which returns the boolean value of its argument) - the
precondition ensures that the both input parameters have the right
type and that additionally the array at that index has been
initialised; if, for example, {\em VALUE\/} is instantiated to {\em
BYTE\/}, translated as:\\ {\tt bb := BEQ(prefix [idx], vv)} "*/

  bb <-- Rename_BiBA_EQ (idx : BYTE & vv : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) THEN
      bb := bool(Rename_bba(b2n(idx)) = vv)
    END;

/*-------------------  EXTRA OPERATIONS V0.02 ----------------- */

  bb <-- Rename_BiBA_IEQ (idx : BYTE & idx2 : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) & b2n(idx2) : dom(Rename_bba) THEN
      bb <-- BEQ(Rename_bba(b2n(idx)), Rename_bba(b2n(idx2)))
    END;


  bb <-- Rename_BiBA_NE (idx : BYTE & vv : BYTE) =
    PRE b2n(idx) : dom(Rename_bba)  THEN
      bb <-- BNE(Rename_bba(b2n(idx)), vv)
    END;

/* Not Equals - two indexes. */
  bb <-- Rename_BiBA_INE (idx : BYTE & idx2 : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) & b2n(idx2) : dom(Rename_bba) THEN
      bb <-- BNE(Rename_bba(b2n(idx)), Rename_bba(b2n(idx2)))
    END;

  bb <-- Rename_BiBA_GT (idx : BYTE & vv : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) THEN
      bb <-- BGT(Rename_bba(b2n(idx)), vv)
    END;

/* Greater than - two indexes. */
  bb <-- Rename_BiBA_IGT (idx : BYTE & idx2 : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) & b2n(idx2) : dom(Rename_bba) THEN
      bb <-- BGT(Rename_bba(b2n(idx)), Rename_bba(b2n(idx2)))
    END;


  bb <-- Rename_BiBA_GE (idx : BYTE & vv : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) THEN
      bb <--  BGE(Rename_bba(b2n(idx)), vv)
    END;

/* Greater than or equal to - two indexes. */
  bb <-- Rename_BiBA_IGE (idx : BYTE & idx2 : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) & b2n(idx2) : dom(Rename_bba) THEN
      bb <-- BGE(Rename_bba(b2n(idx)), Rename_bba(b2n(idx2)))
    END;


  bb <-- Rename_BiBA_LT (idx : BYTE & vv : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) THEN
      bb <-- BLT(Rename_bba(b2n(idx)), vv)
    END;

/* Less than - two indexes. */
  bb <-- Rename_BiBA_ILT (idx : BYTE & idx2 : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) & b2n(idx2) : dom(Rename_bba) THEN
      bb <-- BLT(Rename_bba(b2n(idx)), Rename_bba(b2n(idx2)))
    END;


  bb <-- Rename_BiBA_LE (idx : BYTE & vv : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) THEN
      bb <-- BLE(Rename_bba(b2n(idx)), vv)
    END;

/* Less than or equal to - two indexes. */
  bb <-- Rename_BiBA_ILE (idx : BYTE & idx2 : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) & b2n(idx2) : dom(Rename_bba) THEN
      bb <-- BLE(Rename_bba(b2n(idx)), Rename_bba(b2n(idx2)))
    END;

/* */
  Rename_BiBA_ADD (idx : BYTE & vv : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) &
        Rename_bba(b2n(idx)) + vv <= MaxByt &
        Rename_bba(b2n(idx)) + vv : BYTE
    THEN
      Rename_bba(b2n(idx)) := Rename_bba(b2n(idx)) + vv 
    END;

/* Add to indexes put result in first index. */
  Rename_BiBA_IADD (idx : BYTE & idx2 : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) & b2n(idx2) : dom(Rename_bba) &
    	Rename_bba(b2n(idx)) + Rename_bba(b2n(idx2)) : BYTE &
        Rename_bba(b2n(idx)) + Rename_bba(b2n(idx2)) <= MaxByt
    THEN
      Rename_bba(b2n(idx)) := Rename_bba(b2n(idx)) + Rename_bba(b2n(idx2)) 
    END;

  Rename_BiBA_SUB (idx : BYTE & vv : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) &
	Rename_bba(b2n(idx)) >= vv &	/* Result must be positive. */
        Rename_bba(b2n(idx)) - vv : BYTE &
        Rename_bba(b2n(idx)) - vv >= MinByt
    THEN
      Rename_bba(b2n(idx)) := Rename_bba(b2n(idx)) - vv
    END;

/* Sub to indexes put result in first index. */
  Rename_BiBA_ISUB (idx : BYTE & idx2 : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) & b2n(idx2) : dom(Rename_bba) &
	Rename_bba(b2n(idx)) >= Rename_bba(b2n(idx2)) &	/* Result must be positive. */
        Rename_bba(b2n(idx)) -  Rename_bba(b2n(idx2)) : BYTE &
        Rename_bba(b2n(idx)) -  Rename_bba(b2n(idx2)) >= MinByt
    THEN
      Rename_bba(b2n(idx)) := Rename_bba(b2n(idx)) - Rename_bba(b2n(idx2))
    END;


  Rename_BiBA_INC (idx : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) &
        Rename_bba(b2n(idx)) < MaxByt &
        Rename_bba(b2n(idx)) + n2b(1) : BYTE
    THEN
      Rename_bba(b2n(idx)) := Rename_bba(b2n(idx)) + n2b(1) 
    END;

  Rename_BiBA_DEC (idx : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) &
      Rename_bba(b2n(idx)) - n2b(1) : BYTE &
      Rename_bba(b2n(idx)) > MinByt
    THEN
      Rename_bba(b2n(idx)) := Rename_bba(b2n(idx)) - n2b(1) 
    END;

  Rename_BiBA_MUL (idx : BYTE & vv : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) &
        Rename_bba(b2n(idx)) * vv <= MaxByt &
        Rename_bba(b2n(idx)) * vv : BYTE 
    THEN
      Rename_bba(b2n(idx)) := Rename_bba(b2n(idx)) * vv 
    END;

  Rename_BiBA_DIV (idx : BYTE & vv : BYTE) =
    PRE
      vv /= n2b(0) &
      idx /= n2b(0) &
      (Rename_bba(b2n(idx)) / vv) : BYTE
    THEN
      Rename_bba(b2n(idx)) := Rename_bba(b2n(idx)) / vv 
    END;

  Rename_BiBA_REM (idx : BYTE & vv : BYTE) =
    PRE b2n(idx) : dom(Rename_bba) &
        (Rename_bba(b2n(idx)) mod vv) : BYTE &
        vv > MinByt 		/* greater than zero. */
    THEN
      Rename_bba(b2n(idx)) := Rename_bba(b2n(idx)) mod vv 
    END;

/*--------------------------- Sequence type operations. ---------------------------*/

/* store next position - append. */
  Rename_BiBA_STO_NXT(vv : BYTE) =
    BEGIN
      Rename_bba(Rename_nxt) := vv ||
      IF Rename_nxt < ub 
      THEN
        Rename_nxt := Rename_nxt + 1	/* next available position recorded. */
      ELSE 
        Rename_nxt := lb		/* wraps around. */
      END
    END;


/* fill store. */
  Rename_BiBA_FILL(vv : BYTE) =
    BEGIN
      Rename_bba : 
        (
        Rename_bba : seq(BYTE) &
        card(Rename_bba) = ub - lb + 1 &
        ran(Rename_bba) = {vv} 
        ) ||
        Rename_nxt := lb		/* wraps around. */

    END;

/* what is next position. */
nn <-- Rename_BiBA_NXT = nn := n2b(Rename_nxt)

END
