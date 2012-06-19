(Rename_MEM_FUL_FSTR_OBJ(bb;?) == (bb : BOOL));
(Rename_OBJ_FUL_FSTR_OBJ(bb;?) == (bb : BOOL));
(Rename_XST_FSTR_OBJ(bb;pp) == (bb : BOOL & pp : Rename_FSTROBJ));
(Rename_ANY_FSTR_OBJ(pp;?) == (pp : Rename_FSTROBJ));
(Rename_INI_FSTR_OBJ(?;?) == ?);
(Rename_CRE_FSTR_OBJ(bb , pp;?) == (pp : Rename_FSTROBJ & bb : BOOL));
(Rename_NEW_FSTR_OBJ(bb , pp;nn) == (pp : Rename_FSTROBJ & bb : BOOL & nn : seq(NAT) & nn : POW(NAT*NAT)));
(Rename_KIL_FSTR_OBJ(?;pp) == (pp : Rename_FSTROBJ));
(Rename_VAL_FSTR_OBJ(vv;pp , ii) == (vv : NAT & ii : NAT & pp : Rename_FSTROBJ));
(Rename_EMP_FSTR_OBJ(bb;pp) == (bb : BOOL & pp : Rename_FSTROBJ));
(Rename_XST_IDX_FSTR_OBJ(bb;pp , ii) == (bb : BOOL & pp : Rename_FSTROBJ & ii : NAT));
(Rename_LEN_FSTR_OBJ(nn;pp) == (nn : NAT & pp : Rename_FSTROBJ));
(Rename_SMR_FSTR_OBJ(bb;ss , tt) == (bb : BOOL & ss : Rename_FSTROBJ & tt : Rename_FSTROBJ));
(Rename_EQL_FSTR_OBJ(bb;ss , tt) == (bb : BOOL & ss : Rename_FSTROBJ & tt : Rename_FSTROBJ));
(Rename_EQL_LIT_FSTR_OBJ(bb;tt , nn) == (bb : BOOL & tt : Rename_FSTROBJ & nn : seq(NAT) & nn : POW(NAT*NAT)));
(Rename_XTR_FSTR_OBJ(ss;pp) == (ss : seq(NAT) & pp : Rename_FSTROBJ));
(Rename_CLR_FSTR_OBJ(?;pp) == (pp : Rename_FSTROBJ));
(Rename_PSH_FSTR_OBJ(bb;pp , vv) == (bb : BOOL & pp : Rename_FSTROBJ & vv : NAT));
(Rename_KEP_FSTR_OBJ(?;pp , ii) == (ii : NAT & pp : Rename_FSTROBJ));
(Rename_CUT_FSTR_OBJ(?;pp , ii) == (ii : NAT & pp : Rename_FSTROBJ));
(Rename_REV_FSTR_OBJ(?;pp) == (pp : Rename_FSTROBJ));
(Rename_SWP_FSTR_OBJ(?;pp , ii , jj) == (ii : NAT & jj : NAT & pp : Rename_FSTROBJ));
(Rename_POP_FSTR_OBJ(?;pp) == (pp : Rename_FSTROBJ));
(Rename_STO_FSTR_OBJ(?;pp , ii , vv) == (ii : NAT & pp : Rename_FSTROBJ & vv : NAT));
(Rename_APP_FSTR_OBJ(bb;pp , qq) == (bb : BOOL & pp : Rename_FSTROBJ & qq : Rename_FSTROBJ));
(Rename_CPY_FSTR_OBJ(bb;pp , qq) == (bb : BOOL & pp : Rename_FSTROBJ & qq : Rename_FSTROBJ));
(Rename_OVR_FSTR_OBJ(bb;pp , qq) == (bb : BOOL & pp : Rename_FSTROBJ & qq : Rename_FSTROBJ));
(Rename_SAV_FSTR_OBJ(?;?) == ?);
(Rename_RST_FSTR_OBJ(?;?) == ?);
(Rename_SAVN_FSTR_OBJ(?;?) == ?);
(Rename_RSTN_FSTR_OBJ(?;?) == ?);
(Rename_FIRST_FSTR_OBJ(nn , pp;?) == (pp : Rename_FSTROBJ & nn : NAT));
(Rename_NEXT_FSTR_OBJ(nn , qq;mm , pp) == (qq : Rename_FSTROBJ & nn : NAT & mm : NAT & pp : Rename_FSTROBJ))
|
(maxobj : NAT);
(maxmem : NAT);
(Rename_fstrmem : NAT);
(Rename_fstrtok : POW(Rename_FSTROBJ));
(Rename_fstrstruct : POW(Rename_FSTROBJ*seq(NAT)))|
(maxobj , maxmem)
