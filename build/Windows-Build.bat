@echo off

echo.going to execute myDosFunc with different arguments
call:myDosFunc 100 YeePEE
call:myDosFunc 100 "for me"
call:myDosFunc 100,"for me"
call:myDosFunc 100,for me

echo.&pause&goto:eof


::--------------------------------------------------------
::-- Function section starts below here
::--------------------------------------------------------

:myDosFunc    - here starts my function identified by it's label
echo.
echo. here the myDosFunc function is executing a group of commands
echo. it could do %~1 of things %~2.
goto:eof