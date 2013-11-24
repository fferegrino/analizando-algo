#include "Random.h"

#ifndef FUNCION_H
#define FUNCION_H

class Funcion
{
	public:
		// Constructor
		Funcion(int inf, int sup);
		~Funcion();
		// Funciones
		double Evaluar(int iteraciones);
		double Uniforme();
		double Rand();
		// Miembros
		int superior;	// Limite superior
		int inferior;	// Limite inferior
	
	private:
		Random * random;
};

/**
 * Función a evaluar
 * @param variable Es el valor que le asignaremos para evaluar
 */
inline double FuncionAEvaluar(double variable){
	// Aquí se evalúa la función deseada. Debemos sustituir 
	// todas las variables dentro de nuestra función por 
	// el valor de nuestras variables aleatorias. En este caso, 
	// la función es simple: (e^x) * (x^2) 
	return exp(variable) * pow(variable, 2.0);
}


#endif