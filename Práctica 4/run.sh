#!/bin/bash
clear
echo "accion|archivo entrada|resultado|bytes entrada|bytes salida|archivo salida" > salidas/resultados.csv
# Forma de invocación para codificar
#	./a.out ruta_archivo_a_codificar ruta_archivo_codificado ruta_tabla_de_frecuencias
./a.out /home/fferegrino/Documents/archivos/document.docx /home/fferegrino/Documents/comprimidos/word.comprimido /home/fferegrino/Documents/tablasC/word.txt >> salidas/resultados.csv
./a.out /home/fferegrino/Documents/archivos/document.pdf /home/fferegrino/Documents/comprimidos/pdf.comprimido /home/fferegrino/Documents/tablasC/pdf.txt >> salidas/resultados.csv
./a.out /home/fferegrino/Documents/archivos/img.bmp /home/fferegrino/Documents/comprimidos/bmp.comprimido /home/fferegrino/Documents/tablasC/bmp.txt >> salidas/resultados.csv
./a.out /home/fferegrino/Documents/archivos/sound.mp3 /home/fferegrino/Documents/comprimidos/mp3.comprimido /home/fferegrino/Documents/tablasC/mp3.txt >> salidas/resultados.csv
./a.out /home/fferegrino/Documents/archivos/img.jpg /home/fferegrino/Documents/comprimidos/jpg.comprimido /home/fferegrino/Documents/tablasC/jpg.txt >> salidas/resultados.csv
# Forma de invocación para descodificar
#	./a.out -d ruta_tabla_de_frecuencias ruta_archivo_codificado ruta_de_archvo_descomprimido
./a.out -d /home/fferegrino/Documents/tablasC/word.txt /home/fferegrino/Documents/comprimidos/word.comprimido /home/fferegrino/Documents/descomprimidos/doc.docx >> salidas/resultados.csv
./a.out -d /home/fferegrino/Documents/tablasC/pdf.txt /home/fferegrino/Documents/comprimidos/pdf.comprimido /home/fferegrino/Documents/descomprimidos/doc.pdf >> salidas/resultados.csv
./a.out -d /home/fferegrino/Documents/tablasC/bmp.txt /home/fferegrino/Documents/comprimidos/bmp.comprimido /home/fferegrino/Documents/descomprimidos/img.bmp >> salidas/resultados.csv
./a.out -d /home/fferegrino/Documents/tablasC/mp3.txt /home/fferegrino/Documents/comprimidos/mp3.comprimido /home/fferegrino/Documents/descomprimidos/sou.mp3 >> salidas/resultados.csv
./a.out -d /home/fferegrino/Documents/tablasC/jpg.txt /home/fferegrino/Documents/comprimidos/jpg.comprimido /home/fferegrino/Documents/descomprimidos/im.jpg >> salidas/resultados.csv

