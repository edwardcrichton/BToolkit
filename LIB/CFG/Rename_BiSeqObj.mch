/***
HISTORY:
 
V1.0
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
***/

MACHINE           Rename_BiSeqObj(VALUE,maxobj,maxmem)

/*"

A parameterised renamable encapsulation of a machine which can hold a
set of sequences; the total length of the sequence must not exceed {\em
128\/}.

The values to be stored appear as the {\em VALUE\/} parameter which
may be instantiated to any valid PASP type; the total number of sequences
is given by the {\em maxobj\/} parameter, and the sum of the lengths of
all sequences is given by the {\em maxmem\/} parameter.

This PASP library construct comprises this specification together with
the PASP module {\em Rename\_BiSeqObj.param\/}, which is also renamed
and introduced into a development at the same time as the
specification; it is built on two record modules, {\em
Rename\_B\_BiRcd.param\/} and {\em Rename\_V\_BiRcd.param\/} (the
former comprising two fields to implement a linked list, and the
latter comprising one field to hold the sequence values), three array
modules, {\em Rename\_I\_BiArr.param\/}, {\em
Rename\_S\_BiArr.param\/} and {\em Rename\_H\_BiArr.param\/} (the
first holding the initial record identifier for each sequence, the
second the size of each sequence and the last the unallocated sequence
objects, and a byte modules, {\em Rename\_TOT\/} holding the current
total of sequence objects.

From then on the library module is treated in exactly the same way as
a PASP code module directly translated form an AMN implementation. The
concrete variables are all provided through the imported modules, and
attributes of these variables may be set in the {\em map\/} file in
the usual way.

The operations provided in this machine are those of the single sequence
machine {\em Rename\_BiSeq\/} together with operations to create and kill
a sequence object, query operations on whether the object and memory store
are full and whether a sequence object is valid, and operations to copy
and append one sequence to another.

"*/

CONSTRAINTS       maxobj : 1 .. 127 & maxmem : 1 .. 127

SEES              Bool_TYPE, Byt_TYPE

SETS              Rename_SEQOBJ

PROPERTIES        card(Rename_SEQOBJ) = maxobj

VARIABLES         Rename_seqobj, Rename_seqfun, Rename_seqmem

INVARIANT

  Rename_seqobj <: Rename_SEQOBJ &
  Rename_seqfun : Rename_seqobj --> seq(VALUE) &
  Rename_seqmem = SIGMA ss.(ss : Rename_seqobj| size(Rename_seqfun(ss))) &
  Rename_seqmem <= maxmem   
 
INITIALISATION

  Rename_seqobj, Rename_seqfun, Rename_seqmem := {},{}, 0

OPERATIONS

/*"
{\bf Rename\_BiSeqObj\_FULL\_MEM}\\[1ex]
Returns a boolean indicating whether or not the memory is full:
"*/

  bb <-- Rename_BiSeqObj_FULL_MEM =
    BEGIN bb := bool(Rename_seqmem = maxmem) END;

/*"
{\bf Rename\_BiSeqObj\_FULL\_OBJ}\\[1ex]
Returns a boolean indicating whether or not the object store is full:
"*/

  bb <-- Rename_BiSeqObj_FULL_OBJ =
    BEGIN bb := bool(Rename_seqobj =  Rename_SEQOBJ) END;

/*"
{\bf Rename\_BiSeqObj\_CRE}\\[1ex]
The operation to create a(n empty) sequence; a unique token is
returned through which the sequence object may subsequently be
referenced:
"*/

  obj <-- Rename_BiSeqObj_CRE =
    PRE Rename_seqobj /= Rename_SEQOBJ THEN
      ANY newobj WHERE newobj : Rename_SEQOBJ - Rename_seqobj THEN
        Rename_seqobj := Rename_seqobj \/ {newobj} ||
        Rename_seqfun(newobj) := <> ||
        obj := newobj
      END
    END;

