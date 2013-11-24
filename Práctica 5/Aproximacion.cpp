#include "Aproximacion.h"
#include <cmath>

Aproximacion::Aproximacion(){
	random = new Random();
}

Aproximacion::~Aproximacion(){
	delete random;
}

/**
 * Método que ejecuta la aproximación de pi
 * @param dardos La cantidad de dardos a tirar,
 * entre mayor sea este número, mejor será la aproximación.
 * @return La aproximación a Pi
 */
double Aproximacion::Pi(int dardos) {
	double pi = 0;
	int i = 0;
	double x = 0.0, y = 0.0;
	// Reiniciamos la cantidad de aciertos
	dardosAcertados = 0;
	// Se "lanzan" tantos dardos como se haya marcado en el parametro
	for(i = 0; i < dardos; ++i) {
		// Obtenemos la siguiente posición del dardo
		y = random->Uniforme();
		x = random->Uniforme();
		// Si cae dentro del área deseada aumentamos la cantidad de aciertos
		if(pow(x,2.0) + pow(y,2.0) < 1)
			dardosAcertados++;
	}
	// Calculamos el valor aproximado de Pi
	pi = 4 * dardosAcertados / (double) dardos;
	return pi;
}