# Las instrucciones que comienzan con 'w' están hechas
# para la funcionalidad en plataformas Windows
run: ejecutable
	./run.sh
wrun: ejecutable
	./run.bat
ejecutable: main.c frecuencias.o codificacion.o
	gcc main.c frecuencias.o codificacion.o
frecuencias.o:
	gcc -c frecuencias.c
codificacion.o:
	gcc -c codificacion.c
clean:
	rm frecuencias.o
	rm codificacion.o
	rm a.out	
wclean:
	rm frecuencias.o
	rm codificacion.o
	rm a.exe	