/*"
\newpage
{\bf Rename\_BiSeqObj\_KILL}\\[1ex]
The operation to kill a sequence; the token input must have previously
been returned by {\em Rename\_BiSeqObj\_CRE\/}, and must be currently valid:
"*/

  Rename_BiSeqObj_KILL(obj : Rename_SEQOBJ) =
    PRE  obj : Rename_seqobj THEN
      Rename_seqfun :=  {obj} <<| Rename_seqfun ||
      Rename_seqobj := Rename_seqobj - {obj} ||
      Rename_seqmem := Rename_seqmem - size(Rename_seqfun(obj))
    END;

/*"
{\bf Rename\_BiSeqObj\_VLD\_OBJ}\\[1ex]
Returns a boolean indicating whether or not the input token is a
valid sequence (i.e.\ currently in use):
"*/

  bb <-- Rename_BiSeqObj_VLD_OBJ(obj : Rename_SEQOBJ) =
    BEGIN bb := bool(obj : Rename_seqobj) END;

/*"
{\bf Rename\_BiSeqObj\_VLD\_IDX}\\[1ex]
Returns a boolean indicating whether or not the index input is a
valid sequence index for the sequence object input:
"*/

  bb <-- Rename_BiSeqObj_VLD_IDX(obj : Rename_SEQOBJ & idx : BYTE) =
    BEGIN
      bb := bool(obj : Rename_seqobj & b2n(idx) : 1..size(Rename_seqfun(obj)))
    END;

/*"
{\bf Rename\_BiSeqObj\_OBJ\_TOT}\\[1ex]
Returns the number of sequences currently valid:
"*/

  tt <-- Rename_BiSeqObj_OBJ_TOT =
    BEGIN tt := n2b(card(Rename_seqobj)) END;

/*"
{\bf Rename\_BiSeqObj\_LEN}\\[1ex]
Returns the length of the (valid) sequence input: 
"*/

  ll <-- Rename_BiSeqObj_LEN(obj : Rename_SEQOBJ) =
    PRE obj : Rename_seqobj THEN ll := n2b(size(Rename_seqfun(obj))) END;

/*"
{\bf Rename\_BiSeqObj\_FRST}\\[1ex]
Returns the first element of the sequence input, with precondition
that the sequence is valid and non-empty: 
"*/

  vv <-- Rename_BiSeqObj_FRST(obj : Rename_SEQOBJ) =
    PRE obj : Rename_seqobj & size(Rename_seqfun(obj)) > 0 THEN
      vv := Rename_seqfun(obj)(1)
    END;

/*"
{\bf Rename\_BiSeqObj\_LAST}\\[1ex]
Returns the last element of the sequence input, with precondition
that the sequence is valid and non-empty: 
"*/

  vv <-- Rename_BiSeqObj_LAST(obj : Rename_SEQOBJ) =
    PRE obj : Rename_seqobj & size(Rename_seqfun(obj)) > 0 THEN
      vv := Rename_seqfun(obj)(size(Rename_seqfun(obj)))
    END;

/*"
{\bf Rename\_BiSeqObj\_VAL}\\[1ex]
Returns the value of the {\em idx\/} element of the sequence input, with
precondition that {\em obj\/} and {\em idx\/} are both valid:
"*/

  vv <-- Rename_BiSeqObj_VAL(obj : Rename_SEQOBJ & idx : BYTE) =
    PRE obj : Rename_seqobj & b2n(idx) : 1..size(Rename_seqfun(obj)) THEN
      vv := Rename_seqfun(obj)(b2n(idx))
    END;

/*"
{\bf Rename\_BiSeqObj\_CLR}\\[1ex]
Empties the (valid) sequence input:
"*/
  Rename_BiSeqObj_CLR(obj : Rename_SEQOBJ) =
   PRE obj : Rename_seqobj THEN
     Rename_seqfun(obj) := <> ||
      Rename_seqmem := Rename_seqmem - size(Rename_seqfun(obj))
   END;

