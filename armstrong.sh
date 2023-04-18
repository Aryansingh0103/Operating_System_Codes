     is_armstrong() {
    n=$1
    sum=0
    num_digits=${#n}
    for ((i = 0; i < num_digits; i++)); do
        digit=${n:i:1}
        sum=$((sum + digit ** num_digits))
    done
    if [ $sum -eq $n ]; then
        echo "$n is an Armstrong number"
    else
        echo "$n is not an Armstrong number"
    fi
}

is_palindrome() {
    n=$1
    reversed=$(echo $n | rev)
    if [ $n -eq $reversed ]; then
        echo "$n is a palindrome"
    else
        echo "$n is not a palindrome"
    fi
}

reverse_and_print() {

    n=$1
    reversed=$(echo $n | rev)
    while [ $reversed -gt 0 ]; do
        digit=$((reversed % 10))
        case $digit in
        0) echo -n "zero " ;;
        1) echo -n "one " ;;
        2) echo -n "two " ;;
        3) echo -n "three " ;;
        4) echo -n "four " ;;
        5) echo -n "five " ;;
        6) echo -n "six " ;;
        7) echo -n "seven " ;;
        8) echo -n "eight " ;;
        9) echo -n "nine " ;;
        esac
        reversed=$((reversed / 10))
    done
    echo
}

echo "Enter an integer to do the following tasks:"
echo "1. Check if it is an Armstrong number"
echo "2. Check if it is a palindrome"
echo "3. Reverse the number and print it in words"
read choice

echo "Enter the number of your choice:"
read number

case $choice in
1) is_armstrong $number ;;
2) is_palindrome $number ;;
3) reverse_and_print $number ;;
*) echo "Invalid choice" ;;
esac
