(Rename_UiSeq_FULL(bb;?) == (bb : BOOL));
(Rename_UiSeq_IDX(bb;idx) == (bb : BOOL & idx : UNSIGNED));
(Rename_UiSeq_LEN(ll;?) == (ll : UNSIGNED));
(Rename_UiSeq_FRST(vv;?) == (vv : VALUE));
(Rename_UiSeq_LAST(vv;?) == (vv : VALUE));
(Rename_UiSeq_VAL(vv;idx) == (vv : VALUE & idx : UNSIGNED));
(Rename_UiSeq_CLR(?;?) == ?);
(Rename_UiSeq_FILL(?;len , vv) == (len : UNSIGNED & vv : VALUE));
(Rename_UiSeq_STO(?;idx , vv) == (idx : UNSIGNED & vv : VALUE));
(Rename_UiSeq_INS(?;idx , vv) == (idx : UNSIGNED & vv : VALUE));
(Rename_UiSeq_SWP(?;idx1 , idx2) == (idx1 : UNSIGNED & idx2 : UNSIGNED));
(Rename_UiSeq_PUSH(?;vv) == (vv : VALUE));
(Rename_UiSeq_APP(?;vv) == (vv : VALUE));
(Rename_UiSeq_POP(?;?) == ?);
(Rename_UiSeq_FRONT(?;?) == ?);
(Rename_UiSeq_DEL(?;idx) == (idx : UNSIGNED));
(Rename_UiSeq_RTN(?;idx) == (idx : UNSIGNED));
(Rename_UiSeq_RMV(?;idx) == (idx : UNSIGNED))
|
(given(VALUE));
(maxlen : NAT);
(Rename_seq : POW(NAT*VALUE));
(Rename_seq : seq(VALUE))|
(VALUE , maxlen)
