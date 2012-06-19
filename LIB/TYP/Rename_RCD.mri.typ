(Rename_RCD_IDX(bb;idx) == (bb: BOOL & idx: BYTE));
(Rename_RCD_FULL(bb;?) == (bb: BOOL));
(Rename_RCD_CRE(rr;?) == (rr: Rename_RCD));
(Rename_RCD_KILL(?;rr) == (rr: Rename_RCD));
(Rename_RCD_DEF(bb;rr) == (bb: BOOL & rr: Rename_RCD));
(Rename_RCD_STO(?;rr,idx,vv) == (rr: Rename_RCD & idx: BYTE & vv: VALUE));
(Rename_RCD_VAL(vv;rr,idx) == (vv: VALUE & rr: Rename_RCD & idx: BYTE))
|
(given(VALUE));
(maxfld: NAT);
(maxrcd: NAT);
(given(Rename_RCD));
(Rename_rcd: POW(Rename_RCD));
(Rename_rcd_fnc: POW(Rename_RCD*POW(NAT*VALUE)))
|
(VALUE,maxfld,maxrcd)
