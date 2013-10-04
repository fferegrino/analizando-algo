/*
 * Libería encargada de concentrar los algoritmos de búsqueda
 * 9 de septiembre de 2013
 * Alumnos:
 * 	Feregrino Bolaños Antonio
 * 	Juárez Soriano Nayeli
 * 	Rojas Alejo Diana Isabel
 *
 * */
#include <pthread.h>
#include <stdlib.h>
#include "arbol.h"

// Estructura auxiliar para la búsqueda
// en árbol con hilos
typedef struct auxiliarBusquedaEnArbol{
	arbol t;
	int valorABuscar;
	int * encontrado;
}AuxiliarArbol;

// Estructura auxiliar para la búsqueda
// lineal
typedef struct auxiliarBusquedaLineal{
	int * arrelgo;
	int valorABuscar;
	int inicio;
	int final;
	int * encontrado;
}AuxiliarLineal;

//en busqueda binaria con hilos
typedef struct auxiliarBusquedaBinaria{
	int * arreglo;
	int valorABuscar;
	int * encontrado;
	int tam;
}AuxiliarBusquedaBinaria;

// Prototipos internos
void * procesarBusquedaArbol(void* busqueda);
void * procesarBusquedaBinaria(void* busqueda);
void * procesarBusquedaLineal(void* busqueda);

/*
 * Función que busca en un arreglo mediante el uso
 * de un árbol binario de búsqueda
 * Parámetros:
 *	arreglo - el arreglo en el que se desea buscar
 *	n - la longitud del arreglo anterior
 *	valorABuscar - el valor a buscar dentro del arreglo
 *	bandera - nos indicará si el valor fue encontrado
 *
 * */
void BusquedaEnArbol(int * arreglo, int n, int valorABuscar, int * bandera)
{
	// Variable para "almacenar" el árbol
	arbol t;
	// Creamos nuestro árbols
	Iniciar(&t);
	// Rellenamos el arbol
	int ix = 0;
	for(;ix < n; ++ix)
	{
		NuevoNodo(&t,arreglo[ix]);
	}
	// Lanzamos la búsqueda sin hilos
	BuscaValor(&t, valorABuscar, bandera);
}

/*
 * Función que busca en un arreglo mediante el uso
 * de un árbol binario de búsqueda repartiendo la carga
 * de trabajo en dos hilo
 * Parámetros:
 *	arreglo - el arreglo en el que se desea buscar
 *	n - la longitud del arreglo anterior
 *	valorABuscar - el valor a buscar dentro del arreglo
 *	bandera - nos indicará si el valor fue encontrado
 *
 * */
void BusquedaEnArbolHilos(int * arreglo, int n, int valorABuscar, int * bandera)
{
	// Variable para "almacenar" el árbol
	arbol t;
	// Creamos nuestro árbol
	Iniciar(&t);
	// Rellenamos el arbol
	int ix = 0;
	for(;ix < n; ++ix)
	{
		NuevoNodo(&t,arreglo[ix]);
	}
	/* Parte de hilos */
	// Comprobamos si nuestro valor a buscar
	// no está en la raíz:
	if((*t).valor == valorABuscar) 
	{
		*bandera = (*t).valor;
	}
	else
	{
		// Si no está, comenzamos la
		// repartición de los subarboles
		pthread_t *thread;
		thread = malloc(2*sizeof(pthread_t));
		// Creamos los auxiliares 
		AuxiliarArbol * izq = (AuxiliarArbol *)malloc(sizeof(AuxiliarArbol));
		(*izq).t = (*t).izquierdo;
		(*izq).valorABuscar = valorABuscar;
		(*izq).encontrado = bandera;

		
		AuxiliarArbol * der = (AuxiliarArbol *)malloc(sizeof(AuxiliarArbol));
		(*der).t = (*t).derecho;
		(*der).valorABuscar = valorABuscar;
		(*der).encontrado = bandera;

		// Creamos los hilos
		if(pthread_create(&thread[0], NULL, procesarBusquedaArbol, (void *)izq) != 0)
		{
			perror("El thread no  pudo crearse [Arbol]\n");
			exit(-1);
		}
		if(pthread_create(&thread[1], NULL, procesarBusquedaArbol, (void *)der) != 0)
		{
			perror("El thread no  pudo crearse [Arbol]\n");
			exit(-1);
		}
		// Esperamos a los hilos
		int i;
		for (i=0; i<2; i++) pthread_join (thread[i], NULL);
		free(thread);
	}
}

/*
 * Función que busca en un arreglo mediante el uso
 * del algoritmo de búsqueda secuencial
 * Parámetros:
 *	arreglo - el arreglo en el que se desea buscar
 *	valorABuscar - el valor a buscar dentro del arreglo
 * 	inicio - el punto inicial del segmento dentro del arreglo para buscar
 * 	final - el punto final del segmento dentro del arreglo para buscar
 *	bandera - nos indicará si el valor fue encontrado
 *
 * */	
void BusquedaLineal(int * arreglo, int valorABuscar, int inicio, int final, int * encontrado)
{
	int n;
	for(n = inicio; n < final; n++)
	{
		if(*encontrado >= 0)
		{
			break;
		}
		if (arreglo[n] == valorABuscar )
		{ 
			*encontrado=valorABuscar;
      		}
	}
}

/*
 * Función que busca en un arreglo mediante el uso
 * del algoritmo de búsqueda secuencial
 * Parámetros:
 *	arreglo - el arreglo en el que se desea buscar
 *	valorABuscar - el valor a buscar dentro del arreglo
 * 	inicio - el punto inicial del segmento dentro del arreglo para buscar
 * 	final - el punto final del segmento dentro del arreglo para buscar
 *	bandera - nos indicará si el valor fue encontrado
 *
 * */	
