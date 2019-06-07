#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

//extern hnode_t CACHE[8];
extern hnode_t *ROOT;
extern hcode_t DICTIONARY[SIZE];

unsigned int encode(const char *text, unsigned long long int *code) {
    register unsigned int i = 0, loc = 0, len = 0;
    register unsigned char key;
    unsigned long long int buffer = 0;

    for(; text[i]; ++i) {
        key = text[i];
        buffer |= DICTIONARY[key].code << len;
        len += DICTIONARY[key].len;

        if(len & CODE) {
            len -= CODE;
            code[loc++] = buffer;
            buffer = DICTIONARY[key].code >> (DICTIONARY[key].len - len);
        }
    }

    code[loc++] = buffer;

    return loc;
}


unsigned int decode(const unsigned long long int *code, char *text) {
    register unsigned int loc = 0, bit = 0, pos = 0;
    unsigned long long int buffer = code[0];
    hnode_t curr, root = *ROOT;

    do {
        curr = root;

        while(curr.letter & SIZE) {
            if(buffer & 1) {
                curr = *(curr.right);
            } else {
                curr = *(curr.left);
            }
            
            buffer >>= 1;
            
            if(++bit & CODE) {
                buffer = code[++pos];
                bit = 0;
            }
        }
        
        text[loc++] = curr.letter;
    } while(curr.letter != 0x03);

    return loc;
}
