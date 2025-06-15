CC=gcc
CFLAGS=-Wall -g

all: server client main

server: server.c
	$(CC) $(CFLAGS) -c server.c

client: client.c
	$(CC) $(CFLAGS) -o client client.c

main: main.c server.o
	$(CC) $(CFLAGS) main.c server.o -o main

clean:
	rm -f *.o client main
