bTree: main.o
	g++ -g main.o -o bTree

main.o: main.cpp
	g++ -g -c main.cpp

clean:
	rm *.o
	rm bTree

run: bTree
	./bTree

debug: bTree
	gdb bTree

valgrind: bTree
	valgrind --leak-check=full ./bTree