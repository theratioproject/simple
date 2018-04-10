echo off
cls

REM BULDING SIMPLE.EXE and SIMPLE.DLL
if exist "../src/Makefile-Windows.mks" (
	cd "../src"
	echo `
	echo `
	echo 	SIMPLE s0.3.302-debug build 
	echo		Building simple.dll and simple.exe
	make -f Makefile-Windows.mk
	cd ../build
) else (
	echo `
	echo `
	echo 	SIMPLE s0.3.302-debug build 
	echo 		The file 'Makefile-Windows.mk' does not exist in src folder
	echo 		Skipping simple Build
)

REM BULDING DYNAMIC LIBRARIES

	echo `
	echo 	Building Dynamic modules
	
if exist "../../modules" (
	cd "../../modules"
	echo			Modules repository detected
	if exist "./dynamic_modules/Makefile-Windows.mk" (
		cd ./dynamic_modules
		echo		Starting Build...
		make -f Makefile-Windows.mk
		cd ../
	) else (
		echo 		dynamic_modules folder does not exist
		echo 		Kindly Clone the modules repository again
	)
	cd ../simple/build
) else (
	echo 		modules repository does not exist
	echo 		Clone the repository in the same folder as simple repository
	echo 		if you want to build them else ignore
	echo 		if ignored only the simple.exe and simple.dll will be built
)

REM has been successful create and copy executable to s0.3.302-debug folder
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
	cp ../src/dist/simple.dll ../../s0.3.302-debug/bin
	exit /b
) else (
	echo `
	echo `
	echo 		SIMPLE s0.3.302-debug build 
	echo 		The file 'Makefile-Windows.mk' does not exist in src folder
	echo 		Stopping Build
)

REM CLEANING UP
if exist "./-p" (
	rmdir -f "./-p"
}


exit /b
