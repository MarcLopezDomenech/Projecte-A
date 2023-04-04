CFLAGS = -std=c++2a 
CC = g++

all: main

main: main.cpp
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	rm build/*
	rm main