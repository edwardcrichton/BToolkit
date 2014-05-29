MACHINE      Rename_file_dump

SEES         Bool_TYPE

OPERATIONS

  rep <-- Rename_open_write_dump = BEGIN rep :: BOOL END;

  rep <-- Rename_open_read_dump = BEGIN rep :: BOOL END;

  rep <-- Rename_close_dump =  BEGIN rep :: BOOL END

END
