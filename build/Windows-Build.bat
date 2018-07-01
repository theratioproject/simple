echo off
cls 

setlocal enabledelayedexpansion

SET EXEC_TYPE=""
SET BUILD_ARC="x86"
SET VER="0.3.34"
SET THERE_IS_VS="false"

for %%x in (%*) do (
	if "%%x"=="--configure" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="install-configure"
		) else (
			SET EXEC_TYPE="configure"
		)
	) 
	if "%%x"=="-c" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="install-configure"
		) else (
			SET EXEC_TYPE="configure"
		)
	)
	if "%%x"=="--install" (
		if !EXEC_TYPE!=="configure" (
			SET EXEC_TYPE="install-configure"
		) else (
			SET EXEC_TYPE="install"
		)
	) 
	if "%%x"=="-i" (
		if !EXEC_TYPE!=="configure" (
			SET EXEC_TYPE="install-configure"
		) else (
			SET EXEC_TYPE="install"
		)
	)
	if "%%x"=="--debug" (
		SET EXEC_TYPE="debug"
	) 
	if "%%x"=="-d" (
		SET EXEC_TYPE="debug"
	)
	if "%%x"=="x64" (
		SET BUILD_ARC="x64"
	)
	if "%%x"=="--uninstall" (
		call:uninstall
	) 
	if "%%x"=="-u" (
		call:uninstall
	)
	if "%%x"=="--help" (
		call:help
	) 
	if "%%x"=="-h" (
		call:help
	)
	if "%%x"=="-vs" (
		SET THERE_IS_VS="true"
	)
	if "%%x"=="--visual-studio" (
		SET THERE_IS_VS="true"
	)
)

if !EXEC_TYPE!=="" (
	SET EXEC_TYPE="install"
)

SET VERSION="s0.3.34"
SET SIMPLE_DEBUG_VERSION="s0.3.34-debug"
SET FULLTICK_BUILD_ISSUE="<https://github.com/simple-lang/simple/issues/16>"

if !EXEC_TYPE!=="install" (
	call:configure
	call:installdebug
)
if !EXEC_TYPE!=="debug" (
	call:configure
	call:installdebug
)
if !EXEC_TYPE!=="install-configure" (
	call:configure
	SET EXEC_TYPE="install"
	call:installdebug
)
if !EXEC_TYPE!=="configure" (
	call:configure
)

	:: configure and install for now

REM echo Installation Type : !EXEC_TYPE!
REM echo Architecture : %BUILD_ARC%
exit /b %ERRORLEVEL%

