@echo off
setlocal enabledelayedexpansion

rem Create necessary folders if they don't exist
if not exist object mkdir object
if not exist release mkdir release

rem Remove old files
del /Q object\*.rel 2>nul
del /Q object\*.ihx 2>nul
del /Q release\*.hex 2>nul
del /Q errors.log 2>nul

rem Step 1: Compile each .c file into .rel (object) files
set C_COUNT=0
set REL_COUNT=0

for %%f in (src\*.c) do (
    set /A C_COUNT+=1
    sdcc -c -mmcs51 --model-small --no-c-code-in-asm --disable-warning 196 "%%f" -o object\ 2>>errors.log
)

rem Step 2: Check if all .rel files were created
for %%f in (object\*.rel) do (
    set /A REL_COUNT+=1
)

if %C_COUNT% NEQ %REL_COUNT% (
    echo ERROR: Some .rel files are missing! Compilation failed.
    exit /b 1
)

rem Step 3: Collect all .rel files and link
set REL_FILES=
for %%f in (object\*.rel) do (
    set REL_FILES=!REL_FILES! %%f
)

sdcc !REL_FILES! -o object\output.ihx
if %errorlevel% neq 0 (
    echo ERROR: Linking failed!
    exit /b 1
)

rem Step 4: Convert IHX to HEX
packihx object\output.ihx > release\output.hex
if %errorlevel% neq 0 (
    echo ERROR: HEX conversion failed!
    exit /b 1
)

echo Build completed. HEX file saved in release\output.hex
