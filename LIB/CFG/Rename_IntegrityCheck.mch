MACHINE           Rename_IntegrityCheck

SEES              Bool_TYPE, Scalar_TYPE

OPERATIONS

  rr <-- Rename_CheckIntegrity(print_flag : NAT) = BEGIN rr :: BOOL END;

  Rename_IntegritySetAllObjectsModified = BEGIN skip END;

  Rename_IntegrityResetAllObjectsModified = BEGIN skip END;

  Rename_IntegritySetObjectsModifiedFromModOp ( op : SCALAR ) = BEGIN skip END

END
