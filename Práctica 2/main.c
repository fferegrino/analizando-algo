#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lector.h"
#include "tiempo.h"
#include "busqueda.h"

#define N 20
#define TOTALARCHIVO 200000


void Shell(int * array, int n);
int * intdup(int const * src, size_t len);

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Error en la ejecucion del programa, intente: practica1 #deArgumentos\n");
		return 0;
	}

	int cantidadABuscar = N;
	int numerosABuscar[N] = 
	{	89344946,14700764,595857862,1872304343,
		4480, 	61396, 2147472445, 2147445644, 1048955290,
		450057883, 187645041, 1980098116, 152503, 5000, 7500,
		214826, 15000, 1360839354, 559833307, 865429016};

	// El tamano del arreglo a procesar
	int cantidadNumeros = atoi(argv[1]);
	// El arreglo original
	int * arregloOriginal = leeNumeros(TOTALARCHIVO);
	// Copiamos los valores al arreglo que se usará en el árbol:
	int * arregloArbol = intdup(arregloOriginal,cantidadNumeros);
	// Creamos un arreglo nuevo a partir del original para ordenar los N numeros:
	int * arregloOrdenadoA = intdup(arregloOriginal,TOTALARCHIVO);
	Shell(arregloOrdenadoA,TOTALARCHIVO); // Llamada a la ordenacion
	// Creamos el arreglo final que contenga los primeros n numeros
	int * arregloOrdenado = intdup(arregloOrdenadoA,cantidadNumeros);
	// Liberación de memoria:
	free(arregloOrdenadoA);
	free(arregloOriginal);

	// Variable de control para ciclos
	int ix = 0;
	// Variable de control para determinar si se encontró el numero
	int encontrado = -1;
	// Variables para controlar el tiempo
	double 	usrtime11, systime11, walltime11,
		usrtime21, systime21, walltime21,
		real, user, sys, cpuwall;

	/* ALGORITMOS */

	//* Lineal normal
	for(ix = 0; ix < cantidadABuscar; ix++){
		int numeroABuscar = numerosABuscar[ix];
		uswtime(&usrtime11, &systime11, &walltime11);
		// Llamada al algoritmo
		BusquedaLineal(arregloOrdenado,numeroABuscar, 0, cantidadNumeros, &encontrado);
		uswtime(&usrtime21, &systime21, &walltime21);
		// Cálculos
		real = walltime21 - walltime11;
		// Impresión de resultados
		if(encontrado > 0)
		{
			printf("lineal|normal|%d|%d|%.15f|si\n",numeroABuscar,cantidadNumeros,real);
		}
		else
		{
			printf("lineal|normal|%d|%d|%.15f|no\n",numeroABuscar,cantidadNumeros,real);
		}
		encontrado = -1;
	}

	//* Lineal hilos
	for(ix = 0; ix < cantidadABuscar; ix++){
		int numeroABuscar = numerosABuscar[ix];
		uswtime(&usrtime11, &systime11, &walltime11);
		// Llamada al algoritmo
		BusquedaLinealHilos(arregloOrdenado, numeroABuscar, 0, cantidadNumeros, &encontrado);
		uswtime(&usrtime21, &systime21, &walltime21);
		if(encontrado > 0)
		{
			printf("lineal|hilos|%d|%d|%.15f|si\n",numeroABuscar,cantidadNumeros,real);
		}
		else
		{
			printf("lineal|hilos|%d|%d|%.15f|no\n",numeroABuscar,cantidadNumeros,real);
		}
		encontrado = -1;
	}

	//* Binaria normal
	for(ix = 0; ix < cantidadABuscar; ix++){
		int numeroABuscar = numerosABuscar[ix];
		uswtime(&usrtime11, &systime11, &walltime11);
		// Llamada al algoritmo
		BusquedaBinaria(arregloOrdenado,numeroABuscar,0,cantidadNumeros, &encontrado);
		uswtime(&usrtime21, &systime21, &walltime21);
		// Cálculos
		real = walltime21 - walltime11;
		// Impresión de resultados
		if(encontrado > 0)
		{
			printf("binaria|normal|%d|%d|%.15f|si\n",numeroABuscar,cantidadNumeros,real);
		}
		else
		{
			printf("binaria|normal|%d|%d|%.15f|no\n",numeroABuscar,cantidadNumeros,real);
		}
		encontrado = -1;
	}

	//* Binaria hilos
	for(ix = 0; ix < cantidadABuscar; ix++){
		int numeroABuscar = numerosABuscar[ix];
		uswtime(&usrtime11, &systime11, &walltime11);
		// Llamada al algoritmo
		BusquedaBinariaHilos(arregloOrdenado,numeroABuscar,0,cantidadNumeros, &encontrado);
		uswtime(&usrtime21, &systime21, &walltime21);
		if(encontrado > 0)
		{
			printf("binaria|hilos|%d|%d|%.15f|si\n",numeroABuscar,cantidadNumeros,real);
		}
		else
		{
			printf("binaria|hilos|%d|%d|%.15f|no\n",numeroABuscar,cantidadNumeros,real);
		}
		encontrado = -1;
	}
	

	//* Arbol normal
	for(ix = 0; ix < cantidadABuscar; ix++){
		int numeroABuscar = numerosABuscar[ix];
		uswtime(&usrtime11, &systime11, &walltime11);
		// Llamada al algoritmo
		BusquedaEnArbol(arregloArbol, cantidadNumeros, numeroABuscar, &encontrado);
		uswtime(&usrtime21, &systime21, &walltime21);
		// Cálculos
		real = walltime21 - walltime11;
		// Impresión de resultados
		if(encontrado > 0)
		{
			printf("arbol|normal|%d|%d|%.15f|si\n",numeroABuscar,cantidadNumeros,real);
		}
		else
		{
			printf("arbol|normal|%d|%d|%.15f|no\n",numeroABuscar,cantidadNumeros,real);
		}
		encontrado = -1;
	}
	//* Arbol hilos
	for(ix = 0; ix < cantidadABuscar; ix++){
		int numeroABuscar = numerosABuscar[ix];
		uswtime(&usrtime11, &systime11, &walltime11);
		// Llamada al algoritmo
		BusquedaEnArbolHilos(arregloArbol, cantidadNumeros, numeroABuscar, &encontrado);
		uswtime(&usrtime21, &systime21, &walltime21);
		if(encontrado > 0)
		{
			printf("arbol|hilos|%d|%d|%.15f|si\n",numeroABuscar,cantidadNumeros,real);
		}
		else
		{
			printf("arbol|hilos|%d|%d|%.15f|no\n",numeroABuscar,cantidadNumeros,real);
		}
		encontrado = -1;
	}
}


