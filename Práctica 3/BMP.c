/* 
 * File:        BMP.h
 * Author:      Antonio Feregrino Bolanos
 * Version:     1.0
 * Descripción: Librería para el tratamiento de imágenes BMP de 24 bits
 * 
 * Conversion a libreria de BMP.c (C) Marzo 2013 Versión 1.5, de Edgardo Adrián Franco, 
 * disponible en http://www.eafranco.com/docencia/analisisdealgoritmos/files/practicas/03/BMP24BitsEnC.zip
 * 
 * Created on October 3, 2013, 10:33 PM
 */

/* 
 * Librerías necesarias para la compilación
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BMP.h"

//
// Prototipos de funciones no expuestas en la cabecera
//
void traslacion(int i, int j, int i1, int j1, BMP * imagen, int n);
void traslacionM(int i, int j, int i1, int j1, unsigned char ** matriz, int n);
void rotacionBase(int i, int j, int i1, int j1, BMP * imagen, int n);
void rotacionBaseM(int i, int j, int i1, int j1, unsigned char ** matriz, int n);

/**
 * Función propia de la ejecución con hilos
 */
void ejecutaRotacion(void * imagen);

//
// Estructuras auxiliares para la ejecucion con hilos
//
typedef struct bmpAux
{
	int i;		   // Inicio del rango de pixeles a tratar	
	int j;		   // Inicio del rango de pixeles a tratar
	int i1;		   // Final del rango de pixeles a tratar
	int j1;		   // Final del rango de pixeles a tratar	
	int n;		   // Tamaño del problema
	BMP * imagen;  // Apuntador a imagen
}BMPAux;


//
// Implementación de las funciones
//

/**
 * Función encargada de abrir una imagen a partir de una ruta especificada
 * @param imagen La estructura en la que residirá la información de la imagen abierta
 * @param ruta La ruta en la que se encuentra la imagen que deseamos abrir
 */
void abrirImagen(BMP* imagen, char* ruta) {
    FILE *archivo; //Puntero FILE para el archivo de imágen a abrir
    int i, j, k, resto;
    unsigned char R, B, G, var;

    //Abrir el archivo de imágen
    archivo = fopen(ruta, "rb+");
    if (!archivo) {
        //Si la imágen no se encuentra en la ruta dada
        printf("La imágen %s no se encontro\n", ruta);
        exit(1);
    }

    //Leer la cabecera de la imagen y almacenarla en la estructura global img
    fseek(archivo, 0, SEEK_SET);
    fread(&imagen->bm, sizeof (char), 2, archivo);
    fread(&imagen->tamano, sizeof (int), 1, archivo);
    fread(&imagen->reservado, sizeof (int), 1, archivo);
    fread(&imagen->offset, sizeof (int), 1, archivo);
    fread(&imagen->tamanoMetadatos, sizeof (int), 1, archivo);
    fread(&imagen->alto, sizeof (int), 1, archivo);
    fread(&imagen->ancho, sizeof (int), 1, archivo);
    fread(&imagen->numeroPlanos, sizeof (short int), 1, archivo);
    fread(&imagen->profundidadColor, sizeof (short int), 1, archivo);
    fread(&imagen->tipoCompresion, sizeof (int), 1, archivo);
    fread(&imagen->tamanoEstructura, sizeof (int), 1, archivo);
    fread(&imagen->pxmh, sizeof (int), 1, archivo);
    fread(&imagen->pxmv, sizeof (int), 1, archivo);
    fread(&imagen->coloresUsados, sizeof (int), 1, archivo);
    fread(&imagen->coloresImportantes, sizeof (int), 1, archivo);

    //Validar ciertos datos de la cabecera de la imágen	
    if (imagen->bm[0] != 'B' || imagen->bm[1] != 'M') {
        printf("La imagen debe ser un bitmap.\n");
        exit(1);
    }
    if (imagen->profundidadColor != 24) {
        printf("La imagen debe ser de 24 bits.\n");
        exit(1);
    }

    //*********************************************************************************************************
    //Colocar el cursor en el byte (offset) donde comienzan los datos de la imagen
    //*********************************************************************************************************
    fseek(archivo, imagen->offset, SEEK_SET);

    //*********************************************************************************************************
    //Reservar memoria para el arreglo que tendra los planos RGB de la imagen (Arreglo de tamaño "img.ancho X img.alto")
    //*********************************************************************************************************
    imagen->pixelR = malloc(imagen->alto * sizeof (char *));
    imagen->pixelG = malloc(imagen->alto * sizeof (char *));
    imagen->pixelB = malloc(imagen->alto * sizeof (char *));
    for (i = 0; i < imagen->alto; i++) {
        imagen->pixelR[i] = malloc(imagen->ancho * sizeof (char));
        imagen->pixelG[i] = malloc(imagen->ancho * sizeof (char));
        imagen->pixelB[i] = malloc(imagen->ancho * sizeof (char));
    }

    //*********************************************************************************************************
    //Padding (Bytes necesarios para que el Pad row alcance a ser multiplo de 4 Bytes)		
    //*********************************************************************************************************
    resto = (imagen->ancho * 3) % 4;
    if (resto != 0)
        resto = 4 - resto;

    //*********************************************************************************************************
    //Pasar la imágen a el arreglo reservado en escala de grises
    //*********************************************************************************************************
    //Iterar a través de las filas de píxeles, teniendo en cuenta que los datos comienza en la esquina inferior izquierda de la imagen BMP
    for (i = imagen->alto - 1; i >= 0; i--) {
        for (j = 0; j < imagen->ancho; j++) {
            fread(&B, sizeof (char), 1, archivo); //Byte Blue del pixel
            fread(&G, sizeof (char), 1, archivo); //Byte Green del pixel
            fread(&R, sizeof (char), 1, archivo); //Byte Red del pixel
            imagen->pixelR[i][j] = R;
            imagen->pixelG[i][j] = G;
            imagen->pixelB[i][j] = B;
        }

        //Padding (Bytes necesarios para que el Pad row alcance a ser multiplo de 4 Bytes)		
        for (k = 1; k <= resto; k++) {
            fread(&var, sizeof (char), 1, archivo); //Leer los pixeles de relleno (Padding)
        }
    }
    //Cerrrar el archivo
    fclose(archivo);
}

