/* 
 * File:        BMP.h
 * Author:      Antonio Feregrino Bolanos
 * Version:     1.0
 * Descripción: Librería para el tratamiento de imágenes BMP de 24 bits
 * 
 * Conversión a librería de BMP.c (C) Marzo 2013 Versión 1.5, de Edgardo Adrián Franco, 
 * disponible en http://www.eafranco.com/docencia/analisisdealgoritmos/files/practicas/03/BMP24BitsEnC.zip
 * 
 * Created on October 3, 2013, 10:33 PM
 */

#ifndef BMP_H
#define	BMP_H

#ifdef	__cplusplus
extern "C" {
#endif

    // 
    
    /**
     * Estructura para almacenar la imagen, así como todas sus propiedades
     */
    typedef struct bmp
    {
        char bm[2];			//(2 Bytes) BM (Tipo de archivo)
        int tamano;			//(4 Bytes) Tamaño del archivo en bytes
        int reservado;			//(4 Bytes) Reservado
        int offset;			//(4 Bytes) offset, distancia en bytes entre la img y los píxeles
        int tamanoMetadatos;		//(4 Bytes) Tamaño de Metadatos (tamaño de esta estructura = 40)
        int alto;			//(4 Bytes) Ancho (numero de píxeles horizontales)
        int ancho;			//(4 Bytes) Alto (numero de pixeles verticales)
        short int numeroPlanos;		//(2 Bytes) Numero de planos de color
        short int profundidadColor;	//(2 Bytes) Profundidad de color (debe ser 24 para nuestro caso)
        int tipoCompresion;		//(4 Bytes) Tipo de compresión (Vale 0, ya que el bmp es descomprimido)
        int tamanoEstructura;		//(4 Bytes) Tamaño de la estructura Imagen (Paleta)
        int pxmh;			//(4 Bytes) Píxeles por metro horizontal
        int pxmv;			//(4 Bytes) Píxeles por metro vertical
        int coloresUsados;		//(4 Bytes) Cantidad de colores usados 
        int coloresImportantes;		//(4 Bytes) Cantidad de colores importantes
        unsigned char **pixelR; 	//Puntero a los pixeles del plano R (Rojo)
        unsigned char **pixelG; 	//Puntero a los pixeles del plano G (Verde)
        unsigned char **pixelB; 	//Puntero a los pixeles del plano B (Azul)
    }BMP;

    /**
     * Función encargada de abrir una imagen a partir de una ruta especificada
     * @param imagen La estructura en la que residirá la información de la imagen abierta
     * @param ruta La ruta en la que se encuentra la imagen que deseamos abrir
     */
    void abrir_imagen(BMP *imagen, char *ruta);
    
    /**
     * Función encargada de guardar una imagen en la ruta especificada
     * @param imagen La estructura en la que está la información relacionada con la imagen que queremos guardar
     * @param ruta La ruta en la que vamos a guardar
     */
    void crear_imagen(BMP *imagen, char *ruta);
    
    /**
     * Función encargada de rotar una imagen la cantidad de grados especificada mediante el uso del algoritmo clásico de rotacion
     * @param rotacion El grado de rotación: 1 para 90, 2 para 180 y 3 para 270
     * @param imagenOriginal La imagen original a ser tratada
     * @param imagenTratada Estructura en el que se guardará la imagen tratada
     */
    void rotacion_clasica(BMP *imagenOriginal, BMP * imagenTratada);
    
	/**
	 * Función encargada de rotar una imagen la cantidad de grados especificada mediante el uso de un algoritmo con la técnica 
	 * divide y vencerás
	 * @param i El inicio del rango a tratar
	 * @param j El inicio del rango a tratar
	 * @param i1 El final del rango a tratar
	 * @param j1 El final del rango a tratar
	 * @param imagen La imagen original a ser tratada
	 * @param n El tamaño del problema
	 */
	void rota90GradosDivide(int i, int j,int i1, int j1,BMP * imagen, int n);

	/**
	 * Función encargada de rotar una imagen la cantidad de grados especificada mediante el uso de un algoritmo con la técnica 
	 * divide y vencerás, que, además incorpora el uso de threads para acelerar su ejecución
	 * @param i El inicio del rango a tratar
	 * @param j El inicio del rango a tratar
	 * @param i1 El final del rango a tratar
	 * @param j1 El final del rango a tratar
	 * @param imagen La imagen original a ser tratada
	 * @param n El tamaño del problema
	 */
	void rota90GradosDivideThreads(int i, int j, int i1, int j1, BMP * imagen, int n);

    
#ifdef	__cplusplus
}
#endif

#endif	/* BMP_H */

