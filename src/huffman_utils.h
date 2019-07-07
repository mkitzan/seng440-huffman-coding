#ifndef _HUFFMAN_UTILS_H_
#define _HUFFMAN_UTILS_H_

#include <inttypes.h>
#include "huffman_data.h"

#define HEAP 188
#define SIZE 128
#define CODE (sizeof(uint16_t) * 8)
#define TEXT (sizeof(char) * 8)

// dictionary struct to hold code and code length values for each alphabet char
typedef struct hcode hcode_t;
struct __attribute__((__packed__)) hcode {
    uint16_t code;
    uint8_t len;
};

// lookup table entry struct holds letter and contributing bit count
typedef struct hlook hlook_t;
struct __attribute__((__packed__)) hlook {
    char letter;
    uint8_t contrib;
};


// pointer to a lookup table which also holds the value to help copy input data
typedef struct htable htable_t;
struct __attribute__((__packed__)) htable {
    hlook_t *table;
    uint8_t draw;
};

// global references to the statically allocated huffman dictionary and lookup tables
hcode_t *DICT;
htable_t *LOOKUP;

void build();

#endif
