#!/bin/bash

SIMPLE_DEBUG_VERSION=s0.3.302-debug

if [ -e ../src/makefiles/Makefile-Linux.mk ]; then 
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
		cd ./dynamic_modules/makefiles/
		echo "		Starting build..."
		make -f Makefile-Linux.mk
		cd ../../
	else
		echo "		dynamic_modules folder is missing "
		echo "		simply clone the modules repository again "
	fi
	cd ../simple/build
else
	echo "		Modules repository does not exist"
	echo "		Clone the repository in the same folder as simple and environment"
	echo "		if you want to build the modules and dynamic_modules else you can "
	echo "		ignore it and continue building simple "
fi

#moving the modules to the debug folder
	echo "~"
	echo "	Moving the Dynamic Modules to $SIMPLE_DEBUG_VERSION folder"

if [ -e ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules/ ]; then
	echo "	the ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules already exist"
else
	echo "		Creating the ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules folder"
	mkdir -p "../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules"
fi

if [ -e ../../modules/dynamic_modules/dist/systemic.so ]; then
	echo "		Copying dynamic_modules to ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules"
	cp ../../modules/dynamic_modules/dist/*.so ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules
else
	echo "		Building of dynamic modules fails"
	echo "		rebuild the modules individually to resolve issue"
fi

#Resolve dependency
#All the current dependencies are built into linux

#Copy the simple modules
	echo "~"
	echo "	Copying Simple Modules to $SIMPLE_DEBUG_VERSION folder"

#Simple core modules
	echo "		~simple core modules"
if [ -e ../../modules/simple ]; then
	echo "		Copying simple module to ../../$SIMPLE_DEBUG_VERSION/modules/simple folder"
	cp -R "../../modules/simple" "../../$SIMPLE_DEBUG_VERSION/modules/simple"
else
	echo "		simple module cannot be found"
	echo "		The repository appear to be currupted. Try clonning again"
	echo "		to resolve the issue"
fi

#archive modules
	echo "		~archive module"
if [ -e ../../modules/archive ]; then
	echo "		Copying archive module to ../../$SIMPLE_DEBUG_VERSION/modules/archive folder"
	cp -R "../../modules/archive" "../../$SIMPLE_DEBUG_VERSION/modules/archive"
else
	echo "		archive module cannot be found"
	echo "		The repository appear to be currupted. Try clonning again"
	echo "		to resolve the issue"
fi

#web modules
	echo "		~web module"
if [ -e ../../modules/web ]; then
	echo "		Copying web module to ../../$SIMPLE_DEBUG_VERSION/modules/web folder"
	cp -R "../../modules/web" "../../$SIMPLE_DEBUG_VERSION/modules/web"
else
	echo "		web module cannot be found"
	echo "		The repository appear to be currupted. Try clonning again"
	echo "		to resolve the issue"
fi

#fulltick(GUI) modules
	echo "		~fulltick module"
if [ -e ../../modules/fulltick ]; then
	echo "		Copying fulltick module to ../../$SIMPLE_DEBUG_VERSION/modules/fulltick folder"
	cp -R "../../modules/fulltick" "../../$SIMPLE_DEBUG_VERSION/modules/fulltick"
else
	echo "		fulltick module cannot be found"
	echo "		The repository appear to be currupted. Try clonning again"
	echo "		to resolve the issue"
fi

#ENVIRONMENT PROGRAMS
	echo "~"
	echo "	Copying Environment Programs to $SIMPLE_DEBUG_VERSION folder"

if [ -e ../../$SIMPLE_DEBUG_VERSION/environment ]; then
	echo "		the ../../$SIMPLE_DEBUG_VERSION/environment already exist"
else 
	echo "		Creating the ../../$SIMPLE_DEBUG_VERSION/environment directory"
	mkdir "../../$SIMPLE_DEBUG_VERSION/environment"
fi

#modular
	echo "		~modular"
if [ -e ../../environment/modular/modular.sim ]; then
	echo "		Copying modular to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../../environment/modular/modular.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "		../../environment/modular/modular.sim cannot be found"
	echo "		skipping modular"
fi

#repl
	echo "		~repl"
if [ -e ../../environment/modular/SimpleRepl.sim ]; then
	echo "		Copying SimpleRepl.sim to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../../environment/repl/SimpleRepl.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "		../../environment/repl/SimpleRepl.sim cannot be found"
	echo "		skipping repl"
fi

#SimplePad
	echo "		~simplepad"
if [ -e ../../environment/simplepad/SimplePad.sim ]; then
	echo "		Copying SimplePad.sim to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../../environment/simplepad/SimplePad.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "		../../environment/simplepad/SimplePad.sim cannot be found"
	echo "		skipping simplepad"
fi

#smake (undone)

#spider
	echo "		~spider"
if [ -e ../../environment/spider/spider.sim ]; then
	echo "		Copying spider.sim to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../../environment/spider/spider.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "		../../environment/spider/spider.sim cannot be found"
	echo "		skipping spider"
fi













