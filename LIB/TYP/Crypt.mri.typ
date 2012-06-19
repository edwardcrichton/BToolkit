(CRYPT(ss;key) == (ss : seq(CHAR) & key : seq(CHAR) & key : POW(NAT*CHAR)));
(CRYPT_CHECK(rr;key , encryption) == (rr : BOOL & key : seq(CHAR) & key : POW(NAT*CHAR) & encryption : seq(CHAR) & encryption : POW(NAT*CHAR)))
|
true
|
(?)
