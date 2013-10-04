#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BMP.h"
#include "tiempo.h"


int main(int argc, char* argv[]) {
	BMP img;

	
	// Variables para controlar el tiempo
	double 	usrtime11, systime11, walltime11,
		usrtime21, systime21, walltime21,
		real, user, sys, cpuwall;

	char IMAGEN[55];
	char IMAGEN_OUT[55];
	char tipoEjecucion = 'C';

	if(argc < 3){
		exit(1);
	}	
	if(argc == 4){ // Obtenemos el tipo de ejecución
		tipoEjecucion = argv[3][0];
	}
	strcpy(IMAGEN, argv[1]);
	strcpy(IMAGEN_OUT, argv[2]);

	abrir_imagen(&img, IMAGEN);

	uswtime(&usrtime11, &systime11, &walltime11);
	if(tipoEjecucion == 'N') // Ejecucion normal DYV
	{
		rota90GradosDivide(0,0,img.alto,img.ancho,&img,img.alto);
	}
	else if (tipoEjecucion == 'H') // Ejecucion con hilos DYV
	{
		rota90GradosDivideThreads(0,0,img.alto,img.ancho,&img,img.alto);
	}
	else // Rotacion clásica
	{
		rotacion_clasica(&img,&img);
	}
	uswtime(&usrtime21, &systime21, &walltime21);	
	// Calculo de los tiempos
	real = walltime21 - walltime11;
	user = usrtime21 - usrtime11;
	sys = systime21 - systime11;
	cpuwall = ((user + sys) * 100.0) / real;

	// Salida de resultados
	if(tipoEjecucion == 'N')
		printf("Normal DYV|%d|%.10f|%.10f|%.10f|%.10f\n",img.alto,real,user,sys,cpuwall);
	else if (tipoEjecucion == 'H')
		printf("Hilos DYV|%d|%.10f|%.10f|%.10f|%.10f\n",img.alto,real,user,sys,cpuwall);
	else
		printf("Clasica|%d|%.10f|%.10f|%.10f|%.10f\n",img.alto,real,user,sys,cpuwall);		

    	crear_imagen(&img, IMAGEN_OUT);

	//Terminar programa normalmente	
	exit(0);
}
