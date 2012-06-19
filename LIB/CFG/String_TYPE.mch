MACHINE     String_TYPE

SEES        Bool_TYPE

SETS

 CHAR;STRING

PROPERTIES

  STRING = { ss | ss : seq(CHAR) & size(ss) <= 1000 }

  /* literal string in AMN are written as: "a string" in ANSI C */


END
