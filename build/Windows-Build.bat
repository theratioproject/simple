echo off
cls

SET VERSION="s0.3.303"
SET SIMPLE_DEBUG_VERSION="s0.3.303-debug"

REM Remove previous build of the current versions
if exist "../../%SIMPLE_DEBUG_VERSION%/" (
	echo a previous simple build %SIMPLE_DEBUG_VERSION% is detected
	echo removing previous build and performing a clean build
	rm -r ../../%SIMPLE_DEBUG_VERSION%/
) 

REM BULDING SIMPLE.EXE and SIMPLE.DLL
if exist "../simple/makefiles/Makefile-Windows.mk" (
	cd "../simple/makefiles"
	echo SIMPLE %SIMPLE_DEBUG_VERSION% build 
	echo simple: building simple.dll and simple.exe
	make -f Makefile-Windows.mk
	cd ../../build
) else (
	echo SIMPLE %SIMPLE_DEBUG_VERSION% build 
	echo error:simple: the file 'Makefile-Windows.mk' does not exist in simple directory
	echo error:simple: skipping simple Build
)

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
	echo copying includes directory for developers
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
	echo Building of fulltick(GUI) modules not currently supported
if exist "../modules/dynamic_modules/fulltick/dist/fulltick.dll" (
	echo fulltick: copying fulltick.dll to ../../%SIMPLE_DEBUG_VERSION%/bin directory
	cp ../modules/dynamic_modules/fulltick/dist/fulltick.dll ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules
) else (
	echo error:fulltick: the fulltick.dll built module cannot be found 
	echo error:fulltick skipping the GUI module build
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
REM move the environment to %SIMPLE_DEBUG_VERSION% directory
	echo Copying Environment Programs to %SIMPLE_DEBUG_VERSION%
	
if exist "../../%SIMPLE_DEBUG_VERSION%/environment" (
	echo environment: the ../../%SIMPLE_DEBUG_VERSION%/environment directory already exist
) else (
	echo environment: creating the ../../%SIMPLE_DEBUG_VERSION%/environment directory
	mkdir "../../%SIMPLE_DEBUG_VERSION%/environment"
)

REM modular	
	echo environment:modular: modular
if exist "../environment/modular/modular.sim" (
	echo environment:modular: copying modular to ../../%SIMPLE_DEBUG_VERSION%/environment directory
	cp ../environment/modular/modular.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo error:environment:modular: ../environment/modular/modular.sim cannot be found
	echo error:environment:modular: skipping modular
)

REM repl
	echo environment:repl: repl
if exist "../environment/repl/simplerepl.sim" (
	echo environment:repl: copying repl to ../../%SIMPLE_DEBUG_VERSION%/environment directory
	cp ../environment/repl/simplerepl.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo error:environment:repl: ../environment/repl/simplerepl.sim cannot be found
	echo error:environment:repl: skipping repl
)

REM simplepad
	echo environment:simplepad: simplepad
if exist "../environment/simplepad/simplepad.sim" (
	echo environment:simplepad: copying simplepad to ../../%SIMPLE_DEBUG_VERSION%/environment directory
	cp ../environment/simplepad/simplepad.sim ../../%SIMPLE_DEBUG_VERSION%/environment
	REM cp ../environment/simplepad/runwindows.bat ../../%SIMPLE_DEBUG_VERSION%/environment
	REM cp ../environment/simplepad/debugwindows.bat ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo error:environment:simplepad: ../environment/simplepad/simplepad.sim cannot be found
	echo error:environment:simplepad: skipping simplepad
)

REM smake 
	echo environment:smake smake
if exist "../environment/smake/smake.sim" (
	echo environment:smake: copying smake to ../../%SIMPLE_DEBUG_VERSION%/environment directory
	cp ../environment/smake/smake.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo error:environment:smake: ../environment/smake/simplepad.sim cannot be found
	echo error:environment:smake: skipping smake
)

REM spider
	echo environment:spider: spider
if exist "../environment/spider/spider.sim" (
	echo environment:spider: copying spider to ../../%SIMPLE_DEBUG_VERSION%/environment directory
	cp ../environment/spider/spider.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo error:environment:spider: ../environment/spider/simplepad.sim cannot be found
	echo error:environment:spider: skipping spider
)

REM build environment programs executable

echo off

	echo Building Environment Program to Executable 
	
SET SMAKE=""
SET SIMPLE=""

REM Confirm simple is present

if exist "../../%SIMPLE_DEBUG_VERSION%/bin/simple.exe" (
	echo build:environment: simple Found. yea now to check for smake...
	SET SIMPLE="../../%SIMPLE_DEBUG_VERSION%/bin/simple.exe"
) else (
	echo error:build:environment: simple cannot be found
	echo error:build:environment: the build process failed bye
	exit 
)
	
REM Confirm smake is present

if exist "../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim" (
	echo build:environment: smake Found. yea Starting Build...
	SET SMAKE="../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim"
) else (
	echo error:build:environment: smake.sim cannot be found
	echo error:build:environment: no smake no build bye
	exit 
)

REM Builing simplepad
	echo build:environment: simplepad
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/simplepad.sim" (
	if exist ../../simple-arts/environment/simplepad.ico (
		echo 		Building simplepad with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simplepad.ico -gui -delete ../../%SIMPLE_DEBUG_VERSION%/environment/simplepad.sim	
	) else (
		echo 		Building simplepad
		%SIMPLE% %SMAKE% -gui -delete ../../%SIMPLE_DEBUG_VERSION%/environment/simplepad.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/simplepad.sim cannot be found
	echo 		skipping simplepad
)

REM Builing REPL
		echo build:environment: simplerepl
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/simplerepl.sim" (
	if exist ../../simple-arts/environment/simplerepl.ico (
		echo 		Building simplerepl with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simpleprepl.ico -delete ../../%SIMPLE_DEBUG_VERSION%/environment/simplerepl.sim	
	) else (
		echo 		Building simplerepl
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/environment/simplerepl.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/simplerepl.sim cannot be found
	echo 		skipping simplerepl
)

REM Building modular
		echo build:environment: modular
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/modular.sim" (
	if exist ../../simple-arts/environment/modular.ico (
		echo 		Building modular with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simpleprepl.ico -delete ../../%SIMPLE_DEBUG_VERSION%/environment/modular.sim	
	) else (
		echo 		Building modular
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/environment/modular.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/modular.sim cannot be found
	echo 		skipping modular
)

REM Building spider
		echo spider
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/spider.sim" (
	if exist ../../simple-arts/environment/spider.ico (
		echo 		Building spider with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simpleprepl.ico -delete ../../%SIMPLE_DEBUG_VERSION%/environment/spider.sim	
	) else (
		echo 		Building spider
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/environment/spider.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/spider.sim cannot be found
	echo 		skipping spider
)

REM Building smake should be the last build or first whatever ok ok last is better
REM Building SMAKE
	echo build:environment: smake
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim" (
	if exist ../../simple-arts/environment/smake.ico (
		echo 		Building smake with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/smake.ico -delete ../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim	
	) else (
		echo 		Building smake
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim cannot be found
	echo 		skipping smake
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



REM exit /b
