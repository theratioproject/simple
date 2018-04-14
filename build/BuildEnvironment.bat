echo off

	echo `
	echo 	Building Environment Program to Executable 
	
SET SMAKE=""
ECHO We're working with %SMAKE%
	
REM Confirm smake is present
if exist "../../s0.3.302-debug/environment/smake.sim" (
	echo 		Smake Found. yea Starting Build...
) else (
	echo 		smake.sim cannot be found
	echo 		no smake no build bye
	REM exit 
)


REM Builing SimplePad
echo 		`SimplePad
if exist "../../s0.3.302-debug/environment/SimplePad.sim" (
	if exist ../../simple-arts/environment/simplepad.ico (
		echo 		Building SimplePad with icon
		simple ../../s0.3.302-debug/environment/smake.sim -I/../../simple-arts/environment/simplepad.ico -delete ../../s0.3.302-debug/environment/SimplePad.sim	
	) else (
		echo 		Building SimplePad
		simple ../../s0.3.302-debug/environment/smake.sim -delete ../../s0.3.302-debug/environment/SimplePad.sim
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
		simple ../../s0.3.302-debug/environment/smake.sim -I/../../simple-arts/environment/simpleprepl.ico -delete ../../s0.3.302-debug/environment/SimpleRepl.sim	
	) else (
		echo 		Building SimpleRepl
		simple ../../s0.3.302-debug/environment/smake.sim -delete ../../s0.3.302-debug/environment/SimpleRepl.sim
	)
) else (
	echo 		../../s0.3.302-debug/environment/SimpleRepl.sim cannot be found
	echo 		skipping SimpleRepl
)