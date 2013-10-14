/* 
 * File:   main.c
 * Author: fferegrino
 *
 * Created on 10 de octubre de 2013, 05:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int empatar(char u[], char v[], int n, int m);
int min(int a, int b);

/**
 * Punto de entrada al programa
 */
int main(int argc, char** argv) {
    char * cadena2;
    char * cadena1;
    if (argc == 3) {
        cadena1 = argv[1];
        cadena2 = argv[2];
    } else {
        cadena1 = "Lorem ipsum dolor sit amet.";
        cadena2 = "Lorem ipsum dolor sit amet";
    }
    int l1 = strlen(cadena1);
    int l2 = strlen(cadena2);
	int i;
    int w = empatar(cadena1, cadena2, l1, l2);
    printf("\nOperaciones para llegar de %s a %s: %d\n", cadena1, cadena2, w);
	return (EXIT_SUCCESS);
}

int empatar(char u[], char v[], int n, int m) {
    int i;
    int j;
    int **matrizDistancias;
    matrizDistancias = (int **) malloc(sizeof (int *) * (n + 1));
    for (i = 0; i < (n + 1); i++) matrizDistancias[i] = (int *) malloc(sizeof (int) * (m + 1));


    for (i = 0; i <= n; i++)
        matrizDistancias[i][0] = i;
    for (j = 0; j <= m; j++)
        matrizDistancias[0][j] = j;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (u[i-1] == v[j-1]) {
                matrizDistancias[i][j] = matrizDistancias[i - 1][j - 1];
            } else {
                matrizDistancias[i][j] = min(matrizDistancias[i - 1][j - 1],min(matrizDistancias[i][j - 1], matrizDistancias[i - 1][j])) + 1;
            }
        }
    }
    return matrizDistancias[n][m];
	
}

int min(int a, int b) {
    if (a <= b)
	return a;
	else 
	return b;
}
