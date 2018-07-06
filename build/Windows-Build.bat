echo off
cls 

setlocal enabledelayedexpansion

SET EXEC_TYPE=""
SET BUILD_ARC="x86"
SET VER=0.3.35
SET THERE_IS_VS="false"
SET KEEP_DIST="false"
SET INSTALLATION_FOLDER=C:\Simple\
SET VERSION=s0.3.35
SET SIMPLE_DEBUG_VERSION=s0.3.35-debug
SET FULLTICK_BUILD_ISSUE="<https://github.com/simple-lang/simple/issues/16>"
SET BUILD_TOOL="any"

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
	if "%%x"=="--64-bit" (
		SET BUILD_ARC="x64"
	)
	if "%%x"=="x86" (
		SET BUILD_ARC="x86"
	)
	if "%%x"=="--32-bit" (
		SET BUILD_ARC="x86"
	)
	if "%%x"=="--uninstall" (
		call:uninstall
	) 
	if "%%x"=="-u" (
		call:uninstall
	)
	if "%%x"=="--keep" (
		SET KEEP_DIST="true"
	) 
	if "%%x"=="-k" (
		SET KEEP_DIST="true"
	)
	if "%%x"=="--help" (
		call:help
		exit /b 0
	) 
	if "%%x"=="-h" (
		call:help
		exit /b 0
	)
	if "%%x"=="-b" (
		SET /p INSTALLATION_FOLDER=Enter the folder you want to install simple-lang to : 
	)
	if "%%x"=="--install-folder" (
		SET /b INSTALLATION_FOLDER=Enter the folder you want to install simple-lang to : 
	) 
	if "%%x"=="-so" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="simple-only-install"
		) else (
			SET EXEC_TYPE="simple-only-debug"
		)
	)  
	if "%%x"=="--simple-only" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="simple-only-install"
		) else (
			SET EXEC_TYPE="simple-only-debug"
		)
	)  
	if "%%x"=="-do" (
		call:resolvedependencies
		exit /b 0
	)  
	if "%%x"=="--dep-only" (
		call:resolvedependencies
		exit /b 0
	)  
	if "%%x"=="-io" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="includes-only-install"
		) else (
			SET EXEC_TYPE="includes-only-debug"
		)
	)  
	if "%%x"=="--includes-only" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="includes-only-install"
		) else (
			SET EXEC_TYPE="includes-only-debug"
		)
	) 
	if "%%x"=="-yo" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="dymodules-only-install"
		) else (
			SET EXEC_TYPE="dymodules-only-debug"
		)
	)  
	if "%%x"=="--dymodules-only" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="dymodules-only-install"
		) else (
			SET EXEC_TYPE="dymodules-only-debug"
		)
	)
	if "%%x"=="-mo" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="modules-only-install"
		) else (
			SET EXEC_TYPE="modules-only-debug"
		)
	)  
	if "%%x"=="--modules-only" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="modules-only-install"
		) else (
			SET EXEC_TYPE="modules-only-debug"
		)
	)
	if "%%x"=="-eo" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="environment-only-install"
		) else (
			SET EXEC_TYPE="environment-only-debug"
		)
	) 
	if "%%x"=="--environment-only" (
		if !EXEC_TYPE!=="install" (
			SET EXEC_TYPE="environment-only-install"
		) else (
			SET EXEC_TYPE="environment-only-debug"
		)
	) 
	if "%%x"=="-vs" (
		SET THERE_IS_VS="true"
	)
	if "%%x"=="--visual-studio" (
		SET THERE_IS_VS="true"
	)
	if "%%x"=="-gcc" (
		SET  BUILD_TOOL="gcc"
	)
	if "%%x"=="--gnu" (
		SET BUILD_TOOL="gcc"
	)
	if "%%x"=="-mg" (
		SET  BUILD_TOOL="mingw"
	)
	if "%%x"=="--mingw" (
		SET BUILD_TOOL="mingw"
	)
	if "%%x"=="-cy" (
		SET  BUILD_TOOL="cygwin"
	)
	if "%%x"=="--cygwin" (
		SET BUILD_TOOL="cygwin"
	)
)

if !THERE_IS_VS!=="true" (
	call:header configure "configure build %VERSION%"
	call:locatevisualstudio !BUILD_ARC!
)
if !BUILD_TOOL!=="mingw" (
	call:header configure "configure build %VERSION%"
	call:locatemingw !BUILD_ARC!
)
if !BUILD_TOOL!=="cygwin" (
	call:header configure "configure build %VERSION%"
	call:locatecygwin !BUILD_ARC!
)
if !BUILD_TOOL!=="gcc" (
	call:header configure "configure build %VERSION%"
	call:locategcc !BUILD_ARC!
)
if !NO_BUILDTOOL!=="true" (
	echo error:simple-lang:configure: no C/C++ compiler to found 
	echo error:simple-lang:configure: re-build with no C/C++ compiler flag to find available build tool 
	echo error:simple-lang:configure: stopping build...
	exit /b 0
)

