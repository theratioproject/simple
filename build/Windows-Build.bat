echo off
cls 

SET EXEC_TYPE="install"
SET VER="0.3.34"

for %%x in (%*) do (
	if %%x=="--install" (
		SET EXEC_TYPE="install"
	) 
	if %%x=="-i" (
		SET EXEC_TYPE="install"
	)
	if %%x=="--uninstall" (
		echo.going to execute myDosFunc
call:myDosFunc
echo.returned from myDosFunc
	) 
	if %%x=="-u" (
		echo yea it reached
		call:uninstall
		SET EXEC_TYPE="uninstall"
	)
)


:: Functions

:install
	echo Installation Type : %EXEC_TYPE%
	exit /b 0

:uninstall
	echo myDosFunc
	exit /b 0
