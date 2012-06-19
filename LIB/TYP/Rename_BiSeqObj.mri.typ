(Rename_BiSeqObj_FULL_MEM(bb;?) == (bb : BOOL));
(Rename_BiSeqObj_FULL_OBJ(bb;?) == (bb : BOOL));
(Rename_BiSeqObj_CRE(obj;?) == (obj : Rename_SEQOBJ));
(Rename_BiSeqObj_KILL(?;obj) == (obj : Rename_SEQOBJ));
(Rename_BiSeqObj_VLD_OBJ(bb;obj) == (bb : BOOL & obj : Rename_SEQOBJ));
(Rename_BiSeqObj_VLD_IDX(bb;obj , idx) == (bb : BOOL & obj : Rename_SEQOBJ & idx : BYTE));
(Rename_BiSeqObj_OBJ_TOT(tt;?) == (tt : BYTE));
(Rename_BiSeqObj_LEN(ll;obj) == (ll : BYTE & obj : Rename_SEQOBJ));
(Rename_BiSeqObj_FRST(vv;obj) == (vv : VALUE & obj : Rename_SEQOBJ));
(Rename_BiSeqObj_LAST(vv;obj) == (vv : VALUE & obj : Rename_SEQOBJ));
(Rename_BiSeqObj_VAL(vv;obj , idx) == (vv : VALUE & obj : Rename_SEQOBJ & idx : BYTE));
(Rename_BiSeqObj_CLR(?;obj) == (obj : Rename_SEQOBJ));
(Rename_BiSeqObj_STO(?;obj , idx , vv) == (obj : Rename_SEQOBJ & idx : BYTE & vv : VALUE));
(Rename_BiSeqObj_INS(?;obj , idx , vv) == (obj : Rename_SEQOBJ & idx : BYTE & vv : VALUE));
(Rename_BiSeqObj_SWP(?;obj , idx1 , idx2) == (obj : Rename_SEQOBJ & idx1 : BYTE & idx2 : BYTE));
(Rename_BiSeqObj_PUSH(?;obj , vv) == (obj : Rename_SEQOBJ & vv : VALUE));
(Rename_BiSeqObj_APP(?;obj , vv) == (obj : Rename_SEQOBJ & vv : VALUE));
(Rename_BiSeqObj_POP(?;obj) == (obj : Rename_SEQOBJ));
(Rename_BiSeqObj_FRONT(?;obj) == (obj : Rename_SEQOBJ));
(Rename_BiSeqObj_DEL(?;obj , idx) == (obj : Rename_SEQOBJ & idx : BYTE));
(Rename_BiSeqObj_RTN(?;obj , idx) == (obj : Rename_SEQOBJ & idx : BYTE));
(Rename_BiSeqObj_RMV(?;obj , idx) == (obj : Rename_SEQOBJ & idx : BYTE));
(Rename_BiSeqObj_CPY(?;obj1 , obj2) == (obj1 : Rename_SEQOBJ & obj2 : Rename_SEQOBJ));
(Rename_BiSeqObj_CAT(?;obj1 , obj2) == (obj1 : Rename_SEQOBJ & obj2 : Rename_SEQOBJ))
|
(given(VALUE));
(maxobj : NAT);
(maxmem : NAT);
(given(Rename_SEQOBJ));
(Rename_seqobj : POW(Rename_SEQOBJ));
(Rename_seqfun : POW(Rename_SEQOBJ*seq(VALUE)));
(Rename_seqmem : NAT)|
(VALUE , maxobj , maxmem)
