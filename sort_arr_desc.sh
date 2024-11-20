#!/bin/bash

# Function to sort the array in descending order
sort_descending() {
    local arr=("$@")
    local n=${#arr[@]}

    # Bubble sort algorithm for descending order
    for ((i = 0; i < n-1; i++)); do
        for ((j = 0; j < n-i-1; j++)); do
            if ((arr[j] < arr[j+1])); then
                # Swap elements
                temp=${arr[j]}
                arr[j]=${arr[j+1]}
                arr[j+1]=$temp
            fi
        done
    done

    echo "${arr[@]}"
}

# Input: Read the array elements
echo "Enter the number of elements:"
read n
echo "Enter the elements separated by spaces:"
read -a array

# Call the function and print the sorted array
echo "Array in descending order:"
sorted_array=$(sort_descending "${array[@]}")
echo $sorted_array
