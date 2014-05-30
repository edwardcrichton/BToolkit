(Rename_TST_FLD_FNC(bb;ff) == (bb : BOOL & ff : NAT));
(Rename_DEF_FNC(bb;ff) == (bb : BOOL & ff : NAT));
(Rename_FREE_FNC(bb , dd;?) == (dd : NAT & bb : BOOL));
(Rename_STO_FNC(?;ff , vv) == (ff : NAT & vv : VALUE));
(Rename_RMV_FNC(?;ff) == (ff : NAT));
(Rename_VAL_FNC(vv;ff) == (vv : VALUE & ff : NAT));
(Rename_EQL_FNC(bb;ff , vv) == (bb : BOOL & ff : NAT & vv : VALUE));
(Rename_NEQ_FNC(bb;ff , vv) == (bb : BOOL & ff : NAT & vv : VALUE));
(Rename_SAV_FNC(?;?) == ?);
(Rename_RST_FNC(?;?) == ?);
(Rename_SAVN_FNC(?;?) == ?);
(Rename_RSTN_FNC(?;?) == ?)
|
(given(VALUE));
(maxfld : NAT);
(Rename_Vfnc : POW(NAT*VALUE))|
(VALUE , maxfld)
