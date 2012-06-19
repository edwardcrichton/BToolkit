(Rename_UiRcd_RST(?;?) == ?);
(Rename_UiRcd_IDX(bb;idx) == (bb : BOOL & idx : UNSIGNED));
(Rename_UiRcd_FULL(bb;?) == (bb : BOOL));
(Rename_UiRcd_CRE(rr;?) == (rr : Rename_UiRcd));
(Rename_UiRcd_KILL(?;rr) == (rr : Rename_UiRcd));
(Rename_UiRcd_VLD(bb;rr) == (bb : BOOL & rr : Rename_UiRcd));
(Rename_UiRcd_STO(?;rr , idx , vv) == (rr : Rename_UiRcd & idx : UNSIGNED & vv : VALUE));
(Rename_UiRcd_VAL(vv;rr , idx) == (vv : VALUE & rr : Rename_UiRcd & idx : UNSIGNED))
|
(given(VALUE));
(numfld : NAT);
(maxrcd : NAT);
(given(Rename_UiRcd));
(Rename_rcd : POW(Rename_UiRcd));
(Rename_rcd_fnc : POW(Rename_UiRcd*POW(NAT*VALUE)))|
(VALUE , numfld , maxrcd)
