#!/bin/bash

# Example file path
file_path="example.txt"

# File test operators:
# -e: Check if file exists
# -f: Check if file is a regular file
# -d: Check if file is a directory
# -r: Check if file is readable
# -w: Check if file is writable
# -x: Check if file is executable

# Check if the file exists
if [ -e "$file_path" ]; then
    echo "File $file_path exists"
else
    echo "File $file_path does not exist"
fi

# Check if the file is a regular file
if [ -f "$file_path" ]; then
    echo "File $file_path is a regular file"
else
    echo "File $file_path is not a regular file"
fi

# Check if the file is a directory
if [ -d "$file_path" ]; then
    echo "File $file_path is a directory"
else
    echo "File $file_path is not a directory"
fi

# Check if the file is readable
if [ -r "$file_path" ]; then
    echo "File $file_path is readable"
else
    echo "File $file_path is not readable"
fi

# Check if the file is writable
if [ -w "$file_path" ]; then
    echo "File $file_path is writable"
else
    echo "File $file_path is not writable"
fi

# Check if the file is executable
if [ -x "$file_path" ]; then
    echo "File $file_path is executable"
else
    echo "File $file_path is not executable"
fi
