(Rename_GET_TOK(tt;?) == (tt : TOKEN));
(Rename_GET_PROMPT_TOK(tt;ss) == (tt : TOKEN & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(Rename_PUT_TOK(?;tt) == (tt : TOKEN));
(Rename_GET_ACT_TOK(tt;SS) == (tt : TOKEN & SS : POW(TOKEN)));
(Rename_GET_PROMPT_ACT_TOK(tt;SS , ss) == (tt : TOKEN & SS : POW(TOKEN) & ss : seq(CHAR) & ss : POW(NAT*CHAR)));
(Rename_PUT_ACT_TOK(?;SS , tt) == (tt : TOKEN & SS : POW(TOKEN)))
|
(given(TOKEN))|
(TOKEN)
