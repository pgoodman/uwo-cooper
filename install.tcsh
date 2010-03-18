#!/usr/bin/env tcsh

set DEST_DIR=$1

# make the dir where the stuff needs to go in
echo
echo "Making assignment directory..."
if (! -d $DEST_DIR) then
    mkdir $DEST_DIR
endif

# copy the executable into the destination dir
echo
echo "Copying files..."
cp -f ./cooper/cooper ./$DEST_DIR/cooper

# TODO: InstallFiles.txt and ReqsSatisfied.txt
cp -f ./cooper/ReqsSatisfied.txt ./$DEST_DIR
cp -f ./cooper/InstallFiles.txt ./$DEST_DIR

