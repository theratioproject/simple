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
		call:uninstall
	) 
	if %%x=="-u" (
		call:uninstall
	)
)

exit /b %ERRORLEVEL%

:: Functions

:install
	echo Installation Type : %EXEC_TYPE%
	exit /b 0

:uninstall
	echo unintstalling
	exit /b 0
