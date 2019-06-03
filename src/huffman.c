#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

extern hnode_t CACHE[8];
extern hcode_t DICTIONARY[SIZE];

unsigned int encode(const char *text, unsigned char *code) {
    unsigned int i, loc = 0;
    unsigned char key, buffer = 0, len = 0;

    for(i = 0; text[i]; ++i) {
        key = text[i] - '?';
        buffer |= DICTIONARY[key].code << len;
        len += DICTIONARY[key].len;

        if(len >= 8) {
            len -= 8;
            code[loc++] = buffer;
            buffer = DICTIONARY[key].code >> (DICTIONARY[key].len - len);
        }
    }

    code[loc++] = buffer;

    return loc;
}


unsigned int decode(const unsigned char *code, char *text) {
    unsigned int loc = 0, pos = 1;
    unsigned char buffer = code[0], len = 0, lvl = 0;
    hnode_t curr;

    do {
        lvl = 3;
        curr = CACHE[buffer & 7];
        buffer >>= lvl;

        while(curr.left || curr.right) {
            if(buffer & 1) {
                curr = *(curr.right);
            } else {
                curr = *(curr.left);
            }
            
            lvl += 1;
            buffer >>= 1;
        }

        buffer |= (code[pos] >> len) << (8 - lvl);
        len += lvl;

        if(len >= 8) {
            len -= 8;
            buffer |= code[++pos] << (8 - len);
        }        

        text[loc++] = curr.letter;

    } while(curr.letter != '@');

    return loc;
}
