#!/bin/bash

clear

exec_type=""
build_arc="x86"
ver=0.4.0
keep_dist="false"
version=s"$ver"
simple_debug_version=$version-debug
fulltick_build_issue="<https://github.com/simple-lang/simple/issues/16>"
arc_var=-m64
arc=64
operating_system="linux_x64"
cpu_arc="x64"

execute_build() {
	#check_if_is_sudo $@
	local standalone_flag="none"

	# If no arguments passed we display help and exit
	if [ $# -eq 0 ]; then
		help && exit 0
	fi

	for param in "$@"
	do
		case "$param"  in 
			"-h"|"--help")
				help && exit 0
				;;
			"-u"|"--uninstall")
				uninstall && exit 0
				;;
			"x64"|"--64-bit")
				arc_var=-m64
				arc=64
				;;
			"x86"|"--32-bit")
				arc_var=-m32
				arc=32
				;;
			"-c"|"--configure")
				exec_type="configure$exec_type"
				;;
			"-t"|"--temp")
				keep_dist="true"
				;;
			"-i"|"--install")
				exec_type="install-$exec_type"
				;;
			"-d"|"--debug")
				exec_type="debug-$exec_type"
				;;
			"-x"|"--deb")
				exec_type="deb-package-$exec_type" 
				;;
			"-so"|"--simple-only")
				standalone_flag="simple-only"
				;;
			"-io"|"--includes-only")
				standalone_flag="includes-only"
				;;
			"-yo"|"--dymodules-only")
				standalone_flag="dy-modules-only"
				;;
			"-mo"|"--modules-only")
				standalone_flag="modules-only"
				;;
			"-eo"|"--environment-only")
				standalone_flag="environment-only"
				;;
			*)
			  help && exit 0;;
		esac
	done
	
	cpu_arc=$(get_os_arch_platform)
	operating_system=$(get_os_platform)_$cpu_arc
	simple_debug_version=simple$ver-$operating_system-debug

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
			build_environments $1
			case $1 in
				*install* )
					finalize_installation $1
				;;
			esac
		;;
		*simple-only* )
			installsimpleexec $1
		;;
		*includes-only* )
			copyinclude $1
		;;
		*dy-modules-only* )
			installsimpleexec notanyofit
			build_dynamic_modules $1
		;;
		*modules-only* )
			copymodules $1
		;;
		*environment-only* )
			build_environments $1
		;;
	esac
	case $1 in
		*deb-package* )
			build_deb_package $@
		;;
	esac
	case $1 in
		*debug* )
			sudo chmod -R 777 ../../$simple_debug_version
		;;
	esac
	remove_dist_folders ../simple/dist/ ../modules/dynamic_modules/dist/ ../environment/dist/ ./dist/ ../$simple_debug_version ../../simple$ver-$operating_system 
}

build_environments() {
    header $1 "preparing to install simple-lang environments"
	cd ../build
	build_environment_in_loop $1 bake simplerepl
}

build_environment_in_loop() {	
	
	case $1 in
		*debug* )
			cd "../../$simple_debug_version/bin/"
			shift ;
			local simple_command="../../$simple_debug_version/bin/simple"
			for param in "$@"
	        do
	            echo $param
	            build_single_environment $simple_command ../../simple/environment/bake/bake.sim $cpu_arc ../../simple/environment/$param/$param.sim --simple="../../$simple_debug_version/bin/" --include="\"$PWD/../include/simple.h\""
	        done 
			cd "../../simple/build/"
		;;
		*install* )
		    shift ;
		    local simple_command="simple"
			cd ../environment/
		    for param in "$@"
	        do
	            echo $param
	            build_single_environment simple ./bake/bake.sim $cpu_arc ./$param/$param.sim
	        done 
			
		;;
	esac
}

build_single_environment(){
    sudo $1 $2 $4 $3 --install $5 $6 $7
}

