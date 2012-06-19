MACHINE           Crypt

SEES              String_TYPE, Bool_TYPE

OPERATIONS

  /* ss created using crypt */

  ss <-- CRYPT(key : STRING) = BEGIN ss :: STRING END;


  /* key is then checked against encryption using crypt,
     salt being provided by first two chars of encryption */

  rr <-- CRYPT_CHECK(key : STRING & encryption : STRING) =
  PRE size(encryption) > 1 THEN rr :: BOOL END

END
