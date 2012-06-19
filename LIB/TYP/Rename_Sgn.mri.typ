(Rename_VAL(vv;?) == (vv: SIGNED));
(Rename_STO(?;vv) == (vv: SIGNED));
(Rename_INC(?;?) == ?);
(Rename_DEC(?;?) == ?);
(Rename_ADD(?;vv) == (vv: SIGNED));
(Rename_SUB(?;vv) == (vv: SIGNED));
(Rename_MUL(?;vv) == (vv: SIGNED));
(Rename_DIV(?;vv) == (vv: SIGNED));
(Rename_MOD(?;vv) == (vv: SIGNED))
|
(Rename_sgn: SIGNED)|
(?)
