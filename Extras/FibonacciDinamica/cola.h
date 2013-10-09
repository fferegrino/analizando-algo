/* 
 * File:   doublelinkedlist.h
 * Author: Antonio
 *
 * Created on 8 de octubre de 2013, 01:23 PM
 */

#ifndef COLA_H
#define	COLA_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct dllNodo {
        struct dllNodo * siguiente;
        long long dato;
    } DLLNodo;

    typedef struct cola  {
        DLLNodo * frente;
        DLLNodo * final;
    } Cola;

    void creaLista(Cola * cola) {
        //lista = (DoubleLinkedList *) malloc(sizeof (DoubleLinkedList));
        cola->frente = NULL;
        cola->final = NULL;
    }

    int listaVacia(Cola * cola) {
        if (cola->frente == NULL && cola->final == NULL) {
            return 1;
        }
        return 0;
    }

    void formar(Cola * cola, long long valor) {
        DLLNodo * nuevo = (DLLNodo *) malloc(sizeof (DLLNodo));
        nuevo->dato = valor;
        if(listaVacia(cola) == 1){
            nuevo->siguiente = NULL;
            cola->frente = nuevo;
            cola->final = nuevo;
        }
        else{
            cola->final->siguiente = nuevo;
            cola->final = nuevo;
        }
    }

    void imprimeCola(Cola * cola){
        DLLNodo * aux = cola->frente;
        while(aux != NULL){
            printf(" %ld ",aux->dato);
            aux = aux->siguiente;
        }
        printf("\n");
    }
    
    long long atender(Cola * cola){
        long long valor = -1;
        if(listaVacia(cola) != 1){
            DLLNodo * aux = cola->frente;
            cola->frente = aux->siguiente;
            valor = aux->dato;
            free(aux);
        }
        return valor;
    }
    
    long long valorPrincipio(Cola * cola){
        if(listaVacia(cola) != 1){
            return cola->frente->dato;
        }
        return -1;
    }
    long long valorFinal(Cola * cola){
        if(listaVacia(cola) != 1){
            return cola->final->dato;
        }
        return -1;
    }
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* DOUBLELINKEDLIST_H */