void Shell(int * array, int n){ /*La función recibe el arreglo de números a ordenar asi como el tamaño del problema(cantidad de numeros a ordenar)*/
	int k; /*Almacena el tamaño de subarreglos,el cual siempre es menor al tamaño del problema n*/
	int i; /*Indice que nos permite realizar el recorrido de los sub-arreglos a partir de la posición k*/
	int j;  /*Indice que permite realizar el recorrido del subarreglo desde la posición 0 hasta la posición k*/
	int v;  /*Variable temporal que nos permite almacenar un número del arreglo a comparar*/
	
	k=n/2;  /*Divide en 2 el tamaño del problema*/
	while(k>=1){    /*Bucle que se realiza hasta que cada subarreglo no pueda dividirse mas */
		for(i=k;i<n;i++){  /*Ciclo que permite realizar el recorrido del arreglo a partir de la posición k*/
			v = array[i];  /* Se almacena el numero en la posición i del arreglo*/
			j = i - k;     
			while(j>=0 && array[j]>v){ /*Ciclo que permite comparar  un numero en posición j respecto a la variable temporal v*/
				array[j + k] = array[j]; /*En caso que el numero en posición j sea mayor se realiza una copia del número a la psición j+k del arreglo original*/
				j=j-k;
			}
			array[j + k] = v;  /*Se realiza la asignación del número almacenado en v a su nueva posición j+k en el arreglo*/
		}
		k=k/2;	/*Vuelve a efectuarse una subdivision del arreglo*/
	}
}

/*
 * Funcion para copiar un arreglo a otro, para no modificar el original
 *
 * http://stackoverflow.com/questions/8287109/how-to-copy-one-integer-array-to-another
 * */
int * intdup(int const * src, size_t len)
{
   int * p = malloc(len * sizeof(int));
   memcpy(p, src, len * sizeof(int));
   return p;
}
