(Rename_STS_STR_OBJ(mm , nn , pp , qq;?) == (qq : NAT & pp : NAT & nn : NAT & mm : NAT));
(Rename_MEM_FUL_STR_OBJ(bb;?) == (bb : BOOL));
(Rename_OBJ_FUL_STR_OBJ(bb;?) == (bb : BOOL));
(Rename_ANY_STR_OBJ(pp;?) == (pp : Rename_STROBJ));
(Rename_CRE_STR_OBJ(bb , pp;?) == (pp : Rename_STROBJ & bb : BOOL));
(Rename_NEW_STR_OBJ(bb , pp;nn) == (pp : Rename_STROBJ & bb : BOOL & nn : seq(CHAR) & nn : POW(NAT*CHAR)));
(Rename_KIL_STR_OBJ(?;pp) == (pp : Rename_STROBJ));
(Rename_VAL_STR_OBJ(vv;pp , ii) == (vv : CHAR & ii : NAT & pp : Rename_STROBJ));
(Rename_EMP_STR_OBJ(bb;pp) == (bb : BOOL & pp : Rename_STROBJ));
(Rename_LEN_STR_OBJ(nn;pp) == (nn : NAT & pp : Rename_STROBJ));
(Rename_EQL_LIT_STR_OBJ(bb;tt , nn) == (bb : BOOL & tt : Rename_STROBJ & nn : seq(CHAR) & nn : POW(NAT*CHAR)));
(Rename_XTR_STR_OBJ(ss;pp) == (ss : seq(CHAR) & pp : Rename_STROBJ));
(Rename_CLR_STR_OBJ(?;pp) == (pp : Rename_STROBJ));
(Rename_PSH_STR_OBJ(bb;pp , vv) == (bb : BOOL & pp : Rename_STROBJ & vv : CHAR));
(Rename_KEP_STR_OBJ(?;pp , ii) == (ii : NAT & pp : Rename_STROBJ));
(Rename_POP_STR_OBJ(?;pp) == (pp : Rename_STROBJ));
(Rename_STO_STR_OBJ(?;pp , ii , vv) == (ii : NAT & pp : Rename_STROBJ & vv : CHAR));
(Rename_APP_STR_OBJ(bb;pp , qq) == (bb : BOOL & pp : Rename_STROBJ & qq : Rename_STROBJ));
(Rename_SAV_STR_OBJ(?;?) == ?);
(Rename_RST_STR_OBJ(?;?) == ?);
(Rename_SAVN_STR_OBJ(?;?) == ?);
(Rename_RSTN_STR_OBJ(?;?) == ?)
|
(maxobj : NAT);
(maxmem : NAT);
(Rename_strmem : NAT);
(Rename_strtok : POW(Rename_STROBJ));
(Rename_strstruct : POW(Rename_STROBJ*seq(CHAR)))|
(maxobj , maxmem)
