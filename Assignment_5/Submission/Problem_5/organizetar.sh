#!/bin/bash
#
#
# Unzip original tar file

tar -zxf $1

# Generate list of files

files=$(ls -a)

# Current directory

current=$(pwd)

# Sort through files and place them in correct subfolder

for i in ${files[@]}; do

# Determine file extension

    type="${i##*.}"
# Skip hidden files

    if [[ "$i" =~ ^\. ]]; then
:
# Disregard original zip file
elif [ "$i" == $1 ]; then
:
# Disregard this bash file

elif [ "$i" == "organizetar.sh" ]; then
:
# Move file if directory already exists

elif [ -d "$type" ]; then

	$(mv $i $current/$type)
# Create directory and move file if not

elif [ "$type" != "$i" ]; then

	$(mkdir $type)
	$(mv $i "$current"/$type)
# Leave files without extensions
else
:
fi
done
# Extract Original filename
input="$1"; tarext=${input%.*}; name=${tarext%.*};
# Zip folder structure into a new clean tar file
