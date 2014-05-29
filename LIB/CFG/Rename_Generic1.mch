MACHINE           Rename_Generic1(REPORT)

/*** a mchine exclusively used in SSTL DcrModify generation,
     providing a tempate for a generated machine ***/

SEES              Bool_TYPE

OPERATIONS

  case_hit,crr <-- Rename_Generic1_op(op : NAT) =
  BEGIN case_hit :: BOOL || crr :: REPORT END

END
