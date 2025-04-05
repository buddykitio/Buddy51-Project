@echo off
setlocal enabledelayedexpansion

rem Define libraries to use
set USE=

rem Available libraries: Delay LCD4 I2C EEPROM DS1307 SPI LED_7SEGMENT KEYPAD4X4 UART

rem Create necessary folders if they don't exist
if not exist object mkdir object
if not exist release mkdir release

rem Remove old files
del /Q object\*.rel 2>nul
del /Q object\*.ihx 2>nul
del /Q release\*.hex 2>nul
del /Q object\errors.log 2>nul

rem Step 1: Compile each .c file in src folder into .rel files
set C_COUNT=0
set REL_COUNT=0

for %%f in (src\*.c) do (
    echo Compiling: %%f
    set /A C_COUNT+=1
    sdcc -c -mmcs51 --model-small --no-c-code-in-asm --disable-warning 196 "%%f" -o object\ 2>>object\errors.log
)

rem Step 2: Compile libraries specified in USE
for %%L in (%USE%) do (
    if exist .\library\%%L ( 
        if exist .\library\%%L\%%L.c (
            echo Compiling Library: .\library\%%L\%%L.c
            set /A C_COUNT+=1
           sdcc -c -mmcs51 --model-small --no-c-code-in-asm --disable-warning 196 ".\library\%%L\%%L.c" -o object\ 2>>object\errors.log
        ) else (
            echo WARNING: %%L\%%L.c not found, skipping...
        )
    ) else (
        echo WARNING: Library folder %%L not found, skipping...
    )
)

rem Step 3: Check if all .rel files were created
for %%f in (object\*.rel) do (
    set /A REL_COUNT+=1
)

if %C_COUNT% NEQ %REL_COUNT% (
    echo:
    echo ERROR: Compilation failed!
    echo ================================
    type object\errors.log
    echo:
    exit /b 1
)

rem Step 4: Collect all .rel files and link
set REL_FILES=
for %%f in (object\*.rel) do (
    set REL_FILES=!REL_FILES! %%f
)

sdcc !REL_FILES! -o object\output.ihx
if %errorlevel% neq 0 (
    echo ERROR: Linking failed!
    exit /b 1
)

rem Step 5: Convert IHX to HEX
packihx object\output.ihx > release\output.hex
if %errorlevel% neq 0 (
    echo ERROR: HEX conversion failed!
    exit /b 1
)

echo Build completed. HEX file saved in release\output.hex
