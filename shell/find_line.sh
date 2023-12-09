#!/bin/bash

#read -p "Enter file path: " file_path

# Check if the file exists
#if [ -f "$file_path" ]; then
    # Use grep to find lines starting with bsse13
 #   grep "^bsse13" "$file_path"
#else
 #   echo "Error: File does not exist."
#fi

read -p "Enter file path: " file_path

# Check if the file exists
if [ -f "$file_path" ]; then
    # Use grep to find lines starting with bsse13
    grep "^bsse13" "$file_path" | while IFS= read -r line; do
        # Count the number of words in the line
        word_count=$(echo "$line" | wc -w)

        # Count the number of characters in the line
        char_count=$(echo "$line" | wc -c)

        # Print the line, word count, and character count
        echo "Line: $line"
        echo "Word Count: $word_count"
        echo "Character Count: $char_count"
        echo "---"
    done
else
    echo "Error: File does not exist."
fi


