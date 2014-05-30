(ULE(rr;aa , bb) == (rr : BOOL & aa : UNSIGNED & bb : UNSIGNED));
(UGE(rr;aa , bb) == (rr : BOOL & aa : UNSIGNED & bb : UNSIGNED));
(ULT(rr;aa , bb) == (rr : BOOL & aa : UNSIGNED & bb : UNSIGNED));
(UGT(rr;aa , bb) == (rr : BOOL & aa : UNSIGNED & bb : UNSIGNED));
(UEQ(rr;aa , bb) == (rr : BOOL & aa : UNSIGNED & bb : UNSIGNED));
(UNE(rr;aa , bb) == (rr : BOOL & aa : UNSIGNED & bb : UNSIGNED));
(UADD(rr;aa , bb) == (rr : UNSIGNED & aa : UNSIGNED & bb : UNSIGNED));
(USUB(rr;aa , bb) == (rr : UNSIGNED & aa : UNSIGNED & bb : UNSIGNED));
(UMUL(rr;aa , bb) == (rr : UNSIGNED & aa : UNSIGNED & bb : UNSIGNED));
(UDIV(rr;aa , bb) == (rr : UNSIGNED & aa : UNSIGNED & bb : UNSIGNED));
(UMOD(rr;aa , bb) == (rr : UNSIGNED & aa : UNSIGNED & bb : UNSIGNED));
(UINC(rr;aa) == (rr : UNSIGNED & aa : UNSIGNED));
(UDEC(rr;aa) == (rr : UNSIGNED & aa : UNSIGNED));
(ULEFT(rr;aa) == (rr : UNSIGNED & aa : UNSIGNED));
(URIGHT(rr;aa) == (rr : UNSIGNED & aa : UNSIGNED))
|
(given(UNSIGNED));
(n2u : POW(NAT*UNSIGNED));
(u2n : POW(UNSIGNED*NAT))|
(?)
