
call:generatelibfromdll
exit /b 0

:generatelibfromdll
	if !THERE_IS_VS!=="true" (
		REM call:header configure "configure build %VERSION%"
		REM call:locatevisualstudio !BUILD_ARC!
		REM dumpbin /EXPORTS %1 > %1.txt
		REM findstr %2 %1.txt > %1.2.txt
		REM findstr %3 %1.2.txt > %1.3.txt
		SET THERE_IS_VS="false"
	)
	exit /b 0