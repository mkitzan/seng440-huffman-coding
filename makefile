# makefile for seng440 project
# 05-03-2019

CC=gcc
CFLAGS=-c -O3

all: huffman_test huffman_alphabet huffman_utils.o huffman.o huffman_lookup.o huffman_build.o huffman_alphabet.o huffman_test_perf.o
    
huffman_test: huffman.o huffman_utils.o huffman_test_basic.o huffman_test_perf.o
	$(CC) huffman_utils.o huffman.o huffman_test_basic.o -o huffman_test_basic
	$(CC) huffman_utils.o huffman.o huffman_test_perf.o -o huffman_test_perf

huffman_alphabet: huffman_alphabet.o huffman_build.o huffman_lookup.o
	$(CC) huffman_alphabet.o huffman_build.o huffman_lookup.o -o huffman_alphabet

huffman_test_perf.o: test/huffman_test_perf.c test/huffman_test_perf.h
	$(CC) $(CFLAGS) test/huffman_test_perf.c

huffman_test_basic.o: test/huffman_test_basic.c
	$(CC) $(CFLAGS) test/huffman_test_basic.c

huffman_alphabet.o: build/huffman_alphabet.c
	$(CC) $(CFLAGS) build/huffman_alphabet.c

huffman.o: src/huffman.c src/huffman.h src/huffman_utils.h
	$(CC) $(CFLAGS) src/huffman.c

huffman_utils.o: src/huffman_utils.c src/huffman_utils.h
	$(CC) $(CFLAGS) src/huffman_utils.c

huffman_build.o: build/huffman_build.c build/huffman_build.h
	$(CC) $(CFLAGS) build/huffman_build.c

huffman_lookup.o: build/huffman_lookup.c build/huffman_lookup.h
	$(CC) $(CFLAGS) build/huffman_lookup.c

asm: build/huffman_build.c build/huffman_build.h
	$(CC) -O3 -S src/huffman.c

clean:
	rm huffman*
