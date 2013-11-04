#include <stdlib.h>
#include "colacodificacion.h"
#include "bits.h"


void iniciaCola(ColaCodificacion * cola) {
	cola->count = 0;
	cola->inicio = NULL;
	cola->final = NULL;
}

void formaCodificacion(ColaCodificacion * cola, char valor){
	NodoCola * nuevoNodo = (NodoCola *)malloc(sizeof(NodoCola));	
	nuevoNodo->valor = valor;
	nuevoNodo->siguiente = NULL;
	if(cola->final == NULL) {
		cola->final = nuevoNodo;
		cola->inicio = nuevoNodo;		
	}
	else{
		cola->final->siguiente = nuevoNodo;
		cola->final = nuevoNodo;
	}
	cola->count++;
}

void formaInicioCodificacion(ColaCodificacion * cola, char valor){
	NodoCola * nuevoNodo = (NodoCola *)malloc(sizeof(NodoCola));	
	nuevoNodo->valor = valor;
	nuevoNodo->siguiente = cola->inicio;
	cola->inicio = nuevoNodo;
	cola->count++;
}

char atiendeCola(ColaCodificacion * cola){
	NodoCola * aux = cola->inicio;
	char val = cola->inicio->valor;
	cola->inicio = cola->inicio->siguiente;
	cola->count--;
	free(aux);
	return val;
}

void atiendeTodos(ColaCodificacion * cola){
	while(cola->inicio != NULL){
		atiendeCola(cola);
	}
	cola->count == 0;
}
