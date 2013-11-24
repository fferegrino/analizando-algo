#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Funcion.h"
#include "Aproximacion.h"

using namespace std;

int main(int argc, char * argv[]){
	int i = 0, j = 0;
	int numeroIteraciones = 0;
	int iteraciones = 0;
	int limiteSuperior = 0, limiteInferior = 0;
	
	// Leemos la cantidad de pruebas a correr
	cin >> numeroIteraciones;
	
	if(argv[1][0] == 'p'){ // Aproximación a PI
		Aproximacion * apr;
		apr = new Aproximacion();
		
		for(i = 0; i < numeroIteraciones; ++i){
			cin >> iteraciones;
			double pi = apr->Pi(iteraciones);
			cout 	<< "pi" << "|"
					<< iteraciones << "|"
					<< apr->dardosAcertados << "|"
					<< pi 
					<< endl;
		}
		delete apr;
	} else { // Integración de Monte Carlo
	
		Funcion * f;
		
		cin >> limiteInferior;
		cin >> limiteSuperior;
		
		f = new Funcion(limiteInferior,limiteSuperior);
		
		for(int i = 0; i < numeroIteraciones; ++i) {
			cin >> iteraciones;
			cout 	<< "funcion" << "|"
					<< limiteInferior << "|" 
					<< limiteSuperior << "|" 
					<< iteraciones << "|" 
					<< f->Evaluar(iteraciones)
					<< endl;
		}
		delete f;
	}
	
	return 0;
}