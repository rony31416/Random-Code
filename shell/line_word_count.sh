# #!/bin/bash

# # Get file path from user
# echo "Enter the file path:"
# read filepath

# # Create a text file with user-specified strings
# echo "Enter the strings for the text file (Ctrl+D to end input):"
# cat > "$filepath" 

# # Count lines and words in the text file
# line_count=$(wc -l < "$filepath")
# word_count=$(wc -w < "$filepath")

# # Display the results
# echo "Number of lines in the text file: $line_count"
# echo "Number of words in the text file: $word_count"
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

# Read strings from the input file and create a text file
echo "Creating text file from input..."
cat "$input_filepath" > "output.txt"

# Count lines and words in the text file
line_count=$(wc -l < "output.txt")
word_count=$(wc -w < "output.txt")

# Display the results
echo "Number of lines in the text file: $line_count"
echo "Number of words in the text file: $word_count"

# Store the results in the output file
echo "Results:" > "$output_filepath"
echo "Number of lines in the text file: $line_count" >> "$output_filepath"
echo "Number of words in the text file: $word_count" >> "$output_filepath"

echo "Results have been saved to $output_filepath"
