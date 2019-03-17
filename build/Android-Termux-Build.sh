#!/bin/bash

clear

exec_type=""
build_arc="x64"
ver=0.4.0
keep_dist="false"
version=s"$ver"
simple_debug_version=$version-debug
fulltick_build_issue="<https://github.com/simple-lang/simple/issues/16>"
arc_var=-m64
arc=32
operating_system="linux_x64"
cpu_arc="x64"

execute_build() {
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
		elif [ "$param" = "-x" ] || [ "$param" = "--deb" ]; then 
			exec_type="deb-package-$exec_type" 
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
			copyinclude $1
			copymodules $1
			#build_environments $1
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
			chmod -R 777 ~/$simple_debug_version
		;;
	esac
	remove_dist_folders ../simple/dist/ ../modules/dynamic_modules/dist/ ../environment/dist/ ./dist/ ../$simple_debug_version ../../simple$ver-$operating_system 
}

build_environments() {
	header $1 "preparing to install simple-lang environments"
	cd ../build
	if [ -e ../environment/Linux-Install.mk ]; then
		local simple_command="simple"
		case $1 in
			*debug* )
				cd ~/$simple_debug_version/bin/"
				sudo mkdir -p ../lib/
				sudo cp ./libsimple.so ../lib/
				local simple_command="./$simple_command"
				sudo rm -f ./bake && sudo rm -f ./modular && sudo rm -f ./webworker && sudo rm -f ./simplerepl && sudo rm -f ./simplepad && sudo rm -f ./simplebridge
				sudo make -f ../../simple/environment/Linux-Install.mk ARC_FLAG=$arc_var ARC=$arc ENV_DISTDIR=./  SIMPLE_H=../../../$simple_debug_version/include/simple.h SIMPLE=$simple_command SUDO=sudo ENV_PATH=../../simple/environment/ LIB_PATH=../lib/libsimple.so
				cd ~/simple/build/"
			;;
			*install* )
				cd ../environment/
				sudo make -f ./Linux-Install.mk SIMPLE;=$simple_command ARC_FLAG=$arc_var ARC=$arc 
				if [ -e ./dist/bake ]; then
					sudo make -f ./Linux-Install.mk uninstall
					sudo make -f ./Linux-Install.mk install
				else
					display_error $1 "installation of simple-lang environment fail"
				fi
			;;
		esac
	else 
		not_found_error $1 "./environment/Linux-Install.mk"
	fi
}

copymodules() {
	header $1 "copying the standard modules"
	case $1 in
		*debug* )
			if [ -e ~/$simple_debug_version/modules/simple ]; then 
				rm -R -f ~/$simple_debug_version/modules/archive
				rm -R -f ~/$simple_debug_version/modules/fulltick
				rm -R -f ~/$simple_debug_version/modules/parser
				rm -R -f ~/$simple_debug_version/modules/simple
				rm -R -f ~/$simple_debug_version/modules/web
			fi
			mkdir -p ~/$simple_debug_version/modules/archive
			mkdir -p ~/$simple_debug_version/modules/fulltick
			mkdir -p ~/$simple_debug_version/modules/parser
			mkdir -p ~/$simple_debug_version/modules/simple
			mkdir -p ~/$simple_debug_version/modules/web
			if [ -e "../modules/modules-dependencies.conf" ]; then
				cp "../modules/modules-dependencies.conf" ~/$simple_debug_version/modules/
				cp -R "../modules/archive" ~/$simple_debug_version/modules/
				cp -R "../modules/fulltick" ~/$simple_debug_version/modules/
				cp -R "../modules/parser" ~/$simple_debug_version/modules
				cp -R "../modules/simple" ~/$simple_debug_version/modules
				cp -R "../modules/web" ~/$simple_debug_version/modules/
				treat_first_calls_file $1 ~/$simple_debug_version/modules/simple/core/__first_calls.sim
			else
				not_found_error $1 "includes directory"
			fi
		;;
		*install* )
			local prefix=$PREFIX/var/
			if [ -e "$PREFIX/var/lib/simple/$version/modules/simple" ]; then 
				rm -R -f "$PREFIX/var/lib/simple/$version/modules/archive"
				rm -R -f "$PREFIX/var/lib/simple/$version/modules/fulltick"
				rm -R -f "$PREFIX/var/lib/simple/$version/modules/parser"
				rm -R -f "$PREFIX/var/lib/simple/$version/modules/simple"
				rm -R -f "$PREFIX/var/lib/simple/$version/modules/web"
			fi
			mkdir -p "$PREFIX/var/lib/simple/$version/modules/archive"
			mkdir -p "$PREFIX/var/lib/simple/$version/modules/fulltick"
			mkdir -p "$PREFIX/var/lib/simple/$version/modules/parser"
			mkdir -p "$PREFIX/var/lib/simple/$version/modules/simple"
			mkdir -p "$PREFIX/var/lib/simple/$version/modules/web"
			if [ -e "../modules/modules-dependencies.conf" ]; then
				cp "../modules/modules-dependencies.conf" "$PREFIX/var/lib/simple/$version/modules/"
				cp -R "../modules/archive" "$PREFIX/var/lib/simple/$version/modules/"
				cp -R "../modules/fulltick" "$PREFIX/var/lib/simple/$version/modules/"
				cp -R "../modules/parser" "$PREFIX/var/lib/simple/$version/modules/"
				cp -R "../modules/simple" "$PREFIX/var/lib/simple/$version/modules"
				cp -R "../modules/web" "$PREFIX/var/lib/simple/$version/modules/"
				treat_first_calls_file $1 "$PREFIX/var/lib/simple/$version/modules/simple/core/__first_calls.sim"
			else
				not_found_error $1 "includes directory"
			fi
		;;
	esac
}

