MACHINE         Rename_token_io(TOKEN)

SEES            String_TYPE

OPERATIONS


  /* operations deal with scalars */

  tt <-- Rename_GET_TOK = 
    BEGIN
      tt :: TOKEN           /* reads a token (0..2147483646) */
    END;

  tt <-- Rename_GET_PROMPT_TOK(ss : STRING) = 
    BEGIN
      tt :: TOKEN           /* prompts for a token (0..2147483646) */
    END;

   Rename_PUT_TOK(tt : TOKEN) = 
    BEGIN skip END;         /* printed as tt */



  /* operations deal with enumerated elements */

 tt <-- Rename_GET_ACT_TOK(SS : POW(TOKEN)) = 
    BEGIN
      tt :: SS             /* gets a token (by presenting a list) */
    END;

  tt <-- Rename_GET_PROMPT_ACT_TOK(SS : POW(TOKEN) & ss : STRING) = 
    BEGIN
      tt :: TOKEN           /* prompts for a token(by presenting a list) */
    END;

  Rename_PUT_ACT_TOK(SS : POW(TOKEN) & tt : SS) =
    BEGIN skip END          /* actual value printed if possible, else tt(SS) */

END
