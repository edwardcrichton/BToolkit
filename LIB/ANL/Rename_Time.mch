MACHINE

  Rename_Time

SEES

  Bool_TYPE, Scalar_TYPE

DEFINITIONS

 SecondsInDay == (((24*60) +60)*60 + 60)

VARIABLES

  Rename_limit, Rename_time, Rename_day

INVARIANT

  Rename_limit : 0..(SecondsInDay-1) &
  Rename_time : 0..(SecondsInDay-1) &
  Rename_day : SCALAR

INITIALISATION

  Rename_limit := 0 ||
  Rename_time :: 0..(SecondsInDay-1) ||
  Rename_day :: SCALAR

OPERATIONS

  Rename_SetLimit(tl) =
  PRE 
    tl : 1..(SecondsInDay-1)
  THEN
   Rename_limit := tl
  END;
   
  start_day, start_time <-- Rename_StartClock =
  ANY new_time,new_day WHERE
     new_time : 0..(SecondsInDay-1) &
     new_day : SCALAR &
     new_day >= Rename_day
  THEN
     Rename_time := new_time ||
     Rename_day :=  new_day ||
     start_time :=  new_time ||
     start_day := new_day
  END;

  
  elapsed <-- Rename_CheckClock( start_date ,start_time ) =
    PRE
      start_time : 0..(SecondsInDay-1) &
      start_date : (Rename_day-1)..Rename_day
    THEN
     ANY new_time,new_day WHERE
         new_time : 0..(SecondsInDay-1) &
         new_day : SCALAR &
         new_day >= Rename_day
     THEN
      SELECT start_date = new_day THEN
        elapsed :=
          bool( (new_time-start_time) >= Rename_limit )
      WHEN start_date  = new_day - 1 THEN
        elapsed :=
          bool(
           ((SecondsInDay - start_time) + new_time) >=
           Rename_limit 
              )
      END ||
      Rename_time := new_time ||
      Rename_day := new_day
     END
    END

END
