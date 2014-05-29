(Rename_TST_IDX_ARR(bb;ii) == (bb : BOOL & ii : NAT));
(Rename_VAL_ARR(vv;ii) == (vv : VALUE & ii : NAT));
(Rename_STO_ARR(?;ii , vv) == (ii : NAT & vv : VALUE));
(Rename_EQL_ARR(bb;ii , vv) == (bb : BOOL & ii : NAT & vv : VALUE));
(Rename_NEQ_ARR(bb;ii , vv) == (bb : BOOL & ii : NAT & vv : VALUE));
(Rename_SCH_LO_EQL_ARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : VALUE));
(Rename_SCH_LO_NEQ_ARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : VALUE));
(Rename_SCH_HI_EQL_ARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : VALUE));
(Rename_SCH_HI_NEQ_ARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : VALUE));
(Rename_REV_ARR(?;ii , jj) == (ii : NAT & jj : NAT));
(Rename_RHT_ARR(?;ii , jj , nn) == (ii : NAT & jj : NAT & nn : NAT));
(Rename_LFT_ARR(?;ii , jj , nn) == (ii : NAT & jj : NAT & nn : NAT));
(Rename_SWP_ARR(?;ii , jj) == (ii : NAT & jj : NAT));
(Rename_SAV_ARR(?;?) == ?);
(Rename_RST_ARR(?;?) == ?);
(Rename_SAVN_ARR(?;?) == ?);
(Rename_RSTN_ARR(?;?) == ?)
|
(given(VALUE));
(maxidx : NAT);
(Rename_Varr : POW(NAT*VALUE))|
(VALUE , maxidx)
