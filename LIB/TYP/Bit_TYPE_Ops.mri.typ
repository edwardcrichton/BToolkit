(NO_BITS(ss;?) == (ss : POW(NAT*BOOL)));
(LFT_BTS(ss;tt , nn) == (ss : POW(NAT*BOOL) & tt : POW(NAT*BOOL) & nn : NAT));
(RHT_BTS(ss;tt , nn) == (ss : POW(NAT*BOOL) & tt : POW(NAT*BOOL) & nn : NAT));
(CPL_BTS(ss;tt) == (ss : POW(NAT*BOOL) & tt : POW(NAT*BOOL)));
(LND_BTS(ss;tt , uu) == (ss : POW(NAT*BOOL) & tt : POW(NAT*BOOL) & uu : POW(NAT*BOOL)));
(LOR_BTS(ss;tt , uu) == (ss : POW(NAT*BOOL) & tt : POW(NAT*BOOL) & uu : POW(NAT*BOOL)));
(LXR_BTS(ss;tt , uu) == (ss : POW(NAT*BOOL) & tt : POW(NAT*BOOL) & uu : POW(NAT*BOOL)));
(MSK_BTS(ss;mm , nn) == (ss : POW(NAT*BOOL) & mm : NAT & nn : NAT));
(VMS_BTS(ss;bb , mm , nn) == (ss : POW(NAT*BOOL) & bb : POW(NAT*BOOL) & mm : NAT & nn : NAT));
(MMS_BTS(ss;bb , mm , nn , vv) == (ss : POW(NAT*BOOL) & bb : POW(NAT*BOOL) & mm : NAT & nn : NAT & vv : POW(NAT*BOOL)));
(VAL_BTS(ss;bb , nn) == (ss : BOOL & bb : POW(NAT*BOOL) & nn : NAT));
(STO_BTS(ss;bb , nn , vv) == (ss : POW(NAT*BOOL) & bb : POW(NAT*BOOL) & nn : NAT & vv : BOOL))
|
true
|
(?)
