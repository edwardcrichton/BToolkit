(BSAND(rr;aa , bb) == (rr : POW(NAT*NAT) & aa : POW(NAT*NAT) & bb : POW(NAT*NAT)));
(BSOR(rr;aa , bb) == (rr : POW(NAT*NAT) & aa : POW(NAT*NAT) & bb : POW(NAT*NAT)));
(BSXOR(rr;aa , bb) == (rr : POW(NAT*NAT) & aa : POW(NAT*NAT) & bb : POW(NAT*NAT)));
(BSNOT(rr;aa) == (rr : POW(NAT*NAT) & aa : POW(NAT*NAT)));
(BSXTR(rr;aa , ii) == (rr : BYTE & aa : POW(NAT*NAT) & ii : BYTE));
(BSSET(rr;aa , ii , vv) == (rr : BYTE & aa : POW(NAT*NAT) & ii : BYTE & vv : BYTE));
(BFBS(rr;aa , ii , jj) == (rr : BYTE & aa : POW(NAT*NAT) & ii : BYTE & jj : BYTE));
(BIBS(rr;aa , bb , ii , jj) == (rr : POW(NAT*NAT) & aa : POW(NAT*NAT) & bb : BYTE & ii : BYTE & jj : BYTE));
(BSGET(rr;ss) == (rr : POW(NAT*NAT) & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(BSPUT(?;ss) == (ss : POW(NAT*NAT)))
|
(given(BITSEQ));
(BITSEQ0 : POW(NAT*NAT));
(BITSEQ0 : seq(NAT));
(power : POW(NAT*NAT*NAT));
(n2bs : POW(NAT*BITSEQ));
(bs2n : POW(BITSEQ*NAT));
(BITSEQ = POW(NAT*NAT));
(BITSEQ == POW(NAT*NAT))|
(?)
