selectionSort: main.o
	g++ -g main.o -o selectionSort

main.o: main.cpp
	g++ -g -c main.cpp

clean:
	rm *.o
	rm selectionSort

run: selectionSort
	./selectionSort

debug: main
	gdb main