/***
HISTORY:
 
V1.0
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
***/

MACHINE           Rename_UiSeq(VALUE,maxlen)

/*"

A parameterised renamable encapsulation of a machine which can hold a
sequence; the total length of the sequence must not exceed {\em
32768\/}.

The values to be stored appear as the {\em VALUE\/} parameter which
may be instantiated to any valid PASP type; the {\em maxlen\/}
parameter indicates the maximum length that the sequence may reach.

This PASP library construct comprises this specification together with
the PASP module {\em Rename\_UiSeq.param\/}, which is also renamed and
introduced into a development at the same time as the specification;
it is built on two record modules, {\em Rename\_B\_UiRcd.param\/} and
{\em Rename\_V\_UiRcd.param\/} (the former comprising two fields to
implement a linked list, and the latter comprising one field to hold
the sequence values), and two unsigned modules, {\em Rename\_I\/} and
{\em Rename\_T\/} (the former holding the initial sequence object
and the latter the length of the sequence).

From then on the library module is treated in exactly the same way as
a PASP code module directly translated form an AMN implementation. The
concrete variables are all provided through the above four modules.
Attributes of these variables may be set in the {\em map\/} file in the
usual way.
"*/

CONSTRAINTS       maxlen > 0 & maxlen < 32768

SEES              Bool_TYPE, Uns_TYPE

VARIABLES         Rename_seq

INVARIANT

  Rename_seq : seq(VALUE) &
  size(Rename_seq) <= maxlen

INITIALISATION    Rename_seq := <> 

OPERATIONS

/*"
{\bf Rename\_UiSeq\_FULL}\\[1ex]
Returns a boolean indicating whether or not the sequence is full:
"*/

  bb <-- Rename_UiSeq_FULL =
    BEGIN bb := bool(size(Rename_seq) = maxlen) END;

/*"
{\bf Rename\_UiSeq\_IDX}\\[1ex]
Returns a boolean indicating whether or not the index input is a
valid sequence index:
"*/

  bb <-- Rename_UiSeq_IDX(idx : UNSIGNED) =
    BEGIN bb := bool(u2n(idx) : 1..size(Rename_seq)) END;

/*"
{\bf Rename\_UiSeq\_LEN}\\[1ex]
Returns the length of the sequence: 
"*/

  ll <-- Rename_UiSeq_LEN = BEGIN ll := n2u(size(Rename_seq)) END;

/*"
{\bf Rename\_UiSeq\_FRST}\\[1ex]
Returns the first element of the sequence, with precondition that the sequence
is non-empty: 
"*/

  vv <-- Rename_UiSeq_FRST =
    PRE size(Rename_seq) > 0 THEN
      vv := Rename_seq(1)
    END;

/*"
{\bf Rename\_UiSeq\_LAST}\\[1ex]
Returns the last element of the sequence, with precondition that the sequence
is non-empty: 
"*/

  vv <-- Rename_UiSeq_LAST =
    PRE size(Rename_seq) > 0 THEN
      vv := Rename_seq(size(Rename_seq))
    END;

/*"
\newpage
{\bf Rename\_UiSeq\_VAL}\\[1ex]
Returns the value of the {\em idx\/} element of the sequence, with
precondition that {\em idx\/} is valid:
"*/

  vv <-- Rename_UiSeq_VAL(idx : UNSIGNED) =
    PRE u2n(idx) : 1..size(Rename_seq) THEN
      vv := Rename_seq(u2n(idx))
    END;

/*"
{\bf Rename\_UiSeq\_CLR}\\[1ex]
Empties the sequence:
"*/

  Rename_UiSeq_CLR = BEGIN Rename_seq := <> END;

/*"
{\bf Rename\_UiSeq\_FILL}\\[1ex]
Creates a sequence of length {\em len\/}, storing {\em vv\/} in
each index; the sequence must initially be empty:
"*/

  Rename_UiSeq_FILL(len : UNSIGNED & vv : VALUE) =
    PRE
      Rename_seq = <> &
      u2n(len) : 1 .. 32767
    THEN
       Rename_seq : (
         Rename_seq : seq(VALUE) &
         card(Rename_seq) = u2n(len) &
         ran(Rename_seq) = {vv}
       )
    END;

