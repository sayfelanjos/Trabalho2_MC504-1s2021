###############################################################################################
######################### Compilação com suporte a múltiplos arquivos #########################
###############################################################################################

.PHONY: build clean

ARQ_MAIN =  main # $(shell basename $(shell pwd))

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

CFLAGS = -g -Wall -lm -pthread

build: $(OBJECTS)
	gcc *.o -o  $(ARQ_MAIN) $(CFLAGS)

%.o: %.c
	gcc -c $< -o $@ $(CFLAGS)

softClean:
	rm -f *.o;



# all: main

# main: main.o rotinas.o
# 	gcc -o main main.o rotinas.o -pthread

# rotinas.o: rotinas.c
# 	gcc -c rotinas.c
# main.o: main.c
# 	gcc -c main.c
