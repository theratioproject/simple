REM ENVIRONMENT PROGRAMS

SET SIMPLE_DEBUG_VERSION="s0.3.303-debug"

REM move the environment to %SIMPLE_DEBUG_VERSION% folder
	echo `
	echo 	Copying Environment Programs to %SIMPLE_DEBUG_VERSION%
	
if exist "../../%SIMPLE_DEBUG_VERSION%/environment" (
	echo 		the ../../%SIMPLE_DEBUG_VERSION%/environment folder already exist
) else (
	echo 		Creating the ../../%SIMPLE_DEBUG_VERSION%/environment folder
	mkdir "../../%SIMPLE_DEBUG_VERSION%/environment"
)

REM modular	
	echo 		`modular
if exist "../../environment/modular/modular.sim" (
	echo 		Copying modular to ../../%SIMPLE_DEBUG_VERSION%/environment folder
	cp ../../environment/modular/modular.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo 		../../environment/modular/modular.sim cannot be found
	echo 		skipping modular
)

REM repl
	echo 		`repl
if exist "../../environment/repl/simplerepl.sim" (
	echo 		Copying repl to ../../%SIMPLE_DEBUG_VERSION%/environment folder
	cp ../../environment/repl/simplerepl.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo 		../../environment/repl/simplerepl.sim cannot be found
	echo 		skipping repl
)

REM simplepad
	echo 		`simplepad
if exist "../../environment/simplepad/simplepad.sim" (
	echo 		Copying simplepad to ../../%SIMPLE_DEBUG_VERSION%/environment folder
	cp ../../environment/simplepad/simplepad.sim ../../%SIMPLE_DEBUG_VERSION%/environment
	REM cp ../../environment/simplepad/runwindows.bat ../../%SIMPLE_DEBUG_VERSION%/environment
	REM cp ../../environment/simplepad/debugwindows.bat ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo 		../../environment/simplepad/simplepad.sim cannot be found
	echo 		skipping simplepad
)

REM smake 
echo 		`smake
if exist "../../environment/smake/smake.sim" (
	echo 		Copying smake to ../../%SIMPLE_DEBUG_VERSION%/environment folder
	cp ../../environment/smake/smake.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo 		../../environment/smake/simplepad.sim cannot be found
	echo 		skipping smake
)

REM spider
	echo 		`spider
if exist "../../environment/spider/spider.sim" (
	echo 		Copying spider to ../../%SIMPLE_DEBUG_VERSION%/environment folder
	cp ../../environment/spider/spider.sim ../../%SIMPLE_DEBUG_VERSION%/environment
) else (
	echo 		../../environment/spider/simplepad.sim cannot be found
	echo 		skipping spider
)

REM build environment programs executable

echo off

	echo `
	echo 	Building Environment Program to Executable 
	
SET SMAKE=""
SET SIMPLE=""

REM Confirm simple is present

if exist "../../%SIMPLE_DEBUG_VERSION%/bin/simple.exe" (
	echo 		simple Found. yea now to check for smake...
	SET SIMPLE="../../%SIMPLE_DEBUG_VERSION%/bin/simple.exe"
) else (
	echo 		simple cannot be found
	echo 		The build process failed bye
	REM exit 
)
	
REM Confirm smake is present

if exist "../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim" (
	echo 		Smake Found. yea Starting Build...
	SET SMAKE="../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim"
) else (
	echo 		smake.sim cannot be found
	echo 		no smake no build bye
	REM exit 
)

REM Builing simplepad
echo 		`simplepad
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/simplepad.sim" (
	if exist ../../simple-arts/environment/simplepad.ico (
		echo 		Building simplepad with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simplepad.ico -gui -delete ../../%SIMPLE_DEBUG_VERSION%/environment/simplepad.sim	
	) else (
		echo 		Building simplepad
		%SIMPLE% %SMAKE% -gui -delete ../../%SIMPLE_DEBUG_VERSION%/environment/simplepad.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/simplepad.sim cannot be found
	echo 		skipping simplepad
)

REM Builing REPL
echo 		`simplerepl
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/simplerepl.sim" (
	if exist ../../simple-arts/environment/simplerepl.ico (
		echo 		Building simplerepl with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simpleprepl.ico -delete ../../%SIMPLE_DEBUG_VERSION%/environment/simplerepl.sim	
	) else (
		echo 		Building simplerepl
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/environment/simplerepl.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/simplerepl.sim cannot be found
	echo 		skipping simplerepl
)

REM Building modular
echo 		`modular
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/modular.sim" (
	if exist ../../simple-arts/environment/modular.ico (
		echo 		Building modular with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simpleprepl.ico -delete ../../%SIMPLE_DEBUG_VERSION%/environment/modular.sim	
	) else (
		echo 		Building modular
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/environment/modular.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/modular.sim cannot be found
	echo 		skipping modular
)

REM Building spider
echo 		`spider
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/spider.sim" (
	if exist ../../simple-arts/environment/spider.ico (
		echo 		Building spider with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/simpleprepl.ico -delete ../../%SIMPLE_DEBUG_VERSION%/environment/spider.sim	
	) else (
		echo 		Building spider
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/environment/spider.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/spider.sim cannot be found
	echo 		skipping spider
)

REM Building smake should be the last build or first whatever ok ok last is better
REM Building SMAKE
echo 		`Smake
if exist "../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim" (
	if exist ../../simple-arts/environment/smake.ico (
		echo 		Building smake with icon
		%SIMPLE% %SMAKE% -I/../../simple-arts/environment/smake.ico -delete ../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim	
	) else (
		echo 		Building smake
		%SIMPLE% %SMAKE% -delete ../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim
	)
) else (
	echo 		../../%SIMPLE_DEBUG_VERSION%/environment/smake.sim cannot be found
	echo 		skipping smake
)


REM not copying example repository if you want it in the debug folder 
REM you can copy it manually

REM CLEANING UP
if exist "./-p" (
	rmdir -f "./-p"
}


REM exit /b