#!/bin/bash
clear
echo Pruebas iniciadas: $(date) 
echo "forma|tamaño imagen|real|user|sys|cpuwall" > salidas/resultados.csv
./a.out entradas/car2048.bmp salidas/car.bmp N >> salidas/resultados.csv
./a.out entradas/monalisa512.bmp salidas/monalisa.bmp N >> salidas/resultados.csv
./a.out entradas/lena1024.bmp salidas/lena.bmp N >> salidas/resultados.csv
./a.out entradas/car2048.bmp salidas/car.bmp C >> salidas/resultados.csv
./a.out entradas/monalisa512.bmp salidas/monalisa.bmp C >> salidas/resultados.csv
./a.out entradas/lena1024.bmp salidas/lena.bmp C >> salidas/resultados.csv
./a.out entradas/car2048.bmp salidas/car.bmp H >> salidas/resultados.csv
./a.out entradas/monalisa512.bmp salidas/monalisa.bmp H >> salidas/resultados.csv
./a.out entradas/lena1024.bmp salidas/lena.bmp H >> salidas/resultados.csv
echo Pruebas terminadas: $(date)