if !EXEC_TYPE!=="" (
	SET EXEC_TYPE="install"
)
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

REM STANDALONE BUILDS

if !EXEC_TYPE!=="simple-only-install" (
	SET EXEC_TYPE="install"
	call:header install "install simple-lang %VERSION%"
	call:buildsimpledllexe
	call:copysimpledllexe
	call:removedistfolders
)
if !EXEC_TYPE!=="simple-only-debug" (
	SET EXEC_TYPE="debug"
	call:header debug "debug simple-lang %VERSION%"
	call:buildsimpledllexe
	call:copysimpledllexe
	call:removedistfolders
)
if !EXEC_TYPE!=="includes-only-install" (
	SET EXEC_TYPE="install"
	call:copysimpleincludes
)
if !EXEC_TYPE!=="includes-only-debug" (
	SET EXEC_TYPE="debug"
	call:copysimpleincludes
)
if !EXEC_TYPE!=="modules-only-install" (
	SET EXEC_TYPE="install"
	call:copysimplemodule
)
if !EXEC_TYPE!=="modules-only-debug" (
	SET EXEC_TYPE="debug"
	call:copysimplemodule
)
if !EXEC_TYPE!=="environment-only-install" (
	SET EXEC_TYPE="install"
	call:buildsimplelangenvironments
)
if !EXEC_TYPE!=="environment-only-debug" (
	SET EXEC_TYPE="debug"
	call:buildsimplelangenvironments
)
if !EXEC_TYPE!=="dymodules-only-install" (
	SET EXEC_TYPE="install"
	call:header install "install simple-lang %VERSION%"
	call:buildsimpledllexe
	call:builddynamicmodules
	call:copydynamicmodules
	call:removedistfolders
)
if !EXEC_TYPE!=="dymodules-only-debug" (
	SET EXEC_TYPE="debug"
	call:header install "install simple-lang %VERSION%"
	call:buildsimpledllexe
	call:builddynamicmodules
	call:copydynamicmodules
	call:removedistfolders
)

	:: configure and install for now

exit /b %ERRORLEVEL%

:header
	echo ============================================================================
	echo simple-lang:%1: %2
	echo ============================================================================
	
	exit /b 0

:configure
	call:header configure "configure build %VERSION%"
	echo simple-lang:configure:buildtool determining if a specific tool is specified
	if !BUILD_TOOL!=="any" (
		call:locategcc !BUILD_ARC!
		call:locatemingw !BUILD_ARC!
		call:locatecygwin !BUILD_ARC!
		call:locatevisualstudio !BUILD_ARC!
		echo simple-lang:configure preparing to find build toolchain...
		echo simple-lang:configure serching for mingw and msys
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
	) else (
		exit /b 0
	)
	
	exit /b 0

:installdebug
	if !EXEC_TYPE!=="install" (
		call:header install "install simple-lang %VERSION%"
		
		REM Remove previous build of the current versions
		if exist "!INSTALLATION_FOLDER!\%VERSION%\" (
			echo a previous simple build %VERSION% is detected
			echo removing previous build and performing a clean build
			call:deletedirectories !INSTALLATION_FOLDER!\%VERSION%\
		)
	)
	if !EXEC_TYPE!=="debug" (
		call:header install "debug build %SIMPLE_DEBUG_VERSION%"
		
		REM Remove previous build of the current versions
		if exist "..\..\%SIMPLE_DEBUG_VERSION%\" (
			echo a previous simple build %SIMPLE_DEBUG_VERSION% is detected
			echo removing previous build and performing a clean build
			call:deletedirectories %~dp0\..\..\%SIMPLE_DEBUG_VERSION%\
		) 
	) 
	call:buildsimpledllexe
	call:copysimpledllexe
	call:copysimpleincludes
	call:resolvedependencies
	call:builddynamicmodules
	call:copydynamicmodules
	call:copysimplemodule
	call:buildsimplelangenvironments
	
	call:removedistfolders
	call:removestubornfiles
	
	exit /b 0
	
:removedistfolders
	if !KEEP_DIST!=="false" (
		call:deletedirectories %~dp0.\-p %~dp0\..\simple\dist %~dp0\..\modules\dynamic_modules\dist\
	)
	
	exit /b 0
	
	
REM BULDING SIMPLE.EXE and SIMPLE.DLL