/**
 * Función encargada de guardar una imagen en la ruta especificada
 * @param imagen La estructura en la que está la información relacionada con la imagen que queremos guardar
 * @param ruta La ruta en la que vamos a guardar
 */
void guardarImagen(BMP *imagen, char *ruta) {
    FILE *archivo; //Puntero FILE para el archivo de imágen a abrir

    int i, j, k, resto, var;

    //Abrir el archivo de imágen
    archivo = fopen(ruta, "wb+");
    if (!archivo) {
        //Si la imágen no se encuentra en la ruta dada
        printf("La imágen %s no se pudo crear\n", ruta);
        exit(1);
    }
    //Leer la cabecera de la imagen y almacenarla en la estructura global img
    fseek(archivo, 0, SEEK_SET);
    fwrite(&imagen->bm, sizeof (char), 2, archivo);
    fwrite(&imagen->tamano, sizeof (int), 1, archivo);
    fwrite(&imagen->reservado, sizeof (int), 1, archivo);
    fwrite(&imagen->offset, sizeof (int), 1, archivo);
    fwrite(&imagen->tamanoMetadatos, sizeof (int), 1, archivo);
    fwrite(&imagen->alto, sizeof (int), 1, archivo);
    fwrite(&imagen->ancho, sizeof (int), 1, archivo);
    fwrite(&imagen->numeroPlanos, sizeof (short int), 1, archivo);
    fwrite(&imagen->profundidadColor, sizeof (short int), 1, archivo);
    fwrite(&imagen->tipoCompresion, sizeof (int), 1, archivo);
    fwrite(&imagen->tamanoEstructura, sizeof (int), 1, archivo);
    fwrite(&imagen->pxmh, sizeof (int), 1, archivo);
    fwrite(&imagen->pxmv, sizeof (int), 1, archivo);
    fwrite(&imagen->coloresUsados, sizeof (int), 1, archivo);
    fwrite(&imagen->coloresImportantes, sizeof (int), 1, archivo);

    //*********************************************************************************************************
    //Colocar el cursor en el byte (offset) donde comienzan los datos de la imagen
    //*********************************************************************************************************
    fseek(archivo, imagen->offset, SEEK_SET);

    //*********************************************************************************************************
    //Pasar la imágen del arreglo reservado en escala de grises a el archivo (Deben escribirse los valores BGR)
    //*********************************************************************************************************
    resto = (imagen->ancho * 3) % 4; //Padding (Bytes necesarios para que el Pad row alcance a ser multiplo de 4 Bytes)		
    if (resto != 0)
        resto = 4 - resto;

    //Iterar a través de las filas de píxeles, teniendo en cuenta que los datos comienza en la esquina inferior izquierda de la imagen BMP
    for (i = imagen->alto - 1; i >= 0; i--) {
        for (j = 0; j < imagen->ancho; j++) {
            //Ecribir los 3 bytes BGR al archivo BMP, en este caso todos se igualan al mismo valor (Valor del pixel en la matriz de la estructura imagen)
            fwrite(&imagen->pixelB[i][j], sizeof (char), 1, archivo); //Escribir el Byte Blue del pixel 
            fwrite(&imagen->pixelG[i][j], sizeof (char), 1, archivo); //Escribir el Byte Green del pixel
            fwrite(&imagen->pixelR[i][j], sizeof (char), 1, archivo); //Escribir el Byte Red del pixel
        }

        //Padding (Bytes necesarios para que el Pad row alcance a ser multiplo de 4 Bytes)		
        for (k = 1; k <= resto; k++)
            fwrite(&var, sizeof (char), 1, archivo); //Escribir los pixeles de relleno		
    }
    //Cerrrar el archivo
    fclose(archivo);
}