/*"
{\bf Rename\_BiSeqObj\_STO}\\[1ex]
The operation to store a value at an {\em idx\/} of the sequence
input, with precondition that the {\em obj\/} {\em idx\/} are valid:
"*/

  Rename_BiSeqObj_STO(obj : Rename_SEQOBJ & idx : BYTE & vv : VALUE) =
    PRE obj : Rename_seqobj & b2n(idx) : 1..size(Rename_seqfun(obj)) THEN
      Rename_seqfun(obj)(b2n(idx)) := vv
    END;

/*"
{\bf Rename\_BiSeqObj\_INS}\\[1ex]
The operation to store a value at an {\em idx\/} of the (valid)
sequence input; all elements to the right of this value are shifted to
the right; the precondition is that there the sequence must not be
full, and {\em idx\/} must be valid and not the equal to $1$ (it is
not possible to ``insert'' at the first location): "*/

  Rename_BiSeqObj_INS(obj : Rename_SEQOBJ & idx : BYTE & vv : VALUE) =
    PRE
      obj : Rename_seqobj &
      Rename_seqmem < maxmem &
      b2n(idx) : 2..size(Rename_seqfun(obj))
    THEN
      Rename_seqfun(obj) :=
        (Rename_seqfun(obj) /|\ (b2n(idx) - 1)) ^
        [ vv ] ^
        (Rename_seqfun(obj) \|/ (b2n(idx) - 1)) ||
      Rename_seqmem := Rename_seqmem + 1
    END;

/*"
{\bf Rename\_BiSeqObj\_SWP}\\[1ex]
The operation to swap two elements of the sequence input;
{\em obj\/}, {\em idx1\/} and {\em idx2\/} must all be valid:
"*/

  Rename_BiSeqObj_SWP(obj : Rename_SEQOBJ & idx1 : BYTE & idx2 : BYTE) =
    PRE
      obj : Rename_seqobj &
      b2n(idx1) : 1..size(Rename_seqfun(obj)) &
      b2n(idx2) : 1..size(Rename_seqfun(obj))
    THEN
      Rename_seqfun(obj) := Rename_seqfun(obj) <+ (
        {b2n(idx1) |->  Rename_seqfun(obj)(b2n(idx2)),
                    b2n(idx2) |->  Rename_seqfun(obj)(b2n(idx1))}
     )
    END;

/*"
{\bf Rename\_BiSeqObj\_PUSH}\\[1ex]
The operation to insert an element at the beginning of the (valid) sequence;
the sequence must not be full:
"*/

  Rename_BiSeqObj_PUSH(obj : Rename_SEQOBJ & vv : VALUE) =
    PRE obj : Rename_seqobj & Rename_seqmem < maxmem THEN
      Rename_seqfun(obj) := vv -> Rename_seqfun(obj) ||
      Rename_seqmem := Rename_seqmem + 1
    END;

/*"
{\bf Rename\_BiSeqObj\_APP}\\[1ex]
The operation to insert an element at the end of the (valid) sequence;
the sequence must not be full:
"*/

  Rename_BiSeqObj_APP(obj : Rename_SEQOBJ & vv : VALUE) =
    PRE obj : Rename_seqobj & Rename_seqmem < maxmem THEN
      Rename_seqfun(obj) := Rename_seqfun(obj) <- vv ||
      Rename_seqmem := Rename_seqmem + 1
    END;

/*"
\newpage
{\bf Rename\_BiSeqObj\_POP}\\[1ex]
The operation to remove the element at the beginning of the (valid)
sequence; the sequence must not be empty:
"*/

  Rename_BiSeqObj_POP(obj : Rename_SEQOBJ) =
    PRE obj : Rename_seqobj & size(Rename_seqfun(obj)) > 0 THEN
      Rename_seqfun(obj) := tail(Rename_seqfun(obj)) ||
      Rename_seqmem := Rename_seqmem - 1
    END;

