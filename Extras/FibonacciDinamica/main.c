/* 
 * File:   main.c
 * Author: Antonio
 *
 * Created on 8 de octubre de 2013, 01:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"


long long fibonacci(int n);

/*
 * 
 */
int main(int argc, char** argv) {

    long long fibonachi = fibonacci(46);

    printf(" %ld ", fibonachi);

    return (EXIT_SUCCESS);
}

long long fibonacci(int n) {
    LinkedList lista;
    creaLista(&lista);
    insertaValor(&lista, 0);
    insertaValor(&lista, 1);
    int i;
    for (i = 2; i <= n; i++) {
        long long fi1 = eliminaCabeza(&lista);
        long long fi2 = valorCabeza(&lista);
        insertaValor(&lista, fi1 + fi2);
    }
    return valorCola(&lista);
}