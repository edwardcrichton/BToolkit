(Rename_BAO_OBJ_FUL(bb;?) == (bb: BOOL));
(Rename_BAO_XST(bb;pp) == (bb: BOOL & pp: ARROBJ));
(Rename_BAO_INI(?;?) == ?);
(Rename_BAO_CRE(bb,pp;?) == (pp: ARROBJ & bb: BOOL));
(Rename_BAO_VAL(vv;pp,ii) == (vv: BYTE & pp: ARROBJ & ii: UNSIGNED));
(Rename_BAO_NXT(nn;pp) == (nn: UNSIGNED & pp: ARROBJ));
(Rename_BAO_EQL(bb;ss,tt) == (bb: BOOL & ss: ARROBJ & tt: ARROBJ));
(Rename_BAO_STO(?;pp,ii,vv) == (pp: ARROBJ & ii: UNSIGNED & vv: BYTE));
(Rename_BAO_STO_NXT(?;pp,vv) == (pp: ARROBJ & vv: BYTE));
(Rename_BAO_CPY(?;pp,qq) == (pp: ARROBJ & qq: ARROBJ));
(Rename_BAO_FILL(?;pp,vv) == (pp: ARROBJ & vv: BYTE))
|
(maxobj: NAT);
(ub: NAT);
(given(ARROBJ));
(lb: UNSIGNED);
(BAO_arrtok: POW(ARROBJ));
(BAO_arr: POW(NAT*BYTE));
(BAO_nxt: POW(ARROBJ*NAT));
(BAO_arrstruct: POW(ARROBJ*POW(NAT*BYTE)));
(bb: BOOL);
(ARROBJ = ARROBJ)
|
(maxobj,ub)
