#include "Random.h"

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