(Rename_OPEN_READ(rep;filename) == (rep : BOOL & filename : seq(CHAR) & filename : POW(NAT*CHAR)));
(Rename_OPEN_WRITE(rep;filename) == (rep : BOOL & filename : seq(CHAR) & filename : POW(NAT*CHAR)));
(Rename_OPEN_APPEND(rep;filename) == (rep : BOOL & filename : seq(CHAR) & filename : POW(NAT*CHAR)));
(Rename_CLOSE(rep;?) == (rep : BOOL));
(Rename_PUT_STR(rep;ss) == (rep : BOOL & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(Rename_PUT_CHAR(rep;cc) == (rep : BOOL & cc : CHAR));
(Rename_PUT_BLK(rep;nn) == (rep : BOOL & nn : NAT));
(Rename_PUT_NWL(rep;nn) == (rep : BOOL & nn : NAT));
(Rename_PUT_NAT(rep;nn) == (rep : BOOL & nn : NAT));
(Rename_PUT_TOK(rep;tt) == (rep : BOOL & tt : TOKEN));
(Rename_GET_STR(rep , ss;?) == (ss : seq(CHAR) & rep : BOOL));
(Rename_GET_CHAR(rep , cc;?) == (cc : CHAR & rep : BOOL));
(Rename_GET_NAT(rep , nn;?) == (nn : NAT & rep : BOOL));
(Rename_GET_TOK(rep , tt;?) == (tt : TOKEN & rep : BOOL));
(Rename_FLUSH(rep;?) == (rep : BOOL))
|
(given(TOKEN))|
(TOKEN)
