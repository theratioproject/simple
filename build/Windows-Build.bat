echo off
cls

REM BULDING SIMPLE.EXE and SIMPLE.DLL
if exist "../src/makefiles/Makefile-Windows.mk" (
	cd "../src/makefiles"
	echo `
	echo `
	echo 	SIMPLE s0.3.302-debug build 
	echo		Building simple.dll and simple.exe
	make -f Makefile-Windows.mk
	cd ../../build
) else (
	echo `
	echo `
	echo 	SIMPLE s0.3.302-debug build 
	echo 		The file 'Makefile-Windows.mk' does not exist in src folder
	echo 		Skipping simple Build
)

REM simple.exe and simple.dll has been successful create and copy executable to s0.3.302-debug folder
	echo `
	echo 	Copying Executable and building s0.3.302-debug


if exist "../../s0.3.302-debug/bin/" (
	echo 		the ../../s0.3.302-debug/bin/ folder already exist
) else (
	echo 		Creating the ../../s0.3.302-debug/bin/ folder
	mkdir "../../s0.3.302-debug/bin/"
)

if exist "../src/dist/simple.exe" (
	echo 		Copying simple.exe and simple.dll to ../../s0.3.302-debug/bin folder
	cp ../src/dist/simple.exe ../../s0.3.302-debug/bin
	cp ../src/dist/simple.dll ../../s0.3.302-debug/bin
) else (
	echo 		Build fails simple.exe and simple.dll cannot be found
	echo 		in the ../src/dist/ folder try rebuilding again if it
	echo 		fails again run the build individually
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

REM the dynamic libraries has been successful generated now copy them to s0.3.302-debug folder
	echo `
	echo 	Copying Dynamic Modules to s0.3.302-debug

if exist "../../s0.3.302-debug/modules/dynamic_modules" (
	echo 		the ../../s0.3.302-debug/modules/dynamic_modules folder already exist
) else (
	echo 		Creating the ../../s0.3.302-debug/modules/dynamic_modules folder
	mkdir "../../s0.3.302-debug/modules/dynamic_modules"
)

