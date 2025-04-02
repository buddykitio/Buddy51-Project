#!/bin/bash

# Enable strict mode
set -e  # Exit on error
set -u  # Treat unset variables as errors

# Define libraries to use
USE=(Delay LCD4 I2C EEPROM DS1307)

# availble libraries: Delay LCD4 I2C EEPROM DS1307 SPI
# Create necessary folders if they don't exist
mkdir -p object release

# Remove old files
rm -f object/*.rel object/*.ihx release/*.hex object/errors.log

# Step 1: Compile each .c file in src folder into .rel files
C_COUNT=0
REL_COUNT=0

for file in src/*.c; do
    if [[ -f "$file" ]]; then
        echo "Compiling: $file"
        ((C_COUNT++))
        sdcc -c -mmcs51 --model-small --no-c-code-in-asm --disable-warning 196 "$file" -o object/ 2>>object/errors.log || true
    fi
done

# Step 2: Compile libraries specified in USE
for LIB in "${USE[@]}"; do
    if [[ -d "library/$LIB" ]]; then
        if [[ -f "library/$LIB/$LIB.c" ]]; then
            echo "Compiling Library: library/$LIB/$LIB.c"
            ((C_COUNT++))
            sdcc -c -mmcs51 --model-small --no-c-code-in-asm --disable-warning 196 "library/$LIB/$LIB.c" -o object/ 2>>object/errors.log || true
        else
            echo "WARNING: library/$LIB/$LIB.c not found, skipping..."
        fi
    else
        echo "WARNING: Library folder $LIB not found, skipping..."
    fi
done

# Step 3: Check if all .rel files were created
for file in object/*.rel; do
    if [[ -f "$file" ]]; then
        ((REL_COUNT++))
    fi
done

if [[ $C_COUNT -ne $REL_COUNT ]]; then
    echo -e "\nERROR: Some .rel files are missing! Compilation failed.\n"
    cat object/errors.log
    exit 1
fi

# Step 4: Collect all .rel files and link
REL_FILES=$(find object -name "*.rel" -print)
if [[ -z "$REL_FILES" ]]; then
    echo "ERROR: No object files (*.rel) found! Linking failed."
    exit 1
fi

sdcc $REL_FILES -o object/output.ihx
if [[ $? -ne 0 ]]; then
    echo "ERROR: Linking failed!"
    exit 1
fi

# Step 5: Convert IHX to HEX
packihx object/output.ihx > release/output.hex
if [[ $? -ne 0 ]]; then
    echo "ERROR: HEX conversion failed!"
    exit 1
fi

echo "Build completed successfully. HEX file saved in release/output.hex"