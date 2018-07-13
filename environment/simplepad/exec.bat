
SET type=%1
SET simplepath=%2
SET filepath=%3

REM to pass simple path only 

if %type%==1 (
	cls
	start cmd /C %simplepath% %filepath%
) else if %type%==2 (
	cls
	start cmd /k %simplepath% %filepath%
) else (
	cls
	echo Building Executable Program
	if exist "./smake.exe" (
		start cmd /k smake.exe %filepath%
	) else (
		echo Simple Make program is not present
	)
)