/***
HISTORY:
 
V1.0
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
***/

MACHINE           Rename_BiSeq(VALUE,maxlen)

/*"

A parameterised renamable encapsulation of a machine which can hold a
sequence; the total length of the sequence must not exceed {\em
128\/}.

The values to be stored appear as the {\em VALUE\/} parameter which
may be instantiated to any valid PASP type; the {\em maxlen\/}
parameter indicates the maximum length that the sequence may reach.

This PASP library construct comprises this specification together with
the PASP module {\em Rename\_BiSeq.param\/}, which is also renamed and
introduced into a development at the same time as the specification;
it is built on two record modules, {\em Rename\_B\_BiRcd.param\/} and
{\em Rename\_V\_BiRcd.param\/} (the former comprising two fields to
implement a linked list, and the latter comprising one field to hold
the sequence values), and two byte modules, {\em Rename\_I\/} and
{\em Rename\_T\/} (the former holding the initial sequence object
and the latter the length of the sequence).

From then on the library module is treated in exactly the same way as
a PASP code module directly translated form an AMN implementation. The
concrete variables are all provided through the above four modules.
Attributes of these variables may be set in the {\em map\/} file in the
usual way.
"*/

CONSTRAINTS       maxlen > 0 & maxlen < 128

SEES              Bool_TYPE, Byt_TYPE

VARIABLES         Rename_seq

INVARIANT

  Rename_seq : seq(VALUE) &
  size(Rename_seq) <= maxlen

INITIALISATION    Rename_seq := <> 

/*"
\newpage
"*/
OPERATIONS

/*"
{\bf Rename\_BiSeq\_FULL}\\[1ex]
Returns a boolean indicating whether or not the sequence is full:
"*/

  bb <-- Rename_BiSeq_FULL =
    BEGIN bb := bool(size(Rename_seq) = maxlen) END;

/*"
{\bf Rename\_BiSeq\_IDX}\\[1ex]
Returns a boolean indicating whether or not the index input is a
valid sequence index:
"*/

  bb <-- Rename_BiSeq_IDX(idx : BYTE) =
    BEGIN bb := bool(b2n(idx) : 1..size(Rename_seq)) END;

/*"
{\bf Rename\_BiSeq\_LEN}\\[1ex]
Returns the length of the sequence: 
"*/

  ll <-- Rename_BiSeq_LEN = BEGIN ll := n2b(size(Rename_seq)) END;

/*"
{\bf Rename\_BiSeq\_FRST}\\[1ex]
Returns the first element of the sequence, with precondition that the sequence
is non-empty: 
"*/

  vv <-- Rename_BiSeq_FRST =
    PRE size(Rename_seq) > 0 THEN
      vv := Rename_seq(1)
    END;

/*"
\newpage
{\bf Rename\_BiSeq\_LAST}\\[1ex]
Returns the last element of the sequence, with precondition that the sequence
is non-empty: 
"*/

  vv <-- Rename_BiSeq_LAST =
    PRE size(Rename_seq) > 0 THEN
      vv := Rename_seq(size(Rename_seq))
    END;

/*"
{\bf Rename\_BiSeq\_VAL}\\[1ex]
Returns the value of the {\em idx\/} element of the sequence, with
precondition that {\em idx\/} is valid:
"*/

  vv <-- Rename_BiSeq_VAL(idx : BYTE) =
    PRE b2n(idx) : 1..size(Rename_seq) THEN
      vv := Rename_seq(b2n(idx))
    END;

/*"
{\bf Rename\_BiSeq\_CLR}\\[1ex]
Empties the sequence:
"*/

  Rename_BiSeq_CLR = BEGIN Rename_seq := <> END;

/*"
{\bf Rename\_BiSeq\_FILL}\\[1ex]
Creates a sequence of length {\em len\/}, storing {\em vv\/} in
each index; the sequence must initially be empty:
"*/

  Rename_BiSeq_FILL(len : BYTE & vv : VALUE) =
    PRE
      Rename_seq = <> &
      b2n(len) : 1 .. maxlen       /* Dave */
    THEN
       Rename_seq : (
         Rename_seq : seq(VALUE) &
         size(Rename_seq) = b2n(len) &
         ran(Rename_seq) = {vv}
       )
    END;

