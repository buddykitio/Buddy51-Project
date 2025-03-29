#!/bin/bash

echo "Cleaning build files..."

# Remove object and release directories if they exist
rm -rf object release

# Remove errors log
rm -f errors.log

echo "Cleanup completed!"
exit 0
