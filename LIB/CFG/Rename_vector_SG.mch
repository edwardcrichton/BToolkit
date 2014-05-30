MACHINE           Rename_vector_SG(lb,ub)

CONSTRAINTS       lb=0 & lb<ub

SEES              VHDL_PK

CONSTANTS         Rename_Vec, Rename_Vec2Nat, Rename_Nat2Vec
    
PROPERTIES        

   Rename_Vec = 0..ub --> std_logic &
   Rename_Vec2Nat : Rename_Vec --> NAT &
   Rename_Nat2Vec : NAT +-> Rename_Vec &


/*   Rename_Vec2Nat = 
           %(vec). ( vec : Rename_Vec | (
               SIGMA(nn).( nn:0..ub & vec(nn)='1' | exp(2,nn) ) 
           )) &
*/
   !(vec).(
        vec : Rename_Vec =>
        Rename_Vec2Nat(vec) = SIGMA(nn).( nn:0..ub & vec(nn)='1' | exp(2,nn) )
          ) &

   Rename_Nat2Vec = Rename_Vec2Nat~
              
VARIABLES         Rename_vec

INVARIANT         Rename_vec : Rename_Vec 

INITIALISATION    Rename_vec :: Rename_Vec 

OPERATIONS


/* vector store/retrieve/equality */

  Rename_vec_STO(vec:Rename_Vec) = BEGIN Rename_vec := vec END;

  vec <-- Rename_vec_VAL = BEGIN  vec := Rename_vec END;

  sl <-- Rename_vec_EQL(vec:Rename_Vec) =
  IF vec=Rename_vec THEN
    sl := '1'
  ELSE
    sl := '0'
  END;


/* index modify/retrieve/equality */

  Rename_idx_MOD(val:std_logic & idx:0..ub) =
  BEGIN
    Rename_vec := Rename_vec <+ {idx |-> val}
  END;

  val <-- Rename_idx_VAL(idx:0..ub) = BEGIN val := Rename_vec(idx) END;

  sl <-- Rename_idx_EQL(val:std_logic & idx:0..ub) =
  IF val = Rename_vec(idx) THEN
    sl := '1'
  ELSE
    sl := '0'
  END;


/* vector/nat conversions */

  nn <-- Rename_vec_VEC2NAT =
  BEGIN
    nn := Rename_Vec2Nat(Rename_vec)
  END;

  Rename_vec_NAT2VEC(nn:NAT) =
  PRE nn : dom(Rename_Nat2Vec) THEN
    Rename_vec := Rename_Nat2Vec(nn)
  END;

/* vector extract */

  vec <-- Rename_vec_XTR(lo,hi) =
  PRE lo:0..ub & hi:0..ub & lo <= hi THEN
     vec := %(nn).(nn:0..(hi-lo) | Rename_vec(lo+nn) )
  END;

/*  vector mask */

  Rename_vec_MASK(lo:0..ub & hi:0..ub) =
  PRE lo <= hi THEN
    Rename_vec := ((0..ub) * {'0'}) <+ ( lo..hi <| Rename_vec ) 
  END

END
