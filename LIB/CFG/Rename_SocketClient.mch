MACHINE              Rename_SocketClient(TOK,insize,outsize)

SEES                 String_TYPE, Bool_TYPE

VARIABLES            in,inptr,outptr,outbufsize

INVARIANT
            outbufsize :  NAT1 &  outbufsize >= outsize &

            in : NAT1 &  in >= insize &
            inptr : 0..in &
            outptr : 0..outbufsize
   
INITIALISATION  
    
      in,inptr,outptr := 0,0,0 ||
      outbufsize  := outsize

OPERATIONS


  /*** operation to initialise ipaddress,port and reset pointers ***/

  rep <-- Rename_INIT(ipaddress : STRING & port : NAT) =
  BEGIN in,inptr,outptr,outbufsize := 0,0,0,outsize || rep :: BOOL END;



  /*** operations on the socket ***/

  rep <-- Rename_CONNECT = BEGIN rep :: BOOL END;

  rep <-- Rename_WRITE =
  CHOICE
    rep := TRUE || outptr := 0 ||
    outbufsize  := outsize
  OR
    rep := FALSE
  END;

  rep,pp <-- Rename_READ  = 
  ANY buf_size WHERE  buf_size : NAT1 &  buf_size >= insize  THEN
    CHOICE
      rep := TRUE || pp := buf_size || in := buf_size || inptr := 0
    OR
      rep := FALSE || pp := 0
    END
  END;

  rep <-- Rename_CLOSE = BEGIN rep :: BOOL END;



  /*** operations to read from the input buffer ***/

  tok <-- Rename_GET_TOK(toksize : 1..4 ) =
  IF inptr+toksize <= in THEN
    tok :: TOK || inptr := inptr + toksize
  ELSE
    tok :: TOK
  END;

  ss <-- Rename_GET_STR =
  IF inptr + 3 <= in THEN
    ANY str, newptr  WHERE
      str : STRING &  newptr = inptr + size(str) + 3
    THEN
      ss := str || inptr := newptr
    END
  ELSE
    ss :: STRING
  END;

  rep,filesize <-- Rename_GET_FIL(filename : STRING) =
  CHOICE
    ANY newptr  WHERE newptr : 0..in & newptr > inptr THEN
      inptr := newptr ||
      rep := TRUE ||
      filesize :: NAT
    END
  OR
    rep := FALSE ||
    filesize :: NAT
  END;



  /*** operations to to write the output buffer ***/

  Rename_PUT_TOK(tok : TOK & toksize : 1..4 ) =
  IF outptr+toksize <= outbufsize THEN
    outptr := outptr+toksize
  ELSE
     CHOICE
        outbufsize : ( outbufsize : NAT1 & outbufsize >= outptr+toksize ) ||
        outptr := outptr+toksize
     OR
        skip
     END
  END;

  Rename_PUT_STR(ss:STRING) =
  IF outptr+size(ss)+3 <= outbufsize THEN
    outptr := outptr+size(ss)+3 
  ELSE
     CHOICE
        outbufsize : ( outbufsize : NAT1 & outbufsize >= outptr+size(ss)+3 ) ||
        outptr := outptr+size(ss)+3
     OR
        skip
     END 
  END;



  /*** operations to get and set the input buffer pointer ***/

  Rename_SET_IN_PTR(ptr : NAT) = PRE ptr <= inptr THEN inptr := ptr END;

  ptr <-- Rename_GET_IN_PTR = BEGIN ptr := inptr END;



  /*** operations to get and set the output buffer pointer ***/

  Rename_SET_OUT_PTR(ptr : NAT) =  PRE ptr <= outptr THEN outptr := ptr END;

  ptr <-- Rename_GET_OUT_PTR = BEGIN ptr := outptr END;
  
  sz <-- Rename_GET_OUT_SIZE = BEGIN sz := outbufsize END




END
