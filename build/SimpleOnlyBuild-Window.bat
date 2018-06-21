echo off
cls

SET VERSION="s0.3.34"
SET SIMPLE_DEBUG_VERSION="s0.3.34-debug"

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