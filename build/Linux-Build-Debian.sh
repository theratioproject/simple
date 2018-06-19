#!/bin/bash

VERSION=s0.3.303
SIMPLE_DEBUG_VERSION=s0.3.303-debug

if [ -e ../simple/makefiles/Makefile-Linux.mk ]; then 
	cd ../simple/makefiles
	echo "SIMPLE $SIMPLE_DEBUG_VERSION build"
	echo "		Building simple and simple.so"
	make -f Makefile-Linux.mk uninstall 
	make -f Makefile-Linux.mk
	make -f Makefile-Linux.mk install 
	cd ../../build
else 
	echo "SIMPLE s0.3.303-debug build"
	echo "		The 'File Makefile-Linux.mk' does not exists"
	echo "		Skipping simple Build"
fi

#copy simple and simple.so to s0.3.303-debug folder
	echo "~"
	echo "	Copying simple executable and building $SIMPLE_DEBUG_VERSION "

if [ -e ../../$SIMPLE_DEBUG_VERSION/bin/ ]; then
	echo "	the ../../$SIMPLE_DEBUG_VERSION/bin already exist"
else
	echo "		Creating the ../../$SIMPLE_DEBUG_VERSION/bin folder"
	mkdir -p "../../$SIMPLE_DEBUG_VERSION/bin"
fi

if [ -e ../simple/dist/simple ]; then
	echo "		Copying simple and simple.so to ../../$SIMPLE_DEBUG_VERSION/bin folder"
	cp "../simple/dist/simple" "../../$SIMPLE_DEBUG_VERSION/bin"
	cp "../simple/dist/simple.so" "../../$SIMPLE_DEBUG_VERSION/bin"
else
	echo "		Build fails. Simple and simple.so cannot be found in the"
	echo "		../simple/dist folder. Try rebuilding the program individually"
	echo "		ff it ails again run the build individually"
fi

#copying the includes folder for developers
	echo "		~includes"
if [ -e ../simple/includes ]; then
	echo "		Copying includes to ../../$SIMPLE_DEBUG_VERSION/includes folder"
	cp -R "../simple/includes" "../../$SIMPLE_DEBUG_VERSION/includes"
else
	echo "		simple includes cannot be found"
	echo "		The repository appear to be corrupted. Try cloning again"
	echo "		to resolve the issue"
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
		make -f Makefile-Linux.mk uninstall
		make -f Makefile-Linux.mk
		make -f Makefile-Linux.mk install
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

#modules-dependencies.conf
	echo "		~modules-dependencies.conf"
if [ -e ../../modules/modules-dependencies.conf ]; then
	echo "		Copying modules-dependencies.conf to ../../$SIMPLE_DEBUG_VERSION/modules folder"
	cp "../../modules/modules-dependencies.conf" "../../$SIMPLE_DEBUG_VERSION/modules"
else
	echo "		modules-dependencies.conf module cannot be found"
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
if [ -e ../environment/modular/modular.sim ]; then
	echo "		Copying modular to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../environment/modular/modular.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "		../environment/modular/modular.sim cannot be found"
	echo "		skipping modular"
fi

#repl
	echo "		~repl"
if [ -e ../environment/repl/SimpleRepl.sim ]; then
	echo "		Copying SimpleRepl.sim to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../environment/repl/SimpleRepl.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "		../environment/repl/SimpleRepl.sim cannot be found"
	echo "		skipping repl"
fi

#SimplePad
	echo "		~simplepad"
if [ -e ../environment/simplepad/SimplePad.sim ]; then
	echo "		Copying SimplePad.sim to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../environment/simplepad/SimplePad.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "		../environment/simplepad/SimplePad.sim cannot be found"
	echo "		skipping simplepad"
fi

#smake
	echo "		~smake"
if [ -e ../environment/smake/smake.sim ]; then
	echo "		Copying smake.sim to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../environment/smake/smake.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "		../environment/smake/smake.sim cannot be found"
	echo "		skipping smake"
fi

#spider
	echo "		~spider"
if [ -e ../environment/spider/spider.sim ]; then
	echo "		Copying spider.sim to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../environment/spider/spider.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "		../environment/spider/spider.sim cannot be found"
	echo "		skipping spider"
fi

#Build the environment app note due to it been debug
#the executable enviroment might not run on a linux machine
#except the SIMPLE_PATH and SIMPLE_MODULE_PATH has been set
	echo "	Building the executable environments"
	echo "		we first check if the simple and smake.sim has benen copied"

echo "		checking simple"
if [ -e ../../$SIMPLE_DEBUG_VERSION/bin/simple ]; then
	echo "		simple is present now checking smake"
	cd "../../$SIMPLE_DEBUG_VERSION/bin"
else
	echo "		simple has not been built the building process "
	echo "		failed restart process again or build manually"
fi

echo "		checking smake"
if [ -e ../environment/smake.sim ]; then
	echo "		smake is present procedding build.."
	cd "../../$SIMPLE_DEBUG_VERSION/bin"
else
	echo "		sno smake no build bye "
	exit 
fi

#Now since the prequsite are present start build Always make smake the last
#build in this script because it the one building the former(s)
#Build SimpleRepl

echo "		building SimpleRepl"
if [ -e ../environment/SimpleRepl.sim ]; then
	echo "		building smake..."
	./simple ../environment/smake.sim -delete ../environment/SimpleRepl.sim
	rm ../environment/SimpleRepl.sim
else
	echo "		SimpleRepl.sim not present skipping "
fi

#Build modular

echo "		building modular"
if [ -e ../environment/modular.sim ]; then
	echo "		building modular..."
	./simple ../environment/smake.sim -delete ../environment/modular.sim
	rm ../environment/modular.sim
else
	echo "		modular.sim not present skipping "
fi

#Build SimplePad

echo "		building SimplePad"
if [ -e ../environment/SimplePad.sim ]; then
	echo "		building SimplePad..."
	./simple ../environment/smake.sim -delete ../environment/SimplePad.sim
	rm ../environment/SimplePad.sim
else
	echo "		SimplePad.sim not present skipping "
fi

#Build spider

echo "		building spider"
if [ -e ../environment/spider.sim ]; then
	echo "		building spider..."
	./simple ../environment/smake.sim -delete ../environment/spider.sim
	rm ../environment/spider.sim
else
	echo "		spider.sim not present skipping "
fi

#Build smake

echo "		building smake"
if [ -e ../environment/smake.sim ]; then
	echo "		building smake..."
	./simple ../environment/smake.sim -delete ../environment/smake.sim
	rm ../environment/smake.sim
else
	echo "		Seriously it an hack if smake not present "
fi

#Add Simple to path
echo "SIMPLE_PATH=\"/simple/\"" >> /etc/environment











