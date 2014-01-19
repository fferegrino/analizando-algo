/* 
 * File:   frecuencias.c
 * Author: fferegrino
 *
 * Created on 23 de octubre de 2013, 03:47 PM
 */
 
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "ListaFrecuencias.h"

using namespace RuntimeComponent;


/**
 * Función encargada de insertar los caracteres en una lista de frecuencias
 * @param frecuencias Un apuntador a la lista
 * @param caracteres Los caracteres a insertar
 * @param length La longitud del arreglo de caracteres a insertar
 */
void ListaFrecuencias::generaFrecuencias(char caracteres[], int length) {
    // Comprobamos que la lista esté iniciada, si no lo está, la inicializamos
    if (this->inicio == NULL) {
		this->length = 0;
    }
    int ix;
    // Recorremos el arreglo de caracteres para insertarlos en la lista de frecuencia
    for (ix = 0; ix < length; ix++) {
        insertaFrecuencia(caracteres[ix]);
    }
}


/**
 * Función para insertar (o actualizar) en la lista de frecuencias
 * @param frecuencias La lista de frecuencias
 * @param caracter El caracter que queremos insertar o actualizar
 */
void ListaFrecuencias::insertaFrecuencia(char caracter) {
    NodoFrecuencia * f;
    NodoFrecuencia * fanterior;
	///DEBUG
	//imprimeListaF(frecuencias);
	
    for(f = this->inicio, fanterior = this->inicio;f != NULL; f = f->siguiente)
    {
		if (f->frecuencia.caracter == caracter) { 
            // En caso de que exista solo incrementamos sus ocurrencias
            f->frecuencia.apariciones++;
			int ix = 0;
			// Comprobamos que la lista siga en orden, si no, la acomodamos
			// TODO: 	Hacer un ciiclo para mover el elemento hasta que quede en orden
			//			actualmente solo lo mueve una posición.
			if( f->siguiente != NULL 
				&& f->frecuencia.apariciones > f->siguiente->frecuencia.apariciones)
			{
				
				NodoFrecuencia * auxiliar = f->siguiente;
				if(f == this->inicio)
				{
					// En caso de que el elemento que se tenga que mover esté en el inicio de la lista 
					this->inicio = f->siguiente;
					f->siguiente = auxiliar->siguiente;
					this->inicio->siguiente = f;
				}
				else
				{
					// Si el elemento se encuentra en otra posición
					fanterior->siguiente = f->siguiente;
					f->siguiente = fanterior->siguiente->siguiente;
					fanterior->siguiente->siguiente = f;
				}
			}
            // Salimos de la función
            return;
        }
		// Movemos el auxiliar a la siguiente posición
		fanterior = f;
	}
	
	// Si se llega hasta este punto significa que el nodo no existía anteriormente en la lista
    // Insertamos el nodo en la lista, como es su primera aparición, queda al inicio
	NodoFrecuencia * aux = this->inicio;
	f = (NodoFrecuencia *) malloc(sizeof (NodoFrecuencia));
    f->frecuencia.caracter = caracter;
    f->frecuencia.apariciones = 1;
    f->siguiente = aux;
	this->inicio = f;
	this->length++;
}

/**
 * Función para convertir de una lista de frecuencias a un vector de frecuencias
 * @param frecuencias La lista de frecuencias a convertir
 */ 
Frecuencia * ListaFrecuencias::vectorFrecuencias(){
	// Reservamos la memoria suficiente para almacenar el arreglo
	Frecuencia * vector = (Frecuencia *) malloc(sizeof(Frecuencia) * this->length);
	int i = 0;
    NodoFrecuencia * f;
	for (f = this->inicio; f != NULL; f = f->siguiente, i++){
		vector[i] = f->frecuencia;
	}
	ordenaFrecuenciasPorAparicion(vector);
		
	return vector;
}


void ListaFrecuencias::ordenaFrecuenciasPorAparicion(Frecuencia * vector){
	Frecuencia temp;
	int i, j;
	// Bubble sort para ordenar el vector de frecuencias de menor a mayor
	// TODO:	Implementar un algoritmo de ordenación más eficiente
	for (i = 0; i < this->length - 1; i++)
	{
		for (j = 0; j < this->length - 1; j++)
		{
			if(vector[j].apariciones > vector[j+1].apariciones)
			{
				temp=vector[j];
				vector[j]=vector[j+1];
				vector[j+1]=temp;
			}
		}
	} 
}