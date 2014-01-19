#include "pch.h"
//#include <stdlib.h>
//#include <stdio.h>
#include "Codificacion.h"
#include "ColaCodificacion.h"
#include "Bit.h"
#include "ListaFrecuencias.h"

using namespace RuntimeComponent;

/**
 * Genera el árbol de codificacion
 * @param frecuencias Un arreglo con las frecuencias ordenadas previamente de forma ascendente
 * @param length La longitud del arreglo de frecuencias
 */
void Codificacion::creaArbolCodificacion(Frecuencia * frecuencias, int length) {
	int i;
	nodos = length;
	// Reservamos memoria
	bosqueHuffman = (NodoArbol **)malloc(sizeof(NodoArbol *)* length);
	// Como las frecuencias ya estaban ordenadas previamente, basta con asignarlas en ese orden dentro del nuevo arreglo
	for (i = 0; i < length; i++) {
		NodoArbol * hoja = (NodoArbol *)malloc(sizeof(NodoArbol));
		hoja->frecuencia = &(frecuencias[i]); // Guardamos la información del caracter y sus apariciones
		hoja->peso = frecuencias[i].apariciones; // Para el paso uno el peso es igual a la frecuencia del caracter
		hoja->nodo0 = NULL; // Son hojas
		hoja->nodo1 = NULL; // Son hojas
		hoja->visitado = 0; // Lo marcamos como no visitado
		bosqueHuffman[i] = hoja;
	}

	// Llamado a la función encargada de realizar las combinaciones
	generaUnicoArbol();
	//ordenaVectorFrecuenciasPorCaracter(frecuencias, length);
	for (i = 0; i < length; i++) {
		// Usaremos una cola para guardar la sevuencia de 1 y 0
		ColaCodificacion * cola = new ColaCodificacion();//(ColaCodificacion *)malloc(sizeof(ColaCodificacion));
		// Obtenemos el camino tantas veces como caracteres tenemos
		// En boasqueHuffman[0] está el árbol de codificación.
		this->obtieneCaminoR(bosqueHuffman[0], cola);
		this->asignaCodificacion(frecuencias, length, cola);
		// Liberamos la memoria de la cola
		free(cola);
	}
}

/**
 *	Función que realiza la combinación de los árboles hasta llegar a un único nodo
 */
void Codificacion::generaUnicoArbol() {
	int i = nodos, j;

	while (bosqueHuffman[1] != NULL){ // Mientras no tengamos un solo árbol

		// Generamos un nuevo árbol:
		NodoArbol * nuevaHoja = (NodoArbol *)malloc(sizeof(NodoArbol));
		// Como es un árbol resultado de la combinación de otros dos, ya no deberá tener un caracter asociado
		nuevaHoja->frecuencia = NULL;
		nuevaHoja->peso = bosqueHuffman[0]->peso + bosqueHuffman[1]->peso; // La suma de los pesos de sus dos hijos
		nuevaHoja->nodo0 = bosqueHuffman[0]; // Hijo de menor frecuencia
		nuevaHoja->nodo1 = bosqueHuffman[1]; // Hijo de mayor frecuencia
		nuevaHoja->visitado = 0; // Lo marcamos como no visitado

		// Dentro de este for iremos recorriendo todos, un lugar hacia atrás cada vez
		for (j = 2; j < i; j++) {
			bosqueHuffman[j - 1] = bosqueHuffman[j];
		}
		// Borramos el último elemento de la lista
		bosqueHuffman[j - 1] = NULL;
		// Y asignamos el nuevo al inicio
		bosqueHuffman[0] = nuevaHoja;
		// Llamamos a la ordenación de los árboles para reacomodarlos según su peso
		reordenaArboles();
	}

}

/**
 * Función encargada de la reordenación de los árboles dentro del arreglo
 */
