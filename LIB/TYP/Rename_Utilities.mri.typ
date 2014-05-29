(Rename_RestorePreviousData(rep;sysname , op) == (rep : BOOL & sysname : seq(CHAR) & sysname : POW(NAT*CHAR) & op : NAT));
(OBJ_TO_NAT(nn;obj) == (nn : NAT & obj : OBJ));
(OBJ_TO_STR(ss;obj) == (ss : seq(CHAR) & obj : OBJ))
|
(given(OBJ))|
(OBJ)
