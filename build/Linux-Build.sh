#!/bin/sh

#check if the current user and session is a sudoer or root
echo $UID $EUID
if [ "$(id -u)" -ne 0 ]; then 
	echo "simple-lang:root: it appear you are not running the script as root"
	echo "simple-lang:root: the script is reinitiated as root"
	echo "simple-lang;root: if it fails to re execute the Linux-Build.sh script with sudo"
	echo "simple-lang:root: manualy run the script with 'sudo sh Linux-Build.sh --c --i'"
	sudo sh Linux-Build.sh --c --i
  	exit
fi

EXEC_TYPE=""
VER=0.3.34

if [ ! $1 ]; then
	EXEC_TYPE="install"
elif [ $1 = "-i" ] || [ $1 = "--install" ]; then
	EXEC_TYPE="install"
elif [ $1 = "-c" ] || [ $1 = "--configure" ]; then
	EXEC_TYPE="configure"
elif [ $1 = "-u" ] || [ $1 = "--uninstall" ]; then

	#Remove all instance of the simple-lang from the system
	echo "============================================================="
	echo "simple-lang:uninstall: unlinking environment and library"
	echo "============================================================="
	echo "simple-lang:unlink: unlinking simplepad from ~/Desktop"
	unlink ~/Desktop/simplepad
	echo "simple-lang:unlink: unlinking libsimple.so and libsimple.$VER.so from $DESTDIR/$PREFIX/lib/"
	sudo unlink $DESTDIR/$PREFIX/lib/libsimple.$VER.so
	sudo unlink $DESTDIR/$PREFIX/lib/libsimple.so
	echo "============================================================="
	echo "simple-lang:uninstall: uninstalling simple-lang core executables"
	echo "============================================================="
	cd ../simple/makefiles
	sudo make -f Makefile-Linux.mk uninstall 
	cd ../../build 
	echo "============================================================="
	echo "simple-lang:uninstall: uninstalling simple-lang environments "
	echo "============================================================="
	cd ../environment
	sudo make -f Linux-Install.mk uninstall
	cd ../build
	echo "============================================================="
	echo "simple-lang:uninstall: uninstalling simple-lang modules "
	echo "============================================================="
	cd ../modules/dynamic_modules/makefiles 
	sudo make -f Makefile-Linux.mk uninstall
	cd ../../../build
	echo "============================================================="
	echo "simple-lang:uninstall: reinstall with 'sudo sh Linux-Build.sh --i'"
	echo "simple-lang:uninstall: uninstallation complete "
	echo "============================================================="
	exit 0

elif [ $1 = "-d" ] || [ $1 = "--debug" ]; then
	EXEC_TYPE="debug"
elif [ $1 != "--install" -a $1 != "-i" ] && [ $1 != "--uninstall" -a $1 != "-u" ] && [ $1 != "--debug" -a $1 != "-d" ] ; then
	if [ $1 != "-h" ] && [ $1 != "--help" ]; then
		echo "======================================"
		echo "simple-lang:build: invalid flag : $1"
		echo "======================================"
	fi
	echo "Usage: ./sudo sh Linux-Build.sh [FLAG]"
	echo "[FLAGS] :"
	echo "	-i --install	install simple-lang on your system"
	echo "	-u --uninstall	uninstall simple-lang from your system"
	echo "	-d --debug	creat a distributable version in ../../ source directory"
	echo "	-h --help	print this help message"
	exit 1
else 
	EXEC_TYPE=$1
fi

VERSION=s0.3.34
SIMPLE_DEBUG_VERSION=s0.3.34-debug
FULLTICK_BUILD_ISSUE="<https://github.com/simple-lang/simple/issues/16>"

if [ $EXEC_TYPE = "debug" ]; then
	echo "============================================================="
	echo "simple-lang:debug: debug build $SIMPLE_DEBUG_VERSION"
	echo "============================================================="
elif [ $EXEC_TYPE = "install" ]; then
	echo "============================================================="
	echo "simple-lang:install: install simple-lang $SIMPLE_VERSION"
	echo "============================================================="
fi


if [ $EXEC_TYPE = "configure" ]; then
	echo "simple-lang:configure:"
