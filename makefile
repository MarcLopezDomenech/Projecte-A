CFLAGS = -std=c++2a 
CC = g++

all: main

main: main.cpp greedyIC.cpp
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	rm main