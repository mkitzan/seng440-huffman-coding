#ifndef _HUFFMAN_BUILD_H_
#define _HUFFMAN_BUILD_H_

#include <inttypes.h>

#define HEAP 248
#define SIZE 128
#define CODE (sizeof(uint16_t) * 8)
#define TEXT (sizeof(uint8_t) * 8)
#define MSB  0x8000


typedef struct huffman huffman_t;
struct __attribute__((__packed__)) huffman {
    unsigned int freq;
    char letter;
};

typedef struct node node_t;
struct __attribute__((__packed__)) node {
    huffman_t data;
    node_t *left, *right;
};

// dictionary struct to hold code and code length values for each alphabet char
typedef struct hcode hcode_t;
struct __attribute__((__packed__)) hcode {
    uint16_t code;
    uint8_t len;
};

// reduced memory version of node_t to minimize memory loads on dereference
typedef struct hnode hnode_t;
struct __attribute__((__packed__)) hnode {
    char letter;
    hnode_t *left, *right;
};

// pseudo memory heap to build the huffman tree in
typedef struct hheap hheap_t;
struct __attribute__((__packed__)) hheap {
    uint8_t next;
    hnode_t heap[HEAP];
};

hcode_t ALPHABET[SIZE];
hheap_t HUFFMAN;

void build();

#endif
