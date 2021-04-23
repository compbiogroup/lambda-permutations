#!/bin/bash

for i in {1..20}
do
  let "lambda=($i*5)"
  echo "lambda = $lambda..."
  ./exec_novo lambda-permutations/ 100 10 100 $lambda 5 $lambda output/extra t 
done
wait

for i in {1..20}
do
  let "lambda=($i*5)"
  echo "lambda = $lambda..."
  ./exec_novo lambda-permutations/ 100 10 100 $lambda 5 $lambda output/extra rt_uns
done
wait

for i in {1..20}
do
  let "lambda=($i*5)"
  echo "lambda = $lambda..."
  ./exec_novo lambda-permutations/ 100 10 100 $lambda 5 $lambda output/extra r_uns
done
wait
