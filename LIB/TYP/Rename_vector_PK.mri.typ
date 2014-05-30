(Rename_vec_VEC2NAT(nn;vec) == (nn : NAT & vec : POW((0..ub)*std_logic)));
(Rename_vec_NAT2VEC(vec;nn) == (vec : POW((0..ub)*std_logic) & nn : NAT));
(Rename_idx_VAL(val;vec , idx) == (val : std_logic & vec : POW((0..ub)*std_logic) & idx : 0..ub));
(Rename_idx_EQL(sl;val , vec , idx) == (sl : std_logic & val : std_logic & vec : POW((0..ub)*std_logic) & idx : 0..ub));
(Rename_vec_XTR(vecout;vecin , lo , hi) == (vecout : POW(NAT*std_logic) & vecin : POW((0..ub)*std_logic) & lo : 0..ub & hi : 0..ub));
(Rename_idx_MOD(vecout;val , vecin , idx) == (vecout : POW((0..ub)*std_logic) & val : std_logic & vecin : POW((0..ub)*std_logic) & idx : 0..ub))
|
(lb : lb..lb);
(ub : ub..ub);
(Rename_Vec : POW(POW((0..ub)*std_logic)));
(Rename_Vec2Nat : POW(POW((0..ub)*std_logic)*NAT));
(Rename_Nat2Vec : POW(NAT*POW((0..ub)*std_logic)))|
(lb , ub)
