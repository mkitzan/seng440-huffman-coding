#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "huffman_utils.h"

unsigned int encode(const char *text, unsigned long long int *code);

unsigned int decode(const unsigned long long int *code, char *text);

#endif
