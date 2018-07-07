
call:visualstudio
call:generatelibfromdll %1
exit /b 0

:generatelibfromdll
	if !THERE_IS_VS!=="true" (
		call:locatevisualstudio !BUILD_ARC!
		dumpbin /EXPORTS %1 > %1.txt
		findstr %2 %1.txt > %1.2.txt
		findstr %3 %1.2.txt > %1.3.txt
	)
	exit /b 0