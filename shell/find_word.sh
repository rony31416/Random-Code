#!/bin/bash

# Get file path from user
echo "Enter the file path:"
read filepath

# Check if the file exists
if [ ! -f "$filepath" ]; then
    echo "Error: File does not exist."
    exit 1
fi

# Get string to search for from user
echo "Enter the string to search for:"
read search_string

# Use grep to find the string in the file
result=$(grep "$search_string" "$filepath")

# Display the result
echo "Occurrences of '$search_string' in $filepath:"
echo "$result"
