(Rename_vec_STO(?;vec) == (vec: POW(NAT*NAT)));
(Rename_vec_VAL(vec;?) == (vec: POW(NAT*NAT)));
(Rename_vec_EQL(st;vec) == (st: NAT & vec: POW(NAT*NAT)));
(Rename_VEC2NAT(nn;?) == (nn: NAT));
(Rename_NAT2VEC(?;nn) == (nn: NAT));
(Rename_ALL1s(?;?) == ?);
(Rename_ALL0s(?;?) == ?);
(Rename_VAL(bb;idx) == (bb: NAT & idx: NAT));
(Rename_SET1(?;idx) == (idx: NAT));
(Rename_SET0(?;idx) == (idx: NAT));
(Rename_MASK(?;lo,up) == (lo: NAT & up: NAT));
(Rename_EXT(?;lo,up) == (lo: NAT & up: NAT))
|
(length: NAT);
(Rename_vector: POW(POW(NAT*NAT)));
(Rename_Vec2Nat: POW(POW(NAT*NAT)*NAT));
(Rename_Nat2Vec: POW(NAT*POW(NAT*NAT)));
(Rename_vec: POW(NAT*NAT))|
(length)
