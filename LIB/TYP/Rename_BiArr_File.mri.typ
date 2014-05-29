(Rename_IDX(bb;idx) == (bb : BOOL & idx : BYTE));
(Rename_VAL(vv;idx) == (vv : VALUE & idx : BYTE));
(Rename_STO(?;idx , vv) == (idx : BYTE & vv : VALUE));
(Rename_EQ(bb;idx , vv) == (bb : BOOL & idx : BYTE & vv : VALUE))
|
(given(VALUE));
(lb : NAT);
(ub : NAT);
(Rename : POW(NAT*VALUE))|
(VALUE , lb , ub)
