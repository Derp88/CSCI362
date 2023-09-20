nQueens: main.o
	g++ -g main.o -o nQueens

main.o: main.cpp
	g++ -g -c main.cpp

clean:
	rm *.o
	rm nQueens
	rm *.csv
	rm *.png

run: nQueens
	./nQueens

debug: main
	gdb main