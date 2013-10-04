#include "arbol.h"
#include <stdlib.h>
#include <stdio.h>

int arrayIndex = 0;

/*
 * Función encargada de iniciar el apuntado a arbol
 *
 * */
void Iniciar(arbol* a){
	*a = NULL;
	return;
}

/*
 * Función que determina si un arbol está vacío
 * Regresa 1 en caso de que esté vacío y 0 en otro caso
 *
 * */
int Vacio(arbol* a){
	if(*a == NULL)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

/*
 * Función encargada de insertar nuevos nodos
 * al arbol, recursivamente
 *
 * */
void NuevoNodo(arbol* a, int valor){
	// Si el árbol está vacío, crea un nodo en la raíz
	if(Vacio(a) == 1)
	{
		*a = CreaNodo(valor);
	}
	else
	{
		// Determinamos hacia donde hay que mover
		// la posición
		if((*a)->valor < valor)
		{
			// Llamamos nuevamente a esta función
			// pero ahora con la nueva ubicación
			NuevoNodo(&((*a)->derecho),valor);
		}
		else	
		{
			// Llamamos nuevamente a esta función
			// pero ahora con la nueva ubicación
			NuevoNodo(&((*a)->izquierdo),valor);
		}
	}
	return;
}

/*
 * Función encargada de crear un nuevo nodo con el valor
 * enviado en el parámetro
 *
 * */
Nodo * CreaNodo(int valor){
	Nodo * aux = (Nodo *)malloc(sizeof(Nodo));
	aux->valor = valor;
	aux->derecho = NULL;
	aux->izquierdo = NULL;
	return aux;
}

/*
 * Función encargada de rellenar un arreglo mediante 
 * la lectura InOrder del arbol
 *
 * */
void RellenaInorden(arbol* a, int * arreglo)
{
	// Comprobamos que no esté vacío
	if(Vacio(a) != 1)
	{
		// Nos movemos a la izquierda y llamamos a la función nuevamente
		RellenaInorden(&((*a)->izquierdo),arreglo);
		// Aumentamos el índice y almacenamos el valor en el arreglo
		arreglo[arrayIndex++] = (*a)->valor;
		// Nos movemos a la derecha y llamamos a la función nuevamente
		RellenaInorden(&((*a)->derecho),arreglo);		
	}
	return;
}
