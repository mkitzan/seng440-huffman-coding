#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "huffman_utils.h"

unsigned int encode(const char *text, uint16_t *code);

unsigned int decode(const uint16_t *code, char *text);

#endif
