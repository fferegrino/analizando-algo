run: a.out
	./script.sh
test: a.out
	./test.sh
compila: a.out

a.out: main.c lector.o arbol.o busqueda.o
	gcc main.c busqueda.o lector.o arbol.o -lm -lpthread
lector.o:
	gcc -c lector.c
busqueda.o:
	gcc -c busqueda.c -lm -lpthread
arbol.o:
	gcc -c arbol.c
clean:
	rm a.out
	rm lector.o
	rm arbol.o
	rm busqueda.o
cleanResultados:
	rm resultados/*.*
