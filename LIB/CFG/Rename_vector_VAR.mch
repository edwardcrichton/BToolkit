MACHINE           Rename_vector_VAR(length)

SEES              std_numbers_PK

CONSTANTS         

    Rename_vector,
    Rename_Vec2Nat,
    Rename_Nat2Vec
    
PROPERTIES        

   Rename_vector = 0..length --> {0,1} &
   Rename_Vec2Nat : Rename_vector --> NAT &
   Rename_Nat2Vec : NAT +-> Rename_vector &

   Rename_Vec2Nat = 
           %(vec). ( vec : Rename_vector | (
               SIGMA(nn).( nn:0..length | vec(nn) * exp(2,nn) ) 
           )) &

   Rename_Nat2Vec = Rename_Vec2Nat~
              
VARIABLES

  Rename_vec

INVARIANT

  Rename_vec : Rename_vector 

OPERATIONS

/* basic */

  Rename_vec_STO(vec:Rename_vector) =
  BEGIN  Rename_vec := vec END;

  vec <-- Rename_vec_VAL =
  BEGIN  vec := Rename_vec END;

  st <-- Rename_vec_EQL(vec:Rename_vector) =
  IF vec=Rename_vec THEN st := 1 ELSE st := 0 END;


/* conversions */

  nn <-- Rename_VEC2NAT =
  BEGIN
    nn := Rename_Vec2Nat(Rename_vec)
  END;

  Rename_NAT2VEC( nn : NAT ) =
  PRE nn : dom(Rename_Nat2Vec) THEN
    Rename_vec := Rename_Nat2Vec(nn)
  END;

/* initialising */

  Rename_ALL1s =
  BEGIN
    Rename_vec := (1..length) * {1}
  END;

  Rename_ALL0s =
  BEGIN
    Rename_vec := (1..length) * {0}
  END;

/* inquiry */

  bb <-- Rename_VAL(idx : 0..length) =
  BEGIN
    bb := Rename_vec(idx)
  END;

/* modifying */

  Rename_SET1(idx : 0..length) =
  BEGIN
    Rename_vec := Rename_vec <+ {idx |-> 1}
  END;

  Rename_SET0(idx : 0..length) =
  BEGIN
    Rename_vec := Rename_vec <+ {idx |-> 0}
  END;

/* masking */

  Rename_MASK(lo : 0..length & up : 0..length) =
  PRE lo <= up THEN
    Rename_vec := lo..up <| Rename_vec 
  END;

  Rename_EXT(lo : 0..length & up : 0..length) =
  PRE lo <= up THEN
    Rename_vec := ( %(nn).(nn:lo..up | nn-lo) ; (lo..up <| Rename_vec)) 
  END

END