:buildsimpledllexe	
	if exist "%~dp0\..\simple\dist"  (
		echo simple: removing previous simple build
		call:deletedirectories %~dp0\..\simple\dist
	)
	if !THERE_IS_VS!=="true" (
		call:getsimplecfiles
		echo simple-lang:install:visual-studio flies are !SIMPLE_C_FILES!
		mkdir %~dp0\..\simple\dist
		cl.exe /D_USRDLL /D_WINDLL /TC !SIMPLE_C_FILES! /MT /I %~dp0\..\simple\includes\ /link /DLL /OUT:%~dp0\..\simple\dist\simple.dll
		call:deletetempfiles *.obj *.exp *.cod
		if exist "..\simple\dist\simple.lib" (
			cl.exe /GA /MT /TC %~dp0\..\simple\simple.c /link /LIBPATH:%~dp0\..\simple\dist\ simple.lib /OUT:%~dp0\..\simple\dist\simple.exe
			cl.exe /GA /MT /TC %~dp0\..\simple\simplew.c /link /SUBSYSTEM:windows /LIBPATH:%~dp0\..\simple\dist\ simple.lib /OUT:%~dp0\..\simple\dist\simplew.exe
			call:deletetempfiles *.obj *.exp *.cod
		)
		exit /b 0
	) else (
		if exist "..\simple\makefiles\Makefile-Windows.mk" (
			cd "..\simple\makefiles"
			echo simple: building simple.dll and simple.exe
			make -f Makefile-Windows.mk
			cd ..\..\build
		) else (
			echo error:simple: simple-lang %SIMPLE_DEBUG_VERSION% build 
			echo error:simple: the file 'Makefile-Windows.mk' does not exist in simple directory
			echo error:simple: skipping simple Build
		)
	)
	
	exit /b 0
	
	
REM SIMPLE.EXE AND SIMPLE.DLL HAS BEEN SUCCESSFUL CREATE AND COPY EXECUTABLE TO %SIMPLE_DEBUG_VERSION% DIRECTORY

:copysimpledllexe
	echo Copying Executable and building %VERSION% and %SIMPLE_DEBUG_VERSION% 
	if !EXEC_TYPE!=="install" (
		echo installation folder "!INSTALLATION_FOLDER!\%VERSION%\"
		call:confirmfolderelsecreate "!INSTALLATION_FOLDER!\%VERSION%\bin\"
		if exist "..\simple\dist\simple.dll" (
			echo simple: copying simple.exe and simple.dll to !INSTALLATION_FOLDER!\%VERSION%\bin\ directory
			copy ..\simple\dist\simple* !INSTALLATION_FOLDER!\%VERSION%\bin\
		) else (
			echo error:simple: build fails simple.exe and simple.dll cannot be found
			echo error:simple: try rebuilding individually
		)
	)
	if !EXEC_TYPE!=="debug" (
		call:confirmfolderelsecreate "..\..\%SIMPLE_DEBUG_VERSION%\bin\"
		if exist "..\simple\dist\simple.dll" (
			echo simple: copying simple.exe and simple.dll to ..\..\%SIMPLE_DEBUG_VERSION%\bin directory
			copy ..\simple\dist\simple* ..\..\%SIMPLE_DEBUG_VERSION%\bin
		) else (
			echo error:simple: build fails simple.exe and simple.dll cannot be found
			echo error:simple: try rebuilding individually
		)
	)
	
	exit /b 0

REM COPY THE INCLUDE DIRECTORY	
	
:copysimpleincludes
	call:header includes "copying includes directory for developer"
	if !EXEC_TYPE!=="install" (
		if exist "..\simple\includes" (
			echo includes: copying includes to !INSTALLATION_FOLDER!\%VERSION%\ directory
			call:deletedirectories "!INSTALLATION_FOLDER!\%VERSION%\includes"
			xcopy "..\simple\includes" "!INSTALLATION_FOLDER!\%VERSION%\includes" /s /h /e /i /k /f /c
		) else (
			echo error:includes: the includes directory cannot be found
			echo error:includes: the repository appears to be currupted. 
			echo error:includes: try clonning the simple repository again to resolve the issue
		)
	)
	if !EXEC_TYPE!=="debug" (
		if exist "..\simple\includes" (
			echo includes: copying includes to ..\..\%SIMPLE_DEBUG_VERSION%\ directory
			call:deletedirectories "..\..\%SIMPLE_DEBUG_VERSION%\includes"
			xcopy "..\simple\includes" "..\..\%SIMPLE_DEBUG_VERSION%\includes" /s /h /e /i /k /f /c
		) else (
			echo error:includes: the includes directory cannot be found
			echo error:includes: the repository appears to be currupted. 
			echo error:includes: try clonning the simple repository again to resolve the issue
		)
	)
	
	exit /b 0
	
REM RESOLVE DEPENDENCIES

