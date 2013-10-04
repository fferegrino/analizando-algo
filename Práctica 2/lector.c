#include <stdio.h>
#include <stdlib.h>
#include "lector.h"

/*
 * Función encargada de leer números directamente
 * de la entrada estándar
 *
 * */
int* leeNumeros(int n)
{
	int* arreglo;
	// Reservamos espacio
	arreglo = (int*)malloc(sizeof(int)*n);
	int i = 0;
	for(;i < n; i++)
	{
		scanf("%d",&arreglo[i]);
	}
	return arreglo;
}
