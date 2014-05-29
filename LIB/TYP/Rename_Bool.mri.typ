(Rename_VAL(vv;?) == (vv : BOOL));
(Rename_STO(?;vv) == (vv : BOOL));
(Rename_SET(?;?) == ?);
(Rename_RESET(?;?) == ?);
(Rename_EQL(bb;vv) == (bb : BOOL & vv : BOOL));
(Rename_NOT(?;?) == ?);
(Rename_AND(?;vv) == (vv : BOOL));
(Rename_OR(?;vv) == (vv : BOOL));
(Rename_XOR(?;vv) == (vv : BOOL))
|
(init_val : NAT);
(Rename_bool : BOOL)|
(init_val)
