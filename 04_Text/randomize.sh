#!/bin/bash

i=0
coords=()
art=()
DELAY=${1:-0.01}

while IFS= read -r line
do
    art+=("$line")
  	if [ ${line:$i:1} != " " ]
  	then
      for j in $(seq 0 $((${#line}-1)) )
      do
          coords+=("$i $j")
      done
    else
      for j in $(seq 0 $((${#line}-1)) )
      do
          coords+=("$i $j")
      done
    fi
    ((i++))
done

coords="$(echo -ne "$coords" | shuf)"

tput clear
echo -n "$art" |
for idx in $(shuf -i 0-$((${#coords[@]}-1)) )
do
    x=$(echo ${coords[$idx]} | cut -f 1 -d " ")
    y=$(echo ${coords[$idx]} | cut -f 2 -d " ")
    tput cup $x $y
    echo "${art[$x]:$y:1}"
    sleep $DELAY

done
tput cup "$(tput lines)" 0
echo -n

