bTree: main.o node.o
	g++ -g main.o node.o -o bTree

main.o: main.cpp node.h
	g++ -g -c main.cpp

node.o: node.cpp node.h
	g++ -g -c node.cpp

clean:
	rm *.o
	rm bTree

run: bTree
	./bTree

debug: bTree
	gdb bTree

valgrind: bTree
	valgrind --leak-check=full ./bTree