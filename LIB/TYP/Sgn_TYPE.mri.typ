(SLE(rr;aa,bb) == (rr: BOOL & aa: SIGNED & bb: SIGNED));
(SGE(rr;aa,bb) == (rr: BOOL & aa: SIGNED & bb: SIGNED));
(SLT(rr;aa,bb) == (rr: BOOL & aa: SIGNED & bb: SIGNED));
(SGT(rr;aa,bb) == (rr: BOOL & aa: SIGNED & bb: SIGNED));
(SEQ(rr;aa,bb) == (rr: BOOL & aa: SIGNED & bb: SIGNED));
(SNE(rr;aa,bb) == (rr: BOOL & aa: SIGNED & bb: SIGNED));
(SADD(rr;aa,bb) == (rr: SIGNED & aa: SIGNED & bb: SIGNED));
(SSUB(rr;aa,bb) == (rr: SIGNED & aa: SIGNED & bb: SIGNED));
(SMUL(rr;aa,bb) == (rr: SIGNED & aa: SIGNED & bb: SIGNED));
(SDIV(rr;aa,bb) == (rr: SIGNED & aa: SIGNED & bb: SIGNED));
(SMOD(rr;aa,bb) == (rr: SIGNED & aa: SIGNED & bb: SIGNED));
(SINC(rr;aa) == (rr: SIGNED & aa: SIGNED));
(SDEC(rr;aa) == (rr: SIGNED & aa: SIGNED))
|
(given(SIGNED));
(n2ps: POW(NAT*SIGNED));
(n2ns: POW(NAT*SIGNED));
(ps2n: POW(SIGNED*NAT));
(ns2n: POW(SIGNED*NAT));
(MinSgn: SIGNED);
(MaxSgn: SIGNED);
(?+?: SIGNED*SIGNED +-> SIGNED);
(?-?: SIGNED*SIGNED +-> SIGNED);
(?*?: SIGNED*SIGNED +-> SIGNED);
(?/?: SIGNED*SIGNED +-> SIGNED);
(? mod ?: SIGNED*SIGNED +-> SIGNED)|
(?)
