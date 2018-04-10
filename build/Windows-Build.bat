echo off
cls

if exist "../src/Makefile-Windows.mks" (
	cd "../src"
	echo "Hello we good"
	exit /b
) else (
	echo 
	echo "The file 'Makefile-Windows.mk' does not exist in src folder"
)