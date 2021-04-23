#!/bin/bash
echo "Generating signed Lambda Permutations"
for n in $(seq 10 10 100)
do
  for i in $(seq 5 5 $n)
  do
    echo "running n = $n lambda = $i"
    mkdir -p ~/pesquisa/instances/lambda-permutations/signed/n$n-1000
    ../bin/./gen-lp 1 $n $i 1000 0 > ~/pesquisa/instances/lambda-permutations/signed/n$n-1000/lamb$i-n$n-1000.lp
  done
done
