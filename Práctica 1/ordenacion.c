#include "ordenacion.h"
#include "arbol.h"

/*
 * Función del algoritmo de inserción
 * Recibe:
 *	array, el arreglo a ordenar
 *  n, el tamaño del arreglo
 * */
void Insercion(int * array, int n)
{
	// Inicializamos una variable
	// auxiliar para recorrer el arreglo
	int ix = 1;
	for(;ix < n; ++ix) // Recorremos el arreglo
	{
		// Asignamos el valor actual a
		// una variable temporal
		int temp = array[ix];
		// Nos ubicamos en la posición anterior a 
		// la actual para ir revisando los valores
		int j = ix - 1;
		while((array[j] > temp) && (j >= 0))
		{
			// Nos vamos moviendo hacia atrás
			// hasta que encontremos la nueva
			// ubicación de nuestro valor
			array[j + 1] = array[j];
			j--;
		}
		// Lo asignamos
		array[j + 1] = temp;
	}
}

/*
 * Función del algoritmo de inserción
 * Recibe:
 *	array, el arreglo a ordenar
 *  n, el tamaño del arreglo
 * */
void Arbol(int * array, int n)
{
	// Variable que nos ayudará a recorrer
	// el arreglo en su totalidad
	int ix = 0;
	// Variable para "almacenar" el árbol
	arbol t;
	// Creamos nuestro árbol
	Iniciar(&t);
	for(;ix < n; ++ix)
	{
		// Para cada elemento en nuestro arreglo
		// creaamos un nodo en el árbol
		NuevoNodo(&t,array[ix]);
	}
	// Reemplazamos los valores iniciales de
	// nuestro arreglo por los leídos
	// inorden del árbol
	RellenaInorden(&t, array);
}

/*
*FunciÃ³n para el algoritmo de ordenamiento de Burbuja Simple
*
*/
void Burbuja(int * array, int n) /*AquÃ­ se colocan los argumentos que recibira nuestra funciÃ³n, en este caso el arreglo de nÃºmeros en desorde y el tamaÃ±o de problema n*/
{
	int temp=0,i,j; /*Inicializamos las variables que utilizaremos, los contadores i y j, ademÃ¡s de temp la que nos ayuda a almacenar el contenido de una posiciÃ³n del arreglo*/
	for(i=1;i<n;i++) /*Aqui tenemos los bucles que recorren el arreglo en su totalidad*/
  {
                  for(j=0;j<n-1;j++)
                  {
                     if(array[j]>array[j+1])/*Esta decisiÃ³n nos ayuda a saber si el contenido de la posiciÃ³n actual es mayor que la siguiente y si es asÃ­ intercambiarlas*/
                       {
                                                temp=array[j];
                                                array[j]=array[j+1];/*En esta parte se realiza la asignaciÃ³n y el cambio de posiciÃ³n del contenido del arreglo*/
                                                array[j+1]=temp;
                       }
                  }
  } 

}

/*FunciÃ³n para el algoritmo de ordenamiento SelecciÃ³n*/
void Seleccion(int * array, int n)/*AquÃ­ se colocan los argumentos que recibira nuestra funciÃ³n, en este caso el arreglo de nÃºmeros en desorde y el tamaÃ±o de problema n*/
{
	int i,g,temp=0,p=0; /*Inicializamos las variables que utilizaremos, los contadores i,g y p otro contador auxiliar, ademÃ¡s de temp la que nos ayuda a almacenar el contenido de una posiciÃ³n del arreglo*/
	for(g=0;g<n-1;g++)
		p=g;
	for(i=g+1;i<n-1;i++)/*Aqui tenemos los bucles que recorren el arreglo en su totalidad*/
	{
		if(array[i]<array[p])/*En esta parte comparamos el contenido de la posiciÃ³n del arreglo donde encontramos el menor con las siguientes posiciones y asÃ­ sucesivamente hasta encontrar el menor de todo el arreglo y colocarlo al inicio*/
			p=i;
		if(p!=g)
		{
			temp=array[p];
			array[p]=array[g];/*De igual manera aquÃ­ intercambiamos las posiciones de acuerdo a como vamos 		encontrando al menor del arreglo*/
			array[g]=temp;
		}
	}

}

/*Función para el ordenamiento de burbuja mejorada*/
void BurbujaMejorada(int * array,int n){  /*La función recibe el arreglo de números a ordenar asi como el tamaño del problema(cantidad de numeros a ordenar)*/
   	int i;               /*Indice que nos permitira hacer un recorrido al arreglo de números*/
	int j;               /*Indice que nos permitira hacer un recorrido al arreglo de números */
	int temp;            /*Permite el almacenamiento temporal de un número del arreglo el cual auxiliará el cambio de posición de un número a ordenar*/

	for(i=0;i<n;i++){                /*Se realiza un recorrido general del  arreglo numérico*/
		for(j=0;j<i;j++){            /*Se realiza un recorrido general del  arreglo numérico */   
			if(array[i]<array[j]){   /*Compara si el elemento en posición i es menor al elemeto en posición actual(indice j)*/
				temp = array[j];     /*En caso que el elemento mayor se encuentre en la posición j, el numero contendo se asigna a la variable temporal*/
				array[j] = array[i];  /*Se realiza el cambio de psición de los números comparados auxiliándose de la variable temp*/
				array[i] = temp;     
			}
		}
	}
	

}
/*Función de ordenamiento Shell*/
void Shell(int * array, int n){ /*La función recibe el arreglo de números a ordenar asi como el tamaño del problema(cantidad de numeros a ordenar)*/
	int k; /*Almacena el tamaño de subarreglos,el cual siempre es menor al tamaño del problema n*/
	int i; /*Indice que nos permite realizar el recorrido de los sub-arreglos a partir de la posición k*/
	int j;  /*Indice que permite realizar el recorrido del subarreglo desde la posición 0 hasta la posición k*/
	int v;  /*Variable temporal que nos permite almacenar un número del arreglo a comparar*/
	
	k=n/2;  /*Divide en 2 el tamaño del problema*/
	while(k>=1){    /*Bucle que se realiza hasta que cada subarreglo no pueda dividirse mas */
		for(i=k;i<n;i++){  /*Ciclo que permite realizar el recorrido del arreglo a partir de la posición k*/
			v = array[i];  /* Se almacena el numero en la posición i del arreglo*/
			j = i - k;     
			while(j>=0 && array[j]>v){ /*Ciclo que permite comparar  un numero en posición j respecto a la variable temporal v*/
				array[j + k] = array[j]; /*En caso que el numero en posición j sea mayor se realiza una copia del número a la psición j+k del arreglo original*/
				j=j-k;
			}
			array[j + k] = v;  /*Se realiza la asignación del número almacenado en v a su nueva posición j+k en el arreglo*/
		}
		k=k/2;	/*Vuelve a efectuarse una subdivision del arreglo*/
	}

}

