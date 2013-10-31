/* 
 * File:   codificacion.h
 * Author: fferegrino
 *
 * Created on 25 de octubre de 2013, 04:15 PM
 */

#ifndef __CODIFICACION_H__
#define	__CODIFICACION_H__

#include "frecuencias.h"

typedef struct nodoArbol {
	Frecuencia * frecuencia;
	int peso;
	struct nodoArbol  * nodo0;
	struct nodoArbol  * nodo1;
	unsigned visitado : 1;
}NodoArbol;

void creaArbolCodificacion(Frecuencia * frecuencias, int length);

int escribeBits(char * salida, int salidaLength, long pointer, char c, Frecuencia * frecuencias, int length);

void decodificaBits(char * codificado, long longitudCodificado, char * salida);

#endif	/* __CODIFICACION_H__ */