(Rename_INIT(rep;ipaddress , port) == (rep : BOOL & ipaddress : seq(CHAR) & ipaddress : POW(NAT*CHAR) & port : NAT));
(Rename_CONNECT(rep;?) == (rep : BOOL));
(Rename_WRITE(rep;?) == (rep : BOOL));
(Rename_READ(rep , pp;?) == (pp : NAT & rep : BOOL));
(Rename_CLOSE(rep;?) == (rep : BOOL));
(Rename_GET_TOK(tok;toksize) == (tok : TOK & toksize : NAT));
(Rename_GET_STR(ss;?) == (ss : seq(CHAR)));
(Rename_GET_FIL(rep , filesize;filename) == (filesize : NAT & rep : BOOL & filename : seq(CHAR) & filename : POW(NAT*CHAR)));
(Rename_PUT_TOK(?;tok , toksize) == (tok : TOK & toksize : NAT));
(Rename_PUT_STR(?;ss) == (ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(Rename_SET_IN_PTR(?;ptr) == (ptr : NAT));
(Rename_GET_IN_PTR(ptr;?) == (ptr : NAT));
(Rename_SET_OUT_PTR(?;ptr) == (ptr : NAT));
(Rename_GET_OUT_PTR(ptr;?) == (ptr : NAT));
(Rename_GET_OUT_SIZE(sz;?) == (sz : NAT))
|
(given(TOK));
(insize : NAT);
(outsize : NAT);
(outbufsize : NAT);
(outptr : NAT);
(in : NAT);
(inptr : NAT)|
(TOK , insize , outsize)
