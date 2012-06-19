MACHINE           Rename_FileRefGen

SEES              String_TYPE

OPERATIONS

  filePathA,filePathB,filePathC,updatedYear,updatedRefNo
    <-- Rename_GEN_NEW_FILE_REF(refString : STRING & year : NAT & refNo : NAT) =
  BEGIN filePathA :: STRING || filePathB :: STRING || filePathC :: STRING || updatedYear :: NAT || updatedRefNo :: NAT END

END