/*"
{\bf Rename\_BiSeq\_STO}\\[1ex]
The operation to store a value at an {\em idx\/}, with precondition
that the {\em idx\/} is valid:
"*/

  Rename_BiSeq_STO(idx : BYTE & vv : VALUE) =
    PRE b2n(idx) : 1..size(Rename_seq) THEN
      Rename_seq(b2n(idx)) := vv
    END;

/*"
{\bf Rename\_BiSeq\_INS}\\[1ex]
The operation to store a value at an {\em idx\/}; all elements to the
right of this value are shifted to the right; the precondition is that
there the sequence must not be full, and {\em idx\/} must be valid and
not the equal to $1$ (it is not possible to ``insert'' at the
first location):
"*/

  Rename_BiSeq_INS(idx : BYTE & vv : VALUE) =
    PRE
      size(Rename_seq) < maxlen &
      b2n(idx) : 2..size(Rename_seq)
    THEN
      Rename_seq :=
        (Rename_seq /|\ (b2n(idx) - 1)) ^
        [ vv ] ^
        (Rename_seq \|/ (b2n(idx) - 1))
    END;


/*"
\newpage
{\bf Rename\_BiSeq\_SWP}\\[1ex]
The operation to swap two elements of the sequence; both {\em idx1\/}
and {\em idx2\/} must both be valid:
"*/

  Rename_BiSeq_SWP(idx1 : BYTE & idx2 : BYTE) =
    PRE
      b2n(idx1) : 1..size(Rename_seq) &
      b2n(idx2) : 1..size(Rename_seq)
   THEN
      Rename_seq := Rename_seq <+ (
        {b2n(idx1) |->  Rename_seq(b2n(idx2)), b2n(idx2) |->  Rename_seq(b2n(idx1))}
     )
    END;


/*"
{\bf Rename\_BiSeq\_PUSH}\\[1ex]
The operation to insert an element at the beginning of the sequence;
the sequence must not be full:
"*/

  Rename_BiSeq_PUSH(vv : VALUE) =
    PRE size(Rename_seq) < maxlen THEN
      Rename_seq := vv -> Rename_seq
    END;

/*"
{\bf Rename\_BiSeq\_APP}\\[1ex]
The operation to insert an element at the end of the sequence;
the sequence must not be full:
"*/

  Rename_BiSeq_APP(vv : VALUE) =
    PRE size(Rename_seq) < maxlen THEN
      Rename_seq := Rename_seq <- vv
    END;


/*"
\newpage
{\bf Rename\_BiSeq\_POP}\\[1ex]
The operation to remove the element at the beginning of the sequence;
the sequence must not be empty:
"*/

  Rename_BiSeq_POP =
    PRE size(Rename_seq) > 0 THEN
      Rename_seq := tail(Rename_seq)
    END;

/*"
{\bf Rename\_BiSeq\_FRONT}\\[1ex]
The operation to remove the element at the end of the sequence;
the sequence must not be empty:
"*/

  Rename_BiSeq_FRONT =
    PRE size(Rename_seq) > 0 THEN
      Rename_seq := front(Rename_seq)
    END;

/*"
{\bf Rename\_BiSeq\_DEL}\\[1ex]
The operation to delete the element at {\em idx\/}, which must
be valid:
"*/

  Rename_BiSeq_DEL(idx : BYTE) =
    PRE
      size(Rename_seq) > 0 &
      b2n(idx) : 1..size(Rename_seq)
    THEN
      Rename_seq :=
        Rename_seq /|\ b2n(idx) - 1 ^ Rename_seq \|/ b2n(idx)
    END;

/*"
\newpage
{\bf Rename\_BiSeq\_RTN}\\[1ex]
The operation to retain the first {\em idx\/} elements of the
sequence; {\em idx\/}  must be valid:
"*/

  Rename_BiSeq_RTN(idx : BYTE) =
    PRE b2n(idx) : 0..size(Rename_seq) THEN
        Rename_seq := Rename_seq /|\ b2n(idx)
    END;

/*"
{\bf Rename\_BiSeq\_RMV}\\[1ex]
The operation to remove the first {\em idx\/} elements of the
sequence; {\em idx\/}  must be valid:
"*/

  Rename_BiSeq_RMV(idx : BYTE) =
    PRE b2n(idx) : 0..size(Rename_seq) THEN
        Rename_seq := Rename_seq \|/ b2n(idx)
    END

END
