CPPFLAGS = -O3 -Wall -Werror
CC = g++

PROGS = main
default: $(PROGS)

main: main.o NN.o
	$(CC) $(CPPFLAGS) -o $@ main.o NN.o

main.o: main.cpp NN.h
	$(CC) -c main.cpp -o $@

NN.o: NN.cpp NN.h
	$(CC) -c ACO.cpp -o $@

clean:
	rm *.o
	rm -f main
