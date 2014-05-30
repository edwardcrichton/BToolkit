(Rename_TST_IDX_NARR(bb;ii) == (bb : BOOL & ii : NAT));
(Rename_MAX_IDX_NARR(vv;ii , jj) == (vv : NAT & ii : NAT & jj : NAT));
(Rename_MIN_IDX_NARR(vv;ii , jj) == (vv : NAT & ii : NAT & jj : NAT));
(Rename_VAL_NARR(vv;ii) == (vv : NAT & ii : NAT));
(Rename_STO_NARR(?;ii , vv) == (ii : NAT & vv : NAT));
(Rename_ADD_NARR(?;ii , vv) == (ii : NAT & vv : NAT));
(Rename_MUL_NARR(?;ii , vv) == (ii : NAT & vv : NAT));
(Rename_SUB_NARR(?;ii , vv) == (ii : NAT & vv : NAT));
(Rename_DIV_NARR(?;ii , vv) == (ii : NAT & vv : NAT));
(Rename_MOD_NARR(?;ii , vv) == (ii : NAT & vv : NAT));
(Rename_EQL_NARR(bb;ii , vv) == (bb : BOOL & ii : NAT & vv : NAT));
(Rename_NEQ_NARR(bb;ii , vv) == (bb : BOOL & ii : NAT & vv : NAT));
(Rename_GTR_NARR(bb;ii , vv) == (bb : BOOL & ii : NAT & vv : NAT));
(Rename_GEQ_NARR(bb;ii , vv) == (bb : BOOL & ii : NAT & vv : NAT));
(Rename_SMR_NARR(bb;ii , vv) == (bb : BOOL & ii : NAT & vv : NAT));
(Rename_LEQ_NARR(bb;ii , vv) == (bb : BOOL & ii : NAT & vv : NAT));
(Rename_SCH_LO_EQL_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SCH_LO_NEQ_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SCH_LO_GEQ_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SCH_LO_GTR_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SCH_LO_LEQ_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SCH_LO_SMR_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SCH_HI_EQL_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SCH_HI_NEQ_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SCH_HI_GEQ_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SCH_HI_GTR_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SCH_HI_LEQ_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SCH_HI_SMR_NARR(bb , ii;jj , kk , vv) == (ii : NAT & bb : BOOL & jj : NAT & kk : NAT & vv : NAT));
(Rename_SRT_ASC_NARR(?;ii , jj) == (ii : NAT & jj : NAT));
(Rename_SRT_DSC_NARR(?;ii , jj) == (ii : NAT & jj : NAT));
(Rename_REV_NARR(?;ii , jj) == (ii : NAT & jj : NAT));
(Rename_RHT_NARR(?;ii , jj , nn) == (ii : NAT & jj : NAT & nn : NAT));
(Rename_LFT_NARR(?;ii , jj , nn) == (ii : NAT & jj : NAT & nn : NAT));
(Rename_SWP_NARR(?;ii , jj) == (ii : NAT & jj : NAT));
(Rename_SAV_NARR(?;?) == ?);
(Rename_RST_NARR(?;?) == ?);
(Rename_SAVN_NARR(?;?) == ?);
(Rename_RSTN_NARR(?;?) == ?)
|
(maxint : NAT);
(maxidx : NAT);
(Rename_Narr : POW(NAT*NAT))|
(maxint , maxidx)