:configure
	echo =============================================================
	echo simple-lang:configure: configure build %VERSION%
	echo =============================================================
	echo simple-lang:configure preparing to find build toolchain...
	echo simple-lang:configure:compiler checking if gcc is present in path
	gcc 2> ..\..\simple_build_configure
	SET /p GCCVAL=<..\..\simple_build_configure
	if "!GCCVAL!"=="gcc: fatal error: no input files" (
		call:deletetempfiles ..\..\simple_build_configure
		echo simple-lang:configure:compiler gcc found
		echo simple-lang:configure:compiler checking if g++ is present in path
		g++ 2> ..\..\simple_build_configure
		SET /p GCCVAL=<..\..\simple_build_configure
		if "!GCCVAL!"=="g++: fatal error: no input files" (
			call:deletetempfiles ..\..\simple_build_configure
			echo simple-lang:configure:compiler g++ found
			echo simple-lang:configure:compiler checking if make is present in path
			make 2> ..\..\simple_build_configure
			SET /p GCCVAL=<..\..\simple_build_configure
			if "!GCCVAL!"=="make: *** No targets specified and no makefile found.  Stop." (
				call:deletetempfiles ..\..\simple_build_configure
				echo simple-lang:configure:compiler make found
				echo simple-lang:configure:compiler proceeding to build...
				exit /b 0
			) else (
				call:compilernotfound make
				call:deletetempfiles ..\..\simple_build_configure
			)
		) else (
			call:compilernotfound g++
			call:deletetempfiles ..\..\simple_build_configure
		)
	) else (
		call:compilernotfound gcc
		call:deletetempfiles ..\..\simple_build_configure
	)
	echo simple-lang:configure serching for mingw and msys
	if exist "C:\MinGW\msys\1.0\bin\" (
		echo simple-lang:configure found MinGW Build Toolchain
		if !EXEC_TYPE!=="configure" (
			call:setcompilerenv C:\MinGW\bin\ C:\MinGW\msys\1.0\bin
		) else (
			SET PATH=!PATH!;C:\MinGW\bin\;C:\MinGW\msys\1.0\bin
		)
	) else (
		echo error:simple-lang:configure MinGW not fund
		echo simple-lang:configure searching for cygwin
		if exist "C:/cygwin/" (
			echo simple-lang:configure found CygWIN Build Toolchain
			if !EXEC_TYPE!=="configure" (
				call:setcompilerenv C:\cygwin\bin\
			) else (
				SET PATH=!PATH!;C:\cygwin\bin\
			) 
		) else (
			echo error:simple-lang:configure CygWIN not found
			echo simple-lang:configure searching for Microsoft Visual Studio
			for /d %%a in ("%programfiles%\Microsoft Visual Studio*") do (
				for /f "tokens=3 delims=\" %%x in ("%%a") do SET THERE_IS_VS="true"  
				SET MVS=%%a\
				break
			)
			if exist !MVS! (
				echo simple-lang:configure !MVS! found
			) else (
				echo error:simple-lang:configure:msvisualstudio Microsoft Visual Studio not found
				echo simple-lang:configure:compiler please enter your C/C++ toolchain folder
				SET /p COMPILER_PATH=Enter your C/C++ Toolchain directory : 
				echo simple-lang:configure:compiler your C/C++ Toolchain Directory ~ !COMPILER_PATH!
				echo simple-lang:configure:compiler checking the presence of toolchain : gcc
				if exist !COMPILER_PATH!/gcc.exe (
					echo simple-lang:configure:compiler gcc : found
					echo simple-lang:configure:compiler checking the presence of toolchain : g++
					if exist "!COMPILER_PATH!/g++.exe" (
						echo simple-lang:configure:compiler g++ : found
						echo simple-lang:configure:compiler checking the presence of toolchain : make
						if exist "!COMPILER_PATH!/make.exe" (
							echo simple-lang:configure:compiler make : found
							if !EXEC_TYPE!=="configure" (
								SET PATH=!PATH!;!COMPILER_PATH!
							) else (
								call:setcompilerenv !COMPILER_PATH! 
							)
						) else (
							echo error:simple-lang:configure make not found
							echo simple-lang:configure enter make.exe folder if different from !COMPILER_PATH!
							SET /p COMPILER_PATH2=Enter your Make.exe directory : 
							if exist "!COMPILER_PATH2!/make.exe" (
								echo simple-lang:configure:compiler make : found
								if !EXEC_TYPE!=="configure" (
									SET PATH="%PATH%;%COMPILER_PATH%;%COMPILER_PATH2%"
								) else (
									call:setcompilerenv !COMPILER_PATH! !COMPILER_PATH2!
								)
							) else (
								call:compilernotfound make
							)
						)
					) else (
						call:compilernotfound g++
					)
				) else (
					call:compilernotfound gcc
				)
			)
		)
	)
	
	exit /b 0
	
:setcompilerenv
	echo simple-lang:configure:compiler adding the directory to PATH for this session
	echo simple-lang:configure:compiler the environment is available for only this session
	echo simple-lang:configure:compiler your PATH variable is never affected in any way
	for %%x in (%*) do (
		SET PATH=!PATH!;%%x
	)
	echo simple-lang:configure:compiler the C/C++ Toolchain directory has been added to PATH
	echo simple-lang:configure:compiler proceeding build...

	exit /b 

