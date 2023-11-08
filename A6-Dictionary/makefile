dictionary: main.o
	g++ -g main.o -o dictionary

main.o: main.cpp
	g++ -g -c main.cpp

clean:
	rm *.o
	rm dictionary

run: dictionary
	./dictionary

debug: dictionary
	gdb dictionary

valgrind: dictionary
	valgrind --leak-check=full ./dictionary