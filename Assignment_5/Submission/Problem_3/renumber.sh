#!/bin/bash
#
# Renames all the files of the specified file extension wit#hin a directory.
#
name=$1
ext=$2
counter=001
for i in *.$ext;
do
    mv $i $(printf "$name%0.3d.$ext" $counter)
    ((counter+=1))
done
