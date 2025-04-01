@echo off
echo Cleaning build files...

rem Delete object and release directories if they exist
if exist object rmdir /S /Q object
if exist release rmdir /S /Q release

echo Cleanup completed!
exit /b 0