/**
 * Función encargada de rotar una imagen usando el algoritmo clásico
 * @param imagenOriginal La imagen original a ser tratada
 * @param imagenTratada Estructura en el que se guardará la imagen tratada
 */
void rotacionClasica(BMP *imagenOriginal, BMP * imagenTratada) {
    int i;
    int j;
    int n = imagenOriginal->alto;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            imagenTratada->pixelR[i][j] = imagenOriginal->pixelR[n - j - 1][i];
            imagenTratada->pixelB[i][j] = imagenOriginal->pixelB[n - j - 1][i];
            imagenTratada->pixelG[i][j] = imagenOriginal->pixelG[n - j - 1][i];
        }
    }
}

/**
 * Función encargada de rotar una imagen la cantidad de grados especificada mediante el uso de un algoritmo con la técnica 
 * divide y vencerás
 * @param i El inicio del rango a tratar
 * @param j El inicio del rango a tratar
 * @param i1 El final del rango a tratar
 * @param j1 El final del rango a tratar
 * @param imagen La imagen original a ser tratada
 * @param n El tamaño del problema
 */
void rota90GradosDivide(int i, int j, int i1, int j1, BMP * imagen, int n) {
    if (n > 1) {
        rota90GradosDivide(i, j, (n / 2) + i, (n / 2) + j, imagen, n / 2);
        rota90GradosDivide(i + (n / 2), j, n + i, (n / 2) + j, imagen, n / 2);
        rota90GradosDivide(i + (n / 2), j + (n / 2), n + i, n + j, imagen, n / 2);
        rota90GradosDivide(i, j + (n / 2), (n / 2) + i, n + j, imagen, n / 2);
    }
    traslacion(i, j, i1, j1, imagen, n / 2);
}

/**
 * Función encargada de rotar una imagen la cantidad de grados especificada mediante el uso de un algoritmo con la técnica 
 * divide y vencerás, que además incorpora el uso de threads para acelerar su ejecución
 * @param i El inicio del rango a tratar
 * @param j El inicio del rango a tratar
 * @param i1 El final del rango a tratar
 * @param j1 El final del rango a tratar
 * @param imagen La imagen original a ser tratada
 * @param n El tamaño del problema
 */
void rota90GradosDivideThreads(int i, int j, int i1, int j1, BMP * imagen, int n) {
    if (n > 1) {
    	int matrices = 4;
    	// Comenzamos la
    	// repartición de los subarreglos
    	pthread_t *thread;
    	thread = malloc(matrices*sizeof(pthread_t));
    	// Creamos los auxiliares 
    	BMPAux * c11 = (BMPAux *)malloc(sizeof(BMPAux));
    	(*c11).i = i; 
    	(*c11).j = j; 
    	(*c11).i1 = (n / 2) + i; 
    	(*c11).j1 = (n / 2) + j;
    	(*c11).n = (n / 2);
    	(*c11).imagen = imagen;


    	BMPAux * c12 = (BMPAux *)malloc(sizeof(BMPAux));
    	(*c12).i = i + (n / 2); 
    	(*c12).j = j; 
    	(*c12).i1 = n + i; 
    	(*c12).j1 = (n / 2) + j;
    	(*c12).n = (n / 2);
    	(*c12).imagen = imagen;

    	BMPAux * c21 = (BMPAux *)malloc(sizeof(BMPAux));
    	(*c21).i = i + (n / 2); 
    	(*c21).j =  j + (n / 2); 
    	(*c21).i1 = n + i; 
    	(*c21).j1 = n + j;
    	(*c21).n = (n / 2);
    	(*c21).imagen = imagen;

    	BMPAux * c22 = (BMPAux *)malloc(sizeof(BMPAux));
    	(*c22).i = i; 
    	(*c22).j =  j + (n / 2); 
    	(*c22).i1 = (n / 2) + i; 
    	(*c22).j1 = n + j;
    	(*c22).n = (n / 2);
    	(*c22).imagen = imagen;

    	// Creamos los hilos
    	if(pthread_create(&thread[0], NULL, ejecutaRotacion, (void *)c11) != 0)
    	{
    		perror("El thread no  pudo crearse [Arbol]\n");
    		exit(-1);
    	}
    	if(pthread_create(&thread[1], NULL, ejecutaRotacion, (void *)c12) != 0)
    	{
    		perror("El thread no  pudo crearse [Arbol]\n");
    		exit(-1);
    	}
    	if(pthread_create(&thread[2], NULL, ejecutaRotacion, (void *)c21) != 0)
    	{
    		perror("El thread no  pudo crearse [Arbol]\n");
    		exit(-1);
    	}
    	if(pthread_create(&thread[3], NULL, ejecutaRotacion, (void *)c22) != 0)
    	{
    		perror("El thread no  pudo crearse [Arbol]\n");
    		exit(-1);
    	}
    	// Esperamos a los hilos
    	int i;
    	for (i=0; i<matrices; i++) pthread_join (thread[i], NULL);
    	free(thread);

    }
    traslacion(i, j, i1, j1, imagen, n / 2);
}

