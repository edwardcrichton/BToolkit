/***
HISTORY:
 
V1.0
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
***/

MACHINE           Rename_BiSSeq(VALUE,maxlen)

/*"

A parameterised renamable encapsulation of a machine which can hold a
sequence; this is a simplified version of {\em Rename\_BiSeq\/},
enabling a simpler (more efficient implementation), resulting in
the  total length of the sequence not exceeding {\em 255\/}.

The main differences between the two sequence machines is that
this machine features a subset of six of the the operations of
{\em Rename\_BiSeq\/}.

The values to be stored appear as the {\em VALUE\/} parameter which
may be instantiated to any valid PASP type; the {\em maxlen\/}
parameter indicates the maximum length that the sequence may reach.

This PASP library construct comprises this specification together with
the PASP module {\em Rename\_BiSSeq.param\/}, which is also renamed and
introduced into a development at the same time as the specification;
it is built on an array modules, {\em Rename\_V\_BiArr.param\/} and
a byte module {\em Rename\_L\_Byt.param\/} (the former holding the
values of the sequence and the letter the current length of the sequence).

From then on the library module is treated in exactly the same way as
a PASP code module directly translated form an AMN implementation. The
concrete variables are all provided through the above two modules.
Attributes of these variables may be set in the {\em map\/} file in the
usual way.
"*/

CONSTRAINTS       maxlen : 1 .. 255

SEES              Bool_TYPE, Byt_TYPE

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
{\bf Rename\_BiSSeq\_LEN}\\[1ex]
Returns the length of the sequence: 
"*/

  ll <-- Rename_BiSSeq_LEN = BEGIN ll := n2b(size(Rename_sseq)) END;

/*"
{\bf Rename\_BiSSeq\_VAL}\\[1ex]
Returns the value of the {\em idx\/} element of the sequence, with
precondition that {\em idx\/} is valid:
"*/

  vv <-- Rename_BiSSeq_VAL(idx : BYTE) =
    PRE b2n(idx) : 1..size(Rename_sseq) THEN
      vv := Rename_sseq(b2n(idx))
    END;

/*"
{\bf Rename\_BiSSeq\_FILL}\\[1ex]
Creates a sequence of length {\em len\/}, storing {\em vv\/} in
each index; the sequence must initially be empty:
"*/

  Rename_BiSSeq_FILL(vv : VALUE) =
    PRE
      size(Rename_sseq) = 0
    THEN
       Rename_sseq : (
         Rename_sseq : seq(VALUE) &
         card(Rename_sseq) = maxlen &
         ran(Rename_sseq) = {vv}
       )
    END;

/*"
\newpage
{\bf Rename\_BiSSeq\_CHG}\\[1ex]
The operation to store a value at an {\em idx\/}, with precondition
that the {\em idx\/} is valid:
"*/

  Rename_BiSSeq_CHG(idx : BYTE & vv : VALUE) =
    PRE b2n(idx) : 1..size(Rename_sseq) THEN
      Rename_sseq(b2n(idx)) := vv
    END;

/*"
{\bf Rename\_BiSSeq\_APP}\\[1ex]
The operation to insert an element at the end of the sequence;
the sequence must not be full:
"*/

  Rename_BiSSeq_APP(vv : VALUE) =
    PRE size(Rename_sseq) < maxlen THEN
      Rename_sseq := Rename_sseq <- vv
    END;

/*"
{\bf Rename\_BiSSeq\_KEEP}\\[1ex]
The operation to retain the first {\em idx\/} elements of the
sequence; {\em idx\/}  must be valid:
"*/

  Rename_BiSSeq_KEEP(idx : BYTE) =
    PRE b2n(idx) : 0..size(Rename_sseq) THEN
        Rename_sseq := Rename_sseq /|\ b2n(idx)
    END

END
/*"
\newpage
"*/
