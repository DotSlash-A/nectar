CC = gcc
CFLAGS = -Wall

all: main

main: main.c lines/slope.c
	$(CC) $(CFLAGS) main.c lines/slope.c -o main

clean:
	rm -f main
