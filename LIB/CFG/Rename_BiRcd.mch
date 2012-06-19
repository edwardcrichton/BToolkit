/***
HISTORY:
 
V1.0
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
***/

MACHINE           Rename_BiRcd(VALUE,numfld,maxrcd)

/*"
A parameterised renamable encapsulation of a machine which can
hold records; the total number of data entries (i.e.\ the product of
fields and records) must not exceed {\em MaxByt\/}.

The values to be stored in each record field appear as the {\em
VALUE\/} parameter which may be instantiated to any valid PASP type;
the {\em numfld\/} parameter indicates the number of fields that each
record contains; the {\em maxrcd\/} parameter indicates the maximum
number of records required at any one time.

This PASP library construct comprises this specification together with
the PASP module {\em Rename\_BiRcd.param\/}, which is also renamed and
introduced into a development at the same time as the
specification. From then on the library module is treated in exactly
the same way as a PASP code module directly translated form an AMN
implementation. The three concrete variables {\em Rename\_RCD\_ARR\/},
{\em Rename\_RCD\_HEAP\_ARR\/} and {\em Rename\_RCD\_TOT\_byt\/}
(renamed) will appear in the {\em map} file so that attributes can be
set if required.

Importing, for example, `{\em control\_BiRcd(UNSIGNED,3,50)\/}' will
result in  the global data declaration in {\em Rename\_BiRcd.noatt\/}:
\begin{verbatim}
    VAR control_RCD_ARR                  : ARRAY[0..149] OF UNSIGNED;
    VAR control_RCD_HEAP_ARR             : ARRAY[0..49] OF BYTE;
    VAR control_RCD_TOT_byt              : BYTE;
\end{verbatim}

An operation to reset the machine {\em Rename\_BiRcd\_RST\/} is
provided, together with the three enquiry operations
{\em Rename\_BiRcd\_IDX\/}, {\em Rename\_BiRcd\_FULL\/},
{\em Rename\_BiRcd\_VLD\/}, operations to create and
kill a record {\em Rename\_BiRcd\_CRE\/} and
{\em Rename\_BiRcd\_KILL\/}, and operations to store and
retrieve a value {\em Rename\_BiRcd\_STO\/} and
{\em Rename\_BiRcd\_VAL\/}. 
"*/

CONSTRAINTS       numfld > 0 & maxrcd> 0 & numfld * maxrcd < 256

SEES              Bool_TYPE, Byt_TYPE

SETS

/*"
{\em Rename\_BiRcd\/} is the abstract set from which all records
will be taken.
"*/

  Rename_BiRcd

PROPERTIES        card(Rename_BiRcd) = maxrcd

VARIABLES

  Rename_rcd, Rename_rcd_fnc

/*"
\newpage
"*/
INVARIANT

/*"
{\em Rename\_rcd\/} is the set of record identifiers currently in use,
and {\em Rename\_rcd\_fnc\/} is the total function mapping each into a
record comprising {\em numfld\/} values.
"*/

  Rename_rcd <: Rename_BiRcd &
  Rename_rcd_fnc: Rename_rcd --> (1..numfld +-> VALUE)

INITIALISATION

/*"
In line with current PASP programming practice, the initialisation
nondeterministically sets the two variables:
"*/

/*
  Rename_rcd : (Rename_rcd <: Rename_BiRcd) ||
  Rename_rcd_fnc :: Rename_rcd --> (1..numfld +-> VALUE)
*/
  ANY Rename_rcdx, Rename_rcd_fncx WHERE
    Rename_rcdx <: Rename_BiRcd &
    Rename_rcd_fncx: Rename_rcdx --> (1..numfld +-> VALUE)
  THEN
    Rename_rcd, Rename_rcd_fnc :=  Rename_rcdx, Rename_rcd_fncx
  END

OPERATIONS


/*"
{\bf Rename\_BiRcd\_RST}\\[1ex]
Resets the machine so that the current number of records is $0$:
"*/

  Rename_BiRcd_RST =
    BEGIN Rename_rcd := {} || Rename_rcd_fnc := {} END;

/*"
{\bf Rename\_BiRcd\_IDX}\\[1ex]
Returns a boolean indicating whether or not the index input is a
valid field number:
"*/

  bb <-- Rename_BiRcd_IDX(idx : BYTE) =
    BEGIN bb := bool(b2n(idx) : 0..numfld) END;

/*"
\newpage
{\bf Rename\_BiRcd\_FULL}\\[1ex]
Returns a boolean indicating whether or not the machine is full:
"*/

  bb <-- Rename_BiRcd_FULL =
    BEGIN bb:=bool(Rename_rcd = Rename_BiRcd) END;

/*"
{\bf Rename\_BiRcd\_CRE}\\[1ex]
The operation to create a record; a unique token is returned through
which the record may subsequently be referenced:
"*/

  rr <-- Rename_BiRcd_CRE =
    PRE Rename_rcd /= Rename_BiRcd THEN
      ANY new_rcd WHERE new_rcd : Rename_BiRcd - Rename_rcd THEN
        Rename_rcd := Rename_rcd \/ {new_rcd} ||
        Rename_rcd_fnc(new_rcd) := {} ||
        rr := new_rcd
      END
    END;

/*"
{\bf Rename\_BiRcd\_KILL}\\[1ex]
The operation to kill a record; the token input must have previously
been returned by {\em Rename\_BiRcd\_CRE\/}, and must be currently valid:
"*/

  Rename_BiRcd_KILL(rr : Rename_BiRcd) =
    PRE rr : Rename_rcd THEN
      Rename_rcd := Rename_rcd - {rr} ||
      Rename_rcd_fnc := {rr} <<| Rename_rcd_fnc
    END;

/*"
{\bf Rename\_BiRcd\_VLD}\\[1ex]
Returns a boolean indicating whether or not the input token is a
valid record (i.e.\ currently in use):
"*/

  bb <-- Rename_BiRcd_VLD(rr : Rename_BiRcd) =
    BEGIN bb := bool(rr : Rename_rcd) END;

/*"
\newpage
{\bf Rename\_BiRcd\_STO}\\[1ex]
The operation to store a value, {\em vv\/} in the field {\em idx\/}
of the record {\em rr\/};  {\em idx\/} must be a valid field, and
{\em rr\/} a valid record.
"*/

  Rename_BiRcd_STO(rr : Rename_BiRcd & idx : BYTE & vv : VALUE) =
    PRE rr : Rename_rcd & b2n(idx) : 1..numfld THEN
      Rename_rcd_fnc(rr)(b2n(idx)) := vv
   END;

/*"
{\bf Rename\_BiRcd\_VAL}\\[1ex]
The operation to return the value stored in field {\em idx\/} of record
of {\em vv\/};  {\em idx\/} must be a valid field, and
{\em rr\/} a valid record.
"*/

  vv <-- Rename_BiRcd_VAL(rr : Rename_BiRcd & idx : BYTE) =
    PRE rr : Rename_rcd & b2n(idx) : 1..numfld THEN
      vv := Rename_rcd_fnc(rr)(b2n(idx))
    END

END
