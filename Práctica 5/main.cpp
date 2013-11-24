#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Funcion.h"

using namespace std;

int main(){
	int i = 0, j = 0;
	// Numero de limites a evaluar
	int numeroIteraciones = 0;
	int iteraciones = 0;
	int limiteSuperior = 0, limiteInferior = 0;
	Funcion * f;
	
	cin >> limiteInferior;
	cin >> limiteSuperior;
	cin >> numeroIteraciones;
	
	f = new Funcion(limiteInferior,limiteSuperior);
	
	for(int i = 0; i < numeroIteraciones; ++i) {
		cin >> iteraciones;
		cout 	<< limiteInferior << "|" 
				<< limiteSuperior << "|" 
				<< iteraciones << "|" 
				<< f->Evaluar(iteraciones)
				<< endl;
	}
	
	delete f;

	return 0;
}