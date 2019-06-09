#ifndef _HUFFMAN_UTILS_H_
#define _HUFFMAN_UTILS_H_

#define HEAP 255
#define SIZE 128
#define CODE  64
#define TEXT   8
#define MSB  0x8000000000000000

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
    unsigned long long int code;
    unsigned char len;
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
    unsigned char next;
    hnode_t heap[HEAP];
};


hcode_t ALPHABET[SIZE];
hheap_t HUFFMAN;


void build();

#endif