copymodules() {
	header $1 "copying the standard modules"
	case $1 in
		*debug* )
			if [ -e "../../$simple_debug_version/modules/simple" ]; then 
				sudo rm -R -f "../../$simple_debug_version/modules/archive"
				sudo rm -R -f "../../$simple_debug_version/modules/fulltick"
				sudo rm -R -f "../../$simple_debug_version/modules/parser"
				sudo rm -R -f "../../$simple_debug_version/modules/simple"
				sudo rm -R -f "../../$simple_debug_version/modules/web"
			fi
			sudo mkdir -p "../../$simple_debug_version/modules/archive"
			sudo mkdir -p "../../$simple_debug_version/modules/fulltick"
			sudo mkdir -p "../../$simple_debug_version/modules/parser"
			sudo mkdir -p "../../$simple_debug_version/modules/simple"
			sudo mkdir -p "../../$simple_debug_version/modules/web"
			if [ -e "../modules/modules-dependencies.conf" ]; then
				sudo cp "../modules/modules-dependencies.conf" "../../$simple_debug_version/modules/"
				sudo cp -R "../modules/archive" "../../$simple_debug_version/modules/"
				sudo cp -R "../modules/fulltick" "../../$simple_debug_version/modules/"
				sudo cp -R "../modules/parser" "../../$simple_debug_version/modules/"
				sudo cp -R "../modules/simple" "../../$simple_debug_version/modules"
				sudo cp -R "../modules/web" "../../$simple_debug_version/modules/"
				treat_first_calls_file $1 "../../$simple_debug_version/modules/simple/core/__first_calls.sim"
			else
				not_found_error $1 "includes directory"
			fi
		;;
		*install* )
			local prefix="/var"
			if [ -e "$prefix/lib/simple/$version/modules/simple" ]; then 
				sudo rm -R -f "$prefix/lib/simple/$version/modules/archive"
				sudo rm -R -f "$prefix/lib/simple/$version/modules/fulltick"
				sudo rm -R -f "$prefix/lib/simple/$version/modules/parser"
				sudo rm -R -f "$prefix/lib/simple/$version/modules/simple"
				sudo rm -R -f "$prefix/lib/simple/$version/modules/web"
			fi
			sudo mkdir -p "$prefix/lib/simple/$version/modules/archive"
			sudo mkdir -p "$prefix/lib/simple/$version/modules/fulltick"
			sudo mkdir -p "$prefix/lib/simple/$version/modules/parser"
			sudo mkdir -p "$prefix/lib/simple/$version/modules/simple"
			sudo mkdir -p "$prefix/lib/simple/$version/modules/web"
			if [ -e "../modules/modules-dependencies.conf" ]; then
				sudo cp "../modules/modules-dependencies.conf" "$prefix/lib/simple/$version/modules/"
				sudo cp -R "../modules/archive" "$prefix/lib/simple/$version/modules/"
				sudo cp -R "../modules/fulltick" "$prefix/lib/simple/$version/modules/"
				sudo cp -R "../modules/parser" "$prefix/lib/simple/$version/modules/"
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
		echo "callDynamicModule(\"libsystemic.dylib\") callDynamicModule(\"libstring_savant.dylib\")" >> $2
	else
		display_error $1 "cannot find the __first_calls.sim file "
	fi
}

