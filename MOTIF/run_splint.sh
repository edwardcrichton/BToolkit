#/bin/bash
splint -DBTOOLKIT_FLAG -D__gnuc_va_list=va_list -DBoolean=int -DTrue=1 -DNULL=0 -warnposix -nullassign -predboolint -unqualifiedtrans -mustfreefresh -retvalint $1
