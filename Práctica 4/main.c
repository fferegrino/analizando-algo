/* 
 * File:   main.c
 * Author: fferegrino
 *
 * Created on 23 de octubre de 2013, 03:26 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include "frecuencias.h"
#include "codificacion.h"
#include "bits.h"

void imprimeTablaFrecuencias(Frecuencia * frecuencias, int length,const char ruta[]);

// Definimos el tamaño del buffer
#define BUFFER 1024 
// Usada para almacenar temporalmente los valores del archivo
char buffer[BUFFER];
// Nuestras variables para los archivos
FILE * entrada;
FILE * tablaFrecuenciasArchivo;
FILE * out;

/*
 * 
 */
int main(int argc, char** argv) {
	// Salida
	char * salida;
    int leidos;
	long leidosTotal = 0;
	int bitsEscritosReal = 0;
	Frecuencia * v;
	
	if(argv[1][0] == '-' && argv[1][1] == 'd') // Decompresión
	{
		// Apertura del archivo
		tablaFrecuenciasArchivo = fopen(argv[2],"r");
		// Variables necesarias
		char caracter;
		int apariciones;
		int numeroCaracteres;
		// Leemos la cantidad de caracteres
		fscanf(tablaFrecuenciasArchivo,"N:%d",&numeroCaracteres);
		// Reservamos el espacio para el arreglo de frecuencias
		v = (Frecuencia *)malloc(sizeof(Frecuencia) * numeroCaracteres);
		// Lectura del archivo de la tabla de frecuencias para generar un arreglo
		for(leidos = 0; leidos < numeroCaracteres; leidos++){
			fscanf(tablaFrecuenciasArchivo,"%c"); // Salto de línea
			fscanf(tablaFrecuenciasArchivo,"%c|%d",&caracter,&apariciones);
			Frecuencia f;
			f.caracter = caracter;
			f.apariciones = apariciones;
			v[leidos] = f;
		}
		// Ordenamos el arreglo por las apariciones
		ordenaFrecuenciasPorAparicion(v, numeroCaracteres);
		// TODO: Seguir con la decodificación xD
	}
	else // Compresión
	{
		ListaFrecuencia f;
		f.inicio = NULL;
		entrada = fopen(argv[1], "rb");
		if (entrada == NULL) {
			perror("No se puede abrir el fichero de entrada");
			return -1;
		}
		
		// Este primer ciclo se encarga de la lectura para generar el árbol
		do {
			// Leemos el archivo hasta que ya no haya que leer
			// fread nos devuelve la cantidad de datos leídos
			leidos = fread(buffer, sizeof(char), BUFFER, entrada);
			leidosTotal += leidos;
			// Insertamos las frecuencias en nuestra tabla
			generaFrecuencias(&f,buffer,leidos);
			// Cuando no se hayan ocupado todos los espacios en la lectura
			// sabemos que ya se terminó de leer el archivo
		}while(leidos == BUFFER);
		
		// Reservamos memoria suficiente para almacenar el archivo codificado
		salida = (char *)malloc(sizeof(char) * leidosTotal);
		// Obtenemos el arreglo de frecuencias
		v = vectorFrecuencias(&f);
		// Generamos la codificación mediante la llamada a este método
		creaArbolCodificacion(v,f.length);
		// Imprimimos la tabla de frecuencias a un archivo para conservarla
		imprimeTablaFrecuencias(v,f.length,argv[3]);
		
		
		// Regresamos al inicio del archivo
		leidos = 0;
		rewind(entrada);
		
		// El segundo ciclo lee el archivo para generar la codificación
		do {
			int iaux = 0;
			// Leemos el archivo hasta que ya no haya que leer
			// fread nos devuelve la cantidad de datos leídos
			leidos = fread(buffer, sizeof(char), BUFFER, entrada);
			// Por cada caracter leído vamos a modificar los bits dentro de este ciclo
			for(iaux = 0; iaux < leidos; iaux++){
				bitsEscritosReal += escribeBits(salida,leidosTotal*8,bitsEscritosReal, buffer[iaux], v, f.length);
			}
			// Cuando no se hayan ocupado todos los espacios en la lectura
			// sabemos que ya se terminó de leer el archivo
		}while(leidos == BUFFER);
		
		// Impresión de información relevante de la compresión [Académico]
		printf("%s|%ld|%ld|%s\n",argv[1],leidosTotal*8,bitsEscritosReal, argv[2]);
		
		fclose(entrada); // Cerramos la entrada
		int bytesTotal = (bitsEscritosReal / 8)+1; // Determinamos cuantos bytes ocupará el nuevo archivo
		out = fopen(argv[2],"w"); // Abrimos un flujo de salida para guardar el nuevo archivo
		fwrite(salida,sizeof(char),bytesTotal,out); // Escribimos el arreglo de chars, el cual fue modificado para contener la información
		fclose(out); // Cerramos el flujo
	}
	
    return (EXIT_SUCCESS);
}

/**
 * Función para imprimir la tabla de frecuencias a un archivo especificado
 * @param frecuencias La tabla de frecuencias en el archivo
 * @param ruta La ruta en la que se debe guardar
 */
void imprimeTablaFrecuencias(Frecuencia * frecuencias, int length,const char ruta[]) {
    tablaFrecuenciasArchivo = fopen(ruta,"w");
    if (tablaFrecuenciasArchivo == NULL) {
        perror("No se puede abrir archivo");
    }
	fprintf(tablaFrecuenciasArchivo,"N:%d\n", length);;
	// Impresión de las frecuencias al archivo especificado
	int i;
    for (i = 0; i < length; i++) {
        fprintf(tablaFrecuenciasArchivo,"%c|%d\n"
                , (int) frecuencias[i].caracter
                , frecuencias[i].apariciones
				/*, frecuencias[i].codigo*/);
    }
    fclose(tablaFrecuenciasArchivo);
}

