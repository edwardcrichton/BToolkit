(Rename_STS_STR_OBJ(mm , nn , pp , qq;?) == (qq : NAT & pp : NAT & nn : NAT & mm : NAT));
(Rename_MEM_FUL_STR_OBJ(bb;?) == (bb : BOOL));
(Rename_OBJ_FUL_STR_OBJ(bb;?) == (bb : BOOL));
(Rename_XST_STR_OBJ(bb;pp) == (bb : BOOL & pp : Rename_STROBJ));
(Rename_ANY_STR_OBJ(pp;?) == (pp : Rename_STROBJ));
(Rename_INI_STR_OBJ(?;?) == ?);
(Rename_CRE_STR_OBJ(bb , pp;?) == (pp : Rename_STROBJ & bb : BOOL));
(Rename_NEW_STR_OBJ(bb , pp;nn) == (pp : Rename_STROBJ & bb : BOOL & nn : seq(CHAR) & nn : POW(NAT*CHAR)));
(Rename_KIL_STR_OBJ(?;pp) == (pp : Rename_STROBJ));
(Rename_VAL_STR_OBJ(vv;pp , ii) == (vv : CHAR & ii : NAT & pp : Rename_STROBJ));
(Rename_EMP_STR_OBJ(bb;pp) == (bb : BOOL & pp : Rename_STROBJ));
(Rename_XST_IDX_STR_OBJ(bb;pp , ii) == (bb : BOOL & pp : Rename_STROBJ & ii : NAT));
(Rename_LEN_STR_OBJ(nn;pp) == (nn : NAT & pp : Rename_STROBJ));
(Rename_SMR_STR_OBJ(bb;ss , tt) == (bb : BOOL & ss : Rename_STROBJ & tt : Rename_STROBJ));
(Rename_EQL_STR_OBJ(bb;ss , tt) == (bb : BOOL & ss : Rename_STROBJ & tt : Rename_STROBJ));
(Rename_SUB_STR_OBJ(bb;ss , tt) == (bb : BOOL & ss : Rename_STROBJ & tt : Rename_STROBJ));
(Rename_EQL_LIT_STR_OBJ(bb;tt , nn) == (bb : BOOL & tt : Rename_STROBJ & nn : seq(CHAR) & nn : POW(NAT*CHAR)));
(Rename_XTR_STR_OBJ(ss;pp) == (ss : seq(CHAR) & pp : Rename_STROBJ));
(Rename_CLR_STR_OBJ(?;pp) == (pp : Rename_STROBJ));
(Rename_PSH_STR_OBJ(bb;pp , vv) == (bb : BOOL & pp : Rename_STROBJ & vv : CHAR));
(Rename_KEP_STR_OBJ(?;pp , ii) == (ii : NAT & pp : Rename_STROBJ));
(Rename_CUT_STR_OBJ(?;pp , ii) == (ii : NAT & pp : Rename_STROBJ));
(Rename_REV_STR_OBJ(?;pp) == (pp : Rename_STROBJ));
(Rename_SWP_STR_OBJ(?;pp , ii , jj) == (ii : NAT & jj : NAT & pp : Rename_STROBJ));
(Rename_POP_STR_OBJ(?;pp) == (pp : Rename_STROBJ));
(Rename_STO_STR_OBJ(?;pp , ii , vv) == (ii : NAT & pp : Rename_STROBJ & vv : CHAR));
(Rename_APP_STR_OBJ(bb;pp , qq) == (bb : BOOL & pp : Rename_STROBJ & qq : Rename_STROBJ));
(Rename_CPY_STR_OBJ(bb;pp , qq) == (bb : BOOL & pp : Rename_STROBJ & qq : Rename_STROBJ));
(Rename_OVR_STR_OBJ(bb;pp , qq) == (bb : BOOL & pp : Rename_STROBJ & qq : Rename_STROBJ));
(Rename_SAV_STR_OBJ(?;?) == ?);
(Rename_RST_STR_OBJ(?;?) == ?);
(Rename_SAVN_STR_OBJ(?;?) == ?);
(Rename_RSTN_STR_OBJ(?;?) == ?);
(Rename_FIRST_STR_OBJ(nn , pp;?) == (pp : Rename_STROBJ & nn : NAT));
(Rename_NEXT_STR_OBJ(nn , qq;mm , pp) == (qq : Rename_STROBJ & nn : NAT & mm : NAT & pp : Rename_STROBJ))
|
(maxobj : NAT);
(maxmem : NAT);
(Rename_strmem : NAT);
(Rename_strtok : POW(Rename_STROBJ));
(Rename_strstruct : POW(Rename_STROBJ*seq(CHAR)))|
(maxobj , maxmem)
