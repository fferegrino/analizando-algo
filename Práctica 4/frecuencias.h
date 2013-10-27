/* 
 * File:   frecuencias.h
 * Author: fferegrino
 *
 * Created on 23 de octubre de 2013, 03:47 PM
 */

#ifndef __FRECUENCIAS_H__
#define	__FRECUENCIAS_H__


typedef struct frecuencia{
    char caracter;
    int apariciones;
	char * codigo;
}Frecuencia;

typedef struct nodoFrecuencia{
    Frecuencia frecuencia;
    struct nodoFrecuencia * siguiente;
}NodoFrecuencia;

typedef struct listaFrecuencia{
    NodoFrecuencia * inicio;
    int length;
}ListaFrecuencia;

/**
 * Rellena una lista de frecuencias con los caracteres deseados
 * @param frecuencias La lista en la que se debe almacenar
 * @param caracteres El arreglo de caracteres que se quiere almacenar
 * @param length La longitud del arreglo
 */
void generaFrecuencias(ListaFrecuencia * frecuencias,char caracteres[], int length);

/**
 * Función encargada de regresar un arreglo de frecuencias dada una lista de ellas
 * el arreglo resultante está ordenado de forma ascendete de acuerdo a sus apariciones
 * 
 */ 
Frecuencia * vectorFrecuencias(ListaFrecuencia * frecuencias);

void ordenaFrecuenciasPorAparicion(Frecuencia * vector, int length);

#endif	/* __FRECUENCIAS_H__ */

