(Rename_BiRcd_RST(?;?) == ?);
(Rename_BiRcd_IDX(bb;idx) == (bb : BOOL & idx : BYTE));
(Rename_BiRcd_FULL(bb;?) == (bb : BOOL));
(Rename_BiRcd_CRE(rr;?) == (rr : Rename_BiRcd));
(Rename_BiRcd_KILL(?;rr) == (rr : Rename_BiRcd));
(Rename_BiRcd_VLD(bb;rr) == (bb : BOOL & rr : Rename_BiRcd));
(Rename_BiRcd_STO(?;rr , idx , vv) == (rr : Rename_BiRcd & idx : BYTE & vv : VALUE));
(Rename_BiRcd_VAL(vv;rr , idx) == (vv : VALUE & rr : Rename_BiRcd & idx : BYTE))
|
(given(VALUE));
(numfld : NAT);
(maxrcd : NAT);
(given(Rename_BiRcd));
(Rename_rcd : POW(Rename_BiRcd));
(Rename_rcd_fnc : POW(Rename_BiRcd*POW(NAT*VALUE)))|
(VALUE , numfld , maxrcd)
