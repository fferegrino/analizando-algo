run: a.out
	./run.sh
a.out: main.c frecuencias.o
	gcc main.c frecuencias.o
frecuencias.o:
	gcc -c frecuencias.c
clean:
	rm frecuencias.o
	rm a.out	