:resolvedependencies
	call:header install "resolving simple-lang dependencies"
	if !THERE_IS_VS!=="true" (
		SET THERE_IS_VS_TEMP="true"
	)
	REM ssleay32.dll
		echo dependencies: ssleay32.dll
	if !BUILD_ARC!=="x64" (
		if exist "..\modules\dynamic_modules\security\bin\ssleay64.dll" (
			call:movedependencytobin ssleay64.dll ssleay32.dll %~dp0\..\modules\dynamic_modules\security\bin\
		) else (
			call:dependencieserror ssleay64.dll
		)
	) else (
		if exist "..\modules\dynamic_modules\security\bin\ssleay32.dll" (
			call:movedependencytobin ssleay32.dll ssleay32.dll %~dp0\..\modules\dynamic_modules\security\bin\
		) else (
			call:dependencieserror ssleay32.dll
		)
	)
	
	REM libeay32.dll
		echo dependencies: libeay32.dll
	if !BUILD_ARC!=="x64" (
		if exist "..\modules\dynamic_modules\security\bin\libeay64.dll" (
			call:movedependencytobin libeay64.dll libeay32.dll %~dp0\..\modules\dynamic_modules\security\bin\
		) else (
			call:dependencieserror libeay64.dll
		)
	) else (
		if exist "..\modules\dynamic_modules\security\bin\libeay32.dll" (
			call:movedependencytobin libeay32.dll libeay32.dll %~dp0\..\modules\dynamic_modules\security\bin\
		) else (
			call:dependencieserror libeay32.dll
		)
	)
	
	REM libcurl.dll
		echo dependencies: libcurl.dll
	if !BUILD_ARC!=="x64" (
		if exist "..\modules\dynamic_modules\networker\lib\libcurl64.dll" (
			call:generatelibfromdll %~dp0\..\modules\dynamic_modules\networker\lib\libcurl64.dll curl_* 000*
			call:movedependencytobin libcurl64.dll libcurl.dll %~dp0\..\modules\dynamic_modules\networker\lib\
		) else (
			call:dependencieserror libcurl64.dll
		)
	) else (
		if exist "..\modules\dynamic_modules\networker\lib\libcurl.dll" (
			call:generatelibfromdll %~dp0\..\modules\dynamic_modules\networker\lib\libcurl.dll curl_* 000*
			call:movedependencytobin libcurl.dll libcurl.dll %~dp0\..\modules\dynamic_modules\networker\lib\
		) else (
			call:dependencieserror libcurl.dll
		)
	)
	if !THERE_IS_VS_TEMP!=="true" (
		SET THERE_IS_VS="true"
	)
	
	exit /b 0
	
:generatelibfromdll
	if !THERE_IS_VS!=="true" (
		REM call:header configure "configure build %VERSION%"
		REM call:locatevisualstudio !BUILD_ARC!
		REM dumpbin /EXPORTS %1 > %1.txt
		REM findstr %2 %1.txt > %1.2.txt
		REM findstr %3 %1.2.txt > %1.3.txt
		SET THERE_IS_VS="false"
	)
	
	exit /b 0

:movedependencytobin
	echo dependencies: copying %1 to ..\..\%SIMPLE_DEBUG_VERSION%\bin directory
	if !EXEC_TYPE!=="install" (
		call:confirmfolderelsecreate "!INSTALLATION_FOLDER!\%VERSION%\bin\"
		copy %3\%1 !INSTALLATION_FOLDER!\%VERSION%\bin\%2
	)
	if !EXEC_TYPE!=="debug" (
		call:confirmfolderelsecreate  "..\..\%SIMPLE_DEBUG_VERSION%\bin\"
		copy %3\%1 ..\..\%SIMPLE_DEBUG_VERSION%\bin\%2
	)
	
	exit /b 0
	
:dependencieserror
	echo error:dependencies: the dependency %1 cannot be found 
	echo error:dependencies: search for %1 for !BUILD_ARC! and download from reliable source
	echo error:dependencies: manually copy to ..\..\%SIMPLE_DEBUG_VERSION%\bin directory
	
	exit /b 0	
	
REM BULDING DYNAMIC LIBRARIES
	
