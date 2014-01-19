#include <stdlib.h>
#include "ColaCodificacion.h"
//#include "bits.h"

using namespace RuntimeComponent;

ColaCodificacion::ColaCodificacion(){
	this->count = 0;
	this->inicio = NULL;
	this->final = NULL;
}

void ColaCodificacion::formaCodificacion(char valor){
	NodoCola * nuevoNodo = (NodoCola *)malloc(sizeof(NodoCola));	
	nuevoNodo->valor = valor;
	nuevoNodo->siguiente = NULL;
	if (this->final == NULL) {
		this->final = nuevoNodo;
		this->inicio = nuevoNodo;
	}
	else{
		this->final->siguiente = nuevoNodo;
		this->final = nuevoNodo;
	}
	this->count++;
}

void ColaCodificacion::formaInicioCodificacion(char valor){
	NodoCola * nuevoNodo = (NodoCola *)malloc(sizeof(NodoCola));	
	nuevoNodo->valor = valor;
	nuevoNodo->siguiente = this->inicio;
	this->inicio = nuevoNodo;
	this->count++;
}

char ColaCodificacion::atiendeCola(){
	NodoCola * aux = this->inicio;
	char val = this->inicio->valor;
	this->inicio = this->inicio->siguiente;
	this->count--;
	free(aux);
	return val;
}

void ColaCodificacion::atiendeTodos(){
	while(this->inicio != NULL){
		atiendeCola();
	}
	this->count = 0;
}
