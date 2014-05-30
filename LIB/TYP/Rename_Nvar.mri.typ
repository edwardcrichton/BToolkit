(Rename_VAL_NVAR(vv;?) == (vv : NAT));
(Rename_STO_NVAR(?;vv) == (vv : NAT));
(Rename_MIN_NVAR(uu;vv) == (uu : NAT & vv : NAT));
(Rename_MAX_NVAR(uu;vv) == (uu : NAT & vv : NAT));
(Rename_PRE_INC_NVAR(bb;?) == (bb : BOOL));
(Rename_INC_NVAR(?;?) == ?);
(Rename_PRE_DEC_NVAR(bb;?) == (bb : BOOL));
(Rename_DEC_NVAR(?;?) == ?);
(Rename_PRE_ADD_NVAR(bb;vv) == (bb : BOOL & vv : NAT));
(Rename_ADD_NVAR(?;vv) == (vv : NAT));
(Rename_PRE_MUL_NVAR(bb;vv) == (bb : BOOL & vv : NAT));
(Rename_MUL_NVAR(?;vv) == (vv : NAT));
(Rename_PRE_SUB_NVAR(bb;vv) == (bb : BOOL & vv : NAT));
(Rename_SUB_NVAR(?;vv) == (vv : NAT));
(Rename_PRE_DIV_NVAR(bb;vv) == (bb : BOOL & vv : NAT));
(Rename_DIV_NVAR(?;vv) == (vv : NAT));
(Rename_PRE_MOD_NVAR(bb;vv) == (bb : BOOL & vv : NAT));
(Rename_MOD_NVAR(?;vv) == (vv : NAT));
(Rename_EQL_NVAR(bb;vv) == (bb : BOOL & vv : NAT));
(Rename_NEQ_NVAR(bb;vv) == (bb : BOOL & vv : NAT));
(Rename_GTR_NVAR(bb;vv) == (bb : BOOL & vv : NAT));
(Rename_GEQ_NVAR(bb;vv) == (bb : BOOL & vv : NAT));
(Rename_SMR_NVAR(bb;vv) == (bb : BOOL & vv : NAT));
(Rename_LEQ_NVAR(bb;vv) == (bb : BOOL & vv : NAT));
(Rename_SAV_NVAR(?;?) == ?);
(Rename_RST_NVAR(?;?) == ?);
(Rename_SAVN_NVAR(?;?) == ?);
(Rename_RSTN_NVAR(?;?) == ?)
|
(maxint : NAT);
(Rename_Nvar : NAT)|
(maxint)
