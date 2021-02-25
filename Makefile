CFLAGS=--std=c18 -Wall
CC=gcc

all: linsys-solver

calculation.o: calculation.c
	$(CC) -c $(CFLAGS) $< -o $@

file_handler.o: file_handler.c
	$(CC) -c $(CFLAGS) $< -o $@

matrix.o: matrix.c
	$(CC) -c $(CFLAGS) $< -o $@

utils.o: utils.c
	$(CC) -c $(CFLAGS) $< -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@

linsys-solver: main.o calculation.o matrix.o file_handler.o utils.o
	$(CC) -o linsys-solver $^

clean:
	rm -f main.o calculation.o matrix.o file_handler.o utils.o linsys-solver
