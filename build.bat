@echo off
setlocal enabledelayedexpansion

rem Define libraries to use
set USE=Delay LCD4 I2C EEPROM DS1307

rem Available libraries: Delay LCD4 I2C EEPROM DS1307 SPI LED_7SEGMENT KEYPAD4X4

rem Create necessary folders if they don't exist
if not exist object mkdir object
if not exist release mkdir release

rem Remove old files
del /Q object\*.ihx 2>nul
del /Q release\*.hex 2>nul
del /Q object\errors.log 2>nul

rem Step 1: Compile each .c file in src folder into .rel files if updated
set C_COUNT=0
set REL_COUNT=0

for %%f in (src\*.c) do (
    set "rel_file=object\%%~nf.rel"
    set /A C_COUNT+=1

    echo Compiling: %%f
    sdcc -c -mmcs51 --model-small --no-c-code-in-asm --disable-warning 196 "%%f" -o object\ 2>>object\errors.log
)

rem Step 2: Compile libraries specified in USE if updated
for %%L in (%USE%) do (
    if exist .\library\%%L\%%L.c (
        set "rel_file=object\%%L.rel"
        set /A C_COUNT+=1

        if not exist "!rel_file!" (
            echo Compiling library: .\library\%%L\%%L.c
            sdcc -c -mmcs51 --model-small --no-c-code-in-asm --disable-warning 196 ".\library\%%L\%%L.c" -o object\ 2>>object\errors.log
        ) else (
            for /F "delims=" %%T in ('forfiles /P "library\%%L" /M "%%L.c" /C "cmd /c echo @ftime"') do set "SRC_TIME=%%T"
            for /F "delims=" %%T in ('forfiles /P "object" /M "%%L.rel" /C "cmd /c echo @ftime"') do set "REL_TIME=%%T"

            if !SRC_TIME! GTR !REL_TIME! (
                echo Recompiling updated library: .\library\%%L\%%L.c
                sdcc -c -mmcs51 --model-small --no-c-code-in-asm --disable-warning 196 ".\library\%%L\%%L.c" -o object\ 2>>object\errors.log
            ) else (
                echo Skipping unchanged library: .\library\%%L\%%L.c
            )
        )
    ) else (
        echo WARNING: Library file .\library\%%L\%%L.c not found, skipping...
    )
)

rem Step 3: Count all .rel files
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
