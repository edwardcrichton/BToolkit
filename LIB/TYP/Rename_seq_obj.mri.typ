(Rename_STS_SEQ_OBJ(mm , nn , pp , qq;?) == (qq : NAT & pp : NAT & nn : NAT & mm : NAT));
(Rename_MEM_FUL_SEQ_OBJ(bb;?) == (bb : BOOL));
(Rename_OBJ_FUL_SEQ_OBJ(bb;?) == (bb : BOOL));
(Rename_XST_SEQ_OBJ(bb;pp) == (bb : BOOL & pp : Rename_SEQOBJ));
(Rename_INI_SEQ_OBJ(?;?) == ?);
(Rename_ANY_SEQ_OBJ(pp;?) == (pp : Rename_SEQOBJ));
(Rename_CRE_SEQ_OBJ(bb , pp;?) == (pp : Rename_SEQOBJ & bb : BOOL));
(Rename_KIL_SEQ_OBJ(?;pp) == (pp : Rename_SEQOBJ));
(Rename_VAL_SEQ_OBJ(vv;pp , ii) == (vv : VALUE & ii : NAT & pp : Rename_SEQOBJ));
(Rename_XST_IDX_SEQ_OBJ(bb;pp , ii) == (bb : BOOL & pp : Rename_SEQOBJ & ii : NAT));
(Rename_LEN_SEQ_OBJ(nn;pp) == (nn : NAT & pp : Rename_SEQOBJ));
(Rename_EMP_SEQ_OBJ(bb;pp) == (bb : BOOL & pp : Rename_SEQOBJ));
(Rename_EQL_SEQ_OBJ(bb;ss , tt) == (bb : BOOL & ss : Rename_SEQOBJ & tt : Rename_SEQOBJ));
(Rename_MBR_SEQ_OBJ(bb , ii;tt , vv) == (ii : NAT & bb : BOOL & tt : Rename_SEQOBJ & vv : VALUE));
(Rename_PSH_SEQ_OBJ(bb;pp , vv) == (bb : BOOL & pp : Rename_SEQOBJ & vv : VALUE));
(Rename_CLR_SEQ_OBJ(?;pp) == (pp : Rename_SEQOBJ));
(Rename_KEP_SEQ_OBJ(?;pp , ii) == (ii : NAT & pp : Rename_SEQOBJ));
(Rename_CUT_SEQ_OBJ(?;pp , ii) == (ii : NAT & pp : Rename_SEQOBJ));
(Rename_REV_SEQ_OBJ(?;pp) == (pp : Rename_SEQOBJ));
(Rename_SWP_SEQ_OBJ(?;pp , ii , jj) == (ii : NAT & jj : NAT & pp : Rename_SEQOBJ));
(Rename_POP_SEQ_OBJ(?;pp) == (pp : Rename_SEQOBJ));
(Rename_STO_SEQ_OBJ(?;pp , ii , vv) == (ii : NAT & pp : Rename_SEQOBJ & vv : VALUE));
(Rename_APP_SEQ_OBJ(bb;pp , qq) == (bb : BOOL & pp : Rename_SEQOBJ & qq : Rename_SEQOBJ));
(Rename_CPY_SEQ_OBJ(bb;pp , qq) == (bb : BOOL & pp : Rename_SEQOBJ & qq : Rename_SEQOBJ));
(Rename_OVR_SEQ_OBJ(bb;pp , qq) == (bb : BOOL & pp : Rename_SEQOBJ & qq : Rename_SEQOBJ));
(Rename_SAV_SEQ_OBJ(?;?) == ?);
(Rename_RST_SEQ_OBJ(?;?) == ?);
(Rename_SAVN_SEQ_OBJ(?;?) == ?);
(Rename_RSTN_SEQ_OBJ(?;?) == ?);
(Rename_FIRST_SEQ_OBJ(nn , pp;?) == (pp : Rename_SEQOBJ & nn : NAT));
(Rename_NEXT_SEQ_OBJ(nn , qq;mm , pp) == (qq : Rename_SEQOBJ & nn : NAT & mm : NAT & pp : Rename_SEQOBJ));
(Rename_OUTPUT_SEQ_OBJ(?;SS , pp) == (SS : POW(VALUE) & pp : Rename_SEQOBJ));
(Rename_INPUT_SEQ_OBJ(bb;SS , pp , ll) == (bb : BOOL & SS : POW(VALUE) & pp : Rename_SEQOBJ & ll : NAT))
|
(given(VALUE));
(maxobj : NAT);
(maxmem : NAT);
(Rename_seqmem : NAT);
(Rename_seqtok : POW(Rename_SEQOBJ));
(Rename_seqstruct : POW(Rename_SEQOBJ*seq(VALUE)))|
(VALUE , maxobj , maxmem)
