CC = g++
CFLAGS = -Wall -std=c++11

all: main

main: main.cc lines/slope.cc
	$(CC) $(CFLAGS) main.cc lines/slope.cc -o main

clean:
	rm -f main
