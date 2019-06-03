#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "huffman_utils.h"

unsigned int encode(const char *text, unsigned int *code);

unsigned int decode(const unsigned int *code, char *text);

#endif
