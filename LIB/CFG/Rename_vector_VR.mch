MACHINE      Rename_vector_VR(lb,ub)

CONSTRAINTS  lb=0 & lb<ub

SEES         std_number_PK

CONSTANTS    Rename_Vec, Rename_Vec2Nat, Rename_Nat2Vec
    
PROPERTIES        

   Rename_Vec = 0..ub --> {0,1} &
   Rename_Vec2Nat : Rename_Vec --> NAT &
   Rename_Nat2Vec : NAT +-> Rename_Vec &

   Rename_Vec2Nat = 
           %(vec). ( vec : Rename_Vec | (
               SIGMA(nn).( nn: 0..ub | vec(nn) * exp(2,nn) ) 
           )) &

   Rename_Nat2Vec = Rename_Vec2Nat~
              
VARIABLES    Rename_vec

INVARIANT    Rename_vec : Rename_Vec 

OPERATIONS

/* basic */

  Rename_vec_STO(vec:Rename_Vec) =
  BEGIN  Rename_vec := vec END;

  vec <-- Rename_vec_VAL =
  BEGIN  vec := Rename_vec END;

  st <-- Rename_vec_EQL(vec:Rename_Vec) =
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
    Rename_vec := (0..ub) * {1}
  END;

  Rename_ALL0s =
  BEGIN
    Rename_vec := (0..ub) * {0}
  END;

/* inquiry */

  bb <-- Rename_VAL(idx : 0..ub) =
  BEGIN
    bb := Rename_vec(idx)
  END;

  vv <-- Rename_XTR(lo : 0..ub & hi : 0..ub) =
  PRE lo <= hi THEN
     vv := %(nn).(nn:0..(hi-lo) | Rename_vec(lo+nn) )
  END;

/* modifying */

  Rename_SET1(idx : 0..ub) =
  BEGIN
    Rename_vec := Rename_vec <+ {idx |-> 1}
  END;

  Rename_SET0(idx : 0..ub) =
  BEGIN
    Rename_vec := Rename_vec <+ {idx |-> 0}
  END;

/* masking */

  Rename_MASK(lo : 0..ub & hi : 0..ub) =
  PRE lo <= hi THEN
    Rename_vec := ((0..ub) * {0}) <+ ( lo..hi <| Rename_vec ) 
  END

END
