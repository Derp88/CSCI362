smallestBST: main.o
	g++ -g main.o -o smallestBST

main.o: main.cpp
	g++ -g -c main.cpp

clean:
	rm *.o
	rm smallestBST

run: smallestBST
	./smallestBST

debug: smallestBST
	gdb smallestBST

valgrind: smallestBST
	valgrind --leak-check=full ./smallestBST