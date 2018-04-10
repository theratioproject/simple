echo off
cls

if exist "../src/Makefile-Windows.mk" (
	cd "../src"
	echo `
	echo `
	echo 		SIMPLE s0.3.302-debug build 
	echo		Building simple.dll and simple.exe
	exit /b
) else (
	echo `
	echo `
	echo 		SIMPLE s0.3.302-debug build 
	echo 		The file 'Makefile-Windows.mk' does not exist in src folder
	echo 		Stopping Build
)