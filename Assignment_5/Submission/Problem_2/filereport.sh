#!/bin/bash


fileprop=($(ls -l $1 | head -c 4 */))

echo $fileprop

