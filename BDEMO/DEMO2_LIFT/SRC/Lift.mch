/*" \begin{center} {\bf DEMO2\_LIFT} \end{center} "*/

MACHINE           Lift(LFT,topfloor,bottomfloor)

CONSTRAINTS       topfloor > bottomfloor

SETS              DIR = {up, dn};  DOR = {opn, clo}

CONSTANTS         opp

PROPERTIES

  opp: DIR --> DIR &
  opp = {up |-> dn, dn |-> up} &
  opp(up) = dn &
  opp(dn) = up 

VARIABLES         in, out, mov, dir, flr, dor

INVARIANT

 in: (bottomfloor..topfloor) <-> DIR &
 out: LFT <-> (bottomfloor..topfloor) &
 mov <: LFT &
 dir: LFT --> DIR &
 flr: LFT --> bottomfloor..topfloor &
 dor: LFT --> DOR &

 dor[mov] <: {clo}

INITIALISATION 

 in:= {} ||
 out:= {} ||
 mov:= {} ||
 dir:= LFT * {up} ||
 flr:= LFT * {bottomfloor} ||
 dor:= LFT * {clo}

/*"\newpage"*/ 

DEFINITIONS

 attr_up(l) ==
   (out[{l}] \/ dom(in)) /\ ((flr(l)+1)..topfloor) /= {};

 attr_dn(l) ==
   (out[{l}] \/ dom(in)) /\ (bottomfloor .. (flr(l)-1)) /= {}


OPERATIONS

 Request_Lift(fl,dd) =
	 PRE
	   fl: bottomfloor..topfloor &
	   dd: DIR
	 THEN
 	  in := in \/ {(fl|->dd)}
 	END;


 Request_Floor(ll,fl) =
	 PRE
 	  fl : bottomfloor..topfloor &
 	  ll : LFT
 	THEN
 	  out := out \/ {(ll|->fl)}
 	END;


 Continue_Up(ll) =
	 PRE 
	   ll : mov &
	   dir(ll) = up &
 	  flr(ll)<topfloor &
 	  (ll|->flr(ll)) /: out &
 	  (flr(ll)|->up) /: in &
 	  attr_up(ll)                                        
 	THEN
	   flr(ll):= flr(ll) + 1
	 END;

/*"\newpage"*/
 Continue_Down(ll) =
 	PRE 
 	  ll : mov &
 	  dir(ll) = dn &
	   flr(ll) > bottomfloor &
	   (ll|->flr(ll)) /: out &
	   (flr(ll)|->dn) /: in &
 	  attr_dn(ll)                                       
	 THEN
	   flr(ll):= flr(ll) - 1
	 END; 

                             
 Pickup_Or_Deliver_And_Continue(ll) =
	 PRE
 	  ll : mov &

                           /*    (flr(ll) |-> dir(ll) : in or
                                  flr(ll) : out[{ll}] ) &   */
	  flr(ll) : in~[{dir(ll)}]  \/ out[{ll}]  &  /* does not evaluate,  use above */
 	  (dir(ll) = up =>
		 attr_up(ll)) &
 	  (dir(ll) = dn =>
		 attr_dn(ll))
 	THEN 
 	   mov := mov - {ll} ||
 	   dor(ll):= opn  ||
  	   out:= out - {ll |-> flr(ll)} ||
	   in:= in - {flr(ll) |-> dir(ll)}
	 END;


 Stop(ll) =  
	 PRE
 	  ll : mov &
	   (dir(ll) = up => not(attr_up(ll))) &
	   (dir(ll) = dn => not(attr_dn(ll))) &
	   flr(ll) /: dom(in) 
 	THEN
	   mov := mov - {ll} ||
	   dor(ll):= opn ||
	   out:= out - {ll |-> flr(ll)}
	 END;

/*"\newpage"*/
 Pickup_And_Change_Dir(ll) =
	 PRE
           ll: mov &
	   (dir(ll) = up =>
	      not(attr_up(ll))) &
	   (dir(ll) = dn =>
	      not(attr_dn(ll))) &
	   (flr(ll)|-> dir(ll)) /: in &
	   (flr(ll)|-> opp(dir(ll))) : in
	 THEN 
	   mov := mov - {ll} ||
	   dor(ll):= opn ||
	   out:= out - {ll |-> flr(ll)} ||
	   in:= in - {flr(ll) |-> opp(dir(ll))} ||
	   dir(ll):= opp(dir(ll))
	 END;


 Pickup_And_Same_Dir(ll) =
	 PRE
	   ll: mov &
	   (dir(ll) = up =>
 	     not(attr_up(ll))) &
	   (dir(ll) = dn =>
 	     not(attr_dn(ll))) &   
 	  (flr(ll)|-> dir(ll)) : in 
	 THEN 
	   mov := mov - {ll} ||
	   dor(ll):= opn ||
	   out:= out - {ll |-> flr(ll)} ||
	   in:= in - {flr(ll) |-> dir(ll)} 
	 END;

/*"\newpage"*/
 Close_Door = 
	 PRE 
	   dor~[{opn}] /= {}
	 THEN
	    ANY ll WHERE
	        ll : dor~[{opn}]
 	   THEN
	       dor(ll):= clo
	    END
	 END;


 Open_Door =          
	 PRE   
	   ( dor~[{ clo }] /\ (LFT-mov)) /= {}                  
	 THEN
	   ANY ll WHERE
	       ll : dor~[{ clo }] &
 	      ll /: mov 
	   THEN
	       dor(ll):= opn ||
	       in:= in - {flr(ll) |-> dir(ll)}
	   END
	 END;


 Depart_And_Move_Up(ll) = 
	  PRE
	    ll : dor~[{ clo }] &
	    ll /: mov &
	    attr_up(ll)                             
	  THEN
	    mov := mov \/ {ll} ||
	    flr(ll):= flr(ll)+1 ||
	    dir(ll) := up
 	 END;

/*"\newpage"*/
 Depart_And_Move_Down(ll) = 
	  PRE
	    ll : dor~[{ clo }] & 
	    ll /: mov &      
	    attr_dn(ll)
	  THEN
	    mov := mov \/ {ll} ||
	    flr(ll):= flr(ll)-1 ||
	    dir(ll):= dn
	  END


END
