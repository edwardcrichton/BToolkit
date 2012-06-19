(Rename_vec_STO(?;vec) == (vec : POW((0..ub)*std_logic)));
(Rename_vec_VAL(vec;?) == (vec : POW((0..ub)*std_logic)));
(Rename_vec_EQL(sl;vec) == (sl : std_logic & vec : POW((0..ub)*std_logic)));
(Rename_idx_MOD(?;val , idx) == (val : std_logic & idx : 0..ub));
(Rename_idx_VAL(val;idx) == (val : std_logic & idx : 0..ub));
(Rename_idx_EQL(sl;val , idx) == (sl : std_logic & val : std_logic & idx : 0..ub));
(Rename_vec_VEC2NAT(nn;?) == (nn : NAT));
(Rename_vec_NAT2VEC(?;nn) == (nn : NAT));
(Rename_vec_XTR(vec;lo , hi) == (vec : POW(NAT*std_logic) & lo : 0..ub & hi : 0..ub));
(Rename_vec_MASK(?;lo , hi) == (lo : 0..ub & hi : 0..ub))
|
(lb : lb..lb);
(ub : ub..ub);
(Rename_Vec : POW(POW((0..ub)*std_logic)));
(Rename_Vec2Nat : POW(POW((0..ub)*std_logic)*NAT));
(Rename_Nat2Vec : POW(NAT*POW((0..ub)*std_logic)));
(Rename_vec : POW((0..ub)*std_logic))|
(lb , ub)
