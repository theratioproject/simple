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
	cp ../src/dist/simplew.exe ../../s0.3.302-debug/bin
	cp ../src/dist/simple.dll ../../s0.3.302-debug/bin
) else (
	echo 		Build fails simple.exe and simple.dll cannot be found
	echo 		in the ../src/dist/ folder try rebuilding again if it
	echo 		fails again run the build individually
)