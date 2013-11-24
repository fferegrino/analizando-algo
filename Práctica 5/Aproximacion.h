#include "Random.h"

#ifndef APROXIMACION_H
#define APROXIMACION_H

class Aproximacion
{

// http://www.mathcs.emory.edu/~cheung/Courses/170/Syllabus/07/compute-pi.html
	public:
		// Constructor
		Aproximacion();
		~Aproximacion();
		// Funciones
		double Pi(int dardos);
		// Miembros
		int dardosAcertados;
	
	private:
		Random * random;
};

#endif