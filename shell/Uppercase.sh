#!/bin/bash

read -p "Enter folder path: " folder_path

# Check if the folder path exists
if [ -d "$folder_path" ]; then
    # Traverse the folder and convert filenames to uppercase if they contain bsse13
    find "$folder_path" -type f -name "*bsse13*" -exec sh -c 'mv "$1" "$(dirname "$1")/$(basename "$1" | tr "a-z" "A-Z")"' _ {} \;
    echo "Conversion complete."
else
    echo "Error: Folder path does not exist."
fi

