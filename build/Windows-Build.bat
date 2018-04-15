echo off
cls

SET SIMPLE_DEBUG_VERSION="s0.3.302-debug"

REM BULDING SIMPLE.EXE and SIMPLE.DLL
if exist "../src/makefiles/Makefile-Windows.mk" (
	cd "../src/makefiles"
	echo `
	echo `
	echo 	SIMPLE %SIMPLE_DEBUG_VERSION% build 
	echo		Building simple.dll and simple.exe
	make -f Makefile-Windows.mk
	cd ../../build
) else (
	echo `
	echo `
	echo 	SIMPLE %SIMPLE_DEBUG_VERSION% build 
	echo 		The file 'Makefile-Windows.mk' does not exist in src folder
	echo 		Skipping simple Build
)

REM simple.exe and simple.dll has been successful create and copy executable to %SIMPLE_DEBUG_VERSION% folder
	echo `
	echo 	Copying Executable and building %SIMPLE_DEBUG_VERSION%


if exist "../../%SIMPLE_DEBUG_VERSION%/bin/" (
	echo 		the ../../%SIMPLE_DEBUG_VERSION%/bin/ folder already exist
) else (
	echo 		Creating the ../../%SIMPLE_DEBUG_VERSION%/bin/ folder
	mkdir "../../%SIMPLE_DEBUG_VERSION%/bin/"
)

if exist "../src/dist/simple.exe" (
	echo 		Copying simple.exe and simple.dll to ../../%SIMPLE_DEBUG_VERSION%/bin folder
	cp ../src/dist/simple.exe ../../%SIMPLE_DEBUG_VERSION%/bin
	cp ../src/dist/simplew.exe ../../%SIMPLE_DEBUG_VERSION%/bin
	cp ../src/dist/simple.dll ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo 		Build fails simple.exe and simple.dll cannot be found
	echo 		in the ../src/dist/ folder try rebuilding again if it
	echo 		fails again run the build individually
)

REM COPY THE INCLUDE DIRECTORY	
	echo 		`copying includes folder for developers
if exist "../src/includes" (
	echo 		Copying includes to ../../%SIMPLE_DEBUG_VERSION%/ folder
	xcopy "../src/includes" "../../%SIMPLE_DEBUG_VERSION%/includes" /s /h /e /i /k /f /c
) else (
	echo 		The includes folder cannot be found
	echo 		The repository appears to be currupted. Try clonning
	echo 		the simple repository again to resolve the issue
)

REM BULDING DYNAMIC LIBRARIES

	echo `
	echo 	Building Dynamic modules
	
if exist "../../modules" (
	cd "../../modules"
	echo			Modules repository detected
	if exist "./dynamic_modules/makefiles/Makefile-Windows.mk" (
		cd ./dynamic_modules/makefiles
		echo		Starting Build...
		make -f Makefile-Windows.mk
		cd ../../
	) else (
		echo 		dynamic_modules folder does not exist
		echo 		Kindly Clone the modules repository again
	)
	cd ../simple/build
) else (
	echo 		modules repository does not exist
	echo 		Clone the repository in the same folder as simple repository
	echo 		if you want to build them else ignore
	echo 		if ignored only the simple.exe and simple.dll will be built
)

REM the dynamic libraries has been successful generated now copy them to %SIMPLE_DEBUG_VERSION% folder
	echo `
	echo 	Copying Dynamic Modules to %SIMPLE_DEBUG_VERSION%

if exist "../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules" (
	echo 		the ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules folder already exist
) else (
	echo 		Creating the ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules folder
	mkdir "../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules"
)