:builddynamicmodules
	call:header dynamic_modules "dynamic modules for buiild %VERSION%"
	if exist "%~dp0\..\modules\dynamic_modules\dist\"  (
		echo simple: removing previous simple build
		call:deletedirectories %~dp0\..\modules\dynamic_modules\dist\
	)
	if !THERE_IS_VS!=="true" (
		call:builddymodule c archiver
		call:builddymodule c consoler
		call:builddymodule c core_dynamic_module
		call:builddymodule c file_savant
		call:builddymodule c mathic
		REM call:builddymodule cpp fulltick
		REM require .lib call:builddymodule c networker
		REM failed call:builddymodule c parser
		REM require .lib call:builddymodule c security
		call:builddymodule c string_savant
		call:builddymodule c systemic
		
		call:confirmfolderelsecreate "..\modules\dynamic_modules\dist\"
		move *.lib "..\modules\dynamic_modules\dist\"
		move *.dll "..\modules\dynamic_modules\dist\"
	) else (
		if exist "..\modules" (
			cd "..\modules"
			echo modules: modules repository detected
			if exist ".\dynamic_modules\makefiles\Makefile-Windows.mk" (
				cd .\dynamic_modules\makefiles
				if exist "..\dist" (
					echo dynamic_modules: removing previous dynamic modules build
					rm -R ..\dist\
				)
				echo dynamic_modules: build starting...
				make -f Makefile-Windows.mk
				cd ..\
			) else (
				call:repocurrupterror dynamic_modules
			)
			cd ..\..\build
		) else (
			call:repocurrupterror modules
		)
	)
	call:confirmfulltickdymodule
	
	exit /b 0
	
REM FULLTICK(GUI) DYNAMIC MODULE

:confirmfulltickdymodule
	echo dynamic_modules:fulltick: checking if fulltick build successfully
	if !BUILD_ARC!=="x64" (
		SET FULLTICK_DY_MODULE="fulltick64.dll"
	) else (
		SET FULLTICK_DY_MODULE="fulltick.dll"
	)
	if exist "..\modules\dynamic_modules\dist\%FULLTICK_DY_MODULE%" (
		echo dynamic_modules:fulltick: fulltick dynamic module built successfully
	) else (
		echo error:dynamic_modules:fulltick: fulltick dynamic module build failed
		echo error:dynamic_modules:fulltick: fulltick build is sure to fail if you don't have fltk library installed or it is not configured as shared library
		echo error:dynamic_modules:fulltick: visit %FULLTICK_BUILD_ISSUE% for build instruction
		echo dynamic_modules:fulltick: falling back on available backup build.
		if exist "..\modules\dynamic_modules\fulltick\dist\%FULLTICK_DY_MODULE%" (
			echo dynamic_modules:fulltick: backup build found but might be outdated
			echo fulltick: copying fulltick.dll to "..\modules\dynamic_modules\dist\fulltick.dll" directory
			copy "..\modules\dynamic_modules\fulltick\dist\%FULLTICK_DY_MODULE%" "..\modules\dynamic_modules\dist\fulltick.dll"
		) else (
			echo error:dynamic_modules:fulltick: the backup fulltick dynamic module cannot be found
			echo error:dynamic_modules:fulltick: the repository appears to be currupted. 
			echo error:dynamic_modules:fulltick: try clonning the simple repository again to resolve the issue
			echo error:dynamic_modules:fulltick: or visit %FULLTICK_BUILD_ISSUE% to build instruction
		)
	) 
	
	exit /b 0
	
:builddymodule
	echo building %2 dynamic module
	call:getdynamicmodulefiles %1 %2
	cl.exe /D_USRDLL /D_WINDLL /LD /MT !DY_MODULE_FILES! /link /DLL /LIBPATH:%~dp0\..\simple\dist\ simple.lib 
	call:deletetempfiles *.obj *.exp *.cod
		
	exit /b 0
	
:copydynamicmodules
	call:header dynamic_modules "copying dynamic_modules to %VERSION%"
	if !EXEC_TYPE!=="install" (
		if exist "..\modules\dynamic_modules\dist\systemic.dll" (
			echo dynamic_modules: copying dynamic modules to !INSTALLATION_FOLDER!\%VERSION%\modules\dynamic_modules directory
			call:confirmfolderelsecreate "!INSTALLATION_FOLDER!\%VERSION%\modules\dynamic_modules"
			copy ..\modules\dynamic_modules\dist\*.dll !INSTALLATION_FOLDER!\%VERSION%\modules\dynamic_modules
		) else (
			call:dynamicmoduleserror
		)
	)
	if !EXEC_TYPE!=="debug" (
		if exist "..\modules\dynamic_modules\dist\systemic.dll" (
			echo dynamic_modules: copying dynamic modules to ..\..\%SIMPLE_DEBUG_VERSION%\modules\dynamic_modules directory
			call:confirmfolderelsecreate "%~dp0\..\..\%SIMPLE_DEBUG_VERSION%\modules\dynamic_modules"
			copy ..\modules\dynamic_modules\dist\*.dll ..\..\%SIMPLE_DEBUG_VERSION%\modules\dynamic_modules
		) else (
			call:dynamicmoduleserror
		)
	)

	exit /b 0
	
REM DYNAMIC MODULE ERROR
	
