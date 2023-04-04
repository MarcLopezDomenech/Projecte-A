CFLAGS = -std=c++2a 
CC = g++

all: main

build/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

main: build/main.o build/readGraph.o build/greedyIC.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm build/*
	rm main