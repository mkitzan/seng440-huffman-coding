#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "huffman_utils.h"

unsigned int encode(const char *text, unsigned char *code);

unsigned int decode(const unsigned char *code, char *text);

#endif
