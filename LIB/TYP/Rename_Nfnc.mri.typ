(Rename_TST_FLD_NFNC(bb;ff) == (bb : BOOL & ff : NAT));
(Rename_DEF_NFNC(bb;ff) == (bb : BOOL & ff : NAT));
(Rename_FREE_NFNC(bb , dd;?) == (dd : NAT & bb : BOOL));
(Rename_STO_NFNC(?;ff , vv) == (ff : NAT & vv : NAT));
(Rename_RMV_NFNC(?;ff) == (ff : NAT));
(Rename_ADD_NFNC(?;ff , vv) == (ff : NAT & vv : NAT));
(Rename_MUL_NFNC(?;ff , vv) == (ff : NAT & vv : NAT));
(Rename_SUB_NFNC(?;ff , vv) == (ff : NAT & vv : NAT));
(Rename_DIV_NFNC(?;ff , vv) == (ff : NAT & vv : NAT));
(Rename_MOD_NFNC(?;ff , vv) == (ff : NAT & vv : NAT));
(Rename_VAL_NFNC(vv;ff) == (vv : NAT & ff : NAT));
(Rename_EQL_NFNC(bb;ff , vv) == (bb : BOOL & ff : NAT & vv : NAT));
(Rename_NEQ_NFNC(bb;ff , vv) == (bb : BOOL & ff : NAT & vv : NAT));
(Rename_GTR_NFNC(bb;ff , vv) == (bb : BOOL & ff : NAT & vv : NAT));
(Rename_GEQ_NFNC(bb;ff , vv) == (bb : BOOL & ff : NAT & vv : NAT));
(Rename_SMR_NFNC(bb;ff , vv) == (bb : BOOL & ff : NAT & vv : NAT));
(Rename_LEQ_NFNC(bb;ff , vv) == (bb : BOOL & ff : NAT & vv : NAT));
(Rename_SAV_NFNC(?;?) == ?);
(Rename_RST_NFNC(?;?) == ?);
(Rename_SAVN_NFNC(?;?) == ?);
(Rename_RSTN_NFNC(?;?) == ?)
|
(maxint : NAT);
(maxfld : NAT);
(Rename_Nfnc : POW(NAT*NAT))|
(maxint , maxfld)
