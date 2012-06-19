MACHINE

  Owners

SETS

  ACCTNO; CUSTNO; O_RESP = {success, noroom}

CONSTANTS

  specacct, speccust

PROPERTIES

  specacct : ACCTNO &
  speccust : CUSTNO

VARIABLES

  owner

INVARIANT

  owner : ACCTNO +-> CUSTNO &
  specacct |-> speccust : owner

DEFINITIONS

  accounts == dom (owner);
  customers == ran (owner)

INITIALISATION

  owner := {specacct |-> speccust}

OPERATIONS

  resp <-- new_acct_old_cust (cust, acct) =
    PRE
      cust : customers &
      acct : ACCTNO &
      acct /: accounts
    THEN
      CHOICE
        resp := success ||
        owner := owner \/ {acct |-> cust}
      OR
        resp := noroom
      END
    END
    ;
  resp, acct <-- alt_new_acct_old_cust (cust) =
    PRE
      cust : customers &
      accounts /= ACCTNO
    THEN
      CHOICE
        ANY
          ac
        WHERE
          ac : ACCTNO &
          ac /: accounts
        THEN
          resp := success ||
          owner(ac) := cust ||
          acct := ac
        END
      OR
        resp := noroom  ||
        acct :: ACCTNO
      END
    END

END
