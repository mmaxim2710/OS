all: client server

client:
	gcc -std=c99 -pthread -Wall -D_POSIX_SOURCE=600 -D_XOPEN_SOURCE=600 client.c -o client -L/usr/local/lib -lzmq -lm

server:
	gcc -std=c99 -pthread -Wall -D_POSIX_SOURCE=600 -D_XOPEN_SOURCE=600 bank.c server.c -o server -L/usr/local/lib -lzmq -lm

clean:
	rm -f *.o client server