/*
 * Funciones "privadas", no expuestas en el archivo de cabecera
 */

void traslacion(int i, int j, int i1, int j1, BMP * imagen, int n) {
    if (i < i1 - n) {
        rotacionBaseM(i, j, i1, j1, imagen->pixelB, n);
        rotacionBaseM(i, j, i1, j1, imagen->pixelR, n);
        rotacionBaseM(i, j, i1, j1, imagen->pixelG, n);
        traslacion(i + 1, j, i1, j1, imagen, n);
    }
}

void traslacionM(int i, int j, int i1, int j1, unsigned char ** matriz, int n) {
    if (i < i1 - n) {
        rotacionBaseM(i, j, i1, j1, matriz, n);
        traslacionM(i + 1, j, i1, j1, matriz, n);
    }
}

/**
 * Función que aplica el algoritmo de rotación recursivo a una una imagen
 * @param i El inicio del rango a tratar
 * @param j El inicio del rango a tratar
 * @param i1 El final del rango a tratar
 * @param j1 El final del rango a tratar
 * @param imagen La imagen a rotar
 * @param n El tamaño del problema
 */
void rotacionBase(int i, int j, int i1, int j1, BMP * imagen, int n) {
    if (j < j1 - n) {
        char px = imagen->pixelB[i][j];
        imagen->pixelB[i][j] = imagen->pixelB[i + n][j];
        imagen->pixelB[i + n][j] = imagen->pixelB[i + n][j + n];
        imagen->pixelB[i + n][j + n] = imagen->pixelB[i][j + n];
        imagen->pixelB[i][j + n] = px;

        px = imagen->pixelR[i][j];
        imagen->pixelR[i][j] = imagen->pixelR[i + n][j];
        imagen->pixelR[i + n][j] = imagen->pixelR[i + n][j + n];
        imagen->pixelR[i + n][j + n] = imagen->pixelR[i][j + n];
        imagen->pixelR[i][j + n] = px;

        px = imagen->pixelG[i][j];
        imagen->pixelG[i][j] = imagen->pixelG[i + n][j];
        imagen->pixelG[i + n][j] = imagen->pixelG[i + n][j + n];
        imagen->pixelG[i + n][j + n] = imagen->pixelG[i][j + n];
        imagen->pixelG[i][j + n] = px;
        rotacionBase(i, j + 1, i1, j1, imagen, n);
    }
}

/**
 * Función que aplica el algoritmo de rotación recursivo a una matriz de caracteres de forma individual
 * @param i El inicio del rango a tratar
 * @param j El inicio del rango a tratar
 * @param i1 El final del rango a tratar
 * @param j1 El final del rango a tratar
 * @param matriz La matriz a rotar
 * @param n El tamaño del problema
 */
void rotacionBaseM(int i, int j, int i1, int j1, unsigned char ** matriz, int n) {
    if (j < j1 - n) {
        char px = matriz[i][j];
        matriz[i][j] = matriz[i + n][j];
        matriz[i + n][j] = matriz[i + n][j + n];
        matriz[i + n][j + n] = matriz[i][j + n];
        matriz[i][j + n] = px;
        rotacionBaseM(i, j + 1, i1, j1, matriz, n);
    }
}

/**
 * Auxiliar en la ejecución del algoritmo de rotación usando hilos
 * @param imagen
 */
void ejecutaRotacion(void * imagen){
	BMPAux * aux = (BMPAux *)imagen;
    rota90GradosDivide(aux->i, aux->j, aux->i1, aux->j1, aux->imagen, aux->n);
}
