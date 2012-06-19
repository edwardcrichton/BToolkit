#! /bin/csh -f

#
# Build!
#

set curdir = `pwd`
cd ..

echo ""
echo '  This script builds an entire '
echo "  installation in `pwd`/BKIT "

if ( -d BKIT ) then
  echo ""
  echo ""
  echo "  `pwd`/BKIT currently exists"
  echo ""
  echo -n "  Remove before starting ( start from scratch ) [N/y]? "
  set answer=$<
  echo ""
  if ( $answer == "y" || $answer == "yes" ) then
  rm -Rf BKIT
    echo ""
    echo "  Removed `pwd`/BKIT "
    echo ""

    find . -type f -name '*.o' -delete
    echo "  Cleaned .o files"

  else
    echo "  `pwd`/BKIT not removed"
    echo ""
    echo ""    
  endif
  echo ""
endif

cd $curdir

##############################################################
#
#  Ensure BKIT directory. Set B_server and B_port (no longer needed though)
#
##############################################################

set curdir = `pwd`
cd ..
setenv BKIT `pwd`/BKIT
if ( ! -d $BKIT ) then
  mkdir $BKIT
endif
if ( ! -d $BKIT/BLIB ) then
  mkdir $BKIT/BLIB
endif
cd $curdir

if ( ! -f $BKIT/B_server ) then

    set bserver=`uname -n`
  
  echo "$bserver" > $BKIT/B_server

endif

if ( ! -f $BKIT/B_port ) then

    set bport="2107"
  
  echo "$bport" > $BKIT/B_port

endif

echo ""
echo "  Entry point: "
echo ""

echo "   2    CRE_c "
echo "   3    CRE_b "
echo "   4    CRE_BTool "
echo "   5    CRE_bplatform "
echo "   6    CRE_lex "
echo "   7    CRE_motif "
echo "   8    _link_BMotif "
echo "   9    CPY_scripts "
echo "  10    CPY_lib "
echo "  11    CPY_help "
echo "  12    CPY_palette "
echo "  13    CPY_b2doors "
echo "  14    CPY_demo "
echo "  15    CPY_BTool_Tutorial "
echo "  16    CPY_ErrorCodes "
echo "  17    CRE_toolkit_binaries_all "
echo "  18    CRE_launcher "
echo ""
echo "  19    abort "
echo "   A    all"

echo ""
echo -n "  Number? "
set answer=$<

if ( $answer == "A" ) then
  setenv ask "no"
  set answer="2"
else

endif

switch ( $answer )
  case "1":
    set level = 1
    breaksw
  case "2":
    set level = 2
    breaksw
  case "3":
    set level = 3
    breaksw
  case "4":
    set level = 4
    breaksw
  case "5":
    set level = 5
    breaksw
  case "6":
    set level = 6
    breaksw
  case "7":
    set level = 7
    breaksw
  case "8":
    set level = 8
    breaksw
  case "9":
    set level = 9
    breaksw
  case "10":
    set level = 10
    breaksw
  case "11":
    set level = 11
    breaksw
  case "12":
    set level = 12
    breaksw
  case "13":
    set level = 13
    breaksw
  case "14":
    set level = 14
    breaksw
  case "15":
    set level = 15
    breaksw
  case "16":
    set level = 16
    breaksw
  case "17":
    set level = 17
    breaksw
  case "18":
    set level = 18
    breaksw
  default:
    echo ""
    echo "  Aborted"
    echo ""
    exit ( 1 )
    breaksw
endsw


if ( -f ./build_trace.txt ) then
rm ./build_trace.txt
endif

touch ./build_trace.txt

if ( $level <= 2 ) then
  CRE_c |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 3 ) then
  CRE_b |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 4 ) then
  CRE_BTool |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 5 ) then
  CRE_bplatform |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 6 ) then
  CRE_lex |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 7 ) then
  CRE_motif |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 8 ) then
  _link_BMotif |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 9 ) then
  CPY_scripts |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 10 ) then
  CPY_lib |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 11 ) then
  CPY_help |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 12 ) then
  CPY_palette |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 13 ) then
  CPY_b2doors |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 14 ) then
  CPY_demo |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 15 ) then
  CPY_BTool_Tutorial |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 16 ) then
  CPY_ErrorCodes |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 17 ) then
  CRE_toolkit_binaries_all |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

if ( $level <= 18 ) then
  CRE_launcher |& tee build_trace.txt
  if ( $status != 0 ) then
    echo ""
    echo "  Build aborted"
    echo ""
    exit ( 1 )
  endif
endif

echo ""
echo ""
echo "  BUILD `pwd`/BKIT complete"
echo ""
