#!/bin/bash

VERSION=s0.3.303
SIMPLE_DEBUG_VERSION=s0.3.303-debug
FULLTICK_BUILD_ISSUE=https://github.com/simple-lang/simple/issues/35

echo "	simple-lang build $SIMPLE_DEBUG_VERSION"

#Remove previous build of current version
if [ -e ../../$SIMPLE_DEBUG_VERSION/ ]; then
	echo "a previous simple build $SIMPLE_DEBUG_VERSION is detected"
	echo "removing previous build and performing a clean build"
	rm -R ../../$SIMPLE_DEBUG_VERSION/ 
fi

if [ -e ../simple/makefiles/Makefile-Linux.mk ]; then 
	cd ../simple/makefiles
	echo "simple: simple-lang $SIMPLE_DEBUG_VERSION build" 
	echo "simple: building simple.so and simple"
	if [ -e ../dist/ ]; then
		echo "simple: removing previous simple build"
		rm -R ../dist/
	fi
	make -f Makefile-Linux.mk uninstall 
	make -f Makefile-Linux.mk
	make -f Makefile-Linux.mk install 
	cd ../../build
else 
	echo "error:simple: simple-lang $SIMPLE_DEBUG_VERSION build "
	echo "error:simple: the file 'Makefile-Linux.mk' does not exist in simple directory"
	echo "error:simple: skipping simple Build"
fi

#copy simple and simple.so to s0.3.303-debug folder
	echo "	Copying simple executable and building $SIMPLE_DEBUG_VERSION "

if [ -e ../../$SIMPLE_DEBUG_VERSION/bin/ ]; then
	echo "simple:bin: the ../../$SIMPLE_DEBUG_VERSION/bin already exist"
else
	echo "simple:bin: creating the ../../$SIMPLE_DEBUG_VERSION/bin folder"
	mkdir -p "../../$SIMPLE_DEBUG_VERSION/bin"
fi

if [ -e ../simple/dist/simple ]; then
	echo "simple: copying simple and simple.so to ../../$SIMPLE_DEBUG_VERSION/bin folder"
	cp "../simple/dist/simple" "../../$SIMPLE_DEBUG_VERSION/bin"
	cp "../simple/dist/simple.so" "../../$SIMPLE_DEBUG_VERSION/bin"
else
	echo "error:simple: build fails simple.exe and simple.dll cannot be found"
	echo "error:simple: try rebuilding individually"
fi

#copying the includes folder for developers
	echo "copying includes directory for developer"
if [ -e ../simple/includes ]; then
	echo "includes: copying includes to ../../$SIMPLE_DEBUG_VERSION/includes folder"
	cp -R "../simple/includes" "../../$SIMPLE_DEBUG_VERSION/includes"
else
	echo "error:includes: the includes directory cannot be found"
	echo "error:includes: the repository appears to be currupted. "
	echo "error:includes: try clonning the simple repository again to resolve the issue"
fi

#Resolve dependency
#Most the current dependencies are moved with linux
#if some of the dependencies are missing you can use apt-get to install them
#	sudo apt-get install libcurl
#

#Buld dynamic modules
	echo "	Building Dynamic Modules "

if [ -e ../modules ]; then
	cd ../modules
	echo "modules: modules repository detected"
	if [ -e ./dynamic_modules/makefiles/Makefile-Linux.mk ]; then
		cd ./dynamic_modules/makefiles/
		if [ -e ../dist/ ]; then
			echo "dynamic_modules: removing previous dynamic modules build"
			rm -R ../dist/
		fi
		echo "dynamic_modules: build starting..."
		make -f Makefile-Linux.mk uninstall
		make -f Makefile-Linux.mk
		make -f Makefile-Linux.mk install
		cd ../
	else
		echo "error:dynamic_modules directory does not exist"
		echo "error:dynamic_modules: the repository appears to be currupted. "
		echo "error:dynamic_modules: try clonning the simple repository again to resolve the issue"
	fi
	cd ../../build
else
	echo "error:modules: modules directory does not exist"
	echo "error:modules: the repository appears to be currupted." 
	echo "error:modules: try clonning the simple repository again to resolve the issue"

fi

#moving the modules to the debug folder
	echo "dynamic_modules: moving the Dynamic Modules to $SIMPLE_DEBUG_VERSION folder"

if [ -e ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules/ ]; then
	echo "dynamic_modules: the ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules already exist"
else
	echo "dynamic_modules: creating the ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules folder"
	mkdir -p "../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules"
fi

