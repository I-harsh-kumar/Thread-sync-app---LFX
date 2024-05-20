CC = gcc
CFLAGS = -pthread -lrt

all: main

main: main.c 
	$(CC) $(CFLAGS) -o main main.c
	@echo "Application built successfully."

clean:
	rm -f main
