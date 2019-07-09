#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "huffman_utils.h"

unsigned int encode(const char *restrict text, uint32_t * restrict code);

unsigned int decode(const uint32_t *restrict code, char *restrict text);

#endif
