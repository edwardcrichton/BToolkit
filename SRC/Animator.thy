/* Copyright (c) 1988-96, B-Core (UK) Ltd
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
THEORY LibraryBoolX IS

/*
 
  (( a|->b ) === ( c|->d ) ) == ( a===c &  b===d );

  ( {a} === {b} ) == ( a === b );

not finished - the blconstant check is currently
not in  Constant____  but are done in the individual
rules - where I have found it necessary.
so the constant check below - allow the forms above.
( and other forms - which was the original problem
I tried to solve );
If problems arises with this - then blconstant could
be needed when unwanted rewrites occur -
I have been able to avoid most of them by rearanging the tactic
in Toolkit 9.
*/
  
  Constant____(v,(a,b))
/*
HERE(( ASSUMING :: (a = b) <=>  false ))
*/
 =>
  (a===b == false);

  Constant____(v,(f,a,b)) 
 =>
  (a===f(b) == UNDEF(f(b)));


  Constant____(v,(a,f,b)) &
  HERE(( UNDEFINED(f(a)) )) 
 =>
  (f(a)===b == UNDEF(f(a)));

/******************************* solving undefined values - partly! ***************/
  


  bident(f) &             /* f is assumed to be a defered function */
  Constant____(v,(b)) & 
HERE((Property : f(b) = a )) &
  PromptForData((BT_GET_STRING_M,bcatl("Failed to evaluate equality|Enter value of function application: ",f,"(",b,")"),"i"))
 =>
  ( f(b)===a  == Set__Fap2(f(b)|(a)) );

  bident(f) &
  Constant____(v,(b)) &  
HERE((Property : a  = f(b) )) &
  PromptForData((BT_GET_STRING_M,bcatl("Failed to evaluate equality|Enter value of function application: ",f,"(",b,")"),"i"))
 =>
  ( a===f(b)  == Set__Fap1(a|f(b)) );

 
  Set__Fap2(a|a) == true;
 
  ReadData(y) &
  bcall(RULE: bcrel(UserLibX,(f(b) == y)))
 => 
  Set__Fap1(a|f(b)) == (a === y);

  ReadData(y) &
/***
HERE(("ReadData":8:y))&
HERE((Set__Fap2(f(b)|a) == (y === a))) &
***/
  bcall(RULE: bcrel(UserLibX,(f(b) == y)))
 => 
  Set__Fap2(f(b)|a) == (y === a);

/***********************************************/


  (a or true) == true;

  (true or a) == true;

  (a or false) == a;

  (false or a) == a;


  (false => a) == true;

  (true => a) == a;


  bstring(a)
 =>
  a:seq(0..255) == true;

  (-a) == (0-(a));

  btest(a<b)
 =>
  (a-b) : NAT == false;

  
  btest(a<=b)
 =>
  (a-b) : NAT1 == false;


  Constant____(v,(a)) &
  bconstant(a)
 =>
  a:NAT1 == false;

  Constant____(v,(a)) &
  bconstant(a)
 =>
  a:NAT == false;


  bnum(a)
 =>
  a:NAT == true;


  bnum(a) &
  btest(a>0)
 =>
  a:NAT1 == true;



  (true & a) == a;

  (a & true) == a;


  bool(false) == FALSE;

  bool(true) == TRUE;

  Constant____(v,(b,a))
  =>
  a:{b} == false;

  bsearch(a,(b),c)
 =>
  a:{b} == true;

  a:{a} == true;

  a:{} == false;



  Constant____(v,(a,b))
 => 
  not(a===b) == true;

  not(a===a) == false;

  Constant____(v,(a,b))
 =>
  a/=b == true;

  a/=a == false;



/*** dave98 ***/


  {e} : S --> T == ( (dom({e})=S) & (ran({e})<:T) &
                           card(dom({e}))===card({e}) );


  {e} : S +-> T == ( (dom({e})<:S) & (ran({e})<:T) &

                           card(dom({e}))===card({e}) );
  {e} : S <-> T == ( (dom({e})<:S) & (ran({e})<:T) );


  {} : {} --> t == true;

  {} : s +-> t == true;

  {} : s <-> t == true;

/**************/


/******************* 3 rules to catch set-comprehension *******/

  ReadData(s) 
/***
&HERE(("ReadData":6:s)) 
***/
 => 
  Set__Comp_Query(x|p) == (s >>+-+<< (x|p));

  ReadData((l,e)) 
/***
&HERE(("ReadData":6:l,e)) 
***/
 => 
  Set__Comp_Query(x|p) == ({l,e} >>+-+<< (x|p));

  ReadData({s})
/***
&HERE(("ReadData":5:{s})) 
***/
 => 
  Set__Comp_Query(x|p) == ({s} >>+-+<< (x|p));


/*
  _FifoWrite_Store((BT_ANM_CST_M,bcatl("  Finite range for  ",x),"Cannot quantify over carrier set|Limit the set to continue :{e1,.,en}"),(PromptUserX.1))
*/
  HERE(( Infinite_Carrier_Set_in : {x | x : s } )) &
  HERE(( Infinite_Carrier_Set : s )) &

  PromptForData((BT_GET_STRING_M,bcatl(" Provide Finite Enumerated Carrier Set for ",x," in set"),"i"))
  =>
  (s >>+-+<< (x|p)) == Set__Comp_Query(x|p);

