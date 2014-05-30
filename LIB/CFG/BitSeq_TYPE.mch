/***
HISTORY:
 
V1.0
  VERSION:          B-Toolkit Beta 4.16
  DATE:             03/06/98
***/

MACHINE            BitSeq_TYPE

/*"
The operational interface to this machine provides bit positions
{\em 0\/} to {\em 7\/}, with position {\em 0\/} being the least
significant bit. Thus the number {\em 1\/} would have its {\em 0\/}th
bit set to {\em 1\/}, and all other bits set to {\em 0\/}.

The low-nibble occupies bit positions {\em 0\/} to {\em 3\/}, and the
high-nibble positions {\em 4\/} to {\em 7\/}.

The operations comprise six bit manipulation functions {\em BSAND,
BSOR, BSXOR, BSNOT, BXSTR\/} and {\em BSSET \/} and the two operations
for manipulating bytes in a bit-sequence {\em BSBYTE\_FROM\_BITSEQ\/}
and {\em BSBYTE\_IN\_BITSEQ\/}.
"*/

SEES               Byt_BS_TYPE, String_TYPE

SETS               BITSEQ

CONSTANTS          BITSEQ0, /* bit_and, bit_or, bit_xor, bit_comp, */ power, n2bs, bs2n

PROPERTIES

/*"
{\em BITSEQ\/} is a sequence of {\em 0\/}s and {\em 1\/}s of length 8:
"*/

       BITSEQ = 1..8 --> {0,1} &

/*"
We define the zero {\em BITSEQ\/}:
"*/

       BITSEQ0 = [0,0,0,0,0,0,0,0] &

/*"
We need a `to the power' function:
"*/

  power : NAT * NAT --> NAT &

/*"
For convenience, we include the conversion functions between {\em BITSEQ\/}
and {\em NAT\/}, defined in terms of those between {\em BITSEQ\/}
and {\em BYTE\/}, and {\em BYTE\/} and {\em NAT\/}
"*/
  n2bs : 0..255 >->> BITSEQ &
  bs2n : BITSEQ >->> 0..255 &
  !byt.(byt:BYTE => bs2b(b2bs(byt)) = byt) &
  !bts.(bts:BITSEQ => b2bs(bs2b(bts)) = bts)

OPERATIONS

/*"
The first four operations return the bitwise-and, -or, -xor and
-complement of their input parameters.\\[2ex]

{\bf BSAND}\\[.5ex]
Translated as: {\tt rr := BAND(aa,bb)}
"*/
  rr <-- BSAND (aa : BITSEQ & bb : BITSEQ) =
    BEGIN rr := ((aa >< bb) ; bnd) END;

/*"
{\bf BSOR}\\[.5ex]
Translated as: {\tt rr := BOR(aa,bb)}
"*/
  rr <-- BSOR (aa : BITSEQ & bb : BITSEQ) =
    BEGIN rr := ((aa >< bb) ; bor) END;

/*"
{\bf BSXOR}\\[.5ex]
Translated as: {\tt rr := BXOR(aa,bb)}
"*/
  rr <-- BSXOR (aa : BITSEQ & bb : BITSEQ) =
    BEGIN rr := ((aa >< bb) ; bxr) END;

/*"
\newpage
{\bf BSNOT}\\[.5ex]
Translated as: {\tt rr := BNOT(aa)}
"*/
  rr <-- BSNOT (aa : BITSEQ) =
    BEGIN rr := (aa ; bcp) END;

/*"
{\bf BSXTR}\\[.5ex]
Returns the {\em BYTE\/} value of the {\em ii\/}th bit of {\em aa\/}:\\
"*/
  rr <-- BSXTR (aa : BITSEQ & ii : BYTE) =
    PRE b2n(ii) : 0..7 THEN rr := n2b(aa(b2n(ii)+1)) END;

/*"
{\bf BSSET}\\[.5ex]
Returns the {\em BYTE\/} whose corresponding {\em BITSEQ\/} is the same
as {\em aa\/} except that the {\em ii\/}th bit has been set to {\em vv\/}:\\
"*/
  rr <-- BSSET (aa : BITSEQ & ii : BYTE & vv : BYTE) =
    PRE b2n(ii) :  0..7 & b2n(vv) : {0,1} THEN
      rr := bs2b(aa<+{b2n(ii)+1|->b2n(vv)})
    END;

/*"
\newpage
{\bf BFBS}\\[.5ex]
Returns the {\em BYTE\/} whose corresponding {\em BITSEQ\/} bit
positions from {\em 0\/} up to {\em jj-ii\/} agree with bit positions
of {\em aa\/} from {\em ii\/} to {\em jj\/}, with the remaining
positions set to {\em 0\/}:\\
"*/
  rr <-- BFBS(aa : BITSEQ & ii : BYTE & jj : BYTE) =
    PRE b2n(ii) :  0..7 & b2n(jj) :  0..7 & ii <= jj THEN
      rr := bs2b ( (
                     (aa \|/ b2n(ii)) /|\ (b2n(jj)-b2n(ii)+1)
                   ) ^
                   (
                     (BITSEQ0 /|\ (7-b2n(jj)+b2n(ii)))
                   )
                 )
    END;

/*"
{\bf BIBS}\\[.5ex]
Returns the {\em BITSEQ\/} whose bit positions from {\em 0\/} up to
{\em ii-1\/} and from {\em jj+1\/} up to {\em 7\/} are unchanged, and
whose bit positions from {\em ii\/} to {\em jj\/} agree with the {\em
BITSEQ\/} representation of {\em bb\/} from bit positions {\em 0\/} to
{\em jj-ii\/}; {\em bb\/}'s remaining bits are {\em 0\/}, and the
precondition ensures that {\em jj-ii+1\/} is large enough for {\em
bb\/}'s {\em BITSEQ\/} representation:\\
"*/
  rr <-- BIBS(aa : BITSEQ &bb : BYTE & ii : BYTE & jj : BYTE)
  =
    PRE
      b2n(ii) :  0..7 & b2n(jj) :  0..7 & ii <= jj &
      b2n(bb) < power(2,b2n(jj-ii))
    THEN
      rr := ( 
              aa /|\ b2n(ii)
            ) ^
            (
              b2bs(bb) /|\ (b2n(jj)-b2n(ii)+1)
            ) ^
            (
              aa /|\ (7-b2n(jj))
            )
    END;

/*"
We provide two operations providing i/o for the purposes of
prototyping in C; the operations have no PASP equivalents.\\[1ex]

{\bf BSGET}\\[.5ex]
"*/
  rr <-- BSGET(ss : STRING) =
    BEGIN rr :: BITSEQ END;

  BSPUT(ss : BITSEQ) = BEGIN skip END

END
