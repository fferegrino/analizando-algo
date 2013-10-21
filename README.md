analizando-algo
===============

#### Códigos inspirados por la materia Análisis de Algoritmos de la ESCOM

En esta unidad de aprendizaje (que he de confesar es mi favorita) tenemos que implementar muchos algoritmos, y es por eso que decidí crear este repositorio, para mantener la historia de casi todo lo que hice en ella.

A lo largo del semestre tendremos que desarrollar diversas prácticas para analizar el comportamiento de las técnicas de algoritmia más reconocidas
Aquí es donde iré colocando el código de dichas prácticas, así como algunos ejemplos y casos de prueba.

Cada práctica tendrá su propia carpeta; podrá ser compilada y ejecutada con solo bajar la carpeta correspondiente, a menos que se indique lo contrario.
Muchas (si no es que todas D:) están escritas en C, para Linux, esto debido a la librería empleada para medir los tiempos que consume la ejecución del algoritmo. Para facilitar la compilación cada práctica cuenta con un archivo Makefile, el cual contiene todas las instrucciones para compilar y ejecutar las prácticas.

Las que estén preparadas para correrse en un entorno Windows, contendrán un archivo `.bat` análogo al `Makefile`, que se encargará de las labores de compilación y ejecución del programa.

***

##### Las prácticas son las siguientes:

#### Práctica 1: "Pruebas a posteriori (Algoritmos de ordenamiento)" 
Con base en el archivo de entrada proporcionado que tiene 200,000 números diferentes. Ordenarlo bajo los siguientes métodos de ordenamiento y comparar experimentalmente las complejidades de estos.

* Burbuja (Bubble Sort)
* Burbuja Simple
* Burbuja Mejorada
* Inserción (Insertion Sort)
* Selección (Selection Sort )
* Shell (Shell Sort)
* Ordenamiento con árbol binario de busqueda (Binary Search Tree)
 
[Práctica 1](/Práctica 1)

***

#### Práctica 2: "Análisis temporal y notación de orden (Algoritmos de busqueda)"
Con base en el ordenamiento obtenido a partir del archivo de entrada de la práctica 01 que tiene 200,000 números diferentes.
Realizar la búsqueda de elementos bajo 3 métodos de búsqueda y variantes con procesos ligeros, realizar el análisis teórico y experimental de las complejidades; así como encontrar las cotas de los algoritmos.
* Búsqueda lineal o secuencial (No recursiva)
* Búsqueda binaria o dicotómica (No recursiva)
* Búsqueda en un árbol binario de búsqueda (No recursiva)

Modificar los tres algoritmos para trabajar con procesos ligeros (Hilos).
 
[Práctica 2](/Práctica 2)

***

#### Práctica 3: "Divide y vencerás (Rotación de una imagen)"
Implementar el algoritmo de rotación de imágenes que emplea la técnica divide y vencerás. La imágen a girar es cuadrada, y es un .bmp de 24 bits.
 
[Práctica 3](/Práctica 3)

***

#### Extras
En este folder están otros códigos relacionados con la asignatura, provenientes de tareas, investigaciones o mi simple curiosidad.
Al momento están ahí:

1. Implementación cálculo de la sucesión de Fibonacci usando programación dinámica
2. Algoritmo de Knuth-Morris-Prat para la búsqueda de subcadenas
3. Algoritmo que calcula la distancia de Levenshtein
4. Implementación del algoritmo de Dijkstra para el cálculo de la distancia entre dos nodos (exposición)
 
[Extras](/Extras)