fi

if [ $EXEC_TYPE="debug" ]; then
#Remove previous debug build of current version
	if [ -e ../../$SIMPLE_DEBUG_VERSION/ ]; then
		echo "a previous simple build $SIMPLE_DEBUG_VERSION is detected"
		echo "removing previous build and performing a clean build"
		sudo rm -R ../../$SIMPLE_DEBUG_VERSION/ 
	fi
fi

if [ -e ../simple/makefiles/Makefile-Linux.mk ]; then 
	cd ../simple/makefiles
	echo "simple-lang: simple-lang $SIMPLE_DEBUG_VERSION build" 
	echo "simple-lang: building simple.so and simple"
	if [ -e "../dist/" ]
		echo "simple-lang: removing previous simple build"
		sudo rm -r ../dist/
	then
		echo "simple-lang: removing previous simple build"
	fi
	sudo make -f Makefile-Linux.mk uninstall 
	sudo make -f Makefile-Linux.mk
	if [ $EXEC_TYPE = "install" ]; then
		sudo make -f Makefile-Linux.mk install
	fi 
	cd ../../build
else 
	echo "error:simple-lang: simple-lang $SIMPLE_DEBUG_VERSION build "
	echo "error:simple-lang: the file 'Makefile-Linux.mk' does not exist in simple directory"
	echo "error:simple-lang: skipping simple Build"
fi

#copy simple and simple.so to s0.3.34-debug folder if built for debugging
if [ $EXEC_TYPE = "debug" ]; then
		echo "	Copying simple executable and building $SIMPLE_DEBUG_VERSION "
	
	if [ -e ../../$SIMPLE_DEBUG_VERSION/bin/ ]; then
		echo "simple-lang:bin: the ../../$SIMPLE_DEBUG_VERSION/bin already exist"
	else
		echo "simple-lang:bin: creating the ../../$SIMPLE_DEBUG_VERSION/bin folder"
		mkdir -p "../../$SIMPLE_DEBUG_VERSION/bin"
	fi
	
	if [ -e ../simple/dist/simple ]; then
		echo "simple-lang: copying simple and simple.so to ../../$SIMPLE_DEBUG_VERSION/bin folder"
		cp "../simple/dist/simple" "../../$SIMPLE_DEBUG_VERSION/bin"
		cp "../simple/dist/simple.so" "../../$SIMPLE_DEBUG_VERSION/bin"
	else
		echo "error:simple-lang: build fails simple.exe and simple.dll cannot be found"
		echo "error:simple-lang: try rebuilding individually"
	fi

	#copying the includes folder for developers
		echo "	copying includes directory for developer"
	if [ -e ../simple/includes ]; then
		echo "includes: copying includes to ../../$SIMPLE_DEBUG_VERSION/includes folder"
		cp -R "../simple/includes" "../../$SIMPLE_DEBUG_VERSION/includes"
	else
		echo "error:includes: the includes directory cannot be found"
		echo "error:includes: the repository appears to be currupted. "
		echo "error:includes: try clonning the simple repository again to resolve the issue"
	fi
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
		echo "dynamic_modules: build and installation starting..."
		sudo make -f Makefile-Linux.mk uninstall
		sudo make -f Makefile-Linux.mk

		# fulltick(GUI) dynamic_module
			echo "dynamic_modules:fulltick: checking if fulltick build successfully"
		if [ -e ../dist/fulltick.so ]; then
			echo "dynamic_modules:fulltick: fulltick dynamic module built successfully"
		else
			echo "error:dynamic_modules:fulltick: fulltick dynamic module build failed"
			echo "error:dynamic_modules:fulltick: fulltick build is sure to fail if you don't have fltk library installed or it is not configured as shared library"
			echo "error:dynamic_modules:fulltick: visit $FULLTICK_BUILD_ISSUE for build instruction"
			echo "dynamic_modules:fulltick: falling back on available backup build."
			if [ -e ../fulltick/dist/fulltick.so ]; then
				echo "dynamic_modules:fulltick: backup build found but might be outdated"
				echo "dynamic_modules:fulltick: copying fulltick.so to ../dist/ directory"
				cp ../fulltick/dist/fulltick.so ../dist/
			else
				echo "error:dynamic_modules:fulltick: the backup fulltick dynamic module cannot be found"
				echo "error:dynamic_modules:fulltick: the repository appears to be currupted. "
				echo "error:dynamic_modules:fulltick: try clonning the simple repository again to resolve the issue"
				echo "error:dynamic_modules:fulltick: or visit $FULLTICK_BUILD_ISSUE to build instruction"
			fi
		fi

		if [ $EXEC_TYPE = "install" ]; then
			sudo make -f Makefile-Linux.mk install
		fi
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

