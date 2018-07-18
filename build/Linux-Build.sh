#!/bin/sh

clear

exec_type=""
build_arc="x86"
ver=0.3.35
keep_dist="false"
version=s"$ver"
simple_debug_version=$version-debug
fulltick_build_issue="<https://github.com/simple-lang/simple/issues/16>"
arc_var=-m32
arc=32
operating_system="linux_amd64"

execute_build() {
	check_if_is_sudo $@
	operating_system=$(get_os_platform)
	local standalone_flag="none"

	for param in "$@"
	do
		if [ "$param" = "-h" ] || [ "$param" = "--help" ]; then 
			help
			exit 0
		elif [ "$param" = "-u" ] || [ "$param" = "--uninstall" ]; then 
			uninstall
			exit 0
		elif [ "$param" = "x64" ] || [ "$param" = "--64-bit" ]; then 
			arc_var=-m64
			arc=64
		elif [ "$param" = "x86" ] || [ "$param" = "--32-bit" ]; then 
			arc_var=-m32
			arc=32
		elif [ "$param" = "-c" ] || [ "$param" = "--configure" ]; then 
			exec_type="configure$exec_type"
		elif [ "$param" = "-t" ] || [ "$param" = "--temp" ]; then 
			keep_dist="true"
		elif [ "$param" = "-i" ] || [ "$param" = "--install" ]; then 
			exec_type="install-$exec_type"
		elif [ "$param" = "-d" ] || [ "$param" = "--debug" ]; then 
			exec_type="debug-$exec_type"
		elif [ "$param" = "-so" ] || [ "$param" = "--simple-only" ]; then 
			standalone_flag="simple-only"
		elif [ "$param" = "-io" ] || [ "$param" = "--includes-only" ]; then 
			standalone_flag="includes-only"
		elif [ "$param" = "-yo" ] || [ "$param" = "--dymodules-only" ]; then 
			standalone_flag="dy-modules-only"
		elif [ "$param" = "-mo" ] || [ "$param" = "--modules-only" ]; then 
			standalone_flag="modules-only"
		elif [ "$param" = "-eo" ] || [ "$param" = "--environment-only" ]; then 
			standalone_flag="environment-only"
		fi
	done

	execute_build_proceed $exec_type $standalone_flag
}

execute_build_proceed() {
	case $1 in
		*configure* )
			configure $@
			if [ "$1" = "configure" ]; then
				echo "configure : $1"
				exit 0
			fi
			;;
	esac
	case $2 in
		*none* )
			installsimpleexec $1
			build_dynamic_modules $1
			case $1 in
				*debug* )
					copyinclude $1
					copymodules $1
				;;
			esac
		;;
		*simple-only* )
			installsimpleexec $1
		;;
		*includes-only* )
			copyinclude $1
		;;
		*modules-only* )
			copymodules $1
		;;
		*dy-modules-only* )
			installsimpleexec notanyofit
			build_dynamic_modules $1
		;;
		*enviroment-only* )
			build_environments $1
		;;
	esac
	remove_dist_folders ../simple/dist/ ../modules/dynamic_modules/dist
}



