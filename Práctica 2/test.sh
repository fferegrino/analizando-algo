#!/bin/bash
clear
echo Pruebas iniciadas: $(date) 
echo "Debug:" > resultados/resultados.txt
./a.out 1000 < entradas/200000numeros.txt
./a.out 80000 < entradas/200000numeros.txt 
./a.out 200000 < entradas/200000numeros.txt 
echo Pruebas terminadas: $(date)

