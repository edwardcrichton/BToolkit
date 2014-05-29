MACHINE           Rename_FileRefYearGen

SEES              String_TYPE

OPERATIONS

  filePath,updatedYear,updatedRefNo <-- GEN_FILE_REF_YEAR(refString : STRING & year : NAT & refNo : NAT) =
  BEGIN filePath :: STRING || updatedYear :: NAT || updatedRefNo :: NAT END

END
