#!/bin/bash

i=0
coords=()
art=()
t=${1:-0.01}

while read -r line
do
    art+=("$line")
  	if [ ${line:$i:1} != " " ]
  	then
      for j in $(seq 0 $((${#line}-1)) )
      do
          coords+=("$i $j")
      done
    fi
    ((i++))
done
coords="$(echo -n "$coords" | shuf)"

tput clear
echo -n "$art" |
for idx in $(shuf -i 0-$((${#coords[@]}-1)) )
do
    x=$(echo -n ${coords[$idx]} | cut -f 1 -d " ")
    y=$(echo -n ${coords[$idx]} | cut -f 2 -d " ")
    tput cup $x $y
    echo -n "${art[$x]:$y:1}"
    sleep $t

done
tput cup "$(tput lines)" 0
echo -n


