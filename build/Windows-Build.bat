echo off
cls 

setlocal enabledelayedexpansion

SET EXEC_TYPE=""
SET BUILD_ARC="x86"
SET VER="0.3.35"
SET THERE_IS_VS="false"
SET KEEP_DIST="false"
SET INSTALLATION_FOLDER="C:\Simple\"
SET VERSION="s0.3.35"
SET SIMPLE_DEBUG_VERSION="s0.3.35-debug"
SET FULLTICK_BUILD_ISSUE="<https://github.com/simple-lang/simple/issues/16>"

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
	if "%%x"=="-p" (
		SET /p INSTALLATION_FOLDER=Enter the folder you want to install simple-lang to : 
	)
	if "%%x"=="--install-folder" (
		SET /p INSTALLATION_FOLDER=Enter the folder you want to install simple-lang to : 
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
	if "%%x"=="-vs" (
		SET THERE_IS_VS="true"
	)
	if "%%x"=="--visual-studio" (
		SET THERE_IS_VS="true"
	)
	if "%%x"=="-gcc" (
		SET THERE_IS_VS="false"
	)
	if "%%x"=="--gnu" (
		SET THERE_IS_VS="false"
	)
)

if !THERE_IS_VS!=="true" (
	call:header configure "configure build %VERSION%"
	call:locatevisualstudio !BUILD_ARC!
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
)
if !EXEC_TYPE!=="simple-only-debug" (
	SET EXEC_TYPE="debug"
	call:header debug "debug simple-lang %VERSION%"
	call:buildsimpledllexe
	call:copysimpledllexe
)
if !EXEC_TYPE!=="includes-only-install" (
	SET EXEC_TYPE="install"
	call:copysimpleincludes
)
if !EXEC_TYPE!=="includes-only-debug" (
	SET EXEC_TYPE="debug"
	call:copysimpleincludes
)
if !EXEC_TYPE!=="dymodules-only-install" (
	SET EXEC_TYPE="install"
	call:header install "install simple-lang %VERSION%"
	call:buildsimpledllexe
	call:builddynamicmodules
)
if !EXEC_TYPE!=="dymodules-only-debug" (
	call:header install "install simple-lang %VERSION%"
	call:buildsimpledllexe
	call:builddynamicmodules
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
	if !THERE_IS_VS!=="true" (
		exit /b 0
	) 
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
				call:locatevisualstudio !BUILD_ARC!
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
	
	if !KEEP_DIST!=="false" (
		call:deletedirectories %~dp0\..\simple\dist %~dp0\..\modules\dynamic_modules\dist\
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
		if exist "../simple/dist/simple.dll" (
			echo simple: copying simple.exe and simple.dll to !INSTALLATION_FOLDER!\%VERSION%\bin\ directory
			copy ..\simple\dist\simple* !INSTALLATION_FOLDER!\%VERSION%\bin\
		) else (
			echo error:simple: build fails simple.exe and simple.dll cannot be found
			echo error:simple: try rebuilding individually
		)
	)
	if !EXEC_TYPE!=="debug" (
		call:confirmfolderelsecreate "..\..\%SIMPLE_DEBUG_VERSION%\bin\"
		if exist "../simple/dist/simple.dll" (
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

REM the dynamic libraries has been successful generated now copy them to %SIMPLE_DEBUG_VERSION% directory
	echo dynamic_modules: copying Dynamic Modules to %SIMPLE_DEBUG_VERSION%
if exist "../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules" (
	echo dynamic_modules: the ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules directory already exist
) else (
	echo dynamic_modules: creating the ../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules directory
	mkdir "../../%SIMPLE_DEBUG_VERSION%/modules/dynamic_modules"
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
	call:deletedirectories "./-p"
}
if exist "../modules/dynamic_modules/dist/" (
	call:deletedirectories "../modules/dynamic_modules/dist/"
)
if exist "../simple/dist/" (
	call:deletedirectories "../simple/dist/"
)

exit /b

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
			echo simple-lang:configure:buildtool Looking for 32 bit x86 MS Visual Studio 
			call:locatevisualstudio x86
			exit /b 0
		)
	) else (
		if exist "!MVS!\VC\vcvarsall.bat" (
			echo simple-lang:configure:buildtool found !MVS!
			call:callmsvisualstudio "!MVS!\VC\vcvarsall.bat"
			exit /b 0
		) else (
			echo simple-lang:configure:buildtool resolve to 32 bit
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

	exit /b 0
	
:compilernotfound
	echo error:simple-lang:compiler %1 not found 
	echo error:simple-lang:compiler please confirm your installation folder
	echo error:simple-lang:compiler restart the build process again
	
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
	
:confirmfolderelsecreate
	if exist %1 (
		echo simple/confirmfolderelsecreate: the %1 directory already exist
	) else (
		echo simple/bin: creating the % directory
		mkdir %1
	)
	
	exit /b 0

:help
	echo =============================================================
	echo simple-lang:build help %VERSION%
	echo =============================================================
	echo Usage: ./sudo Windows-Build.bat [FLAG]
	echo [FLAGS] :
	echo 	-c --configure	configure your system for simple-lang successfull build
	echo 	-i --install	install simple-lang on your system
	echo 	-u --uninstall	uninstall simple-lang from your system
	echo 	-d --debug	create a distributable version in ..\..\ source directory
	echo 	x86 --32-bit	build 32 bit version of simple-lang
	echo 	x64 --64-bit	build 64 bit version of simple-lang
	echo 	-k --keep	keep the */dist/ folder(s) in source tree
	echo 	-h --help	print this help message
	echo 	-gcc --gnu	build simple with available GNU toolchain
	echo 	-vs --visual-studio	build simple with Microsoft Visual Studio
	echo.
	echo [STANDALONE BUILD FLAGS]
	echo 	-so --simple-only	build only simple.exe, simplew.exe and simple.dll
	echo 	-do --dep-only		build only the dependencies
	echo 	-io --includes-only		copy only the simple includes files
	echo 	-yo --dymodules-only		build only the dynamic module
	
	exit /b 0
