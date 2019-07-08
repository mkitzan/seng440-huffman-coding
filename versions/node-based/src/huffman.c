#include "huffman.h"

#include <stdio.h>

unsigned int encode(const char *text, uint32_t *code) {
    unsigned int loc = 0, len = 0;
    uint32_t buffer = 0;
    uint8_t key;

    for(int i = 0; text[i] != 0; ++i) {
        key = text[i];
        buffer |= DICTIONARY[key].code << len;
        len += DICTIONARY[key].len;

        if(len >= CODE) {
            len -= CODE;
            code[loc++] = buffer;
            buffer = DICTIONARY[key].code >> (DICTIONARY[key].len - len);
        }
    }

    code[loc++] = buffer;

    return loc;
}


unsigned int decode(const uint32_t *code, char *text) {
    unsigned int loc = 0, bit = 0, pos = 0;
    uint32_t buffer = code[0];
    hnode_t curr, root = *ROOT;

    do {
        curr = root;

        while(curr.left || curr.right) {
            if((buffer & 1) == 1) {
                curr = *(curr.right);
            } else {
                curr = *(curr.left);
            }
            
            buffer >>= 1;
            
            if(++bit >= CODE) {
                buffer = code[++pos];
                bit = 0;
            }
        }
        
        text[loc++] = curr.letter;
    } while(curr.letter != 0x03);

    return loc;
}
