echo off
cls

if exist "../src/Makefile-Windows.mk" (
	cd "../src"
	echo "Hello we good"
	exit /b
)