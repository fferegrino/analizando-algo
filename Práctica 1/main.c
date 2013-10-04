#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lector.h"
#include "ordenacion.h"
#include "tiempo.h"
#include "arbol.h"

int * intdup(int const * src, size_t len);
void printArr(int const * src, int cantidad);

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Error en la ejecucion del programa, intente: practica1 #deArgumentos\n");
		return 0;
	}
	// El tamano del arreglo a procesar
	int cantidadNumeros = atoi(argv[1]);
	// El arreglo original
	int * arregloOriginal = leeNumeros(cantidadNumeros);
	// Variable de control para ciclos
	int i = 0;
	// Variables para controlar el tiempo
	double 	usrtime11, systime11, walltime11,
		usrtime21, systime21, walltime21,
		usrtime12, systime12, walltime12,
		usrtime22, systime22, walltime22,
		usrtime13, systime13, walltime13,
		usrtime23, systime23, walltime23,
		usrtime14, systime14, walltime14,
		usrtime24, systime24, walltime24,
		usrtime15, systime15, walltime15,
		usrtime25, systime25, walltime25,
		usrtime16, systime16, walltime16,
		usrtime26, systime26, walltime26,
		real, user, sys, cpuwall;

	// Imprimimos los encabezados del archivo:
	//printf("algoritmo|cantidad|real|user|sys|cpu/Wall\n");

	/*
	 * Algoritmo de insercion
	 * */
	int * arregloInsercion = intdup(arregloOriginal, cantidadNumeros);
	uswtime(&usrtime11, &systime11, &walltime11);
	Insercion(arregloInsercion,cantidadNumeros);
	uswtime(&usrtime21, &systime21, &walltime21);
	real = walltime21 - walltime11;
	user = usrtime21 - usrtime11;
	sys = systime21 - systime11;
	cpuwall = ((user + sys) * 100.0) / real;
	printf("Insercion|%d|%.10f|%.10f|%.10f|%.10f\n",cantidadNumeros,real,user,sys,cpuwall);
	free(arregloInsercion);
	/* Termina el algoritmo */

	/*
	 * Algoritmo BST
	 * */
	int * arregloBST = intdup(arregloOriginal, cantidadNumeros);
	uswtime(&usrtime12, &systime12, &walltime12);
	Arbol(arregloBST,cantidadNumeros);
	uswtime(&usrtime22, &systime22, &walltime22);
	real = walltime22 - walltime12;
	user = usrtime22 - usrtime12;
	sys = systime22 - systime12;
	cpuwall = ((user + sys) * 100.0) / real;
	printf("Arbol binario|%d|%.10f|%.10f|%.10f|%.10f\n",cantidadNumeros,real,user,sys,cpuwall);
	free(arregloBST);
	/* Termina el algoritmo */

	/*
	 * Algoritmo Burbuja Simple
	 * */
	int * arregloBurbuja = intdup(arregloOriginal, cantidadNumeros);
	uswtime(&usrtime13, &systime13, &walltime13);
	Burbuja(arregloBurbuja,cantidadNumeros);
	uswtime(&usrtime23, &systime23, &walltime23);
	real = walltime23 - walltime13;
	user = usrtime23 - usrtime13;
	sys = systime23 - systime13;
	cpuwall = ((user + sys) * 100.0) / real;
	printf("Burbuja Simple|%d|%.10f|%.10f|%.10f|%.10f\n",cantidadNumeros,real,user,sys,cpuwall);
	free(arregloBurbuja);
	/* Termina el algoritmo */

	/*
	 * Algoritmo Seleccion
	 * */
	int * arregloSeleccion = intdup(arregloOriginal, cantidadNumeros);
	uswtime(&usrtime14, &systime14, &walltime14);
	Seleccion(arregloSeleccion,cantidadNumeros);
	uswtime(&usrtime24, &systime24, &walltime24);
	real = walltime24 - walltime14;
	user = usrtime24 - usrtime14;
	sys = systime24 - systime14;
	cpuwall = ((user + sys) * 100.0) / real;
	printf("Seleccion|%d|%.10f|%.10f|%.10f|%.10f\n",cantidadNumeros,real,user,sys,cpuwall);
	free(arregloSeleccion);
	/* Termina el algoritmo */

	/*
	 * Algoritmo Burbuja Mejorada
	 * */
	int * arregloBurbujaM = intdup(arregloOriginal, cantidadNumeros);
	uswtime(&usrtime15, &systime15, &walltime15);
	BurbujaMejorada(arregloBurbujaM,cantidadNumeros);
	uswtime(&usrtime25, &systime25, &walltime25);
	real = walltime25 - walltime15;
	user = usrtime25 - usrtime15;
	sys = systime25 - systime15;
	cpuwall = ((user + sys) * 100.0) / real;
	printf("Burbuja Mejorada|%d|%.10f|%.10f|%.10f|%.10f\n",cantidadNumeros,real,user,sys,cpuwall);
	free(arregloBurbujaM);
	/* Termina el algoritmo */

	/*
	 * Algoritmo Shell
	 * */
	int * arregloShell= intdup(arregloOriginal, cantidadNumeros);
	uswtime(&usrtime16, &systime16, &walltime16);
	Shell(arregloShell,cantidadNumeros);
	uswtime(&usrtime26, &systime26, &walltime26);
	real = walltime26 - walltime16;
	user = usrtime26 - usrtime16;
	sys = systime26 - systime16;
	cpuwall = ((user + sys) * 100.0) / real;
	printf("Shell|%d|%.10f|%.10f|%.10f|%.10f\n",cantidadNumeros,real,user,sys,cpuwall);
	free(arregloShell);
	/* Termina el algoritmo */

	return 0;
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

void printArr(int const * src, int cantidad)
{
	int ix = 0;
	for(;ix < cantidad;++ix)
	{
		printf("%3d - ",src[ix]);
	}
	printf("\n\n",src[ix]);
}
