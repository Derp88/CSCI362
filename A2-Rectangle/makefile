rectangle: main.o
	g++ -g main.o -o rectangle

main.o: main.cpp
	g++ -g -c main.cpp

clean:
	rm *.o
	rm rectangle

run: rectangle
	./rectangle

debug: main
	gdb main