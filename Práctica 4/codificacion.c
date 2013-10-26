/* 
 * File:   codificacion.c
 * Author: fferegrino
 *
 * Created on 25 de octubre de 2013, 04:16 PM
 */
 
#include <stdlib.h>
#include <stdio.h>
#include "codificacion.h"

// En este doble apuntador se almacenará la colección de frecuencias
NodoArbol ** bosqueHuffman;
int nodos;

void reordenaArboles();
void generaUnicoArbol();

/**
 * Genera el árbol de codificacion
 * @param frecuencias Un arreglo con las frecuencias ordenadas previamente de forma ascendente
 * @param length La longitud del arreglo de frecuencias
 */
void creaArbolCodificacion(Frecuencia * frecuencias, int length) {
	int i;
	nodos = length;
	// Reservamos memoria
	bosqueHuffman = (NodoArbol **)malloc(sizeof(NodoArbol *) * length);
	// Como las frecuencias ya estaban ordenadas previamente, basta con asignarlas en ese orden dentro del nuevo arreglo
	for(i = 0; i < length; i++) {
		NodoArbol * hoja = (NodoArbol *)malloc(sizeof(NodoArbol));
		hoja->frecuencia = &(frecuencias[i]); // Guardamos la información del caracter y sus apariciones
		hoja->peso = frecuencias[i].apariciones; // Para el paso uno el peso es igual a la frecuencia del caracter
		hoja->nodo0 = NULL; // Son hojas
		hoja->nodo1 = NULL; // Son hojas
		bosqueHuffman[i] = hoja;
	}
	generaUnicoArbol();
}

/**
 *	Función que realiza la combinación de los árboles hasta llegar a un único nodo
 */
void generaUnicoArbol() {
	int i = nodos, j;
	
	while(bosqueHuffman[1] != NULL){ // Mientras no tengamos un solo árbol
		
		// Generamos un nuevo árbol:
		NodoArbol * nuevaHoja = (NodoArbol *)malloc(sizeof(NodoArbol));
		// Como es un árbol resultado de la combinación de otros dos, ya no deberá tener un caracter asociado
		nuevaHoja->frecuencia = NULL;
		nuevaHoja->peso = bosqueHuffman[0]->peso + bosqueHuffman[1]->peso; // La suma de los pesos de sus dos hijos
		nuevaHoja->nodo0 = bosqueHuffman[0]; // Hijo de menor frecuencia
		nuevaHoja->nodo1 = bosqueHuffman[1]; // Hijo de mayor frecuencia
		
		// Dentro de este for iremos recorriendo todos, un lugar hacia atrás cada vez
		for(j = 2; j < i; j++) {
			bosqueHuffman[j - 1] = bosqueHuffman[j];
		}
		// Borramos el último elemento de la lista
		bosqueHuffman[j-1] = NULL;
		// Y asignamos el nuevo al inicio
		bosqueHuffman[0] = nuevaHoja;
		// Llamamos a la ordenación de los árboles para reacomodarlos según su peso
		reordenaArboles();
	}
	
}
/**
 * Función encargada de la reordenación de los árboles dentro del arreglo
 */
void reordenaArboles(){
	// Bubblesort para ordenar los árboles
	// TODO:	Implementar un algoritmo de ordenación más eficiente, 
	//			además, sabemos que hay un solo elemento desordenado (boasqueHuffman[0])
	//			podríamos auxiliarnos de eso para escribir la ordenación más eficiente
	NodoArbol * temp;
	int i,j;
	char cambio = 0;
	for(i = 0; i < nodos && bosqueHuffman[i] != NULL; i++){
		for(j = 0; j < nodos && bosqueHuffman[j+1] != NULL; j++)
		{
			// Comprobamos el peso del árbol
			if(bosqueHuffman[j]->peso > bosqueHuffman[j+1]->peso)
			{
				temp=bosqueHuffman[j];
				bosqueHuffman[j]=bosqueHuffman[j+1];
				bosqueHuffman[j+1]=temp;
			}
		}
	}
}	
