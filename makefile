CFLAGS = -std=c++2a 
CC = g++

SRC = main.cpp readGraph.cpp greedyIC.cpp aprox_esper.cpp difusioIC.cpp difusioLT.cpp greedyLTgrau.cpp greedyLTexhaustiu.cpp localSearchLT.cpp localSearchIC.cpp metaheuristicaLT.cpp

all: main

main: $(SRC)
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	rm main