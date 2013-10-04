run: a.out
	./run.sh
test: a.out
	./test.sh
compila: a.out

a.out: main.c BMP.o
	gcc main.c BMP.o -lm -lpthread
BMP.o:
	gcc -c BMP.c
clean:
	rm a.out
	rm BMP.o
cleanResultados:
	rm resultados/*.*
