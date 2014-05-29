MACHINE     Char_TYPE

SEES        Bool_TYPE

SETS

 CHAR = 
 { 
 B_SOH, B_STX, B_ETX, B_EOT, B_ENQ, B_ACK, B_BEL, B_BS,
 B_HT, B_LF, B_VT, B_FF, B_CR, B_SO, B_SI,
 B_DLE, B_DC1, B_DC2, B_DC3, B_DC4, B_NAK,
 B_SYN, B_ETB, B_CAN, B_EM, B_SUB, B_ESC,
 B_FS, B_GS, B_RS, B_US, B_SPACE,

 B_EXCL  /* ! */, 
 B_QUOT  /* " */,
 B_HSH   /* # */,
 B_DOLL  /* $ */,
 B_PCT   /* % */,
 B_AMP   /* & */,
 B_SQUOT /* ' */,
 B_OPAR  /* ( */,
 B_CPAR  /* ) */,
 B_MUL   /* * */,
 B_PLUS  /* + */,
 B_COM   /* , */,
 B_MINUS /* - */,
 B_DOT   /* . */,
 B_DIV   /* / */,


 '0', '1', '2','3','4','5','6','7','8','9',  

 B_COL   /* : */,
 B_SCOL  /* ; */,
 B_LESS  /* < */,
 B_EQL   /* = */,
 B_GTR   /* > */,
 B_QUERY /* ? */,
 B_CADD  /* @ */,

 'A','B','C','D','E','F','G','H','I','J','K','L',
 'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',

 B_OBRK  /* [ */,
 B_SLSH  /* \ */,
 B_CBRK  /* ] */,
 B_HAT   /* ^ */,
 B_UNL   /* _ */,
 B_BSQ   /* ` */,

 'a','b','c','d','e','f','g','h','i','j','k','l',
 'm','n','o','p','q','r','s','u','v','w','x','y','z',

 B_OBRC   /* { */,
 B_BAR    /* | */,
 B_CBRC   /* } */,
 B_TLD    /* ~ */,
 B_DEL
 };

 STRING

PROPERTIES

  STRING = { ss | ss : seq(CHAR) & size(ss) <= 1000 }

  /* literal string in AMN are written as: "a string" in ANSI C */


END
