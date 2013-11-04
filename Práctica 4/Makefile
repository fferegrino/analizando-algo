# Las instrucciones que comienzan con 'w' están hechas
# para la funcionalidad en plataformas Windows
run: ejecutable
	./run.sh
wrun: ejecutable 
	./run.bat
ejecutable: main.c frecuencias.o bits.o colacodificacion.o codificacion.o
	gcc main.c frecuencias.o bits.o codificacion.o colacodificacion.o
frecuencias.o:
	gcc -c frecuencias.c 
codificacion.o: 
	gcc -c codificacion.c 
colacodificacion.o:
	gcc -c colacodificacion.c
bits.o:
	gcc -c bits.c
clean:
	rm frecuencias.o
	rm colacodificacion.o
	rm codificacion.o
	rm bits.o
	rm a.out	
wclean:
	rm frecuencias.o
	rm colacodificacion.o
	rm codificacion.o
	rm bits.o
	rm a.exe	

