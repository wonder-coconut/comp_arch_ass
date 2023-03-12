#!/bin/bash

make branch_predictor;
counter=1;
rm out;
touch out;
while [ $counter -le 16 ]
do
    echo "-----------------------------------------------------" >> out;
    echo "trace $counter" >> out;
    if [ $counter -le 9 ]
    then
        ./branch_predictor.o $1 ../traces/trace_0"$counter" $2 $3 >> out;
    else
        ./branch_predictor.o $1 ../traces/trace_"$counter" $2 $3 >> out;
    fi
    ((counter++));
done

make clean;