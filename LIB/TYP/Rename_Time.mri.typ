(Rename_GetTime(time;?) == (time : NAT));
(Rename_StartTimer(start_time;interval) == (start_time : NAT & interval : NAT));
(Rename_CheckTimer(expired;?) == (expired : BOOL))
|
(Rename_expire : NAT);
(Rename_time : NAT)|
(?)
