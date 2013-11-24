run: compile
	./test.bat
compile: Funcion.o Random.o
	g++ main.cpp Funcion.o Random.o -std=c++11
Funcion.o:
	g++ -c Funcion.cpp -std=c++11
Random.o:
	g++ -c Random.cpp -std=c++11
clean:
	rm Funcion.o
	rm Random.o
	rm a.exe