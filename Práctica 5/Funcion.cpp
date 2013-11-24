#include "Funcion.h"
#include <cmath>
/**
 *
 * @param inf El límite inferior de nuestra función
 * @param sup El límite superior de nuestra función
 */
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

/**
 * Método encargado de realizar la evaluación probabilista de la integral
 * Vea: http://beam.acclab.helsinki.fi/~knordlun/mc/mc5nc.pdf
 * @param iteraciones
 * @return El valor aproximado de la integral
 */
double Funcion::Evaluar(int iteraciones){
	int i = 0;
	double resultado = 0.0;
	double aleatorio = 0.0;
	// Iteramos tantas veces como se indique
	for(i = 0; i < iteraciones ; i++){
		// Obtenemos un valor aleatorio comprendido dentro del rango
		aleatorio = Rand();
		// Ejecutamos la función que queremos integrar
		resultado += FuncionAEvaluar(aleatorio);
	}
	// Obtenemos el factor de división para ajustar el resultado
	double divisor = (superior - inferior) / (double)iteraciones;
	resultado *=  divisor;
	return resultado;
}

double Funcion::Uniforme() {
	return random->Uniforme(inferior, superior);
}