treat_first_calls_file() {
	# The __first_calls.sim is important for the simple-lang modules to function
	if [ -e $2 ]; then
		echo "callDynamicModule(\"libsystemic.so\") callDynamicModule(\"libstring_savant.so\")" >> $2
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
			make -f Makefile-Linux.mk uninstall  ARC_FLAG=$arc_var ARC=$arc
			#resolve for debug later
			case $1 in
				*debug* )				
					make -f Makefile-Linux.mk termux  "ARC_FLAG=$arc_var' ./libsimple.so -D__TERMUX__'" ARC=$arc
				;;
				*install* )
					make -f Makefile-Linux.mk termux "ARC_FLAG=$arc_var' -lsimple -D__TERMUX__'" ARC=$arc
				;;
			esac
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
					ln ../dist/fulltick$arc.so ../dist/fulltick.so
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
			if [ -e ~/$simple_debug_version/modules/dynamic_modules ]; then 
				rm -R -f ~/$simple_debug_version/modules/dynamic_modules
			fi
			mkdir -p ~/$simple_debug_version
			mkdir -p ~/$simple_debug_version/modules
			mkdir -p ~/$simple_debug_version/modules/dynamic_modules
			if [ -e "../modules/dynamic_modules/dist/" ]; then
				cp ../modules/dynamic_modules/dist/*.so* ~/$simple_debug_version/modules/dynamic_modules
			else
				build_failed_error $1 "simple and libsimple.so"
			fi
		;;
		*install* )
			mkdir -p $PREFIX/var/lib/simple/$version/
			mkdir -p $PREFIX/var/lib/simple/$version/modules
			mkdir -p $PREFIX/var/lib/simple/$version/modules/dynamic_modules
			if [ -e "../modules/dynamic_modules/dist/" ]; then
				cp ../modules/dynamic_modules/dist/*.so* $PREFIX/var/lib/simple/$version/modules/dynamic_modules
			else
				build_failed_error $1 "simple and libsimple.so"
			fi
			local prefix=$PREFIX/var/
			treat_first_calls_file $1 "$PREFIX/var/lib/simple/$version/modules/simple/core/__first_calls.sim"
		;;
	esac
}

installsimpleexec() {
	header install-debug "building simple-lang core"
	if [ -e ../simple/makefiles/Makefile-Linux.mk ]; then 
		cd ../simple/makefiles
		display $1 "building simple-lang $version build.."
		if [ -e "../dist/" ]; then
			display $1 "uninstalling previous simple object build"
			rm -r ../dist/
		fi
		if [[ "$1" != "notanyofit" ]]; then
			make -f Makefile-Android-Termux.mk uninstall ARC_FLAG=$arc_var ARC=$arc
		fi
		make -f Makefile-Android-Termux.mk ARC_FLAG=$arc_var ARC=$arc
	else 
		not_found_error $1 Makefile-Linux.mk
	fi
	
	case $1 in
		*debug* )
			display $1 "copying executable to $simple_debug_version directory"
			if [ -e ~/$simple_debug_version/bin ]; then 
				rm -R -f ~/$simple_debug_version/bin
			fi
			mkdir -p ~/$simple_debug_version
			mkdir -p ~/$simple_debug_version/bin
			if [ -e "../dist/simple" ]; then
				cp "../dist/simple" ~/$simple_debug_version/bin
				cp "../dist/libsimple.so" ~/$simple_debug_version/bin
			else
				build_failed_error $1 "simple and libsimple.so"
			fi
		;;
		*install* )
			make -f Makefile-Android-Termux.mk install ARC_FLAG=$arc_var ARC=$arc
		;;
	esac
	cd ../../build
}

copyinclude() {
	header $1 "copying the simple includes(h) file "
	case $1 in
		*debug* )
			if [ -e ~/$simple_debug_version/includes ]; then 
				rm -R -f ~/$simple_debug_version/includes
			fi
			mkdir ~/$simple_debug_version/includes
			if [ -e "../simple/includes" ]; then
				cp -R "../simple/includes" ~/$simple_debug_version/
			else
				not_found_error $1 "includes directory"
			fi
		;;
		*install* )
			local prefix=${DESTDIR}${PREFIX:-/usr/}
			if [ -e "$prefix/include/simple" ]; then 
				rm -R -f "$prefix/include/simple"
			fi
			mkdir "$prefix/include/simple"
			if [ -e "../simple/includes" ]; then
				install ../simple/include/simple* "$prefix/include/simple"
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
	local prefix=${DESTDIR}${PREFIX:-/usr/}
	header uninstall "removing simple $version from the system"
	header uninstall "uninstalling core executables"
	cd ../simple/makefiles
	make -f Makefile-Android-Termux.mk uninstall 
	cd ../../build 
	header uninstall "uninstalling environments"
	cd ../environment
	make -f Linux-Install.mk uninstall
	cd ../build
	header uninstall "uninstalling modules"
	cd ../modules/dynamic_modules/makefiles 
	make -f Makefile-Linux.mk uninstall-termux
	cd ../../../build
	header uninstall "reinstall with 'bash Android-Termux-Build.sh -i'"
	header uninstall "uninstallation complete"
}

configure() {
	header configure "configure build $version"
	pkg update && pkg upgrade
	pkg install make
	pkg install clang
	pkg install libcurl-dev
	pkg install openssl-dev
	pkg install libsqlite-dev
}

help() {
	header "build" "help $version"
	echo "Usage: bash Android-Termux-Build.sh [FLAG]"
	echo "[FLAGS] :"
	echo "	-c --configure	configure your system"
	echo "	-i --install	install simple-lang"
	echo "	-u --uninstall	remove simple-lang installation"
	echo "	-d --debug	create a distributable version"
	echo "	-x --deb	create a .deb package "
	echo "	x86 --32-bit	build 32 bit version "
	echo "	x64 --64-bit	build 64 bit version "
	echo "	-t --temp	keep the */dist/ folder(s) "
	echo "	-h --help	display this help message"
	echo ""
	echo "[STANDALONE BUILD FLAGS] :"
	echo "	-so --simple-only	build only simple vm"
	echo "	-io --includes-only	copy only includes files"
	echo "	-mo --modules-only	copy only std modules"
	echo "	-yo --dymodules-only	build jst the dy modules"
	echo "	-eo --environment-only	build the environments"
}