/******************* 2 rules to catch set-comprehension *******/

  ({} >>+-+<< (x|p)) == {};

  ( {e}>>+-+<<false ) == {};

  ( {e}>>+-+<<true ) == {e};


  (#a.(false) == false);

/* Numbers  ************/

  
  0:NAT1 == false;

  btest(a>b)
 =>
  (a<=b) == false;

  btest(a<=b)
 =>
  (a<=b) == true;

  btest(a>=b)
 =>
  (a<b) == false;

  btest(a<b)
 =>
  (a<b) == true;

  btest(a<b)
 =>
  (a>=b) == false;

  btest(a>=b)
 =>
  (a>=b) == true;

  btest(a<=b)
 =>
  (a>b) == false;

  btest(a>b)
 =>
  (a>b) == true;

/******************/


  not(false) == true;

  not(true) == false;


  (false & a) == false;

  (a & false) == false;

  a===a == true

END

&

/*
THEORY MinMaxX IS

  bnum(a) & bnum(b) & btest (b>0) => (a mod b) == (a-((a/b)*b));

  bnum(y)
 =>
  min__(x,y) == x;

  btest(x>y)
 =>
  min__(x,y) == y;

  min({e}) == e;

  min({s,e}) ==  min__(min({s}) , e);

  bnum(y)
 =>
  max__(x,y) == x;

  btest(y>x)
 =>
  max__(x,y) == y;

  max({e}) == e;

  max({s,e}) ==  max__(max({s}) , e)

END
*/

THEORY MinMaxX IS

  bnum(a) & bnum(b) & btest (b>0) => (a mod b) == (a-((a/b)*b));

  bnum(y) &
  bnum(x)      /* <<<<<<<<<<<<<<<<<<<<<<< */
 =>
  min__(x,y) == x;

  btest(x>y)
 =>
  min__(x,y) == y;

  min({e}) == e;

  min({s,e}) ==  min__(min({s}) , e);

  bnum(y)&
  bnum(x)      /* <<<<<<<<<<<<<<<<<<<<<<< */
 =>
  max__(x,y) == x;

  btest(y>x)
 =>
  max__(x,y) == y;

  max({e}) == e;

  max({s,e}) ==  max__(max({s}) , e)

END

&

THEORY TakeDropX IS

  Constant____(v,(x,1)) 
 => 
  [x]|+-+/0 == [x];

  [l,x]|+-+/0 == [brev(l,x)];

  btest(n>0) &
  Constant____(v,(x,1))  
 =>
  [x]|+-+/n == <>;

  btest(n>0)
 =>
  [l,x]|+-+/n == [l]|+-+/(n-1);

  bnum(n)
 =>
  [s]\|/n == [brev(s)]|+-+/n ;

  bnum(n)
 =>
  <>\|/n == <>;



  Constant____(v,(x,1))
 => 
  [x]|+-+\0 == [x];

  [l,x]|+-+\0 == [l,x];

  btest(n>0)
 =>
  [l,x]|+-+\n == [l]|+-+\(n-1);

  bnum(n)
 =>
  [s]/|\n == [s]|+-+\(size([s])-n);

  [s]/|\0 == <>;

  bnum(n)
 =>
  <>/|\n == <>

END

&
  
THEORY UnionX IS  /* new for Version 4.30 */

 
  Set__((a);(c)) == Set__({};(c,a));

  /* HERE(( {c} )) => */ Set__({};(c)) == {c};

  Set__((a,b);(c)) == Set__((a);(c,b));

  bsearch(a,(c),(r)) 
  =>
  Set__((a);(c)) == Set__({};(c));

  Set__((a);(a)) == Set__({};(a));

  bsearch(b,(c),(r))
  =>
  Set__((a,b);(c)) == Set__((a);(c)); 

  Set__((a,b);(b)) == Set__((a);(b));
  
  {a} \/ {b} == Set__((a);(b));

  {a} \/ {a} == {a};

  a \/ {} == a;

  {} \/ a == a;

/*** union of sets *****/

  union({l,{m},{n}}) == union({l,({m} \/ {n})});
  union({l,{m},{}}) == union({l,{m}});
  union({l,{},{n}}) == union({l,{n}});

  union({{m},{n}}) == ({m} \/ {n}); 
  union({{m},{}}) == {m};
  union({{},{n}}) == {n};

  union({{m}})  ==  {m};
  
  union({{}})  ==  {};
  
  union({})  ==  {}

END

&

THEORY IntersectionX IS
  
/***
   Simplifies the intersection of two sets: X /\ Y
   Tactic: (IntersectionX~;UnionX~)
***/


  Constant____(v,(a,b,c,d)) &
  blconstant(a,b,c,d)
 =>
  {a|->b} /\ {c|->d} == {};

  Constant____(v,(a,b)) &
  blconstant(a,b)
 =>
  {a} /\ {b} == {};

  {a} /\ {a} == {a};

/*** {{{ X and Y singletons }}} ****/

  {a,b} /\ {c} == ({a} /\ {c}) \/  ( {b} /\ {c});

  bsearch(c,(a,b),s)
 =>
  {a,b} /\ {c} == {c};

/*** {{{ Y a singleton X non-empty }}} ****/

  {a} /\ {c,d} ==  ({a} /\ {c}) \/  ({a} /\ {d});

  bsearch(d,(a,b),s)
 =>
  {a,b} /\ {c,d} == ({s} /\ {c}) \/ {d};

/*** {{{ X and Y non-empty }}} ****/

  a /\ {} == {};

  {} /\ a == {};

/*** {{{ X and Y are well-formed sets of the same type }}} ****/

  inter({l,{m},{n}}) == inter({l,({m} /\ {n})});
  inter({l,{m},{}}) == inter({l});
  inter({l,{},{n}}) == inter({l});

  inter({{m},{n}}) == ({m} /\ {n});
  inter({{m},{}}) == {};
  inter({{},{n}}) == {};

  inter({{m}})  ==  {m}; 
  inter({{}})  ==  {};  
  inter({})  ==  {}

END

&


THEORY DomRestrictX IS
  
/***
   Simplifies the codomain restriction of one set by another: X <| Y
   Tactic: (DomRestrictX~;UnionX~)
***/

  Constant____(v,(a,b)) &
  blconstant(a,b)
 =>
  {a} <| {b|->c} == {};

  {a} <| {a|->b} == {a|->b};

/*** {{{ X and Y singletons }}} ****/

  {a,b} <| {c} == ({a} <| {c}) \/ ({b} <| {c});

/*** {{{ Y a singleton X non-empty }}} ****/

  {a} <| {b,c} == ({a} <| {b})  \/ ({a} <| {c});

  bsearch(d,(a),s)
 =>
  {a} <| {c,d|->e} == ({a} <| {c}) \/ {d|->e};

/*** {{{ X and Y non-empty }}} ****/

  a <| {} == {};

  {} <| a == {};

/*** {{{ X and Y are well-formed sets
           X has type A, Y has type A x B }}} ****/

  cod(a) == ran(a)

END

&

THEORY CodRestrictX IS
  
/***
   Simplifies the codomain restriction of one set by another: X |> Y
   Tactic: (CodRestrictX~;UnionX~)
***/

  Constant____(v,(c,b)) &
  blconstant(b,c)
 =>
  {a|->b} |> {c} == {};

  {a|->b} |> {b} == {a|->b};

/*** {{{ X and Y singletons }}} ****/

  {a,b} |> {c} == ({a} |> {c}) \/ ({b} |> {c});

/*** {{{ Y a singleton X non-empty }}} ****/

  {a} |> {b,c} == ({a} |> {b}) \/ ({a} |> {c}); /**** IB ****/

  
  bsearch(x|->d,(a),s)
 =>
  {a} |> {c,d} == ({s} |> {c,d}) \/ {x|->d};

/*** {{{ X and Y non-empty }}} ****/

  a |> {} == {};

  {} |> a == {}

/*** {{{ X and Y are well-formed sets
           X has type A x B, Y has type B }}} ****/

END

&

THEORY DomSubtractX IS
  
/***
   Simplifies the domain subtraction of one set by another: X <<| Y
   Tactic: (DomSubtractX~;UnionX~)
***/

  Constant____(v,(a,b)) &
  blconstant(a,b)
 =>
  {a} <<| {b|->c} == {b|->c};

  {a} <<| {a|->b} == {};

/*** {{{ X and Y singletons }}} ****/

  {a,b} <<| {c} == ({a} <<| ({b} <<| {c}));

/*** {{{ Y a singleton X non-empty }}} ****/

  {a} <<| {c,d} == ({a} <<| {c}) \/ ({a} <<| {d});

  Constant____(v,(a,d)) &
  blconstant(a,d)
 =>
  {a} <<| {c,d|->e} == {a} <<| {c} \/ {d|->e} ;

  bsearch(d,(a,?),s)
 =>
  {a} <<| {c,d|->e} == {a} <<| {c};

/*** {{{ X and Y non-empty }}} ****/

  a <<| {} == {};

  {} <<| a == a

/*** {{{ X and Y are well-formed sets
           X has type A x B, Y has type B }}} ****/

END

&

THEORY CodSubtractX IS
  
/***
   Simplifies the codomain restriction of one set by another: X |>> Y
   Tactic: (CodRestrictX~;UnionX~)
***/

  Constant____(v,(c,b)) &
  blconstant(b,c)
 =>
  {a|->b} |>> {c} == {a|->b};

  {a|->b} |>> {b} == {};

/*** {{{ X and Y singletons }}} ****/

  {a,b} |>> {c} == ({a} |>> {c}) \/ ({b} |>> {c});

/*** {{{ Y a singleton X non-empty }}} ****/

  {a} |>> {c,d} == ({a} |>> {c}) |>> {d};

  bsearch((x|->d),(a),s)
 =>
  {a} |>> {c,d} == {s} |>> {c,d};

/*** {{{ X and Y non-empty }}} ****/

  a |>> {} == a;

  {} |>> a == {}

/*** {{{ X and Y are well-formed sets
           X has type A x B, Y has type B }}} ****/

END

&

THEORY SetDifferenceX IS
 
/***
   Simplifies the set difference: X - Y
   Tactic: (SetDifferenceX~)
***/

  Constant____(v,(a,b,c,d)) &
  blconstant(a,b,c,d)
 =>
  {a|->b} - {c|->d} == {a|->b};

  Constant____(v,(a,b)) &
  blconstant(a,b)
 =>
  {a} - {b} == {a};

  {a} - {a} == {};

/*** {{{ X and Y singletons }}} ****/

  {a,b} - {c} == ({a} - {c}) \/ ({b} - {c});

/*** {{{ Y a singleton X non-empty }}} ****/

  {a} - {c,d} == {a} - {c} - {d};

  Constant____(v,(a,d)) &
  blconstant(a,d)
 =>
  {a} - {c,d} == {a} - {c};

  {a} - {c,a} ==  {};

  bsearch(d,(a),s)
 =>
  {a} - {c,d} == {s} - {c};

/*** {{{ X and Y non-empty }}} ****/

  a - {} == a;

  {} - a == {}

/*** {{{ X and Y are well-formed sets of the same type }}} ****/

END

&

THEORY FuncCompX IS
  
/***
   Simplifies the composition of two fulctions: X ; Y
   Tactic: (FuncCompX~;UnionX~)
***/

  Constant____(v,(b,c)) &
  blconstant(b,c)
 =>
  ({a|->b} ; {c|->d}) == {};

  ({a|->b} ; {b|->c}) == {a|->c};

/*** {{{ X and Y singletons }}} ****/

  ({a,b} ; {c}) ==  ({a} ; {c}) \/ ({b} ; {c});

/*** {{{ Y a singleton X non-empty }}} ****/

  ({a} ; {c,d}) ==  ({a} ; {c}) \/ ({a} ; {d});


/*
  bsearch(x|->d,(a),s)
 =>
  ({a} ; {c,d|->e}) == ({s} ; {c,d|->e}) \/ {x|->e};
*/


/*** {{{ X and Y non-empty }}} ****/

  (a ; {}) == a;

  ({} ; a) == {}

/*** {{{ X and Y are well-formed sets
           X has type A x B, Y ha2s type B x C }}} ****/

END

&

THEORY OverwriteX IS
  
/***
   Simplifies the overwriting of one set by another: X <+ Y
   Tactic: (OverwriteX~;UnionX~)
***/

  (s +> t) == (t <+ s);

  Constant____(v,(a,c))
 =>
  {a|->b} <+ {c|->d} == {a|->b,c|->d};

  {a|->b} <+ {a|->c} == {a|->c};

/*** {{{ X and Y singletons }}} ****/

  {a,b} <+ {d|->e} == {a,b}  \/ {d|->e};

  bsearch(d|->x,(a,b),s)
 =>
  {a,b} <+ {d|->e} == ({s}<+ {d|->e}) \/ {d|->e};

/*** {{{ Y a singleton X non-empty }}} ****/

  {a} <+ {c,d|->e} == ({a} <+ {c}) \/ {d|->e};

  bsearch(d|->x,(a),s)
 =>
  {a} <+ {c,d|->e} == ({s} <+ {c,d|->e}) \/ {d|->e};

/*** {{{ X and Y non-empty }}} ****/

  a <+ {} == a;

  {} <+ a == a

/*** {{{ X and Y are well-formed sets
           X and Y have type A x B    }}} ****/

END

&

THEORY ImageX IS

/***
   Image for sequences

***/

  [e] evl [s] == {1|->e}[s];

  [l,e] evl [s] == {size([l,e])|->e}[s] \/ ([l] evl [s]);

  <> evl [s] == {};
   
/***
   Simplifies the image of one set through another: X[Y]
   Tactic: (ImageX~;UnionX~)
***/

  Constant____(v,(c,a)) &
  blconstant(c,a)  /*  needed to make sure 'c' is reduced */ 
 =>  
  {a|->b}[{c}] == {};

  {a|->b}[{a}] == {b};

/*** {{{ X and Y singletons }}} ****/

  {a,b}[{c}] == ({a}[{c}]) \/ ({b}[{c}]);

/*** {{{ Y a singleton X non-empty }}} ****/

  {a}[{c,d}] == ({a}[{c}]) \/ ({a}[{d}]);

  bsearch(d|->y,(a),s) 
 =>
  {a}[{c,d}] == ({s}[{c,d}] \/ {y});

/*** {{{ X and Y non-empty }}} ****/

  a[{}] == {};

  {}[{a}] == {};

/*** {{{ X and Y are well-formed sets
                              X has type A x B, Y has type A }}} ****/
 

  closure(r) == clos__(r, (r;r) , r , card(r) );

  clos__(r,R,a,1) ==  id(carrier_set) \/ a;

  btest(n>1) =>  ( clos__(r,R,a,n) == clos__( r,(R;r),(a \/ (R)),(n-1) )  );

  closure({}) ==  id(carrier_set);

/**  closure(r)  ==  union(ran( %(n).( n: 0..card(r) | iterate(r,n ) ) ));  ***/



  closure(r)[t] == closI__( r , (t \/ r[t]) , card(r) );

  closI__(r,t,1) ==  t;

  btest(n>1) =>  ( closI__(r,t,n) == closI__(r,(t \/ r[t]),(n-1)) );

  closure({})[t] == t;
 
/***  Simplification of closure and  image under closure   ************/

  iterate(r,0) ==  id(carrier_set);

  iterate(r,1) == r;

  btest(n>1) => iterate(r,n) == it__(r|r|n);

  btest(n>1) => it__(f|r|n) == it__((f;r)|r|(n-1));

  it__(f|r|1) == f;
 
/******/

  iterate(r,n)[t] == itI__( r , (r[t]) , n );

  iterate(r,0)[t] == t;

  itI__(r,t,1) ==  t;

  btest(n>1) =>  ( itI__(r,t,n) == itI__( r,(r[t]),(n-1) ) )

/*** Simplifying the  Iterate for n > 0 ;and image under iterate *****
**** Converts iterate(a,0) to id(carrier_set) - must be supplied  *****/


END

&

THEORY InverseX IS
  
/***
   Simplifies the inverse of a set: X~
   Tactic: (InverseX~;UnionX~)
***/

  {a|->b}~ == {b|->a};

/*** {{{ X a singleton }}} ****/

  {a,b|->c}~ == {a}~ \/ {c|->b};

/*** {{{ X non-empty }}} ****/

  {}~ == {}

/*** {{{ X is a well-formed set of type A x B }}} ****/

END

&

THEORY FunApplicationX IS

/***
   Simplifies the application of the function to an element: X(Y)
   Tactic: (InverseX~;UnionX~)
***/

  {a|->b}(a) == b;

/*** {{{ X a singleton }}} ****/

  bsearch(c|->x,(a,b),s) 
 =>
  {a,b}(c) == x;

/*** {{{ X is a well-formed set of type A x B, Y has type A }}} ****/

/*** Simplifying the application of Identity *****/

  id({}) == {};
  
  id({e}) == {e|->e};

  id({l,e}) == id({l}) \/ {e|->e};

/*** Simplifying the  Iterate for n > 0 *****/

  iterate(r,0) ==  id(carrier_set);

  iterate(r,1) == r;

  btest(n>1) => iterate(r,n) == it__(r|r|n);

  btest(n>1) => it__(f|r|n) == it__((f;r)|r|(n-1));

  it__(f|r|1) == f;
 
  iterate({},n) == {}


END

&

THEORY DomX IS
  
/***
   Simplifies the domain of a set: dom(X)
   Tactic: (DomX~;UnionX~)
***/

  dom({a|->b}) == {a};

/*** {{{ X a singleton }}} ****/

  dom({a,b|->c}) == dom({a}) \/ {b};

/*** {{{ X non-empty }}} ****/

  dom({}) == {}

/*** {{{ X is a well-formed set of type A x B }}} ****/

END

&

THEORY CodX IS
  
/***
   Simplifies the codomain of a set: ran(X)
   Tactic: (CodX~;UnionX~)
***/

  ran({a|->b}) == {b};

/*** {{{ X a singleton }}} ****/

  ran({a,b|->c}) == ran({a}) \/ {c};

/*** {{{ X non-empty }}} ****/

  ran({}) == {}

/*** {{{ X is a well-formed set of type A x B }}} ***/

END

&

THEORY Set2SeqX 

IS

  Seq___({A}) == {A};

  Seq___({1|->a}) == [a];

  bsearch((1|->a),A,(2|->b))
 =>
  Seq___({A}) == [a,b];

  bsearch((1|->a),A,B) &
  bsearch((2|->b),B,(3|->c))
 =>
  Seq___({A}) == [a,b,c];

  bsearch((1|->a),A,B) &
  bsearch((2|->b),B,C) &
  bsearch((3|->c),C,(4|->d))
 =>
  Seq___({A}) == [a,b,c,d];

  bsearch((1|->a),A,B) &
  bsearch((2|->b),B,C) &
  bsearch((3|->c),C,D) &
  bsearch((4|->d),D,(5|->e))
 =>
  Seq___({A}) == [a,b,c,d,e];

  bsearch((1|->a),A,B) &
  bsearch((2|->b),B,C) &
  bsearch((3|->c),C,D) &
  bsearch((4|->d),D,E) &
  bsearch((5|->e),E,(6|->f))
 =>
  Seq___({A}) == [a,b,c,d,e,f];

  bsearch((1|->a),A,B) &
  bsearch((2|->b),B,C) &
  bsearch((3|->c),C,D) &
  bsearch((4|->d),D,E) &
  bsearch((5|->e),E,F) &
  bsearch((6|->f),F,(7|->g))
 =>
  Seq___({A}) == [a,b,c,d,e,f,g];

  bsearch((1|->a),A,B) &
  bsearch((2|->b),B,C) &
  bsearch((3|->c),C,D) &
  bsearch((4|->d),D,E) &
  bsearch((5|->e),E,F) &
  bsearch((6|->f),F,G) &
  bsearch((7|->g),G,(8|->h))
 =>
  Seq___({A}) == [a,b,c,d,e,f,g,h];

  bsearch((1|->a),A,B) &
  bsearch((2|->b),B,C) &
  bsearch((3|->c),C,D) &
  bsearch((4|->d),D,E) &
  bsearch((5|->e),E,F) &
  bsearch((6|->f),F,G) &
  bsearch((7|->g),G,H) &
  bsearch((8|->h),H,(9|->i))
 =>
  Seq___({A}) == [a,b,c,d,e,f,g,h,i];

  bsearch((1|->a),A,B) &
  bsearch((2|->b),B,C) &
  bsearch((3|->c),C,D) &
  bsearch((4|->d),D,E) &
  bsearch((5|->e),E,F) &
  bsearch((6|->f),F,G) &
  bsearch((7|->g),G,H) &
  bsearch((8|->h),H,I) &
  bsearch((9|->i),I,(10|->j))
 =>
  Seq___({A}) == [a,b,c,d,e,f,g,h,i,j]


END

&

THEORY SequenceX IS

  delaysetrev(a) == brev(a);

  seq2set(n)(b) == (n|->b);

  seq2set(n)(a,b) == (seq2set(n+1)(a),n|->b);


/* Concatenation */

   conc([[a]]) == [a];
 
   conc(<>) == <>;
 
   conc([a,[b]]) == ( conc([a]) ^ [b] );

   conc([a,<>]) ==  conc([a]);

#define  Par__Fun(x) {delaysetrev(seq2set(1)(brev(x)))}
 
/* composition */

  (<> ; k) == {};
  (l ; <>) == {};
  ([l] ; r) == Seq___(Par__Fun(l) ; r);
  (r ; [k]) == (r ; Par__Fun(k));

/* restrictions */

  <> |> s == {};
  [l] |> s == ( Par__Fun(l) |> s ) ;

  s <| <>  == {};
  s <| [l] == (s <| Par__Fun(l) ) ;

  <> |>> s == s ;
  [l] |>> s == ( Par__Fun(l) |>> s ) ;

  s <<| <>  == s ;
  s <<| [l] == (s <<| Par__Fun(l) ) ;

/* inverse */

  <>~ == {} ;
  [l]~ == Par__Fun(l)~;

/* over-riding */

  (<> <+ r) == r;
  (([l] <+ r))  ==  Seq___(Par__Fun(l) <+ r);
  (r <+ <>) == r;
  ((r <+ [l]))  ==  (r <+ Par__Fun(l));

  (<> +> r) == r;
  (([l] +> r))  ==  (Par__Fun(l) +> r);
  (r +> <>) == r;
  ((r +> [l]))  ==  Seq___(r +> Par__Fun(l));

  ([l] <+ [k])  ==  [k] ^ ([l] \|/ size([k]));


  charseq(x) == false;

  charseq(1) == true;

  charseq(x|b|[a]: seq(CHAR))  == false;

  charseq(1|b|[a]: seq(CHAR)) == ( [a]: seq(CHAR) );

  Constant____(v,(1,a)) 
 =>
  [a]: seq(CHAR) == charseq(blen(a)) ;

  Constant____(v,(a,b)) 
 =>
  [a,b]: seq(CHAR)  ==  ( charseq(blen(b)|b|[a]: seq(CHAR))) ;


  Constant____(v,(a,1)) 
 =>
  [a]: seq(NAT) == false;

  bnum(a) 
 =>
  [a]: seq(NAT) == true;

  Constant____(v,(1,b))
 =>
  [a,b]: seq(NAT) == false;

  bnum(b) 
 =>
  [a,b]: seq(NAT)  == ( [a]: seq(NAT) );

  <> : seq(NAT);



  delaybrev(<>) == <>;

  delaybrev([a]) == [brev(a)];

  rev([x]) == [brev(x)];

  bnum(n) &
  btest(n>0)
 =>
  [l](n) == (Par__Fun(l))(n);

  bnum(n) &
  btest(n>0)
 =>
  [l] evl (n) == (Par__Fun(l))(n);

  a-><> == [a];

  <><-a == [a];

  [b]<-c == [b,c];

  b->[c] == [bflat(b,c)];

  <>^a == a;

  a^<> == a;

  first([a]) ==last([brev(a)]);

  last([a]) == a;

  last([a,b]) == b;

  tail([a]) == delaybrev(front([brev(a)]));

  front([a]) == <>;

  front([a,b]) == [a];

  bstring(a)
 =>
  size(a) == (blen(a)-2);

  size(<>) == 0;

  size([a]) == 1;

  size([a,b]) == (size([a])+1);

  ran[a] == {a};
 
  ran(<>) == {};

  dom(<>) == {};

  dom([l]) == 1..size([l]);

  [a]^[b] == [bflat(a,b)]


END

&

THEORY AliasEqualsX IS

  ([?:=?]a) == a;

  (a=b) == (a===b);

  (a/=b) == not(a===b);

  (a/:b) == not(a:b)

END

&

THEORY CardX IS

  bnum(a) &
  bnum(b)
 =>
  card(a..b) == (b+1-a);

  card({}) == 0;

  card({a}) == 1;

  card({a,b}) == card({a})+1

END

&

THEORY InclusionX IS
  
/***
   Checks the inclusion of one set in another: X <: Y
   Tactic: (InclusionX~)
***/

  Constant____(v,(a,1)) &
  Constant____(v,(b,1))
 =>
  {a} <: {b} == false;

/*** dave98 ***/

  bnum(e)
 =>
  ({e} <: S) == (e:S);

  bsingleton(e)
 =>
  ({e} <: S) == (e:S);

  ({E,e} <: S) == ( (e:S) & ({E} <: S));

  btest(a<=n) &
  btest(n<=b)
 =>
  {n} <: a..b == true;

  btest(a<=n) &
  btest(n<=b) 
 =>
  {N,n} <: a..b == ({N} <: a..b) ;

/*************/

  Constant____(v,(a,b))
 =>
  {a} <: {b} == false;

  {a} <: {a} == true;

/*** {{{ X and Y singletons }}} ****/

  Constant____(v,(c,d,a))
 =>
  {a} <: {c,d} == false;

  bsearch(a,(c,d),s)
 =>
  {a} <: {c,d} == true;

/*** {{{ X a singleton Y non-empty }}} ****/

  Constant____(v,(c,d,b)) 
 =>
  {a,b} <: {c,d} == false;

  bsearch(b,(c,d),s)
 =>
  {a,b} <: {c,d} == {a} <: {c,d};

/*** {{{ X and Y non-empty }}} ****/

  Constant____(v,(a,1)) &
HERE(( a <: {} == false ))
 =>
  a <: {} == false;    

  {a} <: {} == false;    

  {} <: a == true;

  {} <<: {a} == true;


/*** {{{ X and Y are well-formed sets }}} ****/


  bnum(n)
  =>
  {n} <: NAT == true;

  bnum(n)
  =>
  {l,n} <: NAT == {l} <: NAT ;


  btest(n>=1)
  =>
  {n} <: NAT1 == true;

  btest(n>=1)
  =>
  {l,n} <: NAT1 == {l} <: NAT 


END

&

THEORY IntervalX IS
  
/***
   a..b
***/

  bnum(a) &
  btest(a>c)
 =>
  (a: b..c) == false;

  bnum(a) &
  btest(a<b)
 =>
  (a: b..c) == false;

  bnum(a) &
  btest(a>=b) &
  btest(a<=c)
 =>
  (a: b..c) == true;

  bnum(a) &
  bnum(b) &
  btest(b<16)
 =>
  (a..b) == ((a..(b-1)) \/ {b});

  bnum(a)
 =>
  (a..a) == {a};

  btest(b<a)
 =>
  (a..b) == {}

END


&

THEORY SetEqualityX IS
  
/***
   Checks the equality of one set with another: X === Y
   Tactic: (SetEqualityX~)
***/

  Constant____(v,(1,a)) &
  Constant____(v,(1,b)) 
 =>
  {a} === {b} == false;

  {a} === {a} == true;

/*** {{{ X a singleton Y non-empty }}} ****/

  Constant____(v,(c,d,b))
 =>
  {a,b} === {c,d} == false;

  bsearch(b,(c,d),s) 
 =>
  {a,b} === {c,d} == ({a} === {s});

/*** {{{ X and Y non-empty }}} ****/

  {} === {b} == false;

  {a} === {} == false;

  {} === {} == true

/*** {{{ X and Y are well-formed sets }}} ****/

END

&

THEORY SeqEqualityX IS
  
/***
   Checks the equality of one sequence with another: X === Y
   Tactic: (SeqEqualityX~)
***/

  Constant____(v,(a,1)) &
  Constant____(v,(b,1))
 =>
  [a] === [b] == false;

  [a,b] === [c,b] == ([a] === [c]);

  [a] === [a] == true;

/*** {{{ X and Y non-empty }}} ****/

  <> === [b] == false;

  [a] === <> == false;

  <> === <> == true

/*** {{{ X and Y are well-formed sequences }}} ****/

END

&
THEORY SetComprehensionX IS


/***********************************************************************
  
                    
                       NEW theory for quantifiers


************************************************************************/


/************************** Lambda 2 ************************************
 Format :
     domain >>>+-+<<< ( bindable variable . expression giving the value)

**************************************************************************/

  {}>>>+-+<<<(x.v) == {};

  bident(e) &
  x\e
  =>
  {e}>>>+-+<<<(x.v) == {e|->([x:=e]v)};

  bident(e) &
  x\e
  =>
  {l,e}>>>+-+<<<(x.v) == ({e|->([x:=e]v)} \/ ( {l}>>>+-+<<<(x.v)));

  {{e}}>>>+-+<<<(x.v) == {{e}|->([x:={e}]v)};

  {l,{e}}>>>+-+<<<(x.v) == ({{e}|->([x:={e}]v)} \/ ( {l}>>>+-+<<<(x.v)));

  bnum(e) 
  =>
  {e}>>>+-+<<<(x.v) == {e|->([x:=e]v)};

  bnum(e) 
  =>
  {l,e}>>>+-+<<<(x.v) == ({e|->([x:=e]v)} \/ ( {l}>>>+-+<<<(x.v)));

  (x,y)\(e,f)
  =>
  {e|->f}>>>+-+<<<((x,y).v) == {e|->f|->([x,y:=e,f]v)};

  (x,y)\(e,f)
  =>
  {l,(e|->f)}>>>+-+<<<((x,y).v) == ({e|->f|->([x,y:=e,f]v)} \/ ( {l}>>>+-+<<<((x,y).v)));

  ReadBoundVars(l)  &
  l\(q) 
 =>
  Lam__O((x).(p|v);q) == (Set__Comp(x|p))>>>+-+<<<(x.(v));

  %(x).(p|v) == %(set_glue bslmap(x)).( [x:=(set_glue bslmap(x))](p|v) );

  ReadBoundVars(l) &
  ModifyBoundVars((bflat(l,x))) &
  l\x 
  =>
  %(x).(p|v) == (Lam__O( (x).(p|v) ; ( hide((p|v),l) ) )) ;

 
  ReadBoundVars(l) &
  ReadUnaccConsts(k) &
  k\(p|v) & x\l 
 =>
  %(x).(p|v) == (Set__Comp(x|p))>>>+-+<<<(x.(v));

  
 %(x).(p|v)(e) == [x:=e]v;


/************************** set **************************************
 
   Format:

      carrier-set >>+-+<<  ( bindable variable | constraning predicate)

*********************************************************************/
   

  ( {e}>>++<< (x|false) ) == {};

  ( {e}>>++<< (x|true) ) == {e};


   
  x\e
  =>
  ( {e} >>+-+<< (x|r) ) == ( {e} >>++<< (x|[x:=e]r) );


  x\(e|->v) 
  =>
  ( {e|->v} >>+-+<< ((x,y)|r) ) == ( {e|->v} >>++<< ((x,y)|[x:=e][y:=v](r)) );


  x\e 
  =>
  ( {l,e} >>+-+<< (x|r) ) == ({e} >>++<< (x|[x:=e]r)) \/ ({l} >>+-+<< (x|r));


  x\(e|->v)
  =>
  ( {l,(e|->v)} >>+-+<< ((x,y)|r) ) == ({e|->v} >>++<< ((x,y)|[x:=e][y:=v]r)) \/ ({l} >>+-+<< ((x,y)|r));
  
 

/*** Four rules for limiting enumeration  ************/

  ReadData(s) 
/***
&HERE(("ReadData":2:s)) 
***/
 => 
  Set__Comp_Query(x|p) == (s >>+-+<< (x|p));

  ReadData((l,e)) 
/***
&HERE(("ReadData":2:l,e)) 
***/
 => 
  Set__Comp_Query(x|p) == ({l,e} >>+-+<< (x|p));


  ReadData({s}) 
/***
&HERE(("ReadData":1:{s})) 
***/
 => 
  Set__Comp_Query(x|p) == {s} >>+-+<< (x|p);


/*
  _FifoWrite_Store((BT_ANM_CST_M,bcatl("  Finite subset of NAT for  ",x),"Cannot quantify over infinite sets|Limit the set to continue animation:{0,1,2}"),(PromptUserX.1))

  HERE (( set : {x | x : NAT & (p) } )) &
*/
  PromptForData((BT_GET_STRING_M,bcatl("  Finite subset of NAT for ",x," in set"),"j"))
  =>
  (NAT >>+-+<< (x|p)) == Set__Comp_Query(x|p);

/*
  _FifoWrite_Store((BT_ANM_CST_M,bcatl("  Finite subset of NAT1 for ",x),"Cannot quantify over infinite sets|Limit the set to continue animation:{1,2,3}"),(PromptUserX.1))
  HERE (( set : {x | x : NAT1 & (p) } )) &
*/
  PromptForData((BT_GET_STRING_M,bcatl("  Finite subset of NAT1 for ",x," inset"),"j"))
  =>
  (NAT1 >>+-+<< (x|p)) == Set__Comp_Query(x|p);



/********************************************************************

    4 rules to reformulate set expression to common form using :

********************************************************************/

  bsearch((x<<:s),(p),r) &
  x\s 
  =>
  Set__Comp(x|p) == Set__Comp(x|x:POW(s) & r);

  bsearch((x<<:s),(p),r) &
  x\s 
  =>
  Set__Comp((l,x)|p) == Set__Comp((l,x)|x:POW(s) & r);

  bsearch((x<:s),(p),r) &
  x\s 
  =>
  Set__Comp(x|p) == Set__Comp(x|x:POW(s) & r);

  bsearch((x<:s),(p),r) &
  x\s 
  =>
  Set__Comp((l,x)|p) == Set__Comp((l,x)|x:POW(s) & r);

/*******************************************************************

   5 rules to find carrier set

     formats:

       set >>+-+<< (var|pred)     
       - a set whose elements satisfy  pred

      {l|pred} * (v|set2)  
       - product (set1*set2)  whose elements (pairs)  satisfy pred
       (v is not free in pred)

******************************************************************/


  ({s} >>+-+<< (x|p)) * (y|t) == ({s}*t) >>+-+<< ((x,y)|p); /* Ib 7-9-94 */

  ({} >>+-+<< (x|p)) * (y|t) == {};

  ({s} * (y|t)) == ({s}*t);

  ({} * (y|t)) == {};


/***** *****/

  bsearch((x:s),(p),r) &
  bsearch((l:t),(r),w) 
 =>
  Set__Comp((l,x)|p) == Set__Comp( (l,x)| (l,x) : t*s & w );

  bsearch((x:s),(p),r) &    /**** IB ***/
  x\(s,r) &
  ReadBoundVars(k) &
  ModifyBoundVars((bflat(k,x)))
  =>
  Set__Comp((l,x)|p) == Set__Comp(l|r)*(x|(s));

  bsearch((x:s),(p),r) &   /**** IB ***/
  x\(s,r) &
  ReadBoundVars(k) &
  bsearch(x,k,m)
  =>
  Set__Comp((l,x)|p) == Set__Comp(l|r)*(x|(s));

  bsearch((x=e),(p),r) &
  x\(e,r)
  =>
  Set__Comp((l,x)|p) == Set__Comp(l|r) * (x|{e});

  bsearch((x===e),(p),r) &
  x\(e,r)
  =>
  Set__Comp((l,x)|p) == Set__Comp(l|r) * (x|{e});


  bsearch((x:s),(p),r) &    /**** IB ***/
  x\(s) &
  ReadBoundVars(l) &
  ModifyBoundVars((bflat(l,x))) 
  =>
  Set__Comp(x|p) == (s) >>+-+<< (x|r);

  bsearch((x:s),(p),r) &    /**** IB ***/
  x\(s) &
  ReadBoundVars(l) &
  bsearch(x,l,m) 
  =>
  Set__Comp(x|p) == (s) >>+-+<< (x|r);


  bsearch((x:{s}),(p),r) &    /**** IB ***/
  x\(s) &
  ReadBoundVars(l) &
  ModifyBoundVars((bflat(l,x))) 
  =>
  Set__Comp(x|p) == ({s}) >>+-+<< (x|r);

  bsearch((x:{s}),(p),r) &    /**** IB ***/
  x\(s) &
  ReadBoundVars(l) &
  bsearch(x,l,m) 
  =>
  Set__Comp(x|p) == ({s}) >>+-+<< (x|r);

  bsearch((x:L..U),(p),r) &    /**** IB ***/
  ReadBoundVars(l) &
  ModifyBoundVars((bflat(l,x))) 
  =>
  Set__Comp(x|p) == (L..U) >>+-+<< (x|r);

  bsearch((x:L..U),(p),r) &    /**** IB ***/
  ReadBoundVars(l) &
  bsearch(x,l,m) 
  =>
  Set__Comp(x|p) == (L..U) >>+-+<< (x|r);


  bsearch((x=e),(p),r)  &
  x\e
  =>
  Set__Comp(x|p) == {e} >>+-+<< (x|r);

  bsearch((x===e),(p),r)  &
  x\e
  =>
  Set__Comp(x|p) == {e} >>+-+<< (x|r);



/****************************************************************
   the 2 next rule are search for expressions which are 
   likely to give a smaller carrier set.
****************************************************************/

/***
  Dave has added these 12 rules
***/

  bsearch((x:NAT1),(p),r) &
  bsearch((x<=n),r,t) &
  btest(n<15) &
  ReadBoundVars(l) &
  ModifyBoundVars((bflat(l,x)))
  =>
  Set__Comp(x|p) == (1..n) >>+-+<< (x|t);

  bsearch((x:NAT1),(p),r) &
  bsearch((x<=n),r,t) &
  btest(n<15) &
  ReadBoundVars(l) &
  bsearch(x,l,m)
  =>
  Set__Comp(x|p) == (1..n) >>+-+<< (x|t);



  bsearch((x:NAT),(p),r) &
  bsearch((x<=n),r,t) &
  btest(n<15) &
  ReadBoundVars(l) &
  ModifyBoundVars((bflat(l,x)))
  =>
  Set__Comp(x|p) == (0..n) >>+-+<< (x|t);

  bsearch((x:NAT),(p),r) &
  bsearch((x<=n),r,t) &
  btest(n<15) &
  ReadBoundVars(l) &
  bsearch(x,l,m)
  =>
  Set__Comp(x|p) == (0..n) >>+-+<< (x|t);




  bsearch((x:NAT1),(p),r) &
  bsearch((x<n),r,t) &
  btest(n<16) &
  ReadBoundVars(l) &
  ModifyBoundVars((bflat(l,x)))
  =>
  Set__Comp(x|p) == (1..n-1) >>+-+<< (x|t);

  bsearch((x:NAT1),(p),r) &
  bsearch((x<n),r,t) &
  btest(n<16) &
  ReadBoundVars(l) &
  bsearch(x,l,m)
  =>
  Set__Comp(x|p) == (1..n-1) >>+-+<< (x|t);

 



  bsearch((x:NAT),(p),r) &
  bsearch((x<n),r,t) &
  btest(n<16) &
  ReadBoundVars(l) &
  ModifyBoundVars((bflat(l,x)))
  =>
  Set__Comp(x|p) == (0..n-1) >>+-+<< (x|t);

  bsearch((x:NAT),(p),r) &
  bsearch((x<n),r,t) &
  btest(n<16) &
  ReadBoundVars(l) &
  bsearch(x,l,m)
  =>
  Set__Comp(x|p) == (0..n-1) >>+-+<< (x|t);

/********************************************************************
    6 rules to find  set directly - special case -
    no extra constraining predicates
********************************************************************/

  Set__Comp(x|x<<:s) ==  (POW(s) -{s});

  Set__Comp(x|x<:s) == POW(s);

  Set__Comp(x|x:l..u) == l..u;

  Set__Comp(x|x:{l}) == {l};

  Set__Comp(x|x=e) == {e};

  Set__Comp(x|x===e) == {e};

  bsearch((x:{}),(p),r) 
 =>
  Set__Comp(x|p) == {};

  Set__Comp(x|x:{}) == {};

  Set__Comp(x|false) == {};


/***************** UNION ********** INTER *************************/ 


    UNION(n).(p|s) == union(ran(%(n).(p|s)));


    INTER(n).(p|s) == inter(ran(%(n).(p|s)));

/***************** PI ********** SIGMA *************************/ 

  

  Constant____(v,(1,t)) 
 =>
  PI__(x).({t}|q) == [x:=t]q;

  PI__(x).({} | q) == 1; 

  Constant____(v,(1,t)) 
 =>
  PI__(x).({s,t}|q) == (PI__(x).({s}|q)) * [x:=t]q;

  PI__(x,y).({e|->t}|q) == [x,y:=(e,t)]q;
  
  PI__(x,y).({s,(e|->t)}|q) == (PI__(x,y).({s}|q)) * [x,y:=(e,t)]q;



  PI(x).(p|q) ==  PI__(x).({x|p}|q);
  



  Constant____(v,(1,t)) 
 =>
  SIGMA__(x).({t}|q) == [x:=t]q;

  SIGMA__(x).({} | q) == 0; 

  Constant____(v,(1,t)) 
 =>
  SIGMA__(x).({s,t}|q) == (SIGMA__(x).({s}|q)) + [x:=t]q;

  SIGMA__(x,y).({e|->t}|q) == [x,y:=(e,t)]q;
  
  SIGMA__(x,y).({s,(e|->t)}|q) == (SIGMA__(x,y).({s}|q)) + [x,y:=(e,t)]q;



  SIGMA(x).(p|q) ==  SIGMA__(x).({x|p}|q);
  


/**************************** Set Comprehension ******************/
  
 
  ReadBoundVars(l) &
  l\(q)
 =>
  Set__(x).(p;q) == Set__Comp(x|p);

  {x|p} == {(set_glue bslmap(x)) | [x:=(set_glue bslmap(x))](p) };

  ReadBoundVars(l) &
  ModifyBoundVars((bflat(l,x)))  &
  x\l 
 =>
  {x|p} == Set__(x).(p;( hide(p,l) ) );
  
  ReadBoundVars(l) &
  ReadUnaccConsts(k) &
  k\(p) & 
  x\l 
 =>
  {x|p} == Set__Comp(x|p);

  
  {x|p}/\{l} == {x| p & x : {l} };

  {x|p}/\l..u == {x| p & x : l..u };

/**************************** Universial Quantifiers ******************/
  

  ReadBoundVars(l) &
  l\(w)
 =>
  All__(x.(p=>q);w) == ( Set__Comp(x|(p&not(q))) === {} );


  !(x).(p=>q) == !(set_glue bslmap(x)).( [x:=(set_glue bslmap(x))](p=>q));


  ReadBoundVars(l) &
  ModifyBoundVars((bflat(l,x))) &
  l\x
 =>
  !(x).(p=>q) == All__((x).(p=>q);( hide((p=>q),l) ) );


  ReadBoundVars(l) &
  ReadUnaccConsts(k) &
  k\(p=>q) & x\l
 =>
  !(x).(p=>q) == ( Set__Comp(x|(p&not(q))) === {} );



/**************************** Exitential Quantifiers ****************/

 
  ReadBoundVars(l) &
  l\(w) 
 =>
  Exist__((x).(p);w) == not( Set__Comp(x|p) === {} );

  (#(x).(p)) ==  ( #(set_glue bslmap(x)).( [x:=(set_glue bslmap(x))](p) ) );

  ReadBoundVars(l) &
  ModifyBoundVars((bflat(l,x))) &
  l\x 
 =>
  (#(x).(p)) == Exist__((x).(p);( hide(p,l) ) );

  ReadBoundVars(l) &
  ReadUnaccConsts(k) &
  k\(p) & x\l
 =>
  (#(x).(p)) == not( Set__Comp(x|p) === {} );


  bsearch((x=e),p,r) => (#(x).(p)) == [x:=e]p;

  bsearch((x=e),p,r) => (#(l,x).(p)) ==  (#(l).[x:=e]r);
   
  not(not(p)) == p;

 

/****************************** POW (used above) **********************
*/

  POW({}) == {{}};

  POW({x}) == {{x},{}};

  POW({l,x}) == POW({l}) \/ addpow(POW({l}),x);

  
  addpow({{}},x) == {{x}};

  addpow({{k}},x) == {{k,x}};

  addpow({l,{k}},x) == addpow({l},x) \/ {{k,x}};

  addpow({l,{}},x) == addpow({l},x) \/ {{x}};

  (a * POW(b)) == (a * POW__(b));
 
  (POW(a) * b) == (POW__(a) * b);

  (a : POW(b)) == ( a <: b )

END

&

THEORY GlueX IS

  Hlist(p,___default_bv,k) == (k);

  Hlist(p,(l,x),k) == Hlist(p,(l),(k));
  
  ReadSetsConstsEnumElem(l) &
  x\(l) 
 =>
  Hlist(p,(l,x),k) == Hlist(p,(l),(k,x));
  
  x\(p) 
  =>
  Hlist(p,(l,x),k) == Hlist(p,(l),(k));

  hide(p,(l)) == Hlist(p,l,?);

  set_glue(x) == bnewv(x,z);

  set_glue(x$n) == (x$(n+1))

END



&

THEORY CardProdX IS

  (y ||-> x)     == (y|->x) ;

  ((l,y) ||-> x) == ( ((l)||-> x), (y|->x) ) ;

  ({l} * {x})   == { l ||-> x } ;

  ({l} * {k,x}) == (  ( {l} * {k} ) \/ { (l)||->x } );

  {} * {l} == {}; 

  {l} * {} == {}  

END


&

THEORY PaspTheoryX IS

  IsPASPToolkit                    =>  MinUns == 0;
  IsPASPToolkit                    =>  MaxUns == 65535;

  IsPASPToolkit                    =>  MinByt == n2b(0);
  IsPASPToolkit                    =>  MaxByt == n2b(255);

  IsPASPToolkit                    => u2n(n2u(a)) == a;
  IsPASPToolkit                    => n2u(u2n(a)) == a;

  IsPASPToolkit                    => b2n(n2b(a)) == a;
  IsPASPToolkit                    => n2b(b2n(a)) == a;

  IsPASPToolkit                    => n2u~(a) == u2n(a);

  IsPASPToolkit                    => n2b~(a) == b2n(a);

  IsPASPToolkit                    => b2u(a) == n2u(b2n(a));
  IsPASPToolkit                    => u2b(a) == n2b(u2n(a));

  IsPASPToolkit & btest(a>255)    => a: BYTE == false;
  IsPASPToolkit & btest(a>65535)  => a: UNSIGNED == false;

   IsPASPToolkit & btest(a<=255)    => a: BYTE == true;
  IsPASPToolkit & btest(a<=65535)  => a: UNSIGNED == true;

 IsPASPToolkit & btest(a<=255)    => n2b(a) == a;
  IsPASPToolkit & btest(a<=65535)  => n2u(a) == a;

  IsPASPToolkit & btest(a<=255)    => b2n(a) == a;
  IsPASPToolkit & btest(a<=65535)  => u2n(a) == a

END

&

THEORY SimplifyX IS

?;?;?;
  oO00OoI__K_P_o81RZxX99uUoO00OoiI1lLiL1I____________;
  oO00OoI__K_P_o81RZxX99uUoO00OoiI1lLiL1I____________

END

&

THEORY ANIM_TEST IS

bcall(

AnimLibraryX

  :

  ( %nn.(nn: 0..1 | {1|->0,0|->1}(nn))
   &
   %nn.(nn: 0..1 | {1|->'0',0|->'1'}(nn)) )

)

;

bcall(

AnimLibraryX

  :

  ( Seq___({1 |-> 4 , 2 |-> 5} +> {1 |-> 3}) )

)

END
