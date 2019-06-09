# makefile for seng440 project
# 05-03-2019

CC=gcc
CFLAGS=-Wall -g -c -O3

all: huffman_test huffman_alphabet huffman.o huffman_utils.o huffman_alphabet.o huffman_test.o
    
huffman_test: huffman.o huffman_utils.o huffman_test.o
	$(CC) huffman.o huffman_utils.o huffman_test.o -o huffman_test

huffman_alphabet: huffman_alphabet.o huffman_utils.o
	$(CC) huffman_alphabet.o huffman_utils.o -o huffman_alphabet

huffman_test.o: tests/huffman_test.c
	$(CC) $(CFLAGS) tests/huffman_test.c

huffman_alphabet.o: tests/huffman_alphabet.c
	$(CC) $(CFLAGS) tests/huffman_alphabet.c

huffman.o: src/huffman.c src/huffman.h src/huffman_utils.h
	$(CC) $(CFLAGS) src/huffman.c

huffman_utils.o: src/huffman_utils.h src/huffman_utils.c
	$(CC) $(CFLAGS) src/huffman_utils.c

clean:
	rm *.o *.exe
