all: main

main: main.o crypt.o
	g++ -o bday main.o crypt.o -lcrypto

main.o: main.cpp
	g++ -g -c main.cpp

crypt.o: crypt.cpp
	g++ -g -c crypt.cpp

clean:
	rm *.o bday
