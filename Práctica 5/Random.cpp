#include "Random.h"
#include <ctime>
#include <cstdlib>

Random::Random(){
	srand(time(0));
}

double Random::NextDoble(int min, int max){
	return (abs(distribution(generator) * rand()) % (max - min) + min) + Uniforme();
}

double Random::Uniforme(){
	double u;
	u = (double)(rand()) / (double)(RAND_MAX);
	return u;
}

double Random::Uniforme(int a, int b){
	double x;
	x = Uniforme() * (double)(b - a);
	return x;
}