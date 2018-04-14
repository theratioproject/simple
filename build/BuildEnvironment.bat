REM Confirm smake is present
if exist "../../s0.3.302-debug/environment/simplepad/SimplePad.sim" (
	echo 		Building SimplePad
	
) else (
	echo 		smake.sim cannot be found
	echo 		no smake no build bye
)


REM Builing SimplePad
echo 		`SimplePad
if exist "../../s0.3.302-debug/environment/simplepad/SimplePad.sim" (
	echo 		Building SimplePad
	
) else (
	echo 		../../s0.3.302-debug/environment/simplepad/SimplePad.sim cannot be found
	echo 		skipping SimplePad
)