/*
 * File:   colacodificacion.h
 * Author: fferegrino
 *
 * Created on 27 de octubre de 2013, 06:29 AM
 */

#ifndef __COLACODIFICACION_H__
#define	__COLACODIFICACION_H__

typedef struct nodoCola {
	char valor;
	struct nodoCola * siguiente;
}NodoCola;


namespace RuntimeComponent {

	class ColaCodificacion sealed
	{

	public:
		NodoCola * inicio;
		NodoCola * final;
		int count;
		// Metodos //
		ColaCodificacion();
		void formaCodificacion(char valor);
		void formaInicioCodificacion(char valor);
		char atiendeCola();
		void atiendeTodos();
	};
}
#endif	/* __COLACODIFICACION_H__ */