(Rename_UiAO1_RST(?;?) == ?);
(Rename_UiAO1_VAL(vv;ii) == (vv : BYTE & ii : UNSIGNED));
(Rename_UiAO1_NXT(nn;?) == (nn : UNSIGNED));
(Rename_UiAO1_STO(?;ii , vv) == (ii : UNSIGNED & vv : BYTE));
(Rename_UiAO1_STO_NXT(?;vv) == (vv : BYTE));
(Rename_UiAO1_FILL(?;vv) == (vv : BYTE))
|
(ub : NAT);
(init_elem : NAT);
(Rename_UiAO1_nxt : NAT);
(Rename_UiAO1_arr : POW(NAT*BYTE))|
(ub , init_elem)
