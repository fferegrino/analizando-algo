#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "frecuencias.h"

/**
 * Función interna para insertar o actualizar la frecuencia de un elemento
 * @param frecuencias
 * @param caracter
 */
void insertaFrecuencia(ListaFrecuencia * frecuencias, char caracter);

void imprimeListaF(ListaFrecuencia * frecuencias);

void generaFrecuencias(ListaFrecuencia * frecuencias, char caracteres[], int length) {
    // Comprobamos que la lista esté iniciada, si no lo está, la inicializamos
    if (frecuencias->inicio == NULL) {
        frecuencias->length = 0;
    }
    int ix;
    // Recorremos el arreglo de caracteres para insertarlos en la lista de frecuencia
    for (ix = 0; ix < length; ix++) {
        insertaFrecuencia(frecuencias, caracteres[ix]);
    }
}


/**
 * Función para insertar (o actualizar) en la lista de frecuencias
 * @param frecuencias La lista de frecuencias
 * @param caracter El caracter que queremos insertar o actualizar
 */
void insertaFrecuencia(ListaFrecuencia * frecuencias, char caracter) {
    // Buscamos si la frecuencia ya existe
    int x;
    NodoFrecuencia * f;
    NodoFrecuencia * fanterior;
	///DEBUG
	///imprimeListaF(frecuencias);
	
    for(f = frecuencias->inicio, fanterior = frecuencias->inicio;f != NULL; f = f->siguiente)
    {
		if (f->frecuencia.caracter == caracter) { 
            // En caso de que exista solo incrementamos sus ocurrencias
            f->frecuencia.apariciones++;
			
			// Comprobamos que la lista siga en orden, si no, la acomodamos
			if(f->siguiente != NULL 
				&& f->frecuencia.apariciones > f->siguiente->frecuencia.apariciones)
			{
				///DEBUG
				///printf("Superado fanterior = %c inicio= %c \n", f->frecuencia.caracter,f->siguiente->frecuencia.caracter );
				NodoFrecuencia * auxiliar = f->siguiente;
				if(f == frecuencias->inicio)
				{
					// En caso de que el elemento que se tenga que mover esté en el inicio de la lista 
					frecuencias->inicio = f->siguiente;
					f->siguiente = auxiliar->siguiente;
					frecuencias->inicio->siguiente = f;
				}
				else
				{

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
    NodoFrecuencia * aux = frecuencias->inicio;
	f = (NodoFrecuencia *) malloc(sizeof (NodoFrecuencia));
    f->frecuencia.caracter = caracter;
    f->frecuencia.apariciones = 1;
    f->siguiente = aux;
    frecuencias->inicio = f;
    frecuencias->length++;
}


void imprimeListaF(ListaFrecuencia * frecuencias){
	NodoFrecuencia * f;
    for(f = frecuencias->inicio;f != NULL; f = f->siguiente){
		printf("%c : %d -> ",f->frecuencia.caracter,f->frecuencia.apariciones);
	}
	printf("\n\n");
}

Frecuencia * vectorFrecuencias(ListaFrecuencia * frecuencias){
	Frecuencia * vector = (Frecuencia *) malloc(sizeof(Frecuencia) * frecuencias->length);
	int i = 0;
    NodoFrecuencia * f;
    for(f = frecuencias->inicio;f != NULL; f = f->siguiente, i++){
		vector[i] = f->frecuencia;
					
	}
	return vector;
}
