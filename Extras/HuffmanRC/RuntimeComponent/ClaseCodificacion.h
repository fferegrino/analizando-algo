#pragma once

using namespace Platform;
#ifndef __CLASECODIFICACION_H__
#define	__CLASECODIFICACION_H__

namespace RuntimeComponent
{
	public ref class ClaseCodificacion sealed
	{
	public:
		ClaseCodificacion();
		//int Codificar(Platform::String^ archivoOrigen, Platform::String^ archivoSimbolos, Platform::String^ archivoDestino);
		int Codificar(const Platform::Array<byte>^ origen, Platform::WriteOnlyArray<byte>^ simbolos, Platform::WriteOnlyArray<byte>^ destino);
		int Decodificar(Platform::String^ archivoOrigen, Platform::String^ archivoSimbolos, Platform::String^ archivoDestino);

	private:
		int ConvierteCaracteres(const Platform::Array<byte>^ origen, char ** out);
	};
}

#endif /* __CLASECODIFICACION_H__ */