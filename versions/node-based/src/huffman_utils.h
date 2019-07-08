#ifndef _HUFFMAN_UTILS_H_
#define _HUFFMAN_UTILS_H_

#include <inttypes.h>

#define SIZE  128
#define CODE  (sizeof(uint32_t) * 8)
#define WIDTH (sizeof(uint16_t) * 8)
#define TEXT  (sizeof(char) * 8)
#define MSB   0x8000

typedef struct hcode hcode_t;
struct __attribute__((__packed__)) hcode {
    uint8_t len;
    uint16_t code;
};

typedef struct hnode hnode_t;
struct __attribute__((__packed__)) hnode {
    char letter;
    hnode_t *left, *right;
};

typedef struct huffman huffman_t;
struct __attribute__((__packed__)) huffman {
    uint8_t freq;
    char letter;
};

typedef struct node node_t;
struct __attribute__((__packed__)) node {
    huffman_t data;
    node_t *left, *right;
};

hnode_t *ROOT;
hcode_t DICTIONARY[SIZE];

void build();

#endif
