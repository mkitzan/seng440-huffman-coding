#ifndef _HUFFMAN_UTILS_H_
#define _HUFFMAN_UTILS_H_

#include <inttypes.h>
#include "huffman_data.h"

#define HEAP 188
#define SIZE 128
#define CODE (sizeof(uint32_t) * 8)
#define TEXT (sizeof(char) * 8)

// dictionary struct to hold code and code length values for each alphabet char
typedef struct hcode hcode_t;
struct __attribute__((__packed__)) hcode {
    uint16_t code;
    uint8_t len;
};

// binary tree node struct to hold letter and child nodes
typedef struct hnode hnode_t;
struct __attribute__((__packed__)) hnode {
    char letter;
    hnode_t *left, *right;
};

// global references to the statically allocated huffman tree and dictionary
hcode_t *DICT;
hnode_t *TREE;

void build();

#endif