copymodules() {
	header $1 "copying the standard modules"
	case $1 in
		*debug* )
			if [ -e "../../$simple_debug_version/modules/simple" ]; then 
				sudo rm -R -f "../../$simple_debug_version/modules/archive"
				sudo rm -R -f "../../$simple_debug_version/modules/fulltick"
				sudo rm -R -f "../../$simple_debug_version/modules/simple"
				sudo rm -R -f "../../$simple_debug_version/modules/web"
			fi
			sudo mkdir -p "../../$simple_debug_version/modules/archive"
			sudo mkdir -p "../../$simple_debug_version/modules/fulltick"
			sudo mkdir -p "../../$simple_debug_version/modules/simple"
			sudo mkdir -p "../../$simple_debug_version/modules/web"
			if [ -e "../modules/modules-dependencies.conf" ]; then
				sudo cp "../modules/modules-dependencies.conf" "../../$simple_debug_version/modules/"
				sudo cp -R "../modules/archive" "../../$simple_debug_version/modules/"
				sudo cp -R "../modules/fulltick" "../../$simple_debug_version/modules/"
				sudo cp -R "../modules/simple" "../../$simple_debug_version/modules"
				sudo cp -R "../modules/web" "../../$simple_debug_version/modules/"
				treat_first_calls_file $1 "../../$simple_debug_version/modules/simple/core/__first_calls.sim"
			else
				not_found_error $1 "includes directory"
			fi
		;;
		*install* )
			local prefix=${DESTDIR}${PREFIX:-/usr/}
			if [ -e "$prefix/lib/simple/$version/modules/simple" ]; then 
				sudo rm -R -f "$prefix/lib/simple/$version/modules/archive"
				sudo rm -R -f "$prefix/lib/simple/$version/modules/fulltick"
				sudo rm -R -f "$prefix/lib/simple/$version/modules/simple"
				sudo rm -R -f "$prefix/lib/simple/$version/modules/web"
			fi
			sudo mkdir -p "$prefix/lib/simple/$version/modules/archive"
			sudo mkdir -p "$prefix/lib/simple/$version/modules/fulltick"
			sudo mkdir -p "$prefix/lib/simple/$version/modules/simple"
			sudo mkdir -p "$prefix/lib/simple/$version/modules/web"
			if [ -e "../modules/modules-dependencies.conf" ]; then
				sudo cp "../modules/modules-dependencies.conf" "$prefix/lib/simple/$version/modules/"
				sudo cp -R "../modules/archive" "$prefix/lib/simple/$version/modules/"
				sudo cp -R "../modules/fulltick" "$prefix/lib/simple/$version/modules/"
				sudo cp -R "../modules/simple" "$prefix/lib/simple/$version/modules"
				sudo cp -R "../modules/web" "$prefix/lib/simple/$version/modules/"
				treat_first_calls_file $1 "$prefix/lib/simple/$version/modules/simple/core/__first_calls.sim"
			else
				not_found_error $1 "includes directory"
			fi
		;;
	esac
}

treat_first_calls_file() {
	# The __first_calls.sim is important for the simple-lang modules to function
	if [ -e $2 ]; then
		sudo echo "callDynamicModule(\"systemic.so\") callDynamicModule(\"string_savant.so\")" >> $2
	else
		display_error $1 "cannot find the __first_calls.sim file "
	fi
}