if [ -e ../modules/dynamic_modules/dist/systemic.so ]; then
	echo "dynamic_modules: copying dynamic_modules to ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules"
	cp ../modules/dynamic_modules/dist/*.so ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules
else
	echo "error:dynamic_modules: build fails the dynamic modules cannot be found"
	echo "error:dynamic_modules: try building each module individually "
fi

# fulltick(GUI) dynamic_module
	echo "dynamic_modules:fulltick: checking if fulltick build successfully"
if [ -e ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules/fulltick.so ]; then
	echo "dynamic_modules:fulltick: fulltick dynamic module built successfully"
else
	echo "error:dynamic_modules:fulltick: fulltick dynamic module build failed"
	echo "error:dynamic_modules:fulltick: fulltick build is sure to fail if you don't have fltk library installed or it is not configured as shared library"
	echo "error:dynamic_modules:fulltick: visit $FULLTICK_BUILD_ISSUE for build instruction"
	echo "dynamic_modules:fulltick: falling back on available backup build."
	if [ -e ../modules/dynamic_modules/fulltick/dist/fulltick.so ]; then
		echo "dynamic_modules:fulltick: backup build found but might be outdated"
		echo "dynamic_modules:fulltick: copying fulltick.so to ../../$SIMPLE_DEBUG_VERSION/bin directory"
		cp ../modules/dynamic_modules/fulltick/dist/fulltick.so ../../$SIMPLE_DEBUG_VERSION/modules/dynamic_modules
	else
		echo "error:dynamic_modules:fulltick: the backup fulltick dynamic module cannot be found"
		echo "error:dynamic_modules:fulltick: the repository appears to be currupted. "
		echo "error:dynamic_modules:fulltick: try clonning the simple repository again to resolve the issue"
		echo "error:dynamic_modules:fulltick: or visit $FULLTICK_BUILD_ISSUE to build instruction"
	fi
fi

#Copy the simple modules
	echo "	Copying Simple Modules to $SIMPLE_DEBUG_VERSION folder"

#Simple core modules
	echo "modules: simple core modules"
if [ -e ../modules/simple ]; then
	echo "modules: copying simple module to ../../$SIMPLE_DEBUG_VERSION/modules/simple folder"
	cp -R "../modules/simple" "../../$SIMPLE_DEBUG_VERSION/modules/simple"
else
	echo "error:modules: the simple core module cannot be found"
	echo "error:modules: the repository appears to be currupted."
	echo "error:modules: try clonning the simple repository again to resolve the issue"
fi

#archive modules
	echo "modules: archive module"
if [ -e ../modules/archive ]; then
	echo "modules: copying archive module to ../../$SIMPLE_DEBUG_VERSION/modules/archive folder"
	cp -R "../modules/archive" "../../$SIMPLE_DEBUG_VERSION/modules/archive"
else
	echo "error:modules: the archive module cannot be found"
	echo "error:modules: the repository appears to be currupted."
	echo "error:modules: try clonning the simple repository again to resolve the issue"
fi

#web modules
	echo "modules: web module"
if [ -e ../modules/web ]; then
	echo "modules: copying web module to ../../$SIMPLE_DEBUG_VERSION/modules/web folder"
	cp -R "../modules/web" "../../$SIMPLE_DEBUG_VERSION/modules/web"
else
	echo "error:modules: the web module cannot be found"
	echo "error:modules: the repository appears to be currupted."
	echo "error:modules: try clonning the simple repository again to resolve the issue"
fi

#fulltick(GUI) modules
	echo "modules: fulltick module"
if [ -e ../modules/fulltick ]; then
	echo "modules: copying fulltick module to ../../$SIMPLE_DEBUG_VERSION/modules/fulltick folder"
	cp -R "../modules/fulltick" "../../$SIMPLE_DEBUG_VERSION/modules/fulltick"
else
	echo "error:modules: the fulltick GUI module cannot be found"
	echo "error:modules: the repository appears to be currupted."
	echo "error:modules: try clonning the simple repository again to resolve the issue"
fi

#modules-dependencies.conf
	echo "modules: modules-dependencies.conf"
if [ -e ../modules/modules-dependencies.conf ]; then
	echo "modules: copying modules-dependencies.conf to ../../$SIMPLE_DEBUG_VERSION/modules folder"
	cp "../modules/modules-dependencies.conf" "../../$SIMPLE_DEBUG_VERSION/modules"
else
	echo "error:modules: modules-dependencies.conf cannot be found"
	echo "error:modules: the repository appears to be currupted."
	echo "error:modules: try clonning the simple repository again to resolve the issue"
fi

#ENVIRONMENT PROGRAMS
	echo "	Copying Environment Programs to $SIMPLE_DEBUG_VERSION folder"
if [ -e ../../$SIMPLE_DEBUG_VERSION/environment ]; then
	echo "environment: the ../../$SIMPLE_DEBUG_VERSION/environment already exist"
else 
	echo "environment: creating the ../../$SIMPLE_DEBUG_VERSION/environment directory"
	mkdir "../../$SIMPLE_DEBUG_VERSION/environment"
fi

#modular
	echo "environment:modular: modular"
if [ -e ../environment/modular/modular.sim ]; then
	echo "environment:modular: copying modular to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../environment/modular/modular.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "error:environment:modular: ../environment/modular/modular.sim cannot be found"
	echo "error:environment:modular: skipping modular"
fi

#repl
	echo "environment:simplerepl: simplerepl"
if [ -e ../environment/repl/simplerepl.sim ]; then
	echo "environment:simplerepl: copying simplerepl.sim to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../environment/repl/simplerepl.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "error:environment:simplerepl: ../environment/repl/simplerepl.sim cannot be found"
	echo "error:environment:simplerepl: skipping simplerepl"
fi

#SimplePad
	echo "environment:simplepad: simplepad"
if [ -e ../environment/simplepad/simplepad.sim ]; then
	echo "environment:simplepad: copying simplepad.sim to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../environment/simplepad/simplepad.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "error:environment:simplepad: ../environment/simplepad/simplepad.sim cannot be found"
	echo "error:environment:simplepad: skipping simplepad"
fi

#bake
	echo "environment:bake: bake"
if [ -e ../environment/bake/bake.sim ]; then
	echo "environment:bake: copying bake.sim to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../environment/bake/bake.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "error:environment:bake: ../environment/bake/bake.sim cannot be found"
	echo "error:environment:bake: skipping bake"
fi

#webworker
	echo "environment:webworker: webworker"
if [ -e ../environment/webworker/webworker.sim ]; then
	echo "environment:webworker: copying webworker.sim to ../../$SIMPLE_DEBUG_VERSION/environment folder"
	cp "../environment/webworker/webworker.sim" "../../$SIMPLE_DEBUG_VERSION/environment"
else
	echo "error:environment:webworker: ../environment/webworker/webworker.sim cannot be found"
	echo "error:environment:webworker: skipping webworker"
fi

#Build the environment app note due to it been debug
#the executable enviroment might not run on a linux machine
#except the SIMPLE_PATH and SIMPLE_MODULE_PATH has been set
	echo "	Building the executable environments"
	echo "build:environment: we first check if the simple and bake.sim has been copied"

echo "build:environment: checking simple"
if [ -e ../../$SIMPLE_DEBUG_VERSION/bin/simple ]; then
	echo "build:environment: simple is present now checking bake"
	cd "../../$SIMPLE_DEBUG_VERSION/bin"
else
	echo error:build:environment: simple cannot be found
	echo error:build:environment: the build process failed bye
	exit 
fi

echo "build:environment: checking bake"
if [ -e ../environment/bake.sim ]; then
	echo "build:environment: bake is present procedding build.."
	cd "../../$SIMPLE_DEBUG_VERSION/bin"
else
	echo error:build:environment: no bake.sim no build
	echo error:build:environment: the build process failed bye
	exit 
fi

#Now since the prequsite are present start build Always make bake the last
#build in this script because it the one building the former(s)
#Build SimpleRepl

echo "	build;environment: simplerepl"
if [ -e ../environment/simplerepl.sim ]; then
	echo "		building bake..."
	./simple ../environment/bake.sim -delete ../environment/simplerepl.sim
	rm ../environment/simplerepl.sim
else
	echo "		simplerepl.sim not present skipping "
fi

#Build modular

echo "	build:environment modular"
if [ -e ../environment/modular.sim ]; then
	echo "		building modular..."
	./simple ../environment/bake.sim -delete ../environment/modular.sim
	rm ../environment/modular.sim
else
	echo "		modular.sim not present skipping "
fi

#Build SimplePad

echo "	build:environment simplepad"
if [ -e ../environment/simplepad.sim ]; then
	echo "		building simplepad..."
	./simple ../environment/bake.sim -delete ../environment/simplepad.sim
	rm ../environment/simplepad.sim
else
	echo "		simplepad.sim not present skipping "
fi

#Build webworker

echo "	build:environment webworker"
if [ -e ../environment/webworker.sim ]; then
	echo "		building webworker..."
	./simple ../environment/bake.sim -delete ../environment/webworker.sim
	rm ../environment/webworker.sim
else
	echo "		webworker.sim not present skipping "
fi

#Build bake

echo "	build:environment: bake"
if [ -e ../environment/bake.sim ]; then
	echo "		building bake..."
	./simple ../environment/bake.sim -delete ../environment/bake.sim
	rm ../environment/bake.sim
else
	echo "		seriously it an hack if bake not present "
fi


#Install Environments
echo "environment:install: preparing to install simple environment programs"
echo "environment:install: moving back to simple/build diectory"
cd ../../simple/build
if [ -e ../environment/Linux-Install.mk ]; then
	echo "environment:install: the Linux.Install.mk is detected "
	echo "environment:install: checking if the environments are built"
	if [ -e ../../$SIMPLE_DEBUG_VERSION/environment/bake ]; then
		echo "environment:install: the environment are detected. proceding installation..."
		make -f ../environment/Linux-Install.mk uninstall
		make -f ../environment/Linux-Install.mk install
	else
		echo "error:environment:install:  the environment program are yet to be built"
		echo "error:environment:install: aborting installation"
	fi
else 
	echo "error:environment:install: the Linux-install.mk file is absent"
	echo "error:environment:install: skipping the environment programs installation"
fi

#Add Simple to path
#to delegate this task to modular program in future
echo "SIMPLE_PATH=\"/simple/\"" >> /etc/environment











