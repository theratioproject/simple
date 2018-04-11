#!/bin/bash

SIMPLE_DEBUG_VERSION=s0.3.302-debug

if [ -e ../src/makefiles/Makefile-Linux.mk s]; then 
	cd ../src/makefiles
	echo "SIMPLE $SIMPLE_DEBUG_VERSION build"
	echo "		Building simple and simple.so"
	make -f Makefile-Linux.mk
	cd ../../build
else 
	echo "SIMPLE s0.3.302-debug build"
	echo "		The 'File Makefile-Linux.mk' does not exists"
	echo "		Skipping simple Build"
fi

#copy simple and simple.so to s0.3.302-debug folder
	echo "~"
	echo "	Copying simple executable and building $SIMPLE_DEBUG_VERSION "

if [ -e ../../$SIMPLE_DEBUG_VERSION/bin/ ]; then
	echo "	the ../../$SIMPLE_DEBUG_VERSION/bin already exist"
else
	echo "		Creating the ../../$SIMPLE_DEBUG_VERSION/bin folder"
	mkdir -p "../../$SIMPLE_DEBUG_VERSION/bin"
fi

if [ -e ../src/dist/simple ]; then
	echo "		Copying simple and simple.so to ../../$SIMPLE_DEBUG_VERSION/bin folder"
	cp "../src/dist/simple" "../../$SIMPLE_DEBUG_VERSION/bin"
	cp "../src/dist/simple.so" "../../$SIMPLE_DEBUG_VERSION/bin"
else
	echo "		Build fails. Simple and simple.so cannot be found in the"
	echo "		../src/dist folder. Try rebuilding the program individually"
	echo "		ff it ails again run the build individually"
fi

#Buld dynamic modules
	echo "~"
	echo "	Building Dynamic Modules "

if [ -e ../../modules ]; then
	cd ../../modules
	echo "		Modules repository detected"
	if [ -e ./dynamic_modules/makefiles/Makefile-Linux.mk ]; then

	else

	fi
else
	echo "		Modules repository does not exist"
	echo "		Clone the repository in the same folder as simple and environment"
	echo "		if you want to build the modules and dynamic_modules else you can "
	echo "		ignore it and continue building simple "
fi

























