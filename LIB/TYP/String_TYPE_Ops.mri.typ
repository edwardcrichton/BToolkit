(ASSIGN_ANY_STR(rr;?) == (rr : seq(CHAR)));
(CMP_STR(bb;rr , ss) == (bb : BOOL & rr : seq(CHAR) & rr : POW(NAT*CHAR) & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(SMR_STR(bb;rr , ss) == (bb : BOOL & rr : seq(CHAR) & rr : POW(NAT*CHAR) & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(PFX_STR(bb;rr , ss) == (bb : BOOL & rr : seq(CHAR) & rr : POW(NAT*CHAR) & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(PSX_STR(bb;rr , ss) == (bb : BOOL & rr : seq(CHAR) & rr : POW(NAT*CHAR) & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(SUB_STR(bb;rr , ss) == (bb : BOOL & rr : seq(CHAR) & rr : POW(NAT*CHAR) & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(CPY_STR(rr;ss) == (rr : seq(CHAR) & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(CNC_STR(rr;ss , tt) == (rr : seq(CHAR) & ss : seq(CHAR) & ss : POW(NAT*CHAR) & tt : seq(CHAR) & tt : POW(NAT*CHAR)));
(LEN_STR(nn;ss) == (nn : NAT & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(VAL_ITH_CHAR(cc;ss , ii) == (cc : CHAR & ii : NAT & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(CHAR_TO_NAT(nn;cc) == (nn : NAT & cc : CHAR));
(NAT_TO_STR(ss;nn) == (ss : seq(CHAR) & nn : NAT))
|
true
|
(?)
