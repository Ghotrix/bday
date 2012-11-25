all: main

main: main.o crypt.o
	gcc -o test main.o crypt.o -lssl -lcrypto

main.o: main.c
	gcc -g -c main.c

crypt.o: crypt.c
	gcc -g -c crypt.c

clean:
	rm *.o test
