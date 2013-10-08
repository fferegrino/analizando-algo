/* 
 * File:   doublelinkedlist.h
 * Author: Antonio
 *
 * Created on 8 de octubre de 2013, 01:23 PM
 */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct dllNodo {
        struct dllNodo * siguiente;
        long long dato;
    } DLLNodo;

    typedef struct linkedList {
        DLLNodo * frente;
        DLLNodo * cola;
    } LinkedList;

    void creaLista(LinkedList * lista) {
        //lista = (DoubleLinkedList *) malloc(sizeof (DoubleLinkedList));
        lista->frente = NULL;
        lista->cola = NULL;
    }

    int listaVacia(LinkedList * lista) {
        if (lista->frente == NULL && lista->cola == NULL) {
            return 1;
        }
        return 0;
    }

    void insertaValor(LinkedList * lista, long long valor) {
        DLLNodo * nuevo = (DLLNodo *) malloc(sizeof (DLLNodo));
        nuevo->dato = valor;
        if(listaVacia(lista) == 1){
            nuevo->siguiente = NULL;
            lista->frente = nuevo;
            lista->cola = nuevo;
        }
        else{
            lista->cola->siguiente = nuevo;
            lista->cola = nuevo;
        }
    }

    void imprimeLista(LinkedList * lista){
        DLLNodo * aux = lista->frente;
        while(aux != NULL){
            printf(" %ld ",aux->dato);
            aux = aux->siguiente;
        }
        printf("\n");
    }
    
    long long eliminaCabeza(LinkedList * lista){
        long long valor = -1;
        if(listaVacia(lista) != 1){
            DLLNodo * aux = lista->frente;
            lista->frente = aux->siguiente;
            valor = aux->dato;
            free(aux);
        }
        return valor;
    }
    
    long long valorCabeza(LinkedList * lista){
        if(listaVacia(lista) != 1){
            return lista->frente->dato;
        }
        return -1;
    }
    long long valorCola(LinkedList * lista){
        if(listaVacia(lista) != 1){
            return lista->cola->dato;
        }
        return -1;
    }
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* DOUBLELINKEDLIST_H */

