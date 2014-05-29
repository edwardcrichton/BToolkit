(Rename_FUL_SEQ(bb;?) == (bb : BOOL));
(Rename_XST_IDX_SEQ(bb;ii) == (bb : BOOL & ii : NAT));
(Rename_STO_SEQ(?;ii , vv) == (ii : NAT & vv : VALUE));
(Rename_CLR_SEQ(?;?) == ?);
(Rename_PSH_SEQ(?;vv) == (vv : VALUE));
(Rename_POP_SEQ(?;?) == ?);
(Rename_FST_SEQ(vv;?) == (vv : VALUE));
(Rename_LST_SEQ(vv;?) == (vv : VALUE));
(Rename_TAL_SEQ(?;?) == ?);
(Rename_KEP_SEQ(?;ii) == (ii : NAT));
(Rename_CUT_SEQ(?;ii) == (ii : NAT));
(Rename_SWP_SEQ(?;ii , jj) == (ii : NAT & jj : NAT));
(Rename_VAL_SEQ(vv;ii) == (vv : VALUE & ii : NAT));
(Rename_LEN_SEQ(nn;?) == (nn : NAT));
(Rename_EMP_SEQ(bb;?) == (bb : BOOL));
(Rename_EQL_SEQ(bb;ii , vv) == (bb : BOOL & ii : NAT & vv : VALUE));
(Rename_NEQ_SEQ(bb;ii , vv) == (bb : BOOL & ii : NAT & vv : VALUE));
(Rename_SCH_LO_EQL_SEQ(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : VALUE));
(Rename_SCH_LO_NEQ_SEQ(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : VALUE));
(Rename_SCH_HI_EQL_SEQ(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : VALUE));
(Rename_SCH_HI_NEQ_SEQ(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : VALUE));
(Rename_REV_SEQ(?;ii , jj) == (ii : NAT & jj : NAT));
(Rename_RHT_SEQ(?;ii , jj , nn) == (ii : NAT & jj : NAT & nn : NAT));
(Rename_LFT_SEQ(?;ii , jj , nn) == (ii : NAT & jj : NAT & nn : NAT));
(Rename_SAV_SEQ(?;?) == ?);
(Rename_RST_SEQ(?;?) == ?);
(Rename_SAVN_SEQ(?;?) == ?);
(Rename_RSTN_SEQ(?;?) == ?)
|
(given(VALUE));
(maxsize : NAT);
(Rename_Vseq : POW(NAT*VALUE));
(Rename_Vseq : seq(VALUE))|
(VALUE , maxsize)
