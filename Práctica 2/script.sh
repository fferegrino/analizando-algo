#!/bin/bash
#clear
echo Pruebas iniciadas: $(date) 
echo "algoritmo|forma|numero a buscar|tamaño n|real|encontrado" > resultados/resultados.csv
./a.out 1000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 2000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 4000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 6000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 8000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 10000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 15000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 20000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 25000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 30000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 35000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 40000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 45000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 50000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 75000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 100000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 125000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 150000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 175000 < entradas/200000numeros.txt >> resultados/resultados.csv
./a.out 200000 < entradas/200000numeros.txt >> resultados/resultados.csv
echo Pruebas terminadas: $(date)

