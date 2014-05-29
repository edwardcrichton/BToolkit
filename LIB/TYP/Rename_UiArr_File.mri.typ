(Rename_IDX(bb;idx) == (bb : BOOL & idx : UNSIGNED));
(Rename_VAL(vv;idx) == (vv : VALUE & idx : UNSIGNED));
(Rename_STO(?;idx , vv) == (idx : UNSIGNED & vv : VALUE));
(Rename_EQ(bb;idx , vv) == (bb : BOOL & idx : UNSIGNED & vv : VALUE))
|
(given(VALUE));
(lb : NAT);
(ub : NAT);
(Rename : POW(NAT*VALUE))|
(VALUE , lb , ub)
