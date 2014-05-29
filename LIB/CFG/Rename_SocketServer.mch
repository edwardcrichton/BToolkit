MACHINE               Rename_SocketServer(TOK,insize,outsize)

SEES                  String_TYPE, Bool_TYPE

VARIABLES             in,inptr,outptr,no_of_saves,outbufsize

INVARIANT

  outbufsize : NAT1 & outbufsize >= outsize &

  in : NAT1 & in >= insize &
  inptr : 0..in &
  outptr : 0..outbufsize &
  no_of_saves : NAT
   
INITIALISATION       

      in,inptr,outptr,no_of_saves := 0,0,0,0  ||
      outbufsize  := outsize    

OPERATIONS


  /*** operation to initialise the socket ***/

  rep <-- Rename_INIT(lockfile : STRING & port : NAT & bufsavefile : STRING) =
  PRE size(lockfile) < 256 & size(bufsavefile) < 256 THEN rep :: BOOL END;



   /*** operations on the socket ***/

  rep <-- Rename_ACCEPT = BEGIN rep :: BOOL END; 

  rep,pp <-- Rename_READ  = 
  ANY buf_size WHERE  buf_size : NAT1 & buf_size >= insize THEN
    CHOICE
      rep := TRUE || pp := buf_size || in := buf_size || inptr := 0 
    OR
      rep := FALSE || pp := 0
    END
  END;

  rep <-- Rename_WRITE = 
  BEGIN 
     rep :: BOOL || outptr := 0 || 
     outbufsize  := outsize  
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
  
  sz <-- Rename_GET_OUT_SIZE = BEGIN sz := outbufsize END;



  /*** Client initialisation ***/

  /* opens file, and appends its data until EOF to out_buf;
     then appends a null; gives FALSE if this fails.
  */
  rep <-- Rename_PUT_FILE(filename: STRING) = 
  CHOICE 
    rep := TRUE ||
    ANY sz,ptr WHERE
        sz : NAT1 & sz >= outptr+size(filename)+5 &
        ptr : outptr+size(filename)+5 .. sz
    THEN
      outbufsize := sz ||
      outptr := ptr ||
      rep := TRUE
    END
  OR  
    rep := FALSE  
  END;



  /*** Buffer saving and restoring ***/

  /* appends in_buf to bufsavefile of saved in buffers
  */
  rep, num_saves <-- Rename_SAV_BUF =
  CHOICE 
    rep := TRUE || num_saves := no_of_saves + 1 
  OR  
    rep := FALSE || num_saves := 0
  END;

  /* Empty bufsavefile
  */
  Rename_SAV_RMV = BEGIN no_of_saves := 0 END;

  /* returns TRUE if bufsavefile not empty, else returns FALSE
  */
  rep <-- Rename_RST_BUF = BEGIN rep :: BOOL END;
 
  /* restores next saved buffer in inbuf; returns FALSE if finished
  */
  rep <-- Rename_NXT_BUF = 
  SELECT true THEN  
    rep := FALSE
  WHEN no_of_saves > 0 THEN 
    no_of_saves := no_of_saves - 1 || rep := TRUE || 
    inptr := 0 || in :: NAT1
  END

END
