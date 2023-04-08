CFLAGS = -std=c++2a 
CC = g++

SRC = main.cpp algorismes/readGraph.cpp algorismes/greedyIC.cpp algorismes/aprox_esper.cpp algorismes/difusioIC.cpp algorismes/difusioLT.cpp algorismes/greedyLTgrau.cpp algorismes/localSearchLT.cpp algorismes/localSearchIC.cpp algorismes/metaheuristicaLT.cpp

all: main

main: $(SRC)
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	rm main