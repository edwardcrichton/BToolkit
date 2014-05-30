(NWL(?;nn) == (nn : NAT));
(BLK(?;nn) == (nn : NAT));
(PUT_NBR(?;nn) == (nn : NAT));
(PUT_NAT(?;nn) == (nn : NAT));
(PUT_INT(?;nn) == (nn : INTEGER));
(PUT_STR(?;ss) == (ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(PUT_CHR(?;cc) == (cc : CHAR));
(PUT_EOT(?;?) == ?);
(PUT_BOOL(?;bb) == (bb : BOOL));
(PUT_BTS(?;bs) == (bs : POW(NAT*BOOL)));
(FLSH(?;?) == ?);
(PUT_NBR_PAD(?;nn , pd) == (nn : NAT & pd : NAT));
(PUT_NAT_PAD(?;nn , pd) == (nn : NAT & pd : NAT));
(PUT_INT_PAD(?;nn , pd) == (nn : INTEGER & pd : NAT));
(PUT_STR_PAD(?;ss , pd) == (ss : seq(CHAR) & ss : POW(NAT*CHAR) & pd : NAT));
(PUT_BOOL_PAD(?;bb , pd) == (bb : BOOL & pd : NAT));
(GET_NBR(mm;nn) == (mm : NAT & nn : NAT));
(GET_NAT(rr;?) == (rr : NAT));
(GET_INT(rr;?) == (rr : INTEGER));
(GET_STR(ss;?) == (ss : seq(CHAR)));
(GET_CHR(cc;?) == (cc : CHAR));
(GET_BOOL(bb;?) == (bb : BOOL));
(GET_BTS(bs;?) == (bs : POW(NAT*BOOL)));
(GET_PROMPT_NBR(mm;ss , nn) == (mm : NAT & ss : seq(CHAR) & ss : POW(NAT*CHAR) & nn : NAT));
(GET_PROMPT_NAT(rr;ss) == (rr : NAT & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(GET_PROMPT_INT(rr;ss) == (rr : INTEGER & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(GET_PROMPT_STR(tt;ss) == (tt : seq(CHAR) & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(GET_PROMPT_CHR(nn;ss) == (nn : CHAR & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(GET_PROMPT_BOOL(rr;ss) == (rr : BOOL & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(GET_PROMPT_BTS(bs;ss) == (bs : POW(NAT*BOOL) & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(REDIR_stdout(rr;file) == (rr : BOOL & file : seq(CHAR) & file : POW(NAT*CHAR)));
(REAPP_stdout(rr;file) == (rr : BOOL & file : seq(CHAR) & file : POW(NAT*CHAR)));
(RESTR_stdout(rr;?) == (rr : BOOL))
|
true
|
(?)
