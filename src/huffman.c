#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

//extern hnode_t CACHE[8];
extern hnode_t *ROOT;
extern hcode_t DICTIONARY[SIZE];

unsigned int encode(const char *text, unsigned long long int *code) {
    unsigned int i, loc = 0, len = 0;
    unsigned long long int buffer = 0;
    unsigned char key;

    for(i = 0; text[i]; ++i) {
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


unsigned int decode(const unsigned long long int *code, char *text) {
    unsigned int loc = 0, pos = 1, len = 0, lvl = 0;
    unsigned long long int buffer = code[0];
    hnode_t curr, root = *ROOT;

    do {
        // lvl = 3;
        // curr = CACHE[buffer & 7];
        // buffer >>= lvl;
        lvl = 0;
        curr = root;

        while(curr.left || curr.right) {
            if(buffer & 1) {
                curr = *(curr.right);
            } else {
                curr = *(curr.left);
            }
            
            lvl += 1;
            buffer >>= 1;
        }

        buffer |= (code[pos] >> len) << (CODE - lvl);
        len += lvl;

        if(len >= CODE) {
            len -= CODE;
            buffer |= code[++pos] << (CODE - len);
        }        

        text[loc++] = curr.letter;

    } while(curr.letter != 0x03);

    return loc;
}