void Codificacion::reordenaArboles(){
	// Bubblesort para ordenar los árboles
	// TODO:	Implementar un algoritmo de ordenación más eficiente, 
	//			además, sabemos que hay un solo elemento desordenado (boasqueHuffman[0])
	//			podríamos auxiliarnos de eso para escribir la ordenación más eficiente.
	NodoArbol * temp;
	int i, j;
	char cambio = 0;
	for (i = 0; i < nodos && bosqueHuffman[i] != NULL; i++){
		for (j = 0; j < nodos && bosqueHuffman[j + 1] != NULL; j++)
		{
			// Comprobamos el peso del árbol
			if (bosqueHuffman[j]->peso > bosqueHuffman[j + 1]->peso)
			{
				temp = bosqueHuffman[j];
				bosqueHuffman[j] = bosqueHuffman[j + 1];
				bosqueHuffman[j + 1] = temp;
			}
		}
	}
}

/**
 * Función que arma la codificación para cada caracter de forma recursiva,
 * almacena el resultado en una cola para posteriormente recuperarlo
 * @param arbol El árbol donde está la codificación
 * @param cola La cola en la que se almacenarán la codificación
 */
void Codificacion::obtieneCaminoR(NodoArbol * arbol, ColaCodificacion * cola) {
	// Comprobamos si el árbol no ha sido visitado
	if (arbol != NULL && arbol->visitado == 0){
		// Si tiene hijo 0 y no ha sido visitado, nos movemos hacia el
		if (arbol->nodo0 && arbol->nodo0->visitado == 0)
		{
			// Insertamos un 0 en la cola
			cola->formaCodificacion('0');
			//printf("0");
			this->obtieneCaminoR(arbol->nodo0, cola);
		}
		// Si tiene hijo 1 y no ha sido visitado, nos movemos hacia el
		else if (arbol->nodo1 && arbol->nodo1->visitado == 0)
		{
			cola->formaCodificacion('1');
			//printf("1");
			this->obtieneCaminoR(arbol->nodo1, cola);
		}
		// Si no tiene hijos o ya fueron visitados
		else
		{
			// Lo marcamos como visitado
			arbol->visitado = 1;
			if (arbol->frecuencia != NULL)
			{
				// Insertamos el caracter en la cola, pero al inicio
				cola->formaInicioCodificacion(arbol->frecuencia->caracter);
				//printf(" %c\n",arbol->frecuencia->caracter);
			}
			// Insertamos el fin de línea como referencia
			cola->formaCodificacion('\0');
		}
		// Comprobamos que sea un nodo tallo
		if (arbol->frecuencia == NULL)
			// Si sus hijos ya fueron visitados
		if (arbol->nodo0->visitado == 1 && arbol->nodo1->visitado == 1)
			// Marcamos el padre como visitado
			arbol->visitado = 1;
	}
}

/**
 * Función para reordenar el vector de frecuencias de acuerdo a los caracteres que contiene
 * usando el algoritmo de ordenación por inserción
 * @param frecuencias
 * @param length
 */
void Codificacion::ordenaVectorFrecuenciasPorCaracter(Frecuencia * frecuencias, int length){
	// Inicializamos una variable
	// auxiliar para recorrer el arreglo
	int ix = 1;
	for (; ix < length; ++ix) // Recorremos el arreglo
	{
		// Asignamos el valor actual a
		// una variable temporal
		Frecuencia temp = frecuencias[ix];
		// Nos ubicamos en la posición anterior a 
		// la actual para ir revisando los valores
		int j = ix - 1;
		while ((frecuencias[j].caracter > temp.caracter) && (j >= 0))
		{
			// Nos vamos moviendo hacia atrás
			// hasta que encontremos la nueva
			// ubicación de nuestro valor
			frecuencias[j + 1] = frecuencias[j];
			j--;
		}
		// Lo asignamos
		frecuencias[j + 1] = temp;
	}
}

