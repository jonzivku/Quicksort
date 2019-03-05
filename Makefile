# Makefile for p3, an implementation of quicksort

# defining target dependencies and files
p3: main.o
	g++ -o p3 main.o -Wall

# defining how each object file is to be built
main.o: main.cpp
	g++ -c main.cpp -Wall

# clean up
clean:
	rm -f p3 *.o *~
