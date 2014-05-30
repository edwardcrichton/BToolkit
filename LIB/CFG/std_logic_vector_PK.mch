MACHINE             std_logic_vector_PK

SEES                std_number_PK

CONSTANTS 

  std_logic_vector,

/*"
   {\em 0 .. nn\/} $\fun$ \{ {\em 0\/} , {\em 1\/} \} and\\
   {\em 0 .. nn\/} $\fun$ {\em std\_logic\/}\\
   also recognized as {\em std\_logic\_vector\/} ({\em nn\/})
"*/

  Vec2Nat 

PROPERTIES
   
  std_logic_vector = %(nn).(nn : 1..15 | 0..(nn-1) --> {0,1}) &

  Vec2Nat :  ( 0..15 +-> {0,1} ) +-> NAT &

  dom(Vec2Nat) =  UNION(nn).(nn : 0..15 | 0..(nn-1) --> {0,1} )  &   

  !(vec) .( vec : dom(Vec2Nat)  => (
           Vec2Nat(vec) = SIGMA(nn).( nn:dom(vec)| vec(nn) * exp(2,nn) )
          ))


END
