#!/bin/bash

# Prompt user for the first number
echo "Enter the first number:"
read num1

# Prompt user for the second number
echo "Enter the second number:"
read num2

# Perform arithmetic operations
sum=$((num1 + num2))
difference=$((num1 - num2))
product=$((num1 * num2))

# Check if the second number is not zero before performing division
#awk: This is a powerful text processing tool in Unix and Linux systems. In this context, it is used to perform arithmetic operations.
if [ $num2 -ne 0 ]; then
    division=$(awk "BEGIN {printf \"%.2f\", $num1 / $num2}")
else
    division="Cannot divide by zero"
fi

# Print the results
echo "Sum: $sum"
echo "Difference: $difference"
echo "Product: $product"
echo "Division: $division"
