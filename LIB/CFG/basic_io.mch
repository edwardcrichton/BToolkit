MACHINE           basic_io

SEES              Scalar_TYPE, Int_TYPE, Bool_TYPE, String_TYPE, Bit_TYPE

OPERATIONS


/* Output */

  NWL(nn:NAT) = BEGIN skip END;                  /* prints nn newlines */

  BLK(nn:NAT) = BEGIN skip END;                  /* prints nn spaces */

  PUT_NBR(nn:NAT) = BEGIN skip END;              /* writes a number */

  PUT_NAT(nn:NAT) = BEGIN skip END;              /* writes a number */

  PUT_INT(nn:INT) = BEGIN skip END;              /* writes an integer as +nnn/-nnn */

  PUT_STR(ss:STRING) = BEGIN skip END;           /* writes a string */

  PUT_CHR(cc:CHAR) = BEGIN skip END;             /* writes a character */

  PUT_EOT = BEGIN skip END;                      /* writes EOT character */

  PUT_BOOL(bb:BOOL) = BEGIN skip END;            /* writes a boolean */

  PUT_BTS(bs:BITS) = BEGIN skip END;             /* writes a binary */

  FLSH = skip;                                   /* flushes output */


/* Output padded with blanks up to pd */

  PUT_NBR_PAD(nn:NAT & pd:NAT) = BEGIN skip END;     /* writes a number */

  PUT_NAT_PAD(nn:NAT & pd:NAT) = BEGIN skip END;     /* writes a number */

  PUT_INT_PAD(nn:INT & pd:NAT) = BEGIN skip END;     /* writes an integer as +nnn/-nnn */

  PUT_STR_PAD(ss:STRING & pd:NAT) = BEGIN skip END;  /* writes a string */

  PUT_BOOL_PAD(bb:BOOL & pd:NAT) = BEGIN skip END;   /* writes a boolean */


/* Input */

  mm <-- GET_NBR(nn:NAT) = BEGIN mm :: 0..nn END;   /* reads a number 0..nn */

  (rr:SCALAR) <-- GET_NAT;                          /* reads a number */
  
  (rr:INT) <-- GET_INT;                             /* reads an integer as +nnn/-nnn */
  
  (ss:STRING) <-- GET_STR;                          /* reads a string */

  (cc:CHAR) <-- GET_CHR;                            /* reads a character */

  (bb:BOOL) <-- GET_BOOL;                           /* reads a boolean */
  
  (bs:BITS) <-- GET_BTS;                            /* reads a binary */


/* Prompted Input */

 mm <-- GET_PROMPT_NBR(ss:STRING & nn:NAT) =
    BEGIN mm :: 0..nn END;                    /* prompts for a number 0..nn */

  rr <-- GET_PROMPT_NAT(ss:STRING) =
    BEGIN rr :: SCALAR END;                   /* prompts for a number */

  rr <-- GET_PROMPT_INT(ss:STRING) =
    BEGIN rr :: INT END;                      /* prompts for an integer as +nnn/-nnn */

  tt <-- GET_PROMPT_STR(ss:STRING ) =
    BEGIN tt :: STRING END;                   /* prompts for a string */

  nn <-- GET_PROMPT_CHR(ss:STRING) =
    BEGIN nn :: CHAR END;                     /* prompts for a character */

  rr <-- GET_PROMPT_BOOL(ss:STRING) =
    BEGIN rr :: BOOL END;                     /* prompts for a boolean */

  bs <-- GET_PROMPT_BTS(ss:STRING) =
    BEGIN bs :: BITS END;                     /* prompts for a binary */


/* stdout */

  rr <-- REDIR_stdout(file:STRING) = BEGIN rr :: BOOL END;

  rr <-- REAPP_stdout(file:STRING) = BEGIN rr :: BOOL END;

  rr <-- RESTR_stdout = BEGIN rr :: BOOL END


END
