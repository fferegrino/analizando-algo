/* 
 * File:   main.c
 * Author: fferegrino
 *
 * Created on 10 de octubre de 2013, 05:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int distancaLevenshtein(char cadenaOriginal[], char cadenaDestino[], int tamCadenaOriginal, int tamCadenaDestino);
int min(int a, int b);

/**
 * Punto de entrada al programa
 */
int main(int argc, char** argv) {
    char * cadenaDestino;
    char * cadenaOriginal;
    
    if (argc == 3) {
        // Leemos los argumentos de la consola
        cadenaOriginal = argv[1];
        cadenaDestino = argv[2];
    } else {
        // O ponemos unos por default
        cadenaOriginal = "Lorem ipsum dolor sit amet.";
        cadenaDestino = "Lorem ipsum dolor sit amet";
    }
    int l1 = strlen(cadenaOriginal);
    int l2 = strlen(cadenaDestino);
    
    // Cálculo de la distancia
    int w = distancaLevenshtein(cadenaOriginal, cadenaDestino, l1, l2);
    
    // Impresión del resultado
    printf("\nOperaciones minimas para llegar de \"%s\" a \"%s\": %d\n", cadenaOriginal, cadenaDestino, w);
    return (EXIT_SUCCESS);
}

/**
 * Función para calcular la distanca de Levenshtein entre cadenas
 * @param cadenaOriginal La cadena original
 * @param cadenaDestino La cadena a la que queremos llegar
 * @param tamCadenaOriginal El tamaño de la cadena original
 * @param tamCadenaDestino El tamaño de la cadena destino
 * @return 
 */
int distancaLevenshtein(char cadenaOriginal[], char cadenaDestino[], int tamCadenaOriginal, int tamCadenaDestino) {
    // Variables de control
    int i;
    int j;
    
    // Reservamos solo el espacio necesario
    int **matrizDistancias;
    matrizDistancias = (int **) malloc(sizeof (int *) * (tamCadenaOriginal + 1));
    for (i = 0; i < (tamCadenaOriginal + 1); i++) matrizDistancias[i] = (int *) malloc(sizeof (int) * (tamCadenaDestino + 1));

    // Comenzamos con los problemas más sencillos
    for (i = 0; i <= tamCadenaOriginal; i++)
        matrizDistancias[i][0] = i;
    for (j = 0; j <= tamCadenaDestino; j++)
        matrizDistancias[0][j] = j;
    
    // Vamos a ir rellenando las matrices y para ello es necesario reemplazarlos todos
    for (i = 1; i <= tamCadenaOriginal; i++) {
        for (j = 1; j <= tamCadenaDestino; j++) {
            if (cadenaOriginal[i - 1] == cadenaDestino[j - 1]) {
                // Si el caracter coincide, entonces no es necesario realizar operación alguna
                matrizDistancias[i][j] = matrizDistancias[i - 1][j - 1];
            } else {
                matrizDistancias[i][j] = min(   matrizDistancias[i - 1][j - 1], // Borrado
                        min(                    matrizDistancias[i][j - 1],     // Inserción
                                                matrizDistancias[i - 1][j]      // Sustitución
                        )) + 1; // Esta implementación considera que el coste de cada operación es 1
                                // se podría modificar para encontrar el menor costo con costos distintos
                                // de uno.
            }
        }
    }
    return matrizDistancias[tamCadenaOriginal][tamCadenaDestino];
}

/**
 * Función que retorna el mínimo de dos números
 * @param a 
 * @param b
 * @return 
 */
int min(int a, int b) {
    if (a <= b)
        return a;
    else
        return b;
}
