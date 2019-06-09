#ifndef _HUFFMAN_UTILS_H_
#define _HUFFMAN_UTILS_H_

#include "huffman_alpha.h"

#define HEAP 248
#define SIZE 128
#define CODE (sizeof(unsigned long long int) * 8)
#define TEXT (sizeof(char) * 8)

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

hcode_t *DICT;
hnode_t *TREE;

void build();

#endif
