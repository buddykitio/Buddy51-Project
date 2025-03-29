#!/bin/bash

# Enable strict mode
set -e  # Exit on error
set -u  # Treat unset variables as errors

# Detect OS (MacOS vs. Linux)
OS_TYPE="$(uname)"
if [[ "$OS_TYPE" == "Darwin" ]]; then
    # MacOS uses BSD utilities, needs GNU versions for some commands
    FIND_CMD="find"
    LS_CMD="ls"
else
    # Linux (Ubuntu, Fedora, etc.)
    FIND_CMD="find"
    LS_CMD="ls --color=auto"
fi

# Create necessary folders if they don't exist
mkdir -p object release

# Remove old files
rm -f object/*.rel object/*.ihx release/*.hex errors.log

# Step 1: Compile each .c file into .rel (object) files
C_COUNT=0
REL_COUNT=0

for file in src/*.c; do
    if [[ -f "$file" ]]; then
        ((C_COUNT++))
        sdcc -c -mmcs51 --model-small --no-c-code-in-asm --disable-warning 196 "$file" -o object/ 2>>errors.log || true
    fi
done

# Step 2: Check if all .rel files were created
for file in object/*.rel; do
    if [[ -f "$file" ]]; then
        ((REL_COUNT++))
    fi
done

if [[ $C_COUNT -ne $REL_COUNT ]]; then
    echo "ERROR: Some .rel files are missing! Compilation failed."
    exit 1
fi

# Step 3: Collect all .rel files and link
REL_FILES=$($FIND_CMD object -name "*.rel" -print)
if [[ -z "$REL_FILES" ]]; then
    echo "ERROR: No object files (*.rel) found! Linking failed."
    exit 1
fi

sdcc $REL_FILES -o object/output.ihx
if [[ $? -ne 0 ]]; then
    echo "ERROR: Linking failed!"
    exit 1
fi

# Step 4: Convert IHX to HEX
packihx object/output.ihx > release/output.hex
if [[ $? -ne 0 ]]; then
    echo "ERROR: HEX conversion failed!"
    exit 1
fi

echo "Build completed successfully. HEX file saved in release/output.hex"
