MACHINE               Rename_Timer

SEES                  Bool_TYPE, Scalar_TYPE

VARIABLES             Rename_cur_time, Rename_sto_time, Rename_exp_time

/*
  Rename_cur_time is implemented as the system call "time(NULL)", and thus
  represents the time in seconds since 00:00:00 UTC, January 1, 1970.;
  it is returned by Rename_GetCurTime.

  Rename_sto_time stores a time (previously obtained through Rename_GetCurTime)
  and may be accessed through Rename_GetStoTime.

  Rename_StartTimer takes an inteval (in seconds) and sets Rename_exp_time;
  Rename_CheckTimer then checks if Rename_exp_time has been reached.

  RenameGetCurYearMonthDay returns a SCALAR in the form yyyymmdd, where,
  for example, a current date of 21st March 2005 would be returned as 
  20050321.
*/

INVARIANT

  Rename_cur_time : SCALAR &
  Rename_sto_time : SCALAR &
  Rename_exp_time : SCALAR

INITIALISATION

  Rename_cur_time :: SCALAR ||
  Rename_sto_time := 0 ||
  Rename_exp_time := 0
 
OPERATIONS

  time <-- Rename_GetCurTime = BEGIN time := Rename_cur_time END;

  Rename_StoTime(time:SCALAR) = BEGIN Rename_sto_time := time END;

  time <-- Rename_GetStoTime = BEGIN time := Rename_sto_time END;

  exp_time <-- Rename_StartTimer(interval:SCALAR) =
    PRE Rename_cur_time + interval <= MaxScalar THEN
      Rename_exp_time := Rename_cur_time + interval ||
      exp_time := Rename_cur_time + interval
    END;

  expired <-- Rename_CheckTimer =
    BEGIN expired := bool ( Rename_exp_time <= Rename_cur_time ) END;

  cur_ymd <-- Rename_GetCurYearMonthDay = BEGIN cur_ymd :: SCALAR END;

  inc_ymd <-- Rename_IncYearMonthDay(ymd : SCALAR & days : SCALAR) =
    /* increments ymd by days */
    PRE ymd + days : SCALAR THEN inc_ymd :: SCALAR END

END
