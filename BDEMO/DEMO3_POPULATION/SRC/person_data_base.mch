MACHINE

 person_data_base(maxpers)

SEES

 data_base_context,Bool_TYPE

VARIABLES

 person, sex, status, mother, husband

INVARIANT

  person : 0 .. maxpers &
  sex : 1 .. person --> SEX &
  status : 1 .. person --> STATUS &
  mother : 1 .. person +-> dom(husband) &
  husband : sex~[{woman}] >+> sex~[{man}] 

DEFINITIONS

  wife == husband~

INITIALISATION

    person,sex,status,mother,husband := 0,{},{},{},{}


OPERATIONS

  pp <-- newborn(ss) =
    PRE
      person /= maxpers &
      ss : SEX
    THEN
      status(person+1) := living ||
      sex(person+1) := ss ||  
      person := person+1 ||
      pp := person+1
    END;

  mod_mother(xx,yy) =
    PRE
      xx : 1 .. person &
      yy : dom(husband)
    THEN
      mother(xx) := yy
    END;

  marriage(xx,yy) =
    PRE
      xx : sex~[{woman}] - dom(husband) &
      yy : sex~[{man}] - ran(husband)
    THEN
      husband(xx) := yy 
    END;

  death(xx) =
    PRE
      xx : status~[{living}]
    THEN
      status(xx):=dead
     END;

  ss<--val_sex(xx) =
    PRE
      xx : 1 .. person
    THEN
      ss := sex(xx)
    END;

  ss<--val_status(xx) =
    PRE
      xx : 1 .. person
    THEN
      ss := status(xx)
    END;

  bb<--is_married(xx) =
    PRE
      xx : 1 .. person
    THEN
      bb := bool(xx : dom(husband) \/ dom(wife))
    END;
  pp<--val_spouse(xx) =
    PRE
      xx : dom(husband) \/ dom(wife)
    THEN
      pp := (husband \/ wife)(xx)
    END;

  bb<--has_parents(xx) =
    PRE
      xx : 1 .. person
    THEN
      bb := bool(xx : dom(mother))
    END;

  pp<--val_mother(xx) =
    PRE
      xx : dom(mother)
    THEN
      pp := mother(xx)
    END;

  bb<--is_present(xx) =
    PRE
      xx : 1 .. maxpers
    THEN
      bb := bool(xx <= person)
    END;

  bb<--system_is_full =
    BEGIN
      bb := bool(person = maxpers)
    END


END
