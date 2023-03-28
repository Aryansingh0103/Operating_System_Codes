#!/bin/bash

# Take the input from the user
read -p "Enter a string: " str

# # Remove any leading and trailing whitespaces
# str=$(echo $str | tr -d '[:space:]')

# # Convert the string to lowercase
# str=$(echo $str | tr '[:upper:]' '[:lower:]')

# Reverse the string
rev=""
len=${#str}
for (( i=len-1; i>=0; i-- )); do
    rev="$rev${str:$i:1}"
done

# Check if the string is a palindrome
if [ "$str" == "$rev" ]; then
    echo "The string is a palindrome."
else
    echo "The string is not a palindrome."
fi
