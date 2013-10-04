run: a.out
	./script.sh
test: a.out
	./test.sh
a.out: main.c lector.o ordenacion.o arbol.o
	gcc main.c lector.o ordenacion.o arbol.o
lector.o:
	gcc -c lector.c
ordenacion.o: arbol.o
	gcc -c ordenacion.c arbol.o
arbol.o:
	gcc -c arbol.c
clean:
	rm a.out
	rm lector.o
	rm ordenacion.o
	rm arbol.o
cleanResultados:
	rm resultados/*.*