build_dynamic_modules(){
	header dynamic_modules "building simple-lang dynamic_modules"
	if [ -e ../modules ]; then
		cd ../modules
		if [ -e ./dynamic_modules/makefiles/Makefile-Mac.mk ]; then
			cd ./dynamic_modules/makefiles/
			if [ -e ../dist/ ]; then
				rm -R ../dist/
			fi
			sudo make -f Makefile-Mac.mk uninstall  ARC_FLAG=$arc_var ARC=$arc
			sudo make -f Makefile-Mac.mk  ARC_FLAG=$arc_var ARC=$arc
			
			# libfulltick(GUI) dynamic_module
				display "dynamic_modules:libfulltick:" "checking if libfulltick build successfully"
			if [ -e ../dist/libfulltick.dylib ]; then
				display "dynamic_modules:libfulltick:" "libfulltick dynamic module built successfully"
			else
				echo "error:dynamic_modules:libfulltick: libfulltick dynamic module build failed"
				echo "error:dynamic_modules:libfulltick: libfulltick build is sure to fail if you don't have fltk library installed or it is not configured as shared library"
				echo "error:dynamic_modules:libfulltick: visit $fulltick_build_issue for build instruction"
				echo "dynamic_modules:flibulltick: falling back on available backup build."
				if [ -e ../fulltick/dist/libfulltick$arc.dylib ]; then
					echo "dynamic_modules:libfulltick: backup build found but might be outdated"
					echo "dynamic_modules:libfulltick: copying libfulltick.dylib to ../dist/ directory"
					cp ../fulltick/dist/libfulltick$arc.dylib ../dist/
					mv ../dist/libfulltick$arc.dylib ../dist/libfulltick.dylib
				else
					echo "error:dynamic_modules:libfulltick: the backup libfulltick dynamic module cannot be found"
					echo "error:dynamic_modules:libfulltick: the repository appears to be currupted. "
					echo "error:dynamic_modules:libfulltick: try clonning the simple repository again to resolve the issue"
					echo "error:dynamic_modules:libfulltick: or visit $fulltick_build_issue to build instruction"
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
				sudo cp ../modules/dynamic_modules/dist/*.dylib* "../../$simple_debug_version/modules/dynamic_modules"
			else
				build_failed_error $1 "simple and simple.dylib"
			fi
		;;
		*install* )
			cd ../modules//dynamic_modules/makefiles/
			sudo make -f ./Makefile-Mac.mk install ARC_FLAG=$arc_var ARC=$arc
			cd ../../../build 
			local prefix="/var"
			treat_first_calls_file $1 "$prefix/lib/simple/$version/modules/simple/core/__first_calls.sim"
		;;
	esac
}

installsimpleexec() {
	header install-debug "building simple-lang executables"
	if [ -e ../simple/makefiles/Makefile-Mac.mk ]; then 
		cd ../simple/makefiles
		display $1 "building simple-lang $version build..."
		if [ -e "../dist/" ]; then
			display $1 "uninstalling previous simple object build"
			sudo rm -r ../dist/
		fi
		case $1 in
		    *notanyofit* )
		        sudo make -f Makefile-Mac.mk uninstall ARC_FLAG=$arc_var ARC=$arc
		    ;;
		esac
		sudo make -f Makefile-Mac.mk ARC_FLAG=$arc_var ARC=$arc
	else 
		not_found_error $1 Makefile-Mac.mk
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
				sudo cp "../dist/libsimple.dylib" "../../../$simple_debug_version/bin"
				sudo cp "../dist/libsimple.a" "../../../$simple_debug_version/bin"
			else
				build_failed_error $1 "simple and simple.dylib"
			fi
		;;
		*install* )
			sudo make -f Makefile-Mac.mk install ARC_FLAG=$arc_var ARC=$arc
		;;
	esac
	cd ../../build
}

copyinclude() {
	header $1 "copying the simple includes(h) file "
	case $1 in
		*debug* )
			if [ -e "../../$simple_debug_version/include" ]; then 
				sudo rm -R -f "../../$simple_debug_version/include"
			fi
			sudo mkdir "../../$simple_debug_version/include"
			if [ -e "../simple/include" ]; then
				sudo cp -R "../simple/include" "../../$simple_debug_version/"
			else
				not_found_error $1 "includes directory"
			fi
		;;
		*install* )
			local prefix=${DESTDIR}${PREFIX:-/usr/local/}
			if [ -e "$prefix/include/simple" ]; then 
				sudo rm -R -f "$prefix/include/simple"
			fi
			sudo mkdir "$prefix/include/simple"
			if [ -e "../simple/include" ]; then
				sudo install ../simple/include/simple* "$prefix/include/simple"
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
	local prefix=${DESTDIR}${PREFIX:-/usr/local/}
	header uninstall "removing simple $version from the system"
	echo "simple-lang:menu: removing simplerepl menu entry"
	sudo rm -f ~/.local/share/applications/simplerepl.desktop
	header uninstall "unlinking environment and library"
	unlink ~/Desktop/simplerepl
	sudo unlink $prefix/lib/libsimple.$ver.dylib
	sudo unlink $prefix/lib/libsimple.dylib
	sudo unlink /lib/libsimple.$ver.dylib
	sudo unlink /lib/libsimple.dylib
	sudo unlink /lib/libsimple.a
	sudo unlink /usr/local/lib/libsimple.$ver.dylib
	sudo unlink /usr/local/lib/libsimple.dylib 
	header uninstall "uninstalling simple-lang core executables"
	cd ../simple/makefiles
	sudo make -f Makefile-Mac.mk uninstall 
	cd ../../build 
	header uninstall "uninstalling simple-lang environments"
	cd ../environment
	sudo unlink $prefix/bin/bake
	sudo unlink $prefix/bin/simplerepl
	cd ../build
	header uninstall "uninstalling simple-lang modules"
	cd ../modules/dynamic_modules/makefiles 
	sudo make -f Makefile-Mac.mk uninstall
	cd ../../../build
	header uninstall "reinstall with 'sudo sh Mac-Build.sh -i'"
	header uninstall "uninstallation complete"
}

configure() {
	header configure "configure build $version"
	#MACOSX I believe comes with C/C++ tool chains
	sudo brew install fltk
	sudo brew install curl
	sudo brew install openssl
	case $cpu_arc in
			*64* )
				#sudo brew install libfltk1.3-dev:i386
			;;
	esac
}

check_if_is_sudo() {
	if [ "$(id -u)" -ne 0 ]; then 
		display sudo "it appear you are not running the script as root"
		display sudo "the script is reinitiated as root"
		display sudo "if it fails to re execute the Mac-Build.sh script with sudo"
		display sudo "manualy run the script with 'sudo sh Mac-Build.sh -c -i'"
		sudo sh Mac-Build.sh $@
		exit 0
	fi
}

help() {
	header "build" "help $version"
	echo "Usage: sudo sh Mac-Build.sh [FLAG]"
	echo "[FLAGS] :"
	echo "	-c --configure	configure your system for simple-lang successful build"
	echo "	-i --install	install simple-lang on your system"
	echo "	-u --uninstall	remove simple-lang installation from your system"
	echo "	-d --debug	create a distributable(archivable) version in ../../ source directory"
	echo "	x86 --32-bit	build 32 bit version of simple-lang"
	echo "	x64 --64-bit	build 64 bit version of simple-lang"
	echo "	-t --temp	keep the */dist/ folder(s) in source tree"
	echo "	-h --help	display this help message"
	echo ""
	echo "[STANDALONE BUILD FLAGS] :"
	echo "	-so --simple-only	build only simple and libsimple.dylib"
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

	echo "$myos"
}

