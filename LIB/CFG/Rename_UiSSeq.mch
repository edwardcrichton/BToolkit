/***
HISTORY:
 
V1.0
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
***/

MACHINE           Rename_UiSSeq(VALUE,maxlen)

/*"

A parameterised renamable encapsulation of a machine which can hold a
sequence; this is a simplified version of {\em Rename\_UiSeq\/},
enabling a simpler (more efficient implementation), resulting in
the  total length of the sequence not exceeding {\em 65535\/}.

The main differences between the two sequence machines is that
this machine features a subset of six of the the operations of
{\em Rename\_UiSeq\/}.

The values to be stored appear as the {\em VALUE\/} parameter which
may be instantiated to any valid PASP type; the {\em maxlen\/}
parameter indicates the maximum length that the sequence may reach.

This PASP library construct comprises this specification together with
the PASP module {\em Rename\_UiSSeq.param\/}, which is also renamed and
introduced into a development at the same time as the specification;
it is built on an array modules, {\em Rename\_V\_UiArr.param\/} and
a unsigned module {\em Rename\_L\_Uns.param\/} (the former holding the
values of the sequence and the letter the current length of the sequence).

From then on the library module is treated in exactly the same way as
a PASP code module directly translated form an AMN implementation. The
concrete variables are all provided through the above two modules.
Attributes of these variables may be set in the {\em map\/} file in the
usual way.
"*/

CONSTRAINTS       maxlen : 1 .. 65535

SEES              Bool_TYPE, Uns_TYPE

VARIABLES         Rename_sseq

INVARIANT

  Rename_sseq : seq(VALUE) &
  size(Rename_sseq) <= maxlen

INITIALISATION    Rename_sseq := <> 

/*"
\newpage
"*/
OPERATIONS

/*"
{\bf Rename\_UiSSeq\_LEN}\\[1ex]
Returns the length of the sequence: 
"*/

  ll <-- Rename_UiSSeq_LEN = BEGIN ll := n2u(size(Rename_sseq)) END;

/*"
{\bf Rename\_UiSSeq\_VAL}\\[1ex]
Returns the value of the {\em idx\/} element of the sequence, with
precondition that {\em idx\/} is valid:
"*/

  vv <-- Rename_UiSSeq_VAL(idx : UNSIGNED) =
    PRE u2n(idx) : 1..size(Rename_sseq) THEN
      vv := Rename_sseq(u2n(idx))
    END;

/*"
{\bf Rename\_UiSSeq\_FILL}\\[1ex]
Creates a sequence of length {\em len\/}, storing {\em vv\/} in
each index; the sequence must initially be empty:
"*/

  Rename_UiSSeq_FILL(vv : VALUE) =
    BEGIN
       Rename_sseq : (
         Rename_sseq : seq(VALUE) &
         card(Rename_sseq) = maxlen &
         ran(Rename_sseq) = {vv}
       )
    END;

/*"
\newpage
{\bf Rename\_UiSSeq\_CHG}\\[1ex]
The operation to store a value at an {\em idx\/}, with precondition
that the {\em idx\/} is valid:
"*/

  Rename_UiSSeq_CHG(idx : UNSIGNED & vv : VALUE) =
    PRE u2n(idx) : 1..size(Rename_sseq) THEN
      Rename_sseq(u2n(idx)) := vv
    END;

/*"
{\bf Rename\_UiSSeq\_APP}\\[1ex]
The operation to insert an element at the end of the sequence;
the sequence must not be full:
"*/

  Rename_UiSSeq_APP(vv : VALUE) =
    PRE size(Rename_sseq) < maxlen THEN
      Rename_sseq := Rename_sseq <- vv
    END;

/*"
{\bf Rename\_UiSSeq\_KEEP}\\[1ex]
The operation to retain the first {\em idx\/} elements of the
sequence; {\em idx\/}  must be valid:
"*/

  Rename_UiSSeq_KEEP(idx : UNSIGNED) =
    PRE u2n(idx) : 0..size(Rename_sseq) THEN
        Rename_sseq := Rename_sseq /|\ u2n(idx)
    END

END
/*"
\newpage
"*/
