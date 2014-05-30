MACHINE              Rename_Client(TOK,default_inbufsize,default_outbufsize)

CONSTRAINTS          default_inbufsize>=4 & default_outbufsize>=4

SEES                 String_TYPE, Scalar_TYPE, Bool_TYPE

VARIABLES            in,inptr,outptr

INVARIANT

  in : SCALAR &
  inptr : 0..in &
  outptr : SCALAR
   
INITIALISATION       in,inptr,outptr := 0,0,0

OPERATIONS


  /*** operation to initialise ipaddress,port and reset pointers ***/

  rep <-- Rename_INIT(ipaddress : STRING & port : NAT) =
  BEGIN in,inptr,outptr := 0,0,0 || rep :: BOOL END;



  /*** operations on the socket ***/

  rep <-- Rename_CONNECT = BEGIN rep :: BOOL END;

  rep <-- Rename_WRITE =
  CHOICE
    rep := TRUE || outptr := 0
  OR
    rep := FALSE
  END;

  rep,pp <-- Rename_READ  = 
  ANY bufsize WHERE  bufsize : SCALAR THEN
    CHOICE
      rep := TRUE || pp := bufsize || in := bufsize || inptr := 0
    OR
      rep := FALSE || pp := 0
    END
  END;

  rep <-- Rename_CLOSE = BEGIN rep :: BOOL END;



  /*** operations to read from the input buffer ***/

  rep,tok <-- Rename_GET_TOK(toksize : 1..4 ) =
  IF inptr+toksize <= in THEN
    tok :: TOK || inptr := inptr + toksize || rep := TRUE
  ELSE
    tok :: TOK || rep := FALSE
  END;

  rep,ss <-- Rename_GET_STR =
  IF inptr + 3 <= in THEN
    ANY str, newptr WHERE
      str : STRING & newptr = inptr + size(str) + 3
    THEN
      ss := str || inptr := newptr || rep := TRUE
    END
  ELSE
    ss :: STRING || rep := FALSE
  END;

  rep,filesize <-- Rename_GET_FIL(filename : STRING) =
  CHOICE
    ANY newptr  WHERE newptr : 0..in & newptr > inptr THEN
      inptr := newptr ||
      filesize :: SCALAR ||
      rep := TRUE
    END
  OR
    filesize :: SCALAR ||
    rep := FALSE
  END;



  /*** operations to to write the output buffer ***/

  rep <-- Rename_PUT_TOK(tok : TOK & toksize : 1..4 ) =
  CHOICE
    outptr := outptr+toksize || rep := TRUE
  OR
    rep := FALSE
  END;

  rep <-- Rename_PUT_STR(ss:STRING) =
  CHOICE
    outptr := outptr+size(ss)+3 || rep := TRUE
  OR
    rep := FALSE 
  END;



  /*** operations to get and set the input buffer pointer ***/

  Rename_SET_IN_PTR(ptr : NAT) = PRE ptr <= inptr THEN inptr := ptr END;

  ptr <-- Rename_GET_IN_PTR = BEGIN ptr := inptr END;



  /*** operations to get and set the output buffer pointer ***/

  Rename_SET_OUT_PTR(ptr : NAT) =  PRE ptr <= outptr THEN outptr := ptr END;

  ptr <-- Rename_GET_OUT_PTR = BEGIN ptr := outptr END


END
