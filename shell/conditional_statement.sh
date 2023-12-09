#!/bin/bash

# Example variables
string1="hello"
string2="world"

# Numeric variables
num1=10
num2=20

# Comparison operators for numbers:
# -eq: Equal to
# -ne: Not equal to
# -lt: Less than
# -le: Less than or equal to
# -gt: Greater than
# -ge: Greater than or equal to

# String comparison operators:
# = : Equal to
# != : Not equal to
# < : Less than (in lexicographical order)
# > : Greater than (in lexicographical order)

if [ "$string1" = "$string2" ]; then
    echo "Strings are equal"
elif [ "$string1" \< "$string2" ]; then
    echo "$string1 is less than $string2"
else
    echo "$string1 is greater than $string2"
fi

if [ "$num1" -eq "$num2" ]; then
    echo "$num1 is equal to $num2"
elif [ "$num1" -lt "$num2" ]; then
    echo "$num1 is less than $num2"
else
    echo "$num1 is greater than $num2"
fi
