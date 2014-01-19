/*
 * File:   codificacion.h
 * Author: fferegrino
 *
 * Created on 25 de octubre de 2013, 04:15 PM
 */

#ifndef __CODIFICACION_H__
#define	__CODIFICACION_H__

#include "ListaFrecuencias.h"
#include "ColaCodificacion.h"

typedef struct nodoArbol {
	Frecuencia * frecuencia;
	int peso;
	struct nodoArbol  * nodo0;
	struct nodoArbol  * nodo1;
	unsigned visitado : 1;
}NodoArbol;


namespace RuntimeComponent {

	class Codificacion sealed
	{

	public:
		void creaArbolCodificacion(Frecuencia * frecuencias, int length);
		int escribeBits(char * salida, int salidaLength, long pointer, char c, Frecuencia * frecuencias, int length);
		void decodificaBits(char * codificado, long longitudCodificado, char * salida);
		void obtieneCaminoR(NodoArbol * arbol, RuntimeComponent::ColaCodificacion * cola);
		void reordenaArboles();
		void generaUnicoArbol();
		void ordenaVectorFrecuenciasPorCaracter(Frecuencia * frecuencias, int length);
		void asignaCodificacion(Frecuencia * frecuencias, int length, RuntimeComponent::ColaCodificacion * cola);
		int buscaFrecuencia(Frecuencia * frecuencias, int inicio, int final, char c);
	private:
		// En este doble apuntador se almacenará la colección de frecuencias
		NodoArbol ** bosqueHuffman;
		int nodos;
		// Métodos //

	};
}
#endif	/* __CODIFICACION_H__ */