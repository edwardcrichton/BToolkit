(Rename_GET_SEG(rr;?) == (rr: SEGMENT));
(Rename_GET_PROMPT_SEG(rr;ss) == (rr: SEGMENT & ss: seq(CHAR) & ss: POW(NAT*CHAR)));
(Rename_PUT_SEG(?;dd) == (dd: SEGMENT))
|
(given(SEGMENT))|
(SEGMENT)