/*"
{\bf Rename\_BiSeqObj\_FRONT}\\[1ex]
The operation to remove the element at the end of the(valid)
sequence; the sequence must not be empty:
"*/

  Rename_BiSeqObj_FRONT(obj : Rename_SEQOBJ) =
    PRE obj : Rename_seqobj & size(Rename_seqfun(obj)) > 0 THEN
      Rename_seqfun(obj) := front(Rename_seqfun(obj)) ||
      Rename_seqmem := Rename_seqmem - 1
    END;

/*"
{\bf Rename\_BiSeqObj\_DEL}\\[1ex]
The operation to delete the element of the sequence input at
{\em idx\/}; {\em obj\/} and {\em idx\/} must be valid:
"*/

  Rename_BiSeqObj_DEL(obj : Rename_SEQOBJ & idx : BYTE) =
    PRE
      obj : Rename_seqobj & 
      size(Rename_seqfun(obj)) > 0 &
      b2n(idx) : 1..size(Rename_seqfun(obj))
    THEN
      Rename_seqfun(obj) :=
        Rename_seqfun(obj) /|\ (b2n(idx) - 1) ^ (Rename_seqfun(obj) \|/ b2n(idx)) ||
      Rename_seqmem := Rename_seqmem - 1
    END;

/*"
\newpage
{\bf Rename\_BiSeqObj\_RTN}\\[1ex]
The operation to retain the first {\em idx\/} elements of the
sequence input; {\em obj\/} and {\em idx\/} must be valid:
"*/

  Rename_BiSeqObj_RTN(obj : Rename_SEQOBJ & idx : BYTE) =
    PRE
      obj : Rename_seqobj & 
      b2n(idx) : 1..size(Rename_seqfun(obj))
    THEN
      Rename_seqfun(obj) := Rename_seqfun(obj) /|\ b2n(idx) ||
      Rename_seqmem := Rename_seqmem + size(Rename_seqfun(obj)) - b2n(idx)
    END;

/*"
{\bf Rename\_BiSeqObj\_RMV}\\[1ex]
The operation to remove the first {\em idx\/} elements of the
sequence input; {\em obj\/} and {\em idx\/} must be valid:
"*/

  Rename_BiSeqObj_RMV(obj : Rename_SEQOBJ & idx : BYTE) =
    PRE
      obj : Rename_seqobj & 
      b2n(idx) : 1..size(Rename_seqfun(obj))
    THEN
      Rename_seqfun(obj) := Rename_seqfun(obj) \|/ b2n(idx) ||
      Rename_seqmem := Rename_seqmem - size(Rename_seqfun(obj)) + b2n(idx)
    END;

/*"
\newpage
{\bf Rename\_BiSeqObj\_CPY}\\[1ex]
Copies a sequence into another sequence; both must be valid, with
the second sequence empty, and sufficient memory must exist:
"*/

  Rename_BiSeqObj_CPY(obj1 : Rename_SEQOBJ & obj2 : Rename_SEQOBJ) =
    PRE
      obj1 : Rename_seqobj & 
      obj2 : Rename_seqobj &
      size(Rename_seqfun(obj2)) = 0 &
      Rename_seqmem + size(Rename_seqfun(obj1)) <= maxmem
    THEN
      Rename_seqfun(obj2) := Rename_seqfun(obj1) ||
      Rename_seqmem :=  Rename_seqmem + size(Rename_seqfun(obj1))
    END;

/*"
{\bf Rename\_BiSeqObj\_CAT}\\[1ex]
Concatenates a sequence onto the end of another sequence; both
must be valid, and sufficient memory must exist:
"*/

  Rename_BiSeqObj_CAT(obj1 : Rename_SEQOBJ & obj2 : Rename_SEQOBJ) =
    PRE
      obj1 : Rename_seqobj & 
      obj2 : Rename_seqobj &
      Rename_seqmem + size(Rename_seqfun(obj1)) <= maxmem
    THEN
      Rename_seqfun(obj2)  :=  Rename_seqfun(obj2) ^ Rename_seqfun(obj1) ||
      Rename_seqmem :=  Rename_seqmem + size(Rename_seqfun(obj1))
    END

END
