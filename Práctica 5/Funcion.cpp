#include "Funcion.h"
#include <cmath>

Funcion::Funcion(int inf,int sup){
	random = new Random();
	superior = sup;
	inferior = inf;
}

Funcion::~Funcion(){
	delete random;
}

double Funcion::Rand(){
	return random->NextDoble(inferior, superior);
}

double Funcion::Evaluar(int iteraciones){
	int i = 0;
	double resultado = 0.0;
	double aleatorio = 0.0;
	// Iteramos tantas veces como se indique
	for(i = 0; i < iteraciones ; i++){
		// Obtenemos un valor aleatorio comprendido dentro del rango
		aleatorio = Rand();
		// Aquí se evalúa la función deseada. Debemos sustituir 
		// todas las variables dentro de nuestra función por 
		// el valor de nuestras variables aleatorias. En este caso, 
		// la función es simple: (e^x) * (x^2) 
		resultado += /*exp(aleatorio) * */ pow(aleatorio, 2.0);
	}
	// Obtenemos el factor de división para ajustar el resultado
	double divisor = (superior - inferior) / (double)iteraciones;
	resultado *=  divisor;
	return resultado;
}

double Funcion::Uniforme() {
	return random->Uniforme(inferior, superior);
}
