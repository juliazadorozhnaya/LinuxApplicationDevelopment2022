#!/bin/bash

i=0
coords=()
art=()
t=${1:-0.01}

while IFS= read -r line
do
    art+=("$line")
    for j in $(seq 0 $((${#line}-1)) )
    do
        coords+=("$i $j")
    done
    ((i++))
done

coords="$(echo -ne "$coords" | shuf)"

tput clear
echo "$art" |
for idx in $(shuf -i 0-$((${#coords[@]}-1)) )
do
    x=$(echo ${coords[$idx]} | cut -f 1 -d " ")
    y=$(echo ${coords[$idx]} | cut -f 2 -d " ")
    tput cup $x $y
    echo "${art[$x]:$y:1}"
    sleep $t

done
tput cup "$(tput lines)" 0
tr -d '\n'
echo