:dynamicmoduleserror
	echo error:dynamic_modules: build fails the dynamic modules cannot be found
	echo error:dynamic_modules:	try building each module individually 
	
	exit /b 0
	
REM CURRUPT REPOSITORY ERROR
	
:repocurrupterror
	echo error:%1: %1 directory does not exist
	echo error:%1: the repository appears to be currupted. 
	echo error:%1: try clonning the simple repository again to resolve the issue
	
	exit /b 0 
	
REM COPY THE SIMPLE MODULES
	
:copysimplemodule
	call:header modules "copying simple modules to %SIMPLE_DEBUG_VERSION%"
	call:copymodulesinloop archive fulltick simple web
	call:resolvefirstcalls
	copy "..\modules\modules-dependencies.conf" "%~dp0\..\..\%SIMPLE_DEBUG_VERSION%\modules\"

	exit /b 0
	
REM COPY ALL THE MODULE IN LOOP MODE 
	
:copymodulesinloop
	for %%x in (%*) do (
		echo modules: %%x module
		if exist "..\modules\%%x" (
			if !EXEC_TYPE!=="install" (
				echo modules: copying %%x module to !INSTALLATION_FOLDER!\%VERSION%\modules directory
				xcopy "../modules/%%x" "!INSTALLATION_FOLDER!\%VERSION%\modules\%%x\" /s /h /e /k /f /c
			)
			if !EXEC_TYPE!=="debug" (
				echo modules: copying %%x module to ..\..\%SIMPLE_DEBUG_VERSION%\modules directory
				xcopy "../modules/%%x" "%~dp0\..\..\%SIMPLE_DEBUG_VERSION%\modules\%%x\" /s /h /e /k /f /c
			)
		) else (
			call:modulecurrupterror %%x
		)
	)

	exit /b 0
	
REM THE __FIRST_CALLS.SIM FILE IS IMPORTANT FOR SIMPLE-LANG MODULES TO FUNCTION 
	
:resolvefirstcalls
	echo modules:simple: treating the __first_calls.sim file 
	if !EXEC_TYPE!=="install" (
		if exist "!INSTALLATION_FOLDER!\%VERSION%\modules\simple\core\__first_calls.sim" (
			echo modules:simple: this is a windows system the corresponding callDynamicModule are filled
			call:echodycalls !INSTALLATION_FOLDER!\%VERSION%\modules\simple\core\__first_calls.sim dll
		) else (
			call:modulecurrupterror "__first_calls.sim file in"
		)
	)
	if !EXEC_TYPE!=="debug" (
		if exist "..\..\%SIMPLE_DEBUG_VERSION%\modules\simple\core\__first_calls.sim" (
			echo modules:simple: this is a windows system the corresponding callDynamicModule are filled
			call:echodycalls %~dp0\..\..\%SIMPLE_DEBUG_VERSION%\modules\simple\core\__first_calls.sim dll
		) else (
			call:modulecurrupterror "__first_calls.sim file in"
		)
	)
	
	exit /b 0
	
:echodycalls
	echo callDynamicModule("systemic.%2") callDynamicModule("string_savant.%2") >> %1
	
	exit /b 0
	
REM CURRUPT MODULE ERROR

:modulecurrupterror
	echo error:modules: the %1 module cannot be found
	echo error:modules: the repository appears to be currupted. 
	echo error:modules: try clonning the simple repository again to resolve the issue

	exit /b 0 
	
REM SIMPLE_LANG ENVIRONMENT PROGRAMS
REM THE ENVIRONMENT PROGRAMS WILL ALSO BE INSTALLED IN SAME BIN DIRECTORY AS SIMPLE

:buildsimplelangenvironments
	call:header environment "environment program build %VERSION%"
	call:confirmsimplebuild
	if !SIMPLE_EXECUTABLE!=="notfound" (
		echo.
	) else (
		SET BAKE_EXECUTABLE="..\environment\bake\bake.sim"
		if exist !BAKE_EXECUTABLE! (
			echo environment:bake.sim: ..\environment\bake\bake.sim found 
			echo environment:bake.sim: starting environment programs build...
			call:buildenvironmentinloop bake modular simplerepl simplebridge simplepad webworker
		) else (
			call:environmentnotfound ..\environment\bake\bake.sim
		)
	)

	exit /b 0
	
:buildenvironmentinloop
	for %%x in (%*) do (
		echo environment:build: %%x
		if exist "..\environment\%%x\%%x.sim" (
			if "%%x"=="simplepad" (
				SET BAKE_FLAG_GUI=-gui
			) else (
				SET BAKE_FLAG_GUI=
			)
			if exist ../../simple-arts/environment/%%x.ico (
				
				call:buildsingleenvironment %%x !BAKE_FLAG_GUI! -I/../../simple-arts/environment/%%x.ico
			) else (
				call:buildsingleenvironment %%x !BAKE_FLAG_GUI! 
			)
		) else (
			echo error:environment:build ..\environment\%%x\%%x.sim cannot be found
			echo error:environment:build skipping %%x
		)
	)

	exit /b 0
	
