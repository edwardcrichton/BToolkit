(Rename_VAL_VAR(vv;?) == (vv : VALUE));
(Rename_STO_VAR(?;vv) == (vv : VALUE));
(Rename_EQL_VAR(bb;vv) == (bb : BOOL & vv : VALUE));
(Rename_NEQ_VAR(bb;vv) == (bb : BOOL & vv : VALUE));
(Rename_SAV_VAR(?;?) == ?);
(Rename_RST_VAR(?;?) == ?);
(Rename_SAVN_VAR(?;?) == ?);
(Rename_RSTN_VAR(?;?) == ?)
|
(given(VALUE));
(Rename_Vvar : VALUE)|
(VALUE)