/**
 * Función para modificar los bits de un arreglo de caracteres de acuerdo a los parámetros recibidos
 * @param salida Es un arreglo de caracteres al cual se le van a modificar los bits
 * @param salidaLength El tamaño en bits del arreglo
 * @param pointer La posición a partir de la cual se comenzar a modificar los
 * @param c El caracter a codificar
 * @param frecuencias El arreglo de las frecuencias
 * @param length El tamaño del arreglo de frecuencias
 */
int Codificacion::escribeBits(char * salida, int salidaLength, long pointer, char c, Frecuencia * frecuencias, int length){
	int bitsescritos = 0;
	int indiceFrecuencia = buscaFrecuencia(frecuencias, 0, length, c);
	Frecuencia f = frecuencias[indiceFrecuencia];
	Bit * bits = new Bit();
	if (indiceFrecuencia >= 0){
		for (bitsescritos = 0; f.codigo[bitsescritos] != '\0'; bitsescritos++)
		{
			if (f.codigo[bitsescritos] == '1')
			{
				bits->pon1(salida, pointer + bitsescritos);
			}
			else if (f.codigo[bitsescritos] == '0')
			{
				bits->pon0(salida, pointer + bitsescritos);
			}
		}
	}
	return bitsescritos;
}

/**
 * Función encargada de asignar la secuencia de cóodigo correspondiente a cada caracter
 * @param frecuencias Un arreglo de frecuencias ordenado ascendentemente por el caracter
 * @param length El tamaño del arreglo de frecuencias
 * @param cola La cola que contiene el código
 */
void Codificacion::asignaCodificacion(Frecuencia * frecuencias, int length, ColaCodificacion * cola){
	char caracter = cola->atiendeCola();
	int longitudCodigo = cola->count;
	int indiceFrecuencia = buscaFrecuencia(frecuencias, 0, length, caracter);
	int i;
	frecuencias[indiceFrecuencia].codigo = (char *)calloc(longitudCodigo - 1, sizeof(char));
	for (i = 0; i < longitudCodigo; i++){
		frecuencias[indiceFrecuencia].codigo[i] = cola->atiendeCola();
	}
}

/**
 * Función para buscar un caracter dentro del arreglo de caracteres, utiliza búsqueda lineal
 * @param frecuencias
 * @param inicio
 * @param final
 * @param c El caracter a buscar
 */
int Codificacion::buscaFrecuencia(Frecuencia * frecuencias, int inicio, int final, char c) {
	int i = -1;
	// TODO:	Implementar un mejor algoritmo de búsqueda
	for (inicio = 0; inicio < final; inicio++)
	{
		if (frecuencias[inicio].caracter == c){
			i = inicio;
			break;
		}
	}
	return i;
}

/**
 * Función encargada de convertir de un arreglo de caracteres codificado a uno sin codificar empleando
 * el árbol de codificación previamente generado
 * @param codificado El arreglo de caracteres leído del archivo codificado
 * @param longitudCodificado El tamaño del arreglo codificado
 * @param salida El arreglo de caracteres al que se debe escribir el resultado
 */
void Codificacion::decodificaBits(char * codificado, long longitudCodificado, char * salida){
	long x = 0;
	int v;
	int charSalida = 0;
	Bit * bits = new Bit();
	// Nos posicionamos en el la raíz de nuestro árbol
	NodoArbol * aux = bosqueHuffman[0];
	// Navegamos entre los nodos de acuerdo al valor de los bits leídos
	// hasta terminar de recorrerlos todos
	for (x = 0; x < longitudCodificado;){
		while (aux->frecuencia == NULL){
			// Obtenemos el valor del bit y de acuerdo a este
			// nos movemos hacia la hoja 0 o 1 de nuetro árbol
			v = bits->valorBit(codificado, x++);
			if (v == 0){ aux = aux->nodo0; }
			else if (v == 1){ aux = aux->nodo1; }
		}
		// Asignamos el caracter asociado al arreglo de salida
		salida[charSalida++] = aux->frecuencia->caracter;
		// Nos colocamos nuevamente en la raíz del árbol
		aux = bosqueHuffman[0];
	}

}

