MACHINE

  Person1(max_person)

CONSTRAINTS

  max_person>0

SEES

  Bool_TYPE, String_TYPE

SETS

  PERSON;
  SEX = {male,female}

VARIABLES

  person, names, person_name, person_age, person_sex

INVARIANT

  person <: PERSON &
  card(person) <= max_person &
  names <: STRING &
  person_name: person >->> names &
  person_age: person --> NAT &
  person_sex: person --> SEX

INITIALISATION

  BEGIN person,names,person_name,person_age,person_sex := {},{},{},{},{} END

OPERATIONS

  rep <-- Add_person(name_inp,age_inp,sex_inp) =
    PRE
      card(person) < max_person &
      name_inp: STRING-names &
      age_inp: NAT &
      sex_inp: SEX
    THEN
      CHOICE
        ANY new_person WHERE new_person: PERSON-person THEN
          person:= person\/{new_person} ||
          names:= names\/{name_inp} ||
          person_name:=person_name\/{new_person|->name_inp} ||
          person_age:=person_age\/{new_person|->age_inp} ||
          person_sex:=person_sex\/{new_person|->sex_inp} ||
          rep:=TRUE
        END
      OR
        rep:=FALSE
      END
    END;

  rep,age_out,sex_out <-- Get_person_details(name_inp) =
    PRE name_inp: STRING THEN
      IF name_inp: names THEN
        age_out:=(person_name~;person_age)(name_inp) ||
        sex_out:=(person_name~;person_sex)(name_inp) ||
        rep:=TRUE
      ELSE
        age_out::NAT ||
        sex_out::SEX ||
        rep:=FALSE
      END
    END;

  rep<--Remove_person(name_inp) =
      PRE  name_inp: STRING THEN
        IF name_inp: names THEN
          person:= person-{person_name~(name_inp)} ||
          names:= names-{name_inp} ||
          person_name:=person_name |>> {name_inp} ||
          person_age:={person_name~(name_inp)} <<| person_age ||
          person_sex:={person_name~(name_inp)} <<| person_sex ||
          rep:=TRUE
       ELSE
          rep:=FALSE
       END
    END;

  Save_Person1 = skip;

  Restore_Person1 =
    ANY
      rst_person, rst_names, rst_person_name, rst_person_age, rst_person_sex
    WHERE
      rst_person <: PERSON &
      card(rst_person) <= max_person &
      rst_names <: STRING &
      rst_person_name: rst_person >->> rst_names &
      rst_person_age: rst_person --> NAT &
      rst_person_sex: rst_person --> SEX
    THEN
      person,names,person_name,person_age,person_sex:=
        rst_person,rst_names,rst_person_name,rst_person_age,rst_person_sex
    END

END

