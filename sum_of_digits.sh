#!/bin/bash

# Function to calculate the sum of digits
sum_of_digits() {
    local number=$1
    local sum=0
    local digit=0

    while [ $number -gt 0 ]; do
        digit=$((number % 10))  # Extract the last digit
        sum=$((sum + digit))   # Add the digit to the sum
        number=$((number / 10))  # Remove the last digit
    done

    echo $sum
}

# Input: Read the number
echo "Enter a number:"
read number

# Validate input to ensure it is a positive integer
if ! [[ $number =~ ^[0-9]+$ ]]; then
    echo "Please enter a valid positive integer."
    exit 1
fi

# Call the function and display the result
result=$(sum_of_digits $number)
echo "The sum of the digits of $number is: $result"