void BusquedaLinealHilos(int * arreglo, int valorABuscar, int inicio, int final, int * encontrado)
{
	int puntoMedio = (final - inicio) / 2;
	if(puntoMedio > 0)
	{
		// Comenzamos la
		// repartición de los subarreglos
		pthread_t *thread;
		thread = malloc(2*sizeof(pthread_t));
		// Creamos los auxiliares 
		AuxiliarLineal * izq = (AuxiliarLineal *)malloc(sizeof(AuxiliarLineal));
		(*izq).arrelgo = arreglo;
		(*izq).valorABuscar = valorABuscar;
		(*izq).encontrado = encontrado;
		(*izq).inicio = inicio;
		(*izq).final = puntoMedio;


		AuxiliarLineal * der = (AuxiliarLineal *)malloc(sizeof(AuxiliarLineal));
		(*der).arrelgo = arreglo;
		(*der).valorABuscar = valorABuscar;
		(*der).encontrado = encontrado;
		(*der).inicio = puntoMedio + 1;
		(*der).final = final;

		// Creamos los hilos
		if(pthread_create(&thread[0], NULL, procesarBusquedaLineal, (void *)izq) != 0)
		{
			perror("El thread no  pudo crearse [Lineal]\n");
			exit(-1);
		}
		if(pthread_create(&thread[1], NULL, procesarBusquedaLineal, (void *)der) != 0)
		{
			perror("El thread no  pudo crearse [Lineal]\n");
			exit(-1);
		}
		// Esperamos a los hilos
		int i;
		for (i=0; i<2; i++) pthread_join (thread[i], NULL);
		free(thread);
	}	
}




/*
 * Función que busca en un arreglo mediante el uso
 * del algoritmo de búsqueda binaria
 * Parámetros:
 *	arreglo - el arreglo en el que se desea buscar
 *	valorABuscar - el valor a buscar dentro del arreglo
 * 	inicio - el punto inicial del segmento dentro del arreglo para buscar
 * 	final - el punto final del segmento dentro del arreglo para buscar
 *	bandera - nos indicará si el valor fue encontrado
 *
 * */	
void BusquedaBinaria(int * arreglo, int valorABuscar, int inicio, int final, int * encontrado)
{
	while(inicio<=final) 
	{	
		if(*encontrado >= 0)
		{	
			break;
		}
		int medio=(inicio+final)/2;  //subdivide el arreglo en 2
		if(valorABuscar==arreglo[medio])    //Si el numero a buscar es el mismo que el numero en el arreglo en posición 'medio'
		{ 
			*encontrado=valorABuscar;
		} else { 
			if(valorABuscar<arreglo[medio]) 
			{ 
				final=medio-1; 
			} 
			else 
			{ 
				inicio=medio+1; 
			} 
		} 
	}
}


	
void BusquedaBinariaHilos(int * arreglo, int valorABuscar, int inicio, int final, int * encontrado)
{
	int puntoMedio = (final - inicio) / 2;
	if(puntoMedio > 0)
	{
		// Comenzamos la
		// repartición de los subarreglos
		pthread_t *thread;
		thread = malloc(2*sizeof(pthread_t));
		// Creamos los auxiliares 
		AuxiliarLineal * izq = (AuxiliarLineal *)malloc(sizeof(AuxiliarLineal));
		(*izq).arrelgo = arreglo;
		(*izq).valorABuscar = valorABuscar;
		(*izq).encontrado = encontrado;
		(*izq).inicio = inicio;
		(*izq).final = puntoMedio;


		AuxiliarLineal * der = (AuxiliarLineal *)malloc(sizeof(AuxiliarLineal));
		(*der).arrelgo = arreglo;
		(*der).valorABuscar = valorABuscar;
		(*der).encontrado = encontrado;
		(*der).inicio = puntoMedio + 1;
		(*der).final = final;

		// Creamos los hilos
		if(pthread_create(&thread[0], NULL, procesarBusquedaLineal, (void *)izq) != 0)
		{
			perror("El thread no  pudo crearse [Binaria]\n");
			exit(-1);
		}
		if(pthread_create(&thread[1], NULL, procesarBusquedaLineal, (void *)der) != 0)
		{
			perror("El thread no  pudo crearse [Binaria]\n");
			exit(-1);
		}
		// Esperamos a los hilos
		int i;
		for (i=0; i<2; i++) pthread_join (thread[i], NULL);
		free(thread);
	}	
}

// Nos ayudará a lanzar la búsqueda binaria por cada hilo
void * procesarBusquedaBinaria(void* busqueda)
{
	AuxiliarLineal * b = (AuxiliarLineal *)busqueda;
	BusquedaBinaria((*b).arrelgo, (*b).valorABuscar,(*b).inicio, (*b).final, (*b).encontrado);
}

// Nos ayudará a lanzar la búsqueda en árbol por cada hilo
void * procesarBusquedaArbol(void* busqueda)
{
	AuxiliarArbol * b = (AuxiliarArbol *)busqueda;
	BuscaValor(&((*b).t), (*b).valorABuscar, (*b).encontrado);
}

// Nos ayudará a lanzar la búsqueda en árbol por cada hilo
void * procesarBusquedaLineal(void* busqueda)
{
	AuxiliarLineal * l = (AuxiliarLineal *)busqueda;
	BusquedaLineal((*l).arrelgo, (*l).valorABuscar,(*l).inicio, (*l).final, (*l).encontrado);
}