:buildsingleenvironment 
	echo environment:build: building %1 
	if !EXEC_TYPE!=="install" (
		!SIMPLE_EXECUTABLE! !BAKE_EXECUTABLE! %2 %3 -F/!INSTALLATION_FOLDER!\%VERSION%\bin\ ..\environment\%1\%1.sim
	)
	if !EXEC_TYPE!=="debug" (
		!SIMPLE_EXECUTABLE! !BAKE_EXECUTABLE! %2 %3 -F/..\..\%SIMPLE_DEBUG_VERSION%\bin\ ..\environment\%1\%1.sim
	)
	
	exit /b 0
	
REM CONFIRM SIMPLE.EXE IS BUILT SUCCESSFULLY
	
:confirmsimplebuild
	if !EXEC_TYPE!=="install" (
		SET SIMPLE_EXECUTABLE="!INSTALLATION_FOLDER!\%VERSION%\bin\simple.exe"
	)
	if !EXEC_TYPE!=="debug" (
		SET SIMPLE_EXECUTABLE="%~dp0\..\..\%SIMPLE_DEBUG_VERSION%\bin\simple.exe"
	)
	if exist !SIMPLE_EXECUTABLE! (
		echo environment:simple: simple.exe found 
		echo environment:simple: proceeding to detect bake.sim 
	) else (
		call:environmentnotfound simple.exe
		SET SIMPLE_EXECUTABLE="notfound"
	) 
	
	exit /b 0
	
REM ENVIRONMENT PROGRAM BUILD ERROR
	
:environmentnotfound 
	echo error:environment: %1 not found in distribution folder
	echo error:environment: stopping the environment build
	echo error:environment: try cloning the simple directory again to resolve error

	exit /b 0

:removestubornfiles
	if !EXEC_TYPE!=="install" (
		call:deletetempfilesna !INSTALLATION_FOLDER!\%VERSION%\bin\*.exp 
	) else (
		call:deletetempfiles ..\..\%SIMPLE_DEBUG_VERSION%\bin\*.exp 
	)
	call:deletetempfiles ..\simple\dist\*.exp modules\dynamic_modules\dist\*.exp
	
	exit /b 0 

:getsimplecfiles
	if exist "..\simple\sources\" (
		SET SIMPLE_C_FILES="%~dp0\..\simple\sources\simple_*.c"
	) else (
		SET SIMPLE_C_FILES="%~dp0\none\*.c"
	)
	
	exit /b 0

:getdynamicmodulefiles 
	if exist "..\modules\dynamic_modules\" (
		SET DY_MODULE_INCLUDE_DIR="%~dp0\..\modules\dynamic_modules\%2\"
		SET DY_MODULE_FILES="%~dp0\..\modules\dynamic_modules\%2\*.%1"
	) else (
		call:repocurrupterror dynamic_modules
	)
	
	exit /b 0

:locatevisualstudio
	echo simple-lang:configure:buildtool Microsoft Visual Studio is specified
	echo simple-lang:configure:buildtool searching for Microsoft Visual Studio
	if "%1"=="" (
		SET "PROGRAMFILESPATH=%ProgramFiles%"
	)
	if "%1"==""x64"" (
		SET "PROGRAMFILESPATH=%ProgramFiles%"
	)
	if "%1"==""x86"" (
		SET "PROGRAMFILESPATH=%ProgramFiles(x86)%"
	)
	for /d %%a in ("%PROGRAMFILESPATH%\Microsoft Visual Studio*") do (
		for /f "tokens=3 delims=\" %%x in ("%%a") do SET MVS=%%a\
		break
	)
	if !BUILD_ARC!=="x86" (
		if exist "!MVS!\VC\vcvarsall.bat" (
			echo simple-lang:configure:buildtool found !MVS!
			call:callmsvisualstudio "!MVS!\VC\vcvarsall.bat"
			exit /b 0
		) else (
			echo simple-lang:configure:buildtool Microsoft Visual Studio not found
			SET NO_BUILDTOOL="true"
			exit /b 0
		)
	) else (
		if exist "!MVS!\VC\vcvarsall.bat" (
			echo simple-lang:configure:buildtool found !MVS!
			call:callmsvisualstudio "!MVS!\VC\vcvarsall.bat"
			exit /b 0
		) else (
			echo simple-lang:configure:buildtool Microsoft Visual Studio not found in x64 directory
			echo simple-lang:configure:buildtool resolve to 32 bit
			echo simple-lang:configure:buildtool Looking for 32 bit x86 MS Visual Studio 
			SET BUILD_ARC="x86"
			call:locatevisualstudio x86
			exit /b 0
		)
	)

	exit /b 0
	
