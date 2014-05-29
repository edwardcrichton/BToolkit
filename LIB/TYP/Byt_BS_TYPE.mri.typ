(BAND(rr;aa , bb) == (rr : BYTE & aa : BYTE & bb : BYTE));
(BOR(rr;aa , bb) == (rr : BYTE & aa : BYTE & bb : BYTE));
(BXOR(rr;aa , bb) == (rr : BYTE & aa : BYTE & bb : BYTE));
(BNOT(rr;aa) == (rr : BYTE & aa : BYTE));
(ISBITSET(bb;bit , aa) == (bb : BOOL & bit : BYTE & aa : BYTE));
(SETBIT(rr;bit , aa) == (rr : BYTE & bit : BYTE & aa : BYTE));
(RESETBIT(rr;bit , aa) == (rr : BYTE & bit : BYTE & aa : BYTE));
(BLE(rr;aa , bb) == (bb : BYTE & aa : BYTE & rr : BOOL));
(BGE(rr;aa , bb) == (bb : BYTE & aa : BYTE & rr : BOOL));
(BLT(rr;aa , bb) == (bb : BYTE & aa : BYTE & rr : BOOL));
(BGT(rr;aa , bb) == (bb : BYTE & aa : BYTE & rr : BOOL));
(BEQ(rr;aa , bb) == (bb : BYTE & aa : BYTE & rr : BOOL));
(BNE(rr;aa , bb) == (bb : BYTE & aa : BYTE & rr : BOOL));
(BADD(rr;aa , bb) == (bb : BYTE & aa : BYTE & rr : BYTE));
(BSUB(rr;aa , bb) == (bb : BYTE & aa : BYTE & rr : BYTE));
(BMUL(rr;aa , bb) == (bb : BYTE & aa : BYTE & rr : BYTE));
(BDIV(rr;aa , bb) == (bb : BYTE & aa : BYTE & rr : BYTE));
(BMOD(rr;aa , bb) == (bb : BYTE & aa : BYTE & rr : BYTE));
(BINC(rr;aa) == (aa : BYTE & rr : BYTE));
(BDEC(rr;aa) == (aa : BYTE & rr : BYTE));
(B2BOOL(rr;aa) == (aa : BYTE & rr : BOOL));
(BOOL2B(rr;aa) == (aa : BOOL & rr : BYTE));
(BLEFT(rr;aa) == (aa : BYTE & rr : BYTE));
(BRIGHT(rr;aa) == (aa : BYTE & rr : BYTE))
|
(given(BYTE));
(n2b : POW(NAT*BYTE));
(b2n : POW(BYTE*NAT));
(b2bl : POW(BYTE*BOOL));
(bl2b : POW(BOOL*BYTE));
(b2bs : POW(BYTE*POW(NAT*NAT)));
(bs2b : POW(POW(NAT*NAT)*BYTE));
(bnd : POW(NAT*NAT*NAT));
(bor : POW(NAT*NAT*NAT));
(bxr : POW(NAT*NAT*NAT));
(bcp : POW(NAT*NAT))|
(?)
