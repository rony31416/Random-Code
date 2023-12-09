#!/bin/bash

# Get input file path and output file path from user
echo "Enter the input file path:"
read input_filepath

echo "Enter the output file path:"
read output_filepath

# Check if the input file exists
if [ ! -f "$input_filepath" ]; then
    echo "Error: Input file does not exist."
    exit 1
fi

# Convert text to uppercase and store in the output file
tr '[:lower:]' '[:upper:]' < "$input_filepath" > "$output_filepath"

echo "Text has been converted to uppercase and saved to $output_filepath"
