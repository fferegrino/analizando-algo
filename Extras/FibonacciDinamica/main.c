#include <stdio.h>
#include <stdlib.h>
#include "cola.h"


long long fibonacciCola(int n);
long long fibonacciArreglo(int n);

/*
 * 
 */
int main(int argc, char** argv) {

    long long fiboL = fibonacciCola(20);
    printf("Lista\t%ld\n", fiboL);

    long long fiboA = fibonacciArreglo(20);
    printf("Arreglo\t%ld\n", fiboA);

    return (EXIT_SUCCESS);
}

long long fibonacciCola(int n) {
    Cola cola;
    if (n == 0) return 0;
    if (n == 1) return 1;
    creaLista(&cola);
    formar(&cola, 0);
    formar(&cola, 1);
    int i;
    for (i = 2; i <= n; i++) {
        // Quitamos el elemento menos reciente
        long long fi1 = atender(&cola);
        // Obtenemos el valor del siguiente más reciente
        long long fi2 = valorPrincipio(&cola);
        // Almacenamos el resultado en la cola
        formar(&cola, fi1 + fi2);
    }
    return valorFinal(&cola);
}

long long fibonacciArreglo(int n) {
    long long * lista;
    if (n == 0) return 0;
    if (n == 1) return 1;
    lista = (long long *) malloc(sizeof (long long) * n);
    lista[0] = 0;
    lista[1] = 1;
    int i;
    for (i = 2; i <= n; i++) {
        lista[i] = lista[i - 1] + lista[i - 2];
    }
    return lista[n];
}