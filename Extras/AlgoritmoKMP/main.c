/* 
 * File:   main.c
 * Author: Antonio
 *
 * Created on October 10, 2013, 2:55 PM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void construyeVectorFallo(char palabra[], int longitudPalabra, int vector[]);
int encuentraOcurrenciasKMP(char palabra[], char patron[], int longitudPalabra, int longitudPatron);

/**
 * Punto de entrada al programa
 */
int main(int argc, char** argv) {
    char * cadenaTest;
    char * cadenaBuscar;
    
    if (argc == 3) {
        // Leemos los argumentos de la consola
        cadenaTest = argv[1];
        cadenaBuscar = argv[2];
    }else{
        // O seleccionamos unos por default
        cadenaTest = "Lorem ipsum dolor sit amet.";
        cadenaBuscar = "m";
    }
    
    int p1l = strlen(cadenaTest);
    int p2l = strlen(cadenaBuscar);
    int s = encuentraOcurrenciasKMP(cadenaTest, cadenaBuscar, p1l, p2l);
    
    // Imprimimos el resultado
    printf("Ocurrencias de \"%s\" en \"%s\": %d\n",cadenaBuscar, cadenaTest,s);
    return (EXIT_SUCCESS);
}

/**
 * Función encargada de construir el vector de fallo
 * @param palabra La palabra en la que vamos a buscar
 * @param longitudPalabra La longitud de la palabra
 * @param vector El lugar en el que se almacenará el vector
 */
void construyeVectorFallo(char palabra[], int longitudPalabra, int vector[]) {
    // Variables de control
    int i = 1;
    int j = 0;

    // Las dos primeras posiciones son fijas
    vector[0] = -1;
    vector[1] = 0;

    // Relleno del vector
    while (i < longitudPalabra) {
        if (palabra[j] == palabra[i]) {
            // Un caracter previo coincide
            vector[i] = j + 1;
            i++;
            j++;
        } else if (j > 0) {
            j = vector[j - 1];
        } else {
            vector[i] = 0;
            i++;
        }
    }
}

/**
 * Función principal, encargada de encontrar las ocurrencias de una cadena dentro de otra
 * @param palabraBuscar La cadena en la que se buscarán las ocurrencias
 * @param patron El patrón que se buscará en la cadena
 * @param tamanoPalabra La longitud de la palabra en la que se buscará        
 * @param tamanoPatron
 * @return 
 */
int encuentraOcurrenciasKMP(char palabraBuscar[], char patron[], int tamanoPalabra, int tamanoPatron) {
    // Variables de control
    int m = 0;
    int i = 0;
    int rep = 0;
    // Vector de fallo
    int * vector = (int *) malloc(sizeof (int) * tamanoPalabra);

    if (tamanoPalabra >= tamanoPatron) {
        // Construcción de la tabla de fallo
        construyeVectorFallo(palabraBuscar, tamanoPalabra, vector);
        
        while (m <= (tamanoPalabra - tamanoPatron)) {
            if (patron[i] == palabraBuscar[m + i]) {
                if (i == (tamanoPatron - 1)) {
                    rep++; // Incremento de las ocurrencias
                    m += i - vector[i];
                    if (i > 0)
                        i = vector[i];

                } else {
                    i++;
                }
            } else {
                m += i - vector[i];
                if (i > 0)
                    i = vector[i];
            }
        }
    }
    return rep;
}