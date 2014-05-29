(Rename_STS_FNC_OBJ(mm , nn;?) == (nn : NAT & mm : NAT));
(Rename_FUL_FNC_OBJ(bb;?) == (bb : BOOL));
(Rename_TST_FLD_FNC_OBJ(bb;ii) == (bb : BOOL & ii : NAT));
(Rename_ANY_FNC_OBJ(vv;?) == (vv : Rename_FNCOBJ));
(Rename_CRE_FNC_OBJ(bb , pp;?) == (pp : Rename_FNCOBJ & bb : BOOL));
(Rename_KIL_FNC_OBJ(?;ff) == (ff : Rename_FNCOBJ));
(Rename_INI_FNC_OBJ(?;?) == ?);
(Rename_XST_FNC_OBJ(bb;pp) == (bb : BOOL & pp : Rename_FNCOBJ));
(Rename_DEF_FNC_OBJ(bb;ff , ii) == (bb : BOOL & ff : Rename_FNCOBJ & ii : NAT));
(Rename_VAL_FNC_OBJ(vv;ff , ii) == (vv : VALUE & ii : NAT & ff : Rename_FNCOBJ));
(Rename_STO_FNC_OBJ(?;ff , ii , vv) == (ff : Rename_FNCOBJ & ii : NAT & vv : VALUE));
(Rename_RMV_FNC_OBJ(?;ff , ii) == (ff : Rename_FNCOBJ & ii : NAT));
(Rename_SAV_FNC_OBJ(?;?) == ?);
(Rename_RST_FNC_OBJ(?;?) == ?);
(Rename_SAVN_FNC_OBJ(?;?) == ?);
(Rename_RSTN_FNC_OBJ(?;?) == ?);
(Rename_FIRST_FNC_OBJ(nn , pp;?) == (pp : Rename_FNCOBJ & nn : NAT));
(Rename_NEXT_FNC_OBJ(nn , qq;mm , pp) == (qq : Rename_FNCOBJ & nn : NAT & mm : NAT & pp : Rename_FNCOBJ));
(Rename_MOV_FFNC_OBJ(?;ff , gg , ii , jj , ll) == (ff : Rename_FNCOBJ & gg : Rename_FNCOBJ & ii : NAT & jj : NAT & ll : NAT));
(Rename_OVR_FFNC_OBJ(?;ff , ii , ll , aa) == (ff : Rename_FNCOBJ & ii : NAT & ll : NAT & aa : seq(CHAR) & aa : POW(NAT*CHAR)));
(Rename_OVR_LIT_FFNC_OBJ(?;ff , ii , ll , aa) == (ff : Rename_FNCOBJ & ii : NAT & ll : NAT & aa : seq(CHAR) & aa : POW(NAT*CHAR)));
(Rename_XTR_FFNC_OBJ(vv;ff , ii , ll) == (vv : seq(CHAR) & ff : Rename_FNCOBJ & ii : NAT & ll : NAT));
(Rename_EQL_FFNC_OBJ(bb;ff , ii , ll , vv) == (bb : BOOL & ff : Rename_FNCOBJ & ii : NAT & ll : NAT & vv : seq(CHAR) & vv : POW(NAT*CHAR)))
|
(given(VALUE));
(rcdsiz : NAT);
(maxobj : NAT);
(Rename_UnPack : POW(POW(NAT*VALUE)*seq(CHAR)));
(Rename_CHARperWORD : NAT);
(Rename_fnctok : POW(Rename_FNCOBJ));
(Rename_locate : POW(NAT*Rename_FNCOBJ));
(Rename_fncstruct : POW(Rename_FNCOBJ*POW(NAT*VALUE)))|
(VALUE , rcdsiz , maxobj)
