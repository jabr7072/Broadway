#!/bin/bash

gradestring=$(cut -d';' -f 2 $1)

echo $gradestring
grades=(${gradestring// / })



total=0

for i in "${!grades[@]}"
do
    let total+=${grades[i]}
done

length=${#grades[@]}

finalgrade=$(bc <<< "scale=3;$total/$length" )
echo " Final grade is $finalgrade"