get_os_arch_platform() {
	# Get OS/CPU info and store in a `myos` and `mycpu` variable.
	if [ $arc_var = "-m32" ]; then
		local mycpu="i386" 
	elif [ $arc_var = "-m64" ]; then
		local mycpu="amd64"
	else 
		local mycpu="i386"
	fi  
	
	echo "$mycpu"
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

finalize_installation() {
	local prefix=${DESTDIR}${PREFIX:-/usr/local/}
	header link "linking environment and library"
	echo "simple-lang:link: linking simple.dylib to libsimple.dylib and libsimple.$ver.dylib"
	sudo link $prefix/lib/simple.dylib /lib/libsimple.dylib
	sudo link $prefix/lib/simple.dylib /lib/libsimple.$ver.dylib
	sudo link $prefix/lib/simple.dylib $prefix/lib/libsimple.dylib
	sudo link $prefix/lib/simple.dylib $prefix/lib/libsimple.$ver.dylib
	sudo link $prefix/lib/simple.dylib $prefix/local/lib/libsimple.dylib
	sudo link $prefix/lib/simple.dylib $prefix/local/lib/libsimple.$ver.dylib
	display link "linking simplerepl to user ~/Desktop"
	sudo link $prefix/bin/simplerepl ~/Desktop/simplerepl

	header link "add simplerepl to the system menu"
	sudo echo "[Desktop Entry]" >> ~/.local/share/applications/simplerepl.desktop
	sudo echo "Version=1.0" >> ~/.local/share/applications/simplerepl.desktop
	sudo echo "Type=Application" >> ~/.local/share/applications/simplerepl.desktop
	sudo echo "Name=Simple Pad" >> ~/.local/share/applications/simplerepl.desktop
	sudo echo "GenericName=Awesome App" >> ~/.local/share/applications/simplerepl.desktop
	sudo echo "Icon=/var/lib/simple/$version/resources/simplerepl.png" >> ~/.local/share/applications/simplerepl.desktop
	if [ -e $prefix/bin/simplerepl ]; then
		sudo echo "Exec=$prefix/bin/simplerepl" >> ~/.local/share/applications/simplerepl.desktop
	elif [ -e /usr/local/bin/simplerepl ]; then
		sudo echo "Exec=/usr/local/bin/simplerepl" >> ~/.local/share/applications/simplerepl.desktop
	elif [ -e /bin/simplerepl ]; then
		sudo echo "Exec=/bin/simplerepl" >> ~/.local/share/applications/simplerepl.desktop
	else
		sudo echo "Exec=simplerepl" >> ~/.local/share/applications/simplerepl.desktop
	fi
	sudo echo "Comment=Simple Pad code simple-lang with ease" >> ~/.local/share/applications/simplerepl.desktop
	sudo echo "Categories=Development;IDE;" >> ~/.local/share/applications/simplerepl.desktop
	sudo echo "Terminal=false" >> ~/.local/share/applications/simplerepl.desktop

	echo "======================================="

	echo "  Minifying Source code for modules   "
	
	echo "======================================="
	minifier -s /var/lib/simple/s0.4.0/modules -y

	header build "testing installtion > simple" 
	# echo treat_first_calls_file()

	simple
}

build_deb_package() {
	debpackagedir=../../simple$ver-$operating_system
	arc_var="none" #nope
	header debpackage "creating a distributable .deb package"
	if [ -e "$debpackagedir" ]; then
		sudo rm -R -f "$debpackagedir"
	fi
	display debpackage "making directories at $debpackagedir"
	sudo mkdir -p "$debpackagedir"
	sudo mkdir -p "$debpackagedir/usr/"
	sudo mkdir -p "$debpackagedir/usr/bin/"
	sudo mkdir -p "$debpackagedir/usr/lib/"
	sudo mkdir -p "$debpackagedir/usr/lib/"
	sudo mkdir -p "$debpackagedir/usr/include/"
	sudo mkdir -p "$debpackagedir/usr/include/simple/"
	sudo mkdir -p "$debpackagedir/usr/include/simple/$version/"
	sudo mkdir -p "$debpackagedir/var/"
	sudo mkdir -p "$debpackagedir/var/lib/"
	sudo mkdir -p "$debpackagedir/var/lib/simple/"
	sudo mkdir -p "$debpackagedir/var/lib/simple/$version/"
	sudo mkdir -p "$debpackagedir/DEBIAN"

	display debpackage "copying executable, shared libraries and modules"
	case $1 in
		*debug* )
			sudo cp ../../$simple_debug_version/bin/simple $debpackagedir/usr/bin/
			sudo cp ../../$simple_debug_version/bin/simplerepl $debpackagedir/usr/bin/
			sudo cp ../../$simple_debug_version/bin/simplerepl $debpackagedir/usr/bin/
			sudo cp ../../$simple_debug_version/bin/simplebridge $debpackagedir/usr/bin/
			sudo cp ../../$simple_debug_version/bin/modular $debpackagedir/usr/bin/
			sudo cp ../../$simple_debug_version/bin/webworker $debpackagedir/usr/bin/
			sudo cp ../../$simple_debug_version/bin/bake $debpackagedir/usr/bin/
			sudo cp ../../$simple_debug_version/bin/simple.dylib $debpackagedir/usr/lib/
			sudo cp -R ../../$simple_debug_version/modules/ $debpackagedir/var/lib/simple/$version/modules
			sudo cp ../../$simple_debug_version/include/*.h $debpackagedir/usr/include/simple/
			
			if [ $arc_var = "-m32" ]; then
				sudo mkdir -p "$debpackagedir/usr/lib/i386-Mac-gnu/"
				sudo cp ../../$simple_debug_version/bin/simple.dylib $debpackagedir/usr/lib/i386-Mac-gnu/libsimple.dylib.$ver
			elif [ $arc_var = "-m64" ]; then
				sudo mkdir -p "$debpackagedir/usr/lib/x86_64-Mac-gnu/"
				sudo cp ../../$simple_debug_version/bin/simple.dylib $debpackagedir/usr/lib/x86_64-Mac-gnu/libsimple.dylib.$ver
			fi  
			
			local libcrypto=$(find_dependent_lib ../../$simple_debug_version/modules/dynamic_modules/security.dylib libcrypto)
			if [[ "$libcrypto" = *"i386-Mac-gnu"* ]]; then
				sudo mkdir -p "$debpackagedir/usr/lib/i386-Mac-gnu/"
				sudo cp $libcrypto $debpackagedir/usr/lib/i386-Mac-gnu/
			elif [[ "$libcrypto" = *"x86_64-Mac-gnu"* ]]; then
				sudo mkdir -p "$debpackagedir/usr/lib/x86_64-Mac-gnu/"
				sudo cp $libcrypto $debpackagedir/usr/lib/x86_64-Mac-gnu/
			fi
			
		;;
		*install* )
			local prefix=${DESTDIR}${PREFIX:-/usr/local/}
			sudo cp $prefix/bin/simple $debpackagedir/usr/bin/
			sudo cp $prefix/bin/simplerepl $debpackagedir/usr/bin/
			sudo cp $prefix/bin/bake $debpackagedir/usr/bin/
			sudo cp $prefix/lib/simple.dylib $debpackagedir/usr/lib/
			sudo cp $prefix/lib/libsimple.dylib $debpackagedir/usr/lib/
			sudo cp $prefix/lib/libsimple.a $debpackagedir/usr/lib/
			sudo cp -R /var/lib/simple/$version $debpackagedir/var/lib/simple/
			sudo install $prefix/include/simple/simple* $debpackagedir/usr/include/simple/
			
			if [ $arc_var = "-m32" ]; then
				sudo mkdir -p "$debpackagedir/usr/lib/i386-Mac-gnu/"
				#sudo cp $prefix/lib/simple.dylib $debpackagedir/usr/lib/i386-Mac-gnu/libsimple.dylib.$ver
			elif [ $arc_var = "-m64" ]; then
				sudo mkdir -p "$debpackagedir/usr/lib/x86_64-Mac-gnu/"
				#sudo cp $prefix/lib/simple.dylib $debpackagedir/usr/lib/x86_64-Mac-gnu/libsimple.dylib.$ver
			fi  
			
			#no moving with libcrypto
			local libcrypto=$(find_dependent_lib /var/lib/simple/$version/modules/dynamic_modules/security.dylib libcrypto)
			if [[ "$libcrypto" = *"i386-Mac-gnu"* ]]; then
				sudo mkdir "$debpackagedir/usr/lib/i386-Mac-gnu/"
				sudo cp $libcrypto $debpackagedir/usr/lib/i386-Mac-gnu/
			elif [[ "$libcrypto" = *"x86_64-Mac-gnu"* ]]; then
				sudo mkdir "$debpackagedir/usr/lib/x86_64-Mac-gnu/"
				sudo cp $libcrypto $debpackagedir/usr/lib/x86_64-Mac-gnu/
			fi
		;;
	esac

	display debpackage "creating 'control' file"
	sudo echo "Package: simple$ver" >> $debpackagedir/DEBIAN/control
	sudo echo "Version: $ver" >> $debpackagedir/DEBIAN/control
	sudo echo "Essential: no" >> $debpackagedir/DEBIAN/control
	sudo echo "Section: development" >> $debpackagedir/DEBIAN/control
	sudo echo "Priority: optional" >> $debpackagedir/DEBIAN/control
	sudo echo "Architecture: $cpu_arc" >> $debpackagedir/DEBIAN/control
	sudo echo "Depends: " >> $debpackagedir/DEBIAN/control
	sudo echo "License: MIT License" >> $debpackagedir/DEBIAN/control
	sudo echo "Maintainer: Azeez Adewale <azeezadewale98@gmail.com>" >> $debpackagedir/DEBIAN/control
	sudo echo "Installed-Size: 590" >> $debpackagedir/DEBIAN/control
	sudo echo "Description: The Simple Intelligent and Modular Programming Language and Environment" >> $debpackagedir/DEBIAN/control

	display debpackage "creating 'postinst' file"
	echo "#!/bin/sh" >> $debpackagedir/DEBIAN/postinst
	echo "" >> $debpackagedir/DEBIAN/postinst
	echo "sudo chmod -R 777 /var/lib/simple/" >> $debpackagedir/DEBIAN/postinst
	echo "" >> $debpackagedir/DEBIAN/postinst
	echo "mkdir -p ~/" >> $debpackagedir/DEBIAN/postinst
	echo "mkdir -p ~/.local/" >> $debpackagedir/DEBIAN/postinst
	echo "mkdir -p ~/.local/share/" >> $debpackagedir/DEBIAN/postinst
	echo "mkdir -p ~/.local/share/applications/" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"[Desktop Entry]\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Version=0.1\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Type=Application\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Name=Simple Repl\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"GenericName=Awesome App\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Icon=/var/lib/simple/$version/resources/simplerepl.png\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "if [ -e $prefix/bin/simplerepl ]; then" >> $debpackagedir/DEBIAN/postinst
	echo "	sudo echo \"Exec=$prefix/bin/simplerepl\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "elif [ -e /usr/local/bin/simplerepl ]; then" >> $debpackagedir/DEBIAN/postinst
	echo "	sudo echo \"Exec=/usr/local/bin/simplerepl\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "elif [ -e /bin/simplerepl ]; then" >> $debpackagedir/DEBIAN/postinst
	echo "	sudo echo \"Exec=/bin/simplerepl\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "else" >> $debpackagedir/DEBIAN/postinst
	echo "	sudo echo \"Exec=simplerepl\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "fi" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Comment=Simple Pad code simple-lang with ease\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Categories=Development;IDE;\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Terminal=false\" >> ~/.local/share/applications/simplerepl.desktop" >> $debpackagedir/DEBIAN/postinst
	
	sudo chmod 755 $debpackagedir/DEBIAN/postinst
		
	display debpackage "packaging $debpackagedir.deb"
	dpkg-deb --build $debpackagedir

	if [ -e "$debpackagedir.deb" ]; then 
		sudo chmod 777 "$debpackagedir.deb"
		display debpackage "$debpackagedir.deb creation successfull"
	else
		display debpackage "$debpackagedir.deb creation failed"
	fi
}

#find_dependent_lib() {
#	dependinglib="$(ldd $1)"
#	IFS=$'\n' array=($dependinglib) 
#	for element in "${array[@]}"
#	do
#		if [[ "$element" = *"$2"* ]]; then
#			IFS=$' ' read -r -a __deplib <<< "$element"
#			deplib=${__deplib[2]}
#			break
#		fi
#	done
#	echo "$deplib"	
#}

execute_build $@

exit 0

#ma5lata3na1ta34na1la pa4sata1la sa2rava3ca2
#naga wa4rakasa garata shhhh
#

