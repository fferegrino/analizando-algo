/* 
 * File:   bits.c
 * Author: fferegrino
 *
 * Created on 3 de noviembre de 2013, 04:15 PM
 */


#include "bits.h"


/**
 * Función encargada de poner el bit elegido en 1
 * @param array El arreglo en el que queremos modificar
 * @param pos La posición del bit que queremos cambiar
 */ 
void pon1(char * array, int pos){
	// Obtenemos el índice dentro del arreglo
	int ix = pos / BYTE;
	// Obtenemos la posición del bit dentro del arreglo
	int i = pos - (BYTE * ix);
	i =  BYTE - i - 1;
	PONE_1(array[ix],i);
}

/**
 * Función encargada de poner el bit elegido en 0
 * @param array El arreglo en el que queremos modificar
 * @param pos La posición del bit que queremos cambiar
 */
void pon0(char * array, int pos){
	// Obtenemos el índice dentro del arreglo
	int ix = pos / BYTE;
	// Obtenemos la posición del bit dentro del arreglo
	int i = pos - (BYTE * ix);
	i =  BYTE - i - 1;
	PONE_0(array[ix],i);
}

/**
 * Función encargada de obtener el valor del bit en el arreglo
 * @param array El arreglo en el que queremos conocer
 * @param pos La posición del bit que queremos obtener
 */
int valorBit(char * array, int pos){
	// Obtenemos el índice dentro del arreglo
	int ix = pos / BYTE;
	// Obtenemos la posición del bit dentro del arreglo
	int i = pos - (BYTE * ix);
	i =  BYTE - i - 1;
	return COGEBIT(array[ix],i);
}
