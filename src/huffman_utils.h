#ifndef _HUFFMAN_UTILS_H_
#define _HUFFMAN_UTILS_H_

#define SIZE 28
#define LEN  16

typedef struct hcode hcode_t;
struct __attribute__((__packed__)) hcode {
    unsigned char len;
    unsigned char code;
};

typedef struct hnode hnode_t;
struct __attribute__((__packed__)) hnode {
    char letter;
    hnode_t *left, *right;
};

typedef struct huffman huffman_t;
struct __attribute__((__packed__)) huffman {
    unsigned char freq;
    char letter;
};

typedef struct node node_t;
struct __attribute__((__packed__)) node {
    huffman_t data;
    node_t *left, *right;
};

hnode_t *ROOT;
hnode_t CACHE[8];
hcode_t DICTIONARY[SIZE];

void build();

#endif
