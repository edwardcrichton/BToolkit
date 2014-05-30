MACHINE           Rename_EV

SEES              VHDL_PK

VARIABLES         Rename, Rename_event
/*"
The variable {\em Rename\/} holds the current value of a source,
while the variable {\em Rename\_event\/} will indicate whether the
value of that source has changed
"*/

INVARIANT         Rename: std_logic & Rename_event: std_logic

INITIALISATION    BEGIN Rename := '0' || Rename_event := '0' END

OPERATIONS

/*"
{\bf Rename\_chg} is a synchronous event which changes Rename's value.
"*/

  Rename_chg =
  BEGIN 
    IF Rename = '1' THEN  Rename := '0' ELSE  Rename := '1' END ||
    Rename_event := '1'
  END;

/*"
{\bf Rename\_ack\/} is the event of another agent (a process
in an architecture) observing (or using) the value of {\em Rename\/}.
"*/

  Rename_ack = BEGIN Rename_event := '0' END

DEFINITIONS

  Rename_EVENT == (Rename_event = '1')

END
