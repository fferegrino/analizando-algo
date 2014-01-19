/*
 * File:   frecuencias.h
 * Author: fferegrino
 *
 * Created on 23 de octubre de 2013, 03:47 PM
 */

#ifndef __LISTAFRECUENCIAS_H__
#define	__LISTAFRECUENCIAS_H__


typedef struct frecuencia{
	char caracter;
	int apariciones;
	char * codigo;
}Frecuencia;

typedef struct nodoFrecuencia{
	Frecuencia frecuencia;
	struct nodoFrecuencia * siguiente;
}NodoFrecuencia;


namespace RuntimeComponent{

	class ListaFrecuencias sealed
	{

	public:
		NodoFrecuencia * inicio;
		int length;
		/**
		 * Rellena una lista de frecuencias con los caracteres deseados
		 * @param frecuencias La lista en la que se debe almacenar
		 * @param caracteres El arreglo de caracteres que se quiere almacenar
		 * @param length La longitud del arreglo
		 */
		void generaFrecuencias(char caracteres[], int length);

		/**
		 * Función encargada de regresar un arreglo de frecuencias dada una lista de ellas
		 * el arreglo resultante está ordenado de forma ascendete de acuerdo a sus apariciones
		 *
		 */
		Frecuencia * vectorFrecuencias();

		void ordenaFrecuenciasPorAparicion(Frecuencia * vector);

	private:

		/**
		* Función interna para insertar o actualizar la frecuencia de un elemento
		* @param frecuencias
		* @param caracter
		*/
		void insertaFrecuencia(char caracter);

	};
}
#endif	/* __LISTAFRECUENCIAS_H__ */

