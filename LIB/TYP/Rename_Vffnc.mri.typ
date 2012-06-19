(Rename_TST_FLD_FNC(bb;ff) == (bb : BOOL & ff : NAT));
(Rename_DEF_FNC(bb;ff) == (bb : BOOL & ff : NAT));
(Rename_FREE_FNC(bb , dd;?) == (dd : NAT & bb : BOOL));
(Rename_STO_FNC(?;ff , vv) == (ff : NAT & vv : VALUE));
(Rename_RMV_FNC(?;ff) == (ff : NAT));
(Rename_VAL_FNC(vv;ff) == (vv : VALUE & ff : NAT));
(Rename_EQL_FNC(bb;ff , vv) == (bb : BOOL & ff : NAT & vv : VALUE));
(Rename_NEQ_FNC(bb;ff , vv) == (bb : BOOL & ff : NAT & vv : VALUE));
(Rename_MOV_FFNC(?;ii , jj , ll) == (ii : NAT & jj : NAT & ll : NAT));
(Rename_OVR_FFNC(?;ii , ll , aa) == (ii : NAT & ll : NAT & aa : seq(CHAR) & aa : POW(NAT*CHAR)));
(Rename_OVR_LIT_FFNC(?;ii , ll , aa) == (ii : NAT & ll : NAT & aa : seq(CHAR) & aa : POW(NAT*CHAR)));
(Rename_XTR_FFNC(vv;ii , ll) == (vv : seq(CHAR) & ii : NAT & ll : NAT));
(Rename_EQL_FFNC(bb;ii , ll , vv) == (bb : BOOL & ii : NAT & ll : NAT & vv : seq(CHAR) & vv : POW(NAT*CHAR)));
(Rename_SAV_FNC(?;?) == ?);
(Rename_RST_FNC(?;?) == ?);
(Rename_SAVN_FNC(?;?) == ?);
(Rename_RSTN_FNC(?;?) == ?)
|
(given(VALUE));
(rcdsiz : NAT);
(Rename_UnPack : POW(POW(NAT*VALUE)*seq(CHAR)));
(Rename_CHARperWORD : NAT);
(Rename_Vfnc : POW(NAT*VALUE))|
(VALUE , rcdsiz)
