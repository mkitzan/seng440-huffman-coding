# makefile for seng440 project
# 05-03-2019

CC=gcc
CFLAGS=-Wall -g -c -O3

all: huffman_test huffman_alphabet huffman_utils.o huffman.o huffman_build.o huffman_alphabet.o huffman_test.o
    
huffman_test: huffman.o huffman_utils.o huffman_test.o
	$(CC) huffman_utils.o huffman.o huffman_test.o -o huffman_test

huffman_alphabet: huffman_alphabet.o huffman_build.o
	$(CC) huffman_alphabet.o huffman_build.o -o huffman_alphabet

huffman_test.o: tests/huffman_test.c
	$(CC) $(CFLAGS) tests/huffman_test.c

huffman_alphabet.o: tests/huffman_alphabet.c
	$(CC) $(CFLAGS) tests/huffman_alphabet.c

huffman.o: src/huffman.c src/huffman.h src/huffman_utils.h
	$(CC) $(CFLAGS) src/huffman.c

huffman_utils.o: src/huffman_utils.c src/huffman_utils.h
	$(CC) $(CFLAGS) src/huffman_utils.c

huffman_build.o: tests/huffman_build.c tests/huffman_build.h
	$(CC) $(CFLAGS) tests/huffman_build.c

asm: tests/huffman_build.c tests/huffman_build.h
	$(CC) -Wall -g -O3 -S src/huffman.c

clean:
	rm *.o *.s *.exe
