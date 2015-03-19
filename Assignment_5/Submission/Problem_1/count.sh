#!/bin/bash
#
# Outputs a counting of numbers between the two input argum#ents
# The second argument is assumed to be greater than the fir#st.
#
for (( i=$1; i<=$2; i++));
do
    echo $i
done
