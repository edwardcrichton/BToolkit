MACHINE           Rename_vector_PK(lb,ub)

CONSTRAINTS       lb=0 & lb<ub

SEES              VHDL_PK

CONSTANTS         Rename_Vec, Rename_Vec2Nat,  Rename_Nat2Vec
    
PROPERTIES        

   Rename_Vec = 0..ub --> std_logic &
   Rename_Vec2Nat : Rename_Vec --> NAT &
   Rename_Nat2Vec : NAT +-> Rename_Vec &

/*   Rename_Vec2Nat = 
           %(vec). ( vec : Rename_Vec | (
               SIGMA(nn).( nn:0..ub & vec(nn)='1' | exp(2,nn) ) 
           )) & */

  !(vec).(
        vec : Rename_Vec =>
        Rename_Vec2Nat(vec) = SIGMA(nn).( nn:0..ub & vec(nn)='1' | exp(2,nn) )
          ) &

   Rename_Nat2Vec = Rename_Vec2Nat~

OPERATIONS


/* conversions */

  nn <-- Rename_vec_VEC2NAT(vec:Rename_Vec) =
  BEGIN
    nn := Rename_Vec2Nat(vec)
  END;

  vec <-- Rename_vec_NAT2VEC(nn:NAT) =
  PRE nn : dom(Rename_Nat2Vec) THEN
    vec := Rename_Nat2Vec(nn)
  END;


/* enquiry */

  val <-- Rename_idx_VAL(vec:Rename_Vec & idx:0..ub) =
  BEGIN
    val := vec(idx)
  END;

  sl <-- Rename_idx_EQL(val:std_logic & vec:Rename_Vec & idx:0..ub) =
  IF val = vec(idx) THEN
    sl := '1'
  ELSE
    sl := '0'
  END;

 vecout <-- Rename_vec_XTR(vecin:Rename_Vec & lo:0..ub & hi:0..ub) =
  PRE lo <= hi THEN
    vecout :=  %(nn).(nn:0..(hi-lo) | vecin(lo+nn) )  
  END;

/* modification */

  vecout <-- Rename_idx_MOD(val:std_logic & vecin:Rename_Vec & idx:0..ub) =
  BEGIN
    vecout := vecin <+ {idx |-> val}
  END

END