:uninstall
	echo unintstalling
	
	exit /b 0

:help
	echo =============================================================
	echo simple-lang:help
	echo =============================================================
	echo Usage: ./sudo Windows-Build.bat [FLAG]
	echo Basic [FLAGS] :
	echo 	-c --configure	configure your system for simple-lang successfull build
	echo 	-i --install	install simple-lang on your system
	echo 	-u --uninstall	uninstall simple-lang from your system
	echo 	-d --debug	create a distributable version in ..\..\ source directory
	echo 	-h --help	print this help message
	echo Build Tool [FLAGS] :
	echo 	-gcc --gnu		build simple with available GNU toolchain
	echo 	-vs --visual-studio	build simple with Microsoft Visual Studio
	
	exit /b 0

:installdebug
	if !EXEC_TYPE!=="install" (
		echo =============================================================
		echo simple-lang:install: install simple-lang %VERSION%
		echo =============================================================
	)
	if !EXEC_TYPE!=="debug" (
		echo =============================================================
		echo simple-lang:install: debug build %SIMPLE_DEBUG_VERSION%
		echo =============================================================
		
		REM Remove previous build of the current versions
		if exist "..\..\%SIMPLE_DEBUG_VERSION%/" (
			echo a previous simple build %SIMPLE_DEBUG_VERSION% is detected
			echo removing previous build and performing a clean build
			rm -r ..\..\%SIMPLE_DEBUG_VERSION%\
		) 
	)
	REM BULDING SIMPLE.EXE and SIMPLE.DLL
	if exist "../simple/makefiles/Makefile-Windows.mk" (
		cd "../simple/makefiles"
		echo simple: simple-lang %SIMPLE_DEBUG_VERSION% build 
		echo simple: building simple.dll and simple.exe
		if exist "../dist/"  (
			echo simple: removing previous simple build
			rm -r ../dist/
		)
		if !THERE_IS_VS!=="true" (
			echo yea Visual Studio
		) else (
			make -f Makefile-Windows.mk
		)
		cd ../../build
	) else (
		echo error:simple: simple-lang %SIMPLE_DEBUG_VERSION% build 
		echo error:simple: the file 'Makefile-Windows.mk' does not exist in simple directory
		echo error:simple: skipping simple Build
	)
	
	echo simple-lang: !THERE_IS_VS!
	exit /b 0

REM simple.exe and simple.dll has been successful create and copy executable to %SIMPLE_DEBUG_VERSION% directory
	echo Copying Executable and building %SIMPLE_DEBUG_VERSION%


if exist "../../%SIMPLE_DEBUG_VERSION%/bin/" (
	echo simple/bin: the ../../%SIMPLE_DEBUG_VERSION%/bin/ directory already exist
) else (
	echo simple/bin: creating the ../../%SIMPLE_DEBUG_VERSION%/bin/ directory
	mkdir "../../%SIMPLE_DEBUG_VERSION%/bin/"
)

if exist "../simple/dist/simple.exe" (
	echo simple: copying simple.exe and simple.dll to ../../%SIMPLE_DEBUG_VERSION%/bin directory
	cp ../simple/dist/simple.exe ../../%SIMPLE_DEBUG_VERSION%/bin
	cp ../simple/dist/simplew.exe ../../%SIMPLE_DEBUG_VERSION%/bin
	cp ../simple/dist/simple.dll ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo error:simple: build fails simple.exe and simple.dll cannot be found
	echo error:simple: try rebuilding individually
)

REM COPY THE INCLUDE DIRECTORY	
	echo copying includes directory for developer
if exist "../simple/includes" (
	echo includes: copying includes to ../../%SIMPLE_DEBUG_VERSION%/ directory
	xcopy "../simple/includes" "../../%SIMPLE_DEBUG_VERSION%/includes" /s /h /e /i /k /f /c
) else (
	echo error:includes: the includes directory cannot be found
	echo error:includes: the repository appears to be currupted. 
	echo error:includes: try clonning the simple repository again to resolve the issue
)

