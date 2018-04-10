echo off
cls

if exist "../src/Makefile-Windows.mks" (
	cd "../src"
	echo `
	echo `
	echo 		SIMPLE s0.3.302-debug build 
	echo		Building simple.dll and simple.exe
	make -f Makefile-Windows.mk
	cd ../build
	exit /b
) else (
	echo `
	echo `
	echo 		SIMPLE s0.3.302-debug build 
	echo 		The file 'Makefile-Windows.mk' does not exist in src folder
	echo 		Skipping simple Build
)

REM has been successful create and copy executable to s0.3.302-debug folder
if exist "../../s0.3.302-debug/bin/" (
	echo yea
) else (
	echo 		Creating the ../../s0.3.302-debug/bin/ folder
	mkdir -p "../../s0.3.302-debug/bin/"
)

if exist "../src/dist/simple.exe" (
	echo `
	echo `
	echo 		Copying simple.exe and simple.dll to ../../s0.3.302-debug/bin folder
	cp ../src/dist/simple.exe ../../s0.3.302-debug/bin
	exit /b
) else (
	echo `
	echo `
	echo 		SIMPLE s0.3.302-debug build 
	echo 		The file 'Makefile-Windows.mk' does not exist in src folder
	echo 		Stopping Build
)