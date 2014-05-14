THEORY UserLibX IS

 
 btest(b<c)
=>
 maxel({b},c) == c;

 btest(b>=c)
=>
 maxel({b},c) == b;

 btest(b<c)
=>
 maxel({a,b},c) == maxel({a},c);

 btest(b>=c)
=>
 maxel({a,b},c) == maxel({a},b);


 max(a) == maxel(a,0)
 

END
