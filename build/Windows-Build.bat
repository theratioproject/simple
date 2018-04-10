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
	echo 		Stopping Build
)

~Build has been successful