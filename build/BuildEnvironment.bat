echo off

	echo `
	echo 	Building Environment Program to Executable 
	
SET SMAKE=""

REM Confirm simple is present

if exist "../../s0.3.302-debug/bin/simple.exe" (
	echo 		simple Found. yea now chek for smake...
	SET SIMPLE="./../s0.3.302-debug/bin/simple.exe"
) else (
	echo 		simple cannot be found
	echo 		The build process failed bye
	exit 
)
	
REM Confirm smake is present

if exist "../../s0.3.302-debug/environment/smake.sim" (
	echo 		Smake Found. yea Starting Build...
	SET SMAKE="../../s0.3.302-debug/environment/smake.sim"
) else (
	echo 		smake.sim cannot be found
	echo 		no smake no build bye
	exit 
)

REM Builing SimplePad
echo 		`SimplePad
if exist "../../s0.3.302-debug/environment/SimplePad.sim" (
	if exist ../../simple-arts/environment/simplepad.ico (
		echo 		Building SimplePad with icon
		SIMPLE SMAKE -I/../../simple-arts/environment/simplepad.ico ../../s0.3.302-debug/environment/SimplePad.sim	
	) else (
		echo 		Building SimplePad
		SIMPLE SMAKE -delete ../../s0.3.302-debug/environment/SimplePad.sim
	)
) else (
	echo 		../../s0.3.302-debug/environment/SimplePad.sim cannot be found
	echo 		skipping SimplePad
)

REM Builing REPL
echo 		`SimpleRepl
if exist "../../s0.3.302-debug/environment/SimpleRepl.sim" (
	if exist ../../simple-arts/environment/simplerepl.ico (
		echo 		Building SimpleRepl with icon
		SIMPLE SMAKE -I/../../simple-arts/environment/simpleprepl.ico -delete ../../s0.3.302-debug/environment/SimpleRepl.sim	
	) else (
		echo 		Building SimpleRepl
		SIMPLE SMAKE -delete ../../s0.3.302-debug/environment/SimpleRepl.sim
	)
) else (
	echo 		../../s0.3.302-debug/environment/SimpleRepl.sim cannot be found
	echo 		skipping SimpleRepl
)