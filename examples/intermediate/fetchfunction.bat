echo off
cls 

setlocal enabledelayedexpansion

SET DLLNAME=%1
SET BUILD_ARC=%2
SET NO_BUILDTOOL="true"
SET MVS=""

call:generatelibfromdll !DLLNAME! !BUILD_ARC!
exit /b 0


:generatelibfromdll
	call:locatevisualstudio !BUILD_ARC!
	echo !DLLNAME! and !BUILD_ARC! and !NO_BUILDTOOL!
	exit /b 0
	dumpbin /EXPORTS %1 > %1.txt
	findstr %2 %1.txt > %1.2.txt
	findstr %3 %1.2.txt > %1.3.txt
	exit /b 0

:locatevisualstudio
	echo simple-lang:configure:buildtool Microsoft Visual Studio is specified
	echo simple-lang:configure:buildtool searching for Microsoft Visual Studio
	if "%1"=="" (
		SET "PROGRAMFILESPATH=%ProgramFiles%"
	)
	if "%1"=="x64" (
		SET "PROGRAMFILESPATH=%ProgramFiles%"
	)
	if "%1"=="x86" (
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
			SET NO_BUILDTOOL="true"
			exit /b 0
		)
	) else (
		if exist "!MVS!\VC\vcvarsall.bat" (
			echo simple-lang:configure:buildtool found !MVS!
			call:callmsvisualstudio "!MVS!\VC\vcvarsall.bat"
			exit /b 0
		) else (
			echo simple-lang:configure:buildtool Microsoft Visual Studio not found in x64 directory
			echo simple-lang:configure:buildtool resolve to 32 bit
			echo simple-lang:configure:buildtool Looking for 32 bit x86 MS Visual Studio 
			SET BUILD_ARC="x86"
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
	SET NO_BUILDTOOL="false"

	exit /b 0