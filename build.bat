@echo off
setlocal enabledelayedexpansion

rem -------------------------------------------
rem Configuration
set USE=
rem Available libraries: Delay LCD4 I2C EEPROM DS1307 SPI LED_7SEGMENT KEYPAD4X4 UART PCF8591 MPU6050
rem -------------------------------------------

rem Create necessary folders if they don't exist
if not exist object mkdir object
if not exist release mkdir release

rem -------------------------------------------
rem Step 1: Build library.lib ONLY if it doesn't exist
rem -------------------------------------------
if not exist object\library.lib (
    echo Building library.lib...

    for %%L in (%USE%) do (
        if exist .\library\%%L (
            if exist .\library\%%L\%%L.c (
                echo Compiling Library: .\library\%%L\%%L.c
                sdcc -c -mmcs51 --opt-code-size --model-small --nooverlay --no-xinit-opt --code-loc 0x0000 --xram-loc 0 --data-loc 0 --disable-warning 196 ".\library\%%L\%%L.c" -o object\ 2>>object\errors.log
                if !errorlevel! neq 0 (
                    echo:
                    echo ERROR: Compilation failed for library %%L
                    echo ================================
                    type object\errors.log
                    echo:
                    exit /b 1
                )

                for %%r in (object\%%L.rel) do (
                    echo Adding %%r to library.lib
                    sdar -rc object\library.lib %%r
                    del %%r >nul 2>&1
                )
            ) else (
                echo WARNING: %%L.c not found in library %%L
            )
        ) else (
            echo WARNING: Library folder %%L not found
        )
    )
) else (
    echo Skipping library build: object\library.lib already exists.
)

rem Clean temporary files (except library.lib)
del /Q object\*.rel 2>nul
del /Q object\*.lst 2>nul
del /Q object\*.asm 2>nul
del /Q object\*.sym 2>nul
del /Q object\*.rst 2>nul
del /Q object\*.log 2>nul
del /Q object\*.ihx 2>nul
del /Q release\*.hex 2>nul

rem -------------------------------------------
rem Step 2: Compile main source files to .rel
rem -------------------------------------------
set C_COUNT=0
set REL_COUNT=0

for %%f in (src\*.c) do (
    echo Compiling: %%f
    set /A C_COUNT+=1
    sdcc -c -mmcs51 --model-small --opt-code-size --nooverlay --no-xinit-opt --code-loc 0x0000 --xram-loc 0 --data-loc 0 --disable-warning 196 "%%f" -o object\ 2>>object\errors.log
)

rem -------------------------------------------
rem Step 3: Count .rel files and validate
rem -------------------------------------------
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

rem -------------------------------------------
rem Step 4: Link main .rel files with library.lib
rem -------------------------------------------
set REL_FILES=
for %%f in (object\*.rel) do (
    set REL_FILES=!REL_FILES! %%f
)

sdcc --opt-code-size !REL_FILES! object\library.lib -o object\output.ihx
if %errorlevel% neq 0 (
    echo ERROR: Linking failed!
    exit /b 1
)

rem -------------------------------------------
rem Step 5: Convert to HEX
rem -------------------------------------------
packihx object\output.ihx > release\output.hex
if %errorlevel% neq 0 (
    echo ERROR: HEX conversion failed!
    exit /b 1
)

rem -------------------------------------------
rem Step 6: Show final info
rem -------------------------------------------
echo ---------------------------------------------------------
type object\output.mem
echo ---------------------------------------------------------
echo:
echo ✅ Build completed. HEX saved in release\output.hex
