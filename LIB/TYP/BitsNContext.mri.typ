(NO_BTSN(rr;len) == (rr : POW(NAT*BOOL) & len : NAT));
(STO_BTSN(rr;len , reg , nn , bb) == (rr : POW(NAT*BOOL) & reg : POW(NAT*BOOL) & nn : NAT & len : NAT & bb : BOOL));
(VAL_BTSN(bb;len , reg , nn) == (bb : BOOL & reg : POW(NAT*BOOL) & nn : NAT & len : NAT));
(CPL_BTSN(rr;len , reg) == (rr : POW(NAT*BOOL) & reg : POW(NAT*BOOL) & len : NAT));
(SUB_BTSN(rr;len , reg1 , reg2) == (rr : POW(NAT*BOOL) & reg1 : POW(NAT*BOOL) & reg2 : POW(NAT*BOOL) & len : NAT))
|
(BITSN : POW(NAT*POW(POW(NAT*BOOL))));
(tsb : POW(BOOL*BOOL*BOOL))|
(?)
