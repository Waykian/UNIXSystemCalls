#!/bin/bash
if [ $# -ne 1 ]; then echo Sintassi errata; exit; fi
echo Inserisci il nome assoluto di un file
read F
if [ -f $F -a -r $F ]
then echo Il file esiste ed è leggibile
else echo Il file non esiste o non è leggibile; exit
fi
cd
touch result_$USER.out
grep -i "$1" $F | sort -r > result_$USER.out
