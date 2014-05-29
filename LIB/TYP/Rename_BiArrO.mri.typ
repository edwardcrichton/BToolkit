(Rename_BiAO_OBJ_FUL(bb;?) == (bb: BOOL));
(Rename_BiAO_XST(bb;pp) == (bb: BOOL & pp: Rename_ARROBJ));
(Rename_BiAO_INI(?;?) == ?);
(Rename_BiAO_CRE(bb,pp;?) == (pp: Rename_ARROBJ & bb: BOOL));
(Rename_BiAO_VAL(vv;pp,ii) == (vv: BYTE & pp: Rename_ARROBJ & ii: UNSIGNED));
(Rename_Rename_BiAO_nxt(nn;pp) == (nn: UNSIGNED & pp: Rename_ARROBJ));
(Rename_BiAO_EQL(bb;ss,tt) == (bb: BOOL & ss: Rename_ARROBJ & tt: Rename_ARROBJ));
(Rename_BiAO_STO(?;pp,ii,vv) == (pp: Rename_ARROBJ & ii: UNSIGNED & vv: BYTE));
(Rename_BiAO_STO_NXT(?;pp,vv) == (pp: Rename_ARROBJ & vv: BYTE));
(Rename_BiAO_CPY(?;pp,qq) == (pp: Rename_ARROBJ & qq: Rename_ARROBJ));
(Rename_BiAO_FILL(?;pp,vv) == (pp: Rename_ARROBJ & vv: BYTE))
|
(maxobj: NAT);
(ub: NAT);
(given(Rename_ARROBJ));
(Rename_lb: UNSIGNED);
(Rename_BiAO_arrtok: POW(Rename_ARROBJ));
(Rename_BiAO_arr: POW(NAT*BYTE));
(Rename_BiAO_nxt: POW(Rename_ARROBJ*NAT));
(Rename_BiAO_arrstruct: POW(Rename_ARROBJ*POW(NAT*BYTE)))|
(maxobj,ub)
