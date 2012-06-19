MACHINE           std_numbers_PK

CONSTANTS

   num_range, exp 

/*" {\em 0 .. nn\/} also recognized as {\em num\_range(nn)} "*/

PROPERTIES

   num_range  : 1..255 --> POW(0..255) &

   exp : NAT * NAT --> NAT &

   !(nn). ( nn : NAT => num_range(nn) = 0..nn ) &

   !(xx,nn). ( xx : NAT & nn : NAT => ( 
               exp(xx,0) = 1 &
               exp(xx,nn+1) = exp(xx,nn) * nn ) 
             )  

DEFINITIONS

  a ** b == exp(a,b) 

END
