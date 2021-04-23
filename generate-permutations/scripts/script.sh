#!/bin/bash
echo "Unsigned permutations"
for i in $(seq 10 5 100)
do
  echo "running n = $i"
  ./gen_uns -n $i -q 1000 > ~/Dropbox/mestrado/pesquisa/instances/uns/n_$i.in
done
