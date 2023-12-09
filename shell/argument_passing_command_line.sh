#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <length> <width>"
    exit 1
fi

# Extract command-line arguments
length=$1
width=$2

# Calculate area and perimeter
area=$(awk "BEGIN {printf \"%.2f\", $length * $width}")
perimeter=$(awk "BEGIN {printf \"%.2f\", 2 * ($length + $width)}")

# Print the results
echo "Rectangle Dimensions:"
echo "Length: $length"
echo "Width: $width"
echo "Area: $area"
echo "Perimeter: $perimeter"



# ./argument_passing_command_line.sh 10 20




