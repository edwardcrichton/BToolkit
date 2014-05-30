(Rename_BiBA_IDX(bb;idx) == (bb : BOOL & idx : BYTE));
(Rename_BiBA_VAL(vv;idx) == (vv : BYTE & idx : BYTE));
(Rename_BiBA_STO(?;idx , vv) == (idx : BYTE & vv : BYTE));
(Rename_BiBA_EQ(bb;idx , vv) == (bb : BOOL & idx : BYTE & vv : BYTE));
(Rename_BiBA_IEQ(bb;idx , idx2) == (bb : BOOL & idx : BYTE & idx2 : BYTE));
(Rename_BiBA_NE(bb;idx , vv) == (bb : BOOL & idx : BYTE & vv : BYTE));
(Rename_BiBA_INE(bb;idx , idx2) == (bb : BOOL & idx : BYTE & idx2 : BYTE));
(Rename_BiBA_GT(bb;idx , vv) == (bb : BOOL & idx : BYTE & vv : BYTE));
(Rename_BiBA_IGT(bb;idx , idx2) == (bb : BOOL & idx : BYTE & idx2 : BYTE));
(Rename_BiBA_GE(bb;idx , vv) == (bb : BOOL & idx : BYTE & vv : BYTE));
(Rename_BiBA_IGE(bb;idx , idx2) == (bb : BOOL & idx : BYTE & idx2 : BYTE));
(Rename_BiBA_LT(bb;idx , vv) == (bb : BOOL & idx : BYTE & vv : BYTE));
(Rename_BiBA_ILT(bb;idx , idx2) == (bb : BOOL & idx : BYTE & idx2 : BYTE));
(Rename_BiBA_LE(bb;idx , vv) == (bb : BOOL & idx : BYTE & vv : BYTE));
(Rename_BiBA_ILE(bb;idx , idx2) == (bb : BOOL & idx : BYTE & idx2 : BYTE));
(Rename_BiBA_ADD(?;idx , vv) == (idx : BYTE & vv : BYTE));
(Rename_BiBA_IADD(?;idx , idx2) == (idx : BYTE & idx2 : BYTE));
(Rename_BiBA_SUB(?;idx , vv) == (idx : BYTE & vv : BYTE));
(Rename_BiBA_ISUB(?;idx , idx2) == (idx : BYTE & idx2 : BYTE));
(Rename_BiBA_INC(?;idx) == (idx : BYTE));
(Rename_BiBA_DEC(?;idx) == (idx : BYTE));
(Rename_BiBA_MUL(?;idx , vv) == (idx : BYTE & vv : BYTE));
(Rename_BiBA_DIV(?;idx , vv) == (idx : BYTE & vv : BYTE));
(Rename_BiBA_REM(?;idx , vv) == (idx : BYTE & vv : BYTE));
(Rename_BiBA_STO_NXT(?;vv) == (vv : BYTE));
(Rename_BiBA_FILL(?;vv) == (vv : BYTE));
(Rename_BiBA_NXT(nn;?) == (nn : BYTE))
|
(lb : NAT);
(ub : NAT);
(init_val : NAT);
(Rename_nxt : NAT);
(Rename_bba : POW(NAT*BYTE))|
(lb , ub , init_val)
