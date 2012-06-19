MACHINE

  CMA(class_size, STUDENT)

CONSTRAINTS

  class_size > 0 &
  card(STUDENT) : NAT

SEES

  Bool_TYPE

VARIABLES

  enrolled, tested

INVARIANT

  enrolled <: STUDENT &
  tested <: STUDENT &
  tested <: enrolled &
  card(enrolled) <= class_size

INITIALISATION

  enrolled, tested := {}, {}

OPERATIONS

  enrol(st) =
    PRE
      st : STUDENT &
      card(enrolled) < class_size &
      st /: enrolled
    THEN
      enrolled := enrolled \/ {st}
    END
    ;
  ans <-- isenrolled(st) =
    PRE
      st : STUDENT
    THEN
      IF
        st : enrolled
      THEN
        ans := TRUE
      ELSE
        ans := FALSE
      END
    END
    ;
  test(st) =
    PRE
      st : enrolled &
      st /: tested
    THEN
      tested := tested \/ {st}
    END
    ;
  ans <-- istested(st) =
    PRE
     st : enrolled
    THEN
      IF
        st : tested
      THEN
        ans := TRUE
      ELSE
        ans := FALSE
      END
    END
    ;
  leave(st) =
    PRE
      st : enrolled
    THEN
      IF
        st : tested
      THEN
        tested := tested - {st} ||
        enrolled := enrolled - {st}
      ELSE
        enrolled := enrolled - {st}
      END
    END
    ;
  clmax, sofar <-- how_many =
    BEGIN
      clmax, sofar := class_size, card(enrolled)
    END

END
