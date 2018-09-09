# LANGUAGE INFORMATION
version="0.3.36"
program_name="simple"

# PATHS
makefile="Makefile-Unix.mk"
current_dir=`pwd`
first_call_file="/var/lib/$program_name/s$version/modules/simple/core/__first_calls.sim"

# The following allows the script to be run from anywhere
# Getting the absolute path of where script is running from
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd)"
# Getting the absolute paths of the relative paths to the script directory
simple_executable_makefile_path=$(cd "$script_dir/../simple/makefiles" 2> /dev/null && pwd -P)
dynamic_modules_makefile_path=$(cd "$script_dir/../modules/dynamic_modules/makefiles" 2> /dev/null && pwd -P)


# ENTRY FUNCTIONS
main() {
    clear

	check_if_is_sudo $@

	for param in "$@"
	do
		if [ "$param" = "-h" ] || [ "$param" = "--help" ]; then
			flag="help"
		elif [ "$param" = "-u" ] || [ "$param" = "--uninstall" ]; then
			flag="uninstall"
		elif [ "$param" = "-i" ] || [ "$param" = "--install" ]; then
            flag="install"
		fi
	done

    run_program $flag

    exit 0
}

run_program() {
    case $1 in
		*help* )
			help
		;;
		*uninstall* )
			uninstall
		;;
		*install* )
			install
		;;
	esac
}

# BUILD FUNCTIONS
install() {
    build_executable
    build_dynamic_modules
}

build_dynamic_modules() {
    if [ -d $dynamic_modules_makefile_path ]; then
        header "install" "Installing dynamic modules..."
        cd $dynamic_modules_makefile_path
        make -s -f $makefile install
        make -s -f $makefile clean
        cd $current_dir
		dynamic_modules_init "setup" $first_call_file
        header "success" "Dynamic modules installed"
    else
        not_found_error "build" $dynamic_modules_makefile_path
    fi
}

build_executable() {
    if [ -d $simple_executable_makefile_path ]; then
        header "install" "Installing simple executables and libraries..."
        cd $simple_executable_makefile_path
        make -s -f $makefile install
        make -s -f $makefile clean
        cd $current_dir
        header "success" "Executables and libraries installed"
    else
        not_found_error "build" $simple_executable_makefile_path
    fi
}

# SETUP FUNCTIONS
dynamic_modules_init() {
	# The __first_calls.sim is important for the simple-lang modules to function
	if [ -f $2 ]; then
		echo "callDynamicModule(\"systemic.so\") callDynamicModule(\"string_savant.so\")" >> $2
        header "setup" "Dynamic modules setup completed"
	else
		display_error $1 "cannot find the __first_calls.sim file "
	fi
}

# CLEAN-UP FUNCTIONS
uninstall() {
    if [ -d $dynamic_modules_makefile_path ]; then
        header "uninstall" "Removing installed dynamic modules..."
        cd $dynamic_modules_makefile_path
        make -s -f $makefile uninstall
        cd $current_dir
    else
        not_found_error "build" $dynamic_modules_makefile_path
    fi
    if [ -d $simple_executable_makefile_path ]; then
        header "uninstall" "Removing installed libraries and executables"
        cd $simple_executable_makefile_path
        make -s -f $makefile uninstall
        cd $current_dir
        header "success" "Simple dependencies removed"
    else
        not_found_error "build" $simple_executable_makefile_path
    fi
}

# COPY FUNCTIONS

# ENVIRONMENT INFORMATION FUNCTIONS
check_if_is_sudo() {
	if [ "$(id -u)" -ne 0 ]; then
		display sudo "it appear you are not running the script as root"
		display sudo "the script is reinitiated as root"
		display sudo "if it fails to re execute the Unix-Build.sh script with sudo"
		display sudo "manualy run the script with 'sudo sh Unix-Build.sh -c -i'"
		exit 0
	fi
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

# PRINT FUNCTIONS
help() {
	header "help" "$version"
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

not_found_error() {
	display_error $1 "simple-lang $version build"
	display_error $1 "the file '$2' does not exist in simple directory"
	display_error $1 "skipping the build... on to next command..."
}

display_error() {
	display "$1:error" $2
}

display() {
	echo "simple-lang:$1: $2"
}

main $@

