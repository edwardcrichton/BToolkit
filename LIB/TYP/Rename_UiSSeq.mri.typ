(Rename_UiSSeq_LEN(ll;?) == (ll : UNSIGNED));
(Rename_UiSSeq_VAL(vv;idx) == (vv : VALUE & idx : UNSIGNED));
(Rename_UiSSeq_FILL(?;vv) == (vv : VALUE));
(Rename_UiSSeq_CHG(?;idx , vv) == (idx : UNSIGNED & vv : VALUE));
(Rename_UiSSeq_APP(?;vv) == (vv : VALUE));
(Rename_UiSSeq_KEEP(?;idx) == (idx : UNSIGNED))
|
(given(VALUE));
(maxlen : NAT);
(Rename_sseq : POW(NAT*VALUE));
(Rename_sseq : seq(VALUE))|
(VALUE , maxlen)
