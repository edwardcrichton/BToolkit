(Rename_NO_BITS(ss;?) == (ss : POW(NAT*BOOL)));
(Rename_LND_BTS(ss;tt , uu) == (ss : POW(NAT*BOOL) & tt : POW(NAT*BOOL) & uu : POW(NAT*BOOL)));
(Rename_LOR_BTS(ss;tt , uu) == (ss : POW(NAT*BOOL) & tt : POW(NAT*BOOL) & uu : POW(NAT*BOOL)));
(Rename_LXR_BTS(ss;tt , uu) == (ss : POW(NAT*BOOL) & tt : POW(NAT*BOOL) & uu : POW(NAT*BOOL)));
(Rename_VAL_BTS(ss;bb , nn) == (ss : BOOL & bb : POW(NAT*BOOL) & nn : NAT));
(Rename_STO_BTS(ss;bb , nn , vv) == (ss : POW(NAT*BOOL) & bb : POW(NAT*BOOL) & nn : NAT & vv : BOOL))
|
(strsize : NAT);
(given(Rename_BITS));
(bnd : POW(BOOL*BOOL*BOOL));
(bor : POW(BOOL*BOOL*BOOL));
(bxr : POW(BOOL*BOOL*BOOL));
(Rename_BITS = POW(NAT*BOOL));
(Rename_BITS == POW(NAT*BOOL))|
(strsize)
