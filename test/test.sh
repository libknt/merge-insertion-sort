#!/bin/bash

rm -rf log
mkdir -p log

make -C ..

cp ../PmergeMe ./

chmod +x PmergeMe

count=1
length=2147483647
number=10

FILE_COUNT=11

LOGDIR=./log
LOG=$LOGDIR/sorted.log
TEST_LOG=$LOGDIR/sorted_test.log
TEST_LOG2=$LOGDIR/sorted_test2.log
ERRORLOG=$LOGDIR/error.log

mkdir -p $LOGDIR

while getopts "l:c:n:" opt; do
    case $opt in
    l)
        length=$OPTARG
        ;;
    c)
        count=$OPTARG
        ;;
    n)
        number=$OPTARG
        ;;
    *)
        echo "Usage: $0 [-l length] [-c count] [-n number]"
        exit 1
        ;;
    esac
done

if [ "$number" -gt 14053 ]; then
    number=14053
fi



for ((i=1; i<=count; i++)); do
    # numbers=$(python3 -c "import random; print(' '.join(str(random.randint(1, $length)) for _ in range($number)))")
    numbers=$(python3 -c "import random; print(' '.join(str(i) for i in random.sample(range(1, $length + 1), $number)))")
    echo $numbers
    ./PmergeMe $numbers >> $LOG 2>$ERRORLOG
    sorted_numbers=$(echo "$numbers" | tr ' ' '\n' | sort -n | tr '\n' ' ')
    cat $LOG | grep After > $TEST_LOG 
    echo "After:   "$sorted_numbers >> $TEST_LOG2
    diff $TEST_LOG $TEST_LOG2 > /dev/null
    if [ $? -eq 0 ]; then
    RANDOM_FILE_NUM=$(( RANDOM % FILE_COUNT + 1 ))

    RANDOM_FILE_PATH="./art/${RANDOM_FILE_NUM}.art"
    echo -e "\033[32m"
    cat "$RANDOM_FILE_PATH"
    echo -e "\033[0m"  
    else
    RANDOM_FILE_NUM=$(( RANDOM % FILE_COUNT + 1 ))

    RANDOM_FILE_PATH="./art/${RANDOM_FILE_NUM}.art"
    echo -e "\033[31m"
    cat "$RANDOM_FILE_PATH"
    echo -e "\033[0m"  
        echo "error: " $numbers >> $ERRORLOG
        break
    fi
done


if [ $? -eq 0 ]; then
    echo -e "\033[32m"
    echo "all test complete"
    echo -e "\033[0m"  
fi
