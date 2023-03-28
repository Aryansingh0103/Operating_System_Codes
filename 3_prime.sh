#!/bin/bash

for ((i=2; i<=100; i++))
do
  
    is_prime=true
    for ((j=2; j<i; j++))
    do
        if (( i % j == 0 ))
        then
            
            is_prime=false
            break
        fi
    done
    if [ "$is_prime" = true ]
    then
        echo "$i"
    fi
done
