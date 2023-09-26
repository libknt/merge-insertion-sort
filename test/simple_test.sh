#!/bin/bash

MIN=1
MAX=100
INCREMENT=10

for ((i=$MIN; i<=$MAX; i+=INCREMENT)); do
    echo "count [100] length[$i] number[$i]"
    sleep 1
    
    OUTPUT=$(bash test.sh -c 100 -l $i -n $i)
    echo -e $OUTPUT
    if echo "$OUTPUT" | grep -q "all test complete"; then
        echo "Proceeding to the next iteration..."
    else
        echo "incompleted work"
        break
    fi
done

echo finally
echo "count [1] length[2147483647] number[777777]"
sleep 1
bash test.sh -c 1 -l 2147483647 -n 777777