if exist "../../modules/dynamic_modules/dist/systemic.dll" (
	echo 		Copying dynamic modules to ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules folder
	cp ../../modules/dynamic_modules/dist/*.dll ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules
) else (
	echo 		Build fails the dynamic modules cannot be found
	echo 		in the ../../modules/dynamic_modules/dist folder try 
	echo 		rebuilding if it fails again build individually 
)

REM fulltick(GUI) dynamic module
	echo `
	echo 	Building of fulltick(GUI) modules not currently supported
if exist "../../modules/dynamic_modules/fulltick/dist/fulltick.dll" (
	echo 		Copying fulltick.dll to ../../%SIMPLE_DEBUG_VERSION%/bin folder
	cp ../../modules/dynamic_modules/fulltick/dist/fulltick.dll ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules
) else (
	echo 		The fulltick.dll built module cannot be found 
	echo 		Skipping the GUI module build
)

REM resolve dependencies
	echo `
	echo 	Resolving SIMPLE dependencies
	
REM ssleay32.dll
	echo 		`ssleay32.dll
if exist "../../modules/dynamic_modules/security/bin/ssleay32.dll" (
	echo 		Copying ssleay32.dll to ../../%SIMPLE_DEBUG_VERSION%/bin folder
	cp ../../modules/dynamic_modules/security/bin/ssleay32.dll ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo 		The dependency ssleay32.dll cannot be found you can copy it 
	echo 		in to the ../../%SIMPLE_DEBUG_VERSION%/bin folder manually if it is 
	echo 		not included in your cloned repository. Download it from reliable source
)

REM libeay32.dll
	echo 		`libeay32.dll
if exist "../../modules/dynamic_modules/security/bin/libeay32.dll" (
	echo 		Copying libeay32.dll to ../../%SIMPLE_DEBUG_VERSION%/bin folder
	cp ../../modules/dynamic_modules/security/bin/libeay32.dll ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo 		The dependency libeay32.dll cannot be found you can copy it 
	echo 		in to the ../../%SIMPLE_DEBUG_VERSION%/bin folder manually if it is 
	echo 		not included in your cloned repository. Download it from reliable source
)

REM libcurl.dll
	echo 		`libcurl.dll
if exist "../../modules/dynamic_modules/networker/lib/libcurl.dll" (
	echo 		Copying libcurl.dll to ../../%SIMPLE_DEBUG_VERSION%/bin folder
	cp ../../modules/dynamic_modules/networker/lib/libcurl.dll ../../%SIMPLE_DEBUG_VERSION%/bin
) else (
	echo 		The dependency libcurl.dll cannot be found you can copy it 
	echo 		in to the ../../%SIMPLE_DEBUG_VERSION%/bin folder manually if it is 
	echo 		not included in your cloned repository. Download it from reliable source
)

REM Copy the simple modules
	echo `
	echo 	Copying Simple Modules to %SIMPLE_DEBUG_VERSION%

REM simple core module	
	echo 		`simple core module
if exist "../../modules/simple" (
	echo 		Copying simple module to ../../%SIMPLE_DEBUG_VERSION%/modules folder
	xcopy "../../modules/simple" "../../%SIMPLE_DEBUG_VERSION%/modules/simple/" /s /h /e /k /f /c
) else (
	echo 		simple module cannot be found
	echo 		The repository appears to be currupted. Try clonning
	echo 		the modules repository again to resolve the issue
)

REM archive module	
	echo 		`archive module
if exist "../../modules/archive" (
	echo 		Copying archive module to ../../%SIMPLE_DEBUG_VERSION%/modules folder
	xcopy "../../modules/archive" "../../%SIMPLE_DEBUG_VERSION%/modules/archive/" /s /h /e /i /k /f /c
) else (
	echo 		archive module cannot be found
	echo 		The repository appears to be currupted. Try clonning
	echo 		the modules repository again to resolve the issue
)

REM web module	
	echo 		`web module
if exist "../../modules/web" (
	echo 		Copying web module to ../../%SIMPLE_DEBUG_VERSION%/modules folder
	xcopy "../../modules/web" "../../%SIMPLE_DEBUG_VERSION%/modules/web/" /s /h /e /i /k /f /c
) else (
	echo 		web module cannot be found
	echo 		The repository appears to be currupted. Try clonning
	echo 		the modules repository again to resolve the issue
)

REM fulltick(GUI) module	
	echo 		`fulltick(GUI) module
if exist "../../modules/fulltick" (
	echo 		Copying fulltick module to ../../%SIMPLE_DEBUG_VERSION%/modules folder
	xcopy "../../modules/fulltick" "../../%SIMPLE_DEBUG_VERSION%/modules/fulltick/" /s /h /e /i /k /f /c
) else (
	echo 		fulltick module cannot be found
	echo 		The repository appears to be currupted. Try clonning
	echo 		the modules repository again to resolve the issue
)

REM ENVIRONMENT PROGRAMS
REM move the environment to %SIMPLE_DEBUG_VERSION% folder
	echo `
	echo 	Copying Environment Programs to %SIMPLE_DEBUG_VERSION%
	
if exist "../../%SIMPLE_DEBUG_VERSION%/environment" (
	echo 		the ../../%SIMPLE_DEBUG_VERSION%/environment folder already exist
) else (
	echo 		Creating the ../../%SIMPLE_DEBUG_VERSION%/environment folder
	mkdir "../../%SIMPLE_DEBUG_VERSION%/environment"
)

REM modular	
	echo 		`modular
if exist "../../environment/modular/modular.sim" (
	echo 		Copying modular to ../../%SIMPLE_DEBUG_VERSION%/environment folder
	cp ../../environment/modular/modular.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo 		../../environment/modular/modular.sim cannot be found
	echo 		skipping modular
)

REM repl
	echo 		`repl
if exist "../../environment/repl/SimpleRepl.sim" (
	echo 		Copying repl to ../../%SIMPLE_DEBUG_VERSION%/environment folder
	cp ../../environment/repl/SimpleRepl.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo 		../../environment/repl/SimpleRepl.sim cannot be found
	echo 		skipping repl
)

REM simplepad
	echo 		`simplepad
if exist "../../environment/simplepad/SimplePad.sim" (
	echo 		Copying simplepad to ../../%SIMPLE_DEBUG_VERSION%/environment folder
	cp ../../environment/simplepad/SimplePad.sim ../../%SIMPLE_DEBUG_VERSION%/environment
	REM cp ../../environment/simplepad/runwindows.bat ../../%SIMPLE_DEBUG_VERSION%/environment
	REM cp ../../environment/simplepad/debugwindows.bat ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo 		../../environment/simplepad/SimplePad.sim cannot be found
	echo 		skipping simplepad
)

REM smake 
echo 		`smake
if exist "../../environment/smake/smake.sim" (
	echo 		Copying smake to ../../%SIMPLE_DEBUG_VERSION%/environment folder
	cp ../../environment/smake/smake.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo 		../../environment/smake/SimplePad.sim cannot be found
	echo 		skipping smake
)

REM spider
	echo 		`spider
if exist "../../environment/spider/spider.sim" (
	echo 		Copying spider to ../../%SIMPLE_DEBUG_VERSION%/environment folder
	cp ../../environment/spider/spider.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo 		../../environment/spider/SimplePad.sim cannot be found
	echo 		skipping spider
)

REM build environment programs executable

echo off

	echo `
	echo 	Building Environment Program to Executable 
	
SET SMAKE=""
SET SIMPLE=""

REM Confirm simple is present

if exist "../../%SIMPLE_DEBUG_VERSION%/bin/simple.exe" (
	echo 		simple Found. yea now to check for smake...
	SET SIMPLE="../../%SIMPLE_DEBUG_VERSION%/bin/simple.exe"
) else (
	echo 		simple cannot be found
	echo 		The build process failed bye
	exit 
)
	
REM Confirm smake is present

if exist "../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim" (
	echo 		Smake Found. yea Starting Build...
	SET SMAKE="../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim"
) else (
	echo 		smake.sim cannot be found
	echo 		no smake no build bye
	exit 
)

REM Builing SimplePad
echo 		`SimplePad
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/SimplePad.sim" (
	if exist ../../simple-arts/environment/simplepad.ico (
		echo 		Building SimplePad with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simplepad.ico -gui -delete ../../%SIMPLE_DEBUG_VERSION%/environment/SimplePad.sim	
	) else (
		echo 		Building SimplePad
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/environment/SimplePad.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/SimplePad.sim cannot be found
	echo 		skipping SimplePad
)

REM Builing REPL
echo 		`SimpleRepl
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/SimpleRepl.sim" (
	if exist ../../simple-arts/environment/simplerepl.ico (
		echo 		Building SimpleRepl with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simpleprepl.ico -delete ../../%SIMPLE_DEBUG_VERSION%/environment/SimpleRepl.sim	
	) else (
		echo 		Building SimpleRepl
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/environment/SimpleRepl.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/SimpleRepl.sim cannot be found
	echo 		skipping SimpleRepl
)

REM Building SMAKE
echo 		`SimpleRepl
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim" (
	if exist ../../simple-arts/environment/smake.ico (
		echo 		Building SimpleRepl with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simpleprepl.ico -delete ../../%SIMPLE_DEBUG_VERSION%/environment/SimpleRepl.sim	
	) else (
		echo 		Building SimpleRepl
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/environment/SimpleRepl.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/SimpleRepl.sim cannot be found
	echo 		skipping SimpleRepl
)


REM not copying example repository if you want it in the debug folder 
REM you can copy it manually

REM CLEANING UP
if exist "./-p" (
	rmdir -f "./-p"
}


exit /b