REM resolve dependencies
	echo Resolving SIMPLE dependencies
	
REM ssleay32.dll
	echo dependencies: ssleay32.dll
if exist "../modules/dynamic_modules/security/bin/ssleay32.dll" (
	echo dependencies: copying ssleay32.dll to ../../%SIMPLE_DEBUG_VERSION%/bin directory
	cp ../modules/dynamic_modules/security/bin/ssleay32.dll ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo error:dependencies: the dependency ssleay32.dll cannot be found 
	echo error:dependencies: search for ssleay32.dll and download from reliable source
	echo error:dependencies: manually copy to ../../%SIMPLE_DEBUG_VERSION%/bin directory
)

REM libeay32.dll
	echo dependencies: libeay32.dll
if exist "../modules/dynamic_modules/security/bin/libeay32.dll" (
	echo dependencies: copying libeay32.dll to ../../%SIMPLE_DEBUG_VERSION%/bin directory
	cp ../modules/dynamic_modules/security/bin/libeay32.dll ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo error:dependencies: the dependency libeay32.dll cannot be found 
	echo error:dependencies: search for libeay32.dll and download from reliable source
	echo error:dependencies: manually copy to ../../%SIMPLE_DEBUG_VERSION%/bin directory
)

REM libcurl.dll
	echo dependencies: libcurl.dll
if exist "../modules/dynamic_modules/networker/lib/libcurl.dll" (
	echo dependencies: copying libcurl.dll to ../../%SIMPLE_DEBUG_VERSION%/bin directory
	cp ../modules/dynamic_modules/networker/lib/libcurl.dll ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo error:dependencies: the dependency libcurl.dll cannot be found 
	echo error:dependencies: search for libcurl.dll and download from reliable source
	echo error:dependencies: manually copy to ../../%SIMPLE_DEBUG_VERSION%/bin directory
)

REM BULDING DYNAMIC LIBRARIES

	echo Building Dynamic modules
	
if exist "../modules" (
	cd "../modules"
	echo modules: modules repository detected
	if exist "./dynamic_modules/makefiles/Makefile-Windows.mk" (
		cd ./dynamic_modules/makefiles
		if exist "../dist" (
			echo dynamic_modules: removing previous dynamic modules build
			rm -R ../dist/
		)
		echo dynamic_modules: build starting...
		make -f Makefile-Windows.mk
		cd ../
	) else (
		echo error:dynamic_modules directory does not exist
		echo error:dynamic_modules: the repository appears to be currupted. 
		echo error:dynamic_modules: try clonning the simple repository again to resolve the issue
	)
	cd ../../build
) else (
	echo error:modules: modules directory does not exist
	echo error:modules: the repository appears to be currupted. 
	echo error:modules: try clonning the simple repository again to resolve the issue
)

REM the dynamic libraries has been successful generated now copy them to %SIMPLE_DEBUG_VERSION% directory
	echo dynamic_modules: copying Dynamic Modules to %SIMPLE_DEBUG_VERSION%
if exist "../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules" (
	echo dynamic_modules: the ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules directory already exist
) else (
	echo dynamic_modules: creating the ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules directory
	mkdir "../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules"
) 

