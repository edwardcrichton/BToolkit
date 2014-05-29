(Rename_STS_SET_OBJ(mm , nn , pp , qq;?) == (qq : NAT & pp : NAT & nn : NAT & mm : NAT));
(Rename_MEM_FUL_SET_OBJ(bb;?) == (bb : BOOL));
(Rename_OBJ_FUL_SET_OBJ(bb;?) == (bb : BOOL));
(Rename_ANY_SET_OBJ(pp;?) == (pp : Rename_SETOBJ));
(Rename_XST_SET_OBJ(bb;pp) == (bb : BOOL & pp : Rename_SETOBJ));
(Rename_INI_SET_OBJ(?;?) == ?);
(Rename_CRE_SET_OBJ(bb , pp;?) == (pp : Rename_SETOBJ & bb : BOOL));
(Rename_KIL_SET_OBJ(?;qq) == (qq : Rename_SETOBJ));
(Rename_XST_ORD_SET_OBJ(bb;pp , ii) == (bb : BOOL & pp : Rename_SETOBJ & ii : NAT));
(Rename_VAL_SET_OBJ(vv;pp , ii) == (vv : VALUE & ii : NAT & pp : Rename_SETOBJ));
(Rename_CLR_SET_OBJ(?;pp) == (pp : Rename_SETOBJ));
(Rename_UNION_SET_OBJ(bb;ss , tt) == (bb : BOOL & ss : Rename_SETOBJ & tt : Rename_SETOBJ));
(Rename_DIFF_SET_OBJ(?;ss , tt) == (ss : Rename_SETOBJ & tt : Rename_SETOBJ));
(Rename_INTER_SET_OBJ(?;ss , tt) == (ss : Rename_SETOBJ & tt : Rename_SETOBJ));
(Rename_ENT_SET_OBJ(bb;ss , vv) == (bb : BOOL & ss : Rename_SETOBJ & vv : VALUE));
(Rename_RMV_SET_OBJ(?;ss , vv) == (ss : Rename_SETOBJ & vv : VALUE));
(Rename_CPY_SET_OBJ(bb;pp , qq) == (bb : BOOL & pp : Rename_SETOBJ & qq : Rename_SETOBJ));
(Rename_EMP_SET_OBJ(bb;pp) == (bb : BOOL & pp : Rename_SETOBJ));
(Rename_CRD_SET_OBJ(nn;pp) == (nn : NAT & pp : Rename_SETOBJ));
(Rename_INCL_SET_OBJ(bb;tt , ss) == (bb : BOOL & tt : Rename_SETOBJ & ss : Rename_SETOBJ));
(Rename_MBR_SET_OBJ(bb;ss , vv) == (bb : BOOL & ss : Rename_SETOBJ & vv : VALUE));
(Rename_SAV_SET_OBJ(?;?) == ?);
(Rename_RST_SET_OBJ(?;?) == ?);
(Rename_SAVN_SET_OBJ(?;?) == ?);
(Rename_RSTN_SET_OBJ(?;?) == ?);
(Rename_FIRST_SET_OBJ(nn , pp;?) == (pp : Rename_SETOBJ & nn : NAT));
(Rename_NEXT_SET_OBJ(nn , qq;mm , pp) == (qq : Rename_SETOBJ & nn : NAT & mm : NAT & pp : Rename_SETOBJ));
(Rename_OUTPUT_SET_OBJ(?;SS , pp) == (SS : POW(VALUE) & pp : Rename_SETOBJ));
(Rename_INPUT_SET_OBJ(bb;SS , pp , ll) == (bb : BOOL & SS : POW(VALUE) & pp : Rename_SETOBJ & ll : NAT))
|
(given(VALUE));
(maxobj : NAT);
(maxmem : NAT);
(Rename_settok : POW(Rename_SETOBJ));
(Rename_setord : POW(Rename_SETOBJ*seq(VALUE)));
(Rename_setstruct : POW(Rename_SETOBJ*POW(VALUE)))|
(VALUE , maxobj , maxmem)
