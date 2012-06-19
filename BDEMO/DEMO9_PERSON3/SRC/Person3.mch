MACHINE

  Person3(max_person)

CONSTRAINTS

  max_person : 1..10000 

SEES

  String_TYPE, Bool_TYPE, Scalar_TYPE

SETS

  PERSON;
  SEX = {female,male}

VARIABLES

  person, person_name, person_age, person_sex

INVARIANT

  person <: PERSON &
  card(person) <= max_person &
  person_name: person --> STRING &
  person_age: person --> SCALAR &
  person_sex: person --> SEX

INITIALISATION

  BEGIN
    person,person_name,person_age,person_sex := {},{},{},{}
  END

OPERATIONS

  rep,new_person <-- Add_person(name_inp,age_inp,sex_inp) =
    PRE
      name_inp: STRING &
      age_inp: SCALAR &
      sex_inp: SEX &
      card(person) < max_person 
    THEN
      CHOICE
        ANY pers WHERE pers: PERSON-person THEN
          person:= person\/{pers} ||
          person_name:=person_name\/{pers|->name_inp} ||
          person_age:=person_age\/{pers|->age_inp} ||
          person_sex:=person_sex\/{pers|->sex_inp} ||
          new_person:=pers ||
          rep:=TRUE
        END
      OR
        new_person :: PERSON ||
        rep:=FALSE
      END
    END;

  rep <-- Print_person_details(person_inp) = 
    PRE person_inp: person THEN rep :: BOOL END;
  

  Remove_person(person_inp) =
    PRE person_inp: person THEN
      person:= person-{person_inp} ||
      person_name:={person_inp} <<| person_name ||
      person_age:={person_inp} <<| person_age ||
      person_sex:={person_inp} <<| person_sex
    END;

  Save_Person = skip;

  Restore_Person =
    ANY
      rst_person, rst_person_name, rst_person_age, rst_person_sex
    WHERE
      rst_person <: PERSON &
      card(rst_person) <= max_person &
      rst_person_name: rst_person --> STRING &
      rst_person_age: rst_person --> SCALAR &
      rst_person_sex: rst_person --> SEX
    THEN
      person,person_name,person_age,person_sex:=
        rst_person,rst_person_name,rst_person_age,rst_person_sex
    END

END