if exist "../modules/dynamic_modules/dist/systemic.dll" (
	echo dynamic_modules: copying dynamic modules to ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules directory
	cp ../modules/dynamic_modules/dist/*.dll ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules
) else (
	echo error:dynamic_modules: build fails the dynamic modules cannot be found
	echo error:dynamic_modules:	try building each module individually 
)

REM fulltick(GUI) dynamic module
	echo dynamic_modules:fulltick: checking if fulltick build successfully
if exist "../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules/fulltick.dll" (
	echo dynamic_modules:fulltick: fulltick dynamic module built successfully
) else (
	echo error:dynamic_modules:fulltick: fulltick dynamic module build failed
	echo error:dynamic_modules:fulltick: fulltick build is sure to fail if you don't have fltk library installed or it is not configured as shared library
	echo error:dynamic_modules:fulltick: visit %FULLTICK_BUILD_ISSUE% for build instruction
	echo dynamic_modules:fulltick: falling back on available backup build.
	if exist "../modules/dynamic_modules/fulltick/dist/fulltick.dll" (
		echo dynamic_modules:fulltick: backup build found but might be outdated
		echo fulltick: copying fulltick.dll to ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules directory
		cp ../modules/dynamic_modules/fulltick/dist/fulltick.dll ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules
	) else (
		echo error:dynamic_modules:fulltick: the backup fulltick dynamic module cannot be found
		echo error:dynamic_modules:fulltick: the repository appears to be currupted. 
		echo error:dynamic_modules:fulltick: try clonning the simple repository again to resolve the issue
		echo error:dynamic_modules:fulltick: or visit $FULLTICK_BUILD_ISSUE to build instruction
	)
) 

REM Copy the simple modules
	echo Copying Simple Modules to %SIMPLE_DEBUG_VERSION%

REM simple core module	
	echo modules: simple core module
if exist "../modules/simple" (
	echo modules: copying simple module to ../../%SIMPLE_DEBUG_VERSION%/modules directory
	xcopy "../modules/simple" "../../%SIMPLE_DEBUG_VERSION%/modules/simple/" /s /h /e /k /f /c
) else (
	echo error:modules: the simple core module cannot be found
	echo error:modules: the repository appears to be currupted. 
	echo error:modules: try clonning the simple repository again to resolve the issue
)

REM archive module	
	echo modules: archive module
if exist "../modules/archive" (
	echo modules: copying archive module to ../../%SIMPLE_DEBUG_VERSION%/modules directory
	xcopy "../modules/archive" "../../%SIMPLE_DEBUG_VERSION%/modules/archive/" /s /h /e /i /k /f /c
) else (
	echo error:modules: the archive module cannot be found
	echo error:modules: the repository appears to be currupted. 
	echo error:modules: try clonning the simple repository again to resolve the issue
)

REM web module	
	echo modules: web module
if exist "../modules/web" (
	echo modules: copying web module to ../../%SIMPLE_DEBUG_VERSION%/modules directory
	xcopy "../modules/web" "../../%SIMPLE_DEBUG_VERSION%/modules/web/" /s /h /e /i /k /f /c
) else (
	echo error:modules: the web module module cannot be found
	echo error:modules: the repository appears to be currupted. 
	echo error:modules: try clonning the simple repository again to resolve the issue
)

REM fulltick(GUI) module	
	echo modules: fulltick GUI module
if exist "../modules/fulltick" (
	echo modules: copying fulltick module to ../../%SIMPLE_DEBUG_VERSION%/modules directory
	xcopy "../modules/fulltick" "../../%SIMPLE_DEBUG_VERSION%/modules/fulltick/" /s /h /e /i /k /f /c
) else (
	echo error:modules: the fulltick GUI module cannot be found
	echo error:modules: the repository appears to be currupted. 
	echo error:modules: try clonning the simple repository again to resolve the issue
)

REM The __first_calls.sim File is important for simple-lang modules to function 
	echo modules:simple: treating the __first_calls.sim file 
if exist "../../%SIMPLE_DEBUG_VERSION%/modules/simple/core/__first_calls.sim" (
	echo modules:simple: this is a windows system the corresponding callDynamicModule are filled
	call __echo_first_call.bat %SIMPLE_DEBUG_VERSION% dll
) else (
	echo error:modules:simple: the __first_calls.sim file cannot be found
	echo error:modules:simple: the repository appears to be currupted. 
	echo error:modules:simple: try clonning the simple repository again to resolve the issue
) 

REM modules-dependencies.conf	
	echo modules: modules-dependencies.conf
if exist "../modules/modules-dependencies.conf" (
	echo modules: copying modules-dependencies.conf to ../../%SIMPLE_DEBUG_VERSION%/modules directory
	cp "../modules/modules-dependencies.conf" "../../%SIMPLE_DEBUG_VERSION%/modules/" 
) else (
	echo error:modules: modules-dependencies.conf cannot be found
	echo error:modules: the repository appears to be currupted. 
	echo error:modules: try clonning the simple repository again to resolve the issue
)

REM ENVIRONMENT PROGRAMS
REM The environment programs will also be installed in same bin directory as simple
REM move the environment to %SIMPLE_DEBUG_VERSION% directory
	echo Copying Environment Programs to %SIMPLE_DEBUG_VERSION%
if exist "../../%SIMPLE_DEBUG_VERSION%/bin" (
	echo environment: the ../../%SIMPLE_DEBUG_VERSION%/bin directory already exist
) else (
	echo environment: creating the ../../%SIMPLE_DEBUG_VERSION%/bin directory
	mkdir "../../%SIMPLE_DEBUG_VERSION%/bin"
)

REM modular	
	echo environment:modular: modular
if exist "../environment/modular/modular.sim" (
	echo environment:modular: copying modular to ../../%SIMPLE_DEBUG_VERSION%/bin directory
	cp ../environment/modular/modular.sim ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo error:environment:modular: ../environment/modular/modular.sim cannot be found
	echo error:environment:modular: skipping modular
)

REM repl
	echo environment:simplerepl: simplerepl
if exist "../environment/repl/simplerepl.sim" (
	echo environment:repl: copying simplerepl to ../../%SIMPLE_DEBUG_VERSION%/bin directory
	cp ../environment/repl/simplerepl.sim ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo error:environment:simplerepl: ../environment/repl/simplerepl.sim cannot be found
	echo error:environment:simplerepl: skipping simplerepl
)

REM simplepad
	echo environment:simplepad: simplepad
if exist "../environment/simplepad/simplepad.sim" (
	echo environment:simplepad: copying simplepad to ../../%SIMPLE_DEBUG_VERSION%/bin directory
	cp ../environment/simplepad/simplepad.sim ../../%SIMPLE_DEBUG_VERSION%/bin
	REM cp ../environment/simplepad/runwindows.bat ../../%SIMPLE_DEBUG_VERSION%/environment
	REM cp ../environment/simplepad/debugwindows.bat ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo error:environment:simplepad: ../environment/simplepad/simplepad.sim cannot be found
	echo error:environment:simplepad: skipping simplepad
)

REM bake 
	echo environment:bake bake
if exist "../environment/bake/bake.sim" (
	echo environment:bake: copying bake to ../../%SIMPLE_DEBUG_VERSION%/bin directory
	cp ../environment/bake/bake.sim ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo error:environment:bake: ../environment/bake/bake.sim cannot be found
	echo error:environment:bake: skipping bake
)

REM webworker
	echo environment:webworker: webworker
if exist "../environment/webworker/webworker.sim" (
	echo environment:webworker: copying webworker to ../../%SIMPLE_DEBUG_VERSION%/bin directory
	cp ../environment/webworker/webworker.sim ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo error:environment:webworker: ../environment/webworker/webworker.sim cannot be found
	echo error:environment:webworker: skipping webworker
)

REM build environment programs executable

echo off

	echo Building Environment Program to Executable 
	
SET SMAKE=""
SET SIMPLE=""

REM Confirm simple is present

if exist "../../%SIMPLE_DEBUG_VERSION%/bin/simple.exe" (
	echo build:environment: simple Found. yea now to check for bake...
	SET SIMPLE="../../%SIMPLE_DEBUG_VERSION%/bin/simple.exe"
) else (
	echo error:build:environment: simple cannot be found
	echo error:build:environment: the build process failed bye
	exit /b
)
	
REM Confirm bake is present

if exist "../../%SIMPLE_DEBUG_VERSION%/bin/bake.sim" (
	echo build:environment: bake Found. yea Starting Build...
	SET SMAKE="../../%SIMPLE_DEBUG_VERSION%/bin/bake.sim"
) else (
	echo error:build:environment: bake.sim cannot be found
	echo error:build:environment: no bake no build bye
	exit /b
)

REM Builing simplepad
	echo build:environment: simplepad
if exist "../../%SIMPLE_DEBUG_VERSION%/bin/simplepad.sim" (
	if exist ../../simple-arts/environment/simplepad.ico (
		echo 		Building simplepad with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simplepad.ico -gui -delete ../../%SIMPLE_DEBUG_VERSION%/bin/simplepad.sim	
	) else (
		echo 		Building simplepad
		%SIMPLE% %SMAKE% -gui -delete ../../%SIMPLE_DEBUG_VERSION%/bin/simplepad.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/bin/simplepad.sim cannot be found
	echo 		skipping simplepad
)

REM Builing REPL
		echo build:environment: simplerepl
if exist "../../%SIMPLE_DEBUG_VERSION%/bin/simplerepl.sim" (
	if exist ../../simple-arts/environment/simplerepl.ico (
		echo 		Building simplerepl with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simpleprepl.ico -delete ../../%SIMPLE_DEBUG_VERSION%/bin/simplerepl.sim	
	) else (
		echo 		Building simplerepl
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/bin/simplerepl.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/bin/simplerepl.sim cannot be found
	echo 		skipping simplerepl
)

REM Building modular
		echo build:environment: modular
if exist "../../%SIMPLE_DEBUG_VERSION%/bin/modular.sim" (
	if exist ../../simple-arts/environment/modular.ico (
		echo 		Building modular with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simpleprepl.ico -delete ../../%SIMPLE_DEBUG_VERSION%/bin/modular.sim	
	) else (
		echo 		Building modular
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/bin/modular.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/bin/modular.sim cannot be found
	echo 		skipping modular
)

REM Building webworker
		echo build:environment: webworker
if exist "../../%SIMPLE_DEBUG_VERSION%/bin/webworker.sim" (
	if exist ../../simple-arts/environment/webworker.ico (
		echo 		Building webworker with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simpleprepl.ico -delete ../../%SIMPLE_DEBUG_VERSION%/bin/webworker.sim	
	) else (
		echo 		Building webworker
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/bin/webworker.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/bin/webworker.sim cannot be found
	echo 		skipping webworker
)

REM Building bake should be the last build or first whatever ok ok last is better
REM Building SMAKE
	echo build:environment: bake
if exist "../../%SIMPLE_DEBUG_VERSION%/bin/bake.sim" (
	if exist ../../simple-arts/environment/bake.ico (
		echo 		Building bake with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/bake.ico -delete ../../%SIMPLE_DEBUG_VERSION%/bin/bake.sim	
	) else (
		echo 		Building bake
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/bin/bake.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/bin/bake.sim cannot be found
	echo 		skipping bake
)


REM not copying example repository if you want it in the debug directory 
REM you can copy it manually

REM CLEANING UP
if exist "./-p" (
	rmdir -f "./-p"
}
if exist "../modules/dynamic_modules/dist/" (
	rmdir -f "../modules/dynamic_modules/dist/"
)
if exist "../simple/dist/" (
	rmdir -f "../simple/dist/"
)

exit /b
	
:compilernotfound
	echo error:simple-lang:compiler %1 not found 
	echo error:simple-lang:compiler please confirm your installation folder
	echo error:simple-lang:compiler restart the build process again
	exit /b 0
	
:deletetempfiles
	for %%x in (%*) do (
		del /f %~dp0\%%x
	)
