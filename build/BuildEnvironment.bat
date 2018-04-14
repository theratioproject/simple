echo off

	echo `
	echo 	Building Environment Program to Executable 
	
REM Confirm smake is present
if exist "../../s0.3.302-debug/environment/smake.sim" (
	echo 		Smake Found. yea Starting Build..
	simple smake.sim -I/window.ico ../../backup/smake/SimpleRepl.sim
) else (
	echo 		smake.sim cannot be found
	echo 		no smake no build bye
	REM exit 
)


REM Builing SimplePad
echo 		`SimplePad
if exist "../../s0.3.302-debug/environment/SimplePad.sim" (
	echo 		Building SimplePad
	
) else (
	echo 		../../s0.3.302-debug/environment/SimplePad.sim cannot be found
	echo 		skipping SimplePad
)