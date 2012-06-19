(Rename_BiSSeq_LEN(ll;?) == (ll : BYTE));
(Rename_BiSSeq_VAL(vv;idx) == (vv : VALUE & idx : BYTE));
(Rename_BiSSeq_FILL(?;vv) == (vv : VALUE));
(Rename_BiSSeq_CHG(?;idx , vv) == (idx : BYTE & vv : VALUE));
(Rename_BiSSeq_APP(?;vv) == (vv : VALUE));
(Rename_BiSSeq_KEEP(?;idx) == (idx : BYTE))
|
(given(VALUE));
(maxlen : NAT);
(Rename_sseq : POW(NAT*VALUE));
(Rename_sseq : seq(VALUE))|
(VALUE , maxlen)