/*"
\newpage
{\bf Rename\_UiSeq\_STO}\\[1ex]
The operation to store a value at an {\em idx\/}, with precondition
that the {\em idx\/} is valid:
"*/

  Rename_UiSeq_STO(idx : UNSIGNED & vv : VALUE) =
    PRE u2n(idx) : 1..size(Rename_seq) THEN
      Rename_seq(u2n(idx)) := vv
    END;

/*"
{\bf Rename\_UiSeq\_INS}\\[1ex]
The operation to store a value at an {\em idx\/}; all elements to the
right of this value are shifted to the right; the precondition is that
there the sequence must not be full, and {\em idx\/} must be valid and
not the equal to $1$ (it is not possible to ``insert'' at the
first location):
"*/

  Rename_UiSeq_INS(idx : UNSIGNED & vv : VALUE) =
    PRE
      size(Rename_seq) < maxlen &
      u2n(idx) : 2..size(Rename_seq)
    THEN
      Rename_seq :=
        Rename_seq /|\ (u2n(idx) - 1) ^ [ vv ] ^ Rename_seq \|/ (u2n(idx) - 1)
    END;


/*"
\newpage
{\bf Rename\_UiSeq\_SWP}\\[1ex]
The operation to swap two elements of the sequence; both {\em idx1\/}
and {\em idx2\/} must both be valid:
"*/

  Rename_UiSeq_SWP(idx1 : UNSIGNED & idx2 : UNSIGNED) =
    PRE
      u2n(idx1) : 1..size(Rename_seq) &
      u2n(idx2) : 1..size(Rename_seq)
    THEN
      Rename_seq := Rename_seq <+ (
        {u2n(idx1) |->  Rename_seq(u2n(idx2)), u2n(idx2) |->  Rename_seq(u2n(idx1))}
     )
    END;


/*"
{\bf Rename\_UiSeq\_PUSH}\\[1ex]
The operation to insert an element at the beginning of the sequence;
the sequence must not be full:
"*/

  Rename_UiSeq_PUSH(vv : VALUE) =
    PRE size(Rename_seq) < maxlen THEN
      Rename_seq := vv -> Rename_seq
    END;

/*"
{\bf Rename\_UiSeq\_APP}\\[1ex]
The operation to insert an element at the end of the sequence;
the sequence must not be full:
"*/

  Rename_UiSeq_APP(vv : VALUE) =
    PRE size(Rename_seq) < maxlen THEN
      Rename_seq := Rename_seq <- vv
    END;


/*"
\newpage
{\bf Rename\_UiSeq\_POP}\\[1ex]
The operation to remove the element at the beginning of the sequence;
the sequence must not be empty:
"*/

  Rename_UiSeq_POP =
    PRE size(Rename_seq) > 0 THEN
      Rename_seq := tail(Rename_seq)
    END;

/*"
{\bf Rename\_UiSeq\_FRONT}\\[1ex]
The operation to remove the element at the end of the sequence;
the sequence must not be empty:
"*/

  Rename_UiSeq_FRONT =
    PRE size(Rename_seq) > 0 THEN
      Rename_seq := front(Rename_seq)
    END;

/*"
{\bf Rename\_UiSeq\_DEL}\\[1ex]
The operation to delete the element at {\em idx\/}, which must
be valid:
"*/

  Rename_UiSeq_DEL(idx : UNSIGNED) =
    PRE
      size(Rename_seq) > 0 &
      u2n(idx) : 1..size(Rename_seq)
    THEN
      Rename_seq :=
        Rename_seq /|\ u2n(idx) - 1 ^ Rename_seq \|/ u2n(idx)
    END;

/*"
\newpage
{\bf Rename\_UiSeq\_RTN}\\[1ex]
The operation to retain the first {\em idx\/} elements of the
sequence; {\em idx\/}  must be valid:
"*/

  Rename_UiSeq_RTN(idx : UNSIGNED) =
    PRE u2n(idx) : 0..size(Rename_seq) THEN
        Rename_seq := Rename_seq /|\ u2n(idx)
    END;

/*"
{\bf Rename\_UiSeq\_RMV}\\[1ex]
The operation to remove the first {\em idx\/} elements of the
sequence; {\em idx\/}  must be valid:
"*/

  Rename_UiSeq_RMV(idx : UNSIGNED) =
    PRE u2n(idx) : 0..size(Rename_seq) THEN
        Rename_seq := Rename_seq \|/ u2n(idx)
    END

END