build_dynamic_modules(){
	header dynamic_modules "building simple-lang dynamic_modules"
	if [ -e ../modules ]; then
		cd ../modules
		if [ -e ./dynamic_modules/makefiles/Makefile-Linux.mk ]; then
			cd ./dynamic_modules/makefiles/
			if [ -e ../dist/ ]; then
				rm -R ../dist/
			fi
			sudo make -f Makefile-Linux.mk uninstall  ARC_FLAG=$arc_var ARC=$arc
			sudo make -f Makefile-Linux.mk  ARC_FLAG=$arc_var ARC=$arc

			# fulltick(GUI) dynamic_module
				display "dynamic_modules:fulltick:" "checking if fulltick build successfully"
			if [ -e ../dist/fulltick.so ]; then
				display "dynamic_modules:fulltick:" "fulltick dynamic module built successfully"
			else
				echo "error:dynamic_modules:fulltick: fulltick dynamic module build failed"
				echo "error:dynamic_modules:fulltick: fulltick build is sure to fail if you don't have fltk library installed or it is not configured as shared library"
				echo "error:dynamic_modules:fulltick: visit $fulltick_build_issue for build instruction"
				echo "dynamic_modules:fulltick: falling back on available backup build."
				if [ -e ../fulltick/dist/fulltick$arc.so ]; then
					echo "dynamic_modules:fulltick: backup build found but might be outdated"
					echo "dynamic_modules:fulltick: copying fulltick.so to ../dist/ directory"
					cp ../fulltick/dist/fulltick$arc.so ../dist/
					link ../dist/fulltick$arc.so ../dist/fulltick.so
				else
					echo "error:dynamic_modules:fulltick: the backup fulltick dynamic module cannot be found"
					echo "error:dynamic_modules:fulltick: the repository appears to be currupted. "
					echo "error:dynamic_modules:fulltick: try clonning the simple repository again to resolve the issue"
					echo "error:dynamic_modules:fulltick: or visit $fulltick_build_issue to build instruction"
				fi
			fi
			cd ../
		else
			not_found_error "modules" dynamic_modules
		fi
		cd ../../build
	else
		not_found_error "modules" modules

	fi
	case $1 in
		*debug* )
			display $1 "copying dynamic_modules to $simple_debug_version directory"
			if [ -e "../../$simple_debug_version/modules/dynamic_modules" ]; then 
				sudo rm -R -f "../../$simple_debug_version/modules/dynamic_modules"
			fi
			sudo mkdir -p "../../$simple_debug_version"
			sudo mkdir -p "../../$simple_debug_version/modules"
			sudo mkdir -p "../../$simple_debug_version/modules/dynamic_modules"
			if [ -e "../modules/dynamic_modules/dist/" ]; then
				sudo cp ../modules/dynamic_modules/dist/*.so "../../$simple_debug_version/modules/dynamic_modules"
			else
				build_failed_error $1 "simple and simple.so"
			fi
		;;
		*install* )
			cd ../modules//dynamic_modules/makefiles/
			sudo make -f ./Makefile-Linux.mk install ARC_FLAG=$arc_var ARC=$arc
			cd ../../../build 
			local prefix=${DESTDIR}${PREFIX:-/usr/}
			treat_first_calls_file $1 "$prefix/lib/simple/$version/modules/simple/core/__first_calls.sim"
		;;
	esac
}

installsimpleexec() {
	header install "building simple-lang executables"
	if [ -e ../simple/makefiles/Makefile-Linux.mk ]; then 
		cd ../simple/makefiles
		display $1 "building simple-lang $version build..."
		if [ -e "../dist/" ]
			display $1 "uninstalling previous simple object build"
			sudo rm -r ../dist/
		then
			display $1 "uninstalling previous simple object build"
		fi
		sudo make -f Makefile-Linux.mk uninstall ARC_FLAG=$arc_var ARC=$arc
		sudo make -f Makefile-Linux.mk ARC_FLAG=$arc_var ARC=$arc
	else 
		not_found_error $1 Makefile-Linux.mk
	fi
	case $1 in
		*debug* )
			display $1 "copying executable to $simple_debug_version directory"
			if [ -e "../../../$simple_debug_version/bin" ]; then 
				sudo rm -R -f "../../../$simple_debug_version/bin"
			fi
			sudo mkdir "../../../$simple_debug_version"
			sudo mkdir "../../../$simple_debug_version/bin"
			if [ -e "../dist/simple" ]; then
				sudo cp "../dist/simple" "../../../$simple_debug_version/bin"
				sudo cp "../dist/simple.so" "../../../$simple_debug_version/bin"
			else
				build_failed_error $1 "simple and simple.so"
			fi
		;;
		*install* )
			sudo make -f Makefile-Linux.mk install ARC_FLAG=$arc_var ARC=$arc
		;;
	esac
	cd ../../build
}

copyinclude() {
	header $1 "copying the simple includes(h) file "
	case $1 in
		*debug* )
			if [ -e "../../$simple_debug_version/includes" ]; then 
				sudo rm -R -f "../../$simple_debug_version/includes"
			fi
			sudo mkdir "../../$simple_debug_version/includes"
			if [ -e "../simple/includes" ]; then
				sudo cp -R "../simple/includes" "../../$simple_debug_version/"
			else
				not_found_error $1 "includes directory"
			fi
		;;
		*install* )
			local prefix=${DESTDIR}${PREFIX:-/usr/}
			if [ -e "$prefix/include/simple" ]; then 
				sudo rm -R -f "$prefix/include/simple"
			fi
			sudo mkdir "$prefix/include/simple"
			if [ -e "../simple/includes" ]; then
				sudo install ../simple/includes/simple* "$prefix/include/simple"
			else
				not_found_error $1 "includes directory"
			fi
		;;
	esac
}

build_failed_error() {
	display_error $1 "$2 build failed"
	display_error $1 "try building individually"
}

not_found_error() {
	display_error $1 "simple-lang $version build"
	display_error $1 "the file '$2' does not exist in simple directory"
	display_error $1 "skipping the build... on to next command..."
}

uninstall() {
	header uninstall "removing simple $version from the system"
	echo "simple-lang:menu: removing simplepad menu entry"
	sudo rm -f ~/.local/share/applications/simplepad.desktop
	header uninstall "unlinking environment and library"
	unlink ~/Desktop/simplepad
	sudo unlink $DESTDIR/$PREFIX/lib/libsimple.$ver.so
	sudo unlink $DESTDIR/$PREFIX/lib/libsimple.so
	sudo unlink /usr/lib/libsimple.$ver.so
	sudo unlink /usr/lib/libsimple.so
	sudo unlink /usr/local/lib/libsimple.$ver.so
	sudo unlink /usr/local/lib/libsimple.so 
	header uninstall "uninstalling simple-lang core executables"
	cd ../simple/makefiles
	sudo make -f Makefile-Linux.mk uninstall 
	cd ../../build 
	header uninstall "uninstalling simple-lang environments"
	cd ../environment
	sudo make -f Linux-Install.mk uninstall
	cd ../build
	header uninstall "uninstalling simple-lang modules"
	cd ../modules/dynamic_modules/makefiles 
	sudo make -f Makefile-Linux.mk uninstall
	cd ../../../build
	header uninstall "reinstall with 'sudo sh Linux-Build.sh -i'"
	header uninstall "uninstallation complete"
}

configure() {
	header configure "configure build $version"
	sudo apt-get update
	sudo apt-get -y install build-essential
	sudo apt-get -y install gcc-multilib
	sudo apt-get -y install libfltk1.3-dev
	sudo apt-get -y install xorg-dev
	sudo apt-get -y install libx11-dev
	sudo apt-get -y install libxft-dev
	sudo apt-get -y install libssl-dev
	sudo apt-get -y install make
	#sudo apt-get -y install libcurl4-gnutls-dev
	#sudo apt-get -y install libcurl-nss-dev
	sudo apt-get -y install libcurl4-openssl-dev
	sudo apt-get -y install curl
	sudo apt-get -y autoremove
}

check_if_is_sudo() {
	if [ "$(id -u)" -ne 0 ]; then 
		display sudo "it appear you are not running the script as root"
		display sudo "the script is reinitiated as root"
		display sudo "if it fails to re execute the Linux-Build.sh script with sudo"
		display sudo "manualy run the script with 'sudo sh Linux-Build.sh -c -i'"
		sudo sh Linux-Build.sh $@
		exit 0
	fi
}

help() {
	header "build" "help $version"
	echo "Usage: sudo sh Linux-Build.sh [FLAG]"
	echo "[FLAGS] :"
	echo "	-c --configure	configure your system for simple-lang successful build"
	echo "	-i --install	install simple-lang on your system"
	echo "	-u --uninstall	remove simple-lang installation from your system"
	echo "	-d --debug	create a distributable(archivable) version in ../../ source directory"
	echo "	-x --deb	create a .deb package that can be install with 'dpkg -i simple*.deb'"
	echo "	x86 --32-bit	build 32 bit version of simple-lang"
	echo "	x64 --64-bit	build 64 bit version of simple-lang"
	echo "	-t --temp	keep the */dist/ folder(s) in source tree"
	echo "	-h --help	display this help message"
	echo ""
	echo "[STANDALONE BUILD FLAGS] :"
	echo "	-so --simple-only	build only simple and libsimple.so"
	echo "	-io --includes-only	copy only the simple includes files"
	echo "	-mo --modules-only	copy only the standard modules"
	echo "	-yo --dymodules-only	build only the dynamic modules"
	echo "	-eo --environment-only	build only the environment programs"
}

