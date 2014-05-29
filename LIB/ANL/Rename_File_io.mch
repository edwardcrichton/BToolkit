MACHINE         Rename_File_io(TOKEN)

SEES            String_TYPE, Scalar_TYPE, Bool_TYPE

OPERATIONS

  rep <-- Rename_OPEN_READ(filename : STRING) = BEGIN rep :: BOOL END;

  rep <-- Rename_OPEN_WRITE(filename : STRING) = BEGIN rep :: BOOL END;

  rep <-- Rename_OPEN_APPEND(filename : STRING) = BEGIN rep :: BOOL END;

  rep <-- Rename_CLOSE = BEGIN rep :: BOOL END;

  rep <-- Rename_PUT_STR(ss : STRING) = BEGIN rep :: BOOL END;

  rep <-- Rename_PUT_CHAR(cc : CHAR) = BEGIN rep :: BOOL END;

  rep <-- Rename_PUT_BLK(nn: SCALAR) = BEGIN rep :: BOOL END;

  rep <-- Rename_PUT_NWL(nn : SCALAR) = BEGIN rep :: BOOL END;

  rep <-- Rename_PUT_NAT(nn : SCALAR) = BEGIN rep :: BOOL END;

  rep <-- Rename_PUT_TOK(tt : TOKEN) = BEGIN rep :: BOOL END;

  rep,ss <-- Rename_GET_STR = BEGIN rep :: BOOL || ss :: STRING END;

  rep,cc <-- Rename_GET_CHAR = BEGIN rep :: BOOL || cc :: CHAR END;

  rep,nn <-- Rename_GET_NAT = BEGIN rep :: BOOL || nn :: SCALAR END;

  rep,tt <-- Rename_GET_TOK = BEGIN rep :: BOOL || tt :: TOKEN END;

  rep <-- Rename_FLUSH = BEGIN rep :: BOOL END

END
