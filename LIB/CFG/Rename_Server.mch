MACHINE               Rename_Server(TOK,default_inbufsize,default_outbufsize)

CONSTRAINTS           default_inbufsize>=4 & default_outbufsize>=4

SEES                  String_TYPE, Scalar_TYPE, Bool_TYPE

VARIABLES             in,inptr,outptr,no_of_saves

INVARIANT

  in : SCALAR &
  inptr : 0..in &
  outptr : SCALAR &
  no_of_saves : NAT
   
INITIALISATION        in,inptr,outptr,no_of_saves := 0,0,0,0         

OPERATIONS


  /*** operation to initialise the socket ***/

  rep <-- Rename_INIT(lockfile : STRING & port : NAT & bufsavefile : STRING) =
  PRE size(lockfile) < 256 & size(bufsavefile) < 256 THEN rep :: BOOL END;



   /*** operations on the socket ***/

  rep <-- Rename_ACCEPT = BEGIN rep :: BOOL END; 

  rep,pp <-- Rename_READ  = 
  ANY bufsize WHERE  bufsize : SCALAR THEN
    CHOICE
      rep := TRUE || pp := bufsize || in := bufsize || inptr := 0
    OR
      rep := FALSE || pp := 0
    END
  END;

  rep <-- Rename_WRITE = BEGIN rep :: BOOL || outptr := 0 END;

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
    ANY str, newptr  WHERE
      str : STRING &  newptr = inptr + size(str) + 3
    THEN
      ss := str || inptr := newptr || rep := TRUE
    END
  ELSE
    ss :: STRING || rep := FALSE
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
    outptr := outptr+size(ss)+3  || rep := TRUE
  OR
    rep := FALSE 
  END; 



  /*** operations to get and set the input buffer pointer ***/

  Rename_SET_IN_PTR(ptr : NAT) = PRE ptr <= inptr THEN inptr := ptr END;

  ptr <-- Rename_GET_IN_PTR = BEGIN ptr := inptr END;



  /*** operations to get and set the output buffer pointer ***/

  Rename_SET_OUT_PTR(ptr : NAT) =  PRE ptr <= outptr THEN outptr := ptr END;

  ptr <-- Rename_GET_OUT_PTR = BEGIN ptr := outptr END;




  /*** Client initialisation ***/

  /* opens file, and appends its data until EOF to out_buf;
     then appends a null; gives FALSE if this fails.
  */
  rep <-- Rename_PUT_FILE(filename: STRING) = 
  CHOICE 
    rep := TRUE || outptr :: SCALAR
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
    inptr := 0 || in :: SCALAR
  END

END
