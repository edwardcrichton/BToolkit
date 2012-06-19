(Rename_BiSeq_FULL(bb;?) == (bb : BOOL));
(Rename_BiSeq_IDX(bb;idx) == (bb : BOOL & idx : BYTE));
(Rename_BiSeq_LEN(ll;?) == (ll : BYTE));
(Rename_BiSeq_FRST(vv;?) == (vv : VALUE));
(Rename_BiSeq_LAST(vv;?) == (vv : VALUE));
(Rename_BiSeq_VAL(vv;idx) == (vv : VALUE & idx : BYTE));
(Rename_BiSeq_CLR(?;?) == ?);
(Rename_BiSeq_FILL(?;len , vv) == (len : BYTE & vv : VALUE));
(Rename_BiSeq_STO(?;idx , vv) == (idx : BYTE & vv : VALUE));
(Rename_BiSeq_INS(?;idx , vv) == (idx : BYTE & vv : VALUE));
(Rename_BiSeq_SWP(?;idx1 , idx2) == (idx1 : BYTE & idx2 : BYTE));
(Rename_BiSeq_PUSH(?;vv) == (vv : VALUE));
(Rename_BiSeq_APP(?;vv) == (vv : VALUE));
(Rename_BiSeq_POP(?;?) == ?);
(Rename_BiSeq_FRONT(?;?) == ?);
(Rename_BiSeq_DEL(?;idx) == (idx : BYTE));
(Rename_BiSeq_RTN(?;idx) == (idx : BYTE));
(Rename_BiSeq_RMV(?;idx) == (idx : BYTE))
|
(given(VALUE));
(maxlen : NAT);
(Rename_seq : POW(NAT*VALUE));
(Rename_seq : seq(VALUE))|
(VALUE , maxlen)
