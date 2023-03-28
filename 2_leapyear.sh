#!/bin/bash

#reading input from user
read -p 'Enter year to check leap year: ' year

if [ `expr $year % 400` -eq 0 ] 
then
echo $year is a leap year
elif [ `expr $year % 100` -eq 0 ]
then
echo $year is not leap year
elif [ `expr $year % 4` -eq 0 ]
then
echo $year is a leap year
else
echo $year is not a leap year
fi