header() {
	echo "======================================================"
	echo "simple-lang:$1: $2"
	echo "======================================================"
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
				rm -R -f $fol
			fi
		done
	fi
}

finalize_installation() {
	header build "testing installtion > simple" 
	simple
}

build_deb_package() {
	debpackagedir=../../simple$ver-$operating_system
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
			sudo cp ~/$simple_debug_version/bin/simple $debpackagedir/usr/bin/
			sudo cp ~/$simple_debug_version/bin/simplerepl $debpackagedir/usr/bin/
			sudo cp ~/$simple_debug_version/bin/simplepad $debpackagedir/usr/bin/
			sudo cp ~/$simple_debug_version/bin/simplebridge $debpackagedir/usr/bin/
			sudo cp ~/$simple_debug_version/bin/modular $debpackagedir/usr/bin/
			sudo cp ~/$simple_debug_version/bin/webworker $debpackagedir/usr/bin/
			sudo cp ~/$simple_debug_version/bin/bake $debpackagedir/usr/bin/
			sudo cp ~/$simple_debug_version/bin/libsimple.so $debpackagedir/usr/lib/
			sudo cp -R ~/$simple_debug_version/modules/ $debpackagedir/var/lib/simple/$version/modules
			sudo cp ~/$simple_debug_version/include/*.h $debpackagedir/usr/include/simple/
			
			if [ $arc_var = "-m32" ]; then
				sudo mkdir -p "$debpackagedir/usr/lib/i386-linux-gnu/"
				sudo cp ~/$simple_debug_version/bin/libsimple.so $debpackagedir/usr/lib/i386-linux-gnu/libsimple.so.$ver
			elif [ $arc_var = "-m64" ]; then
				sudo mkdir -p "$debpackagedir/usr/lib/x86_64-linux-gnu/"
				sudo cp ~/$simple_debug_version/bin/libsimple.so $debpackagedir/usr/lib/x86_64-linux-gnu/libsimple.so.$ver
			fi  
			
			local libcrypto=$(find_dependent_lib ~/$simple_debug_version/modules/dynamic_modules/security.so libcrypto)
			if [[ "$libcrypto" = *"i386-linux-gnu"* ]]; then
				sudo mkdir -p "$debpackagedir/usr/lib/i386-linux-gnu/"
				sudo cp $libcrypto $debpackagedir/usr/lib/i386-linux-gnu/
			elif [[ "$libcrypto" = *"x86_64-linux-gnu"* ]]; then
				sudo mkdir -p "$debpackagedir/usr/lib/x86_64-linux-gnu/"
				sudo cp $libcrypto $debpackagedir/usr/lib/x86_64-linux-gnu/
			fi
			
		;;
		*install* )
			local prefix=${DESTDIR}${PREFIX:-/usr/}
			sudo cp $prefix/bin/simple $debpackagedir/usr/bin/
			sudo cp $prefix/bin/simplerepl $debpackagedir/usr/bin/
			sudo cp $prefix/bin/simplepad $debpackagedir/usr/bin/
			sudo cp $prefix/bin/simplebridge $debpackagedir/usr/bin/
			sudo cp $prefix/bin/modular $debpackagedir/usr/bin/
			sudo cp $prefix/bin/webworker $debpackagedir/usr/bin/
			sudo cp $prefix/bin/bake $debpackagedir/usr/bin/
			sudo cp $PREFIX/var/lib/libsimple.so $debpackagedir/usr/lib/
			sudo cp $PREFIX/var/lib/libsimple.so $debpackagedir/usr/lib/
			sudo cp -R $PREFIX/var/lib/simple/$version $debpackagedir/var/lib/simple/
			sudo install $prefix/include/simple/simple* $debpackagedir/usr/include/simple/
			
			if [ $arc_var = "-m32" ]; then
				sudo mkdir -p "$debpackagedir/usr/lib/i386-linux-gnu/"
				sudo cp $PREFIX/var/lib/libsimple.so $debpackagedir/usr/lib/i386-linux-gnu/libsimple.so.$ver
			elif [ $arc_var = "-m64" ]; then
				sudo mkdir -p "$debpackagedir/usr/lib/x86_64-linux-gnu/"
				sudo cp $PREFIX/var/lib/libsimple.so $debpackagedir/usr/lib/x86_64-linux-gnu/libsimple.so.$ver
			fi  
			
			local libcrypto=$(find_dependent_lib $PREFIX/var/lib/simple/$version/modules/dynamic_modules/security.so libcrypto)
			if [[ "$libcrypto" = *"i386-linux-gnu"* ]]; then
				sudo mkdir "$debpackagedir/usr/lib/i386-linux-gnu/"
				sudo cp $libcrypto $debpackagedir/usr/lib/i386-linux-gnu/
			elif [[ "$libcrypto" = *"x86_64-linux-gnu"* ]]; then
				sudo mkdir "$debpackagedir/usr/lib/x86_64-linux-gnu/"
				sudo cp $libcrypto $debpackagedir/usr/lib/x86_64-linux-gnu/
			fi
		;;
	esac

	display debpackage "creating 'control' file"
	sudo echo "Package: simple-lang-s$ver" >> $debpackagedir/DEBIAN/control
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
	echo "sudo chmod -R 777 $PREFIX/var/lib/simple/" >> $debpackagedir/DEBIAN/postinst
	echo "" >> $debpackagedir/DEBIAN/postinst
	echo "mkdir -p ~/" >> $debpackagedir/DEBIAN/postinst
	echo "mkdir -p ~/.local/" >> $debpackagedir/DEBIAN/postinst
	echo "mkdir -p ~/.local/share/" >> $debpackagedir/DEBIAN/postinst
	echo "mkdir -p ~/.local/share/applications/" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"[Desktop Entry]\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Version=1.0\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Type=Application\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Name=Simple Pad\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"GenericName=Awesome App\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Icon=/var/lib/simple/$version/resources/simplepad.png\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "if [ -e $prefix/bin/simplepad ]; then" >> $debpackagedir/DEBIAN/postinst
	echo "	sudo echo \"Exec=$prefix/bin/simplepad\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "elif [ -e /usr/local/bin/simplepad ]; then" >> $debpackagedir/DEBIAN/postinst
	echo "	sudo echo \"Exec=/usr/local/bin/simplepad\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "elif [ -e /bin/simplepad ]; then" >> $debpackagedir/DEBIAN/postinst
	echo "	sudo echo \"Exec=/bin/simplepad\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "else" >> $debpackagedir/DEBIAN/postinst
	echo "	sudo echo \"Exec=simplepad\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "fi" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Comment=Simple Pad code simple-lang with ease\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Categories=Development;IDE;\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	echo "sudo echo \"Terminal=false\" >> ~/.local/share/applications/simplepad.desktop" >> $debpackagedir/DEBIAN/postinst
	
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
#naga wa4rakasa garata
#