:callmsvisualstudio 
	echo simple-lang:configure:visual-studio calling Microsoft Visual Studio CMD File
	if !BUILD_ARC!=="x64" (
		call %1 x64
	) else (
		call %1 x86
	)
	SET NO_BUILDTOOL="false"

	exit /b 0
	
:compilernotfound
	echo error:simple-lang:compiler %1 not found 
	echo error:simple-lang:compiler please confirm your installation folder
	echo error:simple-lang:compiler restart the build process again
	SET NO_BUILDTOOL="true"
	
	exit /b 0
	
:deletedirectories
	for %%x in (%*) do (
		rmdir /S /Q %%x 2> nul
	)
	
	exit /b 0
	
:deletetempfiles
	for %%x in (%*) do (
		del /f %~dp0\%%x
	)
	
	exit /b 0
	
:deletetempfilesna
	for %%x in (%*) do (
		del /f %%x
	)
	
	exit /b 0
	
:confirmfolderelsecreate
	if exist %1 (
		echo simple/confirmfolderelsecreate: the %1 directory already exist
	) else (
		echo simple/bin: creating the % directory
		mkdir %1
	)
	
	exit /b 0
	
:locatemingw
	echo simple-lang:configure: checking for mingw in C:\MinGW\msys\1.0\bin\
	if exist "C:\MinGW\msys\1.0\bin\" (
		echo simple-lang:configure found MinGW Build Toolchain
		if !EXEC_TYPE!=="configure" (
			call:setcompilerenv C:\MinGW\bin\ C:\MinGW\msys\1.0\bin
		) else (
			SET PATH=!PATH!;C:\MinGW\bin\;C:\MinGW\msys\1.0\bin
		)
		SET NO_BUILDTOOL="true"
		exit /b 0
	)
	echo simple-lang:configure: mingw not found in C:\MinGW\msys\1.0\bin\
	call:locategcc
	
	exit /b 0
	
:locatecygwin
	echo simple-lang:configure: checking for cygwin in C:\cygwin\
	if exist "C:\cygwin\" (
		echo simple-lang:configure found CygWIN Build Toolchain
		if !EXEC_TYPE!=="configure" (
			call:setcompilerenv C:\cygwin\bin\
		) else (
			SET PATH=!PATH!;C:\cygwin\bin\
		) 
		SET NO_BUILDTOOL="true"
		exit /b 0
	)
	echo simple-lang:configure: cygwin not found in C:\cygwin\
	call:locategcc
		
	exit /b 0
	
:locategcc
	echo simple-lang:configure:compiler: checking if gcc is present in path
	gcc 2> ..\..\simple_build_configure
	SET /p GCCVAL=<..\..\simple_build_configure
	if "!GCCVAL!"=="gcc: fatal error: no input files" (
		call:deletetempfiles ..\..\simple_build_configure
		echo simple-lang:configure:compiler: gcc found
		echo simple-lang:configure:compiler: checking if g++ is present in path
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
				SET NO_BUILDTOOL="false"
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
	echo simple-lang:build help %VERSION%
	echo =============================================================
	echo Usage: Windows-Build.bat [FLAG]
	echo [FLAGS] :
	echo 	-c --configure	configure your system for simple-lang successfull build
	echo 	-i --install	install simple-lang on your system
	echo 	-b --build-dir	manually enter folder to install simple-lang 
	echo 	-u --uninstall	uninstall simple-lang from your system
	echo 	-d --debug	create a distributable version in ..\..\ source directory
	echo 	x86 --32-bit	build 32 bit version of simple-lang
	echo 	x64 --64-bit	build 64 bit version of simple-lang
	echo 	-k --keep	keep the */dist/ folder(s) in source tree
	echo 	-h --help	print this help message
	echo.
	echo [C/C++ COMPILER FLAGS]
	echo 	-gcc --gnu	build simple with available GNU toolchain
	echo 	-mg --mingw	build simple with MinGW tool chain
	echo 	-cy --cygwin	build simple with Cygwin toolchain
	echo 	-vs --visual-studio	build simple with Microsoft Visual Studio
	echo.
	echo [STANDALONE BUILD FLAGS]
	echo 	-so --simple-only	build only simple.exe, simplew.exe and simple.dll
	echo 	-do --dep-only		build only the dependencies
	echo 	-io --includes-only	copy only the simple includes files
	echo 	-mo --modules-only	copy only the standard modules
	echo 	-yo --dymodules-only	build only the dynamic modules
	echo 	-eo --environment-only	build only the environment programs
	
	exit /b 0
