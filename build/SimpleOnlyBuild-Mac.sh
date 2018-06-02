#!/bin/bash

VERSION=s0.3.303
SIMPLE_DEBUG_VERSION=s0.3.303-debug
PWD=$(pwd)

cd build
if [ -e ../src/makefiles/Makefile-Mac.mk ]; then
    cd ../src/makefiles
    echo "SIMPLE $SIMPLE_DEBUG_VERSION build"
    echo "       Building simple and simple.dylib ..."
    echo "       Build completed!"
    make -s -f Makefile-Mac.mk
    rm -rf ../sources/*.o
    mkdir -p ../../dist
    mv "./simple.dylib" "../../dist/simple.dylib"
    mv "./a.out" "../../dist/simple"
    # Copy executable and dynamic library to directories where it can be acessed directly from the shell.
    cp "../../dist/simple.dylib" "/usr/local/lib/simple.dylib"
    cp "../../dist/simple" "/usr/local/bin/simple"
    cd $PWD
    echo "Type \`simple\` and enter to begin using the compiler"
else
    echo "SIMPLE $SIMPLE_DEBUG_VERSION build"
    echo "       The file `Makefile-Mac.mk` does not exist"
    echo "       Skipping simple build"
fi
