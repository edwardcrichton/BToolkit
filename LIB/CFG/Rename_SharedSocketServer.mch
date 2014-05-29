MACHINE               Rename_SharedSocketServer(TOK,insize,outsize)

  /*** stateless version of Rename_SocketServer, allowing sharing ***/


SEES                  String_TYPE, Bool_TYPE

OPERATIONS


  /*** operation to initialise the socket ***/

  rep <-- Rename_INIT(lockfile : STRING & port : NAT & bufsavefile : STRING) =
  PRE size(lockfile) < 256 & size(bufsavefile) < 256 THEN rep :: BOOL END;



   /*** operations on the socket ***/

  rep <-- Rename_ACCEPT = BEGIN rep :: BOOL END; 

  rep,pp <-- Rename_READ  = BEGIN rep :: BOOL || pp :: NAT END; 

  rep <-- Rename_WRITE = BEGIN rep :: BOOL END; 

  rep <-- Rename_CLOSE = BEGIN rep :: BOOL END;



  /*** operations to read from the input buffer ***/

  tok <-- Rename_GET_TOK(toksize : 1..4 ) = BEGIN tok :: TOK END;

  ss <-- Rename_GET_STR = BEGIN ss :: STRING END;



  /*** operations to to write the output buffer ***/

  Rename_PUT_TOK(tok : TOK & toksize : 1..4 ) = skip;

  Rename_PUT_STR(ss:STRING) = skip;



  /*** operations to get and set the input buffer pointer ***/

  Rename_SET_IN_PTR(ptr : NAT) = skip;

  ptr <-- Rename_GET_IN_PTR = BEGIN ptr :: NAT END;



  /*** operations to get and set the output buffer pointer ***/

  Rename_SET_OUT_PTR(ptr : NAT) =  skip;

  ptr <-- Rename_GET_OUT_PTR = BEGIN ptr :: NAT END;
  
  sz <-- Rename_GET_OUT_SIZE = BEGIN sz :: NAT END;



  /*** Client initialisation ***/

  /* opens file, and appends its data until EOF to out_buf;
     then appends a null; gives FALSE if this fails.
  */
  rep <-- Rename_PUT_FILE(filename: STRING) = BEGIN rep :: BOOL END; 



  /*** Buffer saving and restoring ***/

  /* appends in_buf to bufsavefile of saved in buffers
  */
  rep, num_saves <-- Rename_SAV_BUF = BEGIN rep :: BOOL || num_saves:: NAT END; 


  /* Empty bufsavefile
  */
  Rename_SAV_RMV = skip;

  /* returns TRUE if bufsavefile not empty, else returns FALSE
  */
  rep <-- Rename_RST_BUF = BEGIN rep :: BOOL END;
 
  /* restores next saved buffer in inbuf; returns FALSE if finished
  */
  rep <-- Rename_NXT_BUF = BEGIN rep :: BOOL END;


  /* available when compiled with flag SERVER_STATS_FLAG, else returns FALSE,""
  */
  rep,filename <-- Rename_PrintStats = BEGIN rep :: BOOL || filename :: STRING END

END
