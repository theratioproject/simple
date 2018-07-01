echo off
cls

SET VERSION="s0.3.34"
SET SIMPLE_DEBUG_VERSION="s0.3.34-debug"
SET FULLTICK_BUILD_ISSUE="<https://github.com/simple-lang/simple/issues/16>"

echo 	simple-lang build %SIMPLE_DEBUG_VERSION%

REM BULDING SIMPLE.EXE and SIMPLE.DLL
if exist "../simple/makefiles/Makefile-Windows.mk" (
	cd "../simple/makefiles"
	echo simple: simple-lang %SIMPLE_DEBUG_VERSION% build 
	echo simple: building simple.dll and simple.exe
	if exist "../dist/"  (
		echo simple: removing previous simple build
		rm -r ../dist/
	)
	make -f Makefile-Windows.mk
	cd ../../build
) else (
	echo error:simple: simple-lang %SIMPLE_DEBUG_VERSION% build 
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
