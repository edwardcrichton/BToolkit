(UAND(rr;aa , bb) == (rr : UNSIGNED & aa : UNSIGNED & bb : UNSIGNED));
(UOR(rr;aa , bb) == (rr : UNSIGNED & aa : UNSIGNED & bb : UNSIGNED));
(UXOR(rr;aa , bb) == (rr : UNSIGNED & aa : UNSIGNED & bb : UNSIGNED));
(UNOT(rr;aa) == (rr : UNSIGNED & aa : UNSIGNED));
(ULE(rr;aa , bb) == (bb : UNSIGNED & aa : UNSIGNED & rr : BOOL));
(UGE(rr;aa , bb) == (bb : UNSIGNED & aa : UNSIGNED & rr : BOOL));
(ULT(rr;aa , bb) == (bb : UNSIGNED & aa : UNSIGNED & rr : BOOL));
(UGT(rr;aa , bb) == (bb : UNSIGNED & aa : UNSIGNED & rr : BOOL));
(UEQ(rr;aa , bb) == (bb : UNSIGNED & aa : UNSIGNED & rr : BOOL));
(UNE(rr;aa , bb) == (bb : UNSIGNED & aa : UNSIGNED & rr : BOOL));
(UADD(rr;aa , bb) == (bb : UNSIGNED & aa : UNSIGNED & rr : UNSIGNED));
(USUB(rr;aa , bb) == (bb : UNSIGNED & aa : UNSIGNED & rr : UNSIGNED));
(UMUL(rr;aa , bb) == (bb : UNSIGNED & aa : UNSIGNED & rr : UNSIGNED));
(UDIV(rr;aa , bb) == (bb : UNSIGNED & aa : UNSIGNED & rr : UNSIGNED));
(UMOD(rr;aa , bb) == (bb : UNSIGNED & aa : UNSIGNED & rr : UNSIGNED));
(UINC(rr;aa) == (aa : UNSIGNED & rr : UNSIGNED));
(UDEC(rr;aa) == (aa : UNSIGNED & rr : UNSIGNED));
(ULEFT(rr;aa) == (aa : UNSIGNED & rr : UNSIGNED));
(URIGHT(rr;aa) == (aa : UNSIGNED & rr : UNSIGNED))
|
(given(UNSIGNED));
(n2u : POW(NAT*UNSIGNED));
(u2n : POW(UNSIGNED*NAT));
(u2bs : POW(UNSIGNED*POW(NAT*NAT)));
(bs2u : POW(POW(NAT*NAT)*UNSIGNED))|
(?)
