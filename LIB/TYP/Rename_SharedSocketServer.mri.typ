(Rename_INIT(rep;lockfile , port , bufsavefile) == (rep : BOOL & lockfile : seq(CHAR) & lockfile : POW(NAT*CHAR) & port : NAT & bufsavefile : seq(CHAR) & bufsavefile : POW(NAT*CHAR)));
(Rename_ACCEPT(rep;?) == (rep : BOOL));
(Rename_READ(rep , pp;?) == (pp : NAT & rep : BOOL));
(Rename_WRITE(rep;?) == (rep : BOOL));
(Rename_CLOSE(rep;?) == (rep : BOOL));
(Rename_GET_TOK(tok;toksize) == (tok : TOK & toksize : NAT));
(Rename_GET_STR(ss;?) == (ss : seq(CHAR)));
(Rename_PUT_TOK(?;tok , toksize) == (tok : TOK & toksize : NAT));
(Rename_PUT_STR(?;ss) == (ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(Rename_SET_IN_PTR(?;ptr) == (ptr : NAT));
(Rename_GET_IN_PTR(ptr;?) == (ptr : NAT));
(Rename_SET_OUT_PTR(?;ptr) == (ptr : NAT));
(Rename_GET_OUT_PTR(ptr;?) == (ptr : NAT));
(Rename_GET_OUT_SIZE(sz;?) == (sz : NAT));
(Rename_PUT_FILE(rep;filename) == (rep : BOOL & filename : seq(CHAR) & filename : POW(NAT*CHAR)));
(Rename_SAV_BUF(rep , num_saves;?) == (num_saves : NAT & rep : BOOL));
(Rename_SAV_RMV(?;?) == ?);
(Rename_RST_BUF(rep;?) == (rep : BOOL));
(Rename_NXT_BUF(rep;?) == (rep : BOOL));
(Rename_PrintStats(rep , filename;?) == (filename : seq(CHAR) & rep : BOOL))
|
(given(TOK));
(insize : NAT);
(outsize : NAT)|
(TOK , insize , outsize)
