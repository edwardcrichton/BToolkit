MACHINE               Rename_Time

SEES                  Bool_TYPE, Scalar_TYPE

VARIABLES             Rename_time, Rename_expire

/*
  Rename_time is implemented as the system call "time(NULL)", and thus
  represents the time in seconds cince 00:00:00 UTC, January 1, 1970
*/

INVARIANT

  Rename_time : SCALAR &
  Rename_expire : SCALAR

INITIALISATION

  Rename_time :: SCALAR ||
  Rename_expire := 0
 
OPERATIONS

  time <-- Rename_GetTime = BEGIN time := Rename_time END;

  start_time <-- Rename_StartTimer(interval:SCALAR) =
    PRE Rename_time + interval <= MaxScalar THEN
      Rename_expire := Rename_time + interval ||
      start_time := Rename_time
    END;

  expired <-- Rename_CheckTimer =
    BEGIN expired := bool ( Rename_expire <= Rename_time ) END

END
