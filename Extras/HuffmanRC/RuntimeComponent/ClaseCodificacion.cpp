#include "pch.h"
#include "ClaseCodificacion.h"
#include <stdio.h>
#include <stdlib.h>
#include "Codificacion.h"
#include "ColaCodificacion.h"
#include "Bit.h"
#include "ListaFrecuencias.h"

using namespace RuntimeComponent;
using namespace Platform;

#define BUFFER 1024 
// Usada para almacenar temporalmente los valores del archivo
char buffer[BUFFER];
// Nuestras variables para los archivos
FILE * entrada;
FILE * tablaFrecuenciasArchivo;
FILE * out;

char * salida;
char * codificado;
int leidos;
long leidosTotal = 0;
long bytesTotal = 0;
int bitsEscritosReal = 0;
Frecuencia * v;

ClaseCodificacion::ClaseCodificacion()
{
}


int ClaseCodificacion::ConvierteCaracteres(const Platform::Array<byte>^ origen, char ** out){
	int i = 0;
	*out = (char *)malloc(origen->Length * sizeof(char));
	for (i = 0; i < origen->Length; i++){
		(*out)[i] = (char)origen[i];
	}
	return origen->Length;
}

//int ClaseCodificacion::Codificar(Platform::String^ archivoOrigen, Platform::String^ archivoSimbolos, Platform::String^ archivoDestino){
int ClaseCodificacion::Codificar(const Platform::Array<byte>^ origen,
	Platform::WriteOnlyArray<byte>^ simbolos,
	Platform::WriteOnlyArray<byte>^ destino){
	ListaFrecuencias * f = new ListaFrecuencias();
	Codificacion * codificacion = new Codificacion();
	f->inicio = NULL;

	char * in;
	ConvierteCaracteres(origen, &in);
	f->generaFrecuencias(in, origen->Length);

	//salida = (char *)malloc(sizeof(char)* leidosTotal);
	salida = (char *)malloc(sizeof(char)* origen->Length);
	// Obtenemos el arreglo de frecuencias
	v = f->vectorFrecuencias();
	// Generamos la codificación mediante la llamada a este método
	codificacion->creaArbolCodificacion(v, f->length);


	int resultadoEscritura = 0;
	int iaux = 0;
	for (iaux = 0; iaux < origen->Length; iaux++){
		resultadoEscritura = codificacion->escribeBits(salida, origen->Length * 8, bitsEscritosReal, in[iaux], v, f->length);
		if (resultadoEscritura < 0) break;
		bitsEscritosReal += resultadoEscritura;
	}

	bytesTotal = (bitsEscritosReal / 8); // Determinamos cuantos bytes ocupará el nuevo archivo
	int padding = bytesTotal % 8;
	if (padding > 0){
		bytesTotal++;
	}

	int ii;
	//destino =  *(new Platform::WriteOnlyArray<byte, 1>^());
	for (ii = 0; ii < bytesTotal; ii++){
		destino->set(ii, (byte)salida[ii]);
	}

	/*
	// Imprimimos la tabla de frecuencias a un archivo para conservarla
	//imprimeTablaFrecuencias(v, f.length, padding, leidosTotal, argv[3]);
	*/
	
	

	return bytesTotal;// f->length; //origen->Length;
}

int ClaseCodificacion::Decodificar(Platform::String^ archivoOrigen, Platform::String^ archivoSimbolos, Platform::String^ archivoDestino){
	return 0;


}