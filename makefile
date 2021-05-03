all: main

main: main.o rotinas.o
	gcc -o main main.o rotinas.o -pthread

rotinas.o: rotinas.c
	gcc -c rotinas.c
main.o: main.c
	gcc -c main.c
