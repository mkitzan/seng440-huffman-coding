# makefile for seng440 project
# node based huffman tree

CC=gcc
CFLAGS=-c -O3

all: huffman_test huffman_utils.o huffman.o huffman_test_perf.o huffman_test_basic.o
    
huffman_test: huffman.o huffman_utils.o huffman_test_basic.o huffman_test_perf.o
	$(CC) huffman_utils.o huffman.o huffman_test_basic.o -o huffman_test_basic
	$(CC) huffman_utils.o huffman.o huffman_test_perf.o -o huffman_test_perf

huffman_test_basic.o: test/huffman_test_basic.c
	$(CC) $(CFLAGS) test/huffman_test_basic.c

huffman_test_perf.o: test/huffman_test_perf.c
	$(CC) $(CFLAGS) test/huffman_test_perf.c

huffman.o: src/huffman.c src/huffman.h src/huffman_utils.h
	$(CC) $(CFLAGS) src/huffman.c

huffman_utils.o: src/huffman_utils.c src/huffman_utils.h
	$(CC) $(CFLAGS) src/huffman_utils.c

asm:
	$(CC) -O3 -S src/huffman.c

clean:
	rm huffman*
