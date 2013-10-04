/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Libería encargada de concentrar los algoritmos de búsqueda
 * 9 de septiembre de 2013
 * Alumnos:
 * 	Feregrino Bolaños Antonio
 * 	
 * 	
 * 
 * */

/*
 * Función que busca en un arreglo mediante el uso
 * de un árbol binario de búsqueda
 * Parámetros:
 *	arreglo - el arreglo en el que se desea buscar
 *	n - la longitud del arreglo anterior
 *	valorABuscar - el valor a buscar dentro del arreglo
 *	bandera - nos indicará si el valor fue encontrado
 *
 * */
void BusquedaEnArbol(int * arreglo, int n, int valorABuscar, int * bandera);

/*
 * Función que busca en un arreglo mediante el uso
 * de un árbol binario de búsqueda repartiendo la carga
 * de trabajo en dos hilos
 * Parámetros:
 *	arreglo - el arreglo en el que se desea buscar
 *	n - la longitud del arreglo anterior
 *	valorABuscar - el valor a buscar dentro del arreglo
 *	bandera - nos indicará si el valor fue encontrado
 *
 * */
void BusquedaEnArbolHilos(int * arreglo, int n, int valorABuscar, int * bandera);

/*
 * Función que busca en un arreglo mediante el uso
 * del algoritmo de búsqueda secuencial
 * Parámetros:
 *	arreglo - el arreglo en el que se desea buscar
 *	valorABuscar - el valor a buscar dentro del arreglo
 * 	inicio - el punto inicial del segmento dentro del arreglo para buscar
 * 	final - el punto final del segmento dentro del arreglo para buscar
 *	bandera - nos indicará si el valor fue encontrado
 *
 * */
void BusquedaLineal(int * arreglo, int valorABuscar, int inicio, int final, int * encontrado);

/*
 * Función que busca en un arreglo mediante el uso
 * del algoritmo de búsqueda secuencial repartiendo la
 * carga en dos hilos
 * Parámetros:
 *	arreglo - el arreglo en el que se desea buscar
 *	valorABuscar - el valor a buscar dentro del arreglo
 * 	inicio - el punto inicial del segmento dentro del arreglo para buscar
 * 	final - el punto final del segmento dentro del arreglo para buscar
 *	bandera - nos indicará si el valor fue encontrado
 *
 * */
void BusquedaLinealHilos(int * arreglo, int valorABuscar, int inicio, int final, int * encontrado);


/*
 * Función que busca en un arreglo mediante el uso
 * del algoritmo de búsqueda binaria
 * Parámetros:
 *	arreglo - el arreglo en el que se desea buscar
 *	valorABuscar - el valor a buscar dentro del arreglo
 * 	inicio - el punto inicial del segmento dentro del arreglo para buscar
 * 	final - el punto final del segmento dentro del arreglo para buscar
 *	bandera - nos indicará si el valor fue encontrado
 *
 * */	
void BusquedaBinaria(int * arreglo, int valorABuscar, int inicio, int final, int * encontrado);

/*
 * Función que busca en un arreglo mediante el uso
 * del algoritmo de búsqueda binaria repartiendo la
 * carga en dos hilos
 * Parámetros:
 *	arreglo - el arreglo en el que se desea buscar
 *	valorABuscar - el valor a buscar dentro del arreglo
 * 	inicio - el punto inicial del segmento dentro del arreglo para buscar
 * 	final - el punto final del segmento dentro del arreglo para buscar
 *	bandera - nos indicará si el valor fue encontrado
 *
 * */
void BusquedaBinariaHilos(int * arreglo, int valorABuscar, int inicio, int final, int * encontrado);

