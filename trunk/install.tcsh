#!/usr/bin/env tcsh

set BIN_DIR=bin
set DEST_DIR=dir

# make sure environment vars are set
echo
echo "Setting Environment Variables..."
setenv PATH /faculty/andrews/Qt-4.6.0/bin:$PATH
setenv LD_LIBRARY_PATH /faculty/andrews/Qt-4.6.0/lib:$LD_LIBRARY_PATH

# make a dir for binaries
if (! -d $BIN_DIR) then
    echo
    echo "Making compilation directory..."
    mkdir $BIN_DIR
endif

# make the project file
echo
echo "Making Project File..."
qmake -project -o uwo-cooper.pro

# go and make the makefile
cd bin
qmake -makefile -o Makefile -unix "INCLUDEPATH+=/faculty/andrews/Qt-4.6.0/include/QtSql" "QMAKE_LIBS=-lQtSql" ../uwo-cooper.pro

# clean out the dir for the binaries
echo
echo "Compiling Cooper..."
make clean
make

# go back up
cd ../

# make the dir where the stuff needs to go in
echo
echo "Making assignment directory..."
if (! -d $DEST_DIR) then
    mkdir $DEST_DIR
endif

# copy the executable into the destination dir
echo
echo "Copying files..."
cp -f ./$BIN_DIR/uwo-cooper ./$DEST_DIR/cooper

# TODO: InstallFiles.txt and ReqsSatisfied.txt