header() {
	echo "=================================================================="
	echo "simple-lang:$1: $2"
	echo "=================================================================="
}

display() {
	echo "simple-lang:$1: $2"
}

display_error() {
	display "$1:error" $2
}

get_os_platform() {
	  # Get OS/CPU info and store in a `myos` and `mycpu` variable.
	  local ucpu=`uname -m`
	  local uos=`uname`
	  local ucpu=`echo $ucpu | tr "[:upper:]" "[:lower:]"`
	  local uos=`echo $uos | tr "[:upper:]" "[:lower:]"`

	  case $uos in
		*linux* )
		  local myos="linux"
		  ;;
		*dragonfly* )
		  local myos="freebsd"
		  ;;
		*freebsd* )
		  local myos="freebsd"
		  ;;
		*openbsd* )
		  local myos="openbsd"
		  ;;
		*netbsd* )
		  local myos="netbsd"
		  ;;
		*darwin* )
		  local myos="macosx"
		  if [ "$HOSTTYPE" = "x86_64" ] ; then
			local ucpu="amd64"
		  fi
		  ;;
		*aix* )
		  local myos="aix"
		  ;;
		*solaris* | *sun* )
		  local myos="solaris"
		  ;;
		*haiku* )
		  local myos="haiku"
		  ;;
		*mingw* )
		  local myos="windows"
		  ;;
		*)
		  display_error "unknown operating system: $uos"
		  ;;
	  esac

	  case $ucpu in
		*i386* | *i486* | *i586* | *i686* | *bepc* | *i86pc* )
		  local mycpu="i386" ;;
		*amd*64* | *x86-64* | *x86_64* )
		  local mycpu="amd64" ;;
		*sparc*|*sun* )
		  local mycpu="sparc"
		  if [ "$(isainfo -b)" = "64" ]; then
			local mycpu="sparc64"
		  fi
		  ;;
		*ppc64* )
		  local mycpu="powerpc64" ;;
		*power*|*ppc* )
		  local mycpu="powerpc" ;;
		*mips* )
		  local mycpu="mips" ;;
		*arm*|*armv6l* )
		  local mycpu="arm" ;;
		*aarch64* )
		  local mycpu="arm64" ;;
		*)
		  display_error "unknown processor: $ucpu"
		  ;;
	  esac

	  echo "$myos"_"$mycpu"
}

