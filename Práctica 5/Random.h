#include <random>
#include <iostream>

#ifndef RANDOM_H
#define RANDOM_H

class Random{
	public:
		// Constructor
		Random();
		// Funciones
		double Uniforme();
		double Uniforme(int min, int max);
		double NextDoble(int min, int max);
	private:
		// Miembros
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution;	
};

#endif