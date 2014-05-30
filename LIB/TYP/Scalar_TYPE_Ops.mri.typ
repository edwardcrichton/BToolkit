(SCL(uu;vv) == (uu : NAT & vv : NAT));
(MIN(uu;vv , ww) == (uu : NAT & vv : NAT & ww : NAT));
(MAX(uu;vv , ww) == (uu : NAT & vv : NAT & ww : NAT));
(INC(uu;vv) == (uu : NAT & vv : NAT));
(DEC(uu;vv) == (uu : NAT & vv : NAT));
(ADD(uu;vv , ww) == (uu : NAT & vv : NAT & ww : NAT));
(MUL(uu;vv , ww) == (uu : NAT & vv : NAT & ww : NAT));
(SUB(uu;vv , ww) == (uu : NAT & vv : NAT & ww : NAT));
(DIV(uu;vv , ww) == (uu : NAT & vv : NAT & ww : NAT));
(MOD(uu;vv , ww) == (uu : NAT & vv : NAT & ww : NAT));
(EQL(bb;vv , ww) == (bb : BOOL & vv : NAT & ww : NAT));
(NEQ(bb;vv , ww) == (bb : BOOL & vv : NAT & ww : NAT));
(GTR(bb;vv , ww) == (bb : BOOL & vv : NAT & ww : NAT));
(GEQ(bb;vv , ww) == (bb : BOOL & vv : NAT & ww : NAT));
(SMR(bb;vv , ww) == (bb : BOOL & vv : NAT & ww : NAT));
(LEQ(bb;vv , ww) == (bb : BOOL & vv : NAT & ww : NAT));
(EQZ(bb;vv) == (bb : BOOL & vv : NAT));
(RND(nn;mm) == (nn : NAT & mm : NAT))
|
true
|
(?)
