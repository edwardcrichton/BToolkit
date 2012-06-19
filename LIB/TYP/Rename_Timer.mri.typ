(Rename_GetCurTime(time;?) == (time : NAT));
(Rename_StoTime(?;time) == (time : NAT));
(Rename_GetStoTime(time;?) == (time : NAT));
(Rename_StartTimer(exp_time;interval) == (exp_time : NAT & interval : NAT));
(Rename_CheckTimer(expired;?) == (expired : BOOL));
(Rename_GetCurYearMonthDay(cur_ymd;?) == (cur_ymd : NAT));
(Rename_IncYearMonthDay(inc_ymd;ymd , days) == (inc_ymd : NAT & ymd : NAT & days : NAT))
|
(Rename_exp_time : NAT);
(Rename_sto_time : NAT);
(Rename_cur_time : NAT)|
(?)
