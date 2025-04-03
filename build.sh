#!/bin/bash

# Enable strict mode
set -e  # Exit on error
set -u  # Treat unset variables as errors

# Define libraries to use
USE=(Delay LCD4 I2C EEPROM DS1307)

# Available libraries: Delay LCD4 I2C EEPROM DS1307 SPI

# Create necessary folders if they don't exist
mkdir -p object release

# Remove old files (except .rel files for incremental build)
rm -f object/*.ihx release/*.hex object/errors.log

# Step 1: Compile each .c file in src folder into .rel files if updated
C_COUNT=0
REL_COUNT=0

for file in src/*.c; do
    if [[ -f "$file" ]]; then
        rel_file="object/$(basename "${file%.*}").rel"
        ((C_COUNT++))  # Always increment count

        # Check if .rel file exists and if .c file is newer
        if [[ ! -f "$rel_file" || "$file" -nt "$rel_file" ]]; then
            echo "Compiling updated file: $file"
            sdcc -c -mmcs51 --model-small --no-c-code-in-asm --disable-warning 196 "$file" -o object/ 2>>object/errors.log || true
        else
            echo "Skipping unchanged file: $file"
        fi
    fi
done

# Step 2: Compile libraries specified in USE if updated
for LIB in "${USE[@]}"; do
    LIB_SRC="library/$LIB/$LIB.c"
    LIB_REL="object/$LIB.rel"
    
    if [[ -f "$LIB_SRC" ]]; then
        ((C_COUNT++))  # Always increment count

        # Check if .rel file exists and if .c file is newer
        if [[ ! -f "$LIB_REL" || "$LIB_SRC" -nt "$LIB_REL" ]]; then
            echo "Compiling updated library: $LIB_SRC"
            sdcc -c -mmcs51 --model-small --no-c-code-in-asm --disable-warning 196 "$LIB_SRC" -o object/ 2>>object/errors.log || true
        else
            echo "Skipping unchanged library: $LIB_SRC"
        fi
    else
        echo "WARNING: Library file $LIB_SRC not found, skipping..."
    fi
done

# Step 3: Count all .rel files
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
