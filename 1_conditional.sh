#!/bin/bash

# reading data from user
echo For relational operators
read -p 'Enter any integer a: ' a
read -p 'Enter another integer b: ' b

#Relational Operators

if(($a==$b))
then
echo a is equal to b.
else
echo a is not equal to b
fi

read -p 'Enter any integer a: ' a
read -p 'Enter another integer b: ' b
if(($a<$b))
then
echo a is less than b.
else
echo a is not less than b.
fi

read -p 'Enter any integer a: ' a
read -p 'Enter another integer b: ' b
if(($a-ge$b))
then
echo a is greater than or equal to b.
else
echo a is not greater than or equal to b.
fi

echo For logical operators
read -p 'Enter either hi or bye: ' x
read -p 'Enter either hi or bye: ' y

# Logical Operators
if(($x == "hi" || $y == "hi"))
then
echo one of the input is hi
else
echo both of the input is are not hi
fi
