(Rename_INIT(rep;ipaddress , port) == (rep : BOOL & ipaddress : seq(CHAR) & ipaddress : POW(NAT*CHAR) & port : NAT));
(Rename_CONNECT(rep;?) == (rep : BOOL));
(Rename_WRITE(rep;?) == (rep : BOOL));
(Rename_READ(rep , pp;?) == (pp : NAT & rep : BOOL));
(Rename_CLOSE(rep;?) == (rep : BOOL));
(Rename_GET_TOK(rep , tok;toksize) == (tok : TOK & rep : BOOL & toksize : NAT));
(Rename_GET_STR(rep , ss;?) == (ss : seq(CHAR) & rep : BOOL));
(Rename_GET_FIL(rep , filesize;filename) == (filesize : NAT & rep : BOOL & filename : seq(CHAR) & filename : POW(NAT*CHAR)));
(Rename_PUT_TOK(rep;tok , toksize) == (rep : BOOL & tok : TOK & toksize : NAT));
(Rename_PUT_STR(rep;ss) == (rep : BOOL & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(Rename_SET_IN_PTR(?;ptr) == (ptr : NAT));
(Rename_GET_IN_PTR(ptr;?) == (ptr : NAT));
(Rename_SET_OUT_PTR(?;ptr) == (ptr : NAT));
(Rename_GET_OUT_PTR(ptr;?) == (ptr : NAT))
|
(given(TOK));
(default_inbufsize : NAT);
(default_outbufsize : NAT);
(outptr : NAT);
(in : NAT);
(inptr : NAT)|
(TOK , default_inbufsize , default_outbufsize)
