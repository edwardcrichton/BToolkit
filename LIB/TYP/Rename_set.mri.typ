(Rename_FUL_SET(bb;?) == (bb : BOOL));
(Rename_XST_IDX_SET(bb;ii) == (bb : BOOL & ii : NAT));
(Rename_CRD_SET(nn;?) == (nn : NAT));
(Rename_VAL_SET(vv;ii) == (vv : VALUE & ii : NAT));
(Rename_ANY_SET(vv;?) == (vv : VALUE));
(Rename_CLR_SET(?;?) == ?);
(Rename_ENT_SET(?;vv) == (vv : VALUE));
(Rename_RMV_SET(?;vv) == (vv : VALUE));
(Rename_MBR_SET(bb;vv) == (bb : BOOL & vv : VALUE));
(Rename_EMP_SET(bb;?) == (bb : BOOL));
(Rename_SAV_SET(?;?) == ?);
(Rename_RST_SET(?;?) == ?);
(Rename_SAVN_SET(?;?) == ?);
(Rename_RSTN_SET(?;?) == ?)
|
(given(VALUE));
(maxcrd : NAT);
(Rename_sset : POW(VALUE));
(Rename_ordn : POW(NAT*VALUE));
(Rename_ordn : seq(VALUE))|
(VALUE , maxcrd)
