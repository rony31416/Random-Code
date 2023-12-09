#!/bin/bash

# Example array
fruits=("Apple" "Banana" "Orange" "Grapes" "Mango")

# For loop to iterate over the array
echo "Printing fruits using a for loop:"
for fruit in "${fruits[@]}"; do
    echo $fruit
done

# While loop to count from 1 to 5
echo "Counting from 1 to 5 using a while loop:"
counter=1
while [ $counter -le 5 ]; do
    echo $counter
    ((counter++))
done
