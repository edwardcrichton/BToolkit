(Rename_UiAO_OBJ_FUL(bb;?) == (bb : BOOL));
(Rename_UiAO_XST(bb;pp) == (bb : BOOL & pp : BYTE));
(Rename_UiAO_INI(?;?) == ?);
(Rename_UiAO_CRE(bb , pp;?) == (pp : BYTE & bb : BOOL));
(Rename_UiAO_VAL(vv;pp , ii) == (vv : BYTE & pp : BYTE & ii : UNSIGNED));
(Rename_UiAO_NXT(nn;pp) == (nn : UNSIGNED & pp : BYTE));
(Rename_UiAO_EQL(bb;ss , tt) == (bb : BOOL & ss : BYTE & tt : BYTE));
(Rename_UiAO_STO(?;pp , ii , vv) == (pp : BYTE & ii : UNSIGNED & vv : BYTE));
(Rename_UiAO_STO_NXT(?;pp , vv) == (pp : BYTE & vv : BYTE));
(Rename_UiAO_CPY(?;pp , qq) == (pp : BYTE & qq : BYTE));
(Rename_UiAO_FILL(?;pp , vv) == (pp : BYTE & vv : BYTE))
|
(maxobj : NAT);
(ub : NAT);
(given(Rename_ARROBJ));
(Rename_ARROBJ = BYTE);
(Rename_ARROBJ == BYTE);
(Rename_UiAO_arrtok : POW(BYTE));
(Rename_UiAO_nxt : POW(BYTE*NAT));
(Rename_UiAO_arrstruct : POW(BYTE*POW(NAT*BYTE)))|
(maxobj , ub)
