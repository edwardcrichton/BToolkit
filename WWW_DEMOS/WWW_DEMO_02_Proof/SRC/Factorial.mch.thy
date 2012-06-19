THEORY UserLibX IS

  btest(n>0) => math_fac(n) == math_fac(n-1)*n;

  math_fac(0) == 1

END