if exist "../../modules/dynamic_modules/dist/systemic.dll" (
	echo 		Copying dynamic modules to ../../s0.3.302-debug/modules/dynamic_modules folder
	cp ../../modules/dynamic_modules/dist/*.dll ../../s0.3.302-debug/modules/dynamic_modules
) else (
	echo 		Build fails the dynamic modules cannot be found
	echo 		in the ../../modules/dynamic_modules/dist folder try 
	echo 		rebuilding if it fails again build individually 
)

REM resolve dependencies
	echo `
	echo 	Resolving SIMPLE dependencies
	
REM ssleay32.dll
	echo 		`ssleay32.dll
if exist "../../modules/dynamic_modules/security/bin/ssleay32.dll" (
	echo 		Copying ssleay32.dll to ../../s0.3.302-debug/bin folder
	cp ../../modules/dynamic_modules/security/bin/ssleay32.dll ../../s0.3.302-debug/bin
) else (
	echo 		The dependency ssleay32.dll cannot be found you can copy it 
	echo 		in to the ../../s0.3.302-debug/bin folder manually if it is 
	echo 		not included in your cloned repository. Download it from reliable source
)

REM libeay32.dll
	echo 		`libeay32.dll
if exist "../../modules/dynamic_modules/security/bin/libeay32.dll" (
	echo 		Copying libeay32.dll to ../../s0.3.302-debug/bin folder
	cp ../../modules/dynamic_modules/security/bin/libeay32.dll ../../s0.3.302-debug/bin
) else (
	echo 		The dependency libeay32.dll cannot be found you can copy it 
	echo 		in to the ../../s0.3.302-debug/bin folder manually if it is 
	echo 		not included in your cloned repository. Download it from reliable source
)

REM libcurl.dll
	echo 		`libcurl.dll
if exist "../../modules/dynamic_modules/networker/lib/libcurl.dll" (
	echo 		Copying libcurl.dll to ../../s0.3.302-debug/bin folder
	cp ../../modules/dynamic_modules/security/lib/libcurl.dll ../../s0.3.302-debug/bin
) else (
	echo 		The dependency libcurl.dll cannot be found you can copy it 
	echo 		in to the ../../s0.3.302-debug/bin folder manually if it is 
	echo 		not included in your cloned repository. Download it from reliable source
)

REM Copy the simple modules
	echo `
	echo 	Copying Simple Modules to s0.3.302-debug

REM simple core module	
	echo 		`simple core module
if exist "../../modules/simple" (
	echo 		Copying simple module to ../../s0.3.302-debug/modules folder
	xcopy "../../modules/simple" "../../s0.3.302-debug/modules/simple/" /s /h /e /k /f /c
) else (
	echo 		simple module cannot be found
	echo 		The repository appears to be currupted. Try clonning
	echo 		the modules repository again to resolve the issue
)

REM archive module	
	echo 		`archive module
if exist "../../modules/archive" (
	echo 		Copying archive module to ../../s0.3.302-debug/modules folder
	xcopy "../../modules/archive" "../../s0.3.302-debug/modules/archive/" /s /h /e /i /k /f /c
) else (
	echo 		archive module cannot be found
	echo 		The repository appears to be currupted. Try clonning
	echo 		the modules repository again to resolve the issue
)

REM web module	
	echo 		`web module
if exist "../../modules/web" (
	echo 		Copying web module to ../../s0.3.302-debug/modules folder
	xcopy "../../modules/web" "../../s0.3.302-debug/modules/web/" /s /h /e /i /k /f /c
) else (
	echo 		web module cannot be found
	echo 		The repository appears to be currupted. Try clonning
	echo 		the modules repository again to resolve the issue
)

REM fulltick(GUI) module	
	echo 		`fulltick(GUI) module
if exist "../../modules/fulltick" (
	echo 		Copying fulltick module to ../../s0.3.302-debug/modules folder
	xcopy "../../modules/fulltick" "../../s0.3.302-debug/modules/fulltick/" /s /h /e /i /k /f /c
) else (
	echo 		fulltick module cannot be found
	echo 		The repository appears to be currupted. Try clonning
	echo 		the modules repository again to resolve the issue
)

REM ENVIRONMENT PROGRAMS
REM move the environment to s0.3.302-debug folder
	echo `
	echo 	Copying Environment Programs to s0.3.302-debug
	
if exist "../../s0.3.302-debug/environment" (
	echo 		the ../../s0.3.302-debug/environment folder already exist
) else (
	echo 		Creating the ../../s0.3.302-debug/environment folder
	mkdir "../../s0.3.302-debug/environment"
)

REM modular	
	echo 		`modular
if exist "../../environment/modular/modular.sim" (
	echo 		Copying modular to ../../s0.3.302-debug/environment folder
	cp ../../environment/modular/modular.sim ../../s0.3.302-debug/environment
) else (
	echo 		../../environment/modular/modular.sim cannot be found
	echo 		skipping modular
)

REM repl
	echo 		`repl
if exist "../../environment/repl/SimpleRepl.sim" (
	echo 		Copying repl to ../../s0.3.302-debug/environment folder
	cp ../../environment/repl/SimpleRepl.sim ../../s0.3.302-debug/environment
) else (
	echo 		../../environment/repl/SimpleRepl.sim cannot be found
	echo 		skipping repl
)

REM simplepad
	echo 		`simplepad
if exist "../../environment/simplepad/SimplePad.sim" (
	echo 		Copying simplepad to ../../s0.3.302-debug/environment folder
	cp ../../environment/simplepad/SimplePad.sim ../../s0.3.302-debug/environment
	cp ../../environment/simplepad/runwindows.bat ../../s0.3.302-debug/environment
	cp ../../environment/simplepad/debugwindows.bat ../../s0.3.302-debug/environment
) else (
	echo 		../../environment/simplepad/SimplePad.sim cannot be found
	echo 		skipping simplepad
)

REM smake (undone)

REM spider
	echo 		`spider
if exist "../../environment/spider/spider.sim" (
	echo 		Copying spider to ../../s0.3.302-debug/environment folder
	cp ../../environment/spider/spider.sim ../../s0.3.302-debug/environment
) else (
	echo 		../../environment/spider/SimplePad.sim cannot be found
	echo 		skipping spider
)

REM not copying example repository if you want it in the debug folder 
REM you can copy it manually

REM CLEANING UP
if exist "./-p" (
	rmdir -f "./-p"
}


exit /b
