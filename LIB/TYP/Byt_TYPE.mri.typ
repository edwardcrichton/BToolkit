(BLE(rr;aa , bb) == (rr : BOOL & aa : BYTE & bb : BYTE));
(BGE(rr;aa , bb) == (rr : BOOL & aa : BYTE & bb : BYTE));
(BLT(rr;aa , bb) == (rr : BOOL & aa : BYTE & bb : BYTE));
(BGT(rr;aa , bb) == (rr : BOOL & aa : BYTE & bb : BYTE));
(BEQ(rr;aa , bb) == (rr : BOOL & aa : BYTE & bb : BYTE));
(BNE(rr;aa , bb) == (rr : BOOL & aa : BYTE & bb : BYTE));
(BADD(rr;aa , bb) == (rr : BYTE & aa : BYTE & bb : BYTE));
(BSUB(rr;aa , bb) == (rr : BYTE & aa : BYTE & bb : BYTE));
(BMUL(rr;aa , bb) == (rr : BYTE & aa : BYTE & bb : BYTE));
(BDIV(rr;aa , bb) == (rr : BYTE & aa : BYTE & bb : BYTE));
(BMOD(rr;aa , bb) == (rr : BYTE & aa : BYTE & bb : BYTE));
(BINC(rr;aa) == (rr : BYTE & aa : BYTE));
(BDEC(rr;aa) == (rr : BYTE & aa : BYTE));
(B2BOOL(rr;aa) == (rr : BOOL & aa : BYTE));
(BOOL2B(rr;aa) == (rr : BYTE & aa : BOOL));
(BLEFT(rr;aa) == (rr : BYTE & aa : BYTE));
(BRIGHT(rr;aa) == (rr : BYTE & aa : BYTE))
|
(given(BYTE));
(n2b : POW(NAT*BYTE));
(b2n : POW(BYTE*NAT));
(b2bl : POW(BYTE*BOOL));
(bl2b : POW(BOOL*BYTE))|
(?)
