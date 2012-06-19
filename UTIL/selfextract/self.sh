#!/bin/sh

echo "Installing BToolkit"
echo ""

HERE=`pwd`

TMP=`mktemp -d /tmp/btoolkit.XXX`
echo TMP $TMP
TAR=`awk '/^__TAR__/ {print NR + 1; exit 0; }' "$0"`
echo TAR $TAR

tail -n+${TAR} "$0" | tar x -C $TMP

cd $TMP

ls -lrt

gunzip DEBIAN.tar.gz
gunzip files.tar.gz

tar xf DEBIAN.tar
 
./DEBIAN/prerm upgrade
./DEBIAN/preinst upgrade

tar xf files.tar -C /

./DEBIAN/postrm upgrade
./DEBIAN/postinst configure ""

cd $HERE
rm -rf $TMP

exit 0

__TAR__
