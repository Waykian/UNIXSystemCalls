#!/bin/bash

if [ $# -lt 3 ]; then echo Sintassi errata; exit; fi
if ! [[ $2 =~ ^-?[0-9]+$ ]]; then echo Il secondo argomento deve essere un numero; exit; fi
STRING=$1
NUM=$2
TOT=0

shift
shift

for dir in $*
do

for FILE in $dir/*
do

if [ -f $FILE ]
then if [ `grep -o $STRING $FILE | wc -w` -eq  $NUM ]
then echo $FILE; TOT=$((TOT+1))
fi
fi

done

done

echo $TOT