# The __first_calls.sim is important for the simple-lang modules to function
echo "modules:simple-lang:core: treating the __first_calls.sim file"
	echo "modules:simple-lang:core: this is a linux system modify to correspond"
if [ $EXEC_TYPE = "install" ]; then
	if [ -e $DESTDIR/$PREFIX/simple/$VERSION/modules/simple/core/__first_calls.sim ]; then
		sudo echo "callDynamicModule(\"systemic.so\") callDynamicModule(\"string_savant.so\")" >> $DESTDIR/$PREFIX/simple/$VERSION/modules/simple/core/__first_calls.sim
	else
		echo "error:modules:simple-lang:core: the location of the __first_calls.sim could not be verified"
		echo "modules:simple-lang:core: using the SIMPLE_PATH environment instead"
		sudo echo "callDynamicModule(\"systemic.so\") callDynamicModule(\"string_savant.so\")" >> $SIMPLE_PATH/$VERSION/modules/simple/core/__first_calls.sim
	fi
fi

if [ $EXEC_TYPE = "debug" ]; then
		
		#moving the modules to the debug folder if current build is for debugging
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
	
		if [ $EXEC_TYPE = "debug" ]; then 
			if [ -e ../../$SIMPLE_DEBUG_VERSION/modules/simple/core/__first_calls.sim ]; then
				echo "callDynamicModule(\"systemic.so\") callDynamicModule(\"string_savant.so\")" >> ../../$SIMPLE_DEBUG_VERSION/modules/simple/core/__first_calls.sim
			fi
		fi
	
	fi
	
	if [ $EXEC_TYPE = "debug" ]; then
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

fi

if [ $EXEC_TYPE = "install" ]; then
	#Install Environments
	echo "environment:install: preparing to install simple environment programs"
	echo "environment:install: moving back to simple/build diectory"
	cd ../../simple/build
	if [ -e ../environment/Linux-Install.mk ]; then
		cd ../environment/
		echo "environment:install: the Linux.Install.mk is detected "
		echo "environment:install: checking if the environments are built"
		sudo make -f ../environment/Linux-Install.mk
		if [ -e ./dist/bake ]; then
			echo "environment:install: the environment are detected. proceding installation..."
			sudo make -f ../environment/Linux-Install.mk uninstall
			sudo make -f ../environment/Linux-Install.mk install
		else
			echo "error:environment:install:  the environment program are yet to be built"
			echo "error:environment:install: aborting installation"
		fi
		cd ../build/
	else 
		echo "error:environment:install: the Linux-install.mk file is absent"
		echo "error:environment:install: skipping the environment programs installation"
	fi
	
	#Add Simple to path
	#to delegate this task to modular program in future
echo "SIMPLE_PATH=\"/simple/\"" >> /etc/environment

	echo "============================================================="
	echo "simple-lang:link: linking environment and library"
	echo "============================================================="
	echo "simple-lang:link: linking simple.so to libsimple.so and libsimple.$VER.so"
	sudo link $DESTDIR/$PREFIX/lib/simple.so $DESTDIR/$PREFIX/lib/libsimple.so
	sudo link $DESTDIR/$PREFIX/lib/simple.so $DESTDIR/$PREFIX/lib/libsimple.$VER.so
	echo "simple-lang:link: linking simplepad to user ~/Desktop"
	sudo link $DESTDIR/$PREFIX/bin/simplepad ~/Desktop/simplepad

	echo "============================================================="
	echo "simple-lang:build: testing installtion > simple"
	echo "============================================================="
	
	simple

fi