remove_dist_folders() {
	if [ "$keep_dist" = "false" ]; then
		for fol in $@
		do
			if [ -e $fol ]; then
				sudo rm -R -f $fol
			fi
		done
	fi
}

execute_build $@

exit 0

#Buld dynamic modules
	echo "	Building Dynamic Modules "





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
	cd ../build
	if [ -e ../environment/Linux-Install.mk ]; then
		cd ../environment/
		echo "environment:install: the Linux.Install.mk is detected "
		echo "environment:install: checking if the environments are built"
		make -f ../environment/Linux-Install.mk
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
	sudo link $DESTDIR/$PREFIX/lib/simple.so /usr/lib/libsimple.so
	sudo link $DESTDIR/$PREFIX/lib/simple.so /usr/lib/libsimple.$VER.so
	sudo link $DESTDIR/$PREFIX/lib/simple.so /usr/local/lib/libsimple.so
	sudo link $DESTDIR/$PREFIX/lib/simple.so /usr/local/lib/libsimple.$VER.so
	echo "simple-lang:link: linking simplepad to user ~/Desktop"
	sudo link $DESTDIR/$PREFIX/bin/simplepad ~/Desktop/simplepad

	echo "============================================================="
	echo "simple-lang:link: add simplepad to the system menu"
	echo "============================================================="
	sudo echo "[Desktop Entry]" >> ~/.local/share/applications/simplepad.desktop
	sudo echo "Version=1.0" >> ~/.local/share/applications/simplepad.desktop
	sudo echo "Type=Application" >> ~/.local/share/applications/simplepad.desktop
	sudo echo "Name=Simple Pad" >> ~/.local/share/applications/simplepad.desktop
	sudo echo "GenericName=Awesome App" >> ~/.local/share/applications/simplepad.desktop
	sudo echo "Icon=/simple/$SIMPLE_VER/resources/simplepad.png" >> ~/.local/share/applications/simplepad.desktop
	if [ -e $DESTDIR/$PREFIX/bin/simplepad ]; then
		sudo echo "Exec=$DESTDIR/$PREFIX/bin/simplepad" >> ~/.local/share/applications/simplepad.desktop
	elif [ -e /usr/local/bin/simplepad ]; then
		sudo echo "Exec=/usr/local/bin/simplepad" >> ~/.local/share/applications/simplepad.desktop
	elif [ -e /usr/bin/simplepad ]; then
		sudo echo "Exec=/usr/bin/simplepad" >> ~/.local/share/applications/simplepad.desktop
	else
		sudo echo "Exec=simplepad" >> ~/.local/share/applications/simplepad.desktop
	fi
	sudo echo "Comment=Simple Pad code simple-lang with ease" >> ~/.local/share/applications/simplepad.desktop
	sudo echo "Categories=Development;IDE;" >> ~/.local/share/applications/simplepad.desktop
	sudo echo "Terminal=false" >> ~/.local/share/applications/simplepad.desktop

	echo "============================================================="
	echo "simple-lang:build: testing installtion > simple"
	echo "============================================================="
	
	simple

fi









